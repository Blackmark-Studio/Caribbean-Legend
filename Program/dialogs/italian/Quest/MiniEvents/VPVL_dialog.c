
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		////// Леа Карно //////
		
		case "Exit":
			DialogExit();
		break;
		
		case "First Time":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+"! Perdonate, siete forse un marinaio"+GetSexPhrase("o","oress")+"?";
			link.l1 = "Sono il Capitano "+GetFullName(pchar)+", al vostro servizio.";
			link.l1.go = "Lea First Talk";
			DelLandQuestMark(npchar);
		break;

		case "Lea First Talk":
			dialog.text = "Io sono Lea. Lea Carno... "+GetSexPhrase("Monsieur","Mademoiselle")+" Capitano, siete giunto da poco? Non avreste per caso visto in mare una barca da pesca chiamata 'Cormorano'? Vedete, mio marito... mio marito Pierre... è salpato due giorni fa e non ha fatto ritorno.";
			link.l1 = "Il 'Cormorano'? No, non mi è mai capitato d’incontrare una nave con quel nome. Me lo sarei ricordato, senza dubbio. Mi dispiace, madama. Spero che vostro marito stia bene e che sia solo in ritardo lungo la rotta.";
			link.l1.go = "Lea First Talk Rep Plus";
			link.l2 = "Il 'Cormorano'? Ah! È il nome della barca o il soprannome del suo padrone? In ogni caso, non ho visto né l’uno né l’altro.";
			link.l2.go = "Lea First Talk Rep Minus";
		break;

		case "Lea First Talk Rep Plus":
			dialog.text = "Non so più che pensare... Non è mai stato via così a lungo. Tornava sempre prima di mezzogiorno, senza mai mancare. Ora... è successo qualcosa. Lo sento nelle ossa.";
			link.l1 = "Vai dalle autorità. Possono mandare una nave di pattuglia a perlustrare le acque costiere.";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
		break;

		case "Lea First Talk Rep Minus":
			dialog.text = "Non so che pensare... Non è mai stato via così tanto. Tornava sempre entro mezzogiorno, senza mai mancare. Ora... è successo qualcosa. Lo sento nelle ossa.";
			link.l1 = "Vai dalle autorità. Possono mandare una nave di pattuglia a perlustrare queste acque costiere.";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
		break;

		case "Lea First Talk1":
			dialog.text = "Oh, "+GetSexPhrase("Monsieur","Mademoiselle")+" Capitano, certo che ho già parlato col comandante. Ma a che è servito? Si è solo scrollato le spalle... Ha detto che non aveva navi libere per cercare mio marito.\nE io? Non mi resta che restare qui, fissare l’orizzonte, aspettare... e sperare.";
			link.l1 = "Su, su, Madame Lea. Non vi disperate ancora. Credo di poter sacrificare una giornata per aiutarvi nella ricerca.";
			link.l1.go = "Agree To Help";
			link.l2 = "Perché darsi tanto pensiero? Forse la brezza mattutina l’ha sospinto tra le braccia di qualche bella dama. Farà due passi, respirerà l’aria fresca e tornerà.";
			link.l2.go = "bad joke";
			link.l3 = "Vuoi un consiglio? Smetti di fissare l’orizzonte. Vai alla taverna di Le François e cerca lì il tuo caro marito. Non volermene, ma probabilmente aveva solo bisogno di una pausa dalle faccende di casa, e tu stai facendo una tragedia. Che la fortuna ti assista.";
			link.l3.go = "Rejection";
		break;

		case "Agree To Help":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Capitano, io... io non so nemmeno come ringraziarti... Tu... tu non hai idea di quanto significhi per me! Tutti se ne fregano... Ma tu... tu sei disposto ad aiutarmi. Grazie!";
			link.l1 = "Non ringraziarmi ancora. Dimmi solo—dove gettava la rete di solito tuo marito? Aveva una cala fissa, o gli piaceva vagabondare?";
			link.l1.go = "Go To Help";
		break;
		
		case "bad joke":
			dialog.text = "Una dama affascinante?! Pensate davvero che sia il momento giusto per scherzare? So che lui è nei guai... e voi ridete del mio dolore! (piange) Tutto il mondo mi volta le spalle, ora. Nessuno vuol darmi una mano... Nessuno comprende il peso che porto nel petto.";
			link.l1 = "Madame Lea, per l’amor del cielo, perdona la mia sventatezza. Non volevo offenderti! Te lo giuro, cercherò tuo marito. Dimmi solo da dove cominciare.";
			link.l1.go = "bad joke1";
		break;

		case "bad joke1":
			dialog.text = "Tu...? Vuoi davvero aiutarmi?";
			link.l1 = "Ma certo. È il minimo che possa fare per farmi perdonare quella mia battuta infame e fuori luogo.";
			link.l1.go = "bad joke2";
		break;

		case "bad joke2":
			dialog.text = "Grazie, "+GetSexPhrase("Monsieur","Mademoiselle")+" Capitano. Grazie... Davvero, mi avete preso alla sprovvista—non so che dire...";
			link.l1 = "Niente ringraziamenti per ora. Dimmi piuttosto—dove va a pescare di solito tuo marito? Ha un posto fisso o si sposta qua e là?";
			link.l1.go = "Go To Help";
		break;

		case "Go To Help":
			dialog.text = "Beh... Pierre... Raramente mi diceva dove pescava di preciso. Lo chiamava 'il suo segreto'. Ma se può servire a trovarlo... Forse... Non so... Hai davvero intenzione di aiutare, vero, "+GetSexPhrase("Monsieur","Mademoiselle")+" Capitano? Davvero?";
			link.l1 = "Ti domandi se rivelarmi il posto segreto dove tuo marito va a pescare? Ti do la mia parola da capitano: il segreto della tua famiglia resterà al sicuro con me. Ma devo conoscere quel luogo per iniziare la ricerca.";
			link.l1.go = "Go To Help1";
		break;

		case "Go To Help1":
			dialog.text = "Hai ragione, "+GetSexPhrase("Monsieur","Mademoiselle")+" Capitano... Perdonatemi. Quel luogo aveva un grande valore per Pierre. Diceva sempre che era il suo unico vero segreto, il suo piccolo tesoro.\nMa io so dov’è. Se può aiutarlo a tornare a casa... Pescava vicino alla Baia di Le Marin. È sulla costa sud, non lontano dal paese. Ve ne supplico—trovatelo!";
			link.l1 = "Non temere, Lea. Farò tutto ciò che è in mio potere. Aveva dei nemici? Qualcuno lo aveva minacciato di recente?";
			link.l1.go = "Go To Help2";
		break;

		case "Go To Help2":
			dialog.text = "Nemici? Pierre? È la creatura più gentile che calchi questa terra! Non farebbe del male nemmeno a una mosca... È solo un umile pescatore. Chi mai potrebbe avercela con lui? Non capisco proprio cosa sia potuto accadere... È tutto così strano... e spaventoso...";
			link.l1 = "Non temete, Madame Lea. Salpo subito. Son certo che vostro marito sia sano e salvo. Ve lo riporterò tra le braccia, ve lo prometto. Tenete duro.";
			link.l1.go = "Return Lea Exit";
		break;

		case "Return back to Lea":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Capitano, vi prego—avete qualche notizia? Avete scoperto qualcosa? Qualunque cosa, vi supplico?";
			link.l1 = "Non ancora, temo. Ma continuo a cercare, Lea!";
			link.l1.go = "Exit";
		break;
		
		case "Return Lea Exit":
			DialogExit();
			npchar.dialog.currentnode = "Return back to Lea";
			AddQuestRecord("VPVL", "2"); 
			DoQuestCheckDelay("VPVL_Start", 0.1);
		break;
		
		case "Rejection":
			DialogExit();
			npchar.dialog.currentnode = "Rejection1";
			SetTimerCondition("VPVL_ClearLea", 0, 0, 2, false);  // Удаляем Леа через 2 дня
			CloseQuestHeader("VPVL");
		break;
		
		case "Rejection1":
			dialog.text = "Che altro vuoi da me? Non ti sei già divertito abbastanza a prenderti gioco di una povera donna?";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;

		case "Lea second talk":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Capitano! Pierre! Oh, quanto son felice di vedervi! L’avete trovato!";
			link.l1 = "Madame Lea, permettetemi di presentarvi Pierre Carno, in carne ed ossa. Non posso dire che sia uscito indenne, ma non dubito che le vostre cure lo rimetteranno presto in sesto.";
			link.l1.go = "Lea second talk1";
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
		break;

		case "Lea second talk1":
			dialog.text = "Pierre! Santa Vergine Maria! Ero in pena per te, mi hai fatto consumare dall’angoscia! Dove sei stato? Hai la faccia di cera... così pallido... Oh! Ma cos’è questo?! Queste ferite orribili?! Tagli... e ustioni...";
			link.l1 = "Taci ora, gioiello del mio cuore. Sono solo graffi, svaniranno col tempo. Rivedere il tuo volto... era tutto ciò che desideravo. Se non fosse stato per il Capitano... Gli devo "+GetSexPhrase("lui","lei")+" la mia stessa vita.";
			link.l1.go = "Lea second talk2";
			CharacterTurnByChr(npchar, CharacterFromID("VPVL_Pier_carno"));
			sld = CharacterFromID("VPVL_Pier_carno");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_Lea_girl"));
			locCameraFromToPos(-7.62, 3.1, 83.26, false, 30, -15, 0);
		break;

		case "Lea second talk2":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Capitano... Io... non so nemmeno come ringraziarvi... l'avete trovato! Avete salvato il mio Pierre! Grazie... grazie di cuore per tutto! Che il Signore vegli sempre su di voi, "+GetSexPhrase("Monsieur","Mademoiselle")+" Capitano!";
			link.l1 = "Su, su, basta così. Quello che davvero serve a Pierre è un pasto caldo e un buon sonno, per mille balene.";
			link.l1.go = "Exit";
			CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
			AddDialogExitQuest("VPVL_PierTalkOnThePirs");
		break;
		
		//////   Контры   //////
		
		case "Kontr Le Maren":
			dialog.text = "Maledizione! Alla fine ti fai vedere, "+GetSexPhrase("maledetto cane rognoso","maledetta sgualdrina")+"Dove diavolo sei stato? Son tre giorni che arrostiamo su questa maledetta spiaggia! Dov’è il nostro carico?!";
			link.l1 = "A quanto pare la baldoria non può iniziare senza di me, eh, signori? Be’, forse avrò fatto un po’ tardi—ma meglio arrivare con la marea che restare a secco!";
			link.l1.go = "Exit_Sneak";
			link.l2 = "Ti rivolgi a me, eh? Forse impara un po’ di buone maniere prima di sbraitare domande come una ciurma di topi di sentina!";
			link.l2.go = "Exit_Lucky";
			//locCameraFromToPos(-3.35, 2.23, 6.93, false, 20, -1, 10);
			locCameraFromToPos(-5.73, 2.45, 5.75, true, -0.53, 0.40, 7.17);
			DeleteAttribute(pchar, "questTemp.VPVL_Contr_V_Lemaren");
		break;
		
		case "Exit_Sneak":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Sneak", 50);
			notification("Experience gained", SKILL_SNEAK);
		break;
		
		case "Exit_Lucky":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			notification("Experience gained", SKILL_FORTUNE);
		break;

		case "Kontr Le Maren0":
			sld = CharacterFromID("VPVL_contr_2");
			dialog.text = ""+sld.name+", maledetto cozzo di scoglio! Apri quegli occhi da pesce lesso, stolto—questo non è affatto il nostro contatto!";
			link.l1 = "Argh... Un altro cagnolino del governatore! Sicuro come l’alta marea! Da quando "+GetSexPhrase("quel mascalzone","questa sciocca ragazza")+" trascinato "+GetSexPhrase("se stesso","lei stessa")+" qua, issiamo le vele "+GetSexPhrase("lui","lei")+" alla grotta con l'altro topo. Vedrai che ti faremo vedere noi "+GetSexPhrase("lui","lei")+" come strappiamo i segreti—presto sputeranno ogni lurido piano che il loro padrone abbia mai sognato!";
			link.l1.go = "Kontr Le Maren1";
			locCameraFromToPos(-3.40, 2.38, 5.79, true, -0.49, 0.5, 7.59);
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_1"));
			
			sld = CharacterFromID("VPVL_contr_1");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_2"));
		break;
		
		case "Kontr Le Maren1":
			dialog.text = "Che turpi fantasie ribollono nella tua testa, bestia inzuppata di mare? Smettila di sbavare! Meglio venderla a... sai tu chi. Quello ci sgancerà uno scrigno d’oro per una donzella così, e noi scialeremo tra vino e puttane per un mese intero!";
			if (pchar.sex == "man")
			{
				dialog.text = "Che razza di dannazione ci serve un altro mozzo a intasare la nostra stiva? Stringi di più col suo compare—canterà come un gabbiano all’alba. Quanto a questo qui, sventriamolo qui e ora, così ci risparmiamo la fatica di rivedere la sua faccia!";
			}
			link.l1 = "Mille squali affamati ti rodano le viscere, Simone! Sei il contrabbandiere più furbo di tutto l’arcipelago!";
			link.l1.go = "Kontr Le Maren2";
		break;

		case "Kontr Le Maren2":
			dialog.text = "...";
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) >= 20)
			{
				if(GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE) == "") {
					notification("No pistol equipped", "NONE");
					link.l2 = "Se quella testa di cozze è la tua lama più affilata, temo di immaginare quali fesserie frullino nelle teste degli altri!";
					link.l2.go = "Kontr Le Maren3";
					CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
					//locCameraFromToPos(-3.35, 2.23, 6.93, false, 20, -1, 10);
					sld = CharacterFromID("VPVL_contr_1");
					CharacterTurnByChr(sld, CharacterFromID("Blaze"));
				}
				else
				{
					link.l1 = "(Tra me e me)(Pistole) Mentre questi ratti di mare ciarlano con le loro fandonie, ho l’occasione di colpire rapido e deciso, come un fulmine a ciel sereno.";
					link.l1.go = "murder";
					notification("Check passed", SKILL_PISTOL);
					locCameraFromToPos(-5.73, 2.45, 5.75, true, -0.53, 0.40, 7.17);
				}
			}
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) < 20)
			{
				notification("Skill too low (20)", SKILL_PISTOL);
				CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
				sld = CharacterFromID("VPVL_contr_2");
				CharacterTurnByChr(sld, CharacterFromID("Blaze"));
				locCameraFromToPos(-5.73, 2.45, 5.75, true, -0.53, 0.40, 7.17);
			}
			link.l2 = "Se quella testa di cozze è la tua lama più affilata, temo solo d'immaginare quali sciocchezze frullino nei crani degli altri!";
			link.l2.go = "Kontr Le Maren3";
		break;
		
		case "Kontr Le Maren3":
			dialog.text = "Ti strapperò quella lingua insolente dal cranio, cane sfacciato!"+GetSexPhrase("","—puttana lurida")+", e lo darò in pasto ai gabbiani così non proferirai più parola!";
			link.l1 = "Fatti avanti, vuoi? Vieni allora, se hai il fegato di ballare col diavolo.";
			link.l1.go = "Kontr Le Maren Fight";
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
		break;
		
		case "Kontr Le Maren Fight":
			DialogExit();
			AddDialogExitQuest("VPVL_EveryoneFight");
			LAi_LocationFightDisable(&Locations[FindLocation("Shore39")], false);
			EndQuestMovie();
		break;
		
		case "murder":
			DialogExit();
			AddDialogExitQuest("VPVL_Pistol_Murder");
			locCameraFromToPos(-5.04, 2.62, 8.65, false, 20, -6, -15);
		break;
		
		/////////////   Пьер Карно   /////////////
		
		case "PierFirstTalk":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+"... Perdonami... La mia testa è confusa... Sei venuto a finire ciò che hanno iniziato?";
			link.l1 = "Sei tu Pierre Carno?";
			link.l1.go = "Pier_1";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.VPVL_SetFlagLeMaren");
		break;

		case "Pier_1":
			dialog.text = "Aye, sono io. Ma come diavolo conosci il mio nome?";
			link.l1 = "Ma certo. Altrimenti, che ci farei qui?";
			link.l1.go = "Pier_2";
		break;

		case "Pier_2":
			dialog.text = "Perdonami, non capisco nulla... Il dolore e la fame mi hanno tolto il senno... Perché sei venuto?";
			link.l1 = "È semplice. Da quando sei sparito, la tua devota moglie veglia sul molo, gli occhi sempre rivolti alla vela del Cormorano. Il suo dolore mi ha trafitto così a fondo che non potevo passar oltre senza far nulla—ho deciso di mettermi sulle tue tracce.";
			link.l1.go = "Pier_3";
		break;

		case "Pier_3":
			dialog.text = "Mia moglie... la mia adorata Léa... ero certo che non l’avrei mai più rivista...";
			link.l1 = "Quella marea è ormai passata. Ti aspetta al molo, aggrappata a un filo di speranza. Andiamo via da qui. Prendi il mio braccio.";
			link.l1.go = "Pier_4";
		break;

		case "Pier_4":
			dialog.text = "Pietà... "+GetSexPhrase("Monsieur","Mademoiselle")+"... Ho bisogno di riprendermi un attimo... le gambe mi reggon come travi marce... Grazie, davvero. Se non fosse stato per te... pare che l’Onnipotente ti abbia mandato in persona... Non mi hai detto il tuo nome. Come dovrei chiamare il mio salvatore?";
			link.l1 = "Capitano "+GetFullName(pchar)+"   Mentre ti rimetti in forze, raccontami come sei finito in questo posto. Facevi affari con questi... gentiluomini?";
			link.l1.go = "Pier_5";
			LAi_Fade("VPVL_PierStay", "");
		break;

		case "Pier_5":
			dialog.text = "Santissimi no, Capitano. Sono solo un umile pescatore. La giornata era iniziata così bene. Pescavo lungo la riva occidentale—il bottino era incredibile.\nEro impaziente di mettere il pesce nei barili e gettare di nuovo le reti, ma non mi accorsi della corrente che trascinava la barca verso la scogliera. Lo scafo era sottile come un guscio d’uovo—un colpo solo bastò a far entrare il mare. Il Cormorano, appesantito dalla pesca del mattino, affondò in un lampo.";
			link.l1 = "Allora sei riuscito a sbarcare, solo per essere scambiato dai contrabbandieri per una delle spie del governatore?";
			link.l1.go = "Pier_6";
		break;

		case "Pier_6":
			dialog.text = "Proprio così. Sono arrivato a malapena a riva, sballottato dalle maledette onde. Avevo solo bisogno di asciugarmi e riprendere fiato prima di andare in città. Poi, quei diavoli sono spuntati dal nulla.\nMi hanno dato un’occhiata e hanno deciso subito che fossi una spia. Non ho fatto in tempo ad aprir bocca che già mi avevano legato e trascinato fin qui. Mi hanno lasciato senza cibo e torturato per due giorni, cercando di farmi confessare cose che non ho mai saputo—agenti, piani... ma io non sapevo proprio nulla!";
			link.l1 = "Di cervello ne avevano poco, quei poveracci—ecco perché ora danno da mangiare ai granchi. Ma tutto questo è acqua passata. Sei libero, finalmente. È ora di ricongiungerti a tua moglie—sarà già in preda alla disperazione, scommetto.";
			link.l1.go = "Pier_7";
		break;

		case "Pier_7":
			dialog.text = "Tutto ciò che desidero è stringerla di nuovo tra le braccia. Credo... credo di poter camminare adesso.";
			link.l1 = "Allora non perdiamo altro tempo.";
			link.l1.go = "exit_grot";
		break;
		
		case "exit_grot":
			DialogExit();  
			AddQuestRecord("VPVL", "4");
			AddDialogExitQuest("VPVL_PierFollow");
		break;
		
		case "PierInThePirs":
			dialog.text = "Capitano, vi supplico—venite domani sera in taverna al suono delle sei campane. La mia coscienza non troverebbe mai pace se non vi ringraziassi come si deve. In questo momento... non trovo le parole per esprimere ciò che sento nel cuore. Vi prego, venite. Per me significherebbe moltissimo.";
			link.l1 = "Va bene, Pierre. Non temere—ci sarò.";
			link.l1.go = "GoHome";
			locCameraFromToPos(-8.28, 3.1, 82.93, false, 40, -15, 0);
		break;

		case "GoHome":
			DialogExit();
			AddQuestRecord("VPVL", "5");
			AddDialogExitQuest("VPVL_KarnoGoHome");
		break;

		case "PierTalkTavern":
			dialog.text = "Capitano! Siete arrivato! Vi prego, sedetevi con me!";
			link.l1 = "Con piacere!";
			link.l1.go = "PierTalkTavern1";
			LAi_Fade("VPVL_SitOnTheTable", "");
			FreeSitLocator("FortFrance_Tavern", "sit6");  // Just in case
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			pchar.questTemp.VPVL_DontSpawnSmugglersShipPier = true;
			DelLandQuestMark(npchar);
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
		break;

		case "PierTalkTavern1":
			dialog.text = "Leviamo i nostri boccali alla tua fortuna e salute duratura!";
			link.l1 = "Non solo alla mia, Pierre, ma anche alla tua. Hai un’aria assai migliore di quando t’ho raccolto in quella spelonca maledetta. Alla salute!";
			link.l1.go = "PierTalkTavern2";
		break;

		case "PierTalkTavern2":
			dialog.text = "Capitano, non saprei mai ringraziarvi abbastanza! Non mi avete ignorato, non mi avete voltato le spalle—avete aiutato un perfetto sconosciuto, un povero pescatore. Un gesto così nobile merita una degna ricompensa, e desidero donarvi tutto ciò che possiedo.\nEcco—venti pezzi d’ambra dorata come il sole e cinque rare pietre blu, recuperate da un relitto sommerso. Ora sono vostri.\nE inoltre, voglio che prendiate i miei strumenti di navigazione e l’attrezzatura. Non ho più nave, quindi a me non servono più.";
			link.l1 = "Grazie, Pierre. Questi saranno davvero utili. Ma la cosa più importante è che sei tornato a casa—e tua moglie non dovrà più vivere nella paura. La sorte cambierà per entrambi, vedrai.";
			link.l1.go = "PierTakeGift";
			link.l2 = "Pierre, apprezzo il gesto, ma dovresti tenerli tu. Ti servirà ogni moneta per rattoppare la tua barca, comprare attrezzi, reti, barili... Il tuo ringraziamento—e vedervi riuniti, tu e tua moglie—è già una ricompensa più che sufficiente. Abbiate cura l’uno dell’altro.";
			link.l2.go = "PierWontGift1";
		break;
		
		case "PierTakeGift":
			dialog.text = "Ancora non riesco a credere che tutto ciò sia davvero accaduto... Beviamo a un nuovo capitolo nella vita della mia famiglia—e al tuo nobile cuore, Capitano!";
			link.l1 = "Alla buona sorte, Pierre. Un po’ di fortuna non guasta mai a nessuno di noi!";
			link.l1.go = "ZastavkaVPVL";
			AddItems(PChar, "jewelry8", 20);
			AddItems(PChar, "jewelry7", 5);
			AddItems(PChar, "A_map_martiniqua", 1);
			AddItems(PChar, "spyglass3", 1);
			AddItems(PChar, "obereg_7", 1);
		break;

		case "PierWontGift1":
			dialog.text = "Capitano, non posso lasciar correre così... Mi hai salvato la vita, e ti devo tutto. Dal momento che rifiuti l’ambra e gli altri doni, permettimi almeno d’insegnare ai tuoi uomini come pescare nei bassi fondali. Li terrà sazi e alleggerirà il tuo borsello quando toccherà fare provviste. Che ne dici?";
			link.l1 = "Ora questa sì che è un'idea brillante! Come dice il vecchio detto—insegnagli a gettar la rete, e non patiranno mai la fame.";
			link.l1.go = "PierWontGift2";
			pchar.questTemp.VPVL_Food = true;
		break;

		case "PierWontGift2":
			dialog.text = "Parole sagge, Capitano! Son lieto d’esser d’aiuto. Allora—che ne dici d’un altro sorso insieme?";
			link.l1 = "Alla tua salute e prosperità, Pierre!";
			link.l1.go = "ZastavkaVPVL";
		break;
		
		case "ZastavkaVPVL":
			DialogExit();
			SetLaunchFrameFormParam("Four hours have passed...", "VPVL_SitOnTheTable", 2, 2);
			LaunchFrameForm();
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
			sld = CharacterFromID("VPVL_Pier_carno");
			sld.dialog.currentnode = "PierTalkTavern3";
			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, sld, "", -1, 0);
		break;
		
		case "PierTalkTavern3":
			if(CheckAttribute(pchar, "questTemp.VPVL_Food"))
			{
			int foodDays = CalculateShipFood(&pchar);
			dialog.text = "Per la barba di Nettuno! Questa sì che è una ciurma di grog! Un altro sorso o due e... hic... canterò una ballata da svegliare il kraken! Ogni anima dalla taverna al porto sentirà la mia voce!";
			link.l1 = "Molla quella ballata per acque più tranquille, Pierre. Risparmia la voce per... hic... il prossimo porto. Se ti metti a starnazzare, finirò anch'io a gorgheggiare in men che non si dica. E ho... ehm... faccende urgenti che reclamano la mia attenzione. La marea non aspetta nessuno... hic... nemmeno chi ha il vento nei boccali! Tieniti al riparo dalle burrasche... hic... e pure quella tua brava donna!";
			link.l1.go = "PierTalkTavern4";
			WaitDate("", 0, 0, 0, 4, 10);
			LAi_AlcoholSetDrunk(pchar, 71, 5600);
			notification("Ship's provisions consumption reduced by 15%", "None");
			}
			else
			{
			dialog.text = "Per la barba di Nettuno! Questo grog è micidiale! Un altro sorso o due e... hic... canterò una ballata che farà svegliare il kraken! Ogni anima dal qui al porto sentirà la mia voce!";
			link.l1 = "Risparmia quei canti per acque più tranquille, Pierre. Tieni la voce per... hic... il prossimo porto dove metteremo piede. Se ti metti a strillare, finirò per unirti al coro prima di subito. E ho... ehm... affari urgenti che reclamano la mia attenzione. La marea non aspetta nessuno... hic... nemmeno chi ha il vento dentro la bottiglia! Naviga sempre con il sole in poppa... hic... e porta in salvo anche quella tua brava donna!";
			link.l1.go = "PierTalkTavern4";
			WaitDate("", 0, 0, 0, 4, 10);
			LAi_AlcoholSetDrunk(pchar, 71, 5600);
			}
		break;

		case "PierTalkTavern4":
			dialog.text = "Arr, Capitano... hai il cuore di un... hic... vero lupo di mare, tu sì! Il mio debito con te non potrà mai esser saldato, mi senti? Se mai getterai ancora l’ancora nel nostro porto... il nostro focolare... il nostro focolare sarà tuo come fossi nato dalla stessa... stessa madre! Sulla mia anima e il mio onore! Brinderemo insieme ancora quando la Fortuna ti riporterà su queste rive!";
			link.l1 = "Avanti piano, Pierre! È meglio che... hic... molli l’ancora prima che le mie gambe da marinaio diventino gelatina e mi ritrovi alla deriva sul pavimento di questa taverna! Che venti propizi gonfino le tue vele!";
			npchar.dialog.currentnode = "RepeatTavern";
			link.l1.go = "Exit2";
			CloseQuestHeader("VPVL");
		break;

		case "Exit2":
			DialogExit();
			LAi_Fade("VPVL_ExitFromTableVPVL", "VPVL_PierLivingTavern");
			DeleteAttribute(pchar, "questTemp.VPVL_Delete_Ship_RemoveFlag");
		break;

		case "RepeatTavern":
			dialog.text = "Ooooh, il gran mar blu profondo-o-o, e i venti dell’aliseo... hic... verso i banchi da pesca salpiam all’alba!.. Maledetti questi cervelli inzuppati di rum! Le strofe mi sfuggon di mente! Capitano!.. Ancora all’ancora, eh? Oste! Porta qui... hic... il miglior spirito delle Indie Occidentali nascosto in cantina!";
			link.l1 = "Mollo gli ormeggi, Pierre! Hic... finché riesco ancora a navigare il sentiero infido verso la mia nave senza schiantarmi sugli scogli!";
			link.l1.go = "Exit";
		break;

		case "MeetingInTneCity":
			dialog.text = ""+pchar.name+"! Una vista gradita per questi occhi segnati dal sale! Che ne dici di un sorso del miglior spirito dei Caraibi? Per celebrare l’incrocio delle nostre rotte su questo vasto oceano della vita!";
			link.l1 = "Anche il tuo volto segnato dal tempo mi rallegra il cuore, Pierre. Ma, ahimè, il dovere oggi mi impone la sobrietà. La mia rotta mi conduce fra acque infide, dove servono mente lucida e mano ferma. Forse, quando le nostre stelle torneranno a incrociarsi?";
			link.l1.go = "MeetingInTneCity1";
		break;

		case "MeetingInTneCity1":
			dialog.text = "Ayou, ayou, Capitano! Una nave va condotta prima d’attraccare. Prima i registri, poi lo svago, come dicono i mercanti. Ma quando la Sorte girerà la sua ruota in nostro favore, brinderemo come il vecchio Barbanera stesso avrebbe voluto!";
			link.l1 = "Segnalo nel diario di bordo, Pierre. Fino a quando le maree ci riuniranno ancora una volta!";
			link.l1.go = "Exit";
			npchar.dialog.currentnode = "ExitRepeat";
		break;

		case "ExitRepeat":
			dialog.text = "Capitano! La vostra nave ha trovato rifugio sicuro dalla tempesta degli obblighi?";
			link.l1 = "La marea del commercio ancora mi trattiene all’àncora, Pierre. I miei doveri mi tengono legato al timone per un altro poco.";
			link.l1.go = "Exit";
		break;
	}
}   
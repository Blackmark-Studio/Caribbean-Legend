// диалог прочих и малозначимых НПС
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp;
	string attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Serve qualcosa, messere?";
			link.l1 = "No, non adesso.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> матрос на корабле, прибытие в Сен-Пьер
		case "Startsailor":
			dialog.text = "Maledizione, terra in vista! Svegliatevi, Monsieur... come diavolo vi chiamate... Siamo arrivati!";
			link.l1 = "A-ah! È già mattina? Che diavolo è questo caldo infernale e quest’umidità appiccicosa?";
			link.l1.go = "Startsailor_1";
			link.l2 = "Per mille fulmini! Charles de Maure! Un gentiluomo, capite. Ma come fate a bere con questo caldo? Io mi verserei dell’acqua, per l’amor del cielo.";
			link.l2.go = "Startsailor_1a";
		break;
		
		case "Startsailor_1":
			dialog.text = "Abituatevi, Monsieur. Questo è l’unico tempo che abbiamo qui... e potrebbe sempre andare peggio.";
			link.l1 = "Come potrebbe andare peggio!? Indosso solo una camicia di lino e ho il sudore che mi cola lungo la schiena!";
			link.l1.go = "Startsailor_2";			
		break;
		
		case "Startsailor_2":
			dialog.text = "Vedrai, ahah! Potrebbe essere la stagione degli uragani! Sbrigati, monsieur. La scialuppa non ti aspetterà. Non vorrai mica nuotare fino alla Martinica, vero?";
			link.l1 = "Concedimi solo un attimo, vuoi? Dov'è la mia spada? Ah, eccola...";
			link.l1.go = "Startsailor_3";			
		break;
		
		case "Startsailor_3":
			dialog.text = "Non sei più in Europa... Stai in campana, Monsieur. Son tempi burrascosi, questi. Dicono che la Compagnia delle Isole Americane abbia venduto l’isola di Martinica a dei fanatici religiosi, crociati o qualche altra follia del genere. Io per ora non ho visto nulla di strano, almeno sbirciando la costa dalla tolda. Ma siam stati lontani un bel pezzo, e chissà cosa sarà cambiato mentre non c’ero.";
			link.l1 = "Crociati? Sciocchezze!";
			link.l1.go = "Startsailor_4";			
		break;
		
		case "Startsailor_4":
			dialog.text = "Sciocchezze o no, le voci corrono ovunque. Abbiamo già grane fino al берег. Cannibali nella giungla, febbri tropicali, filibustieri, furfanti tra i vicoli – e non parlo nemmeno degli spagnoli e degli inglesi...";
			link.l1 = "Oh, eccoci di nuovo... L’unico guaio che vedo ora è questo caldo infernale e le zanzare... Va bene, sono pronto. Andiamo?";
			link.l1.go = "Startsailor_5";			
		break;
		
		case "Startsailor_5":
			dialog.text = "Sali a bordo e monta sulla scialuppa, Monsieur. Benvenuto nei Caraibi!";
			link.l1 = "";
			link.l1.go = "Startsailor_6";			
		break;
		
		case "Startsailor_1a":
			dialog.text = "Non c'è altro tempo qui, 'Vostra Signoria'. Se cambia, è solo per peggiorare.";
			link.l1 = "Il clima è insopportabile, proprio come la mia compagnia in questi ultimi mesi. Spero che su questo Arcipelago ci sia almeno qualche anima decente.";
			link.l1.go = "Startsailor_2a";
			AddCharacterExpToSkill(pchar, "Leadership", 10);
		break;
		
		case "Startsailor_2a":
			dialog.text = "Ebbene, credo che saremo tutti lieti di vederti finalmente partire, monsieur. La barca ti aspetta. Non farti scappare i calzoni dalla felicità. E non scordare i tuoi effetti – la nave va oltre, e se li lasci qui, addio per sempre.";
			link.l1 = "Come se li lasciassi a te per il tuo divertimento. Peso e spada sono con me: pare che non mi abbiano derubato.";
			link.l1.go = "Startsailor_3a";			
		break;
		
		case "Startsailor_3a":
			dialog.text = "Siamo gente onesta, certo, ma fai bene a stare all’erta – tieni sempre d’occhio le tue cose, o qualcuno ti svuoterà le tasche. Proprio come nella vecchia Europa. O ovunque, davvero. Ma questo posto non è casa. Qui certi fanatici si sono sistemati. Si dice che abbiano comprato l’intera isola sottobanco. Quindi, occhi aperti e non attirare l’attenzione.";
			link.l1 = "Che sciocchezze!";
			link.l1.go = "Startsailor_4a";			
		break;
		
		case "Startsailor_4a":
			dialog.text = "Così si vocifera. Sii grato che abbia avuto la briga di avvisarti, preoccupandomi del tuo soggiorno qui. Altrimenti la tua delicata rosa guascone potrebbe appassire sotto il nostro sole rovente. Che sia verità o fandonia, tieni gli occhi aperti: di guai ne abbiamo già abbastanza senza i fanatici. Briganti nei vicoli e nella giungla, filibustieri per mare e cannibali dalla pelle rossa...";
			link.l1 = "Su, su! Me la caverò. Magari qui fa un caldo del diavolo, ma a casa mia il sole m’ha temprato, mica come quei normanni smidollati. E se c’è da risolver qualcosa a fil di spada, potete fare affidamento su di me. Ma le zanzare… ah, quella sì che è vera tortura! Beh, ho tutta la mia roba con me. Dici che la barca è pronta?";
			link.l1.go = "Startsailor_5a";			
		break;
		
		case "Startsailor_5a":
			dialog.text = "Vi attendo con impazienza. Spero che ce la facciate da solo, monsieur? Tenete alta la testa, e con un po' di fortuna non vi smarrirete. Ah, e benvenuto nell’Arcipelago, eh-eh.";
			link.l1 = "Già, grazie. L’unico sollievo è che non ci resterò a lungo.";
			link.l1.go = "Startsailor_6";
		break;
		
		case "Startsailor_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		// <-- матрос на корабле, прибытие в Сен-Пьер
		
		// горожанин знает Мишеля
		case "Benuatalker":
			DelLandQuestMark(npchar);
			link.l1 = "Mi scusate, "+GetAddress_FormToNPC(NPChar)+", potreste dirmi dove posso trovare Michel de Monper? Dev’essere da qualche parte in questa vostra città.";
            link.l1.go = "Benuatalker_1";
		break;
		
		case "Benuatalker_1":
			dialog.text = "Hmm... Vedo che sei appena sbarcato qui, visto che osi fare domande così sfrontate... Ti consiglio di smetterla, altrimenti ti caccerai nei guai. E riguardo alla tua domanda... Parla con l’Abate. Lo trovi in chiesa.";
			link.l1 = "Grazie!";
            link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddDialogExitQuest("Sharlie_SetBenua");
			QuestPointerToLoc("FortFrance_town", "reload", "reload7_back");
		break;
		
		// --> арест в резиденции
		case "Sharlie_arest":
			dialog.text = "Alt! Deponi subito le armi, Monsieur, e seguici senza fiatare!";
			link.l1 = "Che diavolo è questa roba?";
			link.l1.go = "Sharlie_arest_1";
			if (CheckCharacterItem(PChar, "knife_03")) pchar.Sharlie.KnifeMonpe = true;
		break;
		
		case "Sharlie_arest_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("FortFrance_prison", "goto", "goto9", "Puancie_InJail");
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			RecalculateJumpTable();
			RemoveAllCharacterItems(PChar, true);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "Puancie_Jail"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "FortFrance_prison", "goto", "goto13");
		break;
		// арест в резиденции
		
		// --> офицер базы
		case "Maltie_officer":
			ref location = &Locations[FindLocation(pchar.location)];
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "begin")
			{
				dialog.text = "Felice di vederti, Monsieur de Maure. Quale vento ti porta qui?";
				link.l1 = TimeGreeting()+", ufficiale. Vorrei parlare con mio fratello, Michel de Monper. Naturalmente, fuori dai registri ufficiali. Sto cercando di scoprire qualcosa sul suo servizio qui nei Caraibi.";
				link.l1.go = "spanish";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
			{
				dialog.text = "Com’è andato l’interrogatorio? Hai scoperto qualcosa di buono?";
				link.l1 = "Oh sì. Talmente tanto che porto questo spagnolo con me sulla mia nave. È un testimone importante e va consegnato a Saint-Christophe per ulteriori interrogatori.";
				link.l1.go = "spanish_10";
				break;
			}
			if (!CheckAttribute(location, "first_meeting"))
			{
				dialog.text = "Quali venti vi portano qui, Monsieur?";
				link.l1 = "Sono venuto a trovare mio fratello, Michel de Monper.";
				link.l1.go = "Maltie_officer_1";
				location.first_meeting = true;
			}
			else
			{
				dialog.text = "Monsieur, devo cortesemente ricordarvi che vi trovate in un accampamento militare. Comportatevi di conseguenza.";
				link.l1 = "Sissignore. Naturalmente.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
			
			if (SandBoxMode)
			{
				dialog.text = "Monsieur, devo ricordarvi con tutta la gentilezza che vi trovate in un accampamento militare. Comportatevi di conseguenza.";
				link.l1 = "Sì, signore. Certo.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
		break;
		
		case "Maltie_officer_1":
			DelLandQuestMark(npchar);
			dialog.text = "Michel de Monper è attualmente sorvegliato in una delle nostre casematte, rinchiuso per ordine personale del Cavaliere Philippe de Poincy. Scendi al livello inferiore. Lì troverai le casematte che usiamo come magazzini e prigioni. Sono certo che saprai orientarti.";
			link.l1 = "Grazie!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_officer";
			QuestPointerToLoc("FortFrance_Dungeon", "quest", "quest1");
		break;
		// офицер базы
		
		// --> солдаты базы
		case "Maltie_soldier":
			dialog.text = "Salute, Monsieur. Posso esservi d’aiuto in qualche faccenda?";
			link.l1 = "Grazie, soldato, ma no, sto benissimo. Continua pure.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_soldier";
		break;
		// --> солдаты базы
		
		// --> мальтиец-проводник
		case "Sharlie_maltie":
			dialog.text = "Grazie per l’attesa, Monsieur. Cercate Michel de Monper? Siete suo fratello?";
			link.l1 = "Sì, esatto. Sono suo fratello Charles. Devo vederlo immediatamente. Michel è nei guai?";
			link.l1.go = "Sharlie_maltie_1";			
		break;
		
		case "Sharlie_maltie_1":
			dialog.text = "Purtroppo è proprio così, Monsieur. Michel è rinchiuso in una delle casematte qui sotto. Il Chevalier de Poincy, Governatore Generale delle colonie francesi nel Nuovo Mondo, ha firmato di suo pugno l’ordine d’arresto. Siamo rimasti tutti sconvolti. Vostro fratello rappresenta la virtù virile, la disciplina e il coraggio, è l’orgoglio del nostro Ordine! E la cosa peggiore è che proprio noi, suoi amici, dobbiamo tenerlo dietro le sbarre come un volgare malfattore! Facciamo tutto il possibile per rendergli la prigionia meno dura, ma... una prigione resta sempre una prigione.";
			link.l1 = "Di cosa lo accusano? Ha forse commesso un misfatto?";
			link.l1.go = "Sharlie_maltie_1_1";			
		break;
		
		case "Sharlie_maltie_1_1":
			dialog.text = "L’ufficio del Governatore Generale ha accusato Michel di appropriazione indebita! Che assurdità! Tutti noi qui siamo certi che sia una mossa politica. Ti confido una cosa: Michel partecipava a certe azioni segrete per conto dell’Ordine. Forse ha scoperto più del dovuto. O, peggio, ha fatto arrabbiare qualche potente. Ma rubare denaro? Nessuno ci crede. È solo una scusa, vile e spregevole! Ma basta parole. Tuo fratello non vede l’ora di incontrarti, sono certo che ti racconterà tutto di persona.";
			link.l1 = "Bene. Dove si trova la vostra prigione?";
			link.l1.go = "Sharlie_maltie_1_2";
		break;
		
		case "Sharlie_maltie_1_2":
			dialog.text = "Nella nostra armeria sotterranea, proprio qui in città. Seguimi. Ti mostro la strada.";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2";
		break;
		
		case "Sharlie_maltie_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "FortFrance_town", "officers", "reload7_1", "Maltie_GoTown", -1);
		break;
		
		case "Sharlie_maltie_3":
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Maltie_officer"), "questmarkmain");
			dialog.text = "Eccoci qua. Questa è la nostra base d’operazioni – la Sezione dei Caraibi dell’Ordine Ospedaliero Militare di San Giovanni di Gerusalemme, di Rodi e di Malta. Le casematte sono sotto di noi. Scendi il corridoio oltre la sala da pranzo e la cappella. Le scale laggiù ti porteranno al livello inferiore. Cerca un corridoio fiancheggiato da celle. Troverai tuo fratello in una vicino in fondo.\nVai, Charles, e che Dio ti assista. Ti prego, aiuta Michel! È innocente, chiunque qui lo giurerebbe sul Vangelo.";
			link.l1 = "Tutta la ragione per cui sono venuto in questa lurida fogna è vedere mio fratello. Spero almeno di riuscire a tirarlo fuori da questo pasticcio.";
			link.l1.go = "Sharlie_maltie_4";
		break;
		
		case "Sharlie_maltie_4":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "none", -1);
		break;
		
		//belamour cle -->
		case "Sharlie_maltieA":
			dialog.text = "Così eri in cerca di Michel de Monper? E tu saresti suo fratello?";
			link.l1 = "Sì, esatto. Sono suo fratello Charles. Devo vederlo subito. Si è cacciato nei guai, vero?";
			link.l1.go = "Sharlie_maltie_1a";			
		break;
		
		case "Sharlie_maltie_1a":
			dialog.text = "Purtroppo sì, Monsieur. Michel è agli arresti e rinchiuso nella nostra prigione. Il Cavaliere de Poincy, governatore generale delle colonie francesi in persona, ha dato e firmato gli ordini. Siamo rimasti tutti sconvolti.\nVostro fratello è esempio di virilità, fermezza e coraggio, un vanto per il nostro Ordine! Il peggio è che proprio noi, i suoi compagni, dobbiamo chiudere la sua cella e sorvegliarlo come un malfattore! Facciamo quanto possiamo per alleviare la sua condizione, ma... prigione resta prigione.";
			link.l1 = "Di cosa lo accusano, dunque? Ha commesso qualche misfatto?";
			link.l1.go = "Sharlie_maltie_1_1a";			
		break;
		
		case "Sharlie_maltie_1_1a":
			dialog.text = "Bagianate! Una pura bagianata! Hanno accusato Michel di peculato e di aver rubato soldi alla Corona. Ridicolo! Siamo tutti certi che sia solo un gioco politico. Michel era coinvolto in missioni segrete dell’Ordine, forse ha scoperto più di quanto dovesse.\nO chissà cos’altro. Ma rubare soldi! Nessuno ci crede. È solo una scusa, una sporca e stupida scusa! Ma basta parole. Tuo fratello non vede l’ora di parlarti, sono certo che ti racconterà tutto lui stesso.";
			link.l1 = "Bene. Dove si trova la prigione?";
			link.l1.go = "Sharlie_maltie_1_2a";
		break;
		
		case "Sharlie_maltie_1_2a":
			dialog.text = "Si trova nella nostra base sotterranea, qui in città. Seguimi, ti mostro la strada.";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2a";
		break;
		
		case "Sharlie_maltie_2a":
			DialogExit();
			//LAi_ActorGoToLocation(npchar, "reload", "reloadPr1", "FortFrance_Dungeon", "reload", "reload1", "", -1);
			Pchar.quest.Sharlie_Maltie.win_condition.l1 = "location";
			Pchar.quest.Sharlie_Maltie.win_condition.l1.location = "FortFrance_town";
			Pchar.quest.Sharlie_Maltie.win_condition = "Maltie_GoBasement";
			QuestPointerDelLoc("FortFrance_prison", "reload", "reload1");
		break;
		//<-- cle
		// мальтиец-проводник
		
		// --> найм матросов
		case "Sharlie_sailor":
			DelLandQuestMark(npchar);
			dialog.text = "E poi si è sporgiato fuori bordo e ha vomitato così tanto che perfino i Caraibi sono diventati verdi! Ah ah ah!";
			link.l1 = "Alonso?";
			link.l1.go = "Sharlie_sailor_1";
		break;
		
		case "Sharlie_sailor_1":
			dialog.text = "Oh! Charles, stavo proprio raccontando ai ragazzi delle nostre avventure!";
			link.l1 = "L’ho notato. Ascolta, Alonso. Sono diventato capitano...";
			link.l1.go = "Sharlie_sailor_2";
		break;
		
		case "Sharlie_sailor_2":
			dialog.text = "Già? Pensavo ci volesse almeno un mese, ah ah!";
			link.l1 = "Parlo sul serio!";
			link.l1.go = "Sharlie_sailor_3";
		break;
		
		case "Sharlie_sailor_3":
			dialog.text = "Se fosse solo per me, accetterei subito. Ma ho quaranta uomini della Ulysse con me. Hanno affidato a me il loro futuro; devo essere sicuro che non li deluderai\n"+
			"Che tipo di nave avete?";
			link.l1 = "Una nave come tutte le altre, "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype), "Name")))+". È così importante?";
			link.l1.go = "Sharlie_sailor_4";
		break;
		
		case "Sharlie_sailor_4":
			dialog.text = "Sa, dopo la Ulysse preferiremmo non servire su una barca o una tartana qualsiasi. Abbiamo già visto la vostra nave e ai ragazzi piace\n"+
			"Ora, il denaro. Chiediamo 4.800 pesos in anticipo. Poi – come sempre – si divide. Nulla di esagerato, te lo assicuro. Ce la fai?";
			if (sti(Pchar.money) >= 4800)
			{
				link.l1 = "D’accordo! Ecco le vostre monete.";
				link.l1.go = "Sharlie_sailor_5";
			}
			link.l2 = "Purtroppo, al momento non ho così tanto denaro con me.";
			link.l2.go = "Sharlie_sailor_nomoney";
		break;
		
		case "Sharlie_sailor_5":
			if (GetSquadronGoods(pchar, GOOD_FOOD) < 20 || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < 30)
			{
				dialog.text = "Hai provviste nella stiva, capitano? E medicine? No? Eh, non va bene così. Vai a procurarti almeno il necessario per il viaggio e poi torna, che parleremo. Passa dallo spaccio e prendi quel che serve.";
				link.l1 = "Hm. Hai ragione. Va bene, ci penserò io.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				AddMoneyToCharacter(pchar, -4800);
				dialog.text = "Bah! Congratulazioni... Capitano! Raduno subito i ragazzi e saliamo sulla vostra nave.";
				link.l1 = "Felice di continuare la nostra avventura, Alonso. Prepara la nave per salpare!";
				link.l1.go = "Sharlie_sailor_6";
			}
		break;
		
		case "Sharlie_sailor_6":
			DialogExit();
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "Fortfrance_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
			SetCrewQuantityOverMax(PChar, 40);
			pchar.Ship.Crew.Morale = 50;
			pchar.Ship.Crew.Exp.Sailors = 50;
			pchar.Ship.Crew.Exp.Cannoners = 50;
			pchar.Ship.Crew.Exp.Soldiers = 50;
			AddQuestRecord("Sharlie", "7");
			pchar.questTemp.Sharlie = "skiper";
			DeleteAttribute(pchar, "GenQuest.CannotWait");//снимаем запрет, если не был снят раньше
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		case "Sharlie_sailor_nomoney":
			dialog.text = "Ebbene, appena trovi abbastanza soldi, torna pure qui. Ci troverai nella taverna. Tanto navi nei paraggi non ce ne sono, ah! Noi intanto continueremo a bere e a dilapidare i nostri scudi tra vino e puttane, ahaharr!";
			link.l1 = "Cercherò di tornare il prima possibile.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Sharlie_sailor_again";
		break;
		
		case "Sharlie_sailor_again":
			dialog.text = "Sei tornato, capitano? Pronto ad arruolar me e i miei compagni? Le nostre borse si stanno facendo leggere, sentiamo il bisogno di respirare ancora una volta la brezza del mare!";
			if (sti(Pchar.money) < 4800)
			{
				link.l1 = "Non ancora, sto ancora mettendo tutto in ordine.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				link.l1 = "Sì. Prendi il tuo anticipo. Ora sei al mio servizio.";
				link.l1.go = "Sharlie_sailor_5";
			}
		break;
		// найм матросов
		
		// наводчик на штурмана
		case "skipertalker":
			DelLandQuestMark(npchar);
			dialog.text = LinkRandPhrase("Ahoy capitano! Che vi serve?","Salve, signor mio. In che posso servirla?","Buongiorno. Che cosa desideri?");
			link.l1 = RandPhraseSimple("Ho una domanda per te.","Mi serve qualche informazione su questa colonia.");
			link.l1.go = "skipertalker_1";
			link.l2 = "Solo un saluto. Au revoir!";
			link.l2.go = "exit";
			NextDiag.TempNode = "skipertalker";
		break;
		
		case "skipertalker_1":
			dialog.text = RandPhraseSimple("Che c’è?","Di che hai bisogno?");
			link.l1 = "Ascolta, "+GetAddress_FormToNPC(NPChar)+"... senti, la questione è questa... sto cercando un nocchiere. Forse conosci qualcuno adatto per il mestiere qui in città?";
			link.l1.go = "skipertalker_2";
		break;
		
		case "skipertalker_2":
			dialog.text = "Un navigatore, dici? Mh. Beh, ne conosco uno... Ma c’è un impiccio: è rinchiuso in galera, per debiti. Il poveraccio marcisce nelle segrete già da quasi un mese, finché lui o qualcun altro non salda quel che deve.";
			link.l1 = "Un debitore? Hmm... Come si chiama?";
			link.l1.go = "skipertalker_3";
		break;
		
		case "skipertalker_3":
			dialog.text = "Si chiama Folke Deluc. Chiedi al comandante della prigione se vuoi vederlo. Ma dubito che lo lascino uscire di lì, a meno che tu non paghi il suo debito, perché lui di certo non lo farà, ahahah!";
			link.l1 = "Forse lo farò. Grazie per l’informazione, amico.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie = "jailskiper";
			AddQuestRecord("Sharlie", "8");
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", false);
			SetFunctionLocationCondition("FortfranceJailOff_AddQuestMark", "fortfrance_prison", false);
		break;
		
		// --> штурман
		case "Folke":
			dialog.text = "A che debbo un tal onore, Monsieur?";
			link.l1 = "Ciao, Folke. La faccenda è semplice: ho una nave, ma mi manca un bravo navigatore. E ne ho bisogno come dell’aria. Così ho riscattato i tuoi debiti...";
			link.l1.go = "Folke_1";
		break;
		
		case "Folke_1":
			dialog.text = "Mi stai dicendo che mi hai trascinato fuori di qui solo per arruolarmi tra i tuoi uomini?";
			link.l1 = "Esatto. Credo che presto mi ripagherai fino последнего doblone speso su di te. Beh... vedremo come andrà a finire.";
			link.l1.go = "Folke_2";
		break;
		
		case "Folke_2":
			dialog.text = "La mia gratitudine, Monsieur. Di questa lurida cella umida ne ho fin sopra i capelli. Sarebbe un vero piacere tornare a bordo, ancora una volta. Ah, il mare...";
			link.l1 = "Sono lieto che ci siamo capiti, Folke. Un'ultima cosa: oltre a manovrare una nave, hai qualche altra abilità?";
			link.l1.go = "Folke_3";
		break;
		
		case "Folke_3":
			dialog.text = "Un po' di tutto, capitano. Ho servito su una nave corsara della Compagnia Olandese delle Indie Occidentali. Lì ho imparato l’arte dei cannoni, quindi posso fare da ufficiale d’artiglieria se vi fa comodo. Mercanteggiare e gli abbordaggi non sono proprio il mio forte.";
			link.l1 = "Grazie per aver condiviso, ora seguimi alla nave. Voglio che tu sorvegli l’equipaggio con il tuo occhio esperto mentre si prepara per la partenza. Poi, desidero salpare per Guadalupa quanto prima.";
			link.l1.go = "Folke_4";
		break;
		
		case "Folke_4":
			dialog.text = "Ai tuoi ordini, capitano! Ti aspetto nella tua cabina. *Usa il menu delle azioni mentre sei in mare per accedere alla cabina e ad altre zone della nave*";
			link.l1 = "Grazie, Folke. Ci vediamo a bordo.";
			link.l1.go = "Folke_5";
			Log_Info("You have received amulet 'Merchant's Rosary'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_8");
			if(CheckAttribute(pchar,"systeminfo.tutorial.Amulet"))
			{
				DoQuestFunctionDelay("Tutorial_Amulet", 0.1);
			}
		break;
		
		case "Folke_5":
			DialogExit();
			EndQuestMovie();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			AddQuestRecord("Sharlie", "10");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_skiper.win_condition.l1 = "location";
			pchar.quest.Sharlie_skiper.win_condition.l1.location = "My_Cabin_Small";
			pchar.quest.Sharlie_skiper.function = "Sharlie_SkiperTalk";
			//прерывание на засаду пиратов - принудительный квест
			pchar.quest.Sharlie_seabattle.win_condition.l1 = "location";
			pchar.quest.Sharlie_seabattle.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_seabattle.function = "SharlieSeabattle_agent";
			
			pchar.quest.NewGameTip2.win_condition.l1 = "location";
			pchar.quest.NewGameTip2.win_condition.l1.location = "Martinique";
			pchar.quest.NewGameTip2.function = "ShowNewGameTip";
			pchar.quest.NewGameTip2.text = "Your first officer is waiting for you. Use the action menu (ENTER) to go to the cabin.";
		break;
		
		case "Folke_6":
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин 250912
			dialog.text = "Una bella lugger, capitano! Una nave niente male, con sartie solide e legni robusti. Con una barca così, non solo arriveremo sani e salvi a Guadalupa, ma potremmo anche scorazzare per tutti i Caraibi, se ci va.";
			link.l1 = "Eccellente. Almeno non ho buttato via i miei soldi per una carretta che fa acqua... Hai qualche consiglio prima che molliamo gli ormeggi, Folke?";
			link.l1.go = "Folke_8";
		break;
		
		case "Folke_7":
			dialog.text = "Maledizione, questa goletta fa acqua da tutte le parti, capitano. Ci andrà di lusso se riusciremo ad arrivare fino alla Guadalupa. Se vuoi mettere piede intero a Basse-Terre, bisognerà portarla subito in darsena per le riparazioni.";
			link.l1 = "Non avevo scelta, questa era l’unica nave in vendita! E me l’hanno fatta pagare a peso d’oro. Come ben sai, ora non abbiamo tempo per sistemarla... Hai qualche consiglio prima che salpiamo?";
			link.l1.go = "Folke_8";
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_BALLS) >= 80) && (GetSquadronGoods(pchar, GOOD_GRAPES) >= 80) && (GetSquadronGoods(pchar, GOOD_KNIPPELS) >= 80) && (GetSquadronGoods(pchar, GOOD_BOMBS) >= 80) && (GetSquadronGoods(pchar, GOOD_POWDER) >= 180);
		case "Folke_8":
			if (bOk)
			{
				dialog.text = "Ebbene, capitano, avete davvero fatto scorta di munizioni a sufficienza. Polvere e palle basteranno per le nostre necessità. Non dimenticate solo di rifornirvi quando servirà.";
				link.l1 = "Ebbene, questo è ovvio. Altri commenti, gentaglia?";
				link.l1.go = "Folke_10";
				if (CheckCharacterItem(PChar, "BoxOfBalls"))
				{
					link.l2 = "Ah! Grazie per il promemoria. Ho proprio una cassa intera di palle con me!";
					link.l2.go = "Folke_8_1";
				}
			}
			else
			{
				dialog.text = "Non abbiamo abbastanza munizioni in cambusa, capitano. Dobbiamo avere almeno cento palle di cannone, palle a catena e bombe, oltre a cento sacchi di mitraglia e duecento barili di polvere da sparo. Procurati tutto il necessario, capitano. Non costerà una fortuna, ma ci salverà la pelle se ci assalgono pirati o spagnoli.";
				link.l1 = "Un investimento degno. Vado dal mercante.";
				link.l1.go = "Folke_9";
			}
		break;
		
		case "Folke_8_1":
			dialog.text = "...E da quanto tempo la portate con voi?";
			link.l1 = "Quasi due settimane.";
			link.l1.go = "Folke_8_2";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
			//AddCharacterGoodsSimple(sld, GOOD_BALLS, 10);
			Achievment_Set("ach_CL_164");
		break;
		
		case "Folke_8_2":
			dialog.text = "Ma perché, capitano?!";
			link.l1 = "Mi piace raccogliere ogni sorta di cose. Non si sa mai cosa può tornare utile.";
			link.l1.go = "Folke_8_3";
		break;
		
		case "Folke_8_3":
			dialog.text = "Peccato per voi. Queste palle non entreranno mai nei nostri cannoni giocattolo. Non ho mai visto palle così grandi. Una sola manderebbe l’Adeline a fondo.";
			link.l1 = "...";
			link.l1.go = "Folke_10";
		break;
		
		case "Folke_9":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_1";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "12");
		break;
		
		case "Folke_goods_1":
			dialog.text = "Hai finito di fare scorta di munizioni, capitano?";
			if (bOk)
			{
				link.l1 = "Sì, l'ho fatto. Hai altro da dire?";
				link.l1.go = "Folke_10";
			}
			else
			{
				link.l1 = "Non adesso, ci sto ancora lavorando.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_1";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_WEAPON) >= 50);
		case "Folke_10":
			if (bOk)
			{
				dialog.text = "Ben fatto, hai procurato abbastanza armi per l’equipaggio. Se non ne avremo a sufficienza, perderemo molti più uomini negli abbordaggi. Dio ci scampi da simile sventura. Non dimenticare di controllare spesso la quantità nella stiva.\nConviene tenere sempre qualche arma in più del necessario. Quei dannati topi adorano rosicchiare i calci e le impugnature di legno.";
				link.l1 = "Capisco. Vedo che hai ancora qualcosa da dire?";
				link.l1.go = "Folke_11";
			}
			else
			{
				dialog.text = "Non abbiamo abbastanza armi a bordo per l’equipaggio. Se non ce ne saranno a sufficienza, perderemo molti più uomini durante gli abbordaggi. Che Dio ci scampi da questa sorte. Da quel che so, hai quaranta uomini d’equipaggio.\nCompra armi a sufficienza per ciascuno, anzi, prendi anche qualche pezzo in più: cinquanta set dovrebbero bastare. Meglio averne qualcuna in riserva. Quei maledetti topi adorano rosicchiare i calci e le impugnature di legno.";
				link.l1 = "Così farò. Tornerò presto.";
				link.l1.go = "Folke_10_1";
			}
		break;
		
		case "Folke_10_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_2";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "13");
		break;
		
		case "Folke_goods_2":
			dialog.text = "Hai finito di acquistare le armi, capitano?";
			if (bOk)
			{
				link.l1 = "Le armi sono nella stiva. Vedo che hai ancora qualcosa da aggiungere?";
				link.l1.go = "Folke_11";
			}
			else
			{
				link.l1 = "Non adesso, ci sto ancora lavorando.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_2";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_FOOD) >= 100) && (GetSquadronGoods(pchar, GOOD_RUM) >= 10);
		case "Folke_11":
			if (bOk)
			{
				dialog.text = "No, credo che sia tutto. Abbiamo provviste a sufficienza, e hai pensato pure al rum per la ciurma. Hai fatto bene, ché non c’è medicina migliore per ogni male di un bel goccio fresco di rum dopo il turno. I marinai adorano e rispettano i capitani che danno la razione quotidiana di rum. Non vuoi mai sentire i tuoi uomini domandare: 'Dov’è finito il rum?'";
				link.l1 = "Possiamo salpare adesso?";
				link.l1.go = "Folke_12";
			}
			else
			{
				dialog.text = "Sì. Viveri e rum. È una vera sciagura se non hai abbastanza cibo a bordo. Tieni sempre più provviste di quanto pensi ti servirà. Non puoi mai sapere quanto durerà un viaggio – una bonaccia o una tempesta possono mandare all’aria ogni piano. Gli uomini si ammutinano o crepano di fame quando le scorte finiscono.\nIl rum non è vitale come il cibo, ma ti consiglio caldamente di averne sempre qualche botte a portata di mano, non c’è medicina migliore di un bel sorso di rum fresco dopo il turno di guardia. I marinai adorano e rispettano i capitani che non lesinano la razione giornaliera di rum.\nDunque va’ e procuraci le provviste che servono – almeno cento casse di cibo e dieci barili di rum. Non vorrai mai sentire i tuoi uomini domandare: ‘Perché il rum è finito?’";
				link.l1 = "Credo tu abbia ragione. Andrò a trovare di nuovo il mercante.";
				link.l1.go = "Folke_11_1";
			}
		break;
		
		case "Folke_11_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_3";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "14");
		break;
		
		case "Folke_goods_3":
			dialog.text = "Hai finito di comprare il nostro cibo e il rum, capitano?";
			if (bOk)
			{
				link.l1 = "Sì. Possiamo salpare adesso?";
				link.l1.go = "Folke_12";
			}
			else
			{
				link.l1 = "No, ci sto ancora lavorando.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_3";
			}
		break;
		
		case "Folke_12":
			dialog.text = "Eh già, capitano. Possiam levare l’àncora e puntare a nord, verso Guadalupa, come volevate.";
			// belamour legendary edition -->
			link.l1 = "Ottimo lavoro, Folke. Senza di te sarei stato bello fregato.";
			link.l1.go = "Folke_13";
			link.l2 = "D’accordo, mettiamoci al lavoro, vediamo se vali il prezzo che ho pagato.";
			link.l2.go = "Folke_13a";
		break;
		
		case "Folke_13a":
			Npchar.loyality = makeint(Npchar.loyality) - 5;
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			dialog.text = "Allora mettetemi al timone e prenderò il mio posto sul ponte.";
			link.l1 = "...";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_13":
			Npchar.loyality = makeint(Npchar.loyality) + 5;
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			// <-- legendary edition
			dialog.text = "Allora mettetemi come navigatore e prenderò il mio posto sul ponte.";
			link.l1 = "...";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_14":
			DialogExit();
			LAi_SetStayType(npchar);
			LAi_SetImmortal(npchar, false);
			AddQuestRecord("Sharlie", "15");
			pchar.questTemp.Sharlie = "seabattle";//в Ле Франсуа
			DeleteAttribute(pchar, "NoNavyPenalty"); // штрафуем за нехватку навигации
			
			npchar.quest.OfficerPrice = 20;
			npchar.loyality = 30;
			
			// --> копипаста LandEnc_OfficerHired
			AddPassenger(pchar, npchar, false);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			// <--
			
			pchar.questTemp.HelenDrinking.TakeFolke = true;
			
			DoQuestFunctionDelay("Tutorial_Navigator2", 1.0);
			//DoQuestFunctionDelay("Ngt_FolkeEng", 3.0);
			//NewGameTip("Welcome aboard your new officer! Press F4 to assign him as your Navigator.");
			pchar.questTemp.Sharlie.FolkeWait = true;
			LocatorReloadEnterDisable("My_Cabin_Small", "reload1", true);
			NextDiag.CurrentNode = "Folke_wait";
		break;
		
		case "Folke_wait":
			dialog.text = "Pronti a mollare gli ormeggi, capitano!";
			link.l1 = "...";
			
			if (!CheckAttribute(npchar, "navigator")) {
				dialog.text = "Capitano, mettimi al timone, altrimenti finiremo sugli scogli in men che non si dica.";
				link.l1 = "Capito, mi ci metto subito.";
			}
			
			link.l1.go = "exit";
			NextDiag.TempNode = "Folke_wait";
		break;
	
		// штурман

	// --> пират-обманщик
		case "Seabattle_pirate":
			dialog.text = "Le mie scuse. "+GetFullName(pchar)+"?";
			link.l1 = "Esatto. Quanto vi devo per questa cortesia, messere?";
			link.l1.go = "Seabattle_pirate_1";
		break;
		
		case "Seabattle_pirate_1":
			dialog.text = "Permettetemi di presentarmi - "+GetFullName(npchar)+"Mi manda Cesar Craig. Lo conoscerai senz'altro: è il padrone della taverna a Le Francois. A quanto pare, sei in partenza per Guadalupa. Vorrebbe offrirti un facile guadagno.";
			link.l1 = "Hm... Interessante! E come mai Cesar Craig è diventato così ben informato?";
			link.l1.go = "Seabattle_pirate_2";
		break;
		
		case "Seabattle_pirate_2":
			dialog.text = "È semplice, capitano. La vostra nave è l’unica che sia ancorata a Saint-Pierre in questo momento, chiunque abbia due orecchie e un occhio sa tutto su chi siete e dove ve ne andate. Qui nelle colonie le voci corron più rapide dei gabbiani. Allora, volete sentire la nostra proposta?";
			link.l1 = "Certo. Non mi tiro mai indietro davanti a qualche moneta.";
			link.l1.go = "Seabattle_pirate_3";
		break;
		
		case "Seabattle_pirate_3":
			dialog.text = "Ora sì che si ragiona, compare! Vedo che hai fiuto per gli affari. Ecco la faccenda: Cesare ha urgente bisogno che una partita di vino arrivi a Guadalupa. Duecento barili, la stiva della tua nave li regge senza problemi. Diecimila pesos per un lavoretto facile — Cesare ha fretta e la tua nave è l'unica in porto, al momento. Concorda con me: offerte così grasse non capitano spesso.";
			link.l1 = "Maledizione, diecimila pesos? Affare fatto, allora!";
			link.l1.go = "Seabattle_pirate_4";
		break;
		
		case "Seabattle_pirate_4":
			dialog.text = "Dirigiti a Le Francois e parla con Cesar. Penserà a tutto lui. Tu dovrai solo gettare l’ancora nella baia appena fuori Le Francois. Non deludermi, compare, Cesar mi ha promesso mille pesos se ti convincevo...";
			link.l1 = "Non temere, mi hai già convinto. Appena sarò pronto a partire, salperò dritto verso Le Francois.";
			link.l1.go = "Seabattle_pirate_5";
		break;
		
		case "Seabattle_pirate_5":
			dialog.text = "Hurra! Vado a prendermi il mio bottino, mille grazie, compare!";
			link.l1 = "Non c'è di che...";
			link.l1.go = "Seabattle_pirate_6";
		break;
		
		case "Seabattle_pirate_6":
			DialogExit();
			AddLandQuestMark(characterFromId("LeFransua_tavernkeeper"), "questmarkmain");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "", -1);
			AddQuestRecord("Sharlie", "11");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.location = "None";
		break;
	// пират-обманщик

	// офицер Гриффондора
		case "griffondor_officer":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;

	// командир абордажной роты по защите Сен-Пьера
		case "rosetti":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "Capitano, l’equipaggio d’abbordaggio è schierato e pronto! In attesa dei vostri ordini!";
			link.l1 = "";
			link.l1.go = "rosetti_1";
		break;
		
		case "rosetti_1":
			DialogExit();
			bDisableCharacterMenu = true;//лоченые интерфейсы
			ChangeShowIntarface();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("DefendSP_soldier_0"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Blaze");
			sld.dialog.filename = "MainHero_dialog.c";
			sld.dialog.currentnode = "SP_defend";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rosetti_2":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "Aye aye, capitano! Preparatevi, ragazzi, seguite il comandante! Su, uno-due-tre!";
			link.l1 = "";
			link.l1.go = "rosetti_3";
		break;
		
		case "rosetti_3":
			DialogExit();
			PlaySound("interface\abordage_wining.wav");
			bDisableCharacterMenu = false;//лоченые интерфейсы
			ChangeShowIntarface();
			for (i=0; i<=12; i++)
			{
				sld = CharacterFromID("DefendSP_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// прерывание на джунгли перед выходом из города
			pchar.quest.DefendSP_jungle1.win_condition.l1 = "location";
			pchar.quest.DefendSP_jungle1.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.DefendSP_jungle1.function = "DefendSP_SpainPatrol";
		break;
		
		case "spain_patrol":
			dialog.text = "Maledizione, rinforzi francesi! In formazione! Lorenzo, corri all'accampamento e dai l’allarme! Crepate, maledetti!";
			link.l1 = "...";
			link.l1.go = "spain_patrol_1";
		break;
		
		case "spain_patrol_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DefendSP_spapatrol_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "DefendSP_SpaPatrolDie");
				AddDialogExitQuest("MainHeroFightModeOn");
			}
			sld = CharacterFromID("DefendSP_spapatrol_5");
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "DefendSP_GateAlarm", -1);
		break;

	// страж истины
		case "spanish":
			dialog.text = "Capisci che non ho il permesso di diffondere simili informazioni?";
			link.l1 = "Capisci che è solo grazie al mio tempestivo intervento che St. Pierre non è stata saccheggiata dagli spagnoli? Mio fratello è sparito, abbandonando l’Ordine! Deve averlo fatto per una buona ragione. Io, in qualità di rappresentante di Sir Philippe de Poincy, ho piena autorità per indagare!";
			link.l1.go = "spanish_1";
		break;
		
		case "spanish_1":
			dialog.text = "Va bene, va bene, Monsieur de Maure. Risponderò alle tue domande. Calmati prima di tutto. Ora chiedi pure.";
			link.l1 = "Che diavolo è successo prima che Michel finisse rinchiuso sotto chiave?";
			link.l1.go = "spanish_2";
		break;
		
		case "spanish_2":
			dialog.text = "Michel de Monper stava trattando con alcuni baroni pirati per organizzare un cambio di potere a Tortuga.";
			link.l1 = "Questo già lo so. Cos'altro?";
			link.l1.go = "spanish_3";
		break;
		
		case "spanish_3":
			dialog.text = "Stava anche preparando un'altra operazione contro gli spagnoli. Per essere precisi – la cattura di una nave spagnola carica di merce preziosa. Michel doveva attirare il bersaglio sotto i cannoni della leggera fregata 'Gryffondor'. Non si fece vedere né sentire per un bel pezzo mentre tramava tutto ciò.\nMa il piano andò a rotoli. Il trasporto spagnolo non si fece vivo e Michel fu trovato dai pescatori locali, mezzo morto, trascinato dalle onde sulla spiaggia della baia di Le Marin. Pare proprio che l'impresa sia fallita.\nLa guerra è guerra, e le cose spesso vanno storte. È già un miracolo che Michel sia sopravvissuto, ma il Chevalier de Poincy cadde in una furia. Accusò Michel di aver rubato il denaro dell’Ordine e lo fece sbattere in prigione. Naturalmente, noi non abbiamo creduto a una parola di quelle accuse. Michel è un uomo onesto, un vero cavaliere dell’Ordine. Solo Dio sa cosa abbia fatto scattare il Governatore Generale. Forse il Chevalier de Poincy vorrà raccontartelo lui stesso?";
			link.l1 = "Forse.   È tutto ciò che sai?";
			link.l1.go = "spanish_4";
		break;
		
		case "spanish_4":
			dialog.text = "Sfortunatamente, non c’è altro da aggiungere. I dettagli delle operazioni di vostro fratello erano noti solo a lui e al Cavaliere de Poincy. Siamo cavalieri dell’Ordine di San Giovanni di Malta. Obbediamo ai nostri ordini.";
			link.l1 = "Se il Cavaliere si fida così tanto di Michel, dev’essere riuscito a portare a termine qualche piano segreto in passato. Sai dirmi se Michel ha mai combinato qualcosa di veramente notevole?";
			link.l1.go = "spanish_5";
		break;
		
		case "spanish_5":
			dialog.text = "Senza dubbio. Questo recente fallimento di Michel de Monper è stato anche il suo primo, perciò siamo rimasti sbalorditi dalla reazione del Cavaliere. Non molto tempo fa, la 'Gryffindor' catturò un galeone spagnolo carico d’argento proprio grazie all’ingegno di Michel. Solo quell’impresa doveva valere per decine di errori a venire. Eppure, tuo fratello è finito in catene.";
			link.l1 = "Capisco. Hai qualche idea del perché Michel sia scappato da St. Pierre?";
			link.l1.go = "spanish_6";
		break;
		
		case "spanish_6":
			dialog.text = "Sospetto che sia stato un dissidio personale tra Michel e de Poincy a portarlo in prigione. È chiaro che tuo fratello teme che il Cavaliere continuerà a perseguitarlo anche dopo la scarcerazione, così ha preso le sue precauzioni. E sai che ti dico, Monsieur de Maure? Nessuno qui gli dà torto!\nQuell’uomo ha servito l’Ordine con coraggio e, al primo inciampo, lo hanno sbattuto in una lurida cella, mezzo morto! E che fallimento era mai quello? Nessuno ci ha rimesso la pelle, nessuna nave è affondata!\nAh, e sia ben chiaro: questa chiacchiera fra noi resta tra queste mura e non la ripeterò neanche sotto tortura, intesi, Monsieur de Maure?";
			link.l1 = "Sì, signore. Ho già dimenticato questa nostra chiacchierata. Ditemi, l'attacco spagnolo a St. Pierre potrebbe essere stato provocato dall'Ordine che depredava navi spagnole? Forse proprio quel galeone d’argento di cui avete parlato? I castigliani erano dannatamente zelanti nel cercare il vostro covo...";
			link.l1.go = "spanish_7";
		break;
		
		case "spanish_7":
			dialog.text = "Ne dubito. Pochissimi sanno della presenza dell’Ordine nei Caraibi, e tutte le nostre sortite contro gli spagnoli sono state pianificate con cura. Chiedi all’ufficiale spagnolo che abbiamo catturato: ora sta raffreddando il suo bollente sangue castigliano nelle nostre segrete. L’abbiamo già interrogato. L’attacco a Saint-Pierre non era altro che una scorreria ordinaria, organizzata da un gran barone spagnolo, Ramon de Mendoza y Riba, solo per il proprio tornaconto e per spaventare le colonie francesi. Voleva pure ingraziarsi l’Escorial.";
			link.l1 = "Parlerò con questo spagnolo. Dove posso trovarlo?";
			link.l1.go = "spanish_8";
		break;
		
		case "spanish_8":
			dialog.text = "Di sotto, nella stessa cella dove tenevano tuo fratello.";
			link.l1 = "So la strada. Tornerò dopo aver interrogato lo spagnolo. Potrei avere ancora qualche domanda da farti.";
			link.l1.go = "spanish_9";
		break;
		
		case "spanish_9":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "2");
			pchar.questTemp.Guardoftruth = "prisoner";
			sld = characterFromId("spa_baseprisoner");
			LAi_CharacterEnableDialog(sld);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "spanish_10":
			dialog.text = "Beh, questa sì che è bella! Capisci bene che non posso liberare quel prigioniero, vero? Quel furfante ha guidato l’assalto a Saint-Pierre!";
			link.l1 = "Ufficiale, questo testimone è di grande importanza. L’attacco a Saint-Pierre non fu un semplice saccheggio in cerca di bottino. Don Ramon Mendosa cercava altro. Dobbiamo scoprire la vera ragione. Allora, mi consegnerai questo spagnolo, oppure dovrò chiedere il permesso direttamente a de Poincy?";
			link.l1.go = "spanish_11";
		break;
		
		case "spanish_11":
			dialog.text = "Per Dio Onnipotente... Va bene, portatelo via. Tanto stavo già per impiccare questo bastardo nella piazza di Saint-Pierre, come il pirata da strapazzo che è... Ora è affar vostro. Assicuratevi che non sfugga alla giustizia!";
			link.l1 = "Senza dubbio. Risponderò io per questo spagnolo davanti a de Poincy. Incatena questo prigioniero e portalo alla mia scialuppa, al molo della città.";
			link.l1.go = "spanish_12";
		break;
		
		case "spanish_12":
			dialog.text = "Benissimo, capitano.";
			link.l1 = "Un’ultima cosa, ufficiale. Il nome Miguel Dichoso le dice qualcosa?";
			link.l1.go = "spanish_13";
		break;
		
		case "spanish_13":
			dialog.text = "No. Non l’ho mai sentito prima. Perché lo chiedi?";
			link.l1 = "Ne sei sicuro? Dunque non hai mai incontrato nessuno con quel nome, né qui nel tuo accampamento, né al palazzo del governatore, né da nessun'altra parte a Saint-Pierre?";
			link.l1.go = "spanish_14";
		break;
		
		case "spanish_14":
			dialog.text = "No, non l’ho visto. Da dove vengo io, degli spagnoli non si parla bene.";
			link.l1 = "D'accordo. Beh, c’era da aspettarselo. Sarebbe stato troppo facile... Grazie, ufficiale! Sei stato davvero d’aiuto.";
			link.l1.go = "spanish_15";
		break;
		
		case "spanish_15":
			dialog.text = "Sei il benvenuto... Allora, che ne pensi, Monsieur de Maure, dove si trova tuo fratello adesso?";
			link.l1 = "Anch’io vorrei sapere la risposta a questa domanda. E la scoprirò… presto o tardi. Au revoir!";
			link.l1.go = "spanish_16";
		break;
		
		case "spanish_16":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "3");
			pchar.questTemp.Guardoftruth = "toship";
			sld = characterFromId("spa_baseprisoner");
			sld.dialog.currentnode = "spa_prisoner_28";
			LAi_CharacterEnableDialog(sld);
		break;
		
	// монах-посланник от Винсенто
		case "monk_vinsento":
			dialog.text = TimeGreeting()+"! Siete voi il capitano "+GetFullName(pchar)+"?";
			link.l1 = "Sì, sono io. Cosa posso fare per voi?";
			link.l1.go = "monk_vinsento_1";
		break;
		
		case "monk_vinsento_1":
			dialog.text = "Saluti, capitano. Padre Vincento mi manda da voi. Ho qualcosa per voi...";
			link.l1 = "Padre Vincento? Non servo più Sua Grazia. Non dopo che ha mandato Alonso de Maldonado, il cane fedele di Diego de Montoya, a farmi la pelle. Puoi riferire al Reverendo Padre questo: il suo piano è andato a monte.";
			link.l1.go = "monk_vinsento_2";
		break;
		
		case "monk_vinsento_2":
			dialog.text = "Aspetta, capitano. Padre Vincento si aspettava proprio questa reazione da parte vostra e mi mise in guardia. Vi assicuro che Sua Eccellenza non vi augura alcun male. Vi prego, leggete questa lettera. È davvero, davvero importante.";
			link.l1 = "Padre Vincento non mi vuole male? Eh. Forse si è anche dimenticato di raccontarti qualcosa su di me e Don de Maldonado? Spiegami, allora, perché dovrei crederti.";
			link.l1.go = "monk_vinsento_3";
		break;
		
		case "monk_vinsento_3":
			dialog.text = "Prendi questa lettera, capitano. Leggila e decidi di tua testa. Sappi solo che il destino di tutta la cristianità grava sulle tue spalle. Non prenderla alla leggera. Che Dio ti benedica e ti guidi sulla rotta giusta!";
			link.l1 = "D'accordo, dammi la lettera.";
			link.l1.go = "monk_vinsento_4";
		break;
		
		case "monk_vinsento_4":
			GiveItem2Character(pchar, "specialletter"); 
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_last";
			dialog.text = "Ecco qua. Prego che tu scelga con saggezza. Pax vobiscum.";
			link.l1 = "...";
			link.l1.go = "monk_vinsento_5";
		break;
		
		case "monk_vinsento_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			ReOpenQuestHeader("Sharlie"); // patch-8
			AddQuestRecord("Sharlie", "40");
			CloseQuestHeader("Ksochitam");
		break;
		
	// падре Адриан
		case "adrian":
			dialog.text = "Salute a te, figliolo. Che il Signore sia con te.";
			link.l1 = "E anche con voi, padre Adrian. Sua Eccellenza mi ha detto che potete fornirmi amuleti e medicamenti.";
			link.l1.go = "adrian_1";
		break;
		
		case "adrian_1":
			dialog.text = "Sì, certo. Ho ricevuto una spedizione speciale da Santiago proprio per te. Ecco amuleti benedetti e pozioni curative. E per finire, una rara e unica tintura di Ometochtli che ti renderà invincibile in battaglia. Tutto questo è per te, figliolo. Prendi e vedrai quanto è buono il Signore.";
			link.l1 = "Grazie!";
			link.l1.go = "adrian_2";
		break;
		
		case "adrian_2":
			for(i=2; i<=10; i++)
			{
				if (i == 4 || i == 5 || i == 8 || i == 9) continue;
				TakeNItems(pchar, "amulet_"+i, 2);
			}
			TakeNItems(pchar, "potion2", 20);
			TakeNItems(pchar, "potion4", 10);
			TakeNItems(pchar, "potion7", 3);
			TakeNItems(pchar, "berserker_potion", 3);
			dialog.text = "Se ti servissero ancora delle erbe curative, posso darti una fiala di ognuna ogni giorno. Ne preparerò quante ne vorrai.";
			link.l1 = "Hai la mia gratitudine, Padre Adrian. Ne terrò conto.";
			link.l1.go = "exit";
			link.l2 = "Perfetto. Ne ho proprio bisogno adesso.";
			link.l2.go = "potion";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "adrian_3":
			dialog.text = "Dio ti benedica e ti protegga, figliolo. Che desideri?";
			link.l1 = "Vorrei acquistare qualche pozione curativa.";
			link.l1.go = "potion";
			link.l2 = "Niente per ora, mi sto preparando per un viaggio. Sono passato solo per salutarti e vedere come te la passi.";
			link.l2.go = "exit";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "potion":
			dialog.text = "Ma certo, figliolo. Che rimedio ti serve?";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "Solo un rimedio da poco.";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "Un elisir che ridà vigore.";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "Un antidoto.";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "Un miscuglio d’erbe.";
				link.l4.go = "potion4";
			}
			link.l5 = "Perdonami d’averti disturbato, padre. Ho cambiato idea.";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "Un’essenza curativa? Sono 90 pesos, figliolo. Solo per i materiali, s’intende.";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "Grazie, padre.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Purtroppo non ho monete... Tornerò più tardi.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "Un elisir che ti ridarà vigore? 500 pesos, figliolo.";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "Grazie, padre.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Purtroppo, non ho il denaro... Tornerò più tardi.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "Un antidoto? 200 pesos, figliolo.";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "Grazie, padre.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Purtroppo, non ho il denaro... Tornerò più tardi.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "Un miscuglio d’erbe? Novecento pesos, figliolo.";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "Grazie, padre.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Purtroppo non ho il denaro... Tornerò più tardi.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "«Poiché io ti restituirò la salute e ti guarirò dalle tue ferite, dice il Signore.» Ecco la tua medicina. Dominus vobiscum!";
			link.l1 = "Grazie, padre Adriano.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
			NextDiag.TempNode = "adrian_3";
		break;
		
	// посланец Дичозо
		case "Dichoso_agent":
			dialog.text = "Capitano "+GetFullName(pchar)+"?";
			link.l1 = "Sì, sono io. Che vuoi?";
			link.l1.go = "Dichoso_agent_1";
		break;
		
		case "Dichoso_agent_1":
			dialog.text = "Ho un messaggio per voi dal Capitano Miguel Dichoso. Dice che lo conoscete.";
			link.l1 = "Sì, ne ho sentito parlare. Non ho mai avuto l’onore di incontrarlo di persona.";
			link.l1.go = "Dichoso_agent_2";
		break;
		
		case "Dichoso_agent_2":
			dialog.text = "Il capitano Dichoso vorrebbe cambiare le carte in tavola. Vuole incontrarti di persona. Ha una proposta per te riguardo a una spedizione nelle profondità della Terraferma spagnola, verso la perduta città indiana di Tayasal. Mi ha detto che la tua esperienza, unita alla sua conoscenza, porterà a risultati assai soddisfacenti.";
			link.l1 = "Furono proprio queste le sue parole?";
			link.l1.go = "Dichoso_agent_3";
		break;
		
		case "Dichoso_agent_3":
			dialog.text = "Esatto. Il capitano Dichoso ti aspetterà a Saint-Christophe. Lo troverai nella grande cripta del cimitero di Capsterville, per sfuggire a occhi e orecchi indiscreti.";
			link.l1 = "Hm...";
			link.l1.go = "Dichoso_agent_4";
		break;
		
		case "Dichoso_agent_4":
			dialog.text = "Dichoso mi ha avvertito che avresti esitato. Mi ha detto di offrirti garanzie che non ti sarà torto un capello durante le trattative, qualunque sia la tua scelta. Aggiunge anche che quello che hai trovato su quella certa isola era solo un piccolo antipasto rispetto a ciò che ti aspetta a Tayasal.";
			link.l1 = "Così dici... davvero curioso. Ma perché il capitano Dichoso non è venuto di persona? Per quale diavolo motivo ha mandato un intermediario?";
			link.l1.go = "Dichoso_agent_5";
		break;
		
		case "Dichoso_agent_5":
			dialog.text = "Don Dichoso ti ha cercato dapprima a Isla Tesoro, poi qui, e ora veleggia verso San Cristoforo sperando di trovarti laggiù. Sei un ufficiale di Philippe de Poincy in persona, no? Dovevo attenderti qui, nel caso arrivassi a Blueweld.";
			link.l1 = "Allora tutto è chiaro. Va bene, non perderò altro tempo, devo andare a Capsterville.";
			link.l1.go = "Dichoso_agent_6";
		break;
		
		case "Dichoso_agent_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "Tieyasal_PrepareDichosoTrap", -1);
		break;
		
	// агент Дичозо
		case "Dichoso_crypt_agent":
			dialog.text = "Ebbene, ci incontriamo finalmente, capitano "+GetFullName(pchar)+"...";
			if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) 
			{
				link.l1 = "Dov’è Miguel Dichoso? E non cercare di svignartela. So bene chi sia in realtà, e credo che anche tu lo sappia.";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "Suppongo che questo sia Miguel Dichoso in carne ed ossa proprio davanti a me?";
				link.l1.go = "Dichoso_crypt_agent_1";
			}
		break;
		
		case "Dichoso_crypt_agent_1":
			dialog.text = "Hai indovinato, capitano. Da un bel pezzo ci stiamo braccando a vicenda, non è vero?";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l1 = "Ti vedo subito che menti, compare. Tu non sei Dichoso. Ho letto i resoconti del capitano della 'Santa Quiteria' e ho chiesto in giro com’era fatto. Non gli assomigli nemmeno. Non hai nemmeno la cicatrice di sciabola sulla faccia. Suvvia, anche un saltimbanco avrebbe almeno provato a disegnarla!";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "Esattamente. Se ho capito bene, siamo qui per parlare della città perduta di Tayasal?";
				link.l1.go = "Dichoso_crypt_agent_7";
			}
		break;
		
		case "Dichoso_crypt_agent_2":
			dialog.text = "Ah! Allora non ha senso continuare questa farsa. Miguel mi aveva avvertito che eri un furfante astuto...";
			link.l1 = "Dov’è Miguel Dichoso?";
			link.l1.go = "Dichoso_crypt_agent_3";
		break;
		
		case "Dichoso_crypt_agent_3":
			dialog.text = "Non è qui. Ho l’autorizzazione d’incontrarti e parlare in sua vece.";
			link.l1 = "Non parlo con i fanti. Sono qui per il re. Dov’è lui?!";
			link.l1.go = "Dichoso_crypt_agent_4";
		break;
		
		case "Dichoso_crypt_agent_4":
			dialog.text = "Non siete proprio di compagnia, capitano. Avete perso la vostra compostezza.";
			link.l1 = "Basta scherzi, ho capito l'antifona. È di nuovo un’imboscata. Dovreste inventarvi qualche trucco nuovo, ragazzi.";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
		case "Dichoso_crypt_agent_5":
			dialog.text = "Ahah, ci hai preso di nuovo, compare! I miei uomini ti aspettano proprio dietro la porta che porta alle catacombe. E in più, ho moschettieri appostati dietro ogni pietra tombale, pronti a far fuoco. Non c'è via di scampo. Per quanto questo trucco possa sembrar stantio, ci sei cascato come un pesciolino! La tua smania di vedere Tayasal ha annebbiato quel poco di buonsenso che ti restava!";
			link.l1 = "Hai scelto un bel posto per una rissa, canaglia. Non dovrò andare lontano per seppellirti insieme ai tuoi compari di ventura.";
			link.l1.go = "Dichoso_crypt_agent_6";
		break;
		
		case "Dichoso_crypt_agent_6":
			dialog.text = "Ahah! Mi piace il tuo spirito! Proprio come quello di Miguel! Dì ciò che vuoi, siete fatti della stessa pasta... Farò come ha ordinato lui – ti manderò all’Inferno in fretta e senza troppi patimenti. All’armi, ragazzi!";
			link.l1 = "Uomini migliori di te ci hanno provato. Porta i miei saluti al Diavolo, furfante!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_StartCryptBattle");
		break;
		
		case "Dichoso_crypt_agent_7":
			dialog.text = "Vuoi davvero entrare in città? Capisco, capitano, ma non credo sia una buona idea.";
			link.l1 = "Allora, di cosa mai dovremmo ciarlare qui?";
			link.l1.go = "Dichoso_crypt_agent_8";
		break;
		
		case "Dichoso_crypt_agent_8":
			dialog.text = "Non cerco di intavolare con te una lunga e sdolcinata conversazione. Sei qui, e per me questo basta.";
			link.l1 = "Basta scherzi, ho capito. È di nuovo un’imboscata. Dovreste inventarvi qualche trucco nuovo, furfanti.";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
	// командир абордажников
		case "newcastle_officer":
			dialog.text = "In attesa dei tuoi ordini, capitano!";
			link.l1 = "Attraversiamo la giungla fino al cimitero di Capsterville. Una volta arrivati, non entrate nel camposanto. Prendete posizione con i moschetti proprio fuori dal cancello e tendete l’orecchio mentre entro io. Se sentite che scoppia una rissa, piombate dentro senza indugio.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_0":
			dialog.text = "In attesa dei vostri ordini, capitano!";
			link.l1 = "Attraversiamo la giungla fino al cimitero di Capsterville. Una volta lì, non entrate nel cimitero stesso. Prendete posizione lungo il sentiero, circondate il camposanto e tenete le orecchie tese finché non sarò dentro. Tutta questa faccenda puzza d’agguato. Appena avvistate il nemico, attaccate senza indugio.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_1":
			dialog.text = "Aye aye, capitano!";
			link.l1 = "D’accordo. Avanti!";
			link.l1.go = "newcastle_officer_2";
		break;
		
		case "newcastle_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Charles_exittown")].DisableEncounters = true; //энкаутеры закрыть
			locations[FindLocation("Charles_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			for(i=2; i<=4; i++)
			{
				locations[FindLocation("Charles_Jungle_0"+i)].DisableEncounters = true; //энкаутеры закрыть
			}
			LocatorReloadEnterDisable("Shore42", "boat", true);
			for(i=1; i<=iTotalTemp; i++)
			{
				sld = characterFromID("Tieyasal_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// на локацию перед кладбищем
			pchar.quest.Tieyasal_newcastle.win_condition.l1 = "location";
			pchar.quest.Tieyasal_newcastle.win_condition.l1.location = "Charles_exittown";
			pchar.quest.Tieyasal_newcastle.function = "Tieyasal_NewcastleGoJungle";
			// на крипту
			pchar.quest.Tieyasal_graveyard.win_condition.l1 = "location";
			pchar.quest.Tieyasal_graveyard.win_condition.l1.location = "Charles_CryptBig2";
			pchar.quest.Tieyasal_graveyard.function = "Tieyasal_InGraveyardCrypt";
		break;

case "Europe":
			PlaySound("Voice\English\military01.wav");
			dialog.text = "Capitano Hobart! Secondo le soffiate della nostra spia, i ribelli si nascondono in questa tenuta. Avete cinque dragoni a disposizione. Passate al setaccio l’edificio e acciuffate chiunque vi troviate dentro! Non usate mezzi gentili con questa feccia. Agite in nome del Re!";
			link.l1 = "Sissignore!";
			link.l1.go = "Europe_1";
		break;
		
		case "Europe_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Europe_SharlieFinal_1", 5);
		break;
		
		//Индеец по квесту "Знакомство с индейцами"
		case "ZsI_ListKakao":
			dialog.text = "Tsk! Figlio del Mare!";
			link.l1 = "Eh... cosa? Stai parlando con me?";
			link.l1.go = "ZsI_ListKakao_1";
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "ZsI_ListKakao_1":
			dialog.text = "D'accordo. Sono Foglia di Cacao. Ho un affare con te, Figlio del Mare.";
			link.l1 = "Non so che aspetto abbia il cacao, né perché ti chiami così. Ma va bene, sputa il rospo, dimmi in fretta cosa ti serve.";
			link.l1.go = "ZsI_ListKakao_2";
		break;
		
		case "ZsI_ListKakao_2":
			dialog.text = "Tsk! Vai in città. Compra due pistole e dieci cariche di polvere e pallottole ciascой. Portamele. C'è una ricompensa. Il Figlio del Mare ne sarà soddisfatto.";
			link.l1 = "Due pistole e venti colpi? Tutto qui? Allora perché non te li compri da solo?";
			link.l1.go = "ZsI_ListKakao_3";
		break;
		
		case "ZsI_ListKakao_3":
			dialog.text = "Non capisci, faccia di latte? Chi mai mi venderebbe un’arma da fuoco?!";
			if (CheckAttribute(pchar, "questTemp.ZsI_Cannibals"))		//Sinistra Только если проходил квест "Каннибалы"
			{
				link.l1 = "Sai, ho già incontrato gente come te a Martinica... Cannibali. Hanno rapito una ragazza e due uomini. Uno di loro l’hanno arrostito e divorato. Se solo uno di quei poveracci avesse avuto una pistola, adesso non staremmo a ciarlare.";
				link.l1.go = "ZsI_ListKakao_3_1";
			}
			else
			{
				link.l1 = "E perché ti serve un'arma da fuoco, Foglia di Cacao? Hai forse intenzione di far fuori qualcuno?";
				link.l1.go = "ZsI_ListKakao_3_2";
			}
		break;
		
		case "ZsI_ListKakao_3_1":
			dialog.text = "Goo-oo! Foglia di Cacao non è un brigante, io combatto solo contro i guerrieri della tua tribù. I visi pallidi vengono sulla nostra terra, ci rendono schiavi. Foglia di Cacao combatte di persona. Prendi uno schiavo. Né bene né male. Così va il mondo. Indiano, bianco, non fa differenza. Sono le armi da fuoco a fare la differenza.";
			link.l1 = "E perché mai ti serve un’arma da fuoco, Foglia di Cacao? Hai forse intenzione di far fuori qualcuno?";
			link.l1.go = "ZsI_ListKakao_3_2";
		break;
		
		case "ZsI_ListKakao_3_2":
			dialog.text = "Combattere. Ma ad armi pari. I visi pallidi hanno armi da fuoco, gli indiani no. Non è giusto. E per un indiano avere un’arma da fuoco significa difendersi da soprusi, umiliazioni o insulti dei visi pallidi.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_4";
		break;
		
		case "ZsI_ListKakao_4":
			StartInstantDialog("Tichingitu", "ZsI_ListKakao_5", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_5":
			dialog.text = "D'accordo, Capitano. Quei visi pallidi ci guardano dall'alto in basso.";
			link.l1 = "Me ne sono accorto. In Europa blaterano su come insegnare la vera fede agli indios, e su come tutti lavoriamo insieme in pace nelle piantagioni...";
			link.l1.go = "ZsI_ListKakao_7";
		break;
		
		case "ZsI_ListKakao_7":
			dialog.text = "Tichingitu forse non capisce il capitano, ma la Foglia di Cacao la conosce bene. Cerca vendetta.";
			link.l1 = "Sembra proprio di sì... Non desideri anche tu vendicarti dei nostri recenti carcerieri?";
			link.l1.go = "ZsI_ListKakao_8";
		break;
		
		case "ZsI_ListKakao_8":
			dialog.text = "Forse. Ma Tichingitu non arriverà a tanto. Tichingitu ora è con te. E Tichingitu usa la propria testa. Ci sarebbe troppo spargimento di sangue. Sangue bianco. Sangue indiano. Troppa sofferenza. Non è giusto.";
			link.l1 = "Sì, la situazione è già pessima, e aiutare Foglia di Cacao a procurarsi delle armi la peggiorerà soltanto... Ma, in fondo, non ha tutti i torti. E poi tra poco devo anche pagare la mia ciurma.";
			link.l1.go = "ZsI_ListKakao_9";
		break;
		
		case "ZsI_ListKakao_9":
			dialog.text = "Usa la tua testa, Capitano.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_10";
		break;
		
		case "ZsI_ListKakao_10":
			StartInstantDialog("ListKakao", "ZsI_ListKakao_11", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_11":
			dialog.text = "Quel Figlio del Mare chiacchiera più d’una vecchia pettegola coi baffi.";
			link.l1 = "Chi? Spiegamelo, Foglia di Cacao. Anch'io sono un viso pallido, e vieni da me a chiedere armi per combattere i visi pallidi. Non ti pare una bella contraddizione? Perché proprio io?";
			link.l1.go = "ZsI_ListKakao_12";
		break;
		
		case "ZsI_ListKakao_12":
			dialog.text = "Ho sentito la tua chiacchierata con quell’indiano vestito in modo bizzarro. Tu non sei come gli altri visi pallidi. Capisci il Tichingitu. E sono sicuro che sai apprezzare anche la Foglia di Cacao.";
			link.l1 = "Oh... E tu cosa offri in cambio d’armi, Foglia di Cacao?";
			link.l1.go = "ZsI_ListKakao_13";
		break;
		
		case "ZsI_ListKakao_13":
			dialog.text = "Le lacrime degli dèi. Le chiamate perle. Tante perle.";
			link.l1 = "Ho preso la mia decisione, Foglia di Cacao. Aspettami qui, vado dal mercante d’armi. Comprerò ciò che mi serve e torno.";
			link.l1.go = "ZsI_ListKakao_Soglasen_5";
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				link.l2 = "Ho preso la mia decisione, Foglia di Cacao. Guarda caso ho già quello che ti serve. Tieni, è tuo.";
				link.l2.go = "ZsI_ListKakao_Soglasen_2";
			}
			link.l3 = "Ho preso la mia decisione, Foglia di Cacao. Non ho voglia di attirare guai inutili. Da me non avrai archibugi. Ora leva le ancore.";
			link.l3.go = "ZsI_ListKakao_Otkaz";
			npchar.LifeDay = 1;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		
		case "ZsI_ListKakao_Otkaz":
			dialog.text = "Tsk!";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Otkaz_2";
		break;
		
		case "ZsI_ListKakao_Otkaz_2":
			DialogExit();
			
			ChangeIndianRelation(-3.0);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "ZsI_Mir", -1);
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 1.0, 1.0);
			npchar.lifeday = 0;
			PChar.quest.ZsI_Draka.win_condition.l1 = "NPC_Death";
			PChar.quest.ZsI_Draka.win_condition.l1.character = "ListKakao";
			PChar.quest.ZsI_Draka.win_condition = "ZsI_Draka";
			PChar.quest.ZsI_Mir.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ZsI_Mir.win_condition.l1.location = PChar.location;
			PChar.quest.ZsI_Mir.win_condition = "ZsI_Mir";
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			sld = characterFromId("Tichingitu");
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.Dialog.CurrentNode = "Tichingitu_officer";
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_2":
			dialog.text = "Ohilà! Il Figlio del Mare ha forse un moschetto? Si paga caro, un moschetto!";
			link.l1 = "No, ma che ne dici di un colpo di cannone dalla mia nave? Sparisci subito, Foglia di Cacao, prima che ci pizzichino e ci mettano in catene.";
			link.l1.go = "ZsI_ListKakao_Soglasen_3";
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			ChangeIndianRelation(3.0);
			AddItems(pchar, "jewelry53", 180);
			Log_Info("You have received 180 small pearls");
			PlaySound("Interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
				RemoveItems(PChar, "pistol1", 2);
				RemoveItems(PChar, "GunPowder", 20);
				RemoveItems(PChar, "bullet", 20);
			}
		break;
		
		case "ZsI_ListKakao_Soglasen_3":
			dialog.text = "Affare fatto! Figlio del Mare, se ti addentri nella selva, porta con te un’arma da fuoco. S’imbatti in un indio, che sia uno scambio vantaggioso.";
			link.l1 = "Terrò a mente. Addio, Foglia di Cacao.";
			link.l1.go = "ZsI_ListKakao_Soglasen_4";
		break;
		
		case "ZsI_ListKakao_Soglasen_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			Return_TichingituOfficer();
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_5":
			dialog.text = "La Foglia di Cacao aspetterà.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Soglasen_6";
		break;
		
		case "ZsI_ListKakao_Soglasen_6":
			DoQuestReloadToLocation("BasTer_town", "reload", "gate_back", "ZsI_TPvGorod");
		break;

		case "ZsI_officer":
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				dialog.text = "Bah, pare che qui si sia radunata tutta la ciurma di selvaggi!\nVuoi tornare in gattabuia, cane?\nChe ci fai qui, Monsieur?";
			}
			else
			{
				dialog.text = "Altolà! Che ci fate qui, Monsieur?";
			}
			link.l1 = "";
			link.l1.go = "ZsI_officer_2";
			sld = CharacterFromID("ListKakao");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "ZsI_officer_2":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "Ehi, canaglia, aspettavi forse questo galantuomo?";
			link.l1 = "";
			link.l1.go = "ZsI_officer_3";
		break;
		
		case "ZsI_officer_3":
			DialogExit();
			StartInstantDialog("ListKakao", "ZsI_officer_4", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_4":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ZsI_Patrul_off"));
			dialog.text = "Tutte le facce pallide mi sembrano uguali. Ma questo qui non l’ho mai visto. Tu, guerriero, fa’ quel che devi con me. Inizia a darmi noia. Foglia di Cacao è pronta ad affrontare gli spiriti della foresta.";
			link.l1 = "";
			link.l1.go = "ZsI_officer_5";
		break;
		
		case "ZsI_officer_5":
			DialogExit();
			StartInstantDialog("ZsI_Patrul_off", "ZsI_officer_6", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_6":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "L’inferno t’attende, non gli spiriti della foresta.";
			link.l1 = "";
			link.l1.go = "ZsI_officer_7";
		break;
		
		case "ZsI_officer_7":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			dialog.text = "Capitano, sei congedato. Togliti dai piedi. Difendere la città è faccenda da gente seria.";
			link.l1 = "Capisco... Ma che ne facciamo di questo indio?";
			link.l1.go = "ZsI_officer_8";
		break;
		
		case "ZsI_officer_8":
			dialog.text = "Che ti frega degli indiani, Monsieur? Ah già... sei appena sbarcato dall’Europa.\nCom’è Parigi? Ancora schiacciano i topi nelle strade, o già li invitano alla messa domenicale? Qui invece dei topi abbiamo i selvaggi. Fanno affari coi bucanieri, assaltano i taglialegna — e, maledizione, si mangiano pure la gente!\nTre giorni fa un genio ha già venduto un moschetto a uno di questi tipi. Indovina? Quelle carogne hanno fatto fuori tutta la pattuglia, guidata, tra l’altro, da un mio amico e compagno d’armi. Abbiamo trovato il colono traditore e l’abbiamo lasciato a seccare al sole, come monito. Dare armi da fuoco agli indiani! Questa è alto tradimento! Tradimento contro la Francia!\nÈ da un po’ che seguiamo quella scimmia colorata, ormai la sua faccia la conoscono tutti alle nostre feste.\nEbbene, ora incontrerà la sua fine, rapida e meritata. Puoi andare oltre, Capitano. Non ficcare il naso in faccende che non ti riguardano. Non sei in questa guerra... non ancora... O forse sì?!";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l1 = "(Affidabile) Vedete, ufficiale... Sono il Capitano Charles de Maure, ospite di Fadey Moscovita. Abbiamo dei particolari affari con questo indiano... quindi non intralciamoci a vicenda. D'accordo, Tenente?";
				link.l1.go = "ZsI_officer_Mir";
			}
			link.l2 = "Attitudini verso i forestieri, opinioni sui nativi... Coloni, indigeni... Non ci capisco ancora molto in tutto ciò, ma in questo momento, Tenente, il paragone non gioca a tuo favore... All’armi!";
			link.l2.go = "ZsI_officer_Draka";
			link.l3 = "Hai ragione, Tenente, non lo sono. Addio.";
			link.l3.go = "ZsI_officerKIll";
		break;
		
		case "ZsI_officer_Mir":
			dialog.text = "Ehm! Capito, Capitano. Riferisca i miei saluti al signor Fadey. Squadra, riprendete la ronda!";
			link.l1 = "";
			link.l1.go = "ZsI_officer_Mir_2";
		break;
		
		case "ZsI_officer_Mir_2":
			DialogExit();
			
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_SetImmortal(sld, true);
			LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetActorType(sld);
				sld.lifeday = 0;
				LAi_SetImmortal(sld, true);
				LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			}
			sld = CharacterFromID("ListKakao");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "ZsI_MirFinal";
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Fortune", 30);
		break;
		
		case "ZsI_MirFinal":
			dialog.text = "Uh-oh!";
			link.l1 = "Già, beh, persino io sono stupito che abbia funzionato. Ecco la tua merce, Foglia di Cacao.";
			link.l1.go = "ZsI_MirFinal_2";
		break;
		
		case "ZsI_MirFinal_2":
			dialog.text = "Il Figlio del Mare sa come parlare. Salvare un indiano è roba grossa! Ricompensa grossa!";
			link.l1 = "Per tutti i santi, che bottino... E una pietra bucata, e una specie di talismano.";
			link.l1.go = "ZsI_MirFinal_3";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("You have received 180 small pearls");
			Log_info("You have received Amulet 'Cascavella'}");
			Log_info("You have received Ward 'Adder stone'");
			Log_info("You have received 3 Datura herbs");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_MirFinal_3":
			dialog.text = "Il Figlio del Mare ha un moschetto? Paga caro per un moschetto!";
			link.l1 = "No, ma forse un colpo del mio cannone ti basta? Sparisci, Foglia di Cacao, prima che ci becchino e ci sbattano in gattabuia.";
			link.l1.go = "ZsI_MirFinal_4";
		break;
		
		case "ZsI_MirFinal_4":
			dialog.text = "Affare fatto! Figlio del Mare, se ti avventuri nella selva, porta con te un’arma da fuoco. Se incontri un indio, che sia un buon affare.";
			link.l1 = "Me lo ricorderò. Addio, Foglia di Cacao.";
			link.l1.go = "ZsI_MirFinal_5";
		break;
		
		case "ZsI_MirFinal_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetPlayerType(pchar);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "ZsI_officer_Draka":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeCharacterComplexReputation(pchar, "authority", -2);	
			ChangeIndianRelation(5.0);
			ChangeCharacterNationReputation(pchar, FRANCE, -10);
			sld = CharacterFromID("ListKakao");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetImmortal(sld, false);
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "ZsI_officer_Draka_3");
		break;
		
		case "ZsI_Final":
			ChangeIndianRelation(5.0);
			dialog.text = "Ohimè! Che sciocchezza hai fatto, figliolo del mare. Perché mai ti sei impelagato così?";
			link.l1 = "Ugh... Cinque minuti fa mi sembrava giusto... Ora non ne sono più tanto sicuro... Ho ucciso uno dei miei, dopotutto. E adesso che devo fare? E se lo scoprono? Maledizione! Maledizione!";
			link.l1.go = "ZsI_Final_2";
		break;
		
		case "ZsI_Final_2":
			dialog.text = "Ora ci sarà un'incursione. I soldati ammazzano chiunque. Due pattuglie, nessuna pietà. Fuga della Foglia di Cacao. E tu, Figlio del Mare... perché. La Foglia di Cacao morirà comunque. Gli spiriti così vogliono.";
			link.l1 = "Oh... Il nostro accordo è ancora valido?";
			link.l1.go = "ZsI_Final_3";
		break;
		
		case "ZsI_Final_3":
			dialog.text = "Brutta scelta, Figlio del Mare. Ma ti ringrazio. Ricompensa grossa.";
			link.l1 = "Non così grande, dopotutto...";
			link.l1.go = "ZsI_Final_4";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("You have received 180 small pearls");
			Log_info("You have received Amulet 'Cascavella'}");
			Log_info("You have received Ward 'Adder stone'");
			Log_info("You have received 3 Datura herbs");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_Final_4":
			dialog.text = "Figlio del Mare, se sopravvivi e poi ti avventuri nella selva, porta con te un’arma da fuoco. Se incontri un indio, che sia per trattare.";
			link.l1 = "Terrò a mente per il futuro. Addio, Foglia di Cacao.";
			link.l1.go = "ZsI_Final_5";
		break;
		
		case "ZsI_Final_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
		break;
		
		case "ZsI_officerKIll":
			DialogExit();
			
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("ListKakao"));
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("ZsI_officerKIll_1", 0.1);
			DoQuestCheckDelay("ZsI_officerKIll_2", 1.3);
			AddItems(pchar, "pistol1", 2);
			AddItems(pchar, "GunPowder", 20);
			AddItems(pchar, "bullet", 20);
		break;
		
		//Торговец Барбье по квесту "Деньги на деревьях"
		case "MOT_Barbie":
			dialog.text = "Saluti, Capitano Charles de Maure. Il mio nome è Charles Barbier. Potrei rubarvi un attimo del vostro tempo?";
			link.l1 = "Capitano de Maure... Sì, proprio io! Andate avanti, Monsieur Barbier.";
			link.l1.go = "MOT_Barbie_2";
		break;
		
		case "MOT_Barbie_2":
			dialog.text = "È sempre un piacere incontrare un collega, soprattutto uno che porta il mio stesso nome! Ho una proposta per voi, Capitano. Vedete, avrei bisogno d’una scorta fino a Saint-Pierre, e...";
			link.l1 = "Conosco Saint-Pierre! Ma son solo due giorni di viaggio! E devo ammettere, son ancora un pivello come scorta. Ho preso il comando di questa nave solo una settimana fa.";
			link.l1.go = "MOT_Barbie_3";
		break;
		
		case "MOT_Barbie_3":
			dialog.text = "La tua sincerità è gradita, Capitano. Charles, perdona la mia schiettezza, ma tu sei proprio l’uomo di cui ho bisogno.";
			link.l1 = "Hmm... Ricordo una proposta simile non molto tempo fa. Finì con un’imboscata di filibustieri vicino a Le Francois.";
			link.l1.go = "MOT_Barbie_4";
		break;
		
		case "MOT_Barbie_4":
			dialog.text = "Ho sentito parlare di quell’incidente, per questo sono venuto a cercarti\nInnanzitutto, trasporto un carico di gran valore, e i predoni non mancano mai nei paraggi. Tuttavia, la tua recente vittoria contro quei filibustieri vicino a Le Francois farà riflettere i furfanti del luogo\nInoltre, la tua amicizia con Fadey il Moscovita è un bel biglietto da visita.";
			link.l1 = "Argomento interessante, Monsieur. E quale ricompensa proponete per questo favore?";
			link.l1.go = "MOT_Barbie_5";
		break;
		
		case "MOT_Barbie_5":
			dialog.text = "Non è un favore, Capitano, ma un'impresa vantaggiosa per entrambi! Vi pagherò quaranta pezzi d'oro se m'accompagnate a Saint-Pierre senza indugio.";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l1 = "(Fidato) Dal momento che vado dall’altra parte, Monsieur, dovrai pagarmi in anticipo.";
				link.l1.go = "MOT_Barbie_Torg";
			}
			link.l2 = "Non è una brutta proposta – tanto vado già da quella parte. Affare fatto!";
			link.l2.go = "MOT_Barbie_Soglasen";
			link.l3 = "Merce di valore, dici? Ahimè, Monsieur, ne ho abbastanza di avventure, almeno per ora.";
			link.l3.go = "MOT_Barbie_Otkaz";
		break;
		
		case "MOT_Barbie_Torg":
			dialog.text = "Difficile rifiutare un giovane così serio, Capitano. Ecco i tuoi quaranta dobloni. Salpiamo subito allora? Il tempo è oro.";
			link.l1 = "Non indugeremo a lungo, Monsieur. Presto faremo vela.";
			link.l1.go = "MOT_Barbie_Escadra";
			
			AddItems(pchar, "gold_dublon", 40);
			Log_info("You've received 40 doubloons");
			PlaySound("Interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
		break;
		
		case "MOT_Barbie_Soglasen":
			dialog.text = "Eccellente! Mi preparo subito a salpare!";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Escadra";
		break;
		
		case "MOT_Barbie_Otkaz":
			dialog.text = "Capisco, Capitano. Non mi permetterò di disturbare oltre. Addio, e che sia una buona giornata.";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Otkaz_2";
		break;
		
		case "MOT_Barbie_Otkaz_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload6_back", "none", "", "", "", -1);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_Escadra":
			DialogExit();
			
			SetQuestHeader("MoneyOnTrees");
			AddQuestRecord("MoneyOnTrees", "1");
			
			FantomMakeCoolSailor(npchar, SHIP_BARKENTINE, "Charles", CANNON_TYPE_CANNON_LBS3, 40, 33, 20);
			npchar.Ship.Mode = "trade";
			SetCharacterRemovable(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.CompanionEnemyEnable = true;
			SetCrewQuantity(npchar, 35);
			SetCharacterGoods(npchar, GOOD_ROPES, 30);
			LAi_SetImmortal(npchar, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			SetTimerCondition("MOT_ZadanieProvaleno", 0, 0, 14, false);
			PChar.quest.MOT_Zahvatili.win_condition.l1 = "NPC_Death";
			PChar.quest.MOT_Zahvatili.win_condition.l1.character = "SharlieBarbie";
			PChar.quest.MOT_Zahvatili.win_condition = "MOT_Zahvatili";
			PChar.quest.MOT_Dostavili.win_condition.l1 = "location";
			PChar.quest.MOT_Dostavili.win_condition.l1.location = "FortFrance_town";
			PChar.quest.MOT_Dostavili.win_condition = "MOT_Dostavili";
		break;
		
		case "MOT_Barbie_101":
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				dialog.text = "Grazie per la scorta impeccabile, Capitano. Son lieto che il viaggio sia filato liscio come l’olio.";
				link.l1 = "È stato un piacere fare affari con voi, Monsieur. Ora, se volete scusarmi, ho molte faccende da sbrigare.";
			}
			else
			{	
				dialog.text = "Vi ringrazio per la scorta impeccabile, Capitano. Mi rallegra che il viaggio sia filato liscio come l’olio. Ecco la vostra paga – quaranta dobloni, tutti interi.";
				link.l1 = "Un piacere fare affari con voi, Monsieur. Ora, se volete scusarmi, ho molte faccende che mi attendono.";
				AddItems(pchar, "gold_dublon", 40);
				Log_info("You've received 40 doubloons");
				PlaySound("Interface\important_item.wav");
			}
			link.l1.go = "MOT_Barbie_102";
		break;
		
		case "MOT_Barbie_102":
			dialog.text = "Charles...";
			link.l1 = "Sì, Charles? Hai l’aria agitata. C’è qualche guaio?";
			link.l1.go = "MOT_Barbie_103";
			RemoveCharacterCompanion(pchar, npchar);
			npchar.lifeday = 0;
		break;
		
		case "MOT_Barbie_103":
			dialog.text = "Ebbene, visto che sei un tipo affidabile, e conosci Fadey... Senti, il commercio è un mestiere rischioso, giusto?";
			link.l1 = "Se lo dici tu.";
			link.l1.go = "MOT_Barbie_104";
		break;
		
		case "MOT_Barbie_104":
			dialog.text = "Sono riuscito a procurarmi una partita di corde a buon mercato a Guadalupa da... beh, sai tu chi. Avevo intenzione di sbarazzarmene in fretta a Saint-Pierre e usare il ricavato per comprare caffè da rivendere a Willemstad. Sembrava un piano infallibile.";
			link.l1 = "Non metto in dubbio la vostra onestà, Monsieur, ma tutta questa faccenda mi pare alquanto sospetta. Parlate del vostro carico come se fosse oro puro, mentre la mia nave è piena di queste corde che valgono meno di una moneta bucata.";
			link.l1.go = "MOT_Barbie_106";
		break;
		
		case "MOT_Barbie_106":
			dialog.text = "Charles, queste funi sono di qualità sopraffina, intrecciate con la miglior canapa nelle manifatture dello Zar di Mosca. Servono per scopi strategici e si usano nell'armamento dei vascelli da guerra. Gli inglesi tengono il monopolio delle rotte con la Moscovia e vietano il libero commercio di queste funi. Le altre nazioni si scannano per accaparrarsi ogni briciola di questa merce nei cantieri d’Europa.";
			link.l1 = "Dunque, questo è contrabbando?";
			link.l1.go = "MOT_Barbie_107";
		break;
		
		case "MOT_Barbie_107":
			dialog.text = "Yes. Unfortunately, I had a falling out with Santiago smugglers last year. I had nearly forgotten about it, but these individuals maintain close connections and long memories. Here's a piece of advice: avoid incensing them and reneging on deals; it's a situation you won't rectify later.";
			link.l1 = "Grazie, ma il contrabbando non fa per me.";
			link.l1.go = "MOT_Barbie_108";
		break;
		
		case "MOT_Barbie_108":
			dialog.text = "Peccato! Il commercio onesto può portarti un bel guadagno, ma non ti farà mai diventare veramente ricco. Tuttavia, non ho iniziato questa conversazione rischiosa con te senza motivo. Ti propongo di acquistare un carico di corde da me. I contrabbandieri locali bazzicano spesso la taverna, e saranno ben felici di comprarle. Pensa un po’! Oggi potresti riempirti le tasche senza nemmeno mettere piede in mare aperto.";
			link.l1 = "Quanto chiedi per il carico?";
			link.l1.go = "MOT_Barbie_109";
		break;
		
		case "MOT_Barbie_109":
			dialog.text = "Diecimila pesos. È una cifra modesta, e rivendendo le funi ai contrabbandieri ci tirerai fuori un bel gruzzolo.";
			if (sti(pchar.Money) >= 10000)
			{
				link.l1 = "Non mi perdonerei mai se lasciassi scappare un’occasione come questa. Prendi l’argento e fa’ che la merce arrivi subito sulla mia nave.";
				link.l1.go = "MOT_Barbie_ContraSoglasen";
			}
			if (sti(pchar.Money) >= 7000)
			{
				link.l2 = "Questa è un'impresa rischiosa, amico mio. Facciamo così: incontriamoci a metà strada, va bene? Accetterò le tue corde per settemila.";
				link.l2.go = "MOT_Barbie_ContraTorg";
			}
			link.l3 = "È una somma ragguardevole, Monsieur. Comprendo la vostra situazione, ma non posso assumermi un rischio simile.";
			link.l3.go = "MOT_Barbie_ContraOtkaz";
		break;
		
		case "MOT_Barbie_ContraSoglasen":
			dialog.text = "La mia gratitudine, Charles! Mi hai salvato dalla rovina finanziaria! La merce sarà spedita in fretta e con la massima discrezione. Permettimi di darti un consiglio da collega mercante: appena ti sarai trovato un intendente di fiducia, procurati del caffè a Saint-Pierre e rivendilo per buon guadagno a Willemstad. I signori locali qui pagano a peso d’oro le merci coloniali, esportandole poi in Europa con laute ricompense. Che il vento ti sia favorevole nei tuoi affari, amico!";
			link.l1 = "Addio, Monsieur.";
			link.l1.go = "MOT_Barbie_ContraSoglasen_2";
			AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
			AddMoneyToCharacter(pchar, -10000);
			Log_info("You've received 30 ropes");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "MOT_Barbie_ContraSoglasen_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "5");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_ContraTorg":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 30)
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				dialog.text = "La mia riconoscenza, Charles! Mi hai salvato dalla rovina finanziaria! Le merci saranno spedite in fretta e con la massima discrezione. Permettimi di darti un consiglio da vecchio mercante: appena trovi un quartiermastro affidabile, procurati del caffè a Saint-Pierre e rivendilo a Willemstad. Le città dei paraggi pagano oro per le merci coloniali, che poi smerciando in Europa fruttano fortune. Che il vento ti sia favorevole, compare!";
				link.l1 = "Addio, Monsieur.";
				link.l1.go = "MOT_Barbie_ContraSoglasen_2";
				AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
				AddMoneyToCharacter(pchar, -7000);
				Log_info("You've received 30 ropes");
				PlaySound("Interface\important_item.wav");
			}
			else
			{
				notification("Skill Check Failed (31)", SKILL_COMMERCE); 
				dialog.text = "Non posso, Capitano. La mia mercanzia è roba importante e va trattata con il dovuto rispetto. La maggior parte dei capitani liberi non osa commerciare in beni strategici. Ahimè, qui le trattative non hanno posto.";
				if (sti(pchar.Money) >= 10000)
				{
					link.l1 = "Non mi perdonerei mai se lasciassi sfuggire un’occasione simile. Prendi l’argento e fa’ che la merce sia recapitata alla mia nave senza indugi.";
					link.l1.go = "MOT_Barbie_ContraSoglasen";
				}
				link.l2 = "È una somma considerevole, Monsieur. Capisco la vostra situazione, ma non posso assumermi un rischio simile.";
				link.l2.go = "MOT_Barbie_ContraOtkaz";
			}
		break;
		
		case "MOT_Barbie_ContraOtkaz":
			dialog.text = "Che peccato! Addio, Capitano.";
			link.l1 = "";
			link.l1.go = "MOT_Barbie_ContraOtkaz_2";
		break;
		
		case "MOT_Barbie_ContraOtkaz_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "4");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		//Миниквест "Делюк"
		//Матрос Алонсо
		case "Del_Alonso":
			dialog.text = "Capitano, abbiamo un grattacapo.";
			link.l1 = "Perdona? E tu chi diamine saresti?";
			link.l1.go = "Del_Alonso_2";
		break;
		
		case "Del_Alonso_2":
			dialog.text = "Il nostro nocchiere è stato arrestato e gettato nelle segrete locali. Pare sia una questione di debiti, così dicono.";
			link.l1 = "Di nuovo, eh?!";
			link.l1.go = "Del_Alonso_3";
		break;
		
		case "Del_Alonso_3":
			dialog.text = "È un vero demonio, Capitano.";
			link.l1 = "Che tempismo maledetto! Senza un navigatore, restiamo incagliati qui. Dovrò tirarlo fuori dai guai un'altra volta! Parlerò col comandante...";
			link.l1.go = "Del_Alonso_4";
		break;
		
		case "Del_Alonso_4":
			dialog.text = "Permesso di parlare, Capitano?";
			link.l1 = "Avanti, su.";
			link.l1.go = "Del_Alonso_5";
		break;
		
		case "Del_Alonso_5":
			dialog.text = "Perché dannarsi così tanto? Un uomo come lui porterà solo guai a bordo.";
			link.l1 = "Ho forse scelta? Di piloti qui mancano pure le ombre, quindi non è che abbia grandi alternative.";
			link.l1.go = "Del_Alonso_6";
		break;
		
		case "Del_Alonso_6":
			dialog.text = "Vero, trovare un timoniere di prima scelta non è facile, ma ora non ti serve un maestro, basta uno capace. La tua sorte è cambiata nell’ultima settimana, lo sai bene, no? Non c’è più bisogno di raschiare il fondo del barile per reclutare la ciurma. Ormai tutti parlano di come hai sconfitto quel bucaniere e di chi conosci nei porti. La gente di bordo ti sostiene, Capitano, ci piaci davvero.";
			link.l1 = "Mi rincuora, Alonso. E che ne pensa l’equipaggio di Deluc?";
			link.l1.go = "Del_Alonso_7";
		break;
		
		case "Del_Alonso_7":
			dialog.text = "Hai capito in fretta, Capitano. L’equipaggio lo vede come un buon ufficiale che ci tratta con rispetto, ma non vale tutte queste grane. Solo pochi giorni fa, hanno cacciato tutta la ciurma di una grossa nave mercantile. Forse varrebbe la pena fare un salto in taverna? Così suggerisce la ciurma.";
			link.l1 = "Grazie per il consiglio, Alonso. Ora non ti scorderò più. Torna sulla nave e guida la guardia mentre io mi occupo della faccenda.";
			link.l1.go = "Del_Alonso_8";
		break;
		
		case "Del_Alonso_8":
			dialog.text = "Aye, aye.";
			link.l1 = "...";
			link.l1.go = "Del_Alonso_9";
		break;
		
		case "Del_Alonso_9":
			DialogExit();
			SetQuestHeader("FolkeDeluc");
			AddQuestRecord("FolkeDeluc", "1");
			
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			SetFunctionLocationCondition("FortfranceJailOff_AddQuestMark", "fortfrance_prison", false);
			QuestCloseSeaExit();
			sld = CharacterFromID("Folke");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_Folke_1";
			RemovePassenger(pchar, sld);
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "FortFrance_prison", "goto", "goto9");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.questTemp.Del_Deluck = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("Del_shturman", "mercen_4", "man", "man", 5, FRANCE, 3, false, "quest"));
			GiveItem2Character(sld, "blade_03");
			EquipCharacterByItem(sld, "blade_03");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_shturman";
			LAi_SetSitType(sld);
			sld.greeting = "officer_hire";
			SetSelfSkill(sld, 21, 23, 18, 33, 25);
			SetShipSkill(sld, 25, 10, 8, 6, 35, 11, 13, 25, 14);
			SetSPECIAL(sld, 7, 10, 6, 8, 7, 8, 4);
			sld.rank = 5;
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "BasicDefense");
			//sld.quest.officertype = "navigator";
			FreeSitLocator("FortFrance_tavern", "sit4");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit4");
			AddLandQuestMark(characterFromId("Del_shturman"), "questmarkmain");
		break;
		
		//Делюк
		case "Del_Folke_1":
			DelLandQuestMark(npchar);
			dialog.text = "Capitano...";
			link.l1 = "Ho mille domande, ma te ne faccio una sola: come diavolo hai fatto a farti nuovi debiti, se sei sempre stato con me a insegnarmi l’arte marinaresca!";
			link.l1.go = "Del_Folke_2";
		break;
		
		case "Del_Folke_2":
			dialog.text = "Mi vergogno a dirlo, Capitano, ma ho preso in prestito da vari usurai ben prima d’entrare nella tua ciurma. Il mio piano era di restare nell’ombra e sgobbare sulla tua nave finché non avessi messo da parte abbastanza per saldare tutti i debiti. Ma ho commesso la sciocchezza di scendere a terra qui per una certa donna di Saint-Pierre, e le guardie mi hanno preso proprio tra le sue braccia. Non ho fatto nuovi debiti a Martinica, visto che hai già pagato l’ultimo, lo giuro su tutti i santi!";
			link.l1 = "Sei un imbecille, Deluc, e per colpa tua son diventato lo zimbello di tutta St. Pierre!";
			link.l1.go = "Del_Folke_3a";
			link.l2 = "Notevole, Folke. Grazie per la storia.";
			link.l2.go = "Del_Folke_3b";
		break;
		
		case "Del_Folke_3a":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "Che farai, Capitano? Puoi tirarmi fuori dai guai ancora una volta? Trovare un nuovo navigatore non sarà una passeggiata, sai...";
			link.l1 = "Rimani dove sei per ora. Deciderò io. Potrei tornare a far visita al banchiere.";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_3b":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "Che farai, Capitano? Puoi tirarmi fuori dai guai ancora una volta? Trovare un nuovo navigatore non sarà una passeggiata, sai...";
			link.l1 = "Rimani fermo per ora. Deciderò che fare. Potrei tornare dal banchiere.";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_4":
			dialog.text = "Non è che abbia un posto dove andare...";
			link.l1 = "...";
			link.l1.go = "Del_Folke_5";
		break;
		
		case "Del_Folke_5":
			DialogExit();
			
			pchar.questTemp.Del_Rostovshik = true;
			LAi_CharacterDisableDialog(npchar);
			AddLandQuestMark(characterFromId("FortFrance_usurer"), "questmarkmain");
		break;
		
		case "Del_Folke_10":
			dialog.text = "Capitano, grazie. Hai saldato i miei debiti, ma ora te ne devo uno ancora più grande – la mia stessa vita. E te ne sono sinceramente grato! Ti assicuro, non troverai mai un uomo più fedele di me in tutto questo mondo!";
			link.l1 = "Suppongo che certi debiti si saldino solo facendone di nuovi. Torniamo al lavoro, Folke. Il mare ci aspetta con mille faccende.";
			link.l1.go = "Del_Folke_11a";
			link.l2 = "Non scordartelo, Deluc. La prossima volta ti sparo senza pensarci.";
			link.l2.go = "Del_Folke_11b";
			
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			QuestOpenSeaExit()
			sld = CharacterFromID("Del_shturman");
			sld.lifeday = 0;
			
			sld = CharacterFromID("Del_Ohranik");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", -1);
		break;
		
		case "Del_Folke_11a":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "Ai vostri ordini, Capitano!";
			link.l1 = "...";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_11b":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "Aye aye, Capitano!";
			link.l1 = "…";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_12":
			DialogExit();
			EndQuestMovie();
			AddQuestRecord("FolkeDeluc", "3");
			CloseQuestHeader("FolkeDeluc");
			
			ChangeCharacterComplexReputation(pchar, "authority", -2);
			AddCrewMorale(Pchar, -30);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.location = "None";
			npchar.Dialog.CurrentNode = "hired";
			npchar.Payment = true;
			SetCharacterPerk(npchar, "ByWorker");
			DeleteAttribute(npchar, "CompanionDisable");
		break;
		
		//Штурман из таверны. Стандартный диалог, но с некоторыми изменениями (обучение найма для новичков)
		case "Del_shturman":
			dialog.text = "Hai bisogno di un ufficiale, capitano?";
    		Link.l1 = "Un ufficiale? E in che cosa te la cavi, allora?";
    		Link.l1.go = "Del_Node_2";
			Link.l2 = "No, ho già tutto il necessario.";
			Link.l2.go = "Exit";
			NextDiag.TempNode = "Del_OnceAgain";
		break;		
		case "Del_Node_2":
			dialog.text = "Sono il miglior navigatore in queste acque. Me ne intendo ancora un po’ di medicina. E sono pronto a farti un favore e servire al tuo comando.";
			Link.l1 = "E quanto vuoi?";
			Link.l1.go = "Del_price";
			Link.l2 = "E che razza di specialista saresti, tu?";
			Link.l2.go = "Del_ShowParam_exit";
			Link.l3 = "Ahimè, ho già un nocchiere.";
			Link.l3.go = "Exit";
		break;		
		case "Del_price":
			dialog.text = "Penso che possiamo accordarci su 4000 pesos.";
			Link.l1 = "Non ti pare d'esagerare un tantino?";
			Link.l1.go = "Del_trade";
			Link.l2 = "Sono d'accordo. Considerati parte dell'equipaggio.";
			Link.l2.go = "Del_hire";
			Link.l3 = "Non vali questi soldi.";
			Link.l3.go = "exit";
		break;	
		case "Del_ShowParam_exit":
			NextDiag.TempNode = "Del_OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;		
		case "Del_OnceAgain":
			NextDiag.TempNode = "Del_OnceAgain";
			dialog.text = "Hai cambiato idea, capitano? Hai pensato che un nuovo nocchiere non farebbe male?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "Qualcosa del genere. Quanto vuoi?";
                Link.l1.go = "Del_price";
			}
			Link.l2 = "E di che cosa sei capace, tu?";
			Link.l2.go = "Del_ShowParam_exit";
			// boal <--
			Link.l3 = "Ho già tutto il mazzo. Ci si rivede.";
			Link.l3.go = "exit";
		break;		
		case "Del_trade":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 25)
			{
				dialog.text = "D’accordo... Immagino di poter accettare anche 2500 pesos. Che ne dici?";
				Link.l1 = "Ora va meglio. Sei dei nostri.";
				Link.l1.go = "Del_hire";
				pchar.questTemp.Del_SniziliTsenu = true;
			}
			else
			{
				dialog.text = "Mi dispiace, capitano, ma valgo esattamente quanto ho chiesto. Se è troppo per te, vai pure a cercare qualcun altro.";
				Link.l1 = "D’accordo, ti porto con me.";
				Link.l1.go = "Del_hire";				
				Link.l2 = "Ecco cosa farò. Addio.";
				Link.l2.go = "exit";
			}
		break;		
		case "Del_hire":
			if (CheckAttribute(pchar, "questTemp.Del_SniziliTsenu"))
			{
				if (sti(pchar.Money) >= 2500)
				{
					AddMoneyToCharacter(pchar, -2500);
					NextDiag.TempNode = "OnboardSoon";
					dialog.text = "Grazie, capitano. Non vi pentirete della vostra scelta.";
					Link.l1 = "Spero proprio di sì.";
					Link.l1.go = "Del_Exit_hire";
					DeleteAttribute(pchar, "questTemp.Del_SniziliTsenu");
				}
				else
				{
					dialog.text = "Vedo che sei a corto di monete, capitano! Mi dispiace, ma non faccio credito.";
					Link.l1 = "Ah, diavolo!";
					Link.l1.go = "Exit";								
				}
			}
			else
			{
				if (sti(pchar.Money) >= 4000)
				{
					AddMoneyToCharacter(pchar, -4000);
					NextDiag.TempNode = "Del_OnboardSoon";
					dialog.text = "Grazie, capitano. Non vi pentirete della vostra scelta.";
					Link.l1 = "Spero proprio di sì.";
					Link.l1.go = "Del_Exit_hire";
				}
				else
				{
					dialog.text = "Vedo che sei a corto di dobloni, capitano! Mi dispiace, ma qui il credito non si usa.";
					Link.l1 = "Ah, diavolo!";
					Link.l1.go = "Exit";								
				}
			}
		break;
		case "Del_OnboardSoon":			
			NextDiag.TempNode = "Del_OnboardSoon";
			dialog.text = "Finisco solo il mio bicchiere, capitano, poi vado alla nave. Non temete, ci sarò in tempo.";
			Link.l1 = "D’accordo. Se arrivi in ritardo, ti farò pulire il ponte a forza di braccia!";
			Link.l1.go = "Exit";											
		break;
		case "Del_exit_hire":
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.Dialog.CurrentNode = "hired";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NPChar.quest.meeting = true;
			npchar.loyality = 18;
			
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			AddCrewMorale(Pchar, 30);
			QuestOpenSeaExit();
			DelLandQuestMark(npchar);
			pchar.quest.FortfranceJailOff_AddQuestMark.over = "yes";
			if (GetCharacterIndex("FortFranceJailOff") != -1)
			{
				DelLandQuestMark(characterFromId("FortFranceJailOff"));
			}
			sld = CharacterFromID("Folke");
			LAi_CharacterDisableDialog(sld);
			DeleteAttribute(pchar, "questTemp.Del_Deluck");
			DeleteAttribute(pchar, "questTemp.Del_DeluckSvoboda");
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik");
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik_repeat");
			pchar.questTemp.Del_DeluckSiditTurma = true;
			AddQuestRecord("FolkeDeluc", "4");
			CloseQuestHeader("FolkeDeluc");
			DialogExit();
		break;
		
		//Квест "Травля крысы"
		//Капитан корабля Хейтер
		case "TK_Kapitan":
			dialog.text = "Va bene, va bene! Mi arrendo, maledizione!";
			link.l1 = "Ora sei mio prigioniero, ma presto ti ritroverai a Saint-Pierre, con la corda al collo.";
			link.l1.go = "TK_Kapitan_1";
			PChar.quest.TK_Potopil.over = "yes";
		break;
		
		case "TK_Kapitan_1":
			dialog.text = "Eccoci qua... Come hai fatto a sapere dove trovarmi?";
			link.l1 = "Il Governatore mi ha illustrato la situazione di persona.";
			link.l1.go = "TK_Kapitan_2";
		break;
		
		case "TK_Kapitan_2":
			dialog.text = "Che bastardo! Deve aver fiutato le mie intenzioni e ha deciso di fregarmi alla luce del giorno davanti alla sua tana, così da dare l’esempio alle altre ciurme!";
			link.l1 = "Un’altra parola di troppo contro Sua Eccellenza, e il tuo viaggio a Saint-Pierre sarà rapido e indimenticabile.";
			link.l1.go = "TK_Kapitan_3";
		break;
		
		case "TK_Kapitan_3":
			dialog.text = "Eh? Non parlo di vostra eccellenza, compare. Parlo di Jacques il Giusto.\nDannazione, le voci erano vere! Barbazon ha capito che stavo diventando un pericolo e mi ha consegnato al governatore per togliermi dai piedi. Ecco perché sapevi dove trovarmi — e mi hai colto con le braghe calate, ah ah!";
			link.l1 = "Sei fuori di testa. Il Governatore della Martinica non si abbasserebbe mai a trattare con un capo pirata!";
			link.l1.go = "TK_Kapitan_4";
		break;
		
		case "TK_Kapitan_4":
			dialog.text = "Sì, certo. Forse non direttamente, ma secondo me s’è messo d’accordo con Barbazon. Comodo per lui: un pirata pericoloso impiccato, i rapporti belli in ordine e le 'spese per l’operazione militare' giustificate. Ho fatto il servizio, sai? So bene come vanno certe cose. E tu? Sei di guarnigione?";
			link.l1 = "Servo la mia patria, e la conversazione finisce qui. Benvenuto in cella.";
			link.l1.go = "TK_Kapitan_5";
		break;
		
		case "TK_Kapitan_5":
			dialog.text = "Aspetta un attimo, compare. Non sono castigliano, e oggi non ho messo piede in mare per depredare mercanti francesi. Ho dei principi, maledizione! Facciamo un patto, che ne dici?";
			link.l1 = "Non sprecare fiato, pirata. In cella con te.";
			link.l1.go = "TK_Kapitan_7_1";
			link.l2 = "Cerchi di scansare il cappio?";
			link.l2.go = "TK_Kapitan_6";
		break;
		
		case "TK_Kapitan_6":
			dialog.text = "Avevo una pista sicura qui, e ti darò una parte se mi lasci andare. La mia vita vale solo qualche migliaio in argento, ma posso farti guadagnare molto di più – e senza pagare dazio.";
			if (CheckAttribute(pchar, "questTemp.MOT_SharlyBad"))
			{
				link.l1 = "È un’offerta allettante... Ma la pirateria non è proprio il mio punto forte.";
				link.l1.go = "TK_Kapitan_7";
			}
			else
			{
				link.l1 = "Non sono mica un pirata!";
				link.l1.go = "TK_Kapitan_7";
			}
		break;
		
		case "TK_Kapitan_7":
			dialog.text = "Sta a te decidere, compare. Se vuoi diventare un uomo di fortuna o restare un capitano senza un soldo ma pieno di principi. Se cerchi davvero oro e libertà, dovrai sporcarti le mani con un po’ di tutto. Afferra ogni occasione che ti si presenta.";
			link.l1 = "Hai proprio una lingua affilata, tu...";
			link.l1.go = "TK_Kapitan_8";
			link.l2 = "Ehm... Suppongo che ti porterò a Saint-Pierre. Pare sia la cosa giusta da fare.";
			link.l2.go = "TK_Kapitan_7_1";
		break;
		
		case "TK_Kapitan_7_1":
			dialog.text = "Vaffanculo, allora!";
			link.l1 = "...";
			link.l1.go = "TK_Kapitan_Plen";
		break;
		
		case "TK_Kapitan_8":
			dialog.text = "Allora, abbiamo un accordo?";
			link.l1 = "Sì. Dimmi chi è il tuo informatore, e sei libero di andartene.";
			link.l1.go = "TK_Kapitan_9";
		break;
		
		case "TK_Kapitan_9":
			dialog.text = "C’è un inglesotto furbo a bordo dell’Henry, una barca. Sta per concludere la sua piccola traversata commerciale, portando merci dalle piantagioni francesi fino a Willemstad per un bel gruzzolo. Presto salperà dalla Martinica verso Curaçao. È un lavoretto da nulla – niente scorta, e la barca è carica di roba preziosa, ma la difesa fa acqua da tutte le parti. Sta impiegando troppo tempo e le voci iniziano a correre. Il mio consiglio, compare? Non fare il timido in taverna. Offri da bere alla gente del posto, e ti racconteranno più di quanto tu possa immaginare.";
			link.l1 = "Perché senza scorta?";
			link.l1.go = "TK_Kapitan_10";
		break;
		
		case "TK_Kapitan_10":
			dialog.text = "Come diavolo potrebbe un inglese trattare affari in silenzio a Curaçao? Tra Inghilterra e Olanda è guerra aperta, ottenere una licenza commerciale è un inferno e costa un occhio della testa.";
			link.l1 = "Ma non c'è guerra tra la Francia e l'Inghilterra. Quali saranno le conseguenze se attacco una nave neutrale?";
			link.l1.go = "TK_Kapitan_11";
		break;
		
		case "TK_Kapitan_11":
			dialog.text = "Nessuno, se sarai furbo. L’equipaggio senz’altro si vanterà delle tue prodezze alla prima taverna, ma finché non dai troppo fastidio alle navi inglesi o olandesi, starai a galla. Avvicinati all’Henry battendo bandiera francese. Carica i cannoni a mitraglia, accorcia la distanza, issa il Jolly Roger, scarica qualche bordata, poi all’arrembaggio, maledetta! Tutto qui, compare.";
			link.l1 = "Questo lo vedremo. Terrò fede alla mia parola e ti lascerò andare. Non darmi motivo di pentirmene.";
			link.l1.go = "TK_Kapitan_12";
		break;
		
		case "TK_Kapitan_12":
			dialog.text = "Non lo farò. Buona caccia, compare.";
			link.l1 = "...";
			link.l1.go = "TK_Kapitan_Otpustil";
		break;
		
		case "TK_Kapitan_Plen":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.DontRansackCaptain = true;
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = GetCharacter(NPC_GenerateCharacter("TK_Heiter2", "mercen_8", "man", "man", sti(PChar.rank), PIRATE, -1, false, "pirate"));
			sld.name = "Daniel";
			sld.lastname = "Montbars";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto7");
			LAi_SetGroundSitType(sld);
			LAi_CharacterDisableDialog(sld);
			DoQuestCheckDelay("TK_KapitanSidit_1", 0.8);
		break;
		
		case "TK_Kapitan_Otpustil":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetCitizenType(sld);
			sld.lifeday = 0;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			pchar.questTemp.TK_Otpustil = true;
			AddQuestRecord("TravlyaKrys", "4");
			
			SetTimerCondition("TK_GenrihSpawn", 0, 0, 1, false);	
		break;
		
		//Диего и Гийом за столиком по квесту "Встреча с Диего"
		case "VsD_DiegoAndErnat":
			dialog.text = "... Mi occuperò io dei tuoi debiti di gioco. Ehi! Rimettiti in sesto, uomo! O ti ricomponi adesso, o ti faccio tornare in sé a suon di ceffoni.";
			link.l1 = "";
			link.l1.go = "VsD_DiegoAndErnat_2";
			sld = CharacterFromID("GiumDyubua");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "VsD_DiegoAndErnat_2":
			DialogExit();
			StartInstantDialogNoType("GiumDyubua", "VsD_DiegoAndErnat_3", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "VsD_DiegoAndErnat_3":
			dialog.text = "Monsieur, perdonatemi, ma siete davvero d'impiccio.";
			link.l1 = "Sì, certo. Vi auguro una buona giornata, signori.";
			link.l1.go = "VsD_DiegoAndErnat_4";
		break;
		
		case "VsD_DiegoAndErnat_4":
			DialogExit();
			sld = CharacterFromID("Diego");
			LAi_CharacterDisableDialog(sld);
			sld = CharacterFromID("GiumDyubua");
			LAi_CharacterDisableDialog(sld);
		break;
		
		//Гийом Дюбуа по квесту "Встреча с Диего"
		case "VsD_GiumDyubua":
			dialog.text = "Capitano de Maure! Aspetta!";
			link.l1 = "Sì, Tenente?";
			link.l1.go = "VsD_GiumDyubua_2";
			DelLandQuestMark(npchar);
		break;
		
		case "VsD_GiumDyubua_2":
			dialog.text = "Faticavo a starti dietro. C’è stato... un piccolo intoppo, Capitano. Che gran casino!";
			link.l1 = "Fai un respiro e calmati, per carità.";
			link.l1.go = "VsD_GiumDyubua_3";
		break;
		
		case "VsD_GiumDyubua_3":
			dialog.text = "D'accordo, d'accordo. Dimmi, dopo che abbiamo caricato i cannoni, c’è ancora spazio nella stiva?";
			link.l1 = "Non sono ancora pratico di queste faccende, quindi non ne sono del tutto certo, ma suppongo che dovrebbe esserci.";
			link.l1.go = "VsD_GiumDyubua_4";
		break;
		
		case "VsD_GiumDyubua_4":
			dialog.text = "Eccellente! Il Comando desidera sostenere l’operazione a Porto Bello con ogni mezzo possibile, quindi hanno ordinato la consegna di altre duecento misure di polvere da sparo sulla Warlike. Può sembrare poca cosa, ma qualche salva in più può ribaltare la sorte della battaglia!";
			link.l1 = "Benissimo, Tenente. Son pronto a fare la mia parte. Caricate la polvere – non mi dà alcun fastidio.";
			link.l1.go = "VsD_GiumDyubua_5";
		break;
		
		case "VsD_GiumDyubua_5":
			dialog.text = "Grazie, Capitano. Avviserò subito la nostra ciurma di carico. Per fortuna, non hanno ancora finito con la..."+PChar.Ship.Name+"  ancora. Buona fortuna per la tua missione!";
			link.l1 = "Grazie, anche se finora è stato un bel putiferio. Addio, Tenente.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("VsD_GoToCity");
		break;
		
		//Фульк или Алонсо по квесту "Встреча с Диего"
		case "VsD_FolkeAlonso":
			dialog.text = "Dio santo, Capitano! Sia lodato il cielo che siete illeso!";
			link.l1 = "Che diavolo è successo?! Che fine ha fatto la mia nave?!";
			link.l1.go = "VsD_FolkeAlonso_2";
		break;
		
		case "VsD_FolkeAlonso_2":
			dialog.text = "Non lo so, Capitano! Stavo solo salutando una ragazza del posto che ho conosciuto da poco... Maledizione! Eugenie!";
			link.l1 = "È morta, "+npchar.name+"Mi dispiace, ma dobbiamo restare concentrati e vedere se qualcuno dei nostri uomini è stato ferito.";
			link.l1.go = "VsD_FolkeAlonso_3";
		break;
		
		case "VsD_FolkeAlonso_3":
			dialog.text = "Ci conoscevamo appena... Aaah! Maledizione! Rapporto, Capitano: la maggior parte dell’equipaggio era a terra quando c’è stata l’esplosione – per fortuna. I ragazzi si godevano un po’ di libertà prima della prossima lunga traversata. Ma il turno di guardia... Temo che non ci siano superstiti. Guarda qua! Le schegge hanno ferito o fatto fuori gente persino qui, sul molo! È un miracolo che noi due siamo ancora interi.";
			link.l1 = "E la nave? Sta tutta intera?!";
			link.l1.go = "VsD_FolkeAlonso_4";
		break;
		
		case "VsD_FolkeAlonso_4":
			dialog.text = "È davvero così?! Perdona la mia sfacciataggine, Capitano. Non posso giurarci, ma pare che lo scoppio sia stato sul ponte di coperta, non nelle stive. Non vedo fiamme vive e pare che ce la siamo cavata senza gravi danni.";
			link.l1 = "...";
			link.l1.go = "VsD_FolkeAlonso_5";
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("PortPaxAmmoOff"), 0));
			sld.id = "PortPaxAmmoOff_clone";
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, "PortPax_town", "quest", "quest1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "VsD_FolkeAlonso_5":
			DialogExit();
			LAi_SetStayType(pchar);
			sld = CharacterFromID("PortPaxAmmoOff_clone");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "VsD_Komendant";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 3, 0);
		break;
		
		case "VsD_Komendant":
			dialog.text = "Che diavolo succede, Capitano?!";
			link.l1 = "Lo chiedo anch’io, colonnello!";
			link.l1.go = "VsD_Komendant_1";
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				LAi_SetActorType(sld);
				LAi_ActorGoToLocator(sld, "reload", "reload1", "", -1);
			}
		break;
		
		case "VsD_Komendant_1":
			dialog.text = "Sta' attento, de Maure! Hai accettato quest’incarico dalla Marina, ti sei preso carico di cannoni pesanti – proprietà della Corona, d’importanza strategica! Capisci cosa rappresentano questi cannoni per tutta l’operazione?! La tua negligenza ha messo quasi quattrocento uomini e una nave da guerra francese in pericolo! Qui rischi di finire sotto processo per tradimento!";
			link.l1 = "Calma, Colonnello! Per miracolo la mia nave è sopravvissuta, e il vostro carico prezioso è perlopiù intatto... più o meno.";
			link.l1.go = "VsD_Komendant_2";
		break;
		
		case "VsD_Komendant_2":
			dialog.text = "Cosa vuol dire, per lo più?!";
			link.l1 = "Non posso garantire che le duecento misure di polvere da sparo, caricate all’ultimo istante da uno dei vostri luogotenenti, non siano state danneggiate. Dovevano essere caricate per ultime, e probabilmente sono proprio quelle che sono saltate in aria.";
			link.l1.go = "VsD_Komendant_3";
		break;
		
		case "VsD_Komendant_3":
			dialog.text = "Che diavolo sono queste sciocchezze, Charles? Quale tenente? Quale polvere da sparo? Non ho mai dato un simile ordine!";
			link.l1 = "Questo tenente doveva appartenere alla vostra guarnigione. Non ho chiesto il suo nome, ma pareva ben informato sull’operazione.";
			link.l1.go = "VsD_Komendant_4";
		break;
		
		case "VsD_Komendant_4":
			dialog.text = "Ah, maledizione! Pare proprio che anche gli spagnoli abbiano deciso di barare... Mi occuperò io di questa brutta faccenda, Capitano. Tu però hai ancora un compito da svolgere: sei sicuro che la tua nave sia pronta a solcare il mare?";
			link.l1 = "Galleggia ancora, ma ha proprio bisogno di una bella messa a punto.";
			link.l1.go = "VsD_Komendant_5";
			SetMusic("classic_fra_music_day");
		break;
		
		case "VsD_Komendant_5":
			dialog.text = "Niente tempo da perdere, Capitano. Salpa subito e porta a termine la missione. In gioco c’è troppo per indugiare.";
			link.l1 = "Non possiamo avere almeno un giorno, per l'amor di Dio? Il cantiere locale potrebbe fare le riparazioni necessarie! E che ne sarà del mio equipaggio?! Sicuramente ci sono dei feriti!";
			link.l1.go = "VsD_Komendant_6";
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (GetCharacterIndex("Folke") != -1 && CheckPassengerInCharacter(pchar, "Folke"))
			{
				sld = CharacterFromID("Folke");
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.Dialog.Filename = "Enc_Officer_dialog.c";
				sld.Dialog.CurrentNode = "hired";
			}
			else
			{
				sld = CharacterFromID("Alonso");
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
		break;
		
		case "VsD_Komendant_6":
			dialog.text = "Se non te ne fossi accorto, l’arsenale è in fiamme. Stiamo ancora capendo se sia stato fatto apposta o sia solo il risultato della detonazione. Posso solo garantirti che i tuoi feriti saranno curati e che la Corona si farà carico delle spese per seppellire i morti.";
			link.l1 = "Sei serio? Tutto qui quello che sai offrire?";
			link.l1.go = "VsD_Komendant_7";
			sld = CharacterFromID("VsD_Tsyganka");
			ChangeCharacterAddressGroup(sld, "PortPax_town", "reload", "reload5_back");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "VsD_Komendant_7":
			dialog.text = "Capitano, la Francia ha disperatamente bisogno del vostro aiuto. Vi fornirò delle assi, e se sarete astuto nel muovervi, la vostra nave sarà quasi rimessa a nuovo quando approderete in Giamaica.";
			link.l1 = "Perdonami, ma quali assi? E perché la Giamaica?";
			link.l1.go = "VsD_Komendant_8";
			pchar.ship.HP = sti(pchar.ship.HP) / 2;
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) - sti(pchar.ship.Crew.Quantity) / 7;
			AddCharacterGoodsSimple(pchar, GOOD_PLANKS, 100);
		break;
		
		case "VsD_Komendant_8":
			dialog.text = "La tua ciurma può fare riparazioni d’emergenza in mare con le assi – sono la merce principale per aggiustare la nave. E la Giamaica sta proprio vicino a una delle rotte per Porto Bello. Se non perdi tempo, lì potrai finire le riparazioni e arruolare una ciurma al completo.";
			link.l1 = "Benissimo, allora. Salperò all’istante, Colonnello.";
			link.l1.go = "VsD_Komendant_9";
			
			sld = CharacterFromID("PortRoyal_shipyarder");
			sld.TrialDelQuestMark = true;
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("PortRoyal", false);
		break;
		
		case "VsD_Komendant_9":
			DialogExit();
			LAi_SetStayType(pchar);
			
			sld = CharacterFromID("VsD_Tsyganka");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "VsD_Tsyganka";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 3, 0);
			
			sld = CharacterFromID("PortPaxAmmoOff_clone");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "gate_back", "none", "", "", "", -1);
		break;
		
		case "VsD_Tsyganka":
			dialog.text = "Perché tanta fretta, tesoro?";
			link.l1 = "Tesoro, non ho tempo per queste sciocchezze adesso. Non vedi cosa sta succedendo?";
			link.l1.go = "VsD_Tsyganka_1";
		break;
		
		case "VsD_Tsyganka_1":
			dialog.text = "Oh, i guai attuali sono gravi, ma dalla tua mano vedo che altre tempeste si profilano all’orizzonte.";
			link.l1 = "Chiunque lo capirebbe anche senza guardare la mia mano, che tra l’altro è pure guantata. Va bene, farò finta di cascarci: quanto costa oggi scansare la rovina?";
			link.l1.go = "VsD_Tsyganka_2";
		break;
		
		case "VsD_Tsyganka_2":
			dialog.text = "Non ho questo potere, bellimbusto. E anche se lo avessi, non potrei permettermelo. Ma posso comunque darti una mano... con la tua nave. La poverina è proprio malconcia, caro mio.";
			link.l1 = "Non ho mai sentito che la tua gente zingara avesse mire da falegname.";
			link.l1.go = "VsD_Tsyganka_3";
			
			for (i=3; i<=8; i++)
			{				
				sld = CharacterFromID("VsD_MirnyeMan_"+i);
				LAi_SetCitizenType(sld);
			}
			for (i=3; i<=6; i++)
			{				
				sld = CharacterFromID("VsD_MirnyeWoman_"+i);
				LAi_SetCitizenType(sld);
			}
			for (i=1; i<=6; i++)
			{				
				sld = CharacterFromID("VsD_Sold_"+i);
				LAi_SetCitizenType(sld);
			}
			//Возвращаем всё обратно
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			bDisableCharacterMenu = false;
			SetLocationCapturedState("PortPax_town", false);
			Locations[FindLocation("PortPax_town")].locators_radius.quest.quest1 = 1.0;
			Locations[FindLocation("PortPax_town")].locators_radius.patrol.patrol14 = 0.5;
			LocatorReloadEnterDisable("PortPax_ExitTown", "reload2_back", false);
			LocatorReloadEnterDisable("PortPax_ExitTown", "reload1_back", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_Fort")], false);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("VsD_Guard_"+i);
				sld.lifeday = 0;
			}
			//Диего исчезает
			sld = CharacterFromID("Diego");
			LAi_CharacterEnableDialog(sld);
			sld.location = "None";
			//Верфь закрывается
			LocatorReloadEnterDisable("PortPax_Town", "reload5_back", true);
			SetTimerCondition("VsD_VerfOtkryt", 0, 0, 7, false);
			//Труп предателя в джунглях
			PChar.quest.VsD_TrupPredatelya.win_condition.l1 = "location";
			PChar.quest.VsD_TrupPredatelya.win_condition.l1.location = "PortPax_ExitTown";
			PChar.quest.VsD_TrupPredatelya.win_condition = "VsD_TrupPredatelya";
			SetTimerCondition("VsD_TrupPredatelya_3", 0, 0, 60, false);
		break;
		
		case "VsD_Tsyganka_3":
			dialog.text = "Tu, caro mio, di certo non sei un maestro carpentiere. Credi forse che solo con delle assi si ripari una nave? Ti saranno solo di zavorra, se non hai un vero mastro d'ascia...";
			link.l1 = "O?";
			link.l1.go = "VsD_Tsyganka_4";
		break;
		
		case "VsD_Tsyganka_4":
			dialog.text = "Vi è un potente amuleto, assai venerato dalle genti di queste isole. Il legno si piega al suo comando, e persino chi non ha mai toccato scalpello diventa mastro d'ascia indossandolo. È tuo per soli mille pesos, caro mio.";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Benissimo, affare fatto. Ho bisogno di tutta l’aiuto possibile.";
				link.l1.go = "VsD_Tsyganka_Da";
			}
			link.l2 = "Non ho tempo per le tue stregonerie. Vai in pace, strega, e non ficcare il naso dove non ti compete.";
			link.l2.go = "VsD_Tsyganka_Net";
			npchar.lifeday = 0;
		break;
		
		case "VsD_Tsyganka_Net":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Trial", "7_1");
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "VsD_Tsyganka_Da":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Trial", "7_1");
			AddCharacterExpToSkill(pchar, "Repair", 20);
			AddMoneyToCharacter(pchar, -1000);
			GiveItem2Character(PChar, "obereg_1");
			Log_info("You have received Amulet 'Teredo'");
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Ascolta, io sono un rispettabile cittadino di questa città. Ti consiglio di non andare in giro con la lama sguainata come un volgare brigante.","Signore, vi prego, la legge è chiara: nessun uomo può girare per la città con la lama sguainata.");
			link.l1 = LinkRandPhrase("D'accordo.","D’accordo.","Come desideri...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

// Даниэль Хоук - жена Натаниэля Хоука
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	bool bOk1, bOk2;
	string 	sTemp, sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time": //первая встреча - знакомство
			PlaySound("Voice\English\saga\Denny Hawk-02.wav");
			dialog.text = "Aspetta, bellimbusto! Mi sa che dobbiamo fare due chiacchiere.";
			link.l1 = "Ci conosciamo, forse? In ogni caso, per una dama ho sempre qualche ora da perdere.";
			link.l1.go = "meeting";			
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			PlaySound("Voice\English\saga\Denny Hawk-01.wav");
			dialog.text = "Non fare ancora progetti, Capitano. Cercati una ragazzina più giovane e sprovveduta per passare qualche ora in più. Ho degli affari da proporti. Sono sposata, in realtà. Mio marito si chiama Nathaniel Hawk.";
			link.l1 = "Ma guarda un po’! Allora dev’esser lei... eh, Dannie Hawk, di cui parlava messer Svenson.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "In carne ed ossa. Sì, so bene che il Diavolo della Foresta non ha grande stima di me, il sentimento è reciproco, ma avrà pur dovuto avvertirti che porto la sciabola non solo per bellezza. Dunque, veniamo al sodo, figliolo!\nHo seguito Svenson e le sue frequentazioni per un po’, visto che è stato lui a mandare mio marito a crepare nella giungla. Pensavo fosse in combutta con Jackman, ma ora vedo che non è così. Ero nascosta sotto la finestra durante la vostra chiacchierata. Non ho potuto origliare tutto, ma ho raccolto parecchie informazioni utili.\nHai davvero intenzione di ritrovare mio marito e dare una lezione a quel bastardo di Jackman? O erano solo chiacchiere da salotto?";
			link.l1 = "Spiare non è da gentildonna, Madame Hawk. Ma ti perdonerò se ti rivolgi a me con maggiore rispetto. Che io cerchi Hawk o meno, riguarda solo me. Parla se hai qualcosa di utile da dirmi, altrimenti lasciami in pace. Non lo ripeterò due volte.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Ah-ah, che testa calda! Su, Capitano... Il mio caratteraccio non ti mette proprio a tuo agio, eh? Vedo che non sei un codardo e conosci il tuo valore. Dunque... facciamo conoscenza. Ti prometto che starò attento a come ti parlo. Tu hai bisogno di me, e io di te. Abbiamo lo stesso obiettivo. Prendimi con te tra la ciurma e non te ne pentirai. Ti servirò con lealtà e onore finché non troveremo Nathan, te lo giuro.";
			link.l1 = "Considerati dei nostri... Dannie. Svenson mi ha detto che già stavi cercando tuo marito. Hai scoperto qualcosa di interessante?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Non molto, ma abbastanza per accusare Jackman di menzogna. Quel bastardo ha detto che le guardie della miniera, quelle che il mio Nathan ha affrontato, non prendevano prigionieri. E anche se è vero che nessuno ha visto il cadavere di mio marito sulla baia, come avrebbero potuto, visto che in realtà fu portato vivo alle miniere come prigioniero. Occhio di Serpente, uno stregone dei Miskito, l’ha trovato là.\nE gli ha organizzato la fuga. Ma dove sia ora mio marito, resta un mistero. Lo stregone borbottava qualcosa su un certo Kukulcan che se l’è mangiato, ma non ci ho capito nulla. E poi, il pelle rossa mi ha fatto capire bene che per lui le donne bianche sono solo uno scherzo. Parla tu con lui, magari sarà più loquace con te.";
			link.l1 = "Almeno qualcosa! Queste notizie mi sollevano il cuore. Dove posso rintracciare questo indiano?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "C’è un villaggio nel cuore della giungla. Dobbiamo sbarcare nella Baia di Amatique e andare verso ovest attraverso la giungla. Ti mostrerò la strada, se non la trovi da solo. Non lontano dal villaggio si trova un idolo di pietra che quei selvaggi venerano come fosse un dio. Ci sono stato più volte. Nulla di straordinario, davvero. Solo una rozza pietra coperta di muschio.";
			link.l1 = "Interessante. Va bene, andiamo. Parleremo con lo stregone e poi vedremo il da farsi. Sei pronto?";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Certo! Naturalmente, sono pronto. Da quando ho lasciato Maroon Town, non ho fatto altro che viaggiare. E poi, non ho alcuna intenzione di essere solo uno dei tuoi passeggeri.";
			link.l1 = "Va bene. Andiamo sulla mia nave.";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Ai vostri ordini, Capitano!";
			link.l1 = "...";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.OfficerPrice = sti(pchar.rank)*700;
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.CompanionDisable = true; //нельзя в компаньоны - чтобы не утонула
			LAi_SetImmortal(npchar, false);
			npchar.HalfImmortal = true; //чтобы не убили в сухопутном бою
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Danielle_officer";
			npchar.HoldEquip = true; // лесник -  не отдавать саблю и пистоль																					 
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("BaronReturn", "2");
			Saga_CreateSnakeEye();
			//выбираем амулеты
			pchar.questTemp.Saga.BaronReturn.Indian = "indian_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Amulet = "amulet_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Obereg = "obereg_"+(rand(10)+1);
			// на локацию с истуканом
			npchar.quest.talk = "dolly";
			pchar.quest.Saga_Dolly.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly.function = "Saga_DannyTalk";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.greeting = "danny_1";
		break;
		
		// у истукана в джунглях
		case "Dolly":
			dialog.text = ""+pchar.name+"Avanti! Ti mostro l’idolo di pietra di cui parlava lo stregone indiano. Un semplice pilastro di pietra, niente di più. Andiamo!";
			link.l1 = "...";
			link.l1.go = "Dolly_1";
		break;
		
		case "Dolly_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "item", "torch1", "Saga_ShowDolly", -1);
		break;
		
		case "Dolly_2":
			dialog.text = "Ehi! Guarda un po', è solo una statua di pietra. Niente di speciale...";
			link.l1 = "Capisco... Però quella figura in cima mette quasi un po’ i brividi, non trovi? ";
			link.l1.go = "Dolly_3";
		break;
		
		case "Dolly_3":
			dialog.text = "Tutte le statue indiane fanno paura e sembrano maledette. Ne ho già viste di simili, son tutte uguali. Comunque, avanti, il villaggio è vicino!";
			link.l1 = "Andiamo!";
			link.l1.go = "Dolly_4";
		break;
		
		case "Dolly_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Danielle_officer";
		break;
		
		// у мискито
		case "SnakeEye":
			dialog.text = "Allora, che ne dici, "+pchar.name+"? Che ti ha raccontato quel pellerossa ciarlatano? Hai capito qualcosa dalle sue parole da filosofo?";
			link.l1 = "Stavi di nuovo origliando, Dannie?";
			link.l1.go = "SnakeEye_1";
		break;
		
		case "SnakeEye_1":
			dialog.text = "Beh... un pochino. Sai, noi donne siam fatte così. Ma devi capire: m’inquieto per mio marito, tutto qui. Gli voglio davvero bene. E allora? Se ascolto di nascosto, che male c’è? Insomma, hai scoperto qualcosa di buono?";
			link.l1 = "Sto cercando di ricordare... Non era facile capire quell’occhio di serpe. Però, pare che l’idolo che abbiamo visto entrando nel villaggio sia una sorta di portale magico, capace di teletrasportare la gente.";
			link.l1.go = "SnakeEye_2";
		break;
		
		case "SnakeEye_2":
			dialog.text = "";
			link.l1 = "Non guardarmi così. Non è stata una mia idea e per ora la mia testa è tutta intera. Mi hai chiesto cosa mi ha detto lo stregone, ecco che te lo dico.";
			link.l1.go = "SnakeEye_3";
		break;
		
		case "SnakeEye_3":
			dialog.text = "Perdonami, ti prego. Non ti fisserò più così. Continua pure.";
			link.l1 = "Disse che quando Nathan fu quasi preso dai suoi inseguitori, l’indiano gli mostrò la statua come via di salvezza, chiamandola Kukulcan e dicendo che aveva inghiottito Nathan vivo per poi risputarlo altrove. In parole povere, pare che la statua abbia teletrasportato Nathan.";
			link.l1.go = "SnakeEye_4";
		break;
		
		case "SnakeEye_4":
			dialog.text = "Dio, che diavolo... Io e Nathan ci siamo già trovati in un pasticcio simile, e ora ci risiamo. Ne abbiamo già avute a sufficienza di avventure con quel tempio indiano pieno di magie Maya...";
			link.l1 = "Cosa hai appena detto?";
			link.l1.go = "SnakeEye_5";
		break;
		
		case "SnakeEye_5":
			dialog.text = "Ah, non è nulla, "+pchar.name+", non importa. Solo ricordi della mia giovinezza focosa. Ma come ha fatto Nathan a fare una cosa simile? Intendo, a teletrasportarsi? Siamo appena stati vicino a quell’idolo, ci giravo intorno e lo toccavo... è solo una dannata pietra!";
			link.l1 = "Occhio di Serpente mi ha detto che l'idolo prende vita a mezzanotte. Solo allora comincia a brillare d’oro, quando lo spirito di Kukulcan ci entra dentro. È quello il momento in cui non dovresti toccarlo. O forse proprio allora dovresti...";
			link.l1.go = "SnakeEye_6";
		break;
		
		case "SnakeEye_6":
			dialog.text = "Inquietante... E adesso? Aspettiamo la mezzanotte e poi ci infiliamo nella giungla?";
			link.l1 = "No. Lo stregone diceva che l'idolo non solo trasporta chiunque, ma si nutre anche delle loro vite. Da quel che ho capito, intendeva che prosciuga la salute. Occhio di Serpente è passato per queste statue tre volte e ogni volta s'è curato con qualche strana pozione dopo il viaggio.";
			link.l1.go = "SnakeEye_7";
		break;
		
		case "SnakeEye_7":
			dialog.text = "Gli hai già chiesto questa pozione?";
			link.l1 = "Certo. Ma anzitutto, sono rimaste solo tre fiasche e, in secondo luogo, lui pretende tre amuleti in cambio.";
			link.l1.go = "SnakeEye_8";
		break;
		
		case "SnakeEye_8":
			dialog.text = "Che ne dici di farlo senza la pozione? Andiamo alla statua di notte e tocchiamola...";
			link.l1 = "Troppo rischioso. Ammetto che l'indiano ha qualche rotella fuori posto e forse ci sta prendendo in giro, ma non mi pare uno squilibrato, quindi gli credo. Mi pare che mi raccontavi qualcosa sulla magia indiana... Dubiti che esista davvero?";
			link.l1.go = "SnakeEye_9";
		break;
		
		case "SnakeEye_9":
			dialog.text = "Sì, ero io. Non ne dubito, l'ho visto coi miei occhi. Dunque, suppongo tu abbia ragione, non vale la pena rischiare.";
			link.l1 = "Esatto. Per questo prima troveremo gli amuleti, poi prenderemo quella miracolosa pozione dallo stregone e andremo alla statua. Andrò io. Da solo.";
			link.l1.go = "SnakeEye_10";
		break;
		
		case "SnakeEye_10":
			dialog.text = "Perché mai? E io che c’entro?";
			link.l1 = "Resterai sulla mia nave e comanderai tu mentre sarò via. Non provare nemmeno a discutere, Dannie. Ci sono solo tre fiasche della pozione. Nessuno sa dove porti davvero il portale, se quel dannato sciamano ha ragione e questa roba funziona davvero. Magari nemmeno riuscirò a trovare Nathan lì.";
			link.l1.go = "SnakeEye_11";
		break;
		
		case "SnakeEye_11":
			dialog.text = "Sei proprio come Nathan. Tutti gli uomini sono uguali... Va bene, d’accordo.";
			link.l1 = "È bene che ci intendiamo. Andiamo, dobbiamo trovare gli amuleti.";
			link.l1.go = "Dolly_4";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
				if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6) {
					AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
				}
			}
		break;
		
		// перед походом к истукану
		case "teleport":
			dialog.text = "E allora? Hai preso le pozioni?";
			link.l1 = "Sì. Ho preso le pozioni e delle istruzioni. Ora non resta che andare all’idolo a mezzanotte e toccarlo.";
			link.l1.go = "teleport_1";
		break;
		
		case "teleport_1":
			dialog.text = "Hai paura?";
			link.l1 = "Sì. Temo che lo stregone sia solo un pazzo e che non ci sarà nessuna maledetta teletrasportazione.";
			link.l1.go = "teleport_2";
		break;
		
		case "teleport_2":
			dialog.text = "Ebbene, ebbene... Non sei affatto spaventato? Neanche un briciolo?";
			link.l1 = "Dannie, non insistere... Se proprio vuoi saperlo, d’accordo, lo ammetto: non mi sento affatto sicuro di me.";
			link.l1.go = "teleport_3";
		break;
		
		case "teleport_3":
			dialog.text = "Verrò con te.";
			link.l1 = "Vuoi ricominciare a litigare? Pensavo che avessimo già un accordo...";
			link.l1.go = "teleport_4";
		break;
		
		case "teleport_4":
			dialog.text = "Hai capito male. Starò semplicemente nei paraggi. Devo assicurarmi che la statua funzioni... o che non funzioni affatto.";
			link.l1 = "Non ho nulla in contrario. Ma non ti azzardare a seguirmi se la statua dovesse ‘divorarmi’. Mi hai sentito?";
			link.l1.go = "teleport_5";
		break;
		
		case "teleport_5":
			dialog.text = "Sì. Prometto che non ti seguirò... Capitano.";
			link.l1 = "Bene. E, Dannie, pare che tu non sia proprio la strega che tutti dipingono.";
			link.l1.go = "teleport_6";
		break;
		
		case "teleport_6":
			dialog.text = "Non mi conosci poi tanto bene, "+pchar.name+" Ma lasciamo da parte questo discorso per ora.";
			link.l1 = "Non perdiamo tempo... Dobbiamo prepararci per la nostra scorribanda notturna!";
			link.l1.go = "Dolly_4";
			npchar.quest.talk = "shadowstar";
			pchar.quest.Saga_Dolly1.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly1.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly1.win_condition.l2 = "Hour";
			pchar.quest.Saga_Dolly1.win_condition.l2.start.hour = 0.00;
			pchar.quest.Saga_Dolly1.win_condition.l2.finish.hour = 1.00;
			pchar.quest.Saga_Dolly1.function = "Saga_DannyTalk";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
				if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6) {
					AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
				}
			}
		break;
		
		// перед телепортацией
		case "shadowstar":
			dialog.text = "Guarda, "+pchar.name+"Per tutti i santi, giuro che c’è una strana luce sopra la statua!";
			link.l1 = "Sembra che lo stregone non mentisse. E, se le tenebre non mi ingannano, la cima della statua non pare più tanto di pietra.";
			link.l1.go = "shadowstar_1";
			QuestPointerDelLoc("Pearl_Jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("Pearl_Jungle_03", "camera", "dolly");
		break;
		
		case "shadowstar_1":
			dialog.text = "Proprio così... Sembra fatta d’oro massiccio! Incredibile!";
			link.l1 = "È giunta l’ora, Dannie. Augurami buona fortuna e incrocia le dita per me. Non avvicinarti all’idolo! Resta qui.";
			link.l1.go = "shadowstar_2";
		break;
		
		case "shadowstar_2":
			dialog.text = "Buona fortuna, "+pchar.name+" Speriamo che funzioni... Hai preparato il filtro dello sciamano?";
			link.l1 = "Sì, ce l'ho qui. Tutto andrà bene, Dannie. Ebbene, mi butto! (Premi T per attivare l'idolo)";
			link.l1.go = "shadowstar_3";
		break;
		
		case "shadowstar_3":
			DialogExit();
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestReloadToLocation(pchar.location, pchar.location.group, pchar.location.locator, "");
		break;
		
		// прибыл назад 
		case "arrive":
			dialog.text = "A-a-ah?! Maledizione! Che razza di mostro sei, dannazione?! Va’ al diavolo! Ho visto bestie peggiori in vita mia, persino Van der Decken in persona! Ora ti faccio vedere io, maledetto!";
			link.l1 = "(piano) Dannie, aspetta! Fermati! Adesso!";
			link.l1.go = "arrive_1";
		// belamour legendary edition -->
			link.l2 = "(sommessamente) Van der Decken? Ah-ah-ah! Quello scarafaggio già mi serve! Ora tocca a te! Inginocchiati davanti a me, fedele servitore! Comanderai il mio esercito di dannati!";
			link.l2.go = "arrive_1a";
			SetMusic("music_jungle");
			if (CheckCharacterItem(pchar, "Ultimate_potion"))
			{
				pchar.systeminfo.NoNotifications = true;
				RemoveItems(pchar, "Ultimate_potion", 1);
				DeleteAttribute(pchar,"systeminfo.NoNotifications");
				notification("A Comanche potion is used", "None");
				LAi_SetCurHPMax(PChar);
				AddCharacterHealth(pchar, 50);
				DeleteAttribute(pchar, "chr_ai.poison");
				notification("You are feeling that your health is restored!", "None");
				//Log_Info("A Comanche potion is used");
				//Log_Info("You are feeling that your health is restored!");
				//PlaySound("Ambient\Tavern\glotok_001.wav");
				PlaySound("Ambient\Horror\Fear_breath_01.wav");
			}
		break;
		
		case "arrive_1a":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = "A-A-A-A-A-A-A-A-A-A-A-A-A! Vai via! Non può succedere proprio adesso!";
			link.l1 = "(piano) Dannie, aspetta! Fermati! Adesso!";
			link.l1.go = "arrive_1";
		break;
		// <-- legendary edition
		case "arrive_1":
			dialog.text = "Eh?! Che hai detto?! Dannie?";
			link.l1 = "(sommessamente) Fermati subito! Ferma la tua sciabola! Lascia che mi tolga questa cosa!";
			link.l1.go = "arrive_2";
		break;
		
		case "arrive_2":
			dialog.text = "Maledetto, tu suoni come un vero mostro... "+pchar.name+"?! ";
			link.l1 = "(sottovoce) Oh-oh... Ma davvero!";
			link.l1.go = "arrive_3";
		break;
		
		case "arrive_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			DoQuestCheckDelay("Pearl_TeleportArrive_1", 1.5);
		break;
		
		case "arrive_4":
			dialog.text = "Per mille balene, quasi m’hai fatto crepare dalla paura! Ancora un attimo e ti tagliavo in due con la sciabola!";
			link.l1 = "Ho visto... e perché sei così focoso, eh?";
			link.l1.go = "arrive_5";
		break;
		
		case "arrive_5":
			dialog.text = "Questo sono io... Ah, il mio cuore batte ancora come un tamburo impazzito...";
			link.l1 = "Dannie, dove siamo ora? Non lontano dal villaggio dei Miskiti, giusto?";
			link.l1.go = "arrive_6";
		break;
		
		case "arrive_6":
			dialog.text = "Dove altro potevamo finire! È proprio questa la statua che ti ha fatto sparire. Che spettacolo! Me lo ricorderò finché campo.";
			link.l1 = "Capisco, quindi sei rimasto qui ad aspettarmi tutto questo tempo?";
			link.l1.go = "arrive_7";
		break;
		
		case "arrive_7":
			dialog.text = "Dimmi, che altro dovevo fare? Dopo che la statua ti aveva inghiottito, potevo solo sperare che un giorno ti risputasse fuori. Inoltre, Occhio di Serpente aveva detto che era la cosa più probabile.\nSono vissuto coi Miskito e ho sorvegliato l’idolo ogni giorno. Ma perché stiamo cianciando di queste fandonie? Dimmi! Cos’è successo laggiù? Dove sei stato?";
			link.l1 = "Dannie, questa storia è lunga come una traversata oceanica, ne ho viste di tutti i цветов... Ma per toglierti il peso dal cuore, ti dirò che ho trovato Nathaniel!";
			link.l1.go = "arrive_8";
		break;
		
		case "arrive_8":
			dialog.text = "Hai trovato Nathan? Dov’è finito? E come sta?!";
			link.l1 = "Non ti mentirò - è vivo, ma versa in pessime condizioni. Non ha avuto la pozione dei Comanche e l'idolo gli ha succhiato via tutta la forza. Ora giace in una cabina di qualche vecchio relitto sulla strana Isola delle Navi Abbandonate. Anche io sono stato trasportato lì, quindi il Serpente Occhio aveva ragione!";
			link.l1.go = "arrive_9";
		break;
		
		case "arrive_9":
			dialog.text = "Povero Nathan... Dov’è quell’isola maledetta? Come ci arriviamo, eh?! Solo passando per l’idolo? Proverò a comprare ogni singola pozione dai Miskito e ci andrò stanotte! In qualche modo ce la farò...";
			link.l1 = "Fermati! Aspetta! Nathan è malato, ma la sua vita non è in pericolo. Un ragazzo si sta già occupando di lui e lo nutre. Se passi per l’idolo, rovinerai la tua salute e l’isola è davvero pericolosa. È una follia rischiare così tanto!";
			link.l1.go = "arrive_10";
		break;
		
		case "arrive_10":
			dialog.text = "Allora che proponi? Restare con le mani in mano mentre Nathan soffre o magari crepa?";
			link.l1 = "Pianta quell’isteria. Primo, ti ho detto che Nathan è malato, ma non sta crepando. Ci ho parlato io. Secondo, salperò verso l’isola e tu verrai con me.";
			link.l1.go = "arrive_11";
		break;
		
		case "arrive_11":
			dialog.text = "Sai dove si trova quell’isola?";
			link.l1 = "Certo che sì! Ho trovato laggiù non solo Nathan, ma anche quel vecchio squalo di Dodson. Ho pure messo le mani sulle coordinate approssimative dell’Isola e sulle rotte per schivare gli scogli che la circondano. Ora si torna alla mia nave e si salpa dritti verso Blueweld...";
			link.l1.go = "arrive_12";
		break;
		
		case "arrive_12":
			dialog.text = "Per quale motivo? Perché non possiamo salpare subito verso l'Isola?";
			link.l1 = "Dannie, devo organizzare una spedizione. Sull’Isola manca terribilmente il vettovagliamento, quindi comprerò tutto il cibo che riesco a trovare. Poi dovrò scegliere una nave adatta, ché non tutte riusciranno a passare i maledetti scogli dell’Isola. E prima vorrei pure scambiare due parole con Svenson...";
			link.l1.go = "arrive_13";
		break;
		
		case "arrive_13":
			dialog.text = "";
			link.l1 = "Non ci vorrà molto a prepararci. L'Isola non è lontana da qui, si trova a nord-ovest dell'Avana, verso est rispetto al Golfo del Messico.";
			link.l1.go = "arrive_14";
		break;
		
		case "arrive_14":
			dialog.text = "D'accordo... allora facciamolo. Hai trovato Nathan, ed è la cosa più importante. Grazie! Sta male laggiù?";
			link.l1 = "Beh... è malato. E oltre a questo è anche abbattuto e disperato. Sente la tua mancanza. E sì, Nathan mi ha chiesto di dirti che ti ama moltissimo.";
			link.l1.go = "arrive_15";
		break;
		
		case "arrive_15":
			dialog.text = "(asciugandosi una lacrima) Vecchio sciocco! Non mi dava mai retta... "+pchar.name+", andiamo alla tua nave! Voglio salpare laggiù il prima possibile!";
			link.l1 = "Certo, Dannie. E ti racconterò delle mie avventure. Andiamo!";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "9");
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", false); // пускать офицеров в локу телепорта
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			setCharacterShipLocation(pchar, "Shore9"); // калеуче
			setWDMPointXZ("Shore9"); // корабль в бухту Аматике
			bNoEatNoRats  = false; // еду и крыс включить
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog");
		break;
		
		// в LSC у причала
		case "nathaniel":
			dialog.text = "Non ho mai visto un posto simile prima d’ora. L’intera isola è fatta di navi!";
			link.l1 = "Te l'ho già detto, Dannie...";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "Ma ora posso vederlo coi miei occhi. Comunque, dimmi dove trovo Nathaniel?";
			link.l1 = "È dentro una delle navi. Ma dovrai nuotare fino a lì.";
			link.l1.go = "nathaniel_2";
		break;
		
		case "nathaniel_2":
			dialog.text = "Non m’importa un accidente. Dimmi solo come arrivo a questa nave.";
			link.l1 = "Dannie, datti una calmata. Tu e Nathan avete già aspettato abbastanza, portate ancora un po' di pazienza! Vi ci guiderò io, da soli non lo trovereste mai. Non voglio che incappiate nei Narvali o nei Rivados: vi mettereste subito a litigare con loro e finirebbe in rissa.";
			link.l1.go = "nathaniel_3";
		break;
		
		case "nathaniel_3":
			dialog.text = "Bene, andiamo allora. Ti seguirò.";
			link.l1 = "Non dimenticare che ci toccherà nuotare parecchio.";
			link.l1.go = "nathaniel_4";
		break;
		
		case "nathaniel_4":
			dialog.text = "Va bene, ci penso io.";
			link.l1 = "Sono lieto di sentirlo... Presto rivedrai tuo marito!";
			link.l1.go = "nathaniel_5";
		break;
		
		case "nathaniel_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Danny_Natan.win_condition.l1 = "location";
			pchar.quest.LSC_Danny_Natan.win_condition.l1.location = "FernandaDiffIndoor";
			pchar.quest.LSC_Danny_Natan.function = "LSC_DannyAndNatan";
			AddQuestRecord("LSC", "15");
			// следующая нода
			if (CheckCharacterItem(pchar, "keys_skel")) // идёт Оле
			{
				sld = characterFromId("Ole");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				if (GetCharacterIndex("Mary") != -1) // иначе Мэри
				{
					sld = characterFromId("Mary");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else // иначе завершение
				{
					chrDisableReloadToLocation = false;
					LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				}
			}
		break;
		
		case "nathaniel_6":
			dialog.text = "Nathaniel... Nathan! Maledizione! Amore mio...";
			link.l1 = "...";
			link.l1.go = "nathaniel_7";
		break;
		
		case "nathaniel_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("LSC_DanielleRomantic", 15.0);
		break;
		
		case "nathaniel_8":
			dialog.text = "Gesù, guarda un po’ come ti sei ridotto... Perché ti sei fatto questo, maledizione?!.. (piange) Non mi dai mai retta, mai! Ti avevo detto di non ficcare il naso in quella selva! Ma ci sei andato lo stesso! Perché, Nathan?!";
			link.l1 = "Dannie... Mi dispiace. Non avevo scelta, lo sai bene...";
			link.l1.go = "nathaniel_9";
		break;
		
		case "nathaniel_9":
			sld = characterFromId("Blaze");
			dialog.text = "Lo so! Oh Dio, tesoro... cosa ti è successo! (tra le lacrime) Va tutto bene, amore mio, andrà tutto bene... sono qui ora. Ti porteremo dai Miskito, da Occhio di Serpente."+sld.name+"  mi ha detto che lo stregone potrà guarirti. Abbiamo una nave... Andrà tutto bene!";
			link.l1 = "Dannie, tesoro mio... amore mio! Solo la tua presenza mi ha guarito a metà. Andremo dove vorrai tu. Se vuoi andare da Occhio di Serpente, allora andremo da lui.";
			link.l1.go = "nathaniel_10";
		break;
		
		case "nathaniel_10":
			dialog.text = "Prepara le tue cose. Ah, che stupido sono... Non c’è nulla da mettere via, solo bottiglie vuote. Nathan...";
			link.l1 = "Dannie...";
			link.l1.go = "nathaniel_11";
		break;
		
		case "nathaniel_11": // перекидываем pchar
			DialogExit();
			LAi_SetStayType(pchar);
			DeleteAttribute(pchar, "GenQuest.MusicContinue");
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "nathaniel_12":
			dialog.text = ""+pchar.name+" ... perdona me e Nathan per quella sceneggiata.";
			link.l1 = "Dannie! Perdonarti? Ma per cosa mai? Va tutto bene. Ti vergogni forse dei tuoi sentimenti?";
			link.l1.go = "nathaniel_13";
		break;
		
		case "nathaniel_13":
			dialog.text = "No, non sono io... È solo che...";
			link.l1 = "Nessuno saprà mai nulla di questa faccenda. Te lo giuro. E nessuno verrà mai a sapere che fine ha fatto Nathan. I pirati di Maroon Town vedranno un Nathaniel Hawk forte e temibile!";
			link.l1.go = "nathaniel_14";
		break;
		
		case "nathaniel_14":
			dialog.text = "Grazie, "+pchar.name+"! Ti sono debitrice... Porterò mio marito alla nave. Non temere, ce la farò da sola, ricordo la strada. Lo metterò a letto e resterò con lui. Salperemo per Occhio di Serpente appena avrai finito quello che devi fare qui. Ho fede che Nathan saprà guarirlo.";
			link.l1 = "Va bene, Dannie. Tanto non ci fermeremo qui a lungo. Sei sicuro di non aver bisogno d'aiuto?";
			link.l1.go = "nathaniel_15";
		break;
		
		case "nathaniel_15":
			dialog.text = "Sono certa. Arriveremo alla nave. Non temere, non lascerò che mio marito crepi!";
			link.l1 = "Dannie, sei... meravigliosa!";
			link.l1.go = "nathaniel_16";
		break;
		
		case "nathaniel_16":
			dialog.text = "(asciugandosi una lacrima) Va’... vattene, "+pchar.name+"... e per carità, non perdere tempo qui!";
			link.l1 = "...";
			link.l1.go = "nathaniel_17";
		break;
		
		case "nathaniel_17":
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableCharacterMenu = false;//лоченые интерфейсы
			EndQuestMovie();
			DialogExit();
			pchar.quest.LSC_NatanPassenger.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_NatanPassenger.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_NatanPassenger.function = "LSC_SetNatanPassenger";
			pchar.quest.Saga_NatanTreatment.win_condition.l1 = "location";
			pchar.quest.Saga_NatanTreatment.win_condition.l1.location = "Miskito_village";
			pchar.quest.Saga_NatanTreatment.function = "Saga_NatanPrepareTreatment";
			pchar.questTemp.Saga.BaronReturn = "shamane";
			AddQuestRecord("BaronReturn", "11");
			// открываем вход к Мэри
			if (GetCharacterIndex("Mary") != -1)
			{
				for (i=0; i<=3; i++)
				{
					LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, false);
				}
			}
			else
			{
				bQuestDisableMapEnter = false; //открыть карту
				DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			}
		break;
		
		case "treatment":
			dialog.text = "E allora? Guarirà mio marito? Dimmi che lo guarirà!";
			link.l1 = "Dannie, Nathan dovrà restare qui. Da solo. Lo stregone ha chiesto di non disturbare i suoi riti. Vale anche per te. Ha promesso che guarirà Nathaniel entro un mese.";
			link.l1.go = "treatment_1";
		break;
		
		case "treatment_1":
			dialog.text = "Sai, "+pchar.name+", ora finalmente posso respirare di nuovo liberamente. Sono convinta che lo stregone restituirà mio marito al suo stato normale. Lascio Nathan qui senza esitazione, perché se Occhio di Serpente non riuscirà a curarlo – allora nessuno potrà farlo.";
			link.l1 = "Andrà tutto bene, Dannie. Occhio di Serpente non mi ha mai mentito. Mi fido di lui.";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "Anch’io. Rimarrò con te per un po’, "+pchar.name+", sei d’accordo con questo? Dobbiamo ancora mettere le mani su quel bastardo di Jackman, alla fin fine è lui la causa di tutte le nostre sventure. Ha organizzato l’agguato! Ha preso il posto di Nathan a Maroon Town! E s’è fregato la nostra fregata 'Centurion'!";
			link.l1 = "D'accordo. Dobbiamo occuparci di Jackman. Nessuno di noi potrà dormire sonni tranquilli finché quel cane non sarà crepato. Ma mandarlo all’inferno non sarà una passeggiata.";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Shark Dodson";
			else sTemp = "Marcus Tyrex";
			dialog.text = "Hai qualche piano, "+pchar.name+"?";
			link.l1 = "Non ancora. Devo andare da Jan Svenson e chiedergli consiglio. Facciamo una cosa alla volta, dobbiamo promuovere "+sTemp+" prima dal capo della Fratellanza della Costa. Quindi, dobbiamo ottenere il voto di ogni barone pirata per farlo.";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = "Va bene, andiamo da Svenson. Sentiamo che storie ci racconta quel vecchio barbogio...";
			link.l1 = "Sai, non dovresti essere così ostile verso Jan. In verità, ti converrebbe molto di più farci la pace... dopotutto, il nostro obiettivo è lo stesso!";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "Ma solo perché ti rispetto... Va bene, "+pchar.name+"Mi dispiace. Non volevo offendere Svenson, sono solo agitato. Non succederà più.";
			link.l1 = "Bene. Dannie, andrà tutto per il meglio. Te lo giuro sul mio onore!";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "Mi fido ciecamente di te, "+pchar.name+"Andiamo da Svenson?";
			link.l1 = "Andiamo, Dannie!";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "13");
		break;
		
		case "islatesoro":
			dialog.text = "Sì? Vi ascolto. In che modo posso esservi d’aiuto?";
			link.l1 = "Hai qualche idea su dove si possa nascondere Jackman? Conosci quella canaglia meglio di me. Forse ha una tana, una base...";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			dialog.text = "Maledetto se lo so! Jacob è sempre stato un tipo schivo. Mai sentito che avesse un covo. Forse è meglio ragionare con la testa... Rileggiamo la lettera che hai preso da Knive. Magari lì c’è qualche indizio.";
			link.l1 = "Proviamoci...";
			link.l1.go = "islatesoro_2";
		break;
		
		case "islatesoro_2":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "Vediamo... parla di Isla Tesoro e di un testamento... Ti dice qualcosa, vecchio lupo di mare?";
			link.l1 = "Io e Jan pensiamo che Blaze Sharp sia stato fatto fuori da Jackman su Isla Tesoro e la colpa sia stata appioppata a Shark. E un testamento... una maledetta sgualdrina... dev’esser roba che riguarda Helen... Maledizione, come ho fatto a non capirlo prima! Quel bastardo dev’essere in rotta verso Isla Tesoro!";
			link.l1.go = "islatesoro_3";
		break;
		
		case "islatesoro_3":
			dialog.text = "Non perdiamo tempo allora, "+pchar.name+"?";
			link.l1 = "Sì. Andiamo a Isla Tesoro. Il vecchio 'Marlin' ci darà man forte in questo colpo.";
			link.l1.go = "islatesoro_4";
		break;
		
		case "islatesoro_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "18");
			pchar.questTemp.Saga.BarbTemptation = "islatesoro";
			// ставим прерывание на Исла-Тесоро
			pchar.quest.Saga_AttackJackman.win_condition.l1 = "location";
			pchar.quest.Saga_AttackJackman.win_condition.l1.location = "Bermudes";
			pchar.quest.Saga_AttackJackman.function = "Saga_CheckJackmanBermudes";
		break;
		
		case "after_boarding":
			dialog.text = "Quel bastardo è finalmente morto... Non ci posso credere – sono di nuovo sul ponte del 'Centurion'! Conosco ogni chiodo di questa nave e pare che anche lei mi abbia riconosciuto.";
			link.l1 = "È di nuovo tua, Dannie. Tua e di Nathaniel.";
			link.l1.go = "after_boarding_1";
		break;
		
		case "after_boarding_1":
			PlaySound("Voice\English\saga\Denny Hawk-03.wav");
			dialog.text = "Non puoi nemmeno immaginare quanto io sia felice. Nathaniel parlava spesso della nostra nave, sarà contento di sapere che è di nuovo nostra.";
			link.l1 = "Che farai adesso, Dannie?";
			link.l1.go = "after_boarding_2";
		break;
		
		case "after_boarding_2":
			dialog.text = "Io? Porterò la nave a Sharp Town, arruolerò almeno l’equipaggio minimo e farò vela verso Blueweld. Chiederò a Jan Svenson di badare al ‘Centurione’, poi andrò dal popolo Miskito e resterò lì finché Occhio di Serpente non avrà rimesso in sesto mio marito.";
			link.l1 = "Vuoi davvero andare a trovare Jan Svenson? Mi sorprendi davvero...";
			link.l1.go = "after_boarding_3";
		break;
		
		case "after_boarding_3":
			dialog.text = ""+pchar.name+", è tutto merito tuo. Ho riflettuto sulle tue parole: 'abbiamo tutti lo stesso scopo'. Ricordi? Voglio fare pace con Svenson, dopotutto mi ha aiutato a riavere Nathan. È ora di smetterla con queste dispute.";
			link.l1 = "Sagge parole, Dannie! Nathaniel potrà riprendere il suo posto a Maroon Town non appena si sarà rimesso.";
			link.l1.go = "after_boarding_4";
		break;
		
		case "after_boarding_4":
			dialog.text = "Forse... vedi, la carica di barone pirata si ottiene col voto. E se gli altri decidessero contro di me?";
			link.l1 = "Lascialo fare a Svenson. Sa come convincere chiunque. Anche la scomparsa di Jackman farà la sua parte.";
			link.l1.go = "after_boarding_5";
		break;
		
		case "after_boarding_5":
			dialog.text = "D’accordo. Tanto mi tocca farmi amico Svenson comunque... "+pchar.name+"! Voglio ringraziarti per tutto ciò che hai fatto per me e Nathan. Hai salvato mio marito e ci hai restituito tutto ciò che avevamo perduto. Ti sono debitrice.";
			link.l1 = "Andiamo, Dannie. Siamo amici.";
			link.l1.go = "after_boarding_6";
		break;
		
		case "after_boarding_6":
			dialog.text = "Voglio che tu sappia che saremo sempre lieti di vederti a Maroon Town. Vienici a trovare quando avrai tempo. Io e Nathaniel troveremo il modo di ricompensarti.";
			link.l1 = "Santo cielo, Dannie! Accetto il tuo invito con piacere. Ci sediamo, beviamo e parliamo di come tu e Nathan avete mandato a fondo Van der Decken...";
			link.l1.go = "after_boarding_7";
		break;
		
		case "after_boarding_7":
			dialog.text = "Ha parlato? Oh, non me lo rammentare neppure...";
			link.l1 = "Va bene, Dannie. Hai un bel po’ di lavoro davanti a te e io devo andare a salutare i nostri compari – Marcus e Barbazon. Spero che non ti dispiaccia se rovisto un po’ in questa cabina; sono sicuro che nei forzieri di Jackman si nasconda roba davvero interessante.";
			link.l1.go = "after_boarding_8";
		break;
		
		case "after_boarding_8":
			dialog.text = "Certo, credi davvero che mi opporrei?";
			link.l1 = "Bene. In verità, mi spiace separarmi da te, Dannie... Ci vediamo a Maroon Town!";
			link.l1.go = "after_boarding_9";
		break;
		
		case "after_boarding_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			LAi_SetHP(npchar, 280, 280); 
			LAi_SetImmortal(npchar, false); // если сработало
			pchar.GenQuest.CannotTakeShip = true; // нельзя захватить
			DoQuestFunctionDelay("Saga_CheckJackmanCabinItems", 5.0); // первая проверка через 5 сек
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		// в Марун-Тауне
		case "marun_town":
			dialog.text = ""+pchar.name+", Son davvero lieta di rivederti! Siamo tornati a Maroon Town e Nathan ha ripreso il posto che gli spetta. In verità, tutta la gente del villaggio ne è felice. Ora tutto tornerà ad andare come una volta! Ti sono davvero grata per il tuo aiuto disinteressato!\nVoglio farti un dono. Ecco, prendi. Questo talismano ti renderà le risse molto più facili. E questa ricetta ti permetterà di fabbricarne altri per conto tuo.";
			link.l1 = "Grazie, Dannie!";
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			GiveItem2Character(pchar, "totem_12"); 
			GiveItem2Character(pchar, "recipe_totem_12"); 
			Log_Info("You have received a talisman");
			Log_Info("You have received the recipe of the talisman");
			PlaySound("interface\important_item.wav");
			dialog.text = "Non è tutto. Ho trovato anche due scrigni pieni d’oro qui. Erano senz’altro di Jackman. Prendili come segno della mia gratitudine. E guai a te se rifiuti! So bene quanti dobloni hai sperperato per aiutare me e Nathan.";
			link.l1 = "Va bene, va bene, Dannie, li accetto!";
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			TakeNItems(pchar, "chest", 2); 
			Log_Info("You have received two chests with doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Eccellente! "+pchar.name+", voglio che tu sappia che d’ora in avanti sei il nostro miglior compagno. Io e Nathan saremo sempre felici di vederti a Maroon Town! Passa a trovarci più spesso!";
			link.l1 = "Grazie! Sarò lieto di rivederti, dunque aspettami!";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_3";
		break;
		
		case "marun_town_3":
			if (CheckAttribute(pchar, "GenQuest.MaruntownSex"))
			{
				dialog.text = "Cosa possiamo fare per voi, "+pchar.name+"?";
				link.l1 = "Ahimè, sto proprio per andarmene... Addio, Danny.";
				link.l1.go = "exit";
				if (CheckAttribute(pchar, "GenQuest.MaruntownSex2"))
				{
					dialog.text = "Ecco qua "+GetFullName(pchar)+" Si vede dalla tua faccia che non hai perso tempo!";
					link.l1 = "Devo ammettere, sai proprio come divertirti! Grazie, mi sono proprio spassato.";
					link.l1.go = "marun_town_fuckgirl_3";
				}
				NextDiag.TempNode = "marun_town_3";
				break;
			}
			bOk1 = CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && IsOfficer(characterFromId("Mary"));
			bOk2 = CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && IsOfficer(characterFromId("Helena"));
			dialog.text = "Sono lieto di vederti, "+pchar.name+"   Rum, vino? O magari una donzella?";
			link.l1 = "Grazie, Dannie! Volevo solo vederti...";
			link.l1.go = "exit";
			if (bOk1 || bOk2)
			{
				link.l2 = "La ragazza? Zitto, Danny! Non vorrai mica trovarmi fatto a pezzi e ben impacchettato sul tuo uscio, vero? Ah-ah. La mia fedele dama, che sta proprio dietro la porta, non mi perdonerebbe simili stregonerie.";
				link.l2.go = "marun_town_fuckgirl_Otkaz_1";
			}
			else
			{
				link.l2 = "Una ragazza? Suona intrigante, Danny. Da tempo bramo... il battito di una donna... Credo che dovrei dare un’occhiata – non proporresti certo chiunque, eh?";
				link.l2.go = "marun_town_fuckgirl_1";
			}
			NextDiag.TempNode = "marun_town_3";
		break;
		
		// Данни предлагает девочку
		case "marun_town_fuckgirl_Otkaz_1":
			dialog.text = "Davvero? Perché sei così pallido? Ah-ah, scherzavo soltanto. Abbi cura di lei, hai capito?";
			link.l1 = "Certo. Per me vale più di tutti i tesori di queste acque!";
			link.l1.go = "marun_town_fuckgirl_Otkaz_2";
		break;
		
		case "marun_town_fuckgirl_Otkaz_2":
			dialog.text = "Così va meglio, ah-ah. Su, vai pure, che la tua bella starà già mordendosi le unghie dall’ansia.";
			link.l1 = "Addio, Danny. E grazie per la tua premura, ah-ah.";
			link.l1.go = "exit";
		break;
		
		case "marun_town_fuckgirl_1":
			dialog.text = "Ti assicuro, questa giovane bellezza sa davvero come farti passare momenti indimenticabili, "+pchar.name+"Divertiti! Ti aspetterà nella stanza della taverna.";
			link.l1 = "Grazie, Danny. Vado subito. Non voglio perdere neppure un minuto!";
			link.l1.go = "marun_town_fuckgirl_2";
		break;
		
		case "marun_town_fuckgirl_3":
			dialog.text = ""+pchar.name+", sei sempre il benvenuto a Maroon Town. Le ragazze migliori sono tutte per te!";
			link.l1 = "Oh, Danny. Giuro, questa ormai è la mia seconda casa.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.MaruntownSex2");
			
		break;
		
		case "marun_town_fuckgirl_2":
			DialogExit();
			pchar.GenQuest.MaruntownSex = "true";
			SetTimerCondition("MarunFuckGirl_4", 0, 0, 2, false);
			LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", false); //открыть комнату
			sld = GetCharacter(NPC_GenerateCharacter("MarunFuckGirl", "women_2"+(rand(6)), "woman", "woman", 1, PIRATE, 1, false, "quest"));
			sld.Dialog.Filename = "Quest\Saga\Danielle.c";
			sld.dialog.currentnode = "MarunFuckGirl";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "FortOrange_tavern_upstairs", "goto", "goto1");
		break;
		
		// Диалог с проституткой
		case "MarunFuckGirl":
			dialog.text = "Ecco il mio capitano. Oggi sei solo mio! Vieni qui, ti ho atteso per un'eternità...";
			link.l1 = "Oh, davvero? Non puoi più aspettare? Allora non perdiamo altro tempo!";
			link.l1.go = "MarunFuckGirl_2";
			LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", true); //закрыть комнату
			chrDisableReloadToLocation = true;
		break;
		
		case "MarunFuckGirl_2":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("MarunFuckGirl", "");
			pchar.GenQuest.MaruntownSex2 = "true";
		break;
		
		case "MarunFuckGirl_3":
			dialog.text = RandPhraseSimple("Mio capitano... sapete davvero come far capitolare le dame! Una cosa simile non mi era mai accaduta! Forse vi fermerete ancora qualche ora?","Te ne vai già, mio caro?");
			link.l1 = RandPhraseSimple("Sapevo che non mi avresti lasciato andare così facilmente. Addio, bellezza. Grandi avventure mi attendono...","Ahimè, il dovere chiama. Ma forse le nostre rotte si incroceranno ancora...");
			link.l1.go = "MarunFuckGirl_4";
		break;
		
		case "MarunFuckGirl_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
	// ------------------------------------------- провалы Саги ------------------------------------------------
		case "failcenturion":
			dialog.text = "Finalmente io e Nathan possiamo tirare un sospiro di sollievo! Quel dannato bastardo di Jackman è morto! Mi dispiace per la 'Centurion', ma avevo già fatto il lutto quando quello scellerato me l’ha portata via. Quindi non ci perdo troppo il sonno.";
			link.l1 = "Ma invece sì! Sono proprio uno sciocco! Tutte le prove sono sprofondate negli abissi insieme alla nave. Quelle ci avrebbero dato man forte nel voto per il nuovo capo della Fratellanza della Costa. Ora... è tutto perduto.";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = "Non ti crucciare troppo! Succede, sai. La prossima volta avrai più fortuna... Ma lasciamo stare. Voglio ringraziarti per tutto ciò che hai fatto per me e Nathan. Hai salvato la vita di mio marito. Ti sono immensamente grata.\nSappi che a Maroon Town sarai sempre il benvenuto. Passa a trovarci, me e Nate, quando avrai un momento. Troveremo il modo di ricambiare il favore.";
			link.l1 = "Va bene, Dannie. Verrò senz'altro a trovarti. Parti già ora?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Sì, andrò dai Miskito, spero che Occhio di Serpente abbia già rimesso in sesto Nathan. Poi faremo vela verso Maroon Town.";
			link.l1 = "Heh, ormai mi sono così abituato a te, mi dispiace davvero doverti lasciare... Buona fortuna, Dannie!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Saga_FailCenturion", 10.0);
			npchar.greeting = "danny_2";
		break;
		
		case "before_kiss":
			dialog.text = "Oh, non fare la finta tonta, cara. Charles, questa cotta le faceva girare intorno a quell’idolo giorno e notte, e tormentava il povero Occhio di Serpente con mille domande. E poi è corsa a casa a portargli qualcosa, non è vero?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog2");
		break;
		
		case "after_kiss":
			dialog.text = "Oh, grazie per lo spettacolo, Charles. Tutta la Maroon Town ne sparlerà, ah-ah!";
			link.l1 = "Non ho alcun dubbio che questa sia ormai la tua nuova priorità: assicurarti che ciò avvenga.";
			link.l1.go = "after_kiss_1";
		break;
		
		case "after_kiss_1":
			dialog.text = "In realtà, era proprio in fondo alla mia lista. Non te la prendere con la ragazza – è la sua prima volta. Quando io e Nathan combinavamo le nostre imprese, tutto l’arcipelago si sganasciava dalle risate su di noi.";
			link.l1 = "Cambiamo aria e discorso. Ho finito con questa statua, andiamo.";
			link.l1.go = "after_kiss_2";
		break;
		
		case "after_kiss_2":
			dialog.text = "D'accordo, andiamo, eroe.";
			link.l1 = "";
			link.l1.go = "Dolly_4";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss3");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Danielle_officer":
			dialog.text = "Cosa desideri, capitano?";
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "danielle")
			{
				Link.l3 = "Dannie, vorrei chiederti un consiglio!";
				Link.l3.go = "islatesoro";
			}
			Link.l1 = "Ascolta il mio comando!";
            Link.l1.go = "stay_follow";
			link.l2 = "Non è nulla. Sciolto!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Danielle_officer";
			sld = characterFromId("Danielle");
		    sld.HoldEquip = true; // лесник -  не отдавать саблю и пистоль для текущей игры. поэтому так . другого способа не нашёл						 
		break;
		
		case "stay_follow":
            dialog.Text = "Ordini?";
            Link.l1 = "Stai fermo qui!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Seguimi e stai al passo!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Cambia il tipo di munizioni per le tue armi da fuoco.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Scegliendo il tipo di munizioni:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "C’è stato un mutamento d’umore!";
            Link.l1 = "Congedato.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Vi è mutamento di disposizione!";
            Link.l1 = "Congedato.";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

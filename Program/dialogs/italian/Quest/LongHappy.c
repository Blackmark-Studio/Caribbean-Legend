// диалоги персонажей по квесту Долго и счастливо
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
			dialog.text = "Di che cosa hai bisogno, giusto?";
			link.l1 = "Niente.";
			link.l1.go = "exit";
		break;
		
		// вестовой капитан в порту
		case "cureer":
			dialog.text = "Monsieur de Maure, che fortuna! Ti cercavo da mesi!";
			link.l1 = "Tesoro mio, non compro mappe tarocche, dicerie da taverna o rum fatto in casa – grazie! O forse sei un cacciatore di taglie? E quanto vale adesso la mia testa, giusto?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "Oh, signore, io... io non traffico in cianfrusaglie e non ammazzo nessuno – non toccare la spada, non servirà, non ho cattive intenzioni! È tutto molto più semplice: sono il capitano di una nave postale. Porto la corrispondenza. E per te ho una lettera importante!";
			link.l1 = "Una lettera? Chi è il mittente, se posso chiedere?";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = "Un abate me l'ha dato e mi ha chiesto di consegnarlo personalmente al capitano de Maure, di mano in mano. Avevo ormai perso ogni speranza di trovarti e stavo per lasciarlo all'ufficio del porto di Saint Pierre, ma che fortuna – eccoti qui!";
			link.l1 = "Sì, eccomi, sto aspettando – dammi la lettera.";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "C'è un problema... L'abate ha detto che la consegna sarebbe stata pagata dal destinatario. Quindi devi novemiladuecento pesos.";
			link.l1 = "Per una cifra simile, avrebbero dovuto portarmelo in mare aperto, direttamente in cabina, insieme al caffè del mattino! Puoi pure tenerti la lettera, giusto?";
			link.l1.go = "cureer_6";
			if (sti(pchar.money) >= 9200)
			{
				link.l2 = "E perché non ho mai fatto la postina?! È più redditizio che fare la pirata! Ecco il tuo argento, caro, dammi la busta.";
				link.l2.go = "cureer_4";
			}
		break;
		
		case "cureer_4":
			AddMoneyToCharacter(pchar, -9200);
			dialog.text = "Che piacere trattare con te! L’abate Benoit ti manda i suoi migliori auguri! Addio, monsieur de Maure!";
			link.l1 = "";
			link.l1.go = "cureer_5";
		break;
		
		case "cureer_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			LongHappy_RecibeLetter();
		break;
		
		case "cureer_6":
			dialog.text = "Come desideri. Lascerò la busta all’ufficio del porto. Ma ti avverto, questo influirà sul prezzo. Ah, e sì – l’abate Benoit ti manda i suoi migliori auguri.";
			link.l1 = "La lettera dell’abate Benoit? Perché non l’hai detto subito! Deve essere qualcosa d’importante!";
			link.l1.go = "cureer_7";
		break;
		
		case "cureer_7":
			dialog.text = "Quindi prendilo direttamente dal capo del porto. Non dimenticare di chiedere un prestito in anticipo. Addio, capitano de Maure.";
			link.l1 = "Ho conosciuto pirati più sinceri di te. Buona fortuna, caro mio.";
			link.l1.go = "cureer_8";
		break;
		
		case "cureer_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.LongHappy = "portman";
		break;
		
		// испанский офицер в Сантьяго
		case "spa_officer":
			dialog.text = "Santo Padre, oggi siete arrivato prima del solito. Prego, la vostra scorta vi attende. E voi, signor de Maure – padre Vincento ha saputo del vostro arrivo in città e vi invita con insistenza a unirvi a lui per una cena.";
			link.l1 = "Temo che l’Inquisitore dovrà cenare da solo. Spero che questo non gli rovini l’appetito ancora di più. E anche l’abate Benoit lo lascerà senza compagnia. Tu sai chi sono, quindi ti consiglio di lasciarci passare senza storie e porta i miei saluti a padre Palotti.";
			link.l1.go = "spa_officer_1";
		break;
		
		case "spa_officer_1":
			if(sti(pchar.reputation.nobility) > 80 || sti(pchar.reputation.nobility) < 20) // провести учёт чести и известности
			{
				dialog.text = "Sì, ho sentito molto parlare di te, e ho ordini precisi di non trasformare la città in un bagno di sangue se fai di testa tua. Puoi passare. Ma padre Vincento sarà... poco contento. Tienilo bene a mente.";
				link.l1 = "Hai agito con saggezza, monsieur. Sopravviverò, in qualche modo, al dolore nel cuore che mi ha lasciato il padre inquisitore scontento. Buona serata!";
				link.l1.go = "spa_officer_2";
			}
			else
			{
				dialog.text = "Sì, ho sentito parlare di te... molte cose interessanti. Tuttavia, rifiutare certi inviti può essere letale, señor. Così come rapire gli ospiti di padre Vincento. Prendetelo!";
				link.l1 = "Ognuno ha fatto la sua scelta. Mi dispiace che sia dovuta finire così. Alle armi, caballero!";
				link.l1.go = "spa_officer_3";
			}
		break;
		
		case "spa_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload3_back", "none", "", "", "", 15.0);
			}
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "spa_officer_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				LAi_group_Attack(sld, Pchar);
			}
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterNationReputation(pchar, SPAIN, -20);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "Guests_block":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		// Ян Свенсон патер
		case "Svenson":
			dialog.text = "Charles, congratulazioni! Lo sai, mi sei sempre piaciuto e Helen è come una figlia per me, quindi sono felice per voi due. Diamine... versare una lacrima in chiesa, era tutto ciò che desideravo. Sto invecchiando, o cosa?";
			link.l1 = "Va tutto bene, Jan, stavo quasi per scoppiare a piangere all'altare. Sarà stato l'incenso, giusto?";
			link.l1.go = "Svenson_1";
		break;
		
		case "Svenson_1":
			dialog.text = "Giusto, canfora, accidenti. Continuavo a chiedermi perché mi pizzicassero gli occhi e prudesse il naso! Va bene, parleremo a Sharptown, abbracciamo Gladys e poi andiamo dagli altri. Hanno delle facce come se stessimo firmando la Pace di Westfalia, giusto?";
			link.l1 = "Grazie per essere venuto qui, Jan. Sono contenta di vederti, conta molto per Helen.";
			link.l1.go = "Guests_block";
		break;
		
		// Ян Свенсон на Исла Тесоро
		case "Svenson_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Eccoti finalmente, Charles! La mia corvetta ti ha superato di quasi un giorno – c’è di che essere orgogliosi.";
			link.l1 = "Prego Jan, ma dov’è Gladys, e tua moglie?";
			link.l1.go = "Svenson_3";
		break;
		
		case "Svenson_3":
			dialog.text = "Ho rimandato Gladys a Blueveld su una nave mercantile – tutte queste feste sfrenate non fanno proprio per lei. Joanna non è potuta arrivare – oh, non ho avuto tempo di raccontartelo a Martinica! Immagina un po’: in vecchiaia finirò per diventare padre legittimo, che ne dici? Guarda, se ti sbrighi, i nostri pargoli avranno quasi la stessa età, ahahaha!";
			link.l1 = "Jan, le mie congratulazioni, questa sì che è una bella notizia!!! Dobbiamo brindare, giusto?";
			link.l1.go = "Svenson_4";
		break;
		
		case "Svenson_4":
			dialog.text = "Sicuramente! Ma prima, a voi e alla vostra metà! Ehi, tu laggiù, zitto!!! Il vecchio Diavolo della Foresta deve fare un discorso!\nEhm-ehm... Dunque, i nostri cari Monsieur e Madame de Maure... Al diavolo! Non riesco a parlare così! Charles, Helen – voi due, per me, siete come figli, e so che qui dentro non c’è anima che non gioisca per la vostra unione! Allora beviamo, Fratelli, alla felicità dei nostri fedeli amici, al vento propizio nelle loro vele e all’amore della Signora Fortuna, forte quanto il loro sentimento reciproco!!! Salute!";
			link.l1 = "Evviva! Grazie Jan... oh, questo rum è molto più forte del solito... Che ci ha messo dentro Nathan, giusto?";
			link.l1.go = "Svenson_5";
		break;
		
		case "Svenson_5":
			dialog.text = "Non ne ho la minima idea, ma sembra proprio giusto. Il vecchio Hawk se ne intende di bevute, di solito. Su, vai dagli altri, io devo preparare da bere per un centinaio di anime assetate che vogliono ubriacarsi a dovere.";
			link.l1 = "Il Diavolo della Foresta che serve da bere: che spettacolo! Grazie per aver preso in mano l’organizzazione della festa. Tornerò di sicuro, appena avrò fatto il giro di tutti – magari qualcuno ha bisogno d’aiuto.";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_6":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Svenson_6_1":
			dialog.text = "Tutto bene, Charles, giusto?";
			link.l1 = "Perfetto, Jan!";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_7":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Eccoti qui, finalmente! Com’è andata a Martinica? Ti senti come se la tua vita fosse cambiata per sempre, giusto?";
			link.l1 = "È cambiato molto prima, Jan. Ma tutto è andato sorprendentemente bene. Dov'è Joahnna e...";
			link.l1.go = "Svenson_8";
		break;
		
		case "Svenson_8":
			dialog.text = "Helen? Quella ragazza ha issato le vele appena ha capito cosa stavamo combinando, e si è diretta verso l’orizzonte. Ti ha mandato mille auguri calorosi, ma comunque... le hai spezzato il cuore, davvero. Però vedrai, andrà tutto bene, è solo la giovinezza.";
			link.l1 = "Beh, il cuore desidera ciò che desidera, giusto?";
			link.l1.go = "Svenson_9";
		break;
		
		case "Svenson_9":
			dialog.text = "Sì che lo voglio. Beh, Joahnna non è riuscita ad arrivare, pensa un po' – alla mia età diventerò padre legittimo, ci credi? Dai, se ti sbrighi, i nostri pargoli avranno quasi la stessa età, ahahah!";
			link.l1 = "Jan, le mie congratulazioni, questa sì che è una bella notizia! Dobbiamo festeggiare con un bicchiere, giusto?";
			link.l1.go = "Svenson_10";
		break;
		
		case "Svenson_10":
			dialog.text = "Senza dubbio! Ma prima, a voi e alla vostra metà! Ehi, voi laggiù, silenzio!!! Il Vecchio Diavolo della Foresta deve fare un discorso!\nCharles e Mary, tutta la Fratellanza solleva i calici in vostro onore! La felicità dei veri amici rallegra l’anima di ogni lupo di mare, quasi quanto lo splendore dell’oro spagnolo, ah-ah! Navigate bene, e che i venti favorevoli vi accompagnino nel viaggio della vostra famiglia!!! Salute!";
			link.l1 = "Salute! Grazie Jan... oh, questo rum è molto più forte del solito... Che ci ha messo dentro Nathan, giusto?";
			link.l1.go = "Svenson_11";
		break;
		
		case "Svenson_11":
			dialog.text = "Non ne ho la minima idea, ma sembra proprio giusto. Il vecchio Hawk è solitamente un esperto di bevute. Su, vai dagli altri, io devo preparare da bere per un centinaio di anime assetate pronte a tracannare, giusto?";
			link.l1 = "Questa taverna va davvero rinominata – 'Il Diavolo della Foresta in persona stava qui dietro al bancone'! Grazie, Jan, tornerò di sicuro, appena avrò fatto il giro di tutti – magari qualcuno ha bisogno d’aiuto, giusto?";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_12":
			dialog.text = "Come va, Charles? E le nozze, come procedono?";
			link.l1 = "Molto commovente, Jan. Sono felice che siamo riusciti a riunirci tutti qui. Pare proprio che le botti di rum di Hawk inizino a svuotarsi, giusto?";
			link.l1.go = "Svenson_13";
		break;
		
		case "Svenson_13":
			dialog.text = "Sì, proprio così! Allora, è il momento di vedere cosa hai portato qui. E un'altra cosa – quei tipi che mi hanno aiutata all'inizio si sono già ubriacati di brutto nel retro. Tu invece stai ancora in piedi, sposo – puoi portare una cassa di un altro sherry, giusto?";
			link.l1 = "Certo, dimmi solo dove devo andare. Magari lungo la strada troverò qualche testa ancora sobria che mi dia una mano. Anche se, a dirla tutta, i miei ragazzi saranno già ubriachi marci, giusto?";
			link.l1.go = "Svenson_14";
		break;
		
		case "Svenson_14":
			dialog.text = "Il vino era ammucchiato nelle cantine sotto l’arsenale, te le ricordi? Hawk ha detto di tenerlo nel corridoio in fondo, ''da conservare fino alla festa'' - parole sue. Dice anche che lì ci sono temperatura e umidità perfette, secondo lui sarebbe la cantina ideale. Beh, è proprio un gran sapientone.";
			link.l1 = "Ha fatto la scelta giusta, Jan. Andrò, ma prima dimmi – hai visto mia moglie?";
			link.l1.go = "Svenson_15";
		break;
		
		case "Svenson_15":
			dialog.text = "Lei e Dannie sono andate da qualche parte. Lascia che le ragazze chiacchierino, Charles, e noi dobbiamo dare inizio alla vera festa. Vai nelle cantine mentre io mi occupo del cibo. Perché qui tra poco si sentirà odore di carbone invece che di costolette di montone, giusto?";
			link.l1 = "Va bene, tu salva la carne, io porto il nostro vino, giusto?";
			link.l1.go = "Svenson_16";
		break;
		
		case "Svenson_16":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			LongHappy_IslaTesoroToVineGo();
		break;
		
		case "Svenson_17":
			dialog.text = "Charles, Nathan, che diavolo è successo, avete forse scatenato una rissa da ubriachi?!";
			link.l1 = "No, Jan, abbiamo combattuto insieme contro dei cutter armati nelle segrete. Ce la siamo cavata, ma erano solo degli esploratori – la squadra principale ci sta addosso, giusto?";
			link.l1.go = "Svenson_18";
		break;
		
		case "Svenson_18":
			dialog.text = "Squadra? Ma di che parli?! Marcus, vieni qui! Charles, avanti, raccontaci tutto.";
			link.l1 = "Come ti dicevo: ci sono dei bastardi nelle segrete sotto l’arsenale. Ben armati. Io e Nathan li abbiamo affrontati e per miracolo li abbiamo stesi tutti. Ma ne stanno arrivando altri – ho sentito che uno di loro è andato a chiamare rinforzi. Ah, e sì, uno di loro ha menzionato un certo Jacques.";
			link.l1.go = "Svenson_19";
		break;
		
		case "Svenson_19":
			DialogExit();
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "Terrax_7";
			ChangeCharacterAddressGroup(sld, "Pirates_tavern", "tables", "stay8");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Svenson_20":
			dialog.text = "Riconosco le loro facce... questo qui, e quel bastardo steso vicino alla porta. Sono scagnozzi di Jacques il Gentiluomo. I nomi non li ricordo, ma ne sono certa.";
			link.l1 = "Quindi è colpa di Barbazon? Ha perso la testa o cosa, giusto?";
			link.l1.go = "Svenson_21";
		break;
		
		case "Svenson_21":
			dialog.text = "Non saprei, ma sembra che il Kindman abbia deciso di approfittare dell’occasione per stravolgere l’ordine tra i baroni della Fratellanza.";
			link.l1 = "In tal caso, spero che si faccia vivo di persona – sogno da un'eternità di fargli due buchi addosso. Maledetto, mi ha rovinato le nozze, ci pensi? Muoviamoci, andiamo in strada! Dobbiamo dare un'accoglienza degna ai nostri ospiti!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernReload");
		break;
		
		case "Svenson_22":
			dialog.text = "Ecco il nostro eroe stanco! Ahah, Charles, che avventura! Jacques, che canaglia! Guarda che intrigo ha messo su – ci è andato vicino, giusto?";
			link.l1 = "Sì, forse avremmo dovuto far fuori quel bastardo subito dopo Jackman. Ma ormai è finita. Barbazon è morto.";
			link.l1.go = "Svenson_23";
		break;
		
		case "Svenson_23":
			if (CheckAttribute(pchar, "questTemp.LongHappy.SvensonsShipSink")) dialog.text = "Beh, non si può certo dire che sia finita – la nostra vita continua! Anche se mi sento a pezzi, come se fossi passata sotto la chiglia. Ormai sono troppo vecchia per lanciarmi in mare da una nave in fiamme e nuotare per un’ora fino a riva, con gli squali che mi girano intorno. Spero che ci sia rimasto ancora un po’ di rum...";
			else dialog.text = "Beh, non si può certo dire che sia finita - la nostra vita continua! Dannazione, mi sento più giovane di dieci anni! Era da un sacco che non combattevo così! Spero che le tue scorte di rum e vino non siano state saccheggiate durante quel casino - dobbiamo brindare come si deve, giusto?";
			link.l1 = "Giusto, anch’io berrei volentieri, ma prima devo controllare la residenza, non so se te l’hanno già detto o no…";
			link.l1.go = "Svenson_24";
		break;
		
		case "Svenson_24":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				dialog.text = "Si tratta del tuo amico indiano? Sì, ho sentito... com'è successo, giusto?";
				link.l1 = "Si è lanciato per proteggere mia moglie e Dannielle da una pallottola sparata da quel bastardo. Dovremmo andare, ti racconterò tutto strada facendo.";
			}
			else
			{
				dialog.text = "Si tratta di Nathan? Sì, ho sentito, solo che non ho capito bene come sia successo, giusto?";
				link.l1 = "Si è lanciato per proteggere le nostre mogli da una pallottola sparata da quel bastardo. Dovremmo muoverci, ti racconto tutto strada facendo.";
			}
			link.l1.go = "Svenson_25";
		break;
		
		case "Svenson_25":
			DialogExit();
			DoQuestReloadToLocation("Pirates_townhall", "goto", "goto4", "LongHappy_DannyInResidence");
		break;
		
		case "Svenson_26":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Coraggio, Charles. Mi dispiace davvero per i tuoi ragazzi. Oggi sono caduti molti bravi marinai, e per ognuno di loro, all’inferno Barbazon riceverà un po’ più d’olio nella caldaia.";
				link.l1 = "Non ha senso... dannazione! È dura, Jan... Ho già perso degli amici, ma non riesco ad abituarmici. Non so se posso andare ancora avanti.";
				link.l1.go = "Svenson_28";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "Quel tipo silenzioso, il medico? Mi dispiace davvero, Charles, sul serio. Era un bravo ragazzo, giusto?";
					link.l1 = "Sì, Jan, anche io. Ma temo che il mondo della scienza abbia perso molto più di me. Era un genio... raffinato, come tutti loro, ma... maledizione...";
					link.l1.go = "Svenson_27";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sTemp = "your Indian guy";
					else sTemp = "Nathan";
					dialog.text = "Ebbene, pare sia finita. Oggi tanti bravi ragazzi ci hanno lasciato, e per ognuno di loro, laggiù all’inferno, Barbazon avrà più olio nella sua caldaia, ma "+sTemp+" andrà tutto bene, ed è questo che conta davvero.";
					link.l1 = "Hai ragione, Jan, e mi sento davvero sollevata. Come stanno gli altri baroni? Stanno bene, giusto?";
					link.l1.go = "Svenson_32";
				}
			}
		break;
		
		case "Svenson_27":
			dialog.text = "L'ultima feccia di Jacques Barbazon. Hai ragione, se l'avessimo fatto fuori prima, tutto sarebbe andato diversamente.";
			link.l1 = "Ma a che serve rimpiangere il passato? Non si può cambiare ciò che è stato. E gli altri baroni? Sono sopravvissuti tutti?";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_28":
			dialog.text = "Nessuno ci si abitua mai. Beviamo ai nostri ragazzi, giusto? Ho trovato una bottiglia sul tavolo, è sopravvissuta per miracolo a tutto questo casino.";
			link.l1 = "Versa, io... Maledizione... Mille dannazioni!";
			link.l1.go = "Svenson_29";
		break;
		
		case "Svenson_29":
			dialog.text = "Parlami di loro. Quel medico sembrava sveglio. Si esprimeva con una tale saggezza.";
			link.l1 = "L’ha fatto. Ma temo che il mondo della scienza abbia perso molto più di me. Era un genio… raffinato, come tutti loro. Un vero mago dei prodigi!";
			link.l1.go = "Svenson_30";
		break;
		
		case "Svenson_30":
			dialog.text = "Del tipo indiano? Dove l’hai trovato?";
			link.l1 = "L'ho salvato dalla prigione a Guadalupa, quasi subito dopo il mio arrivo. Una storia davvero buffa e sciocca. Così è rimasto con me. L'ha scelto lui, gli ho dato la libertà ma ha voluto restare al mio fianco – l'ho salvato e ha pensato di dovermi la vita fino alla fine dei suoi giorni. Poche parole, vestito in modo strano, ma più leale di qualsiasi cavaliere, e aveva anche un dono: riusciva a colpire una moneta al volo col moschetto a qualsiasi distanza.";
			link.l1.go = "Svenson_31";
		break;
		
		case "Svenson_31":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Beh, ti ha saldato il debito, che altro posso dire. Sei stato salvato, giusto?"+sld.name+" e Dannielle da quel bastardo. Mi pare che sia una degna fine per una guerriera così coraggiosa.";
			link.l1 = "È così, Jan. Beviamo alla memoria dei caduti... Che trovino la pace. E gli altri baroni? Stanno bene, giusto?";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_32":
			dialog.text = "Questa notte ci è costata cara. Non so nemmeno quando la Fratellanza si riprenderà da questo massacro. Kindman ha scelto il momento e il luogo perfetti per colpire. Ci è andato vicino – ancora un po’ e sarebbe stata la fine di tutto. Ma abbiamo perso molto meno di quanto avremmo potuto.";
			link.l1 = "";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) link.l1.go = "Svenson_33";
			else link.l1.go = "Svenson_35";
		break;
		
		case "Svenson_33":
			dialog.text = "Lo Squalo è in infermeria, la sua nave ha preso una bordata da ventiquattro libbre. È stato sbalzato fuori bordo, si è rotto un paio di costole, ha bevuto acqua di mare, ma è vivo; tra qualche giorno sarà come nuovo, giusto?";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry")) link.l1.go = "Svenson_34"; // был Венсан
			else link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_34":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "Bernard ha rimediato solo qualche graffio – difendeva la costa e ripuliva le catacombe. Ora si trova al porto, organizza ospedali per i feriti e funerali per chi ha avuto meno fortuna.";
			else dialog.text = "Bernard non ha avuto fortuna: stava ripulendo le case dopo l’attacco dalle catacombe e si è imbattuto in quella banda di bastardi nei magazzini. Si è beccato una pallottola, dritta in testa. Peccato, era un buon capitano... Tyrex andrà su tutte le furie quando lo scoprirà.";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "Bernard ha rimediato solo un paio di graffi – difendeva la costa e ripuliva le catacombe. Ora è al porto, organizza ospedali per i feriti e funerali per chi non ce l’ha fatta.";
			else dialog.text = "Bernard non ha avuto fortuna: stava ripulendo le case dopo l’attacco dalle catacombe e si è imbattuto in quella marmaglia nei magazzini. Una palla in fronte, netta. Peccato, era un buon capitano... Tyrex andrà su tutte le furie quando lo saprà.";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_36":
			dialog.text = "Di Hawk sai già. Dannie non lo farà lasciare l’isola per almeno un mese, questo è certo. Aveva solo una faccenda che ci preoccupava… oh, pazienza.";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Svenson_37";
			else link.l1.go = "Svenson_38";
		break;
		
		case "Svenson_37":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free"))
			{
				dialog.text = "Marcus sta bene come sempre. Appena messo piede a terra, ha subito fatto tremare le anime delle sentinelle che chiudevano gli occhi su tutta questa feccia. Riesce ancora a rimettere in riga la città. Un uomo d’acciaio, nient’altro da dire.";
				link.l1 = "Il ferro è più tenero. Suppongo che il nostro barone sia fatto di un metallo che la scienza ancora non conosce, eh!";
			}
			else
			{
				pchar.questTemp.LongHappy.Terrax.Lost = "true";
				dialog.text = "Solo con Marcus la faccenda è oscura, la sua nave è stata abbordata, ma i superstiti dicono che sia riuscito a gettarsi in mare. Ho già mandato le scialuppe a rastrellare la baia. Spero solo che il nostro barone sia abbastanza tosto da non mollare così facilmente.";
				link.l1 = "È brutto, ma è presto per piangere su di lui, Marcus non si arrenderebbe così facilmente con noi. Aspettiamo cosa daranno le ricerche, giusto?";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_38":
			if (CheckAttribute(pchar, "questTemp.LongHappy.TerraxShipSink"))
			{
				dialog.text = "Marcus è arrivato a riva a nuoto dopo che la sua nave è affondata. Beh, sai com’è, Tyrex non è certo uno che si lascia affogare per una sciocchezza del genere. Ora sarà in qualche vicolo della città, probabilmente sta facendo tremare quei poveri diavoli di sentinelle che si sono lasciati sfuggire tutto questo schifo. Un uomo di ferro, non c’è dubbio.";
				link.l1 = "Il ferro affonderebbe. Immagino che il nostro barone sia fatto di un materiale che la scienza ancora non conosce, eh eh!";
			}
			else
			{
				dialog.text = "Marcus sta bene come sempre. Appena è sbarcato, ha subito iniziato a tirar fuori l’anima alle sentinelle che hanno lasciato passare tutta questa feccia. Continua ancora a comandare la restaurazione dell’ordine in città. Un uomo di ferro, non c’è dubbio.";
				link.l1 = "Il ferro è più tenero. Direi che il nostro barone è fatto di un metallo che la scienza non ha ancora scoperto, giusto? Ahah!";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_39":
			dialog.text = "È tutto qui. Beh, poteva andare peggio. Perfino il tuo matrimonio, Charles, sembrava... una battaglia. L'importante è che siate vivi entrambi. Un piccolo consiglio, in generale... ama... e non ti azzardare mai a smettere di lottare per questo!";
			link.l1 = "Grazie, Jan. Grazie a tutti voi... Devo ammettere che mi ero proprio scordata che abbiamo cominciato con una festa, giusto?";
			link.l1.go = "Svenson_40";
		break;
		
		case "Svenson_40":
			dialog.text = "Ecco un promemoria.";
			link.l1 = "Eh, quella sì che è stata una festa... selvaggia, giusto?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum")) link.l1.go = "Svenson_41";
			else link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_41":
			dialog.text = "Oh sì, proprio così, aspetta un attimo. C'è una cosa – avevi con te un tipo indiano, vero? Sempre appiccicato o che scrutava in giro come se qualcuno ti stesse puntando. Vestito in modo buffo, e davvero impossibile non notarlo in mezzo alla folla, giusto?";
			link.l1 = "Sì, Tichingitu, è sparito proprio all'inizio di tutto questo casino, e a dire il vero comincio a preoccuparmi. Ne sai qualcosa, giusto?";
			link.l1.go = "Svenson_42";
		break;
		
		case "Svenson_42":
			pchar.questTemp.LongHappy.Tichingitu_Wife = "true";
			dialog.text = "Sembra proprio di sì. Il nostro oste faceva un gran baccano dicendo che sua nipote era stata rapita, ma pare sia successo ancora prima dell’attacco. Dice che l’hanno vista con una specie di indiano, che la portava sulla spalla lungo la riva, a est della città. Tra la feccia di Kindman non ho visto indiani, ma appena ho sentito questa storia ho pensato subito al tuo, quindi sono stata zitta. Faresti bene ad andare a cercarlo, prima che combini qualche guaio. Perché l’oste ha giurato che, se lo trova lui per primo, gli stacca la testa senza pensarci. È un brav’uomo, ma per la nipote sarebbe capace di qualsiasi cosa.";
			link.l1 = "Sì sì, li conosco quei tipi, non preoccuparti, e grazie Jan, vado subito a cercarlo, giusto?";
			link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_43":
			dialog.text = "Beh, in generale, qualcosa del genere... Scusa, non sono proprio brava con i discorsi. E adesso è ancora peggio – questa notte ci ha prosciugati tutti. Dovremmo riposare almeno un giorno, poi decideremo come andare avanti.";
			link.l1 = "Hai ragione, Jan. Dovrei andare, ho bisogno di schiarirmi un po' le idee, giusto?";
			link.l1.go = "Svenson_44";
		break;
		
		case "Svenson_44":
			DialogExit();
			DoQuestReloadToLocation("Pirates_town", "reload", "reload3", "LongHappy_WifeInTown");
		break;
		
		case "Svenson_45":
			dialog.text = "Bel aspetto, Charles. Hai dormito bene, giusto?";
			link.l1 = "Sì, ci hanno dato una casetta accogliente ai margini della città. Per un attimo ho pensato di aver solo sognato tutta la follia di ieri. E invece sei qui, Jan, sembri uno straccio. Cos’altro è successo?";
			link.l1.go = "Svenson_46";
		break;
		
		case "Svenson_46":
			dialog.text = "Oh no, non è niente, è solo che non ho ancora chiuso occhio. Sai... rimettere in ordine la città dopo tutto quello che è successo qui è un lavoro duro.";
			link.l1 = "Come stanno Dannie e Nathan? Dove sono finiti tutti quanti, giusto?";
			link.l1.go = "Svenson_47";
		break;
		
		case "Svenson_47":
			dialog.text = "Si stanno riposando. Meglio non disturbarli, Dannie ha avvertito tutti che oggi si è portata le pistole a letto... Dodson è in mare, partito a cercare altre navi per proteggere l'isola, così che non succeda di nuovo, gli altri stanno seppellendo i caduti a nord dell'isola.";
			link.l1 = "";
			link.l1.go = "Svenson_48";
		break;
		
		case "Svenson_48":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner") && !CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free")) dialog.text = "Marcus non si è ancora fatto vivo, ma ce la caveremo, non preoccuparti. Hai già fatto tanto per tutti noi, quindi non affaticarti oltre. Tyrax tornerà prima o poi – lo troveremo.";
			else dialog.text = "Marcus ha finito qui e si è precipitato via su una lugger di qualcuno verso Hispaniola. Deve sistemare alcune questioni sorte dopo la morte di Barbazon. Ti ha mandato i suoi saluti e i migliori auguri a te e a tua moglie.";
			link.l1 = "";
			link.l1.go = "Svenson_49";
		break;
		
		case "Svenson_49":
			dialog.text = "Ebbene, Fratelli hanno resistito a questo colpo. Presto ci rialzeremo più forti che mai. Kindman e Jackman hanno minato la nostra unità troppo a lungo, ora che non ci sono più sento nel cuore che faremo tremare i Caraibi più di una volta. L’Età d’Oro arriva per chi non si sottomette né a leggi né a re, memorizza queste parole.";
			link.l1 = "Sarebbe bello. Non sono sicura di poter più sopportare il Vecchio Mondo. Mai avrei pensato, venendo qui, di innamorarmi della libertà del mare, di questi tramonti e albe dai colori folli, di trovare la donna migliore al mondo e... amici a cui affiderei la mia stessa vita.";
			link.l1.go = "Svenson_50";
		break;
		
		case "Svenson_50":
			dialog.text = "Bene, conosci la rotta, decidi pure. Nelle nostre case sarai sempre il benvenuto.";
			link.l1 = "Grazie, Jan. Significa molto per me.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete") link.l1.go = "Svenson_51";
				else link.l1.go = "Svenson_54";
			}		
			else link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_51":
			pchar.questTemp.LongHappy.Baron = "true";
			dialog.text = "Ma prima, c’è ancora una cosa importante. Charles, mentre dormivi, ci siamo riuniti e abbiamo deciso... Dato che Barbazon è morto, la Fratellanza ha bisogno di un nuovo barone. Visto che qui eravamo la maggioranza, e la decisione è stata unanime, eccola: congratulazioni – sei il nuovo Barone di Le Francois. Ma aspetta... Capisco, sei uomo di mondo e non hai tempo per gestire gli affari in questo bel posto, quindi ci abbiamo messo una persona fidata, e tu fai ciò che vuoi. Ricorda solo – ora hai voce nella Fratellanza.";
			link.l1 = "Jan, io... sono senza parole... È un grande onore, non so nemmeno cosa dire...";
			link.l1.go = "Svenson_52";
		break;
		
		case "Svenson_52":
			dialog.text = "Andiamo! Hai già dimostrato il tuo valore con Tyrex, e poi con tutta questa storia dell’eredità di Sharp. Sei la benedizione di Dio in persona. Per te non cambierà nulla – continua come hai pianificato, e in tua assenza il tuo uomo si occuperà di tutto.\nC’è un tipo promettente, Jan David, uno dei Bucanieri. Francese, un brav’uomo, con una mente brillante e sa come usarla, proprio come te. Ma ci vorrà un po’ di tempo per trovarlo – pare che sia stato catturato dagli Spagnoli, ma si può risolvere, non preoccuparti. Mi assicurerò che ti mandi la tua parte appena si sarà sistemato con gli affari.";
			link.l1 = "Non mi aspettavo proprio che andasse a finire così. Beh, ormai hai deciso tu, quindi che sia. Il Barone Pirata Charles de Maure!";
			link.l1.go = "Svenson_53";
		break;
		
		case "Svenson_53":
			dialog.text = "Lunga vita al barone! Se qualcuno merita davvero quel titolo, sei tu. Portalo con orgoglio e ricorda: ormai sei dei nostri, qualunque sia la tua bella divisa – qui sotto, proprio sotto di essa, batte il cuore di un vero pirata.";
			link.l1 = "Non so, forse stai esagerando... Ma farò tutto il possibile per meritare la tua fiducia, giusto?";
			link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_54":
			dialog.text = "Cosa farai adesso? Tornerai in Europa, da tuo padre, per presentargli tua moglie?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") || CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				link.l1 = "Sì, ma prima devo salutare qualcuno... Sai a cosa mi riferisco.";
				link.l1.go = "Svenson_56";
			}
			else	
			{
				link.l1 = "Forse non così presto. Voglio ancora una volta solcare l’arcipelago, respirare quest’aria di Libertà un’ultima volta.";
				link.l1.go = "Svenson_55";
			}
		break;
		
		case "Svenson_55":
			dialog.text = "Beh, hai una nave, puoi tornare a casa quando vuoi, giusto?";
			link.l1 = "Spero anch'io. Grazie Jan, grazie a tutti voi e ci vediamo presto, vecchio mio amico! Saluta i Falchi e lo Squalo da parte mia!";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_56":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died")) sTemp = "They deserve";
			else sTemp = "He deserve";
			dialog.text = "Sì, è dura, ma dobbiamo farlo. Verso il mare, giusto?";
			link.l1 = "No, salperò per Antigua. "+sTemp+" riposare in pace in un luogo che, per un po', è stato la nostra casa.";
			link.l1.go = "Svenson_57";
		break;
		
		case "Svenson_57":
			dialog.text = "Di’ anche qualche parola gentile da parte mia. E non preoccuparti – da qui ce la caviamo da soli. Andrà tutto bene.";
			link.l1 = "Grazie Jan. A presto, vecchio mio! Saluta gli Hawks e lo Squalo da parte mia!... Beh, si va ad Antigua.";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_58":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_IslaMarryComplete", 10.0);
		break;
		
		case "Svenson_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Svenson_";
		break;
		
		// Глэдис
		case "Gladis":
			dialog.text = "Giovanotto, oggi sei salito ancora di più nella mia stima. Hai fatto così tanto per Helen che nessuna parola potrà mai bastare a ringraziarti. Spero solo che continuerai a prenderti cura di lei. Se suo padre fosse ancora vivo e avesse visto tutto questo... ah, scusami.";
			link.l1 = "Va tutto bene, Gladys. Hai attraversato l’arcipelago per sostenere Helen in questo giorno. Sia io che lei apprezziamo davvero la tua visita insieme a Jan, grazie.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже - патер Мэри
		case "forge":
			dialog.text = "Monsieur de Maure, perdona la confidenza, ma lo dirò così – Charles, amico mio, sono davvero felice per te! Se posso fare qualcosa per te o la tua sposa, dimmelo pure!";
			link.l1 = "Vi ringrazio, Barone, sono così felice, e i vigneti che mio padre voleva come dote, credo di poterli riscattare – per fortuna, la mia situazione finanziaria qui nel Nuovo Mondo è migliorata di molto.";
			link.l1.go = "forge_1";
		break;
		
		case "forge_1":
			dialog.text = "Sì, immagino che tu possa permetterti tutto ciò che desideri, Charles. Scusami, ma permettimi di svolgere il mio dovere da padre rappresentante – Oggi stesso scriverò al mio caro amico Ministro delle Finanze. Alla tua prescelta verrà conferito un titolo nobiliare, e credo che troveremo per lei una bella tenuta, diciamo in Guascogna, tra quelle confiscate per debiti, e gliela assegneremo con effetto retroattivo. Così nessuno oserà mai dire che il Cavaliere de Monper ha trovato moglie di bassa condizione!";
			link.l1 = "Non credo di dare peso a certe chiacchiere, ma grazie, Barone. Comunque, non dovresti";
			link.l1.go = "forge_2";
		break;
		
		case "forge_2":
			dialog.text = "Dovrei eccome! Ora vai, Charles, dedica un po’ della tua attenzione anche agli altri ospiti. E ancora una volta, accetta le mie congratulazioni più sincere!";
			link.l1 = "Io e mia moglie ti ringraziamo. A presto, Barone.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже - патер ГГ
		case "forge_3":
			dialog.text = "Monsieur de Maure, perdona la confidenza, ma lo dirò così – Charles, amico mio, sono sinceramente felice per te! Se posso fare qualcosa per te o per la tua sposa, basta chiedere!";
			link.l1 = "Grazie, Barone, ma hai già fatto abbastanza per me. Ci basta che tu abbia accettato l'invito.";
			link.l1.go = "forge_4";
		break;
		
		case "forge_4":
			dialog.text = "Come potrei non rispondere, Charles! Ma ascolta – vorrei offrirti, a te e alla tua splendida sposa, un dono degno di voi, ma non riesco a pensare a nulla che tu non possa procurarti da solo con denaro o con la spada. Dunque scriverò al mio amico Ministro delle Finanze a Parigi, e quando giungerai in Europa, ti attenderanno per farti firmare il regio rescritto che eleva il nome de Monper al titolo di Baroni de Monper! No, non dire nulla, è il minimo che possa fare per te.";
			link.l1 = "Non so nemmeno cosa dire, Barone... Mio padre sarà felicissimo. Ti ringrazio davvero di cuore.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже гость
		case "forge_5":
			dialog.text = "Charles, ti prego, accetta le mie più sentite congratulazioni! La tua scelta è semplicemente un prodigio! Credo che oggi la moda coloniale abbia ricevuto una scossa... verso nuovi orizzonti. La tua originalità mi ha sempre affascinato! Che tu e la tua splendida metà possiate vivere felici per sempre!";
			link.l1 = "Grazie, Barone. Ci hai onorati con la tua visita.";
			link.l1.go = "forge_6";
		break;
		
		case "forge_6":
			dialog.text = "Come potrei restare lontano, amico mio? Ne abbiamo passate tante insieme e sono fiero di chiamarti amico, Charles. Ricorda – le mie porte ti saranno sempre aperte, qualunque cosa accada.";
			link.l1 = "Le porte della famiglia de Monper saranno sempre aperte per voi, Barone.";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси патер Мэри
		case "puancie":
			dialog.text = "Charles, amico mio, questo è un giorno molto importante, e sono felice che tu mi abbia invitato a condividerlo con te. Abbiamo percorso una lunga e difficile strada insieme, ed essere il padre rappresentante di mademoiselle... perdonami - Madame de Maure, è un onore per me, credimi. Ti auguro tutta la felicità con tutto il cuore!\nE ti prego, fammi sapere quando partirai per l’Europa: io, come padre rappresentante della tua sposa, manderò a tuo padre tutti i doni nuziali necessari. Fidati, nessuno potrà dire che la sposa del chevalier de Monper sia povera o indegna!";
			link.l1 = "Se posso permettermi, Chevalier, a un paio di miglia a nord della tenuta de Monper ci sono delle ottime vigne, appartengono alla famiglia La Brigne e io...";
			link.l1.go = "puancie_1";
		break;
		
		case "puancie_1":
			dialog.text = "Non una parola di più, amico mio, non una parola! Scriverò subito al mio rappresentante autorizzato a Lione – al tuo arrivo queste vigne saranno già consegnate alla tua prescelta.";
			link.l1 = "Grazie, Cavaliere. Hai ragione – la nostra... amicizia, ne ha passate di ogni. Però, sono davvero felice che tu abbia condiviso questa giornata con noi. Ci vediamo e ancora grazie!";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси патер ГГ
		case "puancie_2":
			dialog.text = "Charles, amico mio, oggi è un giorno davvero importante e sono felice che tu mi abbia invitato a condividerlo con te. Abbiamo attraversato mari burrascosi insieme e per me è un vero onore essere testimone alle tue nozze. Dal profondo del cuore ti auguro ogni felicità! E tienimi informato quando partirai per l’Europa – manderò a tuo padre dei regali di nozze degni di te.";
			link.l1 = "Non ce n'è bisogno, Chevalier. Ti ringrazio per aver accettato il mio invito.";
			link.l1.go = "puancie_3";
		break;
		
		case "puancie_3":
			Log_Info("You have got gems");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry2", 50);
			TakeNItems(pchar, "jewelry3", 50);
			TakeNItems(pchar, "jewelry4", 50);
			dialog.text = "Come ho detto - per me è un onore! Ma aspetta, amico mio, vorrei offrirti qualcosa per questa occasione - sono certo che piacerà sia a te che alla tua prescelta. Splendide gemme dalle nostre miniere della Nuova Guiana – scegli una bella montatura e madame de Maure brillerà persino a un ricevimento reale! Sempre che tu riesca a convincerla a indossare un abito, naturalmente...";
			link.l1 = "Oh, davvero non dovevi, cavaliere. Grazie ancora.";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси гость
		case "puancie_4":
			dialog.text = "Charles, amico mio, lascia che ti faccia le mie congratulazioni! Abbiamo attraversato un lungo e arduo cammino, e sono davvero felice di essere qui oggi. Il Signore è testimone – meriti la tua felicità! Conservala e proteggila – ti auguro tanti anni felici avanti a te!";
			link.l1 = "Grazie, Cavaliere, io e mia moglie ti siamo davvero riconoscenti.";
			link.l1.go = "Guests_block";
		break;
		
		// Фадей патер
		case "fadey":
			dialog.text = "Charles, che festa grandiosa, e quanta gente importante! Permettimi di augurarti con tutto il cuore felicità, salute e figli che portino gioia! Come diciamo noi — 'amaro!'";
			link.l1 = "Grazie, Fadey, mi hai davvero onorata accettando di venire.";
			link.l1.go = "fadey_1";
		break;
		
		case "fadey_1":
			dialog.text = "Ma, non capisco perché ci siano così tante persone come se non stessimo celebrando un matrimonio, ma chiudendo un affare enorme, e poi qui non c’è nemmeno abbastanza birra e vodka per i miei gusti... ahah! Dai, scherzo, Charles, perché sei diventato bianco come una vela? Vieni qui, dammi un abbraccio, capitano sposato!";
			link.l1 = "Wow... Fadey, sei forte come un orso, giusto?";
			if (CheckAttribute(pchar, "questTemp.Persian"))
			{
				if (pchar.questTemp.Persian == "time" || pchar.questTemp.Persian == "end") link.l1.go = "fadey_2";
				else link.l1.go = "Guests_block";
			}
			else link.l1.go = "Guests_block";
		break;
		
		case "fadey_2":
			GiveItem2Character(pchar, "blade_22");
			GiveItem2Character(pchar, "blade_23");
			GiveItem2Character(pchar, "blade_24");
			Log_Info("You got three Persian sabres");
			PlaySound("interface\important_item.wav");
			dialog.text = "Aspetta, Charles, non andare via – non si addice a un ospite venire al matrimonio a mani vuote. Prendi questi, ti prego. So che hai faticato per trovare tutte queste lame, e alcune, di certo, ti hanno colpito. Accettale – appendile nella casa di famiglia e ricorda Fadey Moskovit con una parola gentile!";
			link.l1 = "Questo sì che è un regalo vero! Grazie, Fadey. Queste armi sono davvero magnifiche, e ti prometto che avranno un posto d’onore nella tenuta de Monper!";
			link.l1.go = "Guests_block";
		break;
		
		// Фадей гость
		case "fadey_3":
			dialog.text = "Charles, che festa grandiosa, e quanta gente importante! Permettimi di augurarti felicità, salute e un mare di figli che portino gioia! Come diciamo noi – ‘amaro!’ Vieni qui, abbracciami, capitano sposato!";
			link.l1 = "Wow... Fadey, sei forte come un orso, giusto?";
			link.l1.go = "Guests_block";
		break;
		
		// Проспер Трубаль
		case "Prosper":
			dialog.text = "Charles, non potevo mancare, ti faccio i miei più sinceri auguri a te e alla tua sposa! Siate felici! Sai, un paio di mesi fa ho sposato mia figlia, con un brav’uomo che la ama, ma a dire il vero ero un po’ rattristato che non fossi tu… Beh, lasciamo perdere… cosa vado cianciando – congratulazioni! Che la vostra vita sia lunga e felice!";
			link.l1 = "Grazie, Prosper, sono felice che tu sia venuto, giusto?";
			link.l1.go = "Guests_block";
		break;
		
		// Тичингиту
		case "Tichingitu":
			dialog.text = "Congratulazioni, capitano! Un rito strano, ma affascinante – Tichingitu l’ha gradito. Anche se, secondo la tradizione, il capitano dovrebbe solo rapire la sua squaw e mandare un riscatto ai suoi parenti.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "Beh, in un certo senso sì, è solo una formalità. Grazie, amico mio!";
			else link.l1 = "Beh, in un certo senso sì, è solo una formalità. Grazie, amico mio! Tu ed io parleremo ancora a Sharptown – lì ci sarà molto meno ufficialità e molto più divertimento sincero, te lo prometto!";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Acqua di fuoco di nuovo? Tichingitu non può dire che gli piaccia. Forse un arrembaggio festoso sarebbe meglio, o almeno ballare attorno a un falò?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "Spero proprio che non finirà in danze attorno al fuoco prima del tempo, e preferirei evitare gli abbordaggi. Va bene, pazienza – manca poco, e poi ci spostiamo subito in taverna.";
			else link.l1 = "Temo che finirà con danze intorno ai falò ben prima della fine, e preferirei restarmene fuori dalle abbordate. Va bene, pazienta ancora un po’ – manca davvero poco, e salpiamo subito per Sharptown.";
			link.l1.go = "Guests_block";
		break;
		
		case "Tichingitu_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Capitano, congratulazioni ancora! Tichingitu si gode questa festa più della precedente. Il capitano sa scegliere i compagni: qui c'è più sincerità, meno ipocrisia e parrucche finte.";
			link.l1 = "Grazie, amico mio! Ma non bere l'acqua di fuoco, qui è davvero pesante, giusto?";
			link.l1.go = "Tichingitu_4";
			link.l2 = "Grazie, amico mio! Beviamo qualcosa? Lo so, non ti piace, ma oggi dovresti provarci, giusto?";
			link.l2.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			pchar.questTemp.LongHappy.Tichingitu_Rum = "true";
			dialog.text = "Tichingitu non ama l’acqua di fuoco, ma se il capitano insiste, oggi si può fare. Alla tua felicità, e alla tua squaw!";
			link.l1 = "E a te, Tichingitu! Alla tua amicizia e lealtà!";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			DialogExit();
			npchar.dialog.currentnode = "Tichingitu_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "LongHappy_57";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tichingitu_4_1":
			dialog.text = "Bel festino, capitano.";
			link.l1 = "Sono felice che tu sia soddisfatto.";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Capitano, sei venuto a vedere le stelle? La notte promette d’essere splendida. A Tichingitu piace la notte sul mare. È così serena.";
			link.l1 = "Felice di vederti ancora in piedi, amico mio! Io e Nathaniel abbiamo bisogno del tuo aiuto – alla taverna sono rimasti a secco, dobbiamo portare qualche cassa di bottiglie dal magazzino sotto l'arsenale.";
			link.l1.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_6":
			dialog.text = "Conduci tu, capitano. Tichingitu ti segue, come sempre.";
			link.l1 = "Va bene, andiamo, giusto?";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Tichingitu_8":
			dialog.text = "Capitano, ci sono delle persone, e sono armate, Tichingitu sente il tintinnio delle loro armi e si fa sempre più forte ogni secondo. Non mi piace per niente. Nascondiamoci.";
			link.l1 = "Dai, amico — questa è Sharptown, qui persino in latrina ci si va armati di pistola. Ehi Nathan... cavolo! Ecco, una bottiglia già andata. Se continui così, spaccherai tutte le bottiglie! Stai dritto sulle gambe, dannazione! Ah-ah!";
			link.l1.go = "Tichingitu_9";
		break;
		
		case "Tichingitu_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LongHappy_SetBandosInDungeon();
		break;
		
		case "Tichingitu_10":
			dialog.text = "Capitano... tu... la testa di Tichingitu mi gira come l’albero maestro in tempesta. Cos’è successo?";
			link.l1 = "Volevo chiederti la stessa cosa! Dove sei stato per tutto questo tempo, giusto?";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "Tichingitu si è svegliato un’ora fa per via delle urla di quella ragazza. Correva sulla spiaggia quasi nuda e urlava qualcosa sui rapitori e sui selvaggi… Ma qui non c’è nessuno oltre a noi. Hai dell’acqua? Non quella infuocata di nuovo, Tichingitu ormai la detesta.";
			link.l1 = "C'era una fiaschetta da qualche parte, se non l'ho persa durante una rissa... eccola qua. Come hai fatto a combinare tutto questo? Suo zio, un oste del posto, cerca un indiano che ha rapito la nipote e minaccia di staccargli quella testa vuota piena di piume. Secondo te, di chi sta parlando?";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "Tichingitu ricorda. Aiutava il Diavolo della Foresta alla taverna con le nozze. Abbiamo bevuto acqua di fuoco insieme, e Tichingitu ne voleva ancora. E poi, quella squaw... era così graziosa e... Capitano, credo di ricordare! Tichingitu voleva sposarla... Voleva costruire una canoa e portarla via... Spiriti di pietà! Gente malvagia è arrivata con l'acqua di fuoco. Forse demoni, o spiriti maligni! Tichingitu non lo farà mai più...";
			link.l1 = "Portarla via? Costruire una canoa?! Ahah, sei proprio un romantico, amico mio... Ah-ah... ah-ah-ah-ah-ah oh, non ce la faccio... non riesco a smettere di ridere!";
			link.l1.go = "Tichingitu_13";
		break;
		
		case "Tichingitu_13":
			dialog.text = "Capitano, Tichingitu ha rapito la squaw, sì... ma, possiamo, beh... non sposarci adesso? Lei è... rumorosa come un pappagallo, e... non proprio bella.";
			link.l1 = "Sì, amico mio, le donne che si divertono tutta la notte sono uno spettacolo pietoso al mattino. Non preoccuparti, eroe dal cuore tenero, qualcosa ci inventeremo. Dai, dobbiamo tornare a Sharptown, ti sei perso l’imbarco della festa...";
			link.l1.go = "Tichingitu_14";
		break;
		
		case "Tichingitu_14":
			dialog.text = "Un abbordaggio? Il Capitano aveva già accennato a una battaglia. I pensieri non ascoltano ancora Tichingitu. Cos’è accaduto in città?";
			link.l1 = "Una vera battaglia, sia sulla terra che in mare. I cannoni hanno tuonato tutta la notte, credo che persino a San Jose li abbiano sentiti. Però tu eri impegnato in un’altra 'battaglia', posso capirlo… Su, ti racconto tutto strada facendo.";
			link.l1.go = "Tichingitu_15";
		break;
		
		case "Tichingitu_15":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("LH_waitress");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.longhappy_shoregirl1.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl1.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_shoregirl1.function = "LongHappy_ReturnShoreGirl";
		break;
		
		case "Tichingitu_16":
			dialog.text = "Grazie, capitano... Tichingitu non oserà mai più...";
			link.l1 = "Sì, 'lo stallone delle lontane praterie' non dovresti proprio bere oltre, giusto? Vai a dormire. Anche io sto per crollare dai piedi, giusto?";
			link.l1.go = "Tichingitu_17";
		break;
		
		case "Tichingitu_17":
			DialogExit();
			npchar.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			LAi_SetImmortal(npchar, false);
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			LAi_SetOfficerType(npchar);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			npchar.dialog.currentnode = "Tichingitu_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_55";
			ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Tichingitu_18":
			dialog.text = "Capitano, congratulazioni ancora! Tichingitu gradisce questa festa più della precedente. Il capitano sa scegliere i compagni – qui c’è più sincerità, meno ipocrisia e parrucche finte.";
			link.l1 = "E molto altro rum, giusto? A proposito, berrai qualcosa con me? Lo so che non ti piace, ma oggi c’è un’occasione speciale, giusto?";
			link.l1.go = "Tichingitu_19";
		break;
		
		case "Tichingitu_19":
			dialog.text = "Tichingitu non ama l’acqua ardente, ma se il capitano insiste, oggi si può fare. Alla vostra felicità, e alla tua squaw! Che possiate camminare sullo stesso sentiero, e che il sole e la luna lo illuminino per sempre.";
			link.l1 = "Grazie, amico mio. Un brindisi a te, Tichingitu! Alla nostra amicizia!";
			link.l1.go = "Tichingitu_4";
		break;
		
		// губернаторы
		// Сен Пьер
		case "FortFrance_Mayor":
			if (pchar.questTemp.GoldenGirl == "end")
			{
				dialog.text = "Grande... che festa, sono davvero felice per te, Charles. Anche se ancora non ti capisco... Tenere tra le mani una rosa senza prezzo e scambiarla per... un fiore selvatico. Ma il cuore va dove vuole, giusto? Sii felice, amico mio. Che la vostra vita sia una favola senza fine!";
				link.l1 = "Nel fiore che stringi, la cosa più bella è il sentimento che ci metti. Senza quello, resta solo un mucchietto di petali destinati a svanire. Felice che tu sia venuto, Vostra Grazia.";
				link.l1.go = "FortFrance_Mayor_1";
			}
			else
			{
				dialog.text = "Una giornata meravigliosa, amico mio, e un'occasione ancor più splendida! Accetta le mie più sincere felicitazioni! Io mi sono sposato tre volte, e ogni volta tremavo come la prima, ah, gioventù...";
				link.l1 = "Monsieur, sei ancora lontano dalla vecchiaia, non perderti d’animo. Grazie d’essere venuto, Jacques!";
				link.l1.go = "Guests_block";
			}
		break;
		
		case "FortFrance_Mayor_1":
			dialog.text = "Aspetta, Charles. Hai frainteso, sono davvero felice con tutto il cuore! E sì... tieni, prendilo. Il nostro comune... Amico, ci teneva che tu lo ricevessi proprio oggi.";
			link.l1 = "Sospetto già da chi possa arrivare. Ti ringrazio e a presto.";
			link.l1.go = "Guests_block";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2-1");
					else AddQuestRecordInfo("Letter_Marquesa", "1-1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4-1");
					else AddQuestRecordInfo("Letter_Marquesa", "3-1");
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2");
					else AddQuestRecordInfo("Letter_Marquesa", "1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4");
					else AddQuestRecordInfo("Letter_Marquesa", "3");
				}
			}
		break;
		
		// Бас Тер
		case "BasTer_Mayor":
			dialog.text = "Una liturgia deliziosa, vero, Charles? Sono sinceramente felice per te! Da parte mia e di tutti i cittadini di Basse-Terre – vi porgo le nostre congratulazioni a te e alla tua... incantevole sposa. Siete una coppia meravigliosa! Che possiate vivere felici per sempre!";
			link.l1 = "Grazie, Vostra Grazia. Felice che sia stato di vostro gradimento.";
			link.l1.go = "Guests_block";
		break;
		
		// Порт Принс
		case "PortPax_Mayor":
			dialog.text = "Che splendida cerimonia, monsieur de Maure, davvero magnifica! E la sposa è così... originale con questo abito. A nome di tutti gli abitanti della nostra città – accettate le mie più sentite congratulazioni! Vi auguro molti anni felici insieme!";
			link.l1 = "Grazie, Vostra Grazia.";
			link.l1.go = "Guests_block";
		break;
		
		// Тортуга
		case "Tortuga_Mayor":
			dialog.text = "Che scena adorabile – tu e la tua sposa, monsieur de Maure, eravate proprio una coppia fuori dal comune! Ma tu sei un uomo fuori dal comune. Ti auguro una lunga e felice vita insieme. Che possiate essere felici per sempre!";
			link.l1 = "Ti sono davvero grata, Vostra Grazia.";
			link.l1.go = "Guests_block";
		break;
		
		// д'Ойли
		case "PortRoyal_Mayor":
			PlaySound("Voice\English\LE\Doily\Edvard_Doily_03.wav");
			dialog.text = "Per le vostre nozze, ne è valsa la pena attraversare i Caraibi! Congratulazioni, capitano, a nome di tutti gli abitanti delle colonie inglesi! Tu e la tua sposa, anzi, ormai tua moglie, siete proprio una coppia magnifica!";
			link.l1 = "Grazie della visita e delle belle parole, Colonnello!";
			link.l1.go = "Guests_block";
		break;
		
		// Исла Тесоро
		// Тиракс
		case "Terrax":
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "E che ci fa questo damerino sposato sulla mia spiaggia di pirati, eh?! Dimmi, monsieur, che fine hai fatto fare al mio vecchio amico – il temibile pirata Charlie Prince?";
					link.l1 = "Charlie Prince è morto, te lo ricordi, Marcus... Ah-ah-ah, vieni qui, vecchio diavolo del mare! Che piacere vederti! Come ve la passate qui, vi siete già radunati tutti, giusto?";
					link.l1.go = "Terrax_1_1";
				}
				else // 28-03-20
				{
					dialog.text = "E che ci fa questo damerino sposato sulla mia spiaggia di pirati, eh?! Dimmi, monsieur, che ne hai fatto del mio vecchio amico — il temibile capitano Charles de Maure?";
					link.l1 = "Ehilà, Marcus, sono felice di vederti anche io! Come ve la passate qui, vi siete già radunati tutti, giusto?";
					link.l1.go = "Terrax_1";
				}
			}
			else
			{
				dialog.text = "E cosa ci fa questo damerino sposato sulla mia spiaggia di pirati, eh?! Dimmi, monsieur, che ne hai fatto del mio vecchio amico – il burbero Capitano Charles de Maure?";
				link.l1 = "Ehilà, Marcus, sono felice di vederti anche io! Come ve la cavate qui, sono già arrivati tutti, giusto?";
				link.l1.go = "Terrax_1";
			}
		break;
		
		case "Terrax_1":
			dialog.text = "Sì, il Diavolo della Foresta è arrivato proprio ieri e subito ha iniziato a dare ordini – quindi gli ospiti sono qui e tutto è pronto per la festa. La tua nave è stata avvistata vicino alle scogliere, e i ragazzi non hanno resistito – si sono fiondati in taverna e, quasi certamente, hanno già stappato quella botte di Hawk. Sbrigati, magari riusciamo ancora a bere un bicchiere insieme – Nathaniel si vantava che fosse un rum davvero speciale!";
			link.l1 = "Ecco come si fa: dalla nave dritti alla festa! Aspetterò la mia metà migliore e veniamo subito dietro di te, Marcus!";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_1_1":
			dialog.text = "Sì, il Diavolo della Foresta è arrivato solo ieri e ha subito preso il comando – così gli ospiti sono qui e tutto è pronto per la festa. La tua nave è stata avvistata vicino alle scogliere, e i ragazzi non hanno saputo resistere – si sono precipitati in taverna e, molto probabilmente, hanno già stappato quella botte di Falco. Sbrigati, magari riusciamo ancora a bere un bicchiere – Nathaniel si vantava che fosse un rum davvero speciale!";
			link.l1 = "E allora così si fa – dalla nave dritti al festeggiamento! Aspetterò la mia dolce metà e saremo proprio dietro di te, Marcus!";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_2":
			DialogExit();
			DoQuestReloadToLocation("Pirates_tavern", "reload", "reload1", "LongHappy_IslaTesoroTavern");
		break;
		
		case "Terrax_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Sposata con Charles de Maure – ancora non riesco a crederci... Prima Svenson, ora tu – e poi chi? Il pastore Marlow, o magari Jacques il Buonaccione, giusto?";
			link.l1 = "Hai dimenticato i Falchi. E tu, Marcus? Non sei stanco di fare il lupo di mare solitario, giusto?";
			link.l1.go = "Terrax_4";
		break;
		
		case "Terrax_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				dialog.text = "Dannie e Nathan sono una vecchia storia – ormai ci ho fatto il callo, ma tu mi hai davvero stupito, non c’è che dire! Però la pupilla del Diavolo della Foresta è una vera bellezza – niente da aggiungere, sempre pronta con la parola e la pistola, e sa destreggiarsi in qualsiasi tempesta. Difficile trovare una donna più degna di lei. Sei proprio fortunato, capitano – tienitela stretta!";
			}
			else
			{
				dialog.text = "Dannie e Nathan sono una storia vecchia – ormai ci ho fatto il callo, ma tu mi hai proprio spiazzato, non c’è che dire! Però, da quel che si dice in giro, la tua Mary se ne intende davvero di spade e sa il fatto suo – il mio rispetto! Una vera compagna da battaglia. Ti confido un segreto: per una ragazza così, persino io potrei rivedere le mie convinzioni da scapolo. Sei fortunato, capitano – non perdertela!";
			}
			link.l1 = "Lo so, lei è un miracolo e sono di nuovo al settimo cielo dalla felicità — proprio come quei giorni quando ci siamo incontrati per la prima volta!";
			link.l1.go = "Terrax_5";
		break;
		
		case "Terrax_5":
			dialog.text = "E allora, un brindisi!... All’amore!... Ma non a quello che ci spinge oltre la soglia, verso l’orizzonte!... Bensì a quello che ci aspetta qui, su questa soglia! All’amore che ci richiama a sé, anche dall’altro capo del mondo e dalle montagne d’oro! Vivilo, e sii felice!";
			link.l1 = "Gran brindisi, Marcus, grazie!";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6_1":
			dialog.text = "Un brindisi, al tuo matrimonio, compagno!";
			link.l1 = "Grazie, Marcus...";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6":
			DialogExit();
			npchar.dialog.currentnode = "Terrax_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Terrax_7":
			dialog.text = "Jacques? Questo non promette niente di buono...";
			link.l1 = "Marcus, pensi che...";
			link.l1.go = "Terrax_8";
		break;
		
		case "Terrax_8":
			dialog.text = "Non c’è tempo! Sono dietro le porte! Tutti alle armi!";
			link.l1 = "Eccoci qua!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernFight");
		break;
		
		case "Terrax_9":
			dialog.text = "Non ricordo l’ultima volta che mi sono divertita così tanto a una festa! Ma non è ancora finita! Senti anche tu? Qualcuno sta sparando fuori! Facciamo scorrere il loro sangue per le strade, giusto?";
			link.l1 = "Aspetta! Chi diavolo sono quelli?! E che diavolo vogliono da noi?!";
			link.l1.go = "Terrax_10";
		break;
		
		case "Terrax_10":
			DialogExit();
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		// Натаниэль Хоук
		case "Nathaniel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Capitano de Maure sposato, raramente ho trovato motivi più sinceri per un brindisi. Alziamo i bicchieri – questa non è la solita bevanda da quattro soldi. È infusa con tè nero delle Indie Orientali e speziata con veri aromi persiani!";
			link.l1 = "E pensavo proprio a perché mi brucia la gola come se avessi bevuto piombo fuso. Beh, Nathan, alla salute...";
			link.l1.go = "Nathaniel_1";
		break;
		
		case "Nathaniel_1":
			dialog.text = "Aspetta, prima un brindisi! Ehi, gentiluomini, alzate i boccali! Oggi il nostro amico e compagno Charles de Maure imbocca la via della vita familiare. Accetta da noi le più sentite condoglian... oh, Dannie per favore, abbassa la pistola! Congratulazioni, ovviamente! Ora siete le vele della stessa nave, quindi conducila attraverso ogni tempesta verso le coste più fertili!";
			link.l1 = "Grazie, Nathan, davvero. Tu e Danielle siete un esempio da seguire per tutti noi.";
			link.l1.go = "Nathaniel_2";
		break;
		
		case "Nathaniel_2":
			dialog.text = "Mi fa piacere sentirtelo dire. Io e mia moglie forse non siamo la coppia perfetta del mondo, ma insieme siamo felici, e tu hai fatto così tanto per noi che, se vuoi saperlo, ti considero parte della mia famiglia, e ci sarò sempre per te quando avrai bisogno. Sii felice, e bevi qualcosa, mi raccomando!";
			link.l1 = "Beviamo allora! Oh... questo rum dovrebbe stare nell’arsenale della Santa Inquisizione. Maledizione! Brucia dalla gola fino allo stomaco... aghhh! Uff!... Mi piace, giusto?";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_3":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_3_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Nathaniel_3_1":
			dialog.text = "Sembri proprio me e Dannie vent’anni fa!";
			link.l1 = "Un altro bicchiere, Nathan, giusto?";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Cosa!? Jan ti ha mandato nelle cantine a prendere del vino? Dai, facciamo due passi, ti do una mano e un po' d’aria fresca ci farà bene, giusto?";
			link.l1 = "Ma dove sono Dannie e "+sld.name+"? Jan mi ha detto che erano andati a parlare.";
			link.l1.go = "Nathaniel_5";
		break;
		
		case "Nathaniel_5":
			dialog.text = "Sì, Dannie sa bene che anche la presenza della miglior compagna d’armi non basta a far rilassare del tutto i gentiluomini della ventura. Così hanno ascoltato tutti i complimenti ricevuti e poi sono andate alla residenza, lasciando i ragazzi a divertirsi, giusto?";
			link.l1 = "Allora, muoviamoci! Sono riuscita a scolarmi un paio di boccali, ma maledizione, adesso è proprio il momento di ubriacarsi come si deve, giusto?";
			link.l1.go = "Nathaniel_6";
		break;
		
		case "Nathaniel_6":
			DialogExit();
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableFastReload = true;//закрыть переход
			pchar.quest.longhappy_isla_vine.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_vine.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_isla_vine.function = "LongHappy_IslaTesoroToAlexus";
		break;
		
		case "Nathaniel_7":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "Ecco il forziere. Prendiamo tutto quello che riusciamo a portare e torniamo indietro, prima che quel vecchio brontolone ci chiuda qui dentro.";
			link.l1 = "Esageri, Nathan. Non è poi così terribile... Aspetta, hai sentito anche tu?";
			link.l1.go = "Nathaniel_8";
		break;
		
		case "Nathaniel_8":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "Jan probabilmente ha trovato altri uomini e li ha mandati ad aiutarci. Maledizione!";
			link.l1 = "Dai, le bottiglie si rompono per buona sorte. Prendine un'altra e andiamo, giusto?";
			link.l1.go = "Nathaniel_9";
		break;
		
		case "Nathaniel_9":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum") && GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu");
				sld.dialog.currentnode = "Tichingitu_8";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else LongHappy_SetBandosInDungeon();
		break;
		
		case "Nathaniel_10":
			dialog.text = "Che diavolo sta succedendo, chi sono questi bastardi? Capisci qualcosa, Charles?";
			link.l1 = "Non lo so, Nathan, ma uno di loro è corso a chiamare rinforzi e mi pare di sentire altri passi. Dobbiamo tornare alla taverna!";
			link.l1.go = "Nathaniel_11";
		break;
		
		case "Nathaniel_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			pchar.quest.longhappy_totavern.win_condition.l1 = "location";
			pchar.quest.longhappy_totavern.win_condition.l1.location = "Pirates_tavern";
			pchar.quest.longhappy_totavern.function = "LongHappy_TavernAlarm";
		break;
		
		case "Nathaniel_12":
			LongHappy_TownRepose();
			dialog.text = "Abbiamo sistemato questi bastardi, ma senti i cannoni che tuonano dal mare? Abbiamo solo due equipaggi pronti a combattere, sulla fregata di Marcus e sulla corvetta di Jan. Io, Dannie e gli altri abbiamo sbarcato la nostra gente – dopotutto c'è il matrimonio – quindi il Centurion è fuori gioco. E la tua nave? Dobbiamo decidere in fretta che fare!";
			link.l1 = "Ho già sbarcato metà dell’equipaggio, spero che il resto sia sobrio. Ma prima devo trovare mia moglie e assicurarmi che stia bene.";
			link.l1.go = "Nathaniel_13";
		break;
		
		case "Nathaniel_13":
			dialog.text = "Sì, neanche Dannie si vede da nessuna parte. Allora facciamo così: Tyrex e Svenson sono già corsi al porto, raggiungeranno le loro navi con le scialuppe. Noi andiamo alla residenza delle mogli, gli altri che organizzino la difesa a terra. Puoi mandare alcuni dei tuoi ufficiali a radunare gente sulla tua nave? Un po’ d’aiuto lì di certo non guasta.";
			link.l1 = "Bene, avanti tutti! Ogni secondo è prezioso!";
			link.l1.go = "Nathaniel_14";
		break;
		
		case "Nathaniel_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
		break;
		
		case "Nathaniel_15":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Più in fretta, di sopra! Dannie e "+sld.name+" Devono essere lì! E se quei bastardi gli hanno fatto del male...";
			link.l1 = "Non ci pensare nemmeno! Al piano di sopra! Andiamo!";
			link.l1.go = "Nathaniel_16";
		break;
		
		case "Nathaniel_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_townhall", "reload1_back", true);
			pchar.quest.longhappy_isla_bedroom.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_bedroom.win_condition.l1.location = "Location_reserve_04";
			pchar.quest.longhappy_isla_bedroom.function = "LongHappy_IslaTesoroBedroom";
		break;
		
		case "Nathaniel_17":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Maledizione! Quel tuo compare si è lanciato dritto davanti alla canna per non far sparare quel bastardo alle ragazze!";
			link.l1 = "E si è preso una pallottola... Aspetta, Nathan... respira! È ancora vivo! Maledizione, ho bisogno di Gino! "+sld.name+", tesoro, come stai?";
			link.l1.go = "Nathaniel_18";
		break;
		
		case "Nathaniel_18":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_19";
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_7_1";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Nathaniel_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Stiamo bene, Charles! Vado a liberarla. Sento spari nel porto – tu e Nathan dovete andare subito laggiù, altrimenti Barbazon distruggerà tutte le nostre navi. Non perdete tempo!";
			link.l1 = "Troverò Gino e lo manderò qui, lui ti aiuterà... deve farlo, giusto?"+sld.name+", cara, resta qui, occupati di lui, tutti e due.";
			link.l1.go = "Nathaniel_19";
		break;
		
		case "Nathaniel_19":
			dialog.text = "Charles, sbrigati! Qualunque sia la tua decisione, adesso il tempo vale oro! Se le navi di Jacques arrivano a riva, tutto sarà stato inutile!";
			link.l1 = "Sì, lo so. Maledetto bastardo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Nathaniel_20":
			dialog.text = "Più in fretta, non c’è tempo per chiacchiere!";
			link.l1 = "";
			link.l1.go = "Nathaniel_20_1";
		break;
		
		case "Nathaniel_20_1":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_20";
		break;
		
		case "Nathaniel_21":
			dialog.text = "Maledizione! Perdonami Charles. Siamo rimasti bloccati al piano di sopra, c’erano una dozzina di quei bastardi... Peccato non essere arrivata prima, ma vedo che te la sei cavata alla grande, giusto?";
			link.l1 = "Non posso dire che sia stato facile, ma, accidenti, ho provato un enorme piacere quando ho fatto fuori quel 'galantuomo'! È ora di scendere a terra, Nathan, la nostra gente ci aspetta laggiù!";
			link.l1.go = "Nathaniel_22";
		break;
		
		case "Nathaniel_22":
			dialog.text = "Sì, dobbiamo andare dal tuo ragazzo indiano, finire qui e poi salpare per Sharptown, giusto?";
			link.l1 = "Hai ragione, sono con te, giusto?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Nathaniel_23";
			else link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_23":
			dialog.text = "A proposito, abbiamo trovato Marcus! Era nella stiva, legato e privo di sensi.";
			link.l1 = "È ancora vivo, giusto?";
			link.l1.go = "Nathaniel_24";
		break;
		
		case "Nathaniel_24":
			dialog.text = "È messo male, ma se la caverà. Tyrex è più duro di un chiodo da bara, quindi non preoccuparti, è già stato portato sulla tua nave e ha chiesto una sciabola.";
			link.l1 = "Finalmente una buona notizia! Bene, finiamo qui e torniamo indietro, giusto?";
			link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		// Даниэль Хоук
		case "Danielle":
			dialog.text = "Ciao, Charles. Fammi dare un'occhiata – sei diventato ancora più bello, non posso lamentarmi! Proprio come Nathan, dieci anni fa! Entra, non restare sulla soglia, tutti ti stavano aspettando!";
			link.l1 = "Grazie, Dannie, sono davvero felice di vederti! Più tardi verrò da te e Nathan, così potremo parlare con calma!";
			link.l1.go = "Danielle_1";
		break;
		
		case "Danielle_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "tables", "stay1", "LongHappy_DannyNorm", -1); 
		break;
		
		case "Danielle_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, accomodati – Nathan ed io siamo davvero felici per te! Marcus, Jan e mio marito hanno preparato qualcosa per te, ma i regali possono aspettare. Ora lasciami solo farti le mie congratulazioni e augurarti ogni felicità! La tua scelta è davvero un prodigio! Dimmi, non sarai riuscito a farle indossare un abito bianco laggiù a Martinica, vero?";
			link.l1 = "Grazie, Dannie. Sì, è stato buffo con l’abito – sono sicuro che tra la gente di alto rango il nostro matrimonio ha fatto nascere pettegolezzi a non finire. Tutti distoglievano lo sguardo facendo finta che non accadesse nulla di insolito. Modi, etichetta e simili… ma a me delle chiacchiere non importa niente, io la amo e questo è ciò che conta davvero.";
			link.l1.go = "Danielle_3";
		break;
		
		case "Danielle_3":
			dialog.text = "Hai proprio ragione! Anch'io sono arrivata all'altare con la spada al fianco e due pistole infilate nella fascia. Ma era a Port Royal, ancora prima che diventasse una residenza coloniale rispettabile. All'epoca ci si divertiva da matti, persino più che a Tortuga sotto Levasseur, e nessuno ci trovava nulla di strano... eh. Ma guarda come mi sono messa a chiacchierare – vai, fai un giro tra gli ospiti, tutti ti aspettano qui, dammi solo un abbraccio!";
			link.l1 = "Ah Dannie, come potrei mai dirti di no, ahah! Non puoi nemmeno immaginare quanto io e mia moglie siamo felici di vedervi tutti, giusto?";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_4":
			DialogExit();
			npchar.dialog.currentnode = "Danielle_4_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Danielle_4_1":
			dialog.text = "Siete proprio una bella coppia, Charles!";
			link.l1 = "Grazie, Dannie...";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_5":
			dialog.text = "Charles, ha ragione... non hai altra scelta. Non credo nella clemenza di Jacques il Buonaccio, se fa affari con Tyrex e quella feccia. Sai cosa va fatto.";
			link.l1 = "";
			link.l1.go = "Danielle_6";
		break;
		
		case "Danielle_5_1":
			dialog.text = "Non dargli ascolto! Se il Kindman ha deciso di fare una pazzia simile, non risparmierà nessuno!";
			link.l1 = "";
			link.l1.go = "Danielle_6_1";
		break;
		
		case "Danielle_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_39";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_6_1":
			DialogExit();
			sld = characterFromId("LH_Dussak");
			sld.dialog.currentnode = "Dussak_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_7_1":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Stiamo bene, Charles! La libero io. Sento i cannoni nel porto, tu e Nathan dovete andare subito laggiù, altrimenti Barbazon ci affonderà le navi come anatroccoli in una botte. Non dovete perdere neanche un minuto!";
			link.l1 = "Troverò Gino e lo manderò qui, lui ti aiuterà ... deve farlo, accidenti!"+sld.name+", cara, resta qui e bada a Tichingitu.";
			link.l1.go = "Danielle_8_1";
		break;
		
		case "Danielle_7":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Nathan, no!!!";
			link.l1 = "Ha colto l’attimo e si è precipitato al cannone per coprirti, Dannie... "+sld.name+", tesoro, come stai?";
			link.l1.go = "Danielle_8";
		break;
		
		case "Danielle_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_41";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_8_1":
			DialogExit();
			sld = characterFromId("Nathaniel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_9":
			dialog.text = "Sì, Charles, è vivo! Il cuore batte appena, ma è vivo! Che facciamo?!";
			link.l1 = "Abbiamo bisogno di Gino, subito! Lo troverò e lo mando qui, lui ci aiuterà... deve farlo!";
			link.l1.go = "Danielle_10";
		break;
		
		case "Danielle_10":
			dialog.text = "Charles, non abbiamo tempo! Se le navi di Jacques arrivano a riva, sarà tutto inutile! Mio marito... ha fatto ciò che doveva. Ora tocca a te. Io resto con lui. Voi due andate a cercare Gino!";
			link.l1 = "Sì, lo so. Maledetto bastardo, la pagherà cara!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Danielle_11":
			dialog.text = "Eccoti finalmente! Tutti stanno bene, giusto?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				link.l1 = "Stiamo bene, Dannie, non preoccuparti. Jacques è morto, le sue navi sono in fondo al mare. Come sta Tichingitu?";
				link.l1.go = "Danielle_17";
			}
			else
			{
				link.l1 = "Stiamo bene, Dannie, non preoccuparti. Jacques è morto, le sue navi ora giacciono sul fondo del mare. E Nathan, come sta?";
				link.l1.go = "Danielle_12";
			}
		break;
		
		case "Danielle_12":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "Sta bene! Il tuo dottore italiano è un genio! Nathan dorme di sopra, ma secondo Gino non c'è alcun pericolo. Una o due settimane a letto, vino rosso e, come ha detto lui, 'la visita di una signora benevola' ehm... Insomma – tutto a posto, ci hai salvati di nuovo, Charles, come posso ringraziarti?";
				link.l1 = "È stato Nathaniel a salvare mia moglie e te. Gli sarò per sempre debitore per questo. Non puoi nemmeno immaginare quanto mi rallegri sapere che si sta riprendendo. Lascialo riposare, tornerò a vedere come state più tardi.";
				link.l1.go = "Danielle_13";
			}
			else
			{
				dialog.text = "Sta bene, il proiettile è passato da parte a parte, e il nostro cerusico del 'Centurion' era lì vicino. Si nascondeva da tutto questo casino. Quindi Nathan se la caverà, un paio di settimane a letto – niente di che!";
				link.l1 = "Dannie, ha protetto mia moglie e te da una pallottola e gli sarò debitore per sempre. Non puoi nemmeno immaginare quanto sia felice di sapere che si sta riprendendo. Lascialo riposare, vi controllerò più tardi.";
				link.l1.go = "Danielle_14";
			}
		break;
		
		case "Danielle_13":
			dialog.text = "Certo! Ma ora devo lasciarti, devo andare da mio marito... Non ti dispiace se prendiamo in prestito il tuo amico? Quando Nathan starà meglio, lo porterò io stessa ad Antigua. Il Centurion è sopravvissuto per miracolo, deve solo reclutare un nuovo equipaggio.";
			link.l1 = "Va bene, Dannie, saluta Gino e Nathan da parte mia. Ora dovrei andare, giusto?";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_14":
			dialog.text = "Certo, Charles, ma... ho brutte notizie. Quell’italiano, Guineili, che era al tuo matrimonio... Hanno trovato il suo cadavere in una stanza della taverna. Mi dispiace, Charles.";
			link.l1 = "Cosa? Gino?! No! Ma come?";
			link.l1.go = "Danielle_15";
		break;
		
		case "Danielle_15":
			dialog.text = "Non lo so, probabilmente uno di quei bastardi che hanno attraversato le catacombe e attaccato la città. A quanto pare si nascondevano lì, aspettando il momento giusto per scappare, e l'hanno trovato loro...";
			link.l1 = "Merda! No, non ci posso credere...";
			link.l1.go = "Danielle_16";
		break;
		
		case "Danielle_16":
			pchar.questTemp.LongHappy.Jino_died = "true";
			dialog.text = "Mi dispiace, Charles. È stata una maledetta carneficina, e lui non era certo un combattente... Se vuoi, manderemo il suo corpo sulla tua nave, così potrai riportarlo a casa e dargli sepoltura come si deve. Mi dispiace davvero...";
			link.l1 = "Grazie, Dannie. Dai l’ordine di caricare il corpo sulla nave. Ora devo andare... Devo riflettere. E saluta Nathan da parte mia.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_17":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "Sta benone! Il tuo medico italiano è un genio! Sta dormendo nella stanza di sopra e Gino si sta occupando di lui. Dice che 'una settimana o due e starà come nuovo'.";
				link.l1 = "Una bella notizia! Immagino che non posso andarlo a trovare adesso, giusto?";
				link.l1.go = "Danielle_18";
			}
			else
			{
				dialog.text = "Mi dispiace tanto, Charles. Ho trovato il nostro chirurgo del Centurion, ma non ha potuto fare nulla... Il tuo amico è spirato un paio d’ore fa.";
				link.l1 = "Tichingitu?! No! Non ci credo!!!";
				link.l1.go = "Danielle_19";
			}
		break;
		
		case "Danielle_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "No, l’italiano aveva proprio proibito di disturbarlo, lasciatelo riposare, e dopo tutte quelle preoccupazioni pure Gino merita un po’ di pace. L’ho detto anch’io "+sld.name+"  siamo usciti a fare una passeggiata quando abbiamo scoperto che sarebbe andato tutto bene\nE un’altra cosa... il tuo amico, mi ha protetta dal colpo di pistola. Non so nemmeno come ringraziarlo, digli che d’ora in poi fa parte anche lui della nostra famiglia, e tu — tu ci hai salvati ancora una volta, Charles!";
			link.l1 = "Tutto è bene quel che finisce bene, Dannie. Vai da Nathan, ti sta aspettando, e io mi riposo un po' qui e do un'occhiata in giro per il mio "+sld.name+".";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_19":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Scusa, ho fatto tutto ciò che potevo, e "+sld.name+", anche. Ci ha protetti da quella pallottola, e non lo dimenticherò mai, credimi.";
			link.l1 = "... Tanto tempo fa diceva che sarebbe morto per me... Credo non abbia mai immaginato che avrebbe davvero dato la vita per tutti noi... e adesso è un eroe, e io lo ricorderò sempre così... Dov'è "+sld.name+"Sta bene, giusto?";
			link.l1.go = "Danielle_20";
		break;
		
		case "Danielle_20":
			dialog.text = "Non posso dirlo... Cioè, fisicamente sì. Ma... capisci... Ha detto che è uscita a fare una passeggiata, per schiarirsi le idee. Probabilmente ti ha visto attraccare e tornerà presto.";
			link.l1 = "Maledizione a te, Jacques Barbazon... Dovevamo farlo fuori prima!";
			link.l1.go = "Danielle_21";
		break;
		
		case "Danielle_21":
			dialog.text = "Aspetta... non è ancora tutto. Quell’italiano, Guineili, giusto? Quel ragazzo così silenzioso. Lui... il suo corpo è stato trovato in una taverna... Non so, probabilmente uno di quei bastardi che hanno attraversato le catacombe e assalito la città. A quanto pare si nascondevano là sotto, aspettando il momento giusto per svignarsela, e lo hanno trovato loro...";
			link.l1 = "E anche Gino?! Oggi è proprio una giornata storta, giusto?";
			link.l1.go = "Danielle_22";
		break;
		
		case "Danielle_22":
			pchar.questTemp.LongHappy.Tichingitu_died = "true";
			dialog.text = "Mi dispiace, Charles... Se vuoi, faremo portare i loro corpi sulla tua nave, così potrai riportarli a casa e seppellirli come si deve. Mi spiace davvero...";
			link.l1 = "Grazie Dannie. Fallo... Devo andare... Ho bisogno... di pensare.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		// Додсон
		case "Dodson":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, riesci anche solo a immaginare quante ragazze hai spezzato il cuore con questo tuo matrimonio? Scommetto che metà delle fanciulle dell'arcipelago hanno pianto il giorno delle tue nozze, ahah!";
			link.l1 = "Che posso farci – me ne serviva solo una e l’ho trovata. Ma è presto perché le ragazze siano tristi, visto che hanno ancora te, Stiven.";
			link.l1.go = "Dodson_1";
		break;
		
		case "Dodson_1":
			dialog.text = "E questo è vero! Finiamo qui e subito dopo mi occuperò di loro, accidenti! Dai, Charles, beviamo alla tua fortuna e alla vita familiare. Così, come si dice, vissero felici e contenti!";
			link.l1 = "Grazie, amico mio!";
			link.l1.go = "Dodson_2";
		break;
		
		case "Dodson_2":
			DialogExit();
			npchar.dialog.currentnode = "Dodson_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Dodson_2_1":
			dialog.text = "Alla felicità familiare, ah-ah!";
			link.l1 = "Salute!";
			link.l1.go = "Dodson_2";
		break;
		
		// Венсан
		case "Vensan":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, riesci a immaginare quante ragazze hai spezzato il cuore con questo tuo matrimonio? Scommetto che metà delle ragazze dell’arcipelago hanno pianto dopo le tue nozze, ahah!";
			link.l1 = "Che ci posso fare – ne volevo solo una e l’ho già conquistata. Ma è presto perché le altre ragazze si disperino, alla fine ci sei ancora tu, Bernard.";
			link.l1.go = "Vensan_1";
		break;
		
		case "Vensan_1":
			dialog.text = "E questo è vero! Finiremo qui e subito dopo me ne occupo io, accidenti! Dai, Charles, beviamo alla tua fortuna e alla vita familiare. Così, come si dice, vissero felici e contenti, giusto?";
			link.l1 = "E vissero felici e contenti!";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_2":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_2_1":
			dialog.text = "Per una vita familiare felice, ah ah!";
			link.l1 = "Un gran brindisi!";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Ahah, Charles, anche tu ti sei sistemato e sei diventato noioso, proprio come il nostro vecchio Nathan! Avventure infuocate e tutto il resto sono ormai roba passata, giusto? Un vero uomo di famiglia, ormai!";
			link.l1 = "Continua pure ad aspettare, Bernard! Mia moglie non è certo una di quelle che si annoiano sedute sotto la finestra di una casa cadente! L'unica cosa che cambierà saranno le borse piene delle ragazze da bordello, da qui fino a Curaçao!";
			link.l1.go = "Vensan_4";
		break;
		
		case "Vensan_4":
			dialog.text = "Non è una gran perdita, dico io! Meglio una moneta d’oro che un sacchetto di spiccioli. Beviamoci su! Un brindisi a te e a tua moglie! Tieni l’oro al sicuro e goditi la felicità!";
			link.l1 = "Grazie Bernard. Oh, questo rum è davvero forte. Uff!";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_5":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_5_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_5_1":
			dialog.text = "Alla tua sposa, anzi, ormai già moglie!";
			link.l1 = "Grazie!";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_6":
			dialog.text = "Sei arrivato proprio al momento giusto, Charles, grazie!";
			link.l1 = "Qual è il divertimento qui? Pensavo che fossi già impegnato a caricare le navi nel porto, giusto?";
			link.l1.go = "Vensan_7";
		break;
		
		case "Vensan_7":
			dialog.text = "Marcus mi ha lasciata a organizzare la difesa sulla costa. Siamo a corto di gente, i ragazzi al porto hanno bisogno di polvere da sparo. Ho pensato di passare di qui, prendere un paio di barili... e poi questi furfanti. Eh, si sono nascosti, credo, volevano aspettare o rapinare qualcuno. E sono ancora piena del rum di Hawk, quindi senza di te, non so proprio, sarei ancora viva oppure no, giusto?";
			link.l1 = "Sei sempre la benvenuta. Bene, Bernard, tu assicurati che la città sia al sicuro, e io devo andare, stammi bene!";
			link.l1.go = "Vensan_8";
		break;
		
		case "Vensan_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.LongHappy.Vensan_alive = "true";
		break;

		// Джино
		case "Jino":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Capitano, permettetemi di congratularmi di cuore con voi e la vostra amata in questo giorno felice! Siate felici e abbiate cura l’uno dell’altra!";
			link.l1 = "Grazie, Gino. Sono felice che tu abbia deciso di venire! Spero che i colori locali non ti diano fastidio, giusto?";
			link.l1.go = "Jino_1";
		break;
		
		case "Jino_1":
			dialog.text = "Questo viaggio... è davvero istruttivo. Devo ammettere che non uscivo da Antigua da tanto tempo, e in questa società non è facile sentirmi a mio agio. Però tu hai sempre saputo capire la gente, quindi cercherò di restare tranquilla, perché mi fido di te.";
			link.l1 = "Forse ti serve bere qualcosa di più forte? Rilassati e trova qualcuno con cui chiacchierare, giusto?";
			link.l1.go = "Jino_2";
		break;
		
		case "Jino_2":
			dialog.text = "Grazie, capitano, ho già avuto abbastanza vino annacquato. L’alcool, devo avvertirti, non fa molto bene al fegato e forse neanche al cuore. Quanto alle conversazioni, ho cercato di discutere delle proprietà curative del Chirik-Sanango con quel gentiluomo laggiù, si chiama anche Manaka. I nativi del Maine lo usano per...";
			link.l1 = "Fammi indovinare – quel gentiluomo non ha retto la conversazione? Gino, per me, solo per oggi – prova il rum che Jan sta versando laggiù al bancone. Se riesci a indovinare tutti gli ingredienti, Nathaniel Hawk, laggiù, sarà davvero colpito, giusto? Sono certa che sarà felice di stare in tua compagnia, così come Svenson, quello al bancone; entrambi rispettano la gente istruita.";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_3":
			DialogExit();
			npchar.dialog.currentnode = "Jino_3_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.HambitOfficer"))
				{
					sld = characterFromId(pchar.questTemp.LongHappy.HambitOfficer);
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Baker") != -1)
					{
						sld = characterFromId("Baker");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						if (GetCharacterIndex("Tichingitu") != -1)
						{
							sld = characterFromId("Tichingitu");
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
						else
						{
							sld = characterFromId("Mary");
							sld.dialog.currentnode = "LongHappy_57";
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
					}
				}
			}
			else (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Jino_3_1":
			dialog.text = "Alla tua salute e a quella della tua affascinante consorte!";
			link.l1 = "Grazie, amico!";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_4":
			dialog.text = "Capitano, sei tu, grazie al cielo! Quei mascherati li ho visti e mi sono nascosta qui, hanno provato pure a sfondare la porta...";
			link.l1 = "Va tutto bene, Gino, nessuno ti farà più del male. È una vera fortuna che ti abbia trovato, ho bisogno del tuo aiuto. Il mio amico è ferito – gli hanno sparato e ha perso molto sangue. Dobbiamo sbrigarci!";
			link.l1.go = "Jino_5";
		break;
		
		case "Jino_5":
			dialog.text = "Spari... sangue... va bene, capitano. Mentre venivo qui, ho preso la mia cassa da campo con tutti gli strumenti per le ferite. Portami da lui, vedrò cosa si può fare. E questi... uomini mascherati, magari si sono nascosti da qualche altra parte?";
			link.l1 = "Sono sicura, erano gli ultimi. Gino, c’è battaglia nel porto e devo andarci subito. Tu vai alla residenza da solo, non è lontano. La casa grande è dietro l’angolo – non puoi sbagliarti. Non avere paura – le strade sono piene della nostra gente, e sbrigati, ti prego!";
			link.l1.go = "Jino_6";
		break;
		
		case "Jino_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 7.0);
			LocatorReloadEnterDisable("Pirates_tavern", "reload1_back", false);
			pchar.questTemp.LongHappy.Jino_alive = "true";
			AddQuestRecord("LongHappy", "18");
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sld = characterFromId("Tichingitu");
			else sld = characterFromId("Nathaniel");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName1", sTemp);
		break;
		
		case "Jino_7":
			dialog.text = "Capitano, lasciate che vi porga le mie più vive congratulazioni a voi e alla vostra amata in questo giorno propizio! Siate felici e abbiate cura l’uno dell’altra.";
			link.l1 = "Grazie, Gino. Sono felice che tu abbia deciso di venire! Spero che il viaggio sia andato liscio, giusto?";
			link.l1.go = "Jino_8";
		break;
		
		case "Jino_8":
			dialog.text = "Tutto va bene, capitano, grazie per la premura. Devo ammettere che non mettevo piede fuori da Antigua da un bel pezzo, e tra la gente di rango... non mi sento proprio a mio agio. Ma la ragione che mi ha portata qui non mi lasciava alternative. A proposito, il servizio è stato impeccabile, sono proprio felice per voi due! La sposa con quell'abito è incantevole – è una nuova moda? Sembra che io sia rimasta indietro con la vita, ma mi piace, davvero.";
			link.l1 = "La moda... In un certo senso sì, o almeno, lo sarà presto. Va bene, divertiti pure, Gino, e se quei nobili ti annoiano, vieni al porto. Tutta la ciurma è in taverna. I ragazzi saranno felici di vederti.";
			link.l1.go = "Guests_block";
		break;
		
		case "Jino_9":
			dialog.text = "Capitano, ancora una volta, congratulazioni a te e alla tua splendida sposa! Che abbiate lunghi e felici anni insieme!";
			link.l1 = "Grazie, Gino. Sono felice che tu sia venuto! Spero che il colore locale non ti disturbi troppo, giusto?";
			link.l1.go = "Jino_10";
		break;
		
		case "Jino_10":
			dialog.text = "Non è facile per me sentirmi a mio agio in questa società. Ma tu hai sempre saputo scegliere le persone giuste, quindi cercherò di restare tranquilla, perché mi fido di te...";
			link.l1 = "Forse dovresti bere qualcosa di più forte? Rilassati e trova qualcuno con cui chiacchierare, giusto?";
			link.l1.go = "Jino_11";
		break;
		
		case "Jino_11":
			dialog.text = "Grazie, capitano, ho già avuto abbastanza vino annacquato. L’alcool, devo avvertirti, non fa proprio bene né al fegato né, forse, al cuore. Quanto alle conversazioni, ho provato a discutere delle proprietà curative del Chirik-Sanango con quel gentiluomo, si chiama anche Manaka. I nativi del Maine lo usano per...";
			link.l1 = "Fammi indovinare – quel gentiluomo non ha retto la discussione? Gino, per me soltanto per oggi – prova il rum che Jan sta versando laggiù al bancone. Se riesci a indovinare tutti gli ingredienti, Nathaniel Hawk, lo vedi laggiù, rimarrà davvero colpito. Son certa che sarà lieto della tua compagnia, come anche Svenson, quello al banco: entrambi rispettano chi sa il fatto suo, giusto?";
			link.l1.go = "Jino_3";
		break;
		
		// Лонгвэй
		case "Longway":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "   Ora sola in terra straniera, straniera anch’io, in questo giorno di festeggiamenti sento ancor più la nostalgia dei miei cari   ";
			link.l1 = "Longway, mai avrei detto che fossi un maestro con le parole, giusto?";
			link.l1.go = "Longway_1";
		break;
		
		case "Longway_1":
			dialog.text = "Perdonami, Capitano, sono stata immersa nei miei pensieri. Queste sono le parole di Wang Wei, un poeta vissuto durante la dinastia Tang che governò la mia patria tanto tempo fa.";
			link.l1 = "Queste parole sono così belle. Spero che un giorno rivedrai la tua terra natale...";
			link.l1.go = "Longway_2";
		break;
		
		case "Longway_2":
			dialog.text = "''Si può forse giurare che sotto l’arco di misteriose lastre di pietra sia impossibile, tentando e riprovando, trovare un passaggio verso la valle degli U-lin?'\nNo, Capitano, lo sai bene — Longway non tornerà più a casa. Ora è qui la mia dimora, e oggi ci attende una grande festa! Ti mando i miei auguri più sentiti, a te e alla tua splendida sposa! Che la vostra felicità scorra lunga come lo Yangtze, costellato di diamanti di stelle tra perle di loto.";
			link.l1 = "Grazie, vecchio amico. Le tue parole sono belle quanto quelle di Wang Wei.";
			link.l1.go = "Longway_3";
		break;
		
		case "Longway_3":
			dialog.text = "Beviamo qualcosa, Capitano! Questo rum scaccia la malinconia e ravviva l’allegria meglio di qualunque maotai, giusto?";
			link.l1 = "Alla tua salute, Longway!";
			link.l1.go = "Longway_4";
		break;
		
		case "Longway_4":
			DialogExit();
			npchar.dialog.currentnode = "Longway_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Longway_4_1":
			dialog.text = "Gran bel matrimonio, capitano!";
			link.l1 = "Bevi e divertiti!";
			link.l1.go = "Longway_4";
		break;
		
		// Книппель
		case "Knippel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "Lanciami una catena! Tutti i nostri ti fanno i complimenti! Com'è andato il colpo, giusto?";
				link.l1 = "Va tutto bene, Charlie! Ora sono ufficialmente sposata e rispettabile, e la mia prima ufficiale è madame de Monper adesso.";
			}
			else
			{
				dialog.text = "Colpiscimi con una scarica a catena, che serata, capitano! Qui ci sono quasi tutti i baroni della Fratellanza! Scommetto che ogni puritano spagnolo si immagina l’Inferno proprio così! E il rum, è qualcosa di speciale, una scarica a catena dritta nella mia botte!";
				link.l1 = "Già, qui la legge non è proprio di casa, ma nemmeno noi siamo santi, Charlie, e ognuno di queste persone mi è caro a modo suo, giusto?";
			}
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "È magnifico, una scarica di catene sul mio didietro! Capitano, cioè, questa festa è in tuo onore, beh, io... io, congratulazioni, cioè... anche... felicità e... ecco, non sono brava con i discorsi. Ma devi sapere che ti vogliamo tutti bene, a entrambi, e ti seguiremo anche all'inferno, capitano!";
				link.l1 = "Grazie, vecchio amico.";
			}
			else
			{
				dialog.text = "Aspetta, cioè... Ma che dico, una scarica di mitraglia sul mio sedere?! Capitano, volevo dire che oggi è il tuo giorno, insomma, io... ti faccio i miei auguri... e anche... ti auguro felicità e... e scusa cap, forse sono troppo sbronza per fare un discorso, catena alla gola, è da un po' che non sono sobria ah-ah-ah!";
				link.l1 = "Hah! Va tutto bene... grazie, vecchio amico.";
			}
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			Log_Info("You have got gems");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry4", 20);
			dialog.text = "Ah! E sì, capitano, accetta questo, ti prego. Per te e la tua signora. Ho tenuto queste pietre per i tempi duri... Capisco che l’oro non ti manca, ma non saranno di troppo, giusto?";
			link.l1 = "Charlie, sei davvero un’anima generosa, e questi smeraldi staranno una meraviglia negli orecchini di famiglia della madame de Monper!";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			dialog.text = "E allora brindiamo a questo, una scarica di mitraglia per la mia... ehm. Siate felici, tu e la tua bellezza, capitano!";
			link.l1 = "Lo faremo, Charlie, giusto?";
			link.l1.go = "Knippel_4";
		break;
		
		case "Knippel_4":
			DialogExit();
			npchar.dialog.currentnode = "Knippel_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Knippel_4_1":
			dialog.text = "Un gran bel matrimonio, capitano!";
			link.l1 = "Bevi e divertiti!";
			link.l1.go = "Knippel_4";
		break;
		
		// Тонзаг
		case "Tonzag":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Mai avrei pensato, capitano, di vederti sposato. Di solito, la rotta che abbiamo scelto conduce dritta verso una tomba solitaria. Che io ricordi, sei il primo che sia mai riuscito a cambiare destino. Un brindisi in più ci sta tutto, non credi?";
			link.l1 = "Eccoci qui, amico! E davvero, sono felice che questa parte della mia vita sia ormai acqua passata. Salute!";
			link.l1.go = "Tonzag_1";
		break;
		
		case "Tonzag_1":
			dialog.text = "Un brindisi a voi e alla vostra lunga e felice vita insieme! Maledizione, a guardarvi mi viene in mente che anch’io un tempo ero sposato.";
			link.l1 = "Tu? Sposato? Ma guarda un po’ che storie mi racconti! E allora, che è successo?";
			link.l1.go = "Tonzag_2";
		break;
		
		case "Tonzag_2":
			dialog.text = "Cosa credi, che sia sempre stata un vecchio ciclope puzzolente di polvere da sparo e sangue, capitano? Eh no. Madame Tonzag lei... mi voleva bene, suppongo. Ma poi successe una brutta storia. In cui la coppia Tonzag finì male e solo il buon Gaston il Pelato, con la sua collezione di cicatrici, ne uscì vivo.";
			link.l1 = "Mi dispiace, Hercule, non lo sapevo...";
			link.l1.go = "Tonzag_3";
		break;
		
		case "Tonzag_3":
			dialog.text = "Dimenticalo, capitano, quella storia è roba vecchia ormai. Ma ora, guardandoti, penso che la mia storia possa ancora avere un lieto fine. Allora, beviamoci su!";
			link.l1 = "Andiamo, amico. Sai, dal giorno in cui ti ho incontrato, ti ho sempre visto come avrei visto mio padre, quindi magari un giorno potrai diventare un grande nonno. Comunque, salute! Devo occuparmi del resto, parleremo dopo.";
			link.l1.go = "Tonzag_4";
		break;
		
		case "Tonzag_4":
			DialogExit();
			npchar.dialog.currentnode = "Tonzag_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tonzag_4_1":
			dialog.text = "Gran festa, Capitano!";
			link.l1 = "Bevi e divertiti!";
			link.l1.go = "Tonzag_4";
		break;
		
		// Бейкер
		case "Baker":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Ecco il nostro capitano! Congratulazioni, tu e tua moglie siete una coppia splendida! Che possiate vivere felici per sempre!";
			link.l1 = "Grazie, Raymond.";
			link.l1.go = "Baker_1";
		break;
		
		case "Baker_1":
			sTemp = "Sharptown";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) sTemp = "Sent Pierre";
			dialog.text = "Sembra che tu sia troppo sobrio per il tuo stesso matrimonio, capitano. Vuoi rimediare? Ho preso una bottiglia di sherry eccellente al banco. Mischiato col rum locale va che è una meraviglia!";
			link.l1 = "Mi piacerebbe, ma qualcuno deve tenere d’occhio la situazione qui. Altrimenti, in "+sTemp+"  non sarà solo la taverna a mancarci quando arriverà il mattino.";
			link.l1.go = "Baker_2";
		break;
		
		case "Baker_2":
			DialogExit();
			npchar.dialog.currentnode = "Baker_2_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Tichingitu") != -1)
				{
					sld = characterFromId("Tichingitu");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "LongHappy_57";
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Baker_2_1":
			dialog.text = "Ottimo cibo e ottimo rum, capitano! Un brindisi a te e alla tua giovane sposa!";
			link.l1 = "Grazie, giusto?";
			link.l1.go = "Baker_2";
		break;
		
		// Алексус
		case "Alexus":
			dialog.text = "Giovani, perché entrate qui senza permesso, posso sapere? Il cantiere è chiuso, non si vede? Tornate domani.";
			link.l1 = "Maestro, scusami se ti disturbo, passeremo solo per le segrete. Ci sono le provviste per le nozze, la taverna sta quasi finendo le bevande.";
			link.l1.go = "Alexus_1";
		break;
		
		case "Alexus_1":
			dialog.text = "Oh, Charles de Maure e Nathan Hawk in persona! State qui per festeggiare il matrimonio di qualcuno, giusto? Va bene – andate a procurarvi il vostro carburante. I giovani devono divertirsi, è la legge in ogni epoca. Ma non fate tintinnare le bottiglie sulla via del ritorno – io vado a dormire!";
			link.l1 = "Grazie, signore, saremo silenziosi come il fiume più placido.";
			link.l1.go = "Alexus_2";
		break;
		
		case "Alexus_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			pchar.GenQuestBox.Bermudes_Dungeon = true;
			pchar.GenQuestBox.Bermudes_Dungeon.box3.items.potionwine = 100;
			pchar.quest.longhappy_isla_box.win_condition.l1 = "locator";
			pchar.quest.longhappy_isla_box.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator_group = "box";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator = "box3";
			pchar.quest.longhappy_isla_box.function = "LongHappy_IslaTesoroDungeon";
		break;
		
		case "Alexus_2_1":
			dialog.text = "Dai, non restare lì impalato, vai! Allora, capitano, sei contento di tutto, giusto?";
			link.l1 = "...";
			link.l1.go = "Alexus_2_2";
		break;
		
		case "Alexus_2_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
		break;
		
		// пиратус в подземелье
		case "DungeonPirate":
			dialog.text = "Ma che diavolo?! Jacques aveva detto 'Nessuno viene qui sotto'! Hugo, torna indietro, chiama gli altri, facciamo pulizia. Ammazzateli, forza!";
			link.l1 = "Merda!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BandosInDungeonFight");
		break;
		
		// киллеры
		case "killer":
			dialog.text = "Ragazzi, lasciate stare i forzieri, abbiamo ospiti!";
			link.l1 = "Pensavo che canaglie come te fossero sparite insieme a Jackman. Va bene, finiamola qui!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_ResidenceFight");
		break;
		
		case "killer_1":
			dialog.text = "Maledizione... Ci hanno scovati! Allarme!";
			link.l1 = "Levati di torno, bastardo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernKillerFight");
		break;
		
		// Ангерран
		case "Shivo":
			dialog.text = "Monsieur de Maure, buonasera, o forse è già quasi mattina? Entra, accomodati.";
			link.l1 = "Angerran De Chievous! Ma guarda chi si vede, non mi sorprende affatto! Un miserabile, buono solo a battersi con le donne! Le hai pure legate?! Ora finirò quello che ho iniziato in quel duello a Martinica!";
			link.l1.go = "Shivo_1";
		break;
		
		case "Shivo_1":
			dialog.text = "Calmati, giovanotto, vedi questa pistola? Sono due canne. Forse non sono un asso con la spada, ma a sparare ci so fare — posa quella lama, o ti perderai la compagnia di due belle signorine, te lo garantisco.";
			link.l1 = "Bastardo... Maledetto tu.";
			link.l1.go = "Shivo_2";
		break;
		
		case "Shivo_2":
			dialog.text = "E tu, monsieur pirata, posa anche tu la tua arma, proprio così, sì. E ora – siediti, puoi versare il vino – là, sul tavolo. Dovremo aspettare un po', finché monsieur Barbazon non avrà finito di fare a pezzi le navi dei tuoi amici, i baroni pirati. Poi decideremo come tu ed io risolveremo i nostri... ehm, dissapori.";
			link.l1 = "Sistemare i disaccordi? E come, scusa? Vuoi un duello, giusto?";
			link.l1.go = "Shivo_3";
		break;
		
		case "Shivo_3":
			dialog.text = "Non fare lo spiritoso, Charles. Tu e madame Botot mi avete dato un sacco di grattacapi, e ho intenzione di farvela pagare fino all’ultimo. Anche se lei mi ha messo nei guai molto più di te... comunque, se tu e il tuo imponente monsieur pirata vi siederete buoni, ti do la mia parola d’onore: le vostre mogli resteranno vive. Credo che nelle colonie spagnole del Maine schiave così valgano qualcosa. Anche se in modo non ufficiale. Ma sempre vita è, no?";
			link.l1 = "Angerran, sei un codardo, un bastardo e... Maledizione, non esistono ancora parole giuste per te in nessuna lingua!";
			link.l1.go = "Shivo_4";
		break;
		
		case "Shivo_4":
			dialog.text = "Lo sai bene, non hai alternativa. Posso solo prometterti che sarà rapido. Dunque, se tieni a queste donne, comportati come si deve, salvale e facilita il tuo destino. Ah, e chiudi la porta, se non ti pesa. Grazie.";
			link.l1 = "";
			link.l1.go = "Shivo_5";
		break;
		
		case "Shivo_5":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Shivo_6":
			dialog.text = "Che donne battagliere. Ma vi chiedo comunque di essere prudenti. Non ho mai amato uccidere le donne.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Shivo_7":
			dialog.text = "Merda...";
			link.l1 = "Crepa, bastardo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// Дюссак
		case "Dussak":
			dialog.text = "Capitano Charles de Maure, barone Hawk – che lieta sorpresa! Permettete che mi presenti – Mauritz Dussak, questo è il mio nome.";
			link.l1 = "Togliti dai piedi, bastardo! Dov'è mia moglie?!";
			link.l1.go = "Dussak_1";
		break;
		
		case "Dussak_1":
			dialog.text = "Calmatevi, signori! Vedete questa pistola? Ci sono due bauli. Non mi hanno soprannominata così per caso – adoro le sciabole, certo... ma so anche sparare, credetemi. Posate le spade, o rischiate di perdere qualche vostra signora, giusto?";
			link.l1 = "Ti sventrerò come un maiale, lurido bastardo...";
			link.l1.go = "Dussak_2";
		break;
		
		case "Dussak_2":
			dialog.text = "Ma allora sarai già vedovo. Non lo vuoi? Allora calmati e posa la tua arma. Barone Hawk, per favore, chiudi la porta. E noi ci rilasseremo e aspetteremo un po', mentre Jacques Barbazon laggiù nel porto finirà i capi della Confraternita.";
			link.l1 = "E poi che succede? Ci abbracciamo e andiamo insieme verso il tramonto, giusto?";
			link.l1.go = "Dussak_3";
		break;
		
		case "Dussak_3":
			dialog.text = "Non credo proprio. Per averti catturato, Jacques mi coprirà d’oro, e con un po’ di fortuna magari diventerò barone. Le tue donne? Forse le lasceremo andare, ma tu... ahimè... Se mi dice bene, chiederò il diritto di toglierti la vita io stesso, capitano. Sei una lama famosa, sarebbe interessante metterti alla prova. Sai, anche io mi reputo un maestro.";
			link.l1 = "Un vero maestro a intrufolarsi nelle case di notte per legare donne mezze addormentate? Sei un verme, e pure uno schifoso, giusto?";
			link.l1.go = "Dussak_4";
		break;
		
		case "Dussak_4":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Dussak_5":
			dialog.text = "Ascolta, signora, non ho mai ucciso donne, non farmi cambiare abitudine, giusto? Stai facendo innervosire il capitano e tuo marito... Maledizione!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Dussak_6":
			dialog.text = "Merda...";
			link.l1 = "Crepa, bastardo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// Барбазон
		case "Barbazon_boarding":
			dialog.text = "Maledetto francese, possibile che non ci fosse una sciabola o una pallottola per lui?!";
			link.l1 = "Sai, Jacques, ho entrambe le cose per te. Onestamente, quasi mi pento di averti lasciato in vita quando ho scoperto i tuoi giochetti con Jackman. Ma ora rimedio, giusto?";
			link.l1.go = "Barbazon_boarding_1";
		break;
		
		case "Barbazon_boarding_1":
			dialog.text = "Sei coraggioso solo quando ti circondi dei tuoi scagnozzi? Cambiamo le carte in tavola! Dei baroni mi occuperò dopo, ma tu, topo, non te ne andrai vivo di qui!";
			link.l1 = "Mi aspettavo...";
			link.l1.go = "Barbazon_boarding_2";
		break;
		
		case "Barbazon_boarding_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			AddItems(npchar, "potion2", 1);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "LongHappy_BarbAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			// подкрепление
			sld = GetCharacter(NPC_GenerateCharacter("LH_BarbCabinHelper", "citiz_57", "man", "man", 35, PIRATE, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 70, 70, "blade_21", "pistol4", "bullet", 300);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			AddItems(sld, "potion2", 2);
		break;
		
		// официантка
		case "waitress":
			dialog.text = "Capitano, aiuto, questo selvaggio mi ha rapita! Io... io devo tornare a casa – mio zio avrà già messo a soqquadro tutta la città, giusto?";
			link.l1 = "Calmati, bellezza, andrà tutto bene. Fatti da parte, devo parlare con il tuo 'selvaggio'.";
			link.l1.go = "waitress_1a";
		break;
		
		case "waitress_1a":
			DialogExit();
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "waitress_1":
			dialog.text = "Grazie, capitano! Mi hai salvata! Quando stamattina mi sono svegliata su questa spiaggia, non potevo credere che stavo per sposare quel selvaggio, lui...";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 94)
			{
				link.l1 = "Sì, il mattino è un martello severo che frantuma il cristallo di speranza della notte. Capisco. Ma lui appartiene alla tribù dei Muscogue, e vive secondo le dure leggi della sua terra. Ti ha rapita col tuo consenso, e avete passato la notte insieme. Ora, agli occhi dei suoi Dei, siete marito e moglie. Andiamo a preparare le tue cose, e lascerò a me il compito di risolvere la faccenda del riscatto con tuo zio.";
				link.l1.go = "waitress_2";
			}
			link.l2 = "Mi dispiace per questo. Tichingitu vive secondo le leggi della sua tribù, ma è una brava persona. Ti prego, dimentica questa faccenda del rapimento.";
			link.l2.go = "waitress_5";
		break;
		
		case "waitress_2":
			dialog.text = "Moglie? Davanti ai suoi Dei?! No, capitano, ti prego, risparmiami questo! Era solo... un'avventura, lui era così galante e simpatico, mica come questi zoticoni... Ma sposarmi? Sono troppo giovane per finire in una capanna con un selvaggio!";
			link.l1 = "Lui è il mio ufficiale e il mio migliore amico, quindi non preoccuparti, lo pago bene e avrai la capanna migliore che tu abbia mai desiderato. Tichingitu è un ottimo cacciatore, ti procurerà da mangiare, e tu darai alla luce e ti occuperai dei bambini.";
			link.l1.go = "waitress_3";
		break;
		
		case "waitress_3":
			dialog.text = "Bambini? Procurare da mangiare?! No capitano, ti prego, non farmi questo, ti supplico!";
			link.l1 = "Beh, forse riesco a convincerlo. Ma non sarà facile. La tribù dei Muskogue prende molto sul serio queste faccende: se scoprono che ha rapito una squaw senza sposarla...";
			link.l1.go = "waitress_4";
		break;
		
		case "waitress_4":
			dialog.text = "Devi provarci, ti prego! Non lo dirò a nessuno, nessuno lo saprà! Mentirò a mio zio, non sarebbe la prima volta, giusto?";
			link.l1 = "Va bene, dovresti andare, bella squaw. Cercherò di tenere il mio amico lontano.";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_5":
			dialog.text = "Mi ha rapita come... come una capra dal fienile! Lo racconterò a tutti! Mio zio lo farà a pezzi! Quando si arrabbia è una furia! Prima saccheggiava le navi spagnole — con lui non si scherza, giusto?";
			link.l1 = "Va bene, zitta, bella signora, zitta. Forse ventimila ‘ragioni’ per perdonarlo saranno più convincenti delle mie parole? O preferisci che le dia a tuo zio, come riscatto per una moglie? Tanto sono tutti sull’isola, giusto? Domani possiamo organizzare un altro matrimonio...";
			link.l1.go = "waitress_6";
		break;
		
		case "waitress_6":
			if (sti(Pchar.money) >= 20000) AddMoneyToCharacter(pchar, -20000); 
			dialog.text = "No no, capitano, aspetta! Mi hai convinta. Inventerò qualcosa così mio zio non si arrabbia. Addio! E arrivederci a te, mio stallone delle lontane praterie! Cercami la prossima volta che passi di qui...";
			link.l1 = "Giusto. Sono contenta che siamo d'accordo. Corri a casa, bella.";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// тавернщик Сен Пьер
		case "tavernkeeper":
			dialog.text = "Ebbene, Capitano, tutto ti soddisfa? Il miglior rum, costolette d’agnello, prosciutti di maiale e persino dell’ottimo vino delle mie riserve personali per il tuo amico scienziato! E - le mie congratulazioni a te e alla tua splendida sposa!";
			link.l1 = "Grazie! Devo ammettere che hai organizzato tutto alla perfezione. Spero che tu abbia abbastanza scorte di rum in cantina, la mattina è ancora lontana, giusto?";
			link.l1.go = "tavernkeeper_1";
		break;
		
		case "tavernkeeper_1":
			dialog.text = "Non preoccuparti di questo, se i barili saranno vuoti manderò subito un aiutante al magazzino del porto. Divertiti pure, monsieur, e non pensare a nulla.";
			link.l1 = "Va bene, "+npchar.name+"Allora andrò dai miei ospiti.";
			link.l1.go = "tavernkeeper_2";
		break;
		
		case "tavernkeeper_2":
			DialogExit();
			npchar.dialog.currentnode = "tavernkeeper_3";
		break;
		
		case "tavernkeeper_3":
			dialog.text = "Cosa desideri, capitano? Costine fritte, prosciutto affumicato o punta di petto? Magari un po' di vino per la tua dolce metà?";
			link.l1 = "";
			link.l1.go = "tavernkeeper_2";
		break;
		
		// моряки в таверне Сен Пьер
		case "sailor":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Alla salute del capitano e di sua moglie!","Che tu possa vivere per sempre felice e contento, capitano!","Lunga vita e felicità a entrambi voi!"),LinkRandPhrase("Evviva al capitano e alla sua bellezza!","Che la buona sorte accompagni il capitano e la sua sposa per tutta la vita!","Che il vento sia favorevole alla tua vita familiare, capitano!"));
			link.l1 = LinkRandPhrase("Grazie, giusto?","Grazie!","Salute!");
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor";
		break;
		
		// босс Ле Франсуа
		case "JanDavid":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Sei impazzito? Volevi fare il macellaio? Tutti i pirati ce l'hanno con te, amico, quindi ti conviene levare le ancore da qui.","Pare proprio che tu abbia perso la testa, amico. Avevi voglia di allungare un po’ le mani? Niente di personale, ma qui non hai nulla da fare. Sparisci!");
				link.l1 = RandPhraseSimple("Ascolta, voglio sistemare la faccenda...","Aiutami a risolvere questo pasticcio...");
				link.l1.go = "pirate_town";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LongHappy.Baron"))
			{
				if (!CheckAttribute(npchar, "quest.Baron"))
				{
					dialog.text = "Ah, ti aspettavo proprio, capo. Jan Svenson mi aveva avvertita che saresti venuto a vedere come stanno andando le cose a Le Francois. Ho preso tutto in mano io, e per mille fulmini ti giuro che questo villaggio vivrà meglio che ai tempi di quel dannato Kindman — che i diavoli si divertano con lui nei più bui sotterranei dell'inferno!";
					link.l1 = "Tu sei Jean David, vero? Svenson ha detto qualcosa riguardo la mia parte...";
					link.l1.go = "JanDavid_2";
				}
				else
				{
					dialog.text = TimeGreeting()+" capo. Tutto tranquillo a Le Francois, come al solito. Che ti porta qui? Posso darti una mano con qualcosa?";
					link.l1 = "Sono solo passata a vedere come vanno le cose, giusto?";
					link.l1.go = "JanDavid_1";
					if (sti(pchar.questTemp.LongHappy.BaronMoney) > 0)
					{
						link.l2 = "E il mio bottino?";
						link.l2.go = "JanDavid_5";
					}
				}
			}
			else
			{
				dialog.text = TimeGreeting()+" amico. Che ci fai qui? Posso aiutarti in qualcosa?";
				link.l1 = "Sono passata solo per salutarti, giusto?";
				link.l1.go = "JanDavid_1";
			}
		break;
		
		case "JanDavid_1":
			DialogExit();
			npchar.dialog.currentnode = "JanDavid";
		break;
		
		case "JanDavid_2":
			npchar.quest.Baron = "true";
			dialog.text = "Agli ordini, capo! Quanto alla quota – il cinque di ogni mese una parte delle monete d’oro guadagnate dai nostri ragazzi ti verrà trattenuta, e ti aspetterà finché vorrai. A partire dal prossimo mese potrai venire a riscuoterla.";
			link.l1 = "Bello, giusto?";
			link.l1.go = "JanDavid_3";
		break;
		
		case "JanDavid_3":
			dialog.text = "E al resto ci penso io. Il Diavolo della Foresta diceva che non avresti avuto tempo per preoccuparti di piccolezze come Le Francois...";
			link.l1 = "Ti hanno detto bene. Va bene, Jean, mi affido a te, spero che non mi deluderai.";
			link.l1.go = "JanDavid_4";
		break;
		
		case "JanDavid_4":
			dialog.text = "Andrà tutto bene, capo. Qui è tutto sotto controllo, ahah, e che io possa restare a secco di rum fino alla fine dei miei giorni se combino qualche casino!";
			link.l1 = "Va bene, ci vediamo, giusto?";
			link.l1.go = "JanDavid_1";
			// запуск отчисления доли
			pchar.questTemp.LongHappy.BaronPart = "true";
			pchar.questTemp.LongHappy.BaronMoney = 0;
		break;
		
		case "JanDavid_5":
			dialog.text = "Ti stavamo aspettando, capo. Nel frattempo abbiamo raccolto per te "+FindRussianMoneyString(sti(pchar.questTemp.LongHappy.BaronMoney))+" Prendilo.";
			link.l1 = "Ah, niente male. Ben fatto, Jean.";
			link.l1.go = "JanDavid_6";
		break;
		
		case "JanDavid_6":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.LongHappy.BaronMoney));
			pchar.questTemp.LongHappy.BaronMoney = 0;
			dialog.text = "Faccio del mio meglio, capo. Torna il prossimo mese o quando vuoi tu – i tuoi soldi saranno al sicuro con me.";
			link.l1 = "Va bene, ci vediamo, Jean.";
			link.l1.go = "JanDavid_1";
		break;
		
		case "pirate_town":
             dialog.text = "Risolvere il problema? Hai la minima idea di cosa hai combinato? Comunque, portami un milione di pesos e convincerò i ragazzi a dimenticare la tua bravata. Se non ti va, puoi pure andare all’inferno.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "D’accordo, sono pronta a pagare.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Ricevuto. Me ne vado.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Bene! Considerati di nuovo pulito. Ma spero che non ti venga più in mente di fare cose tanto ripugnanti.";
			link.l1 = "Non lo farò. È troppo costoso per me. Addio...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
} 

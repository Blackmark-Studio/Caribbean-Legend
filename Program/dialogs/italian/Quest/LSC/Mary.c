// Мэри Каспер - взаимная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	int iTime, iAddTime;
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
		case "First time":
			dialog.text = "Di cosa hai bisogno, giusto?";
			link.l1 = "No, non è nulla, giusto?";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
	// ---------------------------------покушение на Акулу - вариант R --------------------------------
		// разговор в каюте Адольфа
		case "Cabin":
			dialog.text = "Marcello, lo conosco. È un amico di Rivados e dei pirati. Adolf non lavorerebbe mai con lui. Senti l’aria... percepisci l’odore della polvere da sparo? E c’è sangue sul muro... Ha ucciso Adolf e ora cerca di prenderci in giro! Deve essere al soldo dell’ammiraglio! Uccidilo, giusto?";
			link.l1 = "...";
			link.l1.go = "Cabin_fight";
		break;
		
		case "Cabin_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			DialogExit();
			sld = characterFromId("Marchello");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack"))
			{
				for (i=1; i<=3; i++)
				{
					sld = characterFromId("CyclopGuard_"+i);
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_CyclopNMaryDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// на улице
		case "Town":
			dialog.text = "Oh, scusami... Posso chiederti una mano, giusto?";
			link.l1 = "Hm. Sono sempre pronto ad aiutare una splendida signora. Qual è il problema, giusto?";
			link.l1.go = "Town_1";
		break;
		
		case "Town_1":
			dialog.text = "Vedi, ho comprato uno scrigno pieno di ogni sorta di pezzi di metallo da Sessile Gallard. Lei vive sull’‘Eva’. Jurgen mi ha promesso che mi forgerà una bella cosa, giusto… L’ho comprato, sì, però non riesco a portarglielo. Che sciocca che sono!\nMagari potresti aiutarmi a trasportare lo scrigno dall’‘Eva’ al blocco del Narvalo sulla ‘Esmeralda’? Ti prego, te ne sarei davvero grata!";
			link.l1 = "E tutto qui? Certo, signorina, ti do volentieri una mano. Non è mica un gran fastidio, giusto?";
			link.l1.go = "Town_2";
		break;
		
		case "Town_2":
			dialog.text = "Grazie! Ti mostro dov’è il forziere, giusto?";
			link.l1 = "Mia signora...";
			link.l1.go = "Town_3";
		break;
		
		case "Town_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload41", "LSC_EnterAevaWithMary", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "Town_4":
			dialog.text = "Eccoci qua... Ora dimmi, bastardo, dove sta la chiave, giusto?!";
			link.l1 = "Wow! Ah, pare proprio che qui non serva alcun aiuto... Mary, giusto?";
			link.l1.go = "Town_5";
		break;
		
		case "Town_5":
			dialog.text = "Furbo, eh? Parla meno, maledetto! Dov’è la chiave? Dammi subito, o te ne pentirai, giusto?";
			link.l1 = "Che modi! Una lingua così tagliente in una ragazza così bella. Quale chiave, giusto?";
			link.l1.go = "Town_6";
		break;
		
		case "Town_6":
			dialog.text = "La chiave che hai preso da Adolf Barbier. E non provare a negarlo — ti hanno visto uscire dalla sua cabina. Adolf è morto e la colpa è tua... Ora, dammi la chiave, giusto?";
			link.l1 = "Quindi eri proprio tu, dopotutto... Hai fatto un bel pasticcio, ragazza, un errore grosso, giusto?";
			link.l1.go = "Town_7";
		break;
		
		case "Town_7":
			PlaySound("Voice\English\LSC\Mary Casper-04.wav");
			dialog.text = "Cosa hai detto?... Maledizione, non sei un semplice brigante! Sta lavorando per l’ammiraglio! Prendetelo, ragazzi!";
			link.l1 = "...";
			link.l1.go = "Cabin_fight";
		break;
		
	// ---------------------------------покушение на Акулу - вариант N --------------------------------
		case "caroline":
			dialog.text = "Chad, è lui! Maledizione, s’è portato pure un compare! Ragazzi, ammazzateli tutti!";
			link.l1 = "...";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			// Акулу к бою
			sld = characterFromId("Dodson");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			sld.cirassId = Items_FindItemIdx("cirass1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			// устанавливаем 4 толстых нарвалов
			int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
			int iScl = 65;
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaryGuard_"+i, "citiz_5"+(i+4), "man", "man", iRank, PIRATE, -1, true, "soldier"));
				if(i == 4) 
				{
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, "topor_07", "pistol11", "bullet", iScl*2);
					sld.DontClearDead = true;
					sld.SaveItemsForDead = true;
				}
				else FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2);
				if (i < 3) ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload3");
				else ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// Мэри и Чада к бою
			sld = characterFromId("Capper");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_MarynChadDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
	// ---------------------------------покушение на Акулу - вариант M --------------------------------
		case "mary":
			dialog.text = "Sei arrivato proprio al momento giusto... Non ce l’avrei mai fatta da sola con quei tipi... Tsk! A dirla tutta, pensavo proprio che per me fosse finita, giusto?";
			link.l1 = "Hai combattuto come una vera valchiria! Non ho mai visto una donna così bella menare le mani con tanto vigore, giusto?";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "Ah-ah, sei proprio un gentiluomo, giusto? Mentre impugni ancora la spada, già mi riempi di complimenti. Grazie dell’aiuto, mi hai salvato la vita, giusto? Presentati, gentiluomo, non ti ho mai visto prima. Sei nuovo da queste parti?";
			link.l1 = "Mi chiamo "+GetFullName(pchar)+", ma le belle signore possono chiamarmi "+pchar.name+". . Sono nuova qui? Hm... Proprio così, giusto?";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "Si vede subito, altrimenti avrei già notato un bel ragazzo come te in giro. Io sono Mary, Mary Casper. Ma qui mi chiamano Mary la Rossa. Perché sono rossa, giusto?";
			link.l1 = "Sono lieto di conoscerti anch’io, giusto?";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "Oh, sono doppiamente felice... visto che senza di te sarei già morta! Quel bastardo di Chad non stava affatto scherzando. Un vero parassita! E io che stupida a lasciare le porte di sotto spalancate. È così che sei entrato, giusto?";
			link.l1 = "Sì. Nuotavo intorno all’isola cercando un posto dove poter uscire, giusto?";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "Capisco. Questa porta sbloccata mi è quasi costata la pelle, giusto? Jurgen in persona ha forgiato le serrature per me: senza la chiave giusta non le apri, e scassinarle è inutile. E poi, io non resto certo ferma mentre qualcuno cerca di entrare – quattro canne della mia pistola fanno quattro buchi nella porta o in una panza, ah-ah! Ma quel dannato Chad non mi lascia mai in pace. Ha già mandato dei tagliagole a 'convincermi' a stare dalla sua parte, è proprio deciso, giusto? Se non fossi stato tu, avrei già ceduto. Ora mi tocca restare qui sotto assedio, giusto?"+pchar.name+", giusto? Per fortuna l'avevo previsto, ho provviste a sufficienza e Jurgen è il mio vicino, non ci ho mai litigato.";
			link.l1 = "Mary, perché non vuoi dirmi di più sui tuoi guai? Vedo che hai bisogno del mio aiuto, ma non ho capito una parola di quello che hai detto, giusto?";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "Ahi, ho proprio bisogno d’aiuto, giusto? Ora sono sola. Ho litigato con Donald, poi Chad s’è rivelato un furfante. Oh, scusami, sto di nuovo straparlando. Va bene, ti racconto in che pasticcio mi sono cacciata...";
			link.l1 = "Tieni presente che sono appena arrivata qui, quindi non ci capisco ancora molto, giusto? Chi sarebbe questo Chad che cerca di 'convincerti'... o ucciderti? E chi è Donald, giusto?";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "Chad è un bucaniere della ciurma dell’ammiraglio Shark Dodson, fa il secondino sul ‘Tartaro’...";
			link.l1 = "Aspetta! Cosa hai detto? Squalo Dodson? È qui, giusto?";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "Devi essere arrivato stanotte, se ancora non lo sai. Dove altro potrebbe stare Squalo, se non qui? I miei guai sono cominciati quando è arrivato qui alcuni mesi fa. Anche se, devo ammettere, è tutta colpa dei Narvali e dei Rivados. Quando Squalo è sbarcato con la sua ciurma, voleva mettere su una base, ma la nostra gente e i Rivados proprio non l’hanno digerita. Hanno assaltato la brigantina di Squalo di notte e l’hanno data alle fiamme… Non dovevano farlo! La ciurma di Squalo è piena di diavoli, non di uomini, giusto? Prima hanno affondato le barche dei nemici, poi sono sbarcati e hanno iniziato una vera carneficina. I Narvali si sono ritirati e i Rivados sono scappati più veloci che potevano. Alla fine, i pirati hanno preso San Augustine, dove stavano la maggior parte delle provviste dell’Isola, poi si sono presi anche il Tartaro… Squalo ha imprigionato il nostro capo Alan Milrow, che era anche il mio… mio caro amico, e il mago Rivados Chimiset. Li ha mandati a marcire come bestie nelle gabbie del Tartaro. Da qui arrivare al Tartaro è uno scherzo a nuoto, e sono riuscita a trovare Alan qualche volta. Lì ho incontrato Chad Kapper, Squalo lo ha messo a fare il carceriere. Ho chiesto a Chad di liberare Alan, gli ho promesso denaro, ma aveva troppa paura di mettersi contro l’ammiraglio… E poi Alan è stato assassinato in prigione. Chad mi ha detto che è stato Squalo, giusto? Così sono andata da Donald, che avevano eletto capo al posto di Alan, e gli ho ordinato di attaccare subito i pirati, ma ha rifiutato, dicendo che quei demoni del mare sono troppo per noi. A quel punto gli ho detto di andare al diavolo… La mia gente non valeva nulla in questa faccenda, così ho fatto un patto con Kapper, quella carogna voleva prendere il posto di Squalo. Avevamo un piano: attirare l’ammiraglio fuori dalla sua fortezza in qualche bettola e farlo fuori lì. Avevamo trovato anche un tiratore con un buon fucile. Avrebbe potuto sparare all’ammiraglio dall’albero maestro della Fury… Ora viene il bello: l’altro ieri notte sono passata al Tartaro, volevo dire a Chad una cosa importante sul nostro piano. Sono arrivata alla barca e per caso ho sentito Chad parlare con due Narvali. È venuto fuori che Squalo non aveva ucciso Alan. È stato Chad. Poi ha fatto circolare voci di nascosto per dare la colpa all’ammiraglio… L’ha ammazzato per colpa mia. Prima, mi voleva nel suo letto come un giocattolo. Poi, voleva servirmi per sbarazzarsi di Squalo – sapeva che io avrei sempre cercato vendetta. Riesci a crederci? Che vigliacco, giusto?";
			link.l1 = "Sì, di tipi come lui ne ho già incontrati, giusto?";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "Quel bastardo è anche peggio! Lui... davvero non ho parole per descrivere quel mostro! Me ne sono andata quella volta, ma la mattina dopo l'ho trovato e gli ho detto tutto quello che pensavo di lui. Giusto? Gli ho detto chiaro e tondo che non voglio saperne nulla del suo complotto contro l’ammiraglio.";
			link.l1 = "E a lui non è piaciuto, ovviamente... Era solo rabbia, Mary. Dovresti stare più attenta, giusto?";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			dialog.text = "Non ce l'ho fatta, giusto? Non potevo proprio stare zitta. Quel bastardo ha ammazzato Alan e voleva servirmi su un piatto per i suoi sporchi affari! Feccia! Già, si è incazzato e mi ha giurato che me l'avrebbe fatta pagare. Gli ho detto che gli avrei tagliato le palle e le avrei date in pasto ai granchi, giusto?\nMi ha minacciato di mandarmi addosso i suoi compari del Narvalo se non cambiavo idea. Io ho riso, giusto? Non credo proprio che un Narvalo osi mai alzare le mani su di me.";
			link.l1 = "Sembra che tu ti sia sbagliato, giusto?";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "Giusto? "+pchar.name+"Ho sottovalutato Chad e sopravvalutato me stessa. Ha trovato quei bastardi che avrebbero osato attaccare una ragazza sola nella sua cabina. E ora che dovrei fare? Non posso fidarmi di nessuno. Nemmeno della mia stessa ciurma, giusto. Quei due sono Narvali, li conoscevo entrambi, giusto? Finché Chad respira – sono in pericolo, ne manderà altri, sicuro come il sole che sorge.\nHo paura persino ad uscire, il cecchino che avevamo pagato per far fuori Shark potrebbe spararmi dal territorio di Rivados e svignarsela senza problemi. Da Donald non ci vado, quello non mi ascolta, giusto?\nL’Ammiraglio? Non posso mica spiegargli il mio ruolo nei preparativi per l’assassinio! Mi butterebbe a marcire nelle celle del 'Tartaro', ne sono certa! Maledizione, sono in trappola. Resterò qui con le pistole cariche finché non finiscono le provviste e poi… non ho la più pallida idea di cosa ne sarà di me, giusto?";
			link.l1 = "Beh, in questo caso non ho altra scelta che darti una mano, giusto? Tanto la tua situazione si incastra perfettamente con i miei piani qui...";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			dialog.text = "Hai intenzione di aiutarmi? Ma come? Vuoi davvero far fuori Chad, giusto?";
			link.l1 = "Quella parte del piano, giusto?";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "Ascolta, "+pchar.name+", , Apprezzo le tue intenzioni, ma Chad non fa per te. È uno dei più fidati dell'ammiraglio e anche se riesci ad avvicinarlo – i pirati dello Squalo ti faranno fuori, non conoscono la verità, giusto?";
			link.l1 = "Calmati. Dovrò comunque parlare con Squalo, giusto?";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "Allora, sei un pirata anche tu?! Raccontami di te, guarda un po’: sei entrato di forza a casa mia, mi hai salvato la pelle, hai promesso di aiutarmi con quell’aria da bel ragazzo, eppure non so nulla di te, giusto?";
			link.l1 = "Va bene... Non sono una piratessa, ma al momento lavoro col barone pirata Jan Svenson. Sono venuta qui per trovare Nathaniel Hawk. Ne hai mai sentito parlare, giusto?";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			dialog.text = "No, chi sarebbe, giusto?";
			link.l1 = "Anche lui è un pirata famoso. Peccato che non l’hai ancora incontrato, deve essere da queste parti. Anch’io stavo cercando Squalo, ma non pensavo proprio di trovarlo qui, giusto?";
			link.l1.go = "mary_15";
		break;
		
		case "mary_15":
			dialog.text = "Ma come sei arrivato fin qui? Sembri troppo in forma per essere uno scampato a un naufragio, giusto?";
			link.l1 = "E perché mai dovresti pensare che io sia naufragata, giusto?";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "È l’unico modo per arrivare fin qui. Solo Squalo è riuscito in qualche modo a farsi strada fino a qui, giusto?";
			link.l1 = "Beh, come puoi vedere, Shark non era l’unico, giusto?";
			link.l1.go = "mary_17";
		break;
		
		case "mary_17":
			dialog.text = "Allora, hai una nave? Fantastico, giusto?";
			link.l1 = "Non scaldarti troppo presto, Mary. Sono arrivato fin qui su... una barca, ma è finita a fondo, giusto?";
			link.l1.go = "mary_18";
		break;
		
		case "mary_18":
			dialog.text = "A-ah... Beh, come ti dicevo – un naufragio. Ora sei bloccato qui con noi, giusto?";
			link.l1 = "Mary, lascia che ti spieghi il mio piano. Hai detto che Chad voleva far fuori Shark. A me Shark serve vivo, io e Jan vogliamo metterlo a capo dei pirati. Ecco perché devo avvertirlo, giusto? Perché dalla tua storia sono sicuro che Chad ci proverà comunque, con o senza il tuo aiuto.";
			link.l1.go = "mary_19";
		break;
		
		case "mary_19":
			dialog.text = "Eh, probabile. Ha gli uomini giusti per riuscirci, giusto?";
			link.l1 = "Vuol dire che il mio scopo principale è conquistare la fiducia di Shark e salvarlo. Poi penserò a Chad, ufficialmente. Hai qualche prova delle sue intenzioni, giusto?";
			link.l1.go = "mary_20";
		break;
		
		case "mary_20":
			dialog.text = "Ho ricevuto la sua lettera, portata qui da uno di questi... sciocchi stesi per terra. Ci sono minacce e dettagli che l’ammiraglio troverebbe interessanti. Aspetta! E io che fine faccio? Lo Squalo scoprirà che collaboravo con Chad, giusto?";
			link.l1 = "Mary, hai intenzione di restare qui per l’eternità armata di pistole e nascondere quel tuo dolce viso a tutti? Davvero mi prendi per uno dei babbei che bramano la morte di una dama così bella? Fammi vedere prima la lettera, giusto? Vediamo cosa posso fare…";
			link.l1.go = "mary_21";
		break;
		
		case "mary_21":
			GiveItem2Character(pchar, "letter_chad_1");
			RemoveItems(npchar, "letter_chad_1", 1);
			dialog.text = "Ecco. Che ne pensi, giusto?";
			link.l1 = "Aspetta un attimo... (leggendo). Sì, sembra proprio che Chad sia una razza particolare di bastardi a infestare questa terra. Questa lettera basterà per far venire a Shark la voglia di stringere la corda attorno al collo di Chad con le sue stesse mani. Non preoccuparti, mia signora, mi assicurerò che Shark non sospetti nulla di te. Sarà troppo occupato con Chad, giusto?";
			link.l1.go = "mary_22";
		break;
		
		case "mary_22":
			dialog.text = "Lo farai? Promettimi, giusto? Giura che non mi tradirai!";
			link.l1 = "Mary, ti giuro che non ti tradirò. Non preoccuparti per questo, non ti ho salvata per vederti finire così. Chad non ti lascerà in pace, ormai sai troppo. Resta qui finché non sarà morto, giusto?";
			link.l1.go = "mary_23";
		break;
		
		case "mary_23":
			dialog.text = "Sì, resto qui. Non ho nessuna voglia di prendermi una pallottola da un cecchino o beccarmi una coltellata alle spalle, giusto?";
			link.l1 = "Brava ragazza. Chiudi tutte le porte, anche quelle di sotto. Hai solo una chiave, giusto?";
			link.l1.go = "mary_24";
		break;
		
		case "mary_24":
			dialog.text = "No. Ce n'è un altro. Lo vuoi, giusto?";
			link.l1 = "Sì. Ti fidi di me, giusto?";
			link.l1.go = "mary_25";
		break;
		
		case "mary_25":
			dialog.text = "Beh, se il gentiluomo che mi ha appena salvato la vita mi tradisce, allora non ha più senso vivere... Prendi, giusto?";
			link.l1 = "Non temere, bellezza! Non ti deluderò. Verrò da te appena avrò sistemato questo pasticcio. Spero non ci metta troppo, giusto?";
			link.l1.go = "mary_26";
		break;
		
		case "mary_26":
			GiveItem2Character(pchar, "key_mary");
			dialog.text = "Va bene, posso tenere questo posto per qualche settimana, giusto?";
			link.l1 = "Perfetto. Non perdo tempo allora. Porterò fuori i cadaveri e parlerò con Squalo. È sulla 'San Augustine', giusto?";
			link.l1.go = "mary_27";
		break;
		
		case "mary_27":
			dialog.text = "Sì, lui è sempre là. E vattene allo stesso modo in cui sei arrivato – non ti lascerò mai mettere piede sul ponte superiore della 'Fucina di Ceres', giusto?";
			link.l1 = "Interessante, e come mai, giusto?";
			link.l1.go = "mary_28";
		break;
		
		case "mary_28":
			dialog.text = "Perché non potrai aiutarmi se ci lasci le penne. Qui è il territorio dei Narvali e ti faranno fuori come uno straniero, giusto?";
			link.l1 = "Hm... Capito. Beh, Mary, ci si vede. Tornerò appena sarà sicuro, giusto?";
			link.l1.go = "mary_29";
		break;
		
		case "mary_29":
			dialog.text = "Puoi venire a trovarmi quando vuoi, per me non è un problema. (ride)";
			link.l1 = "Addio, bellezza!";
			link.l1.go = "mary_30";
		break;
		
		case "mary_30":
			DialogExit();
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "mary_wait";
			npchar.greeting = "mary_3";
			AddQuestRecord("SharkHunt", "31");
			AddQuestRecordInfo("Chad_Mary_letter", "2");
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем выходы
		break;
		
		case "mary_wait":
			dialog.text = "Ciao, "+pchar.name+", qualche buona nuova per me? Tutto a posto, giusto?";
			if (pchar.questTemp.Saga.SharkHunt == "mary_whiskey")
			{
				link.l1 = "Il problema con l'ammiraglio è risolto. Non gli importa di darti la caccia, è solo il tradimento di Chad che gli dà fastidio, giusto?";
				link.l1.go = "letters";
			}
			else
			{
				link.l1 = "Non ancora, Mary. Ma farò tutto ciò che posso, giusto?";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "mary_wait";
		break;
		
		case "letters":
			dialog.text = "Oh, grazie al cielo! Grazie, non me lo scorderò, giusto? Almeno dall’ammiraglio non c’è più pericolo. E invece Chad? Che ha combinato Squalo?";
			link.l1 = "Abbiamo convinto i Rivados ad assalirlo. Layton Dexter ha tolto le guardie dal 'Tartaro' e ha dato la chiave a Eddie il Nero. I ragazzi di colore hanno liberato il loro stregone Chimiset, ma non sono riusciti a far fuori Chad. Hanno fatto fuori due dei suoi compari del Narvalo, ma lui è scappato e ora si nasconde da qualche parte, giusto?";
			link.l1.go = "letters_1";
		break;
		
		case "letters_1":
			dialog.text = "Maledizione! Questo vuol dire che devo stare ancora più attenta, giusto?";
			link.l1 = "Calmati, Mary. Sono certo che ha gente molto più minacciosa di cui preoccuparsi. Probabilmente sa già chi ha mandato i Rivados ad attaccarlo. Farà di tutto per far fuori lo Squalo, non te, giusto?";
			link.l1.go = "letters_2";
		break;
		
		case "letters_2":
			dialog.text = "Ci credi davvero? Chad non è certo uno che si lascia scivolare le cose addosso, giusto? Ah, sono troppo stanca per aver ancora paura...";
			link.l1 = "Uh. Non ti facevo il tipo da spaventarsi facilmente, giusto?";
			link.l1.go = "letters_3";
		break;
		
		case "letters_3":
			dialog.text = "Ah! Non è vero? Non ho paura di combattere faccia a faccia, ma restare seduta sul mio culo aspettando di crepare? Quello sì che mi fa una paura dannata, giusto?"+pchar.name+", giusto!...";
			link.l1 = "Fidati di me, Mary: Kapper ha già le mani piene con l’ammiraglio, al momento... Ho bisogno di un tuo consiglio, giusto?";
			link.l1.go = "letters_4";
		break;
		
		case "letters_4":
			dialog.text = "Un consiglio da me? Che tipo di consiglio, giusto?";
			link.l1 = "Eddie ha trovato due lettere scritte da Chad. Leggile, magari capisci cosa sta tramando. In fondo eri nel piano insieme a Chad, giusto?";
			link.l1.go = "letters_5";
		break;
		
		case "letters_5":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "Dalli a me... (leggendo). Axel è il nostro mercante sull’‘Esmeralda’, giusto? Chad voleva comprare del whiskey da lui per qualche ragione. Strano! Chad beve solo rum, dice che il whiskey è ‘la grappa dei pezzenti’...";
			link.l1 = "E della seconda lettera, che mi dici, giusto?";
			link.l1.go = "letters_6";
		break;
		
		case "letters_6":
			dialog.text = "Marcello? Marcello il Ciclope, un ex cacciatore reale. È lui il motivo principale per cui non voglio mettere piede fuori da questa cabina, giusto?";
			link.l1 = "È lui il tiratore scelto che hai assoldato, giusto?";
			link.l1.go = "letters_7";
		break;
		
		case "letters_7":
			dialog.text = "Sì. Marcello può colpire una mosca a dodici passi, anche se gli manca un occhio, giusto? Doveva abbattere Shark usando uno stutzen a lungo raggio dalla prua della Santa Florentina, o dalla piattaforma della Fury...";
			link.l1 = "Quindi pare che Chad abbia deciso di far fuori Shark. Ma allora a cosa serve Eva? Cecille? Da bere, giusto?";
			link.l1.go = "letters_8";
		break;
		
		case "letters_8":
			dialog.text = "Eva è una nave neutrale e Cecille è Cecille Halard, una vecchietta buffa che ci vive. Si è trasferita qui da poco, veniva da Santa Florentina. Orelie Bertine è un’amica sua. Un tempo abitavano insieme qui, ancora prima che io venissi al mondo, giusto?";
			link.l1 = "Hm. Sciocchezze. Due omaccioni che si nascondono da una vecchia per scolarsi un barile di whiskey insieme. Roba da pazzi... Non è proprio il momento migliore per bere, Chad, giusto?";
			link.l1.go = "letters_9";
		break;
		
		case "letters_9":
			dialog.text = "Te l’ho già detto che lui non tocca il whiskey. Solo rum, qui c’è qualcosa che non quadra, giusto?";
			link.l1 = "Va bene, come vuoi. Sai dove posso trovare il Ciclope, giusto?";
			link.l1.go = "letters_10";
		break;
		
		case "letters_10":
			dialog.text = "No. È molto riservato. Ogni giorno spara agli uccelli là fuori al confine, e nessuno sa dove vada a dormire. Prima veniva spesso da Rivados, giusto?";
			link.l1 = "Che sfortuna... Beh, allora vado a parlare con Axel. Magari lui capirà qualcosa in più di questa storia. Ci vediamo, Mary! Chiudi la porta!";
			link.l1.go = "letters_11";
		break;
		
		case "letters_11":
			dialog.text = ""+pchar.name+"Per favore, trova Chad. Sbrigati, non ho chiuso occhio dall’ultimo assalto, giusto?";
			link.l1 = "Aspetta, tesoro. Farò del mio meglio, giusto?";
			link.l1.go = "letters_12";
		break;
		
		case "letters_12":
			DialogExit();
			NextDiag.CurrentNode = "mary_wait";
			pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
			AddQuestRecord("SharkHunt", "35");
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! Come ha fatto ad arrivare qui? È venuto a...";
			link.l1 = "Sì, per ucciderti, Mary. È arrivato qui passando per la cabina di Jurgen e ha usato una corda per calarsi quaggiù, giusto?";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			dialog.text = "Ah! Che sciocca che sono stata a dimenticarmi di quella strada! Sono sicura che è stato Chad a insegnargliela, giusto?";
			link.l1 = "Molto probabile. Ce l’ho fatta per un soffio. Stava venendo proprio dietro di te, giusto?";
			link.l1.go = "happy_2";
		break;
		
		case "happy_2":
			dialog.text = "E io dormivo. Mi avrebbe fatta fuori in un lampo... Ma come hai fatto a capire che stava arrivando qui, giusto?";
			link.l1 = "L’ho fatto... proprio adesso, Mary.";
			link.l1.go = "happy_3";
		break;
		
		case "happy_3":
			dialog.text = "Mi hai salvata di nuovo, bel ragazzo. Arrivi sempre al momento giusto, giusto? Come fai a fare così?";
			link.l1 = "Eh, che vuoi che ti dica. È solo uno dei miei tanti talenti, giusto? L’assedio è finito – Chad Kapper è morto, e pure tutti i suoi compari. Ciclope era l’ultimo di quella ciurma marcia, giusto?";
			link.l1.go = "happy_4";
		break;
		
		case "happy_4":
			dialog.text = "Davvero? È la verità, giusto?"+pchar.name+"Non mi stai prendendo in giro, giusto?";
			link.l1 = "Ma figurati. Eh, ho proprio bisogno di riposarmi dopo tutto quello che è successo in questi giorni, giusto?";
			link.l1.go = "happy_5";
		break;
		
		case "happy_5":
			dialog.text = "Posso finalmente respirare liberamente ora! Grazie... Grazie di cuore! Sei il mio eroe, giusto?";
			link.l1 = "Mi piace come suona, essere il tuo eroe, intendo. Sono solo felice che tu sia finalmente al sicuro, giusto?";
			link.l1.go = "happy_6";
		break;
		
		case "happy_6":
			dialog.text = "Allora, giusto?";
			link.l1 = "Che c’è, bellezza?";
			link.l1.go = "happy_7";
		break;
		
		case "happy_7":
			dialog.text = "Perché stai lì impalato? Su, avanti, gentiluomo, giusto?";
			link.l1 = "E fare cosa, giusto?";
			link.l1.go = "happy_8";
		break;
		
		case "happy_8":
			dialog.text = "Sei proprio un gentiluomo... Vieni qui e stringimi, baciami finalmente, lo vuoi, lo vedo, giusto!";
			link.l1 = "Mary...";
			link.l1.go = "happy_9";
		break;
		
		case "happy_9":
			DialogExit();
			LAi_Fade("LSC_MaryRomantic_1", "");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, false, true);
			PlayStereoOGG("music_romantic");
			pchar.questTemp.LSC.MaryBye = "true"; // атрибут обязательного прощания перед телепортацией
			LocatorReloadEnterDisable("LostShipsCity_town", "reload62", false);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload63", false); // открываем Церес снаружи
		break;
		
		case "happy_10":
			dialog.text = "Non lasciarmi, giusto?";
			link.l1 = "Sono qui, Mary, tesoro...";
			link.l1.go = "happy_11";
		break;
		
		case "happy_11":
			dialog.text = "Tutto può aspettare. L’ammiraglio aspetterà, pure i tuoi pirati aspetteranno. Stanotte siamo solo noi due, giusto?!";
			link.l1 = "Ma certo... giusto?";
			link.l1.go = "happy_12";
		break;
		
		case "happy_12":
			dialog.text = "E tutte le notti dopo quella, giusto?";
			link.l1 = "Sì, Mary.";
			link.l1.go = "happy_13";
		break;
		
		case "happy_13":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Next morning...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("LSC_MaryRomantic_5", 4.0);
		break;
		
	// ----------------------------------вместе с Мэри на Церес Смити------------------------------------------
		case "LSC_love":
			if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
			{
				dialog.text = ""+pchar.name+"! Sei tornato... senza di lei. Quindi non è riuscita a portarti via da me, giusto?";
				link.l1 = "Mary, i tuoi sospetti erano infondati. Sei tu l’unica per me. Eri sempre nei miei pensieri e nei miei sogni, giusto?";
				link.l1.go = "adversary_hire_return";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+", , perché stai litigando coi Narvali? Vivo sulle loro terre, anzi, ormai sono una di loro, giusto? Ti prego, vai da Fazio e fai pace, ti scongiuro.";
				link.l1 = "Giusto, Mary, farò come chiedi.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.FindDolly")) // нашёл статую - прощается
			{
				dialog.text = ""+pchar.name+", qualcosa ti turba. Che succede, giusto?";
				link.l1 = "Mary, ho bisogno di parlarti, giusto?";
				link.l1.go = "dolly";
				break;
			}
			if (CheckAttribute(npchar, "quest.donald"))
			{
				dialog.text = ""+pchar.name+"! Tutti i Narvali parlano di te, giusto?";
				link.l1 = "Davvero, tesoro mio, giusto?";
				link.l1.go = "donald";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+"! Questa spada lunga è incredibile! Grazie ancora!.. Voglio darti anch’io un regalo. Certo, non è nulla in confronto al tuo, ma vorrei che tu lo prendessi, giusto.";
				link.l1 = "Mary, il valore di un dono non conta... Grazie, amore mio";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
			{
				dialog.text = "Hai una giornata piena davanti, giusto?"+pchar.name+"Giusto? Buona fortuna!";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, dobbiamo andare a trovare Jurgen oggi, giusto?";
					link.l3.go = "narval";
				}
				link.l1 = "Grazie, Mary! Non ne dubito affatto, giusto?";
				link.l1.go = "exit";
				link.l2 = "No, Mary. Voglio riposarmi un po’ qui. Ti va bene, giusto?";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "Ebbene, "+pchar.name+", come te la passi? Sempre di corsa su quest’Isola, giusto?";
				link.l1 = "Sì, Mary. Ci sono un sacco di cose da fare, giusto?";
				link.l1.go = "LSC_love_1";
			}
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_1":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = "È già sera, giusto?"+pchar.name+", di che cose vai blaterando? Resta qui, beviamo qualcosa e rilassiamoci, giusto! Può aspettare fino a domani mattina!";
				link.l1 = "(ridendo) Ma certo, amore, non serve aggiungere altro, giusto?";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "Mary, oggi andiamo in taverna, giusto?";
					link.l2.go = "LSC_tavern";
				}
				link.l3 = "Mary, tesoro, ora sono davvero impegnato. Tornerò tra un po', giusto?";
				link.l3.go = "LSC_love_2";
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) //день
			{
				dialog.text = "Non dimenticarti di venire a trovarmi stasera. E non ti azzardare a evitarmi, giusto!";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, oggi dobbiamo andare a trovare Jurgen, giusto?";
					link.l3.go = "narval";
				}
				link.l1 = "Certo, Mary, come potrei? Verrò sicuramente a trovarti, giusto?";
				link.l1.go = "exit";
				link.l2 = "No, Mary. Voglio riposare qui stanotte. Per te va bene, giusto?";
				link.l2.go = "rest_afternoon"; // отдых
				NextDiag.TempNode = "LSC_love";
				break;
			}
			dialog.text = "Di che stai parlando? È già notte! No, tu non vai da nessuna parte, resti qui con me, giusto?";
			link.l1 = "(ridendo) come vuoi tu, tesoro...";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_2":
			dialog.text = "Neanche pensarci, giusto?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
		break;
		
		// сходить в таверну
		case "LSC_tavern":
			dialog.text = LinkRandPhrase("Un’idea magnifica, giusto?"+pchar.name+", giusto! Sono d'accordo!","Aye, andiamo, giusto?"+pchar.name+"Sancho ha una bella collezione di vini, c’è davvero l’imbarazzo della scelta, giusto?","Oh, sarei proprio felice, giusto? Alla taverna di Sancho ci si diverte sempre e ha una scelta di vini che fa girare la testa!");
			link.l1 = "Andiamo, giusto?";
			link.l1.go = "LSC_love_tavern";
		break;
		
		// --> отдых
		case "rest_morning":
			dialog.text = "Certo, giusto?"+pchar.name+"Certo, riposati un po', giusto?";
			link.l1 = "Resterò fino a mezzogiorno, giusto?";
			link.l1.go = "rest_day";
			link.l2 = "Rimarrò fino a stasera, giusto?";
			link.l2.go = "rest_evening";
		break;
		
		case "rest_afternoon":
			dialog.text = "Certo, giusto?"+pchar.name+"Certo, riposati un po', giusto?";
			link.l1 = "Resto fino a stasera, giusto?";
			link.l1.go = "rest_evening";
		break;
		
		case "rest_day":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 13 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		
		case "rest_evening":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 18 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- отдых
		
	//--> если скоро уходит через портал
		case "LSC_love_3": 
			if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
			{
				dialog.text = ""+pchar.name+"! Sei tornato... senza di lei. Quindi non è riuscita a portarti via da me, giusto?";
				link.l1 = "Mary, i tuoi sospetti erano infondati. Per me esisti solo tu. Sei sempre stata nei miei pensieri e nei miei sogni, giusto?";
				link.l1.go = "adversary_hire_return";
				break;
			} // 291112
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+", perché stai combattendo coi Narvali? Io vivo sulle loro terre, anzi, sono una di loro, giusto? Per favore, vai da Fazio e fai pace, ti scongiuro.";
				link.l1 = "Giusto, Mary, farò come chiedi.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+"Questa spada lunga è incredibile! Grazie ancora!.. Voglio darti anch’io un regalo. Certo, non vale quanto il tuo, ma voglio che tu lo prenda, giusto.";
				link.l1 = "Mary, il valore di un regalo non conta... Grazie, amore mio";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
			{
				dialog.text = "Te ne vai già, giusto?"+pchar.name+"Giusto? Buona fortuna e non ti scordare di me...";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, oggi dovremmo andare a trovare Jurgen, giusto?";
					link.l3.go = "narval";
				}
				link.l1 = "Certo, Mary.";
				link.l1.go = "exit";
				link.l2 = "No, Mary. Voglio riposarmi un po' qui. Va bene per te, giusto?";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "Non vai al tuo affare con Kukulcan, giusto?"+pchar.name+"?";
				link.l1 = "Non ancora, mi sto ancora preparando, giusto?";
				link.l1.go = "LSC_love_4";
			}
			NextDiag.TempNode = "LSC_love_3";
		break;
		
		case "LSC_love_4":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = "È già sera, giusto?"+pchar.name+"Perché non resti qui? Voglio starti accanto, giusto?";
				link.l1 = "Va bene, tesoro, resto qui, giusto?";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "Mary, andiamo in taverna oggi, giusto?";
					link.l2.go = "LSC_tavern";
				}
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) //день
			{
				dialog.text = "Buona fortuna e non ti scordare di me... Vieni a trovarmi stasera se puoi, giusto!";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, oggi dovremmo vedere Jurgen, giusto?";
					link.l3.go = "narval";
				}
				link.l1 = "Benissimo, tesoro.";
				link.l1.go = "exit";
				link.l2 = "Mary, vorrei riposare un po’ qui. Sei d’accordo, giusto?";
				link.l2.go = "rest_afternoon"; // отдых
				NextDiag.TempNode = "LSC_love_3";
				break;
			}
			dialog.text = "Di che stai parlando? È notte fonda! No, non vai da nessuna parte, resti qui, giusto?";
			link.l1 = "(ridendo) Va bene, resto... giusto?";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love_3";
		break;
		// <-- скоро уходит через портал
		
	// --> взаимоотношения - секс и прочее
		case "LSC_love_tavern":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_MaryTavern");
		break;
		
		case "LSC_love_evening":
			DialogExit();
			//if(CheckAttribute(PChar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LSC_MaryEveneng();
		break;
		
		case "LSC_love_night":
			DialogExit();
			LSC_MaryLove();
		break;
		
		case "LSC_love_morning":
			if (CheckAttribute(npchar, "quest.hire"))
			{
				dialog.text = "Capitano "+pchar.name+"! L’ufficiale Mary Casper è pronta a servire sotto il tuo comando, giusto?";
				link.l1 = "Ben fatto, ufficiale! Ti ordino d’imbarcarti subito sulla nave. Ma prima: bacia il tuo capitano, giusto?";
				link.l1.go = "LSC_mary_hire";
			}
			else
			{
				dialog.text = "È stato incredibile, amore... Buongiorno, giusto?";
				link.l1 = "Buongiorno, tesoro! Sei una meraviglia, giusto?";
				link.l1.go = "LSC_love_morning_1";
			}
		break;
		
		case "LSC_love_morning_1":
			DialogExit();
			LAi_SetOwnerType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- взаимоотношения
		
		// стал другом нарвалам
		case "donald":
			dialog.text = "Hai parlato con Donald? È vero che l'ammiraglio voleva allearsi con Rivados e combattere contro i Narvali? È vero che tu l'hai convinto a non farlo? Ci sarà pace tra i pirati e i Narvali, giusto?";
			link.l1 = "Sì, Mary. Proprio così, giusto?";
			link.l1.go = "donald_1";
		break;
		
		case "donald_1":
			dialog.text = ""+pchar.name+", non trovo le parole... Dicono anche che Donald ti consideri un amico. Potresti diventare uno dei Narvali, giusto!";
			link.l1 = "Parla con Donald quando puoi – anche lui vuole fare pace con te. Ti chiede di perdonarlo per le sue parole e per non essere riuscito a proteggerti da quei due bastardi, giusto?";
			link.l1.go = "donald_2";
		break;
		
		case "donald_2":
			dialog.text = "Al diavolo Donald! Anche se, certo, mi fa piacere sentirlo. Lo vedrò. Ma tu! Io... no, non proprio così... Sono fiera di te, giusto?";
			link.l1 = "Santo cielo, Mary... tu sei... ah, mi fai battere il cuore a mille, giusto?";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
			DeleteAttribute(npchar, "quest.donald");
		break;
		
		// ноды прощания
		case "dolly":
			dialog.text = "Parliamo! Sei nei guai, giusto?";
			link.l1 = "No. Mary, ti ricordi la notte in cui ci siamo conosciuti? Dopo che abbiamo sistemato quei due bastardi, ti dissi che ero arrivato qui su una nave, giusto?";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "Ricordo, sì. La tua barca è affondata e hai dovuto nuotare fin qui… giusto?";
			link.l1 = "Ho mentito. Avresti pensato che fossi matta se ti avessi detto la verità, giusto? Nessuna barca, davvero. Ho usato una forza inspiegabile di un dio indiano, Kukulcan, per arrivare qui.";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = ""+pchar.name+"... Di che stai parlando? Kukulcan, giusto?";
			link.l1 = "Mary, cara, devi credermi, perché non c’è nulla di razionale in tutto questo, e non posso confidarlo a nessun altro se non a te. Nathaniel Hawk è sparito toccando l’idolo indiano, lo stavano inseguendo e quello gli ha salvato la pelle, giusto?";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "";
			link.l1 = "Cercavo Nathaniel. Ho parlato con uno sciamano indiano e dovevo fare come Hawk. Sono stata catapultata nella stiva della 'San Augustine', sono uscita da un buco nello scafo, e il destino mi ha portata da te, giusto?";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "Questa dovrebbe essere una storiella divertente sul nostro primo incontro, da raccontare ai nostri figli un giorno? O hai perso il senno, giusto?";
			link.l1 = "Sono seria, Mary. Capisco che sia difficile da credere, e che ti sembri pura follia, ma ti prego, fidati di me, giusto?";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "Sembra proprio che le storie di Eric fossero vere, giusto?";
			link.l1 = "Chi sarebbe questo Eric? E che ti ha raccontato, giusto?";
			link.l1.go = "dolly_6";
		break;
		
		case "dolly_6":
			dialog.text = "Eric era uno del posto, un vecchio lupo di mare. Ormai è morto. Quando ero bambina, mi raccontava storie su un idolo d’oro, un santuario dove Rivados sacrificava gli uomini. Qui, sull’Isola. Chi lo toccava spariva, e non lo si vedeva più. Pensavo fossero solo storie per spaventare i bambini, giusto?";
			link.l1 = "È vero, Mary. Eric non mentiva, giusto?";
			link.l1.go = "dolly_7";
		break;
		
		case "dolly_7":
			dialog.text = "Per fortuna, la nave con quell’orribile idolo è affondata. Non l’ho mai visto con i miei occhi, giusto?";
			link.l1 = "L’ho trovato, adagiato sul fondo, giusto?";
			link.l1.go = "dolly_8";
		break;
		
		case "dolly_8":
			dialog.text = "Sei davvero andato a tuffarti laggiù?! Quell’inventore maledetto, Vedecker, ti ha dato la sua tuta? Lì sotto ci sono i granchi che strisciano ovunque, giusto! Maledetto! Metterti in pericolo così!";
			link.l1 = "Mary, non preoccuparti per me. Posso cavarmela con quei mostri, non sono poi così spaventosi come dicono. Cerco quella statua dal primo giorno che sono sbarcato su quest’isola e, finalmente, l’ho trovata, giusto?";
			link.l1.go = "dolly_9";
		break;
		
		case "dolly_9":
			dialog.text = "E adesso che succederà, giusto?";
			link.l1 = "Questa è l’unica via d’uscita di qui. Sono arrivata in questo posto grazie a un idolo proprio come questo, e lo userò di nuovo per tornare indietro… Mary! Stai piangendo? Mary! Basta così, giusto?";
			link.l1.go = "dolly_10";
		break;
		
		case "dolly_10":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Shark, ";
			else sTemp = "";
			dialog.text = "Perché dovrei? Voglio piangere, piangerò, giusto... (singhiozza) Succede sempre così ai miei uomini! Rimarrò di nuovo sola!";
			link.l1 = "Cosa credi che mi succederà? Davvero pensi che ti lascerei qui?! Tornerò a prenderti, su una nave. Devo portare via sia te che "+sTemp+"Nathaniel è tornato con me. Mi seguirai nel mondo là fuori, giusto?";
			link.l1.go = "dolly_11";
		break;
		
		case "dolly_11":
			dialog.text = "(tra le lacrime) Certo... Sì, lo farò... Tornerai a prendermi, giusto? Come diavolo pensi di tornare sull’isola? Solo Squalo sa navigare fin qui. E non ti azzardare a dimenticarti di me, o ti do una lezione quando ti ritrovo, giusto?";
			link.l1 = "Mary, basta con questi tuoi pensieri folli! Certo che tornerò da te, chi mai potrebbe far battere il mio cuore come fai tu da quel giorno che t'ho incontrata? Non temere, amore mio, Shark mi ha dato le coordinate e la rotta. Ti raggiungerò, giusto?";
			link.l1.go = "dolly_12";
		break;
		
		case "dolly_12":
			dialog.text = "Hai detto che una statua ti ha portato qui direttamente da Main, ma se poi quella statua ti spedisse altrove, magari in Africa? E io cosa dovrei fare senza di te, giusto?!";
			link.l1 = "Kukulcan è un dio indiano, mi porterà da qualche parte nei Caraibi o sulla terraferma. Devo solo trovare un insediamento, poi sarà facile per me rintracciare la mia nave e l’equipaggio, giusto?";
			link.l1.go = "dolly_13";
		break;
		
		case "dolly_13":
			dialog.text = "(piange) Promettimi... anzi, giurami che tornerai, giusto!";
			link.l1 = "Mary, cara, ti giuro che tornerò. E ti porterò via da questo lurido posto. Non sentirai la mia mancanza troppo a lungo. Basta lacrime, giusto?";
			link.l1.go = "dolly_14";
		break;
		
		case "dolly_14":
			dialog.text = "D'accordo, "+pchar.name+"... ... Torna da me, ti aspetterò, giusto! Quando pensi di partire?";
			link.l1 = "Non lo so ancora. Devo prepararmi prima, poi mi tufferò e toccherò la statua. Ti diranno che sono affogata – non crederci, giusto? Andrà tutto bene.";
			link.l1.go = "dolly_15";
		break;
		
		case "dolly_15":
			dialog.text = "Ho capito, giusto?"+pchar.name+", caro, abbracciami... Baciami...";
			link.l1 = "Mary... Mia cara Mary...";
			link.l1.go = "dolly_16";
		break;
		
		case "dolly_16":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.MaryBye"); // можно телепортироваться
			DeleteAttribute(pchar, "questTemp.LSC.FindDolly");
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love_3";
			npchar.greeting = "mary_5"; 
		break;
		
		// дарим Мэри палаш Нарвал
		case "narval":
			dialog.text = "Jurgen? Perché, giusto?";
			link.l1 = "Vedrai. Questa sarà una bella sorpresa, giusto?";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "Oh, che interessante! Piacevole? È fantastico, giusto? Andiamo, prima che muoia dalla curiosità!";
			link.l1 = "Ti piacerà, ne sono certa. Andiamo, giusto?";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			DialogExit();
			NextDiag.CurrentNode = "narval_wait";
			LocatorReloadEnterDisable("CeresSmithy", "reload6", true);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", true);
			pchar.quest.LSC_PresentMary.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_PresentMary.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_PresentMary.function = "LSC_GotoPresentMary";
		break;
		
		case "narval_wait":
			dialog.text = "Andiamo, giusto?"+pchar.name+"!";
			link.l1 = "Certo, giusto?";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "narval_3":
			dialog.text = "Beh, "+pchar.name+", , che sorpresa mi hai preparato, giusto?";
			link.l1 = "Mary! Io e Jurgen abbiamo deciso di farti un regalo insieme. Questa è una lama unica, una spada larga che porta il nome di Narvalo. Ne esistono solo due al mondo: la prima era di Alan Milrow, questa sarà tua. È forgiata in un acciaio speciale, lavorato dalle mani esperte di Jurgen, che non perderà mai il filo né arrugginirà, giusto?";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Schmidt"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_5":
			dialog.text = "";
			link.l1 = "La nostra cara ragazza... Tutti i Narvali sanno quanto hai sofferto. Suppongo che tu abbia meritato di portare questa spada larga, simbolo del clan dei Narvali. Portala con orgoglio. Questa lama sarà una minaccia per i tuoi nemici e ti proteggerà in battaglia.";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			PlaySound("interface\important_item.wav");
			sld = characterFromId("Mary");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveItems(sld, "blade_17", 1);
			sTemp = GetBestGeneratedItem("blade_31");
			GiveItem2Character(sld, sTemp);
			EquipCharacterbyItem(sld, sTemp);
			sld = characterFromId("Blaze");
			dialog.text = "Jurgen? Questo... è per me, giusto?...";
			link.l1 = "Sì, giusto?"+sld.name+"  mi ha chiesto di farla per te, e ha portato un ferro unico dal fondo del mare, nessun acciaio potrà mai eguagliare il peso o la forza di questo materiale. Ho messo l'anima in questa spada, proprio come feci una volta con quella di Alan, giusto?";
			link.l1.go = "narval_7";
		break;
		
		case "narval_7":
			dialog.text = "Non so proprio cosa dire... Grazie, Jurgen! Grazie, giusto? Lo porterò con orgoglio e sarò all’altezza della lama, lo giuro, giusto? Non mi sono allenata abbastanza con le spade larghe, ma ora mi allenerò sul serio!";
			link.l1 = "Su questo non ho alcun dubbio, giusto?";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_9":
			dialog.text = ""+pchar.name+"... aspetta, no... Sei l’uomo migliore che abbia mai incontrato! Sei davvero straordinario, giusto? Sai quanto significa per me tutto questo? Questa spada è il dono più bello che avrei mai potuto ricevere! Hai già fatto così tanto per me, mi hai salvato la vita due volte, eppure continui a sorprendermi! Grazie, amore mio!";
			link.l1 = "Non poteva andare diversamente, Mary. Continuerò a stupirti ogni giorno, fino all’ultimo mio respiro! Il tuo sorriso mi dà gioia e sono felice che il regalo ti piaccia, giusto?";
			link.l1.go = "narval_10";
		break;
		
		case "narval_10":
			dialog.text = "(ride) Grazie! Che lama splendida, giusto? Ci vuole una mano ferma per brandirla... Non vedo l’ora di cominciare ad allenarmi con questa!";
			link.l1 = "Non vedo il problema. Corri in cabina e prova la tua nuova spada larga, giusto?";
			link.l1.go = "narval_11";
		break;
		
		case "narval_11":
			dialog.text = "È proprio quello che sto per fare. Grazie ancora, gentiluomo, giusto? "+pchar.name+"... Vieni a trovarmi stanotte, quando sei pronto... (ride)";
			link.l1 = "Ma certo, mia signora. Ci vediamo stasera, giusto?";
			link.l1.go = "narval_12";
		break;
		
		case "narval_12":
			DialogExit();
			EndQuestMovie();
			sld = characterFromId("Schmidt");
			sld.dialog.currentnode = "Jurgen";
			DeleteAttribute(sld, "quest.narval_blade");
			DeleteAttribute(npchar, "quest.narval_blade");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "CeresSmithy", "goto", "goto10", "LSC_MaryReturnNormal", -1);
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем проход через трюм
			// владение Нарвалом повышает скилл ТО у Мэри и открывает перк тяжелой руки
			SetSelfSkill(npchar, 95, 50, 90, 90, 50);
			SetCharacterPerk(npchar, "HardHitter");
			npchar.quest.talisman = "true";
			npchar.quest.blade31 = "true";
		break;
		
		// Мэри дарит талисман
		case "talisman":
			dialog.text = "Ecco, dai un'occhiata. L'ho trovato su una delle navi all'esterno, dentro il baule di un capitano. Ogni vecchio lupo di mare dice che questo oggetto è preziosissimo per un navigatore, riesce a proteggere una nave dalle tempeste più feroci. Alcuni erano persino disposti a comprarlo, ma non l'ho mai venduto... Voglio che sia tuo, amore. Tienilo con te, ti proteggerà in mare, giusto?";
			link.l1 = "Grazie, Mary! Che premura, ti adoro, giusto?";
			link.l1.go = "talisman_1";
		break;
		
		case "talisman_1":
			GiveItem2Character(pchar, "talisman2"); 
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a talisman of 'Jonah'");
			dialog.text = "Davvero? Ti piace? Oh, che meraviglia! Sono proprio felice, giusto?";
			link.l1 = "Questo è un talismano davvero raro e prezioso. Certo che mi piace! Grazie, tesoro, giusto?";
			link.l1.go = "talisman_2";
		break;
		
		case "talisman_2":
			DialogExit();
			DeleteAttribute(npchar, "quest.talisman");
		break;
		
	// --------------------------------------вернулся на Остров---------------------------------------------
		case "return":
			dialog.text = ""+pchar.name+"... Sei tornato. Ti aspettavo, ogni giorno scrutavo l’orizzonte, giusto? Sei tornato da me...";
			link.l1 = "Sì, Mary. Sono qui come ti avevo promesso. Vieni qui, lasciami stringerti, tesoro!";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Ah, "+pchar.name+"... Non puoi nemmeno immaginare come mi sono sentita! I Narwhal parlavano della tua morte, dicevano che eri annegato. Erano tutti convinti che fossi morto. Continuavo a ripetere che eri vivo... Ovviamente nessuno mi credeva, pensavano che fossi impazzita dopo tutto quello che è successo, giusto?";
			link.l1 = "Mary... Mia cara! Che ti prende? Stai tremando... Hai freddo, giusto?";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "No, non ho freddo. È solo che… non voglio parlarne qui. Vieni alla mia cabina quando hai finito. Voglio restare sola con te, giusto… Non vai ora dall’ammiraglio e da Nathaniel?";
			link.l1 = "Sì. Devo parlare con Shark e, ovviamente, portare Danielle da Nathaniel. Non ci metterò molto. Ci vediamo presto, Mary.";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "Non vedo l'ora di... vederti. Vieni appena puoi, giusto!";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload62", "CeresSmithy", "goto", "goto11", "LSC_MaryWaitInCabin", 20.0);
		break;
		
		case "adversary":
			dialog.text = ""+pchar.name+"Finalmente. Dobbiamo parlare, giusto?";
			link.l1 = "Cosa c’è che non va, Mary? Vedo che qualcosa ti turba! Che succede, giusto?";
			link.l1.go = "adversary_1";
		break;
		
		case "adversary_1":
			dialog.text = "È successo... giusto?"+pchar.name+", chi è quella sgualdrina sulla tua nave?";
			link.l1 = "Chi? Parli di Danielle? Ma lo sai già, giusto?";
			link.l1.go = "adversary_2";
		break;
		
		case "adversary_2":
			dialog.text = "No, non Danielle. Intendo quella bionda, quasi senza un filo addosso, che se ne va a zonzo sul ponte della tua nave! L'ho vista col cannocchiale, giusto?";
			link.l1 = "A-ah! Quella è Helen McArthur. È invischiata in questa faccenda strana proprio come Danielle. Adesso fa parte del mio equipaggio come ufficiale. Ma è solo una cosa temporanea, giusto?";
			link.l1.go = "adversary_3";
		break;
		
		case "adversary_3":
			dialog.text = "Ufficiale? Lei sarebbe un ufficiale?!";
			link.l1 = "Ebbene sì. Che c’è di male in questo?.. Mary, maledizione! Sei gelosa, giusto?";
			link.l1.go = "adversary_4";
		break;
		
		case "adversary_4":
			dialog.text = "Cosa pensavi, eh?!... (tra le lacrime) Ti ho aspettato per tutto questo tempo, non ho chiuso occhio per colpa tua, e tu osi tornare qui con quella strega, giusto?";
			link.l1 = "Mary! Smettila di piangere! Che ti prende? Sei capace di sventrare un uomo senza batter ciglio, eppure hai sempre gli occhi lucidi... Mary, cara, Helen è solo un’ufficiale, di passaggio finché la giustizia non sarà fatta e i nostri scopi raggiunti, niente di più, giusto?";
			link.l1.go = "adversary_5";
		break;
		
		case "adversary_5":
			if (CheckAttribute(npchar, "quest.blade31")) 
			{
				sTemp = "I have been training hard with the broadsword you gave me, and in your absense I have mastered it perfectly.";
				notification("Heavy Weapons +", "Mary");
			}
			else sTemp = "I have been training hard with rapiers and I have mastered them perfectly.";
			dialog.text = "(singhiozzando) Ufficiale... Allora voglio essere anch’io il tuo ufficiale, giusto! So combattere, lo sai bene!"+sTemp+"E poi ci so fare con le pistole! Magari non sono una cima in mare, ma imparo in fretta, ho talento, giusto?";
			// проход первый - ГГ либо соглашается, либо нет, отказ ведет к полному разрыву
			link.l1 = "Mary... volevo offrirti io stessa questo posto. Non c’è nessuna più abile, più ardente e più tosta di te! Ti voglio al mio fianco, giusto?";
			link.l1.go = "adversary_hire";
			link.l2 = "Mary! Fare l'abbordaggio è roba da disperati! Non hai idea di cosa chiedi. Non posso mettere a rischio la tua vita, giusto?";
			link.l2.go = "adversary_fail";
		break;
		
		// отказ
		case "adversary_fail":
			dialog.text = "Non puoi? Quella sgualdrina bionda può diventare ufficiale e io no? Mi stai raccontando frottole, giusto?"+pchar.name+", semplicemente non vuoi stare con me! (piange) Quella ragazza è meglio di me, giusto?";
			link.l1 = "Mary, non capisci, giusto?";
			link.l1.go = "adversary_fail_1";
		break;
		
		case "adversary_fail_1":
			dialog.text = "Lo so! Ho visto quegli occhi infuocati puntati su di te! Non è soltanto un’ufficiale, giusto? Capisco (singhiozza). Ovviamente, io non posso competere con lei – quella sa davvero comandare una nave...";
			link.l1 = "Mary, di che diamine stai parlando, giusto?";
			link.l1.go = "adversary_fail_2";
		break;
		
		case "adversary_fail_2":
			dialog.text = "È finita... (piange) Vai via! Vai dalla tua sgualdrina! E io resterò qui... Non me ne vado da nessuna parte! Ridammi la mia chiave, giusto?";
			link.l1 = "Ma Mary, giusto?";
			link.l1.go = "adversary_fail_3";
		break;
		
		case "adversary_fail_3":
			RemoveItems(pchar, "key_mary", 1);
			dialog.text = "Vai via, giusto?";
			link.l1 = "...";
			link.l1.go = "adversary_fail_4";
		break;
		
		case "adversary_fail_4": // обидел Мэри - больше от неё ничего не получишь
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=0; i<=3; i++)
			{
				LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, true); // закрываем вход к Мэри
			}
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "");
			pchar.questTemp.LSC.Mary = "fail";
			AddQuestRecord("LSC", "23");
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		// соглашаемся
		case "adversary_hire":
			// проход второй - смотрим, Элен может стать подругой или нет
			bOk = (CheckAttribute(pchar, "questTemp.HelenDrinking.GaveCutlass")) && (sti(pchar.questTemp.Saga.HelenRelation) >= 6);
			if (bOk || sti(pchar.questTemp.Saga.HelenRelation) >= 5 || CharacterIsAlive("Longway"))
			{
				dialog.text = "Davvero? Mi volevi davvero come tua ufficiale, giusto?"+pchar.name+"Maledizione, non immagini nemmeno quanto sono felice! Voglio tanto diventare il tuo ufficiale... ma non sulla stessa nave di quella bionda, giusto?";
				link.l1 = "Mary, ma perché, giusto?";
				link.l1.go = "adversary_hire_no";
			}
			else
			{
				dialog.text = "Davvero? Mi volevi davvero come tua ufficiale, giusto?"+pchar.name+"Maledizione, non immagini quanto sono felice! Te lo giuro, non ti deluderò, vedrai, giusto?";
				link.l1 = "Santo cielo, Mary, tesoro, sei davvero preziosa. Un attimo fa piangevi e ora il tuo viso brilla tutto! E poi, Mary, per me non sei solo un altro ufficiale. Sei molto di più, giusto? E dubito che tu possa mai deludermi, in qualsiasi modo.";
				link.l1.go = "adversary_hire_yes";
			}
		break;
		
		case "adversary_hire_no": // Мэри не пойдёт, пока не ГГ не расстанется с Элен. Выбирай, кто тебе милее...
			dialog.text = "Puoi anche considerarla solo un tuo ufficiale, ma dubito che lei ti veda soltanto come il suo capitano. Ho visto come ti guardava, riconosco quello sguardo, giusto! Solo io posso guardarti così!";
			link.l1 = "Mary, cara, ma te l’ho già detto, non provo niente per lei, e basta! Tra noi non c’è nulla, giusto? Te lo giuro, maledizione! Ho solo bisogno del suo aiuto per risolvere un casino con la Fratellanza della Costa. Jan Svenson non mi darà una mano a prendere Tortuga se non la aiuto, e di lui ho bisogno, giusto?";
			link.l1.go = "adversary_hire_no_1";
		break;
		
		case "adversary_hire_no_1":
			dialog.text = ""+pchar.name+", caro, abbracciami... Mi dispiace. Ti credo. Ma non potrò restare vicino a lei e guardarla mentre cerca di civettare con te, giusto! Prima o poi prenderò la mia spada e la taglierò in due!";
			link.l1 = "Sì, puoi farlo senza dubbio... Hai proprio un bel caratterino, giusto?";
			link.l1.go = "adversary_hire_no_2";
		break;
		
		case "adversary_hire_no_2":
			dialog.text = "E se la uccido – te ne andrai da me, giusto... Non me lo perdonerei mai.";
			link.l1 = "Allora, che proponi, Mary? Cosa dovrei farne di lei, giusto?";
			link.l1.go = "adversary_hire_no_3";
		break;
		
		case "adversary_hire_no_3":
			dialog.text = "Hai detto che lei è solo un ufficiale temporaneo. Mi unirò a te non appena la lascerai a terra. Sperduta su qualche isola deserta, spero (ride) che ti seguirò fino alla fine del mondo, giusto!"+pchar.name+", caro, è davvero meglio di me, giusto?";
			link.l1 = "Fandonie! Smettila di dire certe cose, Mary cara, non c’è donna migliore di te, giusto?...";
			link.l1.go = "adversary_hire_no_4";
		break;
		
		case "adversary_hire_no_4":
			dialog.text = "Allora dimostramelo. Non voglio dividerti con nessuno, giusto?"+pchar.name+"! Meglio sola che dividerti con qualcun’altra, giusto...";
			link.l1 = "Va bene, Mary. Facciamo un patto. Non posso liberarmi di Helen adesso, è importante per questa faccenda. Le darò una mano con i suoi guai, la farò diventare padrona di Isla Tesoro, la lascerò andare, e tra noi non resterà più nulla. Spero solo che non ci vorrà più di un mese o due. Mi aspetterai così tanto, giusto?";
			link.l1.go = "adversary_hire_no_5";
		break;
		
		case "adversary_hire_no_5":
			dialog.text = "Ma certo che lo farò, giusto? È la mia scelta... Se torni da me, vuol dire che hai scelto me invece di lei. E se non torni... sarà il mio destino allora. Resterò qui e fonderò il mio clan. Il clan Casper...";
			link.l1 = "Piangi ancora? Mary, su. Basta con queste sciocchezze! Di che parli? Quale clan... Sciocchina, certo che torno, non oserei mai lasciarti tra queste vecchie carcasse marce! Rischieresti d'allagare l’isola con le tue lacrime, giusto?";
			link.l1.go = "adversary_hire_no_6";
		break;
		
		case "adversary_hire_no_6":
			dialog.text = "Torna appena puoi, giusto? "+pchar.name+", tesoro, baciami, ti prego...";
			link.l1 = "Tornerò. Promesso, giusto?"; // ага, а мы посмотрим, обманешь или нет
			link.l1.go = "adversary_hire_no_7";
		break;
		
		case "adversary_hire_no_7":
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love"; // оставляем штучки с Мэри на Острове в силе
			pchar.questTemp.LSC.MaryWait = "true";
			AddQuestRecord("LSC", "22");
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		// повторный разговор после расставания с Элен
		case "adversary_hire_return":
			dialog.text = "Mi stai prendendo in giro, giusto? "+pchar.name+", davvero non ti sei scordato di me, giusto?";
			link.l1 = "Ma certo! Ti ho mai tradito, giusto? Ne ho passate di tutti i colori mentre eravamo lontani, e non ho alcuna intenzione di separarmi di nuovo da te... mio talismano.";
			link.l1.go = "adversary_hire_yes";
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
		break;
		
		case "adversary_hire_yes": // Элен заведомо не друг - Мэри идёт сразу, либо если выбрал Мэри
			dialog.text = "Davvero, giusto?"+pchar.name+"! Ti seguirò sempre! Non ti mentirò mai, non ti tradirò mai, lo giuro, giusto?";
			link.l1 = "Ti credo, tesoro... Nemmeno io lo farò, giusto?"; // а куда же ты денешься )
			link.l1.go = "adversary_hire_yes_1";
		break;
		
		case "adversary_hire_yes_1":
			dialog.text = ""+pchar.name+" , tesoro, abbracciami... Staremo insieme, giusto? Dimmi!";
			link.l1 = "Sì, saremo insieme, Mary. Per sempre, giusto?";
			link.l1.go = "adversary_hire_yes_2";
		break;
		
		case "adversary_hire_yes_2":
			dialog.text = "Proprio come Danielle e Nathaniel, giusto?";
			link.l1 = "(ridendo) Giusto, proprio come loro.";
			link.l1.go = "adversary_hire_yes_3";
		break;
		
		case "adversary_hire_yes_3":
			dialog.text = ""+pchar.name+"... Ti amo! Ti sposerò se lo vuoi, giusto...";
			link.l1 = "Mary cara... Certo, ne parleremo più tardi. La tua vita in questo cimitero di navi è finita, prima portiamoti via di qui – benvenuta a bordo della mia nave e nel vasto mondo, amore mio!";
			link.l1.go = "adversary_hire_yes_4";
		break;
		
		case "adversary_hire_yes_4":
			dialog.text = "Passiamo la nostra ultima notte su quest’isola insieme, sulla 'Ceres Smithy'. Solo noi due. Solo tu e io... Non ti lascerò andare da nessuna parte fino al mattino, giusto?";
			link.l1 = "Ebbene, non siamo sulla mia nave, quindi seguirò i tuoi ordini... Mia cara Mary, giusto?";
			link.l1.go = "adversary_hire_yes_5";
		break;
		
		case "adversary_hire_yes_5":
			DialogExit();
			npchar.quest.hire = "true";
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			DoQuestCheckDelay("LSC_LastNight_CS", 3.0);
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "LSC_mary_hire":
			dialog.text = "Ai-ai, capitano!";
			link.l1 = "...";
			link.l1.go = "LSC_mary_hire_1";
		break;
		
		case "LSC_mary_hire_1":
			DialogExit();
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "LSC_Mary_hire");
			if (pchar.questTemp.LSC.Mary != "return") AddQuestRecord("LSC", "24");
			pchar.questTemp.LSC.Mary = "officer";
			RemoveItems(pchar, "key_mary", 1);
		break;
		
	// --> консультации по морским сражениям
		case "sea_bomb":
			dialog.text = ""+pchar.name+"! Ho un’idea, giusto?";
			link.l1 = ""+npchar.name+"Giusto? Non è sicuro qui e ti avevo ordinato di restare sulla nave...";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = ""+pchar.name+", c’è così tanta polvere da sparo su questa vecchia carretta che, se scoppia, vola tutta l’isola in aria. Ormai non importa dove restiamo. Basta che mi ascolti, giusto?";
			link.l1 = "Ascolto, ma sbrigati, giusto?";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "La corvetta pirata e la fregata. Credono che siamo dei loro... Coltello, giusto? Questa potrebbe essere la nostra occasione. Prendiamo qualche barile di polvere da sparo, una miccia, e navighiamo verso di loro.\nQuando ci lasceranno avvicinare, accendiamo la miccia, lanciamo il barile su una delle navi e scappiamo più in fretta che possiamo. Deve essere l'occasione perfetta per vedere un bello spettacolo di fuochi d'artificio... Che ne pensi, giusto?";
			link.l1 = "Rischioso, però il tuo piano potrebbe anche funzionare... Solo se non ci sgamano, giusto?";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "Rischiamo, giusto?"+pchar.name+"?";
			link.l1 = "Va bene. Andiamo avanti, giusto? Ragazzi! Prendete tre barili di polvere da sparo! Ce ne andiamo al diavolo da qui! Adoro la tua fantasia, giusto?"+npchar.name+"... Non mi sarebbe mai venuta in mente da sola, giusto?";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			dialog.text = "Te l’avevo detto, anche io ho i miei talenti, giusto?";
			link.l1 = "...";
			link.l1.go = "sea_bomb_5";
		break;
		
		case "sea_bomb_5":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			AddQuestRecord("BarbTemptation", "15");
			AddQuestUserData("BarbTemptation", "sName", "Mary");
			pchar.questTemp.Saga.BarbTemptation.adviser = "Mary";
		break;
		
		case "fugas":
			dialog.text = "Sì, certo, caro. Son sempre pronta a dare una mano, giusto? Che succede?";
			link.l1 = "La nave di Jackman è alla Baia di Sabo-Matila, la grossa fregata 'Centurion'. Questa nave apparteneva un tempo agli Hawkes, quindi nella cabina di Jackman ci saranno di sicuro cose preziose e documenti importanti... dobbiamo salirci a bordo, giusto?";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "Capisco. E come pensi di fare tutto ciò con il nostro uccellino? Quelli là hanno più uomini e cannoni. Ho già guardato col cannocchiale, giusto?";
			link.l1 = "Hai ragione. Jackman ha almeno il doppio degli uomini rispetto a noi, e sono tutti tagliagole e mercenari navigati. Sarebbe pura follia abbordare senza prepararci a dovere. Una lunga battaglia in mare non è nemmeno un'opzione, giusto? Quindi stavo pensando ad altre strade per portare a termine il compito.";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = ""+pchar.name+", non ci hanno ancora riconosciuti come nemici, proprio come quegli scemi laggiù a Turks... Possiamo riprovare il nostro trucchetto, giusto?";
			link.l1 = "Mary, ti ho appena spiegato che dobbiamo abbordare la fregata, affondarla non è un'opzione, giusto?";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "Lo so, giusto?"+pchar.name+"Non la affonderemo. Ascolta, prenderemo alcune botti vuote di rum e le riempiremo di polvere da sparo, mitraglia e micce corte. Poi ci avvicineremo alla loro fregata e lanceremo queste bombe improvvisate sul loro ponte, giusto?";
			link.l1 = "Ah! Davvero pensi che funzionerà, giusto?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "E perché no? Il loro bordo libero è più alto del nostro, ma con una carrucola e due o tre uomini possiamo sollevare e lanciare una botte piena senza fatica. Grideremo: 'Ecco del rum gratis da Knive!' E le botti scoppieranno prima ancora che capiscano cosa succede, giusto?";
			link.l1 = "La mitraglia esplosiva farà a pezzi i suoi uomini migliori sul ponte... Maledizione, suona proprio invitante, giusto?";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Usiamo cinque barili, giusto?"+pchar.name+", abbiamo il vantaggio della sorpresa. Non sospetteranno nulla! Dobbiamo salpare subito prima che ci mettano le mani addosso, giusto?";
			link.l1 = "Bene, proviamoci. Non devono riconoscerci prima che lanciamo le botti... Maledizione, non sarà facile avvicinarsi a loro, giusto? Jackman non è uno sprovveduto come quel Ghoul.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "Rischiamo, giusto?"+pchar.name+"! Tanto non farà male, giusto?";
			link.l1 = "Bel punto, non abbiamo nulla da perdere... Prepara le fougasses, giusto?";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			dialog.text = "Lo farò, capitano mio! Li preparerò alla perfezione, giusto?";
			link.l1 = "Ehi, non ti hanno lasciato stordire quei granchi sull’isola, così eccomi qui a farti scatenare contro qualche culo di pirata, giusto... Mary, sei davvero una meraviglia!";
			link.l1.go = "fugas_8";
		break;
		
		case "fugas_8":
			dialog.text = "Grazie, giusto?"+pchar.name+"! Non ti deluderò, giusto?";
			link.l1 = "Su questo non ho dubbi. Spero solo che saremo noi a non deluderti mandando tutto a puttane con questo tuo piano... Alle armi, giusto?";
			link.l1.go = "fugas_9";
		break;
		
		case "fugas_9":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		// <-- консультации по морским сражениям
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "Eccoti qua! Ci è voluto un po’ per trovarti... Sei stato incredibile, capitano! Non ho mai visto un salto così mozzafiato! Sei sempre il mio eroe! Anche se, ammetto, quasi mi è venuto un infarto, giusto? Un giorno mi farai crepare con questi tuoi numeri, tesoro... Allora, chi diamine sarebbe questa qui? Oh "+pchar.name+"Giusto?, ti lascio sola un attimo e subito ti ritrovo circondata da una folla di sgualdrine!";
			link.l1 = "Mary, questa 'sgualdrina' è Catherine Fox, figlia del colonnello Fox, il comandante delle Volpi di Mare. Dobbiamo portarla ad Antigua, giusto?";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "Oh, davvero? Che piacere! Va bene, me la racconterai... stanotte, quando resteremo insieme, soli soletti. Adesso andiamo, dobbiamo sbrigarci, giusto?";
			link.l1 = "Sei la migliore, Mary. Cosa farei senza di te? Catherine, andiamo, giusto?";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "Finalmente ti sei svegliato, tesoro mio... Bastardo! Non farmi mai più prendere uno spavento così, giusto?";
			link.l1 = "Mary... cara, che ti è successo? Mi scoppia la testa, giusto?";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Quando siamo entrati nella cabina del capitano, tu eri steso per terra, immobile come un cadavere. Il mio cuore batteva all'impazzata! I ragazzi ti hanno sollevato e trascinato sulla nostra nave – proprio in tempo, perché i morti stesi sul ponte hanno cominciato a rialzarsi, giusto? Che incubo! Non potevamo farci nulla! Abbiamo tagliato le cime in fretta e cercato di salpare, ma una scarica dalla loro nave ha colpito duro lo scafo e abbiamo perso il controllo. Erano veri diavoli, giusto? E poi hanno issato le vele e sono spariti in un batter d'occhio. La nostra nave è finita contro la secca, così siamo dovuti scappare su questa riva prima che la tempesta la facesse a pezzi. Oggi sono morti tanti bravi marinai, ma alla fine la nave si è salvata...";
			link.l1 = "Bel lavoro, Mary... Cosa farei senza di te, giusto?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Forse saresti affogato, o saresti rimasto su quella nave, e i morti ti avrebbero fatto a pezzi... Le mie mani tremano ancora, giusto?";
			link.l1 = "Grazie, tesoro. Da quanto tempo sono svenuta, giusto?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Per un'intera giornata. Ho pulito le tue ferite, ti ho dato delle medicine e ti ho versato un po' di rum. Dovresti rimetterti presto. E non osare crepare proprio adesso, giusto?";
			link.l1 = "Prometto che stavolta non ci lascerò la pelle, tesoro. Anche se non mi sento proprio al meglio, giusto?";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "Questo è sicuro... Era la 'Olandese Volante', capitano? Perché ci hanno assalito? E perché non hanno sparato prima di salire a bordo, giusto?";
			link.l1 = "Il loro capitano voleva proprio quell’amuleto, quello di cui avevo parlato a Tuttuathapak, lo sciamano indiano. Ecco perché dovevano abbordarci, giusto? Ma appena il loro capitano ha preso l’amuleto, non gli interessavamo più... Che incubo! Una nave governata dai morti! Incredibile, giusto?";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Già, pare che il 'Vascello Fantasma' sarebbe venuto a prenderci prima o poi. Appena ne avrò l’occasione, andrò in chiesa, accenderò una candela per la nostra scampata fortuna e pregherò il Signore, giusto?";
			link.l1 = "Anche io, Mary, credo. Devo tornare in quel villaggio. Bisogna far sapere a Tuttuathapak cos'è successo. Quella nave ci ha attaccati per colpa dell’amuleto! Spero che quel diavolo dalla pelle rossa abbia una spiegazione sul perché quelle maledette anime in pena ne avessero bisogno, giusto?";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Giusto? Ma fa' attenzione – le tue ferite sono appena guarite.";
			link.l1 = "Tu sei tutta la cura di cui ho bisogno. E... Mary, ti amo, giusto?";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "Anch’io ti amo, tesoro mio... giusto?";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
	// --> Мэри вне LSC
		// секс - Мэри не отказывает никогда
		case "cabin_sex":
			dialog.text = RandPhraseSimple(""+pchar.name+", non c’è felicità più grande per me che stare fra le tue braccia, giusto... Andiamo!",""+pchar.name+" , vorrei starti accanto ogni attimo che respiro, se solo fosse possibile. Andiamo, giusto?");
			link.l1 = RandPhraseSimple("Sei il migliore, amore mio... giusto?","Sei meraviglioso, il mio portafortuna... giusto?");
			link.l1.go = "exit";
			AddDialogExitQuest("cabin_sex_go");
		break;
		
		case "sex_after":
			dialog.text = RandPhraseSimple("Caro, sei stato incredibile... lo sei sempre, giusto?","È stato fantastico, giusto?");
			link.l1 = RandPhraseSimple("Sono felice che tu sia contento, amore mio... giusto?","Ti amo, Mary...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex"); // belamour для бесконфликтности квестов							
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", non c’è felicità più grande per me che stare tra le tue braccia, giusto... Ma ora non è il momento migliore – dobbiamo acchiappare quella carogna di Thibaut prima che si dia alla fuga.";
				link.l1 = "Hai sempre ragione, ragazza mia, giusto?";
				link.l1.go = "exit";
				break;
			}
			dialog.text = RandPhraseSimple(""+pchar.name+", non c’è felicità più grande per me che stare tra le tue braccia, giusto... Andiamo!",""+pchar.name+" , vorrei starti accanto ogni singolo istante, se solo fosse possibile. Andiamo, giusto?");
			link.l1 = RandPhraseSimple("Sei il massimo, ragazza mia, giusto?","Sei meraviglioso, il mio talismano dai capelli rossi, giusto?");
			link.l1.go = "room_sex_go";
		break;
		
		case "room_sex_go":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
			{
			//DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
			DoFunctionReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "GiveKissInRoom");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_upstairs", "quest", "quest3");
			} // patch-8
			//DoQuestCheckDelay("Mary_LoveSex", 2.5);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
		break;
		
		// требует секса, если давно не давал
		case "givemesex":
			dialog.text = RandPhraseSimple(""+pchar.name+", è passato un secolo dall’ultima volta che abbiamo fatto l’amore... Ti sei proprio dimenticato di me, giusto! Tesoro, voglio rilassarmi, prendiamo una stanza per stanotte e lasciamo le preoccupazioni a domani!",""+pchar.name+", sei stato troppo occupato e comincio a pensare che ti sei proprio dimenticato di me! Tesoro, vorrei... restare con te in privato. Prendiamo una stanza per la notte, giusto?",""+pchar.name+", hai perso la testa? Voglio passare la notte insieme a te, bere un po’ di vino e rilassarci. Sei stato troppo occupato in mare e ti sei completamente dimenticato di me, giusto?");
			link.l1 = "Mary, tesoro, ma che dici mai – ‘mi hai dimenticata del tutto’? Sciocchina... Però è vero che sono stato troppo preso, i guai non finiscono mai, giusto? Perdonami, amore mio. Andiamo di sopra, stanotte sono tutto tuo, il mondo può aspettare, giusto?";
			link.l1.go = "room_sex_go";
		// belamour legendary edition -->
			link.l2 = RandPhraseSimple(RandPhraseSimple("Oggi no, caro. Ho un gran mal di testa, giusto?","Mary, tesoro, come potrei mai scordarmi di te? Dai, dopo – ora abbiamo del lavoro da sbrigare, giusto?"),RandPhraseSimple("Mi stai sempre nei pensieri, Mary, ma ora non possiamo permetterci di abbassare la guardia, giusto?","Mary "+npchar.lastname+", oggi non abbiamo tempo per sciocchezze, giusto?"));
			link.l2.go = "room_sex_goNS";
		break;
		
		case "room_sex_goNS":
		if(sti(pchar.reputation.fame) > 60)
		{
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex"); 
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
			pchar.quest.Mary_giveme_sex.over = "yes"; 
			pchar.quest.Mary_giveme_sex1.over = "yes";
			dialog.text = "Beh... Cos'altro posso dire... Giusto, capitano!";
			link.l1 = "...";
			link.l1.go = "exit";
		}
		else
		{
			if(bImCasual) Log_Info("To refuse Mary become more famous");
			ChangeCharacterComplexReputation(pchar,"authority", -2);
			dialog.text = "Charles...";
			link.l1 = "Mary, cara, ma che dici – ‘ti sei scordato di me del tutto’? Sciocchina... Però davvero sono stato sommerso dagli impegni, i guai non finiscono mai. Perdonami, ragazza mia. Andiamo di sopra, il mondo può aspettare, giusto?";
			link.l1.go = "room_sex_go";
		}
		break;
		// <-- legendary edition
		// ругается за то, что ходил по борделям, ГГ изворачивается
		case "brothel":
			dialog.text = "Eccolo là! Non mi vuoi più bene, giusto? Dimmi la verità!";
			link.l1 = "Cosa?! Mary, che sciocchezze vai dicendo? Perché mai pensi una cosa del genere, giusto?";
			link.l1.go = "brothel_1";
		break;
		
		case "brothel_1":
			dialog.text = "Allora perché sei andato da quelle sgualdrine, quelle puttane da bordello? Lo so che l'hai fatto, non mentire! C’è qualcosa che non ti piace in me quando facciamo l’amore, giusto? (piange) Dimmi...";
			link.l1 = "Mary, Mary... calmati, ti prego, ragazza mia. Sì, sono stato al bordello un paio di volte, ma solo per affari. Non cercavo divertimento, giusto?";
			link.l1.go = "brothel_2";
		break;
		
		case "brothel_2":
			dialog.text = "E quale tipo di ‘affari’ ti ha portato di sopra nella stanza del piacere? (singhiozza) Stai mentendo, giusto?"+pchar.name+"!";
			link.l1 = "Mary, cara, smettila una buona volta... Avevo davvero delle faccende con la padrona del bordello.  E sì, sono salito di sopra un paio di volte. L’ultima era per una questione personale del governatore – mi ha chiesto di ritrovare la sua fede nuziale. Come potevo rifiutare a Sua Eccellenza, giusto?";
			link.l1.go = "brothel_3";
		break;
		
		case "brothel_3":
			dialog.text = "";
			link.l1 = "E come potevo spiegare alla padrona che dovevo guardare sotto il letto al piano di sopra? Non potevo, giusto? Così ho dovuto pagare una sgualdrina per la notte per avere il permesso di salire... La seconda volta, mi hanno detto che un mercante aveva perso lì i documenti della sua nave. Ho dovuto pagare di nuovo una ragazza per poter cercare la stanza, ma almeno sono stato ben ricompensato per quei documenti, giusto?";
			link.l1.go = "brothel_4";
		break;
		
		case "brothel_4":
			dialog.text = "";
			link.l1 = "La terza volta che ho aiutato il comandante locale: dovevo chiedere alle sgualdrine di un ufficiale della guarnigione. Quell’ufficiale era sospettato di spionaggio e di legami con i pirati. Alla fine l’abbiamo beccato e ho ricevuto una bella ricompensa, giusto?";
			link.l1.go = "brothel_5";
		break;
		
		case "brothel_5":
			dialog.text = "";
			link.l1 = "Vedi? Te lo dico io, era solo questione d'affari. Mary, sei tu quella che amo e di cui ho bisogno. Sei la migliore, giusto? Davvero pensi che andrei con qualche sgualdrina di porto, quando ho te? Come ti viene in mente una cosa simile su di me, giusto?";
			link.l1.go = "brothel_6";
		break;
		
		case "brothel_6":
			dialog.text = ""+pchar.name+"... È tutto vero? Sei sincero con me? Non sei mai stato con loro, giusto?";
			link.l1 = "Mary, cara, sei l’unica donna che amo, è la verità. Vieni qui vicino, bella. Lasciami stringerti… Asciuga quelle lacrime e, per favore, smettila di essere gelosa! Non metterò più piede in un bordello, se è quello che vuoi, giusto?";
			link.l1.go = "brothel_7";
		break;
		
		case "brothel_7":
			dialog.text = "Sì, è proprio quello che voglio... "+pchar.name+", sono gelosa perché ti amo... E non voglio perderti, giusto! Mi senti? Ammazzerò qualunque sgualdrina osi avvicinarsi anche solo di un dito a te!";
			link.l1 = "Calmati... Non c’è bisogno di ammazzare nessuno. E non mi perderai, te lo prometto. Va tutto bene, rilassati. Sei la mia unica e la miglior ragazza del mondo... Fidati, è proprio così, giusto?";
			link.l1.go = "brothel_8";
		break;
		
		case "brothel_8":
			DialogExit();
			SetLaunchFrameFormParam("", "", 0, 5);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			pchar.GenQuest.BrothelLock = true; // все, больше не походишь по борделям :)
			DeleteAttribute(pchar, "GenQuest.BrothelCount");
		break;
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+", che domanda strana? Ti amo. Mi hai salvata. Sono il tuo talismano dai capelli rossi – davvero pensi che ti lascerei andare là da solo? Nemmeno per sogno, giusto? Sono con te! Quando partiamo?";
			link.l1 = "Hai ragione, caro, era proprio una domanda strana... Te lo racconterò più tardi, quando andremo. Prima dobbiamo prepararci, giusto?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Sono pronta, capitano mio! Ti seguirò fino ai confini del mondo, giusto?";
			link.l1 = "Grazie, amore mio...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "19");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			pchar.quest.Mary_giveme_sex1.over = "yes"; // fix 22-03-20
			pchar.questTemp.GoldenGirl.MaryBlock = "true"; // fix 22-03-20
			dialog.text = "Che succede stavolta, Capitano? Spagnoli, filibustieri o qualcosa di peggio, giusto?";
			link.l1 = "È peggio, Mary, molto peggio. Il governatore ha intenzione di fare visita a una cortigiana dalle tariffe stellari e io dovrei accompagnarlo come ospite d’onore, come avevo promesso alla padrona. Chiacchiere noiose, vino strapagato e nobili insulsi, giusto?";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "Tutt'altro, un vero peso quell'invito a una festa di società, organizzata da una nobildonna. Sua Eccellenza mi ha colta alla sprovvista chiedendomi di accompagnarlo, ma a dire il vero, non vedo l’ora di distrarmi un po’, giusto?";
			link.l2.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "Ah davvero?! Una cortigiana? Lo dici come se fosse una cosa da niente, eh? Ti stai solo divertendo un po’ con Sua Eccellenza? Charles, mi stai prendendo per i fondelli, giusto?";
			link.l1 = "Mary, calmati, ti prego! Non è che ci vado per... non è un bordello! Beh, è un bordello, dannazione, ma sono un gentiluomo e un uomo d’onore, giusto? Davvero non ti fidi di me? Il governatore mi ha solo chiesto un piccolo favore e devo accontentarlo, tutto qui!";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "Sì, ho sentito parlare di un paio di quei ‘nobili’, giusto? Li ho visti anche in tua compagnia. Le cortigiane sono il loro pane quotidiano! Le ‘alte’ società, i loro ‘divertimenti dignitosi’… ma va’ al diavolo! Neanche il matrimonio li ferma dal visitare queste… signore. Maledizione, non avevo idea che anche tu fossi come loro. Noi nemmeno… Vaffà, a tutti quanti!";
			link.l1 = "Mary, aspetta! Maledizione...";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "Ce la siamo proprio meritata una vacanza, giusto? Pensi che riusciranno a reggere la vista di una signorina con un cappotto rosso? Immagina tutte le chiacchiere negli angoli… Qualcuno di sicuro sviene, sarebbe divertente, giusto?";
			link.l1 = "Mary, mia cara, questa non è proprio la festa dove si porta una signora... almeno non una signora come te. Beh, è un po’ complicato ma lascia che ti spieghi, giusto?";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "Wow, lascia stare. Dimmi la verità: non sono abbastanza per quei damerini impomatati. Una ragazza semplice, solo per divertirsi, eh? Hai vergogna a farti vedere con me in giro? Non vado bene per i tuoi ricevimenti eleganti, giusto, nobile monsieur Charles de Maure?";
			link.l1 = "No, per niente. Sei straordinario e non mi importa affatto dell’impressione che facciamo su chi ci circonda. Il governatore cerca ancora una volta di risolvere i suoi guai grazie a me. Sarò come un trofeo prezioso nella stanza, giusto? Un’ospite interessante per far colpo su quei nobilastri buoni a nulla.";
			link.l1.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "Quindi non ti vado bene, giusto? Capisco, i nobili stanno coi nobili, e la gente semplice serve solo per divertirsi un po'. Buona fortuna coi tuoi signorotti. Parleremo quando tornerai coi piedi per terra, giusto?";
			link.l1 = "Mary, aspetta! Maledizione...";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_7":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "Buona fortuna con i tuoi signorotti. Ti parlo quando torni sulla nostra umile terra, giusto?";
			link.l1 = "Mary oh, dai su!";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "Guarda un po’, giusto! Il nostro capitano smarrito tra l’alta società!";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "Sei sparito nel bordello per tutto il giorno e adesso in città tutti chiacchierano. Charles, dammi solo una buona ragione per cui dovrei parlare con te adesso invece di, che so, mostrarti il Narvalo su per la... pancia? Non te ne importa nulla di me, giusto?!";
			link.l1 = "Mary, ti spiegherò tutto, ma più tardi. Devo prepararmi e andare a duello. Se dovessi sopravvivere, sentiti pure libera di uccidermi. Nel frattempo, occupati tu della nostra nuova nave, giusto? L'ho vinta come premio a carte ieri notte.";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "Dimentica la nave, hai parlato di un duello, giusto? Qui la gente racconta un mare di fandonie che proprio non ascolto. Dicono che dovresti sfidare o il figlio del re o perfino il maledetto Papa in persona. Dimmi subito, che diavolo sta succedendo, giusto?!";
			link.l1 = "Quest’uomo è il figlio bastardo di un nobilastro parecchio potente, il Conte de Levi Vantadur. È stato lui a sfidarmi per primo, giusto? Devo vincere il duello senza ferirlo, altrimenti suo padre scatenerà l’inferno su di me.";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "Mentre io dovrei restarmene col culo in ammollo sulla tinozza che hai appena vinto tu? Sei impazzito, Charles, giusto?";
			link.l1 = "Temo che debba andare così. Il governatore mi ha dato un paio di ufficiali nobili come testimoni, così da evitare ogni malinteso in seguito. Non posso portare te o nessuno dei ragazzi con me, per l’integrità ufficiale del duello. È una faccenda troppo seria, mi dispiace, giusto?";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "Sai cosa farò adesso? Andrò su quella dannata nave e mi ubriacherò come si deve, giusto? Fai pure quello che ti pare, ma se quel nobile figlio di puttana non riesce ad ammazzarti, te lo giuro, lo farò io stessa!";
			link.l1 = "Mary, andrà tutto bene, fidati di me. Ora aspetta... Maledizione! Eccoci di nuovo, giusto?";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "Eccoti qui! Non ci hai mandato nemmeno una parola per tutto il giorno! Eravamo in pensiero, sai, dopo aver sentito certe chiacchiere al mercato. Dicono che hai scommesso navi e donne, e ti sei pure messo a duellare con un principe coronato, o addirittura con il Papa in persona! Che diavolo sta succedendo, giusto?";
			link.l1 = "È una faccenda complicata, Mary. Ci vorrà un po’ per spiegare tutto. Però sono riuscito a vincere una fregata. Dovrai occupartene tu mentre sistemo i conti col suo vecchio proprietario, giusto?";
			link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "Quindi avevano ragione sul duello, giusto? Chi sarebbe quel nobile bastardo pieno di sé? Perché te la stai prendendo con lui?";
			link.l1 = "Devo farlo. È una storia complicata, ma in breve: ho vinto la sua nave e la sua... signora. Mi ha accusato pubblicamente di barare e mi ha sfidato a duello. Quel bastardo è il figlio di un nobilastro assai influente, il Conte de Levi Vantadur. Dovrò stare ben attenta a non fargli troppo male, giusto?";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "Una donna? Capisco giocarsi una nave, ma... una donna, davvero? Quindi era vero ciò che si diceva in giro, giusto? Lo ammetti così, senza problemi?! Come se fossi... una delle tue ciurme di scemi, giusto?";
			link.l1 = "Maledizione, Mary, non è affatto come credi! Lui l'ha vinta dal governatore, io gliel'ho ripresa solo per liberarla, tutto qui. Non c'è altro dietro, lo giuro, giusto?";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "Beh, forse per voi nobili è normale, ma io non sono fatta così, giusto! Fa' quello che vuoi, dì quello che ti pare... vai pure a crepare per lei se ti va! Io me ne torno sulla maledetta nave che hai vinto e mi sbronzo. Credevo che fosse tutto vero e... che sarebbe durato per sempre. Credo di aver preteso troppo, giusto?";
			link.l1 = "Mary, non me ne frega un accidente di quella donna! Aspetta solo un attimo, ti prego... Maledizione! Eccoci di nuovo, giusto?";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "Charles, sei venuto per me, giusto! Lo sapevo, non ho mai avuto dubbi! Sono così felice di vederti!";
			link.l1 = "Anche io, Mary! Mi ha divorato dentro tutto questo tempo. Grazie al cielo che stai bene, giusto?";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "A proposito, che hai fatto di preciso per convincerli a lasciarmi andare così facilmente? Senza nemmeno una bella rissa o una sparatoria, giusto? Ah, e ho visto una dama stupenda sul ponte mentre mi trascinavano via. Che è successo, Charles?";
			}
			else
			{
				dialog.text = "Che hai fatto di preciso per farmi liberare così, senza nemmeno una rissa, senza sparare un colpo, giusto? Ho visto dei pavoni inglesi sul ponte quando mi portavano fuori. Che diavolo succedeva, Charles?";
			}
			link.l1 = "Tutto ciò che conta è che tu sia tornato da me. Ho mancato nei tuoi confronti, Mary. Mi dispiace davvero! Spero che troverai nel tuo cuore la forza di perdonarmi! Odio il modo in cui ci siamo lasciati l’ultima volta, giusto?";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "L’ho già fatto. Anche io mi dispiace, giusto? Se solo non avessi preso così a cuore le tue faccende con quella dama... Avrei messo una guardia come si deve quella notte. Non ci avrebbero mai fregato così facilmente! Che sciocca che sono stata!";
			link.l1 = "Il passato è passato. Ti amo e non ti lascerò mai più così, giusto? Te lo prometto!";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "Sapevo che non mi avresti mai abbandonata, giusto? Scusami se ho mai dubitato di te, Charles! Forse è meglio che io non sappia esattamente cosa hai fatto, eh? L’importante è che siamo di nuovo insieme, giusto?";
			link.l1 = "Non ho segreti con te. Ti racconterò tutto, giusto?";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Che storia... dubito che qualcun altro ci crederebbe, giusto! L’ho capito subito! Sapevo che la tua notte ‘giocosa’ nascondeva qualcosa! Tutti quei pavoni nobili... bestie senza cuore! Almeno su di te non mi sbagliavo, sapevo che eri diverso, giusto!";
				link.l1 = "Sono abbastanza sicura che là fuori molti pensino che io sia molto peggio. Una vera bestia da favola, giusto?";
			}
			else
			{
				dialog.text = "Che storia... dubito che qualcun altro ci crederebbe, giusto! L'ho capito fin dall'inizio! Sapevo che la tua 'notte giocosa' era una faccenda losca! Politica, spie, con-giu-ra-zioni. E tu di nuovo ci hai salvati tutti, giusto! Il mio eroe!";
				link.l1 = "Non ne sono tanto sicura. C’è il rischio che tra qualche settimana scoppierà la guerra con l’Inghilterra. Però ho fatto quel che dovevo, Mary. Sei tutto per me, giusto?";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Non m’importa cosa pensa la gente, se è così, sarai il mio mostro, Charles! Gli altri possono piagnucolare o venire a vedersela con me! Ricorda che sarò sempre al tuo fianco, giusto?";
			}
			else
			{
				dialog.text = "Lo so, Charles. L’ho sempre saputo, ma è così dolce sentirtelo dire. Sappi questo: resterò sempre al tuo fianco, giusto?";
			}
			link.l1 = "Non ne ho mai dubitato, Mary. Andiamo, i ragazzi sono in pensiero. È ora di issare le vele e filare via da qui al diavolo. Sei di nuovo al mio fianco, e l’orizzonte non scapperà da solo, giusto?";
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			dialog.text = "Aye aye, Capitano!";
			link.l1 = "";
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
			GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;
		
		case "GoldenGirl_32":
			dialog.text = "Charles, sei davvero tu?! Avevo quasi perso ogni speranza, giusto! Dio, quanto mi sei mancato! Ti prego, ti prego, perdonami, giusto?";
			link.l1 = "No, perdonami, non l’avevo previsto… Grazie al cielo che sei arrivata, Mary! Sono davvero felice, giusto?";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "A proposito di perdono – per dirla tutta, sto decidendo se spararti o abbracciarti. Faresti meglio a dirmi che diavolo sta succedendo, giusto?";
			link.l1 = "Ti amo, Mary. Era tutto ciò che volevo dirti, giusto?";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "Già, come se fosse servito a qualcosa, ma… Dannazione, anch’io Charles. Ti amo anch’io, giusto? Dio, finalmente siamo insieme!";
			link.l1 = "E non voglio sprecare il tempo che abbiamo parlando di sciocchezze. Vieni con me e non oserò lasciarti stanotte, giusto? Anche se il cielo dovesse crollare su questa lurida città, io non ti lascerò mai più. Mai, giusto?";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "Pare sia meglio che io non sappia davvero cosa hai combinato, giusto? Siamo di nuovo insieme e solo questo conta.";
			link.l1 = "Non ho segreti con te. Ti racconterò tutto, giusto?";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "Mi stai dicendo che... questa marchesa ti ha aiutato a riportarmi indietro? E avete quasi scatenato una guerra tra Inghilterra e Francia, giusto? Non fraintendermi – è tutto così romantico e tutto il resto, ma adesso che succederà, giusto?";
			link.l1 = "Non ne ho la minima idea, Mary. Siamo di nuovo insieme, il resto non conta. Se quelli al potere non riusciranno a nascondere tutto sotto il tappeto... beh, sono pronto a fare il mio dovere davanti alla Corona, giusto?";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "E quella tua marchesa? Anche lei l’hai riportata indietro? Il portoghese ne parlava un gran bene. Mi ha assicurato che hai resistito ai suoi assalti come la Bastiglia. Voglio credergli, giusto? Ma devo sentirlo dalla tua bocca!";
			link.l1 = "Non c’è proprio nulla tra me e madame Botot, Mary. L’ho aiutata, lei ha fatto lo stesso, tutto qui. A proposito di Bartholomew, sai dov’è finito, giusto?";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "È sparito, giusto? Ha mollato le vele subito dopo avermi portata qui. In quel maledetto bordello non ci metterei mai piede, così mi ha affittato una stanza, pagata in anticipo per un paio di settimane, e se n’è andato. Ah, quasi dimenticavo, giusto! Ho una lettera per te!";
			link.l1 = "Una lettera? Da Bartolomeo il Portoghese? Questa è nuova. Non mi piace dove si sta andando a parare, giusto?";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "Vai pure, leggilo. Io vado a vedere i ragazzi. Probabilmente si sono preoccupati. Sono arrivati tutti sani e salvi? Spero non ti dispiaccia se ci facciamo un bicchiere o due di sotto. Cerca di non cacciarti di nuovo nei guai, giusto?";
			link.l1 = "Certo, ma fa’ attenzione con loro, Mary. Preferirei passare la serata con te, invece di dover trascinare corpi sbronzi fino alla nave. Giusto? Non riesco ancora a credere di averti ritrovata!";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
			GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "La spiaggia, tu, io e del buon vino – Charles, è così romantico! Dovremmo farlo più spesso, giusto?";
			link.l1 = "Felice che ti piaccia. Credo che d’ora in poi ci ritaglieremo più tempo l’uno per l’altra per momenti così, giusto?";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "Di che stai cianciando? È successo qualcosa alla nave, eh? Perché sei in ginocchio, amore mio, giusto?";
			link.l1 = "Perché ti amo, Mary. Lo sai tu, lo so io, lo sanno tutti. Così, qui e ora, davanti al mare e al cielo, ti chiedo, Mary Casper – concedimi l’onore di starti accanto, davanti agli uomini e a Dio, per tutti i giorni che ci saranno concessi dall’alto. Io, Charles de Maure, chevalier de Monper, ti domando – vuoi diventare mia moglie, giusto?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore36")
			{
				dialog.text = "Ho sognato di sentirlo, giusto! Io... sai già la mia risposta Charles... oh, scusa!";
				link.l1 = "Lascia stare, è solo vino e non ho mai amato davvero questa camicia, giusto?";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "Charles, certo che sì! Sì, sì, mille volte sì!!! Tu... questo posto... nulla potrebbe rendermi più felice!!! Oh dio, sono così felice, giusto?";
				link.l1 = "Mi hai resa felice, Mary. E voglio brindare a te, mio sole ardente dei Caraibi, giusto?";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestCheckDelay("Mary_LoveSex", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "Bevo alla tua salute, mio capitano e futuro marito, giusto! Sei la cosa migliore che mi sia mai capitata!";
			link.l1 = "Ma questo è solo l’inizio – a noi! E al nostro futuro insieme! Abbiamo un mare d’avventure davanti, giusto?";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "Alla tua, mio capitano e futuro marito, giusto? Sei la cosa migliore che mi sia mai capitata!";
			link.l1 = "Ma questo è solo l’inizio — a noi! E al nostro futuro insieme! Davanti a noi c’è un mare d’avventure, giusto?";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Mary_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "Charles, l’abate Benoit è di nuovo a Martinica, quindi possiamo andare avanti, giusto? Ma io un vestito non lo metto, nemmeno per una messa: spero che non ti offenda, giusto?";
			link.l1 = "Mary, ti adoro in qualsiasi abito e... beh, lo sai. Puoi indossare quello che ti pare, a chi storce il naso ci penso io! Volevo solo consultarmi con te riguardo agli invitati e alla cerimonia, giusto?";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			if (LongHappy_CheckSaga())
			{
				dialog.text = "Sai, la maggior parte di quelli che davvero saprebbe gioire per la nostra felicità non verrà nemmeno fatta entrare in questa città, figurarsi nella chiesa, giusto? Quindi – sposiamoci qui con tutta la gente importante, come si conviene, e poi salpiamo verso Isla Tessoro per festeggiare come si deve con gli amici veri! Che ne dici, giusto?";
				link.l1 = "Grande idea! Allora facciamolo, giusto? Parlerò con l’abate Benoit, ma dobbiamo anche spedire gli inviti e tutto il resto...";
				link.l1.go = "LongHappy_9";
			}
			else // Сага провалена по времени или утоплен Центурион
			{
				dialog.text = "Sai, non ho molti amici oltre ai nostri della ciurma. Quindi invita chi pensi sia giusto, e io sarò felice comunque, giusto!";
				link.l1 = "Come dici tu, tesoro. Parlerò con l’Abate Benoit e metterò tutto in moto: ti meriti davvero la cerimonia più magnifica, giusto?";
				link.l1.go = "LongHappy_9a";
			}
		break;
		
		case "LongHappy_9":
			dialog.text = "Non preoccuparti, da brava moglie mi occuperò io di parte dei preparativi, giusto? Scriverò ai nostri amici e organizzerò tutto, ma prima dimmi: come immagini questo matrimonio?";
			link.l1 = "Il mio sogno sei tu, io e i nostri amici più fidati. Dopo tutte queste facce ufficiali qui a Martinica, avremo voglia di un po’ di sincerità, giusto?";
			link.l1.go = "LongHappy_10";
			link.l2 = "Dobbiamo ricordare questo giorno. Chiama tutti! Nessuno sarà lasciato fuori, giusto?";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_9a":
			dialog.text = "Con te, basterebbe una cerimonia col cappellano di bordo sul cassero, al tramonto sul mare, giusto? Ma se è questo che vuoi – allora festeggeremo! Charles ... ora mi viene da piangere, abbracciami, giusto ...";
			link.l1 = "Mary...";
			link.l1.go = "LongHappy_9b";
		break;
		
		case "LongHappy_9b":
			dialog.text = "Ecco fatto, sono tranquilla, giusto? Scusa, è tutto così insolito. Ma Charles, da brava moglie, prenderò io in mano l’organizzazione. Dobbiamo anche preparare una festa per i ragazzi, giusto? Ma dubito che tutta la ciurma ci stia in chiesa. Mi metto d’accordo con la taverna, ma serviranno bottiglie e monete – sai bene quanto ai marinai piaccia far baldoria, giusto?";
			link.l1 = "Giusto, ecco cosa faremo. Che cosa devo preparare, giusto?";
			link.l1.go = "LongHappy_9c";
		break;
		
		case "LongHappy_9c":
			pchar.questTemp.LongHappy.MarryMoney = 100000;
			pchar.questTemp.LongHappy.MarryRum = 100;
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				pchar.questTemp.LongHappy.MarryMoney = 200000;
				pchar.questTemp.LongHappy.MarryRum = 150;
			}
			if (GetCompanionQuantity(pchar) > 1)
			{
				pchar.questTemp.LongHappy.MarryMoney = 300000;
				pchar.questTemp.LongHappy.MarryRum = 200;
			}
			dialog.text = "Penso, giusto?"+sti(pchar.questTemp.LongHappy.MarryMoney)+" pesos basteranno, giusto. "+sti(pchar.questTemp.LongHappy.MarryRum)+" barili di rum, non c’è nulla di peggio che restare a secco, giusto? Appena recuperi tutto quello che ci serve, vieni in taverna, al resto penso io.";
			link.l1 = "Va bene, tesoro, lo faccio, giusto?";
			link.l1.go = "LongHappy_9d";
		break;
		
		case "LongHappy_9d":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10_1");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "Capito, facciamolo. Però dovremo passare da Sharptown e sistemare tutto quanto. Direi che cinquanta barili di rum e una ventina di barili di vino basteranno, giusto? Ma, per sicurezza, avrò bisogno di trecentomila pesos.";
			link.l1 = "È tanto, ma l’occasione lo merita. Raccatterò i soldi, non ti preoccupare. Ora passo dall’abate e poi vado a Sharptown, giusto?";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "Perfetto, raduniamo tutti, giusto? Però dobbiamo passare da Sharptown e organizzarci per bene – ci servirà un galeone carico di alcol! Credo che cento botti di rum e cinquanta di vino basteranno. Ma, per sicurezza, aggiungo cinquecentomila pesos. Se la festa finisce in fretta, che razza di festa sarebbe, giusto?";
			link.l1 = "Sì, i nostri amici non devono crepare di sete – ci penso io a tutto, giusto? Ora passo dall’abate e poi vado a Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "È tutto pronto, Charles, giusto? Mi occuperò io di far scaricare il rum, poi andrò alla taverna del posto, incontrerò il barone e consegnerò gli inviti. Tu aspetta qui, giusto?";
			link.l1 = "Sei tu al timone, caro! Allora io me ne andrò a spassarmela da qualche parte. Non avrei mai pensato che preparare una spedizione nella giungla del Maine fosse più semplice che organizzare un matrimonio, giusto?";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Several hours have passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "Abbiamo finito qui, Charles, giusto? Ho sistemato tutto, credimi – sarà fantastico! Una cosa è un po’ imbarazzante: la taverna del posto è bruciata durante una festa la settimana scorsa. Ma ormai l’hanno quasi ricostruita, più grande e migliore di prima, giusto? Dovremmo starci tutti.";
			link.l1 = "Spero proprio che questa nave non la bruciamo, giusto? Mi piaceva davvero il ‘Vecchio Picchio’! Comunque, abbiamo ancora un sacco da fare. È ora di salpare. E sì, Mary – sei la migliore, lo sai, giusto?";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "Eccoci qua, eh? Gli ospiti sono arrivati, la chiesa è pronta. So che siamo più uniti di tanti sposi e queste sono solo poche parole importanti in una bella sala, ma maledizione – in quella città antica e selvaggia ero meno agitata, giusto?";
			link.l1 = "È del tutto normale, amore mio, davvero normale. Anche io sono agitata. Penso che padre Benoit stia già aspettando, vado da lui per capire quando inizierà la cerimonia, giusto?";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "Bene, farò un giro per la città, vuoi prepararti, giusto? Charles, capisci che ormai non si torna più indietro?";
			link.l1 = "Mary, cara, da quando ci siamo incontrati non c’è più stato ritorno per me. Ho aspettato questo giorno con tutto il cuore. Non preoccuparti, andrà tutto bene, giusto?";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Mary");
		break;
		
		case "LongHappy_20":
			dialog.text = "Giusto?";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "Giusto?";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "Giusto?";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "Io, Charles Henry de Maure, cavaliere di Monper, prendo te, Mary Casper, come mia sposa, per amarti e onorarti da oggi e per sempre, nella gioia e nel dolore, nella ricchezza e nella povertà, in salute e in malattia, finché morte non ci separi. Secondo la Santa Legge di Dio, davanti a Lui, faccio questo giuramento.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "Io, Mary Casper, prendo te, Charles de Maure, come mio sposo, per amarti e onorarti da oggi e per sempre, nella gioia e nel dolore, nella ricchezza e nella povertà, in salute e in malattia, finché morte non ci separi. Davanti a Dio e secondo la Sua santa legge, io faccio questo giuramento, giusto?";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "Amen.";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "È incredibile, giusto! Io... io sto piangendo, perdonami Charles, ora... mi si è arrossato pure il naso, giusto?";
			link.l1 = "Mary de Maure, mia moglie, oggi sei splendida come ogni altro giorno, giusto?";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) dialog.text = "Grazie, Charles, grazie... Tutto è così solenne e meraviglioso! È il giorno più bello della mia vita, giusto!!! Guarda quanto sono felici tutti! Ma ora tocca a te andare tra gli invitati e ricevere le congratulazioni! Quando hai finito – torna da me – andiamo a vedere come stanno i ragazzi in taverna.";
			else dialog.text = "Grazie, Charles, grazie... Tutto è così solenne e meraviglioso! È il giorno più bello della mia vita, giusto!!! Guarda quanto sono felici tutti! Ma ora devi andare in giro tra gli ospiti e accettare le congratulazioni! Quando hai finito, torna qui, ci aspettano a Sharptown.";
			link.l1 = "Lo faccio subito, tesoro. Un bacio e me ne vado, giusto?";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "Charles, amore mio, hai già parlato con gli ospiti, giusto?";
			link.l1 = "Non ancora, abbi pazienza, tesoro, torno presto, giusto?";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "Sì, non ho mai sentito tanti complimenti tutti insieme. E sai una cosa? La maggior parte li diceva sul serio, giusto?";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) 
			{
				dialog.text = "Sì, sì! Anche a me hanno detto un sacco di cose piacevoli! Non tutti, ovvio, qualcuno resta proprio stupito dal mio vestito, giusto? Ma sono così felice che metà delle chiacchiere mi scivolano via. E poi, tutti sono così simpatici. Charles, i ragazzi in taverna ci stanno già aspettando – dobbiamo andare da loro. Saranno contenti di fare i complimenti al loro capitano, giusto?";
				link.l1 = "Andiamo subito, giusto? Ma vorrei proprio finire questa giornata in un posto più romantico della stanza della taverna del porto. Spero che non ti dispiaccia passare questa notte nella nostra cabina, moglie mia, giusto? Tanto ormai sulla nave non c’è guardia...";
			}
			else
			{
				dialog.text = "Sì, sì! Mi hanno detto anche un sacco di belle cose! Non tutti, ovvio, qualcuno resta proprio a bocca aperta per il mio abbigliamento, giusto? Ma sono così felice che metà delle parole mi scivolano addosso. E poi, in generale, sono tutti così simpatici. Charles! Ma ci aspettano a Sharptown, quando si salpa?";
				link.l1 = "Proprio adesso. Non possiamo lasciare che i nostri ospiti si scolino tutte le provviste! Spero, mia cara, che non ti dispiaccia passare questa notte nella nostra cabina, giusto?";
			}
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "Anche in una capanna su un’isola deserta, ma solo insieme a te, giusto?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "Lo so. Ti amo anch’io. Andiamo, prima che quei mascalzoni si scolino tutto il nostro rum e diano fuoco alla taverna, giusto?";
			else link.l1 = "Certo che sì. Ti amo anch'io. Allora... salpiamo, giusto?";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "Oh mio caro, sono così felice! Oggi è una giornata meravigliosa, giusto?";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "Strappa quella lurida testa dal suo collo, Charles!";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "Sto bene, giusto? E Nathan, come sta, è ancora vivo?";
			link.l1 = "Così tanto sangue... Dannie, sta respirando? Lo vedo che respira, giusto?";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "Più svelto, caro, non perdere tempo, giusto?";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "Abbiamo vinto, giusto? Perdonami, sono in ritardo. Siamo rimasti bloccati al piano di sopra, c’erano una dozzina di quei bastardi, quindi avevo le mani un po’ occupate, giusto?";
			link.l1 = "Va tutto bene, me la sono cavata da sola. Sono felice di aver chiuso quella faccenda con Jacques... finalmente. Ha avuto quello che si meritava, giusto?";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "Allora finisci qui e torna a Sharptown! Dobbiamo vedere come sta Nathan, giusto? Ha rischiato la vita per noi!";
			link.l1 = "Hai ragione, amore mio. Vai pure, ti seguo subito, giusto?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "A proposito, caro, abbiamo trovato Marcus, giusto! Era nella stiva, legato e privo di sensi.";
			link.l1 = "È ancora vivo, giusto?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "È ferito, ma si rimetterà. Non puoi spezzare il nostro barone, giusto! Si è appena svegliato e già scalpita per la battaglia.";
			link.l1 = "Ecco il nostro vecchio Marcus! Allora, finisci qui e poi dritto alla riva, giusto?";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Mi dispiace tanto, Charles, giusto, io... sono uscita a fare due passi. Ho visto che eri tornato, ho sentito che tutti festeggiavano la vittoria, però io... Ma cosa c’è che non va in me, giusto!";
				link.l1 = "Andrà tutto bene, amore, andrà tutto bene. Anche io sono triste. Ma abbiamo vinto, e Jacques Barbazon ha pagato per tutto quello che ha fatto, giusto?";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "Mi sento così male per Gino, Charles, giusto? Quando l’ho scoperto, non ci credevo! Come stai?";
					link.l1 = "Nemmeno io ci credo... è venuto fuori tutto così scemo, non me l’ero immaginata proprio così, questa giornata, giusto?";
				}
				else
				{
					dialog.text = "Abbiamo vinto di nuovo, giusto? Mio marito è una tempesta per quei baroni ribelli della Fratellanza della Costa! Gli amici sono vivi e i nemici sono morti – un dono glorioso, giusto?";
					link.l1 = "Sì, che baldoria, ma ce l’abbiamo fatta, amore mio. Ce l’abbiamo fatta, giusto?";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "Non ti reggi nemmeno in piedi, giusto? Dai, Dannie ci ha trovato una casa qui in periferia, non ho voglia di tornare ora sulla nave. Ci sediamo e beviamo ai nostri amici caduti. Tutto questo è troppo da affrontare a mente lucida, giusto.";
			link.l1 = "Sì, Mary, andiamo, giusto?";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Mi sento così male per Gino, Charles, giusto? Quando l’ho scoperto, non potevo crederci! Come stai?";
				link.l1 = "Non ci posso credere nemmeno io... è andata proprio da scemi, non pensavo che questa giornata sarebbe finita così, giusto?";
			}
			else
			{
				dialog.text = "Scusa il ritardo, caro, giusto? Sono andata a fare due passi, poi ti ho visto avvicinarti e sono corsa più veloce che potevo! Dannielle mi ha fatto uscire quando Gino ha detto ‘non c’è più pericolo’, giusto? Sono così felice che ora vada tutto bene!";
				link.l1 = "Anche io, tesoro. E abbiamo vinto. Barbazon è crepato, i baroni stanno raccattando quello che resta delle loro ciurme. La battaglia è finita, giusto?";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "Charles, ti vedo che a malapena stai in piedi, ma nessuno riesce a trovare Tichingitu, giusto?";
			link.l1 = "Jan mi ha dato una dritta... Mi pare che il nostro burbero mascalzone sia andato a far baldoria. Facciamo due passi fino alla Cala di Sabo-Matila, giusto? Qualcuno l’ha visto dirigersi proprio da quelle parti.";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "Ecco il nostro burbero di casa, giusto? Su, Dannie ci ha trovato una casa qui in periferia – ormai vai avanti come un sonnambulo, Charles, giusto?";
			link.l1 = "Eccolo ... rapiscimi, mia bella squaw. E domani facciamo finta che sia stato tutto un brutto sogno, giusto?";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_57":
			dialog.text = "Non fraintendermi, marito mio, in chiesa era tutto sfarzoso, ma qui l’atmosfera è decisamente più calorosa, giusto? Beh, ecco tutto, Charles, ora che tutti i guai sono alle spalle possiamo rilassarci.";
			link.l1 = "Beh, non è proprio 'tutto', mia moglie – la nostra vita insieme continua! Si può dire che in realtà oggi ha appena avuto inizio. Allora, andiamo, beviamo qualcosa con i nostri ragazzi, e poi – beh, ti ricordi: la cabina, il vino, e noi due... giusto?";
			link.l1.go = "LongHappy_58";
		break;
		
		case "LongHappy_58":
			DialogExit(); // телепорт в каюту
			DoQuestReloadToLocation("My_Cabin", "rld", "loc1", "LongHappy_InSPcabin");
		break;
		
		case "LongHappy_59":
			dialog.text = "Mio marito... Suona così dolce, giusto! Ora sei mio, per sempre!";
			link.l1 = "È già da tanto che sono tua, e lo sarò per sempre, amore mio... giusto?";
			link.l1.go = "LongHappy_60";
		break;
		
		case "LongHappy_60":
			DialogExit();
			DoQuestCheckDelay("Mary_LoveSex", 1.0);
			npchar.dialog.currentnode = "LongHappy_61";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_61":
			dialog.text = "Sono così felice, Charles! E adesso dobbiamo rimetterci in marcia, giusto?";
			link.l1 = "Certo, tesoro! Fianco a fianco, insieme e per sempre, giusto?";
			link.l1.go = "LongHappy_62";
		break;
		
		case "LongHappy_62":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Mary_officer";
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload1", "LongHappy_InSPComplete");
		break;
		
		// Jason Исла Мона
		case "IslaMona":
			dialog.text = "Temo che questa pestilenza stia mettendo a dura prova le tue ragazze, Rodrigo. Tienile occupate a cucire o giù di lì, giusto?";
			link.l1 = "Questa conversazione non porta proprio da nessuna parte, giusto? Abbiamo già deciso che domani andremo in chiesa. A pregare... naturalmente.";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Mary_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "Sono fiera di te, amore mio, giusto?";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "Ebbene, Charles...";
			link.l1 = "Che ti passa per la testa stavolta, Mary, giusto?";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "(ride) Il fatto è che io e Alan volevamo fare sull’isola proprio quello che hai combinato tu qui, giusto?";
			link.l1 = "Il tuo... Alan, giusto?";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "Sì, era davvero un gran sognatore, tu e lui sareste stati ottimi compari se fosse ancora in vita, giusto?";
			link.l1 = "Beh, almeno su una cosa i nostri gusti si sono incrociati, giusto?";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "Cosa? Ah-ah-ah! Smettila Charles!\nComunque sia, è incredibile, abbiamo portato così tanta gioia a questa gente, giusto?";
			link.l1 = "Abbiamo dato loro una possibilità di felicità, ma tutto il resto se lo sono guadagnato da soli. Allora, a cosa pensi, giusto?";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			dialog.text = "Vieni a cercarmi più tardi e scoprirai tutto, giusto?";
			link.l1 = "Eccome se lo farò, giusto?";
			link.l1.go = "IslaMona_9";
		break;
		
		case "IslaMona_9":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestCheckDelay("Mary_LoveSex", 2.0);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "tonzag_jailed":
			dialog.text = "Mi piace il buio e gli spazi stretti. Mi fanno sentire tranquilla. Finalmente posso raccogliere i miei pensieri, giusto? È come se tutte le preoccupazioni e i guai... svanissero, giusto! Mi manca davvero questa sensazione...";
			link.l1 = "Dovresti farti vedere da un medico, giusto?";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "Giusto? È come se fossi di nuovo sulla 'Fucina di Cerere'.";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;

		case "tonzag_jailed_1":
			dialog.text = "...Peccato che non sia sola. Nel silenzio, nell’oscurità, e nella solitudine, giusto? Quello sì che sarebbe perfetto.";
			link.l1 = "Continua così, Mary Casper.";
			link.l1.go = "exit";
		break;

		case "tonzag_jailed_2":
			dialog.text = "Una volta un granchio mi è finito nel letto – l’ho fatto a pezzi e me lo sono mangiato. Giusto?";
			link.l1 = "Continua così, Mary Casper.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "Maledetto mascalzone mascherato! Ahi! Aiutami, caro – dobbiamo sfondare queste sbarre, giusto?";
			link.l1 = "Zitto! Sto cercando di capire che fare, giusto?";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "Tesoro, questi diavoli mascherati sono dappertutto! Hanno sfondato la chiglia e ora si infilano dentro come quei dannati granchi! Dobbiamo farli fuori tutti, giusto?";
			link.l1 = "Mary, stay here, find the senior officer, and take command! Take the ship out of the battle; we won't withstand another boarding!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "E dove pensi di andare? Non ho alcuna intenzione di lasciarti scappare, giusto?";
			link.l1 = "Devo aiutare Hercule e tutta la nostra ciurma! Fidati di me, giusto?";
			link.l1.go = "tonzag_after_boarding_2";
		break;

		case "tonzag_after_boarding_2":
			dialog.text = "Aye aye, tesoro!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Vittoria, giusto? Vieni qui, caro! Ti voglio tutta per me, anche solo per un'ora o due!";
			link.l1 = "Uh...";
			link.l1.go = "tonzag_after_victory_1";
			link.l2 = "Andiamo, giusto?";
			link.l2.go = "tonzag_after_victory_1";
		break;

		case "tonzag_after_victory_1":
			dialog.text = "Ehi, Hercule! Che piacere vederti, vecchia barba grigia, giusto?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog");
		break;

		case "tonzag_after_victory_2":
			dialog.text = "";
			link.l1 = "Mary, Mary, aspetta! Ho bisogno del tuo resoconto, giusto?";
			link.l1.go = "tonzag_after_victory_3";
		break;

		case "tonzag_after_victory_3":
			dialog.text = "Eh? Beh, abbiamo vinto, giusto? Quella maledetta nave è scappata. Ho spaccato il cranio a uno di quei bastardi in due!\nUff, maledetti bottoni!";
			link.l1 = "Oh, Mary...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "Oh Dio, non guardarmi, caro! Sto per... phew, giusto?";
			link.l1 = "Forza, ragazza. Sono qui, giusto?";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
		break;

		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Mary_officer":
			// если шлялся по борделям - устроит небольшой скандал 
			if (sti(pchar.GenQuest.BrothelCount) >= 3 && LAi_grp_playeralarm == 0)
			{
				dialog.Text = ""+pchar.name+"! Devo parlarti, giusto! Sul serio!";
				Link.l1 = "Che succede, Mary? C’è qualche grana, giusto?";
				Link.l1.go = "brothel";
				break;
			}
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("Ascolto, mio caro capitano, giusto?","Giusto? "+pchar.name+", sono tutta orecchi, giusto?","Hai qualche incarico per me, giusto?"+pchar.name+"?");
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Mary, sto per visitare la vecchia città indiana di Tayasal. Non ti mentirò: questo viaggio è davvero rischioso e, in più, prevede pure una specie di teletrasporto attraverso l’idolo di cui ti ho parlato. Mi seguirai, giusto?";
				Link.l4.go = "tieyasal";
			}
			////////////////////////казначей///////////////////////////////////////////////////////////
			// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Mary, dammi il resoconto completo della nave, giusto?";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Voglio che tu compri certe mercanzie ogni volta che attracchiamo, giusto?";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Mary, ho bisogno del tuo consiglio, giusto?";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Mary, ho un incarico per te...";
            Link.l1.go = "stay_follow";
			if (pchar.location == Get_My_Cabin() && !CheckAttribute(npchar, "quest.daily_sex"))
			{
				Link.l2 = RandPhraseSimple("Caro, ti voglio proprio adesso. Sei d’accordo, giusto?","Mary, che ne dici se... restiamo un po' insieme? Solo noi due, giusto?");
				Link.l2.go = "cabin_sex";
			}
			if (rLoc.type == "tavern" && !CheckAttribute(npchar, "quest.daily_sex") && sti(pchar.money) >= 10)
			{
				Link.l2 = RandPhraseSimple("Mary, affittiamo una stanza e restiamo insieme, giusto?","Amore, vorrei restare un po’ con te da soli… che ne dici se affittiamo una stanza e dimentichiamo tutto il resto per qualche ora, giusto?");
				Link.l2.go = "room_sex";
			}
			link.l9 = "Non è niente finora, Mary, giusto?";
			link.l9.go = "exit";
			NextDiag.TempNode = "Mary_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Charles, è proprio una bellezza, giusto? Abbiamo sistemato quel buchetto sotto la linea di galleggiamento e asciugato le vele. Che ti aspettavi? Non guardarmi così, non ho mai studiato per fare il cassiere di bordo, giusto?";
			Link.l1 = "Scusa, Mary, davvero non ci ho pensato bene, giusto?";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Charles, ma va tutto bene! Ho già il mio guardaroba e la mia lama. Però grazie per esserti preoccupato, sei proprio gentile, giusto?";
			link.l1 = "Ma io nemmeno... Bah, lascia perdere, caro, va tutto bene tra noi, giusto?";
			link.l1.go = "exit";
		break;

		case "stay_follow":
            dialog.Text = "Ordini, giusto?";
            Link.l1 = "Resta qui, giusto?";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Seguimi e stai al passo, giusto?";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Mary, cambia munizioni per le armi da fuoco, giusto?";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Scegliendo il tipo di munizione:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
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
            dialog.Text = "Subito, mio capitano!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Subito, capitano mio!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

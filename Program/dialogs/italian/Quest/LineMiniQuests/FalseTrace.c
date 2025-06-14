void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Errore. Fatecelo sapere.";
			link.l1 = "Certo!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "FalseTrace":
			DelMapQuestMarkCity(pchar.questTemp.FalseTrace.StartCity);
			dialog.text = "Buon pomeriggio, capitano... ehm... kha-hahrm! Maledette miniere... Lasci che mi presenti. Adam Rayner. Sono un uomo semplice e non amo i giri di parole, quindi vado dritto al sodo. Vuole fare un bel po' di soldi? Le propongo un affare che da soli non potremmo mai gestire.";
			link.l1 = "Heh! Bei soldi? Interessante. Ti ascolto, Adam.";
			link.l1.go = "FalseTrace_1";
			link.l2 = "Sai, mi dispiace, ma non sembri degno di fiducia. Quindi non avrò nulla a che fare con te.";
			link.l2.go = "FalseTrace_exit";
		break;
		
		case "FalseTrace_exit":
			dialog.text = "Affidabile? Ah-ah! Non si giudica un uomo dalla faccia. Beh, lascia stare. Hai appena perso una ghiotta occasione per far soldi facili e veloci. Troverò qualcun altro più accomodante...";
			link.l1 = "La nostra chiacchierata è finita, signore. Addio!";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_exit_1":
			DialogExit();
			DelLandQuestMark(npchar);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "questTemp.FalseTrace");
		break;
		
		case "FalseTrace_1":
			//выбираем целевой пункт
			switch (hrand(2))
			{
				case 0: 
					pchar.questTemp.FalseTrace.DayQty = 18;
					pchar.questTemp.FalseTrace.TargetCity = "Beliz";
					pchar.questTemp.FalseTrace.TargetShore = "Shore8";
				break;
				case 1: 
					pchar.questTemp.FalseTrace.DayQty = 22;
					pchar.questTemp.FalseTrace.TargetCity = "Marigo";
					pchar.questTemp.FalseTrace.TargetShore = "Shore41";
				break;
				case 2: 
					pchar.questTemp.FalseTrace.DayQty = 20;
					pchar.questTemp.FalseTrace.TargetCity = "Santodomingo";
					pchar.questTemp.FalseTrace.TargetShore = "Mayak8";
				break;
			}
			pchar.questTemp.FalseTrace.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.FalseTrace.Mation = sti(npchar.nation);
			dialog.text = "Kha! Un piacere fare affari con una mente svelta come la vostra, Capitano. Allora, il lavoro è semplice: c’è un fluyt carico di una discreta quantità d’argento, e presto salperà da uno dei porti locali. Una sola nave, nessuna scorta. Sciocchi, vero? K-kha\n Facile come bere un bicchier d’acqua. Io vi dico dove e quando, voi vi prendete il bottino e io la mia parte.";
			link.l1 = "E naturalmente, vuoi riceverlo in monete sonanti proprio adesso?";
			link.l1.go = "FalseTrace_2";
		break;
		
		case "FalseTrace_2":
			dialog.text = "Sembro forse un miserabile furfante, capitano? Macché. Parteciperò anch’io a questa razzia, e la faremo insieme. Non resterò in stiva durante la mischia, anzi – ti chiedo di mettermi tra gli abbordatori come tuo ufficiale, solo per stavolta, s’intende.\nConosco il mestiere, so come si pugnala e si spara alla gente. Quindi rischierò la pellaccia proprio come te... khe... kha! Mi pagherai la mia parte dopo che avremo preso il flauto.";
			link.l1 = "Che parte del bottino rivendichi per te stesso?";
			link.l1.go = "FalseTrace_3";
		break;
		
		case "FalseTrace_3":
			dialog.text = "Non sono un uomo avido, capitano. La mia parte è tutto ciò che può entrare nella stiva della mia vecchia lancia, e questo fa circa 200 casse d’argento. Da quello che so, sul fluyt ce ne saranno non meno di 2000, dunque prendo il decimo. Mi pare giusto, no?";
			link.l1 = "Un decimo del bottino solo per qualche dritta? Queste notizie le strappo ai vecchi ubriaconi per un bicchiere di rum nella taverna del porto. No, non facciamo affari insieme, compare!";
			link.l1.go = "FalseTrace_4";
			link.l2 = "Hm. Credo che tu abbia ragione. Accetto la tua offerta, Adam. Benvenuto a bordo. Ora parliamo delle tue informazioni: da dove, verso dove, quando e il nome del vascello?";
			link.l2.go = "FalseTrace_5";
		break;
		
		case "FalseTrace_4":
			dialog.text = "Che taccagno che sei, Capitano! In tal caso non avrai che merda! Addio!";
			link.l1 = "Buona fortuna! Trova un altro babbeo per i tuoi loschi traffici!";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_5":
			dialog.text = "Il nome del fluyt è il "+pchar.questTemp.FalseTrace.ShipName+", ella salpa da Cartagena e prende il largo "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+"Non abbiamo molto tempo, però. Due settimane, tre al massimo. Se non la troviamo entro tre settimane, sarà finita.";
			link.l1 = "Non perdiamo tempo, allora! L’avventura ci chiama!";
			link.l1.go = "FalseTrace_6";
		break;
		
		case "FalseTrace_6":
			DialogExit();
			NextDiag.CurrentNode = "FalseTrace_officer";
			DelLandQuestMark(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			AddQuestRecord("FalseTrace", "1");
			AddQuestUserData("FalseTrace", "sCity1", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen"));
			AddQuestUserData("FalseTrace", "sCity2", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity));
			AddQuestUserData("FalseTrace", "sShip", pchar.questTemp.FalseTrace.ShipName);
			//установим таймер на генерацию энкаунтера
			pchar.quest.False_Trace_2.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.False_Trace_2.function = "CreateFalseTraceGaleonOnMap";
			SetFunctionTimerCondition("FalseTraceGaleonOver", 0, 0, sti(pchar.questTemp.FalseTrace.DayQty)+2, false);//таймер
		break;
		
		case "FalseTrace_officer":
			dialog.text = "Volevi qualcosa, capitano?";
			link.l1 = "Niente, lascia perdere.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FalseTrace_officer";
		break;
		
		case "FalseTrace_7":
			chrDisableReloadToLocation = true;
			dialog.text = "Mi cercavi, capitano?";
			link.l1 = "Penso che te lo aspettassi... Dov’è l’argento, maledizione? Dove sta? Sto parlando con te! Il capitano del fluyt mi ha detto che era una nave da provviste! Mi hai mentito, canaglia!";
			link.l1.go = "FalseTrace_8";
		break;
		
		case "FalseTrace_8":
			dialog.text = "Calmati, Capitano. Cercherò di spiegare tutto.";
			link.l1 = "Certo che lo farai! Mi sono già calmato! Non ti ho ancora fatto penzolare dalla galloccia solo perché non riesco a capire le tue intenzioni. Hai inseguito questa flûte insieme a me, pur sapendo in anticipo che non c’era argento a bordo. Allora spiegati, per cortesia.";
			link.l1.go = "FalseTrace_9";
		break;
		
		case "FalseTrace_9":
			dialog.text = "Sì, ti ho proprio gabbato, Capitano. Ma era l’unica maniera per spingerti a fare ciò che mi serviva, catturare... khe kha! Catturare quella maledetta flûte.\nMa ti prometto che salderò il mio debito con te. Ora lascia che ti spieghi perché l’ho fatto. Hai trovato una donna sulla flûte? Ho visto i marinai portarla sulla tua nave...";
			link.l1 = "Hm... Quindi, ti serviva la ragazza? E per questo mi hai costretto ad attaccare in mare e a mandare all'altro mondo un mucchio di gente!?";
			link.l1.go = "FalseTrace_10";
		break;
		
		case "FalseTrace_10":
			dialog.text = "È mia moglie. Katerine Rayner. Mi ha abbandonato tre mesi fa con quel cencioso capitano. Ho fatto di tutto per trovarli, e ci sono riuscito. Stavano entrambi per "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". Non potevo immaginare modo migliore per riportare Katerine e farla pagare pure a quel ladro di mogli.\nSe ti avessi detto la verità, te ne saresti andato. Quindi ho dovuto raccontarti una storia succosa su un fluyt carico d’argento.";
			link.l1 = "Hmpf... T'ha lasciato la moglie, vero? Ma che storia intrigante!";
			link.l1.go = "FalseTrace_11";
		break;
		
		case "FalseTrace_11":
			dialog.text = "Questa è mia legittima moglie, la amo e nessun altro ha diritto di stare con lei! Quel mascalzone le ha raccontato belle frottole d’amore e altre sciocchezze mentre io ero... lontano. Non conosci le donne? Lei ha creduto a quelle fandonie, povera sciocca, ed è scappata con lui.";
			link.l1 = "Ascolta, dei tuoi affari di famiglia non me ne importa un accidente, sistematela tra voi due, tu e tua moglie. Ma mi avevi promesso che mi avresti rimborsato le spese, o sbaglio? Ho capito bene?";
			link.l1.go = "FalseTrace_12";
		break;
		
		case "FalseTrace_12":
			if (pchar.basenation == SPAIN || pchar.basenation == HOLLAND)
			{
				pchar.questTemp.FalseTrace.QuestCity = "Portobello";
				pchar.questTemp.FalseTrace.QuestShore = "Shore48";
			}
			else
			{
				pchar.questTemp.FalseTrace.QuestCity = "SantaCatalina";
				pchar.questTemp.FalseTrace.QuestShore = "Shore54";
			}
			dialog.text = "Sì, hai capito bene, capitano. Un favore per un favore. Non ho denaro al momento, ma se porti Katerine e me a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", ti rivelerò informazioni assolutamente affidabili su dove potrai arraffare dell’oro senza muovere un dito.";
			link.l1 = "Molto interessante. E perché mai non puoi dirmi subito questa informazione così affidabile?";
			link.l1.go = "FalseTrace_13";
		break;
		
		case "FalseTrace_13":
			dialog.text = "Perché, ancora non ho queste informazioni. Lascia che ti spieghi nei dettagli. C'è un certo gentiluomo di ventura, Squint-eyed Solly — lo hai mai sentito nominare? — ha in mente di depredare alcune miniere d’oro non lontano da Blueweld.\nPer via di certi eventi, dovrà lasciare tutto il suo oro nascosto in qualche posto segreto, mettendoci un paio di canaglie a far la guardia. Lui stesso andrà a piedi a Belize o a Blueweld per procurarsi una nave.\nHo un mio uomo tra la ciurma di Solly, mi aspetterà a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+". Una volta gettata l’ancora lì, lui mi svelerà dove Solly nasconde la sua robaccia.\nTu andrai, farai fuori le guardie e ti prenderai tutto l’oro per te. Avevo in mente di farlo io, ma viste le circostanze, lascio tutto nelle tue mani. Gratis, stavolta.";
			link.l1 = "La tua storia somiglia fin troppo alla tua vecchia fola di una flûte carica d’argento. Mi hai già imbrogliato una volta. Come puoi giurare che questa volta non stai mentendo?";
			link.l1.go = "FalseTrace_14";
		break;
		
		case "FalseTrace_14":
			dialog.text = "Ti do la mia parola. Non ho altre garanzie da offrirti. Ma è vero, lo giuro khe... kha... maledette miniere!";
			link.l1 = "D'accordo. Ora vai, e rifletterò su ciò che mi hai detto.";
			link.l1.go = "FalseTrace_15";
		break;
		
		case "FalseTrace_15":
			dialog.text = "Non pensarci troppo a lungo. Solly lo Strabico tornerà per i suoi tesori, dovresti saperlo. Secondo i miei calcoli, hai solo due settimane per arrivare a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+".";
			link.l1 = "Terrò a mente, capitano. Ora vai ai quartieri dell’equipaggio e raggiungi i marinai. Credo sia meglio che restiate separati da tua moglie fino al nostro arrivo. Puoi andare.";
			link.l1.go = "FalseTrace_16";
		break;
		
		case "FalseTrace_16":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.FalseTrace = "TalkCabinWoman";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "TalkSelf_Quest", 3.0);
			SetFunctionTimerCondition("FalseTraceSollyOver", 0, 0, 15, false);//таймер
			AddQuestRecord("FalseTrace", "5");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_17":
			dialog.text = "Mi avete chiamato, capitano?";
			link.l1 = "Sì. Adam Rayner, ti metterò in catene e ti sbatterò in cella. Mi hai ingannato, e non mi resta altra scelta che isolarti e consegnarti alle autorità.";
			link.l1.go = "FalseTrace_18";
		break;
		
		case "FalseTrace_18":
			dialog.text = "Davvero? Me l’aspettavo da voi, Capitano. Soprattutto dopo che siete sceso nella stiva a ciarlare con quel lurido scippatore di mogli altrui. Avete scelto la sua parte, non è forse così, Capitano?";
			link.l1 = "Non sono affari tuoi. Mi hai usato, mi hai fregato, e ora cerchi di raggirarmi di nuovo con storielle assurde sui tesori! Nostromo, portalo via!";
			link.l1.go = "FalseTrace_19";
		break;
		
		case "FalseTrace_19":
			dialog.text = "Kha, non così in fretta, Capitano... Il nostromo e il resto della tua ciurma non potranno entrare qui tanto presto. Non hai notato che ho sprangato la porta? Ora siam soli qui – tu ed io. Su, fammi vedere, capitano, di che pasta sei fatto!";
			link.l1 = "Davvero? Pensi davvero di avere una possibilità?! Te ne pentirai, bastardo!";
			link.l1.go = "FalseTrace_20";
		break;
		
		case "FalseTrace_20":
			DialogExit();
			NextDiag.currentnode = "FalseTrace_21";
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetHP(npchar, 100+MOD_SKILL_ENEMY_RATE*35, 100+MOD_SKILL_ENEMY_RATE*35); // belamour с 40 хп боец из него никудышный
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "FalseTrace_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_21":
			dialog.text = "";
			link.l1 = "Così va meglio... Getta le armi, furfante! Nostromo! Mettete questo mascalzone ai ferri e sbattetelo in stiva!";
			link.l1.go = "FalseTrace_22";
		break;
		
		case "FalseTrace_22":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			bQuestDisableMapEnter = false;
			RemovePassenger(Pchar, npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.questTemp.FalseTrace.PrisonerAdamIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			LAi_SetPlayerType(pchar);
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, CIRASS_ITEM_TYPE);
			sld = &Characters[sti(Pchar.questTemp.FalseTrace.PrisonerIDX)];
			ReleasePrisoner(sld); //освободили пленника
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			DeleteAttribute(sld, "LifeDay") //постоянный персонаж
			GiveItem2Character(sld, "blade_10");
			EquipCharacterbyItem(sld, "blade_10");
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");//патроны не даю - все одно для антуражу
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			AddComplexSelfExpToScill(40, 40, 40, 40);
			AddQuestRecord("FalseTrace", "11");
			AddQuestUserData("FalseTrace", "sShore", XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen"));
			pchar.questTemp.FalseTrace = "AdamPrisoner";
		break;
		
		case "FalseTrace_23":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "Grazie, capitano, per avermi aiutato a riportare indietro mia moglie! Adam Rayner ti deve un favore, non se lo scorderà, ah-ah, te lo giuro su... kha! Maledette miniere! Ora parliamo di Solly lo Strabico. Il mio uomo mi ha già dato tutti i dettagli. Solly ha nascosto tutta la sua roba in una grotta nella baia di San Juan del Norte. Lui invece adesso si trova a Blueweld\nDevi fare in fretta, hai solo cinque giorni, parola del mio compare. Porta i tuoi uomini, la banda di Solly non scherza, ti faranno sudare sette camicie\nÈ l’ora dei saluti. Grazie ancora, Capitano, buon vento!";
			link.l1 = "Buona fortuna, Adam. Non far arrabbiare tua moglie!";
			link.l1.go = "FalseTrace_Remove_exit";
			SetFunctionTimerCondition("FalseTraceBonanzaOver", 0, 0, 5, false);//таймер
			pchar.quest.False_Trace_4.win_condition.l1 = "location";
			pchar.quest.False_Trace_4.win_condition.l1.location = "Shore55";
			pchar.quest.False_Trace_4.function = "FalseTrace_SollyBonanza";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddQuestRecord("FalseTrace", "14");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_24":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "Ah! Perché mai, Capitano, siamo sbarcati in questa baia? Ti avevo detto che il mio uomo mi aspettava al porto di "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"! Hai intenzione di andarci a piedi, attraversando la giungla?";
			link.l1 = "Cattiva intuizione, Adam. Davvero pensavi che avrei abboccato alle tue frottole un'altra volta? Mi prendi forse per un babbeo? Stavolta ho stretto un patto con tua moglie.";
			link.l1.go = "FalseTrace_25";
		break;
		
		case "FalseTrace_25":
			dialog.text = "Cosa?! Ah! Che razza d’accordo con mia moglie? Di che vaneggi, pesce marcio?!";
			link.l1 = "A causa delle tue menzogne ho catturato una fluyt vuota e fatto fuori il suo capitano. Me ne pento, ma ormai è troppo tardi per rimorsi. Tua moglie era innamorata di quel marinaio, così ho capito. Ecco perché mi ha chiesto di farti fuori. Ecco perché adesso ci troviamo in questa baia.";
			link.l1.go = "FalseTrace_26";
		break;
		
		case "FalseTrace_26":
			dialog.text = "Non ci posso credere! Katerine... che strega! Beh, prima o poi avrai quello che ti meriti... Allora, come ti ha promesso di pagarti, sciocco? Non ha un soldo, si era persino venduta tutti i gioielli per scappare con quel capitano!";
			link.l1 = "Non sono affari tuoi, canaglia. Ma ora è giunto il momento di chiudere questa conversazione. Ti manderò all’inferno, dove già da tempo dovresti marcire!";
			link.l1.go = "FalseTrace_27";
		break;
		
		case "FalseTrace_27":
			dialog.text = "Vediamo cosa sai fare, carogna di aringa!";
			link.l1 = "...";
			link.l1.go = "FalseTrace_28";
		break;
		
		case "FalseTrace_28":
			DialogExit();
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_AdamDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_abordage":
			dialog.text = "Ah! Perché diamine hai assaltato la mia nave, lurido bastardo? Non riesco proprio a capire...";
			link.l1 = "Non fare il santo, capitano. So bene che razza di carico trasporti. Mi serve.";
			link.l1.go = "FalseTrace_abordage_1";
		break;
		
		case "FalseTrace_abordage_1":
			dialog.text = "Carico? Ah-ah! Che razza di carico pensavi di trovare qui? Le mie stive son vuote!";
			link.l1 = "Cosa hai detto, furfante? Ripeti se hai fegato!";
			link.l1.go = "FalseTrace_abordage_2";
		break;
		
		case "FalseTrace_abordage_2":
			dialog.text = "Te lo ripeto – non ho alcun carico a bordo. Questo fluyt è una nave di approvvigionamento diretta a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+"   portare un carico di palle di cannone e vettovaglie per le truppe.";
			link.l1 = "Mi prendi per scemo. Le tue stive devono straripare d’argento. E andrò a controllare di persona, appena finiamo questa chiacchierata...";
			link.l1.go = "FalseTrace_abordage_3";
		break;
		
		case "FalseTrace_abordage_3":
			dialog.text = "Non so chi ti abbia parlato dell’argento. Ma sono tutte fandonie... Ho perso con te, quindi mi arrendo. Prendi la mia spada. Ora puoi andare a controllare le stive. Sono vuote.";
			link.l1 = "Arrenderti? Mai! Non ho bisogno di testimoni. Prendi la tua spada e combatti, o ti sventro come un agnello.";
			link.l1.go = "FalseTrace_abordage_4";
			link.l2 = "Bene per te che hai mostrato un po' di senno. Credo che riuscirò a ricavare un bel riscatto per la tua testa... Ohé, ragazzi – sbattetelo in stiva!";
			link.l2.go = "FalseTrace_abordage_5";
		break;
		
		case "FalseTrace_abordage_4":
			DialogExit();
			pchar.questTemp.FalseTrace.KillCaptain = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "FalseTrace_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "FalseTrace_abordage_5":
			DialogExit();
			pchar.questTemp.FalseTrace.CapPrisoner = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FalseTrace_AfterFight", 3.0);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "FalseTrace_wife":
			dialog.text = "L’hai ammazzato, canaglia! Mascalzone! Poveraccio "+pchar.questTemp.FalseTrace.CapName+"!";
			link.l1 = "Che c’è? Da dove sbuchi fuori, caro?";
			link.l1.go = "FalseTrace_wife_1";
		break;
		
		case "FalseTrace_wife_1":
			dialog.text = "Brucerai all’inferno per tutto ciò che hai fatto. Al diavolo, lurido cane!";
			link.l1 = "Calmati, ragazza! Non tentare troppo la sorte insultandomi, o ti mando a raggiungere il tuo capitano all'altro mondo!";
			link.l1.go = "FalseTrace_wife_2";
		break;
		
		case "FalseTrace_wife_2":
			dialog.text = "Tu... tu non oseresti mai alzare la mano contro una donna!";
			link.l1 = "Non ne avrò nemmeno bisogno. Posso spararti, oppure gettarti fuori bordo e lasciare che gli squali finiscano il lavoro... Allora, che aspetti? Sali sulla mia nave. Non temere – nessuno ti farà del male, e io stesso non ti toccherò, purché tu stia zitto...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_3":
			DialogExit();
			pchar.quest.False_Trace_AfterBattle.over = "yes";
			pchar.quest.FalseTraceGaleonOver.over = "yes";
			if (CheckAttribute(pchar, "questTemp.FalseTrace.CapPrisoner")) AddQuestRecord("FalseTrace", "");
			else AddQuestRecord("FalseTrace", "");
			sld = characterFromId("Mugger");
			DeleteAttribute(sld, "HalfImmortal");
			RemovePassenger(Pchar, sld);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			DoQuestCheckDelay("LAi_EnableReload", 4.0);
			bQuestDisableMapEnter = true;
			pchar.questTemp.FalseTrace = "TalkCabin";
			AddQuestRecord("FalseTrace", "4");
		break;
		
		case "FalseTrace_wife_4":
			dialog.text = "Cosa... cosa hai intenzione di fargli?";
			link.l1 = "Che succede? Da dove vieni, caro?";
			link.l1.go = "FalseTrace_wife_5";
		break;
		
		case "FalseTrace_wife_5":
			dialog.text = "Poveraccio "+pchar.questTemp.FalseTrace.CapName+"! Dimmi - hai intenzione di ammazzarlo? Non farlo...";
			link.l1 = "Ascoltami bene, signora – se avessi voluto ammazzarlo, l’avrei già fatto. Starà nella stiva, poi lo lascerò andare... o magari chiederò un riscatto – il che è più probabile. E ora, sii una brava ragazza e sali a bordo della mia nave. Non temere – non permetterò a nessuno di farti del male, e io stesso non ti sfiorerò, purché tu stia tranquilla...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_6":
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "Cosa vuoi da me? Vuoi gettarmi in pasto agli squali, come hai detto? Mi hai rovinato la vita e io...";
				link.l1 = "Avanti, caro. Nessuno ti butterà da nessuna parte. Voglio solo chiarire la faccenda, visto che ho assaltato questo fluyt per causa tua e non per altro motivo.";
				link.l1.go = "FalseTrace_wife_7";
			}
			else
			{
				dialog.text = "Cosa vuoi da me? Dove si trova "+pchar.questTemp.FalseTrace.CapName+"  Riscatto? Hai bisogno di un riscatto? ";
				link.l1 = "D'accordo, signora, basta con questa raffica di domande inutili. Non ti ho convocata qui per questo. Un fatto è ormai chiaro, e ti interesserà ascoltarlo.";
				link.l1.go = "FalseTrace_wife_20";
			}
		break;
		
		case "FalseTrace_wife_7":
			dialog.text = "A causa mia? Vuoi dire che è colpa mia se avete assaltato la nostra nave e ucciso il mio amore? Povero "+pchar.questTemp.FalseTrace.CapName+", che t'ha fatto costui? Dovrai render conto al Signore di tutte le tue malefatte...";
			link.l1 = "La solita sbobba! Torniamo a ciarlare di squali, che ne dici?";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_8"://ноды пересечения - старт
			dialog.text = "";
			link.l1 = "Calma adesso? Benissimo. Ora ascoltami! Ho assaltato quella nave perché avevo soffiata che trasportava un bel carico d’argento. E questa dritta l’ho avuta da Adam Rayner.";
			link.l1.go = "FalseTrace_wife_9";
		break;
		
		case "FalseTrace_wife_9":
			dialog.text = "Ah! Cosa?! Adam? Dov’è finito? È qui?";
			link.l1 = "Vedo che conosci il nome... Katerine. E come puoi notare, io so già tutto su di te. Immagino che Adam Rayner sia tuo marito, vero?";
			link.l1.go = "FalseTrace_wife_10";
		break;
		
		case "FalseTrace_wife_10":
			dialog.text = "Sì. Sono la moglie di quel mostro. Credevo che quest’incubo fosse finito, finalmente... Ti ha forse pagato lui per darmi la caccia?";
			link.l1 = "In generale, è andata proprio così. Adam mi ha raccontato frottole sull'argento solo per farmi abbordare la flûte '"+pchar.questTemp.FalseTrace.ShipName+"'. Sicuramente, era deciso a riportarti indietro. Un quarto d’ora fa mi ha spiegato tutte le sue intenzioni.";
			link.l1.go = "FalseTrace_wife_11";
		break;
		
		case "FalseTrace_wife_11":
			dialog.text = "E... che vuole da me? Cosa t’ha raccontato?";
			link.l1 = "Vuole che la sua legittima moglie torni da lui. Mi darà informazioni sull’oro di Solly lo Strabico come risarcimento per avermi gabbato. E io vi porterò entrambi a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+".";
			link.l1.go = "FalseTrace_wife_12";
		break;
		
		case "FalseTrace_wife_12":
			dialog.text = "No... (piangendo) Non voglio tornare da quel mascalzone! Ho fatto una fatica tremenda per scappare e cancellare le mie tracce, eppure mi ha trovata lo stesso... Farabutto! Brigante! Maledetto ladro!";
			link.l1 = "Calmati, Katerine... Modera la lingua. È pur sempre tuo marito. E ha detto che ti amava.";
			link.l1.go = "FalseTrace_wife_13";
		break;
		
		case "FalseTrace_wife_13":
			dialog.text = "(piangendo) Mio marito? Sai chi è mio marito? Un ex galeotto, un dannato e adesso il più feroce mascalzone di "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen")+"! È una bestia meschina e lurida, e per lui io non sono altro che un buco fra le gambe da scopare!";
			link.l1 = "Non avevi già visto tutto prima di sposarlo?";
			link.l1.go = "FalseTrace_wife_14";
		break;
		
		case "FalseTrace_wife_14":
			dialog.text = "All'inizio, era diverso... E il suo passato mi sembrava così affascinante... Ma col tempo tutto è cambiato. E adesso non voglio nemmeno vederlo, figuriamoci viverci insieme, non capisci? Non voglio! Specie dopo quell'attacco al fluyt, che ha organizzato lui!";
			link.l1 = "Mm... Che dovrei fare con te, dolce signora?";
			link.l1.go = "FalseTrace_wife_15";
		break;
		
		case "FalseTrace_wife_15"://ноды пересечения - конец
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "Cosa fare? So bene cosa fare. Sei uno strumento del peccato, grazie alle azioni di mio marito. Hai ucciso un uomo innocente, l’unico che mi abbia mai trattata come si deve. Esìpia i tuoi peccati, capitano. Uccidi Adam. Davanti ai miei occhi. Voglio vedere quel lurido morire, voglio sputargli addosso quando sarà cadavere. \nQuando sarà morto, ti dirò dove nasconde i suoi tesori. Quell’ubriacone una volta mi ha confessato dove li tiene, ahah, neanche se lo ricorda!";
				link.l1 = "Ehi! Sei una donna spietata, Katerine, a quanto vedo!";
				link.l1.go = "FalseTrace_wife_16";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.FalseTrace.CapName+"... Il capitano del fluyt. L'hai rinchiuso. Parlaci, te ne supplico! Ti offrirà qualcosa per salvarci la pelle e darci la libertà! Qualcosa si inventerà! Io... io non voglio tornare da Adam, non più, mai più "+pchar.questTemp.FalseTrace.CapName+" è mio marito! Ti scongiuro – non riportarmi da Adamo, da quel mostro!";
				link.l1 = "Hm. Interessante. E cosa mai potrebbe offrirmi il mio prigioniero? Posso ottenere un riscatto dalle autorità, e avrò anche l’oro di Solly lo Strabico...";
				link.l1.go = "FalseTrace_wife_21";
			}
		break;
		
		case "FalseTrace_wife_16":
			dialog.text = "Guarda chi parla di crudeltà. Salpa verso "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", fai come ti ha detto Adam, solo che invece di sbarcare al porto, punta sulla baia più vicina. Noi tre ci presenteremo lì e tu farai fuori quel bastardo\nQuando sarà fatto, ti parlerò del nascondiglio. Te lo giuro, non ti prendo in giro. Credo che ti fidi più della mia parola che di quella di Adam, dico bene? Già ti ha fregato una volta, no? Che ne dici, capitano?";
			link.l1 = "Già... Dicono che marito e moglie sian davvero tagliati dalla stessa stoffa. Ti guardo, Katerine, e vedo che sei proprio l’anima gemella di Adam... Se lo vuoi morto così tanto, potresti pure piantargli una lama nel sonno da ubriaco... Nostromo! Portala via!";
			link.l1.go = "FalseTrace_wife_17";
			link.l2 = "Odio i furfanti che cercano di imbrogliarmi e usarmi per i loro sporchi fini. Va bene, Katherine, accetto la tua proposta, visto che mi è chiaro che Adam non è degno di fiducia. Ma se anche tu mi tradisci, ti troverò pure in Europa, lo giuro, e ti ficcherò una palla in testa. Ora sparisci. Nostromo! Portala via!";
			link.l2.go = "FalseTrace_wife_19";
		break;
		
		case "FalseTrace_wife_17":
			dialog.text = "Te ne pentirai... Te lo giuro, io...";
			link.l1 = "Contramestre! Sorvegliala e tienila d’occhio senza sosta finché non arriviamo a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"!";
			link.l1.go = "FalseTrace_wife_18";
		break;
		
		case "FalseTrace_wife_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "6");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_19":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "7");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForKillAdam");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_20":
			dialog.text = "Quale fatto? Che volete farci? Perché avete catturato la nostra nave?";
			link.l1 = "Mi lasci parlare o devo ordinare al mio nostromo di tapparti la bocca con uno straccio?!";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_21":
			dialog.text = "L'oro di Solly? Ti fidi davvero di quel mascalzone? Ti fregherà di nuovo, è fatto così! Parla col tuo prigioniero!\n"+pchar.questTemp.FalseTrace.CapName+" è un vero gentiluomo, non mancherà mai alla sua parola e non ti mentirà mai!";
			link.l1 = "Non mi hai convinto, signora. Non ho nulla da discutere col tuo capitano. Otterrò un riscatto per lui e prenderò l’oro di Solly da Adam. Se Adam mi inganna ancora, lo scovo anche all’inferno, e maledirà il giorno in cui è venuto al mondo... Nostromo! Portala via!";
			link.l1.go = "FalseTrace_wife_23";
			link.l2 = "A dir la verità, non mi fido di Adam... Non sopporto essere manovrato. Va bene, parlerò col tuo capitano e vedrò cosa ha da dirmi. Puoi andare ora... Nostromo! Portala via!";
			link.l2.go = "FalseTrace_wife_24";
		break;
		
		case "FalseTrace_wife_23":
			dialog.text = "Sei un uomo crudele e senza cuore! Lo giuro che io...";
			link.l1 = "Contramestre! Sorvegliala e tienila d’occhio per tutto il tempo finché non arriviamo a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"!";
			link.l1.go = "FalseTrace_wife_18";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "8");
			chrDisableReloadToLocation = false;
			pchar.questTemp.FalseTrace.Prisoner = "true";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_25":
			dialog.text = "È finita ormai... Poveraccio "+pchar.questTemp.FalseTrace.CapName+" è stato vendicato, e ora posso finalmente respirare e chiamarmi vedova...";
			link.l1 = "Ho mantenuto la mia parte dell'accordo, Katerine. Ora tocca a te.";
			link.l1.go = "FalseTrace_wife_26";
		break;
		
		case "FalseTrace_wife_26":
			dialog.text = "Certo, capitano. Mio marito – grazie al cielo, ormai ex marito – era un furfante, come già sapete. Temendo perquisizioni, non teneva mai il bottino saccheggiato in casa. Aveva organizzato un nascondiglio – ma una volta se ne lasciò scappare una parola. Tuttavia, lo nascose in modo molto astuto – da terra non si può raggiungere quel posto.";
			link.l1 = "Molto interessante... E dove si trova?";
			link.l1.go = "FalseTrace_wife_27";
		break;
		
		case "FalseTrace_wife_27":
			dialog.text = "Su una piccola isola vicino a Hispaniola. Nel faro.";
			link.l1 = "Faro di Port-au-Prince! Si trova sull'isola!";
			link.l1.go = "FalseTrace_wife_28";
		break;
		
		case "FalseTrace_wife_28":
			dialog.text = "Probabilmente sì. Lì troverai il bottino. Vedrai tu stesso. Questo è tutto. Addio, Capitano.";
			link.l1 = "Aspetta... Perdonami, Katerine, se puoi. Spero che la morte di colui che è causa di tutte le tue sventure ti porti almeno un po’ di sollievo. Mi dispiace davvero...";
			link.l1.go = "FalseTrace_wife_29";
		break;
		
		case "FalseTrace_wife_29":
			dialog.text = "Non ho bisogno dei tuoi rimpianti, Capitano. Hai fatto ciò che ti ho chiesto – e io ti ho detto tutto ciò che volevi sapere. Ora vattene, lasciami solo con il mio dolore...";
			link.l1 = "Addio, Katerine.";
			link.l1.go = "FalseTrace_wife_30";
		break;
		
		case "FalseTrace_wife_30":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15);
			LAi_LocationDisableOfficersGen(pchar.questTemp.FalseTrace.QuestShore, false);//офицеров пускать
			//LAi_LocationDisableOfficersGen("Mayak7", true);//офицеров не пускать
			locations[FindLocation("Mayak7")].DisableEncounters = true;//энкаунтеры закрыть
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.False_Trace_7.win_condition.l1 = "location";
			pchar.quest.False_Trace_7.win_condition.l1.location = "Mayak7";
			pchar.quest.False_Trace_7.function = "FalseTrace_AdamTreasure";
			AddQuestRecord("FalseTrace", "23");
		break;
		
		case "FalseTrace_wife_31":
			dialog.text = "Maledetto furfante! È riuscito a far fuori tutti e quattro! Incredibile!";
			link.l1 = "Non te l’aspettavi, eh, Katerine? Sono duro a morire, io. Devo ammettere che giochi bene su due tavoli!";
			link.l1.go = "FalseTrace_wife_32";
		break;
		
		case "FalseTrace_wife_32":
			dialog.text = "Hai ucciso il mio uomo. Davvero pensavi che ti avrei lasciato respirare ancora?! Credevi che la morte di Adam mi bastasse? No! Da qui non te ne vai. C’è una nave poco lontano dall’isola, farà affondare la tua carretta con te dentro!\nAdesso, fai di me ciò che vuoi.";
			link.l1 = "Non ti avevo forse detto, caro mio, che avresti perso la testa se mi avessi ingannata? Maledetto furfante! Da morto sarai ben meno pericoloso. Questa testolina adesso si becca una palla...";
			link.l1.go = "FalseTrace_wife_33";
			link.l2 = "Mi fai pena, Katerine. La tua sete di vendetta non ti ha portato nulla di buono, alla fine. Ti lascerò al tuo destino – resterai su quest’isola. Credo che i pescatori del posto ti troveranno presto e ti porteranno a Hispaniola. E che il Signore ci giudichi tutti per le nostre azioni...";
			link.l2.go = "FalseTrace_wife_35";
		break;
		
		case "FalseTrace_wife_33":
			dialog.text = "Sei tu che dovresti pregare, mostro! Assassino! Aiuto! Maledett...";
			link.l1 = "Ho sentito abbastanza.";
			link.l1.go = "FalseTrace_wife_34";
		break;
		
		case "FalseTrace_wife_34":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetImmortal(npchar, false);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE) || !CheckAttribute(pchar,"equip."+MUSKET_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
			LAi_ActorAnimation(pchar, "shot", "FalseTrace_CaterinaKilled", 1.0);
		break;
		
		case "FalseTrace_wife_35":
			dialog.text = "Possa tu affogare! Che la tua nave si schianti sugli scogli! E che tu...";
			link.l1 = "Addio, Katerine.";
			link.l1.go = "FalseTrace_wife_36";
		break;
		
		case "FalseTrace_wife_36":
			DialogExit();
			sld = characterFromID("FalseTraceWife"); 
			sld.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "goto", "goto33", "none", "", "", "", -1);
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("Mayak7", false);//офицеров пускать
			locations[FindLocation("Mayak7")].DisableEncounters = false;//энкаунтеры открыть
			AddQuestRecord("FalseTrace", "25");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
		break;
		
		case "FalseTrace_Bandits":
			dialog.text = "A-ah, ecco l’assassino di Adam! Katerine aveva ragione, questo bastardo è venuto a saccheggiare il bottino!";
			link.l1 = "Cosa? Katerine? Chi diavolo sei, tu?";
			link.l1.go = "FalseTrace_Bandits_1";
		break;
		
		case "FalseTrace_Bandits_1":
			dialog.text = "Chi siamo? Siamo amici di Adam Rayner, che tu hai mandato all’altro mondo. Era il capo della nostra confraternita. Ora il capo sono io, il mio nome è "+GetFullName(npchar)+", e ti farò pagare per aver ucciso il mio padrone e per la violenza commessa contro sua moglie.";
			link.l1 = "Violenza? Ma che diavolo stai blaterando?";
			link.l1.go = "FalseTrace_Bandits_2";
		break;
		
		case "FalseTrace_Bandits_2":
			dialog.text = "Hai pugnalato Adam alle spalle, lurido traditore, hai costretto sua moglie a svelarti dove teneva il suo oro e poi hai lasciato la povera donna a crepare su una spiaggia deserta\nMa lei è sopravvissuta, ci ha implorato d’aiutarla, di raddrizzare un torto. Ti aspettavamo da giorni. Ed eccoti qua, bastardo!";
			link.l1 = "Ah-ah! Decisamente lo stile di Katerine... Ora ascolta, ho davvero ucciso Adam, è vero, ma l'ho fatto perché sua moglie stessa mi ha chiesto di farlo. Era una vendetta per la morte del suo amante. Mi ha detto dove trovare il bottino per ricompensarmi...";
			link.l1.go = "FalseTrace_Bandits_3";
		break;
		
		case "FalseTrace_Bandits_3":
			dialog.text = "Non infangare la povera vedova, lurido cane! Perché, allora, sarebbe venuta da noi? Ci ha offerto tutto l’oro se ti avessimo levato di mezzo. Non cerca monete, vuole la tua testa! Una morte santa per vendicare lo sposo!\nMa ti giuro, non finirà nella miseria, quanto è vero che mi chiamo "+GetFullName(npchar)+", e che questa è l’ora in cui crepi, codardo!";
			link.l1 = "Santo cielo, che discorso da far tremare i cannoni. Ah, eccola là, impaziente di godersi questa farsa di persona... Signori?";
			link.l1.go = "FalseTrace_Bandits_4";
		break;
		
		case "FalseTrace_Bandits_4":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Adam_bandit_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_BanditsAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_Remove1":
			dialog.text = "Sei proprio un pasticcione, capitano! Perdere un fluyt carico d’argento... Ho sbagliato a contare su di te. Addio!";
			link.l1 = "Addio, Adam.";
			link.l1.go = "FalseTrace_Remove2";
		break;
		
		case "FalseTrace_Remove2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 15);
		break;
		
		case "FalseTrace_Remove_exit":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "FalseTraceWife_Remove", 15);
		break;
		
		case "FalseTrace_Remove2":
			dialog.text = "T’ho avvertito, capitano, avevamo solo due settimane! Ormai Solly lo Strabico avrà già arraffato tutto il bottino. Non è colpa mia se sei un tale pasticcione. Addio!";
			link.l1 = "Sì, colpa mia. Addio, spero che non ci rivedremo, porti solo sfortuna alla mia ciurma.";
			link.l1.go = "FalseTrace_Remove_exit";
		break;
		
		case "FalseTrace_Solly":
			dialog.text = "Ehilà! Finalmente! Siamo stanchi di aspettare, e queste maledette zanzare... Aspetta... E dov’è Solly? Non ci capisco un’acca...";
			link.l1 = "Solly non verrà qui. Io agisco per lui... Quindi o mi dai l’oro, oppure sei già morto.";
			link.l1.go = "FalseTrace_Solly_1";
		break;
		
		case "FalseTrace_Solly_1":
			dialog.text = "Argh! Vedremo, maledetti! A me, ragazzi! Alle armi!";
			link.l1 = "Che morte da sciocchi, avanti allora, avvoltoi!";
			link.l1.go = "FalseTrace_Solly_2";
			AddDialogExitQuestFunction("FalseTrace_SollyBonanzaAdd");
		break;
		
		case "FalseTrace_Solly_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("FTEnemy_crew_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_SollyAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_GoldShip":
			dialog.text = "Hai mantenuto la tua parte dell’accordo, capitano. Grazie per la fiducia. Non preoccuparti per Adam, lo porterò dove serve. Riceverà ciò che si merita.";
			link.l1 = "Di Adam non me ne frega un accidente. E la tua promessa riguardo quella nave?";
			link.l1.go = "FalseTrace_GoldShip_1";
		break;
		
		case "FalseTrace_GoldShip_1":
			if (sti(pchar.basenation == HOLLAND) || sti(pchar.basenation == SPAIN))
			{
				pchar.questTemp.FalseTrace.ShipNation = ENGLAND;
				pchar.questTemp.FalseTrace.ShipCity = "PortRoyal";
			}
			else
			{
				pchar.questTemp.FalseTrace.ShipNation = SPAIN;
				pchar.questTemp.FalseTrace.ShipCity = "Maracaibo";
			}
			dialog.text = "Sì, sì, certo. Vediamo, contando da oggi... Sì... Tra 12-14 giorni da "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+" una pesante galeone carica di minerale d’oro salperà per l’Europa. Sarà scortata solo da una fregata o una corvetta\nQuindi preparati, è un bottino ricco ma ben difeso. Però, son certo che ce la farai, visto come hai spazzato via la mia resistenza... Devi arrivare a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+" tra due settimane e preparate un agguato\nRicordate che il vostro bersaglio è un pesante galeone con una sola nave di scorta. Questo è quanto, credo. Il resto è nelle vostre mani.";
			link.l1 = "Capisco... Ebbene, "+pchar.questTemp.FalseTrace.CapName+", addio. Forse dovrei augurarti fortuna e una vita felice con Katerine? Spero che voi due ve la caviate. Peccato che ci siamo incontrati in circostanze così tristi.";
			link.l1.go = "FalseTrace_GoldShip_2";
		break;
		
		case "FalseTrace_GoldShip_2":
			dialog.text = "Grazie, capitano. Come ho già detto, avete un che di nobile. Spero che capirete che l'onestà rende più bottino che l'infamia. Dedicatevi a servire la vostra nazione e diverrete un grande uomo di mare.";
			link.l1 = "Rifletterò sulle tue parole. Bene, ora addio!";
			link.l1.go = "FalseTrace_GoldShip_3";
		break;
		
		case "FalseTrace_GoldShip_3":
			DialogExit();
			locations[FindLocation(pchar.questTemp.FalseTrace.TargetShore)].DisableEncounters = false; //энкаутеры открыть
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "FalseTraceDouble_Remove", -1);
			pchar.quest.False_Trace_6.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_6.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_6.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.False_Trace_6.function = "CreateFalseTraceGoldShipOnMap";
			AddQuestRecord("FalseTrace", "19");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen"));
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

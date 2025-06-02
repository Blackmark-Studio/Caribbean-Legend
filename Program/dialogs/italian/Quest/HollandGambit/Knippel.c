// Чарли Книппель - старый артиллерист
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, iTemp, amount;
	string 	sAttr, sGun, sBullet, attrL;

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
		//ветка на взятие 2 варианта прохождения - за Англию
		if(CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Eng") && !CheckAttribute(npchar, "quest.HWICTake") && !CheckAttribute(pchar, "questTemp.HWIC.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
		{
			dialog.text = "Ahoy compare, colpo a catena nel mio deretano! Che vento ti porta da queste parti?";
			link.l1 = "Catene ai tuoi... cosa? Ah lascia stare, volevo solo salutarti.";
			link.l1.go = "exit";
			link.l2 = "Salute, messer Knippel. Ah, ora capisco perché vi chiamano così. Dicono che aveste servito nella Marina Inglese. Ho una nave di prim’ordine e ciurma valente. Vorrei mettere me stesso e il mio vascello al servizio della Corona inglese... ehm... del Commonwealth. Potreste darmi qualche consiglio, raccomandarmi a qualcuno, o magari aiutarmi in questa faccenda?";
			link.l2.go = "Knippel_check";
			break;
		}
		//за Голландию
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "toKnippel")
			{
				dialog.text = "Ahò, compare, catene alla malora! Cosa ti porta da queste parti?";
				link.l1 = "Saluti, signor Knippel. Ah, ora capisco perché ti chiamano Knippel. Si vocifera che tu abbia servito nella Marina Inglese, ed è proprio per questo che vorrei chiederti aiuto...";
				link.l1.go = "Dominica";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Catena nel culo! Che vuoi da me, furfante?";
			link.l1 = "No, non è nulla. Me ne vado.";
			link.l1.go = "exit";
			break;
		}
		//за Англию
		if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
		{
			if (pchar.questTemp.HWIC.Eng == "TakeHollConvoy")
			{
				dialog.text = "Ahoy capitano, ho sentito voci su un convoglio d’argento che è stato assalito...";
				link.l1 = "Siete ben informato, signor Knippel.";
				link.l1.go = "HollConvoy_Check";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SentJons");
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Wait")
			{
				dialog.text = "Domande, capitano?";
				link.l1 = "No, non è nulla. Me ne vado.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Start_main")
			{
				dialog.text = "Son lieto di vederti, capitano! Il mio comandante Richard Fleetwood voleva venir di persona a far la tua conoscenza, ma ieri sera gli è capitata una disgrazia... Qualcuno ha provato a farlo fuori in mezzo alla strada, che maledetta tempesta di catene, accidenti al diavolo!";
				link.l1 = "Impossibile! E che facevano le guardie, si grattavano la pancia?";
				link.l1.go = "Fleetwood_house";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Domande, capitano?";
			link.l1 = "No, non è nulla. Me ne vado.";
			link.l1.go = "exit";
		break;
		}
			dialog.text = "Ahoy, compare, catene e piombo nel deretano! Cosa ti porta da queste parti?";
			link.l1 = "Salve, solo di passaggio.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------за Голландию--------------------------------------------------	
		case "Dominica":
			dialog.text = "Ahò, davvero? E come potrebbe un vecchio lupo di mare, ormai incagliato da tempo, darti una mano, compare?";
			link.l1 = "Vedi... Sono solo un capitano qualunque e faccio la rotta regolare tra la Martinica e Curaçao. Così, sono stato assalito due volte dalla nave fantasma non lontano dalla Martinica... Ma ascolta bene: non è né la Fata Morgana né l’Olandese Volante. Son riuscito a sbrindellarle le vele con semplici palle di cannone!";
			link.l1.go = "Dominica_1";			
		break;
		
		case "Dominica_1":
			dialog.text = "Ah davvero? Non è da nave fantasma perdere vele per un colpo di cannone vero, che il diavolo mi prenda...";
			link.l1 = "Siamo sopravvissuti solo perché la mia nave riusciva a filar via stringendo il vento. L’ultima volta ho dovuto gettare tutto il carico a mare per alleggerire lo scafo e scappare... riesci a immaginare che perdita? Spezza il cuore!";
			link.l1.go = "Dominica_2";			
		break;
		
		case "Dominica_2":
			dialog.text = "Per mille balene, capitano...";
			link.l1 = "Mathias Beck, il governatore di Curaçao, ha semplicemente ignorato le mie lamentele. Ha detto che le storie della nave fantasma sono fandonie e che i miei sentinelli erano ciucchi di grog. Il governatore della Martinica ha promesso di mandare una pattuglia laggiù, ma i suoi occhi mi han detto che non muoverà un dito. Non posso tornare in Martinica finché quel dannato pirata 'fantasma' se ne va in giro. La mia nave è piccola e l’equipaggio pure, probabilmente non sopravvivremo al terzo incontro con lui...";
			link.l1.go = "Dominica_3";			
		break;
		
		case "Dominica_3":
			dialog.text = "È proprio una disgrazia, compare. Ma dimmi, come posso darti una mano?";
			link.l1 = "Ho sentito dai marinai di queste parti che a St. John's c’era un capitano di nome Richard Fleetwood che ha dato la caccia a quella stessa nave fantasma. Io non lo conosco di persona, ecco perché racconto questa storia a te: magari potresti riferirgli delle mie sventure? Son certo che quel lurido pirata si nasconde da qualche parte vicino alle coste selvagge di Dominica, e fa razzie tra Barbados e Martinica.";
			link.l1.go = "Dominica_4";			
		break;
		
		case "Dominica_4":
			dialog.text = "Tra Barbados e Martinica? Ahoy là! Una rotta grassa e piena d’oro, quella. Suona proprio come una carognata che quel malnato farebbe.";
			link.l1 = "Non sono né ricco né pingue, e non ho denaro per ungere la zampa d’un capitano di marina per una scorta armata. Però, se sir Fleetwood già dà la caccia a questa carogna, potreste forse dirgli dove stanare quel 'Vascello Fantasma'?";
			link.l1.go = "Dominica_5";			
		break;
		
		case "Dominica_5":
			dialog.text = "Hai fatto bene a venire qui, compare. Racconterò la tua storia ai giusti, che il diavolo mi porti via il fegato! Presto potrai commerciare di nuovo con la Martinica.";
			link.l1 = "Spero che il Signore ascolti le tue parole! Ti ringrazio per avermi dato ascolto, Charlie. Confido nel meglio. Addio, e schiva la mitraglia a catena!";
			link.l1.go = "Dominica_6";			
		break;
		
		case "Dominica_6":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toDominica";
			AddQuestRecord("Holl_Gambit", "1-17");
			pchar.quest.toDominica.win_condition.l1 = "location";
			pchar.quest.toDominica.win_condition.l1.location = "Dominica";
			pchar.quest.toDominica.function = "PrepareToFleetwoodAttack";
			DelMapQuestMarkShore("Shore1");
			DelMapQuestMarkShore("Shore2");
			AddMapQuestMarkIsland("Dominica", true);
		break;

//----------------------------------------------за Англию--------------------------------------------------	
		case "Knippel_check"://начинаем проверять нашего ГГ по всем статьям
			if(makeint(PChar.reputation.nobility) < 48)//низкая репа
			{
				// belamour legendary edition покажем критерии
				notification("Reputation Too Low! (Adventurer)", "None");
				PlaySound("Voice\English\hambit\Charlie Knippel-04.wav");
				dialog.text = "Alla Vecchia Inghilterra non servono i servizi di canaglie, doppia palla il mio culo! Con tutto il rispetto, vattene affanculo.";
				link.l1 = "Ehi, ehi compare, bada a come parli o ti cucirò la bocca!";
				link.l1.go = "exit";
				break;
			}
			else
			{
				notification("Reputation Check Passed", "None");
			}
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 30)//низкая навигация
			{
				dialog.text = "Capitano, sarò schietto. Non sapreste navigare nemmeno in una tinozza bucata. Tornate quando avrete più mestiere col timone, avete capito?";
				// belamour legendary edition покажем критерии  -->
				notification("Skill Check Failed (30)", SKILL_SAILING);
				//<--
				dialog.text = "Capitano, la nostra flotta ha bisogno di lupi di mare esperti, non di poltroncelli. Torna quando avrai imparato l’arte della navigazione.";							 
				link.l1 = "Capisco... Allora ci vediamo più tardi.";
				link.l1.go = "exit";
				break;
			}
			else
			{
				notification("Skill Check Passed", SKILL_SAILING);
			}
			dialog.text = "Ahoy, sei proprio arrivato al momento giusto, capitano, che mi venga un colpo se mento! Richard non sapeva su chi poteva contare per questa faccenda rischiosa, stava persino pensando di tirarsi indietro... Oggi gli uccellini della fortuna ti cinguettano proprio nell’orecchio. Se ti dimostri all’altezza, ti raccomanderò a un certo uomo molto importante. Hai abbastanza polvere nel braghe per affrontare la faccenda?";
			link.l1 = "Son carico di mitraglia, signor Knippel.";
			link.l1.go = "Knippel_task";
		break;
		
		case "Knippel_task"://первое задание
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
			DelLandQuestMark(characterFromId("Lucas"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Ar har! Vedo che sei pronto all’arrembaggio, capitano! Presto voleranno scintille! Ora ascolta bene. La flotta d’argento della Compagnia Olandese delle Indie Occidentali ha lasciato Willemstad a Curaçao uno o due giorni fa. Naviga verso Philipsburg. Stavolta ci sono poche navi nel convoglio: un solo galeone con l’argento nella stiva e due scorte. Intercetta la flotta d’argento, cattura il Galeone d’Oriente con il carico prezioso e portalo ad Antigua. Le scorte puoi pure mandarle a fondo, non servono a nessuno. Sgancia una salva di palle incatenate nei loro fegati, yar!";
			link.l1 = "I loro giorni sono contati.";
			link.l1.go = "Knippel_task_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Knippel_task_1":
			dialog.text = "Un consiglio, capitano. La rotta commerciale da Curaçao a Sint Maarten passa non lontano dalle coste di San Cristoforo. Io vi suggerirei d'appostare un'imboscata lì. Preparate bene voi stesso e la vostra nave per quest'affare. Mischiarsi con la Compagnia delle Indie Occidentali non è come passeggiare in giardino a braccetto con una bella signorina.";
			link.l1 = "So che razza d'impiccio mi aspetta, ma apprezzo la tua franchezza, messer Knippel. Tornerò con l’argento olandese.";
			link.l1.go = "Knippel_task_2";			
		break;
		
		case "Knippel_task_2":
			DialogExit();
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Eng = "true";//признак, что английка уже бралась
			HWICSilverConvoyInWorld();
			AddQuestRecord("Holl_Gambit", "2-1");
			ReOpenQuestHeader("Holl_Gambit"); // данила ,чтобы вышел из архива. 																				   
			pchar.questTemp.HWIC.Eng = "begin";
			SetFunctionTimerCondition("HollConvoy_Over", 0, 0, 15, false);
		break;
		
		case "HollConvoy_Check"://начинаем проверять
			int iHal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_GALEON_L) iHal++;
				}
			}//признак наличия ТГ в компаньонах
			if (iHal > 0)
			{
				amount = sti(pchar.questTemp.HWIC.Eng.SlvQty) - GetSquadronGoods(pchar, GOOD_SILVER);
				if (amount <= 0)
				{
					dialog.text = "Non c’è bisogno che mi racconti cos’è successo, capitano. Mi hanno già messo al corrente mentre il doganiere frugava la tua nave... Te la sei cavata alla grande, capitano. Davvero magnifico! Non sembrava affatto una passeggiata, altro che palle incatenate!";
					link.l1 = "Fa piacere essere apprezzato.";
					link.l1.go = "HollConvoy_complete";
				}
				else
				{
					dialog.text = "Non c’è bisogno che mi racconti che è successo, compare. Mi hanno già messo al corrente mentre il doganiere frugava la tua nave... Non sei riuscito a portare tutto l’argento, palle di catena un accidente! So con precisione quanto argento c’era su quell’East Indiaman, fino all’ultimo peso. Lo scopo di questa missione era non solo mettere alla prova il tuo valore in battaglia, ma anche la tua lealtà. In quest’ultima hai fallito. Fuori da casa mia, mezzomarinaio!";
					link.l1 = "All’inferno allora, stolto di un babbeo!";
					link.l1.go = "HollConvoy_fail";
				}
			}
			else
			{
				dialog.text = "Fermo là, compare. Non vedo la nave olandese nel tuo squadrone. Ti avevo detto di portarmela come preda. Te la sei venduta e volevi intascarti il malloppo, eh?";
				link.l1 = "Aspetta, dovevo portare anche la nave? Credevo volessi solo l’argento.";
				link.l1.go = "HollConvoy_noShip";
			}
		break;
		
		case "HollConvoy_noShip":
			dialog.text = "Nessuno prende in giro Charlie Knippel, compare! Ricordo benissimo cosa ti ho detto e cosa no. Hai infranto i patti del nostro accordo, e nessun inglese d’onore farà affari con te: qui non c’è posto per i furfanti. Fuori da casa mia, lurido mozzo!";
			link.l1 = "Al diavolo allora, babbeo!";
			link.l1.go = "HollConvoy_fail";
		break;
		
		case "HollConvoy_fail":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-3");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Eng");//зачищаем для возможности отката к голландскому варианту
			pchar.questTemp.HWIC.Fail2 = "true";
		break;
		
		case "HollConvoy_complete":
			dialog.text = "Fatti vedere da me domani e ti presenterò al mio protettore. Ti proporrà altri lavoretti degni delle tue capacità. E si occuperà anche del tuo... tornaconto. Sciogli gli ormeggi!";
			link.l1 = "Benissimo, signor Knippel. Sarò qui domani.";
			link.l1.go = "exit";
			npchar.greeting = "knippel_2";
			AddDialogExitQuestFunction("HollConvoy_Remove");
			AddQuestRecord("Holl_Gambit", "2-4");
			SetTimerFunction("EnglandGambit_2_ZadanieStart", 0, 0, 1);
			pchar.questTemp.HWIC.Eng = "Wait";
			AddSimpleRumourCity("They say that you captured a Dutch ship filled with silver. Well done! You are a valiant sailor, captain! Godspeed!", "SentJons", 10, 3, "");
		break;
		
		case "Fleetwood_house":
			dialog.text = "Me lo sono chiesto anch’io... Quel dannato ha lanciato del pepe negli occhi del capitano Fleetwood e gli ha piantato una lama nel petto prima ancora che Richard potesse sguainare la sua. L’assassino sperava di finirlo con un solo colpo, ché tempo per un secondo non aveva, ma ha fallito. Il capitano Fleetwood indossa sempre un corsaletto sotto la giubba.\nQuella carogna, con un colpo a catena al fegato, è riuscita a svignarsela e a sparire. Pare che abbia dei compari in città. L’unica cosa che il capitano ricorda è che il sicario ha un solo occhio. Non ci servirà poi molto, di Cyclopi come lui il porto ne pullula al giorno d’oggi.\nRichard ha perso un mare di sangue, e il pepe gli ha rovinato la vista: ora è quasi cieco...";
			link.l1 = "Pepe nero? Una maniera costosa per accecare un uomo. Qualcuno doveva essere davvero furioso con Fleetwood. Mi dispiace per il vostro capitano. Avete trovato qualche traccia di того, chi ha colpito?";
			link.l1.go = "Fleetwood_house_1";
		break;
		
		case "Fleetwood_house_1":
			dialog.text = "I marines del capitano Fleetwood hanno perlustrato tutta la città e le baie vicine, ma non hanno trovato un accidente, maledizione alle loro teste! Se non siamo riusciti a beccarlo subito dopo l’attacco, ora non c’è più speranza di mettere le mani su quel maledetto. Il capitano Fleetwood si è fatto una bella schiera di nemici... Ma, capitano, il mio comandante vuole vederti comunque, nonostante l’incidente. Ora si sta riposando a casa sua, quindi andiamo da lui. Seguimi!";
			link.l1 = "Avanti, signor Knippel.";
			link.l1.go = "Fleetwood_house_2";
		break;
		
		case "Fleetwood_house_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			bDisableFastReload = true;//закроем быстрый переход
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//чтобы не сбежал
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_town", "reload", "houseH1", "OpenTheDoors", -1);
			pchar.quest.Knippel_Outside.win_condition.l1 = "location";
			pchar.quest.Knippel_Outside.win_condition.l1.location = "SentJons_town";
			pchar.quest.Knippel_Outside.function = "Knippel_GoTown";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);
			sld = characterFromId("Fleetwood");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseSP3_room", "goto", "goto1");
			AddLandQuestMark(sld, "questmarkmain");
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.money = 110000;
		break;
		
		case "InFleetwoodHouse":
			dialog.text = "Capitano Fleetwood è al piano di sopra, nella sua stanza. Vai da lui, t’aspetta. Io resto qui.";
			link.l1 = "Capito, signor Knippel. Mi metto subito in cammino.";
			link.l1.go = "exit";	
		break;
		
		case "Knippel_ToOfficer":
			dialog.text = "Ascolta, cap... Il capitano Fleetwood ora è al sicuro e in buone mani. Voglio aiutarti a vendicarti del bastardo che l'ha assalito. Ti offro i miei servigi come ufficiale d’artiglieria. Non sono più un gran duellante, troppo vecchio per quelle robe, ma so spazzare via le coffe di un mercantile da mille passi.";
			link.l1 = "Questa sì che vorrei vederla. Benvenuto a bordo, monsieur Knippel!";
			link.l1.go = "Knippel_ToOfficer_1";	
		break;
		
		case "Knippel_ToOfficer_1":
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", false);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", false);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", false);//откроем локаторы
			//Книппеля - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 20;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			SetFunctionTimerCondition("GotoBridgetownOver", 0, 0, 30, false);//на все дела - 1 месяц
			AddSimpleRumourCity("They say that Sir Richard Fleetwood himself is indebted in you. You are a very important man in our town, sir", "SentJons", 10, 3, "");
		break;
		
		case "hired":
			dialog.text = "Ahoy capitano! Cercavi qualcosa?";
			link.l1 = "No, niente.";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("Voice\English\hambit\Charlie Knippel-07.wav");
			if (pchar.questTemp.HWIC.Eng == "MirageFail")
			{
				dialog.text = "Sei proprio un buono a nulla, compare, catene al vento e chiacchiere! Hai fallito il compito più semplice: catturare la 'Mirage' senza perdere la 'Valkyrie'.\nLa nostra ciurma non prenderà più ordini da te. Siamo certi che sir Fleetwood approverà la nostra scelta, a lui gli imbecilli vanno per traverso quanto a noi.";
				link.l1 = "Vai al diavolo tu e il tuo padrone!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "GotoBridgetown" || pchar.questTemp.HWIC.Eng == "SeekVanBerg")
			{
				dialog.text = "Sei proprio un babbeo, compagno, palle incatenate al mio fondoschiena! Abbiamo perso fin troppo tempo a sbrogliare le tue faccende private.\nIl nostro equipaggio non ti servirà più. Siamo certi che Sir Fleetwood approverà la nostra scelta, gli idioti gli stanno sulle scatole quanto a noi.";
				link.l1 = "Vaffanculo tu e il tuo padrone!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "VanBergFailInWorld")
			{
				dialog.text = "Sei proprio un completo idiota, compare, palla incatenata il mio culo! Ti avevamo detto di fingerti mercante solitario sulla 'Valkyrie', e che hai fatto? Hai spaventato il bucaniere col tuo convoglio!\nSiamo certi che Sir Fleetwood approverà la nostra decisione, gli idioti gli stanno sulle scatole quanto a noi.";
				link.l1 = "Vaffanculo a te e al tuo padrone!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "MirageTake")
			{
				dialog.text = "Sei proprio un babbeo completo, compare, palle incatenate un accidente! Hai deciso di farci perdere tempo con ogni fesseria invece di catturare la 'Mirage' e puntare su Antigua? \nL’equipaggio non ti servirà più. Siamo sicuri che Sir Fleetwood approverà la nostra scelta, a lui gli idioti vanno di traverso quanto a noi.";
			link.l1 = "Vaffanculo tu e il tuo padrone!";
			link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_VALCIRIA)//если сам на Валькирии
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "Boat";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA)
						{
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Eng.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
			pchar.questTemp.HWIC.Eng = "end";
			pchar.questTemp.HWIC.Detector = "eng_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "OnCuracao":
			pchar.quest.HWICEng_toBarbadosOver.over = "yes";//снять прерывание
			dialog.text = "Salute, capitano. Felice di rivederti!";
			link.l1 = "Salute, Monsieur Knippel. Hai il denaro? Dammelo e andiamo a Willemstad a prendere Abigail. Vieni con me?";
			link.l1.go = "OnCuracao_1";	
		break;
		
		case "OnCuracao_1":
			dialog.text = "Capitano, ascolta... Non c’è più bisogno di muoversi adesso.";
			link.l1 = "Di che diavolo parli? Questa è una fandonia!";
			link.l1.go = "OnCuracao_2";	
		break;
		
		case "OnCuracao_2":
			dialog.text = "Ho una lettera dal Capitano Fleetwood per voi. E anche il denaro. Ma questi soldi non sono per il padre di Abigail, bensì per voi. Duecentomila pesos. Leggete la lettera e cercate di non giudicarlo troppo severamente...";
			link.l1 = "Che diavolo sta succedendo in questi tempi?! Un altro brutto colpo? Dammi subito la lettera!";
			link.l1.go = "OnCuracao_3";	
		break;
		
		case "OnCuracao_3":
			DialogExit();
			NextDiag.CurrentNode = "OnCuracao_4";
			AddMoneyToCharacter(pchar, 200000);
			LAi_SetCitizenType(npchar);
			npchar.lifeday = 1;//еще денек пусть погуляет по пляжу
			pchar.quest.Holland_ShoreAttack.win_condition.l1 = "location";
			pchar.quest.Holland_ShoreAttack.win_condition.l1.location = "Curacao";
			pchar.quest.Holland_ShoreAttack.function = "CreateHollandShorePatrol";//патруль в прибрежных водах
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", false);//открыть подземелье
			pchar.questTemp.HWIC.Eng = "MerdokMeeteng";
			AddQuestRecordInfo("LetterFromFleetwood", "1");
			AddQuestRecord("Holl_Gambit", "2-23");
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "OnCuracao_4":
			dialog.text = "L'hai letta, capitano? Sarò sincero. Mi vergogno di Capitan Fleetwood e delle sue azioni, sparando palle incatenate al suo... ah, al diavolo tutto ciò. Rodenburg era furibondo quando ha scoperto la tresca tra Abigail e Richard. Pattuglie per le strade perlustrano Curaçao e le navi armate della Compagnia solcano queste acque. Dobbiamo filarcela da qui, subito.\n Capitano, vi serve un cannoniere? Non pretendo agi — mi basta una razione marinaresca regolare. Non sono più un duellante, l'età si fa sentire, ma vi garantisco che so abbattere l'alberetto di un mercantile a mille passi.";
			link.l1 = "Per la miseria, mi piacerebbe proprio vederti riuscirci, signor Knippel. Benvenuto a bordo!";
			link.l1.go = "Knippel_hire";
			link.l2 = "Mi pento d’aver mai dato una mano a voi furfanti inglesi. Ora non so proprio come cavarmi fuori da questo pasticcio. Seguite la vostra rotta, ne ho abbastanza di sorprese.";
			link.l2.go = "Knippel_exit";
			DelLandQuestMark(npchar);
		break;
		
		case "Knippel_hire":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*200;
			npchar.OfficerWantToGo.DontGo = true;
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 120, 120);
			LAi_SetOfficerType(npchar);
			npchar.greeting = "knippel_hire";
			NextDiag.CurrentNode = "Knippel_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			
			//Sinistra - через 2 месяца стартует личный квест Чарли Книппеля "Длинные тени старых грехов"
			SetTimerCondition("DTSG_Start", 0, 0, 60, false);
		break;
		
		case "Knippel_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
		break;
		
//------------------------------------------------против всех-----------------------------------------------
		case "Knippel_abordage":
			dialog.text = "Fermati, canaglia! Perché hai assaltato questa pacifica nave olandese? Non ho merci preziose né oro, che ti prenda un colpo di cannone nel deretano!";
			link.l1 = "Nave olandese? Ahah! Non farmi ridere, 'olandese'. Ho assaltato il tuo brigantino proprio per metterti le mani addosso, caro Charlie. Benvenuto nella mia stiva. Ora parleremo un po’ di dove veleggiavi e per quale diavolo di motivo...";
			link.l1.go = "Knippel_abordage_1";	
		break;
		
		case "Knippel_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-20");
            pchar.quest.Knippel_DieHard.over = "yes";
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "KnippelPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveKnippelOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Knippel_prisoner":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\hambit\Charlie Knippel-07.wav");
			dialog.text = "Sei un demonio, pirata... Brucerai all’inferno per tutti i tuoi peccati! Str...";
			link.l1 = "Rilassati, predicatore. Tu fai sermoni come un puritano. Faresti meglio a preoccuparti prima dello stato della tua anima.";
			link.l1.go = "Knippel_prisoner_1";
		break;
		
		case "Knippel_prisoner_1":
			dialog.text = "Che hai in mente, furfante? Cosa vuoi dal mio comandante e dalla povera ragazza olandese?";
			link.l1 = "Non ti riguarda, Charlie. Non ho più bisogno di te. Alzati.";
			link.l1.go = "Knippel_prisoner_2";	
		break;
		
		case "Knippel_prisoner_2":
			dialog.text = "Vuoi ammazzarmi? Proprio degno d’un bastardo come te. *sputa* Vaffanculo!";
			link.l1 = "Alzati, Charlie. Prepara le tue ultime preghiere.";
			link.l1.go = "Knippel_prisoner_3";	
		break;
		
		case "Knippel_prisoner_3":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Ground_StandUp", "Kill_Knippel", 3.5);
			pchar.quest.RemoveKnippelOver.over = "yes";//снять таймер
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Knippel_officer":
			dialog.text = "Ahoy capitano, palle incatenate sul mio deretano!";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Messer Knippel, sto per mettermi in viaggio verso l’antica città perduta degli indiani, Tayasal. Parliamoci chiaro: sarà una faccenda davvero rischiosa, e per giunta fuori dal comune – dovremo arrivarci passando attraverso... questa statuetta magica. Vuoi venire con me?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Monsieur Knippel, fammi il resoconto completo della nave.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Voglio che tu acquisti certe merci ogni volta che gettiamo l’ancora in porto.";
				Link.l12.go = "QMASTER_2";
			}
			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Sono giunto su vostro ordine, capitano.";
				Link.l2 = "Devo impartirti diversi ordini.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Knippel_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Ascoltate i miei ordini!";
            Link.l1.go = "stay_follow";
			link.l2 = "Non è niente. Puoi andare!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Knippel_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Misere mie... I cannoni vanno bene, quelli che scoppiano li cambiamo, e la polvere la teniamo asciutta e sicura. Che razza di rapporto ti aspettavi, capitano? Sono un vecchio artigliere, mica un contabile. Palle incatenate, un corno! Sono il miglior artigliere di tutti i Caraibi, bada bene!";
			Link.l1 = "Nessuna discussione qui, messer Knippel, il vostro mestiere lo conoscete bene. Troverò io stesso un quartiermastro, non crucciatevi.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Vuoi che il vecchio Charlie lasci i cannoni per il cassero? Capitano, io mando a fondo navi, non faccio il damerino per ogni doblone. E sono certo che nella prima colonia dove ci proveremo mi spennano fino all’osso.";
			link.l1 = "Ma certo, signor Knippel. Devo proprio mettermi a cercare un quartiermastro come si deve.";
			link.l1.go = "exit";
		break;
		
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Ti sto ascoltando.";
			Link.l1 = "Si tratta dell’abbordaggio.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Si tratta della tua nave.";
			Link.l2.go = "Companion_TaskChange";
			if (bBettaTestMode) // Только при бета-тесте
			{
				Link.l3 = "Voglio che tu lasci la mia squadra per un po' e vada a cercare fortuna da solo.";
				Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Niente per ora.";
			Link.l8.go = "exit";
			break;

		case "Companion_TaskBoarding":
			dialog.Text = "Dunque, qual è il vostro desiderio.";
			Link.l1 = "Non abbordare le navi nemiche. Pensa prima alla tua pelle e all’equipaggio.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Voglio che tu assalga le navi nemiche.";
			Link.l2.go = "Companion_TaskBoardingYes";
			break;

		case "Companion_TaskChange":
			dialog.Text = "Dunque, qual è il vostro desiderio.";
			Link.l1 = "Vorrei che tu non scambiassi la tua nave con un’altra dopo l’abbordaggio. La tua nave vale troppo.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Quando abbordi una nave nemica, puoi anche fartela tua, se ne vale la pena.";
			Link.l2.go = "Companion_TaskChangeYes";
			break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Ai ai!";
			Link.l1 = "A tuo agio.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
			break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "Sarà fatto.";
			Link.l1 = "A tuo agio.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
			break;

		case "Companion_TaskChangeNo":
			dialog.Text = "Aye aye!";
			Link.l1 = "Sarà fatto.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
			break;

		case "Companion_TaskChangeYes":
			dialog.Text = "Sarà fatto.";
			Link.l1 = "A riposo.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
			break;
			//	<========////////////////////////////////////////

		case "stay_follow":
            dialog.Text = "Ordini?";
            Link.l1 = "Stai fermo qui!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Seguimi e non perdere il passo!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Cambia il tipo di munizione per le tue armi da fuoco.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Scegli il tipo di munizione:";
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
            dialog.Text = "C’è un cambiamento d’umore!";
            Link.l1 = "Congedato.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Si è mutato il vento dell’umore!";
            Link.l1 = "Licenziato.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Mi sono davvero affezionato a te durante il mio servizio, "+pchar.name+" , e non abbandono mai il mio capitano nei guai. Ti seguirei anche all'inferno, se occorre. Sono con te!";
			link.l1 = "Grazie, messer Knippel! Son lieto che il mio giudizio su di voi fosse giusto.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Quando si parte, che mi fulmini la palla incatenata?";
			link.l1 = "Un po’ più tardi. Dobbiamo prepararci per questo.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "22");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Tu sei un "+GetSexPhrase("Ladro, messere! Guardie, prendetelo","Ladra, ragazza! Guardie, prendetela")+"!!!","Ma guarda un po’! Appena ho girato le spalle, ti sei messo a frugare nel mio baule! Al ladro!!!","Guardie! Una rapina! Prendete quel furfante!!!");
			link.l1 = "Maledizione!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}

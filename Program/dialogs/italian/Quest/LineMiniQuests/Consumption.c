// диалоги по квесту Цена чахотки
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.Consumption == "final")
			{
				dialog.text = "Capitano! Sei partito per mare, ho sentito! Che è successo? Hai scoperto qualcosa? Per carità, raccontami, sputa il rospo!";
				if (CheckAttribute(pchar, "questTemp.Consumption.TakeMoney"))
				{//взял деньги
					link.l1 = "No, mia bella, quest’incursione fu fatta su ordine di Sua Eccellenza il governatore. Mi dispiace davvero, ma Angelo è morto nelle segrete del forte – ormai non v’è più dubbio. Tieniti salda! ";
					link.l1.go = "Waitress";
				}
				else
				{//убил Хуана
					if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
					{
						link.l1 = "Avevi ragione. Tuo fratello è stato rapito. Il comandante vendeva prigionieri come bestiame a un mercante di schiavi chiamato Consumo. Ma ho raggiunto la sua nave, e ora giace in fondo al mare, mentre tuo fratello Angelo sbarcherà presto. Purtroppo non ho tante lance quante servirebbero per portare tutti i passeggeri a terra in una volta sola. ";
						link.l1.go = "Waitress_2";
					}
					else
					{//отпустил Хуана
						link.l1 = "Avevi ragione. Tuo fratello è stato rapito. Il comandante vendeva prigionieri come bestiame a uno schiavista chiamato Consumo. Ma ho raggiunto la sua nave, e anche se non sono riuscito ad ammazzare quel bastardo, tuo fratello Angelo presto metterà piede a terra. Purtroppo, non ho abbastanza scialuppe per sbarcare tutti i passeggeri in una volta sola. ";
						link.l1.go = "Waitress_2";
					}
					sld = characterFromId("ConAndjelo");
					sld.lifeday = 0;
					RemovePassenger(Pchar, sld);
				}
			}
			else
			{
				dialog.text = "Sei riuscito a scoprire qualcosa sul destino di Angelo, capitano?";
				link.l1 = "Non ancora. Ma credo che presto avrò novità. Devi solo avere pazienza, amico. ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		case "without_moneysss": // лесник  если Гг нажрался..сволочь:D:D:D
		    dialog.text = "Signore, mi avevate promesso di ritrovare mio fratello... Perché perdete tempo a bere qui?";
			link.l1 = "Ohh..Sì, giusto..hic... Calmati, bella... Il Signore ci guida... 'slurp'... Il Signore ci guida. Io sono già altrove...hic..";
			link.l1.go = "exit";
		break;
		
		case "Servant":
			dialog.text = "Buon pomeriggio, signore. Quali sono i vostri affari qui?";
			link.l1 = "Ho portato un dispaccio per il signor comandante, ma devo consegnarglielo di persona.";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "Allora vai a cercarlo nella fortezza.";
			link.l1 = "Questa missiva è troppo importante e non è destinata agli occhi né alle orecchie dei soldati. Forse sono arrivato troppo presto, ma posso aspettarlo qui. Fidati di me, è davvero importante!";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < 40)
			{
				notification("Skill Check Failed (40)", SKILL_SNEAK);
				dialog.text = "Il signor comandante di solito mi avverte di tutte le questioni importanti che richiedono di cambiare la solita rotta... Sai, in effetti, mi aveva avvertito proprio di questo caso.";
				link.l1 = "E che cosa t'ha detto?";
				link.l1.go = "Servant_3";
			}
			else
			{
				notification("Skill Check Passed", SKILL_SNEAK);
				dialog.text = "D’accordo, ti credo. E ti crederò ancor di più quando il señor comandante arriverà a confermare le tue parole. Ma fino ad allora, non ti toglierò mai gli occhi di dosso.";
				link.l1 = "Puoi fissarmi quanto ti pare...";
				link.l1.go = "Servant_4";
			}
		break;
		
		case "Servant_3":
			dialog.text = "Mi ha detto di chiamare le guardie della guarnigione in casi simili. Ma ce la caveremo da soli, scommetto. Ragazzi! Sventriamolo!";
			link.l1 = "Accidenti!";
			link.l1.go = "Servant_fight";
		break;
		
		case "Servant_4":
			DialogExit();
			NextDiag.CurrentNode = "Servant_repeat";
			LAi_SetOwnerType(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Servant_repeat":
			dialog.text = "Che altro vuoi? Hai deciso di consegnarmi il messaggio?";
			link.l1 = "No, aspetterò il comandante...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Servant_repeat";
		break;
		
		case "Servant_fight":
			int iRank = sti(pchar.rank)+5;
			int iScl = 15 + 2*sti(pchar.rank);
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			chrDisableReloadToLocation = true;
			for (i=9; i<=11; i++)
			{	
				sld = GetCharacter(NPC_GenerateCharacter("Conservant_"+i, "citiz_"+i, "man", "man", iRank, SPAIN, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "PortSpein_houseF2", "goto", "goto5");
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Consumption_AfterHouseFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//попытка залезть в сундук
		case "Man_FackYou":
			dialog.text = "Sei un ladro! O forse una spia? Ragazzi, giù subito!";
			link.l1 = "Ah, diavolo!";
			link.l1.go = "Servant_fight";
		break;
		
		case "Sergio":
			dialog.text = "Perdonami, posso scambiare due parole con te?";
			link.l1 = "A dir la verità, ho fretta. Che vuoi?";
			link.l1.go = "Sergio_1";
		break;
		
		case "Sergio_1":
			dialog.text = "Ho sentito dire che vai in giro a chiedere di un certo Juan e di una malattia nelle nostre segrete...";
			link.l1 = "Infatti l'ho fatto... puoi spiegarti, per cortesia.";
			link.l1.go = "Sergio_2";
		break;
		
		case "Sergio_2":
			dialog.text = "Calma, calma! Ferma la mano e lascia stare la spada! Siamo dalla stessa parte, qui! Non so perché dovresti impicciarti dei nostri guai, ma questa storia deve finire! Non posso più restarmene zitto!";
			link.l1 = "Stare zitto? Su cosa, di grazia? Che diavolo sai tu del consumo?";
			link.l1.go = "Sergio_3";
		break;
		
		case "Sergio_3":
			dialog.text = "So molto, se non tutto, e ti spiegherò - ma non qui. Incontriamoci stasera, quando le luci saranno spente; sono un assistente medico, quindi ho il permesso di lasciare il forte. Ci vedremo oltre le porte della città, e ti racconterò ogni cosa. Ti supplico - smettila di fare domande, prima che attirino attenzioni, se già non l’hai fatto... Ora devo andare. Ricorda, stanotte oltre le porte della città.";
			link.l1 = "D'accordo, ci sarò. Ehi! Aspetta...";
			link.l1.go = "Sergio_4";
		break;
		
		case "Sergio_4":
			DialogExit();
			AddQuestRecord("Consumption", "8");
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption3.win_condition.l1 = "location";
			pchar.quest.Consumption3.win_condition.l1.location = "PortSpein_Exittown";
			pchar.quest.Consumption3.win_condition.l2 = "Hour";
			pchar.quest.Consumption3.win_condition.l2.start.hour = 0;
			pchar.quest.Consumption3.win_condition.l2.finish.hour = 3;
			pchar.quest.Consumption3.function = "Consumption_MeetSergio";
			pchar.quest.Consumption4.win_condition.l1 = "Timer";
			pchar.quest.Consumption4.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Consumption4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Consumption4.function = "Consumption_FailSergio";
			locations[FindLocation("PortSpein_Exittown")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("PortSpein_Exittown", true);//офицеров не пускать
		break;
		
		case "Sergio_5":
			dialog.text = "Grazie al cielo, sei arrivato... Spero che nessuno ti abbia seguito?";
			link.l1 = "Perché? Sei troppo diffidente, forse persino più del signor comandante, quindi faresti meglio a passare ai fatti... Che sai di Juan?";
			link.l1.go = "Sergio_6";
		break;
		
		case "Sergio_6":
			dialog.text = "Mi chiamo Sergio Saldo. Presto servizio come aiutante medico nella nostra fortezza e...";
			link.l1 = "";
			link.l1.go = "Sergio_6_1";
		break;
		
		case "Sergio_6_1":
			dialog.text = "";
			link.l1 = "Aspetta! Hai sentito quel rumore?";
			link.l1.go = "Sergio_7";
			Play3DSound("lomanie_vetki", -33.25, 1.00, 3.73)
		break;
		
		case "Sergio_7":
			dialog.text = "Cosa?! Dove?";
			link.l1 = "Merda, non siamo soli qui... Chi hai portato con te, canaglia?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Consumption_CreateBandits");
		break;
		
		case "Bandit":
			dialog.text = "Ci hanno beccati! Tu prendi il dottore, io mi occupo dell'altro!";
			link.l1 = "...";
			link.l1.go = "Bandit_1";
		break;
		
		case "Bandit_1":
			DialogExit();
			sld = characterFromId("Sergio");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=3; i++)
			{	
				sld = characterFromId("Conbandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Conbandit_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Sergio_8":
			dialog.text = "Riponi la spada, è finita! Hai visto con i tuoi occhi che hanno provato a far fuori pure me!";
			link.l1 = "Beh, mi pare troppo raffinato per essere una mascalzonata, quindi non sei dei loro. Dove eravamo rimasti? Sei il medico della prigione, giusto?";
			link.l1.go = "Sergio_9";
		break;
		
		case "Sergio_9":
			dialog.text = "Sì. Servo come medico del carcere. Da giovane studiavo medicina, e qui in pochi hanno istruzione. Ecco perché nessuno sa meglio di me cosa succede tra queste mura!";
			link.l1 = "Che sta succedendo allora? E i prigionieri? Sai qualcosa della loro sparizione improvvisa.";
			link.l1.go = "Sergio_10";
		break;
		
		case "Sergio_10":
			dialog.text = "Il nostro comandante li vende... li vende come bestiame a uno schiavista chiamato Juan. Sceglie quelli che nessuno cercherà – poveracci, marinai di navi qualsiasi. E poi, all’improvviso, 'morti di consunzione' – il resto lo puoi immaginare...";
			link.l1 = "Dunque, Juan è umano, dopotutto! Che sai di lui?";
			link.l1.go = "Sergio_11";
		break;
		
		case "Sergio_11":
			dialog.text = "Un poco. Era solito trafficare affari loschi in Marocco insieme ai pirati berberi, e ogni volta che ci visita gli piace raccontare storie di quei tempi. È lì che ha guadagnato il soprannome di Consunzione. Non voglio nemmeno sapere da dove viene, quel nome.\nViene qui ogni mese e si porta via tutti i prigionieri sulla sua nave.";
			link.l1 = "'Consunzione!' E poi dicono che io sia cinico! Ecco perché... Quel tuo comandante è proprio un babbeo!";
			link.l1.go = "Sergio_12";
		break;
		
		case "Sergio_12":
			dialog.text = "Da quel che capisco, ti serve uno di quei dannati prigionieri scomparsi, altrimenti come diavolo sapresti di questa faccenda, dico bene? Se è così, muoviti: stanotte è l’ultima possibilità per questo mese. Ho già firmato i documenti sul decesso di altri tre, e domani, prima di mezzogiorno, Juan mollerà gli ormeggi, appena avrà ricevuto i corpi!";
			link.l1 = "Che hai firmato, dannato? Non ti seguo proprio...";
			link.l1.go = "Sergio_13";
		break;
		
		case "Sergio_13":
			dialog.text = "Dovevo farlo – come facevo ormai da diversi mesi! Ecco perché sono venuto qui, per porre fine a tutto ciò. Sai come è morto il dottor Pinero? Quello che curava i prigionieri prima di me?";
			link.l1 = "Credo d'aver sentito che sia morto di tisi, o sbaglio? Quindi sei stato costretto a questo. Ha senso — ma perché nessuno ha avvertito le autorità su questa faccenda?";
			link.l1.go = "Sergio_14";
		break;
		
		case "Sergio_14":
			dialog.text = "E chi ci crederà mai? Non ho alcuna prova e quei soldati che dovrebbero sorvegliare i prigionieri sono ben pagati, quindi non gli importa nulla, anche se li vendessero ai Caribi come pasto.\nNessuno si fa scrupoli per quei disgraziati, ed è proprio questo il vantaggio del comandante. Ma tu puoi fermare questa storia, almeno per un po', facendo fuori Juan!";
			link.l1 = "Per quel che ho capito, quei tizi a terra erano i suoi uomini, vero? Come faccio a trovarlo?";
			link.l1.go = "Sergio_15";
		break;
		
		case "Sergio_15":
			dialog.text = "Probabilmente hai attirato l'attenzione di qualcuno con tutte queste domande... Ti avevo detto di stare più attento! Ma ora non conta. Non so nulla della nave di Juan, ma i prigionieri vengono sempre spediti a Galera Point, che si trova a nord dell'isola. Suppongo che la nave dello schiavista debba essere lì vicino e potresti ancora raggiungerlo. I suoi messaggeri oggi hanno detto che salperà domani a mezzogiorno.";
			if (!CheckCharacterItem(pchar, "letter_consumption"))
			{
				link.l1 = "Grazie, Sergio, sei un vero ufficiale e un uomo d’onore. Salperò subito l’ancora e andrò a caccia di quella lurida nave. Tu torna al forte prima che si mettano a cercarti.";
				link.l1.go = "Sergio_16";
			}
			else
			{
				link.l1 = "Ebbene, questo mi basta sapere. Devo levare l’ancora subito, se non voglio andare a cercar quella ‘Consunzione’ per tutto il Nuovo Mondo. Nel frattempo, tu puoi darti a studiare questo.";
				link.l1.go = "Sergio_17";
			}
		break;
		
		case "Sergio_16":
			dialog.text = "Buona fortuna, capitano! Non preoccuparti per me – l’importante è che tu riesca almeno a fermare questa faccenda, anche solo per un po’. Ti auguro ogni fortuna!";
			link.l1 = "I miei cannoni sono la miglior cura per malanni e viltà. Giuro che tutti i prigionieri toccheranno terra prima dell’alba – e la nave di Juan dormirà sul fondo del mare!";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_17":
			RemoveItems(PChar, "letter_consumption", 1);
			Log_Info("You have given the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "Che cos'è? Qui c'è il nome del colonnello e un monogramma 'J'? Incredibile! Dove l'hai trovato?";
			link.l1 = "Meglio che tu non lo sappia, ma son certo che ne farai buon uso.";
			link.l1.go = "Sergio_18";
		break;
		
		case "Sergio_18":
			dialog.text = "Lo giuro su tutto ciò che è sacro! Quel colonnello ci finirà sulla forca prima della fine del mese! Mi occuperò io stesso di farlo!";
			link.l1 = "Temo che finirà con una punizione disciplinare, che, a quanto pare, non sarà la prima nella sua miserabile vita. Forse sarebbe meglio sparare a quel cane? È un rimedio assai efficace... Ora devo andare – non vorrei far aspettare la 'Consunzione'.";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_19":
			DialogExit();
			AddQuestRecord("Consumption", "11");
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption5.win_condition.l1 = "location";
			pchar.quest.Consumption5.win_condition.l1.location = "Trinidad";
			pchar.quest.Consumption5.function = "Consumption_CreateJuan";
			pchar.quest.Consumption6.win_condition.l1 = "HardHour";
			pchar.quest.Consumption6.win_condition.l1.hour = 13;
			pchar.quest.Consumption6.function = "Consumption_FailJuan";
			// Сержио теперь наш друг и будет торговать смолами
			SetFunctionTimerCondition("Oil_PrepareSergio", 0, 0, 20, false); // таймер
		break;
		
		// генератор торговли смолами
		case "Sergio_20":
			dialog.text = "Oh, che fortunato incontro! Signor "+GetFullName(pchar)+"! Son così felice di vederti!";
			link.l1 = "Signor Sergio! Non mi aspettavo proprio d'incontrarvi! Come state? E il buon vecchio comandante, come se la passa?";
			link.l1.go = "Sergio_21";
		break;
		
		case "Sergio_21":
			dialog.text = "Sto bene, e il signor comandante è andato alle miniere di Los-Teques – le sue luride macchinazioni con Juan Consumo sono state smascherate.";
			link.l1 = "Miniere?! Per tutti i diavoli! Non avrei mai creduto che la giustizia l’avrebbe raggiunto davvero...";
			link.l1.go = "Sergio_22";
		break;
		
		case "Sergio_22":
			dialog.text = "Ah, magari fosse così, capitano... È stato solo trasferito e retrocesso. Ora serve nella guarnigione, e non gli hanno nemmeno tolto il grado d’ufficiale. Beh, almeno San Jose s’è liberata di quella feccia.";
			link.l1 = "Ebbene, fin qui tutto liscio. Anche se mi aspettavo di meglio.";
			link.l1.go = "Sergio_23";
		break;
		
		case "Sergio_23":
			dialog.text = "Anch’io... Ma lasciamo perdere quella feccia – non merita nemmeno una parola. Señor, appena ho sentito che la vostra nave stava per entrare in porto, mi sono precipitato al molo a tutta birra. Ho un affare da proporvi.";
			link.l1 = "Davvero? Sto ascoltando.";
			link.l1.go = "Sergio_24";
		break;
		
		case "Sergio_24":
			if (startHeroType == 1) sStr = "French";
			if (startHeroType == 2) sStr = "Spanish";
			if (startHeroType == 3) sStr = "English";
			if (startHeroType == 4) sStr = "English";
			dialog.text = "Capitano, mi parete un uomo di cui ci si può fidare. Un'altra cosa assai importante è che siete "+sStr+" e possiedi la tua nave. Ti propongo di stringere un patto commerciale.";
			link.l1 = "Sembra promettente! Che sorta d’accordo?";
			link.l1.go = "Sergio_25";
		break;
		
		case "Sergio_25":
			dialog.text = "Parliamone altrove – nella capanna del guardiano del faro. È un mio vecchio compare, di cui mi fido ciecamente. Vieni al faro di San Jose oggi o domani. Là ti aspetto. Son sicuro che la mia proposta stuzzicherà il tuo interesse!";
			link.l1 = "D'accordo, señor Sergio. Ci vediamo laggiù!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Oil_SergioRuntoMayak");
		break;
		
		case "Sergio_26":
			chrDisableReloadToLocation = true;//закрыть локацию
			pchar.quest.Oil_SetSergioToMayakOver.over = "yes"; //снять прерывание
			dialog.text = "Ben tornato, señor. Permettimi di spiegarti questa faccenda. ";
			link.l1 = "Sono tutto orecchi. ";
			link.l1.go = "Sergio_27";
		break;
		
		case "Sergio_27":
			dialog.text = "Come forse già sapete, non sono solo un soldato, ma pure un medico. Sapete perché? Son uomo di grande cultura, io. I miei studi mi han tenuto lontano dal perder tempo qui con donne e rum. Invece, ho organizzato diverse spedizioni e son riuscito a trovare un giacimento di resina poco distante da qui\nQuesta è una risorsa di grande valore strategico: quest’isola è l’unico luogo dove si può trovare la resina speciale che serve per costruire navi solide e durature\nUn governatore e un comandante m’han ordinato di vendere tutta la resina alla marina spagnola\nIl guaio è che mi pagano la metà del suo valore di mercato, e non posso smerciarla altrove. Dunque, vi propongo di acquistarla voi. È una merce assai preziosa e difficilissima da ottenere.";
			link.l1 = "Quali sono le condizioni del nostro accordo? ";
			link.l1.go = "Sergio_28";
		break;
		
		case "Sergio_28":
			dialog.text = "Secondo i miei calcoli, potrò raccogliere sessanta barili al mese senza destare sospetti. Facciamo così: ogni cinque del mese verrò a questo faro a bermi un goccio col mio compare. Se vuoi comprare la resina, vieni anche tu. Dieci dobloni d’oro per barile.\nPaghi tutta la partita in una volta e te la porti via. Nessuno ti mette fretta, scegli tu. Allora, affare fatto?";
			link.l1 = "Mi sembra proprio un affare da maledetti! Certo che ci sto!";
			link.l1.go = "Sergio_29";
		break;
		
		case "Sergio_29":
			dialog.text = "Meraviglioso. Allora, il cinque di ogni mese berrò una bottiglia di vino delle Canarie col mio vecchio compare, il custode, e ti aspetteremo.";
			link.l1 = "D'accordo. Facciamolo così.";
			link.l1.go = "Sergio_30";
		break;
		
		case "Sergio_30":
			dialog.text = "Sono lieto che abbiamo trovato un accordo. Ci si vede, capitano!";
			link.l1 = "Buona fortuna col tuo traffico di resina, señor!";
			link.l1.go = "Sergio_31";
		break;
		
		case "Sergio_31":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			pchar.questTemp.OilTrade = "true";
			pchar.quest.Oil_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.Oil_fail.win_condition.l1.character = "Sergio";
			pchar.quest.Oil_fail.function = "Oil_TradeFail";
			AddQuestRecordInfo("Unique_Goods", "4");
		break;
		
		case "oil_trade":
			dialog.text = "Salve, señor capitano! Sei venuto per una partita di resina, suppongo.";
			link.l1 = "Proprio così, señor Sergio. È tutto pronto?";
			link.l1.go = "oil_trade_1";
			link.l2 = "Señor Sergio, non ho nessuna voglia di mercanteggiare ora. Magari più tardi.";
			link.l2.go = "oil_trade_exit";
		break;
		
		case "oil_trade_exit":
			DialogExit();
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "oil_trade_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeOil"))
			{
				dialog.text = "Sì. Hai con te 2550 dobloni?";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "Certo. Ecco a te.";
					link.l1.go = "oil_trade_2";
				}
				else
				{
					link.l1 = "Sfortuna! Ho dimenticato il denaro sulla mia nave. Lo porto qui subito!";
					link.l1.go = "oil_trade_exit";
				}
			}
			else
			{
				dialog.text = "Sì. Hai con te seicento dobloni?";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "Certo. Eccoti qua.";
					link.l1.go = "oil_trade_2";
				}
				else
				{
					link.l1 = "Che sfortuna! Ho dimenticato i soldi sulla mia nave. Li porto qui subito!";
					link.l1.go = "oil_trade_exit";
				}
			}
			if(sti(pchar.questTemp.SergioOil) >= 1 && !CheckAttribute(pchar, "questTemp.SergioOilBlock")) // увеличить объём поставок смолами
			{
				link.l4 = "Señor Sergio, desidero comprare altra resina. Potreste fornirmi partite, diciamo, cinque volte più grandi?";
				link.l4.go = "UpgradeOil";
			}
			if(sti(pchar.questTemp.SergioOil) >= 1 && CheckAttribute(pchar, "questTemp.SergioOilPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок смолами, если в первый раз не принесли
			{
				link.l4 = "Ecco qui, come promesso, Señor Sergio, tremila dobloni, come avete richiesto. Confido che con la vostra lungimiranza e il mio investimento, questa impresa porterà notevole profitto ad entrambi.";
				link.l4.go = "UpgradeOil_Agreed";
			}
		break;
		
		case "oil_trade_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			if (CheckAttribute(pchar, "questTemp.UpgradeOil")) RemoveDublonsFromPCharTotal(2550);
			else RemoveDublonsFromPCharTotal(600);
			PlaySound("interface\important_item.wav");
			dialog.text = "È un piacere fare affari con voi, capitano. I miei uomini vi aiuteranno a caricare le botti sulla vostra nave.";
			link.l1 = "Grazie di cuore!";
			link.l1.go = "oil_trade_3";
		break;
		
		case "oil_trade_3":
			dialog.text = "L’accordo è sempre valido. Se ti serve un’altra partita, torna fra un mese.";
			link.l1 = "D'accordo, Sergio. Ci si vede.";
			link.l1.go = "oil_trade_4";
		break;
		
		case "oil_trade_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			if (CheckAttribute(pchar, "questTemp.UpgradeOil")) AddCharacterGoods(pchar, GOOD_OIL, 300);
			else AddCharacterGoods(pchar, GOOD_OIL, 60);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
			pchar.questTemp.SergioOil = sti(pchar.questTemp.SergioOil) + 1; // счётчик покупок
		break;
		
		case "UpgradeOil":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Señor"+GetSexPhrase("","ita")+", il tuo desiderio di acquistare altra resina dimostra una certa fiducia nei nostri affari. Tuttavia, c’è una piccola complicazione...\nAumentando i volumi cresce anche il rischio di attirare l’attenzione delle autorità dell’isola, e gestire spedizioni così grosse richiede uomini fidati e misure di sicurezza, che, ti avverto, non costano poco. Se sei disposto ad aggiungere tremila dobloni al prezzo, come pagamento unico, assumerò gente affidabile che proteggerà la merce e terrà la bocca chiusa. Così la nostra rotta diventerà più sicura e potrò fornirti trecento barili di resina al mese. Per ricompensarti dell’investimento, ti offrirò uno sconto del quindici per cento su tutte le future spedizioni, come cliente all’ingrosso.";
				link.l1 = "Tremila dobloni per mettere al sicuro le spedizioni? Señor Sergio, non lo nego, questo prezzo mi pare assurdo – sembra quasi che tu voglia ordire una congiura all’Escorial invece di proteggere qualche barile di pece!";
				link.l1.go = "UpgradeOil_1";
				notification("Skill Check Passed", SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Señor"+GetSexPhrase("","ita")+", apprezzo il tuo interesse, ma affari di tale portata richiedono esperienza e prudenza. A dire il vero, il tuo livello nelle questioni di commercio non è ancora abbastanza alto per gestire un carico simile. Ti consiglio di fare un po’ più di esperienza e tornare da me quando sarai pronto per spedizioni più grandi. Allora, forse, ne parleremo sul serio.";
				link.l1 = "Molto bene. Torneremo su questa faccenda più tardi.";
				link.l1.go = "oil_trade_exit";
				notification("Skill Check Failed (80)", SKILL_COMMERCE);
			}
		break;
		
		case "UpgradeOil_1":
			dialog.text = "Señor"+GetSexPhrase("","ita")+", Capisco la tua preoccupazione. Ma sai bene che la sicurezza non è mai a buon mercato, soprattutto con merci così rare. Inoltre, non solo ti garantisco nessuna soffiata, ma ti offro pure uno sconto che col tempo ripagherà il tuo investimento. Non ti pare un compromesso ragionevole?";
			link.l1 = "Lo ammetto: nella nostra attività, affidabilità e discrezione si pagano care, e lo sconto rende l’affare un po’ più interessante. Ma tremila dobloni sono comunque una cifra esagerata. Non potreste abbassare un po’ la richiesta?";
			link.l1.go = "UpgradeOil_2";
		break;
		
		case "UpgradeOil_2":
			dialog.text = "Mi rincresce, ma in queste faccende i mezzi termini non valgono. O garantiamo una protezione completa, o rischiamo tutto quanto. La somma resta invariata, ed è solo così che posso assicurare affidabilità e discrezione. Non vorrà mica che tutta la flotta reale si metta prima alle mie calcagna e poi alle sue, vero?";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Molto bene, Señor Saldo, mi hai convinto. Sicurezza e affidabilità valgono il loro prezzo. Tremila dobloni. Eccoli qua.";
				link.l1.go = "UpgradeOil_Agreed";
			}
			link.l2 = "Señor Saldo, mi avete persuaso della necessità di queste misure. Tuttavia, tremila dobloni sono una somma considerevole, e al momento non li ho. Dovrò attendere finché non avrò raccolto la cifra richiesta.";
			link.l2.go = "UpgradeOil_4";
			link.l3 = "Per una somma simile, si potrebbe corrompere un'intera flotta e tutti i soldati del continente, figurarsi assoldare delle guardie per un carico così misero! Mi scuso, ma non posso accettare una proposta del genere. Lasciamo tutto com'è, senza esagerazioni né spese aggiuntive.";
			link.l3.go = "UpgradeOil_3";
		break;
		
		case "UpgradeOil_Agreed":
			dialog.text = "Ebbene, señor, vedo che la nostra fiducia è reciproca. Stia tranquillo: tutto sarà sistemato come si deve. E ora ai dettagli: 300 barili di resina, come sempre, vi aspetteranno qui al faro di Trinidad il 5 di ogni mese. Potete acquistare l’intero carico per 2550 dobloni.";
			link.l1 = "Eccellente, Señor Sergio. Non deludermi.";
			link.l1.go = "UpgradeOil_Agreed_1";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "4_1");
			pchar.questTemp.UpgradeOil = true;
			pchar.questTemp.SergioOilBlock = true;
			DeleteAttribute(pchar, "questTemp.SergioOilPotom");
		break;
		
		case "UpgradeOil_Agreed_1":
			dialog.text = "Non aver dubbi, señor"+GetSexPhrase("","ita")+"   Tutto sarà organizzato al massimo livello, e il nostro sforzo congiunto darà i suoi frutti.";
			link.l1 = "Ci si vede.";
			link.l1.go = "oil_trade_exit";
		break;
		
		case "UpgradeOil_3":
			DialogExit();
			pchar.questTemp.SergioOilBlock = true;
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "UpgradeOil_4":
			dialog.text = "Vieni quando avrai tutta la somma. Sarò lieto di concludere un nuovo accordo con te.";
			link.l1 = "D'accordo.";
			link.l1.go = "oil_trade_exit";
			pchar.questTemp.SergioOilBlock = true;
			pchar.questTemp.SergioOilPotom = true;
		break;
	// <-- генератор смол
		
		case "Juan_abordage":
			dialog.text = "Chi diavolo sei tu!?";
			link.l1 = "Il mio nome è "+GetFullName(pchar)+", quanto a te, Consumo, il diavolo ti aspetta – e si prenderà la tua anima molto presto!";
			link.l1.go = "Juan_abordage_1";
		break;
		
		case "Juan_abordage_1":
			if (CheckAttribute(pchar, "questTemp.Consumption.House"))
			{
				dialog.text = "Questa nave sta per saltare in aria – la miccia arde già nella santabarbara – che senso ha crepare a tutti двоим? Abbassiamo le spade. Avrai tempo di sgattaiolare fuori, e io mi butterò a mare, Punta Galera è a due passi da qui. Se ti serve oro, prendilo! Cinquecento dobloni, sonanti sul tavolo – tu ti scordi di me, io mi scordo di te! Affare fatto?";
				link.l1 = "Oro? Non mi sono messo in tutto questo per il denaro, Juan, ma per far fuori la feccia, e tu sei già un bottino degno di un re.";
				link.l1.go = "Juan_abordage_2";
				link.l2 = "Cinquecento dobloni? Mi prendi per il culo, Consumo. Qua ce n’è almeno il doppio... Dammi subito mille e poi puoi andare al diavolo, altrimenti...";
				link.l2.go = "Juan_abordage_3";
			}
			else
			{
				dialog.text = "La nave sta per saltare in aria, quindi avrò buona compagnia, che ne dici?";
				link.l1 = "Parli troppo, Consumo, veniamo al sodo!";
				link.l1.go = "Juan_abordage_5";
			}
		break;
		
		case "Juan_abordage_2":
			dialog.text = "Potevamo fare un accordo... Eh, al diavolo!";
			link.l1 = "Hai strappato queste povere anime dalle loro celle, senza che potessero opporsi o fuggire. Sei un codardo, Consumo, e ora morirai come il vile che sei.";
			link.l1.go = "Juan_abordage_5";
		break;
		
		case "Juan_abordage_3":
			dialog.text = "Hai fiuto per gli affari, amico... Tieni – questo è tutto ciò che possiedo. Non è molto per una vita, eh?";
			link.l1 = "La tua vita non vale nemmeno una pallottola, quindi pare che sia l’affare più vantaggioso della mia esistenza. Ora sparisci dai miei occhi.";
			link.l1.go = "Juan_abordage_4";
			TakeNItems(pchar, "gold_dublon", 1000);
			Log_Info("You received 1000 doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			OfficersReaction("bad");
			pchar.questTemp.Consumption.TakeMoney = "true"; //атрибут для диалога
		break;
		
		case "Juan_abordage_4":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "ConJuan_AfterFight_1", 10.0);
		break;
		
		case "Juan_abordage_5":
			dialog.text = "Che peccato che non avrai tempo di salvare tutti e farmi fuori, eh? La miccia arde, il tempo scorre...";
			link.l1 = "Maledizione! Devo far sgombrare questa gente... Sparite, feccia – prima o poi avrete ciò che vi spetta!";
			link.l1.go = "Juan_abordage_4";
			link.l2 = "Ci proverò comunque...";
			link.l2.go = "Juan_abordage_6";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
			sld = GetCharacter(NPC_GenerateCharacter("ConAndjelo", "citiz_9", "man", "man", 5, SPAIN, -1, true, "quest"));
			sld.name = "Angelo";
			sld.lastname = "";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
		break;
		
		case "Juan_abordage_6":
			//LAi_SetCurHPMax(NPChar);
			//LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("ConJuan_AfterFight_2"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Consumption.KillJuan = "true"; //атрибут для диалога
		break;
		
		case "Waitress":
			dialog.text = "Ah... Sono senza parole... Che incubo!";
			link.l1 = "Ahimè, non potevo far nulla. Mi dispiace, ragazza. Addio.";
			link.l1.go = "Waitress_1";
		break;
		
		case "Waitress_1":
			DialogExit();
			AddQuestRecord("Consumption", "16");
			AddQuestUserData("Consumption", "sSex", GetSexPhrase("",""));
			Consumption_Close();
		break;
		
		case "Waitress_2":
			dialog.text = "Incredibile! Tu... davvero l’hai salvato? Non so proprio come ringraziarti.";
			if (CheckAttribute(npchar, "quest.Consumption.sex"))
			{
				link.l1 = "Posso ben immaginarlo, bellezza. Ma la mia parte dell’accordo è fatta ormai – resta solo una piccola cosuccia.";
				link.l1.go = "Waitress_3";
			}
			link.l2 = "Il dovere mi ha chiamato – ed io ho risposto. Tutto qui.";
			link.l2.go = "Waitress_5";
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan")) AddQuestRecord("Consumption", "18");
			else AddQuestRecord("Consumption", "17");
		break;
		
		case "Waitress_3":
			dialog.text = "Io... oh Dio! Hai ragione. Per lui, come promisi... Sali di sopra nella stanza – non abbiamo molto tempo.";
			link.l1 = "Sbrighiamoci, allora!";
			link.l1.go = "Waitress_4";
		break;
		
		case "Waitress_4"://благодарность натурой
			DialogExit();
			LocatorReloadEnterDisable("PortSpein_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("PortSpein_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "PortSpein_tavern_upstairs", "goto", "goto3", "ConsumptionSexWaitress", -1);
			pchar.questTemp.Consumption.Sex = "true";
		break;
		
		case "Waitress_sex":
			dialog.text = "Ecco qua, mio prode caballero! E guarda cosa mi sono portato dietro.";
			link.l1 = "Ebbene, ebbene, son davvero colpito, apriamo quel vin di ciliegie! Poi apriremo qualcos'altro... Oggi la sorte ti sorride, dopotutto... Ah-ah!";
			link.l1.go = "Waitress_sex_1";
		break;
		
		case "Waitress_sex_1":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;
		
		case "Waitress_5":
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
			{
				dialog.text = "Sei un vero cavaliere! Caballero! Tieni - non prenderlo come un’offesa, ma desidero che tu lo accetti. Ho messo da parte questi scudi per riscattare Angelo, ma ora non ha più importanza! Ti prego, non rifiutare - prendi!";
				link.l1 = "Ebbene, ricorderò i tuoi occhi, señorita – sono assai più belli quando brillano di lacrime di gioia invece che di dolore. Accetto il tuo dono. Addio, e buona fortuna a te e ad Angelo.";
				link.l1.go = "Waitress_6";
				AddMoneyToCharacter(pchar, 5000);
			}
			else
			{
				dialog.text = "Sei un vero cavaliere! Un caballero! Lo racconterò a tutti! Non ti dimenticherò mai!";
				link.l1 = "Ebbene, e ricorderò i tuoi occhi, señorita – son assai più incantevoli quando brillano di lacrime di gioia e non di dolore. Che la felicità ti accompagni sempre. Addio!";
				link.l1.go = "Waitress_6";
			}
		break;
		
		case "Waitress_6":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			Consumption_Close();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

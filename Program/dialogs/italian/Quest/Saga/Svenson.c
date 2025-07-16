// Ян Свенсон - пиратский барон Западного Мэйна
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson")) {
				if (pchar.questTemp.HelenDrinking.Result == "won") {
					dialog.text = "Ah, Charles. Grazie d’essere passato. Volevo solo ringraziarti per aver fatto compagnia a Helen. La ragazza aveva bisogno di leccarsi le ferite, e mi dicono che pure tu non te la sia passata male, eh eh! Diavolo, quasi ti invidio!";
					link.l1 = "Non sei arrabbiato? Per la faccenda della botte e... tutto il resto?";
					link.l1.go = "after_drinking";
				} else {
					dialog.text = "Ah, Charles. Grazie d’essere passato. Volevo solo ringraziarti per aver fatto compagnia a Helen. La ragazza aveva bisogno di leccarsi le ferite, e mi dicono che anche tu non te la sei passata male, eh eh! Buona fortuna a Cartagena!";
					link.l1 = "Sì, anch'io son lieto che ieri tutto sia filato liscio. Fino a rivederci, Jan.";
					link.l1.go = "exit";
				}
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson");
				break;
			}
		
			if(CheckAttribute(pchar, "questTemp.Saga"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga_Late")) // отсекание при провале по времени
				{
					dialog.text = "Oh, mio buon amico "+pchar.name+"Che piacere vederti! Dimmi pure, che posso fare per te?";
					link.l1 = "Passavo solo per vedere come te la cavi.";
					link.l1.go = "exit";
					if(CheckAttribute(npchar, "quest.trade_bakaut")) // торговля бакаутом
					{
						if (GetDataDay() == 14 || GetDataDay() == 28)
						{
							link.l2 = "Jan, vorrei acquistare del legno di ferro.";
							link.l2.go = "trade_bakaut";
						}
					}
					break;
				}
				if(pchar.questTemp.Saga == "svenson")
				{
					dialog.text = "Come posso esserle d’aiuto, signore?";
					link.l1 = "Vorrei chiederti un favore, Diavolo della Foresta.";
					link.l1.go = "saga";
					break;
				}
				if(pchar.questTemp.Saga == "svenson1")
				{
					dialog.text = "Aha, mio buon amico "+pchar.name+" ! Quali sono le novità?";
					link.l1 = "Son riuscito a scoprire un bel po' di cose intriganti dal Boia.";
					link.l1.go = "saga_11";
					break;
				}
				if(pchar.questTemp.Saga == "svenson2")
				{
					dialog.text = "Allora, "+pchar.name+", hai parlato con Gladys?";
					link.l1 = "Sì, l’ho fatto. Jan, vieni qui a vedere... Mi sai dire qualcosa su questo pezzo di pergamena?";
					link.l1.go = "saga_17";
					break;
				}
				if(pchar.questTemp.Saga == "helena1" || pchar.questTemp.Saga == "helena2" || pchar.questTemp.Saga == "svenson_wait")
				{
					dialog.text = "Non ho ancora niente di nuovo da raccontarti, "+pchar.name+" Ma sto lavorando a una soluzione per la nostra faccenda. Torna più tardi.";
					link.l1 = "D’accordo, Jan. A più tardi.";
					link.l1.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests") // старт трех квестов баронов
				{
					// первая проверка времени. Свенсон очень недоволен растяпством ГГ. Счищаем Элен, к Свенсону доступ закроем
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = ""+pchar.name+", mi hai profondamente deluso. Ti credevo uomo serio, invece sei solo un ragazzino sciocco. Dove diavolo sei stato tutto questo tempo, eh? Gli inglesi si sono presi Isla Tesoro mentre tu chissà cosa combinavi!\nTutti i miei piani sono andati in malora! A dirla tutta, avevo quasi scordato che esisti e non voglio che me lo si ricordi. Sparisci!";
						link.l1 = "Non ci posso credere!";
						link.l1.go = "saga_l1";
					}
					else
					{
						dialog.text = "Eccoti, "+pchar.name+"Ho rimuginato un po’ sulla nostra disgrazia. Non lo chiamerei proprio un piano, ma...";
						link.l1 = "Sono tutt’orecchi, Jan.";
						link.l1.go = "saga_25";
					}
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests_1") // идут три квеста баронов
				{
					dialog.text = "Come vanno le cose? Posso darti una mano in qualcosa?";
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "after_marlow")
					{
						link.l3 = "Ho parlato col Prete Nero. Ahimè, dopo la nostra chiacchierata sono di nuovo qui a chiederti consiglio: sono proprio a corto d’idee.";
						link.l3.go = "shark_hunt_2";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "LSC" && !CheckAttribute(pchar, "questTemp.Saga.BaronReturn"))
					{
						link.l3 = "Ho trovato Dios e ci siamo fatti una bella chiacchierata. Mi ha raccontato parecchie cose interessanti, ma purtroppo non siamo arrivati al sodo.";
						link.l3.go = "shark_hunt_7";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "third_teleport")
					{
						link.l3 = "Oh, Jan. Avrei così tanto da raccontarti che mi ci vorrebbe tutta la notte, quindi cercherò di essere breve.";
						link.l3.go = "return_LSC";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "shamane" && !CheckAttribute(npchar, "quest.shamane"))
					{
						link.l3 = "Ho raccolto Nathaniel Hawk dall’Isola della Giustizia. Ora si trova sulla mia nave.";
						link.l3.go = "nathaniel";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "treatment")
					{
						link.l3 = "Ho lasciato Nathaniel Hawk al villaggio Miskito perché lo curi uno stregone chiamato Occhio di Serpente. Mi ha promesso che rimetterà in sesto Nathan.";
						link.l3.go = "nathaniel_2";
					}
					link.l4 = "Niente di nuovo da raccontarti per ora. Passavo solo a vedere come te la cavi.";
					link.l4.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "fail_centurion") // провал - потоплен Центурион
				{
					dialog.text = "Che si dice di nuovo, "+pchar.name+"? Come vanno le cose?";
					link.l1 = "Oh, non poteva andare peggio. Ho sgobbato come un cane... Ho rintracciato Jackman, abbiamo gettato via i foderi, e l'ho mandato a dormire con i pesci come il più grande degli idioti, insieme a tutto quello che poteva esserci nella sua cabina. Ora non ho niente con cui ripulire il nome di Squalo né per mettere il fuoco addosso a Barbazon. Temo che sia una causa persa, Jan.";
					link.l1.go = "saga_f_1";
					break;
				}
				if(pchar.questTemp.Saga == "calendar") // квесты баронов завершены
				{
					// вторая проверка времени. Отбираем Элен, со Свенсоном нейтральные отношения - ну не выщло и не вышло, хоть попытались. Данни и Натана - в Марун-Таун
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = "Ho sentito delle tue gesta eroiche! Dannie mi ha raccontato brevemente la storia. A proposito, ora siamo amici. E Nathan è cambiato del tutto! Tutta la sua malinconia è svanita quando ha rivisto il suo 'Centurion'.\nMa ho brutte notizie per te, "+pchar.name+"Abbiam perso talmente tanto tempo che i diritti sull’eredità di Sharp sono ormai svaniti e Isla Tesoro s’è fatta base militare inglese. Non posso più far nulla per aiutarti contro Levasseur."link.l1 ="Non ho davvero parole... Abbiamo passato mille peripezie per un pugno di mosche. Davvero non c’è più nulla da fare?";
						link.l1.go = "saga_l2";
					}
					else
					{
						dialog.text = "Ho sentito parlare delle tue imprese! Dannie mi ha messo al corrente. Ah, e abbiamo fatto pace, tra l’altro. Nathan è irriconoscibile, credimi. Appena ha rivisto il suo ‘Centurion’, ha lasciato brontolii e malumori come se fossero nebbia sparita col vento...";
						link.l1 = "Nathan sta meglio? Son lieto di sentirlo!";
						link.l1.go = "saga_26";
					}
					break;
				}
				if(pchar.questTemp.Saga == "mine") // рудник взят
				{
					dialog.text = "Eccoti qua, "+pchar.name+"Adesso ho qualcosa da raccontarti.";
					link.l1 = "Ciao, Jan. Son tutto felice! Che novità? Spero che sia qualcosa di buono?";
					link.l1.go = "saga_32";
					break;
				}
				if(pchar.questTemp.Saga == "mine_1") // рудник взят совместно
				{
					dialog.text = "Eccoti qua, "+pchar.name+"   Hai riposato un po'? Posso dunque pensare che sei di nuovo pronto per nuove, grandi avventure?";
					link.l1 = "Ciao, Jan. Sì, sono pronto.";
					link.l1.go = "saga_32a";
					break;
				}
				if(pchar.questTemp.Saga == "late_l3") // провал по времени у адвоката
				{
					dialog.text = "Che si dice di nuovo, "+pchar.name+"? Come vanno le cose?";
					link.l1 = "Oh.  Le cose vanno proprio a rotoli.  Ho lottato con le unghie e coi denti, ma alla fine ho perso tutto. Come ricorderai, il testamento di Sharp aveva una scadenza. Ebbene, quel termine è ormai passato, e Isla Tesoro è diventata una base militare inglese. Non c'è più nulla da fare, Jan.";
					link.l1.go = "saga_l3";
					break;
				}
				if(pchar.questTemp.Saga == "bakaut") // пришёл от адвоката за деньгами
				{
					dialog.text = "Saluti, "+pchar.name+"! Buone nuove: il Consiglio si è riunito e la Fratellanza della Costa ha trovato un nuovo capo.";
					link.l1 = "Buon pomeriggio, Jan. Son lieto per te.";
					link.l1.go = "saga_44";
					break;
				}
				if(pchar.questTemp.Saga == "sellbakaut" && GetSquadronGoods(pchar, GOOD_SANDAL) >= 1) // отдает бакаут
				{
					dialog.text = "Ebbene, "+pchar.name+"   Hai raggiunto Molligan?";
					link.l1 = "L’ho fatto io. È stato lui a rubarti il legno di ferro.";
					link.l1.go = "saga_55";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut") && GetNpcQuestPastDayParam(npchar, "bakaut_date") >= 1) // за деньгами за бакаут
				{
					dialog.text = "Puntuale come sempre, "+pchar.name+" Ho venduto il legno di ferro che mi hai portato.";
					link.l1 = "Eccellente.   Quanti dobloni hai messo in tasca?";
					link.l1.go = "saga_57";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut_sum")) // сам продал бакаут
				{
					dialog.text = "Ebbene, "+pchar.name+"   Sei riuscito a raggiungere Molligan?";
					link.l1 = "L’ho fatto io. È stato lui a rubarti il legno di ferro. Mi sono imbattuto anche nel suo compratore, un certo comandante olandese. Gli ho venduto la merce.";
					link.l1.go = "saga_59";
					link.l2 = "L'ho fatto. Ho cercato di costringerlo a mostrarmi la stiva... ci siamo presi a sciablate e... addio Molligan. Ma nella stiva non c'è altro che ebano e mogano, te lo giuro.";
					link.l2.go = "saga_59_1";
					break;
				}
				if(CheckAttribute(npchar, "quest.jessika")) // информация о Джессике
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". Novità in vista?";
					link.l1 = "Jan, vorrei parlarti di una certa faccenda. Ho scavato un po’ nel passato della madre di Helen, Beatrice, e mi sono imbattuto in qualcuno che tu conosci fin troppo bene. Per quel che mi è stato detto...";
					link.l1.go = "saga_62";
					break;
				}
				if(pchar.questTemp.Saga == "lastpages") 
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". Come stanno andando le cose? Dal tuo muso, posso già farti i miei complimenti? ";
					link.l1 = "Sì. Finalmente sono riuscito a sistemare tutto questo casino. Helen ha ottenuto tutti i diritti su Isla Tesoro. Mai più nessuno oserà mettere piede nel rifugio dei Fratelli della Costa!";
					link.l1.go = "saga_82";
					break;
				}
				if (pchar.questTemp.Saga == "end") sTemp = "Oh, my friend "+pchar.name+"! Pleased to see you! What brings you here?";
				else sTemp = "Anything else, "+pchar.name+"?";
				dialog.text = sTemp;
				link.l1 = "No, Jan. Nulla per ora.";
				link.l1.go = "exit";
				if(CheckAttribute(npchar, "quest.trade_bakaut")) // торговля бакаутом
				{
					if (GetDataDay() == 14 || GetDataDay() == 28)
					{
						link.l2 = "Jan, vorrei comprare un po’ del tuo legno di ferro.";
						link.l2.go = "trade_bakaut";
					}
				}
				NextDiag.TempNode = "First time";
			}
			else
			{
				// заглушка Элен
				if(startHeroType == 4)
				{
					dialog.text = "Elen, salve, mia cara. Che novità porti? Avevi qualcosa da chiedere?";
					link.l1 = "Salute, Jan! Sempre lo stesso, son passato solo per darti un’occhiata.";
					link.l1.go = "exit";
					NextDiag.TempNode = "First time";
					break;
				}
				dialog.text = "Posso esservi d'aiuto in qualche modo?";
				link.l1 = "No, sto bene.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First time";
			}
		break;
		
		case "saga":
			dialog.text = "Ti riconosco, maledizione! Sei quel capitano impavido che ha salvato Rumba e affrontato a muso duro i cannoni della corvetta inglese! Che piacere vederti! Helen per me è come una figlia. Da oggi ti sarò debitore per tutta la vita. Chiamami pure Jan, o Svenson se preferisci. Dimmi, cosa posso fare per te?";
			link.l1 = "Devo far fuori Levasseur, il governatore di Tortuga. So che arrivare a lui nella sua isola non sarà una passeggiata, quindi son venuto da te per un consiglio.";
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			dialog.text = "Per mille balene, dove sei stato qualche anno fa! Avevo in mente anch’io una bravata simile. Quel dannato ha mandato tutto a monte coi francesi. Ma era un altro tempo allora. Blaze respirava ancora, Shark comandava rispetto, e Nathan faceva il bello e il cattivo tempo a Maroon Town... Ora tutto è andato a ramengo, e che Dio ci aiuti, non in meglio. Sai qualcosa di noi, dei Fratelli della Costa?";
			link.l1 = "Sono appena sbarcato qui, quindi non so praticamente nulla. A parte il fatto che tu e Jackman fate parte del Consiglio.";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			dialog.text = "Oh, non sopporto quel Jackman! Da quando è arrivato lui, sono iniziati все i nostri guai. Rifletterò sulla tua richiesta. Al momento non mi viene nulla in mente.";
			link.l1 = "Ho scoperto qualcosa d’interessante su Jackman.";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			dialog.text = "Uhm. Che cos’è quello?";
			link.l1 = "Jackman sta cercando Gladys Chandler e sua figlia. Dopo aver parlato con Higgins, ho cominciato a pensare che in realtà cerca Rumba. Pare che Gladys non sia la vera madre di Helen, e che il suo cognome fosse Chandler prima di sposare Sean McArthur.";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			dialog.text = "Maledizione! Questa è una pessima notizia. Jackman ora è più forte che mai. E per di più, ho la brutta sensazione che non agisca da solo. Dietro le sue spalle si muove un’ombra minacciosa. Se davvero gli serve Helen, allora la ragazza ha urgente bisogno di qualcuno che la protegga. Temo d’esser ormai troppo vecchio per quel compito...";
			link.l1 = "Non è tutto. Jackman sta anche cercando uno chiamato Henry il Boia, ex nostromo della 'Neptune', della ciurma del capitano Butcher.";
			link.l1.go = "saga_5";
		break;
		
		case "saga_5":
			dialog.text = "Caramba! Le mie peggiori paure si sono avverate! Quel Macellaio e la sua 'Neptune' seminavano il terrore in tutto l’arcipelago. All’epoca niente Fratellanza, ognuno per sé. Quell’uomo ha fatto più danni che tempeste, e una persona a me cara ci ha lasciato la pelle per colpa sua.\nNon ho mai avuto occasione di incontrarlo. La 'Neptune' fu mandata a fondo da una fregata inglese, e il Macellaio finì impiccato a St. John’s. E che se lo porti pure il diavolo! Anche se, a dirla tutta, c’era chi ammirava la sua fortuna e il suo coraggio da pazzo.\nJackman era il suo braccio destro, il primo ufficiale sulla 'Neptune'. Sorpreso? Quei vecchi furfanti ora son diventati eroi della Nazione, tutto merito di Cromwell! Dov’è finita la buona vecchia Inghilterra?\nDobbiamo trovare Henry l’Impiccatore prima che ci arrivino gli uomini di Jackman. Forse ha lui la chiave di quest’intrigo, sempre che sia ancora tra i vivi.";
			link.l1 = "Scommetto che sarebbe più facile pescare un pesce con le mani nude! Almeno hai qualche traccia?";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Conoscevo Enrico quand’era ancora uno sbarbatello. Figlio di una bagascia di Cartagena, per metà spagnolo, anche se si guardava bene dal confessarlo. Sua madre era un vero schianto! Non posso dire che fosse bella, ma di ballerine di flamenco come lei ce n’erano poche. Tutto il casino si fermava a guardare gli spettacoli della nuda Chica Gonzales e delle sue nacchere.  Poveretta. Prese un brutto malanno e si spense come una candela. Fu allora che convinsi Enrico a filare verso Providence, dove si fece presto un nome e si aggregò alla ciurma di Thomas Beltrope, amicone di Nicolas Sharp. Quei due erano gli ultimi cani della regina Elisabetta e facevano tutto insieme. Bei tempi, quelli!  Thomas tornò in Inghilterra quando il compare tirò le cuoia. Si portò dietro la sua gente, ma Enrico rimase nei Caraibi. Navigò sotto diversi capitani finché non spuntò il Macellaio. Si guadagnò quel soprannome per via di una sciabola che non mollava mai, sempre appesa al fianco.";
			link.l1 = "E che cosa ci dice questa informazione?";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Se il Boia ha deciso di nascondersi dai pirati, il posto migliore per lui sarebbe una città spagnola. Soprattutto a casa sua, a Cartagena, dove ha amici e parenti. Henry era piuttosto devoto, quindi dubito che cambierebbe la chiesa del suo santo. Probabilmente porta ancora lo stesso nome di quando era ragazzino: Enrique.";
			link.l1 = "Eh... Poca roba, ma sempre meglio, che restar a mani vuote.";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "Cerca di trovarlo, Charles! Pochi sanno delle radici spagnole di Henry, quindi qui abbiamo un piccolo vantaggio. Intanto penserò a come convincere Rumba a unirsi al tuo equipaggio. Quella ragazza ha più coraggio di tanti uomini, non ha mai servito sotto nessuno che non fosse suo padre.\nMa non ha né nave né uomini, e deve pur campare. Certo, continuerò ad aiutare Gladys come sempre, ma non potrò trattenere Helen a Blueweld ancora a lungo. E un’ufficiale così ti sarà davvero utile. Sean le ha insegnato ogni trucco del mestiere e l’ha cresciuta come se fosse un maschio.\nMi sentirei più tranquillo sapendola sotto il comando di un capitano come te.";
			link.l1 = "Rumba si è dimostrata davvero all’altezza. Gente come lei mi serve nella ciurma. Se riesci a convincerla, la prenderò come ufficiale. Ma prima voglio capire chi sia davvero e perché Jackman la voglia. Temo che, a differenza di Donovan, lui non sia attratto dai suoi vezzi. Cercherò di scovare Hangman, anche se non prometto nulla.";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Ebbene, magnifico. Prendi questa patente della Compagnia Olandese delle Indie Occidentali, valevole tre mesi. Mettici la tua firma, potrà tornarti utile nelle tue ricerche. Nel frattempo rifletterò su ciò che mi hai raccontato riguardo a Levasseur e Tortuga.";
			link.l1 = "Grazie mille! Questo foglio mi tornerà proprio utile. In tal caso, mi metto in rotta per Cartagena.";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			DialogExit();
			GiveNationLicence(HOLLAND, 90);
			AddQuestRecord("Saga", "14");
			pchar.questTemp.Saga = "cartahena";//идем в Картахену
			pchar.quest.Saga_Gonsales.win_condition.l1 = "location";
			pchar.quest.Saga_Gonsales.win_condition.l1.location = "Cartahena_town";
			pchar.quest.Saga_Gonsales.function = "Saga_CreateGonsalesB";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//открыть спальню Элен
			LocatorReloadEnterDisable("FortOrange_town", "reload6", true); // закрыть резиденцию Джекмана
			npchar.greeting = "svenson_3";
			
			AddQuestRecord("HelenDrinking", "1");
			pchar.questTemp.HelenDrinking.CanDrink = true;
			SetFunctionTimerConditionParam("HelenDrinking_NoVisit", 0, 0, 1, 24 - GetHour(), false);
			
			pchar.questTemp.Saga.HelenRelation = 0;
		break;
		
		case "saga_11":
			dialog.text = "Henry è morto? Aspetta, non dirmi che sei stato tu ad accopparlo?";
			link.l1 = "Non guardarmi con quegli occhi spalancati! Non c’entro nulla. È morto per mano sua, divorato dalla sua coscienza e dalla paura di Jackman. Quel vecchio filibustiere aveva il cuore malandato e gli restava poco da vivere. Ecco cosa sono riuscito a scoprire...";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "Per favore, racconta!";
			link.l1 = "Vent’anni fa, Henry doveva consegnare uno scrigno d’oro per conto del Capitano Butcher alla madre adottiva della figlia di sangue. Non c’è alcun dubbio che quella donna fosse la signora McArthur. All’epoca portava il cognome Chandler e viveva a Belize. Ma il destino trattenne il Boia a St. John’s per un intero mese in più, e quando finalmente arrivò a Belize, trovò solo rovine dopo il saccheggio degli spagnoli, e zia Gladys con Sean erano già scappati sotto la tua protezione.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = "";
			link.l1 = "Fecero passare Helen per la loro figlia di sangue e la allevarono come fosse loro. Henry perse le loro tracce e si tenne nell’ombra, ben consapevole della vendetta di Jackman, vivendo per vent’anni nella paura. Pare che Jackman stia cercando la figlia del suo capitano. Ma il perché, questo non lo so.";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "Forse sta eseguendo gli ordini di qualcuno...";
			link.l1 = "Ne dubito. Chi mai potrebbe dargli ordini? Il Macellaio è morto. La sua morte è attestata da documenti ufficiali. Decine, se non centinaia di testimoni l’hanno visto esalare l’ultimo respiro.";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "Forse non si tratta affatto di chi sia il padre di Helen. Forse tutto ruota attorno a sua madre naturale. Ho già un'idea di chi potesse essere, ma temo di ammetterlo. Eppure Gladys! Come ha potuto tenere questo segreto per tanti anni, senza mai svelarlo nemmeno al marito! Sean McArthur me l’avrebbe senz’altro detto. Non abbiamo mai avuto segreti l’uno con l’altro.";
			link.l1 = "Vado a farmi una chiacchierata a cuore aperto con Gladys. Credo di avere i mezzi per farla cantare. Fino alla prossima, Jan!";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			DialogExit();
			pchar.questTemp.Saga = "gladis1";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_history";
			AddQuestRecord("Saga", "21");
		break;
		
		case "saga_17":
			dialog.text = "Dove diavolo hai preso quella roba!?";
			link.l1 = "Me l’ha dato Gladys. Ha detto che era ‘l’eredità della madre di Helen’. Non sapeva come si chiamasse. Qualcosa mi dice che non è un semplice pezzo di carta da buttare.";
			link.l1.go = "saga_18";
		break;
		
		case "saga_18":
			dialog.text = "Ricordi quando ti dissi che avevo un sospetto su chi fosse la vera madre di Helen? Ora ne sono certo. Si chiamava Beatrice Sharp. Era la figlia di sangue del mio maestro e amico Nicholas Sharp, la sorella dichiarata del fondatore della nostra Fratellanza, Blaze Sharp, e comproprietaria di Isla Tesoro. È proprio quel pezzo di mappa che Jackman sta cercando.";
			link.l1 = "Ma guarda un po’! Ma per quale diavolo gli servirebbe mezza mappa d’un’isola?";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "L'isola fu scoperta da Nicolas Sharp. La chiamò Isla Tesoro, la mappò e ne prese possesso tramite la Compagnia di Providence Island, dove godeva di buone conoscenze. \nNicolas scrisse nella sua testimonianza che l'isola poteva essere ereditata solo da chi presentasse entrambe le parti della mappa. Fece ciò per evitare ogni disputa. Consegnò le parti a Beatrice e al figliastro Blaze, prima di morire tragicamente per mano degli spagnoli.";
			link.l1 = "Per mille balene! Che stramberia.";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "Hai ragione. Non fu certo la scelta più saggia. E quel furbo di notaio aggiunse pure che l’isola passerà alla corona inglese, se entro un anno dopo la morte degli eredi nessuno presenterà entrambe le parti della mappa.\nNessuno ci pensò allora, e ora paghiamo pegno per la nostra dabbenaggine. Beatrice è morta vent’anni fa. Tutti questi anni sono volati e ancora non sappiamo dove sia la sua tomba, assieme alla sua metà della mappa. Blaze Sharp è stato assassinato di recente. Anche la sua parte è svanita nel nulla.\nSe nessuno consegnerà la mappa completa di Isla Tesoro alle autorità entro un anno, Sharptown finirà nelle grinfie degli inglesi. Spediranno laggiù un governatore con una guarnigione, e per la Fratellanza sarà la fine.";
			link.l1 = "Che cosa proponi di fare?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "Non possiamo permettere che accada una simile sciagura. Ho bisogno di te, Charles, ho bisogno che tu impedisca che ciò si compia. E potrò aiutarti a sbarazzarti di Levasseur solo quando metteremo le mani su Isla Tesoro e Shark Dodson sarà eletto nuovo capo della Fratellanza. Tra tutti noi, è il più degno. Ti propongo un’alleanza. \nAh, e ho già parlato con Helen. Ha accettato d’imbarcarsi con la tua ciurma.";
			link.l1 = "Non mi lasci altra scelta, Jan. Non posso tornare in Francia senza ristabilire l’onore della mia famiglia. E per farlo devo liberarmi di Levasseur, con o senza il tuo aiuto. Non cerco spargimenti di sangue inutili, e spero tu sappia come prendere Tortuga senza trasformarla in un bagno di sangue. Anche se, lo confesso, mi piacerebbe capire di persona cosa si cela dietro la storia offuscata dell’eredità di Sharps.";
			link.l1.go = "saga_22";
		break;
		
		case "saga_22":
			dialog.text = "Fa piacere sentire parole sensate! Troveremo il modo giusto per prendere Tortuga, te lo giuro io. E allora, andiamo?";
			link.l1 = "Andiamo! Passerò di nuovo più tardi. Intanto, rifletti da dove cominciare ad affrontare la faccenda.";
			link.l1.go = "saga_23";
		break;
		
		case "saga_23":
			dialog.text = "Ritorna tra due o tre giorni. Per allora credo che il mio piano sarà giunto a compimento. E non dimenticare di portare Helen con te sulla tua nave. La poverina si consuma senza il mare. Sarà una compagna leale e potrai sempre contare su di lei senza esitazione.";
			link.l1 = "D'accordo, Jan. Vado subito a prenderla.";
			link.l1.go = "saga_24";
		break;
		
		case "saga_24":
			DialogExit();
			pchar.questTemp.Saga = "helena1";
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);//закрыть выходы из города
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			AddQuestRecord("Saga", "23");
		break;
		
		case "saga_25":
			dialog.text = "Per prima cosa, dobbiamo trovare lo Squalo. Quel furfante voleva sbarazzarsi di Levasseur di persona e ti assicuro che la sua testa è sempre piena di trovate geniali. Certo, potremmo anche convincere Marcus ad accettare la guida: dopotutto è lui il custode del Codice. Ma dubito che ci sarebbe d’aiuto; ha voluto tagliare ogni rapporto con Levasseur e Tortuga. Un uomo tutto d’un pezzo, quello. Non ho la minima idea di dove Steven e i suoi si siano nascosti, ma la sua fregata, la “Fortuna”, è stata avvistata a Puerto Principe. Forse Zachary Marlow, detto anche il Pastore Nero, può indicarci dove cercare lo Squalo. Secondo: dobbiamo ottenere il favore degli altri baroni per eleggere Dodson. E per farlo, bisogna recuperare le loro Schegge Indiane – ovvero i voti. Il nuovo capo deve averne cinque. Così prescrive il Codice quando il vecchio leader è morto.\nAssurdo! Sarebbe ora di cambiare le leggi, ma solo il nuovo capo può farlo. Il mio voto ce l’abbiamo già. Quanto al Pastore Nero, credo che non gliene freghi un accidente di chi comanda a Sharptown. Speriamo che Jackman non gli abbia già parlato. Dovremo anche convincere sia Tyrex sia Jacques Barbazon, che si odiano a morte. Ma tutto questo non conta nulla finché non scopriamo che fine ha fatto lo Squalo. Terzo: prima o poi dovremo far fuori Jackman e trovare qualcun altro al suo posto. Con lui non si tratta.\nPeccato che Hawk sia crepato! Aveva la fiducia della gente e la sua parola ci sarebbe tornata utile. Non troveremo mai un barone migliore per Maroon Town. Pare che Jackman c’entri qualcosa con l’assassinio di Blaze, quindi è anche la chiave per trovare la seconda parte della mappa. Jacob non si fida di nessuno e probabilmente tiene la sua parte della mappa nella cabina della “Centurion”.\nLa famiglia di Hawk possedeva quella fregata, ma Jackman se l’è presa così come si è preso la baronia di Hawk. Se troviamo la seconda parte della mappa in mano a Jackman, sarà un ottimo argomento per far eleggere Steven. Soprattutto agli occhi di Marcus Tyrex, custode del Codice, pignolo com’è con l’onore. Restituiremo a Helen i suoi diritti su Isla Tesoro appena metteremo le mani su entrambe le parti della mappa.\nMa bisogna andarci piano: Jackman non starà certo con le mani in mano a guardare te che frughi in giro.";
			link.l1 = "Ehm... Sto per far visita al Parroco Nero. Dimmi qualcosa su di lui.";
			link.l1.go = "shark_hunt";
			pchar.questTemp.Saga = "baronsquests_1";
		break;
		
		case "shark_hunt":
			dialog.text = "Che diavolo ne so io di cosa gli passa per la testa. A volte sembra proprio un matto da legare, ma secondo me è solo una finta ben recitata. E poi, i suoi uomini sarebbero pronti a menar le mani col demonio in persona pur di difendere il loro caro Pastore.\nHanno messo in piedi una specie di setta protestante che fa concorrenza all’inquisizione spagnola a Cuba. Quindi ti consiglio di non parlare di teologia laggiù, non te la perdonerebbero.";
			link.l1 = "Ne terrò conto...";
			link.l1.go = "shark_hunt_0";
		break;
		
		case "shark_hunt_0":
			dialog.text = "E dunque, "+pchar.name+": non perdere nemmeno un attimo del tuo tempo. Parlo sul serio. Ricordi la clausola nel testamento che dice che se gli eredi non reclamano l’isola entro un anno, Isla Tesoro finirà alla corona inglese, giusto? Ebbene, il tempo non gioca a nostro favore adesso. Quando ci siamo visti l’ultima volta, mancavano solo undici mesi prima che scadesse il termine.";
			link.l1 = "Ricordo, Jan.  Hai ragione, il tempo è oro. Ci sto già lavorando!";
			link.l1.go = "shark_hunt_1";
		break;
		
		case "shark_hunt_1":
			DialogExit();
			AddQuestRecord("SharkHunt", "1");
			pchar.questTemp.Saga.SharkHunt = "begin";
			pchar.GenQuest.LigaAttack = "true"; // киллеры Лиги активированы
		break;
		
		case "shark_hunt_2":
			dialog.text = "Mm... Che ti ha raccontato quel furfante di Zachary?";
			link.l1 = "Prima di sparire, Shark venne a trovarlo e lasciò la sua fregata a Zachary come pegno per una brigantina e un po’ di viveri, poi salpò verso nord-ovest, in direzione di Cuba.";
			link.l1.go = "shark_hunt_3";
		break;
		
		case "shark_hunt_3":
			dialog.text = "Questa puzza proprio di bruciato. Continua.";
			link.l1 = "Un mese dopo Dodson non si fece più vivo e il Reverendo, come da patto, si prese la fregata e la vendette a caro prezzo a un tizio chiamato Paterson. Quanto ai nostri impicci, Zachary accennò che lo Squalo poteva essersela filata verso una leggendaria Isola della Giustizia, che dicono si trovi da queste parti, a nord-ovest di Cuba.";
			link.l1.go = "shark_hunt_4";
		break;
		
		case "shark_hunt_4":
			dialog.text = "Ho sentito parlare dell'Isola della Giustizia. Dicono che ci sia un'isola dove bianchi e neri vivono in pace, insieme da pari. Bagianate messe in giro da sognatori e buontemponi. Però, c'è la possibilità che a Nord-Ovest ci sia davvero una base di contrabbandieri. Una decina d'anni fa si vedevano spesso le loro barche in mare aperto. Portavano ogni sorta di mercanzia a Cuba in cambio di un po' di viveri.";
			link.l1 = "Tesori in cambio di viveri? Anche il Pastore mi ha raccontato dei bucanieri che trafficano in manzi. Una vera contraddizione che cammina.";
			link.l1.go = "shark_hunt_5";
		break;
		
		case "shark_hunt_5":
			dialog.text = "Queste chiacchiere devono pur nascere da чего-то, quelle barche di contrabbandieri o bucanieri navigavano laggiù per qualche motivo. Ricordo che lo Squalo mi raccontava storie della sua gioventù, era una sorta di schiavo in una strana costruzione fatta di relitti nel mezzo del mare. Forse è proprio lì che dobbiamo cercare? Non ne ho idea. Comunque il Pastore non ha tutti i torti, là fuori c’è qualcosa: una base segreta oppure un’isola dove lo Squalo potrebbe essersi rifugiato. Ascolta, naviga fino a Santo Domingo e cerca uno scienziato di nome Jose Dios. È un cartografo spagnolo. Una volta l’ho salvato da canaglie fetide, ho rispetto per la gente istruita. Ti aiuterà, digli solo il mio nome. Vai a Hispaniola, trova Dios e parla con lui. Conosce queste acque meglio di chiunque altro e, se non può aiutarti lui, nessuno potrà.";
			link.l1 = "Va bene, Jan. Sembra un piano. Vado subito!";
			link.l1.go = "shark_hunt_6";
		break;
		
		case "shark_hunt_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "dios";
			AddQuestRecord("SharkHunt", "3");
		break;
		
		case "shark_hunt_7":
			dialog.text = "Peccato davvero. Speravo proprio che José ci avrebbe dato una mano.";
			link.l1 = "Anch'io ci contavo, ma ahimè. Su, non piangiamoci addosso. Mi prenderò ancora un po' di tempo per riflettere su questa faccenda. Allora, Jan, raccontami: come è crepato Falco?";
			link.l1.go = "baron_return";
		break;
		
		case "baron_return":
			dialog.text = "Nessuno ha visto la sua morte, così come nessuno ha mai trovato il suo corpo. È semplicemente sparito diversi mesi fa. Da allora, è la stessa storia che con lo Squalo: nessuna traccia, né viva né morta. Ma a differenza di Steven, Nathan non aveva motivo di nascondersi. Proprio per questo tutti hanno pensato che fosse crepato nella selva. Se non fosse stato per questo, non avrebbero mai acconsentito a eleggere Jackman al suo posto.";
			link.l1 = "Che diavolo ci faceva Hawk nella selva?";
			link.l1.go = "baron_return_1";
		break;
		
		case "baron_return_1":
			dialog.text = "È tutta colpa mia, sono un vecchio rimbambito! L’ho convinto io a occuparsi di quei banditi arrivati di fresco. Non so chi siano, né chi li comandi. Di solito non me ne importerebbe un fico secco, ma hanno cominciato a rapire i Miskitos nostri amici. Il loro capo di guerra Kumvana ha minacciato di intraprendere la via della guerra e mi ha chiesto aiuto. Non ho avuto altra scelta che ficcare il naso.\nFalco è sbarcato con una manciata di uomini sulla Costa dei Mosquitos, ma è finito in una trappola organizzata alla perfezione e poi sconfitto. Pareva proprio che li stessero aspettando. Tra i cadaveri nella giungla, quello di Falco non s’è trovato.";
			link.l1 = "Avete ogni sorta di canagliate che vi ballano sotto il naso! Nessuno degli uomini di Hawk ha provato a sbrogliare la faccenda coi banditi?";
			link.l1.go = "baron_return_2";
		break;
		
		case "baron_return_2":
			dialog.text = "Jackman fu più lesto di tutti. Si autoproclamò risolutore alla riunione della Fratellanza e prese la decisione. I Miskitos smisero di sparire, ma quei furfanti restarono lì, agendo piuttosto nell’ombra. \nJackman disse che non tenevano in ostaggio nessuno di quelli venuti ad attaccarli e che non c’era motivo perché la Fratellanza dichiarasse loro guerra. Hawk fu il primo ad assalirli, dunque, secondo le nostre leggi, i banditi avevano tutto il diritto di difendersi. Tutti furono d’accordo. Tutti tranne...";
			link.l1 = "Tutti tranne chi?";
			link.l1.go = "baron_return_3";
		break;
		
		case "baron_return_3":
			dialog.text = "Nathan aveva una moglie. Si chiamava Danielle Hawk, una vera furia dei sette mari! Non credo che abbia mai superato la perdita del suo capitano, e poi, sospettava qualcosa sin dall’inizio e ha provato a far desistere Hawk. Ricordo che ebbero una lite furibonda per questa faccenda, ma per loro era solo un giorno come un altro.";
			link.l1 = "E dove si trova Danielle adesso?";
			link.l1.go = "baron_return_4";
		break;
		
		case "baron_return_4":
			dialog.text = "Chi lo sa! Jackman si è assicurato che lei lasciasse Maroon Town. Non viene mai a trovarmi. Non ci siamo mai sopportate, è diventata ancora più acida con gli anni, e ora deve proprio odiarmi, visto che probabilmente pensa che sia io la causa delle sue sventure.\nForse sta cercando Hawk da sola, ma che può fare una donna, anche se indossa i calzoni e sa menar di sciabola! A proposito, la sciabola la sa usare sul serio. Non ti consiglio di provocarla se la incontri. E poi non serve a nulla parlare con quei banditi. Hanno messo in piedi un accampamento bello tosto e sono armati fino ai denti.\nSembrano ex-militari, e del mestiere ne sanno parecchio. Non lasciano piede a nessuno sulle loro terre. Dicono che gli spagnoli ci cavavano l’oro, lì. Ma il filone è finito e hanno mollato la miniera. Non ho la minima idea di che diavolo combinano quei bastardi laggiù.";
			link.l1 = "Ebbene, finché nessuno ha visto il cadavere di Hawk, la speranza di trovarlo vivo rimane. Dio solo sa, potremmo persino restituirgli il titolo di barone.";
			link.l1.go = "baron_return_5";
		break;
		
		case "baron_return_5":
			dialog.text = "Eh già, guarda un po’. Prendi questa lettera. Quando incontrerai Steve Dodson, dagli subito. Quel che c’è scritto lì dentro ti assicurerà la pelle, per ogni evenienza.";
			link.l1 = "Grazie, Jan. Ci penserò io, stanne certo!";
			link.l1.go = "baron_return_6";
		break;
		
		case "baron_return_6":
			DialogExit();
			GiveItem2Character(pchar, "letter_svenson");
			AddQuestRecord("BaronReturn", "1");
			pchar.questTemp.Saga.BaronReturn = "begin";
			pchar.quest.Saga_DannyMeeting.win_condition.l1 = "location";
			pchar.quest.Saga_DannyMeeting.win_condition.l1.location = "SantaCatalina_town";
			pchar.quest.Saga_DannyMeeting.function = "Saga_DannyMeeting";
		break;
		
		case "return_LSC":
			dialog.text = "Ehi, perché quella faccia lunga. Sei stanco? Forse un bicchiere di rum ti rimetterebbe in sesto?";
			link.l1 = "Non mi dispiacerebbe...";
			link.l1.go = "return_LSC_1";
		break;
		
		case "return_LSC_1":
			LAi_AlcoholSetDrunk(pchar, 51, 5600);
			dialog.text = "Prendi un bicchiere. Ora, parla.";
			link.l1 = "(bevendo) Ah, ora sì che va meglio... Dunque, Jan, avevate ragione tu e il Parroco Nero. L’Isola della Giustizia esiste davvero. Ci sono stato.";
			link.l1.go = "return_LSC_2";
		break;
		
		case "return_LSC_2":
			dialog.text = "Te l’avevo detto che doveva esserci una base di contrabbandieri laggiù!";
			link.l1 = "In realtà non c'è alcuna base, di nessun tipo. E le dicerie nei Caraibi non mentivano. Neri e bianchi vivono davvero insieme laggiù, certo non sempre in pace, piuttosto come cani e gatti. E l'isola stessa è fatta d'un'infinità di relitti navali.";
			link.l1.go = "return_LSC_3";
		break;
		
		case "return_LSC_3":
			dialog.text = "Non ci posso credere! Scommetto che José Dios sarà assai curioso di sentire la tua storia, ne sono certo. Fagli visita un giorno, mi raccomando.";
			link.l1 = "Lo andrò a trovare più tardi. Ora non è proprio il momento adatto. Ho faccende più urgenti da sbrigare al momento. Ho trovato Nathaniel Hawk sull'isola.";
			link.l1.go = "return_LSC_4";
		break;
		
		case "return_LSC_4":
			dialog.text = "Hai trovato Nathan? È straordinario! Come sta?";
			link.l1 = "Beh... È malato, costantemente ubriaco e sprofondato nella malinconia.";
			link.l1.go = "return_LSC_5";
		break;
		
		case "return_LSC_5":
			dialog.text = "Maledizione, che notizia da far cascare le braccia. Dov'è lui? Sul tuo vascello?";
			link.l1 = "No, è sulla sua nave. Sull’Isola.";
			link.l1.go = "return_LSC_6";
		break;
		
		case "return_LSC_6":
			dialog.text = "Cosa? Non l’hai portato qui? Perché?";
			link.l1 = "Perché non c’era nulla che potesse fermarlo. Sono arrivato sull’isola senza nemmeno una nave.";
			link.l1.go = "return_LSC_7";
		break;
		
		case "return_LSC_7":
			dialog.text = "Maledizione, "+pchar.name+", hai appena assaggiato un goccio di rum e già parli a vanvera come se ti fossi sbronzato fino a perdere i sensi. Che c’è, hai attraversato i Caraibi a nuoto? O ti sei legato delle tartarughe ai piedi?";
			link.l1 = "No, non ho nuotato. Jan, sono arrivato sull’Isola dritto dalla giungla del Continente, proprio come Nathan, grazie a un idolo indiano magico. Ho già raccontato questa storia a troppa gente e sono stufo di dover dimostrare che non sono impazzito, quindi ti dico solo: credimi e basta, va bene!?";
			link.l1.go = "return_LSC_8";
		break;
		
		case "return_LSC_8":
			dialog.text = "Idolo indiano?";
			link.l1 = "Ci sono almeno tre idoli nei Caraibi noti come le statue di Kukulcan: una vicino al villaggio Miskito di West Main, una sul fondo delle acque basse dell’Isola della Giustizia, e un’altra presso il villaggio dei Caraibi a Dominica. Questi idoli, grazie a stregonerie indiane, possono trasportare gli uomini all’istante attraverso tempo e spazio.";
			link.l1.go = "return_LSC_9";
		break;
		
		case "return_LSC_9":
			dialog.text = "";
			link.l1 = "Son passato tra tutte e tre le statue in cerchio e sono uscito proprio dove avevo iniziato il mio viaggio, nel villaggio Miskito. Se non mi credi, posso chiamare Danielle. Ha visto tutto con i suoi stessi occhi!";
			link.l1.go = "return_LSC_10";
		break;
		
		case "return_LSC_10":
			dialog.text = "Danielle? La moglie di Hawk? Era con te?";
			link.l1 = "In parte, sì. È stata lei a trovarmi a Blueweld e mi ha portato al villaggio dei Miskito, da uno stregone che mi ha mandato alla statua magica. Ora mi fa da ufficiale, ma è solo una sistemazione provvisoria, s'intende.";
			link.l1.go = "return_LSC_11";
		break;
		
		case "return_LSC_11":
			dialog.text = "Sono assolutamente sbalordito, "+pchar.name+"! Proprio come dicono gli inglesi. Sei stato svezzato col cucchiaio d’argento, eh? Che figlio di buona donna fortunato! Va bene, ti crederò sulla parola, anche se mi costa. Ma la faccenda con Nathan resta: va tirato fuori dai guai.";
			link.l1 = "Ecco cosa farò. Sto preparando una spedizione all’Isola della Giustizia. Ora ho tutto ciò che mi serve: le coordinate dell’isola e le istruzioni di navigazione.";
			link.l1.go = "return_LSC_12";
		break;
		
		case "return_LSC_12":
			dialog.text = "Fantastico. Posso fare qualcosa per darti una mano?";
			link.l1 = "No, grazie. Ma ho omesso un piccolo dettaglio. Oltre a Nathan, sull’isola ho trovato anche Squalo Dodson.";
			link.l1.go = "return_LSC_13";
		break;
		
		case "return_LSC_13":
			dialog.text = "Dunque, davvero ci è andato! Eh già, "+pchar.name+", hai fatto un lavoro eccellente. E Dodson, come se la cava laggiù? Hai già scambiato due parole con lui, vero?";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			{
				link.l1 = "Non solo ci ho parlato. Siamo diventati anche amici. È stato lui a darmi le rotte per tornare all’Isola. Steven ha accettato di scambiare la cabina della sua nave da guerra con la residenza di Sharptown.";
				link.l1.go = "return_LSC_14";
			}
			else
			{
				link.l1 = "Abbiamo parlato, sì, ma alla fine è stato tutto inutile. Steven è stato ucciso mentre mi trovavo sull’Isola, quando una congiura ordita dal suo nostromo, Chad Kapper, è entrata in gioco.";
				link.l1.go = "return_LSC_17";
			}
		break;
		
		case "return_LSC_14":
			dialog.text = "Ah! E come diavolo ha fatto Squalo a diventare capitano d’una nave da guerra?";
			link.l1 = "La nave giace in una bonaccia eterna da più di mezzo secolo. Lui è in trappola con своей gente sull’Isola. Ecco perché non s’è fatto vedere nei Caraibi per così tanto tempo. Ad ogni modo, presto lo porterò qui e vi racconterà lui stesso le sue avventure.";
			link.l1.go = "return_LSC_15";
		break;
		
		case "return_LSC_15":
			dialog.text = "Non vedo l’ora! Ora le cose cominciano a migliorare. Siamo appena diventati più forti, "+pchar.name+"Quando pensi di salpare di nuovo verso l’Isola?";
			link.l1 = "Proprio ora. Sono venuto qui solo per un attimo per raccontarti le novità, mentre Danielle si sta preparando per la spedizione. Muore dalla voglia di rivedere il suo Nathan. E sai una cosa, Jan? Non è poi così una strega, come dicono.";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_16":
			dialog.text = "Eh?  Beh, forse mi son sbagliato su di lei. Va bene, "+pchar.name+", non ti trattengo oltre. Vai, che la sorte ti accompagni! Aspetterò con ansia il tuo ritorno.";
			link.l1 = "Ci vediamo, Jan.";
			link.l1.go = "return_LSC_19";
		break;
		
		case "return_LSC_17":
			dialog.text = "Chad Kapper? Maledizione, conoscevo quel furfante. Ha fatto fuori Steven? Quel bastardo...";
			link.l1 = "Kapper è morto. Ma Steven non tornerà tra noi, quindi dobbiamo escogitare un modo per tenere insieme le nostre faccende politiche.";
			link.l1.go = "return_LSC_18";
		break;
		
		case "return_LSC_18":
			dialog.text = "Ah! Che peccato... Che c’è da rimuginare? Dovremo solo persuadere Tyrex a guidare la Fratellanza. D’altronde, dopo Blaze, Tyrex – custode del Codice – è la nostra figura più degna. Ma prima bisogna riportare Falco indietro, così almeno avremo un asso nella manica. Quando salpi per l’Isola?";
			link.l1 = "Proprio adesso. Sono venuto qui solo un attimo per raccontarti le novità, mentre Danielle si prepara per la spedizione. Non vede l’ora di rivedere il suo Nathan. E sai che ti dico, Jan? Non è poi una strega così terribile.";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_19":
			DialogExit();
			pchar.questTemp.Saga.BaronReturn = "return_LSC";
			// LSC ждёт своего героя!
			i = FindIsland("LostShipsCity");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			pchar.quest.return_LSC.win_condition.l1 = "location";
			pchar.quest.return_LSC.win_condition.l1.location = "LostShipsCity";
			pchar.quest.return_LSC.function = "LSC_ReturnCheckShips"; // проверка типов кораблей
			pchar.quest.return_LSC_attack.win_condition.l1 = "location";
			pchar.quest.return_LSC_attack.win_condition.l1.location = "Beliz";
			pchar.quest.return_LSC_attack.function = "LSC_ReturnJackmanAttack"; // атака наймитов Джекмана
			pchar.quest.return_LSC_main.win_condition.l1 = "Ship_location";
			pchar.quest.return_LSC_main.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.return_LSC_main.function = "LSC_ReturnMain"; // основная функция возвращения
		break;
		
		case "nathaniel":
			dialog.text = "Come sta? Hai detto che non si sentiva bene.";
			link.l1 = "Sì, proprio così. Lo porterò con me al villaggio dei Miskito, dove il vecchio Occhio di Serpente, lo sciamano, saprà curarlo.";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "Allora, non c’è tempo da perdere! Sbrigati, "+pchar.name+"Non appena avrai consegnato Nathan al tuo stregone, torna subito da me.";
			link.l1 = "Va bene, Jan. Sembra proprio un buon piano.";
			link.l1.go = "exit";
			npchar.quest.shamane = "true";
		break;
		
		case "nathaniel_2":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				if (CheckAttribute(npchar, "quest.shark")) //и на месте
				{
					dialog.text = "Benissimo. Steven è già passato a trovarmi. Ora possiamo finalmente riprendere a discutere i nostri piani.";
					link.l1 = "Sono tutto orecchi, Jan.";
					link.l1.go = "barbazon";
				}
				else
				{
					dialog.text = "È gentile da parte tua, certo, ma perché Dodson non è ancora venuto a trovarmi? Che c’è, l’hai lasciato sull’isola?";
					link.l1 = "Hm... Avevo fretta di portare Nathan da Occhio di Serpente...";
					link.l1.go = "nathaniel_wait";
				}
			}
			else
			{
				dialog.text = "Va bene. Il mio cuore piange per Shark. Ma così va la vita, quindi Tyrex prenderà il suo posto. Bene, ora possiamo finalmente continuare a discutere i nostri piani.";
				link.l1 = "Sono tutto orecchi, Jan.";
				link.l1.go = "barbazon";
			}
		break;
		
		case "nathaniel_wait":
			dialog.text = "... e ti sei scordato di portare Squalo? Non ci posso credere, "+pchar.name+"Porta Steven a Blueweld subito! Mi hai sentito? Vai!";
			link.l1 = "Calmati, Jan. Penserò a tutto io.";
			link.l1.go = "exit";
			NextDiag.TempNode = "nathaniel_wait_1";
		break;
		
		case "nathaniel_wait_1":
			if (CheckAttribute(npchar, "quest.shark"))
			{
				dialog.text = "Steven è passato a trovarmi. Ora finalmente possiamo riprendere a discutere i nostri piani.";
				link.l1 = "Sono tutto orecchi, Jan.";
				link.l1.go = "barbazon";
			}
			else
			{
				dialog.text = "Oh, "+pchar.name+"... Mi pare che ultimamente tu abbia tracannato troppo rum. Vedi, non porta mai a nulla di buono. Prima ti tremano le mani, poi perdi la memoria, e alla fine ti arriva la macchia nera...";
				link.l1 = "Ho capito, Jan. Vado subito a recuperare Steven!";
				link.l1.go = "exit";
				NextDiag.TempNode = "nathaniel_wait_1";
			}
		break;
		
		case "barbazon":
			dialog.text = "Il Pastore Nero è stato chiarissimo, vuole solo quel libro di teologia. Ho mandato i miei uomini a cercarlo, magari qualcuno lo trova. Marcus Tyrex non ci darà problemi, lo convinceremo senza fatica. Jackman ha lasciato Maroon Town subito dopo la tua visita. È salpato da qualche parte sulla 'Centurion', la fregata degli Hawks.\nResta solo Barbazon – detto anche Jacques il Gentiluomo. Dobbiamo trovare il modo di farlo collaborare con noi. Non so ancora come riuscirci. Ma una cosa è certa: dovresti fargli visita.";
			link.l1 = "Raccontami di Barbazon."; // Addon 2016-1 Jason пиратская линейка патч 17/1
			link.l1.go = "barbazon_1";
		break;
		
		case "barbazon_1":
			dialog.text = "Tipo misterioso. Fa finta d'essere squattrinato, ma forse è il più ricco di tutti i Caraibi. Tiene in pugno ogni traffico di contrabbando dell'Oriente. Se non fosse per Marcus che gli tiene testa, dominerebbe tutto il commercio clandestino nelle Isole Sopravento. Tyrex gli è come una lisca di pesce piantata in gola.\nSempre a beccarsi durante i consigli, ma Barbazon non ha fegato per dichiarar guerra aperta. Forse davvero fu pirata di Dunkerque, come si vanta, ma adesso mi pare più uno strozzino che un lupo di mare.";
			link.l1 = "Come diavolo ha fatto a farsi eleggere barone?";
			link.l1.go = "barbazon_2";
		break;
		
		case "barbazon_2":
			dialog.text = "Oro, amico mio, comanda su tutto e ovunque: chi ha l’oro detta legge. Inoltre, Barbazon ha un talento diabolico nell’inventare ogni sorta di affari lucrosi e fuori legge. Lui non si sporca mai direttamente, ma la sua fetta la pretende sempre. Così attorno a lui ronza вrava marmaglia, per lo più zucche vuote, che senza di lui morirebbero di fame o finirebbero dritti al patibolo.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				link.l1 = "Mi ricorda Marcus... Jan, il fatto è... Non ho la minima idea di come avvicinarmi a Barbazon. C'è un problema di cui tu non sai nulla.";
				link.l1.go = "barbazon_5";
			}
			else
			{
				link.l1 = "Come si va a Barbazon?";
				link.l1.go = "barbazon_3";
			}
		break;
		
		case "barbazon_3":
			dialog.text = "Fingi semplicemente d'essere uno di quegli sciocchi che aspettano una soffiata per un bel colpo. Non t'azzardare nemmeno a fregargli la parte. Il buon Barbazon non perdona.";
			link.l1 = "Non c’è nemmeno bisogno di dirlo. Non mi impiccio con lui per tornaconto personale. Ad ogni modo, è ora di fargli visita.";
			link.l1.go = "barbazon_4";
		break;
		
		case "barbazon_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "1");
			pchar.questTemp.Saga.BarbTemptation = "begin";
			pchar.questTemp.Saga.BaronReturn = "barbazon";
			NextDiag.CurrentNode = "First time";
			// тут вычищаем квестовый мусор от LSC
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
			if (CheckCharacterItem(pchar, "letter_chad_1")) RemoveItems(pchar, "letter_chad_1", 1);
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "barbazon_5":
			dialog.text = "Davvero? Sputa il rospo.";
			link.l1 = "Hai mai sentito parlare di Charlie Prince?"; 
			link.l1.go = "barbazon_6";
		break;
		
		case "barbazon_6":
			dialog.text = "Sì, ho sentito le voci. Quel tizio lavorava per Marcus Tyrex fino a poco tempo fa. In poco tempo ha fatto un bel casino, s’è fatto un nome saccheggiando Cartagena. E allora?";
			link.l1 = "Questo tizio sono io. Io sono Charles il Principe. Ero, almeno. Ora capisci?"; 
			link.l1.go = "barbazon_7";
		break;
		
		case "barbazon_7":
			dialog.text = "Per mille balene! Sei tu il Principe Charlie? Che colpo di scena!"+pchar.name+", Sono impressionato! Ora capisco da dove ti viene questa presa... Ma che c'entra Barbazon in tutto questo?";
			link.l1 = "Che ne diresti, Jan, se il Principe facesse visita a Barbazon?"; 
			link.l1.go = "barbazon_8";
		break;
		
		case "barbazon_8":
			dialog.text = "Hm... Capisco. Hai già avuto a che fare con lui prima d’ora?";
			link.l1 = "Non proprio. Uno dei suoi scagnozzi, tale Ignacio Marco, ha provato a farmela pagare su ordine diretto di Barbazon. Era parte della loro guerra da quattro soldi."; 
			link.l1.go = "barbazon_9";
		break;
		
		case "barbazon_9":
			dialog.text = "Ti ha visto in faccia? Gli hai fatto le presentazioni?";
			link.l1 = "No."; 
			link.l1.go = "barbazon_10";
		break;
		
		case "barbazon_10":
			dialog.text = "Non vedo dunque alcun problema. Avevo sentito parlare di quel corsaro Charlie Prince, ma non sapevo che fossi tu finché non me l’hai detto.";
			link.l1 = "Pensi che Barbazon non vedrà attraverso le mie menzogne?"; 
			link.l1.go = "barbazon_11";
		break;
		
		case "barbazon_11":
			dialog.text = "Come avrebbe potuto, se non ha mai visto la tua faccia? Tutto ciò che ha fatto è stato ordinare di sbarazzarsi di uno degli uomini di Marcus.";
			link.l1 = "Hm... Potresti aver ragione su questo."; 
			link.l1.go = "barbazon_12";
		break;
		
		case "barbazon_12":
			dialog.text = "Non ce la caveremo senza Barbazon. Vai a trovarlo, ma fa’ attenzione. Se ti riconosce, scappa a gambe levate, troveremo un altro modo per avvicinarlo.";
			link.l1 = "D’accordo. Ora dovrei andare. Non vedevo l’ora di incontrare quel bastardo."; 
			link.l1.go = "barbazon_13";
		break;
		
		case "barbazon_13":
			dialog.text = "Non fare il fesso e non provare a fregare Jacques. Quello non perdona mai. Gioca la parte dell’allocco smanioso di far soldi facili.";
			link.l1 = "Il mio ruolo preferito, a quanto pare... Addio, Jan!"; 
			link.l1.go = "barbazon_4";
		break;
		
		case "saga_26":
			dialog.text = "Sì. Lo stregone indiano ha fatto tutto il possibile, Hawk è tornato come nuovo. Dovrebbe già essere a Maroon Town con Dannie, quindi se vuoi, vai pure a salutarli. Saranno contenti di vederti.";
			link.l1 = "Passerò senz'altro a vedere come se la cavano... Jan, sono riuscito a mettere le mani sulla seconda parte della mappa di Sharp! Stava nella cabina di Jackman. Ora nessuno potrà negare i diritti di Helen su Isla Tesoro.";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			dialog.text = "Benissimo, mostramelo.\nAvevamo ragione, Jacob è stato lui a far fuori Blaze. Ora la macchia sul nome di Squalo va cancellata per sempre. Quanto alle prove... è una faccenda più delicata. Bisogna rifletterci sopra con molta attenzione, prima di agire.";
			link.l1 = "Un'altra faccenda, Jan. Guarda un po' questo biglietto. Era pure tra la roba di Jackman.";
			link.l1.go = "saga_28";
		break;
		
		case "saga_28":
			RemoveItems(pchar, "letter_parol", 1); // удалить записку
			dialog.text = "Vediamo un po'... Ah, dunque ecco perché quei mascalzoni hanno dato retta a Jackman e smesso di rapтire i miskito! Non poteva finire altrimenti! Quel furfante l’aveva tutto architettato ed era avanti di diverse lunghezze.";
			link.l1 = "Già, e capisco pure perché gli uomini di Hawk sono stati massacrati. Ma ci sono due cose che proprio non mi tornano: primo, che ci fanno i complici di Jackman nella miniera? E secondo, come mai te la prendi così comoda mentre tutto questo caos succede nei tuoi domini?";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "Mi vergogno... Hai ragione. Jackman è proprio sfuggito di mano. E i suoi sgherri non hanno alcun diritto di mettere piede nei miei mari. Pare sia giunta l’ora di rammentare ai Caraibi con chi hanno a che fare.";
			link.l1 = "Che hai in mente, Jan?";
			link.l1.go = "saga_30";
		break;
		
		case "saga_30":
			dialog.text = "Rievocando il passato... Ho intenzione di radunare una spedizione punitiva e spazzare via ogni canaglia che infesta le miniere. Ora abbiamo la prova che sono uomini di Jackman, e sta a me ripulire le mie terre da questa marmaglia.\n"+pchar.name+", hai fatto un lavoro eccellente. Ora tocca a me darmi una mossa. Tu riposati un po'. Vai a trovare i Falchi. Torna tra dieci giorni!";
			link.l1 = "Va bene, Jan.   Lo farò. Tornerò esattamente quando hai detto!";
			link.l1.go = "saga_31";
			link.l2 = "Ah! Voglio anch'io unirmi a questa crociata. Perché mai mi condanni all’ozio mentre gli altri si danno da fare?";
			link.l2.go = "saga_31_1";
		break;
		
		case "saga_31_1":
			dialog.text = "Perdonami, vecchio mio. Ho solo pensato che forse fosse giunta l’ora che io mi dessi da fare, mentre tu potessi finalmente tirare il fiato. Ma se così vuoi, sarò più che lieto! Affrontiamo la tempesta insieme! E tutto ciò che troveremo nella miniera lo divideremo equamente tra i nostri equipaggi, come prescrivono le leggi dei Fratelli.";
			link.l1 = "Affare fatto, Jan! Quando salpiamo?";
			link.l1.go = "saga_31_2";
		break;
		
		case "saga_31_2":
			dialog.text = "Vieni coi tuoi uomini alla Costa dei Mosquitos fra tre giorni. Avrò già radunato la mia ciurma e ti aspetterò laggiù. Non tardare!";
			link.l1 = "Va bene, Diavolo della Foresta. Non vedo l’ora di menar le mani spalla a spalla con te! A presto!";
			link.l1.go = "saga_31";
			npchar.quest.mine_tw = "true";
		break;
		
		case "saga_31": 
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if (CheckAttribute(npchar, "quest.mine_tw"))
			{
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1 = "location";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1.location = "Shore53";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2 = "Timer";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.hour  = sti(GetTime());
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.function = "Saga_MineBanditsPrepareAttack";
				SetFunctionTimerCondition("Saga_MineBanditsAttackOver", 0, 0, 4, false); // таймер
			}
			else SetFunctionTimerCondition("Saga_MineBanditsDestroyed", 0, 0, 10, false); // таймер
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // наверно не нужно
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
		break;
		
		case "saga_32a":
			dialog.text = "Eccellente. Ho scovato qualcosa sul misterioso proprietario della miniera, Lawrence Beltrope.";
			link.l1 = "Allora, chi sarebbe questa donnina?";
			link.l1.go = "saga_35";
		break;
		
		case "saga_32":
			dialog.text = "Ho strappato la verità agli scagnozzi di Jackman nella miniera. Razza di ossi duri, ma i miei non sono nati ieri, sai. In più, siamo riusciti a farli abbassare la guardia dopo avergli sussurrato la parola d’ordine che hai trovato tu. Siamo entrati nella miniera e li abbiamo spediti all’altro mondo con tanto di fuochi d’artificio.";
			link.l1 = "Hai preso la miniera? Straordinario!";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "Che questo serva da lezione a chiunque pensi che il Diavolo della Foresta sia arrugginito. Ho davvero bighellonato troppo in questi anni, ed ecco il risultato! Jackman tramava le sue malefatte proprio sotto il mio naso!";
			link.l1 = "Che hai visto in quella miniera? Raccontami tutto, avanti!";
			link.l1.go = "saga_34";
		break;
		
		case "saga_34":
			dialog.text = "La miniera fu davvero abbandonata dagli spagnoli, ma Lawrence Beltrope di Port Royal l'ha comprata per quattro soldi e ha continuato a sfruttarla di nascosto. Pare che gli spagnoli abbiano mollato la vena troppo presto, perché anche se noi oro non ne abbiamo visto, abbiamo trovato diversi schiavi che giurano che fino a poco fa ce n’era in abbondanza.";
			link.l1 = "Lawrence Beltrope? Mai sentito nominare. Chi diavolo sarebbe costui?";
			link.l1.go = "saga_35";
		break;
		
		case "saga_35":
			dialog.text = "È un locale, figlio di Thomas Beltrope, che un tempo fu fratello giurato di Nicholas Sharp e corsaro per la Compagnia dell’Isola di Providence. Conoscevo bene Thomas, davvero. Un anno fa, Lawrence è tornato nei Caraibi. E guarda un po’, Jackman lavorava per lui. Tienilo a mente e stai all’erta!";
			link.l1 = "Dunque, questo misterioso 'capo' di Jackman, di cui si parlava in quella lettera, è Lawrence Beltrope... D'accordo, quel nome me lo segno.";
			link.l1.go = "saga_36";
		break;
		
		case "saga_36":
			dialog.text = "Un'ultima cosa. Mi torna in mente qualcosa di strano. Blaze una volta parlò di una vecchia miniera d'oro spagnola abbandonata e diceva che avrebbe investito quell'oro a Sharptown. Ma la mappa della miniera sparì quando sua sorella scappò col capitano Butcher. Forse parlava proprio della nostra miniera?\nBah, è passato tanto tempo e ormai non cambia granché... Tu ed io dobbiamo occuparci del Consiglio. Hai raccolto tutte e cinque le schegge?";
			link.l1 = "Sì. Questi quattro: Nathaniel, Tyrex, Marlow e Barbazon. Tutti quanti hanno dato il loro sì.";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			sTemp = "Shark";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Tyrex";
			dialog.text = "Magnifico. Son certo che non ci saranno intoppi nell'elezione "+sTemp+" come capo della Fratellanza della Costa. Mi metterò subito all’opera per convocare il Consiglio.";
			link.l1 = "Allora Jan, possiamo dire che per ora tutto sia sotto controllo? Nathaniel sta a Maroon Town, Jackman è crepato e la Fratellanza ha un nuovo capo... Forse è il momento di tornare da dove tutto ebbe inizio, cioè riprenderci Tortuga?";
			link.l1.go = "saga_38";
		break;
		
		case "saga_38":
			dialog.text = "Ricordo, "+pchar.name+", ma dobbiamo avere ancora un po' di pazienza. Oltretutto, il tempo per sistemare l’eredità di Sharp sta per scadere e quella faccenda, come ben sai, va risolta sul serio.";
			link.l1 = "Che problema c'è con l'eredità? Ho entrambe le parti della mappa. Dobbiamo solo mostrarle e il gioco è fatto...";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = ""+pchar.name+", Ti assicuro che ormai non regalano più isole a chi capita. Nemmeno ai legittimi eredi con tutti i documenti in regola. Le autorità inglesi bramano quest’isola, lo so fin troppo bene.\nNon credo proprio che il colonnello Doyle starà lì a guardare mentre ci riprendiamo un’isola che ormai considera inglese. E poi, sarebbe meglio per noi due restare nell’ombra.";
			link.l1 = "E che cosa proponi?";
			link.l1.go = "saga_40";
		break;
		
		case "saga_40":
			dialog.text = "Dirigiti a Port Royal e cerca un uomo di nome Albert Loxley. È il miglior avvocato di tutti i Caraibi. Ormai si destreggia con maestria in ogni sorta di faccenda losca, quindi accetta qualsiasi incarico se la paga è da re. Ha un appetito da balena, ma vale ogni doblone.";
			link.l1 = "Pensi che il testamento di Sharp possa nascondere qualche tranello?";
			link.l1.go = "saga_41";
		break;
		
		case "saga_41":
			dialog.text = "Non è che lo pensi soltanto, ne sono certo. Hai mai dovuto trattare con funzionari? Sappi che se vogliono qualcosa da te, ti strapperanno l’anima, ti faranno notare ogni virgola fuori posto, gireranno tutto a modo loro e ti lasceranno nudo come un gattino cieco.\nEcco perché sono nati gli avvocati. Combattano la burocrazia con le stesse armi: chiacchiere, inchiostro a fiumi e cavilli. Quindi, va’ a trovare Loxley e ingaggialo per difendere i nostri interessi, mentre io mi occupo delle elezioni.";
			link.l1 = "D'accordo. Salpo per Port Royal. Quanto tempo ci vorrà prima che il Consiglio si raduni e tenga le elezioni?";
			link.l1.go = "saga_42";
		break;
		
		case "saga_42":
			dialog.text = "Dieci giorni. Quindi non ti scomodare a cercarmi a Blueweld prima di allora.";
			link.l1 = "Capito. Allora, Jan. In tal caso, ci si rivede fra poco!";
			link.l1.go = "saga_43";
		break;
		
		case "saga_43":
			DialogExit();
			AddQuestRecord("Testament", "1");
			pchar.questTemp.Saga = "loxly"; // обновляем флаг
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			SetFunctionTimerCondition("Saga_GoldForLoxly", 0, 0, 10, false); // таймер
		break;
		
		case "saga_44":
			sTemp = "Steven Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = ""+sTemp+" ti manda i suoi più calorosi saluti. Sarà sempre lieto di riceverti nella sua dimora a Isla Tesoro. Fai visita quando se ne presenterà l’occasione.";
			link.l1 = "Per essere ben sicuro "+sTemp+" non lascerà la sua nuova dimora, Jan, ci tocca sporcarci le mani, tu ed io.";
			link.l1.go = "saga_45";
		break;
		
		case "saga_45":
			sTemp = "four hundred and fifty";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "one thousand";
			dialog.text = "Suppongo che tu abbia già fatto visita a Loxley...";
			link.l1 = "Sì, l’ho trovato. Prenderà in mano la nostra causa, ma ha preteso una montagna d’oro per i suoi servigi. "+sTemp+" dobloni in anticipo. In anticipo! E dovremo pure sganciare ancora di più, a seconda di come andrà la prova dei diritti di Helen. La cifra raddoppierà o triplicherà, così ha detto.";
			link.l1.go = "saga_46";
		break;
		
		case "saga_46":
			dialog.text = "Ah! Beh, non mi aspettavo nulla di meno da un vecchio marpione come lui. Sente l’odore della preda a miglia di distanza, proprio come una iena. D’altronde, qui si tratta di un’isola intera. Sarebbe una follia pensare che Albert non chiederebbe almeno qualche centinaio. Quindi, la somma totale potrebbe aggirarsi intorno a millecinquecento dobloni d’oro...";
			link.l1 = "Jan, è una montagna di soldi!";
			link.l1.go = "saga_47";
		break;
		
		case "saga_47":
			dialog.text = "So cosa vuoi dire. Capisco che non sei uno sciocco che tira fuori tutto quell’oro dal proprio borsello. Ma purtroppo, al momento non ho una simile somma nascosta da parte. Avevo previsto tali spese, ma l’intervento di un furfante ha mandato tutto all’aria.";
			link.l1 = "Di che diavolo stai blaterando?";
			link.l1.go = "saga_48";
		break;
		
		case "saga_48":
			dialog.text = "Ascolta. Forse già sai che il nostro insediamento è solo mezzo legale. Gli inglesi tengono qui una guarnigione e noi li riforniamo di mogano a buon prezzo. Ma esiste una varietà di legno molto pesante e resistente – il Lignum Vitae, che dovresti conoscere come legno di ferro.\nÈ raro e difficile da lavorare persino con l'acciaio temprato. Si dice che tanto tempo fa i Maya-Itza fabbricassero con esso le loro temute mazze. Non puoi comprare il legno di ferro al mercato aperto e quello di contrabbando costa quanto argento.\nGli uomini di Doyle ogni tanto arrivano e si prendono tutto quello che abbiamo lavorato, per due soldi. Ma io riesco sempre a metterne via un po' per i miei bisogni.";
			link.l1 = "Ho sentito parlare di quest’albero. Dicono che le palle di moschetto vi affondano dentro come pece, tanto il suo legno è unto! Robusto al punto da farci ruote d’ingranaggi per meccanismi d’acciaio.";
			link.l1.go = "saga_49";
		break;
		
		case "saga_49":
			dialog.text = "Stanno raccontando qualche fandonia sui meccanismi, ma il resto corrisponde alla verità. Così, prevedendo le spese, avevo messo da parte una bella partita di legno di ferro, eppure qualche malnato ha svuotato il mio magazzino un paio di giorni fa. È uno dei nostri, ne sono certo. Ho un sospetto, ma non posso giurarlo.";
			link.l1 = "I topi vanno schiacciati! Chi sospetti, dunque?";
			link.l1.go = "saga_50";
		break;
		
		case "saga_50":
			dialog.text = "Paul Molligan. Il suo 'Oyster' delle Indie Orientali è salpato per Barbados ieri. Non ho avuto occasione di controllare le sue stive. Ma non porterebbe comunque il legno di ferro a Bridgetown, laggiù lord Willoughby ha doganieri severi e il legno di ferro è materia prima di grande valore per la marina inglese.\nSe davvero ha il mio legno di ferro, lo venderà prima di arrivare a Bridgetown. Se solo potessi intercettare Molligan e dare un’occhiata alle sue stive!..";
			link.l1 = "Dici che è salpato per Bridgetown ieri? Non tutto è ancora perduto. Proverò a raggiungerlo.";
			link.l1.go = "saga_51";
		break;
		
		case "saga_51":
			dialog.text = "Sai cosa devi fare, se Molligan è davvero la spia. Ma prima cerca di scoprire il nome del suo mandante. Così potrai consegnare tu stesso il carico al cliente... oppure riportarlo a me.\nPorta anche l’‘Ostrica’ a Blueweld, è una nave di tutto rispetto, la vorrei per me stesso e la rimetterei a nuovo a mio piacere. Sei libero di prenderti quello che vuoi come bottino... E se per caso Molligan non fosse il colpevole... no, sono certo che è proprio quella canaglia a cui devo il furto del mio ferro nero.";
			link.l1 = "Farò buon uso del mio tempo!";
			link.l1.go = "saga_52";
		break;
		
		case "saga_52":
			dialog.text = "Se venderai tu stesso il legno di ferro, metti da parte millecinquecento dobloni d’oro per Loxley e il resto lo dividiamo a metà. Mi posso fidare di te, vero?";
			link.l1 = "Ma certo. Non sono mica una spia, io.";
			link.l1.go = "saga_53";
		break;
		
		case "saga_53":
			dialog.text = "Non ne dubito. Buona fortuna, "+pchar.name+"! Spero che ti sorrida questa volta.";
			link.l1 = "Grazie. A presto!";
			link.l1.go = "saga_54";
		break;
		
		case "saga_54":
			DialogExit();
			pchar.questTemp.Saga = "molligan"; // обновляем флаг
			AddQuestRecord("Testament", "3");
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			Saga_CreateMolliganInWorld(); // ставим корабль Моллигана на карту
		break;
		
		case "saga_55":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "Lo sapevo. Quanta roba aveva nelle sue stive?";
			link.l1 = "Ho trovato "+FindRussianQtyString(sti(npchar.quest.bakaut))+" sulla 'Ostrica'.";
			link.l1.go = "saga_56";
		break;
		
		case "saga_56":
			iTemp = sti(npchar.quest.bakaut);
			if (iTemp > 100)
			{
				dialog.text = "Per la miseria! Mai visto tanto bottino nel mio magazzino. Guarda un po’ chi s’è riempito le mani d’oro. Grazie, "+pchar.name+", non mi deludi mai. Vendo subito la merce, abbiamo già un compratore. Domani ti procuro i dobloni.";
				link.l1 = "D’accordo. Non ti trattengo oltre, allora. A domani.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 90 && iTemp < 101)
			{
				dialog.text = "Sì, ne ho avuto abbastanza. Maledetto topo! Grazie, "+pchar.name+", non mi deludi mai. Vendo subito la mercanzia, ho già trovato un compratore. Domani avrai i tuoi dobloni.";
				link.l1 = "Va bene. Non ti trattengo oltre allora. Ci si vede domani.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "Avrà già smerciato parte del carico a qualcuno, perché doveva essercene di più. Ma non importa, la maggior parte l’abbiamo recuperata. Grazie, "+pchar.name+", venderò subito la merce, abbiamo già un compratore. Domani avrai i tuoi dobloni.";
				link.l1 = "D'accordo. Non ti trattengo oltre, allora. A domani.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 50 && iTemp < 70)
			{
				dialog.text = "Maledizione, quel bastardo è già riuscito a smerciare una bella fetta del carico... Eh, che peccato. Pazienza. Venderò ciò che mi resta, ho già un compratore. Domani avrò i dobloni in tasca.";
				link.l1 = "D'accordo. Non ti trattengo oltre, allora. Ci vediamo domani.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 20 && iTemp < 50)
			{
				dialog.text = "Maledizione, che disgrazia! Quel bastardo è già riuscito a smerciare più della metà del carico... Ah, che peccato. Pazienza. Quel che mi resta lo piazzerò io, ho già trovato un compratore. Domani avrò i dobloni in mano.";
				link.l1 = "D'accordo. Non ti trattengo oltre allora. Ci vediamo domani.";
				link.l1.go = "saga_oust";
				break;
			}
			dialog.text = "Amico, la mia fortuna è proprio andata a fondo. Ha venduto quasi tutto... Tieni, prendi questo legno di ferro per te, "+pchar.name+", fanne ciò che ti pare. Sei la mia unica speranza di mettere insieme qualche moneta adesso.";
			link.l1 = "Va bene. Cercherò io stesso, allora. Non è la mia prima scorribanda... Addio, Jan.";
			link.l1.go = "saga_oust";
		break;
		
		case "saga_oust":
			if (CheckAttribute(npchar, "quest.bakaut"))
			{
				if (sti(npchar.quest.bakaut) < 20) DeleteAttribute(npchar, "quest.bakaut");
				else 
				{
					SaveCurrentNpcQuestDateParam(npchar, "bakaut_date");
					RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(npchar.quest.bakaut));
				}
				pchar.questTemp.Saga = "removebakaut";
			}
			int iUst = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_EASTINDIAMAN && sld.ship.name == "Oyster") iUst = 1;
				}
			} // есть ли у нас Устрица
			dialog.text = "Aspetta! Hai catturato l’‘Ostrica’?";
			if (iUst == 1)
			{
				link.l1 = "Sì. È in porto proprio adesso. L’ho ormeggiata per te, come avevi chiesto.";
				link.l1.go = "saga_oust_yes";
			}
			else
			{	
				link.l1 = "No. La nave era così malridotta dopo la battaglia che ho dovuto mandarla a fondo.";
				link.l1.go = "saga_oust_no";
			}
		break;
		
		case "saga_oust_no":
			dialog.text = "Che peccato. Ma tant’è. Ci si rivede, "+pchar.name+"!";
			link.l1 = "Addio, Jan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_oust_yes":
			dialog.text = "Straordinario! Armerò questa bellezza come si deve. E poi potrai sempre prenderla in prestito per un po', proprio come pattuito. Credo che tra un paio di mesi sarà pronta.";
			link.l1 = "D'accordo. Una nave come questa potrebbe tornare davvero utile, a volte... A presto, Jan!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_RemoveOuster");
			npchar.quest.ouster = "true";
			SaveCurrentNpcQuestDateParam(npchar, "ouster_date"); // через 2 месяца
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_57":
			int idlt;
			iTemp = sti(npchar.quest.bakaut)*30; // Ян за 1 шт бакаута даёт 30 дублонов
			if (iTemp > 1600)
			{
				idlt = makeint(iTemp-1500)/2; // доля Бонса :)
				dialog.text = "Ho ricevuto "+iTemp+" monete per questo. Millecinquecento sono per l’avvocato, e il resto dei dobloni è la tua parte - "+idlt+"Ecco qua.";
				link.l1 = "Lodevole! Ora posso salpare senza indugio per Loxley.";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500+idlt);
				break;
			}
			if (iTemp > 1450 && iTemp <= 1600)
			{
				dialog.text = "Ho ricevuto millecinquecento dobloni per questo. Bastano appena per il leguleio. Tieni, prendi.";
				link.l1 = "Fantastico. Ora posso salpare per Loxley.";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500);
				break;
			}
			dialog.text = "Ho ricevuto "+iTemp+" dobloni per questo. Ecco qua. Il resto dovrai scavarlo da solo.";
			link.l1 = "Ebbene, se devo arrangiarmi da solo, che sia. Va bene, mi metto in cammino verso Loxley.";
			link.l1.go = "saga_58";
			TakeNItems(pchar, "gold_dublon", iTemp);
		break;
		
		case "saga_58":
			DialogExit();
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.bakaut");
		break;
		
		case "saga_59":
			dialog.text = "E allora? Curioso davvero. E quanto sarebbe disposto a sborsare quell’olandese per il malloppo?";
			link.l1 = "Quaranta dobloni a testa.";
			link.l1.go = "saga_60";
		break;
		
		case "saga_60":
			dialog.text = "Ohibò! I miei compratori pagano di meno...";
			link.l1 = "In tutto, ho tirato su duemila dobloni per Loxley e "+sti(npchar.quest.bakaut_sum)*2+" dobloni in aggiunta a ciò.";
			link.l1.go = "saga_61";
		break;
		
		case "saga_61":
			dialog.text = "Benissimo. Allora lo dividiamo a metà.";
			if (CheckCharacterItem(pchar, "gold_dublon"))
			{
				npchar.quest.bakaut_pay = GetCharacterItem(pchar, "gold_dublon"); // дублоны в кармане
				link.l1 = "Ecco qua. Ho preso "+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+".";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "Ho lasciato i dobloni sulla nave. Faccio un salto veloce laggiù e torno subito.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "saga_61_1":
			dialog.text = "Per mille balene! Quanto hai portato?";
			if (CheckCharacterItem(pchar, "gold_dublon"))
			{
				npchar.quest.bakaut_pay = GetCharacterItem(pchar, "gold_dublon"); // дублоны в кармане
				link.l1 = "Ecco qua. Ho "+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+".";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "Che diavolo succede alla mia memoria! È ora di smettere di ciarlare col rum. Ancora una volta ho lasciato i dobloni nel mio baule. Vado a recuperarli in fretta e li porto qui.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay": // оплата
			if (sti(npchar.quest.bakaut_sum) < sti(npchar.quest.bakaut_pay)) // полная сумма
			{
				npchar.quest.bakaut_pay = sti(npchar.quest.bakaut_sum);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.bakaut_sum)-sti(npchar.quest.bakaut_pay);
			npchar.quest.bakaut_sum = iTemp; // запоминаем остаток
			RemoveItems(pchar, "gold_dublon", sti(npchar.quest.bakaut_pay));
			Log_Info("You have given "+sti(npchar.quest.bakaut_pay)+" doubloons");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "Bel colpo, "+pchar.name+"! Mi ricordo ancora una volta che sei proprio un buon compagno d’avventure.";
				link.l1 = "Ci provo, Jan...";
				link.l1.go = "bakaut_done";
			}
			else
			{
				dialog.text = "Perfetto. Porterai anche il resto "+FindRussianQtyString(sti(npchar.quest.bakaut_sum))+" dobloni dopo?";
				link.l1 = "Sì. Non potevo mica trascinarmi dietro tutta quella montagna d’oro in una volta sola.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay_wait":
			dialog.text = "Dunque, "+pchar.name+", come stanno andando i miei dobloni?";
			link.l1 = "Sono disposto a darti ancora un po' d'oro.";
			link.l1.go = "saga_61_1";
		break;
		
		case "bakaut_done": // рассчитались
			dialog.text = "Ho una proposta per te. Visto che sei riuscito a trovare un compratore coi fiocchi, posso venderti un po' di legno di ferro. Un tempo mi pagavano trenta dobloni a pezzo. Se vuoi, te lo cedo a quel prezzo. Preferisco venderlo a te che a qualche altro furfante.";
			link.l1 = "Quanta legna di ferro sei in grado di vendere?";
			link.l1.go = "bakaut_done_1";
		break;
		
		case "bakaut_done_1":
			dialog.text = "Evito di mettere da parte grandi scorte. Quella volta da Molligan fu un’eccezione. Le autorità non vedranno di buon occhio la voce di un mercato nero locale. Dunque, senti qui: ti terrò da parte 25 pezzi di legno di ferro ogni 14 e 24 del mese. \nSe li vorrai comprare, porta settecentocinquanta dobloni e prendi l’intero lotto. Se non ti fai vivo quel giorno, li vendo a qualcun altro. Così potrai avere 50 pezzi al mese. Intesi?";
			link.l1 = "Hai la mia parola, Jan! Facciamolo. Ora è tempo che io mi metta in cammino...";
			link.l1.go = "saga_oust";
			DeleteAttribute(npchar, "quest.bakaut_sum");
			npchar.quest.trade_bakaut = "true"; // генератор купли-продажи бакаута
			AddQuestRecordInfo("Unique_Goods", "1");
		break;
		
		case "saga_59_1": // укрысил у Яна - нет генератора на бакаут, потерял больше
			dialog.text = "Ah, quindi o non era lui oppure ha già venduto quell’ironwood prima... Che peccato. Beh, ormai sei la mia unica speranza di racimolare il denaro per l’avvocato.";
			link.l1 = "Sarò pronto a prendermi questa responsabilità. Non è certo la mia prima scorribanda.";
			link.l1.go = "exit";
			// Ян расстроен и забыл про Устрицу - так что и Устрицы тоже не будет
			DeleteAttribute(npchar, "quest.bakaut_sum");
		break;
		
		case "saga_62":
			dialog.text = "Ah, davvero? Che curioso. Su, domandami pure. Di chi vuoi ciarlare?";
			link.l1 = "Per via di una ragazza. Si chiamava... Jessica Rose.";
			link.l1.go = "saga_63";
		break;
		
		case "saga_63":
			dialog.text = "Mm. Il nuovo capo della nostra Fratellanza ti ha parlato di lei?";
			link.l1 = "Anche lui lo fece. Ma io venni a sapere di lei da Baker, il vecchio boia di St. John. Proprio quello che ha mandato all’altro mondo il capitano Butcher.";
			link.l1.go = "saga_64";
		break;
		
		case "saga_64":
			dialog.text = "Bene. Eh. Sono passati più di vent'anni dall'ultima volta che ho visto Jessica. Che sai di lei?";
			link.l1 = "Beh, so come sia finita tra le grinfie del capitano Butcher e come abbiano predato insieme. So che lui l’ha lasciata per Beatrice. Poi lei si è vendicata, con l’aiuto di un certo Joshua Leadbeater, detto anche la Maschera...";
			link.l1.go = "saga_65";
		break;
		
		case "saga_65":
			dialog.text = "";
			link.l1 = "So anche che tu, Jan, perdona la mia schiettezza, avevi interesse per Jessica. È proprio per questo che sono venuto da te. Jessica è una figura chiave nelle mie ricerche. È stata lei a uccidere Beatrice Sharp, per gelosia, almeno così mi pare di capire.";
			link.l1.go = "saga_66";
		break;
		
		case "saga_66":
			dialog.text = "Ebbene, ne sai parecchio. Sì, davvero facevo la corte a Jess, ma non era certo un segreto: all’epoca tutti i filibustieri di Isla Tesoro si dividevano in due schiere – quelli che volevano infilarsi nel letto di Beatrice e quelli che sognavano Jessica.\nLa ricordo bene... Era una bellezza, una vera sirena!..";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Jess");
			NextDiag.TempNode = "saga_66a";
		break;
		
		case "saga_66a":
			dialog.text = "Era una ragazza fuori dal comune... E molto probabile che sia stata Jess ad ammazzare Beatrice. Dopo che il Macellaio l'ha cacciata a calci dal 'Neptune', non avrà pensato ad altro che vendicarsi di lui e di Beatrice. A proposito, sai come il Macellaio si è sbarazzato di Jessica?";
			link.l1 = "No. O l’ha semplicemente sbarcata a Barbados, o l’ha messa a riscatto.";
			link.l1.go = "saga_67";
		break;
		
		case "saga_67":
			dialog.text = "La seconda. L’ha umiliata oltre ogni limite. L’ha rinchiusa in cabina, l’ha portata a Barbados, ha iniziato a trattare col padre Oliver Rose e, alla fine, l’ha venduta per una montagna di dobloni... dopo tutto quello che lei aveva fatto per lui.";
			link.l1 = "Uhm. Pensavo che Macellaio avesse difeso il suo onore quando i pirati presero il ‘Neptune’ da Joshua Leadbeater...";
			link.l1.go = "saga_68";
		break;
		
		case "saga_68":
			dialog.text = "Anche questo è vero. Ma lo ha anche ricompensato profumatamente. Jessica ha salvato quella canaglia dalla morte più d'una volta, tirandolo fuori dagli impicci in cui si cacciava col suo temperamento burrascoso e la sua sregolatezza. In realtà, fu soltanto grazie a lei che raggiunse la fama di pirata fortunato.";
			link.l1 = "Sì, sì, il suo 'talismano rosso'. Ho sentito parlare di quella storia. Dicono che appena il Macellaio ha mollato Jess, la fortuna l’ha subito piantato pure lui...";
			link.l1.go = "saga_69";
		break;
		
		case "saga_69":
			dialog.text = "Ma certo. Senza Jessica era diventato solo un altro volgare predone dei mari, sebbene uno dannatamente audace. Ma Jessica non c’era più accanto a lui, era lei che architettava tutte le sue folli imprese e la sua lama non lo tradiva mai. Certo, neanche Beatrice era una santa, ma non poteva reggere il confronto con Jess, le grazie di Bea erano tutt’altra storia... Ha commesso l’errore di mettersi contro il Macellaio.";
			link.l1 = "Mi pare d’averlo già sentito dire da qualche parte...";
			link.l1.go = "saga_70";
		break;
		
		case "saga_70":
			dialog.text = "Tutti i filibustieri la pensavano così, persino Blaze Sharp, suo fratello. Non poteva soffrire il Macellaio... Ma torniamo a Jessica. Quand’era sulla ‘Neptune’ non osavo neppure sognarla, non avrebbe mai lasciato il suo adorato capitano. Ma poi il Macellaio l’ha scaricata in modo così vile...\nSono sbarcato a Barbados e le sono diventato amico. Non le fu semplice, amava il mare e le avventure pericolose. Quella vita da colonia la stava spegnendo. E poi, dopo gli anni passati sulla ‘Neptune’, era ormai famigerata in tutti i Caraibi – la gente di Bridgetown aveva pure i suoi motivi per vederla come la complice del Macellaio...";
			link.l1 = "Ma non avevano uno straccio di prova...";
			link.l1.go = "saga_71";
		break;
		
		case "saga_71":
			dialog.text = "No. Ma nessuno voleva averci a che fare comunque. La tenevano per maledetta, nonostante il suo rango a Bridgetown. Credo d’esser stato l’unico a passarci più di mezz’ora insieme, laggiù con Jessica.\nLe proposi di venire con me nelle Indie Occidentali e cominciare una nuova vita. Quella vita che aveva sempre sognato – il mare, le navi, i viaggi, l’avventura. Avevo già messo su un bel giro a Blueweld allora, potevo offrirle cento volte di più di quell’infame del Macellaio. Ma Jess era ferita, dentro e fuori. Non aveva perdonato il Macellaio per il tradimento e per come la trattò poi. E credo che, in fondo, provasse ancora qualcosa per lui... Nonostante ogni mio sforzo, non riuscii a farle scordare il passato, era accecata dalla voglia di vendetta.";
			link.l1 = "Sì, non la invidio affatto. Poveretta...";
			link.l1.go = "saga_72";
		break;
		
		case "saga_72":
			dialog.text = "Provavo lo stesso verso di lei. Più tardi cominciò a interessarsi ai culti antichi e ai riti degli indiani. Tutto iniziò quando un mago indigeno fu catturato nelle selve dello Yucatán e portato alla piantagione locale. Jessica lo comprò e gli diede una casa sulla sua tenuta. \nPassava ore con quel mago. Sosteneva che era solo per la sua passione per la storia e i riti magici degli indiani. Ma la gente di Bridgetown cominciò a preoccuparsi, in particolare il pastore locale. E dire che lui era uno dei pochi che trattava Jessica con rispetto. \nIl prete andava spesso da lei, cercava di convincerla a sbarazzarsi del mago, la minacciava con l’inquisizione e con mille sventure. Ma spaventare Jessica era come parlare al vento. Una notte degli sconosciuti si introdussero nella casa del mago e lo uccisero. \nQuella stessa notte due uomini assalirono Jessica nella sua camera, ma si pentirono amaramente – nessuno a Bridgetown sapeva quanto bene Jess sapesse maneggiare la sua spada dalla lama di fuoco. Li fece a fettine, letteralmente.";
			link.l1 = "Sì, certo... quella furia sconsiderata!";
			link.l1.go = "saga_73";
		break;
		
		case "saga_73":
			dialog.text = "Dopo di ciò, tutta la città cominciò ad aver timore di lei. Poi arrivò la Maschera. Si trovarono l’un l’altro in men che non скажи rum.";
			link.l1 = "Secondo gli scritti, la Maschera è Joshua Leadbeater, l’ex capitano del 'Neptune'...";
			link.l1.go = "saga_74";
		break;
		
		case "saga_74":
			dialog.text = "L'ho scoperto molto più tardi. Una settimana dopo l’arrivo della Maschera, Jess prese le sue cose, mi salutò e salpò su una fregata militare, sparendo verso rotte sconosciute. Non è mai tornata... proprio come Beatrice non è mai tornata a Isla Tesoro.\nPoco dopo, impiccarono il Macellaio a St. John’s, ce lo portò la Maschera in persona. Ma quello sopravvisse al Macellaio solo per un giorno.";
			link.l1 = "Sì... Il nostro Steven Dodson ha dato prova di classe...";
			link.l1.go = "saga_75";
		break;
		
		case "saga_75":
			dialog.text = "Sì, così mi hanno detto. Ha vendicato Beatrice... Ed è così che finisce la storia di Jessica, è morta chissà dove su un'isola deserta durante uno scontro coi cani di mare del Macellaio. Nessuno sa dove sia quel posto. Il Macellaio è all'inferno, e con lui anche Jackman e l’Impiccato.";
			link.l1 = "E qui ti sbagli, Jan. Butcher è ancora vivo.";
			link.l1.go = "saga_76";
		break;
		
		case "saga_76":
			dialog.text = " Cosa!? Non può essere! È stato impiccato!";
			link.l1 = "Leggi la testimonianza di Raymond Baker. Vale più di mille racconti.";
			link.l1.go = "saga_77";
		break;
		
		case "saga_77":
			PlaySound("interface\important_item.wav");
			dialog.text = "Fammi vedere...(leggendo) Mh. Incredibile! Pare che la sua esecuzione sia stata solo una messinscena!";
			link.l1 = "Astuto, eh? Ma non è tutto. Conosci il Macellaio. Solo che non sai chi sia adesso.";
			link.l1.go = "saga_78";
		break;
		
		case "saga_78":
			dialog.text = "Eh?   E chi sarebbe costui?";
			link.l1 = "Lawrence Beltrope da Port Royal. Il padrone della miniera, quella stessa ombra misteriosa che si cela dietro Jackman. L’ho scoperto tramite Baker, e Baker lo ha saputo dalla Maschera.";
			link.l1.go = "saga_79";
		break;
		
		case "saga_79":
			dialog.text = "Santo diavolo! Quindi è lui che ha tirato le fila di tutta questa farsa? Va bene... Andremo anche noi dal Macellaio. Mediterò su come far fuori quella zecca maledetta. Anche se non sarà una passeggiata: ha gli inglesi che gli fanno da scudo.";
			link.l1 = "Il suo momento arriverà, Jan. Presto incontrerà il suo nostromo e quartiermastro. Va bene, grazie per la storia. Ora è tempo che io me ne vada.";
			link.l1.go = "saga_80";
		break;
		
		case "saga_80":
			dialog.text = "Dove te ne vai adesso?";
			link.l1 = "Su qualche isola. Credo sia lo stesso luogo dove Jess e Beatrice hanno trovato la morte, e dove la Maschera ha ghermito il Macellaio Beltrope. Mi serve una prova che Helen sia del sangue degli Sharp e spero di scavare qualcosa laggiù.";
			link.l1.go = "saga_81";
		break;
		
		case "saga_81":
			dialog.text = "D'accordo. Allora, "+pchar.name+", buona fortuna a te. Raccontami tutto nei dettagli quando torni.";
			link.l1 = "Certo. Ci si rivede, Jan!";
			link.l1.go = "saga_81a";
		break;
		
		case "saga_81a":
			DialogExit();
			LAi_SetHuberType(npchar);
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(npchar, "quest.jessika");
			npchar.quest.jessika_peace = "true"; // атрибут на мирное разрешение после боя
		break;
		
		case "saga_82":
			dialog.text = "Bel colpo, "+pchar.name+" Hai compiuto l’impossibile. Tutti noi baroni della Fratellanza della Costa ti dobbiamo un favore.";
			link.l1 = "Sì, la via per la vittoria era stretta. Se solo avessi saputo prima che avrei dovuto resistere a tanto...";
			link.l1.go = "saga_83";
		break;
		
		case "saga_83":
			dialog.text = "Come sta Helen? Che ha intenzione di fare?";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "Resterà sulla mia nave con me. Non è più un semplice ufficiale, ormai. Il comando dell’isola passerà al capo della Fratellanza, e tutto ciò che le spetterà sarà una pigione. Helen ha preso questa decisione da sola.";
				link.l1.go = "saga_84";
			}
			else
			{
				link.l1 = "È salpata per Isla Tesoro per prendere il baronato nelle sue mani.";
				link.l1.go = "saga_85";
			}
		break;
		
		case "saga_84":
			dialog.text = "Ebbene, "+pchar.name+"... Congratulazioni! Molti uomini avrebbero dato l’anima per essere al tuo posto. Sono lieto che Hélène abbia scelto un uomo degno di lei. Non poteva esserci miglior candidato di te per condividere il resto dei suoi giorni.";
			link.l1 = "Grazie, Jan! Ora vorrei tornare al nostro discorso su Tortuga e Levasseur.";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "Grazie, Jan!";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_85":
			dialog.text = "Meraviglioso. Se lo merita proprio. Credo che il nuovo capo della Fratellanza saprà guidarla nei suoi affari. È una ragazza giovane, sveglia e piena di talento: impara tutto in un lampo. Ti ringrazio, "+pchar.name+"! Helen è come una figlia per me, e sono al settimo cielo vedendo che un destino così splendido le si è appena spalancato davanti.";
			link.l1 = "Prego, Jan... Ma tornando al nostro discorso su Tortuga e Levasseur, vorrei riprenderlo.";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "Non c’è di che, Jan.";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_86":
			sTemp = "Shark Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = "Mentre eri via, "+sTemp+" e abbiamo già discusso la faccenda, giungendo a un'opinione comune su come sbarazzarci di Levasseur. Salpa verso Isla Tesoro e parla col nostro nuovo capo, lui ti spiegherà il piano nei dettagli e ti aiuterà in tutto ciò che potrà.";
			link.l1 = "Finalmente sento il profumo della polvere da sparo! Non c’è tempo da perdere, mi metto subito in rotta per Isla Tesoro!";
			link.l1.go = "saga_87";
		break;
		
		case "saga_87":
			dialog.text = ""+pchar.name+" , aspetta un attimo. Ho un paio di doni per te, per l’aiuto che mi hai dato con Helen e la Confraternita. Il primo è l’amuleto incantato del Saraceno, giunto dall’Estremo Oriente. I suoi sortilegi rafforzano la disciplina a bordo, garantito dal sottoscritto. Tieni, prendi questo.";
			link.l1 = "Grazie!";
			link.l1.go = "saga_88";
		break;
		
		case "saga_88":
			GiveItem2Character(pchar, "talisman4");
			Log_Info("You've received the 'Janissary' amulet.");
			PlaySound("interface\important_item.wav");
			dialog.text = "La seconda è solo un ricordo delle vecchie avventure. Ho convinto il Consiglio a lasciar perdere questa buffonata di gettare frammenti di pietra al vento. Ormai non servono più a nulla. Te li darò io. Magari tu troverai un modo per farne buon uso.";
			link.l1 = "Un uso per questi frammenti? Mh. Non saprei... ma come ricordo, ti sono molto grato!";
			link.l1.go = "saga_89";
		break;
		
		case "saga_89":
			GiveItem2Character(pchar, "splinter_js"); 
			GiveItem2Character(pchar, "splinter_nh"); 
			GiveItem2Character(pchar, "splinter_mt"); 
			GiveItem2Character(pchar, "splinter_zm"); 
			GiveItem2Character(pchar, "splinter_jb"); 
			Log_Info("You've received five ornamental pattern fragments");
			dialog.text = "Ebbene, non dimenticare il tuo buon compare, "+pchar.name+"Passa da me quando getti l’ancora a Blueweld. Ci sediamo, ci scoliamo un po’ di rum. Mi fa sempre piacere vederti.";
			link.l1 = "Certamente, Jan. Adesso abbiamo qualcosa da ricordare, eh? Ah-ah! Ad ogni modo, è ora che me ne vada.";
			link.l1.go = "saga_90";
		break;
		
		case "saga_90":
			dialog.text = "Buona fortuna, "+pchar.name+"!";
			link.l1 = "Ci si rivede...";
			link.l1.go = "saga_91";
		break;
		
		case "saga_91":
			DialogExit();
			pchar.questTemp.Saga = "end";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock")) AddQuestRecord("Saga", "26_1");
			else 
			{
				AddQuestRecord("Saga", "26");
				pchar.questTemp.Terrapin = "islatesoro";
			}
			CloseQuestHeader("Saga");
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
	// --> провалы Саги
		case "saga_f_1":
			dialog.text = "Già... Pare proprio che il nostro piano sia andato a picco. Ora non potremo mettere chi volevamo a capo della Fratellanza. Jackman è morto, pace all'anima sua. Ma ahimè, il mio piano ormai è andato in fumo. Toccherà scegliere il capo della Fratellanza come sempre, e che il diavolo sappia dove ci porterà questa storia...";
			link.l1 = "Che sfortuna, maledizione. E pare proprio che Helen resterà senza la sua eredità.";
			link.l1.go = "saga_f_2";
		break;
		
		case "saga_f_2":
			dialog.text = "Sì, "+pchar.name+" E vorrei davvero aiutarti a prendere Tortuga, davvero, ma ora non saprei proprio come. Forse non c'è nulla che io possa fare per darti una mano. Pare che dovrai contare solo sulle tue forze e sulla tua lama. ";
			link.l1 = "Pare che non ci resti altra scelta... Va bene, Jan, vado a riflettere sul da farsi. Ci vediamo più tardi...";
			link.l1.go = "saga_f_3";
		break;
		
		case "saga_f_3":
			dialog.text = "Fermati qui, "+pchar.name+". Son sempre lieto di vederti.";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			CloseQuestHeader("Testament");
		break;
		
		case "saga_l1": // проход первый - отбираем Элен и закрываем вход к Свенсону
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l1";
			pchar.quest.Saga_Late_1.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_1.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_1.function = "Saga_HelenaTalk";
			pchar.questTemp.Saga.Jackman = "true";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
		break;
		
		case "saga_l2": // проход второй - отбираем Элен, Натана и Данни в Марун-Таун, чистим квестовый лут
			dialog.text = "Ma ahimè, ormai è troppo tardi per poter fare alcunché. Isla Tesoro è passata ufficialmente sotto l’autorità della corona inglese. Ora vi staziona una guarnigione. È un colpo tremendo per la Fratellanza, temo che non riusciremo mai più a riprenderci.";
			link.l1 = "Che disgrazia... Ah, avrei dovuto muovermi più in fretta. Vedi, allora tutto sarebbe andato per il verso giusto. Va bene, Jan, vado a riflettere sul da farsi. Ci si vede più tardi...";
			link.l1.go = "saga_l2_1";
		break;
		
		case "saga_l2_1":
			dialog.text = "Fermati qui, "+pchar.name+". Sono sempre lieto di vederti.";
			link.l1 = "...";
			link.l1.go = "saga_l2_2";
		break;
		
		case "saga_l2_2":
			DialogExit();
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			RemoveItems(pchar, "letter_parol", 1);
			RemoveItems(pchar, "map_sharp_full", 1);
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // наверно не нужно
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l2";
			pchar.quest.Saga_Late_2.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_2.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_2.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
			pchar.questTemp.Saga_Late = true; // второй атрибут, отсекающий диалоги, на всякий пожарный
		break;
		
		case "saga_l3":
			dialog.text = "Già... Abbiamo appena subito una sconfitta amara. E la cosa peggiore è che ci mancava un soffio alla vittoria. Maledizione! Com'è potuto accadere, eh, "+pchar.name+"? Ci hai provato con tutto te stesso, hai fatto così tanto e... che sfortuna maledetta!";
			link.l1 = "Sono io lo sciocco responsabile di tutto questo. Avrei dovuto muovermi più in fretta. E per colpa mia, Helen perderà la sua eredità. E il piano per Tortuga andrà in malora.";
			link.l1.go = "saga_f_2";
			pchar.questTemp.Saga_Late = true; // второй атрибут, отсекающий диалоги, на всякий пожарный
		break;
	// <-- провалы Саги
		
	//-----------------------------------генератор торговли бакаутом--------------------------------------------
		case "trade_bakaut":
			if (CheckAttribute(pchar, "questTemp.UpgradeBakaut"))
			{
				dialog.text = "Va bene, non mi fa né caldo né freddo. Ho 125 unità nel mio magazzino. Il prezzo, come ricorderai, è di 3150 a pezzo.";
				if (PCharDublonsTotal() >= 3150)
				{
					link.l1 = "D'accordo, affare fatto. Ecco qua. Prendi 3150 dobloni.";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "Che sfiga maledetta. Ho dimenticato il borsello sulla mia nave. Torno subito con i dobloni.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "D'accordo, non m'importa. Ho venticinque unità nel mio magazzino. Il prezzo, come ricordi, è di trenta dobloni a pezzo.";
				if (PCharDublonsTotal() >= 750)
				{
					link.l1 = "D'accordo, affare fatto. Ecco qua. Settecentocinquanta dobloni, come promesso.";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "Che sfortuna maledetta. Ho lasciato i miei soldi sulla nave. Torno subito con il borsello.";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && !CheckAttribute(pchar, "questTemp.SvensonBakautBlock")) // увеличить объём поставок бакаута
			{
				link.l4 = "Jan, sarebbe possibile aumentare la quantità delle spedizioni di legno di ferro?";
				link.l4.go = "UpgradeBakaut";
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && CheckAttribute(pchar, "questTemp.SvensonBakautPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок бакаута, если в первый раз не принесли
			{
				link.l4 = "Jan, ho raccolto tremila monete d’oro. Tieni, puoi offrire questo dono ai nostri parassiti. Immagino che oggi avranno una giornata felice.";
				link.l4.go = "UpgradeBakaut_Agreed";
			}
		break;
		
		case "trade_bakaut_1":
			RemoveDublonsFromPCharTotal(750);
			Log_Info("You have given 750 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Lodevole. Ordinerò ai miei uomini di caricare il legno di ferro sulla tua nave.";
			link.l1 = "Grazie!";
			link.l1.go = "trade_bakaut_2";
		break;
		
		case "trade_bakaut_2":
			dialog.text = "Se vuoi comprarne ancora, torna fra due settimane. Per allora avrò messo insieme un altro carico.";
			link.l1 = "Va bene, Jan. Alla prossima!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SANDAL, 25);
			DeleteAttribute(npchar, "quest.trade_bakaut");
			SetFunctionTimerCondition("Bakaut_SvensonAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "UpgradeBakaut": //
			if (startHeroType == 1) sStr = "old friend";
			if (startHeroType == 2) sStr = "old friend";
			if (startHeroType == 3) sStr = "old friend";
			if (startHeroType == 4) sStr = "Helen";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Felice che tu abbia preso gusto per il legno di ferro, "+sStr+"Aumentare i carichi non è un problema, ma c’è un tranello, come ben capisci. Più merci, più rischи di lasciare tracce che potrebbero attirare attenzioni sgradite, soprattutto quelle maledette autorità inglesi. Se però mettiamo gente affidabile, orecchie fidate e qualcuno nella residenza che ci aiuti a restare nell’ombra, tutto si può sistemare. Ma non sarà a buon mercato – tremila dobloni per svicolare dal tesoro cittadino e dalle grinfie d’Inghilterra. Dopodiché potrò fornirti cinque volte tanto. Che ne dici?";
				link.l1 = " Tremila dobloni? Jan, questo è un furto alla luce del sole! Non potremmo cavarcela con meno spese? Forse c’è modo di risolvere la faccenda senza queste cifre da capogiro? ";
				link.l1.go = "UpgradeBakaut_1";
				notification("Skill Check Passed", SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Buona idea, ma devo dire che per traffici di questa portata serve un po’ più di mestiere e fiuto. Se ti affretti troppo, rischi più di quanto ci guadagni. Facciamo così: fai un po’ di esperienza in più, e quando sarai pronto per carichi maggiori, torna pure. Allora ne parleremo come si deve.";
				link.l1 = "Hmm... Va bene. Torneremo su questo discorso più tardi.";
				link.l1.go = "exit";
				notification("Skill Check Failed (80)", SKILL_COMMERCE);
			}
		break;
		
		case "UpgradeBakaut_1":
			dialog.text = "Ahimè, "+pchar.name+", tale è il prezzo della pace in questi tempi - gli appetiti di quei galantuomini in parrucche e uniformi crescono ogni giorno. Nulla li stuzzica più del tintinnio dei dobloni nei loro forzieri. Ti garantisco uno sconto del quindici per cento su tutte le spedizioni future, se questo può consolarti.";
			link.l1 = "Maledetti! Chiedere simili somme! Con quell’avidità dovrebbero comprare tesori reali, non mercanteggiare per un po’ di silenzio! Jan, forse dovremmo... mostrare loro chi comanda davvero in questo arcipelago, eh?";
			link.l1.go = "UpgradeBakaut_2";
		break;
		
		case "UpgradeBakaut_2":
			if (startHeroType == 1) sStr = "my friend";
			if (startHeroType == 2) sStr = "my friend";
			if (startHeroType == 3) sStr = "my friend";
			if (startHeroType == 4) sStr = "Helen";
			dialog.text = "Ah! Che temperamento che hai, "+sStr+"!   Ma sfidare tutta l’Inghilterra non mi conviene adesso, e non ho più i miei vent’anni. Paghiamo questi sanguisughe e che stiano buoni – abbiamo altro da fare. Raduna la somma necessaria, e la nostra strada sarà libera, senza troppe domande!";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Ebbene, Jan, mi hai convinto. Che sia così, visto che non c’è altro rimedio. Ecco i tuoi tremila dobloni. Ma ricordati: non ho alcuna intenzione di mantenere questi avari in eterno.";
				link.l1.go = "UpgradeBakaut_Agreed";
			}
			link.l2 = "Maledizione, Jan! Davvero credi che non ci sia altra via d’uscita? Va bene. Troverò questi dobloni. Ma al momento non ho tutto quel denaro.";
			link.l2.go = "UpgradeBakaut_4";
			link.l3 = "Maledizione, Jan, vuoi davvero che dia da mangiare a questi funzionari e alle loro donnicciole viziate? Se ne stanno seduti sulle loro sedie, non fanno un accidente e pretendono solo denaro! No, questa roba non mi va giù! Non riempirò le loro tasche col mio sudore e col mio sangue! Torniamo agli accordi di prima. Quello mi basta.";
			link.l3.go = "UpgradeBakaut_3";
		break;
		
		case "UpgradeBakaut_Agreed":
			dialog.text = "Ecco che si ragiona! Con la tua parte, la nostra impresa filerà liscia, e quei pidocchiosi avari avranno finalmente ciò che si meritano – e smetteranno pure di ficcare il naso dove non devono, specie attorno al legno di ferro. Fidati, presto riprenderemo con gli interessi tutto quel che abbiamo messo – e pure di più.";
			link.l1 = "Spero di sì, Jan, lo spero davvero.";
			link.l1.go = "UpgradeBakaut_Agreed_1";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "1_1");
			pchar.questTemp.UpgradeBakaut = true;
			pchar.questTemp.SvensonBakautBlock = true;
			DeleteAttribute(pchar, "questTemp.SvensonBakautPotom");
		break;
		
		case "UpgradeBakaut_Agreed_1":
			dialog.text = "Gli affari procederanno come si conviene, non hai motivo di preoccuparti. E adesso, riguardo ai nostri futuri accordi: terrò pronti per te 125 tronchi di legno di ferro, come sempre, per il 14 e il 28 di ogni mese. Puoi prendere l’intero carico per 3150 dobloni.";
			link.l1 = "Queste chiacchiere mi piacciono assai di più! Centoventicinque tronchi, allora? Magnifico, Jan. Bene, a presto, attenderò il carico!";
			link.l1.go = "exit";
		break;
		
		case "UpgradeBakaut_3":
			if (startHeroType == 1) sStr = "old friend";
			if (startHeroType == 2) sStr = "old friend";
			if (startHeroType == 3) sStr = "old friend";
			if (startHeroType == 4) sStr = "Helen";
			dialog.text = "Come desideri, "+sStr+"  E non agitarti tanto. È così che va il mondo, bellezza.";
			link.l1 = "Sì, Jan, so bene come vanno le cose in questo mondo. Ma non vuol dire che debba inghiottirle senza fiatare. D’accordo, ora devo andare.";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
		break;
		
		case "UpgradeBakaut_4":
			dialog.text = "Aspetterò finché non raccoglierai il denaro. So che ti inventerai qualcosa. Non appena sarai pronto – ti aspetterò coi soldi, e andremo avanti.";
			link.l1 = "D'accordo.";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
			pchar.questTemp.SvensonBakautPotom = true;
		break;
		// <-- генератор бакаута
		
	//----------------------------------- штурм рудника --------------------------------------------
		case "mine_attack":
			dialog.text = "Felice di vederti, "+pchar.name+". I miei uomini sono pronti. Si parte per la selva?";
			link.l1 = "Sì, Jan. La mia ciurma è pronta a menar le mani.";
			link.l1.go = "mine_attack_1";
		break;
		
		case "mine_attack_1":
			dialog.text = "Andiamo allora. La miniera si trova nelle profondità della giungla, proprio lungo questo sentiero. Tieni la destra al bivio. Avanti!";
			link.l1 = "Avanti!";
			link.l1.go = "mine_attack_2";
		break;
		
		case "mine_attack_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("shore53", "boat", true);
			LocatorReloadEnterDisable("mine_03", "reload3_back", true);
			LocatorReloadEnterDisable("mine_02", "reload3_back", true);
			pchar.quest.Saga_MineAttack_01.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_01.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_01.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_3":
			dialog.text = "Allora, "+pchar.name+", è giunta l’ora di discutere come intendiamo procedere con quest’impresa. Ho già mandato alcune guide Miskito in ricognizione e ho elaborato un piano basato sulle loro osservazioni.";
			link.l1 = "Mettiamici al corrente!";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "La fossa rappresenta la miniera sotto le montagne nella giungla. C’è un accampamento vicino all’ingresso della miniera. Qualche capanna e una palizzata. Un sentiero porta alla palizzata. Vedi, conduce a una piccola radura nella giungla, non lontano da qui. È lì che si trova l’ingresso principale della fossa.\nQuella palizzata rappresenta un alto muro di pietra incastonato tra due colline scoscese, impedendo a chiunque di intrufolarsi. I cancelli sono sorvegliati da sei uomini. Nulla di straordinario, se non fosse che hanno piazzato anche due cannoni lassù. Ed è proprio questo il guaio.\nDue scariche di mitraglia e la metà dei nostri finirà stesa, una vera rovina, quindi attaccarli di petto non è proprio cosa...";
			link.l1 = "Ah! Ma abbiamo un asso nella manica, conosciamo la parola d’ordine che ci farà entrare...";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			dialog.text = "Esatto. Useremo questo a nostro vantaggio, ma ora lascia che ti sveli il mio piano fino in fondo.";
			link.l1 = "Certo, Jan. Sono tutt’orecchi.";
			link.l1.go = "mine_attack_6";
		break;
		
		case "mine_attack_6":
			dialog.text = "C’è un altro ingresso alla fossa – passando per quel sentiero nella giungla. Costeggia le colline che difendono la miniera e porta a una piccola gola stretta, da cui si può entrare. Ma quei cani di banditi hanno alzato una staccionata alta e piazzato delle guardie. Il cancello è piccolo, ma sbarrato dall’interno.\nOra ascoltami bene, ecco il piano: sgomberiamo chiunque stia di guardia al secondo ingresso della miniera. Una parte dei nostri resterà lì e troverà un tronco da usare come ariete.\nNoi torneremo all’ingresso principale e faremo fuori i serventi dei cannoni. La parola d’ordine che abbiamo ci tornerà utile due volte. Poi attaccheremo la miniera da due lati. Io guiderò la prima squadra d’assalto, tu la seconda.";
			link.l1 = "Ebbene, è logico. Li costringeremo a combatterci su due fronti. Avanti!";
			link.l1.go = "mine_attack_7";
		break;
		
		case "mine_attack_7":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.quest.mine01 = "true";
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", true);//офицеров не пускать
			pchar.quest.Saga_MineAttack_02.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_02.win_condition.l1.location = "Mine_04";
			pchar.quest.Saga_MineAttack_02.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_8":
			dialog.text = "Bene, eccoci qui... Questo è il sentiero che porta al ricettatore dei banditi. Ora dobbiamo decidere come agire. Se mandiamo tutta la compagnia, daremo troppo nell'occhio e suoneranno l'allarme.\nConviene mandare un gruppetto di tre uomini, non di più; così si potrà avvicinare senza destare sospetti e coglierli di sorpresa. Io non posso guidare il gruppo, la mia faccia è troppo nota da queste parti.\nTocca a te, "+pchar.name+", perché sei l'unico di cui mi possa fidare al comando senza mandare tutto a ramengo. Ti affido Gregory e un moschettiere per aiutarti...";
			link.l1 = "Quanti sbirri stanno appostati alla staccionata?";
			link.l1.go = "mine_attack_9";
		break;
		
		case "mine_attack_9":
			dialog.text = "Quattro. Due moschettieri e due soldati.";
			link.l1 = "Li prenderemo...";
			link.l1.go = "mine_attack_10";
		break;
		
		case "mine_attack_10":
			dialog.text = "Conoscendoti, non ne dubito nemmeno per un attimo. Avvicinati a loro e dì che ti manda Jackman. Pronuncia la parola d’ordine. E poi, quando saranno tutti tranquilli... agisci secondo la situazione.";
			link.l1 = "D'accordo. Li terremo sulle spine.";
			link.l1.go = "mine_attack_11";
		break;
		
		case "mine_attack_11":
			dialog.text = "Buona fortuna, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "mine_attack_12";
		break;
		
		case "mine_attack_12":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 2)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 12)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				LAi_CharacterDisableDialog(sld);//запрет диалога
			}
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(npchar, "quest.mine01");
			npchar.quest.mine02 = "true";
			pchar.questTemp.Saga.MineAttack = "true";
			pchar.quest.Saga_MineAttack_03.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_03.win_condition.l1.location = "Mine_01";
			pchar.quest.Saga_MineAttack_03.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_13":
			dialog.text = "Bel colpo, "+pchar.name+"Ah! Sei riuscito a spuntarla, come sempre. Ora i miei ragazzi si prepareranno a scatenare un inferno da questo lato della miniera e libereremo l’ingresso principale.";
			link.l1 = "Immagino che dovrò tornare a scocciare le guardie, eh?";
			if (GetCharacterIndex("Svensons_off_2") != -1 && GetCharacterIndex("Svensons_sold_12") != -1) link.l1.go = "mine_attack_14";
			else link.l1.go = "mine_attack_14a";
		break;
		
		case "mine_attack_14a":
			dialog.text = "Sì, "+pchar.name+", ancora una volta. Mi piacerebbe andare io stesso, ma di sicuro mi riconoscerebbero e tutta la faccenda andrebbe a rotoli. Sarà più rischioso, ci sono più nemici in giro, e non scordarti le armi.";
			link.l1 = "Porterò con me i miei ufficiali.";
			link.l1.go = "mine_attack_14_1";
		break;
		
		case "mine_attack_14":
			dialog.text = "Sì, "+pchar.name+", ancora una volta. Mi piacerebbe andarci di persona, ma mi riconoscerebbero subito e tutta la faccenda andrebbe a rotoli. Stavolta sarà più rischioso: più canaglie in giro, e non scordare le armi. Chi porterai con te per darti man forte? I tuoi ufficiali, oppure Gregory e il moschettiere come l’ultima volta?";
			link.l1 = "Porterò i miei ufficiali.";
			link.l1.go = "mine_attack_14_1";
			link.l2 = "Porterò con me Gregory e il moschettiere.";
			link.l2.go = "mine_attack_14_2";
		break;
		
		case "mine_attack_14_1":
			dialog.text = "Va bene. I tuoi uomini sono il miglior sostegno che puoi avere. Ora torniamo verso l’ingresso principale. Ricordi la strada?";
			link.l1 = "Ma certo. Torniamo indietro per dove siamo venuti, poi tieni la sinistra, e segui la traccia intorno alla collina.";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "officer";
		break;
		
		case "mine_attack_14_2":
			dialog.text = "D’accordo. Sei già riuscito una volta, quindi la seconda sarà una passeggiata. Ora torniamo all’ingresso principale. Ricordi la strada?";
			link.l1 = "Certo. Torniamo indietro da dove siamo venuti, poi tieni la sinistra e prendi il sentiero che gira intorno alla collina.";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "soldiers";
		break;
		
		case "mine_attack_15":
			dialog.text = "Nessun tempo da perdere. Avanti, marciamo!";
			link.l1 = "Avanti!";
			link.l1.go = "mine_attack_16";
		break;
		
		case "mine_attack_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 12) LAi_ActorFollowEverywhere(sld, "", -1);
				else LAi_ActorRunToLocation(sld, "reload", "reload3_back", "mine_01", "goto", "goto"+i, "", 5);
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", false);//офицеров пускать
			if (pchar.questTemp.Saga.MineAttack == "soldiers") LAi_LocationDisableOfficersGen("mine_exit", true);//офицеров не пускать
			LocatorReloadEnterDisable("mine_03", "reload3_back", false);
			LocatorReloadEnterDisable("mine_02", "reload3_back", false);
			DeleteAttribute(npchar, "quest.mine02");
			npchar.quest.mine03 = "true";
			pchar.quest.Saga_MineAttack_05.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_05.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_05.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_17":
			dialog.text = "Giusto, "+pchar.name+", ascolta bene queste ultime istruzioni. Quei dannati diavoli che sorvegliano i cancelli sono ossi duri, quindi non ti sarà facile. Il tuo scopo principale è far fuori i cannonieri che stanno vicino ai cancelli, perché finché respirano non potremo venire in tuo aiuto.\nQuando entrambi saranno morti e non ci sarà rischio di una scarica di fucileria, allora tutti noi piomberemo su di loro e li faremo a pezzi in un lampo. Hai capito, "+pchar.name+" Non fare l’eroe, sgozza i cannonieri e lascia il resto a noi.";
			link.l1 = "Va bene, Jan. Cercherò di fare tutto come abbiamo deciso. E se qualcosa andrà storto, improvviserò.";
			link.l1.go = "mine_attack_18";
		break;
		
		case "mine_attack_18":
			dialog.text = "Sembra un buon piano. Che Dio ti accompagni!";
			link.l1 = "Grazie...";
			link.l1.go = "mine_attack_19";
		break;
		
		case "mine_attack_19":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 2)
					{
						LAi_SetActorType(sld);
						LAi_ActorFollowEverywhere(sld, "", -1);
					}
					else LAi_SetStayTypeNoGroup(sld);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", false);//офицеров пускать
			DeleteAttribute(npchar, "quest.mine03");
			pchar.quest.Saga_MineAttack_06.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_06.win_condition.l1.location = "Mine_exit";
			pchar.quest.Saga_MineAttack_06.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_20":
			dialog.text = "Uff! Abbiamo fatto fuori quei figli di puttana... Bei diavoletti erano. Si vede che quei mercenari hanno servito tra le truppe regolari. Abbiamo fatto un bel casino qui, temo ci abbiano sentito. Non c’è tempo da perdere!"+pchar.name+", è giunta l’ora di assaltare la miniera.\nIo torno al mio gruppo all’ingresso secondario – dovrebbero aver già trovato e preparato un tronco per sfondare la palizzata. Tu e i tuoi uomini entrerete dai cancelli centrali. Attendete mezz’ora il nostro segnale, non attaccate subito...";
			link.l1 = "Jan, se hanno sentito gli spari alla miniera, non abbiamo nemmeno mezz’ora. Quei furfanti potrebbero già piazzare una linea difensiva, o peggio, venir dritti ai cancelli centrali e assalire la mia compagnia con tutte le loro maledette forze...";
			link.l1.go = "mine_attack_21";
		break;
		
		case "mine_attack_21":
			dialog.text = "Merda! È ben possibile. Che proponi di fare, allora?";
			link.l1 = "Hm... Ah! Ho un’idea! I cannoni! Guarda un po’ attorno. Non ci sono solo mitraglie, ma pure bombe! Adesso questi furfanti sono spacciati! Perché non ci ho pensato prima?!";
			link.l1.go = "mine_attack_22";
		break;
		
		case "mine_attack_22":
			dialog.text = "Che ne pensi, che dovremmo fare?";
			link.l1 = "Prenderemo un solo cannone. Con uno solo ci muoveremo più svelti e senza intoppi. Lo faremo rotolare dentro, oltre i cancelli, fino alla miniera e lo piazzeremo dove serve. Se quei cani attaccano per primi, si beccano un bel botto; se restano fermi, allora li bombarderemo nel loro accampamento. Puoi dirmi esattamente dove si trova il loro campo dietro i cancelli?";
			link.l1.go = "mine_attack_23";
		break;
		
		case "mine_attack_23":
			dialog.text = "Il campo si trova in una valle ai piedi della montagna. C’è un sentiero appena oltre il cancello che scende serpeggiando intorno al colle. Il campo è proprio dietro questa collina.";
			link.l1 = "Splendido! Ci piazzeremo in cima al sentiero e lanceremo un paio di bombe oltre la collina dritto nel loro covo! Ah, li faremo ballare come scimmie impazzite!";
			link.l1.go = "mine_attack_24";
		break;
		
		case "mine_attack_24":
			dialog.text = "Maledizione, "+pchar.name+", ben fatto! Avanti tutta! Lascio Randolf ai tuoi ordini, è il mio miglior artigliere di bordo. Prendilo come tuo cannoniero e non ti tradirà. Io ora vado dai miei uomini.";
			link.l1 = "D’accordo. Canonerò le loro posizioni all’inferno per mezz’ora, finché non sfonderete i cancelli.";
			link.l1.go = "mine_attack_25";
		break;
		
		case "mine_attack_25":
			dialog.text = "Cercherò di arrivare in tempo. Ci vediamo all'accampamento!";
			link.l1 = "Affare fatto... Ciurma! Ascoltate il mio ordine! Preparatevi a spostare il cannone in una nuova posizione! Prendete con voi polvere da sparo, bombe e mitraglia! Verso la miniera, attraverso i cancelli. In marcia!";
			link.l1.go = "mine_attack_26";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 5);
			if (GetCharacterIndex("Svensons_off_2") != -1)
			{
				sld = characterFromId("Svensons_off_2");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", 5);
			}
		break;
		
		case "mine_attack_26":
			DialogExit();
			int n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "mine_bandits");
			LocatorReloadEnterDisable("mine_exit", "reload1_back", false);
			pchar.quest.Saga_MineAttack_07.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_07.win_condition.l1.location = "Mine";
			pchar.quest.Saga_MineAttack_07.function = "Saga_MineGunAttack";
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("mine_exit", "reload2_back", true);
			LAi_LocationDisableOfficersGen("mine_exit", false); // офицеров пускать
			n = Findlocation("mine");
			locations[n].models.always.Gun = "mortair";
			Locations[n].models.always.Gun.locator.group = "goto";
			Locations[n].models.always.Gun.locator.name = "fire"; // орудие - к бою!
			Locations[n].hidden_sound = true;
		break;
		
		case "mine_attack_27":
			dialog.text = "Uff, non siamo arrivati troppo tardi, "+pchar.name+"?";
			link.l1 = "Jan, santo cielo! Che diavolo ti ha trattenuto così tanto? La mia ciurma ha appena preso una bella batosta!";
			link.l1.go = "mine_attack_28";
		break;
		
		case "mine_attack_28":
			dialog.text = "Quella dannata staccionata di legno si è rivelata più tosta del previsto. L’abbiamo sfondata a forza... Abbiamo sentito il tuo casino laggiù. Pare proprio che tu abbia fatto pulizia qui! Ora il posto va in fiamme!";
			link.l1 = "Le imprese di Randolf... Vorrei che avessi visto quanti bastardi abbiamo spedito sottoterra prima che si arrivasse a menar le mani corpo a corpo!";
			link.l1.go = "mine_attack_29";
		break;
		
		case "mine_attack_29":
			dialog.text = "Caramba! Mi tolgo il cappello davanti a te, "+pchar.name+" Ben fatto! Beh, per quanto riguarda le perdite... quando si è in guerra, non mancano mai.";
			link.l1 = "Ora dobbiamo ripulire la miniera stessa. È possibile che qualche superstite si sia nascosto là dentro.";
			link.l1.go = "mine_attack_30";
		break;
		
		case "mine_attack_30":
			dialog.text = "Andiamo solo noi due. Vediamo che aria tira laggiù.";
			link.l1 = "Sembra un piano degno di un vecchio lupo di mare!";
			link.l1.go = "mine_attack_31";
		break;
		
		case "mine_attack_31":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, "");
			TakeNItems(npchar, "potion2", 8); 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "Mine_mines", "reload", "reload1", "", -1);
			LAi_LocationDisableOfficersGen("Mine_mines", true);//офицеров не пускать
			pchar.quest.Saga_MineAttack_08.win_condition.l1 = "locator";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.location = "mine";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator_group = "reload";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator = "reload4";
			pchar.quest.Saga_MineAttack_08.function = "Saga_MineAttackMines";
		break;
		
		case "mine_attack_32a":
			dialog.text = "Non abbiamo ancora perlustrato tutta la miniera! Scommetto la mia ultima bottiglia che qualche altro furfante si nasconde ancora qua dentro!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_32a";
		break;
		
		case "mine_attack_32":
			dialog.text = "Non credo sia rimasto un altro lurido bastardo...";
			link.l1 = "Jan, pensavo che fossimo venuti qui solo per capire come stanno le cose...";
			link.l1.go = "mine_attack_33";
		break;
		
		case "mine_attack_33":
			dialog.text = "Ah-ah, beh, non ti avevo detto che sarebbe stata un'esplorazione speciale, una bella esplorazione sanguinosa... Da tempo non mi scaldavo così le ossa! Ora tutti possono star certi: non è rimasto un solo furfante in questa miniera!";
			link.l1 = "E allora, che si fa adesso, Jan?";
			link.l1.go = "mine_attack_34";
		break;
		
		case "mine_attack_34":
			dialog.text = "Cosa vuoi dire con 'che facciamo adesso'? Andiamo a cercare oro e argento, ovvio. Non credo proprio che Jackman piazzasse una fortezza del genere qui per annoiarsi. Ha messo un'intera guarnigione. Hai visto gli schiavi nella miniera? Dovresti informarti dove tengono il bottino.";
			link.l1 = "D'accordo. Allora tu vai a interrogare gli schiavi e io mi arrampico a perlustrare tutte le case dell'accampamento, magari scopro qualcosa.";
			link.l1.go = "mine_attack_35";
		break;
		
		case "mine_attack_35":
			dialog.text = "Preso! È ora di darsela a gambe!";
			link.l1 = "...";
			link.l1.go = "mine_attack_36";
		break;
		
		case "mine_attack_36":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("mine", "reload1", true);
			LocatorReloadEnterDisable("mine", "reload6", true);//закрыть выходы с рудника
			pchar.quest.Saga_Mine_letter.win_condition.l1 = "item";
			pchar.quest.Saga_Mine_letter.win_condition.l1.item = "letter_mine";
			pchar.quest.Saga_Mine_letter.function = "Saga_FindMineLetter";
			NextDiag.CurrentNode = "mine_attack_36a";
		break;
		
		case "mine_attack_36a":
			dialog.text = "Avanti, compare. E rovescia queste miserabili catapecchie da cima a fondo!";
			link.l1 = "Sto arrivando!";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_36a";
		break;
		
		case "mine_attack_37":
			dialog.text = "Ah-ah! "+pchar.name+", è fantastico che tu ti sia offerto volontario per venire con me a sfasciare questa miniera! È un altro chiaro segno che sei nato sotto una buona stella.";
			link.l1 = "Hai trovato dell’oro?";
			link.l1.go = "mine_attack_38";
		break;
		
		case "mine_attack_38":
			dialog.text = "Sì, maledizione! Non oro, ma argento, e una bella montagna pure. Un giorno in più e l’avrebbero già portato via dal campo. Per questo c’erano tanti mascalzoni qui – erano la scorta.\nGrazie a te ce l’abbiamo fatta in tempo, senza di te starei ancora a radunare uomini. Complimenti, compare!";
			link.l1 = "Ah! Capisco... Quanti dobloni abbiamo in tasca?";
			link.l1.go = "mine_attack_39";
		break;
		
		case "mine_attack_39":
			dialog.text = "Abbiamo circa quattromila dobloni. Li divideremo in due parti: metà a me, metà a te, proprio come pattuito.";
			link.l1 = "Straordinario! Possiamo farci una barca di soldi con quella roba!";
			link.l1.go = "mine_attack_40";
		break;
		
		case "mine_attack_40":
			dialog.text = "Questo è certo... Hai trovato qualcosa di prezioso?";
			link.l1 = "Niente da fare. Non c’è neanche un doblone in queste catapecchie. Però ho trovato delle carte. Le ho lette e ho scoperto che il padrone di questa miniera è un certo Lawrence Beltrope di Port Royal.";
			link.l1.go = "mine_attack_41";
		break;
		
		case "mine_attack_41":
			dialog.text = "Ah, davvero? Fammi dare un'occhiata a quei documenti...";
			link.l1 = "Ecco a te.";
			link.l1.go = "mine_attack_42";
		break;
		
		case "mine_attack_42":
			RemoveItems(pchar, "letter_mine", 1);
			dialog.text = "(leggendo)... Bene... Beltrope? Quel cognome mi suona. Ah, sì! Thomas Beltrope! Che curioso... Va bene, mi informerò su questo appena torno a Blueweld. Tieni, terrò questi documenti con me, se non ti dispiace?";
			link.l1 = "Affatto. Non me ne faccio proprio nulla.";
			link.l1.go = "mine_attack_43";
		break;
		
		case "mine_attack_43":
			dialog.text = "Bene. Ora viene la parte migliore: trasporterò l’argento alle navi. I Miskitos ci daranno una mano. Metteremo insieme un carro... Nel frattempo, tu vai pure a riposarti, "+pchar.name+" Te lo sei meritato più di chiunque altro!";
			link.l1 = "Grazie, Jan. Faremo campo su quella collina, l’odore di bruciato qui è insopportabile. Già, e dobbiamo anche spegnere gli incendi in queste catapecchie, vai a sapere, magari ci torneranno utili più avanti...";
			link.l1.go = "mine_attack_44";
		break;
		
		case "mine_attack_44":
			dialog.text = "Stai pensando di mettere le mani sulla miniera? Ah-ah! L’idea mi è già passata per la testa, ma una cosa è saccheggiare, un’altra – farne la tua proprietà. Amico mio, c’è già chi la considera sua. Potremmo cacciarci nei guai con le autorità inglesi.\nE poi, gli schiavi con cui parlavo mi hanno detto che tutte le vene qui sono praticamente esaurite – grandi carichi d’argento sono stati portati via più volte. Temo che questa miniera abbia già dato tutto quel che poteva.";
			link.l1 = "Hm... Vedremo. Forse non tutto è andato in malora. Va bene, dovrei proprio riposarmi un po’. Ci si vede, Jan.";
			link.l1.go = "mine_attack_45";
		break;
		
		case "mine_attack_45":
			dialog.text = "Vai pure avanti. E non ti preoccupare di nulla. Al resto penseremo noi, senza bisogno d’altri impicci.";
			link.l1 = "...";
			link.l1.go = "mine_attack_46";
		break;
		
		case "mine_attack_46":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "rld", "attack1", "Saga_MineWaitTime", -1);
			n = Findlocation("mine");
			DeleteAttribute(&locations[n], "hidden_sound");
			DeleteAttribute(&locations[n], "hidden_fire");
			n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "models.always.Gun1");
		break;
		
		case "mine_attack_47":
			dialog.text = "Hai dormito bene, "+pchar.name+"?";
			link.l1 = "Non è andata male... Anche se, a dirla tutta, darei qualsiasi cosa per trovare una taverna, tracannare qualcosa e dormire in un letto pulito.";
			link.l1.go = "mine_attack_48";
		break;
		
		case "mine_attack_48":
			dialog.text = "Gli indios hanno portato l’argento sulla riva e lo stanno caricando sulla tua nave sotto la sorveglianza dei miei ufficiali. Puoi già fare rotta indietro. Il tuo desiderio di rhum, taverna e un letto caldo sarà presto realtà. Passa da me tra cinque giorni, ché abbiamo ancora un mare di faccende da sbrigare.";
			link.l1 = "Va bene, Jan. Ci vediamo a Blueweld tra cinque giorni! In bocca al lupo!";
			link.l1.go = "mine_attack_49";
		break;
		
		case "mine_attack_49":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4", "none", "", "", "", 15.0);
			LocatorReloadEnterDisable("shore53", "boat", false);
			LocatorReloadEnterDisable("mine", "reload1", false);
			LocatorReloadEnterDisable("mine", "reload6", false);
			LocatorReloadEnterDisable("mine_01", "reload3_back", false);
			LocatorReloadEnterDisable("mine_exit", "reload2_back", false); //открыть выходы с рудника
			LAi_LocationDisableOfficersGen("mine_mines", false); // офицеров пускать
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			SetFunctionTimerCondition("Saga_ReturnFromMine", 0, 0, 5, false); // таймер
			pchar.questTemp.Saga.Mines = "true"; // после Саги рудник будет разрабатываться
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			DoQuestReloadToLocation("Shore53", "goto", "goto6", "");
		break;
		// <-- штурм рудника
		
		case "helensleep":
			dialog.text = "";
			link.l1 = "Jan, non urlare contro di me. Sistemiamo la faccenda da uomini di buon senso — ricordati che abbiamo degli affari da concludere!";
			link.l1.go = "helensleep_1";
		break;
		
		case "helensleep_1":
			dialog.text = "Ti scaglio subito contro i miei segugi, lurido rospo! Scordati di Levasseur e levati dai piedi!";
			link.l1 = "Jan! Ascoltami...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenSleep_SvensonThrowOut");
		break;
		
		case "after_drinking":
			dialog.text = "Quale barile? Quanto a Helen, le darò una bella strapazzata... Scherzo, Charles, sto solo scherzando! So come vanno queste cose, e per Joanna – spero che questa storia la faccia riflettere un po', ultimamente è stata proprio bisbetica, sai... Eh, così va la vita. Comunque, buona fortuna a Cartagena!";
			link.l1 = "Fino al nostro prossimo incontro, Jan.";
			link.l1.go = "exit";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

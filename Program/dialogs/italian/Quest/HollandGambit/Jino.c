// Джино Гвинейли - алхимик
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
		case "First time":
			// --> Страж истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino1")
			{
				dialog.text = "Oh! Buongiorno, signore. Come diavolo siete arrivato qui?";
				link.l1 = "Buondì, Gino. Facciamo conoscenza. Sono il Capitano "+GetFullName(pchar)+" e sono qui col permesso di John. Parliamoci chiaro: ho bisogno del tuo aiuto, ma posso darti una mano anch’io.";
				link.l1.go = "guardoftruth_0";
				npchar.quest.meeting = "1";
				DelLandQuestMark(npchar);
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Oh! Buon giorno, signore. Come siete arrivato qui? E dov’è John?";
				link.l1 = "Ma guarda un po’... Ecco chi si nascondeva sempre dietro questa porta chiusa! Interessante... Quanto a John... se n’è andato. Adesso questa casa è mia. Ma non ti preoccupare. Presentiamoci, chi sei e che ci fai qui?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
				DelLandQuestMark(npchar);
			}
			else
			{
				// --> Страж истины
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "threeitems")
				{
					dialog.text = "Ciao, "+pchar.name+"Il tuo volto mi dice che hai scoperto qualcosa d’importante. Hai trovato tutte le parti del Guardiano della Verità?";
					link.l1 = "Esatto! Ho con me tutti e tre gli oggetti: il pugnale, la mappa e la bussola!";
					link.l1.go = "guardoftruth_34";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino")
				{
					dialog.text = "Ciao, "+pchar.name+". Che succede? Hai una faccia da chi ha visto il diavolo...";
					link.l1 = "Ho da dirti una cosa, Gino. Una faccenda grossa.";
					link.l1.go = "guardoftruth";
					break;
				}
				// Ксочитэм
				if (CheckAttribute(pchar, "questTemp.Ksochitam") && pchar.questTemp.Ksochitam == "begin")
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"Sì, ricordo, son passati due giorni e vuoi saper del Custode della Verità, giusto?";
					link.l1 = "Sì, proprio tu! Sei riuscito a scoprire qualcosa?";
					link.l1.go = "ksochitam";
					break;
				}
				//--> Португалец
				if (CheckAttribute(pchar, "questTemp.Portugal.Nomoney"))
				{
					dialog.text = "Hai portato 5 000 pesos, "+pchar.name+"?";
					if (sti(pchar.money) >= 5000)
					{
						link.l1 = "Certo. Prendi questi dobloni e procurati tutto quel che ti serve.";
						link.l1.go = "Portugal_3";
						SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
						DeleteAttribute(pchar, "questTemp.Portugal.Nomoney");
						pchar.quest.Portugal_Ill1.over = "yes";
						pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
						pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
						pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
						pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";
					}
					else
					{
						link.l1 = "Purtroppo, al momento non ho il denaro con me.";
						link.l1.go = "Portugal_nomoney";
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal.Die"))
				{
					dialog.text = "Ahimè, "+pchar.name+", Mi rincresce moltissimo – il paziente è spirato. Si è aggravato all’improvviso e se n’è andato in un lampo.";
					link.l1 = "Peccato... Che Dio abbia pietà della sua anima!";
					link.l1.go = "exit";
					DeleteAttribute(pchar, "questTemp.Portugal.Die");
					pchar.quest.Remove_Avendel.win_condition.l1 = "Location_Type";
					pchar.quest.Remove_Avendel.win_condition.l1.location_type = "town";
					pchar.quest.Remove_Avendel.function = "RemoveAvendelnDoc";
					AddQuestRecord("Portugal", "6");
					CloseQuestHeader("Portugal");
					pchar.questTemp.Portugal = "end";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToAntigua")
				{
					dialog.text = "Ciao, "+pchar.name+"È successo qualcosa? Sembri proprio agitato...";
					link.l1 = "Gino, ho una richiesta fuori dal comune per te! C'è un uomo sulla mia nave con la febbre alta. È in delirio e fuori di sé... puoi aiutarlo?";
					link.l1.go = "Portugal";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Portugal_wait")
				{
					dialog.text = ""+pchar.name+", sto aspettando il paziente. Sbrigati, più presto me lo porti, più possibilità avrò di salvarlo.";
					link.l1 = "Sì, sì, sarà portato qui immediatamente.";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentStart")
				{
					dialog.text = "L'hai portato proprio in tempo, "+pchar.name+". È in condizioni critiche, ma c’è ancora una speranza.\nCapitano, sto finendo gli ingredienti e non abbiamo il tempo di andare a cercarli nella giungla. Devo comprarli tutti dagli erboristi locali per 5.000 pesos. Puoi procurarmi questa somma?";
					if (sti(pchar.money) >= 5000)
					{
					link.l1 = "Certo. Tieni, prendi questi soldi e compra tutto ciò che ti serve.";
					link.l1.go = "Portugal_3";
					SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
					}
					else
					{
						link.l1 = "Sfortunatamente, al momento non ho il denaro.";
						link.l1.go = "Portugal_nomoney";
						pchar.quest.Portugal_Ill.over = "yes";
						pchar.quest.Portugal_Ill1.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill1.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
						pchar.quest.Portugal_Ill1.function = "Portugal_ToAntiguaOver";//не принесёт через 1 день - Португальцу капут
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentCurrent")
				{
					dialog.text = "Non ho nulla da dire adesso, "+pchar.name+" Sto lottando per la vita del paziente. C'è ancora un barlume di speranza. Torna a trovarmi più tardi, penso che presto potrò dirti qualcosa di più preciso.";
					link.l1 = "Va bene, Gino, tornerò più tardi.";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentFinish")
				{
					pchar.quest.Portugal_Ill.over = "yes";
					dialog.text = "Ho delle novità,"+pchar.name+". Non dirò che il vostro uomo sia fuori pericolo, ma è vivo. La febbre si sta ritirando e qualche miglioramento si vede. A dire il vero, non pensavo che le mie pozioni gli avrebbero giovato così tanto.";
					link.l1 = "Son buone nuove, Gino, ma dimmi: quando potrò riprendermelo? Abbiamo ancora un mare da solcare e il tempo ci morde le calcagna.";
					link.l1.go = "Portugal_4";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentComplete")
				{
					dialog.text = "Buongiorno, Capitano. Lieto di rivederti.";
					link.l1 = "Come se la cava il nostro paziente, Gino?";
					if (GetQuestPastDayParam("questTemp.Portugal_threedays") > 2) link.l1.go = "Portugal_9";
					else link.l1.go = "Portugal_threedays";
					break;
				}
				// <--Португалец
				dialog.text = "Buon dì, Capitano. Come va? Vi serve il mio aiuto?";
				if (!CheckAttribute(npchar, "quest.rome"))
				{
					link.l1 = "Sì. Gino, suppongo che tu sia un uomo di lettere e magari conosci pure un po' di latino...";
					link.l1.go = "rome";
				}
				if (CheckCharacterItem(pchar, "chemistry"))
				{
					link.l2 = "Ho qualcosa di diverso. Un piccolo dono per te. Ecco, dai un’occhiata a questo libro.";
					link.l2.go = "chemistry";
				}
				if (CheckAttribute(npchar, "quest.colt") && CheckCharacterItem(pchar, "pistol7"))
				{
					link.l2 = "Sì, Gino. Voglio mostrarti questa pistola. Hai mai visto roba simile?";
					link.l2.go = "colt";
				}
				if (CheckAttribute(npchar, "quest.sample") && CheckCharacterItem(pchar, "pistol7") && CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
				{
					link.l2 = "Ti ho portato un esempio della carica per la mia pistola.";
					link.l2.go = "colt_1";
				}
				if (CheckAttribute(npchar, "quest.cartridge"))
				{
					link.l2 = "E per quanto riguarda le accuse per la pistola? Hai già qualche indizio?";
					link.l2.go = "cartridge";
				}
				// Addon 2016-1 Jason Пиратская линейка
				if (CheckAttribute(pchar, "questTemp.Mtraxx.Gord"))
				{
					link.l3 = "Gino, ho trovato la parola 'gord', che per me è sconosciuta, nel diario di un capitano. Sai che vuol dire?";
					link.l3.go = "mtraxx";
				}
				link.l9 = "Buon giorno, Gino. Sto bene, non ho bisogno d’aiuto. Volevo solo passare a salutarti e scambiare due chiacchiere.";
				link.l9.go = "exit";	
			}
			NextDiag.TempNode = "First time";
		break;

		case "meeting":
			pchar.questTemp.HWIC.Jino = "true"; // Addon 2016-1 Jason Пиратская линейка
			dialog.text = "Il mio nome è Gino. Gino Gvineili. Sono un uomo di scienza. Il mio mestiere è preparare polveri, intrugli e altre medicine per il signor Murdock. Ma ora che lui non c’è più...";
			link.l1 = "Ebbene, sono io "+GetFullName(pchar)+" . Capitano della mia nave, finalmente. Allora, sei un alchimista, dunque?";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Non solo sono un alchimista, ma pure un medico. Ho una discreta conoscenza dell’arte medica. So parecchio su erbe curative e sono capace di mescere intrugli e pozioni da esse. Ma la mia vera vocazione è la chimica, passo il tempo a sperimentare e certe mie invenzioni potrebbero tornare utili a gentiluomini come voi.\nConosco il latino, il francese, l’inglese e l’italiano. Il mio aiuto sarà indispensabile se volete gestire una bottega di rimedi, come faceva quel brav’uomo di Murdock...";
			link.l1 = "Oho! Non capita mica tutti i giorni d’incontrare un uomo così dotto. La farmacia va bene, certo, ma io sono un marinaio... eh, fa strano perfino a me sentirlo... comunque, son sicuro che diventeremo compari, Gino. Puoi restare qui e continuare i tuoi esperimenti da scienziato...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "";
			link.l1 = "E se mai avrò bisogno dell’aiuto d’un alchimista, d’un cerusico o d’un sapiente… saprò a chi rivolgermi. Dimmi, perché stai sempre rintanato qua dentro? Non ti capita mai di uscire a respirare il vento?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Esco solo quando devo comprare ingredienti o erbe per i miei esperimenti. Mi piace vivere da solo, è il mio stile. Ho dedicato la mia vita alla scienza e la vita comune non m’interessa affatto. Libri, manoscritti, provette, alambicchi... Il signor Murdock m’ha dato questa possibilità in cambio del mio aiuto nel preparare droghe.";
			link.l1 = "Ora avrai ancora più tempo, Gino. Ma dovrai rinunciare a un po’ dei tuoi esperimenti se mi servirà il tuo aiuto, intesi?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Certo, Capitano. Ti chiamerò Capitano, "+GetAddress_Form(NPChar)+", se non ti dispiace? Lascio tutte le mie ricerche, così, se mai ti servissero le mie doti pratiche o il mio sapere.";
			link.l1 = "Splendido. Mi fa piacere che ci siamo capiti così in fretta. Non ti preoccupare delle tue spese, io o il mio cassiere ti lasceremo di tanto in tanto delle somme ragionevoli.";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Grazie, Capitano. Non ho bisogno di molto... Capitano, mi è venuta un’idea... perché non impari un po’ d’alchimia? Potrebbe tornarti davvero utile.";
			link.l1 = "Hm. Come mi disse una volta mio fratello – non fare lo schizzinoso, impara a sbrigartela con le tue mani. Dunque, certo, perché no. Che mi puoi insegnare?";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Ebbene, certo, non potrai trasformare il ferro in oro, è impossibile... per ora, ma puoi imparare a mescolare gli ingredienti seguendo le istruzioni per ottenere pozioni o altri oggetti utili. Tieni, prendi questa sacca. Contiene tutto ciò che serve a un apprendista alchimista: provette, fiasche, alambicchi, distillatori, spatole, tubi di vetro, un fornello e via dicendo...";
			link.l1 = "Affascinante!";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			Log_Info("You have received an alchemist's kit");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "Devi conoscere una ricetta per preparare una pozione o un oggetto. Le ricette si possono acquistare dai mercanti o trovare ovunque. Una volta studiata la ricetta, raccogli ogni ingrediente necessario e segui alla lettera le istruzioni.\n Usa i tuoi strumenti d’alchimia, trova o compra mortaio e pestello, cerca un crogiolo – ahimè, non ne ho uno di scorta da darti. Erbe, spiriti, elisir, minerali, robaccia – tutto va bene, purché tu abbia la ricetta giusta e gli arnesi adatti.";
			link.l1 = "Capisco. Cercherò di mischiare qualcosa nel tempo libero. Grazie, Gino! Puoi darmi una ricetta facile? Qualcosa per cominciare? ";
			link.l1.go = "meeting_8";
		break;
		
		case "meeting_8":
			dialog.text = "Non ho incarichi semplici... ma prendi questa ricetta di un antidoto. Suppongo che tu sia in grado di cavartela con questa faccenda. Tienila.";
			link.l1 = "Gratitudine! Imparerò che cos’è. Addio, Gino! Sorveglia la mia casa, temo che non ci passerò spesso, quindi sentiti libero d’usare non solo la tua stanza, ma anche tutto il resto della dimora.";
			link.l1.go = "meeting_9";
		break;
		
		case "meeting_9":
			DialogExit();
			GiveItem2Character(pchar, "recipe_potion4"); // belamour legendary edition
			Log_Info("You have received an antidote recipe");
			PlaySound("interface\notebook.wav");
			Log_Info("You need to have the Alchemy skill in order to craft potions, amulets and items!");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "rome":
			dialog.text = "Sì, Capitano, conosco la lingua degli antichi Romani. Ogni scienziato, specialmente un cerusico o un alchimista, deve masticare il latino. Vi occorre la mia sapienza in latino?";
			link.l1 = "Sì. Gino, non prendermi per uno sciocco ma... ehm, come dire...";
			link.l1.go = "rome_1";
		break;
		
		case "rome_1":
			dialog.text = "Parla senza peli sulla lingua, Capitano. Non fare il timido.";
			link.l1 = "Va bene. Puoi stilarmi una lista di massime latine dotte? Vedi, c’è... un tale che ama vantarsi della sua ‘erudizione’ e ogni tanto snocciola quelle frasette in latino per farmi sentire uno zuccone al suo cospetto. Tipo... ‘si vis pacem, para bellum’...";
			link.l1.go = "rome_2";
		break;
		
		case "rome_2":
			dialog.text = "«Si vis pacem, para bellum», dici?";
			link.l1 = "Sì, sì. Voglio impararle per dare una lezione al mio arrogante fr... al mio amico.";
			link.l1.go = "rome_3";
		break;
		
		case "rome_3":
			AddQuestRecordInfo("Rome", "1");
			dialog.text = "Non v’è nulla di strano né di vergognoso nella vostra richiesta, Capitano. Conoscere i detti degli antichi che han lasciato il segno nella storia fa di voi un uomo colto. Ecco qua, prendete questo scritto. È proprio ciò che avete chiesto.";
			link.l1 = "Grazie, Gino! Ti sono debitore! Lo leggerò quando avrò un momento libero...";
			link.l1.go = "exit";
			npchar.quest.rome = true;
			NextDiag.TempNode = "First time";
		break;
		
		case "chemistry":
			RemoveItems(pchar, "chemistry", 1);
			Log_Info("You have given Lavoisier's chemistry textbook");
			dialog.text = "Fammi vedere... (leggendo) Impossibile! Un 'piccolo dono', dici? Questo libro non ha prezzo! Dove diavolo l’hai trovato?! Questo è... un vero tesoro!";
			link.l1 = "Sono lieto che ti piaccia.";
			link.l1.go = "chemistry_1";
		break;
		
		case "chemistry_1":
			dialog.text = "(Leggendo) Incredibile! Non ne avevo mai sentito parlare... e questo? Qui non ci capisco un accidente... ma ci capirò, maledizione! Presto il mio laboratorio ribollirà di lavoro! "+pchar.name+", non hai nemmeno idea di COSA mi hai appena dato...";
			link.l1 = "Perché no? Anzi, sì. Un libro di scienza per un uomo di scienza...";
			link.l1.go = "chemistry_2";
		break;
		
		case "chemistry_2":
			dialog.text = "Ma chi è l’autore di questo prodigio? Antoine-Laurent de Lavoisier, Francia... Mai sentito nominare. Ma aspetta! Com’è possibile! L’anno di stampa è il 1789? Ma che diavolo...";
			link.l1 = "Non so nemmeno io perché quell'anno sia scritto lì sopra. Beh, forse lo so. Ma ti consiglio di non arrovellarti troppo su questa faccenda. Il libro serve, e questo è tutto ciò che conta.";
			link.l1.go = "chemistry_3";
		break;
		
		case "chemistry_3":
			dialog.text = "È promettente oltre ogni dire, e quell’anno dev’essere uno sbaglio di scrittura... Poco importa. Mille grazie, Capitano!";
			link.l1 = "Benvenuto, Gino. È tutto tuo.";
			link.l1.go = "exit";
			if (CheckCharacterItem(pchar, "pistol7"))
			{
				link.l1 = "Non è tutto, Gino. Voglio mostrarti questa pistola. Hai mai visto nulla del genere?";
				link.l1.go = "colt";
			}
			npchar.quest.colt = true;
		break;
		
		case "colt":
			dialog.text = "Non sono un armaiolo, ma posso dare un’occhiata... no, non ho mai visto nulla di simile. Perché lo chiedi?";
			link.l1 = "Questa pistola è potente e micidiale, ma servono cariche speciali per farla sparare. Nient'altro funziona. E non ho la minima idea di come fabbricare altre munizioni. Son venuto qui per chiederti consiglio.";
			link.l1.go = "colt_1";
		break;
		
		case "colt_1":
			dialog.text = "Hai almeno una carica da mostrarmi come esempio? Se non ne hai, temo proprio di non poterti aiutare.";
			if (CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
			{
				link.l1 = "Sì. Il colpo è composto da due parti: la pallottola vera e propria e questo aggeggio che fa esplodere la polvere.";
				link.l1.go = "colt_2";
			}
			else
			{
				link.l1 = "Che fiasco! Che vergogna! Va bene, magari ne troverò altri e te li porterò.";
				link.l1.go = "exit";
				npchar.quest.sample = true;
			}
			DeleteAttribute(npchar, "quest.colt");
		break;
		
		case "colt_2":
			RemoveItems(pchar, "pistol7", 1);
			RemoveItems(pchar, "GunCap_colt", 1);
			RemoveItems(pchar, "shotgun_cartridge", 1);
			Log_Info("You have given a revolver's cartridge");
			Log_Info("You have given a capsule");
			PlaySound("interface\important_item.wav");
			dialog.text = "Interessante! Pare facile, c’è della polvere dentro, una palla si mette da sopra, ma ha un’aria un po’ bizzarra. E questa ‘cosa’… hmm. Senza di lei la polvere non scoppia, giusto? Che diavolo… Senti, Capitano, lascia tutto a me: pistola e cariche. Vieni a trovarmi tra un mese, mi serve un po’ per capire come funziona.";
			link.l1 = "Magnifico! Cerca di capire come funziona, ho proprio voglia di sparare con questa pistola.";
			link.l1.go = "colt_3";
		break;
		
		case "colt_3":
			dialog.text = "Il problema principale è scoprire di che diavolo è fatta questa sostanza che fa saltare la polvere. Questo libro mi tornerà utile. Vedrò di andare a fondo alla faccenda.";
			link.l1 = "D'accordo. Addio, Gino!";
			link.l1.go = "colt_4";
		break;
		
		case "colt_4":
			DialogExit();
			DeleteAttribute(npchar, "quest.sample");
			SetFunctionTimerCondition("Colt_Timer", 0, 0, 30, false); // таймер
		break;
		
		case "cartridge":
			dialog.text = "Sì, ho scoperto di che cosa sono fatte le cariche per la pistola. Devo rendere onore al libro che mi hai donato: senza di esso non ci sarei mai riuscito. Ma devo avvertirti, Capitano, non sarà facile fabbricare proiettili e capsule per quest'arma.";
			link.l1 = "Capsule?";
			link.l1.go = "cartridge_1";
		break;
		
		case "cartridge_1":
			dialog.text = "La capsula è quella ‘cosa’ che, come hai detto tu, fa scoppiare la polvere. Ma partiamo dall’inizio. Sei pronto?";
			link.l1 = "Sì! Ti sto prestando molta attenzione.";
			link.l1.go = "cartridge_2";
		break;
		
		case "cartridge_2":
			AddQuestRecordInfo("Recipe", "shotgun_bullet");
			SetAlchemyRecipeKnown("shotgun_bullet");
			dialog.text = "Dunque, per prima cosa, devi fabbricare una pallottola speciale. Le pallottole comuni non serviranno a nulla. Deve avere una forma conica particolare. Dovrai procurarti uno stampo per questi proiettili, lo stampo per pallottole, come l’ho chiamato io. Prendi dei normali proiettili di piombo, fondili in un crogiolo e versa il piombo fuso nello stampo. Lascia solidificare il tutto e poi estrai la pallottola finita.";
			link.l1 = "E dove posso trovare uno stampo per proiettili del genere?";
			link.l1.go = "cartridge_3";
		break;
		
		case "cartridge_3":
			dialog.text = "Non lo so, Capitano. Sono un alchimista, non un fabbro. Prenda questo proiettile come esempio, magari scoprirà lei cosa farne.";
			link.l1 = "D'accordo. Continua...";
			link.l1.go = "cartridge_4";
		break;
		
		case "cartridge_4":
			AddQuestRecordInfo("Recipe", "shotgun_cartridge");
			SetAlchemyRecipeKnown("shotgun_cartridge");
			dialog.text = "Poi devi fabbricare un contenitore per la polvere. Lì ci infili la palla. Ti ho scritto delle belle istruzioni. Leggile con attenzione e prova tu stesso.";
			link.l1 = "Bene...";
			link.l1.go = "cartridge_5";
		break;
		
		case "cartridge_5":
			AddQuestRecordInfo("Recipe", "GunCap_colt");
			SetAlchemyRecipeKnown("GunCap_colt");
			dialog.text = "Ora dobbiamo recuperare le capsule. Ti servirà una lamina di rame sottilissima - fabbricala tu stesso da una pepita di rame. Ricavaci dei dischetti della stessa misura delle palle. Poi riempili con argento fulminante, usando della cera come supporto.";
			link.l1 = "Argento fulminante? Che diavoleria sarebbe mai questa?";
			link.l1.go = "cartridge_6";
		break;
		
		case "cartridge_6":
			dialog.text = "Non ne sapevo nulla nemmeno io, ho scoperto il segreto dal tuo libro. È una polvere bianca che si può ottenere da argento, spirito e acido nitrico. Basta sfregarla o scuoterla e salta subito per aria, per questo è ottima per accendere la polvere da sparo nei colpi della tua pistola. Robaccia per davvero, mi è già esplosa due volte durante le prove finché non ho trovato la ricetta giusta.";
			link.l1 = "Son stato fortunato ad avere questo libro con me!";
			link.l1.go = "cartridge_7";
		break;
		
		case "cartridge_7":
			dialog.text = "Sta’ molto attento, questa roba scoppia come l’inferno! Potrei produrne un po’ da solo, ma tenere l’argento fulminante è una follia: bisogna metterlo nelle capsule subito dopo averlo fatto. Non so forgiare capsule di rame, te l’ho già detto, non sono mica fabbro.";
			link.l1 = "Va bene. Dammi la ricetta, la imparerò da solo.";
			link.l1.go = "cartridge_8";
		break;
		
		case "cartridge_8":
			AddQuestRecordInfo("Recipe", "OxyHydSilver");
			SetAlchemyRecipeKnown("OxyHydSilver");
			dialog.text = "Sei il benvenuto. Segui la ricetta con precisione e bada bene alla sequenza delle operazioni, o finirai in aria coi fiaschi, come un dannato fuochista ubriaco.";
			link.l1 = "Starò in guardia.";
			link.l1.go = "cartridge_9";
		break;
		
		case "cartridge_9":
			dialog.text = "Inoltre, prendi queste due fiaschette. In questa c’è acido nitrico, nell’altra spirito. Con ciò potrai preparare abbastanza argento fulminante per riempire una ventina di capsule.";
			link.l1 = "Grazie, Gino!";
			link.l1.go = "cartridge_10";
		break;
		
		case "cartridge_10":
			GiveItem2Character(pchar, "Mineral29");
			GiveItem2Character(pchar, "Mineral28");
			Log_Info("You have received a flask of nitric acid");
			Log_Info("You have received a flask of spirit");
			PlaySound("interface\important_item.wav");
			dialog.text = "Prendi anche la tua pistola e la cartuccia d’esempio. Buona fortuna, Capitano, con la fabbricazione delle cariche. Spero che tu resti vivo e tutto d’un pezzo.";
			link.l1 = "Farò tutto il possibile per badare a me stesso. E, Gino, ti ho mai detto che sei un genio?";
			link.l1.go = "cartridge_11";
		break;
		
		case "cartridge_11":
			TakeNItems(pchar, "pistol7", 1);
			TakeNItems(pchar, "shotgun_cartridge", 3);
			TakeNItems(pchar, "GunCap_colt", 1);
			dialog.text = "Mi fai arrossire, Capitano, parlo sul serio...";
			link.l1 = "Va bene. Addio, Gino! Sei il mio miglior alchimista!";
			link.l1.go = "cartridge_12";
		break;
		
		case "cartridge_12":
			DialogExit();
			DeleteAttribute(npchar, "quest.cartridge");
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx":
            dialog.text = "Gord, gord... Mi racconteresti qualcosa di più sul capitano? Da dove viene?";
			link.l1 = "Non ne ho idea, anche se è nato da qualche parte al Nord, a volte lo chiamavano il Vichingo.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Un vichingo! Sì, sì, rammento, ho letto qualcosa del genere in un libro di storia. Un gord è un insediamento fortificato di un jarl libero.";
			link.l1 = "Un jarl libero? E chi diavolo sarebbe costui?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "È un principe dei Nordici. Un tempo, i jarls liberi con le loro bande di guerra saccheggiavano e depredavano l’Europa secoli fa sulle loro navi, i Drakkar. Potresti chiamarli pirati, immagino. I Gords erano le loro basi e le loro case, luoghi dove potevano riposare, coltivare la terra e banchettare.";
			link.l1 = "Capisco. Allora questa tana dev’essere il suo covo di filibustieri... Grazie, Gino!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookFourth");
		break;
		
	// ----------------------------------------- Португалец ----------------------------------------------------
		case "Portugal":
			dialog.text = "Febbri e deliri, dici? Interessante davvero. Portalo qui senza indugio! Vedrò cosa posso fare. Ma bada, se sta troppo male, non ti prometto miracoli... È uno dei tuoi ufficiali?";
			link.l1 = "No, grazie al cielo, non lo è. Gino, ascolta, non chiedere chi sia, fa’ solo quello che puoi, ci tengo davvero, per mille balene!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Va bene, portalo dentro, nella tua stanza. Preparerò qualche intruglio... forse questa radice potrà...";
			link.l1 = "Lo porterò qui subito, senza perdere tempo!";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			PChar.quest.Portugal_DoctorPodhodit.win_condition.l1 = "location";
			PChar.quest.Portugal_DoctorPodhodit.win_condition.l1.location = "SentJons_HouseF3";
			PChar.quest.Portugal_DoctorPodhodit.function = "Portugal_DoctorPodhodit";
		break;
		
		case "Portugal_nomoney":
			dialog.text = "Allora cerca di trovarlo al più presto, non potrò curarlo senza medicine e potrebbe essere troppo tardi se non ti sbrighi.";
			link.l1 = "D'accordo, troverò i soldi.";
			link.l1.go = "exit";
			pchar.questTemp.Portugal.Nomoney = "true";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Splendido, Capitano. Ora mi occuperò di preparare qualche mistura e Le consiglio di lasciar solo il mio paziente. Torni qui domani.";
			link.l1 = "D'accordo, Gino. Ho fiducia nei tuoi intrugli e nel tuo ingegno.";
			link.l1.go = "exit";
			pchar.questTemp.Portugal = "TreatmentCurrent";
			//pchar.GenQuest.CannotWait = true;//запрет ожидания
		break;
		
		case "Portugal_4":
			dialog.text = "Ebbene, credo che fra due settimane starà meglio. Non posso promettere che si metterà a ballare, ma almeno reggersi sulle proprie gambe, questo sì, di certo.";
			link.l1 = "Maledizione, non ho due settimane da perdere! Devo... salpare il prima possibile!";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = "Capitano, non sono un mago, e vi assicuro che quell’uomo è troppo debole, per adesso. Dubito possa reggere qualche giorno a bordo, non potete spostarlo!";
			link.l1 = "Va bene, va bene, ma due settimane... anzi, pure una settimana è già troppo!";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = "Tre giorni... sì, credo che fra tre giorni potrai tentare di salpare, ma avrà bisogno di cure e d’erbe, e dovrai fermarti di tanto in tanto.";
			link.l1 = "Ho trovato un cerusico, si occuperà di lui. Tornerò tra tre giorni e allora lo prenderemo con noi, è tutto quello che posso permettermi. Dobbiamo salpare, anche con qualche sosta... ah, e ancora una cosa – Gino, sei un genio!";
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			dialog.text = "Grazie, Capitano. Torna a riprendere il tuo compare fra tre giorni, ma non disturbarlo prima. Gli serve riposo completo.";
			link.l1 = "Va bene, ho capito. Lo porterò tra tre giorni.";
			link.l1.go = "Portugal_8";
		break;
		
		case "Portugal_8":
			DialogExit();
			SaveCurrentQuestDateParam("questTemp.Portugal_threedays");
			pchar.quest.Portugal_Ill2.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill2.function = "Portugal_ToAntiguaOver";//чтобы не тянул
			pchar.questTemp.Portugal = "TreatmentComplete";
			pchar.quest.Avendel_room.win_condition.l1 = "location";
			pchar.quest.Avendel_room.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room.function = "AvendelSpeach";
		break;
		
		case "Portugal_threedays":
			dialog.text = "Sta andando bene, ma i progressi sono lenti. Non si può ancora mettere le mani su di lui.";
			link.l1 = "Sì - sì, Gino, ricordo. Tre giorni...";
			link.l1.go = "exit";
		break;
		
		case "Portugal_9":
			pchar.quest.Portugal_Ill2.over = "yes";
			dialog.text = "Nessun peggioramento, ma nemmeno grandi miglioramenti. È ancora privo di sensi, non capisce dove si trova né perché sia qui, anche se pare che la cosa non gli dia troppo fastidio. Ha ancora la febbre, quindi non sono certo che portarlo a bordo adesso sia una buona pensata.";
			link.l1 = "Non posso più aspettare, siamo già rimasti qui fin troppo. Prepara i tuoi intrugli per aiutarlo durante il viaggio e ce ne andiamo. Spero che questo bastardo sia abbastanza tosto da restare vivo quel tanto che basta per affrontare la sua condanna a morte...";
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			dialog.text = "Aspetta, Capitano! Ho forse curato un impiccato? Maledizione! Qui è stato fatto un lavoro mastodontico, hai idea di quanto sia dannatamente difficile preparare la polvere asciutta...";
			link.l1 = "Gino, non dovevi sapere questo. Non crucciarti troppo, è un filibustiere, uno dei più temuti della sua razza. Devo portarlo a Curaçao quanto prima per farlo incontrare coi signori della Compagnia. Punto.";
			link.l1.go = "Portugal_11";
		break;
		
		case "Portugal_11":
			dialog.text = "Va bene, ne saprai più di me. Pirata, allora... Curaçao. Come vuoi, ma ascoltami: dormirà quasi sempre, però il rollio della nave e questo caldo maledetto possono far precipitare tutto. Ti consiglio di fermarti dopo qualche giorno di navigazione e di lasciare che il tuo... prigioniero riposi a terra. Altrimenti rischiate d’arrivare a Curaçao con un cadavere da appendere all’albero... ";
			link.l1 = "Va bene, lo farò. La Martinica andrà bene, è quasi a metà strada per Curaçao. Spero che il vento sia favorevole. Lo porto con me adesso e partiremo subito. Ti ringrazio ancora, Gino.";
			link.l1.go = "Portugal_12";
		break;
		
		case "Portugal_12":
			dialog.text = "Benvenuto, Capitano. Ricorda che hai quattro giorni, anzi, facciamo cinque, ma non di più. E un'ultima cosa... sai, di solito curo la gente non per vederla poi finire impiccata dopo le mie cure. Il cerusico risponde per i suoi pazienti, chiunque essi siano. E francamente, non mi sento affatto bene per questo...";
			link.l1 = "Mi dispiace averti trascinato in tutto questo, ma senza di te non avevamo alcuna speranza. Dobbiamo mollare gli ormeggi adesso, o quei figli di portoghese si raduneranno davanti alla nostra porta in attesa del loro capo.";
			link.l1.go = "Portugal_13";
		break;
		
		case "Portugal_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3_Room", "goto", "goto2", "Portugal_JinoNorm", -1);//Джино в свою комнату
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			pchar.quest.Portugal_Ill3.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill3.function = "Portugal_ToAntiguaOver";//5 дней до Мартиники
			pchar.questTemp.Portugal = "ToMartinique";
			pchar.quest.Avendel_room1.win_condition.l1 = "location";
			pchar.quest.Avendel_room1.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room1.function = "AvendelSpeach";
			pchar.quest.Portugal_street.win_condition.l1 = "location";
			pchar.quest.Portugal_street.win_condition.l1.location = "SentJons_town";
			pchar.quest.Portugal_street.function = "PortugalOnStreet";
		break;
		// <-- Португалец
		case "guardoftruth_0":
			dialog.text = "Interessante... E in che modo potresti aiutarmi? Non ho bisogno d’aiuto e non l’ho certo chiesto...";
			link.l1 = "Ma ti servirà. Prima ascoltami, poi decidi.";
			link.l1.go = "guardoftruth";
		break;
		
		case "guardoftruth":
			dialog.text = "Sono tutto orecchi.";
			link.l1 = "Sono stato a Santiago di recente... a trovare padre Vincento. Cercava il suo segretario scomparso, di nome... Gesù, Gino, perché sei diventato pallido come uno straccio?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Tu... hai visto l’inquisitore? È forse...";
			link.l1 = "Non temere, Gino. Non ho alcuna intenzione di consegnarti a lui, anche se così mi ha ordinato: trovarti e portarti da lui. Mi serve qualche informazione su un indio del popolo Itza. Parlami di Tayasal, dei suoi tesori e del 'male' che aleggia su quel luogo.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Vedo che sei ben informato. Te l’ha detto padre Vincento?";
			link.l1 = "Ho avuto delle informazioni da lui e qualcuna da altra gente. Ma vorrei sentire anche la tua versione. Sei stato il suo segretario, dunque avrai sicuramente redatto il verbale dell’interrogatorio, o sbaglio?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Non puoi nemmeno immaginare cosa stesse facendo a quel povero indiano!.. Mi vengono i brividi ogni volta che ripenso a quell’interrogatorio.";
			link.l1 = "Tuttavia, parliamone. Chi era quell’indiano? Come è finito nelle grinfie di padre Vincento?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Era tra gli indios del popolo Itza che partirono da Tayasal in cerca della Maschera di Kukulcan, un cimelio del dio antico dei Maya – Kukulcan. Quegli indios si imbatterono in una banda di avventurieri bianchi guidati da Archibald Calhoun, uno scozzese cacciatore di tesori. Solo uno degli indios sopravvisse, si chiamava Ksatl Cha. Aveva con sé tre oggetti davvero curiosi, ma di quelli ti parlerò più avanti. \ Calhoun tentò di far sputare il rospo al prigioniero sui tesori, ma quello rimase muto come un pesce. Così lo scozzese lo consegnò a Santiago, a padre Vincento, ottenendo in cambio il permesso di girare per un anno nei porti spagnoli. Sapeva bene che l’inquisitore andava ghiotto per misteri e leggende locali. Vincento riuscì a sciogliergli la lingua. L’indio cominciò a parlare senza freni, raccontandoci ogni cosa sapeva – e quello che scoprimmo lasciò di stucco perfino l’inquisitore.";
			link.l1 = "Ma davvero? E cosa mai potrebbe far tremare Sua Grazia?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Te lo racconterò tutto per filo e per segno. Nelle profondità delle giungle dello Yucatán si trova un’antica città Maya chiamata Tayasal. Vi abitano i discendenti dei Maya – il popolo Itza. Cercano di vivere secondo le leggi e le usanze degli antenati. Di certo, non sopportano lo stato del mondo moderno – intendo il dominio dell’uomo bianco. Sognano i bei tempi andati. Ma ora arriva la parte più succosa. Un branco di avventurieri bianchi, per caso, si avvicinò a Tayasal e rapì la figlia del capo supremo degli Itza. Accadde quasi un quarto di secolo fa. Questo fu il colpo di grazia, e Kanek, il capo, fu preso da furia. Decise allora di compiere il più pericoloso e segreto dei riti Maya – evocare un dio indiano per spazzare via tutta la stirpe dei conquistadores bianchi...";
			link.l1 = "Hmm... Dev'essere il demonio di cui parlava padre Vincento. Ma come farà questo dio indiano a trattare con i bianchi coloni? Si mostrerà sotto forma di drago e li brucerà tutti quanti?";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Oh, "+pchar.name+", lascia queste storie di mostri di fuoco alle vecchie comari! In realtà, non sei tanto fuori strada, ma la nostra faccenda è ben più complessa e grave. Nemmeno il Diluvio riuscirebbe a fermare l'espansione dell'Europa nel Nuovo Mondo. Per ogni morto ne sbucheranno dieci. Kanek doveva annientare proprio la possibilità stessa della colonizzazione europea.";
			link.l1 = "Ebbene sì, è già successo.";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Stai ragionando bene, Capitano... Lo scopo del rito di Kanek non era solo evocare l’Essere Supremo, ma anche spalancare una falla nello spazio e nel tempo.";
			link.l1 = "Cosa?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Gli antichi Maya avevano una sapienza fuori dal comune, Capitano. Kanek ha trovato la descrizione di un rito che permette di dominare il tempo.";
			link.l1 = "Per mille balene! Incredibile!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Ascolta. Lo scopo finale del rituale è cambiare il passato, così che l’arrivo dell’uomo bianco nel Nuovo Mondo diventi impossibile. Per riuscirci, intendono mandare qualcuno indietro nel tempo, uno che abbia autorità, potere e la forza di mutar il destino degli uomini. Ma soprattutto, costui dovrà possedere la sapienza dei tempi moderni.\nPensaci, "+pchar.name+", cosa sarebbe accaduto a Colombo se le sue caravelle fossero state accolte da una flotta indiana di fregate e galeoni armati di cannoni moderni? E se gli archibugi dei soldati bianchi non avessero trovato archi e lance, ma mortai e moschetti ad attenderli?";
			link.l1 = "Suppongo che le Americhe non sarebbero mai state scoperte del tutto...";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Esattamente! E magari qualche Colombo indiano avrebbe scoperto l’Europa...";
			link.l1 = "Interessante, e chi manderà Kanek nel passato? Uno dei suoi guerrieri nudi? Dubito che riuscirà a insegnare qualcosa ai suoi antenati...";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "Non ridere, Capitano. Kanek non ha passato anni nei templi Maya a leggere i loro scritti per niente. Un dio indiano dev’essere mandato nel passato sotto forma d’uomo...";
			link.l1 = "Gino, che sciocchezze stai blaterando? Sei forse...";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "Anche il Figlio del nostro Signore, Gesù Cristo, è venuto su questa terra in forma umana ed è nato da una donna mortale, la Santa Vergine Maria...";
			link.l1 = "Gesù, Gino... dici sul serio?";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "Certamente lo sono. Ksatl Cha è stato davvero convincente...";
			link.l1 = "Ma quale dio ha scelto Kanek per una missione così ‘nobile’?";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "Il rito doveva evocare un solo Alto Essere. Il serpente piumato, Quetzalcoatl, Kukulcan...";
			if (CheckAttribute(pchar, "questTemp.Dolly")) link.l1 = "Kukulcan?! Ho già avuto la sventatezza d’incontrare il suo ‘spirito’ che dimora in statue. Ora capisco… continua!";
			else link.l1 = "Mm. Interessante. Quel nome l’ho già sentito dal padre Vincento... continua!";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Kanek decise di evocare Kukulcan, poiché gli Itza già possedevano un antico artefatto di questo dio: la Maschera di Kukulcan. Colui che indossa la maschera può varcare il portale, e solo lui sarà accolto dagli antichi Maya come divinità vivente.\nIl sacerdote officiò il rito, chiamando Kukulcan a incarnarsi nel corpo di un mortale. Creò inoltre una fessura temporale che risucchiò alcune persone a caso dal futuro nel nostro tempo.\nLo scopo di questo richiamo era donare all’incarnazione di Kukulcan non solo la conoscenza della nostra epoca, ma anche del futuro. Ma qualcosa andò storto, e tutte quelle persone finirono altrove e non a Tayasal. Non ne ho mai incontrata nessuna.\nFurono creati diversi portali nell’arcipelago: dovevano trasportare i detentori del sapere futuro e gli agenti Itza ovunque nella zona e fino a Tayasal. Ma questi portali hanno fallito, nessuno è giunto a Tayasal negli ultimi venticinque anni...";
			if (CheckAttribute(pchar, "questTemp.Dolly"))
			{
				link.l1 = "Certo... Perché questi portali trasferiscono i prigionieri solo l'uno all'altro. Incredibile!";
				link.l1.go = "guardoftruth_15a";
			}
			else
			{
				link.l1 = "Interessante...";
				link.l1.go = "guardoftruth_16";
			}
		break;
		
		case "guardoftruth_15a":
			dialog.text = "Hai visto quei portali? Dimmi subito!";
			link.l1 = "Forse dopo, Gino... Al momento mi interessa di più la tua storia. Continua!";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "Padre Vincento è al corrente di tutto ciò che ti ho raccontato. Naturalmente, questo lo ha fatto preoccupare. Se Kukulcan, incarnato in forma umana, raggiungerà il portale con la Maschera e tutto il sapere che ha raccolto... la fine dei tempi, l’Apocalisse.\nSe il passato cambia – anche il futuro si trasforma. La nostra realtà muterà, svanirà, si dissolverà. Tu ed io potremmo non nascere mai. Oppure saremo diversi. Quando Kukulcan toccherà il passato – noi cesseremo d’esistere.";
			link.l1 = "E chi sarebbe l’incarnazione di Kukulcan?";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Chi può dirlo. Potrebbe essere chiunque sia nato un quarto di secolo fa, quando il rituale fu compiuto. Magari tu... scherzo, ovviamente. Ma una speranza resta. Primo: l’incarnazione di Kukulcan è solo un semplice mortale, può affogare, essere infilzato, crivellato di piombo o crepare di febbre. E in tal caso, nessun finimondo ci minaccia.\nSecondo: non si può raggiungere il passato senza la maschera, Kanek l’ha nascosta così bene che forse nemmeno lui saprebbe dove cercare. Potrebbe anche darsi che lo stesso Kukulcan reincarnato non la trovi mai.";
			link.l1 = "Raccontami di più.";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Tempo dopo il rituale, un gruppo di conquistadores spagnoli quasi raggiunse Tayasal e fu a un soffio dal tesoro. Gli Itza riuscirono a sterminarli tutti tranne uno – un gigante alto sette piedi. Kanek temeva che la Maschera potesse essere rubata da chiunque, così decise di proteggerla con un incanto. Si inventò un proprio rito, attingendo alla sapienza degli antichi Maya. Prese tre oggetti, che secondo lui racchiudevano il potere dell’uomo bianco: un pugnale appartenuto allo stesso Cortez, una bussola, e usò quel pugnale per scorticare un pezzo di pelle dalla schiena del gigante spagnolo catturato, a far da terzo ingrediente. L’uomo fu poi sacrificato sull’altare di Kukulcan. Tre oggetti per il rituale.\nDa quel rito nacque un’isola nuova, in mare aperto non lontano dallo Yucatan. Nessuno sa dove sia, ma la Maschera è nascosta là. Per trovarla servono il pugnale, la bussola e quel pezzo di pelle. Inoltre, ogni tesoro della camera è maledetto: nessuno può lasciare l’arcipelago. Chi ci prova scatenerà una tempesta che spingerà la nave dritta sulle rocce dell’isola dove sta la Maschera. Si chiama Ksocheatem. Furbo, eh?";
			link.l1 = "Forse anche troppo sveglio. Su questo non si discute. Ma come diavolo faceva Ksatl Cha ad essere così ben informato? Dubito che Kanek si mettesse a spifferare certe cose ai semplici guerrieri...";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "Vedi, l’attuale capo degli Itza, Urakan, figlio di Kanek, aveva confidato tutto a quel guerriero. Mandò Ksatl Cha con una schiera di guerrieri a cercare l’isola segreta e la Maschera di Kukulcan. Gli affidò il Custode della Verità: così chiamano quei tre oggetti insieme — il pugnale, la bussola e la mappa fatta di pelle umana.";
			link.l1 = "La mappa? E perché Urakan aveva bisogno della Maschera? Aveva deciso di riscrivere il passato da solo?";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "La pelle reca i contorni dell’arcipelago, perciò la chiamano la mappa. Urakan voleva la Maschera per una ragione assai semplice: non desiderava distruggere il mondo così com’è, né sacrificare la propria vita e il sangue della sua gente per la gloria degli antichi.\nPer questo era disposto a tutto pur di distruggere la Maschera. Ma Ksatl Cha fu catturato da Calhoun e... beh, il resto della storia lo conosci. Non arrivò mai a Ksocheatem.";
			link.l1 = "Quindi è possibile scongiurare la fine dei tempi trovando e distruggendo la Maschera? E dov’è ora quel... Custode della Verità?";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "Il pugnale 'Artiglio del Capo' e la bussola 'Freccia della Via' furono lasciati a Calhoun, mentre la mappa di pelle 'Delle due sembianze' si trova ancora da qualche parte nell’Inquisizione. Calhoun la usò come bavaglio per tappare la bocca al prigioniero. Non aveva la minima idea a cosa servissero questi oggetti.";
			link.l1 = "Come hai detto? ‘L’Artiglio del Capo’? Maledizione, ho proprio questo pugnale addosso adesso! Fadey me l’ha dato per saldare il suo debito con mio fratello! Guarda qui!";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			dialog.text = "Incredibile... Proprio così. Me lo ricordo.";
			link.l1 = "Gino, dimmi, cosa sa esattamente padre Vincento della tua storia?";
			link.l1.go = "guardoftruth_23";
		break;
		
		case "guardoftruth_23":
			dialog.text = "Tutto, tranne le notizie sul Custode della Verità e il modo per farsi mostrare il luogo dell’isola segreta dove si cela la Maschera di Kukulcan. Di questo me ne parlò Ksatl Cha quando restammo soli, proprio prima che gli dessi una mistura velenosa per placare le sue pene. Morì col sorriso sulle labbra. \nDi certo, dopo quel che feci, non potevo più restare a Santiago. Avevo il brutto sentore d’essere ormai un testimone troppo scomodo per l’inquisitore. Padre Vincento ottiene sempre ciò che vuole, a qualsiasi prezzo. Ksatl Cha gli aveva già svelato il segreto del tesoro di Tayasal.";
			link.l1 = "Questi tesori sono già stati scoperti da un certo avventuriero di nome Miguel Dichoso. L’hai mai sentito nominare?";
			link.l1.go = "guardoftruth_24";
		break;
		
		case "guardoftruth_24":
			dialog.text = "No. E dov’è ora, coi suoi tesori?";
			link.l1 = "Lo voglio sapere anch’io. È per questo che sono venuto da te, sto cercando quell’oro indiano. Dichoso ha portato i tesori in Europa e si è dileguato con essi.";
			link.l1.go = "guardoftruth_25";
		break;
		
		case "guardoftruth_25":
			dialog.text = "Ti rivelerò dove sono i tesori e lo stesso Dichoso.";
			link.l1 = "Gino, mi sorprendi. Come diavolo fai a saperlo?!";
			link.l1.go = "guardoftruth_26";
		break;
		
		case "guardoftruth_26":
			dialog.text = "Puoi capirlo da solo dalla mia storia, Capitano. I tesori di Tayasal erano maledetti – nessun oggetto può lasciare l’arcipelago. Ogni nave...";
			link.l1 = "... verrà inghiottito dalla tempesta e scaraventato sull'isola dove si cela la Maschera di Kukulcan! Ero cieco, ma ora vedo. Pare che sappia abbastanza per trovare Ksocheatem, i tesori e la Maschera stessa!";
			link.l1.go = "guardoftruth_27";
		break;
		
		case "guardoftruth_27":
			dialog.text = "Vuoi salvare il mondo, Capitano?";
			link.l1 = "Voglio ritrovare mio fratello scapestrato... Gino, come faccio a far sì che il Guardiano della Verità mi riveli dove si trova l’isola? Hai detto che conosci il modo!";
			link.l1.go = "guardoftruth_28";
		break;
		
		case "guardoftruth_28":
			dialog.text = "So il metodo, ma non conosco i dettagli. Non potrò aiutarti finché non avrò tutti i componenti del Guardiano.";
			link.l1 = "Hm. Abbiamo già preso il pugnale. Restano solo la bussola e la mappa. Calhoun ha la bussola e padre Vincento tiene la mappa...";
			link.l1.go = "guardoftruth_29";
		break;
		
		case "guardoftruth_29":
			dialog.text = "Vuoi tornare dall’inquisitore?   Ma come pensi di riferire riguardo a...";
			link.l1 = "Devo convincere padre Vincento che sei morto, Gino. Solo allora smetterà di cercarti. Diciamo che ti è venuto un colpo appena mi hai visto. Dammi qualcosa che possa servire come prova della tua dipartita.";
			link.l1.go = "guardoftruth_30";
		break;
		
		case "guardoftruth_30":
			dialog.text = "Vincento non crederà alla storia dell’infarto, ma si berrà la байка se gli dici che mi sono tolto la vita bevendo del veleno che sa di mandorla. Dagli il mio almanacco, sa bene che non me ne separo mai.";
			link.l1 = "Va bene. Ho bisogno di quel legame con l’inquisitore. Sicuramente sa un sacco dei nostri affari.";
			link.l1.go = "guardoftruth_31";
		break;
		
		case "guardoftruth_31":
			dialog.text = "Sta attento con padre Vincento. È feroce come una tigre e gioca la sua partita. Non condividerà né i tesori né la gloria con te.";
			link.l1 = "Capisco, va bene, Gino, dammi il tuo almanacco e cerca di ricordare cosa ti ha detto l’indiano riguardo al Guardiano della Verità, perché voglio metterlo insieme. Devo trovare Ksocheatem, sono certo che là troverò non solo la maschera e i tesori, ma anche il mio caro fratello.";
			link.l1.go = "guardoftruth_32";
		break;
		
		case "guardoftruth_32":
			dialog.text = "Prendilo. Buona fortuna, Capitano!";
			link.l1 = "Non sto dicendo addio, Gino...";
			link.l1.go = "guardoftruth_33";
		break;
		
		case "guardoftruth_33":
			DialogExit();
			Log_Info("You have received an almanac");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "Almanac");
			ChangeItemDescribe("Almanac", "itmdescr_jinobook");
			pchar.questTemp.Guardoftruth = "twoitems";
			AddQuestRecord("Guardoftruth", "37");
		break;
		
		case "guardoftruth_34":
			dialog.text = "È stata dura, Capitano?";
			link.l1 = "Non parliamone... Troppa gente è crepata per mettere le mani su questi oggetti. Troppa. Pare che non sia l’unico a bramare d’incontrare il misterioso Ksocheatem.";
			link.l1.go = "guardoftruth_35";
		break;
		
		case "guardoftruth_35":
			dialog.text = "Posso immaginare... A proposito, come sta padre Vincento? Sei ancora in contatto con lui?";
			link.l1 = "Finora sì, ma credo che ormai non sia più necessario. Ho raccolto tutti i pezzi del Guardiano della Verità, quindi possiedo la chiave per il luogo di Ksocheatem. Non vedo alcuna fretta di annunciare il mio successo a Sua Grazia, per qualche strana ragione.";
			link.l1.go = "guardoftruth_36";
		break;
		
		case "guardoftruth_36":
			dialog.text = "Sta' attento, "+pchar.name+"Padre Vincento ha cento occhi e mille mani. Mani lunghe come il diavolo...";
			link.l1 = "Ho passato di tutto negli ultimi mesi e ormai non temo più né padre Vincento, né i suoi occhi, né le sue mani. Poco importa. È ora che troviamo Ksocheatem usando i pezzi del Guardiano. Sai come si fa, tu?";
			link.l1.go = "guardoftruth_37";
		break;
		
		case "guardoftruth_37":
			dialog.text = "In verità no. Ksatl Cha è stato piuttosto vago. Credo che quell’indiano non sapesse davvero come mettere in moto il Guardiano. Lascia a me quei pezzi e proverò a capirci qualcosa. Torna tra due giorni e forse avrò risolto questo enigma.";
			link.l1 = "D’accordo, Gino. Conto su di te. Tieni, prendi questi.";
			link.l1.go = "guardoftruth_38";
		break;
		
		case "guardoftruth_38":
			dialog.text = "Puoi star certo che con me resteranno al sicuro e interi.";
			link.l1 = "Non ne dubito affatto. Ebbene, per ora non ti disturbo oltre, Gino. Buona fortuna con le tue ricerche!";
			link.l1.go = "guardoftruth_39";
		break;
		
		case "guardoftruth_39":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			RemoveItems(pchar, "knife_01", 1);
			RemoveItems(pchar, "skinmap", 1);
			RemoveItems(pchar, "arrowway", 1);
			pchar.questTemp.Guardoftruth = "end";
			SetFunctionTimerCondition("Ksochitam_StartSearchIsland", 0, 0, 2, false);
			CloseQuestHeader("Guardoftruth");
			AddQuestRecord("Ksochitam", "1");
		break;
		
		case "ksochitam":
			dialog.text = "In parte. Voglio dire, ho qualche indizio, ma non so proprio come far quadrare tutto sul serio. Proviamo a risolvere questo enigma insieme.";
			link.l1 = "Proviamoci! Dimmi che idee hai.";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "Ksatl Cha disse qualcosa del genere: 'L'Artiglio del Capo farà svelare la mappa. La Freccia del Cammino mostrerà la via delle apparizioni.'";
			link.l1 = "E che cosa sei riuscito a combinare?";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "Ho capito come far sì che la mappa si 'sveli'. Hai già dato un’occhiata alla mappa delle Due Apparizioni?";
			link.l1 = "Hm. E c’era qualcosa di particolare? Qualche contorno confuso dell’arcipelago...";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			GiveItem2Character(pchar, "skinmap");
			dialog.text = "Prendilo e guardalo di nuovo. Sta’ attento.";
			link.l1 = "Ebbene, facciamolo pure, se insisti.";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_1";
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "ksochitam_wait":
			dialog.text = "Non hai nemmeno dato un’occhiata alla mappa, "+pchar.name+"...";
			link.l1 = "Sì-sì, lo farò subito...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_wait";
		break;
		
		case "ksochitam_5":
			dialog.text = "";
			link.l1 = "Ho visto. Nulla di nuovo all'orizzonte. Solo sagome confuse d’isole e della costa. Cosa dovrei scorgere, secondo te?";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "Aspetta un attimo. Ora devi far sì che questa mappa si riveli. Prendi il pugnale e sfiora dolcemente la mappa con la sua lama. Non premere, dobbiamo evitare qualsiasi danno. Prendi il pugnale. E osserva bene!";
			link.l1 = "Interessante! Vediamo un po'...";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			DialogExit();
			GiveItem2Character(pchar, "knife_01");
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_2";
			sld = ItemsFromID("skinmap");
			sld.mark = 2;
		break;
		
		case "ksochitam_8":
			dialog.text = "Ebbene, adesso noti qualche differenza?";
			link.l1 = "Sì. Quando tocchi la mappa col pugnale compaiono due segni a forma di teschio, sempre negli stessi punti...";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "Negli STESSI due posti, "+pchar.name+" Ecco perché la chiamavano la mappa delle Due Facce!";
			link.l1 = "E che vuol dire?";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "Penso parecchio... Ma ci aspettano altri enigmi. Suppongo che questi teschi siano proprio le apparizioni di cui parlava Ksatl Cha. Dunque la bussola dovrebbe indicare la giusta rotta verso Ksocheatem partendo da loro. Hai visto la bussola, "+pchar.name+"?";
			link.l1 = "Sì. Sembra una bussola da marinaio qualsiasi, ma si comporta in modo strano: la sua freccia sussulta in tutte le direzioni o inizia a girare come una matta.";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "Pensavo che piazzare la bussola sui teschi avrebbe fermato la sua freccia e mostrato una direzione chiara sulla mappa. Così ho provato a fissarla prima su un teschio, poi sull’altro, mentre toccavo la mappa col pugnale.";
			link.l1 = "E allora?";
			link.l1.go = "ksochitam_12";
		break;
		 
		case "ksochitam_12":
			dialog.text = "Inutilmente. La bussola non ha cambiato comportamento. L’ago gira ancora come un forsennato. Pare che stia sbagliando qualcosa. Oppure ho frainteso le parole di Ksatl Cha.";
			link.l1 = "Quindi il pugnale e la mappa funzionano, ma la bussola no?";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			dialog.text = "La Freccia del Cammino dev’essere funzionante, solo che ancora non sappiamo come diavolo farla partire. "+pchar.name+",  tu conosci la geografia dell’arcipelago meglio di me... Dimmi, quali luoghi svela la mappa delle due apparizioni?";
			link.l1 = "Un attimo! (dando un’occhiata)... Ebbene, ebbene... Quella sagoma a sinistra è la terraferma d’Occidente. Quella a destra sembra proprio l’isola di Dominica. Più o meno.";
			link.l1.go = "ksochitam_14";
		break;
		
		case "ksochitam_14":
			dialog.text = "E dimmi: c’è... qualcosa di notevole in quei posti?";
			link.l1 = "Cosa vuoi dire?";
			link.l1.go = "ksochitam_15";
		break;
		
		case "ksochitam_15":
			dialog.text = "Non saprei nemmeno io... Beh, qualcosa di particolare?";
			link.l1 = "Gino, non parlare per enigmi. Spiegati chiaramente.";
			link.l1.go = "ksochitam_16";
		break;
		
		case "ksochitam_16":
			dialog.text = "Posso solo supporre che questi teschi ci indichino dei luoghi reali. La Freccia della Via non funziona se puntata sulle immagini della mappa. Forse funzionerà vicino alle vere conformazioni geografiche che la mappa ci ha rivelato?";
			link.l1 = "Gino, sei un genio! Main occidentale, Dominica? Quelle teste sono troppo grosse per indicare i posti precisi.";
			link.l1.go = "ksochitam_17";
		break;
		
		case "ksochitam_17":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = ""+pchar.name+", facciamo così: Portami una mappa cartacea dell’arcipelago, uniscila a quella delle Due Apparizioni e segna le apparizioni con delle croci. Forse così ti verrà qualche supposizione?";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "Ho questa vecchia mappa dell’arcipelago.";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "Ho tra le mani una mappa pregiata dell’arcipelago.";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "Ho tra le mani questa splendida mappa dell’arcipelago.";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "Affare fatto. Ti porterò una mappa e poi si continua...";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_17_1":
			dialog.text = "Oh, dai, "+pchar.name+"Questo pergamena dei tempi di Colombo non è molto meglio della mappa di pelle. Son certo che al mondo c’è di meglio di questa robaccia. Portami un’altra mappa, più recente!";
			link.l1 = "D'accordo...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_2":
			dialog.text = "Splendido! Ora segna i luoghi delle apparizioni su questa. Così sarà più facile fare supposizioni.";
			link.l1 = "Un attimo solo, Gino!";
			link.l1.go = "ksochitam_18";
		break;
		
		case "ksochitam_17_3":
			dialog.text = "Non penserai davvero che rovineremo una mappa così magnifica con le nostre scarabocchiate. Ti servirà ancora, "+pchar.name+"Portami un’altra mappa, magari una meno pretenziosa!";
			link.l1 = "D’accordo...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_map_wait":
			dialog.text = "Mi hai portato una mappa dell’arcipelago, "+pchar.name+"?";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "Ho questa vecchia mappa dell'arcipelago.";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "Ho qui una splendida carta dell’arcipelago.";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "Ho messo le mani su questa splendida mappa dell’arcipelago.";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "Non ancora, ma l’ho già ordinato. Presto lo avrò e allora proseguiremo...";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_18":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_19";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto1", "Ksochitam_SitTable", -1);
		break;
		
		case "ksochitam_19":
			dialog.text = "";
			link.l1 = "Fatto... Ho tracciato i segni, ma sono ancora informazioni approssimative. Il primo posto si trova da qualche parte a nord-ovест di Blueweld. Il secondo è nel cuore dell'isola di Dominica.";
			link.l1.go = "ksochitam_20";
		break;
		
		case "ksochitam_20":
			dialog.text = "Hai qualche idea?";
			link.l1 = "No. Ma penso che dovremmo portare là la Freccia della Via e vedere come si comporta. Certo, è come cercare un ago in un pagliaio, ma non abbiamo idee migliori comunque.";
			link.l1.go = "ksochitam_21";
		break;
		
		case "ksochitam_21":
			dialog.text = "Sono d'accordo con te, "+pchar.name+". Mi permetterai di salpare con te?";
			link.l1 = "Vuoi davvero mettere alla prova le tue supposizioni? Sarebbe un onore averti sul ponte della mia nave, Gino. Fai il fagotto!";
			link.l1.go = "ksochitam_22";
		break;
		
		case "ksochitam_22":
			dialog.text = "Non ci vorrà molto. Sarò pronto fra poche ore. Tieni, prendi la Freccia della Via.";
			link.l1 = "Benvenuto a bordo!";
			link.l1.go = "ksochitam_23";
		break;
		
		case "ksochitam_23":
			LAi_SetOwnerType(npchar);
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_24";
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetPlayerType(pchar);
			GiveItem2Character(pchar, "arrowway");
			pchar.questTemp.Ksochitam = "seekway";
			sld = ItemsFromID("skinmap");
			sld.mark = 1;
			pchar.quest.Ksochitam_room.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Ksochitam_room.win_condition.l1.location = pchar.location;
			pchar.quest.Ksochitam_room.function = "Ksochitam_JinoPassenger";
			AddQuestRecord("Ksochitam", "2");
		break;
		
		case "ksochitam_24":
			dialog.text = "Sì-sì, "+pchar.name+", Mi sto preparando. Sarò pronto fra poco.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_24";
		break;
		
		case "ksochitam_25":
			dialog.text = "E allora, "+pchar.name+", abbiamo avuto fortuna nelle nostre ricerche?";
			link.l1 = "Avevamo ragione. Eccolo qui. L’idolo indiano è una delle manifestazioni.";
			link.l1.go = "ksochitam_26";
		break;
		
		case "ksochitam_26":
			dialog.text = "Oh! Dev'essere uno di quegli idoli che, si dice, trasportavano la gente a Tayasal! Te ne parlavo, ricordi? Allora, dov'è che punta la Freccia della Via?";
			link.l1 = "È puntato a nord-ovest. Ho segnato la direzione sulla mappa. Ma la linea tracciata attraversa quasi tutto il mar dei Caraibi. Dobbiamo trovare un altro segno a Dominica per scovare Ksocheatem.";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_27":
			dialog.text = "Sono certo che troveremo un altro idolo laggiù... sei d'accordo con la mia ipotesi, "+pchar.name+"?";
			link.l1 = "Sì, Gino. Non perdiamo tempo e mettiamoci subito a cercare.";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_28":
			DialogExit();
			locations[FindLocation(pchar.location)].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
		break;
		
		case "ksochitam_29":
			dialog.text = "E quindi, "+pchar.name+", hai trovato qualcosa d'interessante?";
			link.l1 = "Avevamo ragione. Eccolo qui. L’idolo indiano è una delle manifestazioni.";
			link.l1.go = "ksochitam_30";
		break;
		
		case "ksochitam_30":
			dialog.text = "Oh! Dev'essere uno di quegli idoli che si diceva trasportassero la gente a Tayasal! Te ne parlavo, ti ricordi? Allora, dov'è che punta la Freccia del Cammino?";
			link.l1 = "Nord-ovest. Ho segnato la rotta sulla mappa. Ma la linea tracciata taglia quasi tutto il maledetto mar dei Caraibi. Tocca scovarci un altro approdo sulla terraferma per trovare Ksocheatem.";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_31":
			dialog.text = "E allora, "+pchar.name+", hai trovato il secondo idolo?";
			link.l1 = "Sì. Ho tracciato la direzione indicata dalla Freccia del Cammino. Ora sappiamo dove si trova Ksocheatem, non proprio il punto preciso, ma sappiamo dove cercare! Perlustrerò tutta la zona dove si incrociano le rotte e troverò quell’isola maledetta!";
			link.l1.go = "ksochitam_32";
		break;
		
		case "ksochitam_32":
			dialog.text = "Sono lieto di sentire tanto ardore nella tua voce. Ma occorre prepararci con cura per la spedizione che ci attende, ché non sappiamo quali sorprese ci riserverà. Dubito che ci accoglieranno a braccia aperte laggiù...";
			link.l1 = "Ti crucci per qualcosa in particolare o stai solo sfogando le tue inquietudini?";
			link.l1.go = "ksochitam_33";
		break;
		
		case "ksochitam_33":
			dialog.text = "Pensaci su, "+pchar.name+".. Ksocheatem fu forgiata dalla magia dei Maya per mano di Kanek. Non è una formazione naturale e vi alberga un potere malvagio e distruttivo. Nessuno sa cosa ci attende laggiù, ma dubito che troveremo sole, mari placidi, puttane e venti gentili.";
			link.l1 = "Va bene, Gino. Terrò conto delle tue parole e mi preparerò per la spedizione. Metterò in ordine la mia nave e provvederò a pozioni e munizioni...";
			link.l1.go = "ksochitam_34";
		break;
		
		case "ksochitam_34":
			dialog.text = "Una scelta assai saggia. Allora, torniamo alla nave?";
			link.l1 = "Certo! Andiamo!";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_35":
			dialog.text = "Siamo arrivati, "+pchar.name+"! Uh, il vento ulula!";
			link.l1 = "Sì, Gino, avevi ragione, nessun sole a darci il benvenuto... e nemmeno una sgualdrina in vista. In verità, non si sa proprio che diavolo ci aspetti qui.";
			link.l1.go = "ksochitam_36";
		break;
		
		case "ksochitam_36":
			dialog.text = "Eh, capitano, avete scelto proprio un pessimo posto per sbarcare! Solo scogli e dirupi ovunque! E come pensate di raggiungere l'interno dell’isola da qui?";
			link.l1 = "Non ho visto nessun’altra baia decente dove sbarcare su quest’isola, maledetta tempesta! Bah, meglio questo che niente. Saprò farmi strada tra queste rocce, ho visto di peggio. Niente panico, compare!";
			link.l1.go = "ksochitam_37";
		break;
		
		case "ksochitam_37":
			dialog.text = "Quest’isola mi puzza, "+pchar.name+"È una faccenda inquietante. E questa tempesta dev’essere legata all’isola. Questo posto è maledetto, senza dubbio!";
			link.l1 = "Nemmeno a me piace questo posto, Gino! Ma quest’isola esiste davvero, il che vuol dire che la storia di Kukulcan è vera. Saremo tutti nei guai se riesce ad arrivare a Tayasal con la Maschera...";
			link.l1.go = "ksochitam_38";
		break;
		
		case "ksochitam_38":
			dialog.text = "Cerca di trovare la Maschera, Capitano! Vale più di tutti i tesori del mondo! Dev’essere nei paraggi, da qualche parte! Quando l’avremo, manderemo all’aria i piani di Kukulcan e non gli permetteremo di cambiare il passato!";
			link.l1 = "E come sarebbe questa maschera, lo sai?";
			link.l1.go = "ksochitam_39";
		break;
		
		case "ksochitam_39":
			dialog.text = "Non ne ho la minima idea!  Ma sono certo che lo riconoscerai, è un antico manufatto indiano, difficile confonderlo con qualcos’altro!";
			link.l1 = "Capisco. Terrò gli occhi aperti! Va bene, Gino, torna sulla nave! Non serve che ti aggiri per l’isola, la tua testa vale troppo per rischiarla!";
			link.l1.go = "ksochitam_40";
		break;
		
		case "ksochitam_40":
			dialog.text = "Non ti mentirò, Capitano, sono una frana con la spada e questo posto mi mette a disagio. Vuoi ascoltare un consiglio? Ogni parte del Guardiano è legata alla magia di quest’isola. Ksatl Cha ha accennato che il pugnale comanda i locali, ma non saprei dirti come.\nRimarrò a bordo. Se ti serve una mano, cercami lì.";
			link.l1 = "Bene. E adesso augurami fortuna, Gino!";
			link.l1.go = "ksochitam_41";
		break;
		
		case "ksochitam_41":
			dialog.text = "Buona fortuna, "+pchar.name+"Che Dio ti benedica e ti protegga!";
			link.l1 = "...";
			link.l1.go = "ksochitam_42";
		break;
		
		case "ksochitam_42":
			DialogExit();
			NextDiag.CurrentNode = "adversary";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "rld", "aloc0", "Ksochitam_JinoStay", 10.0);
			AddQuestRecord("Ksochitam", "6");
		break;
		
		case "adversary":
			dialog.text = "Come te la passi, "+pchar.name+"Hai bisogno di un consiglio, eh?";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L1"))
			{
				link.l1 = "Quest'isola maledetta pullula di non-morti, e quei dannati scheletri sono più tosti di quanto sembrino. Non ho la minima idea di come affrontarli.";
				link.l1.go = "adversary_1";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L2"))
			{
				link.l1 = "Se prendi a sinistra al bivio, prima o poi arrivi alla grotta.   Ma dove diavolo dovrei andare dopo?   Ho il sospetto che quella grotta sia una trappola senza uscita...";
				link.l1.go = "adversary_2";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L3"))
			{
				link.l1 = "Ho trovato un passaggio dentro la grotta umida, puoi tuffarti nella sua parte sommersa. Ma non vedo alcuna via d’uscita laggiù...";
				link.l1.go = "adversary_3";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L4"))
			{
				link.l1 = "Se prendi a sinistra al bivio arriverai alla caverna. Ma dove dovrei andare dopo? Temo che la caverna sia un vicolo cieco...";
				link.l1.go = "adversary_4";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L5"))
			{
				link.l1 = "C'è un punto nella grande caverna dove puoi tuffarti nella parte allagata. Ma pare che da lì non ci sia via d’uscita...";
				link.l1.go = "adversary_5";
			}
			link.l10 = "Finora tutto fila liscio, Gino, sto bene.";
			link.l10.go = "exit";
			NextDiag.TempNode = "adversary";
		break;
		
		case "adversary_1":
			dialog.text = "Ksatl Cha ha parlato dell'Artiglio del Capo. Prova a usarlo contro gli scheletri, l’indiano diceva che questo pugnale comanda sugli abitanti di Ksocheatem.";
			link.l1 = "Ci proverò senz'altro!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L1");
		break;
		
		case "adversary_2":
			dialog.text = "E come sarebbe fatta questa grotta?";
			link.l1 = "Ebbene, c’è una piccola grotta nella roccia, è umida e sul fondo l’acqua si muove come la risacca…";
			link.l1.go = "adversary_2_1";
		break;
		
		case "adversary_2_1":
			dialog.text = "Se l’acqua si muove, allora la grotta ha qualche collegamento col mare e non può essere un vicolo cieco. Cerca un passaggio, dev’esserci per forza.";
			link.l1 = "In cammino...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L2");
		break;
		
		case "adversary_3":
			dialog.text = "Se esiste un passaggio dalla grotta principale a quella allagata, e se l’acqua ondeggia come il mare nella grotta grande, allora la caverna sommersa ha davvero una seconda uscita. Perlustrala meglio, ma fa’ attenzione o annegherai come uno sciocco.";
			link.l1 = "Vado a tuffarmi...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L3");
		break;
		
		case "adversary_4":
			dialog.text = "E come sarebbe fatta questa grotta?";
			link.l1 = "Beh, è piuttosto grande con qualche caverna, è umido e c’è una piccola buca con acqua stagnante...";
			link.l1.go = "adversary_4_1";
		break;
		
		case "adversary_4_1":
			dialog.text = "Se l’acqua resta ferma, allora la grotta non ha sbocco al mare e potremmo esser finiti in un vicolo cieco.";
			link.l1 = "Pensavo anch’io. Ho cercato là per un bel pezzo e c’è un solo ingresso, che è pure l’uscita...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L4");
		break;
		
		case "adversary_5":
			dialog.text = "Se l’acqua resta quieta nella caverna, allora forse hai ragione tu. Cerca ancora un po’, ma non crucciarti se non trovi nulla. Probabile che sia un vicolo cieco.";
			link.l1 = "Capisco...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L5");
		break;
		
		case "adversary_6":
			dialog.text = ""+pchar.name+", Le navi spagnole ci stanno addosso! Non è proprio il momento giusto per chiacchiere!";
			link.l1 = "Sì, certo...";
			link.l1.go = "exit";
			NextDiag.TempNode = "adversary_6";
		break;
		
		case "ksochitam_43":
			dialog.text = "Gli occhi tuoi ridenti mi dicono che hai trovato ciò che cercavi.";
			link.l1 = "Sì. I tesori di Miguel Dichoso e la Maschera di Kukulcan. Ora la sua incarnazione non potrà mai più cambiare il destino!";
			link.l1.go = "ksochitam_44";
		break;
		
		case "ksochitam_44":
			dialog.text = "Incredibile! Sei un eroe, "+pchar.name+"...";
			link.l1 = "Gino, sei davvero sicuro che basterà per fermare Kukulcan?";
			link.l1.go = "ksochitam_45";
		break;
		
		case "ksochitam_45":
			dialog.text = "Secondo Ksatl Cha, sì. E lui citava Urakan. Suo padre Kanek è stato quello che ha dato inizio a tutto questo casino. Hai ancora dubbi?";
			link.l1 = "Sono stato accolto nella baia da un ospite del passato – Alonso de Maldonado. Era a Tayasal quando Kanek compiva il rituale per evocare il Guardiano della Verità. Fu risucchiato in quell’abisso spazio-temporale, ma sopravvisse... Fino ad oggi.";
			link.l1.go = "ksochitam_46";
		break;
		
		case "ksochitam_46":
			dialog.text = "";
			link.l1 = "Ha detto che devo chiudere il portale stesso per proteggere il nostro mondo una volta per tutte. Per riuscirci, devo distruggere la Maschera su qualche altare a Tayasal.";
			link.l1.go = "ksochitam_47";
		break;
		
		case "ksochitam_47":
			dialog.text = "E tu vuoi andare a Tayasal? Sei fuori di testa! "+pchar.name+", hai ottenuto la maschera e l’incarnazione di Kukulcan non potrà farci un accidente! E Kanek stesso ne è certo! Per questo Urakan ha mandato Ksatl Cha a cercare Ksocheatem – per prendere la Maschera e distruggerla.";
			link.l1 = "E se questo Urakan avesse intenzione di distruggere la maschera a Tayasal?";
			link.l1.go = "ksochitam_48";
		break;
		
		case "ksochitam_48":
			dialog.text = ""+pchar.name+", finora solo un uomo è riuscito a fuggire vivo da Tayasal, ed è stato Miguel Dichoso. Anche Maldonado, ma quello fu un caso a parte. Anche se l’incarnazione di Kukulcan dovesse arrivare nel passato, gli antichi Maya lo farebbero fuori!";
			link.l1 = "E se invece di ammazzarlo lo riconoscessero?";
			link.l1.go = "ksochitam_49";
		break;
		
		case "ksochitam_49":
			dialog.text = "Allora, stai pianificando una spedizione a Tayasal?";
			link.l1 = "Non so, Gino. Davvero, non lo so...";
			link.l1.go = "ksochitam_50";
		break;
		
		case "ksochitam_50":
			dialog.text = "Allora riflettici su, perché dovresti farlo? Hai sentito la mia opinione. Ora sta a te decidere..."+pchar.name+", mi porterai a St. John's?";
			link.l1 = "Certo, Gino. Salpiamo al più presto. Ne ho fin sopra i capelli di quest’isola maledetta.";
			link.l1.go = "ksochitam_51";
		break;
		
		case "ksochitam_51":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_52";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Ksochitam", "16");
			pchar.quest.Ksochitam_gohome.win_condition.l1 = "location";
			pchar.quest.Ksochitam_gohome.win_condition.l1.location = "sentjons_town";
			pchar.quest.Ksochitam_gohome.function = "Ksochitam_ArriveHome";
			pchar.questTemp.Ksochitam = "gohome";
		break;
		
		case "ksochitam_52":
			dialog.text = "Ritorneremo presto a casa, "+pchar.name+"? Mi mancano davvero le mie fiaschette e le mie ampolle...";
			link.l1 = "Sì, sì, Gino, presto saremo ad Antigua.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_52";
		break;
		
		case "ksochitam_53":
			dialog.text = "Son proprio lieto che siam tornati infine! Non mi capacito di come voi, uomini di mare, riusciate a passar tanto tempo stipati sulle vostre navi...";
			link.l1 = "È solo questione d’abitudine, Gino.";
			link.l1.go = "ksochitam_54";
		break;
		
		case "ksochitam_54":
			dialog.text = "Mi sdraierò sul mio letto con i piedi ben piantati a terra, e sarà un vero piacere... Spero, "+pchar.name+", che tu abbia avuto il buon senso di non ficcare il naso a Tayasal?";
			link.l1 = "Non lo so ancora, Gino. A dir la verità, non ne sono ancora certo.";
			link.l1.go = "ksochitam_55";
		break;
		
		case "ksochitam_55":
			dialog.text = "Distruggi la maschera di Kukulcan e vivi senza pensieri, Capitano. Se vuoi, la scioglieremo nel più potente acido che ho a bordo. Non serberò rancore per una faccenda simile.";
			link.l1 = "Sai, aspetterò un po'. Avremo sempre tempo per mandarlo a fondo.";
			link.l1.go = "ksochitam_56";
		break;
		
		case "ksochitam_56":
			dialog.text = "Sta a te decidere. Se sceglierai di risparmiare questo mondo da quest’artefatto, vieni da me. Ti sarò grato per questo viaggio straordinario, Capitano!";
			link.l1 = "Quando vuoi, Gino. Ci si rivede in giro!";
			link.l1.go = "exit";
			NextDiag.TempNode = "first time";
			AddDialogExitQuestFunction("Ksochitam_TripComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Tu sei un "+GetSexPhrase("Ladro, signore! Guardie, pigliatelo!","Ladra, ragazza! Guardie, prendetela ")+"!!!","Ma guarda un po’! Appena mi sono perso nei miei pensieri, tu hai deciso di ficcare il naso nel mio baule! Al ladro!!!","Guardie! Al ladro! Prendete quel furfante!!!");
			link.l1 = "Maledizione!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}

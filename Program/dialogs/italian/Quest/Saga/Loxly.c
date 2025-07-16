// Альберт Локсли - адвокат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
    string sTemp, attrLoc;
	
    attrLoc = Dialog.CurrentNode;
	int iSumm = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	if (findsubstr(attrLoc, "RelationTo_" , 0) != -1)
	{
		i = findsubstr(attrLoc, "_" , 0);
		npchar.quest.relation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
		// проверка на уже договор
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
			Dialog.CurrentNode = "RelationYet";
		}
		else
		{
			Dialog.CurrentNode = "RelationAny_Done";
			npchar.quest.relation.summ = CalculateRelationLoyerSum(sti(npchar.quest.relation));
		}
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Mi chiamo Albert Loxley e sono avvocato. Difendo gli interessi dei miei clienti nei tribunali. I miei servigi non sono certo a buon mercato, ma credetemi, valgono ogni doblone.";
				if(SandBoxMode)
				{					
					if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
					{
						link.l1 = "Ho dei guai con le autorità inglesi.";
						link.l1.go = "RelationTo_0";
					}
					
					if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
					{
						link.l2 = "Ho dei guai con le autorità francesi.";
						link.l2.go = "RelationTo_1";
					}
					if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
					{
						link.l3 = "Ho dei guai con le autorità spagnole.";
						link.l3.go = "RelationTo_2";
					}

					if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
					{
						link.l4 = "Ho dei guai con le autorità olandesi.";
						link.l4.go = "RelationTo_3";
					}
					if (ChangeContrabandRelation(pchar, 0) <= 5)
					{
						Link.l5 = "Ho avuto un diverbio con i contrabbandieri.";
						Link.l5.go = "contraband";
					}
					Link.l7 = "Grazie, ma per fortuna non ho ancora bisogno dei servigi d’un leguleio.";
					Link.l7.go = "exit";
					NextDiag.TempNode = "Loxly";
					npchar.quest.meeting = "1";
				}
				link.l1 = "Grazie, ma per fortuna non ho ancora bisogno dei servigi d’un avvocato.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "loxly")
				{
					link.l1 = "Ho bisogno dei vostri servigi. Sono il delegato autorizzato di una giovane dama, Helen McArthur, nipote del celebre Nicolas Sharp. Dopo la morte di sua madre e di suo zio, ella è l’unica erede legittima. Secondo il testamento dello zio, possiede ogni diritto su Isla Tesoro. Quanto chiedereste per aiutare Helen a divenire la legittima padrona dell’isola?";
					link.l1.go = "saga";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga"))
				{
					if (pchar.questTemp.Saga == "loxly") // первое обращение по саге
					{
						dialog.text = "Avete bisogno dei miei servigi, signore? Non resterete deluso, ve lo garantisco.";
						link.l1 = "Sì, mi servono. Sono il delegato ufficiale di una giovane dama, Helen McArthur, nipote del celebre Nicolas Sharp. Dopo la morte di sua madre e di suo zio, è rimasta l’unica erede legittima. Secondo il testamento dello zio, ha pieno diritto su Isla Tesoro. Quanto vuoi per aiutare Helen a reclamare il dominio sull’isola come le spetta di diritto?";
						link.l1.go = "saga";
						break;
					}
					if (pchar.questTemp.Saga == "bakaut")
					{
						dialog.text = "Signore, non sono ancora pratico delle faccende vostre. Tornate più tardi, come già v'ho detto.";
						link.l1 = "Va bene.";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "molligan" || pchar.questTemp.Saga == "sellbakaut")
					{ // если не выполнил до конца квест по бакауту
						dialog.text = "Signore, purtroppo mi serve ancora un po’ di tempo per recuperare tutti i documenti dagli archivi. Non sono ancora pronto. Vi prego, tornate più tardi.";
						link.l1 = "Bene.";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "removebakaut") // с бакаутом разобрались
					{
						// четвертая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							RemoveItems(pchar, "map_sharp_full", 1);
							dialog.text = "Signore, perché avete lavorato con tanta lentezza?! Ormai è finita per вашего protettоре. Il termine di validità del testamento è scaduto e Isla Tesoro appartiene ora all’Inghilterra. Presto diventerà una base militare."link.l1 ="Accidenti! Pare che tutti i miei sforzi siano andati in malora...";
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "Ah, eccovi, signore. Mi sono già fatto un’idea dei materiali, quindi ora tocca all’anticipo. Avete portato i dobloni con voi?";
							if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) {n = 1000;}
							else {n = 450;}
							if (PCharDublonsTotal() >= n)
							{
								link.l1 = "Sì, li ho. Ecco i tuoi dobloni.";
								link.l1.go = "saga_5";
							}
							else
							{
								link.l1 = "Perdona la mia pessima memoria, li ho lasciati in uno scrigno sulla mia nave. Li porto subito.";
								link.l1.go = "exit";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "shadow")
					{
						// пятая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							dialog.text = "Monsieur, perché vi state muovendo come una lumaca?! È finita per il vostro principale. Il termine di validità del testamento è scaduto e Isla Tesoro ora appartiene all’Inghilterra. Presto diventerà una base militare."link.l1 ="Accidenti! Pare che tutti i miei sforzi siano andati in fumo...";
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "Signore, siete riuscito a trovare qualcosa che possa provare la discendenza del vostro principale?";
							if (!CheckCharacterItem(pchar, "Letter_beatriss"))
							{
								link.l1 = "Non ancora. Ma ci sto lavorando.";
								link.l1.go = "exit";
							}
							else
							{
								link.l1 = "Sì. Ho davvero prove schiaccianti.";
								link.l1.go = "saga_14";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "court" && GetNpcQuestPastDayParam(npchar, "court_date") >= 1 && IsOfficer(characterFromId("Helena")))
					{
						 // запрет сохранения чтобы ленку не заграбастали себе умники всякие с ГК-  лесник
						InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться																																			   
						dialog.text = "A-ah, eccovi qua, signore. Lieto di vedervi. Devo confessare che vi attendevo da un bel po’. È questo il vostro principale?";
						link.l1 = "Sì. Permettimi di presentarti Helen McArthur.";
						link.l1.go = "saga_26";
						break;
					}
					dialog.text = "Avete bisogno dei miei servigi, Signore? Ve lo garantisco, ne resterete soddisfatto.";
					link.l1 = "Grazie, ma per ora non ne ho bisogno.";
					link.l1.go = "exit";
				}
				if (CheckAttribute(npchar, "quest.waitgold"))
				{
					dialog.text = "Buongiorno, signore. Immagino che abbiate portato la mia ricompensa?";
					if (PCharDublonsTotal() >= 450)
					{
						link.l1 = "Sì, ce li ho. Ecco i tuoi dobloni.";
						link.l1.go = "saga_36";
					}
					link.l2 = "Sai, signor Loxley, pensavo... Insomma, novecento dobloni sono più che sufficienti per il tuo lavoro.";
					link.l2.go = "saga_38";
					link.l3 = "Ricordo, signor Loxley. Lo porterò un po' più tardi...";
					link.l3.go = "exit";
					break;
				}
				dialog.text = "Avete bisogno dei miei servigi, signore? Sarete soddisfatto, ve lo garantisco.";
				link.l1 = "Grazie, ma per adesso non mi servono.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "saga":
			// третья проверка времени. Отбираем Элен, чистим квестовый лут, даем флаг на Свенсона, вызываем перемены
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				RemoveItems(pchar, "map_sharp_full", 1);
				dialog.text = "Signore, dovete aver passato troppo tempo in mare. Isla Tesoro ormai è una base militare della Marina Inglese! Sì, il testamento di Sharp esiste, ma ormai è scaduto e Isla Tesoro è diventata proprietà della Corona inglese. Ahimè!"link.l1 ="Accidenti! Pare che tutte le mie fatiche siano state vane...";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "La signorina pretende di possedere tutta l’isola? Hmm... Pare che la faccenda non sarà di quelle facili. Isla Tesoro è già quasi una colonia inglese...";
				link.l1 = "Non ancora. Secondo il testamento, chiunque presenti entrambe le parti della mappa diventerà il proprietario di Isla Tesoro. Abbiamo entrambe le parti della mappa di Sharp, che è la prova principale dell’eredità.";
				link.l1.go = "saga_1";
			}
		break;
		
		case "saga_1":
			dialog.text = "Nicolas Sharp... Bene, bene. Devo fare una capatina agli archivi e mettere le mani su tutto ciò che riguarda Isla Tesoro. Hai la mappa con te?";
			link.l1 = "Ce l'ho, ma te lo darò solo dopo che avremo firmato un contratto. Allora, parliamo del prezzo per i tuoi servigi?";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			sTemp = "";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = " Your esteemed involvement won't go unnoticed either. Cartagena... There will be questions.";
			dialog.text = "Come ti ho detto, non sarà una passeggiata. Devi dimostrare il diritto di possesso su un’isola intera, mica su una vecchia bagnarola o una catapecchia. E poi, Nicolas Sharp era un bucaniere: dar man forte a pirati o ai loro parenti costa caro."+sTemp;
			link.l1 = "Mi dirai mai una cifra precisa?";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			sTemp = "four hundred and fifty";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "one thousand";
			dialog.text = "Signore, la somma finale sarà decisa durante il processo. Non so ancora quanto sarà grave la situazione. Ma sono pronto a stimare un anticipo - "+sTemp+" dobloni. Questa somma d’oro dovrà essere pagata di nuovo una o due volte, a seconda di come andranno i nostri affari.\nPortami il denaro tra una settimana, mi serve tempo per consultare gli archivi e prepararmi. Poi ci metteremo d’accordo. Affare fatto?";
			link.l1 = "Mi hanno detto che sei il miglior avvocato di tutto l'arcipelago, quindi l’affare è fatto. Ci vediamo tra una settimana!";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			DialogExit();
			pchar.questTemp.Saga = "bakaut"; // обновляем флаг
			AddQuestRecord("Testament", "2");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) AddQuestUserData("Testament", "sMoney", "1000");
			else AddQuestUserData("Testament", "sMoney", "450");
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				bDisableFastReload = true;
				SetFunctionLocationCondition("HelenDrinking_PortRoyalDialog", "PortRoyal_town", false);
			}
		break;
		
		case "saga_5":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
			{
				RemoveDublonsFromPCharTotal(1000);
				//Log_Info("You have given 1450 doubloons");
			}
			else
			{
				RemoveDublonsFromPCharTotal(450);
				//Log_Info("You have given 450 doubloons");
			}
			PlaySound("interface\important_item.wav");
			dialog.text = "Molto bene. Sono pronto a occuparmi del tuo caso e a rappresentare i tuoi interessi in tribunale. Ma veniamo al sodo. Ho rovistato negli archivi e parlato con gente importante. L'eredità di Sharp non sarà semplice da ottenere. Meno male che hai recuperato entrambe le parti della mappa. Ma potrebbe non bastare.\nIl colonnello Doyle ha grandi mire su Isla Tesoro, dopo aver fallito nel prendere Tortuga. L'isola è ben protetta dalla natura e potrebbe diventare una roccaforte militare in queste acque.";
			link.l1 = "Ma secondo la legge inglese, Helen è la legittima erede dell’isola!";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Forse non sai che il defunto Sharp fece un'aggiunta al suo testamento. L'erede, o gli eredi, devono portare il suo cognome. E se non erro, la tua ragazza ha un altro cognome. Hai detto che era McArthur, vero?";
			link.l1 = "Questo è il cognome del suo patrigno, ma Helen ha tutto il diritto di portare il cognome Sharp, poiché è figlia della defunta Beatrice Sharp, la figlia di Nicolas.";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Splendido! Ma chi può giurarlo davanti a Dio? I genitori adottivi di Helen conoscevano forse Beatrice Sharp?";
			link.l1 = "Per quel che ne so, non lo erano. Il signor McArthur pensava che fosse figlia di Gladys, e Gladys conosceva solo il padre della ragazza.";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "Che peccato. Vedi, non ho trovato alcuna traccia negli archivi che Beatrice Sharp abbia mai avuto figli. È possibile che non esista nessun documento ufficiale sulla nascita di questo bambino. Chiunque può spacciarsi per nipote della Sharp e pretendere il diritto di portarne il nome.";
			link.l1 = "Ma solo Hélène possiede la mappa completa!";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Questa è la sua carta vincente, e forse basterebbe, se solo le autorità locali non covassero i propri intrighi per Isla Tesoro. Un documento vergato dalla mano di Beatrice, con la sua firma, giace negli archivi. Dobbiamo scovare un qualche scritto redatto da lei che attesti la nascita della figlia, quella stessa figlia affidata a quella Gladys... ehm, come diavolo si chiamava di cognome?";
			link.l1 = "Chandler. Gladys Chandler da Belize.";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "Esatto. Hai modo di scovare qualcosa del genere?";
			link.l1 = "Ne dubito. Sono passati troppi anni. Secondo la leggenda, pare che il padre di Helen fosse nientemeno che il capitano Butcher in persona. Forse l’ex boia di St. John’s può svelarci qualcosa. Fu l’ultimo a vedere suo padre ancora in vita.";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "Mm. Era davvero un tipo divertente. Se ben ricordo, si chiamava Raymond Baker. Ebbi la fortuna di scambiare quattro chiacchiere con lui una volta. È un uomo sveglio e istruito. Bene, prova a scovare qualcosa su Antigua, io intanto continuerò a frugare negli archivi, magari scovo qualcosa d’utilità.";
			link.l1 = "Va bene. Mi sta a genio.";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "Dammi la mappa di Sharp e sbrigati, parla con Baker, magari con il suo aiuto riuscirai a trovare dei documenti. Potresti perfino scovare prove della sua nascita.";
			link.l1 = "Eh, magari potessi. Va bene, ci si vede, messer Loxley.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			DialogExit();
			RemoveItems(pchar, "map_sharp_full", 1);
			pchar.questTemp.Saga = "shadow";
			pchar.questTemp.Saga.Shadows = "sentjons";
			AddQuestRecord("Shadows", "1");
		break;
		
		case "saga_14":
			dialog.text = "Ah davvero? Vediamo un po’ queste prove.";
			link.l1 = "Questa è una lettera privata scritta da Beatrice Sharp a suo fratello. Qui c’è scritto che ha dato alla luce una figlia, e che il padre era in realtà Lawrence Beltrope. La bambina fu affidata a una giovane vedova di nome Gladys Chandler. Lawrence Beltrope è anche conosciuto come il capitano Butcher. Tieni, prendi la lettera...";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			RemoveItems(pchar, "Letter_beatriss", 1);
			dialog.text = "";
			link.l1 = "Gladys è pronta a giurarlo su tutto. È anche pronta a confermare che il padre si presentò come capitano Butcher.";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) // Белтроп убит
			{
				dialog.text = "Aspetta un attimo! Il Capitano Butcher, quella canaglia di pirata e assassino di sudditi inglesi, fu impiccato nella fortezza di St. John's vent'anni or sono. E Lawrence Beltrope, caro compare di Richard Doyle, è morto tragicamente non molto tempo fa. E soprattutto, Doyle voleva farlo nuovo governatore di Sharptown!";
				link.l1 = "Ah! Certo, nessuno lo sa... Ho una deposizione scritta di Raymond Baker, l’ex boia di St. John, che fu costretto – sotto minaccia di morte sicura – a inscenare l’impiccagione del Macellaio! Guarda qui, dai un’occhiata...";
				link.l1.go = "saga_17";
			}
			else
			{
				dialog.text = "Aspetta un attimo! Il Capitano Butcher, quel famigerato bucaniere e boia degli inglesi, fu impiccato alla fortezza di San Giovanni vent’anni fa. E Lawrence Beltrope è vivo e se la spassa in una delle ville più sontuose di Port Royal. E, per di più, Doyle vuole farlo diventare il nuovo governatore di Sharptown!";
				link.l1 = "Ah! Sicuro, nessuno lo sa... Ho una testimonianza scritta di Raymond Baker, il boia in pensione di St. John's, che fu costretto, sotto minaccia di morte certa, a inscenare l’esecuzione del Macellaio! Ecco, guarda con i tuoi occhi...";
				link.l1.go = "saga_17";
			}
		break;
		
		case "saga_17":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = "Uhm. Bene, bene...";
			link.l1 = "Non è forse astuto? Il capitano Butcher è riuscito a salvarsi la pelle ed è tornato in Inghilterra. Ha ripreso il nome di Lawrence Beltrope ed è rientrato qui senza che nessuno se ne accorgesse.";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "saga_18";
			else link.l1.go = "saga_22";
		break;
		
		case "saga_18":
			dialog.text = "Ma questo... Questo cambia tutto! Pubblicare la lettera di Beatrice dimostrerà che per tutto questo tempo il governatore militare ha nascosto il pirata fuggiasco Butcher, che doveva esser preso al volo e portato davanti alla corte per i suoi vecchi misfatti!\nE la testimonianza di Baker spazzerà via qualsiasi obiezione! Meraviglioso! Con un simile asso nella manica, batteremo Doyle lealmente, a carte scoperte!";
			link.l1 = "Sono lieto. Conto su di te in questa prova. Dimmi anche, come è morto Lawrence Beltrope?";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "Questa è una storia da far gelare il sangue, signore. Lo trovarono nella sua camera, col volto tutto stravolto. Difficile persino immaginare cosa possa aver terrorizzato così un uomo senza paura. Dicono che fosse coperto di brina. Il suo corpo, pieno di ferite orrende e squarciate, ma nemmeno una goccia di sangue sul pavimento! Pensateci! Neanche una goccia!";
			link.l1 = "Sì, pare davvero un incubo. Pare che sia stato assassinato... Ma chi diamine potrebbe aver fatto una cosa simile?";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "Non si sa. È tutto troppo ingarbugliato... Il medico della guarnigione ha detto che le ferite non erano mortali. Beltrope è crepato di paura, dolore, o chissà cos’altro. Comunque sia, questa è una morte stregata.";
			link.l1 = "Capisco... E quando avrà inizio il processo?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "Tutto dipende da voi, signore. Presenterò tutti i documenti al tribunale non appena mi avrete pagato la seconda parte della mia parcella – 450 dobloni. Helen otterrà i suoi diritti una settimana dopo.";
			if (PCharDublonsTotal() >= 450)
			{
				link.l1 = "Benissimo. Ecco i tuoi dobloni.";
				link.l1.go = "saga_24";
			}
			else
			{
				link.l1 = "Sì, certo. Ti porterò la somma che ti serve.";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_23";
			}
		break;
		
		case "saga_23":
			// шестая проверка времени
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				dialog.text = "Signore, mi avete lasciato di stucco! Avete fatto così tanto, l’isola stava quasi per cadere nelle nostre mani, ma ormai è finita per colpa del vostro ritardo col mio compenso! Il testamento è scaduto e Isla Tesoro appartiene ora alla corona inglese. Diventerà una base militare."link.l1 ="Perdinci! Pare proprio che tutti i miei sforzi siano andati in fumo...";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "Hai portato la seconda parte del mio compenso, signore?";
				if (PCharDublonsTotal() >= 450)
				{
					link.l1 = "Sì, certo. Ecco i tuoi dobloni.";
					link.l1.go = "saga_24";
				}
				else
				{
					link.l1 = "Perdonatemi la memoria da vecchia ciurma, li ho lasciati in uno scrigno sulla mia nave. Ve li porto subito.";
					link.l1.go = "exit";
					NextDiag.TempNode = "saga_23";
				}
			}
		break;
		
		case "saga_22":
			dialog.text = "Ma questo... questo cambia tutto! Pubblicare la lettera di Beatrice significherà che Lawrence Beltrope dovrà essere arrestato all’istante e dovrà rispondere in tribunale dei suoi crimini passati!\nE la deposizione di Baker spazzerà via ogni scusa contraria! È magnifico! Con un simile asso nella manica, faremo fuori Doyle senza trucchi!";
			link.l1 = "Sono molto lieto. Quando avrà inizio il processo?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_24":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("You have given 450 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Eccellente, signore. È stato un piacere fare affari con voi. Ora, sentite qua l'accordo. Tornate domani. Sì-sì, avete capito bene – domani! In fin dei conti sono il miglior avvocato dell’arcipelago e ho i miei agganci.\nPortate la vostra mandante, senza di lei il processo non si farà. Non fate tardi e non lasciate la città. E se potete, portate anche l’ultima parte del pagamento, sono assolutamente certo della nostra vittoria.";
			link.l1 = "Bene. Domani saremo nel vostro ufficio, messer Loxley.";
			link.l1.go = "saga_25";
		break;
		
		case "saga_25":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "court_date");
			pchar.questTemp.Saga = "court"; // обновляем флаг
			AddQuestRecord("Testament", "10");
			NextDiag.CurrentNode = "First time";
			// закрываем выходы из города
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", true);
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", true);// лесник там нет этого пирса
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", true);
			//pchar.GenQuest.CannotWait = true;//запрет ожидания
			// снимаем общий таймер Саги!
			pchar.quest.Saga_TimeOver.over = "yes";
		break;
		
		case "saga_26":
			dialog.text = "MacArthur? No, è Sharp! Su, seguimi ora!";
			link.l1 = "...";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			DialogExit();
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto10");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			sld = characterFromId("Helena");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(npchar, "reload", "reload1", "Saga_CourtGo", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			LAi_ActorFollow(sld, npchar, "", -1);
			NextDiag.CurrentNode = "saga_28";
			// открываем выходы из города
			//LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник рано 
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", false);
			//LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "saga_28":
			dialog.text = "Permettetemi di farvi i miei complimenti, signore, e alla vostra principale. Ormai è la legittima sovrana di Isla Tesoro. Questa sì che merita una bottiglia di champagne!";
			link.l1 = "Assolutamente, signor Loxley. Il vostro discorso è stato davvero magistrale. Pensavo che il colonnello Doyle stesse per crepare dallo spavento quando avete dichiarato in tribunale che Lawrence Beltrop è in realtà il capitano Macellaio.";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "Sì, il signor Doyle dovrà dire addio al suo sogno di una base militare su Isla Tesoro. E che può farci? La legge è legge, e vale per tutti, persino per il rispettato colonnello.";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die"))
			{
				link.l1 = "Sono in regola tutti i documenti, confermano davvero il diritto di Hélène all’isola?";
				link.l1.go = "saga_30";
			}
			else
			{
				link.l1 = "Ho sentito dire che il giudice ha ordinato l’arresto di Lawrence Beltrop. Immagino che finirà impiccato?";
				link.l1.go = "saga_34";
			}
		break;
		
		case "saga_30":
			dialog.text = "Certo, signore. Ho controllato ogni virgola su quei documenti. Può star sicuro che sono a posto.";
			link.l1 = "Va bene...";
			link.l1.go = "saga_31";
		break;
		
		case "saga_31":
			dialog.text = "Ebbene, il mio compito è svolto. La faccenda era spinosa, ma insieme l’abbiamo spuntata. Ora, messere, resta solo che mi versiate l’ultima parte della mia ricompensa. Senza fretta, capisco che possiate essere impicciato. Ma confido che troverete il tempo di portarmi gli ultimi 450 dobloni entro la settimana.  Inoltre, per un cliente come voi ci son sempre sconti generosi. Posso esservi assai utile, ho agganci in ogni capitale dell’arcipelago, perfino tra i nemici: qualsiasi grana legale vi si pari davanti, io la sistemo.";
			link.l1 = "Eccellente. Ora so a chi chiedere.";
			link.l1.go = "saga_32";
		break;
		
		case "saga_32":
			dialog.text = "Ti garantisco che ne usciremo a testa alta anche nelle peggiori burrasche.";
			link.l1 = "Bene. Ora devo andare, io ed Hélène abbiamo un bel da fare.";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "Addio, signore.";
			link.l1 = "Addio, messer Loxley.";
			link.l1.go = "saga_35";
		break;
		
		case "saga_34":
			dialog.text = "Suppongo di sì, è il capitano Butcher, pirata e mascalzone. Ma ora non si trova a Port Royal. Ha avuto la fortuna di svignarsela, addentrandosi nell’isola. Ma la caccia è aperta, e presto finirà nella rete, statene certi.";
			link.l1 = "Capisco... I documenti sono in regola?";
			link.l1.go = "saga_30";
		break;
		
		case "saga_35":
			DialogExit();
			SetFunctionTimerCondition("Saga_RemainGoldLoxly", 0, 0, 10, false); // таймер на оплату услуг
			DoQuestReloadToLocation("PortRoyal_town", "quest", "quest3", "Saga_HelenaIslaTesoro");
			npchar.quest.waitgold = "true";
			pchar.questTemp.Saga = "lastpages";
			NextDiag.CurrentNode = "First time";
		break;
		
		case "saga_36":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("You have given 450 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Splendido! È stato un piacere fare affari con voi, Signore! Ora potete contare sul mio aiuto in qualsiasi faccenda, e vi farò pure uno sconto. Guai con la legge, taglia sulla testa... Siete il benvenuto. Sarò sempre lieto di rivedervi.";
			link.l1 = "Sarebbe meglio se me ne stessi lontano dai guai, ma... le cose capitano. Grazie e addio, messer Loxley.";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			DialogExit();
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			NextDiag.CurrentNode = "Loxly"; // услуги адвоката
		break;
		
		case "saga_38":
			dialog.text = "Cosa intendete dire, signore? Avete forse intenzione di infrangere i termini del nostro accordo?";
			link.l1 = "Esatto. Il grosso del lavoro l’ho fatto io. Non hai idea di cosa mi sia toccato fare per mettere insieme le prove. E tu ti sei limitato a prendere quei fogli e trascinarti in tribunale. Novecento dobloni bastano e avanzano, ne sono certo.";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = "Parli come un bucaniere, signore! Ebbene, non mi ridurrò in miseria perdendo quattrocentocinquanta dobloni, ma nemmeno tu diventerai ricco. Anzi, hai appena perso ben di più! E forse perderai ancora qualcosa in futuro... Fuori subito da casa mia e non ti azzardare mai più a mostrarti qui!";
			link.l1 = "E lo farò, statene certo. Addio, messer Loxley.";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			LocatorReloadEnterDisable("PortRoyal_town", "houseSp4", true); // закроем вход к Локсли
			ChangeCharacterNationReputation(pchar, ENGLAND, -10);
		break;
		
		case "saga_40":
			dialog.text = "Non voglio parlare con te. Sparisci o chiamo le guardie!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
		break;
		
		// провалы Саги
		case "saga_l3":
			dialog.text = "Signore, avremmo potuto vincere la vostra causa se foste venuto prima da me. Il testamento è ormai scaduto. Mi rincresce.";
			link.l1 = "Eh, mi dispiace ancor di più! Ebbene, addio, messer Loxley.";
			link.l1.go = "saga_l3_1";
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l3";
		break;
		
		case "saga_l3_1":
			DialogExit();
			pchar.quest.Saga_Late_3.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_3.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_3.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
			pchar.questTemp.Saga = "late_l3"; // для Свенсона
		break;
		
	//-------------------------------------- адвокатские услуги ------------------------------------------------
		case "Loxly":
			dialog.text = TimeGreeting()+", Signore. Lieto di vederla. Ha bisogno dei miei servigi?";
			link.l1 = "Sì. È proprio per questo che sono qui.";
			link.l1.go = "loxly_1";
			link.l2 = "No, per fortuna non ne ho bisogno adesso. Volevo solo salutarti.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "loxly_1":
			dialog.text = "Sono pronto ad ascoltarti. Di che aiuto hai bisogno?";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l1 = "Ho dei guai con le autorità inglesi.";
				link.l1.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l2 = "Mi trovo nei guai con le autorità francesi.";
				link.l2.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l3 = "Ho dei guai con le autorità spagnole.";
				link.l3.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "Ho dei guai con le autorità olandesi.";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "Ho avuto una lite coi contrabbandieri.";
				Link.l5.go = "contraband";
            }
			Link.l7 = "Mi dispiace, ho cambiato idea...";
			Link.l7.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "RelationYet": // уже оплачено
			dialog.text = "Sto già lavorando sulla tua faccenda. Andrà tutto bene, te lo assicuro.";
			Link.l1 = "Grazie. Ti aspetterò.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		// --> снятие НЗГ
		case "RelationAny_Done":
			iSumm = sti(npchar.quest.relation.summ);
			int iRate = abs(ChangeCharacterNationReputation(pchar, sti(npchar.quest.relation), 0));
			if (iRate <= 10) sTemp = "Well, I wouldn't call that trouble. Just a little problem. I will settle the affair at once";
			if (iRate > 10 && iRate <= 30) sTemp = "Yes, your reputation is slightly spoiled but I don't see anything critical. I will settle the affair at once";
			if (iRate > 30 && iRate <= 60) sTemp = "Yes, you went down the wrong path with the authorities. It won't be easy but I am sure that I will be able to settle your disagreements without a hitch";
			if (iRate > 60 && iRate <= 90) sTemp = "And how did you do that, Sir? Your troubles are not just serious, they are really serious. The authorities are very eager to get you. I will have to put a lot of effort into settling your disagreements";
			if (iRate > 90) sTemp = "Well... The situation is catastrophic - you are claimed to be the most bitter enemy. It will be tough but I am the best lawyer in the Caribbean after all, so I will settle your disagreements";
			dialog.text = ""+sTemp+" con "+XI_ConvertString(Nations[sti(npchar.quest.relation)].Name+"Abl")+" . Ti costerà "+FindRussianMoneyString(iSumm)+".";
			if(sti(pchar.money) >= iSumm)
			{
				link.l1 = "Benissimo, signor Loxley, accetto. Ecco i vostri soldi, vedete di sistemare la faccenda quanto prima.";
				link.l1.go = "relation";
			}
			link.l2 = "Non ho la cifra che chiedi in questo momento. Tornerò più tardi!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;

		case "relation":
			dialog.text = "È stato un piacere fare affari con voi, signore. Potete tirare un sospiro di sollievo, il vostro grattacapo sparirà entro le prossime due settimane. Evitate qualsiasi scaramuccia con "+XI_ConvertString(Nations[sti(npchar.quest.relation)].Name+"Abl")+", mentre sono nel bel mezzo delle trattative.";
			link.l1 = "D'accordo, terrò a mente il tuo avvertimento. Grazie e addio!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.relation.summ));
			ChangeNationRelationFromRelationAgent(npchar);
			attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
            Pchar.GenQuest.(attrLoc) = true;
			Pchar.GenQuest.(attrLoc).loyer = "true";
			NextDiag.TempNode = "Loxly";
		break;
		// <-- снятие НЗГ
		
		case "contraband":
			npchar.quest.contrasum = makeint(0.3*stf(Pchar.rank)/stf(Pchar.reputation.nobility)*60000);
			dialog.Text = "E perché mai hai fatto ciò? I contrabbandieri sono brava gente, a modo loro onesti. Tutti dobbiamo campare e mangiare... Va bene, non è nulla di grave e ti costerà soltanto "+FindRussianMoneyString(sti(npchar.quest.contrasum))+".";
			if(sti(Pchar.money) >= sti(npchar.quest.contrasum))
			{
				Link.l1 = "Va bene, messer Loxley, accetto. Ecco i tuoi dobloni, sbrigati a sistemare la faccenda quanto prima.";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "Non ho la somma che chiedi in questo momento. Tornerò più tardi!";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Eccellente, risolverò il tuo problema. Presto vorranno di nuovo fare affari con te.";
			Link.l1 = "Grazie, amico!";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			AddMoneyToCharacter(pchar, -sti(npchar.quest.contrasum));
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

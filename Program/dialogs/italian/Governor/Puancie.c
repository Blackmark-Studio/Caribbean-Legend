// Филипп де Пуанси - генерал-губернатор французских колоний
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Terrapin_KathyFox"))
			{
				dialog.text = "Saluti, "+pchar.name+". Come in; I've already been informed.";
				link.l1 = "Informato? Potrebbe esserci qualche errore, Vostra Eccellenza. Sono venuto a riportare il completamento con successo della vostra missione, ma vedo che non siete nel migliore degli umori.";
				link.l1.go = "PZ_PoincyAngry1";
				DeleteAttribute(pchar, "questTemp.Terrapin");
				DeleteAttribute(pchar, "questTemp.Terrapin_KathyFox");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "done")
			{
				dialog.text = "Contento di vederti, "+pchar.name+". Sono informato sui tuoi successi e, soprattutto, hai avuto successo nella tua missione! Ti sei mostrato dal lato migliore e sono contento di non essermi sbagliato su di te.";
				link.l1 = "Posso ricevere da lei un ordine scritto per liberare mio fratello ora?";
				link.l1.go = "serve";
				AddCharacterExpToSkill(pchar, "Sneak", 500);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga") && CheckAttribute(pchar, "questTemp.Sharlie.LevasserDied"))
			{
				dialog.text = "Contento di vederti, "+pchar.name+". Ho sentito parlare delle tue imprese e, soprattutto, la tua missione è completata! Devo dire, però, che mi aspettavo un'idea più astuta di un attacco frontale. Peccato per i soldati francesi morti.\nMa la guerra è guerra, ci sono sempre vittime. Hai adempiuto al tuo dovere, e sono lieto di aver avuto ragione su di te.";
				link.l1 = "Posso ricevere da te un ordine scritto per liberare mio fratello ora?";
				link.l1.go = "serve";
				DeleteAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga");
				DeleteAttribute(pchar, "questTemp.Sharlie.LevasserDied");
				break;
			}
			// Jason НСО 
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && GetCharacterIndex("Noel") == -1 && pchar.questTemp.Patria != "epizode_12_barondie" && pchar.questTemp.Patria != "epizode_12_baronfail" && pchar.questTemp.Patria != "epizode_12_baronkilled" && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "Contento di vederti, Charles. Prima di tutto, permettimi di congratularmi con te per aver completato con successo il complesso compito di proteggere la colonia di Saint-Pierre dagli invasori spagnoli. Lavoro brillante, amico mio!";
					link.l1 = "Grazie, Cavaliere.";
					link.l1.go = "patria";
					Patria_SetInspector();
				}
				else
				{
					dialog.text = "Buono vederti, Charles. Prima di tutto, permettimi di congratularmi con te per aver completato con successo l'arduo compito di proteggere la colonia di Saint-Pierre dagli invasori spagnoli. Lavoro brillante, amico mio! Ti presento un'altra opportunità di collaborare con la Marina. La Francia ha un disperato bisogno di ufficiali come te. Spero che questa volta sarai più sensibile... Prendi il brevetto, Capitano Charles de Maure!";
					link.l1 = "Grazie, Cavaliere. Sono lieto di aiutare il paese e desideroso di continuare a servirlo!";
					link.l1.go = "patria";
					if (!CheckCharacterItem(pchar, "suit1")) GiveItem2Character(pchar, "suit1");
					GiveItem2Character(pchar, "patent_fra");
					EquipCharacterbyItem(pchar, "patent_fra");
					Items[sti(pchar.EquipedPatentId)].TitulCur = 2; 
					Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
					ChangeCharacterNationReputation(pchar, FRANCE, 100);
					Patria_SetInspector();
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (!CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "Charles, mi deludi. A causa delle tue azioni imprudenti, hai perso il tuo brevetto e il grado nella Marina Reale. Non c'è spazio per ulteriori collaborazioni. Sei licenziato.";
					link.l1 = "Uhm...";
					link.l1.go = "patria_patentfail";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_1_return")
				{
					dialog.text = "Contento di vederti, Charles. Rapporto!";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "È fatto, il riscatto dalla colonia di San Jose è stato ricevuto. Ma ci sono brutte notizie: in battaglia con il forte 'Eclatant' è affondato. Avevo avvertito il capitano di fare attenzione, ma non mi ha ascoltato, e...";
						link.l1.go = "patria_8_1";
					}
					else
					{
						link.l1 = "Il lavoro è fatto, il riscatto dalla colonia di San Jose è stato ricevuto.";
						link.l1.go = "patria_8";
					}
					break;
				}
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(!IsUniformEquip())
				{
					dialog.text = "Signore, d'ora in poi entra nei miei saloni solo in uniforme appropriata!";
					link.l1 = "...";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_2_return" && IsUniformEquip())
				{
					dialog.text = "Barone, capitano! Felice di vederti!";
					link.l1 = "L'incarico è completato, Cavaliere.";
					link.l1.go = "patria_14";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_3_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", capitano. Quali notizie porti?";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "Gli spagnoli hanno pianificato un attacco su Port-au-Prince. All'estremità occidentale di Hispaniola abbiamo trovato una potente squadra nemica. È stata completamente distrutta. Tuttavia, 'Eclatant' è affondato.";
						link.l1.go = "patria_26_1";
					}
					else
					{
						link.l1 = "Gli spagnoli avevano pianificato un attacco a Port-au-Prince. All'estremità occidentale di Hispaniola abbiamo trovato una potente squadra nemica. È stata completamente distrutta.";
						link.l1.go = "patria_26";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_4_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", Charles. Come sta Mynheer Stuyvesant?";
					link.l1 = "Tutto bene, Cavaliere. La consegna è stata un successo, ecco la risposta alla tua lettera.";
					link.l1.go = "patria_31";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_5_return" && IsUniformEquip())
				{
					dialog.text = "Charles, Barone... Sei già tornato?";
					link.l1 = "...";
					link.l1.go = "patria_36";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_6_return" && IsUniformEquip())
				{
					dialog.text = "Non mi piace il tuo cipiglio, Charles. Cosa ha detto Stuyvesant, rapporto!";
					if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win") link.l1 = "Letteralmente, ha detto: 'dì al Chevalier che non è più a capo di Sint-Maarten. Basta con lui. E riguardo all'ispezione dallo stato madre - lascia che inventi qualcosa, non è mai stato difficile per de Poincy capovolgere tutto'. Dopo aver annunciato questo messaggio, il mio signore mi ha cacciato dalla residenza. Questa è stata la fine delle nostre negoziazioni.";
					else link.l1 = "Ebbene, ecco cosa ha detto: 'il tuo sovrano è stato troppo avido su Sint-Maarten ultimamente, quindi è ora di temperare la sua insaziabile fame.' Dopo questo, ha cercato di arrestarmi. Ho dovuto aprirmi la strada verso la nave con una lama. Tanto per la diplomazia olandese.";
					link.l1.go = "patria_43";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_go" && IsUniformEquip())
				{
					dialog.text = "Capitano, ti stavamo aspettando. Ho spiegato lo stato attuale delle cose al barone, e lui ha pienamente sostenuto la mia decisione. Gli olandesi risponderanno per la loro arroganza.";
					link.l1 = "È guerra, allora?";
					link.l1.go = "patria_51";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_continue" && IsUniformEquip() && pchar.location.from_sea == "Charles_town") // add-7
				{
					Patria_HunterShipChecker();
					if (CheckAttribute(pchar, "questTemp.Patria.Hunter.GiveShip"))
					{
						dialog.text = "Allora, mio amico, vedo che hai catturato la nave delle Indie Orientali con i beni. Eccellente!";
						link.l1 = "Ti sto consegnando una nave, dai ordini ai funzionari del porto, Chevalier.";
						link.l1.go = "patria_55";
					}
					else
					{
						dialog.text = "Hai delle domande, Charles?";
						link.l1 = "Non al momento, Monsieur. Allora me ne andrò...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8" && IsUniformEquip())
				{
					dialog.text = "Finalmente, sei arrivato, Capitano! C'è un'emergenza su Saint Christopher!";
					link.l1 = "Uno squadrone ostile?";
					link.l1.go = "patria_59";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_wait" && IsUniformEquip() && GetCompanionQuantity(pchar) < 5)
				{
					dialog.text = "Sei pronto a prendere in consegna la nostra imbarcazione da corriere?";
					link.l1 = "Sono io.";
					link.l1.go = "patria_64";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_return")
				{
					dialog.text = "Capitano de Maure, Sir Doily! Felice di vedervi! L'intera città ha osservato mentre insegnavate una lezione ai furfanti spagnoli-olandesi che desideravano la nostra colonia!";
					link.l1 = "Era il mio dovere, Cavaliere.";
					link.l1.go = "patria_66";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_start" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", Charles. Cominciamo, non è vero?";
					link.l1 = "Certo, Cavaliere. Ecco perché sono qui.";
					link.l1.go = "patria_69";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_return" && IsUniformEquip())
				{
					dialog.text = "Sono lieto di accogliere nel mio ufficio il Vice Ammiraglio della Marina Reale di Francia! Sì, amico mio, non ti sei sbagliato: ho firmato personalmente l'ordine riguardante la tua nomina. Formalmente, deve ancora essere approvato in Francia, ma non devi nemmeno dubitare che succederà. Congratulazioni!";
					link.l1 = "Servo la mia nazione!";
					link.l1.go = "patria_76";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_10_return" && IsUniformEquip())
				{
					if (GetQuestPastDayParam("questTemp.Patria.Curacao.Date") < 30) sTemp = "will be ready soon and"; // в зависимости от времени сколько добирался
					else sTemp = "is ready and";
					dialog.text = "Hai avuto successo nei tuoi sforzi? Il colonnello Doily era soddisfatto?";
					link.l1 = "Tutto è andato perfettamente, Chevalier. La carovana di Stuyvesant è stata catturata, tutti gli schiavi portati in Jamaica, lo squadrone del colonnello "+sTemp+" sulla via per Curaçao.";
					link.l1.go = "patria_81";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_11_return" && IsUniformEquip())
				{
					dialog.text = "Gloria ai vincitori! Congratulazioni, congratulazioni, amico mio! Non smetti mai di stupire.";
					link.l1 = "Grazie, Cavaliere. Stuyvestant è stato punito ed è pronto a pagare le indennità, la pace è stata ristabilita, Saint Martin appartiene ora esclusivamente alla Francia.";
					link.l1.go = "patria_85";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_continue")
				{
					dialog.text = "Allora, amico mio, sono felice di rivederti. Hai riposato bene?";
					link.l1 = "Sì, Cavaliere. Era una pausa molto necessaria... Hai menzionato una questione delicata?";
					link.l1.go = "patria_88";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronalive")
				{
					dialog.text = "Amico mio, devi essere un mago! Sei riuscito a compiere un'impresa! Il nostro barone non vuole più creare una Compagnia di Commercio qui.";
					link.l1 = "Credo che il suo unico desiderio ora sia tornare a Parigi.";
					link.l1.go = "patria_103";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_barondie")
				{
					dialog.text = "Charles, hai sentito parlare del barone? È stato preso dai pirati...";
					link.l1 = "Sì, Cavaliere. Purtroppo, il barone è morto. Lo so per certo.";
					link.l1.go = "patria_112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronfail")
				{
					dialog.text = "Charles, come procedono le tue imprese? Mi è stato detto che il barone è salito sulla tua nave...";
					link.l1 = "Sì, Cavaliere. Era a bordo, stavo lavorando su di lui, ma... è morto di febbre.";
					link.l1.go = "patria_x112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronkilled")
				{
					dialog.text = "Charles, come procedono le cose? Mi è stato detto che il barone ha salito a bordo della tua nave...";
					link.l1 = "Sì, Cavaliere. Era a bordo, stavo lavorando su di lui, ma... è morto in battaglia.";
					link.l1.go = "patria_y112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronwin")
				{
					dialog.text = "Amico mio, devi essere un mago! Sei riuscito a compiere un'impresa! Il nostro barone non vuole più creare una Compagnia di Commercio qui.";
					link.l1 = "Probabilmente sta andando a Parigi ora.";
					link.l1.go = "patria_117";
					break;
				}
				dialog.text = "Hai delle domande, Charles?";
				link.l1 = "Non in questo momento, signore. Allora me ne vado...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Cosa vuoi? Monsieur?";
			link.l1 = "Niente di serio, solo una visita di cortesia. Sto andando via ora...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// в тюрьме при старте игры
		case "Puancie_Jail":
			dialog.text = "Buongiorno a te, Charles. Permettimi di presentarmi: sono Philippe de Poincy e io...";
			link.l1 = "Perché diavolo mi hai messo in prigione? È inappropriato! Sono un nobile francese e...";
			link.l1.go = "Puancie_Jail_1";			
			// belamour legendary edition -->
			link.l2 = "Buon... pomeriggio? Buon scherzo, Signore. Come fai a sapere chi sono?";
			link.l2.go = "Puancie_Jail_1a";	
		break;
		
		case "Puancie_Jail_1a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			dialog.text = "Giovane uomo, ti chiedo di non interrompermi! Stai parlando con il Governatore Generale delle colonie francesi dell'arcipelago dei Caraibi! Perdonerò il tuo tono sfacciato solo perché non potevi sapere chi stava di fronte a te. Ma ti consiglierei di essere più riservato.";
			link.l1 = "Mmm... Mi dispiace, Vostra Grazia.";
			link.l1.go = "Puancie_Jail_2";
		break;
		
		case "Puancie_Jail_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "FencingL", 10);
			AddCharacterExpToSkill(pchar, "FencingS", 10);
			AddCharacterExpToSkill(pchar, "FencingH", 10);
			AddCharacterExpToSkill(pchar, "Pistol", 10);
			// <-- legendary edition
			dialog.text = "Ascolta bene, giovane, e non interrompermi! Stai parlando con il Governatore Generale delle colonie francesi nell'arcipelago dei Caraibi! Perdonerò il tuo tono solo a causa della tua ignoranza su con chi stavi parlando. Ma ti consiglierei di essere più riservato in futuro.";
			link.l1 = "Mm... perdonami, vostra Eccellenza.";
			link.l1.go = "Puancie_Jail_2";			
		break;
		
		case "Puancie_Jail_2":
			dialog.text = "Meglio. Ora, riguardo alla tua precedente domanda - sei stato considerato - per errore - una spia spagnola e messo sotto arresto fino a quando la tua posizione non è chiara. Maledetti Castigliani sono diventati più attivi di recente, quindi ho ordinato di detenere tutte le persone sospette.\nMa ora sappiamo chi sei - sei davvero Charles de Maure, fratello di Michelle de Monper, e sono personalmente sceso qui per liberarti. E tu mi stai urlando come un ragazzino!";
			link.l1 = "Chiedo ancora perdono, vostra Eccellenza. Sono libero ora?";
			link.l1.go = "Puancie_Jail_3";			
		break;
		
		case "Puancie_Jail_3":
			dialog.text = "Sì, lo sei. Ma prima che un sergente apra la tua cella, voglio parlare in privato con te. Sai che tuo fratello, uno dei guerrieri più degni dell'Ordine di Malta, è stato arrestato e messo sotto custodia?";
			link.l1 = "Sapevo solo che mio fratello è in difficoltà e ha bisogno di aiuto. Ecco perché sono venuto qui da Parigi.";
			link.l1.go = "Puancie_Jail_4";			
		break;
		
		case "Puancie_Jail_4":
			dialog.text = "Lieta di sentirlo. Voglio che tu sappia che il signor de Monper è nei guai seri. Ho tutte le ragioni per sospettarlo di abuso di autorità, appropriazione indebita e spergiuro. Ma tu puoi aiutarlo.";
			link.l1 = "Signore, potrebbe dirmi di più? Non capisco, Michel era l'orgoglio dell'Ordine e...";
			link.l1.go = "Puancie_Jail_5";			
		break;
		
		case "Puancie_Jail_5":
			dialog.text = "Anche io la pensavo così. Lo pensavamo tutti! Ma le sue recenti azioni ci hanno reso... incerti della sua lealtà all'Ordine, quindi è stato arrestato. Michel ti dirà i dettagli da solo. Ti spiegherà come potresti aiutarlo a prenderti cura delle accuse e ad evitare una vergogna.";
			link.l1 = "Dove si trova mio fratello ora? Mi hai detto che è in prigione, ma non l'ho visto in giro...";
			link.l1.go = "Puancie_Jail_6";			
		break;
		
		case "Puancie_Jail_6":
			dialog.text = "Ho detto imprigionato, giovane? Stai persino ascoltando?! Ho detto, è sotto arresto! Non è la stessa cosa. Michel de Monper è tenuto sotto arresto nella base sotterranea di Saint Pierre che è di proprietà dell'Ordine di Malta.\nTi permetto di visitare la base senza alcuna limitazione e di parlare con tuo fratello ogni volta che pensi sia necessario. Gli ufficiali e i soldati dell'Ordine sono a conoscenza delle mie istruzioni e non ti fermeranno.";
			link.l1 = "Dove si trova quella base sotterranea?";
			link.l1.go = "Puancie_Jail_7";			
		break;
		
		case "Puancie_Jail_7":
			dialog.text = "È qui, a Saint Pierre ovviamente. Cerca la prigione locale e entra nella porta con i simboli dell'Ordine. Scendi al casamatto al secondo livello di un seminterrato. Monsieur Monper sarà lì. Ma non preoccuparti: all'uscita dalla prigione, verrai incontrato e scortato da tuo fratello - ho organizzato tutto... È tutto. Spero che ci rivedremo, Charles. Sergente!";
			link.l1 = "Per favore aspetta, vostra Eccellenza! E i miei... beni? La mia spada e il resto?";
			link.l1.go = "Puancie_Jail_8";			
		break;
		
		case "Puancie_Jail_8":
			dialog.text = "I tuoi beni sono stati confiscati per ripagare il debito di tuo fratello. Addio, Monsieur de Maure.";
			link.l1 = "Cosa diavolo...";
			link.l1.go = "Puancie_Jail_9";			
		break;
		
		case "Puancie_Jail_9":
			DialogExit();
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Sharlie_GoFromPrison", 3.5);
			NextDiag.CurrentNode = "First time";
			locCameraFromToPos(-11.09, 0.65, 3.05, true, -12.59, 0.09, -4.66);
		break;
		
		// возвращаем деньги
		case "saga":
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Charles_townhall", "reload1_back", false);
			dialog.text = "Aha, Charles de Maure in persona! Felice di vederti. Immagino che tu sia venuto qui per discutere del destino di tuo fratello con me?";
			link.l1 = "Sono pronto a ripagare ciò che Michel de Monper deve all'Ordine e personalmente a te.";
			if (sti(pchar.money) >= 1000000) link.l1.go = "saga_1";
			else link.l1.go = "saga_exit";			
		break;
		
		case "saga_exit":
			dialog.text = "Mh.. Ma dove sono i soldi? Hai un senso dell'umorismo strano, ragazzo e non lo capisco.";
			link.l1 = "Mi scusi, Cavaliere. Ho dimenticato i soldi nella mia cassaforte sulla nave. Tornerò presto.";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_repeat";	
		break;
		
		case "saga_repeat":
			dialog.text = "Hai portato i soldi, Charles?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Certo! Spero che questa somma ripaghi completamente tutte le tue spese.";
				link.l1.go = "saga_1";
			}
			else
			{
				link.l1 = "Non ancora...";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_repeat";
			}		
		break;
		
		case "saga_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Charles");
			AddMoneyToCharacter(pchar, -1000000);
			dialog.text = "Splendido! Li prenderò da te. Ti sei mostrato dal tuo lato migliore, Charles!";
			link.l1 = "Quando riceverò un ordine per la liberazione di Michel de Monper?";
			link.l1.go = "saga_2";			
		break;
		
		case "saga_2":
			dialog.text = "Non affrettarti, giovane. Posso solo rispettare il fatto che tu paghi i debiti e protegga la tua famiglia mettendo in pericolo la tua stessa vita. È una nobiltà rara al giorno d'oggi... Ma il denaro non è la parte principale in questa triste storia. Tuo fratello ha ottenuto una somma così grande a condizione di svolgere una missione molto delicata.\nMichel de Monper, come fedele cattolico, aveva giurato sul Libro che avrebbe trovato un modo per punire un eretico insolente e per ripristinare la giustizia che lui ha violato per la gloria dell'Ordine e della Santa Chiesa...";
			link.l1 = "Ma non sarà in grado di mantenere la sua parola sotto arresto! Se lo rilasci, noi due saremo in grado di completare la missione molto più velocemente di quanto potrei farlo da solo.";
			link.l1.go = "saga_3";			
		break;
		
		case "saga_3":
			dialog.text = "Vedi, mio amico, tuo fratello mi ha dato un forte motivo per non fidarmi della sua decenza. Non ci sono garanzie che non scapperà e romperà il suo giuramento. Quindi, se vuoi liberarlo da tutte le accuse - compi il giuramento da solo. Monsieur de Monper ti dirà i dettagli.";
			link.l1 = "Hm... Non me lo aspettavo. Ma non mi lasci altra scelta. Prenderò la mia decisione finale dopo aver parlato con mio fratello.";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			dialog.text = "Sto iniziando a apprezzarti davvero, Charles. Un giorno, forse, diventeremo amici. Comunque, questo è il mio ultimo termine per liberare tuo fratello. Ti do la mia parola che la reputazione della tua famiglia non sarà danneggiata se farai ciò che tuo fratello non ha fatto. E in futuro potrai contare sulla mia amicizia.";
			link.l1 = "Ti ho capito completamente. Addio!";
			link.l1.go = "saga_5";			
		break;
		
		case "saga_5":
			DialogExit();
			pchar.questTemp.Saga = "mishelle";//Сага - старт
			AddQuestRecord("Sharlie", "21");
			NextDiag.CurrentNode = "First time";
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
		break;
		
		case "serve":
			dialog.text = "Non preoccuparti, "+pchar.name+", Manterrò la mia parola. Tuo fratello sarà liberato e tutte le accuse contro di lui saranno ritirate. La reputazione della tua famiglia è ora fuori pericolo. Direi che tutto ciò è merito tuo e solo tuo. Tuo padre può essere orgoglioso di aver cresciuto un figlio così.";
			link.l1 = "Grazie per le gentili parole, Cavaliere. Posso presumere che posso partire immediatamente per la Martinica?";
			link.l1.go = "serve_1";	
			Island_SetReloadEnableGlobal("Tortuga", true);
			CloseQuestHeader("Terrapin");
			SetFunctionTimerCondition("Terrapin_SetFontene", 0, 0, 5, false); // таймер
		break;
		
		case "serve_1":
			dialog.text = "Aspetta un attimo, amico mio. Spero di poterti chiamare mio amico, posso farlo, vero? Voglio esprimere la mia gratitudine personalmente. Ti ho osservato dal tuo arrivo qui e so della maggior parte delle tue azioni. Ti sei fatto un grande nome nei Caraibi e, senza dubbio, sei anche ben conosciuto e rispettato in alcuni particolari settori della società. La Francia ha bisogno di persone come te\nCapitano "+GetFullName(pchar)+"! Per potere, conferitomi da Sua Maestà, il Re di Francia, ho l'onore di offrirti un brevetto di capitano della Marina Reale e di prendere sotto il tuo comando il vascello della marina francese, una fregata leggera 'Gryffondor'!\nIl suo ex capitano de Fontenot sarà governatore di Tortuga grazie a te e la migliore fregata leggera nei Caraibi ha bisogno di un capitano. Accetti l'offerta?";
			link.l1 = "Interessante. In cambio di cosa?";
			link.l1.go = "serve_2";		
		break;
		
		case "serve_2":
			dialog.text = "Solo un po'. Un decimo della tua cattura e a volte l'esecuzione di missioni delicate. Sto aspettando la tua decisione.";
			link.l1 = "Nessuno rifiuterebbe un'offerta del genere, vostra Eccellenza! È un onore servire la mia nazione!";
			link.l1.go = "serve_3";
			link.l2 = "Perdonami per la mia immodestia, ma devo rifiutare la tua offerta per ora. Le questioni di famiglia potrebbero richiedere un ritorno immediato in patria.";
			link.l2.go = "serve_no";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "serve_no":
			ChangeCharacterComplexReputation(pchar, "fame", 7);
			dialog.text = "Peccato. Speravo che saresti d'accordo... Ma, ciononostante, sono costretto a chiederti un altro favore, in realtà è nel tuo interesse anche. La Martinica è sotto attacco. Ci sono violenti combattimenti nel porto e nella città stessa.\nAhimè, non ho nessuno da mandare lì per aiutare la guarnigione se non te. Ti chiedo come patriota della tua Patria di respingere l'assalto con qualsiasi mezzo necessario. Spero che tu abbia abbastanza risorse per farlo.\nInoltre, tuo fratello è ancora lì, potresti salvargli la vita.";
			link.l1 = "Mio fratello è in pericolo? Sono in viaggio!";
			link.l1.go = "serve_exit";			
		break;
		
		case "serve_3":
			dialog.text = "Parole così onorevoli! Parole di un vero soldato e figlio leale della Patria! Congratulazioni, signore "+GetFullName(pchar)+". Ti viene conferito il rango di comandante delle forze navali della Francia. Accetta questa uniforme da me. Indossala con orgoglio e sii degno di essa!";
			link.l1 = "Servo la mia nazione!";
			link.l1.go = "serve_4";	
			locCameraFromToPos(-2.63, 2.20, -4.96, true, 2.64, 0.22, -4.96);
			npchar.greeting = "puancie_1";			
		break;
		
		case "serve_4":
			dialog.text = "La leggera fregata 'Gryffondor' è ora sotto il tuo comando. Da questo momento questa eccellente nave è tua. Usa le sue alte qualità per la gloria di Sua Maestà e per rafforzare l'influenza francese sull'arcipelago dei Caraibi!";
			link.l1 = "Subito!";
			link.l1.go = "serve_5";
			LAi_Fade("SharlePutsSuit", "");
		break;
		
		case "serve_5":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Ma il tuo squadrone è già troppo grande, quindi torna a prendere il 'Gryffondor' quando ti sarai liberato di una nave.";
				link.l1 = "Bene. Lo farò.";
				link.l1.go = "serve_wait";		
			}
			else
			{
				dialog.text = "Insieme alla nave otterrai anche il suo capitano ad interim e l'equipaggio. Se vuoi, puoi lasciarlo sotto il tuo comando o spostarlo da una nave e noi gli troveremo un'altra posizione.";
				link.l1 = "Capito!";
				link.l1.go = "serve_6";
			}
		break;
		
		case "serve_6":
			dialog.text = "Ma ho brutte notizie per te, capitano. Sono appena stato informato che la Martinica è sotto attacco. Ci sono pesanti combattimenti nel porto e nella stessa città.\nAhimè, non ho nessuno da mandare lì per aiutare la guarnigione se non te. Ecco la tua prima missione:\n Proteggi Saint Pierre! Inoltre, tuo fratello è ancora lì, puoi salvargli la vita.";
			link.l1 = "Mio fratello è in pericolo? Sono in viaggio!";
			link.l1.go = "serve_7";
		break;
		
		case "serve_7":
			DialogExit();
			locCameraTarget(PChar);
			locCameraFollow();
			CreateGriffondor();
			sld = characterFromId("GriffOfficer");
			SetCharacterRemovable(sld, true);
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "24");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 500);
			pchar.questTemp.GoldenGirl_block = true;	// Запрещаем квест Дороже Золота
		break;
		
		case "serve_wait":
			DialogExit();
			NextDiag.CurrentNode = "serve_shipcheck";
		break;
		
		case "serve_shipcheck":
			dialog.text = "Sei pronto a prendere il comando del 'Gryffondor'?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "Non ancora, sto riposizionando le mie navi nello squadrone...";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Sono io.";
				link.l1.go = "serve_5a";
			}
			NextDiag.TempNode = "serve_wait";
		break;
		
		case "serve_5a":
			dialog.text = "Splendido! Insieme alla nave avrai anche il suo capitano in carica e l'equipaggio. Se vuoi, puoi lasciarlo al tuo comando o trasferirlo da una nave e noi gli troveremo un'altra posizione.";
			link.l1 = "Capito!";
			link.l1.go = "serve_6";
		break;
		
		case "serve_exit":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "23");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
		break;
		
		// Jason НСО
		case "patria":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince"); // Rebbebion, удалить команду пиратов на всякий
			DelCharleePrince("");
			dialog.text = "E questo è solo l'inizio, signore! Sono certo che andrai lontano, con tali talenti militari! E ho già un'altra commissione per un eccellente ufficiale navale, con il quale, sono sicuro, te la caverai altrettanto bene. Inoltre, è direttamente correlato alla tua missione precedente.";
			link.l1 = "Sono tutto orecchie, monsieur";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Ma prima permettetemi di presentarvi la persona che è entrata nel mio ufficio. Incontrate il Barone Noel Forget, membro onorario della Compagnia di Commercio delle Indie Occidentali Francesi. È arrivato nell'arcipelago per ispezionare le nostre colonie per l'espansione dell'organizzazione delle piantagioni di canna da zucchero e altre colture, oltre a esplorare la possibilità di sviluppare legami commerciali nella nostra regione. Da Parigi è prescritto di dargli ogni tipo di supporto e assistenza in queste materie, cosa che indubbiamente faremo. Barone, vi presento Monsieur Charles de Maure, uno dei capitani più talentuosi al servizio della Francia...";
			link.l1 = "";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			DialogExit();
			sld = characterFromId("Noel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_3":
			dialog.text = "Allora, Charles, mentre io e il barone ispezioniamo Saint Christopher, ti assegno il seguente compito. Nessuno può attaccare gli insediamenti francesi e sperare di farla franca, e gli spagnoli, sebbene abbiano già ricevuto una lezione per l'aggressione su Martinica, devono rispondere dei loro crimini con le loro borse e compensare il danno fatto alla colonia.\nInsieme al barone francese, è arrivata una potente squadriglia composta da una potente nave da 66 cannoni 'Eclatant'. Il capitano della nave è un marinaio esperto, ma nei Caraibi per la prima volta, quindi passa sotto il tuo comando. Insieme all' 'Eclatant' andrai alle coste dell'isola spagnola di Trinidad, e chiederai agli spagnoli un risarcimento monetario dell'ordine di trecentomila pesos per l'attacco a Saint Pierre.";
			link.l1 = "Cavaliere, crede davvero che gli spagnoli accetteranno?";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Sono sicuro che sarà così - dopo che l' 'Eclatant' e la tua squadra avranno distrutto il Forte San Jose. Sbarcare truppe e prendere la città, perdere soldati, penso, non sarà necessario. Attacca senza preavviso, distruggi il forte, e poi segnala al comandante che vuoi stabilire le condizioni. In questa situazione, gli spagnoli non avranno dove andare, e preferiranno pagare. Cosa faresti se agissi al posto del governatore della città rimasta senza protezione?";
			link.l1 = "Mmm, sembra ragionevole, Cavaliere.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "È chiaro quello che devi fare?";
			link.l1 = "Sì, vostra Grazia.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip())
			{
				dialog.text = " Allora mettiti al lavoro. Ecco una lettera per il Capitano dell' 'Eclatant' con la conferma della tua autorità. Questa eccellente nave con un equipaggio ben addestrato è ora a tua disposizione. Charles, e non dimenticare che ora servi la Francia, e per comunicare adeguatamente con funzionari come me si consiglia di indossare una divisa. Ti si addice perfettamente. Buona fortuna, Capitano de Maure!";
			}
			else
			{
				dialog.text = "Allora mettiti al lavoro. Ecco una lettera per il Capitano dell''Eclatant' con la conferma della tua autorità. Questa eccellente nave con un equipaggio ben addestrato è ora a tua disposizione. Oh e Charles: indossa l'uniforme da capitano, te lo ordino! Prima di tutto, non è degno di un ufficiale della Marina Reale Francese sembrare un commerciante o qualche corsaro, e in secondo luogo, la tua uniforme ti si addice perfettamente. Esegui subito, Capitano de Maure!";
			}
			link.l1 = "";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "1");
			pchar.questTemp.Patria = "epizode_1";
			Patria_SetEcliaton();
			pchar.questTemp.GoldenGirl_block = true;	// Запрещаем квест Дороже Золота
		break;
		
		case "patria_8_1":
			if (sti(pchar.money) >= 300000) AddMoneyToCharacter(pchar, -300000);
			else pchar.questTemp.Patria.NoMoney = "true";
			dialog.text = "'Eclatant' è affondato? Charles, questo è un disastro! Cosa dirà ora il ministro? Mi hai deluso, Charles! Ero certo di poter contare sulla tua esperienza, e tu... Ahimè, ma sarai tu a rispondere di questo. Scriverò un rapporto, e sarebbe meglio per te sparire per un po'. Il tuo servizio nella Marina Reale è finito.";
			link.l1 = "Hmm... Mi dispiace, Monsieur. Sembra che sia davvero meglio per me sparire per un mese o due, finché il ministro non si calma. Addio, e ancora mi dispiace molto per averti deluso.";
			link.l1.go = "patria_8_2";
		break;
		
		case "patria_8_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "8");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_block");	// Разрешаем квест Дороже Золота
			RemoveItems(pchar, "patent_fra", 1);
			if (CheckAttribute(pchar, "questTemp.Patria.NoMoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -20);
				ChangeCharacterNationReputation(pchar, FRANCE, -30);
				DeleteAttribute(pchar, "questTemp.Patria.NoMoney");
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -5);
				ChangeCharacterNationReputation(pchar, FRANCE, -5);
			}
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
		break;
		
		case "patria_8":
			if (sti(pchar.money) >= 300000)
			{
				dialog.text = "Perfetto!";
				link.l1 = "Ecco, per favore prendi questi trecentomila.";
				link.l1.go = "patria_9";
			}
			else
			{
				dialog.text = "Perfetto, ma dove sono i soldi, Charles?";
				link.l1 = "Eh, Nel baule sulla nave, lo consegnerò in un momento!";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_8_3":
			DialogExit();
			npchar.dialog.currentnode = "patria_8_4";
		break;
		
		case "patria_8_4":
			dialog.text = "Allora, Charles, hai portato il riscatto da Trinidad?";
			if (sti(pchar.money) >= 300000)
			{
				link.l1 = "Sì Monsieur. Eccolo qui.";
				link.l1.go = "patria_9";
			}
			else
			{
				link.l1 = "Lo porterò in un momento!";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_9":
			AddMoneyToCharacter(pchar, -300000);
			dialog.text = "Sono contento di te, Charles, non deludi mai. Il compito non era facile, e ti viene concesso un importo di 50.000 pesos dal totale del riscatto come ricompensa. Prendilo, è tutto tuo.";
			link.l1 = "Grazie, Cavaliere.";
			link.l1.go = "patria_10";
		break;
		
		case "patria_10":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "C'è già un nuovo compito per te. Monsieur Forget ha completato l'ispezione a Saint Christopher e ora desidera visitare le nostre colonie settentrionali. Ti chiedo di portare il barone a Tortuga e Hispaniola, di aiutare in tutti i modi nelle sue faccende e di soddisfare le sue richieste. È chiaro, Charles?";
			link.l1 = "Certo, Cavaliere.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Il Barone ha poco tempo, quindi ti chiedo di non distrarti con altre questioni e di non ritardare il viaggio per più di due mesi.";
			link.l1 = "Certo, Monsieur. Il viaggio tra le isole non richiede molto tempo, a meno che gli affari di Monsieur Forget nelle colonie non siano impegnativi.";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Perfetto. Allora il Barone viaggerà sulla tua nave. Dagli la migliore cabina che c'è.";
			link.l1 = "Certo, Cavaliere!";
			if(IsUniformEquip()) link.l1.go = "patria_13";
			else link.l1.go = "patria_13_1";
		break;
		
		case "patria_13_1":
			dialog.text = "E un'altra cosa, Charles: Sei di nuovo senza la tua divisa da ufficiale! Questo è il tuo ultimo avvertimento. Da questo momento in poi ti chiedo di venire da me solo in divisa, altrimenti non ti ascolterò. Sei in servizio, e la disciplina dovrebbe essere tutto, specialmente nell'aspetto di un ufficiale navale!";
			link.l1 = "Perdonami, Cavaliere. Non succederà di nuovo.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "9");
			pchar.questTemp.Patria = "epizode_2";
			Patria_VisiterBegin();
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_14":
			sld = characterFromId("Noel");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
			dialog.text = "Non avevo dubbi che il tuo viaggio sarebbe stato un successo. Ci sono novità da Tortuga o da Port-au-Prince?";
			link.l1 = "...";
			link.l1.go = "patria_15";
		break;
		
		case "patria_15":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_16";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_16":
			dialog.text = "";
			link.l1 = "Sì, Cavaliere, porto notizie ma non sono molto piacevoli. Prima di tutto, il Governatore di Port-au-Prince è sicuro che gli spagnoli stanno preparando un attacco alla colonia e per questo stanno radunando una squadra militare su... em-m, come si chiama... su Santiago, sì. E questo non sembra essere un pettegolezzo. Credo che non possiamo ignorare questa questione, soprattutto perché le piantagioni di Port-au-Prince sono tra le migliori che abbia mai visto.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Gli spagnoli si stanno preparando ad attaccare Port-au-Prince? Hmm... Va bene. Ti daremo istruzioni su come affrontare questo capitano Charles de Maure. 'Eclatant' è appena stato riparato, equipaggiato e pronto a salpare...";
			link.l1 = "E un'altra cosa, Monsieur: a Parigi, l'isola di Saint Martin, che si trova a nord da qui, è considerata una colonia francese ma il Capitano Charles de Maure mi ha detto che sono i olandesi a controllarla. È così, Chevalier?";
			link.l1.go = "patria_18";
		break;
		
		case "patria_18":
			dialog.text = "Mmm... Hai ragione fino a un certo punto. Saint Martin è una colonia francese. Tuttavia, Barone, da un punto di vista economico, quest'isola è assolutamente inutile - l'area è piccola, il terreno lì è scarso, magro, l'acqua dolce è scarsa, e quella che si trova nei pozzi è fangosa e amara. Mi è stato persino detto che lì si raccoglie l'acqua piovana per bere.\nQuindi, Saint Martin è stata ceduta in affitto a lungo termine alla Dutch West Indies Trading Company, che la utilizza come punto di transito settentrionale per le navi della Compagnia dalla regione alla metropoli. I olandesi hanno ampliato l'insediamento di Phillipsburg lì, hanno costruito un forte e un porto, e per coloro che sono arrivati nell'arcipelago relativamente di recente, come il Capitano Charles de Maure, Saint Martin sembra una colonia olandese.";
			link.l1 = "Ma de jure l'isola ci appartiene?";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			dialog.text = "Certo. Ma come ho detto, è più redditizio ottenere soldi per l'affitto che utilizzare le sue scarse risorse.";
			link.l1 = "Mi sembra che quest'isola sarebbe molto utile per la Compagnia delle Indie Occidentali Francesi quando appare nei Caraibi. Il significato di ciò che hai appena annunciato - l'avamposto settentrionale sulla via per l'Europa. Devo visitare questa colonia, ed è molto probabile che l'affitto dell'isola agli olandesi sarà interrotto.";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Prima, devi inviare un'inchiesta a Willemstad, il direttore della Compagnia olandese delle Indie occidentali, la Zecca di Peter Stuyvesant. Deve dare il suo permesso per l'ispezione dell'isola - dopotutto, gli olandesi ci sono da molto tempo.";
			link.l1 = "Allora dobbiamo inviare un corriere a Willemstad.";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			dialog.text = "Il problema è, il mio signore Stuyvesant è raramente presente a Willemstad, è costantemente in viaggio e si occupa degli affari della Compagnia sul suo galeone...";
			link.l1 = "Ma almeno a volte è presente lì, suppongo? Comunque, gli olandesi sono obbligati a garantire l'ispezione dell'isola ai suoi legittimi proprietari. Perché non inviamo una lettera al Governatore di Philipsburg?";
			link.l1.go = "patria_22";
		break;
		
		case "patria_22":
			dialog.text = "Mynheer Martin Thomas, con tutto il rispetto dovuto a lui, è solo un semplice impiegato, la vera gestione è eseguita dalla Compagnia. Barone, risolverò questo problema, non preoccuparti, ci vorrà un po' di tempo.";
			link.l1 = "Ebbene, ho molto tempo. Dopotutto, dobbiamo ancora visitare le colonie meridionali, Guadalupa e Martinica. È un peccato che il Capitano Charles de Maure non mi accompagnerà questa volta - deve ancora una volta dirigersi verso Hispaniola...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetActorType(pchar); // 17-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_24";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
		break;
		
		case "patria_24":
			dialog.text = "Sì, sì, stiamo ritardando il nostro caro capitano con le nostre conversazioni noiose! Charles, porta l''Eclatant' alla squadra, avanzate verso Hispaniola e informatevi su eventuali reali minacce a Port-au-Prince da parte degli spagnoli. Se ce ne sono, allora occupati di loro. Comunque, non spetta a me insegnarti, tu sai tutto meglio di me. Se non trovi nulla, allora non dovresti perdere tempo, ho bisogno di te qui. Ti aspetto con il rapporto non più tardi di un mese. Buona fortuna, amico mio!";
			link.l1 = "Grazie, Cavaliere. Salperò immediatamente.";
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10) link.l1.go = "patria_25_1";
			else link.l1.go = "patria_25_2";
		break;
		
		case "patria_25_1":
			dialog.text = "E un'altra cosa, Charles: Ho sentito dire che hai problemi con le autorità olandesi? Per favore, risolvi questo problema il prima possibile, nel prossimo futuro dovrai visitare le loro colonie. Come capisci, sarebbe impossibile sotto il fuoco dei forti.";
			link.l1 = "Bene, Monsieur, sarà fatto.";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25_2":
			dialog.text = "E un'altra cosa, Charles: ti avverto: evita qualsiasi conflitto con gli olandesi. Nel prossimo futuro dovrai visitare le loro colonie. Come capisci, sarebbe impossibile sotto il fuoco dei forti...";
			link.l1 = "Bene, Monsieur. Nessun litigio con gli olandesi.";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "15");
			pchar.questTemp.Patria = "epizode_3";
			Patria_PortPaxBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_26_1":
			dialog.text = "'Eclatant' è affondato? Charles, questo è un disastro! Cosa dirà ora il ministro? Mi hai deluso, Charles! Ero certo di poter contare sulla tua esperienza, e tu ... Ahimè, ma sarai ritenuto responsabile per questo. Scriverò un rapporto, e sarebbe meglio che tu sparissi per un po'. Il tuo servizio nella Marina Reale è finito.";
			link.l1 = "Hmm ... Mi dispiace, Monsieur. Sembra che sia davvero meglio per me sparire per un mese o due, fino a quando il ministro non calma la sua rabbia. Addio, e ancora una volta mi dispiace molto per averti deluso.";
			link.l1.go = "patria_26_2";
		break;
		
		case "patria_26_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "19");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_block");	// Разрешаем квест Дороже Золота
			RemoveItems(pchar, "patent_fra", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterNationReputation(pchar, FRANCE, -5);
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
		break;
		
		case "patria_26":
			dialog.text = "Eccellente! Finché avremo capitani come te nella nostra marina, non dovremmo temere l'astuzia dei Castigliani. Domani manderò un corriere a Port-au-Prince con un dispaccio e una posta dalla Francia, e allo stesso tempo lascerò un suggerimento in una lettera personale a Monsieur Jeremy Deschamps du Mussaca che sarebbe bello ringraziarti per il servizio, quindi posso assicurarti che tu, Charles, riceverai un premio ben meritato.\nE ora passiamo al tuo prossimo incarico. Sì, amico mio, ho un nuovo incarico per te, tuttavia questa volta non militare ma molto delicato, e vorrei che tu lo facessi.";
			link.l1 = "Sono tutto orecchie, Cavaliere.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Suppongo che tu ricordi la mia discussione con Monsieur Forget riguardo a Saint Martin? Dobbiamo rassicurare il barone che la colonia è stata ispezionata, e tu andrai a Curacao, a Willemstad, dal direttore della Compagnia Peter Stuyvesant. È lì proprio adesso, e lo sarà per altre tre settimane. Inoltre, dovrai scortare il fluyt con le merci della Compagnia a Curacao e dare a Mynheer Stuyvesant una lettera da parte mia.";
			link.l1 = "Sono questi tutti i compiti?";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			dialog.text = "Sì, capitano. Informami sulla risposta del signor Stuyvesant. Dovremmo essere giusto in tempo prima che il signor Forget ritorni dal suo viaggio a Martinica e Guadalupa, e finalmente potrà visitare Saint Martin, che desidera veramente visitare.";
			link.l1 = "Molto bene. Posso andare?";
			link.l1.go = "patria_29";
		break;
		
		case "patria_29":
			dialog.text = "Potresti, Charles. Non impiegare troppo tempo, al barone non piace aspettare. E mentre visiti Peter Stuyvesant, assicurati di indossare la tua uniforme! Tutto deve sembrare ufficiale, se capisci cosa intendo.";
			link.l1 = "Certo, Cavaliere. Addio!";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "20");
			pchar.questTemp.Patria = "epizode_4";
			Patria_CureerBegin();
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_1");
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_31":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Grazie, capitano, dammelo... (leggendo)... Bene, eccellente! Peter Stuyvesant dice che il Barone Forget potrà visitare Saint Martin per un'ispezione e che il governatore di Philipsburg ne sarà informato e coopererà. Penso che, dopo una visita, il barone prenderà una decisione giusta - lasciare l'isola in affitto agli olandesi.\nE ora, le notizie più rallegranti, capitano! Ho un paio di cose da dirti. Prima: considerando tutti i tuoi successi militari, sei promosso al rango di 'Commodoro'. Accetta le mie congratulazioni, Monsieur!";
			link.l1 = "Servo la Francia!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			dialog.text = "E in secondo luogo: il governatore di Port-au-Prince ci ha inviato una nave mercantile piena di merci per te: 500 sacchi di caffè e altri 500 sacchi di cacao. Questi sono tutti i raccolti delle piantagioni ad Hispaniola, quelle che hai protetto dai raid spagnoli. Inoltre, un carico particolarmente prezioso era destinato a te - 50 unità di lignum vitae. Non credo di dover spiegarti cosa sia. Le tue merci sono nel magazzino del negozio a Capsterville, e puoi andare a prenderle dal mercante in qualsiasi momento.";
			link.l1 = "Grazie, Cavaliere! Notizie fantastiche!";
			link.l1.go = "patria_33";
		break;
		
		case "patria_33":
			dialog.text = "E ora, per quanto riguarda il tuo prossimo compito: il Barone Forget tornerà a Saint-Christopher da un giorno all'altro. Lo porterai a Saint Martin e ti assicurerai che sia ben custodito. E, per così dire, osserverai attentamente ciò che succederà a Philipsburg, e poi mi riporterai. Non lasciare la città, capitano, non appena arriva il barone - il mio pedone ti troverà e ti riporterà.";
			link.l1 = "Tutto è chiaro. Posso andare?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "Potresti. Alcuni giorni di riposo sulla terra saranno buoni e utili per te.";
			link.l1 = "...";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "25");
			pchar.questTemp.Patria = "epizode_5";
			pchar.quest.Patria_CureerBackOver.over = "yes"; // снять таймер
			Items[sti(pchar.EquipedPatentId)].TitulCur = 4; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.quest.Patria_SanMartin_wait.win_condition.l1 = "Timer";
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.hour  = 8+rand(2);
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l2 = "Location_Type";
			pchar.quest.Patria_SanMartin_wait.win_condition.l2.location_type = "town";
			pchar.quest.Patria_SanMartin_wait.function = "Patria_SanMartinBaron";
			pchar.questTemp.Patria.Goods = "true"; // товары-призы
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_36":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_37";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_37":
			dialog.text = "";
			link.l1 = "Sì, Cavaliere, già di ritorno! I tuoi amici olandesi vicino a Saint Martin ci hanno accolto con il fuoco dei cannoni del forte e ci hanno attaccato con una squadra di tre navi. Solo grazie alle abilità del capitano Charles de Maure e del suo equipaggio siamo riusciti a scappare! Sembra che il signor Peter Stuyvesant non voglia realmente vedere gli inviati del re francese a Philipsburg, cosa ne pensi, Cavaliere?";
			link.l1.go = "patria_38";
		break;
		
		case "patria_38":
			dialog.text = "Cosa?! Ecco una lettera da Stuyvesant con la sua firma personale, dove garantisce...";
			link.l1 = "Ma il comandante del forte di Philipsburg ha chiaramente ricevuto una lettera diversa da Stuyvesant, dicendogli di sparare a volontà e di tendere un'imboscata con una squadriglia! È stato un incidente, Cavaliere?! No! Ci stavano chiaramente aspettando lì! Con palle di cannone e pallini!";
			link.l1.go = "patria_39";
		break;
		
		case "patria_39":
			dialog.text = "Barone, ti prego... Me ne occuperò io. Invieremo immediatamente il nostro caro capitano, Charles de Maure, di nuovo a Curacao per incontrare Stuyvesant. Il capitano ha una lunga storia nel gestire situazioni delicate... E ora, chiederò ai servi di preparare un bagno e un buon pranzo per te.";
			link.l1 = "...";
			link.l1.go = "patria_40";
		break;
		
		case "patria_40":
			DialogExit();
			LAi_SetActorType(pchar); // 14-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_41";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_41":
			dialog.text = "Charles, amico mio, devi sbrigarti a Willemstad. Forse, Stuyvesant è ancora lì. Se non lo è - scopri dove si trova e trovalo. Durante l'incontro, parlagli dell'incidente e chiedi una spiegazione. Mi affido alla tua esperienza e autorità, e ti affido la conduzione delle trattative. Poi, senza perdere un solo minuto, torna indietro e riferiscimi i risultati dell'incontro.";
			link.l1 = "La missione è chiara, Cavaliere. Preparerò la nave e partirò immediatamente.";
			link.l1.go = "patria_42";
		break;
		
		case "patria_42":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "29");
			pchar.questTemp.Patria = "epizode_6";
			Patria_DiplomatBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_43":
			dialog.text = "Non posso crederci...";
			link.l1 = "Inoltre, durante il viaggio di ritorno sono stato attaccato da una squadriglia della marina olandese. Per favore, mi spieghi, Chevalier, cosa sta succedendo qui?";
			link.l1.go = "patria_44";
		break;
		
		case "patria_44":
			dialog.text = "Amico mio, sono consapevole di quanto tu sia perspicace, quindi non ti nasconderò nulla. L'unica cosa che ti chiedo - ciò che sentirai non deve uscire da questa stanza. Prometti?";
			link.l1 = "Certo, Chevalier.";
			link.l1.go = "patria_45";
		break;
		
		case "patria_45":
			dialog.text = "Bene. Sono sicuro, ti aspetta una grande carriera nella marina francese. Con il mio aiuto, ovviamente, puoi raggiungere il grado di viceammiraglio! Ma sto divagando... E ora, riguardo gli olandesi e Saint Martin.\nMolto prima che tu arrivassi a Saint Martin, lì erano state trovate grandi giacenze di sale. Inizialmente, a nessuno importava, ma poi gli spagnoli a Cuba e Hispaniola hanno mostrato un grande interesse - per salare le carcasse di toro. Come sicuramente capisci, non possiamo commerciare direttamente con la Spagna, quindi...";
			link.l1 = "...hai creato un 'negoziatore' sotto forma della Compagnia commerciale olandese delle Indie occidentali...";
			link.l1.go = "patria_46";
		break;
		
		case "patria_46":
			dialog.text = "Esattamente! Pensi in fretta - e con precisione, Charles! E ora, sapendo dell'ispezione da Parigi, Stuyvesant ha deciso di prendere audacemente in mano l'intero affare del sale, contando sul fatto che a noi non piace raccontare a tutti del nostro accordo con gli spagnoli. Ma è lì che si è sbagliato. Nessuno può osare prendere dalle mani del Governatore Generale francese senza punizione! E glielo mostreremo proprio.";
			link.l1 = "Come ho capito, il Barone Forget non può saperlo...";
			link.l1.go = "patria_47";
		break;
		
		case "patria_47":
			dialog.text = "Amico mio, hai assolutamente ragione, al barone non servono i dettagli. È già successo abbastanza: un tentativo di togliere la vita al rappresentante del re di Francia, l'attacco alle navi della missione diplomatica, cioè a te, e soprattutto: l'annessione de facto dell'isola di Saint Martin! Questo è sufficiente per giustificare un'azione militare contro gli olandesi.";
			link.l1 = "Guerra?!";
			link.l1.go = "patria_48";
		break;
		
		case "patria_48":
			dialog.text = "Esattamente! Mio amico, la posizione di vice ammiraglio non è così lontana per te, capisci? Immagina te stesso a colloquio nel Louvre in uniforme da ammiraglio, e lo stesso Luigi XIV accoglierà un ospite così onorevole... Dobbiamo mettere gli olandesi al loro posto! Stuyvesant si pentirà di ciò che ha fatto. Sei d'accordo?";
			link.l1 = "Sono d'accordo, Cavaliere. Gli olandesi devono rispondere delle loro azioni oltraggiose e vile.";
			link.l1.go = "patria_49";
		break;
		
		case "patria_49":
			dialog.text = "Eccellente. Informerò il barone della nostra decisione e invierò corrieri alle colonie francesi immediatamente! E tu, mio amico, puoi riposarti dopo un lungo viaggio, e per favore vieni a trovarmi domani dopo le nove del mattino. Preparerò un compito di combattimento per te.";
			link.l1 = "Molto bene, Signore. Permettetemi di scusarmi.";
			link.l1.go = "patria_50";
		break;
		
		case "patria_50":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "33");
			pchar.questTemp.Patria = "epizode_7";
			Patria_HunterBegin();
			pchar.quest.Patria_DiplomatTimeOver.over = "yes"; // снять таймер
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_51":
			dialog.text = "Non lo chiamerei una guerra, più che altro una forzatura della pace, in realtà. E se Stuyvesant cambia idea, ci renderà solo più felici. Ecco perché ora dobbiamo dimostrargli che cercando di rivendicare l'isola di Saint Martin, perderà molto più di quanto guadagnerà. Qui entrerai in gioco tu, Charles.";
			link.l1 = "Sto ascoltando.";
			link.l1.go = "patria_52";
		break;
		
		case "patria_52":
			dialog.text = "Saint Martin è una base di transito per le navi olandesi che vanno in Europa. Le navi della Compagnia sostano regolarmente nella baia di Philipsburg. Fino ad ora, le acque erano abbastanza sicure per loro. Fino ad ora, Capitano!.. Partirai per le coste di Saint Martin e le pattuglierai catturando le navi mercantili della Compagnia.\nPer il trasporto di merci preziose, la Compagnia utilizza gli Orientali - navi resistenti, ben armate con ampie stive. Questi saranno i tuoi obiettivi. Cattura cinque di queste navi insieme ai loro beni e portali come premi a Casterville. Dopo di ciò, continueremo le trattative con Stuyvesant, e forse, dopo aver conteggiato le perdite, cambierà idea.";
			link.l1 = "È chiaro il compito. Posso andare?";
			link.l1.go = "patria_53";
		// belamour legendary edition -->
			link.l2 = "Signore, mi vedo costretto a chiedere, potrebbe partecipare al finanziamento di questa operazione? Saranno mesi di navigazione, riparazioni costanti e perdite...";
			link.l2.go = "patria_53a";
		break;
		
		case "patria_53a":
			AddMoneyToCharacter(pchar, 20000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			dialog.text = "Temiamo che le nostre riserve siano esaurite, Charles. La manutenzione dell'Ecliaton e i combattimenti ci hanno già costato metà del budget annuale delle colonie francesi. Ora, questo è tutto ciò che posso darti ora. Pensa ai premi futuri, Charles! Un grande futuro ti aspetta!";
			link.l1 = "Sì signore!";
			link.l1.go = "patria_54";
		break;
		// <-- legendary edtion
		case "patria_53":
			dialog.text = "Vai, amico mio, e possa la fortuna seguire ogni tuo passo.";
			link.l1 = "...";
			link.l1.go = "patria_54";
		break;
		
		case "patria_54":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "34");
			pchar.questTemp.Patria = "epizode_7_continue";
			Patria_HunterContinue();
		break;
		
		case "patria_55":
			pchar.questTemp.Patria.Hunter = sti(pchar.questTemp.Patria.Hunter)+1;
			if (sti(pchar.questTemp.Patria.Hunter) > 4) // все собрал
			{
				dialog.text = "Hai completato il compito, capitano. Grazie per il tuo eccellente servizio! Dovresti ricevere una parte del reddito dalla vendita dei trofei - duecentomila pesos.";
				link.l1 = "Contento di sentirlo, Monsieur!";
				link.l1.go = "patria_57";
			}
			else
			{
				dialog.text = "Allora, hai solo "+FindRussianQtyString(5-sti(pchar.questTemp.Patria.Hunter))+"Le navi olandesi sono partite per portare al nostro porto.";
				link.l1 = "Sì, Cavaliere!";
				link.l1.go = "patria_56";
			}
		break;
		
		case "patria_56":
			DialogExit();
			AddQuestRecord("Patria", "35");
			AddQuestUserData("Patria", "sQty", 5-sti(pchar.questTemp.Patria.Hunter));
			DeleteAttribute(pchar, "questTemp.Patria.Hunter.GiveShip");
		break;
		
		// belamour legendary edition -->
		case "patria_57":
			AddMoneyToCharacter(pchar, 200000);
			dialog.text = "E questo non è tutto. L'altro giorno ho riflettuto un po'... Charles, hai davvero fatto molto per la Francia. L'eliminazione, francamente, del traditore Levasseur, la difesa di Saint-Pierre dal subdolo attacco della Spagna, la vittoriosa conquista del forte della colonia di San Jose e l'ottenimento di un indennizzo dagli spagnoli come punizione per il loro audace inganno... E dopo tutto questo, hai personalmente accompagnato il rappresentante della corona francese, arrivato dall'Europa, e hai persino salvato la sua vita sfuggendo a un'imboscata olandese nelle acque di Philipsburg!";
			link.l1 = "Signore, davvero, mi metti in imbarazzo... Sto solo facendo il mio dovere.";
			link.l1.go = "patria_57_1";
		break;
		
		case "patria_57_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "Sei modesto come sempre, amico mio. E ora, durante l'esecuzione del prossimo compito di costringere l'Olanda alla pace, non mi hai deluso di nuovo. Non hai paura di questa parola - l'eroe della nazione! Come governatore generale delle colonie francesi nell'arcipelago, ho con me diverse copie del massimo riconoscimento della Francia e ... Ma, a proposito, ti chiedo di leggere questo documento.";
			link.l1 = "Per l'eccezionale servizio alla Francia... nel nome di Sua Maestà il Re di Francia... per premiare un ufficiale navale al servizio della Francia, Capitano Charles de Maure, figlio di Henri de Montpe... Chevalier, stai scherzando?";
			link.l1.go = "patria_57_2";
		break;
		
		case "patria_57_2":
			dialog.text = "Per niente, amico mio. Ho l'onore di premiarti come meriti presentandoti la più alta onorificenza di Francia - l'Ordine di San Luigi! Ogni cittadino del nostro paese dovrebbe conoscere il suo eroe! E Saint-Pierre ti è debitore! Meriti questo Ordine, Charles.";
			link.l1 = "Davvero, non so cosa dire... Grazie, Governatore Generale! Giuro di continuare a servire la Francia con orgoglio e di non ritirarmi di fronte al nemico!";
			link.l1.go = "patria_57_3";
		break;
		
		case "patria_57_3":
			GiveItem2Character(pchar, "talisman9");
			Log_Info("You've received the Order of Saint Louis! You are the hero of the nation!");
			PlaySound("interface\important_item.wav");
			DoQuestCheckDelay("sea_victory", 0.5);
			dialog.text = "Parole di un vero ufficiale! Sono davvero orgoglioso di te, Charles. Ora riposa un po'. Te lo meriti. Nel frattempo, mi occuperò delle negoziazioni con Stuyvesant - forse ha già capito che è molto più svantaggioso per lui essere in conflitto con noi che essere amici. Non lasciare la città, avrò bisogno di te tra due giorni.";
			link.l1 = "Molto bene, signore. Aspetterò ulteriori istruzioni.";
			link.l1.go = "patria_58";
		break;
		// <-- legendary edtion
		case "patria_58":
			DialogExit();
			AddQuestRecord("Patria", "36");
			pchar.questTemp.Patria = "epizode_7_end";
			pchar.quest.Patria_siege_begin.win_condition.l1 = "Timer";
			pchar.quest.Patria_siege_begin.win_condition.l1.date.hour  = 9.00;
			pchar.quest.Patria_siege_begin.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l2 = "location";
			pchar.quest.Patria_siege_begin.win_condition.l2.location = "Charles_town";
			pchar.quest.Patria_siege_begin.function = "Patria_SiegeBegin";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_59":
			dialog.text = "Sì. Sembra che Stuyvesant abbia iniziato a rispondere con azioni militari in alleanza con la Spagna. Una squadra olandese-spagnola ha assediato Saint-Christopher. Ogni ora, i forti sentinella mi riferiscono di ogni loro movimento.";
			link.l1 = "Un assedio?";
			link.l1.go = "patria_60";
		break;
		
		case "patria_60":
			dialog.text = "Ovviamente. Non hanno optato per un attacco diretto, ed è effettivamente un bene. Dobbiamo agire rapidamente, capitano, mentre il nemico non è riuscito a bloccare l'intera isola.";
			link.l1 = "Cosa dobbiamo fare?";
			link.l1.go = "patria_61";
		break;
		
		case "patria_61":
			dialog.text = "A Saint-Jones, ad Antigua, è basata la squadra della Marina inglese del colonnello Doily. Proprio ora, sta visitando Sir Jonathan Fox. Devi passare accanto alle navi nemiche e arrivare ad Antigua. Lì, incontrerai il colonnello, gli consegnerai la mia lettera e gli chiederai aiuto.";
			link.l1 = "Pensi che il Colonnello accetterà di aiutarci?";
			link.l1.go = "patria_62";
		break;
		
		case "patria_62":
			dialog.text = "Spero proprio di sì. La lettera dovrebbe convincerlo che la ricompensa per il suo aiuto sarà piuttosto cospicua... Inoltre, dobbiamo inviare una lettera al capitano dell' 'Eclatant', attualmente vicino alle coste di Guadalupa, deve affrettarsi a Saint-Christopher. La potenza di fuoco dell' 'Eclatant' ci aiuterà notevolmente nella battaglia. Poiché non puoi essere in due posti contemporaneamente, il nostro luggero corriere si unirà alla tua squadra - devi farlo passare indenne attraverso il cerchio dei nemici, e partirà per Guadalupa, prima che l' 'Eclatant' si diriga a Sud...";
			link.l1 = "Capisco. Attraversa l'assedio, scorta il pinnace del corriere e affrettati a Saint-Jones dal Colonnello Doily con la tua lettera.";
			link.l1.go = "patria_63";
		break;
		
		case "patria_63":
			dialog.text = "Esattamente. Sei pronto ad accettare un'altra nave nella tua squadriglia?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "Mi libererò di una nave e tornerò da te.";
				link.l1.go = "patria_63_1";
			}
			else
			{
				link.l1 = "Sì.";
				link.l1.go = "patria_64";
			}
		break;
		
		case "patria_63_1":
			DialogExit();
			pchar.questTemp.Patria = "epizode_8_wait";
		break;
		
		case "patria_64":
			dialog.text = "Eccellente. Prendi la lettera, la lancia è pronta e aspetta i tuoi comandi.";
			link.l1 = "Non perdiamo tempo, Chevalier!";
			link.l1.go = "patria_65";
		break;
		
		case "patria_65":
			DialogExit();
			AddQuestRecord("Patria", "38");
			pchar.questTemp.Patria = "epizode_8_continue";
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_3");
			Patria_SiegeCreateSquadron();
		break;
		
		case "patria_66":
			dialog.text = "Sì-sì, amico mio, conosco tutta la tua modestia. Sei un vero ufficiale! E riceverai una ricompensa, te lo assicuro! Immagino che, dopo la dura battaglia, avrai bisogno di riposo? Hai un'intera settimana. Vieni a parlare nella mia stanza tra sette giorni - la città preparerà una ricompensa per il suo eroe.";
			link.l1 = "Sì, Monsieur. Posso andare?";
			link.l1.go = "patria_67";
		break;
		
		case "patria_67":
			dialog.text = "Vai e riposati bene. Più tardi dovremo affrontare questioni serie - Come puoi vedere, una pace con gli olandesi è impossibile a questo punto. Per ora, il colonnello ed io discuteremo alcune questioni importanti.";
			link.l1 = "Allora ci incontreremo tra una settimana, Cavaliere.";
			link.l1.go = "patria_68";
		break;
		
		case "patria_68":
			DialogExit();
			AddQuestRecord("Patria", "45");
			pchar.questTemp.Patria = "epizode_8_end";
			Patria_SiegeEnd();
			ChangeCharacterNationReputation(pchar, FRANCE, 20);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_69":
			pchar.quest.Patria_BastionTimeOver.over = "yes"; //снять таймер
			dialog.text = "Abbiamo avuto una discussione con il colonnello Doily ed ha accettato di aiutarmi. L'Inghilterra ci aiuterà nella guerra contro gli olandesi. Tu ed io dobbiamo contrattaccare e ripristinare la giustizia - l'isola di Saint Martin deve tornare alla Francia. Affido questo compito al miglior capitano della marina - a te, Charles de Maure! Il nemico non si è ancora ripreso dalla sconfitta della loro squadra, attaccheremo Philipsburg e la prenderemo.\nLa battaglia non sarà facile. Prima, dobbiamo distruggere il forte, poi rompere la difesa della guarnigione...(sussurrando) Dovrai anche fare una marcia forzata attraverso la giungla fino al deposito di sale di cui ti ho parlato, e uccidere i nemici accampati lì...";
			link.l1 = "La missione è molto dura, Cavaliere...";
			link.l1.go = "patria_70";
		break;
		
		case "patria_70":
			dialog.text = "Ti capisco perfettamente, amico mio. La tua squadra sarà rafforzata. I governatori di Basse-Terre e Saint-Pierre dovrebbero aver preparato una nave ciascuno - una fregata - già adesso. Dovrai solo visitare la Guadalupa e la Martinica e prendere queste fregate sotto il tuo comando. Se, naturalmente, le vuoi tu stesso - non insisterò sulla tua scelta di navi. Ti do anche un sussidio di 20.000 pesos per acquistare provviste e attrezzature per la tua nave ammiraglia. Ecco, prendilo...";
			link.l1 = "Molto bene, Monsieur.";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_71";
			else link.l1.go = "patria_71_1";
		break;
		
		case "patria_71_1":
			dialog.text = "Inoltre, come al solito, la nave 'Eclatant' è sotto il tuo comando. È stata riparata e attrezzata, attende in rada, e dopo aver parlato con il capitano, sarai in grado di prenderla in qualsiasi momento.";
			link.l1 = "Eccellente!";
			link.l1.go = "patria_71";
			pchar.questTemp.Patria.Ecliaton_Bastion = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_7";
			sld.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "patria_71":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "Non possiamo perdere tempo, capitano. Come mi hanno informato le mie spie, gli olandesi capiscono il pericolo per Saint Martin e intendono rafforzare le sue difese. Ma hai ancora due mesi. Devi completare il compito in tempo!";
			link.l1 = "Lo farò... (sussurrando) Dov'è il deposito di sale di Saint Martin? Non è segnato su nessuna mappa dell'isola...";
			link.l1.go = "patria_72";
		break;
		
		case "patria_72":
			dialog.text = "(sussurrando) Quando assalirai la città, interroga il viceré di Philipsburg, Mynheer Martin Thomas, lui ti dirà. Quel olandese è un codardo e non ti resisterà, te lo garantisco.";
			link.l1 = "Capisco. Posso andare ora?";
			link.l1.go = "patria_73";
		break;
		
		case "patria_73":
			dialog.text = "Aspetta un momento, Charles. Non hai ancora ricevuto la tua ricompensa per aver salvato Saint-Christopher. Prendi questi bauli d'oro dalla gente della città, oltre alla nostra più sincera gratitudine, che nessuna somma di denaro può esprimere!";
			link.l1 = "Grazie, Signore!";
			link.l1.go = "patria_74";
		break;
		
		case "patria_74":
			TakeNItems(pchar, "chest", 10);
			Log_Info("You've received 10 chests of doublons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ora puoi andare. Buona fortuna, capitano! Stiamo tutti aspettando la tua vittoria!";
			link.l1 = "Addio, Cavaliere.";
			link.l1.go = "patria_75";
		break;
		
		case "patria_75":
			DialogExit();
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Bastion")) sTemp = "The warship 'Eclatant' will also be under my command.";
			AddQuestRecord("Patria", "48");
			AddQuestUserData("Patria", "sText", sTemp);
			pchar.questTemp.Patria = "epizode_9_continue";
			SetFunctionTimerCondition("Patria_BastionSturmTimeOver", 0, 0, 62, false);
			// вернуть Синт-Маартен в норму
			int n = FindIsland("SentMartin");
			Islands[n].reload.l1.radius = 600.0;
			LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", false); // открыть городские ворота
			sld = CharacterFromID("Marigo Fort Commander");
			LAi_SetImmortal(sld, false);
			Character_SetAbordageEnable(sld, true);
			// атрибут квестовой высадки десанта
			pchar.TempPerks.QuestTroopers = true;
		break;
		
		case "patria_76":
			dialog.text = "Chi avrebbe mai pensato solo un anno fa che saresti stato promosso al grado di viceammiraglio, amico mio? Posso solo immaginare quanto sarà orgoglioso tuo padre quando la notizia raggiungerà la Francia!";
			link.l1 = "Mio caro padre sarà estremamente felice di questo.";
			link.l1.go = "patria_77";
		break;
		
		case "patria_77":
			dialog.text = "Hai guadagnato il tuo posto nella flotta! Saint Martin è stata restituita alla Francia, Stuyvesant ha imparato una dura lezione. Questa è stata una grande vittoria! Ma non dobbiamo fermarci, non possiamo lasciare un minuto di riposo agli olandesi. Saranno ritenuti responsabili del loro tradimento! Il colonnello Doily si trova a Port-Royal in questo momento, sta preparando la sua squadra navale: andremo a spezzare la schiena del nostro nemico colpendo a Curacao. Ma questo sarà più tardi, per ora dobbiamo uccidere due uccelli con una fava, Charles. \nLa Compagnia non ha guadagnato tutte le sue immense ricchezze con il commercio. La principale fonte di reddito degli olandesi nella regione è il lavoro degli schiavi nelle loro piantagioni. Se non ne sei a conoscenza, Charles: l'Olanda è la nazione più grande proprietaria di schiavi e commerciante di schiavi. Gli indiani dell'Est che portano l'";
			link.l1 = "Il servizio non è miele, Chevalier. Lo so meglio di chiunque altro. Preparerò la mia nave e partirò appena possibile.";
			link.l1.go = "patria_78";
		break;
		
		case "patria_78":
			dialog.text = "Vi auguro buoni venti e un viaggio sereno, viceammiraglio. E quando tornerete a Saint-Christopher, il nostro amico comune, Monsieur Noel Forget, avrà terminato la sua ispezione di Philipsburg, e mi assicurerò che parte dei trofei che prenderanno dai Olandesi andranno personalmente a voi.";
			link.l1 = "Mi renderà molto grato, Cavaliere. Posso andare?";
			link.l1.go = "patria_79";
		break;
		
		case "patria_79":
			dialog.text = "Vai. Buona fortuna a te, amico mio!";
			link.l1 = "...";
			link.l1.go = "patria_80";
		break;
		
		case "patria_80":
			DialogExit();
			Items[sti(pchar.EquipedPatentId)].TitulCur = 5; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.questTemp.Patria = "epizode_10_start";
			AddQuestRecord("Patria", "52");
			Patria_SlaveShipsStart();
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_81":
			dialog.text = "Eccellente! Non conosci la parola 'impossibile', Charles. Pensavo che tuo fratello fosse il miglior ufficiale della marina nei Caraibi, ma ha molto da imparare da te, se mi perdoni questo grossolano confronto. Penso che tu sappia già chi si recherà dal nostro caro colonnello per partecipare all'assalto a Willemstad.";
			link.l1 = "Assolutamente no, Signore! Come potrei saperlo!";
			link.l1.go = "patria_82";
		break;
		
		case "patria_82":
			dialog.text = "Ah, il tuo famoso senso dell'umorismo, mio caro amico! Ha-hah! Naturalmente, sarai tu, vice-ammiraglio. Il più degno di tutti. Sei pronto?";
			link.l1 = "Certo, Cavaliere. Tutto ciò di cui ho bisogno sono alcune riparazioni, un po' di attrezzatura - e sono pronto a partire.";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_83";
			else link.l1.go = "patria_83_1";
		break;
		
		case "patria_83_1":
			dialog.text = "Non dimenticare di prendere sotto il tuo comando l''Eclatant'. È stato riparato e attrezzato, ti aspetta nel porto. Il marchese Hubert Dassier sta già diventando impaziente e aspetta di andare in un'altra battaglia con te.";
			link.l1 = "Ottimo. Una poderosa nave con culverine a lungo raggio è esattamente ciò di cui ho bisogno per bombardare il forte.";
			link.l1.go = "patria_83";
			pchar.questTemp.Patria.Ecliaton_Curacao = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_11";
			sld.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "patria_83":
			dialog.text = "Aspetta un minuto, Charles. Il nostro amico, Barone Forget, ha portato notizie per te da Saint Martin.";
			link.l1 = "...";
			link.l1.go = "patria_84";
		break;
		
		case "patria_84":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_25";
			sld.greeting = "noel_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			ChangeCharacterComplexReputation(pchar, "nobility", 2); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
		break;
		
		case "patria_85":
			dialog.text = "Ho notizie per te da Parigi. La tua nomina a viceammiraglio è stata firmata dal Re. Riceverai i documenti pertinenti. Quindi, ti faccio i miei complimenti!";
			link.l1 = "Grazie, Monsieur! Felice di servire la Francia e il Re!";
			link.l1.go = "patria_coat";
		break;
		
		case "patria_coat":
			dialog.text = "E io, come sempre, sono molto lieto di sentire queste parole da te. Charles, forse vorresti condividere un po' di vino con me? Portato direttamente da Parigi, non troverai questo tipo qui per un giorno di viaggio!";
			link.l1 = "Grazie, cavaliere, ma credo che passerò. Devo tornare alla nave più tardi, e non sarebbe appropriato per il vice ammiraglio di Francia essere ubriaco sul cassero.";
			link.l1.go = "patria_coat_01";
			link.l2 = "Ebbene, perché no? Non è tutti i giorni che ho l'opportunità di condividere un drink con il governatore generale in persona!";
			link.l2.go = "patria_coat_02";
		break;
		
		case "patria_coat_01":
			dialog.text = "Ebbene, potresti prenderti una pausa, non c'è bisogno di tornare subito sulla nave. Ma è il tuo desiderio, e lo rispetto. Bene, passiamo direttamente agli affari.";
			link.l1 = "Sto ascoltando attentamente.";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_02":
			dialog.text = "E non ogni governatore generale ha la fortuna di avere il suo viceammiraglio non solo come il più fine ufficiale navale, ma anche come un amico, con il quale potrebbe sedersi allo stesso tavolo e bere vino portato da una lontana patria!";
			link.l1 = "Per la Francia!";
			link.l1.go = "patria_coat_03";
			link.l2 = "Alla tua salute, cavaliere!";
			link.l2.go = "patria_coat_04";
		break;
		
		case "patria_coat_03":
			dialog.text = "E per il re!";
			link.l1 = "...";
			link.l1.go = "patria_coat_05";
		break;
		
		case "patria_coat_04":
			dialog.text = "E alla tua, Charles!";
			link.l1 = "...";
			link.l1.go = "patria_coat_05";
		break;
		
		case "patria_coat_05":
			LAi_Fade("", "");
			if(LAi_GetCharacterHP(pchar) == LAi_GetCharacterMaxHP(pchar))
			pchar.chr_ai.hp = stf(pchar.chr_ai.hp) - 1.0;
			GiveItem2Character(pchar, "potionwine");
			DoCharacterUsedItem(pchar, "potionwine");
			npchar.dialog.currentnode = "patria_coat_06";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorSetHuberMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 1.2);
		break;
		
		case "patria_coat_06":
			dialog.text = "Mh, vino squisito! Non credi anche tu?";
			link.l1 = "Sì, avevi ragione. Mi ricorda il vino che fanno a casa mia in Guascogna...";
			link.l1.go = "patria_coat_07";
		break;
		
		case "patria_coat_07":
			dialog.text = "Sei un po' fuori strada, amico mio - è Bordeaux. Tuttavia, sono sicuro che il vino della Guascogna sia altrettanto buono!";
			link.l1 = "Penso di cominciare a dimenticare il suo sapore... Quanto tempo è passato da quando ho lasciato la Francia? Un anno? Due?";
			link.l1.go = "patria_coat_08";
		break;
		
		case "patria_coat_08":
			dialog.text = "Ah, Charles, sembra che ci siamo incontrati solo di recente...e non nelle circostanze più piacevoli. Perdonami per aver sollevato questo argomento, ma se qualcuno mi avesse detto allora che nella cella di prigione di fronte a me stava il mio futuro braccio destro nelle colonie francesi, probabilmente avrei riso a crepapelle.";
			link.l1 = "Le vie del Signore sono insondabili.";
			link.l1.go = "patria_coat_09";
		break;
		
		case "patria_coat_09":
			dialog.text = "Scusami, cosa hai appena detto?";
			link.l1 = "È latino, cavaliere. Le vie del Signore sono insondabili. Nessuno sa cosa riserva la vita.";
			link.l1.go = "patria_coat_10";
		break;
		
		case "patria_coat_10":
			dialog.text = "Non smetti mai di stupirmi, Charles. Guardati - non avevo idea che potessi anche parlare latino. Ma d'altra parte, in qualche misura, forgiamo il nostro destino, non è vero?";
			link.l1 = "Credo che entrambe le cose siano vere. Solo il Signore sa cosa ci aspetta. Ma premia i persistenti.";
			link.l1.go = "patria_coat_11";
		break;
		
		case "patria_coat_11":
			dialog.text = "Non potrei essere più d'accordo. Ricordo, per esempio, quando ti ho consegnato la commissione di un ufficiale navale e ti ho dato quella divisa. E ora, davanti a me, si erge un vice ammiraglio, non meno!";
			link.l1 = "Il tempo vola, cavaliere.";
			link.l1.go = "patria_coat_12";
		break;
		
		case "patria_coat_12":
			dialog.text = "Indeed... And even on your uniform, I see the cuts left by sabers; some cuts have been stitched, and some are clearly fresh. This needs to be corrected.";
			link.l1 = "Cosa hai in mente, Signor Governatore Generale?";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_13":
			dialog.text = "Oltre alla tua nuova posizione di Viceammiraglio della flotta francese nell'arcipelago dei Caraibi, ho un altro dono per te.";
			link.l1 = "Mi stai facendo arrossire, cavaliere. Quale regalo?";
			link.l1.go = "patria_coat_14";
		break;
		
		case "patria_coat_14":
			dialog.text = "Ho organizzato con il mio sarto personale - il migliore nelle colonie francesi! - per cucire una divisa adatta al tuo grado. Non preoccuparti del pagamento, ho preso cura di tutto.";
			link.l1 = "Sono davvero grato! Farò sicuramente visita al tuo sarto. Dove posso trovarlo?";
			link.l1.go = "patria_coat_15";
		break;
		
		case "patria_coat_15":
			dialog.text = "Dovrebbe essere nell'ufficio del porto in questo momento - una nuova nave corriere è appena arrivata dalla terraferma con piccoli pacchi. Il nostro sarto ordina sempre alcuni materiali che sono difficili da trovare qui.";
			link.l1 = "Andrò quindi all'ufficio portuale. Grazie ancora, signore!";
			link.l1.go = "patria_86";
		break;
		
		case "patria_86":
			dialog.text = "E ora, sono certo, avrai bisogno di riposarti bene. Ti do un mese, e assicurati di spenderlo bene. Nessun lavoro, nessuna preoccupazione. Lascia tutto il lavoro ai tuoi ufficiali e riposati bene. Puoi usare le stanze nella mia residenza. I servi renderanno la tua vacanza più confortevole. Ci incontreremo di nuovo tra un mese - e avrò una questione delicata da discutere con te.";
			link.l1 = "Molto bene, Cavaliere. Addio!";
			link.l1.go = "patria_87";
		break;
		
		case "patria_87":
			npchar.dialog.currentnode = "First time";
			LAi_Fade("","");
			LAi_SetHuberType(npchar);
			DialogExit();
			AddQuestRecord("Patria", "65"); // далее коллизия Пуанси-Инспектор-Шарль
			pchar.questTemp.Patria = "epizode_12_start";
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			SetFunctionLocationCondition("Patria_Tailor", "Charles_PortOffice", false)
			Patria_CondotierStart();
			ChangeCharacterComplexReputation(pchar, "nobility", 15); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 15);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
		break;
		
		case "patria_88":
			dialog.text = "Sì, Charles. Pensavo di gestire questo da solo, ma ... ahimè, devo chiederti di utilizzare ancora una volta i tuoi talenti. Ma prima, devo darti qualcosa: trecentomila pesos e cinque casse di dobloni. Questa è una grande parte del contributo che Stuyvesant mi ha pagato secondo l'accordo. Suppongo che tu abbia guadagnato tutto questo, dato che hai fatto la maggior parte del lavoro. Accettalo. Sei soddisfatto, amico mio?";
			link.l1 = "I soldi non hanno mai fatto male a nessuno, Monsieur, ho imparato bene questa lezione.";
			link.l1.go = "patria_89";
		break;
		
		case "patria_89":
			AddMoneyToCharacter(pchar, 300000); 
			TakeNItems(pchar, "chest", 5);
			dialog.text = "Ah, viceammiraglio, spero che non ti abbia offeso quello che è successo in passato?.. Ora sei un eroe della tua nazione, lo sapevi? Come ti senti in questa nuova posizione? Ricorda: molti ufficiali degni hanno passato decenni a scalare la scala gerarchica, ma senza una mano esperta... rimangono nella posizione di comandante. Ma tu, mio amico, hai un'abilità unica di compiere sempre l'impossibile! E hai un amico nelle alte sfere, che è anche il tuo protettore, quindi se avrai problemi in futuro sarò lì per aiutarti.";
			link.l1 = "Grazie per queste gentili parole, vostra Eccellenza. Ho la sensazione di aver realizzato quasi tutto in questa regione. Con il vostro aiuto, ovviamente. Suppongo, ora posso occuparmi dei miei problemi in pace? Devo pensare alla mia famiglia.";
			link.l1.go = "patria_90";
		break;
		
		case "patria_90":
			dialog.text = "Vuoi sposarti, Charles? Ah-ha-ha! Indica qualsiasi bella donna a Parigi - e sarà subito tua! Ma, ahimè, dovrà aspettare. Ho bisogno di te qui, amico mio, almeno per ora.";
			link.l1 = "Sembra che la Francia sia più forte che mai nell'Arcipelago. Un'alleanza con gli inglesi, una tregua con la Compagnia. Non ci sono problematici... 'Levasseurs' rimasti. Giusto?";
			link.l1.go = "patria_91";
		break;
		
		case "patria_91":
			dialog.text = "Le nazioni, molto simili alle persone, desiderano sempre di più, indipendentemente da quanto hanno... E infatti abbiamo un nuovo 'Levasseur', viceammiraglio...";
			link.l1 = "Davvero? E chi sarebbe?";
			link.l1.go = "patria_92";
		break;
		
		case "patria_92":
			dialog.text = "È il nostro vecchio conoscente reciproco, il Barone Noel Forget. Ti ricordi perché è venuto qui?";
			link.l1 = "Mmm... Hai detto qualcosa sulla Compagnia commerciale delle Indie Occidentali. Parigi ha deciso di creare la stessa organizzazione come i olandesi?";
			link.l1.go = "patria_93";
		break;
		
		case "patria_93":
			dialog.text = "Esattamente. Analogamente alla Compagnia Olandese. Ma crearne una da zero è molto difficile. Vedi, Stuyvesant aveva decenni di commercio con diversi continenti alle spalle, una rete sviluppata di agenti e una potente flotta di navi mercantili. La Francia non ha tutto ciò e, se non lo sapevi, Charles, il Re sta attraversando una grave mancanza di fondi in questo momento. Vogliono risolvere la situazione finanziaria della metropoli dirigendo il commercio qui, ma non capiscono ciò a cui dovremo far fronte.\nLa rivalità sia degli Inglesi che degli Olandesi, le ambizioni territoriali degli Spagnoli, la pirateria che fiorisce come mai prima. Ogni nave mercantile ha bisogno di essere scortata da una nave da guerra, o rischierà di non raggiungere mai la sua destinazione. E non abbiamo una potente flotta come gli Olandesi delle Indie Orientali, o i potenti Galleoni come quelli degli Spagnoli.";
			link.l1 = "Ma hai spiegato tutto questo al barone? Anche dei pirati?";
			link.l1.go = "patria_94";
		break;
		
		case "patria_94":
			dialog.text = "Certo che l'ho fatto. E riguardo alla cacciata dei pirati da Tortuga dopo la tua missione di eliminazione di Levasseur, cosa che i pirati non hanno dimenticato e ci porteranno sempre rancore. Ho organizzato incontri con varie persone che hanno confermato le mie preoccupazioni, ma purtroppo, ciò non ha avuto alcun effetto sul barone. È stato mandato qui dai ministri, ed è loro che deve... È semplicemente così.";
			link.l1 = "Eh...";
			link.l1.go = "patria_95";
		break;
		
		case "patria_95":
			dialog.text = "E non nascondiamo il fatto che una compagnia commerciale nell'Arcipelago, con controllo diretto da Parigi... tu ed io, vice ammiraglio... non ne abbiamo bisogno qui.";
			link.l1 = "Capisco.";
			link.l1.go = "patria_96";
		break;
		
		case "patria_96":
			dialog.text = "Vedi, amico mio, sono estremamente sincero con te... Così, speravo con tutto il cuore che Monsieur Forget cambiasse idea sulla creazione di questa compagnia commerciale, ma... non è successo. Ho sprecato tutta la mia influenza sul barone, e ora devi entrare in gioco tu.";
			link.l1 = "Ah... Proprio come con Levasseur?";
			link.l1.go = "patria_97";
		break;
		
		case "patria_97":
			dialog.text = "Oh dio no, per chi mi prendi, Charles?! Il barone è una figura influente, un amico del Ministro delle Finanze! E poi, eliminarlo fisicamente non porterà a nulla: semplicemente verrà inviato un nuovo politico da Parigi. Dobbiamo distruggere l'idea di organizzare tale compagnia in primo luogo, capisci, Charles? Così che il barone ritornerebbe in Francia e riferirebbe che sarebbe finanziariamente rischioso, assurdo...";
			link.l1 = "Avete un'idea, Monsieur?";
			link.l1.go = "patria_98";
		break;
		
		case "patria_98":
			dialog.text = "Purtroppo no, Charles. Ho provato di tutto. L'ho spaventato con la mancanza di navi e denaro, i olandesi, i pirati... Nessun effetto.";
			link.l1 = "Sembra, abbiamo bisogno di qualcosa di più serio delle semplici parole. Hm... Pirati, dici?";
			link.l1.go = "patria_99";
		break;
		
		case "patria_99":
			dialog.text = "Vedo che hai un'idea, amico mio? Non avevo dubbi. Hai una mente brillante. Persuadi questo barone, e mi assicurerò che tuo padre abbia abbastanza soldi per riempire tutta la tua casa con ricchezze degne del Louvre. Te lo prometto, Charles.";
			link.l1 = "Molto bene, Cavaliere. Il compito è chiaro.";
			link.l1.go = "patria_100";
		break;
		
		case "patria_100":
			dialog.text = "Ti giuro, Charles, non te ne pentirai se avrai successo. Puoi esserne certo. Ti ho mai tradito, amico mio?";
			link.l1 = "Assolutamente no, signore. Dove posso trovare il Barone?";
			link.l1.go = "patria_101";
		break;
		
		case "patria_101":
			dialog.text = "Adesso, si trova a Port-au-Prince. Ha detto che trova i campi e le valli senza fine di Hispaniola molto affascinanti...";
			link.l1 = "Bene. Ora, permettimi di scusarmi.";
			link.l1.go = "patria_102";
		break;
		
		case "patria_102":
			DialogExit();
			AddQuestRecord("Patria", "67");
			pchar.questTemp.Patria = "epizode_12_pirates";
			Patria_CondotierSail();
		break;
		
		case "patria_103":
			dialog.text = "Proprio così. Il barone mi ha raccontato tutto. Dopo tutto quello che ha passato... Tuttavia, tu riesci a spiegare le cose in modo chiaro, come nessun altro, viceammiraglio! Dovrei imparare da te!";
			link.l1 = "Ho imparato molto da te, Cavaliere.";
			link.l1.go = "patria_104";
		break;
		
		case "patria_104":
			dialog.text = "Amico mio, ti devo. Ti assicuro che tuo caro padre avrà tutto ciò di cui ha bisogno o di cui avrà mai bisogno nella sua vita, e la tua casa familiare sarà la migliore della provincia... e una delle migliori in Francia. Inoltre, ti pagherò 100 000 pesos - spero, coprirà il tuo debito con i pirati...";
			link.l1 = "È bello sentire questo, Monsieur!";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_105add":
			AddMoneyToCharacter(pchar, 100000); 
			dialog.text = "Ho anche preparato un regalo speciale per te. Sono sicuro che apprezzerai il valore di questo oggetto e la sincerità della mia gratitudine per il tuo leale servizio! Quindi, Viceammiraglio Charles de Maure, ti do la mia spada cerimoniale personale dell'Ordine di Malta! Quest'arma preziosa si adatterà alla tua uniforme, penso! Se decidi di tornare a Parigi, il barone Noel Forget ha promesso di presentarti al Re - dovresti andare da lui in piena parata: indossando la tua uniforme e portando questa eccellente lama! Ti aspettano ancora più gloriose opportunità di carriera nella marina francese!";
			link.l1 = "Questa spada è incomparabile nella sua bellezza! Grazie, Monsieur, davvero non merito questo onore...";
			link.l1.go = "patria_105";
		break;
		
		case "patria_105":
			ref itm = ItemsFromID("blade_36");
			itm.picIndex = 16;
			itm.picTexture = "ITEMS_17";
			itm.price = 10000;
			itm.Weight = 3.0;
			itm.lenght = 1.05;
			itm.curve = 1.0;
			itm.Balance = 1.9;
			GiveItem2Character(pchar, "blade_36");
			Log_Info("You've received the Maltese Sword");
			PlaySound("interface\important_item.wav");
			dialog.text = "Lo fai! E mentre sei qui, ti attendono grandi cambiamenti. Buoni cambiamenti. Viceammiraglio Charles de Maure, ti nomino Governatore di Saint Martin!";
			link.l1 = "Aah! Ti ho sentito correttamente?";
			link.l1.go = "patria_106";
		break;
		
		case "patria_106":
			ChangeCharacterComplexReputation(pchar, "nobility", 12); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 12);
			ChangeCharacterComplexReputation(pchar, "fame", 12);
			dialog.text = "Sì, mio amico. Ora sei il governatore di Saint Martin, che hai protetto così diligentemente.";
			link.l1 = "Cavaliere, permettetemi di rifiutare questo onore. Non desidero essere legato a questa misera isola! E tutti questi problemi domestici... Non è quello che sono destinato a fare!";
			link.l1.go = "patria_107";
		break;
		
		case "patria_107":
			dialog.text = "Non accetto il rifiuto. Amico mio, non aver paura: vivrai come prima. Tutte le cose noiose saranno gestite dall'attuale governatore ad interim. Tu sarai il governatore de facto. Charles, non capisci perché TU sei stato nominato per governare Saint Martin? Ora è il momento giusto, quando nessuno farà domande. Ho bisogno di uno dei MIEI uomini come governatore lì, capisci cosa intendo?";
			link.l1 = "La miniera di sale?";
			link.l1.go = "patria_108";
		break;
		
		case "patria_108":
			dialog.text = "Certo! E la seconda buona notizia: d'ora in poi, il 15 di ogni mese, riceverai una parte del profitto della miniera, così come dal commercio di Doily. Il tuo reddito passivo sarà di 100.000 pesos al mese.";
			link.l1 = "Ah! Sono lieto di sentire questo! Grazie, Cavaliere. Beh, se non sarò obbligato a stare seduto lì, accetto il governatorato. E se decido di navigare verso la Francia?";
			link.l1.go = "patria_109";
		break;
		
		case "patria_109":
			dialog.text = "Quando deciderai - andrai, e io, nonostante sia molto deluso, troverò un sostituto per te. Ma non è tutto. Ho una lettera da tuo padre qui. Dai un'occhiata.";
			link.l1 = "Dal mio padre? Sono emozionato!.. Molto bene, Monsieur, accordo. Posso andare ora? Desidero leggere la lettera... Nessun nuovo compito per me?";
			link.l1.go = "patria_110";
		break;
		
		case "patria_110":
			dialog.text = "Non ora, Governatore, ma se trovo del lavoro, so come trovarvi. Buona fortuna, Charles!";
			link.l1 = "E a te, Cavaliere!";
			if (pchar.questTemp.Patria == "epizode_12_baronwin") link.l1.go = "patria_119";
			else link.l1.go = "patria_111";
		break;
		
		case "patria_111":
			DialogExit();
			AddQuestRecord("Patria", "77");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_112":
			dialog.text = "Per Dio, che disastro! Ora abbiamo più problemi da affrontare. Sei tu responsabile di questo, Charles? Dimmi la verità. È stato un incidente?";
			link.l1 = "Beh, qualcosa è andato storto...";
			link.l1.go = "patria_113";
		break;
		
		case "patria_x112":
			dialog.text = "Dannazione, che disastro! Ora abbiamo più problemi da affrontare. Il Barone ha scelto un posto molto brutto dove morire! Sei sicuro di non averlo aiutato a lasciare questo mondo?";
			link.l1 = "Cosa stai dicendo, Cavaliere?! Naturalmente no!";
			link.l1.go = "patria_x113";
		break;
		
		case "patria_y112":
			dialog.text = "Dannazione, che disastro! Ora abbiamo più problemi da affrontare. Sei sicuro di non avergli aiutato a lasciare questo mondo?";
			link.l1 = "Cosa stai dicendo, Cavaliere?! Certamente no!";
			link.l1.go = "patria_y113";
		break;
		
		case "patria_x113":
			dialog.text = "Bene. Allora, amico mio, forse non tutto è rovinato. La febbre è febbre, giusto? E fino a quando non arriverà un nuovo ispettore dal ministero, puliremo il pasticcio qui e aspetteremo i nostri ospiti ben armati... E ora, Charles, dobbiamo interrompere tutti i nostri contatti. Spero tu capisca il perché?";
			link.l1 = "Certo.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_y113":
			dialog.text = "Bene. Allora, amico mio, forse non tutto è perduto. Si prevedono battaglie nei Caraibi, giusto? E fino a quando non arriverà un nuovo ispettore dal ministero, puliremo il pasticcio qui e aspetteremo i nostri ospiti ben armati... E ora, Charles, dobbiamo chiudere tutti i nostri contatti. Spero tu capisca il perché?";
			link.l1 = "Certo.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_113":
			dialog.text = "Bene. Allora, amico mio, forse non tutto è rovinato. I pirati sono pirati, vero? E fino a quando non arriverà un nuovo ispettore dal ministero, puliremo il casino qui e aspetteremo i nostri ospiti ben armati... E ora, Charles, dobbiamo interrompere tutti i nostri contatti. Spero tu capisca il perché?";
			link.l1 = "Certo.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_114":
			dialog.text = "In ogni caso, amico mio, hai fatto tutto il possibile. Ed è meglio di niente. Sono contento che il destino ci abbia uniti. Puoi mantenere la tua posizione, e sono sicuro che ti aspetta una grande carriera in Francia. E, penso che sia ora per te di tornare a Parigi. Ecco, una lettera da tuo padre. Prendila.";
			link.l1 = "Mio padre? Questa è un'ottima notizia!.. Bene, Monsieur, ho capito. Nessun contatto, piena segretezza, e appena posso - mi reco a Parigi. Posso andare ora? Desidero leggere la lettera...";
			link.l1.go = "patria_115";
		break;
		
		case "patria_115":
			dialog.text = "Vai, Charles. Buona fortuna!";
			link.l1 = "E a te, Cavaliere!";
			link.l1.go = "patria_116";
		break;
		
		case "patria_116":
			DialogExit();
			AddQuestRecord("Patria", "78");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_117":
			dialog.text = "Esattamente. Puoi spiegare le cose chiaramente come nessun altro, vice-ammiraglio! Dovrei imparare questo da te!!";
			link.l1 = "Ho imparato molto da te, Cavaliere.";
			link.l1.go = "patria_118";
		break;
		
		case "patria_118":
			dialog.text = "Mio amico, ti devo. Ti assicuro che tuo caro padre avrà tutto ciò di cui ha bisogno o avrà mai bisogno nella sua vita, e la tua casa familiare sarà la migliore della provincia... e una delle migliori in Francia. Inoltre, ti pagherò 100.000 pesos - spero che coprirà le tue spese di viaggio e ti permetterà di goderti un meritato riposo.";
			link.l1 = "È bello sentire questo, Monsieur!";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_119":
			DialogExit();
			AddQuestRecord("Patria", "87");
			pchar.questTemp.Patria = "europe";
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			SetFunctionTimerCondition("Patria_EuropeTime", 0, 0, 175+rand(10), false); // таймер
		break;
		
		case "patria_prison":
			dialog.text = "Come hai potuto, Charles! Come hai potuto farlo a me?!";
			link.l1 = "Ehm...";
			link.l1.go = "patria_prison_1";
		break;
		
		case "patria_prison_1":
			dialog.text = "So che sei stato tu! Hai fatto tu! Non negarlo! Senza il tuo aiuto, il Barone Forget non avrebbe mai ottenuto né i rapporti del direttore della miniera, né la posizione della miniera, né i documenti di Peter Stuyvesant. Il tuo nome non è stato menzionato lì, ma lascia che te lo dica, so per certo: sei stato tu. Perché, Charles?.. Rispondimi solo... Perché? Michel? Un milione di pesos? Levasseur? O forse la posizione del Governatore Generale?";
			// belamour legendary edition -->
			link.l1 = "Ricordi il nostro primo incontro, Cavaliere? Come mi hai messo al mio posto? Come mi hai estorto un milione di pesos? Desideravo solo che un giorno potessimo scambiarci i posti. Non ho altro da dirti.";
			link.l1.go = "patria_prison_2";
			link.l2 = "Per Levasseur. Un debito di un milione, posso ancora capire. Ho lavorato, ho ucciso, ho guadagnato, ho rubato, ma ti ho risarcito per tutti i danni. E questo non ti bastava. Tu, Chevalier, mi hai mandato in una missione suicida contro la corona per poter rafforzare ulteriormente il tuo potere personale! Il tuo tradimento esigeva una risposta. E l'hai ottenuta!";
			link.l2.go = "patria_prison_2";
			link.l3 = "Ambizione, Chevalier. In questo strano nuovo mondo, avevo già raggiunto quasi tutto ciò che potevo. La posizione di governatore generale mi sembrava un obiettivo degno di nota. Ho imparato molto da te. Addio!";
			link.l3.go = "patria_prison_2";
			link.l4 = "Non lo so nemmeno io, per essere sincero. Forse perché sono impressionato dal barone e dal suo fedele servizio al nostro paese? In ogni caso, ora avrai abbastanza tempo per pensare a questa questione per me. Addio!";
			link.l4.go = "patria_prison_2";
			// <-- legendary edition
		break;
		
		case "patria_prison_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			SetFunctionTimerCondition("Patria_EuropePuancieClear", 0, 0, 5, false); // таймер
			pchar.quest.Patria_Europe_final.win_condition.l1 = "location";
			pchar.quest.Patria_Europe_final.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Europe_final.function = "Patria_EuropeFinal";
		break;
		
		case "patria_patentfail":
			DialogExit();
			pchar.questTemp.Patria = "fail";
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_block");	// Разрешаем квест Дороже Золота
			// убрать Эклятон, если есть
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton"))
			{
				sld = characterFromId("Ecliaton_Cap");
				RemoveCharacterCompanion(pchar, sld);
				sld.lifeday = 0;
				DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
			}
		break;
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ1":
			SetTimerCondition("PZ_NormanBackToStreets", 0, 0, 1, false);	//Вовзращаем Акулу или Тиракса в Шарптаун
			// ставим сразу прерывание, чтобы потом по тысячу раз не копировать
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang") || CheckAttribute(pchar, "questTemp.PZ.LongwayTorero") || CheckAttribute(pchar, "questTemp.PZ.LongwayElCasador"))
				{
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition.l1 = "location";
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition.l1.location = "Charles_town";
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition = "PZ_AfterPoincyLongwayDialog";
				}
			}
			
			if (!CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva")) 
			{
				dialog.text = "Buono vederti, Charles. Ho sentito parlare delle tue imprese. Lavoro brillante!";
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Non è tutto, Vostra Eccellenza.";
					link.l1.go = "PZ2";
				}
				else
				{
					link.l1 = "Posso ottenere un ordine scritto da lei che mio fratello sarà rilasciato dalla custodia ora?";
					link.l1.go = "serve";
				}
			}
			else 
			{
				dialog.text = "Greetings, Charles. Come in; I've already been informed.";
				link.l1 = "Informato? Potrebbe esserci qualche errore, Vostra Eccellenza. Sono venuto a riferire il successo della vostra missione, ma vedo che non siete nel migliore degli umori.";
				link.l1.go = "PZ_PoincyAngry1";
			}
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube");
		break;
					
		case "PZ2":
			dialog.text = "Davvero? Cosa intendi, Capitano?";
			link.l1 = "Sono riuscito a catturare Levasseur vivo e a portarlo da te. Non appena abbiamo finito, ordinerò di portarlo da te.";
			link.l1.go = "PZ3";
		break;
		
		case "PZ3":
			dialog.text = "Non avrei mai pensato che qualcosa del genere fosse possibile! Davvero, un lavoro brillante, Charles! Dubito che anche tuo illustre fratello avrebbe potuto fare meglio. Tuo padre sarebbe orgoglioso di te, amico mio.";
			link.l1 = "Grazie per le tue gentili parole, Monsieur Philippe.";
			link.l1.go = "exit";
			npchar.greeting = "";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie");
		break;
		
		case "PZ5":
			dialog.text = "Molto bene, Charles. Sono contento di te.";
			link.l1 = "Posso ottenere un ordine scritto da te che mio fratello sarà rilasciato dalla custodia ora?";
			link.l1.go = "serve";
			LAi_SetHuberType(npchar);
		break;
		
		case "PZ_PoincyAngry1":
			dialog.text = "Forse avrei dovuto considerare che tu non sei tuo fratello - non un militare, non un agente segreto e non ancora esperto in operazioni delicate. Non avresti dovuto combattere apertamente con i soldati nelle strade di Tortuga. Ci saranno indagini, e anche su di me. Da persone serie, come capisci.";
			link.l1 = "Chiedo scusa, Cavaliere. Come capirai, Levasseur non avrebbe ceduto senza una lotta.";
			link.l1.go = "PZ_PoincyAngry2";
		break;
		
		case "PZ_PoincyAngry2":
			dialog.text = "Vero, ma... non importa. Non male per una prima operazione. Riporterò che ha attaccato il Revisore Reale e la sua scorta durante un'ispezione ufficiale.";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
			{
				link.l1 = "Vostra Eccellenza, se può essere d'aiuto, posso portarvi Levasseur. Io e i miei uomini abbiamo avuto la fortuna di catturarlo in un luogo isolato dopo che i suoi scagnozzi hanno cercato di arrestarci per strada.";
				link.l1.go = "PZ_PoincyAngry3";
			}
			else
			{
				link.l1 = "Posso ottenere un ordine scritto da te che mio fratello sarà rilasciato dalla custodia ora?";
				link.l1.go = "serve";
			}
		break;
				
		case "PZ_PoincyAngry3":
			dialog.text = "Cosa hai detto, Charles? Ripeti.";
			link.l1 = "François Levasseur è nella mia stiva in questo momento, pronto per essere consegnato a te, Monsieur Philippe.";
			link.l1.go = "PZ_PoincyAngry4";
		break;
		
		case "PZ_PoincyAngry4":
			dialog.text = "Dimentica tutto quello che ho detto prima. Ho decisamente esagerato. Lavoro brillante. Non sono sicuro che anche il tuo illustre fratello avrebbe potuto farcela.";
			link.l1 = "Grazie, Cavaliere.";
			link.l1.go = "PZ_PoincyAngry5";
		break;
		
		case "PZ_PoincyAngry5":
			dialog.text = "Hai un grande potenziale, amico mio. Vorrei che i tuoi talenti fossero utilizzati più spesso per il bene del paese. Ma per favore, cerca di essere più... discreto d'ora in poi. Il nostro lavoro richiede di solito un approccio delicato. Ah sì, e un'altra cosa.";
			link.l1 = "Sì, Vostra Signoria?";
			link.l1.go = "exit";
			npchar.greeting = "";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

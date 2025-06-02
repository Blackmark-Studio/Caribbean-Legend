// Абигайль Шнеур
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyInHouse")
				{
					dialog.text = "Buongiorno, signor mio. Cosa vi porta nella nostra dimora?";
					link.l1 = "Buongiorno, Abigail. Il mio nome è "+GetFullName(pchar)+" . Sono un capitano al servizio della Repubblica e della Compagnia Olandese delle Indie Occidentali.";
					link.l1.go = "AbbyAndLucas";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "Dio mio, hai trovato i soldi di mio padre? È vero? Ah, sono così felice! Corri da mio padre, vuole parlarti. Vai a trovarlo!";
					link.l1 = "Sto arrivando, madame.";
					link.l1.go = "exit";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyLeavesMarried")
				{
					dialog.text = "Ci avete salvato dalla più nera disperazione, capitano! Ve ne sono immensamente grato! Ora l’onore della famiglia Shneur potrà essere ristabilito!";
					link.l1 = "Non faccio che il mio dovere da gentiluomo, madame. Spero che ormai nulla vi trattenga più dallo sposare il mio protettore.";
					link.l1.go = "AbbyAndLucas_8";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Avete bisogno di qualcosa, capitano?";
				link.l1 = "Non adesso, madame.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "AbigileInChurch")
				{
					dialog.text = "Salve, Santa Regina, nostra vita, nostra dolcezza e nostra speranza. A Te ricorriamo, poveri figli di Eva esiliati. A Te sospiriamo, piangendo e gemendo in questa valle di lacrime... oh signore, mi avete fatto prendere uno spavento! Cosa vi porta qui?";
					link.l1 = "Mi scusi, Abigail, suppongo? Mi manda Richard Fleetwood...";
					link.l1.go = "Seek_Island";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Volete qualcosa, capitano?";
				link.l1 = "Non adesso, madame.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "Che succede qui? Cos’è tutto questo baccano? Papà, chi è questo strano individuo?";
					link.l1 = "Buongiorno, madame. Abigail Schneur, suppongo? Mi rallegra il vederla. Perdonate la mia sfrontatezza, vi prego, ma porto con urgenza una missiva indirizzata a voi da... eh, mi piacerebbe dirvelo, ma vostro caro padre non mi permette nemmeno di varcare la soglia, figuriamoci consegnarvi il messaggio.";
					link.l1.go = "Abigile_kidnapping";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDay")
				{
					dialog.text = "Ah, eccoti Charles. Son pronto a seguirti ovunque, capitano!";
					link.l1 = "Andiamo allora.";
					link.l1.go = "Abigile_kidnapping_7";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInCabin")
				{
					dialog.text = "Siamo già arrivati a St. John's, Charles? Rivedrò presto Richard?";
					link.l1 = "Sì, madame, siamo a St. John's. Purtroppo Richard non è in città al momento, due giorni fa gli è stato ordinato di pattugliare vicino a Barbados. Non vi preoccupate, dovrebbe tornare entro una settimana.";
					link.l1.go = "Abigile_kidnapping_8";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileLie")
				{
					dialog.text = "Charles! Che gioia vederti! Ci sono novità da Richard?";
					link.l1 = "Ahimè, mia cara madame. Richard ha dovuto trattenersi a Bridgetown per un po', impegnato in una missione segreta e di gran peso, qualcosa che riguarda gli olandesi. Immagino che Richard vi abbia già confidato di che mestiere si occupa, vero?";
					link.l1.go = "Abigile_kidnapping_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHome")
				{
					DelLandQuestMark(npchar);
					dialog.text = "Charles! Sei tu! Finalmente sei tornato!";
					link.l1 = "Salute, madama. Son lieto di vederla.";
					link.l1.go = "Abigile_return";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHomeGo")
				{
					dialog.text = "Ah, finalmente sono a casa! Che gioia rivedere papà! Charles, ti devo tutto quello che hai fatto per me!";
					link.l1 = "Per favore, non c'è bisogno di simili parole, madama. Non faccio che il mio dovere da gentiluomo verso una dama in difficoltà.";
					link.l1.go = "Abigile_return_6";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryNext")
				{
					dialog.text = "Papà, se ti ricordi qualcosa, ti prego, parla! Charles, lui... ci si può fidare di lui. Oso dire che è l’unico che possa aiutarci!";
					link.l1 = "";
					link.l1.go = "Abigile_return_12";
					pchar.questTemp.HWIC.Self = "SolomonHistoryAfter";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryEnd")
				{
					dialog.text = "Pregherò per te notte e giorno! Dimmi... dimmi che lo farai! Che troverai l'isola!";
					link.l1 = "Farò quel che posso, madama.";
					link.l1.go = "Abigile_return_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "final" || pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					DelLandQuestMark(npchar);
					dialog.text = "Ah, Charles! Sei tornato! Dimmi subito, hai trovato l’isola? Non riesco più a reggere quest’attesa!";
					if (makeint(Pchar.money) >= 200000)
					{
						link.l1 = "Sì, Abi. Ho trovato l’isola e il denaro di tuo padre. Sono qui per restituirtelo.";
						link.l1.go = "Abigile_GiveMoney";
					}
					link.l2 = "Ahimè, madame. Non sono riuscito a trovare né il capitano Keller né la vostra isola. Ho fatto il possibile, ma...";
					link.l2.go = "Abigile_NoMoney";
				break;
				}
				dialog.text = "Ah, sei tu, Charles! Hai bisogno di qualcosa? Posso offrirti un po' di caffè?";
				link.l1 = "No, niente. Non disturbarti, te ne prego.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Buongiorno, signore. Che c'è?";
			link.l1 = "Niente, madame. Chiedo umilmente perdono. Addio.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

//-------------------------------------------------за Голландию-----------------------------------------------
		case "AbbyAndLucas":
			dialog.text = "È un onore fare la vostra conoscenza, Capitano "+GetFullName(pchar)+"Ho sentito ogni sorta di storia su di te dalle altre signore della città. Sei l’uomo che ha catturato la nave fantasma dei pirati e l’ha portata come trofeo a Willemstad. Dimmi, capitano... è vero che questa nave era comandata da... Richard Fleetwood?";
			link.l1 = "Tutto ciò che avete sentito è vero, madama. Sono rimasto sconvolto quanto voi nel scoprire la verità. Uno scandalo! Un ufficiale di marina del Commonwealth inglese che depreda i mercanti della sua stessa nazione come un volgare filibustiere! Quel furfante ha cercato di mascherare le sue infamie fingendosi una nave fantasma rinnegata sotto la protezione della Compagnia Olandese delle Indie Occidentali. Usava questa copertura per gettare discredito sulla Compagnia e per assaltare anche i bastimenti olandesi.";
			link.l1.go = "AbbyAndLucas_1";
		break;
		
		case "AbbyAndLucas_1":
			dialog.text = "Mi gira la testa...  È difficile ascoltare simili orrori, capitano. Conoscevo Richard Fleetwood di persona, mai avrei immaginato che lui...";
			link.l1 = "Madame, il mio protettore Lucas Rodenburg mi ha messo al corrente del vostro viaggio da Recife a Curaçao. Ora tutto torna. Fleetwood ha affondato la vostra nave, poi s’è presentato da eroe per 'salvare' voi e vostro padre da quell’isola dimenticata da Dio. Ho letto io stesso il diario di quel filibustiere, ogni maledetto dettaglio annotato nel suo registro.";
			link.l1.go = "AbbyAndLucas_2";
		break;
		
		case "AbbyAndLucas_2":
			dialog.text = "Che incubo... Pare proprio che il mio papà avesse ragione. Continuava a dirmi che Richard era quel filibustiere responsabile di tutte le nostre disgrazie. Dovrei gioire che la verità sia venuta a galla... ah, perdonatemi, capitano. È solo che la mia povera testa fatica a raccapezzarsi con tutto ciò... ditemi, cosa può volere una persona tanto importante come voi da una semplice fanciulla come me?";
			link.l1 = "Abigail, sono giunto per una faccenda assai intricata e delicata. Mi porgerai orecchio?";
			link.l1.go = "AbbyAndLucas_3";
		break;
		
		case "AbbyAndLucas_3":
			dialog.text = "Ma certo, signor mio. Sono tutto orecchi.";
			link.l1 = "Come vi ho già detto, sono al servizio della Compagnia. Lucas Rodenburg non è soltanto il mio comandante militare, ma anche un caro amico. Mi ha mandato da voi con un messaggio. Nulla lo renderebbe più felice che il vostro consenso alla sua proposta di matrimonio. Son qui a chiedervi di sposare il mio protettore: egli farebbe qualunque cosa al mondo per la vostra felicità.";
			link.l1.go = "AbbyAndLucas_4";
		break;
		
		case "AbbyAndLucas_4":
			dialog.text = "Oh, capitano! Ora capisco perché il signor Rodenburg non voleva occuparsene di persona... Mio povero papà sarebbe al settimo cielo, ma io...";
			link.l1 = "Madame, vedo che qualcosa la turba. Dubita forse della sincerità di Mynheer Rodenburg? Forse potrei aiutarla a cambiare idea?";
			link.l1.go = "AbbyAndLucas_5";
		break;
		
		case "AbbyAndLucas_5":
			dialog.text = "Oh no capitano, non metto certo in dubbio la sincerità del signor Rodenburg. Lucas ha fatto tanto per me e mio padre, non oso immaginare cosa sarebbe di noi senza la sua protezione. Ma vi scongiuro, dovete capire la mia posizione!\nLa mia famiglia non è certo quella dei Rothschild, ma non siamo mai stati poveri. Gli Shneur sono ben noti tra le case bancarie d’Europa per la nostra fortuna... e ora quella dannata canaglia di pirata ci ha rovinati! Non sopporto più queste malelingue che so serpeggiano alle nostre spalle. Ogni pettegola e servetta della città pensa che io voglia solo i soldi del signor Rodenburg. ‘Proprio come una giudea’, dicono. Maledette vipere! Se solo mio padre ricordasse dov’è quell’isola! Ha nascosto lì quel che resta della nostra fortuna per salvarla dalle grinfie di quei pirati malvagi che uccisero le mie sorelle e mio fratello!\nMa il povero papà non è un marinaio, proprio non riesce a ricordare dove sia quell’isola né i nostri soldi! Vi prego, parlate con mio padre, capitano! Forse può ricordare qualcosa che ai vostri occhi esperti sarà utile. Vi supplico, trovate quell’isola e la nostra fortuna! Salverete una povera ragazza dalla vergogna e dall’infamia!";
			link.l1 = "Va bene, Abigail. Parlerò con tuo padre. Abbi fede, ragazza, farò il possibile.";
			link.l1.go = "AbbyAndLucas_6";
		break;
		
		case "AbbyAndLucas_6":
			dialog.text = "Grazie, signor mio. Pregherò per voi notte e dì. Che il Dio dei nostri padri vi accompagni!";
			link.l1 = "Addio, Abigail. Tornerò con buone nuove, te lo giuro.";
			link.l1.go = "AbbyAndLucas_7";
		break;
		
		case "AbbyAndLucas_7":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-27");
			pchar.questTemp.HWIC.Holl = "AbbyFather";
			AddLandQuestMark(characterFromId("Solomon"), "questmarkmain");
		break;
		
		case "AbbyAndLucas_8":
			dialog.text = "Oh, sì! Il signor Rodenburg è un uomo d’onore e di buon cuore. Gli darò il mio consenso senza alcun indugio, e sarò lieta di chiamarlo mio marito.";
			link.l1 = "Allora considero la mia missione compiuta. Devo andare subito dal signor Rodenburg e portargli la lieta novella. Vi auguro sinceramente ogni felicità, madame.";
			link.l1.go = "AbbyAndLucas_9";
		break;
		
		case "AbbyAndLucas_9":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-33");
			pchar.questTemp.HWIC.Holl = "AbbyAgreeMarried";//теперь к Лукасу
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
		break;
		
//-------------------------------------------------за Англию-----------------------------------------
		case "Seek_Island":
			dialog.text = "Richard ti ha mandato?! Santa Maria benedetta, grazie! Ah, signore! Ho sentito dire che il povero Richard è stato ferito ed era in fin di vita. È vero? Dimmi, è ancora vivo?! Sta bene?!";
			link.l1 = "Richard è vivo e... tutto sommato in salute. Ora, le cattive notizie: è un po’ malconcio e ci vede poco, ma si sta rimettendo. Per le buone: Richard vuole che tu prenda il largo con lui per l’Inghilterra, dove vi sposerete. Il suo tempo nei Caraibi è finito, e sta aspettando la tua risposta.";
			link.l1.go = "Seek_Island_1";
		break;
		
		case "Seek_Island_1":
			dialog.text = "Ah, mio caro messaggero, di’ a Richard che per la nostra felicità sono pronta a seguirlo ovunque voglia. Ma temo che la nostra fuga spezzerà il cuore al mio povero padre... Signore, sono disperata e non so che fare. Vorrei che Richard riuscisse a trovare quell’isola maledetta e il baule con l’oro della nostra famiglia... Forse questo darebbe un po’ di conforto al mio papà durante la mia assenza.";
			link.l1 = "Capisco... Il mio incarico era portarti ad Antigua, ma la faccenda si fa più spinosa. Se dovessi trovare l’isola e lo scrigno e portarli a te, verresti infine con me a St. John's da Richard?";
			link.l1.go = "Seek_Island_2";
		break;
		
		case "Seek_Island_2":
			dialog.text = "Oh sì, signore, vi ricorderò nelle preghiere della nostra famiglia! Chiamerò il nostro primogenito col vostro nome! Grazie di cuore, capitano! Pregherò per voi! Andate, che Cristo e la Beata Madre vi accompagnino!";
			link.l1 = "Non vi farò attendere troppo a lungo, madame. Tornerò presto.";
			link.l1.go = "Seek_Island_3";
		break;
		
		case "Seek_Island_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-18");
			pchar.questTemp.HWIC.Eng = "SeekIsland";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Villemstad_houseSp2_bedroom", "goto", "goto1", "", -1);//Аби домой
			pchar.questTemp.HWIC_Coordinates = "true"; //атрибут координат на поиск острова через каюту
			DelMapQuestMarkCity("Villemstad");
		break;
		
//--------------------------------------------против всех------------------------------------------------
		case "Abigile_kidnapping":
			dialog.text = "Oh... Avete una lettera da lui? Oh papà, non siate così severo con i nostri ospiti! Mi mettete in imbarazzo con le vostre fantasie paranoiche! Signore, vi prego, seguitemi, desidero parlarvi.";
			link.l1 = "Grazie, signorina. Fa piacere vedere che almeno qui qualcuno ragiona.";
			link.l1.go = "Abigile_kidnapping_1";
		break;
		
		case "Abigile_kidnapping_1":
			DialogExit();
			npchar.greeting = "abigile_3";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "Abigile_Stay", -1);
			NextDiag.CurrentNode = "Abigile_kidnapping_2";
			pchar.questTemp.HWIC.Self = "AbigileTalk";
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "Abigile_kidnapping_2":
			DelLandQuestMark(npchar);
			dialog.text = "Perdona mio padre, signor mio. In verità è un uomo buono e gentile, ma le nostre... sventure l’hanno spezzato.";
			link.l1 = "Va bene, madama, capisco. Permettetemi di presentarmi, sono Charlie... Knippel. Sono qui per ordine di Richard Fleetwood, vuole che vi conduca da lui. Ecco, prego, leggete la lettera.";
			link.l1.go = "Abigile_kidnapping_3";
		break;
		
		case "Abigile_kidnapping_3":
			RemoveItems(PChar, "NPC_Letter", 1);
			dialog.text = "Oh Richard... (leggendo). Oh, Dio! Ha deciso... di restituire a mio padre tutti i suoi soldi perduti! Che generosità! Caro, dolce Richard! Signore, portate notizie come l’arcangelo Gabriele in persona! Richard, dov’è lui? È forse a Curaçao?";
			link.l1 = "No, signorina. Hanno attentato alla sua vita ed è stato gravemente ferito. Ora si trova ad Antigua... non hai finito di leggere la lettera.";
			link.l1.go = "Abigile_kidnapping_4";
		break;
		
		case "Abigile_kidnapping_4":
			dialog.text = "Santa Maria concepita senza peccato, prega per noi che ricorriamo a te! Dimmi, è al sicuro? La sua ferita è grave?";
			link.l1 = "Non vi tormentate così, signorina! Richard non è certo il tipo d’uomo che si lascerebbe far fuori da quattro canaglie senza reagire. Ora si sta riprendendo, è al sicuro. Vuole che vi conduca da lui. Poi ve ne andrete insieme a Londra... vi prego, concludete la lettera, signorina, non correte troppo avanti.";
			link.l1.go = "Abigile_kidnapping_5";
		break;
		
		case "Abigile_kidnapping_5":
			dialog.text = "Ah, sì...Scusatemi (leggendo). Monsieur Knippel, sono pronto a salpare con voi. Mi serve solo un giorno per mettere insieme le mie cose e parlare con mio padre. Tornate domani e verrò con voi.";
			link.l1 = "D'accordo, signora. Domani sarò qui. Non tema, io e la mia ciurma veglieremo su di lei contro qualsiasi pericolo durante il viaggio.";
			link.l1.go = "Abigile_kidnapping_6";
		break;
		
		case "Abigile_kidnapping_6":
			DialogExit();
			npchar.greeting = "abigile_2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Holl_Gambit", "3-22");
			pchar.quest.Abigile_Kidnap.win_condition.l1 = "Timer";
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.hour  = 7.0;
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l2 = "location";
			pchar.quest.Abigile_Kidnap.win_condition.l2.location = "Villemstad_houseSp2";
			pchar.quest.Abigile_Kidnap.function = "AbigileGoToShip";
			pchar.questTemp.HWIC.Self = "AbigileWaitNextDay";
			SetFunctionTimerCondition("AbigileGoToShipOver", 0, 0, 3, false);//таймер 3 дня, ибо нефиг
		break;
		
		case "Abigile_kidnapping_7":
			DialogExit();
			chrDisableReloadToLocation = true;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SetAbigileToCabin", -1);//Аби в каюту к ГГ поставим
			AddQuestRecord("Holl_Gambit", "3-23");
			pchar.questTemp.HWIC.Self = "AbigileOnShip";
			pchar.quest.AbigileGoToShipOver.over = "yes";//снять таймер
			SetFunctionTimerCondition("RemoveAbigileOver", 0, 0, 30, false);//таймер на 1 месяц, ибо нефиг
			pchar.quest.Abigile_died.win_condition.l1 = "NPC_Death";
			pchar.quest.Abigile_died.win_condition.l1.character = "Abigile";
			pchar.quest.Abigile_died.function = "AbigileDied";//специально для особо упоротых
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_8":
			DelLandQuestMark(npchar);
			dialog.text = "Ah, che peccato. Ma credo che posso aspettare ancora una settimana, come ho già fatto finora...";
			link.l1 = "Ben detto, signorina. E per rendere l'attesa meno gravosa, vi propongo di scambiare questa cabina austera con la casa del mio amico. Lì vi attenderà un letto soffice e cibo squisito preparato per voi.";
			link.l1.go = "Abigile_kidnapping_9";
		break;
		
		case "Abigile_kidnapping_9":
			dialog.text = "Sei proprio un gentiluomo, Charlie. Grazie. Sarà un sollievo sentire la terra sotto i piedi... Dopo tutto questo dondolio tra le onde, mi gira la testa.";
			link.l1 = "Seguimi, prego, signorina.";
			link.l1.go = "Abigile_kidnapping_10";
		break;
		
		case "Abigile_kidnapping_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.questTemp.HWIC.Self = "AbigileInHouse";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_11":
			dialog.text = "Son lieto d’incontrarti, John. Vi ringrazio per la vostra ospitalità, signori!";
			link.l1 = "...";
			link.l1.go = "Abigile_kidnapping_12";
		break;
		
		case "Abigile_kidnapping_12":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "SentJons_HouseF3_Room2", "barmen", "bar1", "ContinueWithMerdok", -1);
			pchar.questTemp.HWIC.Self = "AbigileInRoom";
			NextDiag.CurrentNode = "First time";
			RemovePassenger(Pchar, npchar);
			pchar.quest.RemoveAbigileOver.over = "yes";//снять таймер
			sld = characterFromId("Merdok");
			LAi_SetActorType(sld);//чтобы геймер сам с ним не заговорил
		break;
		
		case "Abigile_kidnapping_13":
			DelLandQuestMark(npchar);
			dialog.text = "Oh Charlie, ho visto Richard solo un paio di volte e non mi ha mai raccontato granché di quello che combina.";
			link.l1 = "Mi sorprende davvero che abbia nascosto un segreto così grande alla donna che ama... Signorina, Richard non è un semplice capitano. È anche un agente speciale del Consiglio Privato d’Inghilterra. Un uomo assai importante che si occupa di incarichi delicati, ordinati direttamente dal Lord Protettore in persona. Al momento, il suo compito è di spezzare il potere commerciale della Compagnia Olandese delle Indie Occidentali nei Caraibi.";
			link.l1.go = "Abigile_kidnapping_14"
		break;
		
		case "Abigile_kidnapping_14":
			dialog.text = "Signore, ma di che andate cianciando?";
			link.l1 = "Sì, signorina. Il vostro amato Richard – mio amico – è un uomo di grande importanza. Sono sempre stato fiero della nostra amicizia, ma ultimamente è divenuto assai riservato perfino con me. È palese che sia coinvolto in qualche incarico segreto. Mi dispiace sinceramente che questa missione gli impedisca d’incontrarvi.";
			link.l1.go = "Abigile_kidnapping_15";
		break;
		
		case "Abigile_kidnapping_15":
			dialog.text = "Charlie, mi stai facendo venire i brividi. Sei sicuro che stia bene?";
			link.l1 = "Ne sono certo. È solo che... non approvo il modo in cui ti tratta adesso. Capisco che il suo incarico sia vitale e che non possa venir meno al dovere, nemmeno per te.";
			link.l1.go = "Abigile_kidnapping_16";
		break;
		
		case "Abigile_kidnapping_16":
			dialog.text = "Oh, mio caro Charlie... Attenderò Richard anche fino al Giudizio Universale, se dovesse servire. Forse potrei restare sopra la taverna... Non posso continuare a abusare dell’ospitalità di John per così tanto tempo.";
			link.l1 = "Smettila di dire sciocchezze, madamigella! La vostra presenza ci onora e non mi chiamo certo Charlie il Knippel se scaccio la promessa sposa della mia cara amica Richard Fleetwood dalla sua stessa casa!";
			link.l1.go = "Abigile_kidnapping_17";
		break;
		
		case "Abigile_kidnapping_17":
			dialog.text = "Charlie... Sono profondamente commossa dal tuo modo di trattarmi. Non sono che una semplice fanciulla, e per di più ebrea...";
			link.l1 = "Signorina! So che son parole da sconsiderato, siete una giovane cristiana di tutto rispetto! E non vi venga manco in mente di metter piede in una taverna! Non mi perdonerei mai se fallissi nel mio dovere verso Richard.";
			link.l1.go = "Abigile_kidnapping_18";
		break;
		
		case "Abigile_kidnapping_18":
			dialog.text = "Grazie, Charlie. Son lieto ch’ tu sia un... brav’uomo.";
			link.l1 = "È mio dovere, signorina. Ora vi chiedo scusa, ma devo andare. Potete girare liberamente per la città adesso, immagino vi sentiate sola rinchiusa in questa casa, sbaglio?";
			link.l1.go = "Abigile_kidnapping_19";
		break;
		
		case "Abigile_kidnapping_19":
			dialog.text = "Ebbene... John è una compagnia davvero interessante. Può parlare per ore delle sue polveri, pozioni e di ogni sorta di... malanno. È anche un uomo cortese e raffinato. E poi, vado spesso in chiesa: il prete locale è assai gentile... ma, ovviamente, Richard mi manca terribilmente.";
			link.l1 = "Penso che tornerà presto. Charlie il Knippel è al vostro servizio, se avete bisogno di qualcosa.";
			link.l1.go = "Abigile_kidnapping_20";
		break;
		
		case "Abigile_kidnapping_20":
			DialogExit();
			pchar.questTemp.HWIC.Self = "MeetTonzag";
			pchar.quest.Meet_Tonzag.win_condition.l1 = "location";
			pchar.quest.Meet_Tonzag.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Meet_Tonzag.function = "TonzagMeetingInDange";
		break;
		
		case "Abigile_return":
			dialog.text = "Ho sentito delle voci su Richard... pare sia sparito. Ne sai qualcosa, Charlie?";
			link.l1 = "Lo so, Abigail. Mi dispiace... Richard Fleetwood è tornato in Inghilterra e non farà più ritorno. Ha avuto una promozione, o forse un trasferimento... insomma, dopo ciò che ti ha fatto, non voglio più averci a che fare.";
			link.l1.go = "Abigile_return_1";
		break;
		
		case "Abigile_return_1":
			dialog.text = "Ah, lo sapevo che sarebbe finita così... (singhiozza) Perché non ho dato retta a papà! Almeno sarebbe stato felice se avessi sposato Lucas Rodenburg.";
			link.l1 = "Perdonami ancora, madamigella...";
			link.l1.go = "Abigile_return_2";
		break;
		
		case "Abigile_return_2":
			dialog.text = "Perché mai, Charlie? Non hai alcuna colpa. Sei sempre stato gentile con me!";
			link.l1 = "Per me è dura darti ancora cattive notizie. Sono appena tornato da Curaçao: Lucas Rodenburg è stato arrestato per sedizione e tradimento contro la Repubblica. Lo stanno spedendo incatenato ad Amsterdam per essere processato. Ha tentato di assassinare Peter Stuyvesant, il direttore della Compagnia. Non solo: voleva rovesciare il governatore di Willemstad ed è sospettato d’aver ammazzato almeno un altro cristiano, quindi dubito che lo Stadtholder si limiterà a una pacca sulla spalla.";
			link.l1.go = "Abigile_return_3";
		break;
		
		case "Abigile_return_3":
			dialog.text = "Oh Dio! Che incubo! Mi sento svenire! Charles, è vero? No, ti prego, dimmi che non è così!";
			link.l1 = "Mi dispiace, signorina, ma la situazione è ancor più grave. Durante l’indagine sulle azioni di Rodenburg si è scoperto che il pirata che ha affondato il vostro fluyt agiva su ordine diretto di Lucas Rodenburg. Stava conducendo una sua guerra privata contro le navi inglesi. Mi rincresce davvero, Abigail. Tutti gli uomini che avete incontrato qui nei Caraibi sono stati bugiardi, ladri o assassini.";
			link.l1.go = "Abigile_return_4";
		break;
		
		case "Abigile_return_4":
			dialog.text = "Oh... Sono rovinata. Charles... ti prego... portami a casa, a Willemstad. Ho bisogno del mio papà...";
			link.l1 = "Ma certo, mia cara. Sfortunatamente qui a Bridgetown non c’è nulla per voi. Su, fate le valigie, salutate John e salpiamo senza indugio.";
			link.l1.go = "Abigile_return_5";
		break;
		
		case "Abigile_return_5":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-57");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);//откроем комнату Аби
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.HWIC.Self = "AbiReturnHomeGo";
			pchar.quest.AbiReturn_Home.win_condition.l1 = "location";
			pchar.quest.AbiReturn_Home.win_condition.l1.location = "Villemstad_town";
			pchar.quest.AbiReturn_Home.function = "AbiGoInVillemstad";
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		case "Abigile_return_6":
			dialog.text = "No, Charlie, sono io che ti devo ringraziare. Se non fosse stato per te e John, non so nemmeno cosa ne sarebbe stato di me. Siete gli unici uomini onesti che abbia incontrato su questo maledetto arcipelago.";
			link.l1 = "Hm... mi fai arrossire, Abigail. Sono stato lieto di darti una mano. E ti chiedo davvero perdono per tutto questo pasticcio.";
			link.l1.go = "Abigile_return_7";
		break;
		
		case "Abigile_return_7":
			dialog.text = "Sai, Charlie, ho riflettuto molto durante il nostro viaggio verso Curaçao. Ora tutto è chiaro – Richard Fleetwood, il signor Rodenburg – tutto pare solo un incubo orrendo finalmente svanito. Sono di nuovo con mio padre e possiamo tornare a una vita normale.\nNon sarà facile però – siamo senza un soldo. Ma ce la faremo, andrà tutto bene. La Santa Madre veglierà su di noi, non dimentica mai i suoi figli, nemmeno il mio vecchio padre testardo che rinnega Suo Figlio.";
			link.l1 = "Signorina Abigail, vengo in vostro aiuto.";
			link.l1.go = "Abigile_return_8";
		break;
		
		case "Abigile_return_8":
			dialog.text = "Aiutarci? Ma come, Charlie?";
			link.l1 = "Richard mi ha raccontato della tua naufragio e di come ti hanno salvato. E so anche che tuo padre è riuscito a nascondere i suoi averi su un’isola fuori da ogni rotta. Andrò a cercarla e ti riporterò il tuo denaro.";
			link.l1.go = "Abigile_return_9";
		break;
		
		case "Abigile_return_9":
			dialog.text = "Oh Charlie... Né io né mio padre possiamo dirti dove si trovi quell’isola maledetta... Non siamo marinai. Inoltre, durante l’attacco ero talmente terrorizzato per la mia vita che non ricordo altro che sangue e l’odore della morte.";
			link.l1 = "Abigail, cerca di ricordare. Ti prego, ogni dettaglio può aiutarmi, anche il più piccolo. Forse è successo qualcosa prima dell’attacco? Com’è fatta quest’isola?";
			link.l1.go = "Abigile_return_10";
		break;
		
		case "Abigile_return_10":
			dialog.text = "Isola... Pareva proprio un’isola, sì? Una baia, giungle. Nulla che mi sia rimasto impresso, davvero. Ah, aspetta! Questo forse ti torna utile. Poco prima che i filibustieri ci assaltassero, incrociammo un fluyt e chiamammo a bordo il suo capitano. Venne da noi e cenò col nostro comandante. Eravamo tutti presenti. Magari lui sa qualcosa di quest’isola.";
			link.l1 = "Questa sì che è una notizia! Come si chiamavano il fluyt e il suo capitano?";
			link.l1.go = "Abigile_return_11";
		break;
		
		case "Abigile_return_11":
			dialog.text = "Non ricordo, Charlie. Davvero non ricordo...";
			link.l1 = "Cerca di ricordare, Abi!";
			link.l1.go = "Abigile_return_12";
			pchar.questTemp.HWIC.Self = "SolomonHistory";
		break;
		
		case "Abigile_return_12":
			DialogExit();
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_return_13":
			dialog.text = "Ti aspetteremo. Aiutaci, Charlie il Knippel. Sei la nostra unica speranza... Pregherò per te! Che Dio ti assista!";
			link.l1 = "Sto per partire. Addio, Abi. Addio, Solomon.";
			link.l1.go = "Abigile_return_14";
		break;
		
		case "Abigile_return_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "ReturnAbiNormal", -1);
			pchar.questTemp.HWIC.Self = "SeekFleut";
			AddQuestRecord("Holl_Gambit", "3-58");
			AddLandQuestMark(characterFromId("Villemstad_PortMan"), "questmarkmain");
		break;
		
		case "Abigile_NoMoney":
			dialog.text = "Oh, mio caro... che peccato. Avevamo sperato, ma... grazie comunque, Charlie, per aver tentato d'aiutarci quando nessun altro lo avrebbe fatto. Pare proprio che questo sia il destino che il buon Dio ha preparato per me.";
			link.l1 = "Addio, Abigail. Spero che tutto vada per il meglio per te.";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Abigile_Poor";
		break;
		
		case "Abigile_GiveMoney":
			dialog.text = "È... è vero? Hai davvero riportato a casa i nostri soldi perduti? Oh, Charlie!";
			link.l1 = "Sì, è vero. Ce l'ho io. Tieni, prendi pure. È tutto tuo.";
			link.l1.go = "Abigile_GiveMoney_1";
		break;
		
		case "Abigile_GiveMoney_1":
			AddMoneyToCharacter(pchar, -200000);
			pchar.quest.MakeAbiPoor.over = "yes"; //снять прерывание
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			dialog.text = "Come posso ringraziarti?! Come?!";
			link.l1 = "Non c’è bisogno di ringraziamenti, Abi. Era il minimo che potessi fare per te. Ora puoi cominciare una nuova vita, senza Rodenburg, Fleetwood o altri furfanti che cerchino di approfittarsi di te. Sono certo che tuo padre saprà far fruttare questi soldi… pare che sia una dote di famiglia.";
			link.l1.go = "Abigile_GiveMoney_2";
		break;
		
		case "Abigile_GiveMoney_2":
			dialog.text = "Charlie, non essere così sfrontato! Hai fatto così tanto per me, per me e per il mio povero padre. Ormai mi sono abituata alla tua presenza nella mia vita. Ogni giorno prego senza sosta per te, e continuerò a pregare per te e per la tua ciurma davanti alla Beata Madre, ogni giorno che verrà! Sei il nostro angelo custode. È stato il Signore stesso a mandarti alla nostra famiglia, che tu ci creda o no\nPrima che tu parta, voglio che tu sappia che le porte di casa nostra saranno sempre spalancate per te, in qualsiasi momento. E... ti prego, lasciami darti un bacio, mio caro Charlie...";
			link.l1 = "Beh... sì, certo Abi... se proprio insisti.";
			link.l1.go = "Abigile_GiveMoney_3";
		break;
		
		case "Abigile_GiveMoney_3":
			DialogExit();
			npchar.greeting = "abigile_1";
			npchar.dialog.currentnode = "Abigile_AllRight";
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("AbiKiss", "");
		break;
		
		case "Abigile_Poor":
			dialog.text = "Dio ti benedica, Charles. Per noi nulla è cambiato... Mendico ancora per due briciole davanti alla chiesa.";
			link.l1 = "Coraggio, signorina. Che Dio vi protegga.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_Poor";
		break;
		
		case "Abigile_AllRight":
			dialog.text = "Charles, sei proprio tu! Che gioia rivederti! Siediti, ti prego! Ti preparo subito un caffè!";
			link.l1 = "Son lieto di vederti anch’io, Abi. E mi rincuora sapere che te la passi bene.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_AllRight";
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Woman_FackYou":
			dialog.text = "Ah, dunque è così?! Ti ho accolto come ospite e tu hai deciso di derubarmi?! Guardie!!!";
			link.l1 = "Taci, sciocca ragazza.";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}

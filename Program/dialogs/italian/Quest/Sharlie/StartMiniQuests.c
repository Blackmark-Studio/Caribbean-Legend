void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Cosa vuoi, eh?";
			link.l1 = "Niente per ora.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//Найти помощника в магазин
		case "Storehelper":
			DelLandQuestMark(npchar);
			dialog.text = "C’è qualcosa di cui avete bisogno, monsieur?";
			link.l1 = "Tu sei Gralam Lavoie, giusto?";
			link.l1.go = "Storehelper_1";
		break;
		
		case "Storehelper_1":
			dialog.text = "Chi lo chiede? Non disturbarmi mentre bevo il mio rum, signore. Non sono dell’umore per far conversazione.";
			link.l1 = "Non ti ruberò molto tempo. Sono stato mandato qui da un mercante di Saint-Pierre. Dicevi di lavorare per lui un tempo. Ti sta cercando e...";
			link.l1.go = "Storehelper_2";
		break;
		
		case "Storehelper_2":
			dialog.text = "Ah, mi sta cercando!? Che buffonata da parte di quel taccagno maledetto! Davvero pensava che avrei sprecato tutta la mia vita a sgobbare per quattro soldi? È l’avaro più infame di tutti i Caraibi! Ho sgobbato per lui cinque anni, e mai che mi abbia dato un soldo in più del necessario! Nemmeno abbastanza per una sorsata di rum!\nAdesso si conti pure la sua mercanzia da solo, io ho chiuso. Nessuno a Saint-Pierre lavorerà mai più per quell’avido pezzente, puoi giurarci. Non pensa ad altro che a riempirsi le tasche e pagare gli altri sempre meno.";
			link.l1 = "Immagino che tu non abbia intenzione di tornare a servire quel bastardo?";
			link.l1.go = "Storehelper_3";
		break;
		
		case "Storehelper_3":
			dialog.text = "No, che il Signore mi fulmini se mento! Resto qui a Le Francois ad aspettare qualche nave, magari mi prendono come commissario di bordo. E se nemmeno quello, allora mi riduco a vivere come un semplice marinaio. Non posso nemmeno sopportare la vista di quell’avido strozzino. Se devo fare la fame, almeno che sia da uomo libero...";
			link.l1 = "Capisco, è tutto ciò che mi serviva sapere. Buona fortuna, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_4":
			DelLandQuestMark(npchar);
			dialog.text = "Messere, scansatevi. State intralciando il mio cammino!";
			link.l1 = "Solo una domanda, monsieur. Siete voi Gralam Lavoie?";
			link.l1.go = "Storehelper_5";
		break;
		
		case "Storehelper_5":
			dialog.text = "Ah! Sì, son proprio io. Che diavolo vuoi?";
			link.l1 = "Ti sta cercando un mercante di Saint-Pierre. Lavoravi per lui, vero?";
			link.l1.go = "Storehelper_6";
		break;
		
		case "Storehelper_6":
			dialog.text = "Ah-ah! Che burla! E cosa mai vorrà da me sua maestà reale? Ha forse deciso di pagarmi il salario che mi deve per le ultime due settimane? Oppure ha difficoltà a contare i suoi barili mentre raggira i clienti, eh? Ah-ah-ah!";
			link.l1 = "Mi ha chiesto di venirti a cercare e chiarire perché non ti fai più vedere al suo negozio a lavorare.";
			link.l1.go = "Storehelper_7";
		break;
		
		case "Storehelper_7":
			dialog.text = "Perché? Perché è un dannato tirchio e un padrone d’inferno! Ormai faccio parte della Fratellanza della Costa, sono un uomo libero e schiavo mai più! Guarda qui intorno, mi sto proprio godendo la vita!\nPresto salperò e conterò pesos e dobloni strappati agli spagnoli invece che casse di banane! E quanto a quel braccino corto – dubito che troverà uno che lo rimpiazzi. Nessuno a Saint-Pierre è così fesso da lavorare per lui, abbiamo sparso la voce tra tutti gli apprendisti dell’isola, ah-ah!";
			link.l1 = "Ho capito. Era tutto ciò che volevo sapere. Buona fortuna, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_8":
			DelLandQuestMark(npchar);
			dialog.text = "In che modo posso esserti utile?";
			link.l1 = "Buon pomeriggio. Gralam Lavoie, suppongo?";
			link.l1.go = "Storehelper_9";
		break;
		
		case "Storehelper_9":
			dialog.text = "Sì. Cosa desiderate, monsieur?";
			link.l1 = "Ti cerca un mercante di Saint-Pierre. Lavoravi per lui, vero?";
			link.l1.go = "Storehelper_10";
		break;
		
		case "Storehelper_10":
			dialog.text = "Ebbene, che continui pure a cercare. Non gli devo proprio nulla. Lui mi deve ancora due settimane di paga, ma non ho neanche voglia di andare a riscuoterla. Che si strozi pure con i suoi spiccioli.";
			link.l1 = "Hm. Quindi l’hai davvero lasciato per sempre, a quanto pare?";
			link.l1.go = "Storehelper_11";
		break;
		
		case "Storehelper_11":
			dialog.text = "Hai capito tutto, messeruzzo. Il mio ex-padrone è un usuraio di quelli rari, roba da far impallidire le scritture. Ormai sono Fratello della Costa e i miei talenti sono apprezzati tra i nuovi compagni. Prendo il doppio, più le mance.\nDubito che il nostro caro amico troverà uno che mi rimpiazzi. La sua tirchieria è leggenda a Saint-Pierre, nessuno là è tanto scemo da farsi sfruttare da lui.";
			link.l1 = "Ho capito. Era tutto ciò che mi serviva sapere. Buona fortuna, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_12":
			DialogExit();
			npchar.lifeday = 0;
			AddQuestRecord("SharlieA", "2");
			pchar.questTemp.Sharlie.Storehelper = "return";
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.StorehelperOver.over = "yes"; //снять таймер
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload6_back");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload3_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload1_back");
		break;
		
		case "Newstorehelper_1":
			dialog.text = "Salve, monsieur. Non vorrei sembrare troppo sfacciato, ma credo proprio che la mia candidatura calzi a pennello per la posizione che offrite.";
			link.l1 = "Buon pomeriggio. E perché mai lo pensi?";
			link.l1.go = "Newstorehelper_1_1";
		break;
		
		case "Newstorehelper_2":
			dialog.text = "Salve, messere! Permettetemi di raccontarvi qualcosa su di me.";
			link.l1 = "Sono tutto orecchi.";
			link.l1.go = "Newstorehelper_2_1";
		break;
		
		case "Newstorehelper_3":
			dialog.text = "Salute a voi, caro signore. Offrite forse un posto da mercante?";
			link.l1 = "Sì, sono io. E tu, chi sei di grazia?";
			link.l1.go = "Newstorehelper_3_1";
		break;
		
		case "Newstorehelper_1_1":
			dialog.text = "Ho servito come nostromo sotto il comando del capitano Francis Dubois in persona. Era assai soddisfatto delle mie capacità, ma fui ferito in battaglia e dovetti prendermi congedo per curarmi. Ora sto bene, in perfetta salute, ma il solo pensiero delle onde mi fa venir la nausea. No, ora desidero soltanto restare su terra ferma. \n(sussurrando) E se sceglierai me, ti pagherò cinquecento pesos e venticinque dobloni d’oro in più.";
			link.l1 = "Capisco. Ci rifletterò su.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_1":
			dialog.text = "Facevo il mercante ambulante, ma ho dovuto darmi alla fuga per certi debiti e così sono finito in mare come tesoriere su una nave mercantile. Il destino m’ha portato in questo villaggio. In verità, la vita da marinaio non mi andava poi tanto, e accetterei volentieri la tua proposta. \n (sottovoce) E se scegli me, ti darò non solo cinquecento pesos, ma anche questo pacco pesante d’ambra.";
			link.l1 = "Capisco. Ci rifletterò su.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_1":
			dialog.text = "Ero un impiegato in uno dei magazzini portuali di Glasgow. Son venuto ai Caraibi in cerca di fortuna, e son riuscito a guadagnare abbastanza per godermi la vecchiaia con decoro. Ma mi son stufato delle traversate e vorrei vivere tranquillo sulla terraferma. \n (sussurrando) E se scegli me, t’offro cinquecento pesos più altri duemilacinquecento come incentivo.";
			link.l1 = "Capisco. Ci rifletterò su.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_2":
			dialog.text = "Monsieur, fa' la scelta giusta. E non scordarti dei dobloni...";
			link.l1 = "Ho preso una decisione a tuo favore. Raccogli le tue cose. Si va a Saint-Pierre.";
			link.l1.go = "Newstorehelper_1_3";
			link.l2 = "Non ho ancora preso una decisione...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_2":
			dialog.text = "Spero che sceglierai me, monsieur. E l’ambra è pure una roba assai preziosa e utile...";
			link.l1 = "Ho deciso in tuo favore. Rimettiti in sesto. Andiamo a Saint-Pierre.";
			link.l1.go = "Newstorehelper_2_3";
			link.l2 = "Non ho ancora preso una decisione...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_2":
			dialog.text = "Il mercante non resterà deluso dal mio operato. E non scordarti della tua ricompensa extra.";
			link.l1 = "Ho deciso a tuo favore. Raccogli le tue cose. Si va a Saint-Pierre.";
			link.l1.go = "Newstorehelper_3_3";
			link.l2 = "Non ho ancora preso una decisione...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_3":
			dialog.text = "Lascia solo che raccolga le mie cose! Ti aspetto all'ingresso della taverna.";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 0;
		break;
		
		case "Newstorehelper_2_3":
			dialog.text = "Arrivo subito, monsieur! Vi aspetto all’ingresso della taverna.";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 1;
		break;
		
		case "Newstorehelper_3_3":
			dialog.text = "Prendo la mia vecchia valigia e vi aspetto all’ingresso della taverna, signore!";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 2;
		break;
		
		case "Newstorehelper_exit":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Sharlie.Storehelper.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay")
			chrDisableReloadToLocation = true;
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Newstorehelper_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			}
			pchar.quest.storehelper2.win_condition.l1 = "location";
			pchar.quest.storehelper2.win_condition.l1.location = "LeFransua_town";
			pchar.quest.storehelper2.function = "NewstorehelperAdd";
			AddQuestRecord("SharlieA", "4");
			pchar.questTemp.Sharlie.Storehelper = "choise";
			pchar.quest.storehelper.over = "yes"; //снять прерывание
			pchar.quest.Sharlie_JungleBandos.win_condition.l1 = "location";
			pchar.quest.Sharlie_JungleBandos.win_condition.l1.location = "Martinique_Jungle_01";
			pchar.quest.Sharlie_JungleBandos.function = "SharlieJungleBandos";
			
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload6_back");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
		break;
		
		case "Newstorehelper_regard":
			dialog.text = "Bene, suppongo che questo sia il mio nuovo posto da oggi? Vi ringrazio, monsieur, per avermi scelto. Ecco i vostri cinquecento pesos e il bonus promesso, come pattuito.";
			link.l1 = "La mia gratitudine... Permettimi di presentarti al tuo datore di lavoro.";
			link.l1.go = "Newstorehelper_regard_1";
		break;
		
		case "Newstorehelper_regard_1":
			DialogExit();
			npchar.lifeday = 0;
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "gold_dublon", 25);
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "jewelry8", 10);
					TakeNItems(pchar, "jewelry7", 1);
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 3000);
				break;
			}
		break;
		
		//контрабанда рома
		case "Rum_Cap_Over":
			dialog.text = "Monsieur, vi ordino di lasciare subito la mia nave. Stiamo levando l’ancora e mollando gli ormeggi!";
			link.l1 = "D'accordo...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rum_Cap_Over";
			chrDisableReloadToLocation = false;
			npchar.DontDeskTalk = true;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
		break;
		
		case "Rum_Cap":
			pchar.quest.Sharlie_rum2.over = "yes"; //снять таймер
			chrDisableReloadToLocation = false; // patch-4
			dialog.text = "E allora? Chi sei tu, compare?";
			//link.l1.edit = 1;			
			link.l1 = ""+pchar.questTemp.Sharlie.Rum.Pass+"!";
			link.l1.go = "Rum_Cap_1";
		break;
		
		case "Rum_Cap_1":
			dialog.text = "Bevi un sorso di rum, marinajo! Ah-ah! Benvenuto a bordo della mia lugger. Sei venuto per la merce?";
			link.l1 = "Sì. Perché mai sarei qui, se no?";
			link.l1.go = "Rum_Cap_2";
			/* if(GetStrSmallRegister(pchar.questTemp.Sharlie.Rum.Pass) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Bevi un goccio di rum, marinaio! Ah-ah! Benvenuto a bordo della mia lugger. Sei venuto per la merce?";
				link.l1 = "Sì. Perché altro sarei qui, secondo te?";
				link.l1.go = "Rum_Cap_2";
			}
			else
			{
				dialog.text = "Per mille tempeste, che figlio di una sgualdrina smarrito! Ragazzi, questo sembra proprio un novellino! Buttiamolo a mare!";
				link.l1 = "Su, forza!";
				link.l1.go = "Rum_Cap_getout";
			} */
		break;
		
		case "Rum_Cap_getout":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			setCharacterShipLocation(pchar, "Shore38"));
			setWDMPointXZ("Shore38");
			DoQuestReloadToLocation("Shore38", "goto", "goto1", "Rum_RemoveBarkas");
		break;
		
		case "Rum_Cap_2":
			dialog.text = "Ragazzi! Caricate le casse sulla scialuppa!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Rum_CarrierEnter");
		break;
		
		case "Rum_Cap_3":
			dialog.text = "Tutte le casse di rum sono già sul tuo scafo. Port Le Francois si trova dritto a sud da qui. Muoviti, che è tempo anche per me di salpare l’ancora!";
			link.l1 = "Non perdiamo tempo, signori! Buona fortuna!";
			link.l1.go = "Rum_Cap_4";
		break;
		
		case "Rum_Cap_4":
			dialog.text = "Anche a te, canaglia...";
			link.l1 = "...";
			link.l1.go = "Rum_Cap_5";
		break;
		
		case "Rum_Cap_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			npchar.DontDeskTalk = true;
			NextDiag.CurrentNode = "Rum_Cap_Over";
			pchar.quest.Sharlie_rum4.win_condition.l1 = "Ship_location";
			pchar.quest.Sharlie_rum4.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Sharlie_rum4.function = "Rum_RemoveRum";
			AddQuestRecord("SharlieB", "4");
			i = FindIsland("Martinique");
			Islands[i].EffectRadius = 3000;
			
			DoQuestFunctionDelay("MessageRum1", 1.0);
			//NewGameTip("Transport the rum to Le Francois. Keep sailing around the island.");
			pchar.questTemp.Rum.Tip2.Reload = "l4";
			
			Weather.Wind.Speed = 16.0;
			pchar.wind.speed = Weather.Wind.Speed;
			fWeatherSpeed = stf(Weather.Wind.Speed);//халява первого выхода
			
			Weather.Wind.Angle = PId2;
			pchar.wind.angle = Weather.Wind.Angle;
			fWeatherAngle = stf(Weather.Wind.Angle);//халява первого выхода
			
			pchar.quest.MessageRum2.win_condition.l1 = "ExitFromLocation";
			pchar.quest.MessageRum2.win_condition.l1.location = pchar.location;
			pchar.quest.MessageRum2.function = "MessageRum2";
		break;
		
		case "Rum_Carrier":
			dialog.text = "Vi stavamo aspettando, monsieur. Com’è andata la traversata? Avete con voi le casse?";
			link.l1 = "Tutto è filato a meraviglia. Le casse di rum sono già sulla scialuppa.";
			link.l1.go = "Rum_Carrier_1";
		break;
		
		case "Rum_Carrier_1":
			dialog.text = "Benissimo. Da qui ce la sbrighiamo noi. Tu filatene a St. Pierre, alla taverna, a riscuotere il pagamento. Sta' all'occhio e non distrarti tra le giungle notturne.";
			link.l1 = "Tutto il meglio, signori.";
			link.l1.go = "Rum_Carrier_2";
		break;
		
		case "Rum_Carrier_2":
			DialogExit();
			for (i=1; i<=3; i++)
			{
				
				sld = characterFromId("Rum_Carrier2_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			}
			pchar.questTemp.Sharlie.Rum = "regard";
			i = FindLocation("Fortfrance_town");
			setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
		    setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
			SetCurrentTime(23, 0);
			Sharlie_removeLocks("");
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			if(CheckAttribute(pchar, "questTemp.Sharlie.Gigolo")) QuestPointerToLocTime("fortfrance_town", "reload", "reload9_back", 23.0, 24.0);
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		//доставить девочку из борделя
		case "GigoloMan":
			DelLandQuestMark(npchar);
			dialog.text = "Buon pomeriggio, monsieur! Perbacco, non avete l’aria dei soliti cani sciolti che bazzicano la nostra colonia. A giudicare dal vostro abito, dovete aver fatto un bel viaggio… Siete forse giunto dall’Europa, eh?";
			link.l1 = "Esattamente, monsieur. "+GetFullName(pchar)+", al vostro servizio. Di che avete bisogno?";
			link.l1.go = "GigoloMan_1";
		break;
		
		case "GigoloMan_1":
			dialog.text = "Permettetemi di presentarmi - "+GetFullName(npchar)+" Sono giunto in questo lurido posto dalla Francia qualche anno fa. Ma non è questo il punto. Ho per voi una faccenda assai delicata.\nSappiate, per cortesia, che mai бы осмелился просить вас о таком одолжении, кабы не был уверен, что вы истинный джентльмен.";
			link.l1 = "Per favore, esponete la vostra richiesta, monsieur. Se sarà nei miei poteri, ebbene, tenterò senz’altro di prestarvi aiuto.";
			link.l1.go = "GigoloMan_2";
		break;
		
		case "GigoloMan_2":
			dialog.text = "I am glad to hear that, monsieur de Maure. Now, how to put this delicately...There is a brothel in this town. A new girl appeared there recently; young, pale, blonde, stunningly beautiful! Now, I've been watching her for weeks and... got a very strong desire to spend some time with her in private\nBut my estate and status make it...inconvenient to visit such a place. Imagine the gossip!\nThat is why I am appealing to you. Plainly put, you are a newcomer to our island, people don't know you and they don't care about what you do... yet. You could do me a great favour, monsieur.";
			link.l1 = "Penso di afferrare dove vuoi arrivare.";
			link.l1.go = "GigoloMan_3";
		break;
		
		case "GigoloMan_3":
			dialog.text = "Apprezzo la vostra discrezione, monsieur. Non posso andare io dalla ragazza, dunque la ragazza dovrà venire da me. A casa mia. Vi chiedo di recarvi al bordello e accordarvi con la madama affinché vi permetta di organizzare una 'visita a domicilio' della bionda per una notte.\nAurora non rifiuterà, è risaputo che offre tali servizi di consegna, sebbene ciò costi sempre qualcosa in più. Dopodiché condurrete la ragazza a casa mia. Come compenso, vi darò seimila pesos. Aurora di solito chiede tremila, o tremila e cinquecento per una notte con la ragazza in casa. Potete tenere il resto come ricompensa per i vostri fastidi.";
			link.l1 = "Non sembra troppo complicato. Posso occuparmene io.";
			link.l1.go = "GigoloMan_4";
			link.l2 = "Monsieur, tengo alla mia reputazione di gentiluomo quanto voi. Vi prego di scusarmi, ma non posso esaudire la vostra richiesta. Devo rifiutare. Forse mi conviene andare in taverna a vedere se l’oste ha qualche lavoretto per me.";
			link.l2.go = "GigoloMan_exit";
		break;
		
		case "GigoloMan_exit":
			DialogExit();
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false);// бордель open
			LocatorReloadEnterDisable("Fortfrance_town", "reload9", false);// бордель
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", false);// таверна
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			chrDisableReloadToLocation = false;
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			SetCurrentTime(17, 30);
		break;
		
		case "GigoloMan_4":
			dialog.text = "I am damn glad to hear it. Now listen, the girl's name is Lucille. I ask you to deliver her to my place when it's dark, no earlier than eleven p.m., in order to avoid unwanted attention from any gawkers. Knock on the door, and I will open.\nMy house is located to the left of the governor's residence, facing away from it - a two-story mansion with a red roof. You can easily find it, and there's a shop nearby, too. Actually, I am heading to my house now; feel free to follow me to see what it looks like and where it is exactly, so you won't get lost at night.\n Regarding the matter at hand - here, take six thousand pesos. I expect you by the agreed-upon time!";
			link.l1 = "Affare fatto. La tua bionda Lucille sarà sulla tua soglia stanotte.";
			link.l1.go = "GigoloMan_5";
		break;
		
		case "GigoloMan_5":
			DialogExit();
			AddMoneyToCharacter(pchar, 6000);
			AddQuestRecord("SharlieC", "1");
			AddQuestUserData("SharlieC", "sName", GetFullName(npchar));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("Fortfrance_town", "houseSp1", true);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie.Gigolo = "start";
			pchar.questTemp.Sharlie.Gigolo.Rand1 = rand(1);
			pchar.questTemp.Sharlie.Gigolo.Rand2 = rand(1);
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false);// бордель open
			LocatorReloadEnterDisable("Fortfrance_town", "reload91", false);// бордель
			AddLandQuestMark(characterFromId("Fortfrance_hostess"), "questmarkmain");
			QuestPointerToLoc("fortfrance_town", "reload", "reload9_back");
			QuestPointerToLoc("fortfrance_brothel", "reload", "reload3");
			chrDisableReloadToLocation = false;
		break;
		
		case "GigoloGirl":
			if (npchar.quest.meeting == "0")
			{
				DelLandQuestMark(npchar);
				QuestPointerDelLoc("fortfrance_town", "reload", "reload9_back");
				dialog.text = "Buongiorno, monsieur. Dite un po’, siete voi colui che mi ha ingaggiata stasera? Oh, che fortuna la mia, capitare con un gentiluomo così affascinante e ben curato, ben diverso da quei rozzi scaricatori che sbarcano dal porto puzzando di pece e sudore...";
				link.l1 = "Perdona la mia franchezza, Lucille, ma stanotte non se ne parla. Sono qui per conto di un caro amico che, per ragioni fin troppo intricate, non può mettere il naso fuori di casa, quindi ti accompagno io da lui. Su, non ti crucciare, è un galantuomo e ti porta una gran stima. Vedrai che alla fine ne sarai ben contenta.";
				link.l1.go = "GigoloGirl_1";
				// belamour legendary edition -->
				link.l2 = "Uhm... Hai proprio ragione, cara. Andiamo?";
				link.l2.go = "GigoloGirl_1a";
				// <-- legendary edition
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Monsieur, spero capiate che non posso certo passeggiare con voi a quest’ora della notte. Portatemi subito a casa del vostro amico, oppure torno dritta dalla Madame e avrete buttato i vostri soldi al vento.";
				link.l1 = "D'accordo, ho capito. Seguimi!";
				link.l1.go = "GigoloGirl_2";
			}
		break;
		// belamour legendary edition -->
		case "GigoloGirl_1a":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			chrDisableReloadToLocation = true; //закрыть локацию
			DoQuestReloadToLocation(pchar.location+"_room", "goto", "goto2", "GigoloGirl_Sex");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_room", "goto", "goto1");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		
		case "GigoloGirl_1":
			AddCharacterExpToSkill(pchar, "Fortune", 40);
		// <-- legendary edition
			dialog.text = "Che peccato... Mi sei piaciuto subito, monsieur. Avrei tanto voluto passare la notte con te... magari la prossima volta. Andiamo?";
			link.l1 = "Sì. Seguimi!";
			link.l1.go = "GigoloGirl_2";
		break;
		
		case "GigoloGirl_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_Gigolo.win_condition.l1 = "locator";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator = "houseSp1";
			pchar.quest.Sharlie_Gigolo.function = "Sharlie_GiveGigoloGirl";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.function = "Sharlie_GigoloGirlOver";
			QuestPointerToLoc("fortfrance_town", "reload", "houseSp1");
		break;
		
		case "GigoloGirl_3":
			dialog.text = "Che dimora sontuosa. È questo il posto?";
			link.l1 = "Sì. Entra pure. Non temere, il mio compare è un brav’uomo.";
			link.l1.go = "GigoloGirl_4";
		break;
		
		case "GigoloGirl_4":
			dialog.text = "Mi sottovaluti, non ho paura, monsieur. So badare a me stesso. E poi, magari più tardi potresti pagare alla Madame una notte con me? Ti prometto che sarà la migliore notte della tua vita!";
			link.l1 = "Tutto può accadere, Lucille. Forse ci rincontreremo ancora. Addio!";
			link.l1.go = "GigoloGirl_5";
		break;
		
		case "GigoloGirl_5":
			pchar.quest.Sharlie_Gigolo1.over = "yes";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "GigoloGirl_Remove", 5.0);
			QuestPointerDelLoc("fortfrance_town", "reload", "houseSp1");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		
		//пираты с пленным испанцем
		case "CaptivePirate":
			pchar.quest.Captive_CreatePiratesOver.over = "yes";//снять таймер
			pchar.quest.Captive_CreatePiratesOver2.over = "yes";//снять таймер
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_03", "reload", "reload2_back");
			dialog.text = "Che diavolo è questo!? Chi sei tu? Che ci fai qui? Dai, sparisci da qui, maledetto!";
			link.l1 = "Non sei affatto cortese, mascalzone.";
			link.l1.go = "CaptivePirate_1";
		break;
		
		case "CaptivePirate_1":
			dialog.text = "Ascolta, ragazzo, non sono stato cresciuto per essere gentile, come non m’hanno mai insegnato lettere, ma spaccarti il cranio con la sciabola mi viene facile come a una sgualdrina cascare di schiena. E giuro sulle mie luci morte: se non te ne vai subito, ti ci portano steso. Capito?";
			link.l1 = "No, ora ascolta me, furfante. Il tuo intrigo è ormai svelato. Mi serve quell’uomo vivo, quindi getta le armi e scappa. C’è una pattuglia di soldati francesi nella giungla proprio dietro di me. Se te la dai a gambe, forse riuscirai a salvare la tua miserabile pellaccia.";
			link.l1.go = "CaptivePirate_3";
			link.l2 = "Va bene, va bene, calmati. Me ne vado.";
			link.l2.go = "CaptivePirate_2";
		break;
		
		case "CaptivePirate_2":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_CharacterDisableDialog(sld);
				LAi_SetImmortal(sld, true);
				sld.lifeday = 0;
			}
			sld = characterFromId("CaptiveSpain");
			LAi_SetImmortal(sld, true);
			sld.lifeday = 0;
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";//снять прерывание
			AddQuestRecord("SharlieD", "5");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "CaptivePirate_3":
			dialog.text = "Cheee? Stai farneticando, compare! Prendetelo ragazzi, alle armi!";
			link.l1 = "Sarà la tua testa a pagare, allora! In guardia!";
			link.l1.go = "CaptivePirate_4";
		break;
		
		case "CaptivePirate_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			int n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Captive_PiratesDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
			sld = characterFromId("CaptiveSpain");
			LAi_SetCitizenType(sld);
			DoQuestFunctionDelay("Ngt_CaptiveEng", 0.5);
		break;
		
		//пленный испанец
		case "CaptiveSpain":
			dialog.text = "Gracias a Dios! Ah, sei francese? Maledizione, hai respinto quei briganti con gran classe. Ma non credere che mi arrenderò senza combattere, ora ti mostro come combatte un vero spagnolo! Santiago!";
			link.l1 = "No, aspetta, ti prego!";
			link.l1.go = "CaptiveSpain_1";
		break;
		
		case "CaptiveSpain_1":
			dialog.text = "Preferirei crepare piuttosto che finire nelle grinfie dei francesi. Ho preso una sciabola da uno dei cadaveri mentre tu menavi le mani... e ora ti farò ballare un fandango spagnolo!";
			link.l1 = "Voi spagnoli siete testardi come muli!";
			link.l1.go = "CaptiveSpain_2";
		break;
		
		case "CaptiveSpain_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			NextDiag.currentnode = "CaptiveSpain_3";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "CaptiveSpain_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "CaptiveSpain_3":
			dialog.text = "Maledetto... Hai vinto. Mi arrendo, dannato francese. Sono nelle tue mani.";
			link.l1 = "Metti via la lama e lasciami parlare, ostinato castigliano! Non voglio che tu ci lasci la pelle, né tantomeno mandarti in galera!";
			link.l1.go = "CaptiveSpain_4";
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
		break;
		
		case "CaptiveSpain_4":
			dialog.text = "E allora che ci fai qui? Perché hai ammazzato quei filibustieri? E dove sono finiti i tuoi soldati?";
			link.l1 = "Non ci sono soldati. Ho provato a gabbare quei furfanti, ma come vedi qui attorno, non ha funzionato. Sono qui da solo, su richiesta del tuo vecchio amico. Si chiama "+pchar.questTemp.Sharlie.Captive.Name+", è un banchiere a St. Pierre.";
			link.l1.go = "CaptiveSpain_5";
		break;
		
		case "CaptiveSpain_5":
			dialog.text = ""+pchar.questTemp.Sharlie.Captive.Name+"? Non conosco nessuno con quel nome...";
			link.l1 = "Non sapevo nulla né di te né della tua prigionia. Solo da lui ho appreso che ti hanno trasferito su una nave inglese. Il mio compito è portarti da lui, e ho giurato che l’avrei fatto! Suvvia, seguimi se tieni alla pelle.";
			link.l1.go = "CaptiveSpain_6";
		break;
		
		case "CaptiveSpain_6":
			dialog.text = "Tanto non ho scelta... Questo tuo banchiere non può essere peggio degli inglesi e della loro cucina schifosa...";
			link.l1 = "Finalmente prendi una decisione saggia. Ora basta chiacchiere, si va a Saint-Pierre. Stammi vicino e non ti allontanare. Se provi a svignartela, ti riacchiappo e ti pesto come l’ultima volta, capito?";
			link.l1.go = "CaptiveSpain_7";
		break;
		
		case "CaptiveSpain_7":
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.Notsearchbody"); // 170712
			DialogExit();
			AddQuestRecord("SharlieD", "6");
			LAi_group_Register("TempFriends");
			LAi_group_SetRelation("TempFriends", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "TempFriends");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
			pchar.quest.Sharlie_captive3.win_condition.l1 = "locator";
			pchar.quest.Sharlie_captive3.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator = "reload8_back";
			pchar.quest.Sharlie_captive3.win_condition.l2 = "Night";
			pchar.quest.Sharlie_captive3.win_condition.l3 = "Alarm";
			pchar.quest.Sharlie_captive3.win_condition.l3.value = 0;
			pchar.quest.Sharlie_captive3.win_condition.l3.operation = "=";
			pchar.quest.Sharlie_captive3.function = "CaptiveSpain_reload";//вход ночью
			pchar.questTemp.Sharlie = "bankskipercaptive";
			SetFunctionLocationCondition("CaptiveSpain_removeGuard", "fortfrance_town", 0);
			SetFunctionLocationCondition("CaptiveSpain_saveTip", "fortfrance_exittown", 0);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
			// Rebbebion, новые марки до места назначения. belamour поправил - были не в ту сторону
			QuestPointerToLoc("shore39", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_03", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload8_back");
			AddLandQuestMark(characterFromId("FortFrance_Usurer"), "questmarkmain");
		break;
		
		//горожанин с пропавшей дочерью
		case "Prosper":
			DelLandQuestMark(npchar);
			pchar.quest.Sharlie_RescueDaughter.over = "yes"; //снять прерывание
			dialog.text = "Cosa desiderate, monsieur? Non ho tempo da perdere in chiacchiere, dunque siate conciso.";
			link.l1 = "Tu sei Prosper Trubal, vero?";
			link.l1.go = "Prosper_1";
		break;
		
		case "Prosper_1":
			dialog.text = "Sì, sono io. Ma tu hai il vantaggio su di me. Dimmi chi diavolo sei e che accidenti vuoi.";
			link.l1 = "Il mio nome è "+GetFullName(pchar)+". Sono stato mandato da voi da "+GetFullName(characterFromId("Fortfrance_portman"))+", il maestro di porto. Diceva che avevi bisogno d’aiuto urgente...";
			link.l1.go = "Prosper_2";
		break;
		
		case "Prosper_2":
			dialog.text = "Dio mio, sì! Quel furfante di comandante non ha nemmeno ascoltato la mia lamentela! O è troppo pigro o un codardo per darmi una mano. Sei davvero venuto fin qui per aiutarmi? Se è così, non resterai a mani vuote, te lo prometto!";
			link.l1 = "Sì, Prosper. Dimmi cosa è successo e cosa devo fare per aiutarti. Ho sentito che tua figlia è sparita...";
			link.l1.go = "Prosper_3";
		break;
		
		case "Prosper_3":
			dialog.text = "Sì, la mia cara figlia Celene è scomparsa da due giorni. Era andata a passeggiare verso il forte, che si trova non lontano da qui. Ma non è mai tornata, così sono andato io stesso al forte e i soldati mi hanno detto che non l’hanno mai vista!\nPoi, tornando indietro, sono stato assalito da due selvaggi indiani! Mi si sono gettati addosso con delle mazze, cercando di ridurmi in poltiglia.\nMa non sono certo un gattino indifeso, così ho mollato un pugno in faccia a uno, guadagnando abbastanza tempo per sguainare la pistola e sparare. Ho mancato il bersaglio, ma li ho messi in fuga. Sono riuscito a raggiungere le porte della città e ho raccontato tutto alle guardie. Sono corsi nella giungla, ma quei selvaggi si erano già dileguati.\nSono sicuro che siano loro i responsabili della sparizione di Celene. E non solo: nell’ultima settimana sono scomparsi altri due cristiani – Cesar Blanchet e Gilbert Courcy! Uno era diretto alla baia, l’altro a Le Francois. Non hanno mai fatto ritorno.";
			link.l1 = "Dunque, gli indiani attaccano la gente proprio alle porte della città? Che sfacciataggine incredibile...";
			link.l1.go = "Prosper_4";
		break;
		
		case "Prosper_4":
			dialog.text = "Nel frattempo, sono andato io stesso nella giungla a cercarla e ho trovato una grotta a nord della città. Quei bastardi si sono rintanati là dentro. Ho visto diversi indios all’ingresso, ma alcuni dovevano essere anche dentro.\nHo sentito una ragazza urlare... Era la mia Celene, ne sono certo, era la sua voce! Ho dovuto mordermi la lingua per non gettarmi là dentro subito – non avevo alcuna possibilità e mi avrebbero fatto a pezzi. Da morto, non le sarei servito a nulla.";
			link.l1 = "Ma perché diavolo stanno attaccando e prendendo cittadini come prigionieri?";
			link.l1.go = "Prosper_5";
		break;
		
		case "Prosper_5":
			dialog.text = "Non saprei... Magari li venderanno ai filibustieri o agli schiavisti? O forse li mangeranno vivi, in fondo sono selvaggi.";
			link.l1 = "Santo Dio nei cieli, sono forse cannibali? Pensavo che fossero solo storie per spaventare i bambini in Europa...";
			link.l1.go = "Prosper_6";
		break;
		
		case "Prosper_6":
			dialog.text = "Storie, dici? Beh, certi uomini come te la pensavano allo stesso modo, finché i Caribi non li hanno cotti allo spiedo e mangiati… Così sono corso subito dal comandante, chiedendo una spedizione punitiva per salvare la mia Célène. Mi ha riso in faccia! Secondo lui, quando spariscono le ragazze, di solito scappano con qualche giovanotto, non con gli indiani. Mi ha pure consigliato di cercarla nei fienili qui intorno.\nQuanto agli altri due scomparsi… uno sospettato di contrabbando, l’altro probabilmente annega nel rum alla taverna di Le François. Insomma, non ho concluso un accidente e ho deciso di darmi da fare per conto mio.";
			link.l1 = "Che hai intenzione di fare?";
			link.l1.go = "Prosper_7";
		break;
		
		case "Prosper_7":
			dialog.text = "Andrò laggiù e sterminerò fino all’ultimo di quei maledetti cani rossi. Spero solo che Celene sia ancora viva. Come vedi, ho comprato un moschetto – e so come usarlo. Mi è costato un sacco di dobloni ma non me ne frega nulla.\nLa mia impresa sarebbe ben più facile se venissi con me. Insieme potremmo spazzare via quei selvaggi senza troppi grattacapi, se solo mi copri le spalle mentre ricarico. Mi accompagnerai a salvare mia figlia?";
			link.l1 = "Ma certo! È questione d'onore! Non posso certo lasciare che una fanciulla finisca sotto la lama di qualche selvaggio.";
			link.l1.go = "Prosper_8";
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") {
				link.l1.go = "Prosper_noweapon";
			}
			link.l2 = "Hm. Sai, credo che le parole del comandante abbiano un certo senso. Forse dovremmo davvero seguire prima il suo consiglio?";
			link.l2.go = "Prosper_exit";
		break;
		
		case "Prosper_noweapon":
			dialog.text = "Monsieur, dove avete lasciato la vostra lama?";
			link.l1 = "Pare che l’abbia perso da qualche parte.";
			link.l1.go = "Prosper_noweapon_1";
		break;
		
		case "Prosper_noweapon_1":
			dialog.text = "Così proprio non va. Ti aspetterò fino a sera, ti consiglio di strisciare ai piedi del nostro governatore e supplicarlo per il suo aiuto.";
			link.l1 = "Strisciare ai suoi piedi, eh? Beh, come vuoi tu...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prosper_getweapon";
			SetFunctionTimerConditionParam("RescueDaughter_Over", 0, 0, 0, 22, false);
		break;
		
		case "Prosper_getweapon":
			dialog.text = "Ebbene, monsieur? Hai messo le mani su una lama?";
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") {
				link.l1 = "Non ancora, abbi ancora un po’ di pazienza...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Prosper_getweapon";
			} else {
				link.l1 = "Capisco. Sono pronto ad aiutarti!";
				link.l1.go = "Prosper_8";
				DeleteQuestCondition("RescueDaughter_Over");
			}
		break;

		case "Prosper_exit":
			dialog.text = "Dio mio, stai scappando? No! Fuori dai piedi, vigliacco!";
			link.l1 = "Ehi-ehi, piano lì, sempliciotto! Meglio che vada a vedere se qualche nobilastro per le strade di Saint-Pierre ha bisogno d’aiuto.";
			link.l1.go = "Prosper_exit_1";
			pchar.questTemp.Sharlie.GigoloMan.SamPodbezhit = true;
		break;
		
		case "Prosper_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			//AddTimeToCurrent(2,0);
			SetCurrentTime(17,30);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "gate_back", "none", "", "", "", 10.0);
			CloseQuestHeader("SharlieF");
			chrDisableReloadToLocation = true;
			
			//Подбегает дворянин с квестом "девочка по вызову"
			sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
			SetFantomParamFromRank(sld, 25, true);
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.dialog.currentnode = "GigoloMan";
			sld.greeting = "noble_male";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetLoginTime(sld, 6.0, 21.0);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Prosper_8":
			dialog.text = "Son lieto che almeno un uomo con le palle si trovi in questa città. Tieni, prendi queste tre fiale. Sono erbe che danno forza e salute, le ho comprate dal nostro speziale. Ti saranno di buon aiuto quando le spade cominceranno a cantare.";
			link.l1 = "E tu invece?";
			link.l1.go = "Prosper_9";
		break;
		
		case "Prosper_9":
			TakeNItems(pchar, "potion1", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "Non preoccuparti, ne ho ancora. Sei pronto?";
			link.l1 = "Sì, non perdiamo tempo. Avanti!";
			link.l1.go = "Prosper_10";
		break;
		
		case "Prosper_10":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "fortfrance_exittown", "reload", "reload3", "OpenTheDoors", 10.0);
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1 = "location";
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1.location = "FortFrance_ExitTown";
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition = "RescueDaughter_ProsperGateOutReload";
			AddQuestRecord("SharlieF", "3");
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1.location = "Martinique_jungle_04";
			pchar.quest.Sharlie_RescueDaughter1.function = "RescueDaughter_NearCave";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.hour  = sti(GetTime()+2);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CaveOver";
			NextDiag.CurrentNode = "Prosper_11";
			pchar.questTemp.Sharlie.RescueDaughter = "true";
			LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", true);//форт
			LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", true);//джунгли
			LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", true);//джунгли
		break;
		
		case "Prosper_11":
			dialog.text = "Siamo quasi pronti, "+pchar.name+"   Oltre questa curva si trova l’ingresso della grotta. Avvicinati e ti svelerò il nostro piano.";
			link.l1 = "Sono tutto orecchi, Prosper.";
			link.l1.go = "Prosper_12";
		break;
		
		case "Prosper_12":
			dialog.text = "Devo prendere bene la mira con quest’archibugio pesante, ma se mi tieni il tempo non sbaglierò bersaglio. Se però si arriva al corpo a corpo, scordati il fuoco di copertura: potrò solo menar colpi col calcio come un randagio. Questa battaglia dipenderà tutto dalla tua abilità con la spada.";
			link.l1 = "Che vuoi insinuare?";
			link.l1.go = "Prosper_13";
		break;
		
		case "Prosper_13":
			dialog.text = "Tutto ciò che devi fare è distrarli abbastanza da lasciarmi sparare a tutti quanti. Non posso muovermi e sparare, quindi rimarrò fermo in un punto. Ci sono tre furfanti vicino all’ingresso della grotta. Devi piombare su di loro il più in fretta possibile, con la lama sguainata.\nColpiscine uno e attira la loro furia su di te. Portali lontano da me. Se tutti e tre si accaniscono su di te, potrò abbatterli come uccelli mentre schivi e pari. Ma se quei selvaggi si fiondano contro di me, siamo spacciati. Sei pronto?";
			link.l1 = "Non è la prima volta che impugno una spada, questi selvaggi non sono una minaccia.";
			link.l1.go = "Prosper_14";
			// belamour legendary edition -->
			link.l2 = "Ah! Non preoccuparti per me. È come cacciare a Le Mans! Basta che non mi spari nella schiena per sbaglio!";
			link.l2.go = "Prosper_14a";
		break;
		
		case "Prosper_14a":
			AddCharacterExpToSkill(pchar, "FencingL", 10);
			AddCharacterExpToSkill(pchar, "FencingS", 10);
			AddCharacterExpToSkill(pchar, "FencingH", 10);
			AddCharacterExpToSkill(pchar, "Pistol", 10);
			dialog.text = "Avanti tu, io ti seguo. Ricorda: non devi lasciarli avvicinarsi a me!";
			link.l1 = "Mi ricordo, andiamo. Avanti!";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_14":
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			// <-- legendary edition
			dialog.text = "Allora preparati all’azione. Vai avanti tu, ti seguirò da vicino. Ricorda: non devi lasciarli avvicinare troppo a me!";
			link.l1 = "Ricordo. Farò tutto ciò che è in mio potere. Avanti, all’arrembaggio!";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_15":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_jungle_04", "reload2_back", false);
			NextDiag.CurrentNode = "Prosper_16";
			NewGameTip("A challenging fight awaits ahead. (F6) for quick save.");
		break;
		
		case "Prosper_16":
			dialog.text = "Ben fatto, "+pchar.name+"Questi selvaggi pagani non uccideranno più nessого. Ora passiamo alla vera faccenda: la grotta. Credo che dentro ce ne siano tre o quattro, ma non posso esserne certo. Ascolta bene.\nCi sono stato dieci anni fa. Dentro c’è un cunicolo stretto che porta a una specie di grotticella, separata da un muro con un buco nel mezzo. Facciamo come abbiamo deciso prima: io rimango vicino all’ingresso e tu ti getti dentro.\nAttirali su di te, non tentare di affrontarli tutti assieme, basta che non mi lascino a portata. Mettiti al tunnel di cui ti ho detto: è stretto, così solo uno o due alla volta potranno starti addosso.\nIo gli sparerò da sopra la tua spalla. Pronto?";
			link.l1 = "Avanti! Sbarazziamoci di questa tana di selvaggi!";
			link.l1.go = "Prosper_17";
		break;
		
		case "Prosper_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_CaveEntrance", "reload1_back", false);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.location = "Martinique_Grot";
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CreateIndiansGrot";
			NextDiag.CurrentNode = "Prosper_18";
		break;
		
		case "Prosper_18":
			dialog.text = "Mia figlia è viva! Sia lodato il Cielo! Siamo arrivati in tempo, "+pchar.name+" Le sono debitore, signore. Siete un uomo coraggioso e un ottimo spadaccino!";
			link.l1 = "Sono lieto che ci sia un lieto fine, Prosper. È stato un vero bagno di sangue far fuori tutti quegli indiani.";
			link.l1.go = "Prosper_19";
		break;
		
		case "Prosper_19":
			DialogExit();
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
		break;
		
		case "Prosper_20":
			dialog.text = "I miei più profondi ringraziamenti ancora una volta, "+pchar.name+"Avanti, torniamo in città. La vita di mia figlia non ha prezzo, nessun tesoro al mondo può valerne il valore... ma lascia che ti ringrazi con ciò che resta dei miei risparmi. Non appena metteremo piede a Saint-Pierre, sarò lieto di darteli. E non azzardarti nemmeno a rifiutare!";
			link.l1 = "Non mi tirerò indietro, Prosper. Anche se non l’ho fatto per denaro, aiutarti.";
			link.l1.go = "Prosper_21";
		break;
		
		case "Prosper_21":
			dialog.text = "Sei un vero cavaliere cristiano, "+pchar.name+"Orsù, non attardiamoci oltre. Facciamo vela verso casa senza indugio!";
			link.l1 = "…";
			link.l1.go = "Prosper_22";
		break;
		
		case "Prosper_22":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Tutorial_Amulet.over = "yes";
			SetLaunchFrameFormParam("Back to the town...", "Reload_To_Location", 0, 3.0);
			SetLaunchFrameReloadLocationParam("FortFrance_town", "reload", "gate_back", "");
			LaunchFrameForm();
		break;
		
		case "Prosper_23":
			SelectPresentAmulet();
			dialog.text = "Eccoci qua, Charles. Ti ringrazio ancora per l’aiuto e associo a queste parole una modesta borsa di pesos e dobloni d’oro. Ti consiglio di non sperperare i dobloni e tenerli per le occasioni davvero importanti. So che non sono gran ricchezze per ciò che hai fatto per me, ma viene dal cuore. Prendi anche questo amuleto, "+pchar.questTemp.SMQ.Text+"";
			link.l1 = "Grazie! Addio Prosper, che la felicità arrida a te e alla tua amata figlia!";
			link.l1.go = "Prosper_24";
		break;
		
		case "Prosper_24":
			LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", false);//форт
			LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", false);//джунгли
			LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", false);//джунгли
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "gold_dublon", 15);
			TakeNItems(pchar, pchar.questTemp.SMQ.Amulet, 1);
			Log_Info("You've received 15 doubloons");
			Log_Info("You've received an amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ah, un marito come te le farebbe proprio bene. Tutto il giorno non fa che farsi inseguire per la città da un branco di moscerini smidollati senza mento. Peccato maledetto che siano tutti spariti chissà dove... che vadano pure all’inferno. In bocca al lupo, Charles!";
			link.l1 = "...";
			link.l1.go = "Prosper_25";
		break;
		
		case "Prosper_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload10_back", "none", "", "", "", 10.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 120);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 70);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 70);//скрытность
			AddQuestRecord("SharlieF", "7");
			CloseQuestHeader("SharlieF");
			DeleteAttribute(pchar, "questTemp.SMQ");
			pchar.questTemp.Prosper_fmql = "true"; // Addon-2016 Jason, французские миниквесты (ФМК)
			pchar.questTemp.ZsI_Cannibals = true;	//Sinistra Требуется для квеста "Знакомство с индейцами"
			pchar.quest.Sharlie_JungleNative.win_condition.l1 = "location";
			pchar.quest.Sharlie_JungleNative.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.Sharlie_JungleNative.function = "SharlieJungleNative";
			SetCurrentTime(17,30);
			//AddTimeToCurrent(2,0);
			//QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Selina":
			dialog.text = "Ah! Che Dio mi assista! (piange) Tu... tu non puoi nemmeno immaginare l’orrore che si consuma qui! Questi... questi selvaggi ci hanno trascinati qui per ammazzarci e divorarci! Cesar Blanchet era con noi... Quei dannati selvaggi l’hanno preso... Hanno compiuto un qualche rito infernale e poi... Signore, non riesco nemmeno a parlarne! Dovevo essere il prossimo! Volevano sgozzarmi... domani!";
			link.l1 = "Calmati, Céline. È tutto finito. Quei cani maledetti hanno avuto ciò che si meritavano e non faranno più del male a nessuno.";
			link.l1.go = "Selina_1";
		break;
		
		case "Selina_1":
			dialog.text = "Anche Gilbert Coursie è qui. Laggiù... ehm... non si è ancora ripreso. Parlagli... Poi sbrighiamoci a filar via da questo posto!";
			link.l1 = "Su, su. Va tutto bene, ragazza. Basta lacrime. Va tutto bene. Hai un padre straordinario. Non permetterebbe mai che ti accadesse nulla... Vai fuori, io aiuterò... ehm... Gilbert a uscire di qui e poi ti raggiungo.";
			link.l1.go = "Selina_2";
		break;
		
		case "Selina_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			sld = characterFromId("RD_Prosper");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_1", "", 5.0);
			AddQuestRecord("SharlieF", "5");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
		break;
		
		case "Selina_3":
			dialog.text = "Dio e la Santa Vergine hanno udito le mie preghiere! Sei venuto a salvarci?";
			link.l1 = "Tu... Il tuo nome è Celine, vero?";
			link.l1.go = "Selina_4";
		break;
		
		case "Selina_4":
			dialog.text = "Sì... (piangendo) Tu... tu non puoi nemmeno immaginare gli orrori che accadono qui! Questi... questi selvaggi ci hanno trascinato in questo inferno per scannarci e mangiarci vivi! Cesar Blanchet era qui... L'hanno preso... Hanno fatto qualche rito maledetto e poi... Signore, non riesco nemmeno a parlarne! Dovrei essere il prossimo! Domani volevano sgozzarmi...";
			link.l1 = "Calmati, piccola... Mi dispiace, ma ho brutte notizie per te. Sono venuto qui insieme a tuo padre. È stato ucciso proprio là fuori da quei selvaggi dalla pelle rossa, mentre lottavamo per raggiungerti. Ha dato la vita per salvarti.";
			link.l1.go = "Selina_5";
		break;
		
		case "Selina_5":
			dialog.text = "Cosa?! Mio padre... Oh Dio! Io... io...(singhiozza)";
			link.l1 = "Le mie condoglianze, Céline. Non sei sola qui, vero?";
			link.l1.go = "Selina_6";
		break;
		
		case "Selina_6":
			dialog.text = "(tra le lacrime) Sì... Gilbert Coursie. È lì dentro... Non si è ancora ripreso. Vai a parlargli... Poi filiamo via di qui!";
			link.l1 = "Sì, certo. Non possiamo perdere nemmeno un minuto a bighellonare qui.";
			link.l1.go = "Selina_7";
		break;
		
		case "Selina_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			AddQuestRecord("SharlieF", "6");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
			AddComplexSelfExpToScill(20, 20, 20, 20);
		break;
		
		case "Selina_8":
			dialog.text = "Mio padre... Il mio povero, caro padre! Ah, monsieur, non vi ho neanche ringraziato per avermi salvato...";
			link.l1 = "Selina, son solo felice che tu e Gilbert siate usciti vivi da quella grotta. La morte eroica di tuo padre non è stata vana.";
			link.l1.go = "Selina_9";
		break;
		
		case "Selina_9":
			dialog.text = "(piangendo) Per favore, monsieur, portateci con voi in città. Dobbiamo mandare a chiamare i soldati perché vengano a prendere il corpo di mio padre, così che possa avere una degna sepoltura cristiana...";
			link.l1 = "Ma certo, Céline. Seguimi!";
			link.l1.go = "Selina_10";
		break;
		
		case "Selina_10":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Selina_11":
			dialog.text = "Grazie, monsieur, per aver accompagnato il mio povero padre... Grazie per avermi salvato da morte certa. Io... io... Ecco, prendi questa borsa di dobloni. L'ho trovata in uno scrigno di mio padre a casa. Ti prego, non osare nemmeno pensare di rifiutare!";
			link.l1 = "Grazie, Céline. Sono davvero lieto che siamo riusciti a salvarti. Le mie più sentite condoglianze per la perdita di tuo padre.";
			link.l1.go = "Selina_12";
		break;
		
		case "Selina_12":
			TakeNItems(pchar, "gold_dublon", 15);
			PlaySound("interface\important_item.wav");
			dialog.text = "Siete un vero gentiluomo, monsieur. Non vi scorderò mai. Addio!";
			link.l1 = "Addio, Céline.";
			link.l1.go = "Selina_13";
		break;
		
		case "Selina_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			AddQuestRecord("SharlieF", "8");
			CloseQuestHeader("SharlieF");
			pchar.questTemp.ZsI_Cannibals = true;	//Sinistra Требуется для квеста "Знакомство с индейцами"
			
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Jilberte":
			PlaySound("Voice\English\other\robinzons-08.wav");
			dialog.text = "Oh Signore, davvero tutto questo è ormai alle nostre spalle? Faccio fatica a crederci... Hai salvato sia me che Céline. Se non fosse stato per te, domani la stessa sorte toccata al povero Cesare sarebbe capitata a lei, e tra qualche giorno sarebbe toccato anche a me.";
			link.l1 = "Questi indiani... sono davvero cannibali?!";
			link.l1.go = "Jilberte_1";
		break;
		
		case "Jilberte_1":
			dialog.text = "Ne dubiti? Se hai fegato, ficca il naso tra le ceneri del loro fuoco da campo. Troverai quel poveraccio di Cesare lì. Ora non è altro che quattro ossa rosicchiate...";
			link.l1 = "Santissimo Sacramento... No, passo. Son giunto qui dall’Europa da poco e mai avrei pensato che simili abomini diabolici ancora accadessero su questa terra.";
			link.l1.go = "Jilberte_2";
		break;
		
		case "Jilberte_2":
			dialog.text = "Nel Caribe succedono cose assai strane, cose di cui in Vecchio Mondo solo si sussurra... Sciamani indiani, magia, riti segreti e stregonerie. Resta qui abbastanza e vedrai ogni sorta di diavoleria coi tuoi occhi. Ma perdonami, non ti ho ancora ringraziato per avermi salvato – son ancora scosso.\nMi hai salvato la pellaccia e la mia gratitudine non sarà solo a parole, ma anche sonante d’oro. Scorta me e Céline fino alla città; là potrò ricompensarti come si conviene, monsieur.";
			link.l1 = "D'accordo. Esci fuori. Prima voglio dare un'occhiata qui attorno.";
			link.l1.go = "Jilberte_3";
		break;
		
		case "Jilberte_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_3", "OpenTheDoors", 10.0);
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1.location = "Martinique_CaveEntrance";
			pchar.quest.Sharlie_RescueDaughter5.function = "RescueDaughter_GoHome";
		break;
		
		case "Jilberte_4":
			dialog.text = "Permettetemi ancora una volta di esprimervi la mia più profonda gratitudine per avermi salvato, monsieur! Come promesso, alle mie parole di ringraziamento aggiungo ora il mio apprezzamento concreto sotto forma di pesos d’argento e dobloni d’oro.";
			link.l1 = "Sono lieto che tutto sia finito per il meglio, Gilbert.";
			link.l1.go = "Jilberte_5";
		break;
		
		case "Jilberte_5":
			AddMoneyToCharacter(pchar, 3000);
			TakeNItems(pchar, "gold_dublon", 20);
			Log_Info("You've received 20 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Non puoi nemmeno immaginare quanto mi renda felice tutto ciò! Ti ringrazio ancora e permettimi ora di congedarmi, monsieur.";
			link.l1 = "Buona fortuna, Gilbert! A proposito, sapresti per caso se qualcun altro a Saint-Pierre ha bisogno d’aiuto?";
			link.l1.go = "Jilberte_6a";
		break;
		
		case "Jilberte_6a":
			dialog.text = "Non saprei, ma... Potete chiedere alla gente per strada, Monsieur. La plebaglia e perfino i benestanti di solito non hanno nulla di interessante, ma i gran signori... forse avranno un incarico per voi.";
			link.l1 = "Capito, Gilbert, grazie. Ci si vede!";
			link.l1.go = "Jilberte_6";
		break;
		
		case "Jilberte_6":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.Sharlie.RescueDaughter");
			
			//Подбегает дворянин с квестом "девочка по вызову"
			sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
			SetFantomParamFromRank(sld, 25, true);
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.dialog.currentnode = "GigoloMan";
			sld.greeting = "noble_male";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetLoginTime(sld, 6.0, 21.0);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
			sld.talker = 9;
			LAi_SetCitizenType(sld);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Ascolta, tu! Sono un onesto cittadino di questa città. Ti prego di non andare in giro con la lama sguainata come un volgare tagliagole.","Signore, vi prego, la legge parla chiaro: nessun uomo può girare con le armi sguainate tra queste mura.");
			link.l1 = LinkRandPhrase("D'accordo.","Molto bene.","Come desideri...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

void SelectPresentAmulet()
{
	switch (pchar.HeroParam.HeroType)
	{        
		case "HeroType_1":
			pchar.questTemp.SMQ.Amulet = "indian_7";
			pchar.questTemp.SMQ.Text = "it adds endurance and gives a second wind.";
		break;
		
		case "HeroType_2":
			pchar.questTemp.SMQ.Amulet = "amulet_7";
			pchar.questTemp.SMQ.Text = "it heightens resilience to battle wounds.";
		break;
		
		case "HeroType_3":
			pchar.questTemp.SMQ.Amulet = "indian_4";
			pchar.questTemp.SMQ.Text = "it raises the attack strength of your weapons.";
		break;
		
		case "HeroType_4":
			pchar.questTemp.SMQ.Amulet = "indian_1";
			pchar.questTemp.SMQ.Text = "it makes fire weaponry much more lethal.";
		break;
	}
}

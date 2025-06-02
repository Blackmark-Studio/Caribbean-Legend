// Addon-2016 Jason, французские миниквесты (ФМК) Мартиника
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Un errore evidente. Fai sapere ai diavoli che l’han fatto.";
			link.l1 = "Oh, lo farò.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестодатель
		case "carpenter":
			DelMapQuestMarkCity("Fortfrance");
			LAi_SetImmortal(npchar, false);
			npchar.lifeday = 0;
			DelLandQuestMark(npchar);
			dialog.text = TimeGreeting()+", capitano. Permettete che mi presenti - "+GetFullName(npchar)+" . Sebbene ci siamo già incontrati di recente, dubito che tu ti ricordi di me.";
			link.l1 = "Salute, monsieur. Dove mai ci saremmo già incontrati?";
			link.l1.go = "carpenter_1";
		break;
		
		case "carpenter_1":
			sTemp = "lugger 'Adeline'";
			if (pchar.questTemp.Sharlie.Ship == "sloop") sTemp = "sloop 'Black Dog'";
			dialog.text = "Il nostro cantiere navale. Hai acquistato "+sTemp+". Ti ricordi adesso? Sono il carpentiere laggiù.";
			link.l1 = "Sì, davvero ho comprato quella nave. Allora, che vuoi, monsieur "+GetFullName(npchar)+"?";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
			sld = characterFromId("FortFrance_shipyarder");
			AddLandQuestMark(sld, "questmarkmain");
			dialog.text = "Il nostro costruttore di navi "+GetFullName(sld)+"vuole parlarti. Credo che abbia una proposta d'affari per te. Ha visto la tua nave nel nostro porto e mi ha mandato a cercarti. Accetteresti il suo invito, per cortesia?";
			link.l1 = "D'accordo. Andrò a trovare il tuo capo appena avrò sbrigato le mie faccende in città.";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			pchar.questTemp.FMQM = "begin";
			AddQuestRecord("FMQ_Martinique", "1");
			SetFunctionTimerCondition("FMQM_Denial", 0, 0, 2, false);
		break;
		
		case "officer":
			PlaySound("Voice\English\soldier_arest_4.wav");
			dialog.text = "Ben-ben... Nuovi contrabbandieri nella mia rete!";
			link.l1 = "Eh...";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			dialog.text = "Basta con le chiacchiere! In questo cantiere ci sono diverse botti di resina. Capitano, le hai consegnate al tuo compare. Siete entrambi in arresto e confisco il carico in nome della legge!";
			link.l1 = "...";
			link.l1.go = "officer_2";
		break;
		
		case "officer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_3":
			dialog.text = "Non fare il finto tonto, capitano! Quali botti? Sai benissimo che parlo proprio di quelle botti che avete scaricato poco fa dalla nave di questo marinaio! Finirete tutti e due a marcire nelle segrete! Avanti, canaglie...";
			link.l1 = "";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_5":
			PlaySound("Voice\English\soldier\soldier arest-02.wav");
			dialog.text = "Questa resina, mio caro maestro d’ascia, è una merce di valore strategico sotto il diretto controllo del nostro governatore! Dal momento che la reclami tutta per te – così sia. Sei in arresto: passerai la notte nelle nostre comode segrete e domani ci renderai un resoconto dettagliato su come l’hai ottenuta e per quale scopo. Non preoccuparti, prima o poi sapremo tutto. Tu, capitano, sei libero di andare. Oggi la fortuna ti sorride.";
			link.l1 = "";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("FMQM_officer"));
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "FortFrance_town", "officers", "reload5_3", "FMQM_ArestContinue", 8);
		break;
		
		case "officer_7":
			PlaySound("Voice\English\soldier_arest_2.wav");
			dialog.text = "Sapevo che questa nave aveva qualcosa che non andava... Pare proprio che ti abbia sottovalutato, capitano.";
			link.l1 = "Esattamente, tenente. Non sono così sprovveduto. La tua allegra complicità col costruttore di navi è ormai andata a ramengo.";
			link.l1.go = "officer_8";
			DelLandQuestMark(npchar);
		break;
		
		case "officer_8":
			dialog.text = "Capisco. Complimenti, devi avere del talento se sei riuscito a rintracciarmi e sorprendermi. Ora dimmi, cosa vuoi da me?";
			link.l1 = "Non è chiaro? Voglio indietro la mia resina. Quella che tu e il tuo compare mi avete soffiato.";
			link.l1.go = "officer_9";
		break;
		
		case "officer_9":
			dialog.text = "D'accordo. Puoi prenderlo, ma solo metà del tuo carico. È tutto quello che ho nascosto qui. Spero ti basti, perché è tutto ciò che posso offrire.";
			link.l1 = "Stai ancora cercando di fregarmi? Dammi l'altra metà in dobloni o con la mercanzia che tieni nascosta alle tue spalle.";
			link.l1.go = "officer_10";
		break;
		
		case "officer_10":
			dialog.text = "Non se ne parla. Vai dal nostro comune compare per l'altra metà.";
			link.l1 = "Mi stai prendendo per il culo? Davvero credi che "+GetFullName(characterFromId("FortFrance_shipyarder"))+" mi restituirà le mie botti? Che assurdità.";
			link.l1.go = "officer_11";
		break;
		
		case "officer_11":
			dialog.text = "Capitano, prendi tutta la resina che ho, tieniti la vita e sparisci da qui al diavolo. In più ti prometto di non darti noie a Saint-Pierre. Questa è la mia ultima offerta.";
			link.l1 = "Da quando la mia vita fa parte del patto? Ah!";
			link.l1.go = "officer_12";
		break;
		
		case "officer_12":
			dialog.text = "Sembri ancora credere d’essere invincibile dopo lo scontro, capitano. Lascia che ti chiarisca una cosa: quelli erano pivelli, inesperti e senza voglia di combattere, contro la mia ciurma non hai speranza. Potrei farti ammazzare qui e ora senza tante storie, ma tengo alla pelle dei miei uomini. Qualcuno potrebbe farsi male, o finire all’altro mondo, solo per levarti di mezzo. Dunque, o accetti la mia offerta magnanima, oppure resti qui a marcire. Ora decidi.";
			link.l1 = "Vaffanbagno, tenente, ma sono costretto ad accettare le tue condizioni. Qui sono decisamente in svantaggio.";
			link.l1.go = "officer_13";
			link.l2 = "Troppo sicuro di te, tenente? Suppongo che dovrò darti una lezione a te e ai tuoi mercenari. Maledetto cane di pece!";
			link.l2.go = "officer_15";
		break;
		
		case "officer_13":
			dialog.text = "Sei un uomo ragionevole, capitano. Prendi le tue botti e levati dai piedi. Ti avverto però, accusarmi davanti al governatore non ti servirà a nulla. Oggi stesso cambierò il nascondiglio della mia roba. Risparmia il tuo tempo.";
			link.l1 = "Non avevo intenzione di farlo. Capisco bene quanto sia inutile rivolgersi alle autorità.";
			link.l1.go = "officer_14";
		break;
		
		case "officer_14":
			dialog.text = "Svelto, non ho molto tempo da perdere.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_PeaceExit");
		break;
		
		case "officer_15":
			DialogExit();
			AddDialogExitQuestFunction("FMQM_BattleExit");
		break;
		
		case "greguar":
			PlaySound("Voice\English\LE\Greguar\Greguar_02.wav");
			dialog.text = "Oh! Che incontro! Salute, monsignore! Passate una notte magnifica?";
			link.l1 = "Buona notte... ah, sei tu! Ti riconosco, ci siamo incontrati proprio il primo giorno che sono sbarcato nei Caraibi. Monsignor Gregoire Valinnie.";
			link.l1.go = "greguar_1";
		break;
		
		case "greguar_1":
			dialog.text = "Felice che tu abbia ancora memoria. Vedo che ora sei diventato capitano. Capitano "+GetFullName(pchar)+" . Congratulazioni.";
			link.l1 = "Grazie...";
			link.l1.go = "greguar_2";
		break;
		
		case "greguar_2":
			dialog.text = "Sembri preoccupato, capitano. Che diavolo è successo qui? C’è qualcosa che non va?";
			link.l1 = "Qualcosa non quadra...";
			link.l1.go = "greguar_3";
		break;
		
		case "greguar_3":
			dialog.text = "Monsieur, invece di restare in mezzo alla strada, andiamo in taverna. Una pinta o due ti farebbero bene. Lì possiamo parlare. Su, vieni!";
			link.l1 = "...";
			link.l1.go = "greguar_4";
		break;
		
		case "greguar_4":
			DialogExit();
			NextDiag.CurrentNode = "greguar_5"; 
			FreeSitLocator("Fortfrance_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Fortfrance_tavern", "sit", "sit_front4", "FMQM_InTavern", -1);
		break;
		
		case "greguar_5":
			LAi_SetSitType(Pchar);
			dialog.text = "Versane ancora, capitano...";
			link.l1 = "Vai, avanti...";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,20);
			RecalculateJumpTable();
			dialog.text = "Uff... Su, dimmi che ti rode? Hai la faccia di quel disgraziato che han fatto penzolare la scorsa settimana. Stesso sguardo da condannato sulla forca.";
			link.l1 = "Vede, monsieur Gregoire... Diciamo solo che ho delle grane con il lavoro.";
			link.l1.go = "greguar_7";
		break;
		
		case "greguar_7":
			dialog.text = "Capitano, puoi confidarmi tutto. Non sono tipo da venderti al governatore o al comandante, puoi fidarti di me. Non hai fiducia in me?";
			link.l1 = "Mi fido di te, monseniore.";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			dialog.text = "Allora confessa e alleggerisci la tua anima. Potrei essere in grado di darti una mano.";
			link.l1 = "Un costruttore di navi locale m’ha assoldato per depredare una carovana spagnola salpata da Trinidad. Aveva un gran bisogno di resina, quella era la mia preda e promise quindici dobloni per ogni barile. Ho rintracciato la carovana, l’ho svaligiata e portato il bottino qui. Hanno messo la mia nave in riparazione e scaricato i barili all’arsenale. Stavamo per chiudere l’accordo quando quell’ufficiale si è fatto vivo... Mi chiedo come diavolo abbia fatto a scoprirlo?";
			link.l1.go = "greguar_9";
		break;
		
		case "greguar_9":
			dialog.text = "";
			link.l1 = "Era fatta, ci avevano presi. Devo riconoscere un certo merito al costruttore di navi: si prese tutta la colpa, dichiarò che la resina era roba sua e che io non c’entravo nulla. Alla fine, lui in catene e le mie monete sparite. Tutto il pasticcio col convoglio spagnolo è stato solo una perdita di tempo e denaro, anche se ho avuto la fortuna di non finire in galera. Riempimi ancora il bicchiere, messer Gregoire.";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			dialog.text = "Dunque, il costruttore di navi è finito in gattabuia?";
			link.l1 = "Ebbene sì. È stato portato in prigione proprio da quell’ufficiale di cui ti parlavo. Dovevi vederli.";
			link.l1.go = "greguar_11";
		break;
		
		case "greguar_11":
			dialog.text = "Sì, li ho visti entrambi, anche se mai avrei pensato che il tenente Felicien Gronier potesse davvero mettere in ceppi il suo vecchio compare.";
			link.l1 = "C-cosa hai appena detto?";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "Hai sentito bene. Il tenente Felicien Gronier e il costruttore navale "+GetFullName(characterFromId("FortFrance_shipyarder"))+" sono vecchi compari. Un tempo servivano insieme nell’esercito, laggiù in Europa. Gronier è rimasto sotto le armi e "+GetFullName(characterFromId("FortFrance_shipyarder"))+" è riuscito ad avviare la propria attività.";
			link.l1 = "Quindi si conoscono... Ora capisco...";
			link.l1.go = "greguar_13";
		break;
		
		case "greguar_13":
			dialog.text = "Mio caro "+pchar.name+", pare che ti abbiano fregato. Sei ancora un novellino da queste parti e se ne sono approfittati. Scommetto cento dobloni che monsieur "+GetFullName(characterFromId("FortFrance_shipyarder"))+" tornerà a passeggiare per il suo cantiere navale tra tre giorni o anche prima.";
			link.l1 = "Pare proprio che tu abbia ragione, monsieur. Mi hanno fregato per bene. Non c’era modo che quell’ufficiale sapesse della resina. Tempismo perfetto, maledizione.";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			dialog.text = "Questi sono i Caraibi, monseniore "+pchar.name+"  Fatti il callo. Dimentica le apparenze, qui il peggio del peggio ha sempre l’aria d’un gran signore.";
			link.l1 = "Questa frase l’ho già sentita da qualche parte... Che dovrei farne di loro? Devo forse rivolgermi al governatore?";
			link.l1.go = "greguar_15";
		break;
		
		case "greguar_15":
			dialog.text = "Temo che in questo caso "+GetFullName(characterFromId("FortFrance_shipyarder"))+" racconterai loro un'altra storia e finirai nei ceppi.";
			link.l1 = "Ma guarda un po'. Va bene, allora! Se la legge non è dalla mia parte, farò a modo mio, maledizione! Non mi arrenderò così facilmente.";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			dialog.text = "Per favore, calmati "+pchar.name+"   È il rum e la rabbia che parlano, non tu. Fatti una dormita e poi ripensaci. Forse ti conviene lasciar perdere. Tenente Felicien Gronier e "+GetFullName(characterFromId("FortFrance_shipyarder"))+" qui ci sono dei pezzi grossi, sono ben al di sopra della tua portata. Non fare sciocchezze.";
			link.l1 = "Vedremo. Ti ringrazio per avermi aperto gli occhi. È una fortuna averti incontrato.";
			link.l1.go = "greguar_17";
		break;
		
		case "greguar_17":
			dialog.text = "Sta' attento. Ricòrdati bene quello che t'ho detto.";
			link.l1 = "Lo farò. Ora beviamoci un ultimo bicchiere!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_OutTavern");
		break;
		
		case "greguar_18":
			PlaySound("Voice\English\LE\Greguar\Greguar_03.wav");
			dialog.text = "Capitano "+GetFullName(pchar)+"!";
			link.l1 = "Oh, messer Gregoire! Di nuovo voi!";
			link.l1.go = "greguar_19";
		break;
		
		case "greguar_19":
			dialog.text = "Sì. Dopo la nostra chiacchierata in taverna ho fatto delle indagini sul tenente Felicien Gronier. Pare che abbia chiesto dieci giorni di licenza non molto tempo fa. La sua richiesta è stata accolta. L'ho visto oggi, ha preso una scialuppa verso una tartana che è subito salpata per la Guadalupa. Si chiama la Topazio\nTi ho detto tutto, ora tocca a te. Sono certo che puoi cogliere il filo che lega la richiesta improvvisa di Gronier e la sua partenza dall'isola su una tartana fresca di cantiere.";
			link.l1 = "Maledizione, adesso mi è tutto chiaro come il sole, senza dubbio! Questa tartana ha la mia resina nascosta nella stiva! Monsignore Gregoire, vi ringrazio, mi avete proprio salvato la pellaccia! Posso sdebitarmi in qualche modo, ditemi voi?";
			link.l1.go = "greguar_20";
		break;
		
		case "greguar_20":
			dialog.text = "Oh, andiamo amico mio. Siamo gentiluomini, dobbiamo aiutarci l’un l’altro. Così si vive da queste parti. Credo che avresti fatto lo stesso se fossi nei miei panni. Non perdere tempo, veleggia verso nord e trova quell’ufficiale. Non combattere, seguilo soltanto e scopri che diavolo sta tramando. Sbrigati, capitano!";
			link.l1 = "Grazie ancora!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_HurryToSea");
		break;
		
		case "pirate":
			dialog.text = "Cosa stai guardando? Che diavolo vuoi qui?";
			link.l1 = "Ehi compare, sono qui per riprendermi la mia roba. Vedi quelle botti laggiù? È la mia resina, e non mi hanno dato nemmeno un soldo bucato.";
			link.l1.go = "pirate_1";
			DelLandQuestMark(characterFromId("FMQM_Enemy_crew_2"));
		break;
		
		case "pirate_1":
			dialog.text = "Sei scemo o cosa? Sparisci finché hai ancora le gambe!";
			link.l1 = "Ho faticato troppo per ottenere questa resina per lasciare che qualche lurido mascalzone mi fermi.";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "Seppelliremo qui il tuo bel completo, canaglia!";
			link.l1 = "Oh che gentile da parte tua proporre una sepoltura, ma temo che dovremo semplicemente lasciarti qui sulla spiaggia a far banchettare i gabbiani con le tue budella!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_ShoreFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

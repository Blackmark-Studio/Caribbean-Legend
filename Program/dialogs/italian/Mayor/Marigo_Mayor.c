// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa vuoi? Chiedi pure.","Ti sto ascoltando, qual è la domanda?"),"Questa è la seconda volta che provi a chiedere...","Questa è la terza volta che provi a chiedere...","Quando finirà tutto questo?! Sono un uomo impegnato, lavoro su questioni coloniali e tu continui a infastidirmi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ora. Luogo e tempo sbagliati."),"Vero... Ma più tardi, non ora...","Chiederò... Ma un po' più tardi...","Mi dispiace, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToGovernor")
			{
				link.l1 = "Vostra Grazia, ho delle notizie assolutamente eccellenti e urgenti per voi! Ho catturato Bartolomeo il Portoghese, il bastardo è sotto custodia e cerca un processo equo! E io sto cercando una qualche modesta gratitudine della Compagnia...";
				link.l1.go = "Portugal";
			}
			//Португалец
			
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "governor")
			{
				link.l1 = "Insistevate nel vedermi, signor governatore...";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_battle_complete")
			{
				link.l1 = "Sono qui per questioni riguardanti le spie inglesi, signor governatore...";
				link.l1.go = "FMQN_7";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Hai già preso tutto. Cosa vuoi ancora?","C'è rimasto qualcosa che non hai preso?");
            link.l1 = RandPhraseSimple("Solo dando un'occhiata...","Solo un controllo, potrei dimenticare di prendere qualcosa...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		//Jason, Португалец
		case "Portugal":
			dialog.text = "Bartolomeo... Bart il Portoghese è nella mia città?! Vivo?!!";
			link.l1 = "Egli è, vostra Grazia, ed è sotto una guardia affidabile. Lo consegnerò a voi dopo aver ricevuto una fattura per la testa di Bart che era stata promessa dalla Compagnia. Anche i dobloni d'oro andrebbero bene...";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Bill, dobloni? Sei pazzo?! Cosa pensavi, portando questa bestia nella mia città?! Se lui è qui, allora la sua fregata non è lontana dall'isola e il suo equipaggio potrebbe essere proprio in città, proprio adesso!";
			link.l1 = "Ho ucciso coloro che erano con lui, non so degli altri, ma suppongo che non importi davvero perché Bartolomeo è...";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Certo che lo fa! Non capisci veramente cosa hai fatto?! L''Albatros' è vicino all'isola e hai catturato il pirata la cui brutalità spaventa persino il suo stesso popolo sanguinario! Vattene da qui! Lascia l'isola! E porta via questo mostro con te!";
			link.l1 = "Ma ascolta, che ne è stato della ricompensa promessa e...";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "Non voglio vedere la mia città bruciare a causa della tua avidità e della vendetta della Compagnia! Nel mio forte ci sono solo nuove reclute e metà di loro scapperanno appena scopriranno chi e perché attacca le loro ravelins! E poi inizierà la strage... Non sto per rischiare, mi senti?! Smettila e consegnalo tu stesso a Curacao se la Compagnia vuole così tanto la sua testa!\nFallo subito prima che sia troppo tardi! E puoi farci quello che vuoi, anche gettarlo fuori dal ponte della tua nave, basta che non lo faccia nella mia città!\nHans! Hans, dov'è, stupido pigro! Portami una pozione di valeriana o qualcosa del genere e qualcuno, per l'amor di Dio, per favore cacci questo avventuriero dalla mia residenza!";
			link.l1 = "Ma vostra Grazia...";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			DialogExit();
			DoQuestReloadToLocation("Marigo_town", "reload", "reload3_back", "PortugalOutResidence");
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "Molto bene! Dimmi capitano, hai incontrato qualche nave militare o commerciale inglese mentre ti avvicinavi alla nostra isola?";
			link.l1 = "No, Mynheer. Non ho visto né navi militari, né mercantili sotto bandiera inglese nelle vostre acque.";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Capisco. Per quanto tempo prevedi di restare qui?";
			link.l1 = "Circa tre giorni...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = "In tal caso, ho un'offerta per te. Secondo le nostre informazioni, c'è il rischio di spie inglesi qui. Darò diecimila pesos come ricompensa per qualsiasi informazione riguardante navi e persone sospette nell'isola, in città, nelle sue vicinanze, sulle coste, ecc. La ricompensa sarà significativamente aumentata in caso di assistenza alle autorità nell'arresto o nell'eliminazione di un nemico.\nOgni capitano civile è invitato a partecipare all'indagine e a perlustrare le coste e la giungla locali alla ricerca delle spie.\nÈ possibile che tu incontri la nostra corvetta militare, la Zeepard, non aver paura, è in pattuglia. Sei libero di rivolgerti al suo capitano nel caso in cui trovi gli inglesi.";
			link.l1 = "Ahimè, vostra Eccellenza, ma sono qui solo con intenzioni di commercio pacifico. Dovrò lasciare quest'isola non appena mi rifornisco e finisco i miei affari qui.";
			link.l1.go = "FMQN_3";
			link.l2 = "Un'offerta allettante! Credo che parteciperò e saccheggerò le acque e le coste della tua isola. Potrei anche restare qui per un po'.";
			link.l2.go = "FMQN_5";
		break;
		
		case "FMQN_3":
			dialog.text = "È solo informazione gratuita, capitano. Nessuna pressione. Sai a chi rivolgerti nel caso in cui noti qualcosa di sospetto.";
			link.l1 = "Molto bene, Mynheer, ho capito. Addio!";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			DialogExit();
			pchar.questTemp.FMQN = "way_eng_1";
			AddQuestRecord("FMQ_Nevis", "8");
			chrDisableReloadToLocation = false;
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_5":
			dialog.text = "Splendido, capitano! Dato che sei così serio, assicurati di parlare anche con il nostro comandante. È responsabile della cattura delle spie e potrebbe darti informazioni aggiuntive.";
			link.l1 = "Bene, Mynheer. Andrò a vederlo.";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			DialogExit();
			pchar.questTemp.FMQN = "way_div";
			AddQuestRecord("FMQ_Nevis", "9");
			chrDisableReloadToLocation = false;
			AddLandQuestMarkToPhantom("marigo_prison", "marigoJailOff");
		break;
		
		case "FMQN_7":
			DelLandQuestMark(npchar);
			dialog.text = "La stavamo aspettando, Mynheer "+GetFullName(pchar)+". Permettimi di esprimere la nostra gratitudine per le tue azioni nell'eliminare la pericolosa squadra d'assalto inglese. Accetta questi diecimila pesos. Inoltre: 200 sete di nave saranno caricate nella stiva della tua nave e una ricompensa molto speciale - una licenza triennale della Compagnia Olandese delle Indie Occidentali. Questo è un documento estremamente prezioso, spero tu lo sappia?";
			link.l1 = "Certo! Una licenza di tre anni - è sicuramente importante.";
			link.l1.go = "FMQN_8";
		break;
		
		case "FMQN_8":
			dialog.text = "Per favore, prendi la tua ricompensa. Inoltre, puoi contare sulla gratitudine di tutti i cittadini e le autorità olandesi. Sei una sensazione a Philipsburg, saremmo lieti di rivederti.";
			link.l1 = "Sentire parole così calorose è più prezioso della licenza. Grazie, è stato un piacere. E ora, dovrei mettermi in viaggio. Arrivederci!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandBattleComplete");
		break;
		
		// Jason НСО
		case "tomas":
			dialog.text = "Ci arrendiamo! In nome di tutto ciò che è sacro, ti prego, non saccheggiare e depredare Philipsburg e i suoi cittadini! Sono pronto ad ascoltare le tue richieste!";
			link.l1 = "Non preoccuparti dei cittadini, Mynheer. I sudditi della Corona Francese non dovrebbero temere i soldati francesi.";
			link.l1.go = "tomas_1";
		break;
		
		case "tomas_1":
			dialog.text = "La Corona Francese?";
			link.l1 = "Esattamente. Quest'isola appartiene alla Francia, e voi siete solo affittuari qui. Affittuari impudenti, che credevano che quest'isola potesse essere di loro proprietà. Da oggi in poi, l'autorità olandese a Saint Maarten è giunta al termine. È chiaro?";
			link.l1.go = "tomas_2";
		break;
		
		case "tomas_2":
			dialog.text = "Ma ... Ma cosa succederà a noi, con i soldati olandesi che si sono arresi a te, e i feriti? E cosa...";
			link.l1 = "Ciò dipenderà solo da te, Mynheer Thomas. Se mi farai un favore, allora permetterò a tutti coloro che si sono arresi di prendere i loro feriti e partire da qui su una o più navi che troveremo nei moli, per Curacao, al Mynheer Stuyvesant.";
			link.l1.go = "tomas_2_1";
		break;
		
		case "tomas_2_1":
			dialog.text = "";
			link.l1 = "Altrimenti sarete trattenuti nelle stive delle mie navi e nei casamatti di Saint Kitts. Inoltre, alcuni importanti funzionari olandesi dovranno essere impiccati, solo per assicurarsi che Stuyvesant perda il suo interesse a conquistare le nostre colonie...";
			link.l1.go = "tomas_3";
		break;
		
		case "tomas_3":
			dialog.text = "(balbettando) Co... Cosa... a pro...po...sito di che ge...ge...nere di fa...vo...re?";
			link.l1 = "Nelle profondità dell'isola si trova un osso di contesa - una miniera di sale. So che non ci sono solo minatori e schiavi, ma anche soldati olandesi, armati fino ai denti. Devono essere della Guardia della Compagnia, non è vero, Mynheer? Offrirò loro di arrendersi, o userò la forza in caso di rifiuto. Ho bisogno di una guida che mi mostri la strada per la miniera. Trovami una tale guida.";
			link.l1.go = "tomas_4";
		break;
		
		case "tomas_4":
			dialog.text = "S-Sale....m-mia?";
			link.l1 = "Esattamente. Non aver paura, Mynheer Thomas, se le guardie della miniera sono abbastanza sagge da arrendersi, darò loro l'opportunità di lasciare l'isola. Non ho bisogno di spargimenti di sangue inutili. Non preoccuparti, la tua coscienza sarà pulita: anche se non mi dici dove si trova la miniera, l'isola di Saint Maarten è abbastanza piccola da permettermi di trovare la miniera senza il tuo aiuto, semplicemente non voglio sprecare il mio tempo, vagando tra cespugli e paludi. Quindi questo affare è più vantaggioso per te che per me.";
			link.l1.go = "tomas_5";
		break;
		
		case "tomas_5":
			dialog.text = "B-be...ne, ti dirò come arrivare alla miniera, m-ma devi pro...mettere che tutti... tutti noi lasceremo quest'isola!";
			link.l1 = "Ti do la mia parola come ufficiale e nobile.";
			link.l1.go = "tomas_6";
		break;
		
		case "tomas_6":
			dialog.text = "Nella baia di Grand Case... al suo estremo, vicino all'acqua, ci sono... ci sono delle pietre. Lì... là, dietro di loro, lungo la riva, c'è un passaggio lungo l'acqua, lì... è basso lì, profondo fino alla cintura o meno. Devi andare intorno alla roccia e arriverai a una grande spiaggia, dove... dove non puoi attraccare la tua nave a causa delle barriere coralline attorno. Da questa spiaggia c'è un sentiero direttamente... verso... verso la miniera.";
			link.l1 = "Eccellente. Sto partendo. E tu, Mynheer, rimarrai qui sotto la diligente sorveglianza dei miei soldati fino al mio ritorno.";
			link.l1.go = "tomas_7";
		break;
		
		case "tomas_7":
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			LAi_SetActorType(npchar);
			pchar.quest.Patria_BastionGate.win_condition.l1 = "location";
			pchar.quest.Patria_BastionGate.win_condition.l1.location = "Shore40";
			pchar.quest.Patria_BastionGate.function = "Patria_BastionShore";
			AfterTownBattle();
			AddQuestRecord("Patria", "50_1");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

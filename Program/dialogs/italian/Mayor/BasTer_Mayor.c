// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa desideri? Chiedi pure.","Ti sto ascoltando, qual è la domanda?"),"È la seconda volta che provi a chiedere...","È la terza volta che stai di nuovo cercando di chiedere...","Quando finirà?! Sono un uomo occupato, che lavora sulle questioni della colonia e tu stai ancora cercando di chiedere qualcosa!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ora. Luogo e momento sbagliati."),"Vero... Ma più tardi, non ora...","Chiederò... Ma un po' più tardi...","Mi dispiace, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "Ho una questione delicata per te. Non molto tempo fa, un corsaro ha donato una croce d'oro con un lapislazzuli alla parrocchia di Basse-Terre. Il problema è che la croce è stata rubata dalla parrocchia di Santiago e un religioso è stato assassinato durante il furto...";
                link.l1.go = "guardoftruth";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "Sono arrivato per ordine del Governatore Generale Philippe de Poincy per assumere il comando della vostra fregata armata.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < 5)
			{
				link.l1 = "Sono pronto a portare la fregata nella squadra.";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "baster")
			{
				link.l1 = "Ho un incontro qui con una persona...";
                link.l1.go = "baster_goldengirl";
			}
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_guber_1"))
			{
				link.l1 = "Signore, ho intenzione di intraprendere attività commerciali in città. Specificamente, sono interessato al costante commercio su larga scala di spiriti.";
				link.l1.go = "TPZ_guber_1";
			}
			//<-- Торговля по закону

		break;
		//************************** Квестовые штрумы ************************
		case "Cupture_after":
            dialog.text = RandPhraseSimple("Hai già preso tutto. Cosa vuoi ancora?","C'è qualcosa che non hai preso?");
            link.l1 = RandPhraseSimple("Solo dando un'occhiata...","Solo un controllo, potrei dimenticare di prendere qualcosa...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "guardoftruth":
			dialog.text = "Mh. Questo è abbastanza interessante. Ma perché pensi che mi importi dei problemi degli spagnoli?";
			link.l1 = "Non si tratta degli spagnoli, Monsieur. La religione non divide le persone per nazionalità. C'è un oggetto coperto dal sangue del santo servitore nella tua parrocchia e c'è stata una profanazione fatta alla parrocchia di Santiago...";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "";
			link.l1 = "Vi chiedo di mostrare giustizia e di ordinare al santo padre di restituire la croce ai suoi proprietari.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "E da quando sei diventato un credente così sincero e devoto, eh, "+pchar.name+"? Gli spagnoli non sono nostri amici e non vedo alcun motivo per coinvolgere il santo padre in questa questione. La croce era un dono ed è tutto a posto. Il nostro prete non ha alcuna connessione con quel furto e omicidio, quindi...";
			link.l1 = "E non puoi aiutarmi, vero?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Ad essere onesto, "+pchar.name+", Non sento che io debba. Non provo amore per quei fanatici Papisti.";
			link.l1 = "Capisco. Mi scuso per il disturbo, Monsieur...";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			npchar.quest.utensil = "true";
			AddQuestRecord("Guardoftruth", "28");
		break;
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "La nave è pronta, ma non hai un posto libero per essa nella tua squadra. Capitano, riduci la tua squadra e torna, allora ti darò immediatamente la fregata.";
				link.l1 = "Bene.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "Sì, certo, la nave è pronta a salpare. Il suo capitano è informato e seguirà tutti i vostri ordini.";
				link.l1 = "Allora ci mettiamo in viaggio. Addio, Vostra Grazia.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "Eccellente. Preparati ad accogliere la tua nuova nave. Il suo capitano è informato e seguirà tutti i tuoi ordini.";
			link.l1 = "Allora partiamo. Addio, Vostra Grazia.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateGlp(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "baster_goldengirl":
			dialog.text = "Ah, Monsieur Charles de Maure, arrivi al momento giusto! Il mio vecchio amico è molto ansioso di conoscerti e ha chiesto di fargli sapere del tuo arrivo. Per favore, vieni nel mio salotto, informerò immediatamente Angerran. Come vi siete conosciuti tra l'altro?";
			link.l1 = "Abbiamo giocato d'azzardo insieme. Lui ha perso, abbiamo avuto una piccola lite. Suppongo che Monsieur de Chievous vorrebbe sistemare le cose tra di noi.";
			link.l1.go = "baster_goldengirl_1";
		break;
		
		case "baster_goldengirl_1":
			dialog.text = "Senza dubbio! Spero che riuscirai a mettere le cose in chiaro tra voi due. Angerran potrebbe non essere la persona più piacevole con cui avere a che fare, ma è astuto e onorevole, proprio come te. È una razza rara.";
			link.l1 = "Mi lusinga, Eccellenza. Lo aspetterò nel salotto se non le dispiace.";
			link.l1.go = "baster_goldengirl_2";
		break;
		
		case "baster_goldengirl_2":
			dialog.text = "Ma certo, fai come se fossi a casa tua. Forse dovrai aspettare un po'. Ordinerò di portare da bere.";
			link.l1 = "Grazie, Eccellenza, ma declino. Mi siederò semplicemente ad aspettare il nostro... amico comune.";
			link.l1.go = "baster_goldengirl_3";
		break;
		
		case "baster_goldengirl_3":
			DialogExit();
			pchar.questTemp.GoldenGirl = "baster1";
			DoQuestReloadToLocation("CommonResidence_3", "reload", "reload1", "GoldenGirl_AngerranInResidence");
		break;
		
		//--> Торговля по закону
		case "TPZ_guber_1":
			dialog.text = "Capitano, sei stato saggio nel cercarmi. Stiamo facendo ogni sforzo per combattere il commercio illecito su quest'isola, e accogliamo veramente i capitani onesti che cercano di stabilire affari attraverso canali legali.";
			link.l1 = "Allora, quali sono i termini e i passaggi necessari per iniziare il commercio?";
			link.l1.go = "TPZ_guber_2";
			DelLandQuestMark(npchar);
		break;

		case "TPZ_guber_2":
			dialog.text = "È piuttosto semplice. Per commerciare in liquori, devi pagare una tassa mensile di cento dobloni al tesoro, mantenere registri adeguati e presentare rapporti regolari sull'attività. Una volta depositati i fondi, puoi iniziare a fare commercio sul serio.";
			link.l1 = "Eccellente. I termini sono assolutamente ragionevoli. Un residente locale di nome Christian Deluce agirà per mio conto. Spero che non ci siano problemi?";
			link.l1.go = "TPZ_guber_3";
		break;

		case "TPZ_guber_3":
			dialog.text = "Come desideri, Capitano. Ma tieni a mente - la piena responsabilità del tuo protetto ricadrà sulle tue spalle. Se dovesse trasgredire, condividerai le sue conseguenze.";
			link.l1 = "Certo. Grazie per la chiarificazione, Governatore. Faremo gli accordi, e Christian si occuperà del pagamento delle tasse.";
			link.l1.go = "TPZ_guber_4";
		break;

		case "TPZ_guber_4":
			dialog.text = "Splendido. Sono lieto di vedere un approccio così diligente. Ti auguro successo nella tua impresa.";
			link.l1 = "Molto obbligato. Confido che la nostra cooperazione beneficerà la città. Addio.";
			link.l1.go = "TPZ_guber_5";
		break;

		case "TPZ_guber_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.TPZ_guber_1");
			AddQuestRecord("TPZ", "11");

			sld = CharacterFromID("TPZ_Kristian");
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_21";
			ChangeCharacterAddressGroup(sld, "BasTer_houseF3", "barmen", "stay");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

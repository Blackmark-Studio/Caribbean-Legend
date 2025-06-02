// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti, "+GetAddress_Form(NPChar)+"?"),"Cosa c'è, "+GetAddress_Form(NPChar)+"...","Questa è la terza volta che mi disturbi...","Altre domande, presumo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho nulla di cui parlare al momento."),"Uh, dove se n'è andata la mia memoria...","Sì, è davvero la terza volta...","No, quali domande?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
			{
				link.l1 = "Cerco il mio vecchio compagno di bordo Fernand Luc. Ho un paio di domande per lui. Ho sentito dire che si è divertito molto qui una settimana fa...";
				link.l1.go = "terrapin";
			}
			//Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTavern"))
			{
				link.l1 = "Io e il mio amico abbiamo concordato di incontrarci qui, ma non lo vedo da nessuna parte. Sai dove è andato? È ancora in città, o almeno sull'isola? Il suo nome è Longway - è cinese.";
				link.l1.go = "PZ_BasTerTavern_1";
			}
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_2"))
			{
				link.l1 = "Buone notizie, "+npchar.name+". Ho esattamente ciò che salverà la tua situazione. Cento bottiglie di eccellente vino e cento bottiglie di rum. Con un tale carico i tuoi clienti si bagneranno di nuovo nei fiumi di alcol. Sei pronto a pagare?";
				link.l1.go = "TPZ_Tavern2_1";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_3"))
			{
				link.l1 = "Allora, "+npchar.name+", sei pronto a discutere i termini dell'accordo?";
				link.l1.go = "TPZ_Tavern2_11";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_4"))
			{
				link.l1 = "Allora, "+npchar.name+". Da parte mia, tutto è sistemato e le merci sono già in viaggio verso la taverna. Procediamo con il pagamento?";
				link.l1.go = "TPZ_Tavern3_1";
			}
			//<-- Торговля по закону
		break;
		
		//суп из черепахи
		case "terrapin":
			dialog.text = "Potrebbe ancora divertirsi mentre è all'inferno. Il tuo compagno è morto, quindi sei un po' in ritardo, capitano. Quell'uomo laggiù seduto al tavolo più lontano ha pagato per il suo funerale, anche se ho la sensazione che sia lo stesso uomo che l'ha causato. Ha una faccia da impiccato, come si suol dire. Il suo nome è Robert Martene. Se vuoi, puoi andare da lui e chiederglielo tu stesso. ";
			link.l1 = "Grazie, compagno. Andrò a parlare con monsieur Robert. Berrò per l'anima del povero vecchio Luc affinché la sua anima possa riposare in pace...";
			link.l1.go = "terrapin_1";
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_1":
			DialogExit();
			AddQuestRecord("Terrapin", "4");
			pchar.questTemp.Terrapin = "rober";
		break;
		
		// Sinistra - Квест "Длинные тени старых грехов" ==>
		case "DTSG_BasTerTavern_1":
			dialog.text = "Cosa c'è da discutere? Ha attaccato te e il tuo amico, tu hai reagito, vedo questo quasi ogni giorno. Buon lavoro. Ora devo solo pulire il casino...";
			Link.l1 = "Lo pulirai, sono sicuro che ormai ci sei abituato. Cosa sai di lui?";
			Link.l1.go = "DTSG_BasTerTavern_2";
		break;
		
		case "DTSG_BasTerTavern_2":
			dialog.text = "Non molto, davvero. È arrivato un paio di giorni fa. Gli piaceva qui, ha persino affittato una casa alla periferia della città. Veniva spesso, pagava regolarmente. E, soprattutto, si è comportato bene tutto il tempo, non ha mai detto una parola cattiva a nessuno. Sono ancora scioccato che ti abbia attaccato tu e il tuo amico\nPensavo che potesse stabilirsi qui per sempre.";
			Link.l1 = "In un certo senso, lo ha fatto. Beh, non è molto, ma grazie per questo, amico mio. Ci vediamo in giro.";
			Link.l1.go = "DTSG_BasTerTavern_3";
		break;
		
		case "DTSG_BasTerTavern_3":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_BasTerTavern");
			LAi_LocationDisableOfficersGen("BasTer_tavern", false);
			SetQuestHeader("DTSG");
			AddQuestRecord("DTSG", "1");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			Return_KnippelOfficer();
			
			PChar.quest.DTSG_BasTerDom.win_condition.l1 = "locator";
			PChar.quest.DTSG_BasTerDom.win_condition.l1.location = "BasTer_town";
			PChar.quest.DTSG_BasTerDom.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_BasTerDom.win_condition.l1.locator = "HutFish1";
			PChar.quest.DTSG_BasTerDom.win_condition = "DTSG_BasTerDom";
			
			SetTimerCondition("DTSG_BasTerDom_Timer", 0, 0, 7, false);
			SetTimerCondition("DTSG_Etap2", 0, 0, 14, false);
		break;
		// <== Квест "Длинные тени старых грехов" - Sinistra
		
		// Sinistra - Квест "Путеводная звезда" ==>
		
		case "PZ_BasTerTavern_1":
			dialog.text = "Quel nome non significa nulla per me, e in generale, non lascio entrare persone come lui nel mio locale, né mi interesso a loro.";
			Link.l1 = "Giusto. Bene, ci vediamo dopo.";
			Link.l1.go = "PZ_BasTerTavern_2";
		break;
		
		case "PZ_BasTerTavern_2":
			DialogExit();
			bDisableLandEncounters = true;
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTavern");
			DeleteAttribute(pchar, "questTemp.PZ_BasTerAlkash");
			pchar.questTemp.PZ_BasTerTavern2 = true;
			DeleteQuestCondition("PZ_BasTer_Opozdal");
			DelMapQuestMarkIsland("Guadeloupe");
			
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1 = "location";
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1.location = "BasTer_town";
			PChar.quest.PZ_BasTer_Strazha.win_condition = "PZ_BasTer_Strazha";
		break;
		
		// <== Квест "Путеводная звезда" - Sinistra
		
		//--> Торговля по закону
		case "TPZ_Tavern_1":
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+", è ancora peggio di così. Il mio fornitore da Antigua ha perso la sua distilleria - i pirati l'hanno saccheggiata, tutto bruciato fino al suolo. Ora dice che non dovremmo aspettarci rum o vino per almeno due mesi.";
			link.l1 = "Allora trova un nuovo fornitore. Non starai certo seduto ad aspettare per due mesi, vero?";
			link.l1.go = "TPZ_Tavern_2";
		break;
		
		case "TPZ_Tavern_2":
			dialog.text = "Trovare un fornitore affidabile non è facile. Ho provato a trattare con piccoli commercianti, ma sono inaffidabili. A volte la merce arriva, a volte no. Con un grande fornitore, tutto funziona come un orologio: consegne stabili e alta qualità.";
			link.l1 = "Ebbene, se i fornitori normali sono un problema, forse dovresti cercare qualcuno nell'ombra? Raramente ti deludono, e le merci sono sempre disponibili.";
			link.l1.go = "TPZ_Tavern_3";
		break;
		
		case "TPZ_Tavern_3":
			dialog.text = "Capisci, "+GetAddress_Form(NPChar)+", questa taverna è sotto l'occhio pubblico. Non voglio guai con le autorità. Se qualcuno con una solida reputazione portasse la merce, non solo comprerei un lotto, ma chiuderei volentieri un occhio su da dove proviene\nDopotutto, quando la situazione è così disperata, a chi importano tali banalità? La cosa principale è evitare sospetti. Ma a lungo termine, tratterò solo con mercanti seri e onesti.";
			link.l1 = "Capisco. Beh, forse passerò di nuovo più tardi. Qualsiasi problema può essere risolto con un approccio intelligente.";
			link.l1.go = "TPZ_Tavern_4";
		break;
		
		case "TPZ_Tavern_4":
			DialogExit();
			AddQuestRecord("TPZ", "2");
			pchar.questTemp.TPZ_ContraInfo = true;
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
		break;
		
		case "TPZ_Tavern2_1":
			dialog.text = "Capitano, questo è incredibile! Come hai fatto a farcela? Non importa, davvero. Dimmi solo, cosa vuoi in cambio per un carico così lussuoso di alcol? E tutto sarà a posto con i documenti?";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Documenti? Naturalmente è tutto perfettamente in ordine. Non stai davvero pensando di controllarlo, vero?";
				link.l1.go = "TPZ_Tavern2_2";
				notification("Honor check passed", "None");
			}
			else
			{
				link.l1 = "Documentazione?";
				link.l1.go = "TPZ_Tavern2_2_badrep";
				notification("Honor level too low! ("+XI_ConvertString(GetReputationName(40))+")", "None");
			}
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_2");
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_Tavern2_2_badrep":
			dialog.text = "Capitano, per favore capisci, è vitale per me ottenere questa spedizione di alcol. Ma la mia libertà e la mia reputazione sono altrettanto preziose. Il governatore è spietato con i trafficanti del mercato nero, anche i più piccoli. Se la gente parlasse bene di te, potrei chiudere un occhio sulla mancanza di documenti, ma adesso... stai attirando troppa attenzione indesiderata...";
			link.l1 = "Sembra che sia il momento di fare qualche buona azione. Aspettami, tornerò presto.";
			link.l1.go = "exit";
			pchar.questTemp.TPZ_Tavern_3 = true;
		break;
		
		case "TPZ_Tavern2_2":
			dialog.text = "Questa volta, suppongo che mi fiderò della tua parola. Quindi, quanto vuoi per il lotto?";
			link.l1 = "Voglio trenta dobloni per ogni dieci bottiglie di vino, e cinque dobloni per ogni dieci bottiglie di rum. L'intero lotto - cento bottiglie di ciascuno - ti costerà trecentocinquanta dobloni.";
			link.l1.go = "TPZ_Tavern2_3";
		break;
		
		case "TPZ_Tavern2_3":
			dialog.text = "Fermati, Capitano! Questo è un furto in pieno giorno! Sì, la mia situazione è disperata, ma non gestirò la mia attività in perdita!";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 50)
			{
				link.l1 = "Forse posso darti uno sconto. Ma non è tutto. Voglio essere il tuo fornitore abituale. Garantisco consegne regolari e puntuali. Affitterò un magazzino a Basse-Terre, e riceverai la tua merce direttamente da lì senza ritardi. Ci sarà sempre abbastanza alcol immagazzinato per prevenire qualsiasi carenza. Con lo sconto, il prezzo sarà di duecentoquaranta dobloni. Cosa ne dici?";
				link.l1.go = "TPZ_Tavern2_4";
				notification("Check passed", SKILL_COMMERCE);
			}
			else
			{
				link.l1 = "Bene, sono disposto a ridurre il prezzo a duecentoquaranta dobloni per spedizione, puntando a una partnership a lungo termine. In futuro, posso soddisfare tutte le vostre esigenze e garantire un approvvigionamento affidabile. Cosa ne dici?";
				link.l1.go = "TPZ_Tavern2_7";
				notification("Skill too low (50)", SKILL_COMMERCE);
			}
		break;
		
		case "TPZ_Tavern2_4":
			dialog.text = "È ancora più di quanto ero solito pagare. Ma ho imparato la mia lezione: la stabilità vale il prezzo. Accetto i tuoi termini, ma sappi questo: un solo errore, e troverò un altro fornitore. Devo capire per cosa sto pagando di più. E un'altra cosa: come pensi di gestire le autorità?";
			link.l1 = "Me ne occuperò subito. Una volta sistemato tutto, tornerò con la merce.";
			link.l1.go = "TPZ_Tavern2_5";
		break;
		
		case "TPZ_Tavern2_5":
			dialog.text = "Per favore, non indugiare. Non vedo l'ora di vedere di nuovo i boccali dei miei clienti pieni.";
			link.l1 = "Non preoccuparti, non ti farò aspettare.";
			link.l1.go = "TPZ_Tavern2_6";
		break;
		
		case "TPZ_Tavern2_6":
			DialogExit();
			AddQuestRecord("TPZ", "5");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino240 = true;
			
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
	    case "TPZ_Tavern2_7":
			dialog.text = "È ancora troppo costoso, Capitano. Questo prezzo è superiore a quello che pagavo al mio fornitore precedente. Anche se accetto ora, tra qualche mese dovrò tornare da lui una volta ripresa la produzione. Non vedo motivo di pagare di più.";
			link.l1 = "Capisco. Va bene. La mia offerta finale — duecento dobloni. Se non è accettabile, allora non c'è motivo di continuare questa conversazione.";
			link.l1.go = "TPZ_Tavern2_8";
		break;
		
		case "TPZ_Tavern2_8":
			dialog.text = "Va bene, accordo. Duecento è accettabile. Ma dimmi, come pensi di gestire le autorità dell'isola? Come ho detto prima, il governatore controlla rigorosamente l'isola per il contrabbando. Non tollererà affari che avvengono proprio sotto il suo naso.";
			link.l1 = "Ha-ha, beh, discuterei su questo. Ma stai tranquillo — ho intenzione di superare tutti gli ostacoli burocratici in fretta.";
			link.l1.go = "TPZ_Tavern2_9";
		break;
		
		case "TPZ_Tavern2_9":
			dialog.text = "Per favore, non indugiare. Non vedo l'ora di vedere di nuovo le pinte dei miei clienti piene.";
			link.l1 = "Non preoccuparti, non ti farò aspettare.";
			link.l1.go = "TPZ_Tavern2_10";
		break;
		
		case "TPZ_Tavern2_10":
			DialogExit();
			AddQuestRecord("TPZ", "6");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino200 = true;
		break;
		
		case "TPZ_Tavern2_11":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "Certo, Capitano! Quindi, quanto vuoi per la tua spedizione?";
				link.l1 = "Per ogni dieci bottiglie di vino voglio trenta dobloni, e cinque dobloni per ogni dieci bottiglie di rum. L'intera spedizione - cento bottiglie di ciascuno - ti costerà trecento cinquanta dobloni.";
				link.l1.go = "TPZ_Tavern2_3";
				notification("Honor check passed", "None");
			}
			else
			{
				dialog.text = "Mi dispiace, Capitano, ma la tua reputazione lascia ancora molto a desiderare.";
				link.l1 = "Maledizione...";
				link.l1.go = "exit";
				notification("Honor too low! ("+XI_ConvertString(GetReputationName(40))+")", "None");
			}
		break;
		
		case "TPZ_Tavern3_1":
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				dialog.text = "Certo, Capitano, certo! 240 dobloni, proprio come concordato. Ecco a lei!";
				link.l1 = "Un piacere fare affari con te! Ora la taverna traboccherà di nuovo di rum e vino.";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 240);
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				dialog.text = "Certo, Capitano, certo! 200 dobloni, proprio come concordato. Ecco a te!";
				link.l1 = "Un piacere fare affari con te! Ora la taverna traboccherà di nuovo di rum e vino.";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 200);
			}
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_Tavern3_2":
			dialog.text = "Sei il mio salvatore, Capitano! Mi aspetto spedizioni simili ogni due settimane. Spero che rispetterai rigorosamente i tuoi obblighi. Un'altra siccità come quella, e la mia taverna non sopravviverà...";
			link.l1 = "Non c'è bisogno di preoccuparti, "+npchar.name+". Il mio rappresentante in città è Christian Deluce. Lui farà in modo che alla tua taverna non manchi mai vino o rum.";
			link.l1.go = "TPZ_Tavern3_3";
		break;
		
		case "TPZ_Tavern3_3":
			dialog.text = "Christian? Lo conosco. Un uomo responsabile, anche se... beh, non importa. Dato che hai sistemato le cose con le autorità, suppongo di potergli fidare.";
			link.l1 = "Eccellente. Ora, se mi scusi, ho un altro affare da risolvere in questa città.";
			link.l1.go = "TPZ_Tavern3_4";
		break;
		
		case "TPZ_Tavern3_4":
			dialog.text = "Vieni a trovarci più spesso!";
			link.l1 = "Certo che lo farò.";
			link.l1.go = "TPZ_Tavern3_5";
		break;
		
		case "TPZ_Tavern3_5":
			DialogExit();
			AddQuestRecord("TPZ", "7");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_4");
			
			sld = CharacterFromID("TPZ_Kristian");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

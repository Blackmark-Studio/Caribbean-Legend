// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Parla, ti sto ascoltando.";
			link.l1 = "Mi sono sbagliato. Addio.";
			link.l1.go = "Exit";
			// --> Тичингиту
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "true")
            {
                link.l1 = "C'è un indiano sotto arresto. È stato catturato da Fadey il Moscovita. Posso parlare con lui?";
                link.l1.go = "Tichingitu";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "commandante")
            {
                link.l1 = "Dimmi, stai davvero per impiccare questo indiano? Non è troppo severa come punizione per un delitto così piccolo?";
                link.l1.go = "Tichingitu_3";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "pay")
            {
                link.l1 = "Sono di nuovo io, comandante. Fadey il Moscovita ha scritto questa petizione per liberare l'indiano. Eccola qui.";
                link.l1.go = "Tichingitu_6";
            }
			// <-- Тичингиту
			//Jason --> Бесчестный конкурент
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "Sono venuto da te su richiesta del proprietario del negozio locale, il suo nome è "+pchar.questTemp.Shadowtrader.Tradername+". Lui mi ha chiesto di darti questa lettera.";
				link.l1.go = "Shadowtrader_prison";
			}
			
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.SeekTrader") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "Eccomi di nuovo. Ho prove sostanziali che "+pchar.questTemp.Shadowtrader.Tradername+" ha ragione.";
				link.l1.go = "Shadowtrader_prison2";
			}
			//Jason <-- Бесчестный конкурент
			//Sinistra --> Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTurma"))
            {
                link.l1 = "Cerco un uomo chiamato Longway. Ho sentito dire che anche voi, Monsieur Ufficiale, lo state cercando. Avete avuto fortuna nel trovarlo, o forse qualche indizio?";
                link.l1.go = "PZ_IshemLongway_1";
            }
			//Sinistra <-- Путеводная звезда
		break;
		
		// --> Тичингиту
		case "Tichingitu":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			dialog.text = "A-ah, Fadey ti ha raccontato la sua storia? Non ho motivi per vietarti di dargli un'occhiata, signore. Non sei il primo a venire a vedere quel pellerossa. Beh, tra dieci giorni ogni cittadino potrà dargli un'occhiata quando lo impiccheremo al sole...";
			link.l1 = "Posso entrare nella prigione?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Come ti ho già detto 'Non ho motivi per proibirtelo'. Vai avanti.";
			link.l1 = "Grazie!";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "Tichingitu_3":
			DelLandQuestMark(npchar);
			dialog.text = "Sei nuovo qui, vero, signore? Direttamente dall'Europa? Non capisci la situazione nelle colonie. Questa esecuzione sarà una lezione per quei bastardi pellerossa che oserebbero attentare alla proprietà dei coloni francesi. Inoltre, Fadey stesso insiste su questo ed è un uomo molto rispettato qui e un amico stretto del nostro governatore.";
			link.l1 = "C'è un modo per attenuare la punizione? Io continuo a pensare che sia troppo severa...";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Oh, non diventare filosofico! Vai da Fadey e chiedi di questo indiano se ti importa davvero così tanto del suo destino. Se Fadey scrive una petizione per la liberazione, la soddisferemo.";
			link.l1 = "Capito, ufficiale. Andrò da Fadey.";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "fadey";
			AddLandQuestMark(characterFromId("fadey"), "questmarkmain");
			QuestPointerToLoc("BasTer_town", "reload", "houseSp1");
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			RemoveItems(pchar, "letter_1", 1);
			dialog.text = "(leggendo) Mh... Questo Fadey è strano... Ha richiesto un'esecuzione dimostrativa e ora chiede di liberare questo indiano... Comunque, immagino che tutti gli amici del governatore siano come lui. Bene, puoi andare e prendere questo pellerossa.";
			link.l1 = "Grazie mille, ufficiale!";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			AddQuestRecord("Tichingitu", "3");
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_6";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// <-- Тичингиту
		
		//Jason --> мини-квест Бесчестный конкурент
		case "Shadowtrader_prison":
			dialog.text = "Di nuovo quello "+pchar.questTemp.Shadowtrader.Tradername+" con le sue lamentele! Va bene, vediamo cosa c'è questa volta... (legge)";
			link.l1 = "...";
			link.l1.go = "Shadowtrader_prison_1";
			RemoveItems(PChar, "letter_1", 1);
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Fort");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison_1":
			dialog.text = "Di nuovo, supposizioni assurde e non una singola prova concreta! Va bene. Digli che questo semplicemente non è sufficiente per me per allertare le guardie e ordinar loro di setacciare la città.";
			link.l1 = "Vuoi che glielo dica?";
			link.l1.go = "Shadowtrader_prison_2";
		break;
		
		case "Shadowtrader_prison_2":
			dialog.text = "Esattamente - e, preferibilmente, parola per parola. Capirà cosa intendo. Non sprecherò carta per scrivere una risposta a questo fastidioso.";
			link.l1 = "Capisco. Addio, allora.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.Trouble = "true";
			NextDiag.TempNode = "First_officer";
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
		
		case "Shadowtrader_prison2":
			dialog.text = "E quale sarebbe questa 'sostanziale' prova che affermi di aver raccolto?";
			link.l1 = "Ho fatto un accordo con i contrabbandieri riguardo l'acquisto di merci attraverso il loro negozio non ufficiale. Il loro agente verrà stasera all'ufficio dell'autorità portuale, per portarmi al loro cosiddetto 'negozio'.";
			link.l1.go = "Shadowtrader_prison2_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			pchar.quest.ShadowtraderTimeSmugglers_Over.over = "yes";
			pchar.quest.Shadowtrader_SMG.over = "yes";//снять оба прерывания
			sld = characterFromID("ShadowAgent_1");
			sld.lifeday = 0;
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison2_1":
			dialog.text = "Hmm... Beh, ottimo lavoro, capitano! Allora agiremo ulteriormente. Invieremo il nostro uomo al loro incontro, localizzeremo il loro nascondiglio e arrestiamo tutti loro. Grazie per la tua iniziativa!";
			link.l1 = "Sempre lieto di aiutare. Sono sicuro che la vostra operazione avrà successo.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.End.Fort = "true";
			AddQuestRecord("Shadowtrader", "7");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			SetTimerFunction("ShadowTrader_questmark", 0, 0, 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			NextDiag.TempNode = "First_officer";
		break;
		// <-- мини-квест Бесчестный конкурент
		
		// Sinistra - Квест "Путеводная звезда" ==>
		case "PZ_IshemLongway_1":
			DelLandQuestMark(npchar);
			dialog.text = "Chi? Lungo... Cammino? Non ricordo nessun inglese nella nostra città recentemente.";
			link.l1 = "No, Longway è... cinese.";
			link.l1.go = "PZ_IshemLongway_2";
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTurma");
			DeleteQuestCondition("PZ_BasTerPeshera");
		break;
		
		case "PZ_IshemLongway_2":
			dialog.text = "Ebbene, ebbene. E perché state cercando questo vostro Longway, signore?";
			link.l1 = "È un mio amico. Ho già sentito parlare di ciò che è successo - è un triste malinteso, ti assicuro.";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "Lo sto cercando perché è un criminale noto nell'Arcipelago.";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_IshemLongway_Zashita_1":
			dialog.text = "Ah, un malinteso. Non cercavamo di metterlo in riga sul posto, se altro. Volevamo solo parlargli... per cominciare. Tuttavia, questo tuo aggressivo uomo giallo non solo ha abbattuto diversi guardie cittadine, ma ha anche massacrato le unità inviate a inseguirlo nella giungla.";
			link.l1 = "Ha intenzione di inviare un'altra unità? Potrei andare con i suoi uomini, parlare con lui, calmarlo e prevenire un altro disastro. Basterebbe se gli omicidi si fermassero e Longway lasciasse la città per sempre?";
			link.l1.go = "PZ_IshemLongway_Zashita_2";
		break;
		
		case "PZ_IshemLongway_Zashita_2":
			dialog.text = "In circostanze normali, potrei essere d'accordo con te. Ma vedi, uno di quelli uccisi era un ufficiale - un giovane tenente promettente, il preferito di Sua Grazia. La città è in lutto. Non c'è modo di chiudere un occhio o di rimediare. Capisci?";
			link.l1 = "Capisco perfettamente. Mi scuso per le azioni del mio amico. Non vi disturberò più.";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
			link.l2 = "Sai, solo Dio sa cosa sta succedendo nella giungla. Chiunque avrebbe potuto uccidere quegli uomini.";
			link.l2.go = "PZ_IshemLongway_Blef_1";
		break;
		
		case "PZ_IshemLongway_Blef_1":
			dialog.text = "E chi pensi che potrebbe aver abbattuto un'intera squadra di pattugliatori guidata da un ufficiale?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l1 = "(Onesto) Banditi, chi altri? Mi vergogno ad ammetterlo, ma recentemente sono appena sfuggito a una grande banda.";
				link.l1.go = "PZ_IshemLongway_Blef_2";
			}
			else
			{
				notification("Perk check failed", "Trustworthy");
				link.l1 = "Ma come potrei saperlo? Potrebbe essere stato chiunque - briganti, pirati, spie...";
				link.l1.go = "PZ_IshemLongway_Blef_netVD_1";
			}
		break;
		
		case "PZ_IshemLongway_Blef_2":
			dialog.text = "Eh, non è sorprendente - considerando la tua stazza, Capitano. Sì, abbiamo tali canaglie sull'isola in questi giorni...";
			link.l1 = "Esattamente! Quindi, avrebbero potuto massacrare la pattuglia e il povero tenente di grado inferiore.";
			link.l1.go = "PZ_IshemLongway_Blef_3";
		break;
		
		case "PZ_IshemLongway_Blef_3":
			dialog.text = "Sfortunatamente, è del tutto possibile.";
			link.l1 = "Esattamente. Quindi, ancora una volta, ti chiedo di lasciarmi unirmi alla prossima squadra di ricerca - Longway mi ascolterà, e in questo modo possiamo evitare altre morti.";
			link.l1.go = "PZ_IshemLongway_Blef_4";
		break;
		
		case "PZ_IshemLongway_Blef_4":
			dialog.text = "Va bene. Ma c'è ancora un 'ma', signore.";
			link.l1 = "E cosa sarebbe quello?";
			link.l1.go = "PZ_IshemLongway_Blef_5";
		break;
		
		case "PZ_IshemLongway_Blef_5":
			dialog.text = "A differenza di quanto accaduto nella giungla, la colpa del tuo amico in città è chiara e pienamente provata. Non passerà impunita. Quindi, queste morti devono essere compensate se vuoi che lui lasci la città vivo.";
			link.l1 = "Va bene. Quanto costerà, Signor Ufficiale?";
			link.l1.go = "PZ_IshemLongway_Blef_6";
		break;
		
		case "PZ_IshemLongway_Blef_6":
			dialog.text = "Trecento dobloni. Quei soldi andranno alla città, non ai barattieri della piazza del mercato.";
			if (PCharDublonsTotal() >= 300)
			{
				link.l1 = "Certo. Trecento dobloni - eccoli qui.";
				link.l1.go = "PZ_IshemLongway_Blef_7";
			}
			link.l2 = "Non ho portato i miei dobloni in città questa volta. Ma se mi permetti di recuperarli...";
			link.l2.go = "PZ_IshemLongway_NetDublonov_1";
		break;
		
		case "PZ_IshemLongway_Blef_7":
			dialog.text = "Eccellente. Hai dimostrato la tua responsabilità. Stiamo solo finalizzando l'informazione per la prossima squadra. Ti autorizzo a unirti a loro.";
			link.l1 = "Grazie. Addio, Signor Ufficiale.";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.PZ_DrugOtryad = true;
		break;
		
		case "PZ_IshemLongway_NetDublonov_1":
			dialog.text = "Non sono nato ieri. So che intendi scappare - non per i dobloni, ma per il tuo caro cinese.";
			link.l1 = "Ti do la mia parola che non lascerò la città con Longway.";
			link.l1.go = "PZ_IshemLongway_NetDublonov_2";
		break;
		
		case "PZ_IshemLongway_NetDublonov_2":
			dialog.text = "Parole, parole... Sono stanco del tuo chiacchiericcio, Capitano. Non andrai da nessuna parte finché non catturiamo noi stessi questo maledetto uomo dalla pelle gialla.";
			link.l1 = "Obbedirò al tuo ordine se prometti di non uccidere Longway sul posto, Signor Ufficiale.";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "Ma ho violato personalmente le leggi della città oggi?";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_1":
			dialog.text = "Allora non lo sai. Mi atterro' alla mia corrente intuizione - il Cinese deve essere catturato, indipendentemente.";
			link.l1 = "La tua attuale intuizione? Ma non hai prove che Longway abbia ucciso tutti nella giungla.";
			link.l1.go = "PZ_IshemLongway_Blef_netVD_2";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_2":
			dialog.text = "E hai prove della sua innocenza? No? Allora smetti di fare un santo del tuo uomo dalla pelle gialla. Mi capisci?";
			link.l1 = "Capisco perfettamente. Mi scuso per le azioni del mio amico. Non vi disturberò più.";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
		break;
		
		case "PZ_IshemLongway_Uiti_1":
			dialog.text = "Mi dispiace, ma non posso permetterti di andartene proprio ora, Capitano.";
			link.l1 = "Cosa intendi?";
			link.l1.go = "PZ_IshemLongway_Uiti_2";
		break;
		
		case "PZ_IshemLongway_Uiti_2":
			dialog.text = "Quello che intendo è che, dato che questo Longway è tuo amico, non c'è garanzia che tu non gli correrai dietro cercando di fuggire con lui. Quindi, dovrò tenerti qui fino a quando non cattureremo noi stessi questo macellaio dalla pelle gialla.";
			link.l1 = "Obbedirò al tuo ordine se prometti di non uccidere Longway sul posto, Signor Ufficiale.";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "Ma ho violato personalmente le leggi della città oggi?";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Arest_1":
			dialog.text = "Non posso promettere nulla. Chissà cosa ha in mente il tuo amico, o se inizierà un altro massacro quando ci vede. Nel frattempo, per favore, goditi il tuo lussuoso alloggio, Capitano.";
			link.l1 = "Divertentissimo...";
			link.l1.go = "PZ_IshemLongway_Arest_2";
		break;
		
		case "PZ_IshemLongway_Arest_2":
			DialogExit();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto9", "PZ_SharliePlennik_BadFinal");
		break;
		
		case "PZ_IshemLongway_Pobeg_1":
			dialog.text = "Capisci, non ho nulla contro di te personalmente. E hai ragione - non hai commesso alcun crimine. Ma dobbiamo garantire che il tuo amico dalla pelle gialla non sfugga alla giustizia.";
			link.l1 = "Allora capisci che non mi permetterò di essere detenuto in modo così falso.";
			link.l1.go = "PZ_IshemLongway_Pobeg_2";
		break;
		
		case "PZ_IshemLongway_Pobeg_2":
			if (pchar.location.from_sea == "BasTer_Town")
			{
				dialog.text = "In tal caso, dovremo farvi tacere, signore.";
			}
			else
			{
				dialog.text = "Ne ho abbastanza di tutto questo! Sergente, guidate la squadra in quella maledetta caverna e trovate i Cinesi! Mi occuperò personalmente di questo...";
			}
			link.l1 = "All'inferno andrai.";
			link.l1.go = "PZ_IshemLongway_Pobeg_3";
		break;
		
		case "PZ_IshemLongway_Pobeg_3":
			DialogExit();
			
			LAi_SetHuberType(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_MoveCharacter(NPChar, "FRANCE_CITIZENS");
			LAi_group_Attack(characterFromId("BasTer_Mayor"), Pchar);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			if (pchar.location.from_sea == "BasTer_Town")
			{
				PChar.quest.PZ_KorablPort_BadFinal.win_condition.l1 = "MapEnter";
				PChar.quest.PZ_KorablPort_BadFinal.win_condition = "PZ_KorablPort_BadFinal";
				AddQuestRecord("PZ", "10");
				LocatorReloadEnterDisable("BasTer_town", "gate_back", true);
				Island_SetReloadEnableGlobal("Guadeloupe", false);
			}
			else
			{
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition.l1 = "EnterToSea";
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition = "PZ_KorablBuhta_BadFinal";
				AddQuestRecord("PZ", "5");
				
				// Микро-диалог с Лонгвэем у пещеры, если мы побежали к пещере ему помочь после ссоры с комендантом
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1 = "location";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1.location = "Guadeloupe_CaveEntrance";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition = "PZ_IshemLongway_SorraKomendant";
				
				LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
				LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
				//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			}
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_1":
			dialog.text = "Un cacciatore di taglie, eh? Normalmente, non mi piace avere a che fare con la tua specie, ma in questo caso, è a mio vantaggio che i nostri interessi si allineino. A quanto pare, questo dalla pelle gialla è un famigerato assassino. Ha ucciso molti dei miei uomini, sia in città che nella giungla.";
			link.l1 = "Lo sto inseguendo per l'arcipelago da un po' di tempo ormai.";
			link.l1.go = "PZ_IshemLongway_OhotnikOtryad_2";
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_2":
			dialog.text = "Maledetto furfante! Ecco cosa faremo: riunirò un'altra squadra, e tu andrai con loro. Questa volta, non avrà dove scappare, e con il tuo aiuto, avremo più possibilità di successo. Non aspettarti una ricompensa da me, però - sei un cacciatore di taglie, quindi il tuo pagamento verrà da chi ti ha assunto. Dovresti essere grato che ti permetto di cooperare con me in primo luogo.";
			link.l1 = "È vero quanto dici. Ci vediamo dopo, ufficiale. Se qualcuno dei tuoi uomini sopravviverà ad un altro incontro con il nostro amico cinese, ti farò sapere come è andata.";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			pchar.questTemp.PZ_OhotnikOtryad = true;
		break;
		
		case "PZ_IshemLongway_BeryomOtryad":
			DialogExit();
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			DoQuestReloadToLocation("Guadeloupe_jungle_02", "goto", "goto1", "PZ_IshemLongway_Otryad");
		break;
		
		case "PZ_BasTer_ComendantDialog_1":
			dialog.text = "Hai ragione. Voi due vi conoscete, immagino? Che rapporto avete?";
			link.l1 = "È un ufficiale di navigazione sulla mia nave, e...";
			link.l1.go = "PZ_BasTer_ComendantDialog_2";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "Lo sto cercando perché è un criminale noto nell'Arcipelago.";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_BasTer_ComendantDialog_2":
			dialog.text = "Lui è più bravo con le pistole che con le mappe. Hai idea di cosa ha fatto il tuo cinese preferito?";
			link.l1 = "Onestamente no, perché sono appena attraccato e ho iniziato a cercare. Sono sicuro che tutto sia stato un malinteso.";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_1":
			dialog.text = "Esattamente. Chi sei tu per lui se lo vuoi così tanto? Non importa - ciò che conta è lo scopo della tua visita alla città.";
			link.l1 = "Niente di illegale, signore. Ma cosa intendevate con “non importa più”? Ha lui...";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_2";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_2":
			dialog.text = "Sì. È stato sepolto dietro una delle colline, a una certa distanza dal cimitero. I santi padri non hanno permesso una degna sepoltura cristiana per un pagano.";
			link.l1 = "Come è successo, se non è un segreto?";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_3";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_3":
			dialog.text = "Molto semplicemente - è arrivato in città, fiutando senza fine. Abbiamo provato a parlare con lui, per scoprire cosa stava facendo qui, ma ha ucciso alcuni uomini e si è rifugiato nella giungla. Ho mandato diversi gruppi di ricerca dietro di lui, uno dopo l'altro, ma li ha tutti eliminati! Abbiamo dovuto intrappolarlo in una grotta, e i tiratori hanno fatto il resto.";
			link.l1 = "E non sai cosa stava cercando? Vedi, non aveva mai fatto nulla del genere prima - era un navigatore sulla mia nave. Ma poi mi ha rubato e scappato.";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_4";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_4":
			dialog.text = "Mi è proprio sfuggito, eh. Quindi, hai sofferto anche tu per le sue azioni? Questo ti insegnerà una lezione, Capitano. Sarai più saggio nel prendere qualcuno di cui non ti puoi fidare. Non fidarti mai di un uomo dalla pelle gialla - segna le mie parole!";
			link.l1 = "Certo, lo terrò a mente. Hai trovato qualcosa su di lui?";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_5";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_5":
			dialog.text = "Oh, vuoi recuperare la merce rubata? Aveva dell'argento nelle tasche, quindi se ti ha rubato, ha già speso tutto. E c'erano alcuni altri documenti... dal registro della tua nave? Non lo abbiamo capito comunque - qualche tipo di codice, forse? Tutto era coperto di sangue, quindi non siamo riusciti a distinguere le parti intatte.";
			link.l1 = "Eh, sì. Grazie. Ho sempre temuto cosa sarebbe successo se i miei diari fossero finiti nelle mani di qualcun altro...";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_6";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_6":
			dialog.text = "E avere a che fare con un cifrario complesso e completo per questo? Non ti sei pentito del tuo tempo e sforzo? Ecco a te. E riguardo l'argento - non arrabbiarti, ma l'abbiamo restituito alla città. Quel cinese quel giorno ha messo molti dei miei uomini sotto terra.";
			link.l1 = "Allora non oso insistere. Addio.";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_7";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_7":
			DialogExit();
			
			LAi_SetHuberType(npchar);
			AddQuestRecord("PZ", "9");
			CloseQuestHeader("PZ");
			bDisableLandEncounters = false;
		break;
		// <== Квест "Путеводная звезда" - Sinistra
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

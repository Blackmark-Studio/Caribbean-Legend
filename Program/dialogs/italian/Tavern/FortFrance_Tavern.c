// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti, "+GetAddress_Form(NPChar)+"?"),"Hai cercato di farmi una domanda poco tempo fa, "+GetAddress_Form(NPChar)+"...","Per tutto il giorno, è la terza volta che parli di qualche domanda...","Altre domande, presumo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho nulla di cui parlare al momento."),"Uh, dove se n'è andata la mia memoria...","Sì, è davvero la terza volta...","No, quali domande?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Jason, Бремя гасконца
			if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
			{
				link.l1 = "Signore, sto cercando lavoro. Hai qualche lavoro da proporre?";
                link.l1.go = "Sharlie_rum";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
			{
				link.l1 = "Ho completato la tua missione. La scialuppa con il rum è stata consegnata alla Baia di Le Francois e consegnata ai tuoi uomini.";
                link.l1.go = "Sharlie_rum_5";
			}	
			//<-- Бремя гасконца */
			
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToMartinique" && !CheckAttribute(npchar, "quest.Portugal"))
			{
				link.l1 = "Ho bisogno di affittare una delle vostre stanze per due o tre giorni. Ho un uomo a bordo che è ferito. Ha bisogno di riposare e recuperare.";
				link.l1.go = "Portugal";
			}
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernorEnd")
			{
				link.l1 = "Dimmi. L'amico per cui ho affittato una stanza, se n'è andato? Ha promesso di aspettarmi, ma la stanza è vuota.";
				link.l1.go = "Portugal_2";
			}
			//Португалец
			// Jason Долго и счастливо
			if (!CheckAttribute(npchar, "quest.LongHappy") && CheckAttribute(PChar, "questTemp.LongHappy.MarryRum") && LongHappy_CheckTavernGoods())
			{
				link.l1 = "Sto organizzando una festa per i miei uomini. Suppongo che tu ne sia già a conoscenza?";
				link.l1.go = "LH_tavern_SP";
			}
			if (CheckAttribute(npchar, "quest.LongHappy.Nomoney") && LongHappy_CheckTavernGoods() && sti(Pchar.money) >= 100000+sti(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = "Ho portato tutto il necessario per la nostra celebrazione.";
				link.l1.go = "LH_tavern_SP_3";
			}
		break;
		
		//--> Jason, Бремя гасконца
		case "Sharlie_rum":
			DelLandQuestMark(npchar);
			dialog.text = "Un compito? Mh... Sembri avere un po' di cervello, ragazzo. Potrei avere qualcosa per te\nQuesto lavoro potrebbe sembrare facile, ma richiede responsabilità e intelligenza. Non posso fidarmi di questi idioti per fare affari, lo rovinerebbero di sicuro...";
			link.l1 = "Ascolta, potresti per favore dirmi cosa diavolo vuoi affidarmi? Lo giuro, non ti deluderò o almeno farò del mio meglio.";
			link.l1.go = "Sharlie_rum_1";
		break;
		
		case "Sharlie_rum_1":
			switch(rand(4))
			{
				case 0:
					pchar.questTemp.Sharlie.Rum.Pass = "Old Thomas has grown tired of waiting for the beer";
				break;
				case 1:
					pchar.questTemp.Sharlie.Rum.Pass = "The boards and the oakum will be here in the morning";
				break;
				case 2:
					pchar.questTemp.Sharlie.Rum.Pass = "Don't wait for the south wind";
				break;
				case 3:
					pchar.questTemp.Sharlie.Rum.Pass = "The bay is ready for disembarkation";
				break;
				case 4:
					pchar.questTemp.Sharlie.Rum.Pass = "The camels are going north";
				break;
			}
			dialog.text = "Bene. Ho bisogno di qualcuno che consegni diverse casse di pregiato rum della Giamaica alla mia taverna. Ecco il punto, i dazi doganali incidono sui miei margini e i miei migliori clienti hanno sete, quindi dobbiamo agire con astuzia per evitare gli ufficiali doganali. Il lugger 'Ghost' arriverà al largo di Martinica stanotte\nLanceranno l'ancora non lontano dalla Baia di Lamanten. Devi trovare questa nave e salire a bordo. Ti fornirò una barca lunga e cinque marinai, seguiranno i tuoi ordini\nUna volta a bordo, un uomo si avvicinerà a te. Dovrai dirgli una password: '"+pchar.questTemp.Sharlie.Rum.Pass+"'\nLa risposta sarà 'Perché non prendere un rum, marinaio?'. Avrai solo un tentativo, quindi scrivilo e non fare errori o l'accordo è nullo. Ecco perché non posso affidarlo a quei cretini senza cervello che navigheranno con te. Ripeti la password.";
			link.l1 = "'"+pchar.questTemp.Sharlie.Rum.Pass+"'. ";
			link.l1.go = "Sharlie_rum_2";
		break;
		
		case "Sharlie_rum_2":
			dialog.text = "Bene. Ripetilo a te stesso ancora qualche volta, o meglio ancora, scrivilo da qualche parte. Dopo che avrai detto la parola d'ordine al capitano del gozzo, le casse con le bottiglie di rum verranno caricate sulla barca lunga, che poi dovrai navigare fino alla baia dell'insediamento pirata Le Francois - là ti accoglieranno.\nQuesto è tutto il compito. Puoi andare da Le Francois Bay a Saint Pierre a piedi - la barca lunga resterà nella baia. Ti pagherò cinquemila pezzi di otto una volta fatto.";
			link.l1 = "Contrabbando suona sia eccitante che lucrativo. Farò quello che mi hai detto di fare. Dov'è la scialuppa?";
			link.l1.go = "Sharlie_rum_3";
			link.l2 = "Allora, proponi che mi metta a contrabbandare? Mm... Sai, non posso rischiare il mio nome. Mi devi scusare, facciamo finta che non ho sentito nulla.";
			link.l2.go = "Sharlie_rum_exit";
		break;
		
		case "Sharlie_rum_exit":
			dialog.text = "Come desidera, signore. Non ho altri lavori.";
			link.l1 = "Capisco. Allora, tutto il meglio, "+npchar.name+".";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
			SetCurrentTime(23, 0);
			Sharlie_removeLocks("");
		break;
		
		case "Sharlie_rum_3":
			dialog.text = "La lancia sarà al molo alle sette di sera. L'equipaggio sulla lancia è abile, quindi dovresti raggiungere il goletta velocemente. L'intera missione non dovrebbe richiedere più di quattro ore - sono sicuro che sarai di ritorno a Saint Pierre per le undici di sera. Prendi questo cannocchiale, è un pezzo di spazzatura ma è meglio di niente. La spiaggia di Lamanten si trova nella parte settentrionale dell'isola, quindi lasciando il porto, mantieni la rotta a nord. Buona fortuna!";
			link.l1 = "Bene, capito. A presto, "+npchar.name+"!";
			link.l1.go = "Sharlie_rum_4";
		break;
		
		case "Sharlie_rum_4":
			DialogExit();
			AddQuestRecord("SharlieB", "1");
			AddQuestUserData("SharlieB", "sPassword", pchar.questTemp.Sharlie.Rum.Pass);
			GiveItem2Character(pchar, "spyglass1"); 
			Log_Info("You've received a spyglass");
			PlaySound("interface\important_item.wav");
			if(CheckAttribute(pchar, "questTemp.Sharlie.FastStart"))
			{
				GiveItem2Character(pchar, "map_martiniqua");
				Log_Info("You have received a map of Martinique");
				RefreshEquippedMaps(GetMainCharacter());
			}
			/* pchar.quest.Sharlie_rum.win_condition.l1 = "location";
			pchar.quest.Sharlie_rum.win_condition.l1.location = "Fortfrance_town"; */
			//pchar.quest.Sharlie_rum.win_condition.l1.locator_group = "rld";
			//pchar.quest.Sharlie_rum.win_condition.l1.locator = "loc0";
			pchar.quest.Sharlie_rum.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_rum.win_condition.l1.hour = 19.00;
			pchar.quest.Sharlie_rum.function = "Rum_CreateBarkas";
			SetFunctionTimerCondition("Rum_CreateBarkasOver", 0, 0, 1, false);
			pchar.questTemp.Sharlie.Rum = "true";
			npchar.quest.Rum = "true";
			NewGameTip("Open your inventory (F1) and equip the spyglass.");
			pchar.quest.NgtBarkas.win_condition.l1 = "location";
			pchar.quest.NgtBarkas.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.NgtBarkas.win_condition.l2 = "HardHour";
			pchar.quest.NgtBarkas.win_condition.l2.hour = 19.00;
			pchar.quest.NgtBarkas.function = "NgtBarkas";
			AddTimeToCurrent(1,30);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
			QuestPointerToLoc("fortfrance_town", "reload", "reload1_back");
		break;
		
		case "Sharlie_rum_5":
			dialog.text = "Meraviglioso! Sapevo di poter contare su di te. È stato difficile?";
			link.l1 = "Beh, dipende da come definisci difficile...";
			link.l1.go = "Sharlie_rum_6";
		break;
		
		case "Sharlie_rum_6":
			dialog.text = "Ebbene, ecco la tua ricompensa: cinquemila pesos. Puoi tenere il cannocchiale. E anche, un altro piccolo regalo, per favore, prendi queste tre bottiglie di rum. Dopo che lo avrai provato, capirai perché c'è così tanta richiesta.";
			link.l1 = "Grazie! È stato bello lavorare con te! Ci vediamo dopo!";
			link.l1.go = "Sharlie_rum_7";
		break;
		
		case "Sharlie_rum_7":
			DialogExit();
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "potionrum", 3);
			AddQuestRecord("SharlieB", "5");
			CloseQuestHeader("SharlieB");
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
			DelLandQuestMark(npchar);
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		//<-- Бремя гасконца
		
		//Португалец
		case "Portugal":
			dialog.text = "Nessun problema, ho una stanza. Per 50 pesos, è tua per tre giorni.";
			if (sti(pchar.money) >= 50)
			{
				link.l1 = "Eccoti qua.";
				link.l1.go = "Portugal_1";
			}
			else
			{
				link.l1 = "Prenderò i soldi dal tesoriere e tornerò.";
				link.l1.go = "exit";
			}
		break;
		
		case "Portugal_1":
			ref sld;
			DialogExit();
			AddMoneyToCharacter(pchar, -50);
			npchar.quest.Portugal = "true";
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", false);
			pchar.quest.Portugal_Ill3.over = "yes";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", true);//закрыть выходы из города
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto3");
			sld = characterFromId("PortugalDoctor");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto1");
			pchar.quest.Portugal_tavernroom.win_condition.l1 = "location";
			pchar.quest.Portugal_tavernroom.win_condition.l1.location = "FortFrance_tavern_upstairs";
			pchar.quest.Portugal_tavernroom.function = "PortugalInTavernRoom";
		break;
		
		case "Portugal_2":
			dialog.text = "Non direi che si è alzato e ha lasciato la stanza da solo, monsieur. Alcune persone sono passate di qui ieri. Uno di loro era un uomo alto e magro con un occhio solo - un palese bandito dall'aspetto, e uno anche con un difetto di pronuncia, sembrava un Castigliano. Ero solo sorpreso, ma quel balbuziente mi ha dato uno sguardo... proprio come a una pidocchia prima di una bastonata. E così hanno chiesto del tuo amico... e io gliel'ho detto. Cosa altro avrei dovuto fare?";
			link.l1 = "Lo so, "+npchar.name+", non sei un eroe, è vero. Cos'altro hai visto? Dove sono andati?";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "Questo è tutto... aspetta, no! Fermati, l'uomo con un occhio solo ha detto qualcosa su un carro. Immagino che abbiano preso un carro e trascinato il tuo amico dall'altra parte dell'isola. Questo è tutto signore, lo giuro... Avrei chiamato la guardia, ma quel balbuziente mi ha detto che avevo una bellissima moglie prima della sua partenza... Vedi? Se scoprono che ti ho detto tutto questo, loro...";
			if (pchar.money >= 1000)
			{
				link.l1 = "Non aver paura, da me non sentiranno altro che proiettili. Mi hai davvero aiutato, grazie. Ecco, prendi 1000 pesos come ricompensa.";
				link.l1.go = "Portugal_4";
			}
			link.l2 = "Non è molto, ma grazie comunque. La prossima volta chiama la guardia e non fare il pollo.";
			link.l2.go = "Portugal_5";
		break;
		
		case "Portugal_4":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Grazie, signore. Posso assicurarle che il suo amico si è quasi ripreso. Almeno camminava da solo. E quell'uomo, quel tranquillo olandese, è entrato in quel momento, ha visto tutto quel disastro e si è precipitato fuori, è semplicemente sparito.";
			link.l1 = "Direi che è già partito sulla prima nave che ha potuto prendere. Grazie per l'informazione, è ora per me di andare.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_5":
			dialog.text = "Non ogni uomo può essere un eroe con la spada sguainata, capitano.";
			link.l1 = "Ebbene... quella è la scelta dell'uomo.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_seapatrol_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		//Португалец
		
		// Jason Долго и счастливо
		case "LH_tavern_SP":
			npchar.quest.LongHappy = "true";
			dialog.text = "Sì, la tua assistente è passata, ma le ho detto e te lo ripeterò - mi sono abituato alle folle di marinai ubriachi, ma so come vanno le tue feste. Quello che rimane sembrerà Anversa dopo l'arrivo dei tercios spagnoli. Sarò felice se le mura saranno ancora in piedi. Quindi, se vuoi far scatenare le masse, avrò bisogno di un deposito non rimborsabile oltre a quello che hai già portato. In caso di conseguenze, per così dire.";
			link.l1 = "Tu astuta volpe! Io stesso ho bevuto con cani di mare per molti anni, sono stato in diversi... stabilimenti, e so che per i soldi che ho portato potremmo ricostruire la tua taverna da zero! Sfruttando l'opportunità, eh? Va bene, ho un matrimonio, e non ho voglia di preoccuparmi di queste piccolezze - quanto vuoi?";
			link.l1.go = "LH_tavern_SP_1";
		break;
		
		case "LH_tavern_SP_1":
			dialog.text = "Un altro 100.000 pezzi di otto dovrebbero bastare e non preoccuparti - farò tutto nel miglior modo possibile. I tuoi ragazzi ricorderanno questa festa per molto tempo, ricorda la mia parola!";
			if (sti(Pchar.money) >= 100000+sti(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = "Davvero devi fare del tuo meglio - questa è un'occasione speciale, capisci. E sì, dopo la festa, non venire da me con lamentele, anche se la tua taverna brucia.";
				link.l1.go = "LH_tavern_SP_4";
			}
			else
			{
				link.l1 = "Sembra già che stia organizzando un matrimonio reale! Aspetta, tornerò presto.";
				link.l1.go = "LH_tavern_SP_2";
			}
		break;
		
		case "LH_tavern_SP_2":
			DialogExit();
			npchar.quest.LongHappy.Nomoney = "true";
		break;
		
		case "LH_tavern_SP_3":
			dialog.text = "I vostri ragazzi ricorderanno questa festa per molto tempo, ricordate le mie parole!";
			link.l1 = "Devi davvero impegnarti - è un'occasione speciale, capisci. Non venire a piangere da me se i miei ragazzi incendiano accidentalmente la tua taverna.";
			link.l1.go = "LH_tavern_SP_4";
		break;
		
		case "LH_tavern_SP_4":
			DialogExit();
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.questTemp.LongHappy.MarryRum));
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.LongHappy.MarryMoney));
			AddMoneyToCharacter(pchar, -100000);
			DeleteAttribute(npchar, "quest.LongHappy.Nomoney");
			pchar.questTemp.LongHappy.DrinkReady = "true";
			pchar.questTemp.LongHappy.MarrySP = "true";
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryMoney");
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryRum");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

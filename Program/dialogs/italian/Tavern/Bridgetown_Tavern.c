// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti, "+GetAddress_Form(NPChar)+"?"),"Hai provato a farmi una domanda non molto tempo fa, "+GetAddress_Form(NPChar)+"...","Questa è la terza volta che mi infastidisci...","Altre domande, presumo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho nulla di cui parlare al momento."),"Uhm, dove è andata a finire la mia memoria...","Sì, è davvero la terza volta...","No, quali domande?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит /за Англию/
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Vorrei un drink. Versami il miglior rum che hai.";
                link.l1.go = "TavernDone";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "toBarbados")
            {
                link.l1 = "Ascolta, dov'è Callow Gaston?";
                link.l1.go = "Tonzag_Letter";
            }
			//Голландский гамбит /против всех/
			if (!CheckAttribute(npchar, "quest.HWICTake") && CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Self") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
                link.l1 = "Avete per caso qualche tipo di lavoro? O forse potreste suggerire qualcosa?";
                link.l1.go = "Tonzag_check";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FernandoDie")
			{
                link.l1 = "Ho finito il lavoro. Fernando Rodriguez è morto.";
                link.l1.go = "Task_check";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Ascolta, è arrivato qui in città un alchimista, un medico? È italiano, circa trent'anni, si chiama Gino Gvineili. Hai sentito qualcosa a riguardo?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Голландский гамбит /за Англию/
		case "TavernDone":
			dialog.text = "Ecco il tuo drink. Il miglior rum per il nostro nuovo ospite! È un'occasione speciale o sei passato solo per bagnarti il fischietto";
			link.l1 = "Sì, si può dire che è un'occasione speciale. Sto portando alcuni negri a Blueweld. Ho recentemente modificato la stiva del mio nuovo brigantino appositamente per questo scopo. Mi sono fermato in una piantagione e ho parlato con il sorvegliante, ha ordinato un bel lotto di 'avorio nero' da me. Quindi aspettami di nuovo nella tua taverna presto. Consegnarò la merce a Blueweld e poi farò un po' più di affari qui a Barbados, yo ho!";
			link.l1.go = "TavernDone_1";
		break;
		
		case "TavernDone_1":
			dialog.text = "Davvero? Beh, non c'è vergogna nel bere per un buon affare! Quindi, dici che farai affari a Barbados? Fantastico! Alla tua salute, capitano!";
			link.l1 = "Grazie mille, compagno. Bene... vado a cercare un posto dove posso sedermi.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-12");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "Tonzag_Letter":
			dialog.text = "Gaston ha lasciato la città due giorni dopo il tuo atto da 'commerciante'. Hai fatto uno spettacolo qui, ah! Il tuo inganno è stato scoperto rapidamente, questa città è piccola e i pettegolezzi viaggiano velocemente. Questo ha fatto sì che Gaston prendesse e se ne andasse. Nessuno lo ha più visto qui da allora. Ha lasciato una lettera per te, però\nHa chiesto di consegnarla personalmente a te nel caso tu ti presentassi qui prima di lui. A dire il vero, non sei il primo uomo che cerca Gaston. C'era un tipo grande con gli occhi a mandorla e uno vecchio, sembrava spagnolo o portoghese, non posso dirlo con certezza. Ma non posso dimenticare il suo volto, c'era qualcosa di molto strano in lui...";
			link.l1 = "Dammi quella lettera... Grazie!";
			link.l1.go = "Tonzag_Letter_1";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Bridgetown");
		break;
		
		case "Tonzag_Letter_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-22");
			AddQuestRecordInfo("LetterFromGaston", "1");
			pchar.questTemp.HWIC.Eng = "toCuracao";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);//закрыть дом Флитвуда
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//закрыть аптеку
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", true);//закрыть подземелье
			pchar.quest.Knippel_Shore.win_condition.l1 = "location";
			pchar.quest.Knippel_Shore.win_condition.l1.location = "Shore24";
			pchar.quest.Knippel_Shore.function = "KnippelOnCuracao";
			AddMapQuestMarkShore("Shore24", true);
		break;
		
		//Голландский гамбит /против всех/
		case "Tonzag_check"://начинаем проверять нашего ГГ по всем статьям
			if(sti(pchar.reputation.nobility) > 48)//высокая репа
			{
				// belamour legendary edition покажем критерии
				notification("Reputation Too Low! (Rogue)", "None");
				PlaySound("Voice\English\hambit\Ercule Tongzag-03.wav");
				dialog.text = "Non ho bisogno dei servizi di un mascalzone. Non ho nessun incarico da offrirti.";
				link.l1 = "Ehi, ehi. Con calma con il linguaggio, amico!";
				link.l1.go = "exit";
				break;
			}
			bool bOk = GetSummonSkillFromName(pchar, SKILL_F_LIGHT) > 34 || GetSummonSkillFromName(pchar, SKILL_FENCING) > 34 || GetSummonSkillFromName(pchar, SKILL_F_HEAVY) > 34 || GetSummonSkillFromName(pchar, SKILL_PISTOL) > 34;
			if(!bOk)//слабое фехтование
			{
				// belamour legendary edition покажем критерии -->
				notification("Skill Check Failed (35)", SKILL_F_LIGHT);
				notification("Skill Check Failed (35)", SKILL_FENCING);
				notification("Skill Check Failed (35)", SKILL_F_HEAVY);
				notification("Skill Check Failed (35)", SKILL_PISTOL);
				// <--
				dialog.text = "Capitano, sei troppo morbido. Ho bisogno di un combattente un po' più rispettabile di te. Torna quando imparerai a maneggiare quella spada che pendola dalla tua cintura. E un po' di precisione nel tiro non farebbe male neanche.";
				link.l1 = "Capisco. Allora ti farò visita più tardi.";
				link.l1.go = "exit";
				break;
			}
			PlaySound("Voice\English\hambit\Ercule Tongzag-02.wav");
			dialog.text = "Mh... Sei effettivamente puntuale. Ho un incarico che deve essere eseguito immediatamente. Se ti mostri in buona luce, ti presenterò ad alcune persone influenti. Ora ascolta, ecco cosa devi fare.";
			link.l1 = "Sono tutto orecchie.";
			link.l1.go = "Tonzag_task";
		break;
		
		case "Tonzag_task":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Bridgetown");
			pchar.questTemp.HWIC.Self.SpainCity = FindSpainCity();
			log_Testinfo(pchar.questTemp.HWIC.Self.SpainCity);
			dialog.text = "Un hidalgo è recentemente arrivato da Siviglia con l'intenzione di evitare alcune conseguenze indesiderate di un duello in Europa. Ma la vendetta non ha limiti e una nobile famiglia spagnola desidera che questo hidalgo sia morto. Adempie la loro richiesta con qualsiasi mezzo necessario\nPorta il dito dell'uomo con il suo anello come prova. Inoltre, porta tutti gli altri oggetti che troverai sul suo cadavere. Sei pronto a prendere il lavoro?";
			link.l1 = "Se il pagamento è buono, allora sono dentro.";
			link.l1.go = "Tonzag_task_1";
			link.l2 = "Lavorare come un assassino? Assolutamente no!";
			link.l2.go = "Tonzag_exit";
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Self = "true";//признак, что против всех уже бралась
		break;
		
		case "Tonzag_exit":
			dialog.text = "Allora vaffanculo e dimentica di quello che abbiamo parlato.";
			link.l1 = "Me ne sto andando.";
			link.l1.go = "exit";	
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//откат к двум другим вариантам
			pchar.questTemp.HWIC.Fail3 = "true";
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
			{
				AddMapQuestMarkCity("Villemstad", false);
				AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			}
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
			{
				AddMapQuestMarkCity("SentJons", false);
				AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			}
		break;
		
		case "Tonzag_task_1":
			dialog.text = "La tua ricompensa sarà di 30.000 pezzi di otto, buoni soldi. Oltre a ciò, puoi prendere ogni moneta che troverai sul suo corpo. Ora discutiamo i dettagli. Si chiama Don Fernando Rodriguez, 35 anni, alto, scuro, vestito come un ufficiale militare. È un buon marinaio e un schermidore esperto\nNon posso dirti dove trovarlo, tutto quello che so è che si trova da qualche parte nei Caraibi\nCerca in ogni città spagnola finché non l'hai trovato. Hai due mesi. Un'ultima cosa: sono a conoscenza di ciò che porta con sé, quindi non pensare nemmeno di nascondermi oggetti. Domande?";
			link.l1 = "Non ho nessuna domanda. Sono sulla mia strada!";
			link.l1.go = "Tonzag_task_2";	
		break;
		
		case "Tonzag_task_2":
			DialogExit();
			pchar.questTemp.HWIC.Self = "start";
			SetFunctionTimerCondition("TargetFernandoOver", 0, 0, 60, false); //таймер
			//SetFunctionExitFromLocationCondition("CreateMapMarksTonzag", pchar.location, false);
			AddQuestRecord("Holl_Gambit", "3-1");
			ReOpenQuestHeader("Holl_Gambit"); // данила . чтобы вышел из архива																				  
			Log_TestInfo(""+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Self.SpainCity)+"");
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Lucas"));
			DelLandQuestMark(characterFromId("Knippel"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			AddMapQuestMarkCity(pchar.questTemp.HWIC.Self.SpainCity, true);
			AddLandQuestMark(characterFromId(pchar.questTemp.HWIC.Self.SpainCity+"_tavernkeeper"), "questmarkmain");
		break;
		
		case "Task_check":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("bridgetown");
			dialog.text = "Hai con te un dito con l'anello? Fammi vedere.";
			if (CheckCharacterItem(pchar, "Finger"))
			{
				link.l1 = "Sì, certo. Eccolo qui.";
				link.l1.go = "Task_check_1";	
			}
			else
			{
				link.l1 = "No. Fernando è affondato nell'acqua insieme alla sua nave e il dito è affondato con Fernando.";
				link.l1.go = "Task_fail";	
			}
		break;
		
		case "Task_fail":
			dialog.text = "La dito con l'anello era una condizione obbligatoria nel contratto. Doveva servire come conferma della morte del cliente. Chi sa se Rodriquez ha nuotato fino alla riva dalla nave affondata? Hai controllato? No. Hai sostanzialmente fallito l'incarico, quindi il nostro accordo è finito. Tutto il meglio.";
			link.l1 = "Ma l'ho eliminato. Se ne è andato! Oh, vaffanculo... C'è un sacco di altre cose da fare nei Caraibi. Addio.";
			link.l1.go = "exit";
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
			{
				AddMapQuestMarkCity("Villemstad", false);
				AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			}
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
			{
				AddMapQuestMarkCity("SentJons", false);
				AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			}
			pchar.questTemp.HWIC.Fail3 = "true";
			AddQuestRecord("Holl_Gambit", "3-8");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//зачищаем для возможности отката к голландскому варианту
		break;
		
		case "Task_check_1":
			RemoveItems(PChar, "Finger", 1);
			dialog.text = "Meraviglioso! Mi terrò il dito io. Ora per il contenuto delle sue tasche. Vediamo cosa hai portato.";
			link.l1 = "Vai avanti, dai un'occhiata...";
			link.l1.go = "Task_check_2";	
		break;
		
		case "Task_check_2":
			if (CheckCharacterItem(pchar, "jewelry7") && CheckCharacterItem(pchar, "totem_05") && CheckCharacterItem(pchar, "amulet_1"))
			{
				dialog.text = "Aha, è tutto ciò di cui ho bisogno. Ben fatto! Hai fatto un buon lavoro. Sono molto soddisfatto di te.";
				link.l1 = "Grazie! È sempre bello essere lodato per un lavoro ben fatto.";
				link.l1.go = "Task_complete";	
			}
			else
			{
				dialog.text = "Mh... Ti avevo avvertito che so cosa Rodriguez non farebbe mai a meno. E non vedo quello di cui ho bisogno qui. Hai messo quelle cose in tasca? Le hai perse? Non importa comunque. Non ho più voglia di avere a che fare con te. Vattene da qui.";
				link.l1 = "Oh, vaffanculo...";
				link.l1.go = "exit";
				pchar.questTemp.HWIC.Fail3 = "true";
				if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
				{
					AddMapQuestMarkCity("Villemstad", false);
					AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
				}
				if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
				{
					AddMapQuestMarkCity("SentJons", false);
					AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
				}
				AddQuestRecord("Holl_Gambit", "3-9");
				CloseQuestHeader("Holl_Gambit");
				DeleteAttribute(pchar, "questTemp.HWIC.Self");//зачищаем для возможности отката к голландскому варианту
			}
		break;
		
		case "Task_complete":
			RemoveItems(PChar, "jewelry7", 1);
			RemoveItems(PChar, "totem_05", 1);
			RemoveItems(PChar, "amulet_1", 1);
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "Ecco la tua ricompensa come promesso, trentamila. E ho anche un incarico aggiuntivo, ad alto rischio e responsabilità, ma il compenso salirà di conseguenza, 40.000 pesos.";
			link.l1 = "Sono tutto orecchie. Chi è il prossimo cliente?";
			link.l1.go = "Fleetwood_house";	
		break;
		
		//2 задание
		case "Fleetwood_house":
			PlaySound("Voice\English\hambit\Ercule Tongzag-05.wav");
			dialog.text = "Questa volta dovrai cacciare non un uomo, ma un oggetto. Devi intrufolarti nella casa di Richard Fleetwood ad Antigua e rubare il suo registro. È un capitano inglese. Il posto è strettamente sorvegliato e Richard raramente visita la sua casa\nIl piano è semplice. Il governatore di St. Jones organizzerà una festa privata tra dieci giorni, Fleetwood parteciperà. Devi entrare nella sua casa di notte tra l'una e le tre. Ci sarà solo un soldato dentro\nSbarazzati di lui. Cerca un diario nell'appartamento di Richard. Prendi questa chiave.";
			link.l1 = "Mh... Interessante. Ho capito cosa devo fare. Sono pronto a partire!";
			link.l1.go = "Fleetwood_house_1";	
		break;
		
		case "Fleetwood_house_1":
			GiveItem2Character(pchar, "key3");
			dialog.text = "Fai attenzione. Non intrufolarti nella casa prima della data che ti ho indicato. Altrimenti, nel migliore dei casi, ti cacciano solo da lì o nel peggiore dei casi, finirai dietro le sbarre. Ripetimi la data e l'ora.";
			link.l1 = "Tra esattamente dieci giorni, tra l'una e le tre del mattino.";
			link.l1.go = "Fleetwood_house_2";	
		break;
		
		case "Fleetwood_house_2":
			dialog.text = "Bene. Puoi andare. Buona fortuna!";
			link.l1 = "Grazie, Gaston.";
			link.l1.go = "Fleetwood_house_3";
		break;
		
		case "Fleetwood_house_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-10");
			pchar.questTemp.HWIC.Self = "theft";
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
			LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//комнату закроем
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.FleetwoodJournal = 1;//положим в комод СЖ
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.sand_clock = 1;//и песочные часы
			AddDialogExitQuestFunction("CreateFleetwoodSoldiers");//4 солдат в доме
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("FleetwoodJournalOver", 0, 0, 11, false);//таймер
			pchar.quest.Fleetwood_Journal.win_condition.l1 = "Timer";
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l2 = "Hour";
			pchar.quest.Fleetwood_Journal.win_condition.l2.start.hour = 0;
			pchar.quest.Fleetwood_Journal.win_condition.l2.finish.hour = 3;
			pchar.quest.Fleetwood_Journal.win_condition.l3 = "locator";
			pchar.quest.Fleetwood_Journal.win_condition.l3.location = "SentJons_town";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator_group = "reload";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator = "houseSP3";//доступно открывание двери
			pchar.quest.Fleetwood_Journal.function = "FleetwoodHouseEnter";
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";//если надумает раньше заявиться
			AddMapQuestMarkCity("sentjons", true);
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("No, non l'ho fatto. Abbiamo erboristi e medici, ma nessuno con un nome del genere.","È la prima volta che sento un nome così strano. No, l'uomo di cui parli non è mai venuto a trovarci.","Non abbiamo nessun tipo di alchimisti. Abbiamo dei medici, ma nessuno con un nome così strano.");
			link.l1 = "Capisco. Che peccato. Continuerò a cercare!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

string FindSpainCity()//Jason выбрать радномный испанский город - пусть побегает
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation == SPAIN && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}

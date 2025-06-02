// диалог коменданта форта
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
   /*NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}*/
    // вызов диалога по городам <--

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		
		case "First time":
			location = &Locations[FindLocation(pchar.location)];
			if (rand(4) == 4 && GetNpcQuestPastDayParam(location, "gun_date") > 365 && !CheckAttribute(pchar, "questTemp.PrisonGun"))
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Ascolta, ho un affare importante con te. Spero davvero che tu possa aiutare.","Capitano, posso interessarti a un'offerta piuttosto proficua?"),RandPhraseSimple("Credo che tu possa aiutarci in un affare importante.","Capitano, ho una proposta delicata per te, che potrebbe essere molto redditizia per entrambi."));					
				link.l1 = "Bene, parla pure, e vedremo...";
				link.l1.go = "GiveTaskGun";
				location.quest.PrisonGun = "Target"; 
				SaveCurrentNpcQuestDateParam(location, "gun_date");
				break;
			}
		
			dialog.text = RandPhraseSimple("Sono il comandante del forte. Di che cosa hai bisogno qui?","Di che cosa hai bisogno? Perché sei venuto qui?");
			link.l1 = "Oh, niente, solo un giro per la città e dintorni. Sono arrivato qui solo per puro caso.";
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// Офицер с патентом
			if(IsOfficerFullEquip())
			{
				dialog.text = "Benvenuto al forte, capitano. Hai bisogno di qualcosa?";
				link.l1 = "No, niente, sono solo passato a caso.";
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Saluti Vice Ammiraglio! Avete qualche ordine?";
				link.l1 = "No, ufficiale, nessun ordine. Sono venuto solo per vedere il forte.";
			}
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Governatore Generale, Vostra Grazia! Ho l'ordine completo nel forte. Ci saranno ordini?";
				link.l1 = "Sono contento che tu stia bene, ufficiale. Nessun ordine, sono solo passato a controllare il forte.";
			}
			// <-- legendary edition
			link.l1.go = "exit";
			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_ammo" && GetQuestPastDayParam("questTemp.Wine_bottle") < 5)
			{
				link.l11 = "Ho una notizia interessante per te, ufficiale. Uno dei tuoi soldati, "+pchar.questTemp.Wine.SName+" mi ha chiesto di comprare del vino in città tramite la mia mediazione. Considerando i tuoi ordini...";
				link.l11.go = "Wine_prison";
			}
			// <-- мини-квест Дефицитный товар
			// Карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "fraht" && NPChar.location == "portpax_ammo")
			{
				link.l11 = "Salve, ufficiale. Vengo dalla colonia di Basse-Terre, su ordine di un uomo di nome Gerard LeCroix. Ho un carico di polvere da sparo e bombe per te nella mia stiva...";
				link.l11.go = "trial";
			}
			// Опасный груз -->
			if (pchar.location == "Cumana_Ammo")
			{
				if (pchar.questTemp.zpq != "begin" && pchar.questTemp.zpq != "failed" && pchar.questTemp.zpq != "completed")
				{
					link.l2 = "Sembri preoccupato, ufficiale. Come posso aiutarti?";
					link.l2.go = "zpq_prs1";
				}
				if (pchar.questTemp.zpq == "begin" && GetSquadronGoods(pchar, GOOD_POWDER) >= 15000 && GetQuestPastDayParam("pchar.questTemp.zpq") >= 7)
				{
					link.l3 = "Sono pronto a riferire che l'intero carico di polvere da sparo è stato consegnato. La mia nave è pronta per lo scarico.";
					link.l3.go = "zpq_ex";
				}
				if (pchar.questTemp.zpq == "begin")
				{
					link.l4 = "Voglio rifiutare il nostro accordo sulla polvere da sparo. È troppo problematico.";
					link.l4.go = "zpq_fld2";
				}
			}
			// <-- Опасный груз
			NextDiag.TempNode = "First time";
		break;

		// --> Орудия для форта
		case "GiveTaskGun":
			dialog.Text = LinkRandPhrase("Vedi, i cannoni del forte sono piuttosto logori. Il tesoro ha assegnato dei fondi per sostituirli, ma semplicemente non ho idea di dove acquistare quelli nuovi: non c'è proprio modo di trovarli nella nostra colonia nella quantità richiesta. Quindi, ho pensato che le armi dalle navi che hai abbordato potrebbero essere molto utili per noi qui.","Devo sostituire la batteria di cannoni del forte. I fondi sono già stati stanziati, ma, sai... È semplicemente impossibile acquistare la quantità necessaria nella nostra colonia.","Mi è stato affidato il compito di sostituire i cannoni logori del forte, ma non riesco proprio a trovarne abbastanza da nessuna parte.");
			Link.l1 = "Mmm... Puoi entrare un po' più nel dettaglio? Calibro, quantità, prezzo?";
			Link.l1.go = "GiveTaskGun_1";
			pchar.questTemp.PrisonGun = true;
			SaveCurrentQuestDateParam("pchar.questTemp.PrisonGun");
		break;
			
		case "GiveTaskGun_1":
			GetGunType();
			pchar.questTemp.PrisonGun.Sum = makeint(sti(pchar.questTemp.PrisonGun.Price)*sti(pchar.questTemp.PrisonGun.Qty));
			pchar.questTemp.PrisonGun.Luck = rand(4);
			pchar.questTemp.PrisonGun.Id = npchar.location;
			dialog.Text = "Ho bisogno "+pchar.questTemp.PrisonGun.Text+", nella quantità di "+sti(pchar.questTemp.PrisonGun.Qty)+"  unità esattamente. Pagherò in dobloni d'oro, "+sti(pchar.questTemp.PrisonGun.Price)+" per un pezzo. Questo ammonta a "+FindRussianDublonString(sti(pchar.questTemp.PrisonGun.Sum))+" in totale. Cosa dirai? Ah, e un'altra cosa - accetterò l'intero lotto, ma non prima di un mese - i soldi non sono ancora arrivati.";
			Link.l1 = RandPhraseSimple("No, ufficiale, la tua offerta non mi ha interessato affatto... Mi dispiace.","È allettante, ma credo di rinunciare. Permettimi di tenere le mie ragioni per me.");
			Link.l1.go = "exit_gun";
			Link.l2 = RandPhraseSimple("Ebbene, quell'offerta è certamente interessante. Consideriamola un affare.","Immagino che lo prenderò. Non è così difficile e chiaramente redditizio.");
			Link.l2.go = "GiveTaskGun_2";
		break;
			
		case "exit_gun":
			dialog.Text = "Che peccato, capitano, contavo su di te. E... spero davvero che questa conversazione rimanga dentro il forte?";
			Link.l1 = "Non devi ricordarmi di quello. I miei migliori saluti.";
			Link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
			
		case "GiveTaskGun_2":
			dialog.Text = "Ebbene, allora abbiamo un accordo! Non ti sto imponendo termini precisi, ma per favore, cerca di non protrarlo per oltre mezzo anno. E spero tu capisca che questa è una questione strettamente confidenziale?";
			Link.l1 = "Certo che lo faccio. Ci vediamo, comandante.";
			Link.l1.go = "exit";
			ReOpenQuestHeader("PrisonGun");
			AddQuestRecord("PrisonGun", "1");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			AddQuestUserData("PrisonGun", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("PrisonGun", "sQty", makeint(pchar.questTemp.PrisonGun.Qty));
			AddQuestUserData("PrisonGun", "sSum", makeint(pchar.questTemp.PrisonGun.Sum));
			AddQuestUserData("PrisonGun", "sText", pchar.questTemp.PrisonGun.Text);
			NextDiag.TempNode = "First time";
		break;	
		
		case "CheckGun":
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") < 30)
			{
				dialog.Text = "Ti ho detto di non venire prima di un mese!";
				Link.l1 = "Maledizione! Ero così occupato"+GetSexPhrase("","")+", che ho perso un"+GetSexPhrase("","")+" perdo la cognizione del tempo ... Scusa, verrò più tardi, come concordato.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				break;
			}
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") > 180)
			{
				dialog.Text = "Hmm... Sai, è passato più di mezzo anno da quando abbiamo stretto il nostro 'accordo'. Ho già acquistato i cannoni. Pensavi davvero che ti avrei aspettato per sempre?";
				Link.l1 = "Maledizione! E cosa dovrei fare con loro adesso?";
				Link.l1.go = "TakeGun_late";
				break;
			}
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = GetSquadronGoods(Pchar, iGunGoods) - sti(pchar.questTemp.PrisonGun.Qty);
			sTemp = sti(pchar.questTemp.PrisonGun.Qty);
			iTest = FindColony(NPChar.City); // город
			
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.Text = "Sì, sei pronto ad aiutarmi?";
				if (amount < 0)
				{
					Link.l1 = "No, è ancora in corso. Volevo solo assicurarmi che il nostro accordo sia ancora valido.";
					Link.l1.go = "exit";
				}
				else
				{
					Link.l1 = "Sono io. L'intero carico è nella stiva - "+sTemp+" unità, come era stato concordato.";
					Link.l1.go = "TakeGun";
				}
			}
			else 
			{
				dialog.text = "Non vedo la tua nave nel porto. Stai suggerendo di trascinare quei cannoni attraverso la giungla? Fai presto al nostro porto e torna.";
				link.l1 = "La mia nave è dall'altra parte dell'isola. La porterò al porto.";
				link.l1.go = "exit";
			}
		break;
		
		case "TakeGun":
			if (pchar.questTemp.PrisonGun.Luck == 4)
			{
				dialog.Text = RandPhraseSimple("Sai, è davvero imbarazzante, ma devo denunciare il nostro accordo. Abbiamo appena avuto un'ispezione finanziaria, e sai quanto siano scrupolosi in queste cose. Non posso fare nulla. Mi dispiace.","Capitano, sai... Beh, ci hanno mandato dei cannoni dalla metropoli, e ovviamente sono stato costretto a comprarli. Prezzi esorbitanti, ma... Mi dispiace davvero di averti deluso... Neanche a me fa piacere, sai.");
				Link.l1 = "Maledizione! E cosa diavolo dovrei fare con loro adesso?";
				Link.l1.go = "TakeGun_no";
			}
			else
			{
				dialog.Text = RandPhraseSimple("Eccellente. Manderò una squadra dalla guarnigione per scaricarli.","Eccellente. I miei soldati ti aiuteranno a scaricare i cannoni.");
				Link.l1 = "Hai preparato il pagamento?";
				Link.l1.go = "TakeGun_1";
			}
		break;
		
		case "TakeGun_no":
			dialog.Text = "Non lo so. Vendili al cantiere navale, equipaggia una nave da commercio, affondali... davvero non ne ho idea. E per favore, non dire a nessuno di questo affare.";
			Link.l1 = "Oh, dici così! Sono senza parole!";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "3");
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_late":
			dialog.Text = "Non ne ho idea. È un tuo problema. Vendili, buttali via, affondali - davvero non me ne importa.";
			Link.l1 = "Oh, è stato semplicemente uno spreco di tempo...";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "4");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_1":
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = sti(pchar.questTemp.PrisonGun.Qty);
			iTemp = sti(pchar.questTemp.PrisonGun.Sum);
			dialog.Text = "Certo. Ecco il tuo oro - fai come vuoi.";
			Link.l1 = "Grazie! È stato un piacere fare affari con te!";
            Link.l1.go = "TakeGun_2";
			TakeNItems(pchar, "gold_dublon", iTemp);
			Log_Info("You have received "+FindRussianDublonString(sti(pchar.questTemp.WPU.Escort.Money))+"");
			PlaySound("interface\important_item.wav");
			RemoveCharacterGoods(Pchar, iGunGoods, amount);
		break;
		
		case "TakeGun_2":
			dialog.Text = "È un sentimento reciproco. Sei stato molto utile. E, ti prego, mantieni quel patto in questa stanza.";
			Link.l1 = "Certo. I miei migliori auguri a te.";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "2");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		// <-- орудия для форта

		//Jason --> мини-квест Дефицитный товар
		case "Wine_prison":
			dialog.text = "Cosa?! Ho proibito severamente di bere nel territorio del forte! Beh, dovrà pagare per questo. Detrarro 1000 pesos dal suo pagamento e li consegnerò a te come ricompensa per la tua vigilanza. E questo ragazzo resterà in detenzione per tre giorni.";
			link.l1 = "Grazie, "+GetAddress_FormToNPC(NPChar)+". Fermare tali violazioni è il nostro dovere comune.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 1000);
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
			pchar.quest.Wine_Exchange.over = "yes";//снять прерывание
			pchar.quest.WineTraderQM.over = "yes";//снять прерывание
			WineTraderQMDel();
			sld = characterFromId(pchar.questTemp.Wine.id);
			sld.lifeday = 0;
			CloseQuestHeader("Wine");
			NextDiag.TempNode = "First time";
		break;
		// <-- мини-квест Дефицитный товар
		
		// Карибские нравы
		case "trial":
			iTest = FindColony(NPChar.City); // город
			QuestPointerDelLoc("portpax_town", "reload", "gate_back");
			QuestPointerDelLoc("portpax_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("portpax_fort", "reload", "reload2");
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetSquadronGoods(pchar, GOOD_BOMBS) < 2500 || GetSquadronGoods(pchar, GOOD_POWDER) < 2500)
				{
					dialog.text = "Mmm. Ma questa partita non è completa! Come è potuto succedere?";
					link.l1 = "Accidenti! Perdonami, è colpa mia. Acquisterò immediatamente la quantità mancante e ti consegnerò l'intero lotto, come abbiamo concordato.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Allora sei il nostro corriere? Bene. Mettiamo a posto le cose con il carico, e poi riceverai ulteriori istruzioni.";
					link.l1 = "Bene.";
					link.l1.go = "trial_1";
				}
			}
			else
			{
				dialog.text = "Non vedo la tua nave nel porto. Suggerisci di trascinare il carico attraverso la giungla? Fa' presto a raggiungere il nostro porto e torna.";
				link.l1 = "La mia nave è dall'altra parte dell'isola. La porterò al porto.";
				link.l1.go = "exit";
			}
		break;
		
		case "trial_1":
			if(!bImCasual) pchar.quest.Trial_FrahtFail.over = "yes"; // belamour legendary edition если был - снять таймер
			dialog.text = "Bene, bombe e polvere da sparo, 2500 unità ciascuna... Ottimo. I soldati scaricheranno il carico, i tuoi uomini possono prendersi una pausa. Ecco il tuo pagamento per il trasporto - cinquemila pesos.";
			link.l1 = "Grazie! Cosa dovrei fare dopo? Monsieur LeCroix ha detto...";
			link.l1.go = "trial_2";
			DelLandQuestMark(npchar);
		break;
		
		case "trial_2":
			AddMoneyToCharacter(pchar, 5000);
			RemoveCharacterGoods(pchar, GOOD_BOMBS, 2500);
			RemoveCharacterGoods(pchar, GOOD_POWDER, 2500);
			dialog.text = "Sì, sì, riceverai ora le tue istruzioni. Sei pronto a prestare attenzione?";
			link.l1 = "Certo, ufficiale.";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "So, our military ship 'Warlike' is cruising near the Spanish colony Porto Bello, in the southern part of the Spanish Main. This vessel is under the command of Florian Shoke, who is preparing an ambush of a Spanish heavy galleon set to leave Porto Bello in two weeks.\nThe problem is that our frigate's cannons are suffering from a casting defect, and we need to replace fifteen cannons to save the mission; otherwise, the galleon will outnumber 'Warlike' in both guns and men. \nWithout the replacement, Florian Shoke will be forced to sail away with no result. Such a sequence of events is highly undesirable. Your task is to save the mission by delivering fifteen cannons within fourteen days.";
			link.l1 = "Allora, devo prendere a bordo quindici cannoni, dirigermi verso Portobello, cercare la fregata 'Militant' e consegnare i cannoni al capitano Florian Shoke?";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "Esatto. Hai capito bene. Sei pronto a intraprendere questa missione?";
			link.l1 = "E per il pagamento?";
			link.l1.go = "trial_5";
			link.l2 = "Mi dispiace, ufficiale, ma non voglio semplicemente coinvolgermi. Mi scusi.";
			link.l2.go = "trial_exit";
		break;
		
		case "trial_exit":
			dialog.text = "Hai ragione, ma contavo sul tuo consenso. Ora dovrò trovare un altro corriere, anche se non mi resta molto tempo... Beh, non ti tratterrò più a lungo, capitano.";
			link.l1 = "Cordiali saluti.";
			link.l1.go = "trial_exit_1";
		break;
		
		case "trial_exit_1":
			DialogExit();
			AddQuestRecord("Trial", "6");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "trial_5":
			dialog.text = "Non preoccuparti di quello. Florian Shoke ti pagherà duecento dobloni d'oro dalla tesoreria della nave. Inoltre, sono certo che vorrebbe utilizzare te e la tua nave per i suoi scopi - con il tuo consenso, ovviamente.";
			link.l1 = "Bene, sono in questa missione! Dove sono i cannoni?";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "Darò l'ordine ai soldati di caricarli immediatamente sulla tua nave. Mettiti in mare appena puoi, monsieur! Buona fortuna!";
			link.l1 = "Grazie. La fortuna di certo non farà male, e nemmeno il vento in poppa...";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			DialogExit();
			AddQuestRecord("Trial", "7");
			pchar.questTemp.Trial = "cannon";
			// belamour legendary edition
			if(!bImCasual) SetFunctionTimerCondition("Trial_CannonFail", 0, 0, 21, false); 
			else NewGameTip("Exploration mode: timer is disabled.");
			SetCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24)+15);
			if (MOD_SKILL_ENEMY_RATE >= 6)
			{
				EnemyNationHunterOnMap(true);//запуск перехватчиков
			}
			pchar.quest.Trial_cannon.win_condition.l1 = "location";
			pchar.quest.Trial_cannon.win_condition.l1.location = "Portobello";
			pchar.quest.Trial_cannon.function = "Trial_CreateFlorianFrigate";
			// Sinistra - квест "Встреча с Диего"
			bDisableFastReload = true;
			PChar.quest.VsD_GiumDyubua.win_condition.l1 = "location";
			PChar.quest.VsD_GiumDyubua.win_condition.l1.location = "PortPax_Fort";
			PChar.quest.VsD_GiumDyubua.win_condition = "VsD_GiumDyubua";
			AddMapQuestMarkShore("Shore47", false);
		break;
		
		// Опасный груз -->
		case "zpq_prs1":
			if(!isBadReputation(pchar, 70))
			{
				dialog.text = "Mh, forse. Beh, grazie alla tua buona reputazione, mi rischierò a fidarmi di te. In un altro caso, non ne avrei nemmeno parlato con te. Il fatto è che abbiamo bisogno di un lotto piuttosto grande di merce speciale, quindi avrai bisogno di una nave da carico di grandi dimensioni e una volontà di rischiare. Inoltre, devi darmi la parola di non dire nulla a nessuno su di esso.\nSe lo trovi imbarazzante, allora dimmelo subito. Penso di aver reso chiaro il mio punto...";
				link.l1 = "Sembra intrigante. Sono dentro se il pagamento è buono, anche se non ho idea di quale carico stai parlando. Hai comunque la mia parola.";
				link.l1.go = "zpq_prs2";
				link.l2 = "Direi di no, suppongo... se ti dessi la mia parola, dovrei fare un lavoro che sembra piuttosto fastidioso. Non lo farò.";
				link.l2.go = "zpq_fld";
				notification("Reputation Check Passed", "None");
			}
			else
			{
				dialog.text = "La tua reputazione è inaccettabile per me. Ti chiedo di lasciare la stanza. Siamo in grado di risolvere i nostri problemi da soli.";
				link.l1 = "Comunque, risolvili allora...";
				link.l1.go = "exit";
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
			}		
		break;
		
		case "zpq_fld":
			dialog.text = "Bene, almeno mi hai rifiutato in modo onesto... Non ti tratterrò più.";
			link.l1 = "Addio.";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "failed";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Cumana");
		break;
		
		case "zpq_fld2":
			dialog.text = "Mh, in realtà non me lo aspettavo da te. Devo chiederti di andartene... E ricorda la tua promessa di non divulgare alcuna informazione.";
			link.l1 = "Mi dispiace...";
			link.l1.go = "exit";
    		ChangeCharacterComplexReputation(pchar,"nobility", -3);
			if (pchar.questTemp.zpq == "begin")
			{
				AddQuestRecord("zpq", "6");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
				CloseQuestHeader("zpq");
			}
			pchar.questTemp.zpq = "failed";
		break;
		
		case "zpq_prs2":
			dialog.text = "Splendido. Splendido. Il problema è che la recente tempesta ha danneggiato la nostra riserva di polvere da sparo nell'arsenale della fortezza. Spero di non dovervi spiegare che abbiamo un problema delicato qui. In caso di un lungo assedio, la fortezza non sarà in grado di fare nulla. Non dureremo a lungo.";
			link.l1 = "Ora capisco. Che tipo di carico ti serve - e di quale quantità?";
			link.l1.go = "zpq_prs3";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Cumana");
		break;
		
		case "zpq_prs3":
			dialog.text = "Abbiamo bisogno di 15 000 barili di polvere da sparo. Ti pagherò 100 000 pesos... Devi capire che è un prezzo molto buono. Il nostro stato attuale mi costringe ad andare con tali costi anche se è stato difficile convincere il cassiere del governatore... La stagione delle tempeste non ci permetterà di utilizzare le nostre linee di approvvigionamento e non vogliamo che tutti sappiano di questo guaio...";
			link.l1 = "Capisco... il prezzo è davvero interessante. Hai menzionato dei rischi...";
			link.l1.go = "zpq_prs4";
		break;
		
		case "zpq_prs4":
			dialog.text = "Intendevo dire che un quantitativo così grande di polvere da sparo può essere molto pericoloso durante il trasporto. Ho visto qualche esplosione con i miei occhi, a volte una singola scintilla può fare il lavoro. Ma se affronti la tempesta... I convogli di solito mantengono le distanze dal potenziale incendiario. Se esplode, allora tutti sono morti!";
			link.l1 = "Capisco... Ma mantengo sempre la mia parola, consideralo fatto.";
			link.l1.go = "zpq_prs5";
			link.l2 = "Ebbene, signore... Mi hai raccontato cose così terribili, che ho perso ogni voglia di fare quel lavoro.";
			link.l2.go = "zpq_fld2";
		break;
		
		case "zpq_prs5":
			dialog.text = "Bene, sono molto contento che abbiamo fatto un affare. Ti pagherò non appena mi porterai il carico.\nAvrò i soldi tra una settimana, non prima, quindi prenditi il tuo tempo ma ti chiederei di cercare di non ritardare troppo.";
			link.l1 = "Capisco, signore. Mi sto occupando di questo.";
			link.l1.go = "zpq_prs5_ok";
		break;
		
		case "zpq_prs5_ok":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.zpq = "begin";
			pchar.questTemp.zpq.time = 20;
			AddQuestRecord("zpq", "1");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
			SaveCurrentQuestDateParam("pchar.questTemp.zpq");
		break;
		
		case "zpq_ex":
			dialog.text = "Finalmente! Pensavo che ti fossi già dimenticato del nostro accordo. Ordinerò subito ai miei soldati di iniziare a scaricare la tua nave. Lavorare con la polvere da sparo è un affare molto delicato, ah-ah!";
			link.l1 = "È fantastico, signore, ma devo ricordarvi del pagamento.";
			link.l1.go = "zpq_ex2";
			RemoveCharacterGoods(pchar, GOOD_POWDER, 15000);
			AddCharacterExpToSkill(pchar, "Sailing", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 500);

            pchar.quest.zpq_sld1_fc.win_condition.l1 = "location";
            pchar.quest.zpq_sld1_fc.win_condition.l1.location = "Cumana_ExitTown";
            pchar.quest.zpq_sld1_fc.function = "zpq_sld1_fc";
		break;
		
		case "zpq_ex2":
			dialog.text = "Sì, naturalmente. Sarai pagato 50 000 pesos come abbiamo concordato.";
			link.l1 = "Stai probabilmente scherzando con me, signore?! Avevamo un accordo su 100 000 pesos!";
			link.l1.go = "zpq_ex3";
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l2 = "(Affidabile) Comincio a pensare che tu voglia imbrogliarmi, quindi non me ne andrò da qui senza i miei 125 000 pesos!";
				link.l2.go = "zpq_ex4";
			}
			link.l3 = "Mm.. Vedo che le circostanze sono cambiate. Beh, è meglio che prendo i soldi e me ne vada...";
			link.l3.go = "zpq_ex5";
		break;
		
		case "zpq_ex3":
			if (GetSummonSkillFromName(pchar, "Leadership") > 35)
			{
				notification("Skill Check Passed", "Leadership");
				dialog.text = "Ah, sì... Esatto! 100 000 pesos. Me ne ero dimenticato, perdonami. È la mia età da biasimare, sai, la sclerosi... Certo, ecco le tue monete. È stato un piacere fare affari con te, capitano. Ora mi dispiace, ma ho molto lavoro da fare...";
				link.l1 = "Lo stesso a te, signore. Ci vediamo.";
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
				AddQuestRecord("zpq", "2");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
				CloseQuestHeader("zpq");
				pchar.questTemp.zpq.sum = 100000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			}
			else
			{
				notification("Skill Check Failed (36)", "Leadership");
				dialog.text = "Cosa?! Prendi i tuoi soldi e sparisci, o marciresti in questa casamatta!";
				link.l1 = "Sei un bugiardo, signore! Ti consiglio di darmi i miei soldi in buona fede, o ti toglierò il carico!";
				link.l1.go = "zpq_ex_agry";
				link.l2 = "Scusami... Va bene, accetterò la somma che offri e abbiamo finito.";
				link.l2.go = "zpq_ex5";
				Log_info("Leadership skill is not sufficient");
			}
		break;
		
		case "zpq_ex4":
				dialog.text = "Che maleducazione! Non sono pazzo e ricordo perfettamente di aver offerto 100.000 pesos.\n Accidenti! Non giocherò ai tuoi giochi!";
				link.l1 = "Calmati. Pensa al brander pronto riempito di polvere da sparo proprio davanti al tuo forte. Se dico solo una parola, il tuo forte si trasformerà in rovine.";
				link.l1.go = "zpq_ex6";
		break;
		
		case "zpq_ex6":
			dialog.text = "Hm-Hm... argomento forte. 125 000 pesos, dici? Prendili, e perdonami adesso ma ho un lavoro da fare...";
			link.l1 = "Addio, signore. Ci vediamo.";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "5");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 125000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			/*else
			{
				dialog.text = "Cosa?! Sono un ufficiale militare! Pensi di potermi spaventare, ragazzino?! Guardie, prendete "+GetSexPhrase("lui","lei")+"!";
				link.l1 = "Buona fortuna nel tentare, ratti delle prigioni...";
				link.l1.go = "zpq_ex_war";
			}*/
		break;
		
		case "zpq_ex5":
			dialog.text = "Splendido! Hai fatto la scelta giusta. Prendi le tue monete e arrivederci. È stato un piacere!";
			link.l1 = "Addio...";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "3");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 50000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
		break;
		
		case "zpq_ex_agry":
			dialog.text = "Ah, maledetto! Guardie, prendete "+GetSexPhrase("lui","lei")+"!";
			link.l1 = "Argh! Sembra che dovrò prendere i miei soldi dal tuo corpo senza respiro...";
			link.l1.go = "zpq_ex_war";
		break;
		
        case "zpq_ex_war":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetFightMode(PChar, true);
			pchar.questTemp.zpq = "failed";
            AddQuestRecord("zpq", "4");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 100000;
			AddMoneyToCharacter(npchar, makeint(sti(pchar.questTemp.zpq.sum)*2 + rand(5000)));
			GiveItem2Character(npchar, "blade_21");
			EquipCharacterbyItem(npchar, "blade_21");
			npchar.SaveItemsForDead  = true;
			npchar.DontClearDead = true;
			npchar.cirassId = Items_FindItemIdx("cirass3");
			chrDisableReloadToLocation = true;
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			LAi_group_SetCheck(slai_group, "OpenTheDoors");
			AddSimpleRumour("Such terrible things happen here! They say that some prisoner has escaped from the casemates! He slaughtered all the guards, stole the treasury, and just went away! Wow!", SPAIN, 5, 1);
		break;
		// <-- Опасный груз
	}
}

void GetGunType()
{
	int iGunType;
	if(makeint(pchar.rank) < 6) iGunType = rand(1);	//18&&24
	if(makeint(pchar.rank) >= 6 && makeint(pchar.rank) < 15) iGunType = rand(2); //24&&32	
	if(makeint(pchar.rank) >= 15 && makeint(pchar.rank) < 24) iGunType = rand(2)+2; //32&&36&&42
	if(makeint(pchar.rank) >= 24) iGunType = 5-rand(1); //36clv&&42
	int iAdd = makeint(GetSummonSkillFromName(pchar, SKILL_COMMERCE)/20);
	
	switch (iGunType)
	{
		case 0:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_24;     					
			pchar.questTemp.PrisonGun.Price = 28 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "24 calibre cannons";
		break; 
		case 1:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_18;     					
			pchar.questTemp.PrisonGun.Price = 25 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "couleuvrines";
		break; 
		case 2:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_32;     					
			pchar.questTemp.PrisonGun.Price = 32 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "32 calibre cannons";
		break; 
		case 3:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_36;     					
			pchar.questTemp.PrisonGun.Price = 36 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "36 calibre cannons";
		break;
		case 4:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_36;     					
			pchar.questTemp.PrisonGun.Price = 49 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "full couleuvrines";
		break; 
		case 5:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_42;     					
			pchar.questTemp.PrisonGun.Price = 40 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+20+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "42 calibre cannons";
		break; 
	}
}

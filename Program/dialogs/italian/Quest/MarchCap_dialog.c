void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp, iQty;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Un maledetto bug. Assicurati di segnalarlo agli sviluppatori.";
			link.l1 = "D'accordo.";
			link.l1.go = "exit";
		break;
		
		//разговор на палубе
		case "MarchCap":
			pchar.quest.MarchCapOver.over = "yes"; //снять прерывание
			dialog.text = "Eccoti qui, capitano. Parliamo nei dettagli della mia proposta. Capirai perché non volevo parlarne davanti a tutti.";
			link.l1 = "Avanti, signore. Vi ascolto.";
			link.l1.go = "MarchCap_1";
		break;
		
		case "MarchCap_1":
			pchar.GenQuest.MarchCap.Goods = SelectMarchCapGoods1();//целевой товар
			switch (rand(2))
			{
				case 0: //конвой у острова, установка параметров
					pchar.GenQuest.MarchCap.Island = GetRandIslandId();
					while(pchar.GenQuest.MarchCap.Island == pchar.GenQuest.MarchCap.Startisland)
					{
						pchar.GenQuest.MarchCap.Island = GetRandIslandId();
					}
					pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
					while(pchar.GenQuest.MarchCap.Island.Shore == "")
					{
						pchar.GenQuest.MarchCap.Island = GetRandIslandId();
						pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
						if (!isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island) || !isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island.Shore)) pchar.GenQuest.MarchCap.Island.Shore = "";
					}
					pchar.GenQuest.MarchCap.DaysQty = GetMaxDaysFromIsland2Island(pchar.GenQuest.MarchCap.Startisland, pchar.GenQuest.MarchCap.Island)+3;
					dialog.text = "Sono riuscito a scoprire che in "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" un piccolo convoglio mercantile sotto la bandiera di "+NationNameGenitive(sti(pchar.GenQuest.MarchCap.Nation))+", due navi mercantili e una nave di scorta, solcheranno le acque vicino a "+XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen")+", questo non è lontano da "+XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen")+". I mercanti hanno una gran quantità di "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" nelle loro stive. Sarebbe da sciocchi non approfittarne, capitano\nTu ed io possiamo sbarazzarci delle guardie senza problemi e prenderci il carico. Allora, ci stai?";
					link.l1 = "Suona allettante. Direi di sì!";
					link.l1.go = "MarchCap_1_1";
					link.l2 = "Qualcuni"+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" non basta perché io rovini i miei rapporti con "+NationNameAblative(sti(pchar.GenQuest.MarchCap.Nation))+"No, non ho intenzione di farlo! Addio, signore, e non provare nemmeno a fermarmi!";
					link.l2.go = "MarchCap_exit";
				break;
				
				case 1: //энкаунтер на глобалке, установка параметров
					pchar.GenQuest.MarchCap.Startcity = SelectAnyColony(pchar.GenQuest.MarchCap.basecity);
					pchar.GenQuest.MarchCap.Finishcity = SelectAnyColony2(pchar.GenQuest.MarchCap.basecity, pchar.GenQuest.MarchCap.Startcity);
					pchar.GenQuest.MarchCap.DaysQty = 5+hrand(5);
					dialog.text = "Sono riuscito a scoprire che a "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" un piccolo convoglio mercantile sotto la bandiera di "+NationNameGenitive(sti(pchar.GenQuest.MarchCap.Nation))+", due navi mercantili e una nave di scorta salperanno da "+XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Startcity+"Gen")+" a "+XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Finishcity+"Acc")+". I mercanti hanno un sacco di "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" nei loro stive. Sarebbe da sciocchi non approfittare di questa dritta, capitano.\nTu ed io possiamo sbarazzarci delle guardie senza fatica e prenderci il carico. Il più difficile sarà stanarli in mare aperto tra queste due colonie. Allora, ci stai?";
					link.l1 = "Suona allettante. Direi di sì!";
					link.l1.go = "MarchCap_2_1";
					link.l2 = "Un po' "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" non basta per farmi rovinare i rapporti con "+NationNameAblative(sti(pchar.GenQuest.MarchCap.Nation))+" No, non intendo farlo! Addio, signore, e non osare nemmeno cercare di fermarmi!";
					link.l2.go = "MarchCap_exit";
				break;
				
				case 2: //одиночный пиратский кулсейлор у бухты, установка параметров
					pchar.GenQuest.MarchCap.Goods = GOOD_GOLD + hrand(makeint(GOOD_SILVER - GOOD_GOLD));
					pchar.GenQuest.MarchCap.GoodsQty = sti(pchar.rank)*50+170+rand(30);
					if (sti(pchar.GenQuest.MarchCap.GoodsQty) > 1600) pchar.GenQuest.MarchCap.GoodsQty = 1500+rand(100);
					pchar.GenQuest.MarchCap.Island = GetRandIslandId();
					while(pchar.GenQuest.MarchCap.Island == pchar.GenQuest.MarchCap.Startisland)
					{
						pchar.GenQuest.MarchCap.Island = GetRandIslandId();
					}
					pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
					while(pchar.GenQuest.MarchCap.Island.Shore == "")
					{
						pchar.GenQuest.MarchCap.Island = GetRandIslandId();
						pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
						if (!isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island) || !isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island.Shore)) pchar.GenQuest.MarchCap.Island.Shore = "";
					}
					pchar.GenQuest.MarchCap.DaysQty = GetMaxDaysFromIsland2Island(pchar.GenQuest.MarchCap.Startisland, pchar.GenQuest.MarchCap.Island)+1;
					pchar.GenQuest.MarchCap.PirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);//пират
					pchar.GenQuest.MarchCap.ShipType = SelectPirateShipType();
					pchar.GenQuest.MarchCap.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.MarchCap.ShipType));
					dialog.text = "Mi hanno parlato di un certo pirata di nome "+GetName(NAMETYPE_ORIG,pchar.GenQuest.MarchCap.PirateName,NAME_NOM)+"   Questo mascalzone ha appena soffiato "+RandPhraseSimple(RandPhraseSimple("Inglese","Francese"),RandPhraseSimple("Spagnolo","Olandese"))+" e ha riempito la stiva con "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+". Ma, che peccato, la sua nave "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.ShipType),"Name")+"Acc"))+" era malmessa, quindi ha dovuto prendersi del tempo per rimetterla in sesto.\nAttualmente si trova a "+XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen")+" di "+XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen")+". Credo che ci vorranno circa "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" perché possa riparare alberi e falle nello scafo. Ci arriviamo in tempo se ci sbrighiamo e tutti noi "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" sarà nostra\nNon riuscirò mai a gestire questo filibustiere da solo, è un diavolo di marinaio e un combattente formidabile, ma in due possiamo affrontarlo, per quanto scaltro sia. Allora, ci stai o no?";
					link.l1 = "Sembra allettante. Direi di sì!";
					link.l1.go = "MarchCap_3_1";
					link.l2 = "Hm. Pare che questa preda sia irraggiungibile non solo per te, ma anche per entrambi noi. No, non ho intenzione di continuare, addio, signore, e non tentare nemmeno di fermarmi!";
					link.l2.go = "MarchCap_exit";
				break;
			}
		break;
		
		case "MarchCap_1_1":
			dialog.text = "Sapevo che potevo contare su di te! Non perdiamo neanche un battito di clessidra. Va' alla tua nave e prendi il comando, io ti seguirò. È ora di spiegare le vele!";
			link.l1 = "Ordina di salpare l’ancora, capitano!";
			link.l1.go = "MarchCap_1_2";
		break;
		
		case "MarchCap_1_2":
			DialogExit();
			NextDiag.CurrentNode = "MarchCap_repeat";
			Group_DelCharacter("MarchGroup", "MarchCap");
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			SetCharacterRemovable(npchar, false);
			Character_SetAbordageEnable(npchar, false);
			npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
			pchar.quest.MarchCap1_1.win_condition.l1 = "Timer";
			pchar.quest.MarchCap1_1.win_condition.l1.date.hour  = sti(GetTime()+rand(10));
			pchar.quest.MarchCap1_1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l2 = "location";
			pchar.quest.MarchCap1_1.win_condition.l2.location = pchar.GenQuest.MarchCap.Island;
			pchar.quest.MarchCap1_1.function = "MarchCap1_CreateConvoy";
			SetFunctionTimerCondition("MarchCap_Attack_Over", 0, 0, sti(pchar.GenQuest.MarchCap.DaysQty)+2, false); //таймер на нахождение
			pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
			pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
			ReOpenQuestHeader("MarchCap");
			AddQuestRecord("MarchCap", "1");
			AddQuestUserData("MarchCap", "sShore", XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen"));
			AddQuestUserData("MarchCap", "sIsland", XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen"));
			AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
			AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
		break;
		
		case "MarchCap_TimeOver":
			dialog.text = "E perché mai mi sono impelagato con te, capitano? A causa tua abbiamo perso un bottino di gran valore! La prossima volta navigherò da solo, maledizione...";
			link.l1 = "Colpa tua, non mia. Addio.";
			link.l1.go = "MarchCap_Talk_exit";
			pchar.GenQuest.MarchCap = "late";
		break;
		
		case "MarchCap_Talk_exit":
			pchar.quest.MarchCap1_fail2.over = "yes"; //снять прерывание
			pchar.quest.MarchCap1_fail1.over = "yes"; //снять прерывание
			pchar.quest.MarchCap1_fail.over = "yes"; //снять прерывание
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			DeleteAttribute(npchar, "AlwaysFriend");
			npchar.DontDeskTalk = true;
			if (CheckAttribute(pchar, "GenQuest.MarchCap.Deck"))
			{
				PChar.quest.Munity = "Deads";
				LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			}
			else
			{
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				chrDisableReloadToLocation = false;
			}
			RemoveCharacterCompanion(pchar, npchar);
			npchar.location = pchar.location;
			if (pchar.GenQuest.MarchCap == "late") AddQuestRecord("MarchCap", "2");
			if (pchar.GenQuest.MarchCap == "bad") AddQuestRecord("MarchCap", "5");
			if (pchar.GenQuest.MarchCap == "poor" || pchar.GenQuest.MarchCap == "good" || pchar.GenQuest.MarchCap == "exellent")
			{
				iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
				iTemp = iQty-sti(pchar.GenQuest.MarchCap.CapPart);
				RemoveCharacterGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods), iQty);
				AddCharacterGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods), iTemp);
				if (pchar.GenQuest.MarchCap == "poor") AddQuestRecord("MarchCap", "6");
				if (pchar.GenQuest.MarchCap == "good") AddQuestRecord("MarchCap", "7");
				if (pchar.GenQuest.MarchCap == "exellent") AddQuestRecord("MarchCap", "8");
			}
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
			CloseQuestHeader("MarchCap");
			DeleteAttribute(pchar, "GenQuest.MarchCap");
		break;
		
		case "MarchCap_AfterBattle":
			iTemp = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty))*sti(Goods[sti(pchar.GenQuest.MarchCap.Goods)].Weight);
			iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
			pchar.GenQuest.MarchCap.CapPart = iQty/sti(pchar.GenQuest.MarchCap.Parts);
			if (iTemp < 50)
			{
				dialog.text = "Sei proprio una frana, capitano! Non abbiamo visto nemmeno una moneta! E tutto per colpa tua! Sei tu la causa del nostro fallimento, maledetto cane!";
				link.l1 = "Ah sì? Guardati allo specchio! Non mi hai dato una mano in battaglia! Ho solo perso tempo con te... Fuori dalla mia nave!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "bad";
				break;
			}
			if (iTemp > 50 && iTemp < 500)
			{
				dialog.text = "Ebbene, questa razzia non è andata come speravo, il bottino è proprio misero... Pazienza, capitano, spartiamoci questi quattro soldi e diamoci l’addio.";
				link.l1 = "Se invece di contar pennuti nel cielo mi avessi dato una mano, la razzia sarebbe andata a buon fine... Prendi la tua parte - "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+" e sparisci dalla mia vista!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "poor";
				break;
			}
			if (iTemp > 500 && iTemp < 1500)
			{
				dialog.text = "Ben fatto, capitano! Come ti dicevo, è stato un gioco da ragazzi svuotare le stive di quei mercanti, ahah... Il bottino è "+FindRussianQtyString(iQty)+" pezzi. La mia parte è "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
				link.l1 = "È giusto, "+npchar.name+"Non ho obiezioni. Le scialuppe stanno venendo caricate proprio ora. Chissà, magari faremo un'altra scorribanda insieme in futuro? Hai proprio l’aria di chi potrebbe farmi buona compagnia.";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "good";
				break;
			}
			dialog.text = "Eccellente, capitano! Come ti avevo detto - svuotare le stive di quei mercantacci è stato piuttosto facile, ah-ah... Il bottino è enorme, ben più di quanto mi aspettassi. È "+FindRussianQtyString(iQty)+" dobloni. La mia parte è "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
			link.l1 = "È corretto, "+npchar.name+". Non ho obiezioni. Le scialuppe stanno già venendo caricate. Forse, in futuro, faremo un'altra scorribanda insieme? Hai proprio l’aria di essere un compagno adatto per me.";
			link.l1.go = "MarchCap_Deck_continue";
			pchar.GenQuest.MarchCap = "exellent";
		break;
		
		//если будет время - здесь создаем еще одного клона с уникальным ИД для продолжения квеста
		case "MarchCap_Deck_continue":
			dialog.text = "C'è una possibilità, capitano. Verrò a cercarti se dovessi imbattermi in qualche altra pista redditizia che da solo non potrei seguire. Mi sembri anche un compagno d’armi fidato.";
			link.l1 = "Bene! Addio, capitano. Buona fortuna!";
			link.l1.go = "MarchCap_Talk_exit";
		break;
		
		case "MarchCap_2_1":
			dialog.text = "Sapevo che potevo contare su di te! Non perdiamo neanche un minuto. Vai alla tua nave e prendi il comando, io ti seguirò. È ora di salpare!";
			link.l1 = "Dà l’ordine di salpare l’àncora, capitano.";
			link.l1.go = "MarchCap_2_2";
		break;
		
		case "MarchCap_2_2":
			DialogExit();
			NextDiag.CurrentNode = "MarchCap_repeat";
			Group_DelCharacter("MarchGroup", "MarchCap");
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			SetCharacterRemovable(npchar, false);
			Character_SetAbordageEnable(npchar, false);
			npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
			pchar.quest.MarchCap1_1.win_condition.l1 = "Timer";
			pchar.quest.MarchCap1_1.win_condition.l1.date.hour  = sti(GetTime()+rand(10));
			pchar.quest.MarchCap1_1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.function = "MarchCap2_CreateConvoy";
			pchar.GenQuest.MarchCap.WdmEnc = "true";
			pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
			pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
			ReOpenQuestHeader("MarchCap");
			AddQuestRecord("MarchCap", "10");
			AddQuestUserData("MarchCap", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Startcity+"Gen"));
			AddQuestUserData("MarchCap", "sCity2", XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Finishcity+"Acc"));
			AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
			AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
		break;
		
		case "MarchCap_3_1":
			dialog.text = "Sapevo che potevo contare su di te! Non perdiamo nemmeno un minuto. Vai alla tua nave e guidami. È tempo di salpare!";
			link.l1 = "Ordina di salpare l’ancora, capitano.";
			link.l1.go = "MarchCap_3_2";
		break;
		
		case "MarchCap_3_2":
			DialogExit();
			NextDiag.CurrentNode = "MarchCap_repeat";
			Group_DelCharacter("MarchGroup", "MarchCap");
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			SetCharacterRemovable(npchar, false);
			Character_SetAbordageEnable(npchar, false);
			npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
			pchar.quest.MarchCap1_1.win_condition.l1 = "location";
			pchar.quest.MarchCap1_1.win_condition.l1.location = pchar.GenQuest.MarchCap.Island;
			pchar.quest.MarchCap1_1.function = "MarchCap3_CreatePirate";
			SetFunctionTimerCondition("MarchCap_Attack_Over", 0, 0, sti(pchar.GenQuest.MarchCap.DaysQty), false); //таймер
			pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
			pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
			pchar.GenQuest.MarchCap.Pirate = "true";
			ReOpenQuestHeader("MarchCap");
			AddQuestRecord("MarchCap", "11");
			AddQuestUserData("MarchCap", "sShore", XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen"));
			AddQuestUserData("MarchCap", "sIsland", XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen"));
			AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
			AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
			AddQuestUserData("MarchCap", "sName1", GetName(NAMETYPE_ORIG, pchar.GenQuest.MarchCap.PirateName, NAME_NOM));
		break;
		
		case "MarchCap_DieHard":
			dialog.text = "Sei un codardo, maledetto! Te la sei svignata dal campo di battaglia!";
			link.l1 = "E che pensavi che dovessi fare? Lasciare che quel filibustiere mandasse a picco la mia nave? Neanche per sogno, meglio un codardo vivo che un fesso morto!";
			link.l1.go = "MarchCap_DieHard_1";
		break;
		
		case "MarchCap_DieHard_1":
			dialog.text = "E perché mai mi sono impicciato con te, capitano? Avrei dovuto trovare un uomo che non tremasse davanti a una sciabola d’abbordaggio!";
			link.l1 = "Ora ti chiedo di scendere dalla mia nave – devo rimetterla in sesto.";
			link.l1.go = "MarchCap_Talk_exit";
		break;
		
		case "MarchCap_AfterBattleGold":
			iTemp = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty))*sti(Goods[sti(pchar.GenQuest.MarchCap.Goods)].Weight);
			iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
			pchar.GenQuest.MarchCap.CapPart = iQty/sti(pchar.GenQuest.MarchCap.Parts);
			if (iTemp < 10)
			{
				dialog.text = "Sei proprio un buono a nulla, capitano! Non abbiamo visto nemmeno una briciola del bottino! E tutto per colpa tua! Sei tu la causa della nostra sventura, maledetto!";
				link.l1 = "Ah sì? Guardati allo specchio! Non mi hai dato man forte in battaglia! Ho solo perso tempo con te... Fuori dalla mia nave!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "bad";
				break;
			}
			if (iTemp > 10 && iTemp < 100)
			{
				dialog.text = "Ebbene, questa razzia non è andata come speravo, il bottino è proprio misero... Pazienza, capitano, dividiamoci queste briciole e diamoci l'addio.";
				link.l1 = "Se invece di contar pennuti nel cielo mi davi una mano, il colpo sarebbe andato a segno... Prendi la tua parte - "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+" e sparisci dai paraggi!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "poor";
				break;
			}
			if (iTemp > 100 && iTemp < 500)
			{
				dialog.text = "Ben fatto, capitano! Il bottino è "+FindRussianQtyString(iQty)+" dobloni. La mia parte è "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
				link.l1 = "È giusto, "+npchar.name+"Non ho obiezioni. Le scialuppe vengono caricate proprio ora. Forse ci rivedremo ancora...";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "good";
				break;
			}
			dialog.text = "Splendido, capitano! Come dissi – fu davvero una passeggiata, ah-ah... Il bottino è enorme, ben più di quanto m’aspettassi. È "+FindRussianQtyString(iQty)+" pezzi. La mia parte è "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
			link.l1 = "È giusto, "+npchar.name+"Non ho alcuna obiezione. Stiamo caricando le scialuppe proprio ora. Forse un giorno faremo un’altra razzia insieme? Mi sembri proprio un buon compare per me.";
			link.l1.go = "MarchCap_Deck_continue";
			pchar.GenQuest.MarchCap = "exellent";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "MarchCap_repeat":
			dialog.text = ""+GetAddress_Form(NPChar)+", torna alla tua nave. Non c’è tempo per chiacchiere. Salpiamo!";
			link.l1 = "Sì, sì, naturalmente, hai ragione.";
			link.l1.go = "exit";
			NextDiag.TempNode = "MarchCap_repeat";
		break;
		
		case "MarchCap_exit":
			dialog.text = "Hm... Non ci penso proprio. Sparisci! Me la cavo da solo!";
			link.l1 = "Ebbene, ebbene, che il viaggio ti sia propizio allora...";
			link.l1.go = "MarchCap_DeckExit";
		break;
		
		case "MarchCap_DeckExit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(npchar, "AlwaysFriend");
			npchar.DontDeskTalk = true;
			DeleteAttribute(pchar, "GenQuest.MarchCap");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

int SelectMarchCapGoods1()
{
	int iGoods;
	switch (hrand(5))
	{
		case 0: iGoods = GOOD_EBONY; break;
		case 1: iGoods = GOOD_MAHOGANY; break;
		case 2: iGoods = GOOD_CINNAMON; break;
		case 3: iGoods = GOOD_COFFEE; break;
		case 4: iGoods = GOOD_CHOCOLATE; break;
		case 5: iGoods = GOOD_TOBACCO; break;
	}
	return iGoods;
}

int SelectPirateShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 5;
	if(iRank >= 12 && iRank < 21) iClass = 4;
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
}

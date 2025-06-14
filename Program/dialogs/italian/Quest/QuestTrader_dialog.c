void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		bool ok = CheckFreeSitFront(npchar);
			if(hrand(11) > 8 && ok && !CheckAttribute(pchar, "GenQuest.Racing.Go") && !CheckAttribute(npchar, "quest.race") && sti(Pchar.Ship.Type) != SHIP_NOTUSED && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0)//гонки на гидропланах
			{
				dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Il mio nome è "+GetFullName(NPChar)+", sono un capitano. Vedo che anche tu sei un capitano. Ti andrebbe di unirti a me per bere qualcosa insieme? Offro io.";
				link.l1 = "Perché no? Non mi dispiacerebbe bere qualcosa in buona compagnia.";
				link.l1.go = "Race_prepare";
				link.l2 = "Perdonami, ma vado di fretta. Magari un’altra volta.";
				link.l2.go = "exit";
				npchar.quest.race = "true";
			}
			else
			{
			//конвой торгового судна
				if(!CheckAttribute(pchar, "GenQuest.Escort.Trader") && !CheckAttribute(npchar, "quest.race") && sti(Pchar.Ship.Type) != SHIP_NOTUSED && !CheckAttribute(npchar, "repeat_work") && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0 && GetCompanionQuantity(pchar) < 3)
				{
					dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Sono "+GetFullName(NPChar)+", un mercante. Immagino che tu sia un capitano. Che ne dici di guadagnare qualche migliaio di pesos?";
					link.l1 = "Son sempre avido di guadagnare qualche moneta. Di che tipo di lavoro si tratta?";
					link.l1.go = "Escort_choice";
					link.l2 = "E che razza di lavoro può offrire un mercante, eh? Proteggere il suo baraccone marcio? Ai profittatori non do una mano.";
					link.l2.go = "exit_distress";
					SaveCurrentNpcQuestDateParam(npchar, "repeat_work");
				}
				else
				{
					dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Come va, amico? Ti serve qualcosa?";
					link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+" No, non mi serve nulla. Passavo solo a salutare. Goditi la permanenza!";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "exit_distress":
			DialogExit();
			NextDiag.CurrentNode = "Trader_distress";
		break;
		
		case "Trader_distress":
			dialog.text = "Capitano, abbiamo già parlato, vero? Tu 'non aiuti gli sfruttatori', allora che diavolo vuoi ancora da me adesso?";
			link.l1 = "Sì, hai ragione. Va bene, resta pure qui a scaldare il culo e a tracannare il tuo rum. Io devo andare.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Trader_distress";
		break;
		
		case "Escort_choice"://первые развилки - выбираем между городом, бухтой и необитайкой
			pchar.GenQuest.Escort.Trader.StartCity = GetCurrentTown();//стартовый город
			pchar.GenQuest.Escort.Trader.ShipType = TraderShipType(&iTemp);//тип корабля торговца
			pchar.GenQuest.Escort.Trader.Nation = npchar.nation;//нация торговца
			switch (hrand(2))
			{
				case 0://город дружественный
					pchar.GenQuest.Escort.Trader.City = FindFriendCityToMC(false);//целевой город
					pchar.GenQuest.Escort.Trader.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Escort.Trader.StartCity), GetArealByCityName(pchar.GenQuest.Escort.Trader.City))+5;//дни
					pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.DaysQty) * 400 * ShipFactorMC() + iTemp * 700);//оплата от расстояния и классов кораблей ГГ и неписи
					pchar.GenQuest.Escort.Trader.Type1 = "true";//тип задания
					pchar.GenQuest.Escort.Trader.Chance = rand(1);
					pchar.GenQuest.Escort.Trader.Add = "to "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+"";
					dialog.text = "Vorrei chiederti di scortarmi fino a "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+"   entro "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+". Ti pagherò "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "E perché no? Navigare in compagnia è sempre più sicuro, lo capisco bene. Sono d’accordo.";
					link.l1.go = "EscortType";
					link.l2 = "Sarei lieto d’aiutarti, ma la mia rotta va altrove.";
					link.l2.go = "Escort_exit";
				break;
				case 1://бухта
					GetEscortTraderShore();//целевая бухта
					while(pchar.GenQuest.Escort.Trader.City == "Terks" || pchar.GenQuest.Escort.Trader.City == "caiman" || pchar.GenQuest.Escort.Trader.City == "dominica" 
							|| pchar.GenQuest.Escort.Trader.City == "Pearl" || pchar.GenQuest.Escort.Trader.City == "Tenotchitlan")
					{
						GetEscortTraderShore();
					} // patch-6
					pchar.GenQuest.Escort.Trader.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Escort.Trader.StartCity), pchar.GenQuest.Escort.Trader.Island)+5;//дни
					pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.DaysQty) * 400 * ShipFactorMC() + iTemp * 700);//оплата
					pchar.GenQuest.Escort.Trader.Type2 = "true";//тип задания
					pchar.GenQuest.Escort.Trader.Chance = rand(2);
					pchar.GenQuest.Escort.Trader.Add = "to "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+", not far from "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+"";
					dialog.text = "Vorrei chiederti di scortarmi fino a "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+", non lontano da "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+"   entro   "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+". Ti pagherò "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "E perché no? È sempre più sicuro navigare insieme, lo capisco bene. Sono d’accordo.";
					link.l1.go = "EscortType";
					link.l2 = "Sarei felice d’aiutarti, ma io vado per altra rotta.";
					link.l2.go = "Escort_exit";
				break;
				case 2://необитайка
					pchar.GenQuest.Escort.Trader.Island = DesIsland();//целевой остров
					pchar.GenQuest.Escort.Trader.Shore = SelectQuestShoreLocationFromSea(pchar.GenQuest.Escort.Trader.Island);//и бухта на нём
					pchar.GenQuest.Escort.Trader.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Escort.Trader.StartCity), pchar.GenQuest.Escort.Trader.Island)+5;//дни
					pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.DaysQty) * 400 * ShipFactorMC() + iTemp * 700);//оплата
					pchar.GenQuest.Escort.Trader.Type3 = "true";//тип задания
					pchar.GenQuest.Escort.Trader.Chance = rand(2);
					pchar.GenQuest.Escort.Trader.Add = "to "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+" of inhabitant island "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Island)+"";
					dialog.text = "Vorrei chiederti di scortarmi fino a "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+" che si trova a "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Island)+", in "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+". Ti pagherò "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "E perché no? Navigar insieme è sempre più sicuro, lo capisco. Sono d'accordo. Ma non ho mai sentito parlare di botteghe o empori laggiù.";
					link.l1.go = "EscortType";
					link.l2 = "Sarei lieto d’aiutarti, ma prendo il largo in tutt’altra direzione.";
					link.l2.go = "Escort_exit";
				break;
			}
		break;
		
		case "Escort_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Escort.Trader");
		break;
		
		case "Trader_wait":
			dialog.text = "Sei pronto a salpare, capitano? Attendo i tuoi ordini.";
			link.l1 = "Sì, salpiamo subito. Ci vediamo al porto.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Trader_wait";
		break;
		
		case "EscortType":
			dialog.text = "Splendido! Son felice che abbiamo stretto un accordo. Che la nostra traversata sia senza pericoli.";
			link.l1 = "Anch’io. È ora di salpare!";
			link.l1.go = "EscortType_go";
			NextDiag.CurrentNode = "Trader_wait";
		break;
		
		case "EscortType_go":
			//общие параметры
			DialogExit();
			pchar.GenQuest.Escort.Trader.id = npchar.id;
			CreateTraderShipAndAdd(npchar);//присоединяем торговца
			pchar.GenQuest.Escort.Trader.ShipMaxHP = sti(npchar.ship.HP);
			ReOpenQuestHeader("TraderEscort");
			AddQuestRecord("TraderEscort", "1");
			AddQuestUserData("TraderEscort", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty)));
			AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
			AddQuestUserData("TraderEscort", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.StartCity+"Gen"));
			AddQuestUserData("TraderEscort", "sAdd", pchar.GenQuest.Escort.Trader.Add);
			pchar.GenQuest.Escort.Trader = "begin";
			//различные параметры
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type1"))//в дружественный город
			{
				pchar.GenQuest.Escort.Trader.Location = pchar.GenQuest.Escort.Trader.City+"_tavern";
			if (sti(pchar.GenQuest.Escort.Trader.Chance) == 1) TraderHunterOnMap(true);
				else TraderHunterOnMap(false);//запуск ДУ на глобалке
			}
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type2"))//в бухту
			{
				pchar.GenQuest.Escort.Trader.Location = pchar.GenQuest.Escort.Trader.Shore;
				if (sti(pchar.GenQuest.Escort.Trader.Chance) != 2) TraderHunterOnMap(false);
				else
				{
					pchar.quest.EscortTrader_Attack.win_condition.l1 = "location";
					pchar.quest.EscortTrader_Attack.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Island;
					pchar.quest.EscortTrader_Attack.function = "EscortTraderAttackInShore";
				}
			}
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type3"))//на необитайку
			{
				pchar.GenQuest.Escort.Trader.Location = pchar.GenQuest.Escort.Trader.Shore;
				if (sti(pchar.GenQuest.Escort.Trader.Chance) == 0) TraderHunterOnMap(false);
				if (sti(pchar.GenQuest.Escort.Trader.Chance) == 1) 
				{
					if(sti(RealShips[sti(pchar.Ship.Type)].Class) >= sti(RealShips[sti(pchar.GenQuest.Escort.Trader.ShipType)].Class) && sti(RealShips[sti(pchar.Ship.Type)].BaseType) != SHIP_GALEON_H && GetCompanionQuantity(pchar) < 3)//меряемся кораблями
					{//нападет сам
						pchar.quest.EscortTrader_Attack.win_condition.l1 = "location";
						pchar.quest.EscortTrader_Attack.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Island;
						pchar.quest.EscortTrader_Attack.function = "DesIslandAttack";
					}
					else TraderHunterOnMap(true);
				}
				else
				{//будет засада + сам нападет
					pchar.quest.EscortTrader_Attack.win_condition.l1 = "location";
					pchar.quest.EscortTrader_Attack.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Island;
					pchar.quest.EscortTrader_Attack.function = "DesIslandAttack";
				}
			}
			pchar.quest.EscortTrader_Complete.win_condition.l1 = "location";
			pchar.quest.EscortTrader_Complete.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Location;
			pchar.quest.EscortTrader_Complete.function = "EscortTraderComplete";
			SetFunctionTimerCondition("EscortTrader_Over", 0, 0, sti(pchar.GenQuest.Escort.Trader.DaysQty), false);
			pchar.quest.EscortTrader_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
			pchar.quest.EscortTrader_fail.win_condition.l1.character = pchar.GenQuest.Escort.Trader.id;
			pchar.quest.EscortTrader_fail.function = "EscortTrader_failed";
		break;
		
		case "EscortTrader_complete"://сдаём квест
			sld = characterFromId(pchar.GenQuest.Escort.Trader.id);
			if (sti(sld.ship.HP) < makeint(sti(pchar.GenQuest.Escort.Trader.ShipMaxHP)/4))//если корпуса осталось меньше 1/4 - первая проверка
			{
				dialog.text = "Capitano, dimmi, perché mai ti ho assunto? Guarda la mia nave! Che aspetto ha? È sfasciata! Si regge a galla per miracolo. Non lo vedi? Non capisco: chi doveva scortare chi? Comunque sia, niente ricompensa per te, scordatelo.";
				link.l1 = "Se non fosse stato per me, adesso saresti pasto per i granchi, mercante idiota. Va bene, oggi ti dice bene, ma il mondo è piccolo e un giorno ci rivedremo in mare aperto!";
				link.l1.go = "EscortTrader_complete_1";
				break;
			}
			if (sti(sld.ship.HP) < makeint(sti(pchar.GenQuest.Escort.Trader.ShipMaxHP)/2))//если корпуса осталось меньше 1/2 - вторая проверка
			{
				pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.Money))/2;
				dialog.text = "Capitano, dimmi, perché ti ho assoldato? Guarda la mia nave! Che aspetto ha? È in rovina! Sta quasi affondando... Non lo vedi? Comunque, ti pagherò solo metà della ricompensa. Non sperar d'ottenere di più!";
				link.l1 = "Hmm... Va bene, accetto. La tua nave è davvero... un po’ malconcia...";
				link.l1.go = "EscortTrader_complete_2";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type2") && sti(pchar.GenQuest.Escort.Trader.Chance) == 1)//вместо денег - наводка
			{
				dialog.text = "Capitano, vede... Non ho denaro per pagarti per il tuo lavoro. Ma non disperare, voglio offrirti un altro tipo di ricompensa, ben più ricca di quanto ti avevo promesso!";
				link.l1 = "Hmm... In verità mi aspettavo sonanti monete in questo momento. Ma se è così, sono tutto orecchi.";
				link.l1.go = "EscortTrader_complete_4";
				break;
			}
			dialog.text = "Grazie di cuore, capitano. Navigare con voi, pur tra mille pericoli, è stato sicuro. Tenete, questa è la vostra ricompensa.";
			link.l1 = "Benvenuto... Ho solo fatto il mio dovere.";
			link.l1.go = "EscortTrader_complete_3";
		break;
		
		case "EscortTrader_complete_1":
			dialog.text = "Non provare a spaventarmi! Le tue doti in battaglia rendono le tue minacce ridicole. Addio!";
			link.l1 = "Sparisci finché sei in tempo, sanguisuga...";
			link.l1.go = "complete_exit";
			AddQuestRecord("TraderEscort", "4");
			AddComplexSeaExpToScill(20, 20, 20, 0, 20, 0, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 20);//везение
		break;
		
		case "EscortTrader_complete_2":
			dialog.text = "Sì, osservazione assai saggia... Tieni, prendi il tuo "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+" e addio.";
			link.l1 = "Ci vediamo, "+npchar.name+".";
			link.l1.go = "complete_exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Escort.Trader.Money));
			AddQuestRecord("TraderEscort", "5");
			AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
			AddComplexSeaExpToScill(50, 50, 50, 0, 50, 0, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 40);//везение
		break;
		
		case "EscortTrader_complete_3":
			dialog.text = "Hai fatto un bel lavoro! Ora devo andare. Addio, capitano!";
			link.l1 = "Buona fortuna, "+npchar.name+"!";
			link.l1.go = "complete_exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Escort.Trader.Money));
			AddQuestRecord("TraderEscort", "6");
			AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
			AddComplexSeaExpToScill(100, 100, 100, 50, 100, 100, 150);
			AddCharacterExpToSkill(pchar, "Leadership", 80);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 80);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
		break;
		
		case "EscortTrader_complete_4":
			pchar.GenQuest.Escort.Trader.Enemyname = GenerateRandomName_Generator(sti(npchar.nation), "man");
			GetEnemyTraderGoods();
			pchar.GenQuest.Escort.Trader.EnIsland = DesIsland();
			dialog.text = "C'è un mercante – "+pchar.GenQuest.Escort.Trader.Enemyname+". Possiede e comanda un fluyt. Mi è stato riferito che tra due settimane approderà sull'isola abitata "+XI_ConvertString(pchar.GenQuest.Escort.Trader.EnIsland)+", per rifornirsi d'acqua e barattare con gli indiani del posto. Gli capiteranno molte "+pchar.GenQuest.Escort.Trader.add+" a bordo. Un combattente da quattro soldi, non avrai alcun problema a prendere la sua nave\nQuindi ci guadagnerai comunque, capitano.";
			link.l1 = "L’uomo è lupo per l’uomo?";
			link.l1.go = "EscortTrader_complete_5";
		break;
		
		case "EscortTrader_complete_5":
			dialog.text = "Mi scusi?";
			link.l1 = "State 'vendendo' il vostro compare in modo così facile e schietto... Ma del vostro scrupolo poco mi cale, e vi ringrazio per la dritta. Buona fortuna, messere!";
			link.l1.go = "EscortTrader_complete_6";
		break;
		
		case "EscortTrader_complete_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.EscortTrader_fail.over = "yes";
			pchar.quest.EscortTrader_Over.over = "yes";//снять оба прерывания
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			RemoveCharacterCompanion(Pchar, npchar);
			AddQuestRecord("TraderEscort", "7");
			AddQuestUserData("TraderEscort", "sIsland", XI_ConvertString(pchar.GenQuest.Escort.Trader.EnIsland));
			AddQuestUserData("TraderEscort", "sAdd", pchar.GenQuest.Escort.Trader.add);
			pchar.quest.EscortTrader_EnTrader.win_condition.l1 = "Timer";
			pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 12);
			pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 12);
			pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 12);
			pchar.quest.EscortTrader_EnTrader.win_condition.l2 = "location";
			pchar.quest.EscortTrader_EnTrader.win_condition.l2.location = pchar.GenQuest.Escort.Trader.EnIsland;
			pchar.quest.EscortTrader_EnTrader.function = "Create_EnemyTraderFleut";
			SetFunctionTimerCondition("EscortTraderEnemy_Over", 0, 0, 16, false); // таймер
			AddComplexSeaExpToScill(100, 100, 100, 50, 100, 100, 150);
			AddCharacterExpToSkill(pchar, "Leadership", 80);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 80);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
		break;
		
		case "complete_exit":
			DialogExit();
			CloseQuestHeader("TraderEscort");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.EscortTrader_fail.over = "yes";
			pchar.quest.EscortTrader_Over.over = "yes";//снять оба прерывания
			pchar.quest.EscortTrader_Attack.over = "yes"; // patch-8
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			RemoveCharacterCompanion(Pchar, npchar);
			DeleteAttribute(pchar, "GenQuest.Escort.Trader");
		break;
		
		case "Race_prepare":
			NextDiag.TempNode = "Race_begin";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;
		
		case "exit_sit":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		
		case "Race_begin"://гонки на гидропланах
			dialog.text = "Eh, beviamoci un buon vecchio rum, capitano! Come vanno le cose, come tira il tuo commercio?";
			link.l1 = "Non sono davvero un mercante. Ma me la cavo egregiamente.";
			link.l1.go = "Race_begin_1";
		break;
		
		case "Race_begin_1":
			dialog.text = "E questo è ciò che conta di più! Visti i pericoli che ci attendono in mare aperto.";
			link.l1 = "Hai ragione, senz'altro. Soprattutto voi mercanti siete il boccone preferito dei predoni: tanti puntano al vostro carico. E quasi mai riuscite a scappare o a rispondere al fuoco. Le vostre navi sono lente, i cannoni piccoli, ché la vostra priorità resta sempre il guadagno. Soltanto navigare in convoglio, quattro o cinque navi assieme, vi salva la pelle.";
			link.l1.go = "Race_begin_2";
		break;
		
		case "Race_begin_2":
			dialog.text = "Ebbene, non tutti noi siamo così, compare. Io navigo sempre da solo, non ho bisogno di zavorra. Conosco alla perfezione il Mare dei Caraibi e, sia detto tra noi, sono davvero abile a guidare la nave, a navigare e a comandare i miei uomini. So come seminare qualsiasi filibustiere.";
			link.l1 = "Davvero? Fatico a crederci. Con la stiva piena di carico? Su una nave mercantile? Vuoi dirmi che riesci a sfuggire a una brigantina pirata, a una lugger o a una corvetta veloce?";
			link.l1.go = "Race_begin_3";
		break;
		
		case "Race_begin_3":
			dialog.text = "Pare che tu, compare, dubiti che la mia nave possa filar via veloce? Bene. Ti propongo una scommessa.";
			link.l1 = "Che razza di scommessa sarebbe?";
			link.l1.go = "Race_begin_4";
		break;
		
		case "Race_begin_4"://тут устанавливаем все параметры
			if (!CheckAttribute(pchar, "GenQuest.Racing")) pchar.GenQuest.Racing.Count = 0;
			pchar.GenQuest.Racing.Go.Nation = npchar.nation;
			pchar.GenQuest.Racing.Go.StartCity = GetCurrentTown();
			pchar.GenQuest.Racing.Go.City = FindFriendCityToMC(false);//целевой дружественный город
			pchar.GenQuest.Racing.Go.Island = GetIslandByCityName(pchar.GenQuest.Racing.Go.City);
			pchar.GenQuest.Racing.Go.DaysQty = makeint((GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Racing.Go.StartCity), GetArealByCityName(pchar.GenQuest.Racing.Go.City)))/1.3);//дни
			pchar.GenQuest.Racing.Go.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
			if (sti(pchar.GenQuest.Racing.Go.DaysQty) < 1) pchar.GenQuest.Racing.Go.DaysQty = 1; // patch-8
			dialog.text = "Ascolta. Oggi salperò per "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City)+". E ti dico che ci sarò in "+FindRussianDaysString(pchar.GenQuest.Racing.Go.DaysQty)+" Prova a seminarmi e arriva a "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City)+" prima. Il tempo comincia a scorrere ora. Vuoi rischiare? O sei troppo codardo per questa fatica?";
			link.l1 = "Per chi? Per me? Non farmi ridere. Pensi davvero di farcela in quel tempo? Roba da pazzi. Va bene, accetto la tua scommessa. Quanto sei pronto a lasciarci le penne?";
			link.l1.go = "Race_begin_5";
			link.l2 = "Son troppo occupato per mettermi a fare una corsa per via di qualche vanteria da quattro soldi.";
			link.l2.go = "Race_exit";
		break;
		
		case "Race_exit":
			dialog.text = "Hm... Hai paura di perdere? Bah, come vuoi. Ma non correre a giudicare gli altri, tra i mercanti ci sono lupi di mare che ne sanno più di te... e di gran lunga.";
			link.l1 = "Va bene, va bene, risparmiami i tuoi sermoni da filosofo. Addio...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
		break;
		
		case "Race_begin_5":
			dialog.text = "Sta a te decidere, capitano.";
			iTemp = 1;
			for (i=5; i>=1; i--)
			{
					sTemp = "l"+iTemp;
					link.(sTemp) = ""+FindRussianMoneyString(sti(10000*i))+"";
					link.(sTemp).go = "Racing_rate"+i;
					iTemp++;
			}
		break;
		
		case "Racing_rate5"://50 000
			if (hrand(9, "&RacRa") > 6)
			{
			dialog.text = "D'accordo. Accetto. Le tue monete, prego. Ecco la mia puntata.";
			link.l1 = "Lascia che prenda la mia borsa...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 50000;
			}
			else
			{
			dialog.text = "Che proposta insensata, capitano! Con quei soldi ti compri una goletta e ti sbronzi di rum per un mese intero. Fai un’offerta decente.";
			link.l1 = "Questa somma mi pare abbastanza ragionevole, e non intendo perdere tempo con te per meno di così. Non siamo straccioni da mendicare due spicci. Bene... ci siamo detti quello che dovevamo, ora basta. Se hai paura di scommettere, affari tuoi... Vantarsi non costa nulla.";
			link.l1.go = "Race_exit";
			link.l2 = "Davvero? Va bene. Fammi pensare...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate4"://40 000
			if (hrand(9, "&RacRa") > 4)
			{
			dialog.text = "Va bene. Accetto. I tuoi dobloni, per favore. Ecco la mia puntata.";
			link.l1 = "Lascia ch’io prenda la mia borsa...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 40000;
			}
			else
			{
			dialog.text = "Che offerta insensata, capitano! Con quei soldi ti compri una barca e ti sbronzi di rum per un mese intero. Fa' una proposta più ragionevole.";
			link.l1 = "Questa somma mi sembra abbastanza ragionevole, e non ho intenzione di perdere tempo con te per meno di così. Non siamo mendicanti che si accontentano di qualche peso. Va bene... abbiamo parlato, basta così. Se temi di scommettere, è affar tuo... Vantarsi non costa poco.";
			link.l1.go = "Race_exit";
			link.l2 = "Davvero? Va bene. Fammi pensare...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate3"://30 000
			if (hrand(9, "&RacRa") > 2)
			{
			dialog.text = "Bene. Accetto. I tuoi dobloni, prego. Ecco la mia puntata.";
			link.l1 = "Lascia che prenda la mia borsa...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 30000;
			}
			else
			{
			dialog.text = "Che proposta insensata, capitano! Con quella somma ci compri uno sloop e ti ubriacchi di rum per un mese intero. Fai un'offerta più ragionevole.";
			link.l1 = "Questa somma mi sembra abbastanza ragionevole, e non ho intenzione di perdere tempo con te per meno di così. Non siamo accattoni da mendicare per qualche peso. Bene... abbiamo parlato abbastanza, ora basta. Se hai paura di scommettere, è una tua scelta... Vantarsi non costa poco.";
			link.l1.go = "Race_exit";
			link.l2 = "Davvero? Va bene. Fammi pensare...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate2"://20 000
			if (hrand(9, "&RacRa") > 0)
			{
			dialog.text = "Va bene. Accetto. Le tue monete, per favore. Ecco la mia puntata.";
			link.l1 = "Lascia che prenda la mia borsa...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 20000;
			}
			else
			{
			dialog.text = "Che proposta insensata, capitano! Con quei soldi ti compri una lancia e bevi rum per un mese intero. Fai un'offerta più ragionevole.";
			link.l1 = "Questa somma mi pare abbastanza ragionevole, e non ho intenzione di perdere tempo con te per meno. Non siamo straccioni in cerca di pochi pesos. D’accordo... ci siamo detti abbastanza, ora basta. Se hai paura di scommettere, è una tua scelta... Vantarsi non costa poco.";
			link.l1.go = "Race_exit";
			link.l2 = "Davvero? Va bene. Fammi pensare...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate1"://10 000
			dialog.text = "D'accordo. Accetto. Le tue monete, per favore. Ecco la mia puntata.";
			link.l1 = "Lascia che prenda la mia borsa...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 10000;
		break;
		
		case "Racing_rate":
			dialog.text = "Allora?";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Racing.Go.Money))
			{
			link.l1 = "Ecco!";
			link.l1.go = "Racing_Go";
			}
			else
			{
			link.l1 = "Hm... sembra che non ne abbia poi così tanto.";
			link.l1.go = "Racing_rate_nomoney";
			}
		break;
		
		case "Racing_rate_nomoney":
			if (sti(pchar.GenQuest.Racing.Go.Money) == 10000 || sti(pchar.Money) < 10000)
			{
			dialog.text = "Beh, lo sai che non siamo degli straccioni che giocano per due spiccioli, o sei solo un codardo? Va bene, al diavolo, fa come vuoi. Ma non giudicare troppo in fretta gli altri, tra i mercanti ci sono vecchi lupi di mare... molto più navigati di te.";
			link.l1 = "Va bene, va bene, risparmiami la predica, filosofo. Addio...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
			}
			else
			{
			dialog.text = "Allora perché non controlli la tua borsa o punti una somma più modesta?";
			link.l1 = "D'accordo, cercherò di ricordare quanti dobloni ho...";
			link.l1.go = "Race_begin_5";
			link.l2 = "Ho cambiato idea.";
			link.l2.go = "Racing_exit";
			}
		break;
		
		case "Racing_exit":
			dialog.text = "Hai cambiato idea, eh? O forse ti sei solo spaventato? Va bene, al diavolo allora. Ma non essere tanto svelto a giudicare gli altri, tra i mercanti ci sono lupi di mare navigati... ben più di quanto tu possa credere.";
			link.l1 = "Va bene, va bene, risparmiami la predica, filosofo. Addio...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
		break;
		
		case "Racing_Go":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Racing.Go.Money));
			dialog.text = "Abbiamo una scommessa allora! Chiamiamo l’oste a far da testimone, se non ti dispiace... e lasciamogli le nostre poste. Il vincitore tornerà e prenderà tutta la somma. Imbrogliare è impossibile: le voci volano per l’arcipelago più rapide del vento, così lui saprà chi ha vinto.";
			link.l1 = "Sono d’accordo. Mi pare giusto.";
			link.l1.go = "Racing_Go_1";
		break;
		
		case "Racing_Go_1":
			dialog.text = "Ebbene, credo sia giunta l’ora di salpare e prendere il largo, il tempo stringe. Non so tu, ma io lascio subito il porto. Ah, la mia nave è una flûte e si chiama "+pchar.GenQuest.Racing.Go.ShipName+". Suppongo che la riconoscerai subito al porto, appena metterai piede a terra.";
			link.l1 = "Non festeggiare troppo presto. Ci vediamo nella taverna di "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City+"Gen")+"!";
			link.l1.go = "Racing_Go_2";
		break;
		
		case "Racing_Go_2":
			DialogExit();
			npchar.lifeday = 0;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.GenQuest.Racing.Go.StartCity + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "exit_sit", -1);
			//работает корректно только через клон :(
			sTemp = npchar.model;
			int iNation = sti(npchar.Nation);
			sld = GetCharacter(NPC_GenerateCharacter("RaceTrader", sTemp, "man", "man", sti(PChar.rank)+5, iNation, -1, true, "quest"));
			sld.name = npchar.name;
			sld.lastname = npchar.lastname;
			sld.Dialog.Filename = "Quest\QuestTrader_dialog.c";
			pchar.quest.Racing_Timer.win_condition.l1 = "Timer";
			pchar.quest.Racing_Timer.win_condition.l1.date.hour  = sti(GetTime()+rand(6));
			pchar.quest.Racing_Timer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty));
			pchar.quest.Racing_Timer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty));
			pchar.quest.Racing_Timer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty));
			pchar.quest.Racing_Timer.function = "TraderRaceInTargetCity";
			pchar.quest.Racing_Finish.win_condition.l1 = "location";
			pchar.quest.Racing_Finish.win_condition.l1.location = pchar.GenQuest.Racing.Go.City + "_town";
			pchar.quest.Racing_Finish.function = "MCRaceInTargetCity";
			SetFunctionTimerCondition("RacingTimeOver", 0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty)+10, false);
			ReOpenQuestHeader("Racing");
			AddQuestRecord("Racing", "1");
			AddQuestUserData("Racing", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Gen"));
			AddQuestUserData("Racing", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City+"Gen"));
			AddQuestUserData("Racing", "sDay", FindRussianDaysString(pchar.GenQuest.Racing.Go.DaysQty));
			AddQuestUserData("Racing", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Racing.Go.Money)));
		break;
		
		case "Racing_Finished":
			if (CheckAttribute(pchar, "GenQuest.Racing.Go.MCWin"))
			{
			dialog.text = "Ehi! Devo ammetterlo... Complimenti, capitano! Sei davvero più veloce di me. Dicono che per ogni forza c’è sempre una mano più pesante, no?";
			link.l1 = "Esattamente, signore. Ma lasci che le dica: lei è insolitamente esperto e abile per essere il capitano di una nave mercantile. Non tutti i commercianti sanno manovrare un flauto così, in così poco tempo.";
			link.l1.go = "Racing_Finished_1";
			}
			else
			{
			dialog.text = "Ebbene, sei sorpreso, capitano? Come ti dissi, conosco il mare alla perfezione e so condurre la mia nave come si deve. Vedi ora?";
			link.l1 = "Argh! Incredibile! Su una fluyt... così lontano e in così poco tempo... Complimenti, capitano!";
			link.l1.go = "Racing_Finished_2";
			}
			//bDisableFastReload = false;
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload1_back", false);
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload2_back", false);
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "gate_back", false);
		break;
		
		case "Racing_Finished_1":
			dialog.text = "Ebbene, hai vinto tu. Ora, devi fare ritorno a "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity)+" e prendi il tuo denaro dall’oste. Te lo sei proprio guadagnato!";
			link.l1 = "Già sulla mia rotta. È stato un piacere. Addio!";
			link.l1.go = "Racing_end";
			pchar.GenQuest.Racing.Count = sti(pchar.GenQuest.Racing.Count)+1;
			//запустить регату
			if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.GenQuest.Racing.Count) == 3)
			{
				pchar.questTemp.RegataGo = "true";
				pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true);//город, в котором вестовой подойдет
				if (pchar.questTemp.Regata.CureerCity == "PortRoyal") pchar.questTemp.Regata.CureerCity = "SentJons";
				pchar.quest.Regata_Cureer.win_condition.l1 = "location";
				pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity+"_town";
				pchar.quest.Regata_Cureer.function = "PrepareToRegata";
				log_testinfo(pchar.questTemp.Regata.CureerCity);
			}
			pchar.GenQuest.Racing.Go.Advantage = "true";
			npchar.lifeday = 0;
			AddCharacterExpToSkill(pchar, "Sailing", 200);//навигация
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 100);//харизма
			ChangeCharacterComplexReputation(pchar,"authority", 3);
			ChangeOfficersLoyality("good_all", 3);
		break;
		
		case "Racing_Finished_2":
			dialog.text = "Non c’è alcun segreto, solo maestria ed esperienza. E devo andare a "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Acc")+" per riscuotere la mia ricompensa.";
			link.l1 = "Te lo sei guadagnato. Addio!";
			link.l1.go = "Racing_end";
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 20);//харизма
			ChangeCharacterComplexReputation(pchar,"authority", 1);
			AddQuestRecord("Racing", "5");
			CloseQuestHeader("Racing");
		break;
		
		case "Racing_end":
			DialogExit();
			NextDiag.currentNode = "Racing_end_repeat";
			pchar.quest.Racing_fail.over = "yes";
			Group_DeleteGroup("RacingTrader");
			sld = characterFromId("RaceTraderSkiper");
			sld.lifeday = 0;
		break;
		
		case "Racing_end_repeat":
			dialog.text = "Vuoi discutere ancora di qualcos'altro?";
			link.l1 = "No, non è nulla.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Racing_end_repeat";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

float ShipFactorMC()//коэффициент от класса корабля ГГ
{
	float f;
	switch (sti(RealShips[sti(pchar.Ship.Type)].Class))
	{
		case 1: f = 1.0 break;
		case 2: f = 1.2 break;
		case 3: f = 1.5 break;
		case 4: f = 2.2 break;
		case 5: f = 3.0 break;
		case 6: f = 4.5 break;
		case 7: f = 5.5 break;
	}
	return f;
}

int TraderShipType(ref iShipCoef)//корабль торговца
{
	int iRank = sti(pchar.rank);
	int iShip;
	
	if(iRank < 5)
	{
		switch (rand(2))
		{
			case 0:
				iShip = SHIP_BARKENTINE;
				iShipCoef = 2;
			break;
			case 1:
				iShip = SHIP_LUGGER;
				iShipCoef = 3;
			break;
			case 2:
				iShip = SHIP_BARQUE;
				iShipCoef = 4;
			break;
		}
	}
	if(iRank >= 5 && iRank < 11)
	{
		switch (rand(2))
		{
			case 0:
				iShip = SHIP_BARKENTINE;
				iShipCoef = 2;
			break;
			case 1:
				iShip = SHIP_BARQUE;
				iShipCoef = 4;
			break;
			case 2:
				iShip = SHIP_SCHOONER;
				iShipCoef = 5;
			break;
		}
	}
	if(iRank >= 11 && iRank < 18)
	{
		switch (rand(3))
		{
			case 0:
				iShip = SHIP_SCHOONER;
				iShipCoef = 5;
			break;
			case 1:
				iShip = SHIP_FLEUT;
				iShipCoef = 6;
			break;
			case 2:
				iShip = SHIP_CARAVEL;
				iShipCoef = 7;
			break;
			case 3:
				iShip = SHIP_BRIGANTINE;
				iShipCoef = 8;
			break;
		}
	}
	if(iRank >= 18 && iRank < 25)
	{
		switch (rand(4))
		{
			case 0:
				iShip = SHIP_CARAVEL;
				iShipCoef = 7;
			break;
			case 1:
				iShip = SHIP_BRIGANTINE;
				iShipCoef = 8;
			break;
			case 2:
				iShip = SHIP_PINNACE;
				iShipCoef = 9;
			break;
			case 3:
				iShip = SHIP_GALEON_L;
				iShipCoef = 10;
			break;
			case 4:
				iShip = SHIP_EASTINDIAMAN;
				iShipCoef = 11;
			break;
		}
	}
	if(iRank > 25)
	{
		switch (rand(3))
		{
			case 0:
				iShip = SHIP_PINNACE;
				iShipCoef = 9;
			break;
			case 1:
				iShip = SHIP_GALEON_L;
				iShipCoef = 10;
			break;
			case 2:
				iShip = SHIP_EASTINDIAMAN;
				iShipCoef = 11;
			break;
			case 3:
				iShip = SHIP_NAVIO;
				iShipCoef = 12;
			break;
		}
	}
	return iShip;
}

void GetEnemyTraderGoods()//выберем товар
{
switch (rand(7))
	{
		case 0:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_EBONY;
			pchar.GenQuest.Escort.Trader.add = "ebony";
			break;
		case 1:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_MAHOGANY;
			pchar.GenQuest.Escort.Trader.add = "redwood";
			break;
		case 2:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_TOBACCO;
			pchar.GenQuest.Escort.Trader.add = "tobacco";
			break;
		case 3:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_COFFEE;
			pchar.GenQuest.Escort.Trader.add = "coffee";
			break;
		case 4:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_CINNAMON;
			pchar.GenQuest.Escort.Trader.add = "cinnamon";
			break;
		case 5:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_FOOD;
			pchar.GenQuest.Escort.Trader.add = "provision";
			break;
		case 6:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_WEAPON;
			pchar.GenQuest.Escort.Trader.add = "weapon";
			break;
		case 7:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_CHOCOLATE;
			pchar.GenQuest.Escort.Trader.add = "cacao";
			break;
	}
}

bool CheckFreeSitFront(ref _npchar)
{
 	ref rCharacter;
	int n;

	if (!CheckAttribute(_npchar, "Default.ToLocator")) return false;
	
	for (n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, "location") && rCharacter.location == _npchar.location)
		{
            if (rCharacter.location.locator == _npchar.Default.ToLocator)
                return  false;
		}
    }
    return  true;
}

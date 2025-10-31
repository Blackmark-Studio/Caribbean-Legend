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
				dialog.text = TimeGreeting() + ", "+GetAddress_Form(NPChar) + "! A nevem "+ GetFullName(NPChar) + ", kapitány vagyok. Látom, hogy te is kapitány vagy. Szeretnél csatlakozni hozzám és meginni egy italt együtt? Én fizetek.";
				link.l1 = "Miért ne? Nem bánnám, ha meginnék néhány italt egy jó társaságban.";
				link.l1.go = "Race_prepare";
				link.l2 = "Sajnálom, de sietek. Majd legközelebb.";
				link.l2.go = "exit";
				npchar.quest.race = "true";
			}
			else
			{
			//конвой торгового судна
				if(!CheckAttribute(pchar, "GenQuest.Escort.Trader") && !CheckAttribute(npchar, "quest.race") && sti(Pchar.Ship.Type) != SHIP_NOTUSED && !CheckAttribute(npchar, "repeat_work") && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0 && GetCompanionQuantity(pchar) < 3)
				{
					dialog.text = TimeGreeting() + ", "+GetAddress_Form(NPChar) + "! Én vagyok "+ GetFullName(NPChar) + ", egy kereskedô. Gondolom, ön kapitány. Mi lenne, ha keresnék néhány ezer pesót?";
					link.l1 = "Mindig szívesen keresek egy kis pénzt. Milyen munkáról beszélünk?";
					link.l1.go = "Escort_choice";
					link.l2 = "És milyen munkát tudna ajánlani a kereskedô, mi? Hogy megvédje a rothadó hajóját? Én nem segítek a haszonlesôknek.";
					link.l2.go = "exit_distress";
					SaveCurrentNpcQuestDateParam(npchar, "repeat_work");
				}
				else
				{
					dialog.text = TimeGreeting() + ", "+GetAddress_Form(NPChar) + "! Hogy vagy? Szükséged van valamire?";
					link.l1 = TimeGreeting() + ", " + GetAddress_FormToNPC(NPChar) + ". Nem, nem tudom. Csak köszönni akartam. Jó szórakozást!";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "exit_distress":
			DialogExit();
			NextDiag.CurrentNode = "Trader_distress";
		break;
		
		case "Trader_distress":
			dialog.text = "Kapitány, már beszéltünk, ugye? Ön 'nem segít a haszonlesôknek', , akkor most mit akar tôlem?";
			link.l1 = "Igen, és igaza van. Rendben, csak üljön itt a kövér seggén és igya a rumját. Nekem mennem kell.";
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
					dialog.text = "Szeretném megkérni, hogy kísérjen el a "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+" belül "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+". Fizetek neked "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "És miért ne? Mindig biztonságosabb együtt hajózni, megértem. Egyetértek.";
					link.l1.go = "EscortType";
					link.l2 = "Szívesen segítenék, de most más irányba tartok.";
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
					dialog.text = "Szeretném megkérni, hogy kísérjen el a "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+", nem messze a "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+" belül "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+". Fizetek neked "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "És miért ne? Mindig biztonságosabb együtt hajózni, megértem. Egyetértek.";
					link.l1.go = "EscortType";
					link.l2 = "Szívesen segítenék, de most más irányba tartok.";
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
					dialog.text = "Szeretném megkérni, hogy kísérjen el a "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+" , amely a "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Island)+", a "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+". Fizetek neked "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "És miért ne? Mindig biztonságosabb együtt hajózni, ezt megértem. Egyetértek. De még sosem hallottam ott boltokról és kereskedelmi állomásokról.";
					link.l1.go = "EscortType";
					link.l2 = "Szívesen segítenék, de más irányba indulok.";
					link.l2.go = "Escort_exit";
				break;
			}
		break;
		
		case "Escort_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Escort.Trader");
		break;
		
		case "Trader_wait":
			dialog.text = "Készen áll a hajózásra, kapitány? Várom a parancsát.";
			link.l1 = "Igen, most indulunk. Találkozunk a kikötôben.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Trader_wait";
		break;
		
		case "EscortType":
			dialog.text = "Pompás! Örülök, hogy megegyeztünk. Remélem, hogy az utunk biztonságos lesz.";
			link.l1 = "Én is. Itt az idô, hogy kihajózzunk!";
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
				dialog.text = "Kapitány, mondja, miért béreltem fel magát? Nézd a hajómat! Hogy néz ki? Tönkrement! Alig tartja magát a víz felett. Hát nem látja? Nem értem - ki kísért kit? Különben is, nem kapsz jutalmat, felejtsd el.";
				link.l1 = "Ha én nem lennék, most rákokat etetnél, te ostoba kereskedô. Jó, ez a te szerencsenapod, de a világ kicsi, és egyszer majd a nyílt tengeren találkozunk!";
				link.l1.go = "EscortTrader_complete_1";
				break;
			}
			if (sti(sld.ship.HP) < makeint(sti(pchar.GenQuest.Escort.Trader.ShipMaxHP)/2))//если корпуса осталось меньше 1/2 - вторая проверка
			{
				pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.Money))/2;
				dialog.text = "Kapitány, mondd meg, miért béreltelek fel? Nézd meg a hajómat! Hogy néz ki? Tönkrement! Alig tartja magát a víz felett... Hát nem látod? Mindegy, a jutalmadnak csak a felét fizetem ki. Ne számíts arra, hogy többet kapsz!";
				link.l1 = "Hmm... Rendben, egyetértek. A hajód tényleg... egy kicsit sérült...";
				link.l1.go = "EscortTrader_complete_2";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type2") && sti(pchar.GenQuest.Escort.Trader.Chance) == 1)//вместо денег - наводка
			{
				dialog.text = "Kapitány, tudja... Nincs pénzem, hogy kifizessem a munkádat. De ne aggódjon, kérem, szeretnék egy másik fizetséget ajánlani, ami sokkal nagyobb, mint amit korábban ígértem!";
				link.l1 = "Hmm... Igazából arra számítottam, hogy most azonnal érméket kapok. De csupa fül vagyok, ha ez a helyzet.";
				link.l1.go = "EscortTrader_complete_4";
				break;
			}
			dialog.text = "Köszönöm szépen, kapitány. Biztonságos volt veled hajózni minden veszély ellenére. Tessék, vedd el a jutalmad.";
			link.l1 = "Szívesen... Csak a munkámat végeztem.";
			link.l1.go = "EscortTrader_complete_3";
		break;
		
		case "EscortTrader_complete_1":
			dialog.text = "Ne próbálj megijeszteni! A harci képességeid miatt a fenyegetéseid szánalmasak. Viszontlátásra!";
			link.l1 = "Tûnj el, amíg lehet, te haszonlesô...";
			link.l1.go = "complete_exit";
			AddQuestRecord("TraderEscort", "4");
			AddComplexSeaExpToScill(20, 20, 20, 0, 20, 0, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 20);//везение
		break;
		
		case "EscortTrader_complete_2":
			dialog.text = "Igen, nagyon bölcs megfigyelés... Tessék, fogd a "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+" és viszlát.";
			link.l1 = "Viszlát, " + npchar.name + ".";
			link.l1.go = "complete_exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Escort.Trader.Money));
			AddQuestRecord("TraderEscort", "5");
			AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
			AddComplexSeaExpToScill(50, 50, 50, 0, 50, 0, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 40);//везение
		break;
		
		case "EscortTrader_complete_3":
			dialog.text = "Remekül csináltad! Nos, most mennem kell. Viszlát, kapitány!";
			link.l1 = "Sok sikert, " + npchar.name + "!";
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
			dialog.text = "Van egy kereskedô - "+ pchar.GenQuest.Escort.Trader.Enemyname +". Ô birtokolja és parancsolja a fuvolát. Úgy értesültem, hogy két hét múlva érkezik a lakott szigetre "+ XI_ConvertString(pchar.GenQuest.Escort.Trader.EnIsland) +", hogy helyreállítsa a vízkészleteit és kereskedjen a helyi indiánokkal. Sok "+pchar.GenQuest.Escort.Trader.add+" lesz a fedélzeten. Szánalmas harcos, nem fog gondot okozni, ha elfoglalja a hajóját\nSzóval mindenképpen hasznát veszi, kapitány.";
			link.l1 = "Homo homini lupus est?";
			link.l1.go = "EscortTrader_complete_5";
		break;
		
		case "EscortTrader_complete_5":
			dialog.text = "Elnézést?";
			link.l1 = "Te 'adod' kollégádat ilyen könnyedén és ôszintén... De a lelkiismereteddel keveset törôdöm, és köszönöm ezt az információt. Sok szerencsét, uram!";
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
			dialog.text = "Eh, igyunk egy kis jó öreg rumot, kapitány! Hogy vagy, hogy megy a kereskedés?";
			link.l1 = "Nem igazán vagyok kereskedô. De jól megvagyok.";
			link.l1.go = "Race_begin_1";
		break;
		
		case "Race_begin_1":
			dialog.text = "És ez a legfontosabb! Tekintettel a nyílt tenger veszélyeire.";
			link.l1 = "Igen, igazad van. Különösen nektek, kereskedôknek, sok a vadász a rakományotokra. És ritkán vagytok képesek sem menekülni, sem visszavágni. A hajóitok lassúak és az ágyúitok kicsik, mivel a nyereséget helyezitek elôtérbe. Négy vagy öt hajóval együtt, konvojban hajózva ez az, ami megment titeket.";
			link.l1.go = "Race_begin_2";
		break;
		
		case "Race_begin_2":
			dialog.text = "Nos, nem mindannyian vagyunk ilyenek, barátom. Én mindig egyedül hajózom, nincs szükségem ballasztra. Tökéletesen ismerem a karibi tengert, és mondhatom, nagyon jól navigálok, vitorlázom és irányítom az embereimet. Képes vagyok bármelyik kalózt megelôzni.";
			link.l1 = "Tényleg? Ezt alig tudom elhinni. Teli rakománnyal? A kereskedelmi hajón? Tehát úgy érted, hogy el tudsz menekülni egy kalóz brigantin, egy lugger vagy egy gyors korvett elôl?";
			link.l1.go = "Race_begin_3";
		break;
		
		case "Race_begin_3":
			dialog.text = "Úgy tûnik, pajtás, te kételkedsz abban, hogy a hajóm képes gyorsan hajózni? Hát jó. Felajánlok egy fogadást.";
			link.l1 = "Miféle fogadást?";
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
			dialog.text = "Hallgassa meg. Ma elhajózom a "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City)+". És azt mondom, hogy ott leszek "+FindRussianDaysString(pchar.GenQuest.Racing.Go.DaysQty)+". Próbáljatok meg lehagyni engem és hamarabb odaérni "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City)+" . Az idô már kezd ketyegni. Akarsz kockáztatni? Vagy ez túl kemény neked?";
			link.l1 = "Kinek? Nekem? Ne légy ilyen vicces. Meg fogod csinálni ennyi idô alatt? Nevetséges. Rendben, elfogadom a fogadást. Mennyit vagy hajlandó veszíteni?";
			link.l1.go = "Race_begin_5";
			link.l2 = "Túlságosan elfoglalt vagyok ahhoz, hogy valami ostoba dicsekvés miatt versenyezzek.";
			link.l2.go = "Race_exit";
		break;
		
		case "Race_exit":
			dialog.text = "Hm... Félsz veszíteni? Mindegy. De ne ítélkezz olyan gyorsan mások felett, a kereskedôk között sok tapasztalt tengerész van... sokkal tapasztaltabb, mint te.";
			link.l1 = "Rendben, rendben, ne prédikálj nekem, filozófus. Viszlát...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
		break;
		
		case "Race_begin_5":
			dialog.text = "A te döntésed, kapitány.";
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
			dialog.text = "Rendben. Egyetértek. Az érméit kérem. Itt a tétem.";
			link.l1 = "Csak hadd hozzam a pénztárcámat...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 50000;
			}
			else
			{
			dialog.text = "Micsoda értelmetlen ajánlat, kapitány? Ennyi pénzért vehetsz egy szkúnert, és rumot ihatsz egy egész hónapig. Ajánlj egy ésszerû összeget.";
			link.l1 = "Nekem ez az összeg elég ésszerûnek tûnik, és nem fogom az idômet vesztegetni önre ennél kevesebbért. Nem vagyunk koldusok, hogy néhány pezóért fogadjunk. Jól van... eleget beszéltünk, most már elég. Ha félsz fogadni, a te döntésed... A hencegés nem olcsó.";
			link.l1.go = "Race_exit";
			link.l2 = "Tényleg? Rendben. Hadd gondolkozzak...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate4"://40 000
			if (hrand(9, "&RacRa") > 4)
			{
			dialog.text = "Rendben. Egyetértek. Az érméit kérem. Itt a tétem.";
			link.l1 = "Csak hadd hozzam a pénztárcámat...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 40000;
			}
			else
			{
			dialog.text = "Micsoda értelmetlen ajánlat, kapitány? Ennyi pénzért vehetsz egy bárkát, és rumot ihatsz egy egész hónapig. Ajánlj egy ésszerû összeget.";
			link.l1 = "Nekem ez az összeg elég ésszerûnek tûnik, és nem fogom az idômet vesztegetni önre ennél kevesebbért. Nem vagyunk koldusok, hogy néhány pezóért fogadjunk. Jól van... eleget beszéltünk, most már elég. Ha félsz fogadni, a te döntésed... A hencegés nem olcsó.";
			link.l1.go = "Race_exit";
			link.l2 = "Tényleg? Rendben. Hadd gondolkozzak...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate3"://30 000
			if (hrand(9, "&RacRa") > 2)
			{
			dialog.text = "Rendben. Egyetértek. Az érméit kérem. Itt a tétem.";
			link.l1 = "Csak hadd hozzam a pénztárcámat...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 30000;
			}
			else
			{
			dialog.text = "Milyen értelmetlen ajánlat, kapitány? Ennyi pénzért vehetsz egy sloopot, és egy hónapig rumot ihatsz. Ajánljon egy ésszerû összeget.";
			link.l1 = "Nekem ez az összeg elég ésszerûnek tûnik, és nem fogom az idômet vesztegetni önre ennél kevesebbért. Nem vagyunk koldusok, hogy néhány pezóért fogadjunk. Jól van... eleget beszéltünk, most már elég. Ha félsz fogadni, a te döntésed... A hencegés nem olcsó.";
			link.l1.go = "Race_exit";
			link.l2 = "Tényleg? Rendben. Hadd gondolkozzak...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate2"://20 000
			if (hrand(9, "&RacRa") > 0)
			{
			dialog.text = "Rendben. Egyetértek. Az érméit kérem. Itt a tétem.";
			link.l1 = "Csak hadd hozzam a pénztárcámat...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 20000;
			}
			else
			{
			dialog.text = "Milyen értelmetlen ajánlat, kapitány? Ennyi pénzért vehet egy luggert, és egy egész hónapig rumot ihat. Ajánljon egy ésszerû összeget.";
			link.l1 = "Nekem ez az összeg elég ésszerûnek tûnik, és nem fogom az idômet vesztegetni önre ennél kevesebbért. Nem vagyunk koldusok, hogy néhány pezóért fogadjunk. Jól van... eleget beszéltünk, most már elég. Ha félsz fogadni, a te döntésed... A hencegés nem olcsó.";
			link.l1.go = "Race_exit";
			link.l2 = "Tényleg? Rendben. Hadd gondolkozzak...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate1"://10 000
			dialog.text = "Rendben. Egyetértek. Az érméit kérem. Itt a tétem.";
			link.l1 = "Csak hadd hozzam a pénztárcámat...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 10000;
		break;
		
		case "Racing_rate":
			dialog.text = "Szóval?";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Racing.Go.Money))
			{
			link.l1 = "Tessék!";
			link.l1.go = "Racing_Go";
			}
			else
			{
			link.l1 = "Hm... úgy néz ki, nekem nincs olyan sok mindenem.";
			link.l1.go = "Racing_rate_nomoney";
			}
		break;
		
		case "Racing_rate_nomoney":
			if (sti(pchar.GenQuest.Racing.Go.Money) == 10000 || sti(pchar.Money) < 10000)
			{
			dialog.text = "Hát, tudod, hogy nem vagyunk koldusok, hogy néhány pezóért fogadjunk, vagy csak megijedtél? Rendben, a pokolba veled. De ne ítélkezz olyan gyorsan mások felett, a kereskedôk között sok tapasztalt tengerész van... sokkal tapasztaltabb, mint te.";
			link.l1 = "Rendben, rendben, ne prédikálj nekem, filozófus. Viszlát...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
			}
			else
			{
			dialog.text = "Szóval miért nem nézed meg a pénztárcádat, vagy miért nem teszel kisebb tétet?";
			link.l1 = "Rendben, megpróbálok emlékezni, mennyi pénzem van...";
			link.l1.go = "Race_begin_5";
			link.l2 = "Meggondoltam magam.";
			link.l2.go = "Racing_exit";
			}
		break;
		
		case "Racing_exit":
			dialog.text = "Meggondoltad magad, mi? Nem félsz? Rendben, a pokolba veled. De ne ítélkezz olyan gyorsan mások felett, a kereskedôk között sok tapasztalt tengerész van... sokkal tapasztaltabb, mint te.";
			link.l1 = "Rendben, rendben, ne prédikálj nekem, filozófus. Viszlát...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
		break;
		
		case "Racing_Go":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Racing.Go.Money));
			dialog.text = "Akkor megvan a fogadás! Hívjunk egy csapost, hogy legyen a tanúja, ha nem bánod... és adjuk oda neki a tétünket. A gyôztes visszatér és elveszi az egész összeget. Csalni lehetetlen, hiszen a pletykák nagyon gyorsan terjednek a szigetvilágban, így tudni fogja, hogy ki a gyôztes.";
			link.l1 = "Egyetértek. Ez így helyesnek tûnik.";
			link.l1.go = "Racing_Go_1";
		break;
		
		case "Racing_Go_1":
			dialog.text = "Nos, azt hiszem, itt az ideje, hogy felszálljunk a hajóinkra és elhajózzunk, az idô ketyeg. Nem tudom, ti hogy vagytok vele, de én most azonnal útnak indulok. Ó, és a hajóm egy fuvola, és a neve "+pchar.GenQuest.Racing.Go.ShipName+". Gondolom, könnyen felismeritek majd a kikötôben, ha megérkeztek.";
			link.l1 = "Ne ugrálj örömödben ilyen hamar. Találkozunk a "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City+"Gen")+"kocsmában !";
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
			dialog.text = "Heh! Igazából meglepôdtem... Gratulálok, kapitány! Tényleg gyorsabb vagy nálam. Azt mondják, hogy minden erôre mindig van erôsebb erô, igazam van?";
			link.l1 = "Pontosan, uram. De szeretném elmondani, hogy meglepôen tapasztalt és ügyes vagy egy kereskedelmi hajó kapitányához képest. Nem minden kereskedô képes ilyen rövid idô alatt így vitorlázni egy furulyán.";
			link.l1.go = "Racing_Finished_1";
			}
			else
			{
			dialog.text = "Hát nem lepôdik meg, kapitány úr? Mint mondtam, tökéletesen ismerem a tengert, és elég jól vezetem a hajómat. Látod?";
			link.l1 = "Argh! Hihetetlen! Egy fuvolán... ilyen messzire és ilyen rövid idô alatt... Gratulálok, kapitány!";
			link.l1.go = "Racing_Finished_2";
			}
			//bDisableFastReload = false;
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload1_back", false);
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload2_back", false);
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "gate_back", false);
		break;
		
		case "Racing_Finished_1":
			dialog.text = "Nos, te vagy a gyôztes. Most vissza kell térned a "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity)+" , és el kell venned a pénzt a csapostól. Biztosan megérdemelted!";
			link.l1 = "Már úton vagyok. Öröm volt. Viszontlátásra!";
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
			dialog.text = "Ebben nincs semmi titok, csak a szakértelem és a tapasztalat. És el kell mennem a "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Acc")+" címre, hogy átvegyem a nyereményemet.";
			link.l1 = "Megérdemelted. Viszontlátásra!";
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
			dialog.text = "Van még valami, amirôl szeretnél beszélni?";
			link.l1 = "Nem, ez semmiség.";
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
	if(iRank >= 25)
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

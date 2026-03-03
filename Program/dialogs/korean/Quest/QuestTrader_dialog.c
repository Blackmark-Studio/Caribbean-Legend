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
				dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! 내 이름은 "+GetFullName(NPChar)+", 나는 선장이오. 보아하니 그쪽도 선장인 것 같군. 한잔 같이 할 생각 있나? 내가 살 테니.";
				link.l1 = "왜 안 되겠어? 좋은 사람들이랑 한잔하는 거라면 나도 마다하지 않지.";
				link.l1.go = "Race_prepare";
				link.l2 = "미안하지만, 나는 급해서. 다음에 보자.";
				link.l2.go = "exit";
				npchar.quest.race = "true";
			}
			else
			{
			//конвой торгового судна
				if(!CheckAttribute(pchar, "GenQuest.Escort.Trader") && !CheckAttribute(npchar, "quest.race") && sti(Pchar.Ship.Type) != SHIP_NOTUSED && !CheckAttribute(npchar, "repeat_work") && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0 && GetCompanionQuantity(pchar) < 3)
				{
					dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! 나는 "+GetFullName(NPChar)+", 상인이지. 자네는 선장인 것 같군. 몇 천 페소 벌어볼 생각 없나?";
					link.l1 = "나는 언제나 돈 벌 기회라면 반갑지. 무슨 일인데?";
					link.l1.go = "Escort_choice";
					link.l2 = "상인이 무슨 일을 줄 수 있는데, 응? 썩은 배나 지키라고? 나는 돈만 밝히는 놈들 안 도와.";
					link.l2.go = "exit_distress";
					SaveCurrentNpcQuestDateParam(npchar, "repeat_work");
				}
				else
				{
					dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! 어떻게 지내? 뭐 필요한 거라도 있어?";
					link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+". 아니, 없어. 그냥 인사나 하려고 왔어. 머무는 동안 잘 지내!";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "exit_distress":
			DialogExit();
			NextDiag.CurrentNode = "Trader_distress";
		break;
		
		case "Trader_distress":
			dialog.text = "선장, 우리 이미 얘기했잖아? 너는 '장사꾼들 안 도와준다'며, 그럼 이제 나한테 뭘 원하는 거야?";
			link.l1 = "그래, 네 말이 맞아. 좋아, 여기 네 뚱뚱한 엉덩이 붙이고 럼이나 마시고 있어라. 나는 가봐야겠다.";
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
					dialog.text = "나를 데려다 주었으면 해 "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+" 내부에 "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+". 내가 돈을 주겠다 "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "왜 안 되겠어? 같이 항해하는 게 항상 더 안전하지, 그건 나도 이해해. 나도 동의해.";
					link.l1.go = "EscortType";
					link.l2 = "도와주고 싶지만, 나는 다른 방향으로 가는 중이야.";
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
					dialog.text = "나를 까지 호위해 줬으면 해 "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+", 근처에 "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+" 내부에 "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+". 내가 돈을 주겠다 "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "왜 안 되겠어? 같이 항해하는 게 항상 더 안전하지, 그건 나도 잘 알아. 나도 동의해.";
					link.l1.go = "EscortType";
					link.l2 = "도와주고 싶지만, 나는 다른 방향으로 가는 중이야.";
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
					dialog.text = "나를 까지 호위해 주었으면 해 "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+" 있는 곳이 "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Island)+", 에 "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+". 내가 돈을 주겠다 "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "왜 안 되겠어? 같이 항해하는 게 항상 더 안전하지, 그건 이해해. 나도 동의해. 하지만 거기에 상점이나 교역소가 있다는 얘기는 들어본 적 없어.";
					link.l1.go = "EscortType";
					link.l2 = "도와주고 싶지만 나는 다른 방향으로 가는 중이야.";
					link.l2.go = "Escort_exit";
				break;
			}
		break;
		
		case "Escort_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Escort.Trader");
		break;
		
		case "Trader_wait":
			dialog.text = "항해할 준비가 되었습니까, 선장님? 명령을 기다리고 있습니다.";
			link.l1 = "그래, 이제 출항할 거야. 항구에서 보자.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Trader_wait";
		break;
		
		case "EscortType":
			dialog.text = "훌륭하군! 우리가 거래를 성사시켜서 기쁘네. 우리의 항해가 무사하길 바라네.";
			link.l1 = "나도 그래. 이제 출항할 시간이야!";
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
				dialog.text = "선장, 말해 봐라, 내가 왜 너를 고용했지? 내 배 좀 봐! 이게 뭐처럼 보이냐? 완전히 망가졌잖아! 겨우 물 위에 떠 있는 수준이야. 그걸 못 보겠어? 도무지 이해가 안 돼 – 누가 누구를 호위한 거지? 어쨌든, 보상은 없다, 잊어버려.";
				link.l1 = "내가 아니었으면 넌 지금쯤 게밥이 됐을 거다, 이 멍청한 상인 놈아. 좋아, 오늘은 운이 좋았군. 하지만 세상은 좁고, 언젠가 바다에서 다시 만나게 될 거다!";
				link.l1.go = "EscortTrader_complete_1";
				break;
			}
			if (sti(sld.ship.HP) < makeint(sti(pchar.GenQuest.Escort.Trader.ShipMaxHP)/2))//если корпуса осталось меньше 1/2 - вторая проверка
			{
				pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.Money))/2;
				dialog.text = "선장, 내가 왜 자네를 고용했는지 말해 보게! 내 배 좀 보라고! 이게 뭐처럼 보이나? 완전히 망가졌잖아! 겨우 물 위에 떠 있는 수준이야... 그걸 모르겠나? 아무튼, 자네 보수의 절반만 줄 거야. 더 받을 생각은 하지 마!";
				link.l1 = "흠... 좋아, 동의하지. 네 배가 정말... 좀 망가졌군...";
				link.l1.go = "EscortTrader_complete_2";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type2") && sti(pchar.GenQuest.Escort.Trader.Chance) == 1)//вместо денег - наводка
			{
				dialog.text = "선장님, 저기... 드릴 돈이 없어서 일값을 못 드리겠소. 하지만 걱정 마십시오, 전에 약속했던 것보다 훨씬 더 큰 보상을 드리고 싶소!";
				link.l1 = "흠... 사실 지금쯤이면 동전을 받을 줄 알았는데. 하지만 그렇다면 들어나 보지.";
				link.l1.go = "EscortTrader_complete_4";
				break;
			}
			dialog.text = "정말 감사합니다, 선장님. 온갖 위험 속에서도 선장님과 함께라서 안전하게 항해할 수 있었습니다. 자, 보상금을 받으십시오.";
			link.l1 = "별말씀을요... 저는 그냥 제 할 일을 했을 뿐입니다.";
			link.l1.go = "EscortTrader_complete_3";
		break;
		
		case "EscortTrader_complete_1":
			dialog.text = "나 겁주려고 하지 마! 네 싸움 실력으론 협박도 우습군. 잘 가라!";
			link.l1 = "아직 기회 있을 때 꺼져라, 졸부 놈아...";
			link.l1.go = "complete_exit";
			AddQuestRecord("TraderEscort", "4");
			AddComplexSeaExpToScill(20, 20, 20, 0, 20, 0, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 20);//везение
		break;
		
		case "EscortTrader_complete_2":
			dialog.text = "그래, 아주 현명한 지적이군... 자, 네 거 가져가라 "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+" 그리고 안녕히 가십시오.";
			link.l1 = "또 보자, "+npchar.name+".";
			link.l1.go = "complete_exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Escort.Trader.Money));
			AddQuestRecord("TraderEscort", "5");
			AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
			AddComplexSeaExpToScill(50, 50, 50, 0, 50, 0, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 40);//везение
		break;
		
		case "EscortTrader_complete_3":
			dialog.text = "잘했어! 자, 이제 난 가봐야겠군. 안녕, 선장!";
			link.l1 = "행운을 빌어, "+npchar.name+"!";
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
			dialog.text = "상인이 한 명 있는데 - "+pchar.GenQuest.Escort.Trader.Enemyname+". 그는 플루이트선을 소유하고 지휘하지. 2주 후에 사람이 사는 섬에 도착할 거라고 들었어 "+XI_ConvertString(pchar.GenQuest.Escort.Trader.EnIsland)+", 식수를 보충하고 현지 인디언들과 교역하기 위해서지. 그는 많은 "+pchar.GenQuest.Escort.Trader.add+" 배에 올라타라. 한심한 싸움꾼이라 그의 배를 빼앗는 데 아무 문제 없을 거다\n어쨌든 이득을 보게 될 거야, 선장.";
			link.l1 = "호모 호미니 루푸스 에스트?";
			link.l1.go = "EscortTrader_complete_5";
		break;
		
		case "EscortTrader_complete_5":
			dialog.text = "뭐라고?";
			link.l1 = "동료를 이렇게 쉽게, 그리고 솔직하게 넘기다니... 하지만 네 양심 따위엔 관심 없어. 이 정보에는 고맙군. 행운을 빌지, 나리!";
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
			dialog.text = "이봐, 선장! 옛날 럼주나 한잔하자고! 잘 지내? 장사는 어때?";
			link.l1 = "나는 사실 상인이 아니야. 그래도 잘 지내고 있지.";
			link.l1.go = "Race_begin_1";
		break;
		
		case "Race_begin_1":
			dialog.text = "그게 가장 중요한 거야! 망망대해의 위험을 생각하면 말이지.";
			link.l1 = "그래, 네 말이 맞아. 특히 너희 상인들한테는 화물을 노리는 사냥꾼들이 아주 많지. 그리고 너희는 도망치거나 맞서 싸우는 것도 거의 못 하지. 배는 느리고 대포도 작으니까, 이익만 먼저 생각하잖아. 네댓 척씩 무리를 지어 항해하는 것, 그게 너희를 살리는 거야.";
			link.l1.go = "Race_begin_2";
		break;
		
		case "Race_begin_2":
			dialog.text = "글쎄, 우리 모두가 그런 건 아니야, 친구. 나는 항상 혼자 항해하지, 쓸데없는 짐 따윈 필요 없어. 나는 카리브 해를 완벽하게 알고 있고, 감히 말하건대 항해와 조타, 부하들 지휘에 정말 능숙하지. 어떤 해적보다도 더 빠르게 달릴 수 있어.";
			link.l1 = "정말이야? 도저히 믿기 힘든데. 화물이 가득 실린 상태로? 그것도 상선에서? 설마 해적 브리건틴이나 루거, 아니면 빠른 코르벳에서 도망칠 수 있다는 거야?";
			link.l1.go = "Race_begin_3";
		break;
		
		case "Race_begin_3":
			dialog.text = "보아하니, 이봐 친구, 내 배가 빠르게 달릴 수 있을지 의심하는 것 같은데? 좋아. 내기하자.";
			link.l1 = "무슨 내기인데?";
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
			dialog.text = "들어봐. 오늘 나는 출항해서 "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City)+". 그리고 나는 내가 거기 있을 거라고 말하지 "+FindRussianDaysString(pchar.GenQuest.Racing.Go.DaysQty)+". 나보다 먼저 도착하려고 해 봐, 그리고 "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City)+" 더 빨리. 이제부터 시간이 흐르기 시작한다. 해볼래? 아니면 너무 힘든가?";
			link.l1 = "누구를 위해서? 나를 위해서? 웃기지 마라. 네가 정말 그 시간 안에 해낼 거라고? 말도 안 돼. 좋아, 내기 받아들이지. 얼마나 잃을 각오가 되어 있나?";
			link.l1.go = "Race_begin_5";
			link.l2 = "나는 쓸데없는 허세 때문에 경주를 시작할 만큼 한가하지 않아.";
			link.l2.go = "Race_exit";
		break;
		
		case "Race_exit":
			dialog.text = "음... 지는 게 두려운 거냐? 뭐, 상관없지. 하지만 남을 함부로 판단하지 마라, 상인들 중에도 노련한 선원들이 많거든... 너보다 훨씬 더 경험 많은 이들이지.";
			link.l1 = "알았어, 알았어, 설교는 그만해, 철학자 녀석. 잘 가라...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
		break;
		
		case "Race_begin_5":
			dialog.text = "선장님, 선택은 당신 몫입니다.";
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
			dialog.text = "좋아. 동의하지. 돈을 내놔. 이게 내 내기야.";
			link.l1 = "잠깐만, 내 지갑 좀 챙길게...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 50000;
			}
			else
			{
			dialog.text = "정말 어이없는 제안이군, 선장. 그 돈이면 슈쿠너 한 척을 사고도 한 달 내내 럼주를 마실 수 있겠어. 제대로 된 금액을 제시해.";
			link.l1 = "이 정도 금액이면 나한테는 충분히 합리적으로 보인다. 이보다 적은 돈 때문에 너랑 시간 낭비할 생각 없어. 우리는 몇 페소에 구걸하는 거지들이 아니거든. 좋아... 할 말은 다 했으니 이제 충분하다. 내기할 용기가 없으면 그건 네 선택이지... 허세 부리는 것도 공짜는 아니야.";
			link.l1.go = "Race_exit";
			link.l2 = "정말이야? 좋아. 생각 좀 해보자...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate4"://40 000
			if (hrand(9, "&RacRa") > 4)
			{
			dialog.text = "좋아. 동의하지. 돈을 내놔. 여기 내 내기다.";
			link.l1 = "잠깐만, 내 지갑 좀 챙길게...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 40000;
			}
			else
			{
			dialog.text = "정말 말도 안 되는 제안이군, 선장! 그 돈이면 바크 한 척을 사고도 한 달 내내 럼주를 마실 수 있겠어. 적당한 금액을 제시해.";
			link.l1 = "이 금액이면 나한텐 충분히 합리적으로 보이네, 그리고 이보다 적은 돈 때문에 너랑 시간 낭비할 생각 없어. 우리는 몇 페소에 구걸하는 거지들이 아니거든. 좋아... 할 얘긴 다 했으니 이제 충분하다. 내기할 용기가 없으면 그건 네 선택이지... 허세 부리는 것도 공짜가 아니야.";
			link.l1.go = "Race_exit";
			link.l2 = "정말이야? 좋아. 생각 좀 해볼게...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate3"://30 000
			if (hrand(9, "&RacRa") > 2)
			{
			dialog.text = "좋아. 동의하지. 네 돈을 내놔. 여기 내 내기다.";
			link.l1 = "잠깐만, 내 돈주머니 좀 가져올게...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 30000;
			}
			else
			{
			dialog.text = "정말 어이없는 제안이군, 선장. 그 돈이면 슬루프 한 척을 사고 한 달 내내 럼주도 마실 수 있겠어. 제대로 된 금액을 제시해.";
			link.l1 = "이 정도 금액이면 나한테는 충분히 합리적으로 보이네, 그리고 이보다 적은 돈으로는 너랑 시간 낭비할 생각 없어. 우리는 몇 페소 때문에 구걸하는 거지들이 아니거든. 좋아... 얘기는 충분히 했으니 이제 됐어. 내기에 겁이 난다면 그건 네 선택이지... 허세 부리는 것도 공짜가 아니야.";
			link.l1.go = "Race_exit";
			link.l2 = "정말이야? 좋아. 생각 좀 해보자...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate2"://20 000
			if (hrand(9, "&RacRa") > 0)
			{
			dialog.text = "좋아. 동의하지. 네 동전 내놔. 여기 내 내기다.";
			link.l1 = "잠깐만, 내 돈주머니 좀 챙길게...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 20000;
			}
			else
			{
			dialog.text = "정말 말도 안 되는 제안이군, 선장. 그 돈이면 루거 한 척을 사고도 한 달 내내 럼주를 마실 수 있겠어. 제대로 된 금액을 제시해.";
			link.l1 = "이 금액이면 나한텐 충분히 괜찮아 보여. 이보다 적으면 너랑 시간 낭비할 생각 없어. 우리는 몇 페소 때문에 구걸하는 거지들이 아니거든. 좋아... 할 말 다 했으니 이제 됐다. 내기할 용기가 없으면 그건 네 선택이지... 허세 부리는 것도 공짜가 아니야.";
			link.l1.go = "Race_exit";
			link.l2 = "정말이야? 좋아. 생각 좀 해보자...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate1"://10 000
			dialog.text = "좋아. 동의하지. 돈을 내놔. 여기 내 내기다.";
			link.l1 = "잠깐만, 내 돈주머니 좀 챙길게...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 10000;
		break;
		
		case "Racing_rate":
			dialog.text = "그래?";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Racing.Go.Money))
			{
			link.l1 = "여기 있다!";
			link.l1.go = "Racing_Go";
			}
			else
			{
			link.l1 = "흠... 내게 그만큼은 없는 것 같군.";
			link.l1.go = "Racing_rate_nomoney";
			}
		break;
		
		case "Racing_rate_nomoney":
			if (sti(pchar.GenQuest.Racing.Go.Money) == 10000 || sti(pchar.Money) < 10000)
			{
			dialog.text = "글쎄, 우리야 몇 페소 걸려고 구걸하는 거지들이 아니란 거 알잖아, 아니면 겁먹은 거야? 좋아, 네 맘대로 해. 하지만 남을 너무 쉽게 판단하지 마라; 상인들 중에도 노련한 선원들이 많으니까... 너보다 훨씬 더 경험 많은 이들이 있지.";
			link.l1 = "알았어, 알았어, 설교는 그만해, 철학자. 잘 가라...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
			}
			else
			{
			dialog.text = "그러니까 주머니를 확인하거나 판돈을 좀 줄여보는 게 어때?";
			link.l1 = "좋아, 내가 가진 돈이 얼마나 되는지 기억해 보려고 할게...";
			link.l1.go = "Race_begin_5";
			link.l2 = "내 마음이 바뀌었어.";
			link.l2.go = "Racing_exit";
			}
		break;
		
		case "Racing_exit":
			dialog.text = "생각이 바뀌었나? 겁먹은 거 아니야? 좋아, 네 멋대로 해. 하지만 남을 함부로 판단하지 마라, 상인들 중에도 노련한 선원들이 많으니까... 너보다 훨씬 더 경험 많은 사람들이지.";
			link.l1 = "좋아, 좋아, 설교는 그만해라, 철학자 녀석. 잘 가라...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
		break;
		
		case "Racing_Go":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Racing.Go.Money));
			dialog.text = "그럼 내기 성사군! 괜찮다면 바텐더를 불러 증인으로 세우자고... 그리고 우리 판돈도 그에게 맡기자. 이긴 사람이 돌아와서 전부 가져가는 거지. 속임수는 불가능해, 소문이 군도 전체에 금방 퍼지니까 누가 이겼는지 바텐더도 알 테니.";
			link.l1 = "동의해. 그게 맞는 것 같아.";
			link.l1.go = "Racing_Go_1";
		break;
		
		case "Racing_Go_1":
			dialog.text = "음, 이제 우리 배에 올라 출항할 시간이 된 것 같군, 시간은 계속 흐르고 있으니. 너는 어떤지 모르겠지만, 나는 바로 출항할 거야. 아, 그리고 내 배는 플루트선이고 이름은 "+pchar.GenQuest.Racing.Go.ShipName+". 항구에 도착하면 그녀를 쉽게 알아볼 수 있을 거요.";
			link.l1 = "아직 축하하긴 이르다. 선술집에서 보자, "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City+"Gen")+"!";
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
			dialog.text = "헤! 사실 좀 놀랐군... 축하하오, 선장! 정말 나보다 빠르구만. 힘에는 항상 더 강한 힘이 있다던데, 맞지 않소?";
			link.l1 = "정확합니다, 나리. 하지만 말씀드리자면, 무역선 선장치고는 놀랄 만큼 노련하고 능숙하시군요. 그렇게 짧은 시간에 플루트를 저렇게 다룰 수 있는 상인은 많지 않습니다.";
			link.l1.go = "Racing_Finished_1";
			}
			else
			{
			dialog.text = "글쎄, 놀랐지, 선장? 내가 말했잖아, 나는 바다를 잘 알고 내 배도 충분히 잘 다룬다고. 이제 알겠어?";
			link.l1 = "으악! 믿을 수가 없군! 슬루프로... 그렇게 멀리, 그것도 그렇게 짧은 시간에... 축하하오, 선장!";
			link.l1.go = "Racing_Finished_2";
			}
			//bDisableFastReload = false;
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload1_back", false);
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload2_back", false);
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "gate_back", false);
		break;
		
		case "Racing_Finished_1":
			dialog.text = "자, 네가 이겼다. 이제 돌아가야 해\n "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity)+" 그리고 바텐더에게서 돈을 받아가. 너라면 충분히 받을 자격이 있지!";
			link.l1 = "이미 가는 중이야. 즐거웠어. 잘 있어!";
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
			dialog.text = "그건 비밀이 아니야, 그냥 실력과 경험이지. 그리고 나는 가야 해\n "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Acc")+" 내 상금을 받으려고.";
			link.l1 = "네가 자격을 얻었어. 잘 가!";
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
			dialog.text = "다른 이야기하고 싶은 게 있나?";
			link.l1 = "아니, 아무것도 아니야.";
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
switch (rand(6))
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

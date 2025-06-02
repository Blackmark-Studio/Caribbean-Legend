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
				dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Nazywam się "+GetFullName(NPChar)+", jestem kapitanem. Widzę, że ty także jesteś kapitanem. Chciałbyś dołączyć do mnie i wypić razem drinka? Ja stawiam.";
				link.l1 = "Dlaczego nie? Nie miałbym nic przeciwko wypiciu kilku drinków w dobrym towarzystwie.";
				link.l1.go = "Race_prepare";
				link.l2 = "Przepraszam, ale się spieszę. Następnym razem.";
				link.l2.go = "exit";
				npchar.quest.race = "true";
			}
			else
			{
			//конвой торгового судна
				if(!CheckAttribute(pchar, "GenQuest.Escort.Trader") && !CheckAttribute(npchar, "quest.race") && sti(Pchar.Ship.Type) != SHIP_NOTUSED && !CheckAttribute(npchar, "repeat_work") && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0 && GetCompanionQuantity(pchar) < 3)
				{
					dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Jestem "+GetFullName(NPChar)+", kupiec. Zakładam, że jesteś kapitanem. Co powiesz na zarobienie kilku tysięcy pesos?";
					link.l1 = "Zawsze chętnie zarobię kilka monet. O jakiej pracy mówimy?";
					link.l1.go = "Escort_choice";
					link.l2 = "A jaką pracę handlarz może zaproponować, co? Ochronić jego zgniły statek? Nie pomagam spekulantom.";
					link.l2.go = "exit_distress";
					SaveCurrentNpcQuestDateParam(npchar, "repeat_work");
				}
				else
				{
					dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Jak się masz? Potrzebujesz czegoś?";
					link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+"Nie, nie mam. Po prostu chciałem się przywitać. Miłego pobytu!";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "exit_distress":
			DialogExit();
			NextDiag.CurrentNode = "Trader_distress";
		break;
		
		case "Trader_distress":
			dialog.text = "Kapitanie, już rozmawialiśmy, prawda? 'Nie pomagasz dorobkiewiczom', więc czego teraz ode mnie chcesz?";
			link.l1 = "Tak, i masz rację. Dobrze, po prostu usiądź tu na swoim tłustym tyłku i pij rum. Muszę iść.";
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
					dialog.text = "Chciałbym prosić cię o eskortowanie mnie do "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Generał")+" w środku "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+"Zapłacę ci "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "A dlaczego nie? Zawsze bezpieczniej jest żeglować razem, rozumiem to. Zgadzam się.";
					link.l1.go = "EscortType";
					link.l2 = "Z przyjemnością bym pomógł, ale zmierzam w innym kierunku.";
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
					dialog.text = "Chciałbym prosić cię o eskortowanie mnie do "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Generał")+", niedaleko od "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+" wewnątrz "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+" Zapłacę ci "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "I dlaczego nie? Zawsze bezpieczniej jest żeglować razem, rozumiem to. Zgadzam się.";
					link.l1.go = "EscortType";
					link.l2 = "Chętnie pomogę, ale zmierzam w innym kierunku.";
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
					dialog.text = "Chciałbym prosić cię o eskortę do "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+" który jest w "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Island)+", w "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+" Zapłacę ci "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "A dlaczego nie? Zawsze bezpieczniej jest żeglować razem, rozumiem to. Zgadzam się. Ale nigdy nie słyszałem o sklepach i punktach handlowych tam.";
					link.l1.go = "EscortType";
					link.l2 = "Z przyjemnością pomógłbym, ale zmierzam w innym kierunku.";
					link.l2.go = "Escort_exit";
				break;
			}
		break;
		
		case "Escort_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Escort.Trader");
		break;
		
		case "Trader_wait":
			dialog.text = "Jesteś gotów do żeglugi, kapitanie? Czekam na twoje rozkazy.";
			link.l1 = "Tak, teraz wypływamy. Do zobaczenia w porcie.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Trader_wait";
		break;
		
		case "EscortType":
			dialog.text = "Znakomicie! Cieszę się, że zawarliśmy umowę. Mam nadzieję, że nasza podróż będzie bezpieczna.";
			link.l1 = "Tak samo i ja. Czas podnieść żagle!";
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
			if (sti(pchar.GenQuest.Escort.Trader.Chance) == 1) CoolTraderHunterOnMap();
				else TraderHunterOnMap();//запуск ДУ на глобалке
			}
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type2"))//в бухту
			{
				pchar.GenQuest.Escort.Trader.Location = pchar.GenQuest.Escort.Trader.Shore;
				if (sti(pchar.GenQuest.Escort.Trader.Chance) != 2) TraderHunterOnMap();
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
				if (sti(pchar.GenQuest.Escort.Trader.Chance) == 0) TraderHunterOnMap();
				if (sti(pchar.GenQuest.Escort.Trader.Chance) == 1) 
				{
					if(sti(RealShips[sti(pchar.Ship.Type)].Class) >= sti(RealShips[sti(pchar.GenQuest.Escort.Trader.ShipType)].Class) && sti(RealShips[sti(pchar.Ship.Type)].BaseType) != SHIP_GALEON_H && GetCompanionQuantity(pchar) < 3)//меряемся кораблями
					{//нападет сам
						pchar.quest.EscortTrader_Attack.win_condition.l1 = "location";
						pchar.quest.EscortTrader_Attack.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Island;
						pchar.quest.EscortTrader_Attack.function = "DesIslandAttack";
					}
					else CoolTraderHunterOnMap();
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
				dialog.text = "Kapitanie, powiedz mi, dlaczego cię zatrudniłem? Spójrz na mój statek! Jak on wygląda? Jest zrujnowany! Ledwo utrzymuje się na wodzie. Nie widzisz tego? Nie pojmuję - kto kogo eskortował? Tak czy inaczej, nie dostaniesz żadnej nagrody, zapomnij o tym.";
				link.l1 = "Gdyby nie ja, karmiłbyś teraz kraby, głupi kupcu. Dobra, masz dziś szczęście, ale świat jest mały i kiedyś spotkamy się na otwartym morzu!";
				link.l1.go = "EscortTrader_complete_1";
				break;
			}
			if (sti(sld.ship.HP) < makeint(sti(pchar.GenQuest.Escort.Trader.ShipMaxHP)/2))//если корпуса осталось меньше 1/2 - вторая проверка
			{
				pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.Money))/2;
				dialog.text = "Kapitanie, powiedz mi dlaczego cię zatrudniłem? Spójrz na mój statek! Jak ona wygląda? Jest zrujnowana! Ledwo utrzymuje się na wodzie... Nie widzisz tego? Tak czy inaczej, zapłacę ci tylko połowę twojej nagrody. Nie licz na więcej!";
				link.l1 = "Hmm... Dobrze, zgadzam się. Twój statek jest naprawdę... trochę uszkodzony...";
				link.l1.go = "EscortTrader_complete_2";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type2") && sti(pchar.GenQuest.Escort.Trader.Chance) == 1)//вместо денег - наводка
			{
				dialog.text = "Kapitanie, widzisz... Nie mam pieniędzy, by zapłacić ci za twą robotę. Ale nie martw się, proszę, chcę zaoferować ci inny rodzaj zapłaty, który jest znacznie większy niż obiecałem ci wcześniej!";
				link.l1 = "Hmm... Właściwie to spodziewałem się dostać monety od razu. Ale jeśli tak jest, to jestem gotów słuchać.";
				link.l1.go = "EscortTrader_complete_4";
				break;
			}
			dialog.text = "Dziękuję bardzo, kapitanie. To było bezpieczne żeglowanie z tobą mimo wszystkich niebezpieczeństw. Proszę, weź swoją nagrodę.";
			link.l1 = "Proszę bardzo... Po prostu wykonałem swoją robotę.";
			link.l1.go = "EscortTrader_complete_3";
		break;
		
		case "EscortTrader_complete_1":
			dialog.text = "Nie próbuj mnie straszyć! Twoje umiejętności bojowe sprawiają, że twoje groźby są żałosne. Żegnaj!";
			link.l1 = "Zmykaj, póki masz czas, spekulancie...";
			link.l1.go = "complete_exit";
			AddQuestRecord("TraderEscort", "4");
			AddComplexSeaExpToScill(20, 20, 20, 0, 20, 0, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 20);//везение
		break;
		
		case "EscortTrader_complete_2":
			dialog.text = "Tak, bardzo mądra obserwacja... Proszę, weź swoje "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+" i żegnaj.";
			link.l1 = "Do zobaczenia, "+npchar.name+".";
			link.l1.go = "complete_exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Escort.Trader.Money));
			AddQuestRecord("TraderEscort", "5");
			AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
			AddComplexSeaExpToScill(50, 50, 50, 0, 50, 0, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 40);//везение
		break;
		
		case "EscortTrader_complete_3":
			dialog.text = "Spisałeś się świetnie! Cóż, muszę już iść. Do widzenia, kapitanie!";
			link.l1 = "Powodzenia, "+npchar.name+"!";
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
			dialog.text = "Jest jeden kupiec - "+pchar.GenQuest.Escort.Trader.Enemyname+". Posiada i dowodzi fletą. Zostałem poinformowany, że za dwa tygodnie przybędzie na zamieszkaną wyspę "+XI_ConvertString(pchar.GenQuest.Escort.Trader.EnIsland)+", aby uzupełnić zapasy wody i handlować z miejscowymi Indianami. Będzie miał dużo "+pchar.GenQuest.Escort.Trader.add+" na pokładzie. Żałosny wojownik, nie napotkasz żadnych trudności w przejęciu jego statku\nWięc i tak na tym skorzystasz, kapitanie.";
			link.l1 = "Człowiek człowiekowi wilkiem jest?";
			link.l1.go = "EscortTrader_complete_5";
		break;
		
		case "EscortTrader_complete_5":
			dialog.text = "Przepraszam?";
			link.l1 = "Tak łatwo i szczerze 'wydajesz' swego kolegę... Ale mało mnie obchodzi twoje sumienie i dziękuję ci za tę informację. Powodzenia, panie!";
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
			dialog.text = "Eh, wypijmy trochę starego, dobrego rumu, kapitanie! Jak się masz, jak idzie twój handel?";
			link.l1 = "Nie jestem tak naprawdę kupcem. Ale radzę sobie całkiem dobrze.";
			link.l1.go = "Race_begin_1";
		break;
		
		case "Race_begin_1":
			dialog.text = "I to jest najważniejsze! Biorąc pod uwagę niebezpieczeństwa na otwartym morzu.";
			link.l1 = "Tak, masz rację. Zwłaszcza dla was, kupców, jest wielu łowców na wasze ładunki. I rzadko jesteście w stanie ani uciec, ani się bronić. Wasze statki są powolne, a działa małe, bo stawiacie zyski na pierwszym miejscu. Żeglowanie w konwojach z czterema czy pięcioma statkami razem, to jest to, co was ratuje.";
			link.l1.go = "Race_begin_2";
		break;
		
		case "Race_begin_2":
			dialog.text = "Cóż, nie wszyscy z nas tacy są, przyjacielu. Zawsze żegluję samotnie, nie potrzebuję żadnego balastu. Doskonale znam morze Karaibskie i muszę powiedzieć, że jestem naprawdę dobry w nawigacji, żeglowaniu i dowodzeniu moimi ludźmi. Potrafię uciec przed każdym piratem.";
			link.l1 = "Naprawdę? Trudno mi w to uwierzyć. Z pełnym ładunkiem na pokładzie? Na statku handlowym? Czy to znaczy, że możesz uciec przed piracką brygantyną, lugrem lub szybką korwetą?";
			link.l1.go = "Race_begin_3";
		break;
		
		case "Race_begin_3":
			dialog.text = "Wygląda na to, że wątpisz, mój drogi, w to, że mój statek jest w stanie szybko żeglować? Dobrze. Proponuję zakład.";
			link.l1 = "Jaki zakład?";
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
			dialog.text = "Słuchaj. Zamierzam dziś wyruszyć w morze do "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City)+". A ja mówię, że będę tam za "+FindRussianDaysString(pchar.GenQuest.Racing.Go.DaysQty)+" Spróbuj mnie prześcignąć i dotrzeć do "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City)+" wcześniej. Czas zaczyna teraz tykać. Chcesz zaryzykować? Czy to zbyt trudne dla ciebie?";
			link.l1 = "Dla kogo? Dla mnie? Nie bądź taki zabawny. Zamierzasz się wyrobić w tym czasie? Niedorzeczne. Dobrze, przyjmuję twój zakład. Ile jesteś gotów stracić?";
			link.l1.go = "Race_begin_5";
			link.l2 = "Jestem zbyt zajęty, aby rozpocząć wyścig z powodu jakiegoś głupiego przechwalania się.";
			link.l2.go = "Race_exit";
		break;
		
		case "Race_exit":
			dialog.text = "Hm... Boisz się przegrać? Nieważne. Ale nie osądzaj tak szybko innych ludzi, wśród kupców jest wielu doświadczonych żeglarzy... znacznie bardziej doświadczonych niż ty.";
			link.l1 = "Dobrze, dobrze, nie kazaj mi, filozofie. Żegnaj...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
		break;
		
		case "Race_begin_5":
			dialog.text = "To twój wybór, kapitanie.";
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
			dialog.text = "Zgoda. Przyjmuję. Twoje monety, proszę. Oto moja stawka.";
			link.l1 = "Pozwól mi tylko wziąć moją sakiewkę...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 50000;
			}
			else
			{
			dialog.text = "Co za bezsensowna oferta, kapitanie? Za takie pieniądze możesz kupić szkunera i pić rum przez cały miesiąc. Zaproponuj rozsądną sumę.";
			link.l1 = "Ta suma wydaje się dla mnie wystarczająco rozsądna, i nie zamierzam tracić z tobą czasu dla mniejszych pieniędzy. Nie jesteśmy żebrakami, by zakładać się o kilka peso. Dobrze... porozmawialiśmy, wystarczy teraz. Jeśli boisz się zakładać, to twój wybór... Przechwałki nie są tanie.";
			link.l1.go = "Race_exit";
			link.l2 = "Naprawdę? Dobrze. Niech pomyślę...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate4"://40 000
			if (hrand(9, "&RacRa") > 4)
			{
			dialog.text = "Dobrze. Zgadzam się. Twoje monety, proszę. Oto mój zakład.";
			link.l1 = "Tylko pozwól mi wziąć moją sakiewkę...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 40000;
			}
			else
			{
			dialog.text = "Co za bezsensowna oferta, kapitanie? Za tyle pieniędzy można kupić barkę i pić rum przez cały miesiąc. Zaproponuj rozsądną sumę.";
			link.l1 = "Ta suma wygląda dla mnie wystarczająco rozsądnie i nie zamierzam tracić na ciebie czasu za mniej. Nie jesteśmy żebrakami, by zakładać się o kilka pesos. Dobrze... porozmawialiśmy, wystarczy. Jeśli boisz się zakładać, to twój wybór... Przechwałki nie są tanie.";
			link.l1.go = "Race_exit";
			link.l2 = "Naprawdę? Dobrze. Niech pomyślę...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate3"://30 000
			if (hrand(9, "&RacRa") > 2)
			{
			dialog.text = "Dobrze. Zgadzam się. Twoje monety, proszę. Oto mój zakład.";
			link.l1 = "Pozwól mi tylko wziąć moją sakiewkę...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 30000;
			}
			else
			{
			dialog.text = "Co za bezsensowna oferta, kapitanie? Za tyle pieniędzy można kupić slup i pić rum przez cały miesiąc. Zaproponuj rozsądną sumę.";
			link.l1 = "Ta suma wygląda dla mnie dostatecznie rozsądnie, i nie zamierzam tracić czasu z tobą za mniej. Nie jesteśmy żebrakami, by zakładać się o kilka peso. Dobrze... porozmawialiśmy, wystarczy. Jeśli boisz się zakładać, to twój wybór... Przechwałki nie są tanie.";
			link.l1.go = "Race_exit";
			link.l2 = "Naprawdę? Dobrze. Daj mi pomyśleć...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate2"://20 000
			if (hrand(9, "&RacRa") > 0)
			{
			dialog.text = "Zgoda. Zgadzam się. Twoje monety, proszę. Oto mój zakład.";
			link.l1 = "Pozwól, że wezmę swoją sakiewkę...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 20000;
			}
			else
			{
			dialog.text = "Co za bezsensowna oferta, kapitanie? Za tyle pieniędzy możesz kupić lugier i pić rum przez cały miesiąc. Zaproponuj rozsądną sumę.";
			link.l1 = "Ta suma wygląda dla mnie wystarczająco rozsądnie i nie zamierzam marnować na ciebie czasu za mniej. Nie jesteśmy żebrakami, by zakładać się o kilka peso. Dobrze... porozmawialiśmy, wystarczy. Jeśli boisz się zakładu, to twój wybór... Przechwałki nie są tanie.";
			link.l1.go = "Race_exit";
			link.l2 = "Naprawdę? Dobrze. Daj mi pomyśleć...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate1"://10 000
			dialog.text = "Dobrze. Zgadzam się. Twoje monety, proszę. Oto mój zakład.";
			link.l1 = "Pozwól mi tylko wziąć moją sakiewkę...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 10000;
		break;
		
		case "Racing_rate":
			dialog.text = "Więc?";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Racing.Go.Money))
			{
			link.l1 = "Tu!";
			link.l1.go = "Racing_Go";
			}
			else
			{
			link.l1 = "Hm... wygląda na to, że nie mam aż tyle.";
			link.l1.go = "Racing_rate_nomoney";
			}
		break;
		
		case "Racing_rate_nomoney":
			if (sti(pchar.GenQuest.Racing.Go.Money) == 10000 || sti(pchar.Money) < 10000)
			{
			dialog.text = "Cóż, wiesz, nie jesteśmy jakimiś żebrakami, by zakładać się o kilka pesos, czy może po prostu się boisz? Dobrze, do diabła z tobą. Ale nie osądzaj tak szybko innych ludzi, wśród kupców jest wielu doświadczonych żeglarzy... o wiele bardziej doświadczonych niż ty.";
			link.l1 = " Dobrze, dobrze, nie kaznodziej mnie filozofie. Żegnaj...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
			}
			else
			{
			dialog.text = "Więc czemu nie sprawdzisz swej sakiewki lub nie postawisz mniejszej stawki?";
			link.l1 = "Dobrze, spróbuję zapamiętać, ile mam monet...";
			link.l1.go = "Race_begin_5";
			link.l2 = "Zmieniłem zdanie.";
			link.l2.go = "Racing_exit";
			}
		break;
		
		case "Racing_exit":
			dialog.text = "Zmieniliście zdanie, co? Nie jesteście przypadkiem przerażeni? Dobra, do diabła z wami. Ale nie osądzajcie tak szybko innych ludzi, wśród kupców jest wielu doświadczonych żeglarzy... o wiele bardziej doświadczonych niż wy.";
			link.l1 = " Dobrze, dobrze, nie moralizuj mi tu, filozofie. Żegnaj...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
		break;
		
		case "Racing_Go":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Racing.Go.Money));
			dialog.text = "Mamy więc zakład! Zawołajmy barmana na świadka, jeśli nie masz nic przeciwko... i dajmy mu nasze stawki. Zwycięzca wróci i zabierze całą sumę. Oszustwo jest niemożliwe, ponieważ plotki rozchodzą się po archipelagu bardzo szybko, więc będzie wiedział, kto jest zwycięzcą.";
			link.l1 = "Zgadzam się. To wydaje się słuszne.";
			link.l1.go = "Racing_Go_1";
		break;
		
		case "Racing_Go_1":
			dialog.text = "Cóż, przypuszczam, że nadszedł czas, abyśmy wsiedli na nasze statki i wyruszyli w morze, czas ucieka. Nie wiem jak ty, ale ja wyruszam natychmiast. Och, a mój statek to flauta, a jej imię to "+pchar.GenQuest.Racing.Go.ShipName+" . Przypuszczam, że łatwo ją rozpoznasz w porcie, gdy dotrzesz na miejsce.";
			link.l1 = "Nie skacz z radości tak szybko. Do zobaczenia w tawernie "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City+"Generał")+"!";
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
			dialog.text = "Heh! Jestem naprawdę zaskoczony... Gratulacje, kapitanie! Naprawdę jesteś szybszy ode mnie. Mówią, że na każdą siłę znajdzie się większa siła, prawda?";
			link.l1 = "Dokładnie, panie. Ale chcę powiedzieć, że jesteś zaskakująco doświadczony i zręczny jak na kapitana statku handlowego. Nie każdy kupiec potrafi w taki sposób żeglować na fleucie przez tak krótki czas.";
			link.l1.go = "Racing_Finished_1";
			}
			else
			{
			dialog.text = "Cóż, czyż nie jesteś zaskoczony, kapitanie? Jak mówiłem, doskonale znam morze i prowadzę mój statek wystarczająco dobrze. Widzisz teraz?";
			link.l1 = "Argh! Niesamowite! Na flecie... tak daleko i w tak krótkim czasie... Gratulacje, kapitanie!";
			link.l1.go = "Racing_Finished_2";
			}
			//bDisableFastReload = false;
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload1_back", false);
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload2_back", false);
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "gate_back", false);
		break;
		
		case "Racing_Finished_1":
			dialog.text = "Cóż, jesteś zwycięzcą. Teraz musisz wrócić do "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity)+" i odbierz swoje pieniądze od karczmarza. Z pewnością na nie zasłużyłeś!";
			link.l1 = "Już jestem w drodze. To była przyjemność. Do widzenia!";
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
			dialog.text = "Nie ma w tym żadnej tajemnicy, tylko umiejętności i doświadczenie. A ja muszę iść do "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Acc")+" aby odebrać moją nagrodę.";
			link.l1 = "Zasłużyłeś na to. Żegnaj!";
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
			dialog.text = "Czy jest coś jeszcze, o czym chcesz porozmawiać?";
			link.l1 = "Nie, to nic takiego.";
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

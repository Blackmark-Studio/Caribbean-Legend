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
			dialog.text = "Robak. Pamiętaj, aby powiedzieć deweloperom.";
			link.l1 = "Dobrze.";
			link.l1.go = "exit";
		break;
		
		//разговор на палубе
		case "MarchCap":
			pchar.quest.MarchCapOver.over = "yes"; //снять прерывание
			dialog.text = "Oto jesteś, kapitanie. Omówmy szczegóły mojej oferty. Zrozumiesz, dlaczego nie chciałem o tym rozmawiać publicznie.";
			link.l1 = "Proszę mówić, sir. Słucham.";
			link.l1.go = "MarchCap_1";
		break;
		
		case "MarchCap_1":
			pchar.GenQuest.MarchCap.Goods = SelectMarchCapGoods1();//целевой товар
			switch (rand(2))
			{
				case 0: //конвой у острова, установка параметров
					pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
					while(pchar.GenQuest.MarchCap.Island == pchar.GenQuest.MarchCap.Startisland)
					{
						pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
					}
					pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
					while(pchar.GenQuest.MarchCap.Island.Shore == "")
					{
						pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
						pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
						if (!isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island) || !isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island.Shore)) pchar.GenQuest.MarchCap.Island.Shore = "";
					}
					pchar.GenQuest.MarchCap.DaysQty = GetMaxDaysFromIsland2Island(pchar.GenQuest.MarchCap.Startisland, pchar.GenQuest.MarchCap.Island)+3;
					dialog.text = "Udało mi się dowiedzieć, że w "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" mały konwój handlowy pod banderą "+NationNameGenitive(sti(pchar.GenQuest.MarchCap.Nation))+", dwie handlowe fregaty i jeden statek strażniczy, będą żeglować blisko "+XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Kapitan")+", to nie jest daleko od "+XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Generał")+"  Kupcy mają dużo  "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" w ich ładowniach. Byłoby głupotą nie wykorzystać tej informacji, kapitanie\nTy i ja możemy łatwo poradzić sobie ze strażnikami i zabrać ładunek dla siebie. A więc, wchodzisz w to?";
					link.l1 = "Brzmi kusząco. Powiedziałbym tak!";
					link.l1.go = "MarchCap_1_1";
					link.l2 = "Trochę"+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+"  to dla mnie za mało, by psuć moje relacje z "+NationNameAblative(sti(pchar.GenQuest.MarchCap.Nation))+" Nie, nie zamierzam tego robić! Żegnaj, panie, i nawet nie próbuj mnie zatrzymać!";
					link.l2.go = "MarchCap_exit";
				break;
				
				case 1: //энкаунтер на глобалке, установка параметров
					pchar.GenQuest.MarchCap.Startcity = SelectAnyColony(pchar.GenQuest.MarchCap.basecity);
					pchar.GenQuest.MarchCap.Finishcity = SelectAnyColony2(pchar.GenQuest.MarchCap.basecity, pchar.GenQuest.MarchCap.Startcity);
					pchar.GenQuest.MarchCap.DaysQty = 5+hrand(5);
					dialog.text = "Udało mi się dowiedzieć, że w "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" mały konwój handlowy pod banderą "+NationNameGenitive(sti(pchar.GenQuest.MarchCap.Nation))+", dwa statki handlowe i jeden statek strażniczy, wypłyną z "+XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Startcity+"Gen")+" do "+XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Finishcity+"Zatwierdź")+"  Kupcy mają dużo "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" w ich ładowniach. Byłoby głupotą nie wykorzystać tej informacji, kapitanie.\nTy i ja możemy łatwo poradzić sobie ze strażnikami i zabrać ładunek dla siebie. Najtrudniejsza część to znaleźć ich na otwartym morzu pomiędzy tymi dwiema koloniami. Więc, jesteś zainteresowany?";
					link.l1 = "Brzmi kusząco. Powiedziałbym tak!";
					link.l1.go = "MarchCap_2_1";
					link.l2 = "Nieco "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" to za mało, bym psuł swoje relacje z "+NationNameAblative(sti(pchar.GenQuest.MarchCap.Nation))+" Nie, nie zamierzam tego robić! Żegnaj, panie, i nawet nie próbuj mnie zatrzymywać!";
					link.l2.go = "MarchCap_exit";
				break;
				
				case 2: //одиночный пиратский кулсейлор у бухты, установка параметров
					pchar.GenQuest.MarchCap.Goods = GOOD_GOLD + hrand(makeint(GOOD_SILVER - GOOD_GOLD));
					pchar.GenQuest.MarchCap.GoodsQty = sti(pchar.rank)*50+170+rand(30);
					if (sti(pchar.GenQuest.MarchCap.GoodsQty) > 1600) pchar.GenQuest.MarchCap.GoodsQty = 1500+rand(100);
					pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
					while(pchar.GenQuest.MarchCap.Island == pchar.GenQuest.MarchCap.Startisland)
					{
						pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
					}
					pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
					while(pchar.GenQuest.MarchCap.Island.Shore == "")
					{
						pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
						pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
						if (!isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island) || !isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island.Shore)) pchar.GenQuest.MarchCap.Island.Shore = "";
					}
					pchar.GenQuest.MarchCap.DaysQty = GetMaxDaysFromIsland2Island(pchar.GenQuest.MarchCap.Startisland, pchar.GenQuest.MarchCap.Island)+1;
					pchar.GenQuest.MarchCap.PirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);//пират
					pchar.GenQuest.MarchCap.ShipType = SelectPirateShipType();
					pchar.GenQuest.MarchCap.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.MarchCap.ShipType));
					dialog.text = "Zostałem poinformowany o jednym piracie imieniem "+GetName(NAMETYPE_ORIG,pchar.GenQuest.MarchCap.PirateName,NAME_NOM)+" Ten bandyta niedawno ukradł "+RandPhraseSimple(RandPhraseSimple("Angielski","Francuski"),RandPhraseSimple("Hiszpański","Holenderski"))+" i załadował jego ładownię "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+". Ale, co za szkoda, jego statek "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.ShipType),"Nazwa")+"Acc"))+" został poważnie uszkodzony, więc musiał poświęcić czas na jej naprawę.\nObecnie jest w "+XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen")+" z "+XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen")+"  Myślę, że to zajmie około "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" aby naprawił maszty i dziury w kadłubie. Możemy tam dotrzeć na czas, jeśli się pospieszymy i wszyscy "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" będzie nasza\nNie będę w stanie poradzić sobie z tym piratem samemu, jest bardzo dobrym żeglarzem i wojownikiem, ale we dwóch możemy stawić mu czoła pomimo jego doświadczenia. Więc, jesteś z nami czy nie?";
					link.l1 = "Kusi mnie to. Powiedziałbym tak!";
					link.l1.go = "MarchCap_3_1";
					link.l2 = "Hm. Wygląda na to, że ta zdobycz jest nieosiągalna nie tylko dla ciebie, ale i dla nas obu. Nie, nie zamierzam tego robić, żegnaj, panie, i nawet nie próbuj mnie zatrzymać!";
					link.l2.go = "MarchCap_exit";
				break;
			}
		break;
		
		case "MarchCap_1_1":
			dialog.text = "Wiedziałem, że mogę na ciebie liczyć! Nie traćmy ani chwili. Idź na swój statek i obejmij dowodzenie, ja będę podążał za tobą. Czas wyruszyć w rejs!";
			link.l1 = "Rozkaz podnieść kotwicę, kapitanie!";
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
			dialog.text = "A dlaczego zaangażowałem się z tobą, kapitanie? Straciliśmy przez ciebie tak cenną zdobycz! Lepiej popłynę następnym razem sam...";
			link.l1 = "Twoja wina, nie moja. Do widzenia.";
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
				dialog.text = "Jesteś takim nieudacznikiem, kapitanie! Nie dostaliśmy ani kawałka! A to wszystko przez ciebie! To ty jesteś przyczyną naszej porażki, do diabła z tobą!";
				link.l1 = "Czyżby? Spójrz na siebie! Nie pomogłeś mi w bitwie! Tylko zmarnowałem z tobą czas... Wynoś się z mojego statku!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "bad";
				break;
			}
			if (iTemp > 50 && iTemp < 500)
			{
				dialog.text = "Cóż, ten rajd nie był tak udany, jak się spodziewałem, nasza zdobycz jest naprawdę skromna... Cóż, kapitanie, podzielmy te resztki i pożegnajmy się.";
				link.l1 = "Gdybyś mi pomagał, zamiast liczyć ptaki na niebie, najazd byłby udany... Weź swoją część - "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+" i spadaj!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "poor";
				break;
			}
			if (iTemp > 500 && iTemp < 1500)
			{
				dialog.text = "Dobra robota, kapitanie! Jak mówiłem - łatwo było opróżnić ładownie tych kupców, ha-ha... Nagroda to "+FindRussianQtyString(iQty)+" kawałki. Mój udział to "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
				link.l1 = "To prawda, "+npchar.name+"  Nie mam żadnych zastrzeżeń. Łodzie są właśnie ładowane. Może w przyszłości zrobimy kolejny napad razem? Wyglądasz na odpowiedniego towarzysza dla mnie.";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "good";
				break;
			}
			dialog.text = "Doskonale, kapitanie! Jak mówiłem - opróżnienie ładowni tych kupców było stosunkowo łatwe, ha-ha... Nagroda jest ogromna, znacznie większa, niż się spodziewałem. To jest "+FindRussianQtyString(iQty)+" sztuki. Mój udział to "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
			link.l1 = "To prawda, "+npchar.name+" . Nie mam żadnych zastrzeżeń. Szkuty są właśnie ładowane. Być może, w przyszłości dokonamy kolejnego najazdu razem? Wyglądasz na odpowiedniego towarzysza dla mnie.";
			link.l1.go = "MarchCap_Deck_continue";
			pchar.GenQuest.MarchCap = "exellent";
		break;
		
		//если будет время - здесь создаем еще одного клона с уникальным ИД для продолжения квеста
		case "MarchCap_Deck_continue":
			dialog.text = "Jest taka możliwość, kapitanie. Znajdę cię, jeśli otrzymam kolejny dochodowy trop, z którym nie poradzę sobie sam. Wyglądasz na godnego zaufania towarzysza bitwy dla mnie również.";
			link.l1 = "Miło! Żegnaj, kapitanie. Powodzenia!";
			link.l1.go = "MarchCap_Talk_exit";
		break;
		
		case "MarchCap_2_1":
			dialog.text = "  Wiedziałem, że mogę na tobie polegać! Nie traćmy ani minuty. Idź na swój statek i przejmij dowodzenie, ja podążę za tobą.   Czas wyruszać w rejs! ";
			link.l1 = "Rozkaz podniesienia kotwicy, kapitanie.";
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
			dialog.text = "Wiedziałem, że mogę na ciebie liczyć! Nie traćmy ani minuty. Idź na swój statek i prowadź mnie. Czas wyruszać w morze!";
			link.l1 = "Rozkaz podnieść kotwicę, kapitanie.";
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
			dialog.text = "Jesteś tchórzem, do diabła z tobą! Właśnie uciekłeś z pola bitwy!";
			link.l1 = "I co myślisz, że miałem zrobić? Pozwolić temu piratowi zatopić mój statek? Nie ma mowy, wolę być żywym tchórzem niż martwym idiotą!";
			link.l1.go = "MarchCap_DieHard_1";
		break;
		
		case "MarchCap_DieHard_1":
			dialog.text = "A dlaczego ja się z tobą związałem, kapitanie? Powinienem był znaleźć człowieka, który nie bał się abordażowych szabel!";
			link.l1 = " Teraz proszę cię, byś opuścił mój statek - muszę go naprawić.";
			link.l1.go = "MarchCap_Talk_exit";
		break;
		
		case "MarchCap_AfterBattleGold":
			iTemp = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty))*sti(Goods[sti(pchar.GenQuest.MarchCap.Goods)].Weight);
			iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
			pchar.GenQuest.MarchCap.CapPart = iQty/sti(pchar.GenQuest.MarchCap.Parts);
			if (iTemp < 10)
			{
				dialog.text = "Jesteś takim przegranym, kapitanie! Nie dostaliśmy ani kawałka naszej nagrody! A to wszystko przez ciebie! Jesteś powodem naszej porażki, do diabła z tobą!";
				link.l1 = "Tak? Spójrz na siebie! Nie pomogłeś mi w bitwie! Tylko zmarnowałem na ciebie czas... Wynoś się z mojego statku!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "bad";
				break;
			}
			if (iTemp > 10 && iTemp < 100)
			{
				dialog.text = "Cóż, ten najazd nie był tak udany, jak się spodziewałem, nasza zdobycz jest naprawdę skromna... Nieważne, kapitanie, podzielmy się tymi ochłapami i pożegnajmy się.";
				link.l1 = "Gdybyś mi pomagał zamiast liczyć ptaki na niebie, najazd byłby udany... Weź swoją działkę - "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+" i zgiń!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "poor";
				break;
			}
			if (iTemp > 100 && iTemp < 500)
			{
				dialog.text = "Dobra robota, kapitanie! Nagroda to "+FindRussianQtyString(iQty)+" kawałki. Mój udział to "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
				link.l1 = "To prawda, "+npchar.name+"Nie mam żadnych zastrzeżeń. Szalupy są właśnie ładowane. Być może spotkamy się ponownie...";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "good";
				break;
			}
			dialog.text = "Wspaniale, kapitanie! Jak mówiłem - to było dość łatwe, ha-ha... Nagroda jest ogromna, znacznie większa, niż się spodziewałem. To jest "+FindRussianQtyString(iQty)+" sztuki. Mój udział to "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
			link.l1 = "To prawda, "+npchar.name+"Nie mam żadnych zastrzeżeń. Szalupy są właśnie ładowane. Może w przyszłości przeprowadzimy kolejny rajd razem? Wyglądasz na odpowiedniego towarzysza dla mnie.";
			link.l1.go = "MarchCap_Deck_continue";
			pchar.GenQuest.MarchCap = "exellent";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "MarchCap_repeat":
			dialog.text = ""+GetAddress_Form(NPChar)+", idź na swój statek. Nie mamy czasu na pogaduszki. Stawmy żagle!";
			link.l1 = "Tak, tak, oczywiście, masz rację.";
			link.l1.go = "exit";
			NextDiag.TempNode = "MarchCap_repeat";
		break;
		
		case "MarchCap_exit":
			dialog.text = "Hm... Nie zamierzam. Zjeżdżaj! Zrobię to sam!";
			link.l1 = "Cóż, cóż, życzę wam szczęśliwej podróży wtedy...";
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

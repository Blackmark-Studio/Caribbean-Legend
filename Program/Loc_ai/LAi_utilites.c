string arrayNPCModel[128];
int    arrayNPCModelHow; // для рандомизации моделей в одной локации

void CreateTraders(aref loc)
{
	if (CheckAttribute(loc, "DisableCitizens")) return;
	if(CheckAttribute(loc, "QuestCapture")) return; // если идёт квестовый бой
	if (loc.type == "town" && !LAi_IsCapturedLocation)
	{
		int iColony = -1;
		int iNation = -1;
		int iCitizensQuantity;
		ref chr;
		aref st;
		int iChar, iSex;
		string slai_group, sType, sTraderType;

		for(int n = 0; n < MAX_CHARACTERS; n++)
		{
			makeref(chr, Characters[n]);
			if (CheckAttribute(chr, "CityType") && CheckAttribute(chr, "Merchant.type") && chr.location == loc.id) return; 
		}				

		if(CheckAttribute(loc, "fastreload"))
		{
			iColony = FindColony(loc.fastreload);
		}
		if(iColony == -1)
		{
			return;
		}
	
		iNation = GetCityNation(loc.fastreload);
	
		if(iNation == -1)
		{
			return;
		}
				
		slai_group = GetNationNameByType(iNation)  + "_citizens"; 
		if (checkAttribute(loc, "locators.merchant"))
		{
			makearef(st, loc.locators.merchant);
			iCitizensQuantity = GetAttributesNum(st) / 2;
			for (int i=0; i<iCitizensQuantity; i++)
			{		
				switch (i)
				{
					case 0:
						iSex = 1;
						sType = "citizen";	
						sTraderType = "potion";	
					break;
					case 1:
						iSex = rand(1);
						sType = "citizen";
						sTraderType = "veteran";	
					break;
					case 2:
						iSex = 0;
						sType = "blade_trader";
						sTraderType = "armourer";	
					break;
					case 3:
						iSex = 0;
						sType = "monk";
						sTraderType = "monk";	
					break;
					case 4:
						iSex = 1;
						sType = "gipsy";
						sTraderType = "indian";	
					break
					case 5:
						iSex = rand(1);
						sType = "citizen";
						sTraderType = "veteran";	
					break;
					case 6:
						iSex = 0;
						sType = "blade_trader";
						sTraderType = "armourer";	
					break;
				}
			
				iChar = NPC_GeneratePhantomCharacter(sType, iNation, iSex, 180);

				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				chr.Merchant = true; // Флаг "торговец"
				chr.Merchant.type = sTraderType; 
				chr.money = TRADER_MIN_MONEY + rand(TRADER_NORM);
				
				LAi_SetLoginTime(chr, 7.0, 20.0);

				ChangeCharacterAddressGroup(chr, loc.id, "merchant", "merchant"+(i+1));
				LAi_SetMerchantType(chr);
				chr.dialog.filename = "Common_ItemTrader.c";
				chr.dialog.currentnode = "first time";
				if (chr.sex == "man") chr.greeting = "item_male";
				else chr.greeting = "item_female";			
	   			if (sti(Colonies[iColony].HeroOwn) == true)
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
				}
			}
		} 
	}	
}

// создаем горожан в локацию + солдаты, фантомы-многодневки (живут 48ч) переработка boal 13.05.06
void CreateCitizens(aref loc)
{
	if (CheckAttribute(loc, "DisableCitizens")) return;
	bool generateAffairOfHonor = true;
	bool bNightAdventure = true; // belamour ночной приключенец
	
	if (loc.type != "town" && loc.type != "church" && loc.type != "residence") return; //городской генератор не должен отрабатывать везде
	if(LAi_IsCapturedLocation) // fix нефиг грузить, когда город трупов или боевка
	{
		return;
	}
	if(CheckAttribute(loc, "QuestCapture")) return; // если идёт квестовый бой
	
	int iColony = -1;
	int iNation = -1;

	if (isLocationHasCitizens(loc.id)) return; // boal  если есть ещё с того раза, но не нужно
	
	if(CheckAttribute(loc, "fastreload"))
	{
		iColony = FindColony(loc.fastreload);
	}
	if(iColony == -1)
	{
		return;
	}
	
	iNation = GetCityNation(loc.fastreload);
	
	if(iNation == -1)
	{
		return;
	}

	int iCitizensQuantity, iModel;
	int iSailorQty, iCapQty, iCitizQty, iNobleQty, iGipsyQty, iContraQty, iIndianQty, iMonkQty, iConvQty;
	ref chr;
	aref st;
	int iChar, i, iSex;
	bool bOk;
	string slai_group, locatorName, sType;
    slai_group = GetNationNameByType(iNation)  + "_citizens"; 
	string blade; // belamour ночной приключенец
	// legendary edition отключаем Дело чести для адмирала и губернатора
	if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) generateAffairOfHonor = false;
	if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4) generateAffairOfHonor = false;
	// нищие -->
	if (loc.type == "town")
	{
		int iPoorIdx = GetCharacterIndex(colonies[iColony].id + "_Poorman");
		if (iPoorIdx != -1)
		{
			if (rand(1)) 
			{
				characters[iPoorIdx].PoorSit = true;
				sType = "locator" + rand(2);
				locatorName = characters[iPoorIdx].forSit.(sType);
			}
			else 
			{ 
				DeleteAttribute(&characters[iPoorIdx], "PoorSit");
				locatorName = characters[iPoorIdx].forStay.locator;
			}
			LAi_SetPoorTypeNoGroup(&characters[iPoorIdx]);
			if (LAi_CheckLocatorFree("goto", locatorName))
				ChangeCharacterAddressGroup(&characters[iPoorIdx], loc.id, "goto", locatorName);
			else
				PlaceCharacter(&characters[iPoorIdx], "patrol", "random_free");

		}
	}
	// нищие <--
	
	// belamour ночной приключенец -->
	if(CheckAttribute(pchar, "questTemp.Sharlie.Lock") || loc.id == "Panama_town") bNightAdventure = false;
	if(IsLoginTime()) bNightAdventure = false;
	if(!bNightAdventure) log_testinfo("Ночной приключенец отложен");
	if(CheckAttribute(pchar,"GenQuest.NightAdventure") && loc.type == "town" && bNightAdventure)
	{
		switch(rand(3)) 
		{
			case 0: // матрос
				log_testinfo("Сгенерировался 'Ночной приключенец' : Матрос");
				iSex = MAN;
				sType = "sailor";
				iChar = NPC_GeneratePhantomCharacter("sailor", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetCitizenType(chr);
				LAi_SetLoginTime(chr, 22.0, 5.99);
				blade = RandPhraseSimple("blade_03","blade_05");
				GiveItem2Character(chr, blade);
				EquipCharacterbyItem(chr, blade);
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				PlaceCharacter(chr, "goto", "random_free");
				chr.dialog.filename    = "GenQuests_Dialog.c";
				chr.dialog.currentnode = "NightAdventure_Sailor";
				chr.greeting = "habitue";
				chr.talker = rand(6);
				pchar.GenQuest.NightAdventureId = chr.id; 
				pchar.GenQuest.NightAdventure_money = 3000+(rand(200)*10);

				// варианты квеста
                switch (hrand(7, loc.id + chr.name))
                {
                    case 0: pchar.GenQuest.NightAdventureVar = "NightAdventure_SailorTavern";          break; // до таверны
                    case 1: pchar.GenQuest.NightAdventureVar = "NightAdventure_SailorShuler0";         break; // нет шулера
                    case 2: pchar.GenQuest.NightAdventureVar = "NightAdventure_SailorShulerGiveMoney"; break; // отдал деньги с миром
                    case 3: pchar.GenQuest.NightAdventureVar = "NightAdventure_SailorShulerGiveOk";    break; // честный
                    case 4: pchar.GenQuest.NightAdventureVar = "NightAdventure_SailorShulerFight";     break; // драка
                    case 5: pchar.GenQuest.NightAdventureVar = "NightAdventure_SailorBoat";            break; // до пирса
                    case 6: pchar.GenQuest.NightAdventureVar = "NightAdventure_SailorShip";            break; // захочет наняться в команду
                    case 7: pchar.GenQuest.NightAdventureVar = "NightAdventure_Bull";                  break; // пьяные наезды
				}

				log_testinfo("Вариант: "+pchar.GenQuest.NightAdventureVar);
			break;
			
			case 1: //горожанин
				log_testinfo("Сгенерировался 'Ночной приключенец' : Горожанин");
				iSex = MAN;
				sType = "citizen";
				iChar = NPC_GeneratePhantomCharacter("citizen", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetCitizenType(chr);
				LAi_SetLoginTime(chr, 22.0, 5.99);
				blade = RandPhraseSimple("blade_03","blade_05");
				GiveItem2Character(chr, blade);
				EquipCharacterbyItem(chr, blade);
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				PlaceCharacter(chr, "goto", "random_free");
				chr.dialog.filename    = "GenQuests_Dialog.c";
				chr.dialog.currentnode = "NightAdventure_Citizen";
				chr.greeting = "habitue";
				chr.talker = rand(6);
				pchar.GenQuest.NightAdventureId = chr.id; 
				pchar.GenQuest.NightAdventure_money = 3000+(rand(200)*10);

				// варианты квеста
                switch (hrand(8, loc.id + chr.name))
                {
                    case 0: pchar.GenQuest.NightAdventureVar = "NightAdventure_CitizenHomie";          break; // выручить приятеля
                    case 1: pchar.GenQuest.NightAdventureVar = "NightAdventure_CitizenHomieSolderNM";  break; // выручить приятеля солдат не возьмет денег
                    case 2: pchar.GenQuest.NightAdventureVar = "NightAdventure_CitizenHomieSolderGM";  break; // выручить приятеля солдат возьмет деньги
                    case 3: pchar.GenQuest.NightAdventureVar = "NightAdventure_CitizenHomieOfficer";   break; // выручить приятеля офицер возьмет деньги
                    case 4: pchar.GenQuest.NightAdventureVar = "NightAdventure_SailorShuler0";         break; // нет шулера
                    case 5: pchar.GenQuest.NightAdventureVar = "NightAdventure_SailorShulerGiveMoney"; break; // отдал деньги с миром
                    case 6: pchar.GenQuest.NightAdventureVar = "NightAdventure_SailorShulerGiveOk";    break; // честный
                    case 7: pchar.GenQuest.NightAdventureVar = "NightAdventure_SailorShulerFight";     break; // драка
                    case 8: pchar.GenQuest.NightAdventureVar = "NightAdventure_Bull";                  break; // пьяные наезды
                }

				log_testinfo("Вариант: "+pchar.GenQuest.NightAdventureVar);
			break;
			
			case 2: //контрабандист
				log_testinfo("Сгенерировался 'Ночной приключенец' : Контрабандист");
				iSex = MAN;
				sType = "pirate";
				iChar = NPC_GeneratePhantomCharacter("pirate", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "marginal";
				LAi_SetCitizenType(chr);
				LAi_SetLoginTime(chr, 22.0, 5.99);
				//blade = RandPhraseSimple("blade_03","blade_05");
				//GiveItem2Character(chr, blade);
				//EquipCharacterbyItem(chr, blade);
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				PlaceCharacter(chr, "goto", "random_free");
				chr.dialog.filename    = "GenQuests_Dialog.c";
				chr.dialog.currentnode = "NightAdventure_Pirate";
				chr.greeting = "habitue";
				chr.talker = rand(6);
				pchar.GenQuest.NightAdventureId = chr.id; 

				// варианты квеста
                switch (hrand(2, loc.id + chr.name))
                {
                    case 0: pchar.GenQuest.NightAdventureVar = "NightAdventure_Bull";        break; // наезды
                    case 1: pchar.GenQuest.NightAdventureVar = "NightAdventure_PiratePeace"; break; // мирный исход
                    case 2: pchar.GenQuest.NightAdventureVar = "NightAdventure_PirateBad";   break; // плохой исход
                }

				log_testinfo("Вариант: "+pchar.GenQuest.NightAdventureVar);
			break;
			
			case 3: // Дворянин
				log_testinfo("Сгенерировался 'Ночной приключенец' : Дворянин");
				iSex = MAN;
				sType = "noble";
				iChar = NPC_GeneratePhantomCharacter("noble", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetCitizenType(chr);
				LAi_SetLoginTime(chr, 22.0, 5.99);
				blade = RandPhraseSimple("blade_09","blade_15");
				GiveItem2Character(chr, blade);
				EquipCharacterbyItem(chr, blade);
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				PlaceCharacter(chr, "goto", "random_free");
				chr.dialog.filename    = "GenQuests_Dialog.c";
				chr.dialog.currentnode = "NightAdventure_Noble";
				chr.greeting = "habitue";
				chr.talker = rand(6);
				pchar.GenQuest.NightAdventureId = chr.id;
				int NABrothel = Findlocation(chr.City+"_Brothel");
				if(NABrothel != -1)
				{
					// варианты квеста
                    switch (hrand(2, loc.id + chr.name))
                    {
                        case 0: pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleGame";     break; // в карты
                        case 1: pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleGameDuel"; break; // в карты с дуэлью
                        case 2: pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleWhore";    break; // жрица
                    }
				}
				else
				{
					log_testinfo("Бордель не найден");
                    if(hrand(1,  loc.id + chr.name) == 0)
                        pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleGame";     // в карты
					else
                        pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleGameDuel"; // в карты с дуэлью
				}					
				log_testinfo("Вариант: "+pchar.GenQuest.NightAdventureVar);
			
			break;
		}
		DeleteAttribute(pchar,"GenQuest.NightAdventure");
		SetFunctionTimerCondition("NightAdventure_NextQuest", 0, 0, 12+rand(4), false);
	}
	// <-- ночной приключенец
	
    // горожане --> Jason: тотально переделал генерацию горожан - разнесено по типам
	iSailorQty = rand(2)+2;
	iContraQty = rand(1)+1;
	iCapQty = rand(1);
	iCitizQty = rand(4)+10;
	iNobleQty = rand(2)+1;
	iGipsyQty = rand(1);
	iMonkQty = rand(1);
	iIndianQty = 0;
	iConvQty = 0;
	iCitizensQuantity = rand(8)+6;
	if (loc.type == "church")
	{//лучше так, отдельным циклом работает некорректно
		iSailorQty = 0;
		iCapQty = 0;
		iNobleQty = 0;
		iContraQty = 0;
		iGipsyQty = 0;
		iMonkQty = 0;
		iIndianQty = 0;
		iConvQty = 0;
	}
	if (loc.id == "LosTeques_town")
	{
		iIndianQty = rand(2)+10;
		iContraQty = rand(2)+4;
		iCitizQty = 0;
		iSailorQty = 0;
		iCapQty = rand(2);
		iNobleQty = 0;
		iGipsyQty = 0;
		iMonkQty = 0;
		iConvQty = rand(2)+4;
	}
    arrayNPCModelHow = 0;
	if (checkAttribute(loc, "citizens") || loc.type == "church")
	{
		if(iNation != PIRATE || sti(Colonies[iColony].HeroOwn) == true)//колония
		{
			if (Colonies[iColony].id == "Pirates") return; // Исла-Тесоро у англичан заполним в другом месте
			for(i=0; i<iSailorQty; i++)//матросы
			{
                iSex = MAN;
				sType = "sailor";
				iChar = NPC_GeneratePhantomCharacter("sailor", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				LAi_SetCitizenType(chr);
				GiveItem2Character(chr, RandPhraseSimple("blade_03","blade_05"));
				EquipCharacterbyItem(chr, RandPhraseSimple("blade_03","blade_05"));
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				PlaceCharacter(chr, "goto", "random_free");
				chr.dialog.filename    = "Population\Sailor.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "town_sailor";
				if (rand(5) == 1 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock")) //нанимаются в команду
				{
					chr.quest.crew = "true";
					chr.quest.crew.qty = 5+rand(15);
					chr.quest.crew.type = rand(2);
					chr.quest.crew.money = (1+rand(1))*100+rand(50);
					chr.talker = rand(9);
				}
			}
			for(i=0; i<iGipsyQty; i++)//цыганки
			{
                iSex = WOMAN;
				sType = "gipsy";
				iChar = NPC_GeneratePhantomCharacter("gipsy", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				LAi_SetCitizenType(chr);
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				PlaceCharacter(chr, "goto", "random_free");
				chr.dialog.filename    = "Population\Gipsy.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "gipsy";
				chr.talker = 5;
			}
			for(i=0; i<iContraQty; i++)//контрики и прочие темные личности
			{
                iSex = MAN;
				sType = "marginal";
				iChar = NPC_GeneratePhantomCharacter("marginal", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				LAi_SetCitizenType(chr);
				GiveItem2Character(chr, RandPhraseSimple("blade_04","blade_06"));
				EquipCharacterbyItem(chr, RandPhraseSimple("blade_04","blade_06"));
				
				if(CheckAttribute(pchar, "questTemp.StatusCity") && chr.City == pchar.questTemp.StatusCity && !CheckAttribute(pchar, "GenQuest.Marginpassenger") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && chr.City != "LosTeques" && chr.City != "Panama")
				{
					chr.quest.passenger = "true";
					chr.talker = rand(3);
				}
				if (rand(7) < 2 && !CheckAttribute(pchar, "GenQuest.Marginpassenger") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && chr.City != "LosTeques" && chr.City != "Panama") //захват пассажира
				{
					chr.quest.passenger = "true";
					chr.talker = rand(3);
				}
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				PlaceCharacter(chr, "goto", "random_free");
				chr.dialog.filename    = "Population\Marginal.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "marginal";
			}
			for(i=0; i<iCapQty; i++)//капитаны кораблей
			{
				iSex = MAN;
				sType = "captain";
				iChar = NPC_GeneratePhantomCharacter("captain", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				LAi_SetCitizenType(chr);
				GiveItem2Character(chr, RandPhraseSimple("blade_10","blade_13"));
				EquipCharacterbyItem(chr, RandPhraseSimple("blade_10","blade_13"));
				if (rand(3) < 1 && !CheckAttribute(pchar, "GenQuest.MarchCap") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && chr.City != "Panama") //пойдём на дельце patch-5
				{
					chr.quest.march = "true";
					chr.talker = rand(1);
				}
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				PlaceCharacter(chr, "goto", "random_free");
				chr.dialog.filename    = "Population\Captain.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "captain";
			}
			for(i=0; i<iCitizQty; i++)//мещане-бюргеры + посетители церкви
			{
				if (loc.type == "church") iSex = MAN;
				else iSex = rand(WOMAN);
				sType = "citizen";
				iChar = NPC_GeneratePhantomCharacter("citizen", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				if (loc.type == "church" && chr.sex == "man")
				{
				    LAi_SetSitType(chr);
					PlaceCharacter(chr, "sit", "random_free");
					chr.dialog.filename = "Enc_Walker.c";
					chr.greeting = "citizen_male";
					chr.nonTable = true;
					chr.inChurch = true;
				}
				else
				{
					LAi_SetCitizenType(chr);
					PlaceCharacter(chr, "goto", "random_free");
				}
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				chr.dialog.currentnode = "first time";
				if(chr.sex == "man")
				{
					chr.dialog.filename = "Population\Townman.c";
					chr.greeting = "citizen_male";
					if (CheckAttribute(pchar, "questTemp.StatusCity") && chr.City == pchar.questTemp.StatusCity && loc.type != "church" && chr.City != "Panama")
					{
						chr.quest.passenger = "true";
						chr.talker = rand(3);
					}
					if (rand(6) > 4 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && loc.type != "church" && chr.City != "Panama") //пассажирский генератор patch-5
					{
						chr.quest.passenger = "true";
						chr.talker = rand(3);
					}
				}
				else
				{
					chr.dialog.filename = "Population\Towngirl.c";
					chr.greeting = "citizen_female";
				}
				// Warship, 25.05.11. "Дело чести" -->
				// belamour legendary edition встречается значительно чаще
				bool bAh = (hrand(4, loc.id) == 4) && (!CheckAttribute(pchar, "questTemp.Sharlie.Lock")) && (!CheckAttribute(pchar, "GenQuest.Escort.Trader"))
				if(bAh || bBettaTestMode)
				{
					if(generateAffairOfHonor)
					{
						if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.FinishCount")) PChar.QuestTemp.AffairOfHonor.FinishCount = 0;
						//pchar.questTemp.AffairOfHonor.LighthouseId = Island_GetLighthouseId(loc.islandId);
						pchar.questTemp.AffairOfHonor.LighthouseId = Colony_GetLighthouseId(loc.fastreload);
						
						if(loc.type == "town" && chr.City != "PortRoyal" && chr.City != "FortOrange" && PChar.QuestTemp.AffairOfHonor.LighthouseId != "" && AffairOfHonor_GetCurQuest() == "")
						{
							if(sti(PChar.QuestTemp.AffairOfHonor.FinishCount) < 8 && !CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor") && GetCharacterIndex("AffairOfHonor_QuestMan") == -1)
							{
								if(chr.sex == "man" || !CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Cavalier"))
								{
									// Jason: дохляки нам не нужны - делаем кулфайтера
									int Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10;
									int Scl = 30+2*sti(pchar.rank);
									chr.id = "AffairOfHonor_QuestMan";
									chr.rank = Rank;
                                    if(chr.sex == "man")
                                    {
										FantomMakeCoolFighter(chr, Rank, Scl, Scl, RandPhraseSimple("blade_08","blade_09"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
										float Mft = MOD_SKILL_ENEMY_RATE/20;
										chr.MultiFighter = 1.0+Mft; // мультифайтер
									}
									chr.dialog.filename = "Quest\ForAll_dialog.c";
									chr.dialog.currentnode = "AffairOfHonor_1";
									chr.talker = rand(3);
									LAi_SetImmortal(chr, true);
									generateAffairOfHonor = false; // Чтобы по двести раз не генерило квестодателей.
									Log_TestInfo("Сгенерилось дело чести");
								}
							}
						}
					}
				}
				// <--
			}
			for(i=0; i<iNobleQty; i++)//дворяне
			{
				iSex = rand(WOMAN);
				sType = "noble";
				iChar = NPC_GeneratePhantomCharacter("noble", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				LAi_SetCitizenType(chr);
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				PlaceCharacter(chr, "goto", "random_free");
				if(chr.sex == "man")
				{
					chr.dialog.filename = "Population\Nobleman.c";
					chr.greeting = "noble_male";
					GiveItem2Character(chr, RandPhraseSimple("blade_15","blade_16"));
					EquipCharacterbyItem(chr, RandPhraseSimple("blade_15","blade_16"));
					if(CheckAttribute(pchar, "questTemp.StatusCity") && chr.City == pchar.questTemp.StatusCity && chr.City != "Panama")
					{
						chr.quest.passenger = "true";
						chr.talker = rand(3);
					}
					else
					{
						if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
						{
							if (rand(11) > 9 && GetCharacterIndex("QuestCitiz_" + loc.fastreload) == -1  && !CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
							{//поисковый генератор
								chr.id = "QuestCitiz_" + loc.fastreload;
								chr.dialog.filename = "Quest\ForAll_dialog.c";
								chr.dialog.currentnode = "SCQ_Nobleman";
								chr.talker = rand(3); //начать диалог
								chr.quest.SeekCap.numQuest = rand(1); //какой квест будет давать
							}
							if (rand(11) < 2  && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && chr.City != "Panama") //пассажирский генератор patch-5
							{
								chr.quest.passenger = "true";
								chr.talker = rand(3);
							}
							if (rand(11) == 3) chr.quest.donation = "true"; //клянчит деньги
							if (rand(11) == 5) chr.quest.lombard = "true"; //семейная реликвия
							if (rand(11) == 7) chr.quest.slaves = "true"; //привезти рабов
						}
					}
				}
				else
				{
					chr.dialog.filename = "Population\Noblegirl.c";
					chr.greeting = "noble_female";
				}
			}
			for(i=0; i<iIndianQty; i++)//индейцы
			{
                if (i < 9) iSex = MAN;
				else iSex = WOMAN;
				sType = "indian";
				iChar = NPC_GeneratePhantomCharacter("indian", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				LAi_SetCitizenType(chr);
				if(chr.sex == "man")
				{
					chr.name = GetIndianName(MAN);
					chr.lastname = "";
					GiveItem2Character(chr, "slave_02");
					EquipCharacterbyItem(chr, "slave_02");
					chr.greeting = "indian_male";
				}
				else
				{
					chr.name = GetIndianName(WOMAN);
					chr.lastname = "";
					RemoveAllCharacterItems(chr, true);
					//chr.greeting = "Gr_Woman_Citizen";
				}
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				PlaceCharacter(chr, "goto", "random_free");
				chr.dialog.filename    = "Population\Indian.c";
				chr.dialog.currentnode = "first time";
			}
			for(i=0; i<iConvQty; i++)//каторжники на руднике
			{
                iSex = MAN;
				sType = "convict";
				iChar = NPC_GeneratePhantomCharacter("convict", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				LAi_SetCitizenType(chr);
				GiveItem2Character(chr, "slave_02");
				EquipCharacterbyItem(chr, "slave_02");
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				PlaceCharacter(chr, "goto", "random_free");
				chr.dialog.filename    = "Population\Convict.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "convict";
			}
			for(i=0; i<iMonkQty; i++)//монахи
			{
                iSex = MAN;
				sType = "monk";
				iChar = NPC_GeneratePhantomCharacter("monk", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				LAi_SetCitizenType(chr);
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
				{
					if (rand(4) == 1) //собирает пожертвования
				{
					chr.quest.donation = "true";
					chr.talker = rand(3);
				}
					if (rand(4) == 0 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && chr.City != "Panama") //пассажирский генератор patch-5
				{
					chr.quest.passenger = "true";
					chr.talker = rand(3);
				}
					// Captain Beltrop, 04.05.21, правка выхода за границы массива при отсутствии корабля
				if (rand(4) == 4 && !CheckAttribute(pchar, "questTemp.ShipCapellan") && pchar.ship.type != SHIP_NOTUSED && 6-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0) //корабельный капеллан
				{
					chr.quest.capellan = "true";
					chr.talker = 9;
				}
				}
				PlaceCharacter(chr, "goto", "random_free");
				chr.dialog.filename    = "Population\Monk.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "monk";
			}
		}
		else
		{
			for(i=0; i<iCitizensQuantity; i++)//пиратское поселение
			{
				iSex = MAN;
				sType = "pirate";
				iChar = NPC_GeneratePhantomCharacter("pirate", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				LAi_SetWarriorType(chr);
				LAi_warrior_DialogEnable(chr, true);
				chr.watchBoxes = true;
				LAi_group_MoveCharacter(chr, slai_group);
				chr.dialog.filename    = "Population\Townman.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "town_pirate";
				PlaceCharacter(chr, "goto", "random_free");
			}
		}
	}
	// горожане <--    
	
	// солдаты -->
	if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.soldiers"))
	{
		aref solderLoc;
		makearef(st, loc.locators.soldiers);
		iCitizensQuantity = GetAttributesNum(st);
		for (i=0; i<iCitizensQuantity; i++)
		{
			if(iNation != PIRATE)
			{
                sType = "soldier";
				iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
			}
			else
			{
                sType = "pirate";
				iChar = NPC_GeneratePhantomCharacter("pirate", iNation, MAN, 2);
			}
			chr = &characters[iChar];
			SetNPCModelUniq(chr, sType, MAN);
			chr.City = Colonies[iColony].id;
            chr.CityType = "soldier";
			chr.RebirthPhantom = true; 
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //задаем шаг на увеличение ранга фантомам на реинкарнацию
            SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
			LAi_SetLoginTime(chr, 6.0, 23.0); //а ночью будет беготня от патруля :)

			//locatorName = PlaceCharacter(chr, "soldiers", "random_free"); // бага наложения была из-за правки рандома
			solderLoc = GetAttributeN(st, i);
			locatorName = GetAttributeName(solderLoc);
			ChangeCharacterAddressGroup(chr, pchar.location, "soldiers", locatorName);
			// eddy. проверяем, должен ли солдат быть протектором -->
			if (findsubstr(locatorName, "protector" , 0) != -1 && iNation != PIRATE) 
			{
				chr.protector = true;
				chr.greeting = "protector";
			}
			else 
			{
				//Экку Korsar - что-бы пираты звучали как пираты, а не солдаты. "Все вопросы к офицеру"... В пиратском поселении, блин.
				//chr.greeting = "soldier";
				if(chr.nation == PIRATE)
			    {
			        chr.greeting = "town_pirate";
			    }
			    else
			    {
			    	chr.greeting = "soldier";
			    }
		    }
			// <-- eddy. проверяем, должен ли солдат быть протектором
			
			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";
			
			LAi_SetGuardianType(chr);

            if (sti(Colonies[iColony].HeroOwn) == true)
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				chr.greeting = "town_pirate";
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
			}
		}
	}
	// солдаты <--
	// патруль -->
	if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.patrol"))
	{
		makearef(st, loc.locators.patrol);
		iCitizensQuantity = GetAttributesNum(st);
		if(iCitizensQuantity > 5)
		{
			iCitizensQuantity = 5;
		}
		for (i=0; i<iCitizensQuantity-2; i++)
		{
			if(iNation != PIRATE && LAi_IsCapturedLocation == 0)
			{
                sType = "soldier";
				iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
			}
			else
			{
                sType = "pirate";
				iChar = NPC_GeneratePhantomCharacter("pirate", iNation, MAN, 2);
			}
			chr = &characters[iChar];
			SetNPCModelUniq(chr, sType, MAN);
			chr.City = Colonies[iColony].id;
            chr.CityType = "soldier";
            SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
			chr.RebirthPhantom = true; 
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //задаем шаг на увеличение ранга фантомам на реинкарнацию
			LAi_SetLoginTime(chr, 0.0, 24.0);
			
			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";

			LAi_SetPatrolType(chr);
			
            if (sti(Colonies[iColony].HeroOwn) == true)
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				chr.greeting = "town_pirate";
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
				//chr.greeting = "soldier";
				if(chr.nation == PIRATE)
			    {
			        chr.greeting = "town_pirate";
			    }
			    else
			    {
			    	chr.greeting = "soldier";
			    }
			}
			PlaceCharacter(chr, "patrol", "random_free");
		}
		//мушкетеры
		for (i=1; i<=2; i++)
		{
			if(iNation == PIRATE)
			{
                sType = "mush_ctz_" + (rand(2)+7);
			}
			else
			{
                sType = "mush_" + NationShortName(iNation) + "_" + i;
			}
			chr = GetCharacter(NPC_GenerateCharacter("GenChar_", sType, "man", "mushketer", sti(pchar.rank), iNation, 2, false, "soldier"));
			chr.id = "GenChar_" + chr.index;	
			chr.reputation = (1 + rand(44) + rand(44));// репа всем горожанам
			chr.City = Colonies[iColony].id;
            chr.CityType = "soldier";
			chr.greeting = "soldier";
			chr.RebirthPhantom = true; 
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //задаем шаг на увеличение ранга фантомам на реинкарнацию
            SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
			LAi_SetLoginTime(chr, 0.0, 24.0); //а ночью будет беготня от патруля :)

			PlaceCharacter(chr, "patrol", "random_free");

			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";				

			LAi_SetPatrolType(chr);
			
            if (sti(Colonies[iColony].HeroOwn) == true)
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				chr.greeting = "town_pirate";
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
				//Экку Korsar - что-бы пираты звучали как пираты, а не солдаты. "Все вопросы к офицеру"... В пиратском поселении, блин.
				//chr.greeting = "soldier";
				if(chr.nation == PIRATE)
			    {
			        chr.greeting = "town_pirate";
			    }
			    else
			    {
			    	chr.greeting = "soldier";
			    }
			}
		}
	}
	// патруль <--
	// грузчики -->
	if (loc.type == "town" && CheckAttribute(loc, "carrier") && IsLoginTime())
	{
		int iTemp;
		int iQtyCarrier = rand(2) + 2;
		string locReload[7];
		locReload[0] = "reload4_back";
		locReload[1] = "reload5_back";
		locReload[2] = "reload6_back";
		locReload[3] = "reload7_back";
		locReload[4] = "reload8_back";
		locReload[5] = "reload10_back";
		locReload[6] = "reload9_back";
		string CarrierName[10];
		CarrierName[0] = "GenresBag1";
		CarrierName[1] = "GenresBag2";
		CarrierName[2] = "GenresBarrel1";
		CarrierName[3] = "GenresBarrel2";
		CarrierName[4] = "GenresBarrelTop1";
		CarrierName[5] = "GenresBarrelTop2";
		CarrierName[6] = "GenresBottle1";
		CarrierName[7] = "GenresBottle2";
		CarrierName[8] = "GenresChest1";
		CarrierName[9] = "GenresChest2";
		for (i=iQtyCarrier; i>0; i--)
		{
			//выберем уникальную для этой локации модельку
			iSex = 1;
			while (iSex == 1)
			{
				iTemp = rand(9);
				if (CarrierName[iTemp] != "") iSex = 0;
			}
			chr = GetCharacter(NPC_GenerateCharacter("Carrier", CarrierName[iTemp], "man", "genres", 35, iNation, 2, false, "citizen"));
			chr.id = chr.id + "_" + chr.index;
			aref aLocator;
			makearef(aLocator, loc.locators.reload);
			CarrierName[iTemp] = ""; //имя модельки уберем из списка
			LAi_SetImmortal(chr, true);
			LAi_SetLoginTime(chr, 7.0, 20.0);
			iSex = 1;
			while (iSex == 1)
			{
				iTemp = rand(6);
				if (CheckAttribute(aLocator, locReload[iTemp]) && locReload[iTemp] != "")
				{
					chr.firstLoc = locReload[iTemp];
					chr.firstLoc.timer = frand(7) + 4.0;
					locReload[iTemp] = "";
					iSex = 0;
				}
			}
			ChangeCharacterAddressGroup(chr, loc.id, "reload", "gate");
			LAi_SetCarrierType(chr);
			LAi_group_MoveCharacter(chr, slai_group);
		}
	}
	// грузчики <--
	
	// belamour cle рыбаки -->
	if(CheckAttribute(loc,"locators.fisher"))
	{
		aref locatorGroup;
		makearef(locatorGroup, loc.locators.fisher);
		iSailorQty = GetAttributesNum(locatorGroup);
		for (i = 1; i <= iSailorQty; i++)
		{
			sType = "sailor";
			iChar = NPC_GeneratePhantomCharacter(sType, iNation, MAN, 2);
			chr = &characters[iChar];
			chr.model.animation = "fisher";
			sType = "fisher";
			SetNPCModelUniq(chr, sType, MAN);
			if(!HasSubStr(chr.model, "fisherman")) chr.model = "fisherman_"+sti(rand(10)+1);
			chr.City = Colonies[iColony].id;
			RemoveAllCharacterItems(chr, true);
			chr.CityType = sType;
			chr.chr_ai.hp_max = 1;
			chr.chr_ai.hp = 1;
            chr.Unpushable = "";
			ChangeCharacterAddressGroup(chr, loc.id, "fisher", "fisher"+i);
			LAi_SetLoginTime(chr, 6.0, 15.99);
			LAi_SetFisherSitType(chr);
			if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
		}
	}
	
	//рыбачит стоя 
	if(CheckAttribute(loc,"locators.fisherstay"))
	{
		makearef(locatorGroup, loc.locators.fisherstay);
		iSailorQty = GetAttributesNum(locatorGroup);
		for (i = 1; i <= iSailorQty; i++)
		{
			sType = "sailor";
			iChar = NPC_GeneratePhantomCharacter(sType, iNation, MAN, 2);
			chr = &characters[iChar];
			chr.model.animation = "fisher";
			sType = "fisher";
			SetNPCModelUniq(chr, sType, MAN);
			if(!HasSubStr(chr.model, "fisherman")) chr.model = "fisherman_"+sti(rand(10)+1);
			chr.City = Colonies[iColony].id;
			RemoveAllCharacterItems(chr, true);
			chr.CityType = sType;
			chr.chr_ai.hp_max = 1;
			chr.chr_ai.hp = 1;
            chr.Unpushable = "";
			ChangeCharacterAddressGroup(chr, loc.id, "fisherstay", "fisherstay"+i);
			LAi_SetLoginTime(chr, 6.0, 15.99);
			LAi_SetFisherStayType(chr);
			if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
		}
	}
	// <--
	
	// сидящие на лавочках
	if(CheckAttribute(loc,"locators.benchsit"))
	{
		makearef(locatorGroup, loc.locators.benchsit);
		iSailorQty = GetAttributesNum(locatorGroup);
		for (i = 1; i <= iSailorQty; i++)
		{
			
				iSex = rand(WOMAN);
				sType = "citizen";
				iChar = NPC_GeneratePhantomCharacter("citizen", iNation, iSex, 2);
				chr = &characters[iChar];
				if(iSex == WOMAN) chr.model.animation = "woman";
					else chr.model.animation = "man";
				SetNPCModelUniq(chr, sType, iSex);
				if(iSex == WOMAN)
				{
					switch (rand(13))
					{
						case 0: chr.model = "Girl_1"; break;
						case 1: chr.model = "Girl_2"; break;
						case 2: chr.model = "Girl_3"; break;
						case 3: chr.model = "Girl_4"; break;
						case 4: chr.model = "Girl_5"; break;
						case 5: chr.model = "Girl_8"; break;
						case 6: chr.model = "Women_9"; break;
						case 7: chr.model = "Women_10"; break;
						case 8: chr.model = "Women_12"; break;
						case 9: chr.model = "Women_13"; break;
						case 10: chr.model = "Women_14"; break;
						case 11: chr.model = "Women_15"; break;
						case 12: chr.model = "Women_16"; break;
						case 13: chr.model = "Women_18"; break;
					}
					int k = 0;
					while (!CheckNPCModelUniq(chr) && k < 10)
					{
						k++;
						switch (rand(13))
						{
							case 0: chr.model = "Girl_1"; break;
							case 1: chr.model = "Girl_2"; break;
							case 2: chr.model = "Girl_3"; break;
							case 3: chr.model = "Girl_4"; break;
							case 4: chr.model = "Girl_5"; break;
							case 5: chr.model = "Girl_8"; break;
							case 6: chr.model = "Women_9"; break;
							case 7: chr.model = "Women_10"; break;
							case 8: chr.model = "Women_12"; break;
							case 9: chr.model = "Women_13"; break;
							case 10: chr.model = "Women_14"; break;
							case 11: chr.model = "Women_15"; break;
							case 12: chr.model = "Women_16"; break;
							case 13: chr.model = "Women_18"; break;
						}
					}
					arrayNPCModel[arrayNPCModelHow] = chr.model;
					arrayNPCModelHow++;
				}
				else
				{
					if(rand(3) == 2)
					{
						k = 0;
						while (!CheckNPCModelUniq(chr) && k < 10)
						{
							k++;
							chr.model = "drinker_"+sti(rand(15)+1)
						}
					}
				}
				chr.City = Colonies[iColony].id;
				RemoveAllCharacterItems(chr, true);
				chr.CityType = "citizen";
				chr.chr_ai.hp_max = 1;
				chr.chr_ai.hp = 1;
                chr.Unpushable = "";
				if(HasSubStr(chr.model, "drinker"))
				{
					LAi_SetDrinkerSitBenchType(chr);
					LAi_SetLoginTime(chr, 18.30, 23.99);
				}
				else
				{
					LAi_SetBenchSitType(chr);
					LAi_SetLoginTime(chr, 10.0, 17.99);
				}
				ChangeCharacterAddressGroup(chr, loc.id, "benchsit", "benchsit"+i);
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				//chr.dialog.currentnode = "first time";
		}
	}
	
	//кузнец
	if(CheckAttribute(loc,"locators.blacksmith"))
	{
		makearef(locatorGroup, loc.locators.blacksmith);
		iSailorQty = GetAttributesNum(locatorGroup);
		for (i = 1; i <= iSailorQty; i++)
		{
			sType = "sailor";
			iChar = NPC_GeneratePhantomCharacter(sType, iNation, MAN, 2);
			chr = &characters[iChar];
			chr.model.animation = "blacksmith";
			chr.model = "blacksmith_"+sti(rand(17)+1);
			chr.City = Colonies[iColony].id;
			RemoveAllCharacterItems(chr, true);
			chr.CityType = sType;
			chr.chr_ai.hp_max = 1;
			chr.chr_ai.hp = 1;
            chr.Unpushable = "";
			LAi_SetLoginTime(chr, 10.0, 17.99);
			LAi_SetBlacksmithType(chr);
			ChangeCharacterAddressGroup(chr, loc.id, "blacksmith", "blacksmith"+i);
			chr.chr_ai.disableDlg = 1;
			if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
		}
	}
	
	// сидящие пьяницы
	if(CheckAttribute(loc,"locators.drinkersit"))
	{
		makearef(locatorGroup, loc.locators.drinkersit);
		iSailorQty = GetAttributesNum(locatorGroup);
		for (i = 1; i <= iSailorQty; i++)
		{
				sType = "citizen";
				iChar = NPC_GeneratePhantomCharacter("citizen", iNation, MAN, 2);
				chr = &characters[iChar];
				chr.model.animation = "man";
				chr.model = "drinker_"+sti(rand(15)+1));
				
				k = 0;
				while (!CheckNPCModelUniq(chr) && k < 10)
				{
					k++;
					chr.model = "drinker_"+sti(rand(15)+1));
				}
					arrayNPCModel[arrayNPCModelHow] = chr.model;
					arrayNPCModelHow++;
				chr.City = Colonies[iColony].id;
				RemoveAllCharacterItems(chr, true);
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 18.29, 23.99);
				chr.chr_ai.hp_max = 1;
				chr.chr_ai.hp = 1;
                chr.Unpushable = "";
				LAi_SetDrinkerSitType(chr);
				ChangeCharacterAddressGroup(chr, loc.id, "drinkersit", "drinkersit"+i);
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				//chr.dialog.currentnode = "first time";
		}
	}
	
	// стоящие пьяницы
	if(CheckAttribute(loc,"locators.drinkerstay"))
	{
		makearef(locatorGroup, loc.locators.drinkerstay);
		iSailorQty = GetAttributesNum(locatorGroup);
		for (i = 1; i <= iSailorQty; i++)
		{
				sType = "citizen";
				iChar = NPC_GeneratePhantomCharacter("citizen", iNation, MAN, 2);
				chr = &characters[iChar];
				chr.model.animation = "man";
				chr.model = "drinker_"+sti(rand(15)+1));
				
				k = 0;
				while (!CheckNPCModelUniq(chr) && k < 10)
				{
					k++;
					chr.model = "drinker_"+sti(rand(15)+1));
				}
					arrayNPCModel[arrayNPCModelHow] = chr.model;
					arrayNPCModelHow++;
				chr.City = Colonies[iColony].id;
				RemoveAllCharacterItems(chr, true);
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 18.29, 23.99);
				chr.chr_ai.hp_max = 1;
				chr.chr_ai.hp = 1;
                chr.Unpushable = "";
				LAi_SetDrinkerStayType(chr);
				ChangeCharacterAddressGroup(chr, loc.id, "drinkerstay", "drinkerstay"+i);
				if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				//chr.dialog.currentnode = "first time";
		}
	}
	
	// belamour legendary edition дополнительный народ в новом Виллемстаде -->
	if(loc.id == "villemstad_town")
	{
		if(rand(9) > 1) sType = "sailor"; 
		else sType = "pirate";
		// пока что занимаем все места, потом посмотрим и сделаем на rand
		iSailorQty = 3;
		if(iSailorQty > 0) // матросы(контрики) у костра
		{
			for(i=1; i<=iSailorQty; i++)
			{
				iChar = NPC_GeneratePhantomCharacter(sType, HOLLAND, MAN, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, MAN);
				chr.City = Colonies[iColony].id;
				if(sType =="sailor")
				{
					chr.CityType = "sailor";
					chr.greeting = "town_sailor";
					chr.dialog.filename = "Population\sailor.c";
				}
				else
				{
					chr.CityType = "marginal";
					chr.greeting = "marginal";
					chr.dialog.filename = "Population\Marginal.c";
				}
				chr.dialog.currentnode = "first time";
				//LAi_SetLoginTime(chr, 20.0, 7.99);
				ChangeCharacterAddressGroup(chr, "villemstad_town", "sit", "fire1_"+i);
				LAi_SetGroundSitTypeNoGroup(chr);
			}
		}
		iSailorQty = 1;
		if(iSailorQty > 0) // матрос(контрик) под навесом
		{
			for(i=1; i<=iSailorQty; i++)
			{
				iChar = NPC_GeneratePhantomCharacter(sType, HOLLAND, MAN, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, MAN);
				chr.City = Colonies[iColony].id;
				if(sType =="sailor")
				{
					chr.CityType = "sailor";
					chr.greeting = "town_sailor";
					chr.dialog.filename = "Population\sailor.c";
				}
				else
				{
					chr.CityType = "marginal";
					chr.greeting = "marginal";
					chr.dialog.filename = "Population\Marginal.c";
				}
				chr.dialog.currentnode = "first time";
				//LAi_SetLoginTime(chr, 20.0, 7.99);
				ChangeCharacterAddressGroup(chr, "villemstad_town", "sit", "fire2_"+i);
				LAi_SetGroundSitTypeNoGroup(chr);
			}
		}
		iSailorQty = 2;
		if(iSailorQty > 0) // матросы у моря
		{
			for(i=1; i<=iSailorQty; i++)
			{
				sType = "sailor";
				iChar = NPC_GeneratePhantomCharacter("sailor", HOLLAND, MAN, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, MAN);
				chr.City = Colonies[iColony].id;
				chr.CityType = "sailor";
				chr.greeting = "town_sailor";
				chr.dialog.filename    = "Population\sailor.c";
				chr.dialog.currentnode = "first time";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				ChangeCharacterAddressGroup(chr, "villemstad_town", "sit", "fire3_"+i);
				LAi_SetGroundSitTypeNoGroup(chr);
			}
		}
		// кэп(горожанин) гуляет и облокачивается на перила
		sType = RandPhraseSimple("citizen","Captain");
		iChar = NPC_GeneratePhantomCharacter(sType, HOLLAND, MAN, 2);
		chr = &characters[iChar];
		SetNPCModelUniq(chr, sType, MAN);
		chr.City = Colonies[iColony].id;
		chr.CityType = sType;
		chr.TownBar = true;
		if(sType == "citizen") 
		{
			chr.dialog.filename = "Population\Townman.c";
			chr.greeting = "citizen_male";
		}
		else 
		{
			chr.dialog.filename = "Population\Captain.c";
			chr.greeting = "captain";
		}
		chr.dialog.currentnode = "first time";
		LAi_SetLoginTime(chr, 6.0, 21.99);
		ChangeCharacterAddressGroup(chr, "villemstad_town", "barmen", "stay");
		LAi_SetBarmanType(chr);
		
		// горожанин рядом с продавцом
		iCitizQty = 1;
		if(iCitizQty > 0)
		{
			iChar = NPC_GeneratePhantomCharacter("citizen", HOLLAND, MAN, 2);
			chr = &characters[iChar];
			SetNPCModelUniq(chr, "citizen", MAN);
			chr.City = Colonies[iColony].id;
			chr.CityType = "citizen";
			chr.dialog.filename = "Population\Townman.c";
			chr.greeting = "citizen_male";
			chr.dialog.currentnode = "first time";
			LAi_SetLoginTime(chr, 6.0, 21.99);
			ChangeCharacterAddressGroup(chr, "villemstad_town", "sit", "sit1");
			LAi_SetSitType(chr);
		}
		// столик во внутреннем дворике
		sType = RandPhraseSimple("citizen","sailor");
		iChar = NPC_GeneratePhantomCharacter(sType, HOLLAND, MAN, 1);
		chr = &characters[iChar];
		SetNPCModelUniq(chr, sType, MAN);
		chr.City = Colonies[iColony].id;
		if(sType =="sailor") chr.dialog.filename = "Population\sailor.c";
		else chr.dialog.filename = "Population\Townman.c";
		chr.CityType = sType;	
		chr.greeting = "habitue";
		chr.dialog.currentnode = "first time";
		LAi_SetLoginTime(chr, 10.0, 01.99);
		ChangeCharacterAddressGroup(chr, "villemstad_town", "sit", "sit_front1");
		LAi_SetSitType(chr);
		
		
		sType = RandPhraseSimple("citizen","sailor");
		iChar = NPC_GeneratePhantomCharacter(sType, HOLLAND, MAN, 1);
		chr = &characters[iChar];
		SetNPCModelUniq(chr, sType, MAN);
		chr.City = Colonies[iColony].id;
		if(sType =="sailor") chr.dialog.filename = "Population\sailor.c";
		else chr.dialog.filename = "Population\Townman.c";
		chr.CityType = sType;	
		chr.greeting = "habitue";
		chr.dialog.currentnode = "first time";
		LAi_SetLoginTime(chr, 10.0, 01.99);
		ChangeCharacterAddressGroup(chr, "villemstad_town", "sit", "sit_front2");
		LAi_SetSitType(chr);
		
		sType = RandPhraseSimple("citizen","sailor");
		iChar = NPC_GeneratePhantomCharacter(sType, HOLLAND, MAN, 1);
		chr = &characters[iChar];
		SetNPCModelUniq(chr, sType, MAN);
		chr.City = Colonies[iColony].id;
		if(sType =="sailor") chr.dialog.filename = "Population\sailor.c";
		else chr.dialog.filename = "Population\Townman.c";
		chr.CityType = sType;	
		chr.greeting = "habitue";
		chr.dialog.currentnode = "first time";
		LAi_SetLoginTime(chr, 10.0, 01.99);
		ChangeCharacterAddressGroup(chr, "villemstad_town", "sit", "sit_base1");
		LAi_SetSitType(chr);
		
		sType = RandPhraseSimple("citizen","sailor");
		iChar = NPC_GeneratePhantomCharacter(sType, HOLLAND, MAN, 1);
		chr = &characters[iChar];
		SetNPCModelUniq(chr, sType, MAN);
		chr.City = Colonies[iColony].id;
		if(sType =="sailor") chr.dialog.filename = "Population\sailor.c";
		else chr.dialog.filename = "Population\Townman.c";
		chr.CityType = sType;	
		chr.greeting = "habitue";
		chr.dialog.currentnode = "first time";
		LAi_SetLoginTime(chr, 10.0, 01.99);
		ChangeCharacterAddressGroup(chr, "villemstad_town", "sit", "sit_base2");
		LAi_SetSitType(chr);
	}
}

void CreateIslatesoroEng(aref loc)//Jason, Исла Тесоро при провале Саги
{
	if (loc.id == "Pirates_town" && CheckAttribute(loc, "EngBase"))
	{
		int iNation = -1;
		iNation = GetCityNation(loc.fastreload);
		if(iNation == -1) return;
		if(iNation != ENGLAND) return;
		int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
		// протекторы -->
		for (i=1; i<=4; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Eng_IT_Prot_"+i, "sold_eng_"+(rand(5)+1), "man", "man", iRank, ENGLAND, 1, false, "soldier"));
			SetFantomParamFromRank(sld, iRank, true);
			sld.dialog.Filename = "Common_Soldier.c";
			sld.dialog.currentnode = "first time";
			sld.greeting = "soldier"; 
			sld.RebirthPhantom = true; 
			LAi_CharacterReincarnation(sld, true, true);
			LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
			ChangeCharacterAddressGroup(sld, "Pirates_town", "soldiers", "soldier"+i);
			LAi_SetLoginTime(sld, 6.0, 23.0);
			if (i < 3) 
			{
				sld.protector = true;
				sld.protector.CheckAlways = true; //проверять всегда
				sld.greeting = "protector"; 
			}
			LAi_SetGuardianType(sld);
			LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
		}
		// патрульные
		for (i=1; i<=10; i++)
		{
			if (i < 8)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Eng_IT_Sold_"+i, "sold_eng_"+(rand(5)+1), "man", "man", iRank, ENGLAND, 1, false, "soldier"));
				SetFantomParamFromRank(sld, iRank, true);
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Eng_IT_Sold_"+i, "mush_eng_"+(rand(4)+1), "man", "mushketer", iRank, ENGLAND, 1, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, 70, 70, "", "mushket1", "bullet", 100);
			}
			sld.dialog.Filename = "Common_Soldier.c";
			sld.dialog.currentnode = "first time";
			sld.greeting = "soldier"; 
			sld.RebirthPhantom = true; 
			LAi_CharacterReincarnation(sld, true, true);
			LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
			LAi_CharacterReincarnation(sld, true, true);
			LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
			ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto"+i);
			LAi_SetLoginTime(sld, 0.0, 24.0);
			sld.city = "Pirates";
			sld.citytype = "soldier";
			LAi_SetPatrolType(sld);
			LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
		}
	}
}

// плодим завсегдатеев в таверну, тоже фантомы-многоджневки (24ч) переработка boal 13.05.06
void CreateHabitues(aref loc)
{
	int iColony = -1;
	int iNation = -1;
	
	bool generateAffairOfHonor = true;
	if (!checkAttribute(loc, "habitues")) return;
	if(LAi_IsCapturedLocation) return;
	if (CheckAttribute(pchar, "questTemp.Mtraxx.InTavern") && loc.id == "LaVega_tavern") return; // Addon 2016-1 Jason Пиратская линейка
	if (CheckAttribute(pchar, "questTemp.LongHappy.InTavern") && loc.id == "Pirates_tavern") return; // Jason Долго и счастливо
	if (CheckAttribute(pchar, "questTemp.HelenDrinking.InTavern")) return;
	if(loc.id == "islamona_town") return;
	OfficersReactionResult(); // уход офов в местах, где есть пьянь и др офы - пока это таверна

	if (!isLocationHasCitizens(loc.id))  // boal  если есть ещё с того раза, но не нужно
	{
		if (CheckAttribute(loc, "fastreload"))
		{
			iColony = FindColony(loc.fastreload);

			if(iColony == -1)
			{
				return;
			}

			iNation = GetCityNation(loc.fastreload);

			if (iNation == -1)
			{
				return;
			}

			string sColony = loc.fastreload;
			int iCitizensQuantity, iModel;
			ref chr;
		    string slai_group;
			int iChar;
			int i, n, k;
			string sTemp;

			slai_group = GetNationNameByType(iNation)  + "_citizens";

            arrayNPCModelHow = 0;
			if (pchar.location == "LosTeques_tavern")
			{
				for (i=1; i <=rand(2)+1; i++)
				{
					if (CheckFreeLocator(loc.id, "sit_base" + i, -1))
					{
						iChar = NPC_GeneratePhantomCharacter("spa_soldier", iNation, MAN, 1);
						chr = &characters[iChar];
						SetNPCModelUniq(chr, "spa_soldier", MAN);
						chr.City = Colonies[iColony].id;
						chr.CityType = "citizen";
						ChangeCharacterAddressGroup(chr, loc.id, "sit", "sit_base" + i);
						chr.Default           = loc.id;
						chr.Default.group     = "sit";
						chr.Default.ToLocator = "sit_front" + i;
						LAi_SetLoginTime(chr, 0.0, 24.0);
						LAi_SetSitType(chr);
						if (sti(Colonies[iColony].HeroOwn) == true)
						{
							LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
						}
						else
						{
							LAi_group_MoveCharacter(chr, slai_group);
						}
						chr.quest.last_theme = 0;
						chr.dialog.filename = "Habitue_dialog.c";
						chr.dialog.currentnode = "first time";
						chr.greeting = "habitue";
					}
				}
				for (i=0; i<=rand(2); i++)
				{
				    iChar = NPC_GeneratePhantomCharacter("spa_soldier", iNation, MAN, 1);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, "spa_soldier", MAN);
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					sTemp = PlaceCharacter(chr, "sit", "random_free"); // может не быть вовсе, если все места заняты
                    ReSitCharacterOnFree(chr, loc.id, sTemp);

					LAi_SetLoginTime(chr, 0.0 + rand(6), 24.0 - rand(10));
					LAi_SetSitType(chr);
					if (sti(Colonies[iColony].HeroOwn) == true)
					{
						LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					}
					else
					{
						LAi_group_MoveCharacter(chr, slai_group);
					}
					chr.quest.last_theme = 0;
					chr.dialog.filename = "Habitue_dialog.c";
					chr.dialog.currentnode = "first time";
					chr.greeting = "habitue";
				}
				return;
			}

			 //Jason --> квестовые кэпы - 33%, отберем одно место для выпивки у пьяниц
			if (rand(11) < 4 && loc.id != "Panama_tavern" && !CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{ // 170712
				i = rand(3)+1;
				if (CheckFreeLocator(loc.id, "sit_base"+i, -1))
				{
					iChar = NPC_GeneratePhantomCharacter("trader", iNation, MAN, 1);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, "trader", MAN);
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					ChangeCharacterAddressGroup(chr, loc.id, "sit", "sit_base"+i);
					chr.Default           = loc.id;
					chr.Default.group     = "sit";
					chr.Default.ToLocator = "sit_front"+i;
					LAi_SetSitType(chr);
					LAi_group_MoveCharacter(chr, slai_group);
					chr.dialog.filename = "Quest\QuestTrader_dialog.c";
					chr.dialog.currentnode = "first time";
					chr.greeting = "captain_trader";
					if (sti(Colonies[iColony].HeroOwn) == true)
					{
						LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					}
					else
					{
						LAi_group_MoveCharacter(chr, slai_group);
					}
				}
			}
			//<-- квестовые кэпы
			
			// belamour квест пьяный матрос -->
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Lock") && CheckAttribute(pchar, "GenQuest.GuiltySailor") 
			&& sti(pchar.reputation.fame) > 60 && loc.id != "Panama_tavern" && GetCharacterShipClass(pchar) < 3)
			{ 
				log_testinfo("Сгенерировался квест: Пьяный матрос");
				i = rand(3)+1;
				if (CheckFreeLocator(loc.id, "sit_base"+i, -1))
				{   
					string sHeroNation = GetBaseHeroNation(); 
					string sModelGS = "sailor"; // модель морячка по умолчанию
					if(CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) sModelGS = "pirate"; // для Чарли Принца
					if(CheckAttribute(pchar, "questTemp.CharleePrince")) sModelGS = "pirate"; // для Чарли Принца
					iChar = NPC_GeneratePhantomCharacter(sModelGS, sHeroNation, MAN, 1);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, sModelGS, MAN);
					if(isMainCharacterPatented()) // На службе у нации
					{
						chr.model = "sold_" + NationShortName(sti(chr.nation)) + "_" + (1 + rand(7));
						FaceMaker(chr);
						CirassMaker(chr);
						Characters_RefreshModel(chr); 
					}
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					ChangeCharacterAddressGroup(chr, loc.id, "sit", "sit_base"+i);
					chr.Default           = loc.id;
					chr.Default.group     = "sit";
					chr.Default.ToLocator = "sit_front"+i;
					LAi_SetSitType(chr);
					LAi_group_MoveCharacter(chr, slai_group);
					chr.dialog.filename = "GenQuests_Dialog.c";
					chr.dialog.currentnode = "GuiltySailor";
					chr.greeting = "habitue";
					if (sti(Colonies[iColony].HeroOwn) == true)
					{
						LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					}
					else
					{
						LAi_group_MoveCharacter(chr, slai_group);
					}
				}
				DeleteAttribute(pchar, "GenQuest.GuiltySailor"); 
				SetFunctionTimerCondition("GuiltySailor_NextQ", 0, 0, 45+rand(15), false);
				
			}
			// <-- квест пьяный матрос
			
			// belamour хороший специалист -->
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Lock") && CheckAttribute(pchar, "GenQuest.ExpertSailor") && loc.id != "Panama_tavern")
			{ 
				log_testinfo("Сгенерировался квест: Хороший специалист");
				i = rand(3)+1;
				if(CheckFreeLocator(loc.id, "sit_base"+i, -1))
				{   
					iChar = NPC_GeneratePhantomCharacter("sailor", sHeroNation, MAN, 1);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, "sailor", MAN);
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					ChangeCharacterAddressGroup(chr, loc.id, "sit", "sit_base"+i);
					chr.Default           = loc.id;
					chr.Default.group     = "sit";
					chr.Default.ToLocator = "sit_front"+i;
					LAi_SetSitType(chr);
					LAi_group_MoveCharacter(chr, slai_group);
					chr.dialog.filename = "GenQuests_Dialog.c";
					chr.dialog.currentnode = "ExpertSailor";
					chr.greeting = "town_sailor";
					if (sti(Colonies[iColony].HeroOwn) == true)
					{
						LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					}
					else
					{
						LAi_group_MoveCharacter(chr, slai_group);
					}
				}
				DeleteAttribute(pchar, "GenQuest.ExpertSailor"); 
				SetFunctionTimerCondition("ExpertSailor_NextQuest", 0, 0, 25+rand(5), false);
			}
			// <-- хороший специалист
			
			// сажаем пьянь, на козырные места под ГГ
			for (i = 1; i <=4; i++)
			{
                if (CheckFreeLocator(loc.id, "sit_base" + i, -1))
				{
					string sType = RandPhraseSimple("citizen","sailor");
					if (Colonies[iColony].nation == PIRATE) sType = RandPhraseSimple("pirate","sailor");
					iChar = NPC_GeneratePhantomCharacter(sType, iNation, MAN, 1);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, sType, MAN);
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					ChangeCharacterAddressGroup(chr, loc.id, "sit", "sit_base" + i);
					chr.Default           = loc.id;
					chr.Default.group     = "sit";
					chr.Default.ToLocator = "sit_front" + i;
					LAi_SetLoginTime(chr, 0.0, 24.0);
					LAi_SetSitType(chr);
					if (sti(Colonies[iColony].HeroOwn) == true)
					{
						LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					}
					else
					{
						LAi_group_MoveCharacter(chr, slai_group);
					}
					chr.quest.last_theme = rand(1);
					chr.quest.last_theme_game = rand(1);
					chr.dialog.filename = "Habitue_dialog.c";
					chr.dialog.currentnode = "first time";
					if (chr.quest.last_theme == 0) chr.greeting = "habitue"; // пьянтос
					else chr.greeting = "player"; // игрок
					
					// Warship, 30.05.11. "Дело чести" -->
					// belamour legendary edition встречается значительно чаще
					bool bAh = (hrand(4, loc.id) == 4) && (!CheckAttribute(pchar, "questTemp.Sharlie.Lock")) && (!CheckAttribute(pchar, "GenQuest.Escort.Trader"))
					if(bAh || bBettaTestMode)
					{
						if(generateAffairOfHonor && IsDay())
						{
							pchar.questTemp.AffairOfHonor.LighthouseId = Colony_GetLighthouseId(loc.fastreload);
							
							if(chr.City != "PortRoyal" && chr.City != "FortOrange" && PChar.QuestTemp.AffairOfHonor.LighthouseId != "" && AffairOfHonor_GetCurQuest() == "")
							{
								if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor") && GetCharacterIndex("AffairOfHonor_QuestMan") == -1)
								{
									chr.id = "AffairOfHonor_QuestMan";
									chr.dialog.filename = "Quest\ForAll_dialog.c";
									chr.dialog.currentnode = "AffairOfHonor_1";
									LAi_SetImmortal(chr, true);
									SetRandNationSoldierModel(chr);
									Characters_RefreshModel(chr); // Jason: рефрешить модель обязательно
									generateAffairOfHonor = false; // Чтобы по двести раз не генерило квестодателей.
									Log_TestInfo("Сгенерилось дело чести");
								}
							}
						}
					}
					// <--
				}
			}
			// belamour legendary edition локаторы на полу (таверна7)
			if(loc.filespath.models == "locations\inside\tavern07\")
			{
				for (i = 1; i <=5; i++)
				{
					if (CheckFreeLocator(loc.id, "sit_ground" + i, -1))
					{
						if(IsDay() && rand(10) > 0 ) continue;
						else 
						{
							if(rand(10) > 2) continue;
						}
						sType = RandPhraseSimple("citizen","sailor");
						if (Colonies[iColony].nation == PIRATE) sType = RandPhraseSimple("pirate","sailor");
						iChar = NPC_GeneratePhantomCharacter(sType, iNation, MAN, 1);
						chr = &characters[iChar];
						SetNPCModelUniq(chr, sType, MAN);
						chr.City = Colonies[iColony].id;
						chr.CityType = "citizen";
						ChangeCharacterAddressGroup(chr, loc.id, "sit", "sit_ground" + i);
						chr.Default           = loc.id;
						chr.Default.group     = "sit";
						chr.Default.ToLocator = "sit_ground" + i;
						LAi_SetLoginTime(chr, 0.0, 24.0);
						LAi_SetGroundSitType(chr);
						if (sti(Colonies[iColony].HeroOwn) == true)
						{
							LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
						}
						else
						{
							LAi_group_MoveCharacter(chr, slai_group);
						}
						chr.dialog.filename = "Habitue_dialog.c";
						chr.dialog.currentnode = "first time";
						chr.greeting = "habitue"; // пьянтос
					}
				}
			}
			iChar = GetCharacterIndex(Colonies[iColony].id + "_Smuggler");
			if (iChar != -1) // у пиратов нет вообще - это статики
			{
		        chr = &characters[iChar];
				if (sti(Colonies[iColony].HeroOwn) != true)
				{ // грузим контрикова агента, он статик, но локацию и локатор ставим тут
		            chr.City = Colonies[iColony].id;  // это можно прописать в статике, но мне лениво по 20 городам лазить.
		            chr.nation = iNation; // нация его нужна, тк она будет нацией патруля на берегу, он не пират
					CreateModel(iChar, "pirate", MAN);
					sTemp = PlaceCharacter(chr, "sit", "random_free");
					ReSitCharacterOnFree(chr, loc.id, sTemp);
					LAi_group_MoveCharacter(chr, slai_group);
				}
				else
				{
				    ChangeCharacterAddressGroup(chr, "none", "none", "none");
				}
				// вне группы
			}
			// офицеры -->
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))//не идёт старт квеста Шарля
			{
				iCitizensQuantity = rand(8)-6;
				if(CheckCharacterPerk(pchar, "Trustworthy")) iCitizensQuantity += 4;
				if(iCitizensQuantity > 3) iCitizensQuantity = 3;
				if(CheckAttribute(pchar, "cheats.lai_officers")) iCitizensQuantity = 2;
				for (i = 0; i <iCitizensQuantity; i++)
				{
					iChar = NPC_GeneratePhantomCharacter("pofficer", iNation, MAN, 1);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, "pofficer", MAN);
					SetOfficerParam(chr, rand(4));
					sTemp = PlaceCharacter(chr, "sit", "random_free");
					ReSitCharacterOnFree(chr, loc.id, sTemp);

					LAi_SetSitType(chr);
					// без группы
					chr.dialog.filename = "Enc_Officer_dialog.c";
					chr.dialog.currentnode = "first time";
					chr.greeting = "officer_hire";
					if (sti(Colonies[iColony].HeroOwn) == true)
					{
						LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					}
					else
					{
						LAi_group_MoveCharacter(chr, slai_group);
					}
				}
			}
			// офицеры <--
			// belamour legendary edition увеличить вероятность появления странной личности У Счетовода
			if(ShipBonus2Artefact(pchar, SHIP_LADYBETH))
			{
				if(CheckCharacterPerk(pchar, "HT2")) i = 3;
				else i = 7;
			}
			else
			{
				if(CheckCharacterPerk(pchar, "HT2")) i = 4;
				else i = 15;
			}
			if (rand(i) == 3 || TestRansackCaptain) // ugeen --> уменьшил вероятность встретить странную личность с картой до 1/20
			{ // карты кладов
                iChar = NPC_GeneratePhantomCharacter("pirate", iNation, MAN, 1);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, "pirate", MAN);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				sTemp = PlaceCharacter(chr, "sit", "random_free"); // может не быть вовсе, если все места заняты
				ReSitCharacterOnFree(chr, loc.id, sTemp);

				LAi_SetSitType(chr);
				LAi_group_MoveCharacter(chr, slai_group);
				chr.dialog.filename = "Enc_Treasure_dialog.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "map_trader";
				
		        if (GetCharacterItem(pchar, "map_full") == 0) // нет карты - генерим, если купит
		        {
		            aref item;
		            Items_FindItem("map_full", &item);
					FillMapForTreasure(item);
					//pchar.GenQuest.TreasureMoney = 5000 + rand(30)*500 + rand(30)*500;
					pchar.GenQuest.TreasureMoney = 100 + rand(50)*5; // Addon-2016 Jason
		        }
          		if (sti(Colonies[iColony].HeroOwn) == true)
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
				}
			}
			else
			{
				iCitizensQuantity = rand(3) - 1 ; // простая пьянь для антуражу
				for (i = 0; i <iCitizensQuantity; i++)
				{
				    iChar = NPC_GeneratePhantomCharacter(sType, iNation, MAN, 1);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, sType, MAN);
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					sTemp = PlaceCharacter(chr, "sit", "random_free"); // может не быть вовсе, если все места заняты
                    ReSitCharacterOnFree(chr, loc.id, sTemp);

					LAi_SetLoginTime(chr, 0.0 + rand(6), 24.0 - rand(10));
					LAi_SetSitType(chr);
					if (sti(Colonies[iColony].HeroOwn) == true)
					{
						LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					}
					else
					{
						LAi_group_MoveCharacter(chr, slai_group);
					}
					chr.quest.last_theme = 0;
					chr.dialog.filename = "Habitue_dialog.c";
					chr.dialog.currentnode = "first time";
					chr.greeting = "habitue";
				}
			}
			// музыканты
			if(CheckAttribute(loc,"locators.band"))
			{
				log_testinfo("Локаторы музыкантов доступны");
				aref locatorGroup;
				makearef(locatorGroup, loc.locators.band);
				iCitizensQuantity = GetAttributesNum(locatorGroup);
				log_testinfo("Локаторы музыкантов количество " +iCitizensQuantity);
				for (i = 1; i <= iCitizensQuantity; i++)
				{
					int iSex = rand(WOMAN);
					sType = "citizen";
					iChar = NPC_GeneratePhantomCharacter(sType, iNation, iSex, 1);
					chr = &characters[iChar];
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					if(iSex == WOMAN) 
					{
						if(rand(1) == 0) 
						{
							k = 0;
							chr.model = "woman_flutist_"+sti(rand(7)+1);
							while (!CheckNPCModelUniq(chr) && k < 10)
							{
								k++;
								chr.model = "woman_flutist_"+sti(rand(7)+1);
							}
							arrayNPCModel[arrayNPCModelHow] = chr.model;
							arrayNPCModelHow++;
							chr.model.animation = "woman_musician";
							if(rand(1) == 1) LAi_SetFlutistStayType(chr);
								else LAi_SetFlutistSitType(chr);
						}
						else 
						{
							k = 0;
							chr.model = "woman_violinist_"+sti(rand(3)+1);
							while (!CheckNPCModelUniq(chr) && k < 10)
							{
								k++;
								chr.model = "woman_violinist_"+sti(rand(3)+1);
							}
							arrayNPCModel[arrayNPCModelHow] = chr.model;
							arrayNPCModelHow++;
							chr.model.animation = "woman_musician";
							LAi_SetViolinistStayType(chr);
						}
					}
					else 
					{
						if(rand(1) == 0)
						{
							k = 0;
							chr.model = "flutist_"+sti(rand(11)+1);
							while (!CheckNPCModelUniq(chr) && k < 10)
							{
								k++;
								chr.model = "flutist_"+sti(rand(11)+1);
							}
							arrayNPCModel[arrayNPCModelHow] = chr.model;
							arrayNPCModelHow++;
							chr.model.animation = "musician";
							if(rand(1) == 1) LAi_SetFlutistStayType(chr);
								else LAi_SetFlutistSitType(chr);
						}
						else
						{
							k = 0;
							chr.model = "violinist_"+sti(rand(16)+1);
							while (!CheckNPCModelUniq(chr) && k < 10)
							{
								k++;
								chr.model = "violinist_"+sti(rand(16)+1);
							}
							arrayNPCModel[arrayNPCModelHow] = chr.model;
							
							chr.model.animation = "musician";
							LAi_SetViolinistStayType(chr);
						}
					}
					RemoveAllCharacterItems(chr, true);
					chr.chr_ai.hp_max = 1;
					chr.chr_ai.hp = 1;
                    chr.Unpushable = "";
					ChangeCharacterAddressGroup(chr, loc.id, "band", "band"+i);
					if (sti(Colonies[iColony].HeroOwn) == true) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					else LAi_group_MoveCharacter(chr, slai_group);
					LAi_SetLoginTime(chr, 16.0, 21.99); // Rebbebion, "часы приёма" для музыкантов
				}
			}
		}
	}
	//PGG_TavernCheckIsPGGHere(); //Jason: вызов ПГГ закомментил
	if (CheckAttribute(pchar, "GenQuest.Ole")) LSC_CheckOlePearl(); // Оле клянчит очередную жемчужину
}

void CreateMaltains(aref loc)//Jason, заполнение базы мальтийцев в Сен-Пьере
{	
	if (GetCityNation("FortFrance") != FRANCE) return; 
	if(CheckAttribute(loc, "QuestCapture")) return; // если идёт квестовый бой
	
	if (CheckAttribute(loc, "Maltains"))
	{
		ref sld;
		int i;
		if (!CheckAttribute(loc, "Maltains_date") || GetNpcQuestPastDayParam(loc, "Maltains_date") >= 2)
		{
			SaveCurrentNpcQuestDateParam(loc, "Maltains_date");
			//офицер
			sld = GetCharacter(NPC_GenerateCharacter("Maltie_officer", "off_Malt_1", "man", "man", 35, FRANCE, 2, false, "soldier"));
			FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 100, 100, "blade_07", "pistol5", "bullet", 150);//спецназ
			sld.greeting = "patrol";
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Maltie_officer";
			ChangeCharacterAddressGroup(sld, "Fortfrance_dungeon", "sit", "sit1");
			LAi_SetHuberType(sld);
			sld.standUp = true;
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			//протекторы
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaltainsPro_"+i, "sold_fra_"+(i+8), "man", "man", 25, FRANCE, 2, false, "soldier"));
				FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 90, 90, "blade_08", "pistol6", "bullet", 100);//спецназ
				sld.greeting = "protector";
				sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
				sld.dialog.currentnode = "Maltie_soldier";
				ChangeCharacterAddressGroup(sld, "Fortfrance_dungeon", "soldiers", "soldier"+i);
				LAi_SetGuardianType(sld);
				LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			}
			//сидячие рыцари, 3 шт
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaltainsSit_"+i, "sold_fra_"+(rand(7)+9), "man", "man", 20, FRANCE, 2, false, "soldier"));
				FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 70, 70, "blade_08", "pistol7", "bullet", 100);//спецназ
				sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
				sld.dialog.currentnode = "Maltie_soldier";	
				sld.greeting = "soldier";
				LAi_LoginInCaptureTown(sld, true);
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetSitType(sld);
				sld.standUp = true;
				PlaceCharacter(sld, "sit", "random_free");
				LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			}
			//стоячие рыцари, 4 шт
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaltainsStay_"+i, "sold_fra_"+(rand(7)+9), "man", "man", 20, FRANCE, 2, false, "soldier"));
				FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 70, 70, "blade_08", "pistol7", "bullet", 100);//спецназ
				sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
				sld.dialog.currentnode = "Maltie_soldier";	
				sld.greeting = "soldier";
				LAi_LoginInCaptureTown(sld, true);
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetGuardianType(sld);
				PlaceCharacter(sld, "soldiers", "random_free");
				LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			}
			//бродячие рыцари, 4 шт
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaltainsGo_"+i, "sold_fra_"+(rand(7)+9), "man", "man", 20, FRANCE, 2, false, "soldier"));
				FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 70, 70, "blade_08", "pistol7", "bullet", 100);//спецназ
				sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
				sld.dialog.currentnode = "Maltie_soldier";	
				sld.greeting = "soldier";
				LAi_LoginInCaptureTown(sld, true);
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetPatrolType(sld);
				sld.city = "FortFrance";
				sld.citytype = "soldier";
				PlaceCharacter(sld, "goto", "random_free");
				LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			}
		}
		//заключенные
		if (!CheckAttribute(loc, "Maltaprisoner_date") || GetNpcQuestPastDayParam(loc, "Maltaprisoner_date") > 15)
		{
			SaveCurrentNpcQuestDateParam(loc, "Maltaprisoner_date");
			for (i=2; i<=(rand(2)+2); i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaltainsPrisoner_"+i, "mercen_"+(rand(29)+1), "man", "man", 10, FRANCE, 15, false, "slave"));
				RemoveAllCharacterItems(sld, true);
				LAi_CharacterDisableDialog(sld);
				LAi_LoginInCaptureTown(sld, true);
				LAi_SetLoginTime(sld, 0.0, 24.0);
				if (rand(1) == 0) LAi_SetStayType(sld);
				else LAi_SetGroundSitType(sld);
				ChangeCharacterAddressGroup(sld, "Fortfrance_dungeon", "quest", "quest"+i);
				LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			}
		}
	}
}

void CreateHWICOffice(aref loc)//Jason, заполнение офиса ГВИК. Belamour legendary edition переехали в новое здание
{	
	if (GetCityNation("Villemstad") != HOLLAND) return; 
	
	if (CheckAttribute(loc, "HWIC"))
	{
		ref sld;
		int i;
		if (!CheckAttribute(loc, "HWIC_date") || GetNpcQuestPastDayParam(loc, "HWIC_date") >= 30)
		{
			SaveCurrentNpcQuestDateParam(loc, "HWIC_date");
			//солдаты, 6 шт
			for (i=1; i<=6; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("HWIC_sold_"+i, "sold_hol_"+(i+9), "man", "man", 25, HOLLAND, 30, false, "soldier"));
				FantomMakeCoolFighter(sld, 35, 90, 90, "blade_08", "pistol1", "bullet", 100);
				sld.Dialog.Filename = "Quest\HollandGambit\HWIC_Office.c";
				sld.dialog.currentnode = "HWIC_soldier";
				sld.greeting = "protector";
				if(i == 3) ChangeCharacterAddressGroup(sld, "GVIK", "reload", "reload3");
				else ChangeCharacterAddressGroup(sld, "GVIK", "soldiers", "soldier"+i);
				LAi_SetGuardianType(sld);
				LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			}
			//клерки, 2 шт
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("HWIC_clerk_"+i, "citiz_"+(rand(9)+11), "man", "man", 10, HOLLAND, 30, false, "citizen"));
				SetFantomParamFromRank(sld, 10, true);
				sld.Dialog.Filename = "Quest\HollandGambit\HWIC_Office.c";
				sld.dialog.currentnode = "HWIC_clerk";
				sld.greeting = "official";
				RemoveAllCharacterItems(sld, true);
				LAi_SetLoginTime(sld, 6.0, 21.99);
				LAi_SetHuberType(sld);
				ChangeCharacterAddressGroup(sld, "GVIK", "sit", "sit"+i);
				LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			}
		}
		// главный клерк, статик
		sld = GetCharacter(NPC_GenerateCharacter("HWIC_headclerk", "citiz_9", "man", "man", 20, HOLLAND, -1, false, "citizen"));
		SetFantomParamFromRank(sld, 20, true);
		sld.name = GetCharacterName("Coris");
		sld.lastname = GetCharacterName("Gerritz");
		sld.Dialog.Filename = "Quest\HollandGambit\HWIC_Office.c";
		sld.dialog.currentnode = "HWIC_headclerk";
		sld.greeting = "official";
		LAi_SetLoginTime(sld, 6.0, 21.99);
		RemoveAllCharacterItems(sld, true);
		sld.standUp = true; //вставать и нападать на врага
		LAi_SetImmortal(sld, true);
		LAi_SetHuberType(sld);
		ChangeCharacterAddressGroup(sld, "GVIK", "sit", "sit3");
		LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		// 230912 торгует
		sld.Merchant = true;
		sld.Merchant.type = "company";
		sld.money = TRADER_MIN_MONEY;
	}
}

// устанавливаем клановых охранников в LSC - фантомы-однодневки
void CreateLSCGuardClan(aref loc)
{	
	if (loc.id == "LostShipsCity_town")
	{
		ref sld;
		string LocatorGroup, LocatorName;
		int i;
		int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+15;
		int iScl = 30 + 3*sti(pchar.rank);
		
		int imush = 17; // общее число мушкетеров
		int isold = 15; // общее число солдат
		int iprot = 10; // общее число протекторов
		if (CheckNPCQuestDate(loc, "LSCGuard_date"))
		{
			SetNPCQuestDate(loc, "LSCGuard_date");
			LocatorGroup = "soldiers";
			// ставим мушкетеров
			for (i=1; i<=imush; i++)
			{
				LocatorGroup = "soldiers";
				LocatorName = "mushketer"+i;	
				if (i <= 7) // нарвалы 7 шт
				{
					sld = GetCharacter(NPC_GenerateCharacter("NarvalMush_"+i, "mush_ctz_"+(rand(2)+10), "man", "mushketer", iRank, PIRATE, 1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket2", "cartridge", iScl+100);
					sld.dialog.Filename = "Quest\LSC\Guardian.c"; // 170912
					sld.dialog.currentnode = "Narval_soldier";	
					sld.greeting = "Narval";
					sld.RebirthPhantom = true; 
					LAi_CharacterReincarnation(sld, true, true);
					LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
					LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_NarvalConflict");
					ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetGuardianType(sld);
					sld.MusketerDistance = 0;
					LAi_group_MoveCharacter(sld, "LSC_NARVAL");
					sld.LSC_clan = true;
				}
				if (i >= 8 && i <= 14) // ривадос 7 шт
				{
					sld = GetCharacter(NPC_GenerateCharacter("RivadosMush_"+i, "mush_rvd_"+(rand(2)+1), "man", "mushketer", iRank, PIRATE, 1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "bullet", iScl+100);
					sld.dialog.Filename = "Quest\LSC\Guardian.c";
					sld.dialog.currentnode = "Rivados_soldier";	
					sld.greeting = "Rivados"; 
					sld.RebirthPhantom = true; 
					LAi_CharacterReincarnation(sld, true, true);
					LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
					LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_RivadosConflict");
					ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetGuardianType(sld);
					sld.MusketerDistance = 0;
					LAi_group_MoveCharacter(sld, "LSC_RIVADOS");
					sld.LSC_clan = true;
				}
				if (i >= 15) // пираты Акулы
				{
					sld = GetCharacter(NPC_GenerateCharacter("SharkMush_"+i, "mush_ctz_"+(rand(2)+7), "man", "mushketer", iRank, PIRATE, 1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "bullet", iScl+100);
					sld.dialog.Filename = "Quest\LSC\Guardian.c";
					sld.dialog.currentnode = "Shark_soldier";	
					sld.greeting = "SharkPirate"; 
					sld.RebirthPhantom = true; 
					LAi_CharacterReincarnation(sld, true, true);
					LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
					LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_SharkConflict");
					ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetGuardianType(sld);
					sld.MusketerDistance = 0;
					LAi_group_MoveCharacter(sld, "LSC_SHARK");
					sld.LSC_clan = true;
				}
			}
			// ставим солдат
			for (i=1; i<=isold; i++)
			{
				LocatorGroup = "soldiers";
				LocatorName = "soldier"+i;	
				if (i <= 6) // нарвалы
				{
					sld = GetCharacter(NPC_GenerateCharacter("NarvalSold_"+i, "citiz_"+(rand(9)+51), "man", "man", iRank, PIRATE, 1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_15","blade_16","blade_13"), RandPhraseSimple("pistol6","pistol4"), "bullet", iScl+100);
					sld.dialog.Filename = "Quest\LSC\Guardian.c";
					sld.dialog.currentnode = "Narval_soldier";	
					sld.greeting = "Narval"; 
					sld.RebirthPhantom = true; 
					LAi_CharacterReincarnation(sld, true, true);
					LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
					LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_NarvalConflict");
					ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetGuardianType(sld);
					LAi_group_MoveCharacter(sld, "LSC_NARVAL");
					sld.LSC_clan = true;
				}
				if (i >= 7 && i <= 12) // ривадос
				{
					sld = GetCharacter(NPC_GenerateCharacter("RivadosSold_"+i, "rivados_"+(rand(6)+1), "man", "man", iRank, PIRATE, 1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_08","blade_04","blade_06"), RandPhraseSimple("pistol6","pistol5"), "bullet", iScl+100);
					sld.dialog.Filename = "Quest\LSC\Guardian.c";
					sld.dialog.currentnode = "Rivados_soldier";	
					sld.greeting = "Rivados"; 
					sld.RebirthPhantom = true; 
					LAi_CharacterReincarnation(sld, true, true);
					LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
					LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_RivadosConflict");
					ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetGuardianType(sld);
					LAi_group_MoveCharacter(sld, "LSC_RIVADOS");
					sld.LSC_clan = true;
				}
				if (i >= 13) // пираты Акулы
				{
					sld = GetCharacter(NPC_GenerateCharacter("SharkSold_"+i, "citiz_"+(rand(9)+41), "man", "man", iRank, PIRATE, 1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_15","blade_10","blade_13"), RandPhraseSimple("pistol6","pistol5"), "bullet", iScl+100);
					sld.dialog.Filename = "Quest\LSC\Guardian.c";
					sld.dialog.currentnode = "Shark_soldier";	
					sld.greeting = "SharkPirate"; 
					sld.RebirthPhantom = true; 
					LAi_CharacterReincarnation(sld, true, true);
					LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
					LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_SharkConflict");
					ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetGuardianType(sld);
					LAi_group_MoveCharacter(sld, "LSC_SHARK");
					sld.LSC_clan = true;
				}
			}
			// ставим протекторов
			for (i=1; i<=iprot; i++)
			{
				LocatorGroup = "soldiers";
				LocatorName = "protector"+i;	
				if (i <= 3) // нарвалы
				{
					sld = GetCharacter(NPC_GenerateCharacter("NarvalProt_"+i, "citiz_"+(rand(9)+51), "man", "man", iRank, PIRATE, 1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_15","blade_16","blade_13"), "pistol4", "bullet", iScl+100);
					sld.dialog.Filename = "Quest\LSC\Guardian.c";
					if (i == 1) sld.dialog.currentnode = "Narval_warning";	
					if (i == 2) sld.dialog.currentnode = "Narval_parol";
					if (i == 3) sld.dialog.currentnode = "Narval_residence";
					sld.greeting = "Narval"; 
					sld.RebirthPhantom = true; 
					LAi_CharacterReincarnation(sld, true, true);
					LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
					LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_NarvalConflict");
					ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					sld.protector = true;
					if (i != 2) sld.protector.CheckAlways = true; //проверять всегда
					LAi_SetGuardianType(sld);
					LAi_group_MoveCharacter(sld, "LSC_NARVAL");
					sld.LSC_clan = true;
				}
				if (i >= 4 && i <= 8) // ривадос
				{
					sld = GetCharacter(NPC_GenerateCharacter("RivadosProt_"+i, "rivados_"+(rand(6)+1), "man", "man", iRank, PIRATE, 1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_08","blade_04","blade_06"), "pistol4", "bullet", iScl+100);
					sld.dialog.Filename = "Quest\LSC\Guardian.c";
					if (i == 5 || i == 7) sld.dialog.currentnode = "Rivados_warning";	
					if (i == 6 || i == 8) sld.dialog.currentnode = "Rivados_parol";
					if (i == 4) sld.dialog.currentnode = "Rivados_residence";
					sld.greeting = "Rivados"; 
					sld.RebirthPhantom = true; 
					LAi_CharacterReincarnation(sld, true, true);
					LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
					LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_RivadosConflict");
					ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetGuardianType(sld);
					sld.protector = true;
					if (i != 6 ) sld.protector.CheckAlways = true; //проверять всегда
					if (i != 8) sld.protector.CheckAlways = true; //проверять всегда
					LAi_group_MoveCharacter(sld, "LSC_RIVADOS");
					sld.LSC_clan = true;
				}
				if (i >= 9) // пираты Акулы
				{
					sld = GetCharacter(NPC_GenerateCharacter("SharkProt_"+i, "citiz_"+(rand(9)+41), "man", "man", iRank, PIRATE, 1, false, "soldier"));
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_15","blade_10","blade_13"), "pistol4", "bullet", iScl+100);
					sld.dialog.Filename = "Quest\LSC\Guardian.c";
					if (i == 9) sld.dialog.currentnode = "Shark_storage";
					if (i == 10 || i == 11) sld.dialog.currentnode = "Shark_residence";	
					sld.greeting = "SharkPirate"; 
					sld.RebirthPhantom = true; 
					LAi_CharacterReincarnation(sld, true, true);
					LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
					LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_SharkConflict");
					ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetGuardianType(sld);
					sld.protector = true;
					sld.protector.CheckAlways = true; //проверять всегда
					LAi_group_MoveCharacter(sld, "LSC_SHARK");
					sld.LSC_clan = true;
				}
			}
		}
	}
}

void CreateLSCInsideClan(aref loc) // создаем кланы внутри их кораблей
{
	if (CheckAttribute(loc, "lsc_inside"))
	{
		ref sld;
		string LocatorGroup, LocatorName;
		int i;
		int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+15;
		int iScl = 30 + 3*sti(pchar.rank);
		
		if (CheckNPCQuestDate(loc, "LSCInside_date"))
		{
			SetNPCQuestDate(loc, "LSCInside_date");
			LocatorGroup = "goto";
			LocatorName = "goto"+i;	
			switch (loc.lsc_inside)
			{
				case "narval": // нарвалы
					for (i=1; i<=10; i++)
					{
						LocatorGroup = "goto";
						LocatorName = "goto"+i;	
						sld = GetCharacter(NPC_GenerateCharacter("NarvalSoldInside_"+i, "citiz_"+(rand(9)+51), "man", "man", iRank, PIRATE, 1, false, "soldier"));
						FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_15","blade_16","blade_13"), RandPhraseSimple("pistol6","pistol4"), "bullet", iScl+100);
						sld.dialog.Filename = "Quest\LSC\Guardian.c";
						sld.dialog.currentnode = "Narval_soldier";	
						sld.greeting = "Narval"; 
						sld.RebirthPhantom = true; 
						LAi_CharacterReincarnation(sld, true, true);
						LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
						LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_NarvalConflict");
						ChangeCharacterAddressGroup(sld, loc.id, LocatorGroup, LocatorName);
						LAi_SetLoginTime(sld, 0.0, 24.0);
						LAi_SetWarriorType(sld);
						LAi_warrior_DialogEnable(sld, true);
						sld.watchBoxes = true;
						LAi_group_MoveCharacter(sld, "LSC_NARVAL");
						sld.LSC_clan = true;
					}
				break;
				
				case "rivados": // ривадос
					for (i=1; i<=8; i++)
					{
						LocatorGroup = "goto";
						LocatorName = "goto"+i;	
						sld = GetCharacter(NPC_GenerateCharacter("RivadosSoldInside_"+i, "rivados_"+(rand(6)+1), "man", "man", iRank, PIRATE, 1, false, "soldier"));
						FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_08","blade_04","blade_06"), RandPhraseSimple("pistol6","pistol5"), "bullet", iScl+100);
						sld.dialog.Filename = "Quest\LSC\Guardian.c";
						sld.dialog.currentnode = "Rivados_soldier";	
						sld.greeting = "Rivados"; 
						sld.RebirthPhantom = true; 
						LAi_CharacterReincarnation(sld, true, true);
						LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
						LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_RivadosConflict");
						ChangeCharacterAddressGroup(sld, loc.id, LocatorGroup, LocatorName);
						LAi_SetLoginTime(sld, 0.0, 24.0);
						LAi_SetWarriorType(sld);
						LAi_warrior_DialogEnable(sld, true);
						sld.watchBoxes = true;
						LAi_group_MoveCharacter(sld, "LSC_RIVADOS");
						sld.LSC_clan = true;
					}
				break;
				
				case "shark": // пираты Акулы
					for (i=1; i<=10; i++)
					{
						LocatorGroup = "goto";
						LocatorName = "goto"+i;	
						sld = GetCharacter(NPC_GenerateCharacter("SharkSoldInside_"+i, "citiz_"+(rand(9)+41), "man", "man", iRank, PIRATE, 1, false, "soldier"));
						FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_15","blade_10","blade_13"), RandPhraseSimple("pistol6","pistol5"), "bullet", iScl+100);
						sld.dialog.Filename = "Quest\LSC\Guardian.c";
						sld.dialog.currentnode = "Shark_soldier";	
						sld.greeting = "SharkPirate"; 
						sld.RebirthPhantom = true; 
						LAi_CharacterReincarnation(sld, true, true);
						LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); 
						LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_SharkConflict");
						ChangeCharacterAddressGroup(sld, loc.id, LocatorGroup, LocatorName);
						LAi_SetLoginTime(sld, 0.0, 24.0);
						LAi_SetWarriorType(sld);
						LAi_warrior_DialogEnable(sld, true);
						sld.watchBoxes = true;
						LAi_group_MoveCharacter(sld, "LSC_SHARK");
						sld.LSC_clan = true;
					}
				break;
			}
		}
	}
}

// остров Ксочитэм - скелеты
void CreateKsochitamSkeletons(aref loc) //Jason
{	
	if (CheckAttribute(loc, "KsochitamSkeletons"))
	{
		ref sld;
		int i;
		int n = sti(loc.KsochitamSkeletons);
		string sIdf = loc.id;
		int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+8;
		if (iRank > 56) iRank = 56;
		int iScl = 25+2*sti(pchar.rank);
		float fMft = MOD_SKILL_ENEMY_RATE/20;
		if (!CheckAttribute(loc, "Ksochitam_date") || GetNpcQuestPastDayParam(loc, "Ksochitam_date") >= 2)
		{
			SaveCurrentNpcQuestDateParam(loc, "Ksochitam_date");
			for (i=1; i<=n; i++)
			{
				// Captain Beltrop, 16.07.21, перенос переменных выше в цикл, иначе не работают
				string sModel = "skel"+(rand(3)+1);
		        string sBlade = LinkRandPhrase("blade_10","blade_06","blade_04");
		        string sPistol = LinkRandPhrase("pistol6","pistol1","pistol5");
				sld = GetCharacter(NPC_GenerateCharacter(sIdf+"_skeleton_"+i, sModel, "skeleton", "skeleton", iRank, PIRATE, 2, false, "soldier"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, sBlade, sPistol, "bullet", iScl*2+100);
				sld.MultiFighter = 0.9+fMft; // мультифайтер
				ChangeCharacterAddressGroup(sld, sIdf, "monsters", "monster"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
				LAi_group_MoveCharacter(sld, "KSOCHITAM_MONSTERS");
			}
		}
	}
}

// Калеуче - храм на Хаэль Роа - нежить
void CreateKhaelRoaSkeletons(aref loc) //Jason
{	
	if (CheckAttribute(loc, "id.label"))
	{
		if (loc.id.label == "Maze" || loc.id.label == "Alcove")
		{
			ref sld;
			aref grp;
			makearef(grp, loc.locators.monsters);
			int n = GetAttributesNum(grp);
			int i;
			string sIdf = loc.id;
			string sPistol = "pistol1";
			if (MOD_SKILL_ENEMY_RATE > 2) sPistol = "pistol5";
			if (MOD_SKILL_ENEMY_RATE > 4) sPistol = "pistol6";
			if (MOD_SKILL_ENEMY_RATE > 8) sPistol = "pistol4";
			
			int iRank = 17+MOD_SKILL_ENEMY_RATE*2;
			int iHp = 300+MOD_SKILL_ENEMY_RATE*70;
			int iHpt = 200+MOD_SKILL_ENEMY_RATE*30;
			float fMft = 1.0+MOD_SKILL_ENEMY_RATE/20;
			
			if (!CheckAttribute(loc, "KhaelRoa_date") || GetNpcQuestPastDayParam(loc, "KhaelRoa_date") >= 1)
			{
				SaveCurrentNpcQuestDateParam(loc, "KhaelRoa_date");
				for (i=0; i<n; i++)
				{
					if (rand(1) == 0 || loc.id.label == "Alcove") // чавинави
					{
						sld = GetCharacter(NPC_GenerateCharacter(sIdf+"_skeleton_"+i, "Chavinavi_1", "skeleton", "skeleton", iRank+5, PIRATE, 1, false, "soldier"));
						FantomMakeCoolFighter(sld, iRank+5, 80, 80, "topor_01", "", "", 50);
						LAi_SetHP(sld, iHp, iHp);
						sld.KhaelRoaMonster = true;
						sld.name = GetCharacterName("Chavinavi");
						sld.lastname = "";
						sld.MultiFighter = fMft; // мультифайтер
					}
					else // скелеты
					{
						sld = GetCharacter(NPC_GenerateCharacter(sIdf+"_skeleton_"+i, "skel"+(rand(3)+1), "skeleton", "skeleton", iRank, PIRATE, 1, false, "soldier"));
						FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_10","blade_06","blade_04"), sPistol, "bullet", 50);
						LAi_SetHP(sld, iHpt, iHpt);
						sld.name = GetCharacterName("TempleSkeleton");
						sld.lastname = "";
					}
					sld.LSC_clan = true; // для бесконфликтности
					ChangeCharacterAddressGroup(sld, sIdf, "monsters", GetAttributeName(GetAttributeN(grp, i)));
					LAi_SetWarriorType(sld);
					LAi_warrior_SetStay(sld, true);
					LAi_CharacterDisableDialog(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
				}
			}
		}
	}
}

// заполнение инквизиции. eddy
void CreateIncquisitio(aref loc)
{	
	if (GetCityNation("Santiago") != SPAIN) return; 
	
	if (CheckAttribute(loc, "Incquisitio"))
	{
		ref sld;
		string LocatorGroup, LocatorName;
		int i, nSit;
		//====> накидаем священников
		if (CheckNPCQuestDate(loc, "Incquisitor_date"))
		{
			SetNPCQuestDate(loc, "Incquisitor_date");
			LocatorGroup = "goto";
			nSit = rand(2)+1;
			for (i=1; i<=3; i++)
			{
				LocatorGroup = "goto";
				LocatorName = LAi_FindRandomLocator("goto");				 
				if (i==nSit) 
				{
					LocatorGroup = "sit";
					LocatorName = "sit"+(rand(3)+1);			
				}
				sld = GetCharacter(NPC_GenerateCharacter("Incquisitor_"+i, "priest_sp"+i, "man", "man2", 20, SPAIN, 1, false, "citizen"));
				sld.Dialog.Filename = "Incquistors.c";									
				LAi_LoginInCaptureTown(sld, true);
				LAi_SetLoginTime(sld, 0.0, 24.0);
				if (i==nSit) LAi_SetSitType(sld);
				else LAi_SetCitizenType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", LocatorGroup, LocatorName);
			}
		}
		//====> накидаем солдат.
		if (CheckNPCQuestDate(loc, "Guard_date"))
		{
			SetNPCQuestDate(loc, "Guard_date");
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("IncqGuard_"+i, "sold_spa_"+(rand(7)+1), "man", "man", 35, SPAIN, 1, true, "soldier"));
				sld.City = "Santiago";
				sld.CityType = "soldier";
				LAi_LoginInCaptureTown(sld, true);
				FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+15, 100, 90, BLADE_LONG, "pistol3", "grapeshot", 100);//спецназ
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetGuardianType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");	
				locatorName = PlaceCharacter(sld, "soldiers", "random");
				// eddy. проверяем, должен ли солдат быть протектором -->				
				if (locatorName == "soldier1" || locatorName == "soldier2")
				{
					sld.protector.CheckAlways = true; //проверять всегда
					sld.Dialog.Filename = "Incquistors.c";
					sld.greeting = "protector";
				}
				else
				{
					if (findsubstr(locatorName, "protector" , 0) != -1) sld.protector = true;
					sld.Dialog.Filename = "Common_Soldier.c";
					sld.greeting = "soldier";
				}
				// <-- eddy. проверяем, должен ли солдат быть протектором
			}
		}
		//====> накидаем заключенных, раз в месяц.
		if (!CheckAttribute(loc, "Prison_date") || GetNpcQuestPastDayParam(loc, "Prison_date") > 30)
		{
			SaveCurrentNpcQuestDateParam(loc, "Prison_date");
			for (i=1; i<=8; i++)
			{
				if (rand(100)<70)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Prisoner_"+i, "Prison_"+(rand(4)+1), "man", "man2", 10, SPAIN, 30, false, "slave"));							
					sld.Dialog.Filename = "Incquistors.c";
					sld.greeting = "Gr_prison";
					LAi_LoginInCaptureTown(sld, true);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetActorType(sld);
					if (rand(10)>5) LAi_ActorSetLayMode(sld);
					else 
					{
						LAi_SetGroundSitType(sld);
					}				
					//ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "prison", "prison"+i);
					PlaceCharacter(sld, "prison", "random_free");
				}
			}
		}
	}
}
//eddy. наполнение маяка
void CreateMayak(aref loc)
{
	if (loc.type == "mayak")
	{		
		if (!CheckAttribute(loc, "Mayak_date") || GetNpcQuestPastDayParam(loc, "Mayak_date") > 2)
		{
			SaveCurrentNpcQuestDateParam(loc, "Mayak_date");

			if(CheckAttribute(loc, "from_colony")) 
			{
				int iColony = FindColony(loc.from_colony);
			}
			else 
			{
				iColony = FindColony(GetCityNameByIsland(GiveArealByLocation(loc)));
			}
			if(iColony == -1) return;

			int iNation = GetCityNation(GetCityNameByIsland(GiveArealByLocation(loc)));
			if(iNation == -1) return;

			int iCitizensQuantity, iModel;
			ref chr;
			aref st, solderLoc;
			int iChar, i;
			string slai_group, locatorName;
			slai_group = GetNationNameByType(iNation)  + "_mayak"; 
			// солдаты -->
			if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.soldiers"))
			{
				makearef(st, loc.locators.soldiers);
				iCitizensQuantity = GetAttributesNum(st);
				for (i=0; i<iCitizensQuantity; i++)
				{
					solderLoc = GetAttributeN(st, i);
					locatorName = GetAttributeName(solderLoc);					
					if (findsubstr(locatorName, "protector" , 0) != -1) 
					{		
						iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
						chr = &characters[iChar];
					}
					else
					{
						chr = GetCharacter(NPC_GenerateCharacter("GenChar_", "mush_eng_1", "man", "mushketer", sti(pchar.rank), iNation, 2, false, "soldier"));
						chr.id = "GenChar_" + chr.index;
						chr.MusketerDistance = 0;
					}					
					chr.City = Colonies[iColony].id;
					chr.CityType = "soldier";
					chr.greeting = "soldier_common";
					SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+6, true); // бравые орлы
					LAi_SetLoginTime(chr, 0.0, 24.0);
					solderLoc = GetAttributeN(st, i);
					locatorName = GetAttributeName(solderLoc);
					ChangeCharacterAddressGroup(chr, pchar.location, "soldiers", locatorName);
					// eddy. проверяем, должен ли солдат быть протектором -->
					if (findsubstr(locatorName, "protector" , 0) != -1) 
					{
						chr.protector = true;
						chr.greeting = "protector";
						if (locatorName != "protector1" && locatorName != "protector2") 
						{
							chr.protector.CheckAlways = 1; //проверять всегда
							if (locatorName == "protector11") chr.dialog.currentnode = "PortRoyal_Mayak";
							else chr.dialog.currentnode = "PortRoyal_Gans";
						}
					}
					else chr.greeting = "soldier";
					// <-- eddy. проверяем, должен ли солдат быть протектором
					chr.dialog.filename = "Common_Soldier.c";
					LAi_SetGuardianType(chr);
					LAi_group_MoveCharacter(chr, slai_group);
				}
			}
			// солдаты <--
			// патруль -->
			if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.patrol"))
			{
				makearef(st, loc.locators.patrol);
				iCitizensQuantity = GetAttributesNum(st);
				for (i=0; i<iCitizensQuantity; i++)
				{
					iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
					chr = &characters[iChar];
					chr.City = Colonies[iColony].id;
					chr.CityType = "soldier";
					SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
					LAi_SetLoginTime(chr, 0.0, 24.0);
					LAi_SetPatrolType(chr);
					LAi_group_MoveCharacter(chr, slai_group);
					chr.greeting = "soldier";
					PlaceCharacter(chr, "patrol", "random_free");
					chr.dialog.filename = "Common_Soldier.c";
					chr.dialog.currentnode = "first time";
				}
			}
			// патруль <--
			LAi_group_SetLookRadius(slai_group, 80);
			LAi_group_SetHearRadius(slai_group, 80);
		}
	}
}

void CreateBrothels(aref loc)
{
	if (CheckAttribute(loc, "brothel"))
	{
		ref location;
		if (findsubstr(loc.id, "SecBrRoom", 0) != -1)
		{
			location = &locations[FindLocation(loc.fastreload + "_Brothel")];
		}
		else
		{
			makeref(location, loc);
		}
		if (!CheckAttribute(location, "Brothel_date") || GetNpcQuestPastDayParam(location, "Brothel_date") > 100)
		{
			ref sld;
			int iColony, iNation, qty, num, qtyAll, qtyStay, qtySit, SitLocatorNum;
			// ==>  массив моделек шлюх, чтоб не двоились в локациях
			string horse[8];
			horse[0] = "women_19";
			horse[1] = "women_20";
			horse[2] = "women_21";
			horse[3] = "women_22";
			horse[4] = "women_23";
			horse[5] = "women_24";
			horse[6] = "women_25";
			horse[7] = "women_26";
			SaveCurrentNpcQuestDateParam(location, "Brothel_date");
			if(CheckAttribute(location, "fastreload"))
			{
				iColony = FindColony(location.fastreload);
			}
			else return;
			iNation = GetCityNation(location.fastreload);
			string slai_group = GetNationNameByType(iNation)  + "_citizens";
			qty = 1;
			SitLocatorNum = 1;
			qtyStay = rand(1) + 3;
			//qtySit = rand(3);
			qtySit = 1;
			qtyAll = qtyStay + qtySit;
			trace("qtyAll " + qtyAll + " qtyStay "+qtyStay+ " qtySit "+qtySit);
			while (qty <= qtyAll)
			{
				num = rand(7);
				if (horse[num] != "")
				{
					sld = GetCharacter(NPC_GenerateCharacter("HorseGen_"+location.index +"_"+ qty, horse[num], "woman", "woman", 3, iNation, 100, false, "soldier"));
					sld.City = location.fastreload;
					sld.CityType = "horse";
					sld.dialog.filename = "Common_Brothel.c";
					sld.dialog.currentnode = "Horse_talk";
					sld.greeting = "whore";
					switch (location.fastreload)
					{
						case "Marigo": 			sld.quest.price = 40*(rand(5) + rand(5)); 			break;
						case "Tortuga":   		sld.quest.price = 40*(rand(5) + rand(5)); 			break;
						case "FortFrance":  	sld.quest.price = 50 + 40*(rand(5) + rand(5)); 		break;
						case "PortRoyal":  		sld.quest.price = 150 + 40*(rand(5) + rand(5)); 	break;
						case "Charles":   		sld.quest.price = 200 + 40*(rand(5) + rand(5)); 	break;
						case "Bridgetown":  	sld.quest.price = 250 + 40*(rand(5) + rand(5)); 	break;
						case "SantoDomingo": 	sld.quest.price = 300 + 40*(rand(5) + rand(5)); 	break;
						case "Panama":   		sld.quest.price = 500 + 40*(rand(5) + rand(5)); 	break;
					}
					//LAi_SetCitizenType(sld);
					if(qty <= qtyStay)
					{
						LAi_SetHorseStayType(sld);
						LAi_group_MoveCharacter(sld, slai_group);
						ChangeCharacterAddressGroup(sld, location.id, "goto", "goto"+qty);
					}
					else
					{
						if(qtySit > 0)
						{
							/* if(horse[num] == "women_21" || horse[num] == "women_22")
							{
								horse[num] = "";
								qty++;
								continue;
							} */
							trace(" qtySit ");
							LAi_SetHorseSitType(sld);
							LAi_group_MoveCharacter(sld, slai_group);
							ChangeCharacterAddressGroup(sld, location.id, "HorseSit", "HorseSit"+SitLocatorNum);
							SitLocatorNum ++;
						}
					}
					horse[num] = "";
					qty++;
				}
			}
		}
	}
}

void CreatePearlVillage(aref loc) // Jason: деревни мискито, браво, араваков
{
	if (CheckAttribute(loc, "pearlVillage"))
	{
		if (CheckNPCQuestDate(loc, "miskito_date"))
		{
			SetNPCQuestDate(loc, "miskito_date");
			int i, iMassive;
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			int grp = sti(loc.pearlVillage);
			int num = rand(2)+6; //кол-во 
			ref chr;
			string model[10];		
			model[0] = "Miskito_1";
			model[1] = "Miskito_2";
			model[2] = "Miskito_3";
			model[3] = "Miskito_4";
			model[4] = "Miskito_5";
			model[5] = "Miskito_6";
			model[6] = "Miskito_1";
			model[7] = "Miskito_2";
			model[8] = "Miskito_3";
			model[9] = "Miskito_4";
			i = 0;
			
			while(i < num)
			{
				iMassive = rand(9);
				if (model[iMassive] != "")
				{
					chr = GetCharacter(NPC_GenerateCharacter("Miskito"+grp+"_"+i, model[iMassive], "man", "man", iRank, ENGLAND, 1, true, "native"));
					SetFantomParamFromRank(chr, iRank, true);
					chr.name = GetIndianName(MAN);
					chr.lastname = "";
					LAi_SetLoginTime(chr, 6.0, 21.99);
					LAi_CharacterReincarnation(chr, true, true);
					LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); 
					chr.dialog.Filename = "indian_dialog.c";
					chr.dialog.currentnode = "IndianMan";
					chr.greeting = "indian_male";
					GiveItem2Character(chr, LinkRandPhrase("slave_01","slave_02","topor_05"));
					EquipCharacterbyItem(chr, LinkRandPhrase("slave_01","slave_02","topor_05"));
					chr.city = "SantaCatalina"; //НЗГ Санта-Каталины
					if (grp == 3) chr.city = "Maracaibo"; // Addon 2016-1 Jason Пиратская линейка
					PlaceCharacter(chr, "goto", "random");
					LAi_SetWarriorType(chr);
					LAi_group_MoveCharacter(chr, "MiskitoGroup"+grp);
					i++;
					model[iMassive] = "";
				}
			}
			if (rand(1) == 1) // сидячие у костерка
			{
				for (i=1; i<=2; i++)
				{
					chr = GetCharacter(NPC_GenerateCharacter("MiskitoSit"+grp+"_"+i, "Miskito_"+(rand(5)+1), "man", "man", iRank, ENGLAND, 1, true, "native"));
					SetFantomParamFromRank(chr, iRank, true);
					chr.name = GetIndianName(MAN);
					chr.lastname = "";
					chr.dialog.Filename = "Indian_dialog.c";
					chr.dialog.currentnode = "IndianMan";
					chr.greeting = "indian_male";
					GiveItem2Character(chr, LinkRandPhrase("slave_01","slave_02","topor_05"));
					EquipCharacterbyItem(chr, LinkRandPhrase("slave_01","slave_02","topor_05"));
					chr.city = "SantaCatalina"; //НЗГ Санта-Каталины
					if (grp == 3) chr.city = "Maracaibo"; // Addon 2016-1 Jason Пиратская линейка
					ChangeCharacterAddressGroup(chr, loc.id, "sit", "ground"+i);
					LAi_SetGroundSitType(chr);
					LAi_group_MoveCharacter(chr, "MiskitoGroup"+grp);
				}
			}
			for (i=1; i<=3; i++) // женщины
			{
				chr = GetCharacter(NPC_GenerateCharacter("MiskitoWoman"+grp+"_"+i, "squaw_"+i, "woman", "woman_B", 10, ENGLAND, 1, true, "citizen"));
				SetFantomParamFromRank(chr, 10, true);
				chr.name = GetIndianName(WOMAN);
				chr.lastname = "";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				chr.dialog.Filename = "Indian_dialog.c";
				chr.dialog.currentnode = "IndianWoman";
				//chr.greeting = "cit_common";
				RemoveAllCharacterItems(chr, true);
				chr.city = "SantaCatalina"; //НЗГ Санта-Каталины
				if (grp == 3) chr.city = "Maracaibo"; // Addon 2016-1 Jason Пиратская линейка
				PlaceCharacter(chr, "goto", "random");
				LAi_SetCitizenType(chr);
				LAi_group_MoveCharacter(chr, "MiskitoGroup"+grp);
			}
			LAi_group_SetLookRadius("MiskitoGroup"+grp, 16);
			LAi_group_SetHearRadius("MiskitoGroup"+grp, 10);				
		}
	}
}

void CreateIndianVillage(aref loc) // Jason: деревня карибов
{
	if (CheckAttribute(loc, "indianVillage"))
	{	
		if (CheckNPCQuestDate(loc, "canib_date"))
		{
			SetNPCQuestDate(loc, "canib_date");
			int i, iMassive;
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			int num = rand(2)+6; //кол-во 
			ref chr;
			string model[10];
				
			model[0] = "canib_1";
			model[1] = "canib_2";
			model[2] = "canib_3";
			model[3] = "canib_4";
			model[4] = "canib_5";
			model[5] = "canib_6";
			model[6] = "canib_1";
			model[7] = "canib_2";
			model[8] = "canib_3";
			model[9] = "canib_4";
			i = 0;
			
			while(i < num)
			{
				iMassive = rand(9);
				if (model[iMassive] != "")
				{
					chr = GetCharacter(NPC_GenerateCharacter("Canib_"+i, model[iMassive], "man", "man", iRank, PIRATE, 1, true, "native"));
					SetFantomParamFromRank(chr, iRank, true);
					chr.name = GetIndianName(MAN);
					chr.lastname = "";
					LAi_SetLoginTime(chr, 6.0, 21.99);
					LAi_CharacterReincarnation(chr, true, true);
					LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); 
					chr.dialog.Filename = "Indian_dialog.c";
					chr.dialog.currentnode = "IndianMan";
					chr.greeting = "indian_male";
					GiveItem2Character(chr, LinkRandPhrase("slave_01","slave_02","topor_05"));
					EquipCharacterbyItem(chr, LinkRandPhrase("slave_01","slave_02","topor_05"));
					PlaceCharacter(chr, "goto", "random");
					LAi_SetWarriorType(chr);
				LAi_group_MoveCharacter(chr, "IndianGroup");
				i++;
				model[iMassive] = "";
			}
		}
			if (rand(1) == 1) // сидячие у костерка
			{
				for (i=1; i<=2; i++)
				{
					chr = GetCharacter(NPC_GenerateCharacter("CanibSit_"+i, "Canib_"+(rand(5)+1), "man", "man", iRank, PIRATE, 1, true, "native"));
					SetFantomParamFromRank(chr, iRank, true);
					chr.name = GetIndianName(MAN);
					chr.lastname = "";
					chr.dialog.Filename = "Indian_dialog.c";
					chr.dialog.currentnode = "IndianMan";
					chr.greeting = "indian_male";
					GiveItem2Character(chr, LinkRandPhrase("slave_01","slave_02","topor_05"));
					EquipCharacterbyItem(chr, LinkRandPhrase("slave_01","slave_02","topor_05"));
					ChangeCharacterAddressGroup(chr, loc.id, "sit", "ground"+i);
					LAi_SetGroundSitType(chr);
					LAi_group_MoveCharacter(chr, "IndianGroup");
				}
			}
			for (i=1; i<=3; i++) // женщины
			{
				chr = GetCharacter(NPC_GenerateCharacter("CanibWoman_"+i, "squaw_"+i, "woman", "woman_B", 10, PIRATE, 1, true, "citizen"));
				SetFantomParamFromRank(chr, 10, true);
				chr.name = GetIndianName(WOMAN);
				chr.lastname = "";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				chr.dialog.Filename = "Indian_dialog.c";
				chr.dialog.currentnode = "IndianWoman";
				//chr.greeting = "cit_common";
				RemoveAllCharacterItems(chr, true);
				PlaceCharacter(chr, "goto", "random");
				LAi_SetCitizenType(chr);
				LAi_group_MoveCharacter(chr, "IndianGroup");
			}
			LAi_group_SetLookRadius("IndianGroup", 20);
			LAi_group_SetHearRadius("IndianGroup", 15);				
		}
	}
}

void CreateLosTequesMine(aref loc) // Jason: шахта на руднике
{
	if (loc.id == "LosTeques_mine")
	{
		if (CheckAttribute(loc, "QuestCapture")) {
			return;
		}
		if (!CheckAttribute(loc, "mine_date") || GetNpcQuestPastDayParam(loc, "mine_date") > 30)
		{
			SaveCurrentNpcQuestDateParam(loc, "mine_date");
			int i;
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			ref chr;
			for (i=1; i<=21; i++) // каторжники
			{
				chr = GetCharacter(NPC_GenerateCharacter("MineConvict_"+i, "prizon_"+(rand(7)+1), "man", "man_B", iRank, PIRATE, 30, true, "native"));
				SetFantomParamFromRank(chr, iRank, true);
				chr.dialog.Filename = "Convict_dialog.c";
				chr.dialog.currentnode = "First time";
				chr.greeting = "convict";
				GiveItem2Character(chr, RandPhraseSimple("slave_01","topor_05"));
				EquipCharacterbyItem(chr, RandPhraseSimple("slave_01","topor_05"));
				chr.city = "LosTeques"; 
				ChangeCharacterAddressGroup(chr, loc.id, "monsters", "convict"+i);
				LAi_SetStayType(chr);
				LAi_group_MoveCharacter(chr, "SPAIN_CITIZENS");
			}
			for (i=1; i<=7; i++) // бродячие солдаты
			{
				chr = GetCharacter(NPC_GenerateCharacter("MineSoldier_"+i, "sold_spa_"+(rand(7)+1), "man", "man", iRank+5, SPAIN, 30, true, "soldier"));
				SetFantomParamFromRank(chr, iRank+5, true);
				chr.dialog.Filename = "Common_Soldier.c";
				chr.greeting = "soldier";
				LAi_CharacterReincarnation(chr, true, true);
				LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); 
				chr.city = "LosTeques";
				chr.CityType = "soldier";
				PlaceCharacter(chr, "goto", "random");
				LAi_SetPatrolType(chr);
				LAi_group_MoveCharacter(chr, "SPAIN_CITIZENS");
			}
			for (i=1; i<=4; i++) // протекторы
			{
				chr = GetCharacter(NPC_GenerateCharacter("MineProtector_"+i, "sold_spa_"+(rand(7)+1), "man", "man", iRank+10, SPAIN, 30, true, "soldier"));
				SetFantomParamFromRank(chr, iRank+10, true);
				chr.dialog.Filename = "Common_Soldier.c";
				chr.greeting = "protector";
				LAi_CharacterReincarnation(chr, true, true);
				LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); 
				chr.city = "LosTeques";
				ChangeCharacterAddressGroup(chr, loc.id, "soldiers", "soldier"+i);
				LAi_SetGuardianType(chr);
				LAi_group_MoveCharacter(chr, "SPAIN_CITIZENS");
			}	
		}
		chr = GetCharacter(NPC_GenerateCharacter("MineHead", "off_spa_5", "man", "man", 35, SPAIN, 30, true, "soldier"));
		FantomMakeCoolFighter(chr, 35, 100, 100, "blade_17", "pistol4", "bullet", 250);
		chr.dialog.Filename = "MineHead_dialog.c";
		chr.greeting = "patrol";
		chr.city = "LosTeques";
		ChangeCharacterAddressGroup(chr, loc.id, "quest", "quest1");
		LAi_SetGuardianType(chr);
		LAi_group_MoveCharacter(chr, "SPAIN_CITIZENS");
	}
}

void CreateMineBandits(aref loc) // Jason: бандиты у рудника у Блювельда
{
	ref chr;
	int i;
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
	int iScl = 80;
	if (CheckAttribute(loc, "mine_bandits"))
	{
		if (loc.id == "Mine_exit")
		{
			// отрабатываем вход в локацию
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestCheckDelay("Saga_MineBanditsTalk", 2.0);
			if (CheckNPCQuestDate(loc, "bandits_date"))
			{
				SetNPCQuestDate(loc, "bandits_date");
				for (i=1; i<=6; i++)
				{
					if (i >= 3)
					{
						chr = GetCharacter(NPC_GenerateCharacter("Mine_bandit_"+i, "citiz_"+(rand(9)+51), "man", "man", iRank, PIRATE, 1, true, "soldier"));
						FantomMakeCoolFighter(chr, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
					}
					else
					{
						chr = GetCharacter(NPC_GenerateCharacter("Mine_bandit_"+i, "mush_ctz_"+(rand(2)+10), "man", "mushketer", iRank, PIRATE, 1, false, "soldier"));
						FantomMakeCoolFighter(chr, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
						chr.MusketerDistance = 0; 
					}
					chr.dialog.Filename = "Quest\Saga\OtherNPC.c";
					if (i == 3) chr.dialog.currentnode = "mine_bandit";
					else chr.dialog.currentnode = "mine_bandit_0";
					//chr.greeting = "soldier_common";
					LAi_CharacterReincarnation(chr, true, true);
					LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); 
					LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, false, "Saga_MineBanditsFire");
					ChangeCharacterAddressGroup(chr, loc.id, "soldiers", "protector"+i);
					LAi_SetGuardianType(chr);
					LAi_group_MoveCharacter(chr, "PIRATE_CITIZENS");
				}
			}
		}
		if (loc.id == "Mine_01")
		{
			if (CheckNPCQuestDate(loc, "bandits_date"))
			{
				SetNPCQuestDate(loc, "bandits_date");
				for (i=1; i<=4; i++)
				{
					if (i == 3 || i == 4)
					{
						chr = GetCharacter(NPC_GenerateCharacter("Mine_banditx_"+i, "citiz_"+(rand(9)+51), "man", "man", iRank, PIRATE, 1, true, "soldier"));
						FantomMakeCoolFighter(chr, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
					}
					else
					{
						chr = GetCharacter(NPC_GenerateCharacter("Mine_banditx_"+i, "mush_ctz_"+(rand(2)+10), "man", "mushketer", iRank, PIRATE, 1, false, "soldier"));
						FantomMakeCoolFighter(chr, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
						chr.MusketerDistance = 0; 
					}
					chr.dialog.Filename = "Quest\Saga\OtherNPC.c";
					if (i == 1) chr.dialog.currentnode = "mine_banditx";
					else chr.dialog.currentnode = "mine_bandit_0";
					//chr.greeting = "soldier_common";
					LAi_CharacterReincarnation(chr, true, true);
					LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2);
					LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, false, "Saga_MineBanditsxFire");
					ChangeCharacterAddressGroup(chr, loc.id, "soldiers", "protector"+i);
					LAi_SetGuardianType(chr);
					LAi_group_MoveCharacter(chr, "PIRATE_CITIZENS");
				}
			}
		}
	}
}

void CreateInsideHouseEncounters(aref loc)
{	
	if (CheckAttribute(loc, "MustSetReloadBack") && loc.id.label == "house" && CheckAttribute(loc,"fastreload") && !IsLocationCaptured(loc.fastreload+"_town"))
	{
		// проверяем разрешение города на формирование энкаунтеров
		int iBaseCity = FindLocation(loc.fastreload+"_town");
		if (!CheckAttribute(&locations[iBaseCity], "houseEnc")) return;
		if (CheckAttribute(&locations[iBaseCity], "QuestCapture")) return; // если идёт квестовый бой
		if (CheckAttribute(pchar, "questTemp.LockHouseEnc")) return; // общий лок всех энкаунтеров
		//==> блокируем квест мэра
		if (CheckAttribute(pchar, "GenQuest.SeekSpy.Location") && pchar.GenQuest.SeekSpy.Location == loc.id) return;
		//==> блокируем квест доставки малявы
		if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId") && pchar.questTemp.jailCanMove.Deliver.locationId == loc.id) return;
		if (CheckAttribute(pchar, "questTemp.Shadowtrader.ClearHouse")) return; // 240912
		if (CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "sdm" && loc.id == "CommonPirateHouse") return; // Addon-2016 Jason, французские миниквесты (ФМК)
		if (CheckAttribute(pchar, "questTemp.PatriaTailor") && loc.id == "CommonDoubleflourHouse_1") return;
		//--> ночью не забалуешь
		bool bDN = IsDay();
    	aref arRld, arDis;
		makearef(arRld, loc.reload);
		int i;
    	int	Qty = GetAttributesNum(arRld);
		for (i=0; i<Qty; i++)
    	{
    		arDis = GetAttributeN(arRld, i);
    		if (arDis.name != "reload1")
    		{
				if (bDN && !isBadReputation(pchar, 40)) DeleteAttribute(arDis, "disable");
				else arDis.disable = true; //закрываем вход в коммоны 2 уровня
    		}
    	}
		//<-- ночью не забалуешь
		//==> блокируем локации второго уровня		
		if (locations[reload_cur_location_index].type == "town" || locations[reload_cur_location_index].id == "Islamona_town")
		{
			ref chr, npchar;
			aref rCity;
			makearef(rCity, locations[iBaseCity].houseEnc);		
			bool bMW = rand(1);
			int iNation = GetCityNation(loc.fastreload);
			string slai_group = GetNationNameByType(iNation)  + "_citizens";
			string Model, Name, LastName, sName;
			string sTemp = reload_locator_ref.name + loc.index;
			int iManIdx = GetCharacterIndex("HouseMan_"+iBaseCity+"_"+loc.index);
			int iWomanIdx = GetCharacterIndex("HouseWoman_"+iBaseCity+"_"+loc.index);
			if (iWomanIdx != -1 || iManIdx != -1) 
			{				
				if (!CheckAttribute(rCity, sTemp)) //уже есть хозяин, но дом не тот же, новый!!! сделаем из старого хозяина нового
				{
					if (iWomanIdx != -1) 
					{
						npchar = &characters[iWomanIdx];
						SetRandomNameToCharacter(npchar);
						npchar.model = "women_"+(rand(3)+7);
						FaceMaker(npchar);
						CirassMaker(npchar);
						SetNewModelToChar(npchar);  // перерисуем модель на лету			
						LAi_SetActorType(npchar);
						LAi_ActorDialog(npchar, pchar, "", 1.0, 0); 
						LAi_group_MoveCharacter(npchar, slai_group);
						rCity.(sTemp) = "woman"; //последний сгенеренный
						rCity.(sTemp).woman.model = npchar.model;
						rCity.(sTemp).woman.name = npchar.name;
						rCity.(sTemp).woman.lastname = npchar.lastname;
						//<-- запомним параметры нпс в структуре колонии
					}
					else 
					{
						npchar = &characters[iManIdx];
						SetRandomNameToCharacter(npchar);
						npchar.model = "citiz_"+(rand(9)+1);
						FaceMaker(npchar);
						CirassMaker(npchar);
						SetNewModelToChar(npchar);  // перерисуем модель на лету			
						LAi_SetActorType(npchar);
						LAi_ActorDialog(npchar, pchar, "", 1.0, 0); 
						LAi_group_MoveCharacter(npchar, slai_group);
						//--> запомним параметры нпс в структуре колонии
						rCity.(sTemp) = "man"; //последний сгенеренный
						rCity.(sTemp).man.model = npchar.model;
						rCity.(sTemp).man.name = npchar.name;
						rCity.(sTemp).man.lastname = npchar.lastname;
						//<-- запомним параметры нпс в структуре колонии
					}
				}
				else //уже есть структура на дом с данными хозяина
				{
					if (iWomanIdx != -1) npchar = &characters[iWomanIdx];
					else npchar =  &characters[iManIdx];
					string sSex = sTemp + "." + rCity.(sTemp);
					if (rCity.(sSex).model != npchar.model) 
					{	//данные на хозяина другие, преобразим текущего	
						npchar.model = rCity.(sSex).model;
						if (rCity.(sTemp) == "man") 
						{
							npchar.sex = "man";
							npchar.model.animation = "man";
							npchar.dialog.currentnode = "HouseMan";
							npchar.greeting = "citizen_male";
							LAi_NPC_Equip(npchar, sti(npchar.rank), true, true);
						}
						else 
						{
							npchar.sex = "woman";
							npchar.model.animation = "towngirl";
							npchar.dialog.currentnode = "HouseWoman";
							npchar.greeting = "citizen_female";
							DeleteAttribute(npchar, "equip");
						}
						npchar.name = rCity.(sSex).name;
						npchar.lastname = rCity.(sSex).lastname;
						FaceMaker(npchar);
						CirassMaker(npchar);
						SetNewModelToChar(npchar);  // перерисуем модель на лету					
					}
				}
				return;
			}
			Model = "";
			Name = "";
			LastName = "";
			//-->> генерился ли такой раньше		
			if (CheckAttribute(rCity, sTemp))
			{
				if (GetNpcQuestPastDayParam(rCity, sTemp) < 30)
				{
					if (rCity.(sTemp) == "man") 
					{//если был мужик, то след. - баба
						bMW = true;
						if (CheckAttribute(rCity, sTemp + ".woman.model"))
						{
							Model = rCity.(sTemp).woman.model;
							Name = rCity.(sTemp).woman.name;
							LastName = rCity.(sTemp).woman.lastname;
						}
						else
						{
							if (CheckAttribute(rCity, sTemp + ".man.lastname"))
							{
								LastName = rCity.(sTemp).man.lastname;
							}
						}
					}
					else 
					{//если была баба, то след. - мужик
						bMW = false;
						if (CheckAttribute(rCity, sTemp + ".man.model"))
						{
							Model = rCity.(sTemp).man.model;
							Name = rCity.(sTemp).man.name;
							LastName = rCity.(sTemp).man.lastname;
						}
						else
						{
							if (CheckAttribute(rCity, sTemp + ".woman.lastname"))
							{
								LastName = rCity.(sTemp).woman.lastname;
							}
						}
					}
				}
				else //смена хозяев в доме
				{
					if (rand(10) > 8) //шанс на пустой дом.
					{
						for (i=0; i<Qty; i++) 
    					{//снимаем возможный блок коммонов второго уровня (если репа у ГГ хреновая) 
    						arDis = GetAttributeN(arRld, i);
    						if (arDis.name != "reload1")
    						{
								DeleteAttribute(arDis, "disable");
    						}
    					}
						return; 
					}
					SaveCurrentNpcQuestDateParam(rCity, sTemp); //пишем дату генерации первого нпс в этой локации
				}
			}
			else 
			{
				if (rand(10) > 8) //шанс на пустой дом.
				{
					for (i=0; i<Qty; i++) 
    				{//снимаем возможный блок коммонов второго уровня (если репа у ГГ хреновая) 
    					arDis = GetAttributeN(arRld, i);
    					if (arDis.name != "reload1")
    					{
							DeleteAttribute(arDis, "disable");
    					}
    				}
					return; 
				}
				SaveCurrentNpcQuestDateParam(rCity, sTemp); //пишем дату генерации первого нпс в этой локации
			}
			//<<-- генерился ли такой раньше
			if (bMW)
			{//============= генерим бабу ====================
				if (Model == "") Model = "women_"+(rand(3)+7);
				sName = "HouseWoman_"+reload_cur_location_index+"_"+loc.index;
				chr = GetCharacter(NPC_GenerateCharacter(sName, Model, "woman", "towngirl", rand(2)+4, iNation, 3, false, "citizen"));
				if (Name != "") chr.name = Name;
				if (LastName != "") chr.lastname = LastName;
				chr.dialog.Filename = "HouseEnc_dialog.c";
				if(loc.fastreload == "islamona") chr.dialog.Filename = "Quest\IslaMona_NPC.c";
				chr.dialog.currentnode = "HouseWoman";
				chr.CityType = "citizen";
				chr.city = loc.fastreload; //НЗГ
				chr.greeting = "citizen_female";			
				ChangeCharacterAddressGroup(chr, loc.id, "barmen", "stay");
				LAi_SetActorType(chr);
				LAi_ActorDialog(chr, pchar, "", 1.0, 0); 
				LAi_group_MoveCharacter(chr, slai_group);
				//--> запомним параметры нпс в структуре колонии
				rCity.(sTemp) = "woman"; //последний сгенеренный
				rCity.(sTemp).woman.model = chr.model;
				rCity.(sTemp).woman.name = chr.name;
				rCity.(sTemp).woman.lastname = chr.lastname;
				//<-- запомним параметры нпс в структуре колонии
			}
			else
			{//============ генерим мужика ==================
				if (Model == "") Model = "citiz_"+(rand(9)+11);
				sName = "HouseMan_"+reload_cur_location_index+"_"+loc.index;
				chr = GetCharacter(NPC_GenerateCharacter(sName, Model, "man", "man", rand(10)+4, iNation, 3, true, "citizen"));
				if (Name != "") chr.name = Name;
				if (LastName != "") chr.lastname = LastName;
				chr.dialog.Filename = "HouseEnc_dialog.c";
				if(loc.fastreload == "islamona") chr.dialog.Filename = "Quest\IslaMona_NPC.c";
				chr.dialog.currentnode = "HouseMan";
				chr.CityType = "citizen";
				chr.city = loc.fastreload; //НЗГ
				chr.greeting = "citizen_male";
				ChangeCharacterAddressGroup(chr, loc.id, "barmen", "stay");
				LAi_SetActorType(chr);
				LAi_ActorDialog(chr, pchar, "", 1.0, 0); 
				LAi_group_MoveCharacter(chr, slai_group);
				//--> запомним параметры нпс в структуре колонии
				rCity.(sTemp) = "man"; //последний сгенеренный
				rCity.(sTemp).man.model = chr.model;
				rCity.(sTemp).man.name = chr.name;
				rCity.(sTemp).man.lastname = chr.lastname;
				//<-- запомним параметры нпс в структуре колонии
				
				// --> калеуче
				if(CheckAttribute(PChar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "seek" && chr.city == "Beliz")
				{
					chr.id = "Beliz_townbandos";
					chr.model = "citiz_23";
					Characters_RefreshModel(chr); 
					Rank = 20+MOD_SKILL_ENEMY_RATE*3;
					FantomMakeCoolFighter(chr, Rank, 60, 60, RandPhraseSimple("blade_12","blade_13"), RandPhraseSimple("pistol6","pistol4"), "bullet", 250);
					Mft = MOD_SKILL_ENEMY_RATE/20;
					chr.MultiFighter = 1.0+Mft; // мультифайтер
					chr.dialog.filename = "Quest\Caleuche_dialog.c";
					chr.dialog.currentnode = "Beliz_townbandos";
					chr.greeting = "marginal";
					LAi_SetImmortal(chr, true);
					GiveItem2Character(chr, "kaleuche_letter");
					chr.SaveItemsForDead = true;
					chr.DontClearDead = true;
					pchar.questTemp.Caleuche.Bandos = "find";
					chrDisableReloadToLocation = true;//закрыть локацию
					return;
				}
				// <-- калеуче
				
				if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor.NeedGenerateDuelMan"))
				{
					chr.id = "AffairOfHonor_CoatHonor_Man";
					SetRandNationOfficerModel(chr);
					Characters_RefreshModel(chr); // Jason: рефрешить модель обязательно
					// Jason: дохляки нам не нужны - делаем кулфайтера
					int Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10;
					int Scl = 35+2*sti(pchar.rank);
					FantomMakeCoolFighter(chr, Rank, Scl, Scl, RandPhraseSimple("blade_12","blade_13"), RandPhraseSimple("pistol6","pistol5"), "bullet", Scl*3);
					float Mft = MOD_SKILL_ENEMY_RATE/20;
					chr.MultiFighter = 1.0+Mft; // мультифайтер
					chr.dialog.filename = "Quest\ForAll_dialog.c";
					chr.dialog.currentnode = "AffairOfHonor_CoatHonor_4";
					LAi_SetWarriorType(chr);
					LAi_SetImmortal(chr, true);
					DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor.NeedGenerateDuelMan");
				}
			}
		}
		//==> следование хозяина за ГГ в другие комнаты дома
		else
		{
			//если в комнате уже есть кто-то, то не следуем за ГГ на второй этаж
			for(int n=0; n<MAX_CHARACTERS; n++)
			{
				if (characters[n].location == pchar.location && characters[n].id != "Blaze")
				{
					return;
				}
			}
			//переносим хозяина на второй этаж				
			int iLocIndexEnc;
			if (pchar.location.locator == "reload1") iLocIndexEnc = reload_cur_location_index;
			else iLocIndexEnc = reload_location_index;
			int iEnc = GetCharacterIndex("HouseWoman_"+iBaseCity+"_"+iLocIndexEnc);
			if (iEnc != -1)
			{
				ChangeCharacterAddressGroup(&characters[iEnc], loc.id, "barmen", "stay");
			}
			else
			{
				iEnc = GetCharacterIndex("HouseMan_"+iBaseCity+"_"+iLocIndexEnc);
				if (iEnc != -1)
				{
					ChangeCharacterAddressGroup(&characters[iEnc], loc.id, "barmen", "stay");
				}
			}
			
		}
	}
}

//энкаунтеры в резиденциях
void CreateInsideResidenceEncounters(aref loc)
{	
	bool bOk;
	if (CheckAttribute(loc, "MustSetReloadBack"))
	{ //если заглушка
		if (loc.id.label == "TownhallRoom" || loc.id.label == "Townhall")
		{
			bOk = CreateQuestResidenceNPC(loc);
			if(!bOk) 
			{
				CreateResidenceNpc(loc);
			}	
		}	
	}
	else
	{ //если статичная локация
		if (loc.id.label == "TownhallRoom")
		{
			bOk = CreateQuestResidenceNPC(loc);
			if(!bOk)
			{
				CreateResidenceNpc(loc);
			}	
		}	
	}
}
//относится к методу выше
void CreateResidenceNpc(aref loc)
{
	ref chr;
	int Rank;
	string sModel, sSex, sAni, sNode, sGreeting;
	bool bWeapon;
	int iBaseCity = FindLocation(loc.fastreload + "_town");
	if (!CheckAttribute(&locations[iBaseCity], "houseEnc")) return;
	if (rand(10) > 8) return; //шанс на пустую комнату
	if (CheckAttribute(pchar, "questTemp.FMQT.Common")) return; // Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
	//==> выбираем тип
	int iEncType = rand(3); //0 - леди, 1 - рабочий, 2 - солдат.
	if (loc.id.label  == "TownhallRoom") iEncType = 2;
	if (CheckAttribute(loc, "Bedroom"))  iEncType = 0;	
	if (CheckAttribute(loc, "PlayHall")) iEncType = 1;	
	int iNation = GetCityNation(loc.fastreload);
	if (iNation == PIRATE) return; //пиратские резиденции нам не нужны
	switch (iEncType)
	{
	case 0:
		Rank = 3;
		sModel = "women_"+(rand(5)+1);
		sSex = "woman";
		sAni = "towngirl"
		bWeapon = false;
		sNode = "ResWoman";
		sGreeting = "bedroom_lady";
		break;
	case 1:
		Rank = 5;
		sModel = "barmen_"+(rand(15)+1);
		sSex = "man";
		sAni = "man"
		bWeapon = true;
		sNode = "ResMan";
		sGreeting = "worker";
		break;
	case 2:
		Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE;
		sModel = "sold_"+NationShortName(iNation)+"_"+(rand(7)+1);
		sSex = "man";
		sAni = "man"
		bWeapon = true;
		sNode = "ResGuard";
		sGreeting = "soldier_guard";
		break;
	}
	//==> генерим непися
	string slai_group = GetNationNameByType(iNation) + "_citizens";		
	string sName = "EncResidence_" + iBaseCity + "_" + loc.index;
	if (GetCharacterIndex(sName) > 0) return; //если есть
	chr = GetCharacter(NPC_GenerateCharacter(sName, sModel, sSex, sAni, Rank, iNation, 1, bWeapon, "citizen"));
	chr.dialog.Filename = "ResidenceEnc_dialog.c"; 
	chr.dialog.currentnode = sNode;
	chr.CityType = "citizen";
	chr.city = loc.fastreload; //НЗГ
	chr.greeting = sGreeting;
	ChangeCharacterAddressGroup(chr, loc.id, "barmen", "stay");
	LAi_SetOwnerType(chr);
	LAi_group_MoveCharacter(chr, slai_group);
}

bool CreateQuestResidenceNPC(aref loc)
{
	bool bOk;
	if(CheckAttribute(pchar,"questTemp.ReasonToFast"))
	{
		if(!CheckAttribute(pchar,"questTemp.ReasonToFast.GenerateLakey") && (pchar.questTemp.ReasonToFast.chain == "A1"))
		{
			// генерим лакея
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther")) return false;
			bOk = ReasonToFast_CreateResidenceNPC(loc);
			if(bOk) 
			{
				pchar.questTemp.ReasonToFast.GenerateLakey = true;
				return true;	
			}
			else return false;	
		}
	}
	return false;
}

//энкаунтеры на склад верфи и магазине
void CreateSkladInsideEncounters(aref loc)
{
	if (CheckAttribute(loc, "packhouse") && !IsLocationCaptured(loc.id))
	{
		ref chr;
		int iNation = GetCityNation(loc.fastreload);
		string slai_group = GetNationNameByType(iNation) + "_citizens";		
		string sName = "SkladMan_"+reload_cur_location_index;
		if (GetCharacterIndex(sName) > 0) return; //если есть
		int Rank = sti(pchar.rank) + rand(6);
		if (Rank < 10) Rank += 10;
		if (Rank > 30) Rank -= 10;
		chr = GetCharacter(NPC_GenerateCharacter(sName, "citiz_"+(rand(9)+1), "man", "man", Rank, iNation, 2, true, "citizen"));
		chr.dialog.Filename = "HouseEnc_dialog.c"; 
		chr.dialog.currentnode = "SkladMan";
		chr.CityType = "citizen";
		chr.city = loc.fastreload; //НЗГ
		chr.greeting = "citizen_male";
		LAi_LoginInCaptureTown(chr, false);
		ChangeCharacterAddressGroup(chr, loc.id, "barmen", "stay");
		LAi_SetOwnerType(chr);
		LAi_group_MoveCharacter(chr, slai_group);
	}
}

//тюрьма
void CreateJail(aref loc)
{
	if (loc.type == "jail")
	{
		ref sld;
		string LocatorGroup, LocatorName, slai_group, nShortName;
		int i, nSit, iNation, iRank;			
		if(!CheckAttribute(pchar, "isload") && reload_location_index != reload_cur_location_index)
		{
			pchar.questTemp.jailCanMove = false;
		}
		if (CheckNPCQuestDate(loc, "Jail_date"))
		{
			SetNPCQuestDate(loc, "Jail_date");
			LAi_group_Delete("Prisoner_Group"); 
			iNation = GetCityNation(loc.parent_colony);
			slai_group = GetNationNameByType(iNation)  + "_citizens";
			nShortName = NationShortName(iNation);
			iRank = sti(pchar.rank) + rand(4);
			if (iRank < 10) iRank = 10;
			if (iRank > 20) iRank = 20;
			//====> начальник тюрьмы
			sld = GetCharacter(NPC_GenerateCharacter(loc.parent_colony+"JailOff", "off_"+nShortName+"_"+(rand(1)+1), "man", "man", iRank+5, iNation, 2, true, "governor"));
			sld.City = loc.parent_colony;
			sld.CityType = "soldier";
			sld.standUp = true; //вставать и нападать на врага
 			sld.Dialog.Filename = "Common_prison.c";
			sld.dialog.currentnode = "First_officer";
			sld.greeting = "prisonboss_"+(rand(3)+1);
			FantomMakeCoolFighter(sld, iRank+5, 70, 50, BLADE_LONG, "pistol3", "grapeshot", 30);//спецназ
			LAi_SetLoginTime(sld, 0.0, 24.0);
			LAi_SetHuberType(sld);
			LAi_group_MoveCharacter(sld, slai_group);
			ChangeCharacterAddressGroup(sld, loc.id, "sit", "sit1");
			//====> солдаты
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter(loc.parent_colony+"JailSold_"+i, "sold_"+nShortName+"_"+(rand(7)+1), "man", "man", iRank, iNation, 2, true, "soldier"));
				sld.City = loc.parent_colony;
				sld.CityType = "soldier";
				sld.rank = iRank;
				sld.Dialog.Filename = "Common_prison.c";
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetGuardianType(sld);
				LAi_group_MoveCharacter(sld, slai_group);
				locatorName = PlaceCharacter(sld, "soldiers", "random_free");
				// eddy. проверяем, должен ли солдат быть протектором -->				
				if (locatorName == "protector1")
				{
					sld.protector = true;
					sld.protector.CheckAlways = 1; //проверять всегда
					sld.dialog.currentnode = "First_protector";
					sld.greeting = "protector";
				}
				else
				{
					sld.dialog.currentnode = "First_soldier";
					sld.greeting = "soldier";
				}
				// <-- eddy. проверяем, должен ли солдат быть протектором
			}
			//====> накидаем заключенных
			for (i=1; i<=10; i++)
			{
				if (rand(100)<70)
				{
					sld = GetCharacter(NPC_GenerateCharacter(loc.parent_colony+"Prisoner_"+i, "Prison_"+(rand(4)+1), "man", "man2", 10, iNation, 2, false, "slave"));							
					sld.Dialog.Filename = "Common_prison.c";
					sld.dialog.currentnode = "First_prisoner";
					sld.City = loc.parent_colony;
					sld.greeting = "convict";
					//LAi_LoginInCaptureTown(sld, true);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetActorType(sld);
					locatorName = "prison"+i;
					if (rand(10)>5) 
					{
						LAi_ActorSetLayMode(sld);
						locatorName += "lay";
					}
					else LAi_SetGroundSitType(sld);
					LAi_group_MoveCharacter(sld, "Prisoner_Group");
					ChangeCharacterAddressGroup(sld, loc.id, "prison", locatorName);
				}
			}
		}
	}
}

//форты
void CreateFortsNPC(aref loc)
{	
	if (loc.type == "fort")
	{
		if (loc.id == "Jungle_fort") return;
		int iNation = GetCityNation(loc.parent_colony);	
		if(iNation == -1) return;
		string slai_group = GetNationNameByType(iNation)  + "_citizens";
		if (locations[reload_cur_location_index].type == "jail" && GetNationRelation2MainCharacter(iNation) == RELATION_ENEMY && !CheckAttribute(loc, "loginNpc"))
		{
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			return;
		}
		DeleteAttribute(loc, "loginNpc"); //снимаем возможный флаг на генерацию нпс при выходе из тюрьмы
		if (GetNpcQuestPastDayWOInit(loc, "Fort_date") < 2) return;
		if(CheckAttribute(loc, "QuestCapture")) return; // если идёт квестовый бой
		ref chr;
		int iCitizensQuantity, iChar, i;
		string locatorName, sType;
		int iColony = -1;
		SaveCurrentNpcQuestDateParam(loc, "Fort_date");
		if(CheckAttribute(loc, "parent_colony")) iColony = FindColony(loc.parent_colony);
		if(iColony == -1) return;		
		arrayNPCModelHow = 0;
		// солдаты -->
		if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.soldiers"))
		{
			aref solderLoc, st;
			makearef(st, loc.locators.soldiers);
			iCitizensQuantity = GetAttributesNum(st);		
			for (i=0; i<iCitizensQuantity; i++)
			{	
				if(iNation != PIRATE)
				{
					sType = "soldier";
					iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
				}
				else
				{
					sType = "pirate";
					iChar = NPC_GeneratePhantomCharacter("pirate", iNation, MAN, 2);
				}
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, MAN);
				chr.City = Colonies[iColony].id;
				chr.CityType = "soldier";
				chr.RebirthPhantom = true; 
				LAi_CharacterReincarnation(chr, true, true);
				LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //задаем шаг на увеличение ранга фантомам на реинкарнацию
				SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
				solderLoc = GetAttributeN(st, i);
				locatorName = GetAttributeName(solderLoc);
				ChangeCharacterAddressGroup(chr, pchar.location, "soldiers", locatorName);
				// eddy. проверяем, должен ли солдат быть протектором -->
				if (findsubstr(locatorName, "protector" , 0) != -1 && iNation != PIRATE) 
				{
					chr.protector = true;
					chr.greeting = "protector";
					// belamour cle
					if (!CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && sti(pchar.rank) < 4
					&& !CheckAttribute(pchar, "questTemp.Wine") && chr.location.group == "soldiers"
					&& locatorName == "protector1")
					{
						string wineCity = "FortFrance";
						if(SandboxMode)
						{
							if(CheckAttribute(pchar,"HeroParam.ToCityId"))
							{
								wineCity = pchar.HeroParam.ToCityId;	
							}
						}
						if(GetCityNameByIsland(LoadedLocation.islandId) ==  wineCity) AddLandQuestMark(chr, "questmarkmain");
						if(StartHeroType == 2)
						{
							if(LoadedLocation.id == "Santiago_fort") AddLandQuestMark(chr, "questmarkmain");
						}
					}
				}
				else chr.greeting = "soldier";
				// <-- eddy. проверяем, должен ли солдат быть протектором
				LAi_SetLoginTime(chr, 0.0, 24.0);
				LAi_SetGuardianType(chr);
				if (sti(Colonies[iColony].HeroOwn) == true)
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
				}
				chr.dialog.filename = "Common_Fort.c";
				chr.dialog.currentnode = "First time";
			}
		}
		// солдаты <--
		// патруль -->
		if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.patrol"))
		{			
			makearef(st, loc.locators.patrol);
			iCitizensQuantity = GetAttributesNum(st);
			for (i=0; i<iCitizensQuantity; i++)
			{
				if(iNation != PIRATE)
				{
					sType = "soldier";
					iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
				}
				else
				{
					sType = "pirate";
					iChar = NPC_GeneratePhantomCharacter("pirate", iNation, MAN, 2);
				}
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, MAN);
				chr.City = Colonies[iColony].id;
				chr.CityType = "fortPatrol";
				SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
				chr.RebirthPhantom = true; 
				LAi_CharacterReincarnation(chr, true, true);
				LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //задаем шаг на увеличение ранга фантомам на реинкарнацию
				LAi_SetLoginTime(chr, 0.0, 24.0);
				LAi_SetPatrolType(chr);

				if (sti(Colonies[iColony].HeroOwn) == true)
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					chr.greeting = "town_pirate";
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
					chr.greeting = "soldier";
				}
				PlaceCharacter(chr, "patrol", "random_free");
				chr.dialog.filename = "Common_Fort.c";
				chr.dialog.currentnode = "First time";
			}
		}
		// патруль <--
	}
}

void CreateAmmo(aref loc) // Jason, оружейная
{
	if (loc.type == "ammo")
	{
		if (Loc.id == "Jungle_fort_ammo") return;
		ref sld;
		int i, iNation, iRank;			
		if (!CheckAttribute(loc, "Ammo_date") || GetNpcQuestPastDayParam(loc, "Ammo_date") > 2)
		{
			SaveCurrentNpcQuestDateParam(loc, "Ammo_date");
			iNation = GetCityNation(loc.parent_colony);
			string slai_group = GetNationNameByType(iNation)  + "_citizens";
			iRank = sti(pchar.rank)+5+MOD_SKILL_ENEMY_RATE*2;
			// комендант
			sld = GetCharacter(NPC_GenerateCharacter(loc.parent_colony+"AmmoOff", "off_"+NationShortName(iNation)+"_"+(rand(1)+1), "man", "man", iRank, iNation, 2, true, "governor"));
			FantomMakeCoolFighter(sld, iRank+5, 70, 70, "blade_13", "pistol3", "grapeshot", 100);
			sld.City = loc.parent_colony;
			sld.CityType = "soldier";
			sld.standUp = true; //вставать и нападать на врага
			sld.Dialog.Filename = "Common_Ammo.c";
			sld.dialog.currentnode = "First time";
			sld.greeting = "comandante";
			LAi_SetLoginTime(sld, 0.0, 24.0);
			LAi_SetHuberType(sld);
			LAi_group_MoveCharacter(sld, slai_group);
			ChangeCharacterAddressGroup(sld, loc.id, "sit", "sit1");
			// солдаты
			for (i=1; i<=3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter(loc.parent_colony+"AmmoSold_"+i, "sold_"+NationShortName(iNation)+"_"+(rand(7)+1), "man", "man", iRank, iNation, 2, true, "soldier"));
				FantomMakeCoolFighter(sld, iRank, 60, 60, "blade_13", "pistol1", "bullet", 50);
				sld.City = loc.parent_colony;
				sld.CityType = "soldier";
				sld.rank = iRank;
				sld.Dialog.Filename = "Common_soldier.c";
				sld.greeting = "soldier";
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetGuardianType(sld);
				LAi_group_MoveCharacter(sld, slai_group);
				ChangeCharacterAddressGroup(sld, loc.id, "soldiers", "soldier"+i);
			}
		}
	}
}

// belamour вынес в отдельный метод
void CreatIslaMonaNPC(ref loc)
{
	if (isLocationHasCitizens(loc.id)) return;
	if(CheckAttribute(pchar,"questTemp.IslaMonaDisableFantom")) return;
	if(!CheckAttribute(pchar,"questTemp.IslaMona.TownStage")) return;
	//if(sti(pchar.questTemp.IslaMona.TownStage) < 2) return;
	int iColony = -1;
	if(CheckAttribute(loc,"fastreload")) iColony = FindColony(loc.fastreload);
		
	int iChar, i;
	ref chr;
	
	if(loc.id == "islamona_town")
	{
		log_testinfo("loc.id Ok...");
		if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage") && sti(pchar.questTemp.IslaMona.TownStage) > 1)
		{
			log_testinfo("Stage Ok...");
			ref rTown = GetColonyByIndex(iColony);
			if(CheckAttribute(rTown,"Ship.crew.quantity") && rTown.Ship.crew.quantity > 0) // матросы у костра
			{
				log_testinfo("crew.quantity Ok...");
				arrayNPCModelHow = 0;
				if(!CheckAttribute(loadedlocation,"models.night.beachcamp"))
				loadedlocation.models.night.beachcamp = "beachcamp";
				int j = sti(rTown.Ship.crew.quantity)/100;
				if(j < 1) j=1;
				for(i=1; i<=j; i++)
				{
					iChar = NPC_GeneratePhantomCharacter("sailor", PIRATE, MAN, 1);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, "sailor", MAN);
					chr.City = Colonies[iColony].id;
					chr.CityType = "sailor";
					chr.greeting = "town_sailor";
					chr.dialog.filename = "Population\sailor.c";
					chr.dialog.currentnode = "first time";
					LAi_SetLoginTime(chr, 20.0, 7.99);
					ChangeCharacterAddressGroup(chr, "islamona_town", "beachcamp", "fire1_"+i);
					LAi_SetGroundSitTypeNoGroup(chr);
				} 
			}
			else
			{
				if(CheckAttribute(loadedlocation,"models.night.beachcamp"))
					DeleteAttribute(loadedlocation,"models.night.beachcamp");
			}
			ChangeIslamonaCitizens(loc);
		}
		// Jason Исла Мона
		// это таверна Исла Моны
		if(sti(pchar.questTemp.IslaMona.TownStage) > 1)
		{
			for (i=1; i <=rand(1)+3; i++) // поселенцы 3-4 шт по вечерам
			{
				if (CheckFreeLocator(loc.id, "sit_base" + i, -1))
				{
					iChar = NPC_GeneratePhantomCharacter("citizen", PIRATE, MAN, 1);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, "citizen", MAN);
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					ChangeCharacterAddressGroup(chr, loc.id, "sit", "sit_base" + i);
					chr.Default           = loc.id;
					chr.Default.group     = "sit";
					chr.Default.ToLocator = "sit_front" + i;
					LAi_SetLoginTime(chr, 18.0, 23.0);
					LAi_SetSitType(chr);
					LAi_group_MoveCharacter(chr, "PIRATE_CITIZENS");
					chr.quest.last_theme = 0;
					chr.dialog.filename = "Quest\IslaMona_NPC.c";
					chr.dialog.currentnode = "citizen_tavern";
					//chr.greeting = "habitue";
				}
			}
			for (i=1; i<=rand(1)+2; i++) // 2-3 матроса
			{
				iChar = NPC_GeneratePhantomCharacter("sailor", PIRATE, MAN, 1);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, "sailor", MAN);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				sTemp = PlaceCharacter(chr, "sit", "random_free"); 
				ReSitCharacterOnFree(chr, loc.id, sTemp);
				LAi_SetLoginTime(chr, 0.0, 24.0);
				LAi_SetSitType(chr);
				LAi_group_MoveCharacter(chr, "PIRATE_CITIZENS");
				chr.quest.last_theme = 0;
				chr.dialog.filename = "Quest\IslaMona_NPC.c";
				chr.dialog.currentnode = "sailor_tavern";
				chr.greeting = "town_sailor";
			}	
		}
		if(sti(pchar.questTemp.IslaMona.TownStage) > 0)
		{
			if(CheckAttribute(loc,"locators.blacksmith"))
			{
				makearef(locatorGroup, loc.locators.blacksmith);
				iSailorQty = GetAttributesNum(locatorGroup);
				for (i = 1; i <= iSailorQty; i++)
				{
					iChar = NPC_GeneratePhantomCharacter("sailor", PIRATE, MAN, 2);
					chr = &characters[iChar];
					chr.model.animation = "blacksmith";
					chr.model = "blacksmith_"+sti(rand(17)+1);
					chr.City = Colonies[FindColony("islamona")].id;
					RemoveAllCharacterItems(chr, true);
					chr.CityType = "sailor";
					chr.chr_ai.hp_max = 1;
					chr.chr_ai.hp = 1;
                    chr.Unpushable = "";
					ChangeCharacterAddressGroup(chr, loc.id, "blacksmith", "blacksmith"+i);
					LAi_SetLoginTime(chr, 6.0, 21.99);
					LAi_SetBlacksmithType(chr);
					chr.chr_ai.disableDlg = 1;
					//LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				}
			}
		}
	}
	
	if(iColony != -1 && loc.id == "IslaMona_Jungle_01")
	{
		ref rItm;
		log_testinfo("loc.id Ok...");
		if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage") && sti(pchar.questTemp.IslaMona.TownStage) > 1)
		{
			log_testinfo("Stage Ok...");
			rTown = GetColonyByIndex(iColony);
			if(CheckAttribute(rTown,"Ship.crew.quantity") && rTown.Ship.crew.quantity > 0) // матросы у костра
			{
				log_testinfo("crew.quantity Ok...");
				arrayNPCModelHow = 0;
				j = sti(rTown.Ship.crew.quantity)/75;
				if(j < 1) j=1;
				for(i=1; i<=j; i++)
				{
					iChar = NPC_GeneratePhantomCharacter("sailor", PIRATE, MAN, 1);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, "sailor", MAN);
					chr.City = Colonies[iColony].id;
					chr.CityType = "sailor";
					chr.greeting = "town_sailor";
					chr.dialog.filename = "Quest\IslaMona_NPC.c";
					chr.dialog.currentnode = "sailor_town";
					//LAi_SetLoginTime(chr, 20.0, 7.99);
					if(!CheckAttribute(&locations[FindLocation("IslaMona_Jungle_01")], "fire"))
					{
						rItm = ItemsFromID("fire");
						rItm.startLocation = loc.id;
						rItm.shown = true;
						rItm.startLocator = "fire";
						loc.fire = true;
					}
					ChangeCharacterAddressGroup(chr, "IslaMona_Jungle_01", "goto", "ass"+i);
					LAi_SetGroundSitTypeNoGroup(chr);
				}
			}
			else
			{
				if(CheckAttribute(&locations[FindLocation("IslaMona_Jungle_01")], "fire"))
				{
					DeleteAttribute(&locations[FindLocation("IslaMona_Jungle_01")], "fire");
					rItm = ItemsFromID("fire");
					rItm.shown = false;
				}
			}
		}
	}
	// пирс
	if(FindColony("islamona") != -1 && sti(pchar.questTemp.IslaMona.TownStage) > 1 && loc.id == "Shore75" && loc.models.always.locators == "Shore07_locators_pier")
	{
		log_testinfo("условия пирса Ok...");
		if(CheckAttribute(loc,"locators.fisher"))
		{
			rTown = GetColonyByIndex(FindColony("islamona"));
			if(CheckAttribute(rTown,"Ship.crew.quantity") && rTown.Ship.crew.quantity > 0)
			{
				aref locatorGroup;
				makearef(locatorGroup, loc.locators.fisher);
				int iSailorQty = GetAttributesNum(locatorGroup);
				for (i = 1; i <= iSailorQty; i++)
				{
					iChar = NPC_GeneratePhantomCharacter("sailor", PIRATE, MAN, 1);
					chr = &characters[iChar];
					RemoveAllCharacterItems(chr, true);
					chr.City = Colonies[FindColony("islamona")].id;
					chr.model.animation = "fisher";
					SetNPCModelUniq(chr, "fisher", MAN);
					if(!HasSubStr(chr.model, "fisherman")) chr.model = "fisherman_"+sti(rand(10)+1);
					//chr.model = "fisherman_1";
					chr.CityType = "sailor";
					chr.chr_ai.hp_max = 1;
					chr.chr_ai.hp = 1;
                    chr.Unpushable = "";
					ChangeCharacterAddressGroup(chr, loc.id, "fisher", "fisher"+i);
					LAi_SetLoginTime(chr, 6.0, 21.99);
					LAi_SetFisherSitType(chr);
				}
			}
		}
		
		if(CheckAttribute(loc,"locators.fisherstay"))
		{
			rTown = GetColonyByIndex(iColony);
			if(CheckAttribute(rTown,"Ship.crew.quantity") && rTown.Ship.crew.quantity > 0)
			{
				makearef(locatorGroup, loc.locators.fisherstay);
				iSailorQty = GetAttributesNum(locatorGroup);
				for (i = 1; i <= iSailorQty; i++)
				{
					iChar = NPC_GeneratePhantomCharacter("sailor", PIRATE, MAN, 1);
					chr = &characters[iChar];
					RemoveAllCharacterItems(chr, true);
					chr.City = Colonies[iColony].id;
					chr.model.animation = "fisher";
					SetNPCModelUniq(chr, "fisher", MAN);
					if(!HasSubStr(chr.model, "fisherman")) chr.model = "fisherman_"+sti(rand(10)+1);
					//chr.model = "fisherman_1";
					chr.CityType = "sailor";
					chr.chr_ai.hp_max = 1;
					chr.chr_ai.hp = 1;
                    chr.Unpushable = "";
					ChangeCharacterAddressGroup(chr, loc.id, "fisherstay", "fisherstay"+i);
					LAi_SetLoginTime(chr, 6.0, 21.99);
					LAi_SetFisherStayType(chr);
				}
			}
		}
	}
}	

int GetCityNation(string _sColony) // boal метод вернет нацию по ид города
{
    int iColony = FindColony(_sColony)
	if (colonies[iColony].nation == "none")
	{
		return PIRATE;
	}
	return sti(Colonies[iColony].nation);
}

/// boal
// проверка локации на сгенеренного в ней фантома многожневку, если есть, то новый не плодим
bool isLocationHasCitizens(string _locId)
{
    ref rCharacter; //ищем
	int n, Qty;
	bool bOk = false;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter,Characters[n]);
		if (CheckAttribute(rCharacter, "CityType") && !CheckAttribute(rCharacter, "Merchant.type")) // признак фантома-многодневки
		{
            if (rCharacter.location == _locId)
			{
				bOk = true;
				if (rCharacter.chr_ai.type == "patrol")
					PlaceCharacter(rCharacter, "patrol", "random_free"); //патруль генерится в разных локаторах
			}
		}
    }
	return bOk;
}

void ReSitCharacterOnFree(ref chr, string _locId, string sTemp)
{
	int n, k;
	
	n = 0;
	while (!CheckFreeLocator(_locId, sTemp, sti(chr.index)) && n < 10)
	{
	    sTemp = PlaceCharacter(chr, "sit", "random_free");
	    n++;
	}
	
	n = 0;
	while (findsubstr(sTemp, "sit_front" , 0) != -1 && n < 20)
	{    // чтоб не занимали место напротив
	    sTemp = PlaceCharacter(chr, "sit", "random_free");
	    k = 0;
	    while (!CheckFreeLocator(_locId, sTemp, sti(chr.index)) && k < 10)
		{
		    sTemp = PlaceCharacter(chr, "sit", "random_free");
		    k++;
		}
	    n++;
	}
}

bool CheckNPCModelUniq(ref chr)
{
	int   i, n;
	bool  bOk;
	string sModel = chr.model;
	
    bOk = true;
	for (i=0; i<arrayNPCModelHow; i++)
	{
	    if (arrayNPCModel[i] == sModel)
	    {
	        bOk = false;
	        break;
	    }
	}
	return bOk;
}

void SetNPCModelUniq(ref chr, string sType, int iSex)
{
	int i;
	
	i = 0;
	while (!CheckNPCModelUniq(chr) && i < 10)
	{
	    i++;
	    CreateModel(sti(chr.index), sType, iSex);
	}
	arrayNPCModel[arrayNPCModelHow] = chr.model;
	arrayNPCModelHow++;
}

void ChangeIslamonaCitizens(ref loc)
{
	log_testinfo("Меняем жителей Исламоны");
	if(CheckAttribute(loc,"locators.benchsit"))
	{
		ref locatorGroup, sld;
		makearef(locatorGroup, loc.locators.benchsit);
		int LocatorsQty = GetAttributesNum(locatorGroup);
		int i, n;
		string arrayModels[11];
		
		n = 0;
		for(i = 1; i < 13; i++)
		{
			sld = characterFromId("Himenes_companion_"+i);
			if(CheckAttribute(sld, "benchsit"))
			{
				if(sld.sex == "woman")
				{
					sld.model.animation = "towngirl";
				}
				DeleteAttribute(sld, "benchsit");
				LAi_SetCitizenType(sld);
			}
			if(i == 7) continue;
			arrayModels[n] = "Himenes_companion_"+i;
			n++;
		}
		for (i = 1; i <= LocatorsQty; i++)
		{
			//if(rand(3) == 3) continue;
			n = rand(10);
			sld = characterFromId(arrayModels[n]);
			if(CheckAttribute(sld, "benchsit")) continue;
			if(sld.sex == "woman")
			{
				sld.model.animation = "woman";
			}
			LAi_SetBenchSitType(sld);
			ChangeCharacterAddressGroup(sld, loc.id, "benchsit", "benchsit"+i);
			sld.benchsit = true;
		}
	}
}
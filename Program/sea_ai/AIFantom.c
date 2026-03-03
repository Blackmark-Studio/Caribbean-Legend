
#define INVALID_SHIP_TYPE			-1

int seaFantomsNum; // mitrokosta перенес из глобалов
int seaFantoms[MAX_SHIPS_ON_SEA];

ref CreateSeaFantom() {
	int index = FindFirstEmptyCharacter();
	seaFantoms[seaFantomsNum] = index;
	seaFantomsNum++;
	return GetCharacter(index);
}

void ClearSeaFantoms() {
	for (int i = 0; i < seaFantomsNum; i++) {
		int index = seaFantoms[i];
		InitCharacter(GetCharacter(index), index);
		FreeCharacter(index);
	}

	seaFantomsNum = 0;
}

int Fantom_SetEncounterShips(ref rEnc, string sGroupName)
{
    ref rFantom;

    // ENCOUNTER_TYPE_BARREL, ENCOUNTER_TYPE_BOAT
	if (!CheckAttribute(rEnc, "FixedShips"))
	{
		rFantom = CreateSeaFantom();

		DeleteAttribute(rFantom, "relation");
		DeleteAttribute(rFantom, "abordage_twice");
		DeleteAttribute(rFantom, "QuestDate");
		DeleteAttribute(rFantom, "ransom");

		rFantom.SeaAI.Group.Name = sGroupName;
		return 0;
	}

	int iShipSum = 0;

	aref arShip, arShips;
	makearef(arShips, rEnc.FixedShips);

	int i, q = GetAttributesNum(arShips);
    int Commanders[q];
    int iShipTypes[q];
    string ShipModes[q];

    // Найти подходящего командира и поставить его первым (флагман)
    int iCurClass, iBestClass = INT_MAX;
    int numCandidates = 1;
    bool bTrade = (rEnc.Type == "trade");
    Commanders[0] = 0;
	for (i = 0; i < q; i++)
	{
        arShip = GetAttributeN(arShips, i);
		iShipTypes[i] = arShip.type;
		 ShipModes[i] = arShip.mode;

        // Проверяем кандидатуру
        if (or(bTrade && ShipModes[i] == "trade", !bTrade && ShipModes[i] != "trade"))
        {
            iCurClass = ShipsTypes[iShipTypes[i]].Class;
            if (iCurClass < iBestClass)
            {
                iBestClass = iCurClass;
                numCandidates = 1;
                Commanders[0] = i;
            }
            else if (iCurClass == iBestClass)
            {
                Commanders[numCandidates] = i;
                numCandidates++;
            }
        }
	}
    // Перетасовать остальных, чтобы убрать чёткий порядок по специализациям
    int j, tmp;
    int iSort[q];
    for (i = 0; i < q; i++) iSort[i] = i;
    iSort[0] = Commanders[rand(numCandidates-1)]; // Флагман
    iSort[iSort[0]] = 0;
    for (i = q-1; i > 1; i--)
    {
        j = rand(i-1) + 1;
        tmp = iSort[i];
        iSort[i] = iSort[j];
        iSort[j] = tmp;
    }
    // В итоге в блоке "load ship to sea" из SeaLogin
    // корабли будет выгружать именно в таком порядке
	for (i = 0; i < q; i++)
	{
		rFantom = CreateSeaFantom();

		DeleteAttribute(rFantom, "relation");
		DeleteAttribute(rFantom, "abordage_twice");
		DeleteAttribute(rFantom, "QuestDate");
		DeleteAttribute(rFantom, "ransom");

		rFantom.Ship.Type = GenerateShipExt(iShipTypes[iSort[i]], 0, rFantom);
		rFantom.Ship.Mode = ShipModes[iSort[i]];
		rFantom.SeaAI.Group.Name = sGroupName;
		rFantom.Charge.Type = GOOD_BALLS;

		iShipSum++;
	}

	return iShipSum;
}

// на деле этот метод бесполезен, тк золото в сундуке генерится в др месте, а в к3 тут были распределения опыта и команды вообще - позорище
void Fantom_SetRandomMoney(ref rFantom, string sFantomType)
{
	// clear money from character
	rFantom.Money = 0;

	//GenerateBootyItems(rFantom); // to_do del
	if (!CheckAttribute(rFantom, "ship.type")) return; // fix
	
    int iShip = sti(rFantom.ship.type);
	if (iShip == SHIP_NOTUSED) return; // fix
	
	// clear money from character
	rFantom.Money = 0;

	// ship class
	int iSClass = GetCharacterShipClass(rFantom);

	// add money
// boal 20.01.2004 -->
	switch (sFantomType)
	{
		case "trade":
			rFantom.Money = (10 - iSClass) * 100 + rand((10 - iSClass) * 800);
			return;
		break;
		case "war":
			rFantom.Money = (10 - iSClass) * 40 + rand((10 - iSClass) * 350);
			return;
		break;
		case "pirate":
		    rFantom.Money = (10 - iSClass) * 80 + rand((10 - iSClass) * 500);
			return;
		break;
	}
// boal 20.01.2004 <--
	//Trace("Fantom index = " + rFantom.index + ", group id = " + rFantom.SeaAI.Group.Name + ", have invalid encounter type = " + sFantomType);
}

// boal перенес из ВМЛ
int Fantom_CalcSkill(ref rMainCharacter, string sSkill, int iShipClass, int iSkillMin, int iSkillMax, int iSClass7, int iSClass6, int iSClass5, int iSClass4, int iSClass3, int iSClass2, int iSClass1)
// Stone-D : It was all backwards!
{
	int iSkill = GetSummonSkillFromName(rMainCharacter, sSkill);
    // boal 15.03.04 -->
    int minSkillLevel = 0;
	iSkill = iSkill + iSkillMin + rand(iSkillMax - iSkillMin);
	switch (iShipClass)
	{
		case 1: minSkillLevel =  iSClass1; break;
		case 2: minSkillLevel =  iSClass2; break;
		case 3: minSkillLevel =  iSClass3; break;
		case 4: minSkillLevel =  iSClass4; break;
		case 5: minSkillLevel =  iSClass5; break;
		case 6: minSkillLevel =  iSClass6; break;
		case 7: minSkillLevel =  iSClass7; break;
	}
	minSkillLevel = minSkillLevel*10; // приведение скила к 1-100
	
    if (iSkill < minSkillLevel)	iSkill = minSkillLevel;
    // boal 15.03.04 <--
	if (iSkill < 1)		    	iSkill = 1;
	if (iSkill > SKILL_MAX)     iSkill = SKILL_MAX;
	return iSkill;
}

void Fantom_SetCannons(ref rFantom, string sFantomType)
{
	int iSClass = GetCharacterShipClass(rFantom);
	ref rShip = GetRealShip(GetCharacterShipType(rFantom));
	if (sti(rShip.Cannon) == CANNON_TYPE_NONECANNON)
	{
		rFantom.Ship.Cannons.Type = CANNON_TYPE_NONECANNON;
		return;
	}
    int iCaliber = sti(rShip.MaxCaliber);
	string sCannonType = "cannon";
	switch (sFantomType)
	{
        case "trade":
            if(rand(9) > 1) // 80%
			   sCannonType = "culverine";
            break;

		case "war":
			if(rand(9) > 6) // 30%
			   sCannonType = "culverine";
		    break;

		case "pirate":
			if(rand(9) > 4) // 50%
			   sCannonType = "culverine";
		    break;
	}

    // Для поиска кулеврин своя логика
    if(sCannonType != "cannon")
    {
        if(FindRelevantCulverine(rFantom, iCaliber))
            return; // Либо нашли, либо пушки принудительно
    }

    switch(iCaliber)
	{
        case 3:  iCaliber = 0;  break;
        case 6:  iCaliber = 1;  break;
        case 8:  iCaliber = 2;  break;
        case 12: iCaliber = 3;  break;
        case 16: iCaliber = 4;  break;
        case 18: iCaliber = 5;  break;
        case 20: iCaliber = 6;  break;				
        case 24: iCaliber = 7;  break;
        case 32: iCaliber = 8;  break;
        case 36: iCaliber = 9;  break;
        case 42: iCaliber = 10; break;
	}

    iCaliber = iCaliber - rand(1);
    if (iCaliber < 0) iCaliber = 0;

	switch(iCaliber)
	{
        case 0:  iCaliber = 3;  break;
        case 1:  iCaliber = 6;  break;
        case 2:  iCaliber = 8;  break;
        case 3:  iCaliber = 12; break;
        case 4:  iCaliber = 16; break;
        case 5:  iCaliber = 18; break;
        case 6:  iCaliber = 20; break;
        case 7:  iCaliber = 24; break;
        case 8:  iCaliber = 32; break;
        case 9:  iCaliber = 36; break;
        case 10: iCaliber = 42; break;	
	}
	if (iCaliber < 3)
        iCaliber = 3;

	if (iCaliber > sti(rShip.MaxCaliber))
        iCaliber = sti(rShip.MaxCaliber);

	rFantom.Ship.Cannons.Type = GetCannonByTypeAndCaliber(sCannonType, iCaliber);
}

bool FindRelevantCulverine(ref rFantom, int iMaxCaliber)
{
    int iRes = 0;

    // Допустим даунгрейд на 1 вниз, либо ставим пушки
    if(iMaxCaliber == 42) iRes = CANNON_TYPE_CULVERINE_LBS36;
    else if(iMaxCaliber == 20 || iMaxCaliber == 18) iRes = CANNON_TYPE_CULVERINE_LBS18;
    else if(iMaxCaliber == 12 || iMaxCaliber == 8)  iRes = CANNON_TYPE_CULVERINE_LBS8;
    // Нашли
    if(iRes)
    {
        rFantom.Ship.Cannons.Type = iRes;
        return true;
    }
    // Нет валидных
    return false;
}

void Fantom_SetSails(ref rFantom, string sFantomType)
{
	rFantom.Ship.Sails.Gerald = false;
	if (sFantomType == "war") rFantom.Ship.Sails.Gerald = true;
}

// Следовые количества приятностей
void Fantom_SetPrize(ref rFantom)
{
    if (rand(99) < 40)
    {
        int iGoodName = GOOD_SHIPSILK + rand(3);
        int iGoodQuantity = rand(4) + 2 * (7 - GetCharacterShipClass(rFantom));
        Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, true);
    }
}

void Fantom_SetBalls(ref rFantom, string sFantomType)
{
	float fKBalls = 7 - GetCharacterShipClass(rFantom);

	if (fKBalls <= 0) fKBalls = 0.7; // баркас
	switch (sFantomType)
	{
		case "war":
			fKBalls = fKBalls * 1.7;
		break;
		case "trade":
			fKBalls = fKBalls * 0.8;
		break;
		case "pirate":
			fKBalls = fKBalls * 1.0;
		break;
	}
	if (GetCharacterShipClass(rFantom) == 1) fKBalls = fKBalls * 2.2; 
	if (GetCharacterShipClass(rFantom) == 2) fKBalls = fKBalls * 1.8; 
    // boal 20.01.2004 -->
	Fantom_SetCharacterGoods(rFantom, GOOD_BALLS,    	MakeInt(195 * fKBalls + rand(MakeInt(10 * fKBalls))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_BOMBS,    	MakeInt(10  * fKBalls + rand(MakeInt(2  * fKBalls))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_KNIPPELS, 	MakeInt(90  * fKBalls + rand(MakeInt(10 * fKBalls))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_GRAPES,   	MakeInt(70  * fKBalls + rand(MakeInt(10 * fKBalls))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_POWDER,   	MakeInt(350 * fKBalls + rand(MakeInt(30 * fKBalls))), 0);

	Fantom_SetCharacterGoods(rFantom, GOOD_SAILCLOTH, 	MakeInt(4 	* fKBalls + rand(MakeInt(10 * fKBalls))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_PLANKS, 		MakeInt(3 	* fKBalls + rand(MakeInt(20 * fKBalls))), 0);

    Fantom_SetCharacterGoods(rFantom, GOOD_FOOD, 		MakeInt(20 	* fKBalls + rand(MakeInt(26 * fKBalls))), 0);
    Fantom_SetCharacterGoods(rFantom, GOOD_WEAPON, 		MakeInt(8  	* fKBalls + rand(MakeInt(13 * fKBalls))), 0);
    Fantom_SetCharacterGoods(rFantom, GOOD_RUM, 		MakeInt(4  	* fKBalls + rand(MakeInt(10 * fKBalls))), 0);
    Fantom_SetCharacterGoods(rFantom, GOOD_MEDICAMENT, 	MakeInt(4  	* fKBalls + rand(MakeInt(13 * fKBalls))), 0);
    // boal 20.01.2004 <--
}

void Fantom_SetGoods(ref rFantom, string sFantomType)
{
	int 	iShipClass = 7 - GetCharacterShipClass(rFantom);  // для баркаса = 0
	int 	i, iGoods, iRandGoods, iGoodName, iGoodQuantity;

	int 	iMultiply 		= 10;
	int 	iRandMultiply 	= 1;

	int 	iStart 	= GOOD_BALLS;
	int 	iFinish = GOOD_POWDER - iStart - 1;

	bool 	isLock; 
	bool 	bOk = false;

	float 	fModifikator = 0.0;

	int 	Nation = sti(rFantom.nation);

	if(CheckAttribute(rFantom, "situation")) bOk = true;

	switch (sFantomType)
	{
		case "war":
			iStart 	= GOOD_BALLS;
            iFinish = GOOD_BRICK - iStart - 1;
            iMultiply = (rand(5)+5) * (rand(iShipClass) + 1);
			iRandMultiply = 1 + rand(iShipClass);		
			iRandGoods = rand(5)+3;
            // Провиант на корабли снабжения (to_do ref)
            if(IsMerchantShipType(rFantom) && CheckAttribute(rFantom, "RealEncounterType"))
            {
                i = sti(rFantom.RealEncounterType);
                if(i >= ENCOUNTER_TYPE_PATROL_SMALL && i <= ENCOUNTER_TYPE_NAVAL_LARGE)
                    Fantom_SetCharacterGoods(rFantom, GOOD_FOOD, 1000 * iShipClass + rand(300 * iShipClass), rand(1));
            }
			for (i = 0; i < iRandGoods; i++)
			{
				if(rand(4) == 1) isLock = 1; 
				else			 isLock = 0; 	
				isLock = isLock || bOk; 
			    Fantom_SetCharacterGoods(rFantom, iStart + rand(iFinish), iMultiply * rand(iRandMultiply * 3), isLock);
			}
			iMultiply = GetCannonGoodsIdxByType(sti(rFantom.Ship.Cannons.Type));
			if (iMultiply != -1)
			{
				iRandMultiply = rand(6) - 2;  // 0..4 пушки
				if (iRandMultiply > 0)
				{
					Fantom_SetCharacterGoods(rFantom, iMultiply, iRandMultiply, 0);	
				}
			}			
		break;

		case "trade":
			iRandMultiply = 2 + rand(iShipClass);

			if (CheckAttribute(rFantom, "RealEncounterType"))
			{
				switch (sti(rFantom.RealEncounterType))
				{
					case ENCOUNTER_TYPE_MERCHANT_SMALL:
						iGoods = rand(2) + 4; 
						fModifikator = 0.2 + 8.0/iGoods;
						iStart 	= GOOD_FOOD;
						iFinish = GOOD_LEATHER - iStart - 1;						
					break;

					case ENCOUNTER_TYPE_MERCHANT_MEDIUM:
						iGoods = rand(4) + 4; 
						fModifikator = 0.2 + 8.0/iGoods;
						iStart 	= GOOD_FOOD;
						iFinish = GOOD_POWDER - iStart - 1;					
					break;

					case ENCOUNTER_TYPE_MERCHANT_LARGE:
						iGoods = rand(6) + 4; 
						fModifikator = 0.4 + 12.0/iGoods;
						iStart = GOOD_COFFEE;
						iFinish = GOOD_SHIPSILK - iStart - 1;					
					break;

					case ENCOUNTER_TYPE_MERCHANT_CROWN:
						iGoods = rand(3) + 3; 
						fModifikator = 0.4 + 12.0/iGoods;
						iStart = GOOD_POWDER;
						iFinish = GOOD_SLAVES - iStart - 1;
					break;

					case ENCOUNTER_TYPE_MERCHANT_EXPEDITION:
						iGoods = 2 + rand(2);
						fModifikator = 0.4 + 12.0/iGoods;
						iStart = GOOD_SHIPSILK;
						iFinish = GOOD_CANNON_3 - iStart - 1;
					break;

                    case ENCOUNTER_TYPE_MERCHANT_SLAVES:
						iGoods = 2 + rand(1);
						fModifikator = 0.4 + 12.0/iGoods;
						iStart  = GOOD_SLAVES;
						iFinish = 0;
                    break;
				}

				for (i = 0; i < iGoods; i++)
				{
					iGoodName = iStart + rand(iFinish);
					iGoodQuantity = makeint(20 + fModifikator * iMultiply * (2 + rand(iRandMultiply * 3)));

					// уникальные и коронные товары
					if(iGoodName >= GOOD_SHIPSILK && iGoodName <= GOOD_SILVER)
					{
						iGoodQuantity = makeint(rand(25) + rand(15) +  1.5 * (10 - MOD_SKILL_ENEMY_RATE) + 15 * (8 - iShipClass) );
						if(iGoodQuantity < 1) iGoodQuantity = 1;
						isLock = 1; 
						Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, isLock);			
					}
					else
					{
						if(rand(4) == 1) isLock = 1; 
						else			 isLock = 0; 	
						isLock = isLock || bOk; 
						Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, isLock);
					}
				}
			}
		break;

		case "pirate": 
			fModifikator = 1.2;
			iMultiply = (rand(10)+3) * (rand(iShipClass) + 1);
			iRandMultiply = 2 + rand(iShipClass);
			iRandGoods = rand(3) + 1;

			if (CheckAttribute(rFantom, "RealEncounterType"))
			{
				switch (sti(rFantom.RealEncounterType))
				{
					case ENCOUNTER_TYPE_PIRATE: // TO_DO: REF
                        switch (iGPThreatMax)
                        {
                            case THREAT_LVL_1: i = 0;           break;
                            case THREAT_LVL_2: i = rand(1);     break;
                            case THREAT_LVL_3: i = 1 + rand(1); break;
                            case THREAT_LVL_4: i = 2;           break;
                            case THREAT_LVL_5: i = 2 + rand(1); break;
                        }
                        switch(i)
                        {
                            case 0:
                                iRandGoods = rand(3) + 1;
                                iStart 	= GOOD_BALLS;
                                iFinish = GOOD_BRICK - iStart - 1;
                            break;
                            case 1:
                                iRandGoods = rand(4) + 1;
                                iStart 	= GOOD_BALLS;
                                iFinish = GOOD_COFFEE - iStart - 1;
                            break;
                            case 2:
                                iRandGoods = rand(5) + 1;
                                iStart 	= GOOD_BALLS;
                                iFinish = GOOD_POWDER - iStart - 1;
                            break;
                            case 3:
                                iRandGoods = rand(6) + 1;
                                iStart = GOOD_FOOD;
                                iFinish = GOOD_SHIPSILK - iStart - 1;
                            break;
                        }
                        // Следовые количества приятностей
                        if (rand(99) < 40)
                        {
                            iGoodName = GOOD_SHIPSILK + rand(3);
                            iGoodQuantity = rand(4) + 2 * iShipClass;
                            Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, true);
                        }
					break;

					case ENCOUNTER_TYPE_SMUGGLERS:
						// TO_DO
					break;
				}
			}

			for (i = 0; i < iRandGoods; i++)
			{
				iGoodName = iStart + rand(iFinish);
				iGoodQuantity = makeint(20 + fModifikator * iMultiply * (1+rand(iRandMultiply * 3)));

				if(rand(4) == 1) isLock = 1; 
				else			 isLock = 0; 	
				isLock = isLock || bOk; 
				Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, isLock);
			}

			iMultiply = GetCannonGoodsIdxByType(sti(rFantom.Ship.Cannons.Type));
			if (iMultiply != -1)
			{
				iRandMultiply = rand(6) - 2;  // 0..4 пушки
				if (iRandMultiply > 0)
				{
					Fantom_SetCharacterGoods(rFantom, iMultiply, iRandMultiply, 0);	
				}
			}         
		break;
	}

	RecalculateCargoLoad(rFantom);
}

// доработал метод, теперь возвращает сколько взял
int Fantom_SetCharacterGoods(ref rFantom, int iGoods, int iQuantity, bool isLock)
{
	if(iQuantity == 0) return 0;
	if(iGoods > GetArraySize(&Goods) - 1 || iGoods < 0) //fix
	{ 
		trace("rChar " + rFantom.id +"     goods :" + iGoods + " out of order" );
        return 0; 
	}

	string sGood = Goods[iGoods].name;
	int iFreeQuantity = GetGoodQuantityByWeight(iGoods, GetCargoFreeSpace(rFantom));
	if (iFreeQuantity < 0) iFreeQuantity = 0;

	if (iQuantity > iFreeQuantity) iQuantity = iFreeQuantity;
	
	if (CheckAttribute(rFantom,"Ship.Cargo.Goods." + sGood))
	{
		rFantom.Ship.Cargo.Goods.(sGood) = sti(rFantom.Ship.Cargo.Goods.(sGood)) + iQuantity;
	}
    else
	{	
		rFantom.Ship.Cargo.Goods.(sGood) = iQuantity;
	}
	
	if(isLock) rFantom.Ship.Cargo.Goods.(sGood).Lock = true;
	RecalculateCargoLoad(rFantom);
	return iQuantity;
}

// опыт матросов
void Fantom_SetRandomCrewExp(ref rFantom, string sFantomType)
{
    if (!CheckAttribute(rFantom, "ship.type")) return; // fix
    
	int iShip = sti(rFantom.ship.type);
	if (iShip == SHIP_NOTUSED) return; // fix
	
	// ship class
	int iSClass = GetCharacterShipClass(rFantom);

	switch (sFantomType)
	{
		case "trade":
			rFantom.Ship.Crew.Exp.Sailors   = 20 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(70);
			rFantom.Ship.Crew.Exp.Cannoners = 20 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(70);
			rFantom.Ship.Crew.Exp.Soldiers  = 20 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(70);
		break;
		case "war":
			rFantom.Ship.Crew.Exp.Sailors   = 30 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(60);
			rFantom.Ship.Crew.Exp.Cannoners = 30 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(60);
			rFantom.Ship.Crew.Exp.Soldiers  = 30 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(60);
		break;
		case "pirate":
		    rFantom.Ship.Crew.Exp.Sailors   = 35 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(55);
			rFantom.Ship.Crew.Exp.Cannoners = 35 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(55);
			rFantom.Ship.Crew.Exp.Soldiers  = 35 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(55);
		break;
	}
}

void Fantom_SetQuestSitiation(ref rFantom, string sFantomType)
{
	string sSituation;
	bool CanGenerateSituation = false;
	if (!CheckAttribute(rFantom, "ship.type")) return; 
    
	int iShip = sti(rFantom.ship.type);
	if (iShip == SHIP_NOTUSED) return; 
	
	switch (sFantomType)
	{
		case "pirate": // пираты или ДУ
			if(rand(120) < 3) 
			{
				sSituation = "Explosion";
				CanGenerateSituation = true;
			}	
		break;
		case "hunter": // ОЗГ
			if(rand(120) < 3) 
			{
				sSituation = "Explosion";
				CanGenerateSituation = true;
			}	
		break;
		case "war": // военные корабли
			if(rand(120) < 3) 
			{
				sSituation = "Explosion";
				CanGenerateSituation = true;
			}	
		break;
		case "trade": // торговцы
			if(rand(120) < 3) 
			{
				sSituation = "Epidemy";
				CanGenerateSituation = true;
			}	
		break;		
	}
	if(CanGenerateSituation)
	{
		rFantom.situation = sSituation;
		rFantom.situation.type = sFantomType;
		rFantom.DontRansackCaptain = true; // Врагу не сдаётся наш гордый Варяг !!
	}
}

void Fantom_SetDamage(ref rFantom, string sFantomType)
{
	if (!CheckAttribute(rFantom, "ship.type")) return; // fix
    
	int iShip = sti(rFantom.ship.type);
	if (iShip == SHIP_NOTUSED) return; // fix

	switch (sFantomType)
	{
		case "pirate":
			if(rand(100) < 5)
			{
				GenerateShipDamageParameters(rFantom);
			}	
		break;
		case "hunter":
			if(rand(100) < 5)
			{
				GenerateShipDamageParameters(rFantom);
			}			
		break;
		case "trade" :
			if(rand(100) < 10)
			{
				GenerateShipDamageParameters(rFantom);
			}			
		break;
		case "war"	 :
			if(rand(100) < 3)
			{
				GenerateShipDamageParameters(rFantom);
			}			
		break;
	}
}

void GenerateShipDamageParameters(ref rFantom)
{
	int i = rand(100);
	int j = rand(2);
	
	if(i < 33) 
	{
		if( j == 0 ) Fantom_SetDamageHull(rFantom);
		if( j == 1 ) Fantom_SetDamageCrew(rFantom);
		if( j == 2 ) Fantom_SetDamageCannons(rFantom);
		return;
	}	
	if((i >= 33) && (i < 66))
	{
		if( j == 0 )
		{
			Fantom_SetDamageHull(rFantom);
			Fantom_SetDamageCrew(rFantom);
		}
		if( j == 1 )
		{
			Fantom_SetDamageHull(rFantom);
			Fantom_SetDamageCannons(rFantom);
		}
		if( j == 2 )
		{
			Fantom_SetDamageCrew(rFantom);
			Fantom_SetDamageCannons(rFantom);
		}
		return;
	}
	if((i >= 66))
	{
		Fantom_SetDamageHull(rFantom);
		Fantom_SetDamageCrew(rFantom);
		Fantom_SetDamageCannons(rFantom);
		return;	
	}
}

void Fantom_SetDamageHull(ref rFantom)
{
	int nMaxDamageProcent = rand(20) + 20;
	int nHP = GetCurrentShipHP( rFantom );
	nHP -= nHP * nMaxDamageProcent / 100;
	rFantom.ship.hp = nHP; 
}

void Fantom_SetDamageCrew(ref rFantom)
{
	int nMaxDamageProcent = rand(10) + 15;
	int nCrew = GetCrewQuantity( rFantom );
	nCrew -= nCrew * nMaxDamageProcent / 100;
	SetCrewQuantity(rFantom, nCrew);
}

void Fantom_SetDamageCannons(ref rFantom)
{
	aref 	refShip;
	string 	sAttr, sBort;
	int 	i;
	
	makearef(refShip, rFantom.Ship);
	ref rRealShip = GetRealShip(GetCharacterShipType(rFantom));
	
	int iCannonDiff = 0;	
	int rCannonQty = GetBortIntactCannonsNum(rFantom, "cannonr", sti(rRealShip.rcannon));
	int lCannonQty = GetBortIntactCannonsNum(rFantom, "cannonl", sti(rRealShip.lcannon));

	if(rCannonQty > 4)
	{
		iCannonDiff = rand(1) + 1;
		sBort		= "cannonr";
		if(iCannonDiff > 0)
		{
			for (i = 0; i < iCannonDiff; i++)
			{
				sAttr = "c" + i;	
				if (CheckAttribute(rFantom, "Ship.Cannons.Borts." + sBort + ".damages"))
				{
					rFantom.Ship.Cannons.Borts.(sBort).damages.(sAttr) 		= 1.0; 			
				}	
			}
		}	
	}
	if(lCannonQty > 4)
	{
		iCannonDiff = rand(1) + 1;		
		sBort		= "cannonl";
		if(iCannonDiff > 0)
		{
			for (i = 0; i < iCannonDiff; i++)
			{
				sAttr = "c" + i;
				if (CheckAttribute(rFantom, "Ship.Cannons.Borts." + sBort + ".damages"))
				{	
					rFantom.Ship.Cannons.Borts.(sBort).damages.(sAttr) 		= 1.0; 
				}	
			}
		}	
	}			
}

// eddy. подбор типа корабля для фантома от ранга и нац. принадлежности
void SetShipToFantom(ref _chr, string _type, bool _setgoods)
{
	int ShipType;
	int Nation = sti(_chr.nation);
	int Rank = sti(pchar.rank);
	int iClassFlag = FLAG_SHIP_CLASS_6;
	int iTypesFlag = FLAG_SHIP_TYPE_MERCHANT;
	int iNationsFlag = GetNationFlag(Nation);
	switch (_type)
	{
		case "trade":	
			iTypesFlag = FLAG_SHIP_TYPE_MERCHANT;
			if (Rank < 6)
			{
				iClassFlag = FLAG_SHIP_CLASS_6;
			}			
			if (Rank >= 6 && Rank < 12)
			{
				iClassFlag = FLAG_SHIP_CLASS_5;
			}
			if (Rank >= 12 && Rank <= 20)
			{
				iClassFlag = FLAG_SHIP_CLASS_4;
			}
            if (Rank > 21 && Rank <= 29)
            {
                iClassFlag = FLAG_SHIP_CLASS_3 + FLAG_SHIP_CLASS_4;
            }
			if (Rank > 30)
			{
				iClassFlag = FLAG_SHIP_CLASS_2 + FLAG_SHIP_CLASS_3;
			}
		break;
		case "pirate":
			iTypesFlag = FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT;
			if (Rank < 6)
			{
				iClassFlag = FLAG_SHIP_CLASS_6;
			}			
			if (Rank >= 6 && Rank < 12)
			{
				iClassFlag = FLAG_SHIP_CLASS_5;
			}
			if (Rank >= 12 && Rank <= 20)
			{
				iClassFlag = FLAG_SHIP_CLASS_4;
			}
            if (Rank > 21 && Rank <= 29)
            {
                iClassFlag = FLAG_SHIP_CLASS_3 + FLAG_SHIP_CLASS_4;
            }
			if (Rank > 30)
			{
				iClassFlag = FLAG_SHIP_CLASS_2 + FLAG_SHIP_CLASS_3;
			}
		break;

		case "war":
			iTypesFlag = FLAG_SHIP_TYPE_WAR;
			if (Rank < 6)
			{
				iClassFlag = FLAG_SHIP_CLASS_6;
			}			
			if (Rank >= 6 && Rank < 12)
			{
				iClassFlag = FLAG_SHIP_CLASS_5;
			}
			if (Rank >= 12 && Rank <= 20)
			{
				iClassFlag = FLAG_SHIP_CLASS_4;
			}
            if (Rank > 21 && Rank <= 29)
            {
                iClassFlag = FLAG_SHIP_CLASS_3 + FLAG_SHIP_CLASS_4;
            }
			if (Rank > 30)
			{
				iClassFlag = FLAG_SHIP_CLASS_2 + FLAG_SHIP_CLASS_3;
			}
		break;
	}
	
	ShipType = GetRandomShipType(iClassFlag, iTypesFlag, iNationsFlag);
	
	_chr.Ship.Type = GenerateShipExt(ShipType, true, _chr);
	SetRandomNameToShip(_chr);
    SetBaseShipData(_chr);
    SetCrewQuantityFull(_chr);
    Fantom_SetCannons(_chr, _type);
    Fantom_SetBalls(_chr, _type);

	if(_type == "pirate")
	{
		Fantom_SetUpgrade(_chr, "pirate");
	}
	
    if (_setgoods)
    {
        Fantom_SetGoods(_chr, _type);
    }
}

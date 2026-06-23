// Здесь работа с моделями, палубами для абордажа

//Получить картинку для перехода в абордаж
string LAi_GetBoardingImage(ref echr, bool isMCAttack)
{
	ref mchr = GetMainCharacter();
	string deckID = "";
	isMCAttack   = true;// boal 110804 fix всегда герой
	int mclass = GetCharacterShipClass(mchr); // класс корабля ГГ
	int eclass = GetCharacterShipClass(echr); // класс корабля НПС
	
	if(isMCAttack)
	{
		deckID = GetShipLocationID(echr);
	}else{
		deckID = GetShipLocationID(mchr);
	}
	
	int locID = -1;
	if(deckID != "")
	{
		locID = FindLocation(deckID);
		if(locID < 0)
		{
			Trace("Boarding: ship location not found <" + deckID + ">, set default");
			deckID = "";
		}
	}
	if(locID >= 0)
	{
		if(CheckAttribute(&Locations[locID], "image"))
		{
			if(Locations[locID].image != "")
			{
				return Locations[locID].image;
			}
		}
	}
	return "loading\battle.tga";
}

string chooseDeck(ref mchr, ref echr)
{
	int mclass = GetCharacterShipClass(mchr);
	int eclass = GetCharacterShipClass(echr);
	
	if(GetShipTypeName(echr) == "Galeon_sm") return "BOARDING_3_WAR_SM";
	if(GetShipTypeName(echr) == "Memento") return "BOARDING_3_WAR";
	if(mclass > 2 && eclass > 2)
	{
		int HighClass = func_min(mclass, eclass);
		if(HighClass > 5) HighClass = 5;
		if(isTradeDeck(mchr) || isTradeDeck(echr))
		{
			if(isTradeDeck(mchr) && isTradeDeck(echr))
			{
				return "BOARDING_"+HighClass+"_TRADE";
			}
			else
			{
				if(isTradeDeck(mchr)) return "BOARDING_"+mclass+"_TRADE";
				if(isTradeDeck(echr)) return "BOARDING_"+eclass+"_TRADE";
			}
		}
		return "BOARDING_"+HighClass+"_WAR";
	}
	else
	{
		return GetShipLocationID(echr);
	}
	
	return "";
}

bool isTradeDeck(ref chr)
{
	return IsUniversalShipType(chr) || IsMerchantShipType(chr);
}

void DelOurMusketerDist()
{
	ref chr;
	
	if(CheckAttribute(pchar, "GenQuest.boarding.n2"))
	{
		chr = characterFromId(pchar.GenQuest.boarding.n2);
		if(CheckAttribute(chr,"boarding.mDistance"))
		{
			chr.MusketerDistance = float(chr.boarding.mDistance);
			DeleteAttribute(chr,"boarding.mDistance");
		}
		DeleteAttribute(pchar, "GenQuest.boarding.n2");
	}
	if(CheckAttribute(pchar, "GenQuest.boarding.n1"))
	{
		chr = characterFromId(pchar.GenQuest.boarding.n1);
		if(CheckAttribute(chr,"boarding.mDistance"))
		{
			chr.MusketerDistance = float(chr.boarding.mDistance);
			DeleteAttribute(chr,"boarding.mDistance");
		}
		DeleteAttribute(pchar, "GenQuest.boarding.n1");
	}
}

string ChooseShipUpDeck(ref _mchar, ref _enemy)
{
		string sLoc = "loc";
		
	if (GetCargoMaxSpace(_mchar) > GetCargoMaxSpace(_enemy))
	{
			sLoc = "aloc";
	}
	
		return sLoc;
}

//Процес абордажа
bool LAi_IsBoardingProcess()
{
	return LAi_boarding_process;
}

// Определяем следующую палубу
void SetNextDeck(ref enemy, int boardingLocationIdx, bool IsFort)
{
	int eclass = GetCharacterShipClass(&enemy);
	ref location = &Locations[boardingLocationIdx];
	if (CheckAttribute(&location, "UpDeckType"))
	{
		switch (eclass)
		{
			case 1: location.boarding.nextdeck = "Boarding_GunDeck"; break;
			case 2: location.boarding.nextdeck = "Boarding_GunDeck"; break;
			case 3: location.boarding.nextdeck = "Boarding_Campus"; break;
			case 4: location.boarding.nextdeck = "Boarding_Campus"; break;
			case 5: location.boarding.nextdeck = "Boarding_Cargohold"; break;
			case 6: location.boarding.nextdeck = "Boarding_Cargohold"; break;
			case 7: location.boarding.nextdeck = ""; break;
		}
	}

	if (IsFort && location.boarding.nextdeck == "Boarding_bastion")
	{
		location.boarding.nextdeck = "Boarding_bastion"+(hrand(1, boarding_enemy.id + boarding_enemy.name)+1); // TO_DO: другой тэг
	}
}

// Устанавливаем локацию для драки
void BRD_SetLocationForFight(ref deckID, ref locID, ref echr, bool IsFort)
{
	if (IsFort) deckID = GetShipLocationID(echr);
	else deckID = ChooseDeck(pchar, echr);
	
	if(deckID != "")
	{
		locID = FindLocation(deckID);
		if(locID < 0)
		{
			Trace("Boarding: ship location not found <" + deckID + ">, set default");
			deckID = "";
		}
	}
	if(deckID != "") return;

	deckID = LOCINITBRD_DEFAULTLOCATION;
	if (IsFort) deckID = LOCINITBRD_DEFAULTLOCATION_FORT;
	locID = FindLocation(deckID);
}

bool IsUpperDeck(int locIdx)
{
	return CheckAttribute(&Locations[locIdx], "UpDeckType");
}

/// метод расчета от опыта солдат, даёт бонус в НР (или пенальти)
bool GetBoardingHP(ref mchr, ref echr, ref float_boarding_player_hp, ref float_boarding_enemy_hp)
{
	float b_p_hp, b_e_hp;
	float moral;
	float exp;
	float fShipBonus = 0.0;
	b_p_hp = LAi_GetCharacterMaxHP(mchr) / 3.0;  // треть от НР кэпа идет в базу бонуса
	
	exp = GetCrewExp(mchr, "Soldiers") / GetCrewExpRate() - 0.7;
	
	if(ShipBonus2Artefact(mchr, SHIP_MEMENTO))
	{
		if(CheckAttribute(&RealShips[int(mchr.Ship.Type)], "DeadSailors.SailorsBoardingBonus"))
		{
			fShipBonus = float(RealShips[int(mchr.Ship.Type)].DeadSailors.SailorsBoardingBonus) / 100.0;
		}
	}

	exp += fShipBonus;
	moral = 0;
	if(CheckAttribute(mchr, "ship.crew.morale"))
	{
		moral = (float(mchr.ship.crew.morale) - MORALE_NORMAL)/(MORALE_MAX - MORALE_MIN);
		if(moral < -0.5) moral = -0.5;
		if(moral > 0.5) moral = 0.5;
	}
	exp = exp + moral;  // может быть минус
	b_p_hp = b_p_hp*exp; 
	b_e_hp = 0;

	float_boarding_player_hp   =  b_p_hp;
	float_boarding_enemy_hp    =  b_e_hp;
	
	return true;
}
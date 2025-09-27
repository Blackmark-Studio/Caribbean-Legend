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
		return "BOARDING_"+HighClass+"_WAR"
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
			chr.MusketerDistance = stf(chr.boarding.mDistance);
			DeleteAttribute(chr,"boarding.mDistance");
		}
		DeleteAttribute(pchar, "GenQuest.boarding.n2");
	}
	if(CheckAttribute(pchar, "GenQuest.boarding.n1"))
	{
		chr = characterFromId(pchar.GenQuest.boarding.n1);
		if(CheckAttribute(chr,"boarding.mDistance"))
		{
			chr.MusketerDistance = stf(chr.boarding.mDistance);
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

string LAi_GetBoardingMushketerModel(ref rCharacter)
{
	string model;
	int iNation = sti(rCharacter.nation);
	
	//Экку Korsar - пусть у команды-нежити будут мушкетеры-нежить!
	if (CheckAttribute(rCharacter, "GenQuest.CrewSkelMode"))
		{
				model = "mush_skel_"+(rand(3)+1);
		return model;
		}
	
	if(sti(rCharacter.index) == GetMainCharacterIndex()) // для ГГ
	{
		//национальная форма солдат на квестовиках по мультиквесту
		if (CheckAttribute(rCharacter, "questTemp.HWIC.HollEquip") && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
				{
						model = "mush_hol_"+(rand(5)+1);
			return model;
				}
		if (CheckAttribute(rCharacter, "questTemp.HWIC.EngEquip") && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_VALCIRIA)
				{
						model = "mush_eng_"+(rand(5)+1);
			return model;
				}
		if (CheckAttribute(rCharacter, "questTemp.Mtraxx.CharleePrince")) //команда пиратов Fullback7
			{
			model = "mush_ctz_"+(rand(2)+7);
			return model;
		}
		if (CheckAttribute(rCharacter, "questTemp.CharleePrince"))
			{
			model = "mush_ctz_"+(rand(2)+7);
			return model;
		}
		//<-- форма солдат на квестовиках
				if (isMainCharacterPatented() && sti(Items[sti(rCharacter.EquipedPatentId)].TitulCur) > 1) //если есть патент, оставлю, хотя рудимент, форма только со звания капитан
				{
						iNation = sti(Items[sti(rCharacter.EquipedPatentId)].Nation);
			model = "mush_"+NationShortName(iNation)+"_"+(rand(5)+1); // 6 моделей
				}
				else model = "mush_ctz_"+(rand(2)+4); // три модели
	}
	else // для НПС
		{   
		if (CheckAttribute(rCharacter, "Ship.Mode")) // если прописан тип команды
		{
			switch (rCharacter.Ship.Mode)
			{
				case "war": 		
				if(iNation == PIRATE)
				{
					model = "mush_ctz_"+(rand(2)+7);
				}	
				else
				{		
					model = "mush_"+NationShortName(iNation)+"_"+(rand(5)+1); 
				}	
				break; // военные
				case "trade": 		model = "mush_ctz_"+(rand(2)+1); break; // торговцы
				case "pirate": 		model = "mush_ctz_"+(rand(2)+7); break; // пираты
				case "hunter": 		model = "mush_ctz_"+(rand(2)+7); break; // ОЗГ
				case "mercenary": 	model = "mush_ctz_"+(rand(2)+10); break; // наёмники на квестовиках
			}
				}
		else // если не прописан - выставляем согласно нации
				{
			if (iNation == PIRATE) model = "mush_ctz_"+(rand(2)+7);
			else model = "mush_"+NationShortName(iNation)+"_"+(rand(5)+1); // 6 моделей
				}
	}
	return model;
}

//Моделька для абордажного персонажа
string LAi_GetBoardingModel(ref rCharacter, ref ani)
{
	ani = "man";
	int iNation = sti(rCharacter.nation);
	string atr;
	string model;
	
	
	if (CheckAttribute(rCharacter, "GenQuest.CrewSkelMode"))
	{
		model = GetRandSkelModel();
		ani = "skeleton";
		return model;
	}
	if (CheckAttribute(rCharacter, "GenQuest.CrewMementoMode"))
	{
		model = GetRandMementoModel();
		ani = "man";
		return model;
	}	

	if(sti(rCharacter.index) == GetMainCharacterIndex())
	{
				// boal 290904 форма солдат -->
				if (CheckAttribute(rCharacter, "GenQuest.CrewSkelMode"))
				{
						model = GetRandSkelModel();
			ani = "skeleton";
			return model;
		}
		//--> Jason - национальная форма солдат на квестовиках по мультиквесту
		if (CheckAttribute(rCharacter, "questTemp.HWIC.HollEquip") && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
		{
			model = GetRandQuestSoldierModel(HOLLAND);
			ani = "man";
			return model;
		}
		if (CheckAttribute(rCharacter, "questTemp.HWIC.EngEquip") && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_VALCIRIA)
		{
			model = GetRandQuestSoldierModel(ENGLAND);
			ani = "man";
			return model;
		}
		if (CheckAttribute(rCharacter, "questTemp.Mtraxx.CharleePrince")) //команда пиратов Fullback7
			{
			model = "citiz_" + (rand(9) + 41);
			ani = "man";
			return model;
		}
		if (CheckAttribute(rCharacter, "questTemp.CharleePrince"))
			{
			model = "citiz_" + (rand(9) + 41);
			ani = "man";
			return model;
		}
		//<-- форма солдат на квестовиках
				if (isMainCharacterPatented() && sti(Items[sti(rCharacter.EquipedPatentId)].TitulCur) > 1) //форма только со звания капитан
				{
						atr = "boardingModel.enemy";
						iNation = sti(Items[sti(rCharacter.EquipedPatentId)].Nation);
				}
				else
				{
						atr = "boardingModel.player";
				}
				// boal 290904 форма солдат <--
	}
	else
		{   //boal -->
		if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "Trade")
		{
						atr = "boardingModel.merchant";
				}
		else
				{//boal <--
			if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "mercenary")
			{ // Jason
				model = GetRandQuestMercenaryModel();
				ani = "man";
				return model;
			}
			else
			{
				atr = "boardingModel.enemy";
			}
		}
	}
	
	if (iNation < 0) iNation = PIRATE;
	//eddy. замаскировавшися пиратов тоже надо учитывать
	if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "Pirate" && !IsMainCharacter(rCharacter)) iNation = PIRATE;
	Nations[iNation].boardingModel.player = "";
	Nations[iNation].boardingModel.enemy = "";
		
	aref models;
	makearef(models, Nations[iNation].(atr));
	int num = GetAttributesNum(models);
	if(num <= 0) return "";
	int i = rand(num - 1);
	atr = GetAttributeName(GetAttributeN(models, i));
	model = models.(atr);
	atr = atr + ".ani";
	if(CheckAttribute(models, atr))
	{
		if(models.(atr) != "")
		{
			ani = models.(atr);
		}
	}
	return model;
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
void BRD_SetLocationForFight(string deckID, int locID, ref echr, bool IsFort)
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
		if(CheckAttribute(&RealShips[sti(mchr.Ship.Type)], "DeadSailors.SailorsBoardingBonus"))
		{
			fShipBonus = stf(RealShips[sti(mchr.Ship.Type)].DeadSailors.SailorsBoardingBonus) / 100.0;
		}
	}

	exp += fShipBonus;
	moral = 0;
	if(CheckAttribute(mchr, "ship.crew.morale"))
	{
		moral = (stf(mchr.ship.crew.morale) - MORALE_NORMAL)/(MORALE_MAX - MORALE_MIN);
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
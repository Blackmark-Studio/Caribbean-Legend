
// строковая дата, день_мес
string LastSpeakDate()
{
    return environment.date.day + " " + environment.date.month;
}
// Для диалогов НПС -->
string GetNPCQuestDate(ref npchar, string _type)
{
    if (!CheckAttribute(npchar, "QuestDate." + _type))
    {
        npchar.QuestDate.(_type) = "";
    }
    return npchar.QuestDate.(_type);
}
void SetNPCQuestDate(ref npchar, string _type)
{
    npchar.QuestDate.(_type) = LastSpeakDate();
}
bool CheckNPCQuestDate(ref npchar, string _type)
{
    if (GetNPCQuestDate(npchar, _type) != LastSpeakDate())
    {
        return true;
    }
    return false;
}
// Для ГГ <--
void SaveCurrentQuestDateParam(string _quest)
{ // запись даты получения квеста
    aref  arQ;
    makearef(arQ, PChar.(_quest));
    
    arQ.control_day = GetDataDay();
    arQ.control_month = GetDataMonth();
    arQ.control_year = GetDataYear();
    arQ.control_time = GetTime();
}
int GetQuestPastMonthParam(string _quest)
{
    aref  arQ;
    makearef(arQ, PChar.(_quest));

    return GetPastTime("month", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), stf(arQ.control_time),GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
}
int GetQuestPastDayParam(string _quest)
{
    aref  arQ;
    makearef(arQ, PChar.(_quest));
    if (CheckAttribute(PChar, _quest + ".control_year"))
    {
    	return GetPastTime("day", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), stf(arQ.control_time),GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
	} 
	return 0;   	
}
int GetQuestPastTimeParam(string _quest)
{
    aref  arQ;
    makearef(arQ, PChar.(_quest));
    if (CheckAttribute(PChar, _quest + ".control_year"))
    {
    	return GetPastTime("hour", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), stf(arQ.control_time), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
	}  
	return 0;
}
//navy -->
//Ввел ещё одну функцию, т.к. нужны прошедшие минуты.
int GetQuestPastMinutesParam(string _quest)
{
    aref  arQ;
    makearef(arQ, PChar.(_quest));
    if (CheckAttribute(PChar, _quest + ".control_year"))
    {
    	return GetPastTime("minute", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), stf(arQ.control_time), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
	}
	return 0;
}
//navy <--

// eddy
// ************* для неписей.
void SaveCurrentNpcQuestDateParam(ref _character, string _quest)
{ // запись даты получения квеста
    aref  arQ;
    makearef(arQ, _character.(_quest));

    arQ.control_day = GetDataDay();
    arQ.control_month = GetDataMonth();
    arQ.control_year = GetDataYear();
    arQ.control_time = GetTime();
}

int GetNpcQuestPastDayParam(ref _character, string _quest)
{
    aref  arQ;
    makearef(arQ, _character.(_quest));
    if (CheckAttribute(_character, _quest + ".control_year"))
    {
        return GetPastTime("day", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), 0,GetDataYear(), GetDataMonth(), GetDataDay(), 0);
    }
    else {return 0;}
}

int GetNpcQuestPastDayWOInit(ref _character, string _quest)
{
    aref  arQ;
    makearef(arQ, _character.(_quest));
    if (CheckAttribute(_character, _quest + ".control_year"))
    {
        return GetPastTime("day", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), 0,GetDataYear(), GetDataMonth(), GetDataDay(), 0);
    }
    else {return 1000;}  // если нет ветки, то это значит черти когда было дело
}

int GetNpcQuestPastTimeParam(ref _character, string _quest)
{
    aref  arQ;
    makearef(arQ, _character.(_quest));
    if (CheckAttribute(_character, _quest + ".control_year"))
    {
    	return GetPastTime("hour", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), sti(arQ.control_time), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
	}
	return 0;
}
int GetNpcQuestPastMinutesParam(ref _character, string _quest)
{
    aref  arQ;
    makearef(arQ, _character.(_quest));
    if (CheckAttribute(_character, _quest + ".control_year"))
    {
    	return GetPastTime("minute", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), stf(arQ.control_time), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
	}
	return 0;
}

int GetNpcQuestPastMonthParam(ref _character, string _quest)
{
    aref  arQ;
    makearef(arQ, _character.(_quest));
    if (CheckAttribute(_character, _quest + ".control_year"))
    {
        return GetPastTime("month", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), 0,GetDataYear(), GetDataMonth(), GetDataDay(), 0);
    }
    else {return 0;}
}
// *************


// Поместить непися в компаньоны и тут же отправить его на выход из текущей локации.
void CharacterIntoCompanionAndGoOut(ref _mainCharacter, ref _compCharacter, string _group, string _locator, int _timeToGoOut, bool _compRemove)
{
    if (!bDisableFastReload) //чтобы не снимать запрет, если он установлен другим методом
	{
		bDisableFastReload = true;
		_mainCharacter.GenQuest.CallFunctionParam.CharacterIntoCompanion.FastReload = true;
	}
	if (_group == "")    {_group = "reload";}
    if (_locator == "")
    {
    	float locx, locy, locz;
        GetCharacterPos(_compCharacter, &locx, &locy, &locz);
        _locator = LAi_FindNearestFreeLocator(_group, locx, locy, locz);
    }
    LAi_ActorGoToLocation(_compCharacter, _group, _locator, "none", "", "", "", _timeToGoOut);
    _mainCharacter.GenQuest.CallFunctionParam = "Character_into_companion";
    _mainCharacter.GenQuest.CallFunctionParam.CharacterIntoCompanion.Id = _compCharacter.id;
    _mainCharacter.GenQuest.CallFunctionParam.CharacterIntoCompanion.Remove = _compRemove;
    DoQuestCheckDelay("CallFunctionParam", _timeToGoOut);
}

void Character_into_companion()    // относится к методу выше.
{
    ref NPChar = characterFromID(PChar.GenQuest.CallFunctionParam.CharacterIntoCompanion.Id);
    SetCompanionIndex(pchar, -1, getcharacterIndex(PChar.GenQuest.CallFunctionParam.CharacterIntoCompanion.Id));
    if (PChar.GenQuest.CallFunctionParam.CharacterIntoCompanion.Remove == false)    {SetCharacterRemovable(npchar, false);}
	//снимать запрет, только если он установлен этим методом
	if (CheckAttribute(PChar, "GenQuest.CallFunctionParam.CharacterIntoCompanion.FastReload")) bDisableFastReload = false;
}

string GetBookData(int day, int mn, int year)
{
	string result = "";

	if (day < 10)
	{
	    result = result + "0";
	}
	result = result + day + ".";
	if (mn < 10)
	{
	    result = result + "0";
	}
	result = result + mn + "." + year;

    return result;
}

// репутация плохого парня с границами
bool isBadReputation(ref _pchar, int _rep)
{
    if (GetCharacterPerkUsing(_pchar, "Trustworthy") || sti(_pchar.reputation.nobility) >= _rep)
    {
        return false;// good guy
    }
    return true;// bad guy
}

// --> ugeen  - генерация карт островов в сундуке каюты во время абордажа   07.07.09
void FillCabinBoxMap(ref _location, int _probability)
{
	int 	i;
	string  itemID, groupID;
    ref     itm;
	
	for (i=0; i<ITEMS_QUANTITY; i++)
	{	
		makeref(itm,Items[i]);
		if(CheckAttribute(itm, "ID") && CheckAttribute(itm, "groupID"))
		{
			itemID = itm.id;
			groupID = itm.groupID;
			if(groupID == MAPS_ITEM_TYPE && itm.mapType == "")
			{
				if(rand(_probability) == 1) 
				{
					_location.box1.items.(itemID) = 1;
					return;
				}
			}
		}		
	}
}
//<-- ugeen

//ugeen --> заполнить сундук в трюме квестовым барахлом
void FillQuestHoldBox(ref _location)
{
	_location.box1 = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear()); // нужно, чтоб не перетерлось
	
	int nShipType = sti(pchar.ship.type);

	if(CheckAttribute(pchar,"GenQuest.CaptainComission.CanFindChest"))
	{
		if(nShipType == sti(pchar.GenQuest.CaptainComission.ShipType) && !CheckAttribute(pchar,"GenQuest.CaptainComission.Treasure"))
		{
			Log_QuestInfo("Устанавливаем сундуки");
			//DeleteAttribute(_location, "box1");
			if(CheckAttribute(_location,"box1.items.chest")) _location.box1.items.chest = sti(_location.box1.items.chest)+3;
			else _location.box1.items.chest = 3;
			pchar.GenQuest.CaptainComission.Treasure = true;
		}	
	}
}
// <-- ugeen

// заполнить сундук каюты во время абордажа
void FillAboardCabinBox(ref _location, ref _npchar)
{
    int     iTemp;
    bool    ok;
	float   nLuck;
	int 	iNation;
	int     iRnd; 
	string amap, amulet; // dlc
    string tag = _location.id + _npchar.id + _npchar.name;

	_location.box1 = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear()); // нужно, чтоб не перетерлось
	// нужно отметить, что в сундуке сгенерятся рандомные вещи, этот код срабатывает потом и правит токо деньги
	
	ok = true;
	// заготовка под квест

	// маленькая пасхалка от меня -> ugeen  17.06.09 "Кoлecо Фoртуны"
	if (CheckAttribute(_npchar, "Ship.Name") && _npchar.Ship.Name == StringFromKey("QuestsUtilite_1") )
	{
		DeleteAttribute(_location, "box1");
		if(hrand(100, tag) > 85)
		{		
			if(rand(1) == 0) { _location.box1.items.jewelry1 = rand(1500) + 461; }
			if(rand(1) == 0) { _location.box1.items.jewelry2 = rand(800) + 1214; }
			if(rand(1) == 0) { _location.box1.items.jewelry3 = rand(2210) + 750; }
			if(rand(1) == 0) { _location.box1.items.jewelry4 = rand(3450) + 280; }
			if(rand(1) == 0) { _location.box1.items.jewelry5 = rand(2471) + 370; }
			iRnd = hrand(4, tag);
			switch (iRnd)
			{
				case 0:
					_location.box1.items.amulet_6 = 1; 
				break;
				case 1:
					_location.box1.items.amulet_9 = 1; 
				break;
				case 2:
					_location.box1.items.obereg_3 = 1; 
				break;
				case 3:
					_location.box1.items.amulet_8 = 1; 
				break;
				case 4:
					_location.box1.items.indian_5 = 1; 
				break;
			}			
		}
		else
		{
			if(rand(1) == 0) { _location.box1.items.mineral4 = rand(118) + 85; }
			_location.box1.items.mineral5 = rand(78) + 115;
			if(rand(1) == 0) { _location.box1.items.mineral8 = rand(86) + 44; }
			_location.box1.items.mineral11 = rand(146) + 131;
		}		
		_location.box1.money = 12560 + rand(1000);
		ok = false;
	}

	// Осады  homo 22/10/06	 
	if (findsubstr(_npchar.id, "SiegeCap_" , 0) != -1)
	{
	    aref aData, itm;
	    makearef(aData, NullCharacter.Siege);
	    string sGroup = "Sea_"+NationShortName(sti(aData.nation))+"SiegeCap_1";
	    ref rchar = Group_GetGroupCommander(sGroup);  //поиск текущего командера, он меняется от убиеня
	    Log_TestInfo( _npchar.id +" == "+ rchar.id);
		if (_npchar.id == rchar.id && CheckAttribute(aData, "loot"))
		{
	        DeleteAttribute(_location, "box1");
	        _location.box1.money = sti(aData.loot);
	        _location.box1.items.potionrum = 3;
	        _location.box1.items.potionwine = 1;
	        string idmap = "map_"+aData.island;
            if (Items_FindItem(idmap, &itm) != -1)
            {
                _location.box1.items.(idmap) = 1;
            }
			if (hrand(4, tag) == 1 && CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты, 20% 250912
			{
				amap = SelectAdmiralMaps();
				if (amap != "") _location.box1.items.(amap)	= 1;
			}
			if (hrand(4, tag) == 2 && sti(RealShips[sti(_npchar.ship.type)].Class) < 2) _location.box1.items.Hat5 = 1;

	        ok = false;
		}
	}
	//homo =>
    if (findsubstr(_npchar.id, "_QuestMerchant" , 0) != -1)
    {
        if (trap)
        {
            DeleteAttribute(_location, "box1");
            _location.box1.money = (hRand(30, tag)+1) * 40;
            _location.box1.items.blade_13 = 1;
			if (hrand(4, tag) == 2 && CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты
			{
				amap = SelectAdmiralMaps();
				if (amap != "") _location.box1.items.(amap)	= 1;
			}
            ok = false;
        }
    }
    
    if (_npchar.id == "Head_of_Gold_Squadron" )
    {
        DeleteAttribute(_location, "box2");
        _location.box2.money = 2212;
		if (!CheckAttribute(pchar, "questTemp.MapBest")) { // mitrokosta отличная карта без НИ
			_location.box2.items.map_best = 1;
			pchar.questTemp.MapBest = true;
		} else {
        _location.box2.items.map_normal = 1;
		}
		
		if(hrand(100, tag) > 75)
		{		
			if(rand(1) == 0) _location.box1.items.jewelry1 = rand(1200) + 122;
			if(rand(1) == 0) _location.box1.items.jewelry2 = rand(461)  + 225;
			if(rand(1) == 0) _location.box1.items.jewelry3 = rand(515)  + 750;
			if(rand(1) == 0) _location.box1.items.jewelry4 = rand(346)  + 311;
			if(rand(1) == 0) _location.box1.items.jewelry5 = rand(678)  + 420;
			if(rand(1) == 0) _location.box1.items.hat5 = 1;
		}	
		if (CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты
		{
			amap = SelectAdmiralMaps();
			if (amap != "") _location.box1.items.(amap)	= 1;
		}
        ok = false;

    }
    //homo <=

	// Jason: укладка важных предметов и просто вкусных пряников в сундуки квестовых кэпов.
	//работорговец, 2 эпизод
	if (_npchar.id == "CaptainSlaveAttack_2" && CheckAttribute(PChar, "questTemp.Slavetrader"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 20000;
		_location.box1.items.talisman8 = 1;
        ok = false;
	}
	//работорговец, письмо, 4 эпизод
	if (_npchar.id == "CapBrigAttack" && CheckAttribute(PChar, "questTemp.Slavetrader"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 5500;
		_location.box1.items.letter_1 = 1;
		ChangeItemDescribe("letter_1", "itmdescr_letter_1");
        ok = false;
	}
	//работорговец, линкор
	if (_npchar.id == "GaleonCap" && CheckAttribute(PChar, "questTemp.Slavetrader"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 2350;
		_location.box1.items.jewelry5 = 1000;
		if (CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты
		{
			amap = SelectAdmiralMaps();
			if (amap != "") _location.box1.items.(amap)	= 1;
		}
		DeleteAttribute(_location, "box2");
		_location.box2.items.obereg_6 = 1;
		_location.box2.items.mineral2 = 28;
		_location.box2.items.mineral11 = 34;
		_location.box2.items.mineral18 = 3;
		_location.box2.items.mineral20 = 31;
		_location.box2.items.potion7 = 1;
		_location.box2.items.mineral31 = 2; //заговоренная кость
		DeleteAttribute(_location, "box3");
		_location.box3.items.mineral4 = 2;
		_location.box3.items.mineral12 = 10;
		_location.box3.items.mineral14 = 58;
		_location.box3.items.talisman16 = 1; //золотой нож
		_location.box3.items.mineral1 = 12;
		_location.box3.items.berserker_potion = 1;
        ok = false;
	}
	
	//малява курьер
	if (_npchar.id == "CureerAttack")
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 1000;
        _location.box1.items.jewelry1 = 50+rand(200);
        _location.box1.items.jewelry2 = 50+rand(100);
        _location.box1.items.jewelry3 = 50+rand(100);
        _location.box1.items.jewelry4 = 50+rand(100);
        _location.box1.items.jewelry5 = 50+rand(80);
        _location.box1.items.jewelry40 = 50+rand(100);
		_location.box1.items.jewelry41 = 50+rand(160);
        _location.box1.items.jewelry47 = 50+rand(150);
		_location.box1.items.jewelry48 = rand(40);
		_location.box1.items.jewelry46 = rand(200);
		DeleteAttribute(_location, "box2");
		iRnd = rand(5);
        switch (iRnd)
        {
            case 0:
                _location.box2.items.cirass2 = 1; 
            break;
            case 1:
                _location.box2.items.spyglass3 = 1; 
            break;
            case 2:
                _location.box2.items.pistol5 = 1; 
            break;
            case 3:
                _location.box2.items.blade_10 = 1; 
            break;
            case 4:
                _location.box2.items.blade_15 = 1; 
            break;
            case 5:
                _location.box2.items.pistol4 = 1; 
            break;
        }			
        ok = false;
	}
	// ложный след, галеон
	if (_npchar.id == "FalseTraceCap")
	{
		DeleteAttribute(_location, "box1");
		_location.box1.money = 15000;
		_location.box1.items.gold_dublon = 100;
		_location.box1.items.recipe_totem_01 = 1;
		_location.box1.items.totem_01 = 1;
        ok = false;
	}
	// карибские нравы, пуэбла
	if (_npchar.id == "PueblaCap")
	{
		DeleteAttribute(_location, "box1");
		_location.box1.money = 5000;
		_location.box1.items.gold_dublon = 20;
		_location.box1.items.spyglass2 = 1;
		_location.box1.items.mushket1 = 1; // patch-6
		DeleteAttribute(_location, "box2");
		_location.box2.items.rat_poison = 1; // belamour legendary edition
		_location.box2.items.recipe_totem_06 = 1;
		_location.box2.items.totem_06 = 1;
        ok = false;
	}
	//Голландский Гамбит
	//серебряный конвой по английскому варианту
	if (_npchar.id == "SilverCap2" && CheckAttribute(PChar, "questTemp.HWIC.Eng"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 2000;
		_location.box1.items.gold_dublon = 80;
		_location.box1.items.clock1 = 1;
		_location.box1.items.mushket3 = 1; // patch-5
        ok = false;
	}
	
	//Мейфенг по английскому варианту
	if (_npchar.id == "Lucas" && CheckAttribute(PChar, "questTemp.HWIC.Eng"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 20000;
		_location.box1.items.pistol4 = 1;
		_location.box1.items.obereg_7 = 1;
		_location.box1.items.obereg_5 = 1;
		_location.box1.items.jewelry8 = 5;
		_location.box1.items.jewelry7 = 2;
		_location.box1.items.jewelry11 = 1;
		_location.box1.items.gold_dublon = 145;
		_location.box1.items.potion7 = 1;
        ok = false;
	}
	
	//Валькирия без Флитвуда - против всех
	if (_npchar.id == "ValCap" && CheckAttribute(PChar, "questTemp.HWIC.Self"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 200000;//выкуп за Аби
		_location.box1.items.gold_dublon = 175;
		_location.box1.items.obereg_7 = 1;
		_location.box1.items.jewelry8 = 5;
		_location.box1.items.clock1 = 1;
		_location.box1.items.berserker_potion = 1;
        ok = false;
	}
	
	// Пиратская Сага
	// корвет Донована
	if (_npchar.id == "Donovan" && CheckAttribute(PChar, "questTemp.Saga"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 25000;//
		_location.box1.items.gold_dublon = 250;
		_location.box1.items.cirass7 = 1;
		DeleteAttribute(_location, "box2");
		_location.box2.items.recipe_totem_03 = 1;
		_location.box2.items.totem_03 = 1;
		_location.box2.items.indian_7 = 1;
        ok = false;
	}
	// полакр Марлин
	if (_npchar.id == "Cap_Marlin" && CheckAttribute(PChar, "questTemp.Saga"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 12000;
		_location.box1.items.gold_dublon = 100;
		_location.box1.items.map_terks = 1;
		_location.box1.items.amulet_1 = 1;
		_location.box1.items.recipe_totem_07 = 1;
		_location.box1.items.totem_07 = 1;
		if (CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты
		{
			amap = SelectAdmiralMaps();
			if (amap != "") _location.box1.items.(amap)	= 1;
		}
		DeleteAttribute(_location, "box2");
		_location.box2.items.jewelry17 = 20;
		_location.box2.items.jewelry18 = 15;
		_location.box2.items.jewelry1 = 10;
        ok = false;
	}
	// корвет Бродяги
	if (_npchar.id == "Saga_Vagrant" && CheckAttribute(PChar, "questTemp.Saga"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 15000;//
		_location.box1.items.gold_dublon = 50;
		_location.box1.items.letter_chad_1 = 1;
		ChangeItemDescribe("letter_chad_1", "itmdescr_letter_vargant");
		if (CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты
		{
			amap = SelectAdmiralMaps();
			if (amap != "") _location.box1.items.(amap)	= 1;
		}
        ok = false;
	}
	// Джекман, Центурион
	if (_npchar.id == "Jackman" && CheckAttribute(PChar, "questTemp.Saga"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 50000;//
		_location.box1.items.gold_dublon = 100;
		_location.box1.items.map_half_blaze = 1; // половинка карты
		_location.box1.items.splinter_nh = 1; // осколок календаря
		_location.box1.items.recipe_totem_10 = 1;
		_location.box1.items.map_normal = 1;
		if (CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты 250912
		{
			amap = SelectAdmiralMaps();
			if (amap != "") _location.box1.items.(amap)	= 1;
		}
		DeleteAttribute(_location, "box2");
		_location.box2.items.gold_dublon = 250;
		_location.box2.items.witches_hammer = 1; //молот ведьм
		_location.box2.items.letter_parol = 1; // записка с паролем на рудник
		_location.box2.items.map_bermudas = 1;
		_location.box2.items.map_jam = 1;
		_location.box2.items.obereg_8 = 1;
		_location.box2.items.indian_9 = 1; 
		_location.box2.items.potion7 = 1;
		_location.box2.items.berserker_potion = 3;
        ok = false;
	}

	// Моллиган, Устрица
	if (_npchar.id == "Molligan" && CheckAttribute(PChar, "questTemp.Saga"))
	{
		DeleteAttribute(_location, "box1");
		_location.box1.money = 5000;
		_location.box1.items.gold_dublon = 100;
		_location.box1.items.jewelry16 = 1;
		_location.box1.items.tailor_tool = 1; // портняжный набор
		if (CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты
		{
			amap = SelectAdmiralMaps();
			if (amap != "") _location.box1.items.(amap)	= 1;
		}
		DeleteAttribute(_location, "box2");
		_location.box2.items.gold_dublon = 50;
		_location.box2.items.letter_parol = 1;
		ChangeItemDescribe("letter_parol", "itmdescr_letter_ouster");
		_location.box2.items.indian_5 = 1;
		_location.box2.items.mineral14 = 1;
		_location.box2.items.mineral31 = 1;
        ok = false;
	}

	// Суп из черепахи
	// Мартэн, Вольтижёр
	if (_npchar.id == "Rober" && CheckAttribute(PChar, "questTemp.Terrapin"))
	{
		DeleteAttribute(_location, "box1");
		_location.box1.money = 200000;
		_location.box1.items.Cromvel_depeshe = 1;
		if (CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты
		{
			amap = SelectAdmiralMaps();
			if (amap != "") _location.box1.items.(amap)	= 1;
		}
		ref ritm = ItemsFromID("Cromvel_depeshe");
		ritm.Day = GetAddingDataDay(0,0,429);
		ritm.Month = GetAddingDataMonth(0,0,429);
		ritm.Year = GetAddingDataYear(0,0,429);
		DeleteAttribute(_location, "box2");
		_location.box2.items.totem_04 = 1;
		_location.box2.items.recipe_totem_04 = 1; // patch-9
        ok = false;
	}
	
	// Мартэн, Инфанта
	if (_npchar.id == "RoberCap2")
	{
		DeleteAttribute(_location, "box1");
		_location.box1.money = 12500;
		_location.box1.items.Cromvel_depeshe = 1;
		ritm = ItemsFromID("Cromvel_depeshe");
		ritm.Day = GetAddingDataDay(0,0,397);
		ritm.Month = GetAddingDataMonth(0,0,397);
		ritm.Year = GetAddingDataYear(0,0,397);
		if (CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты
		{
			amap = SelectAdmiralMaps();
			if (amap != "") _location.box1.items.(amap)	= 1;
		}
		DeleteAttribute(_location, "box2");
		_location.box2.items.totem_04 = 1;
		_location.box2.items.recipe_totem_04 = 1; // patch-9
        ok = false;
	}
	
	// эскадра Кромвеля, мановар 141012
	if (_npchar.id == "Cromvel_cap_1")
	{
		DeleteAttribute(_location, "box1");
		_location.box1.money = 30000;
		_location.box1.items.gold_dublon = 200; // Captain Beltrop, 18.02.2021, было пропущено слово items, из-за чего в сундуке были только деньги
		_location.box1.items.map_normal = 1;
		_location.box1.items.pistol8 = 1;
		_location.box1.items.harpoon = 5;
		_location.box1.items.GunEchin = 10;
		_location.box1.items.Hat5 = 1;
		DeleteAttribute(_location, "box2");
		_location.box2.items.bussol = 1;
		_location.box2.items.clock2 = 1;
        ok = false;
	}
	
	// Защита Сен-Пьера, мановар
	if (_npchar.id == "SPsiege_cap_1")
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 100000;
		_location.box1.items.Chest = 2;
		_location.box1.items.map_martiniqua = 1;
		_location.box1.items.mushket3 = 1;
		if (MOD_SKILL_ENEMY_RATE > 7) _location.box1.items.cirass4 = 1; 
		if (MOD_SKILL_ENEMY_RATE < 7) _location.box1.items.cirass3 = 1; 
		if (CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты
		{
			amap = SelectAdmiralMaps();
			if (amap != "") _location.box1.items.(amap)	= 1;
		}
		DeleteAttribute(_location, "box2");
		_location.box2.items.bussol = 1;
		_location.box2.items.clock2 = 1;
		_location.box2.items.cannabis7 = 1; // мангароса
		_location.box2.items.totem_11 = 1;
		_location.box2.items.recipe_totem_11 = 1; 
        ok = false;
	}
	// Страж Истины
	// ТГ у Сан-Антонио
	if (_npchar.id == "Diegohaleon_cap")
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 10000;
		_location.box1.items.Chest = 1;
		_location.box1.items.map_cuba = 1;
		_location.box1.items.blade_17 = 1;
		if (CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты
		{
			amap = SelectAdmiralMaps();
			if (amap != "") _location.box1.items.(amap)	= 1;
		}
		DeleteAttribute(_location, "box2");
		_location.box2.items.jewelry6 = 200;
		_location.box2.items.jewelry10 = 4;
		_location.box2.items.berserker_potion = 1;
        ok = false;
	}
	// флагман эскадры Диего
	if (_npchar.id == "GOT_catochecap_1")
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 100000;
		_location.box1.items.Chest = 3;
		_location.box1.items.icollection = 2;
		_location.box1.items.map_beliz = 1;
		_location.box1.items.cirass7 = 1;
		if (CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты
		{
			amap = SelectAdmiralMaps();
			if (amap != "") _location.box1.items.(amap)	= 1;
		}
		DeleteAttribute(_location, "box2");
		_location.box2.items.bussol = 1;
		_location.box2.items.clock2 = 1;
		_location.box2.items.jewelry2 = 100;
		_location.box2.items.cannabis7 = 1; // мангароса
		_location.box2.items.talisman6 = 1;
        ok = false;
	}
	
	// фрегат Патерсона - Фортуна
	if (_npchar.id == "Willy")
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 100000;
		_location.box1.items.Chest = 5;
		_location.box1.items.map_beliz = 1;
		_location.box1.items.cirass7 = 1;
		if (CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты
		{
			amap = SelectAdmiralMaps();
			if (amap != "") _location.box1.items.(amap)	= 1;
		}
		DeleteAttribute(_location, "box2");
		_location.box2.items.bussol = 1;
		_location.box2.items.clock2 = 1;
		_location.box2.items.jewelry2 = 100;
		_location.box2.items.cannabis7 = 1; // мангароса
		_location.box2.items.potion7 = 1;
        ok = false;
	}
	
	//Контркурьер, губерский генер
	if (_npchar.id == "ContraCureerCap" && CheckAttribute(PChar, "GenQuest.TakePostcureer"))
	{
		 DeleteAttribute(_location, "box1");
        _location.box1.money = rand(10000);
		_location.box1.items.gold_dublon = rand(50);
		_location.box1.items.chest = hrand(2, tag);
		amulet = SelectRandomArtefact(3, tag);
		_location.box1.items.(amulet) = 1;
		_location.box1.items.ContraPostLetters = 1;
        ok = false;
	}
	
	//Контрарсенал, губерский генер
	if (_npchar.id == "ContraCureerCap" && CheckAttribute(PChar, "GenQuest.TakeArsenalship"))
	{
		 DeleteAttribute(_location, "box1");
        _location.box1.money = rand(10000);
		_location.box1.items.gold_dublon = rand(50);
		amulet = SelectRandomArtefact(1, tag);
		_location.box1.items.(amulet) = 1;
		switch (hrand(6, tag))
		{
			case 0: _location.box1.items.pistol3 = 1; break;
			case 1: _location.box1.items.pistol5 = 1; break;
			case 2: _location.box1.items.cirass1 = 1; break;
			case 3: _location.box1.items.cirass2 = 1; break;
			case 4: _location.box1.items.cirass6 = 1; break;
			case 5: _location.box1.items.mushket1 = 1; break;
			case 6: _location.box1.items.mushket3 = 1; break;
		}
        ok = false;
	}
	
	//Контрпират, губерский генер
	if (_npchar.id == "ContraCureerCap" && CheckAttribute(PChar, "GenQuest.TakePirateship"))
	{
		 DeleteAttribute(_location, "box1");
        _location.box1.money = rand(15000);
		_location.box1.items.gold_dublon = rand(100);
		_location.box1.items.icollection = hrand(3, tag);
		amulet = SelectRandomArtefact(2, tag);
		_location.box1.items.(amulet) = 1;
		if (hrand(4, "&CCC" + tag) == 1) _location.box1.items.mushket3 = 1;
		else if (hrand(4, "&CCC" + tag) == 3) _location.box1.items.mushket1 = 1;
        ok = false;
	}
	
	//Контрпассажир, губерский генер
	if (_npchar.id == "ContraPassCap" && CheckAttribute(PChar, "GenQuest.TakePassenger"))
	{
		 DeleteAttribute(_location, "box1");
        _location.box1.money = rand(5000);
		_location.box1.items.gold_dublon = rand(30);
		if (hrand(3, tag) == 0) _location.box1.items.mushket1 = 1;
		amulet = SelectRandomArtefact(1, tag);
		_location.box1.items.(amulet) = 1;
		amulet = SelectRandomArtefact(2, tag);
		_location.box1.items.(amulet) = 1;
		amulet = SelectRandomArtefact(3, tag);
		_location.box1.items.(amulet) = 1;
        ok = false;
	}
	
	//Калеуче
	if (_npchar.id == "Kaleuche_khaelroacap")
	{
		 DeleteAttribute(_location, "box1");
        _location.box1.money = 100000;
		_location.box1.items.blade_28 = 1;
		DeleteAttribute(_location, "box2");
		_location.box2.items.gold_dublon = 5000;
        ok = false;
	}
	
	// Addon-2016 Jason, французские миниквесты (ФМК)
	if (_npchar.id == "OilCap2")
	{
		 DeleteAttribute(_location, "box1");
        _location.box1.money = 4500;
		_location.box1.items.obereg_8 = 1;
		_location.box1.items.obereg_1 = 1;
		DeleteAttribute(_location, "box2");
		_location.box2.items.gold_dublon = 15;
        ok = false;
	}
	if (_npchar.id == "FMQN_shorecap")
	{
		 DeleteAttribute(_location, "box1");
        _location.box1.money = 2450;
		_location.box1.items.indian_6 = 1;
		_location.box1.items.amulet_5 = 1;
        ok = false;
	}
	if (_npchar.id == "FMQP_Follower")
	{
		 DeleteAttribute(_location, "box1");
        _location.box1.money = 1800;
		_location.box1.items.gold_dublon = 20;
		_location.box1.items.indian_9 = 1;
		_location.box1.items.amulet_11 = 1;
		_location.box1.items.obereg_2 = 1;
        ok = false;
	}
	// Addon 2016-1 Jason Пиратская линейка
	// полакр Тореро
	if (_npchar.id == "Ignasio" && CheckAttribute(PChar, "questTemp.Mtraxx.Corrida.Logbook"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 25600;
		_location.box1.items.gold_dublon = 155;
		_location.box1.items.map_normal = 1;
        if(GetCharacterItem(PChar, "map_part1") == 0)
            _location.box1.items.map_part1 = 1;
        else if(GetCharacterItem(pchar, "map_full") == 0 && GetCharacterItem(PChar, "map_part2") == 0)
            _location.box1.items.map_part2 = 1;
        _location.box1.items.wolfreeks_book = 1;
        
        ok = false;
	}
	// шхуна Кантавро
	if (_npchar.id == "Cabanos")
	{
		 DeleteAttribute(_location, "box1");
        _location.box1.money = 550;
		_location.box1.items.gold_dublon = 10;
		_location.box1.items.totem_09 = 1;
		_location.box1.items.jewelry8 = 15;
		_location.box1.items.jewelry41 = 1; // патч 17/1
		
		DeleteAttribute(_location, "box2");
		_location.box2.items.clock1 = 1;
		if (hrand(2, tag) == 2) _location.box2.items.cirass3 = 1;
        ok = false;
	}
	// бригантина Утрехт
	if (_npchar.id == "Cap_Utreht")
	{
		 DeleteAttribute(_location, "box1");
        _location.box1.money = 7800;
		_location.box1.items.gold_dublon = 30;
		_location.box1.items.indian_11 = 1;
		_location.box1.items.chest_open = 5;
		_location.box1.items.pistol3 = 1; // патч 17/1
		
		DeleteAttribute(_location, "box2");
		_location.box2.items.purse1 = 1;
		if (hrand(4, tag) == 1) _location.box2.items.pistol2 = 1;
        ok = false;
	}
	// Розбоом
	if (_npchar.id == "Mtr_PasqCap_2")
	{
		 DeleteAttribute(_location, "box1");
        _location.box1.money = 5300;
		_location.box1.items.gold_dublon = 10;
		_location.box1.items.obereg_8 = 1;
		_location.box1.items.pistol5 = 1; // патч 17/1
		_location.box1.items.jewelry42 = 1; // патч 17/1
		_location.box1.items.map_Curacao = 1;
		
		DeleteAttribute(_location, "box2");
		_location.box2.items.spyglass2 = 1;
		if (hrand(3, tag) == 1) _location.box2.items.blade_16 = 1;
        ok = false;
	}
	// голландец по Игнасио
	if (_npchar.id == "Mtr_IgnasioSeaCap_1")
	{
		 DeleteAttribute(_location, "box1");
        _location.box1.money = 10800;
		_location.box1.items.gold_dublon = 40;
		_location.box1.items.obereg_1 = 1;
		_location.box1.items.clock2 = 1;
		_location.box1.items.rat_poison = 1;
		
        ok = false;
	}
	// Торо де Оро
	if (_npchar.id == "Mtr_GoldCap_2")
	{
		 DeleteAttribute(_location, "box1");
        _location.box1.money = 15000;
		_location.box1.items.chest = 1;
		_location.box1.items.obereg_10 = 1;
		_location.box1.items.amulet_8 = 1;
		if (hrand(3, tag) == 3) _location.box1.items.spyglass4 = 1;
		
        ok = false;
	}
	// Jason НСО
	// флагман испанской эскадры у Порт Пренса
	if (_npchar.id == "PatriaPP_Seacap_1")
	{
		 DeleteAttribute(_location, "box1");
        _location.box1.money = 20000;
		_location.box1.items.gold_dublon = 200;
		_location.box1.items.obereg_9 = 1;
		_location.box1.items.amulet_7 = 1;
		_location.box1.items.indian_7 = 1;
		
		if (CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты
		{
			amap = SelectAdmiralMaps();
			if (amap != "") _location.box1.items.(amap)	= 1;
		}
        ok = false;
	}
	// ТГ добавочный у Порт Пренса
	if (_npchar.id == "PatriaPP_Seacap_add")
	{
		 DeleteAttribute(_location, "box1");
        _location.box1.money = 5000;
		_location.box1.items.mushket2 = 1;
		_location.box1.items.indian_1 = 1;
		
        ok = false;
	}
	// флагман эскадры голландцев у сан-мартина
	if (_npchar.id == "Patria_SanMartinCap_1")
	{
		 DeleteAttribute(_location, "box1");
        _location.box1.money = 7000;
		_location.box1.items.cannabis7 = 1; // мангароса
		_location.box1.items.indian_10 = 1;
		
        ok = false;
	}
	// флагман эскадры-погони голландцев 
	if (_npchar.id == "Patria_DiplomatCap_1")
	{
		 DeleteAttribute(_location, "box1");
        _location.box1.money = 13000;
		_location.box1.items.obereg_10 = 1;
		_location.box1.items.harpoon = 100;
		
        ok = false;
	}
	// Олифант 
	if (_npchar.id == "Patria_SiegeCap_1")
	{
		 DeleteAttribute(_location, "box1");
        _location.box1.money = 50000;
		_location.box1.items.Chest = 3;
		_location.box1.items.map_nevis = 1;
		_location.box1.items.cirass3 = 1;
		_location.box1.items.berserker_potion = 2;
		if (CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты
		{
			amap = SelectAdmiralMaps();
			if (amap != "") _location.box1.items.(amap)	= 1;
		}
		
        ok = false;
	}
	// флагман испанцев в осаде
	if (_npchar.id == "Patria_SiegeCap_4")
	{
		 DeleteAttribute(_location, "box1");
        _location.box1.money = 25000;
		_location.box1.items.Chest = 1;
		_location.box1.items.obereg_7 = 1;
		_location.box1.items.clock2 = 1;
		_location.box1.items.totem_05 = 1;
		
        ok = false;
	}
	// 1 ост-ндец с рабами
	if (_npchar.id == "PatriaSlaveCap2")
	{
		 DeleteAttribute(_location, "box1");
        _location.box1.money = 10000;
		_location.box1.items.obereg_11 = 1;
		_location.box1.items.obereg_6 = 1;
		_location.box1.items.Mineral30 = 50;
		if (CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты
		{
			amap = SelectAdmiralMaps();
			if (amap != "") _location.box1.items.(amap)	= 1;
		}
		
        ok = false;
	}
	// 2 ост-ндец с рабами
	if (_npchar.id == "PatriaSlaveCap3")
	{
		 DeleteAttribute(_location, "box1");
        _location.box1.money = 12000;
		_location.box1.items.obereg_9 = 1;
		_location.box1.items.indian_6 = 1;
		_location.box1.items.Mineral30 = 50;
		if (CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты
		{
			amap = SelectAdmiralMaps();
			if (amap != "") _location.box1.items.(amap)	= 1;
		}
		
        ok = false;
	}
	// ТГ Стайвесанта Фредерик
	if (_npchar.id == "Patria_CuracaoCap1_1")
	{
		 DeleteAttribute(_location, "box1");
        _location.box1.money = 30000;
		_location.box1.items.Chest = 2;
		_location.box1.items.cannabis7 = 1; // мангароса
		_location.box1.items.recipe_GunEchin = 1;
		_location.box1.items.GunEchin = 100;
		
        ok = false;
	}
	// Jason Долго и счастливо
	if (_npchar.id == "LH_BarbSeaCap_1")
	{
		 DeleteAttribute(_location, "box1");
        _location.box1.money = 50000;
		_location.box1.items.Chest = 5;
		_location.box1.items.map_bermudas = 1;
		if (CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты
		{
			amap = SelectAdmiralMaps();
			if (amap != "") _location.box1.items.(amap)	= 1;
		}
		DeleteAttribute(_location, "box2");
		_location.box2.items.bussol = 1;
		_location.box2.items.clock2 = 1;
		_location.box2.items.jewelry1 = 30;
		_location.box2.items.jewelry2 = 50;
		_location.box2.items.jewelry3 = 60;
		_location.box2.items.jewelry4 = 40;
		_location.box2.items.cannabis7 = 2; // мангароса
		_location.box2.items.potion7 = 1;
		_location.box2.items.berserker_potion = 1;
		
        ok = false;
	}
	// Бриг торговца по квесту "Деньги на деревьях"
	if (_npchar.id == "SharlieBarbie")
	{
		DeleteAttribute(_location, "box1");
		_location.box1.money = 10000;
		_location.box1.items.gold_dublon = 60;
		
        ok = false;
	}
	// Люггер Хейтер по квесту "Травля Крысы"
	if (_npchar.id == "TK_Heiter")
	{
		DeleteAttribute(_location, "box1");
		_location.box1.money = 1500;
		_location.box1.items.gold_dublon = 10;
        if(GetCharacterItem(PChar, "map_part1") == 0)
            _location.box1.items.map_part1 = 1;
        else if(GetCharacterItem(pchar, "map_full") == 0 && GetCharacterItem(PChar, "map_part2") == 0)
            _location.box1.items.map_part2 = 1;
        
        ok = false;
	}
	// Барк Генрих по квесту "Травля Крысы"
	if (_npchar.id == "TK_Genrih")
	{
		DeleteAttribute(_location, "box1");
		_location.box1.money = 5000;
		_location.box1.items.gold_dublon = 100;
		_location.box1.items.obereg_8 = 1;
		_location.box1.items.obereg_4 = 1;
		
        ok = false;
	}
	// Rebbebion, тяжёлый фрегат Лебрена по "Путеводной звезде
	if (_npchar.id == "PZ_KlemanLebren")
	{
		DeleteAttribute(_location, "box1");
		_location.box1.items.ClementLebrunJournal = 1;
		
        ok = false;
	}
	// Галеон Святое Милосердие
	if (_npchar.id == "SantaMisericordia_cap")
	{
		DeleteAttribute(_location, "box1");
		_location.box1.items.chest = 10;
		_location.box1.items.Reserve_item_02 = 1;
		_location.box2.items.Reserve_item_03 = 1;
		
        ok = false;
	}
	// Бриг по квесту "Торговля по закону"
	if (_npchar.id == "TPZ_Pirate")
	{
		DeleteAttribute(_location, "box2");
		_location.box2.items.potionrum = 100;
		_location.box2.items.potionwine = 100;
		
        ok = false;
	}
	// Бриг Мементо
	if (_npchar.id == "Memento_cap")
	{
		DeleteAttribute(_location, "box1");
		_location.box1.items.Mineral30 = 150;
		_location.box1.items.Memento_Book = 1;
		_location.box1.items.spyglassSP3 = 1;
		
        ok = false;
	}
	
    if (ok) // не квестовый
    {
    	// код для всех
		
    	iTemp = GetCharacterShipClass(_npchar);
		iNation = sti(_npchar.nation);		

		if(iNation == PIRATE)
		{
			nLuck   = GetCharacterSkillToOld(Pchar, SKILL_FORTUNE);			
			if (nLuck > rand(250))  // шанс 1/30 
			{
				if (GetCharacterItem(pchar, "map_part1") == 0)
                    _location.box1.items.map_part1 = 1;
				else if (GetCharacterItem(pchar, "map_full") == 0 && GetCharacterItem(pchar, "map_part2") == 0)
                    _location.box1.items.map_part2 = 1;
			}
			FillCabinBoxMap(_location, 200 - (8 - iTemp) * 5); 
			if(rand(10) == 5) _location.box1.items.Chest_open = 1;
			if(SandBoxMode && rand(9) == 7 && sti(pchar.rank) > 19) _location.box1.items.Hat8 = 1;
		}
		else
		{
			FillCabinBoxMap(_location, 250 - (8 - iTemp) * 5);
		}
		
		if (CheckAttribute(_npchar, "Ship.Mode") && _npchar.Ship.Mode == "Trade")  // торговец
		{
			_location.box1.money = (11 - iTemp) * 200 + rand(11 - iTemp) * 2000 + rand(10)*50 + rand(7 - iTemp) * 4000;
			if(rand(5) > 2)
			{
				_location.box1.items.gold_dublon = rand(10) + 4;
				if(hrand(20, tag) == 15) _location.box1.items.rat_poison = 1;		
			}
			
			if(rand(10) == 1 && sti(RealShips[sti(_npchar.ship.type)].Class) == 3) _location.box1.items.Hat6 = 1;
		}
		else // все остальные
		{
			if(rand(3) == 1) _location.box1.items.gunpowder = 5 + rand(10);
			_location.box1.money = (11 - iTemp) * 90 + rand((11 - iTemp) * 2000);
			if(rand(4) == 1)
			{
				_location.box1.items.gold_dublon = rand(5) + 2;			
			}
		}				
		if (2-sti(RealShips[sti(_npchar.ship.type)].Class) > 0) // 1 класс
		{
			if (hrand(2, tag) == 1 && CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты
			{
				amap = SelectAdmiralMaps();
				if (amap != "") _location.box1.items.(amap)	= 1;
			}
		}
		if (CheckAttribute(_npchar, "Ship.Mode") && _npchar.Ship.Mode == "war" && 2-sti(RealShips[sti(_npchar.ship.type)].Class) == 0) // военный 2 класс
		{
			if (hrand(4, tag) == 1 && CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты
			{
				amap = SelectAdmiralMaps();
				if (amap != "") _location.box1.items.(amap)	= 1;
			}
		}
		if (CheckAttribute(_npchar, "Ship.Mode") && _npchar.Ship.Mode == "war" && 3-sti(RealShips[sti(_npchar.ship.type)].Class) == 0) // военный 3 класс
		{
			if (hrand(6, tag) == 1 && CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты
			{
				amap = SelectAdmiralMaps();
				if (amap != "") _location.box1.items.(amap)	= 1;
			}
		}
		if (CheckAttribute(pchar, "questTemp.Persian.skimitar") && hrand(20, tag) == 5 && 3-sti(RealShips[sti(_npchar.ship.type)].Class) >= 0) // 3 класс и выше. Скимитар - 5% 021012
		{
			_location.box1.items.blade_23 = 1;
		}
		if (CheckAttribute(pchar, "questTemp.Caleuche.SeekAmulet") && hrand(3, tag) == 3) // первый амулет на Калеуче
		{
			_location.box1.items.kaleuche_amulet1 = 1;
		}
		if (CheckAttribute(_npchar, "Ship.Mode") && _npchar.Ship.Mode == "war")
		{
			if(sti(pchar.rank) < 12)
			{
				if(hrand(10, "&SMW_hat" + tag) == 3)) _location.box1.items.hat1 = 1;
				else if(hrand(10, "&SMW_hat" + tag) == 8)) _location.box1.items.hat3 = 1;
			}
			else
			{
				if(hrand(10, "&SMW_hat" + tag) == 3)) _location.box1.items.hat2 = 1;
				else if(hrand(10, "&SMW_hat" + tag) == 8)) _location.box1.items.hat4 = 1;
			}
		}
		// Озги
		if (findsubstr(_npchar.id, "Hunter0" , 0) != -1)
		{
			if(rand(10) == 3 && sti(pchar.rank) > 11) _location.box1.items.hat7 = 1;
		}
		// Джентельмен удачи
		if (findsubstr(_npchar.id, "Follower0" , 0) != -1)
		{
			if(rand(10) == 4 && sti(pchar.rank) > 11) _location.box1.items.hat7 = 1;
		}
		
    } else {
		_location.box1.items.talisman11 = 1 + rand(4);
	}
}

// ugeen --> вычисление ранга квестовых проитвников в зависимости от ранга ГГ и уровня сложности
int SetQuestCharacterRank()
{
	int rank = 25 + makeint(sti(pchar.rank)*(0.1 + MOD_SKILL_ENEMY_RATE));

	return rank;
}
// <-- ugeen

// ==> две функции Эдди для крутизны невероятной.
void FantomMakeCoolSailor(ref _Character, int _ShipType, string _ShipName, int _CannonsType, int _Sailing, int _Accuracy, int _Cannons)
{
    if(_CannonsType >= 0) _Character.Ship.Cannons.Type = _CannonsType;
	_Character.skill.Sailing  = GetCoffDiff(_Sailing, SKILL_MAX);
	_Character.skill.Accuracy = GetCoffDiff(_Accuracy, SKILL_MAX);
	_Character.skill.Cannons  = GetCoffDiff(_Cannons, SKILL_MAX);
    _Character.DontRansackCaptain = true; //квестовые не сдаются
    _Character.SinkTenPercent     = false; // не тонуть при 10%, не убегать в бою
    _Character.AboardToFinalDeck  = true; // абордаж всегда
	_Character.DontClearDead      = true;
	_Character.SaveItemsForDead   = true;
	_Character.AlwaysSandbankManeuver = true;

    _Character.Ship.Type = GenerateShipExt(_ShipType, true, _Character);
    if (_ShipName == "none" || _ShipName == "") SetRandomNameToShip(_Character);
    else _Character.Ship.Name = _ShipName;

    SetBaseShipData(_Character);
    SetCrewQuantityFull(_Character);
    Fantom_SetBalls(_Character, "pirate");

	SetCharacterPerk(_Character, "FastReload");
	SetCharacterPerk(_Character, "HullDamageUp");
	SetCharacterPerk(_Character, "SailsDamageUp");
	SetCharacterPerk(_Character, "CrewDamageUp");
	SetCharacterPerk(_Character, "CriticalShoot");
	SetCharacterPerk(_Character, "LongRangeShoot");
	SetCharacterPerk(_Character, "CannonProfessional");
	SetCharacterPerk(_Character, "ShipDefenseProfessional");
	SetCharacterPerk(_Character, "ShipSpeedUp");
	SetCharacterPerk(_Character, "ShipTurnRateUp");

    DeleteAttribute(_Character, "ship.sails");// убрать дыры на парусах
    DeleteAttribute(_Character, "ship.blots");
    DeleteAttribute(_Character, "ship.masts");// вернуть сбытые мачты
	DeleteAttribute(_Character, "ship.hulls");// вернуть сбитые элементы корпуса
    DeleteAttribute(_Character, "Killer.status"); // снять аттрибут 'был захвачен на абордаж'
    _Character.questTemp.abordage = 0; //снять аттрибут отказа повторного захвата
   	DeleteAttribute(_Character, "Abordage.Enable"); //снять невозможноть абордажа
}

//Jason, функция уменьшенного кулсейлора + скилл защиты и абордажа
void FantomMakeSmallSailor(ref _Character, int _ShipType, string _ShipName, int _CannonsType, int _Sailing, int _Accuracy, int _Cannons, int _Grappling, int _Defence)
{
	if(_CannonsType >= 0) _Character.Ship.Cannons.Type = _CannonsType;
	_Character.skill.Sailing  = GetCoffDiff(_Sailing, SKILL_MAX);
	_Character.skill.Accuracy = GetCoffDiff(_Accuracy, SKILL_MAX);
	_Character.skill.Cannons  = GetCoffDiff(_Cannons, SKILL_MAX);
	_Character.skill.Grappling  = GetCoffDiff(_Grappling, SKILL_MAX);
	_Character.skill.Defence  = GetCoffDiff(_Defence, SKILL_MAX);
	
    _Character.DontRansackCaptain = true; //квестовые не сдаются
    _Character.SinkTenPercent     = false; // не тонуть при 10%, не убегать в бою
    _Character.AboardToFinalDeck  = true; // абордаж всегда
	_Character.AlwaysSandbankManeuver = true;

    _Character.Ship.Type = GenerateShipExt(_ShipType, true, _Character);
    if (_ShipName == "none" || _ShipName == "") {SetRandomNameToShip(_Character)}
    else {_Character.Ship.Name = _ShipName}

    SetBaseShipData(_Character);
    SetCrewQuantityFull(_Character);
    Fantom_SetBalls(_Character, "pirate");

	SetCharacterPerk(_Character, "HullDamageUp");
	SetCharacterPerk(_Character, "SailsDamageUp");
	SetCharacterPerk(_Character, "CrewDamageUp");
	SetCharacterPerk(_Character, "AdvancedBattleState");
	SetCharacterPerk(_Character, "ShipSpeedUp");
	SetCharacterPerk(_Character, "ShipTurnRateUp");
	SetCharacterPerk(_Character, "Doctor1");
	SetCharacterPerk(_Character, "LongRangeGrappling");

    DeleteAttribute(_Character, "ship.sails");// убрать дыры на парусах
    DeleteAttribute(_Character, "ship.blots");
    DeleteAttribute(_Character, "ship.masts");// вернуть сбытые мачты
	DeleteAttribute(_Character, "ship.hulls");// вернуть сбытые элементы корпуса
    DeleteAttribute(_Character, "Killer.status"); // снять аттрибут 'был захвачен на абордаж'
    _Character.questTemp.abordage = 0; //снять аттрибут отказа повторного захвата
   	DeleteAttribute(_Character, "Abordage.Enable"); //снять невозможноть абордажа
}

void FantomMakeCoolFighter(ref _Character, int _Rank, int _Fencing, int _Pistol, string _Blade, string _Gun, string _Bullet, float _AddHP)
{
    _Character.rank = GetCoffDiff(_Rank, 1000);
    _Character.skill.FencingS  = GetCoffDiff(_Fencing, SKILL_MAX);
    _Character.Skill.FencingL  = GetCoffDiff(sti(_Character.skill.FencingL), SKILL_MAX);
    _Character.Skill.FencingH  = GetCoffDiff(sti(_Character.skill.FencingH), SKILL_MAX); 
    _Character.skill.Pistol = GetCoffDiff(_Pistol, SKILL_MAX);
    _Character.skill.Fortune = GetCoffDiff(_Pistol, SKILL_MAX); //zagolski. если умеет хорошо стрелять из пистоля, то умеет и хорошо от него защищаться
	_Character.chr_ai.hp = stf(_Character.chr_ai.hp) + GetCoffDiff(_AddHP, 5000);
	_Character.chr_ai.hp_max = stf(_Character.chr_ai.hp_max) + GetCoffDiff(_AddHP, 5000);
	SetCharacterPerk(_Character, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, даётся ГГ и боссам уровней
	SetCharacterPerk(_Character, "AdvancedDefense");
	SetCharacterPerk(_Character, "CriticalHit");
	SetCharacterPerk(_Character, "Sliding");
	SetCharacterPerk(_Character, "HardHitter");
	DeleteAttribute(_Character, "Items");
	// belamour ДА! Я - ленивая рожа, но всего то 4 пестика :) --->
	if(_Gun == "pistol2" || _Gun == "pistol4" || _Gun == "pistol6" || _Gun == "howdah")
	{SetCharacterPerk(_Character, "GunProfessional");}
	// <--- belamour пистоли выдаются раньше перка, как итог - не могут одеть
	_Character.SuperShooter  = true;
	_Blade = GetGeneratedItem(_Blade);
    GiveItem2Character(_Character, _Blade);
    EquipCharacterbyItem(_Character, _Blade);
    TakeNItems(_Character,"potion1", rand(MOD_SKILL_ENEMY_RATE/2)+1);
    if (MOD_SKILL_ENEMY_RATE > 4) TakeNItems(_Character,"potion2", rand(2)+1);
	TakeNItems(_Character,"potion3", 2);
    if (_Gun != "")
	{
		if(HasSubStr(_Gun, "mushket")) // у мушкетеров отдельная логика экипировки
		{
			SetCharacterPerk(_Character, "Gunman");
			_Character.MushketType = _Gun;
			_Character.MushketBulletType = _Bullet;
			LAi_NPC_MushketerEquip(_Character);
		}
		else
		{
			GiveItem2Character(_Character, _Gun);
			EquipCharacterbyItem(_Character, _Gun);
			LAi_SetCharacterBulletType(_Character,_Bullet);
			LAi_SetCharacterUseBullet(_Character, GUN_ITEM_TYPE, _Bullet);
			string sGunpowder = LAi_GetCharacterGunpowderType(_Character, GUN_ITEM_TYPE);
			if(sGunPowder != "")
			{
				AddItems(_Character, sGunpowder, 30 + rand(20)); // Warship. Порох
			}	
		}
	}

    FaceMaker(_Character);
	CirassMaker(_Character);
    SetNewModelToChar(_Character);  // перерисуем модель на лету
}

int GetCoffDiff(float _num, int _maxRange)
{
	switch (MOD_SKILL_ENEMY_RATE)
	{
		case  1: _num *= 0.5;  break;
		case  2: _num *= 0.6; break;
		case  3: _num *= 0.7; break;
		case  4: _num *= 0.8;  break;
		case  5: _num *= 0.9; break;
		case  6: _num *= 1;    break;
		case  7: _num *= 1.1;  break;
		case  8: _num *= 1.2;  break;
		case  9: _num *= 1.3;  break;
		case 10: _num *= 1.5;  break;
	}
	_num += 0.5;
	if (_num > _maxRange) return _maxRange;
	else return MakeInt(_num);
}
// заполнение сундуков и рандитема по квесту
bool SetLocationQuestRandItem(int _index, aref _location, string _locatorName, aref al) // al - ветка локатора из модели, остальное тоже из обратотки локации
{   // метод редактировать не нужно - все задается в квестах
	string  lastSpawnTimeString;
    int     n;
	string  itemId;
	aref checkAref

	/* Пример
 	pchar.GenQuestRandItem.QC_Port = true;
    pchar.GenQuestRandItem.QC_Port.randitem1 = "pistol6";
    // если нужно чтоб было всегда
	pchar.GenQuestRandItem.QC_Port.stay = true; - тереть потом эту ветку самому по квесту
	
    QC_Port - локация где
    randitem1 - локатор
    pistol6 - предмет
    
    если нужно сразу несколько локаторов, то
    pchar.GenQuestRandItem.QC_Port.randitem1 = "pistol6";
    pchar.GenQuestRandItem.QC_Port.randitem2 = "pistol1";
 	*/
	lastSpawnTimeString = _location.id;
    if (CheckAttribute(pchar , "GenQuestRandItem." + lastSpawnTimeString) && CheckAttribute(pchar , "GenQuestRandItem." + lastSpawnTimeString +"."+_locatorName))
    {
        itemId = pchar.GenQuestRandItem.(lastSpawnTimeString).(_locatorName);
        if (!CheckAttribute(pchar , "GenQuestRandItem." + lastSpawnTimeString +".stay"))
        {
			//--> fix eddy. нельзя было положить в несколько локаторов
			DeleteAttribute(pchar , "GenQuestRandItem." + lastSpawnTimeString + "." + _locatorName); // если токо один раз
			makearef(checkAref,  pchar.GenQuestRandItem.(lastSpawnTimeString));
			if (GetAttributesNum(checkAref) == 0) DeleteAttribute(pchar , "GenQuestRandItem." + lastSpawnTimeString);
        }
        // только один предмет!!!!!!!!!!!!
        n = SetRandItemShow(_index, al, itemId); // вывести 3д модель в лакацию, если модель вообще есть
		if (n != -1)
		{
            Log_TestInfo("SetLocationQuestRandItem");
            lastSpawnTimeString = "LastSpawnTime"+_index;
		    _location.(lastSpawnTimeString) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
            lastSpawnTimeString = "RandItemType"+_index;
        	_location.(lastSpawnTimeString) = n;
            return true;
        }
    }
    
    return false;
}
// загрузить модель
int SetRandItemShow(int _index, aref al, string _itemId)
{
    int     n;
    aref    randItem;
    
    n = Items_FindItem(_itemId, &randItem);
	if (n != -1)
	{
        if (!CheckAttribute(randItem, "model") || randItem.model == "")
    	{
    		Trace("SetRandItemShow: no model for item "+randItem.id);
    		return -1;
    	}
	    Items_LoadModel(&randItemModels[_index],  randItem);
    	SendMessage(&randItemModels[_index], "lffffffffffff", MSG_MODEL_SET_POSITION, makeFloat(al.x), makeFloat(al.y), makeFloat(al.z), makeFloat(al.vx.x), makeFloat(al.vx.y), -makeFloat(al.vx.z), makeFloat(al.vy.x), makeFloat(al.vy.y), -makeFloat(al.vy.z), makeFloat(al.vz.x), makeFloat(al.vz.y), -makeFloat(al.vz.z));

        return n;
    }
    return n;
}

// заполнить сундук
bool SetLocationQuestBox(ref _location, string _locatorName)
{   // метод редактировать не нужно - все задается в квестах
    bool    ok = false;
    string  locId;
    aref    arToBox;
    aref    arFromBox;

    /* Пример
 	pchar.GenQuestBox.Havanna_town_04 = true;
    pchar.GenQuestBox.Havanna_town_04.box1.items.jewelry1 = 4;
    pchar.GenQuestBox.Havanna_town_04.box1.items.mineral2 = 10;
    // если нужны деньги, иначе не заполнять
	pchar.GenQuestBox.Havanna_town_04.box1.money          = 100;
    // если нужно чтоб было всегда
	pchar.GenQuestBox.Havanna_town_04.stay = true; - тереть потом эту ветку самому по квесту

    Havanna_town_04 - локация где
    box1 - локатор
    items - список предметов
    
    если нужно сразу несколько локаторов, то
    pchar.GenQuestBox.Havanna_town_04.box2.items.jewelry1 = 34;
 	*/
 	locId  = _location.id;
    if (CheckAttribute(pchar , "GenQuestBox." + locId) && CheckAttribute(pchar , "GenQuestBox." + locId + "." + _locatorName))
    {
        Log_TestInfo("SetLocationQuestBox");

        makearef(arToBox, _location.(_locatorName));
        makearef(arFromBox, pchar.GenQuestBox.(locId).(_locatorName));
        CopyAttributes(arToBox, arFromBox);
        _location.(_locatorName) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear()); // таймер, чтоб не затерлись рандомом при выходе из локации
        if (!CheckAttribute(pchar , "GenQuestBox." + locId +".stay"))
        {
			//--> fix eddy. нельзя было положить в несколько локаторов
			DeleteAttribute(pchar , "GenQuestBox." + locId + "." + _locatorName); // если токо один раз
			makearef(arToBox,  pchar.GenQuestBox.(locId));
			if (GetAttributesNum(arToBox) == 0) DeleteAttribute(pchar , "GenQuestBox." + locId);
        }
        return true;
    }
    return false;
}

// ==> Метод открытия\закрытия локаторов релоад. Если _flag=true - закрыть локатор, если _flag=false - открыть.
void LocatorReloadEnterDisable(string _locationID, string _locator, bool _flag)
{
    aref arDis, arRld;
	makearef(arRld, Locations[FindLocation(_locationID)].reload);
	int	Qty = GetAttributesNum(arRld);
	for (int i=0; i<Qty; i++)
	{
		arDis = GetAttributeN(arRld, i);
        if (arDis.name == _locator)
        {
    		if (_flag) arDis.disable = 1;
    		else DeleteAttribute(arDis, "disable");
            break;
        }
	}
}

//===>>> Функции по работе с диалоговыми файлами. Эдди. ================================================================
// == _strNormal - обычная строка диалога
// == _strBad1, _strBad2, _strBad3 - строки степени возмущения,  "" и "none" - базовый набор.
// == _kind - вид возмущения: "repeat" - снимается на следующий день при условии, что НПС вконец не разозлился (не задействован анги-файл).
//                            "quest"  - квестовые повторялки, не снимаются на следующий день, но может быть задан срок примирения после перевода на ангри.
//                            "block"  - реакцию НПС на повторные клики без включения ангри, для того, чтобы обозначить интеллект, но не ругаться. Ангри вообще не делать.
//                            "cycle"  - крутим цикл из повторялок, ангри не заряжать. На след. день все снимается.
// == _terms для "repeat" и "quest" - сроки в днях примирения само-собой после задействоания ангри-файла, если == 0, то ругань навсегда (примерение только через подарки).
//    _terms для "block" - сроки возврата в норму в днях, если 0 - навсегда.
// == _character и _Node - npchar и Dialog.CurrentNode
string NPCStringReactionRepeat(string _strNormal, string _strBad1, string _strBad2, string _strBad3, string _kind, int _terms, ref _character, string _Node)
{
    _Node = stripblank(_Node); //fix spaces
	string strBack;
    string strTemp = "quest.repeat." + _Node;
    if (!CheckAttribute(_character , strTemp))
    {
        _character.quest.repeat.(_Node) = 0;
        _character.quest.repeat.(_Node).ans = 0;
    }
    if (_kind == "cycle" || _kind == "repeat") //на след.день все снимается.
    {
        if (GetNpcQuestPastDayParam(_character, strTemp) >= 1)
        {
            _character.quest.repeat.(_Node) = 0;
            _character.quest.repeat.(_Node).ans = 0;
        }
    }
    else
    {
        if (GetNpcQuestPastDayParam(_character, strTemp) >= _terms && _terms!=0 && _kind != "quest") //снятие по "block"
        {
            _character.quest.repeat.(_Node) = 0;
            _character.quest.repeat.(_Node).ans = 0;
        }
    }
    switch(_character.quest.repeat.(_Node))
	{
        case "0":
            strBack = _strNormal;
            _character.quest.repeat.(_Node) = 1;
            _character.quest.repeat.(_Node).ans = 0;
            SaveCurrentNpcQuestDateParam(_character, strTemp);
        break;
        case "1":
            if (_strBad1 == "none" || _strBad1 == "")
            {
                strBack = LinkRandPhrase(StringFromKey("QuestsUtilite_2"),
                          StringFromKey("QuestsUtilite_3"),
                          StringFromKey("QuestsUtilite_4"));
            }
            else
            {
                strBack = _strBad1;
            }
            _character.quest.repeat.(_Node) = 2;
            _character.quest.repeat.(_Node).ans = 1;
        break;
        case "2":
            if (_strBad2 == "none" || _strBad2 == "")
            {
                strBack = LinkRandPhrase(StringFromKey("QuestsUtilite_5"),
                          StringFromKey("QuestsUtilite_6"),
                          StringFromKey("QuestsUtilite_7"));
            }
            else
            {
                strBack = _strBad2;
            }
            _character.quest.repeat.(_Node) = 3;
            _character.quest.repeat.(_Node).ans = 2;
        break;
        case "3":
            if (_strBad3 == "none" || _strBad3 == "")
            {
                strBack = LinkRandPhrase(StringFromKey("QuestsUtilite_8"),
                          StringFromKey("QuestsUtilite_9"),
                          StringFromKey("QuestsUtilite_10")+ GetSexPhrase(StringFromKey("QuestsUtilite_11"),StringFromKey("QuestsUtilite_12")) +StringFromKey("QuestsUtilite_13"));
            }
            else
            {
                strBack = _strBad3;
            }
            // ==> Реакция на третье повторение.
            if (_kind == "cycle") //снова на первую строку.
            {
			    _character.quest.repeat.(_Node) = 0;
            }
			else
            {
                if(_kind != "block") //если block, то опять в последнюю строку
                {
                    _character.quest.repeat.(_Node) = 4;
                    CharacterAddAngry(_character, _Node, _kind, _terms);
    			}
            }
            _character.quest.repeat.(_Node).ans = 3;
        break;
        case "4":
            strBack = "NPCStringReactionRepeat error!!!"
        break;
	}
    return strBack;
}

string HeroStringReactionRepeat(string _strNormal, string _strBad1, string _strBad2, string _strBad3, ref _character, string _Node)
{
    _Node = stripblank(_Node); //fix spaces
	string strBack;
    int Temp = sti(_character.quest.repeat.(_Node).ans);
    switch(Temp)
	{
        case "0":
            strBack = _strNormal;
        break;
        case "1":
            if (_strBad1 == "none" || _strBad1 == "")
            {
                strBack = LinkRandPhrase(StringFromKey("QuestsUtilite_14"),
                          StringFromKey("QuestsUtilite_15"),
                          StringFromKey("QuestsUtilite_16")+ GetSexPhrase(StringFromKey("QuestsUtilite_17"),StringFromKey("QuestsUtilite_18")) +StringFromKey("QuestsUtilite_19"));
            }
            else
            {
                strBack = _strBad1;
            }
        break;
        case "2":
            if (_strBad2 == "none" || _strBad2 == "")
            {
                strBack = LinkRandPhrase(StringFromKey("QuestsUtilite_20"),
                          StringFromKey("QuestsUtilite_21"),
                         StringFromKey("QuestsUtilite_22"));
            }
            else
            {
                strBack = _strBad2;
            }
        break;
        case "3":
            if (_strBad3 == "none" || _strBad3 == "")
            {
                strBack = LinkRandPhrase(StringFromKey("QuestsUtilite_23"),
                          StringFromKey("QuestsUtilite_24"),
                          StringFromKey("QuestsUtilite_25"));
            }
            else
            {
                strBack = _strBad3;
            }
        break;
        case "4":
            strBack = "HeroStringReactionRepeat error!!!"
        break;
	}
    return strBack;
}

// возможны только две переходные ноды: _GoNode1 и _GoNode2, третья не нужна, т.к. идёт сразу в ангри-файл.
// неверно, оставил третью ноду для циклов и прочего.
string DialogGoNodeRepeat(string _NormalNode, string _GoNode1, string _GoNode2, string _GoNode3, ref _character, string _Node)
{
    _Node = stripblank(_Node); //fix spaces
	string strBack, Temp;
    Temp = sti(_character.quest.repeat.(_Node).ans);
    switch(Temp)
	{
        case "0":
            strBack = _NormalNode;
        break;
        case "1":
            if (_GoNode1 == "none" || _GoNode1 == "")
            {
                strBack = "exit";
            }
            else
            {
                strBack = _GoNode1;
            }
        break;
        case "2":
            if (_GoNode2 == "none" || _GoNode2 == "")
            {
                strBack = "exit";
            }
            else
            {
                strBack = _GoNode2;
            }
        break;
        case "3":
            if (_GoNode3 == "none" || _GoNode3 == "")
            {
                strBack = "exit";
            }
            else
            {
                strBack = _GoNode3;
            }
        break;
        case "4":
            strBack = "exit"
            Log_SetStringToLog("DialogGoNodeRepeat#4 error!!!");
        break;
    }
    return strBack;
}

// _Node - имя ноды, идентификатор текущей ангри. Если метод вызывается не в диалоговом файле, то == "none".
void CharacterAddAngry(ref _character, string _Node, string _kind, int _terms)
{
    if (_kind == "repeat" || _kind == "quest")
    {
        DeleteAttribute(_character, "angry");
        _character.angry.kind = _kind;
        _character.angry.name = _Node; //и имя ноды тоже, для расфасовки разных ангри
        if (_terms != 0) // если == 0, то ссора непроходящая с течением времени.
        {
            _character.angry.terms = _terms;
            SaveCurrentNpcQuestDateParam(_character, "angry.terms");
            if (_terms < 10) // размер вознаграждения за примирение, анти с/л
            {
                _character.angry.QtyMoney = (rand(10)+1) * 500;
            }
            else
            {
                _character.angry.QtyMoney = (rand(10)+1) * 5000;
            }
        }
        else
        {
            _character.angry.QtyMoney = (rand(10)+1) * 10000;
        }
    }
    else {Log_Info("CharacterAddAngry error!!!");}
}

void CharacterDelAngry(ref _character)
{
    DeleteAttribute(_character, "angry");
    DeleteAttribute(_character, "quest.repeat");
}

//В условиях возможного тотального применения ангри по квестам, нужно подстраховаться.
//Если нода даётся НПС в момет, когда у него задействован ангри, то нода будет возвращена после примирения.
//Соотв. менять ноды желательно данным методом.
void QuestSetCurrentNode(string _chID, string _Node)
{
    ref chref = characterFromID(_chID);
    if (CheckAttribute(chref, "angry")) chref.dialog.TempNode = _Node;
    else chref.dialog.currentnode = _Node;
}

// фраза от пола НПС
string NPCharSexPhrase(ref _character, string StrMan, string StrWoman)
{
	string strBack;
    if (_character.sex == "woman")
    {
        strBack = StrWoman;
    }
    else
    {
        strBack = StrMan;
    }
    return strBack;
}
// фраза от пола ГГ
string GetSexPhrase(string StrMan, string StrWoman)
{
    return NPCharSexPhrase(PChar, StrMan, StrWoman);
}

//Jason --> фраза от нации персонажа
string GetNatPhrase(ref _character, string StrEng, string StrFra, string StrSpa, string StrHol)
{
	string strBack;
    if (_character.nation == ENGLAND || _character.nation == PIRATE)
    {
        strBack = StrEng;
    }
    else
	{
		if (_character.nation == FRANCE)
		{
        strBack = StrFra;
		}
		else
		{
			if (_character.nation == SPAIN)
			{
			strBack = StrSpa;
			}
			else
			{
			strBack = StrHol;
			}
		}
	}
    return strBack;
}
//<-- фраза от нации персонажа
//<<<=== Функции по работе с диалоговыми файлами. =======================================================================


// Временно сохранить все данные о нашем корабле в памяти
//--------------------------------------------------------
bool SetTempRemoveParam(ref _refCharacter, string _param)
{
    string sParam = "TmpRemember" + _param;
    
	if( CheckAttribute(_refCharacter, sParam) ) return false;
	if( !CheckAttribute(_refCharacter, _param) ) return false;

	aref dstRef; makearef(dstRef, _refCharacter.(sParam));
	aref srcRef; makearef(srcRef, _refCharacter.(_param));

	CopyAttributes(dstRef,srcRef);
	return true;
}

// Восстановить данные о нашем старом корабле из памяти
//------------------------------------------------------
bool RestoreTempRemoveParam(ref _refCharacter, string _param)
{
    string sParam = "TmpRemember" + _param;
    
	if( !CheckAttribute(_refCharacter, sParam) ) return false;

	aref dstRef; makearef(dstRef, _refCharacter.(_param));
	aref srcRef; makearef(srcRef, _refCharacter.(sParam));

	DeleteAttribute(_refCharacter, _param);
	//--> eddy. структура быть должна, иначе вылет в винду.
	_refCharacter.(_param) = "";
	CopyAttributes(dstRef,srcRef);
	DeleteAttribute(_refCharacter, sParam);
	return true;
}

// установка отмены боевки в резиденции при захвате города
// ВАЖНО: работает только не в пиратском городе - иначе это просто мятеж и губернатора там нет вообще
void SetCaptureResidenceQuest(string _city, string _method, bool _majorOff)
{
    PChar.GenQuestFort.ResidenceQuest.(_city) = true;
    // убирать ли губернатора из локации вообще, он пропадёт, но потом обратно пропишется, чтоб не рушить мир игры.
    PChar.GenQuestFort.ResidenceQuest.(_city).MayorOff = _majorOff;
    if (_method != "")
    {
        PChar.GenQuestFort.ResidenceQuest.(_city).method = _method;
	}
}

// вернём диалог после разговора и спрячем
void  SetReturn_Gover_Dialog_Exit(ref NPChar)
{
	LAi_LoginInCaptureTown(NPChar, false);

	PChar.GenQuest.GoverIdx = NPChar.index;
	Pchar.quest.Return_Gover_Dialog_Exit.win_condition.l1          = "ExitFromLocation";
    Pchar.quest.Return_Gover_Dialog_Exit.win_condition.l1.location = Pchar.location;
    Pchar.quest.Return_Gover_Dialog_Exit.win_condition             = "Return_Gover_Dialog_Exit";
}

void SetNewModelToChar(ref chref)
{
    float liveTime = 0.1;
	int colors = argb(64, 64, 64, 64);
	int colore = argb(0, 32, 32, 32);

    if (IsEntity(&chref))
    {
    	if(CheckAttribute(chref, "model"))
        {
            SendMessage(chref, "lss",   MSG_CHARACTER_SETMODEL, chref.model, chref.model.animation);
        }
        if(CheckAttribute(chref, "equip.gun"))
        {
			ref rItem = ItemsFromID(chref.equip.gun);
			if(CheckAttribute(rItem, "model")) SendMessage(chref, "ls",    MSG_CHARACTER_SETGUN,   rItem.model);
			else trace("SetNewModelToChar -> Character "+ chref.id + " has invalide model 'equip.gun'");
        }
        if(CheckAttribute(chref, "equip.blade"))
        {
			rItem = ItemsFromID(chref.equip.blade);
            //SendMessage(chref, "lsfll", MSG_CHARACTER_SETBLADE, chref.equip.blade, liveTime, colors, colore);
            //SendMessage(chref, "llsfll", MSG_CHARACTER_SETBLADE, 0, chref.equip.blade, liveTime, colors, colore);
			SendMessage(chref, "llsfll", MSG_CHARACTER_SETBLADE, 0, rItem.model, liveTime, colors, colore);
        }
		if(CheckAttribute(chref, "equip.musket"))	// evganat - мушкет
        {
			rItem = ItemsFromID(chref.equip.musket);
            SendMessage(chref, "ls", MSG_CHARACTER_SETMUS, rItem.model);
        }
    }
}
// функции из квест_реакшн
void SetNationToOfficers(int _nat)
{
    int j, cn;
    ref officer;

    for(j=1; j<COMPANION_MAX; j++)
    {
        cn = GetCompanionIndex(GetMainCharacter(),j);
        if( cn>0 )
        {
	        officer = GetCharacter(cn);
	        if (!GetRemovable(officer)) continue;
	        officer.nation = _nat;
	        Ship_FlagRefresh(officer); //флаг на лету
	    }
	}
}

bool IsOfficerCompanion(ref _refCharacter)
{
	int findIdx = sti(_refCharacter.index);
	ref mc = GetMainCharacter();
	int ci, cn;
	ref npc;
	for(int i=1; i<COMPANION_MAX; i++)
	{
		ci = GetCompanionIndex(mc,i);
		npc = GetCharacter(ci);
		for(int j=1; j<4; j++)
		{
			if(GetOfficersIndex(npc,j)==findIdx) return true;
		}
	}
	return false;
}
///////////////////////////////////////////////////////////////////
void SortItems(ref NPChar)
{// отсортировать предметы в кармане, сундуке
    aref   arToChar;
    aref   arFromChar;
    object objChar;
    int    i;
    aref   curItem;
	string attr;
	ref    itm;
	ref    rObj;
	int    iSortIndex;
	bool   ok;

    objChar.Items = "";
    rObj = &objChar;

    makearef(arToChar,   rObj.Items);
    makearef(arFromChar, NPChar.Items);

    CopyAttributes(arToChar, arFromChar);

    DeleteAttribute(NPChar, "Items");
    NPChar.Items = "";

    makearef(arFromChar, NPChar.equip); // экипировка
    int iMax = GetAttributesNum(arFromChar);
    for(i=0; i<iMax; i++)
    {
        curItem = GetAttributeN(arFromChar, i);
        attr = GetAttributeValue(curItem);
        if (attr != "") //патенты клинит
        {
        	NPChar.Items.(attr) = sti(rObj.Items.(attr));
        }
    }
    // неоптимальная сортировка по индексу itm.SortIndex
	// размерность индекса определяется автоматом - длжен быть непрерывен!!, начинается с 1 - целое число
	ok = true;
	iSortIndex = 1;
	while (iSortIndex < 3)// 2 типа
	{
		ok = false;
		for (i=0; i<TOTAL_ITEMS; i++)
		{
			// Warship 11.05.09 fix для новой системы предметов
			if(!CheckAttribute(&Items[i], "ID"))
			{
				continue;
			}
			
			makeref(itm, Items[i]);
			attr = itm.id;
			if (CheckAttribute(rObj, "items."+attr) && CheckAttribute(itm, "SortIndex") && sti(itm.SortIndex) == iSortIndex)
			{
                NPChar.Items.(attr) = sti(rObj.Items.(attr));
	   			ok = true;
	      	}
	    }
	    iSortIndex++;
    }
    // все остальные
    for (i=0; i<TOTAL_ITEMS; i++)
	{
		// Warship 11.05.09 fix для новой системы предметов
		if(!CheckAttribute(&Items[i], "ID"))
		{
			continue;
		}
		
		makeref(itm, Items[i]);
		attr = itm.id;
		if (CheckAttribute(rObj, "items."+attr) && !CheckAttribute(itm, "SortIndex"))
		{
   			NPChar.Items.(attr) = sti(rObj.Items.(attr));
   			ok = true;
      	}
    }
}
// установка квестовых товаров и цен
void SetQuestGoodsToStore(ref refStore)
{
	string    goodName;
	// пример использования по квест_реакшн
	/*
	pchar.GenQuest.StoreGoods.StoreIdx = Bridgetown_STORE;
	pchar.GenQuest.StoreGoods.NowNeedToBe = true;
	*/
	if (CheckAttribute(pchar, "GenQuest.StoreGoods.StoreIdx") && refStore.index == pchar.GenQuest.StoreGoods.StoreIdx)
	{
        // пример обработки события pchar.GenQuest.StoreGoods.StoreIdx = LaVega_STORE;
		/*if (CheckAttribute(pchar, "GenQuest.StoreGoods.NowNeedToBe")) // состояние говорящие, то нужно делать
		{
		    DeleteAttribute(pchar, "GenQuest.StoreGoods"); // одноразовая операция, трем обе ветки
		    goodName = Goods[GOOD_RUM].Name;
		    refStore.Goods.(goodName).Quantity       = 666;
		    // цена из обратного вычисления 20 в модификатор
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_RUM, PRICE_TYPE_BUY, pchar, 20);
		}  */
		if (CheckAttribute(pchar, "GenQuest.StoreGoods.Starting")) // заполнение магазина Сен-Пьера на старте
		{
		    DeleteAttribute(pchar, "GenQuest.StoreGoods"); // одноразовая операция, трем обе ветки
		    goodName = Goods[GOOD_BALLS].Name;
		    refStore.Goods.(goodName).Quantity = 300;
			goodName = Goods[GOOD_GRAPES].Name;
			refStore.Goods.(goodName).Quantity = 300;
			goodName = Goods[GOOD_KNIPPELS].Name;
			refStore.Goods.(goodName).Quantity = 300;
			goodName = Goods[GOOD_BOMBS].Name;
			refStore.Goods.(goodName).Quantity = 300;
			goodName = Goods[GOOD_FOOD].Name;
			refStore.Goods.(goodName).Quantity = 500;
			goodName = Goods[GOOD_MEDICAMENT].Name;
			refStore.Goods.(goodName).Quantity = 150;
			goodName = Goods[GOOD_WEAPON].Name;
			refStore.Goods.(goodName).Quantity = 100;
			goodName = Goods[GOOD_RUM].Name;
			refStore.Goods.(goodName).Quantity = 100;
		} 
		if (CheckAttribute(pchar, "GenQuest.StoreGoods.Guardoftruth")) // ваниль на Гваделупе
		{
			DeleteAttribute(pchar, "GenQuest.StoreGoods"); // одноразовая операция, трем обе ветки
		    goodName = Goods[GOOD_CINNAMON].Name;
		    refStore.Goods.(goodName).Quantity = 127;
		}		
	}
}

// метод обработки капитана в каюте на абордаже. Ставим проверку на минНР + дилог
// refChar - это фантом, а не реальный кэп, он копия, диалог от настоящего, но ИД и индекс не его, а фантомный, поэтому управляем имено этим актером
// CaptanId - реальный ИД кэпа, запомненный в момент копирования.
void SetQuestAboardCabinDialog(ref refChar)
{
	// пример. тут задаю для теста, все это должно быть на изначальном капитане по квестам
	//refChar.DontClearDead      = true;
	//refChar.SaveItemsForDead   =   true;
	//TakeNItems(refChar, "Chest", 1);
	// пример. <--

	if (CheckAttribute(refChar, "CaptanId"))
	{
        pchar.GenQuest.QuestAboardCabinDialogIdx = refChar.index;
        // как использовать, пример
		/*if (true) // true - для теста, должно быть это CheckAttribute(pchar, "квестовая ветка, если нужно") && refChar.CaptanId == "IdNPC")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
            refChar.Dialog.Filename    = "Capitans_dialog.c";   // это нужно задать на изначальном кэпе в др месте
	    	refChar.Dialog.CurrentNode = "QuestAboardCabinDialog";
	    	// все остальное в диалоге, по образцу
		}*/
		//капитан по квесту мэра на поиск и уничтожение пирата.
		if (refChar.CaptanId == "MQPirate" && CheckAttribute(pchar, "GenQuest.DestroyPirate"))
		{
		    LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");
			refChar.dialog.currentnode = "DestroyPirate_Abordage";
		}
		else if (findsubstr(refChar.CaptanId, "_QuestMerchant" , 0) != -1  && trap)
		{
            //засада на ГГ по наводке на купца homo
		    LAi_SetCheckMinHP(refChar, 30, true, "QuestAboardCabinDialog");
		    refChar.dialog.filename = "Capitans_dialog.c";  //fix homo 23/03/07
			refChar.dialog.currentnode = "MerchantTrap_Abordage";
		}
		else if (findsubstr(refChar.CaptanId, "SeekCap_" , 0) != -1)
		{
            //квест возврата украденного корабля
		    LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");
			refChar.Dialog.CurrentNode = "SeekCap";
		}
		else if (findsubstr(refChar.CaptanId, "SeekCitizCap_" , 0) != -1) //поисковый генератор
		{
			if (refChar.quest.SeekCap == "NM_battle")
			{
				LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");
				refChar.Dialog.CurrentNode = "NM_battleBoard";
			}
			else if (refChar.quest.SeekCap == "NM_prisoner")
			{
				LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");
				refChar.Dialog.CurrentNode = "NM_prisonerBoard";
			}
			else if (refChar.quest.SeekCap == "manRapeWife")
			{
				LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");
				refChar.Dialog.CurrentNode = "RapeWifeCap_Board";
			}
		    else if (refChar.quest.SeekCap == "womanRevenge")
			{
				LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");
				refChar.Dialog.CurrentNode = "RevengeCap_board";
			}
			else if (refChar.quest.SeekCap == "womanPirates")
			{
				LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");
				refChar.Dialog.CurrentNode = "PiratesCap_Board";
			}
		}
		else if (refChar.CaptanId == "PirateCapt") //генератор "Продажный патруль" 
		{
			LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
		}
		else if(refChar.CaptanId == "PiratesOnUninhabited_BadPirate") // Warship Генер "Пираты на необитайке"
		{
			LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "GenQuests_Dialog.c";
			refChar.Dialog.CurrentNode = "PiratesOnUninhabited_46";
		}
        else if(CheckAttribute(pchar,"GenQuest.CaptainComission") && pchar.GenQuest.CaptainComission == "Begin")
		{
            // Генерратор "Поручение капитана 'Выкуп' или 'Операция Галеон'"
			LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "GenQuests_Dialog.c";
			refChar.Dialog.CurrentNode = "CaptainComission_1";
		}
		else if(refChar.CaptanId == "ShipWreck_BadPirate")
		{
			LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "GenQuests_Dialog.c";
			refChar.Dialog.CurrentNode = "ShipWreck_50";
		}
		else if (refChar.CaptanId == "Slaveshorecap")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\Other_Quests_NPC.c";
			refChar.Dialog.CurrentNode = "TakeShoreCap";
		}
		else if (refChar.CaptanId == "RatCaptain")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\Other_Quests_NPC.c";
			refChar.Dialog.CurrentNode = "Rat_talk";
		}
		else if (refChar.CaptanId == "Jafar")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\Other_Quests_NPC.c";
			refChar.Dialog.CurrentNode = "Ja_talk";
		}
		else if (refChar.CaptanId == "Fleetwood")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\HollandGambit\Fleetwood.c";
			refChar.Dialog.CurrentNode = "Fleetwood_abordage";
		}
		else if (refChar.CaptanId == "JacobBerg")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\HollandGambit\JacobBerg.c";
			refChar.Dialog.CurrentNode = "JacobBerg_abordage";
		}
		else if (refChar.CaptanId == "Lucas")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\HollandGambit\LucasRodenburg.c";
			refChar.Dialog.CurrentNode = "Lucas_abordage";
		}
		else if (refChar.CaptanId == "Knippel")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\HollandGambit\Knippel.c";
			refChar.Dialog.CurrentNode = "Knippel_abordage";
		}
		else if (refChar.CaptanId == "CureerCap")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\HollandGambit\OtherNPC.c";
			refChar.Dialog.CurrentNode = "Cureer_abordage";
		}
		else if (refChar.CaptanId == "Longway")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\HollandGambit\Longway.c";
			refChar.Dialog.CurrentNode = "Longway_abordage";
		}
		else if (refChar.CaptanId == "FalseTraceCap")//ложный след
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\LineMiniQuests\FalseTrace.c";
			refChar.Dialog.CurrentNode = "FalseTrace_abordage";
		}
		else if (refChar.CaptanId == "Vaskezs_helper")//португалец
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\Portugal_dialog.c";
			refChar.Dialog.CurrentNode = "VaskezsHelper_abordage";
		}
		else if (refChar.CaptanId == "ConJuan")//цена чахотки
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\LineMiniQuests\Consumption.c";
			refChar.Dialog.CurrentNode = "Juan_abordage";
		}
		else if (refChar.CaptanId == "MarginCap")//захват пассажиров
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\Marginpassenger.c";
			refChar.Dialog.CurrentNode = "MarginCap_abordage";
		}
		else if (refChar.CaptanId == "ContraPassCap")//генер губера - ОЗГ - пассажир
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "MayorQuests_dialog.c";
			refChar.Dialog.CurrentNode = "ContraPass_abordage";
		}
		else if (refChar.CaptanId == "Donovan")//Сага, корвет Донована
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\Saga\OtherNPC.c";
			refChar.Dialog.CurrentNode = "Donovan_abordage";
		}
		else if (refChar.CaptanId == "Jackman")//Сага, Джекман
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Mayor\Jackman.c";
			refChar.Dialog.CurrentNode = "Jackman_abordage";
		}
		else if (refChar.CaptanId == "RoberCap2")//Черепаха, Мартэн
		{
		    LAi_SetCheckMinHP(refChar, 100, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\Sharlie\Terrapin.c";
			refChar.Dialog.CurrentNode = "rober_abordage";
		}
		else if (refChar.CaptanId == "Kaleuche_khaelroacap")//Калеуче
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\Caleuche_dialog.c";
			refChar.Dialog.CurrentNode = "CaleucheCap_3";
		}
		else if (refChar.CaptanId == "FMQG_Juan" && CheckAttribute(pchar,"questTemp.FMQG") && pchar.questTemp.FMQG != "fail") // Addon-2016 Jason ФМК-Гваделупа
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\LineMiniQuests\FMQ_Guadeloupe.c";
			refChar.Dialog.CurrentNode = "Juan";
		}
		else if (refChar.CaptanId == "Ignasio" && CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Logbook"))
		{
            // Addon 2016-1 Jason Пиратская линейка
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\Roger.c";
			refChar.Dialog.CurrentNode = "ignasio_boarding";
		}
		else if (refChar.CaptanId == "LH_BarbSeaCap_1") // Jason Долго и счастливо
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\LongHappy.c";
			refChar.Dialog.CurrentNode = "Barbazon_boarding";
		}
		else if (refChar.CaptanId == "TK_Heiter") // Sinistra Травля крысы
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\Sharlie\OtherNPC.c";
			refChar.Dialog.CurrentNode = "TK_Kapitan";	
		}
		else if (refChar.CaptanId == "DTSG_Kortni") // Sinistra Длинные тени старых грехов
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\CompanionQuests\Knippel.c";
			refChar.Dialog.CurrentNode = "DTSG_Kortni";	
		}
		else if (refChar.CaptanId == "PZ_KlemanLebren") // Rebbebion, квест "Путеводная звезда"
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\CompanionQuests\Longway.c";
			refChar.Dialog.CurrentNode = "PZ_KlemanLebren_7";	
		}
		else if (refChar.CaptanId == "PZ_RobertMartin") // Sinistra, квест "Путеводная звезда"
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\CompanionQuests\Longway.c";
			refChar.Dialog.CurrentNode = "PZ_RobertMartin_8";	
		}
		else if (refChar.CaptanId == "BM_GabeCallow") // Rebbebion, квест "Чёрная метка"
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\BlackMark.c";
			refChar.Dialog.CurrentNode = "BM_Callow1";	
		}
		else if (refChar.CaptanId == "SantaMisericordia_cap") // Святое Милосердие
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\ShipsPack\SantaMisericordia_dialog.c";
			refChar.Dialog.CurrentNode = "Alamida_abordage";	
		}
		else if (refChar.CaptanId == "LadyBeth_cap") // Леди Бет
		{
			LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\ShipsPack\LadyBeth_dialog.c";
			refChar.Dialog.CurrentNode = "LadyBeth_abordage";	
		}
		else if (refChar.CaptanId == "TPZ_Pirate") // квест "Торговля по закону"
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
			refChar.Dialog.FileName = "Quest\MiniEvents\TradingByLaw_dialog.c";
			refChar.Dialog.CurrentNode = "Pirate_1";	
		}
		else if (refChar.CaptanId == "Memento_cap") // Мементо
		{
		    LAi_SetCheckMinHP(refChar, 1, false, "Memento_MortimerGrimDead");
		}
        else if (refChar.CaptanId == NationShortName(sti(refChar.nation)) + "Brigadier01") // Пожарная команда
        {
            LAi_SetCheckMinHP(refChar, 1, true, "QuestAboardCabinDialog");
            refChar.Dialog.FileName = "Quest\FireBrigade.c";
			refChar.Dialog.CurrentNode = "FireBrigade_" + NationShortName(sti(refChar.nation));	
        }
	}
}

// ugeen --> ситуации на абордаже в каюте вражеского кэпа (эпидемия или взрыв)
void SetQuestAboardCabinDialogSituation(ref refChar)
{
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, true);
	refChar.Dialog.FileName = "GenQuests_Dialog.c";	
	switch(refChar.situation.type)
	{
		case "pirate": 	// пираты или ДУ	
			refChar.Dialog.CurrentNode = "ShipSituation11";
		break;
		case "hunter": 	// ОЗГ
			refChar.Dialog.CurrentNode = "ShipSituation31";
		break;
		case "war": 	// военные корабли
			refChar.Dialog.CurrentNode = "ShipSituation21";
		break;
		case "trade": 	// торговцы
			refChar.Dialog.CurrentNode = "ShipEpidemy1";
		break;		
	}
	LAi_SetActorType(refChar);
	LAi_ActorDialog(refChar, pchar, "", -1, 0); 
}
// <-- ugeen

void QuestAboardCabinDialogFree()
{
	ref sld;
	sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
	Lai_SetPlayerType(pchar);
	LAi_RemoveCheckMinHP(sld);
	LAi_SetImmortal(sld, false);
    LAi_SetWarriorType(sld);
    LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
}
//выход без боевки, но в плен не надо
void QuestAboardCabinDialogNotBattle()
{
	ref sld;
	sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
	Lai_SetPlayerType(pchar);
	LAi_RemoveCheckMinHP(sld);
	LAi_SetImmortal(sld, false);
    LAi_SetWarriorType(sld);
	DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
}
// выход с боевкой
void QuestAboardCabinDialogExitWithBattle(string _questName)
{
    QuestAboardCabinDialogFree(); // важный метод
	ref sld;
	sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
	LAi_SetFightMode(pchar, true);
	LAi_SetFightMode(sld, true);
	LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck(LAI_GROUP_BRDENEMY, _questName);
	// SetCharacterTask_Fight(sld, pchar);
}

void QuestAboardCabinDialogExitWithBattleNoParam()// homo тоже самое, только без параметров
{
    QuestAboardCabinDialogExitWithBattle("");
}

void QuestAboardCabinDialogSurrender()
{
 	ref sld;
	sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
	DeleteAttribute(sld, "DontRansackCaptain"); // если было зачем-то
	pchar.GenQuest.QuestAboardCaptanSurrender = true;
	Lai_SetPlayerType(pchar);
	LAi_RemoveCheckMinHP(sld);
	LAi_SetImmortal(sld, false);
	//на форме убиваем LAi_SetCurHP(characterFromId(sld.CaptanId), 0.0); 
	//sld.LifeDay = 0;    это не фантом многодневка, а фантом локации, трется он сам при закрузке локации, но не при выгрузке
	DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
}
//==> квестовое пленение с сохранением индекса пленного.
void QuestAboardCabinDialogQuestSurrender()
{
	ref sld;
	sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
	sld.DontRansackCaptain = true; // чтоб не сдался второй раз
	Lai_SetPlayerType(pchar);
	LAi_RemoveCheckMinHP(sld);
	LAi_SetImmortal(sld, false);
	//на форме убиваем LAi_SetCurHP(characterFromId(sld.CaptanId), 0.0); 
	//sld.LifeDay = 0;
	pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(sld);
	SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
	DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
}

// eddy. лицензии торговых компаний. -->
//дать лицензию
void GiveNationLicence(int _nation, int _validity)
{
	string sTemp; 
	ref rItem;
	for(int i=0; i<4; i++)
	{
		if (CheckNationLicence(i) && GetDaysContinueNationLicence(i) == -1) TakeNationLicence(i);
	}
	if (_nation != PIRATE) 
	{
		if (CheckNationLicence(_nation)) TakeNationLicence(_nation);
		sTemp = NationShortName(_nation)+"TradeLicence";
		GiveItem2Character(pchar, sTemp);
		rItem = ItemsFromID(sTemp);
		SaveCurrentNpcQuestDateParam(rItem, "Action_date");
		rItem.Action_date = GetCurrentDate(); 
		rItem.Validity = FindRussianDaysString(_validity); //строка для дескрайба
		rItem.Validity.QtyDays = _validity; //время действия лицензии в днях для расчетов
	}
}
//забрать лицензию 
void TakeNationLicence(int _nation)
{
	string sTemp; 
	if (_nation != PIRATE && CheckNationLicence(_nation)) 
	{
		sTemp = NationShortName(_nation)+"TradeLicence";
		TakeItemFromCharacter(pchar, sTemp);
		DeleteAttribute(ItemsFromID(sTemp), "Action_date");
		DeleteAttribute(ItemsFromID(sTemp), "Validity");
	}
}
//проверить наличие лицензии
bool CheckNationLicence(int _nation)
{
	if (_nation != PIRATE) 
	{
		if (CheckCharacterItem(pchar, NationShortName(_nation)+"TradeLicence")) return true; 
	}
	return false;
}
//проверить сроки лицензии, сколько осталось дней. если -1, то просрочена или отсутствует
int GetDaysContinueNationLicence(int _nation)
{
	int iTerms = -1;
	ref rItem;
	if (_nation != PIRATE) 
	{
		if (CheckNationLicence(_nation))
		{
			rItem = ItemsFromID(NationShortName(_nation)+"TradeLicence");
			
			if(!CheckAttribute(rItem, "Validity")) // Warship 10.07.09 fix - Судя по логам, могло не быть
			{
				return -1;
			}
			
			int Validity = sti(rItem.Validity.QtyDays);
			iTerms = GetNpcQuestPastDayParam(rItem, "Action_date");
			if (iTerms > Validity) iTerms = -1;
			else iTerms = Validity - iTerms;
		}
	}
	return iTerms;
}
//дать наименование лицензии, например 'Лицензия Голландской Вест-Индской компании'
string GetRusNameNationLicence(int _nation)
{
	string sTemp, itmTitle;
	int lngFileID;
	if (_nation != PIRATE) 
	{
		if (CheckNationLicence(_nation))
		{
			sTemp = NationShortName(_nation)+"TradeLicence";
			lngFileID = LanguageOpenFile("ItemsDescribe.txt");
			itmTitle = LanguageConvertString(lngFileID, Items[GetItemIndex(sTemp)].name);
		}
	}
	return itmTitle;
}
// eddy. лицензии торговых компаний. <--

void SelectSlavetraderRendom() // работорговец, выбор города
{
	if (CheckAttribute(&colonies[1], "nation"))
	{
		int n, nation;
		int storeArray[2];
		SetArraySize(&storeArray, MAX_COLONIES);
		int howStore = 0;
		for(n=0; n<MAX_COLONIES; n++)
		{			
			if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && colonies[n].id != "FortOrange" && colonies[n].id != "Havana" && colonies[n].id != "Santiago" && colonies[n].id != "Portroyal" && colonies[n].id != "Villemstad" && colonies[n].id != "Charles" && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres")
			{           
				storeArray[howStore] = n;
				howStore++;
			}
		}
		nation = storeArray[rand(howStore-1)];
		pchar.questTemp.Slavetrader.UsurerId = colonies[nation].id + "_usurer";
		AddMapQuestMarkCity(colonies[nation].id, false);
		AddLandQuestMark(characterFromId(pchar.questTemp.Slavetrader.UsurerId), "questmarkmain");
	}
}

void HollandGambitNpcInit()//оптимизация - создаем всех ключевых персонажей по этому квесту здесь
{
//--------------------------------штаб-квартира ГВИК в Виллемстаде--------------------------------------
	//Лукас Роденбург
	sld = GetCharacter(NPC_GenerateCharacter("Lucas", "Lucas", "man", "man", 30, HOLLAND, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_26");
	sld.lastname = StringFromKey("QuestsUtilite_27");
	sld.greeting = "rodenburg_1";
	sld.rank = 30;
	LAi_SetHP(sld, 350, 350);
	sld.Dialog.Filename = "Quest\HollandGambit\LucasRodenburg.c";
	sld.dialog.currentnode = "First time";
	GiveItem2Character(sld, "blade_17");
	sld.equip.blade = "blade_13";
	GiveItem2Character(sld, "pistol5");
	EquipCharacterbyItem(sld, "pistol5");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld,"potion2", 5);
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
	sld.DontClearDead = true;
	sld.SaveItemsForDead = true;
	// belamour legendary edition меням прописку
	sld.location = "GVIK_residence";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	sld.money = 20000;
 	SetRandSPECIAL(sld);
    SetSelfSkill(sld, 80, 80, 80, 80, 80);
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	// belamour legendary edition новое название локации GVIK
	LocatorReloadEnterDisable("GVIK", "reload2", true);//кабинет закроем до поры 
	//офицер-секретарь
	sld = GetCharacter(NPC_GenerateCharacter("HWIC_officer", "off_hol_4", "man", "man", 25, HOLLAND, -1, false, "soldier"));
	FantomMakeCoolFighter(sld, 35, 90, 90, "blade_07", "pistol2", "grapeshot", 200);
	sld.greeting = "patrol";
	sld.Dialog.Filename = "Quest\HollandGambit\HWIC_Office.c";
	sld.dialog.currentnode = "HWIC_officer";
    TakeNItems(sld, "grapeshot", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld,"potion2", 3);
	LAi_SetImmortal(sld, true);
	sld.location = "GVIK";
	sld.location.group = "soldiers";
	sld.location.locator = "soldier3";
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	pchar.quest.HWIC_officer.win_condition.l1 = "location";
	pchar.quest.HWIC_officer.win_condition.l1.location = "GVIK";
	pchar.quest.HWIC_officer.function = "HWICofficerTalk";
	
//----------------------------------------Дом Соломона и Абигайль Шнеур-------------------------------------
	//Абигайль
	sld = GetCharacter(NPC_GenerateCharacter("Abigile", "Aby", "woman", "woman_A2", 10, HOLLAND, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_28");
	sld.lastname = StringFromKey("QuestsUtilite_29");
	sld.greeting = "abigile_1";
	sld.rank = 5;
	SetSelfSkill(sld, 5, 5, 5, 5, 5);
	SetShipSkill(sld, 5, 5, 5, 5, 5, 5, 5, 5, 5);
	sld.Dialog.Filename = "Quest\HollandGambit\Abigile.c";
	sld.dialog.currentnode = "First time";
	sld.location	= "Villemstad_houseSp2_bedroom";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.money = 0;
	LAi_SetOwnerType(sld);
 	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	//Соломон
	sld = GetCharacter(NPC_GenerateCharacter("Solomon", "Solomon", "man", "man_B", 10, HOLLAND, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_30");
	sld.lastname = StringFromKey("QuestsUtilite_31");
	sld.greeting = "solomon_1";
	sld.rank = 10;
	sld.Dialog.Filename = "Quest\HollandGambit\Solomon.c";
	sld.dialog.currentnode = "First time";
	sld.location	= "Villemstad_houseSp2";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.money = 1000;
	LAi_SetOwnerType(sld);
 	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	LocatorReloadEnterDisable("Villemstad_town", "houseSP2", true);//дом закроем до поры
	
//-----------------------------------------аптека мистера Мердока-------------------------------------------
	//Джон Мердок
	sld = GetCharacter(NPC_GenerateCharacter("Merdok", "Merdok", "man", "man", 30, ENGLAND, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_32");
	sld.lastname = StringFromKey("QuestsUtilite_33");
	sld.greeting = "merdok_1";
	sld.rank = 30;
	LAi_SetHP(sld, 350, 350);
	sld.Dialog.Filename = "Quest\HollandGambit\Merdok.c";
	sld.dialog.currentnode = "First time";
	sld.location = "SentJons_HouseF3";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.Merchant = true;
	sld.Merchant.type = "potion";
	sld.money = TRADER_MIN_MONEY + rand(TRADER_NORM);
	sld.DontClearDead = true;
	sld.SaveItemsForDead = true;
	SetRandSPECIAL(sld);
    SetSelfSkill(sld, 80, 80, 80, 80, 80);
	LAi_SetOwnerType(sld);
 	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", true);//подземелье закроем до поры
	//Джино Гвинейли
	sld = GetCharacter(NPC_GenerateCharacter("Jino", "Gino", "man", "man", 20, ENGLAND, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_34");
	sld.lastname = StringFromKey("QuestsUtilite_35");
	sld.greeting = "Jino";
	sld.rank = 20;
	LAi_SetHP(sld, 150, 150);
	sld.Dialog.Filename = "Quest\HollandGambit\Jino.c";
	sld.dialog.currentnode = "First time";
	sld.location	= "SentJons_HouseF3_Room";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.money = 5000;
	LAi_SetCitizenType(sld);
	AddLandQuestMark(sld, "questmarkmain");
 	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", true);//комнату закроем до поры
	
//------------------------------------хижина Чарли Книппеля-------------------------------------------
	//Чарли Книппель
	sld = GetCharacter(NPC_GenerateCharacter("Knippel", "Kneepel", "man", "man_B", 20, ENGLAND, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_36");
	sld.lastname = StringFromKey("QuestsUtilite_37");
	sld.greeting = "knippel_1";
	sld.CompanionDisable = true;
	sld.rank = 20;
	LAi_SetHP(sld, 120, 120);
	SetSelfSkill(sld, 10, 12, 10, 10, 70);
	SetShipSkill(sld, 50, 20, 75, 75, 45, 20, 20, 10, 15);
	SetSPECIAL(sld, 9, 10, 6, 5, 5, 5, 9);
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "FastReload");
	sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
	sld.dialog.currentnode = "First time";
	GiveItem2Character(sld, "blade_12");
	sld.equip.blade = "blade_12";
	GiveItem2Character(sld, "pistol1");
	EquipCharacterbyItem(sld, "pistol1");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld,"potion2", 3);
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
	sld.location = "SentJons_houseH1";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.money = 1000;
	LAi_SetOwnerType(sld);
 	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	
//----------------прочие персонажи - расстановка в зависимости от варианта квеста в разных местах-----------
	//Ричард Флитвуд
	sld = GetCharacter(NPC_GenerateCharacter("Fleetwood", "Fleetwood", "man", "man", 20, ENGLAND, -1, true, "quest"));
	sld.name = StringFromKey("QuestsUtilite_38");
	sld.lastname = StringFromKey("QuestsUtilite_39");
	sld.greeting = "fleetwood_1";
	sld.rank = 30;
	LAi_SetHP(sld, 300, 300);
	SetSelfSkill(sld, 80, 80, 80, 80, 80);
	SetShipSkill(sld, 50, 20, 70, 75, 80, 60, 70, 80, 50);
	SetRandSPECIAL(sld);
	sld.Dialog.Filename = "Quest\HollandGambit\Fleetwood.c";
	sld.dialog.currentnode = "First time";
	GiveItem2Character(sld, "blade_14");
	sld.equip.blade = "blade_14";
	GiveItem2Character(sld, "pistol3");
	EquipCharacterbyItem(sld, "pistol3");
    TakeNItems(sld, "grapeshot", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", 2);
	sld.DontClearDead = true;
	sld.SaveItemsForDead = true;
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "grapeshot");
	sld.money = 20000;
 	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	
	//Якоб ван Берг
	sld = GetCharacter(NPC_GenerateCharacter("JacobBerg", "VanBerg", "man", "man", 35, PIRATE, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_40");
	sld.lastname = StringFromKey("QuestsUtilite_41");
	sld.greeting = "JacobBerg";
	sld.Dialog.Filename = "Quest\HollandGambit\JacobBerg.c";
	sld.dialog.currentnode = "First time";
	sld.DontClearDead = true;
	sld.SaveItemsForDead = true;
	TakeNItems(sld, "potion2", 2);
	sld.money = 12000;
	SetRandSPECIAL(sld);
	
	//Лонгвэй
	sld = GetCharacter(NPC_GenerateCharacter("Longway", "Longway", "man", "Longway", 20, HOLLAND, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_42");
	sld.lastname = StringFromKey("QuestsUtilite_43");
	sld.greeting = "Longway";
    sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
	sld.dialog.currentnode = "First time";
	sld.CompanionDisable = true;
	sld.rank = 20;
	sld.money = 5000;
	SetSelfSkill(sld, 45, 45, 45, 40, 50);
	SetShipSkill(sld, 50, 20, 25, 25, 65, 20, 20, 50, 15);
	SetSPECIAL(sld, 8, 9, 6, 5, 10, 7, 5);
	LAi_SetHP(sld, 250, 250);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "WindCatcher");
	SetCharacterPerk(sld, "SailsMan");
	SetCharacterPerk(sld, "SailingProfessional");
	GiveItem2Character(sld, "blade_08");
	sld.equip.blade = "blade_08";
	GiveItem2Character(sld, "pistol3");
	EquipCharacterbyItem(sld, "pistol3");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "grapeshot");
    TakeNItems(sld, "grapeshot", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", 1);
	
	//Жоаким Мерриман
	sld = GetCharacter(NPC_GenerateCharacter("Joakim", "Meriman_1", "man", "man_B", 25, HOLLAND, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_44");
	sld.lastname = StringFromKey("QuestsUtilite_45");
	sld.greeting = "Joakim";
    sld.Dialog.Filename = "Quest\HollandGambit\Joakim.c";
	sld.dialog.currentnode = "First time";
	sld.rank = 25;
	GiveItem2Character(sld, "blade_09");
	sld.equip.blade = "blade_09";
	GiveItem2Character(sld, "pistol3");
	EquipCharacterbyItem(sld, "pistol3");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "grapeshot");
    TakeNItems(sld, "grapeshot", 50);
	AddItems(sld, "gunpowder", 50);
	LAi_SetImmortal(sld, true);
	
	//Эркюль Тонзаг
	sld = GetCharacter(NPC_GenerateCharacter("Tonzag", "Tonzag", "man", "man", 30, ENGLAND, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_46");
	sld.lastname = StringFromKey("QuestsUtilite_47");
	sld.greeting = "tonzag_2";
	sld.Dialog.Filename = "Quest\HollandGambit\Tonzag.c";
	sld.dialog.currentnode = "First time";
	sld.rank = 30;
	LAi_SetHP(sld, 250, 250);
	sld.money = 5000;
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	SetSelfSkill(sld, 60, 60, 65, 60, 50);
	SetShipSkill(sld, 50, 20, 20, 20, 20, 20, 70, 20, 70);
	SetSPECIAL(sld, 10, 3, 10, 3, 6, 10, 8);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "BladeDancer");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "GrapplingProfessional");
	SetCharacterPerk(sld, "MusketsShoot");
	GiveItem2Character(sld, "blade_07");
	sld.equip.blade = "blade_07";
	GiveItem2Character(sld, "pistol3");
	EquipCharacterbyItem(sld, "pistol3");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "grapeshot");
    TakeNItems(sld, "grapeshot", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", 2);
}

void SharlieNpcInit()//создаем всех ключевых персонажей по квестам Бремя Гасконца, Страж Истины здесь
{
	string sBlade;
	//Мишель де Монпе
	sld = GetCharacter(NPC_GenerateCharacter("Mishelle", "Migel_1", "man", "man", 60, FRANCE, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_48");
	sld.lastname = StringFromKey("QuestsUtilite_49");
	sld.greeting = "mishelle_1";
    sld.Dialog.Filename = "Quest\Sharlie\Mishelle.c";
	sld.dialog.currentnode = "First time";
	sld.rank = 60;
	SetSelfSkill(sld, 100, 100, 100, 100, 100);
    SetShipSkill(sld, 100, 100, 100, 100, 100, 100, 100, 100, 100);
	LAi_SetHP(sld, 700, 700);
	sld.PoisonResistent = true; // Addon 2016-1 Jason пиратская линейка
	GiveItem2Character(sld, "unarmed");
	sld.equip.blade = "unarmed";
	sld.equip.gun = "";
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	
	//аббат Бенуа
	sld = GetCharacter(NPC_GenerateCharacter("Benua", "abbat", "man", "man_B", 20, FRANCE, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_50");
	sld.lastname = StringFromKey("QuestsUtilite_51");
	sld.greeting = "Gr_Church";
    sld.Dialog.Filename = "Quest\Sharlie\Benua.c";
	sld.dialog.currentnode = "First time";
	sld.rank = 25;
	GiveItem2Character(sld, "unarmed");
	sld.equip.blade = "unarmed";
	sld.equip.gun = "";
	LAi_SetImmortal(sld, true);
	LAi_SetStayType(sld);
	sld.location = "FortFrance_church";
	sld.location.group = "reload";
	sld.location.locator = "reload2_back";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	
	//Фадей Московит
	sld = GetCharacter(NPC_GenerateCharacter("Fadey", "moscovit", "man", "moscovit", 30, FRANCE, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_52");
	sld.lastname = StringFromKey("QuestsUtilite_53");
	sld.greeting = "fadey";
	sld.location = "BasTer_houseSp1";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	sld.Dialog.Filename = "Quest\Sharlie\Fadey.c";
	sld.dialog.currentnode = "First time";
    SetSelfSkill(sld, 90, 90, 90, 70, 90);
    SetShipSkill(sld, 20, 90, 10, 10, 10, 20, 10, 10, 50);
	LAi_SetSitType(sld);
	LAi_SetHP(sld, 350.0, 350.0);
	LAi_SetImmortal(sld, true);
	GiveItem2Character(sld, "unarmed");
	sld.equip.blade = "unarmed";
	sld.equip.gun = "";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	
	// Диего де Монтойя
	sld = GetCharacter(NPC_GenerateCharacter("Diego", "diego_6", "man", "man_A", 1, SPAIN, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_54");
	sld.lastname = StringFromKey("QuestsUtilite_55");
	sld.greeting = "";
	sld.FaceId = 203;
    sld.Dialog.Filename = "Quest\Sharlie\Diego.c";
	sld.dialog.currentnode = "First time";
	sld.rank = 25+MOD_SKILL_ENEMY_RATE;
	LAi_SetHP(sld, 230+MOD_SKILL_ENEMY_RATE*35, 230+MOD_SKILL_ENEMY_RATE*35); 
	SetSelfSkill(sld, 90, 90, 90, 90, 90);
	SetShipSkill(sld, 90, 90, 90, 90, 90, 90, 90, 90, 90);
	SetSPECIAL(sld, 7, 5, 10, 5, 6, 10, 5);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "WindCatcher");
	SetCharacterPerk(sld, "SailsMan");
	SetCharacterPerk(sld, "Doctor1");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "LongRangeGrappling");
	SetCharacterPerk(sld, "GrapplingProfessional");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "BasicCommerce");
	SetCharacterPerk(sld, "AdvancedCommerce");
	sBlade = GetBestGeneratedItem("blade_20");
	GiveItem2Character(sld, sBlade);
	sld.equip.blade = sBlade;
	GiveItem2Character(sld, "pistol4");
	EquipCharacterbyItem(sld, "pistol4");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", MOD_SKILL_ENEMY_RATE/2);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	sld.cirassId = Items_FindItemIdx("cirass1"); 
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	
	// Алонсо де Мальдонадо
	sld = GetCharacter(NPC_GenerateCharacter("Maldonado", "Alonso", "man", "man", 1, SPAIN, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_56");
	sld.lastname = StringFromKey("QuestsUtilite_57");
	sld.greeting = "alonso";
    sld.Dialog.Filename = "Quest\Sharlie\Maldonado.c";
	sld.dialog.currentnode = "First time";
	sld.rank = 20+MOD_SKILL_ENEMY_RATE;
	LAi_SetHP(sld, 130+MOD_SKILL_ENEMY_RATE*35, 130+MOD_SKILL_ENEMY_RATE*35); 
	SetSelfSkill(sld, 90, 60, 60, 70, 90);
	SetShipSkill(sld, 70, 70, 70, 70, 70, 70, 70, 70, 70);
	SetSPECIAL(sld, 7, 5, 9, 7, 6, 8, 8);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "Doctor1");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "LongRangeGrappling");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "BasicCommerce");
	SetCharacterPerk(sld, "AdvancedCommerce");
	GiveItem2Character(sld, "blade_18");
	sld.equip.blade = "blade_18";
	GiveItem2Character(sld, "pistol5");
	EquipCharacterbyItem(sld, "pistol5");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", MOD_SKILL_ENEMY_RATE/2);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	sld.cirassId = Items_FindItemIdx("cirass1"); 
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	
	// Вильям Патерсон
	sld = GetCharacter(NPC_GenerateCharacter("Willy", "willy_6", "man", "man_A", 1, ENGLAND, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_58");
	sld.lastname = StringFromKey("QuestsUtilite_59");
	sld.greeting = "";
    sld.Dialog.Filename = "Quest\Sharlie\Willy.c";
	sld.dialog.currentnode = "First time";
	sld.FaceId = 202;
	sld.rank = 25+MOD_SKILL_ENEMY_RATE;
	LAi_SetHP(sld, 230+MOD_SKILL_ENEMY_RATE*35, 230+MOD_SKILL_ENEMY_RATE*35); 
	SetSelfSkill(sld, 100, 100, 100, 100, 90);
	SetShipSkill(sld, 90, 90, 90, 90, 90, 90, 90, 90, 90);
	SetSPECIAL(sld, 9, 3, 8, 6, 4, 10, 8);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "WindCatcher");
	SetCharacterPerk(sld, "SailsMan");
	SetCharacterPerk(sld, "Doctor1");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "LongRangeGrappling");
	SetCharacterPerk(sld, "GrapplingProfessional");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "BasicCommerce");
	SetCharacterPerk(sld, "AdvancedCommerce");
	sBlade = GetBestGeneratedItem("blade_21");
	GiveItem2Character(sld, sBlade);
	sld.equip.blade = sBlade;
	GiveItem2Character(sld, "pistol4");
	EquipCharacterbyItem(sld, "pistol4");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", MOD_SKILL_ENEMY_RATE/2);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	sld.PoisonResistent = true; // Addon 2016-1 Jason пиратская линейка
	sld.cirassId = Items_FindItemIdx("cirass1"); 
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	
	// Арчибальд Колхаун
	sld = GetCharacter(NPC_GenerateCharacter("Archy", "archy", "man", "man", 1, ENGLAND, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_60");
	sld.lastname = StringFromKey("QuestsUtilite_61");
	sld.greeting = "Archy";
    sld.Dialog.Filename = "Quest\Sharlie\Archy.c";
	sld.dialog.currentnode = "First time";
	sld.rank = 15+MOD_SKILL_ENEMY_RATE;
	LAi_SetHP(sld, 150+MOD_SKILL_ENEMY_RATE*30, 150+MOD_SKILL_ENEMY_RATE*30); 
	SetSelfSkill(sld, 90, 60, 60, 70, 90);
	SetShipSkill(sld, 70, 70, 70, 70, 70, 70, 70, 70, 70);
	SetSPECIAL(sld, 7, 5, 9, 7, 6, 8, 8);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "Doctor1");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "LongRangeGrappling");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "BasicCommerce");
	SetCharacterPerk(sld, "AdvancedCommerce");
	GiveItem2Character(sld, "blade_18");
	sld.equip.blade = "blade_18";
	GiveItem2Character(sld, "pistol5");
	EquipCharacterbyItem(sld, "pistol5");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", MOD_SKILL_ENEMY_RATE/2);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	sld.cirassId = Items_FindItemIdx("cirass1"); 
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
}

void SagaNpcInit()//создаем всех ключевых персонажей по квесту Пиратская Сага здесь
{
	//Ян Свенсон, Блювельд
	sld = GetCharacter(NPC_GenerateCharacter("Svenson", "Svenson", "man", "man", 1, ENGLAND, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_62");
	sld.lastname = StringFromKey("QuestsUtilite_63");
	sld.greeting = "svenson_1";
    sld.Dialog.Filename = "Quest\Saga\Svenson.c";
	sld.dialog.currentnode = "First time";
	sld.rank = 35;
	LAi_SetHP(sld, 600, 600); 
	SetSelfSkill(sld, 100, 100, 100, 100, 90);
	SetShipSkill(sld, 80, 85, 75, 80, 100, 65, 90, 60, 80);
	SetSPECIAL(sld, 8, 4, 10, 5, 5, 10, 6);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "WindCatcher");
	SetCharacterPerk(sld, "SailsMan");
	SetCharacterPerk(sld, "Doctor1");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "LongRangeGrappling");
	SetCharacterPerk(sld, "GrapplingProfessional");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "BasicCommerce");
	SetCharacterPerk(sld, "AdvancedCommerce");
	GiveItem2Character(sld, "blade_21");
	sld.equip.blade = "blade_21";
	GiveItem2Character(sld, "pistol5");
	EquipCharacterbyItem(sld, "pistol5");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", 10);
	sld.cirassId = Items_FindItemIdx("cirass1"); 
	LAi_SetImmortal(sld, true);
	sld.location = "Santacatalina_houseS1_residence";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	
	//жена Яна Свенсона - просто антураж дома
	sld = GetCharacter(NPC_GenerateCharacter("JS_girl", "Svenson_wife", "woman", "towngirl", 10, ENGLAND, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_64");
	sld.lastname = StringFromKey("QuestsUtilite_65");
	sld.greeting = "joanna";
    sld.Dialog.Filename = "Quest\Saga\OtherNPC.c";
	sld.dialog.currentnode = "js_girl";
	LAi_SetImmortal(sld, true);
	sld.location = "Santacatalina_houseS1";
	sld.location.group = "barmen";
	sld.location.locator = "stay";
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	
	//Натаниэль Хоук
	sld = GetCharacter(NPC_GenerateCharacter("Nathaniel", "Hawk_1", "man", "man_B", 25, PIRATE, -1, false, "quest"));
	SetFantomParamFromRank(sld, 25, true);
	sld.name = StringFromKey("QuestsUtilite_66");
	sld.lastname = StringFromKey("QuestsUtilite_67");
	sld.greeting = "Nathaniel";
    sld.Dialog.Filename = "Quest\Saga\Nathaniel.c";
	sld.dialog.currentnode = "First time";
	sld.rank = 25;
	GiveItem2Character(sld, "blade_11");
	sld.equip.blade = "blade_11";
	GiveItem2Character(sld, "pistol1");
	EquipCharacterbyItem(sld, "pistol1");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	sld.location = "FernandaDiffIndoor";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	LAi_SetGroundSitTypeNoGroup(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	
	//Даниэль Хоук ... Данни, Данни...
	sld = GetCharacter(NPC_GenerateCharacter("Danielle", "Danny", "woman", "danny", 1, ENGLAND, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_68");
	sld.lastname = StringFromKey("QuestsUtilite_69");
	sld.greeting = "Danny";
    sld.Dialog.Filename = "Quest\Saga\Danielle.c";
	sld.dialog.currentnode = "First time";
	sld.rank = 22;
	LAi_SetImmortal(sld, true); // временно
	LAi_SetHP(sld, 280, 280); 
	SetSelfSkill(sld, 70, 85, 60, 55, 60);
	SetShipSkill(sld, 50, 38, 41, 39, 85, 33, 44, 62, 63);
	SetSPECIAL(sld, 6, 7, 9, 4, 5, 9, 7);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "WindCatcher");
	SetCharacterPerk(sld, "SailsMan");
	SetCharacterPerk(sld, "Doctor1");
	GiveItem2Character(sld, "blade_10");
	sld.equip.blade = "blade_10";
	GiveItem2Character(sld, "pistol5");
	EquipCharacterbyItem(sld, "pistol5");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", 5);
	TakeNItems(sld, "potion3", 2);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");

	//Эдвард д'Ойли
	sld = GetCharacter(NPC_GenerateCharacter("Doylie", "citiz_6", "man", "man", 35, ENGLAND, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_70");
	sld.lastname = StringFromKey("QuestsUtilite_71");
	//sld.greeting = "";
    sld.Dialog.Filename = "Quest\Saga\Doylie.c";
	sld.dialog.currentnode = "First time";
	sld.rank = 35;
	GiveItem2Character(sld, "blade_17");
	sld.equip.blade = "blade_17";
	GiveItem2Character(sld, "pistol7");
	EquipCharacterbyItem(sld, "pistol7");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	
	//Лоуренс Белтроп
	sld = GetCharacter(NPC_GenerateCharacter("Beltrop", "Balthrop", "man", "balthrop", 35, PIRATE, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_72");
	sld.lastname = StringFromKey("QuestsUtilite_73");
	sld.greeting = "Beltrop";
    sld.Dialog.Filename = "Quest\Saga\Beltrop.c";
	sld.dialog.currentnode = "First time";
	sld.rank = 35;
	GiveItem2Character(sld, "blade_16");
	sld.equip.blade = "blade_16";
	GiveItem2Character(sld, "pistol6");
	EquipCharacterbyItem(sld, "pistol6");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	
	//Глэдис
	sld = GetCharacter(NPC_GenerateCharacter("Gladis", "Gladys", "woman", "woman", 10, ENGLAND, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_74");
	sld.lastname = StringFromKey("QuestsUtilite_75");
	sld.greeting = "gladis_1";
    sld.Dialog.Filename = "Quest\Saga\Gladis.c";
	sld.dialog.currentnode = "First time";
	sld.rank = 10;
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	
	//Элен
	sld = GetCharacter(NPC_GenerateCharacter("Helena", "Rumba", "woman", "rumba", 1, ENGLAND, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_76");
	sld.lastname = StringFromKey("QuestsUtilite_77");
	sld.Dialog.Filename = "Quest\Saga\Helena.c";
	sld.dialog.currentnode = "First time";
	sld.greeting = "helena_1";
	sld.rank = 15;
	LAi_SetHP(sld, 220, 220); 
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	LAi_SetImmortal(sld, true); // временно
	SetSelfSkill(sld, 70, 50, 5, 60, 20);
	SetShipSkill(sld, 40, 40, 65, 65, 80, 60, 30, 60, 40);
	SetSPECIAL(sld, 5, 6, 6, 6, 10, 10, 6);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "ByWorker");
	SetCharacterPerk(sld, "ShipEscape");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "WindCatcher");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "BasicCommerce");
	SetCharacterPerk(sld, "Doctor1");
	SetCharacterPerk(sld, "BasicBattleState");
	SetCharacterPerk(sld, "AdvancedBattleState");
	SetCharacterPerk(sld, "ByWorker2");
	
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	
	//Хосе Диос - картограф
	sld = GetCharacter(NPC_GenerateCharacter("Dios", "Dios", "man", "man_B", 16, SPAIN, -1, false, "citizen"));
	SetFantomParamFromRank(sld, 16, true);
	sld.name = StringFromKey("QuestsUtilite_78");
	sld.lastname = StringFromKey("QuestsUtilite_79");
	sld.greeting = "Dios";
    sld.Dialog.Filename = "Quest\Saga\Dios.c";
	sld.dialog.currentnode = "First time";
	LAi_SetImmortal(sld, true);
	GiveItem2Character(sld, "blade_08");
	sld.equip.blade = "blade_08";
	sld.location = "Santodomingo_houseSp2";
	sld.location.group = "barmen";
	sld.location.locator = "stay";
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	
	//Альберт Локсли - адвокат
	sld = GetCharacter(NPC_GenerateCharacter("Loxly", "advocat", "man", "man", 20, ENGLAND, -1, false, "citizen"));
	SetFantomParamFromRank(sld, 20, true);
	sld.name = StringFromKey("QuestsUtilite_80");
	sld.lastname = StringFromKey("QuestsUtilite_81");
	sld.greeting = "Loxly";
    sld.Dialog.Filename = "Quest\Saga\Loxly.c";
	sld.dialog.currentnode = "First time";
	LAi_SetImmortal(sld, true);
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed");
	sld.location = "PortRoyal_houseSp4";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
}

void LSC_NpcInit()// ключевые НПС LSC
{
	//Акула Додсон
	sld = GetCharacter(NPC_GenerateCharacter("Dodson", "Shark", "man", "man", 1, PIRATE, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_82");
	sld.lastname = StringFromKey("QuestsUtilite_83");
	sld.greeting = "dodson_1";
    sld.Dialog.Filename = "Quest\LSC\Dodson.c";
	sld.dialog.currentnode = "First time";
	sld.rank = 35;
	LAi_SetHP(sld, 480, 480); 
	SetSelfSkill(sld, 80, 100, 100, 90, 70);
	SetShipSkill(sld, 90, 80, 90, 85, 95, 60, 100, 50, 60);
	SetSPECIAL(sld, 9, 5, 10, 5, 5, 10, 4);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "LongRangeGrappling");
	SetCharacterPerk(sld, "GrapplingProfessional");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	GiveItem2Character(sld, "blade_31");
	sld.equip.blade = "blade_31";
	GiveItem2Character(sld, "pistol4");
	EquipCharacterbyItem(sld, "pistol4");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", 5);
	sld.location = "SanAugustineResidence";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	LAi_SetHuberType(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "LSC_SHARK");

	// Чад Каппер
	sld = GetCharacter(NPC_GenerateCharacter("Capper", "Chad", "man", "man", 1, PIRATE, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_84");
	sld.lastname = StringFromKey("QuestsUtilite_85");
	sld.greeting = "Capper";
    sld.Dialog.Filename = "Quest\LSC\Capper.c";
	sld.rank = 30;
	if (MOD_SKILL_ENEMY_RATE >= 6) LAi_SetHP(sld, 250+MOD_SKILL_ENEMY_RATE*35, 250+MOD_SKILL_ENEMY_RATE*35);
	else LAi_SetHP(sld, 150+MOD_SKILL_ENEMY_RATE*30, 150+MOD_SKILL_ENEMY_RATE*30);
	SetSelfSkill(sld, 70, 80, 90, 90, 70);
	SetShipSkill(sld, 40, 40, 60, 60, 80, 40, 100, 20, 20);
	SetSPECIAL(sld, 9, 5, 9, 4, 4, 10, 6);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "LongRangeGrappling");
	SetCharacterPerk(sld, "GrapplingProfessional");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	GiveItem2Character(sld, "blade_16");
	sld.equip.blade = "blade_16";
	GiveItem2Character(sld, "pistol4");
	EquipCharacterbyItem(sld, "pistol4");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", MOD_SKILL_ENEMY_RATE/2);
	sld.location = "TartarusPrison";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	LAi_SetHuberType(sld);
	
	//Лейтон Декстер
	sld = GetCharacter(NPC_GenerateCharacter("Dexter", "Dexter", "man", "man", 1, PIRATE, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_86");
	sld.lastname = StringFromKey("QuestsUtilite_87");
	sld.greeting = "dexter_1";
    sld.Dialog.Filename = "Quest\LSC\Dexter.c";
	sld.dialog.currentnode = "First time";
	sld.rank = 28;
	LAi_SetHP(sld, 380, 380); 
	SetSelfSkill(sld, 70, 70, 60, 70, 60);
	SetShipSkill(sld, 80, 90, 40, 45, 85, 75, 40, 30, 70);
	SetSPECIAL(sld, 7, 4, 8, 9, 9, 8, 6);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "BasicCommerce");
	SetCharacterPerk(sld, "AdvancedCommerce");
	SetCharacterPerk(sld, "BasicBattleState");
	SetCharacterPerk(sld, "AdvancedBattleState");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	GiveItem2Character(sld, "blade_10");
	sld.equip.blade = "blade_10";
	GiveItem2Character(sld, "pistol6");
	EquipCharacterbyItem(sld, "pistol6");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", 2+makeint(MOD_SKILL_ENEMY_RATE * 0.5));
	sld.location = "SanAugustineResidence";
	sld.location.group = "goto";
	sld.location.locator = "goto11";
	LAi_SetStayType(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "LSC_SHARK");
	
	// Чёрный Эдди
	sld = GetCharacter(NPC_GenerateCharacter("Eddy", "Black", "man", "man", 1, PIRATE, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_88");
	sld.lastname = StringFromKey("QuestsUtilite_89");
	sld.greeting = "eddy_1";
    sld.Dialog.Filename = "Quest\LSC\Eddy_Rivados.c";
	sld.rank = 28;
	LAi_SetHP(sld, 350, 350); 
	SetSelfSkill(sld, 60, 75, 60, 70, 60);
	SetShipSkill(sld, 80, 40, 90, 85, 30, 30, 50, 20, 50);
	SetSPECIAL(sld, 9, 5, 9, 4, 4, 10, 6);
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	GiveItem2Character(sld, "blade_16");
	sld.equip.blade = "blade_16";
	GiveItem2Character(sld, "pistol5");
	EquipCharacterbyItem(sld, "pistol5");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", 5);
	sld.location = "ProtectorFisher";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "LSC_RIVADOS");
	
	// колдун ривадос Чимисет
	sld = GetCharacter(NPC_GenerateCharacter("Chimiset", "Chimiset2", "man", "man_A1", 1, PIRATE, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_90");
	sld.lastname = StringFromKey("QuestsUtilite_91");
	sld.greeting = "Chimiset";
    sld.Dialog.Filename = "Quest\LSC\Chimiset.c";
	sld.rank = 17;
	LAi_SetHP(sld, 160, 160); 
	SetSelfSkill(sld, 50, 55, 50, 40, 30);
	SetShipSkill(sld, 50, 10, 10, 10, 10, 10, 10, 90, 10);
	SetSPECIAL(sld, 9, 5, 9, 4, 4, 10, 6);
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "Doctor1");
	SetCharacterPerk(sld, "Doctor2");
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed");
	LAi_group_MoveCharacter(sld, "LSC_RIVADOS");
	
	// Зикомо
	sld = GetCharacter(NPC_GenerateCharacter("Zikomo", "Zikomo", "man", "man", 1, PIRATE, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_92");
	sld.lastname = StringFromKey("QuestsUtilite_93");
	sld.greeting = "Zikomo";
    sld.Dialog.Filename = "Quest\LSC\Zikomo.c";
	sld.rank = 24;
	LAi_SetHP(sld, 280, 280); 
	SetSelfSkill(sld, 30, 55, 80, 50, 50);
	SetShipSkill(sld, 40, 20, 10, 15, 10, 10, 10, 10, 70);
	SetSPECIAL(sld, 7, 3, 10, 4, 6, 10, 8);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "HardHitter");
	GiveItem2Character(sld, "topor_01");
	sld.equip.blade = "topor_01";
	GiveItem2Character(sld, "pistol1");
	EquipCharacterbyItem(sld, "pistol1");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", 5);
	sld.location = "ProtectorFisher";
	sld.location.group = "goto";
	sld.location.locator = "goto4";
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "LSC_RIVADOS");
	
	// Джузеппе Фацио - посредник
	sld = GetCharacter(NPC_GenerateCharacter("Facio", "Facio", "man", "man_B", 1, PIRATE, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_94");
	sld.lastname = StringFromKey("QuestsUtilite_95");
	sld.greeting = "facio_1";
    sld.Dialog.Filename = "Quest\LSC\Facio.c";
	sld.city = "LostShipsCity";
	sld.cityTape = "diplomat"; //тип нпс
	sld.rank = 15;
	LAi_SetHP(sld, 120, 120); 
	SetSelfSkill(sld, 40, 25, 10, 30, 80);
	SetShipSkill(sld, 80, 90, 10, 10, 10, 10, 10, 10, 10);
	SetSPECIAL(sld, 5, 4, 6, 9, 9, 6, 6);
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "BasicCommerce");
	SetCharacterPerk(sld, "AdvancedCommerce");
	GiveItem2Character(sld, "blade_15");
	sld.equip.blade = "blade_15";
	GiveItem2Character(sld, "pistol5");
	EquipCharacterbyItem(sld, "pistol5");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", 2);
	sld.location = "CarolineBank";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	LAi_SetSitType(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	
	// Аксель Йост - торговец
	sld = GetCharacter(NPC_GenerateCharacter("Axel", "Axel", "man", "man", 1, PIRATE, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_96");
	sld.lastname = StringFromKey("QuestsUtilite_97");
	sld.greeting = "Axel";
    sld.Dialog.Filename = "Quest\LSC\Axel.c";
	sld.city = "LostShipsCity";
	sld.cityTape = "trader"; //тип нпс
	sld.rank = 19;
	LAi_SetHP(sld, 150, 150); 
	SetSelfSkill(sld, 55, 35, 10, 35, 90);
	SetShipSkill(sld, 80, 100, 10, 10, 10, 10, 10, 10, 10);
	SetSPECIAL(sld, 4, 4, 5, 10, 10, 7, 6);
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "BasicCommerce");
	SetCharacterPerk(sld, "AdvancedCommerce");
	GiveItem2Character(sld, "blade_15");
	sld.equip.blade = "blade_15";
	GiveItem2Character(sld, "pistol6");
	EquipCharacterbyItem(sld, "pistol6");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", 2);
	sld.location = "EsmeraldaStoreBig";
	sld.location.group = "barmen";
	sld.location.locator = "stay";
	sld.Merchant = true;
	sld.Merchant.type = "LSC_trader";
	sld.money = TRADER_MIN_MONEY + rand(TRADER_NORM);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "LSC_NARVAL");
	
	// Санчо Карпентеро - бармен ...Санчо Панса...
	sld = GetCharacter(NPC_GenerateCharacter("Carpentero", "Carpentero", "man", "man", 1, PIRATE, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_98");
	sld.lastname = StringFromKey("QuestsUtilite_99");
	sld.greeting = "Carpentero";
    sld.Dialog.Filename = "Quest\LSC\Carpentero.c";
	sld.city = "LostShipsCity";
	sld.cityTape = "barmen"; //тип нпс
	sld.rank = 18;
	LAi_SetHP(sld, 140, 140); 
	SetSelfSkill(sld, 25, 25, 20, 25, 60);
	SetShipSkill(sld, 80, 90, 15, 5, 5, 5, 10, 10, 30);
	SetSPECIAL(sld, 6, 6, 5, 8, 8, 7, 6);
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "BasicCommerce");
	SetCharacterPerk(sld, "AdvancedCommerce");
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed");
	sld.location = "FleuronTavern";
	sld.location.group = "barmen";
	sld.location.locator = "stay";
	LAi_SetBarmanType(sld);
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	
	// брат Юлиан - священник
	sld = GetCharacter(NPC_GenerateCharacter("Julian", "priest_1", "man", "man", 1, PIRATE, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_100");
	sld.lastname = StringFromKey("QuestsUtilite_101");
	sld.greeting = "padre_1";
    sld.Dialog.Filename = "Quest\LSC\Julian_priest.c";
	sld.city = "LostShipsCity";
	sld.cityTape = "priest"; //тип нпс
	sld.rank = 12;
	LAi_SetHP(sld, 110, 110); 
	SetSelfSkill(sld, 15, 25, 10, 15, 50);
	SetShipSkill(sld, 80, 90, 15, 5, 5, 5, 10, 10, 30);
	SetSPECIAL(sld, 6, 6, 6, 6, 8, 8, 6);
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "BasicCommerce");
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed");
	sld.location = "GloriaChurch";
	sld.location.group = "barmen";
	sld.location.locator = "stay";
	sld.cityTape = "priest";
	LAi_SetPriestType(sld);
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	
	// Мэри Каспер ... Мэри... никому теперь не верит Мэри... лучшей подруги и любовницы для ГГ не будет :)
	sld = GetCharacter(NPC_GenerateCharacter("Mary", "Mary", "woman", "mary", 1, PIRATE, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_102");
	sld.lastname = StringFromKey("QuestsUtilite_103");
	sld.Dialog.Filename = "Quest\LSC\Mary.c";
	sld.dialog.currentnode = "First time";
	sld.greeting = ""; // установим по нужным местам
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true; 
	sld.rank = 20;
	LAi_SetHP(sld, 250, 250); 
	SetSelfSkill(sld, 95, 50, 50, 90, 50);
	SetShipSkill(sld, 90, 25, 5, 5, 5, 5, 5, 15, 30);
	SetSPECIAL(sld, 6, 6, 8, 3, 9, 10, 4);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "BladeDancer");
	SetCharacterPerk(sld, "ByWorker");
	SetCharacterPerk(sld, "Doctor1");
	GiveItem2Character(sld, "blade_17");
	sld.equip.blade = "blade_17";
	GiveItem2Character(sld, "pistol4");
	EquipCharacterbyItem(sld, "pistol4");
	GiveItem2Character(sld, "cirass6");
	EquipCharacterbyItem(sld, "cirass6");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", 5);
	sld.location = "CeresSmithy";
	sld.location.group = "barmen";
	sld.location.locator = "stay";
	LAi_SetOwnerType(sld);
	
	// Хенрик Ведекер - механик
	sld = GetCharacter(NPC_GenerateCharacter("Mechanic", "Mechanic", "man", "man", 1, PIRATE, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_104");
	sld.lastname = StringFromKey("QuestsUtilite_105");
	sld.greeting = "Mechanic";
    sld.Dialog.Filename = "Quest\LSC\Mechanic.c";
	sld.rank = 25;
	LAi_SetHP(sld, 180, 180); 
	SetSelfSkill(sld, 30, 25, 20, 30, 80);
	SetShipSkill(sld, 80, 10, 10, 10, 10, 10, 10, 10, 10);
	SetSPECIAL(sld, 5, 4, 6, 10, 10, 6, 8);
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "BasicCommerce");
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed");
	sld.location = "SanGabrielMechanic";
	sld.location.group = "barmen";
	sld.location.locator = "stay";
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "LSC_NARVAL");
	
	// Юрген Шмидт - оружейник
	sld = GetCharacter(NPC_GenerateCharacter("Schmidt", "Schmidt", "man", "man", 1, PIRATE, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_106");
	sld.lastname = StringFromKey("QuestsUtilite_107");
	sld.greeting = "Schmidt";
    sld.Dialog.Filename = "Quest\LSC\Schmidt.c";
	sld.rank = 28;
	LAi_SetHP(sld, 250, 250); 
	SetSelfSkill(sld, 10, 35, 70, 90, 70);
	SetShipSkill(sld, 50, 10, 10, 10, 10, 10, 10, 10, 10);
	SetSPECIAL(sld, 10, 4, 10, 3, 10, 8, 4);
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "BasicCommerce");
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed");
	sld.location = "CeresSmithy";
	sld.location.group = "quest";
	sld.location.locator = "quest1";
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "LSC_NARVAL");
	
	//Дональд Гринспи - лидер нарвалов
	sld = GetCharacter(NPC_GenerateCharacter("Grinspy", "Donald", "man", "man", 1, PIRATE, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_108");
	sld.lastname = StringFromKey("QuestsUtilite_109");
	sld.greeting = "Grinspy";
    sld.Dialog.Filename = "Quest\LSC\Grinspy_Narval.c";
	sld.dialog.currentnode = "First time";
	sld.rank = 25;
	LAi_SetHP(sld, 280, 280); 
	SetSelfSkill(sld, 50, 60, 85, 75, 65);
	SetShipSkill(sld, 60, 70, 45, 55, 80, 75, 20, 20, 50);
	SetSPECIAL(sld, 8, 3, 8, 8, 5, 8, 5);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "BasicCommerce");
	SetCharacterPerk(sld, "AdvancedCommerce");
	SetCharacterPerk(sld, "BasicBattleState");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "LongRangeGrappling");
	GiveItem2Character(sld, "blade_31");
	sld.equip.blade = "blade_31";
	GiveItem2Character(sld, "pistol4");
	EquipCharacterbyItem(sld, "pistol4");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", 5);
	sld.location = "EsmeraldaStoreBig";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "LSC_NARVAL");
	
	// Оле Кристиансен - Белый Мальчик ...Оле...оле-оле-оле... :)
	sld = GetCharacter(NPC_GenerateCharacter("Ole", "Ole", "man", "man", 1, PIRATE, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_110");
	sld.lastname = StringFromKey("QuestsUtilite_111");
	sld.greeting = "Ole";
    sld.Dialog.Filename = "Quest\LSC\Ole.c";
	sld.rank = 10;
	LAi_SetHP(sld, 90, 90); 
	SetSelfSkill(sld, 10, 15, 10, 15, 90);
	SetShipSkill(sld, 10, 5, 5, 5, 5, 5, 10, 10, 90);
	SetSPECIAL(sld, 4, 10, 3, 3, 5, 8, 10);
	SetCharacterPerk(sld, "BasicDefense");
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed");
	LAi_SetImmortal(sld, true); // ключевой персонаж
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	
	// Циклоп Марчелло ...Циклопус... или Суслопус :)
	sld = GetCharacter(NPC_GenerateCharacter("Marchello", "Cyclop", "man", "man", 15, PIRATE, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_112");
	sld.lastname = StringFromKey("QuestsUtilite_113");
	sld.greeting = "Marchello";
    sld.Dialog.Filename = "Quest\LSC\OtherNPC.c";
	sld.dialog.currentnode = "First time";
	GiveItem2Character(sld, "blade_21");
	sld.equip.blade = "blade_21";
	GiveItem2Character(sld, "pistol6");
	EquipCharacterbyItem(sld, "pistol6");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", 3);
}

void LSC_CreateStateCitizens() // создание горожан-статиков LSC, 20 штук
{
	// ------------------------ внешние горожане ------------------------	
	// внешний горожанин Дугал Эбботт - дворянин
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Dugal", "citiz_3", "man", "man", 25, PIRATE, -1, true, "soldier"));
	SetFantomParamFromRank(sld, 25, true);
	sld.name = StringFromKey("QuestsUtilite_114");
	sld.lastname = StringFromKey("QuestsUtilite_115");
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto02_1"; 
	sld.location.baseShip = "02"; //базовый корабль в ГПК - Каролина
	sld.location.baseLocator = sld.location.locator; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 2; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LSC\Citizen\LSC_Dugal.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "noble_male";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_CitizenConflict");
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	SaveCurrentNpcQuestDateParam(sld, "location");
	sld.LSC_clan = true;

	// внешний горожанин Лайонел Маскетт - мещанин
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Lionel", "citiz_11", "man", "man", 20, PIRATE, -1, true, "citizen"));
	SetFantomParamFromRank(sld, 20, true);
	sld.name = StringFromKey("QuestsUtilite_116");
	sld.lastname = StringFromKey("QuestsUtilite_117");
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto09_3"; 
	sld.location.baseShip = "09"; //базовый корабль в ГПК - Плуто
	sld.location.baseLocator = sld.location.locator; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 4; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LSC\Citizen\LSC_Lionel.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "citizen_male";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_CitizenConflict");
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	SaveCurrentNpcQuestDateParam(sld, "location");
	sld.LSC_clan = true;

	// внешний горожанин Гхерад Смиитс - матрос
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Gherad", "citiz_38", "man", "man", 18, PIRATE, -1, false, "citizen"));
	SetFantomParamFromRank(sld, 18, true);
	sld.name = StringFromKey("QuestsUtilite_118");
	sld.lastname = StringFromKey("QuestsUtilite_119");
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto05_1"; 
	sld.location.baseShip = "05"; //базовый корабль в ГПК - Флерон
	sld.location.baseLocator = sld.location.locator; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 3; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LSC\Citizen\LSC_Gherad.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "town_sailor";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_CitizenConflict");
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	SaveCurrentNpcQuestDateParam(sld, "location");
	sld.LSC_clan = true;

	// внешний горожанин Ришард Шамбон - контрабандист
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Rishard", "Shambone", "man", "man", 17, PIRATE, -1, false, "marginal"));
	SetFantomParamFromRank(sld, 17, true);
	sld.name = StringFromKey("QuestsUtilite_120");
	sld.lastname = StringFromKey("QuestsUtilite_121");
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto08_1"; 
	sld.location.baseShip = "08"; //базовый корабль в ГПК - Глория
	sld.location.baseLocator = sld.location.locator; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 4; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LSC\Citizen\LSC_Rishard.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "marginal";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_CitizenConflict");
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	SaveCurrentNpcQuestDateParam(sld, "location");
	sld.LSC_clan = true;

	// внешний горожанин Альваро Гомец - капитан
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Alvaro", "mercen_23", "man", "man", 28, PIRATE, -1, false, "soldier"));
	SetFantomParamFromRank(sld, 28, true);
	sld.name = StringFromKey("QuestsUtilite_122");
	sld.lastname = StringFromKey("QuestsUtilite_123");
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto09_1"; 
	sld.location.baseShip = "09"; //базовый корабль в ГПК - Плуто
	sld.location.baseLocator = sld.location.locator; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 4; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LSC\Citizen\LSC_Alvaro.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "captain";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_CitizenConflict");
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	SaveCurrentNpcQuestDateParam(sld, "location");
	sld.LSC_clan = true;

	// внешний горожанин Виктор Кассель - бандит
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Victor", "mercen_20", "man", "man", 30, PIRATE, -1, true, "marginal"));
	SetFantomParamFromRank(sld, 30, true);
	sld.name = StringFromKey("QuestsUtilite_124");
	sld.lastname = StringFromKey("QuestsUtilite_125");
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto11_1"; 
	sld.location.baseShip = "11"; //базовый корабль в ГПК - Сан-Августин
	sld.location.baseLocator = sld.location.locator; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 4; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LSC\Citizen\LSC_Victor.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "town_pirate";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_CitizenConflict");
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	SaveCurrentNpcQuestDateParam(sld, "location");
	sld.LSC_clan = true;
	
	// внешний горожанин Адольф Барбье - авантюрист
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Adolf", "Adolf", "man", "man", 22, PIRATE, -1, true, "marginal"));
	SetFantomParamFromRank(sld, 22, true);
	sld.name = StringFromKey("QuestsUtilite_126");
	sld.lastname = StringFromKey("QuestsUtilite_127");
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto05_3"; 
	sld.location.baseShip = "05"; //базовый корабль в ГПК - Флерон
	sld.location.baseLocator = sld.location.locator; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 5; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LSC\Citizen\LSC_Adolf.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "town_pirate";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	SaveCurrentNpcQuestDateParam(sld, "location");
	sld.LSC_clan = true;
	
	// внешний горожанин Куранай - индеец
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Curanai", "miskito_4", "man", "man", 18, PIRATE, -1, true, "native"));
	SetFantomParamFromRank(sld, 18, true);
	sld.name = StringFromKey("QuestsUtilite_128");
	sld.lastname = StringFromKey("QuestsUtilite_129");
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto14_1"; 
	sld.location.baseShip = "14"; //базовый корабль в ГПК - Санта-Флорентина
	sld.location.baseLocator = sld.location.locator; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 4; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LSC\Citizen\LSC_Curanai.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "indian_male";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_CitizenConflict");
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	SaveCurrentNpcQuestDateParam(sld, "location");
	sld.LSC_clan = true;
	sld.Merchant.type = "LSC_indian";
	sld.money = 0;
	
	// внешняя горожанка Рамона Лоцано
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Ramona", "women_16", "woman", "towngirl", 14, PIRATE, -1, true, "citizen"));
	SetFantomParamFromRank(sld, 14, true);
	sld.name = StringFromKey("QuestsUtilite_130");
	sld.lastname = StringFromKey("QuestsUtilite_131");
	RemoveAllCharacterItems(sld, true);
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto15_1"; 
	sld.location.baseShip = "15"; //базовый корабль в ГПК - Эва
	sld.location.baseLocator = sld.location.locator; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 4; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LSC\Citizen\LSC_Ramona.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "Gr_Woman_Citizen";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_CitizenConflict");
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	SaveCurrentNpcQuestDateParam(sld, "location");
	sld.LSC_clan = true;

	// ------------------------ внешние горожане в таверне ------------------------
	// в таверне Оеларт Котеел - канонир (возможный офицер)
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Oelart", "mercen_3", "man", "man", 20, PIRATE, -1, false, "citizen"));
	SetFantomParamFromRank(sld, 20, true);
	sld.name = StringFromKey("QuestsUtilite_132");
	sld.lastname = StringFromKey("QuestsUtilite_133");
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit2"; 
	sld.location.baseShip = "02"; //базовый корабль в ГПК - Каролина
	sld.location.baseLocator = "goto02_2"; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 6; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LSC\Citizen\LSC_Oelart.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "town_sailor";
	LAi_SetSitType(sld);
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_CitizenConflict");
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	SaveCurrentNpcQuestDateParam(sld, "location");
	sld.LSC_clan = true;

	// в таверне Джаспер Пратт - каторжник
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Jasper", "prizon_7", "man", "man_B", 15, PIRATE, -1, true, "slave"));
	SetFantomParamFromRank(sld, 15, true);
	sld.name = StringFromKey("QuestsUtilite_134");
	sld.lastname = StringFromKey("QuestsUtilite_135");
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit3"; 
	sld.location.baseShip = "09"; //базовый корабль в ГПК - Плуто
	sld.location.baseLocator = "goto09_2"; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 5; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LSC\Citizen\LSC_Jasper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "marginal";
	LAi_SetSitType(sld);
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_CitizenConflict");
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	SaveCurrentNpcQuestDateParam(sld, "location");
	sld.LSC_clan = true;

	// в таверне Леонард Маскетт - пьяница
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Leonard", "LeoMaskett", "man", "man", 12, PIRATE, -1, false, "citizen"));
	SetFantomParamFromRank(sld, 12, true);
	sld.name = StringFromKey("QuestsUtilite_136");
	sld.lastname = StringFromKey("QuestsUtilite_137");
	sld.city = "LostShipsCity";
	sld.location = "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit5"; 
	sld.location.baseShip = "05"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto05_2"; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 7; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LSC\Citizen\LSC_Leonard.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "habitue";
	LAi_SetSitType(sld);
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_CitizenConflict");
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	SaveCurrentNpcQuestDateParam(sld, "location");
	sld.LSC_clan = true;

	// в таверне Джозеф Лодердэйл - английский военный офицер
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Josef", "off_eng_2", "man", "man", 35, PIRATE, -1, true, "soldier"));
	SetFantomParamFromRank(sld, 35, true);
	sld.name = StringFromKey("QuestsUtilite_138");
	sld.lastname = StringFromKey("QuestsUtilite_139");
	sld.city = "LostShipsCity";
	sld.location = "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit8"; 
	sld.location.baseShip = "08"; //базовый корабль в ГПК - Глория
	sld.location.baseLocator = "goto08_3";  
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 3; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LSC\Citizen\LSC_Josef.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "captain";
	LAi_SetSitType(sld);
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_CitizenConflict");
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	SaveCurrentNpcQuestDateParam(sld, "location");
	sld.LSC_clan = true;

	// в таверне Лоренцо Сольдерра - испанский военный офицер
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Lorenzo", "off_spa_4", "man", "man", 35, PIRATE, -1, false, "soldier"));
	SetFantomParamFromRank(sld, 35, true);
	sld.name = StringFromKey("QuestsUtilite_140");
	sld.lastname = StringFromKey("QuestsUtilite_141");
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit6"; 
	sld.location.baseShip = "14"; //базовый корабль в ГПК - Санта-Флорентина
	sld.location.baseLocator = "goto14_2";  
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 3; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LSC\Citizen\LSC_Lorenzo.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "captain";
	LAi_SetSitType(sld);
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_CitizenConflict");
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	SaveCurrentNpcQuestDateParam(sld, "location");
	sld.LSC_clan = true;
	
	// в таверне Жаклин Тьюрам - торговый капитан
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Jacklin", "citiz_26", "man", "man", 20, PIRATE, -1, false, "soldier"));
	SetFantomParamFromRank(sld, 20, true);
	sld.name = StringFromKey("QuestsUtilite_142");
	sld.lastname = StringFromKey("QuestsUtilite_143");
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit7"; 
	sld.location.baseShip = "11"; //базовый корабль в ГПК - Сан-Августин
	sld.location.baseLocator = "goto11_2";  
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 4; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LSC\Citizen\LSC_Jacklin.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "captain";
	LAi_SetSitType(sld);
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_CitizenConflict");
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	SaveCurrentNpcQuestDateParam(sld, "location");
	sld.LSC_clan = true;

	// ------------------------ внешние горожане в церкви -----------------------
	// в церкви Джиллиан Стайнер
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Jillian", "women_15", "woman", "towngirl", 12, PIRATE, -1, false, "citizen"));
	SetFantomParamFromRank(sld, 12, true);
	sld.name = StringFromKey("QuestsUtilite_144");
	sld.lastname = StringFromKey("QuestsUtilite_145");
	RemoveAllCharacterItems(sld, true);
	sld.city = "LostShipsCity";
	sld.location	= "GloriaChurch";
	sld.location.group = "goto";
	sld.location.locator = "goto1"; 
	sld.location.baseShip = "08"; //базовый корабль в ГПК - Глория
	sld.location.baseLocator = "goto08_3"; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 4; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LSC\Citizen\LSC_Jillian.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "Gr_Woman_Citizen";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_CitizenConflict");
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	SaveCurrentNpcQuestDateParam(sld, "location");
	sld.LSC_clan = true;

	// в церкви Таннеке Эверс
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Tanneke", "women_13", "woman", "towngirl", 13, PIRATE, -1, false, "citizen"));
	SetFantomParamFromRank(sld, 13, true);
	sld.name = StringFromKey("QuestsUtilite_146");
	sld.lastname = StringFromKey("QuestsUtilite_147");
	RemoveAllCharacterItems(sld, true);
	sld.city = "LostShipsCity";
	sld.location	= "GloriaChurch";
	sld.location.group = "goto";
	sld.location.locator = "goto2"; 
	sld.location.baseShip = "15"; //базовый корабль в ГПК - Эва
	sld.location.baseLocator = "goto15_3"; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 5; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LSC\Citizen\LSC_Tanneke.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "Gr_Woman_Citizen";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_CitizenConflict");
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	SaveCurrentNpcQuestDateParam(sld, "location");
	sld.LSC_clan = true;

	// ------------------------ внутренние горожане ------------------------

	// внутреняя горожанка Орели Бертин
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Oreli", "women_18", "woman", "towngirl", 11, PIRATE, -1, false, "citizen"));
	SetFantomParamFromRank(sld, 11, true);
	sld.name = StringFromKey("QuestsUtilite_148");
	sld.lastname = StringFromKey("QuestsUtilite_149");
	RemoveAllCharacterItems(sld, true);
	sld.city = "LostShipsCity";
	sld.location	= "PlutoStoreSmall";
	sld.location.group = "barmen";
	sld.location.locator = "stay"; 
	sld.location.baseShip = "09"; //базовый корабль в ГПК - Плуто
	sld.location.baseLocator = "goto09_0"; 
	sld.location.baseLocation = "PlutoStoreSmall"; //базовая внутреняя локация
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 6; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LSC\Citizen\LSC_Oreli.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizenHome"; //тип нпс
	sld.greeting = "Gr_Woman_Citizen";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetOwnerType(sld);
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_CitizenConflict");
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	SaveCurrentNpcQuestDateParam(sld, "location");
	sld.LSC_clan = true;

	// внутрений горожанин Антонио Бетанкур
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Betancur", "Betancur", "man", "man", 20, PIRATE, -1, false, "citizen"));
	SetFantomParamFromRank(sld, 20, true);
	sld.name = StringFromKey("QuestsUtilite_150");
	sld.lastname = StringFromKey("QuestsUtilite_151");
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "PlutoStoreSmall";
	sld.location.group = "barmen";
	sld.location.locator = "bar1"; 
	sld.location.baseShip = "09"; //базовый корабль в ГПК - Плуто
	sld.location.baseLocator = "goto09_4"; 
	sld.location.baseLocation = "PlutoStoreSmall"; //базовая внутреняя локация
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 5; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LSC\Citizen\LSC_Betancur.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizenHome"; //тип нпс
	sld.greeting = "noble_male";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetOwnerType(sld);
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_CitizenConflict");
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	SaveCurrentNpcQuestDateParam(sld, "location");
	sld.LSC_clan = true;

	// внутреняя горожанка Сесиль Галард
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Sesil", "women_17", "woman", "towngirl", 10, PIRATE, -1, false, "citizen"));
	SetFantomParamFromRank(sld, 10, true);
	sld.name = StringFromKey("QuestsUtilite_152");
	sld.lastname = StringFromKey("QuestsUtilite_153");
	RemoveAllCharacterItems(sld, true);
	sld.city = "LostShipsCity";
	sld.location	= "AvaShipInside3";
	sld.location.group = "barmen";
	sld.location.locator = "stay"; 
	sld.location.baseShip = "15"; //базовый корабль в ГПК - Эва
	sld.location.baseLocator = "goto15_0"; 
	sld.location.baseLocation = "AvaShipInside3"; //базовая внутреняя локация
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 5; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LSC\Citizen\LSC_Sesil.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizenHome"; //тип нпс
	sld.greeting = "Gr_SesilGalard";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetOwnerType(sld);
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LSC_CitizenConflict");
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	SaveCurrentNpcQuestDateParam(sld, "location");
	sld.LSC_clan = true;
	
	//официантка Наталия Бушелл
	sld = GetCharacter(NPC_GenerateCharacter("Natalie_Waitress", "women_11", "woman", "towngirl", 10, PIRATE, -1, false, "citizen"));
	SetFantomParamFromRank(sld, 10, true);
	sld.name = StringFromKey("QuestsUtilite_154");
	sld.lastname = StringFromKey("QuestsUtilite_155");
	RemoveAllCharacterItems(sld, true);
	sld.location	= "FleuronTavern";
	sld.location.group = "waitress";
	sld.location.locator = "barmen";
	sld.dialog.filename   = "Quest\LSC\Natalie_Waitress.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "tavern"; //тип нпс
	sld.greeting = "waitress";
	LAi_SetWaitressType(sld);
	LAi_RemoveLoginTime(sld);
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	SaveCurrentNpcQuestDateParam(sld, "location");
	sld.LSC_clan = true;
}

void OtherNpcInit() // остальные ключевые НПС
{
	// Диего де Ланда
	ref sld = GetCharacter(NPC_GenerateCharacter("DiegoDeLanda", "priest_sp1", "man", "man2", 100, SPAIN, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_279");
	sld.lastname = StringFromKey("QuestsUtilite_280");
	sld.dialog.filename = "Quest\ShipsPack\DiegoDeLanda_dialog.c";
	sld.dialog.currentnode = "DiegoDeLanda_Meeting";
	LAi_SetHP(sld, 999.0, 999.0);
	LAi_SetImmortal(sld, true);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
}

string GetStrSmallRegister(string sBase)
{
	string sResult, Simbol;
	sResult = "";
	int qty = strlen(sBase);
	for (int i=0; i<qty; i++)
	{
		Simbol = GetSymbol(sBase, i);
		switch (Simbol)
		{
			case "А": sResult += "а"; continue; break;
			case "Б": sResult += "б"; continue; break;
			case "В": sResult += "в"; continue; break;
			case "Г": sResult += "г"; continue; break;
			case "Д": sResult += "д"; continue; break;
			case "Е": sResult += "е"; continue; break;
			case "Ё": sResult += "ё"; continue; break;
			case "Ж": sResult += "ж"; continue; break;
			case "З": sResult += "з"; continue; break;
			case "И": sResult += "и"; continue; break;
			case "Й": sResult += "й"; continue; break;
			case "К": sResult += "к"; continue; break;
			case "Л": sResult += "л"; continue; break;
			case "М": sResult += "м"; continue; break;
			case "Н": sResult += "н"; continue; break;
			case "О": sResult += "о"; continue; break;
			case "П": sResult += "п"; continue; break;
			case "Р": sResult += "р"; continue; break;
			case "С": sResult += "с"; continue; break;
			case "Т": sResult += "т"; continue; break;
			case "У": sResult += "у"; continue; break;
			case "Ф": sResult += "ф"; continue; break;
			case "Х": sResult += "х"; continue; break;
			case "Ц": sResult += "ц"; continue; break;
			case "Ч": sResult += "ч"; continue; break;
			case "Ш": sResult += "ш"; continue; break;
			case "Щ": sResult += "щ"; continue; break;
			case "Э": sResult += "э"; continue; break;
			case "Ю": sResult += "ю"; continue; break;
			case "Я": sResult += "я"; continue; break;
			
			case "A": sResult += "a"; continue; break;
			case "B": sResult += "b"; continue; break;
			case "C": sResult += "c"; continue; break;
			case "D": sResult += "d"; continue; break;
			case "E": sResult += "e"; continue; break;
			case "F": sResult += "f"; continue; break;
			case "G": sResult += "g"; continue; break;
			case "H": sResult += "h"; continue; break;
			case "I": sResult += "i"; continue; break;
			case "J": sResult += "j"; continue; break;
			case "K": sResult += "k"; continue; break;
			case "L": sResult += "l"; continue; break;
			case "M": sResult += "m"; continue; break;
			case "N": sResult += "n"; continue; break;
			case "O": sResult += "o"; continue; break;
			case "P": sResult += "p"; continue; break;
			case "Q": sResult += "q"; continue; break;
			case "R": sResult += "r"; continue; break;
			case "S": sResult += "s"; continue; break;
			case "T": sResult += "t"; continue; break;
			case "U": sResult += "u"; continue; break;
			case "V": sResult += "v"; continue; break;
			case "W": sResult += "w"; continue; break;
			case "X": sResult += "x"; continue; break;
			case "Y": sResult += "y"; continue; break;
			case "Z": sResult += "z"; continue; break;
			
			// Немецкие символы
			case "Ä": sResult += "ä"; continue; break;
			case "Ö": sResult += "ö"; continue; break;
			case "Ü": sResult += "ü"; continue; break;
			case "ß": sResult += "ß"; continue; break;

			// Испанские символы
			case "Ñ": sResult += "ñ"; continue; break;
			case "Á": sResult += "á"; continue; break;
			case "É": sResult += "é"; continue; break;
			case "Í": sResult += "í"; continue; break;
			case "Ó": sResult += "ó"; continue; break;
			case "Ú": sResult += "ú"; continue; break;

			// Польские символы
			case "Ą": sResult += "ą"; continue; break;
			case "Ć": sResult += "ć"; continue; break;
			case "Ę": sResult += "ę"; continue; break;
			case "Ł": sResult += "ł"; continue; break;
			case "Ń": sResult += "ń"; continue; break;
			case "Ó": sResult += "ó"; continue; break;
			case "Ś": sResult += "ś"; continue; break;
			case "Ź": sResult += "ź"; continue; break;
			case "Ż": sResult += "ż"; continue; break;

			// Украинские символы
			case "Ґ": sResult += "ґ"; continue; break;
			case "Є": sResult += "є"; continue; break;
			case "І": sResult += "і"; continue; break;
			case "Ї": sResult += "ї"; continue; break;
		}
		sResult += Simbol;
	}
	return sResult;
}

// Warship 15.08.09 -->
// Перевод всей строки в верхний регистр
string ToUpper(string _text)
{
	string retString, symbol;
	retString = "";
	int length = strlen(_text);
	
	for(int i = 0; i < length; i++)
	{
		symbol = GetSymbol(_text, i);
		
		switch(symbol)
		{
			case "а": retString += "А"; continue; break;
			case "б": retString += "Б"; continue; break;
			case "в": retString += "В"; continue; break;
			case "г": retString += "Г"; continue; break;
			case "д": retString += "Д"; continue; break;
			case "е": retString += "Е"; continue; break;
			case "ё": retString += "Ё"; continue; break;
			case "ж": retString += "Ж"; continue; break;
			case "з": retString += "З"; continue; break;
			case "и": retString += "И"; continue; break;
			case "й": retString += "Й"; continue; break;
			case "к": retString += "К"; continue; break;
			case "л": retString += "Л"; continue; break;
			case "м": retString += "М"; continue; break;
			case "н": retString += "Н"; continue; break;
			case "о": retString += "О"; continue; break;
			case "п": retString += "П"; continue; break;
			case "р": retString += "Р"; continue; break;
			case "с": retString += "С"; continue; break;
			case "т": retString += "Т"; continue; break;
			case "у": retString += "У"; continue; break;
			case "ф": retString += "Ф"; continue; break;
			case "х": retString += "Х"; continue; break;
			case "ц": retString += "Ц"; continue; break;
			case "ч": retString += "Ч"; continue; break;
			case "ш": retString += "Ш"; continue; break;
			case "щ": retString += "Щ"; continue; break;
			case "э": retString += "Э"; continue; break;
			case "ю": retString += "Ю"; continue; break;
			case "я": retString += "Я"; continue; break;
			
			case "a": retString += "A"; continue; break;
			case "b": retString += "B"; continue; break;
			case "c": retString += "C"; continue; break;
			case "d": retString += "D"; continue; break;
			case "e": retString += "E"; continue; break;
			case "f": retString += "F"; continue; break;
			case "g": retString += "G"; continue; break;
			case "h": retString += "H"; continue; break;
			case "i": retString += "I"; continue; break;
			case "j": retString += "J"; continue; break;
			case "k": retString += "K"; continue; break;
			case "l": retString += "L"; continue; break;
			case "m": retString += "M"; continue; break;
			case "n": retString += "N"; continue; break;
			case "o": retString += "O"; continue; break;
			case "p": retString += "P"; continue; break;
			case "q": retString += "Q"; continue; break;
			case "r": retString += "R"; continue; break;
			case "s": retString += "S"; continue; break;
			case "t": retString += "T"; continue; break;
			case "u": retString += "U"; continue; break;
			case "v": retString += "V"; continue; break;
			case "w": retString += "W"; continue; break;
			case "x": retString += "X"; continue; break;
			case "y": retString += "Y"; continue; break;
			case "z": retString += "Z"; continue; break;

			// Немецкие символы
			case "ä": retString += "Ä"; continue; break;
			case "ö": retString += "Ö"; continue; break;
			case "ü": retString += "Ü"; continue; break;
			case "ß": retString += "ß"; continue; break;

			// Испанские символы
			case "ñ": retString += "Ñ"; continue; break;
			case "á": retString += "Á"; continue; break;
			case "é": retString += "É"; continue; break;
			case "í": retString += "Í"; continue; break;
			case "ó": retString += "Ó"; continue; break;
			case "ú": retString += "Ú"; continue; break;

			// Польские символы
			case "ą": retString += "Ą"; continue; break;
			case "ć": retString += "Ć"; continue; break;
			case "ę": retString += "Ę"; continue; break;
			case "ł": retString += "Ł"; continue; break;
			case "ń": retString += "Ń"; continue; break;
			case "ś": retString += "Ś"; continue; break;
			case "ź": retString += "Ź"; continue; break;
			case "ż": retString += "Ż"; continue; break;
			
			// Украинские символы
			case "ґ": retString += "Ґ"; continue; break;
			case "є": retString += "Є"; continue; break;
			case "і": retString += "І"; continue; break;
			case "ї": retString += "Ї"; continue; break;
		}
		
		retString += symbol;
	}
	
	return retString;
}

// Первый символ в верхний регистр
string UpperFirst(string _text)
{
	String firstSymbol = GetSymbol(_text, 0);
	firstSymbol = ToUpper(firstSymbol);
	
	return firstSymbol + strcut(_text, 1, strlen(_text) - 1);
}

// Первый символ в нижний регистр
string LowerFirst(string _text)
{
	string firstSymbol = GetSymbol(_text, 0);
	firstSymbol = GetStrSmallRegister(firstSymbol);
	
	return firstSymbol + strcut(_text, 1, strlen(_text) - 1);
}
// <--


//домашние энкаунтеры. установка тамера 'покинуть дом'
void HouseEnc_TimerGoUot(string qName)
{
	if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
	{
		if (pchar.location == pchar.questTemp.HouseEncTimer && !actLoadFlag && !LAi_grp_alarmactive)
		{
			LAi_group_Attack(characterFromId(pchar.questTemp.HouseEncTimer.Id), Pchar);
		}
		DeleteAttribute(pchar, "questTemp.HouseEncTimer");
	}
}

//удаления группы с задержкой
void Delay_DeleteGroup(string GroupName)
{	
	pchar.quest.DeleteGroupOnExitLocation.GroupName = GroupName;
	DoQuestCheckDelay("DeleteGroupOnExitLocation", 2.0);
}

//Перехват всех попыток ГГ залезть в боксы
void QuestCheckTakeBoxes(ref itemsRef) 
{	
	int iTemp;
	string title;

	// Флаг 'в сундуке'
	bMainCharacterInBox = true;

	//-------------------- КЛАДЫ ------------>>>>>>>>>>>>>
	if (CheckAttribute(itemsRef, "Treasure"))
	{
		Log_Info(StringFromKey("QuestsUtilite_156"));
		PlaySound("interface\notebook.wav");
        iTemp = sti(itemsRef.Treasure); // Тир клада
        AddCharacterExpToSkill(PChar, "Fortune", iTemp*3);
        // Ачивки
        if(!GetAchievement("ach_CL_151") && iTemp == 15) Achievment_Set("ach_CL_151");
		Statistic_AddValue(Pchar, "Treasure", 1);
		Achievment_SetStat(8, 1);
		if(SandBoxMode) Achievment_SetStat(101, 1);
        DeleteAttribute(itemsRef, "Treasure");
		//eddy. для бесконфликтности квестов
		locations[FindLocation(pchar.location)].DisableEncounters = false; //энкаутеры открыть
		if(CheckAttribute(itemsRef, "PiratesOnUninhabitedTreasure"))
		{
			title = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			
			if(CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.UseMainPiratename"))
			{
				AddQuestRecordEx(title, "PiratesOnUninhabited", "10");
				AddQuestUserData(title, "sSex", GetSexPhrase(StringFromKey("QuestsUtilite_157"),StringFromKey("QuestsUtilite_158")));
			}
			else
			{
				AddQuestRecordEx(title, "PiratesOnUninhabited", "9");
				AddQuestUserData(title, "sSex", GetSexPhrase(StringFromKey("QuestsUtilite_159"),StringFromKey("QuestsUtilite_160")));
				AddQuestUserData(title, "shore", XI_ConvertString(PChar.location + "Gen")); // belamour gen
			}
			
			CloseQuestHeader(title);
			
			PChar.Quest.PiratesOnUninhabited_ShoreTreasureLose.over = "yes";
			
			DeleteAttribute(itemsRef, "PiratesOnUninhabitedTreasure");
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
		}
		else
		{
			if (CheckAttribute(itemsRef, "ReasonToFastTreasure")) // mitrokosta фикс двойных ОЗК
			{
				DeleteAttribute(itemsRef, "ReasonToFastTreasure");
			}
			else
			{
				// ОЗК (Выход из пещеры)
				switch (sti(pchar.GenQuest.Treasure.Vario))
				{
					case 2:  
						pchar.quest.Treasure_evilcaptain.win_condition.l1 = "ExitFromLocation";
						pchar.quest.Treasure_evilcaptain.win_condition.l1.location = pchar.location;
						pchar.quest.Treasure_evilcaptain.function = "Treasure_SetCaptainWarrior";
					break;
					
					case 3:
						pchar.quest.Treasure_evilsoldier.win_condition.l1 = "ExitFromLocation";
						pchar.quest.Treasure_evilsoldier.win_condition.l1.location = pchar.location;
						pchar.quest.Treasure_evilsoldier.function = "Treasure_SetOfficerWarrior";
					break;
				}
			}
		}
		
		if(CheckAttribute(itemsRef, "Hold_GenQuest_Treasure"))
		{
			if(sti(pchar.GenQuest.Hold_GenQuest.Treasure) == 0)
			{
				AddQuestRecord("HoldQuest", "18");
				AddQuestUserData("HoldQuest", "sCapName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour gen
			}
			else
			{
				AddQuestRecord("HoldQuest", "17");
				AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name); // belamour gen
			}
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(itemsRef, "Hold_GenQuest_Treasure");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");
		}
	}
    if (CheckAttribute(itemsRef, "treasure_note")) // Проверка записок
    {
        if(GetCharacterItem(itemsRef, "treasure_note") > 0)
        {
            // Пока открыт этот сундук, запоминаем всю инфу для взятия записки
            ref rNote = &items[FindItem("treasure_note")];
            rNote.curNumb = itemsRef.treasure_note;
            rNote.curLoc  = PChar.location;
            rNote.curBox  = GetAttributeName(itemsRef);
        }
        else
            DeleteAttribute(itemsRef, "treasure_note");
    }
	//<<<<<<<<<<---------- КЛАДЫ --------------------------
}

//открытие дверей в локации города для коммонов. только на текущие сутки + ещё одни, потом снимается само.
void SetOpenDoorCommonLoc(string City, string locationId)
{
	aref arRld, arDis, arRld2, arDis2;
	string LocId;
	makearef(arRld, locations[FindLocation(City + "_town")].reload);
    int Qty2, n, i;
	int Qty = GetAttributesNum(arRld);
	for (i=0; i<Qty; i++)
    {
    	arDis = GetAttributeN(arRld, i);
		LocId = arDis.go;
    	if (LocId == locationId)
    	{
			arDis.disable = false;
			arDis.canEnter = true;
			return;
    	}
		if (arDis.label != "Sea")
		{	
			makearef(arRld2, Locations[FindLocation(LocId)].reload);
			Qty2 = GetAttributesNum(arRld2);
			for (n=0; n<Qty2; n++)
			{
    			arDis2 = GetAttributeN(arRld2, n);
				LocId = arDis2.go;
				if (arDis2.name != "reload1" && LocId == locationId) // mitrokosta вот где собака зарыта! reload1 не смотреть!
    			{
					arDis.disable = false;
					arDis.canEnter = true;
					arDis2.disable = false; // на всякий случай
					return;					
				}
			}
		}
    }
}

//для борьбы со взломом через ArtMoney
int CheckItemsCRC(ref rChar)
{
	aref arItems;
	string sName;
	ref rItm;
	int BaseCRC = 0;
	int Qty, ItmQty;
	
	makearef(arItems, rChar.items);
	Qty = GetAttributesNum(arItems);
	for (int a = 0; a < Qty; a++)
	{
		sName = GetAttributeName(GetAttributeN(arItems, a));		
		rItm = ItemsFromID(sName);
		if(rItm.id != "Gold")
		{
			ItmQty = sti(arItems.(sName));
			if(!CheckAttribute(rChar,"BaseCRC")) 
			{
				rChar.BaseCRC = 1 + rand(5);		
			}	
			BaseCRC += (sti(rItm.index) + sti(rChar.BaseCRC)) * ItmQty);	
		}			
	}
	return BaseCRC;
}

int AddItemToCRC(ref rChar, string itemName, int n)
{
	int BaseCRC = 0;	
	ref rItm = ItemsFromID(itemName);
	if(rItm.id != "Gold")
	{
		if(!CheckAttribute(rChar,"BaseCRC")) 
		{
			rChar.BaseCRC = 1 + rand(5);		
		}
		BaseCRC = (sti(rItm.index) + sti(rChar.BaseCRC)) * n);
	}		
	return BaseCRC;
}

///Jason ---------блок помещения ГГ в тюрьму, пребывания в ней, штрафа и выхода из тюрьмы----------------------
void GoToPrison(string _sCity, int _iStraff, int _iDay)//поместить ГГ в тюрьму, забрать все предметы и положить в сундук, оштрафовать
{
	DoFunctionReloadToLocation(_sCity+"_prison", "goto", "goto9", "");
	//Время отсидки прокрутим ДО изъятия предметов - иначе при смене локи сундук и НПС вычистятся
	WaitDate("", 0, 0, _iDay, 0, 10); //крутим время
	RecalculateJumpTable();

	ref location = &Locations[FindLocation(_sCity+"_prison")];
	
	aref arItems, boxItems;
	ref rItem, sld;
	string sName;
	makearef(arItems, PChar.items);
	makearef(boxItems, location.box1.items);
	int iItemsNum = GetAttributesNum(arItems);
	for(int i=0; i<iItemsNum; i++)
	{
		sName = GetAttributeName(GetAttributeN(arItems, i));
		rItem = ItemsFromID(sName);
		if (rItem.ItemType != "QUESTITEMS")
		{
			boxItems.(sName) = PChar.items.(sName);
		}
	}
	DeleteAttribute(location, "box1.QuestClosed");
	location.box1.money = sti(PChar.money)-_iStraff;	
	location.box1 = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
	RemoveAllCharacterItems(PChar, true);
	
	pchar.questTemp.Jaillocation = _sCity+"_prison";
	pchar.questTemp.JailTemp1 = _iStraff;
	pchar.questTemp.JailTemp2 = _iDay;
	
	sld = characterFromId(_sCity+"_trader");
	int iNation = sld.nation;
	sld = GetCharacter(NPC_GenerateCharacter("Jail_officer", "off_" + NationShortName(iNation) + "_" + (rand(1) + 1), "man", "man", 20, iNation, -1, true, "soldier"));
	SetFantomParamFromRank(sld, 20, true); 
	sld.name = StringFromKey("QuestsUtilite_161");
    sld.lastname = StringFromKey("QuestsUtilite_162");
	sld.Dialog.Filename = "Quest\Jail_dialog.c"; 
	sld.dialog.currentnode = "Jail_officer_take"; 
	sld.greeting = "soldier_arest";
	LAi_SetActorTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, _sCity+"_prison", "goto", "goto13");
	DoQuestFunctionDelay("Hide_Interface", 0.8);
	DoQuestFunctionDelay("Jail_officer", 10.0);
}

void Hide_Interface(string qName)//скроем нашу махинацию с датами
{
	ChangeShowIntarface();
}

void Jail_officer(string qName)
{
    sld = characterFromID("Jail_officer");
    LAi_SetActorTypeNoGroup(sld);
    LAi_ActorGoToLocator(sld, "goto", "goto23", "", -1);
	DoQuestFunctionDelay("Jail_officer_talk", 3.0);
}

void Jail_officer_talk(string qName)
{
    sld = characterFromID("Jail_officer");
    LAi_SetActorTypeNoGroup(sld);
    LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void InPrison(string qName)//отсидка
{
	SetLaunchFrameFormParam(StringFromKey("QuestsUtilite_163"), "", 0, 6);
	LaunchFrameForm();
	sld = characterFromId("Jail_officer");
    LAi_SetActorTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto13");
	DoQuestFunctionDelay("Jail_officer", 10.0);
}

void GoFromPrison(string qName)//выход из тюрьмы
{
	pchar.questTemp.jailCanMove = true; //разрешить пройти мимо стражи
	DoQuestReloadToLocation(pchar.location, "goto", "goto23", "");
	DeleteAttribute(pchar, "questTemp.JailTemp1");
	DeleteAttribute(pchar, "questTemp.JailTemp2");
	SetFunctionTimerCondition("LockPrisonBox", 0, 0, 1, false);
}

void LockPrisonBox(string qName)// закрыть сундук
{
	ref location = &Locations[FindLocation(pchar.questTemp.Jaillocation)];
	location.box1.QuestClosed = true;
	DeleteAttribute(pchar, "questTemp.Jaillocation");
}
//<-- блок помещения ГГ в тюрьму

string DesIsland()//Jason выбор рандомной необитайки - вынес сюда
{
	string sIsland;
	switch (rand(2))
	{
		case 0:
			sIsland = "Terks";
			break;
		case 1:
			sIsland = "Caiman";
			break;
		case 2:
			sIsland = "Dominica";
			break;
	}
	return sIsland;
}

string FindFriendCityToMC(bool bRand) //Jason выбрать радномный дружественный к ГГ город - вынес сюда
{
	int n;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;
	int nation = GetBaseHeroNation(); // mitrokosta фикс зависимости от флага
	if (nation == PIRATE) {
		nation = ENGLAND;
	}
	int curIsland = GetCharacterCurrentIsland(pchar);

	for(n=0; n<MAX_COLONIES; n++)
	{
		bool notSameIsland = (curIsland < 0) || (Islands[curIsland].id != colonies[n].island);
		if (notSameIsland && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].id != "IslaMona" && colonies[n].nation != "none" && colonies[n].nation != PIRATE && GetNationRelation(nation, sti(colonies[n].nation)) != RELATION_ENEMY) // mitrokosta фикс зависимости от флага
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	if (bRand) nation = storeArray[Rand(howStore-1)];
	else nation = storeArray[hrand(howStore-1)]; // По умолчанию функция в диалоге, тэг пока не нужен
	return colonies[nation].id;
}

string FindEnemyCityToMC(bool bRand) //Jason выбрать радномный враждебный к ГГ город - вынес сюда
{
	int n;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;
	int nation = GetBaseHeroNation(); // mitrokosta фикс зависимости от флага
	if (nation == PIRATE) {
		nation = ENGLAND;
	}
	int curIsland = GetCharacterCurrentIsland(pchar);

	for(n=0; n<MAX_COLONIES; n++)
	{
		bool notSameIsland = (curIsland < 0) || (Islands[curIsland].id != colonies[n].island);
		if (notSameIsland && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].id != "IslaMona" && colonies[n].nation != "none" && colonies[n].nation != PIRATE && GetNationRelation(nation, sti(colonies[n].nation)) == RELATION_ENEMY) // mitrokosta фикс зависимости от флага
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	if (bRand) nation = storeArray[Rand(howStore-1)];
	else nation = storeArray[hrand(howStore-1)]; // По умолчанию функция в диалоге, тэг пока не нужен
	return colonies[nation].id;
}

// belamour legendary edition -->

/* метод находит случайный город для выполнения квеста по следующим параметрам
ref ch - относительно какого персонажа будем выбирать колонию
string relation - враждебность города к ch
enemy - только враждебные колонии
friend - включает нейтральные и дружественные
friend_only - только дружественные колонии
neutral - только нейтральные колонии
all," " или другое значение - любая колония независимо от отношений
int _Nation - выборка среди определённой нации, ставить -1, если такая не нужна
bool pirate - true - включая пиратские колонии, false - исключая пиратские колонии
bool bRand - вид рандома true - обычный rand(), false - hrand()
*/
string FindQuestCity(ref ch, string relation, int _nation, bool bpirate, bool bRand)
{
	int n;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;
	int nation = sti(ch.nation); 
	bool nationSort = true;
	if(nation < 0 || nation > 4) nation = PIRATE;
	if(_nation < 0 || _nation > 4)  
	{
		nationSort = false;
		if(bRand) _nation = rand(4);
		else _nation = hrand(4); // По умолчанию в диалоге, тэг пока не нужен
	}
	int curIsland = GetCharacterCurrentIsland(pchar);

	for(n=0; n<MAX_COLONIES; n++)
	{
		bool notSameIsland = (curIsland < 0) || (Islands[curIsland].id != colonies[n].island);
		if(notSameIsland && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].id != "IslaMona" && colonies[n].nation != "none")
		{
			if(!bpirate && colonies[n].nation == PIRATE) continue;
			if(relation == "enemy" && GetNationRelation(nation, sti(colonies[n].nation)) != RELATION_ENEMY) continue;
			if(relation == "friend" &&  GetNationRelation(nation, sti(colonies[n].nation)) == RELATION_ENEMY) continue;
			if(relation == "friend_only" &&  GetNationRelation(nation, sti(colonies[n].nation)) != RELATION_FRIEND) continue;
			if(relation == "neutral" &&  GetNationRelation(nation, sti(colonies[n].nation)) != RELATION_NEUTRAL) continue;
			if(nationSort && sti(colonies[n].nation) != _nation) continue;
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	if (bRand) nation = storeArray[Rand(howStore-1)];
	else nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}
// <-- legendary edition

void SelectLevelWarShipParameter()//Jason автолевеллинг на военные корабли противника
{
	int iShipRank;
	if(sti(pchar.rank) >= 30) iShipRank = 4;
	if(sti(pchar.rank) >= 21 && sti(pchar.rank) < 30) iShipRank = 3;
	if(sti(pchar.rank) >= 12 && sti(pchar.rank) < 21) iShipRank = 2;
	if(sti(pchar.rank) >= 6 && sti(pchar.rank) < 12) iShipRank = 1;
	if(sti(pchar.rank) < 6) iShipRank = 0;
	
	int iClassFlag = FLAG_SHIP_CLASS_6;
	switch (iShipRank)
	{
		case 0:  
			iClassFlag = FLAG_SHIP_CLASS_6;					
			iTotalTemp = CANNON_TYPE_CANNON_LBS6;
			sTotalTemp = "blade_12";
		break; 
		case 1:  
			iClassFlag = FLAG_SHIP_CLASS_5;					
			iTotalTemp = CANNON_TYPE_CANNON_LBS12;
			sTotalTemp = "blade_14";
		break; 	
		case 2:  
			iClassFlag = FLAG_SHIP_CLASS_4;				
			iTotalTemp = CANNON_TYPE_CANNON_LBS16;
			sTotalTemp = "blade_13";
		break; 		
		case 3:  
			iClassFlag = FLAG_SHIP_CLASS_4 + FLAG_SHIP_CLASS_3;	
			iTotalTemp = CANNON_TYPE_CANNON_LBS16;
			sTotalTemp = "blade_15";
		break; 
		case 4: 
			iClassFlag = FLAG_SHIP_CLASS_2;		
			iTotalTemp = CANNON_TYPE_CULVERINE_LBS18;
			sTotalTemp = "blade_19";
		break;			
	}
	
	iGlobalTemp = GetRandomShipType(iClassFlag, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY);
}

void SelectLevelTradeShipParameter()//Jason автолевеллинг на торговые корабли противника
{
	int iShipRank;
	if(sti(pchar.rank) >= 26) iShipRank = 4;
	if(sti(pchar.rank) >= 17 && sti(pchar.rank) < 26) iShipRank = 3;	
	if(sti(pchar.rank) >= 10 && sti(pchar.rank) < 17) iShipRank = 2;
	if(sti(pchar.rank) >= 5 && sti(pchar.rank) < 10) iShipRank = 1;	
	if(sti(pchar.rank) < 5) iShipRank = 0;
	switch (iShipRank)
	{
		case 0:  
			iGlobalTemp = GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY);
			iTotalTemp = CANNON_TYPE_CANNON_LBS3;
			sTotalTemp = "blade_03";
		break; 	
		case 1:  
			iGlobalTemp = GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY);
			iTotalTemp = CANNON_TYPE_CANNON_LBS6;
			sTotalTemp = "blade_05";
		break; 		
		case 2:  
			iGlobalTemp = GetRandomShipType(FLAG_SHIP_CLASS_4 + FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY);
			iTotalTemp = CANNON_TYPE_CANNON_LBS6;
			sTotalTemp = "blade_07";
		break; 
		case 3: 
			iGlobalTemp = GetRandomShipType(FLAG_SHIP_CLASS_3 + FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY);
			iTotalTemp = CANNON_TYPE_CANNON_LBS8;
			sTotalTemp = "blade_10";
		break; 
		case 4: 
			iGlobalTemp = GetRandomShipType(FLAG_SHIP_CLASS_2 + FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY);
			iTotalTemp = CANNON_TYPE_CANNON_LBS16;
			sTotalTemp = "blade_06";
		break; 		
	}
}

// TO_DO: DEL/REF
// Jason автолевеллинг на орудия - иногда надо
int SelectLevelCannonParameter(int iShipType)
{
	int iCannon = GetCannonByTypeAndCaliber(RandPhraseSimple("cannon","culverine"), sti(ShipsTypes[iShipType].MaxCaliber));
	return iCannon;
}

//Jason --> сделаю функции добавления боевых морских и личных скиллов комплексом - много где надо дать сразу по 4-6, а стопки экспы в функциях мешают
//морские навыки, нужны для экспы после морских боев
void AddComplexSeaExpToScill(int s, int a, int c, int g, int d, int r, int t)
{
	AddCharacterExpToSkill(pchar, "Sailing", s);//навигация
	AddCharacterExpToSkill(pchar, "Accuracy", a);//меткость
	AddCharacterExpToSkill(pchar, "Cannons", c);//орудия
	AddCharacterExpToSkill(pchar, "Grappling", g);//абордаж
	AddCharacterExpToSkill(pchar, "Defence", d);//защита
	AddCharacterExpToSkill(pchar, "Repair", r);//починка
	AddCharacterExpToSkill(pchar, "Commerce", t);//торговля
}

//личные боевые навыки, нужны для экспы после сухопутных боев
void AddComplexSelfExpToScill(int l, int m, int h, int p)
{
	AddCharacterExpToSkill(pchar, "FencingL", l);//лёгкое оружие
	AddCharacterExpToSkill(pchar, "FencingS", m);//среднее оружие
	AddCharacterExpToSkill(pchar, "FencingH", h);//тяжелое оружие
	AddCharacterExpToSkill(pchar, "Pistol", p); //пистоли
}

// Sinistra - личные мирные навыки
void AddComplexLandExpToScill(int o, int f, int n)
{
	AddCharacterExpToSkill(pchar, "Leadership", o);//харизма
	AddCharacterExpToSkill(pchar, "Fortune", f);//везение
	AddCharacterExpToSkill(pchar, "Sneak", n);//скрытность
}

int CheckShipTypeInSquadron(int iShipType) //Jason, есть ли такой тип корабля в эскадре и сколько
{
	ref sld;
	int iTemp;
	int iShip = 0;
	for(int i = 0; i < COMPANION_MAX; i++)
	{
		iTemp = GetCompanionIndex(PChar, i);
		if(iTemp > 0)
		{
			sld = GetCharacter(iTemp);
			if(sti(RealShips[sti(sld.ship.type)].basetype) == iShipType) iShip++;
		}
	}
	return iShip;
}

bool LSC_CheckShips() // проверка, можно ли подойти к острову LSC // Addon-2016 Jason
{
	ref sld;
	int iTemp;
	if(4-sti(RealShips[sti(pchar.Ship.Type)].Class) > 0 || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_FLEUT) return false;
	for(int i = 0; i < COMPANION_MAX; i++)
	{
		iTemp = GetCompanionIndex(PChar, i);
		if(iTemp > 0)
		{
			sld = GetCharacter(iTemp);
			if(4-sti(RealShips[sti(sld.Ship.Type)].Class) > 0 || sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_FLEUT) return false;
		}
	}
	return true;
}

void SetPassengerParameter(string _sIndex, bool bEnemy) //Jason, общие параметры пассажиров
{
	if(CheckAttribute(pchar, "questTemp.StatusCity"))
	{
		SetPassengerParameterToStatusCity(_sIndex);
		return;
	}
	if (bEnemy)
	{
		pchar.GenQuest.(_sIndex).City = FindEnemyCityToMC(true);
		pchar.GenQuest.(_sIndex).Enemycity = true;
	}
	else pchar.GenQuest.(_sIndex).City = FindFriendCityToMC(true); //целевой город
	pchar.GenQuest.(_sIndex).StartCity = GetCurrentTown(); //стартовый город
	int DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.(_sIndex).City), GetArealByCityName(pchar.GenQuest.(_sIndex).StartCity));
	if (DaysQty > 16) DaysQty = 16;
	if (DaysQty < 1) DaysQty = 10; // оставлю на всяк пожарный пока
	pchar.GenQuest.(_sIndex).DaysQty = makeint(sti(DaysQty)*(frand(1.5)+1.0)); //дни
	float fShipIdx;
	switch(7-sti(RealShips[sti(Pchar.Ship.Type)].Class))
	{
		case 0: fShipIdx = 1.0; break;
		case 1: fShipIdx = 1.2;	break;
		case 2: fShipIdx = 1.5; break;
		case 3: fShipIdx = 2.2; break;
		case 4: fShipIdx = 3.0; break;
		case 5:	fShipIdx = 4.5; break;
		case 6:	fShipIdx = 5.0; break;
	}
	pchar.GenQuest.(_sIndex).Money = (sti(DaysQty)*500*stf(fShipIdx)+rand(100))*sti(DaysQty)/sti(pchar.GenQuest.(_sIndex).DaysQty);
	if (bEnemy) pchar.GenQuest.(_sIndex).Money = makeint(sti(pchar.GenQuest.(_sIndex).Money) / 50); //оплата в дублонах
}

void SetPassengerParameterToStatusCity(string _sIndex)
{
	pchar.GenQuest.(_sIndex).City = FindFriendCityToMC(true); //целевой город
	pchar.GenQuest.(_sIndex).StartCity = GetCurrentTown(); //стартовый город
	int attempt = 0;
	while (GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.(_sIndex).City), GetArealByCityName(pchar.GenQuest.(_sIndex).StartCity)) > 7 && attempt < 10)
	{		
		pchar.GenQuest.(_sIndex).City = FindFriendCityToMC(true); //целевой город
		attempt++;
	}
	int DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.(_sIndex).City), GetArealByCityName(pchar.GenQuest.(_sIndex).StartCity));
	if (DaysQty > 16) DaysQty = 16;
	if (DaysQty < 1) DaysQty = 10; // оставлю на всяк пожарный пока
	pchar.GenQuest.(_sIndex).DaysQty = makeint(sti(DaysQty)*(frand(1.5)+1.0)); //дни
	float fShipIdx;
	switch(7-sti(RealShips[sti(Pchar.Ship.Type)].Class))
	{
		case 0: fShipIdx = 1.0; break;
		case 1: fShipIdx = 1.2;	break;
		case 2: fShipIdx = 1.5; break;
		case 3: fShipIdx = 2.2; break;
		case 4: fShipIdx = 3.0; break;
		case 5:	fShipIdx = 4.5; break;
		case 6:	fShipIdx = 5.0; break;
	}
	pchar.GenQuest.(_sIndex).Money = (sti(DaysQty)*500*stf(fShipIdx)+rand(100))*sti(DaysQty)/sti(pchar.GenQuest.(_sIndex).DaysQty);
}

string UpdateLSCClanParol() // Jason: обновление паролей кланов
{
	string sParol;
	switch (rand(29))
	{
		case 0: sParol = StringFromKey("QuestsUtilite_164"); break;
		case 1: sParol = StringFromKey("QuestsUtilite_165"); break;
		case 2: sParol = StringFromKey("QuestsUtilite_166"); break;
		case 3: sParol = StringFromKey("QuestsUtilite_167"); break;
		case 4: sParol = StringFromKey("QuestsUtilite_168"); break;
		case 5: sParol = StringFromKey("QuestsUtilite_169"); break;
		case 6: sParol = StringFromKey("QuestsUtilite_170"); break;
		case 7: sParol = StringFromKey("QuestsUtilite_171"); break;
		case 8: sParol = StringFromKey("QuestsUtilite_172"); break;
		case 9: sParol = StringFromKey("QuestsUtilite_173"); break;
		case 10: sParol = StringFromKey("QuestsUtilite_174"); break;
		case 11: sParol = StringFromKey("QuestsUtilite_175"); break;
		case 12: sParol = StringFromKey("QuestsUtilite_176"); break;
		case 13: sParol = StringFromKey("QuestsUtilite_177"); break;
		case 14: sParol = StringFromKey("QuestsUtilite_178"); break;
		case 15: sParol = StringFromKey("QuestsUtilite_179"); break;
		case 16: sParol = StringFromKey("QuestsUtilite_180"); break;
		case 17: sParol = StringFromKey("QuestsUtilite_181"); break;
		case 18: sParol = StringFromKey("QuestsUtilite_182"); break;
		case 19: sParol = StringFromKey("QuestsUtilite_183"); break;
		case 20: sParol = StringFromKey("QuestsUtilite_184"); break;
		case 21: sParol = StringFromKey("QuestsUtilite_185"); break;
		case 22: sParol = StringFromKey("QuestsUtilite_186"); break;
		case 23: sParol = StringFromKey("QuestsUtilite_187"); break;
		case 24: sParol = StringFromKey("QuestsUtilite_188"); break;
		case 25: sParol = StringFromKey("QuestsUtilite_189"); break;
		case 26: sParol = StringFromKey("QuestsUtilite_190"); break;
		case 27: sParol = StringFromKey("QuestsUtilite_191"); break;
		case 28: sParol = StringFromKey("QuestsUtilite_192"); break;
		case 29: sParol = StringFromKey("QuestsUtilite_193"); break;
	}
	return sParol;
}

void UltimatePotionEffect() // зелье команчей
{
	RemoveItems(pchar, "Ultimate_potion", 1);
	notification(StringFromKey("QuestsUtilite_194"), "None");
	LAi_SetCurHPMax(PChar);
	AddCharacterHealth(pchar, 50);
	DeleteAttribute(pchar, "chr_ai.poison");
	notification(StringFromKey("QuestsUtilite_195"), "None");
	//Log_Info("Использовано зелье команчей");
	//Log_Info("Вы чувствуете себя полностью излеченным!");
	//PlaySound("Ambient\Tavern\glotok_001.wav");
	PlaySound("Ambient\Horror\Fear_breath_01.wav");
}

// ugeen --> 
//--> расчёт аренды склада
int GetStoragePriceExt(ref NPChar, ref chref)
{
/*  --> оставим для хардкорного патча если он будет, не вытирать!!!! 
	float fLeadership = 1.5 - GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/120.0; // учитываем авторитет
	float fCommerce = 1.5 - GetSummonSkillFromName(pchar, SKILL_COMMERCE)/120.0; // учитываем торговлю
	
	int price = makeint(15000 * MOD_SKILL_ENEMY_RATE * fLeadership * fCommerce * 0.5);
*/
	int price = makeint( 10000 * (5 + MOD_SKILL_ENEMY_RATE) * (3 + GetNationRelation2MainCharacter(sti(NPChar.nation)))/360.0 );
	
	return price;
}
//<-- расчёт аренды склада
// --> перемещаем остатки груза со склада на корабль ГГ с перегрузом, пусть сам разбирается что делать со всем этим барахлом
void SetStorageGoodsToShip(ref pStorage)
{
	int iStoreQ;
	for (int i = 0; i< GetArraySize(&Goods); i++)
	{
		iStoreQ = GetStorageGoodsQuantity(pStorage, i); 
		if (iStoreQ == 0) continue;
		SetCharacterGoods(pchar, i, GetCargoGoods(pchar, i) + iStoreQ);// перегруз
	}
}
// зануляем оставленные в ПУ корабли
void SetNull2ShipInStockMan(string _city)
{
	int i;
	ref chref, sld;
	int iTest = FindColony(_city);
	if(iTest == -1) return;
	
	ref rColony = GetColonyByIndex(iTest);
	
	for (i=1; i<MAX_CHARACTERS; i++)
	{
		makeref(chref, Characters[i]);
		if (CheckAttribute(chref, "ShipInStockMan"))
    	{
            if(chref.ShipInStockMan == (rColony.id + "_PortMan"))
		    {
				sld = CharacterFromId(rColony.id + "_PortMan");  
				DeleteAttribute(chref, "ShipInStockMan");
				chref.lifeDay = 0;
				pchar.ShipInStock = sti(pchar.ShipInStock) - 1; 
				sld.Portman    = sti(sld.Portman) - 1; 
			}
		}	
	}	
}
// <-- ugeen

bool Saga_CheckMarlinShip() // проверка полакра марлин - одинаковый юз в 2 местах
{
	if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_POLACRE || GetCompanionQuantity(pchar) > 1) return false;
	if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Marlin") && pchar.ship.name != StringFromKey("QuestsUtilite_196")) return false;
	if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Marlin") && pchar.ship.name != StringFromKey("QuestsUtilite_196")) return false;
	return true;
}

bool bPincers() // можно ли добывать клешни крабов
{
	ref chr = characterFromId("Carpentero");
	if (CheckAttribute(chr, "quest.crab")) return true;
	return false;
}

// устанавливаем сторожевики на Тортугу, сеттим каждый день 2015
void Tortuga_SetShipGuard()
{
	if (CheckAttribute(pchar, "questTemp.Sharlie.DelTerGuard")) return;
	if (pchar.location == "Tortuga" && bSeaActive) return;
	int iShipType;
	int iCannonType;
	int i;
	Group_FindOrCreateGroup("Tortuga_Guard");
	for (i=1; i<=3; i++)
	{       
		switch (i)
		{
			case 1: 
				iShipType = SHIP_LINESHIP;
				iCannonType = CANNON_TYPE_CANNON_LBS32;
			break;
			case 2: 
				iShipType = SHIP_FRIGATE_H;
				iCannonType = CANNON_TYPE_CANNON_LBS32;
			break;
			case 3: 
				iShipType = SHIP_FRIGATE;
				iCannonType = CANNON_TYPE_CANNON_LBS24;
			break;
		}
		sld = GetCharacter(NPC_GenerateCharacter("TortugaGuardCap_"+i, "citiz_"+(rand(9)+51), "man", "man", 45, FRANCE, -1, true, "soldier"));	
		FantomMakeCoolFighter(sld, 45, 110, 100, "blade_19", "pistol5", "bullet", 200);
		FantomMakeCoolSailor(sld, iShipType, "", iCannonType, 110, 110, 110);
		SetAllPerksToChar(sld, false);
		sld.Ship.Mode = "mercenary";
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.DontHitInStorm = true; // не ломается в шторм
		sld.SinkTenPercent = false;
		sld.Abordage.Enable = false; // запрет абордажа
		sld.AlwaysSandbankManeuver = true;
		sld.MultiFighter = 2.5; // мультифайтер
		sld.ship.Crew.Morale = 100;
		sld.Ship.Crew.Exp.Sailors = 100;
		sld.Ship.Crew.Exp.Cannoners = 100;
		sld.Ship.Crew.Exp.Soldiers = 100;
		Group_AddCharacter("Tortuga_Guard", "TortugaGuardCap_"+i);
	}
	Group_SetGroupCommander("Tortuga_Guard", "TortugaGuardCap_1");
	Group_SetTaskNone("Tortuga_Guard");//нет задачи
	Group_SetAddress("Tortuga_Guard", "Tortuga", "IslandShips1", "ship_1");
	Group_LockTask("Tortuga_Guard");
}

void Tortuga_DeleteShipGuard()
{
	if (pchar.location == "Tortuga" && bSeaActive) return;
	Group_DeleteGroup("Tortuga_Guard");
	for (int i=1; i<=3; i++)
	{  
		if (GetCharacterIndex("TortugaGuardCap_"+i) != -1)
		{
			sld = characterFromId("TortugaGuardCap_"+i);
			sld.lifeday = 0;
		}
	}
}

void Tortuga_ShipGuardAttack() // 2015
{
	int i;
	for (i=1; i<=3; i++)
	{       
		sld = characterFromId("TortugaGuardCap_"+i);
		sld.AlwaysEnemy = true;
		Ship_SetTaskAttack(SECONDARY_TASK, sti(sld.index), sti(pchar.index));
		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	}
	RefreshBattleInterface();
	UpdateRelations();
	DoQuestFunctionDelay("Tortuga_BranderGo", 4.0);
}

void Tortuga_BranderGo(string qName) // 2015
{
	Group_FindOrCreateGroup("Tortuga_GuardAdd");
	int iShipType, iCannonType;
	for (int i=1; i<=4; i++)
	{       
		switch (i)
		{
			case 1: 
				iShipType = SHIP_LINESHIP;
				iCannonType = CANNON_TYPE_CANNON_LBS32;
			break;
			case 2: 
				iShipType = SHIP_FRIGATE_H;
				iCannonType = CANNON_TYPE_CANNON_LBS24;
			break;
			case 3: 
				iShipType = SHIP_FRIGATE;
				iCannonType = CANNON_TYPE_CANNON_LBS24;
			break;
			case 4: 
				iShipType = SHIP_CORVETTE;
				iCannonType = CANNON_TYPE_CULVERINE_LBS18;
			break;
		}
		sld = GetCharacter(NPC_GenerateCharacter("TortugaGuardCapAdd_"+i, "citiz_"+(rand(9)+51), "man", "man", 45, FRANCE, 1, true, "soldier"));	
		FantomMakeCoolFighter(sld, 45, 110, 100, "blade_19", "pistol5", "bullet", 200);
		FantomMakeCoolSailor(sld, iShipType, "", iCannonType, 110, 110, 110);
		SetAllPerksToChar(sld, false);
		sld.Ship.Mode = "mercenary";
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.DontHitInStorm = true; // не ломается в шторм
		sld.SinkTenPercent = false;
		sld.Abordage.Enable = false; // запрет абордажа
		sld.AlwaysSandbankManeuver = true;
		sld.AlwaysEnemy = true;
		sld.MultiFighter = 2.5; // мультифайтер
		sld.ship.Crew.Morale = 100;
		sld.Ship.Crew.Exp.Sailors = 100;
		sld.Ship.Crew.Exp.Cannoners = 100;
		sld.Ship.Crew.Exp.Soldiers = 100;
		Group_AddCharacter("Tortuga_GuardAdd", "TortugaGuardCapAdd_"+i);
	}
	Group_SetGroupCommander("Tortuga_GuardAdd", "TortugaGuardCapAdd_1");
	Sea_LoginGroupCurrentSea("Tortuga_GuardAdd");
	Group_SetTaskAttack("Tortuga_GuardAdd", PLAYER_GROUP);
    Group_LockTask("Tortuga_GuardAdd");
}

void Map_NationQuestHunter(int Nation)//квестовый энкаунтер-охотник
{
    ref  sld;
	int iRank = sti(PChar.rank)+MOD_SKILL_ENEMY_RATE+5;
	if (iRank > 42) iRank = 42;
    string sCapId = "FollowerQuest0";
    string sGroup = "Sea_" + sCapId + "1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	int iNation = sti(Nation);
    for (int i = 1; i <= GetCompanionQuantity(pchar)+1; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_"+NationShortName(iNation)+"_"+(rand(1)+1), "man", "man", iRank, iNation, 46, true, "hunter"));
        SetShipHunter(sld);
        SetFantomParamHunter(sld);
        SetCaptanModelByEncType(sld, "war");
        sld.AlwaysEnemy = true;
        sld.DontRansackCaptain = true;
		sld.WatchFort = true;
		sld.Coastal_Captain = true;
        sld.mapEnc.type = "war";
		sld.mapEnc.worldMapShip = "Galleon_red";
        sld.mapEnc.Name = StringFromKey("QuestsUtilite_197");
		sld.hunter = iNation;
        Group_AddCharacter(sGroup, sCapId + i);
    }
    Group_SetGroupCommander(sGroup, sCapId+ "1");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	Map_CreateCoolWarrior("", sCapId + "1", 45);
}

void FillShorechestBox(string loc, int n, int i) // Jason: заполнение выброшенных на берег сундуков
{
	pchar.GenQuestBox.(loc) = true;
	string boxx = "box"+n;

    // На if'ах оставил старую логику (TO_DO: переверить)
    // За счёт "&" для каждой конкретной loc в конкретный день используется одна и та же дробь
    string tag2 = loc + boxx;
    string tag  = "&SBoxx" + tag2;

	string sgem1 = "jewelry"+(hrand(3, tag2)+1);
	string sgem2 = "jewelry"+(hrand(9, tag2)+14);
	string sring = "jewelry"+(hrand(11, tag2)+40);
	string smin1 = "mineral"+(hrand(12, tag2)+1);
	string smin2 = "mineral"+(hrand(14, tag2)+12);
	string sind  = "indian_"+(hrand(10, tag2)+1);
	string saml  = "amulet_"+(hrand(10, tag2)+1);
	string sobr  = "obereg_"+(hrand(10, tag2)+1);
	string srec  = "recipe_totem_0"+(hrand(8, tag2)+1);
	string srecd = "recipe_totem_" +(hrand(3, tag2)+10);

	switch (i)
	{
		// good
		case 0:
			if (rand(1) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).money = hrand(7000, tag2);
	        }
			if (rand(1) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.gold_dublon = 30+hrand(100, tag2);
	        }
		    if (rand(1) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.(sgem1) = 2+hrand(10, tag2);
	        }
	        else
	        {
	            pchar.GenQuestBox.(loc).(boxx).items.(sgem2) = 5+hrand(20, tag2);
	        }
	        if (hrand(10, tag) > 6)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.jewelry8 = hrand(12, tag2);
	        }
	        if (rand(1) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.(sring) = 1+hrand(9, tag2);
	        }
	        if (rand(2) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.potion3 = 5+hrand(15, tag2);
	        }
	        if (rand(2) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.potion1 = 5+hrand(25, tag2);
	        }
	        if (rand(2) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.(smin1) = 1+hrand(6, tag2);
	        }
	        if (rand(2) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.(smin2) = 1+hrand(7, tag2);
	        }
	        if (hrand(30, tag) == 5)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.(sind) = 1;
	        }
	        if (hrand(30, tag) == 15)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.(saml) = 1;
	        }
			if (hrand(30, tag) == 25)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.(sobr) = 1;
	        }
	        if (hrand(9, tag) == 3)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.cirass6 = 1;
	        }
	    break;
	    // best
	    case 1:
			if (rand(1) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).money = hrand(15000, tag2);
	        }
            if (rand(2) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.chest = 1+hrand(3, tag2);
	        }
	        if (rand(2) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.icollection = 1;
	        }
	        if (rand(1) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.(sgem1) = 20+hrand(40, tag2);
	        }
	        if (rand(1) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.jewelry53 = 15+hrand(100, tag2);
	        }
	        if (rand(1) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.jewelry52 = 15+hrand(100, tag2);
	        }
	        if (rand(1) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.jewelry8 = 5+hrand(30, tag2);
	        }
			if (hrand(3, tag) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.jewelry9 = hrand(2, tag2);
	        }
	        if (hrand(4, tag) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.cirass7 = 1;
	        }
			if (rand(1) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.(sring) = 10+hrand(25, tag2);
	        }
			if (hrand(5, tag) == 1)
			{
				pchar.GenQuestBox.(loc).(boxx).items.rat_poison = 1;
			}
			if (hrand(5, tag) == 1)
			{
				pchar.GenQuestBox.(loc).(boxx).items.(srec) = 1;
			}
			if (rand(2) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.potion2 = 5+hrand(15, tag2);
	        }
	        if (rand(2) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.potion4 = 5+hrand(15, tag2);
	        }
	    break;
	    // bad
	    case 2:
			if (rand(1) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).money = hrand(1000, tag2);
	        }
	        if (rand(2) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.slave_01 = hrand(5, tag2);
	        }
	        else
	        {
                pchar.GenQuestBox.(loc).(boxx).items.blade_05 = hrand(5, tag2);
	        }
	        if (rand(2) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.blade_07 = 1;
	        }
	        if (rand(2) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.slave_02 = 1;
	        }
	        if (rand(2) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.(sgem2) = 1+hrand(2, tag2);
	        }
	        if (rand(2) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.mineral30 = 1;
	        }
	        if (rand(2) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.mineral31 = 1;
	        }
	        if (rand(2) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.mineral35 = 1;
	        }
	        if (rand(2) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.mineral14 = 1;
	        }
	        if (rand(2) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.mineral8 = 1;
	        }
	        if (rand(2) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.potion5 = 1+hrand(20, tag2);
	        }
	        if (rand(2) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.jewelry51 = +hrand(10, tag2);
	        }
	        if (rand(2) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.jewelry49 = hrand(5, tag2);
	        }
	        if (rand(2) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.jewelry48 = hrand(11, tag2);
	        }
	        if (rand(2) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.jewelry9 = 1;
	        }
	        if (hrand(9, tag) == 1)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.cirass1 = 1;
	        }
			 if (hrand(100, tag) == 30)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.(sind) = 1;
	        }
			if (hrand(100, tag) == 60)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.(saml) = 1;
	        }
			if (hrand(100, tag) == 90)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.(sobr) = 1;
	        }
	        if (hrand(9, tag) == 5)
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.cirass6 = 1;
	        }
	    break;
		// gold
		case 3:
	        if (hrand(1, tag2) == 1 && GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 10 + hrand(50, tag2 + "1") + hrand(50, tag2 + "2"))
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.jewelry5 = 500+hrand(500, tag2);
	        }
			else
			{
				pchar.GenQuestBox.(loc).(boxx).items.potionwine = 60+hrand(40, tag2);
				if (hrand(12, tag) == 10)
				{
					pchar.GenQuestBox.(loc).(boxx).items.(srecd) = 1;
				}
				if (hrand(10, tag) == 6)
				{
					pchar.GenQuestBox.(loc).(boxx).items.(srec) = 1;
				}
			}
	    break;
		// silver
		case 4:
	        if (hrand(1, tag2) == 0 && GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 10 + hrand(50, tag2 + "1") + hrand(50, tag2 + "2"))
	        {
            	pchar.GenQuestBox.(loc).(boxx).items.jewelry6 = 1000+hrand(1000, tag2);
	        }
			else
			{
				pchar.GenQuestBox.(loc).(boxx).items.potionrum = 60+hrand(40, tag2);
				if (hrand(12, tag) == 10)
				{
					pchar.GenQuestBox.(loc).(boxx).items.(srecd) = 1;
				}
				if (hrand(10, tag) == 6)
				{
					pchar.GenQuestBox.(loc).(boxx).items.(srec) = 1;
				}
			}
	    break;
		// warrior
		case 5:
			if (rand(1) == 1)
			{
				pchar.GenQuestBox.(loc).(boxx).items.GunPowder = 50+hrand(50, tag2);
			}
			if (rand(1) == 1)
			{
				pchar.GenQuestBox.(loc).(boxx).items.bullet = 50+hrand(50, tag2);
			}
			if (rand(1) == 1)
			{
				pchar.GenQuestBox.(loc).(boxx).items.grapeshot = 50+hrand(50, tag2);
			}
			if (rand(2) == 1)
			{
				pchar.GenQuestBox.(loc).(boxx).items.cartridge = 25+hrand(25, tag2);
			}
			if (rand(3) == 1)
			{
				pchar.GenQuestBox.(loc).(boxx).items.astrolab = 1;
			}
			if (rand(3) == 1)
			{
				pchar.GenQuestBox.(loc).(boxx).items.compass1 = 1;
			}
			if (rand(3) == 1)
			{
				pchar.GenQuestBox.(loc).(boxx).items.clock1 = 1;
			}
			if (hrand(5, tag) == 2)
			{
				pchar.GenQuestBox.(loc).(boxx).items.pistol3 = 1;
			}
			else
			{
				pchar.GenQuestBox.(loc).(boxx).items.pistol1 = 2;
			}
			if (hrand(20, tag) == 5)
			{
				pchar.GenQuestBox.(loc).(boxx).items.pistol6 = 1;
			}
			if (hrand(10, tag) == 1)
			{
				pchar.GenQuestBox.(loc).(boxx).items.(srec) = 1;
			}
	    break;
	}
}

bool CheckIndianGift() // Jason: есть ли подарок для индианки
{
	for (int i=47; i<=50; i++)
    {
		if (CheckCharacterItem(pchar, "jewelry"+i)) return true;
	}
	if (CheckCharacterItem(pchar, "mineral6")) return true;
	
	return false;
}

bool CheckCaribGuns() // Jason: есть ли пистоли для продажи карибам
{
	for (int i=1; i<=6; i++)
    {
		if (GetCharacterFreeItem(pchar, "pistol"+i) > 0) return true;
	}
	return false;
}

void MakeHellFireDamage() // Jason: урон огнем на рифе
{
	LAi_ApplyCharacterDamage(pchar, 45+MOD_SKILL_ENEMY_RATE*3, "other");
	LAi_CheckKillCharacter(pchar);
	PlaySound("People Fight\Death_NPC_08.wav");
}

void MakeHellSplashDamage() // Jason: урон водой на рифе
{
	PlaySound("Sea Battles\bolshoy_vsplesk_001.wav");
	CreateLocationParticles("Splash", "item", "splash"+iGlobalTemp, 0.5, 0, 0, "");
	CreateLocationParticles("blood_big", "item", "splash"+iGlobalTemp, 2.0, 0, 0, "");
	// belamour legendary edition оберег ловца скрытые свойства
	if(!IsEquipCharacterByArtefact(pchar, "talisman10"))
	{
		LAi_ApplyCharacterDamage(pchar, 90+MOD_SKILL_ENEMY_RATE*6, "other");
		LAi_CheckKillCharacter(pchar);
		PlaySound("People Fight\Death_NPC_08.wav");
	}
}

bool Tieyasal_CheckTablets() // Jason: есть ли скрижали
{
	for (int i=1; i<=6; i++)
    {
		if (CheckCharacterItem(pchar, "Tablet_"+i)) return true;
	}
	return false;
}

void ShowRipInscription(int i, string locId) // Jason: надписи на надгробиях - пасхалка
{
	if (LAi_grp_playeralarm > 0) return;
	
	if (locId == "Charles_graveyard")
	{
		switch (i)
		{
			case 1: 
				Log_Info(StringFromKey("QuestsUtilite_198")); 
				Log_Info(StringFromKey("QuestsUtilite_199"));
			break;
			case 2: 
				Log_Info(StringFromKey("QuestsUtilite_200")); 
				Log_Info(StringFromKey("QuestsUtilite_201")); 
			break;
			case 3: 
				Log_Info(StringFromKey("QuestsUtilite_202"));
				Log_Info(StringFromKey("QuestsUtilite_203"));
			break;
			case 4: 
				Log_Info(StringFromKey("QuestsUtilite_204"));
				Log_Info(StringFromKey("QuestsUtilite_205")); 
			break;
			case 5: 
				Log_Info(StringFromKey("QuestsUtilite_206")); 
				Log_Info(StringFromKey("QuestsUtilite_207")); 
			break;
			case 6: 
				Log_Info(StringFromKey("QuestsUtilite_208")); 
				Log_Info(StringFromKey("QuestsUtilite_209")); 
			break;
			case 7: 
				Log_Info(StringFromKey("QuestsUtilite_210")); 
				Log_Info(StringFromKey("QuestsUtilite_211")); 
			break;
			case 8: 
				Log_Info(StringFromKey("QuestsUtilite_212")); 
				Log_Info(StringFromKey("QuestsUtilite_213")); 
			break;
			case 9: 
				Log_Info(StringFromKey("QuestsUtilite_214")); 
				Log_Info(StringFromKey("QuestsUtilite_215")); 
			break;
		}
	}
	if (locId == "Havana_graveyard")
	{
		switch (i)
		{
			case 1: 
				Log_Info(StringFromKey("QuestsUtilite_216")); 
				Log_Info(StringFromKey("QuestsUtilite_217"));
			break;
			case 2: 
				Log_Info(StringFromKey("QuestsUtilite_218")); 
				Log_Info(StringFromKey("QuestsUtilite_219"));
			break;
			case 3: 
				Log_Info(StringFromKey("QuestsUtilite_220")); 
				Log_Info(StringFromKey("QuestsUtilite_221"));
			break;
			case 4: 
				Log_Info(StringFromKey("QuestsUtilite_222")); 
				Log_Info(StringFromKey("QuestsUtilite_223"));
			break;
			case 5: 
				Log_Info(StringFromKey("QuestsUtilite_224")); 
				Log_Info(StringFromKey("QuestsUtilite_225"));
			break;
			case 6: 
				Log_Info(StringFromKey("QuestsUtilite_226")); 
				Log_Info(StringFromKey("QuestsUtilite_227"));
			break;
			case 7: 
				Log_Info(StringFromKey("QuestsUtilite_228")); 
				Log_Info(StringFromKey("QuestsUtilite_229")); 
			break;
			case 8: 
				Log_Info(StringFromKey("QuestsUtilite_230")); 
				Log_Info(StringFromKey("QuestsUtilite_231")); 
			break;
			case 9: 
				Log_Info(StringFromKey("QuestsUtilite_232")); 
				Log_Info(StringFromKey("QuestsUtilite_233")); 
			break;
		}
	}
	if (locId == "PortRoyal_graveyard")
	{
		switch (i)
		{
		case 1: 
				Log_Info(StringFromKey("QuestsUtilite_234")); 
				Log_Info(StringFromKey("QuestsUtilite_235"));
			break;
			case 2: 
				Log_Info(StringFromKey("QuestsUtilite_236")); 
				Log_Info(StringFromKey("QuestsUtilite_237"));
			break;
			case 3: 
				Log_Info(StringFromKey("QuestsUtilite_238")); 
				Log_Info(StringFromKey("QuestsUtilite_239"));
			break;
			case 4: 
				Log_Info(StringFromKey("QuestsUtilite_240")); 
				Log_Info(StringFromKey("QuestsUtilite_241"));
			break;
			case 5: 
				Log_Info(StringFromKey("QuestsUtilite_242")); 
				Log_Info(StringFromKey("QuestsUtilite_243"));
			break;
			case 6: 
				Log_Info(StringFromKey("QuestsUtilite_244")); 
				Log_Info(StringFromKey("QuestsUtilite_245"));
			break;
			case 7: 
				Log_Info(StringFromKey("QuestsUtilite_246")); 
				Log_Info(StringFromKey("QuestsUtilite_247")); 
			break;
			case 8: 
				Log_Info(StringFromKey("QuestsUtilite_248")); 
				Log_Info(StringFromKey("QuestsUtilite_249")); 
			break;
			case 9: 
				Log_Info(StringFromKey("QuestsUtilite_250")); 
				Log_Info(StringFromKey("QuestsUtilite_251")); 
			break;
		}
	}
	if (locId == "Villemstad_graveyard")
	{
		switch (i)
		{
			case 1: 
				Log_Info(StringFromKey("QuestsUtilite_252")); 
				Log_Info(StringFromKey("QuestsUtilite_253"));
			break;
			case 2: 
				Log_Info(StringFromKey("QuestsUtilite_254")); 
				Log_Info(StringFromKey("QuestsUtilite_255"));
			break;
			case 3: 
				Log_Info(StringFromKey("QuestsUtilite_256")); 
				Log_Info(StringFromKey("QuestsUtilite_257"));
			break;
			case 4: 
				Log_Info(StringFromKey("QuestsUtilite_258")); 
				Log_Info(StringFromKey("QuestsUtilite_259"));
			break;
			case 5: 
				Log_Info(StringFromKey("QuestsUtilite_260")); 
				Log_Info(StringFromKey("QuestsUtilite_261"));
			break;
			case 6: 
				Log_Info(StringFromKey("QuestsUtilite_262")); 
				Log_Info(StringFromKey("QuestsUtilite_263"));
			break;
			case 7: 
				Log_Info(StringFromKey("QuestsUtilite_264")); 
				Log_Info(StringFromKey("QuestsUtilite_265")); 
			break;
			case 8: 
				Log_Info(StringFromKey("QuestsUtilite_266")); 
				Log_Info(StringFromKey("QuestsUtilite_267")); 
			break;
			case 9: 
				Log_Info(StringFromKey("QuestsUtilite_268")); 
				Log_Info(StringFromKey("QuestsUtilite_269")); 
			break;
		}
	}
}

//Jason 240912 ------------------------------- адмиральские карты ----------------------------------------------
string SelectAdmiralMaps() // выбор случайной не повторяющейся
{	
	string sMap = "";
	ref sld = characterFromId("Dios");
	string map[24];
	map[0] = "A_map_bermudas";
	map[1] = "A_map_jam";
	map[2] = "A_map_cayman";
	map[3] = "A_map_barbados";
	map[4] = "A_map_tortuga";
	map[5] = "A_map_curacao";
	map[6] = "A_map_martiniqua";
	map[7] = "A_map_dominica";
	map[8] = "A_map_trinidad";
	map[9] = "A_map_puerto";
	map[10] = "A_map_cuba";
	map[11] = "A_map_hisp";
	map[12] = "A_map_nevis";
	map[13] = "A_map_beliz";
	map[14] = "A_map_guad";
	map[15] = "A_map_santa";
	map[16] = "A_map_antigua";
	map[17] = "A_map_terks";
	map[18] = "A_map_sm";
	map[19] = "A_map_maine_1";
	map[20] = "A_map_maine_2";
	map[21] = "A_map_panama";
	map[22] = "A_map_cumana";
	map[23] = "A_map_perl";
	
	string storeArray[24]; // mitrokosta переписал случайный выбор - старый иногда ничего не выдавал даже если карты были
	int howStore = 0;
	string sTemp;
	
	for (int i = 0; i < 24; i++) {
		sTemp = map[i];
		if (!CheckAttribute(sld, "quest.map." + sTemp))
        {
			if(CheckAttribute(&TreasureTiers[0], "map_a." + sTemp))
                continue; // Если есть такой атрибут, значит мы сейчас генерим карту в клад, и там такая уже лежит
            storeArray[howStore] = sTemp;
			howStore++;
		}
	}
	
	if (howStore > 0) {
		sMap = storeArray[rand(howStore - 1)];
		//sld.quest.map.(sMap) = true;
		}
	
	return sMap;
}

void GiveAdmiralMapToCharacter(ref chr, int abl) // дать случайную с рандомом
{
	if (!CheckAttribute(pchar, "questTemp.AdmiralMap")) return;
	if (hrand(abl, chr.id + chr.name) == 0)
	{
		string amap = SelectAdmiralMaps();
		if (amap != "") GiveItem2Character(chr, amap);
	}
}

void TargetAdmiralMapToCharacter(ref chr, string amap) // дать конкретную, если такой ещё нет
{
	if (!CheckAttribute(pchar, "questTemp.AdmiralMap")) return;
	ref sld = characterFromId("Dios");
	if (!CheckAttribute(sld, "quest.map."+amap))
	{
		GiveItem2Character(chr, amap);
		//sld.quest.map.(amap) = true;
	}
}

int CountAdmiralMapFromCharacter() // сосчитать
{
	aref arItems;
	int amap = 0;
	string sName;
	makearef(arItems, pchar.items);
	int n = GetAttributesNum(arItems);
	for(int i=0; i<n; i++)
	{
		sName = GetAttributeName(GetAttributeN(arItems, i));
		if (findsubstr(sName, "A_map_", 0) != -1) amap++;
	}
	return amap;
}

string IdentifyAdmiralMapLast() // идентифицировать последнюю в списке
{
	aref arItems;
	string sName;
	string sMap = "";
	makearef(arItems, pchar.items);
	int n = GetAttributesNum(arItems);
	for(int i=0; i<n; i++)
	{
		sName = GetAttributeName(GetAttributeN(arItems, i));
		if (findsubstr(sName, "A_map_", 0) != -1) sMap = sName;
	}
	return sMap;
}

// mitrokosta не хочу копипастить код прохода по всем локам и фантомам
// handler это функция вида void Handler(ref chref, string itemID) где chref - ссылка на найденного персонажа/бокса с предметом, а itemID - ид предмета
// вызывается на всех найденных объектах, возвращает число найденных
int FindRealItem(string itemID, string handler) {
	ref sld;
	aref chref;
	int i, j;
	string simpleBox, privateBox;
	int numChr = 0;

	for(i = 0; i < nLocationsNum; i++) {
		sld = &Locations[i]; // проверим локации
		for(j = 1; j < MAX_HANDLED_BOXES; j++) {
			simpleBox = "box" + j;
			privateBox = "private" + j;
			
			if(!CheckAttribute(sld, simpleBox) && !CheckAttribute(sld, privateBox)) {
				break;
			}

			if(CheckAttribute(sld, simpleBox + ".Items." + itemID)) {
				trace(itemID + " найден в локации " + sld.id + " в боксе " + simpleBox);
				makearef(chref, sld.(simpleBox));
				if (handler != "") {
					call handler(chref, itemID);
				}
				numChr++;
			}
			
			if(CheckAttribute(sld, privateBox + ".Items." + itemID)) {
				trace(itemID + " найден в локации " + sld.id + " в привате " + privateBox);
				makearef(chref, sld.(privateBox));
				if (handler != "") {
					call handler(chref, itemID);
				}
				numChr++;
			}
		}
	}

	for(i = 0; i < MAX_CHARACTERS; i++) {
		sld = &Characters[i]; // и фантомов
		if(CheckAttribute(sld, "Items." + itemID)) {
			trace(itemID + " найден у персонажа " + sld.id);
			if (handler != "") {
				call handler(sld, itemID);
			}
			numChr++;
		}
	}
	return numChr;
}

// mitrokosta проверить существование помеченных отличных карт и "освободить" их
void PrepareAdmiralMaps() {
	string sMap;
	string map[24];
	ref sld = CharacterFromID("Dios");

	map[0] = "A_map_bermudas";
	map[1] = "A_map_jam";
	map[2] = "A_map_cayman";
	map[3] = "A_map_barbados";
	map[4] = "A_map_tortuga";
	map[5] = "A_map_curacao";
	map[6] = "A_map_martiniqua";
	map[7] = "A_map_dominica";
	map[8] = "A_map_trinidad";
	map[9] = "A_map_puerto";
	map[10] = "A_map_cuba";
	map[11] = "A_map_hisp";
	map[12] = "A_map_nevis";
	map[13] = "A_map_beliz";
	map[14] = "A_map_guad";
	map[15] = "A_map_santa";
	map[16] = "A_map_antigua";
	map[17] = "A_map_terks";
	map[18] = "A_map_sm";
	map[19] = "A_map_maine_1";
	map[20] = "A_map_maine_2";
	map[21] = "A_map_panama";
	map[22] = "A_map_cumana";
	map[23] = "A_map_perl";

	if (CheckAttribute(pchar, "questTemp.AdmiralMap")) {
		for (int i = 0; i < 24; i++) {
			sMap = map[i];
			if (FindRealItem(sMap, "") == 0) {
				DeleteAttribute(sld, "quest.map." + sMap); // второй шанс... можно и без этого конечно
			}
		}
	}
}

// mitrokosta если у перса/бокса есть отличная карта, пометить её как найденную и удалить отовсюду кроме него самого
void CheckAdmiralMaps(ref chref) {
	string sMap;
	string map[24];
	ref sld = CharacterFromID("Dios");
	ref rMap = ItemsFromID("map_full");
	ref qMap = ItemsFromID("mapQuest");

	map[0] = "A_map_bermudas";
	map[1] = "A_map_jam";
	map[2] = "A_map_cayman";
	map[3] = "A_map_barbados";
	map[4] = "A_map_tortuga";
	map[5] = "A_map_curacao";
	map[6] = "A_map_martiniqua";
	map[7] = "A_map_dominica";
	map[8] = "A_map_trinidad";
	map[9] = "A_map_puerto";
	map[10] = "A_map_cuba";
	map[11] = "A_map_hisp";
	map[12] = "A_map_nevis";
	map[13] = "A_map_beliz";
	map[14] = "A_map_guad";
	map[15] = "A_map_santa";
	map[16] = "A_map_antigua";
	map[17] = "A_map_terks";
	map[18] = "A_map_sm";
	map[19] = "A_map_maine_1";
	map[20] = "A_map_maine_2";
	map[21] = "A_map_panama";
	map[22] = "A_map_cumana";
	map[23] = "A_map_perl";

	if (CheckAttribute(pchar, "questTemp.AdmiralMap")) {
		for (int i = 0; i < 24; i++) {
			sMap = map[i];
			if (CheckCharacterItem(chref, sMap)) {
				if (!CheckAttribute(sld, "quest.map." + sMap)) {
					FindRealItem(sMap, "TakeItemFromCharacter"); // стереть карту отовсюду
					DeleteAttribute(rMap, "BoxTreasure." + sMap);
					DeleteAttribute(qMap, "BoxTreasure." + sMap);

					GiveItem2Character(chref, sMap);
					sld.quest.map.(sMap) = true;
					trace("Карта " + sMap + " помечена как найденная, больше она генериться не будет");
				}
			}
		}
	}
}

// belamour дать адмиральский атлас
void GiveAdmiralAtlasToCharacter (ref chr)
{
	string sItmId;
	for (i=0; i<TOTAL_ITEMS; i++)
	{
		if(!CheckAttribute(&Items[i],"groupID")) continue;
		if(Items[i].groupID != MAPS_ITEM_TYPE) continue;
		if(findsubstr(Items[i].id, "A_map_", 0) != -1) GiveItem2Character(chr, Items[i].id);
	}
}
// <-- адмиральские карты

// --> персидские клинки Фадея
int CheckNCountPersian() // patch-7
{
	int blade = 0;
	
	if (GetCharacterFreeGenerableItem(pchar, "blade_22") > 0) blade++;
	if (GetCharacterFreeGenerableItem(pchar, "blade_23") > 0) blade++;
	if (GetCharacterFreeGenerableItem(pchar, "blade_24") > 0) blade++;
	
	return blade;
}

string CheckNIdentifyPersian()
{
	ref rItem;
	aref arItems;
	string sName;
	string sBlade = "";
	makearef(arItems, pchar.items);
	int n = GetAttributesNum(arItems);
	for(int i=0; i<n; i++)
	{
		sName = GetAttributeName(GetAttributeN(arItems, i));
		rItem = ItemsFromID(sName);
		if (CheckAttribute(rItem, "target") && rItem.target == TGT_PERSIAN) sBlade = sName;
	}
	return sBlade;
}
// <-- персидские клинки Фадея

void CaveEnc_FillSkeleton(ref chr, int i) // лут для скелетов в пещерах
{
    // На if'ах оставил старую логику (TODO: переверить)
    // За счёт "&" для каждого конкретного chr в конкретный день используется одна и та же дробь
    string tag2 = chr.id + chr.name;
    string tag  = "&FillSkeleton" + tag2;

	switch (i)
	{
		case 0:
			if (hrand(7, tag) == 0) TakeNItems(chr, "gold_dublon", hrand(50, tag2)); // Addon-2016 Jason
			else if (hrand(7, tag) == 1) TakeNItems(chr, "chest", hrand(1, tag2));
			else if (hrand(7, tag) == 2) TakeNItems(chr, "purse"+(hrand(2, tag2)+1), 1);
			else if (hrand(7, tag) >  2) TakeNItems(chr, "mineral"+(hrand(12, tag2)+1), hrand(5, tag2 + "2"));
		break;
	
		case 1:
			if (hrand(6, tag) == 0) TakeNItems(chr, "indian_"+(hrand(10, tag2)+1), 1);
			else if (hrand(6, tag) == 1) TakeNItems(chr, "blade_0"+(hrand(2,  tag2)+7), 1);
			else if (hrand(6, tag) == 2) TakeNItems(chr, "pistol1", 1);
			else if (hrand(6, tag) >  2) TakeNItems(chr, "mineral"+(hrand(13, tag2)+13), hrand(2, tag2 + "2"));
		break;
		
		case 2:
			if (hrand(5, tag) == 0) TakeNItems(chr, "amulet_"+(hrand(10, tag2)+1), 1);
			else if (hrand(5, tag) == 1) TakeNItems(chr, "jewelry"+(hrand(5,  tag2)+1), hrand(20, tag2 + "2"));
			else if (hrand(5, tag) >  1) TakeNItems(chr, "mineral"+(hrand(25, tag2)+1), hrand(3,  tag2 + "2"));
		break;
		
		case 3:
			if (hrand(8, tag) == 0) TakeNItems(chr, "obereg_"+(hrand(10, tag2)+1), 1);
			else if (hrand(8, tag) == 1) TakeNItems(chr, "jewelry8",hrand(10, tag2));
			else if (hrand(8, tag) == 2) TakeNItems(chr, "jewelry7",hrand(2,  tag2));
			else if (hrand(8, tag) == 3) TakeNItems(chr, "jewelry11",hrand(5, tag2));
			else if (hrand(8, tag) == 4) TakeNItems(chr, "jewelry"+(hrand(10, tag2)+41), hrand(6, tag2 + "2"));
			else if (hrand(8, tag) == 5) TakeNItems(chr, "jewelry"+(hrand(11, tag2)+12), hrand(6, tag2 + "2"));
			else if (hrand(8, tag) >  5) TakeNItems(chr, "mineral"+(hrand(20, tag2)+1),  hrand(4, tag2 + "2"));
		break;
	}
}
// поиск и определение линейных кораблей наций
bool FindCompanionShips(int Type)
{
	for(int i=1; i<COMPANION_MAX; i++)
	{
		int iTemp = GetCompanionIndex(PChar, i);
		if(iTemp > 0)
		{
			ref sld = GetCharacter(iTemp);
			if(sti(RealShips[sti(sld.ship.type)].basetype) == Type) return true;
		}
	}
	return false;
}

bool LineShips_CheckAndIdentify(int Nation)
{
	if(GetCharacterEquipByGroup(pchar, HAT_ITEM_TYPE) == "hat5") return false;
	
	switch (Nation)
	{
		case ENGLAND:
			if (sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_LSHIP_ENG && FindCompanionShips(SHIP_LSHIP_ENG) && Trafalgar_FindCompanionShip()) return false; // Jason, НСО
			if (sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LSHIP_ENG || FindCompanionShips(SHIP_LSHIP_ENG)) return true;
		break;
		
		case FRANCE:
			if (sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_LSHIP_FRA && FindCompanionShips(SHIP_LSHIP_FRA) && Ecliaton_FindCompanionShip()) return false; // Jason, НСО
			if (sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LSHIP_FRA || FindCompanionShips(SHIP_LSHIP_FRA)) return true;
		break;
		
		case SPAIN:
			if (sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LSHIP_SPA || FindCompanionShips(SHIP_LSHIP_SPA)) return true;
		break;
		
		case HOLLAND:
			if (sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LSHIP_HOL || FindCompanionShips(SHIP_LSHIP_HOL)) return true;
		break;
	}
	return false;
}

bool Ecliaton_FindCompanionShip() // Jason, НСО
{
	for(int i=1; i<COMPANION_MAX; i++)
	{
		int iTemp = GetCompanionIndex(PChar, i);
		if(iTemp > 0)
		{
			ref sld = GetCharacter(iTemp);
			if(sld.ship.name == StringFromKey("QuestsUtilite_270") && CheckAttribute(pchar, "questTemp.Patria.Ecliaton")) return true;
		}
	}
	return false;
}

bool Trafalgar_FindCompanionShip() // Jason, НСО
{
	for(int i=1; i<COMPANION_MAX; i++)
	{
		int iTemp = GetCompanionIndex(PChar, i);
		if(iTemp > 0)
		{
			ref sld = GetCharacter(iTemp);
			if(sld.ship.name == StringFromKey("QuestsUtilite_271") && CheckAttribute(pchar, "questTemp.Patria.Trafalgar")) return true;
		}
	}
	return false;
}

bool Companion_CheckShipType(int iShipType) // поиск любого конкретного типа корабля у компаньона и запоминание индекса компаньона для дальнейшего использования
{
	int cn;
	ref sld;
	for (int i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn != -1)
		{
			sld = &characters[cn];
			if (RealShips[sti(sld.Ship.Type)].basetype == iShipType)
			{
				pchar.GenQuest.CompanionId = sld.id;
				return true;
			}
		}
	}
	return false;
}

bool CheckTotalDepositsSum(ref _chref, int Sum)
{
	aref 		quests;
	aref 		quest;
	int  		nQuestsNum;
	int  		n;
	string 		sQuestName;
	int			TotalSum = 0;
		
	if (CheckAttribute(_chref, "Quest.Deposits")) 
    {
    	makearef(quests,Characters[GetMainCharacterIndex()].Quest.Deposits);
    	nQuestsNum = GetAttributesNum(quests);

    	for(n = 0; n < nQuestsNum; n++)
    	{
    		quest = GetAttributeN(quests,n);
    		sQuestName = GetAttributeName(quest);
						
    		if (CheckAttribute(_chref, "Quest.Deposits."+sQuestName+".Sum"))
    		{
				if(HasSubStr(sQuestName, "_type1"))
				{
					TotalSum += sti(_chref.Quest.Deposits.(sQuestName).Sum);
				}
							
			}			
        }
    }
	else return false;
	
	if(TotalSum >= Sum) return true;
	
	return false;
}

bool Caleuche_CheckAmulet() // Калеуче, амулеты
{
	int aml = 0;
	if (CheckCharacterItem(pchar, "kaleuche_amulet2")) aml++;
	if (CheckCharacterItem(pchar, "kaleuche_amulet3")) aml++;
	
	if (aml > 0) return true;
	
	return false;
}

string SelectRandomArtefact(int kind, string tag) // dlc
{
	string prefix, suffix, amulet;
	suffix = "_"+(hrand(10, tag)+1);
	switch (kind)
	{
		case 1: prefix = "indian"; break;
		case 2: prefix = "amulet"; break;
		case 3: prefix = "obereg"; break;
	}
	amulet = prefix+suffix;
	return amulet;
}

// Addon 2016-1 Jason Пиратская линейка
bool Mtraxx_MeridaCheckCarpenter() // проверка наличия плотника и его умений
{
    DelBakSkillAttr(PChar);
    ClearCharacterExpRate(PChar);
    RefreshCharacterSkillExpRate(PChar);

	return GetSummonSkillFromName(PChar, SKILL_REPAIR) >= 30 && CheckOfficersPerk(PChar, "BasicBattleState");
}

string Mtraxx_RetributionSelectRanditem() // выбор рандитема
{
	string sItem;
	int iChance = rand(9);
	
	switch (iChance)
	{
		case 0: sItem = "potion1"; break;
		case 1: sItem = "potion1"; break;
		case 2: sItem = "potion2"; break;
		case 3: sItem = "potion3"; break;
		case 4: sItem = "potion3"; break;
		case 5: sItem = "potion4"; break;
		case 6: sItem = "potionrum"; break;
		case 7: sItem = "potionrum"; break;
		case 8: sItem = "potionwine"; break;
		case 9: 
			if (rand(1) == 0) sItem = "potion2"; 
			else sItem = "berserker_potion"; 
		break;
	}
	return sItem;
}

void MakeIndianPoisonAttack(ref chref, ref _attack) // яд индейцев таино
{
	// исключения
	if (CheckAttribute(chref, "chr_ai.immortal")) return;                                                          /*Экку Korsar - доп проверки на нежить \/ */
	if (CheckAttribute(chref, "monster") || chref.chr_ai.group == LAI_GROUP_MONSTERS || chref.sex == "skeleton" || chref.model.animation == "skeleton" || HasSubStr(chref.model, "skel")) return; // патч 17/1
	if (CheckAttribute(chref, "PoisonResistent"))
	{
		if(ShowCharString()) Log_Chr(chref, StringFromKey("QuestsUtilite_272"));
		else log_info(StringFromKey("QuestsUtilite_272"));
		return;
	}
	if (LAi_GetCharacterHP(chref) < 15) 
	{
		if (CheckAttribute(chref, "chr_ai.immortal")) return;
		bool isSetBalde = (CheckAttribute(chref, "equip.blade") == true);
		LAi_SetImmortal(chref, true);
		//log_info("Персонаж с ID = "+chref.id+" с индексом "+chref.index+" и именем "+GetFullName(chref)+" достиг 15 НР");
		DeleteAttribute(chref, "quest.indianpoisoned");
		LAi_SetImmortal(chref, false);
		LAi_KillCharacter(chref);
		LAi_SetResultOfDeath(_attack, chref, isSetBalde);
		return;
	}
	sGlobalTemp = _attack.id; // атакующий один и тот же
	chref.quest.indianpoisoned = true;
	//log_info("Персонаж с ID = "+chref.id+" с индексом "+chref.index+" и именем "+GetFullName(chref)+" отравлен ядом таино");
	if (!CheckAttribute(chref, "quest.indianpoisoned.info"))
	{
		if(ShowCharString()) Log_Chr(chref, StringFromKey("QuestsUtilite_273"));
		else log_info(StringFromKey("QuestsUtilite_274", GetFullName(chref)));
		chref.quest.indianpoisoned.info = true;
	}
	LAi_ApplyCharacterDamage(chref, 15, "other");
	DoQuestFunctionDelay("MakeIndianPoisonAttackCycle", 0.5);
}

void MakeIndianPoisonAttackCycle(string qName) // к функции выше
{
	DoQuestFunctionDelay("MakeTainoPoisonAttack", 0.5);
}

void MakeTainoPoisonAttack(string qName) // к функции выше
{
	ref chref, _attack;
	_attack = characterFromId(sGlobalTemp);
	for(int i=0; i<TOTAL_CHARACTERS; i++)
	{	
		chref = &characters[i];
		if (CheckAttribute(chref, "quest.indianpoisoned")) MakeIndianPoisonAttack(chref, _attack);
	}
}

// Jason Дороже золота
bool GoldenGirl_CheckGirls() // проверка наличия Элен или Мэри
{
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) 
	{
		pchar.questTemp.GoldenGirl.Helena = "true";
		log_Testinfo("Героиня - Элен");
		return true;
	}
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) 
	{
		pchar.questTemp.GoldenGirl.Mary = "true";
		log_Testinfo("Героиня - Мэри");
		return true;
	}
	return false;
}

// Jason Долго и счастливо
bool LongHappy_CheckGirls() // проверка наличия Элен или Мэри
{
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) 
	{
		return true;
	}
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) 
	{
		return true;
	}
	return false;
}

bool LongHappy_CheckCondisiones() // проверка всех условий fix 22-03-20
{
	if (!CheckAttribute(pchar, "questTemp.Tieyasal_WinEnd")) return false;
	
	if (!GoldenGirl_CheckGirls()) return false;
	
	if (!CheckAttribute(pchar, "questTemp.GoldenGirl")) return false;
	
	if (CheckAttribute(pchar, "questTemp.GoldenGirl")) 
	{
		if (!LongHappy_CheckGoldenGirl()) return false;
	}
	if (CheckAttribute(pchar, "questTemp.Patria"))
	{
		if (!LongHappy_CheckPatria()) return false;
	}
	return true;
}

bool LongHappy_CheckGoldenGirl() // fix 22-03-20
{
	if (pchar.questTemp.GoldenGirl == "end") return true;
	if (pchar.questTemp.GoldenGirl == "cards_fail") return true;
	if (pchar.questTemp.GoldenGirl == "start_fail") return true;
	return false;
}

bool LongHappy_CheckPatria() // fix 22-03-20
{
	if (pchar.questTemp.Patria == "end") return true;
	if (pchar.questTemp.Patria == "fail") return true;
	return false;
}

bool LongHappy_CheckShore() // 
{
	ref chr;
	if (CheckAttribute(pchar, "questTemp.LongHappy") && !CheckAttribute(pchar, "questTemp.LongHappy.Offer") && LongHappy_CheckGirls())
	{
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) chr = characterFromId("Helena");
		else chr = characterFromId("Mary");
		
		if (IsOfficer(chr) && pchar.location == pchar.questTemp.LongHappy.Shore && GetCharacterItem(pchar, "potionwine") >= 2) return true;
	}
	return false;
}

bool LongHappy_CheckGoods() // 
{
	if (CheckAttribute(pchar, "questTemp.LongHappy.SmallMarry"))
	{
		if (GetSquadronGoods(pchar, GOOD_RUM) >= 50 && GetSquadronGoods(pchar, GOOD_WINE) >= 20 && sti(Pchar.money) >= 300000) return true;
	}
	else
	{
		if (GetSquadronGoods(pchar, GOOD_RUM) >= 100 && GetSquadronGoods(pchar, GOOD_WINE) >= 50 && sti(Pchar.money) >= 500000) return true;
	}
	return false;
}

bool LongHappy_CheckSaga() // 
{
	if (CheckAttribute(pchar, "questTemp.Saga.Late")) return false;
	if (CheckAttribute(pchar, "questTemp.Saga.CenturionSink")) return false;
	return true;
}

bool LongHappy_CheckTavernGoods() // 
{
	if (GetSquadronGoods(pchar, GOOD_RUM) >= sti(pchar.questTemp.LongHappy.MarryRum) && sti(Pchar.money) >= sti(pchar.questTemp.LongHappy.MarryMoney)) return true;
	return false;
}

// mitrokosta проверка, может ли/хочет ли казначей считать крыс и деньги
bool CheckFunctionalTreasurer() {
	if (!IsPCharHaveTreasurer()) {
		return false;
	}
	
	ref sld = GetPCharTreasurerRef();
	
	if (sld.id == "Helena") {
		return false;
	}
	
	if (sld.id == "Mary") {
		return false;
	}
	
	if (sld.id == "Tichingitu") {
		return false;
	}
	
	if (sld.id == "Tonzag") {
		return false;
	}
	
	if (sld.id == "Knippel") {
		return false;
	}
	
	if (sld.id == "Longway") {
		return false;
	}
	
	if (sld.id == "Baker") {
		return false;
	}
	
	return true;
}

// подсказки на старте игры
// todo: дописать проверку на то, что они не отключены
void NewGameTip(string sTip) {
	if(CheckAttribute(&InterfaceStates, "ShowTutorial") && sti(InterfaceStates.ShowTutorial) == 1)
	{
		aref arFader;
		if(GetEntity(arFader,"fader"))
		{
			pchar.systeminfo.delayTip = sTip;
			DoQuestFunctionDelay("NewGameTip2", 0.5);
			return;
		}
		if(CheckAttribute(pchar,"systeminfo.DialogExitDelay"))
		{
			pchar.systeminfo.delayTip = sTip;
			DoQuestFunctionDelay("NewGameTip2", 0.5);
			return;
		}
		if(dialogRun)
		{
			pchar.systeminfo.delayTip = sTip;
			DoQuestFunctionDelay("NewGameTip2", 1.5);
			return;
		}
		LaunchMessage(sTip);
		/* PlaySound("interface\notebook.wav");
		Log_SetStringToLog(sTip); */
	}
}

void NewGameTip2(string sQuest)
{
	if(dialogRun || bQuestCheckProcessFreeze || pchar.chr_ai.type != "player")
	{
		//Log_testinfo("Отработал dialogRun in NewGameTip2");
		DoQuestFunctionDelay("NewGameTipInDialog", 1.5);
		return;
	}
	if(CheckAttribute(pchar,"systeminfo.delayTip"))
	{
		//Log_testinfo("Отработал systeminfo.delayTip in NewGameTip2");
		LaunchMessage(pchar.systeminfo.delayTip);
		DeleteAttribute(pchar,"systeminfo.delayTip");
	}
}

void NewGameTipInDialog(string sQuest)
{
	if(dialogRun || bQuestCheckProcessFreeze || pchar.chr_ai.type != "player")
	{
		//Log_testinfo("Отработал dialogRun in NewGameTipInDialog");
		DoQuestFunctionDelay("NewGameTip2", 1.5);
		return;
	}
	if(CheckAttribute(pchar,"systeminfo.delayTip"))
	{
		//Log_testinfo("Отработал systeminfo.delayTip in NewGameTipInDialog");
		LaunchMessage(pchar.systeminfo.delayTip);
		DeleteAttribute(pchar,"systeminfo.delayTip");
	}
}
// квестовая проверка выхода из каюты
// вернет false, если выход невозможен
bool QuestCheckReturn2SeaAfterCabin() {
	if (CheckAttribute(pchar, "questTemp.Sharlie.FolkeWait")) {
		sld = CharacterFromID("Folke");
		if(CheckAttribute(sld, "navigator")) {
			// сделать обычным офицером
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Dialog.CurrentNode = "hired";
			sld.quest.meeting = true;
			sld.location = "none";
			
			// выпустить из каюты
			LocatorReloadEnterDisable("My_Cabin_Small", "reload1", false);
			DeleteAttribute(pchar, "questTemp.Sharlie.FolkeWait");
			NewGameTip(StringFromKey("QuestsUtilite_275"));
			pchar.quest.Tutorial_Box.win_condition.l1 = "My_Cabine";
			pchar.quest.Tutorial_Box.function = "Tutorial_Box";
		} else {
			PlaySound("interface\knock.wav");
			//Log_Info("Назначьте Фулька Делюка своим штурманом в окне персонажа (F4)");
			LaunchTutorial("Navigator", 1);
			return false;
		}
		pchar.systeminfo.tutorial.navigator = true;
	}
	
	return true;
}
// Jason Исла Мона
bool IslaMona_CheckFood() // 
{
	ref strg = &stores[IslaMona_STORE];
	int i, n;
	i = GetStorageGoodsQuantity(strg, GOOD_FOOD);
	n = GetStorageGoodsQuantity(strg, GOOD_MEDICAMENT);
	if (i >= 2000 && n >= 300) return true;
	return false;
}

bool IslaMona_CheckBuild() // 
{
	ref strg = &stores[IslaMona_STORE];
	int p, b, l, s, o, c;
	p = GetStorageGoodsQuantity(strg, GOOD_PLANKS);
	b = GetStorageGoodsQuantity(strg, GOOD_BRICK);
	l = GetStorageGoodsQuantity(strg, GOOD_LEATHER);
	s = GetStorageGoodsQuantity(strg, GOOD_SAILCLOTH);
	o = GetStorageGoodsQuantity(strg, GOOD_OIL);
	c = GetStorageGoodsQuantity(strg, GOOD_CLOTHES);
	if (p >= 1000 && b >= 500 && l >= 200 && s >= 300 && o >= 50 && c >= 200) return true;
	return false;
}

bool IslaMona_CheckHarbour() // 
{
	ref strg = &stores[IslaMona_STORE];
	int p, b, s, o;
	p = GetStorageGoodsQuantity(strg, GOOD_PLANKS);
	b = GetStorageGoodsQuantity(strg, GOOD_BRICK);
	s = GetStorageGoodsQuantity(strg, GOOD_SAILCLOTH);
	o = GetStorageGoodsQuantity(strg, GOOD_OIL);
	if (p >= 300 && b >= 50 && s >= 150 && o >= 20) return true;
	return false;
}

bool IslaMona_CheckTavern() // 
{
	ref strg = &stores[IslaMona_STORE];
	int p, b, l, s, o, r, w;
	p = GetStorageGoodsQuantity(strg, GOOD_PLANKS);
	b = GetStorageGoodsQuantity(strg, GOOD_BRICK);
	l = GetStorageGoodsQuantity(strg, GOOD_LEATHER);
	s = GetStorageGoodsQuantity(strg, GOOD_SAILCLOTH);
	o = GetStorageGoodsQuantity(strg, GOOD_OIL);
	r = GetStorageGoodsQuantity(strg, GOOD_RUM);
	w = GetStorageGoodsQuantity(strg, GOOD_WINE);
	if (p >= 200 && b >= 200 && l >= 100 && s >= 50 && o >= 10 && r >= 1000 && w >= 1000) return true;
	return false;
}

bool IslaMona_CheckPlantation() // 
{
	ref strg = &stores[IslaMona_STORE];
	int p, b, l, s, o;
	p = GetStorageGoodsQuantity(strg, GOOD_PLANKS);
	b = GetStorageGoodsQuantity(strg, GOOD_BRICK);
	l = GetStorageGoodsQuantity(strg, GOOD_LEATHER);
	s = GetStorageGoodsQuantity(strg, GOOD_SAILCLOTH);
	o = GetStorageGoodsQuantity(strg, GOOD_OIL);
	if (p >= 500 && b >= 250 && l >= 200 && s >= 100 && o >= 30) return true;
	return false;
}

bool IslaMona_CheckSlave() // 
{
	aref arItems;
	string sName;
	makearef(arItems, pchar.items);
	int res = 0;
	int iItemsNum = GetAttributesNum(arItems);
	for(int i=0; i<iItemsNum; i++)
	{
		sName = GetAttributeName(GetAttributeN(arItems, i));
		if (findsubstr(sName, "mushket" , 0) != -1 && GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE) != sName)
		{
			res++;
			i = iItemsNum;
		}
	}
	if (GetCharacterItem(pchar, "mineral30") >= 15) res++;
	if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 15) res++;
	if (res == 3) return true;
	return false;
}

bool IslaMona_CheckBacautSpace() // 
{
	ref strg = &stores[29];
	int i, n;
	i = GetStorageUsedWeight(strg); // вес того, что уже лежит
	n = 7*sti(pchar.questTemp.IslaMona.Factory.Goods); // вес партии бакаута
	if (50000-i-n >= 0) return true;
	return false;
}

bool IslaMona_CheckChurch() // 
{
	ref strg = &stores[29];
	int p, b, o, s, m;
	p = GetStorageGoodsQuantity(strg, GOOD_PLANKS);
	b = GetStorageGoodsQuantity(strg, GOOD_BRICK);
	o = GetStorageGoodsQuantity(strg, GOOD_OIL);
	s = GetStorageGoodsQuantity(strg, GOOD_SANDAL);
	m = GetStorageGoodsQuantity(strg, GOOD_MAHOGANY);
	if (p >= 300 && b >= 100 && o >= 10 && s >= 20 && m >= 100)  return true;
	return false;
}

bool IslaMona_CheckCandles()
{
	if(CheckAttribute(pchar, "questTemp.IslamonaChurch.GoldNugget") && GetCharacterItem(pchar, "jewelry5") > 0) return true;
	if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Candle") && GetCharacterItem(pchar, "mineral3") > 0) return true;
	if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Amber") && GetCharacterItem(pchar, "jewelry8") > 0) return true;
	if(CheckAttribute(pchar, "questTemp.IslamonaChurch.BlueAmber") && GetCharacterItem(pchar, "jewelry7") > 0) return true;
	
	return false;
}

void IslaMona_RemoveCandles()
{
	if(CheckAttribute(pchar, "questTemp.IslamonaChurch.GoldNugget"))
	{
		int gn = sti(pchar.questTemp.IslamonaChurch.GoldNugget);
		if(GetCharacterItem(pchar, "jewelry5") < gn)
		{
			pchar.questTemp.IslamonaChurch.GoldNugget = sti(pchar.questTemp.IslamonaChurch.GoldNugget) - GetCharacterItem(pchar, "jewelry5");
			RemoveItems(pchar, "jewelry5", GetCharacterItem(pchar, "jewelry5"));
		}
		else
		{
			RemoveItems(pchar, "jewelry5", sti(pchar.questTemp.IslamonaChurch.GoldNugget));
			DeleteAttribute(pchar, "questTemp.IslamonaChurch.GoldNugget");
		}
	}
	if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Candle"))
	{
		int can = sti(pchar.questTemp.IslamonaChurch.Candle);
		if(GetCharacterItem(pchar, "mineral3") < can)
		{
			pchar.questTemp.IslamonaChurch.Candle = sti(pchar.questTemp.IslamonaChurch.Candle) - GetCharacterItem(pchar, "mineral3");
			RemoveItems(pchar, "mineral3", GetCharacterItem(pchar, "mineral3"));
		}
		else
		{
			RemoveItems(pchar, "mineral3", sti(pchar.questTemp.IslamonaChurch.Candle));
			DeleteAttribute(pchar, "questTemp.IslamonaChurch.Candle");
		}
	}
	if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Amber"))
	{
		int Amb = sti(pchar.questTemp.IslamonaChurch.Amber);
		if(GetCharacterItem(pchar, "jewelry8") < Amb)
		{
			pchar.questTemp.IslamonaChurch.Amber = sti(pchar.questTemp.IslamonaChurch.Amber) - GetCharacterItem(pchar, "jewelry8");
			RemoveItems(pchar, "jewelry8", GetCharacterItem(pchar, "jewelry8"));
		}
		else
		{
			RemoveItems(pchar, "jewelry8", sti(pchar.questTemp.IslamonaChurch.Amber));
			DeleteAttribute(pchar, "questTemp.IslamonaChurch.Amber");
		}
	}
	if(CheckAttribute(pchar, "questTemp.IslamonaChurch.BlueAmber"))
	{
		int BlueAmb = sti(pchar.questTemp.IslamonaChurch.BlueAmber);
		if(GetCharacterItem(pchar, "jewelry7") < BlueAmb)
		{
			pchar.questTemp.IslamonaChurch.BlueAmber = sti(pchar.questTemp.IslamonaChurch.BlueAmber) - GetCharacterItem(pchar, "jewelry7");
			RemoveItems(pchar, "jewelry7", GetCharacterItem(pchar, "jewelry7"));
		}
		else
		{
			RemoveItems(pchar, "jewelry7", sti(pchar.questTemp.IslamonaChurch.BlueAmber));
			DeleteAttribute(pchar, "questTemp.IslamonaChurch.BlueAmber");
		}
	}
	PlaySound("interface\important_item.wav");
}

// Rebbebion, проверяем время, в которое зашли в дом Кэллоу
bool BlackMark_CheckTimeInGabeHouse()
{
	int iTime;
	
	iTime = sti(environment.time);
	
	if (iTime > 6 && iTime < 22) return false;
	
	return true;
}
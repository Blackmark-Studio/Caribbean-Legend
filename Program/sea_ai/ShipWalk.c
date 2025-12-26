object Sailors;

void Ship_Walk_Init()
{
	CreateEntity(&Sailors, "Sailors");

	SetEventHandler(SHIP_BORT_FIRE, "Ship_Walk_Bort_Fire", 0);
	SetEventHandler(SHIP_CREATE, "Ship_Walk_Create", 0);
	SetEventHandler(SHIP_HULL_HIT, "Ship_Walk_Hull_Damage", 0);
}

void Ship_Walk_Delete()
{
	DelEventHandler(SHIP_BORT_FIRE, "Ship_Walk_Bort_Fire");
	DelEventHandler(SHIP_CREATE, "Ship_Walk_Create");
	DelEventHandler(SHIP_HULL_HIT, "Ship_Walk_Hull_Damage");

	DeleteClass(&Sailors);
}

string sModelGroup[8] = {"LowCharacters/sold_eng_",	// солдаты англичане [0]
                         "LowCharacters/sold_fra_",	// солдаты французы [1]
                         "LowCharacters/sold_spa_",	// солдаты испанцы [2]
                         "LowCharacters/sold_hol_",	// солдаты голландцы [3]
                         "LowCharacters/pirate_",	// пираты [4]
                         "LowCharacters/trader_",	// торговцы [5]
                         "LowCharacters/skeleton_",	// скелеты [6]
                         "LowCharacters/man_"};		// обычные моряки [7]
	
void Ship_Walk_Create()
{
	int charIndex = GetEventData();
	aref ship = GetEventData();
	
	ref ch = GetCharacter(charIndex);

	if (!CheckAttribute(ch, "ship.type"))
	{
		trace("Ship_Walk_Create err: " + ch.id + " have invalid ship");
		return;
	}

	if(ch.id == "0" || sti(ch.ship.type) == SHIP_NOTUSED)
	{
		trace("Ship_Walk_Create err: " + ch.id + " have invalid ship");
		return;
	}

	int Index= sti(ch.ship.type);
	int ri= sti(RealShips[Index].basetype);

	if (!CheckAttribute(ch,"nation")) 
	{
		SendMessage(&Sailors, "lis", AI_MESSAGE_ADD_SHIP, ship, /*ShipsTypes[ri].name*/RealShips[Index].name); // дефолтные модели из движка
	}
	else
	{
		string sModel = sModelGroup[7]; // обычные моряки
		if (sti(ch.index) == nMainCharacterIndex)
		{
			if (isMainCharacterPatented()) sModel = sModelGroup[sti(ch.nation)];
		}
		else
		{
			if (RealShips[Index].Type.War == true) sModel = sModelGroup[sti(ch.nation)];
			if (RealShips[Index].Type.Merchant == true) sModel = sModelGroup[5]; // торговцы
		}
		if (ch.sex == "skeleton") 
		{
			sModel = sModelGroup[7];
		}
		string sModelRange[10];
		for (int i = 0; i < 10; i++) sModelRange[i] = sModel + (i+1); // выбор моделей
		SendMessage(&Sailors, "lise", AI_MESSAGE_ADD_SHIP, ship, RealShips[Index].name,&sModelRange); // выбор группы моделей
	}
}

void Ship_Walk_Hull_Damage()
{
	aref	rShipObject = GetEventData();

	int		iBallCharacterIndex = GetEventData();
	int		iOurCharacterIndex = GetEventData();

	ref		rBallCharacter = GetCharacter(iBallCharacterIndex);	
	ref		rCharacter = GetCharacter(iOurCharacterIndex);

	rCharacter.Ship.LastBallCharacter = iBallCharacterIndex;


	float	x = GetEventData();
	float	y = GetEventData();
	float	z = GetEventData();

	SendMessage(&Sailors, "lafff", MSG_PEOPLES_ON_SHIP_HULLHIT, rCharacter, x,y,z);
}

void Ship_Walk_Bort_Fire()
{
	aref	firedShip;
	string	bortName;

	ref rCharacter = GetCharacter(GetEventData());
	firedShip = GetEventData();
	bortName = GetEventData();

	SendMessage(&Sailors, "lis", AI_MESSAGE_CANNON_RELOAD, firedShip, bortName);
}
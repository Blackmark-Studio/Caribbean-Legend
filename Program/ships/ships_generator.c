


#define FLAG_SHIP_TYPE_WAR 1
#define FLAG_SHIP_TYPE_MERCHANT 2
//#define FLAG_SHIP_TYPE_SCOUT 4
#define FLAG_SHIP_TYPE_ANY 3

#define SHIP_TYPE_COUNT 2
int gShipTypeFlags[SHIP_TYPE_COUNT] = {1, 2}
string gTypeFields[SHIP_TYPE_COUNT] = {"War", "Merchant"};

#define FLAG_SHIP_CLASS_1  1
#define FLAG_SHIP_CLASS_2  2
#define FLAG_SHIP_CLASS_3  4
#define FLAG_SHIP_CLASS_4  8
#define FLAG_SHIP_CLASS_5 16
#define FLAG_SHIP_CLASS_6 32

int gShipClassFlags[7] = {0, 1, 2, 4, 8, 16, 32}

#define FLAG_SHIP_NATION_ENGLAND   1
#define FLAG_SHIP_NATION_FRANCE    2
#define FLAG_SHIP_NATION_SPAIN     4
#define FLAG_SHIP_NATION_HOLLAND   8
#define FLAG_SHIP_NATION_PIRATE   16
#define FLAG_SHIP_NATION_ANY      31





string gNationFields[MAX_NATIONS] = {"england", "france", "spain", "holland", "pirate"};
int gShipNationFlags[MAX_NATIONS] = {1, 2, 4, 8, 16}

int GetClassFlag(int class) {
	if (class > 6)
		return FLAG_SHIP_CLASS_6;
	if (class < 1)
		return FLAG_SHIP_CLASS_1;
	return gShipClassFlags[class];
	
}

int GetNationFlag(int nation) {
	if (nation >= MAX_NATIONS)
		nation = MAX_NATIONS - 1;
	if (nation < 0)
		nation = 0;
	return gShipNationFlags[nation];
	
}

// Usage: GetRandomShipType(FLAG_SHIP_CLASS_2 + FLAG_SHIP_CLASS_3 + FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ENGLAND + FLAG_SHIP_NATION_PIRATE)
// Gives random war or merchant, english or pirate ship with class 2 or 3 or 4
int GetRandomShipType(int classFlags, int typeFlags, int nationFlags) 
{
	int shipArr[2];
	SetArraySize(&shipArr, GetArraySize(&ShipsTypes));
	int shipArrScore[2];
	SetArraySize(&shipArrScore, GetArraySize(&ShipsTypes));
	
	int shipCount = 0;
	int shipTotalScore = 0;
	string sShipFlag;
	for (int i = 0; i < GetArraySize(&ShipsTypes); i++)
	{
		ref refShip;
		makeref(refShip,ShipsTypes[i]);
		if (CheckAttribute(refShip, "QuestShip"))
		{
			sShipFlag = refShip.QuestShip;
			if (sti(sShipFlag) == 1)
			{
				continue;
			}
		}
		
		if (CheckAttribute(refShip, "ShipHolder"))
		{
			sShipFlag = refShip.ShipHolder;
			if (sti(sShipFlag) == 1)
			{
				continue;
			}
		}
		
		if (CheckAttribute(refShip, "CanEncounter"))
		{
			sShipFlag = refShip.CanEncounter;
			if (sti(sShipFlag) == 0)
			{
				continue;
			}
		}

		
		if (!CheckAttribute(refShip, "Class"))
		{
			continue;
		}

		int class = sti(refShip.Class);

		if (!and(classFlags, gShipClassFlags[class]))
		{
			continue;
		}
		
		
		bool match = false;
		for (int j = 0; j < SHIP_TYPE_COUNT; j++)
		{
			string sType = gTypeFields[j];
			if (!CheckAttribute(refShip, "Type."+sType))
			{
				continue;
			}
			string sTypeFlag = refShip.Type.(sType);

			if (sti(sTypeFlag) == 1 && and(typeFlags, gShipTypeFlags[j]))
			{
				match = true;
				break;
			}
		}
		
		if (!match) 
		{
			continue;
		}
		
		match = false;
		for (int k = 0; k < MAX_NATIONS; k++)
		{
			
			string sNation = gNationFields[k];
			if (!CheckAttribute(refShip, "nation."+sNation))
			{
				continue;
			}
			string sNationFlag = refShip.nation.(sNation);
			if (sti(sNationFlag) == 1 && and(nationFlags, gShipNationFlags[k]) != 0)
			{
				match = true;
				break;
			}
		}
		
		if (!match) 
		{
			continue;
		}
		
		shipArr[shipCount] = i;
		
		//Здесь должна появиться некая "редкость типа корабля"
		//В массиве будет храниться накопительная редкость корабля.
		shipArrScore[shipCount] = shipTotalScore + 1; 
		shipTotalScore = shipTotalScore + 1;
		shipCount++;
	}

	if (shipCount == 0) 
	{
		return SHIP_NOTUSED;
	}
	
	//Генерируем рандомную стоимость, после чего будем искать ее в массиве shipArrScore
	//Если найденная стоимость попадает между shipArrScore[i - 1] и shipArrScore[i] - мы выбираем корабль i
	//Таким образом чем больше очков у корабля, тем выше вероятность его сгенерировать
	
	int searchScore = rand(shipArrScore[shipCount - 1])
	
	//Дальше двоичным поиском ищем по массиву shipArrScore, чтобы вместо n^2 поиск был бы n*log(n)
	
	int left = 0;
	int right = shipCount - 1;
	
	int shipIdx = SHIP_NOTUSED;
	while ((right - left) > 1)
	{
		int middle = (left + right) / 2;
		if (shipArrScore[middle] == searchScore)
		{
			return shipArr[middle];
		}
		if (shipArrScore[middle] < searchScore)
		{
			left = middle;
		}
		else
		{
			right = middle;
		}
	}
	
	
	//По итогу получаем что shipArrScore[left] меньше искомого, shipArrScore[right] - больше, но они соседние. Значит наш выбор - right.
	return shipArr[right];
}



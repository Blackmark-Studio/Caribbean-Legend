#define SHIP_LOC_HOLD "My_Deck"
#define SHIP_LOC_CAMPUS "My_Campus"
#define SHIP_LOC_GUNDECK "My_Deck_Medium"

/**
 * Заполнить массив локациями корабля, каюта, гандек, кают-компания...
 * @return `false` если у игрока сейчас нет каюты, иначе `true`
 */
bool _FillPlayerShipInsidesLocations(ref result)
{
	string cabinId = Get_My_Cabin();
	if (cabinId == "") return false;

	result = {cabinId, SHIP_LOC_HOLD, SHIP_LOC_CAMPUS, SHIP_LOC_GUNDECK};
	return true;
}

// belamour общая проверка количества дублонов у ГГ и в каюте
int PCharDublonsTotal()
{
	return PCharItemsTotal("gold_dublon");
}

// Получить общеее количество предмета в боксах в переданной локации
int CheckItemInAllBoxes(ref loc, string itemId, string boxAttributeName = "box", int boxesNum = 4)
{
	int qty = 0;
	aref box;

	for (int n = 1; n <= boxesNum; n++)
	{
		string boxId = boxAttributeName + n;
		makearef(box, loc.(boxId).items);
		int boxItemsQty = GetAttributesNum(box);
		for (int i = 0; i < boxItemsQty; i++)
		{
			aref boxItem = GetAttributeN(box, i);
			if (GetAttributeName(boxItem) != itemId) continue;

			qty += makeint(GetAttributeValue(boxItem));
		}
	}

	return qty;
}

// Забрать n предметов из боксов в переданной локации
int GetItemFromAllBoxes(ref loc, string itemId, int itemsToTakeQty, string boxAttributeName = "box", int boxesNum = 4)
{
	int itemsTaken = 0;

	for (int n = 1; n <= boxesNum; n++)
	{
		string boxId = boxAttributeName + n;
		if (!CheckAttribute(loc, boxId + ".items")) continue;

		aref box;
		makearef(box, loc.(boxId).items);
		int boxItemsQty = GetAttributesNum(box);

		for (int i = boxItemsQty-1; i >= 0; i--)
		{
			aref boxItem = GetAttributeN(box, i);
			if (GetAttributeName(boxItem) != itemId) continue;

			int inBoxQty = makeint(GetAttributeValue(boxItem));
			if (inBoxQty < 1) continue;

			if (inBoxQty > itemsToTakeQty) // в боксе достаточно предметов
			{
				itemsTaken += itemsToTakeQty;
				loc.(boxId).items.(itemId) = makeint(inBoxQty - itemsToTakeQty);
				return itemsTaken;
			}
			else // берём сколько есть
			{
				itemsTaken += inBoxQty;
				itemsToTakeQty -= inBoxQty;
				DeleteAttribute(loc, boxId + ".items." + itemId);
			}
		}
	}

	return itemsTaken;
}


// Получить общее кол-во предмета в сундуках на корабле игрока, перебирает последовательно каюту, гандек и т. д.
int CheckItemMyCabin(string itemId)
{
	int qty = 0;
	string shipLocations[];
	if (!_FillPlayerShipInsidesLocations(&shipLocations)) return 0;

	string boxAttributeName = "box";
	for (int i = 0; i < 4; i++)
	{
		int locationId = FindLocation(shipLocations[i]);
		if (locationId < 0) continue;

		if (i > 0) boxAttributeName = "private"; // костыль, в каюте box, в остальных помещениях private
		qty += CheckItemInAllBoxes(&locations[locationId], itemId, boxAttributeName, 4);
	}

	return qty;
}

// belamour положить предмет в сундук в КАЮТЕ!
void PutItemMyBox(string _Box, string _itemID, int _qty)
{
	int nShipType = GetCharacterShipType(pchar);
	if (nShipType == SHIP_NOTUSED)	return;
	if (Pchar.SystemInfo.CabinType != "")
	{
		ref loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)]; 
		if(CheckAttribute(loc,_Box+".items."+_itemID))
		{
			loc.(_Box).items.(_itemID) = makeint(sti(loc.(_Box).items.(_itemID)) + _qty);
		}
		else
		{
			loc.(_Box).items.(_itemID) = _qty;
		}
	}
} 

// belamour количество предмета в конкретном корабельном сундуке в КАЮТЕ!
int CheckItemMyBox(string _Box, string _itemID)
{
	int     i;	
	int		Qty = 0; 
    ref     loc;
	aref    arBox;
    aref    curItem;
	string  attr;

	int nShipType = GetCharacterShipType(pchar);
	if (nShipType == SHIP_NOTUSED)	return 0;
	if (Pchar.SystemInfo.CabinType != "")
	{
		loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)]; 			
		makearef(arBox, loc.(_Box).items);
		for(i=0; i<GetAttributesNum(arBox); i++)
		{
			curItem = GetAttributeN(arBox, i);
			attr = GetAttributeName(curItem);
			if (attr == _itemID)
			{
				Qty += makeint(GetAttributeValue(curItem));
			}
		}			
	}
	return Qty;
}

// belamour взять предмет из конкретного корабельного сундука, только из КАЮТЫ!
int GetItemMyBox(string _Box, string _itemID, int _qty)
{
	int     i;	
	int		Qty = 0; 
	int 	rQty = 0;	
    ref     loc;
	aref    arBox;
    aref    curItem;
	string  attr;
	
	int nShipType = GetCharacterShipType(pchar);
	if (nShipType == SHIP_NOTUSED)	return;
	if (Pchar.SystemInfo.CabinType != "")
	{
		loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)]; 			
		makearef(arBox, loc.(_Box).items);
		for(i=0; i<GetAttributesNum(arBox); i++)
		{
			curItem = GetAttributeN(arBox, i);
			attr = GetAttributeName(curItem);
			if (attr == _itemID)
			{
				Qty = makeint(GetAttributeValue(curItem));
				if(Qty > 0)
				{
					if(Qty > _qty) 
					{
						loc.(_Box).items.(attr) = makeint(sti(loc.(_Box).items.(attr)) - _qty);
						rQty += Qty;
						return rQty;
					}
					else
					{
						DeleteAttribute(loc, _Box + ".items." + attr);
						_qty -= Qty;
						rQty += Qty;
					}		
				}
			}
		}
		
	}
	return rQty;
}

// belamour взять дублоны сначала у ГГ, а потом из корабельных помещений
// Если дублонов недостаточно – ничего не произойдёт
void RemoveDublonsFromPCharTotal(int _Dublons)
{
	if (_Dublons < 1) return;
	if (PCharDublonsTotal() < _Dublons) return;

	RemoveItemsFromPCharTotal("gold_dublon", _Dublons);
	notification(StringFromKey("characterUtilite_9", _Dublons), "Dubloon"); //"Потрачено "+_Dublons+" дублонов"
	PlayStereoSound("Ambient\SHOP\dubloons.wav");
}

// Общая сумма предмета у игрока в карманах и корабельных помещениях
int PCharItemsTotal(string _itemID)
{
	return GetCharacterItem(pchar, _itemID) + CheckItemMyCabin(_itemID);
}

/** 
 * Забрать n предметов из карманов и с корабля игрока, перебирает последовательно карманы, каюту, гандек и т. д.
 * @param itemId id предмета
 * @param itemsToTakeQty кол-во, которое хотим забрать, должно быть > 0
 * 
 * Если предметов недостаточно – ничего не произойдёт
*/
void RemoveItemsFromPCharTotal(string itemId, int itemsToTakeQty)
{
	if(itemsToTakeQty<1) return;
	if(PCharItemsTotal(itemId) < itemsToTakeQty) return;
	int Total = itemsToTakeQty;
	int cq = GetCharacterItem(pchar,itemId);
	int bq = CheckItemMyCabin(itemId);
	if(cq > 0)
	{
		if(cq >= itemsToTakeQty)
		{
			TakeNItems(pchar,itemId, -itemsToTakeQty);
		}
		else
		{
			Total -= cq;
			TakeNItems(pchar,itemId, -cq);
			GetItemMyCabin(itemId, Total);
		}
	}
	else
	{
		GetItemMyCabin(itemId, itemsToTakeQty);
	}
}

/** 
 * Забрать n предметов с корабля игрока, перебирает последовательно каюту, гандек и т. д.
 * @param itemId id предмета
 * @param itemsToTakeQty кол-во, которое хотим забрать, должно быть > 0
 * @return количество забранных предметов, может быть меньше переданного, если в сундуках не хватило, тогда заберем всё, что нашли
*/
int GetItemMyCabin(string itemId, int itemsToTakeQty, bool withNotification = false)
{
	if (itemsToTakeQty < 0) return 0;

	int itemsTaken = 0;
	string shipLocations[];
	if (!_FillPlayerShipInsidesLocations(&shipLocations)) return 0; // нет каюты, а значит и корабля

	string boxAttributeName = "box";
	for (int i = 0; i < 4; i++)
	{
		int locationId = FindLocation(shipLocations[i]);
		if (locationId < 0) continue;

		if (i > 0) boxAttributeName = "private"; // костыль, в каюте box, в остальных помещениях private
		itemsTaken += GetItemFromAllBoxes(&locations[locationId], itemId, itemsToTakeQty, boxAttributeName, 4);
		itemsToTakeQty -= itemsTaken;
		if (itemsToTakeQty < 1) break;
	}

	if (withNotification) notification(StringFromKey("characterUtilite_5")+GetItemName(itemId), "BoxMinus");
	return itemsTaken;
}

// Добавить предмет на корабль игрока, число должно быть больше 0
void PutItemToShip(ref loc_id_or_Idx, string itemId, int qty, int boxIndex = 1)
{
	if (qty < 1) return;

	ref location = FindLocation_VT(loc_id_or_Idx);
	string shipLocations[];
	_FillPlayerShipInsidesLocations(&shipLocations);
	if (location == nullptr || ValueIsBad(&shipLocations, location.id))
	{
		trace("Error: bad location for ship item placement");
		return;
	}

	PutItemToLocationBox(loc_id_or_Idx, itemId, qty, boxIndex);
}

// Найти предмет на корабле игрока по функции-фильтру
ref FindItemOnShip(bool cabinOnly, string filterFunc)
{
	string shipLocations[];
	if (!_FillPlayerShipInsidesLocations(&shipLocations)) return nullptr; // нет каюты, а значит и корабля
	if (cabinOnly) SetArraySize(&shipLocations, 1);

	string boxAttributeName = "box";
	int j, n;
	for (int i = 0; i < 4; i++)
	{
		int locationIdx = FindLocation(shipLocations[i]);
		if (locationIdx < 0) continue;
		ref location = &Locations[locationIdx];

		if (i > 0) boxAttributeName = "private"; // костыль, в каюте box, в остальных помещениях private
		for (n = 1; n <= 4; n++)
		{
			string boxId = boxAttributeName + n;
			aref box = GetAref(location, boxId + ".items");
			if (box == nullptr) continue;

			int boxItemsQty = GetAttributesNum(box);
			for (j = 0; j < boxItemsQty; j++)
			{
				aref boxItem = GetAttributeN(box, j);
				if (int(GetAttributeValue(boxItem)) < 1) continue;

				ref item = ItemsFromID(GetAttributeName(boxItem));
				bool filterOk = call filterFunc(item);
				if (!filterOk) continue;

				return item;
			}
		}
	}

	return nullptr;
}

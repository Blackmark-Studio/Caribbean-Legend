void BRD_InitLooting()
{
	aref location = GetEventData();
	DelEventHandler("BRD_InitLooting", "BRD_InitLooting");
	if (CheckAttribute(location, "CabinType")) return;                   // в каюте не рыщем
	aref LootBox, boxes, resultBox;
	makearef(LootBox, location.LootBox);
	makearef(boxes, location.locators.box);

	// чистим коробку с прошлого раза
	DeleteAttribute(&LootBox, "items");
	DeleteAttribute(&LootBox, "money");

	// перебираем сундуки
	LootAllBoxes(&location, &boxes, &LootBox);

	// перебираем трупы
	LootAllCorpses(&LootBox);

	// складываем всё в первый сундук, вдруг случайно закроют окно, так спокойнее
	makearef(resultBox, location.box1);
	CopyAttributes(&resultBox, LootBox);
	LaunchLootingBox(&resultBox);

	// красивую меточку сверху
	QuestPointerToLoc(location.id, "box", "box1");
}

// обычное открытие сундука, просто немного перетираем интерфейс
void LaunchLootingBox(ref boxRef)
{
	LaunchItemsBox(boxRef);
	SetFormatedText("STORECAPTION", StringFromKey("boarding_7"));
	SetFormatedText("OTHER_TABLE_CAPTION", StringFromKey("boarding_8"));
}

void LootAllBoxes(ref location, ref boxes, ref LootBox){
	aref itemList, container;

	for (int i=0; i<GetAttributesNum(boxes); i++) 
	{
		string boxName = GetAttributeName(GetAttributeN(boxes, i));
		makearef(itemList, location.(boxName).items);
		makearef(container, location.(boxName));
		LootItemsFromContainer(&itemList, &LootBox, &container);
	}
}

void LootAllCorpses(ref LootBox)
{
	aref itemList;
	ref corpse, realChar;

	for (int i = 0; i < Dead_Char_num; i++)
	{
		corpse = &Dead_Characters[i];
		realChar = CharacterFromId(corpse.id);
		if (!CheckAttribute(corpse, "id") || CheckAttribute(&realChar, "CantLoot")) continue;

		makearef(itemList, corpse.items);
		LootItemsFromContainer(&itemList, &LootBox, corpse);
		DeleteAttribute(corpse, "items");
		DeleteAttribute(corpse, "money");
	}
}

// вещи из контейнера кладём в лутбокс, а в контейнере удаляем
void LootItemsFromContainer(ref Items, ref LootBox, ref container)
{
	aref item;

	for (int i=0; i<GetAttributesNum(Items); i++)
	{
		item = GetAttributeN(Items, i);
		string itemName = GetAttributeName(item);
		if (itemName == "" || itemName == "unarmed" ) continue;

		if (!CheckAttribute(&LootBox, "items." + itemName)) LootBox.items.(itemName) = 0;
		LootBox.items.(itemName) = makeint(sti(LootBox.items.(itemName)) + makeint(GetAttributeValue(item)));
	}

	if (CheckAttribute(container, "money")) {
		LootBox.money = sti(LootBox.money) + sti(container.money);
		DeleteAttribute(container, "money");
	}

	DeleteAttribute(container, "items");
}

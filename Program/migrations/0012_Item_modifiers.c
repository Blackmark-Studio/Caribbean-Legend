void ApplyMigration(ref migrationState) {

	PotionsRebalance();
	Log_TestInfo("Обновили зелья");

	// превращаем предметы в обереги
	// если экипировано - пусть остается, но надеть заново нельзя
	ref item;
	item = ItemsFromId("knife_01");
	item.groupID = TALISMAN_ITEM_TYPE;
	item = ItemsFromId("knife_02");
	item.groupID = TALISMAN_ITEM_TYPE;
	item = ItemsFromId("knife_03");
	item.groupID = TALISMAN_ITEM_TYPE;


	// Все амулеты, талисманы теперь длятся 50 дней
	item = ItemsFromId("indian_1");
	item.time = 50;
	item = ItemsFromId("indian_2");
	item.time = 50;
	item = ItemsFromId("indian_3");
	item.time = 50;
	item = ItemsFromId("indian_4");
	item.time = 50;
	item = ItemsFromId("indian_5");
	item.time = 50;
	item = ItemsFromId("indian_6");
	item.time = 50;
	item = ItemsFromId("indian_7");
	item.time = 50;
	item = ItemsFromId("indian_8");
	item.time = 50;
	item = ItemsFromId("indian_9");
	item.time = 50;
	item = ItemsFromId("indian_10");
	item.time = 50;
	item = ItemsFromId("indian_11");
	item.time = 50;
	item = ItemsFromId("amulet_1");
	item.time = 50;
	item = ItemsFromId("amulet_2");
	item.time = 50;
	item = ItemsFromId("amulet_3");
	item.time = 50;
	item = ItemsFromId("amulet_4");
	item.time = 50;
	item = ItemsFromId("amulet_5");
	item.time = 50;
	item = ItemsFromId("amulet_6");
	item.time = 50;
	item = ItemsFromId("amulet_7");
	item.time = 50;
	item = ItemsFromId("amulet_8");
	item.time = 50;
	item = ItemsFromId("amulet_9");
	item.time = 50;
	item = ItemsFromId("amulet_10");
	item.time = 50;
	item = ItemsFromId("amulet_11");
	item.time = 50;
	item = ItemsFromId("obereg_1");
	item.time = 50;
	item = ItemsFromId("obereg_2");
	item.time = 50;
	item = ItemsFromId("obereg_3");
	item.time = 50;
	item = ItemsFromId("obereg_4");
	item.time = 50;
	item = ItemsFromId("obereg_5");
	item.time = 50;
	item = ItemsFromId("obereg_6");
	item.time = 50;
	item = ItemsFromId("obereg_7");
	item.time = 50;
	item = ItemsFromId("obereg_8");
	item.time = 50;
	item = ItemsFromId("obereg_9");
	item.time = 50;
	item = ItemsFromId("obereg_10");
	item.time = 50;
	item = ItemsFromId("obereg_11");
	item.time = 50;
	item = ItemsFromId("rat_poison");
	item.time = 50;
	Log_TestInfo("Мигрировали вещи");

	DubloonsPrice();

	KukulklanStoleMyPerks();
}


void KukulklanStoleMyPerks()
{
	ref chr;
	object fellows = GetAllFellows(pchar, true);
	for (int i=0; i < GetAttributesNum(&fellows); i++)
	{
		int idx = sti(GetAttributeValue(GetAttributeN(&fellows, i)));
		chr = GetCharacter(idx);
		if (!IsFellowOurCrew(chr)) continue;
		if (!CheckAttribute(chr, "perks.list")) continue;
		RemoveAllPerksNoCash(chr);

		object temp;
		GEN_SummPerkPoints(chr, &temp);

		SetFreePerkPoints(chr, sti(temp.self), "self");
		SetFreePerkPoints(chr, sti(temp.ship), "ship");

		if (IsMainCharacter(chr))
		{
			SetCharacterPerkNoCash(chr, "FlagPir", false);
			SetCharacterPerkNoCash(chr, "Flag" + NationShortName(GetBaseHeroNation()), false);
		}
		else ForceHeroPerks(chr);

		CT_UpdateCashTables(chr);
	}
}

void PotionsRebalance()
{
	int i;
	ref itm;

	object tempItems[2];
	SetArraySize(&tempItems, TOTAL_ITEMS);
	
	for(i = 0; i < TOTAL_ITEMS; i++)
	{
		CopyAttributes(&tempItems[i], &Items[i]);
	}
	
	ExpandItemsArray();
	
	ITEMS_QUANTITY++;
	
	DeleteAttribute(&Items[ITEMS_QUANTITY - 1], "");
	InitAddItem(ITEMS_QUANTITY - 1);
	
	makeref(itm,Items[ITEMS_QUANTITY - 1]);
	itm.id = "recipe_potion1";
	itm.name = "itmname_recipe_potion1";
	itm.describe = "itmdescr_recipe_potion1";
	itm.result 		= "potion1";
	itm.groupID		= SPECIAL_ITEM_TYPE;
	itm.model		= "letter";
	itm.picTexture	= "ITEMS_26";
	itm.picIndex		= 16;
	itm.price		= 3500;
	itm.rare 		= 0.0001;
	itm.minlevel 	= 1;
	itm.Weight 		= 0.1;
	itm.ItemType 	= "SUPPORT";
	
	for(i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
	{
		DeleteAttribute(&Items[i], "");
		CopyAttributes(&Items[i], &tempItems[i - 1]);
		Items[i].index = i;
	}

	pchar.alchemy.recipe_potion1.isKnown = false;

	itm = ItemsFromId("potion5");
	itm.potion.health = 25;
	itm.potion.health.speed = 5;
	itm = ItemsFromId("potionrum");
	itm.potion.health = 45;
	itm.potion.health.speed = 5;
	itm = ItemsFromId("potionwine");
	itm.potion.health = 90;
	itm.potion.health.speed = 5;
	itm = ItemsFromId("potion1");
	itm.potion.health = 85;
	itm.potion.health.speed = 5;
	itm.multiobject = true;
	itm.multiobject.qty = 1;
	itm.multiobject.alchemy = true;
	InitMultiObjectCommon(itm,     "t1",     "potion5",    "Component",        1); // Имбирный корень
	InitMultiObjectCommon(itm,     "t2",     "potionrum",  "Component",        1); // Ром
	InitMultiObjectCommon(itm,     "t3",     "mineral27",  "AlchemyTool",      1); // Ступка с пестиком
	itm = ItemsFromId("potion2");
	itm.potion.health = 140;
	itm.potion.health.speed = 5;
	InitMultiObjectCommon(itm,	    "t1",     "cannabis1", 	  "Component", 	  1); // Дурман
	InitMultiObjectCommon(itm,	    "t2",     "cannabis2", 	  "Component", 	  1); // Сабадилла
	InitMultiObjectCommon(itm,	    "t3",       "potion1", 	  "Component", 	  1); // Лечебное зелье
	InitMultiObjectCommon(itm,	    "t4",     "mineral17", 	  "Component", 	  3); // Пустой флакончик
	InitMultiObjectCommon(itm,	    "t5",     "potionrum", 	  "Component", 	  1); // Бутылка рома
	InitMultiObjectCommon(itm,      "t6",     "mineral27",  "AlchemyTool", 	  1); // Ступка с пестиком
	InitMultiObjectCommon(itm,	    "t7",  "alchemy_tool",  "AlchemyTool", 	  1); // Алхимический набор
	
	itm = ItemsFromId("potion3");
	itm.potion.health = 35;
	itm.potion.health.speed = 5;
	itm = ItemsFromId("potion4");
	itm.potion.health = 185;
	itm.potion.health.speed = 5;
	InitMultiObjectCommon(itm,	    "t1",       "potion2", 	  "Component", 	  1); // Эликсир
	InitMultiObjectCommon(itm,	    "t2",     "potionwine", 	"Component", 	  1); // Вино
	InitMultiObjectCommon(itm,	    "t3",     "cannabis1", 	  "Component", 	  1); // Дурман
	InitMultiObjectCommon(itm,	    "t4",     "cannabis2", 	  "Component", 	  1); // Сабадилла
	InitMultiObjectCommon(itm,	    "t5",     "cannabis3", 	  "Component", 	  1); // Вербена
	InitMultiObjectCommon(itm,	    "t6",      "cannabis4",   "Component",    1); // Ипекакуана
	InitMultiObjectCommon(itm,	    "t7",      "cannabis5",   "Component",    1); // Гуарана
	InitMultiObjectCommon(itm,	    "t8",      "cannabis6",   "Component", 	  1); // Ямайский перец
	InitMultiObjectCommon(itm,	    "t9",     "mineral17", 	  "Component", 	  3); // Пустой флакончик
	InitMultiObjectCommon(itm,	    "t10",     "potion3", 	  "Component", 	  3); // Противоядие
	InitMultiObjectCommon(itm,	   "t11",  "alchemy_tool",  "AlchemyTool", 	  1); // Алхимический набор
	InitMultiObjectCommon(itm,     "t12",     "mineral27",  "AlchemyTool", 	  1); // Ступка с пестиком
}

void DubloonsPrice()
{
	ref item;
	
	item = ItemsFromId("gold_dublon");
	item.price = 500;
	DeleteAttribute(item, "fixedprice");
	
	item = ItemsFromId("Chest");
	item.price = 75000;
	DeleteAttribute(item, "fixedprice");
	
	item = ItemsFromId("jewelry1");
	item.PriceDublon = 2;
	item = ItemsFromId("jewelry2");
	item.PriceDublon = 4;
	item = ItemsFromId("jewelry3");
	item.PriceDublon = 3;
	item = ItemsFromId("jewelry4");
	item.PriceDublon = 2;
	item = ItemsFromId("jewelry5");
	item.PriceDublon = 1;
	item = ItemsFromId("jewelry6");
	item.PriceDublon = 1;
	item = ItemsFromId("jewelry7");
	item.PriceDublon = 8;
	item = ItemsFromId("jewelry8");
	item.PriceDublon = 2;
	item = ItemsFromId("jewelry9");
	item.PriceDublon = 1;
	item = ItemsFromId("jewelry10");
	item.PriceDublon = 1;
	item = ItemsFromId("jewelry11");
	item.PriceDublon = 7;
	item = ItemsFromId("jewelry12");
	item.PriceDublon = 1;
	item = ItemsFromId("jewelry13");
	item.PriceDublon = 1;
	item = ItemsFromId("jewelry14");
	item.PriceDublon = 2;
	item = ItemsFromId("jewelry15");
	item.PriceDublon = 1;
	item = ItemsFromId("jewelry16");
	item.PriceDublon = 2;
	item = ItemsFromId("jewelry17");
	item.PriceDublon = 1;
	item = ItemsFromId("jewelry18");
	item.PriceDublon = 1;
	item = ItemsFromId("jewelry19");
	item.price = 235;
	item.PriceDublon = 1;
	item = ItemsFromId("jewelry20");
	item.PriceDublon = 1;
	item = ItemsFromId("jewelry21");
	item.price = 380;
	item.PriceDublon = 2;
	item = ItemsFromId("jewelry22");
	item.price = 425;
	item.PriceDublon = 2;
	item = ItemsFromId("jewelry23");
	item.PriceDublon = 1;
}
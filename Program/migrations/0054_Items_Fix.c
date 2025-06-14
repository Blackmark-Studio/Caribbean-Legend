void ApplyMigration(ref migrationState) {
	
    // Шкура ягуара
    ref sld = ItemsFromID("KhaelRoa_item");
    sld.groupID = ITEM_SLOT_TYPE;
    sld.ItemType = "ARTEFACT";
    sld.Type = ITEM_AMULET;
    sld.time = 2;
    sld.price = 5000;
    sld.Weight = 10.0;

    DeleteAttribute(&Render, "T14.Special.KhaelRoa_item");
    DeleteAttribute(&Render, "T15.Special.KhaelRoa_item");
    DeleteAttribute(&Render, "SingleTreasure.KhaelRoa_item");

    // Сокровища
    sld = ItemsFromID("icollection");
    sld.name = "itmname_icollection";
	sld.describe = "itmdescr_icollection";

    sld = &Locations[FindLocation("SanAugustineResidence")];
    sld.private2.items.icollection = 3;
    DeleteAttribute(sld, "private2.items.incas_collection");

    sld = &Locations[FindLocation("VelascoShipInside1")];
    sld.private3.items.icollection = 3;
    DeleteAttribute(sld, "private3.items.incas_collection");
}

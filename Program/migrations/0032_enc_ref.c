
void ApplyMigration(ref migrationState)
{
	aref aEnc, aCurEnc, arTemp, arTemp2;
    makearef(aEnc, worldMap.encounters);
    int q = GetAttributesNum(aEnc);
    for (int i = 0; i < q; i++)
    {
        aCurEnc = GetAttributeN(aEnc, i);
        if (CheckAttribute(aCurEnc, "encdata.FixedTypes"))
        {
            makearef(arTemp,  aCurEnc.encdata.ShipTypes);
            makearef(arTemp2, aCurEnc.encdata.ShipModes);
            int j, q2 = GetAttributesNum(arTemp);
            for (j = 0; j < q2; j++)
            {
                string sTemp = "s" + j;
                aCurEnc.encdata.FixedShips.(sTemp).type = GetAttributeValue(GetAttributeN(arTemp,  j));
                aCurEnc.encdata.FixedShips.(sTemp).mode = GetAttributeValue(GetAttributeN(arTemp2, j));
            }
            DeleteAttribute(aCurEnc, "encdata.ShipTypes");
            DeleteAttribute(aCurEnc, "encdata.ShipModes");
            DeleteAttribute(aCurEnc, "encdata.FixedTypes");
        }
    }

    ref item;
    item = ItemsFromId("Vodka");
    item.time = 50;

    item = ItemsFromId("talisman17");
    item.kind = "doctor";
}

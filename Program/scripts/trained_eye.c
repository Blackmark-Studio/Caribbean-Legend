// Оцениваем трюм
void ShowShipCargoEstimateCost(ref spyglass, ref captain)
{
	if (!CheckOfficersPerkEnable("TrainedEye")) return;

	string typeName = GetConvertStr(GetShipSpecDesc(&captain), "ShipsPerksDescribe.txt");
	string traitName = GetShipTraitDesc(&captain);
	string curkUniqueStr = GetQuestBookDataDigit() + captain.Ship.Name;
	if (CheckAttribute(&spyglass, "checkUniqueStr") && spyglass.checkUniqueStr == curkUniqueStr)  return;

	int maxPoints = 50 * GetCargoMaxSpace(captain); // 50 –  условно среднее значение
	int sumPoints;
	for (int i=0; i<GOODS_QUANTITY; i++) sumPoints = sumPoints + GetCargoGoods(captain,i) * GetCargoPoints(i);

	string text;
	if (sumPoints > maxPoints) text = "perks_4";
	else text = "perks_5";

	text = DLGO(StringFromKey(text), captain);
	if (CheckOfficersPerkEnable("QuickGlance")) 
	{
		string traitPart;
		if (traitName == "") traitPart = "";
		else traitPart = GetConvertStr(traitName, "ShipsPerksDescribe.txt") + ", ";
		
		text = typeName + ", " + traitPart + LowerFirst(text);
	}
	Notification(text, "TrainedEye");

	spyglass.checkUniqueStr = curkUniqueStr;
}

int GetCargoPoints(string goodIdx)
{
	switch (goodIdx)
	{
		case GOOD_BALLS: return 2; break;
		case GOOD_GRAPES: return 1; break;
		case GOOD_KNIPPELS: return 1; break;
		case GOOD_BOMBS: return 10; break;
		case GOOD_FOOD: return 2; break;
		case GOOD_SAILCLOTH: return 30; break;
		case GOOD_PLANKS: return 50; break;
		case GOOD_BRICK: return 8; break;
		case GOOD_WHEAT: return 20; break;
		case GOOD_CLOTHES: return 2; break;
		case GOOD_FRUITS: return 20; break;
		case GOOD_COFFEE: return 200; break;
		case GOOD_CHOCOLATE: return 200; break;
		case GOOD_TOBACCO: return 200; break;
		case GOOD_SUGAR: return 200; break;
		case GOOD_COTTON: return 100; break;
		case GOOD_LEATHER: return 100; break;
		case GOOD_EBONY: return 500; break;
		case GOOD_MAHOGANY: return 400; break;
		case GOOD_CINNAMON: return 200; break;
		case GOOD_COPRA: return 200; break;
		case GOOD_PAPRIKA: return 100; break;
		case GOOD_POWDER: return 5; break;
		case GOOD_WEAPON: return 50; break;
		case GOOD_MEDICAMENT: return 4; break;
		case GOOD_WINE: return 350; break;
		case GOOD_RUM: return 100; break;
		case GOOD_ALE: return 200; break;
		case GOOD_SHIPSILK: return 3000; break;
		case GOOD_ROPES: return 3000; break;
		case GOOD_SANDAL: return 3000; break;
		case GOOD_OIL: return 3000; break;
		case GOOD_SLAVES: return 500; break;
		case GOOD_GOLD: return 800; break;
		case GOOD_SILVER: return 400; break;
		case GOOD_CANNON_3: return 80; break;
		case GOOD_CANNON_6: return 160; break;
		case GOOD_CANNON_8: return 240; break;
		case GOOD_CANNON_12: return 300; break;
		case GOOD_CANNON_16: return 450; break;
		case GOOD_CANNON_18: return 520; break;
		case GOOD_CANNON_20: return 600; break;
		case GOOD_CANNON_24: return 500; break;
		case GOOD_CANNON_32: return 1200; break;
		case GOOD_CANNON_36: return 2500; break;
		case GOOD_CANNON_42: return 4000; break;
		case GOOD_CULVERINE_8: return 250; break;
		case GOOD_CULVERINE_18: return 650; break;
		case GOOD_CULVERINE_36: return 2500; break;
		case GOOD_CANNON_48: return 4500; break;
	}

	return 0;
}

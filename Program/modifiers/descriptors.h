// Вместо констант, используется только в инитке предметов и для локализации
float DescriptorBaseValue(string descriptorName)
{
	switch (descriptorName)
	{
		case "Exotic":        return 0.07; break;
		case "HighQuality":   return 0.30; break;
		case "Fancy":         return 7.0;  break;
		case "Unremarkable":  return 7.0;  break;
		case "GoodFit":       return 0.07; break;
		case "HeartDefence":  return 0.16; break;
		case "Bayonet":       return 0.25; break;

		// Специальные
		case "MonsterGun":    return 20.0; break;
		case "IronsideArmor": return 0.15; break;
		case "LamportSuit":   return 0.13; break;
	}
}
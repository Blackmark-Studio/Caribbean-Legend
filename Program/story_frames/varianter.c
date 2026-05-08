#define RAND_NORMAL 0
#define RAND_TAG 1

void VRNTR_PickVariants(ref rObject, string variantsAttributeName, bool keepProbabilityAttributes = false)
{
	aref variants, variant;
	makearef(variants, rObject.(variantsAttributeName));
	string temp = "";
	int variantsQty = GetAttributesNum(variants);
	for (int i = 0; i < variantsQty; i++)
	{
		variant = GetAttributeN(variants, i);
		string varName = GetAttributeName(variant);
		int maxSeed = VRNTR_MaxSeed(&variant, GetAttributesNum(variant));
		int seed = _VRNTR_GetSeed(rObject, maxSeed);
		SetAttribute(variants, varName, VRNTR_PickVariant(rObject, variantsAttributeName + "." + varName, seed));
		SetAttribute(rObject, "debug." + varName + "-seed", seed + " / " + maxSeed);
	}
}

// Суммируем все вероятности вариантов
int VRNTR_MaxSeed(ref variants, int variantsQty)
{
	int summ = -1;
	for (int i = 0; i < variantsQty; i++)
	{
		summ += sti(GetAttributeValue(GetAttributeN(variants, i)));
	}
	return summ;
}

//JOKERTODO тут доделать вариации рандома и обкомментировать весь модуль
int _VRNTR_GetSeed(ref rObject, int maxSeed)
{
	int seed;
	int mode = GetAttributeInt(rObject, "random.mode");
	switch (mode)
	{
		case RAND_NORMAL: return rand(maxSeed); break;
		case RAND_TAG: return DateRandom(maxSeed, rObject.random.tag); break;
	}
}

string VRNTR_PickVariant(ref rObject, string variantsAttributeName, int seed)
{
	aref variant;
	aref variants;
	makearef(variants, rObject.(variantsAttributeName));

	int temp = 0;
	string resultVariantName;
	int variantsQty = GetAttributesNum(variants);
	if (variantsQty == 0)
	{
		resultVariantName = GetAttributeName(variants);
		SetAttribute(rObject, variantsAttributeName, resultVariantName);
		return resultVariantName;
	}

	for (int i = 0; i < variantsQty; i++)
	{
		variant = GetAttributeN(variants, i);
		int chance = sti(GetAttributeValue(variant));
		chance += temp;
		if (seed < chance)
		{
			resultVariantName = GetAttributeName(variant);
			break;
		}
		temp += chance;
	}

	variantsQty = GetAttributesNum(variant);
	if (variantsQty > 0)
	{
		int maxSeed = VRNTR_MaxSeed(&variant, variantsQty);
		seed = _VRNTR_GetSeed(rObject, maxSeed);
		resultVariantName += "_" + VRNTR_PickVariant(rObject, variantsAttributeName + "." + resultVariantName, seed); // есть подварианты
		SetAttribute(rObject, "debug." + resultVariantName + "-seed", seed + " / " + maxSeed);
	}

	SetAttribute(rObject, variantsAttributeName, resultVariantName);

	return resultVariantName;
}

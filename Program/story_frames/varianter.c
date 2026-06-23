#define RAND_NORMAL 0
#define RAND_TAG 1

// Выбираем один из вариантов, перечисленных в атрибутах как «имя = вероятность», у каждого варианта могут быть подварианты
void VRNTR_PickVariants(ref rObject, string variantsAttributeName)
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
		SetAttribute(&variants, varName, VRNTR_PickVariant(rObject, variantsAttributeName + "." + varName, seed));
		SetAttribute(rObject, "debug." + varName + "-seed", seed + " / " + maxSeed);
	}
}

// Суммируем все вероятности вариантов
int VRNTR_MaxSeed(ref variants, int variantsQty)
{
	int summ = -1;
	for (int i = 0; i < variantsQty; i++)
	{
		summ += int(GetAttributeValue(GetAttributeN(variants, i)));
	}
	return summ;
}

// Бросок вероятности для выбора варианта выполняется либо случайно, либо привязан к дате
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

/* Рекурсивная функция для перебора атрибутов и их атрибутов
@param seed изначальный бросок от 0 до суммы вероятностей всех вариантов
Если вероятность варианта выше значения броска → выпадает этот вариант. Иначе к броску добавляется вероятность первого варианта
и проверяется второй так далее.
*/
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
		int chance = int(GetAttributeValue(variant));
		if (seed < chance+temp)
		{
			resultVariantName = GetAttributeName(variant);
			break;
		}
		temp += chance;
	}

	// если есть подварианты, рекурсивно пробегаемся и по ним тоже
	variantsQty = GetAttributesNum(variant);
	if (variantsQty > 0)
	{
		int maxSeed = VRNTR_MaxSeed(&variant, variantsQty);
		seed = _VRNTR_GetSeed(rObject, maxSeed);
		resultVariantName += "_" + VRNTR_PickVariant(rObject, variantsAttributeName + "." + resultVariantName, seed);
		SetAttribute(rObject, "debug." + resultVariantName + "-seed", seed + " / " + maxSeed);
	}

	SetAttribute(rObject, variantsAttributeName, resultVariantName);

	return resultVariantName;
}

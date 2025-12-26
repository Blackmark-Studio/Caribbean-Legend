#define RAND_NORMAL 0
#define RAND_TAG 1

void VRNTR_PickVariants(ref rObject, string variantsAttributeName)
{
	aref variants, variant;
	makearef(variants, rObject.(variantsAttributeName));
	string temp = "";
	int variantsNum = GetAttributesNum(variants);
	for (int i = 0; i < variantsNum; i++)
	{
		variant = GetAttributeN(variants, i);
		string varName = GetAttributeName(variant);
		SetAttribute(variants, varName, VRNTR_PickVariant(rObject, variantsAttributeName + "." + varName, _VRNTR_GetSeed(rObject)));
	}
}

//JOKERTODO тут доделать вариации рандома и обкомментировать весь модуль
int _VRNTR_GetSeed(ref rObject)
{
	int seed;
	int mode = GetAttributeInt(rObject, "random.mode");
	switch (mode)
	{
		case RAND_NORMAL: return rand(99); break;
		case RAND_TAG: return DateRandom(99, rObject.random.tag); break;
	}
}

string VRNTR_PickVariant(ref rObject, string variantsAttributeName, int seed)
{
	aref variant;
	aref variants;
	makearef(variants, rObject.(variantsAttributeName));

	int temp = 0;
	string resultVariantName;
	int variantNums = GetAttributesNum(variants);
	if (variantNums == 0)
	{
		resultVariantName = GetAttributeName(variants);
		SetAttribute(rObject, variantsAttributeName, resultVariantName);
		return resultVariantName;
	}

	for (int i = 0; i < variantNums; i++)
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

	if (GetAttributesNum(variant) > 0)
	{
		seed = _VRNTR_GetSeed(rObject);
		resultVariantName += "_" + VRNTR_PickVariant(rObject, variantsAttributeName + "." + resultVariantName, seed); // есть подварианты
	}

	SetAttribute(rObject, variantsAttributeName, resultVariantName);

	return resultVariantName;
}

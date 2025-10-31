#define SPYGLASS_BAD_BASE 0.06          // базовый +- разброос для базы
#define SPYGLASS_BAD_RANDOM 0.14        // дополнительный случайный разброос для базы
#define SPYGLASS_BAD_OFFSET_BASE 0.03   // базовый разброос для мин/макс значений
#define SPYGLASS_BAD_OFFSET_RANDOM 0.07 // дополнительный случайный разброс для мин/макс значений

#define SPYGLASS_NORMAL_BASE 0.03
#define SPYGLASS_NORMAL_RANDOM 0.09
#define SPYGLASS_NORMAL_OFFSET_BASE 0.04
#define SPYGLASS_NORMAL_OFFSET_RANDOM 0.03

string SPGL_GetAproximateCrewQuantity(ref chr, ref spyglass)
{
	int realQty = GetCrewQuantity(chr);
	int glassLevel = 0;
	float sumMtp, minMtp, maxMtp;
	if (IsCompanion(chr)) return its(realQty);

	if (HasDescriptor(spyglass, "SpyGlass_Crew_0")) glassLevel = 1;
	else if (HasDescriptor(spyglass, "SpyGlass_Crew_1")) glassLevel = 2;
	else if (HasDescriptor(spyglass, "SpyGlass_Crew_2")) return its(realQty);
	else return "";

	if (realQty > 999) return "1k - 2k";

	aref cash;
	string chrId = chr.id;
	makearef(cash, TEV.localMapCash.(chrId).spyglass);

	if (CheckAttributeEqualTo(cash, "checkSum", realQty + "/" + glassLevel))
	{
		return cash.result;
	}
	else if (CheckAttributeEqualTo(cash, "glassLevel", its(glassLevel)))
	{
		sumMtp = stf(cash.sumMtp);
		minMtp = stf(cash.minMtp);
		maxMtp = stf(cash.maxMtp);
	}
	else
	{
		SPGL_SetAproximateMtps(glassLevel, &sumMtp, &minMtp, &maxMtp);
		if (PercentChance(50)) sumMtp = -sumMtp;

		cash.sumMtp = sumMtp;
		cash.glassLevel = glassLevel;
		cash.checkSum = realQty + "/" + glassLevel;
		cash.minMtp = minMtp;
		cash.maxMtp = maxMtp;
	}

	float tempQty = makefloat(realQty) * (1.0 + sumMtp);
	int min = makeint(tempQty * (1.0 - minMtp));
	int max = makeint(0.5 + tempQty * (1.0 + maxMtp));
	string result;
	if (min < 1) result = "1";
	else if (min != max) result = min + " - " + max;
	else result = min; // для всяких 1-1, 2-2

	cash.result = result;
	return result;
}

void SPGL_SetAproximateMtps(int glassLevel, ref sumMtp, ref minMtp, ref maxMtp)
{
	if (glassLevel == 1)
	{
		sumMtp = SPYGLASS_BAD_BASE        + frandSmall(SPYGLASS_BAD_RANDOM);
		minMtp = SPYGLASS_BAD_OFFSET_BASE + frandSmall(SPYGLASS_BAD_OFFSET_RANDOM);
		maxMtp = SPYGLASS_BAD_OFFSET_BASE + frandSmall(SPYGLASS_BAD_OFFSET_RANDOM);
		return;
	}

	sumMtp = SPYGLASS_NORMAL_BASE        + frandSmall(SPYGLASS_NORMAL_RANDOM);
	minMtp = SPYGLASS_NORMAL_OFFSET_BASE + frandSmall(SPYGLASS_NORMAL_OFFSET_RANDOM);
	maxMtp = SPYGLASS_NORMAL_OFFSET_BASE + frandSmall(SPYGLASS_NORMAL_OFFSET_RANDOM);
}
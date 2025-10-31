#define VO_TYPE_OFFSET_SKILLS 0.18 // сдвиг в среднем скилле от типа фантома, 0.1=10%

// Выдать персонажу-капитану виртуальных офицеров на корабельные должности
void GiveCaptainOfficers(ref chr, bool upNavy)
{
	RemoveChrModifier(chr, "officer");
	chr.personality.hasCrew = true;

	if (CheckAttributeEqualTo(chr, "personality.upNavy", "1")) upNavy = true;
	else chr.personality.upNavy = upNavy;

	int shipClass = GetCharacterShipClass(chr);
	if (shipClass > 6) return; // офицеров не будет на лодках

	// накинем до 20% от харизмы потому что можем
	float score = GetSkillSum(chr) / 16;
	score *= Bring2Range(1.0, 1.2, 1.0, 100.0, makefloat(GetSkillWithEffects(chr, SKILL_LEADERSHIP)));

	int goodScore = makeint(score * (1+VO_TYPE_OFFSET_SKILLS));
	int perkPoints = makeint(score / 7);
	int goodPerkPoints = makeint(goodScore / 7);
	int badScore = makeint(score * (1-VO_TYPE_OFFSET_SKILLS));
	int badPerkPoints = makeint(badScore / 7);
	GiveCaptainVirtualOfficerNoCash(chr, perkPoints, score, JOB_NAVIGATOR);

	string phantomType = GetAttributeOrDefault(chr, "PhantomType", "none");

	switch (phantomType)
	{
		case "marginal":
		{
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, badScore, JOB_NAVIGATOR);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, goodScore, JOB_CANNONER);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, goodScore, JOB_BOATSWAIN);
			GiveCaptainVirtualOfficerNoCash(chr, perkPoints, badScore, JOB_DOCTOR);
			GiveCaptainVirtualOfficerNoCash(chr, perkPoints, goodScore, JOB_CARPENTER);
			GiveCaptainVirtualOfficerNoCash(chr, badPerkPoints, badScore, JOB_TREASURER);
		}
		break;
		case "hunter":
		{
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, goodScore, JOB_NAVIGATOR);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, goodScore, JOB_CANNONER);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, goodScore, JOB_BOATSWAIN);
			GiveCaptainVirtualOfficerNoCash(chr, perkPoints, badScore, JOB_DOCTOR);
			GiveCaptainVirtualOfficerNoCash(chr, perkPoints, goodScore, JOB_CARPENTER);
			GiveCaptainVirtualOfficerNoCash(chr, badPerkPoints, badScore, JOB_TREASURER);
		}
		break;
		case "pirate":
		{
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, score, JOB_NAVIGATOR);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, goodScore, JOB_CANNONER);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, goodScore, JOB_BOATSWAIN);
			GiveCaptainVirtualOfficerNoCash(chr, perkPoints, badScore, JOB_DOCTOR);
			GiveCaptainVirtualOfficerNoCash(chr, perkPoints, goodScore, JOB_CARPENTER);
			GiveCaptainVirtualOfficerNoCash(chr, badPerkPoints, badScore, JOB_TREASURER);
		}
		break;
		case "citizen":
		{
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, score, JOB_NAVIGATOR);
			GiveCaptainVirtualOfficerNoCash(chr, badPerkPoints, badScore, JOB_CANNONER);
			GiveCaptainVirtualOfficerNoCash(chr, badPerkPoints, badScore, JOB_BOATSWAIN);
			GiveCaptainVirtualOfficerNoCash(chr, badPerkPoints, score, JOB_DOCTOR);
			GiveCaptainVirtualOfficerNoCash(chr, perkPoints, score, JOB_CARPENTER);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, goodScore, JOB_TREASURER);
		}
		break;
		case "officer":
		{
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, goodScore, JOB_NAVIGATOR);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, goodScore, JOB_CANNONER);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, goodScore, JOB_BOATSWAIN);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, badScore, JOB_DOCTOR);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, badScore, JOB_CARPENTER);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, badScore, JOB_TREASURER);
		}
		break;
		case "soldier":
		{
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, goodScore, JOB_NAVIGATOR);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, goodScore, JOB_CANNONER);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, goodScore, JOB_BOATSWAIN);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, badScore, JOB_DOCTOR);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, badScore, JOB_CARPENTER);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, badScore, JOB_TREASURER);
		}
		break;
		case "quest":
		{
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, goodScore, JOB_NAVIGATOR);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, goodScore, JOB_CANNONER);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, goodScore, JOB_BOATSWAIN);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, badScore, JOB_DOCTOR);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, badScore, JOB_CARPENTER);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, badScore, JOB_TREASURER);
		}
		break;
		case "governor":
		{
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, goodScore, JOB_NAVIGATOR);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, goodScore, JOB_CANNONER);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, goodScore, JOB_BOATSWAIN);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, badScore, JOB_DOCTOR);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, badScore, JOB_CARPENTER);
			GiveCaptainVirtualOfficerNoCash(chr, goodPerkPoints, badScore, JOB_TREASURER);
		}
		break;
	}

	if (upNavy)
	{
		int needSkill = GetShipClassNavySkill(shipClass);
		GiveCaptainVirtualOfficerSkill(chr, SKILL_SAILING, score, needSkill+rand(5));
	}


	GiveNationFlagPerk(chr);
	if (shipClass < 5) SetCharacterPerkWithRequiredNoCash(chr, "Captain");
	CT_UpdateCashTables(chr);
}

void GiveNationFlagPerk(ref chr)
{
	switch (GetAttributeIntOrDefault(chr, "nation", PIRATE))
	{
		case ENGLAND: SetCharacterPerkNoCash(chr, "FlagEng", false); break;
		case FRANCE: SetCharacterPerkNoCash(chr, "FlagFra", false); break;
		case SPAIN: SetCharacterPerkNoCash(chr, "FlagSpa", false); break;
		case HOLLAND: SetCharacterPerkNoCash(chr, "FlagHol", false); break;
		case PIRATE: SetCharacterPerkNoCash(chr, "FlagPir", false); break;
	}
}

void GiveCaptainVirtualOfficerNoCash(ref chr, int perkPoints, int score, string job)
{
	string skillName = GetSkillNameByJob(job);
	RemoveCaptainVirtualOfficersPerksNoCash(chr, job);
	GiveCaptainVirtualOfficerSkill(chr, skillName, score, -1);
	if (job == JOB_CANNONER) GiveCaptainVirtualOfficerSkill(chr, SKILL_CANNONS, score, -1); // исключение для канонира, там 2 скилла

	object perksTemplate;
	perksTemplate.seed = rand(2);
	FillPersonTemplate(&perksTemplate, job);
	aref perksList;
	makearef(perksList, perksTemplate.list);

	object chrPerks;
	int counter = 0;

	while (counter < 20)
	{
		if (perkPoints < 1) break;
		if (GetAttributesNum(&perksList) < 1) break;

		string perkName = GetAttributeName(GetAttributeN(&perksList, 0));
		string resultPerkName = GetPerkOrRequired(&chrPerks, perkName);
		int cost = GetPerkPrice(resultPerkName);
		if (cost > perkPoints) break;

		perkPoints -= cost;
		DeleteAttribute(&perksList, resultPerkName);
		chrPerks.(resultPerkName) = true;
		SetCharacterPerkFromOfficer(chr, resultPerkName, true);
		counter++;
	}
}

void GiveCaptainVirtualOfficer(ref chr, int perkPoints, int score, string job)
{
	GiveCaptainVirtualOfficerNoCash(chr, perkPoints, score, job);
	CT_UpdateCashTables(chr);
}

void GiveCaptainVirtualOfficerSkill(ref chr, string skillName, int score, int fixScore)
{
	int currentValue = sti(chr.skill.(skillName));
	int tempScore;
	if (fixScore > 0) tempScore = fixScore;
	// else tempScore = iClamp(1, 100, makeint(score + rand(GEN_CHAOS_VALUE) * 2 - rand(GEN_CHAOS_VALUE) * 2 - rand(GEN_CHAOS_VALUE) * 2));
	else tempScore = iClamp(1, 100, makeint(makefloat(score) * (0.9+fRandSmall(0.20))));
	if (currentValue < tempScore) SetChrModifier(chr, SKILL_TYPE + skillName, tempScore-currentValue, "officer");
}

void RemoveCaptainVirtualOfficersPerksNoCash(ref chr, string job)
{
	aref perks, perk;
	makearef(perks, chr.perks.list);

	for (int i=GetAttributesNum(perks)-1; i > -1; i--)
	{
		aref charPerk = GetAttributeN(perks, i);
		string perkName = GetAttributeName(charPerk);
		if (!CheckAttribute(charPerk, "fromOfficer")) continue;
		if (GetPerkJob(perkName) != job) continue;

		DelCharacterPerkNoCash(chr, perkName);
	}
}

void RemoveCaptainOfficers(ref chr)
{
	RemoveChrModifier(chr, "officer");
	DeleteAttribute(chr, "personality.HasCrew");
	aref perks, perk;
	makearef(perks, chr.perks.list);
	for (int i=GetAttributesNum(perks)-1; i > -1; i--)
	{
		aref charPerk = GetAttributeN(perks, i);
		string perkName = GetAttributeName(charPerk);
		if (!CheckAttribute(charPerk, "fromOfficer")) continue;

		DelCharacterPerkNoCash(chr, perkName);
	}

	CT_UpdateCashTables(chr);
}
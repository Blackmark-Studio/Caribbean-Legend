#include "characters\RPG\_old_alias.c"

// Получить базовый уровень скилла без бонусов
int GetSkillBase(ref chr, string skillName)
{
	return GetAttributeInt(chr, SKILL_TYPE + "." + skillName);
}

// Получить уровень скилла со шмотками и эффектами, но без офицеров и штрафа от навигации
int GetSkillWithEffects(ref chr, string skillName)
{
	if (!LAi_IsArmed(chr)) return GetSkillBase(chr, &skillName);

	int skillValue;
	if (!CheckAttribute(chr, "ct." + CT_COMMON + "." + skillName)) CT_UpdateCommonTable(chr);
	if (IsMainCharacter(chr) && isShipTypeSkill(&skillName)) 
	{
		skillValue = CT_GetInt(chr, CT_COMMON, "officer.backup." + skillName);
	}
	else skillValue = CT_GetInt(chr, CT_COMMON, &skillName);

	skillValue += GetStatusIntValue(chr, &skillName);
	return iClamp(1, SKILL_MAX, skillValue);
}

// Получить уровень скилла с учётом офицеров
int GetSkillWithOfficer(ref chr, string skillName)
{
	if (!CheckAttribute(chr, "ct." + CT_COMMON + "." + skillName)) CT_UpdateCommonTable(chr);
	int skillValue = CT_GetInt(chr, CT_COMMON, &skillName) + GetStatusIntValue(chr, &skillName);
	return iClamp(1, SKILL_MAX, skillValue);
}

// Получить уровень скилла с учётом офицеров и штрафом от навигации
int GetSkillAfterPenalty(ref chr, string skillName)
{
	if (!LAi_IsArmed(chr)) return GetSkillBase(chr, &skillName);

	int skillValue = GetSkillWithOfficer(chr, &skillName);
	skillValue -= GetAttributeInt(chr, "ct.com.navyPenaltySkill");
	return iClamp(1, SKILL_MAX, skillValue);
}

void SetSelfSkill(ref _refCharacter, int _fl, int _f, int _fh, int _p, int _fr)
{
	_refCharacter.Skill.FencingL      = _fl;
	_refCharacter.Skill.FencingS      = _f;
	_refCharacter.Skill.FencingH      = _fh;
	_refCharacter.Skill.Pistol        = _p;
	_refCharacter.Skill.Fortune       = _fr;
//	_refCharacter.Skill.Leadership = _ld;
//	_refCharacter.Skill.Sneak      = _sn;
}

void SetShipSkill(ref _refCharacter, int _ld, int _cr, int _ac, int _cn, int _sl, int _re, int _gr, int _de, int _sn)
{
	_refCharacter.Skill.Leadership = _ld;
	_refCharacter.Skill.Commerce   = _cr;
	_refCharacter.Skill.Accuracy   = _ac;
	_refCharacter.Skill.Cannons    = _cn;
	_refCharacter.Skill.Sailing    = _sl;
	_refCharacter.Skill.Repair     = _re;
	_refCharacter.Skill.Grappling  = _gr;
	_refCharacter.Skill.Defence    = _de;
	_refCharacter.Skill.Sneak      = _sn;
}

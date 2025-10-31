
void HideSkillChanger()
{
	SetNodeUsing("B_SKILLUP", false);
	SetNodeUsing("B_SKILLDown", false);
}

void IncreaseSkill(int _add)
{
	int iValue;
	string sSkillName;

	sSkillName = GameInterface.(CurTable).(CurRow).UserData.ID;
	if (CurTable != "TABLE_SPECIAL")
	{
		if (sti(xi_refCharacter.skill.freeskill) < _add)
			_add = sti(xi_refCharacter.skill.freeskill);
		if ((GetSkillValue(xi_refCharacter, SKILL_TYPE, sSkillName) + _add) > SKILL_MAX)
		{
			_add = SKILL_MAX - GetSkillValue(xi_refCharacter, SKILL_TYPE, sSkillName);
		}
		if (_add > 0)
		{
			iValue = AddCharacterSkill(xi_refCharacter, sSkillName, _add);
			xi_refCharacter.skill.freeskill = sti(xi_refCharacter.skill.freeskill) - _add;
		}
		else
			return;
	}
	else
	{
		if (sti(xi_refCharacter.skill.FreeSPECIAL) < _add)
			_add = sti(xi_refCharacter.skill.FreeSPECIAL);
		if ((GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName) + _add) > SPECIAL_MAX)
		{
			_add = SPECIAL_MAX - GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName);
		}
		if (_add > 0)
		{
			iValue = AddSPECIALValue(xi_refCharacter, sSkillName, _add);
			xi_refCharacter.skill.FreeSPECIAL = sti(xi_refCharacter.skill.FreeSPECIAL) - _add;
		}
		else
			return;
	}
	CT_UpdateCashTables(xi_refCharacter);
	SetEnergyToCharacter(xi_refCharacter);
	int hp;
	hp = LAi_GetCharacterMaxHP(xi_refCharacter);
	LAi_SetHP(xi_refCharacter, hp, hp);
	LAi_SetCurHPMax(xi_refCharacter);
	SetVariable();
	SetSkillArrows();
}

void DecreaseSkill(int _add)
{
	int iValue;
	string sSkillName;

	sSkillName = GameInterface.(CurTable).(CurRow).UserData.ID;
	if (CurTable != "TABLE_SPECIAL")
	{
		if (GetSkillValue(xi_refCharacter, SKILL_TYPE, sSkillName) <= _add)
		{
			_add = GetSkillValue(xi_refCharacter, SKILL_TYPE, sSkillName) - 1;
		}
		if (_add > 0)
		{
			iValue = AddCharacterSkill(xi_refCharacter, sSkillName, -_add);
			xi_refCharacter.skill.freeskill = sti(xi_refCharacter.skill.freeskill) + _add;
		}
		else
			return;
	}
	else
	{
		if (GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName) <= _add)
		{
			_add = GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName) - 1;
		}
		if ((GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName) - _add) < 3)
		{
			_add = GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName) - 3;
		}
		if (_add > 0)
		{
			iValue = AddSPECIALValue(xi_refCharacter, sSkillName, -_add);
			xi_refCharacter.skill.FreeSPECIAL = sti(xi_refCharacter.skill.FreeSPECIAL) + _add;
		}
		else
			return;
	}
	CT_UpdateCashTables(xi_refCharacter);
	SetEnergyToCharacter(xi_refCharacter);
	int hp;
	hp = LAi_GetCharacterMaxHP(xi_refCharacter);
	LAi_SetHP(xi_refCharacter, hp, hp);
	LAi_SetCurHPMax(xi_refCharacter);
	SetVariable();
	SetSkillArrows();
}

void SetSkillsTooltip(string sCurrentNode, string header, string text, string badText, string goodText, string sRow)
{
	cashTable = CT_GetTableOrInit(xi_refCharacter, CT_COMMON);
	string skillType = "";
	switch (sCurrentNode)
	{
		case "TABLE_SPECIAL": skillType = "Special"; break;
		case "TABLE_SKILL_1": skillType = "Skill"; break;
		case "TABLE_SKILL_2": skillType = "Skill"; break;
	}
	if (skillType == "") return;
	if (!CheckAttribute(&GameInterface, sCurrentNode + "." + sRow + ".UserData.ID")) return;

	string skillName = GameInterface.(sCurrentNode).(sRow).UserData.ID;
	header = XI_ConvertString(skillName);
	aref skillAttribute;
	makearef(skillAttribute, cashTable.(skillName));
	GetStatusIntWithInfo(xi_refCharacter, skillName, &skillAttribute, true); // добавляем эффекты статусов

	int lngFileID = LanguageOpenFile("RPGDescribe.txt");
	text = LanguageConvertString(lngFileID, skillName) + newStr() + " " +  newStr() + " " +  newStr();

	for (int i=0; i < GetAttributesNum(skillAttribute); i++)
	{
		aref row = GetAttributeN(skillAttribute, i);
		string reasonName = GetAttributeName(row);
		string reasonValue = GetAttributeValue(row);
		int value = sti(reasonValue);

		string humanReason = newStr() + GetHumanReadableReason(reasonName, xi_refCharacter) + ": " + ToHumanNumber(reasonValue);
		if (reasonName == "base") text += humanReason;
		else if (value > 0) goodText += humanReason;
		else if (value < 0) badText += humanReason;
	}

	string navyAttribute = "navypenalty"+skillType;
	if (GetAttributeInt(&cashTable, navyAttribute) > 0)
	{
		badText += newStr() + LanguageConvertString(lngFileID, "SourceNavyPenalty") + ": " + cashTable.(navyAttribute);
	}

	LanguageCloseFile(lngFileID);
}

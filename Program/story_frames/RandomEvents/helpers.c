// Отметить, что ивент произошёл, установить задержку в днях на следующий раз
void RE_SetEventDelay(int delay)
{
	string storyName = storyObject.name;
	Log_TestInfo("Следующее событие " + storyName + " возможно через " + delay + " дней");
	SetAttribute(&RandEventSystem, "recentEvents." + storyName, TMSTD_Timestamp(delay));
}

void SF_LearnSkillsFromOfficer(ref officer, float value)
{
	string jobName = GetMainJob(officer);
	if (jobName == JOB_FIGHTER)
	{
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_F_HEAVY, value * 0.25);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_FENCING, value * 0.25);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_F_LIGHT, value * 0.25);
		SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_PISTOL, value * 0.25);
	}
	else
	{
		string skillname = GetSkillNameByJob(jobName);
		if (jobName == JOB_CANNONER)
		{
			SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_CANNONS, value * 0.5);
			SF_AddEffect(SF_E_SKILL_EXP, pchar, SKILL_ACCURACY, value * 0.5);
		}
		else SF_AddEffect(SF_E_SKILL_EXP, pchar, skillname, value);
	}
}
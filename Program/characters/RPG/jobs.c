
#define JOB_NAVIGATOR "navigator"
#define JOB_BOATSWAIN "boatswain"
#define JOB_CANNONER "cannoner"
#define JOB_DOCTOR "doctor"
#define JOB_TREASURER "treasurer"
#define JOB_CARPENTER "carpenter"
#define JOB_FIGHTER "fighter"
#define JOBS_MAX 7 // всего работ

string JobByIdx(int idx)
{
	switch (idx)
	{
		case 0: return JOB_NAVIGATOR; break;
		case 1: return JOB_BOATSWAIN; break;
		case 2: return JOB_CANNONER;  break;
		case 3: return JOB_DOCTOR;    break;
		case 4: return JOB_TREASURER; break;
		case 5: return JOB_CARPENTER; break;
		case 6: return JOB_FIGHTER;   break;
	}

	trace("Can't find job by idx: " + idx);
	return "error";
}

string GetJobBySkillName(string skillName)
{
	switch (skillName)
	{
		case SKILL_SAILING:   return JOB_NAVIGATOR; break;
		case SKILL_CANNONS:   return JOB_CANNONER;  break;
		case SKILL_ACCURACY:  return JOB_CANNONER;  break;
		case SKILL_GRAPPLING: return JOB_BOATSWAIN; break;
		case SKILL_DEFENCE:   return JOB_DOCTOR;    break;
		case SKILL_REPAIR:    return JOB_CARPENTER; break;
		case SKILL_COMMERCE:  return JOB_TREASURER; break;
	}

	trace("Can't find job by skill name: " + skillName);
	return "error";
}

// Для канонира нужно делать исключение для пушек
string GetSkillNameByJob(string skillName)
{
	switch (skillName)
	{
		case JOB_NAVIGATOR: return SKILL_SAILING;   break;
		// case JOB_CANNONER:  return SKILL_CANNONS;   break;
		case JOB_CANNONER:  return SKILL_ACCURACY;  break;
		case JOB_BOATSWAIN: return SKILL_GRAPPLING; break;
		case JOB_DOCTOR:    return SKILL_DEFENCE;   break;
		case JOB_CARPENTER: return SKILL_REPAIR;    break;
		case JOB_TREASURER: return SKILL_COMMERCE;  break;
	}

	trace("Can't find skillName by job: " + skillName);
	return "error";
}
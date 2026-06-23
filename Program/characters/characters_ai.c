

void CharacterExitFromLocation(ref character)
{
	SendMessage(character, "l", MSG_CHARACTER_EXIT_FROM_LOCATION);
}

bool SetCharacterTask_None(ref character)
{
	return bool(SendMessage(character, "ls", MSG_NPCHARACTER_SETTASK, "None"));
}

bool SetCharacterForcedStop(ref character)
{
	SendMessage(character, "ls", MSG_CHARACTER_EX_MSG, "ForcedStopMove");
	return SetCharacterTask_None(character);
}

bool SetCharacterTask_Stay(ref character)
{
	return bool(SendMessage(character, "ls", MSG_NPCHARACTER_SETTASK, "Stay"));
}

bool SetCharacterTask_GotoPoint(ref character, string locatorGroup, string locatorName)
{
	float x, y, z;
	//Get current location
	if(IsEntity(&loadedLocation) == 0)
	{
		Trace("SetCharacterTask_GotoPoint -> location not created");
		return false;
	}
	//Check locator by create
	string slocator = "locators." + locatorGroup + "." + locatorName;
	if(CheckAttribute(loadedLocation, slocator) == 0)
	{
		if (locatorName != "")
		{
			Trace("SetCharacterTask_GotoPoint -> locator '" + locatorName + "' in group '" + locatorGroup + "' not found");
		}
		return false;
	}
	//Get locator position
	aref locator;
	MakeARef(locator, loadedLocation.(slocator));
	x = float(locator.x);
	y = float(locator.y);
	z = float(locator.z);
	//Set task
    bool isCheckBusyPos = !CheckAttribute(character, "chr_ai.tmpl.forced") || character.chr_ai.tmpl.forced == "0";
	return bool(SendMessage(character, "lslfff", MSG_NPCHARACTER_SETTASK, "Goto point", isCheckBusyPos, x, y, z));
}

bool SetCharacterTask_RuntoPoint(ref character, string locatorGroup, string locatorName)
{
	float x, y, z;
	//Get current location
	if(IsEntity(loadedLocation) == 0)
	{
		Trace("SetCharacterTask_GotoPoint -> location not created");
		return false;
	}
	//Check locator by create
	string slocator = "locators." + locatorGroup + "." + locatorName;
	if(CheckAttribute(loadedLocation, slocator) == 0)
	{
		Trace("SetCharacterTask_GotoPoint -> locator '" + locatorName + "' in group '" + locatorGroup + "' not found");
		return false;
	}
	//Get locator position
	aref locator;
	MakeARef(locator, loadedLocation.(slocator));
	x = float(locator.x);
	y = float(locator.y);
	z = float(locator.z);
	//Set task
    bool isCheckBusyPos = !CheckAttribute(character, "chr_ai.tmpl.forced") || character.chr_ai.tmpl.forced == "0";
	return bool(SendMessage(character, "lslfff", MSG_NPCHARACTER_SETTASK, "Runto point", isCheckBusyPos, x, y, z));
}

bool SetCharacterTask_FollowCharacter(ref character, ref followCharacter)
{	
	return bool(SendMessage(character, "lsi", MSG_NPCHARACTER_SETTASK, "Follow character", followCharacter));
}

bool SetCharacterTask_Fight(ref character, ref targetCharacter)
{
	return bool(SendMessage(character, "lsi", MSG_NPCHARACTER_SETTASK, "Fight", targetCharacter));
}

bool SetCharacterTask_Escape(ref character, ref escapeCharacter)
{
	return bool(SendMessage(character, "lsi", MSG_NPCHARACTER_SETTASK, "Escape", escapeCharacter));
}

bool SetCharacterTask_Dead(ref character)
{
	return bool(SendMessage(character, "ls", MSG_NPCHARACTER_SETTASK, "Dead"));
}

bool PushCharacterTask(ref character)
{
	return bool(SendMessage(character, "l", MSG_NPCHARACTER_PUSHTASK));
}

bool PopCharacterTask(ref character)
{
	return bool(SendMessage(character, "l", MSG_NPCHARACTER_POPTASK));
}

bool CharacterTurnByLoc(ref character, string group, string locator)
{
	return bool(SendMessage(character, "lssl", MSG_CHARACTER_TURNBYLOC, group, locator, false));
}

bool CharacterTurnToLoc(ref character, string group, string locator)
{
	return bool(SendMessage(character, "lssl", MSG_CHARACTER_TURNBYLOC, group, locator, true));
}

bool CharacterTurnByChr(ref character, ref byCharacter)
{
	return bool(SendMessage(character, "li", MSG_CHARACTER_TURNBYCHR, byCharacter));
}

bool CharacterTurnByPoint(ref character, float x, float y, float z)
{
	return bool(SendMessage(character, "lfff", MSG_CHARACTER_TURNBYPOINT, x, y, z));
}

bool CharacterTurnAy(ref character, float ay)
{
	return bool(SendMessage(character, "lf", MSG_CHARACTER_TURNAY, ay));
}

bool GetCharacterDistByChr(ref character, ref byCharacter, ref float_dist2D)
{
	float d = -1.0;
	if(SendMessage(character, "lie", MSG_CHARACTER_DIST2D, byCharacter, &d) == 0) return false;
	if(d < 0) return false;
	float_dist2D = d;
	return true;
}

bool GetCharacterDistByChr3D(ref character, ref byCharacter, ref float_dist3D)
{
	float d = -1.0;
	if(SendMessage(character, "lie", MSG_CHARACTER_DIST3D, byCharacter, &d) == 0) return false;
	if(d < 0) return false;
	float_dist3D = d;
	return true;
}

bool CharacterPlayAction(ref character, string actionName)
{
	return bool(SendMessage(character, "ls", MSG_CHARACTER_ACTIONPLAY, actionName));
}

bool GetCharacterDistByLoc(ref character, string group, string locator, ref float_dist3D)
{
	float d = -1.0;
	if(SendMessage(character, "lssse", MSG_CHARACTER_EX_MSG, "DistToLocator", group, locator, &d) == 0) return false;
	if(d < 0) return false;
	float_dist3D = d;
	return true;
}

string FindCharacterOptLocator(aref character, string group)
{
	string str = "";
	if(SendMessage(character, "lsse", MSG_CHARACTER_EX_MSG, "FindForvardLocator", group, &str) == 0) return "";
	return str;
}

string CharacterGetTask(ref character)
{
	string str = "";
	if(SendMessage(character, "le", MSG_NPCHARACTER_GETTASK, &str) == 0) str = "";
	return str;
}

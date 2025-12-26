void StealthCheckGates_Node1()
{
	aref situation;
	makearef(situation, storyObject.situation);
	situation.a = 100;

	situation.b.a = 60;
	situation.b.b = 40;

	situation.c.a = 50;
	situation.c.b = 50;

	situation.d = 100;
	SF_ResolveSituation(&situation);

	switch (situation.b)
	{
		case "a":
			bool anyPotion = StealthCheckGates_HasAnyPotion();
			reaction = SF_AddReaction("b", "", "", SF_Icon("item", storyObject.temp.potion));
			SF_SetResult(reaction, sti(storyObject.temp.potionPoints));
			if (!anyPotion) reaction.disabled = true;
		break;
		case "b":
			//ПРОВЕРКА. Шанс успеха 25+Талант*7. При успехе результат 1 и +25, при провале результат 2 и -10.
			reaction = SF_AddReaction("b", "", "", SF_Icon("pirates", PIRATES_T));
			SF_SetChance(reaction, 25, "base");
			SF_SetChance(reaction, GetSpecialAfterPenalty(pchar, PIRATES_T) * 7, PIRATES_T);
			SF_SetResults(reaction, -10, 25);
		break;
	}

	switch (situation.c)
	{
		case "a":
			//ПРОВЕРКА. Шанс успеха 40+Харизма/2. При успехе результат 1 и +25, при провале результат 2 и -10.
			reaction = SF_AddReaction("c", "", "", SF_Icon("skill", SKILL_LEADERSHIP));
			SF_SetChance(reaction, 40, "base");
			SF_SetChance(reaction, GetSkillAfterPenalty(pchar, SKILL_LEADERSHIP) / 2, SKILL_LEADERSHIP);
			SF_SetResults(reaction, -10, 25);
		break;
		case "b":
			reaction = SF_AddReaction("c", "", "", SF_Icon("item", "potionrum"));
			SF_SetResult(reaction, 20);
			if (GetCharacterFreeItem(pchar, "potionrum") < 1) reaction.disabled = true;
		break;
	}

	action = SF_AddAction("a", "", "", SF_Icon("skill", SKILL_SNEAK));
	SF_SetChance(action, -50.0, "base");
	SF_SetChance(action, GetCharacterSkill(pchar, SKILL_LEADERSHIP) / 2, SKILL_LEADERSHIP);
	SF_SetChance(action, GetCharacterSpecial(pchar, SPECIAL_L) * 2, SPECIAL_L);

	SF_AddAction("b", "", "", SF_Icon("story", "fail"));
}

// Предложить раненому гвардейцу помощь
void StealthCheckGates_Node1_b_a_reaction()
{
	SF_DefaultReaction("a");
	TakeNItems(pchar, storyObject.temp.potion, -1);
}

// Демонстративно подчиниться сержанту и укрепить его авторитет
void StealthCheckGates_Node1_b_b_reaction()
{
	SF_DefaultReaction("a");
}

// Сказать, что вы опаздываете на важную встречу и об этом инциденте будет доложено кому следует
void StealthCheckGates_Node1_c_a_reaction()
{
	SF_DefaultReaction("a");
}

// Предложить караульным ром
void StealthCheckGates_Node1_c_b_reaction()
{
	SF_DefaultReaction("a");
	TakeNItems(pchar, "potionrum", -1);
}

// Попытаться сгладить ситуацию
void StealthCheckGates_Node1_a_action()
{
	if (SF_PerformCheck())
	{
		SF_Triumph();
		AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 7);
		return;
	}

	AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 9);
	SF_Fail();
}

// Сбежать обратно в джунгли
void StealthCheckGates_Node1_b_action()
{
	storyObject.exit = true;
	STH_SetColonyEnemy(storyObject.context.colonyId, 1);
}

// Триумф
void StealthCheckGates_Node1_Triumph()
{
	StealthCheck_EnterTown("gates", STH_LEGAL);
}

// Крах
void StealthCheckGates_Node1_Fail()
{
	storyObject.exit = true;
	notification(XI_ConvertString("FriendFailNotif"), "SneakFail");
	STH_SetColonyEnemy(storyObject.context.colonyId, 1);
}

// =========================================
// ============ Хелперы истории ============
// =========================================

// Есть ли любое зелье для истории?
bool StealthCheckGates_HasAnyPotion()
{
	string potion = "";
	if (GetCharacterFreeItem(pchar, "potion4") > 0) potion = "potion4";
	// else if (GetCharacterFreeItem(pchar, "potion3") > 0) potion = "potion3"; противоядие?
	else if (GetCharacterFreeItem(pchar, "potion2") > 0) potion = "potion2";
	else if (GetCharacterFreeItem(pchar, "potion1") > 0) potion = "potion1";
	if (potion == "") return false;

	storyObject.temp.potion = potion;

	switch (potion)
	{
		case "potion1": storyObject.temp.potionPoints = 10; break;
		case "potion2": storyObject.temp.potionPoints = 15; break;
		// case "potion3": storyObject.temp.potionPoints = 20; break; противоядие?
		case "potion4": storyObject.temp.potionPoints = 35; break;
	}

	return true;
}

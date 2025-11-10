void LoyaltyPack_Start(string qName)
{
	pchar.questTemp.LoyaltyPack.FirstStage = "ready";
	AddQuestRecord("LoyaltyPack", "1");
}

void LoyaltyPack_FirstStage_DlgExit()
{
	// Устанавливаем флаг завершения этого этапа
	pchar.questTemp.LoyaltyPack.FirstStage = "completed";
	AddQuestRecord("LoyaltyPack", "2");
	Achievment_Set("ach_CL_165");
	SetFunctionTimerCondition("LoyaltyPack_SecondStage_Prepare", 0, 0, 1, false);
}

void LoyaltyPack_SecondStage_Prepare(string qName)
{
	pchar.quest.LoyaltyPack_SecondStage.win_condition.l1 = "Rank";
	pchar.quest.LoyaltyPack_SecondStage.win_condition.l1.value = 8;
	pchar.quest.LoyaltyPack_SecondStage.win_condition.l1.operation = ">=";
	pchar.quest.LoyaltyPack_SecondStage.function = "LoyaltyPack_SecondStage";
}

void LoyaltyPack_SecondStage(string qName)
{
	pchar.questTemp.LoyaltyPack.SecondStage = "ready";
	AddQuestRecord("LoyaltyPack", "3");
}

void LoyaltyPack_SecondStage_DlgExit()
{
	// Устанавливаем флаг завершения этого этапа
	pchar.questTemp.LoyaltyPack.SecondStage = "completed";
	AddQuestRecord("LoyaltyPack", "4");
	SetFunctionTimerCondition("LoyaltyPack_ThirdStage_Prepare", 0, 0, 1, false);
}

void LoyaltyPack_ThirdStage_Prepare(string qName)
{
	pchar.quest.LoyaltyPack_ThirdStage.win_condition.l1 = "Rank";
	pchar.quest.LoyaltyPack_ThirdStage.win_condition.l1.value = 12;
	pchar.quest.LoyaltyPack_ThirdStage.win_condition.l1.operation = ">=";
	pchar.quest.LoyaltyPack_ThirdStage.function = "LoyaltyPack_ThirdStage";
}

void LoyaltyPack_ThirdStage(string qName)
{
	pchar.questTemp.LoyaltyPack.ThirdStage = "ready";
	AddQuestRecord("LoyaltyPack", "5");
}

void LoyaltyPack_ThirdStage_DlgExit()
{
	// Устанавливаем флаг завершения этого этапа
	pchar.questTemp.LoyaltyPack.ThirdStage = "completed";
	AddQuestRecord("LoyaltyPack", "6");
	SetFunctionTimerCondition("LoyaltyPack_FourthStage_Prepare", 0, 0, 1, false);
}

void LoyaltyPack_FourthStage_Prepare(string qName)
{
	pchar.quest.LoyaltyPack_FourthStage.win_condition.l1 = "Rank";
	pchar.quest.LoyaltyPack_FourthStage.win_condition.l1.value = 16;
	pchar.quest.LoyaltyPack_FourthStage.win_condition.l1.operation = ">=";
	pchar.quest.LoyaltyPack_FourthStage.function = "LoyaltyPack_FourthStage";
}

void LoyaltyPack_FourthStage(string qName)
{
	pchar.questTemp.LoyaltyPack.FourthStage = "ready";
	AddQuestRecord("LoyaltyPack", "7");
}

void LoyaltyPack_FourthStage_DlgExit()
{
	// Устанавливаем флаг завершения этого этапа
	pchar.questTemp.LoyaltyPack.FourthStage = "completed";
	AddQuestRecord("LoyaltyPack", "8");
	
	// Продолжение у Фадея
	AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
	pchar.questTemp.LoyaltyPack.Fadey = "ready";
}

void LoyaltyPack_Fadey_DlgExit()
{
	pchar.questTemp.LoyaltyPack.Fadey = "completed";
	AddQuestRecord("LoyaltyPack", "9");
	CloseQuestHeader("LoyaltyPack");
	Achievment_Set("ach_CL_166");
}

bool RemoveAlonsoFromHold()
{
	if(CheckAttributeEqualTo(pchar, "questTemp.HWIC.Self", "KnippelPrisoner")) return true;
	if(CheckAttributeEqualTo(pchar, "questTemp.HWIC.Self", "LongwayPrisoner")) return true;
	
	return false;
}
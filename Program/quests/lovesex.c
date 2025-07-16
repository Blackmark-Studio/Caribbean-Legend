// ======================================================================================
// =============================== Отношения с девушками ================================
// ======================================================================================

// Sinistra катсцена с поцелуями в каюте корабля
void LoveSex_Cabin_Go()
{
	StartQuestMovie(true, false, true);
	chrDisableReloadToLocation = true;
	LAi_SetActorType(pchar);
	LAi_FadeToBlackStart();
	DoQuestFunctionDelay("LoveSex_Cabin_Go_2", 1.0);
}

void LoveSex_Cabin_Go_2(string qName)
{
	DeleteAllOfficersFromLocation();
	DoQuestFunctionDelay("LoveSex_Cabin_Go_3", 1.0);
}

void LoveSex_Cabin_Go_3(string qName)
{
	LAi_FadeToBlackEnd();
	if (Get_My_Cabin() == "My_Cabin_Huge")
	{
		LoveSex_Cabin_Huge();
	}
	if (Get_My_Cabin() == "My_Cabin" || Get_My_Cabin() == "My_CabineFDM")
	{
		LoveSex_Cabin_Big();
	}
	if (Get_My_Cabin() == "My_Cabin_Medium2")
	{
		LoveSex_Cabin_Normal();
	}
	if (Get_My_Cabin() == "My_Cabin_Medium")
	{
		LoveSex_Cabin_Medium();
	}
	if (Get_My_Cabin() == "My_Cabin_Small")
	{
		LoveSex_Cabin_Small();
	}
	if (Get_My_Cabin() == "My_Cabin_Memento")
	{
		LoveSex_Cabin_Memento();
	}
}

//--> Огромная каюта
void LoveSex_Cabin_Huge()
{	
	TeleportCharacterToPosAy(pchar, -0.40, 10.00, 4.60, -1.50);
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "kiss", "1", 16.5);
	sld = characterFromId(pchar.quest.sex_partner);
	DoQuestFunctionDelay("LoveSex_Cabin_Final", 15.0);
	ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
	TeleportCharacterToPosAy(sld, -1.00, 10.00, 4.60, 1.50);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "kiss", "1", 16.5);
	locCameraFromToPos(1.64, 11.53, 1.81, true, -0.92, 9.78, 5.16);
	DoQuestFunctionDelay("LoveSex_Cabin_Huge_2", 6.5);
	DoQuestFunctionDelay("LoveSex_Cabin_Huge_3", 12.0);
}

void LoveSex_Cabin_Huge_2(string qName)
{	
	locCameraFromToPos(-1.99, 11.43, 5.86, true, 3.00, 9.78, 1.58);
}

void LoveSex_Cabin_Huge_3(string qName)
{	
	locCameraFromToPos(-2.33, 11.08, 2.93, true, 1.14, 10.28, 5.84);
}
//<-- Огромная каюта

//--> Большая каюта
void LoveSex_Cabin_Big()
{	
	TeleportCharacterToPosAy(pchar, -1.30, 20.00, -1.10, 3.00);
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "kiss", "1", 9.5);
	sld = characterFromId(pchar.quest.sex_partner);
	DoQuestFunctionDelay("LoveSex_Cabin_Final", 9.5);
	ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
	TeleportCharacterToPosAy(sld, -1.30, 20.00, -1.70, 0.00);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "kiss", "1", 9.5);
	locCameraFromToPos(1.76, 21.32, -3.48, true, -3.14, 19.16, 0.27);
	DoQuestFunctionDelay("LoveSex_Cabin_Big_2", 6.5);
}

void LoveSex_Cabin_Big_2(string qName)
{	
	locCameraFromToPos(-0.70, 21.85, -3.30, true, -1.57, 19.40, 1.43);
}
//<-- Большая каюта

//--> Нормальная каюта
void LoveSex_Cabin_Normal()
{	
	TeleportCharacterToPosAy(pchar, 1.50, 2.14, -3.80, -1.50);
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "kiss", "1", 8.5);
	sld = characterFromId(pchar.quest.sex_partner);
	DoQuestFunctionDelay("LoveSex_Cabin_Final", 8.5);
	ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
	TeleportCharacterToPosAy(sld, 0.90, 2.14, -3.80, 1.50);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "kiss", "1", 8.5);
	locCameraFromToPos(-0.44, 3.57, -0.59, true, 1.76, 1.65, -5.05);
	DoQuestFunctionDelay("LoveSex_Cabin_Normal_2", 4.5);
}

void LoveSex_Cabin_Normal_2(string qName)
{	
	locCameraFromToPos(0.07, 3.32, -2.69, true, 1.92, 2.10, -4.31);
}
//<-- Нормальная каюта

//--> Средняя каюта
void LoveSex_Cabin_Medium()
{	
	TeleportCharacterToPosAy(pchar, -0.55, 6.06, 1.65, -1.50);
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "kiss", "1", 8.5);
	sld = characterFromId(pchar.quest.sex_partner);
	DoQuestFunctionDelay("LoveSex_Cabin_Final", 8.5);
	ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
	TeleportCharacterToPosAy(sld, -1.15, 6.06, 1.65, 1.50);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "kiss", "1", 8.5);
	locCameraFromToPos(-2.03, 7.59, -0.83, true, 0.01, 6.00, 3.28);
	DoQuestFunctionDelay("LoveSex_Cabin_Medium_2", 4.5);
}

void LoveSex_Cabin_Medium_2(string qName)
{	
	locCameraFromToPos(-1.80, 7.03, 3.33, true, 0.85, 6.25, -0.85);
}
//<-- Средняя каюта

//--> Маленькая каюта
void LoveSex_Cabin_Small()
{	
	TeleportCharacterToPosAy(pchar, 1.20, 3.00, -1.40, 3.00);
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "kiss", "1", 7.5);
	sld = characterFromId(pchar.quest.sex_partner);
	DoQuestFunctionDelay("LoveSex_Cabin_Final", 7.5);
	ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
	TeleportCharacterToPosAy(sld, 1.20, 3.00, -2.00, 0.00);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "kiss", "1", 7.5);
	locCameraFromToPos(-0.55, 4.42, -2.84, true, 2.06, 2.82, -2.00);
}
//<-- Маленькая каюта

//--> Мементо каюта
void LoveSex_Cabin_Memento()
{	
	TeleportCharacterToPosAy(pchar, -0.20, 6.12, 1.30, -1.50);
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "kiss", "1", 8.5);
	sld = characterFromId(pchar.quest.sex_partner);
	DoQuestFunctionDelay("LoveSex_Cabin_Final", 7.5);
	ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
	TeleportCharacterToPosAy(sld, -0.80, 6.12, 1.30, 1.50);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "kiss", "1", 8.5);
	locCameraFromToPos(1.05, 8.12, -0.60, true, -0.18, 6.05, 1.26);
	DoQuestFunctionDelay("LoveSex_Cabin_Memento_2", 4.5);
}

void LoveSex_Cabin_Memento_2(string qName)
{	
	locCameraFromToPos(-1.88, 7.69, 3.25, true, 0.30, 5.80, 0.71);
}
//<-- Мементо каюта

void LoveSex_Cabin_Final(string qName)
{	
	EndQuestMovie();
	bDisableCharacterMenu = false;
	LAi_SetPlayerType(pchar);
	locCameraTarget(PChar);
	locCameraFollowEx(true);
	sld = CharacterFromID(pchar.quest.sex_partner);
	ChangeCharacterAddressGroup(pchar, PChar.location, "reload", "reload1");
	ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
	if (Get_My_Cabin() == "My_Cabin_Huge")
	{
		ChangeCharacterAddressGroup(pchar, PChar.location, "rld", "aloc1");
		ChangeCharacterAddressGroup(sld, PChar.location, "rld", "aloc2");
	}
	if (Get_My_Cabin() == "My_Cabin" || Get_My_Cabin() == "My_CabineFDM")
	{
		ChangeCharacterAddressGroup(pchar, PChar.location, "rld", "aloc2");
		ChangeCharacterAddressGroup(sld, PChar.location, "rld", "aloc5");
	}
	if (Get_My_Cabin() == "My_Cabin_Medium2")
	{
		ChangeCharacterAddressGroup(pchar, PChar.location, "rld", "loc0");
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto3");
	}
	if (Get_My_Cabin() == "My_Cabin_Medium")
	{
		ChangeCharacterAddressGroup(pchar, PChar.location, "rld", "aloc0");
		ChangeCharacterAddressGroup(sld, PChar.location, "rld", "aloc2");
	}
	if (Get_My_Cabin() == "My_Cabin_Small")
	{
		ChangeCharacterAddressGroup(pchar, PChar.location, "rld", "loc1");
		ChangeCharacterAddressGroup(sld, PChar.location, "rld", "aloc0");
	}
	if (Get_My_Cabin() == "My_Cabin_Memento")
	{
		ChangeCharacterAddressGroup(pchar, PChar.location, "rld", "aloc0");
		ChangeCharacterAddressGroup(sld, PChar.location, "rld", "loc0");
	}
	LAi_SetActorType(sld);
	LAi_ActorTurnToCharacter(sld, pchar);
	LAi_ActorFollow(sld, pchar, "", -1);
	LAi_SetOfficerType(sld);
	sld.Dialog.CurrentNode = "sex_after";

	//--> квестовые ситуации после секса
	if (CheckAttribute(pchar, "questTemp.PZ_MaryRazgovorOBordeli")) sld.Dialog.CurrentNode = "PZ_MaryRazgovorOBordeli_Bad_17";
	if (CheckAttribute(pchar, "questTemp.PZ_DevushkaSnovaOfficer")) sld.Dialog.CurrentNode = "PZ_DevushkaSnovaOfficer_Dialog1";
	//<-- квестовые ситуации после секса
	
	SetLaunchFrameFormParam("", "", 0, 15);
	SetLaunchFrameFormPic("loading\inside\censored1.tga");
	PlayStereoSound("sex\sex" + (rand(9) + 1) + ".wav");
	LaunchFrameForm();
	WaitDate("", 0, 0, 0, 3, 10);
	RecalculateJumpTable();
	
	int addHealthQuantity = 6;
	float addMaxHealthQuantity = 1;
	
	if (pchar.quest.sex_partner == "Mary")
	{
		addHealthQuantity *= 2;
	}
	
	if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
	{
		addHealthQuantity *= 2;
		addMaxHealthQuantity *= 2;
	}
	
	AddCharacterHealth(pchar, addHealthQuantity);
	AddCharacterMaxHealth(pchar, addMaxHealthQuantity);
	
	LAi_SetCurHPMax(pchar);
	
	if (pchar.quest.sex_partner == "Mary")
	{
		pchar.quest.Mary_giveme_sex.over = "yes";
		pchar.quest.Mary_giveme_sex1.over = "yes";
	}
}

// Sinistra катсцена с поцелуями в комнате на суше
void LoveSex_Room_Go()
{
	StartQuestMovie(true, false, true);
	if(loadedLocation.filespath.models == "locations\inside\Tavern_room")
	{
		LoveSex_Room_Tavern();
	}
	if(loadedLocation.filespath.models == "locations\inside\Brothel_room\")
	{
		LoveSex_Room_Brothel();
	}
	if(loadedLocation.filespath.models == "locations\inside\Doubleflour_house")
	{
		LoveSex_Room_Doubleflour();
	}
}

//--> Комната в таверне
void LoveSex_Room_Tavern()
{
	locCameraFromToPos(-0.64, 1.72, -0.90, true, 1.53, -0.20, -3.08);
	TeleportCharacterToPosAy(pchar, 0.10, 0.00, -1.50, 3.00);
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "kiss", "1", 7.5);
	
	ref sld = characterFromId(pchar.quest.sex_partner);

	TeleportCharacterToPosAy(sld, 0.10, 0.00, -2.10, 0.00);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "kiss", "1", 7.5);
	
	DoQuestFunctionDelay("LoveSex_Room_Tavern_2", 2.9);
	DoQuestFunctionDelay("LoveSex_Room_Final", 7.5);
}

void LoveSex_Room_Tavern_2(string qName)
{
	locCameraFromToPos(-0.92, 1.57, -2.40, true, 2.14, -0.20, -0.37);
}
//<-- Комната в таверне

//--> Комната в борделе
void LoveSex_Room_Brothel()
{
	locCameraFromToPos(2.37, 1.48, -1.02, true, -0.29, -0.14, -3.85);
	TeleportCharacterToPosAy(pchar, 1.50, 0.00, -2.49, 0.00);
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "kiss", "1", 7.5);
	
	ref sld = characterFromId(pchar.quest.sex_partner);
	
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto3");
	TeleportCharacterToPosAy(sld, 1.50, 0.00, -1.89, 3.00);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "kiss", "1", 7.5);
	
	DoQuestFunctionDelay("LoveSex_Room_Final", 7.5);
}
//<-- Комната в борделе

//--> Комната на Исла Моне
void LoveSex_Room_Doubleflour()
{
	locCameraFromToPos(-1.48, 1.84, -0.86, true, -3.61, -0.20, -2.41);
	TeleportCharacterToPosAy(pchar, -3.60, 0.00, -2.20, 3.00);
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "kiss", "1", 5.5);
	
	ref sld = characterFromId(pchar.quest.sex_partner);
	
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
	TeleportCharacterToPosAy(sld, -3.60, 0.00, -2.80, 0.00);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "kiss", "1", 5.5);
	
	DoQuestFunctionDelay("LoveSex_Room_Final", 5.5);
}
//<-- Комната на Исла Моне

void LoveSex_Room_Final(string qName)
{
	EndQuestMovie();
	locCameraTarget(PChar);
	locCameraFollowEx(true);
	LAi_SetPlayerType(pchar);
	
	ref sld = characterFromId(pchar.quest.sex_partner);
	
	int addHealthQuantity = 6;
	float addMaxHealthQuantity = 1;
	
	if (pchar.quest.sex_partner == "Mary")
	{
		addHealthQuantity *= 2;
	}
	
	if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
	{
		addHealthQuantity *= 2;
		addMaxHealthQuantity *= 2;
	}
	
	AddCharacterHealth(pchar, addHealthQuantity);
	AddCharacterMaxHealth(pchar, addMaxHealthQuantity);

	if(loadedLocation.filespath.models == "locations\inside\Tavern_room")
	{
		ChangeCharacterAddressGroup(pchar, PChar.location, "quest", "quest4");
		ChangeCharacterAddressGroup(sld, PChar.location, "quest", "quest3");
	}
	if(loadedLocation.filespath.models == "locations\inside\Brothel_room\")
	{
		ChangeCharacterAddressGroup(pchar, PChar.location, "goto", "goto2");
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
	}
	if(loadedLocation.filespath.models == "locations\inside\Doubleflour_house")
	{
		ChangeCharacterAddressGroup(pchar, PChar.location, "goto", "goto2");
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
	}

	sld.dialog.currentnode = "sex_after";
	LAi_SetOfficerType(sld);
	
	SetLaunchFrameFormParam("", "", 0, 15);
	SetLaunchFrameFormPic("loading\inside\censored1.tga");
	PlayStereoSound("sex\sex"+(rand(9)+1)+".wav");
    LaunchFrameForm();
	WaitDate("", 0, 0, 0, 3, 10);
	RecalculateJumpTable();
	LAi_SetCurHPMax(pchar);
	if (rand(2) == 0)
	{
		pchar.GenQuest.CamShuttle = 2;
		SetCamShuttle(loadedLocation);
	}
	
	AddMoneyToCharacter(pchar, -1000);
	
	string skill;
	
	switch (rand(5)) {
		case 0:
			skill = SKILL_ACCURACY;
		break;
		
		case 1:
			skill = SKILL_CANNONS;
		break;
		
		case 2:
			skill = SKILL_SAILING;
		break;
		
		case 3:
			skill = SKILL_REPAIR;
		break;
		
		case 4:
			skill = SKILL_GRAPPLING;
		break;
		
		case 5:
			skill = SKILL_DEFENCE;
		break;
	}
	
	AddCharacterSkill(pchar, skill, 1);
	Log_Info(""+pchar.name + StringFromKey("HelenDrinking_22") + XI_ConvertString(skill)+"");
	
	switch (rand(2)) {
		case 0:
			skill = SKILL_F_LIGHT;
		break;
		
		case 1:
			skill = SKILL_FENCING;
		break;
		
		case 2:
			skill = SKILL_F_HEAVY;
		break;
	}
	
	
	if (pchar.quest.sex_partner == "Mary")
	{
		pchar.quest.Mary_giveme_sex.over = "yes";
		pchar.quest.Mary_giveme_sex1.over = "yes"; 
	}
	if (pchar.quest.sex_partner == "Helena")
	{
		pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
		pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
		pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
		pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
		pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
		pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
		pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
	}
	AddCharacterSkill(sld, skill, 1);
	Log_Info(""+sld.name + StringFromKey("HelenDrinking_23") + XI_ConvertString(skill));
}
	
// Классический вариант секса
void LoveSex_Classic(string qName)
{
	SetLaunchFrameFormParam("", "", 0, 15);
	SetLaunchFrameFormPic("loading\inside\censored1.tga");
	PlayStereoSound("sex\sex" + (rand(9) + 1) + ".wav");
	LaunchFrameForm();
	WaitDate("", 0, 0, 0, 3, 10);
	RecalculateJumpTable();
	
	int addHealthQuantity = 6;
	float addMaxHealthQuantity = 1;
	
	if (pchar.quest.sex_partner == "Mary")
	{
		addHealthQuantity *= 2;
	}
	
	if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
	{
		addHealthQuantity *= 2;
		addMaxHealthQuantity *= 2;
	}
	
	AddCharacterHealth(pchar, addHealthQuantity);
	AddCharacterMaxHealth(pchar, addMaxHealthQuantity);
	
	LAi_SetCurHPMax(pchar);
	
	if (pchar.quest.sex_partner == "Mary")
	{
		pchar.quest.Mary_giveme_sex.over = "yes";
		pchar.quest.Mary_giveme_sex1.over = "yes";
	}
}
	
	
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////	
///Jason-------------------------------------Пиратская Сага-----------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void Gladis_SetHome(string qName)//ставим Глэдис домой
{
	sld = characterFromId("Gladis");
	ChangeCharacterAddressGroup(sld, "SantaCatalina_houseSp3", "goto", "goto1");
	LAi_SetOwnerType(sld);
}

void Helena_AntiguaOver(string qName)//провал квеста по срокам
{
	pchar.quest.Saga_createDonovan.over = "yes";//снять возможное прерывание на корвет Донована
	pchar.quest.Saga_createJimmy.over = "yes"; //снять возможное прерывание на Джимми
	sld = characterFromId("Gladis");
	sld.dialog.currentnode = "Helena_die";
	AddQuestRecord("Saga", "2");
	CloseQuestHeader("Saga");
	DeleteAttribute(pchar, "questTemp.Saga");
	// Левассера - к барьеру!
	sld = characterFromId("Tortuga_Mayor");
	LAi_LoginInCaptureTown(sld, true);
	pchar.questTemp.Sharlie.Hardcore_Tortuga = "true";
}

void Saga_CreateJimmy(string qName)//ставим Джимми
{
	int iRank = 18+MOD_SKILL_ENEMY_RATE;
	int iScl = 50;
	sld = GetCharacter(NPC_GenerateCharacter("SagaJimmy" , "mercen_16", "man", "man", iRank, PIRATE, -1, true, "quest"));
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol6", "bullet", iScl);
	sld.name = StringFromKey("Saga_1");
	sld.lastname = StringFromKey("Saga_2");
	sld.dialog.FileName = "Quest\Saga\OtherNPC.c";
	sld.dialog.currentnode = "Jimmy";
	sld.greeting = "town_pirate";
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	LAi_SetOwnerType(sld);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "FortOrange_House1", "goto", "goto1");
}

void Saga_createDonovan(string qName)//ставим корвет Донована
{
	pchar.quest.Helena_AntiguaOver.over = "yes";// снять таймер
	AddQuestRecord("Saga", "7");
	Island_SetReloadEnableGlobal("Antigua", false);//на остров нельзя
	Group_FindOrCreateGroup("DonovanGroup");
	Group_SetType("DonovanGroup", "war");//тип группы
	int iRank = 18+MOD_SKILL_ENEMY_RATE;
	int iScl = 55;
	sld = GetCharacter(NPC_GenerateCharacter("Donovan", "Donovan", "man", "man", iRank, ENGLAND, -1, true, "quest"));
	FantomMakeSmallSailor(sld, SHIP_CORVETTE, StringFromKey("Saga_3"), CANNON_TYPE_CANNON_LBS20, 70, iScl, iScl+5, iScl+10, iScl+5);
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_22", "pistol6", "bullet", iScl*2); // 300912
	if (MOD_SKILL_ENEMY_RATE >= 6) LAi_SetHP(sld, 200+MOD_SKILL_ENEMY_RATE*30, 200+MOD_SKILL_ENEMY_RATE*30);
	sld.name = StringFromKey("Saga_4");
	sld.lastname = StringFromKey("Saga_5");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.SaveItemsForDead = true; // сохранять на трупе вещи
	sld.DontClearDead = true; // 300912
	sld.Ship.Mode = "war";
	sld.AlwaysEnemy = true;
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "BasicBattleState");
	SetCharacterPerk(sld, "AdvancedBattleState");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "Doctor1");
	Group_AddCharacter("DonovanGroup", "Donovan");
	Group_SetGroupCommander("DonovanGroup", "Donovan");
	if (sti(pchar.rank > 17) && MOD_SKILL_ENEMY_RATE > 4)
	{
		sld = GetCharacter(NPC_GenerateCharacter("DonovanHelper", "off_eng_2", "man", "man", 25, ENGLAND, 2, true, "quest"));
		FantomMakeSmallSailor(sld, SHIP_FRIGATE, "", CANNON_TYPE_CANNON_LBS24, 80, 65, 75, 80, 65);
		FantomMakeCoolFighter(sld, 25, 70, 70, "blade_15", "pistol6", "bullet", 200);
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.Ship.Mode = "war";
		sld.AlwaysEnemy = true;
		SetCharacterPerk(sld, "MusketsShoot");
		SetCharacterPerk(sld, "HullDamageUp");
		SetCharacterPerk(sld, "SailsDamageUp");
		SetCharacterPerk(sld, "CrewDamageUp");
		SetCharacterPerk(sld, "CriticalShoot");
		SetCharacterPerk(sld, "BasicBattleState");
		SetCharacterPerk(sld, "AdvancedBattleState");
		SetCharacterPerk(sld, "ShipDefenseProfessional");
		SetCharacterPerk(sld, "ShipSpeedUp");
		SetCharacterPerk(sld, "ShipTurnRateUp");
		SetCharacterPerk(sld, "Doctor1");
		Group_AddCharacter("DonovanGroup", "DonovanHelper");
		Group_SetGroupCommander("DonovanGroup", "DonovanHelper");
	}
	Group_SetTaskNone("DonovanGroup");//нет задачи
	Group_SetAddress("DonovanGroup", "Antigua", "quest_ships", "quest_ship_"+(3+rand(4)));
	Group_LockTask("DonovanGroup");
	
	pchar.quest.Donovan_AfterBattle.win_condition.l1 = "NPC_Death";
	pchar.quest.Donovan_AfterBattle.win_condition.l1.character = "Donovan";
	pchar.quest.Donovan_AfterBattle.function = "Donovan_AfterBattle";
	pchar.quest.Donovan_DieHard.win_condition.l1 = "MapEnter";
	pchar.quest.Donovan_DieHard.function = "Donovan_DieHard";
}

void Donovan_AfterBattle(string qName)//после боя
{
	DoQuestCheckDelay("sea_victory", 1.5);
	pchar.quest.Donovan_DieHard.over = "yes";
	if (CheckAttribute(pchar, "questTemp.Saga.Takehelen"))//абордировали
	{
		bQuestDisableMapEnter = true;//закрыть карту
		int iShipType = GetCharacterShipType(pchar);
		ref rShip = GetRealShip(iShipType);
		sTemp = "My_" + rShip.CabinType;
		sld = characterFromId("Helena");
		sld.dialog.currentnode = "After_boarding";
		ChangeCharacterAddressGroup(sld, sTemp, "rld", "aloc0");
		LAi_SetStayType(sld);
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, false);
		AddQuestRecord("Saga", "10");
		AddComplexSeaExpToScill(150, 100, 100, 200, 100, 100, 0);
	}
	else
	{
		Island_SetReloadEnableGlobal("Antigua", true);//на остров можно
		sld = characterFromId("Gladis");
		sld.dialog.currentnode = "Helena_die";
		AddQuestRecord("Saga", "9");
		CloseQuestHeader("Saga");
		DeleteAttribute(pchar, "questTemp.Saga");
		// Левассера - к барьеру!
		sld = characterFromId("Tortuga_Mayor");
		LAi_LoginInCaptureTown(sld, true);
		pchar.questTemp.Sharlie.Hardcore_Tortuga = "true";
	}
}

void Donovan_DieHard(string qName)//сбежал
{
	Island_SetReloadEnableGlobal("Antigua", true);//на остров можно
	pchar.quest.Donovan_AfterBattle.over = "yes";
	Group_DeleteGroup("DonovanGroup");
	sld = characterFromId("Gladis");
	sld.dialog.currentnode = "Helena_die";
	AddQuestRecord("Saga", "8");
	CloseQuestHeader("Saga");
	DeleteAttribute(pchar, "questTemp.Saga");
	// Левассера - к барьеру!
	sld = characterFromId("Tortuga_Mayor");
	LAi_LoginInCaptureTown(sld, true);
	pchar.questTemp.Sharlie.Hardcore_Tortuga = "true";
}

void Saga_returnBlueveld(string qName)//возвращение в Блювельд
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = characterFromId("Helena");
	RemovePassenger(Pchar, sld);
	sld.dialog.currentnode = "Return_blueveld";
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "Santacatalina_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Helena_ReturnOver(string qName)//чтобы не тянул c переходом
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Helena_ReturnOver.over"))
			DeleteAttribute(pchar,"quest.Helena_ReturnOver.over");
		NewGameTip(StringFromKey("Saga_6"));
		SetFunctionTimerCondition("Helena_ReturnOver", 0, 0, 45, false);
		return;
	}
	sld = characterFromId("Helena");
	RemovePassenger(Pchar, sld);
	sld.lifeday = 0;
	sld = characterFromId("Gladis");
	sld.dialog.currentnode = "Gladis_exit";
	AddQuestRecord("Saga", "12");
	CloseQuestHeader("Saga");
	DeleteAttribute(pchar, "questTemp.Saga");
	log_info(StringFromKey("Saga_7"));
	pchar.quest.Saga_returnBlueveld.over = "yes"; //Desperado фикс блокировки Блювельда
	// Левассера - к барьеру!
	sld = characterFromId("Tortuga_Mayor");
	LAi_LoginInCaptureTown(sld, true);
	pchar.questTemp.Sharlie.Hardcore_Tortuga = "true";
}

void Saga_CreateGonsalesA(string qName)	//ставим Гонсалеса
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = GetCharacter(NPC_GenerateCharacter("SagaGonsalesA" , "citiz_19", "man", "man", 12, SPAIN, 2, true, "soldier"));
	SetFantomParamFromRank(sld, 12, true);
	sld.name = StringFromKey("Saga_8");
	sld.lastname = StringFromKey("Saga_9");
	sld.dialog.FileName = "Quest\Saga\OtherNPC.c";
	sld.dialog.currentnode = "GonsalesA";
	sld.greeting = "citizen_male";
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	ChangeCharacterAddressGroup(sld, "Cartahena_houseF2", "goto", "goto1");
}

void Saga_CreateGonsalesB(string qName)	//ставим Гонсалеса
{
	sld = GetCharacter(NPC_GenerateCharacter("SagaGonsalesB", "citiz_41", "man", "man", 15, SPAIN, -1, true, "soldier"));
	FantomMakeCoolFighter(sld, 15, 40, 40, "blade_10", "pistol1", "bullet", 50);
	sld.name = StringFromKey("Saga_10");
	sld.lastname = StringFromKey("Saga_11");
	sld.dialog.FileName = "Quest\Saga\OtherNPC.c";
	sld.dialog.currentnode = "GonsalesB";
	sld.greeting = "town_pirate";
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	LAi_SetWarriorType(sld);
	LAi_SetLoginTime(sld, 6.0, 21.0);
	ChangeCharacterAddressGroup(sld, "Cartahena_town", "quest", "quest2");
}

void Saga_SetOrtega() //ставим клон Ортеги, а настоящего смотрителя прячем
{
	sld = characterFromId("Cartahena_Lightman");
	sld.location = "none";
	sld = GetCharacter(NPC_GenerateCharacter("SagaOrtega", "keeper_1", "man", "man_B", 20, SPAIN, -1, true, "soldier"));
	FantomMakeCoolFighter(sld, 20, 50, 50, "", "pistol1", "bullet", 50);
	string sBlade = GetBestGeneratedItem("blade_10");
	GiveItem2Character(sld, sBlade);
	sld.equip.blade = sBlade;
	sld.name = StringFromKey("Saga_12");
	sld.lastname = StringFromKey("Saga_13");
	sld.dialog.FileName = "Quest\Saga\OtherNPC.c";
	sld.dialog.currentnode = "Ortega";
	sld.greeting = "lighthouseman_2";
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Mayak11_Lighthouseroom", "barmen", "bar2");
}

void Saga_LightmanReturn(string qName)//вертаем назад смотрителя маяка Картахены
{
	sld = characterFromId("Cartahena_Lightman");
	sld.location = "Mayak11_Lighthouseroom";
	sld.location.group = "barmen";
	sld.location.locator = "bar2";
	sld.model = "citiz_32";
	sld.model.animation = "man";
	sld.name = "Хуан";
	sld.lastname = "Перес";
	sld.dialog.currentnode = "First time";
}

void Saga_CreateTrapBandos(string qName)//ловушка - бандиты у маяка
{
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	int n = makeint(MOD_SKILL_ENEMY_RATE/3);
	int iRank = 20+MOD_SKILL_ENEMY_RATE;
	int iScl = 55;
	for (i=1; i<=3+n; i++)
	{
		if (i == 1) 
		{	
			sld = GetCharacter(NPC_GenerateCharacter("sagatrap_sold_"+i, "mush_ctz_"+(rand(2)+7), "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, 80, "", "mushket1", "cartridge", iScl*2);
			sld.Dialog.Filename = "Quest\Saga\OtherNPC.c";
			sld.dialog.currentnode = "saga_trap";
			sld.greeting = "hunter";
			ChangeCharacterAddressGroup(sld, "mayak11", "reload", "reload1");
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("sagatrap_sold_"+i, "citiz_"+(40+i), "man", "man", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_04", "pistol1", "bullet", iScl*2);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "mayak11", "reload", "reload1");
		}
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

//------------------------------------------телепортация-------------------------------------------
void Dolly_TeleportStart()
{
	PlaySound("interface\notebook.wav");
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "camera", "dolly");
	if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "first_teleport") LAi_ActorAnimation(pchar, "afraid", "OpenTheDoors", 1.2);
	for (i=1; i<=8; i++)
	{
		CreateLocationParticles("shadowstar", "item", "torch"+i, 1.15, 0, 0, "");
	}
	CreateLocationParticles("shadowstar", "camera", "dolly", 1.15, 0, 0, "");
	DoQuestFunctionDelay("Dolly_TeleportContinue_1", 7.0);
	if (sGlobalTemp == "dolly2") PlayStereoOGG("music_teleport");
	else SetMusic("music_teleport");
}

void Dolly_TeleportContinue_1(string qName)
{
	for (i=1; i<=8; i++)
	{
		switch (sGlobalTemp)
		{
			case "dolly1":
				PlaySound("Weather\Thunder_01.wav");
				CreateLocationParticles("torch", "item", "torch"+i, 1.15, 0, 0, "");
			break;
			
			case "dolly2": 
				CreateLocationParticles("fountain", "item", "torch"+i, 1.15, 0, 0, "");
				CreateLocationParticles("fountain", "item", "torch"+i, 1.15, 0, 0, "");
				CreateLocationParticles("fishblue", "item", "dolly2", 1.15, 0, 0, "");
				CreateLocationParticles("fountain", "item", "dolly2", 1.15, 0, 0, "");
				CreateLocationParticles("fountain", "item", "dolly2", 1.15, 0, 0, "");
				CreateLocationParticles("Splash", "item", "dolly2", 2.2, 0, 0, "");
				PlaySound("Sea Battles\bolshoy_vsplesk_001.wav");
				PlaySound("Weather\fontan_001.wav");
			break;
			
			case "dolly3":
				CreateLocationParticles("smoke", "item", "torch"+i, 1.15, 0, 0, "");
				CreateLocationParticles("torch", "camera", "dolly", 1.15, 0, 0, "");
				PlaySound("Ambient\Teno_inside\big_ring.wav");
			break;
		}
	}
	DoQuestFunctionDelay("Dolly_TeleportContinue_2", 7.0);
}

void Dolly_TeleportContinue_2(string qName)
{
	switch (sGlobalTemp)
	{
		case "dolly1":
			CreateLocationParticles("large_smoke", "item", "dolly1", 1.15, 0, 0, "");
			CreateLocationParticles("shipfire", "item", "dolly1", 1.15, 0, 0, "");
	PlaySound("Weather\koster_001.wav");
		break;
		
		case "dolly2":
			CreateLocationParticles("bubbles", "item", "dolly2", 2.0, 0, 0, "");
			PlaySound("Sea Battles\bolshoy_vsplesk_003.wav");
			PlaySound("Weather\fontan_001.wav");
		break;
		
		case "dolly3": 
			CreateLocationParticles("large_smoke", "item", "dolly3", 1.15, 0, 0, "");
			PlaySound("Weather\Thunder_03.wav");
		break;
	}
	DoQuestFunctionDelay("Dolly_TeleportContinue_3", 6.0);
}

void Dolly_TeleportContinue_3(string qName)
{
	switch (sGlobalTemp)
	{
		case "dolly1": LAi_ActorGoToLocation(pchar, "item", "dolly1", "none", "", "", "", 1.0); break;
		case "dolly2": 
			LAi_ActorGoToLocation(pchar, "", "", "none", "", "", "", 1.0); 
		break;
		case "dolly3":
			LAi_ActorGoToLocation(pchar, "", "", "none", "", "", "", 1.0);
			CreateLocationParticles("large_smoke", "item", "dolly3", 1.15, 0, 0, "");
		break;
	}
	PlaySound("Ambient\Teno_inside\teleporter.wav");
	DoQuestFunctionDelay("Dolly_TeleportContinue_4", 8.0);
	if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal")) // 210812
	{
		// офицеры
		for(i=1; i<=3; i++)
		{
			int idx = GetOfficersIndex(pchar, i);
			if(idx < 0) continue;
			sld = &Characters[idx];
			if (CheckAttribute(sld, "quest.Tieyasal") && sld.quest.Tieyasal == "teleport")
			{
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.quest.teleportation = true;
			}
		}
	}
}

void Dolly_TeleportContinue_4(string qName)
{
	if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal")) // 190812
	{
		DoQuestReloadToLocation("Tenochtitlan", "reload", "reload1", "Tieyasal_TeleportArrive");
		return;
	}
	switch (sGlobalTemp)
	{
		case "dolly1":
			DoQuestReloadToLocation("LostShipsCity_town", "quest", "teleport1", "LSC_TeleportArrive");
		break;
		
		case "dolly2":
			DoQuestReloadToLocation("Indian_town", "quest", "teleport1", "Dominica_TeleportArrive");
		break;
		
		case "dolly3": 
			DoQuestReloadToLocation("Pearl_jungle_03", "goto", "goto4", "Pearl_TeleportArrive");
		break;
	}
}

void Dolly_TeleportConsequences() // последствия телепорта
{
	Pchar.chr_ai.hp = stf(Pchar.chr_ai.hp)/3; // 2/3 жизни сносим
	AddCharacterHealth(pchar, -45); //сносим здоровье
	pchar.chr_ai.poison = 500; // травим
	if (stf(pchar.Health.HP) <= 1) LAi_KillCharacter(pchar);
}
//<-- телепортация

void Saga_BaronsQuestsGo(string qName)//старт квестов пиратских баронов
{
	pchar.questTemp.Saga = "baronsquests";
	SetFunctionTimerCondition("Saga_TimeOver", 0, 0, 365, false);//таймер на провал Саги по времени
}

//------------------------------------------возвращение барона-----------------------------------------------

void Saga_DannyMeeting(string qName)//знакомство с Даниэль
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = characterFromId("Danielle");
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "SantaCatalina_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Saga_CreateSnakeEye()// создаем Змеиного Глаза - шамана
{
	sld = GetCharacter(NPC_GenerateCharacter("SnakeEye", "Shaman", "man", "man_B", 20, PIRATE, -1, true, "native"));
	SetFantomParamFromRank(sld, 10, true);
	sld.name = StringFromKey("Saga_14");
	sld.lastname = StringFromKey("Saga_15");
	sld.dialog.FileName = "Quest\Saga\SnakeEye.c";
	sld.dialog.currentnode = "SnakeEye";
	sld.greeting = "SnakeEye";
	LAi_SetGroundSitTypeNoGroup(sld);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Miskito_shack2", "quest", "quest1");
}

void Saga_DannyTalk(string qName)// говорилка Даниэль
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = characterFromId("Danielle");
	switch (sld.quest.talk)
	{
		case "dolly": sld.dialog.currentnode = "Dolly"; break; //Даниэль показывает истукана
		case "SnakeEye": sld.dialog.currentnode = "SnakeEye"; break; //разговор с Даниэль в деревне мискито
		case "teleport": sld.dialog.currentnode = "teleport"; break; //перед полночью
		case "shadowstar": sld.dialog.currentnode = "shadowstar"; break; //перед телепортацией
		case "failcenturion": sld.dialog.currentnode = "failcenturion"; break; //потопили Центурион
	}
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Saga_NatanPrepareTreatment(string qName)// ставим Натана и Даниэль в деревню
{
	LocatorReloadEnterDisable("Miskito_village", "reload1", true);
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	sld = characterFromId("Danielle");
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Miskito_village", "reload", "reload1");
	LAi_ActorFollowEverywhere(sld, "", -1);
	sld = characterFromId("Nathaniel");
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Miskito_village", "reload", "reload1");
	LAi_ActorFollowEverywhere(sld, "", -1);
}

void Saga_NatanTreatment(string qName)// Даниэль после сдачи Натана на лечение
{
	LocatorReloadEnterDisable("Miskito_village", "reload1", false);
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
	sld = characterFromId("Danielle");
	sld.dialog.currentnode = "treatment";
	LAi_SetActorType(sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

//------------------------------------------нахождение в ГПК (Локо-Риферте)----------------------------------
void LSC_CreateCrabGuard() // крабик-охранник
{
	sld = GetCharacter(NPC_GenerateCharacter("CrabGuard", "crabBig", "crab", "crabBig", 40+(MOD_SKILL_ENEMY_RATE), PIRATE, 0, false, "quest"));
	sld.name = StringFromKey("Saga_16");
	sld.lastname = StringFromKey("Saga_17");
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed");
	int iTemp = 100+MOD_SKILL_ENEMY_RATE*15+sti(pchar.rank)*5;
	LAi_SetHP(sld, iTemp, iTemp);
	if (MOD_SKILL_ENEMY_RATE > 2) sld.MultiFighter = stf(MOD_SKILL_ENEMY_RATE/2.5);
	sld.animal = true;
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	LAi_SetActorType(sld);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	GiveItem2Character(sld, "jewelry52");
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "reload", "reload2");
	DoQuestFunctionDelay("LSC_CrabAttack", 6.5);
}

void LSC_CrabAttack(string qName)// нападение краба по прибытии
{
	sld = characterFromId("CrabGuard");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "LSC_CrabGuardDie");
}

void LSC_OpenSanAvgustinDoors()// открыть наружные двери Сан-Августина
{
	for (int i=1; i<=8; i++)
	{
		if (i == 2 || i == 7) continue;
 		LocatorReloadEnterDisable("LostShipsCity_town", "reload"+i, false);
	}
}

void LSC_CloseSanAvgustinDoors()// закрыть наружные двери Сан-Августина
{
	for (int i=1; i<=8; i++)
	{
 		LocatorReloadEnterDisable("LostShipsCity_town", "reload"+i, true);
	}
}

void LSC_OpenTartarusDoors()// открыть наружные двери Тартаруса
{
	LocatorReloadEnterDisable("LostShipsCity_town", "reload51", false);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload52", false);
}

void LSC_CloseTartarusDoors()// закрыть наружные двери Тартаруса
{
	LocatorReloadEnterDisable("LostShipsCity_town", "reload51", true);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload52", true);
}

// ---------------------------------вариант прохождения R: стрелок--------------------------------------------
void LSC_CreatePantryGuard(string qName)// арест, если полез в трюм
{
	chrDisableReloadToLocation = true;//закрыть локацию
	pchar.questTemp.LSC = "prison"; // меняем флаг
	LSC_OpenSanAvgustinDoors(); // открываем Сан-Августин
	LSC_OpenTartarusDoors(); // открываем Тартарус снаружи
	LocatorReloadEnterDisable("TartarusPrison", "reload1", true);
	LocatorReloadEnterDisable("TartarusPrison", "reload2", true); // закрываем Тартарус изнутри
	LocatorReloadEnterDisable("LostShipsCity_town", "reload60", true);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload61", true); // закрываем вход к Мэри
	pchar.quest.LSC_findMary.over = "yes"; //снять прерывание на Мэри
	int iRank = 18+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 60;
	for (i=1; i<=5; i++)
	{
		if (i == 1)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PantryGuard_"+i, "mush_ctz_7", "man", "mushketer", iRank, PIRATE, 0, true, "quest"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "bullet", iScl+50);
			sld.dialog.Filename = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "PantryGuard";	
			sld.greeting = "HUNTER"; 
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");
		}
		else
		{	
			sld = GetCharacter(NPC_GenerateCharacter("PantryGuard_"+i, "citiz_4"+(i+3), "man", "man", iRank, PIRATE, 0, true, "quest"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol4", "bullet", iScl+50);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto"+(i+1));
		}
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
	}
}

void LSC_GotoPrison(string qName)// в тюрьму на Тартарус
{
	DoFunctionReloadToLocation("TartarusPrison", "quest", "reload1", "LSC_TalkWithCapper");
	bDisableCharacterMenu = true;//лочим Ф2
	InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
	//обчистим карманы ГГ
	ref location = &Locations[FindLocation("SanAugustineResidence")];
	aref arItems, boxItems;
	ref rItem;
	string sName;
	makearef(arItems, PChar.items);
	makearef(boxItems, location.private1.items);
	int iItemsNum = GetAttributesNum(arItems);
	for(int i=0; i<iItemsNum; i++)
	{
		sName = GetAttributeName(GetAttributeN(arItems, i));
		rItem = ItemsFromID(sName);
		if (rItem.ItemType != "QUESTITEMS")
		{
			boxItems.(sName) = PChar.items.(sName);
		}
	}
	location.private1.money = sti(PChar.money);	
	location.private1 = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
	RemoveAllCharacterItems(PChar, true);
	RemoveItems(pchar, "letter_svenson", 1);
	AddQuestRecord("BaronReturn", "6");
	LSC_SetChimisetInJail();
	// кладем письмо в сундук
	ref rloc = &Locations[FindLocation("TartarusPrison")];
	rloc.private2.items.letter_chad = 1;
}

void LSC_TalkWithCapper()// разговор с Каппером - подготовка
{
	//ставим охранников-пиратов
	int iRank = 20+MOD_SKILL_ENEMY_RATE+2;
	int iScl = 60;
	for (i=1; i<=3; i++)
	{
		if (i == 3)
		{
			sld = GetCharacter(NPC_GenerateCharacter("ChadGuard_"+i, "mush_ctz_8", "man", "mushketer", iRank, PIRATE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "bullet", iScl+50);
			sld.dialog.Filename = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "ChadGuard";	
			sld.greeting = "HUNTER"; 
			sld.MusketerDistance = 0;
			ChangeCharacterAddressGroup(sld, "Tartarusprison", "goto", "goto6");
		}
		else
		{	
			sld = GetCharacter(NPC_GenerateCharacter("ChadGuard_"+i, "citiz_4"+(i+6), "man", "man", iRank, PIRATE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol4", "bullet", iScl+50);
			sld.dialog.Filename = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "ChadGuard";
			ChangeCharacterAddressGroup(sld, "Tartarusprison", "goto", "goto"+i);
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_warrior_DialogEnable(sld, true);
		LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LSC_ChadGuardAttack_Fail");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
	}
	}
	sld = characterFromId("Capper");
	sld.dialog.currentnode = "Chimiset";
	sld.cirassId = Items_FindItemIdx("cirass1");
	LAi_SetActorType(pchar);
	DoQuestFunctionDelay("LSC_TalkWithCapperGo", 2.0);
	GiveItem2Character(sld, "key_capper");
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	// двери к Мэри и Дональду Гринспи закрываем
	LocatorReloadEnterDisable("LostShipsCity_town", "reload60", true);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload61", true);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload48", true);
}

void LSC_TalkWithCapperGo(string qName)// разговор с Каппером - старт
{
	sld = characterFromId("Capper");
	LAi_ActorDialogNow(pchar, sld, "", -1);
}

void LSC_SetChimisetInJail()// Чимисет в клетке
{
	sld = characterFromId("Chimiset");
	sld.dialog.currentnode = "KillChad";
	LAi_SetStayTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, "Tartarusprison", "quest", "prison1");
	LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LSC_Chimiset_ActivateDialog");
	ref rItm = ItemsFromID("crowbar");
	rItm.shown = true;
	rItm.startLocation = "Tartarusprison";
	rItm.startLocator = "qitem";
}

void LSC_Fightfail_Final(string qName)// завалили колдуна
{
	sld = characterFromId("Capper");
	sld.dialog.currentnode = "Fightfail_Final";
}

void LSC_ChadGuardAttack(string qName)// драка с Чадом и охраной
{
	sld = CharacterFromID("ChadGuard_1");
	sld.dialog.currentnode = "ChadGuard_Attack";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);
}

void LSC_LetterChad_Find(string qName)// нашли письмо
{
	pchar.quest.LSC_TartarusExit1.win_condition.l1 = "locator";
	pchar.quest.LSC_TartarusExit1.win_condition.l1.location = "Tartarusprison";
	pchar.quest.LSC_TartarusExit1.win_condition.l1.locator_group = "reload";
	pchar.quest.LSC_TartarusExit1.win_condition.l1.locator = "reload1";
	pchar.quest.LSC_TartarusExit1.win_condition.l2 = "item";
	pchar.quest.LSC_TartarusExit1.win_condition.l2.item = "key_capper";
	pchar.quest.LSC_TartarusExit1.function = "LSC_TartarusExit1_Open";
	pchar.quest.LSC_TartarusExit2.win_condition.l1 = "locator";
	pchar.quest.LSC_TartarusExit2.win_condition.l1.location = "Tartarusprison";
	pchar.quest.LSC_TartarusExit2.win_condition.l1.locator_group = "reload";
	pchar.quest.LSC_TartarusExit2.win_condition.l1.locator = "reload2";
	pchar.quest.LSC_TartarusExit2.win_condition.l2 = "item";
	pchar.quest.LSC_TartarusExit2.win_condition.l2.item = "key_capper";
	pchar.quest.LSC_TartarusExit2.function = "LSC_TartarusExit2_Open";
	pchar.quest.LSC_TartarusExit.win_condition.l1 = "ExitFromLocation";
	pchar.quest.LSC_TartarusExit.win_condition.l1.location = "Tartarusprison";
	pchar.quest.LSC_TartarusExit.function = "LSC_TartarusExit";
	AddQuestRecord("SharkHunt", "5");
}

void LSC_TartarusExit1_Open(string qName)// открываем двери
{
	PlaySound("interface\key.wav");
	LocatorReloadEnterDisable("Tartarusprison", "reload1", false);
}

void LSC_TartarusExit2_Open(string qName)// открываем двери
{
	PlaySound("interface\key.wav");
	LocatorReloadEnterDisable("Tartarusprison", "reload2", false);
}

void LSC_TartarusExit(string qName)// Чимисета к себе на корабль
{
	sld = characterFromId("Chimiset");
	sld.dialog.currentnode = "Chimiset_1";
	ChangeCharacterAddressGroup(sld, "ProtectorFisher", "sit", "sit1");
	LAi_SetHuberType(sld);
	sld = characterFromId("Dodson");
	sld.dialog.currentnode = "Chad_die"; // ноду Акуле
	sld.quest.takeitems = "true"; // на возврат вещей
}

void LSC_EddyTalk(string qName)// Эдди к разговору
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = characterFromId("Eddy");
	sld.dialog.currentnode = "Friend";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void LSC_CreateAdolfClone()// ставим клона Адольфа
{
	int iRank = 20+MOD_SKILL_ENEMY_RATE+5;
	int iScl = 50;
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Adolf_Clon", "Adolf", "man", "man", iRank, PIRATE, -1, true, "quest"));
	sld.name = StringFromKey("Saga_18");
	sld.lastname = StringFromKey("Saga_19");
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_09", "pistol6", "bullet", iScl*2);
	sld.dialog.filename   = "Quest\LSC\Citizen\LSC_Adolf.c";
	sld.dialog.currentnode = "Adolf";
	sld.greeting = "marginal";
	sld.cirassId = Items_FindItemIdx("cirass1");
	LAi_RemoveLoginTime(sld);
	LAi_SetLoginTime(sld, 19.0, 23.0);
	LAi_SetSitType(sld);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	GiveItem2Character(sld, "key_gun"); // ключ от сундука со штуцером
	GiveItem2Character(sld, "letter_chad"); //письмо
	ChangeItemDescribe("letter_chad", "itmdescr_letter_adolf");
	ChangeCharacterAddressGroup(sld, "SantaFlorentinaShipInside4", "sit", "sit1");
}

void LSC_AdolfLetter(string qName)// нашли письмо
{
	chrDisableReloadToLocation = false;//открыть локацию
	AddQuestRecord("SharkHunt", "16");
	// ставим прерывание на полночь
	SetFunctionTimerCondition("LSC_CyclopCheck", 0, 0, 1, false); 
}

void LSC_CyclopCheck(string qName)// проверяем, где находится ГГ в полночь
{
	if (pchar.location == "SantaFlorentinaShipInside4") LSC_SetMaryNCyclopInCabin();
	else
	{
		pchar.quest.LSC_CyclopWait.win_condition.l1 = "location";
		pchar.quest.LSC_CyclopWait.win_condition.l1.location = "SantaFlorentinaShipInside4";
		pchar.quest.LSC_CyclopWait.function = "LSC_MaryNCyclopWait";
		pchar.quest.LSC_CyclopWaitOver.win_condition.l1 = "HardHour";
		pchar.quest.LSC_CyclopWaitOver.win_condition.l1.hour = 3.00;
		pchar.quest.LSC_CyclopWaitOver.function = "LSC_MaryNCyclopWaitOver";
	}
}

void LSC_SetMaryNCyclopInCabin() // Мэри и Циклоп входят
{
	chrDisableReloadToLocation = true;//закрыть локацию
	int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 70;
	// Мэри
	sld = characterFromId("Mary");
	LAi_SetHP(sld, 280+iScl, 280+iScl); // усилим
	if (MOD_SKILL_ENEMY_RATE > 7) sld.MultiFighter = 1.5; // мультифайтер
	sld.cirassId = Items_FindItemIdx("cirass1");
	GiveItem2Character(sld, "letter_chad_1");
	sld.dialog.currentnode = "Cabin";
	sld.greeting = "mary_4";
	ChangeCharacterAddressGroup(sld, "SantaFlorentinaShipInside4", "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_CharacterDisableDialog(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	// Марчелло
	sld = characterFromId("Marchello");
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol6", "bullet", iScl*2+170);
	sld.cirassId = Items_FindItemIdx("cirass1");
	sld.dialog.currentnode = "Cabin";
	if (MOD_SKILL_ENEMY_RATE > 7) sld.MultiFighter = 1.5; // мультифайтер
	ChangeCharacterAddressGroup(sld, "SantaFlorentinaShipInside4", "reload", "reload2");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void LSC_MaryNCyclopWait(string qName) // Мэри и Циклоп ждут
{
	pchar.quest.LSC_CyclopWaitOver.over = "yes"; //снять прерывание
	chrDisableReloadToLocation = true;//закрыть локацию
	int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 70;
	// Мэри
	sld = characterFromId("Mary");
	sld.greeting = "mary_4";
	LAi_SetHP(sld, 280+iScl, 280+iScl); // усилим
	if (MOD_SKILL_ENEMY_RATE > 7) sld.MultiFighter = 1.5; // мультифайтер
	sld.cirassId = Items_FindItemIdx("cirass1");
	GiveItem2Character(sld, "letter_chad_1");
	sld.dialog.currentnode = "Cabin";
	ChangeCharacterAddressGroup(sld, "SantaFlorentinaShipInside4", "barmen", "bar1");
	LAi_SetActorType(sld);
	LAi_CharacterDisableDialog(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	// Марчелло
	sld = characterFromId("Marchello");
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol6", "bullet", iScl*2+170);
	sld.cirassId = Items_FindItemIdx("cirass1");
	sld.dialog.currentnode = "Cabin_A";
	if (MOD_SKILL_ENEMY_RATE > 7) sld.MultiFighter = 1.5; // мультифайтер
	ChangeCharacterAddressGroup(sld, "SantaFlorentinaShipInside4", "goto", "goto6");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void LSC_MaryNCyclopWaitOver(string qName) // Мэри и Циклоп не дождались - тем хуже для геймера
{
	pchar.quest.LSC_CyclopWait.over = "yes"; //снять прерывание
	pchar.quest.LSC_CyclopAttack.win_condition.l1 = "location";
	pchar.quest.LSC_CyclopAttack.win_condition.l1.location = "LostShipsCity_town";
	pchar.quest.LSC_CyclopAttack.function = "LSC_MaryNCyclopAttack";
}

void LSC_MaryNCyclopAttack(string qName) // Мэри делает замануху на Эву
{
	pchar.questTemp.Saga.SharkHunt.TownAttack = "true";
	int iScl = 80;
	// Мэри
	sld = characterFromId("Mary");
	sld.greeting = "mary_2";
	LAi_SetHP(sld, 280+iScl, 280+iScl); // усилим
	if (MOD_SKILL_ENEMY_RATE > 7) sld.MultiFighter = 1.5; // мультифайтер
	sld.cirassId = Items_FindItemIdx("cirass1");
	GiveItem2Character(sld, "letter_chad_1");
	sld.dialog.currentnode = "Town";
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void LSC_MaryLetter(string qName)// нашли письмо
{
	chrDisableReloadToLocation = false;//открыть локацию
	AddQuestRecord("SharkHunt", "18");
	AddQuestRecordInfo("Chad_Mary_letter", "1");
	pchar.questTemp.Saga.SharkHunt = "find"; //флаг - покушение предотвращено
	sld = characterFromId("Dodson");
	sld.dialog.currentnode = "Mary_Die"; //даем ноду Акуле
}

// ---------------------------------вариант прохождения N: гоп-стоп------------------------------------------

void LSC_TartarusEntrance1_Open(string qName)// открываем двери
{
	PlaySound("interface\key.wav");
	LocatorReloadEnterDisable("LostShipsCity_town", "reload51", false);
}

void LSC_TartarusEntrance2_Open(string qName)// открываем двери
{
	PlaySound("interface\key.wav");
	LocatorReloadEnterDisable("LostShipsCity_town", "reload52", false);
}

void LSC_GotoShark(string qName)// посланник Акулы
{
	sld = GetCharacter(NPC_GenerateCharacter("LSC_SharkCureer", "citiz_44", "man", "man", 20, PIRATE, -1, true, "soldier"));
	FantomMakeCoolFighter(sld, 20, 50, 50, "blade_10", "pistol6", "bullet", 100);
	sld.dialog.FileName = "Quest\LSC\OtherNPC.c";
	sld.dialog.currentnode = "SharkCureer";
	sld.greeting = "town_pirate";
	LAi_SetImmortal(sld, true);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	sld = characterFromId("Chimiset");
	sld.lifeday = 0; // убираем Чимисета
	// прячем Чада
	sld = characterFromId("Capper");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	// на его место ставим нового тюремщика
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Prisonboss", "citiz_48", "man", "man", 30, PIRATE, -1, true, "soldier"));
	FantomMakeCoolFighter(sld, 30, 50, 50, "blade_16", "pistol4", "bullet", 200);
	sld.dialog.FileName = "Quest\LSC\OtherNPC.c";
	sld.dialog.currentnode = "Prisonboss";
	sld.greeting = "town_pirate";
	ChangeCharacterAddressGroup(sld, "TartarusPrison", "sit", "sit1");
	LAi_SetHuberType(sld);
	LAi_LocationFightDisable(&Locations[FindLocation("TartarusPrison")], true);//запретить драться в Тартарусе
	// закрываем дверь к Эдди
	LocatorReloadEnterDisable("LostShipsCity_town", "reload33", true);
	// пускаем слухи
	AddSimpleRumourCityTip(StringFromKey("Saga_20"), "LostShipsCity", 2, 2, "LSC", "");
	AddSimpleRumourCityTip(StringFromKey("Saga_21"), "LostShipsCity", 2, 2, "LSC", "");
	AddSimpleRumourCityTip(StringFromKey("Saga_22"), "LostShipsCity", 2, 2, "LSC", "");
	AddSimpleRumourCityTip(StringFromKey("Saga_23"), "LostShipsCity", 5, 2, "LSC", "");
	AddSimpleRumourCityTip(StringFromKey("Saga_24"), "LostShipsCity", 5, 2, "LSC", "");
}

void LSC_MeetingSharkAugustine(string qName)// Акула в полночь на Сан-Августине - готовим Каролину
{
	sld = characterFromId("Dodson");
	sld.dialog.currentnode = "Caroline";
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", "goto11_2"); // найти локатор
	LAi_SetStayTypeNoGroup(sld);
	sld = characterFromId("Facio");
	ChangeCharacterAddressGroup(sld, "none", "", ""); // спрячем Фацио
	ref rloc = &Locations[FindLocation("CarolineBank")];
	rloc.private1.items.letter_chad_1 = 1;
	ChangeItemDescribe("letter_chad_1", "itmdescr_letter_facio");
	sld = ItemsFromID("key_facio");
	sld.shown = true;
	sld.startLocation = "CarolineBank";
	sld.startLocator = "key1"; //положим ключ на стол
	// если ГГ не явится
	pchar.quest.LSC_MeetingAugustineOver.win_condition.l1 = "Timer";
	pchar.quest.LSC_MeetingAugustineOver.win_condition.l1.date.hour  = 1.00;
	pchar.quest.LSC_MeetingAugustineOver.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
	pchar.quest.LSC_MeetingAugustineOver.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
	pchar.quest.LSC_MeetingAugustineOver.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
	pchar.quest.LSC_MeetingAugustineOver.function = "LSC_MeetingAugustineOver";
}

void LSC_MeetingAugustineOver(string qName)// не пришли к Акуле
{
	sld = characterFromId("Dodson");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload25", "none", "", "", "LSC_SharkDie", -1);
}

void LSC_CarolineEnter(string qName)// входим в Каролину
{
	chrDisableReloadToLocation = true;//закрыть локацию
	pchar.quest.LSC_MeetingAugustineOver.over = "yes"; //снять прерывание
	LocatorReloadEnterDisable("LostShipsCity_town", "reload25", true);
	sld = characterFromId("Dodson");
	sld.dialog.currentnode = "caroline_2";
	LAi_SetActorType(sld);
	LAi_SetActorType(pchar);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
	LAi_ActorTurnToCharacter(sld, pchar);
	SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
}

void LSC_FacioReturn(string qName)// вертаем Фацио
{
	sld = characterFromId("Facio");
	sld.dialog.currentnode = "First time";
	ChangeCharacterAddressGroup(sld, "CarolineBank", "sit", "sit1");
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	ref location = &Locations[FindLocation("CarolineBank")];
	location.private1.key = "key3"; // запираем сундук
}

void LSC_FindLetterFacio(string qName)// нашли письмо Фацио
{
	sld = characterFromId("Grinspy");
	sld.dialog.currentnode = "shark"; // ноду Дональду Гринспи
	AddQuestRecord("SharkHunt", "25");
	AddQuestRecordInfo("Letter_Facio", "1");
}

// ---------------------------------вариант прохождения M: Мэри------------------------------------------
void LSC_FindMary(string qName)// ГГ круто повезло - он нашел Мэри!
{
	pchar.questTemp.LSC = "mary";
	LocatorReloadEnterDisable("CeresSmithy", "reload6", true);
	LocatorReloadEnterDisable("CeresSmithy", "reload7", true); // закрываем выходы
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
	LocatorReloadEnterDisable("LostShipsCity_town", "reload2", true); //закрываем кладовку со стороны моря
	pchar.quest.LSC_entry_pantry.over = "yes"; //снять прерывание на арест
	// устанавливаем врагов
	for (i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("EnemyMary_"+i, "citiz_58", "man", "man", 5, PIRATE, -1, true, "soldier"));
		LAi_SetHP(sld, 300, 300); 
		SetSelfSkill(sld, 60, 60, 60, 50, 60);
		SetRandSPECIAL(sld);
		SetCharacterPerk(sld, "BasicDefense");
		SetCharacterPerk(sld, "AdvancedDefense");
		SetCharacterPerk(sld, "CriticalHit");
		SetCharacterPerk(sld, "SwordplayProfessional");
		GiveItem2Character(sld, "blade_10");
		sld.equip.blade = "blade_10";
		GiveItem2Character(sld, "pistol1");
		EquipCharacterbyItem(sld, "pistol1");
		GiveItem2Character(sld, "cirass1");
		EquipCharacterbyItem(sld, "cirass1");
		LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
		TakeNItems(sld, "bullet", 50);
		AddItems(sld, "gunpowder", 50);
		TakeNItems(sld, "potion2", 3);
		LAi_SetWarriorType(sld);
		LAi_CharacterDisableDialog(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		ChangeCharacterAddressGroup(sld, "CeresSmithy", "barmen", "bar"+i);
	}
	// Мэри в отдельную группу
	sld = characterFromId("Mary");
	sld.greeting = "mary_1";
	GiveItem2Character(sld, "letter_chad_1");
	LAi_group_Register("TMP_FRIEND"); // спецгруппа
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "Tmp_friend");
	// установим отношения
	LAi_group_SetRelation("EnemyFight", "Tmp_friend", LAI_GROUP_ENEMY);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_SetRelation("Tmp_friend", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
	LAi_group_FightGroups("EnemyFight", "Tmp_friend", true);
	LAi_group_SetCheck("EnemyFight", "LSC_EnemiesMaryDie");
}

void LSC_DieMaryletter(string qName) //Мэри убита - нашли письмо на ней, но лучше переиграть, Элен её не стоит))
{
	LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
	LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем выходы
	AddQuestRecord("SharkHunt", "30");
	AddQuestRecordInfo("Chad_Mary_letter", "2");
}

void LSC_AxelReturnStore(string qName) // вертаем Акселя на место
{
	sld = characterFromId("Axel");
	LAi_SetOwnerType(sld);
	ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "barmen", "stay");
	LAi_group_MoveCharacter(sld, "LSC_NARVAL");
}

void LSC_WhiskeyPoison_exit(string qName) // вышли на улицы - запускаем таймер
{
	DoQuestFunctionDelay("LSC_WhiskeyPoisonAlready", 15.0);
}

void LSC_WhiskeyPoisonAlready(string qName) // виски отравлен
{
	log_testinfo("Если вы сейчас не на 'Эве' - то Чад успел отравить виски");
	pchar.questTemp.LSC.Whiskey_poison = "true";
}

void LSC_WhiskeyPoison_SF(string qName) // на Санта-Флорентину - наиболее ожидаемый вариант
{
	pchar.questTemp.LSC.Attack = true; // обработка в АИ
	chrDisableReloadToLocation = true;//закрыть локацию
	pchar.questTemp.LSC.Florentina = "true"; // был на Флорентине
	sld = CharacterFromID("LSC_Adolf");
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "SantaFlorentinaShipInside4", "goto", "goto2");
	sld.SaveItemsForDead = true; 
	sld.DontClearDead = true;
	LAi_SetImmortal(sld, false);
	RemoveAllCharacterItems(sld, true);
	GiveItem2Character(sld, "key_gun"); // ключ от сундука со штуцером
	DoQuestFunctionDelay("LSC_KillAdolf_SF", 2.0); // убить Адольфа
	// ставим толстого нарвала
	int iRank = 22+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 80;
	sld = GetCharacter(NPC_GenerateCharacter("LSC_AdolfKiller", "citiz_58", "man", "man", iRank, PIRATE, -1, true, "quest"));
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_13", "pistol4", "bullet", iScl*2);
	sld.cirassId = Items_FindItemIdx("cirass1");
	if (MOD_SKILL_ENEMY_RATE > 7) sld.MultiFighter = 1.5; // мультифайтер
	LAi_SetWarriorType(sld);
	LAi_warrior_SetStay(sld, true);
	LAi_warrior_DialogEnable(sld, false);
	ChangeCharacterAddressGroup(sld, "SantaFlorentinaShipInside4", "goto", "goto2");
	GiveItem2Character(sld, "letter_chad");
	ChangeItemDescribe("letter_chad", "itmdescr_letter_adolf_1");
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
}

void LSC_KillAdolf_SF(string qName) // убить Адольфа
{
	sld = CharacterFromID("LSC_Adolf");
	LAi_KillCharacter(sld);
}

void LSC_letterAdolf_SF(string qName) // нашли письмо на нарвале
{
	chrDisableReloadToLocation = false;//открыть локацию
	AddQuestRecord("SharkHunt", "38");
	if (!CheckAttribute(pchar, "questTemp.LSC.Dodson_poison") && !CheckAttribute(pchar, "questTemp.LSC.Dodson_warning")) // не было разговора и не предупрежден
	{
		sld = CharacterFromID("Dodson");
		sld.dialog.currentnode = "poison";
		LAi_SetGroundSitTypeNoGroup(sld);
		ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto10"); // Акула отравился
	}
}

void LSC_WhiskeyPoison_AE(string qName) // на Эве
{
	pchar.quest.LSC_Whiskeypoison_SF.over = "yes"; //снять прерывание на Флорентину, если осталось
	pchar.questTemp.LSC.Attack = true; // обработка в АИ
	chrDisableReloadToLocation = true;//закрыть локацию
	LocatorReloadEnterDisable("LostShipsCity_town", "reload20", false);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload24", false);// открываем вход к Фацио
	int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 60;
	// ставим Чада
	sld = CharacterFromID("Capper");
	sld.dialog.currentnode = "Aeva_attack";
	sld.cirassId = Items_FindItemIdx("cirass1");
	LAi_SetActorType(sld);
	GiveItem2Character(sld, "rat_poison"); // мышьяк
	GiveItem2Character(sld, "key_capper"); // ключ от Тартаруса
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true; 
	ChangeCharacterAddressGroup(sld, "AvaShipInside3", "quest", "quest4");
	// нарвалы
	for (i=1; i<=3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("ChadNarval_"+i, "citiz_5"+(i+3), "man", "man", iRank, PIRATE, -1, true, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol4", "bullet", iScl*2);
		sld.cirassId = Items_FindItemIdx("cirass1");
		LAi_SetActorType(sld);
		LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, "AvaShipInside3", "quest", "quest"+i);
	}
	if (!CheckAttribute(pchar, "questTemp.LSC.Whiskey_poison")) // виски не успели отравить
	{
		// ставим Фацио
		pchar.questTemp.LSC.Whiskey_clear = "true";
		sld = CharacterFromID("Facio");
		sld.dialog.currentnode = "whiskey";
		sld.greeting = "facio_2";
		sld.quest.poisonnode = 2;
		LAi_SetStayType(sld);
		LAi_SetImmortal(sld, true);
		ChangeCharacterAddressGroup(sld, "AvaShipInside3", "quest", "quest5");
		sld = CharacterFromID("Capper");
		GiveItem2Character(sld, "cask_whisky"); // бочонок чистого виски
		sld.dialog.currentnode = "Aeva_attack_2";
	}
	else
	{
		if (!CheckAttribute(pchar, "questTemp.LSC.Dodson_poison")  && !CheckAttribute(pchar, "questTemp.LSC.Dodson_warning")) // не было разговора
		{
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "poison";
			ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto10"); // Акула отравился
			LAi_SetGroundSitTypeNoGroup(sld);
		}
	}
}

void LSC_SetCyclop_Fl(string qName) // Циклопа на Флерон - вар. если не уберег Мэри
{
	int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 70;
	pchar.questTemp.LSC.Attack = true; // обработка в АИ
	sld = characterFromId("Marchello");
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol4", "bullet", iScl+150);
	sld.cirassId = Items_FindItemIdx("cirass1");
	if (MOD_SKILL_ENEMY_RATE > 7) sld.MultiFighter = 1.8; // мультифайтер
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "FleuronTavern", "rld", "stay2");
}

void LSC_CheckEnemyDistance() // расчет дистанции до локатора с НПС на Флорентине, Эве, Флероне и Диффиндуре
{
	float fdist;
	if (pchar.location == "SantaFlorentinaShipInside4")
	{
		if (GetCharacterDistByLoc(pchar, "goto", "goto2", &fdist))
		{
			if (fdist < 5.0) LSC_SF_NarvalAttack();
		}
	}
	if (pchar.location == "AvaShipInside3")
	{
		if (GetCharacterDistByLoc(pchar, "quest", "quest3", &fdist))
		{
			if (fdist < 7.0) LSC_Aeva_CapperGo();
		}
	}
	if (pchar.location == "FleuronTavern")
	{
		if (GetCharacterDistByLoc(pchar, "rld", "stay2", &fdist))
		{
			if (fdist < 3.0) LSC_Fleuron_CyclorAttack();
		}
	}
	if (pchar.location == "FernandaDiffIndoor")
	{
		if (GetCharacterDistByLoc(pchar, "goto", "goto1", &fdist))
		{
			if (fdist < 5.0) LSC_NatanielSeeDaniel();
		}
	}
}

void LSC_SF_NarvalAttack() // атакует нарвал у трупа Адольфа
{
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
	DeleteAttribute(pchar, "questTemp.LSC.Attack");
	sld = CharacterFromID("LSC_AdolfKiller");
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "LSC_AdolfKillerDie");
}

void LSC_Aeva_CapperGo() // старт разговора Каппера - итог - бой
{
	DeleteAttribute(pchar, "questTemp.LSC.Attack");
	sld = CharacterFromID("Capper");
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);
}

void LSC_Fleuron_CyclorAttack() // Циклоп атакует
{
	DeleteAttribute(pchar, "questTemp.LSC.Attack");
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
	sld = CharacterFromID("Marchello");
	if (MOD_SKILL_ENEMY_RATE > 7) sld.MultiFighter = 1.5; // мультифайтер
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "LSC_CyclopDie_Fl");
}

void LSC_RescueMary(string qName) // бежим на помощь Мэри
{
	pchar.questTemp.LSC.RescueMary = "true";
	pchar.questTemp.NoFast = true; // запрет ускорения
	SetShowTimer(100.0); // не так уж и много - поспешим!
	DoQuestFunctionDelay("LSC_SetAlarmMusic", 1.0);
	chrDisableReloadToLocation = true; // закрыть локацию
	InterfaceStates.Buttons.Save.enable = false; //запретить сохраняться
	bDisableFastReload = true;//на всяк случай продублирую
	pchar.GenQuest.CannotWait = true;//и это тоже
	pchar.quest.LSC_runtoMary.win_condition.l1 = "locator";
	pchar.quest.LSC_runtoMary.win_condition.l1.location = "LostShipsCity_town";
	pchar.quest.LSC_runtoMary.win_condition.l1.locator_group = "reload";
	pchar.quest.LSC_runtoMary.win_condition.l1.locator = "reload60";
	pchar.quest.LSC_runtoMary.function = "LSC_enterMaryCabin";
}

void LSC_SetAlarmMusic(string qName) // бежим по городу, не путаемся в фалдах камзола и не спотыкаемся :)
{
	SetMusic("music_teleport");
	log_info(StringFromKey("Saga_25"));
	PlaySound("interface\notebook.wav");
}

void LSC_enterMaryCabin(string qName) // входим в каюту к Мэри
{
	DoQuestReloadToLocation("CeresSmithy", "reload", "reload6", "LSC_CyclopInMaryCabin");
}

void LSC_RescueMaryFail() // опоздал к Мэри... лучше переигрывай!
{
	AddQuestRecord("SharkHunt", "49");
	pchar.questTemp.LSC.FailMary = "true";
}

void LSC_ContinueAfterMaryCabin() // завершающая функция
{
	pchar.questTemp.Saga.SharkHunt = "whiskey_final"; // меняем флаг
	InterfaceStates.Buttons.Save.enable = true; //разрешить сохраняться
	chrDisableReloadToLocation = false;//открыть локацию
	if (!CheckAttribute(pchar, "questTemp.LSC.Whiskey_clear")) // если виски был отравлен
	{
		pchar.quest.LSC_WhiskeyStoryFinal.win_condition.l1 = "location";
		pchar.quest.LSC_WhiskeyStoryFinal.win_condition.l1.location = "LostShipsCity_town";
		pchar.quest.LSC_WhiskeyStoryFinal.function = "LSC_WhiskeyStoryFinal"; // адмирал зовет
	}
	// вместо Чада ставим нового тюремщика
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Prisonboss", "citiz_48", "man", "man", 30, PIRATE, -1, true, "soldier"));
	FantomMakeCoolFighter(sld, 30, 50, 50, "blade_16", "pistol4", "bullet", 200);
	sld.dialog.FileName = "Quest\LSC\OtherNPC.c";
	sld.dialog.currentnode = "Prisonboss_M";
	sld.greeting = "town_pirate";
	ChangeCharacterAddressGroup(sld, "TartarusPrison", "sit", "sit1");
	LAi_SetHuberType(sld);
	LAi_LocationFightDisable(&Locations[FindLocation("TartarusPrison")], true);//запретить драться в Тартарусе
	LSC_OpenTartarusDoors();// открыть наружные двери Тартаруса
	sld = CharacterFromID("Facio");
	sld.dialog.currentnode = "First time";
	sld.greeting = "facio_1";
}

// --> штучки с Мэри
void LSC_MaryLove() // провести ночь с Мэри в LSC
{
	pchar.GenQuest.FrameLockEsc = true;
	LSC_MaryLoveWaitTime();
	SetMusic("music_romantic");
	SetLaunchFrameFormParam("", "", 0, 28);
	SetLaunchFrameFormPic("loading\inside\censored1.tga");
	PlayStereoSound("sex\sex"+(rand(9)+1)+".wav");
    LaunchFrameForm();
	if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
	{
		AddCharacterHealth(pchar, 24);
		AddCharacterMaxHealth(pchar, 2.0);
	}
	else 
	{
		AddCharacterHealth(pchar, 12); // Мэри восстанавливает здоровье лучше всех и без бальзама
		AddCharacterMaxHealth(pchar, 1.0);
	}
	LAi_SetCurHPMax(pchar);
	DoQuestFunctionDelay("LSC_MaryLoveMorning", 28.0);
}

void LSC_MaryEveneng() // Sinistra катсцена с поцелуями. Проводим вечер+ночь с Мэри в LSC
{
	//if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
	StartQuestMovie(true, false, true);
	locCameraFromToPos(46.77, 4.10, 99.07, true, 46.30, 2.45, 96.16);
	pchar.GenQuest.FrameLockEsc = true;
	SetMusic("music_romantic");
	sld = characterFromId("Mary");
	ChangeCharacterAddressGroup(sld, "CeresSmithy", "sit", "sit3");
	LAi_SetSitType(sld);
	ChangeCharacterAddressGroup(pchar, "CeresSmithy", "sit", "sit4");
	LAi_SetSitType(pchar);
	DoQuestFunctionDelay("LSC_MaryLoveVstaem", 4.5);
}

void LSC_MaryLoveVstaem(string qName)
{
	LAi_Fade("", "");
	DoQuestFunctionDelay("LSC_MaryLoveKiss", 0.5);
}

void LSC_MaryLoveKiss(string qName)
{
	locCameraFromToPos(44.41, 4.28, 95.70, true, 44.39, 2.25, 92.55);
	sld = characterFromId("Mary");
	ChangeCharacterAddressGroup(sld, "CeresSmithy", "goto", "goto11");
	TeleportCharacterToPosAy(sld, 44.90, 2.75, 93.00, -1.50);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "kiss", "1", 7.5);
	ChangeCharacterAddressGroup(pchar, "CeresSmithy", "goto", "goto10");
	TeleportCharacterToPosAy(pchar, 44.30, 2.75, 93.00, 1.50);
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "kiss", "1", 7.5);
	
	DoQuestFunctionDelay("LSC_MaryLoveKiss_2", 3.0);
	DoQuestFunctionDelay("LSC_MaryLoveStart", 7.5);
}

void LSC_MaryLoveKiss_2(string qName)
{
	locCameraFromToPos(45.30, 4.43, 93.62, true, 43.61, 2.65, 92.50);
}

void LSC_MaryLoveStart(string qName) // к функции выше
{
	sld = characterFromId("Mary");
	LAi_SetOwnerType(sld);
	LAi_SetPlayerType(pchar);
	ChangeCharacterAddressGroup(sld, "CeresSmithy", "goto", "goto11");
	ChangeCharacterAddressGroup(pchar, "CeresSmithy", "goto", "goto10"); // на обрыв эскейпом
	LSC_MaryLoveWaitTime();
	SetLaunchFrameFormParam("", "", 0, 14);
	SetLaunchFrameFormPic("loading\inside\censored1.tga");
	PlayStereoSound("sex\sex"+(rand(9)+1)+".wav");
    LaunchFrameForm();
	if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
	{
		AddCharacterHealth(pchar, 24);
		AddCharacterMaxHealth(pchar, 2.0);
	}
	else 
	{
		AddCharacterHealth(pchar, 12); // Мэри восстанавливает здоровье лучше всех и без бальзама
		AddCharacterMaxHealth(pchar, 1.0);
	}
	LAi_SetCurHPMax(pchar);
	DoQuestFunctionDelay("LSC_MaryLoveMorning", 14.0);
}

void LSC_MaryTavern(string qName) // посидеть в таверне с Мэри в LSC
{
	SetMusic("spa_music_tavern");
	AddMoneyToCharacter(pchar, -500);
	DoQuestCheckDelay("LSC_MaryTavernReturn", 32.5);
}

void LSC_MaryLoveWaitTime() // перемотка времени
{
	int iTime, iAddTime;
	iTime = sti(environment.time);
	if (iTime >= 21) iAddTime = 24 - iTime + 7;
	if (iTime < 7) iAddTime = 7 - iTime;
	if (iTime >= 7 && iTime < 21) iAddTime = 24  + 7 - iTime;
	StoreDayUpdate();
	WaitDate("",0,0,0,iAddtime,5);
	RecalculateJumpTable();
	RefreshWeather();
	RefreshLandTime();
}

void LSC_MaryLoveMorning(string qName) // завершение функций выше
{
	EndQuestMovie();
	locCameraFromToPos(44.40, 4.63, 98.15, true, 43.11, 2.82, 99.44);
	sld = characterFromId("Mary");
	sld.dialog.currentnode = "LSC_love_morning";
	ChangeCharacterAddressGroup(sld, "CeresSmithy", "goto", "goto11");
	ChangeCharacterAddressGroup(pchar, "CeresSmithy", "goto", "goto10");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}
	// --> палаш 'Нарвал' для Мэри
void LSC_NarvalFerrum(string qName) // нашли гигантский кусок метеорита
{
	AddQuestRecord("LSC", "20");
	AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
}	
	
void LSC_NarvalBladeForMary(string qName) // палаш готов
{
	sld = characterFromId("Mary");
	sld.quest.narval_blade = "true";
	sld = characterFromId("Schmidt");
	sld.quest.narval_blade = "ready";
	sld.dialog.currentnode = "Jurgen";
	log_testinfo("Палаш готов!");
}

void LSC_GotoPresentMary(string qName) // идем к Юргену
{
	LocatorReloadEnterDisable("CeresSmithy", "reload5", false);
	LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
	LAi_SetActorType(pchar);
	sld = characterFromId("Mary");
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "reload", "reload62");
	LAi_ActorGoToLocator(sld, "reload", "reload65", "LSC_EnterPresentMary", -1);
	LAi_ActorFollow(pchar, sld, "", -1);
}
// <-- штучки с Мэри

void LSC_SetDexterAdmiral(string qName) // Декстера - в адмиралы
{
	sld = characterFromId("Dexter");
	sld.dialog.currentnode = "admiral_7";
	ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "sit", "sit1");
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "LSC_SHARK");
}

void LSC_WhiskeyStoryFinal(string qName) // посланник от адмирала
{
	sld = GetCharacter(NPC_GenerateCharacter("LSC_SharkCureer", "citiz_44", "man", "man", 20, PIRATE, -1, true, "soldier"));
	FantomMakeCoolFighter(sld, 20, 50, 50, "blade_10", "pistol6", "bullet", 100);
	sld.dialog.FileName = "Quest\LSC\OtherNPC.c";
	sld.dialog.currentnode = "SharkCureer_3";
	sld.greeting = "town_pirate";
	LAi_SetImmortal(sld, true);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
	{
		sld = characterFromId("Dodson");
		sld.dialog.currentnode = "whyskey_final";
		LAi_SetHuberType(sld);
		ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "sit", "sit1");
		LAi_CharacterEnableDialog(sld);
		sld = characterFromId("Dexter");
		sld.dialog.currentnode = "plan";
		LAi_SetHuberType(sld);
		ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "sit", "sit4");
		LAi_CharacterDisableDialog(sld);
	}
}

void LSC_WhiskeyStoryFinal_1(string qName) // к адмиралу
{
	sld = characterFromId("Dodson");
	sld.dialog.currentnode = "whyskey_final";
	LAi_SetHuberType(sld);
	ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "sit", "sit1");
	LAi_CharacterEnableDialog(sld);
	sld = characterFromId("Dexter");
	sld.dialog.currentnode = "plan";
	LAi_SetHuberType(sld);
	ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "sit", "sit4");
	LAi_CharacterDisableDialog(sld);
}

//-------------------------------------общая для всех вариантов часть----------------------------------------

void LSC_SetWhiteBoy()// ставим Оле
{
	sld = characterFromId("Ole");
	sld.dialog.currentnode = "store";
	ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "goto", "goto1");
	LAi_SetStayTypeNoGroup(sld);
	LAi_SetLoginTime(sld, 10.0, 17.0);
}

void LSC_PrepareUnderwater_Check(string qName)// ремонт водолазного костюма - проверка
{
	log_Testinfo("Костюм починен!");
	pchar.questTemp.LSC = "underwater_check";
}

void LSC_PrepareUnderwater(string qName)// готовы к первому погружению
{
	log_Testinfo("К погружению готовы!");
	pchar.questTemp.LSC = "underwater_prepare";
}

void LSC_takeUnderwater(string qName)// выдача скафандра
{
	GiveItem2Character(pchar, "underwater"); 
	PlaySound("interface\notebook.wav");
	//Log_Info("Вы получили водолазный скафандр");
}

void LSC_underwaterDeathTimer(string qName) // время нахождения под водой истекло
{
	GameOver("land");
}

void LSC_FindUnderwaterDolly(string qName) // нашли статую
{
	pchar.questTemp.LSC.FindDolly = "true";
	pchar.questTemp.Saga.BaronReturn = "second_teleport";
	ref rLoc = &Locations[FindLocation("underwater")];
	if (CheckAttribute(rLoc, "canteleport"))
	{
		AddQuestRecord("LSC", "12");
		if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) AddQuestUserData("LSC", "sText", StringFromKey("Saga_26")); 
	}
	else
	{
		AddQuestRecord("LSC", "13");
		if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) AddQuestUserData("LSC", "sText", StringFromKey("Saga_27")); 
	}
	AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
	QuestPointerDelLoc("UnderWater", "quest", "dolly");
}

void LSC_ReadyUnderwater(string qName)// готовы к погружениям
{
	log_Testinfo("К погружению готовы!");
	pchar.questTemp.LSC.UW_ready = "true";
}

// --> борьба с дикими геймерами
void LSC_GameOverPrison(string qName) 
{
	DoQuestCheckDelay("hide_weapon", 0.5);//убрать оружие
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	sld = characterFromId("Dexter");
	sld.dialog.currentnode = "LSC_GameOverPrison";
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetImmortal(sld, true);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	for (i=1; i<=5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("DexterGuard_"+i, "mush_ctz_7", "man", "mushketer", 40, PIRATE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 40, 100, 100, "", "mushket1", "bullet", 200);
		LAi_CharacterDisableDialog(sld);
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
		LAi_SetImmortal(sld, true);
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}
// <-- борьба с дикими геймерами

// -------------------------------------------- мини-квесты LSC --------------------------------------------
// --> пей до дна
void LSC_DrinkOver(string qName) // просрочил
{
	sld = characterFromId("LSC_Leonard");
	sld.dialog.currentnode = "First time";
	AddQuestRecord("LSC_Drink", "7");
	CloseQuestHeader("LSC_Drink");
	DeleteAttribute(pchar, "questTemp.LSC.Drink");
}

void LSC_DrinkDelete(string qName) // подчистка квеста
{
	log_Testinfo("Зачищаем квест");
	sld = characterFromId("Facio");
	sld.dialog.currentnode = "First time";
	ChangeCharacterAddressGroup(sld, "CarolineBank", "sit", "sit1");
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	sld = characterFromId("LSC_Leonard");
	sld.dialog.currentnode = "First time";
	ChangeCharacterAddressGroup(sld, "FleuronTavern", "sit", "sit5");
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	DeleteAttribute(pchar, "questTemp.LSC.Drink");
	if (CheckAttribute(pchar, "GenQuest.CamShuttle")) DeleteAttribute(pchar, "GenQuest.CamShuttle");
	CloseQuestHeader("LSC_Drink");
}

void LSC_DrinkPrepare(string qName) // подготовка Фацио и Леонарда
{
	sld = characterFromId("Facio");
	sld.dialog.currentnode = "drink_8";
	ChangeCharacterAddressGroup(sld, "FleuronTavern", "goto", "goto1");
	LAi_SetStayTypeNoGroup(sld);
	sld = characterFromId("LSC_Leonard");
	ChangeCharacterAddressGroup(sld, "FleuronTavern", "goto", "goto2");
	LAi_SetStayTypeNoGroup(sld);
	sld = ItemsFromID("potionrum");
	sld.shown = true;
	sld.startLocation = "FleuronTavern";
	sld.startLocator = "bottle";
}

void LSC_DrinkGo(string qName) // бухалово
{
	InterfaceStates.Buttons.Save.enable = false;
	bDisableCharacterMenu = true;//лоченые интерфейсы
	SetMusic("spa_music_tavern");
	locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1700);
	Pchar.FuncCameraFly = "";
	DoQuestFunctionDelay("LSC_DrinkResult", 32.5);
	if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
	{
		if (sti(pchar.questTemp.LSC.Drink.Chance) > 80) pchar.questTemp.LSC.Drink.Result = 1;
		else pchar.questTemp.LSC.Drink.Result = 2;
	}
	else pchar.questTemp.LSC.Drink.Result = 0;
}

void LSC_DrinkResult(string qName) // итоги
{
	locCameraResetState();
	InterfaceStates.Buttons.Save.enable = true;
	bDisableCharacterMenu = false;//лоченые интерфейсы
	ref chr = characterFromId("LSC_Leonard");
	LAi_SetActorType(chr);
	LAi_Fade("", "");
	switch (sti(pchar.questTemp.LSC.Drink.Result))
	{
		case 0: // тотем помог
			sld = characterFromId("Facio");
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorAnimation(sld, "Sit_Death", "OpenTheDoors", 2.7);
			chr.dialog.currentnode = "result_0";
			pchar.GenQuest.CamShuttle = 1;
		break;
		
		case 1: // обыграл, но нажрался
			sld = characterFromId("Facio");
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorAnimation(sld, "Sit_Death", "OpenTheDoors", 2.7);
			chr.dialog.currentnode = "result_1";
			pchar.GenQuest.CamShuttle = 3;
		break;
		
		case 2: // ужрался
			LAi_SetActorType(pchar);
			LAi_ActorSetSitMode(pchar);
			LAi_ActorAnimation(pchar, "Sit_Death", "OpenTheDoors", 2.7);
			chr.dialog.currentnode = "result_2";
			pchar.GenQuest.CamShuttle = 4;
		break;
	}
	DoQuestFunctionDelay("LSC_DrinkResult_1", 2.7);
	pchar.questTemp.LSC.Drink = "result";
	WaitDate("",0,0,0,3,5);
}

void LSC_DrinkResult_1(string qName) // итоги-1
{
	LAi_SetPlayerType(pchar);
	ref chr = characterFromId("Carpentero");
	sld = characterFromId("Facio");
	if (sti(pchar.questTemp.LSC.Drink.Result) < 2)
	{
		LAi_SetLayType(sld);
		ChangeCharacterAddressGroup(sld, "FleuronTavern", "quest", "lay1");
		sld.dialog.currentnode = "drunk";
		chr.quest.drink = "win";
		Achievment_Set("ach_70"); // ugeen 2016
	}
	else
	{
		sld.dialog.currentnode = "First time";
		ChangeCharacterAddressGroup(sld, "CarolineBank", "sit", "sit1");
		LAi_SetSitType(sld);
		LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
		chr.quest.drink = "fail";
	}
	sld = ItemsFromID("potionrum");
	sld.shown = false;
	DoQuestReloadToLocation("FleuronTavern", "goto", "goto1", "LSC_DrinkLeonardTalk");
}

void LSC_DrinkClearChest()
{

}
// <-- пей до дна

// --> тайна Санта-Люсии
void LSC_RingOver(string qName) // чистка квеста
{
	sld = characterFromId("LSC_Rishard");
	sld.dialog.currentnode = "First time";
	ChangeCharacterAddressGroup(sld, "FleuronTavern", "sit", "sit2");
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	if (!CheckAttribute(sld, "quest.ring_final")) AddQuestRecord("LSC_Ring", "2");
	CloseQuestHeader("LSC_Ring");
}

void LSC_RingStart(string qName) // готовы
{
	sld = characterFromId("LSC_Rishard");
	sld.dialog.currentnode = "ring_10";
	LAi_RemoveLoginTime(sld);
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "quest", "ring");
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "TMP_FRIEND");
}

void LSC_RingEnter(string qName) // входим
{
	pchar.quest.LSC_Ring_Over.over = "yes"; //снять прерывание
	SetLaunchFrameFormParam("Прошёл час..."+ NewStr() +"Вы добрались до разбитого корабля", "", 0, 6);//табличка
	LaunchFrameForm();
	WaitDate("", 0, 0, 0, 1, 10); //крутим время
	RecalculateJumpTable();
	DoQuestFunctionDelay("LSC_RingReload", 5.5);
}

void LSC_RingReload(string qName) // телепорт
{
	DoQuestReloadToLocation("ExternalRingInside", "reload", "reload1", "LSC_RingEnterInside");
}

void LSC_RingRishardTalk(string node) // говорилка Ришарда
{
	sld = characterFromId("LSC_Rishard");
	sld.dialog.currentnode = node;
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void LSC_RingSetItems() // раскладка итемзов
{
	for (i=1; i<=3; i++)
	{
		sld = ItemsFromID("purse"+i);
		sld.shown = true;
		sld.startLocation = "ExternalRingInside";
		sld.startLocator = "item"+i;
	}
}

void LSC_RingDeleteItemsBoxes(string qName)
{
	ref loc;
	aref arBox;
	string sName;
	for(int i=0; i<MAX_LOCATIONS; i++)
	{				
		loc = &locations[i];
		if (loc.id == "ExternalRingDeck" || loc.id == "ExternalRingInside" || loc.id == "ExternalRingCabin1")
		{	
			for(int n=1; n<=MAX_HANDLED_BOXES; n++)
			{
				sName = "private" + n;
				if (CheckAttribute(loc, sName))
				{					
					makearef(arBox, loc.(sName));
					DeleteAttribute(arBox, "items");
					arBox.items = "";
				}
				else break;
			}
		}
	}
	pchar.GenQuestBox.ExternalRingInside = true;
	pchar.GenQuestBox.ExternalRingInside.box1.items.jewelry5 = 1;
}
// <-- тайна Санта-Люсии

// --> Блудный сын - похождения Оле Кристиансена
void LSC_CheckOlePearl()
{
	if(chrDisableReloadToLocation) return; // belamour уже идёт другой квест
	sld = characterFromId("Ole");
	if (CheckAttribute(sld, "pearl_date") && GetNpcQuestPastDayParam(sld, "pearl_date") >= 20)
	{
		chrDisableReloadToLocation = true;//закрыть локацию
		if (sti(sld.quest.pearlqty) < 11) sld.dialog.currentnode = "givemepearl";
		else sld.dialog.currentnode = "mother";
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void LSC_OleGoHome(string qName) // ставим в дом Оле
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = characterFromId("Ole");
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");
	LAi_ActorTurnToCharacter(sld, characterFromID("Agnes"));
	sld = characterFromId("Agnes");
	sld.dialog.currentnode = "agnes_9";
	LAi_SetActorType(sld);
	LAi_ActorDialogDelay(sld, pchar, "", 1.5);
}

void LSC_OleReturnHome(string qName) // активируем диалоги
{
	LocCameraResetState();
	LAi_SetPlayerType(PChar);
	sld = characterFromId("Ole");
	sld.dialog.currentnode = "home_2";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void LSC_OleAgnesRegard(string qName) // открываем дом
{
	sld = characterFromId("Ole");
	sld.dialog.currentnode = "final";
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, "Marigo_houseSp2", "goto", "goto1");
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	LocatorReloadEnterDisable("Marigo_town", "houseSp2", false);
}
// <-- блудный сын

//------------------------------------------- возвращение на LSC -------------------------------------------
void LSC_ReturnJackmanAttack(string qName) //наймиты Джекмана атакуют
{
	log_Testinfo("Пираты Джекмана атакуют!");
	int iRank = 25+MOD_SKILL_ENEMY_RATE;
	int iScl = 60;
	int iShip = SHIP_TARTANE;
	int iCannons = CANNON_TYPE_CANNON_LBS3;
	Group_DeleteGroup("Jkm_Attack");
	Group_FindOrCreateGroup("Jkm_Attack");
    for (int i = 1; i <= 3; i++)
    {
		switch (sti(RealShips[sti(pchar.ship.type)].Class))
		{
			case 6:
				iShip = SHIP_TARTANE;
				iCannons = CANNON_TYPE_CANNON_LBS3;
				if(i == 1)
				{
					iShip = SHIP_SLOOP;
					iCannons = CANNON_TYPE_CANNON_LBS12;
				}
			break;
			
			case 5:
				iShip = SHIP_SLOOP;
				iCannons = CANNON_TYPE_CANNON_LBS12;
				if(i == 1)
				{
					iShip = SHIP_BRIGANTINE;
					iCannons = CANNON_TYPE_CANNON_LBS16;
				}
			break;
			
			case 4:
				iShip = SHIP_BRIGANTINE;
				iCannons = CANNON_TYPE_CANNON_LBS16;
				if(i == 1)
				{
					iShip = SHIP_CORVETTE;
					iCannons = CANNON_TYPE_CULVERINE_LBS18;
				}
			break;
			
			case 3:
				iShip = SHIP_CORVETTE;
				iCannons = CANNON_TYPE_CULVERINE_LBS18;
				if(i == 1)
				{
					iShip = SHIP_FRIGATE_H;
					iCannons = CANNON_TYPE_CANNON_LBS24;
				}
			break;
			
			case 2:
				iShip = SHIP_FRIGATE_H;
				iCannons = CANNON_TYPE_CANNON_LBS24;
				if(i == 1)
				{
					iShip = SHIP_LINESHIP;
					iCannons = CANNON_TYPE_CANNON_LBS32;
				}
			break;
			
			case 1:
				iShip = SHIP_LINESHIP;
				iCannons = CANNON_TYPE_CANNON_LBS32;
			break;
		}
		//SelectLevelWarShipParameter();//автолевеллинг
        sld = GetCharacter(NPC_GenerateCharacter("Saga_JkmPirate_"+i, "mercen_"+(rand(27)+1), "man", "man", iRank, PIRATE, 2, true, "hunter"));
		FantomMakeSmallSailor(sld, iShip, "", iCannons, iScl, iScl, iScl, iScl, iScl);
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol3", "grapeshot", iScl*2);
        Group_AddCharacter("Jkm_Attack", "Saga_JkmPirate_"+i);
    }
    Group_SetGroupCommander("Jkm_Attack", "Saga_JkmPirate_1");
	Group_SetTaskAttack("Jkm_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Jkm_Attack", PLAYER_GROUP);
	Group_SetAddress("Jkm_Attack", "Beliz", "", "");
	Group_LockTask("Jkm_Attack");
}

void LSC_ReturnCheckShips(string qName) //проверяем правильность кораблей и наличие лоции
{
	if (LSC_CheckShips()) // 270912
	{
		if (CheckCharacterItem(pchar, "LSC_navigation_map"))
		{
			Island_SetReloadEnableGlobal("LostShipsCity", true);//открыть остров, если был закрыт
			log_Testinfo("Проверка пройдена!!");
		}
		else
		{
			Island_SetReloadEnableGlobal("LostShipsCity", false);//закрыть остров
			PlaySound("interface\notebook.wav");
			log_info(StringFromKey("Saga_28"));
		}
	}
	else
	{
		Island_SetReloadEnableGlobal("LostShipsCity", false);//закрыть остров
		PlaySound("interface\notebook.wav");
		log_info(StringFromKey("Saga_29"));
	}
	pchar.quest.LSC_checkships_repeat.win_condition.l1 = "MapEnter";
	pchar.quest.LSC_checkships_repeat.function = "LSC_ReturnCheckShipsRepeat";
}

void LSC_ReturnCheckShipsRepeat(string qName) //установка повтора проверки
{
	log_Testinfo("Повтор проверки LSC установлен");
	pchar.quest.return_LSC.win_condition.l1 = "location";
	pchar.quest.return_LSC.win_condition.l1.location = "LostShipsCity";
	pchar.quest.return_LSC.function = "LSC_ReturnCheckShips";
}

void LSC_ReturnMain(string qName) //возвращение в Эдем
{
	// раздаем ноды всем ключевым персонажам
	if (GetCharacterIndex("Dodson") != -1)
	{
		// Акулу ставим стоймя, Декстера - садим в кресло. Теперь он адмирал.
		sld = characterFromId("Dodson");
		sld.dialog.currentnode = "return"; // Акула
		ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto10");
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_warrior_DialogEnable(sld, true); 
		sld = characterFromId("Dexter");
		sld.dialog.currentnode = "return"; // Декстер
		sld.greeting = "dexter_3"; 
		ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "sit", "sit1");
		LAi_SetHuberType(sld);
	}
	if (GetCharacterIndex("Mary") != -1)
	{
		sld = characterFromId("Mary");
		sld.dialog.currentnode = "return"; 
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "quest", "quest1"); // Мэри - встречает
	}
	if (GetCharacterIndex("Dodson") == -1)
	{
		sld = characterFromId("Dexter");
		sld.dialog.currentnode = "return_A"; // Декстер
	}
	sld = characterFromId("Ole");
	if (CheckCharacterItem(pchar, "keys_skel"))
	{
		LAi_RemoveLoginTime(sld);
		sld.dialog.currentnode = "return";
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "quest", "quest2"); // Оле - встречает
	}
	else sld.dialog.currentnode = "ole_3"; 
	pchar.questTemp.LSC = "return"; // флаг - вернулся
	// ставим Даниэль
	sld = characterFromId("Danielle");
	sld.dialog.currentnode = "nathaniel"; 
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "reload", "reload1_back");
	LAi_ActorDialog(sld, pchar, "", -1, 0); // Даниэль начинает
	// запреты
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.CannotWait = true;//запрет ожидания
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	// устанавливаем повторную атаку пиратов Джекмана
	pchar.quest.return_LSC_attack.over = "yes"; //снять прерывание, если проскочил
	pchar.quest.return_LSC_attack1.win_condition.l1 = "location";
	pchar.quest.return_LSC_attack1.win_condition.l1.location = "Beliz";
	pchar.quest.return_LSC_attack1.function = "LSC_ReturnJackmanAttack"; // атака наймитов Джекмана
}

void LSC_DannyAndNatan(string qName) //Даниэль и Натаниэль... любовь и все такое
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = characterFromId("Nathaniel");
	sld.greeting = "Nathaniel";
	LAi_SetActorType(sld);
	pchar.questTemp.LSC.Attack = true; // обработка в АИ
	sld = characterFromId("Danielle");
	ChangeCharacterAddressGroup(sld, "FernandaDiffIndoor", "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);
}

void LSC_NatanielSeeDaniel() // встретились... 
{
	DeleteAttribute(pchar, "questTemp.LSC.Attack");
	StartQuestMovie(true, true, true);
	sld = characterFromId("Nathaniel");
	sld.dialog.currentnode = "danny";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);
}

void LSC_SetNatanPassenger(string qName) // Натаниэля в пассажиры
{
	sld = characterFromId("Nathaniel");
	sld.location = "none";
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, false);
	sld = characterFromId("Danielle");
	LAi_SetOfficerType(sld);
	sld.dialog.currentnode = "Danielle_officer";
}

void LSC_ClearFoodStorage(string qName) // чистим склады с продовольствием
{
	sld = characterFromId("Dexter");
	sld.quest.foodqty = rand(1000);
}

void LSC_DodsonSC(string qName) // высаживаем Акулу в Санта-Каталине
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = characterFromId("Dodson");
	sld.dialog.currentnode = "return_5";
	RemovePassenger(Pchar, sld);
	ChangeCharacterAddressGroup(sld, "Santacatalina_town", "quest", "quest1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}
//-------------------------------------------искушение Барбазона---------------------------------------------

void Saga_BarbTemptationOver(string qName)//не пошли за шелком
{
	pchar.quest.BarbTemptation.over = "yes"; //снять прерывание
	AddQuestRecord("BarbTemptation", "4");
	pchar.questTemp.Saga.BarbTemptation = "give_silk";
	//пусть ищет шелк, где хочет - так будет лучше, чем валить квест сразу
}

void Saga_BarbTemptationBarkas(string qName)//устанавливаем рыбацкий баркас
{
	Group_FindOrCreateGroup("BarbBarkas");
	Group_SetType("BarbBarkas", "trade");//тип группы
	sld = GetCharacter(NPC_GenerateCharacter("BarbCapBarkas", "citiz_25", "man", "man", 10, HOLLAND, -1, true, "marginal"));
	FantomMakeCoolFighter(sld, 10, 20, 20, "blade_05", "pistol1", "bullet", 50);
	FantomMakeCoolSailor(sld, SHIP_TARTANE, "", CANNON_TYPE_NONECANNON, 5, 5, 5);
	sld.dialog.FileName = "Quest\Saga\OtherNPC.c";
	sld.dialog.currentnode = "BarbCapBarkas";
	sld.DeckDialogNode = "BarbCapBarkas";
	sld.DontRansackCaptain = true;
	sld.Ship.Mode = "trade";
	NullCharacterGoods(sld);
	SetCharacterGoods(sld, GOOD_SHIPSILK, 90);
	Group_AddCharacter("BarbBarkas", "BarbCapBarkas");
	Group_SetGroupCommander("BarbBarkas", "BarbCapBarkas");
	Group_SetTaskNone("BarbBarkas");
	Group_SetAddress("BarbBarkas", "SentMartin", "quest_ships", "quest_ship_6");
	Group_LockTask("BarbBarkas");
	
	pchar.quest.BarbBarkas_Sink.win_condition.l1 = "Character_sink";
	pchar.quest.BarbBarkas_Sink.win_condition.l1.character = "BarbCapBarkas";
	pchar.quest.BarbBarkas_Sink.function = "Saga_BarbBarkasFail";//потопили
	pchar.quest.BarbBarkas_Abordage.win_condition.l1 = "Character_Capture";
	pchar.quest.BarbBarkas_Abordage.win_condition.l1.character = "BarbCapBarkas";
	pchar.quest.BarbBarkas_Abordage.function = "Saga_BarbBarkasBoarding";//взяли на абордаж
}

void Saga_BarbBarkasFail(string qName)// утопили баркас
{
	pchar.quest.Saga_BarbTemptationOver.over = "yes"; //снять таймер
	pchar.quest.BarbBarkas_Abordage.over = "yes"; //снять прерывание
	AddQuestRecord("BarbTemptation", "3");
	pchar.questTemp.Saga.BarbTemptation = "give_silk";
	ChangeCharacterComplexReputation(pchar, "nobility", -5);
	ChangeCharacterNationReputation(pchar, HOLLAND, -5);
}

void Saga_BarbBarkasBoarding(string qName)// абордировали баркас
{
	pchar.quest.Saga_BarbTemptationOver.over = "yes"; //снять таймер
	pchar.quest.BarbBarkas_Sink.over = "yes"; //снять прерывание
	AddQuestRecord("BarbTemptation", "5");
	pchar.questTemp.Saga.BarbTemptation = "give_silk";
	ChangeCharacterComplexReputation(pchar, "nobility", -5);
	ChangeCharacterNationReputation(pchar, HOLLAND, -5);
}

void Saga_BarbBarkasSilk()//погрузка шелка
{
	SetLaunchFrameFormParam(StringFromKey("Saga_30", NewStr()), "", 0, 5);
	LaunchFrameForm();
	WaitDate("", 0, 0, 0, 1, 10); //крутим время
	RecalculateJumpTable();
	DoQuestFunctionDelay("Saga_BarbBarkasBye", 5.5);
}

void Saga_BarbBarkasBye(string qName)//уходим
{
	pchar.quest.Saga_BarbTemptationOver.over = "yes"; //снять таймер
	sld = characterFromId("BarbCapBarkas");
	sld.dialog.currentnode = "BarbCapBarkas_5";
	RemoveCharacterGoods(sld, GOOD_SHIPSILK, 90);
	SetCharacterGoods(pchar, GOOD_SHIPSILK, 90);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 1.0, -1);
}

void Saga_CreateMorelle() //создаем Мореля
{
	sld = GetCharacter(NPC_GenerateCharacter("Morelle", "citiz_22", "man", "man", 10, PIRATE, -1, true, "quest"));
	RemoveAllCharacterItems(sld, true);
	sld.name = StringFromKey("Saga_31");
	sld.lastname = StringFromKey("Saga_32");
	sld.dialog.FileName = "Quest\Saga\OtherNPC.c";
	sld.dialog.currentnode = "Morelle";
	sld.greeting = "town_pirate";
	LAi_SetStayType(sld);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Marigo_prison", "goto", "goto9");
}

void Saga_SetMorelGoods(string qName) //тайник Мореля
{
	Log_Info(StringFromKey("Saga_33"));
	Log_Info(StringFromKey("Saga_34"));
	PlaySound("interface\notebook.wav");
	AddCharacterGoods(pchar, GOOD_SHIPSILK, 30); 
	AddCharacterGoods(pchar, GOOD_EBONY, 50); 
	AddCharacterGoods(pchar, GOOD_MAHOGANY, 60);
	AddCharacterGoods(pchar, GOOD_TOBACCO, 100);
	AddCharacterGoods(pchar, GOOD_COFFEE, 150);
	AddCharacterGoods(pchar, GOOD_CHOCOLATE, 350);
	AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
	//int n = Findlocation("Shore40");
	//DeleteAttribute(&locations[n], "models.always.Roll");
}

void Saga_SetJuniorInCharles() //создаем Валета
{
	int iRank = 22+MOD_SKILL_ENEMY_RATE+5;
	int iScl = 65;
	sld = GetCharacter(NPC_GenerateCharacter("Valet", "Valet", "man", "man", iRank, PIRATE, -1, true, "quest"));
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_18", "pistol6", "bullet", iScl*2);
	sld.name = StringFromKey("Saga_35");
	sld.lastname = StringFromKey("Saga_36");
	sld.dialog.FileName = "Quest\Saga\OtherNPC.c";
	sld.dialog.currentnode = "valet";
	sld.greeting = "Valet";
	if (MOD_SKILL_ENEMY_RATE > 5) sld.MultiFighter = 1.8; // мультифайтер
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, "Charles_houseH1", "barmen", "stay");
	GiveItem2Character(sld, "letter_chad");
	ChangeItemDescribe("letter_chad", "itmdescr_letter_valet");
	GiveAdmiralMapToCharacter(sld, 9);
	sld.SaveItemsForDead = true; 
	sld.DontClearDead = true; 
}

void Saga_FindValetLetter(string qName) //нашли письмо Валета
{
	chrDisableReloadToLocation = false;
	AddQuestRecord("BarbTemptation", "8");
	AddQuestRecordInfo("Letter_valet", "1");
	pchar.quest.Saga_SetPolacre_Marlin.win_condition.l1 = "location";
	pchar.quest.Saga_SetPolacre_Marlin.win_condition.l1.location = "Nevis";
	pchar.quest.Saga_SetPolacre_Marlin.function = "Saga_SetPolacreMarlin";
}

void Saga_SetPolacreMarlin(string qName) //ставим полакр Марлин
{
	RemoveItems(pchar, "letter_chad", 1);
	int iRank = 20+MOD_SKILL_ENEMY_RATE;
	int iScl = 60;
	Island_SetReloadEnableGlobal("Nevis", false);//на остров нельзя
	bQuestDisableMapEnter = true; //закрываем карту
	pchar.GenQuest.MapClosedNoBattle = true; // patch
	Group_FindOrCreateGroup("Ship_Marlin");
	Group_SetType("Ship_Marlin", "pirate");//тип группы
	sld = GetCharacter(NPC_GenerateCharacter("Cap_Marlin", "mercen_27", "man", "man", iRank, ENGLAND, -1, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_POLACRE, StringFromKey("Saga_37"), CANNON_TYPE_CULVERINE_LBS18, iScl, iScl, iScl);
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_18", "pistol6", "bullet", iScl*2+70);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "pirate";
	sld.ship.Crew.Morale = MOD_SKILL_ENEMY_RATE*6+20;
	sld.Ship.Crew.Exp.Sailors = MOD_SKILL_ENEMY_RATE*6+20;
	sld.Ship.Crew.Exp.Cannoners = MOD_SKILL_ENEMY_RATE*6+20;
	sld.Ship.Crew.Exp.Soldiers = MOD_SKILL_ENEMY_RATE*6+40;
	sld.Coastal_Captain = true; 
	sld.DontDeskTalk = true;
	if (MOD_SKILL_ENEMY_RATE > 7) sld.MultiFighter = 1.5; // мультифайтер
	SetCharacterPerk(sld, "MusketsShoot");
	UpgradeShipParameter(sld, "TurnRate");//маневренность
	UpgradeShipParameter(sld, "HP");//корпус
	Group_AddCharacter("Ship_Marlin", "Cap_Marlin");
	Group_SetGroupCommander("Ship_Marlin", "Cap_Marlin");
	Group_SetTaskNone("Ship_Marlin");//нет задачи
	Group_SetAddress("Ship_Marlin", "Nevis", "quest_ships", "quest_ship_"+(3+rand(4)));
	Group_LockTask("Ship_Marlin");
	
	pchar.quest.Marlin_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Marlin_AfterBattle.win_condition.l1.group = "Ship_Marlin";
	pchar.quest.Marlin_AfterBattle.function = "Saga_CheckMarlinAfterBattle";
}

void Saga_CheckMarlinAfterBattle(string qName) //проверяем полакр Марлин после боя
{
	DoQuestCheckDelay("sea_victory", 1.5);
	Group_DeleteGroup("Ship_Marlin");
	Island_SetReloadEnableGlobal("Nevis", true);
	bQuestDisableMapEnter = false; 
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle"); // patch
	int iMar = 0;
	for(i = 0; i < COMPANION_MAX; i++)
	{
		iTemp = GetCompanionIndex(pchar, i);
		if(iTemp > 0)
		{
			sld = GetCharacter(iTemp);
			if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE && sld.ship.name == StringFromKey("Saga_37")) iMar = 1;
		}
	} // есть ли у нас Марлин
	if (iMar == 1) // есть
	{
		pchar.questTemp.Saga.BarbTemptation.Marlin = "true";
		AddQuestRecord("BarbTemptation", "9");
		AddCharacterExpToSkill(pchar, "Grappling", 200);//абордаж
	}
	else AddQuestRecord("BarbTemptation", "10");
	LocatorReloadEnterDisable("LaVega_town", "reload6", true); // закрываем вход к Маркусу
	// прерывание на Теркс
	pchar.quest.Saga_Vensan_brigantine.win_condition.l1 = "location";
	pchar.quest.Saga_Vensan_brigantine.win_condition.l1.location = "Terks";
	pchar.quest.Saga_Vensan_brigantine.function = "Saga_CheckVensanBrigantine";
	AddComplexSeaExpToScill(100, 100, 100, 0, 100, 100, 0);
}

void Saga_CheckVensanBrigantine(string qName) // проверка правильности выполнения
{
	if (!Saga_CheckMarlinShip())
	{
		Log_TestInfo("Проверка НЕ пройдена!");
		if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Marlin_Repeat")) AddQuestRecord("BarbTemptation", "11");
		pchar.quest.Saga_Vensan_brigantine1.win_condition.l1 = "MapEnter";
		pchar.quest.Saga_Vensan_brigantine1.function = "Saga_CheckVensanBrigantineRepeat";
	}
	else
	{
		Log_TestInfo("Проверка пройдена!");
		AddQuestRecord("BarbTemptation", "12");
		bQuestDisableMapEnter = true; //закрываем карту
		pchar.GenQuest.MapClosedNoBattle = true; // patch
		// устанавливаем бригантину Венсана
		Group_FindOrCreateGroup("Ship_Vensan");
		Group_SetType("Ship_Vensan", "pirate");//тип группы
		sld = GetCharacter(NPC_GenerateCharacter("Cap_Vensan", "mercen_20", "man", "man", 20, ENGLAND, -1, true, "quest"));
		FantomMakeCoolSailor(sld, SHIP_BRIGANTINE, StringFromKey("Saga_38"), CANNON_TYPE_CANNON_LBS16, 50, 50, 50);
		sld.FaceId = 333; // пустой кораблик
		sld.name = "";
		sld.lastname = "";
		sld.ShipEnemyDisable  = true;
		sld.AlwaysFriend = true;
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		SetCrewQuantityOverMax(sld, 30);
		sld.Ship.Mode = "pirate";
		ref realShip = GetRealShip(GetCharacterShipType(sld));
		realShip.lowpolycrew = 0; // убрать матросиков с палубы корабля
		Group_AddCharacter("Ship_Vensan", "Cap_Vensan");
		Group_SetGroupCommander("Ship_Vensan", "Cap_Vensan");
		Group_SetTaskNone("Ship_Vensan");//нет задачи
		Group_SetAddress("Ship_Vensan", "Terks", "ships", "l4");
		Group_LockTask("Ship_Vensan");
		// прерывание на высадку в Южный залив
		pchar.quest.Saga_DestroyTrap.win_condition.l1 = "location";
		pchar.quest.Saga_DestroyTrap.win_condition.l1.location = "Shore57";
		pchar.quest.Saga_DestroyTrap.function = "Saga_DestroyVensanTrap";
	}
}

void Saga_CheckVensanBrigantineRepeat(string qName) // повтор проверки
{
	pchar.quest.Saga_Vensan_brigantine.win_condition.l1 = "location";
	pchar.quest.Saga_Vensan_brigantine.win_condition.l1.location = "Terks";
	pchar.quest.Saga_Vensan_brigantine.function = "Saga_CheckVensanBrigantine";
	pchar.questTemp.Saga.BarbTemptation.Marlin_Repeat = "true";
}

void Saga_CreateCapnCrewVensan() // палуба бригантины венсана
{
	// усадим Венсана
	sld = GetCharacter(NPC_GenerateCharacter("Vensan", "Vensan", "man", "man", 20, ENGLAND, -1, true, "quest"));
	sld.name = StringFromKey("Saga_39");
	sld.lastname = StringFromKey("Saga_40");
	sld.dialog.FileName = "Quest\Saga\OtherNPC.c";
	sld.dialog.currentnode = "vensan";
	sld.greeting = "vensan";
	if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Vensan_canfree")) LAi_CharacterDisableDialog(sld);
	RemoveAllCharacterItems(sld, true);
	LAi_SetImmortal(sld, true);
	LAi_SetGroundSitTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "reload", "reload1");
	// разложим его матросов
	for(i = 1; i <= 8; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Vens_sailor_"+i, "citiz_3"+i, "man", "man", 20, ENGLAND, -1, true, "quest"));
		RemoveAllCharacterItems(sld, true);
		ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "goto", "goto"+i);
		LAi_SetActorType(sld);
		LAi_ActorSetLayMode(sld);
	}
	if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Vensan_canfree")) DoQuestFunctionDelay("Saga_BrigantineBoom", 5.0); // бум!!
}

void Saga_BrigantineBoom(string qName) // залез на бригантину не вовремя
{
	PlayStereoSound("Sea Battles\Vzriv_fort_001.wav");
	for(i = 1; i <= 9; i++)
	{
		CreateLocationParticles("shipfire", "goto", "goto"+i, 0.5, 0, 0, "");
		CreateLocationParticles("blast_inv", "goto", "goto"+i, 1.0, 0, 0, "");
		CreateLocationParticles("blast_dirt", "goto", "goto"+i, 1.0, 0, 0, "");
	}
	LAi_KillCharacter(pchar);
	LAi_KillCharacter(pchar);
	ClearAllLogStrings();
}

void Saga_BrigantineDetonate(string qName) // сюрприз для особо упоротых
{
	PlayStereoSound("Sea Battles\Vzriv_fort_001.wav");
		PlayStereoSound("Sea Battles\vzriv_pogreb_002.wav")
	sld = characterFromId("Cap_Vensan");
	Ship_Detonate(sld, true, true); 
	Ship_Detonate(pchar, true, true); 
}

void Saga_DestroyVensanTrap(string qName) // учиняем массовую драку в заливе
{
	chrDisableReloadToLocation = true;//закрыть локацию
	int iRank = 22+MOD_SKILL_ENEMY_RATE;
	int iScl = 55;
	// устанавливаем врагов
	// мушкетеры
	int m = makeint(MOD_SKILL_ENEMY_RATE/2);
	if (m < 2) m = 2;
	for (i=1; i<=m; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Saga_TrapMush_"+i, "mush_ctz_"+(rand(2)+7), "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank+2, iScl+5, iScl+5, "", "mushket1", "cartridge", iScl*2);
		sld.MusketerDistance = 0;
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	// солдаты
	for (i=1; i<=3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Saga_TrapSold_"+i, "citiz_4"+i, "man", "man", iRank, PIRATE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol3", "grapeshot", iScl*2);
		ChangeCharacterAddressGroup(sld, pchar.location, "smugglers", "smuggler"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	// подкрепление
	for (i=1; i<=7; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Saga_TrapSoldAdd_"+i, "citiz_4"+(i+3), "man", "man", iRank, PIRATE, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank+2, iScl+5, iScl+5, "blade_21", "pistol1", "bullet", iScl*2);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto7");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	// устанавливаем наших
	// мушкетеры
	for (i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Saga_OwrMush_"+i, "mush_ctz_"+(rand(2)+4), "man", "mushketer", iRank, PIRATE, 1, false, "soldier")); // 291112
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
		ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc2");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	// солдаты
	for (i=1; i<=5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Saga_OwrSold_"+i, "citiz_3"+i, "man", "man", iRank, PIRATE, 1, false, "soldier")); // 291112
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol3", "grapeshot", iScl*2);
		ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc1");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Saga_VensanTrapDestroyed");
	AddDialogExitQuest("MainHeroFightModeOn");
}

void Saga_CreateVensanEnemyes(string qName) // устанавливаем Бродягу и Упыря
{
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle"); // patch пускай ручками гребет вокруг острова
	Island_SetReloadEnableGlobal("Terks", false);//закрыть остров
	AddQuestRecord("BarbTemptation", "14");
	pchar.nation = FRANCE; // принудительно
	int iRank = 20+MOD_SKILL_ENEMY_RATE;
	int iScl = 55;
	Group_FindOrCreateGroup("Ship_VensanEnemy");
	Group_SetType("Ship_VensanEnemy", "pirate");//тип группы
	// устанавливаем корвет Бродяги
	sld = GetCharacter(NPC_GenerateCharacter("Saga_Vagrant", "mercen_26", "man", "man", iRank, ENGLAND, -1, true, "quest")); // patch
	FantomMakeSmallSailor(sld, SHIP_CORVETTE, StringFromKey("Saga_41"), CANNON_TYPE_CULVERINE_LBS18, iScl, iScl, iScl, iScl, iScl);
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_13", "pistol5", "bullet", iScl*2);
	sld.name = StringFromKey("Saga_42");
	sld.lastname = StringFromKey("Saga_43");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "pirate";
	sld.DontDeskTalk = true;
	if (MOD_SKILL_ENEMY_RATE > 7) sld.MultiFighter = 1.5; // мультифайтер
	Group_AddCharacter("Ship_VensanEnemy", "Saga_Vagrant");
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND); // тестить
	//SetNationRelation2MainCharacter(PIRATE, RELATION_FRIEND); // 300912
	// устанавливаем фрегат Упыря
	sld = GetCharacter(NPC_GenerateCharacter("Saga_vampire", "mercen_25", "man", "man", iRank+5, ENGLAND, -1, true, "quest")); // patch
	FantomMakeCoolSailor(sld, SHIP_FRIGATE, StringFromKey("Saga_44"), CANNON_TYPE_CANNON_LBS24, iScl+5, iScl+5, iScl+5);
	FantomMakeCoolFighter(sld, iRank+5, iScl+15, iScl+15, "blade_14", "pistol5", "bullet", iScl*2+100);
	sld.name = StringFromKey("Saga_45");
	sld.lastname = StringFromKey("Saga_46");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "pirate";
	sld.DontDeskTalk = true;
	if (MOD_SKILL_ENEMY_RATE > 7) sld.MultiFighter = 1.5; // мультифайтер
	Group_AddCharacter("Ship_VensanEnemy", "Saga_vampire");
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND); // тестить
	Group_SetGroupCommander("Ship_VensanEnemy", "Saga_Vagrant");
	Group_SetTaskNone("Ship_VensanEnemy");//нет задачи
	Group_SetAddress("Ship_VensanEnemy", "Terks", "Islandships1", "ship_2");
	Group_LockTask("Ship_VensanEnemy");
	
	pchar.quest.Vensan_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Vensan_AfterBattle.win_condition.l1.group = "Ship_VensanEnemy";
	pchar.quest.Vensan_AfterBattle.function = "Saga_VensanAfterBattle";
	
}

void Saga_CheckVensanEnemyes() // анализируем ГГ - обработка в АИ
{
	bool bOk = false;
	if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Marlin") && pchar.ship.name == StringFromKey("Saga_37") && GetSummonSkillFromName(pchar, SKILL_SNEAK)*isEquippedArtefactUse(pchar, "indian_11", 1.0, 1.15) > (10+rand(35))) bOk = true;
	if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Marlin") && pchar.ship.name == StringFromKey("Saga_37") && GetSummonSkillFromName(pchar, SKILL_SNEAK)*isEquippedArtefactUse(pchar, "indian_11", 1.0, 1.15) > (10+rand(85))) bOk = true;
	if (!bOk)
	{
		log_info(StringFromKey("Saga_55"));
		DeleteAttribute(pchar, "questTemp.Saga.BarbTemptation.Bomb"); // если было
		pchar.questTemp.Saga.BarbTemptation.vensan_attack = "true";
		sld = characterFromId("Saga_Vagrant");
		sld.AlwaysEnemy = true;
		sld = characterFromId("Saga_vampire");
		sld.AlwaysEnemy = true;
		SetCharacterRelationBoth(sti(GetCharacterIndex("Saga_Vagrant")), GetMainCharacterIndex(), RELATION_ENEMY);
		SetCharacterRelationBoth(sti(GetCharacterIndex("Saga_vampire")), GetMainCharacterIndex(), RELATION_ENEMY);
		Group_SetTaskAttack("Ship_VensanEnemy", PLAYER_GROUP);
		Group_LockTask("Ship_VensanEnemy");
		UpdateRelations();
		RefreshBattleInterface();
		AddCharacterExpToSkill(pchar, "Sneak", 200);
	}
}

void Saga_VagrantVampireAttack() // пальнули через прицел
{
	DeleteAttribute(pchar, "questTemp.Saga.BarbTemptation.Bomb"); // если было
	pchar.questTemp.Saga.BarbTemptation.vensan_attack = "true";
	sld = characterFromId("Saga_Vagrant");
	sld.AlwaysEnemy = true;
	sld = characterFromId("Saga_vampire");
	sld.AlwaysEnemy = true;
	SetCharacterRelationBoth(sti(GetCharacterIndex("Saga_Vagrant")), GetMainCharacterIndex(), RELATION_ENEMY);
	SetCharacterRelationBoth(sti(GetCharacterIndex("Saga_vampire")), GetMainCharacterIndex(), RELATION_ENEMY);
	Group_SetTaskAttack("Ship_VensanEnemy", PLAYER_GROUP);
	Group_LockTask("Ship_VensanEnemy");
	UpdateRelations();
	RefreshBattleInterface();
}

void Saga_HitSeaBomb() // ставим бомбу под фрегат - обработка в АИ
{
	float fTemp = 100.0;
	DeleteAttribute(pchar, "questTemp.Saga.BarbTemptation.Bomb");
	PlaySound("Ships\jakor_002.wav");
	log_info(StringFromKey("Saga_47"));
	if(iArcadeSails == 1) fTemp = 40.0;
	AISeaGoods_AddGood(pchar, "powder", "barrel_treasure", fTemp-10.0, 1);
	DoQuestFunctionDelay("Saga_HitSeaBomb_Detonate", fTemp);
	log_info(StringFromKey("Saga_48", sti(fTemp)));
}

void Saga_HitSeaBomb_Detonate(string qName) // капут фрегату
{
	pchar.questTemp.Saga.BarbTemptation.BombFire = "true";
	sld = characterFromId("Saga_vampire");
	Ship_Detonate(sld, true, true); // ба-бах!!!
	PlayStereoSound("Sea Battles\Vzriv_fort_001.wav");
	PlayStereoSound("Sea Battles\vzriv_pogreb_002.wav");
	if (Ship_GetDistance2D(GetMainCharacter(), sld) < 200) Saga_SeaBombFail();
	sld = characterFromId("Saga_Vagrant");
	sld.AlwaysEnemy = true;
	SetCharacterRelationBoth(sti(GetCharacterIndex("Saga_Vagrant")), GetMainCharacterIndex(), RELATION_ENEMY);
	Group_SetTaskAttack("Ship_VensanEnemy", PLAYER_GROUP);
	Group_LockTask("Ship_VensanEnemy");
	UpdateRelations();
	RefreshBattleInterface();
	AddCharacterExpToSkill(pchar, "Sneak", 400);
}

void Saga_SeaBombFail() // а если ГГ не удрал - то и ему тоже
{
	log_info(StringFromKey("Saga_49"));
	Ship_Detonate(pchar, true, true); // ба-бах!!!
}

void Saga_VensanAfterBattle(string qName) // уничтожили врагов
{
	DoQuestCheckDelay("sea_victory", 1.5);
	Group_DeleteGroup("Ship_VensanEnemy");
	Island_SetReloadEnableGlobal("Terks", true);
	bQuestDisableMapEnter = false;
	// чистим за собой
	pchar.quest.Saga_VensanClear.win_condition.l1 = "MapEnter";
	pchar.quest.Saga_VensanClear.function = "Saga_VensanClear";
	if (CheckCharacterItem(pchar, "letter_chad_1"))
	{
		AddQuestRecord("BarbTemptation", "16");
		pchar.questTemp.Saga.BarbTemptation = "islatesoro";
		// ставим прерывание на Исла-Тесоро
		pchar.quest.Saga_AttackJackman.win_condition.l1 = "location";
		pchar.quest.Saga_AttackJackman.win_condition.l1.location = "Bermudes";
		pchar.quest.Saga_AttackJackman.function = "Saga_CheckJackmanBermudes";
	}
	else
	{
		AddQuestRecord("BarbTemptation", "17");
		pchar.questTemp.Saga.BarbTemptation = "danielle"; // даю ещё один шанс
	}
	if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.BombFire")) AddQuestUserData("BarbTemptation", "sText", StringFromKey("Saga_50"));
	AddComplexSeaExpToScill(150, 150, 150, 150, 150, 150, 0);
}

void Saga_VensanClear(string qName) // подчищаем ненужные группы и НПС
{
	Group_DeleteGroup("Ship_Vensan");
	sld = characterFromId("Vensan");
	sld.lifeday = 0;
	for (i=1; i<=8; i++)
	{
		sld = characterFromId("Vens_sailor_"+i);
		sld.lifeday = 0;
	}
}

void Saga_CheckJackmanBermudes(string qName) // Джекман
{
	if (!Saga_CheckMarlinShip())
	{
		Log_TestInfo("Проверка НЕ пройдена!");
		if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Jackman_Repeat")) AddQuestRecord("BarbTemptation", "19");
		pchar.quest.Saga_AttackJackman1.win_condition.l1 = "MapEnter";
		pchar.quest.Saga_AttackJackman1.function = "Saga_CheckJackmanBermudesRepeat";
	}
	else
	{
		string sTemp;
		Log_TestInfo("Проверка пройдена!");
// --> mitrokosta письмо выбрасываем за ненадобностью
    if(CheckCharacterItem(pchar, "letter_chad_1")) {
      RemoveItems(pchar, "letter_chad_1", 1);
    }
// <--
		Island_SetReloadEnableGlobal("Bermudes", false);//закрыть остров
		bQuestDisableMapEnter = true; //закрываем карту
		pchar.nation = FRANCE; // принудительно
		// Даниэль делаем бессмертной
		sld = characterFromId("Danielle");
		LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
		// устанавливаем фрегат Джекмана
		Group_FindOrCreateGroup("Jackman_Frigate");
		Group_SetType("Jackman_Frigate", "pirate");//тип группы
		int iRank = 25+MOD_SKILL_ENEMY_RATE;
		int iScl = 90;
		int iCannon = CANNON_TYPE_CANNON_LBS32;
		if (sti(pchar.rank) < 15 || MOD_SKILL_ENEMY_RATE < 7) iCannon = CANNON_TYPE_CANNON_LBS24;
		sld = characterFromId("Jackman");
		sld.nation = ENGLAND;
		FantomMakeSmallSailor(sld, SHIP_FRIGATE_H, StringFromKey("Saga_51"), iCannon, iScl, iScl, iScl, iScl, iScl);
		SetCharacterPerk(sld, "CriticalShoot");
		SetCharacterPerk(sld, "LongRangeShoot");
		SetCharacterPerk(sld, "CannonProfessional");
		SetCharacterPerk(sld, "ShipDefenseProfessional");
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol5", "bullet", iScl*2+100);
		LAi_SetImmortal(sld, false);
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.Ship.Mode = "mercenary";
		sld.SaveItemsForDead = true;
		sld.DontClearDead = true;
		GiveItem2Character(sld, "spyglass4");
		sld.DontDeskTalk = true;
		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND); // тестить
		sld.ship.Crew.Morale = 50+MOD_SKILL_ENEMY_RATE*5;
		sld.Ship.Crew.Exp.Sailors = 50+MOD_SKILL_ENEMY_RATE*5;
		sld.Ship.Crew.Exp.Cannoners = 50+MOD_SKILL_ENEMY_RATE*5;
		sld.Ship.Crew.Exp.Soldiers = 50+MOD_SKILL_ENEMY_RATE*5; // крутизна невероятная
		if (MOD_SKILL_ENEMY_RATE > 4) 
		{
			SetCharacterPerk(sld, "MusketsShoot");
			sld.MultiFighter = 1.8; // мультифайтер
		}
		Group_AddCharacter("Jackman_Frigate", "Jackman");
		Group_SetGroupCommander("Jackman_Frigate", "Jackman");
		Group_SetTaskNone("Jackman_Frigate");//нет задачи
		Group_SetAddress("Jackman_Frigate", "Bermudes", "quest_ships", "quest_ship_8");
		Group_LockTask("Jackman_Frigate");
		
		//на захват либо потопление абордажем
		pchar.quest.Saga_JackmanAbordage.win_condition.l1 = "Character_Capture";
		pchar.quest.Saga_JackmanAbordage.win_condition.l1.character = "Jackman";
		pchar.quest.Saga_JackmanAbordage.function = "Saga_JackmanAbordage";//взяли на абордаж
		//на потопление орудиями
		pchar.quest.Saga_JackmanSink.win_condition.l1 = "Character_sink";
		pchar.quest.Saga_JackmanSink.win_condition.l1.character = "Jackman";
		pchar.quest.Saga_JackmanSink.function = "Saga_JackmanSink";//потопили
		
		//военный совет
		if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.BombFire")) // если юзал бомбу
		{
			if (pchar.questTemp.Saga.BarbTemptation.adviser == "Mary")
			{
				if (GetCharacterIndex("Mary") != -1)
				{
					sld = characterFromId("Mary");
					sTemp = StringFromKey("Saga_52");
					sld.quest.fugas = "true";
				}
				else sTemp = StringFromKey("Saga_53");
			}
			else
			{
				sld = characterFromId("Helena");
				sTemp = StringFromKey("Saga_54");
				sld.quest.fugas = "true";
			}
		}
		else sTemp = "";
		AddQuestRecord("BarbTemptation", "20");
		AddQuestUserData("BarbTemptation", "sText", sTemp);
		
		DeleteQuestCondition("HelenDrinking_IslaTesoroAmbush");
	}
}

void Saga_CheckJackmanBermudesRepeat(string qName) // повтор проверки
{
	pchar.quest.Saga_AttackJackman.win_condition.l1 = "location";
	pchar.quest.Saga_AttackJackman.win_condition.l1.location = "Bermudes";
	pchar.quest.Saga_AttackJackman.function = "Saga_CheckJackmanBermudes";
	pchar.questTemp.Saga.BarbTemptation.Jackman_Repeat = "true";
}

void Saga_CheckJackmanFrigate() // анализируем ГГ - обработка в АИ
{
	// Джекмана обмануть сложнее
	bool bOk = false;
	if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Marlin") && pchar.ship.name == StringFromKey("Saga_37") && GetSummonSkillFromName(pchar, SKILL_SNEAK)*isEquippedArtefactUse(pchar, "indian_11", 1.0, 1.15) > (10+rand(50))) bOk = true;
	if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Marlin") && pchar.ship.name == StringFromKey("Saga_37") && GetSummonSkillFromName(pchar, SKILL_SNEAK)*isEquippedArtefactUse(pchar, "indian_11", 1.0, 1.15) > (20+rand(100))) bOk = true;
	if (!bOk)
	{
		log_info(StringFromKey("Saga_55"));
		sld = characterFromId(pchar.questTemp.Saga.BarbTemptation.adviser);
		DeleteAttribute(sld, "quest.fugas");
		sld = characterFromId("Jackman");
		sld.AlwaysEnemy = true;
		SetCharacterRelationBoth(sti(GetCharacterIndex("Jackman")), GetMainCharacterIndex(), RELATION_ENEMY);
		Group_SetTaskAttack("Jackman_Frigate", PLAYER_GROUP);
		Group_LockTask("Jackman_Frigate");
		UpdateRelations();
		RefreshBattleInterface();
		AddCharacterExpToSkill(pchar, "Sneak", 250);//скрытность
	}
}

void Saga_CenturionAttack() // пальнули через прицел
{
	sld = characterFromId(pchar.questTemp.Saga.BarbTemptation.adviser);
	DeleteAttribute(sld, "quest.fugas");
	DeleteAttribute(pchar, "questTemp.Saga.BarbTemptation.Fugas");
	sld = characterFromId("Jackman");
	sld.AlwaysEnemy = true;
	SetCharacterRelationBoth(sti(GetCharacterIndex("Jackman")), GetMainCharacterIndex(), RELATION_ENEMY);
	Group_SetTaskAttack("Jackman_Frigate", PLAYER_GROUP);
	Group_LockTask("Jackman_Frigate");
	UpdateRelations();
	RefreshBattleInterface();
}

void Saga_HitSeaFugas() // бросаем фугас - обработка в АИ
{
	float fTemp = 25.0;
	if(iArcadeSails == 1) fTemp = 10.0;
	DeleteAttribute(pchar, "questTemp.Saga.BarbTemptation.Fugas");
	PlayStereoSound("Sea Battles\udar_metal_002.wav");
	log_info(StringFromKey("Saga_56"));
	DoQuestFunctionDelay("Saga_HitSeaFugas_Detonate", fTemp);
	log_info(StringFromKey("Saga_57", sti(fTemp)));
}

void Saga_HitSeaFugas_Detonate(string qName) // фугасом по пиратам
{
	float fTemp = 16.0;
	if(iArcadeSails == 1) fTemp = 7.0;
	pchar.questTemp.Saga.BarbTemptation.FugasFire = "true";
	sld = characterFromId("Jackman");
	Ship_Detonate(sld, false, false); // ба-бах!!!
	PlayStereoSound("Sea Battles\vzriv_pogreb_002.wav");
	PlayStereoSound("Sea Battles\sdavl_kriki_005.wav");
	int iCrew = makeint(sti(sld.Ship.Crew.Quantity)*0.67);
	if(MOD_SKILL_ENEMY_RATE < 8) iCrew = makeint(sti(sld.Ship.Crew.Quantity)*0.4);
	SetCrewQuantityOverMax(sld, iCrew); // сносим треть команды
	sld.ship.HP = makeint(sti(sld.ship.HP)*0.9); // портим корпус
	AddCrewMorale(sld, -30); // команда врага деморализована внезапным и подлым нападением
	ChangeCrewExp(sld, "Sailors", -30);
	ChangeCrewExp(sld, "Cannoners", -30);
	ChangeCrewExp(sld, "Soldiers", -50); // перебили много наемников
	AddCrewMorale(pchar, 20); // а у наших - наоборот
	DoQuestFunctionDelay("Saga_HitSeaFugas_DetonateReaction", fTemp);
	AddCharacterExpToSkill(pchar, "Sneak", 500);//скрытность
}

void Saga_HitSeaFugas_DetonateReaction(string qName) // Джекман атакует
{
	PlayStereoSound("Voice\Russian\EvilPirates01.wav");
	sld = characterFromId("Jackman");
	sld.AlwaysEnemy = true;
	SetCharacterRelationBoth(sti(GetCharacterIndex("Jackman")), GetMainCharacterIndex(), RELATION_ENEMY);
	Group_SetTaskAttack("Jackman_Frigate", PLAYER_GROUP);
	Group_LockTask("Jackman_Frigate");
	UpdateRelations();
	RefreshBattleInterface();
	AddQuestRecord("BarbTemptation", "22");
}

// Jason: у меня не съехала крыша. Просто в абордажной локации прерывания не отрабатываются.
void Saga_CheckJackmanCabinItems(string qName) // проверяем наличие квестовых предметов
{
	if (CheckCharacterItem(pchar, "splinter_nh") && CheckCharacterItem(pchar, "map_half_blaze") && CheckCharacterItem(pchar, "letter_parol") && CheckCharacterItem(pchar, "witches_hammer")) DoQuestFunctionDelay("Saga_CanReloadFromJackmanCabin", 0.5);
	else DoQuestFunctionDelay("Saga_CheckJackmanCabinRepeat", 0.5);
}

void Saga_CheckJackmanCabinRepeat(string qName) // проверка каждые 3 секунды
{
	DoQuestFunctionDelay("Saga_CheckJackmanCabinItems", 2.5);
}

void Saga_CanReloadFromJackmanCabin(string qName) // собрали все квестовые предметы
{
	log_Testinfo("Выход открыт!");
	RemoveItems(pchar, "map_half_beatriss", 1);
	RemoveItems(pchar, "map_half_blaze", 1);
	GiveItem2Character(pchar, "map_sharp_full");
	DeleteAttribute(pchar, "GenQuest.CannotReloadBoarding"); // можно выходить
}

void Saga_JackmanSink(string qName) // провал Саги
{
	// неписи для остановки: Свенсон, Даниэль, Натаниэль, Элен, Тиракс, Барбазон, Марлоу
	Group_DeleteGroup("Jackman_Frigate");
	Island_SetReloadEnableGlobal("Bermudes", true);
	bQuestDisableMapEnter = false;
	AddQuestRecord("Saga", "23");
	DeleteAttribute(pchar, "questTemp.Saga.BarbTemptation");
	DeleteAttribute(pchar, "GenQuest.LigaAttack"); // киллеры Лиги деактивированы
	LocatorReloadEnterDisable("LaVega_town", "reload6", false); // открываем вход к Маркусу
	Saga_CenturionFail(); // остановочная функция
}

void Saga_JackmanAbordage(string qName) // победили Джекмана
{
	DoQuestCheckDelay("sea_victory", 1.5);
	Group_DeleteGroup("Jackman_Frigate");
	Island_SetReloadEnableGlobal("Bermudes", true);
	bQuestDisableMapEnter = false;
	DeleteAttribute(pchar, "GenQuest.CannotTakeShip");
	DeleteAttribute(pchar, "GenQuest.LigaAttack"); // киллеры Лиги деактивированы
	AddQuestRecord("BarbTemptation", "24");
	LocatorReloadEnterDisable("LaVega_town", "reload6", false); // открываем вход к Маркусу
	pchar.questTemp.Saga.BarbTemptation = "terrax"; // посещение трёх баронов
	// поставим прерывание на Барбазона
	pchar.quest.Saga_storming_group.win_condition.l1 = "location";
	pchar.quest.Saga_storming_group.win_condition.l1.location = "LeFransua_town";
	pchar.quest.Saga_storming_group.function = "Saga_CreateStormingGroup";
	ChangeCharacterComplexReputation(pchar, "fame", 3);
}

void Saga_CreateStormingGroup(string qName) // к Барбазону
{
	bDisableFastReload = true;//закрыть переход
	pchar.quest.Saga_storming_group1.over = "yes"; //снять прерывание если не отработало
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], true);//запретить драться
	// мушкетеры
	for (i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Saga_SGM_"+i, "mush_ctz_"+(rand(2)+4), "man", "mushketer", 25, sti(pchar.nation), -1, false, "soldier"));
		FantomMakeCoolFighter(sld, 25, 80, 100, "", "mushket1", "cartridge", 100);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto16");
		LAi_SetActorType(sld);
		LAi_ActorFollowEverywhere(sld, "", -1);
	}
	for (i=3; i<=6; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Saga_SGM_"+i, "mush_ctz_"+(rand(2)+4), "man", "mushketer", 25, sti(pchar.nation), -1, false, "soldier"));
		FantomMakeCoolFighter(sld, 25, 80, 100, "", "mushket1", "cartridge", 100);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto16");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
		sld.lifeday = 0;
	}
	// солдаты
	for (i=1; i<=7; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Saga_SGS_"+i, "citiz_3"+i, "man", "man", 25, sti(pchar.nation), -1, false, "soldier"));
		FantomMakeCoolFighter(sld, 25, 80, 80, "blade_10", "pistol3", "grapeshot", 100);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto17");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
		sld.lifeday = 0;
	}
	pchar.quest.Saga_storming_group2.win_condition.l1 = "location";
	pchar.quest.Saga_storming_group2.win_condition.l1.location = "LeFransua_townhall";
	pchar.quest.Saga_storming_group2.function = "Saga_StormingGroup";
}

void Saga_StormingGroup(string qName) // поведение сопровождения
{
	for (i=1; i<=2; i++)
	{
		sld = characterFromId("Saga_SGM_"+i);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto"+i);
		LAi_SetActorType(sld);
		DoQuestCheckDelay("Saga_StormingGroupTurn", 0.1);	
	}
}

void Saga_GiveCalendar() // осколки собраны - завершаем квесты баронов
{
	pchar.questTemp.Saga = "calendar"; // обновляем флаг центрального квеста
	DeleteAttribute(pchar, "questTemp.Saga.SharkHunt");
	DeleteAttribute(pchar, "questTemp.Saga.BaronReturn");
	DeleteAttribute(pchar, "questTemp.Saga.BarbTemptation");
	CloseQuestHeader("BaronReturn");
	CloseQuestHeader("BarbTemptation");
	AddQuestRecord("Saga", "25");
}
// <-- искушение Барбазона

// переход к квестам Завещание и Тени
void Saga_MineBanditsDestroyed(string qName) // Свенсон взял рудник самостоятельно
{
	int n;
	n = Findlocation("mine_exit");
	DeleteAttribute(&locations[n], "models.always.Gun1");
	DeleteAttribute(&locations[n], "models.always.Gun2");
	DeleteAttribute(&locations[n], "mine_bandits");
	LocatorReloadEnterDisable("mine_exit", "reload1_back", false);
	n = Findlocation("mine_01");
	DeleteAttribute(&locations[n], "mine_bandits");
	LocatorReloadEnterDisable("mine_01", "reload3_back", false);
	pchar.questTemp.Saga = "mine"; // обновляем флаг
	sld = characterFromId("Svenson");
	ChangeCharacterAddressGroup(sld, "Santacatalina_houseS1_residence", "sit", "sit1");
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
}

void Saga_MineBanditsAttackOver(string qName) // не пришёл к совместному началу атаки
{
	pchar.quest.Saga_MinePrepareAttack.over = "yes"; //снять прерывание
	SetFunctionTimerCondition("Saga_MineBanditsDestroyed", 0, 0, 6, false); // таймер
}

void Saga_ReturnFromMine(string qName) // взяли рудник вместе
{
	int n;
	n = Findlocation("mine_exit");
	DeleteAttribute(&locations[n], "models.always.Gun2");
	n = Findlocation("mine");
	DeleteAttribute(&locations[n], "models.always.Gun");
	pchar.questTemp.Saga = "mine_1"; // обновляем флаг
	sld = characterFromId("Svenson");
	sld.dialog.currentnode = "First time";
	ChangeCharacterAddressGroup(sld, "Santacatalina_houseS1_residence", "sit", "sit1");
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
}

// --------------------------------- атака рудника бандитов -------------------------------------------
void Saga_MineBanditsPrepareAttack(string qName) // идем на рудник со Свенсоном
{
	pchar.quest.Saga_MineBanditsAttackOver.over = "yes"; //снять прерывание
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	chrDisableReloadToLocation = true;//закрыть локацию
	pchar.GenQuest.CannotWait = true;//запрет ожидания
	// ставим людей Свенсона - 2 офицера + 12 солдат и самого Свенсона
	int iRank = 22+MOD_SKILL_ENEMY_RATE+5;
	int iScl = 70;
	for (i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Svensons_off_"+i, "mercen_2"+(i+3), "man", "man", iRank, PIRATE, -1, true, "soldier"));
		FantomMakeCoolFighter(sld, iRank+8, iScl+8, iScl+8, "blade_21", "pistol6", "bullet", iScl*2+50);
		if (i == 1)
		{
			sld.name = StringFromKey("Saga_58");
			sld.lastname = StringFromKey("Saga_59");
			LAi_SetCheckMinHP(sld, 10, true, "");
		}
		else
		{
			sld.name = StringFromKey("Saga_60");
			sld.lastname = StringFromKey("Saga_61");
		}
		sld.dialog.FileName = "Quest\Saga\OtherNPC.c";
		sld.dialog.currentnode = "Svensons_off";
		sld.greeting = "off_quest";
		LAi_SetStayType(sld);
		ChangeCharacterAddressGroup(sld, "shore53", "soldiers", "soldier"+(i+12));
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	for (i=1; i<=12; i++)
	{
		if (i == 11 || i == 12)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Svensons_sold_"+i, "mush_ctz_"+(i-4), "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Svensons_sold_"+i, "citiz_"+(40+i), "man", "man", iRank, PIRATE, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_10","blade_11"), "pistol3", "grapeshot", iScl*2+50);
		}
		sld.dialog.FileName = "Quest\Saga\OtherNPC.c";
		sld.dialog.currentnode = "Svensons_sold";
		sld.greeting = "off_quest";
		LAi_SetStayType(sld);
		ChangeCharacterAddressGroup(sld, "shore53", "soldiers", "soldier"+i);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	sld = characterFromId("Svenson");
	LAi_SetImmortal(sld, false);
	LAi_SetCheckMinHP(sld, 10, true, "");
	sld.dialog.currentnode = "mine_attack";
	ChangeCharacterAddressGroup(sld, "shore53", "soldiers", "soldier15");
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	// ставим наших бойцов
	for (i=1; i<=8; i++)
	{
		if (i == 1 || i == 2)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Ourmine_sold_"+i, "mush_ctz_"+(i+4), "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Ourmine_sold_"+i, "citiz_"+(30+i), "man", "man", iRank, PIRATE, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_10","blade_11"), "pistol1", "bullet", iScl*2+50);
		}
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "shore53", "goto", "goto"+i);
		LAi_ActorFollowEverywhere(sld, "", -1);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
}

void Saga_PrepareMineAttackTail(string qName) // 
{
	chrDisableReloadToLocation = true;//закрыть локацию
	ref chr = characterFromId("Svenson");
	LAi_CharacterEnableDialog(chr);//разрешение диалога
	if (CheckAttribute(chr, "quest.mine01")) chr.dialog.currentnode = "mine_attack_8";
	else
	{
		if (CheckAttribute(chr, "quest.mine02")) chr.dialog.currentnode = "mine_attack_13";
		else 
		{
			if (CheckAttribute(chr, "quest.mine03")) chr.dialog.currentnode = "mine_attack_17";
			else chr.dialog.currentnode = "mine_attack_3";
		}
	}
	LAi_SetActorType(chr);
	LAi_ActorDialog(chr, pchar, "", -1, 0);
	if (!CheckAttribute(chr, "quest.mine03"))
	{
		for (i=1; i<=11; i++)
		{
			sld = characterFromId("Svensons_sold_"+i);
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		}
	}
	for (i=1; i<=8; i++)
	{
		sld = characterFromId("Ourmine_sold_"+i);
		LAi_SetActorType(sld);
		LAi_ActorFollowEverywhere(sld, "", -1);
	}
}

void Saga_MineAttackTail(string qName) // 
{
	chrDisableReloadToLocation = true;//закрыть локацию
}

void Saga_SvensonMineexitAttack(string qName) // 
{
	sld = characterFromId("Svenson");
	LAi_CharacterEnableDialog(sld);//разрешение диалога
	ChangeCharacterAddressGroup(sld, "mine_exit", "reload", "reload2_back");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	for (i=1; i<=2; i++)
	{
		if (GetCharacterIndex("Svensons_off_"+i) != -1)
		{
			sld = characterFromId("Svensons_off_"+i);
			if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 2) continue;
			else
			{
				ChangeCharacterAddressGroup(sld, "mine_exit", "reload", "reload2_back");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		}
	}
	for (i=1; i<=8; i++)
	{
		sld = characterFromId("Ourmine_sold_"+i);
		ChangeCharacterAddressGroup(sld, "mine_exit", "reload", "reload2_back");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	if (LAi_group_GetTarget(pchar) <= 0)
	{
		DoQuestCheckDelay("hide_weapon", 1.5);
		DoQuestCheckDelay("Saga_BanditsDestroyed", 0.5);
		for (i=1; i<=8; i++)
		{
			sld = characterFromId("Ourmine_sold_"+i);
			LAi_CharacterDisableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
	}
}

void Saga_MineGunAttack(string qName) // устанавливаем орудие
{
	chrDisableReloadToLocation = true;//закрыть локацию
	bDisableCharacterMenu = true;//лоченые интерфейсы
	InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
	locCameraLockNearHero(-5.0, 2.0, -5.0, 1000, true);
	DoQuestCheckDelay("Saga_MineSetMusic", 0.8);
	ChangeCharacterAddressGroup(pchar, "mine", "soldiers", "commander");
	for (i=1; i<=8; i++)
	{
		if (GetCharacterIndex("Ourmine_sold_"+i) != -1)
		{
			sld = characterFromId("Ourmine_sold_"+i);
			ChangeCharacterAddressGroup(sld, "mine", "soldiers", "gunteam"+i);
			if (i == 1)
			{
				LAi_SetStayType(sld);
				LAi_group_MoveCharacter(sld, "TMP_FRIEND");
				sld.MusketerDistance = 0;
			}
			else LAi_SetActorType(sld);
		}
	}
	if (GetCharacterIndex("Svensons_sold_12") != -1 && pchar.questTemp.Saga.MineAttack == "soldiers")
	{
		sld = characterFromId("Svensons_sold_12");
		ChangeCharacterAddressGroup(sld, "mine", "soldiers", "gunteam11");
		LAi_SetActorType(sld);
	}
	sld = characterFromId("Svensons_off_1");
	sld.dialog.currentnode = "gunner";
	sld.greeting = " ";
	ChangeCharacterAddressGroup(sld, "mine", "soldiers", "gunner");
	LAi_SetActorType(sld);
	DoQuestFunctionDelay("Saga_MineGunAttackStart", 5.0);
	LAi_SetActorType(pchar);
	int iRank = 22+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 80;
	for (i=1; i<=6; i++) // ставим вражеских мушкетеров
	{
		sld = GetCharacter(NPC_GenerateCharacter("Mine_Bandos_05_"+i, "mush_ctz_"+(rand(2)+10), "man", "mushketer", iRank, PIRATE, 0, true, "soldier"));
		FantomMakeCoolFighter(sld, iRank, 80, 80, "", "mushket1", "cartridge", iScl*2+50);
		sld.MusketerDistance = 0; 
		LAi_SetWarriorType(sld);
		ChangeCharacterAddressGroup(sld, "mine", "goto", "mush"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
}

void Saga_MineGunAttackStart(string qName)
{
	LAi_SetPlayerType(pchar);
	locCameraResetState();
	sld = characterFromId("Svensons_off_1");
	LAi_ActorDialogNow(sld, pchar, "", -1);
}

void Saga_MineFightLock(string qName)
{
	CreateLocationParticles("ShipExplode", "rld", "warrior", 0, 0, 0, "boom");
	CreateLocationParticles("blast_dirt", "rld", "warrior", 0, 0, 0, "");
	CreateLocationParticles("blast_inv", "rld", "warrior", 0, 0, 0, "");
	LAi_KillCharacter(pchar);
}

void Saga_MineAttackMines(string qName)
{
	DoQuestReloadToLocation("mine_mines", "reload", "reload1", "Saga_MineAttackMinesLock");
	int iRank = 22+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 70;
	LAi_group_Register("Mine_enemy");
	LAi_group_SetLookRadius("Mine_enemy", 20);
	LAi_group_SetHearRadius("Mine_enemy", 15);		
	LAi_group_SetHearRadius(LAI_GROUP_PLAYER, 5);
	for (i=1; i<=2; i++) // ставим вражеских мушкетеров
	{
		sld = GetCharacter(NPC_GenerateCharacter("Mine_Bandos_mines_"+i, "mush_ctz_"+(rand(2)+10), "man", "mushketer", iRank, PIRATE, -1, true, "soldier"));
		FantomMakeCoolFighter(sld, iRank, 60, 60, "", "mushket1", "cartridge", iScl*2+50);
		sld.MusketerDistance = 0; 
		LAi_SetWarriorType(sld);
		ChangeCharacterAddressGroup(sld, "mine_mines", "soldiers", "soldier"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "Mine_enemy");
	}
	for (i=3; i<=14; i++) // бандюки
	{
		if (i == 4 || i == 6 || i == 8) continue;
		sld = GetCharacter(NPC_GenerateCharacter("Mine_Bandos_mines_"+i, "citiz_"+(rand(9)+51), "man", "man", iRank, PIRATE, -1, true, "soldier"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2+50);
		ChangeCharacterAddressGroup(sld, "mine_mines", "goto", "goto"+i);
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_group_MoveCharacter(sld, "Mine_enemy");
	}
	for (i=1; i<=5; i++) // каторжники
	{
		sld = GetCharacter(NPC_GenerateCharacter("MineConvict_"+i, "prizon_"+(rand(7)+1), "man", "man_B", 10, PIRATE, 1, true, "native"));
		SetFantomParamFromRank(sld, 10, true);
		sld.dialog.Filename = "Quest\Saga\OtherNPC.c";
		sld.dialog.currentnode = "convict";
		sld.greeting = "convict";
		GiveItem2Character(sld, RandPhraseSimple("slave_01","topor_05"));
		EquipCharacterbyItem(sld, RandPhraseSimple("slave_01","topor_05"));
		ChangeCharacterAddressGroup(sld, "mine_mines", "monsters", "convict"+i);
		LAi_SetStayType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	}
}

void Saga_FindMineLetter(string qName)
{
	pchar.quest.Saga_MineAttack_09.win_condition.l1 = "location";
	pchar.quest.Saga_MineAttack_09.win_condition.l1.location = "mine";
	pchar.quest.Saga_MineAttack_09.function = "Saga_FindMineGold";
}

void Saga_FindMineGold(string qName)
{
	sld = characterFromId("Svenson");
	sld.dialog.currentnode = "mine_attack_37";
	ChangeCharacterAddressGroup(sld, "mine", "reload", "reload4");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}
// <-- атака рудника

// ----------------------------------------завещание Шарпа-----------------------------------------------
void Saga_GoldForLoxly(string qName) // нужны деньги для адвоката
{
	LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", false); // открыть кабинет Свенсона
	LocatorReloadEnterDisable("Pirates_town", "reload3_back", false); // открыть резиденцию Исла Тесоро
	// садим Акулу в резиденцию
	if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
	{
		sld = characterFromId("Dodson");
		sld.dialog.currentnode = "First time";
		ChangeCharacterAddressGroup(sld, "Pirates_townhall", "sit", "sit1");
		sld.standUp = true; //вставать и нападать на врага
		LAi_SetHuberType(sld);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
		LAi_SetImmortal(sld, true);
		sld.watchBoxes = true; 
	}
	else // садим Тиракса, а на его место - Бернара Венсана
	{
		sld = characterFromId("Terrax");
		ChangeCharacterAddressGroup(sld, "Pirates_townhall", "sit", "sit1");
		sld.standUp = true; //вставать и нападать на врага
		LAi_SetHuberType(sld);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
		LAi_SetImmortal(sld, true);
		sld.watchBoxes = true; 
				
		sld = characterFromId("Vensan");
		sld.dialog.FileName = "Mayor\LaVega_Mayor.c";
		sld.dialog.currentnode = "I_know_you_good";
		sld.greeting = "town_pirate";
		ChangeCharacterAddressGroup(sld, "LaVega_townhall", "sit", "sit1");
		sld.standUp = true; //вставать и нападать на врага
		LAi_SetHuberType(sld);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
		LAi_SetImmortal(sld, true);
		sld.watchBoxes = true; 
	}
}

void Saga_CreateMolliganInWorld()
{
	int iRank = 22+MOD_SKILL_ENEMY_RATE;
	int iScl = 70;
	int iCannon = CANNON_TYPE_CANNON_LBS24;
	int iDays = 15;
	if (sti(pchar.rank) < 15 || MOD_SKILL_ENEMY_RATE < 7) iCannon = CANNON_TYPE_CANNON_LBS20;
	sld = GetCharacter(NPC_GenerateCharacter("Molligan", "Molligan", "man", "man", iRank, ENGLAND, iDays, true, "quest"));
	sld.name = StringFromKey("Saga_62");
	sld.lastname = StringFromKey("Saga_63");
	sld.Dialog.Filename = "Quest\Saga\OtherNPC.c";
	sld.DeckDialogNode = "Molligan";
	FantomMakeSmallSailor(sld, SHIP_EASTINDIAMAN, StringFromKey("Saga_64"), iCannon, iScl, iScl, iScl, iScl, iScl);
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_13", "pistol1", "bullet", iScl*2+50);
	sld.Ship.Mode = "pirate";	
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true; 
	sld.DontRansackCaptain = true; 
	if (MOD_SKILL_ENEMY_RATE > 7) sld.MultiFighter = 1.5; // мультифайтер
	RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1; //всегда первый - это будет важно потом
	SetCharacterGoods(sld, GOOD_EBONY, 50);
	SetCharacterGoods(sld, GOOD_MAHOGANY, 80);
	SetCharacterGoods(sld, GOOD_SANDAL, 100);//положить бакаут
	//в морскую группу кэпа
	string sGroup = "Molligan_Group";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	if (rand(1) == 0) sld.cityShore = "Shore55";
	else sld.cityShore = "Shore53";
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = StringFromKey("Saga_65");
	Map_CreateTrader(sld.cityShore, "Bridgetown", sld.id, iDays);
	
	SetFunctionTimerCondition("Saga_MolliganInWorldOver", 0, 0, iDays+1, false);
	//на захват либо потопление абордажем
	pchar.quest.Saga_Molligan_Abordage.win_condition.l1 = "Character_Capture";
	pchar.quest.Saga_Molligan_Abordage.win_condition.l1.character = "Molligan";
	pchar.quest.Saga_Molligan_Abordage.function = "Saga_MolliganAbordage";//взяли на абордаж
	//на потопление орудиями
	pchar.quest.Saga_Molligan_Sink.win_condition.l1 = "Character_sink";
	pchar.quest.Saga_Molligan_Sink.win_condition.l1.character = "Molligan";
	pchar.quest.Saga_Molligan_Sink.function = "Saga_MolliganSink";//потопили
}		

void Saga_MolliganInWorldOver(string qName) // упустили Моллигана
{
	pchar.questTemp.Saga.Bakaut = "fail";
	AddQuestRecord("Testament", "4");
	pchar.questTemp.Saga = "removebakaut"; // флаг на адвоката
}

void Saga_MolliganAttack() // атака Моллигана - обработка в АИ
{
	log_info(StringFromKey("Saga_70"));
	PlaySound("interface\notebook.wav");
	sld = characterFromId("Molligan");
	sld.AlwaysEnemy = true;
	SetCharacterRelationBoth(sti(GetCharacterIndex("Molligan")), GetMainCharacterIndex(), RELATION_ENEMY);
	Group_SetTaskAttack("Molligan_Group", PLAYER_GROUP);
	Group_LockTask("Molligan_Group");
	UpdateRelations();
	RefreshBattleInterface();
}

void Saga_MolliganCriticalAttack() // атакуем Моллигана - обработка в АИ
{
	DeleteAttribute(pchar, "questTemp.Saga.Molligan.friend");
	log_info(StringFromKey("Saga_66"));
	sld = characterFromId("Molligan");
	PlayStereoSound("Sea Battles\sdavl_kriki_005.wav");
	int iCrew = makeint(sti(sld.Ship.Crew.Quantity)*0.67); 
	SetCrewQuantityOverMax(sld, iCrew); // сносим треть команды
	AddCrewMorale(sld, -20); // команда врага деморализована внезапным и подлым нападением
	sld.AlwaysEnemy = true;
	SetCharacterRelationBoth(sti(GetCharacterIndex("Molligan")), GetMainCharacterIndex(), RELATION_ENEMY);
	Group_SetTaskAttack("Molligan_Group", PLAYER_GROUP);
	Group_LockTask("Molligan_Group");
	UpdateRelations();
	RefreshBattleInterface();
}

void Saga_MolliganAbordage(string qName) //проверяем Устрицу после боя
{
	DoQuestCheckDelay("sea_victory", 1.5);
	pchar.quest.Saga_MolliganInWorldOver.over = "yes"; //снять прерывание
	pchar.quest.Saga_Molligan_Sink.over = "yes"; //снять прерывание
	Group_DeleteGroup("Molligan_Group");
	int iUst = 0;
	string sTemp;
	for(i = 0; i < COMPANION_MAX; i++)
	{
		iTemp = GetCompanionIndex(PChar, i);
		if(iTemp > 0)
		{
			sld = GetCharacter(iTemp);
			if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_EASTINDIAMAN && sld.ship.name == StringFromKey("Saga_64")) iUst = 1;
		}
	} // есть ли у нас Устрица
	if (iUst == 1) pchar.questTemp.Saga.Oyster = "true"; // есть
	if (CheckCharacterItem(pchar, "letter_parol")) // нашел записку
	{
		sTemp = StringFromKey("Saga_67");
		pchar.quest.Saga_RozencraftWG.win_condition.l1 = "location";
		pchar.quest.Saga_RozencraftWG.win_condition.l1.location = "Trinidad";
		pchar.quest.Saga_RozencraftWG.function = "Saga_CheckRozencraftWG";
		SetFunctionTimerCondition("Saga_RozencraftWGOver", 0, 0, 8, false);
		sld = ItemsFromID("letter_parol");
		sld.price = 10;
	}
	else sTemp = StringFromKey("Saga_68");
	AddQuestRecord("Testament", "6");
	AddQuestUserData("Testament", "sText", sTemp);
	pchar.questTemp.Saga.Bakaut = "find";
	pchar.questTemp.Saga = "sellbakaut";
}

void Saga_MolliganSink(string qName) // потопили Моллигана
{
	pchar.quest.Saga_MolliganInWorldOver.over = "yes"; //снять прерывание
	pchar.quest.Saga_Molligan_Abordage.over = "yes"; //снять прерывание
	Group_DeleteGroup("Molligan_Group");
	pchar.questTemp.Saga.Bakaut = "fail";
	AddQuestRecord("Testament", "5");
	pchar.questTemp.Saga = "removebakaut"; // флаг на адвоката
}

void Saga_RozencraftWGOver(string qName) // снять Розенкрафта
{
	pchar.quest.Saga_RozencraftWG.over = "yes"; //снять прерывание
}

void Saga_RemoveOuster() //удаление Устрицы
{
	if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_EASTINDIAMAN && pchar.ship.name == StringFromKey("Saga_64"))
	{
		pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
		pchar.Ship.name = StringFromKey("Saga_69");
		SetBaseShipData(pchar);
		SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
	}
	else
	{
		for(i = 1; i < COMPANION_MAX; i++)
		{
			int iTemp = GetCompanionIndex(PChar, i);
			if(iTemp > 0)
			{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_EASTINDIAMAN && sld.ship.name == StringFromKey("Saga_64"))
				{
					pchar.GanQuest.CompanionIndex = sld.Index;
					sld = GetCharacter(sti(pchar.GanQuest.CompanionIndex));
					RemoveCharacterCompanion(PChar, sld);
					AddPassenger(PChar, sld, false);
				}
			}
		}
    }
}

void Saga_CheckRozencraftWG(string qName) // устанавливаем Розенкрафта
{
	int iUst = 0;
	for(i = 0; i < COMPANION_MAX; i++)
	{
		iTemp = GetCompanionIndex(PChar, i);
		if(iTemp > 0)
		{
			sld = GetCharacter(iTemp);
			if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_EASTINDIAMAN && sld.ship.name == StringFromKey("Saga_64")) iUst = 1;
		}
	} // есть ли у нас Устрица
	// двойная защита от жухления геймеров
	if (iUst == 1 && CheckAttribute(pchar, "questTemp.Saga.Oyster")) pchar.questTemp.Saga.Oyster = "cantalk";
	Group_FindOrCreateGroup("Rozencraft_Group");
	Group_SetType("Rozencraft_Group", "war");
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10;
	if (iRank > 40) iRank = 40;
	int iScl = 100;
	sld = GetCharacter(NPC_GenerateCharacter("Rozencraft", "Rozencraft", "man", "man", iRank, HOLLAND, -1, true, "quest"));
	sld.name = StringFromKey("Saga_71");
	sld.lastname = StringFromKey("Saga_72");
	sld.Dialog.Filename = "Quest\Saga\Rozencraft.c";
	sld.DeckDialogNode = "Rozencraft";
	FantomMakeSmallSailor(sld, SHIP_GALEON_H, "", CANNON_TYPE_CANNON_LBS32, iScl, iScl, iScl, iScl, iScl);
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol5", "bullet", iScl*2+100);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "war";
	Character_SetAbordageEnable(sld, false);
	if (CheckAttribute(pchar, "questTemp.Saga.Oyster") && pchar.questTemp.Saga.Oyster == "cantalk") sld.AlwaysFriend = true;
	SetCharacterPerk(sld, "MusketsShoot");
	Group_AddCharacter("Rozencraft_Group", "Rozencraft");
	Group_SetGroupCommander("Rozencraft_Group", "Rozencraft");
	Group_SetTaskNone("Rozencraft_Group");//нет задачи
	Group_SetAddress("Rozencraft_Group", "Trinidad", "quest_ships", "quest_ship_8");
	Group_LockTask("Rozencraft_Group");
	
	pchar.quest.Saga_Rozencraft_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Saga_Rozencraft_AfterBattle.win_condition.l1.group = "Rozencraft_Group";
	pchar.quest.Saga_Rozencraft_AfterBattle.function = "Saga_RozencraftAfterBattle";
	pchar.quest.Saga_Rozencraft_GetOut.win_condition.l1 = "MapEnter";
    pchar.quest.Saga_Rozencraft_GetOut.function = "Saga_RozencraftGetOut";
}

void Saga_RozencraftAfterBattle(string qName) //взял и напал зачем-то - накажем
{
	pchar.quest.Saga_Rozencraft_GetOut.over = "yes"; //снять прерывание
	Group_DeleteGroup("Rozencraft_Group");
	ChangeCharacterNationReputation(pchar, HOLLAND, -15);
	DeleteAttribute(pchar, "GenQuest.Bakaut"); // конец генератора
}

void Saga_RozencraftGetOut(string qName) //ушёл на карту - галеон тоже ушёл
{
	pchar.quest.Saga_Rozencraft_AfterBattle.over = "yes"; //снять прерывание
	Group_DeleteGroup("Rozencraft_Group");
}

void Saga_RemainGoldLoxly(string qName) // просрочили заплатить адвокату
{
	sld = characterFromId("Loxly");
	sld.dialog.currentnode = "saga_40";
	LocatorReloadEnterDisable("PortRoyal_town", "houseSp4", true); // закроем вход к Локсли
	ChangeCharacterNationReputation(pchar, ENGLAND, -10);
}

//----------------------------------------генератор торговли бакаутом-------------------------------------
void Bakaut_RozencraftDie(string qName) // убит квестодатель - нет квеста
{
	log_testinfo("Квестодатель убит - генератор деактивирован!");
	Group_DeleteGroup("Rozencraft_Group");
	DeleteAttribute(pchar, "GenQuest.Bakaut"); // конец генератора
}

void Bakaut_RozencraftRemove(string qName) // галеон ушёл в одно из мест
{
	int i = rand(5);
	switch(i)
	{
		case 0: pchar.GenQuest.Bakaut.Island = "Curacao"; break;
		case 1: pchar.GenQuest.Bakaut.Island = "Cumana"; break;
		case 2: pchar.GenQuest.Bakaut.Island = "Hispaniola1"; break;
		case 3: pchar.GenQuest.Bakaut.Island = "Portobello"; break;
		case 4: pchar.GenQuest.Bakaut.Island = "Guadeloupe"; break;
		case 5: pchar.GenQuest.Bakaut.Island = "Cuba2"; break;
	}
	pchar.GenQuest.Bakaut.Value = rand(5)*10+50; // мин объём следующей поставки
	pchar.GenQuest.Bakaut.DaysQty = rand(15)+15; // сколько дней будет крейсировать после получения наводки
	Group_SetAddress("Rozencraft_Group", pchar.GenQuest.Bakaut.Island, "quest_ships", "quest_ship_"+(4+rand(4)));
	DeleteAttribute(pchar, "GenQuest.Bakaut.Info");
}

void Bakaut_SvensonAttrReturn(string qName) // вертаем атрибут Свенсону
{
	sld = characterFromId("Svenson");
	sld.quest.trade_bakaut = "true";
}
// <-- генератор торговли бакаутом

//----------------------------------------генератор торговли канатами---------------------------------021012
void Ropes_FadeyAttrReturn(string qName) // вертаем атрибут Фадею
{
	sld = characterFromId("Fadey");
	sld.quest.ropes = "true";
}

//----------------------------------------генератор торговли шелком---------------------------------161012
void Silk_TraderAttrReturn(string qName) // вертаем атрибут
{
	sld = characterFromId("HWICBoss");
	sld.quest.silk = "true";
}

// ----------------------------------------тени прошлого-----------------------------------------------
void Saga_SetBaldMaggy(string qName) // ставим плешивую мэгги
{
	bQuestDisableMapEnter = true;
	pchar.Cheats.SeaTeleport = true;
	Group_FindOrCreateGroup("BaldMaggy_Group");
	Group_SetType("BaldMaggy_Group", "trade");
	sld = GetCharacter(NPC_GenerateCharacter("Benson", "trader_10", "man", "man", 15, ENGLAND, -1, false, "quest"));
	sld.name = StringFromKey("Saga_73");
	sld.lastname = StringFromKey("Saga_74");
	sld.Dialog.Filename = "Quest\Saga\OtherNPC.c";
	sld.DeckDialogNode = "Benson";
	FantomMakeCoolSailor(sld, SHIP_BARKENTINE, StringFromKey("Saga_75"), CANNON_TYPE_CANNON_LBS12, 40, 40, 40);
	FantomMakeCoolFighter(sld, 15, 40, 40, "blade_10", "pistol1", "bullet", 50);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "trade";
	sld.Abordage.Enable = true;
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable = true; 
	LAi_SetImmortal(sld, true); // сплошная защита от дурака
	Group_AddCharacter("BaldMaggy_Group", "Benson");
	Group_SetGroupCommander("BaldMaggy_Group", "Benson");
	Group_SetTaskNone("BaldMaggy_Group");//нет задачи
	Group_SetAddress("BaldMaggy_Group", "Antigua", "quest_ships", "quest_ship_1");
	Group_LockTask("BaldMaggy_Group");
}

void Saga_SetBakerBoat(string qName) // ставим баркас с Бейкером - обработка в АИ
{
	bQuestDisableMapEnter = true;
	pchar.Cheats.SeaTeleport = true;
	pchar.nation = FRANCE; // принудительно
	pchar.DisableChangeFlagMode = true; // запретить менять флаг
	pchar.questTemp.Saga.Shadows.Baker = "true";
	Group_FindOrCreateGroup("Baker_Group");
	Group_SetType("Baker_Group", "trade");
	sld = GetCharacter(NPC_GenerateCharacter("Baker_Cap", "trader_1", "man", "man", 10, ENGLAND, -1, false, "quest"));
	sld.name = "";
	sld.lastname = "";
	sld.FaceId = 333; // пустой кораблик
	FantomMakeCoolSailor(sld, SHIP_TARTANE, " ", CANNON_TYPE_NONECANNON, 10, 10, 10);
	SetCrewQuantityOverMax(sld, 0);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "trade";
	sld.DontDeskTalk = true;
	sld.Abordage.Enable = true;
	sld.ShipEnemyDisable = true; 
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND); // тестить
	LAi_SetImmortal(sld, true); // сплошная защита от дурака
	sld.ship.masts.mast2 = 1;
	ref realShip = GetRealShip(GetCharacterShipType(sld));
	realShip.lowpolycrew = 0; // убрать матросиков с палубы корабля
	Group_AddCharacter("Baker_Group", "Baker_Cap");
	Group_SetGroupCommander("Baker_Group", "Baker_Cap");
	Group_SetTaskNone("Baker_Group");//нет задачи
	Group_SetAddress("Baker_Group", "Dominica", "quest_ships", "quest_ship_8");
	Group_LockTask("Baker_Group");
}

void Saga_BakerToCabin()
{
	DeleteAttribute(pchar, "questTemp.Saga.Shadows.Baker");
	DeleteAttribute(pchar, "DisableChangeFlagMode");
	Log_Info(StringFromKey("Saga_76"));
	PlaySound("interface\notebook.wav");
	AddQuestRecord("Shadows", "4");
	sld = GetCharacter(NPC_GenerateCharacter("Baker", "Baker", "man", "man_B", 1, ENGLAND, -1, false, "quest"));
	sld.name = StringFromKey("Saga_77");
	sld.lastname = StringFromKey("Saga_78");
	sld.greeting = "baker";
    sld.Dialog.Filename = "Quest\Saga\Baker.c";
	sld.dialog.currentnode = "baker";
	sld.rank = 28;
	LAi_SetHP(sld, 150, 150); 
	SetSelfSkill(sld, 20, 20, 70, 20, 40);
	SetShipSkill(sld, 20, 40, 10, 10, 15, 5, 8, 95, 50);
	SetSPECIAL(sld, 6, 6, 7, 6, 9, 6, 5);
	SetCharacterPerk(sld, "Doctor1");
	SetCharacterPerk(sld, "Doctor2");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "BasicCommerce");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "Gunman");
	GiveItem2Character(sld, "blade_11");
	sld.equip.blade = "blade_11";
	GiveItem2Character(sld, "pistol1");
	EquipCharacterbyItem(sld, "pistol1");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
    TakeNItems(sld, "bullet", 20);
	AddItems(sld, "gunpowder", 20);
	int iShipType = GetCharacterShipType(pchar);
	ref rShip = GetRealShip(iShipType);
	sTemp = "My_" + rShip.CabinType;
	sld = characterFromId("Baker");
	ChangeCharacterAddressGroup(sld, sTemp, "rld", "aloc0");
	LAi_SetStayType(sld);
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, false);
	DeleteAttribute(pchar, "Cheats.SeaTeleport");
}
		
void Saga_JessikaIsland(string qName) // вышли на риф
{
	// ориентируем на день в обязательном порядке
	int iTime, iAddTime;
	iTime = sti(environment.time);
	if (iTime >= 21) iAddTime = 24 - iTime + 12;
	if (iTime < 7) iAddTime = 12 - iTime;
	if (iTime >= 7 && iTime < 21) iAddTime = 24  + 12 - iTime;
	StoreDayUpdate();
	WaitDate("",0,0,0,iAddtime,5);
	RecalculateJumpTable();
	RefreshWeather();
	RefreshLandTime();
	// разложим скелетов
	int iRank = 22+MOD_SKILL_ENEMY_RATE*2;
	int iScl = 65;
	for (int i=1; i<=6; i++)
	{			
		sld = GetCharacter(NPC_GenerateCharacter("Reef_skeleton_"+i, "skel"+(rand(3)+1), "skeleton", "skeleton", iRank, PIRATE, -1, false, "quest"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_13", "", "", iScl);
		if (MOD_SKILL_ENEMY_RATE > 4) sld.cirassId = Items_FindItemIdx("cirass3");
		if (i > 5)
		{
			sld.cirassId = Items_FindItemIdx("cirass1");
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				float fMft = MOD_SKILL_ENEMY_RATE/10;
				sld.MultiFighter = 0.8+fMft; // мультифайтер
			}
		}
		LAi_SetActorType(sld);
		LAi_ActorSetLayMode(sld);
		ChangeCharacterAddressGroup(sld, "shore67", "quest", "skeleton"+i);
		LAi_SetImmortal(sld, true);
	}
	// заставим исследовать риф
	chrDisableReloadToLocation = true;//закрыть локацию
	pchar.GenQuest.CannotWait = true;//запрет ожидания
	pchar.quest.Saga_Jessika_Reef.win_condition.l1 = "locator";
	pchar.quest.Saga_Jessika_Reef.win_condition.l1.location = "shore67";
	pchar.quest.Saga_Jessika_Reef.win_condition.l1.locator_group = "quest";
	pchar.quest.Saga_Jessika_Reef.win_condition.l1.locator = "jessika";
	pchar.quest.Saga_Jessika_Reef.function = "Saga_JessikaReef";
}

void Saga_JessikaReef(string qName) // исследовали риф
{
	chrDisableReloadToLocation = false;
	DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
	AddQuestRecord("Shadows", "7");
	// прерывание на ночь
	pchar.quest.Saga_Jessika_Stay.win_condition.l1 = "Hour";
	pchar.quest.Saga_Jessika_Stay.win_condition.l1.start.hour = 0.00;
	pchar.quest.Saga_Jessika_Stay.win_condition.l1.finish.hour = 2.00;
	pchar.quest.Saga_Jessika_Stay.win_condition.l2 = "location";
	pchar.quest.Saga_Jessika_Stay.win_condition.l2.location = "shore67";
	pchar.quest.Saga_Jessika_Stay.function = "Saga_CreateJessikaGhost";
}

void Saga_CreateJessikaGhost(string qName) // ставим Джессику
{
	ResetSoundScheme();
	ref chr = &Locations[FindLocation(pchar.location)];
	chr.type = "seashore";
	chrDisableReloadToLocation = true;//закрыть локацию
	pchar.GenQuest.CannotWait = true;//запрет ожидания
	sld = characterFromId("Svenson");
	if (CheckAttribute(sld, "quest.jessika")) DeleteAttribute(sld, "quest.jessika");
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = MOD_SKILL_ENEMY_RATE*6;
	int iAdd = MOD_SKILL_ENEMY_RATE*60;
	// ставим Джесс
	pchar.questTemp.Saga.Attack = true; // обработка в АИ
	pchar.questTemp.Saga.Jess_Fightstage = "first";
	sld = GetCharacter(NPC_GenerateCharacter("Jessika", "Ghost_1", "woman", "jess", 1, PIRATE, -1, false, "quest"));
	sld.name = StringFromKey("Saga_79");
	sld.lastname = StringFromKey("Saga_80");
	sld.greeting = "jessika_0";
    sld.Dialog.Filename = "Quest\Saga\Jessika.c";
	sld.dialog.currentnode = "reef";
	sld.monster = true; // признак нежити
	sld.rank = 50;
	LAi_SetHP(sld, 250+iAdd, 250+iAdd); 
	SetSelfSkill(sld, 40+iScl, 40+iScl, 40+iScl, 40+iScl, 40+iScl);
	SetShipSkill(sld, 1, 50, 70, 70, 90, 50, 70, 50, 100);
	SetSPECIAL(sld, 10, 10, 10, 3, 3, 10, 10);
	if (MOD_SKILL_ENEMY_RATE > 4)
	{
		SetCharacterPerk(sld, "Energaiser");
		SetCharacterPerk(sld, "SwordplayProfessional");
		SetCharacterPerk(sld, "HardHitter");
	}
	float fMft = MOD_SKILL_ENEMY_RATE/10;
	sld.MultiFighter = 1.0+fMft; // мультифайтер
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "BladeDancer");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "WindCatcher");
	SetCharacterPerk(sld, "SailsMan");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "LongRangeGrappling");
	SetCharacterPerk(sld, "GrapplingProfessional");
	GiveItem2Character(sld, "blade_25");
	sld.equip.blade = "blade_25";
	sld.cirassId = Items_FindItemIdx("cirass1"); 
	if (MOD_SKILL_ENEMY_RATE < 5) sld.cirassId = Items_FindItemIdx("cirass3"); 
	GiveItem2Character(sld, "letter_beatriss"); // дать письмо
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	LAi_SetCheckMinHP(sld, 10, true, "Saga_JessikaFirstKick"); // первый фокус
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "shore67", "quest", "jessika");
}

void Saga_CheckEnemyDistance() // расчет дистанции до локатора с Джесс
{
	float fdist;
	if (pchar.location == "shore67")
	{
		if (pchar.questTemp.Saga.Jess_Fightstage == "first")
		{
			if (GetCharacterDistByLoc(pchar, "quest", "jessika", &fdist))
			{
				if (fdist < 1.5) Saga_JessikaAttack();
			}
		}
		if (pchar.questTemp.Saga.Jess_Fightstage == "next")
		{
			if (GetCharacterDistByLoc(pchar, "quest", sTotalTemp, &fdist))
			{
				if (fdist < iTotalTemp) Saga_JessikaTalkAttack();
			}
		}
	}
}

void Saga_JessikaAttack() // Джесс атакует - подраться придётся в любом случае
{
	DeleteAttribute(pchar, "questTemp.Saga.Attack");
	sld = characterFromId("Jessika");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	SetMusic("music_teleport");
}

void Saga_JessikaTalkAttack() // переходы между стадиями
{
	DoQuestCheckDelay("hide_weapon", 0.5);//убрать оружие
	DeleteAttribute(pchar, "questTemp.Saga.Attack");
	SetMusic("music_teleport");
	sld = characterFromId("Jessika");
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);
}

void Saga_JessFireStep(string qName) // сунулся в огонь
{
	LAi_KillCharacter(pchar);
}

void Saga_FindBeatrissLetter(string qName) // нашли письмо Беатрисс
{
	chrDisableReloadToLocation = false;//открыть локацию
	DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
	AddQuestRecord("Shadows", "8");
	AddQuestRecordInfo("Letter_beatriss", "1");
	sld = ItemsFromID("letter_jess");
	sld.price = 1; // страницу можно выкладывать 270912 
}

void Saga_JessikaOnJamaica(string qName) // прибытие на Ямайку
{
	bQuestDisableMapEnter = true;//закрыть карту - чтобы не ушёл
	pchar.GenQuest.MapClosedNoBattle = true;
	chrDisableReloadToLocation = true;//закрыть локацию
	pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	sld = characterFromId("Jessika");
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, "shore36", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Saga_JessikaShoreWait(string qName) // прерывание на итоговую встречу
{
	pchar.quest.Saga_Jessika_Final.win_condition.l1 = "Hour";
	pchar.quest.Saga_Jessika_Final.win_condition.l1.start.hour = 0.00;
	pchar.quest.Saga_Jessika_Final.win_condition.l1.finish.hour = 2.00;
	pchar.quest.Saga_Jessika_Final.win_condition.l2 = "location";
	pchar.quest.Saga_Jessika_Final.win_condition.l2.location = "shore36";
	pchar.quest.Saga_Jessika_Final.function = "Saga_JessikaOnJamaica";
}
// <-- Тени прошлого

// ------------------------------- деактивация Саги в случае провалов ---------------------------------------
void Saga_CenturionFail() // провал после потопления Центуриона
{
	// Даниэль - к разговору
	sld = characterFromId("Danielle");
	sld.quest.talk = "failcenturion";
	pchar.quest.Saga_Fail_centurion.win_condition.l1 = "Location_Type";
	pchar.quest.Saga_Fail_centurion.win_condition.l1.location_type = "town";
	pchar.quest.Saga_Fail_centurion.function = "Saga_DannyTalk";
	// Элен - к разговору
	sld = characterFromId("Helena");
	sld.quest.talk = "failcenturion";
	pchar.quest.Saga_Fail_centurion1.win_condition.l1 = "Location_Type";
	pchar.quest.Saga_Fail_centurion1.win_condition.l1.location_type = "town";
	pchar.quest.Saga_Fail_centurion1.function = "Saga_HelenaTalk";
	pchar.questTemp.Saga = "fail_centurion"; // для Свенсона
	// Левассера - к барьеру!
	sld = characterFromId("Tortuga_Mayor");
	LAi_LoginInCaptureTown(sld, true);
	pchar.questTemp.Sharlie.Hardcore_Tortuga = "true";
	// Jason Долго и счастливо
	pchar.questTemp.Saga.CenturionSink = "true";
}

void Saga_HelenaTalk(string qName) // говорилка Элен
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = characterFromId("Helena");	
	switch (sld.quest.talk)
	{
		case "failcenturion": sld.dialog.currentnode = "failcenturion"; break; // потопили Центурион
		case "late_l1": sld.dialog.currentnode = "late_l1"; break; // проверка первая
		case "late_l2": sld.dialog.currentnode = "late_l2"; break; // проверка после квестов баронов
		case "late_l3": sld.dialog.currentnode = "late_l3"; break; // 3-6 проверки у адвоката
	}
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	
	DeleteQuestCondition("HelenDrinking_IslaTesoroAmbush");
	DeleteQuestCondition("HelenDrinking_AtSHDN");
	DeleteQuestCondition("HelenDrinking_InBlueweldAfterCave");
}

// провал по времени
void Saga_TimeOver(string qName)//общий вызов провала по времени
{
	pchar.questTemp.Saga.Late = true; //атрибут - Сага провалена по времени
	// Левассера - к барьеру!
	sld = characterFromId("Tortuga_Mayor");
	LAi_LoginInCaptureTown(sld, true);
	pchar.questTemp.Sharlie.Hardcore_Tortuga = "true";
}

void Saga_ChangesIslatesoro() // вызов перестановки на Исла-Тесоро
{
	int i = FindColony("Pirates");
	colonies[i].nation = ENGLAND;
	string sColony = "Pirates_town";
	worldMap.labels.(sColony).icon = ENGLAND;
	ref rloc = &Locations[FindLocation("Pirates_town")];
	rloc.EngBase = true;
	LocatorReloadEnterDisable("Pirates_town", "reload3_back", false); // открыть резиденцию
	
	if (CheckAttribute(pchar, "questTemp.Saga.Jackman"))
	{
		LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
		// уберем Тиракса с Ла Веги и усадим туда Валета
		sld = characterFromId("Terrax");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld.lifeday = 0;
		sld = GetCharacter(NPC_GenerateCharacter("Valet", "Valet", "man", "man", 30, PIRATE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 30, 100, 100, "blade_18", "pistol6", "bullet", 200);
		sld.name = StringFromKey("Saga_81");
		sld.lastname = StringFromKey("Saga_82");
		sld.dialog.FileName = "Mayor\LaVega_Mayor.c";
		sld.dialog.currentnode = "First time";
		sld.greeting = "Valet";
		ChangeCharacterAddressGroup(sld, "LaVega_townhall", "sit", "sit1");
		sld.standUp = true; //вставать и нападать на врага
		LAi_SetHuberType(sld);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
		LAi_SetImmortal(sld, true);
		sld.watchBoxes = true; 
	}
	FreeSitLocator("Pirates_townhall", "sit1"); // убираем наместника кто там есть
	// садим офицера-наместника
	sld = GetCharacter(NPC_GenerateCharacter("Sharptown_comandante", "off_eng_6", "man", "man", 30, ENGLAND, -1, true, "quest"));
	FantomMakeCoolFighter(sld, 30, 100, 100, "blade_21", "pistol5", "bullet", 200);
	sld.dialog.FileName = "Quest\Saga\OtherNPC.c";
	sld.dialog.currentnode = "First time";
	sld.greeting = "patrol";
	ChangeCharacterAddressGroup(sld, "Pirates_townhall", "sit", "sit1");
	sld.standUp = true; //вставать и нападать на врага
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	LAi_SetImmortal(sld, true);
	sld.watchBoxes = true; 
	sld = characterFromId("Pirates_shipyarder");
	ChangeCharacterAddressGroup(sld, "none", "", ""); // Алексус ушёл с Исла Тесоро
}

//--------------------------- встроенный мини-квест Корабль главы братства -----------------------------------
void AlexClock_Over(string qName) // хронометр Алекса - овертайм
{
	AddQuestRecord("alex_clock", "6");
	CloseQuestHeader("alex_clock");
	DeleteAttribute(pchar, "questTemp.AlexClock");
}

void AlexClock_Chest(string qName) // четыре разгвоздяя в подземелье
{
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_LocationFightDisable(&Locations[FindLocation("Bermudes_Dungeon")], true);//запретить драться
	int iRank = 25+MOD_SKILL_ENEMY_RATE;
	int iScl = 60;
	for (int i=1; i<=4; i++)
	{
		if (i == 1)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Alexs_bandos_"+i, "mush_ctz_9", "man", "mushketer", iRank+2, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl+5, iScl+5, "", "mushket2", "cartridge", iScl*2+100);
			ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "monsters", "monster"+i);
			sld.Dialog.Filename = "Quest\Saga\OtherNPC.c";
			sld.dialog.currentnode = "Alexs_bandos";
			sld.greeting = "marginal"; 
			LAi_SetGuardianType(sld);
			sld.protector = true;
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Alexs_bandos_"+i, "citiz_"+(46+i), "man", "man", iRank, PIRATE, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, RandPhraseSimple("blade_06","blade_10"), "pistol1", "bullet", iScl*2);
			ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "monsters", "monster"+i);
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
		}
	}
}

void AlexClock_FindChest(string qName) // нашли ларчик
{
	chrDisableReloadToLocation = false;
	LocatorReloadEnterDisable("Bermudes_Dungeon", "reload2_back", true);
	AddQuestRecord("alex_clock", "4");
	pchar.questTemp.AlexClock = "clock";
}

//---------------------- На пару с Акулой belamour legendary edition------------------------------------------------
void SharkGoldFleetStart(string qName) 
{
	LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
}

void SharkGoldFleet30(string qName) 
{
	sld = characterFromId("Dodson");
	sld.dialog.currentnode = "SharkGoldFleet_23";
	LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
	pchar.questTemp.SharkGoldFleet = "fail";
	AddQuestRecord("SharkGoldFleet", "3");
	CloseQuestHeader("SharkGoldFleet");
	if(CheckAttribute(pchar,"questTemp.SharkGoldFleet.LicenceOk")) DeleteAttribute(pchar,"questTemp.SharkGoldFleet.LicenceOk");
	
}

void SharkGoldFleet21(string qName) 
{
	pchar.questTemp.SharkGoldFleet.Fail21 = true;
}

void SGF_CreateCurierInWorld(string qName)
{
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE/2;
	int iScl = MOD_SKILL_ENEMY_RATE+3*sti(pchar.rank);
    string sCapId = "SGFcurierCap";
    string sGroup = "Sea_" + sCapId + "1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	sld = GetCharacter(NPC_GenerateCharacter(sCapId, "off_spa_"+(rand(1)+1), "man", "man", iRank, SPAIN, -1, true, "soldier"));
	FantomMakeSmallSailor(sld, SHIP_CAREERLUGGER, GenerateRandomNameToShip(SPAIN), CANNON_TYPE_CANNON_LBS6, iScl+10, iScl, iScl, iScl, iScl);
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_14", "pistol1", "bullet", iScl*2);
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	TakeNItems(sld, "letter_1", 1);
	ChangeItemDescribe("letter_1", "itmdescr_letter_SharkGoldFleet_1");
	pchar.questTemp.SharkGoldFleet.CurierName = sld.name;
	pchar.questTemp.SharkGoldFleet.Curierlastname = sld.lastname;
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "BasicBattleState");
	SetCharacterPerk(sld, "AdvancedBattleState");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	sld.Ship.Mode = "war";
	sld.AnalizeShips = true;
	sld.mapEnc.type = "war";
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = StringFromKey("Saga_83");
	Group_AddCharacter(sGroup, sCapId);
    Group_SetGroupCommander(sGroup, sCapId);
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "toCurierWait")
	Map_CreateTrader("Caracas", "Portobello", sld.id, 30);
	else Map_CreateTrader("Shore21", "Portobello", sld.id, 30);
	
	// на взятие письма
	pchar.quest.SGF_Curier_TakeLatter.win_condition.l1 = "item"; 
	pchar.quest.SGF_Curier_TakeLatter.win_condition.l1.item = "letter_1";
	pchar.quest.SGF_Curier_TakeLatter.function = "SGF_Curier_TakeLatter"; 
	//на захват либо потопление абордажем
	pchar.quest.SGF_Curier_abordage.win_condition.l1 = "Character_Capture";
	pchar.quest.SGF_Curier_abordage.win_condition.l1.character = "SGFcurierCap";
	pchar.quest.SGF_Curier_abordage.function = "SGF_Curier_AfterBattle";
	//на потопление орудиями
	pchar.quest.SGF_Curier_Sink.win_condition.l1 = "Character_sink";
	pchar.quest.SGF_Curier_Sink.win_condition.l1.character = "SGFcurierCap";
	pchar.quest.SGF_Curier_Sink.function = "SGF_Curier_AfterBattle";
}

void SGF_Curier_AfterBattle(string qName)// уничтожили
{
	Group_DeleteGroup("Sea_SGFcurierCap1");
	pchar.quest.SGF_Curier_abordage.over = "yes"; 
	pchar.quest.SGF_Curier_Sink.over = "yes";
	pchar.quest.SGF_Curier_TakeLatter.over = "yes";
	if (CheckAttribute(pchar, "questTemp.SharkGoldFleet.Cletter")) // взяли письмо
	{
		DeleteAttribute(pchar,"questTemp.SharkGoldFleet.Cletter");
		pchar.questTemp.SharkGoldFleet = "KillCurier";
		AddQuestRecord("SharkGoldFleet", "8");
		AddComplexSeaExpToScill(150, 150, 150, 150, 150, 150, 0);
		ChangeCharacterComplexReputation(pchar, "fame", 1);
		if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToPB10", 0, 0, 10, false);
		else NewGameTip(StringFromKey("Saga_84"));
		DoQuestCheckDelay("sea_victory", 1.5);
		return;
	}
	else 
	{
		sld = characterFromId("Dodson");
		sld.dialog.currentnode = "SharkGoldFleet_23";
		LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
		pchar.questTemp.SharkGoldFleet = "fail";
		AddQuestRecord("SharkGoldFleet", "6");
		CloseQuestHeader("SharkGoldFleet");
		if(CheckAttribute(pchar,"questTemp.SharkGoldFleet.LicenceOk")) DeleteAttribute(pchar,"questTemp.SharkGoldFleet.LicenceOk");
		DeleteAttribute(pchar,"questTemp.SharkGoldFleet.CurierName");
		DeleteAttribute(pchar,"questTemp.SharkGoldFleet.Curierlastname");
	}
}


void SGF_Curier_ReleaseInGlobal() // не успели догнать на глобусе
{
	sld = characterFromId("Dodson");
	sld.dialog.currentnode = "SharkGoldFleet_23";
	LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
	pchar.questTemp.SharkGoldFleet = "fail";
	AddQuestRecord("SharkGoldFleet", "7");
	CloseQuestHeader("SharkGoldFleet");
	if(CheckAttribute(pchar,"questTemp.SharkGoldFleet.LicenceOk")) DeleteAttribute(pchar,"questTemp.SharkGoldFleet.LicenceOk");
	DeleteAttribute(pchar,"questTemp.SharkGoldFleet.CurierName");
	DeleteAttribute(pchar,"questTemp.SharkGoldFleet.Curierlastname");
}

void SGF_Curier_TakeLatter(string qName) // взяли письмо
{
	pchar.questTemp.SharkGoldFleet.Cletter = true;
}

void SharkGoldFleetToPB10 (string qName) 
{
	RemoveItems(PChar, "letter_1", 1);
	ChangeItemDescribe("letter_1", "itmdescr_letter_1");
	sld = characterFromId("Dodson");
	sld.dialog.currentnode = "SharkGoldFleet_23";
	LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
	pchar.questTemp.SharkGoldFleet = "fail";
	if(CheckAttribute(pchar,"SharkGoldFleet.Cletter")) 
	{
		DeleteAttribute(pchar,"questTemp.SharkGoldFleet.Cletter");
		AddQuestRecord("SharkGoldFleet", "9");
	}
	else
	{
		AddQuestRecord("SharkGoldFleet", "15");
	}
	
	CloseQuestHeader("SharkGoldFleet");
	if(CheckAttribute(pchar,"questTemp.SharkGoldFleet.LicenceOk")) DeleteAttribute(pchar,"questTemp.SharkGoldFleet.LicenceOk");
	DeleteAttribute(pchar,"questTemp.SharkGoldFleet.CurierName");
	DeleteAttribute(pchar,"questTemp.SharkGoldFleet.Curierlastname");
}

void SharkGoldFleetExitPO(string qName) 
{
	AddQuestRecord("SharkGoldFleet", "16");
	AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
	LAi_LocationFightDisable(&Locations[FindLocation("PortoBello_PortOffice")], true);
}

void SGF_MCread(string qName)
{
	DoQuestFunctionDelay("SGF_MCComplRead", 5.0);
}

void SGF_MCComplRead(string qName)
{
	LAi_SetStayType(pchar);
	ChangeCharacterAddressGroup(pchar, "PortoBello_PortOffice", "goto", "goto2");
	DoQuestFunctionDelay("SGF_PMreturn", 2.0);
}
void SGF_PMreturn(string qName)
{
	sld = characterFromId("PortoBello_Portman");
	ChangeCharacterAddressGroup(sld, "PortoBello_PortOffice", "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "goto", "goto3","SGF_UsurertoLoc3", -1);
}

void SharkGoldFleetToCPO10(string qName) 
{
	RemoveItems(PChar, "letter_2", 1);
	ChangeItemDescribe("letter_2", "itmdescr_letter_2");
	sld = characterFromId("Dodson");
	sld.dialog.currentnode = "SharkGoldFleet_23";
	LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
	pchar.questTemp.SharkGoldFleet = "fail";
	AddQuestRecord("SharkGoldFleet", "19");
	CloseQuestHeader("SharkGoldFleet");
}

void SharkGoldFleet1269fail(string qName) 
{
	sld = characterFromId("Dodson");
	sld.dialog.currentnode = "SharkGoldFleet_23";
	LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
	pchar.questTemp.SharkGoldFleet = "fail";
	if(!CheckAttribute(pchar, "questTemp.SharkGoldFleet.talk")) AddQuestRecord("SharkGoldFleet", "21");
	else AddQuestRecord("SharkGoldFleet", "23");
	CloseQuestHeader("SharkGoldFleet");
	pchar.quest.SharkGoldFleetToShark.over = "yes";
	pchar.quest.SGF_FleetTime.over = "yes";
	if(CheckAttribute(pchar, "GenQuest.SeaHunter2Pause"))
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause");
	if(CheckAttribute(pchar, "questTemp.SharkGoldFleet.talk")) DeleteAttribute(pchar, "questTemp.SharkGoldFleet.talk");
	if (GetCharacterIndex("Dodson_GF") != -1)
	{
		sld = characterFromId("Dodson_GF");
		sld.lifeDay = 0;
		Group_DeleteGroup("DodsonFrigate");
	}
}

void SharkGoldFleetToShark(string qName) 
{
	Group_FindOrCreateGroup("DodsonFrigate");
	sld = GetCharacter(NPC_GenerateCharacter("Dodson_GF", "Shark", "man", "man", 45, PIRATE, -1, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_FRIGATE_H, pchar.questTemp.SharkGoldFleet.KGBB, CANNON_TYPE_CANNON_LBS36, 105, 105, 105);
	FantomMakeCoolFighter(sld, 45, 100, 100, "blade_21", "pistol5", "bullet", 100);
	sld.name = StringFromKey("Saga_85");
	sld.lastname = StringFromKey("Saga_86"); 
	sld.Abordage.Enable = false;
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable = true; 
	LAi_SetImmortal(sld, true); 
	sld.Dialog.Filename = "Quest\LSC\Dodson.c";
	sld.DeckDialogNode = "SharkGoldFleet_25";
	sld.nation = PIRATE;
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	Group_AddCharacter("DodsonFrigate", "Dodson_GF");
	Group_SetGroupCommander("DodsonFrigate", "Dodson_GF");
	Group_SetTaskNone("DodsonFrigate");
	Group_SetAddress("DodsonFrigate", "Curacao", "quest_ships", "quest_ship_4");
	Group_LockTask("DodsonFrigate");
	if(CheckAttribute(&RealShips[sti(sld.Ship.Type)], "Tuning.Capacity"))
	DeleteAttribute(&RealShips[sti(sld.Ship.Type)], "Tuning.Capacity")); 
	RealShips[sti(sld.Ship.Type)].MaxCaliber = 36;
	RealShips[sti(sld.Ship.Type)].CannonsQuantity = 50;
	RealShips[sti(sld.Ship.Type)].CannonsQuantityMin = 50;
	RealShips[sti(sld.Ship.Type)].CannonsQuantityMax = 50;
	RealShips[sti(sld.Ship.Type)].CannonDiff = 0;
	SetShipCannonsDamagesNull(sld);
	RealShips[sti(sld.Ship.Type)].SpeedRate = 16.0;
	RealShips[sti(sld.Ship.Type)].TurnRate = 35.0;
	RealShips[sti(sld.Ship.Type)].MinCrew = 50; 
	RealShips[sti(sld.Ship.Type)].OptCrew = 408; 
	RealShips[sti(sld.Ship.Type)].MaxCrew = 510; 
	RealShips[sti(sld.Ship.Type)].HP = 6000;
	RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;
    sld.ship.HP = 6000;
	SetSailsColor(sld, 8);//черный парус
	UpgradeShipParameter(sld, "SpeedRate");//апгрейдить скорость
	UpgradeShipParameter(sld, "Capacity");//апгрейдить трюм
	RealShips[sti(sld.Ship.Type)].Capacity = 6000;
	DeleteAttribute(sld, "ship.hulls");
	i = GetMaxCrewQuantity(sld);
	SetCrewQuantity(sld, i);
	sld.Ship.Crew.Morale = 100;
	sld.Ship.Crew.Exp.Sailors = 100;
	sld.Ship.Crew.Exp.Cannoners = 100;
	sld.Ship.Crew.Exp.Soldiers = 100;
	SetCharacterGoods(sld, GOOD_BALLS, 3500);
	SetCharacterGoods(sld, GOOD_GRAPES, 2000);
	SetCharacterGoods(sld, GOOD_KNIPPELS, 1500);
	SetCharacterGoods(sld, GOOD_BOMBS, 3500);
	SetCharacterGoods(sld, GOOD_POWDER, 10500);
	SetCharacterGoods(sld, GOOD_WEAPON, 1000);
	SetCharacterGoods(sld, GOOD_FOOD, 2000);
	SetCharacterGoods(sld, GOOD_MEDICAMENT, 700);
	SetCharacterGoods(sld, GOOD_RUM, 200);
	SetCharacterGoods(sld, GOOD_PLANKS, 100);
	SetCharacterGoods(sld, GOOD_SAILCLOTH, 50);
}
void SGF_SharkDelGroup(string qName) 
{
	Group_DeleteGroup("DodsonFrigate");
}

void SGF_SharkCompanion()
{
	sld = characterFromId("Dodson_GF");
	SetCharacterRemovable(sld, false);
	sld.CompanionEnemyEnable = false; //всегда друзья
	SetCompanionIndex(pchar, -1, sti(sld.index));
	sld.loyality = MAX_LOYALITY;
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.AlwaysSandbankManeuver = true;
	Character_SetAbordageEnable(sld, false); // нельзя абордировать
	sld.Tasks.CanBoarding = false; // запрет идти на абордаж - дубль
	sld.Tasks.CanChangeShipAfterBoarding = false; // запрет меняться кораблями - дубль
	sld.Abordage.Enable = false;
	sld.DontDeskTalk = true;
	LAi_SetImmortal(sld, false);
	sld.ShipHideImmortal = 1000; // непотопляемый корабль
	sld.SeaBoss = 0.8; // получает на 80% меньше урона корпусу, 10% урона парусам
}
void SGF_FleetTime(string qName) // срок генерации конвоя
{
	log_Testinfo("Время генерации конвоя!");
	if(!CheckAttribute(pchar, "questTemp.SharkGoldFleet.talk")) return; // не гворили со Стивеном
	if (bSeaActive) DoQuestFunctionDelay("SGF_CheckCoordinates", 0.5);
	else
	{
		pchar.quest.SGF_CheckCoord.win_condition.l1 = "EnterToSea";
		pchar.quest.SGF_CheckCoord.function = "SGF_CheckCoordinates";
	}
}

void SGF_CheckCoordinates(string qName) // проверяем координаты
{
	log_Testinfo("Проверяю координаты...");
	if(!CheckAttribute(pchar, "questTemp.SharkGoldFleet.talk")) return; // не гворили со Стивеном
	int degN, degW, minN1, minN2, minW1, minW2;
	degN = 12; // минута широты
	degW = 69; // минута долготы
	if(MOD_SKILL_ENEMY_RATE < 9)
	{
		minN1 = 40; // нижний предел интервала широты
		minN2 = 60; // верхний предел интервала широты
		minW1 = 40; // нижний предел интервала долготы
		minW2 = 60; // верхний предел интервала долготы
	}
	else  // казуалам достаточно попасть в минуту
	{
		minN1 = 0; // нижний предел интервала широты
		minN2 = 60; // верхний предел интервала широты
		minW1 = 0; // нижний предел интервала долготы
		minW2 = 60; // верхний предел интервала долготы
	}
	if (CheckAttribute(pchar, "Ship.pos.x") && !bDisableMapEnter)
	{
		if(GetSeaCoordDegreeZ(makefloat(pchar.Ship.pos.z)) == degN && GetMapCoordMinutesZ(makefloat(worldMap.playerShipZ)) >= minN1 && GetMapCoordMinutesZ(makefloat(worldMap.playerShipZ)) < minN2 && GetSeaCoordDegreeX(makefloat(pchar.Ship.pos.x)) == degW && GetMapCoordMinutesX(makefloat(worldMap.playerShipX)) >= minW1 && GetMapCoordMinutesX(makefloat(worldMap.playerShipX)) < minW2) 
		{	
			
			log_Testinfo("Координаты соответствуют!");
			bQuestDisableMapEnter = true;
			Island_SetReloadEnableGlobal("Curacao", false);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.SharkGoldFleet1269fail.over = "yes";
			DoQuestFunctionDelay("SGF_CreatGoldFleet", 3.0);
		}
		else 
		{
			log_Testinfo("Координаты не соответствуют!");
			pchar.quest.SGF_CheckCoordRestart.win_condition.l1 = "MapEnter";
			pchar.quest.SGF_CheckCoordRestart.function = "SGF_CheckCoordinatesRestart";
		}
	}
	else log_Testinfo("Координаты не проверяются");
}

void SGF_CheckCoordinatesRestart(string qName) // запуск новой проверки координат
{
	log_Testinfo("Доступна проверка координат!");
	pchar.quest.SGF_CheckCoord.win_condition.l1 = "EnterToSea";
	pchar.quest.SGF_CheckCoord.function = "SGF_CheckCoordinates";
}
void SGF_CreatGoldFleet(string qName)
{
	int i;
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+7;
	if (iRank > 45) iRank = 45;
	log_info(StringFromKey("Saga_87"));
	PlaySound("interface\" + LanguageGetLanguage() + "\_EvEnemy0.wav");;
	DeleteAttribute(pchar,"GenQuest.CannotWait");
	Group_FindOrCreateGroup("SGF_GoldSeaGroup");
	// тяжёлый галеон
	sld = GetCharacter(NPC_GenerateCharacter("SGF_GoldCap_1", "off_spa_2", "man", "man", iRank, SPAIN, -1, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_GALEON_H, StringFromKey("Saga_88"), CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
	FantomMakeCoolFighter(sld, iRank, 100, 100, LinkRandPhrase("blade_17","blade_20","blade_21"), "pistol5", "bullet", 250);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.AlwaysEnemy = true;
	sld.Ship.Mode = "war";
	sld.ship.Crew.Morale = 60+MOD_SKILL_ENEMY_RATE*4;
	sld.Ship.Crew.Exp.Sailors = 60+MOD_SKILL_ENEMY_RATE*4;
	sld.Ship.Crew.Exp.Cannoners = 60+MOD_SKILL_ENEMY_RATE*4;
	sld.Ship.Crew.Exp.Soldiers = 60+MOD_SKILL_ENEMY_RATE*4;
	if(MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
	RealShips[sti(sld.Ship.Type)].Capacity = 5900;
	UpgradeShipParameter(sld, "Capacity");
	SetRandGeraldSail(sld, SPAIN);
	NullCharacterGoods(sld);
	AddCharacterGoods(sld, GOOD_BALLS, 1500);
	AddCharacterGoods(sld, GOOD_GRAPES, 1000);
	AddCharacterGoods(sld, GOOD_KNIPPELS, 800);
	AddCharacterGoods(sld, GOOD_BOMBS, 1700);
	AddCharacterGoods(sld, GOOD_POWDER, 5000);
	AddCharacterGoods(sld, GOOD_WEAPON, 700);
	AddCharacterGoods(sld, GOOD_FOOD, 1000);
	AddCharacterGoods(sld, GOOD_MEDICAMENT, 250);
	AddCharacterGoods(sld, GOOD_RUM, 100);
	pchar.questTemp.SharkGoldFleet.Gold = GetGoodQuantityByWeight(GOOD_GOLD, sti(GetCargoFreeSpace(sld)/2));
	AddCharacterGoods(sld, GOOD_GOLD, makeint(pchar.questTemp.SharkGoldFleet.Gold));
	pchar.questTemp.SharkGoldFleet.Silk = GetGoodQuantityByWeight(GOOD_SHIPSILK, sti(GetCargoFreeSpace(sld)/2));
	AddCharacterGoods(sld, GOOD_SHIPSILK, makeint(pchar.questTemp.SharkGoldFleet.Silk));
	pchar.questTemp.SharkGoldFleet.Ropes = GetGoodQuantityByWeight(GOOD_ROPES, GetCargoFreeSpace(sld));
	AddCharacterGoods(sld, GOOD_ROPES, makeint(pchar.questTemp.SharkGoldFleet.Ropes));
	// навио
	sld = GetCharacter(NPC_GenerateCharacter("SGF_GoldCap_2", "off_spa_3", "man", "man", iRank, SPAIN, -1, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_NAVIO, StringFromKey("Saga_89"), CANNON_TYPE_CANNON_LBS24, 100, 100, 100);
	FantomMakeCoolFighter(sld, iRank, 100, 100, LinkRandPhrase("blade_17","blade_20","blade_21"), "pistol5", "bullet", 250);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.AlwaysEnemy = true;
	sld.Ship.Mode = "war";
	sld.ship.Crew.Morale = 60+MOD_SKILL_ENEMY_RATE*4;
	sld.Ship.Crew.Exp.Sailors = 60+MOD_SKILL_ENEMY_RATE*4;
	sld.Ship.Crew.Exp.Cannoners = 60+MOD_SKILL_ENEMY_RATE*4;
	sld.Ship.Crew.Exp.Soldiers = 60+MOD_SKILL_ENEMY_RATE*4;
	if(MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
	RealShips[sti(sld.Ship.Type)].Capacity = 5800;
	UpgradeShipParameter(sld, "Capacity");
	SetRandGeraldSail(sld, SPAIN);
	NullCharacterGoods(sld);
	AddCharacterGoods(sld, GOOD_BALLS, 1500);
	AddCharacterGoods(sld, GOOD_GRAPES, 1000);
	AddCharacterGoods(sld, GOOD_KNIPPELS, 800);
	AddCharacterGoods(sld, GOOD_BOMBS, 1700);
	AddCharacterGoods(sld, GOOD_POWDER, 5000);
	AddCharacterGoods(sld, GOOD_WEAPON, 700);
	AddCharacterGoods(sld, GOOD_FOOD, 1000);
	AddCharacterGoods(sld, GOOD_MEDICAMENT, 250);
	AddCharacterGoods(sld, GOOD_RUM, 100);
	pchar.questTemp.SharkGoldFleet.Silver = GetGoodQuantityByWeight(GOOD_SILVER, sti(GetCargoFreeSpace(sld)/2));
	AddCharacterGoods(sld, GOOD_SILVER, makeint(pchar.questTemp.SharkGoldFleet.Silver));
	pchar.questTemp.SharkGoldFleet.Sandal = GetGoodQuantityByWeight(GOOD_SANDAL, sti(GetCargoFreeSpace(sld)/2));
	AddCharacterGoods(sld, GOOD_SANDAL, makeint(pchar.questTemp.SharkGoldFleet.Sandal));
	pchar.questTemp.SharkGoldFleet.Oil = GetGoodQuantityByWeight(GOOD_OIL, GetCargoFreeSpace(sld));
	AddCharacterGoods(sld, GOOD_OIL, makeint(pchar.questTemp.SharkGoldFleet.Oil));
	
	// не высплывать товарам после потопления орудиями
	DeleteAttribute(&Goods[GOOD_SHIPSILK],"Swim");
	DeleteAttribute(&Goods[GOOD_ROPES],"Swim");
	DeleteAttribute(&Goods[GOOD_SANDAL],"Swim");
	DeleteAttribute(&Goods[GOOD_OIL],"Swim");
	
	Group_AddCharacter("SGF_GoldSeaGroup", "SGF_GoldCap_1");
	Group_AddCharacter("SGF_GoldSeaGroup", "SGF_GoldCap_2");
	if(pchar.questTemp.SharkGoldFleet == "LightVarToShark")
	{
		AddQuestRecord("SharkGoldFleet", "24");
		pchar.quest.SGF_CreatBattleShips.win_condition.l1 = "Group_Death";
		pchar.quest.SGF_CreatBattleShips.win_condition.l1.group = "SGF_GoldSeaGroup";
		pchar.quest.SGF_CreatBattleShips.function = "SGF_CreatBattleShips";
	}
	else // по плохому варианту сопровождение сразу
	{
		SGF_CreatBattleShips("");
		AddQuestRecord("SharkGoldFleet", "32");
		bQuestDisableMapEnter = false;
	}
	
	Group_SetGroupCommander("SGF_GoldSeaGroup", "SGF_GoldCap_1");
	Group_SetTaskAttack("SGF_GoldSeaGroup", PLAYER_GROUP);
	Group_LockTask("SGF_GoldSeaGroup");
	Sea_LoginGroupCurrentSea("SGF_GoldSeaGroup");
}

void SGF_CreatBattleShips(string qName)
{
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+7;
	if (iRank > 45) iRank = 45;
	int iShip, Ship3, Ship4, Ship5, Ship6, iCannon, Cannon3, Cannon4, Cannon5, Cannon6, n, i;
	if(MOD_SKILL_ENEMY_RATE < 5) n = 5;
	else n = 6;
	Group_FindOrCreateGroup("SGF_GoldSeaGroup");
	if(MOD_SKILL_ENEMY_RATE < 5)
	{
		Ship3 = SHIP_FRIGATE;
		Ship4 = SHIP_CORVETTE;
		Ship5 = SHIP_CORVETTE;
		Cannon3 = CANNON_TYPE_CANNON_LBS24;
		Cannon4 = CANNON_TYPE_CULVERINE_LBS18;
		Cannon5 = CANNON_TYPE_CANNON_LBS20;
	}
	if(MOD_SKILL_ENEMY_RATE == 6)
	{
		Ship3 = SHIP_FRIGATE_H;
		Ship4 = SHIP_FRIGATE;
		Ship5 = SHIP_CORVETTE;
		Ship6 = SHIP_CORVETTE;
		Cannon3 = CANNON_TYPE_CANNON_LBS32;
		Cannon4 = CANNON_TYPE_CANNON_LBS24;
		Cannon5 = CANNON_TYPE_CANNON_LBS20;
		Cannon6 = CANNON_TYPE_CULVERINE_LBS18;
	}
	if(MOD_SKILL_ENEMY_RATE > 7)
	{
		Ship3 = SHIP_LINESHIP;
		Ship4 = SHIP_FRIGATE_H;
		Ship5 = SHIP_FRIGATE_H;
		Ship6 = SHIP_CORVETTE;
		Cannon3 = CANNON_TYPE_CANNON_LBS32;
		Cannon4 = CANNON_TYPE_CANNON_LBS32;
		Cannon5 = CANNON_TYPE_CANNON_LBS24;
		Cannon6 = CANNON_TYPE_CULVERINE_LBS18;
	}
	for(i=3; i<=n; i++)
	{
		switch (i)
		{
			case 3: iShip = Ship3; iCannon = Cannon3; break;
			case 4: iShip = Ship4; iCannon = Cannon4; break;
			case 5: iShip = Ship5; iCannon = Cannon5; break;
			case 6: iShip = Ship6; iCannon = Cannon6; break;
		}
		sld = GetCharacter(NPC_GenerateCharacter("SGF_GoldCap_"+i, "off_spa_"+sti(1+rand(2)), "man", "man", iRank, SPAIN, -1, true, "quest"));
		FantomMakeCoolSailor(sld, iShip, "", iCannon, 100, 100, 100);
		FantomMakeCoolFighter(sld, iRank, 100, 100, LinkRandPhrase("blade_17","blade_20","blade_21"), "pistol5", "bullet", 250);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.AlwaysEnemy = true;
		sld.Ship.Mode = "war";
		sld.ship.Crew.Morale = 60+MOD_SKILL_ENEMY_RATE*4;
		sld.Ship.Crew.Exp.Sailors = 60+MOD_SKILL_ENEMY_RATE*4;
		sld.Ship.Crew.Exp.Cannoners = 60+MOD_SKILL_ENEMY_RATE*4;
		sld.Ship.Crew.Exp.Soldiers = 60+MOD_SKILL_ENEMY_RATE*4;
		if(MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
		if(pchar.questTemp.SharkGoldFleet != "DifficultVarToShark") 
		{
			if(i == 3) Group_FindOrCreateGroup("SGF_GoldSeaGroup1");
			Group_AddCharacter("SGF_GoldSeaGroup1", "SGF_GoldCap_"+i);
		}
		else
		{
			Group_AddCharacter("SGF_GoldSeaGroup", "SGF_GoldCap_"+i);
		}
	}
	if(pchar.questTemp.SharkGoldFleet != "DifficultVarToShark") 
	{
		bQuestDisableMapEnter = false;
		AddQuestRecord("SharkGoldFleet", "31");
		Group_SetGroupCommander("SGF_GoldSeaGroup1", "SGF_GoldCap_3");
		Group_SetTaskAttack("SGF_GoldSeaGroup1", PLAYER_GROUP);
		Group_LockTask("SGF_GoldSeaGroup1");
		Sea_LoginGroupCurrentSea("SGF_GoldSeaGroup1");
	}
	pchar.quest.SGF_CheckWin.win_condition.l1 = "MapEnter";
	pchar.quest.SGF_CheckWin.function = "SGF_CheckWin";
}

void SGF_CheckWin(string qName)
{
	bool bOk = true;
	int num, sum;
	
	if(pchar.questTemp.SharkGoldFleet == "DifficultVarToShark" &&
		GetCharacterIndex("SGF_GoldCap_1") != -1 && 
		GetCharacterIndex("SGF_GoldCap_2") != -1) bOk = false;
		
	int percent;
	int TotalGoods = 0;
	TotalGoods += makeint(pchar.questTemp.SharkGoldFleet.Gold);
	TotalGoods += makeint(pchar.questTemp.SharkGoldFleet.Silk);
	TotalGoods += makeint(pchar.questTemp.SharkGoldFleet.Ropes);
	TotalGoods += makeint(pchar.questTemp.SharkGoldFleet.Silver);
	TotalGoods += makeint(pchar.questTemp.SharkGoldFleet.Sandal);
	TotalGoods += makeint(pchar.questTemp.SharkGoldFleet.Oil);
	int PcharGoods = 0;
	PcharGoods += GetSquadronGoods(pchar, GOOD_GOLD);
	PcharGoods += GetSquadronGoods(pchar, GOOD_SILVER);
	PcharGoods += GetSquadronGoods(pchar, GOOD_SANDAL);
	PcharGoods += GetSquadronGoods(pchar, GOOD_SHIPSILK);
	PcharGoods += GetSquadronGoods(pchar, GOOD_ROPES);
	PcharGoods += GetSquadronGoods(pchar, GOOD_OIL);

	percent = 100*PcharGoods/TotalGoods;
	if(!bOk)
	{
		Island_SetReloadEnableGlobal("Curacao", true);
		AddQuestRecord("SharkGoldFleet", "33");
		SGF_ClearFantoms();
		SGF_ClearDodson();
		SGF_GoodSwimReturn();
		return;
	}
	else
	{
		if(percent>98){ AddQuestRecord("SharkGoldFleet", "25");}
		else{ if(percent>74){ AddQuestRecord("SharkGoldFleet", "26");}
			else{ if(percent>49){ AddQuestRecord("SharkGoldFleet", "27");}
				else{ if(percent>24){ AddQuestRecord("SharkGoldFleet", "28");}
					else{ if(percent>0){ AddQuestRecord("SharkGoldFleet", "29");}
						else{ AddQuestRecord("SharkGoldFleet", "30");
						}
					}
				}
			}
		}
	}
	if(pchar.questTemp.SharkGoldFleet == "LightVarToShark")
	{
		num = Group_GetLiveCharactersNum("SGF_GoldSeaGroup1");
		if(MOD_SKILL_ENEMY_RATE < 5) sum = 3;
		else sum = 4;
		if(sum == num)  AddQuestUserData("SharkGoldFleet", "addText", StringFromKey("Saga_90"));
		if(sum > num && num != 0) AddQuestUserData("SharkGoldFleet", "addText", StringFromKey("Saga_91"));
		if(num == 0) AddQuestUserData("SharkGoldFleet", "addText", StringFromKey("Saga_92"));
	}
	else 
	{
		AddQuestUserData("SharkGoldFleet", "addText", "");
	} 
	pchar.questTemp.SharkGoldFleet = percent;
	DoQuestFunctionDelay("SGF_ToSharkTalk", 1.0);
}

void SGF_ToSharkTalk(string qName)
{ 
	ChangeCharacterNationReputation(pchar, SPAIN, -10);
	if(CheckAttribute(pchar, "GenQuest.SeaHunter2Pause"))
	DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause");
	SGF_ClearFantoms();
	Island_SetReloadEnableGlobal("Curacao", true);
	setCharacterShipLocation(pchar, "Shore22");
	setWDMPointXZ("Shore22");
	DoQuestReloadToLocation("Shore22", "goto", "goto3", "SGF_atVanHatoTalk");
	LAi_LocationFightDisable(&Locations[FindLocation("Shore22")], true);
	locations[FindLocation("Shore22")].DisableEncounters = true;
}

void SGF_ClearFantoms()
{
	for(int i=1; i<7; i++)
	{
		if (GetCharacterIndex("SGF_GoldCap_"+i) != -1)
		{
			sld = characterFromId("SGF_GoldCap_"+i);
			sld.lifeDay = 0;
		}
		Group_DeleteGroup("SGF_GoldSeaGroup");
		Group_DeleteGroup("SGF_GoldSeaGroup1");
	}
}
void SGF_ClearDodson()
{
	SGF_GoodSwimReturn();
	sld = characterFromId("Dodson_GF");
	RemoveCharacterCompanion(pchar, sld);
	sld.lifeDay = 0;
	// откроем доступ к нормальному
	sld = characterFromId("Dodson");
	sld.dialog.currentnode = "SharkGoldFleet_23";
	LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
	pchar.questTemp.SharkGoldFleet = "fail";
	SGF_DelAllSubAttributes(); // удалить все лишнее, чтобы не болталось
}

void SGF_GoodSwimReturn()
{
	Goods[GOOD_SHIPSILK].Swim.Model			= "roll_of_rolls";
	Goods[GOOD_SHIPSILK].Swim.Time			= 20;
	Goods[GOOD_ROPES].Swim.Model	    	= "sack";
	Goods[GOOD_ROPES].Swim.Time	    		= 20;
	Goods[GOOD_SANDAL].Swim.Model			= "box";
	Goods[GOOD_SANDAL].Swim.Time			= 45;
	Goods[GOOD_OIL].Swim.Model	    		= "barrel";
	Goods[GOOD_OIL].Swim.Time	    		= 20;
}

void SGF_DelAllSubAttributes()
{
	aref arAttr, arSubAttr;
	int SubAttrQty, i;
	
	makearef(arAttr, pchar.questTemp.SharkGoldFleet);
	SubAttrQty = GetAttributesNum(arAttr);
	for( i=0; i<SubAttrQty; i++ ) 
	{
		arSubAttr = GetAttributeN(arAttr,i);
		string SubAttrName = GetAttributeName(arSubAttr);
		if(SubAttrName == "KGBB") continue;
		if(CheckAttribute(arAttr,SubAttrName))
		{
			DeleteAttribute(arAttr,SubAttrName);
			SubAttrQty--;
			i--;
		}
	}
}
// belamour копии отличных карт Диаса
void Amapcopy_comlete(string qName)
{
	Log_info(StringFromKey("Saga_93"));
	pchar.questTemp.AdmiralMapCopy = "complete";
}

void AdmAtlas_comlete(string qName)
{
	Log_info(StringFromKey("Saga_94"));
	pchar.questTemp.AdmiralAtlas = "complete";
}

// --------------------------------- отношения с девушками - героинями Саги ---------------------------------
void Helena_SexReady(string qName) // Элен снова готова к сексу
{
	sld = characterFromId("Helena");	
	DeleteAttribute(sld, "quest.daily_sex");
}

// --> Красная Мэри вне LSC - пипец Карибам :) Тут отрабатываем её поведение
void Mary_SexReady(string qName) // Мэри снова готова к сексу
{
	sld = characterFromId("Mary");	
	DeleteAttribute(sld, "quest.daily_sex");
	pchar.quest.Mary_giveme_sex.win_condition.l1 = "Timer";
	pchar.quest.Mary_giveme_sex.win_condition.l1.date.hour  = sti(GetTime());
	pchar.quest.Mary_giveme_sex.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
	pchar.quest.Mary_giveme_sex.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
	pchar.quest.Mary_giveme_sex.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
	pchar.quest.Mary_giveme_sex.function = "Mary_GiveMeSex";
}

// требует секса, если давно не давал. Пока только в таверне
void Mary_GiveMeSex(string qName)
{
	if (CheckAttribute(pchar, "questTemp.GoldenGirl.MaryBlock")) return; // fix 22-03-20
	if (CheckAttribute(pchar, "questTemp.MarySexBlock")) return;
	pchar.quest.Mary_giveme_sex1.win_condition.l1 = "Location_Type";
	pchar.quest.Mary_giveme_sex1.win_condition.l1.location_type = "tavern";
	pchar.quest.Mary_giveme_sex1.function = "Mary_GetTalk";
	sld = characterFromId("Mary");
	sld.quest.iwantsex = true;
	sld.greeting = "mary_love";
}

void Mary_GetTalk(string qName) // говорилка Мэри
{
	if(chrDisableReloadToLocation) // belamour уже идёт другой квест
	{
		SetTimerFunction("Mary_GiveMeSex", 0, 0, 1);
		return;
	}
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = characterFromId("Mary");
	if (CheckAttribute(sld, "quest.iwantsex")) sld.dialog.currentnode = "givemesex";
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Mary_DeleteSexBlock(string qName)
{
	DeleteAttribute(pchar, "questTemp.MarySexBlock");
}

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool Saga_QuestComplete(string sQuestName, string qname)
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////	
///Jason---------------------------------------Пиратская Сага--------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ref sld, chr;
	int iTemp, i, n, iRank, iScl;
    float locx, locy, locz;
	string sTemp;

//-------------------------------------общие функции-----------------------------------------------
	bool condition = true;
	// ---------------------------------поведение бандитов у рудника-----------------------------------------
	if (sQuestName == "Saga_MineBanditsTalk") // инициализация разговора
	{
		DoQuestCheckDelay("hide_weapon", 0.5);
		if (pchar.location == "mine_exit") sld = characterFromId("Mine_bandit_3");
		else sld = characterFromId("Mine_banditx_1");
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}
	else if (sQuestName == "Saga_MineBanditsFire") // стреляют из пушки
	{
		CreateLocationParticles("blast_inv", "quest", "gun1", 1.15, 0, 0, "cannon_fire_1");
		CreateLocationParticles("blast_inv", "quest", "gun2", 1.15, 0, 0, "cannon_fire_1");
		LAi_KillCharacter(pchar);
		LAi_KillCharacter(pchar);
		ClearAllLogStrings();
	}
	else if (sQuestName == "Saga_MineBanditsxFire") // стреляют из мушкетов // 250812
	{
		for (i = 1; i <= 2; i++)
		{
			sld = characterFromId("Mine_banditx_" + i);
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "shot", "Saga_MineBanditsxFire_1", 1.0);
		}
	}
	else if (sQuestName == "Saga_MineBanditsxFire_1")
	{
		LAi_KillCharacter(pchar);
	}
	// -------------------------------------штурм рудника----------------------------------------------------
	else if (sQuestName == "Saga_MineBanditxDie")
	{
		n = Findlocation("mine_01");
		DeleteAttribute(&locations[n], "mine_bandits");
		sld = characterFromId("Mine_banditx_1");
		LAi_KillCharacter(sld);
		sld = characterFromId("Svensons_sold_12");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		sld = characterFromId("Svensons_off_2");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		for (i = 2; i <= 4; i++)
		{
			sld = characterFromId("Mine_banditx_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Saga_BanditsxDestroyed");
		LAi_SetFightMode(pchar, true);
	}
	else if (sQuestName == "Saga_BanditsxDestroyed")
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false; // открыть локацию
		sld = characterFromId("Svensons_sold_12");
		if (LAi_GetCharacterHP(sld) > 0)
		{
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_SetCurHPMax(sld);
		}
		sld = characterFromId("Svensons_off_2");
		if (LAi_GetCharacterHP(sld) > 0)
		{
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_SetCurHPMax(sld);
		}
		pchar.quest.Saga_MineAttack_04.win_condition.l1 = "location";
		pchar.quest.Saga_MineAttack_04.win_condition.l1.location = "Mine_04";
		pchar.quest.Saga_MineAttack_04.function = "Saga_PrepareMineAttackTail";
		AddComplexSelfExpToScill(150, 150, 150, 150);
	}
	else if (sQuestName == "Saga_MineBanditDie")
	{
		sld = characterFromId("Mine_bandit_1");
		LAi_KillCharacter(sld);
		sld = characterFromId("Svensons_sold_12");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		sld = characterFromId("Svensons_off_2");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		for (i = 2; i <= 6; i++)
		{
			sld = characterFromId("Mine_bandit_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Saga_BanditsDestroyed");
		LAi_SetFightMode(pchar, true);
	}
	else if (sQuestName == "Saga_BanditsDestroyed")
	{
		LAi_group_Delete("EnemyFight");
		sld = characterFromId("Svenson");
		sld.dialog.currentnode = "mine_attack_20";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		AddComplexSelfExpToScill(50, 50, 50, 50);
	}
	// канонада
	else if (sQuestName == "Saga_MineSetMusic")
	{
		SetMusic("music_military");
	}
	else if (sQuestName == "Saga_Gunfire") // выстрел
	{
		float ftime = 1.5;
		CreateLocationParticles("Ship_cannon_fire", "goto", "fire", 1.0, 40, 40, "cannon_fire_1");
		sld = characterFromId("Svensons_off_1");
		if (sld.quest.canonada == "1" || sld.quest.canonada == "2") ftime = 2.5;
		DoQuestCheckDelay("Saga_Gunexplode_0" + sld.quest.canonada, ftime);
	}
	else if (sQuestName == "Saga_GunTalk") // базар
	{
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Svensons_off_1");
		sld.dialog.currentnode = "gunner_" + sld.quest.canonada;
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}
	else if (sQuestName == "Saga_Gunexplode_01") // взрыв первый
	{
		CreateLocationParticles("ShipExplode", "goto", "burn11", 1.0, 0, 0, "boom");
		CreateLocationParticles("blast_dirt", "goto", "burn11", 1.0, 0, 0, "");
		CreateLocationParticles("blast_inv", "goto", "burn11", 1.0, 0, 0, "");
		DoQuestCheckDelay("Saga_GunTalk", 3.0);
	}
	else if (sQuestName == "Saga_Gunexplode_02") // взрыв второй
	{
		CreateLocationParticles("ShipExplode", "goto", "burn12", 1.0, 0, 0, "boom");
		CreateLocationParticles("blast_dirt", "goto", "burn12", 1.0, 0, 0, "");
		CreateLocationParticles("shipfire", "goto", "burn12", 0, 0, 0, "");
		CreateLocationParticles("large_smoke", "goto", "burn12", 1.0, 0, 0, "");
		CreateLocationParticles("shipfire", "goto", "burn12", 1.0, 0, 0, "");
		DoQuestCheckDelay("Saga_GunTalk", 6.0);
	}
	else if (sQuestName == "Saga_LoginBandos_01") // бандюки-1
	{
		for (i = 1; i <= 3; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Mine_Bandos_01_" + i, "citiz_" + (rand(9) + 51), "man", "man", 30, PIRATE, 0, true, "soldier"));
			FantomMakeCoolFighter(sld, 30, 60, 60, "blade_10", "", "bullet", 100);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "mine", "rld", "warrior");
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", "TMP_FRIEND", LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", "TMP_FRIEND", true);
		DoQuestCheckDelay("Saga_Gunfire", 5.5);
	}
	else if (sQuestName == "Saga_Gunexplode_03") // взрыв третий
	{
		CreateLocationParticles("ShipExplode", "goto", "boom2", 1.0, 0, 0, "boom");
		CreateLocationParticles("blast_dirt", "goto", "boom2", 1.0, 0, 0, "");
		CreateLocationParticles("blast_inv", "goto", "boom2", 1.0, 0, 0, "");
		for (i = 1; i <= 3; i++)
		{
			sld = characterFromId("Mine_Bandos_01_" + i);
			LAi_KillCharacter(sld);
		}
		DoQuestCheckDelay("Saga_GunTalk", 2.5);
	}
	else if (sQuestName == "Saga_LoginBandos_02") // бандюки-2
	{
		for (i = 1; i <= 3; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Mine_Bandos_02_" + i, "mush_ctz_" + (rand(2) + 10), "man", "mushketer", 35, PIRATE, 0, true, "soldier"));
			FantomMakeCoolFighter(sld, 35, 70, 70, "", "mushket1", "cartridge", 100);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "mine", "rld", "warrior");
			LAi_ActorRunToLocator(sld, "rld", "detector1", "", -1);
		}
		DoQuestCheckDelay("Saga_Gunfire", 3.0);
	}
	else if (sQuestName == "Saga_Gunexplode_04") // взрыв четвертый
	{
		CreateLocationParticles("ShipExplode", "goto", "boom1", 1.0, 0, 0, "boom");
		CreateLocationParticles("blast_dirt", "goto", "boom1", 1.0, 0, 0, "");
		CreateLocationParticles("blast_inv", "goto", "boom1", 1.0, 0, 0, "");
		for (i = 1; i <= 3; i++)
		{
			sld = characterFromId("Mine_Bandos_02_" + i);
			LAi_KillCharacter(sld);
		}
		DoQuestCheckDelay("Saga_LoginBandos_03", 3.0);
		PlaySound("interface\abordage_wining.wav");
		PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
	}
	else if (sQuestName == "Saga_LoginBandos_03") // бандюки-3
	{
		sld = characterFromId("Svensons_off_1");
		sld.quest.canonada = "5";
		for (i=1; i<=2; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Mine_Bandos_03_"+i, "citiz_"+(rand(9)+51), "man", "man", 35, PIRATE, 0, true, "soldier"));
			FantomMakeCoolFighter(sld, 35, 70, 70, "blade_10", "", "bullet", 100);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "mine", "rld", "warrior");
			LAi_ActorRunToLocator(sld, "rld", "detector2", "", -1);
		}
		DoQuestCheckDelay("Saga_Gunfire", 3.5);
	}
	else if (sQuestName == "Saga_Gunexplode_05") // взрыв пятый
	{
		CreateLocationParticles("ShipExplode", "goto", "boom3", 1.0, 0, 0, "boom");
		CreateLocationParticles("blast_dirt", "goto", "boom3", 1.0, 0, 0, "");
		CreateLocationParticles("blast_inv", "goto", "boom3", 1.0, 0, 0, "");
		for (i=1; i<=2; i++)
		{
			sld = characterFromId("Mine_Bandos_03_"+i);
			LAi_KillCharacter(sld);
		}
		DoQuestCheckDelay("Saga_LoginBandos_04", 0.5);
		PlaySound("interface\abordage_wining.wav");
		PlaySound("interface\" + LanguageGetLanguage() + "_grapes_npc.wav");
	}
	else if (sQuestName == "Saga_LoginBandos_04") // бандюки-4
	{
		for (i=1; i<=7; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Mine_Bandos_04_"+i, "citiz_"+(rand(9)+51), "man", "man", 35, PIRATE, 0, true, "soldier"));
			FantomMakeCoolFighter(sld, 35, 70, 70, "blade_10", "", "bullet", 100);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "mine", "rld", "warrior");
			LAi_ActorRunToLocator(sld, "rld", "detector2", "", -1);
		}
		DoQuestCheckDelay("Saga_Bandos_04_Attack", 3.5);
	}
	else if (sQuestName == "Saga_Bandos_04_Attack") // 
	{
		for (i=1; i<=7; i++)
		{
			sld = characterFromId("Mine_Bandos_04_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", "TMP_FRIEND", LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", "TMP_FRIEND", true);
		DoQuestCheckDelay("Saga_GunfireGrape", 6.0);
	}
	else if (sQuestName == "Saga_GunfireGrape") // выстрел
	{
		CreateLocationParticles("Bombard", "goto", "fire", 1.0, 90, 90, "cannon_fire_2");
		CreateLocationParticles("blast_dirt", "goto", "fire", 1.0, 90, 90, "");
		CreateLocationParticles("blast_dirt", "goto", "fire", 1.0, 90, 90, "");
		DoQuestCheckDelay("Saga_Gunexplode_06", 0.5);
	}
	else if (sQuestName == "Saga_Gunexplode_06") // выстрел картечью
	{
		for (i=3; i<=7; i++)
		{
			sld = characterFromId("Mine_Bandos_04_"+i);
			LAi_KillCharacter(sld);
		}
		for (i=1; i<=2; i++)
		{
			sld = characterFromId("Mine_Bandos_04_"+i);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "rld", "warrior", "none", "", "", "", 15.0);
		}
		DoQuestCheckDelay("Saga_GunTalk", 8.0);
		PlaySound("interface\abordage_wining.wav");
	}
	else if (sQuestName == "Saga_GunAutoFire") // выстрел
	{
		if (iTotalTemp <= 10)
		{
			CreateLocationParticles("Ship_cannon_fire", "goto", "fire", 1.0, 90, 90, "cannon_fire_1");
			DoQuestCheckDelay("Saga_GunAutoExplode", 2.5);
			iTotalTemp++;
		}
	}
	else if (sQuestName == "Saga_GunAutoExplode") // взрыв
	{
		CreateLocationParticles("ShipExplode", "goto", "burn"+iTotalTemp, 0, 0, 0, "boom");
		CreateLocationParticles("blast_dirt", "goto", "burn"+iTotalTemp, 0, 0, 0, "");
		CreateLocationParticles("blast_inv", "goto", "burn"+iTotalTemp, 0, 0, 0, "");
		if (iTotalTemp > 2 && iTotalTemp <= 7)
		{
			CreateLocationParticles("large_smoke", "goto", "burn"+iTotalTemp, 0, 0, 0, "");
			CreateLocationParticles("shipfire", "goto", "burn"+iTotalTemp, 0, 0, 0, "");
		}
		if (iTotalTemp > 7) CreateLocationParticles("smoke", "goto", "burn"+iTotalTemp, 0, 0, 0, "");
		if (iTotalTemp == 2)
		{
			for (i=5; i<=6; i++)
			{
				sld = characterFromId("Mine_Bandos_05_"+i);
				LAi_KillCharacter(sld);
			}
		}
		DoQuestCheckDelay("Saga_GunAutoFire", 4.0+iTotalTemp*2);
	}
	else if (sQuestName == "Saga_MineBandos_05Die") // генерим партию бандюков в шесть рыл
	{
		PlaySound("interface\abordage_wining.wav");
		iRank = 20+MOD_SKILL_ENEMY_RATE+5;
		iScl = 65;
		float fMft = MOD_SKILL_ENEMY_RATE/10;
		for (i=1; i<=6; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Mine_Bandos_06_"+i, "citiz_"+(rand(9)+51), "man", "man", iRank, PIRATE, 0, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl);
			ChangeCharacterAddressGroup(sld, "mine", "rld", "attack1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			if (MOD_SKILL_ENEMY_RATE > 4) sld.MultiFighter = 0.5+fMft; // мультифайтер
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Saga_MineBandos_06Die");
		pchar.quest.Saga_MineFightLock1.win_condition.l1 = "locator";
		pchar.quest.Saga_MineFightLock1.win_condition.l1.location = "mine";
		pchar.quest.Saga_MineFightLock1.win_condition.l1.locator_group = "rld";
		pchar.quest.Saga_MineFightLock1.win_condition.l1.locator = "attack1"; // закрываем доступ в лагерь
		pchar.quest.Saga_MineFightLock1.function = "Saga_MineFightLock";
		pchar.quest.Saga_MineFightLock.win_condition.l1 = "locator";
		pchar.quest.Saga_MineFightLock.win_condition.l1.location = "mine";
		pchar.quest.Saga_MineFightLock.win_condition.l1.locator_group = "rld";
		pchar.quest.Saga_MineFightLock.win_condition.l1.locator = "warrior";
		pchar.quest.Saga_MineFightLock.function = "Saga_MineFightLock"; // закрываем доступ назад
	}
	else if (sQuestName == "Saga_MineBandos_06Die") // генерим партию бандюков в восемь рыл
	{
		PlaySound("interface\abordage_wining.wav");
		iRank = 20+MOD_SKILL_ENEMY_RATE+5;
		iScl = 70;
		for (i=1; i<=8; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Mine_Bandos_07_"+i, "citiz_"+(rand(9)+51), "man", "man", iRank, PIRATE, 0, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol5", "bullet", iScl);
			ChangeCharacterAddressGroup(sld, "mine", "rld", "attack2");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Saga_MineBandos_07Die");
		DoQuestCheckDelay("Saga_MineBandos_SvensonHelp", 35.0);
		AddComplexSelfExpToScill(100, 100, 100, 100);
	}
	else if (sQuestName == "Saga_MineBandos_SvensonHelp") // Свенсон идёт на помощь
	{
		PlaySound("interface\abordage_wining.wav");
		pchar.quest.Saga_MineFightLock.over = "yes"; //снять прерывание
		pchar.quest.Saga_MineFightLock1.over = "yes"; //снять прерывание
		sld = characterFromId("Svenson");
		ChangeCharacterAddressGroup(sld, "mine", "reload", "reload6");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		if (GetCharacterIndex("Svensons_off_2") != -1)
		{
			sld = characterFromId("Svensons_off_2");
			ChangeCharacterAddressGroup(sld, "mine", "reload", "reload6");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		for (i=1; i<=11; i++)
		{
			sld = characterFromId("Svensons_sold_"+i);
			ChangeCharacterAddressGroup(sld, "mine", "reload", "reload6");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	else if (sQuestName == "Saga_MineBandos_07Die") // 
	{
		PlaySound("interface\abordage_wining.wav");
		sld = characterFromId("Svenson");
		sld.dialog.currentnode = "mine_attack_27";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		AddComplexSelfExpToScill(150, 150, 150, 150);
	}
	else if (sQuestName == "Saga_MineAttackMinesLock") // 
	{
		chrDisableReloadToLocation = true; //закрыть локацию
		sld = characterFromId("Svenson");
		sld.dialog.currentnode = "mine_attack_32a";
		ChangeCharacterAddressGroup(sld, "mine_mines", "officers", "reload1_3");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_group_SetRelation("Mine_enemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_SetCheck("Mine_enemy", "Saga_MinesBanditsDestroyed");
	}
	else if (sQuestName == "Saga_MinesBanditsDestroyed") // 
	{
		LAi_group_Delete("Mine_enemy");
		LAi_group_SetHearRadius(LAI_GROUP_PLAYER, LAI_GROUP_PLA_HEAR);
		sld = characterFromId("Svenson");
		sld.dialog.currentnode = "mine_attack_32";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		AddComplexSelfExpToScill(50, 50, 50, 50);
	}
	else if (sQuestName == "Saga_MineWaitTime") // 
	{
		//чистим всю солдатню
		for (i=1; i<=8; i++)
		{
			if (GetCharacterIndex("Ourmine_sold_"+i) != -1)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				sld.lifeday = 0;
			}
		}
		for (i=1; i<=12; i++)
		{
			if (GetCharacterIndex("Svensons_sold_"+i) != -1)
			{
				sld = characterFromId("Svensons_sold_"+i);
				sld.lifeday = 0;
			}
		}
		for (i=1; i<=2; i++)
		{
			if (GetCharacterIndex("Svensons_off_"+i) != -1)
			{
				sld = characterFromId("Svensons_off_"+i);
				sld.lifeday = 0;
			}
		}
		GetCharacterPos(pchar, &locx, &locy, &locz);
		pchar.locx = locx;
		pchar.locy = locy;
		pchar.locz = locz;
		SetLaunchFrameFormParam(StringFromKey("Saga_95", NewStr()), "Reload_To_Location", 0.1, 5.0);
		SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
		WaitDate("", 0, 0, 0, iTemp, 0);
		LaunchFrameForm();
		RefreshLandTime();
		RecalculateJumpTable();
		Whr_UpdateWeather();
		SetCharacterGoods(pchar, GOOD_SILVER, GetCargoGoods(pchar, GOOD_SILVER) + 2000 + drand(100)); // кладем серебро
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Svenson");
		sld.dialog.currentnode = "mine_attack_47";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	// -----------------------начальная часть - пропавшая амазонка и наследница------------------------------
	else if (sQuestName == "Saga_KillJimmy")	
	{
		chrDisableReloadToLocation = false; // открыть локацию
		LAi_group_Delete("EnemyFight");
		pchar.questTemp.Saga = "jackman";
		if (CheckAttribute(pchar, "questTemp.Saga.Jimmysecret"))
		{
			AddQuestRecord("Saga", "4");
		}
		else 
		{
			AddQuestRecord("Saga", "3");
		}
	}
	else if (sQuestName == "Saga_AfterDonovanBoarding")
	{
		sld = GetCharacter(NPC_GenerateCharacter("SagaTempsailor", "citiz_35", "man", "man", 10, sti(pchar.nation), 0, true, "quest"));
		sld.Dialog.Filename = "Quest\Saga\OtherNPC.c";
		sld.dialog.currentnode = "Tempsailor";
		ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc2");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		AddComplexSelfExpToScill(70, 70, 70, 70);
		AddComplexSeaExpToScill(100, 100, 100, 100, 100, 100, 0);
	}
	else if (sQuestName == "Saga_KillGonsalesA")	
	{
		chrDisableReloadToLocation = false; // открыть локацию
		LAi_group_Delete("EnemyFight");
		AddQuestRecord("Saga", "16");
	}
	else if (sQuestName == "Saga_KillGonsalesAK")	
	{
		chrDisableReloadToLocation = false; // открыть локацию
		LAi_group_Delete("EnemyFight");
		AddQuestRecord("Saga", "172");
	}
	else if (sQuestName == "Saga_KillGonsalesB")	
	{
		chrDisableReloadToLocation = false; // открыть локацию
		LAi_group_Delete("EnemyFight");
		AddQuestRecord("Saga", "18");
	}
	else if (sQuestName == "Saga_HireHelena")	
	{
		chrDisableReloadToLocation = false; // открыть локацию
		iTemp = 150 + sti(pchar.rank) * 5; // 14-add
		sld = characterFromId("Helena");
		LAi_SetHP(sld, iTemp, iTemp); 
		sld.quest.OfficerPrice = sti(pchar.rank) * 500;
		sld.OfficerWantToGo.DontGo = true; // не пытаться уйти
		sld.CompanionDisable = true; // нельзя в компаньоны - чтобы не утонула
		sld.HalfImmortal = true; // чтобы не убили в сухопутном бою
		sld.loyality = MAX_LOYALITY;
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, true);
		sld.Payment = true;
		sld.DontClearDead = true;
		sld.OfficerImmortal = true;
		sld.Health.HP = 60.0; 
		sld.Health.maxHP = 60.0;
		SetCharacterPerk(sld, "ShipEscape");
		sld.dialog.currentnode = "Helena_officer";
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		SaveCurrentNpcQuestDateParam(sld, "HiredDate");
	}
	// <-- начальная часть

	//------------------------------------- возвращение барона ------------------------------------------

	else if (sQuestName == "Saga_ShowDolly") // Даниэль показывает истукана
	{
		sld = characterFromId("Danielle");
		LAi_SetActorType(sld);
		sld.dialog.currentnode = "Dolly_2";
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}

	//--------------------------------------история Натана - видеоролики-----------------------
	else if (sQuestName == "Video_story") // 
	{
		switch(pchar.questTemp.LSC.Natanstory)
		{
			case "idol": 
				PChar.GenQuest.VideoAVI = "idol"; 
				break;
			case "temple": 
				PChar.GenQuest.VideoAVI = "temple"; 
				break;
			case "blackpearl": 
				PChar.GenQuest.VideoAVI = "blackpearl"; 
				break;
			case "artefact": 
				PChar.GenQuest.VideoAVI = "artefact"; 
				break;
			case "ending": 
				PChar.GenQuest.VideoAVI = "ending_story"; 
				break;
			case "VDDrepair": 
				PChar.GenQuest.VideoAVI = "VDDrepair"; 
				break;
		}
		PChar.GenQuest.VideoAfterQuest = "Video_continueStory";
		DoQuestCheckDelay("PostVideo_Start", 0.2);
	}
	else if (sQuestName == "Video_continueStory")
	{
		sld = characterFromId("Nathaniel");
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}
	// <-- история Натана - видеоролики

	// прибытие на Доминику через телепорт
	else if (sQuestName == "Dominica_TeleportArrive")
	{
		Dolly_TeleportConsequences();
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "Ground_sitting", "LSC_TeleportArrive_1", 3.0);
		LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false); // откроем дверь у Механика
		sld = characterFromId("Mechanic");
		sld.dialog.currentnode = "First time"; // patch-6
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true); // запретить драться
		LAi_LocationFightDisable(&Locations[FindLocation("Dominica_jungle_02")], true); // запретить драться
		chrDisableReloadToLocation = true; // закрыть локацию
		pchar.GenQuest.CirassExchangeDisable = true; // чтобы не снял скафандр
		LAi_LocationDisableOfficersGen("Indian_town", true); // не пускать офицеров в деревню
		LAi_LocationDisableOfficersGen("Dominica_jungle_02", true); // не пускать офицеров в локу телепорта
		for (i = 1; i <= 10; i++)
		{
			if (i == 1)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Dominica_Head", "canib", "man", "man", 30, PIRATE, 1, false, "native"));
				FantomMakeCoolFighter(sld, 30, 100, 100, "blade_02", "", "", 200);
				sld.dialog.Filename = "Quest\Saga\OtherNPC.c";
				sld.dialog.currentnode = "DominicaHead";	
				sld.name = StringFromKey("Saga_96");
				sld.lastname = StringFromKey("Saga_97");
				sld.greeting = "urakan"; 
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{	
				sld = GetCharacter(NPC_GenerateCharacter("Dominica_ind_" + i, "canib_" + (rand(5) + 1), "man", "man", 25, PIRATE, 1, false, "native"));
				FantomMakeCoolFighter(sld, 25, 80, 80, "blade_01", "", "", 100);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto" + i);
				LAi_CharacterDisableDialog(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		}
	}
	else if (sQuestName == "Saga_DominicaDollyReload")
	{
		DoQuestReloadToLocation("Dominica_jungle_02", "reload", "reload2_back", "Saga_DominicaDollyGo");
	}
	else if (sQuestName == "Saga_DominicaDollyGo")
	{
		sld = characterFromId("Dominica_Head");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "Dominica_jungle_02", "reload", "reload2_back");
		LAi_ActorGoToLocator(sld, "quest", "quest1", "Saga_DominicaDollyTalk", -1);
		LAi_SetActorType(pchar);
		LAi_ActorFollow(pchar, sld, "", -1);
		for (i = 2; i <= 10; i++)
		{
			sld = characterFromId("Dominica_ind_" + i);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, "Dominica_jungle_02", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		}
	}
	else if (sQuestName == "Saga_DominicaDollyTalk")
	{
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Dominica_Head");
		if (pchar.questTemp.Saga.BaronReturn == "third_teleport") 
		{
			sld.dialog.currentnode = "DominicaHead_6";
		}
		else 
		{
			sld.dialog.currentnode = "DominicaHead_4";
		}
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "Saga_DominicaDollyWait")
	{
		iTemp = 8;
		if (stf(environment.time) > 9.0) 
		{
			iTemp = 7;
		}
		GetCharacterPos(pchar, &locx, &locy, &locz);
		pchar.locx = locx;
		pchar.locy = locy;
		pchar.locz = locz;
		SetLaunchFrameFormParam(StringFromKey("Saga_98", iTemp), "Reload_To_Location", 0.1, 5.0);
		SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
		WaitDate("", 0, 0, 0, iTemp, 0);
		LaunchFrameForm();
		RefreshLandTime();
		RecalculateJumpTable();
		Whr_UpdateWeather();
		DoQuestCheckDelay("Saga_DominicaDollyTalk", 7.0);
		sld = characterFromId("Dominica_Head");
		ChangeCharacterAddressGroup(sld, "Dominica_jungle_02", "quest", "quest1");
	}
	// прибытие назад к деревне мискито через телепорт
	else if (sQuestName == "Pearl_TeleportArrive")
	{
		Dolly_TeleportConsequences();
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "Ground_sitting", "LSC_TeleportArrive_1", 3.0);
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true); // запретить драться
		// снимаем старые запреты
		LAi_LocationDisableOfficersGen("Indian_town", false); // пускать офицеров в деревню
		LAi_LocationDisableOfficersGen("Dominica_jungle_02", false); // пускать офицеров в локу телепорта
		LAi_LocationFightDisable(&Locations[FindLocation("Indian_town")], false); // разрешить драться
		LAi_LocationFightDisable(&Locations[FindLocation("Dominica_jungle_02")], false); // разрешить драться
		// Даниэль бежит к нам
		sld = characterFromId("Danielle");
		LAi_SetActorType(sld);
		sld.dialog.currentnode = "arrive";
		ChangeCharacterAddressGroup(sld, "Pearl_jungle_03", "item", "torch1");
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		pchar.questTemp.NotTeleportation = true; // нет телепортации более до поры

		if (pchar.questTemp.HelenDrinking.Result != "no_visit" && CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) >= 6) 
		{
			sld = CharacterFromID("Helena");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Pearl_jungle_03", "item", "torch1");
			LAi_ActorFollow(sld, pchar, "", -1);
		}
	}
	else if (sQuestName == "Pearl_TeleportArrive_1")
	{
		DeleteAttribute(pchar, "GenQuest.CannotWait"); // снимаем перманентный запрет перемотки в LSC
		DeleteAttribute(pchar, "GenQuest.CirassExchangeDisable"); // кирасы можно одевать
		bDisableFastReload = false; // открыть переход
		sld = characterFromId("Danielle");
		LAi_SetActorType(sld);
		sld.dialog.currentnode = "arrive_4";
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}

	//---------------------------------------нахождение в LSC--------------------------------------------------

	//--> прибытие через телепорт
	else if (sQuestName == "LSC_TeleportArrive")	
	{
		Dolly_TeleportConsequences();
		chrDisableReloadToLocation = false;
		bDisableFastReload = true; // закрыть переход
		pchar.GenQuest.CannotWait = true; // запрет ожидания
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "Ground_sitting", "LSC_TeleportArrive_1", 3.0);
		DoQuestCheckDelay("LSC_DrinkingAntidote", 6.5);
		if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "first_teleport")
		{
			pchar.questTemp.Saga.BaronReturn = "LSC";
			pchar.questTemp.LSC = "begin"; // флаг - мы в LSC
			bNoEatNoRats = true; // отменяем еду и крыс
			LSC_CreateCrabGuard(); // ставим краба
			LSC_CreateStateCitizens(); // ставим горожан-статиков
			// определяем пароли кланов
			sNrvParol = UpdateLSCClanParol();
			sRvdParol = UpdateLSCClanParol(); 
			log_Testinfo(sNrvParol);
			log_Testinfo(sRvdParol);
			// ставим прерывание на вход в кладовку
			pchar.quest.LSC_entry_pantry.win_condition.l1 = "location";
			pchar.quest.LSC_entry_pantry.win_condition.l1.location = "SanAugustineResidence";
			pchar.quest.LSC_entry_pantry.function = "LSC_CreatePantryGuard";
			// ставим прерывание на вход к Мэри
			pchar.quest.LSC_findMary.win_condition.l1 = "location";
			pchar.quest.LSC_findMary.win_condition.l1.location = "CeresSmithy";
			pchar.quest.LSC_findMary.function = "LSC_FindMary";
			AddQuestRecord("BaronReturn", "5");
			// квест марки
			QuestPointerToLoc("LostShipsCity_town", "reload", "reload2");
			QuestPointerToLoc("LostShipsCity_town", "reload", "reload38");
			QuestPointerToLoc("LostShipsCity_town", "reload", "reload60");
			PChar.quest.LSC_questmarkstart.win_condition.l1 = "ExitFromLocation";
			PChar.quest.LSC_questmarkstart.win_condition.l1.location = PChar.location;
			PChar.quest.LSC_questmarkstart.win_condition = "LSC_questmarkstart";
			// пускаем слухи
			AddSimpleRumourCityTip(StringFromKey("Saga_99"), "LostShipsCity", 2, 2, "LSC", "");
			AddSimpleRumourCityTip(StringFromKey("Saga_100"), "LostShipsCity", 2, 2, "LSC", "");
			AddSimpleRumourCityTip(StringFromKey("Saga_101"), "LostShipsCity", 2, 2, "LSC", "");
			AddSimpleRumourCityTip(StringFromKey("Saga_102"), "LostShipsCity", 2, 2, "LSC", "");
		}
	}
	else if (sQuestName == "LSC_TeleportArrive_1")	
	{
		LAi_ActorAnimation(Pchar, "Ground_StandUp", "pchar_back_to_player", 3.5);
	}
	//<-- прибытие через телепорт

	else if (sQuestName == "LSC_CrabGuardDie") // прибили краба	
	{
		// LAi_group_Delete("EnemyFight");
	}
	else if (sQuestName == "LSC_DrinkingAntidote") // пьём противоядие
	{
		if (CheckCharacterItem(pchar, "Ultimate_potion"))
		{
			pchar.systeminfo.NoNotifications = true;
			RemoveItems(pchar, "Ultimate_potion", 1);
			DeleteAttribute(pchar, "systeminfo.NoNotifications");
			notification(StringFromKey("Saga_103"), "None");
			LAi_SetCurHPMax(PChar);
			AddCharacterHealth(pchar, 50);
			DeleteAttribute(pchar, "chr_ai.poison");
			notification(StringFromKey("Saga_104"), "None");
			PlaySound("Ambient\Horror\Fear_breath_01.wav");
		}
	}
	else if (sQuestName == "LSC_questmarkstart") // стираем стартовые квестмарки
	{
		QuestPointerDelLoc("LostShipsCity_town", "reload", "reload2");
		QuestPointerDelLoc("LostShipsCity_town", "reload", "reload38");
		QuestPointerDelLoc("LostShipsCity_town", "reload", "reload60");
	}
	// --> ---------------------здесь регистрируем обиды групп LSC на ГГ-------------------------------
	else if (sQuestName == "LSC_NarvalConflict") // конфликт с нарвалами
	{
		if (!CheckAttribute(pchar, "GenQuest.NarvalConflict")) 
		{
			pchar.GenQuest.NarvalConflict = 1;
		}
		else 
		{
			pchar.GenQuest.NarvalConflict = sti(pchar.GenQuest.NarvalConflict) + 1;
		}
		LocatorReloadEnterDisable("LostShipsCity_town", "reload48", true); // закрыть вход к Дональду
		log_Testinfo("Конфликт с нарвалами достиг " + sti(pchar.GenQuest.NarvalConflict) + " ступени");
	}
	else if (sQuestName == "LSC_RivadosConflict") // конфликт с ривадос
	{
		if (!CheckAttribute(pchar, "GenQuest.RivadosConflict")) 
		{
			pchar.GenQuest.RivadosConflict = 1;
		}
		else 
		{
			pchar.GenQuest.RivadosConflict = sti(pchar.GenQuest.RivadosConflict) + 1;
		}
		LocatorReloadEnterDisable("LostShipsCity_town", "reload33", true); // закрыть вход к Эдди
		log_Testinfo("Конфликт с ривадос достиг " + sti(pchar.GenQuest.RivadosConflict) + " ступени");
	}
	else if (sQuestName == "LSC_SharkConflict") // конфликт с пиратами
	{
		if (!CheckAttribute(pchar, "GenQuest.SharkConflict")) 
		{
			pchar.GenQuest.SharkConflict = 1;
		}
		else 
		{
			pchar.GenQuest.SharkConflict = sti(pchar.GenQuest.SharkConflict) + 1;
		}
		LSC_CloseSanAvgustinDoors(); // закрыть сан-августин
		LSC_CloseTartarusDoors(); // закрыть Тартарус
		log_Testinfo("Конфликт с пиратами достиг " + sti(pchar.GenQuest.SharkConflict) + " ступени");
	}
	else if (sQuestName == "LSC_CitizenConflict") // избиение горожан строго наказуемо, вплоть до геймовера
	{
		if (!CheckAttribute(pchar, "GenQuest.CitizenConflict")) 
		{
			pchar.GenQuest.CitizenConflict = 1;
		}
		else 
		{
			pchar.GenQuest.CitizenConflict = sti(pchar.GenQuest.CitizenConflict) + 1;
			if (sti(pchar.GenQuest.CitizenConflict) == 5)
			{
				log_Testinfo("Ты - не геймер, ты - отморозок, и место твоему ГГ в тюрьме!");
				pchar.quest.LSC_GameOverPrison.win_condition.l1 = "location";
				pchar.quest.LSC_GameOverPrison.win_condition.l1.location = "LostShipsCity_town";
				pchar.quest.LSC_GameOverPrison.function = "LSC_GameOverPrison";
			}
		}
		log_Testinfo("Конфликт с горожанами достиг " + sti(pchar.GenQuest.CitizenConflict) + " ступени");
	}
	else if (sQuestName == "LSC_GameOverInPrison") // геймовер в тюрьме на Тартарусе
	{
		RemoveAllCharacterItems(pchar, true);
		DoQuestCheckDelay("LSC_GameOverPrisonEnd", 7.0);
		log_Testinfo("Довыделывался?");
	}
	else if (sQuestName == "LSC_GameOverPrisonEnd") // геймовер в тюрьме на Тартарусе
	{
		GameOver("mutiny");
	}
	// <-- обиды групп LSC на ГГ

	// ---------------------------- прочие функции, не относящиеся к квестам ---------------------------

	else if (sQuestName == "LSC_DrinkSit") // бухалово в одиночку в таверне
	{
		LAi_SetSitType(pchar);
		DoQuestCheckDelay("LSC_DrinkSitGo", 0.6);
	}
	else if (sQuestName == "LSC_DrinkSitGo") 
	{
		SetMusic("spa_music_tavern");
		AddMoneyToCharacter(pchar, -300);
		DoQuestCheckDelay("LSC_DrinkSitExit", 16.0);
	}
	else if (sQuestName == "LSC_DrinkSitExit") 
	{
		int iAddTime = 20 - sti(environment.time);
		StoreDayUpdate();
		WaitDate("", 0, 0, 0, iAddTime, 5);
		RecalculateJumpTable();
		RefreshWeather();
		RefreshLandTime();
		LAi_SetPlayerType(pchar);
		sld = ItemsFromID("potionrum");
		sld.shown = false;
		DoQuestReloadToLocation("FleuronTavern", "goto", "goto1", "");
	}
	// <-- прочие функции, не относящиеся к квестам

	//-------------------------------- охота на Акулу - вариант R -----------------------------------
	else if (sQuestName == "LSC_ChadGuardAttack_Fail") // атака не по сюжету, либо если завалил колдуна
	{
		for(i = 1; i <= 3; i++)
		{				
			sld = CharacterFromID("ChadGuard_" + i);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetHP(sld, 3000, 3000);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		sld = characterFromId("Capper");
		LAi_SetWarriorType(sld);
		LAi_SetImmortal(sld, true); // ГГ - однозначный капут
		ChangeCharacterAddressGroup(sld, "Tartarusprison", "goto", "goto8");
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	}
	else if (sQuestName == "LSC_Chimiset_ActivateDialog") // активация диалога при нападении на колдуна
	{
		DoQuestCheckDelay("hide_weapon", 0.1);
		sld = characterFromId("Chimiset");
		LAi_RemoveCheckMinHP(sld);
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}
	else if (sQuestName == "LSC_ChadGuard_Die") // перебили охрану Чада и его самого
	{
		InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
		DoQuestCheckDelay("hide_weapon", 1.0); // убрать оружие
		LAi_group_Delete("EnemyFight");
		sld = characterFromId("Chimiset");
		sld.dialog.currentnode = "Chad_die";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		AddComplexSelfExpToScill(100, 100, 100, 100);
	}
	else if (sQuestName == "LSC_EddyStay") // вертаем Эдди возможность разговора
	{
		chrDisableReloadToLocation = false; // открыть локацию
		sld = characterFromId("Eddy");
		sld.dialog.currentnode = "Total_info";
		LAi_SetOwnerType(sld);
	}
	else if (sQuestName == "LSC_AdolfDie") // прибили Адольфа
	{
		DoQuestCheckDelay("hide_weapon", 1.0); // убрать оружие
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false; // открыть локацию
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true); // запретить драться
		pchar.quest.LSC_AdolfDie.win_condition.l1 = "item";
		pchar.quest.LSC_AdolfDie.win_condition.l1.item = "letter_chad";
		pchar.quest.LSC_AdolfDie.function = "LSC_AdolfLetter";
		AddQuestRecord("SharkHunt", "15");
		AddSimpleRumourCityTip(StringFromKey("Saga_105"), "LostShipsCity", 5, 2, "LSC", "");
		AddSimpleRumourCityTip(StringFromKey("Saga_106"), "LostShipsCity", 5, 2, "LSC", "");
		AddComplexSelfExpToScill(50, 50, 50, 50);
	}
	else if (sQuestName == "LSC_CyclopNMaryDie") // убили Мэри и Циклопа
	{
		DoQuestCheckDelay("hide_weapon", 1.0); // убрать оружие
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true); // запретить драться
		LAi_group_Delete("EnemyFight");
		pchar.quest.LSC_MaryDie.win_condition.l1 = "item";
		pchar.quest.LSC_MaryDie.win_condition.l1.item = "letter_chad_1";
		pchar.quest.LSC_MaryDie.function = "LSC_MaryLetter";
		AddQuestRecord("SharkHunt", "17");
		AddComplexSelfExpToScill(100, 100, 100, 100);
	}
	else if (sQuestName == "LSC_EnterAevaWithMary") // следуем за Мэри на Эву
	{
		DoQuestReloadToLocation("AvaShipInside3", "reload", "reload1", "LSC_AevaWithMary");
	}
	else if (sQuestName == "LSC_AevaWithMary") // внутри Эвы
	{
		iRank = 30 + MOD_SKILL_ENEMY_RATE;
		iScl = 80;
		// нарвалы
		for (i = 1; i <= 3; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("CyclopGuard_" + i, "citiz_58", "man", "man", iRank, PIRATE, -1, true, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol4", "bullet", iScl * 2 + 100);
			sld.cirassId = Items_FindItemIdx("cirass1");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "AvaShipInside3", "quest", "quest" + i);
			LAi_CharacterDisableDialog(sld);
		}
		// Марчелло
		sld = characterFromId("Marchello");
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol6", "bullet", iScl * 2 + 200);
		sld.cirassId = Items_FindItemIdx("cirass1");
		LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, "AvaShipInside3", "quest", "quest4");
		LAi_SetActorType(sld);
		// идем в ловушку
		sld = characterFromId("Mary");
		ChangeCharacterAddressGroup(sld, "AvaShipInside3", "reload", "reload1");
		LAi_SetActorType(pchar);
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "goto", "goto2", "LSC_AevaMaryDialog", -1);
		LAi_ActorFollow(pchar, sld, "", -1);
	}
	else if (sQuestName == "LSC_AevaMaryDialog") // пришли в трюм
	{
		LAi_SetPlayerType(pchar);
		for (i = 1; i <= 3; i++)
		{
			sld = characterFromId("CyclopGuard_" + i);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		sld = characterFromId("Marchello");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		sld = characterFromId("Mary");
		sld.dialog.currentnode = "Town_4";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}

	//--------------------------------охота на Акулу - вар N ---------------------------------------
	else if (sQuestName == "LSC_SharkDie") // убили Акулу - ставим Декстера
	{
		sld = characterFromId("Dodson");
		sld.lifeday = 0;
		pchar.questTemp.Saga.DodsonDie = "true"; // атрибут Саге что Акула погиб
		sld = characterFromId("Dexter");
		sld.dialog.currentnode = "admiral";
		sld.greeting = "dexter_2";
		ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "sit", "sit1");
		LAi_SetHuberType(sld);
		LAi_group_MoveCharacter(sld, "LSC_SHARK");
		SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
		LocatorReloadEnterDisable("LostShipsCity_town", "reload25", true);
	}
	else if (sQuestName == "LSC_CarolineOpen") // открываем Каролину
	{
		LocatorReloadEnterDisable("LostShipsCity_town", "reload25", false);
		pchar.quest.LSC_CarolineEnter.win_condition.l1 = "location";
		pchar.quest.LSC_CarolineEnter.win_condition.l1.location = "CarolineBank";
		pchar.quest.LSC_CarolineEnter.function = "LSC_CarolineEnter";
	}
	else if (sQuestName == "LSC_MarynChadDie") // прибили Мэри и Чада - ищем Акулу
	{
		LAi_group_Delete("EnemyFight");
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true); // запретить драться
		sld = characterFromId("Dodson");
		if (LAi_GetCharacterHP(sld) > 0) // жив
		{
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "caroline_5";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 200); // везение
		}
		else
		{
			chrDisableReloadToLocation = false; // открыть локацию
			DoQuestCheckDelay("LSC_SharkDie", 1.0);
			AddQuestRecord("SharkHunt", "23");
		}
		AddComplexSelfExpToScill(150, 150, 150, 150);
	}
	else if (sQuestName == "LSC_SharkReturnSit") // Акулу на своё место
	{
		chrDisableReloadToLocation = false; // открыть локацию
		sld = characterFromId("Dodson");
		LAi_SetHuberType(sld);
		sld.dialog.currentnode = "Total_wait";
		ref rloc = &Locations[FindLocation("CarolineBank")];
		rloc.private1.key = "key_facio";
		rloc.private1.key.delItem = true;
		// ставим прерывание на письмо Фацио
		pchar.quest.LSC_letterFacio.win_condition.l1 = "item";
		pchar.quest.LSC_letterFacio.win_condition.l1.item = "letter_chad_1";
		pchar.quest.LSC_letterFacio.function = "LSC_FindLetterFacio";
		AddSimpleRumourCityTip(StringFromKey("Saga_107"), "LostShipsCity", 2, 2, "LSC", "");
		AddSimpleRumourCityTip(StringFromKey("Saga_108"), "LostShipsCity", 2, 2, "LSC", "");
		AddSimpleRumourCityTip(StringFromKey("Saga_109"), "LostShipsCity", 1, 2, "LSC", "");
	}

	//-------------------------------- охота на Акулу - вариант M -----------------------------------
	else if (sQuestName == "LSC_EnemiesMaryDie") // перебили негодяев на церес смити - ищем Мэри
	{
		DoQuestCheckDelay("hide_weapon", 1.0); // убрать оружие
		LAi_group_Delete("EnemyFight");
		PlayStereoOGG("music_LostShipsCity");
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true); // запретить драться
		sld = characterFromId("Mary");
		if (LAi_GetCharacterHP(sld) > 0) // жива
		{
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "mary";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			pchar.questTemp.LSC.Mary = "alive"; // Мэри найдена и жива - теперь она наша! Почти...
			AddCharacterExpToSkill(pchar, "Fortune", 100); // везение
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		}
		else
		{
			LAi_group_Delete("TMP_FRIEND"); // опаньки! если не потереть группу - то имеем вылет!
			pchar.quest.LSC_Maryletter.win_condition.l1 = "item";
			pchar.quest.LSC_Maryletter.win_condition.l1.item = "letter_chad_1";
			pchar.quest.LSC_Maryletter.function = "LSC_DieMaryletter";
			AddQuestRecord("SharkHunt", "29");
			pchar.questTemp.LSC.Mary = "die"; // Мэри мертва
		}
		AddComplexSelfExpToScill(50, 50, 50, 50);
	}
	else if (sQuestName == "LSC_ZikomoNearDoor") // Зикомо у дверей
	{
		sld = CharacterFromID("Zikomo");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "reload", "reload1", "LSC_ZikomoTurn", -1);
		DoQuestCheckDelay("LSC_RivadosPrisonAttack", 12.0);
	}
	else if (sQuestName == "LSC_ZikomoTurn") // поворот Зикомо
	{
		sld = CharacterFromID("Zikomo");
		ChangeCharacterAddressGroup(sld, "ProtectorFisher", "goto", "goto4");
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
	}
	else if (sQuestName == "LSC_ChimisetSit") // усадка Чимисета
	{
		sld = CharacterFromID("Chimiset");
		ChangeCharacterAddressGroup(sld, "ProtectorFisher", "sit", "sit1");
		LAi_SetHuberType(sld);
		sld.dialog.currentnode = "freedom";
	}
	else if (sQuestName == "LSC_RivadosPrisonAttack") // мотаем время
	{
		SetLaunchFrameFormParam(StringFromKey("Saga_110"), "", 0, 5);
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 3, 10); // крутим время
		RecalculateJumpTable();
		DoQuestCheckDelay("LSC_RivadosFreeChimiset", 5.0);
	}
	else if (sQuestName == "LSC_RivadosFreeChimiset") // ривадос вернулись с Чимисетом
	{
		sld = CharacterFromID("Zikomo"); // Зикомо на место
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "goto", "goto4", "LSC_ZikomoTurn", 10.0);
		sld = CharacterFromID("Chimiset"); // Чимисета на стул
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "ProtectorFisher", "reload", "reload1");
		LAi_ActorGoToLocator(sld, "sit", "sit1", "LSC_ChimisetSit", 10.0);
		sld = CharacterFromID("Eddy"); // Эдди к разговору
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "ProtectorFisher", "reload", "reload1");
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		AddCharacterExpToSkill(pchar, "Leadership", 100); // авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100); // везение
	}
	else if (sQuestName == "LSC_AdolfKillerDie") // прибили нарвала на Флорентине
	{
		DoQuestCheckDelay("hide_weapon", 1.0); // убрать оружие
		LAi_group_Delete("EnemyFight");
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
		pchar.quest.LSC_letterAdolf.win_condition.l1 = "item";
		pchar.quest.LSC_letterAdolf.win_condition.l1.item = "letter_chad";
		pchar.quest.LSC_letterAdolf.function = "LSC_letterAdolf_SF";
		AddComplexSelfExpToScill(70, 70, 70, 70);
	}
	else if (sQuestName == "LSC_CapperDieAeva") // Каппер капут на Эве
	{
		DoQuestCheckDelay("hide_weapon", 1.0); // убрать оружие
		LAi_group_Delete("EnemyFight");
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
		pchar.questTemp.LSC.CapperDie_Aeva = "true"; // атрибут - Каппер уничтожен
		LSC_OpenTartarusDoors(); // открыть Тартарус
		if (!CheckAttribute(pchar, "questTemp.LSC.Dodson_poison")) // не было разговора
		{
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "poison";
		}
		if (CheckAttribute(pchar, "questTemp.LSC.Whiskey_clear")) // виски не отравлен
		{
			AddQuestRecord("SharkHunt", "44");
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "clear"; // ноду Акуле
		}
		else
		{
			chrDisableReloadToLocation = false;
			if (CheckAttribute(pchar, "questTemp.LSC.Dodson_poison"))
			{
				AddQuestRecord("SharkHunt", "39_1");
				sld = CharacterFromID("Facio");
				sld.greeting = "facio_2";
				sld.dialog.currentnode = "whiskey";
				sld.quest.poisonnode = 1;
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Dodson_warning"))
				{ // Акула был предупрежден - снова к нему
					AddQuestRecord("SharkHunt", "39_2");
					sld = CharacterFromID("Facio");
					LAi_SetStayType(sld);
					sld.dialog.currentnode = "whiskey";
					sld.greeting = "facio_2";
					sld.quest.poisonnode = 3;
					LAi_CharacterDisableDialog(sld); // запрещаем диалог
					ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto10");
					sld = CharacterFromID("Dodson");
					sld.dialog.currentnode = "whiskey_7";
					LAi_CharacterEnableDialog(sld);
				}
				else 
				{
					AddQuestRecord("SharkHunt", "39");
				}
			}
		}
		AddComplexSelfExpToScill(200, 200, 200, 200);
	}
	else if (sQuestName == "LSC_CyclopInMaryCabin") // у Мэри - спасаем её от Циклопа
	{
		iRank = 25 + MOD_SKILL_ENEMY_RATE * 2;
		iScl = 80;
		DeleteAttribute(pchar, "questTemp.LSC.RescueMary");
		DeleteAttribute(pchar, "questTemp.NoFast"); // убираем запрет ускорения
		// Мэри
		sld = CharacterFromID("Mary");
		sld.greeting = "mary_2"; 
		if (!CheckAttribute(pchar, "questTemp.LSC.FailMary")) // успел
		{
			ChangeCharacterAddressGroup(sld, "CeresSmithy", "sit", "sit3");
			LAi_SetSitType(sld);
			LAi_CharacterDisableDialog(sld); // запрет диалога
			LAi_group_MoveCharacter(sld, "TMP_FRIEND");
		}
		else
		{
			LAi_KillCharacter(sld);
		}
		// ставим Циклопуса и утолщаем его
		sld = characterFromId("Marchello");
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol4", "bullet", iScl + 200);
		sld.cirassId = Items_FindItemIdx("cirass1");
		sld.MultiFighter = 1.4;
		if (MOD_SKILL_ENEMY_RATE > 7) sld.MultiFighter = 1.8; // мультифайтер
		SetSelfSkill(sld, iScl, iScl, iScl, iScl, iScl);
		if (!CheckAttribute(pchar, "questTemp.LSC.FailMary")) // успел
		{
			sld.dialog.currentnode = "mary";
			ChangeCharacterAddressGroup(sld, "CeresSmithy", "quest", "quest2"); // затаился, гад
			LAi_SetCheckMinHP(sld, 100, true, "LSC_MaryRunHelp_CS");
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto3", "LSC_CyclopDiag_CS", -1);
		}
		else
		{
			ChangeCharacterAddressGroup(sld, "CeresSmithy", "goto", "goto10");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_KillCyclop_CS");
		}
	}
	else if (sQuestName == "LSC_CyclopDiag_CS") // нашли Циклопа
	{
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID("Marchello");
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}
	else if (sQuestName == "LSC_MaryRunHelp_CS") // Мэри вступает в драку - помогает
	{
		sld = CharacterFromID("Mary");
		LAi_SetWarriorType(sld);
		ChangeCharacterAddressGroup(sld, "CeresSmithy", "barmen", "stay");
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER); // в нашу группу
		sld = CharacterFromID("Marchello");
		LAi_SetImmortal(sld, false);
	}
	else if (sQuestName == "LSC_KillCyclop_CS") // одолели Циклопа
	{
		DoQuestCheckDelay("hide_weapon", 1.0); // убрать оружие
		LAi_group_Delete("EnemyFight");
		PlayStereoOGG("music_LostShipsCity");
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true); // запретить драться
		pchar.questTemp.LSC.CyclopDie = "true";
		if (!CheckAttribute(pchar, "questTemp.LSC.FailMary")) // успел
		{
			sld = characterFromId("Mary");
			if (LAi_GetCharacterHP(sld) > 0) // жива
			{
				LAi_CharacterEnableDialog(sld); // разрешение диалога
				sld.dialog.currentnode = "happy";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0); // Мэри жива - теперь она наша! Совсем!
				AddCharacterExpToSkill(pchar, "Leadership", 500);
				AddCharacterExpToSkill(pchar, "Fortune", 300); // везение
			}
			else
			{
				AddQuestRecord("SharkHunt", "48");
				pchar.questTemp.LSC.Mary = "die"; // Мэри мертва - но такое навряд ли получится
				pchar.quest.LSC_marydienextstage.win_condition.l1 = "location";
				pchar.quest.LSC_marydienextstage.win_condition.l1.location = "LostShipsCity_town";
				pchar.quest.LSC_marydienextstage.win_condition = "LSC_MarydieNextstage";
			}
		}
		else
		{
			AddQuestRecord("SharkHunt", "50");
			pchar.questTemp.LSC.Mary = "die"; // Мэри мертва 
			pchar.quest.LSC_marydienextstage.win_condition.l1 = "location";
			pchar.quest.LSC_marydienextstage.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_marydienextstage.win_condition = "LSC_MarydieNextstage";
		}
		AddComplexSelfExpToScill(150, 150, 150, 150);
	}
	else if (sQuestName == "LSC_MarydieNextstage") 
	{
		DoQuestCheckDelay("LSC_MarydieNextstageFrame", 2.0);
	}
	else if (sQuestName == "LSC_MarydieNextstageFrame") 
	{
		LSC_MaryLoveWaitTime();
		SetLaunchFrameFormParam(StringFromKey("Saga_111"), "", 0, 4);
		LaunchFrameForm();
		DoQuestCheckDelay("LSC_MarydieNextstageReload", 4.0);
	}
	else if (sQuestName == "LSC_MarydieNextstageReload") 
	{
		LSC_ContinueAfterMaryCabin(); // завершающая функция
		DoQuestReloadToLocation("LostShipsCity_town", "goto", "goto09_4", "");
	}
	else if (sQuestName == "LSC_MaryRomantic_1") // Sinistra катсцена с поцелуями 
	{
		// if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
		locCameraFromToPos(44.41, 4.28, 95.70, true, 44.39, 2.25, 92.55);
		sld = characterFromId("Mary");
		TeleportCharacterToPosAy(sld, 44.90, 2.75, 93.00, -1.50);
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "kiss", "1", 7.5);
		TeleportCharacterToPosAy(pchar, 44.30, 2.75, 93.00, 1.50);
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "kiss", "1", 7.5);
		DoQuestCheckDelay("LSC_MaryRomantic_2", 3.0);
		DoQuestCheckDelay("LSC_MaryRomantic_3", 7.5);
	}
	else if (sQuestName == "LSC_MaryRomantic_2")
	{
		locCameraFromToPos(45.30, 4.43, 93.62, true, 43.61, 2.65, 92.50);
	}
	else if (sQuestName == "LSC_MaryRomantic_3")
	{
		pchar.GenQuest.FrameLockEsc = true;
		pchar.GenQuest.MusicContinue = true;
		SetLaunchFrameFormParam("", "", 0, 7);
		SetLaunchFrameFormPic("loading\inside\kiss.tga");
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 3, 10);
		RecalculateJumpTable();
		sld = characterFromId("Mary");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "CeresSmithy", "goto", "goto11");
		ChangeCharacterAddressGroup(pchar, "CeresSmithy", "goto", "goto10");
		DoQuestCheckDelay("LSC_MaryRomantic_4", 7.0);
		if (IsEquipCharacterByArtefact(pchar, "totem_03"))     
		{
			AddCharacterHealth(pchar, 24);
			AddCharacterMaxHealth(pchar, 2.0);
		}
		else 
		{
			AddCharacterHealth(pchar, 12); // Мэри восстанавливает здоровье лучше всех и без бальзама
			AddCharacterMaxHealth(pchar, 1.0);
		}
		LAi_SetCurHPMax(pchar);
	}
	else if (sQuestName == "LSC_MaryRomantic_4")
	{
		locCameraFromToPos(44.40, 4.63, 98.15, true, 43.11, 2.82, 99.44);
		EndQuestMovie();
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Mary");
		sld.dialog.currentnode = "happy_10";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "LSC_MaryRomantic_5") // на улицы
	{
		// здесь снять все установленные запреты
		bDisableCharacterMenu = false; // лоченые интерфейсы
		InterfaceStates.Buttons.Save.enable = true; // разрешить сохраняться
		LSC_ContinueAfterMaryCabin(); // завершающая функция
		DoQuestReloadToLocation("LostShipsCity_town", "goto", "goto09_4", "LSC_MaryReturnNormal");
		AddQuestRecord("SharkHunt", "47");
	}
	else if (sQuestName == "LSC_MaryReturnNormal") // вертаем Мэри в норму
	{
		sld = characterFromId("Mary");
		if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) sld.dialog.currentnode = "LSC_love";
		else sld.dialog.currentnode = "LSC_love_3";
		LAi_SetOwnerType(sld);
		chrDisableReloadToLocation = false; // открыть локацию 
	}
	else if (sQuestName == "LSC_MaryReturnNormal_1") // вертаем Мэри в норму
	{
		sld = characterFromId("Mary");
		LAi_SetOwnerType(sld);
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) LAi_SetOfficerType(sld); // patch-10
	}
	else if (sQuestName == "LSC_CyclopDie_Fl") // одолели Циклопа на Флероне
	{
		DoQuestCheckDelay("hide_weapon", 1.0); // убрать оружие
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true); // запретить драться
		LAi_group_Delete("EnemyFight");
		PlayStereoOGG("music_LostShipsCity");
		chrDisableReloadToLocation = false; // открыть локацию
		AddQuestRecord("SharkHunt", "52");
		pchar.questTemp.LSC.CyclopDie = "true";
		if (!CheckAttribute(pchar, "questTemp.LSC.Whiskey_clear"))
		{
			pchar.quest.LSC_WhiskeyStoryFinal.win_condition.l1 = "Timer";
			pchar.quest.LSC_WhiskeyStoryFinal.win_condition.l1.date.hour  = 6;
			pchar.quest.LSC_WhiskeyStoryFinal.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_WhiskeyStoryFinal.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_WhiskeyStoryFinal.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_WhiskeyStoryFinal.win_condition.l2 = "location";
			pchar.quest.LSC_WhiskeyStoryFinal.win_condition.l2.location = "LostShipsCity_town";
			pchar.quest.LSC_WhiskeyStoryFinal.function = "LSC_WhiskeyStoryFinal";
		}
		AddComplexSelfExpToScill(150, 150, 150, 150);
		pchar.questTemp.Saga.SharkHunt = "whiskey_final"; // меняем флаг
		sld = CharacterFromID("Facio");
		sld.dialog.currentnode = "First time";
		sld.greeting = "facio_1";
	}
	else if (sQuestName == "LSC_MaryTavern")
	{
		LAi_SetSitType(pchar);
		sld = characterFromId("Mary");
		ChangeCharacterAddressGroup(sld, "FleuronTavern", "quest", "sit1");
		LAi_SetSitType(sld);
		DoQuestFunctionDelay("LSC_MaryTavern", 0.6);
	}
	else if (sQuestName == "LSC_MaryTavernReturn")
	{
		LSC_MaryLoveWaitTime();
		DoQuestReloadToLocation("CeresSmithy", "goto", "goto10", "LSC_MaryTavernReturn_1");
	}
	else if (sQuestName == "LSC_MaryTavernReturn_1")
	{
		sld = characterFromId("Mary");
		LAi_SetOwnerType(sld);
		LAi_SetPlayerType(pchar);
		ChangeCharacterAddressGroup(sld, "CeresSmithy", "goto", "goto11");
		ChangeCharacterAddressGroup(pchar, "CeresSmithy", "goto", "goto10");
		if (IsEquipCharacterByArtefact(pchar, "totem_03"))     
		{
			AddCharacterHealth(pchar, 10);
			AddCharacterMaxHealth(pchar, 1.0);
		} 
		else 
		{
			AddCharacterHealth(pchar, 5); // ночь бухали - восстановление меньше
		}
		LAi_SetCurHPMax(pchar);
		DoQuestFunctionDelay("LSC_MaryLoveMorning", 1.0);
		sld = ItemsFromID("potionrum");
		sld.shown = false;
	}
	else if (sQuestName == "LSC_EnterPresentMary") // входим с Мэри в каюту Юргену
	{
		sld = characterFromId("Mary");
		sld.dialog.currentnode = "narval_3";
		ChangeCharacterAddressGroup(sld, "CeresSmithy", "goto", "goto12");
		DoQuestReloadToLocation("CeresSmithy", "reload", "reload1", "LSC_PresentMary");
	}
	else if (sQuestName == "LSC_PresentMary") // в каюте Юргена
	{
		StartQuestMovie(true, true, true);
		chrDisableReloadToLocation = true; // закрыть локацию
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Schmidt");
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, characterFromID("Mary"));
		sld = characterFromId("Mary");
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.7);
	}
	// ---------------------------------- возвращение на Остров ------------------------------------
	else if (sQuestName == "LSC_SetOlePassenger") // Оле - в пассажиры
	{
		sld = characterFromId("Ole");
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, false);
		pchar.GenQuest.Ole = true; // аналог крысобога
		SaveCurrentNpcQuestDateParam(sld, "pearl_date");
		sld.quest.pearlqty = 0; // счёт жемчужин
		if (GetCharacterIndex("Mary") != -1) // Мэри
		{
			sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		else // иначе завершение
		{
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		}
	}
	else if (sQuestName == "LSC_MaryWaitInCabin") // Мэри ждёт
	{
		sld = characterFromId("Mary");
		LAi_SetOwnerType(sld);
		sld.dialog.currentnode = "adversary"; 
		// до сдачи Даниэль Натаниэлю - закрываем вход к Мэри
		for (i = 0; i <= 3; i++)
		{
			LocatorReloadEnterDisable("LostShipsCity_town", "reload6" + i, true);
		}
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
	}
	else if (sQuestName == "LSC_DanielleRomantic") // Даниэль и Натаниэль
	{
		pchar.GenQuest.FrameLockEsc = true;
		pchar.GenQuest.MusicContinue = true;
		SetLaunchFrameFormParam("", "", 0, 8);
		SetLaunchFrameFormPic("loading\inside\kiss.tga");
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 0, 20); // крутим время
		RecalculateJumpTable();
		DoQuestCheckDelay("LSC_DanielleRomantic_1", 8.0);
	}
	else if (sQuestName == "LSC_DanielleRomantic_1") // второй эпизод...
	{
		LocCameraResetState();
		LAi_SetPlayerType(PChar);
		sld = characterFromId("Danielle");
		sld.dialog.currentnode = "nathaniel_8";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "LSC_LastNight_CS") // последняя ночь на Церес Смити
	{
		LAi_SetPlayerType(pchar);
		LSC_MaryLove();
	}
	else if (sQuestName == "LSC_Mary_hire") // найм Мэри: в отличие от всех прочих, её HP будет подбираться автолевеллингом
	{
		pchar.questTemp.LSC.Mary_officer = "true";
		iTemp = 250 + sti(pchar.rank) * 5;
		sld = characterFromId("Mary");
		LAi_SetHP(sld, iTemp, iTemp); 
		sld.quest.OfficerPrice = sti(pchar.rank) * 500;
		sld.OfficerWantToGo.DontGo = true; // не пытаться уйти
		sld.CompanionDisable = true; // Мэри подруга, а не компаньон
		sld.loyality = MAX_LOYALITY;
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, true);
		sld.Payment = true;
		DeleteAttribute(sld, "SaveItemsForDead"); // а вот сохранение вещей - фигушки, потеряете Мэри - нифига не получите
		sld.HoldEquip = true; // не отдавать оружие
		sld.location = "none";
		LAi_SetOfficerType(sld);
		sld.dialog.currentnode = "Mary_officer";
		sld.greeting = "mary_hire";
		// belamour legendary edition квестовое бессмертие -->
		sld.OfficerImmortal = true;
		sld.Health.HP = 60.0; 
		sld.Health.maxHP = 60.0;
		SetCharacterPerk(sld, "ShipEscape");
		// <-- legendary edition
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		SaveCurrentNpcQuestDateParam(sld, "HiredDate");
		// Мэри упакована сама по-полной
		TakeNItems(sld, "potion2", 8);
		TakeNItems(sld, "potion3", 3);
		TakeNItems(sld, "potion4", 3);
		EquipOfficerByArtefact(sld, "indian_7");
		if (CheckAttribute(sld, "quest.blade31"))
		{
			EquipOfficerByArtefact(sld, "indian_3");
			EquipOfficerByArtefact(sld, "indian_4");
		}
		else
		{
			EquipOfficerByArtefact(sld, "indian_1");
			EquipOfficerByArtefact(sld, "amulet_4");
		}
		// активируем поведение Мэри
		// если две недели не заниматься с ней любовью - будет требовать
		pchar.quest.Mary_giveme_sex.win_condition.l1 = "Timer";
		pchar.quest.Mary_giveme_sex.win_condition.l1.date.hour  = sti(GetTime());
		pchar.quest.Mary_giveme_sex.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
		pchar.quest.Mary_giveme_sex.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
		pchar.quest.Mary_giveme_sex.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
		pchar.quest.Mary_giveme_sex.function = "Mary_GiveMeSex";
		pchar.GenQuest.BrothelCount = 0; // нулим бордельный счетчик
		RemoveItems(pchar, "key_mary", 1); // удалить ключ Мэри - он уже не нужен
		Achievment_Set("ach_CL_119");
		
		// Квест Лонгвея "Путеводная звезда", начало 5 этапа
		if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap5_Start") && !CheckAttribute(pchar, "questTemp.PZ_ProvalFinal"))
		{
			PChar.quest.PZ_Etap5_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Etap5_Start.win_condition.l1.location = "Pirates_town";
			PChar.quest.PZ_Etap5_Start.win_condition = "PZ_Etap5_Start";
			AddMapQuestMarkCity("Pirates", false);
		}
		// Запуск квеста Дороже золота
		SetFunctionTimerCondition("GoldenGirl_Start", 0, 0, 1, false);
	}
	else if (sQuestName == "LSC_SetDodsonPassenger") // Акулу - в пассажиры
	{
		sld = characterFromId("Dodson");
		sld.greeting = "dodson_2"; 
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, false);
		LAi_SetImmortal(sld, true);
		chrDisableReloadToLocation = false; // открыть локацию
		sld = characterFromId("Svenson");
		sld.quest.shark = "true";
		pchar.quest.LSC_Dodson_SC.win_condition.l1 = "location";
		pchar.quest.LSC_Dodson_SC.win_condition.l1.location = "SantaCatalina_town";
		pchar.quest.LSC_Dodson_SC.function = "LSC_DodsonSC";
	}
	else if (sQuestName == "LSC_FinalDiosStory") // Диос - завершение рассказа 270912
	{
		sld = characterFromId("Dios");
		sld.dialog.currentnode = "LSC_4";
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}
	// --------------------------------------мини-квесты LSC -----------------------------------------
	else if (sQuestName == "LSC_DrinkLeonardTalk") // Леонард подходит
	{
		chrDisableReloadToLocation = true; // закрыть локацию
		sld = characterFromId("LSC_Leonard");
		LAi_RemoveLoginTime(sld);
		LAi_SetActorType(sld);
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "LSC_DrinkGotoCarolina") // выводим на улицы
	{
		DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload39", "LSC_DrinkGotoCarolina_1");
	}
	else if (sQuestName == "LSC_DrinkGotoCarolina_1") // идем к 'Каролине'
	{
		chrDisableReloadToLocation = false; // открыть локацию
		sld = characterFromId("LSC_Leonard");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "reload", "reload24", "LSC_DrinkGotoCarolina_2", -1);
		LAi_SetImmortal(sld, true);
		pchar.quest.LSC_Drink1.win_condition.l1 = "Timer";
		pchar.quest.LSC_Drink1.win_condition.l1.date.hour  = sti(GetTime() + 1);
		pchar.quest.LSC_Drink1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
		pchar.quest.LSC_Drink1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
		pchar.quest.LSC_Drink1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
		pchar.quest.LSC_Drink1.function = "LSC_DrinkDelete";
	}
	else if (sQuestName == "LSC_DrinkGotoCarolina_2") // стоит, ждёт
	{
		sld = characterFromId("LSC_Leonard");
		LAi_SetStayType(sld);
	}
	else if (sQuestName == "LSC_DrinkGotoCarolina_3") // телепорт внутрь каролины
	{
		DoQuestReloadToLocation("CarolineBank", "reload", "reload3", "pchar_back_to_player");
		chrDisableReloadToLocation = true;
		// считаем деньги и дублоны ГГ
		pchar.questTemp.LSC.Drink.Money = sti(pchar.money);
		pchar.questTemp.LSC.Drink.Dublon = GetCharacterItem(pchar, "gold_dublon");
	}
	else if (sQuestName == "LSC_DrinkInCarolina") // внутри каролины
	{
		chrDisableReloadToLocation = false;
		pchar.questTemp.LSC.Drink = "grabbing";
		LocatorReloadEnterDisable("CarolineBank", "reload1", true); // на галерею
		pchar.quest.LSC_Drink2.win_condition.l1 = "ExitFromLocation";
		pchar.quest.LSC_Drink2.win_condition.l1.location = pchar.location;
		pchar.quest.LSC_Drink2.win_condition = "LSC_DrinkLeonardTalk";
	}
	else if (sQuestName == "LSC_DrinkClear") // вертаем всех на места через три часа
	{
		chrDisableReloadToLocation = false; // открыть локацию
		sld = characterFromId("LSC_Leonard");
		LAi_SetImmortal(sld, false);
		pchar.quest.LSC_Drink3.win_condition.l1 = "Timer";
		pchar.quest.LSC_Drink3.win_condition.l1.date.hour  = sti(GetTime() + 3);
		pchar.quest.LSC_Drink3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
		pchar.quest.LSC_Drink3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
		pchar.quest.LSC_Drink3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
		pchar.quest.LSC_Drink3.function = "LSC_DrinkDelete";
	}
	// <-- пей до дна
	
	// --> тайна Санта-Люсии
	else if (sQuestName == "LSC_RingTalkLook") // смотрим на кольцо
	{
		LAi_SetPlayerType(pchar);
		LSC_RingRishardTalk("ring_13");
	}
	else if (sQuestName == "LSC_RingEnterInside") // входим в трюм разбитого корабля
	{
		chrDisableReloadToLocation = true; // закрыть локацию
		LocatorReloadEnterDisable("ExternalRingInside", "reload1", true);
		// ставим крабикусов
		iRank = 25 + MOD_SKILL_ENEMY_RATE * 2;
		iTemp = 150 + MOD_SKILL_ENEMY_RATE * 30 + sti(pchar.rank) * 5;
		LAi_group_Register("EnemyCrab");
		for (i = 1; i <= 10; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("CrabInside_" + i, "crabBig", "crab", "crabBig", iRank, PIRATE, -1, false, "quest"));
			sld.name = StringFromKey("Saga_112");
			sld.lastname = StringFromKey("Saga_113");
			GiveItem2Character(sld, "unarmed");
			EquipCharacterbyItem(sld, "unarmed");
			if (MOD_SKILL_ENEMY_RATE > 4) sld.MultiFighter = stf(MOD_SKILL_ENEMY_RATE / 2.5);
			sld.SaveItemsForDead = true;
			sld.animal = true;
			LAi_SetHP(sld, iTemp, iTemp);
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			LAi_SetWarriorType(sld);
			if (bPincers()) TakeNItems(sld, "crab_pincers", 2); // клешни
			ChangeCharacterAddressGroup(sld, "ExternalRingInside", "goto", "goto" + i);
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, false);
			LAi_group_MoveCharacter(sld, "EnemyCrab");
		}
		LAi_group_SetRelation("EnemyCrab", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_SetLookRadius("EnemyCrab", 13.0);
		LAi_group_SetHearRadius("EnemyCrab", 5.0);
		LAi_group_SetSayRadius("EnemyCrab", 8.0);
		LAi_group_SetCheck("EnemyCrab", "LSC_RingInsideCrabsDead");
		LAi_SetFightMode(pchar, true);
	}
	else if (sQuestName == "LSC_RingInsideCrabsDead") // перебили крабов
	{
		PlayStereoOGG("music_LostShipsCity");
		LAi_group_Delete("EnemyCrab");
		sld = characterFromId("LSC_Rishard");
		ChangeCharacterAddressGroup(sld, "ExternalRingInside", "reload", "reload1");
		LSC_RingRishardTalk("ring_15");
		AddComplexSelfExpToScill(150, 150, 150, 150);
	}
	else if (sQuestName == "LSC_RingDialog") // активатор диалогов
	{
		sld = characterFromId("LSC_Rishard");
		LSC_RingRishardTalk(sld.quest.diagnode);
	}
	else if (sQuestName == "LSC_RingEnterDeck") // входим на палубу разбитого корабля
	{
		chrDisableReloadToLocation = true; // закрыть локацию
		// ставим крабикусов
		iRank = 25 + MOD_SKILL_ENEMY_RATE * 2;
		iTemp = 150 + MOD_SKILL_ENEMY_RATE * 30 + sti(pchar.rank) * 5;
		for (i = 1; i <= 6; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("CrabDeck_" + i, "crabBig", "crab", "crabBig", iRank, PIRATE, -1, false, "quest"));
			sld.name = StringFromKey("Saga_112");
			sld.lastname = StringFromKey("Saga_113");
			GiveItem2Character(sld, "unarmed");
			EquipCharacterbyItem(sld, "unarmed");
			if (MOD_SKILL_ENEMY_RATE > 2) sld.MultiFighter = stf(MOD_SKILL_ENEMY_RATE / 2.5);
			sld.SaveItemsForDead = true;
			sld.animal = true;
			LAi_SetHP(sld, iTemp, iTemp);
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			ChangeCharacterAddressGroup(sld, "ExternalRingDeck", "goto", "goto" + i);
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, false);
			LAi_group_MoveCharacter(sld, "EnemyCrab");
		}
		LAi_group_SetRelation("EnemyCrab", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_SetLookRadius("EnemyCrab", 15.0);
		LAi_group_SetHearRadius("EnemyCrab", 6.0);
		LAi_group_SetSayRadius("EnemyCrab", 12.0);
		LAi_group_SetCheck("EnemyCrab", "LSC_RingDeckCrabsDead");
		LSC_RingRishardTalk("ring_22");
	}
	else if (sQuestName == "LSC_RingDeckCrabsDead") // перебили крабов
	{
		PlayStereoOGG("music_LostShipsCity");
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("ExternalRingDeck", "reload2", true);
		LAi_group_Delete("EnemyCrab");
		LSC_RingRishardTalk("ring_24");
		AddComplexSelfExpToScill(150, 150, 150, 150);
	}
	else if (sQuestName == "LSC_RingEnterCabin") // вошли в каюту
	{
		chrDisableReloadToLocation = true;
		sld = characterFromId("LSC_Rishard");
		sld.quest.diagnode = "ring_31";
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "goto", "goto1", "LSC_RingDialog", -1);
	}
	else if (sQuestName == "LSC_RingSetToBarman") // 
	{
		sld = characterFromId("LSC_Rishard");
		LAi_SetBarmanType(sld);
	}
	else if (sQuestName == "LSC_RingFinalStage") // 
	{
		sld = characterFromId("LSC_Rishard");
		sld.quest.ring_final = true;
		LAi_SetActorType(sld);
		LAi_SetImmortal(sld, false);
		LAi_ActorRunToLocator(sld, "reload", "reload1", "", 7.0);
		DoQuestFunctionDelay("LSC_RingOver", 7.0); // закрываем квест
		SetFunctionTimerCondition("LSC_RingDeleteItemsBoxes", 0, 0, 2, false); // через 2 дня боксы опустеют
	}
	else if (sQuestName == "LSC_RingFindGold") // нашли золото 
	{
		PlaySound("Ambient\LAND\door_001.wav");
		PlaySound("Ambient\LAND\door_004.wav");
		PlaySound("Types\warrior03.wav");
		PlaySound("Types\warrior04.wav");
		SetLaunchFrameFormParam(StringFromKey("Saga_114", NewStr()), "", 0, 6); // табличка
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 2, 10); // крутим время
		RecalculateJumpTable();
		sld = characterFromId("LSC_Rishard");
		sld.quest.diagnode = "ring_46";
		DoQuestCheckDelay("LSC_RingDialog", 6.0);
	}
	// <-- тайна Санта-Люсии
	// <-- нахождение в LSC

	//-------------------------------------- искушение Барбазона--------------------------------------
	else if (sQuestName == "Saga_ValetDie") // прибили Валета
	{
		LAi_group_Delete("EnemyFight");
		pchar.quest.Saga_Valet_letter.win_condition.l1 = "item";
		pchar.quest.Saga_Valet_letter.win_condition.l1.item = "letter_chad";
		pchar.quest.Saga_Valet_letter.function = "Saga_FindValetLetter";
		pchar.questTemp.Saga.BarbTemptation = "marlin";
		AddComplexSelfExpToScill(100, 100, 100, 100);
	}
	else if (sQuestName == "Saga_VensanTrapDestroyed") // изничтожили засаду на Терксе
	{
		chrDisableReloadToLocation = false;
		LAi_group_Delete("EnemyFight");
		pchar.questTemp.Saga.BarbTemptation.Vensan_canfree = "true"; // можно говорить с венсаном
		pchar.quest.Saga_Vensan_brigantine.win_condition.l1 = "location";
		pchar.quest.Saga_Vensan_brigantine.win_condition.l1.location = "Terks";
		pchar.quest.Saga_Vensan_brigantine.function = "Saga_CreateVensanEnemyes";
		AddQuestRecord("BarbTemptation", "13");
		AddComplexSelfExpToScill(100, 100, 100, 100);
	}
	else if (sQuestName == "Saga_DannyHurryHelp") // Даниэль помогает
	{
		sld = characterFromId("Danielle");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		LAi_SetHP(sld, 500, 500); // увеличиваем ей НР
		sld.cirassId = Items_FindItemIdx("cirass1");
		TakeNItems(sld, "potion2", 5);
		LAi_SetCheckMinHP(sld, 10, true, ""); // скрытое бессмертие
		sld = characterFromId("Saga_JackmanCabinHelper");
		LAi_SetImmortal(sld, false);
	}
	else if (sQuestName == "Saga_AfterJackmanBoarding") // прибили Джекмана
	{
		pchar.questTemp.Saga.BarbTemptation = "after_boarding"; // меняем флаг
		sld = characterFromId("Danielle");
		sld.dialog.currentnode = "after_boarding";
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindNearestFreeLocator("loc", locx, locy, locz));
		pchar.GenQuest.CannotReloadBoarding = true; // нельзя перегружаться
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
		AddComplexSelfExpToScill(150, 150, 150, 150);
		AddComplexSeaExpToScill(220, 220, 220, 220, 220, 220, 0);
	}
	else if (sQuestName == "Saga_StormingGroupTurn") // поворот матросов
	{
		for (i = 1; i <= 2; i++)
		{
			sld = characterFromId("Saga_SGM_" + i);
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "sit", "sit1");
		}
	}
	// <-- искушение Барбазона
		
	//---------------------------------------Тени прошлого-------------------------------------------
	else if (sQuestName == "Saga_FinalLedbitterStory") // завершение рассказа
	{
		if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sld = characterFromId("Dodson");
		else sld = characterFromId("Terrax");
		sld.dialog.currentnode = "shadows_6";
		LAi_SetActorType(sld);
		LAi_ActorSetHuberMode(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}
	// бой с Джессикой
	else if (sQuestName == "Saga_JessikaFirstKick") // фокус первый - хватка тяжести + 5 скелетов
	{
		sld = characterFromId("Jessika");
		sld.dialog.currentnode = "stage_1";
		DoQuestCheckDelay("Saga_JessikaFirstKick_1", 0.5);
	}
	else if (sQuestName == "Saga_JessikaFirstKick_1")
	{
		PlaySound("Ambient\Teno_inside\teleporter.wav");
		CreateLocationParticles("item", "quest", "top", 1.0, 0, 0, "");
		CreateLocationParticles("item", "quest", "top", 1.0, 0, 0, "");
		CreateLocationParticles("item", "quest", "top", 1.0, 0, 0, "");
		sld = characterFromId("Jessika");
		ChangeCharacterAddressGroup(sld, "shore67", "quest", "top");
		pchar.questTemp.Saga.Attack = true; // обработка в АИ
		pchar.questTemp.Saga.Jess_Fightstage = "next";
		sTotalTemp = "top";
		iTotalTemp = 12;
	}
	else if (sQuestName == "Saga_JessikaFirstKick_2")
	{
		LAi_SetActorType(Pchar);
		LAi_ActorAnimation(Pchar, "Ground_StandUp", "", 3.5);
		DoQuestCheckDelay("Saga_JessikaFirstKick_3", 3.5);
		CreateLocationParticles("blast_inv", "quest", "top", 1.6, 0, 0, "");
		sTemp = pchar.location.locator;
		CreateLocationParticles("blast_inv", "goto", sTemp, 1.3, 0, 0, "");
		CreateLocationParticles("blood_big", "goto", sTemp, 1.0, 0, 0, "");
		CreateLocationParticles("blood_big", "goto", sTemp, 1.3, 0, 0, "");
		PlaySound("People Fight\Death_NPC_08.wav");
		PlaySound("Interface\boom.wav");
		Pchar.chr_ai.hp = stf(Pchar.chr_ai.hp) / 1.5; // 1/3 жизни сносим 
		Log_Info(StringFromKey("Saga_115"));
		pchar.GenQuest.CantRun = true;
	}
	else if (sQuestName == "Saga_JessikaFirstKick_3")
	{
		LAi_SetPlayerType(Pchar);
		CheckAndSetOverloadMode(GetMainCharacter());
		PlaySound("Interface\boom.wav");
		for (i = 1; i <= 6; i++)
		{
			sld = characterFromId("Reef_skeleton_" + i);
			sld.monster = true; // признак нежити
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			PlaySound("types\skel.wav");
			CreateLocationParticles("blast_inv", "quest", "skeleton" + i, 1.3, 0, 0, "");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Saga_JessikaFirstKick_4");
		LAi_SetFightMode(pchar, true);
		// поджигаем угол у скалы
		pchar.quest.Saga_JessFire3.win_condition.l1 = "locator";
		pchar.quest.Saga_JessFire3.win_condition.l1.location = "shore67";
		pchar.quest.Saga_JessFire3.win_condition.l1.locator_group = "quest";
		pchar.quest.Saga_JessFire3.win_condition.l1.locator = "fire3";
		pchar.quest.Saga_JessFire3.function = "Saga_JessFireStep";
		CreateLocationParticles("shipfire", "quest", "fire3", 0.5, 0, 0, "");
		// зажигаем огоньки
		chr = &Locations[FindLocation(pchar.location)];
		chr.hell_fire_1 = true;
		for (i = 1; i <= 25; i++)
		{
			CreateLocationParticles("torch", "item", "fire" + i, 0.1, 0, 0, "");
		}
	}
	else if (sQuestName == "Saga_JessikaFirstKick_4")
	{
		sld = characterFromId("Jessika");
		LAi_SetImmortal(sld, false);
		LAi_SetCurHPMax(sld);
		LAi_SetCheckMinHP(sld, 10, true, "Saga_JessikaSecondKick"); // второй фокус
		CreateLocationParticles("blast_inv", "quest", "skeleton1", 1.3, 0, 0, "");
		PlaySound("Ambient\Teno_inside\teleporter.wav");
		ChangeCharacterAddressGroup(sld, "shore67", "quest", "skeleton1");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	}
	else if (sQuestName == "Saga_JessikaSecondKick") // фокус второй - уменьшение владением ХО + 5 скелетов
	{
		sld = characterFromId("Jessika");
		sld.dialog.currentnode = "stage_2";
		DoQuestCheckDelay("Saga_JessikaSecondKick_1", 0.5);
	}
	else if (sQuestName == "Saga_JessikaSecondKick_1")
	{
		CreateLocationParticles("item", "quest", "rock", 1.0, 0, 0, "");
		CreateLocationParticles("item", "quest", "rock", 1.0, 0, 0, "");
		CreateLocationParticles("item", "quest", "rock", 1.0, 0, 0, "");
		PlaySound("Ambient\Teno_inside\teleporter.wav");
		sld = characterFromId("Jessika");
		ChangeCharacterAddressGroup(sld, "shore67", "quest", "rock");
		pchar.questTemp.Saga.Attack = true; // обработка в АИ
		sTotalTemp = "rock";
		iTotalTemp = 5;
	}
	else if (sQuestName == "Saga_JessikaSecondKick_2")
	{
		LAi_SetActorType(Pchar);
		LAi_ActorAnimation(Pchar, "Ground_StandUp", "", 3.5);
		DoQuestCheckDelay("Saga_JessikaSecondKick_3", 3.5);
		CreateLocationParticles("blast_inv", "quest", "rock", 1.6, 0, 0, "");
		sTemp = pchar.location.locator;
		CreateLocationParticles("blast_inv", "goto", sTemp, 1.3, 0, 0, "");
		CreateLocationParticles("blood_big", "goto", sTemp, 1.0, 0, 0, "");
		CreateLocationParticles("blood_big", "goto", sTemp, 1.3, 0, 0, "");
		PlaySound("People Fight\Death_NPC_08.wav");
		PlaySound("Interface\boom.wav");
		Pchar.chr_ai.hp = stf(Pchar.chr_ai.hp) / 2; // 1/2 жизни сносим 
		Log_Info(StringFromKey("Saga_116"));
	}
	else if (sQuestName == "Saga_JessikaSecondKick_3")
	{
		LAi_SetPlayerType(Pchar);
		PlaySound("Interface\boom.wav");
		// скелетоны
		iRank = 20 + MOD_SKILL_ENEMY_RATE * 2;
		iScl = 60;
		for (i = 5; i <= 9; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Reef_skeleton_add_" + i, "skel" + (rand(3) + 1), "skeleton", "skeleton", iRank, PIRATE, -1, false, "quest"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_13", "", "", iScl * 2);
			sld.cirassId = Items_FindItemIdx("cirass3");
			if (i > 5)
			{
				sld.cirassId = Items_FindItemIdx("cirass1");
				if (MOD_SKILL_ENEMY_RATE > 4)
				{
					fMft = MOD_SKILL_ENEMY_RATE / 10;
					sld.MultiFighter = 0.8 + fMft; // мультифайтер
				}
			}
			sld.monster = true; // признак нежити
			ChangeCharacterAddressGroup(sld, "shore67", "quest", "skeleton" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			PlaySound("types\skel.wav");
			CreateLocationParticles("blast_inv", "quest", "skeleton" + i, 1.3, 0, 0, "");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Saga_JessikaSecondKick_4");
		LAi_SetFightMode(pchar, true);
		// закрываем доступ на крыльцо
		pchar.quest.Saga_JessFire.win_condition.l1 = "locator";
		pchar.quest.Saga_JessFire.win_condition.l1.location = "shore67";
		pchar.quest.Saga_JessFire.win_condition.l1.locator_group = "quest";
		pchar.quest.Saga_JessFire.win_condition.l1.locator = "entrance";
		pchar.quest.Saga_JessFire.function = "Saga_JessFireStep";
		CreateLocationParticles("shipfire", "quest", "entrance", 0.5, 0, 0, "");
		// зажигаем огоньки
		chr = &Locations[FindLocation(pchar.location)];
		chr.hell_fire_2 = true;
		for (i = 26; i <= 40; i++)
		{
			CreateLocationParticles("torch", "item", "fire" + i, 0.1, 0, 0, "");
		}
	}
	else if (sQuestName == "Saga_JessikaSecondKick_4")
	{
		sld = characterFromId("Jessika");
		LAi_SetImmortal(sld, false);
		LAi_SetCurHPMax(sld);
		LAi_SetCheckMinHP(sld, 10, true, "Saga_JessikaThirdKick"); // третий фокус
		CreateLocationParticles("blast_inv", "quest", "skeleton8", 1.3, 0, 0, "");
		PlaySound("Ambient\Teno_inside\teleporter.wav");
		ChangeCharacterAddressGroup(sld, "shore67", "quest", "skeleton8");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	}
	else if (sQuestName == "Saga_JessikaThirdKick") // фокус третий - уменьшение энергии + отравленный клинок
	{
		sld = characterFromId("Jessika");
		sld.dialog.currentnode = "stage_3";
		DoQuestCheckDelay("Saga_JessikaThirdKick_1", 0.5);
	}
	else if (sQuestName == "Saga_JessikaThirdKick_1")
	{
		CreateLocationParticles("item", "quest", "wall", 1.0, 0, 0, "");
		CreateLocationParticles("item", "quest", "wall", 1.0, 0, 0, "");
		CreateLocationParticles("item", "quest", "wall", 1.0, 0, 0, "");
		PlaySound("Ambient\Teno_inside\teleporter.wav");
		sld = characterFromId("Jessika");
		ChangeCharacterAddressGroup(sld, "shore67", "quest", "wall");
		pchar.questTemp.Saga.Attack = true; // обработка в АИ
		sTotalTemp = "wall";
		iTotalTemp = 4;
	}
	else if (sQuestName == "Saga_JessikaThirdKick_2")
	{
		LAi_SetActorType(Pchar);
		LAi_ActorAnimation(Pchar, "Ground_StandUp", "", 3.5);
		DoQuestCheckDelay("Saga_JessikaThirdKick_3", 3.5);
		CreateLocationParticles("blast_inv", "quest", "wall", 1.6, 0, 0, "");
		Pchar.chr_ai.hp = stf(Pchar.chr_ai.hp) / 3; // 2/3 жизни сносим
		Log_Info(StringFromKey("Saga_117"));
		PlaySound("People Fight\Death_NPC_08.wav");
		CreateLocationParticles("blood_big", "quest", "wall", 1.3, 0, 0, "");
		CreateLocationParticles("blood_big", "quest", "wall", 1.0, 0, 0, "");
		PlaySound("Sea Battles\bolshoy_vsplesk_001.wav");
	}
	else if (sQuestName == "Saga_JessikaThirdKick_3")
	{
		LAi_SetPlayerType(Pchar);
		SetMusic("music_teleport");
		CreateLocationParticles("blast_inv", "quest", "wall", 1.6, 0, 0, "");
		PlaySound("Interface\boom.wav");
		sld = characterFromId("Jessika");
		LAi_SetImmortal(sld, false);
		LAi_SetCurHPMax(sld);
		LAi_SetCheckMinHP(sld, 10, true, "Saga_JessikaBattleTalk"); // разговор
		ChangeCharacterAddressGroup(sld, "shore67", "quest", "bridge1");
		CreateLocationParticles("blast_inv", "quest", "bridge1", 1.3, 0, 0, "");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_SetFightMode(pchar, true);
		// закрываем выход c моста
		pchar.quest.Saga_JessFire1.win_condition.l1 = "locator";
		pchar.quest.Saga_JessFire1.win_condition.l1.location = "shore67";
		pchar.quest.Saga_JessFire1.win_condition.l1.locator_group = "quest";
		pchar.quest.Saga_JessFire1.win_condition.l1.locator = "fire1";
		pchar.quest.Saga_JessFire1.function = "Saga_JessFireStep";
		CreateLocationParticles("shipfire", "quest", "fire1", 0.5, 0, 0, "");
		// зажигаем огоньки
		chr = &Locations[FindLocation(pchar.location)];
		chr.hell_fire_3 = true;
	}
	else if (sQuestName == "Saga_JessikaBattleTalk") // разговор после последней стадии боя
	{
		DoQuestCheckDelay("hide_weapon", 0.5); // убрать оружие
		sld = characterFromId("Jessika");
		sld.dialog.currentnode = "stage_4";
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
		AddComplexSelfExpToScill(450, 450, 450, 450);
		LAi_group_Delete("EnemyFight");
	}
	else if (sQuestName == "Saga_JessikaDie") // убили Джесс
	{
		LAi_group_Delete("EnemyFight");
		pchar.quest.Saga_JessFire.over = "yes"; 
		pchar.quest.Saga_JessFire1.over = "yes"; 
		pchar.quest.Saga_JessFire2.over = "yes"; // снимаем реакцию на огонь
		chr = &Locations[FindLocation(pchar.location)];
		DeleteAttribute(chr, "hell_fire_1");
		DeleteAttribute(chr, "hell_fire_2");
		DeleteAttribute(chr, "hell_fire_3");
		pchar.quest.Saga_FindBeatriss_Letter.win_condition.l1 = "item";
		pchar.quest.Saga_FindBeatriss_Letter.win_condition.l1.item = "letter_beatriss";
		pchar.quest.Saga_FindBeatriss_Letter.function = "Saga_FindBeatrissLetter";
	}
	else if (sQuestName == "Video_Jess") // видео о Джесс
	{
		PChar.GenQuest.VideoAVI = "Jessika";
		PChar.GenQuest.VideoAfterQuest = "Video_continueSvensonStory";
		DoQuestCheckDelay("PostVideo_Start", 0.2);
	}
	else if (sQuestName == "Video_continueSvensonStory") // завершение рассказа
	{
		sld = characterFromId("Svenson");
		sld.dialog.currentnode = "saga_66a";
		LAi_SetActorType(sld);
		LAi_ActorSetSitMode(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}
	else if (sQuestName == "Video_Reef") // видео о рифе
	{
		PChar.GenQuest.VideoAVI = "Reef";
		PChar.GenQuest.VideoAfterQuest = "Video_continueJessStory";
		DoQuestCheckDelay("PostVideo_Start", 0.2);
	}
	else if (sQuestName == "Video_continueJessStory")
	{
		PlayStereoOGG("music_shore");
		sld = characterFromId("Jessika");
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}
	else if (sQuestName == "Video_Reef2") // видео о рифе
	{
		PChar.GenQuest.VideoAVI = "Jessika_fight";
		PChar.GenQuest.VideoAfterQuest = "Video_continueJessStory2";
		DoQuestCheckDelay("PostVideo_Start", 0.2);
	}
	else if (sQuestName == "Video_continueJessStory2")
	{
		PlayStereoOGG("music_shore");
		sld = characterFromId("Jessika");
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}
	else if (sQuestName == "Saga_BarbadosTreatment") // начинаем молитвы
	{
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "barmen", "bar1", "Saga_BarbadosBead", -1);
		bDisableCharacterMenu = true; // лоченые интерфейсы
		InterfaceStates.Buttons.Save.enable = false; // запретить сохраняться
	}
	else if (sQuestName == "Saga_BarbadosBead") // молимся
	{
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "Bead", "OpenTheDoors", -1);
		DoQuestCheckDelay("Saga_BarbadosTreatmentStart", 10.0);
	}
	else if (sQuestName == "Saga_BarbadosTreatmentStart") // рамка
	{
		SetLaunchFrameFormParam(StringFromKey("Saga_118", NewStr()), "Saga_JessikaSoul", 0, 6);
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 9, 10); // крутим время
		RecalculateJumpTable();
	}
	else if (sQuestName == "Saga_JessikaSoul") // телепортируем в спецлокацию
	{
		DoQuestReloadToLocation("Terrain", "reload", "reload2", "Saga_JessikaSoul_1");
	}
	else if (sQuestName == "Saga_JessikaSoul_1")
	{
		ChangeShowIntarface();
		LAi_SetPlayerType(pchar);
		pchar.questTemp.Saga.JessSoul = "true";
		DoQuestCheckDelay("TalkSelf_Quest", 0.1);
	}
	else if (sQuestName == "Saga_JessikaSoul_2")
	{
		SetMusic("music_terrain");
		LAi_SetActorType(pchar);
		LAi_ActorTurnToLocator(pchar, "reload", "reload1");
		DoQuestCheckDelay("Saga_JessikaSoul_2_1", 4.0);
		DeleteAttribute(pchar, "questTemp.Saga.JessSoul"); // 021012
	}
	else if (sQuestName == "Saga_JessikaSoul_2_1")
	{
		CreateLocationParticles("shadowstar", "reload", "reload1", 1.15, 0, 0, "");
		CreateLocationParticles("shadowstar", "reload", "reload1", 1.15, 0, 0, "");
		CreateLocationParticles("shadowstar", "reload", "reload1", 1.15, 0, 0, "");
		DoQuestCheckDelay("Saga_JessikaSoul_2_2", 3.0);
	}
	else if (sQuestName == "Saga_JessikaSoul_2_2") // встреча с очищенной душой Джесс
	{
		sld = GetCharacter(NPC_GenerateCharacter("Jessika_soul", "Jessika", "woman", "jess", 1, PIRATE, 0, false, "quest"));
		sld.name = StringFromKey("Saga_119");
		sld.lastname = StringFromKey("Saga_120");
		sld.greeting = "Jessika_soul";
		sld.Dialog.Filename = "Quest\Saga\Jessika.c";
		sld.dialog.currentnode = "soul";
		ChangeCharacterAddressGroup(sld, "Terrain", "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "reload", "reload2", "", -1);
		DoQuestCheckDelay("Saga_JessikaSoul_3", 18.5);
	}
	else if (sQuestName == "Saga_JessikaSoul_3") // Джесс начинает разговор
	{
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Jessika_soul");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		SetMusic("music_romantic");
	}
	else if (sQuestName == "Saga_JessikaSoul_4") // перекидываем назад в церковь
	{
		DoQuestReloadToLocation("bridgetown_church", "barmen", "bar1", "Saga_JessikaSoul_5");
	}
	else if (sQuestName == "Saga_JessikaSoul_5") // снимаем отрицательные атрибуты
	{
		LAi_SetPlayerType(pchar);
		DeleteAttribute(pchar, "GenQuest.CantRun");
		CheckAndSetOverloadMode(GetMainCharacter());
		DeleteAttribute(pchar, "GenQuest.BladePenalty");
		DeleteAttribute(pchar, "GenQuest.EnergyPenalty");
		AddCharacterHealth(pchar, 50);
		AddCharacterMaxHealth(pchar, 5);
		chrDisableReloadToLocation = false; // открыть локацию
		bDisableCharacterMenu = false;
		InterfaceStates.Buttons.Save.enable = true;
		AddQuestRecord("Shadows", "12");
		CloseQuestHeader("Shadows");
		// вертаем в норму священника
		sld = characterFromId("Bridgetown_Priest");
		LAi_SetLoginTime(sld, 6.0, 21.99);
		LAi_SetPriestType(sld);
		ChangeCharacterAddressGroup(sld, "bridgetown_church", "barmen", "stay");
		AddCharacterExpToSkill(pchar, "Leadership", 200); // авторитет
	}
	//<-- Тени прошлого

	//---------------------------------------Завещание Шарпа-------------------------------------------
	else if (sQuestName == "Saga_CourtGo") // выводим на улицу
	{
		DoQuestReloadToLocation("PortRoyal_town", "reload", "houseSp4", "Saga_CourtGo_1");
	}
	else if (sQuestName == "Saga_CourtGo_1") // идем в резиденцию
	{
		ChangeShowIntarface();
		sld = characterFromId("Helena");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "PortRoyal_town", "reload", "houseSp4");
		chr = characterFromId("Loxly");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(chr, "PortRoyal_town", "reload", "houseSp4");
		LAi_ActorGoToLocator(chr, "reload", "reload3_back", "Saga_CourtGo_2", -1);
		LAi_ActorFollow(pchar, chr, "", -1);
		LAi_ActorFollow(sld, chr, "", -1);
	}
	else if (sQuestName == "Saga_CourtGo_2") // входим в резиденцию
	{
		pchar.systeminfo.stopsound = true; // тормозим инит схемы
		DoQuestReloadToLocation("PortRoyal_townhall", "reload", "reload1", "Saga_CourtGo_3");
	}
	else if (sQuestName == "Saga_CourtGo_3") // запускаем ролик суда
	{
		PChar.GenQuest.VideoAVI = "court";
		PChar.GenQuest.VideoAfterQuest = "Saga_CourtGo_4";
		DoQuestCheckDelay("PostVideo_Start", 0.2);
	}
	else if (sQuestName == "Saga_CourtGo_4") // суд прошел
	{
		DeleteAttribute(pchar, "systeminfo.stopsound");
		SetLaunchFrameFormParam(StringFromKey("Saga_121"), "", 0, 5);
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 5, 10); // крутим время
		RecalculateJumpTable();
		DoQuestCheckDelay("Saga_CourtReload", 4.5);
	}
	else if (sQuestName == "Saga_CourtReload") // перекидываем в дом адвоката
	{
		DoQuestReloadToLocation("PortRoyal_houseSp4", "quest", "quest1", "Saga_CourtFinish");
	}
	else if (sQuestName == "Saga_CourtFinish") // расставим всех по локаторам
	{
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Helena");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "PortRoyal_houseSp4", "quest", "quest3");
		sld = characterFromId("Loxly");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "PortRoyal_houseSp4", "quest", "quest2");
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}
	else if (sQuestName == "Saga_HelenaIslaTesoro") // Элен с ГГ на улице - подводим итоги Саги
	{
		sld = characterFromId("Loxly");
		LAi_SetHuberType(sld);
		ChangeCharacterAddressGroup(sld, "PortRoyal_houseSp4", "sit", "sit1");
		sld = characterFromId("Helena");
		sld.dialog.currentnode = "result";
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "PortRoyal_town", "quest", "quest4");
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}
	else if (sQuestName == "Saga_HelenaBye") // расстаемся с Элен по собственному решению, не стираем
	{
		chrDisableReloadToLocation = true; // закрыть локацию
		sld = characterFromId("Helena");
		RemovePassenger(pchar, sld);
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload5_back", "none", "", "", "Saga_HelenaOnIsland", 10.0);
		LAi_CharacterDisableDialog(sld);
		AddQuestRecord("Testament", "12");
		CloseQuestHeader("Testament");
	}
	else if (sQuestName == "Saga_HelenaOnIsland") // Элен на Исла Тесоро
	{
		chrDisableReloadToLocation = false;
		sld = characterFromId("Helena");
		ChangeCharacterAddressGroup(sld, "Pirates_townhall", "goto", "goto1");
		LAi_SetOwnerType(sld);
		sld.dialog.currentnode = "islatesoro";
	}
	else if (sQuestName == "Saga_HelenaRomantic") // романтик-сцена
	{
		pchar.GenQuest.FrameLockEsc = true;
		SetLaunchFrameFormParam("", "", 0, 10);
		SetLaunchFrameFormPic("loading\inside\kiss.tga");
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 3, 10); // крутим время
		RecalculateJumpTable();
		DoQuestCheckDelay("Saga_HelenaRomantic_1", 10.0);
	}
	else if (sQuestName == "Saga_HelenaRomantic_1") // в таверне
	{
		DoQuestReloadToLocation("PortRoyal_tavern_upstairs", "quest", "quest4", "");
		sld = characterFromId("Helena");
		ChangeCharacterAddressGroup(sld, "PortRoyal_tavern_upstairs", "quest", "quest3");
		DoQuestCheckDelay("Saga_HelenaRomantic_2", 1.3);
	}
	else if (sQuestName == "Saga_HelenaRomantic_2") // акт второй
	{
		SetMusic("music_romantic");
		ChangeShowIntarface();
		locCameraRotateAroundHero(0.0, 1.5, 0.0, 0.005, 0.0, 1.5, 0.0, 850);
		Pchar.FuncCameraFly = "";
		DoQuestCheckDelay("Saga_HelenaRomantic_3", 14.0);
	}
	else if (sQuestName == "Saga_HelenaRomantic_3") // третий... теперь ГГ как честный человек обязан жениться
	{
		pchar.GenQuest.FrameLockEsc = true;
		SetLaunchFrameFormParam("", "", 0, 16);
		SetLaunchFrameFormPic("loading\inside\censored1.tga");
		PlayStereoSound("sex\sex7.wav");
		LaunchFrameForm();
		DoQuestCheckDelay("Saga_HelenaRomantic_4", 16.0);
		if (IsEquipCharacterByArtefact(pchar, "totem_03"))     
		{
			AddCharacterHealth(pchar, 12);
			AddCharacterMaxHealth(pchar, 2.0);
		}
		else 
		{
			AddCharacterHealth(pchar, 6);
			AddCharacterMaxHealth(pchar, 1.0);
		}
		LAi_SetCurHPMax(pchar);
	}
	else if (sQuestName == "Saga_HelenaRomantic_4") // четвертый...
	{
		locCameraResetState();
		EndQuestMovie();
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Helena");
		sld.dialog.currentnode = "happy";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "Saga_HelenaRomantic_5") // пятый - на улицы
	{
		bDisableCharacterMenu = false; // лоченые интерфейсы
		InterfaceStates.Buttons.Save.enable = true; // разрешить сохраняться
		DeleteAttribute(pchar, "GenQuest.MusicContinue");
		sld = characterFromId("Helena");
		sld.dialog.currentnode = "Helena_officer";
		DeleteAttribute(sld, "HalfImmortal"); // халява закончилась
		DeleteAttribute(sld, "CompanionDisable");
		SetCharacterRemovable(sld, true);
		LAi_SetOfficerType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		DoQuestReloadToLocation("PortRoyal_town", "reload", "reload1", "");
		AddQuestRecord("Testament", "13");
		CloseQuestHeader("Testament");
		// если выбрал не Мэри - закрываем к ней доступ
		if (pchar.questTemp.LSC.Mary == "alive")
		{
			for (i = 0; i <= 3; i++)
			{
				LocatorReloadEnterDisable("LostShipsCity_town", "reload6" + i, true); // закрываем вход к Мэри
			}
			pchar.questTemp.LSC.Mary = "fail";
			RemoveItems(pchar, "key_mary", 1); // удалить ключ Мэри
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait"); // стираем атрибут общения с Мэри
		}
	}
	// ------------------------------------ провалы Саги -------------------------------------------------
	else if (sQuestName == "Saga_FailCenturion") // утопили Центурион - Данни и Натана в Марун-Таун
	{
		chrDisableReloadToLocation = false; // открыть локацию
		sld = characterFromId("Danielle");
		sld.dialog.currentnode = "marun_town";
		sld.greeting = "danny_2";
		ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
		LAi_SetStayType(sld);
		sld = characterFromId("Nathaniel");
		sld.model = "Hawk_2";
		Characters_RefreshModel(sld); // наверно не нужно
		sld.greeting = "nathaniel_2";
		sld.dialog.currentnode = "marun_town";
		ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
		LAi_SetHuberType(sld);
		LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
	}
	//--------------------------- встроенный мини-квест Корабль главы братства ---------------------------
	else if (sQuestName == "AlexClock_BandosDie")
	{
		LAi_group_Delete("EnemyFight");
		if (CheckCharacterItem(pchar, "alexs_chest")) DoQuestFunctionDelay("AlexClock_FindChest", 0.5);
		else
		{
			pchar.quest.AlexClock_Find.win_condition.l1 = "item";
			pchar.quest.AlexClock_Find.win_condition.l1.item = "alexs_chest";
			pchar.quest.AlexClock_Find.function = "AlexClock_FindChest";
		}
	}
	// ------------------------------- отношения с девушками-героинями Саги ------------------------------
	else if (sQuestName == "cabin_sex_go") // Sinistra катсцена с поцелуями
	{
		DialogExit();
		chrDisableReloadToLocation = true; // закрыть локацию
		if (Get_My_Cabin() == "My_Cabin_Huge")
		{
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			DeleteAllOfficersFromLocation();
			LAi_FadeLong("HelenaMary_HugeCabin_LoveKiss", "");
		}
		if (Get_My_Cabin() == "My_Cabin" || Get_My_Cabin() == "My_CabineFDM")
		{
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			DeleteAllOfficersFromLocation();
			LAi_FadeLong("HelenaMary_BigCabin_LoveKiss", "");
		}
		if (Get_My_Cabin() == "My_Cabin_Medium2")
		{
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			DeleteAllOfficersFromLocation();
			LAi_FadeLong("HelenaMary_NormalCabin_LoveKiss", "");
		}
		if (Get_My_Cabin() == "My_Cabin_Medium")
		{
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			DeleteAllOfficersFromLocation();
			LAi_FadeLong("HelenaMary_MediumCabin_LoveKiss", "");
		}
		if (Get_My_Cabin() == "My_Cabin_Small")
		{
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			DeleteAllOfficersFromLocation();
			LAi_FadeLong("HelenaMary_SmallCabin_LoveKiss", "");
		}
	}
	else if (sQuestName == "HelenaMary_HugeCabin_LoveKiss") // Огромная каюта
	{
		// if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
		TeleportCharacterToPosAy(pchar, -0.40, 10.00, 4.60, -1.50);
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "kiss", "1", 16.5);
		sld = characterFromId(pchar.quest.sex_partner);
		DoQuestCheckDelay("MaryHelena_LoveSex_New", 15.0);
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		TeleportCharacterToPosAy(sld, -1.00, 10.00, 4.60, 1.50);
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "kiss", "1", 16.5);
		locCameraFromToPos(1.64, 11.53, 1.81, true, -0.92, 9.78, 5.16);
		DoQuestCheckDelay("HelenaMary_HugeCabin_LoveKiss_2", 6.5);
		DoQuestCheckDelay("HelenaMary_HugeCabin_LoveKiss_3", 12.0);
	}
	else if (sQuestName == "HelenaMary_HugeCabin_LoveKiss_2")
	{
		locCameraFromToPos(-1.99, 11.43, 5.86, true, 3.00, 9.78, 1.58);
	}
	else if (sQuestName == "HelenaMary_HugeCabin_LoveKiss_3")
	{
		locCameraFromToPos(-2.33, 11.08, 2.93, true, 1.14, 10.28, 5.84);
	}
	else if (sQuestName == "HelenaMary_BigCabin_LoveKiss") // Большая каюта
	{
		// if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
		TeleportCharacterToPosAy(pchar, -1.30, 20.00, -1.10, 3.00);
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "kiss", "1", 9.5);
		sld = characterFromId(pchar.quest.sex_partner);
		DoQuestCheckDelay("MaryHelena_LoveSex_New", 9.5);
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		TeleportCharacterToPosAy(sld, -1.30, 20.00, -1.70, 0.00);
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "kiss", "1", 9.5);
		locCameraFromToPos(1.76, 21.32, -3.48, true, -3.14, 19.16, 0.27);
		DoQuestCheckDelay("HelenaMary_BigCabin_LoveKiss_2", 6.5);
	}
	else if (sQuestName == "HelenaMary_BigCabin_LoveKiss_2")
	{
		locCameraFromToPos(-0.70, 21.85, -3.30, true, -1.57, 19.40, 1.43);
	}
	else if (sQuestName == "HelenaMary_NormalCabin_LoveKiss") // Нормальная каюта
	{
		// if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
		TeleportCharacterToPosAy(pchar, 1.50, 2.14, -3.80, -1.50);
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "kiss", "1", 8.5);
		sld = characterFromId(pchar.quest.sex_partner);
		DoQuestCheckDelay("MaryHelena_LoveSex_New", 8.5);
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		TeleportCharacterToPosAy(sld, 0.90, 2.14, -3.80, 1.50);
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "kiss", "1", 8.5);
		locCameraFromToPos(-0.44, 3.57, -0.59, true, 1.76, 1.65, -5.05);
		DoQuestCheckDelay("HelenaMary_NormalCabin_LoveKiss_2", 4.5);
	}
	else if (sQuestName == "HelenaMary_NormalCabin_LoveKiss_2")
	{
		locCameraFromToPos(0.07, 3.32, -2.69, true, 1.92, 2.10, -4.31);
	}
	else if (sQuestName == "HelenaMary_MediumCabin_LoveKiss") // Средняя каюта
	{
		// if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
		TeleportCharacterToPosAy(pchar, -0.55, 6.06, 1.65, -1.50);
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "kiss", "1", 8.5);

		sld = characterFromId(pchar.quest.sex_partner);
		DoQuestCheckDelay("MaryHelena_LoveSex_New", 8.5);

		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		TeleportCharacterToPosAy(sld, -1.15, 6.06, 1.65, 1.50);
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "kiss", "1", 8.5);
		locCameraFromToPos(-2.03, 7.59, -0.83, true, 0.01, 6.00, 3.28);
		DoQuestCheckDelay("HelenaMary_MediumCabin_LoveKiss_2", 4.5);
	}
	else if (sQuestName == "HelenaMary_MediumCabin_LoveKiss_2")
	{
		locCameraFromToPos(-1.80, 7.03, 3.33, true, 0.85, 6.25, -0.85);
	}
	else if (sQuestName == "HelenaMary_SmallCabin_LoveKiss") // Маленькая каюта
	{
		// if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
		TeleportCharacterToPosAy(pchar, 1.20, 3.00, -1.40, 3.00);
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "kiss", "1", 7.5);
		sld = characterFromId(pchar.quest.sex_partner);
		DoQuestCheckDelay("MaryHelena_LoveSex_New", 7.5);
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		TeleportCharacterToPosAy(sld, 1.20, 3.00, -2.00, 0.00);
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "kiss", "1", 7.5);
		locCameraFromToPos(-0.55, 4.42, -2.84, true, 2.06, 2.82, -2.00);
	}
	else if (sQuestName == "MaryHelena_LoveSex_New") // секс с Элен
	{
		EndQuestMovie();
		bDisableCharacterMenu = false;
		LAi_SetPlayerType(pchar);
		locCameraTarget(PChar);
		locCameraFollow();
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
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		LAi_ActorFollow(sld, pchar, "", -1);
		LAi_SetOfficerType(sld);
		sld.Dialog.CurrentNode = "sex_after";

		if (pchar.quest.sex_partner == "Mary")
		{
			if (CheckAttribute(pchar, "questTemp.PZ_MaryRazgovorOBordeli")) sld.Dialog.CurrentNode = "PZ_MaryRazgovorOBordeli_Bad_17";
		}
		
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaSnovaOfficer")) sld.Dialog.CurrentNode = "PZ_DevushkaSnovaOfficer_Dialog1";
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
			pchar.quest.Mary_giveme_sex.over = "yes"; // снять прерывание
			pchar.quest.Mary_giveme_sex1.over = "yes"; // снять прерывание лесник.
		}
	}
	else if (sQuestName == "Helena_LoveSex") // Классический вариант
	{
		SetLaunchFrameFormParam("", "", 0, 15);
		SetLaunchFrameFormPic("loading\inside\censored1.tga");
		PlayStereoSound("sex\sex" + (rand(9) + 1) + ".wav");
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 3, 10);
		RecalculateJumpTable();
		if (IsEquipCharacterByArtefact(pchar, "totem_03"))     
		{
			AddCharacterHealth(pchar, 12);
			AddCharacterMaxHealth(pchar, 2.0);
		}
		else 
		{
			AddCharacterHealth(pchar, 6);
			AddCharacterMaxHealth(pchar, 1.0);
		} 
		LAi_SetCurHPMax(pchar);
	}
	else if (sQuestName == "Mary_LoveSex") // Классический вариант
	{
		SetLaunchFrameFormParam("", "", 0, 15);
		SetLaunchFrameFormPic("loading\inside\censored1.tga");
		PlayStereoSound("sex\sex" + (rand(9) + 1) + ".wav");
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 3, 10);
		RecalculateJumpTable();
		if (IsEquipCharacterByArtefact(pchar, "totem_03"))     
		{
			AddCharacterHealth(pchar, 24);
			AddCharacterMaxHealth(pchar, 2.0);
		}
		else 
		{
			AddCharacterHealth(pchar, 12);
			AddCharacterMaxHealth(pchar, 1.0);
		}
		LAi_SetCurHPMax(pchar);
		pchar.quest.Mary_giveme_sex.over = "yes"; // снять прерывание
		pchar.quest.Mary_giveme_sex1.over = "yes"; // снять прерывание лесник.
	}
	// belamour фортуна для додсона -->
	else if (sQuestName == "SharkFrigateToTown")
	{ 
		sld = characterFromId("Dodson");
		ChangeCharacterAddressGroup(sld, "Pirates_town", "reload", "reload3_back");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "reload", "reload1_back","SharkFrigateTalk", -1);
		LAi_SetActorType(pchar);
		LAi_ActorFollow(pchar, sld, "", -1);
	}
	else if (sQuestName == "SharkFrigateTalk")
	{ 
		sld = characterFromId("Dodson");
		sld.dialog.currentnode = "check_out_my_frigate_02";
		Lai_SetPlayerType(pchar);
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "SharkFrigateEnd")
	{ 
		sld = characterFromId("Dodson");
		sld.dialog.currentnode = "first time";
		ChangeCharacterAddressGroup(sld, "Pirates_townhall", "sit", "sit1");
		LAi_SetHuberType(sld);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
		chrDisableReloadToLocation = false;
		bDisableFastReload = false;
		if(CheckAttribute(pchar,"questTemp.SharkGoldFleet.KGBB")) SetTimerCondition("SharkGoldFleet", 0, 0, 30, false);
	}
	// <-- Фортуна
	// belamour legendary edition на пару с Акулой -->
	else if (sQuestName == "SharkGoldFleet")
	{ 
		pchar.questTemp.SharkGoldFleet = "toDodson";
	}
	else if (sQuestName == "SGF_toUsurer")
	{ 
		sld = characterFromId("PortoBello_Portman");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "goto", "goto2","SGF_MCtoSit", -1);
	}
	else if (sQuestName == "SGF_MCtoSit")
	{ 
		ChangeCharacterAddressGroup(pchar, pchar.location, "sit", "sit1");
		/* if(CheckAttribute(pchar, "IsMushketer"))
		{
			SetMainCharacterToMushketer("", false);
		} */
		LAi_SetSitType(pchar);
		DoQuestFunctionDelay("SGF_MCread", 3.0);
	}
	else if (sQuestName == "SGF_UsurertoLoc3")
	{ 
		sld = characterFromId("PortoBello_Portman");
		LAi_ActorGoToLocator(sld, "goto", "goto1","SGF_UsurerSit", -1);
	}
	else if (sQuestName == "SGF_UsurerSit")
	{ 
		sld = characterFromId("PortoBello_Portman");
		ChangeCharacterAddressGroup(sld, pchar.location, "sit", "sit1");
		sld.dialog.currentnode = "SharkGoldFleet_18";
		LAi_SetHuberType(sld);
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}
	else if (sQuestName == "SGF_atVanHatoTalk")
	{ 
		chrDisableReloadToLocation = true;
		sld = characterFromId("Dodson_GF");
		sld.dialog.currentnode = "SharkGoldFleet_34";
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "SGF_SharkToIT")
	{
		sld = characterFromId("Dodson_GF");
		chrDisableReloadToLocation = false;
		RemoveCharacterCompanion(pchar, sld);
		sld.lifeDay = 0;
		LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
		LAi_LocationFightDisable(&Locations[FindLocation("Shore22")], false);
		DeleteAttribute(&locations[FindLocation("Shore22")],"DisableEncounters");
	}
	//<-- на пару с Акулой
	
	// Sinistra катсцена с поцелуями с проституткой в Марун-Тауне
	else if (sQuestName == "MarunFuckGirl") {
		locCameraFromToPos(-0.64, 1.72, -0.90, true, 1.53, -0.20, -3.08);
		TeleportCharacterToPosAy(pchar, 0.10, 0.00, -1.50, 3.00);
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "kiss", "1", 7.5);
		
		sld = characterFromId("MarunFuckGirl");
		TeleportCharacterToPosAy(sld, 0.10, 0.00, -2.10, 0.00);
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "kiss", "1", 7.5);
		
		DoQuestCheckDelay("MarunFuckGirl_2", 2.9);
		DoQuestCheckDelay("MarunFuckGirl_3", 7.5);
	}
	
	else if (sQuestName == "MarunFuckGirl_2") {
		locCameraFromToPos(-0.92, 1.57, -2.40, true, 2.14, -0.20, -0.37);
	}
	
	else if (sQuestName == "MarunFuckGirl_3") {
		EndQuestMovie();
		locCameraTarget(PChar);
		locCameraFollow();
		LAi_SetPlayerType(pchar);
		ChangeCharacterAddressGroup(pchar, PChar.location, "quest", "quest4");
		sld = characterFromId("MarunFuckGirl");
		LAi_SetStayType(sld);
		sld.lifeday = 0;
		ChangeCharacterAddressGroup(sld, PChar.location, "quest", "quest3");
		sld.dialog.currentnode = "MarunFuckGirl_3";
		
		SetLaunchFrameFormParam("", "", 0, 15);
		SetLaunchFrameFormPic("loading\inside\censored1.tga");
		PlayStereoSound("sex\sex"+(rand(9)+1)+".wav");
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 3, 10); //крутим время
		RecalculateJumpTable();
		LAi_SetCurHPMax(pchar);
		if(IsEquipCharacterByArtefact(pchar, "totem_03"))
		{
			AddCharacterHealth(pchar, 12);
			AddCharacterMaxHealth(pchar, 2.0);
		}
		else 
		{
			AddCharacterHealth(pchar, 6);
			AddCharacterMaxHealth(pchar, 1.0);
		}
	}	
	
	else if (sQuestName == "MarunFuckGirl_4") {
		if (CharacterIsAlive("MarunFuckGirl"))
		{
			sld = characterFromId("MarunFuckGirl");
			sld.lifeday = 0;
		}
		DeleteAttribute(pchar, "GenQuest.MaruntownSex");
		DeleteAttribute(pchar, "GenQuest.MaruntownSex2");
		LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", true); //закрыть комнату
	}
	else
	{
		condition = false;
	}
	
	return condition;
}
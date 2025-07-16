/// Jason ----------------------------------------------------------- На службе Отечеству ------------------------------------------------------------------
// ---------------------------------------------------------- задание 1 ---------------------------------------------------------------
void Patria_SetInspector() // ставим инспектора
{
	sld = GetCharacter(NPC_GenerateCharacter("Noel", "Boss_1", "man", "man", 25, FRANCE, -1, false, "officer"));
	FantomMakeCoolFighter(sld, 25, 80, 80, "blade_17", "pistol5", "bullet", 120);
	sld.Dialog.Filename = "Quest\Patria_NPC.c";
	sld.dialog.currentnode = "noel";
	sld.name = StringFromKey("Patria_1");
	sld.lastname = StringFromKey("Patria_2");
	sld.greeting = "noel_1";
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
	LAi_SetActorType(sld);
}

void Patria_SetEcliaton() // ставим Эклятон
{
	// письмо
	GiveItem2Character(pchar, "Reserve_item_01");
	ref itm = ItemsFromID("Reserve_item_01");
	itm.picIndex = 11;
	itm.picTexture = "ITEMS_34";
	itm.price = 0;
	itm.Weight = 0.1;
	// Эклятон
	sld = GetCharacter(NPC_GenerateCharacter("Ecliaton_Cap", "Off_Fra_Z", "man", "man", 40, FRANCE, -1, true, "officer"));
	sld.Ship.Type = GenerateShipHand(sld, SHIP_LSHIP_FRA, 42, 11250, 742, 9900, 250000, 12.85, 32.5, 0.4);
	sld.Ship.name = StringFromKey("Patria_3");
	SetBaseShipData(sld);
	sld.Ship.Cannons.Type = CANNON_TYPE_CULVERINE_LBS36;
	FantomMakeCoolFighter(sld, 40, 100, 100, "blade_17", "pistol4", "bullet", 250);
	sld.name = StringFromKey("Patria_4");
	sld.lastname = StringFromKey("Patria_5");
	sld.Dialog.Filename = "Quest\Patria_NPC.c";
	sld.DeckDialogNode = "ecliaton_cap";
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.reputation = 80;
	sld.alignment = "good";
	SetSelfSkill(sld, 100, 90, 80, 100, 90);
	SetShipSkill(sld, 95, 100, 100, 100, 100, 100, 100, 100, 70);
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Troopers");
	SetCharacterPerk(sld, "LongRangeGrappling");
	SetCharacterPerk(sld, "GrapplingProfessional");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "BasicBattleState");
	SetCharacterPerk(sld, "AdvancedBattleState");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "Carpenter");
	SetCharacterPerk(sld, "Builder");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "WindCatcher");
	SetCharacterPerk(sld, "SailsMan");
	SetCharacterPerk(sld, "SailingProfessional");
	SetCharacterPerk(sld, "Doctor1");
	SetCharacterPerk(sld, "Doctor2");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.AlwaysSandbankManeuver = true;
	Character_SetAbordageEnable(sld, false); // нельзя абордировать
	sld.Tasks.CanBoarding = false; // запрет идти на абордаж - дубль
	sld.Tasks.CanChangeShipAfterBoarding = false; // запрет меняться кораблями - дубль
	sld.Abordage.Enable = false;
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable = true; 
	sld.SeaBoss = 0.5; // получает на 50% меньше урона корпусу
	RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;
	UpgradeShipParameter(sld, "SpeedRate");//апгрейдить скорость
	UpgradeShipParameter(sld, "TurnRate");//маневренность
	sld.Ship.Mode = "war";
	SetCrewQuantityFull(sld);
	sld.ship.Crew.Morale = 100;
	sld.Ship.Crew.Exp.Sailors = 100;
	sld.Ship.Crew.Exp.Cannoners = 100;
	sld.Ship.Crew.Exp.Soldiers = 100;
	SetCharacterGoods(sld, GOOD_BALLS, 6000);
	SetCharacterGoods(sld, GOOD_GRAPES, 2000);
	SetCharacterGoods(sld, GOOD_KNIPPELS, 2000);
	SetCharacterGoods(sld, GOOD_BOMBS, 5000);
	SetCharacterGoods(sld, GOOD_FOOD, 4000);
	SetCharacterGoods(sld, GOOD_POWDER, 12000);
	SetCharacterGoods(sld, GOOD_WEAPON, 900);
	SetCharacterGoods(sld, GOOD_MEDICAMENT, 900);
	SetCharacterGoods(sld, GOOD_RUM, 200);
	SetCharacterGoods(sld, GOOD_PLANKS, 100);
	SetCharacterGoods(sld, GOOD_SAILCLOTH, 100);
	Group_AddCharacter("Ecliaton_group", "Ecliaton_Cap");
	Group_SetGroupCommander("Ecliaton_group", "Ecliaton_Cap");
	Group_SetAddress("Ecliaton_group", "Nevis", "quest_ships", "quest_ship_1");
	Group_SetTaskNone("Ecliaton_group");
	Group_LockTask("Ecliaton_group");
	// закрыть выход в море
	bQuestDisableMapEnter = true;
	pchar.GenQuest.MapClosedNoBattle = true; 
}

void Patria_AddEcliaton() // присоединяем Эклятон
{
	sld = characterFromId("Ecliaton_Cap");
	SetCharacterRemovable(sld, false);
	sld.CompanionEnemyEnable = false; //всегда друзья
	SetCompanionIndex(pchar, -1, sti(sld.index));
	sld.loyality = MAX_LOYALITY;
	SetFunctionTimerCondition("Patria_SanJoseOver", 0, 0, 30, false); // таймер
	AddQuestRecord("Patria", "2");
	bQuestDisableMapEnter = false;//открыть карту
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	pchar.quest.Patria_SanJoseAttack.win_condition.l1 = "location";
	pchar.quest.Patria_SanJoseAttack.win_condition.l1.location = "Trinidad";
	pchar.quest.Patria_SanJoseAttack.function = "Patria_SanJoseAttack";
	int i = FindColony("PortSpein");
	colonies[i].DontSetShipInPort = true;
	pchar.questTemp.Patria.Ecliaton = "true";
	// прерывание на потерю Эклятона
	pchar.quest.Patria_EcliatonFail.win_condition.l1 = "NPC_Death";
	pchar.quest.Patria_EcliatonFail.win_condition.l1.character = "Ecliaton_Cap";
	pchar.quest.Patria_EcliatonFail.function = "Patria_EcliatonFail";
	// удаление группы Эклятона, иначе клон-призрак
	pchar.quest.Patria_EcliatonDelGroup.win_condition.l1 = "ExitFromSea";
	pchar.quest.Patria_EcliatonDelGroup.function = "Patria_EcliatonDelGroup";
}

void Patria_EcliatonDelGroup(string qName) // 
{
	Group_DeleteGroup("Ecliaton_group");
}

void Patria_EcliatonFail(string qName) // потеря Эклятона
{
	AddQuestRecord("Patria", "2_1");
	DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
	pchar.questTemp.Patria.Ecliaton_Fail = "true";
}

void Patria_SanJoseOver(string qName) // потратили месяц
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Patria_SanJoseOver.over"))
			DeleteAttribute(pchar,"quest.Patria_SanJoseOver.over");
		NewGameTip(StringFromKey("Patria_6"));
		SetFunctionTimerCondition("Patria_SanJoseOver", 0, 0, 30, false);
		return;
	}
	pchar.quest.Patria_SanJoseAttack.over = "yes";
	if (GetCharacterIndex("Ecliaton_Cap") != -1)
	{
		pchar.quest.Patria_EcliatonFail.over = "yes"; //снять прерывание
		sld = characterFromId("Ecliaton_Cap");
		sld.ShipHideImmortal = 1000; // непотопляемый корабль
		RemoveCharacterCompanion(pchar, sld);
		sld.DontDeskTalk = true;
		sld.lifeday = 0;
	}
	RemoveItems(pchar, "patent_fra", 1);
	ChangeCharacterComplexReputation(pchar, "nobility", -10);
	ChangeCharacterComplexReputation(pchar, "authority", -5);
	ChangeCharacterNationReputation(pchar, FRANCE, -10);
	pchar.questTemp.Patria = "fail";
	AddQuestRecord("Patria", "3");
	CloseQuestHeader("Patria");
	DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
	int i = FindColony("PortSpein");
	DeleteAttribute(colonies[i], "DontSetShipInPort");
	DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
}

void Patria_SanJoseAttack(string qName) // вышли у Тринидада
{
	pchar.quest.Patria_SanJoseOver.over = "yes"; // снять таймер
	AddQuestRecord("Patria", "4");
	bQuestDisableMapEnter = true;//закрыть карту
	Island_SetReloadEnableGlobal("Trinidad", false);//закрыть остров
	sld = CharacterFromID("PortSpein Fort Commander");
	Character_SetAbordageEnable(sld, false); // неабордируемый форт
	pchar.questTemp.Patria.SanJoseAttack = "true";
	if (pchar.nation != FRANCE) Flag_FRANCE();
	pchar.DisableChangeFlagMode = true; //закрываем Флаг
}

void Patria_SanJoseFortDestroyed() // форт Сан-Хосе разрушен
{
	Log_Info(StringFromKey("Patria_7"));
	Island_SetReloadEnableGlobal("Trinidad", true); //открыть остров
	pchar.GenQuest.MapClosedNoBattle = true;
	AddQuestRecord("Patria", "5");
	pchar.quest.Patria_SanJoseMayak.win_condition.l1 = "location";
	pchar.quest.Patria_SanJoseMayak.win_condition.l1.location = "Mayak1";
	pchar.quest.Patria_SanJoseMayak.function = "Patria_SanJoseMayak";
	pchar.GenQuest.Hunter2Pause = true;
}

void Patria_SanJoseMayak(string qName) // на маяке Тринидада
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation("Mayak1")], true);
	for (int i=1; i<=11; i++)
	{
		if (i > 8) // мушкетеры, 3 шт
		{
			sld = GetCharacter(NPC_GenerateCharacter("Patria_SanJoseSoldier_"+i, "mush_fra_"+(i-8), "man", "mushketer", 30, FRANCE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, 30, 80, 80, "", "mushket1", "cartridge", 150);
			LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
		}
		else
		{
				sld = GetCharacter(NPC_GenerateCharacter("Patria_SanJoseSoldier_"+i, "sold_fra_"+i, "man", "man", 30, FRANCE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 30, 60, 60, LinkRandPhrase("blade_11","blade_12","blade_13"), "pistol1", "bullet", 150);
		}
		ChangeCharacterAddressGroup(sld, "Mayak1", "goto", "goto"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_CharacterDisableDialog(sld);
	}
	DoQuestFunctionDelay("Patria_SanJoseMayakSpanish", 5.0);
}

void Patria_SanJoseMayakSpanish() // пришли испанцы для переговоров
{
	for (int i=1; i<=4; i++)
	{
		if (i == 1) // офицер
		{
			sld = GetCharacter(NPC_GenerateCharacter("Patria_SanJoseSpanish_"+i, "off_spa_4", "man", "man", 30, SPAIN, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, 30, 60, 60, "blade_20", "pistol5", "bullet", 150);
			sld.Dialog.Filename = "Quest\Patria_NPC.c";
			sld.dialog.currentnode = "SanJoseSpanish";
		}
		else
		{
				sld = GetCharacter(NPC_GenerateCharacter("Patria_SanJoseSpanish_"+i, "sold_spa_"+i, "man", "man", 30, SPAIN, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 30, 60, 60, LinkRandPhrase("blade_11","blade_12","blade_13"), "pistol1", "bullet", 150);
				LAi_CharacterDisableDialog(sld);
		}
		LAi_SetImmortal(sld, true);
		ChangeCharacterAddressGroup(sld, "Mayak1", "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void Patria_SanJoseMayakSpanishGo() // испанцы уходят на сутки
{
	for (int i=1; i<=4; i++)
	{
		sld = CharacterFromID("Patria_SanJoseSpanish_"+i);
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 12.0);
	}
	DoQuestFunctionDelay("Patria_SanJoseMayakSpanishWait", 13.0);
}

void Patria_SanJoseMayakSpanishWait() // крутим сутки
{
	SetLaunchFrameFormParam(StringFromKey("Patria_8"), "", 0, 5);
	LaunchFrameForm();
	WaitDate("", 0, 0, 1, 0, 10); //крутим время
	RecalculateJumpTable();
	StoreDayUpdate();
	RefreshWeather();
	RefreshLandTime();
	DoQuestFunctionDelay("Patria_SanJoseMayakSpanishReturn", 5.0);
	pchar.GenQuest.Hunter2Pause = true;
}

void Patria_SanJoseMayakSpanishReturn() // испанцы возвращаются
{
	LAi_Fade("", "");
	for (int i=1; i<=4; i++)
	{
		sld = CharacterFromID("Patria_SanJoseSpanish_"+i);
		ChangeCharacterAddressGroup(sld, "Mayak1", "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void Patria_SanJoseMayakSpanishFin() // получили выкуп, уходим
{
	for (int i=1; i<=4; i++)
	{
		sld = CharacterFromID("Patria_SanJoseSpanish_"+i);
		sld.lifeday = 0;
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 7.0);
	}
	for (i=1; i<=11; i++)
	{
		sld = CharacterFromID("Patria_SanJoseSoldier_"+i);
		sld.lifeday = 0;
	}
	AddQuestRecord("Patria", "6");
	DeleteAttribute(pchar, "DisableChangeFlagMode"); // открываем флаг
	pchar.questTemp.Patria = "epizode_1_return";
	SetFunctionTimerCondition("Patria_SanJoseReturnOver", 0, 0, 20, false); // таймер 20 дней на возврат
	SetFunctionTimerCondition("Patria_SanJoseNormal", 0, 0, 7, false); // возврат Сан-Хосе в норму
	LAi_LocationFightDisable(&Locations[FindLocation("Mayak1")], false);
	bQuestDisableMapEnter = false;//открыть карту
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
}

void Patria_SanJoseNormal(string qName) // возврат Сан-Хосе в норму
{
	DeleteAttribute(pchar, "questTemp.Patria.SanJoseAttack");
	sld = CharacterFromID("PortSpein Fort Commander");
	Character_SetAbordageEnable(sld, true); 
	int i = FindColony("PortSpein");
	DeleteAttribute(colonies[i], "DontSetShipInPort");
}

void Patria_SanJoseReturnOver(string qName) // потратили месяц
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Patria_SanJoseReturnOver.over"))
			DeleteAttribute(pchar,"quest.Patria_SanJoseReturnOver.over");
		NewGameTip(StringFromKey("Patria_6"));
		SetFunctionTimerCondition("Patria_SanJoseReturnOver", 0, 0, 20, false);
		return;
	}
	if (GetCharacterIndex("Ecliaton_Cap") != -1)
	{
		pchar.quest.Patria_EcliatonFail.over = "yes"; //снять прерывание
		sld = characterFromId("Ecliaton_Cap");
		sld.ShipHideImmortal = 1000; // непотопляемый корабль
		RemoveCharacterCompanion(pchar, sld);
		sld.DontDeskTalk = true;
		sld.lifeday = 0;
	}
	DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
	RemoveItems(pchar, "patent_fra", 1);
	ChangeCharacterComplexReputation(pchar, "nobility", -10);
	ChangeCharacterComplexReputation(pchar, "authority", -5);
	ChangeCharacterNationReputation(pchar, FRANCE, -10);
	pchar.questTemp.Patria = "fail";
	AddQuestRecord("Patria", "7");
	CloseQuestHeader("Patria");
	DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
	sld = characterFromId("Puancie");
	sld.dialog.currentnode = "First time";
}

// ---------------------------------------------------------- задание 2 ---------------------------------------------------------------
void Patria_VisiterBegin() // отсоединяем Эклятон, присоединяем инспектора
{
	pchar.quest.Patria_EcliatonFail.over = "yes";
	chrDisableReloadToLocation = true;
	sld = characterFromId("Ecliaton_Cap");
	sld.ShipHideImmortal = 1000; // непотопляемый корабль
	RemoveCharacterCompanion(pchar, sld);
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable = true;
	Group_AddCharacter("Ecliaton_group", "Ecliaton_Cap");
	Group_SetGroupCommander("Ecliaton_group", "Ecliaton_Cap");
	Group_SetAddress("Ecliaton_group", "Nevis", "quest_ships", "quest_ship_1");
	Group_SetTaskNone("Ecliaton_group");
	Group_LockTask("Ecliaton_group");
	SetFunctionTimerCondition("Patria_EcliatonRepair", 0, 0, 5, false); // таймер на починку Эклятона
	DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
	sld = characterFromId("Noel");
	sld.dialog.currentnode = "noel_2";
	sld.greeting = "noel_2";
	AddPassenger(pchar, sld, false);//добавить пассажира
	SetCharacterRemovable(sld, false);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	if(bImCasual) NewGameTip(StringFromKey("Patria_9"));
	SetFunctionTimerCondition("Patria_VisiterOver", 0, 0, 62, false); // таймер на все задание
	pchar.quest.Patria_visiter_tortuga.win_condition.l1 = "location";
	pchar.quest.Patria_visiter_tortuga.win_condition.l1.location = "Tortuga_townhall";
	pchar.quest.Patria_visiter_tortuga.function = "Patria_VisiterTortuga";
	pchar.quest.Patria_visiter_portpax.win_condition.l1 = "location";
	pchar.quest.Patria_visiter_portpax.win_condition.l1.location = "PortPax_townhall";
	pchar.quest.Patria_visiter_portpax.function = "Patria_VisiterPortPax";
}

void Patria_EcliatonRepair(string qName) // починка Эклятона
{
	sld = CharacterFromID("Ecliaton_Cap");
	DeleteAttribute(sld, "ship.sails");
    DeleteAttribute(sld, "ship.blots");
    DeleteAttribute(sld, "ship.masts");
	DeleteAttribute(sld, "ship.hulls");
	sld.ship.HP = 9900;
	SetCrewQuantityFull(sld);
	SetCharacterGoods(sld, GOOD_BALLS, 6000);
	SetCharacterGoods(sld, GOOD_GRAPES, 2000);
	SetCharacterGoods(sld, GOOD_KNIPPELS, 2000);
	SetCharacterGoods(sld, GOOD_BOMBS, 5000);
	SetCharacterGoods(sld, GOOD_FOOD, 4000);
	SetCharacterGoods(sld, GOOD_POWDER, 12000);
	SetCharacterGoods(sld, GOOD_WEAPON, 900);
	SetCharacterGoods(sld, GOOD_MEDICAMENT, 900);
	SetCharacterGoods(sld, GOOD_RUM, 200);
	SetCharacterGoods(sld, GOOD_PLANKS, 100);
	SetCharacterGoods(sld, GOOD_SAILCLOTH, 100);
	// чиним орудия
	ref shTo = &RealShips[sti(sld.Ship.Type)];
	ResetShipCannonsDamages(sld);
	shTo.Cannons = 66;
}

void Patria_VisiterOver(string qName) // провал по срокам
{
	pchar.quest.Patria_visiter_tortuga.over = "yes";
	pchar.quest.Patria_visiter_portpax.over = "yes";
	pchar.quest.Patria_visiter_delete.win_condition.l1 = "Location_Type";
	pchar.quest.Patria_visiter_delete.win_condition.l1.location_type = "town";
	pchar.quest.Patria_visiter_delete.function = "Patria_VisiterDelete";
	pchar.questTemp.Patria.Visiter_Late = "true";
}

void Patria_VisiterDelete(string qName) // провал по срокам
{
	if (pchar.location == "Charles_town" && CheckAttribute(pchar, "questTemp.Patria.Tortuga") && CheckAttribute(pchar, "questTemp.Patria.PortPax")) // если все выполнил, то прощаем
	{
		return;
	}
	sld = characterFromId("Noel");
	RemovePassenger(pchar, sld);
	Log_Info(StringFromKey("Patria_10"));
	RemoveItems(pchar, "patent_fra", 1);
	ChangeCharacterComplexReputation(pchar, "nobility", -5);
	ChangeCharacterComplexReputation(pchar, "authority", -5);
	ChangeCharacterNationReputation(pchar, FRANCE, -5);
	pchar.questTemp.Patria = "fail";
	AddQuestRecord("Patria", "10");
	CloseQuestHeader("Patria");
	DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
}

void Patria_VisiterTortuga(string qName) // в резиденциях
{
	pchar.quest.Patria_visiter_portpax.over = "yes";
	sld = characterFromId("Noel");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "goto", "governor1", "", -1);
}

void Patria_VisiterTortugaBack(string qName) // 
{
	AddQuestRecord("Patria", "12");
	LocatorReloadEnterDisable("Tortuga_town", "reload3_back", false);
	sld = characterFromId("Noel");
	sld.dialog.currentnode = "noel_7";
	LAi_SetStayType(sld);
}

void Patria_VisiterTortugaSail()
{
	chrDisableReloadToLocation = true;
	sld = characterFromId("Noel");
	AddPassenger(pchar, sld, false);//добавить пассажира
	SetCharacterRemovable(sld, false);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
	pchar.questTemp.Patria.Tortuga = "true"; // посетили Тортугу
	if (!CheckAttribute(pchar, "questTemp.Patria.PortPax"))
	{
		pchar.quest.Patria_visiter_portpax.win_condition.l1 = "location";
		pchar.quest.Patria_visiter_portpax.win_condition.l1.location = "PortPax_townhall";
		pchar.quest.Patria_visiter_portpax.function = "Patria_VisiterPortPax";
	}
	if (CheckAttribute(pchar, "questTemp.Patria.Tortuga") && CheckAttribute(pchar, "questTemp.Patria.PortPax"))
	{
		AddQuestRecord("Patria", "14");
		pchar.quest.Patria_visiter_return.win_condition.l1 = "location";
		pchar.quest.Patria_visiter_return.win_condition.l1.location = "Nevis";
		pchar.quest.Patria_visiter_return.function = "Patria_VisiterSintMaarten";
	}
}

void Patria_VisiterPortPax(string qName) // в резиденциях 
{
	pchar.quest.Patria_visiter_tortuga.over = "yes";
	sld = characterFromId("Noel");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "goto", "governor1", "", -1);
}

void Patria_VisiterPortPaxBack(string qName) // 
{
	AddQuestRecord("Patria", "12");
	LocatorReloadEnterDisable("PortPax_town", "reload3_back", false);
	sld = characterFromId("Noel");
	sld.dialog.currentnode = "noel_11";
	LAi_SetStayType(sld);
}

void Patria_VisiterPortPaxSail()
{
	chrDisableReloadToLocation = true;
	sld = characterFromId("Noel");
	AddPassenger(pchar, sld, false);//добавить пассажира
	SetCharacterRemovable(sld, false);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
	pchar.questTemp.Patria.PortPax = "true"; // посетили Эспаньолу
	if (!CheckAttribute(pchar, "questTemp.Patria.Tortuga"))
	{
		pchar.quest.Patria_visiter_tortuga.win_condition.l1 = "location";
		pchar.quest.Patria_visiter_tortuga.win_condition.l1.location = "Tortuga_townhall";
		pchar.quest.Patria_visiter_tortuga.function = "Patria_VisiterTortuga";
	}
	if (CheckAttribute(pchar, "questTemp.Patria.Tortuga") && CheckAttribute(pchar, "questTemp.Patria.PortPax"))
	{
		AddQuestRecord("Patria", "14");
		pchar.quest.Patria_visiter_return.win_condition.l1 = "location";
		pchar.quest.Patria_visiter_return.win_condition.l1.location = "Nevis";
		pchar.quest.Patria_visiter_return.function = "Patria_VisiterSintMaarten";
	}
}

void Patria_VisiterSintMaarten(string qName) // разговор на палубе
{
	pchar.quest.Patria_VisiterOver.over = "yes"; // снять таймер
	bQuestDisableMapEnter = true;//закрыть карту
	Island_SetReloadEnableGlobal("Nevis", false);
	pchar.GenQuest.MapClosedNoBattle = true; 
	DoQuestFunctionDelay("Patria_VisiterToCabin", 2.0);
}

void Patria_VisiterToCabin(string qName) // в каюту
{
	Sea_CabinStartNow();
	DoQuestFunctionDelay("Patria_VisiterInCabin", 1.8);
}

void Patria_VisiterInCabin(string qName) // в каюту
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = characterFromId("Noel");
	sld.dialog.currentnode = "noel_13";
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Patria_VisiterFin(string qName) // у Пуанси
{
	sld = characterFromId("Noel");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "goto", "goto4", "", -1);
	RemovePassenger(pchar, sld);
}

//----------------------------------------------------------- задание 3 -------------------------------------------------------------
void Patria_PortPaxBegin() // снова присоединяем Эклятон
{
	bQuestDisableMapEnter = false;//открыть карту
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	sld = characterFromId("Ecliaton_Cap");
	DeleteAttribute(sld, "ShipHideImmortal");
	SetCharacterRemovable(sld, false);
	sld.CompanionEnemyEnable = false; //всегда друзья
	SetCompanionIndex(pchar, -1, sti(sld.index));
	sld.loyality = MAX_LOYALITY;
	pchar.questTemp.Patria.Ecliaton = "true";
	SetFunctionTimerCondition("Patria_PortPaxOver", 0, 0, 30, false); // таймер
	pchar.quest.Patria_PortPaxAttack.win_condition.l1 = "location";
	pchar.quest.Patria_PortPaxAttack.win_condition.l1.location = "Hispaniola2";
	pchar.quest.Patria_PortPaxAttack.function = "Patria_PortPaxAttack";
	// прерывание на потерю Эклятона
	pchar.quest.Patria_EcliatonFail.win_condition.l1 = "NPC_Death";
	pchar.quest.Patria_EcliatonFail.win_condition.l1.character = "Ecliaton_Cap";
	pchar.quest.Patria_EcliatonFail.function = "Patria_EcliatonFail";
	DoQuestFunctionDelay("Patria_EcliatonDelGroup", 1.0); // удалить группу Эклятона
}

void Patria_PortPaxOver(string qName) // опоздание по времени
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Patria_PortPaxOver.over"))
			DeleteAttribute(pchar,"quest.Patria_PortPaxOver.over");
		NewGameTip(StringFromKey("Patria_6"));
		SetFunctionTimerCondition("Patria_PortPaxOver", 0, 0, 30, false);
		return;
	}
	if (GetCharacterIndex("Ecliaton_Cap") != -1)
	{
		pchar.quest.Patria_EcliatonFail.over = "yes"; //снять прерывание
		sld = characterFromId("Ecliaton_Cap");
		sld.ShipHideImmortal = 1000; // непотопляемый корабль
		RemoveCharacterCompanion(pchar, sld);
		sld.DontDeskTalk = true;
		sld.lifeday = 0;
	}
	DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
	RemoveItems(pchar, "patent_fra", 1);
	ChangeCharacterComplexReputation(pchar, "nobility", -10);
	ChangeCharacterComplexReputation(pchar, "authority", -5);
	ChangeCharacterNationReputation(pchar, FRANCE, -10);
	pchar.questTemp.Patria = "fail";
	AddQuestRecord("Patria", "16");
	CloseQuestHeader("Patria");
	DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
}

void Patria_PortPaxAttack(string qName) // ставим испанскую эскадру
{
	// спрячем инспектора
	sld = characterFromId("Noel");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	AddQuestRecord("Patria", "17");
	Island_SetReloadEnableGlobal("Hispaniola2", false); //закрыть остров
	bQuestDisableMapEnter = true;//закрыть карту
	int iShip, iCannon, iRank, iScl;
	Group_FindOrCreateGroup("PatriaPPSeaGroup");
	for (int i=1; i<=4; i++)
	{
		switch (i)
		{
			case 1:
				iRank = 18+MOD_SKILL_ENEMY_RATE*2;
				iScl = 65;
				iShip = SHIP_LINESHIP;
				iCannon = CANNON_TYPE_CANNON_LBS36;
			break;
			
			case 2:
				iRank = 16+MOD_SKILL_ENEMY_RATE*2;
				iScl = 55;
				iShip = SHIP_GALEON_H;
				iCannon = CANNON_TYPE_CANNON_LBS24;
			break;
			
			case 3:
				iRank = 12+MOD_SKILL_ENEMY_RATE*2;
				iScl = 45;
				iShip = SHIP_CORVETTE;
				iCannon = CANNON_TYPE_CULVERINE_LBS18;
			break;
			
			case 4:
				iRank = 12+MOD_SKILL_ENEMY_RATE*2;
				iScl = 45;
				iShip = SHIP_XebekVML;
				iCannon = CANNON_TYPE_CANNON_LBS16;
			break;
		}
		sld = GetCharacter(NPC_GenerateCharacter("PatriaPP_Seacap_"+i, "off_spa_"+(6-i), "man", "man", iRank, SPAIN, -1, true, "quest"));
		FantomMakeCoolSailor(sld, iShip, "", iCannon, iScl, iScl, iScl);
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade_18","blade_19","blade_20"), "pistol5", "bullet", 250);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.cirassId = Items_FindItemIdx("cirass4");
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.AlwaysEnemy = true;
		sld.Coastal_Captain = true;
		sld.AlwaysSandbankManeuver = true;
		sld.Ship.Mode = "war";
		sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*5;
		sld.Ship.Crew.Exp.Sailors = 40+MOD_SKILL_ENEMY_RATE*5;
		sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*5;
		sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*5;
		if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
		if (i < 3) SetRandGeraldSail(sld, SPAIN);
		Group_AddCharacter("PatriaPPSeaGroup", "PatriaPP_Seacap_"+i);
	}
	Group_SetGroupCommander("PatriaPPSeaGroup", "PatriaPP_Seacap_1");
	Group_SetAddress("PatriaPPSeaGroup", "Hispaniola2", "quest_ships", "quest_ship_"+(rand(3)+5));
	Group_SetTaskNone("PatriaPPSeaGroup");
	//Group_LockTask("PatriaPPSeaGroup");
	pchar.quest.Patria_PortPax_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Patria_PortPax_AfterBattle.win_condition.l1.group = "PatriaPPSeaGroup";
	pchar.quest.Patria_PortPax_AfterBattle.function = "Patria_PortPaxAfterBattle";
}

void Patria_PortPaxAfterBattle(string qName) // потопили испанскую эскадру
{
	Group_DeleteGroup("PatriaPPSeaGroup");
	if (MOD_SKILL_ENEMY_RATE < 6)
	{
		bQuestDisableMapEnter = false;
		Island_SetReloadEnableGlobal("Hispaniola2", true);//на остров можно
		AddQuestRecord("Patria", "18");
		pchar.questTemp.Patria = "epizode_3_return";
		DoQuestCheckDelay("sea_victory", 1.5);
	}
    else DoQuestFunctionDelay("Patria_PortPaxNextBattle", 5.0);
}

void Patria_PortPaxNextBattle(string qName) // добавочный ТГ
{
	PlaySound("interface\notebook.wav");
	Log_Info(RandSwear()+StringFromKey("Patria_11"));
	PlaySound("interface\" + LanguageGetLanguage() + "\_EvEnemy0.wav");
	Group_FindOrCreateGroup("PatriaPPSeaGroup1");
	sld = GetCharacter(NPC_GenerateCharacter("PatriaPP_Seacap_add", "off_spa_4", "man", "man", 20+MOD_SKILL_ENEMY_RATE*2, SPAIN, -1, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_GALEON_H, "", CANNON_TYPE_CANNON_LBS24, 65, 65, 65);
	FantomMakeCoolFighter(sld, 20+MOD_SKILL_ENEMY_RATE*2, 65, 65, "blade_19", "pistol5", "bullet", 100);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.cirassId = Items_FindItemIdx("cirass4");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.AlwaysEnemy = true;
	sld.Coastal_Captain = true;
	sld.AlwaysSandbankManeuver = true;
	sld.Ship.Mode = "war";
	sld.ship.Crew.Morale = 50+MOD_SKILL_ENEMY_RATE*5;
	sld.Ship.Crew.Exp.Sailors = 50+MOD_SKILL_ENEMY_RATE*5;
	sld.Ship.Crew.Exp.Cannoners = 50+MOD_SKILL_ENEMY_RATE*5;
	sld.Ship.Crew.Exp.Soldiers = 50+MOD_SKILL_ENEMY_RATE*5;
	SetRandGeraldSail(sld, SPAIN);
	Group_AddCharacter("PatriaPPSeaGroup1", "PatriaPP_Seacap_add");
	Group_SetGroupCommander("PatriaPPSeaGroup1", "PatriaPP_Seacap_add");
	Group_SetTaskAttack("PatriaPPSeaGroup1", PLAYER_GROUP);
	Group_LockTask("PatriaPPSeaGroup1");
	DoQuestFunctionDelay("Patria_PortPaxNextBattleGo", 3.0);
	
	pchar.quest.Patria_PortPax_AfterBattle1.win_condition.l1 = "Group_Death";
	pchar.quest.Patria_PortPax_AfterBattle1.win_condition.l1.group = "PatriaPPSeaGroup1";
	pchar.quest.Patria_PortPax_AfterBattle1.function = "Patria_PortPaxAfterFinBattle";
}

void Patria_PortPaxNextBattleGo(string qName) // 
{
	Sea_LoginGroupCurrentSea("PatriaPPSeaGroup1");
}

void Patria_PortPaxAfterFinBattle(string qName) // потопили добавочный ТГ
{
	Group_DeleteGroup("PatriaPPSeaGroup1");
	bQuestDisableMapEnter = false;
	Island_SetReloadEnableGlobal("Hispaniola2", true);//на остров можно
	AddQuestRecord("Patria", "18");
	pchar.questTemp.Patria = "epizode_3_return";
	DoQuestCheckDelay("sea_victory", 1.5);
}

// ---------------------------------------------------------- задание 4 ---------------------------------------------------------------
void Patria_CureerBegin() // отсоединяем Эклятон, присоединяем флейт
{
	pchar.quest.Patria_EcliatonFail.over = "yes";
	sld = characterFromId("Ecliaton_Cap");
	sld.ShipHideImmortal = 1000; // непотопляемый корабль
	RemoveCharacterCompanion(pchar, sld);
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable = true;
	Group_AddCharacter("Ecliaton_group", "Ecliaton_Cap");
	Group_SetGroupCommander("Ecliaton_group", "Ecliaton_Cap");
	Group_SetAddress("Ecliaton_group", "Nevis", "quest_ships", "quest_ship_1");
	Group_SetTaskNone("Ecliaton_group");
	Group_LockTask("Ecliaton_group");
	SetFunctionTimerCondition("Patria_EcliatonRepair", 0, 0, 5, false); // таймер на починку Эклятона
	DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
	// флейт
	sld = GetCharacter(NPC_GenerateCharacter("Patria_FlautCap", "mercen_13", "man", "man", 20, FRANCE, -1, false, "soldier"));
	FantomMakeCoolSailor(sld, SHIP_FLEUT, "", CANNON_TYPE_CANNON_LBS8, 30, 30, 30);
	FantomMakeCoolFighter(sld, 20, 30, 30, "blade_11", "pistol1", "bullet", 50);
	SetShipSkill(sld, 30, 40, 40, 45, 35, 35, 20, 30, 50);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "trade";
	int iSpace = GetCharacterFreeSpace(sld, GOOD_EBONY);
	Fantom_SetCharacterGoods(sld, GOOD_EBONY, iSpace, 1);
	SetCharacterRemovable(sld, false);
	sld.CompanionEnemyEnable = false; //всегда друзья
	SetCompanionIndex(pchar, -1, sti(sld.index));
	sld.loyality = MAX_LOYALITY;
	// прерывание на потерю флейта
	pchar.quest.Patria_CureerFail.win_condition.l1 = "NPC_Death";
	pchar.quest.Patria_CureerFail.win_condition.l1.character = "Patria_FlautCap";
	pchar.quest.Patria_CureerFail.function = "Patria_CureerFail";
	// таймер на 3 недели и таймер на скоростных ДУ
	SetFunctionTimerCondition("Patria_CureerTimeOver", 0, 0, 15, false);
	SetFunctionTimerCondition("Patria_CureerCreatePirates", 0, 0, 3, false);
	// ставим Стайвесанта
	if (GetCharacterIndex("Stivesant") != -1)
	{
		sld = characterFromId("Stivesant");
	}
	else
	{
		sld = GetCharacter(NPC_GenerateCharacter("Stivesant", "huber_1", "man", "man_B", 35, HOLLAND, -1, false, "quest"));
		FantomMakeSmallSailor(sld, SHIP_GALEON_H, StringFromKey("Patria_12"), CANNON_TYPE_CANNON_LBS24, 100, 100, 100, 100, 100);
		FantomMakeCoolFighter(sld, 35, 90, 90, "blade_15", "pistol5", "bullet", 250);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.name = StringFromKey("Patria_13");
		sld.lastname = StringFromKey("Patria_14");
		sld.greeting = "Stivesant"; 
	}
	sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
	sld.dialog.currentnode = "Stivesant_19";
	LAi_SetHuberType(sld);
	ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "sit", "sit1");
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "goto", "governor1");
}

void Patria_CureerCreatePirates(string qName)//атака ДУ
{
	TraderHunterOnMap(true);
}

void Patria_CureerTimeOver(string qName) // опоздание по времени
{
	pchar.quest.Patria_CureerFail.over = "yes"; //снять прерывание
	if (GetCharacterIndex("Patria_FlautCap") != -1)
	{
		sld = characterFromId("Patria_FlautCap");
		sld.ShipHideImmortal = 200; // непотопляемый корабль
		RemoveCharacterCompanion(pchar, sld);
		sld.DontDeskTalk = true;
		sld.lifeday = 0;
	}
	RemoveItems(pchar, "patent_fra", 1);
	RemoveItems(pchar, "Reserve_item_01", 1);
	ChangeCharacterComplexReputation(pchar, "nobility", -10);
	ChangeCharacterComplexReputation(pchar, "authority", -5);
	ChangeCharacterNationReputation(pchar, FRANCE, -10);
	pchar.questTemp.Patria = "fail";
	AddQuestRecord("Patria", "21");
	CloseQuestHeader("Patria");
	DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
	Patria_StivesantHide();
}

void Patria_CureerFail(string qName) // потеряли флейт
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Patria_CureerFail.over"))
			DeleteAttribute(pchar,"quest.Patria_CureerFail.over");
		NewGameTip(StringFromKey("Patria_6"));
		SetFunctionTimerCondition("Patria_CureerFail", 0, 0, 15, false);
		return;
	}
	pchar.quest.Patria_CureerTimeOver.over = "yes"; //снять таймер
	RemoveItems(pchar, "patent_fra", 1);
	RemoveItems(pchar, "Reserve_item_01", 1);
	ChangeCharacterComplexReputation(pchar, "nobility", -10);
	ChangeCharacterComplexReputation(pchar, "authority", -7);
	ChangeCharacterNationReputation(pchar, FRANCE, -15);
	pchar.questTemp.Patria = "fail";
	AddQuestRecord("Patria", "22");
	CloseQuestHeader("Patria");
	DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
	Patria_StivesantHide();
}

void Patria_StivesantHide() // убираем Стайвесанта
{
	sld = characterFromId("Stivesant");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
	LAi_SetHuberType(sld);
	ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "sit", "sit1");
}

void Patria_StivesantWait(string qName) // Стайвесант возвращается
{
	sld = characterFromId("Stivesant");
	ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "reload", "reload2");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "goto", "goto6", "Patria_StivesantSit", -1);
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
}

void Patria_CureerBackOver(string qName) // опоздание по времени
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Patria_CureerBackOver.over"))
			DeleteAttribute(pchar,"quest.Patria_CureerBackOver.over");
		NewGameTip(StringFromKey("Patria_6"));
		SetFunctionTimerCondition("Patria_CureerBackOver", 0, 0, 31, false);
		return;
	}
	RemoveItems(pchar, "patent_fra", 1);
	RemoveItems(pchar, "Reserve_item_01", 1);
	ChangeCharacterComplexReputation(pchar, "nobility", -10);
	ChangeCharacterComplexReputation(pchar, "authority", -5);
	ChangeCharacterNationReputation(pchar, FRANCE, -10);
	sld = characterFromId("Noel");
	sld.lifeday = 0;
	ChangeCharacterAddressGroup(sld, "none", "", "");
	pchar.questTemp.Patria = "fail";
	AddQuestRecord("Patria", "24");
	CloseQuestHeader("Patria");
	DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
}
// ---------------------------------------------------------- задание 5 ---------------------------------------------------------------
void Patria_SanMartinBaron(string qName) // вестовой Пуанси
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = GetCharacter(NPC_GenerateCharacter("Patria_FraOfficer", "off_fra_1", "man", "man", 25, FRANCE, -1, true, "quest"));
	FantomMakeCoolFighter(sld, 25, 60, 60, "blade_10", "pistol5", "bullet", 100);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.Dialog.Filename = "Quest\Patria_NPC.c";
	sld.dialog.currentnode = "fraofficer";
    ChangeCharacterAddressGroup(sld, "Charles_town", "quest", "quest1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Patria_SanMartinSetBaron()
{
	sld = characterFromId("Noel");
	sld.dialog.currentnode = "noel_18";
	ChangeCharacterAddressGroup(sld, "Charles_town", "reload", "reload3");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "reload", "reload1", "Patria_SanMartinSetBaron", -1);
}

void Patria_SanMartinBaronOver(string qName) // время вышло - взрываем корабль ГГ
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Patria_SanMartinBaronOver.over"))
			DeleteAttribute(pchar,"quest.Patria_SanMartinBaronOver.over");
		NewGameTip(StringFromKey("Patria_6"));
		SetFunctionTimerCondition("Patria_SanMartinBaronOver", 0, 0, 3, false);
		return;
	}
	if (bSeaActive) DoQuestFunctionDelay("Mtraxx_MarkusGameOver", 2.0);
	else 
	{
		pchar.quest.patria_boom.win_condition.l1 = "EnterToSea";
		pchar.quest.patria_boom.function = "Patria_SanMartinBaronOverBoom";
	}
}

void Patria_SanMartinBaronOverBoom(string qName) // время вышло - взрываем корабль ГГ
{
	bQuestDisableMapEnter = true;
	DoQuestFunctionDelay("Mtraxx_MarkusGameOver", 3.0);
}

void Patria_SanMartinFortAttack()
{
	DeleteAttribute(pchar, "questTemp.Patria.SanMartinFort");
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.quest.Patria_SanMartinBaronOver.over = "yes"; // снять таймер
	Island_SetReloadEnableGlobal("SentMartin", false);//закрыть Синт-Маартен лесник . сент мартин
	Island_SetReloadEnableGlobal("Curacao", false);//закрыть Кюрасао
	sld = CharacterFromID("Villemstad Fort Commander");
	Character_SetAbordageEnable(sld, false); // неабордируемый форт Кюрасао
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	SetNationRelation2MainCharacter(HOLLAND, RELATION_ENEMY);
	sld.AlwaysEnemy = true;
	DoQuestFunctionDelay("Patria_SanMartinSetSquadron", 5.0);
}

void Patria_SanMartinSetSquadron(string qName) // ставим эскадру голандцев
{
	AddQuestRecord("Patria", "27");
	PlaySound("interface\" + LanguageGetLanguage() + "\_EvEnemy0.wav");
	Group_FindOrCreateGroup("Patria_SanMartinSeaGroup");
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+3;
	if (iRank > 45) iRank = 45;
	int iShip, Ship1, Ship2, Ship3, iCannon, Cannon1, Cannon2;
	
	switch (MOD_SKILL_ENEMY_RATE)
	{
		case 2:
			Ship1 = SHIP_BRIG;
			Ship2 = SHIP_SHNYAVA;
			Ship3 = SHIP_SLOOP;
			Cannon1 = CANNON_TYPE_CANNON_LBS16;
			Cannon2 = CANNON_TYPE_CULVERINE_LBS8;
		break;
		
		case 4:
			Ship1 = SHIP_CARAVEL;
			Ship2 = SHIP_SHNYAVA;
			Ship3 = SHIP_SCHOONER_W;
			Cannon1 = CANNON_TYPE_CANNON_LBS16;
			Cannon2 = CANNON_TYPE_CANNON_LBS12;
		break;
		
		case 6:
			Ship1 = SHIP_CORVETTE;
			Ship2 = SHIP_BRIG;
			Ship3 = SHIP_SCHOONER_W;
			Cannon1 = CANNON_TYPE_CULVERINE_LBS18;
			Cannon2 = CANNON_TYPE_CANNON_LBS16;
		break;
		
		case 8:
			Ship1 = SHIP_FRIGATE;
			Ship2 = SHIP_GALEON_L;
			Ship3 = SHIP_BRIG;
			Cannon1 = CANNON_TYPE_CANNON_LBS24;
			Cannon2 = CANNON_TYPE_CANNON_LBS16;
		break;
		
		case 10:
			Ship1 = SHIP_FRIGATE_H;
			Ship2 = SHIP_CORVETTE;
			Ship3 = SHIP_CARAVEL;
			Cannon1 = CANNON_TYPE_CANNON_LBS24;
			Cannon2 = CANNON_TYPE_CULVERINE_LBS18;
		break;
	}
	for (int i=1; i<=3; i++)
	{
		switch (i)
		{
			case 1:
				iShip = Ship1;
				iCannon = Cannon1;
			break;
			
			case 2:
				iShip = Ship2;
				iCannon = Cannon2;
			break;
			
			case 3:
				iShip = Ship3;
				iCannon = Cannon2;
			break;
		}
		sld = GetCharacter(NPC_GenerateCharacter("Patria_SanMartinCap_"+i, "off_hol_"+i, "man", "man", iRank, HOLLAND, -1, true, "quest"));
		FantomMakeCoolSailor(sld, iShip, "", iCannon, 70, 70, 70);
		FantomMakeCoolFighter(sld, iRank, 70, 70, LinkRandPhrase("blade_09","blade_12","blade_13"), "pistol1", "bullet", 150);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.AlwaysEnemy = true;
		sld.Coastal_Captain = true;
		sld.Ship.Mode = "war";
		sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Sailors = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*6;
		if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
		Group_AddCharacter("Patria_SanMartinSeaGroup", "Patria_SanMartinCap_"+i);
	}
	Group_SetGroupCommander("Patria_SanMartinSeaGroup", "Patria_SanMartinCap_1");
	Group_SetTaskAttack("Patria_SanMartinSeaGroup", PLAYER_GROUP);
	Group_LockTask("Patria_SanMartinSeaGroup");
	Sea_LoginGroupCurrentSea("Patria_SanMartinSeaGroup");

	pchar.quest.Patria_SanMartin_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Patria_SanMartin_AfterBattle.win_condition.l1.group = "Patria_SanMartinSeaGroup";
	pchar.quest.Patria_SanMartin_AfterBattle.function = "Patria_SanMartinEscape";
}

void Patria_SanMartinEscape(string qName) // 
{
	Group_DeleteGroup("Patria_SanMartinSeaGroup");
	bQuestDisableMapEnter = false;
	AddQuestRecord("Patria", "28");
	pchar.quest.Patria_SanMartin_Sea.win_condition.l1 = "MapEnter";
	pchar.quest.Patria_SanMartin_Sea.function = "Patria_SanMartinSeaTalk";
}

void Patria_SanMartinSeaTalk(string qName) // разговор на палубе
{
	aref arOldMapPos;
	makearef(arOldMapPos, worldMap.old);
	WdmPrepareMapForAbordage(arOldMapPos);
	MakeCloneShipDeck(pchar, true);//клон палубы
	LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], true);
	DoReloadFromWorldMapToLocation("Ship_deck", "goto", "goto1");
	LAi_LockFightMode(pchar, true);
	pchar.quest.Munity = "";//чтобы не выскочил без разговора
	sld = characterFromId("Noel");
	sld.dialog.currentnode = "noel_21";
	ChangeCharacterAddressGroup(sld, "Ship_deck", "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Patria_SanMartinBack(string qName) // у Сент-Кристофера
{
	pchar.quest.Patria_SanMartinBaronOver.over = "yes"; // снять таймер
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.MapClosedNoBattle = true;
	pchar.quest.Patria_SanMartin_Back1.win_condition.l1 = "location";
	pchar.quest.Patria_SanMartin_Back1.win_condition.l1.location = "Charles_Roomtownhall";
	pchar.quest.Patria_SanMartin_Back1.function = "Patria_SanMartinFin";
}

void Patria_SanMartinFin(string qName) // у Пуанси
{
	sld = characterFromId("Noel");
	RemovePassenger(pchar, sld);
	ChangeCharacterAddressGroup(sld, "Charles_Roomtownhall", "goto", "goto5");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "goto", "goto4", "Patria_SanMartinBaronTurn", -1);
}

// ---------------------------------------------------------- задание 6 ---------------------------------------------------------------
void Patria_DiplomatBegin() // 
{
	bQuestDisableMapEnter = false;//открыть карту
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	Island_SetReloadEnableGlobal("Curacao", true);//открыть Кюрасао
	Island_SetReloadEnableGlobal("SentMartin", true);//открыть Синт-Маартен бухты
	sld = characterFromId("Stivesant");
	sld.dialog.currentnode = "Stivesant_27";
	if(bImCasual) NewGameTip(StringFromKey("Patria_9"));
	SetFunctionTimerCondition("Patria_DiplomatTimeOver", 0, 0, 90, false); // таймер
}

void Patria_DiplomatTimeOver(string qName) // слишком все затянули
{
	// вернуть Синт-Маартен в норму
	int n = FindIsland("SentMartin");
	Islands[n].reload.l1.radius = 600.0;
	LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", false); // открыть городские ворота
	sld = CharacterFromID("Marigo Fort Commander");
	LAi_SetImmortal(sld, false);
	Character_SetAbordageEnable(sld, true);
	RemoveItems(pchar, "patent_fra", 1);
	ChangeCharacterComplexReputation(pchar, "nobility", -10);
	ChangeCharacterComplexReputation(pchar, "authority", -5);
	ChangeCharacterNationReputation(pchar, FRANCE, -10);
	sld = characterFromId("Noel");
	sld.lifeday = 0;
	ChangeCharacterAddressGroup(sld, "none", "", "");
	pchar.questTemp.Patria = "fail";
	AddQuestRecord("Patria", "24_1");
	CloseQuestHeader("Patria");
	DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
}

void Patria_DiplomatFight() // 
{
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_group_Delete("EnemyFight");
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	if (iRank > 45) iRank = 45;
	for (i=1; i<=5; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("Patria_Vlmsold_"+i, "sold_hol_"+i, "man", "man", iRank, HOLLAND, -1, true, "soldier"));
		FantomMakeCoolFighter(sld, iRank, 40, 40, LinkRandPhrase("blade_09","blade_12","blade_13"), "pistol1", "bullet", 150);       
		LAi_SetWarriorType(sld); 
        ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		LAi_group_MoveCharacter(sld, "EnemyFight");
    }
    sld = GetCharacter(NPC_GenerateCharacter("Patria_Vlmoff", "off_hol_3", "man", "man", iRank+5, HOLLAND, -1, true, "soldier"));
	FantomMakeCoolFighter(sld, iRank, 40, 40, LinkRandPhrase("blade_09","blade_12","blade_13"), "pistol1", "bullet", 150);       
	LAi_SetWarriorType(sld); 
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Patria_DiplomatAfterFight");
	LAi_SetFightMode(pchar, true);
}

void Patria_DiplomatSail(string qName) // вышли на карту
{
	LocatorReloadEnterDisable("Villemstad_town", "reload3_back", false);
	pchar.quest.Patria_DiplomatSeabattle.win_condition.l1 = "EnterToSea";
	pchar.quest.Patria_DiplomatSeabattle.function = "Patria_DiplomatSeabattle";
}

void Patria_DiplomatSeabattle(string qName) // вышли в море
{
	bQuestDisableMapEnter = true;
	pchar.questTemp.Patria.Diplomat.CurIsland = PChar.location;
	if (pchar.questTemp.Patria.Diplomat.CurIsland != "") Island_SetReloadEnableGlobal(pchar.questTemp.Patria.Diplomat.CurIsland, false);
	log_info(PChar.location);
	DoQuestFunctionDelay("Patria_DiplomatSeabattleGo", 4.0);
}

void Patria_DiplomatSeabattleGo(string qName) // ставим эскадру голандцев
{
	PlaySound("interface\notebook.wav");
	PlaySound("interface\" + LanguageGetLanguage() + "\_EvEnemy0.wav");
	Group_FindOrCreateGroup("Patria_DiplomatSeaGroup");
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+3;
	if (iRank > 45) iRank = 45;
	int iShip, Ship1, Ship2, Ship3, iCannon, Cannon1, Cannon2;
	
	switch (MOD_SKILL_ENEMY_RATE)
	{
		case 2:
			Ship1 = SHIP_BRIG;
			Ship2 = SHIP_BRIGANTINE;
			Ship3 = SHIP_SCHOONER_W;
			Cannon1 = CANNON_TYPE_CANNON_LBS16;
			Cannon2 = CANNON_TYPE_CANNON_LBS12;
		break;
		
		case 4:
			Ship1 = SHIP_CORVETTE;
			Ship2 = SHIP_BRIGANTINE;
			Ship3 = SHIP_SCHOONER_W;
			Cannon1 = CANNON_TYPE_CULVERINE_LBS18;
			Cannon2 = CANNON_TYPE_CANNON_LBS16;
		break;
		
		case 6:
			Ship1 = SHIP_FRIGATE;
			Ship2 = SHIP_CORVETTE;
			Ship3 = SHIP_POLACRE;
			Cannon1 = CANNON_TYPE_CANNON_LBS24;
			Cannon2 = CANNON_TYPE_CULVERINE_LBS18;
		break;
		
		case 8:
			Ship1 = SHIP_FRIGATE_H;
			Ship2 = SHIP_FRIGATE;
			Ship3 = SHIP_CORVETTE;
			Cannon1 = CANNON_TYPE_CANNON_LBS24;
			Cannon2 = CANNON_TYPE_CULVERINE_LBS18;
		break;
		
		case 10:
			Ship1 = SHIP_LINESHIP;
			Ship2 = SHIP_FRIGATE_H;
			Ship3 = SHIP_FRIGATE;
			Cannon1 = CANNON_TYPE_CANNON_LBS36;
			Cannon2 = CANNON_TYPE_CANNON_LBS32;
		break;
	}
	for (int i=1; i<=3; i++)
	{
		switch (i)
		{
			case 1:
				iShip = Ship1;
				iCannon = Cannon1;
			break;
			
			case 2:
				iShip = Ship2;
				iCannon = Cannon2;
			break;
			
			case 3:
				iShip = Ship3;
				iCannon = Cannon2;
			break;
		}
		sld = GetCharacter(NPC_GenerateCharacter("Patria_DiplomatCap_"+i, "off_hol_"+i, "man", "man", iRank, HOLLAND, -1, true, "quest"));
		FantomMakeCoolSailor(sld, iShip, "", iCannon, 70, 70, 70);
		FantomMakeCoolFighter(sld, iRank, 70, 70, LinkRandPhrase("blade_09","blade_12","blade_13"), "pistol1", "bullet", 150);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.Coastal_Captain = true; 
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.AlwaysEnemy = true;
		sld.Ship.Mode = "war";
		sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Sailors = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*6;
		if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
		Group_AddCharacter("Patria_DiplomatSeaGroup", "Patria_DiplomatCap_"+i);
	}
	Group_SetGroupCommander("Patria_DiplomatSeaGroup", "Patria_DiplomatCap_1");
	Group_SetTaskAttack("Patria_DiplomatSeaGroup", PLAYER_GROUP);
	Group_LockTask("Patria_DiplomatSeaGroup");
	Sea_LoginGroupCurrentSea("Patria_DiplomatSeaGroup");

	pchar.quest.Patria_Diplomat_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Patria_Diplomat_AfterBattle.win_condition.l1.group = "Patria_DiplomatSeaGroup";
	pchar.quest.Patria_Diplomat_AfterBattle.function = "Patria_DiplomatAfterBattle";
}

void Patria_DiplomatAfterBattle(string qName) // потопили эскадру
{
	Group_DeleteGroup("Patria_DiplomatSeaGroup");
	bQuestDisableMapEnter = false;
	Island_SetReloadEnableGlobal(pchar.questTemp.Patria.Diplomat.CurIsland, true);
	DeleteAttribute(pchar, "questTemp.Patria.Diplomat.CurIsland");
	AddQuestRecord("Patria", "32");
	sld = characterFromId("Noel");
	ChangeCharacterAddressGroup(sld, "none", "", "");
}

// ---------------------------------------------------------- задание 7 ---------------------------------------------------------------
void Patria_HunterBegin() // 
{
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.MapClosedNoBattle = true;
	pchar.quest.Patria_Hunter_begin.win_condition.l1 = "Timer";
	pchar.quest.Patria_Hunter_begin.win_condition.l1.date.hour  = 9.00;
	pchar.quest.Patria_Hunter_begin.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
	pchar.quest.Patria_Hunter_begin.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
	pchar.quest.Patria_Hunter_begin.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
	pchar.quest.Patria_Hunter_begin.function = "Patria_HunterTask";
	// убираем Эклятон к Гваделупе
	Group_SetAddress("Ecliaton_group", "Guadeloupe", "quest_ships", "quest_ship_1");
	Group_SetTaskNone("Ecliaton_group");
	Group_LockTask("Ecliaton_group");
}

void Patria_HunterTask(string qName) // 
{
	sld = characterFromId("Noel");
	ChangeCharacterAddressGroup(sld, "Charles_Roomtownhall", "goto", "goto4");
	LAi_SetActorType(sld);
	pchar.questTemp.Patria = "epizode_7_go";
}

void Patria_HunterContinue() // 
{
	bQuestDisableMapEnter = false;//открыть карту
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	sld = CharacterFromID("Villemstad Fort Commander"); // бессмертный форт
	LAi_SetImmortal(sld, true);
	// меняем отношения наций
	pchar.questTemp.Patria.War = "true";
	LaunchNationLegend();
	DeleteAttribute(pchar, "questTemp.Patria.War");
	DoQuestCheckDelay("sea_victory", 0.2);
	// генератор голландских конвоев
	pchar.questTemp.Patria.Hunter = 0 // счетчик учёта сданных кораблей
	pchar.questTemp.Patria.Hunter.Capture = 0; // счетчик учёта захваченных кораблей
	pchar.questTemp.Patria.Hunter.Num = 0; // нумерация конвоев
	SetFunctionTimerCondition("Patria_HunterConvoyGenerate", 0, 0, 3, false);
	pchar.quest.Patria_Hunter_BugFixer.win_condition.l1 = "EnterToSea";
	pchar.quest.Patria_Hunter_BugFixer.function = "Patria_HunterBugFixer";
}

void Patria_HunterBugFixer(string qName) // 
{
	bQuestDisableMapEnter = false;//открыть карту
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
}

void Patria_HunterConvoyGenerate(string qName) // генерируем конвой
{
	if (sti(pchar.questTemp.Patria.Hunter) > 4) return;
	pchar.questTemp.Patria.Hunter.Num = sti(pchar.questTemp.Patria.Hunter.Num)+1; // порядковый номер конвоя
	int iColony = rand(5);
	int iDay, iGoods, iSpace, iShip, iShip1, iShip2, iCannon, iCannon1, iCannon2, iCannon3;
	string sColony, sModel;
	string sCapId = "PatriaHWICCap";
    string sGroup = "Sea_" + sCapId + "1";
	int iGoodsType = rand(1);
	if (iGoodsType > 0) iGoods = GOOD_COFFEE + rand(2);
	else iGoods = GOOD_EBONY + rand(2);
	switch (iGoods)
	{
		case 11:
			iSpace = 1400+rand(100);
		break;
		
		case 12:
			iSpace = 1400+rand(100);
		break;
		
		case 13:
			iSpace = 1400+rand(100);
		break;
		
		case 17:
			iSpace = 550+rand(20);
		break;
		
		case 18:
			iSpace = 670+rand(30);
		break;
		
		case 19:
			iSpace = 1400+rand(100);
		break;
	}
	switch (iColony)
	{
		case 0:
			sColony = "Shore45";
			iDay = 5;
		break;
		
		case 1:
			sColony = "Shore44";
			iDay = 6;
		break;
		
		case 2:
			sColony = "Mayak8";
			iDay = 8;
		break;
		
		case 3:
			sColony = "Shore58";
			iDay = 10;
		break;
		
		case 4:
			sColony = "Shore2";
			iDay = 5;
		break;
		
		case 5:
			sColony = "Shore28";
			iDay = 8;
		break;
	}
	switch (MOD_SKILL_ENEMY_RATE)
	{
		case 2:
			iShip1 = SHIP_BRIG;
			iShip2 = SHIP_SHNYAVA;
			iCannon1 = CANNON_TYPE_CANNON_LBS16;
			iCannon2 = CANNON_TYPE_CANNON_LBS16;
			iCannon3 = CANNON_TYPE_CANNON_LBS12;
		break;
		
		case 4:
			iShip1 = SHIP_CORVETTE;
			iShip2 = SHIP_BRIG;
			iCannon1 = CANNON_TYPE_CULVERINE_LBS18;
			iCannon2 = CANNON_TYPE_CANNON_LBS16;
			iCannon3 = CANNON_TYPE_CANNON_LBS16;
		break;
		
		case 6:
			iShip1 = SHIP_FRIGATE;
			iShip2 = SHIP_CORVETTE;
			iCannon1 = CANNON_TYPE_CANNON_LBS24;
			iCannon2 = CANNON_TYPE_CULVERINE_LBS18;
			iCannon3 = CANNON_TYPE_CULVERINE_LBS18;
		break;
		
		case 8:
			iShip1 = SHIP_FRIGATE_H;
			iShip2 = SHIP_FRIGATE;
			iCannon1 = CANNON_TYPE_CANNON_LBS24;
			iCannon2 = CANNON_TYPE_CANNON_LBS24;
			iCannon3 = CANNON_TYPE_CANNON_LBS24;
		break;
		
		case 10:
			iShip1 = SHIP_LINESHIP;
			iShip2 = SHIP_FRIGATE_H;
			iCannon1 = CANNON_TYPE_CANNON_LBS32;
			iCannon2 = CANNON_TYPE_CANNON_LBS24;
			iCannon3 = CANNON_TYPE_CANNON_LBS24;
		break;
	}
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	if (iRank > 45) iRank = 45;
	for (int i = 1; i <= 3; i++)
    {
		// 17-add
		switch (i)
		{
			case 1: 
				iShip = iShip1;
				iCannon = iCannon1;	
				sModel = "off_hol_1";
			break;
			case 2: 
				iShip = SHIP_EASTINDIAMAN; 
				iCannon = iCannon2;
				sModel = "off_hol_"+(rand(1)+4);
			break;
			case 3: 
				iShip = iShip2; 
				iCannon = iCannon3;
				sModel = "off_hol_2";
			break;
		}
		sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, sModel, "man", "man", iRank, HOLLAND, iDay, true, "quest"));
		FantomMakeCoolSailor(sld, iShip, "", iCannon, 50, 50, 50);
		FantomMakeCoolFighter(sld, iRank, 50, 50, LinkRandPhrase("blade_09","blade_12","blade_13"), "pistol1", "bullet", 150);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.Ship.Mode = "war";
		sld.AlwaysEnemy = true; // 7-add
		sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Sailors = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*6;
		if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
		sld.lifeDay = iDay;
		sld.Coastal_Captain = true;
		sld.WatchFort = true; //видеть форты
		if (i == 2) SetCharacterGoods(sld, iGoods, iSpace); // груз в ост-индец
		sld.mapEnc.type = "trade";
		sld.mapEnc.worldMapShip = "quest_ship";
        sld.mapEnc.Name = StringFromKey("Patria_15");
        Group_AddCharacter(sGroup, sCapId + i);
	}
	Group_SetGroupCommander(sGroup, sCapId+ "1");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	Map_CreateTrader(sColony, "Marigo", sCapId + "1", iDay);//запуск энкаунтера
	
	pchar.quest.patria_huntership_capture.win_condition.l1 = "Character_Capture";
	pchar.quest.patria_huntership_capture.win_condition.l1.character = "PatriaHWICCap2";
	pchar.quest.patria_huntership_capture.function = "Patria_HunterCaptureCounter";
	
	SetFunctionTimerCondition("Patria_HunterNewConvoyGenerate", 0, 0, iDay+3, false);
	
	log_Testinfo("Сгенерирован конвой номер "+sti(pchar.questTemp.Patria.Hunter.Num)+". Движется из "+XI_ConvertString(sColony)+", будет через "+FindRussianDaysString(iDay)+". Товар: "+GetGoodsNameAlt(iGoods)+" в количестве "+FindRussianQtyString(iSpace)+".");
}

void Patria_HunterNewConvoyGenerate(string qName) // 
{
	DoQuestFunctionDelay("Patria_HunterConvoyGenerate", 2.0);
}

void Patria_HunterCaptureCounter(string qName) // 
{
	log_info(StringFromKey("Patria_16"));
	PlaySound("interface\notebook.wav");
	pchar.questTemp.Patria.Hunter.Capture = sti(pchar.questTemp.Patria.Hunter.Capture)+1;
}

void Patria_HunterShipChecker()
{
	if (sti(pchar.questTemp.Patria.Hunter.Capture) < 1) return; // нет захваченных кораблей, чтобы не сдавал левые ост-индцы
	for(int i = 0; i < COMPANION_MAX; i++)
	{
		int iTemp = GetCompanionIndex(PChar, i);
		if(iTemp > 0)
		{
			ref sld = GetCharacter(iTemp);
			if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_EASTINDIAMAN)
			{
				log_Testinfo("Нужный корабль есть");
				if (GetCargoGoods(sld, GOOD_COFFEE) >= 1300 || GetCargoGoods(sld, GOOD_CHOCOLATE) >= 1300 || GetCargoGoods(sld, GOOD_TOBACCO) >= 1300 || GetCargoGoods(sld, GOOD_EBONY) >= 500 || GetCargoGoods(sld, GOOD_MAHOGANY) >= 600 || GetCargoGoods(sld, GOOD_CINNAMON) >= 1300)
				{
					i = 6; // остановка цикла
					pchar.questTemp.Patria.Hunter.Capture = sti(pchar.questTemp.Patria.Hunter.Capture)-1; // уменьшаем счетчик захваченных кораблей
					pchar.questTemp.Patria.Hunter.GiveShip = "true";
					log_Testinfo("Корабль есть и нужный товар есть на корабле!");
					if (sld.index == pchar.index)
					{
						pchar.Ship.Type = SHIP_NOTUSED;
					}
					else
					{
						RemoveCharacterCompanion(PChar, sld);
						AddPassenger(PChar, sld, false);
					}
				}
			}
		}
	}
}
// ---------------------------------------------------------- задание 8 ---------------------------------------------------------------
void Patria_SiegeBegin(string qName) // вестовой Пуанси
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = characterFromId("Patria_FraOfficer");
	sld.dialog.currentnode = "fraofficer_2";
    ChangeCharacterAddressGroup(sld, "Charles_town", "quest", "quest1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Patria_SiegeHovernor() // 
{
	AddQuestRecord("Patria", "37");
	pchar.questTemp.Patria = "epizode_8";
	LocatorReloadEnterDisable("Charles_town", "reload1_back", true);
	LocatorReloadEnterDisable("Charles_town", "reload2_back", true);
	LocatorReloadEnterDisable("Charles_town", "gate_back", true);//закрыть выходы из города
}

void Patria_SiegeCreateSquadron() // осада 
{
	bQuestDisableMapEnter = false;//открыть карту
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	pchar.questTemp.Patria.Escape = "true";
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	LocatorReloadEnterDisable("Charles_town", "reload1_back", false);
	LocatorReloadEnterDisable("Charles_town", "reload2_back", false);
	LocatorReloadEnterDisable("Charles_town", "gate_back", false);//открыть выходы из города
	Island_SetReloadEnableGlobal("Nevis", false);//закрыть остров
	// добавляем курьерский люггер
	sld = GetCharacter(NPC_GenerateCharacter("Patria_CureerCap", "off_fra_3", "man", "man", 25, FRANCE, -1, false, "soldier"));
	FantomMakeCoolSailor(sld, SHIP_CAREERLUGGER, "", CANNON_TYPE_CULVERINE_LBS8, 100, 100, 100);
	FantomMakeCoolFighter(sld, 25, 70, 70, "blade_11", "pistol1", "bullet", 50);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.Ship.Mode = "war";
	SetCharacterRemovable(sld, false);
	sld.CompanionEnemyEnable = false; //всегда друзья
	SetCompanionIndex(pchar, -1, sti(sld.index));
	sld.loyality = MAX_LOYALITY;
	// прерывание на потерю
	pchar.quest.Patria_LuggerFail.win_condition.l1 = "NPC_Death";
	pchar.quest.Patria_LuggerFail.win_condition.l1.character = "Patria_CureerCap";
	pchar.quest.Patria_LuggerFail.function = "Patria_LuggerFail";
	// ставим осаду
	// линейник + военник голландцев
	for(int i = 1; i <= 3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Patria_SiegeCap_"+i, "off_hol_"+(7-i), "man", "man", 35, HOLLAND, -1, true, "quest"));
		if (i == 1) 
		{
			sld.Ship.Type = GenerateShipHand(sld, SHIP_LSHIP_HOL, 42, 9500, 840, 11500, 350000, 12.5, 29.5, 0.38);
			sld.Ship.name = StringFromKey("Patria_17");
			SetBaseShipData(sld);
			sld.Ship.Cannons.Type = CANNON_TYPE_CULVERINE_LBS36;
			sld.rank = 45;
			SetShipSkill(sld, 80, 50, 100, 100, 100, 100, 100, 100, 80);
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "Troopers");
			SetCharacterPerk(sld, "LongRangeGrappling");
			SetCharacterPerk(sld, "GrapplingProfessional");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "FastReload");
			SetCharacterPerk(sld, "CannonProfessional");
			SetCharacterPerk(sld, "BasicBattleState");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "Carpenter");
			SetCharacterPerk(sld, "Builder");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "StormProfessional");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "SailingProfessional");
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "Doctor2");
			FantomMakeCoolFighter(sld, 45, 80, 80, LinkRandPhrase("blade_18","blade_19","blade_20"), "pistol13", "bullet", 250);
			RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;
			UpgradeShipParameter(sld, "TurnRate");//маневренность
			sld.DontClearDead = true;
			sld.SaveItemsForDead = true;
		}
		else 
		{
			FantomMakeCoolSailor(sld, SHIP_LINESHIP, "", CANNON_TYPE_CANNON_LBS32, 70, 70, 70);
			FantomMakeCoolFighter(sld, 35, 70, 70, LinkRandPhrase("blade_18","blade_19","blade_20"), "pistol5", "bullet", 200);
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
		}
		
		sld.cirassId = Items_FindItemIdx("cirass4");
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.AlwaysEnemy = true;
		sld.Coastal_Captain = true;
		sld.AlwaysSandbankManeuver = true;
		sld.Ship.Mode = "war";
		LAi_SetImmortal(sld, true);
		Character_SetAbordageEnable(sld, false); // нельзя абордировать
		sld.Abordage.MakeDisable = true; // запрет идти на абордаж
		sld.Abordage.Enable = false;
		if (i == 1 && MOD_SKILL_ENEMY_RATE > 4) sld.SeaBoss = 0.6; // получает на 60% меньше урона корпусу
		sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*5;
		sld.Ship.Crew.Exp.Sailors = 40+MOD_SKILL_ENEMY_RATE*5;
		sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*5;
		sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*5;
		if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
		SetRandGeraldSail(sld, HOLLAND);
		if (i < 3) Group_AddCharacter("Patria_SiegeGroup1", "Patria_SiegeCap_"+i);
		else Group_AddCharacter("Patria_SiegeGroup2", "Patria_SiegeCap_"+i);
	}
	
	Group_SetGroupCommander("Patria_SiegeGroup1", "Patria_SiegeCap_1");
	Group_SetAddress("Patria_SiegeGroup1", "Nevis", "quest_ships", "quest_ship_2");
	Group_SetGroupCommander("Patria_SiegeGroup2", "Patria_SiegeCap_3");
	Group_SetAddress("Patria_SiegeGroup2", "Nevis", "quest_ships", "quest_ship_5");
	// военники испанцев
	for(i = 4; i <= 6; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Patria_SiegeCap_"+i, "off_spa_"+(8-i), "man", "man", 35, SPAIN, -1, true, "quest"));
		if (i == 4) FantomMakeCoolSailor(sld, SHIP_LINESHIP, "", CANNON_TYPE_CANNON_LBS36, 70, 70, 70);
		else FantomMakeCoolSailor(sld, SHIP_LINESHIP, "", CANNON_TYPE_CANNON_LBS32, 65, 65, 65);
		FantomMakeCoolFighter(sld, 35, 80, 80, LinkRandPhrase("blade_18","blade_19","blade_20"), "pistol5", "bullet", 150);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.cirassId = Items_FindItemIdx("cirass4");
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.AlwaysEnemy = true;
		sld.Coastal_Captain = true;
		sld.AlwaysSandbankManeuver = true;
		sld.Ship.Mode = "war";
		LAi_SetImmortal(sld, true);
		Character_SetAbordageEnable(sld, false); // нельзя абордировать
		sld.Abordage.MakeDisable = true; // запрет идти на абордаж
		sld.Abordage.Enable = false;
		sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*5;
		sld.Ship.Crew.Exp.Sailors = 40+MOD_SKILL_ENEMY_RATE*5;
		sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*5;
		sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*5;
		if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
		SetRandGeraldSail(sld, SPAIN);
		if (i == 4) Group_AddCharacter("Patria_SiegeGroup3", "Patria_SiegeCap_"+i);
		else 
		{
			if (i == 5) Group_AddCharacter("Patria_SiegeGroup4", "Patria_SiegeCap_"+i);
			else Group_AddCharacter("Patria_SiegeGroup5", "Patria_SiegeCap_"+i);
		}
	}
	Group_SetGroupCommander("Patria_SiegeGroup3", "Patria_SiegeCap_4");
	Group_SetAddress("Patria_SiegeGroup3", "Nevis", "quest_ships", "quest_ship_6");
	Group_SetGroupCommander("Patria_SiegeGroup4", "Patria_SiegeCap_5");
	Group_SetAddress("Patria_SiegeGroup4", "Nevis", "quest_ships", "quest_ship_7");
	Group_SetGroupCommander("Patria_SiegeGroup5", "Patria_SiegeCap_6");
	Group_SetAddress("Patria_SiegeGroup5", "Nevis", "quest_ships", "quest_ship_8");
	for(i = 1; i <= 5; i++)
	{
		Group_SetTaskNone("Patria_SiegeGroup"+i);
		Group_LockTask("Patria_SiegeGroup"+i);
	}
	// прерывание на выход в море
	pchar.quest.Patria_Siege_escape.win_condition.l1 = "location";
	pchar.quest.Patria_Siege_escape.win_condition.l1.location = "Nevis";
	pchar.quest.Patria_Siege_escape.function = "Patria_SiegeEscapeReady";
	// на глобалку
	pchar.quest.Patria_Siege_map.win_condition.l1 = "MapEnter";
	pchar.quest.Patria_Siege_map.function = "Patria_SiegeEscapeOnMap";
	pchar.questTemp.Patria.Escape_count = 0;
	// таймер на 20 дней, после этого Капстервиль падет и станет голландским
	SetFunctionTimerCondition("Patria_SiegeCapitulation", 0, 0, 20, false);
	if(bImCasual) NewGameTip(StringFromKey("Patria_9"));
	// д'Ойли настоящего прячем
	sld = characterFromId("PortRoyal_Mayor");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld.quest.meeting = "1"; // если не было
}

void Patria_SiegeCapitulation(string qName) // Капстервиль капитулировал, полный провал
{
	AddQuestRecord("Patria", "41");
	sld = CharacterFromID("Villemstad Fort Commander"); // бессмертный форт Виллемстада
	LAi_SetImmortal(sld, false);
	// д'Ойли на место
	Group_DeleteGroup("Patria_EngSquadron");
	sld = characterFromId("PortRoyal_Mayor");
	LAi_SetHuberType(sld);
	ChangeCharacterAddressGroup(sld, "PortRoyal_townhall", "sit", "sit1");
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	if (GetCharacterIndex("Doily") != -1)
	{
		sld.lifeday = 0;
	}
	if (GetCharacterIndex("Doily_land") != -1)
	{
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld.lifeday = 0;
	}
	// Пуанси убираем 
	sld = characterFromId("Puancie");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	// губера переделываем
	sld = characterFromId("Charles_Mayor");
	sld.model = "off_hol_6";
	Characters_RefreshModel(sld);
	sld.name 	= StringFromKey("Patria_18");
    sld.lastname = StringFromKey("Patria_19");
	sld.nation = HOLLAND;
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	// меняем нацию колонии
	int i = FindColony("Charles");
	colonies[i].nation = HOLLAND;
	string sColony = "Charles_town";
	worldMap.labels.(sColony).icon = HOLLAND;
        Island_SetReloadEnableGlobal("Nevis", true); // belamour
	// убираем осадную эскадру
	for(i = 1; i <= 5; i++)
	{
		Group_DeleteGroup("Patria_SiegeGroup"+i);
	}
	// убираем Эклятон
	Group_DeleteGroup("Ecliaton_group");
	// репутация и прочее
	RemoveItems(pchar, "patent_fra", 1);
	RemoveItems(pchar, "Reserve_item_01", 1);
	ChangeCharacterComplexReputation(pchar, "nobility", -20);
	ChangeCharacterComplexReputation(pchar, "authority", -10);
	ChangeCharacterNationReputation(pchar, FRANCE, -30);
	pchar.questTemp.Patria = "fail";
	CloseQuestHeader("Patria");
	DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
	// вернуть Синт-Маартен в норму
	int n = FindIsland("SentMartin");
	Islands[n].reload.l1.radius = 600.0;
	LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", false); // открыть городские ворота
	sld = CharacterFromID("Marigo Fort Commander");
	LAi_SetImmortal(sld, false);
	Character_SetAbordageEnable(sld, true);
}

void Patria_LuggerFail(string qName) // потеря люггера
{
	pchar.questTemp.Patria.FailLugger = "true";
	AddQuestRecord("Patria", "39");
}

void Patria_SiegeEscapeReady(string qName) // 
{
	DoQuestFunctionDelay("Patria_SiegeEscape", 20.0);
}

void Patria_SiegeEscape(string qName) // вышли в море, начинаем подгружать три корабля противника
{
	if (pchar.location != "Nevis") return;
	pchar.questTemp.Patria.Escape_count = sti(pchar.questTemp.Patria.Escape_count)+1;
	if (sti(pchar.questTemp.Patria.Escape_count) > 3) return;
	PlaySound("interface\notebook.wav");
	PlaySound("interface\" + LanguageGetLanguage() + "\_EvEnemy0.wav");
	string sGroup = "Patria_EscapeSeaGroup_"+sti(pchar.questTemp.Patria.Escape_count);
	Group_FindOrCreateGroup(sGroup);
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+3;
	if (iRank > 45) iRank = 45;
	int iShip, iCannon;
	
	switch (MOD_SKILL_ENEMY_RATE)
	{
		case 2:
			iShip = SHIP_CORVETTE;
			iCannon = CANNON_TYPE_CANNON_LBS20;
		break;
		
		case 4:
			iShip = SHIP_CORVETTE;
			iCannon = CANNON_TYPE_CULVERINE_LBS18;
		break;
		
		case 6:
			iShip = SHIP_GALEON_H + rand(1);
			iCannon = CANNON_TYPE_CANNON_LBS24;
		break;
		
		case 8:
			iShip = SHIP_GALEON_H + rand(2);
			iCannon = CANNON_TYPE_CANNON_LBS32;
		break;
		
		case 10:
			iShip = SHIP_FRIGATE_H + rand(1);
			if (iShip == SHIP_LINESHIP) iCannon = CANNON_TYPE_CANNON_LBS36;
			else iCannon = CANNON_TYPE_CANNON_LBS32;
		break;
	}
	sld = GetCharacter(NPC_GenerateCharacter(sGroup+"_Cap", "off_hol_"+(rand(2)+1), "man", "man", iRank, HOLLAND, 2, true, "quest"));
	FantomMakeCoolSailor(sld, iShip, "", iCannon, 70, 70, 70);
	FantomMakeCoolFighter(sld, iRank, 70, 70, LinkRandPhrase("blade_09","blade_12","blade_13"), "pistol1", "bullet", 150);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.AlwaysEnemy = true;
	sld.Ship.Mode = "war";
	sld.Coastal_Captain = true; // 14-add
	sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*6;
	sld.Ship.Crew.Exp.Sailors = 40+MOD_SKILL_ENEMY_RATE*6;
	sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*6;
	sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*6;
	if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
	Group_AddCharacter(sGroup, sGroup+"_Cap");
	Group_SetGroupCommander(sGroup, sGroup+"_Cap");
	Group_SetTaskAttack(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Sea_LoginGroupCurrentSea(sGroup);
	DoQuestFunctionDelay("Patria_SiegeEscapeReady", 180.0); // 3 минуты до следующего корабля
}

void Patria_SiegeEscapeOnMap(string qName) // 
{
	if (!CheckAttribute(pchar, "questTemp.Patria.FailLugger"))
	{
		pchar.quest.Patria_LuggerFail.over = "yes";
		sld = characterFromId("Patria_CureerCap");
		RemoveCharacterCompanion(pchar, sld);
		sld.lifeday = 0;
		AddQuestRecord("Patria", "40");
	}
	// ставим эскадру клона д'Ойли у Антигуа
	int iShip, iCannon;
	sld = GetCharacter(NPC_GenerateCharacter("Doily", "huber_9", "man", "man", 45, ENGLAND, -1, true, "quest"));
	sld.name = StringFromKey("Patria_20");
    sld.lastname = StringFromKey("Patria_21");
	sld.Dialog.Filename = "Quest\Patria_NPC.c";
	sld.dialog.currentnode = "doily_10";
	FantomMakeCoolSailor(sld, SHIP_LSHIP_ENG, StringFromKey("Patria_22"), CANNON_TYPE_CULVERINE_LBS36, 100, 100, 100);
	FantomMakeCoolFighter(sld, 45, 100, 100, "blade_20", "pistol5", "bullet", 250);
	SetSelfSkill(sld, 90, 90, 90, 90, 90);
	SetShipSkill(sld, 90, 100, 100, 100, 100, 100, 100, 100, 70);
	sld.cirassId = Items_FindItemIdx("cirass4");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable = true;
	sld.AlwaysSandbankManeuver = true;
	sld.Ship.Mode = "war";
	sld.DontDeskTalk = true; // не высылать шлюпку
	LAi_SetImmortal(sld, true); // не забыть снять
	sld.ShipHideImmortal = 1000; // непотопляемый корабль
	Character_SetAbordageEnable(sld, false); // нельзя абордировать
	sld.Tasks.CanBoarding = false; // запрет идти на абордаж - дубль
	sld.Tasks.CanChangeShipAfterBoarding = false; // запрет меняться кораблями - дубль
	sld.Abordage.Enable = false;
	sld.SeaBoss = 0.5; // получает на 50% меньше урона корпусу
	sld.ship.Crew.Morale = 100;
	sld.Ship.Crew.Exp.Sailors = 100;
	sld.Ship.Crew.Exp.Cannoners = 100;
	sld.Ship.Crew.Exp.Soldiers = 100;
	SetCharacterPerk(sld, "MusketsShoot");
	SetRandGeraldSail(sld, ENGLAND);
	Group_AddCharacter("Patria_EngSquadron", "Doily");
	for(int i = 2; i <= 4; i++)
	{
		switch (i)
		{
			case 2: 
				iShip = SHIP_LINESHIP;
				iCannon = CANNON_TYPE_CANNON_LBS36;	
			break;
			case 3: 
				iShip = SHIP_LINESHIP; 
				iCannon = CANNON_TYPE_CANNON_LBS32;
			break;
			case 4: 
				iShip = SHIP_FRIGATE_H; 
				iCannon = CANNON_TYPE_CANNON_LBS24;
			break;
		}
		sld = GetCharacter(NPC_GenerateCharacter("Patria_EngSquadronCap_"+i, "off_eng_"+(6-i), "man", "man", 42-(i*3), ENGLAND, -1, true, "quest"));
		FantomMakeCoolSailor(sld, iShip, "", iCannon, 100, 100, 100);
		FantomMakeCoolFighter(sld, 42-(i*3), 100, 100, LinkRandPhrase("blade_18","blade_19","blade_20"), "pistol5", "bullet", 250);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.cirassId = Items_FindItemIdx("cirass4");
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.AlwaysFriend = true;
		sld.ShipEnemyDisable = true;
		sld.AlwaysSandbankManeuver = true;
		sld.Ship.Mode = "war";
		LAi_SetImmortal(sld, true); // не забыть снять
		sld.ship.Crew.Morale = 90;
		sld.Ship.Crew.Exp.Sailors = 90;
		sld.Ship.Crew.Exp.Cannoners = 90;
		sld.Ship.Crew.Exp.Soldiers = 90;
		SetCharacterPerk(sld, "MusketsShoot");
		SetRandGeraldSail(sld, ENGLAND);
		Group_AddCharacter("Patria_EngSquadron", "Patria_EngSquadronCap_"+i);
	}
	Group_SetGroupCommander("Patria_EngSquadron", "Doily");
	Group_SetAddress("Patria_EngSquadron", "Antigua", "quest_ships", "quest_ship_1");
	Group_SetTaskNone("Patria_EngSquadron");
	Group_LockTask("Patria_EngSquadron");
	// в резиденцию ещё один клон
	sld = GetCharacter(NPC_GenerateCharacter("Doily_land", "huber_9", "man", "man", 45, ENGLAND, -1, true, "quest"));
	sld.name = StringFromKey("Patria_20");
    sld.lastname = StringFromKey("Patria_21");
	sld.Dialog.Filename = "Quest\Patria_NPC.c";
	sld.dialog.currentnode = "doily";
	FantomMakeCoolFighter(sld, 45, 100, 100, "blade_20", "pistol5", "bullet", 250);
	SetSelfSkill(sld, 90, 90, 90, 90, 90);
	SetShipSkill(sld, 90, 100, 100, 100, 100, 100, 100, 100, 70);
	LAi_SetStayType(sld);
	LAi_SetImmortal(sld, true); // 14-add
	ChangeCharacterAddressGroup(sld, "SentJons_Roomtownhall", "goto", "goto4");
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
}

void Patria_SiegeAddEngSquadron() // присоединяем эскадру д'Ойли
{
	pchar.quest.Patria_SiegeCapitulation.over = "yes"; //снять таймер
	// ремонтируем все осадные корабли и ставим их в две линии
	for(int i = 2; i <= 5; i++)
	{
		Group_DelCharacter("Patria_SiegeGroup"+i, "Patria_SiegeCap_"+(i+1));
	}
	Group_AddCharacter("Patria_SiegeGroup1", "Patria_SiegeCap_3"); // голландцы в одну группу
	for(i = 4; i <= 6; i++)
	{
		Group_AddCharacter("Patria_SiegeGroup2", "Patria_SiegeCap_"+i); // испанцы во вторую группу
	}
	for(i = 3; i <= 5; i++)
	{
		Group_DeleteGroup("Patria_SiegeGroup"+i); // лишнее удаляем
	}
	Group_SetAddress("Patria_SiegeGroup1", "Nevis", "quest_ships", "quest_ship_1");
	Group_SetAddress("Patria_SiegeGroup2", "Nevis", "quest_ships", "quest_ship_2");
	for(i = 1; i <= 6; i++) // чиним и пополняем боеприпасы, снимаем квестовое бессмертие
	{
		sld = characterFromId("Patria_SiegeCap_"+i);
		DeleteAttribute(sld, "ship.sails");
		DeleteAttribute(sld, "ship.blots");
		DeleteAttribute(sld, "ship.masts");
		DeleteAttribute(sld, "ship.hulls");
		AddCharacterGoods(sld, GOOD_BALLS, 1800);
		AddCharacterGoods(sld, GOOD_GRAPES, 1000);
		AddCharacterGoods(sld, GOOD_KNIPPELS, 700);
		AddCharacterGoods(sld, GOOD_BOMBS, 1500);
		AddCharacterGoods(sld, GOOD_POWDER, 5000);
		LAi_SetImmortal(sld, false);
		Character_SetAbordageEnable(sld, true); // можно абордировать
		DeleteAttribute(sld, "Abordage.MakeDisable");
		sld.Abordage.Enable = true;
	}
	// д'Ойли в компаньоны
	Group_DeleteGroup("Patria_EngSquadron");
	sld = characterFromId("Doily");
	SetCharacterRemovable(sld, false);
	sld.CompanionEnemyEnable = false; //всегда друзья
	SetCompanionIndex(pchar, -1, sti(sld.index));
	sld.loyality = MAX_LOYALITY;
	LAi_SetImmortal(sld, false);
	pchar.questTemp.Patria.Trafalgar = "true";
	for(i = 2; i <= 4; i++) 
	{
		sld = characterFromId("Patria_EngSquadronCap_"+i);
		SetCharacterRemovable(sld, false);
		sld.CompanionEnemyEnable = false; //всегда друзья
		SetCompanionIndex(pchar, -1, sti(sld.index));
		sld.loyality = MAX_LOYALITY;
		LAi_SetImmortal(sld, false);
	}
	SetFunctionTimerCondition("Patria_SiegeReturnToHelp", 0, 0, 7, false); // таймер 7 дней
	// прерывание на вход к Сент-Кристоферу
	pchar.quest.Patria_SiegeBattle.win_condition.l1 = "location";
	pchar.quest.Patria_SiegeBattle.win_condition.l1.location = "Nevis";
	pchar.quest.Patria_SiegeBattle.function = "Patria_SiegeSeaBattle";
}

void Patria_SiegeReturnToHelp(string qName) // не дошли за 7 дней
{
	pchar.quest.Patria_SiegeBattle.over = "yes"; 
	sld = characterFromId("Doily");
	LAi_SetImmortal(sld, true);
	RemoveCharacterCompanion(pchar, sld);
	sld.lifeday = 0;
	DeleteAttribute(pchar, "questTemp.Patria.Trafalgar");
	sld = characterFromId("PortRoyal_Mayor");
	LAi_SetHuberType(sld);
	ChangeCharacterAddressGroup(sld, "PortRoyal_townhall", "sit", "sit1");
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	for(int i = 2; i <= 4; i++) 
	{
		sld = characterFromId("Patria_EngSquadronCap_"+i);
		LAi_SetImmortal(sld, true);
		RemoveCharacterCompanion(pchar, sld);
		sld.lifeday = 0;
	}
	sld = CharacterFromID("Villemstad Fort Commander"); // бессмертный форт Виллемстада
	LAi_SetImmortal(sld, false);
	// убираем осадную эскадру
	for(i = 1; i <= 2; i++)
	{
		Group_DeleteGroup("Patria_SiegeGroup"+i);
	}
	// убираем Эклятон
	Group_DeleteGroup("Ecliaton_group");
	// репутация и прочее
	RemoveItems(pchar, "patent_fra", 1);
	ChangeCharacterComplexReputation(pchar, "nobility", -15);
	ChangeCharacterComplexReputation(pchar, "authority", -15);
	ChangeCharacterNationReputation(pchar, FRANCE, -10);
	pchar.questTemp.Patria = "fail";
	AddQuestRecord("Patria", "43");
	CloseQuestHeader("Patria");
	DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
	// вернуть Синт-Маартен в норму
	int n = FindIsland("SentMartin");
	Islands[n].reload.l1.radius = 600.0;
	LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", false); // открыть городские ворота
	sld = CharacterFromID("Marigo Fort Commander");
	LAi_SetImmortal(sld, false);
	Character_SetAbordageEnable(sld, true);
}

void Patria_SiegeSeaBattle(string qName) // 
{
	DoQuestFunctionDelay("Patria_SiegeSeaBattleGo", 2.0);
}

void Patria_SiegeSeaBattleGo(string qName) // бой эскадра на эскадру
{
	pchar.quest.Patria_SiegeReturnToHelp.over = "yes"; 
	bQuestDisableMapEnter = true;//закрыть карту
	// выводим англичан из подчинения
	sld = characterFromId("Doily");
	RemoveCharacterCompanion(pchar, sld);
	Group_AddCharacter("Patria_EngSquadron", "Doily");
	DeleteAttribute(pchar, "questTemp.Patria.Trafalgar");
	for(int i = 2; i <= 4; i++) 
	{
		sld = characterFromId("Patria_EngSquadronCap_"+i);
		RemoveCharacterCompanion(pchar, sld);
		Group_AddCharacter("Patria_EngSquadron", "Patria_EngSquadronCap_"+i);
	}
	Group_SetGroupCommander("Patria_EngSquadron", "Doily");
	Group_SetTaskAttack("Patria_SiegeGroup1", PLAYER_GROUP);
	Group_SetTaskAttack("Patria_SiegeGroup2", PLAYER_GROUP);
	Group_SetTaskAttack("Patria_SiegeGroup1", "Patria_EngSquadron");
	Group_SetTaskAttack("Patria_SiegeGroup2", "Patria_EngSquadron");
	if (!CheckAttribute(pchar, "questTemp.Patria.FailLugger")) DoQuestFunctionDelay("Patria_SiegeSeaBattleAddEcliaton", 5.0);
	// прерывание на уничтожение врага
	pchar.quest.Patria_Siege_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Patria_Siege_AfterBattle.win_condition.l1.group = "Patria_SiegeGroup1";
	pchar.quest.Patria_Siege_AfterBattle.win_condition.l2 = "Group_Death";
	pchar.quest.Patria_Siege_AfterBattle.win_condition.l2.group = "Patria_SiegeGroup2";
	pchar.quest.Patria_Siege_AfterBattle.function = "Patria_SiegeSeaBattleFin";
}

void Patria_SiegeSeaBattleAddEcliaton(string qName) // подгружаем Эклятон
{
	Sea_LoginGroupCurrentSea("Ecliaton_group");
	sld = characterFromId("Ecliaton_Cap");
	DeleteAttribute(sld, "ShipHideImmortal");
	SetCharacterRemovable(sld, false);
	sld.CompanionEnemyEnable = false; //всегда друзья
	SetCompanionIndex(pchar, -1, sti(sld.index));
	sld.loyality = MAX_LOYALITY;
	LAi_SetImmortal(sld, false);
	pchar.questTemp.Patria.Ecliaton = "true";
	// прерывание на потерю Эклятона
	pchar.quest.Patria_EcliatonFail.win_condition.l1 = "NPC_Death";
	pchar.quest.Patria_EcliatonFail.win_condition.l1.character = "Ecliaton_Cap";
	pchar.quest.Patria_EcliatonFail.function = "Patria_SiegeEcliatonFail";
}

void Patria_SiegeEcliatonFail(string qName) // 
{
	DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
	pchar.questTemp.Patria.Ecliaton_Fail = "true";
}

void Patria_SiegeSeaBattleFin(string qName) // победили
{
	Island_SetReloadEnableGlobal("Nevis", true);//открыть остров
	pchar.GenQuest.MapClosedNoBattle = true;
	Group_DeleteGroup("Patria_SiegeGroup1");
	Group_DeleteGroup("Patria_SiegeGroup2");
	AddQuestRecord("Patria", "44");
	pchar.questTemp.Patria = "epizode_8_return";
	pchar.quest.Patria_Siege_Fin.win_condition.l1 = "location";
	pchar.quest.Patria_Siege_Fin.win_condition.l1.location = "Charles_RoomTownhall";
	pchar.quest.Patria_Siege_Fin.function = "Patria_SiegeFin";
	sld = characterFromId("Doily");
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable = true;
	LAi_SetImmortal(sld, true);
	Group_AddCharacter("Patria_EngSquadron", "Doily");
	for(int i = 2; i <= 4; i++) 
	{
		sld = characterFromId("Patria_EngSquadronCap_"+i);
		sld.AlwaysFriend = true;
		sld.ShipEnemyDisable = true;
		LAi_SetImmortal(sld, true);
	}
}

void Patria_SiegeFin(string qName) // у Пуанси
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = characterFromId("Doily_land");
	ChangeCharacterAddressGroup(sld, "Charles_Roomtownhall", "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
}

void Patria_SiegeEnd() //
{
	chrDisableReloadToLocation = false;
	bQuestDisableMapEnter = false;//открыть карту
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	// отсоединяем Эклятон
	if (!CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
	{
		sld = characterFromId("Ecliaton_Cap");
		sld.ShipHideImmortal = 1000; // непотопляемый корабль
		RemoveCharacterCompanion(pchar, sld);
		sld.AlwaysFriend = true;
		sld.ShipEnemyDisable = true;
		Group_AddCharacter("Ecliaton_group", "Ecliaton_Cap");
		Group_SetGroupCommander("Ecliaton_group", "Ecliaton_Cap");
		Group_SetAddress("Ecliaton_group", "Nevis", "quest_ships", "quest_ship_1");
		Group_SetTaskNone("Ecliaton_group");
		Group_LockTask("Ecliaton_group");
		SetFunctionTimerCondition("Patria_EcliatonRepair", 0, 0, 5, false); // таймер на починку Эклятона
		DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
	}
	// д'Ойли и его эскадра
	sld = characterFromId("Doily");
	LAi_SetActorType(sld);
	sld.DontDeskTalk = true;
	Group_SetAddress("Patria_EngSquadron", "Nevis", "quest_ships", "quest_ship_2");
	SetFunctionTimerCondition("Patria_BastionStart", 0, 0, 7, false);
	SetFunctionTimerCondition("Patria_BastionTimeOver", 0, 0, 30, false);
	LocatorReloadEnterDisable("Charles_Townhall", "reload3", true);
}

// ---------------------------------------------------------- задание 9 ---------------------------------------------------------------
void Patria_BastionStart(string qName) // начало 9 эпизода
{
	AddQuestRecord("Patria", "46");
	pchar.questTemp.Patria = "epizode_9_start";
	LocatorReloadEnterDisable("Charles_Townhall", "reload3", false);
	// д'Ойли на место
	sld = characterFromId("Doily_land");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	Group_DeleteGroup("Patria_EngSquadron");
	sld = characterFromId("Doily");
	Group_AddCharacter("Patria_EngSquadron", "Doily");
	Group_SetAddress("Patria_EngSquadron", "Jamaica", "quest_ships", "quest_ship_1");
	DeleteAttribute(sld, "ship.sails");
    DeleteAttribute(sld, "ship.blots");
    DeleteAttribute(sld, "ship.masts");
	DeleteAttribute(sld, "ship.hulls");
	//sld.ship.HP = 10500;
	sld = characterFromId("PortRoyal_Mayor");
	LAi_SetHuberType(sld);
	ChangeCharacterAddressGroup(sld, "PortRoyal_townhall", "sit", "sit1");
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
}

void Patria_BastionTimeOver(string qName) // провал по времени 9 эпизода
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Patria_BastionTimeOver.over"))
			DeleteAttribute(pchar,"quest.Patria_BastionTimeOver.over");
		NewGameTip(StringFromKey("Patria_6"));
		SetFunctionTimerCondition("Patria_BastionTimeOver", 0, 0, 15, false);
		return;
	}
	AddQuestRecord("Patria", "47");
	RemoveItems(pchar, "patent_fra", 1);
	ChangeCharacterComplexReputation(pchar, "nobility", -10);
	ChangeCharacterComplexReputation(pchar, "authority", -5);
	ChangeCharacterNationReputation(pchar, FRANCE, -10);
	pchar.questTemp.Patria = "fail";
	CloseQuestHeader("Patria");
	DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
	// вернуть Синт-Маартен в норму
	int n = FindIsland("SentMartin");
	Islands[n].reload.l1.radius = 600.0;
	LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", false); // открыть городские ворота
	sld = CharacterFromID("Marigo Fort Commander");
	LAi_SetImmortal(sld, false);
	Character_SetAbordageEnable(sld, true);
}

void Patria_BastionFrigateGlp() // присоединяем фрегат на Гваделупе
{
	sld = GetCharacter(NPC_GenerateCharacter("Patria_GlpCap", "off_fra_2", "man", "man", 30, FRANCE, -1, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_FRIGATE, "", CANNON_TYPE_CANNON_LBS24, 60, 60, 60);
	FantomMakeCoolFighter(sld, 30, 60, 60, LinkRandPhrase("blade_09","blade_12","blade_13"), "pistol5", "bullet", 150);
	sld.Ship.Mode = "war";
	sld.ship.Crew.Morale = 90;
	sld.Ship.Crew.Exp.Sailors = 80;
	sld.Ship.Crew.Exp.Cannoners = 80;
	sld.Ship.Crew.Exp.Soldiers = 90;
	sld.reputation = 70;
	sld.alignment = "good";
	SetCharacterRemovable(sld, false);
	sld.CompanionEnemyEnable = false; //всегда друзья
	SetCompanionIndex(pchar, -1, sti(sld.index));
	sld.loyality = MAX_LOYALITY;
}

void Patria_BastionFrigateMrt() // присоединяем фрегат на Мартинике
{
	sld = GetCharacter(NPC_GenerateCharacter("Patria_MrtCap", "off_fra_3", "man", "man", 33, FRANCE, -1, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_FRIGATE_H, "", CANNON_TYPE_CULVERINE_LBS18, 65, 65, 65);
	FantomMakeCoolFighter(sld, 33, 65, 65, LinkRandPhrase("blade_09","blade_12","blade_13"), "pistol5", "bullet", 150);
	sld.Ship.Mode = "war";
	sld.ship.Crew.Morale = 95;
	sld.Ship.Crew.Exp.Sailors = 85;
	sld.Ship.Crew.Exp.Cannoners = 85;
	sld.Ship.Crew.Exp.Soldiers = 95;
	sld.reputation = 70;
	sld.alignment = "good";
	SetCharacterRemovable(sld, false);
	sld.CompanionEnemyEnable = false; //всегда друзья
	SetCompanionIndex(pchar, -1, sti(sld.index));
	sld.loyality = MAX_LOYALITY;
}

void Patria_BastionAddEcliaton() // присоединяем Эклятон
{
	sld = characterFromId("Ecliaton_Cap");
	DeleteAttribute(sld, "ShipHideImmortal");
	SetCharacterRemovable(sld, false);
	sld.CompanionEnemyEnable = false; //всегда друзья
	SetCompanionIndex(pchar, -1, sti(sld.index));
	sld.loyality = MAX_LOYALITY;
	pchar.questTemp.Patria.Ecliaton = "true";
	// прерывание на потерю Эклятона
	pchar.quest.Patria_EcliatonFail.win_condition.l1 = "NPC_Death";
	pchar.quest.Patria_EcliatonFail.win_condition.l1.character = "Ecliaton_Cap";
	pchar.quest.Patria_EcliatonFail.function = "Patria_EcliatonFail";
	// удаление группы Эклятона, иначе клон-призрак
	pchar.quest.Patria_EcliatonDelGroup.win_condition.l1 = "ExitFromSea";
	pchar.quest.Patria_EcliatonDelGroup.function = "Patria_EcliatonDelGroup";
}

void Patria_BastionSturmTimeOver(string qName) // провал по времени взятие Филипсбурга
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Patria_BastionSturmTimeOver.over"))
			DeleteAttribute(pchar,"quest.Patria_BastionSturmTimeOver.over");
		NewGameTip(StringFromKey("Patria_6"));
		SetFunctionTimerCondition("Patria_BastionSturmTimeOver", 0, 0, 15, false);
		return;
	}
	DeleteAttribute(pchar, "TempPerks.QuestTroopers");
	if (!CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
	{
		pchar.quest.Patria_EcliatonFail.over = "yes"; //снять прерывание
		sld = characterFromId("Ecliaton_Cap");
		sld.ShipHideImmortal = 1000; // непотопляемый корабль
		sld.lifeday = 0;
		RemoveCharacterCompanion(pchar, sld);
		sld.AlwaysFriend = true;
		sld.ShipEnemyDisable = true;
		DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
	}
	if (GetCharacterIndex("Patria_GlpCap") != -1)
	{
		sld = characterFromId("Patria_GlpCap");
		sld.ShipHideImmortal = 1000; // непотопляемый корабль
		sld.lifeday = 0;
		RemoveCharacterCompanion(pchar, sld);
		sld.AlwaysFriend = true;
		sld.ShipEnemyDisable = true;
	}
	if (GetCharacterIndex("Patria_MrtCap") != -1)
	{
		sld = characterFromId("Patria_MrtCap");
		sld.ShipHideImmortal = 1000; // непотопляемый корабль
		sld.lifeday = 0;
		RemoveCharacterCompanion(pchar, sld);
		sld.AlwaysFriend = true;
		sld.ShipEnemyDisable = true;
	}
	AddQuestRecord("Patria", "49");
	RemoveItems(pchar, "patent_fra", 1);
	ChangeCharacterComplexReputation(pchar, "nobility", -10);
	ChangeCharacterComplexReputation(pchar, "authority", -5);
	ChangeCharacterNationReputation(pchar, FRANCE, -10);
	pchar.questTemp.Patria = "fail";
	CloseQuestHeader("Patria");
	DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
}

void Patria_BastionSintMartenCapture() // Филипсбург капитулировал
{
	pchar.quest.Patria_BastionSturmTimeOver.over = "yes"; //снять таймер
	pchar.GenQuest.Hunter2Pause = true;
	pchar.GenQuest.CannotWait = true;
	sld = characterFromId("Marigo_Mayor");
	ChangeCharacterAddressGroup(sld, "Marigo_townhall", "goto", "governor1");
	LAi_SetStayType(sld);
	characters[GetCharacterIndex("Marigo_Mayor")].dialog.captureNode = "tomas"; //капитулянтская нода мэра
	LocatorReloadEnterDisable("Marigo_town", "gate_back", true);//закрыть выход из города
	bQuestDisableMapEnter = true;//закрыть карту
	pchar.GenQuest.MapClosedNoBattle = true;
	AddQuestRecord("Patria", "50");
	sld = characterFromId("Ecliaton_Cap");
	sld.dialog.currentnode = "ecliaton_cap_wait";
	sld.DeckDialogNode = "ecliaton_cap_wait"; // страховка от шибко грамотных
	// преобразуем локации
	// меняем локаторы бухты Гран Кейс
	int n = Findlocation("Shore40"); 
	Locations[n].models.always.locators = "shore08_locators_PTR";
	locations[n].reload.l3.name = "reload2_back";
	locations[n].reload.l3.go = "Location_reserve_01";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Beach";
	// локация пляжа к руднику
	n = Findlocation("Location_reserve_01"); 
	DeleteAttribute(&locations[n], "id.label");
	locations[n].id.label = "Shore40";
	locations[n].image = "loading\outside\harbor3.tga";
	locations[n].worldmap = "Shore40";
	locations[n].type = "seashore";
	locations[n].islandId = "SentMartin";
	locations[n].DisableEncounters = true;
	locations[n].Chestgennot = true; // не генерить сундуки
	locations[n].filespath.models = "locations\Outside\Shores\Shore13";
	Locations[n].models.always.jungle = "shore13";
	locations[n].models.always.jungle.sea_reflection = 1;
	Locations[n].models.always.shore13seabed = "shore13_seabed";
	Locations[n].models.always.locators = "shore13_locators_PTR";
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	Locations[n].models.always.grassPatch = "shore13_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	locations[n].models.day.charactersPatch = "shore13_patch";
	locations[n].models.night.charactersPatch = "shore13_patch";		
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";	
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Location_reserve_03"; // на рудник
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Mines";
	locations[n].locators_radius.reload.reload1_back = 8.0;
	
	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Shore40";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Shore40";
    locations[n].locators_radius.reload2_back = 2.0;
	// локация соляного рудника
	n = Findlocation("Location_reserve_03"); 
	DeleteAttribute(&locations[n], "models.always.l1");
	DeleteAttribute(&locations[n], "models.always.l2");
	DeleteAttribute(&locations[n], "models.always.l3");
	locations[n].id.label = "Mines";
	locations[n].worldmap = "Shore40";
	locations[n].islandId = "SentMartin";
    Locations[n].image = "Loading\Mine.tga";
	locations[n].type = "questisland";
	locations[n].filespath.models = "Locations\Mine";
	locations[n].models.always.jungle = "mine";
	locations[n].models.always.barricade = "mine_barricade";
	//locations[n].models.always.mortair1 = "mine_mortar2mine";
	locations[n].models.always.mortair2 = "mine_mortar2gate";
    locations[n].models.always.locators = "minentown_locators_PTR";
    locations[n].models.always.grassPatch = "mine_grass";
	locations[n].models.day.charactersPatch = "mine_patch_storyline";
	locations[n].models.day.fonar = "mine_fd";
	locations[n].models.night.charactersPatch = "mine_patch_storyline";
	locations[n].models.night.fonar = "mine_fn";
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";

	Locations[n].reload.l2.name = "reload2_back";
    Locations[n].reload.l2.go = "Location_reserve_01";
    Locations[n].reload.l2.emerge = "reload1";
    Locations[n].reload.l2.autoreload = "1";
    Locations[n].reload.l2.label = "Beach";
}

void Patria_BastionShore(string qName) // в бухте, ставим штурмовую роту
{
	for (int i=1; i<=15; i++)
	{
		if (i < 4) // мушкетеры, 3 шт
		{
			sld = GetCharacter(NPC_GenerateCharacter("Bastion_soldier_"+i, "mush_fra_"+i, "man", "mushketer", 30, FRANCE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, 30, 60, 60, "", "mushket2", "cartridge", 170);
			LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
			sld.cirassId = Items_FindItemIdx("cirass1");
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Bastion_soldier_"+i, "sold_fra_"+(rand(7)+1), "man", "man", 30, FRANCE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, 30, 60, 60, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 150);
			sld.cirassId = Items_FindItemIdx("cirass2");
		}
		ChangeCharacterAddressGroup(sld, "shore40", "goto", "goto1");
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorFollow(sld, pchar, "", -1);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
	}
	pchar.quest.Patria_BastionMarch.win_condition.l1 = "location";
	pchar.quest.Patria_BastionMarch.win_condition.l1.location = "Location_reserve_01";
	pchar.quest.Patria_BastionMarch.function = "Patria_BastionMarch";
}

void Patria_BastionMarch(string qName) // пляж перед рудником
{
	LocatorReloadEnterDisable("Location_reserve_01", "reload2_back", true); // закрыть выход назад
	for (int i=1; i<=15; i++)
	{
		sld = CharacterFromID("Bastion_soldier_"+i);
		ChangeCharacterAddressGroup(sld, "Location_reserve_01", "reload", "reload2_back");
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorFollow(sld, pchar, "", -1);
	}
	pchar.quest.Patria_BastionMineAttack.win_condition.l1 = "location";
	pchar.quest.Patria_BastionMineAttack.win_condition.l1.location = "Location_reserve_03";
	pchar.quest.Patria_BastionMineAttack.function = "Patria_BastionMineAttack";
}

void Patria_BastionMineAttack(string qName) // соляной рудник - бой
{
	LAi_group_Delete("EnemyFight");
	chrDisableReloadToLocation = true;//закрыть локацию
	for (int i=1; i<=15; i++)
	{
		sld = CharacterFromID("Bastion_soldier_"+i);
		ChangeCharacterAddressGroup(sld, "Location_reserve_03", "reload", "reload2_back");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	int iRank = 15+MOD_SKILL_ENEMY_RATE*3;
	// ставим 6 накрученных гранатометчиков
	for (i=1; i<=6; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Bastion_spa_gunner_"+i, "mush_spa_"+i, "man", "mushketer", iRank, SPAIN, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, 80, 80, "", "grape_mushket", "grenade", 250);
		LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "grenade");
		sld.cirassId = Items_FindItemIdx("cirass1");
		sld.MusketerDistance = 0;
		sld.LSC_clan = true;
		if (MOD_SKILL_ENEMY_RATE > 2) sld.MultiShooter = stf(MOD_SKILL_ENEMY_RATE/2);
		TakeNItems(sld, "grenade", 100);
		TakeNItems(sld, "potion2", 5);
		TakeNItems(sld, "potion3", 5);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		ChangeCharacterAddressGroup(sld, "Location_reserve_03", "quest", "gunner"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	// 10 гулящих гардов
	iRank = 10+MOD_SKILL_ENEMY_RATE*2;
	for (i=1; i<=10; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Bastion_spa_soldier_"+i, "sold_spa_"+(rand(7)+1), "man", "man", iRank, SPAIN, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, 40, 40, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 100);
		ChangeCharacterAddressGroup(sld, "Location_reserve_03", "quest", "gunner"+i);
		sld.LSC_clan = true;
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_SetFightMode(pchar, true);
	DoQuestFunctionDelay("Patria_BastionMineAttackAdd1", 30.0); // 30 секунд до первой атаки
}

void Patria_BastionMineAttackAdd1(string qName) // соляной рудник - 1 добавочная группа
{
	int iRank = 12+MOD_SKILL_ENEMY_RATE*2;
	for (int i=1; i<=4; i++)
	{
		if (i == 1) // офицер
		{
			sld = GetCharacter(NPC_GenerateCharacter("Bastion_spanish_add1_"+i, "off_spa_1", "man", "man", iRank+5, SPAIN, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, 55, 55, LinkRandPhrase("blade_18","blade_19","blade_21"), "pistol5", "bullet", 130);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Bastion_spanish_add1_"+i, "sold_spa_"+(rand(7)+1), "man", "man", iRank, SPAIN, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, 50, 50, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 110);
		}
		ChangeCharacterAddressGroup(sld, "Location_reserve_03", "reload", "houseH"+(rand(1)+3));
		sld.LSC_clan = true;
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	DoQuestFunctionDelay("Patria_BastionMineAttackAdd2", 30.0); // 30 секунд до второй атаки
}

void Patria_BastionMineAttackAdd2(string qName) // соляной рудник - 2 добавочная группа
{
	int iRank = 13+MOD_SKILL_ENEMY_RATE*2;
	for (int i=1; i<=4; i++)
	{
		if (i == 1) // офицер
		{
			sld = GetCharacter(NPC_GenerateCharacter("Bastion_spanish_add2_"+i, "off_spa_3", "man", "man", iRank+5, SPAIN, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_18","blade_19","blade_21"), "pistol6", "bullet", 170);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Bastion_spanish_add2_"+i, "sold_spa_"+(rand(7)+1), "man", "man", iRank, SPAIN, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, 55, 55, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 130);
		}
		ChangeCharacterAddressGroup(sld, "Location_reserve_03", "reload", "reload6_back");
		sld.LSC_clan = true;
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	DoQuestFunctionDelay("Patria_BastionMineAttackAdd3", 40.0); // 40 секунд до третьей атаки
}

void Patria_BastionMineAttackAdd3(string qName) // соляной рудник - 3 добавочная группа
{
	int iRank = 14+MOD_SKILL_ENEMY_RATE*2;
	for (int i=1; i<=4; i++)
	{
		if (i == 1) // офицер
		{
			sld = GetCharacter(NPC_GenerateCharacter("Bastion_spanish_add3_"+i, "off_spa_4", "man", "man", iRank+5, SPAIN, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, 65, 65, LinkRandPhrase("blade_18","blade_19","blade_21"), "pistol6", "bullet", 200);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Bastion_spanish_add3_"+i, "sold_spa_"+(rand(7)+1), "man", "man", iRank, SPAIN, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 150);
		}
		ChangeCharacterAddressGroup(sld, "Location_reserve_03", "reload", "reload4_back");
		sld.LSC_clan = true;
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	DoQuestFunctionDelay("Patria_BastionMineAttackAdd4", 40.0); // 30 секунд до четвертой атаки
}

void Patria_BastionMineAttackAdd4(string qName) // соляной рудник - 4 добавочная группа
{
	int iRank = 15+MOD_SKILL_ENEMY_RATE*2;
	for (int i=1; i<=4; i++)
	{
		if (i == 1) // офицер
		{
			sld = GetCharacter(NPC_GenerateCharacter("Bastion_spanish_add4_"+i, "off_spa_5", "man", "man", iRank+5, SPAIN, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, 70, 70, LinkRandPhrase("blade_18","blade_19","blade_21"), "pistol4", "bullet", 250);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Bastion_spanish_add4_"+i, "sold_spa_1"+i, "man", "man", iRank, SPAIN, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, 65, 65, LinkRandPhrase("blade_18","blade_19","blade_21"), "pistol6", "bullet", 180);
		}
		ChangeCharacterAddressGroup(sld, "Location_reserve_03", "reload", "reload3_back");
		sld.LSC_clan = true;
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetCheck("EnemyFight", "Patria_BastionMineAttackWin");
}

void Patria_BastionNewHuber(string qName) // обновляем губера Синт-Маартена и рудник
{
	// новый губер
	sld = characterFromId("Marigo_Mayor");
	sld.model = "off_fra_5";
	Characters_RefreshModel(sld);
	sld.name 	= StringFromKey("Patria_23");
    sld.lastname = StringFromKey("Patria_24");
	sld.dialog.currentnode = "First time";
	sld.nation = FRANCE;
	LAi_SetHuberType(sld);
	ChangeCharacterAddressGroup(sld, "Marigo_townhall", "sit", "sit1");
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	// рудник
	int n = Findlocation("Location_reserve_03"); 
	DeleteAttribute(&locations[n], "models.always.barricade");
	DeleteAttribute(&locations[n], "models.always.mortair2");
	locations[n].models.day.charactersPatch = "mine_patch";
	locations[n].models.night.charactersPatch = "mine_patch";
	for (int i=1; i<=15; i++) // рабочие
	{
		sld = GetCharacter(NPC_GenerateCharacter("MarigoMine_worker_"+i, "prizon_"+(rand(7)+1), "man", "man_B", 10, ENGLAND, -1, true, "native"));
		SetFantomParamFromRank(sld, 10, true);
		sld.dialog.Filename = "Convict_dialog.c";
		sld.dialog.currentnode = "First time";
		sld.greeting = "convict";
		sld.city = "marigo";
		sld.CityType = "citizen";
		LAi_CharacterReincarnation(sld, true, true);
		GiveItem2Character(sld, RandPhraseSimple("slave_01","topor_05"));
		EquipCharacterbyItem(sld, RandPhraseSimple("slave_01","topor_05"));
		ChangeCharacterAddressGroup(sld, "Location_reserve_03", "goto", "goto"+i);
		LAi_SetCitizenType(sld);
		LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	}
	for (i=1; i<=15; i++) // солдаты
	{
		sld = GetCharacter(NPC_GenerateCharacter("MarigoMine_soldier_"+i, "sold_eng_1"+(rand(7)+1), "man", "man", 25, ENGLAND, -1, false, "soldier"));
		SetFantomParamFromRank(sld, 25, true);
		sld.dialog.Filename = "Common_Soldier.c";
		sld.dialog.currentnode = "First time";
		sld.greeting = "soldier";
		sld.city = "marigo";
		sld.CityType = "soldier";
		LAi_CharacterReincarnation(sld, true, true);
		LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2);
		ChangeCharacterAddressGroup(sld, "Location_reserve_03", "patrol", "patrol"+i);
		LAi_SetPatrolType(sld);
		LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	}
}

// ---------------------------------------------------------- задание 10 ---------------------------------------------------------------
void Patria_SlaveShipsStart() // старт эпизода с перехватом каравана рабов
{
	// отсоединяем Эклятон
	if (!CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
	{
		sld = characterFromId("Ecliaton_Cap");
		sld.ShipHideImmortal = 1000; // непотопляемый корабль
		RemoveCharacterCompanion(pchar, sld);
		sld.AlwaysFriend = true;
		sld.ShipEnemyDisable = true;
		Group_AddCharacter("Ecliaton_group", "Ecliaton_Cap");
		Group_SetGroupCommander("Ecliaton_group", "Ecliaton_Cap");
		Group_SetAddress("Ecliaton_group", "Nevis", "quest_ships", "quest_ship_1");
		Group_SetTaskNone("Ecliaton_group");
		Group_LockTask("Ecliaton_group");
		SetFunctionTimerCondition("Patria_EcliatonRepair", 0, 0, 5, false); // таймер на починку Эклятона
		DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
	}
	if(bImCasual) NewGameTip(StringFromKey("Patria_9"));
	SetFunctionTimerCondition("Patria_SlaveShipsSail", 0, 0, 14, false); // таймер на 14 дней на запуск конвоя
	SetFunctionTimerCondition("Patria_SlaveShipsTimeOver", 0, 0, 21, false); // таймер на провал по времени
}

void Patria_SlaveShipsSail(string qName) // запускаем конвой
{
	int iShip, iShip1, iShip2, iCannon, iCannon1, iCannon2, iCannon3;
	string sColony, sModel;
	string sCapId = "PatriaSlaveCap";
    string sGroup = "Sea_" + sCapId + "1";
	
	switch (MOD_SKILL_ENEMY_RATE)
	{
		case 2:
			iShip1 = SHIP_FRIGATE;
			iShip2 = SHIP_CORVETTE;
			iCannon1 = CANNON_TYPE_CANNON_LBS16;
			iCannon2 = CANNON_TYPE_CANNON_LBS16;
			iCannon3 = CANNON_TYPE_CANNON_LBS16;
		break;
		
		case 4:
			iShip1 = SHIP_FRIGATE;
			iShip2 = SHIP_CORVETTE;
			iCannon1 = CANNON_TYPE_CULVERINE_LBS18;
			iCannon2 = CANNON_TYPE_CANNON_LBS20;
			iCannon3 = CANNON_TYPE_CANNON_LBS20;
		break;
		
		case 6:
			iShip1 = SHIP_FRIGATE_H;
			iShip2 = SHIP_FRIGATE;
			iCannon1 = CANNON_TYPE_CANNON_LBS24;
			iCannon2 = CANNON_TYPE_CANNON_LBS24;
			iCannon3 = CANNON_TYPE_CULVERINE_LBS18;
		break;
		
		case 8:
			iShip1 = SHIP_FRIGATE_H;
			iShip2 = SHIP_FRIGATE_H;
			iCannon1 = CANNON_TYPE_CANNON_LBS32;
			iCannon2 = CANNON_TYPE_CANNON_LBS24;
			iCannon3 = CANNON_TYPE_CANNON_LBS24;
		break;
		
		case 10:
			iShip1 = SHIP_LINESHIP;
			iShip2 = SHIP_FRIGATE_H;
			iCannon1 = CANNON_TYPE_CANNON_LBS32;
			iCannon2 = CANNON_TYPE_CANNON_LBS24;
			iCannon3 = CANNON_TYPE_CANNON_LBS32;
		break;
	}
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	if (iRank > 45) iRank = 45;
	for (int i = 1; i <= 4; i++)
    {
		SetRandomNameToCharacter(sld);
		SetRandomNameToShip(sld);
		switch (i)
		{
			case 1: 
				iShip = iShip1;
				iCannon = iCannon1;	
				sModel = "off_hol_2";
			break;
			case 2: 
				iShip = SHIP_EASTINDIAMAN; 
				iCannon = iCannon2;
				sModel = "off_hol_"+(rand(1)+4);
			break;
			case 3: 
				iShip = SHIP_EASTINDIAMAN; 
				iCannon = iCannon2;
				sModel = "off_hol_"+(rand(1)+4);
			break;
			case 4: 
				iShip = iShip2; 
				iCannon = iCannon3;
				sModel = "off_hol_1";
			break;
		}
		sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, sModel, "man", "man", iRank, HOLLAND, 6, true, "quest"));
		FantomMakeCoolSailor(sld, iShip, "", iCannon, 65, 65, 65);
		FantomMakeCoolFighter(sld, iRank, 65, 65, LinkRandPhrase("blade_09","blade_12","blade_13"), "pistol1", "bullet", 220);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.Coastal_Captain = true;
		sld.Ship.Mode = "war";
		sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Sailors = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*6;
		if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
		sld.lifeDay = 6;
		sld.AnalizeShips = true;
		sld.WatchFort = true; //видеть форты
		if (i == 2 || i == 3) SetCharacterGoods(sld, GOOD_SLAVES, 1500+rand(50)); // рабов в ост-индцы
		sld.mapEnc.type = "trade";
		sld.mapEnc.worldMapShip = "quest_ship";
        sld.mapEnc.Name = StringFromKey("Patria_25");
        Group_AddCharacter(sGroup, sCapId + i);
	}
	Group_SetGroupCommander(sGroup, sCapId+ "1");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	Map_CreateTrader("Mayak1", "Villemstad", sCapId + "1", 6);//запуск энкаунтера
	
	pchar.quest.patria_slaveship1_Abordage.win_condition.l1 = "Character_Capture";
	pchar.quest.patria_slaveship1_Abordage.win_condition.l1.character = "PatriaSlaveCap2";
	pchar.quest.patria_slaveship1_Abordage.function = "Patria_SlaveShipBoarding";
	
	pchar.quest.patria_slaveship2_Abordage.win_condition.l1 = "Character_Capture";
	pchar.quest.patria_slaveship2_Abordage.win_condition.l1.character = "PatriaSlaveCap3";
	pchar.quest.patria_slaveship2_Abordage.function = "Patria_SlaveShipBoarding";
	
	pchar.quest.patria_slaveship1_sink.win_condition.l1 = "Character_sink";
	pchar.quest.patria_slaveship1_sink.win_condition.l1.character = "PatriaSlaveCap2";
	pchar.quest.patria_slaveship1_sink.function = "Patria_SlaveShip1Sink";
	
	pchar.quest.patria_slaveship2_sink.win_condition.l1 = "Character_sink";
	pchar.quest.patria_slaveship2_sink.win_condition.l1.character = "PatriaSlaveCap3";
	pchar.quest.patria_slaveship2_sink.function = "Patria_SlaveShip2Sink";
	
	pchar.quest.patria_slaveship_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.patria_slaveship_AfterBattle.win_condition.l1.group = sGroup;
	pchar.quest.patria_slaveship_AfterBattle.function = "Patria_SlaveShipsAfterBattle";
}

void Patria_SlaveShipsTimeOver(string qName) // не нашли конвой или сбежали
{
	pchar.quest.patria_slaveship1_Abordage.over = "yes";
	pchar.quest.patria_slaveship2_Abordage.over = "yes";
	pchar.quest.patria_slaveship1_sink.over = "yes";
	pchar.quest.patria_slaveship2_sink.over = "yes";
	pchar.quest.patria_slaveship_AfterBattle.over = "yes";
	AddQuestRecord("Patria", "53");
	RemoveItems(pchar, "patent_fra", 1);
	ChangeCharacterComplexReputation(pchar, "nobility", -10);
	ChangeCharacterComplexReputation(pchar, "authority", -5);
	ChangeCharacterNationReputation(pchar, FRANCE, -10);
	pchar.questTemp.Patria = "fail";
	CloseQuestHeader("Patria");
	DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
}

void Patria_SlaveShip1Sink(string qName) // утоп 1 ост-индец
{
	pchar.questTemp.Patria.SlaveShips.Sink1 = "true";
	if (CheckAttribute(pchar, "questTemp.Patria.SlaveShips.Sink2"))
	{	
		pchar.questTemp.Patria.SlaveShips.SinkBoth = "true";
		AddQuestRecord("Patria", "55");
	}
	else AddQuestRecord("Patria", "54");
}

void Patria_SlaveShip2Sink(string qName) // утоп 2 ост-индец
{
	pchar.questTemp.Patria.SlaveShips.Sink2 = "true";
	if (CheckAttribute(pchar, "questTemp.Patria.SlaveShips.Sink1"))
	{	
		pchar.questTemp.Patria.SlaveShips.SinkBoth = "true";
		AddQuestRecord("Patria", "55");
	}
	else AddQuestRecord("Patria", "54");
}

void Patria_SlaveShipBoarding(string qName) // бой состоялся и был захвачен хоть 1 ост-индец
{
	pchar.questTemp.Patria.SlaveShips.Boarding = "true";
	pchar.quest.Patria_SlaveShipsTimeOver.over = "yes"; //снять таймер
	pchar.quest.patria_slaveship1_Abordage.over = "yes";
	pchar.quest.patria_slaveship2_Abordage.over = "yes";
	pchar.quest.patria_slaveship1_sink.over = "yes";
	pchar.quest.patria_slaveship2_sink.over = "yes";
}

void Patria_SlaveShipsAfterBattle(string qName) // итоги боя
{
	if (CheckAttribute(pchar, "questTemp.Patria.SlaveShips.Boarding")) // бой был и захватил хоть 1 - зачет
	{
		SetFunctionTimerCondition("Patria_SlaveShipsJamaicaTimeOver", 0, 0, 30, false); // таймер на месяц на прибытие к д'Ойли
		pchar.questTemp.Patria = "epizode_10_continue";
		AddQuestRecord("Patria", "56");
	}
	if (CheckAttribute(pchar, "questTemp.Patria.SlaveShips.SinkBoth")) // бой был и утопил обоих - полузачет, ищи рабов сам
	{
		pchar.quest.Patria_SlaveShipsTimeOver.over = "yes"; //снять таймер
		SetFunctionTimerCondition("Patria_SlaveShipsJamaicaTimeOver", 0, 0, 30, false); // таймер на месяц на прибытие к д'Ойли
		pchar.questTemp.Patria = "epizode_10_continue";
	}
	// иначе - либо упустил, либо сбежал, тогда отработает общий таймер 
}

void Patria_SlaveShipsJamaicaTimeOver(string qName) // не привезли рабов д'Ойли
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Patria_SlaveShipsJamaicaTimeOver.over"))
			DeleteAttribute(pchar,"quest.Patria_SlaveShipsJamaicaTimeOver.over");
		NewGameTip(StringFromKey("Patria_6"));
		SetFunctionTimerCondition("Patria_SlaveShipsJamaicaTimeOver", 0, 0, 15, false);
		return;
	}
	AddQuestRecord("Patria", "59");
	RemoveItems(pchar, "patent_fra", 1);
	ChangeCharacterComplexReputation(pchar, "nobility", -20);
	ChangeCharacterComplexReputation(pchar, "authority", -5);
	ChangeCharacterNationReputation(pchar, FRANCE, -30);
	pchar.questTemp.Patria = "fail";
	CloseQuestHeader("Patria");
	DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
}

// ---------------------------------------------------------- задание 11 ---------------------------------------------------------------
void Patria_CuracaoAddEcliaton() // присоединяем Эклятон
{
	sld = characterFromId("Ecliaton_Cap");
	DeleteAttribute(sld, "ShipHideImmortal");
	SetCharacterRemovable(sld, false);
	sld.CompanionEnemyEnable = false; //всегда друзья
	SetCompanionIndex(pchar, -1, sti(sld.index));
	sld.loyality = MAX_LOYALITY;
	pchar.questTemp.Patria.Ecliaton = "true";
	// прерывание на потерю Эклятона
	pchar.quest.Patria_EcliatonFail.win_condition.l1 = "NPC_Death";
	pchar.quest.Patria_EcliatonFail.win_condition.l1.character = "Ecliaton_Cap";
	pchar.quest.Patria_EcliatonFail.function = "Patria_EcliatonFail";
	// удаление группы Эклятона, иначе клон-призрак
	pchar.quest.Patria_EcliatonDelGroup.win_condition.l1 = "ExitFromSea";
	pchar.quest.Patria_EcliatonDelGroup.function = "Patria_EcliatonDelGroup";
}

void Patria_CuracaoDoilyReady(string qName) // д'Ойли готов к походу - эскадру на рейд
{
	pchar.questTemp.Patria.Curacao.DoilyReady = "true";
	int iShip, iCannon;
	sld = characterFromId("Doily");
	sld.nation = ENGLAND;
	FantomMakeCoolSailor(sld, SHIP_LSHIP_ENG, StringFromKey("Patria_22"), CANNON_TYPE_CULVERINE_LBS36, 100, 100, 100);
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.AlwaysFriend = true;
	sld.ShipEnemyDisable = true;
	sld.AlwaysSandbankManeuver = true;
	sld.Ship.Mode = "war";
	sld.DontDeskTalk = true; // не высылать шлюпку
	LAi_SetImmortal(sld, true); // не забыть снять
	sld.ShipHideImmortal = 1000; // непотопляемый корабль
	Character_SetAbordageEnable(sld, false); // нельзя абордировать
	sld.Tasks.CanBoarding = false; // запрет идти на абордаж - дубль
	sld.Tasks.CanChangeShipAfterBoarding = false; // запрет меняться кораблями - дубль
	sld.Abordage.Enable = false;
	sld.SeaBoss = 0.5; // получает на 50% меньше урона корпусу
	sld.ship.Crew.Morale = 100;
	sld.Ship.Crew.Exp.Sailors = 100;
	sld.Ship.Crew.Exp.Cannoners = 100;
	sld.Ship.Crew.Exp.Soldiers = 100;
	SetCharacterPerk(sld, "MusketsShoot");
	SetRandGeraldSail(sld, ENGLAND);
	Group_AddCharacter("Patria_DoilySquadron", "Doily");
	for(int i = 1; i <= 2; i++)
	{
		switch (i)
		{
			case 1: 
				iShip = SHIP_LINESHIP;
				iCannon = CANNON_TYPE_CANNON_LBS36;	
			break;
			case 2: 
				iShip = SHIP_LINESHIP; 
				iCannon = CANNON_TYPE_CANNON_LBS32;
			break;
		}
		sld = GetCharacter(NPC_GenerateCharacter("Patria_DoilySquadronCap_"+i, "off_eng_"+(6-i), "man", "man", 35, ENGLAND, -1, true, "quest"));
		FantomMakeCoolSailor(sld, iShip, "", iCannon, 100, 100, 100);
		FantomMakeCoolFighter(sld, 35, 100, 100, LinkRandPhrase("blade_18","blade_19","blade_20"), "pistol5", "bullet", 250);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.cirassId = Items_FindItemIdx("cirass4");
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.AlwaysFriend = true;
		sld.ShipEnemyDisable = true;
		sld.AlwaysSandbankManeuver = true;
		sld.Ship.Mode = "war";
		LAi_SetImmortal(sld, true); // не забыть снять
		sld.ship.Crew.Morale = 90;
		sld.Ship.Crew.Exp.Sailors = 90;
		sld.Ship.Crew.Exp.Cannoners = 90;
		sld.Ship.Crew.Exp.Soldiers = 90;
		SetCharacterPerk(sld, "MusketsShoot");
		SetRandGeraldSail(sld, ENGLAND);
		Group_AddCharacter("Patria_DoilySquadron", "Patria_DoilySquadronCap_"+i);
	}
	Group_SetGroupCommander("Patria_DoilySquadron", "Doily");
	Group_SetAddress("Patria_DoilySquadron", "Jamaica", "quest_ships", "quest_ship_1");
	Group_SetTaskNone("Patria_DoilySquadron");
	Group_LockTask("Patria_DoilySquadron");
}

void Patria_CuracaoTimeOver(string qName) // не пришли к д'Ойли назад за 2 месяца
{
	if(bImCasual)
	{
		if(CheckAttribute(pchar,"quest.Patria_CuracaoTimeOver.over"))
			DeleteAttribute(pchar,"quest.Patria_CuracaoTimeOver.over");
		NewGameTip(StringFromKey("Patria_6"));
		SetFunctionTimerCondition("Patria_CuracaoTimeOver", 0, 0, 15, false);
		return;
	}
	if (!CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
	{
		pchar.quest.Patria_EcliatonFail.over = "yes"; //снять прерывание
		sld = characterFromId("Ecliaton_Cap");
		sld.ShipHideImmortal = 1000; // непотопляемый корабль
		sld.lifeday = 0;
		RemoveCharacterCompanion(pchar, sld);
		sld.AlwaysFriend = true;
		sld.ShipEnemyDisable = true;
		DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
	}
	AddQuestRecord("Patria", "59");
	RemoveItems(pchar, "patent_fra", 1);
	ChangeCharacterComplexReputation(pchar, "nobility", -20);
	ChangeCharacterComplexReputation(pchar, "authority", -10);
	ChangeCharacterNationReputation(pchar, FRANCE, -30);
	pchar.questTemp.Patria = "fail";
	CloseQuestHeader("Patria");
	DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
}

void Patria_CuracaoSail() // формируем эскадру
{
	sld = characterFromId("Doily");
	SetCharacterRemovable(sld, false);
	sld.CompanionEnemyEnable = false; //всегда друзья
	SetCompanionIndex(pchar, -1, sti(sld.index));
	sld.loyality = MAX_LOYALITY;
	LAi_SetImmortal(sld, false);
	pchar.questTemp.Patria.Trafalgar = "true";
	for(int i = 1; i <= 2; i++) 
	{
		sld = characterFromId("Patria_DoilySquadronCap_"+i);
		SetCharacterRemovable(sld, false);
		sld.CompanionEnemyEnable = false; //всегда друзья
		SetCompanionIndex(pchar, -1, sti(sld.index));
		sld.loyality = MAX_LOYALITY;
		LAi_SetImmortal(sld, false);
	}
	// удаление группы д'Ойли
	pchar.quest.Patria_DoyliDelGroup.win_condition.l1 = "ExitFromLocation";
	pchar.quest.Patria_DoyliDelGroup.win_condition.l1.location = pchar.location;
	pchar.quest.Patria_DoyliDelGroup.function = "Patria_DoilyDelGroup";
	if (!bImCasual) SetFunctionTimerCondition("Patria_SanMartinBaronOver", 0, 0, 20, false); // таймер на 20 дней, чтобы не занимался посторонними делами, иначе будет бабах
	else NewGameTip(StringFromKey("Patria_26"));
	
	pchar.quest.Patria_CuracaoEnter.win_condition.l1 = "location";
	pchar.quest.Patria_CuracaoEnter.win_condition.l1.location = "Curacao";
	pchar.quest.Patria_CuracaoEnter.function = "Patria_CuracaoEnter";
	// форт Виллемстада
	sld = CharacterFromID("Villemstad Fort Commander");
	LAi_SetImmortal(sld, false);
}

void Patria_DoilyDelGroup(string qName) // 
{
	Group_DeleteGroup("Patria_DoilySquadron");
}

void Patria_CuracaoEnter(string qName) // пришли к Кюрасао
{
	pchar.quest.Patria_SanMartinBaronOver.over = "yes"; // снять таймер
	bQuestDisableMapEnter = true;//закрыть карту
	Island_SetReloadEnableGlobal("Curacao", true); //закрыть остров
	pchar.questTemp.Patria.CuracaoAttack = "true";
	if (pchar.nation != FRANCE) Flag_FRANCE();
	pchar.DisableChangeFlagMode = true; //закрываем Флаг
	// ставим две группы голландцев
	int iShip, iCannon;
	string sModel;
	Group_DeleteGroup("Patria_CuracaoGroup1");
	Group_FindOrCreateGroup("Patria_CuracaoGroup1");
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	if (iRank > 45) iRank = 45;
	for (int i = 1; i <= 3; i++)
    {
		switch (i)
		{
			case 1: 
				iShip = SHIP_GALEON_H;
				iCannon = CANNON_TYPE_CANNON_LBS32;	
				sModel = "off_hol_5";
			break;
			case 2: 
				iShip = SHIP_FRIGATE_H; 
				iCannon = CANNON_TYPE_CANNON_LBS32;
				sModel = "off_hol_2";
			break;
			case 3: 
				iShip = SHIP_FRIGATE; 
				iCannon = CANNON_TYPE_CANNON_LBS24;
				sModel = "off_hol_1";
			break;
		}
		sld = GetCharacter(NPC_GenerateCharacter("Patria_CuracaoCap1_"+i, sModel, "man", "man", iRank, HOLLAND, -1, true, "quest"));
		FantomMakeCoolSailor(sld, iShip, "", iCannon, 70, 70, 70);
		FantomMakeCoolFighter(sld, iRank, 70, 70, LinkRandPhrase("blade_17","blade_20","blade_21"), "pistol5", "bullet", 250);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.AlwaysEnemy = true;
		sld.Coastal_Captain = true;
		sld.Ship.Mode = "war";
		sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Sailors = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*6;
		if (MOD_SKILL_ENEMY_RATE > 2) SetCharacterPerk(sld, "MusketsShoot");
		sld.AnalizeShips = true;
		sld.WatchFort = true; //видеть форты
		if (i == 1) sld.ship.name = StringFromKey("Patria_12");
		Group_AddCharacter("Patria_CuracaoGroup1", "Patria_CuracaoCap1_"+i);
	}
	Group_SetGroupCommander("Patria_CuracaoGroup1", "Patria_CuracaoCap1_1");
	Group_SetAddress("Patria_CuracaoGroup1", "Curacao", "quest_ships", "quest_ship_2");
	Group_SetTaskAttack("Patria_CuracaoGroup1", PLAYER_GROUP);
	Group_LockTask("Patria_CuracaoGroup1");
	// вторая
	Group_DeleteGroup("Patria_CuracaoGroup2");
	Group_FindOrCreateGroup("Patria_CuracaoGroup2");
	for (i = 1; i <= 3; i++)
    {
		switch (i)
		{
			case 1: 
				iShip = SHIP_XebekVML;
				iCannon = CANNON_TYPE_CANNON_LBS16;	
				sModel = "off_hol_3";
			break;
			case 2: 
				iShip = SHIP_BRIGANTINE; 
				iCannon = CANNON_TYPE_CANNON_LBS12;
				sModel = "off_hol_2";
			break;
			case 3: 
				iShip = SHIP_SCHOONER_W; 
				iCannon = CANNON_TYPE_CANNON_LBS12;
				sModel = "off_hol_1";
			break;
		}
		sld = GetCharacter(NPC_GenerateCharacter("Patria_CuracaoCap2_"+i, sModel, "man", "man", iRank, HOLLAND, -1, true, "quest"));
		FantomMakeCoolSailor(sld, iShip, "", iCannon, 70, 70, 70);
		FantomMakeCoolFighter(sld, iRank, 70, 70, LinkRandPhrase("blade_09","blade_13","blade_15"), "pistol5", "bullet", 200);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		sld.Coastal_Captain = true;
		sld.Ship.Mode = "war";
		sld.AlwaysEnemy = true;
		sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Sailors = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*6;
		sld.AnalizeShips = true;
		sld.WatchFort = true; //видеть форты
		Group_AddCharacter("Patria_CuracaoGroup2", "Patria_CuracaoCap2_"+i);
	}
	Group_SetGroupCommander("Patria_CuracaoGroup2", "Patria_CuracaoCap2_1");
	Group_SetAddress("Patria_CuracaoGroup2", "Curacao", "quest_ships", "quest_ship_1");
	Group_SetTaskAttack("Patria_CuracaoGroup2", PLAYER_GROUP);
	Group_LockTask("Patria_CuracaoGroup2");
	// прерывание на уничтожение эскадры
	pchar.quest.Patria_CuracaoAfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Patria_CuracaoAfterBattle.win_condition.l1.group = "Patria_CuracaoGroup1";
	pchar.quest.Patria_CuracaoAfterBattle.win_condition.l2 = "Group_Death";
	pchar.quest.Patria_CuracaoAfterBattle.win_condition.l2.group = "Patria_CuracaoGroup2";
	pchar.quest.Patria_CuracaoAfterBattle.function = "Patria_CuracaoAfterSeaBattle";
}

void Patria_CuracaoAfterSeaBattle(string qName) // эскадры охранения уничтожены
{
	Group_DeleteGroup("Patria_CuracaoGroup1");
	Group_DeleteGroup("Patria_CuracaoGroup2");
	pchar.questTemp.Patria.Curacao.SquadronDead = "true";
	if (CheckAttribute(pchar, "questTemp.Patria.Curacao.FortDead")) Patria_CuracaoTrooper(); // форт уничтожен, на высадку
}

void Patria_CuracaoFortDestroyed() // форт Кюрасао разрушен
{
	pchar.questTemp.Patria.Curacao.FortDead = "true";
	DeleteAttribute(pchar, "questTemp.Patria.CuracaoAttack");
	if (CheckAttribute(pchar, "questTemp.Patria.Curacao.SquadronDead")) Patria_CuracaoTrooper(); // эскадра уничтожена, на высадку
	else Log_Info(StringFromKey("Patria_27"));
}

void Patria_CuracaoTrooper() // высадка
{
	Log_Info(StringFromKey("Patria_28"));
	DoQuestFunctionDelay("Patria_CuracaoTrooperLand", 7.0);
}

void Patria_CuracaoTrooperLand(string qName) // высадка
{
	pchar.GenQuest.Hunter2Pause = true;
	pchar.GenQuest.CannotWait = true;
	locations[FindLocation("Shore23")].DisableEncounters = true;
	locations[FindLocation("Shore24")].DisableEncounters = true;
	locations[FindLocation("Villemstad_ExitTown")].DisableEncounters = true;
	locations[FindLocation("Curacao_jungle_01")].DisableEncounters = true;
	locations[FindLocation("Curacao_jungle_02")].DisableEncounters = true;
	locations[FindLocation("Curacao_jungle_03")].DisableEncounters = true;
	LocatorReloadEnterDisable("Villemstad_ExitTown", "reload4", true);
	LocatorReloadEnterDisable("Curacao_jungle_03", "reloadW_back", true);
	DoQuestReloadToLocation("Shore24", "reload", "sea", "Patria_CuracaoTrooperLand");
	setCharacterShipLocation(pchar, "shore24");
	setWDMPointXZ("shore24");
	// 2 пушки
	int n = Findlocation("shore24");
	locations[n].models.always.mortair1 = "mortair";
	Locations[n].models.always.mortair1.locator.group = "rld";
	Locations[n].models.always.mortair1.locator.name = "loc1";
	Locations[n].models.always.mortair1.tech = "DLightModel";
	locations[n].models.always.mortair2 = "mortair";
	Locations[n].models.always.mortair2.locator.group = "rld";
	Locations[n].models.always.mortair2.locator.name = "loc2";
	Locations[n].models.always.mortair2.tech = "DLightModel";
	// маленький сюрприз в пещере
	pchar.GenQuestBox.Curacao_Cave = true;
	pchar.GenQuestBox.Curacao_Cave.box2.money = 200000;
	pchar.GenQuestBox.Curacao_Cave.box2.items.gold_dublon = 1000;
	pchar.GenQuestBox.Curacao_Cave.box2.items.jewelry5 = 1000;
	pchar.GenQuestBox.Curacao_Cave.box2.items.jewelry6 = 2000;
}

void Patria_CuracaoGotoMarch() // 
{
	chrDisableReloadToLocation = false;
	LocatorReloadEnterDisable("shore24", "reload1_back", true);
	LocatorReloadEnterDisable("shore22", "reload1_back", true);
	LocatorReloadEnterDisable("Curacao_jungle_03", "reload2_back", true); // лесник
	for (int i=1; i<=15; i++)
	{
		sld = characterFromId("Curacao_eng_soldier_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	pchar.quest.Curacao_inShore.win_condition.l1 = "location";
	pchar.quest.Curacao_inShore.win_condition.l1.location = "Shore23";
	pchar.quest.Curacao_inShore.function = "Patria_CuracaoMarch";
	// рассоединяем эскадру
	Group_FindOrCreateGroup("Patria_DoilySquadron");
	sld = characterFromId("Doily");
	RemoveCharacterCompanion(pchar, sld);
	Group_AddCharacter("Patria_DoilySquadron", "Doily");
	sld.nation = ENGLAND;
	for(i = 1; i <= 2; i++)
	{
		if (GetCharacterIndex("Patria_DoilySquadronCap_"+i) != -1)
		{
			sld = characterFromId("Patria_DoilySquadronCap_"+i);
			RemoveCharacterCompanion(pchar, sld);
			Group_AddCharacter("Patria_DoilySquadron", "Patria_DoilySquadronCap_"+i);
			sld.nation = ENGLAND;
		}
	}
	Group_SetGroupCommander("Patria_DoilySquadron", "Doily");
	Group_SetAddress("Patria_DoilySquadron", "Curacao", "quest_ships", "quest_ship_1");
	Group_SetTaskNone("Patria_DoilySquadron");
	Group_LockTask("Patria_DoilySquadron");
	DeleteAttribute(pchar, "questTemp.Patria.Trafalgar");
}

void Patria_CuracaoMarch(string qName) // наш отряд в бухте
{
	int n = Findlocation("shore24");
	DeleteAttribute(&locations[n], "models.always.mortair1");
	DeleteAttribute(&locations[n], "models.always.mortair2");
	sld = characterFromId("Doily_land");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	for (int i=1; i<=15; i++)
	{
		sld = characterFromId("Curacao_eng_soldier_"+i);
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	// пушки
	n = Findlocation("Villemstad_ExitTown");
	locations[n].models.always.mortair1 = "mortair";
	Locations[n].models.always.mortair1.locator.group = "quest";
	Locations[n].models.always.mortair1.locator.name = "gun1";
	Locations[n].models.always.mortair1.tech = "DLightModel";
	locations[n].models.always.mortair2 = "mortair";
	Locations[n].models.always.mortair2.locator.group = "quest";
	Locations[n].models.always.mortair2.locator.name = "gun2";
	Locations[n].models.always.mortair2.tech = "DLightModel";
	// наша рота
	for (i=1; i<=15; i++)
	{
		if (i < 4) // мушкетеры, 3 шт
		{
			sld = GetCharacter(NPC_GenerateCharacter("Curacao_fra_soldier_"+i, "mush_fra_"+i, "man", "mushketer", 30, FRANCE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, 30, 60, 60, "", "mushket2", "cartridge", 170);
			LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
			sld.cirassId = Items_FindItemIdx("cirass1");
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Curacao_fra_soldier_"+i, "sold_fra_"+(rand(7)+1), "man", "man", 30, FRANCE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, 30, 60, 60, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 150);
			sld.cirassId = Items_FindItemIdx("cirass2");
		}
		ChangeCharacterAddressGroup(sld, "shore23", "goto", "goto1");
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorFollow(sld, pchar, "", -1);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
	}
	pchar.quest.Patria_CuracaoMarchX.win_condition.l1 = "location";
	pchar.quest.Patria_CuracaoMarchX.win_condition.l1.location = "Curacao_jungle_03";
	pchar.quest.Patria_CuracaoMarchX.function = "Patria_CuracaoJungleMarch";
	pchar.quest.Patria_CuracaoMarch.win_condition.l1 = "location";
	pchar.quest.Patria_CuracaoMarch.win_condition.l1.location = "Curacao_jungle_02";
	pchar.quest.Patria_CuracaoMarch.function = "Patria_CuracaoJungleMushketer"; // первый отряд голландцев
}

void Patria_CuracaoJungleMarch(string qName) // проходим пустую локацию
{
	for (int i=1; i<=15; i++)
	{
		sld = characterFromId("Curacao_fra_soldier_"+i);
		ChangeCharacterAddressGroup(sld, "Curacao_jungle_03", "reload", "reload3_back");
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorFollow(sld, pchar, "", -1);
	}
}

void Patria_CuracaoJungleMushketer(string qName) // первая боевка
{
	chrDisableReloadToLocation = true;
	for (int i=1; i<=15; i++)
	{
		sld = characterFromId("Curacao_fra_soldier_"+i);
		ChangeCharacterAddressGroup(sld, "Curacao_jungle_02", "reload", "reload1_back");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	LAi_group_Delete("EnemyFight");
	int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
	for (i=1; i<=9; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Curacao_hol1_soldier_"+i, "mush_hol_"+(rand(2)+4), "man", "mushketer", iRank, HOLLAND, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, iRank, 65, 65, "", "mushket2", "cartridge", 220);
		LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
		sld.cirassId = Items_FindItemIdx("cirass1");
		sld.MusketerDistance = 0;
		if (i < 7) ChangeCharacterAddressGroup(sld, "Curacao_jungle_02", "rld", "aloc"+(i+4));
		if (i >= 7) ChangeCharacterAddressGroup(sld, "Curacao_jungle_02", "rld", "aloc"+(i+5));
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Patria_CuracaoAfterJungleMushketer");
}

void Patria_CuracaoJungleBattle(string qName) // вторая боевка
{
	chrDisableReloadToLocation = true;
	for (int i=1; i<=15; i++)
	{
		if (GetCharacterIndex("Curacao_fra_soldier_"+i) != -1)
		{
			sld = characterFromId("Curacao_fra_soldier_"+i);
			ChangeCharacterAddressGroup(sld, "Curacao_jungle_01", "reload", "reload1_back");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	LAi_group_Delete("EnemyFight");
	int iRank = 18+MOD_SKILL_ENEMY_RATE*2;
	for (i=1; i<=15; i++)
	{
		if (i == 1) // офицер
		{
			sld = GetCharacter(NPC_GenerateCharacter("Curacao_hol2_soldier_"+i, "off_hol_4", "man", "man", iRank+5, HOLLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, 65, 65, LinkRandPhrase("blade_18","blade_19","blade_21"), "pistol6", "bullet", 230);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Curacao_hol2_soldier_"+i, "sold_hol_"+(rand(7)+9), "man", "man", iRank, HOLLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, 60, 60, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 180);
		}
		ChangeCharacterAddressGroup(sld, "Curacao_jungle_01", "reload", "reload3_back");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Patria_CuracaoAfterJungleBattle");
}

void Patria_CuracaoGateBattle(string qName) // в локации ворот
{
	chrDisableReloadToLocation = true;
	for (int i=1; i<=15; i++)
	{
		if (GetCharacterIndex("Curacao_fra_soldier_"+i) != -1)
		{
			sld = characterFromId("Curacao_fra_soldier_"+i);
			ChangeCharacterAddressGroup(sld, "Villemstad_ExitTown", "reload", "reload1_back");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", 2.0);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	sld = characterFromId("Doily_land");
	ChangeCharacterAddressGroup(sld, "Villemstad_ExitTown", "quest", "commander");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "TMP_FRIEND");
	for (i=1; i<=15; i++)
	{
		sld = characterFromId("Curacao_eng_soldier_"+i);
		if (i < 7) 
		{
			ChangeCharacterAddressGroup(sld, "Villemstad_ExitTown", "quest", "mush"+i);
			sld.MusketerDistance = 0;
		}
		if (i >= 7 && i < 14) 
		{
			ChangeCharacterAddressGroup(sld, "Villemstad_ExitTown", "quest", "sold"+i);
		}
		if (i >= 14) 
		{
			ChangeCharacterAddressGroup(sld, "Villemstad_ExitTown", "quest", "soldier"+(i-13));
		}
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, "TMP_FRIEND");
	}
	DoQuestFunctionDelay("Patria_CuracaoGateBattle1", 2.0);
}

void Patria_CuracaoGateBattle1(string qName) // 
{
	LAi_SetActorType(pchar);
	LAi_ActorRunToLocator(pchar, "quest", "hero", "Patria_CuracaoGateBattle1", -1);
	for (int i=1; i<=15; i++)
	{
		if (GetCharacterIndex("Curacao_fra_soldier_"+i) != -1)
		{
			sld = characterFromId("Curacao_fra_soldier_"+i);
			LAi_SetActorType(sld);
		}
	}
	int n = 0;
	for(i=1; i<=3; i++)
	{
		int idx = GetOfficersIndex(pchar, i);
		if(idx < 0) continue;
		sld = &Characters[idx];
		SetCharacterTask_Stay(sld);
		sld.chr_ai.tmpl = LAI_TMPL_STAY;
		n++;
	}
}

void Patria_CuracaoGateBattle2(string qName) // выскочили голландцы из ворот
{
	pchar.questTemp.Patria.Curacao.BoomGate1 = "true";
	LAi_group_Delete("EnemyFight");
	for (int i=1; i<=7; i++)
	{
		if (i == 1) // офицер
		{
			sld = GetCharacter(NPC_GenerateCharacter("Curacao_hol3_soldier_"+i, "off_hol_1", "man", "man", 20, HOLLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, 20, 65, 65, LinkRandPhrase("blade_18","blade_19","blade_21"), "pistol6", "bullet", 100);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Curacao_hol3_soldier_"+i, "sold_hol_"+(rand(7)+1), "man", "man", 15, HOLLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, 20, 60, 60, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 100);
		}
		ChangeCharacterAddressGroup(sld, "Villemstad_ExitTown", "reload", "reload4");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	DoQuestFunctionDelay("Patria_CuracaoGateBattleBoom1", 2.0);
}

void Patria_CuracaoGateBattleBoom1(string qName) // выстрел из пушки №1
{
	CreateLocationParticles("Bombard", "quest", "gun1", 1.0, -90, 0, "cannon_fire_2");
	if (CheckAttribute(pchar, "questTemp.Patria.Curacao.BoomGate3")) DoQuestFunctionDelay("Patria_CuracaoGateBattleExp3", 1.0);
	else DoQuestFunctionDelay("Patria_CuracaoGateBattleExp1", 1.0);
}

void Patria_CuracaoGateBattleBoom2(string qName) // выстрел из пушки №2
{
	CreateLocationParticles("Bombard", "quest", "gun2", 1.0, 0, -90, "cannon_fire_2");
	DoQuestFunctionDelay("Patria_CuracaoGateBattleExp2", 1.0);
}

void Patria_CuracaoGateBattleExp1(string qName) // взрыв от пушки №1
{
	CreateLocationParticles("ShipExplode", "quest", "boom1", 0, 0, 0, "boom");
	CreateLocationParticles("blast_dirt", "quest", "boom1", 0, 0, 0, "");
	CreateLocationParticles("blast_inv", "quest", "boom1", 0, 0, 0, "");
	if (CheckAttribute(pchar, "questTemp.Patria.Curacao.BoomGate1")) 
	{
		for (int i=1; i<=4; i++)
		{
			sld = characterFromId("Curacao_hol3_soldier_"+i);
			LAi_KillCharacter(sld);
		}
		DoQuestFunctionDelay("Patria_CuracaoGateBattleMush1", 0.5);
		DeleteAttribute(pchar, "questTemp.Patria.Curacao.BoomGate1");
	}
	if (CheckAttribute(pchar, "questTemp.Patria.Curacao.BoomGate2")) 
	{
		for (i=12; i<=15; i++)
		{
			sld = characterFromId("Curacao_hol7_soldier_"+i);
			LAi_KillCharacter(sld);
		}
		DoQuestFunctionDelay("Patria_CuracaoGateBattleRush", 0.5);
		DeleteAttribute(pchar, "questTemp.Patria.Curacao.BoomGate2");
	}
}

void Patria_CuracaoGateBattleExp2(string qName) // взрыв от пушки №2
{
	CreateLocationParticles("ShipExplode", "quest", "boom2", 0, 0, 0, "boom");
	CreateLocationParticles("blast_dirt", "quest", "boom2", 0, 0, 0, "");
	CreateLocationParticles("blast_inv", "quest", "boom2", 0, 0, 0, "");
	if (CheckAttribute(pchar, "questTemp.Patria.Curacao.BoomFort1")) 
	{
		for (int i=1; i<=5; i++)
		{
			sld = characterFromId("Curacao_hol4_soldier_"+i);
			LAi_KillCharacter(sld);
		}
		DoQuestFunctionDelay("Patria_CuracaoGateBattle4", 4.0);
		DeleteAttribute(pchar, "questTemp.Patria.Curacao.BoomFort1");
	}
	if (CheckAttribute(pchar, "questTemp.Patria.Curacao.BoomFort2")) 
	{
		for (i=1; i<=5; i++)
		{
			sld = characterFromId("Curacao_hol5_soldier_"+i);
			LAi_KillCharacter(sld);
		}
		DoQuestFunctionDelay("Patria_CuracaoGateBattle5", 7.0);
		DeleteAttribute(pchar, "questTemp.Patria.Curacao.BoomFort2");
	}
	if (CheckAttribute(pchar, "questTemp.Patria.Curacao.BoomFort3")) 
	{
		for (i=1; i<=5; i++)
		{
			sld = characterFromId("Curacao_hol6_soldier_"+i);
			LAi_KillCharacter(sld);
		}
		DoQuestFunctionDelay("Patria_CuracaoGateBattle6", 5.0);
		DeleteAttribute(pchar, "questTemp.Patria.Curacao.BoomFort3");
	}
}

void Patria_CuracaoGateBattleExp3(string qName) // взрыв от пушки №1 по городу
{
	PlaySound("Sea Battles_01\Swish_balls_06.wav");
	DoQuestFunctionDelay("Patria_CuracaoGateBattleExp33", 2.0);
}

void Patria_CuracaoGateBattleExp33(string qName) // взрыв от пушки №1 по городу
{
	CreateLocationParticles("", "quest", "boom1", 0, 0, 0, "boom");
	if (CheckAttribute(pchar, "questTemp.Patria.Curacao.BoomGate3")) DoQuestFunctionDelay("Patria_CuracaoGateBattleBoom1", 4.0);
	else DoQuestFunctionDelay("Patria_CuracaoTownBombingEnd", 2.5);
}

void Patria_CuracaoGateBattleMush1(string qName) // 
{
	for (int i=1; i<=3; i++)
	{
		sld = characterFromId("Curacao_eng_soldier_"+i);
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "shot", "Patria_CuracaoGateBattleMush1", 1.0);
	}
}

void Patria_CuracaoGateBattle3(string qName) // выскочили голландцы из форта
{
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "reload", "reload3_back");
	pchar.questTemp.Patria.Curacao.BoomFort1 = "true";
	LAi_group_Delete("EnemyFight");
	for (int i=1; i<=5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Curacao_hol4_soldier_"+i, "sold_hol_"+(rand(7)+1), "man", "man", 15, HOLLAND, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, 20, 60, 60, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 100);
		ChangeCharacterAddressGroup(sld, "Villemstad_ExitTown", "rld", "loc0");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	DoQuestFunctionDelay("Patria_CuracaoGateBattleBoom2", 2.0);
}

void Patria_CuracaoGateBattle4(string qName) // выскочили голландцы из форта
{
	pchar.questTemp.Patria.Curacao.BoomFort2 = "true";
	LAi_group_Delete("EnemyFight");
	for (int i=1; i<=5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Curacao_hol5_soldier_"+i, "sold_hol_"+(rand(7)+1), "man", "man", 15, HOLLAND, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, 20, 60, 60, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 100);
		ChangeCharacterAddressGroup(sld, "Villemstad_ExitTown", "rld", "loc0");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	DoQuestFunctionDelay("Patria_CuracaoGateBattleBoom2", 2.0);
}

void Patria_CuracaoGateBattle5(string qName) // выскочили голландцы из форта
{
	pchar.questTemp.Patria.Curacao.BoomFort3 = "true";
	LAi_group_Delete("EnemyFight");
	for (int i=1; i<=5; i++)
	{
		if (i == 1) // офицер
		{
			sld = GetCharacter(NPC_GenerateCharacter("Curacao_hol6_soldier_"+i, "off_hol_1", "man", "man", 20, HOLLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, 20, 65, 65, LinkRandPhrase("blade_18","blade_19","blade_21"), "pistol6", "bullet", 100);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Curacao_hol6_soldier_"+i, "sold_hol_"+(rand(7)+1), "man", "man", 15, HOLLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, 20, 60, 60, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 100);
		}
		ChangeCharacterAddressGroup(sld, "Villemstad_ExitTown", "rld", "loc0");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	DoQuestFunctionDelay("Patria_CuracaoGateBattleBoom2", 2.0);
}

void Patria_CuracaoGateBattle6(string qName) // выскочили голландцы из ворот
{
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "reload", "reload4");
	pchar.questTemp.Patria.Curacao.BoomGate2 = "true";
	LAi_group_Delete("EnemyFight");
	int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
	for (int i=1; i<=15; i++)
	{
		if (i == 1) // офицер
		{
			sld = GetCharacter(NPC_GenerateCharacter("Curacao_hol7_soldier_"+i, "off_hol_5", "man", "man", iRank, HOLLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, 70, 70, LinkRandPhrase("blade_18","blade_19","blade_21"), "pistol4", "bullet", 250);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Curacao_hol7_soldier_"+i, "sold_hol_"+(rand(7)+1), "man", "man", iRank, HOLLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, 65, 65, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 200);
		}
		ChangeCharacterAddressGroup(sld, "Villemstad_ExitTown", "reload", "reload4");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	DoQuestFunctionDelay("Patria_CuracaoGateBattleBoom1", 2.0);
}

void Patria_CuracaoGateBattleRush(string qName) // ручная боевка
{
	LAi_SetPlayerType(pchar);
	LAi_SetFightMode(pchar, true);
	// французы
	for (int i=1; i<=15; i++)
	{
		if (GetCharacterIndex("Curacao_fra_soldier_"+i) != -1)
		{
			sld = characterFromId("Curacao_fra_soldier_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	// офицеры
	int n = 0;
	for(i=1; i<=3; i++)
	{
		int idx = GetOfficersIndex(pchar, i);
		if(idx < 0) continue;
		sld = &Characters[idx];
		SetCharacterTask_FollowCharacter(sld, PChar); 
		n++;
	}
	if(GetOfficersQuantity(pchar) > 0)
	{
		pchar.OfficerAttRange = 35.0;
		OfficersFollow();
	}	
	// англичане
	for (i=1; i<=15; i++)
	{
		sld = characterFromId("Curacao_eng_soldier_"+i);
		if (i == 4 || i == 5 || i == 6 || i > 13) continue;
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	LAi_group_SetCheck("EnemyFight", "Patria_CuracaoGateBattleEnd");
}

void Patria_CuracaoTownBombing() // обстрел города
{
	LAi_SetActorType(pchar);
	LAi_ActorTurnToLocator(pchar, "reload", "reload4");
	pchar.questTemp.Patria.Curacao.BoomGate3 = "true";
	DoQuestFunctionDelay("Patria_CuracaoGateBattleBoom1", 5.0);
	DoQuestFunctionDelay("Patria_CuracaoTownBombingTime", 40.0);
	AddQuestRecord("Patria", "62");
}

void Patria_CuracaoTownBombingTime(string qName) // 
{
	DeleteAttribute(pchar, "questTemp.Patria.Curacao.BoomGate3");
}

void Patria_CuracaoTownBombingEnd(string qName) // 
{
	SetLaunchFrameFormParam(StringFromKey("Patria_29", NewStr()), "", 0, 5);
	LaunchFrameForm();
	WaitDate("", 0, 0, 0, 2, 10); //крутим время
	RecalculateJumpTable();
	StoreDayUpdate();
	RefreshWeather();
	RefreshLandTime();
	DoQuestFunctionDelay("Patria_CuracaoParlamenter", 5.0);
}

void Patria_CuracaoParlamenter(string qName) // парламентеры
{
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
	for (int i=1; i<=15; i++)
	{
		if (GetCharacterIndex("Curacao_fra_soldier_"+i) != -1)
		{
			sld = characterFromId("Curacao_fra_soldier_"+i);
			LAi_SetStayType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	for (i=1; i<=3; i++)
	{
		if (i == 1) // офицер
		{
			sld = GetCharacter(NPC_GenerateCharacter("Curacao_parlamenter_"+i, "off_hol_5", "man", "man", 20, HOLLAND, 5, false, "soldier"));
			FantomMakeCoolFighter(sld, 20, 65, 65, LinkRandPhrase("blade_18","blade_19","blade_21"), "pistol6", "bullet", 100);
			sld.Dialog.Filename = "Quest\Patria_NPC.c";
			sld.dialog.currentnode = "holoff";
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Curacao_parlamenter_"+i, "sold_hol_"+(rand(7)+9), "man", "man", 15, HOLLAND, 5, false, "soldier"));
			FantomMakeCoolFighter(sld, 20, 60, 60, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 100);
			LAi_CharacterDisableDialog(sld);
		}
		ChangeCharacterAddressGroup(sld, "Villemstad_ExitTown", "reload", "reload4");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	DoQuestCheckDelay("pchar_back_to_player", 4.0);
}

void Patria_CuracaoParlamenterGo() // парламентеры уходят
{
	for (int i=1; i<=3; i++)
	{
		sld = characterFromId("Curacao_parlamenter_"+i);
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload4", "none", "", "", "Patria_CuracaoStivesantWait", -1);
	}
}

void Patria_CuracaoStivesant(string qName) // Стайвесант
{
	// ставим Стайвесанта
	if (GetCharacterIndex("Stivesant") != -1)
	{
		sld = characterFromId("Stivesant");
	}
	else
	{
		sld = GetCharacter(NPC_GenerateCharacter("Stivesant", "huber_1", "man", "man_B", 35, HOLLAND, -1, false, "quest"));
		FantomMakeSmallSailor(sld, SHIP_GALEON_H, StringFromKey("Patria_12"), CANNON_TYPE_CANNON_LBS24, 100, 100, 100, 100, 100);
		FantomMakeCoolFighter(sld, 35, 90, 90, "blade_15", "pistol5", "bullet", 250);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.name = StringFromKey("Patria_13");
		sld.lastname = StringFromKey("Patria_14");
		sld.greeting = "Stivesant"; 
	}
	sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
	sld.dialog.currentnode = "Stivesant_33";
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Villemstad_ExitTown", "reload", "reload4");
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	for (int i=1; i<=3; i++)
	{
		sld = characterFromId("Curacao_parlamenter_"+i);
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "Villemstad_ExitTown", "reload", "reload4");
		LAi_ActorFollow(sld, characterFromID("Stivesant"), "", -1);
	}
}

void Patria_CuracaoStivesantGo() // Стайвесант уходит
{
	sld = characterFromId("Stivesant");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload4", "none", "", "", "Patria_CuracaoResult", -1);
	for (int i=1; i<=3; i++)
	{
		sld = characterFromId("Curacao_parlamenter_"+i);
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
	}
}

void Patria_CuracaoClear() // прибираемся немного
{
	chrDisableReloadToLocation = false;//открыть локацию
	pchar.GenQuest.Hunter2Pause = true;
	// меняем отношения наций
	pchar.questTemp.Patria.Neutral = "true";
	LaunchNationLegend();
	DeleteAttribute(pchar, "questTemp.Patria.Neutral");
	DoQuestCheckDelay("sea_victory", 0.2);
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
	LocatorReloadEnterDisable("Shore24", "reload1_back", false); // 17-add
	LocatorReloadEnterDisable("Shore22", "reload1_back", false); // 17-add
	LocatorReloadEnterDisable("Curacao_jungle_03", "reload2_back", false);// лесник
	sld = characterFromId("Doily_land");
	LAi_SetWarriorType(sld);
	LAi_CharacterDisableDialog(sld); // 14-add
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	for (int i=1; i<=15; i++)
	{
		sld = characterFromId("Curacao_eng_soldier_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	for (i=1; i<=15; i++)
	{
		if (GetCharacterIndex("Curacao_fra_soldier_"+i) != -1)
		{
			sld = characterFromId("Curacao_fra_soldier_"+i);
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(sld, "", -1);
		}
	}
	pchar.quest.Patria_CuracaoClear.win_condition.l1 = "EnterToSea";
	pchar.quest.Patria_CuracaoClear.function = "Patria_CuracaoClearLand";
}

void Patria_CuracaoClearLand(string qName) // продолжаем чистить
{
	Island_SetReloadEnableGlobal("Curacao", false);//закрыть остров
	bQuestDisableMapEnter = false;//открыть карту
	DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	for (int i=1; i<=15; i++)
	{
		if (GetCharacterIndex("Curacao_fra_soldier_"+i) != -1)
		{
			sld = characterFromId("Curacao_fra_soldier_"+i);
			sld.lifeday = 0;
		}
	}
	sld = characterFromId("Doily_land");
	sld.lifeday = 0;
	for (i=1; i<=15; i++)
	{
		sld = characterFromId("Curacao_eng_soldier_"+i);
		sld.lifeday = 0;
	}
	int n = Findlocation("Villemstad_ExitTown");
	DeleteAttribute(&locations[n], "models.always.mortair1");
	DeleteAttribute(&locations[n], "models.always.mortair2");
	locations[FindLocation("Shore23")].DisableEncounters = false;
	locations[FindLocation("Shore24")].DisableEncounters = false;
	locations[FindLocation("Villemstad_ExitTown")].DisableEncounters = false;
	locations[FindLocation("Curacao_jungle_01")].DisableEncounters = false;
	locations[FindLocation("Curacao_jungle_02")].DisableEncounters = false;
	locations[FindLocation("Curacao_jungle_03")].DisableEncounters = false;
	LocatorReloadEnterDisable("Curacao_jungle_03", "reloadW_back", false);
	LocatorReloadEnterDisable("Shore24", "reload1_back", false);
	LocatorReloadEnterDisable("Shore22", "reload1_back", false);
	LocatorReloadEnterDisable("Curacao_jungle_03", "reload2_back", false); // лесник вход ван-хато с джунглей
	// маленький сюрприз в пещере убираем, если не нашел
	pchar.GenQuestBox.Curacao_Cave = true;
	pchar.GenQuestBox.Curacao_Cave.box2.money = 1;
	pchar.GenQuestBox.Curacao_Cave.box2.items.Mineral26 = 1;
	pchar.quest.Patria_CuracaoClear1.win_condition.l1 = "MapEnter";
	pchar.quest.Patria_CuracaoClear1.function = "Patria_CuracaoComplete";
	DeleteAttribute(pchar, "DisableChangeFlagMode"); // 15-add
}

void Patria_CuracaoComplete(string qName) // заканчиваем чистить
{
	Group_SetAddress("Patria_DoilySquadron", "Jamaica", "quest_ships", "quest_ship_1");
	Group_DeleteGroup("Patria_DoilySquadron");
	sld = characterFromId("PortRoyal_Mayor");
	ChangeCharacterAddressGroup(sld, "PortRoyal_townhall", "sit", "sit1");
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	sld = characterFromId("Noel");
	ChangeCharacterAddressGroup(sld, "none", "", ""); // прячем инспектора
	pchar.questTemp.Patria = "epizode_11_return";
	SetFunctionTimerCondition("Patria_CuracaoRebuild", 0, 0, 5, false); // таймер на возврат Кюрасао в норму
}

void Patria_CuracaoRebuild(string qName) // Кюрасао в норму
{
	Island_SetReloadEnableGlobal("Curacao", true);//открыть остров
	sld = CharacterFromID("Villemstad Fort Commander");
	Character_SetAbordageEnable(sld, true);
	LocatorReloadEnterDisable("Villemstad_ExitTown", "reload4", false);
	sld = characterFromId("Stivesant");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
	ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "sit", "sit1");
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
}

//--------------------------------------------------------------- 12 эпизод ----------------------------------------------------------
void Patria_CondotierStart() //
{
	// отсоединяем Эклятон
	if (!CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
	{
		sld = characterFromId("Ecliaton_Cap");
		sld.ShipHideImmortal = 1000; // непотопляемый корабль
		RemoveCharacterCompanion(pchar, sld);
		sld.AlwaysFriend = true;
		sld.ShipEnemyDisable = true;
		Group_AddCharacter("Ecliaton_group", "Ecliaton_Cap");
		Group_SetGroupCommander("Ecliaton_group", "Ecliaton_Cap");
		Group_SetAddress("Ecliaton_group", "Nevis", "quest_ships", "quest_ship_1");
		Group_SetTaskNone("Ecliaton_group");
		Group_LockTask("Ecliaton_group");
		SetFunctionTimerCondition("Patria_EcliatonRepair", 0, 0, 5, false); // таймер на починку Эклятона
		DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
		Achievment_Set("ach_79");
	}
	SetFunctionTimerCondition("Patria_CondotierToPuancie", 0, 0, 30, false); // таймер
}

void Patria_Tailor(string qName)
{
    ref sld = GetCharacter(NPC_GenerateCharacter("Patria_Tailor", "citiz_6", "man", "man", 10, FRANCE, -1, true, "citizen"));
	sld.Dialog.Filename = "Quest\Patria_NPC.c";
	sld.dialog.currentnode = "Tailor";
	sld.name = StringFromKey("Patria_30");
	sld.lastname = StringFromKey("Patria_31");
	RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed");
	ChangeCharacterAddressGroup(sld, "Charles_PortOffice", "goto", "goto2");
	LAi_SetActorType(sld);
	LAi_ActorDialogDelay(sld, pchar, "", 1.2);
	chrDisableReloadToLocation = true;
}

void Patria_Tailor_Done(string qName)
{
    pchar.questTemp.PatriaTailorDone = true;
}

void Patria_CondotierToPuancie(string qName) // месяц прошёл, к Пуанси
{
	pchar.questTemp.Patria = "epizode_12_continue";
	AddQuestRecord("Patria", "66");
	Group_DeleteGroup("Ecliaton_group"); // Эклятон ушёл в Европу
}

void Patria_CondotierSail() // 
{
	sld = CharacterFromID("Noel");
	sld.dialog.currentnode = "noel_28";
	ChangeCharacterAddressGroup(sld, "PortPax_townhall", "goto", "governor1");
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
}

void Patria_CondotierToPirates(string qName) // 
{
	DoQuestReloadToLocation("Portpax_tavern", "tables", "stay3", "Patria_CondotierToPirates");
}

void Patria_CondotierTimeOver(string qName) // две недели прошли
{
	if (CheckAttribute(pchar, "questTemp.Patria.Condotier.Success"))
	{
		SetFunctionTimerCondition("Patria_CondotierTimeToGo", 0, 0, 9, false);
	}
	else // провалили
	{
		AddQuestRecord("Patria", "69");
		pchar.questTemp.Patria.Arest = "true";
		//pchar.questTemp.Patria = "fail";
		CloseQuestHeader("Patria");
		DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
		SetFunctionTimerCondition("Patria_Arest", 0, 0, 180, false); // арест через полгода
	}
}

void Patria_CondotierTimeToGo(string qName) // пора идти к пиратскому барону
{
	if (CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") || CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) 
	{
		AddQuestRecord("Patria", "72_1");
		LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
	}
	else
	{
		AddQuestRecord("Patria", "72_2");
		LocatorReloadEnterDisable("Lavega_town", "reload6", false);
	}
	pchar.questTemp.Patria = "epizode_12_talk";
}

void Patria_CondotierTerks(string qName) // на Терксе
{
	pchar.quest.Patria_Condotier_Terks.win_condition.l1 = "location";
	pchar.quest.Patria_Condotier_Terks.win_condition.l1.location = "Shore56";
	pchar.quest.Patria_Condotier_Terks.function = "Patria_CondotierOnTerks";
	LAi_LocationDisableOfficersGen("Shore56", true);//офицеров не пускать
	if (CheckAttribute(pchar, "questTemp.Patria.Saga.Shark"))
	{
		// ставим корабль Додсона
		Group_FindOrCreateGroup("DodsonFrigate");
		sld = GetCharacter(NPC_GenerateCharacter("Dodson_sea", "Shark", "man", "man", 45, PIRATE, -1, true, "quest"));
		FantomMakeCoolSailor(sld, SHIP_FRIGATE_H, StringFromKey("Patria_32"), CANNON_TYPE_CANNON_LBS32, 105, 105, 105);
		FantomMakeCoolFighter(sld, 45, 100, 100, "blade_21", "pistol5", "bullet", 100);
		sld.name = StringFromKey("Patria_33");
		sld.lastname = StringFromKey("Patria_34"); //14-add
		sld.Abordage.Enable = false;
		sld.AlwaysFriend = true;
		sld.ShipEnemyDisable = true; 
		LAi_SetImmortal(sld, true); // сплошная защита от дурака
		sld.DontDeskTalk = true;
		sld.nation = PIRATE;
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		Group_AddCharacter("DodsonFrigate", "Dodson_sea");
		Group_SetGroupCommander("DodsonFrigate", "Dodson_sea");
		Group_SetTaskNone("DodsonFrigate");
		Group_SetAddress("DodsonFrigate", "Terks", "quest_ships", "quest_ship_2");
		Group_LockTask("DodsonFrigate");
	}
	else
	{
		// ставим корабль Тиракса
		Group_FindOrCreateGroup("DodsonFrigate");
		sld = GetCharacter(NPC_GenerateCharacter("Terrax_sea", "Terrax", "man", "man", 45, PIRATE, -1, true, "quest"));
		FantomMakeCoolSailor(sld, SHIP_LINESHIP, StringFromKey("Patria_35"), CANNON_TYPE_CULVERINE_LBS36, 110, 110, 110);
		FantomMakeCoolFighter(sld, 45, 100, 100, "blade_21", "pistol5", "bullet", 100);
		sld.name = StringFromKey("Patria_36");
		sld.lastname = StringFromKey("Patria_37"); //14-add
		sld.Abordage.Enable = false;
		sld.AlwaysFriend = true;
		sld.ShipEnemyDisable = true; 
		LAi_SetImmortal(sld, true); // сплошная защита от дурака
		sld.DontDeskTalk = true;
		sld.nation = PIRATE;
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;
		SetSailsColor(sld, 8);//черный парус
		Group_AddCharacter("DodsonFrigate", "Terrax_sea");
		Group_SetGroupCommander("DodsonFrigate", "Terrax_sea");
		Group_SetTaskNone("DodsonFrigate");
		Group_SetAddress("DodsonFrigate", "Terks", "quest_ships", "quest_ship_2");
		Group_LockTask("DodsonFrigate");
	}
}

void Patria_CondotierOnTerks(string qName) // на Терксе
{
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], true);//запретить драться
	LAi_LocationDisableOfficersGen("Shore56", true);//офицеров не пускать
	if (CheckAttribute(pchar, "questTemp.Patria.Saga.Shark")) sld = CharacterFromID("Dodson");
	else sld = CharacterFromID("Terrax");
	sld.dialog.currentnode = "patria_15";
	ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto5");
	LAi_SetActorType(sld);
	LAi_SetActorType(pchar);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
	LAi_ActorTurnToCharacter(sld, pchar);
	SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
	//LAi_ActorDialogDelay(sld, pchar, "", 4.0);
	sld = CharacterFromID("Noel");
	ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto12");
	LAi_SetActorType(sld);
	sld = GetCharacter(NPC_GenerateCharacter("Terks_pirat", "mush_ctz_9", "man", "mushketer", 30, PIRATE, 2, false, "soldier"));
	FantomMakeCoolFighter(sld, 30, 60, 60, "", "mushket1", "cartridge", 170);
	ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto6");
	LAi_SetActorType(sld);
}

void Patria_CondotierTerksOver(string qName) // нельзя заставлять ждать
{
	pchar.quest.Patria_Condotier_Terks.over = "yes"; //снять прерывание
	Group_DeleteGroup("DodsonFrigate");
	DoQuestCheckDelay("Patria_CondotierDodsonNorm", 1.0);
	if (CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax")) DoQuestCheckDelay("Patria_CondotierTerraxNorm", 1.0); // Ла Вега
	else DoQuestCheckDelay("Patria_CondotierDodsonNorm", 1.0);
	pchar.questTemp.Patria.DodsonFail = "true";
	LAi_LocationDisableOfficersGen("Shore56", false);
}

void Patria_CondotierEnCapstervil(string qName) // пришли в Капстервиль с бароном
{
	chrDisableReloadToLocation = true;
	LocatorReloadEnterDisable("Charles_town", "reload3_back", true); // закрыть на сутки резиденцию
	sld = CharacterFromID("Noel");
	sld.dialog.currentnode = "noel_final";
	RemovePassenger(pchar, sld);
	ChangeCharacterAddressGroup(sld, "Charles_town", "quest", "quest1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Patria_CondotierPuancieFinal(string qName) // пора к Пуанси
{
	LocatorReloadEnterDisable("Charles_town", "reload3_back", false); 
	Island_SetReloadEnableGlobal("Bermudes", true);
}

void Patria_CondotierToCabin(string qName) // 
{
	DoQuestReloadToLocation("Portpax_tavern", "tables", "stay3", "Patria_CondotierToCabin");
}

void Patria_CondotierInCabin(string qName) // 
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = CharacterFromID("Noel");
	sld.dialog.currentnode = "noel_62";
	ChangeCharacterAddressGroup(sld, pchar.location, "rld", "aloc0");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
	ChangeCharacterAddressGroup(sld, pchar.location, "rld", "aloc1");
	LAi_SetActorType(sld);
}

void Patria_CondotierInCabinTalk(string qName) // 
{
	SetLaunchFrameFormParam(StringFromKey("Patria_38", NewStr()), "", 0, 5);
	LaunchFrameForm();
	WaitDate("", 0, 0, 0, 2, 10); //крутим время
	RecalculateJumpTable();
	StoreDayUpdate();
	RefreshWeather();
	RefreshLandTime();
	DoQuestFunctionDelay("Patria_CondotierInCabinResult", 5.0);
}

void Patria_CondotierInCabinResult(string qName) // 
{
	sld = CharacterFromID("Noel");
	sld.dialog.currentnode = "noel_64";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 5.0);
}

void Patria_CondotierToMine(string qName) // в бухте Гранд Кейс, идем на рудник
{
	pchar.GenQuest.Hunter2Pause = true;
	pchar.GenQuest.CannotWait = true;
	LocatorReloadEnterDisable("Shore40", "reload2_back", false);
	LocatorReloadEnterDisable("Shore40", "reload1_back", true);
	LocatorReloadEnterDisable("Shore40", "boat", true);
	sld = CharacterFromID("Noel");
	sld.dialog.currentnode = "noel_74";
	ChangeCharacterAddressGroup(sld, "Shore40", "goto", "goto8");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Patria_CondotierInMine(string qName) // на руднике
{
	chrDisableReloadToLocation = true;//закрыть локацию
	FreeSitLocator("Location_reserve_03", "patrol19");
	FreeSitLocator("Location_reserve_03", "patrol20");
	LAi_SetActorType(pchar);
	LAi_ActorRunToLocator(pchar, "goto", "goto26", "Patria_CondotierInMine", -1);
}

void Patria_CondotierBaronFail(string qName) // барон помер от избытка времени
{
	sld = CharacterFromID("Noel");
	RemovePassenger(pchar, sld);
	sld.lifeday = 0;
	log_info(StringFromKey("Patria_39"));
	AddQuestRecord("Patria", "75_1");
	pchar.questTemp.Patria = "epizode_12_baronfail";
}

void Patria_CondotierBeachFight(string qName) // бой на пляже
{
	LAi_LocationFightDisable(&Locations[FindLocation("Location_reserve_01")], false);
	LAi_group_Delete("EnemyFight");
	sld = CharacterFromID("Noel");
	LAi_SetImmortal(sld, false);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	for (int i=1; i<=5; i++)
	{
		sld = CharacterFromID("Marigo_eng_soldier_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Patria_CondotierBeachAfterFight");
	LAi_SetFightMode(pchar, true);
	pchar.quest.Patria_Baron_killed.win_condition.l1 = "NPC_Death";
	pchar.quest.Patria_Baron_killed.win_condition.l1.character = "Noel";
	pchar.quest.Patria_Baron_killed.function = "Patria_CondotierBaronKilled";
}

void Patria_CondotierBaronKilled(string qName) // барон помер от сабли или пули
{
	pchar.questTemp.Patria.Condotier.BaronKilled = "true"; 
}

void Patria_CondotierInShore40(string qName) // 
{
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("Noel");
	sld.dialog.currentnode = "noel_79";
	ChangeCharacterAddressGroup(sld, "Shore40", "goto", "goto2");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Patria_CondotierOnCuracao(string qName) // 
{
	pchar.quest.Patria_CondotierBaronFail.over = "yes"; //снять прерывание
	LAi_LocationFightDisable(&Locations[FindLocation("shore22")], true);
	chrDisableReloadToLocation = true;
	sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
	sld.Dialog.Filename = "Quest\Patria_NPC.c";
	sld.dialog.currentnode = "miner";
	LAi_CharacterEnableDialog(sld);
	ChangeCharacterAddressGroup(sld, "Shore22", "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	LocatorReloadEnterDisable("Location_reserve_01", "reload1_back", false); //14-add
}

void Patria_CondotierStivesant(string qName) // приходит Стайвесант
{
	if (pchar.location != "shore22") return; // тут глюк
	sld = CharacterFromID("Noel");
	LAi_SetActorType(sld);
	LAi_ActorTurnToLocator(sld, "reload", "reload1");
	// перекидываем пчар на инспектора
	LAi_SetActorType(pchar);
	SetMainCharacterIndex(GetCharacterIndex("Noel"));
	pchar = GetMainCharacter();			
	LAi_SetPlayerType(pchar);
	locCameraTarget(pchar);
	locCameraFollow();
	StartQuestMovie(true, true, true);
	if (GetCharacterIndex("Stivesant") != -1)
	{
		sld = characterFromId("Stivesant");
	}
	else
	{
		sld = GetCharacter(NPC_GenerateCharacter("Stivesant", "huber_1", "man", "man_B", 35, HOLLAND, -1, false, "quest"));
		FantomMakeSmallSailor(sld, SHIP_GALEON_H, StringFromKey("Patria_12"), CANNON_TYPE_CANNON_LBS24, 100, 100, 100, 100, 100);
		FantomMakeCoolFighter(sld, 35, 90, 90, "blade_15", "pistol5", "bullet", 250);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.name = StringFromKey("Patria_13");
		sld.lastname = StringFromKey("Patria_14");
		sld.greeting = "Stivesant";
		sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
	}
	sld.dialog.currentnode = "Stivesant_42";
	ChangeCharacterAddressGroup(sld, "Shore22", "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	for (int i=1; i<=3; i++)
	{
		if (i == 1) // офицер
		{
			sld = GetCharacter(NPC_GenerateCharacter("Stivesant_sold_"+i, "off_hol_5", "man", "man", 20, HOLLAND, 5, false, "soldier"));
			FantomMakeCoolFighter(sld, 20, 65, 65, LinkRandPhrase("blade_18","blade_19","blade_21"), "pistol6", "bullet", 100);
			LAi_CharacterDisableDialog(sld);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Stivesant_sold_"+i, "sold_hol_"+(rand(7)+9), "man", "man", 15, HOLLAND, 5, false, "soldier"));
			FantomMakeCoolFighter(sld, 20, 60, 60, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 100);
			LAi_CharacterDisableDialog(sld);
		}
		ChangeCharacterAddressGroup(sld, "Shore22", "reload", "reload1_back");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void Patria_CondotierCabin(string qName) // 
{
	bQuestDisableMapEnter = true;//закрыть карту
	Island_SetReloadEnableGlobal("Curacao", false);
	pchar.GenQuest.MapClosedNoBattle = true; 
	DoQuestFunctionDelay("Patria_CondotierToCabinAgain", 1.5);
}

void Patria_CondotierToCabinAgain(string qName) // в каюту
{
	Sea_CabinStartNow();
	DoQuestFunctionDelay("Patria_CondotierInCabinAgain", 1.8);
}

void Patria_CondotierInCabinAgain(string qName) // в каюту
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = characterFromId("Noel");
	sld.dialog.currentnode = "noel_90";
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Patria_CondotierBaronWin(string qName) // 
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = characterFromId("Noel");
	sld.dialog.currentnode = "noel_96";
	RemovePassenger(pchar, sld);
	ChangeCharacterAddressGroup(sld, "Charles_town", "quest", "quest1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Patria_CondotierStivesantTimeOver(string qName) // просрочка таймера Стайвесанта
{
	AddQuestRecord("Patria", "88");
	RemoveItems(pchar, "patent_fra", 1);
	ChangeCharacterComplexReputation(pchar, "nobility", -60);
	ChangeCharacterComplexReputation(pchar, "authority", -20);
	ChangeCharacterNationReputation(pchar, FRANCE, -200);
	ChangeCharacterNationReputation(pchar, ENGLAND, -100);
	pchar.questTemp.Patria = "fail";
	CloseQuestHeader("Patria");
	DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
	pchar.quest.Patria_CondotierRemove_baron.win_condition.l1 = "Location_Type";
	pchar.quest.Patria_CondotierRemove_baron.win_condition.l1.location_type = "town";
	pchar.quest.Patria_CondotierRemove_baron.function = "Patria_CondotierRemoveBaron";
	LocatorReloadEnterDisable("Charles_townhall", "reload3", true); // закрыть вход к Пуанси
	sld = characterFromId("Stivesant");
	ChangeCharacterAddressGroup(sld, "none", "", "");
}

void Patria_CondotierRemoveBaron(string qName) // 
{
	sld = characterFromId("Noel");
	RemovePassenger(pchar, sld);
	sld.lifeday = 0;
	log_info(StringFromKey("Patria_10"));
	
}

void Patria_EuropeTime(string qName) // 
{
	pchar.quest.Patria_Europe_Time.win_condition.l1 = "Location_Type";
	pchar.quest.Patria_Europe_Time.win_condition.l1.location_type = "town";
	pchar.quest.Patria_Europe_Time.function = "Patria_EuropeCureer";
	DeleteAttribute(pchar, "questTemp.Patria.Governor"); // доходы от Пуанси прекратились
}

void Patria_EuropeCureer(string qName) // 
{
	chrDisableReloadToLocation = true;//закрыть локацию
	DoQuestFunctionDelay("Patria_EuropeSetCureer", 2.0);
}

void Patria_EuropeSetCureer(string qName) // 
{
	float locx, locy, locz;
	sld = GetCharacter(NPC_GenerateCharacter("Europe_cureer", "citiz_32", "man", "man", 10, FRANCE, -1, false, "soldier"));
	FantomMakeCoolFighter(sld, 10, 20, 20, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 100);
	sld.Dialog.Filename = "Quest\Patria_NPC.c";
	sld.dialog.currentnode = "cureer";
	LAi_SetImmortal(sld, true);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Patria_EuropePrepare() // готовим всех персонажей
{
	AddQuestRecord("Patria", "89");
	// Пуанси в тюрьму
	sld = characterFromId("Puancie");
	sld.dialog.currentnode = "patria_prison";
	sld.greeting = "";
	LAi_SetStayType(sld);
	RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
	RemoveCharacterEquip(sld, CIRASS_ITEM_TYPE);
	ChangeCharacterAddressGroup(sld, "Charles_prison", "goto", "goto9");
	LocatorReloadEnterDisable("Charles_town", "reload_jail", true);
	// барона в резиденцию
	sld = characterFromId("Noel");
	sld.dialog.currentnode = "noel_98";
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, "Charles_roomtownhall", "goto", "goto6");
	// заместитель министра финансов
	sld = GetCharacter(NPC_GenerateCharacter("Finansist", "off_fra_6", "man", "man", 25, FRANCE, -1, false, "officer"));
	FantomMakeCoolFighter(sld, 25, 80, 80, "blade_17", "pistol5", "bullet", 120);
	sld.Dialog.Filename = "Quest\Patria_NPC.c";
	sld.dialog.currentnode = "burden";
	sld.name = StringFromKey("Patria_40");
	sld.lastname = StringFromKey("Patria_41");
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Charles_roomtownhall", "goto", "goto4");
	LAi_SetActorType(sld);
}

void Patria_EuropePuancieClear(string qName) // 
{
	sld = characterFromId("Puancie");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld = characterFromId("Finansist");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld.lifeday = 0;
	// рудник
	for (int i=1; i<=15; i++) // солдаты
	{
		sld = characterFromId("MarigoMine_soldier_"+i);
		sld.model = "sold_fra_"+(rand(7)+1);
		sld.nation = FRANCE;
	}
}

void Patria_EuropeFinal(string qName) // 
{
	chrDisableReloadToLocation = true;//закрыть локацию
	sld = characterFromId("Noel");
	sld.dialog.currentnode = "noel_103";
	ChangeCharacterAddressGroup(sld, "charles_town", "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Patria_EuropeMusic(string qName) // 7-add
{
	SetMusic("music_alcove_1");
}

void Patria_BugsFixer() // 17-add
{
	if (GetCharacterIndex("Mary") != -1)
	{
		sld = characterFromId("Mary");
		sld.name = StringFromKey("Patria_42");
		sld.lastname = StringFromKey("Patria_43");
	}
	DeleteAttribute(pchar, "DisableChangeFlagMode"); // открываем флаг
	if (CheckAttribute(pchar, "questTemp.Patria.BugsFixer")) DeleteAttribute(pchar, "questTemp.Patria.BugsFixer");
	pchar.questTemp.Patria_BugsFixer = "true";
}

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool Patria_QuestComplete(string sQuestName, string qname)
{
/// Jason ----------------------------------------------------------- На службе Отечеству ------------------------------------------------------------------

	ref sld;
	int  i, n;
	
	bool condition = true;
	
	if (sQuestName == "Patria_VisiterTortuga") //
	{
		sld = characterFromId("Noel");
		RemovePassenger(pchar, sld);
		AddQuestRecord("Patria", "11");
		LocatorReloadEnterDisable("Tortuga_town", "reload3_back", true);
		pchar.quest.Patria_Visiter_TortugaBack.win_condition.l1 = "Timer";
		pchar.quest.Patria_Visiter_TortugaBack.win_condition.l1.date.hour  = sti(GetTime());
		pchar.quest.Patria_Visiter_TortugaBack.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
		pchar.quest.Patria_Visiter_TortugaBack.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
		pchar.quest.Patria_Visiter_TortugaBack.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
		pchar.quest.Patria_Visiter_TortugaBack.function = "Patria_VisiterTortugaBack";
	}
	else if (sQuestName == "Patria_VisiterPortPax") //
	{
		sld = characterFromId("Noel");
		RemovePassenger(pchar, sld);
		AddQuestRecord("Patria", "13");
		LocatorReloadEnterDisable("Portpax_town", "reload3_back", true);
		pchar.quest.Patria_Visiter_PortpaxBack.win_condition.l1 = "Timer";
		pchar.quest.Patria_Visiter_PortpaxBack.win_condition.l1.date.hour  = sti(GetTime());
		pchar.quest.Patria_Visiter_PortpaxBack.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
		pchar.quest.Patria_Visiter_PortpaxBack.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
		pchar.quest.Patria_Visiter_PortpaxBack.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
		pchar.quest.Patria_Visiter_PortpaxBack.function = "Patria_VisiterPortPaxBack";
	}
	else if (sQuestName == "Patria_StivesantWait") //
	{
		SetLaunchFrameFormParam(StringFromKey("Patria_38", NewStr()), "", 0, 5);
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 2, 10); //крутим время
		RecalculateJumpTable();
		StoreDayUpdate();
		RefreshWeather();
		RefreshLandTime();
		DoQuestFunctionDelay("Patria_StivesantWait", 5.0);
	}
	else if (sQuestName == "Patria_StivesantSit") //
	{
		sld = characterFromId("Stivesant");
		ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "sit", "sit1");
		LAi_SetHuberType(sld);
		LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	}
	else if (sQuestName == "Patria_SanMartinSetBaron") //
	{
		sld = characterFromId("Noel");
		LAi_SetStayType(sld);
	}
	else if (sQuestName == "Patria_SanMartinBaron") //
	{
		chrDisableReloadToLocation = false;
		bQuestDisableMapEnter = false;//открыть карту
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		AddQuestRecord("Patria", "26");
		SetFunctionTimerCondition("Patria_SanMartinBaronOver", 0, 0, 7, false); // таймер
		sld = characterFromId("Noel");
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, false);
		// атрибуты на Синт-Маартен
		pchar.questTemp.Patria.SanMartinFort = "true"; // атака
		n = FindIsland("SentMartin");
		Islands[n].reload.l1.radius = 0.0; // закрыть высадку в порту
		LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", true); // закрыть городские ворота
		sld = CharacterFromID("Marigo Fort Commander");
		LAi_SetImmortal(sld, true);
		Character_SetAbordageEnable(sld, false); // неабордируемый форт Синт-Маартена
	}
	else if (sQuestName == "Patria_SanMartinBack") //
	{
		pchar.quest.Munity = "Deads";
		LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
		pchar.questTemp.Patria = "epizode_5_return";
		pchar.quest.Patria_SanMartin_Back.win_condition.l1 = "location";
		pchar.quest.Patria_SanMartin_Back.win_condition.l1.location = "Nevis";
		pchar.quest.Patria_SanMartin_Back.function = "Patria_SanMartinBack";
		SetFunctionTimerCondition("Patria_SanMartinBaronOver", 0, 0, 7, false); // таймер
	}
	else if (sQuestName == "Patria_SanMartinBaronTurn") //
	{
		sld = characterFromId("Noel");
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, characterFromID("Puancie"));
	}
	else if (sQuestName == "Patria_DiplomatGetOut") //
	{
		LocatorReloadEnterDisable("Villemstad_town", "reload3_back", true);
		pchar.quest.Patria_DiplomatSail.win_condition.l1 = "MapEnter";
		pchar.quest.Patria_DiplomatSail.function = "Patria_DiplomatSail";
		pchar.questTemp.Patria = "epizode_6_return";
		AddQuestRecord("Patria", "30");
	}
	else if (sQuestName == "Patria_DiplomatAfterFight") //
	{
		chrDisableReloadToLocation = false;
		DoQuestCheckDelay("hide_weapon", 0.2);
		LAi_group_Delete("EnemyFight");
		DoQuestReloadToLocation("Villemstad_town", "reload", "reload4", "Patria_DiplomatEscape");
	}
	else if (sQuestName == "Patria_DiplomatEscape") //
	{
		LocatorReloadEnterDisable("Villemstad_town", "reload3_back", true);
		pchar.quest.Patria_DiplomatSail.win_condition.l1 = "MapEnter";
		pchar.quest.Patria_DiplomatSail.function = "Patria_DiplomatSail";
		pchar.questTemp.Patria = "epizode_6_return";
		AddQuestRecord("Patria", "31");
		SetNationRelation2MainCharacter(HOLLAND, RELATION_ENEMY);
	}
	else if (sQuestName == "Patria_BastionMineAttackWin") //
	{
		LAi_group_Delete("EnemyFight");
		DoQuestCheckDelay("hide_weapon", 1.3);
		DoQuestCheckDelay("sea_victory", 1.3);
		DeleteAttribute(pchar, "GenQuest.CannotWait");
		chrDisableReloadToLocation = false;//открыть локацию
		LocatorReloadEnterDisable("Location_reserve_01", "reload2_back", false); // открыть выход назад
		bQuestDisableMapEnter = false;//открыть карту
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		sld = characterFromId("Marigo_Mayor");
		ChangeCharacterAddressGroup(sld, "none", "", ""); // прячем губера
		LocatorReloadEnterDisable("Marigo_town", "gate_back", false);//открыть выход из города
		SetFunctionTimerCondition("Patria_BastionNewHuber", 0, 0, 10, false); // через 10 дней обновим губера на нового и обновим рудник
		// меняем нацию Синт-Маартена
		i = FindColony("Marigo");
		colonies[i].nation = FRANCE;
		string sColony = "Marigo_town";
		worldMap.labels.(sColony).icon = FRANCE;
		// ручками пропишем смену нации статикам
		sld = characterFromId("Marigo_Priest");
		sld.nation = FRANCE;
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		sld = characterFromId("Marigo_waitress");
		sld.nation = FRANCE;
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		sld = characterFromId("Marigo_tavernkeeper");
		sld.nation = FRANCE;
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		sld = characterFromId("Marigo_trader");
		sld.nation = FRANCE;
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		sld = characterFromId("Marigo_Priest");
		sld.nation = FRANCE;
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		sld = characterFromId("Marigo_shipyarder");
		sld.nation = FRANCE;
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		sld = characterFromId("Marigo_usurer");
		sld.nation = FRANCE;
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		sld = characterFromId("Marigo_PortMan");
		sld.nation = FRANCE;
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		sld = characterFromId("Marigo_Hostess");
		sld.nation = FRANCE;
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		sld = CharacterFromID("Marigo Fort Commander"); // лесник . оживил форт после боя смены нации филипсбурга (для НИ)
		sld.nation = FRANCE;
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		// заставка форта
		n = Findlocation("Marigo_fort");
		Locations[n].image = "loading\fort_fra_" + rand(1) + ".tga";
		// чистим за собой
		DeleteAttribute(pchar, "TempPerks.QuestTroopers"); // убрать квестовый десант
		for (i=1; i<=15; i++)
		{
			sld = CharacterFromID("Bastion_soldier_"+i);
			sld.lifeday = 0;
		}
		// выводим фрегаты из эскадры, если таковые были и живы
		if (GetCharacterIndex("Patria_GlpCap") != -1)
		{
			sld = characterFromId("Patria_GlpCap");
			RemoveCharacterCompanion(pchar, sld);
		}
		if (GetCharacterIndex("Patria_MrtCap") != -1)
		{
			sld = characterFromId("Patria_MrtCap");
			RemoveCharacterCompanion(pchar, sld);
		}
		// начальника рудника - в пленники
		sld = GetCharacter(NPC_GenerateCharacter("Bastion_spanish_boss", "Boss_2", "man", "man", 15, SPAIN, -1, false, "soldier"));
		FantomMakeCoolFighter(sld, 15, 20, 20, LinkRandPhrase("blade_18","blade_19","blade_21"), "pistol5", "bullet", 50);
		pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(sld);
		SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
		pchar.questTemp.Patria.SpanishName = GetFullName(sld);
		sld = characterFromId(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)]);
		pchar.questTemp.Patria.SpanishID = sld.id;
		log_info(StringFromKey("Patria_44"));
		pchar.questTemp.Patria = "epizode_9_return";
		AddQuestRecord("Patria", "51");
	}
	else if (sQuestName == "Patria_CuracaoTrooperLand") //
	{
		Island_SetReloadEnableGlobal("Curacao", true); //открыть остров
		pchar.GenQuest.MapClosedNoBattle = true;
		DeleteAttribute(pchar, "DisableChangeFlagMode"); // разблокировать флаг
		chrDisableReloadToLocation = true;
		sld = characterFromId("Doily_land");
		LAi_SetImmortal(sld, true);
		sld.dialog.currentnode = "doily_18";
		ChangeCharacterAddressGroup(sld, "shore24", "goto", "goto2");
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		// отряд д'Ойли с пушками
		for (i=1; i<=15; i++)
		{
			if (i < 7) // мушкетеры, 6 шт
			{
				sld = GetCharacter(NPC_GenerateCharacter("Curacao_eng_soldier_"+i, "mush_eng_"+i, "man", "mushketer", 35, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 35, 70, 70, "", "mushket2", "cartridge", 200);
				LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
				sld.cirassId = Items_FindItemIdx("cirass1");
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Curacao_eng_soldier_"+i, "sold_eng_"+(rand(7)+9), "man", "man", 35, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 35, 65, 65, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 170);
				sld.cirassId = Items_FindItemIdx("cirass2");
			}
			LAi_SetCheckMinHP(sld, 10, true, ""); 
			ChangeCharacterAddressGroup(sld, "shore24", "goto", "goto7");
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorFollow(sld, characterFromID("Doily_land"), "", -1);
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
		}
	}
	else if (sQuestName == "Patria_CuracaoAfterJungleMushketer") //
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;
		pchar.quest.Patria_CuracaoMarch1.win_condition.l1 = "location";
		pchar.quest.Patria_CuracaoMarch1.win_condition.l1.location = "Curacao_jungle_01";
		pchar.quest.Patria_CuracaoMarch1.function = "Patria_CuracaoJungleBattle"; // второй отряд голландцев
	}
	else if (sQuestName == "Patria_CuracaoAfterJungleBattle") //
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;
		pchar.quest.Patria_CuracaoMarch2.win_condition.l1 = "location";
		pchar.quest.Patria_CuracaoMarch2.win_condition.l1.location = "Villemstad_ExitTown";
		pchar.quest.Patria_CuracaoMarch2.function = "Patria_CuracaoGateBattle"; // у ворот
	}
	else if (sQuestName == "Patria_CuracaoGateBattle1") //
	{
		LAi_ActorTurnToLocator(pchar, "reload", "reload4");
		DoQuestFunctionDelay("Patria_CuracaoGateBattle2", 4.0);
	}
	else if (sQuestName == "Patria_CuracaoGateBattleMush1") 
	{
		for (i=5; i<=7; i++)
		{
			sld = characterFromId("Curacao_hol3_soldier_"+i);
			LAi_KillCharacter(sld);
		}
		DoQuestFunctionDelay("Patria_CuracaoGateBattle3", 5.0);
	} 
	else if (sQuestName == "Patria_CuracaoGateBattleEnd") 
	{
		LAi_group_Delete("EnemyFight");
		for (i=1; i<=15; i++)
		{
			sld = characterFromId("Curacao_eng_soldier_"+i);
			LAi_SetActorType(sld);
			if (i >= 7 && i < 14) 
			{
				LAi_ActorRunToLocator(sld, "quest", "sold"+i, "", -1);
			}
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		// на всякий случай сброс шаблона, если вдруг где-то безобразничают
		for (i=1; i<=15; i++)
		{
			if (GetCharacterIndex("Curacao_fra_soldier_"+i) != -1)
			{
				sld = characterFromId("Curacao_fra_soldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		}
		LAi_SetActorType(pchar);
		LAi_ActorRunToLocator(pchar, "quest", "hero", "Patria_CuracaoGateTalk", -1);
	} 
	else if (sQuestName == "Patria_CuracaoGateTalk") 
	{
		SetMusic("music_military");
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Doily_land");
		sld.dialog.currentnode = "doily_23";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	} 
	else if (sQuestName == "Patria_CuracaoStivesantWait") 
	{
		SetLaunchFrameFormParam(StringFromKey("Patria_45", NewStr()), "", 0, 5);
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 23, 10); //крутим время
		RecalculateJumpTable();
		StoreDayUpdate();
		RefreshWeather();
		RefreshLandTime();
		DoQuestFunctionDelay("Patria_CuracaoStivesant", 5.0);
	} 
	else if (sQuestName == "Patria_CuracaoResult") 
	{
		sld = characterFromId("Doily_land");
		sld.dialog.currentnode = "doily_20";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	} 
	else if (sQuestName == "Patria_CondotierTavern") 
	{
		/* if(CheckAttribute(pchar, "IsMushketer"))
		{
			SetMainCharacterToMushketer("", false);
		} */
		FreeSitLocator("PortPax_tavern", "sit_front1");
		sld = CharacterFromID("Noel");
		sld.Dialog.currentnode = "noel_31";
		ChangeCharacterAddressGroup(sld, "PortPax_tavern", "sit", "sit_front1");
		LAi_SetActorType(sld);
		LAi_ActorSetSitMode(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
	} 
	else if (sQuestName == "Patria_CondotierToPirates") 
	{
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID("Noel");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		if(bImCasual) NewGameTip(StringFromKey("Patria_9"));
		SetFunctionTimerCondition("Patria_CondotierTimeOver", 0, 0, 15, false); // две недели на разговор с Акулой/Тираксом 
		if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "end" && colonies[FindColony("Pirates")].nation == PIRATE) // пройдена Сага до конца
		{
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) 
			{
				pchar.questTemp.Patria.Saga.Shark = "true"; // Додсон жив
				AddQuestRecord("Patria", "68_1");
			}
			else 
			{
				pchar.questTemp.Patria.Saga.Terrax = "true"; // Додсон погиб, вместо него Тиракс
				AddQuestRecord("Patria", "68_2");
			}
		}
		else 
		{
			pchar.questTemp.Patria.Pirate.Terrax = "true"; // Сага не пройдена, к Тираксу в Ла Вегу
			AddQuestRecord("Patria", "68_3");
		}
	} 
	else if (sQuestName == "Patria_CondotierDodsonNorm") 
	{
		chrDisableReloadToLocation = false;
		Group_DeleteGroup("DodsonFrigate");
		if (CheckAttribute(pchar, "questTemp.Patria.Saga.Shark"))
		{
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "First time";
		}
		else
		{
			sld = CharacterFromID("Terrax");
			sld.dialog.currentnode = "I_know_you_good";
		}
		ChangeCharacterAddressGroup(sld, "Pirates_townhall", "sit", "sit1");
		LAi_SetHuberType(sld);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
		LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
	} 
	else if (sQuestName == "Patria_CondotierTerraxNorm") 
	{
		chrDisableReloadToLocation = false;
		Group_DeleteGroup("DodsonFrigate");
		sld = CharacterFromID("Terrax");
		sld.dialog.currentnode = "I_know_you_good";
		ChangeCharacterAddressGroup(sld, "Lavega_townhall", "sit", "sit1");
		LAi_SetHuberType(sld);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
		LocatorReloadEnterDisable("Lavega_town", "reload6", false);
	} 
	else if (sQuestName == "Patria_CondotierBaronDie") 
	{
		sld = CharacterFromID("Noel");
		LAi_KillCharacter(sld);
		if (CheckAttribute(pchar, "questTemp.Patria.Saga.Shark")) sld = CharacterFromID("Dodson");
		else sld = CharacterFromID("Terrax");
		sld.dialog.currentnode = "patria_24";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0); 
	} 
	else if (sQuestName == "Patria_CondotierToCabin") 
	{
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID("Noel");
		ChangeCharacterAddressGroup(sld, "Portpax_tavern", "tables", "stay2");
		LAi_SetActorType(sld);
		LAi_ActorFollowEverywhere(sld, "", -1);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		bQuestDisableMapEnter = true;//закрыть карту
		pchar.GenQuest.MapClosedNoBattle = true;
		pchar.quest.Patria_Condotier_inCabin.win_condition.l1 = "location";
		pchar.quest.Patria_Condotier_inCabin.win_condition.l1.location = Get_My_Cabin();
		pchar.quest.Patria_Condotier_inCabin.function = "Patria_CondotierInCabin";
	}
	else if (sQuestName == "Patria_CondotierToSMartin") 
	{
		chrDisableReloadToLocation = false;
		bQuestDisableMapEnter = false;//открыть карту
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		sld = CharacterFromID("Noel");
		AddPassenger(pchar, sld, false);//добавить пассажира
		SetCharacterRemovable(sld, false);
		AddQuestRecord("Patria", "79");
		LocatorReloadEnterDisable("Shore40", "reload2_back", true);//закрыть локатор на рудник
		LAi_LocationDisableOfficersGen("shore40", true);
		LAi_LocationDisableOfficersGen("Location_reserve_01", true);
		LAi_LocationDisableOfficersGen("Location_reserve_03", true);
		pchar.quest.Patria_Condotier_sail.win_condition.l1 = "location";
		pchar.quest.Patria_Condotier_sail.win_condition.l1.location = "shore40";
		pchar.quest.Patria_Condotier_sail.win_condition.l2 = "Night";
		pchar.quest.Patria_Condotier_sail.function = "Patria_CondotierToMine";
		// 2 месяца до Стайвесанта, иначе барон даст дуба
		SetFunctionTimerCondition("Patria_CondotierBaronFail", 0, 0, 60, false); // таймер
	} 
	else if (sQuestName == "Patria_CondotierInMine") 
	{
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID("Noel");
		sld.dialog.currentnode = "noel_76";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	} 
	else if (sQuestName == "Patria_CondotierToBeach") 
	{
		DoQuestReloadToLocation("Location_reserve_01", "reload", "reload1_back", "Patria_CondotierOnBeach");
	} 
	else if (sQuestName == "Patria_CondotierOnBeach") // охрана пришла
	{
		pchar.GenQuest.Hunter2Pause = true;
		LAi_SetPlayerType(pchar);
		chrDisableReloadToLocation = true;//закрыть локацию
		LAi_LocationFightDisable(&Locations[FindLocation("Location_reserve_01")], true);//запретить драться
		for (i=1; i<=5; i++)
		{
			if (i < 3) // мушкетеры, 2 шт
			{
				sld = GetCharacter(NPC_GenerateCharacter("Marigo_eng_soldier_"+i, "mush_eng_"+i, "man", "mushketer", 25, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 25, 50, 50, "", "mushket1", "cartridge", 150);
				LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
				if (MOD_SKILL_ENEMY_RATE > 4) sld.cirassId = Items_FindItemIdx("cirass1");
			}
			else
			{
				if (i == 5) 
				{
					sld = GetCharacter(NPC_GenerateCharacter("Marigo_eng_soldier_"+i, "off_eng_1", "man", "man", 25, ENGLAND, -1, false, "soldier"));
					FantomMakeCoolFighter(sld, 25, 50, 50, LinkRandPhrase("blade_20","blade_21","blade_17"), "pistol5", "bullet", 150);
				}
				else 
				{
					sld = GetCharacter(NPC_GenerateCharacter("Marigo_eng_soldier_"+i, "sold_eng_"+(rand(7)+9), "man", "man", 20, ENGLAND, -1, false, "soldier"));
					FantomMakeCoolFighter(sld, 20, 40, 40, LinkRandPhrase("blade_08","blade_12","blade_14"), "pistol1", "bullet", 100);
				}
				if (MOD_SKILL_ENEMY_RATE > 4) sld.cirassId = Items_FindItemIdx("cirass2");
			}
			ChangeCharacterAddressGroup(sld, "Location_reserve_01", "rld", "loc0");
			LAi_SetActorType(sld);
			if (i == 5)
			{
				sld.Dialog.Filename = "Quest\Patria_NPC.c";
				sld.dialog.currentnode = "engofficer";
			}
			else LAi_CharacterDisableDialog(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
	} 
	else if (sQuestName == "Patria_CondotierBeachAfterFight") 
	{
		chrDisableReloadToLocation = false;
		LAi_group_Delete("EnemyFight");
		LocatorReloadEnterDisable("Location_reserve_01", "reload1_back", true);//закрыть локатор на рудник
		if (CheckAttribute(pchar, "questTemp.Patria.Condotier.BaronKilled")) // барон помер
		{
			pchar.quest.Patria_CondotierBaronFail.over = "yes"; //снять прерывание
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_baronkilled";
			LocatorReloadEnterDisable("Shore40", "reload1_back", false);
			LocatorReloadEnterDisable("Shore40", "boat", false);
			LAi_LocationDisableOfficersGen("shore40", false);
			LAi_LocationDisableOfficersGen("Location_reserve_01", false);
			LAi_LocationDisableOfficersGen("Location_reserve_03", false);
		}
		else
		{
			pchar.quest.Patria_Baron_killed.over = "yes"; //снять прерывание
			sld = CharacterFromID("Noel");
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Patria", "80");
			pchar.quest.Patria_CondotierShore40.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierShore40.win_condition.l1.location = "shore40";
			pchar.quest.Patria_CondotierShore40.function = "Patria_CondotierInShore40";
		}
	} 
	else if (sQuestName == "Patria_CondotierOnCuracaoWait") 
	{
		SetLaunchFrameFormParam(StringFromKey("Patria_46", NewStr()), "", 0, 5);
		LaunchFrameForm();
		WaitDate("", 0, 0, 1, 0, 10); //крутим время
		RecalculateJumpTable();
		StoreDayUpdate();
		RefreshWeather();
		RefreshLandTime();
		DoQuestFunctionDelay("Patria_CondotierStivesant", 5.0);
	} 
	else if (sQuestName == "Patria_CondotierStivesantInHall") 
	{
		chrDisableReloadToLocation = false; // 17-add
		sld = CharacterFromID("Stivesant");
		sld.dialog.currentnode = "Stivesant_49";
		ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "goto", "governor1");
		LAi_SetStayType(sld);
	} 
	else if (sQuestName == "Patria_EuropePuancieInPrison") 
	{
		DoQuestFunctionDelay("Patria_EuropeMusic", 1.5); // 7-add
		pchar.questTemp.jailCanMove = true;
		chrDisableReloadToLocation = true;//закрыть локацию
		LocatorReloadEnterDisable("Charles_town", "reload_jail", false);
	} 
	// belamour legendary edition -->
	else if (sQuestName == "ToEcliatonAward") 
	{
		DoQuestReloadToLocation("Charles_RoomTownHall", "reload", "reload1", "");
		sld = characterFromId("Noel");
		ChangeCharacterAddressGroup(sld, "Charles_RoomTownHall", "goto", "goto1");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "goto", "goto6", "", -1);
		sld = characterFromId("Ecliaton_Cap");
		ChangeCharacterAddressGroup(sld, "Charles_RoomTownHall", "goto", "goto5");
		sld.dialog.currentnode = "ecliaton_cap_15";
		LAi_SetStayType(sld);
		LAi_SetActorType(pchar);
		LAi_ActorDialog(pchar, sld, "", -1, 0);
	} 
	else if (sQuestName == "EcliatonAwardNoelTalk") 
	{
		Lai_SetPlayerType(pchar);
		sld = characterFromId("Ecliaton_Cap");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld = characterFromId("Noel");
		sld.dialog.currentnode = "noel_121";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else if (sQuestName == "SharlePutsSuit")
	{
		//if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
		// <--- belamour всегда снимаем мушкет, если какие либо операции с кирасам	
		RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
		GiveItem2Character(pchar, "suit1");
		EquipCharacterbyItem(pchar, "suit1");
		GiveItem2Character(pchar, "patent_fra");
		EquipCharacterbyItem(pchar, "patent_fra");
		Items[sti(pchar.EquipedPatentId)].TitulCur = 2; 
		Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
		//Log_Info("Вы получили мундир королевского военно-морского флота Франции");
		ChangeCharacterNationReputation(pchar, FRANCE, 100);
		ChangeCharacterComplexReputation(pchar, "fame", 12);
	}
	// <-- legendary edition
	else
	{
		condition = false;
	}
	
	return condition;
}
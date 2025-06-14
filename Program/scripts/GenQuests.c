// Генераторы. Отдельный файл
// ситуации на захваченном корабле - "Взрыв" или "Эпидемия"
#define ShipSituation_0				0 	// "Взрыв на корабле" или "Эпидемия" - обшарили каюту или труп
#define ShipSituation_1				1	// "Взрыв на корабле" или "Эпидемия" - любое использовование интерфейса "грабежа" --> перегрузка отдельных товаров или нажатие кнопки "Взять все" - после этого корабль взрывается или его сами топим
#define ShipSituation_2				2	// "Эпидемия" - сажаем компаньона с командой на инфицированный корабль
#define ShipSituation_3				3	// "Эпидемия" - ГГ пересаживается на инфицированный корабль
#define ShipSituation_4				4	// Ничего не обшаривали

int iGenRank;
string sGenLocation, sGenlocator, sGenBlade, sGenGun, sQuestTitle;

void Rat_GenerateRat()
{
	/* Скопировать файл Rat.gm (модель) в Resource/Models/Characters
	Файл Rat.tx (текстуру) в Resource/Textures/Characters
	Настроить дебагер - В файле Engine.ini поменять debugwindow = 0 на debugwindow = 1
	Потом по F5 в игре в левой части набрать Rat_GenerateRat();
	Модельки маленькие - с первого раза можно не заметить.
	Остальные коменты по ходу...*/
	
	ref rChar;
	int iRatCount = 1; // Скока крыс будем генерить?
	for(int i=1; i<=iRatCount; i++)
	{
		rChar = GetCharacter(NPC_GenerateCharacter("Test_Rat_"+i, "rat", "man", "rat", sti(PChar.rank)*5, PIRATE, -1, false, "citizen"));
		SetFantomParamFromRank(rChar, sti(PChar.rank)*5, true); // Крутая крыса!
		rChar.Dialog.FileName = "GenQuests_Dialog.c";
		LAi_SetStayType(rChar); // ТИП ! От этого анимация и зависит как-раз.
		ChangeCharacterAddressGroup(rChar, PChar.location, "reload", FindNearestFreeLocator("reload")); // Перенесем в локу к ГГ
	}
}

//=====================================================================================================================================
// Генератор контрабандистов. Доставка письма -->
//=====================================================================================================================================
void ContraDeliverQuest_EnterToTavernRoom(string sQuest) // Зашли в комнату наверху
{
	sGenLocation = PChar.GenQuest.ContraDeliver.ToColony;
	LocatorReloadEnterDisable(sGenLocation + "_Tavern", "reload2_back", true); // Закроем сразу
	chrDisableReloadToLocation = true;
	bDisableFastReload         = true;
	DoQuestFunctionDelay("ContraDeliverQuest_ReloadConterToRoom", 3.0); // Ждём 3 сек.
}

void ContraDeliverQuest_ReloadConterToRoom(string sQuest) // генерим клона контрабандиста
{
	ref rChar = GetCharacter(NPC_GenerateCharacter("ContraDeliverQuest_Contra_1", PChar.GenQuest.ContraDeliver.Model, "man", PChar.GenQuest.ContraDeliver.Model.Animation, sti(PChar.rank)*2, PIRATE, 0, true, "marginal"));
	rChar.DontClearDead = true;
	SetFantomParamFromRank(rChar, sti(PChar.rank)*2, true);
	rChar.Name = StringFromKey("GenQuests_1");
	rChar.LastName = "";
	rChar.greeting = "Gr_Smuggler Agent";
	LAi_SetActorType(rChar);
	rChar.Dialog.FileName = "GenQuests_Dialog.c";
	LAi_SetImmortal(rChar, true);
	ChangeCharacterAddressGroup(rChar, PChar.location, "reload", "reload1_back");
	LAi_ActorDialog(rChar, PChar, "", -1, 5);
}

void ContraDeliverQuest_ContraIsDead(string sQuest)
{
	ref rChar = &characters[GetCharacterIndex(sGenLocation + "_Smuggler")];
	rChar.model    = "citiz_" + (rand(9)+41); // Меняем модель (типо, туда уже другой пришёл)
	FaceMaker(rChar);
	CirassMaker(rChar);
	chrDisableReloadToLocation = false;
	bDisableFastReload         = false;
	//PChar.GenQuest.ContraDeliver.Complete.ContraDead = true;
	ChangeContrabandRelation(PChar, -10);
	sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
	AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "5");
	AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ContraDeliver.ToColony + "Gen"));
	CloseQuestHeader(sQuestTitle);
	DeleteAttribute(PChar, "GenQuest.ContraDeliver");
}

void ContraDeliverQuest_GeneratePatrolToRoom()
{
	ref rChar;
	sGenLocation = PChar.GenQuest.ContraDeliver.ToColony;
	int iNation = sti(characters[GetCharacterIndex(sGenLocation + " Fort Commander")].nation);
	string sShortNation = NationShortName(iNation); // Для модельки
	string sModel[3];
	sModel[0] = "off_" + sShortNation + "_1";
	sModel[1] = "sold_" + sShortNation + "_1";
	sModel[2] = "sold_" + sShortNation + "_2";
	string sGenGroup[3];
	sGenGroup[0] = "reload";
	sGenGroup[1] = "Quest";
	sGenGroup[2] = "Quest";
	string sGenLocatorArroy[3];
	sGenLocatorArroy[0] = "reload1_back";
	sGenLocatorArroy[1] = "Quest1";
	sGenLocatorArroy[2] = "Quest2";
	for(int i=0; i<=2; i++)
	{
		rChar = GetCharacter(NPC_GenerateCharacter("ContraDeliverQuest_Soldier_" + i, sModel[i], "man", "man", sti(PChar.rank)*2, iNation, 0, true, "soldier"));
		SetFantomParamFromRank(rChar, sti(PChar.rank)*2, true);
		rChar.Name = StringFromKey("GenQuests_2");
		rChar.LastName = "";
		rChar.Greeting = "soldier_arest";
		LAi_SetActorType(rChar);
		rChar.Dialog.FileName = "GenQuests_Dialog.c";
		LAi_SetImmortal(rChar, true);
		ChangeCharacterAddressGroup(rChar, PChar.location, sGenGroup[i], sGenLocatorArroy[i]);
		if(i != 0) LAi_CharacterDisableDialog(rChar);
		else LAi_ActorDialog(rChar, PChar, "", -1, 5);
	}
	
	rChar = CharacterFromID("ContraDeliverQuest_Contra_1");
	LAi_ActorGoToLocator(rChar, "goto", "goto2", "", 3);
}

void ContraDeliverQuest_SoldiersGoOut()
{
	ref rChar;
	for(int i=0; i<=2; i++)
	{
		rChar = CharacterFromID("ContraDeliverQuest_Soldier_" + i);
		LAi_ActorGoToLocation(rChar, "reload", "reload1_back", "none", "", "", "", 3.0);
	}
	
	rChar = CharacterFromID("ContraDeliverQuest_Contra_1");
	PChar.GenQuest.CallFunctionParam = "ContraDeliverQuest_AfterSoldiersOut";
	LAi_ActorGoToLocation(rChar, "reload", "reload1_back", "none", "", "", "CallFunctionParam", 3.0);
}

void ContraDeliverQuest_AfterSoldiersOut()
{
	chrDisableReloadToLocation = false;
	bDisableFastReload         = false;
	sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
	AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "7");
	CloseQuestHeader(sQuestTitle);
	DeleteAttribute(PChar, "GenQuest.ContraDeliver");
}
//=====================================================================================================================================
// <-- Генератор контрабандистов. Доставка письма
//=====================================================================================================================================

//=====================================================================================================================================
// Генератор контрабандистов. Встреча в бухте -->
//=====================================================================================================================================
void ContraMeetManQuest_InitStartParam() // Инициализация стартовых параметров
{
	if(rand(1) == 0)
	{
		Log_TestInfo("В бухте будут ждать солдаты.");
		PChar.GenQuest.ContraMeetMan.SoldiersInShore = true;
	}
	else
	{
		Log_TestInfo("В бухте солдат не будет.");
		if(rand(1) == 0)
		{
			Log_TestInfo("Человек окажется предателем.");
			PChar.GenQuest.ContraMeetMan.ManIsTraitor = true;
		}
		else Log_TestInfo("В ходе квеста не выясниться, что человек - предатель.");
	}
}

void ContraMeetManQuest_EnterToShore(string sQuest) // Вошли в бухту
{
	ref rChar;
	if(!CheckAttribute(PChar, "GenQuest.ContraMeetMan.SoldiersInShore")) //Встречаем чела
	{
		rChar = GetCharacter(NPC_GenerateCharacter("ContraMeetManQuest_QuestMan", "citiz_"+(rand(9)+21), "man", "man", sti(PChar.rank)*2, PIRATE, -1, true, "citizen"));
		SetFantomParamFromRank(rChar, sti(PChar.rank)*2, true);
		rChar.Greeting = "cit_common";
		LAi_SetCitizenType(rChar);
		rChar.Dialog.FileName = "GenQuests_Dialog.c";
		rChar.DontClearDead = true;
		LAi_SetImmortal(rChar, true); // До поры нельзя завалить
		ChangeCharacterAddressGroup(rChar, PChar.location, "goto", "goto1");
	}
	else // Солдеры
	{
		sGenLocation = PChar.GenQuest.ContraMeetMan.QuestTown;
		int iNation = sti(characters[GetCharacterIndex(sGenLocation + " Fort Commander")].nation);
		string sShortNation = NationShortName(iNation); // Для модельки
		int iSoldCount = 4+rand(2);
		PChar.GenQuest.ContraMeetMan.SoldCount = iSoldCount; // Запомнит, т.к. потом их нужно удалять
		for(int i=0; i<=iSoldCount; i++)
		{
			sGenlocator = LAi_FindRandomLocator("goto");
			if(i==0) // Офицер
			{
				rChar = GetCharacter(NPC_GenerateCharacter("ContraMeetManQuest_Officer_" + i, "off_"+sShortNation+"_1", "man", "man", sti(PChar.rank)*2, iNation, -1, true, "officer"));
				SetFantomParamFromRank(rChar, sti(PChar.rank)*2, true);
				rChar.Name = StringFromKey("GenQuests_2");
				rChar.LastName = "";
			}
			else // Солдаты
			{
				rChar = GetCharacter(NPC_GenerateCharacter("ContraMeetManQuest_Soldier_" + i, "sold_"+sShortNation+"_1", "man", "man", sti(PChar.rank), iNation, -1, true, "soldier"));
				SetFantomParamFromRank(rChar, sti(PChar.rank), true);
				rChar.Name = StringFromKey("GenQuests_3");
				rChar.LastName = "";
			}
			
			rChar.Greeting = "soldier_arest";
			LAi_SetCitizenType(rChar);
			rChar.Dialog.FileName = "GenQuests_Dialog.c";
			LAi_SetImmortal(rChar, true);
			ChangeCharacterAddressGroup(rChar, PChar.location, "goto", sGenlocator);
		}	
	}
}

void ContraMeetManQuest_DeletePatrolFromShore()
{
	int iSoldCount = sti(PChar.GenQuest.ContraMeetMan.SoldCount);
	ref rChar;
	for(int i=0; i<=iSoldCount; i++)
	{
		if(i==0) rChar = CharacterFromID("ContraMeetManQuest_Officer_"+i);
		else rChar = CharacterFromID("ContraMeetManQuest_Soldier_"+i);
		
		rChar.LifeDay = 0;
	}
}

void ContraMeetManQuest_TimeIsLeft(string sQuest) // Вышло время
{
	DeleteQuestCondition("ContraMeetManQuest_EnterToShore"); // Завершим прерывание на вход в бухту
	if(GetCharacterIndex("ContraMeetManQuest_QuestMan") != -1)
	{
		ref rChar = CharacterFromID("ContraMeetManQuest_QuestMan");
		rChar.LifeDay = 0;
		ChangeCharacterAddressGroup(rChar, "none", "", "");
	}
	
	if(CheckAttribute(PChar, "Quest.ContraMeetManQuest_EnterToTavernRoom"))
	{
		LocatorReloadEnterDisable(PChar.GenQuest.ContraMeetMan.QuestTown + "_tavern", "reload2_back", true); // Закроем комнату
		DeleteQuestCondition("ContraMeetManQuest_EnterToTavernRoom");
	}
	
	sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
	AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "2");
	AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
	CloseQuestHeader(sQuestTitle);
	DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters");
	DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
}

void ContraMeetManQuest_EnterToTavernRoom(string sQuest)
{
	sGenLocation = PChar.GenQuest.ContraMeetMan.QuestTown;
	DeleteQuestCondition("ContraMeetManQuest_TimeIsLeft"); // Завершаем прерывание на таймер
	LocatorReloadEnterDisable(sGenLocation + "_Tavern", "reload2_back", true); // Закроем комнату
	DisableAllExits(true);
	DoQuestFunctionDelay("ContraMeetManQuest_ReloadConterToRoom", 3.0);
}

void ContraMeetManQuest_ReloadConterToRoom(string sQuest)
{
	ref rChar;
	string sGenGroup[2];
	sGenGroup[0] = "reload";
	sGenGroup[1] = "Quest";
	string sGenLocatorArroy[2];
	sGenLocatorArroy[0] = "reload1_back";
	sGenLocatorArroy[1] = "Quest2";
	for(int i=0; i<=1; i++)
	{
		rChar = GetCharacter(NPC_GenerateCharacter("ContraMeetManQuest_Contrick_" + i, "citiz_"+(rand(9)+41), "man", "man", sti(PChar.rank)*2, PIRATE, 0, true, "hunter"));
		SetFantomParamFromRank(rChar, sti(PChar.rank)*2, true);
		rChar.Name = StringFromKey("GenQuests_1");
		rChar.LastName = "";
		rChar.Greeting = "Gr_Smuggler Agent";
		LAi_SetActorType(rChar);
		rChar.Dialog.FileName = "GenQuests_Dialog.c";
		LAi_SetImmortal(rChar, true);
		rChar.SuperShooter  = true; // даный НПС будет чаще юзать пистоль (вероятность от сложности, но в разы выше, чем у обычных, близка офам)
		ChangeCharacterAddressGroup(rChar, PChar.location, sGenGroup[i], sGenLocatorArroy[i]);
		if(i != 0) LAi_CharacterDisableDialog(rChar);
		else LAi_ActorDialog(rChar, PChar, "", -1, 5);
	}
	
	rChar = CharacterFromID("ContraMeetManQuest_QuestMan"); // Отправляем чела в дальний локатор, чтоб не мешал
	LAi_ActorGoToLocator(rChar, "goto", "goto2", "", 3);
}

void ContraMeetManQuest_ContersGoQut() // Контрики сваливают из комнаты вместе с челом
{
	ref rChar;
	for(int i=0; i<=1; i++)
	{
		if(GetCharacterIndex("ContraMeetManQuest_Contrick_"+i) != -1 && !LAi_isDead(CharacterFromID("ContraMeetManQuest_Contrick_"+i)))
		{
			rChar = CharacterFromID("ContraMeetManQuest_Contrick_" + i);
			LAi_Type_Actor_Reset(rChar);
			LAi_ActorGoToLocation(rChar, "reload", "reload1_back", "none", "", "", "", 3.0);
		}
	}
	
	PChar.GenQuest.CallFunctionParam = "ContraMeetManQuest_AfterContersOut";
	rChar = CharacterFromID("ContraMeetManQuest_QuestMan");
	LAi_Type_Actor_Reset(rChar);
	LAi_ActorGoToLocation(rChar, "reload", "reload1_back", "none", "", "", "CallFunctionParam", 3.0);
}

void ContraMeetManQuest_AfterContersOut()
{
	DisableAllExits(false); // Откроем выходы
	ref rChar = &Characters[GetCharacterIndex(Locations[FindLocation(PChar.location)].townsack + "_Smuggler")];
	SaveCurrentNpcQuestDateParam(rChar, "work_date");
}

void ContraMeetManQuest_ContraBeatMan() // Контрики начинают мочить чела
{
	LAi_Group_Delete("ContraMeetManQuest_Group1"); // Потрем прежние группы
	LAi_Group_Delete("ContraMeetManQuest_Group2");
	DisableAllExits(false); // Откроем выходы
	ref rChar = CharacterFromID("ContraMeetManQuest_QuestMan");
	rChar.LifeDay = 0;
	LAi_SetImmortal(rChar, false);
	LAi_Group_MoveCharacter(rChar, "ContraMeetManQuest_Group1");
	for(int i=0; i<=1; i++)
	{
		rChar = CharacterFromID("ContraMeetManQuest_Contrick_"+i);
		LAi_Group_MoveCharacter(rChar, "ContraMeetManQuest_Group2");
	}
	LAi_Group_SetRelation("ContraMeetManQuest_Group1", "ContraMeetManQuest_Group2", LAI_GROUP_ENEMY);
	LAi_Group_FightGroups("ContraMeetManQuest_Group1", "ContraMeetManQuest_Group2", true);
	SetFunctionNPCDeathCondition("ContraMeetManQuest_ContraBeatMan_Complete", "ContraMeetManQuest_QuestMan", false);
}

void ContraMeetManQuest_ContraBeatMan_Complete(string sQuest)
{
	// Их может уже не быть
	if(GetCharacterIndex("ContraMeetManQuest_Contrick_0") == -1 || GetCharacterIndex("ContraMeetManQuest_Contrick_1") == -1) return;
		
	ref rChar;
	for(int i=0; i<=1; i++)
	{
		rChar = CharacterFromID("ContraMeetManQuest_Contrick_"+i);
		LAi_SetActorType(rChar);
		LAi_ActorGoToLocation(rChar, "reload", "reload1_back", "none", "", "", "", 3.0);
	}
}

void ContraMeetManQuest_PlayerBeatContra()
{
	LAi_Group_Delete("ContraMeetManQuest_Group1"); // Потрем прежние группы
	ref rChar = CharacterFromID("ContraMeetManQuest_QuestMan");
	rChar.LifeDay = 0;
	LAi_Group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
	for(int i=0; i<=1; i++)
	{
		rChar = CharacterFromID("ContraMeetManQuest_Contrick_"+i);
		LAi_SetImmortal(rChar, false);
		LAi_Group_MoveCharacter(rChar, "ContraMeetManQuest_Group1");
	}
	LAi_Group_SetRelation("ContraMeetManQuest_Group1", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_Group_FightGroups("ContraMeetManQuest_Group1", LAI_GROUP_PLAYER, true);
	LAi_SetFightMode(PChar, true);
	ChangeContrabandRelation(PChar, -15); // Хотим рубнуть контров - отношение в минус
	SetGameModeCondition("ContraMeetManQuest_CheckContraDead");
}

void ContraMeetManQuest_CheckContraDead()
{
	if(LAi_isDead(CharacterFromID("ContraMeetManQuest_Contrick_0")) && LAi_isDead(CharacterFromID("ContraMeetManQuest_Contrick_1")))
	{
		DeleteGameModeCondition("ContraMeetManQuest_CheckContraDead");
		Log_TestInfo("Контрабандистов убили.");
		LAi_SetFightMode(PChar, false);
		LAi_LocationFightDisable(LoadedLocation, true);
		ref rChar = CharacterFromID("ContraMeetManQuest_QuestMan");
		PChar.GenQuest.ContraMeetMan.ContraIsDead = true;
		LAi_SetActorType(rChar);
		LAi_ActorDialog(rChar, PChar, "", -1, 5);	
	}
}
//=====================================================================================================================================
// <-- Генератор контрабандистов. Встреча в бухте
//=====================================================================================================================================

//=====================================================================================================================================
// Миниквест жителей. Поиск обручального кольца -->
//=====================================================================================================================================
void CitizenFindItemMiniQuest_CheckItem()
{
	if(CheckCharacterItem(PChar, "DOjeronRing")) // Проверка незначительная - тормозов не будет
	{
		DeleteGameModeCondition("CitizenFindItemMiniQuest_CheckItem");
		PChar.GenQuest.CitizenFindItem.GiveItem = true; // Флаг - взяли предмет
		string sCity = XI_ConvertString("Colony" + PChar.GenQuest.CitizenFindItem.City + "Gen");
		Log_Info(StringFromKey("GenQuests_4", sCity));
	}
}

void CitizenFindItemMiniQuest_Timer(string sQuest)
{
	DeleteGameModeCondition("CitizenFindItemMiniQuest_CheckItem");
	if(CheckAttribute(PChar, "GenQuest.CitizenFindItem.GiveItem")) // Если взяли предмет
	{
		RemoveItems(PChar, "DOjeronRing", 1);
		BackItemDescribe("DOjeronRing");
		items[FindItem("DOjeronRing")].Name = "itmname_DOjeronRing";
		DeleteAttribute(&items[FindItem("DOjeronRing")], "City");
	}
	else
	{
		string sCity = PChar.GenQuest.CitizenFindItem.City + + "_ExitTown";
		string sTemp = PChar.GenQuest.CitizenFindItem.ItemLocator;
		PChar.GenQuestRandItem.(sCity).(sTemp) = "potionrum";
		BackItemDescribe("DOjeronRing");
		items[FindItem("DOjeronRing")].Name = "itmname_DOjeronRing";
		DeleteAttribute(&items[FindItem("DOjeronRing")], "City");
	}
}
//=====================================================================================================================================
// <-- Миниквест жителей. Поиск обручального кольца 
//=====================================================================================================================================

//=====================================================================================================================================
// Warship. ЦЕРКОВНЫЙ ГЕНЕРАТОР КВЕСТ № 1 -->
//=====================================================================================================================================
void Church_GenQuest1_Timer(string sQuest)
{
	if(GetCharacterIndex("ChurchGenQuest1_Cap") != -1) // Если генерили
	{
		ref sld = CharacterFromID("ChurchGenQuest1_Cap");
		ChangeCharacterAddressGroup(sld, "none", "", ""); // Уберем кэпа
	}
	items[FindItem("Bible")].Name = "itmname_bible"; // Вернет аттрибуты
	BackItemDescribe("Bible");
	DeleteAttribute(items[FindItem("Bible")], "City");
	Group_DeleteGroup("ChurchGenQuest1_CapGroup"); // Потрем шип
	PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = "yes";
	PChar.GenQuest.ChurchQuest_1.Complete.Timer = true;
	AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "14");
	CloseQuestHeader(sQuestTitle);
}

void Church_GenQuest1_ChangeCapitanLocation(string sQuest)
{
	if(GetCharacterIndex("ChurchGenQuest1_Cap") == -1) return; // Может не быть	
	ref sld = CharacterFromID("ChurchGenQuest1_Cap");
	if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern")) // Кэп на судне
	{
		PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = "yes";
		sld.DeckDialogNode = "ChurchGenQuest_1_DeckDialog_1";
		return;
	}
	
	sld.Dialog.Filename = "GenQuests_Dialog.c";
	sld.Dialog.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
	sld.DeckDialogNode = "ChurchGenQuest_1_DeckDialog_1";
	FreeSitLocator(PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern", "Sit1");
	ChangeCharacterAddressGroup(sld, PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern", "sit", "Sit1");
	LAi_SetSitType(sld);
}

void Church_GenQuest1_DeleteCapitan(string sQuest)
{
	ref sld = CharacterFromID("ChurchGenQuest1_Cap");
	Group_DeleteGroup("ChurchGenQuest1_CapGroup");
	PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = "yes";
	sld.LifeDay = 0;
}
//=====================================================================================================================================
// <-- ЦЕРКОВНЫЙ ГЕНЕРАТОР. КВЕСТ № 1
//=====================================================================================================================================

//=====================================================================================================================================
// Warship. ЦЕРКОВНЫЙ ГЕНЕРАТОР КВЕСТ № 2 -->
//=====================================================================================================================================
void Church_GenQuest2_GenerateBandits(string sQuest)
{
	Log_TestInfo("Зашли в локацию с бандюгами");

	ref location = &locations[reload_location_index];
	LAi_LocationFightDisable(location, true);
	string encGenGroup = LAi_FindRandomLocator("encdetector");
	string sGenTemp = "locators." + encGenGroup;
	string sLocGroup;
	aref arGenAll;
	makearef(arGenAll, location.(sGenTemp));
	
	int iBanditsCount = GetAttributesNum(arGenAll); //кол-во человек в банде
	if (iBanditsCount <= 0) iBanditsCount = 1;
	if (iBanditsCount >= 4) iBanditsCount = 3 + rand(1);	// Чаще всего так и бывает
	
	iGenRank = GetCoffDiff(sti(PChar.rank), 1000);
	if (iGenRank < MOD_SKILL_ENEMY_RATE) iGenRank = MOD_SKILL_ENEMY_RATE;
	
	PChar.GenQuest.ChurchQuest_2.BanditsCount = iBanditsCount;
	if(LAi_GetLocatorNum("encdetector") > 0) 	sLocGroup = "encdetector";
	else										sLocGroup = "goto";
	
	for(int i=0; i<iBanditsCount; i++)
	{
		ref rChar = GetCharacter(NPC_GenerateCharacter("Church_GenQuest2_Bandit_" + i, "citiz_" + (rand(9)+41), "man", "man", iGenRank, PIRATE, -1, true, "marginal"));
		if(i == 0) // Главарь банды
		{
			rChar.SaveItemsForDead = true; // сохранять на трупе вещи
			rChar.DontClearDead = true;
		}
		SetFantomParamFromRank(rChar, iGenRank, true);
//		sGenlocator = GetAttributeName(GetAttributeN(arGenAll, i)); 
//		ChangeCharacterAddressGroup(rChar, location.id, encGenGroup, sGenlocator);
//		ChangeCharacterAddressGroup(rChar, location.id, "goto", "goto" + (i + 1));
		PlaceCharacter(rChar, sLocGroup, pchar.location);
		LAi_SetGuardianType(rChar);
		rChar.Dialog.FileName = "GenQuests_Dialog.c";
		LAi_SetImmortal(rChar, true);
		LAi_SetActorType(rChar);
		if (i == 0) LAi_ActorDialog(rChar, pchar, "", -1, 5); 
		else
		{	
			LAi_CharacterDisableDialog(rChar);
			LAi_ActorFollow(rChar, CharacterFromID("Church_GenQuest2_Bandit_0"), "", -1);
		}	
	}
	PChar.Quest.Church_GenQuest2_TimeIsLeft.over = "yes";
	chrDisableReloadToLocation = true;	
	
//	SetFunctionLocatorCondition("Church_GenQuest2_Dialog_With_Bandits", location.id, sLocGroup, encGenGroup, false);
}

void Church_GenQuest2_Dialog_With_Bandits(string sQuest)
{
	int iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
	for(int i=0; i<iBanditsCount; i++)
	{
		ref rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
		LAi_SetActorType(rChar);
		if (rChar.id == "Church_GenQuest2_Bandit_0")
			LAi_ActorDialog(rChar, PChar, "", -1, 5);
		else
			LAi_ActorFollow(rChar, CharacterFromID("Church_GenQuest2_Bandit_0"), "", -1);
		
	}
	
	// Завершаем прерывания на время
	PChar.Quest.Church_GenQuest2_TimeIsLeft.over = "yes";
	chrDisableReloadToLocation = true;
}

void Church_GenQuest2_DeadBandits(string sQuest)
{
	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.WayOfShortVariant"))
	{
		sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
		PChar.GenQuest.ChurchQuest_2.Complete.Short_With_Mon = true;	// Квест выполнен по упрощенному варианту
		Delay_DeleteGroup("Church_GenQuest2_Bandits_Group");
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "3");
		Log_TestInfo("Бандитов замочили. Нужно обыскать трупики и найти украденное (квест пройден по короткому варианту).");
	}
	
	DeleteAttribute(LoadedLocation, "DisableEncounters");
	chrDisableReloadToLocation = false;
}

void Church_GenQuest2_TimeIsLeft(string sQuest) // Не нашли бандюков в джунглях за 1 день
{
	Log_TestInfo("Время вышло, Вы не смогли отыскать грабителей - квест провален.");
	
	// Если прерывание отработало, значит бандюки сгенерились, а значит не будет еррора, когда мы будем получать ссылку на них
	if(!CheckAttribute(PChar, "Quest.Church_GenQuest2_GenerateBandits"))
	{
		int iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
		
		for(int i=0; i<iBanditsCount; i++)
		{
				ref rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				rChar.Dialog.CurrentNode = "Left_Time_Case";
				rChar.LifeDay = 0;
		}
	}
	
	PChar.Quest.Church_GenQuest2_GenerateBandits.over = "yes";
	PChar.Quest.Church_GenQuest2_Dialog_With_Bandits.over = "yes";
	ChangeCharacterComplexReputation(PChar,"nobility", -3);
	sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
	AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "13");
	AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase(StringFromKey("GenQuests_62"),StringFromKey("GenQuests_63")));
	AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName);
	CloseQuestHeader(sQuestTitle);
	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.QuestGangJungle")) // Потрем аттрибуты джунглей (короткий вариант прохождения)
	{
		LAi_LocationFightDisable(&locations[FindLocation(PChar.GenQuest.ChurchQuest_2.QuestGangJungle)], false);
		DeleteAttribute(&locations[FindLocation(PChar.GenQuest.ChurchQuest_2.QuestGangJungle)], "DisableEncounters");
	}
	
	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.QuestGangShore")) // Потрем аттрибуты бухты, если есть
	{
		LAi_LocationFightDisable(&locations[FindLocation(PChar.GenQuest.ChurchQuest_2.QuestGangShore)], false);
		DeleteAttribute(&locations[FindLocation(PChar.GenQuest.ChurchQuest_2.QuestGangShore)], "DisableEncounters");
	}
	DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");	// Трем все аттрибуты по церковному квесту
}

void Church_GenQuest2_BanditsIsEnemies_2_Clear(string sQuest)
{
	Delay_DeleteGroup("Church_GenQuest2_Bandits_Group");
}
//=====================================================================================================================================
// <-- ЦЕРКОВНЫЙ ГЕНЕРАТОР. КВЕСТ № 2
//=====================================================================================================================================

//=====================================================================================================================================
// Ugeen. ГЕНЕРАТОР "ПОВОД ДЛЯ СПЕШКИ "
//=====================================================================================================================================
void ReasonToFast_CheckHorse(string qName)
{
	if(!CheckAttribute(pchar, "questTemp.ReasonToFast.speakHorse"))
	{
		DeleteAttribute(pchar, "questTemp.ReasonToFast");
	}	
}

void ReasonToFast_MeetPatrolShore(string qName) // генерация патруля
{
	aref grp;
	ref chr, rCharacter;
	string encGroup, str, locator;
	int num, i, iNation, n;
	int iRank = sti(pchar.rank);
	ref pLoc;
	bool bOk = false;

	pLoc = &locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)];
	encGroup = LAi_FindRandomLocator("encdetector");
	str = "locators." + encGroup;
	makearef(grp, pLoc.(str));
	iNation = sti(pchar.questTemp.ReasonToFast.GuardNation); // нация патруля
	num = GetAttributesNum(grp); //кол-во человек в патруле
	if (num <= 0) num = 1;
	
	str = "Patrol"+ pLoc.index + "_";
	string sGroup = "PatrolGroup_" + pLoc.index; //имя группы
	LAi_group_SetLookRadius(sGroup, 30);
	LAi_group_SetHearRadius(sGroup, 30);	

	pchar.questTemp.ReasonToFast = "MeetPatrol";
	for (i = 0; i < num; i++)
	{
		if (i == 0)
		{					
			int iPatrolOfficer = NPC_GenerateCharacter(str + i, "off_"+NationShortName(iNation)+"_"+(rand(1)+1), "man", "man", iRank + 2, iNation, 1, true, "officer");
			chr = &characters[iPatrolOfficer];
			SetFantomParamFromRank(chr, iRank + 2, true);
			chr.greeting = "soldier_arest";
			chr.dialog.filename = "Enc_Patrol.c";
			if(sti(pchar.questTemp.ReasonToFast.p1) < GetCharacterSPECIAL(pchar, "LUCK") * 10)	
			{
				chr.dialog.currentnode = "First Time";
				pchar.questTemp.ReasonToFast = "MeetPatrolFail";
			}
			else
			{
				chr.dialog.currentnode = "Reason_To_Fast_1";
				bOk = true;
			}
		}
		else
		{
			if (i == 3)
			{
				chr = GetCharacter(NPC_GenerateCharacter(str + i, "mush_" + NationShortName(iNation) + "_" +(rand(2)+1), "man", "mushketer", iRank, iNation, 1, false, "soldier"));
				chr.dialog.filename = "Enc_Patrol.c";				
				chr.dialog.currentnode = "Node_2";
			}
			else
			{
				chr = GetCharacter(NPC_GenerateCharacter(str + i, "sold_"+NationShortName(iNation)+"_"+(rand(7)+1), "man", "man", iRank, iNation, 1, true, "soldier"));
				SetFantomParamFromRank(chr, iRank, true);
				chr.dialog.filename = "Enc_Patrol.c";				
				chr.dialog.currentnode = "Node_2";
			}
		}	
		chr.City = pchar.questTemp.ReasonToFast.city;
		chr.CityType = "soldier";
		chr.EncQty = num;		
		LAi_SetStayType(chr);
		LAi_group_MoveCharacter(chr, sGroup);
		pchar.questTemp.ReasonToFast.LocIdx = pLoc.index; 
		pchar.questTemp.ReasonToFast.PatrolNum = num;
		//Получим локатор для логина
		locator = GetAttributeName(GetAttributeN(grp, i));
		ChangeCharacterAddressGroup(chr, pLoc.id, encGroup, locator);
		LAi_SetActorType(chr);
		if (i == 0) LAi_ActorDialog(chr, pchar, "", -1, 0); 
		else LAi_ActorFollow(chr, &characters[iPatrolOfficer], "", -1);
	}
	if(bOk) // если это правильный патруль
	{
		LAi_LocationFightDisable(pLoc, true);	
		LAi_SetFightMode(pchar, false);
		LAi_LockFightMode(pchar, true);
	}
}

void ReasonToFast_DeletePatrolFromShore(string qName) //  прибъем патруль на берегу после разговора
{
	ref pLoc, rChar;
	
	int iPatrolCount = sti(pchar.questTemp.ReasonToFast.PatrolNum);
	pLoc = &locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)];
	string str = "Patrol"+ pLoc.index + "_";
	string sTemp = "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx;
	for(int i=0; i<iPatrolCount; i++)
	{
		if(i == 0) rChar = CharacterFromID(str + i);
		else rChar = CharacterFromID(str + i);		
		rChar.LifeDay = 0;
	}
	LAi_group_RemoveCheck(sTemp);
	LAi_group_Delete(sTemp);
}

void ReasonToFast_SpeakMayor(string qName)
{
	if(CheckAttribute(pchar,"questTemp.ReasonToFast.speakAfterPatrolDied") && pchar.questTemp.ReasonToFast.speakAfterPatrolDied == false)
	{
		AddQuestRecord("ReasonToFast", "13");			
		AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase(StringFromKey("GenQuests_64"),StringFromKey("GenQuests_65")));			
		CloseQuestHeader("ReasonToFast");
		DeleteAttribute(pchar, "questTemp.ReasonToFast");
	}
}

void ReasonToFast_GenerateHunter() // генерация ОЗГ
{
	ref chr;
		
	int iRank = sti(pchar.rank) + rand(MOD_SKILL_ENEMY_RATE);
	chr = GetCharacter(NPC_GenerateCharacter("ReasonToFast_Hunter", "mercen_"+(rand(14)+14), "man", "man", iRank, PIRATE, -1, true, "quest"));
	FantomMakeCoolFighter(chr, iRank, 80, 80, "blade_06", "pistol3", "grapeshot", 50);
	int jewelType = sti(pchar.questTemp.ReasonToFast.p4);
	string sItem = "jewelry" + jewelType; 
	AddItems(chr, sItem, 15); 
	chr.SaveItemsForDead = true;
	chr.dialog.Filename = "GenQuests_Dialog.c";
	chr.greeting = "Enc_Raiders"; 
	SetRandomNameToCharacter(chr);
	ChangeCharacterAddressGroup(chr, pchar.location, "reload", "reload1");
	LAi_group_MoveCharacter(chr, "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx);
	
	LAi_SetActorType(pchar); 
	LAi_ActorTurnToCharacter(pchar, chr);
	LAi_SetActorType(chr);
	SetActorDialogAny2Pchar(chr.id, "", 0.0, 1.0);
	LAi_ActorFollow(chr, pchar, "ActorDialog_Any2Pchar", -1);	
}

int ReasonToFast_GetVictimShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	int iShipType = SHIP_BARKENTINE;
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 5;
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21) iClass = 3 - rand(1);
	
	iShipType = GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	pchar.questTemp.ReasonToFast.ShipTypeName = XI_ConvertString(GetBaseShipParamFromType(iShipType, "Name"));
	
	return iShipType;
}

int ReasonToFast_GetVictimShipGoods()
{
	int iGoodIdx;
	switch (rand(6))
    {
        case 0 :
            iGoodIdx = GOOD_CHOCOLATE;
        break;
        case 1 :
            iGoodIdx = GOOD_TOBACCO;
        break;
        case 2 :
            iGoodIdx = GOOD_COFFEE;
        break;
        case 3 :
            iGoodIdx = GOOD_MAHOGANY;
        break;
        case 4 :
            iGoodIdx = GOOD_CINNAMON;
        break;
        case 5 :
            iGoodIdx = GOOD_EBONY;
        break;		
        case 6 :
            iGoodIdx = GOOD_COPRA;
        break;
    }
	return iGoodIdx;
}

void ReasonToFast_GenerateVictimShip(int iShipType, int iShipGoods) // генерация призового корабля
{
	int hcrew;
	int iNation = sti(pchar.questTemp.ReasonToFast.GuardNation);
	
	ref chref = GetCharacter(NPC_GenerateCharacter("VictimCap_1", "mercen_"+(rand(14)+1), "man", "man", 25, iNation, -1, true, "citizen"));

	chref.Ship.Name = pchar.questTemp.ReasonToFast.ShipName;			
    chref.Ship.Type = GenerateShipExt(iShipType, 1, chref);
    SetBaseShipData(chref);

    hcrew = GetMinCrewQuantity(chref);
    SetCrewQuantity(chref, hcrew);
    
    DeleteAttribute(chref,"ship.sails");
    DeleteAttribute(chref,"ship.masts");
    DeleteAttribute(chref,"ship.blots");
    DeleteAttribute(chref,"ship.hulls");
	
	Fantom_SetCannons(chref, "trade");
    Fantom_SetBalls(chref, "trade");
	
	int iSpace = GetCharacterFreeSpace(chref, iShipGoods);
	Fantom_SetCharacterGoods(chref, iShipGoods, iSpace, 1);
	
	string sGroup = "Sea_Victim_1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
    Group_SetType(sGroup, "trade");
        
    Group_AddCharacter(sGroup, "VictimCap_1");
    Group_SetGroupCommander(sGroup, "VictimCap_1");
	Group_SetAddress(sGroup, GetArealByCityName(pchar.questTemp.ReasonToFast.city),"quest_ships", "quest_ship_1");
	Group_SetTaskRunaway(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	
	pchar.quest.ReasonToFast_SetShip_1.win_condition.l1 = "Character_sink";
    pchar.quest.ReasonToFast_SetShip_1.win_condition.l1.character = "VictimCap_1";
    pchar.quest.ReasonToFast_SetShip_1.function = "ReasonToFast_KillVictim";
    
	pchar.quest.ReasonToFast_SetShip_2.win_condition.l1 = "Character_Capture";
    pchar.quest.ReasonToFast_SetShip_2.win_condition.l1.character = "VictimCap_1";
    pchar.quest.ReasonToFast_SetShip_2.function = "ReasonToFast_CaptureVictim";  
	
    SetTimerCondition("ReasonToFast_ClearVictim", 0, 0, 1, false);
}

// кэп пинаса утоп вместе с кораблём или ГГ уплыл на глобалку
void ReasonToFast_KillVictim(string qName)
{
	ref sld = characterFromId("VictimCap_1");
	sld.lifeDay = 0;
	pchar.quest.ReasonToFast_ClearVictim.over = "yes";
	pchar.quest.ReasonToFast_SetShip_1.over = "yes";
	pchar.quest.ReasonToFast_SetShip_2.over = "yes";
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	AddQuestRecord("ReasonToFast","19");
	CloseQuestHeader("ReasonToFast");
	Group_DeleteGroup("Sea_Victim_1");
	DeleteAttribute(pchar,"questTemp.ReasonToFast");
}

// кэп пинаса захвачен или прибит на абордаже
void ReasonToFast_CaptureVictim(string qName)
{
	ref sld = characterFromId("VictimCap_1");
	sld.lifeDay = 0;
	AddQuestRecord("ReasonToFast","18");
	Group_DeleteGroup("Sea_Victim_1");
	pchar.questTemp.ReasonToFast.SpeakOther = true; // допрыгался, к губеру или призонбоссу теперь низзя !!!!
	pchar.quest.ReasonToFast_ClearVictim.over = "yes";
	pchar.quest.ReasonToFast_SetShip_1.over = "yes";
	pchar.quest.ReasonToFast_SetShip_2.over = "yes";
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
    pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";    
}

void ReasonToFast_RemoveVictim()
{
	ref sld = characterFromId("VictimCap_1");
	sld.lifeDay = 0;
	Group_DeleteGroup("Sea_Victim_1"); // прибъем пинас
	pchar.quest.ReasonToFast_ClearVictim.over = "yes";	
	pchar.quest.ReasonToFast_SetShip_1.over = "yes";
	pchar.quest.ReasonToFast_SetShip_2.over = "yes";
	DeleteAttribute(pchar, "GenQuest.CannotWait");
}

void ReasonToFast_PreparePirateShip(string qName) // генерация пиратского корабля
{
	ref sld;
	int iRankPir = sti(pchar.rank) + 5 + rand(MOD_SKILL_ENEMY_RATE);
	int iShipRank, iShipType;
	string sTemp, sTemp1;
	
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 5;
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21) iClass = 3 - rand(1);
	
	iShipType = GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY);
	sTemp1 = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(iShipType, "Name")));
		
	Log_QuestInfo("Генерим пиратский корабль на глобалке.");
	
	sld = GetCharacter(NPC_GenerateCharacter("PirateCapt", "mercen_"+(rand(14)+14), "man", "man", iRankPir, PIRATE, 30, true, "quest"));	
	sld.dialog.filename      = "GenQuests_Dialog.c";
	sld.dialog.currentnode   = "ReasonToFast_FightCap";
	sTemp = GenerateRandomNameToShip(PIRATE);
	FantomMakeCoolSailor(sld, iShipType, sTemp, "", 50+rand(40), 50+rand(40), 50 + rand(40));
	sld.cirassId = Items_FindItemIdx("cirass1");  // предмета нет, но влияение есть
    FantomMakeCoolFighter(sld, makeint(pchar.rank) + rand(10) + 5, 60 + rand(30), 50, "blade_06", "pistol3","grapeshot", 80);
		
    sld.SuperShooter  = true;
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Energaiser"); 					// скрытый перк даёт 1.5 к приросту энергии, даётся ГГ и боссам уровней
	
	LAi_SetHP(sld, 100 + makeint(pchar.rank) * 2, 100 + makeint(pchar.rank) * 2);

	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "quest_ship"; 
	sld.mapEnc.Name = sTemp1 + " '" + sTemp + "'";
	
	sld.ship.Crew.Morale = 60 + rand(20);
	ChangeCrewExp(sld, "Sailors", 60 + rand(20));
	ChangeCrewExp(sld, "Cannoners", 60 + rand(20));
	ChangeCrewExp(sld, "Soldiers", 60 + rand(20));
	
	string sGroup = "Quest_Ship";  
	Group_DeleteGroup(sGroup);
    Group_FindOrCreateGroup(sGroup);
	Group_AddCharacter(sGroup, "PirateCapt");
    Group_SetGroupCommander(sGroup, "PirateCapt");

	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_SetTaskAttack(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	
	SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY);
	
	Map_CreateWarrior("", "PirateCapt", 7);

    pchar.quest.ReasonToFast_PirateShip_Dead.win_condition.l1 = "NPC_Death";
	pchar.quest.ReasonToFast_PirateShip_Dead.win_condition.l1.character = "PirateCapt";
	pchar.quest.ReasonToFast_PirateShip_Dead.function = "ReasonToFast_PirateCapt_Dead";
	
	pchar.quest.ReasonToFast_PirateShip_Sink.win_condition.l1 = "Character_sink";
    pchar.quest.ReasonToFast_PirateShip_Sink.win_condition.l1.character = "PirateCapt";
    pchar.quest.ReasonToFast_PirateShip_Sink.function = "ReasonToFast_PirateCapt_Sink";
}

void ReasonToFast_PirateCapt_Dead(string qName)
{
	ref sld = characterFromId("PirateCapt");
	sld.lifeDay = 0;
	pchar.quest.ReasonToFast_PirateShip_Sink.over = "yes";
	pchar.quest.ReasonToFast_PirateShip_Dead.over = "yes";
	AddQuestRecord("ReasonToFast","22");
	AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT));
	CloseQuestHeader("ReasonToFast");
	DeleteAttribute(pchar,"questTemp.ReasonToFast");
}

void ReasonToFast_PirateCapt_Sink(string qName)
{
	ref sld = characterFromId("PirateCapt");
	sld.lifeDay = 0;
	pchar.quest.ReasonToFast_PirateShip_Sink.over = "yes";
	pchar.quest.ReasonToFast_PirateShip_Dead.over = "yes";
	AddQuestRecord("ReasonToFast","25");
	AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT));
	CloseQuestHeader("ReasonToFast");
	DeleteAttribute(pchar,"questTemp.ReasonToFast");
}

void ReasonToFast_SetHunterCoastal()
{
	pchar.quest.ReasonToFast_SetHunterPort_1.win_condition.l1 = "Location_Type";
	pchar.quest.ReasonToFast_SetHunterPort_1.win_condition.l1.location_type = "town"; 
	pchar.quest.ReasonToFast_SetHunterPort_1.function = "ReasonToFast_SetTreasureHunter";
	
	pchar.quest.ReasonToFast_SetHunterPort_2.win_condition.l1 = "Location_Type";
	pchar.quest.ReasonToFast_SetHunterPort_2.win_condition.l1.location_type = "seashore"; 
	pchar.quest.ReasonToFast_SetHunterPort_2.function = "ReasonToFast_SetTreasureHunter";
}

void ReasonToFast_SetTreasureHunter(string qName)
{
    int    j, i, k;
	string sTemp, sCapId, sLocGroup;
	ref    sld;
	bool   ok;

	pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
	pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
	
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); 
	
	Pchar.GenQuest.Hunter2Pause  = true;	
	sCapId = "LandHunter0";
	sTemp = "LAND_HUNTER";
	ok = true;
	arrayNPCModelHow = 0;
	
    for (i = 1; i <= 3; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", 5, PIRATE, 1, true, "hunter"));
        SetFantomParamHunter(sld); 
        sld.dialog.filename = "Hunter_dialog.c";
		if(pchar.questTemp.ReasonToFast == "GetMap" || pchar.questTemp.ReasonToFast == "LakeyExitSuccess") // получена карта или сокровища от лакея
		{
			sld.Dialog.CurrentNode = "ReasonToFast_HunterShore1";
		}
		if(pchar.questTemp.ReasonToFast == "LakeyExitFail") // лакей сбежал
		{
			sld.Dialog.CurrentNode = "ReasonToFast_HunterShore2";
		}
		if(pchar.questTemp.ReasonToFast == "GetTreasure") // ГГ взял сокровища из клада
		{
			sld.Dialog.CurrentNode = "ReasonToFast_THunter_1";
		}	
        sld.greeting = "hunter";
        sld.location = "none"; // вот где порылась собака!!!!!!!!!!!
		
		SetModelPirate(sld);
        k = 0;
		while (!CheckNPCModelUniq(sld) && k < 10)
		{
		    k++;
			SetModelPirate(sld);
		}
		arrayNPCModel[arrayNPCModelHow] = sld.model;
		arrayNPCModelHow++;
		
		LAi_SetActorTypeNoGroup(sld);
		
		if(LAi_GetLocatorNum("goto") > 0) 	sLocGroup = "goto";
		else								sLocGroup = "encdetector";
		
		if (PlaceCharacter(sld, sLocGroup, "random_must_be_near") == "" && i == 1) // fix если вдруг нет в локации
        {
            ok = false;
            break;
        }
		LAi_ActorFollow(sld, pchar, "", 8.0);
        LAi_group_MoveCharacter(sld, sTemp);		
	}	
	LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER_OWN, LAI_GROUP_NEITRAL);

	LAi_group_ClearAllTargets();
	LAi_SetFightModeForOfficers(false);
	if (ok)
    {
        pchar.HunterCost.Qty = i;
        sld = characterFromID(sCapId + "1");
        LAi_type_actor_Reset(sld);
        LAi_ActorDialog(sld, pchar, "", 4.0, 0);
		chrDisableReloadToLocation = true;
		bDisableFastReload = true; 
    }				
}

void ReasonToFast_GenerateTreasureMap(ref item)
{
    item.MapIslId   = GetIslandForTreasure();
    item.MapLocId   = GetLocationForTreasure(item.MapIslId);
    item.MapBoxId   = GetBoxForTreasure(item.MapIslId, item.MapLocId);
	item.MapOwnId   = GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_NOM);
	
	DeleteAttribute(item, "BoxTreasure");

	pchar.questTemp.ReasonToFast.Treasure.Island = item.MapIslId;
	pchar.questTemp.ReasonToFast.Treasure.Location = item.MapLocId;
	pchar.questTemp.ReasonToFast.Treasure.Locator = item.MapBoxId;
	
    pchar.quest.ReasonToFast_SetTreasureFromMap.win_condition.l1  = "location";
    pchar.quest.ReasonToFast_SetTreasureFromMap.win_condition.l1.location = item.MapLocId;
    pchar.quest.ReasonToFast_SetTreasureFromMap.function = "ReasonToFast_SetTreasureBoxFromMap"; 
}

void ReasonToFast_ExitFromTownFight(string qName)
{
	Log_QuestInfo("Блокируем выход на глобалку, ожидаем встречи с матросом");
	bQuestDisableMapEnter = true;
	QuestCloseSeaExit();
    DoQuestCheckDelay("ReasonToFast_MeetWithSailor", 1);
}

void ReasonToFast_SetTreasureBoxFromMap(string qName)
{
    aref   item;
    ref    loc;
    string box, itmName;
    aref   arToBox;
    aref   arFromBox;

    if (GetCharacterItem(pchar, "mapQuest") > 0 )
    {
        Log_Info(StringFromKey("GenQuests_16"));
        PlaySound("interface\notebook.wav");
		Statistic_AddValue(pchar, "Treasure", 1);
		Achievment_SetStat(8, 1);
		if(SandBoxMode)
		{
			//if(CheckAttribute(pchar,"questTemp.SanBoxTarget"))
			//{
				//if(makeint(pchar.questTemp.SanBoxTarget) > 3)
				//{
					Achievment_SetStat(101, 1);
				//}
			//}
		}
		
        // немного веселой жизни
        pchar.quest.ReasonToFast_SetTreasureHunter.win_condition.l1          = "ExitFromLocation";
        pchar.quest.ReasonToFast_SetTreasureHunter.win_condition.l1.location = pchar.location;
        pchar.quest.ReasonToFast_SetTreasureHunter.function    				= "ReasonToFast_SetTreasureHunter";   
		bDisableLandEncounters = true;	

        Items_FindItem("mapQuest", &item);
		
		itmName = "icollection"; // генерим сокровища
		item.BoxTreasure.(itmName) = sti(pchar.questTemp.ReasonToFast.p8); 
		
		itmName = "Chest"; // генерим сундуки
		item.BoxTreasure.(itmName) = sti(pchar.questTemp.ReasonToFast.p7); 

		itmName = "mineral5"; // генерим ведра
		item.BoxTreasure.(itmName) = rand(5) + 2;
		
		itmName = "mineral8"; // генерим  башмаки
		item.BoxTreasure.(itmName) = rand(7) + 4;
		
        box = item.MapBoxId;

        loc = &locations[FindLocation(item.MapLocId)];
        loc.(box).items = "";

        makearef(arToBox, loc.(box).items);
        makearef(arFromBox, item.BoxTreasure);
        CopyAttributes(arToBox, arFromBox);

        loc.(box) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
        loc.(box).Treasure =  true; // признак сокровища в сундуке
		loc.(box).ReasonToFastTreasure = true; // mitrokosta фикс двойных ОЗК

        DeleteAttribute(item, "MapIslId");
        TakeNItems(pchar, "mapQuest", -1);
		pchar.questTemp.ReasonToFast = "GetTreasure";
    }
}

void ReasonToFast_ClearTreasureBox(string LocId)
{
	ref loc;
	aref boxLocator;
	string locatorName;
	
	loc = &locations[FindLocation(LocId)];
			
	for (int i=1; i < MAX_HANDLED_BOXES; i++)
	{		
		locatorName = "box"+i;
		if(!CheckAttribute(loc, locatorName)) break;
		DeleteAttribute(loc, locatorName + ".items");
		loc.(locatorName).items = "";
		loc.(locatorName).money = 0;	
		loc.(locatorName) = Items_MakeTime(0, 0, 1, 2003); 		
	}
}

int ReasonToFast_CheckTreasure(string ItmName, int ReqQty)
{
	ref loc;
	string locatorName, sName;
	aref arItems, arCur;
	int itemsQty;
	
	loc = &locations[FindLocation(pchar.questTemp.ReasonToFast.Treasure.Location)];
	locatorName = pchar.questTemp.ReasonToFast.Treasure.Locator;
	
	makearef(arItems, loc.(locatorName).items)
		
    int Qty = GetAttributesNum(arItems);
    for (int a = 0; a < Qty; a++)
    {
        sName = GetAttributeName(GetAttributeN(arItems, a));
		if(sName == ItmName)
		{
			arCur = GetAttributeN(arItems,a);
			itemsQty = sti(GetAttributeValue(arCur));
			return ReqQty - itemsQty;
		}
    }
	return ReqQty;
}

int ReasonToFast_CheckTreasureQty(string ItmName, int ReqQty)
{
	int iQty, iNeedQty = 0;
	int iPassenger, cn;
	ref sld;

	iQty = GetCharacterItem(pchar, ItmName);
	if(iQty > 0) 
	{
		iNeedQty += iQty;
		if(iNeedQty >= ReqQty) return iNeedQty;
	}
	for (int io = 0; io < GetPassengersQuantity(pchar); io++)
	{
		iPassenger = GetPassenger(pchar, io);
		if (iPassenger != -1)
		{
			sld = GetCharacter(iPassenger);
			iQty = GetCharacterItem(sld, ItmName);
			if(iQty > 0) 
			{
				iNeedQty += iQty;
				if(iNeedQty >= ReqQty) return iNeedQty;
			}
		}
	}	
	return iNeedQty;
}

void ReasonToFast_GetTreasure(string ItmName, int ReqQty)
{
	int iQty;
	int iPassenger, cn;
	ref sld;
	
	// отберем предметы сначала у ГГ
	iQty = GetCharacterItem(pchar, ItmName);
	if(iQty > 0) 
	{
		TakeNItems(pchar, ItmName, -iQty);
		if(iQty == ReqQty) return;
		ReqQty = ReqQty - iQty;
	}	
	// теперь у офицеров и пассажиров
	for (int io = 0; io < GetPassengersQuantity(pchar); io++)
	{
		iPassenger = GetPassenger(pchar, io);
		if (iPassenger != -1)
		{
			sld = GetCharacter(iPassenger);
			iQty = GetCharacterItem(sld, ItmName);
			if(iQty > 0) 
			{
				TakeNItems(sld, ItmName, -iQty);
				if(iQty == ReqQty) return;
				ReqQty = ReqQty - iQty;
			}
		}
	}
	// у компаньонов
	for (int i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn != -1)
		{
			sld = GetCharacter(cn);
			iQty = GetCharacterItem(sld, ItmName);
			if(iQty > 0) 
			{
				TakeNItems(sld, ItmName, -iQty);
				if(iQty == ReqQty) return;
				ReqQty = ReqQty - iQty;
			}
		}
	}
}

bool ReasonToFast_CreateResidenceNPC(aref loc)
{
	ref chr;
	int iBaseCity = FindLocation(loc.fastreload + "_town");
	int iNation = GetCityNation(pchar.questTemp.ReasonToFast.city);
	
	if (!CheckAttribute(&locations[iBaseCity], "houseEnc")) return false;
		
	if (CheckAttribute(loc, "PlayHall") || CheckAttribute(loc, "Bedroom") || (loc.id.label  == "TownhallRoom") || CheckAttribute(loc, "Office"))
	{	
		string slai_group = GetNationNameByType(iNation) + "_citizens";		
	
		if (GetCharacterIndex("ReasonToFastLakey_1") > 0) return false; //если есть
		Log_QuestInfo("Генерим лакея");		
		chr = GetCharacter(NPC_GenerateCharacter("ReasonToFastLakey_1", "barmen_"+(rand(15)+1), "man", "man", 5, iNation, 1, true, "citizen"));
		chr.dialog.Filename = "GenQuests_Dialog.c"; 
		chr.dialog.currentnode = "ReasonToFast_Lakey";
		chr.CityType = "citizen";
		chr.city = loc.fastreload; //НЗГ
		chr.greeting = "worker";
		ChangeCharacterAddressGroup(chr, loc.id, "goto", "goto1");
		LAi_SetOwnerType(chr);
		LAi_group_MoveCharacter(chr, slai_group);	
		pchar.questTemp.ReasonToFast.LakeyLocation = loc.id;
		bDisableFastReload = true;
	}		
	return true;
}

void ReasonToFast_ClearLakey(string qName)
{
	AddQuestRecord("ReasonToFast","19");
	CloseQuestHeader("ReasonToFast");
	if (GetCharacterIndex("ReasonToFastLakey_1") > 0) // прибъем лакея если он есть
	{
		ref sld = CharacterFromID("ReasonToFastLakey_1");
		sld.LifeDay = 0;
	}	
	DeleteAttribute(pchar,"questTemp.ReasonToFast");
}

void ReasonToFast_InitVariables()
{
	int s1, s2;

	pchar.questTemp.ReasonToFast.p1 = rand(100);
	pchar.questTemp.ReasonToFast.p2 = rand(100);
	pchar.questTemp.ReasonToFast.p3 = "l" + rand(GetNamesCount(NAMETYPE_MAIN) - 1); 	// id пиратского атамана
	pchar.questTemp.ReasonToFast.p4 = rand(3) + 1; 	// id камня (1-4) 
	pchar.questTemp.ReasonToFast.p5 = (110 - GetSummonSkillFromName(pchar, SKILL_FORTUNE)) * MOD_SKILL_ENEMY_RATE * 1000;	
	pchar.questTemp.ReasonToFast.p6 = GenQuest_GenerateGoodBlade(); // генерация клинка
	s1 = GetCharacterSPECIAL(pchar,"Charisma");
	s1 = s1 - rand(makeint(s1/2));
	s2 = GetCharacterSPECIAL(pchar,"Intellect");
	s2 = s2 - rand(makeint(s2/2));
	pchar.questTemp.ReasonToFast.p7 = s1;
	pchar.questTemp.ReasonToFast.p8 = s2;	
	s1 = GetCharacterSPECIAL(pchar,"Charisma");
	s2 = GetCharacterSPECIAL(pchar,"Intellect");
	pchar.questTemp.ReasonToFast.p9 = 50 * (5 + s1 - 2 * rand(makeint(s1/2)) + (s2 - 2 * rand(makeint(s2/2))) * 4) * (200 + GetSummonSkillFromName(pchar, SKILL_COMMERCE));
	pchar.questTemp.ReasonToFast.p10 = 4500000 * (s1 + 4 * s2)/(200 + GetSummonSkillFromName(pchar, SKILL_COMMERCE));
	pchar.questTemp.ReasonToFast.target = rand(1);
	if(rand(1) == 0) 
	{ 
		pchar.questTemp.ReasonToFast.map = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1); 
		pchar.questTemp.ReasonToFast.mapIdx = NAMETYPE_NICK;
	}
	else
	{ 
		pchar.questTemp.ReasonToFast.map = "l" + rand(GetNamesCount(NAMETYPE_VIP) - 1);
		pchar.questTemp.ReasonToFast.mapIdx = NAMETYPE_VIP;
	}
	// ручками трем этот атрибут :( , если квест взят во второй раз
	if(CheckAttribute(pchar,"questTemp.ReasonToFast.speakOther")) DeleteAttribute(pchar,"questTemp.ReasonToFast.speakOther");
	if(CheckAttribute(pchar,"questTemp.ReasonToFast.speakAfterPatrolDied")) DeleteAttribute(pchar,"questTemp.ReasonToFast.speakAfterPatrolDied");
}
//=====================================================================================================================================
// <-- ГЕНЕРАТОР "ПОВОД ДЛЯ СПЕШКИ "
//=====================================================================================================================================

//=====================================================================================================================================
// Warship. ГЕНЕРАТОР "СГОРЕВШЕЕ СУДНО" -->
//=====================================================================================================================================
void BurntShipQuest_TimeIsOver(String _quest)
{
	ref character = CharacterFromID(PChar.Quest.(_quest).PortmanId);
	
	SetRandomNameToCharacter(character);
	character.model = "usurer_" + (rand(7) + 1);
	
	character.Quest.BurntShip.TimeIsOver = true;
}
//=====================================================================================================================================
// <-- ГЕНЕРАТОР "СГОРЕВШЕЕ СУДНО"
//=====================================================================================================================================

//=====================================================================================================================================
// Warship. ГЕНЕРАТОР "ПИРАТЫ НА НЕОБИТАЕМОМ ОСТРОВЕ" -->
//=====================================================================================================================================
void PiratesOnUninhabited_LocationExit(String _quest)
{
	int index;

	for(int i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
	{
		index = GetCharacterIndex("PirateOnUninhabited_" + i);
		
		if(index != -1)
		{
			Characters[index].LifeDay = 0;
			SaveCurrentNpcQuestDateParam(&Characters[index], "LifeTimeCreate");
		}
	}
	
	DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
}

void PiratesOnUninhabited_LocationExit_Good(String _quest)
{
	for(int i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
	{
		ChangeCharacterAddressGroup(CharacterFromID("PirateOnUninhabited_" + i), "none", "", "");
	}
}

void PiratesOnUninhabited_OnShore(String _quest)
{
	ref character;
	
	if(!CheckAttribute(LoadedLocation, "onUninhabitedIsland"))
	{
		for(int i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
		{
			character = CharacterFromID("PirateOnUninhabited_" + i);
			
			ChangeCharacterAddressGroup(character, PChar.location, "goto", "goto" + (i + 1));
			LAi_SetActorTypeNoGroup(character);
			
			if(i == 0)
			{
				if(!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.TreasureMap"))
				{
					if(!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.ClearShip")) // Признак варианта, когда нужно захватить корабль
					{
						character.dialog.currentnode = "PiratesOnUninhabited_12";
					}
					else
					{
						character.dialog.currentnode = "PiratesOnUninhabited_51";
					}
				}
				else
				{
					character.dialog.currentnode = "PiratesOnUninhabited_26";
				}
				
				LAi_ActorDialog(character, PChar, "", 7.0, 0.0);
			}
			else
			{
				LAi_ActorFollow(character, PChar, "", 7.0);
			}
		}
		
		// Затрем второе прерывание
		PChar.Quest.PiratesOnUninhabited_OnShore.over = "yes";
		PChar.Quest.PiratesOnUninhabited_OnMayak.over = "yes";
	}
}

void PiratesOnUninhabited_TreasureLose(String _quest)
{
	PChar.GenQuest.PiratesOnUninhabited.TreasureLose = "true";
}

void PiratesOnUninhabited_InTreasureLoc(String _quest)
{
	ref location = &Locations[FindLocation(PChar.GenQuest.PiratesOnUninhabited.TreasureShore)];
	ref character;
	String boxId = PChar.GenQuest.PiratesOnUninhabited.TreasureBox;
	
	String model[10];
	String attribute;
	aref boxItems;
	int i = 0;
	int count, temp, rank;
	
	model[0] = "citiz_41";
	model[1] = "citiz_42";
	model[2] = "citiz_43";
	model[3] = "citiz_44";
	model[4] = "citiz_45";
	model[5] = "citiz_46";
	model[6] = "citiz_47";
	model[7] = "citiz_48";
	model[8] = "citiz_49";
	model[9] = "citiz_50";
	
	makearef(boxItems, location.(boxId).items);
	Log_Info(StringFromKey("GenQuests_16"));
	Statistic_AddValue(Pchar, "Treasure", 1);
	Achievment_SetStat(8, 1);
	if(SandBoxMode)
	{
		//if(CheckAttribute(pchar,"questTemp.SanBoxTarget"))
		//{
			//if(makeint(pchar.questTemp.SanBoxTarget) > 3)
			//{
				Achievment_SetStat(101, 1);
			//}
		//}
	}
	
	PChar.Quest.PiratesOnUninhabited_TreasureLose.over = "yes";
	
	if(!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.TreasureLose"))
	{
		count = 2 + makeint(MOD_SKILL_ENEMY_RATE / 3) + hRand(1, location.id);
		
		PChar.GenQuest.PiratesOnUninhabited.ShorePiratesQty = count;
		
		rank = sti(PChar.rank);
		
		while(i < count)
		{
			temp = rand(9);
			
			if(model[temp] != "")
			{
				if(!CheckAttribute(location, "locators.goto.goto" + (i + 1))) // Нет больше локаторов
				{
					PChar.GenQuest.PiratesOnUninhabited.ShorePiratesQty = i;
					break;
				}
				
				attribute = "l" + (i + 1);
				
				character = GetCharacter(NPC_GenerateCharacter("PirateOnUninhabited_ShorePirate" + i, model[temp], "man", "man", rank, PIRATE, -1, true, "marginal"));
				SetFantomParamFromRank(character, rank, true);
				ChangeCharacterAddressGroup(character, location.id, "goto", "goto" + (i + 1));
				character.dialog.filename = "GenQuests_Dialog.c";
				character.dialog.currentnode = "PiratesOnUninhabited_34";
				character.greeting = "Enc_Raiders";
				LAi_SetWarriorTypeNoGroup(character);
				LAi_Group_MoveCharacter(character, "PiratesOnUninhabited_ShoreGroup");
				LAi_Group_SetRelation("PiratesOnUninhabited_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				
				PChar.Quest.PiratesOnUninhabited_OpenChest.win_condition.(attribute) = "NPC_Death";
				PChar.Quest.PiratesOnUninhabited_OpenChest.win_condition.(attribute).character = "PirateOnUninhabited_ShorePirate" + i;
				
				i++;
				model[temp] = "";
			}
		}
		
		PChar.Quest.PiratesOnUninhabited_OpenChest.function = "PiratesOnUninhabited_OpenChest";
		
		PChar.Quest.PiratesOnUninhabited_ShoreTreasureLose.win_condition.l1 = "Timer";
		PChar.Quest.PiratesOnUninhabited_ShoreTreasureLose.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		PChar.Quest.PiratesOnUninhabited_ShoreTreasureLose.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		PChar.Quest.PiratesOnUninhabited_ShoreTreasureLose.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		PChar.Quest.PiratesOnUninhabited_ShoreTreasureLose.function = "PiratesOnUninhabited_ShoreTreasureLose"; // belamour gen
		
		// Серебро да золото
		if(rand(2) == 1)
		{
			boxItems.chest = 1 + rand(14);
		}
		else
		{
			boxItems.jewelry2 = 10 + rand(3);
		}
		
		if(rand(2) == 1)
		{
			boxItems.icollection = 1 + rand(4);
		}
		
		if(rand(1) == 1)
		{
			boxItems.jewelry1 = 15 + rand(100);
		}
		
		if(rand(1) == 1)
		{
			boxItems.jewelry3 = 15 + rand(100);
		}
		
		if(rand(1) == 1)
		{
			boxItems.jewelry5 = 15 + rand(100);
		}
		
		if(rand(1) == 1)
		{
			boxItems.jewelry6 = 5 + rand(100);
		}
		
		if(rand(4) == 1)
		{
			boxItems.cirass3 = 1;
		}
		if (hrand(7, location.id) == 1 && CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты
		{
			string amap = SelectAdmiralMaps();
			if (amap != "") boxItems.(amap)	= 1;
		}
		
		location.(boxId) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
		location.(boxId).QuestClosed = true;
		location.(boxId).Treasure = true; // Признак сокровища в сундуке
		location.(boxId).PiratesOnUninhabitedTreasure = true;
		
		Log_TestInfo("Пираты на необитайке: сгенерились стражи клада");
	}
	else
	{
		// Тут ничего вообще - не успели
		
		PChar.Quest.PiratesOnUninhabited_ClearQuest.win_condition.l1 = "ExitFromLocation";
		PChar.Quest.PiratesOnUninhabited_ClearQuest.win_condition.l1.Location = PChar.GenQuest.PiratesOnUninhabited.TreasureShore;
		PChar.Quest.PiratesOnUninhabited_ClearQuest.function = "PiratesOnUninhabited_ClearQuest";
		
		Log_TestInfo("Пираты на необитайке: пришли поздно, ничего не найдем");
	}
	
	TraderHunterOnMap(false); // Немного веселой жизни
}

// Зарубили пиратов, можно лезть в сундук
void PiratesOnUninhabited_OpenChest(String _quest)
{
	DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.PiratesOnUninhabited.TreasureShore)], PChar.GenQuest.PiratesOnUninhabited.TreasureBox + ".QuestClosed");
	
	Log_TestInfo("Пираты на необитайке: зарубили пиратов, можно лезть в сундук");
}

// После входа в локу прошёл день - чистим сундуки и убираем пиратов
void PiratesOnUninhabited_ShoreTreasureLose(String _quest)
{
	ref location = &Locations[FindLocation(PChar.GenQuest.PiratesOnUninhabited.TreasureShore)];
	int index;
	String boxId = PChar.GenQuest.PiratesOnUninhabited.TreasureBox;

	for(int i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.ShorePiratesQty); i++)
	{
		index = GetCharacterIndex("PirateOnUninhabited_ShorePirate" + i);
		
		if(index != -1)
		{
			Characters[index].LifeDay = 0;
		}
	}
	
	DeleteAttribute(location, boxId + ".items");
	DeleteAttribute(location, boxId + ".Treasure");
	DeleteAttribute(location, boxId + ".PiratesOnUninhabitedTreasure");
	DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.PiratesOnUninhabited.TreasureShore)], PChar.GenQuest.PiratesOnUninhabited.TreasureBox + ".QuestClosed"); // belamour gen
	PiratesOnUninhabited_ClearQuest(""); // Для записи в СЖ
}

// Выход из локации, в случае, если пришли позже 10 дней
void PiratesOnUninhabited_ClearQuest(String _quest)
{
	String title = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
	
	AddQuestRecordEx(title, "PiratesOnUninhabited", "8");
	AddQuestUserData(title, "sSex", GetSexPhrase(StringFromKey("GenQuests_64"),StringFromKey("GenQuests_65")));
	AddQuestUserData(title, "shore", LowerFirst(XI_ConvertString(PChar.location + "Gen"))); // belamour gen
	CloseQuestHeader(title);
	
	DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
}
void prosralisrok(string qName)//просрочили  // лесник если просрочили поиск корабля
{
	PChar.GenQuest.ShipWreck_BadPirate.ClearShip = true;
	Map_ReleaseQuestEncounter("ShipWreck_BadPirate"); //лесник . убирае с глоалки
	CloseQuestHeader("ShipWrecked");
	if (IsEntity(&worldMap) || bSeaActive) 
	{
	pchar.quest.qazwsx.win_condition.l1 = "Location_Type";
	pchar.quest.qazwsx.win_condition.l1.location_type = "town";
	pchar.quest.qazwsx.function = "Removepiratov";
	log_info(StringFromKey("GenQuests_17"));
	}
    else
	{
	sld = CharacterFromID("ShipWreck_0");
	RemovePassenger(Pchar, sld);
	sld.lifeday = 0;
	log_info(StringFromKey("GenQuests_18"));
	PlaySound("interface\notebook.wav");
	}
	DeleteAttribute(PChar, "GenQuest.ShipWreck");
}
void Removepiratov(string qName)//удалить негоцианта  лесник
{
	sld = CharacterFromID("ShipWreck_0");
	RemovePassenger(Pchar, sld);
	sld.lifeday = 0;
	log_info(StringFromKey("GenQuests_19"));
	PlaySound("interface\notebook.wav");
	DeleteAttribute(PChar, "GenQuest.GenQuest.ShipWreck");
}	
void PiratesOnUninhabited_ShipSink(String _quest)
{
	PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
	Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
	
	PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1 = "Location_Type";
	PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1.location_type = "seashore";
	PChar.Quest.PiratesOnUninhabited_OnShore.again = true;
	PChar.Quest.PiratesOnUninhabited_OnShore.function = "PiratesOnUninhabited_OnShore";
	
	PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1 = "Location_Type";
	PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1.location_type = "mayak";
	PChar.Quest.PiratesOnUninhabited_OnMayak.again = true;
	PChar.Quest.PiratesOnUninhabited_OnMayak.function = "PiratesOnUninhabited_OnShore";
	
	Log_TestInfo("PiratesOnUninhabited_ShipSink");
}

void PiratesOnUninhabited_CapDeath(String _quest)
{
	float locx, locy, locz;
	ref character = CharacterFromID("PirateOnUninhabited_0");
	
	GetCharacterPos(PChar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(character, PChar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
	
	LAi_SetActorTypeNoGroup(character);
	character.dialog.currentnode = "PiratesOnUninhabited_49";
	LAi_ActorDialog(character, PChar, "", 5.0, 0.0);
	
	Log_TestInfo("PiratesOnUninhabited_CapDeath");
}
//=====================================================================================================================================
// <-- ГЕНЕРАТОР "ПИРАТЫ НА НЕОБИТАЕМОМ ОСТРОВЕ"
//=====================================================================================================================================

//=====================================================================================================================================
// Ugeen. МИНИ-ГЕНЕРАТОРЫ  "ВЗРЫВ ИЛИ ЭПИДЕМИЯ НА ВРАЖЕСКОМ КОРАБЛЕ"
//=====================================================================================================================================
bool CheckShipSituation_GenQuest()
{
	if(CheckAttribute(pchar,"GenQuest.ShipSituation.Explosion") || CheckAttribute(pchar,"GenQuest.ShipSituation.Epidemy")) return true;
	else return false;
}

void RemoveCrewEpidemy_GenQuest()
{
	ref mainCh = GetMainCharacter(); 
	ref chref;
	int i, cn, crew, hcrew;
	int ShipType;
	
	Log_SetStringToLog(StringFromKey("GenQuests_20"));
	for(i = 0; i < COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(mainCh,i);
		if(cn >= 0)
		{
			chref = GetCharacter(cn);
			if (!GetRemovable(chref)) continue;
			ShipType = sti(chref.Ship.Type);
			crew = makeint(GetCrewQuantity(chref)/(20 - 10 * GetCrewQuantity(chref)/GetMaxCrewQuantity(chref) + GetCharacterSPECIAL(pchar,"Luck")));
			if(ShipType != sti(pchar.GenQuest.ShipSituation.Epidemy.ShipType) && !IsMainCharacter(chref))
			{
				crew = makeint(crew/2);
			}
			Log_SetStringToLog(StringFromKey("GenQuests_21", chref.Ship.Name, crew));
			Statistic_AddValue(mainCh, "Sailors_dead", crew);
			AddMementoShipBonus(crew);
			Achievment_SetStat(21, crew);
			hcrew = GetCrewQuantity(chref);
			SetCrewQuantity(chref, hcrew - crew);
		}
	}
}

int CheckShipSituationDaily_GenQuest(ref refChar)
{
	int cn = 1;
	int ShipType = sti(refChar.Ship.Type);
	bool bOk;
	
	if(CheckAttribute(pchar,"GenQuest.ShipSituation.Epidemy"))
	{
		bOk = CheckAttribute(pchar,"GenQuest.ShipSituation.Epidemy.ShipType") && (ShipType == sti(pchar.GenQuest.ShipSituation.Epidemy.ShipType));
		if(bOk || IsMainCharacter(refChar))
		{
			switch(sti(pchar.GenQuest.ShipSituation.Epidemy))
			{
				case ShipSituation_0:
					cn = 1;
				break;
				case ShipSituation_1:
					cn = 2;
				break;
				case ShipSituation_2:
					cn = 2;
				break;
				case ShipSituation_3:
					cn = 3;
				break;
				case ShipSituation_4:
					cn = 1;
				break;
			}
		}	
	}
	return cn;
}

// освобождаем квесты и устанавливаем таймер на повторную генерацию ситуаций
void SetFreeQuestAboardShipSituation(string qName)
{
	if(CheckShipSituation_GenQuest()) 
	{
		DeleteAttribute(pchar,"GenQuest.ShipSituation");
	}	
	bSeaCanGenerateShipSituation = false;
	pchar.CanGenerateShipSituation = false;	
	SetFunctionTimerCondition("CanGenerateQuestAboardShipSituation", 0, 0, rand(15) + 30, false);
}

// можем генерировать ситуацию ещё раз до упора, пока на неё не напорется геймер 
void CanGenerateQuestAboardShipSituation(string qName)
{
	bSeaCanGenerateShipSituation = true;
	pchar.CanGenerateShipSituation = true;	
}

// проверка квестовой ситуации перед выходом из каюты поверженного кэпа в режим "море"
void CheckCaptainFreeQuestAboardSituation()
{
	ref sld;
	if(CheckShipSituation_GenQuest())
	{
		if(CheckAttribute(pchar,"GenQuest.ShipSituation.Explosion")) 
		{
			sld = CharacterFromID(pchar.GenQuest.ShipSituation.Explosion.CapId);
			SetCaptainFreeQuestAboardSituation(sld);
		}
		if(CheckAttribute(pchar,"GenQuest.ShipSituation.Epidemy")) 
		{
			sld = CharacterFromID(pchar.GenQuest.ShipSituation.Epidemy.CapId);			
			pchar.GenQuest.ShipSituation.Epidemy.ShipName = sld.Ship.Name;
			pchar.GenQuest.ShipSituation.Epidemy.ShipType = sti(sld.Ship.Type);
			if(pchar.GenQuest.ShipSituation.Epidemy.CapState == "Died") // кэп помер - вот бедолага
			{
				SetCaptainDiedQuestAboardSituation(sld);
				ShipSituation_SetConsequence(sti(pchar.GenQuest.ShipSituation.Epidemy));
			}
			if(pchar.GenQuest.ShipSituation.Epidemy.CapState == "Live") // кэп остался жить - недолго ему осталось
			{
				SetCaptainFreeQuestAboardSituation(sld);
				ShipSituation_SetConsequence(sti(pchar.GenQuest.ShipSituation.Epidemy));
			}	
		}	
	}	
}

// установка последствий или их отсутствий
void ShipSituation_SetConsequence(int iSituation)
{
	if(GetCharacterSPECIAL(pchar,"LUCK") * 10 > rand(120)) // шутник блин
	{
		DoQuestFunctionDelay("SetFreeQuestAboardShipSituation", 1.0); 
	}
	else // кэп не шутил
	{
		switch (iSituation)
		{
			case ShipSituation_0: // обшарили каюту или труп
				pchar.GenQuest.ShipSituation.Epidemy.Days = 3;
			break;
			case ShipSituation_1: // что-то делали в интерфейсе грабежа
				pchar.GenQuest.ShipSituation.Epidemy.Days = 7 + rand(4);
			break;
			case ShipSituation_2: // сажаем компаньона с командой на инфицированный корабль
				pchar.GenQuest.ShipSituation.Epidemy.Days = 15 + rand(5);
			break;
			case ShipSituation_3: // ГГ пересаживается на инфицированный корабль
				pchar.GenQuest.ShipSituation.Epidemy.Days = 15 + rand(5);
			break;
			case ShipSituation_4: // ничего не обшаривали
				pchar.GenQuest.ShipSituation.Epidemy.Days = 1;
			break;
		}
		pchar.GenQuest.ShipSituation.Epidemy.DaysQty = sti(pchar.GenQuest.ShipSituation.Epidemy.Days);
	}
}

void ShipSituation_CheckConsequence(int iSituation)
{
	int DayQty;
	if(sti(pchar.GenQuest.ShipSituation.Epidemy.Days) > 0)
	{
		DayQty = sti(pchar.GenQuest.ShipSituation.Epidemy.DaysQty) - sti(pchar.GenQuest.ShipSituation.Epidemy.Days);
		if(DayQty == 0)
		{
			ReOpenQuestHeader("ShipEpidemy");
		}
		switch(iSituation)
		{
			case ShipSituation_0:
				if(DayQty == 0)
				{
					pchar.Health.Damg = stf(pchar.chr_ai.hp_max)*10; 
					AddQuestRecord("ShipEpidemy","1");
					AddQuestUserData("ShipEpidemy", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
					AddQuestUserData("ShipEpidemy", "sShipName", pchar.GenQuest.ShipSituation.Epidemy.ShipName);					
				}
				else
				{
					if(DayQty < 3) pchar.Health.Damg = stf(pchar.chr_ai.hp_max)*5; 
				}
			break;
			case ShipSituation_1:
				if(DayQty == 0)
				{
					pchar.Health.Damg = stf(pchar.chr_ai.hp_max)*10; 
					ChangeOfficersLoyality("bad_all", 1);
					AddQuestRecord("ShipEpidemy","3");
					AddQuestUserData("ShipEpidemy", "sShipName", pchar.GenQuest.ShipSituation.Epidemy.ShipName);
					RemoveCrewEpidemy_GenQuest();					
				}
				else
				{
					if(DayQty < 3) pchar.Health.Damg = stf(pchar.chr_ai.hp_max)*5; 
				}	
			break;
			case ShipSituation_2:
				if(DayQty == 0)
				{
					pchar.Health.Damg = stf(pchar.chr_ai.hp_max)*10; 
					ChangeOfficersLoyality("bad_all", 1);
					AddQuestRecord("ShipEpidemy","3");
					AddQuestUserData("ShipEpidemy", "sShipName", pchar.GenQuest.ShipSituation.Epidemy.ShipName);	
					RemoveCrewEpidemy_GenQuest();
				}
				else
				{
					if(DayQty < 3) pchar.Health.Damg = stf(pchar.chr_ai.hp_max)*5; 
				}	
			break;
			case ShipSituation_3:
				if(DayQty == 0)
				{
					pchar.Health.Damg = stf(pchar.chr_ai.hp_max)*10; 
					ChangeOfficersLoyality("bad_all", 2);
					AddQuestRecord("ShipEpidemy","3");
					AddQuestUserData("ShipEpidemy", "sShipName", pchar.GenQuest.ShipSituation.Epidemy.ShipName);	
					RemoveCrewEpidemy_GenQuest();
				}
				else
				{
					if(DayQty < 3) pchar.Health.Damg = stf(pchar.chr_ai.hp_max)*5; 
				}		
			break;
			case ShipSituation_4:
				pchar.Health.Damg = stf(pchar.chr_ai.hp_max)*10;
				AddQuestRecord("ShipEpidemy","1");
				AddQuestUserData("ShipEpidemy", "sShipName", pchar.GenQuest.ShipSituation.Epidemy.ShipName);	
			break;
		}
		pchar.GenQuest.ShipSituation.Epidemy.Days = sti(pchar.GenQuest.ShipSituation.Epidemy.Days) - 1;	
	}
	else
	{
		if(iSituation < 4)
		{
			switch(iSituation)
			{
				case ShipSituation_0:
					AddQuestRecord("ShipEpidemy","2");
				break;
				case ShipSituation_1:
					AddQuestRecord("ShipEpidemy","4");
				break;
				case ShipSituation_2:
					AddQuestRecord("ShipEpidemy","4");
				break;
				case ShipSituation_3:
					AddQuestRecord("ShipEpidemy","4");
				break;
			}
		}	
		CloseQuestHeader("ShipEpidemy");
		DoQuestFunctionDelay("SetFreeQuestAboardShipSituation", 5.0);
	}
}

// вражеский кэп помер от стали и свинца - выходим сразу в режим "море"
void SetCaptainDiedQuestAboardSituation(ref chr)
{
	ShipDead(sti(chr.index), KILL_BY_ABORDAGE, sti(pchar.index));
}

// отпустили кэпа при переходе из вражеской каюты в режим "море" 
void SetCaptainFreeQuestAboardSituation(ref chr)
{
	aref    arTo, arFrom;	
	ref sld = GetCharacter(NPC_GenerateCharacter(chr.id + "_free", "off_hol_2", "man", "man", 60, sti(chr.nation), 0, true, "citizen")); // фантом, на время 
	ChangeAttributesFromCharacter(sld, chr, false);
	DeleteAttribute(sld, "ship");
	sld.ship = "";
			 
	makearef(arTo, sld.ship);
	makearef(arFrom, chr.Ship);
	CopyAttributes(arTo, arFrom);
	sld.AlwaysFriend = true;
	sld.Abordage.Enable = false; // запрет абордажа
		    			
	SeaAI_SetCaptainFree(sld, chr);
	chr.location = "none"; 
		    
	if (bSeaActive)
	{			
		PostEvent("evntQuestsCheck", 400);
		ShipTakenFree(sti(chr.index), KILL_BY_ABORDAGE, sti(pchar.index)); // тут умер реальный кэп, апдайтим ещё
		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
		UpdateRelations();
		RefreshBattleInterface();
		CheckQuestAboardCabinSituation(sld);
		DoQuestCheckDelay("NationUpdate", 1.5);
	}
}

void ShipSituation_SetQuestSituation(int iSituation)
{
	if(CheckAttribute(pchar,"GenQuest.ShipSituation.Explosion")) 
	{
		pchar.GenQuest.ShipSituation.Explosion = iSituation;
	}
	if(CheckAttribute(pchar,"GenQuest.ShipSituation.Epidemy"))
	{
		pchar.GenQuest.ShipSituation.Epidemy = iSituation;
	}	
}

// делаем большой "бум" на вражеском корабле --> превращаем его в брандер
void ShipSituation_MakeDetonate(string qName)
{
	Log_TestInfo("Добро пожаловать в преисподнюю !!");
	ref sld = CharacterFromID(pchar.GenQuest.ShipSituation.Explosion.CapId + "_free");
	ref rBaseShip = GetRealShip(sti(sld.Ship.Type));
	Event(SHIP_BRANDER_DETONATE,"l", sti(sld.index));
    PlaySound("Sea Battles\Vzriv_fort_001.wav");
	Ship_SetTaskNone(SECONDARY_TASK, sti(sld.index));
	Log_Info("" + XI_ConvertString(rBaseShip.BaseName) + " '" + sld.Ship.Name + "' " + GetShipSexWord(rBaseShip.BaseName, StringFromKey("GenQuests_22"), StringFromKey("GenQuests_23")) + StringFromKey("GenQuests_24"));
	bQuestDisableMapEnter = false;
	RefreshBattleInterface();
	if (sld.id == "Fleetwood_free") DoQuestFunctionDelay("FleetwoodJournalFind", 0.1);
	DoQuestFunctionDelay("SetFreeQuestAboardShipSituation", 5.0);
}

void CheckQuestAboardCabinSituation(ref echar)
{
	if(CheckAttribute(pchar,"GenQuest.ShipSituation.Explosion")) 
	{	
		echar.FaceId = 333;
		echar.name = StringFromKey("GenQuests_25");
		echar.lastname = "";
		bQuestDisableMapEnter = true;

		if(sti(pchar.GenQuest.ShipSituation.Explosion) == ShipSituation_1)
		{
			DoQuestFunctionDelay("ShipSituation_MakeDetonate", 0.5);	
		}
		else
		{
			if(sti(pchar.GenQuest.ShipSituation.Explosion) == ShipSituation_0)
			{				
				if(iArcadeSails == 1)
				{
					DoQuestFunctionDelay("ShipSituation_MakeDetonate", 15.0);
				}
				else
				{
					DoQuestFunctionDelay("ShipSituation_MakeDetonate", 40.0);
				}	
			}
			else
			{
				if(iArcadeSails == 1)
				{
					DoQuestFunctionDelay("ShipSituation_MakeDetonate", 30.0);
				}	
				else
				{
					DoQuestFunctionDelay("ShipSituation_MakeDetonate", 75.0);
				}	
			}
		}
	}
	if(CheckAttribute(pchar,"GenQuest.ShipSituation.Epidemy"))
	{
		pchar.GenQuest.ShipSituation.Epidemy.ShipName = echar.Ship.Name;
		pchar.GenQuest.ShipSituation.Epidemy.ShipType = sti(echar.Ship.Type);
		ShipSituation_SetConsequence(sti(pchar.GenQuest.ShipSituation.Epidemy));
	}	
}
//=====================================================================================================================================
// <-- МИНИ-ГЕНЕРАТОРЫ "ВЗРЫВ ИЛИ ЭПИДЕМИЯ  НА ВРАЖЕСКОМ КОРАБЛЕ"
//=====================================================================================================================================

//=====================================================================================================================================
// Ugeen. ГЕНЕРАТОР  "ДЕВИЦА В ДЖУНГЛЯХ"
//=====================================================================================================================================
void EncGirl_Saved()
{
	ref sld = CharacterFromID("CangGirl");
	sld.greeting = "rapers_girl_2";
	sld.dialog.filename = "Enc_RapersGirl_dialog.c";
	if(pchar.GenQuest.EncGirl == "toParents")
	{
		sld.dialog.currentnode = "Node_250"; // ушли без боевки 
	}
	else
	{
		sld.dialog.currentnode = "ThanksForSave"; // грохнули бандюков
	}	
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void EncGirl_GirlGoAway()
{
	ChangeCharacterComplexReputation(pchar,"nobility", -5);
	ref sld = CharacterFromID("CangGirl");
	LAi_SetActorType(sld);
	string sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
	LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "","", -1.0);
	sld.lifeDay = 0; 
	DeleteAttribute(pchar, "GenQuest.EncGirl");
}

void EncGirl_toChurch(string qName)
{
	ref sld = CharacterFromID("CangGirl");
	ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirl.city + "_church", "goto", "goto1");
	LAi_SetStayType(sld);
}

void EncGirl_GenQuest_GetCoins(string qName)
{
	ref sld = CharacterFromID("CangGirl");
	ChangeCharacterAddress(sld, "None", ""); 
	sld.lifeDay = 0; 
	AddSimpleRumour(StringFromKey("GenQuests_26", pchar.GenQuest.EncGirl.name), sti(sld.nation), 5, 1); // belamour
	ChangeCharacterComplexReputation(pchar,"nobility", -10);
	AddQuestRecord("JungleGirl", "3");
	AddQuestUserData("JungleGirl", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
	AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
	CloseQuestHeader("JungleGirl");
	DeleteAttribute(pchar, "GenQuest.EncGirl");
}

void EncGirl_GenQuest_GetChestPlaceName()
{
	int iTemp = rand(3);
	switch (iTemp)
	{
		case 0: 
			pchar.GenQuest.EncGirl.islandId = "Bermudes"
			pchar.GenQuest.EncGirl.placeId = "Bermudes_Cavern";
			pchar.GenQuest.EncGirl.shoreId = "Shore_ship1";
		break;
		case 1: 
			pchar.GenQuest.EncGirl.islandId = "Caiman";
			pchar.GenQuest.EncGirl.placeId = "Caiman_Grot";
			pchar.GenQuest.EncGirl.shoreId = "Shore17";
		break;
		case 2: 
			pchar.GenQuest.EncGirl.islandId = "Dominica";
			pchar.GenQuest.EncGirl.placeId = "Dominica_Grot";
			pchar.GenQuest.EncGirl.shoreId = "Shore26";
		break;
		case 3: 
			pchar.GenQuest.EncGirl.islandId = "Terks";
			pchar.GenQuest.EncGirl.placeId = "Terks_Grot";
			pchar.GenQuest.EncGirl.shoreId = "Shore56";
		break;
	}
} 

void EncGirl_Death(string qName)
{
	AddQuestRecord("JungleGirl", "5");
    AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
	CloseQuestHeader("JungleGirl");
	pchar.quest.EncGirl_FindChest.over = "yes";
	DeleteAttribute(pchar, "pchar.GenQuest.EncGirl.islandId");	
	DeleteAttribute(pchar, "pchar.GenQuest.EncGirl.placeId");
	ChangeCharacterComplexReputation(pchar,"nobility", -30);
    pchar.quest.DeleteGirlGroup.win_condition.l1 = "ExitFromLocation";
    pchar.quest.DeleteGirlGroup.win_condition.l1.location = pchar.location;
    pchar.quest.DeleteGirlGroup.function = "EncGirl_DeleteGirlGroup";
}

void EncGirl_DeathAgain(string qName)
{
	AddQuestRecord("JungleGirl", "7");
	AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
	CloseQuestHeader("JungleGirl");
	ChangeCharacterComplexReputation(pchar,"nobility", -30);
	pchar.quest.EncGirl_DeliveBack.over = "yes";
	pchar.quest.DeleteGirlGroup.win_condition.l1 = "ExitFromLocation";
    pchar.quest.DeleteGirlGroup.win_condition.l1.location = pchar.location;
    pchar.quest.DeleteGirlGroup.function = "EncGirl_DeleteGirlGroup";
}

void EncGirl_DeathSimple(string qName)
{
	if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
	{
		AddQuestRecord("JungleGirl", "10");
		AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);	
		CloseQuestHeader("JungleGirl");
	}
	ChangeCharacterComplexReputation(pchar,"nobility", -30);
	pchar.quest.DeleteGirlGroup.win_condition.l1 = "ExitFromLocation";
    pchar.quest.DeleteGirlGroup.win_condition.l1.location = pchar.location;
    pchar.quest.DeleteGirlGroup.function = "EncGirl_DeleteGirlGroup";
}

void EncGirl_FindChest(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationDisableMonstersGen(pchar.location, true);
	pchar.quest.EncGirl_Death.over = "yes";
	ref sld = characterFromId("CangGirl");
	sld.dialog.filename = "Enc_RapersGirl_dialog.c";
	sld.dialog.currentnode = "Node_132_12";
	LAi_SetActorTypeNoGroup(sld);
	GetCharacterPos(sld, &locx, &locy, &locz);	
	ChangeCharacterAddressGroup(sld, pchar.location, "monsters", LAi_FindFarLocator("monsters", locx, locy, locz));
	LAi_ActorDialog(sld, pchar, "", -1, 0);	
}

void EncGirl_AddPassenger(string qName)
{
	ref sld = characterFromId("CangGirl");	
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, false);		
	LAi_type_actor_Reset(sld); 
	ChangeCharacterAddress(sld, "none", ""); 
}

void EncGirl_DialogAtShore(string qName)
{
	ref sld = characterFromId("CangGirl");
	sld.dialog.filename = "Enc_RapersGirl_dialog.c";
	sld.dialog.currentnode = "Node_132_11_1";	
	PlaceCharacter(sld, "goto", pchar.location);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);	
	pchar.quest.EncGirl_EnterToSea.win_condition.l1 = "EnterToSea";
	pchar.quest.EncGirl_EnterToSea.function = "EncGirl_EnterToSea";
	pchar.quest.EncGirl_Death.over = "yes";
}

void EncGirl_EnterToSea(string qName)
{
	ref sld = characterFromId("CangGirl");
	if(pchar.GenQuest.EncGirl == "ChestGetted") // забрали клад
	{
		LAi_type_actor_Reset(sld); 
	}
	else // кинули тетку на острове, клад не стали брать
	{
		pchar.quest.EncGirl_DeliveBack.over = "yes"; // снимаем ненужные прерывания
		pchar.quest.EncGirl_DeathAgain.over = "yes";
		pchar.quest.EncGirl_FindChest.over = "yes";
		ChangeCharacterComplexReputation(pchar,"nobility", -5);
		AddQuestRecord("JungleGirl", "5_1");
		AddQuestUserData("JungleGirl", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
		AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		CloseQuestHeader("JungleGirl");
		RemovePassenger(pchar, sld);
		ChangeCharacterAddress(sld, "none", "");
		sld.lifeDay = 0; 
		DeleteAttribute(pchar, "GenQuest.EncGirl");
	}
}

void EncGirl_DeleteGirlGroup(string qName)
{
	LAi_group_Delete("DeliveQuest_Girl");
	DeleteAttribute(pchar, "GenQuest.EncGirl");
}

void EncGirl_DeliveBack(string qName)
{
	if (GetCharacterIndex("CangGirl") < 0) return;
	ref sld = characterFromId("CangGirl");	
	sld.dialog.filename = "Enc_RapersGirl_dialog.c";
	if(pchar.GenQuest.EncGirl == "ChestGetted")
	{
		chrDisableReloadToLocation = true;
		LAi_type_actor_Reset(sld); 
		sld.dialog.currentnode = "Node_132_18";
		pchar.quest.EncGirl_DeathAgain.over = "yes";
	}
	if(pchar.GenQuest.EncGirl == "FindCoins")
	{
		LAi_type_actor_Reset(sld); 
		sld.dialog.currentnode = "Node_260";
		pchar.quest.EncGirl_DeathSimple.over = "yes";
	}
	if(pchar.GenQuest.EncGirl == "HorseToTavern")
	{
		sld.dialog.currentnode = "Node_225";
		pchar.quest.EncGirl_DeathSimple.over = "yes";
	}
	PlaceCharacter(sld, "goto", "random_must_be_near");
	if(pchar.GenQuest.EncGirl != "FindCoins")
	{
		LAi_SetActorType(pchar); 
		LAi_ActorTurnToCharacter(pchar, sld);
		LAi_SetActorTypeNoGroup(sld);
		SetActorDialogAny2Pchar(sld.id, "", -1, 1.0);
		LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);	
	}	
	else
	{
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);		
	}
}

void EncGirl_GenerateChest(ref chref)
{
	pchar.GenQuest.EncGirl.Treasure.Island = GetArealByCityName(chref.city);
	pchar.GenQuest.EncGirl.Treasure.Location = GetLocationForTreasure(pchar.GenQuest.EncGirl.Treasure.Island);
	pchar.GenQuest.EncGirl.Treasure.Locator = GetBoxForTreasure(pchar.GenQuest.EncGirl.Treasure.Island, pchar.GenQuest.EncGirl.Treasure.Location);

	pchar.quest.EncGirl_FindTreasure.win_condition.l1 = "location";
	pchar.quest.EncGirl_FindTreasure.win_condition.l1.location = pchar.GenQuest.EncGirl.Treasure.Location;
	pchar.quest.EncGirl_FindTreasure.function = "EncGirl_FindTreasure";
}

void EncGirl_FindTreasure(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationDisableMonstersGen(pchar.location, true);
	pchar.quest.EncGirl_DeathSimple.over = "yes";
	ref sld = characterFromId("CangGirl");
	sld.dialog.filename = "Enc_RapersGirl_dialog.c";
	sld.dialog.currentnode = "Node_207";
	LAi_SetActorTypeNoGroup(sld);
	GetCharacterPos(sld, &locx, &locy, &locz);	
	ChangeCharacterAddressGroup(sld, pchar.location, "monsters", LAi_FindFarLocator("monsters", locx, locy, locz));
	LAi_ActorDialog(sld, pchar, "", -1, 0);	
}

void EncGirl_GirlFollow()
{
	sGlobalTemp = "Saved_CangGirl";
	ref sld = characterFromId("CangGirl");
	DeleteAttribute(sld, "LifeDay"); 
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed"); 
	LAi_SetActorType(sld);
	LAi_group_Register("DeliveQuest_Girl"); 
	LAi_group_SetRelation("DeliveQuest_Girl", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
//	LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Girl", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
	LAi_group_MoveCharacter(sld, "DeliveQuest_Girl"); 
	LAi_ActorFollowEverywhere(sld, "", -1); 
	
	if(pchar.GenQuest.EncGirl != "GetChest")
	{
		pchar.quest.EncGirl_DeathSimple.win_condition.l1 = "NPC_Death";
		pchar.quest.EncGirl_DeathSimple.win_condition.l1.character = "CangGirl";
		pchar.quest.EncGirl_DeathSimple.function = "EncGirl_DeathSimple";
	}	
}

void EncGirl_MeetRapers(string qName)
{
	ref sld;
	for(i = 1; i <= 3; i++)
	{
		if (GetCharacterIndex("GangMan_" + i) == -1) continue;
		sld = CharacterFromID("GangMan_" + i);
		LAi_SetImmortal(sld, false);
		LAi_type_actor_Reset(sld);
		sld.dialog.filename = "Enc_Rapers_dialog.c";
		sld.dialog.currentnode = "Node_8";
		sld.greeting = "Enc_Raiders";
		sld.location = "none";
		PlaceCharacter(sld, "goto", "random_must_be_near");
		LAi_ActorFollow(sld, pchar, "", -1);
        LAi_group_MoveCharacter(sld, "EnemyFight");	
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER_OWN, LAI_GROUP_NEITRAL);

	LAi_group_ClearAllTargets();
	LAi_SetFightModeForOfficers(false);
	
    sld = characterFromID("GangMan_1");
    LAi_type_actor_Reset(sld);
    LAi_ActorDialog(sld, pchar, "", 4.0, 0);
	chrDisableReloadToLocation = true;
	DoQuestCheckDelay("OpenTheDoors", 5.0);							
}

void EncGirl_GenerateLeatherBag(string qName)
{
	ref location;
	string boxId = "box1";
	aref boxItems;
	
	if(pchar.GenQuest.EncGirl == "Bag_BrothelRoomUp") // верхняя комната
	{
		location = &Locations[FindLocation(pchar.GenQuest.EncGirl.city + "_Brothel_room")];
	}
	if(pchar.GenQuest.EncGirl == "Bag_BrothelRoom")
	{
		location = &Locations[FindLocation(pchar.GenQuest.EncGirl.city + "_SecBrRoom")];
	}
	
	makearef(boxItems, location.(boxId).items);
		
	boxItems.leather_bag = 1;
	location.(boxId) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
	Log_TestInfo("Генерируем саквояж");
}

void EncGirl_RapersChest(string qName)
{
	ref location = &Locations[FindLocation(pchar.GenQuest.EncGirl.Treasure.Location)];
	string boxId = pchar.GenQuest.EncGirl.Treasure.Locator;
	aref boxItems;
	
	makearef(boxItems, location.(boxId).items);
			
	boxItems.gold = GetSummonSkillFromName(pchar, SKILL_FORTUNE) * 100 + rand(3000);
	
	if(rand(3) == 1) 
	{ 
		boxItems.jewelry2 = 10 + rand(3); 	
	}				
	if(rand(1) == 1) 
	{ 
		boxItems.jewelry1 = 15 + rand(10); 	
	}		
	if(rand(1) == 1) 
	{ 
		boxItems.jewelry52 = 25 + rand(15);	
	}
	if(rand(1) == 1) 
	{ 
		boxItems.jewelry53 = 18 + rand(20); 
	}
	if(rand(1) == 1) 
	{ 
		boxItems.jewelry47 = 22 + rand(12);	
	}
	if (hrand(6, location.id) == 1 && CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты
	{
		string amap = SelectAdmiralMaps();
		if (amap != "") boxItems.(amap)	= 1;
	}
		
	location.(boxId) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
	location.(boxId).Treasure = true; // Признак сокровища в сундуке
}

void EncGirl_TreasureLose(string qName)
{
	ref location = &Locations[FindLocation(pchar.GenQuest.EncGirl.Treasure.Location)];
	string boxId = pchar.GenQuest.EncGirl.Treasure.Locator;
	
	pchar.quest.EncGirl_RapersTreasure.over = "yes";
	
	DeleteAttribute(location, boxId + ".items");
	DeleteAttribute(location, boxId + ".Treasure");
	
	DeleteAttribute(pchar, "GenQuest.EncGirl");	
}

void EncGirl_RapersAfter(string qName)
{
	pchar.quest.EncGirl_TreasureLose.win_condition.l1 = "Timer";
	pchar.quest.EncGirl_TreasureLose.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
	pchar.quest.EncGirl_TreasureLose.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
	pchar.quest.EncGirl_TreasureLose.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
	pchar.quest.EncGirl_TreasureLose.function = "EncGirl_TreasureLose";

	pchar.quest.EncGirl_RapersTreasure.win_condition.l1 = "location";
	pchar.quest.EncGirl_RapersTreasure.win_condition.l1.location = pchar.GenQuest.EncGirl.Treasure.Location;
	pchar.quest.EncGirl_RapersTreasure.function = "EncGirl_RapersChest";
}

void EncGirl_SpeakInRoom(string qName)
{
	chrDisableReloadToLocation = true;
	LocatorReloadEnterDisable(locations[reload_location_index].fastreload + "_tavern", "reload2_back", true);
	DoQuestFunctionDelay("EncGirl_SpeakInRoomEnter", 2);
}

void EncGirl_SpeakInRoomEnter(string qName)
{
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, true);
	ref sld = characterFromId("CangGirl");	
	sld.dialog.filename = "Enc_RapersGirl_dialog.c";
	sld.dialog.currentnode = "Node_228";
	PlaceCharacter(sld, "goto", "random_must_be_near"));
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", 5.0, 0);
}	

void EncGirl_SetBerglar(string qName)
{
	int iTemp = sti(pchar.rank) + rand(5);
	ref sld = GetCharacter(NPC_GenerateCharacter("Berglar_EncGirl", "mercen_"+(rand(14)+14), "man", "man", iTemp, PIRATE, -1, true, "quest"));
	FantomMakeCoolFighter(sld, iTemp, 50 + rand(30), 50 + rand(30), "topor_04", "pistol6", "bullet", 50);
	sld.dialog.filename = "Enc_Rapers_dialog.c";
	sld.dialog.currentnode = "EncGirl_Berglar";	
	sld.greeting = "Enc_Raiders"; 
	PlaceCharacter(sld, "goto", "random_must_be_near"));
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_ActorDialog(sld, pchar, "", 4.0, 0);
}

void EncGirlFack_outRoom()
{
	pchar.GenQuest.EncGirl = "EncGirlFack_fighted";
	AddCharacterExpToSkill(pchar, "Pistol", 100); 
	sld = characterFromId("Berglar_EncGirl");
	sld.LifeDay = 0;
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
	SetFunctionTimerCondition("EncGirl_SpeakTavernKeeper", 0, 0, 1, false);
}

void EncGirlFack_outRoomRaped()
{
	// ==> Забираем клинки, пистоли и деньги.
	RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
	RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
    while (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) != "")
    {
        TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE));
    }
    while (FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE) != "")
    {             
        TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE));
    }
	while (FindCharacterItemByGroup(pchar, MUSKET_ITEM_TYPE) != "")
    {             
        TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, MUSKET_ITEM_TYPE));
    }
    pchar.money = 0;
    // <== Забираем клинки, пистоли и деньги.
	pchar.GenQuest.EncGirl = "EncGirlFack_fighted";
	AddCharacterExpToSkill(pchar, "Pistol", 100); 
	sld = characterFromId("Berglar_EncGirl");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
	SetFunctionTimerCondition("EncGirl_SpeakTavernKeeper", 0, 0, 1, false);
}

void EncGirlFack_fight()
{
	AddCharacterExpToSkill(pchar, "FencingL", 30);
	AddCharacterExpToSkill(pchar, "FencingS", 30);
	AddCharacterExpToSkill(pchar, "FencingH", 30);
	LAi_SetFightMode(pchar, true);
	pchar.GenQuest.EncGirl = "EncGirlFack_fighted";
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	pchar.quest.EncGirl_afterFight.win_condition.l1 = "NPC_Death";
	pchar.quest.EncGirl_afterFight.win_condition.l1.character = "Berglar_EncGirl";
	pchar.quest.EncGirl_afterFight.win_condition = "OpenTheDoors";
	SetFunctionTimerCondition("EncGirl_SpeakTavernKeeper", 0, 0, 1, false);
}

void EncGirl_SpeakTavernKeeper(string qName)
{
	DeleteAttribute(pchar, "GenQuest.EncGirl");
}

void EncGerl_deleteisjangly(string qName) // лесник квест снова доступен
{
	DeleteAttribute(pchar, "GenQuest.EncGirl");
}
void EncGirl_GenQuest_GetBag(string qName)
{
	ref sld = CharacterFromID("CangGirl");
	sld.lifeDay = 0; 
	AddSimpleRumour(RandPhraseSimple(StringFromKey("GenQuests_27"),  
				StringFromKey("GenQuests_28")), 
				sti(pchar.GenQuest.EncGirl.nation), 3, 1);
	ChangeCharacterComplexReputation(pchar,"nobility", -8);
	pchar.quest.EncGirl_GenerateBag.over = "yes";
	pchar.quest.EncGirl_SpeakHorse.over = "yes";	
	AddQuestRecord("JungleGirl", "22");
	CloseQuestHeader("JungleGirl");
	DeleteAttribute(pchar, "GenQuest.EncGirl");
}

void EncGirl_ExitTavernRoom(string qName)
{
	LocatorReloadEnterDisable(pchar.GenQuest.EncGirl.city + "_tavern", "reload2_back", false);
	
	pchar.quest.EncGirl_SpeakHorse.win_condition.l1 = "location";
	pchar.quest.EncGirl_SpeakHorse.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern_upstairs";
	pchar.quest.EncGirl_SpeakHorse.function = "EncGirl_SpeakHorse";
	ref sld = characterFromId("CangGirl");	
	ChangeCharacterAddress(sld, "none", ""); 
}

void EncGirl_SpeakHorse(string qName)
{
	ref sld = characterFromId("CangGirl");	
	sld.dialog.filename = "Enc_RapersGirl_dialog.c";
	sld.dialog.currentnode = "Node_240_1";
	ChangeCharacterAddress(sld, pchar.location, "goto1");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", 2.0, 0);		
}

void EncGirl_DeliveToParents(string qName)
{
	ref sld;
	sld = characterFromId("CangGirl");	
	RemovePassenger(pchar, sld);
	sld.dialog.filename = "Enc_RapersGirl_dialog.c";
	sld.dialog.currentnode = "Node_245";		
	PlaceCharacter(sld, "goto", pchar.location);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);	
}

void EncGirl_GenerateLover(string qName)
{
	int iTemp = sti(pchar.rank) + rand(5);
	ref sld = GetCharacter(NPC_GenerateCharacter("Lover_EncGirl", "mercen_"+(rand(14)+1), "man", "man", iTemp, sti(pchar.GenQuest.EncGirl.nation), -1, true, "citizen"));
	sld.name = pchar.GenQuest.EncGirl.sLoverId;
	sld.lastname = "";
	FantomMakeCoolFighter(sld, iTemp, 80, 80, "topor_04", "pistol6", "bullet", 50);
	pchar.quest.EncGirl_SpeakLoverTavern.win_condition.l1 = "location";
	pchar.quest.EncGirl_SpeakLoverTavern.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
	pchar.quest.EncGirl_SpeakLoverTavern.function = "EncGirl_SpeakLover";
}

void EncGirl_SpeakLover(string qName)
{
	chrDisableReloadToLocation = true;
	ref sld = characterFromId("Lover_EncGirl");	
	sld.dialog.filename = "GenQuests_Dialog.c";
	sld.dialog.currentnode = "EncGirl_Lover";	
	sld.greeting = "Gr_Officer"; 
	PlaceCharacter(sld, "goto", pchar.GenQuest.EncGirl.city + "_tavern");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
}

void EncGirl_LoverExit()
{
	string sTemp;
	pchar.quest.EncGirl_DeathSimple.over = "yes";
	AddQuestRecord("JungleGirl", "14");
	AddQuestUserData("JungleGirl", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
	CloseQuestHeader("JungleGirl");		
	ChangeCharacterComplexReputation(pchar,"nobility", -3);	
	sTemp = LAi_FindNearestFreeLocator2Pchar("reload");

	for (i = 1; i <= 2; i++)
	{
		if (i == 1) sld = characterFromId("Lover_EncGirl");
		else sld = characterFromId("CangGirl");
		sld.lifeDay = 0;
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", 5.0);
	}

	DeleteAttribute(pchar, "GenQuest.EncGirl");
}

void EncGirl_ToLoverParents()
{
	ref sld;
	string sTemp;
	pchar.quest.EncGirl_DeathSimple.over = "yes";
	AddQuestRecord("JungleGirl", "15");
	AddQuestUserData("JungleGirl", "sSex", GetSexPhrase(StringFromKey("GenQuests_64"),StringFromKey("GenQuests_65")));
	AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.LoverCity));
	ChangeCharacterComplexReputation(pchar,"nobility", 1);
	sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
	
	for (i = 1; i <= 2; i++)
	{
		if (i == 1) sld = characterFromId("Lover_EncGirl");
		else sld = characterFromId("CangGirl");
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, false);
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", 5.0);
	}			
	
	pchar.quest.EncGirl_DeliveToLoverParents.win_condition.l1 = "location";
	pchar.quest.EncGirl_DeliveToLoverParents.win_condition.l1.location = pchar.GenQuest.EncGirl.LoverCity + "_town";
	pchar.quest.EncGirl_DeliveToLoverParents.function = "EncGirl_DeliveToLoverParents";
}

void EncGirl_ToLoverParentsExit()
{
    ref sld = CharacterFromID("CangGirl");
	pchar.quest.EncGirl_DeathSimple.over = "yes";
	ChangeCharacterComplexReputation(pchar,"nobility", -3);
	AddMoneyToCharacter(pchar, 500 * (sti(pchar.rank) + 10) + hrand(5000, sld.name));
	AddQuestRecord("JungleGirl", "13");
	AddQuestUserData("JungleGirl", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"), StringFromKey("GenQuests_67")));
	CloseQuestHeader("JungleGirl");
	string sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "","", -1.0);
	sld.lifeDay = 0; 
	DeleteAttribute(pchar, "GenQuest.EncGirl");
}

void EncGirl_DeliveToLoverParents(string qName)
{
	pchar.GenQuest.Hunter2Pause = true;
	ref sld;	
	sld = characterFromId("CangGirl");
	RemovePassenger(pchar, sld);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
	sld.lifeday = 0;		
	sld = characterFromId("Lover_EncGirl");
	RemovePassenger(pchar, sld);
	chrDisableReloadToLocation = true;
	sld.dialog.filename = "GenQuests_Dialog.c";
	sld.dialog.currentnode = "EncGirl_Lover6";	
	PlaceCharacter(sld, "goto", pchar.location);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void EncGirl_GenQuest_GetLoverFather(string qName)
{
	AddQuestRecord("JungleGirl", "17");
	AddQuestUserData("JungleGirl", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
	CloseQuestHeader("JungleGirl");
	DeleteAttribute(pchar, "GenQuest.EncGirl");
}
//=====================================================================================================================================
// <-- ГЕНЕРАТОР  "ДЕВИЦА В ДЖУНГЛЯХ"
//=====================================================================================================================================

//=====================================================================================================================================
// Ugeen. ГЕНЕРАТОР  "Специальный энкаунтер - бочка"
//=====================================================================================================================================
void Set_TreasureBarrel()
{
	ref			nulChr;
	aref     	trBarrel;

	nulChr = &NullCharacter;
	if(CheckAttribute(nulChr,"GenQuest.Barrel")) DeleteAttribute(nulChr,"GenQuest.Barrel");

	makearef(trBarrel, nulChr.GenQuest.Barrel);
	int irand;

    // На if'ах оставил старую логику. TO_DO: Переверить, не руша баланс, так как предполагалось рандомить везде.
    // За счёт "&" для каждой конкретной бочки в конкретный день используется одна и та же дробь
    string tag2 = TEV.Last_Treasure_Barrel_ID;
    string tag  = "&" + tag2;

	if(GetSummonSkillFromName(pchar, "Fortune") > hrand(200, tag2))
	{
        switch(hrand(20, tag))
        {
            case 1:  trBarrel.items.jewelry1  = rand(18) + 27; break;
            case 2:  trBarrel.items.jewelry2  = rand(22) + 22; break;
            case 3:  trBarrel.items.jewelry3  = rand(15) + 32; break;
            case 4:  trBarrel.items.jewelry4  = rand(22) + 15; break;
            case 5:  trBarrel.items.jewelry5  = rand(19) + 22; break;
            case 6:  trBarrel.items.jewelry6  = rand(22) + 16; break;
            case 7:  trBarrel.items.jewelry7  = rand(17) + 32; break;
            case 8:  trBarrel.items.jewelry40 = rand(5)  + 18; break;
            case 9:  trBarrel.items.jewelry41 = rand(8)  + 12; break;
            case 10: trBarrel.items.jewelry42 = rand(35) + 12; break;
            case 11: trBarrel.items.jewelry43 = rand(13) + 27; break;
            case 12: trBarrel.items.jewelry44 = rand(16) + 18; break;
            case 13: trBarrel.items.jewelry45 = rand(30) + 15; break;
            case 14: trBarrel.items.jewelry46 = rand(30) + 15; break;
            case 15: trBarrel.items.jewelry47 = rand(35) + 14; break;
            case 16: trBarrel.items.jewelry48 = rand(24) + 18; break;
            case 17: trBarrel.items.jewelry49 = rand(17) + 13; break;
            case 18: trBarrel.items.chest     = rand(2)  + 1;  break;
        }

        switch(hrand(24, tag))
        {
            case 18: trBarrel.items.jewelry50 = rand(15) + 22; break;
            case 19: trBarrel.items.jewelry51 = rand(35) + 42; break;
            case 22: trBarrel.items.jewelry52 = rand(41) + 12; break;
            case 23: trBarrel.items.jewelry53 = rand(66) + 70; break;
        }

        switch(hrand(25, tag))
        {
            case 2:  trBarrel.items.hat3      = 1; break;
            case 3:  trBarrel.items.amulet_5  = 1; break;
            case 6:  trBarrel.items.amulet_10 = 1; break;
            case 9:  trBarrel.items.amulet_11 = 1; break;
            case 15: trBarrel.items.indian_8  = 1; break;
            case 18: trBarrel.items.indian_5  = 1; break;
            case 21: trBarrel.items.icollection = 1; break;
        }

		if(hrand(25, tag) == 24)
		{
			if (GetCharacterItem(pchar, "map_part1") == 0)
                trBarrel.items.map_part1 = 1;
			else if (GetCharacterItem(pchar, "map_full") == 0 && GetCharacterItem(pchar, "map_part2") == 0)
                trBarrel.items.map_part2 = 1;		
		}

		if (hrand(30, tag) == 1 && CheckAttribute(pchar, "questTemp.AdmiralMap")) // адм.карты
		{
			string amap = SelectAdmiralMaps();
			if (amap != "") trBarrel.items.(amap) = 1;
		}
	}
	else
	{
		if(rand(1) == 0) trBarrel.items.mineral2 = rand(7)  + 7;
		if(rand(1) == 0) trBarrel.items.mineral3 = rand(15) + 5;
		if(rand(1) == 0) trBarrel.items.mineral4 = rand(10) + 2;
		if(rand(1) == 0) trBarrel.items.mineral5 = rand(8)  + 4;
		if(rand(1) == 0) trBarrel.items.mineral6 = rand(14) + 7;
		if(rand(1) == 0) trBarrel.items.mineral7 = rand(12) + 8;
		if(rand(1) == 0) trBarrel.items.mineral8 = rand(12) + 6;
		if(rand(1) == 0) trBarrel.items.mineral9 = rand(8)  + 2;
		if(rand(1) == 0) trBarrel.items.mineral10 = rand(16)+ 6;
	}	
	trBarrel.items.gold = hrand(5000, tag2) + 5000;
    DeleteAttribute(&TEV, "Last_Treasure_Barrel_ID");
	LaunchItemsBarrel(&trBarrel);
}
//=====================================================================================================================================
// Ugeen. ГЕНЕРАТОР  "Специальный энкаунтер - бочка"
//=====================================================================================================================================

//=====================================================================================================================================
// Ugeen. ГЕНЕРАТОР  "ПОРУЧЕНИЕ КАПИТАНА - ВЫКУП"
//=====================================================================================================================================
void CaptainComission_GenerateSituation(ref chref)
{
	if (CheckAttribute(chref, "RealEncounterType") && sti(chref.RealEncounterType) != ENCOUNTER_TYPE_ALONE && !CheckAttribute(pchar,"GenQuest.CaptainComission"))
	{
		aref chrShip;
		makearef(chrShip, chref.Back.Ship);
    ref origCap = CharacterFromID(chref.CaptanId); // mitrokosta фикс пасхалки с сундуками
		if (CheckAttribute(chrShip, "Mode") && chrShip.Mode == "trade")
		{
			if(rand(4) == 1 || bBettaTestMode) // временно, для бетатеста 
			{
				pchar.GenQuest.CaptainComission = "Begin";
				pchar.GenQuest.CaptainComission.CapId = chref.CaptanId;
				pchar.GenQuest.CaptainComission.CapName = chref.Name;
				pchar.GenQuest.CaptainComission.ShipType = GetCharacterShipType(origCap); // mitrokosta фикс пасхалки с сундуками
			}	
		}	
	}
}

void CaptainComission_Init(ref chref)
{
	pchar.GenQuest.CaptainComission.Nation = chref.nation;
	pchar.GenQuest.CaptainComission.City = GetQuestNationsCity(sti(chref.nation));
	pchar.GenQuest.CaptainComission.Name = GenerateRandomName_Generator(sti(chref.nation), "man");
	pchar.GenQuest.CaptainComission.SlaveName = GenerateRandomName_Generator(sti(chref.nation), "man");
	pchar.GenQuest.CaptainComission.ShipName = chref.Back.Ship.Name;
	pchar.GenQuest.CaptainComission.Speak_Tavern = false;
	pchar.GenQuest.CaptainComission.variant = "A0";
	pchar.GenQuest.CaptainComission.Item = GenQuest_GeneratePrize();
}

void CaptainComission_Speak(string qName)
{
	if(pchar.GenQuest.CaptainComission == "Begin_1" || pchar.GenQuest.CaptainComission == "Begin_2")
	{
		AddQuestRecord("CaptainComission1", "2");
		AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
		CloseQuestHeader("CaptainComission1");
		DeleteAttribute(pchar,"GenQuest.CaptainComission");
	}
}

void CaptainComission_SellSlave(string qName)
{
	pchar.GenQuest.CaptainComission.DaysLeft = true;
}

void CaptainComission_EndTavern()
{
	ref sld;
	sld = characterFromId("CapComission_1");
	sld.lifeDay = 0; 
	LAi_CharacterDisableDialog(sld);
	
	sld = characterFromId("CapComission_Slave");
	RemovePassenger(pchar, sld);
	sld.lifeDay = 0; 
	
	DeleteAttribute(pchar,"GenQuest.CaptainComission");
}

void CaptainComission_GenerateChar(string qName)
{
	ref sld = GetCharacter(NPC_GenerateCharacter("CapComission_1" , "officer_12", "man", "man", 10, sti(pchar.GenQuest.CaptainComission.Nation), -1, true, "quest"));
	FantomMakeCoolFighter(sld, 10, 30, 35, LinkRandPhrase("blade_05","blade_04","blade_07"), "pistol1", "bullet", 10);	
	sld.name = pchar.GenQuest.CaptainComission.Name;
	sld.lastname = "";
	sld.SaveItemsForDead = true; // сохранять на трупе вещи
	sld.DontClearDead = true; // не убирать труп через 200с
	sld.dialog.FileName = "GenQuests_Dialog.c";
	sld.dialog.currentnode = "CaptainComission_3";
	sld.greeting = "cit_quest";
	LAi_SetSitType(sld);
	LAi_SetImmortal(sld, true);	// До поры нельзя убить
	string sLoc = pchar.GenQuest.CaptainComission.City + "_tavern"; 
	FreeSitLocator(sLoc, "sit2");
	ChangeCharacterAddressGroup(sld, sLoc, "sit", "sit2");
}

void CaptainComission_GetPirateIsland()
{
	ref sld;
	string CityId, PirateId;	
	switch (rand(1))
	{
		case 0:
			CityId = "PuertoPrincipe"; // Пуэрто-Принсипе, Куба 250912
			PirateId = "Marlow";
			sld = CharacterFromID("Marlow");
		break;
		case 1:
		if (!CheckAttribute(pchar, "questTemp.LongHappy"))  // лесник - если ДИС взято то уже марлоу.
		{
			
			CityId = "LeFransua"; // Ле-Франсуа на Мартинике
			PirateId = "Barbazon";
			sld = CharacterFromID("Barbazon");
		}
        else
		{
           CityId = "PuertoPrincipe"; // Пуэрто-Принсипе, Куба 250912
		   PirateId = "Marlow";
		   sld = CharacterFromID("Marlow");
		} 		
		break;
	}
	pchar.GenQuest.CaptainComission.PiratesCity = CityId;
	pchar.GenQuest.CaptainComission.PirateId = PirateId;
	pchar.GenQuest.CaptainComission.PirateName = ChangeNameCase(NAMETYPE_MAIN, sld.name, NAME_NOM);
}

void CaptainComission_GetFamilyType()
{
	pchar.GenQuest.CaptainComission.FamilyType = hrand(4) + 1; // hrand auto tagged
}

void CaptainComission_30DaysIsLeft(string qName) // прошло 30 дней после разговора в таверне
{
	ref sld;
	if(pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")
	{
		sld = characterFromId("CapComission_1");
		ChangeCharacterAddress(sld, "none", ""); 
		sld.lifeDay = 0; 
		int idx = GetCharacterIndex("Bishop_manager");
		if(idx != -1) 
		{
			sld = &characters[idx];
			sld.lifeDay = 0; 
		}	
		if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
		{
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddQuestRecord("CaptainComission1", "6");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase(StringFromKey("GenQuests_68"),StringFromKey("GenQuests_69")));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
			AddQuestUserData("CaptainComission1", "sSex2", GetSexPhrase(StringFromKey("GenQuests_62"),StringFromKey("GenQuests_63")));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.GenQuest.CaptainComission.Nation)) + "hunter", 50); // лесник - выдал охотников ибо 150к - это вам не копейки :D
		}
		if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
		{
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			AddQuestRecord("CaptainComission1", "7");
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.GenQuest.CaptainComission.Nation)) + "hunter", 50);
		}
		CloseQuestHeader("CaptainComission1");
		DeleteAttribute(pchar,"GenQuest.CaptainComission");
	}
}

void CaptainComission_PirateShipsOver(string qName)
{
	pchar.quest.CapComission_PirateAttack.over = "yes";
	AddQuestRecord("CaptainComission1", "26");
	AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
	AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
	AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
	pchar.GenQuest.CaptainComission.PirateShips = "goaway";
	ChangeOfficersLoyality("bad_all", 1);
}

void CaptainComission_GetRandomShore()
{
	pchar.GenQuest.CaptainComission.Island = GetRandIslandId();
	while(pchar.GenQuest.CaptainComission.Island == Islands[GetCharacterCurrentIsland(pchar)].id)
	{
		pchar.GenQuest.CaptainComission.Island = GetRandIslandId();
	}
	pchar.GenQuest.CaptainComission.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.CaptainComission.Island);
	while(pchar.GenQuest.CaptainComission.Island.Shore == "")
	{
		pchar.GenQuest.CaptainComission.Island = GetRandIslandId();
		pchar.GenQuest.CaptainComission.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.CaptainComission.Island);
		if (!isLocationFreeForQuests(pchar.GenQuest.CaptainComission.Island)) pchar.GenQuest.CaptainComission.Island.Shore = "";
	} 
}

void CaptainComission_GenerateManager()
{
    ref sld;
	string sModel, sName, sLastName;
	int idx;
	switch(rand(2))
	{
		case 0:
			sModel = "trader_2";
			sName = StringFromKey("GenQuests_29");
			sLastName = StringFromKey("GenQuests_30");		
		break;
		case 1:
			sModel = "citiz_41";
			sName = StringFromKey("GenQuests_31");
			sLastName = StringFromKey("GenQuests_32");				
		break;
		case 2:
			sModel = "trader_3";
			sName = StringFromKey("GenQuests_33");
			sLastName = StringFromKey("GenQuests_34");				
		break;
	}
	
	Log_TestInfo("Генерим управляющего");	
   	sld = GetCharacter(NPC_GenerateCharacter("Bishop_manager", sModel, "man", "man", 1, GetCityNation("Bridgetown"), -1, false, "citizen"));
    sld.name = sName;
    sld.lastname = sLastName;
	sld.dialog.filename = "GenQuests_Dialog.c";
    sld.Dialog.CurrentNode = "CaptainComission_10";
    sld.greeting = "Gr_Bishop";

	string sTemp = GetNationNameByType(GetCityNation("Bridgetown")) + "_citizens";
    LAi_group_MoveCharacter(sld, sTemp);
    LAi_SetCitizenType(sld);
	LAi_SetImmortal(sld, true);

	ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation_Sp1", "goto", "goto1");
	
	LAi_LocationDisableOfficersGen("BridgeTown_Plantation", true);
	
	idx = GetCharacterIndex("Bishop");
	if(idx != -1) // убираем полковника с плантации
	{
		sld = &characters[idx];
		ChangeCharacterAddress(sld, "None", ""); 
	}		
}

void CaptainComission_GenerateSlave(string qName)
{
	string model[10];
	string sTemp = "SlaveGuards";
	int iNation = GetCityNation("Bridgetown");
	string slai_group = GetNationNameByType(iNation)  + "_citizens";
		
	model[0] = "citiz_26";
	model[1] = "citiz_27";
	model[2] = "citiz_28";
	model[3] = "citiz_29";
	model[4] = "citiz_30";
	model[5] = "citiz_31";
	model[6] = "citiz_32";
	
	int iMassive = rand(6);
	
	ref sld = GetCharacter(NPC_GenerateCharacter("CapComission_Slave", model[iMassive], "man", "man", rand(5) + 5, sti(pchar.GenQuest.CaptainComission.Nation), -1, true, "slave"));	
	sld.city = pchar.GenQuest.CaptainComission.City;
	sld.name = pchar.GenQuest.CaptainComission.SlaveName;
	sld.lastname = "";	
	sld.greeting = "Gr_slave";
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed"); 
	sld.dialog.filename = "GenQuests_Dialog.c";
	LAi_SetHP(sld, 50.0, 60.0); // делаем раба задохликом

	if(pchar.GenQuest.CaptainComission.GetSlave == "GetSlave")	
	{
		Log_QuestInfo("Выкупили раба");
		sld.dialog.currentnode = "CaptainComission_20";	
		PlaceCharacter(sld, "goto", "random_must_be_near");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);		
	}	
	if(pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")	
	{
		Log_QuestInfo("Идём освобождать раба");
		LAi_LocationFightDisable(&Locations[FindLocation("BridgeTown_Plantation")], true);
		LAi_SetFightMode(pchar, false);
		LAi_LockFightMode(pchar, true);
		sld.dialog.currentnode = "CaptainComission_70";
		ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "quest", "sit2");
		LAi_SetActorType(sld);
		LAi_ActorSetLayMode(sld);
		LAi_SetGroundSitTypeNoGroup(sld); 
		
		// генерим стражу
		for (int i = 0; i < 3; i++)
		{		
			sld = GetCharacter(NPC_GenerateCharacter("SlaveGuard_"+i, "sold_eng_"+(rand(7)+1), "man", "man", 10, ENGLAND, 1, true,"soldier"));
			SetFantomParamFromRank(sld, sti(pchar.rank) + MOD_SKILL_ENEMY_RATE, true); // бравые орлы
            LAi_SetActorType(sld);
            LAi_SetStayType(sld); 
            LAi_group_MoveCharacter(sld, sTemp);
			LAi_group_SetLookRadius(sTemp, 10);
			LAi_group_SetHearRadius(sTemp, 10);	
			LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_SetRelation(sTemp, slai_group, LAI_GROUP_FRIEND);
            if(i < 2) 	ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "quest", "sit"+(2*i+1));
			else		PlaceCharacter(sld, "goto", "random_free");
			sld.dialog.filename = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "CaptainComission_80";							
        }				
		SetFunctionTimerConditionParam("CaptainComission_SlaveIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false); // прерывание на исчезновение раба  в течение суток
		pchar.quest.CapComission_SlaveDeath.win_condition.l1 = "NPC_Death";
		pchar.quest.CapComission_SlaveDeath.win_condition.l1.character = "CapComission_Slave";
		pchar.quest.CapComission_SlaveDeath.function = "CaptainComission_SlaveDeath";		
	}
}

void CaptainComission_GeneratePassengerSlave()
{
	string model[3];
	string sTemp = "TmpEnemy";
		
	model[0] = "citiz_26";
	model[1] = "shipowner_10";
	model[2] = "barmen_1";
	
	int iMassive = rand(2);
	
	ref sld = GetCharacter(NPC_GenerateCharacter("CapComission_Slave", model[iMassive], "man", "man", rand(5) + 5, sti(pchar.GenQuest.CaptainComission.Nation), -1, true, "slave"));	
	sld.city = pchar.GenQuest.CaptainComission.City;	
	sld.name = pchar.GenQuest.CaptainComission.SlaveName;
	sld.lastname = "";	
	
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed"); 
	
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, false);
	pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
}

void CaptainComission_GuardsAfter(string qName)
{
	pchar.quest.CaptainComission_SlaveIsOver.over = "yes";
		
	ref sld = CharacterFromId("CapComission_Slave");	
	
	if (!LAi_IsDead(sld))
	{
		sld.dialog.filename = "GenQuests_Dialog.c";
		sld.dialog.currentnode = "CaptainComission_85";	
		sld.greeting = "Gr_slave"; 
		LAi_SetStayType(sld); 
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);	
	
		pchar.quest.CaptainComission_SlaveOnMayak.win_condition.l1 = "Location";
		pchar.quest.CaptainComission_SlaveOnMayak.win_condition.l1.location = "Mayak2";
		pchar.quest.CaptainComission_SlaveOnMayak.function = "CaptainComission_OnMayak";
	
		SetFunctionTimerConditionParam("CaptainComission_SlaveDeathJungles", 0, 0, 2, MakeInt(24 - GetHour()), false);
	}	

}

void CaptainComission_SlaveDeathJungles(string qName) // если не пришёл на маяк в течение 2-х суток - раб заблудился в джунглях и помер
{
	pchar.GenQuest.CaptainComission.GetSlave = "SlaveDied";
	pchar.quest.CaptainComission_SlaveOnMayak.over = "yes";
	AddQuestRecord("CaptainComission1", "17_1");
	AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
	ref sld = characterFromId("CapComission_Slave");
	ChangeCharacterAddress(sld, "none", ""); 
	sld.lifeDay = 0; 
}

void CaptainComission_OnMayak(string qName)
{
	aref grp;	
	ref pLoc, sld;
	string encGroup, str, locator;
	int	num;

	AddQuestRecord("CaptainComission1", "18");
	AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
	
	pchar.quest.CaptainComission_SlaveDeathJungles.over = "yes";
	
	chrDisableReloadToLocation = true;
	
	pLoc = &locations[FindLocation("Mayak2")];
	encGroup = LAi_FindRandomLocator("encdetector");
	str = "locators." + encGroup;
	makearef(grp, pLoc.(str));
	num = GetAttributesNum(grp);
	if (num <= 0) num = 1;

	sld = CharacterFromId("CapComission_Slave");	
	LAi_CharacterEnableDialog(sld);
	sld.dialog.filename = "GenQuests_Dialog.c";
	sld.dialog.currentnode = "CaptainComission_90";	
		
	string sEquipItem = "slave_02"; // вооружим кинжалом, он его где-то стащил :)
	AddItems(sld, sEquipItem, 1);
	EquipCharacterByItem(sld, sEquipItem);
		
	LAi_SetStayType(sld);
	locator = GetAttributeName(GetAttributeN(grp, 1));
	ChangeCharacterAddressGroup(sld, pLoc.id, encGroup, locator);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0); 
}

void CaptainComission_SlaveDeath(string qName)
{
	pchar.GenQuest.CaptainComission.GetSlave = "SlaveDied";
	pchar.quest.CaptainComission_SlaveOnMayak.over = "yes";
	AddQuestRecord("CaptainComission1", "17");
	AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
}

void CaptainComission_SlaveIsOver(string qName)
{
	pchar.GenQuest.CaptainComission.GetSlave = "SlaveDied";
	ref sld = characterFromId("CapComission_Slave");
	ChangeCharacterAddress(sld, "none", ""); 
	sld.lifeDay = 0; 
}

void CaptainComission_GeneratePatrol()
{
	ref pLoc, chr;
	string str;
	int iRank, i, num;
	int iNation = GetCityNation("Bridgetown");

	pLoc = &locations[FindLocation("Mayak2")];
	
	str = "Patrol"+ pLoc.index + "_";
	string sGroup = "PatrolGroup_" + pLoc.index; //имя группы
	iRank = sti(pchar.rank);
	if(MOD_SKILL_ENEMY_RATE > 5) num = 5;
	else						 num = 3;	
	
	for(i = 0; i < num; i++)
	{
		if(i == 0)
		{
			int iPatrolOfficer = NPC_GenerateCharacter(str + i, "off_"+NationShortName(iNation)+"_"+(rand(1)+1), "man", "man", iRank + 2, iNation, 1, true, "officer");
			chr = &characters[iPatrolOfficer];
			SetFantomParamFromRank(chr, iRank + 2, true);	
			chr.greeting = "soldier_arest";
		}	
		else
		{
			chr = GetCharacter(NPC_GenerateCharacter(str + i, "sold_"+NationShortName(iNation)+"_"+(rand(7)+1), "man", "man", iRank, iNation, 1, true, "soldier"));
			SetFantomParamFromRank(chr, iRank, true);		
		}
		chr.City = "Bridgetown";
		chr.CityType = "soldier";
		LAi_SetWarriorType(chr);
		ChangeCharacterAddressGroup(chr, pLoc.id, "reload", "reload1");
		LAi_group_MoveCharacter(chr, sGroup);
	}
	
	LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true); 
	LAi_group_SetCheckFunction(sGroup, "CaptainComission_ExitFromMayak");
	LAi_group_SetCheck(sGroup, "OpenTheDoors"); 	
}

void CaptainComission_ExitFromMayak(string qName)
{
	ref sld;
	
	sld = characterFromId("CapComission_Slave");
	if (!LAi_IsDead(sld)) 	pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
	else 					pchar.GenQuest.CaptainComission.GetSlave = "SlaveDied";
				
	if(pchar.GenQuest.CaptainComission.GetSlave == "GetSlave")
	{
		pchar.quest.CapComission_SlaveDeath.over = "yes";
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, false);
				
		if(pchar.GenQuest.CaptainComission == "toEnemyTavern")
		{
			pchar.quest.CapComission_DeliveSlave.win_condition.l1 = "location";
			pchar.quest.CapComission_DeliveSlave.win_condition.l1.location = pchar.GenQuest.CaptainComission.SlaveCity + "_tavern";
			pchar.quest.CapComission_DeliveSlave.function = "CaptainComission_DeliveSlave";			
		}
	}	
}

void CaptainComission_GetSlave()
{	
	ref sld = CharacterFromId("Bishop_manager");
	sld.lifeDay = 1; 
	
	pchar.quest.CapComission_GetSlave.win_condition.l1 = "ExitFromLocation";
	pchar.quest.CapComission_GetSlave.win_condition.l1.location = pchar.location;
	pchar.quest.CapComission_GetSlave.function = "CaptainComission_GenerateSlave";
	
	pchar.quest.CaptainComission_30DaysIsLeft.over = "yes";
}

void CaptainComission_DeliveSlave(string qName)
{
	chrDisableReloadToLocation = true;
	ref sld = characterFromId("CapComission_Slave");
	RemovePassenger(pchar, sld);	
	sld.dialog.filename = "GenQuests_Dialog.c";
	sld.dialog.currentnode = "CaptainComission_100";	
	PlaceCharacter(sld, "goto", "random_must_be_near");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);	
}

void GetSlaveSpeciality()
{
	string Speciality;
	int Spec = hrand(2); // hrand auto tagged
	switch (Spec)
    {
        case 0 :
             Speciality = StringFromKey("GenQuests_35");
        break;
        case 1 :
            Speciality = StringFromKey("GenQuests_36");
        break;
        case 2 :
            Speciality = StringFromKey("GenQuests_37");
        break;
    }
	pchar.GenQuest.CaptainComission.SlaveSpeciality = Speciality;	
	pchar.GenQuest.CaptainComission.Speciality = Spec;
}

void CaptainComission_GeneratePirateShips(string qName)
{
	int i, ShipType, Rank, iShipRank, iCannonType;
	ref sld;
	string Blade, sTemp;
			
	Log_QuestInfo("Пиратские корабли установлены, будет крутое рубилово.");
    Island_SetReloadEnableGlobal(pchar.GenQuest.CaptainComission.Island, false);
    Group_FindOrCreateGroup("Pirate_Attack");
	Group_SetType("Pirate_Attack", "war");
	// ==> Пиратские кэпы
	for (i=1; i<=2; i++)
	{
		Rank = sti(pchar.rank) + rand(MOD_SKILL_ENEMY_RATE);
		if(makeint(pchar.rank) > 13) { iShipRank = rand(2) + 3; }
		if(makeint(pchar.rank) > 6 && makeint(pchar.rank) < 13) { iShipRank = rand(2); }	
		if(makeint(pchar.rank) < 7) { iShipRank = rand(1); }
		switch (iShipRank)
		{
			case 0: 		 
				ShipType = SHIP_SCHOONER_W;
				Rank = 10 + rand(5);
                Blade = "blade_11";
				iCannonType = CANNON_TYPE_CANNON_LBS16;
			break; 		
			case 1:  
				ShipType = SHIP_BRIG;     					
				Rank = 14 + rand(5);
                Blade = "blade_12";
				iCannonType = CANNON_TYPE_CANNON_LBS16;
			break; 		
			case 2:  
				ShipType = SHIP_BRIGANTINE;			
				Rank = 20 + rand(5);
                Blade = "blade_10";
				iCannonType = CANNON_TYPE_CANNON_LBS16;
			break; 
			case 3: 
				ShipType = SHIP_CORVETTE; 				
				Rank = 25 + rand(5);
                Blade = "blade_15";
				iCannonType = CANNON_TYPE_CANNON_LBS20;
			break; 
			case 4: 
				ShipType = SHIP_FRIGATE;         			
				Rank = 30 + rand(5);
                Blade = "blade_19";
				iCannonType = CANNON_TYPE_CANNON_LBS24;
			break; 
			case 5: 
				ShipType = SHIP_LINESHIP; 						
				Rank = 35 + rand(5);
                Blade = "blade_21";
				iCannonType = CANNON_TYPE_CANNON_LBS32;
			break;  				
		}
		if(i == 1) 	sTemp = pchar.GenQuest.CaptainComission.ShipName1;
		else 		sTemp = pchar.GenQuest.CaptainComission.ShipName2;
		sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, "mercen_"+(rand(14)+14), "man", "man", Rank, PIRATE, 3, true, "quest"));
		FantomMakeCoolSailor(sld, ShipType, sTemp, iCannonType, 60 + rand(20), 95, 95);
		FantomMakeCoolFighter(sld, Rank, 50 + rand(30), 50 + rand(20), Blade, "pistol3", "grapeshot", 50);
		Group_AddCharacter("Pirate_Attack", "CaptainAttack_"+i);
		
		sld.SuperShooter  = true;

		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "GunProfessional");
		SetCharacterPerk(sld, "MusketsShoot");
		
		sld.ship.Crew.Morale = 50 + rand(30);
		ChangeCrewExp(sld, "Sailors", 70 + rand(10));
		ChangeCrewExp(sld, "Cannoners", 70 + rand(10));
		ChangeCrewExp(sld, "Soldiers", 70 + rand(10));
    }
    // ==> стравливание
	Group_SetGroupCommander("Pirate_Attack", "CaptainAttack_1");
	Group_SetTaskAttack("Pirate_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Pirate_Attack", PLAYER_GROUP);
	Group_SetAddress("Pirate_Attack", pchar.GenQuest.CaptainComission.Island, "", "");
	Group_LockTask("Pirate_Attack");
			
    // ==> прерывание на убиение эскадры
    pchar.quest.CapComission_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.CapComission_AfterBattle.win_condition.l1.group = "Pirate_Attack";
	pchar.quest.CapComission_AfterBattle.function = "CaptainComission_PirateAttack_AfterBattle";
	pchar.quest.CapComission_DieHard.win_condition.l1 = "MapEnter";
    pchar.quest.CapComission_DieHard.function = "CaptainComission_PirateAttack_DieHard";
}

void CaptainComission_PirateAttack_AfterBattle(string qName)
{
	Log_QuestInfo("Пиратская эскадра разбита.");
	Group_DeleteGroup("Pirate_Attack");
	Island_SetReloadEnableGlobal(pchar.GenQuest.CaptainComission.Island, true);
    pchar.quest.CapComission_DieHard.over = "yes";
	pchar.quest.CaptainComission_PirateShipsOver.over = "yes";
	AddQuestRecord("CaptainComission1", "25");
	AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_GEN));
	AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
	AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
	AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc")); // belamour gen
	AddQuestUserData("CaptainComission1", "sNameNom", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
	pchar.GenQuest.CaptainComission.PirateShips = "died";
	DeleteAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak");
}

void CaptainComission_PirateAttack_DieHard(string qName)
{
	Log_QuestInfo("Свалил с поля боя, очень плохо.");
	Group_DeleteGroup("Pirate_Attack");
    Island_SetReloadEnableGlobal(pchar.GenQuest.CaptainComission.Island, true);
    pchar.quest.CapComission_AfterBattle.over = "yes";
	pchar.quest.CaptainComission_PirateShipsOver.over = "yes";
	AddQuestRecord("CaptainComission1", "33");
	AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase(StringFromKey("GenQuests_62"),StringFromKey("GenQuests_63")));
	AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
	AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
	AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc")); // belamour gen
	//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
	pchar.GenQuest.CaptainComission.PirateShips = "goaway";
	ChangeOfficersLoyality("bad_all",1);
}
//=====================================================================================================================================
// <-- ГЕНЕРАТОР  "ПОРУЧЕНИЕ КАПИТАНА - ВЫКУП"
//=====================================================================================================================================

//=====================================================================================================================================
// Ugeen. ГЕНЕРАТОР  "ПОРУЧЕНИЕ КАПИТАНА - ОПЕРАЦИЯ 'ГАЛЕОН'"
//=====================================================================================================================================
void CaptainComission_GaleonInit(ref chref)
{
	pchar.GenQuest.CaptainComission.Nation = chref.nation;
	pchar.GenQuest.CaptainComission.City = GetQuestNationsCity(sti(chref.nation));
	pchar.GenQuest.CaptainComission.Name = GenerateRandomName_Generator(sti(chref.nation), "man");
	pchar.GenQuest.CaptainComission.ShipName = chref.Back.Ship.Name;
	pchar.GenQuest.CaptainComission.City1 = FindAlliedColonyForNationExceptColony(pchar.GenQuest.CaptainComission.City);
	pchar.GenQuest.CaptainComission.Goods = CaptainComission_GetVictimShipGoods();
	pchar.GenQuest.CaptainComission.Speak_Tavern = false;
	pchar.GenQuest.CaptainComission.Prize = GenQuest_GeneratePrize();
	CaptainComission_GenerateShips();
}

void CaptainComission_GenerateShips()
{
	int iShipType, iShipTypeVictim;
	if(sti(pchar.rank) < 20)
	{
		switch(rand(1))
		{
			case 0: iShipType = SHIP_LUGGER; 	break;
			case 1: iShipType = SHIP_SLOOP;		break;
		}
		switch(rand(2))
		{
			case 0: iShipTypeVictim = SHIP_CARAVEL; 	break;
			case 1: iShipTypeVictim = SHIP_BARKENTINE;	break;
			case 2: iShipTypeVictim = SHIP_FLEUT;		break;
		}
	}
	else
	{
		switch(rand(2))
		{
			case 0: iShipType = SHIP_BARQUE;	break;
			case 1: iShipType = SHIP_BRIG;		break;
			case 2:	iShipType = SHIP_CORVETTE;	break;
		}
		switch(rand(2))
		{
			case 0: iShipTypeVictim = SHIP_GALEON_L;	break;
			case 1: iShipTypeVictim = SHIP_GALEON_H;	break;
			case 2:	iShipTypeVictim = SHIP_PINNACE;		break;
		}
	}
	pchar.GenQuest.CaptainComission.ShipType = iShipType;
	pchar.GenQuest.CaptainComission.ShipTypeVictim = iShipTypeVictim;
	pchar.GenQuest.CaptainComission.ShipTypeName = GenerateRandomNameToShip(sti(pchar.GenQuest.CaptainComission.Nation));
	pchar.GenQuest.CaptainComission.VictimShipName = GenerateRandomNameToShip(rand(3));
}

// не успели за 15 дней - закрываем квест
void CaptainComission_TimeIsOver(string qName)
{
	ref sld;
	if(CheckAttribute(pchar,"GenQuest.CaptainComission.variant"))
	{
		if(pchar.GenQuest.CaptainComission.variant == "A1")
		{
			pchar.quest.CaptainComission_SailToShore.over = "yes";
			Group_DeleteGroup("Sea_CapComission_1"); 
			sld = CharacterFromID("CapComission_1");
			sld.LifeDay = 0;	
			AddQuestRecord("CaptainComission2", "8");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			return;
		}
		if(pchar.GenQuest.CaptainComission.variant == "A2")
		{
			AddQuestRecord("CaptainComission2", "8");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			return;			
		}
		if(pchar.GenQuest.CaptainComission.variant == "A3") 
		{
			pchar.quest.CaptainComission_MeetCanoneerInShoreTimer.over = "yes";
			sld = CharacterFromID("CapComission_Canoneer");
			sld.LifeDay = 0;
			AddQuestRecord("CaptainComission2", "44");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //лесник - на тип корабля. 
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			CloseQuestHeader("CaptainComission2");
			ChangeOfficersLoyality("bad_all", 1);
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			return;
		}
	}	
	
	AddQuestRecord("CaptainComission2", "2");
	AddQuestUserData("CaptainComission2", "sCapName", pchar.GenQuest.CaptainComission.CapName); // belamour gen
	CloseQuestHeader("CaptainComission2");
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
}

// генерим продолжение квеста в зависимости от срока прибытия к заданному острову
void CaptainComission_GenerateQuestContinuation(string qName)
{
	int DaysIsLeft = GetQuestPastDayParam("GenQuest.CaptainComission");
	
	pchar.quest.CaptainComission_TimeIsOver.over = "yes"; // снимаем таймер на опоздание
	if(DaysIsLeft <= 5) // вариант A1 - 100%
	{
		pchar.GenQuest.CaptainComission.variant = "A1";
	}
	else
	{
		if(DaysIsLeft <= 10) // вариант A1 - 50 %  && A2 - 50%
		{
			if(rand(1) == 0) 	pchar.GenQuest.CaptainComission.variant = "A1";
			else				pchar.GenQuest.CaptainComission.variant = "A2";
		}
		else // вариант A1 - 30 %, A2 - 30 %, A3 - 40 %
		{
			int iRnd = rand(9); 
			if(iRnd < 3) pchar.GenQuest.CaptainComission.variant = "A1";
			else 
			{
				if(iRnd < 6) 	pchar.GenQuest.CaptainComission.variant = "A2";
				else			pchar.GenQuest.CaptainComission.variant = "A3";
			}	
		}
	}
	CaptainComission_GenerateQuestVariant();
}

void CaptainComission_GenerateQuestVariant()
{
	switch(pchar.GenQuest.CaptainComission.variant)
	{
		case "A1":
			Log_QuestInfo("вариант 1");
			CaptainComission_GenerateShip();
		break;
		case "A2":
			Log_QuestInfo("вариант 2");
			CaptainComission_GenerateRumourCaptainPrison();
		break;
		case "A3":
			Log_QuestInfo("вариант 3");
			CaptainComission_GenerateRumourCaptainDeath();
		break;
	}
}

void CaptainComission_GenerateShip()
{
	int iRank = sti(pchar.rank) + 5 + rand(MOD_SKILL_ENEMY_RATE);
	int iNation = sti(pchar.GenQuest.CaptainComission.Nation);
	ref chref = GetCharacter(NPC_GenerateCharacter("CapComission_1", "off_"+NationShortName(iNation)+"_"+(rand(1)+1), "man", "man", iRank, iNation, -1, true, "quest"));
	
	chref.name = pchar.GenQuest.CaptainComission.Name;
	chref.lastname = "";
	chref.city = pchar.GenQuest.CaptainComission.City;
	chref.dialog.filename      = "GenQuests_Dialog.c";
	chref.DeckDialogNode	   = "CaptainComission_301";	 
	chref.dialog.currentnode   = "CaptainComission_301";
		
	chref.Ship.Name = pchar.GenQuest.CaptainComission.ShipTypeName;
	FantomMakeCoolSailor(chref, sti(pchar.GenQuest.CaptainComission.ShipType), chref.Ship.Name, CANNON_TYPE_CULVERINE_LBS18, 90, 90, 90);	
	FantomMakeCoolFighter(chref, makeint(pchar.rank) + rand(10) + 5, 90, 50, LinkRandPhrase("blade_06","blade_08","blade_10"), "pistol3", "grapeshot", 80);
	chref.cirassId = Items_FindItemIdx("cirass1");  
	LAi_SetHP(chref, 200 + makeint(pchar.rank) * 5, 200 + makeint(pchar.rank) * 5);

	SetCharacterPerk(chref, "MusketsShoot");
	SetCharacterPerk(chref, "Energaiser"); 	
	
	chref.ship.Crew.Morale = 90;
	ChangeCrewExp(chref, "Sailors", 100);
	ChangeCrewExp(chref, "Cannoners", 100);
	ChangeCrewExp(chref, "Soldiers", 100);
   		
	chref.AlwaysFriend = true;
	chref.Abordage.Enable = false; //нельзя брать на абордаж
	
	string sGroup = "Sea_CapComission_1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
    Group_SetType(sGroup, "war");
	
	SetCharacterRelationBoth(sti(chref.index), GetMainCharacterIndex(), RELATION_FRIEND);
	
	int IslandID = FindIsland(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
	ref pLoc = &Islands[IslandID];
	float x, y, z;
	FindIslandLocatorXYZ(IslandID, "reload1", &x, &y, &z); 
	string sLocator = GetSeaQuestShipFarLocator(pLoc, "Quest_ships", x, y, z);
	
	Group_AddCharacter(sGroup, "CapComission_1");
    Group_SetGroupCommander(sGroup, "CapComission_1");
	Group_SetAddress(sGroup, GetArealByCityName(pchar.GenQuest.CaptainComission.City),"quest_ships", sLocator);
	Group_SetTaskNone(sGroup);
	
	SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
}

void CaptainComission_ExitFromLoc(string qName)
{
	ref sld;
	if(pchar.GenQuest.CaptainComission == "close")
	{
		if(pchar.GenQuest.CaptainComission.variant == "A1")
		{
			sld = CharacterFromID("CapComission_1");
			sld.Dialog.Filename = "Capitans_dialog.c"; // при повторном диалоге
            // нет такого звука
			//sld.greeting        = "Gr_Commander";
			sld.DeckDialogNode  = "Go_away";
			sld.LifeDay = 2;					// сам помрет через 2 дня
		}
		if(pchar.GenQuest.CaptainComission.variant == "A3")
		{
			sld = CharacterFromID("CapComission_Canoneer");
			sld.LifeDay = 0;					
		}
		DeleteAttribute(pchar, "GenQuest.CaptainComission");
	}
}

int CaptainComission_GetVictimShipGoods()
{
	int iGoodIdx;
	switch (rand(6))
    {
        case 0 :
            iGoodIdx = GOOD_CHOCOLATE;
        break;
        case 1 :
            iGoodIdx = GOOD_TOBACCO;
        break;
        case 2 :
            iGoodIdx = GOOD_COFFEE;
        break;
        case 3 :
            iGoodIdx = GOOD_MAHOGANY;
        break;
        case 4 :
            iGoodIdx = GOOD_CINNAMON;
        break;
        case 5 :
            iGoodIdx = GOOD_EBONY;
        break;		
        case 6 :
            iGoodIdx = GOOD_COPRA;
        break;		
    }
	return iGoodIdx;
}

void CaptainComission_CapIsOut(string qName) // свалили из боя
{
	ref sld;
	pchar.GenQuest.CaptainComission = "CaptainIsOut"; 
	pchar.quest.CaptainComission_CapIsDead.over = "yes";
	Group_DeleteGroup("Sea_CapComission_1");
	sld = CharacterFromID("CapComission_1");
	sld.LifeDay = 0;	
	
	AddQuestRecord("CaptainComission2", "6");
	AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase(StringFromKey("GenQuests_70"),StringFromKey("GenQuests_71")));
	AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
	AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
	AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen"));
	CloseQuestHeader("CaptainComission2");	
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
}

void CaptainComission_CapIsDead(string qName)
{
	pchar.quest.CaptainComission_CapIsOut.over = "yes";	
	AddQuestRecord("CaptainComission2", "5");
	AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase(StringFromKey("GenQuests_70"),StringFromKey("GenQuests_71")));
	AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
	AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
	AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen"));
	CloseQuestHeader("CaptainComission2");	
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
}

void CaptainComission_toShore() // вышвыриваем в бухту без штанов
{
	ref sld;
	Group_DeleteGroup("Sea_CapComission_1");
	sld = CharacterFromID("CapComission_1");
	sld.LifeDay = 0;
	
	DeleteAttribute(pchar, "ship"); // допрыгался 
	pchar.ship.name = "";
	pchar.ship.type = SHIP_NOTUSED;
	
	SetCharacterShipLocation(pchar, "");
	
	pchar.money = 0;
	RemoveAllPassengersAndCompanions();
	CleanAllCabinBoxes();
	
	AddSimpleRumour(RandPhraseSimple(StringFromKey("GenQuests_38"), 
				StringFromKey("GenQuests_39")), sti(pchar.GenQuest.CaptainComission.Nation), 5, 2);
	pchar.quest.Munity = "Deads";
	pchar.location.from_sea = pchar.GenQuest.CaptainComission.City + "_town";
	
	AddQuestRecord("CaptainComission2", "4");
	AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
	AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
	AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
	AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen"));
	CloseQuestHeader("CaptainComission2");
	
	if(bDisableMapEnter) bDisableMapEnter = false; //  если был бой
	
	DoReloadFromDeckToLocation(pchar.GenQuest.CaptainComission.ShoreLocation, "reload", "sea");
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
}

void CaptainComission_SailToShore(string qName)
{
	Log_Info(StringFromKey("GenQuests_40"));
	ref sld = characterFromId("CapComission_1");

	SetCharacterShipLocation(sld, pchar.GenQuest.CaptainComission.ShoreLocation);
	SetFunctionLocationCondition("CaptainComission_MeetInShore", pchar.GenQuest.CaptainComission.ShoreLocation, false); 
	SetFunctionTimerCondition("CaptainComission_SailToShoreOver", 0, 0, 1, false); // таймер лесник
}
void CaptainComission_SailToShoreOver(string qName) // мой код . лесник. если опоздали квест удаляется . 
{
			Group_DeleteGroup("Sea_CapComission_1"); 
			ref sld = CharacterFromID("CapComission_1");
			//pchar.GenQuest.CaptainComission.provalqvesta = "true";
			sld.LifeDay = 0;	
			AddQuestRecord("CaptainComission2", "8");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			pchar.GenQuest.CaptainComission = "close";
			DeleteAttribute(pchar, "GenQuest.CaptainComission"); 			
		
}	
// встречаемся на берегу
void CaptainComission_MeetInShore(string qName)
{
      //chrDisableReloadToLocation = true; // лесник . а иначе она остаётся закрытой навечно при провале по времени встречи.
	  pchar.quest.CaptainComission_SailToShoreOver.over = "yes"; // снятие таймера - лесник
	pchar.quest.CaptainComission_TimeIsOver.over = "yes"; 
	ref sld = characterFromId("CapComission_1");
	if(pchar.GenQuest.CaptainComission.variant == "A1")
	{	
        chrDisableReloadToLocation = true; // лесник - закрыть локацию
		sld.dialog.currentnode = "CaptainComission_315";	
	}
	if(pchar.GenQuest.CaptainComission.variant == "A2")
	{
		chrDisableReloadToLocation = true;  //лесник - закрытие локации 
		sld.dialog.currentnode = "CaptainComission_383";
		LAi_LocationDisableOfficersGen(pchar.GenQuest.CaptainComission.ConvoyShore, true);
		pchar.quest.CaptainComission_CapEscapeTimer.over = "yes";	
		DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakBoatswain");
		CaptainComission_GenerateGangInShore();
	}
	 
	
	PlaceCharacter(sld, "goto", "random_must_be_near");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);	
}

void CaptainComission_GenerateShorePatrol()
{
	ref sld;
	string attrName;

	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, true);
	int iTemp = sti(pchar.GenQuest.CaptainComission.Nation);// Нация патруля
	pchar.GenQuest.CaptainComission.SoldierQty = makeint(2 * GetOfficersQuantity(pchar) + 3);
	for (int i = 2; i <= sti(pchar.GenQuest.CaptainComission.SoldierQty); i++)
	{
		sld = SetFantomDefenceForts("", "", iTemp, "CoastalGuards");
		attrName = "SoldierIDX" + i;
    	pchar.GenQuest.CaptainComission.(attrName) = sld.index;
		LAi_SetActorType(sld);
    	LAi_ActorFollow(sld, pchar, "", 38);
		LAi_CharacterDisableDialog(sld);
		sld.greeting = "Gr_Costal_Guards";
	}
	sld = SetFantomOfficer("", "", iTemp, "CoastalGuards");
	pchar.GenQuest.CaptainComission.SoldierIDX1 = sld.index;
	LAi_SetActorType(sld);
	sld.Dialog.Filename = "GenQuests_Dialog.c";
	sld.Dialog.CurrentNode = "CaptainComission_317";
	sld.greeting = "Gr_Costal_Guards";

	LAi_ActorDialog(&Characters[makeint(pchar.GenQuest.CaptainComission.SoldierIDX1)], pchar, "", 35, 1);
	LAi_group_SetCheck("CoastalGuards", "OpenTheDoors");	
	LAi_group_SetCheckFunction("CoastalGuards", "CaptainComission_AfterShoreBattle"); 
}

void CaptainComission_AfterShoreBattle(string qName)
{
	ref sld = characterFromId("CapComission_1");	
	if (LAi_IsDead(sld))
	{
		AddQuestRecord("CaptainComission2", "9");
		AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen")); // belamour gen
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		CloseQuestHeader("CaptainComission2");	
		DeleteAttribute(pchar, "GenQuest.CaptainComission");	
     		
	}
	else
	{
		sld = characterFromId("CapComission_1"); // лесник . временно ,защита от дураков
		LAi_SetImmortal(sld, true);
		sld.dialog.currentnode = "CaptainComission_320";	
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);	
	}
	 
}

void CaptainComission_GenerateCoastalPatrol()
{
	ref CoastGuard;
	int i;
	int iNation = sti(pchar.GenQuest.CaptainComission.Nation);// Нация патруля
	string Model;
	
	for (i = 1; i <= 3; i++)
    {
        Model = "off_" + NationShortName(iNation) + "_" + (rand(1) + 1);
		CoastGuard = GetCharacter(NPC_GenerateCharacter("Coastal_Captain0" + i, Model, "man", "man", sti(pchar.rank) + rand(MOD_SKILL_ENEMY_RATE), iNation, 3, true, "officer")); // 3 дня, потом сами пропадут
		SetFantomParam(CoastGuard);
		SelectCoastalGuardShip(CoastGuard);
		CoastGuard.AlwaysEnemy = true;
		CoastGuard.DontRansackCaptain = true;
		CoastGuard.AlwaysSandbankManeuver = true;
		Group_AddCharacter("Coastal_Guards", CoastGuard.id);
		SetCharacterRelationBoth(sti(CoastGuard.index), GetMainCharacterIndex(), RELATION_ENEMY);
		if (makeint(pchar.rank) < 6 && i == 1 && GetCompanionQuantity(pchar) == 1) break;
		if (makeint(pchar.rank) < 9 && i == 2 && GetCompanionQuantity(pchar) < 3) break;
    }
	Group_SetGroupCommander("Coastal_Guards", "Coastal_Captain01");
	Group_SetAddress("Coastal_Guards", Islands[GetCharacterCurrentIsland(Pchar)].id, "", "");
	Group_SetPursuitGroup("Coastal_Guards", PLAYER_GROUP);
	Group_SetTaskAttack("Coastal_Guards", PLAYER_GROUP);
	Group_LockTask("Coastal_Guards");
}

void CaptainComission_CapShip_Sink(string qName)
{
	pchar.quest.CaptainComission_MapEnter.over = "yes";
	AddQuestRecord("CaptainComission2", "12");
	AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))); // belamour gen
	AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
	AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
	AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
	CloseQuestHeader("CaptainComission2");	
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
}

void CaptainComission_MapEnter(string qName)
{
	DeleteAttribute(pchar,"GenQuest.CannotWait");
	pchar.quest.CaptainComission_CapShip_Sink.over = "yes";
	SetFunctionLocationCondition("CaptainComission_ConvoyInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false);
	pchar.quest.CaptainComission_Ship_Sink.win_condition.l1 = "Character_sink";
	pchar.quest.CaptainComission_Ship_Sink.win_condition.l1.character = "CapComission_1";
	pchar.quest.CaptainComission_Ship_Sink.function = "CaptainComission_Ship_Sink";
	SetFunctionTimerCondition("CaptainComission_ConvoyTimeIsOut", 0, 0, sti(pchar.GenQuest.CaptainComission.iDay) * 2, false);
	SaveCurrentQuestDateParam("GenQuest.CaptainComission");
}

void CaptainComission_ConvoyInShore(string qName)
{
	ref sld;
	pchar.quest.CaptainComission_Ship_Sink.over = "yes";
	pchar.quest.CaptainComission_ConvoyTimeIsOut.over = "yes";
	
	int DaysIsLeft = GetQuestPastDayParam("GenQuest.CaptainComission");
	
	sld = characterFromId("CapComission_1");	
	PlaceCharacter(sld, "goto", "random_must_be_near");
	if(DaysIsLeft <= sti(pchar.GenQuest.CaptainComission.iDay))
	{
		LAi_SetActorTypeNoGroup(sld);
		CaptainComission_GenerateGangInShore();
	}
	else
	{
		sld.dialog.currentnode = "CaptainComission_340";	
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);	
	}		
}

void CaptainComission_GenerateGangInShore()
{
	string encGroup, str, locator;
	int num, i, k, iNation, iRank, n;
	ref pLoc, sld;
	aref grp;
	
	chrDisableReloadToLocation = true;
	pLoc = &locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)];
	encGroup = "smugglers";
	str = "locators." + encGroup;
	makearef(grp, pLoc.(str));
	num = GetAttributesNum(grp); //кол-во человек в банде
	if (num <= 0) num = 1;
	
	str = "Gang" + "_";
	string sGroup = "GangGroup_0"; //имя группы
	LAi_LocationFightDisable(pLoc, true);	
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, true);
		
	arrayNPCModelHow = 0;
	
	for (i = 0; i < num; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter(str + i, "off_hol_2", "man", "man", 5, PIRATE, 3, true, "hunter"));
        SetFantomParamHunter(sld); 
		SetModelPirate(sld);
		k = 0;
		while (!CheckNPCModelUniq(sld) && k < 10)
		{
		    k++;
			SetModelPirate(sld);
		}
		arrayNPCModel[arrayNPCModelHow] = sld.model;
		arrayNPCModelHow++;

		LAi_SetStayType(sld);
		LAi_group_MoveCharacter(sld, sGroup);
		pchar.GenQuest.CaptainComission.GangNum = num;
		sld.greeting = "Gr_Smuggler_OnShore";
		locator = GetAttributeName(GetAttributeN(grp, i));
		ChangeCharacterAddressGroup(sld, pLoc.id, encGroup, locator);
		LAi_SetImmortal(sld, true);
		if (i == 0) 
		{
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true; 
			sld.dialog.filename = "GenQuests_Dialog.c";
			if(pchar.GenQuest.CaptainComission.variant == "A1")
			{
				sld.Dialog.CurrentNode = "CaptainComission_326";
			}
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				if(pchar.GenQuest.CaptainComission == "GetGoodsEscape")
				{
					sld.Dialog.CurrentNode = "CaptainComission_396";
				}
				else
				{
					sld.Dialog.CurrentNode = "CaptainComission_384";
				}	
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				sld.Dialog.CurrentNode = "CaptainComission_360";
			}
		}
		else
		{
			LAi_CharacterDisableDialog(sld);
		}
	}
	sld = CharacterFromID("CapComission_1");
	if(pchar.GenQuest.CaptainComission.variant == "A1")
	{
		sld.Dialog.CurrentNode = "CaptainComission_326_0";
	}	
	if(pchar.GenQuest.CaptainComission.variant == "A2" && pchar.GenQuest.CaptainComission == "GetGoodsEscape")
	{
		sld.Dialog.CurrentNode = "CaptainComission_396_0";
	}	
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);		
}

void CaptainComission_DialogInShore()
{
	ref sld = CharacterFromID("CapComission_1");
	LAi_SetImmortal(sld, false);// лесник . защита от дурака снята. 
	sld.CaptainComission.Name = pchar.GenQuest.CaptainComission.Name;
	sld.CaptainComission.CapName = pchar.GenQuest.CaptainComission.CapName;
	sld.CaptainComission.FullName = GetFullName(pchar);
	sld.CaptainComission.ShipTypeVictim = pchar.GenQuest.CaptainComission.ShipTypeVictim;
	ChangeShowIntarface();
	StartQuestMovie(true, false, true);
	LAi_SetActorType(pchar);	

	SetMainCharacterIndex(GetCharacterIndex("CapComission_1"));
	pchar = GetMainCharacter();
	locCameraTarget(pchar)
	locCameraFollow();
	LAi_SetActorType(pchar);		
	LAi_SetActorType(CharacterFromID("Gang_0"));
	SetActorDialogAny2Pchar("Gang_0", "", -1.0, 0.0);
	LAi_ActorFollow(pchar, CharacterFromID("Gang_0"), "ActorDialog_Any2Pchar", -1);		
}


void CaptainComission_GangDialog()
{
	ref sld;

	SetMainCharacterIndex(1);
    pchar = GetMainCharacter();
    LAi_SetPlayerType(pchar);
	locCameraTarget(pchar);
    locCameraFollow();
    EndQuestMovie(); 
	ChangeShowIntarface();
	bDisableCharacterMenu = false;
	
	sld = CharacterFromID("Gang_0");
	sld.Dialog.CurrentNode = "CaptainComission_328";
	LAi_SetActorType(pchar); 
	LAi_ActorTurnToCharacter(pchar, sld);
	LAi_SetActorType(sld);
	SetActorDialogAny2Pchar(sld.id, "", 0.0, 1.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
}

void CaptainComission_GangExit()
{
	ref sld;
	int iTemp;
	float locx, locy, locz;
	
	DoQuestCheckDelay("OpenTheDoors", 1.0);
	LAi_SetPlayerType(pchar);
	GetCharacterPos(pchar, &locx, &locy, &locz);
    for (int i = 0; i < sti(pchar.GenQuest.CaptainComission.GangNum); i++)
	{
		sld = characterFromID("Gang_" + i);
		LAi_SetActorType(sld); 
		LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", -1.0);			
		iTemp = GetCharacterIndex("Gang_" + i);
		if (iTemp != -1)
		{
			characters[iTemp].lifeDay = 0;
		}
	}
	sld = characterFromID("CapComission_1");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", -1.0);
	sld.lifeDay = 0;
	RemoveCharacterCompanion(pchar, sld);// выход корабля быашего компаньона . лесник
	pchar.quest.CaptainComission_ExitFromShoreAfterGang.win_condition.l1 = "MapEnter";           	
    pchar.quest.CaptainComission_ExitFromShoreAfterGang.function = "CaptainComission_ExitFromShoreAfterGang";
	InterfaceStates.Buttons.Save.enable = true; 
	
}

void CaptainComission_ExitFromShoreAfterGang(string qName)
{	
	if (GetCharacterIndex("CapComission_2") > 0) 
	{
		DeleteAttribute(pchar, "GenQuest.CaptainComission");
		characters[GetCharacterIndex("CapComission_2")].lifeDay = 0;
		
	}
	DeleteAttribute(pchar, "GenQuest.CaptainComission");

			
}

void CaptainComission_ChangeCaptain()
{
	int iRank = sti(pchar.rank) + 5 + rand(MOD_SKILL_ENEMY_RATE);
	int iNation = sti(pchar.GenQuest.CaptainComission.Nation);
	aref	arShip1, arShip2;
	ref chref, sld;
	
	chref = GetCharacter(NPC_GenerateCharacter("CapComission_2", "mercen_"+(rand(14)+1), "man", "man", iRank, iNation, -1, true, "hunter"));
	chref.name = GenerateRandomName_Generator(sti(chref.nation), "man");
	chref.lastname = "";
	SetCharacterPerk(chref, "MusketsShoot");
	SetCharacterPerk(chref, "Energaiser"); 	
	FantomMakeCoolFighter(chref, makeint(pchar.rank) + rand(10) + 5, 90, 50, "blade_06", "pistol3", "grapeshot", 80);
	chref.cirassId = Items_FindItemIdx("cirass1");  // предмета нет, но влияение есть
	LAi_SetHP(chref, 200 + makeint(pchar.rank) * 5, 200 + makeint(pchar.rank) * 5);
	
	DeleteAttribute(chref, "ship"); 
	chref.ship = ""; 
	
	sld = CharacterFromID("CapComission_1");
	
	makearef(arShip1, sld.Ship);
	makearef(arShip2, chref.Ship);
	CopyAttributes(arShip2,arShip1);
	DeleteAttribute(sld, "ship"); 
	sld.ship.type = SHIP_NOTUSED;
	SeaAI_SetOfficer2ShipAfterAbordage(chref, sld); 
	
	RemoveCharacterCompanion(pchar, sld);

	Group_DelCharacter(PLAYER_GROUP, sld.id);
	
	string sGroup = "Sea_CapComission_2";
	Group_FindOrCreateGroup(sGroup);
    Group_SetType(sGroup, "war");
			
	Group_AddCharacter(sGroup, "CapComission_2");
    Group_SetGroupCommander(sGroup, "CapComission_2");
	Group_SetAddress(sGroup, Islands[GetCharacterCurrentIsland(Pchar)].id, "", "");
	Group_SetPursuitGroup(sGroup, PLAYER_GROUP);
	
	chref.nation = PIRATE;
	Ship_NationAgressivePatent(chref);
	Ship_FlagRefresh(chref); //флаг на лету	
	
	SetCharacterRelationBoth(sti(chref.index), GetMainCharacterIndex(), RELATION_ENEMY);
	DeleteAttribute(chref, "AlwaysFriend"); 
	DeleteAttribute(chref,"Abordage.Enable");
	
	Group_SetTaskAttack(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);			
}

void CaptainComission_GangDied(string qName)
{
	if(pchar.GenQuest.CaptainComission.variant == "A1")
	{
		AddQuestRecord("CaptainComission2", "16");
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		AddQuestUserData("CaptainComission2", "sShoreName", UpperFirst(XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen"))); // belamour gen
		CloseQuestHeader("CaptainComission2");	
		pchar.quest.CaptainComission_MapEnterAfterGang.win_condition.l1 = "MapEnter";
		pchar.quest.CaptainComission_MapEnterAfterGang.function = "CaptainComission_ExitFromShoreAfterGang"; 
	}
	if(pchar.GenQuest.CaptainComission.variant == "A2")
	{
		ref sld = CharacterFromId("CapComission_1");	
		if (LAi_IsDead(sld)) // погиб
		{
			AddQuestRecord("CaptainComission2", "33");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			OfficersReaction("bad");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");			
		}
		else
		{
			
			sld.dialog.currentnode = "CaptainComission_401";	
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
		}
	}
	InterfaceStates.Buttons.Save.enable = true;
}

void CaptainComission_ConvoyTimeIsOut(string qName)
{
	pchar.quest.CaptainComission_ConvoyInShore.over = "yes"; 
	pchar.quest.CaptainComission_Ship_Sink.over = "yes";
	ref sld = CharacterFromId("CapComission_1");
	RemoveCharacterCompanion(pchar, sld);
	AddQuestRecord("CaptainComission2", "14");
	AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
	AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")); // belamour gen
	CloseQuestHeader("CaptainComission2");	
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
}

void CaptainComission_Ship_Sink(string qName)
{
	pchar.quest.CaptainComission_ConvoyInShore.over = "yes"; 
	pchar.quest.CaptainComission_ConvoyTimeIsOut.over = "yes";
	AddQuestRecord("CaptainComission2", "13");
	AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))); 
	AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
	AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
	AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
	CloseQuestHeader("CaptainComission2");	
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
}

// ветка №2
void CaptainComission_GenerateRumourCaptainPrison()
{
	string sShipType = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"));
	AddSimpleRumourCity(LinkRandPhrase(StringFromKey("GenQuests_41", GetAddress_Form(pchar), sShipType, pchar.GenQuest.CaptainComission.Name),
		StringFromKey("GenQuests_42", sShipType, pchar.GenQuest.CaptainComission.Name, GetAddress_Form(pchar)),
		RandPhraseSimple(StringFromKey("GenQuests_43", pchar.GenQuest.CaptainComission.Name, GetAddress_Form(pchar)),
		StringFromKey("GenQuests_44", sShipType, pchar.GenQuest.CaptainComission.Name))),
		pchar.GenQuest.CaptainComission.City, 5, 3, "CaptainComission_rumourCapPrison");
}

void CaptainComission_RumourCaptainPrison()
{
	if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
	{
		AddQuestRecord("CaptainComission2", "18");
		AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);				
		pchar.GenQuest.CaptainComission.GetRumour = true;
		SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");	
		SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 2, MakeInt(24 - GetHour()), false);
	}
}

void CaptainComission_GetSecretTimeIsOut(string qName)
{
	ref sld = characterFromId("CapComission_1"); // лесник . удаление ,если опоздал .
	sld.LifeDay = 0;
	AddQuestRecord("CaptainComission2", "20");
	AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);			
	AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
	CloseQuestHeader("CaptainComission2");	
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
}

void CaptainComission_GenerateCaptainInPrison()
{
	
	ref sld = GetCharacter(NPC_GenerateCharacter("CapComission_1" , "mercen_19", "man", "man", 10, sti(pchar.GenQuest.CaptainComission.Nation), -1, true, "quest"));
	SetSPECIAL(sld, 10,9,10,5,10,9,10);
	SetRandSelfSkill(sld, 65, 95);
	SetRandShipSkill(sld, 65, 95); 
	//LAi_SetHP(sld, 100+MOD_SKILL_ENEMY_RATE*30, 100+MOD_SKILL_ENEMY_RATE*30);
	FantomMakeCoolFighter(sld, sti(pchar.rank) + rand(15), 95, 95, LinkRandPhrase("blade_13","blade_14","blade_09"), "pistol2"," grapeshot", 10);	
	sld.name = pchar.GenQuest.CaptainComission.Name;
	sld.lastname = "";
	sld.greeting = "Gr_prison";
	sld.dialog.FileName = "GenQuests_Dialog.c";
	sld.dialog.currentnode = "CaptainComission_370";
	RemoveAllCharacterItems(sld, true); 
	ChangeCharacterAddress(sld, "none", ""); 
}

void CaptainComission_ExitFromTown(string qName)
{
	bQuestDisableMapEnter = true;
	QuestCloseSeaExit();
    DoQuestCheckDelay("CaptainComission_MeetWithCaptain", 1);
}	

void CaptainComission_CapEscapeTimer(string qName)
{
	Log_QuestInfo("Отработало прерывание на бегство капитана");
	Log_Info(StringFromKey("GenQuests_45"));
	ref sld = characterFromId("CapComission_1");
	RemovePassenger(pchar, sld);
	ChangeCharacterAddress(sld, "none", "");
	sld.lifeDay = 0; 
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
	pchar.quest.CaptainComission_TimeIsOver.over = "yes"; // добавил сброс таймера на всяк слуяай.
	pchar.GenQuest.CaptainComission = "CapEscape";
	pchar.GenQuest.CaptainComission.canSpeakBoatswain = true;
	pchar.TownEscape = true;
	pchar.quest.CaptainComission_ExitFromTown.win_condition.l1 	= "EnterToSea";           	
	pchar.quest.CaptainComission_ExitFromTown.function    		= "CaptainComission_ExitFromTown";
	
}

void CaptainComission_GangDialogGetGoods()
{
	ref sld;
	for (int i = 0; i < sti(pchar.GenQuest.CaptainComission.GangNum); i++)
	{
		sld = characterFromID("Gang_" + i);
		LAi_SetActorType(sld); 	
		if (i == 0) LAi_ActorDialog(sld, pchar, "", -1, 0); 
		else LAi_ActorFollow(sld, &characters[GetCharacterIndex("Gang_0")], "", -1);
	}	
	sld = CharacterFromID("CapComission_1");
   // LAi_SetWarriorType(sld); // так лучше . иначе его можно убить. лесник
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
  							 
}

void CaptainComission_CheckCaptainAfterBattle(string qName)
{
	ref sld = characterFromId("CapComission_1");	
	if (LAi_IsDead(sld)) // погиб
	{
		//pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
		AddQuestRecord("CaptainComission2", "22");
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		CloseQuestHeader("CaptainComission2");	
		DeleteAttribute(pchar, "GenQuest.CaptainComission");	
	}
	else // кэп выжил
	{
		//if(GetCharacterEquipByGroup(sld, BLADE_ITEM_TYPE) == "") // снял клинок с трупа. работает через раз..если чесна. лесник.
		    sld = characterFromId("CapComission_1"); // защита от извращенцев :D/ лесник
		    LAi_SetImmortal(sld, true);
			string sEquipItem = GenQuest_GenerateGoodBlade();
			AddItems(sld, sEquipItem, 1);
			EquipCharacterByItem(sld, sEquipItem);
		//}	
		sld.dialog.currentnode = "CaptainComission_387";	
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);	
	}	
}

void CaptainComission_CheckCaptainDied(string qName)
{
	
	if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
	{
		AddQuestRecord("CaptainComission2", "28");
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
		pchar.GenQuest.CaptainComission = "GetGoodsSuccess";
		OfficersReaction("good");
		SetFunctionTimerConditionParam("CaptainComission_SpeakMayorGoods", 0, 0, 1, MakeInt(24 - GetHour()), false);
	}
	else
	{
		AddQuestRecord("CaptainComission2", "27");
		AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.MaxGoodsQty);
		AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
		CloseQuestHeader("CaptainComission2");
		int iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
		if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
		SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
		OfficersReaction("bad");
		ChangeCharacterComplexReputation(pchar,"nobility", -5);
		CaptainComission_GenerateCoastalPatrol();
		pchar.quest.CaptainComission_MapEnter.win_condition.l1 = "MapEnter";
		pchar.quest.CaptainComission_MapEnter.win_condition = "CaptainComission_MapEnterCapDied";  
	}
}
void CaptainComission_NaebalGubera(string qName) // лесник. если обманул губера
{
	OfficersReaction("bad");
	ChangeCharacterComplexReputation(pchar,"nobility", -50);
	AddQuestRecord("CaptainComission2", "52");
}		

void CaptainComission_SpeakMayorGoods(string qName)
{
	pchar.quest.CaptainComission_SpeakMayorGoods.over = "yes";  // лесник. на всяк слуай снял а то хз его знает .
	AddQuestRecord("CaptainComission2", "29");
	AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
	AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
	pchar.GenQuest.CaptainComission = "GetGoods";
	CloseQuestHeader("CaptainComission2"); // лесник . в архив.
	DeleteAttribute(pchar, "GenQuest.CaptainComission"); // лесник. удалил. а то снова хз его знает..
}

void CaptainComission_CapMeetInShore(string qName)
{	
	int DaysIsLeft = GetQuestPastDayParam("GenQuest.CaptainComission.DeleiveCapShore");
	
	ref sld = characterFromId("CapComission_1");	
	RemovePassenger(pchar, sld);	
	PlaceCharacter(sld, "goto", "random_must_be_near");
	if(DaysIsLeft <= sti(pchar.GenQuest.CaptainComission.iDay))
	{
		LAi_SetActorTypeNoGroup(sld);
		CaptainComission_GenerateGangInShore();
	}
	else
	{
		sld.dialog.currentnode = "CaptainComission_392";	
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);	
        pchar.GenQuest.Hunter2Pause = true;		// ОЗГи на паузу . лесник
		chrDisableReloadToLocation = true;// закрыть локация лесник
	}				
}

void CaptainComission_CaptainDiedDuel(string qName)
{
	if(CheckAttribute(pchar, "GenQuest.CaptainComission.Duel"))
	{
		pchar.quest.CaptainComission_Capitan_Cdox.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
		AddQuestRecord("CaptainComission2", "54");
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);	
	}
	else
	{
		AddQuestRecord("CaptainComission2", "31");
		AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat"));
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
	}	
	CloseQuestHeader("CaptainComission2");
	ChangeCharacterComplexReputation(pchar,"nobility", -8);
	OfficersReaction("bad");
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
}

void CaptainComission_BattleInShore(string qName)
{
	ref sld;
	string sTemp = "Gang_";
	string sGroup = "GangGroup_0";			
	LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
	int iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("CapComission_1");
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	//LAi_SetWarriorType(sld); // лесник. лишнее. иначе можно убить во время боя. 
	pchar.quest.CaptainComission_Capitan_Cdox.win_condition.l1 = "NPC_Death"; // лесник . добавил событие на смерть капитана.
	pchar.quest.CaptainComission_Capitan_Cdox.win_condition.l1.character = "CapComission_1"; // оставить ,если после боя сам завалит кэпа
	pchar.quest.CaptainComission_Capitan_Cdox.win_condition = "CaptainComission_Capitan_Cdox";	// в след. раз будет думать:D																																					  
	
	for(int i = 0; i < iTemp; i++)
	{
		sld = CharacterFromID(sTemp + i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, sGroup);
		LAi_SetImmortal(sld, false);
	}			
	LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
	LAi_group_SetCheckFunction(sGroup, "CaptainComission_GangDied");
	LAi_SetFightMode(pchar, true);
}

bool CaptainComission_CheckAllPassengersHired()
{
    int iQty = GetPassengersQuantity(pchar);
    int i = 0;
	int n = 0;
	int idx;
	ref ch;
			
 	while (i < iQty)
	{
		i++;
		idx = GetPassenger(pchar, n);
		if (idx == -1) break;
		ch = GetCharacter(idx);
		if(CheckAttribute(ch, "CaptainComission")) return true;
		n++;
	}
    for (i=0; i<COMPANION_MAX; i++)
	{
		idx = GetCompanionIndex(pchar, i);
		if (idx != -1)
		{
            ch = GetCharacter(idx);
			if(CheckAttribute(ch, "CaptainComission")) return true;
		}
	}
	return false;
} 

// ветка №3
void CaptainComission_GenerateRumourCaptainDeath()
{
	string sShipType = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"));
	AddSimpleRumourCity(LinkRandPhrase(StringFromKey("GenQuests_46", GetAddress_Form(pchar), sShipType, pchar.GenQuest.CaptainComission.Name),
		StringFromKey("GenQuests_47", GetAddress_Form(pchar), sShipType, pchar.GenQuest.CaptainComission.Name),
		RandPhraseSimple(StringFromKey("GenQuests_48", GetAddress_Form(pchar)),
		StringFromKey("GenQuests_49", pchar.GenQuest.CaptainComission.Name, sShipType, GetAddress_Form(pchar)))), 
	pchar.GenQuest.CaptainComission.City, 5, 3, "CaptainComission_rumourCapDeath");
}

void CaptainComission_RumourCaptainDeath()
{
	if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
	{
		AddQuestRecord("CaptainComission2", "37");
		AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
		AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // belamour gen
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);		
		pchar.GenQuest.CaptainComission.GetRumour = true;
		SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
	}
}

void CaptainComission_GenerateCanoneer(string qName)
{
	int Rank = sti(pchar.rank) + 3 + rand(10);
	ref sld = GetCharacter(NPC_GenerateCharacter("CapComission_Canoneer", "officer_15", "man", "man", 10, sti(pchar.GenQuest.CaptainComission.Nation), -1, true, "quest"));
	FantomMakeCoolFighter(sld, Rank, 100, 90, "blade_09", "pistol3", "bullet", 150);
	sld.name = GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM);
	sld.lastname = "";
	sld.dialog.FileName = "GenQuests_Dialog.c";
	sld.dialog.currentnode = "CaptainComission_Canoneer";
	sld.greeting = "cit_quest";
	sld.CityType = "citizen";
	sld.City = pchar.GenQuest.CaptainComission.City;
	LAi_SetImmortal(sld, true);	// До поры нельзя убить
	string sLoc = pchar.GenQuest.CaptainComission.City + "_tavern"; 
	ref pLoc = &locations[FindLocation(sLoc)];
	if (!LAi_CheckLocatorFree("sit", "sit_front2")) FreeSitLocator(sLoc, "sit_front2");
	FreeSitLocator(sLoc, "sit_base2");
	ChangeCharacterAddressGroup(sld, sLoc, "sit", "sit_base2");
	LAi_SetSitType(sld);
}

// канонир ждёт деньги до конца суток .. если бабла нет, то закрываем квест с записью в СЖ
void CaptainComission_CanoneerWaitMoney(string qName)
{
	ref sld = characterFromId("CapComission_Canoneer");
	ChangeCharacterAddress(sld, "none", ""); 
	sld.LifeDay = 0;
	ChangeOfficersLoyality("bad_all", 1);
	AddQuestRecord("CaptainComission2", "42");
	AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
	AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
	AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
	CloseQuestHeader("CaptainComission2");
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
}

void CaptainComission_MeetCanoneerInShoreTimer(string qName)
{
	SetFunctionLocationCondition("CaptainComission_MeetCanoneerInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false);
}

void CaptainComission_MeetCanoneerInShore(string qName)
{
	pchar.quest.CaptainComission_TimeIsOver.over = "yes";
	pchar.quest.CaptainComission_CanoneerWaitMoney.over = "yes";
	if(pchar.Location == pchar.location.from_sea) 
	{
		chrDisableReloadToLocation = true;	
		CaptainComission_GenerateGangInShore();	
		ref sld = characterFromId("CapComission_Canoneer");
		LAi_SetImmortal(sld, true);
		LAi_CharacterEnableDialog(sld);
		sld.dialog.currentnode = "CaptainComission_350";	
		PlaceCharacter(sld, "goto", "random_must_be_near");
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);	
	}
	else // нефик тупить
	{ 
		sld = CharacterFromID("CapComission_Canoneer");
		sld.LifeDay = 0;
		AddQuestRecord("CaptainComission2", "44");
		AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
		AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //лесник - на тип корабля.
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
		CloseQuestHeader("CaptainComission2");
		ChangeOfficersLoyality("bad_all", 1);
		DeleteAttribute(pchar, "GenQuest.CaptainComission");		
	}	
}

void CaptainComission_NoGangDialog(string qName)
{
	ref sld;
	int iTemp;
	float locx, locy, locz;
	string sTemp;
	
	GetCharacterPos(pchar, &locx, &locy, &locz);
	sTemp = LAi_FindNearestLocator("reload", locx, locy, locz);
	sld = characterFromId("CapComission_Canoneer");
	LAi_SetActorType(sld); 
	LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);			
	sld.LifeDay = 0;
	for(int i = 0; i < sti(pchar.GenQuest.CaptainComission.GangNum); i++)
	{
		iTemp = GetCharacterIndex("Gang_" + i);
		if (iTemp != -1)
		{
			sld = characterFromId("Gang_" + i);
			LAi_SetActorType(sld); 
			LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "", "", -1.0);			
			sld.lifeDay = 0;
		}
	}
	AddQuestRecord("CaptainComission2", "45");
	AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
	AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
	CloseQuestHeader("CaptainComission2");	
    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	// лесник - открыть оружие снова.
	DeleteAttribute(pchar, "GenQuest.CaptainComission");
}

void CaptainComission_CheckGangAfterBattle(string qName)
{
	ref sld;
	int iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
	if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;	
	SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз	
	//if (GetCharacterIndex("CapComission_Canoneer") > 0) // канонир остался жив
	sld = CharacterFromId("CapComission_Canoneer"); // лесник . изменил условие . прежнее не работало при смерти канонира.
	 if (!LAi_IsDead(sld))
	{
		Log_Info(StringFromKey("GenQuests_50")); // лесник добавил лог
		sld = CharacterFromId("CapComission_Canoneer");
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, false);
		sld.dialog.currentnode = "CaptainComission_365";	
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);			
		AddQuestRecord("CaptainComission2", "47");
		AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		AddQuestUserData("CaptainComission2", "sSum", iGoods);
		AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
		AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ACC));
		AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity));
		SetFunctionLocationCondition("CaptainComission_DeleiveCanoneer", pchar.GenQuest.CaptainComission.CanoneerCity + "_town", false);
	}
	else // помер .. вот бедолага
	{
		Log_Info(StringFromKey("GenQuests_50")); // лесник добавил лог
		AddQuestRecord("CaptainComission2", "46");
		AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
		AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen")));
		AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
		AddQuestUserData("CaptainComission2", "sSum", iGoods);
		AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
		CloseQuestHeader("CaptainComission2");
		OfficersReaction("bad");
		ChangeCharacterComplexReputation(pchar,"nobility", -5);
		DeleteAttribute(pchar, "GenQuest.CaptainComission"); // лесник . удалил квест.
	}
	CaptainComission_EnterToSeaAfterShoreBattle();
	pchar.quest.CaptainComission_MapEnterAfterShoreBattle.win_condition.l1 = "MapEnter";
    pchar.quest.CaptainComission_MapEnterAfterShoreBattle = "CaptainComission_MapEnterAfterShoreBattle";
}

void CaptainComission_DeleiveCanoneer(string qName)
{
	ref sld = characterFromId("CapComission_Canoneer");	
	RemovePassenger(pchar, sld);
	sld.dialog.currentnode = "CaptainComission_366";		
	PlaceCharacter(sld, "goto", pchar.location);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);	
}

void CaptainComission_EnterToSeaAfterShoreBattle()
{
	ref sld;
	Group_DeleteGroup("Pirate_Guards");	
	Group_FindOrCreateGroup("Pirate_Guards");
    Group_SetType("Pirate_Guards", "pirate");
	for (int i = 1; i <= 3; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter("Pirate_Captain0" + i, "mercen_"+(rand(14)+14), "man", "man", 5, PIRATE, 3, true, "quest")); 
		FantomMakeCoolFighter(sld, makeint(pchar.rank) + rand(10) + 5, 90, 50, "blade_06", "pistol3","grapeshot", 80);
		SetFantomParam(sld);
		SelectCoastalGuardShip(sld);
		sld.AlwaysEnemy = true;
		sld.DontRansackCaptain = true;
		sld.AlwaysSandbankManeuver = true;
		Group_AddCharacter("Pirate_Guards", sld.id);
		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
    }
	Group_SetGroupCommander("Pirate_Guards", "Pirate_Captain01");
	Group_SetPursuitGroup("Pirate_Guards", PLAYER_GROUP);
	Group_SetAddress("Pirate_Guards", Islands[GetCharacterCurrentIsland(Pchar)].id, "", "");
	Group_SetTaskAttack("Pirate_Guards", PLAYER_GROUP);
	Group_LockTask("Pirate_Guards");
}
//=====================================================================================================================================
// <-- ГЕНЕРАТОР  "ПОРУЧЕНИЕ КАПИТАНА - ОПЕРАЦИЯ 'ГАЛЕОН'"
//=====================================================================================================================================
//=====================================================================================================================================
// Ugeen. ГЕНЕРАТОР  "КАТОРЖАНЕ"
//=====================================================================================================================================
void Convict_LocExit(string qName)
{
	ref sld;
	int i;
	if(pchar.GenQuest.Convict == "close")
	{
		for(i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
		{
			sld = CharacterFromID("Convict_" + i);
			sld.LifeDay = 0;
		}
		LAi_group_Delete("ConvictGroup");
		DeleteAttribute(pchar, "GenQuest.Convict");
		return;
	}
	if(pchar.GenQuest.Convict == "fight")
	{
		ChangeCharacterComplexReputation(pchar,"nobility", -2);
		OfficersReaction("bad");		
		DeleteAttribute(pchar, "GenQuest.Convict");
		return;
	}
	if(pchar.GenQuest.Convict == "ToShore" || pchar.GenQuest.Convict == "GetShip" || pchar.GenQuest.Convict == "ToMayak")
	{
		for(i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
		{
			sld = CharacterFromID("Convict_" + i);
			ChangeCharacterAddress(sld, "none", ""); 
		}
	}
	if(pchar.GenQuest.Convict == "FightInShore" || pchar.GenQuest.Convict == "ShoreFight" || pchar.GenQuest.Convict == "MayakFight")
	{
		if(pchar.GenQuest.Convict == "FightInShore")
		{
			AddQuestRecord("Convict", "6");
			AddQuestUserData("Convict", "sSex", GetSexPhrase(StringFromKey("GenQuests_72"),StringFromKey("GenQuests_73")));
			AddQuestUserData("Convict", "sSex1", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString("Shore" + pchar.GenQuest.Convict.ShoreLocation + "Gen")); // belamour gen
		}
		if(pchar.GenQuest.Convict == "ShoreFight")
		{
			AddQuestRecord("Convict", "9");
			AddQuestUserData("Convict", "sSex", GetSexPhrase(StringFromKey("GenQuests_64"),StringFromKey("GenQuests_65")));
		}	
		if(pchar.GenQuest.Convict == "MayakFight")
		{
			AddQuestRecord("Convict", "13");
			AddQuestUserData("Convict", "sSex", GetSexPhrase(StringFromKey("GenQuests_72"),StringFromKey("GenQuests_73")));
			AddQuestUserData("Convict", "sSex1", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat")); // belamour gen
		}	
		
		CloseQuestHeader("Convict");
		ChangeCharacterComplexReputation(pchar,"nobility", 2);
		OfficersReaction("bad");		
		DeleteAttribute(pchar, "GenQuest.Convict");	
	}
}

void Convict_GetMineType()
{
	pchar.GenQuest.Convict.MineType = hrand(2) + 1; // hrand auto tagged
}

void Convict_MeetInShore(string qName)
{
	ref sld;
	int i;
	pchar.quest.Convict_SetTimer.over = "yes";
	pchar.quest.Convict_MapEnter.over = "yes";
	
	DeleteAttribute(&Locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)], "DisableEncounters");
		
	if(pchar.Location == pchar.location.from_sea) // пришёл с моря
	{
		chrDisableReloadToLocation = true;
		bDisableFastReload = true;	
		for(i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
		{
			sld = CharacterFromID("Convict_" + i);
			PlaceCharacter(sld, "goto", pchar.location);
			if(i == 0)
			{
				LAi_CharacterEnableDialog(sld);
				if(pchar.GenQuest.Convict == "GetShip")
				{
					sld.dialog.currentnode = "Convict_15";	
				}
				if(pchar.GenQuest.Convict == "ToShore")	
				{
					sld.dialog.currentnode = "Convict_16";	
				}
				if(pchar.GenQuest.Convict == "ToMayak")	
				{
					sld.dialog.currentnode = "Convict_16";	
				}
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);					
			}
		}	
	}
	else // пришёл с суши --> закрываем квест
	{
		AddQuestRecord("Convict", "3");
		AddQuestUserData("Convict", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
		CloseQuestHeader("Convict");
		for(i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
		{
			sld = CharacterFromID("Convict_" + i);
			sld.LifeDay = 0;
		}
		LAi_group_Delete("ConvictGroup");
		DeleteAttribute(pchar, "GenQuest.Convict");	
	}
}

void Convict_SetTimer(string qName)
{
	pchar.quest.Convict_ToShore.over = "yes";
	pchar.quest.Convict_MapEnter.over = "yes";
	AddQuestRecord("Convict", "3");
	AddQuestUserData("Convict", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
	CloseQuestHeader("Convict");
	for(int i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
	{
		sld = CharacterFromID("Convict_" + i);
		sld.LifeDay = 0;
	}
	LAi_group_Delete("ConvictGroup");
	DeleteAttribute(pchar, "GenQuest.Convict");
}

void Convict_SetTimerMeet(string qName)
{
	pchar.quest.Convict_ToShore.win_condition.l1 = "Location";
	pchar.quest.Convict_ToShore.win_condition.l1.location = pchar.GenQuest.Convict.ShoreLocation;
	pchar.quest.Convict_ToShore.function = "Convict_MeetInShore";
		
	SetFunctionTimerConditionParam("Convict_SetTimer", 0, 0, 0, 14, false);
//	pchar.quest.Convict_MapEnter.win_condition.l1 = "MapEnter";
//       pchar.quest.Convict_MapEnter.function = "Convict_MapEnter";
}

void Convict_MapEnter(string qName)
{
	pchar.quest.Convict_SetTimer.over = "yes";
	pchar.quest.Convict_ToShore.over = "yes";
	AddQuestRecord("Convict", "3");
	AddQuestUserData("Convict", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
	CloseQuestHeader("Convict");
	for(int i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
	{
		sld = CharacterFromID("Convict_" + i);
		sld.LifeDay = 0;
	}
	LAi_group_Delete("ConvictGroup");
	DeleteAttribute(pchar, "GenQuest.Convict");
}

void Convict_DialogDisable()
{
	ref sld;
	for(int i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
	{
		sld = CharacterFromID("Convict_" + i);
		LAi_CharacterDisableDialog(sld);
		LAi_SetStayType(sld);
	}
}

int Convict_GetShipPrice(int iShipType)
{
	ref sld, chr;
	int price = sti(GetBaseShipParamFromType(iShipType, "price"));
	sld = CharacterFromID("Convict_0");
	if (CheckAttribute(sld, "city")) 
	{
		string sCity = sld.city; 
		if(CheckCharacterID(sld, sCity + "_shipyarder"))
		{
			chr = CharacterFromID(sCity + "_shipyarder");
			price = GetShipBuyPrice(iShipType, chr);
		}
	}	
	return price;
}

void Convict_OnMayak(string qName)
{
	ref sld;
	if(pchar.location == pchar.location.from_sea) // пришёл с моря
	{
		pchar.quest.Convict_OnMayak.over = "yes"; // затираем прерывание
		DeleteAttribute(&Locations[FindLocation(pchar.GenQuest.Convict.Mayak)], "DisableEncounters");
		
		for(int i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
		{
			sld = CharacterFromID("Convict_" + i);			
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto" + (i + 1));
			LAi_SetActorTypeNoGroup(sld);			
			if(i == 0)
			{
				RemovePassenger(pchar, sld);
				LAi_CharacterEnableDialog(sld);
				sld.dialog.filename = "GenQuests_Dialog.c";
				sld.dialog.currentnode = "Convict_17";				
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				LAi_ActorFollow(sld, pchar, "", -1);
			}		
		}	
	}
}

bool Convict_CheckShipType(int iShipType)
{
	int cn;
	ref sld;
	for (int i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn != -1)
		{
			sld = &characters[cn];
			if (RealShips[sti(sld.Ship.Type)].basetype == iShipType)
			{
				pchar.GenQuest.Convict.CharShipId = sld.id;	
				pchar.GenQuest.Convict.ShipPrice = Convict_GetShipPrice(iShipType);
				return true;
			}
		}
	}
	return false;
}

void Convict_SetConvictToShip()
{
	ref sld, chr;
	aref arTo, arFrom;
	if(CheckAttribute(pchar,"GenQuest.Convict.CharShipId"))
	{
		sld = CharacterFromID("Convict_0");			
		chr = CharacterFromID(pchar.GenQuest.Convict.CharShipId);			
		
		DeleteAttribute(sld,"ship");
		sld.ship = "";
					 
		makearef(arTo, sld.ship);
		makearef(arFrom, chr.Ship);
		CopyAttributes(arTo, arFrom);

		SeaAI_SetOfficer2ShipAfterAbordage(sld, chr); 			
		DeleteAttribute(chr,"ship"); // трем корабль
		chr.ship.type = SHIP_NOTUSED;
		
		RemoveCharacterCompanion(pchar, chr);
		AddPassenger(pchar, chr, false);
		
		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
		
		DeleteAttribute(pchar,"GenQuest.Convict.CharShipId");
		
		pchar.GenQuest.Convict = "close";
		SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
	}	
}
//=====================================================================================================================================
// <--. ГЕНЕРАТОР  "КАТОРЖАНЕ"
//=====================================================================================================================================

//=====================================================================================================================================
// Ugeen. ГЕНЕРАТОР "ПОТЕРПЕВШИЕ КОРАБЛЕКРУШЕНИЕ" -->
//=====================================================================================================================================
void ShipWreck_LocationExit(string _quest)
{
	int index, i;
	ref sld;
	if(pchar.GenQuest.ShipWreck == "SailorsSaved")
	{
		for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
		{
			index = GetCharacterIndex("ShipWreck_" + i);		
			if(index != -1)
			{
				sld = CharacterFromID("ShipWreck_" + i);
				ChangeCharacterAddress(sld, "None", ""); 
			}
		}			
	}
	else
	{
		for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
		{
			index = GetCharacterIndex("ShipWreck_" + i);		
			if(index != -1)
			{
				Characters[index].LifeDay = 0;
			}
		}	
		DeleteAttribute(pchar, "GenQuest.ShipWreck");
		if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny")) DeleteAttribute(pchar,"GenQuest.ShipWreck.Mutiny"));
	}	
}

string ShipWreck_GetStringQty(int Qty)
{
	string strQty;
	switch(Qty)
	{
		case 3:    	strQty = StringFromKey("GenQuests_51"); break;
		case 4:    	strQty = StringFromKey("GenQuests_52"); break;
		case 5: 	strQty = StringFromKey("GenQuests_53"); break;
		case 6: 	strQty = StringFromKey("GenQuests_54");	break;
		case 7: 	strQty = StringFromKey("GenQuests_55");	break;
		case 8: 	strQty = StringFromKey("GenQuests_56");	break;
		case 9: 	strQty = StringFromKey("GenQuests_57");	break;
		case 10:	strQty = StringFromKey("GenQuests_58");	break;		
	}
	return strQty;
}

void ShipWreck_SetCapToMap()
{
	int temp;
	String group = "ShipWreck_SeaGroup";
	ref character = GetCharacter(NPC_GenerateCharacter("ShipWreck_BadPirate", "", "man", "man", sti(pchar.rank) + 5, PIRATE, -1, true, "hunter"));
		
	character.name = pchar.GenQuest.ShipWreck.BadName;
	character.lastname = "";
	
	character.Ship.Type = GenerateShipExt(sti(pchar.GenQuest.ShipWreck.StartShipType), true, character);
	character.Ship.Name = pchar.GenQuest.ShipWreck.ShipTypeName;
	SetCaptanModelByEncType(character, "pirate");
    SetBaseShipData(character);
    SetCrewQuantityFull(character);
    Fantom_SetCannons(character, "pirate");
    Fantom_SetBalls(character, "pirate");
	
	character.Ship.Mode = "pirate";	

	DeleteAttribute(character, "SinkTenPercent");
	DeleteAttribute(character, "SaveItemsForDead");
	DeleteAttribute(character, "DontClearDead");
	DeleteAttribute(character, "AboardToFinalDeck");
	DeleteAttribute(character, "SinkTenPercent");
	
	character.AlwaysSandbankManeuver = true;
	character.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	character.DontRansackCaptain = true; //не сдаваться
	
	SetAllPerksToChar(character, false);
	
	Group_FindOrCreateGroup(group);
	Group_SetTaskAttackInMap(group, PLAYER_GROUP);
	Group_LockTask(group);
	Group_AddCharacter(group, character.id);
	Group_SetGroupCommander(group, character.id);
	SetRandGeraldSail(character, PIRATE);
	
	character.fromCity = SelectAnyColony(""); // Колония, из бухты которой выйдет
	character.fromShore = GetIslandRandomShoreId(GetArealByCityName(character.fromCity));
	character.toCity = SelectAnyColony(character.fromCity); // Колония, в бухту которой придёт
	character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
	
	character.mapEnc.type = "trade";
	character.mapEnc.worldMapShip = "quest_ship";
	character.mapEnc.Name = LowerFirst(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name)) + " '" + pchar.GenQuest.ShipWreck.ShipTypeName + "'";
	
	Map_CreateTrader(character.fromShore, character.toShore, "ShipWreck_BadPirate", GetMaxDaysFromIsland2Island(GetArealByCityName(character.toCity), GetArealByCityName(character.fromCity)) + 15);
	
	temp = GetCharacterFreeSpace(character, GOOD_SLAVES); // Сколько влезет рабов
	AddCharacterGoodsSimple(character, GOOD_SLAVES, makeint(temp / 2 + hRand(temp / 2)) - 1); // hrand auto tagged
	
	pchar.quest.ShipWreck_ShipSink.win_condition.l1 = "Character_sink";
	pchar.quest.ShipWreck_ShipSink.win_condition.l1.character = "ShipWreck_BadPirate";
	pchar.quest.ShipWreck_ShipSink.function = "ShipWreck_ShipSink";
	
	Log_TestInfo("Кораблекрушенцы: кэп вышел из " + character.fromCity + " и направился в: " + character.toShore);
}

void ShipWreck_DeliveToCity(string qName)
{
	ref sld;
	if(pchar.location == pchar.location.from_sea && reload_cur_island_index > -1)
	{
		chrDisableReloadToLocation = true;
		Log_Info(StringFromKey("GenQuests_59")); // belamour gen
		for(int i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
		{
			sld = CharacterFromID("ShipWreck_" + i);
			PlaceCharacter(sld, "goto", "random_must_be_near");
			if(i == 0)
			{
				if(CheckAttribute(pchar,"GenQuest.ShipWreck.Crazy")) // разговор с психом
				{
					sld.dialog.currentnode = "ShipWreck_34";	
				}
				else
				{
					RemovePassenger(pchar, sld);
					if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny") || pchar.GenQuest.ShipWreck == "SailorsSaved") // belamour gen: в разговоре с пиратами на необитайке атрибут
					{                                                                                                   // GenQuest.ShipWreck.Mutiny удаляется. Оставлю, конечно... Но
						sld.dialog.currentnode = "ShipWreck_48";	                                                    // из-за этого нода та, что на берегу и блокировка локации
					}
					// belamour gen поэтому else тут удалю
					if(pchar.GenQuest.ShipWreck.variant == "1")
					{
						sld.dialog.currentnode = "ShipWreck_30";	
					}	
					if(pchar.GenQuest.ShipWreck.variant == "2")
					{
						sld.dialog.currentnode = "ShipWreck_32";	
					}						
						
				}	
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		}
	}
	else
	{
		SetFunctionExitFromLocationCondition("ShipWreck_ExitFromTown", pchar.location, false);				
	}	
}

void ShipWreck_ExitFromTown(string _quest)
{
	pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
	pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
	pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";						
}

void ShipWreck_GoOut()
{
	ref sld;	
	float locx, locy, locz;
	
	GetCharacterPos(pchar, &locx, &locy, &locz);
	for(int i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
	{
		sld = CharacterFromID("ShipWreck_" + i);
		sld.LifeDay = 0;
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", -1.0);		
	}
	DeleteAttribute(pchar,"GenQuest.ShipWreck");
	DoQuestCheckDelay("OpenTheDoors", 1.0);
}

void ShipWreck_AfterBattle(string qName)
{
	int index;
	for(int i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
	{
		index = GetCharacterIndex("ShipWreck_" + i);		
		if(index != -1)
		{
			Characters[index].LifeDay = 0;
		}
	}	
	// --> belamour gen закрыть запись 
	if(pchar.GenQuest.ShipWreck == "SailorsOnShoreFight")
	{
		pchar.quest.ShipWreck_SaveSailors.over = "yes"; // belamour gen снять таймер 30 дней
		AddQuestRecord("ShipWrecked", "8_1");
		CloseQuestHeader("ShipWrecked");
	}
	// <-- belamour gen
	if(CheckAttribute(pchar,"GenQuest.ShipWreck.Crazy"))
	{
		AddQuestRecord("ShipWrecked", "8");
		CloseQuestHeader("ShipWrecked");	
	}
	DeleteAttribute(pchar, "GenQuest.ShipWreck");
}

void ShipWreck_DialogDisable()
{
	ref sld;
	for(int i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
	{
		sld = CharacterFromID("ShipWreck_" + i);
		LAi_CharacterDisableDialog(sld);
	}
}

void ShipWreck_SaveSailors(string qName)
{
	pchar.quest.ShipWreck_MeetInShore.over = "yes";
	ChangeCharacterComplexReputation(pchar,"nobility", -5);
	AddQuestRecord("ShipWrecked", "12");
	CloseQuestHeader("ShipWrecked");
	DeleteAttribute(pchar, "GenQuest.ShipWreck");	
}

void ShipWreck_MeetInShore(string qName)
{
	ref sld;
	string sLocGroup;
	
	for(int i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
	{
		sld = CharacterFromID("ShipWreck_" + i);
		if(GetFreeCrewQuantity(pchar) < sti(pchar.GenQuest.ShipWreck.Qty)) // нет места 
		{
			ChangeCharacterAddress(sld, "None", "");
		}
		else // ура, место есть
		{
			pchar.quest.ShipWreck_MeetInShore.over = "yes"; // снимаем прерывание на повторный заход в бухту
			if(LAi_GetLocatorNum("encdetector") > 0) 	sLocGroup = "encdetector";
			else										sLocGroup = "goto"; 
			PlaceCharacter(sld, sLocGroup, "random_must_be"); // belamour gen: pchar.GenQuest.ShipWreck.Shore даёт урезанный состав.  Или по задумке с голоду померли???
			if(i == 0)
			{
				sld.dialog.currentnode = "ShipWreck_44";
				LAi_ActorDialog(sld, pchar, "", 5.0, 0.0);
			}
			else
			{
				LAi_ActorFollow(sld, pchar, "", 5.0);
			}
		}
	}	
}

void ShipWreck_afterCabinFight(string qName)
{
	ref sld;
	float locx,locy,locz;

	sld = CharacterFromID("ShipWreck_0");
	sld.dialog.currentnode = "ShipWreck_53";
	LAi_SetStayType(sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
	LAi_SetActorType(pchar);
	LAi_SetActorType(sld);
	SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0.0, 0.0); // mitrokosta belamour gen
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1); // это ему больше надо )))
	pchar.quest.prosralisrok.over = "yes"; // лесник сброс таймера. 
}

void ShipWreck_SetShipNew()
{
	ref sld, chr;
	aref arTo, arFrom;
	string sText; // belamour

	sld = CharacterFromID("ShipWreck_0");
	chr = CharacterFromID("ShipWreck_BadPirate");			
		
	DeleteAttribute(sld, "ship");
	sld.ship = "";
					 
	makearef(arTo, sld.ship);
	makearef(arFrom, chr.ship);
	CopyAttributes(arTo, arFrom);

	SeaAI_SetOfficer2ShipAfterAbordage(sld, chr); 			

	//DeleteAttribute(chr, "ship"); // трем корабль
	//chr.ship = "";
	//chr.ship.type = SHIP_NOTUSED;
	chr.LifeDay = 0;
	
	RemovePassenger(pchar, sld);
	sld.AlwaysFriend = true;
	sld.Abordage.Enable = false; //нельзя брать на абордаж
	SetCrewQuantity(sld, 15 + rand(10));
	
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
	pchar.GenQuest.ShipWreck = "close";
	pchar.quest.ShipWreck_MapEnter.win_condition.l1 = "MapEnter";
	pchar.quest.ShipWreck_MapEnter.function = "ShipWreck_LocationExit"; 			

	AddQuestRecord("ShipWrecked", "18");
	AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
	AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Acc"))); // belamour gen
	AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
	AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);																															   
	CloseQuestHeader("ShipWrecked");
}

void ShipWreck_ShipSink(string qName)
{
	ref sld;
	for(int i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
	{
		sld = CharacterFromID("ShipWreck_" + i);
		if(i == 0) 
		{
			RemovePassenger(pchar, sld);
		}
		sld.LifeDay = 0;
	}
	pchar.quest.prosralisrok.over = "yes"; // лесник сброс таймера.
	AddQuestRecord("ShipWrecked", "19");
	AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name)));
	AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
	AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
	// --> belamour gen : нужно разделить, иначе получается бригантина утонул, а с ним и весь товар
	string sText; 
	if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
	{
		AddQuestUserData("ShipWrecked", "sText", StringFromKey("GenQuests_74"));
	}
	else
	{
		AddQuestUserData("ShipWrecked", "sText", StringFromKey("GenQuests_75"));
	}
	// <-- belamour
	CloseQuestHeader("ShipWrecked");
	DeleteAttribute(pchar, "GenQuest.ShipWreck");	
}
//=====================================================================================================================================
// <-- ГЕНЕРАТОР "ПОТЕРПЕВШИЕ КОРАБЛЕКРУШЕНИЕ" 
//=====================================================================================================================================
//=====================================================================================================================================
// Ugeen. ГЕНЕРАТОР "СИТУАЦИИ В ТРЮМЕ" -->
//=====================================================================================================================================
void Hold_GenQuest_Init(ref chref)
{
	ref rColony;
	string sColony;

	if(!CheckAttribute(chref,"EncType")) chref.EncType = "trade";
	
	switch(chref.EncType)
	{
		case "trade":
			chref.Hold_GenQuest.variant = rand(2);  
		break;
		case "war":
			chref.Hold_GenQuest.variant = 0;
		break;
		case "pirate":
			chref.Hold_GenQuest.variant = rand(1); 
		break;
	}

    TEV.TempTag = chref.id + chref.name; // Проверяется в GetQuestNationsCity

	switch(sti(chref.Hold_GenQuest.variant))	
	{
		case 0: // "наводка"
			chref.Hold_GenQuest.Goods = Hold_GenQuest_GetVictimShipGoods();
			chref.Hold_GenQuest.Nation = FindEnemyNation2NationWithoutPirates(GetBaseHeroNation()); 
			if(sti(chref.Hold_GenQuest.Nation) < 0) 
			{
				chref.Hold_GenQuest.Nation = rand(NON_PIRATES);
			}	
			chref.Hold_GenQuest.Name = GenerateRandomName_Generator(sti(chref.Hold_GenQuest.Nation), "man");
			
			sColony = Sea_FindNearColony();
			if (sColony != "none") 
			{
				chref.Hold_GenQuest.ToCity = FindAlliedColonyForNationExceptColony(sColony);
			}
			else
			{
				chref.Hold_GenQuest.ToCity = GetQuestNationsCity(sti(chref.Hold_GenQuest.Nation));
			}	
			chref.Hold_GenQuest.FromCity = FindAlliedColonyForNationExceptColony(chref.Hold_GenQuest.ToCity);
			chref.Hold_GenQuest.ShipName = GenerateRandomNameToShip(sti(chref.Hold_GenQuest.Nation));
			if(rand(1) == 0) 	chref.Hold_GenQuest.City = chref.Hold_GenQuest.ToCity;
			else 				chref.Hold_GenQuest.City = chref.Hold_GenQuest.FromCity;
		break;

		case 1: // "подельник"
			chref.Hold_GenQuest.Nation = rand(NON_PIRATES);
			chref.Hold_GenQuest.City = GetQuestNationsCity(sti(chref.Hold_GenQuest.Nation));
			chref.Hold_GenQuest.Name = GenerateRandomName_Generator(sti(chref.Hold_GenQuest.Nation), "man");
			chref.Hold_GenQuest.PirateName = "l" + rand(GetNamesCount(NAMETYPE_VIP) - 1);
		break;
		
		case 2: // "выкуп"			
			chref.Hold_GenQuest.City = GetQuestNationsCity(rand(NON_PIRATES));							
			rColony = GetColonyByIndex(FindColony(chref.Hold_GenQuest.City));
			chref.Hold_GenQuest.Nation = sti(rColony.nation);
			chref.Hold_GenQuest.Name = GenerateRandomName_Generator(sti(chref.Hold_GenQuest.Nation), "man");
		break;			
	}
}

int Hold_GenQuest_GetVictimShipGoods()
{
	int iGoodIdx;
	switch (rand(10))
    {
        case 0 :
            iGoodIdx = GOOD_TOBACCO;
        break;
        case 1 :
            iGoodIdx = GOOD_COFFEE;
        break;
        case 2 :
            iGoodIdx = GOOD_MAHOGANY;
        break;						
        case 3 :
            iGoodIdx = GOOD_FOOD;
        break;
        case 4 :
            iGoodIdx = GOOD_EBONY;
        break;				
        case 5 :
            iGoodIdx = GOOD_RUM;
        break;
        case 6 :
            iGoodIdx = GOOD_WEAPON;
        break;
        case 7 :
            iGoodIdx = GOOD_WINE;
        break;
        case 8 :
            iGoodIdx = GOOD_CHOCOLATE;
        break;				
        case 9 :
            iGoodIdx = GOOD_CINNAMON;
        break;
        case 10 :
            iGoodIdx = GOOD_LEATHER;
        break;		
    }
	return iGoodIdx;
}

void Hold_GenQuest_SetMerchant_pre(string qName)
{
	SetFunctionLocationCondition("Hold_GenQuest_SetMerchant", pchar.GenQuest.Hold_GenQuest.Island, false);
}

void Hold_GenQuest_SetMerchant(string qName)
{
	ref chref, sld;
	pchar.quest.Hold_GenQuest_MerchantOver.over = "yes";
	
	int iChar = NPC_GenerateCharacter("Hold_QuestMerchant", "off_spa_2", "man", "man", 5, sti(pchar.GenQuest.Hold_GenQuest.Nation), 3, true, "citizen");
	makeref(chref, Characters[iChar]);
	int iRank = SetShipTypeMerchant(chref); 
	chref.Ship.Name = pchar.GenQuest.Hold_GenQuest.ShipName;
	SetFantomParamHunter(chref); //крутые парни
	
	SetCaptanModelByEncType(chref, "trade");	
	int iSpace = GetCharacterFreeSpace(chref, sti(pchar.GenQuest.Hold_GenQuest.Goods));
    
    float del = makefloat(7 - iRank + rand(1))/10; 
    if (del > 1.0 ) del = 1;
    Log_TestInfo("goods load = "+iSpace+"/"+makeint(iSpace*del));
    iSpace = makeint(iSpace * del); // чтоб не так жирно было
    Fantom_SetCharacterGoods(chref, sti(pchar.GenQuest.Hold_GenQuest.Goods), iSpace, 1);
	
	string sGroup = "Sea_" + chref.id
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
    Group_SetType(sGroup, "trade");
	
	int IslandID = FindIsland(GetArealByCityName(pchar.GenQuest.Hold_GenQuest.City));
	ref pLoc = &Islands[IslandID];
	float x, y, z;
	FindIslandLocatorXYZ(IslandID, "reload1", &x, &y, &z); 
	string sLocator = GetSeaQuestShipFarLocator(pLoc, "Quest_ships", x, y, z);
	
	chref.DontRansackCaptain = true;
	
	Group_SetAddress(sGroup, GetArealByCityName(pchar.GenQuest.Hold_GenQuest.City),"quest_ships", sLocator);        
    Group_AddCharacter(sGroup, chref.id);
    Group_SetGroupCommander(sGroup, chref.id);
	Group_SetTaskRunaway(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	
	pchar.quest.Hold_GenQuest_SinkMerchant.win_condition.l1 = "Character_sink";
    pchar.quest.Hold_GenQuest_SinkMerchant.win_condition.l1.character = "Hold_QuestMerchant";
    pchar.quest.Hold_GenQuest_SinkMerchant.function = "Hold_GenQuest_SinkMerchant";
    
	pchar.quest.Hold_GenQuest_CaptureMerchant.win_condition.l1 = "Character_Capture";
    pchar.quest.Hold_GenQuest_CaptureMerchant.win_condition.l1.character = "Hold_QuestMerchant";
    pchar.quest.Hold_GenQuest_CaptureMerchant.function = "Hold_GenQuest_CaptureMerchant";  

	SetFunctionTimerConditionParam("Hold_GenQuest_TimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
	
	int gcount = rand(3)-1;
    if (gcount < 0 || makeint(pchar.rank) < 5) gcount = 0;
    
    for (int i = 0; i < gcount; i++) // генерим эскорт
    {
        iChar = NPC_GenerateCharacter("Hold_QuestMerchantGuard_"+i, "off_spa_2", "man", "man", 5, sti(pchar.GenQuest.Hold_GenQuest.Nation), 3, true, "hunter"));
        makeref(sld, Characters[iChar]);
        SetGuardsShips(sld, sti(RealShips[sti(chref.ship.type)].Class));
        SetFantomParamHunter(sld); //крутые парни
        SetCaptanModelByEncType(sld, "war");
        sld.Ship.Mode = "war";
		sld.DontRansackCaptain = true;
        Group_AddCharacter(sGroup, sld.id);
    }
    chref.gcount = gcount;    	
}

void Hold_GenQuest_MerchantOver(string qName) // время вышло
{
	pchar.quest.Hold_GenQuest_SetMerchant.over = "yes";
	AddQuestRecord("HoldQuest", "3");
	AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);
	AddQuestUserData("HoldQuest", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.Hold_GenQuest.Goods)].Name + "Gen"))); 
	CloseQuestHeader("HoldQuest");
	DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");
}

void Hold_GenQuest_SinkMerchant(string qName)
{
	pchar.quest.Hold_GenQuest_CaptureMerchant.over = "yes";
	pchar.quest.Hold_GenQuest_TimeIsOver.over = "yes";
	AddQuestRecord("HoldQuest", "5");
	AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);
	AddQuestUserData("HoldQuest", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.Hold_GenQuest.Goods)].Name + "Gen"))); 
	CloseQuestHeader("HoldQuest");
	DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");	
}

void Hold_GenQuest_CaptureMerchant(string qName)
{
	pchar.quest.Hold_GenQuest_SinkMerchant.over = "yes";
	pchar.quest.Hold_GenQuest_TimeIsOver.over = "yes";
	AddQuestRecord("HoldQuest", "4");
	AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);
	AddQuestUserData("HoldQuest", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.Hold_GenQuest.Goods)].Name + "Gen"))); 
	CloseQuestHeader("HoldQuest");
	DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");		
}

void Hold_GenQuest_TimeIsOver(string qName)
{
	pchar.quest.Hold_GenQuest_SinkMerchant.over = "yes";
	pchar.quest.Hold_GenQuest_CaptureMerchant.over = "yes";
	ref sld = characterFromId("Hold_QuestMerchant");
	Group_DeleteGroup("Sea_" + sld.id); 
	AddQuestRecord("HoldQuest", "2");
	AddQuestUserData("HoldQuest", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
	AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);
	CloseQuestHeader("HoldQuest");
	DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");
}

void Hold_GenQuest_GenerateChar()
{
	int Rank = sti(pchar.rank) + rand(10);
	ref sld = GetCharacter(NPC_GenerateCharacter("Hold_GenQuestChar", "trader_"+(rand(5)+1), "man", "man", 10, sti(pchar.GenQuest.Hold_GenQuest.Nation), 3, true, "quest"));
	FantomMakeCoolFighter(sld, Rank, 100, 90, "blade_09", "pistol3", "grapeshot", 50);
	sld.name = pchar.GenQuest.Hold_GenQuest.Name;
	sld.lastname = "";
	sld.dialog.FileName = "GenQuests_Dialog.c";
	sld.dialog.currentnode = "Hold_GenQuest1";
	sld.greeting = "cit_quest";
	sld.CityType = "citizen";
	sld.City = pchar.GenQuest.Hold_GenQuest.City;
	LAi_SetImmortal(sld, true);	// До поры нельзя убить		
	string sTemp = pchar.GenQuest.Hold_GenQuest.City + "_" + pchar.GenQuest.Hold_GenQuest.found;
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, sTemp, "goto", "goto2");
}

void Hold_GenQuest_AfterBattle(string qName)
{
	chrDisableReloadToLocation = false; 
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);  
}

void Hold_GenQuest_FindCharTimeIsOver(string qName)
{
	ref sld = characterFromId("Hold_QuestChar");
	sld.LifeDay = 0;
	AddQuestRecord("HoldQuest", "9");
	AddQuestUserData("HoldQuest", "sSex",GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
	AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
	pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
}

void Hold_GenQuest_PrisonerEscaped()
{
	pchar.quest.Hold_GenQuest_ExitFromTown.win_condition.l1			= "EnterToSea";         
	pchar.quest.Hold_GenQuest_ExitFromTown.function    				= "Hold_GenQuest_ExitFromTownFight";									
	pchar.GenQuest.Hold_GenQuest.canSpeakSailor = true;
	pchar.TownEscape = true; 
}

void Hold_GenQuest_ExitFromTownFight(string qName)
{
	Log_QuestInfo("Блокируем выход на глобалку, ожидаем встречи с матросом");
	bQuestDisableMapEnter = true;
	QuestCloseSeaExit();
    DoQuestFunctionDelay("Hold_GenQuest_MeetWithSailor", 1);
}

void Hold_GenQuest_MeetWithSailor(string qName)
{
	Sea_DeckBoatStartNow(pchar); 
}

void Hold_GenQuest_GetMapTimeIsOver(string qName)
{
	pchar.quest.Hold_GenQuest_SpeakMapCharTavern.over = "yes";
	ref sld = characterFromId("Hold_QuestChar");
	sld.LifeDay = 0;
	AddQuestRecord("HoldQuest", "14");
	AddQuestUserData("HoldQuest", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
	AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
	CloseQuestHeader("HoldQuest");
	DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");				
}

void Hold_GenQuest_GenerateMapChar()
{
	ref sld = GetCharacter(NPC_GenerateCharacter("Hold_GenQuestChar", "citiz_"+(rand(9)+21), "man", "man", 5, sti(pchar.GenQuest.Hold_GenQuest.Nation), 3, true, "hunter"));
	sld.name = pchar.GenQuest.Hold_GenQuest.Name;
	sld.lastname = "";
	LAi_SetImmortal(sld, true);
	pchar.quest.Hold_GenQuest_SpeakMapCharTavern.win_condition.l1 = "location";
	pchar.quest.Hold_GenQuest_SpeakMapCharTavern.win_condition.l1.location = pchar.GenQuest.Hold_GenQuest.City + "_tavern";
	pchar.quest.Hold_GenQuest_SpeakMapCharTavern.function = "Hold_GenQuest_SpeakMapChar";
}

void Hold_GenQuest_SpeakMapChar(string qName)
{
	chrDisableReloadToLocation = true;
	ref sld = characterFromId("Hold_GenQuestChar");	
	sld.dialog.filename = "GenQuests_Dialog.c";
	sld.dialog.currentnode = "Hold_GenQuest80";	
	sld.greeting = "cit_quest";
	sld.CityType = "citizen";
	sld.City = pchar.GenQuest.Hold_GenQuest.City;
 	ChangeCharacterAddressGroup(sld, pchar.GenQuest.Hold_GenQuest.city + "_tavern", "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
}

void Hold_GenQuest_GenerateTreasureMap(ref item)
{
    item.MapIslId   = GetIslandForTreasure();
    item.MapLocId   = GetLocationForTreasure(item.MapIslId);
    item.MapBoxId   = GetBoxForTreasure(item.MapIslId, item.MapLocId);
	item.MapOwnId   = GetName(NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_NOM);
	
	DeleteAttribute(item, "BoxTreasure");

	pchar.GenQuest.Hold_GenQuest.Treasure.Island = item.MapIslId;
	pchar.GenQuest.Hold_GenQuest.Treasure.Location = item.MapLocId;
	pchar.GenQuest.Hold_GenQuest.Treasure.Locator = item.MapBoxId;
	
	SetFunctionLocationCondition("Hold_GenQuest_SetTreasureBoxFromMap", item.MapLocId, false);	
}

void Hold_GenQuest_SetTreasureBoxFromMap(string qName)
{
    ref    loc;
    string box, itmName;
    aref   item, arToBox, arFromBox;
	if (GetCharacterItem(pchar, "mapQuest") > 0 )
    {
        Log_Info(StringFromKey("GenQuests_16"));
        PlaySound("interface\notebook.wav");
		Statistic_AddValue(Pchar, "Treasure", 1);
		Achievment_SetStat(8, 1);
		if(SandBoxMode)
		{
			//if(CheckAttribute(pchar,"questTemp.SanBoxTarget"))
			//{
				//if(makeint(pchar.questTemp.SanBoxTarget) > 3)
				//{
					Achievment_SetStat(101, 1);
				//}
			//}
		}

		Items_FindItem("mapQuest", &item);
		
		if(sti(pchar.GenQuest.Hold_GenQuest.Treasure) == 0)
		{
			itmName = GenQuest_GeneratePrize();
			item.BoxTreasure.(itmName) = 1;
			
			if(rand(1) == 0)
			{
				itmName = GenQuest_GenerateGoodBlade();
				item.BoxTreasure.(itmName) = 1;
			}	
			
			itmName = "icollection"; // генерим сокровища
			item.BoxTreasure.(itmName) = 1 + makeint(sti(pchar.rank)/6); 
			
			itmName = "jewelry2";
			item.BoxTreasure.(itmName) = rand(5) + 5;
			
			itmName = "jewelry3";
			item.BoxTreasure.(itmName) = rand(4) + 10;
			
			GenerateAdmiralMapsTreasure(item, 12); // 250912
		}
		else
		{
			itmName = GetGeneratedItem("slave_02");
			item.BoxTreasure.(itmName) = rand(8) + 4;
		
			itmName = "mineral5"; // генерим ведра
			item.BoxTreasure.(itmName) = rand(5) + 2;
		
			itmName = "mineral8"; // генерим  башмаки
			item.BoxTreasure.(itmName) = rand(7) + 4;		
			
			if (rand(2) == 1)
	        {
            	item.BoxTreasure.slave_01 = 5 + rand(100);
	        }
	        else
	        {
				itmName = GetGeneratedItem("blade_11");
                item.BoxTreasure.(itmName) = 5 + rand(100);//fix
	        }
			if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral4 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral6 = 5 + rand(200);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral7 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral9 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral10 = 25 + rand(300);
	        }	        	        	        
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.cirass1 = 1;
	        }
			GenerateAdmiralMapsTreasure(item, 50); // 250912
		}
        box = item.MapBoxId;

        loc = &locations[FindLocation(item.MapLocId)];
        loc.(box).items = "";

        makearef(arToBox, loc.(box).items);
        makearef(arFromBox, item.BoxTreasure);
        CopyAttributes(arToBox, arFromBox);

        loc.(box) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
        loc.(box).Treasure = true; // признак сокровища в сундуке
		loc.(box).Hold_GenQuest_Treasure = true;

        DeleteAttribute(item, "MapIslId");
        TakeNItems(pchar, "mapQuest", -1);	

		pchar.GenQuest.Hold_GenQuest = "in_TreasureLoc";	
	}
}
//=====================================================================================================================================
// <-- ГЕНЕРАТОР "СИТУАЦИИ В ТРЮМЕ"
//=====================================================================================================================================

//=====================================================================================================================================
// Ugeen. разрешаем генерацию монстров в пещерах для главного персонажа -->
//=====================================================================================================================================
void GenQuest_EnableMonstersGen(string qName)
{
	if(CheckAttribute(pchar, "GenQuest.monstersTimer"))
	{
		DeleteAttribute(pchar, "GenQuest.monstersTimer");
	}	
}

bool GenQuest_CheckMonstersGen()
{
	if(CheckAttribute(pchar, "GenQuest.monstersTimer")) return false;
	else return true;
}
//=====================================================================================================================================
// <-- разрешаем генерацию монстров в пещерах для главного персонажа
//=====================================================================================================================================

//=====================================================================================================================================
// Warship, 15.05.11. Генератор "Правосудие на продажу" -->
//=====================================================================================================================================

// Выход из локации получения квеста.
void JusticeOnSale_LocationExit(string _quest)
{
	// Квест не взят, можно затереть.
	if(!CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait"))
	{
		DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
	}
	else
	{
		PChar.Quest.JusticeOnSale_MapEnter.win_condition.l1 = "MapEnter";
		PChar.Quest.JusticeOnSale_MapEnter.function = "JusticeOnSale_MapEnter";
	}
}

// Выход на карту при работающем квесте.
void JusticeOnSale_MapEnter(string _quest)
{
	ref sld;
	
	DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)], "DisableEncounters");
	
	DeleteQuestCondition("JusticeOnSale_ShoreEnterWithSmuggler");
	DeleteQuestCondition("JusticeOnSale_ShoreEnterFromMayor");
	DeleteQuestCondition("JusticeOnSale_ShoreEnterFromMayor");
	DeleteQuestCondition("JusticeOnSale_PirateShip_Sink");
	
	if(CheckPassengerInCharacter(PChar, "JusticeOnSale_Smuggler"))
	{
		sld = CharacterFromID("JusticeOnSale_Smuggler");
		RemovePassenger(PChar, sld);
		sld.LifeDay = 0;
		
		AddQuestRecord("JusticeOnSale", "2");
	}
	
	CloseQuestHeader("JusticeOnSale");
	DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
}

// Попадание в локацию нужной бухты вместе с освобожденным контриком.
void JusticeOnSale_ShoreEnterWithSmuggler(string _quest)
{
	int curModel, i = 0;
	ref location = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
	ref character;
	string model[11];
	
	model[0] = "citiz_41";
	model[1] = "citiz_42";
	model[2] = "citiz_43";
	model[3] = "citiz_44";
	model[4] = "citiz_45";
	model[5] = "citiz_46";
	model[6] = "citiz_47";
	model[7] = "citiz_48";
	model[8] = "citiz_49";
	model[9] = "citiz_50";
	model[10] = PChar.GenQuest.JusticeOnSale.SmugglerModel;
	
	DeleteQuestCondition("JusticeOnSale_MapEnter");
	
	character = CharacterFromID("JusticeOnSale_Smuggler");
	RemovePassenger(PChar, character);
	character.LifeDay = 0;
	
	while(i < sti(PChar.GenQuest.JusticeOnSale.EncQty))
	{
		if(i == 0)
		{
			curModel = 10;
		}
		else
		{
			curModel = rand(9);
		}
		
		if(model[curModel] != "")
		{
			character = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_ShorePirate_" + i, model[curModel], "man", "man", sti(PChar.rank), PIRATE, 0, true, "marginal"));
			SetFantomParamFromRank(character, sti(PChar.rank), true);
			ChangeCharacterAddressGroup(character, location.id, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
			character.dialog.filename = "GenQuests_Dialog.c";
			character.dialog.currentnode = "JusticeOnSale_9";
			character.greeting = "Enc_Raiders";
			LAi_SetActorType(character);
			
			if(i == 0)
			{
				character.name = PChar.GenQuest.JusticeOnSale.SmugglerName;
				character.lastName = "";
				LAi_ActorDialog(character, PChar, "", 3, 3);
			}
			else
			{
				LAi_ActorFollow(character, CharacterFromID("JusticeOnSale_ShorePirate_0"), "", -1);
			}
			
			model[curModel] = "";
			i++;
		}
	}
	
	chrDisableReloadToLocation = true;
	
	PChar.Quest.JusticeOnSale_LocationExit.win_condition.l1 = "ExitFromLocation";
	PChar.Quest.JusticeOnSale_LocationExit.win_condition.l1.location = PChar.location;
	PChar.Quest.JusticeOnSale_LocationExit.function = "JusticeOnSale_ClearShore";
}

// Попадание в локацию нужной бухты после мэра.
void JusticeOnSale_ShoreEnterFromMayor(string _quest)
{
	int i = 0;
	string attr;
	ref character;
	ref location = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
	
	while(i < sti(PChar.GenQuest.JusticeOnSale.EncQty))
	{
		character = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_ShorePirate_" + i, "", "man", "man", sti(PChar.rank), PIRATE, 0, true, "marginal"));
		SetModelPirate(character);
		SetFantomParamFromRank(character, sti(PChar.rank) + 5, true);
		ChangeCharacterAddressGroup(character, location.id, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
		
		LAi_SetWarriorTypeNoGroup(character);
		LAi_Group_MoveCharacter(character, "JusticeOnSale_ShoreGroup");
		
		attr = "l" + (i + 1);
		PChar.Quest.JusticeOnSale_KillSmugglers.win_condition.(attr) = "NPC_Death";
		PChar.Quest.JusticeOnSale_KillSmugglers.win_condition.(attr).character = "JusticeOnSale_ShorePirate_" + i;
		
		i++;
	}
	
	LAi_Group_SetRelation("JusticeOnSale_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_Group_FightGroups("JusticeOnSale_ShoreGroup", LAI_GROUP_PLAYER, true);
	
	PChar.Quest.JusticeOnSale_KillSmugglers.function = "JusticeOnSale_KillSmugglers";
	
	PChar.Quest.JusticeOnSale_LocExitAfterMayor.win_condition.l1 = "ExitFromLocation";
	PChar.Quest.JusticeOnSale_LocExitAfterMayor.win_condition.l1.location = PChar.location;
	PChar.Quest.JusticeOnSale_LocExitAfterMayor.function = "JusticeOnSale_LocExitAfterMayor";
}

void JusticeOnSale_ClearShore(string _quest)
{
	DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)], "DisableEncounters");
	DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
}

// Выход из локации бухты после посещения мэра.
void JusticeOnSale_LocExitAfterMayor(string _quest)
{
	DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)], "DisableEncounters");
	DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
	
	DeleteQuestCondition("JusticeOnSale_KillSmugglers");
	
	Group_DeleteGroup("JusticeOnSaleGroup"); // Потрем шип.
	
	AddQuestRecord("JusticeOnSale", "6");
	CloseQuestHeader("JusticeOnSale");
	
	Log_TestInfo("Вышли из локации, а зря.");
}

// Потопили корабль контриков.
void JusticeOnSale_PirateShip_Sink(string _quest)
{
	PChar.GenQuest.JusticeOnSale.ShipSink = true;
	
	DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)], "DisableEncounters");
	
	if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.KillSmugglers"))
	{
		// Сделали всё правильно.
		AddQuestRecord("JusticeOnSale", "7");
		CloseQuestHeader("JusticeOnSale");
	}
	else
	{
		// Не убив контриков в бухте, сразу стали мочить шип. Неверный алгоритм.
		DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
		
		DeleteQuestCondition("JusticeOnSale_ShoreEnterFromMayor");
		
		Group_DeleteGroup("JusticeOnSaleGroup"); // Потрем шип.
		
		AddQuestRecord("JusticeOnSale", "6");
		CloseQuestHeader("JusticeOnSale");
	}
	
	DeleteQuestCondition("JusticeOnSale_MapEnter");
}

// Завалили всех контриков в бухте.
void JusticeOnSale_KillSmugglers(string _quest)
{
	ref character;
	
	PChar.GenQuest.JusticeOnSale.KillSmugglers = true;
	
	if(GetCharacterShipLocation(PChar) == PChar.GenQuest.JusticeOnSale.ShoreId && !CheckAttribute(PChar, "GenQuest.JusticeOnSale.ShipSink"))
	{
		// Сделали всё правильно.
		DeleteQuestCondition("JusticeOnSale_LocExitAfterMayor");
		
		character = CharacterFromID("JusticeOnSale_ShipPirate");
		DeleteAttribute(character, "AlwaysFriend");
		SetCharacterRelationBoth(sti(character.index), GetMainCharacterIndex(), RELATION_ENEMY);
		
		Log_TestInfo("Квест идёт по правильному варианту.");
	}
	else
	{
		// Неверный алгоритм.
		DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)], "DisableEncounters");
		DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
		
		Group_DeleteGroup("JusticeOnSaleGroup"); // Потрем шип.
		
		DeleteQuestCondition("JusticeOnSale_PirateShip_Sink");
		
		AddQuestRecord("JusticeOnSale", "6");
		CloseQuestHeader("JusticeOnSale");
	}
	
	Log_TestInfo("Завалили всех контриков, выходим в море!");
}

//=====================================================================================================================================
// <-- Генератор "Правосудие на продажу".
//=====================================================================================================================================

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   Миниквесты        начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------- Переспать с официанткой ---------------------
void WaitressFack_null(string qName) //нулим квест официантки
{
	LocatorReloadEnterDisable(pchar.questTemp.different.FackWaitress.City + "_tavern", "reload2_back", true);
	pchar.questTemp.different = "free";
	pchar.quest.WaitressFack_inRoom.over = "yes"; 
	DeleteAttribute(pchar, "questTemp.different.FackWaitress");
}

void WaitressFack_inRoom(string qName)
{
	chrDisableReloadToLocation = true;
	LocatorReloadEnterDisable(locations[reload_location_index].fastreload + "_tavern", "reload2_back", true);
	DoQuestFunctionDelay("WaitressFack_Enter", 10.0 + frand(10.0));
}

void WaitressFack_Enter(string qName)
{	
	LAi_group_Delete("EnemyFight"); 
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, true);
	if (pchar.questTemp.different.FackWaitress.Kick == "0")
	{	//подстава
		iTemp = sti(pchar.rank) + rand(MOD_SKILL_ENEMY_RATE);
		sld = GetCharacter(NPC_GenerateCharacter("BerglarWairessQuest", "mercen_"+(rand(14)+14), "man", "man", iTemp, PIRATE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, iTemp, 80, 80, "blade_06", "pistol6", "bullet", 50);
		sld.dialog.Filename = "Quest\ForAll_dialog.c";
		sld.dialog.currentnode = "WaitressBerglar";	
		sld.greeting = "banditos"; 
 		//меняем обличие официантки
		rCharacter = characterFromId(locations[reload_location_index].fastreload + "_waitress");
		rCharacter.model = "women_" + (rand(5)+11);
		SetRandomNameToCharacter(rCharacter);
		FaceMaker(rCharacter);  
		CirassMaker(rCharacter);
	}
	else
	{
        sld = characterFromId("WairessQuest");
	}
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_ActorDialog(sld, pchar, "", 2.0, 0);
}

void WaitressFack_outRoom()
{
	// ==> Забираем клинки, пистоли и деньги.
	RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
	RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
    while (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) != "")
    {
        TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE));
    }
    while (FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE) != "")
    {             
        TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE));
    }
	while (FindCharacterItemByGroup(pchar, MUSKET_ITEM_TYPE) != "")
    {             
        TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, MUSKET_ITEM_TYPE));
    }
    pchar.money = 0;
    // <== Забираем клинки, пистоли и деньги.
	AddCharacterExpToSkill(pchar, "Pistol", 100);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
	pchar.questTemp.different = "FackWaitress_noMoney"; //флаг ограбили
}

void WaitressFack_fight()
{
	AddCharacterExpToSkill(pchar, "FencingL", 30);
	AddCharacterExpToSkill(pchar, "FencingS", 30);
	AddCharacterExpToSkill(pchar, "FencingH", 30);
	LAi_SetFightMode(pchar, true);
	pchar.questTemp.different = "FackWaitress_fighted"; //флаг пришлось подраться
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	pchar.quest.WaitressFack_afterFight.win_condition.l1 = "NPC_Death";
	pchar.quest.WaitressFack_afterFight.win_condition.l1.character = "BerglarWairessQuest";
	pchar.quest.WaitressFack_afterFight.win_condition = "OpenTheDoors";
}

void WaitressFack_fack()
{
	pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1;
	DoQuestCheckDelay("PlaySex_1", 1.0);
	pchar.questTemp.different = "FackWaitress_facking"; 
}

// ----------------- Пожертвование хозяйки борделя ---------------------
void HostessChurch_null(string qName) //нулим квест 
{
	//если квест ещё взят, то деньги считай прикарманены
	if (characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch == "taken") 
	{
		characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "baster";
	}
	pchar.questTemp.different = "free";
	DeleteAttribute(pchar, "questTemp.different.HostessChurch");
}

// ----------------- Найти кольцо мэра в борделе ---------------------
void TakeMayorsRing_null(string qName) //нулим квест 
{
	pchar.questTemp.different = "free";
	if (CheckCharacterItem(pchar, "MayorsRing"))
    {
		TakeItemFromCharacter(pchar, "MayorsRing");
		AddQuestRecord("SeekMayorsRing", "4");
		AddQuestUserData("SeekMayorsRing", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
		AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + pchar.questTemp.different.TakeMayorsRing.city + "Gen"));
		CloseQuestHeader("SeekMayorsRing");
		ChangeCharacterComplexReputation(pchar,"nobility", -3);
	}
	else
	{
		if (pchar.questTemp.different.TakeMayorsRing == "toBrothel")
		{
			AddQuestRecord("SeekMayorsRing", "5");
			AddQuestUserData("SeekMayorsRing", "sSex", GetSexPhrase(StringFromKey("GenQuests_76"),StringFromKey("GenQuests_77")));
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + pchar.questTemp.different.TakeMayorsRing.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
		}
	}
	DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
	DeleteAttribute(pchar, "questTemp.RomNaTroih");
}

// ----------------- Спихнуть судовые бумаги ---------------------
void GiveShipLetters_null(string qName) //нулим квест 
{
	pchar.questTemp.different = "free";
	DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
}

void CheckShipLetters(string qName)
{	
	if (!CheckCharacterItem(pchar, "CaptainBook"))
	{
		Log_QuestInfo("Бумаги не взяты!!");
		sld = ItemsFromID("CaptainBook");
		sld.shown = false;
		pchar.questTemp.different = "free";
		pchar.questTemp.different.GiveShipLetters.over = "yes"; //снимаем таймер 
		DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
	}
}
// ----------------- Спихнуть судовые бумаги ---------------------

// ----------------- Развод на секс хозяйки борделя ---------------------
void SexWithHostess_null(string qName) //нулим квест 
{
	if (pchar.questTemp.different.HostessSex == "toRoom")
	{
		sld = characterFromId(pchar.questTemp.different.HostessSex.city + "_Hostess");
		ChangeCharacterAddressGroup(sld, pchar.questTemp.different.HostessSex.city + "_SecBrRoom", "goto", "goto8");
		LocatorReloadEnterDisable(pchar.questTemp.different.HostessSex.city + "_Brothel", "reload2_back", true);
	}
	LAi_SetOwnerTypeNoGroup(sld);
	sld.dialog.currentnode = "First time";
	sld.quest.NotGoneToSex = true; //не пришёл. Секса больше не будет
	DeleteAttribute(pchar, "questTemp.different.HostessSex");
	pchar.questTemp.different = "free";
}

void SexWithHostess_goToRoom()  
{
	chrDisableReloadToLocation = true;
	sld = characterFromId(pchar.questTemp.different.HostessSex.city + "_Hostess");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", pchar.questTemp.different.HostessSex.city + "_Brothel_room", "goto", "goto3", "OpenTheDoors", -1);
	pchar.quest.SexWithHostess_inRoom.win_condition.l1 = "location";
	pchar.quest.SexWithHostess_inRoom.win_condition.l1.location = pchar.questTemp.different.HostessSex.city + "_Brothel_room";
	pchar.quest.SexWithHostess_inRoom.function = "SexWithHostess_inRoom";
	LocatorReloadEnterDisable(pchar.questTemp.different.HostessSex.city + "_Brothel", "reload2_back", false);
}

void SexWithHostess_inRoom(string qName)
{
	DoQuestFunctionDelay("SexWithHostess_inRoom_2", 1.5);
	LocatorReloadEnterDisable(pchar.questTemp.different.HostessSex.city + "_Brothel", "reload2_back", true);
	if (GetCharacterIndex(pchar.RomNaTroih_Shluha) != -1)
	{
		sld = CharacterFromID(pchar.RomNaTroih_Shluha);
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
		TeleportCharacterToPosAy(sld, -1.05, 0.27, 0.80, 0.60);
		LAi_CharacterDisableDialog(sld);
		sld.lifeday = 0;
	}
}

void SexWithHostess_inRoom_2(string qName)
{
	sld = characterFromId(pchar.questTemp.different.HostessSex.city + "_Hostess");
	sld.dialog.currentnode = "Hostess_inSexRoom";
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void SexWithHostess_fack()
{
	pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1;
	DoQuestCheckDelay("PlaySex_1", 1.0);
	pchar.questTemp.different = "HostessSex";
}

// ----------------- Миниквесты портмана  ---------------------
void SetCapitainFromCityToSea(string qName) //помещаем в море кэпа, который сейчас ошивается в городе
{
	if (!CheckAttribute(pchar, "quest." + qName + ".CapId")) return;
	int capIndex = GetCharacterIndex(pchar.quest.(qName).CapId)
	if (capIndex != -1)
	{		
		sld = &characters[capIndex];
		if (LAi_IsDead(sld)) return;
		sld.location	= "none";
		sld.location.group = "";
		sld.location.locator = "";
		//в морскую группу кэпа
		string sGroup = "PorpmansShip_" + sld.index;
		group_DeleteGroup(sGroup);
		Group_FindOrCreateGroup(sGroup);
		Group_SetType(sGroup,"trade");
		Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
		Group_LockTask(sGroup);
		Group_AddCharacter(sGroup, sld.id);
		Group_SetGroupCommander(sGroup, sld.id);
		SetRandGeraldSail(sld, sti(sld.Nation)); 
		//записываем данные в структуру кэпа
		sld.quest = "InMap"; //личный флаг рассеянного кэпа
		sld.quest.targetCity = SelectNotEnemyColony(sld); //определим колонию, куда отправится кэп
		sld.quest.stepsQty = sti(sld.quest.stepsQty) + 1; //количество выходов в море
		Log_TestInfo("Рассеянный кэп " + sld.id + " вышел из " + sld.city + " и направился в: " + sld.quest.targetCity);
		//определим бухту, куда ставить энкаунтер. чтобы сразу не генерился перед ГГ у города
		sTemp = GetArealByCityName(sld.city);
		sld.quest.baseShore = GetIslandRandomShoreId(sTemp);
		//на карту
		iTemp = GetMaxDaysFromIsland2Island(sTemp, GetArealByCityName(sld.quest.targetCity))+5; //дней доехать даем с запасом
		Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, iTemp);
		//даем общий слух, что кэп ушёл в другой город
		// -- > belamour gen
		AddSimpleRumourEx(LinkRandPhrase(StringFromKey("GenQuests_78", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName+"Gen")), sld.Ship.name, GetFullName(sld), XI_ConvertString("Colony"+ sld.quest.targetCity+"Acc")), 
			StringFromKey("GenQuests_79", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName+"Gen")), sld.Ship.name, XI_ConvertString("Colony"+sld.quest.targetCity+"Acc")), 
			StringFromKey("GenQuests_80", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName+ "Gen")), sld.Ship.name, XI_ConvertString("Colony"+sld.quest.targetCity+ "Acc"), GetFullName(sld))), 
			sld.city, iTemp, 1, "PortmansBook_DeliveryToCap", sld.id);
		// <-- gen
		//--> запись инфы по кэпу в базу местного портмана
		sTemp = sld.id; //Id кэпа, который оставил отметку
		rCharacter = &characters[GetCharacterIndex(sld.City + "_PortMan")];
		rCharacter.quest.capitainsList.(sTemp) = sld.quest.targetCity; //куда отправился
		rCharacter.quest.capitainsList.(sTemp).date = GetDateString(); //запишем дату, когда отправился
		//ВНИМАНИЕ. в квестбук должна заносится типовая строка по примеру   PortmansBook_Delivery    #TEXT   5
		//в список портмана заносим тайтл, заголовок и номер строки из quest_text.txt
		rCharacter.quest.capitainsList.(sTemp).QBString1 = characters[GetCharacterIndex(sld.quest.firstCity + "_PortMan")].id + "PortmansBook_Delivery";
		rCharacter.quest.capitainsList.(sTemp).QBString2 = "PortmansBook_Delivery";
		rCharacter.quest.capitainsList.(sTemp).QBQty = 5;
		//перезаносим время в базу кэпов
		sTemp = sld.id;
		NullCharacter.capitainBase.(sTemp).checkTime = iTemp + 5;
		NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
		NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
		NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	}
}

void SetRobberFromSeaToMap(string qName) //помещаем в море кэпа-вора, который счас стоит на рейде в порту
{
	if (!CheckAttribute(pchar, "quest." + qName + ".CapId")) return;
	int capIndex = GetCharacterIndex(pchar.quest.(qName).CapId)
	if (capIndex != -1)
	{		
		sld = &characters[capIndex];
		if (LAi_IsDead(sld)) return;
		//в морскую группу кэпа
		string sGroup = "SeekCapShip_" + sld.index;
		group_DeleteGroup(sGroup);
		Group_FindOrCreateGroup(sGroup);
		Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
		Group_LockTask(sGroup);
		Group_AddCharacter(sGroup, sld.id);
		Group_SetGroupCommander(sGroup, sld.id);
		SetRandGeraldSail(sld, sti(sld.Nation)); 
		//записываем данные в структуру кэпа
		sld.quest = "InMap"; //личный флаг рассеянного кэпа
		sld.quest.targetCity = SelectAnyColony2(sld.city, sld.quest.cribCity); //определим колонию, куда отправится кэп
		//Log_TestInfo("Кэп-вор " + sld.id + " вышел из: " + sld.city + " и направился в: " + sld.quest.targetCity);
		//на карту
		iTemp = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //дней доехать даем с запасом
		Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, iTemp);
		//даем общий слух, что кэп ушёл в другой город
		// -- > belamour gen
		AddSimpleRumourEx(LinkRandPhrase(StringFromKey("GenQuests_81", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName+"Gen")), sld.Ship.name, GetFullName(sld), XI_ConvertString("Colony"+sld.quest.targetCity+"Acc")), 
			StringFromKey("GenQuests_82", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName+"Gen")), sld.Ship.name, XI_ConvertString("Colony"+ sld.quest.targetCity+"Acc")), 
			StringFromKey("GenQuests_83", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName+"Gen")), sld.Ship.name, XI_ConvertString("Colony"+ sld.quest.targetCity+"Acc"), GetFullName(sld))), 
			sld.city, iTemp, 1, "Portmans_SeekShip_rum", sld.id);
		// <-- gen
		//--> запись инфы по кэпу в базу местного портмана
		sTemp = sld.id; //Id кэпа, который оставил отметку
		rCharacter = &characters[GetCharacterIndex(sld.City + "_PortMan")];
		rCharacter.quest.capitainsList.(sTemp) = sld.quest.targetCity; //куда отправился
		rCharacter.quest.capitainsList.(sTemp).date = GetDateString(); //запишем дату, когда отправился
		//ВНИМАНИЕ. в квестбук должна заносится типовая строка по примеру   PortmansBook_Delivery    #TEXT   5
		//в список портмана заносим тайтл, заголовок и номер строки из quest_text.txt
		rCharacter.quest.capitainsList.(sTemp).QBString1 = characters[GetCharacterIndex(sld.quest.cribCity + "_PortMan")].id + "Portmans_SeekShip";
		rCharacter.quest.capitainsList.(sTemp).QBString2 = "Portmans_SeekShip";
		rCharacter.quest.capitainsList.(sTemp).QBQty = 2;
		//перезаносим время в базу кэпов
		sTemp = sld.id;
		NullCharacter.capitainBase.(sTemp).checkTime = iTemp + 5;
		NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
		NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
		NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	}
}

void SeekShip_checkAbordage(string qName) //кэп-вор успешно абордирован
{	
	//смотрим, взят корабль себе или потоплен
	sld = characterFromId(pchar.quest.(qName).CapId);
	rCharacter = &characters[GetCharacterIndex(sld.quest.cribCity + "_PortMan")];
	bOk = false;
	for (i=0; i<=COMPANION_MAX; i++)
	{
		iTemp = GetCompanionIndex(pchar, i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			if (sld.ship.name == rCharacter.quest.PortmansSeekShip.shipName && 
				RealShips[sti(sld.ship.type)].BaseName == rCharacter.quest.PortmansSeekShip.shipTapeName &&
				RealShips[sti(sld.Ship.Type)].basetype == rCharacter.quest.PortmansSeekShip.shipTape)
			{
				bOk = true;
			}
		}
	}	
	//решение по результатам проверки
	sld = characterFromId(pchar.quest.(qName).CapId);
	sTemp = "SeekShip_checkSink" + rCharacter.index;
	pchar.quest.(sTemp).over = "yes"; //снимаем прерывание на утонул
	if (bOk)
	{		
		rCharacter.quest = "SeekShip_success"; //флаг успешного взятия на абордаж
		sTemp = rCharacter.id + "Portmans_SeekShip";
		AddQuestRecordEx(sTemp, "Portmans_SeekShip", "5");
	}
	else
	{
		rCharacter.quest = "SeekShip_sink"; //флаг утопления судна, провал квеста
		sTemp = rCharacter.id + "Portmans_SeekShip";
		AddQuestRecordEx(sTemp, "Portmans_SeekShip", "9");
	}
}

void SeekShip_checkSink(string qName)
{
	sld = characterFromId(pchar.quest.(qName).CapId);
	rCharacter = &characters[GetCharacterIndex(sld.quest.cribCity + "_PortMan")];
	rCharacter.quest = "SeekShip_sink"; //флаг утопления судна, провал квеста
	sTemp = rCharacter.id + "Portmans_SeekShip";
	AddQuestRecordEx(sTemp, "Portmans_SeekShip", "8");
	sTemp = "SeekShip_checkAbordage" + rCharacter.index;
	pchar.quest.(sTemp).over = "yes"; //снимаем прерывание на абордаж
}
// ----------------- поиск кэпов, дача квеста горожанином ---------------------
void SCQ_seekCapIsDeath(string qName)
{	
	string sTitle;
	sld = characterFromId(pchar.quest.(qName).CapId); //капитан
	rCharacter = &characters[GetCharacterIndex("QuestCitiz_" + sld.quest.cribCity)]; //горожанин-квестодатель
	//чистим базу нпс-кэпов  -->
	aref forName;
	makearef(forName, NullCharacter.capitainBase);
	DeleteAttribute(forName, sld.id);
	//<-- чистим базу нпс-кэпов
	if (rCharacter.quest.SeekCap == "NM_battle")
	{
		sTitle = sld.quest.cribCity + "SCQ_" + rCharacter.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + rCharacter.quest.SeekCap, "4");
		AddQuestUserData(sTitle, "sCapName", GetFullName(sld));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rCharacter.city + "Acc"));
		rCharacter.quest.SeekCap = rCharacter.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
	}
	if (rCharacter.quest.SeekCap == "NM_prisoner")
	{
		if (CheckAttribute(pchar, "GenQuest.mustboarding"))//в каюте при абордаже
	{
		sTitle = sld.quest.cribCity + "SCQ_" + rCharacter.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + rCharacter.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", rCharacter.quest.SeekCap.name);
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rCharacter.city + "Acc"));
		rCharacter.quest.SeekCap = rCharacter.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			DeleteAttribute(pchar, "GenQuest.mustboarding");
		}
		else
		{
			sTitle = sld.quest.cribCity + "SCQ_" + rCharacter.quest.SeekCap;
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			string sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SecondTimer_" + sld.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем возможно установленный таймер
			sTemp = "SCQ_" + rCharacter.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
			if (CheckAttribute(sld, "quest.release")) //если кэп сам отдал пассажира
			{
				AddQuestRecordEx(sTitle, "SCQ_" + rCharacter.quest.SeekCap, "5");
				AddQuestUserData(sTitle, "sName", rCharacter.quest.SeekCap.name);
				AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rCharacter.city + "Acc"));
				rCharacter.quest.SeekCap = rCharacter.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			}
			else
		{
			rCharacter.lifeDay = 0;
				AddQuestRecordEx(sTitle, "SCQ_" + rCharacter.quest.SeekCap, "4");
				CloseQuestHeader(sTitle);
			}
		}
	}
	if (rCharacter.quest.SeekCap == "NM_peace")
	{
		sTitle = sld.quest.cribCity + "SCQ_" + rCharacter.quest.SeekCap;
		sld.lifeDay = 0;
		Map_ReleaseQuestEncounter(sld.id);
		sGroup = "SeekCapShip_" + sld.index;
		group_DeleteGroup(sGroup);
		sTemp = "SecondTimer_" + sld.id;
		pchar.quest.(sTemp).over = "yes"; //снимаем возможно установленный таймер
		sTemp = "SCQ_" + rCharacter.index;
		pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
		AddQuestRecordEx(sTitle, "SCQ_" + rCharacter.quest.SeekCap, "4");
		CloseQuestHeader(sTitle);
	}
	if (rCharacter.quest.SeekCap == "manSlave")
	{
		sTitle = sld.quest.cribCity + "SCQ_" + rCharacter.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + rCharacter.quest.SeekCap, "4");
		AddQuestUserData(sTitle, "sCapName", GetFullName(sld));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rCharacter.city + "Acc"));
		rCharacter.quest.SeekCap = rCharacter.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
	}
	if (sld.quest.SeekCap == "womanRevengeFight") //проверим флаг боя на улице, уже можно валить
	{
		sTitle = sld.quest.cribCity + "SCQ_" + rCharacter.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + rCharacter.quest.SeekCap, "5");
		AddQuestUserData(sTitle, "sCapName", GetFullName(sld));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rCharacter.city + "Acc"));
		rCharacter.quest.SeekCap = rCharacter.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
		sTemp = "SecondTimer_" + sld.id;
		pchar.quest.(sTemp).over = "yes"; //снимаем возможно установленный таймер
		sTemp = "SCQ_" + rCharacter.index;
		pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
	}
	if (sld.quest.SeekCap == "womanHasband" || rCharacter.quest.SeekCap == "manRapeWife" || sld.quest.SeekCap == "manFriend" || sld.quest.SeekCap == "womanRevenge" || rCharacter.quest.SeekCap == "womanPirates")
	{
		sTitle = sld.quest.cribCity + "SCQ_" + sld.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + sld.quest.SeekCap, "4");
		sld.lifeDay = 0;
		Map_ReleaseQuestEncounter(sld.id);
		sGroup = "SeekCapShip_" + sld.index;
		group_DeleteGroup(sGroup);
		sTemp = "SecondTimer_" + sld.id;
		pchar.quest.(sTemp).over = "yes"; //снимаем возможно установленный таймер
		sTemp = "SCQ_" + rCharacter.index;
		pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
		sTitle = sld.quest.cribCity + "SCQ_" + sld.quest.SeekCap;
		CloseQuestHeader(sTitle);
		//снимаем горожанку-маньячку
		if (sld.quest.SeekCap == "womanRevenge")
		{
			rCharacter.lifeDay = 0;
		}
	}
}
//смерть квестодателя закрывает и чистит квест
void SCQ_CitizenIsDeath(string qName)
{
	sld = characterFromId(pchar.quest.(qName).CapId); //капитан	
	sld.lifeDay = 0;
	rCharacter = characterFromId(pchar.quest.(qName).CitizenId); //горожанин-квестодатель
	//чистим базу нпс-кэпов  -->
	aref forName;
	makearef(forName, NullCharacter.capitainBase);
	DeleteAttribute(forName, sld.id);
	//<-- чистим базу нпс-кэпов
	Map_ReleaseQuestEncounter(sld.id);
	string sGroup = "SeekCapShip_" + sld.index;
	group_DeleteGroup(sGroup);
	sTemp = "SecondTimer_" + sld.id;
	pchar.quest.(sTemp).over = "yes"; //снимаем возможно установленный таймер
	sTemp = "SCQ_" + sld.index;
	pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
	string sTitle = sld.quest.cribCity + "SCQ_" + rCharacter.quest.SeekCap;
	CloseQuestHeader(sTitle);
}

void CitizCapFromSeaToMap(string qName) //помещаем на карту кэпа, разыскиваемого горожанами
{
	if (!CheckAttribute(pchar, "quest." + qName + ".CapId")) return;
	int capIndex = GetCharacterIndex(pchar.quest.(qName).CapId)
	if (capIndex != -1)
	{		
		sld = &characters[capIndex];
		if (LAi_IsDead(sld)) return;
		sld.nation = sld.quest.nation;
		//в морскую группу кэпа
		string sGroup = "SeekCapShip_" + sld.index;
		group_DeleteGroup(sGroup);
		Group_FindOrCreateGroup(sGroup);
		Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
		Group_LockTask(sGroup);
		Group_AddCharacter(sGroup, sld.id);
		Group_SetGroupCommander(sGroup, sld.id);
		SetRandGeraldSail(sld, sti(sld.Nation)); 
		//записываем данные в структуру кэпа
		sld.quest = "InMap"; //личный флаг искомого кэпа
		sld.quest.targetCity = SelectAnyColony2(sld.city, sld.quest.cribCity); //определим колонию, куда отправится кэп
		//Log_TestInfo("Искомый кэп " + sld.id + " вышел из: " + sld.city + " и направился в: " + sld.quest.targetCity);
		//на карту
		iTemp = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //дней доехать даем с запасом
		Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, iTemp);
		//даем общий слух, что кэп ушёл в другой город
		// --> belamour gen
		AddSimpleRumourEx(LinkRandPhrase(StringFromKey("GenQuests_84", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName+ "Gen")), sld.Ship.name, GetFullName(sld), XI_ConvertString("Colony"+ sld.quest.targetCity+"Acc")), 
			StringFromKey("GenQuests_85", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName+ "Gen")), sld.Ship.name, XI_ConvertString("Colony"+ sld.quest.targetCity+ "Acc")), 
			StringFromKey("GenQuests_86", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName, "Gen")), sld.Ship.name, XI_ConvertString("Colony"+ sld.quest.targetCity+"Acc"), GetFullName(sld))), 
			sld.city, iTemp, 1, "Citiz_SeekCap_rum", sld.id);
		// <-- gen
		//--> запись инфы по кэпу в базу местного портмана
		sTemp = sld.id; //Id кэпа, который оставил отметку
		rCharacter = &characters[GetCharacterIndex(sld.City + "_PortMan")];
		rCharacter.quest.capitainsList.(sTemp) = sld.quest.targetCity; //куда отправился
		rCharacter.quest.capitainsList.(sTemp).date = GetDateString(); //запишем дату, когда отправился
		//ВНИМАНИЕ. в квестбук должна заносится типовая строка по примеру   PortmansBook_Delivery    #TEXT   5
		//в список портмана заносим тайтл, заголовок и номер строки из quest_text.txt
		rCharacter.quest.capitainsList.(sTemp).QBString1 = sld.quest.cribCity + "SCQ_" + characters[GetCharacterIndex("QuestCitiz_"+sld.quest.cribCity)].quest.SeekCap;
		rCharacter.quest.capitainsList.(sTemp).QBString2 = "SCQ_" + characters[GetCharacterIndex("QuestCitiz_"+sld.quest.cribCity)].quest.SeekCap;
		rCharacter.quest.capitainsList.(sTemp).QBQty = 2;
		//меняем сроки проверки по Id кэпа в базе нпс-кэпов
		sTemp = sld.id;
		NullCharacter.capitainBase.(sTemp).checkTime = iTemp + 5;
		NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
		NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
		NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	}
}

//после боевки в каюте. для всех квестов по поисков кэпов ситезанами
void CitizSeekCap_afterCabinFight(string qName)
{	
	sld = GetCharacter(NPC_GenerateCharacter(pchar.quest.(qName).label + "_" + pchar.quest.(qName).WifeCity, pchar.quest.(qName).model, "woman", "towngirl", 5, pchar.quest.(qName).nation, -1, false, "citizen"));
	sld.name = pchar.quest.(qName).WifeName;
	sld.lastname = pchar.quest.(qName).WifeLastname;
	sld.dialog.filename   = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = pchar.quest.(qName).label + "_Board";
	sld.quest.SeekCap = pchar.quest.(qName).label;
	sld.quest.cribCity = pchar.quest.(qName).WifeCity;
	LAi_SetStayType(sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
	LAi_SetActorType(pchar);
    LAi_SetActorType(sld);
    SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   Миниквесты        конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//-->------------------------------------малява, грабеж торгашей------------------------------------------------
void Deliver_CreateTraderShips(string qName)//создание торговых кораблей
{
	int i, ShipType, Rank, iShipRank, iCannonType;
	int iGoods, iSpace;
	ref sld;
	string sTemp1, sTemp2, sNation;
			
	sTemp1 = pchar.questTemp.jailCanMove.Deliver.ShipName1;//имя корабля
	sTemp2 = pchar.questTemp.jailCanMove.Deliver.ShipName2;//имя корабля
	sNation = pchar.questTemp.jailCanMove.Deliver.Nation;
    Island_SetReloadEnableGlobal(pchar.questTemp.jailCanMove.Deliver.Island, false);
    Group_FindOrCreateGroup("Trade_Attack");//создать группу
	Group_SetType("Trade_Attack", "trade");//тип группы
	for (i=1; i<=2; i++)
	{
		if(makeint(pchar.rank) >= 21) { iShipRank = 3; }
		if(makeint(pchar.rank) >= 12 && makeint(pchar.rank) < 21) { iShipRank = 2; }	
		if(makeint(pchar.rank) >= 6 && makeint(pchar.rank) < 12) { iShipRank = 1; }	
		if(makeint(pchar.rank) < 5) { iShipRank = 0; }
		switch (iShipRank)
		{
			case 0:  
				ShipType = GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
				Rank = 12 + rand(5);
			break; 		
			case 1:  
				ShipType = GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
				Rank = 18 + rand(5);
			break; 
			case 2: 
				ShipType = GetRandomShipType(FLAG_SHIP_CLASS_4 + FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
				Rank = 25 + rand(5);
			break; 
			case 3: 
				ShipType = GetRandomShipType(FLAG_SHIP_CLASS_2 + FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
				Rank = 30 + rand(5);
			break; 			
		}
		sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, "trader_"+(rand(15)+1), "man", "man", Rank, sNation, 3, true, "hunter"));//создание кэпа
		if (i == 1)
		{
			FantomMakeCoolSailor(sld, ShipType, sTemp1, -1, 48, 35, 35);//создание кораблей
		}
		if (i == 2)
		{
			FantomMakeCoolSailor(sld, ShipType, sTemp2, -1, 44, 30, 30);//создание кораблей
		}
		sld.Ship.Mode = "trade";
		iGoods = sti(pchar.questTemp.jailCanMove.Deliver.Goods);
		iSpace = GetCharacterFreeSpace(sld, iGoods);
		iSpace = makeint(iSpace/2 + rand(iSpace/2));
		SetCharacterGoods(sld, iGoods, iSpace);
		Group_AddCharacter("Trade_Attack", "CaptainAttack_"+i);//добавление в группу
		sld.AlwaysEnemy = true;
		sld.ship.Crew.Morale = 30+MOD_SKILL_ENEMY_RATE*5;
		ChangeCrewExp(sld, "Sailors", 30+MOD_SKILL_ENEMY_RATE*5);
		ChangeCrewExp(sld, "Cannoners", 10+MOD_SKILL_ENEMY_RATE*5);
		ChangeCrewExp(sld, "Soldiers", 20+MOD_SKILL_ENEMY_RATE*5);
    }
	Group_SetGroupCommander("Trade_Attack", "CaptainAttack_1");
	Group_SetTaskAttack("Trade_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Trade_Attack", PLAYER_GROUP);
	Group_SetAddress("Trade_Attack", pchar.questTemp.jailCanMove.Deliver.Island, "Quest_Ships", "Quest_Ship_" + (3+ rand(4)));
	Group_LockTask("Trade_Attack");
			
    pchar.quest.jailCanMoveDeliver_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.jailCanMoveDeliver_AfterBattle.win_condition.l1.group = "Trade_Attack";
	pchar.quest.jailCanMoveDeliver_AfterBattle.function = "Deliver_AfterBattle";//это победа
	pchar.quest.jailCanMoveDeliver_DieHard.win_condition.l1 = "MapEnter";
    pchar.quest.jailCanMoveDeliver_DieHard.function = "Deliver_DieHard";//это слинял
	pchar.quest.Deliver_TraderShipsOver.over = "yes";
	AddQuestRecord("GivePrisonFree", "13_1");
	AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase(StringFromKey("GenQuests_76"),StringFromKey("GenQuests_77")));
	AddQuestUserData("GivePrisonFree", "sShipName1", pchar.questTemp.jailCanMove.Deliver.ShipName1);
	AddQuestUserData("GivePrisonFree", "sShipName2", pchar.questTemp.jailCanMove.Deliver.ShipName2);
}

void Deliver_AfterBattle(string qName)//реакция на победу
{
	DoQuestCheckDelay("sea_victory", 1.5);
	Group_DeleteGroup("Trade_Attack");
	Island_SetReloadEnableGlobal(pchar.questTemp.jailCanMove.Deliver.Island, true);
    pchar.quest.jailCanMoveDeliver_DieHard.over = "yes";
	DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
	CloseQuestHeader("GivePrisonFree");
	AddComplexSeaExpToScill(100, 100, 100, 100, 100, 100, 0);
}

void Deliver_DieHard(string qName)//реакция на поражение
{
	Group_DeleteGroup("Trade_Attack");
    Island_SetReloadEnableGlobal(pchar.questTemp.jailCanMove.Deliver.Island, true);
    pchar.quest.jailCanMoveDeliver_AfterBattle.over = "yes";
	DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
	CloseQuestHeader("GivePrisonFree");
}

void Deliver_TraderShipsOver(string qName)//просроченный таймер торговых кораблей и кидалова - 2 в 1
{
	pchar.quest.jailCanMoveDeliver_ShipsAttack.over = "yes";
	AddQuestRecord("GivePrisonFree", "13_2");
	AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
	AddQuestUserData("GivePrisonFree", "sShipName1", pchar.questTemp.jailCanMove.Deliver.ShipName1);
	AddQuestUserData("GivePrisonFree", "sShipName2", pchar.questTemp.jailCanMove.Deliver.ShipName2);
	DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
	CloseQuestHeader("GivePrisonFree");
}
//<--малява, грабеж торгашей

//------------------------------------малява, перехват курьера-------------------------------------------------
void Deliver_CreateCureerShips(string qName)//создание курьерского корабля
{
	int i, ShipType, Rank, iShipRank, iCannonType;
	int iNation = sti(pchar.questTemp.jailCanMove.Deliver.Nation);
	ref sld;
	string Blade, sTemp, sNation;
	
	sTemp = pchar.questTemp.jailCanMove.Deliver.ShipName;//имя корабля
	sNation = pchar.questTemp.jailCanMove.Deliver.Nation;
    Island_SetReloadEnableGlobal(pchar.questTemp.jailCanMove.Deliver.Island, false);
    Group_FindOrCreateGroup("Cureer_Attack");
	Group_SetType("Cureer_Attack", "war");
		if(makeint(pchar.rank) >= 21) { iShipRank = 3; }
		if(makeint(pchar.rank) >= 12 && makeint(pchar.rank) < 21) { iShipRank = 2; }	
		if(makeint(pchar.rank) >= 6 && makeint(pchar.rank) < 12) { iShipRank = 1; }	
		if(makeint(pchar.rank) < 6) { iShipRank = 0; }
		switch (iShipRank)
		{
			case 0:  
				ShipType = GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY);
				Rank = 12 + rand(5);
                Blade = "blade_08";
			break; 		
			case 1:  
				ShipType = GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY);
				Rank = 17 + rand(5);
                Blade = "blade_09";
			break; 
			case 2: 
				ShipType = GetRandomShipType(FLAG_SHIP_CLASS_4 + FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY);
				Rank = 22 + rand(5);
                Blade = "blade_10";
			break; 
			case 3: 
				ShipType = GetRandomShipType(FLAG_SHIP_CLASS_3 + FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY);
				Rank = 30 + rand(5);
                Blade = "blade_13";
			break; 			
		}
	sld = GetCharacter(NPC_GenerateCharacter("CureerAttack", "off_" + NationShortName(iNation) + "_" + (rand(1) + 1), "man", "man", Rank, sNation, 3, true, "quest"));
	FantomMakeCoolSailor(sld, ShipType, sTemp, -1, 75, 50, 50);
	FantomMakeCoolFighter(sld, Rank, 40, 40, Blade, "pistol3", "grapeshot", 40);
	Group_AddCharacter("Cureer_Attack", "CureerAttack");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		SetCharacterPerk(sld, "MusketsShoot");
		sld.AlwaysEnemy = true;
	Group_SetGroupCommander("Cureer_Attack", "CureerAttack");
	Group_SetTaskAttack("Cureer_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Cureer_Attack", PLAYER_GROUP);
	Group_SetAddress("Cureer_Attack", pchar.questTemp.jailCanMove.Deliver.Island, "Quest_Ships", "Quest_Ship_" + (3+ rand(4)));
	Group_LockTask("Cureer_Attack");
			
    pchar.quest.jailCanMoveDeliver_AfterBattleC.win_condition.l1 = "Group_Death";
	pchar.quest.jailCanMoveDeliver_AfterBattleC.win_condition.l1.group = "Cureer_Attack";
	pchar.quest.jailCanMoveDeliver_AfterBattleC.function = "DeliverC_AfterBattle";//это победа
	pchar.quest.jailCanMoveDeliver_DieHardC.win_condition.l1 = "MapEnter";
    pchar.quest.jailCanMoveDeliver_DieHardC.function = "DeliverC_DieHard";//это слинял
	pchar.quest.Deliver_CureerShipsOver.over = "yes";
	AddQuestRecord("GivePrisonFree", "14_1");
	AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase(StringFromKey("GenQuests_76"),StringFromKey("GenQuests_77")));
	AddQuestUserData("GivePrisonFree", "sShipName", pchar.questTemp.jailCanMove.Deliver.ShipName);
}

void DeliverC_AfterBattle(string qName)//реакция на победу
{
	DoQuestCheckDelay("sea_victory", 1.5);
	Group_DeleteGroup("Cureer_Attack");
	Island_SetReloadEnableGlobal(pchar.questTemp.jailCanMove.Deliver.Island, true);
    pchar.quest.jailCanMoveDeliver_DieHardC.over = "yes";
	DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
	CloseQuestHeader("GivePrisonFree");
	AddComplexSeaExpToScill(100, 100, 100, 100, 100, 100, 0);
}

void DeliverC_DieHard(string qName)//реакция на поражение
{
	Group_DeleteGroup("Cureer_Attack");
    Island_SetReloadEnableGlobal(pchar.questTemp.jailCanMove.Deliver.Island, true);
    pchar.quest.jailCanMoveDeliver_AfterBattleC.over = "yes";
	DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
	CloseQuestHeader("GivePrisonFree");
}

void Deliver_CureerShipsOver(string qName)//просроченный таймер курьерского корабля
{
	pchar.quest.jailCanMoveDeliver_ShipsCAttack.over = "yes";
	AddQuestRecord("GivePrisonFree", "14_2");
	AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
	AddQuestUserData("GivePrisonFree", "sShipName", pchar.questTemp.jailCanMove.Deliver.ShipName);
	DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
	CloseQuestHeader("GivePrisonFree");
}
//<--малява, перехват курьера

//------------------------------------------малява, кидалово-----------------------------------------
void Deliver_lay(string qName)//пришли - а нету никого
{
	pchar.quest.Deliver_TraderShipsOver.over = "yes";
	AddQuestRecord("GivePrisonFree", "15");
	AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase(StringFromKey("GenQuests_76"),StringFromKey("GenQuests_77")));
	AddQuestUserData("GivePrisonFree", "sSex1", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
	AddQuestUserData("GivePrisonFree", "sShipName1", pchar.questTemp.jailCanMove.Deliver.ShipName1);
	AddQuestUserData("GivePrisonFree", "sShipName2", pchar.questTemp.jailCanMove.Deliver.ShipName2);
	DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
	CloseQuestHeader("GivePrisonFree");
}
//<--малява, кидалово

//zagolski - побег офицера
void mOfficer_fc(string qName)
{
	if (!CheckAttribute(pchar, "questTemp.MutinyOfficerIDX")) {
		return;
	}
	ref sld = &Characters[sti(Pchar.questTemp.MutinyOfficerIDX)];
	if (!CheckAttribute(sld, "quest.Mutiny")) { // mitrokosta если офф мёртв или уволен
		DeleteAttribute(pchar, "questTemp.MutinyOfficerIDX");
		return;
	}
	if (CheckAttribute(sld, "ShipInStockMan")) { // mitrokosta сюрприз для хитрецов поставивших в ПУ
		DeleteAttribute(pchar, "questTemp.MutinyOfficerIDX");
		sld.quest.Mutiny.date = GetDateString();
		return;
	}

	if (IsEntity(&worldMap))
    {
		if(sti(sld.Payment) == true)
		{
			if (sti(sld.ship.type) != SHIP_NOTUSED)
			{
				Log_SetStringToLog(StringFromKey("GenQuests_87", GetFullName(sld), sld.ship.name));
				DeleteAttribute(pchar, "questTemp.MutinyOfficerIDX");
			}
			else
			{
				Log_SetStringToLog(StringFromKey("GenQuests_88", GetFullName(sld), pchar.ship.name));

				if (GetCrewQuantity(pchar) > 0 && !IsEquipCharacterByArtefact(pchar, "totem_02"))
				{
					AddCharacterExpToSkill(PChar, "Leadership", 200);
					MunityOnShip("ShipMunity");
				}
				else DeleteAttribute(pchar, "questTemp.MutinyOfficerIDX");
			}
			sld.LifeDay = 0;
			RemovePassenger(Pchar, sld);
		}
		else DeleteAttribute(pchar, "questTemp.MutinyOfficerIDX");
		
    }
	else
    {
        pchar.quest.mOfficer_fc2.win_condition.l1 = "MapEnter";
		pchar.quest.mOfficer_fc2.function    = "mOfficer_fc2";
    }
}

void mOfficer_fc2(string qName)
{
	if (!CheckAttribute(pchar, "questTemp.MutinyOfficerIDX")) {
		return;
	}
	ref sld = &Characters[sti(Pchar.questTemp.MutinyOfficerIDX)];
	if (!CheckAttribute(sld, "quest.Mutiny")) { // mitrokosta если офф мёртв или уволен
		DeleteAttribute(pchar, "questTemp.MutinyOfficerIDX");
		return;
	}
	if (CheckAttribute(sld, "ShipInStockMan")) { // mitrokosta сюрприз для хитрецов поставивших в ПУ
		DeleteAttribute(pchar, "questTemp.MutinyOfficerIDX");
		sld.quest.Mutiny.date = GetDateString();
		return;
	}

	if(sti(sld.Payment) == true)
	{
		if (sti(sld.ship.type) != SHIP_NOTUSED)
		{
			Log_SetStringToLog(StringFromKey("GenQuests_87", GetFullName(sld), sld.ship.name));
			DeleteAttribute(pchar, "questTemp.MutinyOfficerIDX");
		}
		else
		{
			Log_SetStringToLog(StringFromKey("GenQuests_88", GetFullName(sld), pchar.ship.name));

			if (GetCrewQuantity(pchar) > 0 && !IsEquipCharacterByArtefact(pchar, "totem_02"))
			{
				AddCharacterExpToSkill(PChar, "Leadership", 200);
				MunityOnShip("ShipMunity");
			}
			else DeleteAttribute(pchar, "questTemp.MutinyOfficerIDX");
		}
		sld.LifeDay = 0;
		RemovePassenger(Pchar, sld);
	}
	else DeleteAttribute(pchar, "questTemp.MutinyOfficerIDX");
}

// belamour Нежелательный постоялец -->
void Unwantedpostor_NextQuest(string _quest)
{
	pchar.GenQuest.Unwantedpostor = "start";
	log_testinfo("Доступен квест: Нежелательный постоялец");
}

void Unwantedpostor_OneDay(string _quest) // таймер на день
{
	DeleteAttribute(PChar, "GenQuest.Unwantedpostor");
	SetFunctionTimerCondition("Unwantedpostor_NextQuest", 0, 0, 170+rand(20), false);
	log_testinfo("Просрочен квест: Нежелательный постоялец");
}
// <-- belamour Нежелательный постоялец

// belamour пьяный матрос -->
void GuiltySailor_NextQ(string _quest)
{
	pchar.GenQuest.GuiltySailor = "true";
}
// <-- пьяный матрос

// belamour хороший специалист -->
void ExpertSailor_NextQuest(string _quest)
{
	pchar.GenQuest.ExpertSailor = "true";
}
// <-- хороший специалист

// belamour ночной приключенец -->
void NightAdventure_NextQuest(string _quest)
{
	pchar.GenQuest.NightAdventure = "true";
}

void NightAdventure_Intavern(string _quest)
{
	if(CheckAttribute(pchar,"GenQuest.CantRun")) DeleteAttribute(pchar,"GenQuest.CantRun");
	bDisableFastReload = false;
	pchar.quest.NightAdventure_JungleExit.over = "yes"; 
	pchar.quest.NightAdventure_SeaExit.over = "yes";
	if (GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
	{
		LAi_SetCitizenType(characterFromId(pchar.GenQuest.NightAdventureId)); // хватит ходить следом
		if(CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1
		&& CheckAttribute(characterFromId("Mary"),"quest.iwantsex")) return; // Жарь, музыка
		if(GetCharacterIndex("Ole") != -1 && CheckAttribute(characterFromId("Ole"), "pearl_date") && 
		GetNpcQuestPastDayParam(characterFromId("Ole"), "pearl_date") >= 20) return; // Оле с жемчугом 
		chrDisableReloadToLocation = true;//закрыть локацию
		sld = characterFromId(pchar.GenQuest.NightAdventureId);
		DeleteAttribute(sld, "CityType"); // иначе фантомы не будет грузить
		sld.dialog.currentnode = pchar.GenQuest.NightAdventureNode;
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void NightAdventure_Duel(string _quest)
{
	LAi_LocationDisableOfficersGen(Locations[FindLocation(pchar.location)].fastreload+"_tavern", false); // офицеров пускать
	chrDisableReloadToLocation = true;//закрыть локацию
	GetCharacterPos(pchar, &locx, &locy, &locz);
	sld = characterFromId(pchar.GenQuest.NightAdventureId);
	sld.dialog.currentnode = "NightAdventure_CardProf_Fight_5";
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz)); 
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void NightAdventure_ToBoat(string _quest)
{
	chrDisableReloadToLocation = true;//закрыть локацию
	bDisableFastReload = false;
	DeleteAttribute(pchar,"GenQuest.CantRun");
	LAi_SetStayType(pchar);
	sld = characterFromId(pchar.GenQuest.NightAdventureId);
	sld.dialog.currentnode = pchar.GenQuest.NightAdventureNode;
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void NightAdventure_CitizenHomieOK(string _quest) 
{
	pchar.quest.NightAdventure_JungleExit.over = "yes"; 
	pchar.quest.NightAdventure_SeaExit.over = "yes";
	chrDisableReloadToLocation = true;//закрыть локацию
	GetCharacterPos(pchar, &locx, &locy, &locz);
	LAi_SetStayType(pchar);
	sld = characterFromId(pchar.GenQuest.NightAdventureId);
	sld.dialog.currentnode = "NightAdventure_CitizenHomiePresent";
	string nation = sld.City;
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz)); 
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	sld = GetCharacter(NPC_GenerateCharacter("NightAdventure_Homie", "citiz_"+(rand(9)+11), "man", "man", 25, nation, -1, true, "quest"));
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz)); 
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
}

void NightAdventure_InFort(string _quest)
{
	PlaySound("interface\notebook.wav");
	log_info(StringFromKey("GenQuests_60")); 
	pchar.quest.NightAdventure_InCave.over = "yes";
	pchar.quest.NightAdventure_SeaExit.over = "yes";
	if (GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
	{
		sld = characterFromId(pchar.GenQuest.NightAdventureId);
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld.lifeday = 0;
	}
	SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
}

void NightAdventure_InCave(string _quest)
{
	PlaySound("interface\notebook.wav");
	log_info(StringFromKey("GenQuests_61"));
	pchar.quest.NightAdventure_SeaExit.over = "yes";
	pchar.quest.NightAdventure_InFort.over = "yes";
	if(CheckAttribute(pchar,"GenQuest.CantRun")) DeleteAttribute(pchar,"GenQuest.CantRun");
	bDisableFastReload = false;
	if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PirateBad")
	{
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true); // запретить драться
	}
	if (GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
	{
		LAi_SetCitizenType(characterFromId(pchar.GenQuest.NightAdventureId)); // хватит ходить следом
		chrDisableReloadToLocation = true;//закрыть локацию
		sld = characterFromId(pchar.GenQuest.NightAdventureId);
		sld.dialog.currentnode = "NightAdventure_PirateCave_4";
		if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PirateBad") sld.greeting = "banditos";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}

void NightAdventure_PiratesInCave(string _quest)
{
	int i, Rank, iBull;
	
	iBull = GetCharacterIndex(pchar.GenQuest.NightAdventureId);
	//--> генерим ранг 
	if (sti(pchar.rank) > 6) 
	{
		if (sti(pchar.rank) > 20) Rank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*4/3);
		else Rank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*2.5/3);
	}
	else  
	{	//казуалам зеленый свет на начало игры
		if (sti(pchar.rank) > 3) Rank = sti(pchar.rank);
		else Rank = 1;
	}	
	//<-- генерим ранг 
	for(i=0 ; i < 3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("NAPirat_" + i, "citiz_4"+(1+rand(8)), "man", "man", Rank, PIRATE, 0, true, "marginal"));
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
		LAi_SetActorType(sld);
		if(i == 0) LAi_ActorFollow(sld, &characters[iBull], "NightAdventure_PiratesSpeak", -1);
		else LAi_ActorFollow(sld, &characters[iBull], " ", -1);
	}
	LAi_SetActorType(pchar);
}
void NightAdventure_InBrothel(string _quest)
{
	if(CheckAttribute(pchar,"GenQuest.CantRun")) DeleteAttribute(pchar,"GenQuest.CantRun");
	pchar.quest.NightAdventure_JungleExit.over = "yes"; 
	pchar.quest.NightAdventure_SeaExit.over = "yes";
	if (GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
	{
		LAi_SetCitizenType(characterFromId(pchar.GenQuest.NightAdventureId)); // хватит ходить следом
		chrDisableReloadToLocation = true;//закрыть локацию
		pchar.GenQuest.CannotWait = true;
		sld = characterFromId(pchar.GenQuest.NightAdventureId);
		//DeleteAttribute(sld, "CityType"); 
		sld.dialog.currentnode = pchar.GenQuest.NightAdventureNode;
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
}
void NightAdventure_JungleExit(string _quest)
{
	//log_testinfo("Jungle");
	pchar.quest.NightAdventure_Intavern.over = "yes"; 
	pchar.quest.NightAdventure_SeaExit.over = "yes";
	pchar.quest.NightAdventure_ToBoat.over = "yes"; 
	if (GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
	{
		sld = characterFromId(pchar.GenQuest.NightAdventureId);
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld.lifeday = 0;
	}
	if(CheckAttribute(pchar,"GenQuest.NightAdventureToJail"))
	{
		DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
	}
	if(CheckAttribute(pchar,"GenQuest.NightAdventureSolNum"))
	{
		DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
	}
	if(CheckAttribute(pchar,"GenQuest.NightAdventureToPrisoner")) 
	{
		DeleteAttribute(pchar,"GenQuest.NightAdventureToPrisoner");
	}
	bDisableFastReload = false; 
	DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
	DeleteAttribute(pchar,"GenQuest.CantRun");
	DeleteAttribute(pchar,"GenQuest.NightAdventureVar");
	DeleteAttribute(pchar,"GenQuest.NightAdventureId");
}

void NightAdventure_SeaExit(string _quest)
{
	//log_testinfo("Sea");
	pchar.quest.NightAdventure_JungleExit.over = "yes"; 
	pchar.quest.NightAdventure_Intavern.over = "yes";
	pchar.quest.NightAdventure_ToBoat.over = "yes"; 
	pchar.quest.NightAdventure_InCave.over = "yes";
	pchar.quest.NightAdventure_InFort.over = "yes";
	if (GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
	{
		sld = characterFromId(pchar.GenQuest.NightAdventureId);
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld.lifeday = 0;
	}
	if(CheckAttribute(pchar,"GenQuest.NightAdventureToJail"))
	{
		DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
	}
	if(CheckAttribute(pchar,"GenQuest.NightAdventureSolNum")) 
	{
		DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
	}
	if(CheckAttribute(pchar,"GenQuest.NightAdventureToPrisoner")) 
	{
		DeleteAttribute(pchar,"GenQuest.NightAdventureToPrisoner");
	}
	bDisableFastReload = false; 
	DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
	DeleteAttribute(pchar,"GenQuest.CantRun");
	DeleteAttribute(pchar,"GenQuest.NightAdventureVar");
	DeleteAttribute(pchar,"GenQuest.NightAdventureId");
}

void NightAdventure_KillPhant(string _quest)
{
	if(CheckAttribute(pchar,"GenQuest.NightAdventureNode")) // если брали квест, но не прошли до конца
	{
		pchar.quest.NightAdventure_Intavern.over = "yes";
		pchar.quest.NightAdventure_SeaExit.over = "yes";
		pchar.quest.NightAdventure_JungleExit.over = "yes";
		pchar.quest.NightAdventure_ToBoat.over = "yes"; 
		DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
		DeleteAttribute(pchar,"GenQuest.CantRun");
		bDisableFastReload = false;
	}
	if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
	{
		sld = characterFromId(pchar.GenQuest.NightAdventureId);
		sld.lifeday = 0;
	}
	if(GetCharacterIndex("NightAdventure_CardProf") != -1)
	{
		sld = characterFromId("NightAdventure_CardProf");
		sld.lifeday = 0;
	}
	for(int i=0 ; i < 3; i++)
	{
		if(GetCharacterIndex("NAPirat_" + i) != -1)
		{
			sld = CharacterFromID("NAPirat_" + i);
			sld.lifeday = 0;
		}
	}
	DeleteAttribute(pchar,"GenQuest.NightAdventureId");
	DeleteAttribute(pchar,"GenQuest.NightAdventureVar");
	if(CheckAttribute(pchar,"GenQuest.NightAdventure_money")) DeleteAttribute(pchar,"GenQuest.NightAdventure_money");
	if(CheckAttribute(pchar,"GenQuest.NightAdventureToJail")) DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
	if(CheckAttribute(pchar,"GenQuest.NightAdventureToPrisoner")) DeleteAttribute(pchar,"GenQuest.NightAdventureToPrisoner");
	if(CheckAttribute(pchar,"GenQuest.NightAdventureSolNum")) DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");	
}
// <-- приключенец

/// belamour рыбацкое судно -->
void FishingBoat_NextQuest(string _quest);
{
	pchar.GenQuest.FishingBoat = true;
}

void FishingBoat_End(string _quest)
{
	if(GetCharacterIndex("FishingBoatCap") != -1)
	{
		sld = characterFromId("FishingBoatCap");
		sld.lifeday = 0;
		Group_DeleteGroup("FishingBoat"); 
	}
	if(CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb"))
	{
		DeleteAttribute(pchar,"GenQuest.FishingBoatDialogEnb");
	}
	if(CheckAttribute(pchar,"GenQuest.GenQuest.FishingBoatITemp"))
	{
		DeleteAttribute(pchar,"GenQuest.GenQuest.FishingBoatITemp");
	}
	if(CheckAttribute(pchar,"GenQuest.FishingBoatIMoney"))
	{
		DeleteAttribute(pchar,"GenQuest.FishingBoatIMoney");
	}
	if(CheckAttribute(pchar,"GenQuest.FishingBoatIQty"))
	{
		DeleteAttribute(pchar,"GenQuest.FishingBoatIQty");
	}
	if(CheckAttribute(pchar,"GenQuest.FishingBoatSecondTime"))
	{
		DeleteAttribute(pchar,"GenQuest.FishingBoatSecondTime");
	}
	if(CheckAttribute(pchar,"GenQuest.FishingBoatSTemp"))
	{
		DeleteAttribute(pchar,"GenQuest.FishingBoatSTemp");
	}
	Group_FreeAllDead();
	SetFunctionTimerCondition("FishingBoat_NextQuest", 0, 0, 25+rand(10), false);
}
// <-- рыбацкое судно

// belamour квест на получение фонаря -->
void NoiseCemetery_toCrypt(string _quest) 
{
	if(IsDay()) return;
	pchar.quest.NoiseCemetery_toCrypt.over = "yes";
	chrDisableReloadToLocation = true;//закрыть локацию
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
	sld = GetCharacter(NPC_GenerateCharacter("CemeteryCouple_1", "citiz_8", "man", "man", 25, sti(pchar.questTemp.Lantern.nation), -1, true, "quest"));
	sld.Dialog.Filename = "GenQuests_Dialog.c";
	sld.dialog.currentnode = "CemeteryMan";
	RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed");
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto5");
	
	sld = GetCharacter(NPC_GenerateCharacter("CemeteryCouple_2", "women_10", "woman", "towngirl", 25, sti(pchar.questTemp.Lantern.nation), -1, true, "quest"));
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto6");
	sld.Dialog.Filename = "GenQuests_Dialog.c";
	sld.dialog.currentnode = "CemeteryGirl";
	LAi_SetActorType(sld);
}

void NoiseCemetery_SeaExit(string _quest)
{
	pchar.quest.NoiseCemetery_toCrypt.over = "yes";
	pchar.questTemp.Lantern = "fail";
	AddQuestRecord("NoiseCemetery", "5");
	AddQuestUserData("NoiseCemetery", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
	CloseQuestHeader("NoiseCemetery");
}
// <-- квест на получение фонаря 
// сброс особого статуса у стартового города
void SanBoxStatusCityRemove(string _quest)
{
	if(CheckAttribute(pchar,"questTemp.StatusCity"))
	{
		DeleteAttribute(pchar,"questTemp.StatusCity");
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// --> Jason ---------------------------Товарно-транспортный генератор-----------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FrahtHunterOnSea()//охотники в акватории порта прибытия, одна функция на троих
{
	ref sld;
	int i, iShipType, iRank, iShipRank, iCannonType, iNation;
	string sBlade, sTemp;
    Group_FindOrCreateGroup("Fraht_Attack");
	Group_SetType("Fraht_Attack", "war");
	iNation = PIRATE;
	if (pchar.questTemp.WPU.Postcureer == "begin") iNation = pchar.questTemp.WPU.Postcureer.EnemyNation;
	if (pchar.questTemp.WPU.Escort == "begin") iNation = pchar.questTemp.WPU.Escort.EnemyNation;
	for (i=1; i<=2; i++)
	{
		iRank = sti(pchar.rank) + rand(5);
		if(makeint(pchar.rank) >= 30) { iShipRank = 6; }
		if(makeint(pchar.rank) >= 25 && makeint(pchar.rank) < 30) { iShipRank = 5; }
		if(makeint(pchar.rank) >= 19 && makeint(pchar.rank) < 25) { iShipRank = 4; }	
		if(makeint(pchar.rank) >= 13 && makeint(pchar.rank) < 18) { iShipRank = 3; }	
		if(makeint(pchar.rank) >= 8 && makeint(pchar.rank) < 12) { iShipRank = 2; }	
		if(makeint(pchar.rank) >= 5 && makeint(pchar.rank) < 8) { iShipRank = 1; }	
		if(makeint(pchar.rank) < 5) { iShipRank = 0; }
		
		
		int iClassFlag = FLAG_SHIP_CLASS_5;
		switch (iShipRank)
		{
			case 0:  
				iClassFlag = FLAG_SHIP_CLASS_6;					
				iTotalTemp = CANNON_TYPE_CANNON_LBS6;
				sTotalTemp = "blade_03";
			break;
			case 1:  
				iClassFlag = FLAG_SHIP_CLASS_5;					
				iTotalTemp = CANNON_TYPE_CANNON_LBS6;
				sTotalTemp = "blade_03";
			break; 	
			case 2:  
				iClassFlag = FLAG_SHIP_CLASS_4;				
				iTotalTemp = CANNON_TYPE_CANNON_LBS12;
				sTotalTemp = "blade_05";
			break; 		
			case 3:  
				iClassFlag = FLAG_SHIP_CLASS_3;	
				iTotalTemp = CANNON_TYPE_CANNON_LBS16;
				sTotalTemp = "blade_06";
			break; 
			case 4: 
				iClassFlag = FLAG_SHIP_CLASS_3;		
				iTotalTemp = CANNON_TYPE_CULVERINE_LBS18;
				sTotalTemp = "blade_10";
			break; 
			case 5: 
				iClassFlag = FLAG_SHIP_CLASS_2;     			
				iTotalTemp = CANNON_TYPE_CANNON_LBS20;
				sTotalTemp = "blade_13";
			break; 
			case 6: 
				iClassFlag = FLAG_SHIP_CLASS_2;					
				iTotalTemp = CANNON_TYPE_CANNON_LBS24;
				sTotalTemp = "blade_19";
			break;  				
		}
		
		
		iShipType = GetRandomShipType(iClassFlag, FLAG_SHIP_TYPE_WAR, FLAG_SHIP_NATION_ANY);
		sld = GetCharacter(NPC_GenerateCharacter("FrahtAttack_"+i, "citiz_"+(rand(9)+41), "man", "man", iRank, iNation, 30, true, "quest"));//создание кэпа
		FantomMakeSmallSailor(sld, iShipType, "", iCannonType, 30+rand(15), 20+rand(10), 20+rand(15), 20+rand(15), 20+rand(15));
		FantomMakeCoolFighter(sld, iRank, 30, 30, sBlade, "pistol1", "bullet", 30);
		SetCaptanModelByEncType(sld, "war");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		sld.AlwaysEnemy = true;
		sld.AnalizeShips = true; 
		Group_AddCharacter("Fraht_Attack", "FrahtAttack_"+i);//добавление в группу
    }
	Group_SetGroupCommander("Fraht_Attack", "FrahtAttack_1");
	Group_SetTaskAttack("Fraht_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Fraht_Attack", PLAYER_GROUP);
	Group_SetAddress("Fraht_Attack", pchar.questTemp.WPU.Current.TargetIslandID, "", "");
	Group_LockTask("Fraht_Attack");
}

void EnemyNationHunterOnMap(bool _fast)//охотники вражеской нации
{
    ref  sld;
    int  i, iNation;
    string sCapId = "FollowerNation0"; // patch
    string sGroup = "Sea_" + sCapId + "1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	iNation = GetEnemyNationToMainCharacter();//вражеская нация
	while ((iNation) == PIRATE)
	{
			iNation = GetEnemyNationToMainCharacter();
	}
    for (i = 1; i <= GetCompanionQuantity(pchar); i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_" + NationShortName(iNation) + "_" + (rand(1) + 1), "man", "man", sti(PChar.rank) + 5, iNation, 6, true, "hunter"));
        SetShipHunter(sld);
        SetFantomParamHunter(sld);
        SetCaptanModelByEncType(sld, "war");
        sld.AlwaysEnemy = true;
        sld.DontRansackCaptain = true;
        sld.mapEnc.type = "war";
        sld.mapEnc.Name = StringFromKey("GenQuests_89");
		sld.hunter = iNation;
        Group_AddCharacter(sGroup, sCapId + i);
    }
    Group_SetGroupCommander(sGroup, sCapId+ "1");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	if (_fast) Map_CreateCoolWarrior("", sCapId + "1", 6);
	else Map_CreateWarrior("", sCapId + "1", 6);
}

//--> ------------------------------------------фрахт------------------------------------------------------
void FrahtTime_Over(string qName)//опоздали доставить товар по фрахту
{
	pchar.questTemp.WPU.Fraht = "late";
	SaveCurrentQuestDateParam("questTemp.Fraht.Late");//запомнить дату
	AddQuestRecord("Fraht", "3");
	AddQuestUserData("Fraht", "sTargetColony" ,XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.TargetCity+"Gen"));
	SetFunctionTimerCondition("FrahtTime_FullOver", 0, 0, 19, false);
}

void FrahtTime_FullOver(string qName)//прошли все разумные сроки
{
	pchar.questTemp.WPU.Fraht = "lost";
	AddQuestRecord("Fraht", "5");
	ChangeCharacterComplexReputation(pchar,"nobility", -10);
	ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.WPU.Fraht.Nation)) + "hunter", 30);
	pchar.questTemp.WPU.Fraht.count = 0;//счетчик фрахтов в ноль
	Group_DeleteGroup("Fraht_Attack");
}

void FrahtTimeLevelUp_Over(string qName)//опоздали доставить товар по фрахту 2 уровня
{
	pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-3;//скрутим счетчик
	DeleteAttribute(pchar, "questTemp.WPU.Fraht.LevelUp");
	DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
	pchar.questTemp.WPU.Fraht = "complete";
	AddQuestRecord("Fraht", "3_1");
	CloseQuestHeader("Fraht");
}
// <-- фрахт конец

//--> ------------------------------------------------почта----------------------------------------------------
void PostcureerTime_Over(string qName)//опоздали доставить почту
{
	pchar.questTemp.WPU.Postcureer = "late";
	SaveCurrentQuestDateParam("questTemp.Postcureer.Late");//запомнить дату
	if (CheckAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp")) SetFunctionTimerCondition("PostcureerTime_FullOver", 0, 0, 4, false);
	else SetFunctionTimerCondition("PostcureerTime_FullOver", 0, 0, 9, false);
	AddQuestRecord("Postcureer", "3");
	AddQuestUserData("Postcureer", "sSex1", GetSexPhrase(StringFromKey("GenQuests_64"),StringFromKey("GenQuests_65")));
}

void PostcureerTime_FullOver(string qName)//прошли все сроки на доставку почты
{
	pchar.questTemp.WPU.Postcureer = "lost";
	pchar.questTemp.WPU.Postcureer.count = 0;//счетчик почты в ноль
	Group_DeleteGroup("Fraht_Attack");
	if (CheckAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp"))
	{
		AddQuestRecord("Postcureer", "7");
		ChangeCharacterComplexReputation(pchar,"nobility", -12);
		ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.WPU.Postcureer.Nation)) + "hunter", 35);
	}
	else
	{
		AddQuestRecord("Postcureer", "5");
	}
}
//<--почта конец

//--> ----------------------------------------------эскорт-----------------------------------------------
void EscortTime_Over(string qName)//опоздали сопроводить корабли
{
	pchar.questTemp.WPU.Escort = "late";
	SaveCurrentQuestDateParam("questTemp.Escort.Late");//запомнить дату
	AddQuestRecord("Escort", "3");
	SetFunctionTimerCondition("EscortTime_FullOver", 0, 0, 9, false);
}

void EscortTime_FullOver(string qName)//прошли все сроки на сопровождение
{
	if (pchar.questTemp.WPU.Escort.Bonus != "fail")
	{
		pchar.quest.Escort_fail.over = "yes";//снять прерывание
		pchar.questTemp.WPU.Escort.count = 0;//счетчик эскортов в ноль
		Group_DeleteGroup("Fraht_Attack");
		if (GetCharacterIndex("EscortCaptain_1") != -1 && GetCharacterIndex("EscortCaptain_2") != -1)//оба живы
		{
			RemoveCharacterCompanion(Pchar, characterFromID("EscortCaptain_1"));//удалим компаньонов
			RemoveCharacterCompanion(Pchar, characterFromID("EscortCaptain_2"));
		}
		else
		{
			if (GetCharacterIndex("EscortCaptain_1") == -1) RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_2"));
			else RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_1"));
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), -5);
		}//если делать через цикл - определяет несуществующего НПС, вот и приходится такой огород городить
	}
	if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
	{
		pchar.questTemp.WPU.Escort = "complete";
		pchar.questTemp.WPU.Fraht = "lost";
		
		if (pchar.questTemp.WPU.Escort.Bonus != "fail") AddQuestRecord("Escort", "7");
		else AddQuestRecord("Escort", "16");
		
		pchar.questTemp.WPU.Fraht.count = 0;//счетчик фрахтов в ноль
		ChangeCharacterComplexReputation(pchar,"nobility", -15);
		ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.WPU.Escort.Nation)) + "hunter", 35);
		pchar.questTemp.WPU.Fraht.Nation = pchar.questTemp.WPU.Escort.Nation;
		pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Escort.TargetPortmanID;
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	}
	else
	{
		pchar.questTemp.WPU.Escort = "complete";
		AddQuestRecord("Escort", "5");
		CloseQuestHeader("Escort");
		ChangeCharacterComplexReputation(pchar,"nobility", -10);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), -5);
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
	}
}

void Escort_failed(string qName)//два корабля потоплены - провал
{
	if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
	{
		pchar.questTemp.WPU.Escort.Bonus = "fail";
		AddQuestRecord("Escort", "15");
	}
	else
	{
		if (pchar.questTemp.WPU.Escort == "begin") pchar.quest.EscortTime_Over.over = "yes";//снять таймер
		if (pchar.questTemp.WPU.Escort == "late") pchar.quest.EscortTime_FullOver.over = "yes";//снять таймер
		pchar.questTemp.WPU.Escort = "complete";
		AddQuestRecord("Escort", "10");
		CloseQuestHeader("Escort");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
	}
	pchar.questTemp.WPU.Escort.count = 0;//счетчик эскортов в ноль
	Group_DeleteGroup("Fraht_Attack");
	ChangeCharacterComplexReputation(pchar,"nobility", -10);
	ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), -9);
}
//<--эскорт конец

//--> -------------------------------------задания курьера 2 уровня---------------------------------------------
void PostcureerGopHuntersOnLand(string qName)//охотники в порту прибытия
{
	LAi_group_Delete("EnemyFight");
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
	for (i=1; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("PostHunters"+i, "citiz_58", "man", "man", sti(PChar.rank) + 10, PIRATE, 1, true, "hunter"));
		SetFantomParamHunter(sld);
		SetModelPirate(sld);
		LAi_SetActorType(sld);
		if (i == 1)
		{
			sld.dialog.Filename = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "PostGopHunters";	
			sld.greeting = "hunter"; 
			ChangeCharacterAddressGroup(sld, pchar.questTemp.WPU.Postcureer.City+"_town", "goto", "goto1");
		}
		else
		{
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, pchar.questTemp.WPU.Postcureer.City+"_town", "goto", "goto1");
		}
		LAi_ActorDialog(sld, pchar, "", 10, 0); 
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
}

void PostcureerProfHuntersOnLand(string qName)//наемники в порту убытия
{
	LAi_group_Delete("EnemyFight");
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
	int iRank = sti(PChar.rank) + 10;
	for (i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("PostHunters"+i, "citiz_58", "man", "man", iRank, PIRATE, 1, true, "hunter"));
		FantomMakeCoolFighter(sld, iRank, 50, 50, "blade_06", "pistol6", "bullet", 100);
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		LAi_SetActorType(sld);
		if (i == 1)
		{
			sld.dialog.Filename = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "PostProfHunters";	
			sld.greeting = "hunter"; 
			ChangeCharacterAddressGroup(sld, pchar.questTemp.WPU.Postcureer.StartCity +"_town", "goto", "goto1");
		}
		else
		{
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, pchar.questTemp.WPU.Postcureer.StartCity +"_town", "goto", "goto1");
		}
		LAi_ActorDialog(sld, pchar, "", 20, 0); 
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
}

void PostcureerAgent(string qName)//агент
{
	LAi_group_Delete("EnemyFight");
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
	int iRank = sti(PChar.rank) + 10;
	int iNation = pchar.questTemp.WPU.Postcureer.EnemyNation;
	sld = GetCharacter(NPC_GenerateCharacter("PostAgent", "shipowner_"+(rand(6)+4), "man", "man", iRank, iNation, 2, true, "quest"));
	FantomMakeCoolFighter(sld, iRank, 50, 50, "blade_16", "pistol5", "bullet", 50);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	LAi_SetActorType(sld);
	sld.dialog.Filename = "Quest\Other_quests_NPC.c";
	sld.dialog.currentnode = "PostAgent";	
	sld.greeting = "captain_trader"; 
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.questTemp.WPU.Postcureer.StartCity +"_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_ActorDialog(sld, pchar, "", -1, 0); 
	LAi_group_MoveCharacter(sld, "EnemyFight");
}

void PostcureerAgent_ShipAttack(string qName)//агентский фрегат
{
	int iNation = pchar.questTemp.WPU.Postcureer.EnemyNation;
	Group_FindOrCreateGroup("AgentFrigate");//создать группу
	Group_SetType("AgentFrigate", "war");//тип группы
	sld = GetCharacter(NPC_GenerateCharacter("PostAgentCaptain", "citiz_41", "man", "man", 25, iNation, 1, true, "quest"));//создание кэпа
	FantomMakeCoolSailor(sld, SHIP_FRIGATE, "", CANNON_TYPE_CANNON_LBS24, 50, 50, 50);//создание кораблей
	FantomMakeCoolFighter(sld, 25, 50, 50, "blade_13", "pistol6", "bullet", 50);//создание фантома кэпа
	SetCaptanModelByEncType(sld, "war");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.DontRansackCaptain = true; 
	sld.AlwaysEnemy = true;
	sld.AnalizeShips = true;
	Group_AddCharacter("AgentFrigate", "PostAgentCaptain");//добавление в группу
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	// ==> стравливание
	Group_SetGroupCommander("AgentFrigate", "PostAgentCaptain");
	Group_SetTaskAttack("AgentFrigate", PLAYER_GROUP);
	Group_SetPursuitGroup("AgentFrigate", PLAYER_GROUP);
	Group_SetAddress("AgentFrigate", pchar.questTemp.WPU.Postcureer.AgentIslandID, "", "");
	Group_LockTask("AgentFrigate");
	AddQuestRecord("Postcureer", "14");
}
//<-- задания курьера 2 уровня конец

//--> --------------------------------------задания 2 уровня эскорт--------------------------------------------
void EscortArsenalShip_Over(string qName)//не пришли в срок
{
	pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-2;//скрутим счетчик за то, что не пришёл
	AddQuestRecord("Escort", "21");
	AddQuestUserData("Escort", "sTargetColony", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
	CloseQuestHeader("Escort");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_0");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	pchar.questTemp.WPU.Escort = "complete";
}

void EscortArsenalShipGo_Over(string qName)//не сопровождали, а маялись дурью
{
	pchar.quest.Escort_fail.over = "yes";
	RemoveCharacterCompanion(Pchar, characterFromID("ArsenalShipCaptain"));
	sld = characterFromId("ArsenalShipCaptain");
	sld.lifeday = 0;//на всякий случай
	pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-4;//скрутим счетчик за провал
	AddQuestRecord("Escort", "22");
	AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
	CloseQuestHeader("Escort");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUpGo_0");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	pchar.questTemp.WPU.Escort = "complete";
}

void EscortArsenalShip_failed(string qName)//потеряли корабль
{
	pchar.quest.EscortArsenalShipGo_Over.over = "yes";
	AddQuestRecord("Escort", "23");
	CloseQuestHeader("Escort");
	pchar.questTemp.WPU.Escort.count = 1;//сильно скрутим счетчик за провал
	ChangeCharacterComplexReputation(pchar,"nobility", -2);
	ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), -3);
	DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUpGo_0");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	pchar.questTemp.WPU.Escort = "complete";
}

void DesIsland_Over(string qName)//общее опоздание по всем приключениям у необитаек
{
	pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-3;//скрутим счетчик за опоздание
	AddQuestRecord("Escort", "26");
	AddQuestUserData("Escort", "sIsland", XI_ConvertString("Colony"+pchar.questTemp.WPU.Current.TargetIslandID));
	CloseQuestHeader("Escort");
	if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM"))
	{
		pchar.quest.DisasterShip_WM.over = "yes";//снять прерывание
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM");
	}
	if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP"))
	{
		pchar.quest.DisasterShip_VSP.over = "yes";//снять прерывание
		Delete_EscortStorm();//уберем шторм
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP");
	}
	if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1S"))
	{
		pchar.quest.DisasterShip_S.over = "yes";//снять прерывание
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1S");
	}
	pchar.questTemp.WPU.Escort = "complete";
	DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
}

void Delete_EscortStorm()//убираем шторм
{
	reload_cur_island_index = FindIsland(pchar.questTemp.WPU.Current.TargetIslandID);
	DeleteAttribute(&Islands[reload_cur_island_index], "alwaysStorm");
	DeleteAttribute(&Islands[reload_cur_island_index], "storm");
	DeleteAttribute(&Islands[reload_cur_island_index], "tornado");
	DeleteAttribute(&Islands[reload_cur_island_index], "QuestlockWeather");
	DeleteAttribute(&Islands[reload_cur_island_index], "MaxSeaHeight");//уберем шторм
}

void CreateDisasterShip_WithoutMasts(string qName)//создаем покоцаный корабль
{
    Group_FindOrCreateGroup("WMShip");
	Group_SetType("WMShip", "trade");
	int iShipType = sti(pchar.questTemp.WPU.Escort.ShipType);
	sTemp = pchar.questTemp.WPU.Escort.ShipName;
	sld = GetCharacter(NPC_GenerateCharacter("WMCaptain", "citiz_41", "man", "man", 10, sti(pchar.nation), -1, true, "quest"));
	FantomMakeSmallSailor(sld, iShipType, sTemp, CANNON_TYPE_CANNON_LBS12, 40, 20, 25, 30, 20);
	SetFantomParamFromRank(sld, 10, true); 
	SetCaptanModelByEncType(sld, "trade");
	sld.Ship.Mode = "trade";
	sld.ship.HP = makeint(sti(sld.ship.HP)/5);
	sld.ship.masts.mast3 = 1;
	SetCrewQuantityOverMax(sld, 50+rand(10));
	Group_AddCharacter("WMShip", "WMCaptain");//добавление в группу
	Group_SetGroupCommander("WMShip", "WMCaptain");
	Group_SetAddress("WMShip", pchar.questTemp.WPU.Current.TargetIslandID, "quest_ships", "quest_ship_1");
	pchar.quest.Escort_Shootfail.win_condition.l1 = "Group_Death";
	pchar.quest.Escort_Shootfail.win_condition.l1.group = "WMShip";
	pchar.quest.Escort_Shootfail.function = "Escort_Shootfail";//для особо упоротых
}

void Escort_Shootfail(string qName)//утопили судно сами
{
	Group_DeleteGroup("WMShip");
	pchar.questTemp.WPU.Escort.count = 0;
	CloseQuestHeader("Escort");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	pchar.questTemp.WPU.Escort = "complete";
	ChangeCharacterComplexReputation(pchar,"nobility", -5);
	ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), -50);
}

void WM_Captain_Over(string qName)//опоздали доставить бревна и тряпки
{
	pchar.quest.Escort_Shootfail.over = "yes"; //снять прерывание
	pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-4;//скрутим счетчик за провал
	AddQuestRecord("Escort", "28");
	AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
	CloseQuestHeader("Escort");
	Group_DeleteGroup("WMShip");
	sld = characterFromId("WMCaptain");
	sld.lifiday = 0;
	DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	pchar.questTemp.WPU.Escort = "complete";
}

void RepairShip_Prepare(string qName)//подготовка к ремонту в бухте
{
	chrDisableReloadToLocation = true;//закрыть локацию
	for (i=1; i<=6; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("WMSailor"+i, "shipowner_"+i, "man", "man", 10, PIRATE, 0, true, "citizen"));
		LAi_SetCitizenType(sld);
		LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, pchar.questTemp.WPU.Current.TargetIslandID.Shore, "goto", "goto"+i);
	}
	sld = characterFromId("WMCaptain");
	LAi_SetImmortal(sld, true);//защита от дурака
	ChangeCharacterAddressGroup(sld, pchar.questTemp.WPU.Current.TargetIslandID.Shore, "goto", "goto5");
	LAi_SetActorType(sld);
	sld.dialog.Filename = "Capitans_dialog.c";
	sld.dialog.currentnode = "Repair_start";
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void RepairShip_WithoutMasts(string qName)//крутим время
{
	SetLaunchFrameFormParam(StringFromKey("GenQuests_90"), "", 0, 6);
    LaunchFrameForm();
    WaitDate("", 0, 0, 5, 0, 10); 
    RecalculateJumpTable();
	DoQuestFunctionDelay("RepairShip_Finished", 6.0);
}

void RepairShip_Finished(string qName)//чинимся и добавляемся в компаньоны
{
	pchar.quest.Escort_Shootfail.over = "yes"; //снять прерывание
	sld = characterFromId("WMCaptain");
	DeleteAttribute(sld, "ship.sails");
    DeleteAttribute(sld, "ship.blots");
    DeleteAttribute(sld, "ship.masts");
	DeleteAttribute(sld, "ship.hulls");
	SetBaseShipData(sld);
	Group_DelCharacter("WMShip", "WMCaptain");//иначе будет клон
	SetCharacterRemovable(sld, false);
	sld.CompanionEnemyEnable = false; //всегда друзья
	SetCompanionIndex(pchar, -1, sti(sld.index));
	sld.loyality = MAX_LOYALITY;
	pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
	pchar.quest.Escort_fail.win_condition.l1.character = "WMCaptain";
	pchar.quest.Escort_fail.function = "DisasterShipWM_failed";
	pchar.questTemp.WPU.Escort = "current";
	ChangeCharacterAddressGroup(sld, pchar.questTemp.WPU.Current.TargetIslandID.Shore, "goto", "goto3");
	LAi_SetActorType(sld);
	sld.dialog.Filename = "Capitans_dialog.c";
	sld.dialog.currentnode = "Repair_end";
	LAi_ActorDialog(sld, pchar, "", -1, 0); 
}

void DisasterShipWM_failed(string qName)//потеряли корабль по пути домой
{
	pchar.quest.DisasterShipWM_Over.over = "yes";
	pchar.quest.DisasterShip_final.over = "yes";
	AddQuestRecord("Escort", "23");
	CloseQuestHeader("Escort");
	pchar.questTemp.WPU.Escort.count = 1;//сильно скрутим счетчик за провал
	ChangeCharacterComplexReputation(pchar,"nobility", -1);
	ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), -2);
	if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM")) DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM");
	if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP")) DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	pchar.questTemp.WPU.Escort = "complete";
}

void DisasterShipWM_Over(string qName)//не шли домой, а маялись дурью
{
	pchar.quest.Escort_fail.over = "yes";
	pchar.quest.DisasterShip_final.over = "yes";
	RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));
	sld = characterFromId("WMCaptain");
	sld.lifeday = 0;//на всякий случай
	pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-4;//скрутим счетчик за провал
	AddQuestRecord("Escort", "22");
	AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
	CloseQuestHeader("Escort");
	if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM")) DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM");
	if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP")) DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	pchar.questTemp.WPU.Escort = "complete";
}

void WMShip_final(string qName)//финальный диалог с кэпом по прибытии в порт
{
	chrDisableReloadToLocation = true;
	bDisableFastReload = true;
	GetCharacterPos(pchar, &locx, &locy, &locz);
	sld = characterFromId("WMCaptain");
	LAi_SetImmortal(sld, true);//защита от дурака
	ChangeCharacterAddressGroup(sld, pchar.questTemp.WPU.Escort.StartCity +"_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	sld.dialog.Filename = "Capitans_dialog.c";
	if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM")) sld.dialog.currentnode = "WMShip_final";
	if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP")) sld.dialog.currentnode = "VSPShip_final";
	if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1S")) sld.dialog.currentnode = "SShip_final";
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void CreateDisasterShip_VSPirate(string qName)//создаем потерявшийся корабль в бою с пиратами
{
	pchar.quest.DesIsland_Over.over = "yes";//снять таймер
	Island_SetReloadEnableGlobal(pchar.questTemp.WPU.Current.TargetIslandID, false);
	//потерянный корабль
    Group_FindOrCreateGroup("WMShip");
	Group_SetType("WMShip", "trade");
    int iShipType, hcrew;
	iShipType = sti(pchar.questTemp.WPU.Escort.ShipType);
	sTemp = pchar.questTemp.WPU.Escort.ShipName;
	sld = GetCharacter(NPC_GenerateCharacter("WMCaptain", "citiz_41", "man", "man", sti(pchar.rank), sti(pchar.nation), -1, true, "quest"));
	FantomMakeSmallSailor(sld, iShipType, sTemp, CANNON_TYPE_CANNON_LBS12, 40, 20, 25, 30, 20);
	SetFantomParamFromRank(sld, sti(pchar.rank), true); 
	SetCaptanModelByEncType(sld, "trade");
	sld.ship.HP = makeint(sti(sld.ship.HP)/1.3);
	hcrew = GetMaxCrewQuantity(sld);
	SetCrewQuantityOverMax(sld, makeint(hcrew/1.5));
	sld.ShipEnemyDisable = true; //при попадании не враждебен
	sld.Ship.Mode = "trade";
    Group_AddCharacter("WMShip", "WMCaptain");
    Group_SetGroupCommander("WMShip", "WMCaptain");
	Group_SetAddress("WMShip", pchar.questTemp.WPU.Current.TargetIslandID, "quest_ships", "quest_ship_1");
	//пиратусы
    Group_FindOrCreateGroup("Pir_Attack");
	Group_SetType("Pir_Attack", "war");
    for (int i=1; i<=3; i++)
    {
        switch (i)
        {
			case 1:
				iShipType = SHIP_BRIG;
				iTemp = CANNON_TYPE_CANNON_LBS16;
            break;
            case 2:
				iShipType = SHIP_BRIGANTINE;
				iTemp = CANNON_TYPE_CANNON_LBS12;
            break;
            case 3:
				iShipType = SHIP_SLOOP;
				iTemp = CANNON_TYPE_CANNON_LBS12;
            break;
		}
	    sld = GetCharacter(NPC_GenerateCharacter("PirateAttack_"+i, "citiz_"+(i + 40), "man", "man", sti(pchar.rank)+5, PIRATE, 1, true, "quest"));
	    FantomMakeSmallSailor(sld, iShipType, "", iTemp, 50+rand(10), 25+rand(10), 30+rand(10), 35+rand(10), 40+rand(10));
	    SetFantomParamFromRank(sld, sti(pchar.rank)+5, true); 
		sld.ship.HP = makeint(sti(sld.ship.HP)/(1.0+frand(0.5)));//этих тоже покоцаем немного
		hcrew = GetMaxCrewQuantity(sld);
		SetCrewQuantityOverMax(sld, makeint(hcrew/(1.0+frand(0.5))));
	    Group_AddCharacter("Pir_Attack", "PirateAttack_"+i);
    }       
	Group_SetGroupCommander("Pir_Attack", "PirateAttack_1");
	Group_SetAddress("Pir_Attack", pchar.questTemp.WPU.Current.TargetIslandID, "quest_ships", "quest_ship_1");
	Group_SetTaskAttack("Pir_Attack", "WMShip");
	Group_SetTaskAttack("WMShip", "Pir_Attack");//натравим друг на друга
	Group_LockTask("WMShip");
	
	pchar.quest.DisasterShip_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.DisasterShip_AfterBattle.win_condition.l1.group = "Pir_Attack";
	pchar.quest.DisasterShip_AfterBattle.function = "DisasterShip_Win";//победа
	pchar.quest.DisasterShip_Sink.win_condition.l1 = "NPC_Death";
	pchar.quest.DisasterShip_Sink.win_condition.l1.character = "WMCaptain";
	pchar.quest.DisasterShip_Sink.function = "DisasterShip_Sink";//не спасли - утонул
	pchar.quest.DisasterShip_DieHard.win_condition.l1 = "MapEnter";
	pchar.quest.DisasterShip_DieHard.function = "DisasterShip_DieHard";//сбежали
}

void DisasterShip_Win(string qName)//победа
{
    Island_SetReloadEnableGlobal(pchar.questTemp.WPU.Current.TargetIslandID, true);
	pchar.quest.DisasterShip_Sink.over = "yes";
	pchar.quest.DisasterShip_DieHard.over = "yes";
	Group_DeleteGroup("Pir_Attack");
	AddQuestRecord("Escort", "33");
	AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
	AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
	pchar.questTemp.WPU.Escort = "toCap";
	sld = characterFromId("WMCaptain");
	LAi_SetImmortal(sld, true);
	pchar.quest.DisasterShip_GetOut.win_condition.l1 = "MapEnter";
	pchar.quest.DisasterShip_GetOut.function = "DisasterShip_GetOut";//ушли
}

void DisasterShip_GetOut(string qName)//ушли не поговорив
{
	Delete_EscortStorm();//уберем шторм
	Group_DeleteGroup("WMShip");
	AddQuestRecord("Escort", "33_1");
	CloseQuestHeader("Escort");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP");
	pchar.questTemp.WPU.Escort = "complete";
}

void DisasterShip_Sink(string qName)//утонул
{
	Delete_EscortStorm();//уберем шторм
    Island_SetReloadEnableGlobal(pchar.questTemp.WPU.Current.TargetIslandID, true);
	pchar.quest.DisasterShip_AfterBattle.over = "yes";
	pchar.quest.DisasterShip_DieHard.over = "yes";
	Group_DeleteGroup("WMShip");
	AddQuestRecord("Escort", "34");
	AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
	AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
	AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity));
	pchar.questTemp.WPU.Escort = "sink";
	pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//скрутим счетчик
}

void DisasterShip_DieHard(string qName)//сбежали
{
	Delete_EscortStorm();//уберем шторм
    Island_SetReloadEnableGlobal(pchar.questTemp.WPU.Current.TargetIslandID, true);
	pchar.quest.DisasterShip_AfterBattle.over = "yes";
	pchar.quest.DisasterShip_Sink.over = "yes";
	Group_DeleteGroup("WMShip");
	Group_DeleteGroup("Pir_Attack");
	AddQuestRecord("Escort", "35");
	AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
	AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
	AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
	CloseQuestHeader("Escort");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP");
	pchar.questTemp.WPU.Escort = "complete";
	pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-4;//скрутим счетчик за провал
}

void CreateDisasterShip_Crew(string qName)//создаем потерпевших крушение
{
	pchar.quest.DesIsland_Over.over = "yes";//снять таймер
	for (i=1; i<=7; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("WMSailor"+i, "shipowner_"+i, "man", "man", sti(pchar.rank), sti(pchar.nation), -1, true, "citizen"));
		LAi_SetCitizenType(sld);
		LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, pchar.questTemp.WPU.Current.TargetIslandID.Shore, "goto", "goto"+i);
	}
	sld = GetCharacter(NPC_GenerateCharacter("WMCaptain", "trader_"+(rand(9)+1), "man", "man", sti(pchar.rank), sti(pchar.nation), -1, true, "quest")); 
	FantomMakeCoolFighter(sld, sti(pchar.rank), 20, 20, "blade_04", "pistol6", "bullet", 30);
	LAi_SetCitizenType(sld);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, pchar.questTemp.WPU.Current.TargetIslandID.Shore, "goto", "goto1");
	LAi_SetActorType(sld);
	sld.dialog.Filename = "Quest\Other_quests_NPC.c";
	sld.dialog.currentnode = "DisasterCap";
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void DisasterShipCrew_onBoard()//добавим моряков в нашу команду
{
	for (i=1; i<=7; i++)
	{
		sld = characterFromId("WMSailor"+i);	
		sld.lifeday = 0;
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload1_boat", "none", "", "", "", 10.0);
	}
	sld = characterFromId("WMCaptain");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1_boat", "none", "", "", "", 10.0);
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, false);
	SetCrewQuantityOverMax(pchar, sti(PChar.Ship.Crew.Quantity)+55); 
	log_info(StringFromKey("GenQuests_91"));
	if (sti(pchar.ship.Crew.Morale) < 90) pchar.ship.Crew.Morale = sti(pchar.ship.Crew.Morale)+10;//поднимем мораль
	ChangeCrewExp(pchar, "Sailors", 10);
	ChangeCrewExp(pchar, "Cannoners", 10);
	ChangeCrewExp(pchar, "Soldiers", 10);//увеличим умения команде
	pchar.quest.DisasterShip_ShoreAttack.win_condition.l1 = "location";
	pchar.quest.DisasterShip_ShoreAttack.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
	pchar.quest.DisasterShip_ShoreAttack.function = "DisasterShip_AttackInShore";
}

void DisasterShipCrew_IndianAttack(string qName)//атака индеев
{
	chrDisableReloadToLocation = true; //закроем локацию
	//наши
    for (i=1; i<=7; i++)
    {
        sld = characterFromId("WMSailor"+i);
        LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    }
	sld = characterFromId("WMCaptain");
	LAi_SetWarriorType(sld);
	LAi_warrior_DialogEnable(sld, false);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	//индеи
	for (i=1; i<=7; i++)
    {
		iTemp = sti(pchar.rank) + 10;
		sld = GetCharacter(NPC_GenerateCharacter("DisasterShipIndian_"+i, "Canib_"+(rand(5)+1), "man", "man", iTemp, PIRATE, -1, true, "marginal"));
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.questTemp.WPU.Current.TargetIslandID.Shore, "reload", "reload1_back");
    }
		
    LAi_group_SetLookRadius("EnemyFight", 100);
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "DisasterShipIndian_Win");
}

void DisasterShip_AttackInShore(string qName)//атака пиратского корвета
{
	bQuestDisableMapEnter = true;//иначе нет мотивации драться в этой ситуации
	Group_FindOrCreateGroup("AttackInShore");
	Group_SetType("AttackInShore", "pirate");
	iTemp = sti(pchar.rank)+10;
	if (iTemp > 40) iTemp = 40;
	sld = GetCharacter(NPC_GenerateCharacter("AttackInShoreCaptain", "citiz_"+(rand(9)+41), "man", "man", iTemp, PIRATE, -1, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_CORVETTE, "", CANNON_TYPE_CULVERINE_LBS18, 50, 50, 50);
	FantomMakeCoolFighter(sld, iTemp, 50, 50, "blade_10", "pistol6", "bullet", 50);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.DontRansackCaptain = true; 
	sld.AlwaysEnemy = true;
	sld.AnalizeShips = true;
	Group_AddCharacter("AttackInShore", "AttackInShoreCaptain");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	
	Group_SetGroupCommander("AttackInShore", "AttackInShoreCaptain");
	Group_SetTaskAttack("AttackInShore", PLAYER_GROUP);
	Group_SetPursuitGroup("AttackInShore", PLAYER_GROUP);
	Group_SetAddress("AttackInShore", pchar.questTemp.WPU.Current.TargetIslandID, "", "");
	Group_LockTask("AttackInShore");
	
	pchar.quest.DisasterShipAttack_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.DisasterShipAttack_AfterBattle.win_condition.l1.group = "AttackInShore";
	pchar.quest.DisasterShipAttack_AfterBattle.function = "AttackInShore_Win";//победа
}

void AttackInShore_Win(string qName)//потопили пирата
{
	bQuestDisableMapEnter = false;
	Group_DeleteGroup("AttackInShore");
	AddQuestRecord("Escort", "39");
	AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
	AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
	pchar.questTemp.WPU.Escort = "win";
	pchar.quest.DisasterShip_final.win_condition.l1 = "location";
	pchar.quest.DisasterShip_final.win_condition.l1.location = pchar.questTemp.WPU.Escort.StartCity +"_town";
	pchar.quest.DisasterShip_final.function = "WMShip_final";
}

void CreateCaravanNearIsland(string qName)//защита торговцев от пиратов
{
	Island_SetReloadEnableGlobal(pchar.questTemp.WPU.Current.TargetIslandID, false);
	pchar.quest.CaravanNearIsland_Over.over = "yes";//снять таймер
	//караван торговцев
    Group_FindOrCreateGroup("CaravanShip");
	Group_SetType("CaravanShip", "trade");
    int iShipType, hcrew;
	for (int i=1; i<=3; i++)
    {
        switch (i)
        {
			case 1:
				iShipType = SHIP_PINNACE;
				iTemp = CANNON_TYPE_CANNON_LBS16;
            break;
            case 2:
				iShipType = SHIP_FLEUT + hrand(2);
				iTemp = CANNON_TYPE_CANNON_LBS12;
            break;
            case 3:
				iShipType = SHIP_SCHOONER + hrand(3);
				iTemp = CANNON_TYPE_CULVERINE_LBS8;
            break;
		}
		sld = GetCharacter(NPC_GenerateCharacter("CaravanCaptain_"+i, "trader_"+(rand(9)+1), "man", "man", sti(pchar.rank), sti(pchar.nation), 3, true, "quest"));
		FantomMakeSmallSailor(sld, iShipType, "", iTemp, 50, 25, 25, 30, 25);
		SetFantomParamFromRank(sld, sti(pchar.rank), true); 
		sld.ship.HP = makeint(sti(sld.ship.HP)/(1.0+frand(0.5)));
		hcrew = GetMaxCrewQuantity(sld);
		SetCrewQuantityOverMax(sld, makeint(hcrew/(1.0+frand(0.5))));//попортим немного
		sld.ShipEnemyDisable = true; //при попадании не враждебен
		sld.AlwaysFriend = true; // mitrokosta fix aggro
		sld.Ship.Mode = "trade";
	    Group_AddCharacter("CaravanShip", "CaravanCaptain_"+i);
	}
    Group_SetGroupCommander("CaravanShip", "CaravanCaptain_1");
	Group_SetAddress("CaravanShip", pchar.questTemp.WPU.Current.TargetIslandID, "quest_ships", "quest_ship_6");
	//пиратусы
    Group_FindOrCreateGroup("Pir_Attack");
	Group_SetType("Pir_Attack", "war");
    for (i=1; i<=4; i++)
    {
        switch (i)
        {
			case 1:
				iShipType = SHIP_CORVETTE + hrand(1);
				iTemp = CANNON_TYPE_CULVERINE_LBS18;
            break;
			case 2:
				iShipType = SHIP_BRIG + hrand(1);
				iTemp = CANNON_TYPE_CANNON_LBS16;
            break;
            case 3:
				iShipType = SHIP_BRIGANTINE + hrand(1);
				iTemp = CANNON_TYPE_CANNON_LBS16;
            break;
            case 4:
				iShipType = SHIP_SLOOP + hrand(1);
				iTemp = CANNON_TYPE_CULVERINE_LBS8;
            break;
		}
	    sld = GetCharacter(NPC_GenerateCharacter("PirateAttack_"+i, "citiz_"+(i+40), "man", "man", sti(pchar.rank)+10, PIRATE, 3, true, "quest"));
	    FantomMakeSmallSailor(sld, iShipType, "", iTemp, 50+rand(10), 25+rand(10), 30+rand(10), 35+rand(10), 40+rand(10));
	    SetFantomParamFromRank(sld, sti(pchar.rank)+10, true); 
		sld.ship.HP = makeint(sti(sld.ship.HP)/(1.0+frand(0.5)));//этих тоже попортим
		hcrew = GetMaxCrewQuantity(sld);
		SetCrewQuantityOverMax(sld, makeint(hcrew/(1.0+frand(0.5))));
	    Group_AddCharacter("Pir_Attack", "PirateAttack_"+i);
    }       
	Group_SetGroupCommander("Pir_Attack", "PirateAttack_1");
	Group_SetAddress("Pir_Attack", pchar.questTemp.WPU.Current.TargetIslandID, "quest_ships", "quest_ship_6");
	Group_SetTaskAttack("Pir_Attack", "CaravanShip");
	Group_SetTaskAttack("CaravanShip", "Pir_Attack");//натравим друг на друга
	Group_LockTask("CaravanShip");
	
	pchar.quest.CaravanShip_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.CaravanShip_AfterBattle.win_condition.l1.group = "Pir_Attack";
	pchar.quest.CaravanShip_AfterBattle.function = "CaravanShip_Win";//победа
	pchar.quest.CaravanShip_Sink.win_condition.l1 = "Group_Death";
	pchar.quest.CaravanShip_Sink.win_condition.l1.group = "CaravanShip";
	pchar.quest.CaravanShip_Sink.function = "CaravanShip_Sink";//поражение
	pchar.quest.CaravanShip_DieHard.win_condition.l1 = "MapEnter";
	pchar.quest.CaravanShip_DieHard.function = "CaravanShip_Fail";//сбежали
}

void CaravanShip_Win(string qName)//пиратские корабли потоплены
{
    Island_SetReloadEnableGlobal(pchar.questTemp.WPU.Current.TargetIslandID, true);
	Group_DeleteGroup("Pir_Attack");
	pchar.quest.CaravanShip_DieHard.over = "yes";
	pchar.quest.CaravanShip_Sink.over = "yes";
	pchar.questTemp.WPU.Escort = "win";
	//считаем не потопленных торговцев
	iTemp = 0;
    for (i=1; i<=3; i++)
    {
		sld = characterFromId("CaravanCaptain_"+i);
		if (LAi_GetCharacterHP(sld) > 0)
		{
			iTemp++;
			LAi_SetImmortal(sld, true);//для особо хитрых
		}
    }
	if (iTemp == 3) AddQuestRecord("Escort", "43");
	if (iTemp == 2) AddQuestRecord("Escort", "44");
	if (iTemp == 1) AddQuestRecord("Escort", "45");
	pchar.questTemp.WPU.Escort.LevelUp_2.Qty = iTemp;
}

void CaravanShip_Sink(string qName)//поражение
{
    Island_SetReloadEnableGlobal(pchar.questTemp.WPU.Current.TargetIslandID, true);
	Group_DeleteGroup("CaravanShip");
	pchar.quest.CaravanShip_AfterBattle.over = "yes";
	pchar.quest.CaravanShip_DieHard.over = "yes";
	AddQuestRecord("Escort", "46");
	CloseQuestHeader("Escort");
	pchar.questTemp.WPU.Escort = "complete";
	DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_2");
	pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-2;//скрутим счетчик
}

void CaravanShip_Fail(string qName)//сбежали
{
    Island_SetReloadEnableGlobal(pchar.questTemp.WPU.Current.TargetIslandID, true);
	Group_DeleteGroup("Pir_Attack");
	Group_DeleteGroup("CaravanShip");
	pchar.quest.CaravanShip_AfterBattle.over = "yes";
	pchar.quest.CaravanShip_Sink.over = "yes";
	AddQuestRecord("Escort", "47");
	CloseQuestHeader("Escort");
	pchar.questTemp.WPU.Escort = "complete";
	DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_2");
	ChangeCharacterComplexReputation(pchar,"nobility", -3);
	ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), -1);
	ChangeOfficersLoyality("bad_all", 3);
	pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-4;//скрутим счетчик за провал
}

void CaravanNearIsland_Over(string qName)//засиделись на берегу
{
	pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-4;//скрутим счетчик за провал
	AddQuestRecord("Escort", "42");
	CloseQuestHeader("Escort");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_2");
	pchar.questTemp.WPU.Escort = "complete";
}
//<-- ТТГ конец

// Captain Beltrop, 27.06.21, новый вариант при выпивке в таверне
void Tavern_SetBadHabitue()
{
	string sModel;
	if (rand(1) == 0)
	{
		sModel = "citiz_" + (31 + rand(9));
	}
	else
	{
		sModel = "citiz_" + (11 + rand(9));
	}
	rCharacter = characterFromID(pchar.questTemp.friend_in_tavern);
	LAi_Fade("", "");
	sld = GetCharacter(NPC_GenerateCharacter("Tavern_BadHabitue", sModel, "man", "man", sti(pchar.rank), sti(rCharacter.nation), 2, false, "citizen"));
	sld.dialog.filename = "Habitue_dialog.c";
	sld.dialog.currentnode = "bad_habitue";
	sld.greeting = "habitue";
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1_back");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 5.0, 0);
}

//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool GenQuests_QuestComplete(string sQuestName, string qname)
{
	ref sld, chr, npchar, rloc, shTo;
	aref arOldMapPos, arAll, arPass;
	int     iTemp, i, n, ShipType, Rank, idx, iChurchGenBanditsCount; // нужно для вычислений любых целых (нации)
    float locx, locy, locz, fTemp;
	string  attrName, Model, Blade, Gun, sTemp, sQuestTown, sQuestTitle; // любые строки для вычислений
	bool   bOk;
	
	bool condition = true;
	
	////////////////////////////////////////////////////////////////////////
	//  НАЧАЛО	ЦЕРКОВНЫЕ КВЕСТЫ
	////////////////////////////////////////////////////////////////////////
	
	// Остальное на функциях
	if (sQuestName == "Church_GenQuest2_AskedBand")
	{
		sQuestTown = PChar.GenQuest.ChurchQuest_2.QuestTown;
		PChar.GenQuest.ChurchQuest_2.AskContra_1 = true;
		sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "7");
		AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase(StringFromKey("GenQuests_92"),StringFromKey("GenQuests_93")));
		Log_TestInfo("ГГ думает, что на этом острове нужной банды нету.");
	}
	else if (sQuestName == "Church_GenQuest2_BanditsIsEnemies")
	{
		sQuestTown = PChar.GenQuest.ChurchQuest_2.QuestTown;
		iChurchGenBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
		for(i=0; i<iChurchGenBanditsCount; i++)
		{
			sld = CharacterFromID("Church_GenQuest2_Bandit_" + i);
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_Group_MoveCharacter(sld, "Church_GenQuest2_Bandits_Group");
		}
		LAi_SetFightMode(PChar, true);
		LAi_Group_SetRelation("Church_GenQuest2_Bandits_Group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_Group_FightGroups("Church_GenQuest2_Bandits_Group", LAI_GROUP_PLAYER, true);
		SetFunctionExitFromLocationCondition("Church_GenQuest2_BanditsIsEnemies_2_Clear", PChar.location, false);
		LAi_Group_SetCheckFunction("Church_GenQuest2_Bandits_Group", "Church_GenQuest2_DeadBandits");
	}
	////////////////////////////////////////////////////////////////////////
	//  КОНЕЦ	ЦЕРКОВНЫЕ КВЕСТЫ
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	
	//  Начало   Ланд энкаунтеры
	//////////////////////////////////////////////////////////////////////// 
	//------------------- банда грабителей -------------------------
	else if (sQuestName == "LandEnc_RaidersBegin") {
		LAi_SetFightMode(pchar, false);
		LAi_LockFightMode(pchar, true);
		iTemp = sti(pchar.quest.(qname).EncQty);
		sTemp = "Gang"+ pchar.quest.(qname).LocIdx + "_";
		sld = characterFromId(sTemp + "0");
		fTemp = (stf(locations[reload_location_index].locators_radius.encdetector)-3)/5;
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorDialog(sld, pchar, "", fTemp, 0); 
		for(i = 1; i < iTemp; i++)
		{
			sld = CharacterFromID(sTemp + i);				
			if (sld.id != "none")
			{
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
			}
		}
	}

	else if (sQuestName == "LandEnc_RaidersBeforeDialog") { //если выстрел до диалога
		attrName = locations[reload_location_index].index;
		sTemp = "EncRaiders_" + attrName;
		pchar.quest.(sTemp).over = "yes";
		Model = "RaidersGroup_" + attrName; //имя группы
		sTemp = "Gang"+ attrName + "_";
		for(i = 0; i < 4; i++)
		{				
			if (GetCharacterIndex(sTemp + i) == -1) continue;
			sld = CharacterFromID(sTemp + i);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetWarriorTypeNoGroup(sld);
			//LAi_group_MoveCharacter(sld, Model);
			LAi_SetImmortal(sld, false);
		}
		LAi_group_SetRelation(Model, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(Model, LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck(Model, "LandEnc_RaidersAfrer");
	}

	else if (sQuestName == "LandEnc_RaidersAfrer") { //чистим за собой		
		attrName = locations[reload_location_index].index;
		sTemp = "TimeRaiders_" + attrName;
		pchar.quest.(sTemp).over = "yes";
		sTemp = "RaidersGroup_" + attrName;			
		Delay_DeleteGroup(sTemp);
		Gun = "Raiders_" + attrName; 			
		AddSimpleRumour(LinkRandPhrase(StringFromKey("GenQuests_94", GetFullName(pchar), pchar.GenQuest.(Gun).name), 
			StringFromKey("GenQuests_95", GetFullName(pchar), pchar.GenQuest.(Gun).name), 
			StringFromKey("GenQuests_96", pchar.GenQuest.(Gun).name, GetFullName(pchar))), sti(pchar.GenQuest.(Gun).nation), 5, 1);				
		DeleteAttribute(pchar, "GenQuest." + Gun); //трем нацию и имя			
		DeleteAttribute(&locations[FindLocation(pchar.GenQuest.LandEnc.LocId)], "fire");
	}

	else if (sQuestName == "LandEnc_RaidersOver") { //чистим за собой
		sTemp = "EncRaiders_" + pchar.quest.(qname).LocIdx;
		iTemp = sti(pchar.quest.(sTemp).EncQty);
		sTemp = "Gang" + pchar.quest.(qname).LocIdx + "_";
		for(i = 0; i < iTemp; i++)
		{
			if (GetCharacterIndex(sTemp + i) == -1) continue;
			LAi_RemoveCheckMinHP(CharacterFromID(sTemp + i));
		}
		sTemp = "RaidersGroup_" + pchar.quest.(qname).LocIdx;
		LAi_group_RemoveCheck(sTemp);
		LAi_group_Delete(sTemp);
		pchar.quest.(qname).over = "yes";
		sTemp = "EncRaiders_" + pchar.quest.(qname).LocIdx;
		pchar.quest.(sTemp).over = "yes";
		sTemp = pchar.quest.(qname).LocIdx;
		DeleteAttribute(pchar, "GenQuest." + sTemp); //трем нацию и имя
		DeleteAttribute(&locations[FindLocation(pchar.GenQuest.LandEnc.LocId)], "fire");
	}
	
	//------------------- злые карибы -------------------------
	else if (sQuestName == "LandEnc_CaribBegin") {
		LAi_SetFightMode(pchar, false);
		LAi_LockFightMode(pchar, true);
		iTemp = sti(pchar.quest.(qname).EncQty);
		sTemp = "Carib"+ pchar.quest.(qname).LocIdx + "_";
		sld = characterFromId(sTemp + "0");
		fTemp = (stf(locations[reload_location_index].locators_radius.encdetector)-3)/5;
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorDialog(sld, pchar, "", fTemp, 0); 
		for(i = 1; i < iTemp; i++)
		{
			sld = CharacterFromID(sTemp + i);				
			if (sld.id != "none")
			{
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
			}
		}
	}

	else if (sQuestName == "LandEnc_CaribBeforeDialog") { //если выстрел до диалога - нападение
		attrName = locations[reload_location_index].index;
		sTemp = "EncCarib_" + attrName;
		pchar.quest.(sTemp).over = "yes";
		Model = "CaribGroup_" + attrName; //имя группы
		sTemp = "Carib"+ attrName + "_";
		for(i = 0; i < 4; i++)
		{				
			if (GetCharacterIndex(sTemp + i) == -1) continue;
			sld = CharacterFromID(sTemp + i);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetWarriorTypeNoGroup(sld);
			//LAi_group_MoveCharacter(sld, Model);
			LAi_SetImmortal(sld, false);
		}
		LAi_group_SetRelation(Model, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(Model, LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck(Model, "LandEnc_CaribAfrer");
	}
	
	else if (sQuestName == "LandEnc_MiskitoBeforeDialog") { //если выстрел до диалога - бегство
		attrName = locations[reload_location_index].index;
		sTemp = "EncCarib_" + attrName;
		pchar.quest.(sTemp).over = "yes";
		Model = "CaribGroup_" + attrName; //имя группы
		sTemp = "Carib"+ attrName + "_";
		for(i = 0; i < 4; i++)
		{				
			if (GetCharacterIndex(sTemp + i) == -1) continue;
			sld = CharacterFromID(sTemp + i);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetActorType(sld);
			LAi_SetImmortal(sld, false);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
		}
		DoQuestCheckDelay("LandEnc_CaribAfrer", 10.0);
	}

	else if (sQuestName == "LandEnc_CaribAfrer") { //чистим за собой		
		attrName = locations[reload_location_index].index;
		sTemp = "TimeCarib_" + attrName;
		pchar.quest.(sTemp).over = "yes";
		sTemp = "CaribGroup_" + attrName;			
		Delay_DeleteGroup(sTemp);
		DeleteAttribute(&locations[FindLocation(pchar.GenQuest.LandEnc.LocId)], "fire");
		ref rItm = ItemsFromID("fire");
		rItm.shown = false;
	}

	else if (sQuestName == "LandEnc_CaribOver") { //чистим за собой
		sTemp = "EncCarib_" + pchar.quest.(qname).LocIdx;
		iTemp = sti(pchar.quest.(sTemp).EncQty);
		sTemp = "Carib" + pchar.quest.(qname).LocIdx + "_";
		for(i = 0; i < iTemp; i++)
		{
			if (GetCharacterIndex(sTemp + i) == -1) continue;
			LAi_RemoveCheckMinHP(CharacterFromID(sTemp + i));
		}
		sTemp = "CaribGroup_" + pchar.quest.(qname).LocIdx;
		LAi_group_RemoveCheck(sTemp);
		LAi_group_Delete(sTemp);
		pchar.quest.(qname).over = "yes";
		sTemp = "EncCarib_" + pchar.quest.(qname).LocIdx;
		pchar.quest.(sTemp).over = "yes";
		DeleteAttribute(&locations[FindLocation(pchar.GenQuest.LandEnc.LocId)], "fire");
		rItm = ItemsFromID("fire");
		rItm.shown = false;
	}
	
	// пещерные энкаунтеры
	else if (sQuestName == "CaveEnc_RaidersBeforeDialog") { //если выстрел до диалога
		attrName = locations[reload_location_index].index;
		sTemp = "TimeCaveRaiders_" + attrName;
		pchar.quest.(sTemp).over = "yes";
		Model = "CaveGroup_" + attrName; //имя группы
		sTemp = "CaveBandos"+ attrName + "_";
		for(i=0; i<4; i++)
		{				
			if (GetCharacterIndex(sTemp + i) == -1) continue;
			sld = CharacterFromID(sTemp + i);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, Model);
		}
		LAi_group_SetRelation(Model, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(Model, LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck(Model, "CaveEnc_RaidersAfrer");
	}
	
	else if (sQuestName == "CaveEnc_RaidersAfrer") { //чистим за собой	
		chrDisableReloadToLocation = false;
		attrName = locations[reload_location_index].index;
		sTemp = "CaveGroup_" + attrName;			
		Delay_DeleteGroup(sTemp);			
		DeleteAttribute(&locations[FindLocation(pchar.GenQuest.LandEnc.LocId)], "fire");
	}
	
	else if (sQuestName == "CaveEnc_RaidersOver") { //чистим за собой
		sTemp = "CaveBandos" + pchar.quest.(qname).LocIdx + "_";
		for(i=0; i<4; i++)
		{
			if (GetCharacterIndex(sTemp + i) == -1) continue;
			LAi_RemoveCheckMinHP(CharacterFromID(sTemp + i));
		}
		sTemp = "CaveGroup_" + pchar.quest.(qname).LocIdx;
		LAi_group_RemoveCheck(sTemp);
		LAi_group_Delete(sTemp);
		pchar.quest.(qname).over = "yes";
		DeleteAttribute(&locations[FindLocation(pchar.GenQuest.LandEnc.LocId)], "fire");
	}
	
	else if (sQuestName == "CaveEnc_SkeletDie") {
		for(i=0; i<4; i++)
		{
			sld = characterFromId(sTotalTemp+i);
			LAi_KillCharacter(sld);
		}
	}
	
	//------------------- девка в джунлях -------------------------
	else if (sQuestName == "LandEnc_RapersTalk") {
		for(i = 1; i <= 3; i++)
		{
			if (GetCharacterIndex("GangMan_" + i) == -1) continue;
			sld = CharacterFromID("GangMan_" + i);
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0); 
		}
		LAi_SetFightMode(pchar, false);
		LAi_LockFightMode(pchar, true);
	}

	else if (sQuestName == "LandEnc_RapersBeforeDialog") { //если выстрел до диалога
		if (GetCharacterIndex("CangGirl") != -1) LAi_RemoveCheckMinHP(CharacterFromID("CangGirl"));			
		for(i = 1; i <= 3; i++)
		{				
			if (GetCharacterIndex("GangMan_" + i) == -1) continue;
			sld = CharacterFromID("GangMan_" + i);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
//			LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");
		sld = CharacterFromID("CangGirl");			 
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorAfraid(sld, pchar, true);
	}

	else if (sQuestName == "LandEnc_RapersAfrer") { // грохнули бандюков
		sGlobalTemp = "Saved_CangGirl";
		sld = CharacterFromID("CangGirl");
		sld.greeting = "rapers_girl_2";
		sld.dialog.currentnode = "ThanksForHelp";
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}

	else if (sQuestName == "LandEnc_RapersBadExit") {
		if (GetCharacterIndex("CangGirl") == -1) // если ГГ собственноручно прибил тетку
		{
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			AddSimpleRumour(LinkRandPhrase(StringFromKey("GenQuests_97", pchar.GenQuest.EncGirl.name), 
				StringFromKey("GenQuests_98", GetFullName(pchar), pchar.GenQuest.EncGirl.name), 
				StringFromKey("GenQuests_99", pchar.GenQuest.EncGirl.name)), sti(pchar.GenQuest.EncGirl.nation), 5, 1);			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_RemoveCheckMinHP(sld);
				sld.lifeDay = 0;
			}
		 SetFunctionTimerCondition("EncGerl_deleteisjangly", 0, 0, 30, false);	// лесник 30 дней не давать квест.					
		}
		else
		{
			if (sGlobalTemp == "Saved_CangGirl") // спасли тетку
			{
				if(pchar.GenQuest.EncGirl == "close") // .. и послали её куда подальше
				{
					characters[GetCharacterIndex("CangGirl")].lifeDay = 0;
					DeleteAttribute(pchar, "GenQuest.EncGirl");
				}
				else
				{		
					if(!CheckAttribute(pchar, "GenQuest.EncGirl.Ransom")) 
					{
						ChangeCharacterComplexReputation(pchar,"nobility", 5);
						AddSimpleRumour(LinkRandPhrase(StringFromKey("GenQuests_100", pchar.GenQuest.EncGirl.name), 
							StringFromKey("GenQuests_101", GetFullName(pchar), pchar.GenQuest.EncGirl.name), 
							StringFromKey("GenQuests_102", pchar.GenQuest.EncGirl.name, GetMainCharacterNameGen())), sti(pchar.GenQuest.EncGirl.nation), 3, 1);	
					}		
				}	
			}
			else // оставил на растерзание бандитам
			{	
				for(i = 1; i <= 3; i++)
				{
					if (GetCharacterIndex("GangMan_" + i) == -1) continue;
					sld = CharacterFromID("GangMan_" + i);
					LAi_RemoveCheckMinHP(sld);
					sld.lifeDay = 0;
				}		
				characters[GetCharacterIndex("CangGirl")].lifeDay = 0;
				if(pchar.GenQuest.EncGirl == "Begin_11")
				{
					ChangeCharacterComplexReputation(pchar,"nobility", -8);
				}
				if(pchar.GenQuest.EncGirl == "Begin_22")
				{
					ChangeCharacterComplexReputation(pchar,"nobility", -8);
				}
				if(pchar.GenQuest.EncGirl == "Begin_33")
				{
					ChangeCharacterComplexReputation(pchar,"nobility", -5);
				}
				AddSimpleRumour(RandPhraseSimple(StringFromKey("GenQuests_103", GetFullName(pchar), pchar.GenQuest.EncGirl.name), 
					StringFromKey("GenQuests_104", pchar.GenQuest.EncGirl.name)), sti(pchar.GenQuest.EncGirl.nation), 5, 1);
				DeleteAttribute(pchar, "GenQuest.EncGirl"); //трем нацию и имя	
			}
		}			
	}		
	//------------------- девка просит помочь подруге -------------------------
	else if (sQuestName == "Enc_FriendGirl_after") { //если выстрел до диалога
		ChangeCharacterComplexReputation(pchar,"nobility", -(rand(4)+1));
		if (rand(1))
		{
			AddSimpleRumour(LinkRandPhrase(StringFromKey("GenQuests_105", pchar.GenQuest.EncGirlF.name), 
				StringFromKey("GenQuests_106", GetFullName(pchar), pchar.GenQuest.EncGirlF.name), 
				StringFromKey("GenQuests_107", pchar.GenQuest.EncGirlF.name)), sti(pchar.GenQuest.EncGirlF.nation), 5, 1);
		}
	}
	//------------------- патруль в джунглях -------------------------
	else if (sQuestName == "LandEnc_PatrolBegin") {
		LAi_SetFightMode(pchar, false);
		LAi_LockFightMode(pchar, true);
		iTemp = sti(pchar.quest.(qname).EncQty);
		sTemp = "Patrol"+ pchar.quest.(qname).LocIdx + "_";
		npchar = characterFromId(sTemp + "0");
		fTemp = (stf(locations[reload_location_index].locators_radius.encdetector)-3)/5;
		LAi_SetActorTypeNoGroup(npchar);
		LAi_ActorDialog(npchar, pchar, "", fTemp, 0); 
		for(i = 1; i < iTemp; i++)
		{
			sld = characterFromId(sTemp + i);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, npchar, "", -1); 
		}
	}

	else if (sQuestName == "LandEnc_PatrolBeforeDialog") { //если выстрел до диалога
		attrName = locations[reload_location_index].index;
		sTemp = "EncPatrol_" + attrName;
		pchar.quest.(sTemp).over = "yes";
		Model = "PatrolGroup_" + attrName; //имя группы
		sTemp = "Patrol"+ attrName + "_";
		for(i = 0; i < 4; i++)
		{				
			if (GetCharacterIndex(sTemp + i) == -1) continue;
			sld = CharacterFromID(sTemp + i);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetWarriorTypeNoGroup(sld);
		}
		LAi_group_SetRelation(Model, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(Model, LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck(Model, "LandEnc_PatrolAfrer");
	}

	else if (sQuestName == "LandEnc_PatrolAfrer") { //чистим за собой
		attrName = locations[reload_location_index].index;
		sTemp = "TimePatrol_" + attrName;
		pchar.quest.(sTemp).over = "yes";
		sTemp = "PatrolGroup_" + attrName;
		Delay_DeleteGroup(sTemp);
		//слухи
		AddSimpleRumour(LinkRandPhrase(StringFromKey("GenQuests_108"), 
			StringFromKey("GenQuests_109"), 
			StringFromKey("GenQuests_110")), sti(pchar.GenQuest.(attrName).nation), 5, 1);
		AddSimpleRumour(StringFromKey("GenQuests_111", GetFullName(pchar), NationNameGenitive(sti(pchar.GenQuest.(attrName).nation)), NationNamePeople(sti(pchar.GenQuest.(attrName).nation))), sti(pchar.GenQuest.(attrName).nation)+10, 5, 1);
		DeleteAttribute(pchar, "GenQuest." + attrName); //трем нацию патруля, если есть
	}

	else if (sQuestName == "LandEnc_PatrolOver") { //чистим за собой
		sTemp = pchar.quest.(qname).LocIdx;
		//слухи
		AddSimpleRumour(LinkRandPhrase(StringFromKey("GenQuests_112", GetMainCharacterNameGen()), 
			StringFromKey("GenQuests_113"), 
			StringFromKey("GenQuests_114")), sti(pchar.GenQuest.(sTemp).nation), 5, 1);
		DeleteAttribute(pchar, "GenQuest." + sTemp); //трем нацию патруля, если есть
		sTemp = "PatrolGroup_" + pchar.quest.(qname).LocIdx;
		LAi_group_RemoveCheck(sTemp);
		LAi_group_Delete(sTemp);
		pchar.quest.(qname).over = "yes";
		sTemp = "EncPatrol_" + pchar.quest.(qname).LocIdx;
		pchar.quest.(sTemp).over = "yes";
	}

	else if (sQuestName == "DeleteGroupOnExitLocation") { //группу нулим
		sTemp = pchar.quest.DeleteGroupOnExitLocation.GroupName;
		LAi_group_Delete(sTemp);
	}

	////////////////////////////////////////////////////////////////////////
	//  Конец   Ланд энкаунтеры
	//////////////////////////////////////////////////////////////////////// 
	
	////////////////////////////////////////////////////////////////////////
	//  Начало    Уничтожение банды
	////////////////////////////////////////////////////////////////////////  
	else if (sQuestName == "AllMayorsQuests_Late") { //провальное прерывание на все квесты мэра
		sTemp = pchar.GenQuest.questName;
		pchar.quest.(sTemp).over = "yes"; //снимаем прерывание на квест
		pchar.GenQuest.(sTemp) = "Late"; //флаг опоздал
		npchar = characterFromId(pchar.GenQuest.(sTemp).MayorId);
		AddQuestRecord("MayorsQuestsList", "20");
		AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
		AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));			
	}

	else if (sQuestName == "DestroyGang_fight") {
		if (rand(1))
		{
			chrDisableReloadToLocation = true;
			Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.			
			LAi_group_Delete("EnemyFight");
			sTemp = pchar.GenQuest.questName;
			pchar.quest.(sTemp).over = "yes"; //снимаем текущее многоразовое прерывание					
			ref location = &locations[reload_location_index];
			LAi_LocationFightDisable(location, true);      //лочим возможность начать драку до диалог, это лишнее
			string encGroup = LAi_FindRandomLocator("encdetector");
			sTemp = "locators." + encGroup;
			makearef(arAll, location.(sTemp));
			iTemp = GetAttributesNum(arAll); //кол-во человек в банде
			if (iTemp <= 0 ) iTemp = 1; //если локаторов меньше четырёх
			//--> генерим ранг 
			if (sti(pchar.rank) > 6) 
			{
				if (sti(pchar.rank) > 20) Rank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*4/iTemp);
				else Rank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*2.5/iTemp);
			}
			else  
			{	//казуалам зеленый свет на начало игры
				if (sti(pchar.rank) > 3) Rank = sti(pchar.rank);
				else 
				{
					Rank = 1;
					iTemp = 1;
				}
			}	
			//<-- генерим ранг 
			string iModel[10];
			iModel[0] = "citiz_41";
			iModel[1] = "citiz_42";
			iModel[2] = "citiz_43";
			iModel[3] = "citiz_44";
			iModel[4] = "citiz_45";
			iModel[5] = "citiz_46";
			iModel[6] = "citiz_47";
			iModel[7] = "citiz_48";
			iModel[8] = "citiz_49";
			iModel[9] = "citiz_50";
			i = 0;
			while(i < iTemp)
			{
				ShipType = rand(9);
				if (iModel[ShipType] != "")
				{
					if (i == 0) 
					{   //главарь банды
						int iMainGang = NPC_GenerateCharacter("MayorQuestGang_" + i, iModel[ShipType], "man", "man", Rank, PIRATE, 0, true, "hunter");
						sld = &characters[iMainGang];
						sld.name = pchar.GenQuest.DestroyGang.name;  //имя главаря
						sld.lastname = pchar.GenQuest.DestroyGang.lastname;
						sld.dialog.filename = "MayorQuests_dialog.c";
						sld.dialog.currentnode = "DestroyGang_begin";
						sld.greeting = "banditos"; 
						sld.SaveItemsForDead   = true; // сохранять на трупе вещи
						sld.DontClearDead = true;  // не убирать труп через 200с
					}
					else sld = GetCharacter(NPC_GenerateCharacter("MayorQuestGang_" + i, iModel[ShipType], "man", "man", Rank, PIRATE, 0, true, "marginal"));
					LAi_SetActorType(sld);
					SetFantomParamFromRank(sld, Rank, true);
					//Получим локатор для логина
					attrName = GetAttributeName(GetAttributeN(arAll, i));
					ChangeCharacterAddressGroup(sld, location.id, encGroup, attrName);					
					LAi_SetActorType(sld);
					if (i == 0) LAi_ActorDialog(sld, pchar, "", -1, 0); 
					else LAi_ActorFollow(sld, &characters[iMainGang], "", -1);
					i++;
					iModel[ShipType] = "";
				}
			} 				
		}
	}

	else if (sQuestName == "DestroyGang_SuddenAttack") {
		for(i = 0; i < 4; i++)
		{
			if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
			sld = CharacterFromID("MayorQuestGang_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetImmortal(sld, false);
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "DestroyGang_Afrer");
	}

	else if (sQuestName == "DestroyGang_Afrer") {
		pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
		Delay_DeleteGroup("EnemyFight");
		makearef(arAll, pchar.GenQuest.DestroyGang);
		pchar.GenQuest.DestroyGang = "Execute"; //флаг выполнил успешно
		sTemp = GetFullName(&characters[GetCharacterIndex(arAll.MayorId)]);
		// судовой журнал
		AddQuestRecord("MayorsQuestsList", "2");
		AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.DestroyGang.MayorId)].city+"Gen"));
		AddQuestUserData("MayorsQuestsList", "MayorName", sTemp);
		AddQuestUserData("MayorsQuestsList", "GangName", GetFullName(arAll));
		// слухи
		AddSimpleRumour(LinkRandPhrase(StringFromKey("GenQuests_115", sTemp, GetMainCharacterNameDat(), GetFullName(arAll)), 
			StringFromKey("GenQuests_116", GetFullName(arAll)), 
			StringFromKey("GenQuests_117", GetMainCharacterNameDat(), GetFullName(arAll))), sti(characters[GetCharacterIndex(arAll.MayorId)].nation), 5, 1);
	}
	////////////////////////////////////////////////////////////////////////
	//  Конец    Уничтожение банды
	////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////////////////////
	//  Начало    Повод для спешки
	//////////////////////////////////////////////////////////////////////// 		
	else if (sQuestName == "ReasonToFast_PatrolDied") {
		sTemp = "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx;
		LAi_group_RemoveCheck(sTemp);
		LAi_group_Delete(sTemp);	
		if(pchar.questTemp.ReasonToFast == "PatrolAfterHunter") 
		{
			AddQuestRecord("ReasonToFast", "6");
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
		}			
		if(pchar.questTemp.ReasonToFast == "PatrolAfter")
		{				
			AddQuestRecord("ReasonToFast", "8");
		}	
		if(pchar.questTemp.ReasonToFast == "PatrolAngry")
		{
			AddQuestRecord("ReasonToFast", "4");
		}
		DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther"); //можем говорить с губером	

		pchar.quest.ReasonToFast_SpeakMayor.win_condition.l1 = "Timer";
		pchar.quest.ReasonToFast_SpeakMayor.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.ReasonToFast_SpeakMayor.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.ReasonToFast_SpeakMayor.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.ReasonToFast_SpeakMayor.function = "ReasonToFast_SpeakMayor";

		DeleteAttribute(&Locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], "DisableEncounters");
		SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), sti(pchar.questTemp.ReasonToFast.relation));
		pchar.questTemp.ReasonToFast = "PatrolDied";
		pchar.questTemp.ReasonToFast.speakAfterPatrolDied = false;
		DeleteAttribute(pchar, "GenQuest.HunterScore2Pause"); //вертаем начисление нзг
		DeleteAttribute(pchar, "GenQuest.ReputationNotChange"); //вертаем смену репы 
	}
			
	else if (sQuestName == "ReasonToFast_MeetHunter") {
		ReasonToFast_GenerateHunter();
	}
	
	else if (sQuestName == "ReasonToFast_PatrolAngry") {
		sTemp = "Patrol"+ pchar.questTemp.ReasonToFast.LocIdx + "_";
		sld = CharacterFromID(sTemp + "0");
		sld.dialog.filename = "Enc_Patrol.c";				
		sld.dialog.currentnode = "Reason_To_Fast_AfterHunter3";			
		LAi_SetActorType(pchar); 
		LAi_ActorTurnToCharacter(pchar, sld);
		LAi_SetActorType(sld);
		SetActorDialogAny2Pchar(sld.id, "", 0.0, 1.0);
		LAi_ActorFollow(sld, pchar,"ActorDialog_Any2Pchar", -1);
	}
	
	else if (sQuestName == "ReasonToFast_HunterGoOut") {
		sld = CharacterFromID("ReasonToFast_Hunter");
		LAi_SetActorType(sld); 
		LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1); 
		sld.LifeDay = 0;
		pchar.questTemp.ReasonToFast = "MeetHunterSuccess";

		sTemp = "Patrol"+ pchar.questTemp.ReasonToFast.LocIdx + "_";
		sld = CharacterFromID(sTemp + "0");
		sld.dialog.filename = "Enc_Patrol.c";				
		sld.dialog.currentnode = "Reason_To_Fast_AfterHunter1";
		LAi_SetActorType(pchar); 
		LAi_ActorTurnToCharacter(pchar, sld);
		LAi_SetActorType(sld);
		SetActorDialogAny2Pchar(sld.id, "", 0.0, 1.0);
		LAi_ActorFollow(sld, pchar,"ActorDialog_Any2Pchar", -1);
	}
			
	else if (sQuestName == "ReasonToFast_MeetWithSailor") {
		Sea_DeckBoatStartNow(pchar);
	}
	
	else if (sQuestName == "ReasonToFast_ClearVictim") {
		pchar.quest.ReasonToFast_SetShip_1.over = "yes";
		pchar.quest.ReasonToFast_SetShip_2.over = "yes";
		sld = characterFromId("VictimCap_1");
		sld.lifeDay = 0;
		Group_DeleteGroup("Sea_Victim_1");
		AddQuestRecord("ReasonToFast","19");
		CloseQuestHeader("ReasonToFast");
		DeleteAttribute(pchar,"questTemp.ReasonToFast");
	}
	
	else if (sQuestName == "ReasonToFast_TrHuntersDied") {
		LAi_group_RemoveCheck("LAND_HUNTER");
		LAi_group_Delete("LAND_HUNTER");
		bDisableLandEncounters = false;	
		if(pchar.questTemp.ReasonToFast == "GetMap")
		{
			AddQuestRecord("ReasonToFast", "21");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
			AddQuestUserData("ReasonToFast", "sText", StringFromKey("GenQuests_118"));
		}	
		if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess")
		{
			AddQuestRecord("ReasonToFast", "21");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
			AddQuestUserData("ReasonToFast", "sText", StringFromKey("GenQuests_119"));
		}
		if(pchar.questTemp.ReasonToFast == "LakeyExitFail")
		{
			AddQuestRecord("ReasonToFast", "21");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
			AddQuestUserData("ReasonToFast", "sText", StringFromKey("GenQuests_120"));
		}
		if(pchar.questTemp.ReasonToFast == "GetTreasure")
		{
			AddQuestRecord("ReasonToFast", "23");
			AddQuestUserData("ReasonToFast", "sName", GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN));
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar, "questTemp.ReasonToFast");
		}
	}
	
	else if (sQuestName == "ReasonToFast_LakeyGoOut") {
		sld = CharacterFromID("ReasonToFastLakey_1");
		LAi_SetActorType(sld); 
		LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", -1); 
		sld.LifeDay = 0;		
	}
	
	else if (sQuestName == "ReasonToFast_GoAway_Hunters_Land") {
		DoQuestCheckDelay("OpenTheDoors", 4.0);
		sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
		for (i=1; i<= sti(pchar.HunterCost.Qty); i++)
		{
			sld = characterFromID("LandHunter0" + i);
			LAi_SetActorType(sld); 
			LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "", "", 4.0);
			iTemp = GetCharacterIndex("LandHunter0" + i);
			if (iTemp != -1)
			{
				characters[iTemp].lifeDay = 0;
			}
		}
		pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
		pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
		bDisableLandEncounters = false;	
		DeleteAttribute(pchar, "questTemp.ReasonToFast");
	}

	////////////////////////////////////////////////////////////////////////
	//  Конец    Повод для спешки
	////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////////////////////
	//  Начало Тюремные квесты
	//////////////////////////////////////////////////////////////////////// 
	else if (sQuestName == "GivePrisonFree") {
		chrDisableReloadToLocation = true;
		LAi_LocationDisableMonstersGen(pchar.location, true);
		pchar.quest.GivePrisonFree_Death.over = "yes";
		sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
		sld.dialog.currentnode = "PrisonerInPlace";
		LAi_SetActorTypeNoGroup(sld);
		GetCharacterPos(sld, &locx, &locy, &locz);	
		ChangeCharacterAddressGroup(sld, pchar.location, "monsters", LAi_FindFarLocator("monsters", locx, locy, locz));
		LAi_ActorDialog(sld, pchar, "", -1, 0);		
	}

	else if (sQuestName == "GivePrisonFree_Death") {
		AddQuestRecord("GivePrisonFree", "2");
		AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
		CloseQuestHeader("GivePrisonFree");
		pchar.quest.GivePrisonFree.over = "yes";
		DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
		DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
		DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
		DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
		DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
		DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
		Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
		Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
		Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup"
	}

	else if (sQuestName == "GivePrisonFree_Over") {
		AddQuestRecord("GivePrisonFree", "6");
		AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
		CloseQuestHeader("GivePrisonFree");
		iTemp = GetCharacterIndex(pchar.questTemp.jailCanMove.prisonerId);
		if (iTemp > 0) 
		{
			characters[iTemp].lifeDay = 0;
			ChangeCharacterAddress(&characters[iTemp], "none", "");	
		}
		DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
		DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
		DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
		DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
		DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
		DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
		DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
		DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
		Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
		Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup"
	}

	else if (sQuestName == "DeliverToBander") {
		if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.City") && pchar.questTemp.jailCanMove.Deliver.City == locations[reload_location_index].fastreload)
		{
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = true;
			pchar.quest.DeliverToBander.over = "yes";
			pchar.quest.DeliverToBander_over.over = "yes";
			if (sti(pchar.rank) > 6) Rank = 8+sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
			else Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Bander_"+i, "citiz_"+(rand(9)+41), "man", "man", Rank, PIRATE, 0, true, "marginal"));
				sld.dialog.filename = "quest\Banders_dialog.c";
				sld.dialog.currentnode = "First time";
				sld.greeting = "marginal"; 
				SetFantomParamFromRank(sld, Rank, true);
				if (i == 1)
				{
					LAi_SetOwnerType(sld);
					sld.dialog.currentnode = "Second time";
					ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindFarLocator("goto", locx, locy, locz));
				}
				else
				{
					LAi_SetActorType(sld);
					sld.dialog.currentnode = "First time";
					ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
				}
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_ActorDialog(sld, pchar, "", 1.0, 0); 
		}
	}

	else if (sQuestName == "DeliverToBander_over") {
		AddQuestRecord("GivePrisonFree", "9");
		CloseQuestHeader("GivePrisonFree");
		pchar.quest.DeliverToBander.over = "yes";
		iTemp = GetCharacterIndex(pchar.questTemp.jailCanMove.Deliver.Id);
		if (iTemp > 0) ChangeCharacterAddress(&characters[iTemp], "none", "");
		DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
		TakeItemFromCharacter(pchar, "Malyava");
	}

	else if (sQuestName == "DeliverToBander_Dead") {
		AddQuestRecord("GivePrisonFree", "10");
		AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase(StringFromKey("GenQuests_66"),StringFromKey("GenQuests_67")));
		AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Deliver.name);
		CloseQuestHeader("GivePrisonFree");
		chrDisableReloadToLocation = false;
		iTemp = GetCharacterIndex(pchar.questTemp.jailCanMove.Deliver.Id);
		if (iTemp > 0) ChangeCharacterAddress(&characters[iTemp], "none", "");
		DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
		TakeItemFromCharacter(pchar, "Malyava");
	}

	else if (sQuestName == "DeletePrisonGroup") {
		LAi_group_Delete("DeliveQuest_Prison");
	}
	////////////////////////////////////////////////////////////////////////
	//  Конец  Тюремные квесты
	//////////////////////////////////////////////////////////////////////// 
	// belamour Нежелательный постоялец -->
	else if (sQuestName == "Unwantedpostor_Win") { 
		LAi_RemoveCheckMinHP(pchar);
		LAi_SetImmortal(pchar, false);
		sld = CharacterFromID("Berglar_Unwantedpostor");
		sld.dialog.currentnode = "Unwantedpostor_Win";
		LAi_SetActorType(pchar);
		LAi_SetActorType(sld);
		SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0.0, 0.0); 
		LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1); 
	}
	
	else if (sQuestName == "Unwantedpostor_Lose") { 
		LAi_RemoveCheckMinHP(pchar);
		LAi_SetImmortal(pchar, false);
		sld = CharacterFromID("Berglar_Unwantedpostor");
		sld.dialog.currentnode = "Unwantedpostor_Lose";
		LAi_SetActorType(pchar);
		LAi_SetActorType(sld);
		SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0.0, 0.0); 
		LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1); 
	}
	// <-- belamour Нежелательный постоялец 
	
	// belamour ночной приключенец -->
	else if (sQuestName == "NightAdventure_OpenLoc") { 
		LAi_SetPlayerType(pchar);
		pchar.quest.NightAdventure_JungleExit.over = "yes"; 
		pchar.quest.NightAdventure_SeaExit.over = "yes"; 
		chrDisableReloadToLocation = false;
		if(CheckAttribute(pchar,"GenQuest.CantRun")) DeleteAttribute(pchar,"GenQuest.CantRun");
	}
	
	else if (sQuestName == "NightAdventure_PiratesSpeak") { 
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID(pchar.GenQuest.NightAdventureId);
		sld.nation = PIRATE;
		sld.dialog.currentnode = "NightAdventure_PirateCave_7";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "NightAdventure_NobleGameDialogPrep") { 
		sld = characterFromId(pchar.GenQuest.NightAdventureId);
		ChangeCharacterAddressGroup(sld, pchar.location, "sit", "sit_front4");
		LAi_SetActorType(sld);
		LAi_ActorSetSitMode(sld);
		//if(CheckAttribute(pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
		ChangeCharacterAddressGroup(pchar, pchar.location, "sit", "sit_base4");
		LAi_SetSitType(pchar);
		
	}
	
	else if (sQuestName == "NightAdventure_NobleGameDialog") { 
		ChangeCharacterAddressGroup(pchar, pchar.location, "sit", "sit_base4"); 
		sld = characterFromId(pchar.GenQuest.NightAdventureId);
		sld.dialog.currentnode = "NightAdventure_NobleGame_7";
		LAi_SetActorType(sld);
		LAi_ActorSetSitMode(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.5);
	}
	
	else if (sQuestName == "NightAdventure_GameRes") { 
		if (CheckAttribute(pchar, "questTemp.NA.Cards.Win"))
		{
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_NobleGame_Win";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
		}
		else
		{
			if (CheckAttribute(pchar, "questTemp.NA.Cards.Fail"))
			{
				sld = characterFromId(pchar.GenQuest.NightAdventureId);
				sld.dialog.currentnode = "NightAdventure_NobleGame_Lose";
				LAi_ActorSetSitMode(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				DeleteAttribute(pchar, "questTemp.NA.Cards");
				chrDisableReloadToLocation = false; // открыть локацию
				LAI_SetPlayerType(pchar);           
				DoQuestReloadToLocation(pchar.location, "tables", "stay4", "");
				sld = characterFromId(pchar.GenQuest.NightAdventureId);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
		}
	}
	
	else if (sQuestName == "NightAdventure_OpenBrothel") { 
		DeleteAttribute(pchar, "GenQuest.CannotWait");
		sld = characterFromId(pchar.GenQuest.NightAdventureId);
		if(sld.city != "Charles" || sld.city != "Tortuga") 
		{
			LocatorReloadEnterDisable(sld.city+"_town", "reload91", false);
		}
		LocatorReloadEnterDisable(sld.city + "_Brothel", "reload1_back", false); 
		LocatorReloadEnterDisable(sld.city + "_SecBrRoom", "reload2", false); 
		chrDisableReloadToLocation = false; // открыть локацию
		bDisableFastReload = false;
		SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
	}
	// <-- belamour ночной приключенец 
	else
	{
		condition = false;
	}
	
	return condition;
}
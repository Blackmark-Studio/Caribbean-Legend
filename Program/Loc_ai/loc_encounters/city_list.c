
// Распихать капитанов по городским зданиям
// Максимальное количество подвязано на IslandShips, хотя в итоге тут другие персонажи
void FillIslandCapsInTown(ref rColony)
{
    aref arList = touchattr(rColony.IslandCaps);
    if (@arList == 0) return;

    // Набор доступных локаций
    string sCity = rColony.id, sLoc, sPlaces[];
    string sLocs[] = {"Store", "Shipyard", "Brothel", "Townhall", "Bank", "PortOffice"};
    for(int i = 0; i < @sLocs; i++)
    {
        sLoc = sCity + "_" + sLocs[i];
        if (FindLocation(sLoc) >= 0)
            sPlaces += sLoc;
    }
    ArrayShuffle(&sPlaces);

    // Распихать кэпов
    int iCapNum = 0;
    for(int i = 0; i < @sPlaces; i++)
    {
        if (50 > rand(99))
        {
            PlaceCapVisitorInLoc(rColony, sCity, sPlaces[i]);
            iCapNum++;
            if (iCapNum >= @arList)
                return;
        }
    }
}

bool CapVisitors_Check(ref this, ref loc)
{
    return !chrDisableReloadToLocation && !LAi_grp_alarmactive && LAi_IsCharacterControl(PChar);
}

void CapVisitors_Handler(ref this)
{
    ClearPostEventsForEvent("CapVisitors_Exit");
    int iDelay = this.LoginCallback.Timer;
    PostEvent("CapVisitors_Exit", iDelay * 1000, "e", this);

    aref ExitCond = touchattr(PChar.Quest.CapVisitors_ExitCheck);
    ExitCond.win_condition.l1 = "ExitFromLocation";
    ExitCond.win_condition.l1.location = loadedLocation.id;
    ExitCond.function = "CapVisitors_ExitCheck";
    ExitCond.CapId = this.id;
}

void CapVisitors_ExitAfterDialog()
{
    string id = TEV.CapVisitorId;
    DeleteAttribute(&TEV, "CapVisitorId");
    ref chr = CharacterFromId(id);
    int iSec = 10 + rand(5);
    PostEvent("CapVisitors_Exit", iSec * 1000, "e", chr);
}

#event_handler("CapVisitors_Exit","CapVisitors_Exit");
void CapVisitors_Exit(ref chr)
{
    DeleteAttribute(chr, "LoginCallback.Timer");
    if (dialogRun && CharacterRef.id == chr.id)
    {
        TEV.CapVisitorId = chr.id;
        AddDialogExitQuestFunction("CapVisitors_ExitAfterDialog");
        return;
    }
    if (LAi_IsFightMode(chr))
    {
        return;
    }
    // Ищем подходящий локатор для выхода
    aref locatorsGroup = &loadedLocation.locators.reload;
    string locator = "reload1"; // По умолчанию должен быть таким
    if (locator !in locatorsGroup)
    {   // Если почему-то не оказалось
        if ("reload1_back" in locatorsGroup)
        {
            locator = "reload1_back";
        }
        else
        {
            float x, y, z;
            GetCharacterPos(chr, &x, &y, &z);
            locator = LAi_FindNearestLocator("reload", x, y, z);
        }
    }
	LAi_SetActorTypeNoGroup(chr);
    LAi_ActorGoToLocation(chr, "reload", locator, "none", "", "", "", -1.0);
}

void CapVisitors_ExitCheck(string sQuestAttr)
{
    ClearPostEventsForEvent("CapVisitors_Exit");
    aref info = &PChar.Quest.(sQuestAttr);
    string CapId = info.CapId;
    ref chr = CharacterFromIDSafe(CapId, true);
    if (chr == nullptr || LAi_IsDead(chr))
    {
        return;
    }
    // Уходил с локации, либо виделись два раза
    if ("LoginCallback.Timer" !in chr || "SecondAppearance" in chr)
    {
        chr.lifeDay = 0;
        return;
    }
    chr.SecondAppearance = "";
    chr.LoginCallback.Timer := rand(60);
}

void PlaceCapVisitorInLoc(ref rColony, string sCity, string sLoc)
{
    ref loc = &Locations[FindLocation(sLoc)];
    int iNation = GetCityNation(sCity), iCharNation;
    bool bHeroOwn = bool(rColony.HeroOwn);
    string sGroup = !bHeroOwn ? GetNationNameByType(iNation)  + "_citizens" : LAI_GROUP_PLAYER_OWN; 

    string sType;
    int iFriendNation = FindNonEnemyNation2NationWithoutPirates(iNation);
    if (iFriendNation == -1)
        iFriendNation = iNation;
    bool foreignerCap = false;
    switch(rand(3))
    {
        case 0:
            iCharNation  = iFriendNation;
            sType = "war";
            foreignerCap = iCharNation != iNation;
            break;
        case 1:
            iCharNation  = iNation;
            sType = "war";
            break;
        case 2:
            iCharNation = rand(1) || bHeroOwn ? iNation : iFriendNation;
            sType = "trade";
            break;
        case 3:
            iCharNation = PIRATE;
            sType = "pirate";
            break;
    }

    if (sType == "war" && bHeroOwn)
    {
        iCharNation = PIRATE;
        sType = "pirate";
        foreignerCap = false;
    }

    int iRank = int(PChar.Rank) + rand(MOD_SKILL_ENEMY_RATE / 2);
    ref chr = GetCharacter(NPC_GenerateCharacter("CapVisitor_" + sLoc, "", "man", "man", iRank, iNation, ISLAND_SHIPS_DAYS, false, "quest"));
    if (sType != "war")
    {
        SetCaptanModelByEncType(chr, sType);
    }
    else
    {
        chr.model = "off_" + NationShortName(iNation) + "_" + (1 + rand(4));
        chr.PhantomType = "officer";
        FaceMaker(chr);
    }
    SetFantomParamFromRank(chr, iRank, true);

    chr.Location = sLoc;
    chr.Location.Group = "goto";
    chr.RandomPlace = "";
    chr.LoginCondition := &CapVisitors_Check;
    chr.LoginCallback  := &CapVisitors_Handler;
    chr.LoginCallback.Timer := rand(120);
    LAi_SetLoginTime(chr, 6.0, 21.99);

    chr.City = sCity;
    chr.CapType = foreignerCap ? "WarForeigner" : sType;
    chr.Dialog.Filename = "Encounters\Visitor_Cap.c";
    chr.Dialog.CurrentNode = "First Time";
    chr.Greeting = "Captain";
    CapVisitors_GenerateItem(chr);
    if (rand(99) >= 20)
        chr.CapAdvice = "";

    LAi_SetCitizenType(chr);
    LAi_group_MoveCharacter(chr, sGroup);
    ForceAutolevel(chr, GEN_TYPE_ENEMY, GEN_ELITE, GEN_ARCHETYPE_RANDOM, GEN_ARCHETYPE_RANDOM, GEN_RANDOM_PIRATES, 0.6);

    /*if (MOD_BETTATESTMODE == "On")
        Log_Info("Кэп-посетитель будет в " + sLoc);*/
}

void CapVisitors_GenerateItem(ref chr)
{
    int Distribution[] = CheckMapParts() ? {15, 25, 20, 25, 15} : {0, 25, 20, 25, 15};
    int iType = WeightRandomMethod(&Distribution);
    switch(iType)
    {
        case 0: // 15% Половинка
            chr.CapItem = "MapPart";
            chr.CapItem.Type = "MapPart";
            chr.CapItem.Qty = 1;
            chr.CapItem.Price = 60 + rand(20);
            chr.CapItem.Price.Dublons = "";
            break;
        case 1: // 25% Случайный амулет
            chr.CapItem = RandPhrase("indian_", "amulet_", "obereg_") + (1 + rand(10));
            chr.CapItem.Type = "Amulet";
            chr.CapItem.Qty = 1;
            chr.CapItem.Price = 2000 + rand(1500);
            break;
        case 2: // 20% Обычная карта
            string maps[] = {"map_jam", "map_cayman", "map_barbados", "map_trinidad", "map_Curacao", "map_martiniqua", "map_dominica", "map_puerto", "map_cuba", "map_hisp", "map_nevis", "map_guad", "map_antigua", "map_TORTUGA", "map_terks", "map_sm", "map_bermudas", "map_beliz", "map_santa", "map_maine_1", "map_maine_2", "map_panama", "map_cumana"};
            chr.CapItem = maps[rand(@maps - 1)];
            chr.CapItem.Type = "Map";
            chr.CapItem.Qty = 1;
            chr.CapItem.Price = 5000 + rand(3000);
            break;
        case 3: // 25% Adder stone
            chr.CapItem = "talisman11";
            chr.CapItem.Type = "AdderStone";
            chr.CapItem.Qty = 2 + rand(1);
            chr.CapItem.Price = 1000 + rand(500);
            break;
        case 4: // 15% Ничего
            break;
    }
}

bool CapVisitors_ItemCheck(ref chr)
{
    if ("CapItem" !in chr)
        return false;

    if (chr.CapItem == "MapPart")
        return CheckMapParts();

    return true;
}

void CapVisitors_AdviceBonus(ref chr)
{
    int iRank = PChar.Rank;
    switch(chr.CapType)
    {
        case "war":
        case "WarForeigner":
            AddCharacterExpToSkill(PChar, SKILL_CANNONS, 5 + hrand(iRank * 3));
            AddCharacterExpToSkill(PChar, SKILL_DEFENCE, 5 + hrand(iRank * 3));
            break;
        case "trade":
            AddCharacterExpToSkill(PChar, SKILL_COMMERCE, 5 + hrand(iRank * 4));
            break;
        case "pirate":
            AddCharacterExpToSkill(PChar, SKILL_GRAPPLING, 5 + hrand(iRank * 3));
            AddCharacterExpToSkill(PChar, SKILL_REPAIR, 5 + hrand(iRank * 3));
            break;
    }
}

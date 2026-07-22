
// NONE
bool JungleEncCheck_None(ref loc, aref grp) { return true; }
void JungleEncGenerate_None(ref loc, string sAreal, string sCity, int iNation, aref grp, string encGroup){}

// BITCH
bool JungleEncCheck_Bitch(ref loc, aref grp)
{
    if ("GenQuest.EncGirl" in PChar)
        return false;		
    if ("questTemp.Sharlie.DefendSP" in PChar)
        return false;
    if ("locators.reload.reloadW_back" in loc)
    {
        aref arRld = touchattr(loc.reload);
        for (int i = 0; i < @arRld; i++)
        {
            if (arRld[i].name == "reloadW_back")
                return true;
        }
        return false;
    }

    return @grp >= 2;
}

void JungleEncGenerate_Bitch(ref loc, string sAreal, string sCity, int iNation, aref grp, string encGroup)
{
    // Кол-во локаторов
    int num = @grp; 

    ref chr;
    int iRank, iChar;
    string locator, str;
    if ("locators.reload.reloadW_back" !in loc) // Обычная девка в джунглях
    {
        // Ранг
        if (int(PChar.Rank) > 6)
        {
            if (int(PChar.Rank) > 20) iRank = int(PChar.Rank) + int(MOD_SKILL_ENEMY_RATE * 2.5 / num);
            else iRank = int(PChar.Rank) + int(MOD_SKILL_ENEMY_RATE * 1.6 / num);
        }
        else iRank = int(PChar.Rank);
 
        // Обновим боевой ИИ
        LAi_group_Delete("EnemyFight");
        LAi_group_Delete("LandEncGroup");
        LAi_LocationFightDisable(loc, true);
        LAi_SetFightMode(PChar, false);
        LAi_LockFightMode(PChar, true);
        chrDisableReloadToLocation = true;

        // Модельки
        string model[] = {"citiz_41", "citiz_42", "citiz_43", "citiz_44", "citiz_45", "citiz_46", "citiz_47", "citiz_48", "citiz_49", "citiz_50"};
        ArrayShuffle(&model);

        // Создаём персонажей
        for (int i = 0; i < num; i++)
        {
            locator = GetAttributeName(GetAttributeN(grp, i));
            if (i == 0)
            {
                // Выбрать вариант начала квеста
                switch(rand(2))
                {
                    case 0:
                        Log_QuestInfo("Девица в джунглях : сгенерился вариант 1");
                        iChar =	NPC_GenerateCharacter("CangGirl", "women_"+(rand(5)+11), "woman", "towngirl", 5, iNation, -1, false, "citizen");
                        chr = &characters[iChar];
                        chr.dialog.filename = "Enc_RapersGirl_dialog.c";
                        chr.dialog.currentnode = "Begin_1";
                        PChar.GenQuest.EncGirl = "Begin_1";
                        break;
                    case 1:	
                        Log_QuestInfo("Девица в джунглях : сгенерился вариант 2");	
                        iChar =	NPC_GenerateCharacter("CangGirl", "women_"+(rand(5)+11), "woman", "towngirl", 5, iNation, -1, false, "citizen");
                        chr = &characters[iChar];
                        chr.dialog.filename = "Enc_RapersGirl_dialog.c";
                        chr.dialog.currentnode = "Begin_2";
                        PChar.GenQuest.EncGirl = "Begin_2";
                        PChar.GenQuest.EncGirl.Horse = true;									
                        break;
                    case 2:								
                        Log_QuestInfo("Девица в джунглях : сгенерился вариант 3");
                        iChar =	NPC_GenerateCharacter("CangGirl", "women_"+(rand(5)+11), "woman", "towngirl", 5, iNation, -1, false, "citizen");
                        chr = &characters[iChar];
                        chr.dialog.filename = "Enc_RapersGirl_dialog.c";
                        chr.dialog.currentnode = "Begin_3";
                        PChar.GenQuest.EncGirl = "Begin_3";
                        break;								
                }

                // Параметры девки
                chr.name = GenerateRandomName_Generator(iNation, "woman");			
                chr.lastname = "";
                chr.greeting = "rapers_girl_1";
                ChangeCharacterAddressGroup(chr, loc.id, encGroup, locator);
                LAi_SetActorType(chr);
                LAi_group_MoveCharacter(chr, "LandEncGroup");
                LAi_ActorDialog(chr, PChar, "", -1, 0);  
                LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, false, "LandEnc_RapersBeforeDialog");
                PChar.GenQuest.EncGirl.city = sCity; //  город девицы
                PChar.GenQuest.EncGirl.nation = iNation; //нация для слухов 
                PChar.GenQuest.EncGirl.name = GetFullName(chr); //имя девицы
                PChar.GenQuest.EncGirl.LocIdx = loc.index; 
                chr.city = sCity;

                // Далее бандиты
                continue;
            }
            
            // Параметры бандитов
            chr = GetCharacter(NPC_GenerateCharacter("GangMan_" + i, model[i], "man", "man", iRank, PIRATE, 100, true, "marginal"));
            SetFantomParamFromRank(chr, iRank, true);
            ForceAutolevel(chr, GEN_TYPE_ENEMY, GEN_COMMONER, GEN_ARCHETYPE_RANDOM, GEN_ARCHETYPE_RANDOM, GEN_RANDOM_PIRATES, 0.6); // RB Бандиты в джунглях
            chr.dialog.filename = "Enc_Rapers_dialog.c";
            chr.dialog.currentnode = "First time";
            chr.greeting = "banditos";
            chr.role = "banditos";
            ChangeCharacterAddressGroup(chr, loc.id, encGroup, locator);
            LAi_SetActorType(chr);
            LAi_group_MoveCharacter(chr, "EnemyFight");
            LAi_ActorFollow(chr, &characters[iChar], "", -1);
            LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, false, "LandEnc_RapersBeforeDialog");
        }
        int iRnd = int(PChar.Rank) > 10 ? 2 : 1;
        PChar.GenQuest.EncGirl.variant = rand(iRnd);	
        PChar.GenQuest.EncGirl.item = GenQuest_GenerateArtefact();
        PChar.GenQuest.EncGirl.sum  =  500 * (int(PChar.Rank) + 10) + rand(5000);
        sGlobalTemp = ""; // ~!~ Состояние квеста на выходе из локации, нулим

        // Сюрприз для любителей просто свалить из локации (TO_DO: DEL?)
        PChar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
        PChar.quest.LandEnc_RapersBadExit.win_condition.l1.location = PChar.location;
        PChar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
    }
    else // Замануха в колодец
    {
        // Обновим боевой ИИ
        LAi_group_Delete("LandEncGroup");

        // ID локации, куда ведет колодец
        // Проверка в isValid гарантирует, что найдётся
        aref arRld = touchattr(loc.reload);
        for (int i = 0; i < @arRld; i++)
        {
            if (arRld[i].name == "reloadW_back")
            {
                str = arRld[i].go;
                break;
            }
        }

        // Создать девку
        locator = GetAttributeName(GetAttributeN(grp, 1));
        chr = GetCharacter(NPC_GenerateCharacter("FriendGirl", "women_"+(rand(5)+11), "woman", "towngirl", 5, iNation, 0, false, "citizen"));
        chr.dialog.filename = "Enc_FriendGirl_dialog.c";
        chr.dialog.currentnode = "First time";
        chr.greeting = "rapers_girl_1";
        ChangeCharacterAddressGroup(chr, loc.id, encGroup, locator);
        LAi_SetActorType(chr);
        LAi_group_MoveCharacter(chr, "LandEncGroup");
        LAi_ActorDialog(chr, PChar, "", -1, 0); 
        PChar.GenQuest.EncGirlF.locationId = str; // ID локации
        PChar.GenQuest.EncGirlF.nation = iNation; // Нация для слухов 
        PChar.GenQuest.EncGirlF.name = GetFullName(chr); // Имя девки
        PChar.quest.Enc_FriendGirl_after.win_condition.l1 = "NPC_Death";
        PChar.quest.Enc_FriendGirl_after.win_condition.l1.character = "FriendGirl";
        PChar.quest.Enc_FriendGirl_after.win_condition = "Enc_FriendGirl_after";
    }
}

// FIGHT
bool JungleEncCheck_Fight(ref loc, aref grp)
{
    // Не на тесном пляже, только сельва
    return loc.type != "seashore" && loc.type != "mayak";
}

void JungleEncGenerate_Fight(ref loc, string sAreal, string sCity, int iNation, aref grp, string encGroup)
{
    string FightGroups[] = {"Patrol", "Caribs", "Pirates,Smugglers"}; // "Patrol,Soldiers", "Miskito,Caribs"
    ArrayShuffle(&FightGroups);
    string sType_1 = GetRandSubString(FightGroups[0]), sGroup_1 = "JungFightGroup_A";
    string sType_2 = GetRandSubString(FightGroups[1]), sGroup_2 = "JungFightGroup_B";
    LAi_group_Delete(sGroup_1);
    LAi_group_Delete(sGroup_2);
    call ("JungFightGen_" + sType_1)(iNation, sGroup_1, sType_2, loc, grp, encGroup);
    call ("JungFightGen_" + sType_2)(iNation, sGroup_2, sType_1, loc, grp, encGroup);
    LAi_group_SetReaction(sGroup_1, "JungFightPlayerAttack");
    LAi_group_SetReaction(sGroup_2, "JungFightPlayerAttack");
    LAi_group_FightGroups(sGroup_1, sGroup_2, false);
    // Временный бонус, чтобы союзники не тупили, если вступить в битву
	LAi_group_SetHearRadius(LAI_GROUP_PLAYER, 40000000.0);
	LAi_group_SetSayRadius(LAI_GROUP_PLAYER, 40000000.0);
    // Убрать всё лишнее по выходу
    PChar.Quest.JungFight_Clear.win_condition.l1 = "ExitFromLocation";
    PChar.Quest.JungFight_Clear.win_condition.l1.location = PChar.location;
    PChar.Quest.JungFight_Clear.function = "JungFight_Clear";
    // Вариант слухов
    TEV.JungFightRumour = "Fight";
    TEV.JungFightRumour.City = sCity;
    TEV.JungFightRumour.g1 = sType_1;
    TEV.JungFightRumour.g2 = sType_2;
}

void JungFight_Clear(string qName)
{
    LAi_group_Delete("JungFightGroup_A");
    LAi_group_Delete("JungFightGroup_B");
    // Delete conditions
    LAi_group_RemoveCheck("JungFightGroup_A");
    LAi_group_RemoveCheck("JungFightGroup_B");
    LAi_group_RemoveReaction("JungFightGroup_A");
    LAi_group_RemoveReaction("JungFightGroup_B");
    // Restore player group
    LAi_group_SetSayRadius(LAI_GROUP_PLAYER, LAI_GROUP_PLA_SAY);
	LAi_group_SetHearRadius(LAI_GROUP_PLAYER, LAI_GROUP_PLA_HEAR);
    // Rumour
    bool bRumour = false;
    string file = "Dialogs\Encounters\JungFight.txt";
    string text, sCity = TEV.JungFightRumour.City;
    string Winners = TEV.JungFightRumour.Winners$string("");
    string Losers  = TEV.JungFightRumour.Losers$string("");
    string sTypes[2];
    sTypes[0] = TEV.JungFightRumour.g1, sTypes[1] = TEV.JungFightRumour.g2;
    ArraySort(&sTypes); // for "_vs_" keys lexicographic order
    switch(TEV.JungFightRumour)
    {
        case "Fight":
            bRumour = rand(2) == 1;
            text = DLG_Convert("JungFight_Rumour_" + sTypes[0] + "_vs_" + sTypes[1], file);
            break;
        case "HeroHelp":
            bRumour = rand(1) == 1 && Winners == "Patrol";
            text = DLG_Convert("JungFight_Rumour_HeroHelp_Patrol_" + Losers, file);
            break;
        case "AllDead":
            bRumour = rand(2) == 1;
            if (sTypes[0] == "Patrol" || sTypes[1] == "Patrol")
                text = DLG_Convert("JungFight_Rumour_AllDead_Patrol", file);
            else
                text = DLG_Convert("JungFight_Rumour_AllDead", file);
            break;
    }
    if (bRumour)
        AddSimpleRumourCity(text, sCity, 5, 1, "");
    DeleteAttribute(&TEV, "JungFightRumour");
}

void JungFightGen_Patrol(int iNation, string sGroup, string sEnemies, ref loc, aref grp, string encGroup)
{
    int iQty = 4 + rand(2), iLocator;
    string sNat = NationShortName(iNation);
    string model[8], sOffModel = "off_"  + sNat + "_" + (rand(1)+1), sMushModel = "mush_" + sNat + "_" + (rand(2)+1);
    for(int i = 0; i < 8; i++) model[i] = "sold_" + sNat + "_" + (i+1);
    ArrayShuffle(&model);

    ref chr;
    string locator;
    for(int i = 0; i < iQty; i++)
    {
        int iRank = int(PChar.Rank) + rand(MOD_SKILL_ENEMY_RATE);
        if (i == 0)
        {   // Офицер
            iRank += 2;
            chr = GetCharacter(NPC_GenerateCharacter("JF_Officer", sOffModel, "man", "man", iRank, iNation, 0, true, "officer"));
            SetFantomParamFromRank(chr, iRank, true);
        }
        else if (i == 1 && rand(1))
        {   // Мушкетёр
            chr = GetCharacter(NPC_GenerateCharacter("JF_Patrol_1", sMushModel, "man", "mushketer", iRank, iNation, 0, false, "soldier"));
        }
        else
        {   // Солдаты
            chr = GetCharacter(NPC_GenerateCharacter("JF_Patrol_" + i, model[i], "man", "man", iRank, iNation, 0, true, "soldier"));
            SetFantomParamFromRank(chr, iRank, true);
        }
        chr.dialog.filename = "Encounters\JungFight.c";
        chr.greeting = "protector"; // ~!~
        chr.role = "patrol";
        chr.JungFightType = "patrol";
        chr.JungFightEnemies = sEnemies;
        LAi_SetWarriorType(chr);
        ForceAutolevel(chr, GEN_TYPE_ENEMY, GEN_COMMONER, GEN_ARCHETYPE_RANDOM, GEN_ARCHETYPE_RANDOM, GEN_RANDOM_PIRATES, 0.6);
        if (i != 0) LAi_warrior_SetCommander(chr, CharacterFromId("JF_Officer"));
        LAi_group_MoveCharacter(chr, sGroup);
        iLocator = rand(@grp - 1); // i % @grp;
        locator = nameattr(grp[iLocator]);
        ChangeCharacterAddressGroup(chr, loc.id, encGroup, locator);
        if (IsMusketer(chr)) JungFightSetRandCharge(chr);
    }
}

void JungFightGen_Caribs(int iNation, string sGroup, string sEnemies, ref loc, aref grp, string encGroup)
{
    int iQty = 4 + rand(2), iLocator;
    string model[6], sMushModel = "mush_cnb_" + (rand(2)+1);
    for(int i = 0; i < 6; i++) model[i] = "canib_" + (i+1);
    ArrayShuffle(&model);

    ref chr;
    string locator;
    for(int i = 0; i < iQty; i++)
    {
        int iRank = int(PChar.Rank) + rand(MOD_SKILL_ENEMY_RATE);
        if (i == 1 && rand(1))
        {   // Мушкетёр
            chr = GetCharacter(NPC_GenerateCharacter("JF_Caribs_1", sMushModel, "man", "mushketer", iRank, PIRATE, 0, false, "native"));
        }
        else
        {   // Солдаты
            chr = GetCharacter(NPC_GenerateCharacter("JF_Caribs_" + i, model[i], "man", "man", iRank, PIRATE, 0, true, "native"));
            SetFantomParamFromRank(chr, iRank, true);
        }
        chr.name = GetIndianName(MAN);
        chr.lastname = "";
        chr.dialog.filename = "Encounters\JungFight.c";
        chr.greeting = "indiano";
        chr.JungFightType = "Caribs";
        chr.JungFightEnemies = sEnemies;
        LAi_SetWarriorType(chr);
        ForceAutolevel(chr, GEN_TYPE_ENEMY, GEN_COMMONER, GEN_ARCHETYPE_RANDOM, GEN_ARCHETYPE_RANDOM, GEN_RANDOM_PIRATES, 0.6);
        LAi_group_MoveCharacter(chr, sGroup);
        iLocator = rand(@grp - 1); // i % @grp;
        locator = nameattr(grp[iLocator]);
        ChangeCharacterAddressGroup(chr, loc.id, encGroup, locator);
        if (IsMusketer(chr)) JungFightSetRandCharge(chr);
    }
}

void JungFightGen_Pirates(int iNation, string sGroup, string sEnemies, ref loc, aref grp, string encGroup)
{
    int iQty = 4 + rand(2), iLocator;
    string model[10], sMushModel = "mush_ctz_" + (7+rand(2));
    for(int i = 0; i < 10; i++) model[i] = "citiz_" + (41 + i);
    ArrayShuffle(&model);

    ref chr;
    string locator;
    for(int i = 0; i < iQty; i++)
    {
        int iRank = int(PChar.Rank) + rand(MOD_SKILL_ENEMY_RATE);
        if (i == 1 && rand(1))
        {   // Мушкетёр
            chr = GetCharacter(NPC_GenerateCharacter("JF_Pirates_1", sMushModel, "man", "mushketer", iRank, PIRATE, 0, false, "marginal"));
        }
        else
        {   // Солдаты
            chr = GetCharacter(NPC_GenerateCharacter("JF_Pirates_" + i, model[i], "man", "man", iRank, PIRATE, 0, true, "marginal"));
            SetFantomParamFromRank(chr, iRank, true);
        }
        chr.dialog.filename = "Encounters\JungFight.c";
        chr.greeting = "town_pirate"; // ~!~
        chr.role = "marginal_town";   // ~!~
        chr.JungFightType = "Pirates";
        chr.JungFightEnemies = sEnemies;
        LAi_SetWarriorType(chr);
        ForceAutolevel(chr, GEN_TYPE_ENEMY, GEN_COMMONER, GEN_ARCHETYPE_RANDOM, GEN_ARCHETYPE_RANDOM, GEN_RANDOM_PIRATES, 0.6);
        LAi_group_MoveCharacter(chr, sGroup);
        iLocator = rand(@grp - 1); // i % @grp;
        locator = nameattr(grp[iLocator]);
        ChangeCharacterAddressGroup(chr, loc.id, encGroup, locator);
        if (IsMusketer(chr)) JungFightSetRandCharge(chr);
    }
}

void JungFightGen_Smugglers(int iNation, string sGroup, string sEnemies, ref loc, aref grp, string encGroup)
{
    int iQty = 4 + rand(2), iLocator;
    string model[10], sMushModel = "mush_ctz_" + (1+rand(2));
    for(int i = 0; i < 10; i++) model[i] = "citiz_" + (21 + i);
    ArrayShuffle(&model);

    ref chr;
    string locator;
    for(int i = 0; i < iQty; i++)
    {
        int iRank = int(PChar.Rank) + rand(MOD_SKILL_ENEMY_RATE);
        if (i == 1 && rand(1))
        {   // Мушкетёр
            chr = GetCharacter(NPC_GenerateCharacter("JF_Smugglers_1", sMushModel, "man", "mushketer", iRank, PIRATE, 0, false, "marginal"));
        }
        else
        {   // Солдаты
            chr = GetCharacter(NPC_GenerateCharacter("JF_Smugglers_" + i, model[i], "man", "man", iRank, PIRATE, 0, true, "marginal"));
            SetFantomParamFromRank(chr, iRank, true);
        }
        chr.dialog.filename = "Encounters\JungFight.c";
        chr.greeting = "smuggler";
        chr.role = "smuggler";
        chr.JungFightType = "Smugglers";
        chr.JungFightEnemies = sEnemies;
        LAi_SetWarriorType(chr);
        ForceAutolevel(chr, GEN_TYPE_ENEMY, GEN_COMMONER, GEN_ARCHETYPE_RANDOM, GEN_ARCHETYPE_RANDOM, GEN_RANDOM_PIRATES, 0.6);
        LAi_group_MoveCharacter(chr, sGroup);
        iLocator = rand(@grp - 1); // i % @grp;
        locator = nameattr(grp[iLocator]);
        ChangeCharacterAddressGroup(chr, loc.id, encGroup, locator);
        if (IsMusketer(chr)) JungFightSetRandCharge(chr);
    }
}

void JungFightSetRandCharge(ref chr)
{
    if (rand(2) == 1) return;
    chr.chr_ai.musket.charge = uniform(0.8, 0.9);
    chr.chr_ai.musket.chargeprc = "1";
}

void JungFightPlayerAttack(ref attack, ref hit)
{
    // Если игрок атаковал одну из групп, то персонажи из второй будут союзниками до конца боя
    string sEnemies = hit.chr_ai.group;
    string sAllies = (sEnemies == "JungFightGroup_A") ? "JungFightGroup_B" : "JungFightGroup_A";
    LAi_group_RemoveReaction(sAllies);
    LAi_group_SetCheckFunction(sEnemies, "JungFightVictory");
    JungFightMoveToGroup(sAllies, LAI_GROUP_PLAYER);
}

void JungFightMoveToGroup(string sCur, string sNew)
{
	for(int i = 0; i < LAi_numloginedcharacters; i++)
	{
		int idx = LAi_loginedcharacters[i];
		if (idx >= 0 && Characters[idx].chr_ai.group$string("") == sCur)
            LAi_group_MoveCharacter(&Characters[idx], sNew);
    }
    LAi_group_Delete(sCur);
}

void JungFightVictory(string sEnemies)
{
    string sAllies = (sEnemies == "JungFightGroup_A") ? "JungFightGroup_B" : "JungFightGroup_A";

    ref rNearChr = nullptr;
    float best_dist = 999999.0, dist;
	for(int i = 0; i < LAi_numloginedcharacters; i++)
	{
		int idx = LAi_loginedcharacters[i];
        if (idx < 0) continue;
        ref chr = &Characters[idx];
        if (LAi_IsDead(chr)) continue;
		if ("JungFightType" in chr)
        {
            chr.Dialog.CurrentNode = "Victory";
            GetCharacterDistByChr(PChar, chr, &dist);
            if (dist < best_dist)
            {
                rNearChr = chr;
                best_dist = dist;
            }
        }
    }

    // По умолчанию подойти должен главнюк (если жив, то он сюзник)
    ref boss = CharacterFromIDSafe("JF_Officer", true); // Только у патруля
    if (boss != nullptr && !LAi_IsDead(boss))
        rNearChr = boss;

    if (rNearChr != nullptr)
    {
        rNearChr.RestoreGroup = sAllies;
        rNearChr.Dialog.CurrentNode = "Reward";
        LAi_SetActorTypeNoGroup(rNearChr);
        LAi_ActorDialog(rNearChr, PChar, "", -1.0, 0.0);
    }
}

void JungFightReward(ref rTalker)
{
    // Вернуть тип
    LAi_SetWarriorTypeNoGroup(rTalker);
    // Вернуть командира
    ref boss = CharacterFromIDSafe("JF_Officer", true);
    if (boss != nullptr && !LAi_IsDead(boss) && rTalker.id != "JF_Officer")
        LAi_warrior_SetCommander(rTalker, boss);
    // Вернуть всем группу
    string sGroup = rTalker.RestoreGroup;
	for(int i = 0; i < LAi_numloginedcharacters; i++)
	{
		int idx = LAi_loginedcharacters[i];
        if (idx < 0) continue;
        ref chr = &Characters[idx];
        if (LAi_IsDead(chr)) continue;
		if ("JungFightType" in chr)
            LAi_group_MoveCharacter(chr, sGroup);
    }
    // Повышение репутации
    JungFightChangeRelation(rTalker, true);
    // Слух
    TEV.JungFightRumour = "HeroHelp";
    TEV.JungFightRumour.Winners = rTalker.JungFightType;
    TEV.JungFightRumour.Losers  = rTalker.JungFightEnemies;
    // Конды
    LAi_group_SetReaction(sGroup, "JungFightNoHonor");
    LAi_group_SetCheckFunction(sGroup, "JungFightAllDead");
}

void JungFightChangeRelation(ref rChar, bool bIncr)
{
    string sType = rChar.JungFightType;
    int val = (sType != "Pirates") ? 3 : -5;
    if (!bIncr) val *= -1; // Откат за предательство

    switch(sType)
    { 
        case "Patrol":    ChangeCharacterNationReputation(PChar, int(rChar.Nation), val); break;
        case "Smugglers": ChangeContrabandRelation(PChar, val); break;
        case "Caribs":    ChangeIndianRelation(float(val)); break;
        case "Pirates":
            ChangePirateThreat(val);
            if (bIncr) Notification(StringFromKey("QuestsUtilite_332"), "pirhunter");
            else Notification(StringFromKey("QuestsUtilite_333"), "pirhunter");
            break;
    }
}

void JungFightAllDead(string sGroup) { TEV.JungFightRumour = "AllDead"; }
void JungFightNoHonor(ref attack, ref hit)
{
    TEV.JungFightRumour = "Fight";
    JungFightChangeRelation(hit, false);
}

// CORPSE
bool JungleEncCheck_Corpse(ref loc, aref grp) { return true; }
void JungleEncGenerate_Corpse(ref loc, string sAreal, string sCity, int iNation, aref grp, string encGroup)
{
    ref chr;
    string model;
    int iRank = int(PChar.Rank);

    switch(rand(3))
    {
    case 0: // Контрик
        model = "citiz_" + (21+rand(9));
        chr = GetCharacter(NPC_GenerateCharacter("JngCopse", model, "man", "man", iRank, PIRATE, 0, false, "marginal"));
        RemoveAllCharacterItems(chr, true);
        AddMoneyToCharacter(chr, 500 + rand(1000));
        if (rand(2) == 1) TakeNItems(chr, "potionrum", 1);
        if (rand(2) == 1) TakeNItems(chr, "potionwine", 1);
        break;
    case 1: // Цыганка
        model = "gipsy_" + (1+rand(6));
        chr = GetCharacter(NPC_GenerateCharacter("JngCopse", model, "woman", "woman", iRank, iNation, 0, false, "citizen"));
        RemoveAllCharacterItems(chr, true);
        TakeNItems(chr, "cannabis" + (1 + rand(5)), 2 + rand(2));
        if (rand(99) > 97) TakeNItems(chr, "cannabis7", 1);
        break;
    case 2: // Патрульный
        bool bOff = rand(4) == 1;
        string sNat = NationShortName(iNation);
        model = bOff ? "off_"  + sNat + "_" + (rand(1)+1) : "sold_" + sNat + "_" + (rand(7)+1);
        string sType = bOff ? "officer" : "soldier";
        chr = GetCharacter(NPC_GenerateCharacter("JngCopse", model, "man", "man", iRank, iNation, 0, false, sType));
        RemoveAllCharacterItems(chr, true);
        TakeNItems(chr, "bullet", 5 + rand(5));
        TakeNItems(chr, "GunPowder", 5 + rand(5));
        if (rand(1)) TakeNItems(chr, "ArmoryPaper", 2 + rand(4));
        if (rand(19) == 1) TakeNItems(chr, "totem_05", 1);
        break;
    case 3: // Индеец
        model = rand(1) == 1 ? "miskito_" + (rand(5)+1) : "canib_" + (rand(5)+1);
        chr = GetCharacter(NPC_GenerateCharacter("JngCopse", model, "man", "man", iRank, PIRATE, 0, false, "native"));
        RemoveAllCharacterItems(chr, true);
        TakeNItems(chr, "jewelry8", 4 + rand(2));
        if (rand(1)) TakeNItems(chr, "jewelry52", 10 + rand(5));
        if (rand(1)) TakeNItems(chr, "jewelry53", 30 + rand(20));
        break;
    }

    chr.SaveItemsForDead = true;
    chr.DontClearDead = true;
    LAi_SetCitizenType(chr);
    ChangeCharacterAddressGroup(chr, loc.id, encGroup, GetRandomAttrName(grp));
    SetEventHandler(EVENT_LOCATION_LOAD, "JungCorpse_Kill", 0);
}

void JungCorpse_Kill()
{
    DelEventHandler(EVENT_LOCATION_LOAD, "JungCorpse_Kill");
    ref chr = CharacterFromId("JngCopse");
    CharacterTurnAy(chr, frnd() * PIm2);
	SetCharacterActionAnimation(chr, "dead", "lay_" + (1+rand(1)));
	LAi_KillCharacter(chr);
}

// PATROL
bool JungleEncCheck_Patrol(ref loc, aref grp)
{
    return "questTemp.Sharlie.DefendSP" !in PChar;
}

void JungleEncGenerate_Patrol(ref loc, string sAreal, string sCity, int iNation, aref grp, string encGroup)
{
    // Кол-во человек в патруле
    int num = @grp;

    // Ранг
    int iRank;
    if (int(PChar.Rank) > 14) iRank = int(PChar.Rank) + int(MOD_SKILL_ENEMY_RATE * 2.5 / num);
    else iRank = int(PChar.Rank) + int(MOD_SKILL_ENEMY_RATE * 1.6 / num);

    // Создаём персонажей
    ref chr;
    string str = "Patrol"+ loc.index + "_", locator;
    string sGroup = "PatrolGroup_" + loc.index; // Имя группы
    LAi_group_Register("PatrolGroup_" + loc.index);
    for(int i = 0; i < num; i++)
    {
        if (i == 0)
        {
            chr = GetCharacter(NPC_GenerateCharacter(str + i, "off_"+NationShortName(iNation)+"_"+(rand(1)+1), "man", "man", iRank+2, iNation, 1, true, "officer"));
            SetFantomParamFromRank(chr, iRank+2, true);
        }
        else
        {
            if (i == 3)
            {
                chr = GetCharacter(NPC_GenerateCharacter(str + i, "mush_" + NationShortName(iNation) + "_" +(rand(2)+1), "man", "mushketer", iRank, iNation, 1, false, "soldier"));
            }
            else
            {
                chr = GetCharacter(NPC_GenerateCharacter(str + i, "sold_"+NationShortName(iNation)+"_"+(rand(7)+1), "man", "man", iRank, iNation, 1, true, "soldier"));
                SetFantomParamFromRank(chr, iRank, true);
            }
        }
        chr.City = sCity;
        chr.CityType = "soldier";				
        chr.greeting = "patrol";
        chr.role = "patrol";
        chr.dialog.filename = "Enc_Patrol.c";
        chr.EncQty = num;
        LAi_SetStayType(chr);
        ForceAutolevel(chr, GEN_TYPE_ENEMY, GEN_COMMONER, GEN_ARCHETYPE_RANDOM, GEN_ARCHETYPE_RANDOM, GEN_RANDOM_PIRATES, 0.6);
        LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, false, "LandEnc_PatrolBeforeDialog");
        LAi_group_MoveCharacter(chr, sGroup);
        locator = nameattr(grp[i]);
        ChangeCharacterAddressGroup(chr, loc.id, encGroup, locator);
    }
    LAi_group_SetLookRadius(sGroup, 100);
    LAi_group_SetHearRadius(sGroup, 100);

    str = "EncPatrol_" + loc.index;
    pchar.quest.(str).win_condition.l1        = "locator";
    pchar.quest.(str).win_condition.l1.location = loc.id;
    pchar.quest.(str).win_condition.l1.locator_group = "encdetector";
    pchar.quest.(str).win_condition.l1.locator = encGroup;
    pchar.quest.(str).win_condition = "LandEnc_PatrolBegin";
    pchar.quest.(str).EncQty = num; // Кол-во патрульных
    pchar.quest.(str).LocIdx = loc.index; 

    str = "TimePatrol_" + loc.index;
    pchar.quest.(str).win_condition.l1            = "Timer";
    pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
    pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
    pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
    pchar.quest.(str).win_condition               = "LandEnc_PatrolOver";	
    pchar.quest.(str).LocIdx = loc.index;
    str = loc.index;
    pchar.GenQuest.(str).nation = iNation; // Нация патруля для слухов
}

// BANDITS
bool JungleEncCheck_Bandits(ref loc, aref grp)
{
    if (loc.type == "questisland")
        return false;
    if (loc.id == "Curacao_jungle_03" || loc.id == "Hispaniola_Jungle_02")
        return false;

    return true;
}

void JungleEncGenerate_Bandits(ref loc, string sAreal, string sCity, int iNation, aref grp, string encGroup)
{
    // Кол-во человек в банде
    bool bFireSit = ("locators.fire" !in loc) ? false : rand(1) == 1;
    int num = bFireSit ? 4 - rand(2) : @grp - rand(2);
    if (num <= 0) num = 1; // Если @grp меньше трёх

    // Ранг
    int iRank;
    if (int(PChar.Rank) > 6)
    {
        if (int(PChar.Rank) > 20) iRank = int(PChar.Rank) + int(MOD_SKILL_ENEMY_RATE * 2.5 / num);
        else iRank = int(PChar.Rank) + int(MOD_SKILL_ENEMY_RATE * 1.6 / num);
    }
    else iRank = int(PChar.Rank);

    // Модельки
    string model[] = {"citiz_41", "citiz_42", "citiz_43", "citiz_44", "citiz_45", "citiz_46", "citiz_47", "citiz_48", "citiz_49", "citiz_50"};
    ArrayShuffle(&model);

    // Обновить боевой ИИ
    LAi_grp_alarmactive = false;
    LAi_group_ClearAllTargets();

    // Создаём персонажей
    string str = "Gang"+ loc.index + "_", locator;
    for (int i = 0; i < num; i++)
    {
        ref chr = GetCharacter(NPC_GenerateCharacter(str + i, model[i], "man", "man", iRank, iNation, 1, true, "marginal"));
        SetFantomParamFromRank(chr, iRank, true);
        ForceAutolevel(chr, GEN_TYPE_ENEMY, GEN_COMMONER, GEN_ARCHETYPE_RANDOM, GEN_ARCHETYPE_RANDOM, GEN_RANDOM_PIRATES, 0.6);

        // Ставим
        if (bFireSit)
        {
            ref rItm = ItemsFromID("fire");
            rItm.shown = true;
            rItm.startLocation = loc.id;
            rItm.startLocator = "fire";
            loc.fire = true;
            encGroup = "enc01";
            locator = "ass"+(i+1);
            ChangeCharacterAddressGroup(chr, loc.id, "goto", locator);
            LAi_SetGroundSitTypeNoGroup(chr);
        }
        else
        {
            locator = GetAttributeName(GetAttributeN(grp, i));
            ChangeCharacterAddressGroup(chr, loc.id, encGroup, locator);
            LAi_SetStayType(chr);
        }

        // Параметры
        if (rand(9) == 6) AddItems(chr, "ArmoryPaper", 1 + rand(1));
        chr.dialog.filename = "Enc_Raiders_dialog.c";
        chr.greeting = "banditos";
        chr.role = "banditos";
        chr.EncQty = num;
        LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, true, "LandEnc_RaidersBeforeDialog");
        LAi_group_MoveCharacter(chr, "RaidersGroup_" + loc.index);
        if (i == 0) 			
        {
            string sQuest = "Raiders_" + loc.index;
            PChar.GenQuest.(sQuest).name = GetFullName(chr); // Имя главаря
            PChar.GenQuest.(sQuest).nation = iNation; // Нация для слухов 
        }
    }

    str = "EncRaiders_" + loc.index;
    PChar.quest.(str).win_condition.l1 = "locator";
    PChar.quest.(str).win_condition.l1.location = loc.id;
    PChar.quest.(str).win_condition.l1.locator_group = "encdetector";
    PChar.quest.(str).win_condition.l1.locator = encGroup;
    PChar.quest.(str).win_condition = "LandEnc_RaidersBegin";
    PChar.quest.(str).EncQty = num;
    PChar.quest.(str).LocIdx = loc.index; 
    PChar.GenQuest.LandEnc.LocId = loc.id;

    str = "TimeRaiders_" + loc.index;
    PChar.quest.(str).win_condition.l1            = "Timer";
    PChar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
    PChar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
    PChar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
    PChar.quest.(str).win_condition               = "LandEnc_RaidersOver";	
    PChar.quest.(str).LocIdx = loc.index;
}

// SLAVES
bool JungleEncCheck_Slaves(ref loc, aref grp)
{
    if ("GenQuest.Convict" in PChar)
        return false;
    if (GiveArealByLocation(loc) == "Panama")
        return false;

    return @grp > 1;
}

void JungleEncGenerate_Slaves(ref loc, string sAreal, string sCity, int iNation, aref grp, string encGroup)
{
    // Кол-во человек в группе
    int num = @grp;

    // Ранг
    int iRank = 2 + rand(3);

    // Модельки
    string model[] = {"prizon_1", "prizon_2", "prizon_3", "prizon_4", "prizon_5", "prizon_6", "prizon_7", "prizon_8", "prizon_3", "prizon_4"};
    ArrayShuffle(&model);

    // Дождаться разговора
    PChar.GenQuest.Convict.ConvictQty = num;
    PChar.GenQuest.Convict.city = sCity;
    chrDisableReloadToLocation = true;

    // Создаём персонажей
    for (int i = 0; i < num; i++)
    {
        ref chr = GetCharacter(NPC_GenerateCharacter("Convict_" + i, model[i], "man", "man_B", iRank, PIRATE, -1, true, "slave"));
        SetFantomParamFromRank(chr, iRank, true);
        string locator = GetAttributeName(GetAttributeN(grp, i));
        ChangeCharacterAddressGroup(chr, loc.id, encGroup, locator);
        chr.dialog.filename = "GenQuests_Dialog.c";
        chr.dialog.currentnode = "First time";
        chr.greeting = "convict"; 
        chr.city = sCity;
        LAi_SetImmortal(chr, true); // До поры нельзя убить
        LAi_SetActorTypeNoGroup(chr);
        if (i == 0) LAi_ActorDialog(chr, PChar, "", -1, 0.0);
        else LAi_ActorFollow(chr, PChar, "", -1);
        LAi_Group_MoveCharacter(chr, "ConvictGroup");
        LAi_Group_SetRelation("ConvictGroup", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
    }

    SetFunctionExitFromLocationCondition("Convict_LocExit", PChar.location, false);
    PChar.GenQuest.Convict.Item = GenQuest_GenerateArtefact();

    int iRnd = rand(9);
    if (iRnd <= 5) PChar.GenQuest.Convict.variant = 1;
    else if (iRnd > 5 && iRnd < 8) PChar.GenQuest.Convict.variant = 2;
    else PChar.GenQuest.Convict.variant = 3;
    PChar.GenQuest.Convict.var = rand(2);
    Log_TestInfo("Каторжане: сгенерился квест");
}

// INDIANS
bool JungleEncCheck_Indians(ref loc, aref grp)
{
    if (loc.id == "Curacao_jungle_03" || loc.id == "Hispaniola_Jungle_02")
        return false;

    return true;
}

void JungleEncGenerate_Indians(ref loc, string sAreal, string sCity, int iNation, aref grp, string encGroup)
{
    // Кол-во человек в банде
    bool bFireSit = ("locators.fire" !in loc) ? false : rand(2) > 0;
    int num = bFireSit ? 4 : @grp;

    // Ранг
    int iRank;
    if (int(PChar.rank) > 6)
    {
        if (int(PChar.rank) > 20) iRank = int(PChar.rank) + int(MOD_SKILL_ENEMY_RATE * 2.5 / num);
        else iRank = int(PChar.rank) + int(MOD_SKILL_ENEMY_RATE * 1.6 / num);
    }
    else iRank = int(PChar.rank) + 3;

    // Карибы или Мискито
    string sEncType = rand(1) ? "war" : "peace";
    
    // Модельки
    string model[];
    if (sEncType == "war")
    {
        model = {"canib_1", "canib_2", "canib_3", "canib_4", "canib_5", "canib_6", "canib_1", "canib_2", "canib_3", "canib_4"};
    }
    else
    {
        model = {"miskito_1", "miskito_2", "miskito_3", "miskito_4", "miskito_5", "miskito_6", "miskito_1", "miskito_2", "miskito_3", "miskito_4"};
    }
    ArrayShuffle(&model);

    // Обновить боевой ИИ
    LAi_grp_alarmactive = false;
    LAi_group_ClearAllTargets();

    // Создаём персонажей
    string str = "Carib"+ loc.index + "_", locator;
    for (int i = 0; i < num; i++)
    {
        ref chr = GetCharacter(NPC_GenerateCharacter(str + i, model[i], "man", "man", iRank, PIRATE, 1, true, "native"));
        SetFantomParamFromRank(chr, iRank, true);
        ForceAutolevel(chr, GEN_TYPE_ENEMY, GEN_COMMONER, GEN_ARCHETYPE_RANDOM, GEN_ARCHETYPE_RANDOM, GEN_RANDOM_PIRATES, 0.6);

        // Ставим
        if (bFireSit)
        {
            ref rItm = ItemsFromID("fire");
            rItm.shown = true;
            rItm.startLocation = loc.id;
            rItm.startLocator = "fire";
            loc.fire = true;
            encGroup = "enc01";
            locator = "ass"+(i+1);
            ChangeCharacterAddressGroup(chr, loc.id, "goto", locator);
            LAi_SetGroundSitTypeNoGroup(chr);
        }
        else
        {
            locator = nameattr(grp[i]);
            ChangeCharacterAddressGroup(chr, loc.id, encGroup, locator);
            LAi_SetStayType(chr);
        }

        // Первый амулет Калеуче
        string tag = chr.id + chr.name;
        if ("questTemp.Caleuche.SeekAmulet" in PChar && i == 0 && hrand(2, tag) == 1) 
        {
            GiveItem2Character(chr, "kaleuche_amulet1");
            chr.SaveItemsForDead = true;
            chr.DontClearDead = true;
        }

        // Параметры
        chr.dialog.filename = "Enc_Carib_dialog.c";
        chr.greeting = "indiano"; 
        chr.name = GetIndianName(MAN);
        chr.lastname = "";
        chr.EncQty = num;
        if (sEncType == "war")
        {
            chr.dialog.currentnode = "war_indian";
            if (hrand(9, tag) < 8) LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, true, "LandEnc_CaribBeforeDialog");
            else LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, true, "LandEnc_MiskitoBeforeDialog");
        }
        else
        {
            chr.dialog.currentnode = "peace_indian";
            if (hrand(9, tag) > 8) LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, true, "LandEnc_CaribBeforeDialog");
            else LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, true, "LandEnc_MiskitoBeforeDialog");
        }
        LAi_group_MoveCharacter(chr, "CaribGroup_" + loc.index);
    }

    str = "EncCarib_" + loc.index;
    pchar.quest.(str).win_condition.l1 = "locator";
    pchar.quest.(str).win_condition.l1.location = loc.id;
    pchar.quest.(str).win_condition.l1.locator_group = "encdetector";
    pchar.quest.(str).win_condition.l1.locator = encGroup;
    pchar.quest.(str).win_condition = "LandEnc_CaribBegin";
    pchar.quest.(str).EncQty = num;
    pchar.quest.(str).LocIdx = loc.index;
    pchar.GenQuest.LandEnc.LocId = loc.id;

    str = "TimeCarib_" + loc.index;
    pchar.quest.(str).win_condition.l1            = "Timer";
    pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
    pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
    pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
    pchar.quest.(str).win_condition               = "LandEnc_CaribOver";	
    pchar.quest.(str).LocIdx = loc.index;
}

// SMUGGLERS
bool JungleEncCheck_Smugglers(ref loc, aref grp)
{
    if ("GenQuest.JusticeOnSale" in PChar)
        return false;
    return true;
}

void JungleEncGenerate_Smugglers(ref loc, string sAreal, string sCity, int iNation, aref grp, string encGroup)
{
    // Кол-во человек в банде
    int num = @grp - rand(2);
    if (num <= 0) num = 1;

    // Ранг
    int iRank;
    if (int(PChar.Rank) > 6)
    {
        if (int(PChar.Rank) > 20) iRank = int(PChar.Rank) + int(MOD_SKILL_ENEMY_RATE * 2.5 / num);
        else iRank = int(PChar.Rank) + int(MOD_SKILL_ENEMY_RATE * 1.6 / num);
    }
    else iRank = int(PChar.Rank);

    // Обновим боевой ИИ
    LAi_grp_alarmactive = false;
    LAi_group_ClearAllTargets();

    // Модельки
    string model[] = {"citiz_41", "citiz_42", "citiz_43", "citiz_44", "citiz_45", "citiz_46", "citiz_47", "citiz_48", "citiz_49", "citiz_50"};
    ArrayShuffle(&model);

    // Создаём персонажей
    for(int i = 0; i < num; i++)
    {
        ref chr = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_Jungle_" + i, model[i], "man", "man", iRank, iNation, 0, true, "marginal"));
        SetFantomParamFromRank(chr, iRank, true);
        ForceAutolevel(chr, GEN_TYPE_ENEMY, GEN_COMMONER, GEN_ARCHETYPE_RANDOM, GEN_ARCHETYPE_RANDOM, GEN_RANDOM_PIRATES, 0.6);
        string locator = GetAttributeName(GetAttributeN(grp, i));
        ChangeCharacterAddressGroup(chr, loc.id, encGroup, locator);
        chr.dialog.filename = "GenQuests_Dialog.c";
        chr.dialog.currentnode = "First time";
        chr.greeting = "smuggler"; 
        LAi_SetCitizenType(chr);
        LAi_group_MoveCharacter(chr, "JusticeOnSaleGroup_" + loc.index);
    }
    PChar.GenQuest.JusticeOnSale.EncQty = num;
    PChar.GenQuest.JusticeOnSale.CityId = sCity;
    if (sCity != "Panama") // Лесник
    {
        PChar.GenQuest.JusticeOnSale.ShoreId = SelectQuestShoreLocation();
    }
    else
    {
        switch(rand(1))
        {
            case 0: PChar.GenQuest.JusticeOnSale.ShoreId = "Shore47"; break;
            case 1: PChar.GenQuest.JusticeOnSale.ShoreId = "Shore48"; break;
        }	
    }										
    PChar.GenQuest.JusticeOnSale.SmugglerName = GenerateRandomName_Generator(PIRATE, "man");

    PChar.Quest.JusticeOnSale_LocationExit.win_condition.l1 = "ExitFromLocation";
    PChar.Quest.JusticeOnSale_LocationExit.win_condition.l1.location = PChar.location;
    PChar.Quest.JusticeOnSale_LocationExit.function = "JusticeOnSale_LocationExit";

    Log_TestInfo("Сгенерился квест 'Правосудие на продажу'");
    Log_TestInfo("Имя контрика: " + PChar.GenQuest.JusticeOnSale.SmugglerName);
    Log_TestInfo("Id бухты: " + PChar.GenQuest.JusticeOnSale.ShoreId);
}

// ALONE CITIZEN
bool JungleEncCheck_Alone_Citiz(ref loc, aref grp) { return true; }
void JungleEncGenerate_Alone_Citiz(ref loc, string sAreal, string sCity, int iNation, aref grp, string encGroup)
{
    int iRank = int(PChar.Rank);
    string model = "citiz_" + (11 + rand(9));
    ref chr = GetCharacter(NPC_GenerateCharacter("Walker_" + loc.index, model, "man", "man", iRank, iNation, 1, false, "citizen"));
    ForceAutolevel(chr, GEN_TYPE_ENEMY, GEN_COMMONER, GEN_ARCHETYPE_RANDOM, GEN_ARCHETYPE_RANDOM, GEN_RANDOM_PIRATES, 0.6);

    chr.CityName = sCity; // Не City, чтобы не выдавал свежие слухи из джунглей
    chr.greeting = "citizen_male"; // ~!~
    chr.dialog.filename = "Encounters\Alone_Citiz.c";
    chr.dialog.currentnode = "First time";
    LAi_SetCitizenType(chr);

    string locator = GetRandomAttrName(grp);
    ChangeCharacterAddressGroup(chr, loc.id, encGroup, locator);

    string GroupName = "Alone_Citiz_" + chr.id;
    LAi_group_Delete(GroupName);
    LAi_group_MoveCharacter(chr, GroupName);

    // Damage condition
    LAi_SetCheckMinHPCallback(chr, LAi_GetCharacterMaxHP(chr) - 1, false, "JungWalker_Escape");

    aref   QuestParam;
    string QuestName = "Alone_Citiz_" + chr.id;
    string sClearAttr = QuestName + "_Clear";
    string sDeathAttr = QuestName + "_Death";
    string sFullName  = GetFullName(chr);

    // Clear condition
    QuestParam = touchattr(PChar.Quest.(sClearAttr));
    QuestParam.win_condition.l1            = "Timer";
    QuestParam.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
    QuestParam.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
    QuestParam.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
    QuestParam.function                    = "JungleEncClear_Alone_Citiz";	
    // Info for clear function
    QuestParam.Location  = loc.id;
    QuestParam.Character = chr.id;
    QuestParam.FullName  = sFullName;
    QuestParam.City = sCity;
    QuestParam.RobberySuccess = false;

    // Death condition
    QuestParam = touchattr(PChar.Quest.(sDeathAttr));
    QuestParam.win_condition.l1           = "NPC_Death";
    QuestParam.win_condition.l1.character = chr.id;
    QuestParam.function                   = "JungleEncDeath_Alone_Citiz";
    // Info for death function
    QuestParam.Character = chr.id;
    QuestParam.FullName  = sFullName;
    QuestParam.City = sCity;
}

void JungleEncClear_Alone_Citiz(string sQuestAttr)
{
    aref info = &PChar.Quest.(sQuestAttr);
    string GroupName = "Alone_Citiz_" + info.Character;

    if (PChar.Location != info.Location)
    {
        // Delete group and other conditions
        LAi_group_Delete(GroupName);
        // DeleteAttribute(PChar, "Quest.Alone_Citiz_" + info.Character + "_Escape");
        DeleteAttribute(PChar, "Quest.Alone_Citiz_" + info.Character + "_Death");
        if (int(info.RobberySuccess) != 0 && rand(2) == 0)
        {
            string text = StringFromKey("Alone_Citiz_RobberySuccess_" + rand(1), info.FullName);
            AddSimpleRumourCity(text, info.City, 5, 1, "");  // ~!~ cases _0
        }
    }
    else
    {
        // Delay until exit from location
        aref QuestParam = touchattr(PChar.Quest.("Alone_Citiz_" + info.Character + "_DelayClear"));
        QuestParam.win_condition.l1          = "ExitFromLocation";
        QuestParam.win_condition.l1.location = PChar.Location;
        QuestParam.function                  = "JungleEncClear_Alone_Citiz";
        QuestParam.Location  = info.Location;
        QuestParam.Character = info.Character;
        QuestParam.FullName  = info.FullName;
        QuestParam.City      = info.City;
        QuestParam.RobberySuccess = info.RobberySuccess;
    }
}

void JungleEncDeath_Alone_Citiz(string sQuestAttr)
{
    aref info = &PChar.Quest.(sQuestAttr);
    string GroupName = "Alone_Citiz_" + info.Character;
    // Delete group and other conditions
    LAi_group_Delete(GroupName);
    DeleteAttribute(PChar, "Quest.Alone_Citiz_" + info.Character + "_Escape");
    DeleteAttribute(PChar, "Quest.Alone_Citiz_" + info.Character + "_Clear");
    DeleteAttribute(PChar, "Quest.Alone_Citiz_" + info.Character + "_DelayClear");
    // Rumour
    if (rand(4) > 2)
    {
        string text = StringFromKey("Alone_Citiz_Death_" + rand(1), info.FullName); // ~!~ cases _0
        AddSimpleRumourCity(text, info.City, 5, 1, "");
    }
}

int JungWalker_RobberyChance()
{
    return GetCharacterSkill(PChar, SKILL_LEADERSHIP) / 2 + GetCharacterSkill(PChar, SKILL_SNEAK) / 2;
}

void JungWalker_Escape(ref chr, ref callback = nullptr)
{
    // Удалить NPC после побега
    chr.LifeDay = 0;
    // Убрать CheckMinHP, если побежал после запугивания, а не от урона
    LAi_RemoveCheckMinHP(chr);
    // Удаление по таймеру теперь не нужно, убираем его
    DeleteAttribute(PChar, "Quest.Alone_Citiz_" + chr.id + "_Clear");
    DeleteAttribute(PChar, "Quest.Alone_Citiz_" + chr.id + "_DelayClear");
    // Побег
    float x, y, z;
	GetCharacterPos(chr, &x, &y, &z);
	string locator = LAi_FindNearestLocator("reload", x, y, z);
	LAi_SetActorTypeNoGroup(chr);
    LAi_ActorRunToLocation(chr, "reload", locator, "none", "", "", "", -1.0);
    // Прерывание
    aref QuestParam = touchattr(PChar.Quest.("Alone_Citiz_" + chr.id + "_Escape"));
    QuestParam.win_condition.l1          = "ExitFromLocation";
    QuestParam.win_condition.l1.location = PChar.Location;
    QuestParam.function                  = "JungWalker_EscapeEnd";
    QuestParam.Character = chr.id;
    QuestParam.FullName  = GetFullName(chr);
    QuestParam.City = chr.CityName;
    QuestParam.RobberyFail = "RobberyFail" in chr;
}

void JungWalker_EscapeEnd(string sQuestAttr)
{
    aref info = &PChar.Quest.(sQuestAttr);
    // Delete group and other conditions
    string GroupName = "Alone_Citiz_" + info.Character;
    LAi_group_Delete(GroupName);
    DeleteAttribute(PChar, "Quest.Alone_Citiz_" + info.Character + "_Death");
    // Обработчик побега не был удалён в обработчике смерти, значит NPC ушёл успешно
    if (int(info.RobberyFail) != 0)
    {
        string text = StringFromKey("Alone_Citiz_RobberyFail_" + rand(1), info.FullName);
        AddSimpleRumourCity(text, info.city, 5, 1, ""); // ~!~ cases _0
    }
}

// ALONE SOLDIER
bool JungleEncCheck_Alone_Sold(ref loc, aref grp) { return true; }
void JungleEncGenerate_Alone_Sold(ref loc, string sAreal, string sCity, int iNation, aref grp, string encGroup)
{
    ref chr;
    string model;
    int iRank = int(PChar.Rank) + rand(MOD_SKILL_ENEMY_RATE / 2);
    string sNat = NationShortName(iNation);
    bool bMush  = (rand(2) == 1); 
    
    if (bMush)
    {
        model = "mush_" + sNat + "_" + (rand(2)+1);
        chr = GetCharacter(NPC_GenerateCharacter("AlonePatrol", model, "man", "mushketer", iRank, iNation, 0, false, "soldier"));
        LAi_NPC_MushketerEquip(chr);
    }
    else
    {
        model = "sold_" + sNat + "_" + (rand(7)+1);
        chr = GetCharacter(NPC_GenerateCharacter("AlonePatrol", model, "man", "man", iRank, iNation, 0, true, "soldier"));
    }

    ForceAutolevel(chr, GEN_TYPE_ENEMY, GEN_COMMONER, GEN_ARCHETYPE_RANDOM, GEN_ARCHETYPE_RANDOM, GEN_RANDOM_PIRATES, 0.6);

    chr.greeting = "patrol";
    chr.role = "patrol";
    chr.dialog.filename = "Encounters\Alone_Soldier.c";
    chr.dialog.currentnode = "First time";

    string locator = GetRandomAttrName(grp);
    ChangeCharacterAddressGroup(chr, loc.id, encGroup, locator);
    LAi_SetCitizenType(chr);
    LAi_group_Delete("AlonePatrol");
    LAi_group_MoveCharacter(chr, "AlonePatrol");
}

void JungAloneSoldClear(string qName){ LAi_group_RemoveReaction("AlonePatrol"); }
void JungAloneSoldierPotion(string sPotionName, int iNation)
{
    ref chr = CharacterFromId("AlonePatrol");
    TakeNItems(PChar, sPotionName, -1);
    chr.HaveGift = "";
    chr.greeting = "habitue";
    DeleteAttribute(chr, "greeting.minute");
    DoCharacterUsedItem(chr, sPotionName);
    AddDialogExitQuestFunction("JungAloneSoldSetWarriror");
    AddCharacterExpToSkill(PChar, SKILL_LEADERSHIP, 10);
    ChangeCharacterNationReputation(PChar, iNation, 1);
    ChangeCharacterComplexReputation(PChar, "nobility", 1);
    // Откатить бонусы за агрессию
    LAi_group_SetReaction("AlonePatrol", "JungAloneSoldNoHonor");
    PChar.Quest.AloneSoldClear.win_condition.l1          = "ExitFromLocation";
    PChar.Quest.AloneSoldClear.win_condition.l1.location = PChar.Location;
    PChar.Quest.AloneSoldClear.function                  = "JungAloneSoldClear";
}

void JungAloneSoldSetWarriror()
{
    // Прекращает реагировать на обнажённое оружие
    ref chr = CharacterFromId("AlonePatrol");
    LAi_SetWarriorTypeNoGroup(chr);
}

void JungAloneSoldNoHonor(ref attack, ref hit)
{
    int iNation = int(hit.nation);
    ChangeCharacterNationReputation(PChar, iNation, -1);
    ChangeCharacterComplexReputation(PChar, "nobility", -1);
}

// ALONE INDIAN
bool JungleEncCheck_Alone_Indian(ref loc, aref grp) { return true; }
void JungleEncGenerate_Alone_Indian(ref loc, string sAreal, string sCity, int iNation, aref grp, string encGroup)
{
    LAi_group_Delete("LandEncGroup");
    string locator = GetAttributeName(GetAttributeN(grp, 0));
    ref chr = GetCharacter(NPC_GenerateCharacter("Walker", "miskito_"+(rand(5)+1), "man", "man", int(PChar.Rank), PIRATE, 0, true, "native"));
    SetFantomParamFromRank(chr, int(PChar.Rank), true);
    ForceAutolevel(chr, GEN_TYPE_ENEMY, GEN_COMMONER, GEN_ARCHETYPE_RANDOM, GEN_ARCHETYPE_RANDOM, GEN_RANDOM_PIRATES, 0.6);
    chr.name = GetIndianName(MAN);
    chr.lastname = "";
    chr.greeting = "item_indian";
    chr.dialog.filename = "Enc_Indian.c";
    chr.dialog.currentnode = "First time";
    LAi_SetCitizenType(chr);
    LAi_group_MoveCharacter(chr, "LandEncGroup");
    ChangeCharacterAddressGroup(chr, loc.id, encGroup, locator);
    chr.Merchant.type = "indian";
    chr.money = TRADER_MIN_MONEY;
}

// ALONE INJURED
bool JungleEncCheck_Alone_Injured(ref loc, aref grp) { return true; }
void JungleEncGenerate_Alone_Injured(ref loc, string sAreal, string sCity, int iNation, aref grp, string encGroup)
{
    int iRank = int(PChar.Rank) + rand(MOD_SKILL_ENEMY_RATE / 2);
    string model, sType, sGreeting;
    switch(rand(3))
    {
        case 0: // Indian
            model = rand(1) ? "miskito_"+(rand(5)+1) : "canib_"+(rand(5)+1);
            sType = "Native";
            sGreeting = "indiano";
            iNation = PIRATE;
            break;
        case 1: // Smuggler
            model = "citiz_"+(rand(9)+21);
            sType = "Marginal";
            sGreeting = "smuggler";
            break;
        case 2: // Soldier
            model = "sold_"+NationShortName(iNation)+"_"+(rand(7)+1);
            sType = "Soldier";
            sGreeting = "patrol";
            break;
        case 3: // Bandit
            model = "citiz_"+(rand(9)+41);
            sType = "Marginal";
            sGreeting = "town_pirate";
            break;
    }

    ref chr = GetCharacter(NPC_GenerateCharacter("InjuredGuy", model, "man", "man", iRank, iNation, 0, true, sType));
    ForceAutolevel(chr, GEN_TYPE_ENEMY, GEN_COMMONER, GEN_ARCHETYPE_RANDOM, GEN_ARCHETYPE_RANDOM, GEN_RANDOM_PIRATES, 0.6);

    if (sType == "Native")
    {
        chr.name = GetIndianName(MAN);
        chr.lastname = "";
    }
    chr.city = sCity;
    chr.DialogFlag = (sGreeting == "town_pirate") ? "Bandit" : sType;
    chr.greeting = sGreeting;
    chr.dialog.filename = "Encounters\Alone_Injured.c";
    chr.dialog.currentnode = "First time";

    string locator = GetRandomAttrName(grp);
    ChangeCharacterAddressGroup(chr, loc.id, encGroup, locator);
    MakeUnpushable(chr, true);
    LAi_SetGroundSitType(chr);
    LAi_group_Delete("InjuredGuy");
    LAi_group_MoveCharacter(chr, "InjuredGuy");

    LAi_SetDltHealth(chr, 0.0);
    LAi_SetCurHP(chr, 1.0);
    for(int i = 0; i < 5; i++)
        LaunchBlood(chr, 0.05, true, "fight");

    PChar.Quest.InjuredGuyDeath.win_condition.l1           = "NPC_Death";
    PChar.Quest.InjuredGuyDeath.win_condition.l1.character = chr.id;
    PChar.Quest.InjuredGuyDeath.function                   = "JungInjuredDeath";
    PChar.Quest.InjuredGuyDeath.CharType                   = sType;
    PChar.Quest.InjuredGuyDeath.Nation                     = iNation;

    PChar.Quest.InjuredGuyClear.win_condition.l1           = "ExitFromLocation";
    PChar.Quest.InjuredGuyClear.win_condition.l1.location  = PChar.location;
    PChar.Quest.InjuredGuyClear.function                   = "JungInjuredExit";
}

void JungInjuredExit(string qName) { DeleteAttribute(PChar, "Quest.InjuredGuyDeath"); }
void JungInjuredDeath(string qName)
{
    AddCharacterExpToSkill(PChar, SKILL_SNEAK, 10);
    ChangeCharacterComplexReputation(PChar, "nobility", -4);

    aref info = &PChar.Quest.(qName);
    switch(info.CharType)
    {
        case "Native":   ChangeIndianRelation(-3.0); break;
        case "Marginal": ChangeContrabandRelation(PChar, -3); break;
        case "Soldier":  ChangeCharacterNationReputation(PChar, int(info.Nation), -3); break;
    }
}

void JungInjuredHeal()
{
    ref chr = CharacterFromId("InjuredGuy");
    int add = int(chr.RepIncr);
    switch(chr.DialogFlag)
    {
        case "Native":   ChangeIndianRelation(float(add)); break;
        case "Marginal": ChangeContrabandRelation(PChar, add); break;
        case "Soldier":
            if (rand(2) != 0)
            {
                string text;
                if (rand(1)) text = StringFromKey("JungInjured_SoldHeal_0");
                else text = StringFromKey("JungInjured_SoldHeal_1", GetFullName(chr));
                AddSimpleRumourCity(text, chr.city, 5, 1, "");
            }
            ChangeCharacterNationReputation(PChar, int(chr.Nation), add);
            break;
    }
    LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
    LAi_group_Delete("InjuredGuy");
    DoCharacterUsedItem(chr, chr.PotionToUse);
    float x, y, z;
	GetCharacterPos(chr, &x, &y, &z);
	string locator = LAi_FindNearestLocator("reload", x, y, z);
	LAi_SetActorTypeNoGroup(chr);
    LAi_ActorGoToLocation(chr, "reload", locator, "none", "", "", "", -1.0);
}

void JungInjuredKill()
{
    ref sld = CharacterFromID("InjuredGuy");
    SendMessage(sld, "ls", MSG_CHARACTER_EX_MSG, "forceBlend");
	LAi_SetActorTypeNoGroup(sld);
    SendMessage(PChar, "ls", MSG_CHARACTER_EX_MSG, "forceBlend");
    SendMessage(PChar, "lslssl", MSG_CHARACTER_EX_MSG, "TieItem", FindItem("knife_01"), "knife_01", "Saber_hand", 1);
    LAi_SetActorTypeNoGroup(PChar);
    SetEventHandler("Location_CharacterTaskFailure", "JungInjuredRefreshTask", 0); // Защита на случай бага
    JungInjuredGoToKill();
}

void JungInjuredGoToKill()
{
    ref sld = CharacterFromID("InjuredGuy");
    float x, y, z, ay;
    GetCharacterAy(sld, &ay);
    GetCharacterPos(sld, &x, &y, &z);
    float off_x = 0.0, off_z = 0.6;
    RotateAroundY(&off_x, &off_z, cos(ay), sin(ay));
    LAi_ActorMoveToPoint(PChar, false, x + off_x, y, z + off_z, "JungInjuredKillStart", -1.0);
}

void JungInjuredRefreshTask()
{
	string endTask = GetEventData();
	aref chr = GetEventData();
    if (chr.index == nMainCharacterIndex && endTask == "Goto point")
    {
        LAi_type_actor_Reset(PChar);
        JungInjuredGoToKill();
    }
}

void JungInjuredKillStart()
{
    DelEventHandler("Location_CharacterTaskFailure", "JungInjuredRefreshTask");
    bDisableCharacterMenu = true;
    InterfaceStates.Buttons.Save.enable = false;
	ref sld = CharacterFromID("InjuredGuy");
    SyncPlaybackDlt(PChar, sld);
	SetCharacterActionAnimation(sld, "dead", "hit_stab");
    Statistic_AddValue(PChar, (sld.DialogFlag == "Soldier") ? "Solder_s" : "Warrior_s", 1);
    LAi_KillCharacter(sld);
	LAi_ActorAnimation(PChar, "stab", "JungInjuredKillEnd", 4.0);
}

void JungInjuredKillEnd()
{
    SendMessage(PChar, "lsl", MSG_CHARACTER_EX_MSG, "UntieItem", FindItem("knife_01"));
    SendMessage(PChar, "ls", MSG_CHARACTER_EX_MSG, "forceBlend");
	LAi_SetPlayerType(PChar);
    bDisableCharacterMenu = false;
    InterfaceStates.Buttons.Save.enable = true;
}

// SHIP WRECK
bool JungleEncCheck_ShipWreck(ref loc, aref grp)
{
    if (PChar.location != PChar.location.from_sea)
        return false;
    if ("GenQuest.PiratesOnUninhabited" in PChar || "GenQuest.ShipWreck" in PChar)
        return false;
    return true;
}

void JungleEncGenerate_ShipWreck(ref loc, string sAreal, string sCity, int iNation, aref grp, string encGroup)
{
    // Кол-во кораблекрушенцев
    int num = 3 + hRand(5, loc.id);
    if (num > @grp) num = @grp;

    // Ранг
    int iRank = int(PChar.rank) + MOD_SKILL_ENEMY_RATE;

    // Модельки
    string model[] = {"citiz_41", "citiz_42", "citiz_43", "citiz_44", "citiz_45", "citiz_46", "citiz_47", "citiz_48", "citiz_49", "citiz_50"};
    ArrayShuffle(&model);

    PChar.GenQuest.ShipWreck.Qty = num;	
    PChar.GenQuest.ShipWreck.Nation = hrand(NON_PIRATES, loc.id); // Нация
    PChar.GenQuest.ShipWreck.Prize = GenQuest_GeneratePrize();

    // Создаём персонажей
    for(int i = 0; i < num; i++)
    {
        ref chr = GetCharacter(NPC_GenerateCharacter("ShipWreck_" + i, model[i], "man", "man", iRank, int(PChar.GenQuest.ShipWreck.nation), -1, true, "citizen"));
        SetFantomParamFromRank(chr, iRank, true);
        string locator = GetAttributeName(GetAttributeN(grp, i));
        ChangeCharacterAddressGroup(chr, loc.id, encGroup, locator);
        //ChangeCharacterAddressGroup(chr, loc.id, "goto", "goto" + (i + 1));
        FaceMaker(chr);
        CirassMaker(chr);
        chr.dialog.filename = "GenQuests_Dialog.c";
        chr.dialog.currentnode = "First time";
        chr.greeting = "robinzons_2"; // Enc_Raiders
        LAi_SetImmortal(chr, true); // До поры нельзя убить
        LAi_SetActorTypeNoGroup(chr);
        if (i == 0)
        {
            PChar.GenQuest.ShipWreck.Name = GenerateRandomName_Generator(int(PChar.GenQuest.ShipWreck.Nation), "man");
            chr.name = PChar.GenQuest.ShipWreck.Name;
            chr.lastname = "";
            LAi_ActorDialog(chr, PChar, "", -1, 0); 
        }
        else LAi_ActorFollow(chr, PChar, "", -1);
        LAi_Group_MoveCharacter(chr, "ShipWreckGroup");
        LAi_Group_SetRelation("ShipWreckGroup", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
    }
    SetFunctionExitFromLocationCondition("ShipWreck_LocationExit", PChar.location, false);				
    Log_TestInfo("Кораблекрушенцы: сгенерился квест");
}

// PIRATES ON UNINHABITED ISLAND
bool JungleEncCheck_PiratesOnUninhabited(ref loc, aref grp)
{
    if (reload_cur_island_index < 0) // Проверка, что пришёл с моря
        return false;
    if ("deadlocked" in loc)
        return false;
    if ("GenQuest.PiratesOnUninhabited" in PChar || "GenQuest.ShipWreck" in PChar)
        return false;
    return true;
}

void JungleEncGenerate_PiratesOnUninhabited(ref loc, string sAreal, string sCity, int iNation, aref grp, string encGroup)
{
    // Кол-во человек
    int num = 2 + int(MOD_SKILL_ENEMY_RATE / 3) + hRand(1, loc.id);
    if (num > @grp) num = @grp;
    PChar.GenQuest.PiratesOnUninhabited.PiratesQty = num;

    // Ранг
    int iRank = int(PChar.rank) + MOD_SKILL_ENEMY_RATE;
    
    // Модельки
    string model[] = {"citiz_41", "citiz_42", "citiz_43", "citiz_44", "citiz_45", "citiz_46", "citiz_47", "citiz_48", "citiz_49", "citiz_50"};
    ArrayShuffle(&model);

    // Создаём персонажей
    for(int i = 0; i < num; i++)
    {
        ref chr = GetCharacter(NPC_GenerateCharacter("PirateOnUninhabited_" + i, model[i], "man", "man", iRank, PIRATE, -1, true, "marginal"));
        SetFantomParamFromRank(chr, iRank, true);
        string locator = GetAttributeName(GetAttributeN(grp, i));
        ChangeCharacterAddressGroup(chr, loc.id, encGroup, locator);
        // ChangeCharacterAddressGroup(chr, loc.id, "goto", "goto" + (i + 1));
        chr.dialog.filename = "GenQuests_Dialog.c";
        chr.dialog.currentnode = "First time";
        chr.greeting = "robinzons_1";
        LAi_SetImmortal(chr, true); // До поры нельзя убить
        LAi_SetActorTypeNoGroup(chr);
        if (i == 0) LAi_ActorDialog(chr, PChar, "", -1, 0.0);
        else LAi_ActorFollow(chr, PChar, "", -1);
        LAi_Group_MoveCharacter(chr, "PiratesOnUninhabitedGroup");
        LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
    }

    PChar.quest.PiratesOnUninhabited_LocExit.win_condition.l1 = "ExitFromLocation";
    PChar.quest.PiratesOnUninhabited_LocExit.win_condition.l1.location = PChar.location;
    PChar.quest.PiratesOnUninhabited_LocExit.function = "PiratesOnUninhabited_LocationExit";
    Log_TestInfo("Пираты на необитайке: сгенерился квест");
}

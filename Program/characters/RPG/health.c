int GetHealthNum(ref ch)
{
    if (!CheckAttribute(ch, "Health"))
	{
        return 0;
	}
    int i;

    i = makeint((stf(ch.Health.HP) + 9) / 10.0); // до целого

    return i;
}

int GetHealthMaxNum(ref ch)
{
    if (!CheckAttribute(ch, "Health"))
	{
        return 0;
	}
    int i;

    i = makeint((stf(ch.Health.maxHP) + 9) / 10.0); // до целого

    return i;
}

string GetHealthName(ref ch)
{
    string name = "";

    switch (GetHealthNum(ch))
    {
        case 1:
            name = ToUpper(StringFromKey("RPGUtilite_2"));
        break;
        case 2:
            name = ToUpper(StringFromKey("RPGUtilite_3"));
        break;
        case 3:
            name = ToUpper(StringFromKey("RPGUtilite_4"));
        break;
        case 4:
            name = ToUpper(StringFromKey("RPGUtilite_5"));
        break;
        case 5:
            name = ToUpper(StringFromKey("RPGUtilite_6"));
        break;
        case 6:
            name = ToUpper(StringFromKey("RPGUtilite_7"));
        break;
    }
    return name;
}

string GetHealthNameMaxSmall(ref ch)
{
    string name = "";

    switch (GetHealthMaxNum(ch))
    {
        case 1:
            name = StringFromKey("RPGUtilite_2");
        break;
        case 2:
            name = StringFromKey("RPGUtilite_3");
        break;
        case 3:
            name = StringFromKey("RPGUtilite_4");
        break;
        case 4:
            name = StringFromKey("RPGUtilite_5");
        break;
        case 5:
            name = StringFromKey("RPGUtilite_6");
        break;
        case 6:
            name = StringFromKey("RPGUtilite_7");
        break;
    }
    return name;
}

void SetNewDayHealth()
{
    ref mainChr = GetMainCharacter();

    float maxhp = stf(mainChr.chr_ai.hp_max);
    float damg  = stf(mainChr.Health.Damg);
    int   add   = 0;

    mainChr.Health.Damg = 0.0;

    if (IsCharacterPerkOn(mainChr, "Medic"))
    {
        add = 1;
    }
	if(IsEquipCharacterByArtefact(mainChr, "amulet_6"))
	{
		if(ShipBonus2Artefact(mainChr, SHIP_GALEON_SM)) add += 1;
		add += 1;
	}
    if (damg >= (maxhp / 1.5) )
    {
        if ((damg / maxhp) > add)
        {
            AddCharacterHealth(mainChr, -damg / maxhp + add);
        }
    }
    else
    {
        if (!IsEntity(&worldMap)) // не на карте
        {
            AddCharacterHealth(mainChr, 1 + add);
        }
        else
        {
            AddCharacterHealth(mainChr, 0.5 + add / 2.0);
        }
    }
}

void SetNewDayHealthMax()
{
    ref mainChr = GetMainCharacter();

    float maxhp = stf(mainChr.chr_ai.hp_max);
    float damg  = stf(mainChr.Health.weekDamg);

    mainChr.Health.weekDamg = 0.0;
	// belamour legendary edition отменное здоровье защищает от инвалидности
	if(CheckCharacterPerk(mainChr, "Medic")) maxhp *= 1.3;
    float fShipBonus = 1.15;
	if(ShipBonus2Artefact(mainChr, SHIP_GALEON_SM)) fShipBonus = 1.25;
    if (damg > (maxhp * 3.5 * isEquippedAmuletUse(mainChr, "amulet_6", 1.0, fShipBonus)))
    {
        AddCharacterMaxHealth(mainChr, -1);
    }
}

void AddCharacterHealth(ref mainChr, float add)
{
	// belamour расширенное издание
	if(mainChr.id == "Blaze" && IsEquipCharacterByArtefact(pchar, "talisman12")) return;
	
    float maxhp = stf(mainChr.chr_ai.hp_max);
    int   remHP = GetHealthNum(mainChr);

    mainChr.Health.HP = makefloat(stf(mainChr.Health.HP) + add);

    if (stf(mainChr.Health.HP) < 1)
    {
        mainChr.Health.HP = 1.0;
    }

    if (stf(mainChr.Health.HP) > stf(mainChr.Health.maxHP))
    {
        mainChr.Health.HP = stf(mainChr.Health.maxHP);
    }

    if (GetHealthNum(mainChr) > remHP)
    {
		notification(StringFromKey("RPGUtilite_8"),"HealthUp");
        //Log_Info("Здоровье стало лучше");
    }

    if (GetHealthNum(mainChr) < remHP)
    {
        //Log_Info("Здоровье стало хуже");
		notification(StringFromKey("RPGUtilite_9"),"HealthDown");
		if(CheckAttribute(mainChr,"systeminfo.tutorial.health"))
		{
			LaunchTutorial("Health", 1);
			DeleteAttribute(mainChr,"systeminfo.tutorial.health");
		}
    }
	Event(EVENT_CT_UPDATE_FELLOW, "a", mainChr);
}

void AddCharacterMaxHealth(ref mainChr, float add)
{
	// belamour расширенное издание
	if(mainChr.id == "Blaze" && IsEquipCharacterByArtefact(pchar, "talisman12")) return;
	
    mainChr.Health.maxHP = makefloat(stf(mainChr.Health.maxHP) + add);

    if (stf(mainChr.Health.maxHP) < 1)
    {
        mainChr.Health.maxHP = 1.0;
    }

    if (stf(mainChr.Health.maxHP) > 60)
    {
        mainChr.Health.maxHP = 60.0;
    }

    if (stf(mainChr.Health.HP) > stf(mainChr.Health.maxHP))
    {
        mainChr.Health.HP = stf(mainChr.Health.maxHP);
    }
}

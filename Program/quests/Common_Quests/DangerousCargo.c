// zagolski - опасный груз
void zpq_Prepare(string qName)
{
	AddLandQuestMarkToPhantom("cumana_ammo", "cumanaAmmoOff");
	AddMapQuestMarkCity("Cumana", false);
}

void zpq_sld1_fc(string qName)
{
	int iRank = sti(pchar.rank)+5;
	int iScl = 20+sti(pchar.rank)*2;
	LAi_group_Delete("EnemyFight");
	LAi_LocationFightDisable(loadedLocation, true);

    	for (i=1; i<=3; i++)
    	{
		sld = GetCharacter(NPC_GenerateCharacter("qp2_"+i, "citiz_"+(i+40), "man", "man", iRank, PIRATE, 0, true, "quest"));
		sld.Dialog.Filename = "Quest\zpq_dialog.c";
		sld.dialog.currentnode = "zpq_sld2";
		sld.greeting = "Enc_Waiker";
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		ChangeCharacterAddressGroup(sld, "Cumana_ExitTown", "goto", "goto5");
		if (i == 1)
		{
			FantomMakeCoolFighter(sld, iRank, iScl+5, iScl+5, "blade_10", "pistol1","bullet", iScl*2);
			LAi_ActorDialog(sld, pchar, "", 3, 0);
			GiveItem2Character(sld, "jewelry4");
			AddMoneyToCharacter(sld, 1000+rand(1000));
			sld.SaveItemsForDead  = true;
			sld.DontClearDead = true;
            if (GetCharacterItem(pchar, "map_part1") == 0)
                GiveItem2Character(sld, "map_part1");
            else if (GetCharacterItem(pchar, "map_full") == 0 && GetCharacterItem(pchar, "map_part2") == 0)
                GiveItem2Character(sld, "map_part2");
			else
                GiveItem2Character(sld, "map_normal");
		}
		else
		{
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_04", "pistol1","bullet", iScl);
			LAi_ActorFollow(sld, characterFromId("qp2_1"), "", -1);
		}
	}		
}

void zpq_seaBattle(string qName)
{
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = 20+sti(pchar.rank)*2;
	LAi_group_Delete("EnemyFight");
	sld = GetCharacter(NPC_GenerateCharacter("zpqCaptain", "citiz_45", "man", "man", iRank, PIRATE, 1, true, "quest"));
	FantomMakeSmallSailor(sld, SHIP_CAREERLUGGER, StringFromKey("DangerousCargo_1"), CANNON_TYPE_CANNON_LBS6, iScl, iScl, iScl, iScl, iScl);
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol3", "grapeshot", iScl*2);
	// belamour legendary edition главный кандидат на регату 
	UpgradeShipZPQ(sld);
    sld.name 	= StringFromKey("DangerousCargo_2");
    sld.lastname = StringFromKey("DangerousCargo_3");
	sld.AlwaysSandbankManeuver = true;
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	SetCharacterPerk(sld, "MusketsShoot");
	LAi_group_MoveCharacter(sld, "EnemyFight");
	Group_AddCharacter("zpq_Group", "zpqCaptain");			
	Group_SetType("zpq_Group", "Pirate");
	Group_SetGroupCommander("zpq_Group", "zpqCaptain");
	Group_SetAddress("zpq_Group", "Cumana", "quest_ships", "quest_ship_4");
	Group_SetTaskAttack("zpq_Group", PLAYER_GROUP);
	Group_LockTask("zpq_Group");
}

// belamour legendary edition 
void UpgradeShipZPQ(ref chr)
{
	sld = chr;
	RealShips[sti(sld.Ship.Type)].MaxCaliber = 8;
	//RealShips[sti(sld.Ship.Type)].CannonsQuantity = 10;
	RealShips[sti(sld.Ship.Type)].MinCrew = 9;
	RealShips[sti(sld.Ship.Type)].OptCrew = 40;
	RealShips[sti(sld.Ship.Type)].MaxCrew = 50;
	RealShips[sti(sld.Ship.Type)].SpeedRate = 13.50;
	RealShips[sti(sld.Ship.Type)].TurnRate = 70.70;
	RealShips[sti(sld.Ship.Type)].HP = 750;
	RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;
	UpgradeShipParameter(sld, "SpeedRate");
	UpgradeShipParameter(sld, "TurnRate");
	UpgradeShipParameter(sld, "WindAgainstSpeed");
	if(CheckAttribute(&RealShips[sti(sld.Ship.Type)],"Tuning.Capacity"))
	{
		DeleteAttribute(&RealShips[sti(sld.Ship.Type)],"Tuning.Capacity");
	}
	RealShips[sti(sld.Ship.Type)].Capacity = 950;
	RealShips[sti(sld.Ship.Type)].BaseHP = RealShips[sti(sld.Ship.Type)].HP;
	UpgradeShipParameter(sld, "Capacity");
	UpgradeShipParameter(sld, "HP");
	UpgradeShipParameter(sld, "MaxCrew");
	UpgradeShipParameter(sld, "MinCrew");
	UpgradeShipParameter(sld, "Cannons");
	DeleteAttribute(sld, "ship.hulls");
	SetCrewQuantity(sld, GetMaxCrewQuantity(sld));
	RealShips[sti(sld.ship.type)].Tuning.All = true;
	//sld.ship.HP = 1020;
}
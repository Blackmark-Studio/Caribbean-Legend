
void ApplyMigration(ref migrationState)
{
	if (!CheckAttribute(&objControlsState, "map.controls.hk_Mine"))
	{
        objControlsState.SettingGroups.FightModeControls = "";
        objControlsState.SettingGroups.PrimaryLand  = "";
        objControlsState.SettingGroups.Sailing3Pers = "";
        objControlsState.SettingGroups.Sailing1Pers = "";
        objControlsState.SettingGroups.WorldMapControls = "";

        aref arKGRoot;
        makearef(arKGRoot, objControlsState.keygroups);
        int nGQ = GetAttributesNum(arKGRoot);
        for(int i = 0; i < nGQ; i++)
        {
            aref arKG  = GetAttributeN(arKGRoot, i);
            string sName = GetAttributeName(arKG);
            if (!IsSettingsGroup(sName)) continue;
            DeleteAttribute(&objControlsState, "keygroups." + sName + ".BICommandsConfirm");
            DeleteAttribute(&objControlsState, "keygroups." + sName + ".BICommandsCancel");
            DeleteAttribute(&objControlsState, "keygroups." + sName + ".BICommandsUp");
            DeleteAttribute(&objControlsState, "keygroups." + sName + ".BICommandsDown");
            DeleteAttribute(&objControlsState, "keygroups." + sName + ".BICommandsLeft");
            DeleteAttribute(&objControlsState, "keygroups." + sName + ".BICommandsRight");
        }

        DeleteAttribute(&objControlsState, "map.controls.BICommandsConfirm.SyncLock");
        DeleteAttribute(&objControlsState, "map.controls.BICommandsCancel.SyncLock");
        DeleteAttribute(&objControlsState, "map.controls.BICommandsUp.SyncLock");
        DeleteAttribute(&objControlsState, "map.controls.BICommandsDown.SyncLock");
        DeleteAttribute(&objControlsState, "map.controls.BICommandsLeft.SyncLock");
        DeleteAttribute(&objControlsState, "map.controls.BICommandsRight.SyncLock");

        CI_CreateAndSetControls("BattleInterfaceControls", "BICommandsConfirm2", CI_GetKeyCode("VK_LBUTTON"), 0, false);
        CI_CreateAndSetControls("BattleInterfaceControls", "BICommandsCancel2",  CI_GetKeyCode("VK_RBUTTON"), 0, false);
        CI_CreateAndSetControls("BattleInterfaceControls", "BICommandsLeftW",  CI_GetKeyCode("VK_MWHEEL_UP"), 0, false);
        CI_CreateAndSetControls("BattleInterfaceControls", "BICommandsRightW", CI_GetKeyCode("VK_MWHEEL_DOWN"), 0, false);

        SameBindingAllowed("ChrAltAttackBase", "ChrAimingShot", 0);
        SameBindingAllowed("BICommandsConfirm2", "ChrAltAttackBase", 0);
        SameBindingAllowed("BICommandsConfirm2", "ChrAimingShot", 0);
        SameBindingAllowed("BICommandsConfirm2", "Ship_Fire", 0);
        SameBindingAllowed("BICommandsCancel2", "ChrForward2", 0);
        SameBindingAllowed("BICommandsCancel2", "ChrAttackBase", 0);
        SameBindingAllowed("BICommandsCancel2", "FireCamera_Set", 0);

        BI_MarkAlwaysDisplay();

		CI_CreateAndSetControls("Sailing3Pers","hk_Mine", CI_GetKeyCode("KEY_G"), 0, true);
        AddControlToGroups("hk_Mine", "Sailing1Pers", "BattleInterfaceControls", "SailingFire", "");
	}

    Set_inDialog_Attributes();

    ref rIsland = GetIslandByID("Jamaica");
    rIsland.reload.l4.istown = true;

    ref rLoc = FindLocationById("Villemstad_Graveyard");
    rLoc.fastreload = "Villemstad";
    rLoc = FindLocationById("Villemstad_ExitTown");
    rLoc.fastreload = "Villemstad";
    rLoc = FindLocationById("Villemstad_ClockCellar");
    DeleteAttribute(rLoc, "HWIC");
    rLoc = FindLocationById("Villemstad_ClockTower");
    DeleteAttribute(rLoc, "HWIC");
    rLoc = FindLocationById("PortRoyal_Graveyard");
    rLoc.fastreload = "PortRoyal";
    rLoc = FindLocationById("PortRoyal_ExitTown");
    rLoc.fastreload = "PortRoyal";
    rLoc = FindLocationById("Havana_Graveyard");
    rLoc.fastreload = "Havana";
    rLoc = FindLocationById("Havana_ExitTown");
    rLoc.fastreload = "Havana";
    rLoc = FindLocationById("Charles_ExitTown");
    rLoc.fastreload = "Charles";
    rLoc = FindLocationById("Charles_Graveyard");
    rLoc.fastreload = "Charles";
    rLoc = FindLocationById("Bridgetown_Plantation");
    rLoc.fastreload = "Bridgetown";
    rLoc = FindLocationById("Maracaibo_ExitTown");
    rLoc.fastreload = "Maracaibo";
    rLoc = FindLocationById("Maracaibo_Plantation");
    rLoc.fastreload = "Maracaibo";
    rLoc = FindLocationById("PortoBello_ExitTown");
    rLoc.fastreload = "PortoBello";
    rLoc = FindLocationById("PortoBello_Plantation");
    rLoc.fastreload = "PortoBello";
}

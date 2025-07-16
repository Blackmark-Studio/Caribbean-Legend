int g_LocLngFileID = -1;

object objLandInterface;
object objFastReloadTable;
object objTownStateTable;
int g_intRetVal;

bool bDisableFastReload = false;

int FLqty = 0;
int FSqty = 0;
int FHqty = 0;
int Mqty = 0;
int iShowTime = 15;

#define	BLI_UPDATE_PERIOD 400
#event_handler("evntBattleCommandSound","procBattleCommandSound");

bool bLandInterfaceStart = false;

void procBattleCommandSound()
{
	string comName = GetEventData();
	if(comName=="deactivate")
	{
		PlaySound("interface\ok.wav");
	}
	if(comName=="activate")
	{
		PlaySound("interface\ok.wav");
	}
	if(comName=="right" || comName=="left")
	{
		PlaySound("interface\ok.wav");
	}
}

void InitBattleLandInterface()
{
	if( IsEntity(&objLandInterface) ) 
	{
		EndBattleLandInterface();
	}
	bLandInterfaceStart = false;
	SetEventHandler(EVENT_LOCATION_LOAD,"StartBattleLandInterface",0);
	SetEventHandler(EVENT_LOCATION_UNLOAD,"EndBattleLandInterface",0);
	LoadLIStates();
}

void BLI_EnableShow()
{
	SetLandInterfaceShow( sti(InterfaceStates.BattleShow.Command) );
}

void BLI_DisableShow()
{
	SetLandInterfaceShow(false);
}

void SetLandInterfaceShow(bool commandosShow)
{
	SendMessage(&objLandInterface,"ll",MSG_BATTLE_LAND_SET_SHOW,commandosShow);
}

void StartBattleLandInterface()
{
	if(bLandInterfaceStart)
	{
		return;
	}
	if (bGameMenuStart)
	{
		return;
	}
	bLandInterfaceStart = true;

	BLI_SetObjectData();
	if(FindLoadedLocation() != -1) ControlsLandDesc();
	BLI_SetMessageParameters();
	CreateEntity(&objLandInterface,"battle_land_interface");
	LayerAddObject(EXECUTE,&objLandInterface,-1);
	LayerAddObject(REALIZE,&objLandInterface,-1);

	SetEventHandler(EVENT_CHANGE_OFFICERS,"BLI_UpdateOfficers",0);
	SetEventHandler(EVENT_DIALOG_START,"BLI_DisableShow",0);
	SetEventHandler(EVENT_DIALOG_EXIT,"BLI_EnableShow",0);

	if(dialogRun) BLI_DisableShow();
	else BLI_EnableShow();

	SetEventHandler("evntBLI_Update","BLI_UpdateObjectData",0);
	SetEventHandler("BI_CommandEndChecking","BLI_CheckCommand",0);
	SetEventHandler("BI_LaunchCommand","BLI_ExecuteCommand",0);
	SetEventHandler("BI_SetPossibleCommands","BLI_SetPossibleCommands",0);
	SetEventHandler("evntFindDialogChar","procFindDialogChar",0);
	SetEventHandler("Location_CharacterEntryToLocator", "BLI_ChrEnterToLocation", 0);
	SetEventHandler("Location_CharacterExitFromLocator", "BLI_ChrExitFromLocation", 0);
	SetEventHandler("evntPerkAgainUsable","BLI_RefreshCommandMenu",0);
	SetEventHandler("Control Activation","LI_ProcessControlPress",0);
	CreateILogAndActions(LOG_FOR_LAND);
	Event("evntBLI_Update");
	Event("evntFindDialogChar");
	SendMessage(&objLandInterface,"ll",MSG_BATTLE_LAND_SHOW_EQUIPMENT, bShowEquipment());
    TW_Init();
}

ref BLI_CheckCommand()
{
	string commandName = GetEventData();

	aref uiref;	makearef(uiref,objLandInterface.UserIcons);
	aref ar;
	int nq = GetAttributesNum(uiref);
	int i;

	bool bUsed = false;
	for(i=0; i<nq; i++)
	{
		ar = GetAttributeN(uiref,i);
		ar.enable = false;
	}
	g_intRetVal = BI_COMMODE_USER_ICONS;

	switch(commandName)
	{
	case "cancel":
		g_intRetVal = -1;
	break;

	case "BI_FastReload":
		bUsed = SetReloadIcons();
	break;

	case "BI_ItemsUse":
		bUsed = SetUsedPotionIcons();
	break;

	case "BI_DialogStart":
		g_intRetVal = 0;
	break;

	case "BI_ItemsChange":
		g_intRetVal = 0;
	break;

	case "BI_TakeItem":
		g_intRetVal = 0;
	break;

	case "BI_PlaceItem":
		g_intRetVal = 0;
	break;

	case "BI_OutDoor":
		g_intRetVal = 0;
	break;

	case "BI_UseBox":
		g_intRetVal = 0;
	break;
	// boal
    case "BI_DeadBox":
		g_intRetVal = 0;
	break;
	case "BI_PlayEvent":
		g_intRetVal = 0;
	break;
	case "BI_TalkSelf":
		g_intRetVal = 0;
	break;
	
	case "BI_SelfRepair":
		g_intRetVal = 0;
	break;
	
	case "BI_Alchemy":
		g_intRetVal = 0;
	break;
	
	case "BI_MapAtlas":
		g_intRetVal = 0;
	break;

	case "BI_Rest":
		g_intRetVal = 0;
	break;
	
	case "BI_ActivateRush":
		g_intRetVal = 0;
	break;
	
	case "BI_Exit_Deck": //boal
		g_intRetVal = 0;
	break;
	}

	return &g_intRetVal;
}

void BLI_ExecuteCommand()
{
	int		chrIdx = GetEventData();
	string	commName = GetEventData();
	int		targChrIdx = GetEventData();
	string	evntName = GetEventData();

	aref arFader;
	if( GetEntity(arFader,"fader") ) {return;}

	aref	uiref;
	int		curLocIdx;
	int		tmpi;

	if( commName=="cancel" || evntName=="cancel" ) {
		SendMessage(&objLandInterface,"ls",MSG_BATTLE_LAND_MAKE_COMMAND,"cancel");
		return;
	}

	switch(commName)
	{
	case "BI_FastReload":
		{
			curLocIdx = FindLoadedLocation();
			if(curLocIdx==-1) return;
			if( FindUserIcon(evntName,&uiref) )
			{
				string sTravelLocator = "";
				if(CheckAttribute(uiref,"locator")) {sTravelLocator=uiref.locator;}
				if(CheckAttribute(uiref,"location"))
				{
					PlayerFastTravel(curLocIdx, uiref.location, sTravelLocator);
				}
			}
		}
	break;
	case "BI_ItemsUse":
		if( FindUserIcon(evntName,&uiref) )
		{
			if(CheckAttribute(uiref,"potion"))
			{
				aref arItm;
				if( Items_FindItem(uiref.potion,&arItm) >= 0 )
				{
					if( CheckAttribute(arItm,"potion") )
					{
						DoCharacterUsedItem(pchar,arItm.id);
					}
				}
			}
		}
	break;
	case "BI_DialogStart":
		tmpi = SendMessage(pchar,"ls",MSG_CHARACTER_EX_MSG,"FindDialogCharacter");
		if(tmpi>=0)	Event("dlgReady","l",tmpi);
	break;
	case "BI_ItemsChange":
		tmpi = SendMessage(pchar,"ls",MSG_CHARACTER_EX_MSG,"FindDialogCharacter");
		if(tmpi>=0 && isOfficerInShip(GetCharacter(tmpi), true))//fix вот дыра для обмена с матросом
        {
            LaunchCharacterItemChange(GetCharacter(tmpi));
        }
        // boal 22.01.2004 -->
		else
		{
			if (tmpi>=0 && CheckAttribute(GetCharacter(tmpi), "IsCompanionClone")) // 1.2.4
			{
			    LaunchCharacterItemChange(GetCharacter(tmpi));
			}
			else
			{
				// обмен с офицером всегда и везде (в абордаже нет диалога!)
			    tmpi = LAi_FindNearestVisCharacter(GetMainCharacter(), 1);
			    if( tmpi>0 && IsOfficer(GetCharacter(tmpi)))
				{
				    LaunchCharacterItemChange(GetCharacter(tmpi));
				}
			}
		}
	break;
	case "BI_TakeItem":
		Item_OnPickItem();
	break;
	case "BI_PlaceItem":
		Item_OnUseItem();
	break;
	case "BI_OutDoor":
		Event("Control Activation","s","ChrAction");
	break;
	case "BI_UseBox":
		OpenBoxProcedure();
	break;
	case "BI_PlayEvent":
		PlayLocatorEvent();
	break;
	// boal
	case "BI_DeadBox":
		Dead_OpenBoxProcedure();
	break;
	
	case "BI_TalkSelf":
		DoQuestCheckDelay("TalkSelf_Start", 0.2);
	break;
	
	case "BI_SelfRepair":		
		LaunchRepair(pchar);
	break;
	
	case "BI_Alchemy":
		CheckAlchemyRecipe();
		LaunchAlchemyScreen();
	break;
	
	case "BI_MapAtlas":
		LaunchMapViewScreen();
	break;

	case "BI_Rest":
		LaunchTavernWaitScreen();
	break;
	
	case "BI_ActivateRush":
		ActivateCharacterPerk(pchar,"Rush");
		PerkBerserkerReaction();
	break;
	// boal
    case "BI_Exit_Deck":
        if (isShipInside(pchar.location) || CheckShipSituation_GenQuest())
        {
			Return2SeaAfterCabin();
        }
        else
        {
			int idxLoadLoc = FindLoadedLocation();
			if (idxLoadLoc != -1)
			{
				UnloadLocation(&Locations[idxLoadLoc]);
			}
			wdmReloadToSea();
        }
    break;
	}

}

void EndBattleLandInterface()
{
	if(!bLandInterfaceStart) return;
	bLandInterfaceStart = false;

	DeleteAttribute( pchar, "boxname" );

	BLI_DisableShow();
	SendMessage(&objLandInterface,"l",MSG_BATTLE_LAND_END);

	DeleteClass(&objLandInterface);

	DelEventHandler(EVENT_CHANGE_OFFICERS,"BLI_UpdateOfficers");
	DelEventHandler(EVENT_DIALOG_START,"BLI_DisableShow");
	DelEventHandler(EVENT_DIALOG_EXIT,"BLI_EnableShow");

	DelEventHandler("evntBLI_Update","BLI_UpdateObjectData");
	DelEventHandler("BI_CommandEndChecking","BLI_CheckCommand");
	DelEventHandler("BI_LaunchCommand","BLI_ExecuteCommand");
	DelEventHandler("BI_SetPossibleCommands","BLI_SetPossibleCommands");
	DelEventHandler("evntFindDialogChar","procFindDialogChar");
	DelEventHandler("Location_CharacterEntryToLocator", "BLI_ChrEnterToLocation");
	DelEventHandler("Location_CharacterExitFromLocator", "BLI_ChrExitFromLocation");
	DelEventHandler("evntPerkAgainUsable","BLI_RefreshCommandMenu");
	DelEventHandler("Control Activation","LI_ProcessControlPress");

	Log_SetActiveAction("Nothing");
    TW_Close();
}

void BLI_SetObjectData()
{
    float fHtRatio = stf(Render.screen_y) / iHudScale;
    int fTmp, fTmp2;
	DeleteAttribute(&objLandInterface,"");

	objLandInterface.parameters.DoShowCommandos = InterfaceStates.BattleShow.Command;
	objLandInterface.data.Alarm = 0; // нет тревоги

	// персы вместе с нами
	aref ar;
	int i,cn;
	ref curCh;
	string attrName;
	for(i=0; i<4; i++)
	{
		cn = GetOfficersIndex(pchar,i);
		if(cn==-1) continue;
		curCh = GetCharacter(cn);
		attrName = "id"+i;
		makearef(ar,objLandInterface.data.icons.(attrName));
		SetCharacterIconData(cn,ar);
		//ar.picture = curCh.FaceId;
		//ar.health = 0.0;
		//ar.charge = 0.0;
	}
	BLI_SetMessageParameters();
	// текстуры
	int idLngFile = LanguageOpenFile("commands_name.txt");
	objLandInterface.CommandTextures.list.t0.name = "interfaces\le\battle_interface\LandCommands.tga.tx";
	objLandInterface.CommandTextures.list.t0.xsize = 16;
	objLandInterface.CommandTextures.list.t0.ysize = 4;
	
 	objLandInterface.CommandTextures.list.t1.name = "interfaces\le\battle_interface\LandTarget_SLB.tga.tx";
	objLandInterface.CommandTextures.list.t1.xsize = 16;
	objLandInterface.CommandTextures.list.t1.ysize = 4;
	
	objLandInterface.CommandTextures.list.t2.name = "interfaces\le\battle_interface\Cancel.tga.tx";
	objLandInterface.CommandTextures.list.t2.xsize = 2;
	objLandInterface.CommandTextures.list.t2.ysize = 1;
	// boal <--
	objLandInterface.CommandTextures.CommandTexNum = 0;
	//
	DeleteAttribute(&objIconsNote,"");
	objIconsNote.1x0 = LanguageConvertString(idLngFile, "go_store");
	objIconsNote.1x1 = LanguageConvertString(idLngFile, "go_shipyard");
	objIconsNote.1x2 = LanguageConvertString(idLngFile, "go_tavern");
	objIconsNote.1x4 = LanguageConvertString(idLngFile, "go_residence");
	objIconsNote.1x3 = LanguageConvertString(idLngFile, "go_usurer");
	objIconsNote.1x6 = LanguageConvertString(idLngFile, "go_church");
	objIconsNote.1x7 = LanguageConvertString(idLngFile, "go_exittown");
	objIconsNote.1x9 = LanguageConvertString(idLngFile, "go_brothel");
	objIconsNote.1x10 = LanguageConvertString(idLngFile, "go_port");
	objIconsNote.1x8 = LanguageConvertString(idLngFile, "go_portman");
	objIconsNote.1x5 = LanguageConvertString(idLngFile, "go_prison");
	// belamour legendary edition для LSC -->
	objIconsNote.11x0 = LanguageConvertString(idLngFile, "go_EsmeraldaStoreBig");
	objIconsNote.11x34 = LanguageConvertString(idLngFile, "go_CeresSmithy_Jurgen");
	objIconsNote.11x2 = LanguageConvertString(idLngFile, "go_FleuronTavern");
	objIconsNote.11x13 = LanguageConvertString(idLngFile, "go_SanAugustineResidence");
	objIconsNote.11x36 = LanguageConvertString(idLngFile, "go_ProtectorFisher");
	objIconsNote.11x3 = LanguageConvertString(idLngFile, "go_Caroline");
	objIconsNote.11x5 = LanguageConvertString(idLngFile, "go_TartarusPrison");
	objIconsNote.11x6 = LanguageConvertString(idLngFile, "go_GloriaChurch");
	objIconsNote.11x39 = LanguageConvertString(idLngFile, "go_CeresSmithy_Mary");
	// <-- lsc
	
	// список команд
	objLandInterface.Commands.Cancel.enable		    = false;
	objLandInterface.Commands.Cancel.picNum		    = 1;
	objLandInterface.Commands.Cancel.selPicNum	    = 0;
	objLandInterface.Commands.Cancel.texNum		    = 2;
	objLandInterface.Commands.Cancel.event		    = "Cancel";
	objLandInterface.Commands.Cancel.name		    = "Cancel";
	objLandInterface.Commands.Cancel.note		    = LanguageConvertString(idLngFile, "sea_cancel");

	objLandInterface.Commands.FastReload.enable		= true;
	objLandInterface.Commands.FastReload.picNum		= 27;
	objLandInterface.Commands.FastReload.selPicNum	= 11;
	objLandInterface.Commands.FastReload.texNum		= 1;
	objLandInterface.Commands.FastReload.event		= "BI_FastReload";
	objLandInterface.Commands.FastReload.note		= LanguageConvertString(idLngFile, "land_FastReload");

	objLandInterface.Commands.OutDoor.enable		= true;
	objLandInterface.Commands.OutDoor.picNum		= 28;
	objLandInterface.Commands.OutDoor.selPicNum		= 12;
	objLandInterface.Commands.OutDoor.texNum		= 1;
	objLandInterface.Commands.OutDoor.event			= "BI_OutDoor";
	objLandInterface.Commands.OutDoor.note			= LanguageConvertString(idLngFile, "land_OutDoor");
	// boal -->
    objLandInterface.Commands.ItemsUse.enable		= true;
 	objLandInterface.Commands.ItemsUse.picNum		= 20;
	objLandInterface.Commands.ItemsUse.selPicNum	= 4;
	objLandInterface.Commands.ItemsUse.texNum		= 0;
	objLandInterface.Commands.ItemsUse.event		= "BI_ItemsUse";
	objLandInterface.Commands.ItemsUse.note			= LanguageConvertString(idLngFile, "land_ItemsUse");
	
	objLandInterface.Commands.DialogStart.enable	= true;
 	objLandInterface.Commands.DialogStart.picNum	= 17;
	objLandInterface.Commands.DialogStart.selPicNum	= 1;
	objLandInterface.Commands.DialogStart.texNum	= 0;
	objLandInterface.Commands.DialogStart.event		= "BI_DialogStart";
	objLandInterface.Commands.DialogStart.note		= LanguageConvertString(idLngFile, "land_DialogStart");
	
	objLandInterface.Commands.ItemsChange.enable	= true;
 	objLandInterface.Commands.ItemsChange.picNum	= 19;
	objLandInterface.Commands.ItemsChange.selPicNum	= 3;
	objLandInterface.Commands.ItemsChange.texNum	= 0;
	objLandInterface.Commands.ItemsChange.event		= "BI_ItemsChange";
	objLandInterface.Commands.ItemsChange.note		= LanguageConvertString(idLngFile, "land_ItemsChange");
	
	objLandInterface.Commands.TakeItem.enable		= true;
 	objLandInterface.Commands.TakeItem.picNum		= 16;
	objLandInterface.Commands.TakeItem.selPicNum	= 0;
	objLandInterface.Commands.TakeItem.texNum		= 0;
	objLandInterface.Commands.TakeItem.event		= "BI_TakeItem";
	objLandInterface.Commands.TakeItem.note			= LanguageConvertString(idLngFile, "land_TakeItem");
	
	objLandInterface.Commands.PlaceItem.enable		= true;
 	objLandInterface.Commands.PlaceItem.picNum		= 16;
	objLandInterface.Commands.PlaceItem.selPicNum	= 0;
	objLandInterface.Commands.PlaceItem.texNum		= 0;
	objLandInterface.Commands.PlaceItem.event		= "BI_PlaceItem";
	objLandInterface.Commands.PlaceItem.note		= LanguageConvertString(idLngFile, "land_PlaceItem");

	objLandInterface.Commands.UseBox.enable			= true;
 	objLandInterface.Commands.UseBox.picNum		    = 51;
	objLandInterface.Commands.UseBox.selPicNum		= 35;
	objLandInterface.Commands.UseBox.texNum			= 0;
	objLandInterface.Commands.UseBox.event			= "BI_UseBox";
	objLandInterface.Commands.UseBox.note			= LanguageConvertString(idLngFile, "land_UseBox");
	
	objLandInterface.Commands.DeadBox.enable		= true;
 	objLandInterface.Commands.DeadBox.picNum		= 51;
	objLandInterface.Commands.DeadBox.selPicNum		= 35;
	objLandInterface.Commands.DeadBox.texNum		= 0;
	objLandInterface.Commands.DeadBox.event			= "BI_DeadBox";
	objLandInterface.Commands.DeadBox.note			= LanguageConvertString(idLngFile, "land_ItemsDead");
	
	objLandInterface.Commands.PlayEvent.enable		= true;
 	objLandInterface.Commands.PlayEvent.picNum		= 16;
	objLandInterface.Commands.PlayEvent.selPicNum	= 0;
	objLandInterface.Commands.PlayEvent.texNum		= 0;
	objLandInterface.Commands.PlayEvent.event		= "BI_PlayEvent";
	objLandInterface.Commands.PlayEvent.note		= XI_ConvertString("for_quick_action_Use");//LanguageConvertString(idLngFile, "land_ItemsDead");
	// диалог сам с собой -->
	objLandInterface.Commands.TalkSelf.enable		= true;
 	objLandInterface.Commands.TalkSelf.picNum	 	= 18;
	objLandInterface.Commands.TalkSelf.selPicNum	= 2;
	objLandInterface.Commands.TalkSelf.texNum		= 0;
	objLandInterface.Commands.TalkSelf.event		= "BI_TalkSelf";
	objLandInterface.Commands.TalkSelf.note			= LanguageConvertString(idLngFile, "land_TalkSelf");
	// диалог сам с собой <--
	// починка -->
	objLandInterface.Commands.SelfRepair.enable	= true;
 	objLandInterface.Commands.SelfRepair.picNum	 	= 48;
	objLandInterface.Commands.SelfRepair.selPicNum	= 32;
	objLandInterface.Commands.SelfRepair.texNum		= 0;
	objLandInterface.Commands.SelfRepair.event		= "BI_SelfRepair";
	objLandInterface.Commands.SelfRepair.note		= LanguageConvertString(idLngFile, "land_SelfRepair");
	// починка <--
	// алхимия -->	
	objLandInterface.Commands.Alchemy.enable		= true;
 	objLandInterface.Commands.Alchemy.picNum	 	= 49;
	objLandInterface.Commands.Alchemy.selPicNum	 	= 33;
	objLandInterface.Commands.Alchemy.texNum		= 0;
	objLandInterface.Commands.Alchemy.event			= "BI_Alchemy";
	objLandInterface.Commands.Alchemy.note			= LanguageConvertString(idLngFile, "land_Alchemy");
	// алхимия <--
	// атлас -->	
	objLandInterface.Commands.MapAtlas.enable		= true;
 	objLandInterface.Commands.MapAtlas.picNum	 	= 50;
	objLandInterface.Commands.MapAtlas.selPicNum	= 34;
	objLandInterface.Commands.MapAtlas.texNum		= 0;
	objLandInterface.Commands.MapAtlas.event		= "BI_MapAtlas";
	objLandInterface.Commands.MapAtlas.note			= LanguageConvertString(idLngFile, "land_MapAtlas");
	// атлас <--
	// отдых/проматывание времени -->	
	objLandInterface.Commands.Rest.enable			= true;
 	objLandInterface.Commands.Rest.picNum	 		= 52;
	objLandInterface.Commands.Rest.selPicNum		= 36;
	objLandInterface.Commands.Rest.texNum			= 0;
	objLandInterface.Commands.Rest.event			= "BI_Rest";
	objLandInterface.Commands.Rest.note				= LanguageConvertString(idLngFile, "land_Rest");
	// отдых/проматывание времени <--
	objLandInterface.Commands.ActivateRush.enable	= true;
	objLandInterface.Commands.ActivateRush.picNum	= 28;
	objLandInterface.Commands.ActivateRush.selPicNum	= 12;
	objLandInterface.Commands.ActivateRush.texNum		= 0;
	objLandInterface.Commands.ActivateRush.event	= "BI_ActivateRush";
	objLandInterface.Commands.ActivateRush.note		= LanguageConvertString(idLngFile, "land_ActivateRush");
	
	objLandInterface.Commands.Exit_Deck.enable		= true;
	objLandInterface.Commands.Exit_Deck.picNum		= 30;
	objLandInterface.Commands.Exit_Deck.selPicNum	= 14;
	objLandInterface.Commands.Exit_Deck.texNum		= 0;
	objLandInterface.Commands.Exit_Deck.event		= "BI_Exit_Deck";
	objLandInterface.Commands.Exit_Deck.note		= LanguageConvertString(idLngFile, "land_Exit");
	// boal <--
	// список пользовательских картинок
	LanguageCloseFile(idLngFile);
	// go to icons
	int idxloc = FindLoadedLocation();
	string outGroupName = "";
	RecalculateHireCrew(idxloc);  // to_do убрать на таймер
	if(idxloc>=0 && CheckAttribute(&Locations[idxloc],"fastreload"))
	{
		outGroupName = Locations[idxloc].fastreload;
		CreateReloadPaths(outGroupName);
	}

	// MC backicon -->
	objLandInterface.ManSign.backmctexturename		= "interfaces\le\battle_interface\CharBackIcon0.tga.tx";
	objLandInterface.ManSign.backmccolor			= argb(255,128,128,128);
	objLandInterface.ManSign.backmcuv				= "0.0,0.0,1.0,1.0";
	objLandInterface.ManSign.backmcoffset			= "0,0"; //"0.0,0.0";
	fTmp = makeint(128.0 * fHtRatio);
    objLandInterface.ManSign.backmciconsize			= fTmp + "," + fTmp;
	
	objLandInterface.ManSign.manstatebacktexturename	= "interfaces\le\battle_interface\CharStateBackIcon.tga.tx";
	objLandInterface.ManSign.manstatebackcolor		= argb(255,128,128,128);
	objLandInterface.ManSign.manstatebackuv			= "0.0,0.0,1.0,1.0";
	fTmp = makeint(180.0 * fHtRatio);
    fTmp2 = makeint(0.0 * fHtRatio);	
	objLandInterface.ManSign.manstatebackoffset		= fTmp + "," + fTmp2;
	fTmp = makeint(256.0 * fHtRatio);
	fTmp2 = makeint(64.0 * fHtRatio);
    objLandInterface.ManSign.manstatebackiconsize	= fTmp + "," + fTmp2;
	//<--
	
	//mc states progressbars -->
	objLandInterface.ManSign.manstatemctexturename	= "interfaces\le\battle_interface\CharStateHorizontal.tga.tx";
	objLandInterface.ManSign.manstatemccolor		= argb(255,128,128,128);
	objLandInterface.ManSign.manmchpuv				= "0.1953,0.2187,0.9765,0.4687";
	objLandInterface.ManSign.manmcenegryuv			= "0.1953,0.5937,0.9765,0.7812";
	
	fTmp = makeint(202.0 * fHtRatio);
    fTmp2 = makeint(-10.0 * fHtRatio);
    objLandInterface.ManSign.manmchpoffset			= fTmp + "," + fTmp2;
	fTmp2 = makeint(12.0 * fHtRatio);
    objLandInterface.ManSign.manmcenegryoffset		= fTmp + "," + fTmp2;

	fTmp = makeint(200.0 * fHtRatio);
    fTmp2 = makeint(16.0 * fHtRatio);
    objLandInterface.ManSign.manvchpiconsize		= fTmp + "," + fTmp2;
	fTmp2 = makeint(12.0 * fHtRatio);
    objLandInterface.ManSign.manmcenergyiconsize	= fTmp + "," + fTmp2;
	//<--
	
	float fRes = 0.9; // для ресайза компаньонов	
	objLandInterface.ManSign.backtexturename		= "interfaces\le\battle_interface\CharBackIcon.tga.tx";
	objLandInterface.ManSign.backcolor				= argb(255,128,128,128);
	objLandInterface.ManSign.backuv					= "0.0,0.0,1.0,1.0";
	objLandInterface.ManSign.backoffset				= "0,0"; //"0.0,0.0";
	fTmp = makeint(128.0 * fRes * fHtRatio);
    objLandInterface.ManSign.backiconsize			= fTmp + "," + fTmp;

	objLandInterface.ManSign.manrankratetexturename		= "interfaces\le\battle_interface\CharStatexp.tga.tx";
	objLandInterface.ManSign.manrankratecolor			= argb(255,128,128,128);
	objLandInterface.ManSign.manrankratepuv				= "0.0,0.0,1.0,1.0";
	objLandInterface.ManSign.manrankrate0offset			= "0.0,0.0"; 
	objLandInterface.ManSign.manrankrateoffset			= "0.0,0.0"; 
	fTmp = makeint(128.0 * fHtRatio);
    objLandInterface.ManSign.manrankrate0iconsize		= fTmp + "," + fTmp;
	fTmp = makeint(128.0 * fRes * fHtRatio);
    objLandInterface.ManSign.manrankrateiconsize		= fTmp + "," + fTmp;
	
	objLandInterface.ManSign.rankfontid			= "interface_normal";
	objLandInterface.ManSign.rankfontcolor		= argb(255,255,255,255);													 
	objLandInterface.ManSign.rank0fontscale		= 1.2 * fHtRatio;
	fTmp = makeint(0.0 * fHtRatio);
    fTmp2 = makeint(39.0 * fHtRatio);
    objLandInterface.ManSign.rank0fontoffset       = fTmp + "," + fTmp2;

	objLandInterface.ManSign.rankfontscale		= 1.2 * fRes * fHtRatio;
	fTmp = makeint(0.0 * fHtRatio);
    fTmp2 = makeint(36.0 * fHtRatio);
    objLandInterface.ManSign.rankfontoffset       = fTmp + "," + fTmp2;
	
	objLandInterface.ManSign.energyvaluefontid			= "interface_normal";
	objLandInterface.ManSign.energyvaluefontcolor		= argb(255,255,255,255);
	fTmp = makeint(200.0 * fHtRatio);
    fTmp2 = makeint(4.0 * fHtRatio);
	objLandInterface.ManSign.energyvaluefontscale	= 1.0 * fHtRatio;
	objLandInterface.ManSign.energyvaluefontoffset  = fTmp + "," + fTmp2;
	
	objLandInterface.ManSign.healthvaluefontid		= "interface_normal";
	objLandInterface.ManSign.healthvaluefontcolor	= argb(255,255,255,255);
	fTmp = makeint(200.0 * fHtRatio);
    fTmp2 = makeint(-18.0 * fHtRatio);
	objLandInterface.ManSign.healthvaluefontscale	= 1.1 * fHtRatio;
	objLandInterface.ManSign.healthvaluefontoffset  = fTmp + "," + fTmp2;

	objLandInterface.ManSign.alarmtexturename		= "interfaces\le\battle_interface\alarmback.tga.tx";
	objLandInterface.ManSign.alarmhighcolor			= argb(255,168,28,28);
	objLandInterface.ManSign.alarmlowcolor			= argb(64,168,28,28);
	objLandInterface.ManSign.alarmuptime			= 0.5;
	objLandInterface.ManSign.alarmdowntime			= 1.5;
	objLandInterface.ManSign.alarmuv				= "0.0,0.0,1.0,1.0";
	objLandInterface.ManSign.alarmoffset			= "0,0"; //"0.0,0.0";
	fTmp = makeint(128.0 * fHtRatio);
     objLandInterface.ManSign.alarmiconsize			= fTmp + "," + fTmp;

	objLandInterface.ManSign.manstatetexturename	= "interfaces\le\battle_interface\CharState.tga.tx";
	objLandInterface.ManSign.manstatecolor			= argb(255,128,128,128);
	objLandInterface.ManSign.manhpuv				= "0.0,0.1601,0.5,0.875";
	objLandInterface.ManSign.manenegryuv			= "0.5,0.1601,1.0,0.875";
	fTmp = makeint(-28.0 * fHtRatio);
    fTmp2 = makeint(2.0 * fHtRatio);
    objLandInterface.ManSign.manhpoffset			= fTmp + "," + fTmp2;
	fTmp = makeint(28.0 * fHtRatio);
    objLandInterface.ManSign.manenegryoffset		= fTmp + "," + fTmp2;
	fTmp = makeint(60.0 * fHtRatio);
    fTmp2 = makeint(83.0 * fHtRatio);
    objLandInterface.ManSign.manhpiconsize			= fTmp + "," + fTmp2;
    objLandInterface.ManSign.manenergyiconsize		= fTmp + "," + fTmp2;

	objLandInterface.ManSign.gunchargetexturename	= "interfaces\le\battle_interface\GunShots.tga";
	objLandInterface.ManSign.gunchargecolor			= argb(0,168,168,48); //argb(255,168,168,48);
	objLandInterface.ManSign.gunchargebackcolor		= argb(0,188,48,48); //argb(255,188,48,48);
	objLandInterface.ManSign.gunchargebackuv		= "0.0,0.5,1.0,1.0";
	objLandInterface.ManSign.gunchargeuv			= "0.0,0.0,1.0,0.5";
	fTmp = makeint(0.0 * fHtRatio);
    fTmp2 = makeint(-53.0 * fHtRatio);
    objLandInterface.ManSign.guncharge0offset	    = fTmp + "," + fTmp2;
	fTmp = makeint(0.0 * fHtRatio);
    fTmp2 = makeint(-48.0 * fHtRatio);
    objLandInterface.ManSign.gunchargeoffset	    = fTmp + "," + fTmp2;
    fTmp = makeint(128.0 * 0.6 * fHtRatio);
    fTmp2 = makeint(32.0 * 0.6 * fHtRatio);
    objLandInterface.ManSign.guncharge0iconsize		= fTmp + "," + fTmp2;
    fTmp = makeint(128.0 * 0.6 * fRes * fHtRatio);
    fTmp2 = makeint(32.0 * 0.6 * fRes * fHtRatio);
    objLandInterface.ManSign.gunchargeiconsize		= fTmp + "," + fTmp2;

	objLandInterface.ManSign.gunchargeprogress		= "0.0, 0.234375, 0.40625, 0.59375, 0.765625, 0.985, 0.99"; //"0.0625, 0.211, 0.359, 0.5, 0.633, 0.765, 0.983";"0.0, 0.234375, 0.40625, 0.59375, 0.78125, 0.96, 0.99";

	objLandInterface.ManSign.manfacecolor			= argb(255,128,128,128);
	fTmp = makeint(0 * fHtRatio);
    fTmp2 = makeint(15 * fHtRatio);
    objLandInterface.ManSign.manface0offset			= fTmp + "," + fTmp2;
	fTmp = makeint(128.0 * fHtRatio);
    objLandInterface.ManSign.manface0iconsize		= fTmp + "," + fTmp;

	fTmp = makeint(0 * fHtRatio);
    fTmp2 = makeint(15 * fRes * fHtRatio);
    objLandInterface.ManSign.manfaceoffset			= fTmp + "," + fTmp2;
	fTmp = makeint(128.0 * fRes * fHtRatio);
    objLandInterface.ManSign.manfaceiconsize		= fTmp + "," + fTmp;
	
    objLandInterface.ManSign.commandlistverticaloffset0 = -30 * fHtRatio;
	objLandInterface.ManSign.commandlistverticaloffset = 30 * fHtRatio;

	fTmp = makeint(75.0 * fHtRatio);
    fTmp2 = makeint(130.0 * fHtRatio);
	
	for(i = 1; i<=5; i++) 
	{
		string sOffsetIcon = "iconoffset" + i;
		objLandInterface.ManSign.(sOffsetIcon) = fTmp + "," + (fTmp + (i-1)*fTmp2);
	}
	
	// belamour блок снаряжения
	fTmp = sti(showWindow.left) + RecalculateHIcon(makeint(180.0 * fHtRatio));
	fTmp2 = sti(showWindow.bottom) - RecalculateVIcon(makeint(180.0 * fHtRatio));
	objLandInterface.equipment.BIequipmentPos		= fTmp + "," + fTmp2;
	
	objLandInterface.equipment.Backtexturename		= "interfaces\le\battle_interface\items\equipment_back.tga";
	objLandInterface.equipment.Backcolor			= argb(255,128,128,128);
	objLandInterface.equipment.Backuv				= "0.0,0.0,1.0,1.0";
	objLandInterface.equipment.Backoffset			= "0.0,0.0"; 
	fTmp = makeint(256.0 * fHtRatio);
    objLandInterface.equipment.Backiconsize	        = fTmp + "," + fTmp;
	
	objLandInterface.equipment.Bladetexturename		= "interfaces\le\battle_interface\items\blade_empty.tga";
	objLandInterface.equipment.Bladecolor			= argb(255,128,128,128);
	objLandInterface.equipment.Bladeuv				= "0.0,0.0,1.0,1.0";
	fTmp = makeint(-64.0 * fHtRatio);
	fTmp2 = makeint(0.0 * fHtRatio);
	objLandInterface.equipment.Bladeoffset			= fTmp + "," + fTmp2;
	fTmp = makeint(128.0 * 0.65 * fHtRatio);
    objLandInterface.equipment.Bladeiconsize		= fTmp + "," + fTmp;

	objLandInterface.equipment.Guntexturename		= "interfaces\le\battle_interface\items\gun_empty.tga";
	objLandInterface.equipment.Guncolor				= argb(255,128,128,128);
	objLandInterface.equipment.Gunuv				= "0.0,0.0,1.0,1.0";
	fTmp = makeint(0.0 * fHtRatio);
	fTmp2 = makeint(-64.0 * fHtRatio);
	objLandInterface.equipment.Gunoffset			= fTmp + "," + fTmp2;
	fTmp = makeint(128.0 * 0.65 * fHtRatio);
    objLandInterface.equipment.Guniconsize			= fTmp + "," + fTmp;
	
	objLandInterface.equipment.Bullettexturename	= "interfaces\le\battle_interface\items\bullet_empty.tga";
	objLandInterface.equipment.Bulletcolor			= argb(255,128,128,128);
	objLandInterface.equipment.Bulletuv				= "0.0,0.0,1.0,1.0";
	fTmp = makeint(64.0 * fHtRatio);
	fTmp2 = makeint(0.0 * fHtRatio);
	objLandInterface.equipment.Bulletoffset			= fTmp + "," + fTmp2; 
	fTmp = makeint(128.0 * 0.65 * fHtRatio);
	objLandInterface.equipment.Bulleticonsize		= fTmp + "," + fTmp;

	objLandInterface.equipment.Potiontexturename	= "interfaces\le\battle_interface\items\potion_empty.tga";
	objLandInterface.equipment.Potioncolor			= argb(255,128,128,128);
	objLandInterface.equipment.Potionuv				= "0.0,0.0,1.0,1.0";
	fTmp = makeint(0.0 * fHtRatio);
	fTmp2 = makeint(64.0 * fHtRatio);
	objLandInterface.equipment.Potionoffset			= fTmp + "," + fTmp2; 
	fTmp = makeint(128.0 * 0.65 * fHtRatio);
    objLandInterface.equipment.Potioniconsize		= fTmp + "," + fTmp;
	
	objLandInterface.equipment.Lanterntexturename	= "interfaces\le\battle_interface\items\add\lantern.tga";
	objLandInterface.equipment.Lanterncolor			= argb(255,128,128,128);
	objLandInterface.equipment.Lanternuv				= "0.0,0.0,1.0,1.0";
	fTmp = makeint(-140.0 * fHtRatio);
	fTmp2 = makeint(45.0 * fHtRatio);
	objLandInterface.equipment.Lanternoffset		= fTmp + "," + fTmp2; 
	fTmp = makeint(128.0 * 0.45 * fHtRatio);
    objLandInterface.equipment.Lanterniconsize		= fTmp + "," + fTmp;
	objLandInterface.equipment.LanternOn            = CheckAttribute(pchar, "HandLight");
	
	objLandInterface.equipment.Rushtexturename		= "interfaces\le\battle_interface\items\add\berserker_potion.tga.tx";
	objLandInterface.equipment.Rushcolor			= argb(255,128,128,128);
	objLandInterface.equipment.Rushuv				= "0.0,0.0,1.0,1.0";
	fTmp = makeint(-90.0 * fHtRatio);
	fTmp2 = makeint(100.0 * fHtRatio);
	objLandInterface.equipment.Rushoffset			= fTmp + "," + fTmp2; 
	fTmp = makeint(128.0 * 0.45 * fHtRatio);
    objLandInterface.equipment.Rushiconsize			= fTmp + "," + fTmp;
	objLandInterface.equipment.RushOn           	=  0;
	
	objLandInterface.textinfo.RushTimer.font		= "interface_normal";
	objLandInterface.textinfo.RushTimer.scale		= 1.3 * fHtRatio;
	objLandInterface.textinfo.RushTimer.color		= argb(255,255,255,255);
	objLandInterface.textinfo.RushTimer.pos.x		= sti(showWindow.left) + RecalculateHIcon(makeint(80 * fHtRatio));
	objLandInterface.textinfo.RushTimer.pos.y		= sti(showWindow.bottom)- RecalculateVIcon(makeint(108 * fHtRatio));
	objLandInterface.textinfo.RushTimer.text		= "";
	objLandInterface.textinfo.RushTimer.refreshable = true;
	
	objLandInterface.equipment.Antidotetexturename	= "interfaces\le\battle_interface\items\potion_empty.tga";
	objLandInterface.equipment.Antidotecolor		= argb(255,128,128,128);
	objLandInterface.equipment.Antidoteuv			= "0.0,0.0,1.0,1.0";
	fTmp = makeint(90.0 * fHtRatio);
	fTmp2 = makeint(100.0 * fHtRatio);
	objLandInterface.equipment.Antidoteoffset		= fTmp + "," + fTmp2; 
	fTmp = makeint(128.0 * 0.45 * fHtRatio);
    objLandInterface.equipment.Antidoteiconsize		= fTmp + "," + fTmp;
	objLandInterface.equipment.AntidoteOn           =  0;
	
	objLandInterface.equipment.PotionDesfontid		= "interface_normal";
	objLandInterface.equipment.PotionDesfontcolor	= argb(255,255,255,255);
	fTmp = makeint(0.0 * fHtRatio);
    fTmp2 = makeint(130.0 * fHtRatio);
	objLandInterface.equipment.PotionDesfontscale	= 1.5* fHtRatio;
	objLandInterface.equipment.PotionDesfontoffset  = fTmp + "," + fTmp2;
	objLandInterface.equipment.PotionDescribe		= "";
	
	objLandInterface.equipment.PotionQtyfontid		= "interface_normal";
	objLandInterface.equipment.PotionQtyfontcolor	= argb(255,255,255,255);
	fTmp = makeint(20.0 * fHtRatio);
    fTmp2 = makeint(70.0 * fHtRatio);
	objLandInterface.equipment.PotionQtyfontscale	= 1.5* fHtRatio;
	objLandInterface.equipment.PotionQtyfontoffset  = fTmp + "," + fTmp2;
	objLandInterface.equipment.PotionQty		    = "";
	
	objLandInterface.equipment.BulletQtyfontid		= "interface_normal";
	objLandInterface.equipment.BulletQtyfontcolor	= argb(255,255,255,255);
 	fTmp = makeint(80.0 * fHtRatio);
	fTmp2 = makeint(10.0 * fHtRatio);
	objLandInterface.equipment.BulletQtyfontscale	= 1.5* fHtRatio;
	objLandInterface.equipment.BulletQtyfontoffset  = fTmp + "," + fTmp2;
	objLandInterface.equipment.BulletQty		    = "";
	
	objLandInterface.equipment.gunreloadtexturename	= "interfaces\le\battle_interface\items\gun_charge.tga.tx";
	objLandInterface.equipment.gunreloadcolor 		= argb(180, 128, 128, 128);
	objLandInterface.equipment.gunreloadbackcolor	= argb(180, 128, 128, 128);
	objLandInterface.equipment.gunreloadUV			= "0.0,0.0,1.0,1.0";

	fTmp = makeint(0.0 * fHtRatio);
	fTmp2 = makeint(-64.0 * fHtRatio);
	objLandInterface.equipment.gunreloadoffset		= fTmp + "," + fTmp2;
	fTmp = makeint(128.0 * fHtRatio);
	fTmp2 = makeint(128.0 * fHtRatio);
	objLandInterface.equipment.gunreloadiconsize	= fTmp + "," + fTmp2;
	objLandInterface.equipment.gunprogress        	= 0.0;
	
	objLandInterface.equipment.potionstatustexturename	= "interfaces\le\battle_interface\items\health_charge.tga.tx";
	objLandInterface.equipment.potionstatuscolor 		= argb(180, 128, 128, 128);
	objLandInterface.equipment.potionstatusbackcolor	= argb(180, 128, 128, 128);
	objLandInterface.equipment.potionstatusUV			= "0.0,0.0,1.0,1.0";
	fTmp = makeint(0.0 * fHtRatio);
	fTmp2 = makeint(64.0 * fHtRatio);
	objLandInterface.equipment.potionstatusoffset	= fTmp + "," + fTmp2;
	fTmp = makeint(128.0 * fHtRatio);
	fTmp2 = makeint(128.0 * fHtRatio);
	objLandInterface.equipment.potionstatusiconsize	= fTmp + "," + fTmp2;
	objLandInterface.equipment.potionprogress       = 0.0;
	
	objLandInterface.equipment.Backmustexturename		= "interfaces\le\battle_interface\items\equipment_back1.tga";
	objLandInterface.equipment.Backmuscolor			= argb(255,128,128,128);
	objLandInterface.equipment.Backmusuv				= "0.0,0.0,1.0,1.0";
	fTmp = makeint(-100.0 * fHtRatio);
	fTmp2 = makeint(-64.0 * fHtRatio);
	objLandInterface.equipment.Backmusoffset			= fTmp + "," + fTmp2; 
	fTmp = makeint(70.0 * fHtRatio);
    objLandInterface.equipment.Backmusiconsize	        = fTmp + "," + fTmp;
	
	objLandInterface.equipment.Mustexturename		= "interfaces\le\battle_interface\items\gun_empty.tga";
	objLandInterface.equipment.Muscolor				= argb(255,128,128,128);
	objLandInterface.equipment.Musnuv				= "0.0,0.0,1.0,1.0";
	fTmp = makeint(-100.0 * fHtRatio);
	fTmp2 = makeint(-64.0 * fHtRatio);
	objLandInterface.equipment.Musoffset			= fTmp + "," + fTmp2;
	fTmp = makeint(70.0 * 0.65 * fHtRatio);
    objLandInterface.equipment.Musiconsize			= fTmp + "," + fTmp;

	objLandInterface.equipment.musreloadtexturename	= "interfaces\le\battle_interface\items\gun_charge.tga.tx";
	objLandInterface.equipment.musreloadcolor 		= argb(180, 128, 128, 128);
	objLandInterface.equipment.musreloadbackcolor	= argb(180, 128, 128, 128);
	objLandInterface.equipment.musreloadUV			= "0.0,0.0,1.0,1.0";
	fTmp = makeint(-100.0 * fHtRatio);
	fTmp2 = makeint(-64.0 * fHtRatio);
	objLandInterface.equipment.musreloadoffset		= fTmp + "," + fTmp2;
	fTmp = makeint(70.0 * fHtRatio);
	objLandInterface.equipment.musreloadiconsize	= fTmp + "," + fTmp;
	objLandInterface.equipment.musprogress        	= 0.0;
	objLandInterface.equipment.MusketOn           	=  0;
	
	// evganat - прицел - атрибуты
	/*
		Для элементов прицела используются следующие атрибуты:
		texture и uv - если изображение задано текстурой
		group и picture - если изображение не задано текстурой и задано картинкой в battle_interface.ini
		technique - позволяет задавать технику, по умолчанию "battle_tex_col_Rectangle"
		priority - позволяет задавать порядок наложения элементов, по умолчанию 10000
		color - цвет
		pos - целочисленная позиция прямоугольника в формате "left,top,right,bottom"
		
		Также используются функции:
		BI_CrosshairSetPos(элемент, 
							горизонтальное смещение, 
							вертикальное смещение,
							ширина, 
							высота)
		- позволяет задавать вместо координат прямоугольника для элемента его относительную позицию относительно точки отсчёта и размеры
		BI_CrosshairSetSteadyParams(элемент, 
									начальное горизонтальное смещение, 
									конечное горизонтальное смещение,
									начальное вертикальное смещение,
									конечное вертикальное смещение,
									начальная ширина, 
									конечная ширина, 
									начальная высота, 
									конечная высота)
		- позволяет задавать параметры для автоматического обновления позиции и размеров элемента в зависимости от времени прицеливания
	*/
	aref arElement;
	
	makearef(arElement, objLandInterface.crosshair.elements.center);
	arElement.group		= "CROSSHAIRS";
	arElement.picture	= "crosc11";
	BI_CrosshairSetPos(arElement, 0, 0, 20, 20);
	
	makearef(arElement, objLandInterface.crosshair.elements.left);
	arElement.group		= "CROSSHAIRS";
	arElement.picture	= "crosf11";
	BI_CrosshairSetSteadyParams(arElement, -40, -30, 0, 0, 40, 40, 40, 40);
	
	makearef(arElement, objLandInterface.crosshair.elements.right);
	arElement.group		= "CROSSHAIRS";
	arElement.picture	= "crosf12";
	BI_CrosshairSetSteadyParams(arElement, 40, 30, 0, 0, 40, 40, 40, 40);

/*
	objLandInterface.ManSign.iconoffset1 = "70,70";
	objLandInterface.ManSign.iconoffset2 = "70,180";
	objLandInterface.ManSign.iconoffset3 = "70,290";
	objLandInterface.ManSign.iconoffset4 = "70,400";
*/

	int nLoc = FindLoadedLocation();
	if(nLoc >= 0) {
		int nFile = LanguageOpenFile("LocLables.txt");
		if(nFile >= 0) {
			objLandInterface.textinfo.islandname.font = "interface_normal_bold";
			objLandInterface.textinfo.islandname.scale = 0.7 * fHtRatio;

			objLandInterface.textinfo.islandname.pos.x = sti(showWindow.right) - RecalculateHIcon(124 * fHtRatio );
			objLandInterface.textinfo.islandname.pos.y = RecalculateVIcon(24 * fHtRatio);
			if (CheckAttribute(&locations[nLoc],"islandId"))
			{
				if (locations[nLoc].islandId != "Mein")
				{
					objLandInterface.textinfo.islandname.text = XI_convertString("Island:") + LanguageConvertString(nFile, locations[nLoc].islandId);
				}
				else
				{
					objLandInterface.textinfo.islandname.text = LanguageConvertString(nFile, locations[nLoc].islandId);
				}
			}
			else
			{
				objLandInterface.textinfo.islandname.text = "";//XI_convertString("Open Sea");
			}
			//
			objLandInterface.textinfo.villagename.font = "interface_normal_bold";
			objLandInterface.textinfo.villagename.scale = 0.7 * fHtRatio; 

			objLandInterface.textinfo.villagename.pos.x = sti(showWindow.right) - RecalculateHIcon(124 * fHtRatio);
			objLandInterface.textinfo.villagename.pos.y = RecalculateVIcon(48 * fHtRatio);

			objLandInterface.textinfo.locationname.font = "interface_normal_bold";
			objLandInterface.textinfo.locationname.scale = 0.7 * fHtRatio;

			objLandInterface.textinfo.locationname.pos.x = sti(showWindow.right) - RecalculateHIcon(124 * fHtRatio);
			objLandInterface.textinfo.locationname.pos.y = RecalculateVIcon(72 * fHtRatio);
			
            if (!CheckAttribute(&locations[nLoc],"fastreload"))
			{
			    objLandInterface.textinfo.villagename.text = "";
				if(bGlobalTutor)
				{
					objLandInterface.textinfo.villagename.text = LanguageConvertString(nFile, "Ulysse");
				}
			}
			else
			{
				objLandInterface.textinfo.villagename.text = XI_ConvertString("Colony:") + LanguageConvertString(nFile, locations[nLoc].fastreload + " Town");
			}
			objLandInterface.textinfo.locationname.text = LanguageConvertString(nFile, locations[nLoc].id.label);
			LanguageCloseFile( nFile );
		}
	}
	objLandInterface.textinfo.datatext.font = "interface_normal_bold";
	objLandInterface.textinfo.datatext.scale = 0.7 * fHtRatio;

	objLandInterface.textinfo.datatext.pos.x = sti(showWindow.right) - RecalculateHIcon(124 * fHtRatio);
	objLandInterface.textinfo.datatext.pos.y = RecalculateVIcon(96 * fHtRatio);
	objLandInterface.textinfo.datatext.text = GetQuestBookData();
	// RefreshLandTime();
	//objLandInterface.textinfo.datatext.text = XI_convertString("Date:") + GetQuestBookData(); //GetDataDay()+" "+XI_ConvertString("target_month_" + GetDataMonth())+" "+GetDataYear();
	objLandInterface.textinfo.datatext.refreshable = true;
	
	// belamour legendary edition подсказки управления для новичков
	int coff, boff, doff;
	for(numLine = 1; numLine < 11; numline++)
	{
		sAttr = "Con"+numLine;
		sAttrDes = "Con"+numLine+"desc";
		sAttrB = "Con"+numLine+"Back";
		
		coff = -204 + (numLine-1)*45;
		boff = -205 + (numLine-1)*45;
		doff = -199 + (numLine-1)*45;
		
		objLandInterface.textinfo.(sAttrB).font = "Info_fader_rs";
		objLandInterface.textinfo.(sAttrB).scale = 0.6 * fHtRatio;
		objLandInterface.textinfo.(sAttrB).color = argb(155,255,255,255);
		objLandInterface.textinfo.(sAttrB).pos.x = sti(showWindow.right) + RecalculateHIcon(makeint(210 * fHtRatio));
		objLandInterface.textinfo.(sAttrB).pos.y = sti(showWindow.bottom)/4*3 + RecalculateVIcon(makeint(boff * fHtRatio));
		objLandInterface.textinfo.(sAttrB).align = "right";
		objLandInterface.textinfo.(sAttrB).text = "";
		objLandInterface.textinfo.(sAttrB).refreshable = true;
		
		objLandInterface.textinfo.(sAttr).font = "KEYBOARD_SYMBOL";
		objLandInterface.textinfo.(sAttr).scale = 0.9 * fHtRatio;
		objLandInterface.textinfo.(sAttr).color = argb(255,255,255,255);
		objLandInterface.textinfo.(sAttr).pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(85 * fHtRatio));
		objLandInterface.textinfo.(sAttr).pos.y = sti(showWindow.bottom)/4*3 + RecalculateVIcon(makeint(coff * fHtRatio));
		objLandInterface.textinfo.(sAttr).align = "left";
		objLandInterface.textinfo.(sAttr).text = "";
		objLandInterface.textinfo.(sAttr).refreshable = true;
		
		objLandInterface.textinfo.(sAttrDes).font = "interface_normal";
		objLandInterface.textinfo.(sAttrDes).scale = 1.3 * fHtRatio;
		objLandInterface.textinfo.(sAttrDes).color = argb(255,255,255,255);
		objLandInterface.textinfo.(sAttrDes).pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(95 * fHtRatio));
		objLandInterface.textinfo.(sAttrDes).pos.y = sti(showWindow.bottom)/4*3 + RecalculateVIcon(makeint(doff * fHtRatio));
		objLandInterface.textinfo.(sAttrDes).align = "right";
		objLandInterface.textinfo.(sAttrDes).text = "";
		objLandInterface.textinfo.(sAttrDes).refreshable = true;
	}
	//блок экипировки
	objLandInterface.textinfo.GunCtrl.font = "KEYBOARD_SYMBOL";
	objLandInterface.textinfo.GunCtrl.scale = 0.6 * fHtRatio;
	objLandInterface.textinfo.GunCtrl.color = argb(255,255,255,255);
	objLandInterface.textinfo.GunCtrl.pos.x = sti(showWindow.left) + RecalculateHIcon(makeint(180 * fHtRatio));
	objLandInterface.textinfo.GunCtrl.pos.y = sti(showWindow.bottom)- RecalculateVIcon(makeint(212 * fHtRatio));
	objLandInterface.textinfo.GunCtrl.text = "";
	objLandInterface.textinfo.GunCtrl.refreshable = true;
	
	objLandInterface.textinfo.BladeCtrl.font = "KEYBOARD_SYMBOL";
	objLandInterface.textinfo.BladeCtrl.scale = 0.6 * fHtRatio;
	objLandInterface.textinfo.BladeCtrl.color = argb(255,255,255,255);
	objLandInterface.textinfo.BladeCtrl.pos.x = sti(showWindow.left) + RecalculateHIcon(makeint(168 * fHtRatio));
	objLandInterface.textinfo.BladeCtrl.pos.y = sti(showWindow.bottom)- RecalculateVIcon(makeint(192 * fHtRatio));
	objLandInterface.textinfo.BladeCtrl.align = "right";
	objLandInterface.textinfo.BladeCtrl.text = "";
	objLandInterface.textinfo.BladeCtrl.refreshable = true;
	
	objLandInterface.textinfo.PotionCtrl.font = "KEYBOARD_SYMBOL";
	objLandInterface.textinfo.PotionCtrl.scale = 0.6 * fHtRatio;
	objLandInterface.textinfo.PotionCtrl.color = argb(255,255,255,255);
	objLandInterface.textinfo.PotionCtrl.pos.x = sti(showWindow.left) + RecalculateHIcon(makeint(180 * fHtRatio));
	objLandInterface.textinfo.PotionCtrl.pos.y = sti(showWindow.bottom)- RecalculateVIcon(makeint(168 * fHtRatio));
	objLandInterface.textinfo.PotionCtrl.text = "";
	objLandInterface.textinfo.PotionCtrl.refreshable = true;
	
	objLandInterface.textinfo.BulletCtrl.font = "KEYBOARD_SYMBOL";
	objLandInterface.textinfo.BulletCtrl.scale = 0.6 * fHtRatio;
	objLandInterface.textinfo.BulletCtrl.color = argb(255,255,255,255);
	objLandInterface.textinfo.BulletCtrl.pos.x = sti(showWindow.left) + RecalculateHIcon(makeint(192 * fHtRatio));
	objLandInterface.textinfo.BulletCtrl.pos.y = sti(showWindow.bottom)- RecalculateVIcon(makeint(192 * fHtRatio));
	objLandInterface.textinfo.BulletCtrl.align = "left";
	objLandInterface.textinfo.BulletCtrl.text = "";
	objLandInterface.textinfo.BulletCtrl.refreshable = true;
	
	objLandInterface.textinfo.RushCtrl.font = "KEYBOARD_SYMBOL";
	objLandInterface.textinfo.RushCtrl.scale = 0.6 * fHtRatio;
	objLandInterface.textinfo.RushCtrl.color = argb(255,255,255,255);
	objLandInterface.textinfo.RushCtrl.pos.x = sti(showWindow.left) + RecalculateHIcon(makeint(72 * fHtRatio));
	objLandInterface.textinfo.RushCtrl.pos.y = sti(showWindow.bottom)- RecalculateVIcon(makeint(110 * fHtRatio));
	objLandInterface.textinfo.RushCtrl.text = "";
	objLandInterface.textinfo.RushCtrl.refreshable = true;
	
	objLandInterface.textinfo.AntidoteCtrl.font = "KEYBOARD_SYMBOL";
	objLandInterface.textinfo.AntidoteCtrl.scale = 0.6 * fHtRatio;
	objLandInterface.textinfo.AntidoteCtrl.color = argb(255,255,255,255);
	objLandInterface.textinfo.AntidoteCtrl.pos.x = sti(showWindow.left) + RecalculateHIcon(makeint(252 * fHtRatio));
	objLandInterface.textinfo.AntidoteCtrl.pos.y = sti(showWindow.bottom)- RecalculateVIcon(makeint(110 * fHtRatio));
	objLandInterface.textinfo.AntidoteCtrl.text = "";
	objLandInterface.textinfo.AntidoteCtrl.refreshable = true;
	
	objLandInterface.textinfo.MusCtrl.font = "KEYBOARD_SYMBOL";
	objLandInterface.textinfo.MusCtrl.scale = 0.6 * fHtRatio;
	objLandInterface.textinfo.MusCtrl.color = argb(255,255,255,255);
	objLandInterface.textinfo.MusCtrl.pos.x = sti(showWindow.left) + RecalculateHIcon(makeint(50 * fHtRatio));
	objLandInterface.textinfo.MusCtrl.pos.y = sti(showWindow.bottom)- RecalculateVIcon(makeint(256 * fHtRatio));
	objLandInterface.textinfo.MusCtrl.text = "";
	objLandInterface.textinfo.MusCtrl.refreshable = true;
	
    //GetWeaponQty();
	if(iShowTime < 7) iShowTime = 15;
	
    // Это у вас нет, у меня все есть ;) - boal
	objLandInterface.CommandList.CommandMaxIconQuantity = 10;
	objLandInterface.CommandList.CommandIconSpace = 1;
	objLandInterface.CommandList.CommandIconLeft = 150 * fHtRatio;//157;
	objLandInterface.CommandList.CommandIconWidth = RecalculateHIcon(55 * fHtRatio);
	objLandInterface.CommandList.CommandIconHeight = RecalculateVIcon(55 * fHtRatio);

	objLandInterface.CommandList.CommandNoteFont = "interface_normal_bold";
	objLandInterface.CommandList.CommandNoteColor = argb(255,255,255,255);
	objLandInterface.CommandList.CommandNoteScale = 0.65 * fHtRatio;
	objLandInterface.CommandList.CommandNoteOffset = RecalculateHIcon(0) + "," + RecalculateVIcon(20 * fHtRatio);

	objLandInterface.CommandList.UDArrow_Texture = "interfaces\le\battle_interface\arrowly.tga";
	objLandInterface.CommandList.UDArrow_UV_Up = "0.0,1.0,1.0,0.0";
	objLandInterface.CommandList.UDArrow_UV_Down = "0.0,0.0,1.0,1.0";
	objLandInterface.CommandList.UDArrow_Size = RecalculateHIcon(32 * fHtRatio) + "," + RecalculateVIcon(32 * fHtRatio);
	objLandInterface.CommandList.UDArrow_Offset_Up = RecalculateHIcon(-41 * fHtRatio) + "," + RecalculateVIcon(-30 * fHtRatio);
	objLandInterface.CommandList.UDArrow_Offset_Down = RecalculateHIcon(-41 * fHtRatio) + "," + RecalculateVIcon(46 * fHtRatio);
	
	// дебилы всё равно играть не будут, а нормальным лишнее не нужно boal
	/*objLandInterface.CommandList.ActiveIcon_Texture = "interfaces\le\battle_interface\enter_list.tga";
	objLandInterface.CommandList.ActiveIcon_Offset = RecalculateHIcon(-49) + ",0";
	objLandInterface.CommandList.ActiveIcon_Size = RecalculateHIcon(48) + "," + RecalculateVIcon(48);
	objLandInterface.CommandList.ActiveIcon_UV1 = "0.5,0.0,1.0,1.0";
	objLandInterface.CommandList.ActiveIcon_UV2 = "0.0,0.0,0.5,1.0";
	objLandInterface.CommandList.ActiveIcon_Note = XI_ConvertString("MenuNote");*/
	
	SendMessage(&objLandInterface,"l",MSG_BATTLE_LAND_START);
}

bool bFastEnable() // belamour возможен ли переход
{
	if(LAi_group_IsActivePlayerAlarm()) return false;
	if(!LAi_IsCharacterControl(pchar)) return false;
	if(bDisableFastReload)	return false;
	if(!IsEnableFastTravel()) return false;
	if(chrDisableReloadToLocation) return false;
	if (!CheckAttribute(loadedLocation, "fastreload")) return false;
	if(CheckNationLicence(HOLLAND)) return true;
	if(CheckAttribute(pchar, "questTemp.Guardoftruth") && CheckCharacterItem(pchar, "VerifyPaper") && loadedLocation.fastreload == "santiago" && GetNationRelation2MainCharacter(StealthNat) != RELATION_ENEMY) return true;
	if(CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && CheckCharacterItem(pchar, "VerifyPaper") && loadedLocation.fastreload == "portspein" && GetNationRelation2MainCharacter(StealthNat) != RELATION_ENEMY) return true;
	if(!bBettaTestMode && !CheckAttribute(pchar, "Cheats.LocTeleport"))
	{
		string sNation = Colonies[FindColony(loadedLocation.fastreload)].nation;
		if (sNation != "none")
		{
			int i = sti(sNation);
			bool bOk = (GetNationRelation2MainCharacter(i) == RELATION_ENEMY) || GetRelation2BaseNation(i) == RELATION_ENEMY;
			if(bOk && (i != PIRATE)) return false;
			else return true;
		}
	}
	return true;
}

bool FindUserIcon(string id,ref uiref)
{
	aref arroot,ar; makearef(arroot,objLandInterface.UserIcons);
	int iMax = GetAttributesNum(arroot); //fix
	for(int i=0; i<iMax; i++)
	{
		ar = GetAttributeN(arroot,i);
		if(ar.name != id) continue;
		uiref = ar;
		return true;
	}
	return false;
}

void BLI_SetMessageParameters()
{
	objLandInterface.MessageIcons.IconWidth = RecalculateHIcon(64);
	objLandInterface.MessageIcons.IconHeight = RecalculateVIcon(24);
	objLandInterface.MessageIcons.IconDist = RecalculateVIcon(2);
	objLandInterface.MessageIcons.IconBottom = sti(showWindow.bottom)-RecalculateHIcon(80+40);
	objLandInterface.MessageIcons.IconMaxQuantity = 4;
	objLandInterface.MessageIcons.BlendTime = 3.0;
	objLandInterface.MessageIcons.FallSpeed = 22.0;
	objLandInterface.MessageIcons.argbHighBlind = argb(255,128,128,128);
	objLandInterface.MessageIcons.argbLowBlind = argb(255,68,68,68);
	objLandInterface.MessageIcons.BlindUpTime = 0.5;
	objLandInterface.MessageIcons.BlindDownTime = 1.0;
	objLandInterface.MessageIcons.texture = "interfaces\le\battle_interface\MessageIcons.tga.tx";
	objLandInterface.MessageIcons.TexHSize = 2;
	objLandInterface.MessageIcons.TexVSize = 2;
}

void BLI_UpdateObjectData()
{
	if(LAi_group_IsActivePlayerAlarm() || !StealthEnable)
	{
		objLandInterface.data.stealth = false;
		objLandInterface.ManSign.alarmtexturename = "interfaces\le\battle_interface\alarmback.tga.tx";
	}
	else
	{
		objLandInterface.data.stealth = true;
		objLandInterface.ManSign.alarmtexturename = "interfaces\le\battle_interface\alarmstealth.tga.tx";
		if(CheckAttribute(&InterfaceStates,"ShowStealthAlarm") && sti(InterfaceStates.ShowStealthAlarm) == false)
		{
			objLandInterface.data.stealth = false;
			// objLandInterface.ManSign.alarmtexturename = "interfaces\le\battle_interface\alarmstealth.tga.tx";
		}
	}
	bool bIsRiskAlarm = LAi_group_IsActivePlayerAlarm();
	if(sti(objLandInterface.data.Alarm)!=bIsRiskAlarm) BLI_RefreshCommandMenu();
	objLandInterface.data.Alarm = bIsRiskAlarm;
	//objLandInterface.data.alarmhighcolor	= argb(255,255,225,0);
	//objLandInterface.data.alarmlowcolor	= argb(64,255,225,0); 
	// belamour
	if(CanStartDialog()) 
	{
		Log_SetActiveAction("Talk");
	}
	else 
	{ 
		if(g_ActiveActionName == "Talk") Log_SetActiveAction("Nothing");
	}

	if(Dead_FindCloseBody() >= 0)
	{
		Log_SetActiveAction("DeadBox");
	}
	else 
	{ 
		if(g_ActiveActionName == "DeadBox") Log_SetActiveAction("Nothing");
	}

	if(CharacterIsDead(GetMainCharacter())) Log_SetActiveAction("Nothing");
	
	aref ar,arItm;
	int i,cn;
	ref curCh;
	string attrName;
	for(i=0; i<4; i++)
	{
		attrName = "id"+i;
		cn = GetOfficersIndex(pchar,i);
		if(cn==-1 || !IsEntity(&Characters[cn]))
		{
			DeleteAttribute(&objLandInterface,"data.icons."+attrName);
			continue;
		}
		// belamour legendary edition бессмертные офицеры -->
		if(CheckAttribute(&Characters[cn], "OfficerImmortal") && Characters[cn].OfficerImmortal == "Injury")
		{
			DeleteAttribute(&objLandInterface,"data.icons."+attrName);
			continue;
		}
		// <-- legendary edition
		curCh = GetCharacter(cn);
		makearef(ar,objLandInterface.data.icons.(attrName));
		SetCharacterIconData(cn,ar);
		//ar.picture = curCh.FaceId;
		//ar.health = LAi_GetCharacterRelHP(curCh);
		//ar.charge = LAi_GetCharacterRelCharge(curCh);
		//ar.shootMax = LAi_GetCharacterChargeQuant(curCh);
		//ar.shootCur = LAi_GetCharacterChargeCur(curCh);
		//ar.poison = LAi_IsPoison(curCh);
	}
	if(FindLoadedLocation() != -1)
	{
		ControlsLandDesc();
		EquipmentDesc();
	}
	
	PostEvent("evntBLI_Update",BLI_UPDATE_PERIOD);
}

void BLI_SetPossibleCommands()
{
	int chrMode = SendMessage(pchar,"ls",MSG_CHARACTER_EX_MSG,"CheckFightMode");

	bool bTmpBool;
	bool bUseCommand = false;
	bool bOk, bOk1;
	int i;
	aref rootcom,curcom;
	makearef(rootcom,objLandInterface.Commands);
	int iMax = GetAttributesNum(rootcom); //fix
	for(i=0; i<iMax; i++)
	{
		curcom = GetAttributeN(rootcom,i);
		curcom.enable = false;
	}

	if(chrMode==0)
	{
		bTmpBool = true;
		if(LAi_group_IsActivePlayerAlarm()) bTmpBool = false;
		if(!LAi_IsCharacterControl(pchar)) bTmpBool = false;
		if(bDisableFastReload)	bTmpBool = false;
		if(!IsEnableFastTravel()) bTmpBool = false;
		// boal запрет всех переходов
		if (chrDisableReloadToLocation) bTmpBool = false;
		if (!CheckAttribute(loadedLocation,"fastreload")) bTmpBool = false;  // в каюте некуда переходить
		if (bTmpBool && !CheckAttribute(pchar, "Cheats.LocTeleport")) // все еще можно переходить, проверяем город враг
		{
		    string sNation = Colonies[FindColony(loadedLocation.fastreload)].nation;
			if (sNation != "none")
			{
				i = sti(sNation);
				bTmpBool = (GetNationRelation2MainCharacter(i) == RELATION_ENEMY) || GetRelation2BaseNation(i) == RELATION_ENEMY;
				if (bTmpBool && (i != PIRATE))// && !CheckAttribute(pchar, "CheckStateOk"))
				{
					bTmpBool = false;
				}
				else
				{
		    		bTmpBool = true;
				}
			}
			if(CheckNationLicence(HOLLAND)) bTmpBool = true;
			if(CheckAttribute(pchar, "questTemp.Guardoftruth") && CheckCharacterItem(pchar, "VerifyPaper") && loadedLocation.fastreload == "santiago" && GetNationRelation2MainCharacter(i) != RELATION_ENEMY) bTmpBool = true;
			if(CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && CheckCharacterItem(pchar, "VerifyPaper") && loadedLocation.fastreload == "portspein" && GetNationRelation2MainCharacter(i) != RELATION_ENEMY) bTmpBool = true;
		}
		objLandInterface.Commands.FastReload.enable	= bTmpBool;
		///// boal -->
		i = -1;
		if (CheckAttribute(pchar,"dialogready")) i=sti(pchar.dialogready);
		if (i>=0)
		{
            if(LAi_Character_CanDialog(PChar, &Characters[i]))
            {
                objLandInterface.Commands.DialogStart.enable = true;
			}
			if (isOfficerInShip(&Characters[i], true) || CheckAttribute(&Characters[i], "IsCompanionClone"))
			{
				objLandInterface.Commands.ItemsChange.enable = true;
			}
			// грабеж
			/*
			else
			{
				if( CheckAttribute(&Characters[i],"InterfaceFlags.ItemsChange") &&
					Characters[i].InterfaceFlags.ItemsChange != "0" )
				{
					objLandInterface.Commands.ItemsChange.enable = true;
				}
			}   */
		}
		// boal 22.01.2004 -->
		else
		// обмен с офицером всегда и везде (в абордаже нет диалога!)
		{
		    i = LAi_FindNearestVisCharacter(pchar, 1);
		    if( i>0 && IsOfficer(GetCharacter(i)))
			{
				objLandInterface.Commands.ItemsChange.enable = true;
			}
		}
		//////// <--
		bUseCommand = true;
	}
	if (objLandInterface.Commands.DialogStart.enable == false && LAi_IsCharacterControl(pchar) && !LAi_IsFightMode(pchar)
	&& !LAi_grp_alarmactive && !chrDisableReloadToLocation && !CheckAttribute(pchar, "GenQuest.BlockTalkSelf") && loadedLocation.type != "underwater") // belamour fix только не под водой	// Sinistra новый атрибут запрета диалога сам с собой
	{
    	objLandInterface.Commands.TalkSelf.enable = true;//boal разговор с каюте сам с собой
    	bUseCommand = true;
    }

	bool bSeaBattle = (bDisableMapEnter) && (bSeaActive) && (!CheckAttribute(pchar, "GenQuest.MapClosedNoBattle"));
	if(!LAi_IsFightMode(pchar) && !bSeaBattle && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard" , 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar, "GenQuest.CannotWait")) // отдых/проматывание времени
	{
    	objLandInterface.Commands.Rest.enable = true;//отдых/проматывание времени
    	bUseCommand = true;
    }

	if(GetCharacterPerkUsing(pchar, "Rush") && CheckCharacterItem(pchar, "berserker_potion"))
	{
		objLandInterface.Commands.ActivateRush.enable = true;
		bUseCommand = true;
	}
	bOk = LAi_IsCharacterControl(pchar) && !LAi_IsFightMode(pchar) && !LAi_grp_alarmactive && !chrDisableReloadToLocation;
	if(Pchar.Location == Pchar.location.from_sea && CheckOfficersPerk(pchar, "SelfRepair") && CheckSelfRepairConditions() && bOk)
	{
		objLandInterface.Commands.SelfRepair.enable = true;
		bUseCommand = true;
	}		

	if( CanBeUseItem(pchar) )
	{
		objLandInterface.Commands.ItemsUse.enable = true;
		bUseCommand = true;
	}

	if(CheckAttribute(pchar,"boxname"))
	{
		objLandInterface.Commands.UseBox.enable	= true;
		bUseCommand = true;
	}

	if( CheckAttribute(pchar,"activeItem") && pchar.activeItem!="" )
	{
		bUseCommand = true;
		if( CheckAttribute(pchar,"activeItem.pick") && pchar.activeItem.pick=="1" )
		{
			//objLandInterface.Commands.TakeItem.enable = true; // Jason: баг с двойным взятием через быструю команду+интерфейс
		}
		else
		{
			objLandInterface.Commands.PlaceItem.enable = true;
		}
	}

	if( chrWaitReloadLocator != "" )
	{
		bUseCommand = true;
		objLandInterface.Commands.OutDoor.enable = true;
	}
    // boal dead can be searched 14.12.2003 -->
    i = Dead_FindCloseBody();
    if (i != -1)
    {
        objLandInterface.Commands.DeadBox.enable	= true;
		bUseCommand = true;
    }
	if(g_ActiveActionName == "PlayEvent")
	{
		bUseCommand = true;
		objLandInterface.Commands.PlayEvent.enable = true;
	}
	// boal dead can be searched 14.12.2003 <--
	// boal 20.03.2004 -->
    if (isShipInside(pchar.location) && !chrDisableReloadToLocation)
    {
		bUseCommand = true;
		objLandInterface.Commands.Exit_Deck.enable = true;
    }
	
	if(CheckAttribute(pchar,"alchemy.known") && bLandInterfaceStart && !LAi_IsFightMode(pchar))
	{
		bUseCommand = true;
		objLandInterface.Commands.Alchemy.enable = true;	
	}
	else
	{
		if(HasAlchemyRecipe()) 
		{
			bUseCommand = true;
			objLandInterface.Commands.Alchemy.enable = true;
		}
	}
	
	bOk  = bSeaActive && !bAbordageStarted;
	bOk1 = bLandInterfaceStart && !LAi_IsFightMode(pchar);			
	if(bOk || bOk1) 
	{ 
		if(CheckCharacterItem(PChar, "MapsAtlas") && pchar.MapsAtlasCount > 0) 
		{
			bUseCommand = true;
			objLandInterface.Commands.MapAtlas.enable = true;	
		}
	}	
	
	// ugeen  --> отслеживаем ситуацию взрыва или эпидемии на захваченном корабле --> покидание каюты минуя интерфейс грабежа
	if(CheckAttribute(loadedLocation, "CabinType") && !chrDisableReloadToLocation) 
	{
		if(CheckShipSituation_GenQuest())
		{
			bUseCommand = true;
			objLandInterface.Commands.Exit_Deck.enable = true;
		}	
	}
	// <-- ugeen
    // boal 20.03.2004 <--
    // boal 20.03.2004 <--
    if (pchar.location == "Ship_deck")
    {
		if (CheckQuestAttribute("Munity", "Deads"))
		{
			bUseCommand = true;
			objLandInterface.Commands.Exit_Deck.enable = true;
		}
    }
	//objLandInterface.Commands.OutDoor.enable		= true;
	
	if(!bUseCommand)
	{
		SendMessage(&objLandInterface,"llllll",BI_IN_SET_COMMAND_MODE,0,-1,-1,-1,-1);
	}
}

/*void BLI_evntRefreshCommandMenu()
{
	DelEventHandler("frame","BLI_evntRefreshCommandMenu");
	BLI_RefreshCommandMenu();
}
void BLI_RefreshCommandMenu()
{
	SendMessage(&objLandInterface,"lllll",BI_IN_SET_COMMAND_MODE,-1,-1,-1,-1,-1);
}*/

void procFindDialogChar()
{
	int dlgChar = -1;
	if(!LAi_IsBoardingProcess())
		dlgChar = SendMessage(pchar,"ls",MSG_CHARACTER_EX_MSG,"FindDialogCharacter");

	int oldDlgChar = -1;
	if(CheckAttribute(pchar,"dialogready")) oldDlgChar = sti(pchar.dialogready);

	if(dlgChar!=oldDlgChar)
	{
		pchar.dialogready = dlgChar;
		//BLI_RefreshCommandMenu();
		LI_CareUpdateCommandList();
	}

	PostEvent("evntFindDialogChar",1000);
}

void BLI_ChrEnterToLocation()
{
	aref loc = GetEventData();	
	aref chr = GetEventData();
	string group = GetEventData();
	string locator = GetEventData();
	aref locList,locCur;
	int i,n;

	if(sti(chr.index) != nMainCharacterIndex) return;

	if(group=="reload")
	{
		makearef(locList,loc.reload);
		n = GetAttributesNum(locList);
		for(i=0;i<n;i++)
		{
			locCur = GetAttributeN(locList,i);
			if(locCur.name == locator) break;
		}
		if(i<n)
		{
			i = FindLocation(locCur.go);
			if(i>=0)
			{
				if(CheckAttribute(&locations[i],"id.label"))
				{
					Log_SetStringToLog( LanguageConvertString(g_LocLngFileID,locations[i].id.label) );
				}
			}
		}
		//SetEventHandler("frame","BLI_evntRefreshCommandMenu",1);
		LI_CareUpdateCommandList();
	}
}

void BLI_ChrExitFromLocation()
{
	//SetEventHandler("frame","BLI_evntRefreshCommandMenu",1);
	LI_CareUpdateCommandList();
}

void LI_Reload()
{
	Event("Control Activation","s","ChrAction");
}

bool SetUsedPotionIcons()
{
	if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "blade_SP_3") return false;
	
	aref arItm, ar, uiref;
	int i, itmIdx, nq;

	bool bUsed = false;

	makearef(uiref,objLandInterface.UserIcons);
	nq = GetAttributesNum(uiref);
	for(i=0; i<nq; i++)
	{
		ar = GetAttributeN(uiref,i);
		if( CheckAttribute(ar,"potion") ) {
			DeleteAttribute(uiref,GetAttributeName(ar));
			nq--; i--;
		}
	}

	string UI_name;
	int UI_idx = 0;

	itmIdx = FindPotionFromChr(pchar, &arItm, 0);
	while(itmIdx>=0)
	{
		if(EnablePotionUsing(PChar, arItm) || EnableAntidoteUsing(PChar, arItm))
		{
			UI_idx++;
			UI_name = "potion"+UI_idx;
			objLandInterface.UserIcons.(UI_name).enable = true;
			objLandInterface.UserIcons.(UI_name).pic = GetPotionPicture(arItm);
            objLandInterface.UserIcons.(UI_name).selpic = GetPotionPicture(arItm) - 16;
			objLandInterface.UserIcons.(UI_name).tex = GetPotionTexture(arItm);
			objLandInterface.UserIcons.(UI_name).name = UI_name;
			objLandInterface.UserIcons.(UI_name).potion = arItm.id;
			bUsed = true;
		}
		itmIdx = FindPotionFromChr(pchar, &arItm, itmIdx+1);
	}

	return bUsed;
}

bool SetReloadIcons()
{
	int i, nq, locidx;
	aref ar, curloc, locref, locList, uiref;

	bool bUse = false;

	makearef(uiref,objLandInterface.UserIcons);
	nq = GetAttributesNum(uiref);
	for(i=0; i<nq; i++)
	{
		ar = GetAttributeN(uiref,i);
		if( CheckAttribute(ar,"location") ) {
			DeleteAttribute(uiref,GetAttributeName(ar));
			nq--; 
			i--;
		}
	}
	int idLngFile = LanguageOpenFile("commands_name.txt");
	int idxloc = FindLoadedLocation();
	string str1,str2,fastLocName;
	string outGroupName = "";
	if(idxloc>=0 && CheckAttribute(&Locations[idxloc],"fastreload"))
	{
		outGroupName = Locations[idxloc].fastreload;
		
		if( CheckAttribute(&objFastReloadTable,"table."+outGroupName) )
		{
			makearef(locList,objFastReloadTable.table.(outGroupName));
			nq = GetAttributesNum(locList);
			// to port icon
			if( GetCharacterShipType(pchar)!=SHIP_NOTUSED )
			{
				if( CheckFastJump(Locations[idxloc].id, pchar.location.from_sea) )
				{
					objLandInterface.UserIcons.port.enable = true;
					objLandInterface.UserIcons.port.pic = 26;
					objLandInterface.UserIcons.port.selpic = 10;
					objLandInterface.UserIcons.port.tex = 1;
					objLandInterface.UserIcons.port.name = "reloadtoport";
					objLandInterface.UserIcons.port.location = pchar.location.from_sea;
					objLandInterface.UserIcons.port.locator = "reload1";
					objLandInterface.UserIcons.port.note = GetNodeForIcon(1, 10);
					bUse = true;
				}
			}
			for(i=0; i<nq; i++)
			{
				curloc = GetAttributeN(locList,i);
				if(!CheckFastJump(Locations[idxloc].id, curloc.location) ) 
				{
					continue;
				}
				fastLocName = "fr_"+(i+1);
				// belamour 
				if(loadedlocation.islandId == "LostShipsCity")
				{
					objLandInterface.UserIcons.port.locator = "reload1_back";
					if(CheckAttribute(&locations[idxloc],"lsc_inside"))
					{
						if(locations[idxloc].lsc_inside == "narval" && CheckAttribute(pchar, "GenQuest.NarvalConflict")) continue;
						if(locations[idxloc].lsc_inside == "shark" && CheckAttribute(pchar, "GenQuest.SharkConflict")) continue;
						if(locations[idxloc].lsc_inside == "rivados" && CheckAttribute(pchar, "GenQuest.RivadosConflict")) continue;
					}									
					objLandInterface.UserIcons.(fastLocName).enable = true;
					objLandInterface.UserIcons.(fastLocName).pic = sti(curloc.pic)+16;
					objLandInterface.UserIcons.(fastLocName).selpic = curloc.pic;
					objLandInterface.UserIcons.(fastLocName).tex = 1+sti(curloc.tex);
					objLandInterface.UserIcons.(fastLocName).name = "reload"+i;
					objLandInterface.UserIcons.(fastLocName).location = curloc.location;
					objLandInterface.UserIcons.(fastLocName).note = GetNodeForIcon(11+sti(curloc.tex), sti(curloc.pic));
					// локаторы для перехода
					if(i == 4)
					{
						objLandInterface.UserIcons.(fastLocName).locator = "reload2"; // вход в резиденцию нарвалов
						objLandInterface.UserIcons.(fastLocName).note = LanguageConvertString(idLngFile, "go_EsmeraldaStoreBig_Donald");
					}
					if(i == 8) objLandInterface.UserIcons.(fastLocName).locator = "reload4"; // вход к Мэри
					if(i == 2) objLandInterface.UserIcons.(fastLocName).note = LanguageConvertString(idLngFile, "go_SanAugustineResidence");
					if(i == 10)
					{
						objLandInterface.UserIcons.(fastLocName).locator = "reload3";
						objLandInterface.UserIcons.(fastLocName).note = LanguageConvertString(idLngFile, "go_SanGabrielMechanic");
					}						
				}					
				else
				{					
					objLandInterface.UserIcons.(fastLocName).enable = true;
					objLandInterface.UserIcons.(fastLocName).pic = sti(curloc.pic)+16;
					objLandInterface.UserIcons.(fastLocName).selpic = curloc.pic;
					objLandInterface.UserIcons.(fastLocName).tex = 1+sti(curloc.tex);
					objLandInterface.UserIcons.(fastLocName).name = "reload"+i;
					objLandInterface.UserIcons.(fastLocName).location = curloc.location;
					objLandInterface.UserIcons.(fastLocName).note = GetNodeForIcon(1+sti(curloc.tex), sti(curloc.pic));
				}
				bUse = true;
			}
		}
	}

	return bUse;
}

void SetOfficerTexture(int officerIdx)
{
	aref ar; makearef(ar,objLandInterface.Parameters);
	string attrName = "iconTexture"+officerIdx;

	int cn = GetOfficersIndex(pchar,officerIdx);
	if(cn<0) {
		DeleteAttribute(ar,attrName);
		ar.(attrName) = "";
	} else {
		ar.(attrName) = "interfaces\le\portraits\64\face_"+Characters[cn].FaceID+".tga";
	}
}

void BLI_UpdateOfficers()
{
	SetOfficerTexture(0);
	SetOfficerTexture(1);
	SetOfficerTexture(2);
	SetOfficerTexture(3);

	SendMessage(&objLandInterface, "lls", MSG_BATTLE_LAND_SET_ICONTEX, 0, objLandInterface.Parameters.iconTexture0);
	SendMessage(&objLandInterface, "lls", MSG_BATTLE_LAND_SET_ICONTEX, 1, objLandInterface.Parameters.iconTexture1);
	SendMessage(&objLandInterface, "lls", MSG_BATTLE_LAND_SET_ICONTEX, 2, objLandInterface.Parameters.iconTexture2);
	SendMessage(&objLandInterface, "lls", MSG_BATTLE_LAND_SET_ICONTEX, 3, objLandInterface.Parameters.iconTexture3);
	//Log_TestInfo("BLI_UpdateOfficers");
	BLI_UpdateObjectData();
	LI_CareUpdateCommandList();
	SendMessage(&objLandInterface,"ls",MSG_BATTLE_LAND_MAKE_COMMAND,"cancel");  // фикс иконок офов (рефреш) boal
}

int GetPotionPicture(aref arItm)
{
	if( CheckAttribute(arItm,"potion.pic") ) {
		return sti(arItm.potion.pic);
	}
	trace("Item "+arItm.id+ " hav`t POTION.PIC attribute");
	return 0;
}

int GetPotionTexture(aref arItm)
{
	if( !CheckAttribute(arItm,"potion.tex") ) {
		trace("Item "+arItm.id+ " hav`t POTION.TEX attribute");
		return 0;
	}
	return sti(arItm.potion.tex);
}

// можем ли юзать хоть что то
bool CanBeUseItem(ref chref)
{
	for(int i=0; i<ITEMS_QUANTITY; i++)
	{
		if( CheckAttribute(&Items[i],"potion") && CheckAttribute(chref,"items."+Items[i].id) ) {
			if( EnablePotionUsing(chref,&Items[i]) ) {return true;}
		}
	}
	return false;
}

object objIconsNote;
string GetNodeForIcon(int nTex, int nPic)
{
	string attrName = nTex+"x"+nPic;
	if( CheckAttribute(&objIconsNote,attrName) ) return objIconsNote.(attrName);
	return "";
}

void LI_ProcessControlPress()
{
	string ControlName = GetEventData();

	switch(ControlName)
	{
		case "hk_Cure": // TO_DO не работет - у меня в др месте
			if( LAi_GetCharacterRelHP(pchar) < 1.0 )
			{
				float dhlt = LAi_GetCharacterMaxHP(pchar) - LAi_GetCharacterHP(pchar);
				string btl = FindHealthForCharacter(pchar, dhlt);
				DoCharacterUsedItem(pchar, btl);
			}
		break;
		
		case "LICommandsActivate": 
			PlaySound("interface\ok.wav"); // boal даёшь звуки!
		break;
	}
}

void BLI_RefreshCommandMenu()
{
	SendMessage( &objLandInterface,"l",BI_MSG_CARE_COMMANDLIST_UPDATE );
}
void LI_CareUpdateCommandList()
{
	SendMessage( &objLandInterface,"l",BI_MSG_CARE_COMMANDLIST_UPDATE );
}

void SetCharacterIconData(int chrindex, aref arData)
{
	ref chref = GetCharacter(chrindex);
	arData.chrindex = chrindex;
	arData.health = LAi_GetCharacterRelHP(chref);
	arData.energy = LAi_GetCharacterRelEnergy(chref);
	
	string sType = GUN_ITEM_TYPE;
	if(MusketPriority(chref)) sType = MUSKET_ITEM_TYPE;
	
	arData.shootMax = LAi_GetCharacterChargeQuant(chref, sType);
	arData.shootCur = LAi_GetCharacterChargeCur(chref, sType);
	arData.rankrate = makefloat(makefloat(GetCharacterRankRateCur(chref))/makefloat(GetCharacterRankRate(chref)));
	arData.currank = sti(chref.rank);
	if(CheckAttribute(chref,"chr_ai.energyMax"))
		arData.energyvalue = ""+sti(chref.chr_ai.energy)+"/"+sti(chref.chr_ai.energyMax)+"";
	if(CheckAttribute(chref,"chr_ai.hp_max"))
		arData.healthvalue = ""+sti(chref.chr_ai.hp)+"/"+sti(chref.chr_ai.hp_max)+"";
	if(CheckAttribute(chref,"chr_ai.energyMax"))
		arData.HideStates = sti(chref.chr_ai.energy) == sti(chref.chr_ai.energyMax) && sti(chref.chr_ai.hp) == sti(chref.chr_ai.hp_max) && !LAi_IsFightMode(pchar) && !iMoreInfo;
	if( CheckAttribute(chref,"FaceId") ) {
		//arData.picture = chref.FaceId;
		arData.texture = "interfaces\le\battle_interface\portraits\face_"+chref.FaceID+".tga";
		if( CheckAttribute(chref,"FaceUV") ) {
			arData.uv = chref.FaceUV;
		} else {
			arData.uv = "0.0,0.0,1.0,1.0";
		}
	} else {
		arData.texture = "interfaces\le\battle_interface\two.tga";
		if( chrindex == 1 ) {
			arData.uv = "0.5,0.0,1.0,1.0";
		} else {
			arData.uv = "0.0,0.0,0.5,1.0";
		}
	}
	SendMessage(&objLandInterface,"ll",MSG_BATTLE_LAND_SHOW_EQUIPMENT, bShowEquipment());
	if(chref.id == Characters[nMainCharacterIndex].id)
	{
		if(sType == GUN_ITEM_TYPE)
		{
			objLandInterface.equipment.gunprogress = LAi_GetGunChargeProgress(chref);
			objLandInterface.equipment.musprogress = LAi_GetMusketChargeProgress(chref);
		}
		else
		{
			objLandInterface.equipment.gunprogress = LAi_GetMusketChargeProgress(chref);
			//objLandInterface.equipment.musprogress = LAi_GetGunChargeProgress(chref);
			objLandInterface.equipment.musprogress = 0.0;
		}
		if(GetCharacterEquipByGroup(chref, BLADE_ITEM_TYPE) == "blade_SP_3")
			objLandInterface.equipment.potionprogress = Bring2Range(0.0, 1.0, 0.0, 0.5, (LAi_GetCharacterRelHP(chref)) / 2.0);
		else
			objLandInterface.equipment.potionprogress = LAi_GetPotionProgress(chref);
	}
	//arData.charge = LAi_GetCharacterRelCharge(chref);
	//arData.poison = LAi_IsPoison(chref);
}

void ControlsLandDesc()
{
	if(bMainMenu) return;
	if(iControlsTips > 0 && !IsSteamDeck())
	{
		int colorbase	= argb(255,255,255,255);
		int colorused	= argb(255,255,255,192);
		int colorcd 	= argb(155,255,64,64);
		int colorempty	= argb(155,255,255,255);
		float fHtRatio = stf(Render.screen_y) / iHudScale;
		bool bcompleted = false;
		string stmp = "";
		string cname = "";
		string sTimerDur = "";
		string FTC[10];
		
		for(numline = 1; numline < 11; numline++)
		{
			sAttrB = "Con"+numLine+"Back";
			sAttr = "Con"+numLine;
			sAttrDes = "Con"+numLine+"desc";
			
			objLandInterface.textinfo.(sAttrB).text = "" ;
			objLandInterface.textinfo.(sAttr).text = "";
			objLandInterface.textinfo.(sAttrDes).text = "" ;
			
			objLandInterface.textinfo.(sAttr).color = colorbase;
			objLandInterface.textinfo.(sAttrDes).color = colorbase;
		}
		
		if(iShowTime > 0) iShowTime--;
		numline = 10;
		for(i = 9; i >= 0; i--)
		{
			objLandInterface.textinfo.(sAttr).color = colorbase;
			objLandInterface.textinfo.(sAttrDes).color = colorbase;
			sTimerDur = "";
			if(bLandInterfaceStart)
			{
				if(LAi_IsFightMode(pchar))
				{
					if(SendMessage(pchar, "ls", MSG_CHARACTER_EX_MSG, "IsAimingMode"))
					{
						FTC[0] = "ChrAimingShot";
						FTC[1] = "ChrAiming";
					}
					else 
					{
						FTC[0] = "ChrAltAttackBase";
						FTC[1] = "ChrAttackBase";
						FTC[2] = "ChrAttackBreakBase";
						FTC[3] = "ChrAttackChoseBase";
						if(LAi_CharacterCanFrie(pchar)) FTC[4] = "ChrAiming";
						FTC[5] = "ChrBlock";
					}
				}
				else
				{
					if(iControlsTips > 5) // iControlsTips > 1 включит показ
					{
						if(bFastEnable() && iShowTime > 0 && iControlsTips > 2)
						{
							FTC[0] = "_port";
							FTC[1] = "_store";
							FTC[2] = "_Shipyard";
							FTC[3] = "_tavern";
							FTC[4] = "_townhall";
							FTC[5] = "_bank";
							FTC[6] = "_church";
							FTC[7] = "_brothel";
							FTC[8] = "_portOffice";
							FTC[9] = "_prison";
							
							if(loadedlocation.islandId == "LostShipsCity")
							{
								/* string LSCloc[11];
								LSCloc[0] = "CeresSmithy";
								LSCloc[1] = "EsmeraldaStoreBig";
								LSCloc[2] = "SanGabrielMechanic";
								LSCloc[3] = "FleuronTavern";
								LSCloc[4] = "SanAugustineResidence";
								LSCloc[5] = "CarolineBank";
								LSCloc[6] = "GloriaChurch";
								LSCloc[7] = "CeresSmithy";
								LSCloc[8] = "ProtectorFisher";
								LSCloc[9] = "EsmeraldaStoreBig";
								LSCloc[10] = "TartarusPrison";   */
								
							} 
							else
							{
								if(CheckFastJump(loadedLocation.id, loadedLocation.fastreload+FTC[i]))
								{
									objLandInterface.textinfo.(sAttr).text = GetKeyCodeImg("Fast"+FTC[i]);
									objLandInterface.textinfo.(sAttrDes).text = GetConvertStr("LI_Fast"+FTC[i],"ControlsNames.txt");
									objLandInterface.textinfo.(sAttrB).text = "1" ;
									numLine --;
									
									sAttr = "Con"+numLine;
									sAttrDes = "Con"+numLine+"desc";
									sAttrB = "Con"+numLine+"Back";
								}
								if(CheckFastJump(loadedLocation.id, pchar.location.from_sea))
								{
									objLandInterface.textinfo.(sAttr).text = GetKeyCodeImg("Fast"+FTC[i]);
									objLandInterface.textinfo.(sAttrDes).text = GetConvertStr("LI_Fast"+FTC[i],"ControlsNames.txt");
									objLandInterface.textinfo.(sAttrB).text = "1" ;
								}
							}
							bcompleted = true;
						}
						else
						{
							if(IsCharacterPerkOn(pchar,"Gunman") && pchar.model != "protocusto" && Mqty > 0) FTC[6] = "HK_Musket";
							if(FLqty > 0) FTC[5] = "HK_FencingL";
							if(FSqty > 0) FTC[6] = "HK_FencingS";
							if(FHqty > 0) FTC[7] = "HK_FencingH";
						}
					}
				}
			}
			else
			{
				
			}
			
			if(!bcompleted && FTC[i] != "")
			{
				objLandInterface.textinfo.(sAttr).text = GetKeyCodeImg(FTC[i]);
				objLandInterface.textinfo.(sAttrDes).text = GetConvertStr(FTC[i],"ControlsNames.txt") + sTimerDur;
				objLandInterface.textinfo.(sAttrB).text = "1" ;
				numLine --;
				
				sAttr = "Con"+numLine;
				sAttrDes = "Con"+numLine+"desc";
				sAttrB = "Con"+numLine+"Back";
			}
		}
	}
}

// belamour посчитать оружие в инвентаре
void GetWeaponQty()
{
	aref arItems;
	string sItem;
	ref rItem;
	int iItemsNum; 
	int mq = 0;
	int lq = 0;
	int sq = 0;
	int hq = 0;
	
	makearef(arItems, pchar.items);
	iItemsNum = GetAttributesNum(arItems);
	for(i=0; i<iItemsNum; i++)
	{
		sItem = GetAttributeName(GetAttributeN(arItems, i));
		rItem = ItemsFromID(sItem);
		if(!CheckAttribute(rItem, "groupID")) continue;
		if(sItem != "")
		{
			if(rItem.groupID == MUSKET_ITEM_TYPE) mq++;
			if(rItem.groupID == BLADE_ITEM_TYPE && rItem.FencingType == "FencingL") lq++;
			if(rItem.groupID == BLADE_ITEM_TYPE && rItem.FencingType == "FencingS") sq++;
			if(rItem.groupID == BLADE_ITEM_TYPE && rItem.FencingType == "FencingH") hq++;
		}
		
	}
	if(CheckAttribute(pchar,"chr_ai.FencingType"))
	{
		switch(pchar.chr_ai.FencingType)
		{
			case "FencingL":  lq -= 1; break;
			case "FencingS":  sq -= 1; break;
			case "FencingH":  hq -= 1; break;
		}
	}
	if(CheckAttribute(pchar,"chr_ai.sGun") && HasSubStr(pchar.chr_ai.sGun, "mushket")) mq -= 1;
	FLqty = lq;
	FSqty = sq;
	FHqty = hq;
	Mqty = mq;
}

void EquipmentDesc()
{
	if(bMainMenu) return;
	bool bInFight = LAi_IsFightMode(pchar);
	string cname = "";
	string GunType = GUN_ITEM_TYPE;
	if(MusketPriority(pchar)) GunType = MUSKET_ITEM_TYPE;
	objLandInterface.equipment.MusketOn = IsMusketer(pchar);
	if(GunType == GUN_ITEM_TYPE)
	{
		objLandInterface.equipment.Bladetexturename		    = "interfaces\le\battle_interface\items\"+GetItemVis("Blade")+".tga";
		objLandInterface.equipment.Guntexturename		    = "interfaces\le\battle_interface\items\"+GetItemVis("Gun")+".tga";
		objLandInterface.equipment.Mustexturename		    = "interfaces\le\battle_interface\items\"+GetItemVis("Musket")+".tga";
	}
	else
	{
		objLandInterface.equipment.Bladetexturename		    = "interfaces\le\battle_interface\items\"+GetItemVis("Gun")+".tga";
		objLandInterface.equipment.Guntexturename		    = "interfaces\le\battle_interface\items\"+GetItemVis("Gun")+".tga";
		objLandInterface.equipment.Mustexturename		    = "interfaces\le\battle_interface\items\"+GetItemVis("Blade")+".tga";
	}
	objLandInterface.equipment.Potiontexturename		= "interfaces\le\battle_interface\items\"+GetItemVis("Potion")+".tga";
	objLandInterface.equipment.Bullettexturename		= "interfaces\le\battle_interface\items\"+GetItemVis("Bullet")+".tga";

	objLandInterface.equipment.PotionDescribe = GetItemVis("PotionDesc");

	if(CheckAttribute(pchar,"chr_ai."+GunType+".bullet"))
		objLandInterface.equipment.BulletQty = GetCharacterFreeItem(pchar, pchar.chr_ai.(GunType).bullet);
	else objLandInterface.equipment.BulletQty = "";
	
	objLandInterface.equipment.LanternOn = CheckAttribute(pchar, "HandLight");
	
	objLandInterface.equipment.RushOn = CheckCharacterItem(pchar, "berserker_potion") || AbilityTimeDuration("active", "Rush") > 0;
	if(SendMessage(pchar,"ls",MSG_CHARACTER_EX_MSG,"CheckFightMode") == 0) objLandInterface.equipment.RushOn = false;
	if(objLandInterface.equipment.RushOn > 0)
	{
		if(AbilityTimeDuration("active", "Rush") > 0)
		{
			objLandInterface.textinfo.RushTimer.text = AbilityTimeDuration("active", "Rush");
			objLandInterface.textinfo.RushTimer.color = argb(255,255,255,192);
			objLandInterface.textinfo.RushCtrl.text = "";
		}
		else
		{
			if(AbilityTimeDuration("delay", "Rush") > 0)
			{
				objLandInterface.textinfo.RushTimer.text = AbilityTimeDuration("delay", "Rush");
				objLandInterface.textinfo.RushTimer.color = argb(255,255,64,64);
				objLandInterface.textinfo.RushCtrl.text = "";
			}
			else
			{
				if(iControlsTips > 0)
				{
					objLandInterface.textinfo.RushCtrl.text = GetKeyCodeImg("BOAL_ActivateRush");
				}
				else objLandInterface.equipment.RushOn = false;
				objLandInterface.textinfo.RushTimer.text = "";
			}
		}
	}
	else
	{
		objLandInterface.textinfo.RushCtrl.text = "";
		objLandInterface.textinfo.RushTimer.text = "";
	}
	
	objLandInterface.equipment.AntidoteOn = CheckAttribute(pchar,"chr_ai.poison") && FindCharacterAntidote(pchar, &cname);
	if(objLandInterface.equipment.AntidoteOn > 0)
	{
		objLandInterface.equipment.Antidotetexturename	= "interfaces\le\battle_interface\items\add\"+GetItemVis("Antidote")+".tga";
		if(iControlsTips > 0)
		{
			objLandInterface.textinfo.AntidoteCtrl.text = GetKeyCodeImg("UseAntidote");
		}
		else objLandInterface.textinfo.AntidoteCtrl.text = "";
	}
	else objLandInterface.textinfo.AntidoteCtrl.text = "";
		
	if(iControlsTips > 0 && !IsSteamDeck())
	{
		if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "blade_SP_3")
		{
			objLandInterface.textinfo.PotionCtrl.text = "";
		}
		else
		{
			int ptQty = FindPotionTypesQty(pchar);
			objLandInterface.textinfo.PotionCtrl.text = "";
			if(ptQty - CheckAttribute(pchar,"GenQuest.Potion_choice") > 0)
			{
				if(!iMoreInfo && bInFight) objLandInterface.textinfo.PotionCtrl.text = GetKeyCodeImg("PotionChanger");
				if(iMoreInfo) objLandInterface.textinfo.PotionCtrl.text = GetKeyCodeImg("PotionChanger");
			}
			if(LAi_GetCharacterHP(pchar)<LAi_GetCharacterMaxHP(pchar) && ptQty > 0)
			{
				if(!iMoreInfo && bInFight) objLandInterface.textinfo.PotionCtrl.text = GetKeyCodeImg("BOAL_UsePotion");
				if(iMoreInfo) objLandInterface.textinfo.PotionCtrl.text = GetKeyCodeImg("BOAL_UsePotion");
			}
		}
		
		objLandInterface.textinfo.GunCtrl.text = "";
		if(bInFight && GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE) != "" && LAi_CharacterCanFrie(pchar))
		{
			objLandInterface.textinfo.GunCtrl.text = GetKeyCodeImg("ChrFire");
		}
		if(bInFight && GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE) != "" && LAi_CharacterCanFrie(pchar))
		{
			objLandInterface.textinfo.GunCtrl.text = GetKeyCodeImg("ChrFire");
		}
		objLandInterface.textinfo.BladeCtrl.text = "";
		if(LAi_LocationCanFight() && GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) != "" )
		{
			if(!iMoreInfo && bInFight) objLandInterface.textinfo.BladeCtrl.text = GetKeyCodeImg("ChrFightMode");
			if(iMoreInfo) objLandInterface.textinfo.BladeCtrl.text = GetKeyCodeImg("ChrFightMode");
		}
		objLandInterface.textinfo.MusCtrl.text = "";
		if(IsMusketer(pchar) && GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE) != "")
		{
			if(!iMoreInfo && bInFight) objLandInterface.textinfo.MusCtrl.text = GetKeyCodeImg("ChrSwitchFightMode");
			if(iMoreInfo) objLandInterface.textinfo.MusCtrl.text = GetKeyCodeImg("ChrSwitchFightMode");
		}
		
		objLandInterface.textinfo.BulletCtrl.text = "";
		if(CheckAttribute(pchar, "chr_ai."+GunType+".bullet") && CheckAttribute(pchar, "chr_ai."+GunType+".bulletNum") && sti(pchar.chr_ai.(GunType).bulletNum) > 1)
		{
			if(!iMoreInfo && bInFight) objLandInterface.textinfo.BulletCtrl.text = GetKeyCodeImg("BulletChanger");
			if(iMoreInfo) objLandInterface.textinfo.BulletCtrl.text = GetKeyCodeImg("BulletChanger");
		}
	}
	
}

string GetItemVis(string type)
{
	ref Itm;
	string stmp;
	bool bInFight = LAi_IsFightMode(pchar);
	string GunType = GUN_ITEM_TYPE;
	string GunTypeRev = MUSKET_ITEM_TYPE;
	if(MusketPriority(pchar))
	{
		GunType = MUSKET_ITEM_TYPE;
		GunTypeRev = GUN_ITEM_TYPE;
	}
	
	switch(type)
	{
		case "Blade":
			if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) != "")
			{
				Itm = &Items[FindItem(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE))];
				return Itm.picTexture+"_"+Itm.picIndex;
			}
		break;
		
		case "Gun":
			if(GetCharacterEquipByGroup(pchar, GunType) != "")
			{
				Itm = &Items[FindItem(GetCharacterEquipByGroup(pchar, GunType))]
				return Itm.picTexture+"_"+Itm.picIndex;
			}
		break;
		
		case "Musket":
			if(GetCharacterEquipByGroup(pchar, GunTypeRev) != "")
			{
				Itm = &Items[FindItem(GetCharacterEquipByGroup(pchar, GunTypeRev))]
				return Itm.picTexture+"_"+Itm.picIndex;
			}
		break;
		
		case "Potion":
			if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "blade_SP_3")
			{
				return "Yorick";
			}
			else if(CheckAttribute(pchar,"GenQuest.Potion_choice"))
			{
				Itm = &Items[FindItem(pchar.GenQuest.Potion_choice)];
				return Itm.picTexture+"_"+Itm.picIndex;
			}
			else
			{
				if(FindPotionTypesQty(pchar) > 0)
				return "Auto_"+LanguageGetLanguage();
			}
		break;
		
		case "Antidote":
			if(FindCharacterAntidote(pchar, &stmp))
			{
				Itm = &Items[FindItem(stmp)];
				return Itm.picTexture+"_"+Itm.picIndex;
			}	
		break;
		
		case "Bullet":
			if(CheckAttribute(pchar,"chr_ai."+GunType+".bullet"))
			{
				Itm = &Items[FindItem(pchar.chr_ai.(GunType).bullet)];
				return Itm.picTexture+"_"+Itm.picIndex;
			}	
		break;
		
		case "PotionDesc":
			if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "blade_SP_3")
			{
				objLandInterface.equipment.PotionQty = "";
			}
			else if(CheckAttribute(pchar,"GenQuest.Potion_choice"))
			{
				Itm = &Items[FindItem(pchar.GenQuest.Potion_choice)];
				objLandInterface.equipment.PotionQty = GetCharacterFreeItem(pchar, Itm.id);
				if(CheckAttribute(Itm,"potion.drunk") && GetCharacterEquipByGroup(pchar, HAT_ITEM_TYPE) == "hat8")
				{
					return GetConvertStr(Itm.name, "ItemsDescribe.txt")+ " + "+sti(Itm.potion.health) * 15 / 10);
				}
				return GetConvertStr(Itm.name, "ItemsDescribe.txt")+ " + "+sti(Itm.potion.health));
			}	
			else 
			{
				objLandInterface.equipment.PotionQty = "";
			}
			return "";
		break;
	}
	
	return type+"_empty";
}

bool bShowEquipment()
{
	if(TW_IsActive() && CheckAttribute(&TEV, "Tutor.BackControlsTips"))
		return false;
	if(!LAi_IsFightMode(pchar) && !iMoreInfo) return false;
	return true;
}

int UpdateStealthIndicator(int luck, int vigilance)
{
	if(LAi_group_IsActivePlayerAlarm()) return 0;
	int per = 100*luck/vigilance;
	if(per >= 0 && per < 25)
	{
		objLandInterface.ManSign.alarmhighcolor = argb(255,255,0,0);
		objLandInterface.ManSign.alarmlowcolor = argb(64,255,0,0);
		return per;
	}
	if(per >= 25 && per < 75)
	{
		objLandInterface.ManSign.alarmhighcolor = argb(255,255,255,0);
		objLandInterface.ManSign.alarmlowcolor = argb(64,255,255,0);
		return per;
	}
	if(per >74)
	{
		objLandInterface.ManSign.alarmhighcolor = argb(0,0,0,0);
		objLandInterface.ManSign.alarmlowcolor = argb(0,0,0,0);
		return per;
	}
	
	return 0;
}

// evganat - прицел -->
// расчёт позиции по заданным оффсетам, ширине, высоте и точке отсчёта
void BI_CrosshairSetPos(aref element, int x, int y, int w, int h)
{
	int ox = sti(showWindow.right)/2;
	int oy = sti(showWindow.bottom)/2);
	float fHtRatio = stf(Render.screen_y) / iHudScale;
	int left = makeint(ox + (x - w/2) * fHtRatio);
	int right = makeint(ox + (x + w/2) * fHtRatio);
	int top = makeint(oy + (y - h/2) * fHtRatio);
	int bottom = makeint(oy + (y + h/2) * fHtRatio);
	element.pos = left + "," + top + "," + right + "," + bottom;
}

// выставление параметров, зависящих от времени прицеливания
void BI_CrosshairSetSteadyParams(aref element, int x1, int x2, int y1, int y2, int w1, int w2, int h1, int h2)
{
	float fHtRatio = stf(Render.screen_y) / iHudScale;
	element.steady.offsetX.start	= makeint(x1 * fHtRatio);
	element.steady.offsetX.end		= makeint(x2 * fHtRatio);
	element.steady.offsetY.start	= makeint(y1 * fHtRatio);
	element.steady.offsetY.end		= makeint(y2 * fHtRatio);
	element.steady.width.start		= makeint(w1 * fHtRatio);
	element.steady.width.end		= makeint(w2 * fHtRatio);
	element.steady.height.start		= makeint(h1 * fHtRatio);
	element.steady.height.end		= makeint(h2 * fHtRatio);
	BI_CrosshairSetPos(element, x1, y1, w1, h1);
}

// обновление элемента от времени прицеливания
void BI_CrosshairUpdatePos(aref element, float fSteady)
{
	if(!CheckAttribute(element, "steady"))
		return;
	
	int start, end, width, height, offsetX, offsetY;
	aref attr;
	
	makearef(attr, element.steady.width);
	start = sti(attr.start);
	end = sti(attr.end);
	width = start + (end - start)*fSteady;
	
	makearef(attr, element.steady.height);
	start = sti(attr.start);
	end = sti(attr.end);
	height = start + (end - start)*fSteady;
	
	makearef(attr, element.steady.offsetX);
	start = sti(attr.start);
	end = sti(attr.end);
	offsetX = start + (end - start)*fSteady;
	
	makearef(attr, element.steady.offsetY);
	start = sti(attr.start);
	end = sti(attr.end);
	offsetY = start + (end - start)*fSteady;
	
	BI_CrosshairSetPos(element, offsetX, offsetY, width, height);
}

// evganat - прицел - выставление элементов в зависимости от вида оружия
void BI_CrosshairSet()
{
	if(CharUseMusket(pchar))
	{
		objLandInterface.crosshair.elements.left.picture = "crosf21";
		objLandInterface.crosshair.elements.right.picture = "crosf22";
	}
	else
	{
		objLandInterface.crosshair.elements.left.picture = "crosf11";
		objLandInterface.crosshair.elements.right.picture = "crosf12";
	}
}

// evganat - прицел - обновление
void BI_CrosshairRefresh(float fAimingTime, bool isFindedTarget, aref target)
{
	float fMaxTime = MAX_AIMING_TIME;
	float fSteady = Bring2Range(0.0, 1.0, 0.0, fMaxTime, fAimingTime);

	aref arElement;
	makearef(arElement, objLandInterface.crosshair.elements.center);

	// если есть цель, красим прицел
	if(isFindedTarget)
	{
		if(LAi_group_IsEnemy(pchar, target))
			arElement.color = argb(255, 128, 40, 40);	// враги
		else
		{
			if(pchar.chr_ai.group == target.chr_ai.group || target.chr_ai.group == "TMP_FRIEND")
				arElement.color = argb(255, 0, 128, 0);	// друзья
			else
				arElement.color = argb(255, 128, 100, 40);	// прочие
		}
	}
	else
		objLandInterface.crosshair.elements.center.color = argb(255, 128, 128, 128);
	
	// если цель мертва, меняем прицел на крестик
	if(CheckAttribute(pchar, "chr_ai.kill_timer"))
	{
		arElement.picture = "crosc12";
		arElement.color = argb(255, 128, 40, 40);
		objLandInterface.crosshair.elements.left.color = argb(55, 128, 128, 128);
		objLandInterface.crosshair.elements.right.color = argb(55, 128, 128, 128);
	}
	else
	{
		arElement.picture = "crosc11";
		objLandInterface.crosshair.elements.left.color = argb(255, 128, 128, 128);
		objLandInterface.crosshair.elements.right.color = argb(255, 128, 128, 128);
	}
	
	// обновляем позицию элементов
	makearef(arElement, objLandInterface.crosshair.elements.left);
	BI_CrosshairUpdatePos(arElement, fSteady);
	makearef(arElement, objLandInterface.crosshair.elements.right);
	BI_CrosshairUpdatePos(arElement, fSteady);
}

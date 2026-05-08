void _Birthday_SetUpDeck(string temp = "")
{
	SetMusic("music_LadyBeth");
	aref wormhole = GetAref(&TEV, "wormhole", true);

	ref alonso = GetCharacter(NPC_GenerateCharacter("Alonso_LP", "Alonso", "man", "man", 1, FRANCE, 0, true, "pirate"));
	alonso.name = GetCharacterName("Alonso");
	alonso.lastname = "";
	SetTempDialog(alonso, "exact$story_frames\Randomevents\Birthday\dialogs\Alonso.c", "initial");
	PlaceCharacter(alonso, "goto", "random_must_be");
	AddLandQuestMark(alonso, "questmarkmain");
	LAi_SetCitizenType(alonso);
	CharacterTurnToLoc(alonso, "reload", "reload1");
	_Birthday_SetOfficers(&wormhole);
	LAi_LocationFightDisable(loadedLocation, true);
}

void _Birthday_SetOfficers(ref wormhole)
{
	object fellows;
	GetAllFellowsWithJob(&fellows, pchar);
	int fellowsQty = GetAttributesNum(&fellows);
	for (int i = 0; i < fellowsQty; i++)
	{
		ref chr = GetCharacterSafe(int(GetAttributeValue(GetAttributeN(&fellows, i))));
		PlaceCharacter(chr, "goto", pchar.location);
		LAi_SetCitizenType(chr);
		string dialogId = "commonOfficer";
		switch (chr.id)
		{
			case "Mary": dialogId = chr.id; break;
			case "Helena": dialogId = chr.id; break;
			case "Duran": dialogId = chr.id; break;
			case "Folke": dialogId = chr.id; break;
			case "Tichingitu": dialogId = chr.id; break;
			case "Irons": dialogId = chr.id; break;
			case "Longway": dialogId = chr.id; break;
			case "Knippel": dialogId = chr.id; break;
			case "Tonzag": dialogId = chr.id; break;
		}
		SetTempDialog(chr, "exact$story_frames\Randomevents\Birthday\dialogs\" + dialogId + ".c", "initial");
		SetAttribute(wormhole, "tempDialogs." + chr.id, chr.id);
	}
}

void _Birthday_GoToCabin(string temp = "")
{
	Set_My_Cabin();
	CloneLocation(Get_My_Cabin(), "Clone_location");
	ref cloneCabin = &locations[FindLocation("Clone_location")];
	DeleteAttribute(cloneCabin, "boarding");
	SetEventHandler(EVENT_LOCATION_LOAD, "_Birthday_InCabin", 0);
	SetCurrentTime(23, 00);
	SetLaunchFrameFormParam(DLG_Convert("Frame", "StoryFrames\RandomEvents\Birthday.txt"), "Reload_To_Location", 0, 4);
	SetLaunchFrameReloadLocationParam("Clone_location", "rld", "aloc1", "");
	LaunchFrameForm();
}

void _Birthday_InCabin()
{
	DelEventHandler(EVENT_LOCATION_LOAD, "_Birthday_InCabin");
	DisableAllExits(true);
	LAi_AlcoholSetDrunk(pchar, 51, 5600);

	pchar.GenQuest.CamShuttle = 1;
	SetCamShuttle(loadedLocation);
	LAi_SetActorType(pchar);
	DoQuestFunctionDelay("_Birthday_InCabin2", 0.5);
}

void _Birthday_InCabin2(string temp = "")
{
	SetMusic("music_LadyBeth");
	SetPitch(0.75);
	SetTempDialog(pchar, "exact$story_frames\Randomevents\Birthday\dialogs\self.c", "initial");
	LAi_ActorSelfDialog(pchar, "pchar_back_to_player");
}

void _Birthday_End(string temp = "")
{
	DisableAllExits(false);
	aref chrIds = GetAref(&TEV, "wormhole.tempDialogs");
	int idsQty = GetAttributesNum(chrIds);
	for (int i = 0; i < idsQty; i++)
	{
		ref chr = CharacterFromIDSafe(GetAttributeValue(GetAttributeN(chrIds, i)));
		RestoreTempDialog(chr);
		LAi_SetOfficerType(chr);
	}

	RestoreTempDialog(pchar);
	SetOfficersLocationToNone();
	SetOfficersInCampusToNone();
	int idxLoadLoc = FindLoadedLocation();
	if (idxLoadLoc != -1) UnloadLocation(&Locations[idxLoadLoc]);
	WdmReloadStart(false);
	RecalculateJumpTable();
	RefreshWeather();
	RefreshLandTime();
	SetPitch(1.0);
	PauseAllSounds();
	ResetSound();
	DeleteAttribute(&TEV, "wormhole");
	Achievment_Set("ach_CL_211");
}

// Временно подменить диалог персонажа, использовать только в рамках worm-hole ивента, в конце нужно вернуть нормальный диалог
void SetTempDialog(ref chr, string fileName, string nodeName)
{
	aref tempDialog = GetAref(chr, "Dialog.tempDialog", true);

	tempDialog.fileName = GetAttributeOrDefault(chr, "Dialog.FileName", "");
	tempDialog.currentnode = GetAttributeOrDefault(chr, "Dialog.currentnode", "");
	chr.Dialog.FileName = fileName;
	chr.Dialog.currentnode = nodeName;
}

// Убрать все временные диалоги у персонажей в рамках worm-hole ивента
void RestoreTempDialogAll(ref wormhole)
{
	aref chrIds = GetAref(wormhole, "tempDialogs");
	int idsQty = GetAttributesNum(chrIds);
	for (int i = 0; i < idsQty; i++)
	{
		ref chr = CharacterFromIDSafe(GetAttributeValue(GetAttributeN(chrIds, i)));
		RestoreTempDialog(chr);
	}
}

void RestoreTempDialog(ref chr)
{
	if (!CheckAttribute(chr, "Dialog.tempDialog")) return;

	chr.Dialog.Filename = chr.Dialog.tempDialog.Filename;
	chr.Dialog.currentnode = chr.Dialog.tempDialog.currentnode;
	DeleteAttribute(chr, "Dialog.tempDialog");
}

void DiegoDeLanda_Leaving()
{
	if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
	{
		DiegoDeLanda_Leaving_SantaMisericordia();
		DeleteAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia");
	}
	if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
	{
		DiegoDeLanda_Leaving_LadyBeth();
		DeleteAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth");
	}
	if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
	{
		DiegoDeLanda_Leaving_Memento();
		DeleteAttribute(pchar, "questTemp.DiegoDeLanda_Memento");
	}
}

void DiegoDeLanda_Leaving_2(string qName)
{
	sld = CharacterFromID("DiegoDeLanda");
	sld.dialog.filename = "Quest\ShipsPack\DiegoDeLanda_dialog.c";
	sld.dialog.currentnode = "DiegoDeLanda_Leaving_1";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

//--> Святое Милосердие
void DiegoDeLanda_Leaving_SantaMisericordia()
{
	locCameraSleep(true);
	sld = CharacterFromID("DiegoDeLanda");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "reload", "reload2", "", -1);
	DoQuestFunctionDelay("DiegoDeLanda_Leaving_2", 2.4);
}
//<-- Святое Милосердие
		
//--> Леди Бет
void DiegoDeLanda_Leaving_LadyBeth()
{
	LAi_SetStayType(pchar);
	sld = CharacterFromID("DiegoDeLanda");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "goto", "goto9", "", -1);
	DoQuestFunctionDelay("DiegoDeLanda_Leaving_2", 1.5);
}
//<-- Леди Бет

//--> Мементо
void DiegoDeLanda_Leaving_Memento()
{
	LAi_SetStayType(pchar);
	sld = CharacterFromID("DiegoDeLanda");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "reload", "reload1", "", -1);
	DoQuestFunctionDelay("DiegoDeLanda_Leaving_2", 2.0);
}
//<-- Мементо

// Универсальное Прощание
void DiegoDeLanda_Leaving_End()
{
	LAi_SetActorType(pchar);
	LAi_FadeLong("", "");
	DoQuestFunctionDelay("DiegoDeLanda_Leaving_End_2", 0.4);
	DoQuestFunctionDelay("DiegoDeLanda_Leaving_End_3", 1.0);
}

void DiegoDeLanda_Leaving_End_2(string qName)
{
	if (CharacterIsAlive("DiegoDeLanda"))
	{
		sld = CharacterFromID("DiegoDeLanda");
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
}

void DiegoDeLanda_Leaving_End_3(string qName)
{
	if (questMovieIsLockPlayerCtrl) EndQuestMovie();
	locCameraSleep(false);
	locCameraFollowEx(true);
	LAi_SetPlayerType(pchar);
	chrDisableReloadToLocation = false;
	LAi_LocationFightDisable(loadedLocation, false);
	if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
	{
		SetQuestHeader("SixCaptains");
		AddQuestRecord("SixCaptains", "1");
		AddQuestUserData("SixCaptains", "sSex", GetSexPhrase("","а"));
		CloseQuestHeader("SixCaptains");
	}
	if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
	{
		if (CharacterIsAlive("DiegoDeLanda"))
		{
			AddQuestRecord("SixCaptains", "2");
		}
	}
	Achievment_Set("ach_CL_157");
}

// Убиваем Диего де Ланду
void DiegoDeLanda_Leaving_Shoot(string qName)
{
	LAi_SetActorType(pchar);
	LAi_ActorAnimation(pchar, "Shot", "1", 1.8);
	CharacterTurnByChr(pchar, CharacterFromID("DiegoDeLanda"));
	DoQuestFunctionDelay("DiegoDeLanda_Leaving_Shoot_2", 0.9);
}

void DiegoDeLanda_Leaving_Shoot_2(string qName)
{
	sld = CharacterFromID("DiegoDeLanda");
	LAi_KillCharacter(sld);
	DoQuestFunctionDelay("DiegoDeLanda_Leaving_Shoot_3", 1.5);
}

void DiegoDeLanda_Leaving_Shoot_3(string qName)
{
	if (questMovieIsLockPlayerCtrl) LAi_FadeLong("", "");
	DoQuestFunctionDelay("DiegoDeLanda_Leaving_End_3", 1.0);
}

//=======================================================
bool DiegoDeLanda_QuestComplete(string sQuestName, string qname)
{

	ref sld;
	int i, n; 
	
	bool condition = true;
	
	if (sQuestName == "DiegoDeLanda_2")
	{
		
	}
	else if (sQuestName == "DiegoDeLanda_3")
	{
		
	}
	else
	{
		condition = false;
	}
	
	return condition;
}

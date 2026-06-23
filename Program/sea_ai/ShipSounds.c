
bool bPSSload = false; // Player ship sounds load flag

int PlayShipSoundEvent(ref chr, string name, bool bind)
{
    if (!CheckAttribute(chr, "ship.BoxSize.y"))
        return SOUND_INVALID_ID;

    float x, y, z, height;
    x = float(chr.ship.pos.x);
    y = float(chr.ship.pos.y);
    z = float(chr.ship.pos.z);
    height = float(chr.ship.BoxSize.y) * 0.075;
    int id =  int(SendMessage(Sound, "lslfff", MSG_SOUND_EVENT_PLAY, name, 0, x, y + height, z));
    if (bind) SendMessage(chr, "lllfff", MSG_SHIP_BIND_SOUND, id, true, 0.0, height, 0.0);
    return id;
}

void ShipBells()
{
    int h = GetEventData();
    if (!seaAlarmed && h % 4 == 0)
    {
        PlayShipSoundEvent(PChar, "ShipBells/ShipBells", true);
        BattleInterface.textinfo.Date.text = GetQuestBookData(); // to_do: общий ref обновления
    }
}

void ReleasePlayerShipSounds()
{
    bPSSload = false;
    DeleteAttribute(&TEV, "PSS");
}

void SetPlayerShipSounds()
{
    bPSSload = true;
    // Sailors Chatter
    int id = PlayShipSoundEvent(PChar, "sounds of sailors/SailorChatter_BP", true);
    TEV.PSS.SailorsChatter = id;
    SendMessage(Sound, "llsfl", MSG_SOUND_EVENT_SET_PARAM, id, "Blend", GetFloatByCondition(seaAlarmed, 0.0, 1.0), true);
}

void UpdateSailorsChatter()
{
    if (!bPSSload) return;
    SendMessage(Sound, "llsfl", MSG_SOUND_EVENT_SET_PARAM, int(TEV.PSS.SailorsChatter), "Blend", GetFloatByCondition(seaAlarmed, 0.0, 1.0), false);
}

void Ship_RecreateStaticSounds(bool bWeather)
{
	for (int i=0; i<iNumShips; i++)
    {
	     if (Ships[i] > -1) Ship_CreateStaticSounds(&Characters[Ships[i]]);
	}

	if (bWeather && CheckAttribute(&WeatherParams, "Rain.Sound") && int(WeatherParams.Rain.Sound))
        Whr_SetRainSound(true, bool(Weathers[iCurWeatherNum].Night));
}

void Ship_CreateStaticSounds(ref rCharacter)
{
    if (!CheckAttribute(rCharacter, "Ship.Pos.x")) return; // fix
	if (GetCharacterShipType(rCharacter) == SHIP_NOTUSED) return; // может уже не быть

    ref refBaseShip = GetRealShip(GetCharacterShipType(rCharacter));
	// create water sound
	float fX = float(rCharacter.Ship.Pos.x);
	float fY = float(rCharacter.Ship.Pos.y);
	float fZ = float(rCharacter.Ship.Pos.z);
	rCharacter.Ship.Sounds.WaterID.x = 0.0;
	rCharacter.Ship.Sounds.WaterID.y = -0.3;
	rCharacter.Ship.Sounds.WaterID.z = 0.6;
	rCharacter.Ship.Sounds.WaterID = Play3DSoundEvent("ShipEMB/WTR_Ship_HullSplash", fX, fY, fZ);
    //rCharacter.Ship.Sounds.WaterID = Play3DSoundComplex("ship_water_" + refBaseShip.Soundtype, fX, fY, fZ, true, false);
	//if (int(rCharacter.Ship.Sounds.WaterID) > 0) Sound_SetVolume(int(rCharacter.Ship.Sounds.WaterID), 0.0);
	//rCharacter.Ship.Sounds.WaterSpeed = 30.0;

	// create sails sound
	rCharacter.Ship.Sounds.SailsID.x = 0.0;
	rCharacter.Ship.Sounds.SailsID.y = 0.5;
	rCharacter.Ship.Sounds.SailsID.z = 0.0;
    rCharacter.Ship.Sounds.SailsID = Play3DSoundEvent("ShipEMB/LoopSail", fX, fY, fZ);
	//rCharacter.Ship.Sounds.SailsID = Play3DSoundComplex("sails_up_" + refBaseShip.Soundtype, fX, fY, fZ, true, false);
	//if (int(rCharacter.Ship.Sounds.SailsID) > 0) Sound_SetVolume(int(rCharacter.Ship.Sounds.SailsID), 0.0);
	//rCharacter.Ship.Sounds.SailsMove = 0.0;

	// create turn sound
	rCharacter.Ship.Sounds.TurnID.x = 0.0;
	rCharacter.Ship.Sounds.TurnID.y = 0.0;
	rCharacter.Ship.Sounds.TurnID.z = 0.0;
    rCharacter.Ship.Sounds.TurnID = Play3DSoundEvent("ShipEMB/Creak_ship_turn", fX, fY, fZ);
	//rCharacter.Ship.Sounds.TurnID = Play3DSoundComplex("ship_turn_" + refBaseShip.Soundtype, fX, fY, fZ, true, false);
	//if (int(rCharacter.Ship.Sounds.TurnID) > 0) Sound_SetVolume(int(rCharacter.Ship.Sounds.TurnID), 0.0);
	//rCharacter.Ship.Sounds.TurnSpeed = 0.05;
}

void Ship_PlaySound3D(ref rCharacter, string sSoundID, float fVolume)
{
	float x = float(rCharacter.Ship.Pos.x);
	float y = float(rCharacter.Ship.Pos.y);
	float z = float(rCharacter.Ship.Pos.z);

	int iSoundID = Play3DSound(sSoundID, x, y, z);
	if (iSoundID > 0) { Sound_SetVolume(iSoundID, fVolume); }
}

void Ship_PlaySound3DComplex(ref rCharacter, string sSoundID, float fVolume, float fX, float fY, float fZ)
{
    if (!CheckAttribute(rCharacter, "Ship.BoxSize.x")) return;

	float x = float(rCharacter.Ship.Pos.x);
	float y = float(rCharacter.Ship.Pos.y);
	float z = float(rCharacter.Ship.Pos.z);
	float aY = float(rCharacter.Ship.Ang.y);

    // Смещение в единицах размера коллайдера
    // для x, z смотрим размеры в сторону от рута, поэтому берём половину
	float x1 = fX * float(rCharacter.Ship.BoxSize.x) * 0.5;
    float y1 = fY * float(rCharacter.Ship.BoxSize.y);
	float z1 = fZ * float(rCharacter.Ship.BoxSize.z) * 0.5;
	RotateAroundY(&x1, &z1, cos(aY), sin(aY));

	int iSoundID = Play3DSound(sSoundID, x + x1, y + y1, z + z1);
	if (iSoundID > 0) Sound_SetVolume(iSoundID, fVolume);
}

void Ship_PlaySoundEvent(ref rCharacter, string name, float fX, float fY, float fZ)
{
    if (!CheckAttribute(rCharacter, "Ship.BoxSize.x")) return;

	float x = float(rCharacter.Ship.Pos.x);
	float y = float(rCharacter.Ship.Pos.y);
	float z = float(rCharacter.Ship.Pos.z);
	float aY = float(rCharacter.Ship.Ang.y);

    // Смещение в единицах размера коллайдера
    // для x, z смотрим размеры в сторону от рута, поэтому берём половину
	float x1 = fX * float(rCharacter.Ship.BoxSize.x) * 0.5;
    float y1 = fY * float(rCharacter.Ship.BoxSize.y);
	float z1 = fZ * float(rCharacter.Ship.BoxSize.z) * 0.5;
	RotateAroundY(&x1, &z1, cos(aY), sin(aY));

	Play3DSoundEvent(name, x + x1, y + y1, z + z1);
}

void Ship_PlayVictory(string sSound, int iSoundTime)
{
	FadeOutMusic(3); // boal 3000
	PlayStereoOgg(sSound);
    PlayShipSoundEvent(PChar, "sounds of sailors/SailorJubilation_victory", true);

	iVicSoundTime = iSoundTime;
}

/// странные методы ??? не было их в ПКМ и все было гут
void Ship_VicSoundTime()
{
	if (bAbordageStarted || int(InterfaceStates.Launched)) { return; }

	if (iVicSoundTime > 0)
	{
		iVicSoundTime = iVicSoundTime - iRealDeltaTime;
		if (iVicSoundTime <= 0)
		{
			bUpdatePosMode = true;
		}
	}
}

void Ship_SailsMoveSound()
{
	aref arCharacter = GetEventData();
	bool bMove = GetEventData();

	// update sounds :: SAILS - moving
	if (CheckAttribute(arCharacter, "Ship.Sounds") && int(arCharacter.Ship.Sounds.SailsID) > 0)
		{ Sound_SetVolume(int(arCharacter.Ship.Sounds.SailsID), 0.75 * bMove); }
}

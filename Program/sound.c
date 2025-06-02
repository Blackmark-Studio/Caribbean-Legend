// DEFINES
#define MUSIC_CHANGE_TIME  3000
#define MUSIC_SILENCE_TIME 180000.0
#define SOUNDS_FADE_TIME   200

#event_handler ("LoadSceneSound", "LoadSceneSound")

// PLAY
int Play3DSound(string name, float x, float y, float z)
{
	InitSound();
	//Trace("Play3DSound : "+name);
	return SendMessage(Sound,"lsllllllfff",MSG_SOUND_PLAY, name, SOUND_WAV_3D, VOLUME_FX, false, false, false, 0, x, y, z);
}

int Play3DSoundCached(string name, float x, float y, float z)
{
	InitSound();
	//Trace("Play3DSoundCached : "+name);
	return SendMessage(Sound,"lsllllllfff",MSG_SOUND_PLAY, name, SOUND_WAV_3D, VOLUME_FX, false, false, true, 0, x, y, z);
}

int Play3DSoundComplex(string name, float x, float y, float z, bool bLooped, bool bCached)
{
	InitSound();
	return SendMessage(Sound,"lsllllllfff",MSG_SOUND_PLAY, name, SOUND_WAV_3D, VOLUME_FX, false, bLooped, bCached, 0, x, y, z);
}

int PlayStereoSound(string name)
{
	InitSound();
	//Trace("PlayStereoSound : "+name);
	return SendMessage(Sound,"lslllll",MSG_SOUND_PLAY, name, SOUND_WAV_STEREO, VOLUME_FX, false, false, false);
}

int PlayStereoSoundLooped(string name)
{
	InitSound();
	//Trace("PlayStereoSoundLooped : "+name);
	return SendMessage(Sound,"lsllll",MSG_SOUND_PLAY, name, SOUND_WAV_STEREO, VOLUME_FX, false, true, false);
}

int PlayStereoSoundLooped_JustCache(string name)
{
	InitSound();
	//Trace("PlayStereoSoundLooped : "+name);
	return SendMessage(Sound,"lslllll",MSG_SOUND_PLAY, name, SOUND_WAV_STEREO, VOLUME_FX, true, true, false);
}

int PlayStereoOGG(string name)
{
	InitSound();
	//Trace("PlayStereoSound : "+name);
	return SendMessage(Sound,"lsllllll",MSG_SOUND_PLAY, name, SOUND_MP3_STEREO, VOLUME_FX, false, false, false, 0); //fix boal
}

// OTHER METHODS
void StopSound(int id, int fade)
{
	if(CheckAttribute(pchar, "questTemp.TrackNonStop")) return;
	InitSound();
	//Trace("StopSound : "+id);
	SendMessage(Sound, "lll", MSG_SOUND_STOP, id, fade);
}

void ResumeSound(int id, int fade)
{
	InitSound();
	//Trace("ResumeSound : "+id);
	SendMessage(Sound, "lll", MSG_SOUND_RESUME, id, fade);
}

void ReleaseSound(int id)
{
	InitSound();
	//Trace("ReleaseSound : "+id);
	SendMessage(Sound, "ll", MSG_SOUND_RELEASE, id);
}

// SOUND SCHEMES
void ResetSoundScheme()
{
	if(CheckAttribute(pchar, "questTemp.TrackNonStop")) return;
	InitSound();
	//Trace("ResetSoundScheme");
	SendMessage(Sound,"l",MSG_SOUND_SCHEME_RESET);
}

void SetSoundScheme(string schemeName)
{
	InitSound();
	//Trace("SetSoundScheme: "+schemeName);
	SendMessage(Sound,"ls",MSG_SOUND_SCHEME_SET,schemeName);
}

void AddSoundScheme(string schemeName)
{
	InitSound();
	//Trace("AddSoundScheme: "+schemeName);
	SendMessage(Sound,"ls",MSG_SOUND_SCHEME_ADD,schemeName);
}

/* Теперь эта функция определяет звуковые схемы в игре на СУШЕ!. Внутри проверяется
как погода, так и время. Сделано для того, что бы не было схем, которые
бы игрались независимо от погоды или времени, ибо это всё-таки неудобно
в использовании */

void SetWeatherScheme(string scheme)
{
	if (Whr_IsStorm())
	{
		if (Whr_IsNight())
		{
			SetSoundScheme(scheme+"_night_storm");
		}
		else
		{
			SetSoundScheme(scheme+"_day_storm");
		}
	}
	else 
	{ 
		if (Whr_IsRain())
		{
			if (Whr_IsNight())
			{
					SetSoundScheme(scheme+"_night_rain");
			}
			else
			{
					SetSoundScheme(scheme+"_day_rain");
			}					
		}
		else
		{
			if (Whr_IsNight())
			{
					SetSoundScheme(scheme+"_night");
			}
			else
			{
					SetSoundScheme(scheme+"_day");
			}
		}
	}
}

/* void SetTimeScheme(string scheme)
{
	if (Whr_IsNight())
	{
		AddSoundScheme(scheme+"_night");
	}
	else
	{
		AddSoundScheme(scheme+"_day");
	}
}
*/
void SetSchemeForLocation (ref loc)
{
	if(CheckAttribute(pchar, "questTemp.TrackNonStop")) return;
	if(CheckAttribute(pchar,"systeminfo.stopsound")) return;
    ref mchref = GetMainCharacter();
    mchref.GenQuest.God_hit_us = false; // нефиг воровать :)  (только в домах)
    int iColony = -1; //boal music
    // belamour legendary edition 
	string ClassicSoundScene = "";
	if(CheckAttribute(&InterfaceStates,"ClassicSoundScene") && sti(InterfaceStates.ClassicSoundScene) > 0) ClassicSoundScene = "classic_";
	
    if(CheckAttribute(loc,"type"))
	{
		ResetSoundScheme();
		SetMusicAlarm(""); // музыка не играла, если переходили меж локациями одной схемы - багфиx boal 28.06.06
		switch (loc.type)
		{
			case "town":
				SetWeatherScheme("town");
				if (CheckAttribute(loc,"QuestCapture"))
				{
					SetMusicAlarm(ClassicSoundScene+"music_military");
				}
				if (CheckAttribute(loc,"fastreload"))
				{
					iColony = FindColony(loc.fastreload);
				}
				if (iColony != -1)
				{
					if (CheckAttribute(loc,"QuestCapture")) SetMusicAlarm(ClassicSoundScene+"music_military");
					else 
					{
						if (Whr_IsDay()) 
						{
							SetMusicAlarm(ClassicSoundScene+NationShortName(sti(Colonies[iColony].nation))+"_music_day");
						}
						else SetMusicAlarm(ClassicSoundScene+"music_night");
					}
				}
				else
				{
					SetMusicAlarm(ClassicSoundScene+"music_gorod");
				}
			break;
			
			case "land": // дуэльное поле, лэндфорт и так далее
				SetWeatherScheme("land");
				SetMusicAlarm(ClassicSoundScene+"music_jungle");
			break;
			
			case "jungle":
				SetWeatherScheme("land");
				if (loc.id.label == "Village" || loc.id.label == "ExitTown" || loc.id.label == "Incas Temple")
				{
					switch (loc.id.label)
					{
						case "ExitTown":
							if (Whr_IsDay()) SetMusicAlarm(ClassicSoundScene+"music_exittown");
							else SetMusicAlarm(ClassicSoundScene+"music_nightjungle");
						break;
						case "Incas Temple":
							SetMusicAlarm(ClassicSoundScene+"music_Incas_Temple");
						break;
						case "Village":
							SetMusicAlarm(ClassicSoundScene+"music_village");
						break;
					}
				}
				else
				{
					if (Whr_IsDay()) SetMusicAlarm(ClassicSoundScene+"music_jungle");
					else SetMusicAlarm(ClassicSoundScene+"music_nightjungle");
				}
				DeleteAttribute(pchar, "CheckStateOk"); // убрать флаг проверенности протектором
				if(CheckAttribute(pchar,"StealtDeceptionPenalty")) DeleteAttribute(pchar,"StealtDeceptionPenalty");
			break;
			
			case "mayak":
				ResetSoundScheme();
				SetWeatherScheme("seashore");
				SetMusicAlarm(ClassicSoundScene+"music_mayak");
			break;
			
			case "seashore": 
				ResetSoundScheme();
				SetWeatherScheme("seashore");
				SetMusicAlarm(ClassicSoundScene+"music_shore");
				DeleteAttribute(pchar, "CheckStateOk"); // убрать флаг проверенности протектором
				if(CheckAttribute(pchar,"StealtDeceptionPenalty")) DeleteAttribute(pchar,"StealtDeceptionPenalty");
			break;
			
			case "cave": 
				SetSoundScheme("cave");
				SetMusicAlarm(ClassicSoundScene+"music_cave");
				bMonstersGen = false; //сбросить флаг монстров
			break;
			
			case "dungeon": 
				SetSoundScheme("dungeon");
				SetMusicAlarm(ClassicSoundScene+"music_cave");
				bMonstersGen = false; //сбросить флаг монстров
			break;
			
			case "reef":
				ResetSoundScheme();
				SetSoundScheme("reef");
				SetMusicAlarm(ClassicSoundScene+"music_reef");
			break;
			
			case "mine":
				ResetSoundScheme();
				SetSoundScheme("mine");
				SetMusicAlarm(ClassicSoundScene+"music_cave");
			break;
			
			case "inca_temple": // не используется
				SetSoundScheme("inca_temple");
				SetMusicAlarm("music_coridor");
			break;
			
			case "x_seashore":
				ResetSoundScheme();
				SetWeatherScheme("seashore");
				SetMusicAlarm(ClassicSoundScene+"music_teno");
			break;
			
			case "x_jungle":
				ResetSoundScheme();
				SetWeatherScheme("land");
				SetMusicAlarm(ClassicSoundScene+"music_teno");
			break;
			
			case "questisland":
				ResetSoundScheme();
				if (loc.id.label == "jungle") SetWeatherScheme("land");
				else SetWeatherScheme("seashore");
				SetMusicAlarm(ClassicSoundScene+"music_questislands");
			break;
			
			case "plantation":
				ResetSoundScheme();
				SetWeatherScheme("land");
				SetMusicAlarm(ClassicSoundScene+"music_plantation");
			break;
			
			case "house":
				SetSoundScheme("house");
				if (CheckAttribute(loc,"brothel") && sti(loc.brothel) == true)
				{
					if (CheckAttribute(loc,"fastreload"))
					{
						iColony = FindColony(loc.fastreload);
					}
					if(ClassicSoundScene != "") 
					{
						SetMusicAlarm(ClassicSoundScene+"music_brothel");
					}
					else
					{
						if (iColony != -1) 
						{
							SetMusicAlarm(NationShortName(sti(Colonies[iColony].nation)) + "_music_brothel") ;
						}
						else
						{
							SetMusicAlarm("pir_music_brothel");
						}
					}
				}
				else
				{
					if (CheckAttribute(loc,"id.label") && loc.id.label == "portoffice")
					{
						SetMusicAlarm(ClassicSoundScene+"music_portoffice");
					}
					else
					{
						if(HasSubStr(loc.id, "Common")) SetMusicAlarm(ClassicSoundScene+"music_gorod");
						else SetMusicAlarm(ClassicSoundScene+"music_qhouse");
					}
				}
				mchref.GenQuest.God_hit_us = true; // нефиг воровать :)
			break;
			
			case "tavern":
				SetSoundScheme("tavern");
				if (CheckAttribute(loc,"fastreload"))
				{
					iColony = FindColony(loc.fastreload);
				}
				if (iColony != -1)
				{
			    	SetMusicAlarm(ClassicSoundScene+NationShortName(sti(Colonies[iColony].nation)) + "_music_tavern");
				}
				else
				{
					SetMusicAlarm(ClassicSoundScene+"music_tavern");
				}
			break;
			
			case "shop":
				SetSoundScheme("shop");
				if (CheckAttribute(loc,"id.label") && loc.id.label == "Usurer House")
				{
					SetMusicAlarm(ClassicSoundScene+"music_bank");
				}
				else
				{
					SetMusicAlarm(ClassicSoundScene+"music_shop");
				}
			break;
			
			case "residence":
				SetSoundScheme("residence");
				if (CheckAttribute(loc,"fastreload"))   // boal
				{
					iColony = FindColony(loc.fastreload);
				}
				if (iColony != -1)
				{
					if(ClassicSoundScene != "")
					{
						SetMusicAlarm(ClassicSoundScene+NationShortName(sti(Colonies[iColony].nation)) + "_music_gubernator");
					}
					else
					{
						if(NationShortName(sti(Colonies[iColony].nation)) == "pir")
							SetMusicAlarm(ClassicSoundScene+"pir_music_gubernator");
						else SetMusicAlarm(ClassicSoundScene+"music_gubernator");
					}
				}
				else
				{
					if (Whr_IsDay()) SetMusic(ClassicSoundScene+"music_sea_day");
					else SetMusic(ClassicSoundScene+"music_sea_night");
				}
				if (loadedLocation.id == "SantaCatalina_houseS1_residence") SetMusicAlarm(ClassicSoundScene+"pir_music_gubernator");
			break;
			
			case "church":
				if (isDay()) SetSoundScheme("church");
				SetMusicAlarm(ClassicSoundScene+"music_church");
			break;
			
			case "shipyard":
				SetSoundScheme("shipyard");
				SetMusicAlarm(ClassicSoundScene+"music_shipyard");
			break;
			
			case "fort_attack": // атакуем форт, внутренняя локация			
				SetSoundScheme("fort_attack");
				SetMusicAlarm(ClassicSoundScene+"music_bitva");
			break;
			
			case "fort": // форт для мирных прогулок
				SetWeatherScheme("seashore");
				if (CheckAttribute(loc, "parent_colony"))
				{
					iColony = FindColony(loc.parent_colony);
				}
				if (iColony != -1)
				{
					if (CheckAttribute(loc,"QuestCapture")) SetMusicAlarm("music_military");
					else SetMusicAlarm(ClassicSoundScene+"music_fort");
				}
				else
				{
					SetMusicAlarm(ClassicSoundScene+"music_gorod");
				}
			break;
			
			case "deck": // мирная палуба
				SetSoundScheme("deck");
				if (Whr_IsDay()) SetMusic(ClassicSoundScene+"music_sea_day");
				else SetMusic(ClassicSoundScene+"music_sea_night");
			break;
			
			case "deck_fight": // боевая полуба
				SetSoundScheme("deck_fight");
				SetMusic(ClassicSoundScene+"music_abordage");
			break;
			
			case "slave_deck": // квестовая палуба
				SetSoundScheme("slave_deck");
				//SetMusicAlarm("music_spokplavanie");
			break;
			
			case "quest_deck": // квестовая палуба
				SetSoundScheme("residence");
				SetMusic("music_Quest_Deck");
			break;
			
			case "boarding_cabine":
				SetSoundScheme("cabine");
				SetMusic("music_abordage");
			break;
			
			case "sailing_cabine":
				SetSoundScheme("sail_cabine");
				if (Whr_IsDay()) SetMusicAlarm(ClassicSoundScene+"music_sea_day");
				else SetMusicAlarm(ClassicSoundScene+"music_sea_night");
			break;
			
			case "incquisitio":
				SetSoundScheme("incquisitio");
				SetMusicAlarm(ClassicSoundScene+"music_incquisitio");
			break;
			
			case "jail":
				SetSoundScheme("jail");
				SetMusicAlarm(ClassicSoundScene+"music_jail");
			break;
			
			case "ammo":
				SetSoundScheme("jail");
				SetMusicAlarm(ClassicSoundScene+"music_jail");
			break;
			
			case "LostShipsCity":
				SetWeatherScheme("LostShipsCity");
				SetMusicAlarm(ClassicSoundScene+"music_LostShipsCity");
			break;
			
			case "LSC_inside":
				SetWeatherScheme("LSC_inside");
				SetMusicAlarm(ClassicSoundScene+"music_LostShipsCity");
			break;
			
			case "underwater":
				SetSoundScheme("underwater");
				SetMusicAlarm(ClassicSoundScene+"music_underwater");
			break;
			
			case "teno":
				SetWeatherScheme("land");
				SetMusicAlarm(ClassicSoundScene+"music_teno");
			break;
			
			case "teno_inside":
				SetSoundScheme("teno_inside");
				SetMusicAlarm(ClassicSoundScene+"music_teno_inside");
			break;
			
			case "Alcove": // калеуче
				SetSoundScheme("teno_inside");
				SetMusicAlarm(ClassicSoundScene+"music_alcove");
			break;
			
			case "Alcove_1": // калеуче
				SetSoundScheme("teno_inside");
				SetMusicAlarm(ClassicSoundScene+"music_alcove_1");
			break;
			
			case "Judgement_dungeon": // Addon 2016-1 Jason пиратская линейка
				SetSoundScheme("dungeon");
				SetMusicAlarm(ClassicSoundScene+"music_alcove");
			break;
			
			case "Judgement_hell_dungeon": 
				SetSoundScheme("dungeon");
				if (loc.id == "Judgement_dungeon_10") SetMusicAlarm(ClassicSoundScene+"music_retribution_1");
				else SetMusicAlarm(ClassicSoundScene+"music_retribution");
			break;
			
			case "helensleep_townhall": 
				SetSoundScheme("residence");
				SetMusicAlarm("helendrinking_waybackthen");
			break;
			
			case "helensleep_church": 
				SetSoundScheme("church");
				SetMusicAlarm("helendrinking_waybackthen");
			break;
		}
	}
	if(CheckAttribute(pchar, "GenQuest.CamShuttle"))
	{
		SetPitch(1.0 - stf(pchar.GenQuest.CamShuttle)/20.0);
	}
	else SetPitch(1.0);
	SetStaticSounds(loc);
}

void SetStaticSounds (ref loc)
{
	if(IsEntity(loc) != true) return;
	SetCaveStaticSounds(loc);
	string locatorGroupName = "locators.sound";
	if(CheckAttribute(loadedLocation, locatorGroupName) == 0) return;
	aref locatorGroup;
	makearef(locatorGroup, loc.(locatorGroupName));
	int locatorCount = GetAttributesNum(locatorGroup);
	if(locatorCount <= 0) return;
	string locatorName, locatorType;
	int locatorNameLength;
	int iColony = -1;
	if(CheckAttribute(loc,"fastreload"))
	{
		iColony = FindColony(loc.fastreload);
	}
	
	for(int i = 0; i < locatorCount; i++)
	{
		aref locator = GetAttributeN(locatorGroup, i);
		locatorName = GetAttributeName(locator);
		locatorNameLength = strlen(locatorName);
		locatorType = strcut(locatorName, 0, locatorNameLength-3);
		if ((locatorType == "nightinsects")||(locatorType == "torch"))
		{
			if (Whr_IsDay() && loc.type != "Dungeon" && loc.type != "cave" && loc.type != "fort_attack") continue;
   		}
		if (locatorType == "shipyard")
		{
			if(CheckAttribute(&InterfaceStates,"ClassicSoundScene") && sti(InterfaceStates.ClassicSoundScene) > 0) continue;
			if (Whr_IsNight()) continue;
			if(LAi_IsCapturedLocation) continue;
			if(CheckAttribute(loc, "QuestCapture")) continue;
			if(LAi_group_IsActivePlayerAlarm()) continue;
			if(loc.id == "Villemstad_town") locatorType = "villemstad_"+locatorType;
   		}
		if (locatorType == "church")
		{
			if(CheckAttribute(&InterfaceStates,"ClassicSoundScene") && sti(InterfaceStates.ClassicSoundScene) > 0) continue;
			if (Whr_IsNight()) continue;
			if(LAi_IsCapturedLocation) continue;
			if(CheckAttribute(loc, "QuestCapture")) continue;
			if(LAi_group_IsActivePlayerAlarm()) continue;
			if(loc.id == "Villemstad_town") locatorType = "villemstad_"+locatorType;
   		}
		if (locatorType == "windmill")
		{
			// belamour legendary edition звуки мельницы
			if(loc.id == "FortFrance_town") continue;
			if(Whr_IsNight()) continue;
   		}
		// belamour legendary edition новые звуковые эффекты -->
		if (locatorType == "streetnoise")
		{
			if(!IsMerchantTime()) continue;
			if(LAi_IsCapturedLocation) continue;
			if(CheckAttribute(loc, "QuestCapture")) continue;
   		}
		if(locatorType == "Churchbell")
		{
			if(CheckAttribute(&InterfaceStates,"ClassicSoundScene") && sti(InterfaceStates.ClassicSoundScene) > 0) continue;
			if(LAi_IsCapturedLocation) continue;
			if(CheckAttribute(loc, "QuestCapture")) continue;
			if(Whr_IsNight()) continue;
			// колокола в день святой воды
			if(hrand(15, loc.id) == 0) locatorType = "amulet_7";
			// колокола во время службы
			if(locatorType  != "amulet_7" && hrand(6, loc.id) != 3) continue;
		}
		if(locatorType == "tavern" || locatorType == "brothel")
		{
			if(CheckAttribute(&InterfaceStates,"ClassicSoundScene") && sti(InterfaceStates.ClassicSoundScene) > 0) continue;
			if(LAi_IsCapturedLocation) continue;
			if(CheckAttribute(loc, "QuestCapture")) continue;
			if(LAi_group_IsActivePlayerAlarm()) continue;
			
			if(loc.id == "Villemstad_town") locatorType = "villemstad_"+locatorType;
			else {if(locatorType == "brothel") locatorType = NationShortName(sti(Colonies[iColony].nation)) + "_" + locatorType;}
		}
		if (locatorType == "randsex")
		{
			if(CheckAttribute(&InterfaceStates,"ClassicSoundScene") && sti(InterfaceStates.ClassicSoundScene) > 0) continue;
			if(LAi_IsCapturedLocation) continue;
			if(CheckAttribute(loc, "QuestCapture")) continue;
			if(LAi_group_IsActivePlayerAlarm()) continue;
			if(loc.id == "Villemstad_town") locatorType = "villemstad_"+locatorType;
   		}
		if(locatorType == "seashore")
		{
			if(loadedLocation.id != "khaelroa_port")
			{
				if(loadedLocation.type == "seashore") locatorType = "shoreseashore";
				if(loc.type == "mayak") locatorType = "shoreseashore";
			}
		}
		if(locatorType == "fireplace") 
		{
			if(CheckAttribute(Loc, "locators.heaters_p") && CheckAttribute(Loc, "heaters_night_only") && !Whr_IsNight()) continue;
		} 
		
		if(locatorType == "islamona_tavern")
		{
			if(CheckAttribute(&InterfaceStates,"ClassicSoundScene") && sti(InterfaceStates.ClassicSoundScene) > 0) continue;
		}
		if(locatorType == "band")
		{
			continue;
			//if(CheckAttribute(&InterfaceStates,"ClassicSoundScene") && sti(InterfaceStates.ClassicSoundScene) > 0) continue;
			//if(CheckAttribute(pchar,"systeminfo.bandoff")) continue;
			/* if(iColony != -1)
			{
				locatorType = NationShortName(sti(Colonies[iColony].nation))+"_band";
			}  */
		}
		// <-- legendary edition
		//trace("Create 3D Sound <"+locatorType+ "> for locator <"+locatorName+ "> into pos:("+locator.x+","+locator.y+","+locator.z+")" );
		SendMessage(Sound, "lsllllllfff", MSG_SOUND_PLAY, locatorType, SOUND_WAV_3D, VOLUME_FX, 0, 1, 0, 0, stf(locator.x), stf(locator.y), stf(locator.z));
	}
}

// belamour legendary edition метод создает звуковые локаторы кострам в пещерах и джунглях
void SetCaveStaticSounds (ref loc)
{
	if(IsEntity(loc) != true) return;
	string locatorGroupName = "locators.goto";
	if(CheckAttribute(loadedLocation, locatorGroupName) == 0) return;
	aref locatorGroup;
	makearef(locatorGroup, loc.(locatorGroupName));
	int locatorCount = GetAttributesNum(locatorGroup);
	if(locatorCount <= 0) return;
	string locatorName;
	for(int i = 0; i < locatorCount; i++)
	{
		aref locator = GetAttributeN(locatorGroup, i);
		locatorName = GetAttributeName(locator);
		if(locatorName != "fire") continue;
		if(!CheckAttribute(loc, "fire")) continue;
		
		SendMessage(Sound, "lsllllllfff", MSG_SOUND_PLAY, "fireplace", SOUND_WAV_3D, VOLUME_FX, 0, 1, 0, 0, stf(locator.x), stf(locator.y), stf(locator.z));
	}
}

void SetSchemeForSea ()
{
	if(CheckAttribute(pchar, "questTemp.TrackNonStop")) return;
	ResetSoundScheme();

	// belamour legendary edition 
	string ClassicSoundScene = "";
	if(CheckAttribute(&InterfaceStates,"ClassicSoundScene") && sti(InterfaceStates.ClassicSoundScene) > 0) ClassicSoundScene = "classic_";
	
	// AddSoundScheme("sea");
	if (Whr_IsNight())
	{
		if (Whr_IsStorm())
		{
			AddSoundScheme("sea_night_storm");
			SetMusic(ClassicSoundScene+"music_storm");
		}
		else 
		{ 
			if (pchar.Ship.POS.Mode == SHIP_WAR)
			{
				if(CheckAttribute(pchar, "questTemp.SantaMisericordia.AttackFromMap"))
					SetMusic(ClassicSoundScene+"SantaMisericordia");
				else
					SetMusic(ClassicSoundScene+"music_sea_battle");
			}
			else
			{
				if (Whr_IsDay()) SetMusic(ClassicSoundScene+"music_sea_day");
				else SetMusic(ClassicSoundScene+"music_sea_night");
			}
			if (Whr_IsRain())
			{
				AddSoundScheme("sea_night_rain");
			}
			else
			{
				AddSoundScheme("sea_night");
			}
		}
	}
	else // if Whr_IsDay
	{
		if (Whr_IsStorm())
		{
			AddSoundScheme("sea_day_storm");
			SetMusic(ClassicSoundScene+"music_storm");
		}
		else 
		{ 
   			if (pchar.Ship.POS.Mode == SHIP_WAR)
			{
				if(CheckAttribute(pchar, "questTemp.SantaMisericordia.AttackFromMap"))
					SetMusic(ClassicSoundScene+"SantaMisericordia");
				else
					SetMusic(ClassicSoundScene+"music_sea_battle");
			}
			else
			{
				if (Whr_IsDay()) SetMusic(ClassicSoundScene+"music_sea_day");
				else SetMusic(ClassicSoundScene+"music_sea_night");
			}
			if (Whr_IsRain())
			{
				AddSoundScheme("sea_day_rain");
			}
			else
			{
				AddSoundScheme("sea_day");
			}
		}
	}
	ResumeAllSounds();
}

void SetSchemeForMap ()
{
	if(CheckAttribute(pchar, "questTemp.TrackNonStop")) return;
	ResetSoundScheme();
	AddSoundScheme("sea_map");
	if(CheckAttribute(&InterfaceStates,"ClassicSoundScene") && sti(InterfaceStates.ClassicSoundScene) > 0) SetMusic("classic_music_map");
	else SetMusic("music_map");
	ResumeAllSounds();
	bFortCheckFlagYet = false; //eddy. уберем флаг распознавания фортом врага
}

// MUSIC
int musicID = -1;
int oldMusicID = -1;
int boardM = -1;
string musicName = "";
string oldMusicName = "";
void SetMusic(string name)
{
	if (pchar.location == "UnderWater") return; //не играть музон под водой
	InitSound();
	//Trace("SETTING MUSIC: " + name);

	if (name == musicName)
	{
		SendMessage(Sound, "lll", MSG_SOUND_RESUME, musicID, SOUNDS_FADE_TIME);
		return;
	}

	//Trace("SetMusic : "+name);
	if (oldMusicID >= 0)
	{
        SendMessage(Sound, "lll", MSG_SOUND_STOP, oldMusicID, 0);
		oldMusicID = -1;
	}

	if (musicID >= 0)
	{
		SendMessage(Sound, "lll", MSG_SOUND_STOP, musicID, MUSIC_CHANGE_TIME);
		oldMusicID = musicID;
	}

	//int silenceTime = 20000 + MakeInt(frnd() * MUSIC_SILENCE_TIME);
	//musicID = SendMessage(Sound, "lslllllll", MSG_SOUND_PLAY, name, SOUND_MP3_STEREO, VOLUME_MUSIC, true, true, false, MUSIC_CHANGE_TIME, silenceTime);
	//SendMessage(Sound, "llf", MSG_SOUND_SET_VOLUME, musicID, 1.0);
	// fix поседнее - это громкость звука
	musicID = SendMessage(Sound, "lslllllllf", MSG_SOUND_PLAY, name, SOUND_MP3_STEREO, VOLUME_MUSIC, true, true, false, 0, MUSIC_CHANGE_TIME, 1.0);
	SendMessage(Sound, "lll", MSG_SOUND_RESUME, musicID, MUSIC_CHANGE_TIME);
	
	oldMusicName = musicName;
	musicName = name;
}

// Jason однократное исполнение трека dlc
void SetMusicOnce(string name)
{
	if (pchar.location == "UnderWater") return; //не играть музон под водой
	InitSound();
	
	if (name == musicName)
	{
		SendMessage(Sound, "lll", MSG_SOUND_RESUME, musicID, SOUNDS_FADE_TIME);
		return;
	}

	if (oldMusicID >= 0)
	{
		SendMessage(Sound, "ll", MSG_SOUND_RELEASE, oldMusicID);
		oldMusicID = -1;
	}

	if (musicID >= 0)
	{
		SendMessage(Sound, "lll", MSG_SOUND_STOP, musicID, MUSIC_CHANGE_TIME);
		oldMusicID = musicID;
	}
	musicID = SendMessage(Sound, "lslllllllf", MSG_SOUND_PLAY, name, SOUND_MP3_STEREO, VOLUME_MUSIC, false, false, false, 0, MUSIC_CHANGE_TIME, 1.0);
	SendMessage(Sound, "lll", MSG_SOUND_RESUME, musicID, MUSIC_CHANGE_TIME);
	
	oldMusicName = musicName;
	musicName = name;
}

void FadeOutMusic(int _time)
{
    if(_time < 100)
        _time *= 1000;
	if (musicID >= 0)
	{
		StopSound(musicID, _time);
		musicID = -1;
		musicName = "";
	}
}

// RELOAD
void PauseAllSounds()
{
	if(CheckAttribute(pchar, "questTemp.TrackNonStop")) return;
	//Trace("PauseAllSounds");
	SendMessage(Sound,"lll",MSG_SOUND_STOP, 0, SOUNDS_FADE_TIME);
}

void ResumeAllSounds()
{
	//Trace("ResumeAllSounds");
	//SendMessage(Sound,"lll",MSG_SOUND_RESUME, musicID, SOUNDS_FADE_TIME);
	SendMessage(Sound,"lll",MSG_SOUND_RESUME, 0, SOUNDS_FADE_TIME);
}

// OLD VERSIONS
int PlaySoundDist3D(string name, float x, float y, float z)
{
	return Play3DSound(name, x,y,z);
}

int PlaySoundLoc3D(string name, float x, float y, float z)
{
	return Play3DSoundCached(name, x,y,z);
}

int PlaySound3D(string name, float x, float y, float z)
{
	return Play3DSound(name, x,y,z);
}

void Sound_SetVolume(int iSoundID, float fVolume)
{
	SendMessage(Sound, "llf", MSG_SOUND_SET_VOLUME, iSoundID, fVolume);
}

int PlaySound(string name)
{
	return PlayStereoSound(name);
}

int PlaySoundComplex(string sSoundName, bool bSimpleCache, bool bLooped, bool bCached, int iFadeTime)
{
	return SendMessage(Sound,"lsllllll",MSG_SOUND_PLAY,VOLUME_FX,sSoundName,SOUND_WAV_3D,bSimpleCache,bLooped,bCached,iFadeTime);
}

void StopMusic()
{
}

void PlayMusic(string n)
{
}
//--------------------------------------------------------------------
// Sound Section
//--------------------------------------------------------------------
object Sound;

int alarmed = 0;
int oldAlarmed = 0;
bool seaAlarmed = false;
bool oldSeaAlarmed = false;
void SetMusicAlarm(string name)
{
	if (alarmed == 0)
	{
		SetMusic(name);
	}
	else
	{
  		if (loadedLocation.type == "x_jungle" || loadedLocation.type == "x_seashore" || loadedLocation.id.label == "Maze") SetMusic("music_teno"); // калеуче
		else
		{
			if (loadedLocation.id.label == "Alcove")
			{
				if (loadedLocation.type == "Alcove") SetMusic("music_alcove");
				else SetMusic("music_alcove_1");
			}
            else
            {
                if (loadedLocation.id == "shore67" || loadedLocation.id == "IslaDeVieques_HouseEntrance" || loadedLocation.id == "Shore_mask") SetMusic("music_q_battle");
                else
                {
                    SetMusic("music_bitva");
                    if (LAi_boarding_process != 0)
                    {
                        if (!CheckAttribute(loadedLocation, "CabinType"))
                        {
                            boardM = 1; // потом сбросим звук и схему
                        }
                    }
                }
            }
        }
    }
}

void Sound_OnAllarm()
{
	Sound_OnAlarm(GetEventData());
}

int abordageSoundID;

void Sound_OnAlarm(bool _alarmed)
{
	alarmed = _alarmed;
	if (alarmed == oldAlarmed)
		return;

	if (alarmed != 0)
	{ //alarm on!
		if(CheckAttribute(&InterfaceStates,"ClassicSoundScene") && sti(InterfaceStates.ClassicSoundScene) > 0)
		{
			if (loadedLocation.id == "shore67") SetMusic("music_q_battle");
			else SetMusic("music_bitva");
		}
		else
		{
			ResetSoundScheme();
			StopSound(0,0);
			SetSchemeForLocation (loadedLocation);
		}
	}
	else
	{ //alarm off
		SetMusic(oldMusicName);
	}
	oldAlarmed = alarmed;
}

void Sound_OnSeaAlarm(bool _seaAlarmed)
{
	seaAlarmed = _seaAlarmed;
	if (seaAlarmed == oldSeaAlarmed)
		return;
	string ClassicSoundScene = "";
	if(CheckAttribute(&InterfaceStates,"ClassicSoundScene") && sti(InterfaceStates.ClassicSoundScene) > 0) ClassicSoundScene = "classic_";
	if (seaAlarmed)
	{ //alarm on!
		if(CheckAttribute(pchar, "questTemp.SantaMisericordia.AttackFromMap"))
			SetMusic(ClassicSoundScene+"SantaMisericordia");
		else
			SetMusic(ClassicSoundScene+"music_sea_battle");
	}
	else
	{ //alarm off
		SetMusic(oldMusicName);
	}
	oldSeaAlarmed = seaAlarmed;
}

// set music without any checks
void Sound_OnSeaAlarm555(bool _seaAlarmed, bool bHardAlarm)
{
	if (bHardAlarm) { oldSeaAlarmed = !_seaAlarmed; }
	
	Sound_OnSeaAlarm(_seaAlarmed);
}

void InitSound()
{
	if(CheckAttribute(pchar, "questTemp.TrackNonStop")) return;
	//Trace("InitSound");
	if (!IsEntity(&Sound))
	{
		CreateEntity(&Sound, "Sound");
		SetEventHandler("eventAllarm", "Sound_OnAllarm", 0);
	}
	//SendMessage(Sound,"lf",MSG_SOUND_SET_MASTER_VOLUME,1.0);
}

void ResetSound()
{
	if(CheckAttribute(pchar, "questTemp.TrackNonStop")) return;
	// fix -->
	if (musicID > 0)
	{
		StopSound(musicID,0);
	}
	if (oldMusicID > 0)
	{
		StopSound(oldMusicID,0);
	}
	ResetSoundScheme();
	// fix <--
	StopSound(0,0);
	//ReleaseSound(0);
	musicName = "";
	oldMusicName = "";
	musicID = -1;    //fix boal не было нуления ИД
	oldMusicID = -1;
}

void LoadSceneSound()
{
	int i = FindLoadedLocation();
	if (i != -1)
		SetSchemeForLocation(&Locations[i]);
}

// belamour legendary edition фикс звуковой схемы после смены флага
void SetSchemeAfterFlagRise()
{
	if(CheckAttribute(pchar, "questTemp.TrackNonStop")) return;
	if(IsEntity(&worldMap) != 0) SetSchemeForMap ();
	else
	{
		if(IsEntity(&AISea) != 0) SetSchemeForSea();
		else LoadSceneSound();
	}
}

void SetPitch(float pitch)
{
	SendMessage(Sound,"lf",MSG_SOUND_SET_PITCH, pitch);
}

bool bChangeScheme(int i, int j)
{   
	if (CheckAttribute(pchar, "questTemp.lockedMusic")) 
    {
		return false;
	}
	
	if(CheckAttribute(&Locations[i],"type") && CheckAttribute(&Locations[j],"type"))
	{
		if(Locations[i].type == "questisland") 
        {    
            return true;
        }
		if(Locations[i].type != Locations[j].type) 
        {
            return true;
        }
        else
        {
            if(checkDay(reload_cur_time) != checkDay(reload_time))
            {
                return true;
            }
            if(CheckAttribute(&Locations[i],"townsack") && CheckAttribute(&Locations[j],"townsack"))
            {
                int iNation1 = GetCityNation(Locations[i].townsack);
                int iNation2 = GetCityNation(Locations[j].townsack);
                trace(" iNation1 " + iNation1 + "iNation2 " + iNation2);
                if(iNation1 != iNation2)
                {
                    return true;
                }
            }
        }
	}
	
	return false;
}

void Start_TrackNonStop(string track, float out)
{
	ResetSound();
	//SetMusicOnce("music_SeaDogs1_MainTheme_Sea");
	musicID = SendMessage(Sound, "lslllllllf", MSG_SOUND_PLAY, track, SOUND_MP3_STEREO, VOLUME_MUSIC, false, false, false, 0, MUSIC_CHANGE_TIME, 1.5);
	pchar.questTemp.TrackNonStop = true;
	//pchar.questTemp.NoFast = true;
	DoQuestFunctionDelay("End_TrackNonStop", out);
}

void End_TrackNonStop()
{
	if(CheckAttribute(pchar,"questTemp.TrackNonStop")) DeleteAttribute(pchar,"questTemp.TrackNonStop");
	if(CheckAttribute(pchar,"questTemp.NoFast")) DeleteAttribute(pchar,"questTemp.NoFast");
	SetSchemeAfterFlagRise();
}

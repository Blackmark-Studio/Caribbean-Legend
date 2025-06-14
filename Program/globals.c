#include "storm-engine\sound.h"
#include "storm-engine\messages.h"
#include "sound.c"

string savefile_info = "ver 1.5.0";
// --------- DLC globals ---------------------------------------------
#define DLC_AVAILABLE	  1
#define MAIN_APPID		  2230980
#define DLC_APPID_1       2749310
#define DLC_APPID_2       2628610
#define DLC_APPID_3       3162620
#define DLC_APPID_4       3398030
#define DLC_APPID_5       3549890
#define DLC_APPID_6       3549900
#define DLC_NAME_1        "Loyalty Pack"
#define DLC_NAME_2        "Vile Liittle God"
#define DLC_NAME_3        "Black Mark"
#define DLC_NAME_4        "Ships Pack #1"
#define DLC_NAME_5        "Ships Pack #2"
#define DLC_NAME_6        "Ships Pack #3"
#define DLC_DATE_1	      ""
#define DLC_DATE_2        ""
#define DLC_DATE_3        ""
#define DLC_DATE_4	      ""
#define DLC_DATE_5	      ""
#define DLC_DATE_6	      ""
//--------------------------------------------------------------------
// --------- Max ships on sea ----------------------------------------
#define MAX_SHIPS_ON_SEA	32
#define MAX_SEA_HEIGHT      200.0 
//--------------------------------------------------------------------
//--------------------------------------------------------------------
// Max characters per location
//--------------------------------------------------------------------
#define MAX_CHARS_IN_LOC	128

//--------------------------------------------------------------------
// World Config section
//--------------------------------------------------------------------

// сетевые штучки -->
int iRealDeltaTime = 0;
int iRealYear = 0;
int iRealMonth = 0;
int iRealDay = 0;
// сетевые штучки <--

int iGrassQuality = 0; 		// 0 full, 1 middle, 2 low, 3 off

int iEncountersRate = 1;   	// работает на карте и будет работать для скорости смены отношений и тп
int	iArcadeSails = 1;   	// GetRSRollSpeed
int iFontType = 0;			// 0 italic, 1 normal, 2 mixed
int iDifficulty = 4;		// m_Complexity_2-10
int iMoreInfo = 0;			// 0 fightmode, 1 always
int iControlsMode = 0;		// 0 classic, 1 alternative
int iControlsTips = 0;		// 0 off, 1 base, 2 extended, 3 all
int iCompassPos = 0;		// 0 bottom, 1 top

//bool isLoaded = false;

#define KVL_MODS_FILE "Mods_On_Off_File.txt" // Warship. Глоб. файл для включения/выключения всяких фич игры
#define INVALID_SOUND_ID	0

int ngMusicID = 0;
string sgMusicName = "?";

ref pchar;

object TEV; // Temporary events
object LTR; // Lottery
object HTBL;// Hash Table
int GlobalSeed; // Суточное зерно

//--------------------------------------------------------------------
// Bool section
//--------------------------------------------------------------------
#define false			0
#define true			1			

//--------------------------------------------------------------------
// Nation section
//--------------------------------------------------------------------
#define	MAX_NATIONS       5
#define MAX_NATIONS_SQR   25

#define ENGLAND		0
#define FRANCE		1
#define SPAIN		2
#define HOLLAND		3
#define PIRATE		4

#define NON_PIRATES 3

object	Nations[MAX_NATIONS];
int		NationsRelations[MAX_NATIONS_SQR];
int		NationsRelations2MainCharacter[MAX_NATIONS];

object Render;
object InterfaceBackScene;

//--------------------------------------------------------------------
// Characters section
//--------------------------------------------------------------------
int     GlobalCharacters = 0;  // номер, с которого идут фантомы
int     MAX_CHARACTERS   = 10;
#define TOTAL_CHARACTERS			1201

/* belamour legendary edition динамические массивы
Очень важно!!! Во избежание ошибок компиляции
при объявлении массива указываем его четкую размерность(константа).
и только затем изменяем до нужного значения:
int storeArray[2];
SetArraySize(&storeArray, MAX_LOCATIONS);*/

int MAX_LOCATIONS = 1096;
int MAX_ISLANDS = 38;
int MAX_COLONIES = 43;

#define LSC_MAX_TAVERN		12
#define LSC_MAX_RESIDENCE	3
#define LSC_MAX_CHURCH		7
#define LSC_MAX_PRISON		3
#define LSC_MAX_STORE		3

string 	sEnManNames[10], sEnWomenNames[4], sEnFamilies[108];
string 	sHoManNames[39], sHoWomenNames[14], sHoFamilies[95];
string 	sFrManNames[18], sFrWomenNames[17], sFrFamilies[158];
string 	sSpManNames[42], sSpWomenNames[16], sSpFamilies[66];

string 	sEnManGenNames[5], sEnWomenGenNames[5], sEnGenFamilies[29];
string 	sHoManGenNames[16], sHoWomenGenNames[13], sHoGenFamilies[27];
string 	sFrManGenNames[11], sFrWomenGenNames[8], sFrGenFamilies[86];
string 	sSpManGenNames[21], sSpWomenGenNames[9], sSpGenFamilies[54];


// Падежи
#define NAME_NOM "Nom"  // именительный
#define NAME_GEN "Gen"  // родительный
#define NAME_DAT "Dat"  // дательный
#define NAME_ACC "Acc"  // винительный
#define NAME_ABL "Abl"  // творительный
#define NAME_VOC "Voc"  // предложный

// Типы имен
#define NAMETYPE_ORIG "Orig"
#define NAMETYPE_NICK "Nick"
#define NAMETYPE_VIP  "Vip"
#define NAMETYPE_MAIN "Main"

object  Names;

object  NullCharacter;
object	Characters[TOTAL_CHARACTERS];
object	Locations[1096];
object	Islands[38];
object	Colonies[43];

object  Environment;
int		nMainCharacterIndex = 1;//-1;

int		nLocationsNum;
int		nTeleportLocation;
string	sTeleportLocName;
string  sTeleportLocator;

object SeaParametrs;

int MaxVertices = 32000;//32000;//16000;//8000;//4000
int MaxIndices = 33200;//33200;//17200;//9200;//5200
float GridStepX = 0.1;
float GridStepPC = 0.1;
float MaxWaveDistance = 4000.0;//4000.0;//3000.0;//2000.0;//1000.0
float LodScale = 0.7;//0.7;//1.2;//2.0;//4.0

// Для режима скрытности
int StealthLuck = 0;
int StealthNat  = 4;
int WarningTime = 0;
bool StealthEnable = false;

ref GetCharacter(int iIndex) 
{ 
	if (iIndex < 0 || iIndex >= MAX_CHARACTERS)
	{
		trace("Incorrect Index for a character! Wrong Index is " + iIndex);
		if (MOD_BETTATESTMODE	==	"On") Log_TestInfo("ERROR: Incorrect Index for a character! Wrong Index is " + iIndex);
		return &NullCharacter;
	}
	return &Characters[iIndex]; 
}

ref GetMainCharacter() 
{ 
	return &Characters[nMainCharacterIndex]; 
}

int GetMainCharacterIndex() 
{ 
	return nMainCharacterIndex;
}

int GetCharacterIndex(string string_id) 
{
	return NativeFindCharacter(&Characters, string_id);
}

bool CheckCharacterID(ref rChar, string rChar_ID)
{
	if(rChar.id == rChar_ID) return true;
	else return false;
}

void SetMainCharacterIndex(int index) 
{ 
	if (nMainCharacterIndex!=-1)
	{
		Characters[nMainCharacterIndex].MainCharacter = "0";
		Characters[nMainCharacterIndex].model.entity = "NPCharacter";
	}
	nMainCharacterIndex = index; 
	Characters[nMainCharacterIndex].MainCharacter = "1";
	Characters[nMainCharacterIndex].model.entity = "Player";
	pchar = GetMainCharacter();
}

#event_handler("GOpt_GetGrassQuality","EventReturn_iGrassQuality");

int EventReturn_iGrassQuality()
{
    //trace("GrassQuality"); - эта хрень работает 5-10 раз в секунду
    if (bSeaActive && bStorm && iGrassQuality < 2) { return 2; } //Low
	if (CheckLocGrassOpt() && iGrassQuality < 2) { return 1; } //Medium
	return iGrassQuality;
}

// boal 13.11.06 спец прерывание ядра, для выбора шейдера подсветки и без
#event_handler("GOpt_isGrassLightsOn","EventReturn_isGrassLightsOn");

int EventReturn_isGrassLightsOn()
{
	// trace("EventReturn_isGrassLightsOn"); это я перевел на 1 раз за все время создания травы
	// 1 - светится, 0 - темная
	if(CheckAttribute(&WeatherParams, "Rain") && sti(WeatherParams.Rain))
    {
		if(sti(InterfaceStates.DYNAMICLIGHTS)) 
		{
			if (GetHour() >= 8 && GetHour() <= 18) return 1;
			else return 0;
		}
		return 0;
    }
	
	if (bSeaActive || bStorm || bTornado)
	{
		return 0;
	}
	
	if (GetHour() >= 8 && GetHour() <= 18)
	{
	    return 1;
	}
	return 0;
}

#event_handler("Event_DevMode", "IsDevMode");
int IsDevMode()
{
	if(MOD_BETTATESTMODE == "on")
		return 1;
	return 0;
}

#include "tests\Params.h"

void test__CheckDialogsForCE()
{
    if (!__TST_DIALOGS_CE) return;

	string sPrefix = "PROGRAM\";
	string sScriptsSubdir = "DIALOGS";
	int iPrefixLength = strlen(&sPrefix);

    object oFileFinder;
    string sSearchDir = sPrefix+sScriptsSubdir;

    oFileFinder.dir = sSearchDir;
    oFileFinder.mask = "*.c";
	oFileFinder.recursive = "1";
	oFileFinder.getpaths = "1";
	oFileFinder.stripOverlayPath = "1";
    CreateEntity(&oFileFinder, "FINDFILESINTODIRECTORY");

	aref arFileList;
    makearef(arFileList, oFileFinder.filelist);
    int iFileNum = GetAttributesNum(arFileList);
    DeleteClass(&oFileFinder);

    // Исключения
    object exceptions;
    string attr, attrs[] = {"dialog_func.c"}; // Пока что одно
    for(int i = 0; i < @attrs; i++)
    {
        attr = attrs[i];
        exceptions{attr} = "";
    }

	for(int n = 0; n < iFileNum; n++)
	{
		aref arFile = GetAttributeN(arFileList, n);
		string sFileName = GetAttributeValue(arFile);
		sFileName = strcut(&sFileName, iPrefixLength, strlen(&sFileName) - 1);
        if (__GetDialogSuffix(&sFileName) in &exceptions) continue;
		if (LoadSegment(sFileName)) UnloadSegment(sFileName);
	}
}


void test__CheckInterfacesForCE()
{
    if (!__TST_INTERFACES_CE) return;

	string sPrefix = "PROGRAM\";
	string sScriptsSubdir = "interface";
	int iPrefixLength = strlen(&sPrefix);

    object oFileFinder;
    string sSearchDir = sPrefix+sScriptsSubdir;

    oFileFinder.dir = sSearchDir;
    oFileFinder.mask = "*.c";
	oFileFinder.recursive = "1";
	oFileFinder.getpaths = "1";
	oFileFinder.stripOverlayPath = "1";
    CreateEntity(&oFileFinder, "FINDFILESINTODIRECTORY");

	aref arFileList;
    makearef(arFileList, oFileFinder.filelist);
    int iFileNum = GetAttributesNum(arFileList);
    DeleteClass(&oFileFinder);

    // Исключения
    object exceptions;
    string attr, attrs[] = {
		"interface\interface.c",
		"interface\utils\interface.c",
		"interface\utils\interface.c",
		"interface\utils\MessageBox.c",
		"interface\utils\IconSelector.c",
		"interface\utils\sorting.c",
		"interface\utils\argb_palette.c",
		"interface\utils\items\items.c",
		"interface\utils\goods.c",
		"interface\utils\exchange_from_inventory.c",
		"interface\utils\common_character_scroll.c",
		"interface\utils\numbers_formatter.c",
		"interface\utils\button_icons.c",
		"interface\utilite.c",
		"interface\interface_utils.c"
	};
    for(int i = 0; i < @attrs; i++)
    {
        attr = attrs[i];
        exceptions{attr} = "";
    }

	for(int n = 0; n < iFileNum; n++)
	{
		aref arFile = GetAttributeN(arFileList, n);
		string sFileName = GetAttributeValue(arFile);
		sFileName = strcut(&sFileName, iPrefixLength, strlen(&sFileName) - 1);
		if (exceptions{sFileName}$in)
		{
			trace("ignore: "+sFileName);
			continue;
		}
        //if (__GetDialogSuffix(&sFileName) in &exceptions) continue;
		if (LoadSegment(sFileName)) UnloadSegment(sFileName);
	}
}

void test__CheckMigrationsForCE()
{
    if (!__TST_MIGRATIONS_CE) return;

	string sPrefix = "PROGRAM\";
	string sScriptsSubdir = "migrations";
	int iPrefixLength = strlen(&sPrefix);

    object oFileFinder;
    string sSearchDir = sPrefix+sScriptsSubdir;

    oFileFinder.dir = sSearchDir;
    oFileFinder.mask = "*.c";
	oFileFinder.recursive = "1";
	oFileFinder.getpaths = "1";
	oFileFinder.stripOverlayPath = "1";
    CreateEntity(&oFileFinder, "FINDFILESINTODIRECTORY");

	aref arFileList;
    makearef(arFileList, oFileFinder.filelist);
    int iFileNum = GetAttributesNum(arFileList);
    DeleteClass(&oFileFinder);

    // Исключения
    object exceptions;
    string attr, attrs[] = {
	};
    for(int i = 0; i < @attrs; i++)
    {
        attr = attrs[i];
        exceptions{attr} = "";
    }

	for(int n = 0; n < iFileNum; n++)
	{
		aref arFile = GetAttributeN(arFileList, n);
		string sFileName = GetAttributeValue(arFile);
		sFileName = strcut(&sFileName, iPrefixLength, strlen(&sFileName) - 1);
		if (exceptions{sFileName}$in)
		{
			trace("ignore: "+sFileName);
			continue;
		}
        //if (__GetDialogSuffix(&sFileName) in &exceptions) continue;
		if (LoadSegment(sFileName)) UnloadSegment(sFileName);
	}
}

void test__CheckOtherForCE()
{
    if (!__TST_OTHER_CE) return;

    string attrs[] = {
		"controls\init_sd.c",
		"Encounters\Encounters_init.c",
		"battle_interface\fast_reload_table.c",
		"ships\sails_init.c",
		"weather\WhrInit.c",
		"store\store_init.c",
		"ships\ships_init.c",
		"sea_ai\ShipLights.c",
		"scripts\Treasure_Init.c",
		"nations\nations_init.c",
		"items\modifiers\init\init.c",
		"locations\locations_init.c",
		"islands\islands_init.c",
		"store\initGoods.c",
		"worldmap\worldmap_init.c",
		"items\initItems.c",
		"store\initStore.c",
		"cannons\cannons_init.c",
		"characters\RPG\perks\init.c",
		"characters\Characters_tables.c",
		"characters\init\Antigua.c",
		"characters\init\Barbados.c",
		"characters\init\Jamaica.c",
		"characters\init\Curacao.c",
		"characters\init\Guadeloupe.c",
		"characters\init\Santiago.c",
		"characters\init\Panama.c",
		"characters\init\PuertoPrincipe.c",
		"characters\init\Martinique.c",
		"characters\init\Havana.c",
		"characters\init\Bermudes.c",
		"characters\init\Nevis.c",
		"characters\init\PuertoRico.c",
		"characters\init\LaVega.c",
		"characters\init\SantoDomingo.c",
		"characters\init\PortPax.c",
		"characters\init\PortoBello.c",
		"characters\init\Trinidad.c",
		"characters\init\SentMartin.c",
		"characters\init\Tortuga.c",
		"characters\init\Cartahena.c",
		"characters\init\Maracaibo.c",
		"characters\init\Caracas.c",
		"characters\init\Cumana.c",
		"characters\init\Beliz.c",
		"characters\init\SantaCatalina.c",
		"characters\init\Providence.c",
		"characters\init\StoryCharacters.c",
		"characters\init\Other.c",
		"characters\characters_init.c",
		"Colonies\Colonies_init.c"
	};


	for(int n = 0; n < @attrs; n++)
	{
		string sFileName = attrs[n];
		if (LoadSegment(sFileName)) UnloadSegment(sFileName);
	}
}

string __GetDialogSuffix(ref sPath)
{
    int i = FindSubStr(sPath, "\", 8) + 1;
    return strcut(sPath, i, strlen(sPath) - 1);
}

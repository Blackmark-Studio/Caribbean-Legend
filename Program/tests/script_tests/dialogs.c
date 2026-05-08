#include "tests\Params.h"

void test__CheckSegmentsForCE()
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
    for(int i = 0; i < @&attrs; i++)
    {
        attr = attrs[i];
        exceptions.(attr) = "";
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

string __GetDialogSuffix(ref sPath)
{
    int i = FindSubStr(sPath, "\", 8) + 1;
    return strcut(sPath, i, strlen(sPath) - 1);
}

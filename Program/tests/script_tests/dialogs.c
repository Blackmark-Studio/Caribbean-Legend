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

	for(int n = 0; n < iFileNum; n++)
	{
		aref arFile = GetAttributeN(arFileList, n);
		string sFileName = GetAttributeValue(arFile);
		sFileName = strcut(&sFileName, iPrefixLength, strlen(&sFileName) - 1);
		if (LoadSegment(sFileName)) UnloadSegment(sFileName);
	}
}

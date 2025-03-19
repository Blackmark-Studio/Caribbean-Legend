// mitrokosta переработка контроля версий

#define COMMON_MIGRATION_FOLDER "migrations"
#define MOD_MIGRATION_FOLDER "mod_migrations"
#define MOD_INITS_FOLDER "mod_inits"

extern void ApplyMigration(ref migrationState); // функция которую нужно переопределить в файле конкретной миграции

void ApplyMigrations() {
	ApplyMigrationsForFolder(COMMON_MIGRATION_FOLDER, "");
	CheckForUninstalledMods();
	ApplyModMigrations();
}

// проверяем, что не удалены моды, миграции из которых есть в сейве
void CheckForUninstalledMods() {
  trace("Checking for uninstalled mods...");

  aref migrations;
  makearef(migrations, pchar.migrations);
  int migrationsLength = GetAttributesNum(migrations);
  object ObsoleteState; //сюда сохраним все ненайденные моды
  ref ObsoleteMods;
  makeref(ObsoleteMods, ObsoleteState);

  // идём по всем миграциям в сейве
  for (int i = 0; i < migrationsLength; i++) {
    string migName = GetAttributeName(GetAttributeN(migrations, i));
    if (strcut(migName, 2, 2) != "_")) continue; // это миграция не из мода

    migName = strcut(migName, 3, strlen(migName) - 2);        // режем "_id"
    string modName = getModeNameByMigName(migName, 0);        // получаем название мода
    if (!isModInstalled(modName)) ObsoleteMods.(modName) = 1; // записываем название
  }


  int modsNumber = GetAttributesNum(ObsoleteMods);
  trace("can't found mods number:" + modsNumber);

  string modsList;
  for (int j = 0; j < modsNumber; j++)
  {
    modName = GetAttributeName(GetAttributeN(ObsoleteMods, j));
    trace("can't found mod: " + modName);
    modsList = modsList + modName + " ";
  }

  // выводим предупреждение
  string messageText = GetConvertStr("Uninstalled_Mods_Founded", "migrations.txt") + "~" + modsList;
  // messageText = StringFromKey("Uninstalled_Mods_Founded", "migrations.txt", "TEST");
  if(modsNumber > 0) LaunchMessage(messageText);
}

void ApplyModMigrations() {
	trace("Applying mod migrations...");
	
	string searchPath = "Program\"+MOD_MIGRATION_FOLDER;
	object fileFinder;
	fileFinder.dir = searchPath;
	fileFinder.mask = "*";
	fileFinder.onlydirs = "1";
	fileFinder.onlyfiles = "0";
	CreateEntity(&fileFinder, "FINDFILESINTODIRECTORY");
	DeleteClass(&fileFinder);
	
	aref fileList;
	makearef(fileList, fileFinder.filelist);
	int filesNum = GetAttributesNum(fileList);
	trace("Applying mod migrations... found:"+filesNum);
	object mods;
	
	for (int i = 0; i < filesNum; i++) {
		aref file = GetAttributeN(fileList, i);
		string fileName = GetAttributeValue(file);
		trace("Scanning mod migrations: "+fileName);
		string initPath = MOD_INITS_FOLDER+"\"+fileName+".c";
		if (!LoadSegment(initPath)) {
			trace("Error! Can't load migration file " + initPath);
			continue;
		}
		ApplyMigrationsForFolder(MOD_MIGRATION_FOLDER, fileName);
	}
}

void ApplyMigrationsForFolder(string migrationDir, string modName) {
	trace("Applying migrations...");
	// построение списка миграций
	int migrationsNum = 0;
	string migrationsList[2];
	
    object fileFinder;
	if (modName != "")
	{
		migrationDir = migrationDir + "\" + modName;
	}
	fileFinder.dir = "Program\\"+migrationDir;
	fileFinder.mask = "????_*.c";
	CreateEntity(&fileFinder, "FINDFILESINTODIRECTORY");
	DeleteClass(&fileFinder);
	
	aref fileList;
	makearef(fileList, fileFinder.filelist);
	int filesNum = GetAttributesNum(fileList);
	
	if (filesNum > 1) {
		SetArraySize(&migrationsList, filesNum);
	}
	
	for (int i = 0; i < filesNum; i++) {
		aref file = GetAttributeN(fileList, i);
		string fileName = GetAttributeValue(file);
		//fileName = strcut(&fileName, 0, strlen(&fileName) - 3) + ".c";
		
		string numString = strcut(&fileName, 0, 3);
		int migrationIndex = sti(numString);
		
		// индексы пусть с 1 начинаются, т.к. 0 - признак облома
		if (migrationIndex < 1) {
			trace("Found invalid migration file " + fileName);
		}
		
		trace("Found migration file " + fileName);
		
		migrationsList[migrationIndex - 1] = migrationDir + "\" + fileName;
	}
	
	// последовательное применение миграций с сохранением загруженных сегментов
	object migrationState;
	aref migrations;
	makearef(migrations, pchar.migrations);
	for (i = 0; i < filesNum; i++) {
		fileName = migrationsList[i];
		if (fileName == "") {
			continue;
		}
		
		string migrationName = strcut(&fileName, strlen(migrationDir) + 6, strlen(fileName) - 3);
		
		// миграция уже применена
		string migrationId = "id" + (i + 1);
		if (modName != "") 
		{
			migrationId = "id_" + modName + (i + 1);
		}
		if (CheckAttribute(migrations, migrationId) && migrations.(migrationId) == migrationName) {
			trace("Migration " + migrationName + " already applied");
			continue;
		}
		
		if (!LoadSegment(fileName)) {
			trace("Error! Can't load migration file " + fileName);
			continue;
		}
		
		trace("Applying " + fileName + "...");
		
		ApplyMigration(&migrationState);
		migrations.(migrationId) = migrationName;
		UnloadSegment(fileName);
		
		trace("Success...");
	}
	
	Migration_UnloadSegments(&migrationState);
}

// действуем в предположении того, что все имеющиеся миграции есть в инитах, как и должно быть по-хорошему

void InitMigrations() {
	InitMigrationsForFolder(COMMON_MIGRATION_FOLDER);
	// Моды - всегда в миграциях, моды не меняют иниты
	ApplyModMigrations();
}

void InitMigrationsForFolder(string migrationDir) {
	trace("Initializing migrations...");
	
	object fileFinder;
	fileFinder.dir = "Program\\"+migrationDir;
	fileFinder.mask = "????_*.c";
	CreateEntity(&fileFinder, "FINDFILESINTODIRECTORY");
	DeleteClass(&fileFinder);
	
	aref fileList;
	makearef(fileList, fileFinder.filelist);
	int filesNum = GetAttributesNum(fileList);
	
	aref migrations;
	makearef(migrations, pchar.migrations);
	for (int i = 0; i < filesNum; i++) {
		aref file = GetAttributeN(fileList, i);
		string fileName = GetAttributeValue(file);
		//fileName = strcut(&fileName, 0, strlen(&fileName) - 3) + ".c";
		
		string numString = strcut(&fileName, 0, 3);
		int migrationIndex = sti(numString);
		
		// индексы пусть с 1 начинаются, т.к. 0 - признак облома
		if (migrationIndex < 1) {
			trace("Found invalid migration file " + fileName);
		}
		
		string migrationId = "id" + migrationIndex;
		string migrationName = strcut(&fileName, 5, strlen(fileName) - 3);
		migrations.(migrationId) = migrationName;
		
		trace("Marked migration " + fileName + " as complete...");
	}
}

bool Migration_LoadSegment(ref migrationState, string fileName) {
	aref segments;
	makearef(segments, migrationState.segments);
	
	int segmentsCount = GetAttributesNum(segments);
	for (int i = 0; i < segmentsCount; i++) {
		// сегмент уже загружен
		if (fileName == GetAttributeValue(GetAttributeN(segments, i))) {
			return true;
		}
	}
	
	if (!LoadSegment(fileName)) {
		return false;
	}
	
	string attr = "id" + (segmentsCount + 1);
	segments.(attr) = fileName;
	trace("Loaded segment " + fileName);
	return true;
}

void Migration_UnloadSegments(ref migrationState) {
	aref segments;
	makearef(segments, migrationState.segments);
	
	int segmentsCount = GetAttributesNum(segments);
	for (int i = 0; i < segmentsCount; i++) {
		string fileName = GetAttributeValue(GetAttributeN(segments, i));
		UnloadSegment(fileName);
		trace("Unloaded segment " + fileName);
	}
}

// получаем название мода из миграции
string getModeNameByMigName(string currentMigName, int iteration){
  // если на конце уже не цифра, значит это и есть папка мода
  string lastChar = strcut(currentMigName, strlen(currentMigName) - 1, strlen(currentMigName) - 1);
  if (sti(lastChar) == 0) return currentMigName;
  
  // режем последний символ
  string tempName1 = strcut(currentMigName, 0, strlen(currentMigName) - 2);

  // ррррекурррррсивное прогррррамиррррование
  return getModeNameByMigName(tempName1, iteration + 1) // следующая итерация
}

// есть ли папка с модом?
bool isModInstalled(string folderName)
{
	string searchPath = "Program\"+MOD_MIGRATION_FOLDER;
	object fileFinder;
	fileFinder.dir = searchPath;
	fileFinder.mask = "*";
	fileFinder.onlydirs = "1";
	fileFinder.onlyfiles = "0";
	CreateEntity(&fileFinder, "FINDFILESINTODIRECTORY");
	DeleteClass(&fileFinder);
	
	aref fileList;
	makearef(fileList, fileFinder.filelist);
	int filesNum = GetAttributesNum(fileList);
	
  bool foundedMod = false;
	for (int i = 0; i < filesNum; i++) {
		aref file = GetAttributeN(fileList, i);
		string fileName = GetAttributeValue(file);
		if (fileName == folderName) foundedMod = true;
	}
  return foundedMod;
}


// Сортировка любых интерфейсных таблиц
// column номер столбца
// datatype тип данных в столбце для сравнения
// preserveState – надо ли изменять порядок сортировки
// offset –  отступ, нужен для сравнений иконок по цифре в названии, типа в "ico_n" ищем n
void QoLSortTable(string tableName, int column, string datatype, bool preserveState, int offset)
{
	string curLanguage = BackUpLanguage();

	aref table, upRow, downRow, backup, hr;
	bool isAscend = false;
	object tempRow;
	makearef(table, GameInterface.(tableName));
	makearef(hr, GameInterface.(tableName).hr);
	makearef(backup, hr.backUp);

	string sAscend = "isAscend" + column;
	// Разворачиваем сортировку, если нужно и она вообще была
	if (CheckAttribute(hr, sAscend)) isAscend = true;
	if (!preserveState)
	{
		if (isAscend)	DeleteAttribute(&hr, sAscend);
		isAscend = !isAscend;
	}
	if (isAscend)	hr.(sAscend) = true;

	// Запасаем алфавит для строковых сравнений
	string alphabet; 
	if (datatype == "string") alphabet = GetAlphabet(LanguageGetLanguage(), false);
	if (datatype == "sIcon") alphabet = GetAlphabet("english", false);

	string cellName = "td" + column;
	string lLetter, rLetter;
	int lInt = 0;
	int rInt = 0;
	int i, j;
	int tableSize = GetAttributesNum(&table);
	bool compare = false;

	// Запускаем пузырёк
	for (i=0; i < tableSize - 1; i++){
		for (j=0; j < tableSize - 1 - i; j++){

		upRow = GetAttributeN(&table, j);
		downRow = GetAttributeN(&table, j+1);

		// скипаем заголовки и селекторы
		if (strcut(GetAttributeName(&upRow), 0, 1) != "tr") continue; 
		if (strcut(GetAttributeName(&downRow), 0, 1) != "tr") continue; 

		// Сравниваем значения в зависимости от типа данных
		switch (datatype)
		{
			case "index": // дефолтная сортировка по индексу из строки
				compare = sti(upRow.index) > sti(downRow.index);
			break;
			case "string": 
				lLetter = GetStrSmallRegister(GetSymbol(upRow.(cellName).str, &offset)); 
				rLetter = GetStrSmallRegister(GetSymbol(downRow.(cellName).str, &offset));
				compare = !CompareStringsByABC(&alphabet, &lLetter, &rLetter);
			break;
			case "floatEnd": // преобразуем в число с точкой, отрезав от строки offset символов с начала
				string lNum = upRow.(cellName).str;
				string rNum = downRow.(cellName).str;
				lNum = strcut(lNum, offset, strlen(&lNum) - 1);
				rNum = strcut(rNum, offset, strlen(&rNum) - 1);
				compare = stf(lNum) > stf(rNum);
			break;
			case "integer":
				compare = sti(upRow.(cellName).str) > sti(downRow.(cellName).str);
			break;
			case "float":
				compare = stf(upRow.(cellName).str) > stf(downRow.(cellName).str);
			break;
			case "date": 
				compare = DateStringToInt(upRow.(cellName).str) > DateStringToInt(downRow.(cellName).str);
			break;
			case "intIcon": // ищем цифру в названии иконки на позиции offset, типа portrait_32 → 3
				if (CheckAttribute(&upRow, cellName + ".icon.image")) lInt = sti(GetSymbol(upRow.(cellName).icon.image, &offset)); 
				if (CheckAttribute(&downRow, cellName + ".icon.image")) rInt = sti(GetSymbol(downRow.(cellName).icon.image, &offset)); 
				compare = lInt > rInt;
			break;
			case "sIcon": // сравниваем по первой букве id иконки типа france.tga → f
				if (CheckAttribute(&upRow, cellName + ".icon.image")) lLetter = GetStrSmallRegister(GetSymbol(upRow.(cellName).icon.image, &offset)); 
				if (CheckAttribute(&downRow, cellName + ".icon.image")) rLetter = GetStrSmallRegister(GetSymbol(downRow.(cellName).icon.image, &offset)); 
				compare = !CompareStringsByABC(&alphabet, &lLetter, &rLetter);
			break;
		}

		if (isAscend) compare = !compare;
		if (!compare) continue;

		// Меняем строки местами
		CopyAttributes(&tempRow, upRow);
		CopyAttributes(&upRow, downRow);
		CopyAttributes(&downRow, tempRow);
		}
	}

	makearef(backup, table.hr.backup);
	backup.datatype = datatype;
	backup.offset = offset;
	backup.column = column;
	Table_UpdateWindow(tableName);
	LanguageSetLanguage(curLanguage);
}


// Восстанавливаем последнюю примененную сортировку
void RestoreTableSorting(string tableName)
{
	aref table, backup;
	makearef(table, GameInterface.(tableName));
	if (!CheckAttribute(table, "hr.backup.column")) return;

	makearef(backup, table.hr.backup);
	QoLSortTable(tableName, sti(backup.column), backup.datatype, true, sti(backup.offset));
	Table_UpdateWindow(tableName);
}

// Вернем строчку, куда попал предмет после сортировок
int RestoreSelectedRow(ref table, int tableSize, int selectedGoodsId)
{
	int found = 0;

	for (int i=1; i < tableSize; i++){
		string sRow = "tr" + i;
		if (!CheckAttribute(&table, sRow)) return -1;
		if (selectedGoodsId != sti(table.(sRow).index)) continue;
		found = i;
		break;
	}

	return found;
}

// Восстановим выделение и стрелочки, кинув нужный ивент на нужную строку
bool RestoreAllSelectionsAfterSort(string tableName, int sortedGoodIndex, int sortedRow)
{
	if (sortedGoodIndex == 0) return true;

	aref table;
	makearef(table, GameInterface.(tableName));
	int tableSize = GetAttributesNum(&table);
	int resultRow = RestoreSelectedRow(&table, tableSize, sortedGoodIndex);

	if (resultRow == -1) resultRow = sortedRow; // товара нет, курсор переключается на следующий товар, не меняя строчку

	string sAtrRow = "tr" + resultRow;
	// это была последняя строчка, берем предыдущую
	if (!CheckAttribute(&table, sAtrRow)) 
	{
		resultRow = resultRow - 1; 
		string sPrevAtrRow = "tr" + resultRow;
		if (!CheckAttribute(&table, sPrevAtrRow)) return false; // предыдущей строчки нет, никуда не тыкаем
	}

	if (resultRow < 1 ) return false; // закончились строки в таблице, никуда не тыкаем

	table.select = resultRow;
	Event("TableSelectChange", "sll", tableName, resultRow , 1);
	return true;
}


// Сортируем карты по алфавиту на базе названия острова
void SortMapsIdsByABC(ref array)
{
	string curLanguage = BackUpLanguage();
	string alphabet = GetAlphabet(LanguageGetLanguage(), true);

	int arraySize = GetArraySize(array);
	int j, i;
	for (i=0; i < arraySize - 1; i++) {
		for (j=0; j < arraySize - 1 - i; j++) {
			string lMapId = array[j];
			string rMapId = array[j+1];

			// map_cumana → Cumana
			string lkey = GetMapArea(&lMapId);
			string rkey = GetMapArea(&rMapId);

			// Cumana → К
			string lLetter = GetSymbol(XI_ConvertString(lkey), 0); 
			string rLetter = GetSymbol(XI_ConvertString(rkey), 0);

			if (lMapId == "map_normal" || lMapId == "Map_Best" || lMapId == "map_bad") continue; // выносим общие карты в начало
			if (!CompareStringsByABC(alphabet, lLetter, rLetter)) continue;               // или сравниваем по первой букве

			string q = array[j];
			array[j] = "" + array[j+1];
			array[j+1] = q;
		}
	}
	LanguageSetLanguage(curLanguage);
}

string GetAlphabet(string language, bool uppercase)
{
	if (language == "russian" && uppercase) return "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
	if (language == "russian") return "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
	if (language == "polish" && uppercase) return "AĄBСĆDЕĘFGHIJKLŁMNŃOÓPRSŚTUWYZŹŻ";
	if (language == "polish") return "aąbсćdеęfghijklłmnńoóprsśtuwyzźż";
	if (language == "german" && uppercase) return "ABCDEFGHIJKLMNOPQRSTUVWXYZÄÖÜẞ";
	if (language == "german") return "abcdefghijklmnopqrstuvwxyzäöüß";
	if (language == "spanish" && uppercase) return "ABCDEFGHIJKLMNÑOPQRSTUVWXYZ";
	if (language == "spanish") return "abcdefghijklmnñopqrstuvwxyz";
	if (language == "french" && uppercase) return "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if (language == "french") return "abcdefghijklmnopqrstuvwxyz";
	if (uppercase) return "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return "abcdefghijklmnopqrstuvwxyz";
}

// Сравниваем две строчки по расположению символа в алфавите
bool CompareStringsByABC(string alphabet, string left, string right)
{
	int lPos = findSubStr(alphabet, left, 0);
	int rPos = findSubStr(alphabet, right, 0);
	return lPos > rPos;
}

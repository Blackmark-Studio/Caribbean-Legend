
// Универсальная функция сортировки массивов и таблиц атрибутов.
// rObject - ссылка на объект / aref или массив
// sAttr - атрибут, по которому ведется сортировка. Для массивов примитивных типов не имеет значения.
// sType - тип сортировки:
//             "string"   - регистронезависимая строковая сортировка
//             "int"      - сортировка целых чисел
//             "float"    - сортировка чисел с плавающей точкой
//             "date"     - сортировка дат
// bAscend - true если по возрастанию, false - по убвыванию
// iOffset - пропустить заданное число знаков с начала строки. Игнорируется для примитивных типов
// sPrefix - префикс сортируемых строк. Применимо только если rObject - ссылка на объект или aref.
// extern void SmartSort(ref rObject, string sAttr, string sType, bool bAscend, int iOffset, string sPrefix);



// Сортировка любых интерфейсных таблиц
// column номер столбца
// datatype тип данных в столбце для сравнения
// preserveState – надо ли изменять порядок сортировки
// offset –  отступ, нужен для сравнений иконок по цифре в названии, типа в "ico_n" ищем n
void QoLSortTable(string tableName, int column, string datatype, bool preserveState, int offset)
{
	aref table, backup, hr;
	bool isAscend = false;
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

	string cellName = "td" + column;

	switch (datatype)
	{
		case "index": // дефолтная сортировка по индексу из строки
			SmartSort(table, "index", "int", isAscend, 0, "tr");
		break;
		case "string":
			SmartSort(table, cellName+".str", "string", isAscend, offset, "tr");
		break;
		case "floatEnd": // преобразуем в число с точкой, отрезав от строки offset символов с начала
			SmartSort(table, cellName+".str", "float", isAscend, offset, "tr");
		break;
		case "integer":
			SmartSort(table, cellName+".str", "int", isAscend, offset, "tr");
		break;
		case "float":
			SmartSort(table, cellName+".str", "float", isAscend, offset, "tr");
		break;
		case "date":
			SmartSort(table, cellName+".str", "date", isAscend, offset, "tr");
		break;
		case "intIcon":
			SmartSort(table, cellName+".icon.image", "int", isAscend, offset, "tr");
		break;
		case "sIcon":
			SmartSort(table, cellName+".icon.image", "string", isAscend, offset, "tr");
		break;
	}

	makearef(backup, table.hr.backup);
	backup.datatype = datatype;
	backup.offset = offset;
	backup.column = column;
	Table_UpdateWindow(tableName);
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
	SmartSort(array, "", "string", true, 0, "");
}

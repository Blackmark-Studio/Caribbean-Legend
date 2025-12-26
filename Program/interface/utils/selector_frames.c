// Считываем текущее значение опции и показываем его в тексте
void InitSelectors(string optionName, string selectorName, ref curValue)
{
	if (CheckAttribute(&InterfaceStates, optionName)) {
		curValue = sti(InterfaceStates.(optionName));
	}
	SetSelectorNewTextValue(optionName, selectorName, curValue);
}

// Заполняем тултип о правой кнопке мыши
bool HandleSelectorDescription(ref nodeName, ref header, ref bodyText, string optionName, string selectorName)
{
	if (!HasSubStr(&nodeName, selectorName)) return false; // нода должна содержать имя селектора
	header = XI_ConvertString("Options_" + optionName);
	bodyText = XI_ConvertString("Options_" + optionName + "_descr");
	return true;
}

// Обрабатываем нажатия на стрелки селектора мышкой или с клавы
bool HandleSelector(string nodeName, string optionName, int direction, string selectorName, int optionMax, ref globVariable)
{
	if (!HasSubStr(&nodeName, selectorName)) return false; // нода должна содержать имя селектора
	ChangedOptionByName(&direction, &optionName, &selectorName, &optionMax, &globVariable);
	return true;
}

// Обновляем текст в селекторе
void SetSelectorNewTextValue(string optionName, string selectorName, int iMode)
{
	string des = XI_ConvertString("Options_" + optionName + "_" + iMode);
	SetFormatedText("DESCRIP_TEXT_"+selectorName, des);
}

// Изменяем значение опции
void ChangedOptionByName(int direction, string optionName, string selectorName, int optionMax, ref globVariable)
{
	int newMode = iClamp(0, optionMax, GetAttributeInt(&InterfaceStates, optionName)+direction);
	globVariable = newMode;
	InterfaceStates.(optionName) = newMode;
	SetSelectorNewTextValue(&optionName, &selectorName, &newMode);
}

// По тому, какая стрелка нажата, возвращаем -1 или 1
void SetActionDirection(int actionIndex, ref direction)
{
	if (actionIndex == ACTION_LEFTSTEP) direction = -1;
	else if (actionIndex == ACTION_RIGHTSTEP) direction = 1;
	else direction = 0;
}

// Устанавливаем селектор по умолчанию
void SetSelectorDefault(string optionName, string selectorName, int defaultValue, ref variableToUpdate)
{
	InterfaceStates.(optionName) = defaultValue;
	variableToUpdate = defaultValue;
	SetSelectorNewTextValue(optionName, selectorName, defaultValue);
}
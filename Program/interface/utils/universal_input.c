// Модуль универсализации инпутов
// Для использования
// 1. В ini файл добавляем события arrowsInput/clickInput
// 2. Прописываем XI_InitUniversalInput XI_ExitUniversalInput на запуске и выходе из интерфейса 
// 3. Вешаем XI_SetArrowsInputHandler/XI_SetClickInputHandler в инитке интерфейса

#define XI_UNIVERSAL_INPUT_DEFAULT 0 // стандартный режим инпута Ctrl – x10, shift – x100
#define XI_UNIVERSAL_INPUT_ITEMS 1   // режим инпута помедленнее Ctrl – x5, shift – x20
string XI_UniversalInputCurrentNode = "";

// События для универсального инпута
void XI_InitUniversalInput()
{
	SetEventHandler("arrowsInput", "_XI_HandleArrowsInput", 0);
	SetEventHandler("clickInput", "_XI_HandleClickInput", 0);
}

// Добавляем всплывашку режима ввода к элементу
void XI_SetUniversalInputTooltip(string inputNodeName, string windowName = "MAIN_WINDOW", int mode = XI_UNIVERSAL_INPUT_DEFAULT)
{
	string zoneName = inputNodeName + "_UniversalInputTooltipZone";
	XI_MakeNode("", "PICTURE", zoneName, 30000);

	int x1,y1,x2,y2;
	GetNodePosition(inputNodeName, &x1, &y1, &x2, &y2);
	SetNodePosition(zoneName, x1,y1,x2,y2);
	int xOffset = 30;
	int yOffset = 10;
	x1 -= xOffset;
	y1 -= yOffset;
	x2 += xOffset;
	y2 += yOffset;
	SetTriggerFramePosition(zoneName,x1,y1,x2,y2);
	SetUseTrigger(zoneName, true);
	SetTriggerFrameType(zoneName, 1);
	if (windowName != "") XI_WindowAddNode(windowName, zoneName);
	GameInterface.(zoneName).tooltipdata.mode = mode;
}

// Тултип режима ввода, везде одинаковый, отличаться может только режим
bool XI_ShowUniversalInputTooltip(string currentNode)
{
	if (currentNode + ".tooltipdata" !in &GameInterface) return false;

	object values;
	XI_SetUniversalInputMode(&values, GameInterface.(currentNode).tooltipdata.mode$int(XI_UNIVERSAL_INPUT_DEFAULT));
	string sHeader = GetConvertStr("InputTooltip_header", "ControlsNames.txt");
	string text = DLG_Convert("InputTooltip_text", "ControlsNames.txt", &values);
	CreateTooltipNew(currentNode, sHeader, text, "", "", "", "", "", "", 64, 64, false, false);
	return true;
}

// События для универсального инпута
void XI_ExitUniversalInput()
{
	DelEventHandler("arrowsInput", "_XI_HandleArrowsInput");
	DelEventHandler("clickInput", "_XI_HandleClickInput");
}

// Убрать данные текущего выбранного персонажа/корабля и обработчики с элемента
void XI_UniversalClearElement(string nodeName)
{
	DeleteAttribute(&GameInterface, nodeName + "userdata");
}

// Добавляем элементу обработку стрелок влево/вправо
void XI_SetArrowsInputHandler(string tableName, fref takeFunction, fref giveFunction, int inputMode = XI_UNIVERSAL_INPUT_DEFAULT)
{
	GameInterface.(tableName).userdata.arrowsInput.left := takeFunction;
	GameInterface.(tableName).userdata.arrowsInput.right := giveFunction;
	object values;
	XI_SetUniversalInputMode(&values, inputMode);
	int i = 0;
	for (aref value: &values)
	{
		GameInterface.(tableName).userdata.arrowsInput.("i"+i) = int(value);
		i++;
	}
}

// Добавляем элементу функцию на клик
void XI_SetClickHandler(string nodeName, fref onClickFunction)
{
	GameInterface.(nodeName).userdata.clickInput.onClick := onClickFunction;
}

// Добавляем элементу инпута обработку кликов, предназначено для элементов, передающих +1 -1 куда-либо, то есть обычно это стрелочки
void XI_SetClickInputHandler(string LButtonName, string RButtonName, fref takeFunction, fref giveFunction, int inputMode = XI_UNIVERSAL_INPUT_DEFAULT)
{
	GameInterface.(LButtonName).userdata.clickInput.onClickEnum := takeFunction;
	GameInterface.(RButtonName).userdata.clickInput.onClickEnum := giveFunction;

	object values;
	XI_SetUniversalInputMode(&values, inputMode);
	int i = 0;
	for (aref value: &values)
	{
		GameInterface.(LButtonName).userdata.clickInput.("i"+i) = int(value);
		GameInterface.(RButtonName).userdata.clickInput.("i"+i) = int(value);
		i++;
	}
}

// Обрабатываем нажатия стрелок на элементе инпута
void _XI_HandleArrowsInput()
{
	int commandName = GetEventData();
	string nodeName = GetEventData();
	XI_UniversalInputCurrentNode = nodeName;
	aref handler = GameInterface.(nodeName).userdata.arrowsInput$aref;
	if (handler == nullptr) return;

	switch (commandName)
	{
		case ACTION_LEFTSTEP: handler.left(handler.i0); break;
		case ACTION_SPEEDLEFT: handler.left(XI_IsKeyPressed("control") ? handler.i3 : handler.i2); break;
		case ACTION_CTRLLEFT: handler.left(handler.i1); break;

		case ACTION_RIGHTSTEP: handler.right(handler.i0); break;
		case ACTION_CTRLRIGHT: handler.right(handler.i1); break;
		case ACTION_SPEEDRIGHT: handler.right(XI_IsKeyPressed("control") ? handler.i3 : handler.i2); break;
	}
}

// Обрабатываем клики на элементе инпута
void _XI_HandleClickInput()
{
	int commandName = GetEventData();
	string nodeName = GetEventData();
	XI_UniversalInputCurrentNode = nodeName;
	aref handler = GameInterface.(nodeName).userdata.clickInput$aref;
	if (handler == nullptr) return;

	if ("onClickEnum" in handler)
	{
		bool ctrl = XI_IsKeyPressed("control");
		bool shift = XI_IsKeyPressed("shift");
		switch (commandName)
		{
			case ACTION_MOUSECLICK:
			{
				if (ctrl && shift) handler.onClickEnum(handler.i3);
				else if (ctrl) handler.onClickEnum(handler.i1);
				else if (shift) handler.onClickEnum(handler.i2);
				else handler.onClickEnum(handler.i0);
			}
			break;
			case ACTION_MOUSERCLICK: handler.onClickEnum(handler.i3); break;
		}
		return;
	}

	handler.onClick();
}

void XI_SetUniversalInputMode(ref result, int mode = XI_UNIVERSAL_INPUT_DEFAULT)
{
	result.i0 = 1;
	
	if (mode == XI_UNIVERSAL_INPUT_DEFAULT)
	{
		result.i1 = 10;
		result.i2 = 100;
	}
	else if (mode == XI_UNIVERSAL_INPUT_ITEMS)
	{
		result.i1 = 5;
		result.i2 = 20;
	}
	else assert(false, "Wrong input mode: " + mode);
	result.i3 = 9999999999;
}
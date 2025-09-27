// Функции обмена напрямую из инвентаря, должны быть доступны не только из файла инвентаря, поэтому вынесены отдельно

// Нажали кнопку обмена, закрываем инвентарь, готовим обмен
void OpenExchange()
{
	pchar.GenQuest.CallFunctionParam = "RunFellowExchange";
	pchar.GenQuest.CallFunctionParam.ExchangeId = GetChrIdxFromInterface(sti(GameInterface.CHARACTERS_SCROLL.current), "CHARACTERS_SCROLL");
	pchar.GenQuest.CallFunctionParam.backScrollIdx = GameInterface.CHARACTERS_SCROLL.current;
	DoQuestCheckDelay("CallFunctionParam", 0.1);
	Event("exitCancel");
}

// Запускаем сам обмен
void RunFellowExchange()
{
	SetEventHandler("exitCancel","ReturnToFellowInventory",0);
	LaunchCharacterItemChange(GetCharacter(sti(pchar.GenQuest.CallFunctionParam.ExchangeId)));
}

// Обмен закрыли, готовим открытие инвентаря
void ReturnToFellowInventory()
{
	pchar.GenQuest.CallFunctionParam = "LaunchFellowInventory";
	pchar.GenQuest.CallFunctionParam.backScrollIdx = GetChrIdxFromInterface(sti(GameInterface.CHARACTERS_SCROLL.current), "CHARACTERS_SCROLL");
	DoQuestCheckDelay("CallFunctionParam", 0.1);
	DelEventHandler("exitCancel","ReturnToFellowInventory");
}

// Возвращаемся в инвентарь с выбранным в обмене братишкой
void LaunchFellowInventory()
{
	ref chr = GetCharacter(sti(pchar.GenQuest.CallFunctionParam.backScrollIdx));

	// Переключаем на вкладку пассажиров, если надо
	if (!IsOfficerInSHip(&chr, true) && !IsCompanion(&chr))
	{
		InterfaceStates.nCurScrollTab = 2;
		InterfaceStates.CurCharacter = 0; 
	}

	LaunchInventory();

	// Выбираем братишку в списке персонажей
	aref scroll;
	int newCurChar = 0;
	makearef(scroll, GameInterface.CHARACTERS_SCROLL);
	for (int i=1; i <= sti(scroll.listSize);i++)
	{
		string attrName = "pic"+i;
		if (!CheckAttribute(&scroll, attrName) || scroll.(attrName).character != chr.index) continue;
		newCurChar = i-1;
	}
	GameInterface.CHARACTERS_SCROLL.current = newCurChar;
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE, "CHARACTERS_SCROLL",-1);

	DeleteAttribute(&pchar, "GenQuest.CallFunctionParam.ExchangeId");
	DeleteAttribute(&pchar, "GenQuest.CallFunctionParam.backScrollIdx");
	SetCurrentNode("CHARACTERS_SCROLL");
}

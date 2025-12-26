// Модуль общего поведения торговли и обмена

// метод на TAB переключает вкладки таблицы
void ProcessInterfaceControls() 
{
	string controlName = GetEventData();
	if (controlName == "InterfaceTabSwitch") {
		string tableName = "TABLE_LIST";
		if (CurTable == "TABLE_LIST") tableName = "TABLE_LIST2";

		Event("TableSelectChange", "sll", tableName, 1 , 1);
		GameInterface.TABLE_LIST.select = tableName == "TABLE_LIST";
		GameInterface.TABLE_LIST.top = 0;
		GameInterface.TABLE_LIST2.select = tableName == "TABLE_LIST2";
		GameInterface.TABLE_LIST2.top = 0;
		SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"SCROLL_LIST",0);
		SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"SCROLL_LIST2",0);
		SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"TABLE_LIST", 0 );
		SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"TABLE_LIST2", 0 );
		SetCurrentNode(tableName);
	}
	if (controlName == "InterfaceGoRight") {
		currentTab = currentTab % 5;
		SetControlsTabMode(currentTab + 1);
	}
	if (controlName == "InterfaceGoLeft") {
		currentTab = (5 + currentTab - 2) % 5;
		SetControlsTabMode(currentTab + 1);
	}
}

void REMOVE_BUTTON()  // продать
{
	int targetValue = 1;
	if (XI_IsKeyPressed("control")) targetValue = 10;

	if (BuyOrSell == 0)
    {
        GameInterface.qty_edit.str = -targetValue;
    }
    else
    {
		if (BuyOrSell == -1)
		{
			GameInterface.qty_edit.str = -(sti(GameInterface.qty_edit.str) + targetValue);
		}
		else
		{
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) - targetValue);
		}
		BuyOrSell = 0;
	}
	ChangeQTY_EDIT();
}

void ADD_BUTTON()  // купить
{
	int targetValue = 1;
	if (XI_IsKeyPressed("control")) targetValue = 10;

	if (BuyOrSell == 0)
    {
        GameInterface.qty_edit.str = targetValue;
    }
    else
    {
  		if (BuyOrSell == 1)
		{
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) + targetValue);
		}
		else
		{
			GameInterface.qty_edit.str = -(sti(GameInterface.qty_edit.str) - targetValue);
		}
		BuyOrSell = 0;
	}
	ChangeQTY_EDIT();
}
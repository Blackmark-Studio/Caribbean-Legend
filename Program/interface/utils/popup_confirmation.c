string confirmationBackupNode;
string confirmationHandlerOk;

// Показываем попап с подтверждением действия поверх интерфейса
void CallWithConfirmation(string text, string handlerOk, bool isShown, bool canBeConfirmed = true)
{
	if (!isShown) {
		call handlerOk();
		return;
	}

	confirmationHandlerOk = handlerOk;
	confirmationBackupNode = GetCurrentNode();
	string sIni = "resource\ini\interfaces\components\popup_confirmation.ini";

	XI_MakeNode(sIni, "RECTANGLE", "FADER_CONFIRMATION_POPUP", 104);
	XI_MakeNode(sIni, "MSG_FRAME", "FRAME_CONFIRMATION_POPUP", 60001);
	XI_MakeNode(sIni, "FRAME_GOLD_MSG", "FRAME_GOLD_CONFIRMATION_POPUP", 60003);
	XI_MakeNode(sIni, "FORMATEDTEXT", "TEXT_CONFIRMATION_POPUP", 60003);
	XI_MakeNode(sIni, "TEXTBUTTON", "OK_BUTTON_CONFIRMATION_POPUP", 60003);
	XI_MakeNode(sIni, "TEXTBUTTON", "CANCEL_BUTTON_CONFIRMATION_POPUP", 60003);

	SetFormatedText("TEXT_CONFIRMATION_POPUP", text);
	SetSelectable("OK_BUTTON_CONFIRMATION_POPUP", canBeConfirmed);
	if (canBeConfirmed) SetCurrentNode("OK_BUTTON_CONFIRMATION_POPUP");
	else SetCurrentNode("CANCEL_BUTTON_CONFIRMATION_POPUP");
	XI_WindowDisable("MAIN_WINDOW", true);
	SetEventHandler("HideConfirmationPopup", "HideConfirmationPopup", 0);
	SetEventHandler("ButtonConfirmationOK", "ButtonConfirmationOK", 0);
	Event("PopupIsShown", "s", "Confirmation");
}

// Создать тултип с передачей параметров в виде конфига
void CallWithConfirmationDynamic(fref handlerOk, fref handlerCancel, bool canBeConfirmed, string text1, string header = "", string goodText = "", string badText = "", string text4 = "")
{
	confirmationBackupNode = GetCurrentNode();
	string sIni = "resource\ini\interfaces\components\popup_confirmation.ini";

	int x1,y1,x2,y2;
	// Render.screen_y нагло врёт, поэтому костылим :( 
	XI_MakeNode(sIni, "RECTANGLE", "FADER_CONFIRMATION_POPUP", 60000);
	GetNodePosition("FADER_CONFIRMATION_POPUP", &x1, &y1, &x2, &y2);
	x1 = 660;
	y1 = int((y2-y1)* 0.5)-100;
	x2 = 1260;
	y2 = y1;
	int framePadding = 10;
	int textOffset = 40;
	int buttonsSpace = 60;
	int offset = 0;
	
	XI_MakeNode(sIni, "FRAME", "FRAME_CONFIRMATION_POPUP", 60001);
	XI_MakeNode(sIni, "FRAME_GOLD", "FRAME_GOLD_CONFIRMATION_POPUP", 60003);
	XI_MakeNode(sIni, "FORMATEDTEXT", "TEXT_CONFIRMATION_POPUP", 60003);
	XI_MakeNode(sIni, "TEXTBUTTON", "OK_BUTTON_CONFIRMATION_POPUP", 60003);
	XI_MakeNode(sIni, "TEXTBUTTON", "CANCEL_BUTTON_CONFIRMATION_POPUP", 60003);
	int textStringsNum = GetNumberOfStringsInFormatedText("TEXT_CONFIRMATION_POPUP", text1);
	if (goodText != "") textStringsNum += GetNumberOfStringsInFormatedText("TEXT_CONFIRMATION_POPUP", goodText) + 1;
	if (badText != "") textStringsNum += GetNumberOfStringsInFormatedText("TEXT_CONFIRMATION_POPUP", badText) + 1;
	offset =+ textStringsNum * 15;

	if (header != "")
	{
		textOffset += 40;
		XI_MakeNode(sIni, "TOOLTIP_TITLERECT", "TITLE_BACKGROUND_POPUP", 60003);           // фон заголовка
		XI_MakeNode(sIni, "FORMATEDTEXT", "HEADER_CONFIRMATION_POPUP", 60004);
		SetNodePosition("TITLE_BACKGROUND_POPUP", x1, y1 - offset + 2, x2 , y1 - offset + 51);
		SetNodePosition("HEADER_CONFIRMATION_POPUP", x1, y1 - offset + 8, x2 , y1 - offset + 40);
		SetFormatedText("HEADER_CONFIRMATION_POPUP", header);
	}
	int frameEnd = y2 + offset + framePadding + buttonsSpace + textOffset * 2;
	SetNodePosition("FRAME_CONFIRMATION_POPUP", x1 - framePadding, y1 - offset - framePadding, x2 + framePadding, frameEnd);
	SetNodePosition("FRAME_GOLD_CONFIRMATION_POPUP", x1 , y1 - offset, x2 , y2 + offset + buttonsSpace + textOffset * 2);

	SetNodePosition("OK_BUTTON_CONFIRMATION_POPUP", 690, frameEnd - buttonsSpace - 40, 945, frameEnd - 40);
	SetNodePosition("CANCEL_BUTTON_CONFIRMATION_POPUP", 975, frameEnd - buttonsSpace - 40, 1230, frameEnd - 40);
	SetFormatedText("TEXT_CONFIRMATION_POPUP", text1);
	int n = 0;
	if (goodText != "")
	{
		AddLineToFormatedText("TEXT_CONFIRMATION_POPUP", "~");
		AddLineToFormatedText("TEXT_CONFIRMATION_POPUP", goodText);
		n+=2;
		SetColorToFormatedText("TEXT_CONFIRMATION_POPUP", n, COLOR_LIGHT_GREEN);
	}
	if (badText != "")
	{
		AddLineToFormatedText("TEXT_CONFIRMATION_POPUP", "~");
		AddLineToFormatedText("TEXT_CONFIRMATION_POPUP", badText);
		n+=2;
		SetColorToFormatedText("TEXT_CONFIRMATION_POPUP", n, COLOR_LIGHT_RED);
	}
	
	SetNodePosition("TEXT_CONFIRMATION_POPUP", x1, y1 + textOffset - offset, x2 , y2 + offset + textOffset);
	
	GameInterface.OK_BUTTON_CONFIRMATION_POPUP.onClick := handlerOk;
	if (handlerCancel) GameInterface.CANCEL_BUTTON_CONFIRMATION_POPUP.onClick := handlerCancel;
	else DeleteAttribute(GameInterface, "CANCEL_BUTTON_CONFIRMATION_POPUP.onClick");

	SetSelectable("OK_BUTTON_CONFIRMATION_POPUP", canBeConfirmed);
	if (canBeConfirmed) SetCurrentNode("OK_BUTTON_CONFIRMATION_POPUP");
	else SetCurrentNode("CANCEL_BUTTON_CONFIRMATION_POPUP");
	XI_WindowDisable("MAIN_WINDOW", true);
	SetEventHandler("HideConfirmationPopup", "HideConfirmationPopup", 0);
	SetEventHandler("ButtonConfirmationOK", "ButtonConfirmationOK", 0);
	Event("PopupIsShown", "s", "Confirmation");
}


void HideConfirmationPopup()
{
	XI_DeleteNode("FRAME_CONFIRMATION_POPUP");
	XI_DeleteNode("FRAME_GOLD_CONFIRMATION_POPUP");
	XI_DeleteNode("TITLE_BACKGROUND_POPUP");
	XI_DeleteNode("HEADER_CONFIRMATION_POPUP");
	XI_DeleteNode("FADER_CONFIRMATION_POPUP");
	XI_DeleteNode("TEXT_CONFIRMATION_POPUP");
	XI_DeleteNode("OK_BUTTON_CONFIRMATION_POPUP");
	XI_DeleteNode("CANCEL_BUTTON_CONFIRMATION_POPUP");
	DelEventHandler("HideConfirmationPopup", "HideConfirmationPopup");
	DelEventHandler("ButtonConfirmationOK", "ButtonConfirmationOK");
	XI_WindowDisable("MAIN_WINDOW", false);
	SetCurrentNode(confirmationBackupNode);
	Event("PopupIsClosed", "s", "Confirmation");
	if ("CANCEL_BUTTON_CONFIRMATION_POPUP.onClick" in &GameInterface) GameInterface.CANCEL_BUTTON_CONFIRMATION_POPUP.onClick();
}

void ButtonConfirmationOK()
{
	HideConfirmationPopup();
	if ("OK_BUTTON_CONFIRMATION_POPUP.onClick" in &GameInterface)
	{
		GameInterface.OK_BUTTON_CONFIRMATION_POPUP.onClick();
		return;
	}
	string func = confirmationHandlerOk;
	call func();
}

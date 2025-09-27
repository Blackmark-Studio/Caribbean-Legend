string confirmationBackupNode;
string confirmationHandlerOk;

// Показываем попап с подтверждением действия поверх интерфейса
void CallWithConfirmation(string text, string handlerOk, bool isShown)
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
	XI_MakeNode(sIni, "FRAME_GOLD_MSG", "FRAME_GOLD_MSG_CONFIRMATION_POPUP", 60003);
	XI_MakeNode(sIni, "FORMATEDTEXT", "TEXT_CONFIRMATION_POPUP", 60003);
	XI_MakeNode(sIni, "TEXTBUTTON", "OK_BUTTON_CONFIRMATION_POPUP", 60003);
	XI_MakeNode(sIni, "TEXTBUTTON", "CANCEL_BUTTON_CONFIRMATION_POPUP", 60003);

	SetFormatedText("TEXT_CONFIRMATION_POPUP", text);
	SetCurrentNode("OK_BUTTON_CONFIRMATION_POPUP");
	XI_WindowDisable("MAIN_WINDOW", true);
	SetEventHandler("HideConfirmationPopup", "HideConfirmationPopup", 0);
	SetEventHandler("ButtonConfirmationOK", "ButtonConfirmationOK", 0);
	Event("PopupIsShown", "s", "Confirmation");
}

void HideConfirmationPopup()
{
	XI_DeleteNode("FRAME_CONFIRMATION_POPUP");
	XI_DeleteNode("FRAME_GOLD_MSG_CONFIRMATION_POPUP");
	XI_DeleteNode("FADER_CONFIRMATION_POPUP");
	XI_DeleteNode("TEXT_CONFIRMATION_POPUP");
	XI_DeleteNode("OK_BUTTON_CONFIRMATION_POPUP");
	XI_DeleteNode("CANCEL_BUTTON_CONFIRMATION_POPUP");
	DelEventHandler("HideConfirmationPopup", "HideConfirmationPopup");
	DelEventHandler("ButtonConfirmationOK", "ButtonConfirmationOK");
	XI_WindowDisable("MAIN_WINDOW", false);
	SetCurrentNode(confirmationBackupNode);
	Event("PopupIsClosed", "s", "Confirmation");
}

void ButtonConfirmationOK()
{
	HideConfirmationPopup();
	string func = confirmationHandlerOk;
	call func();
}

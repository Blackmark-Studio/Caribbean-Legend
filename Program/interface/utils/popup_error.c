string errorBackupNode;

// Показываем попап с ошибкой поверх интерфейса
void ShowError(string text)
{
	string sIni = "resource\ini\interfaces\components\popup_error.ini";

	XI_MakeNode(sIni, "RECTANGLE", "FADER_ERROR", 104);
	XI_MakeNode(sIni, "MSG_FRAME", "FRAME_ERROR", 60001);
	XI_MakeNode(sIni, "FRAME_GOLD_MSG", "FRAME_GOLD_MSG_ERROR", 60003);
	XI_MakeNode(sIni, "FORMATEDTEXT", "TEXT_ERROR", 60003);
	XI_MakeNode(sIni, "TEXTBUTTON", "OK_BUTTON_ERROR", 60003);

	SetFormatedText("TEXT_ERROR", text);
	errorBackupNode = GetCurrentNode();
	SetCurrentNode("OK_BUTTON_ERROR");
	XI_WindowDisable("MAIN_WINDOW", true);
	SetEventHandler("HideError", "HideError", 0);
	Event("PopupIsShown", "s", "Error");
}

void HideError()
{
	XI_DeleteNode("FRAME_ERROR");
	XI_DeleteNode("FRAME_GOLD_MSG_ERROR");
	XI_DeleteNode("FADER_ERROR");
	XI_DeleteNode("TEXT_ERROR");
	XI_DeleteNode("OK_BUTTON_ERROR");
	DelEventHandler("HideError", "HideError");
	XI_WindowDisable("MAIN_WINDOW", false);
	SetCurrentNode(errorBackupNode);
	Event("PopupIsClosed", "s", "Error");
}

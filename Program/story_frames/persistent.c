// Здесь функции, подгруженные в код постоянно, чтобы выполнить что-то уже после закрытия стори

// Вызов коллбэка закрытия истории
void SF_OnClose()
{
	DelEventHandler("SF_OnClose", "SF_OnClose");
	aref storyObject = GetEventData();

	if (!CheckAttribute(&storyObject, "onClose")) return; 

	string persistentFilePath = "story_frames\" + storyObject.name + "\OnClose.c";
	if (LoadSegment(persistentFilePath))
	{
		aref onCloseCallbacks = GetAref(storyObject, "OnClose");
		int callbacksQty = GetAttributesNum(onCloseCallbacks);

		for (int i = 0; i < callbacksQty; i++)
		{
			aref functionObject = GetAttributeN(onCloseCallbacks, i);
			string funcName = GetAttributeName(functionObject);
			call funcName(&storyObject);
		}

		UnloadSegment(persistentFilePath);
		return;
	}

	trace("Error: Missing OnClose.c file for story with name: " + storyObject.name);
}

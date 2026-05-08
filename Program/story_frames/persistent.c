// Здесь функции, подгруженные в код постоянно, чтобы выполнить что-то уже после закрытия стори
#include "story_frames\RandomEvents\Birthday\persistent.c" // квестовые функции для ДР
#include "story_frames\RandomEvents\runner.c"              // запускатор случайных событий на глобалке

// Вызов коллбэка закрытия истории
void SF_OnClose()
{
	DelEventHandler("SF_OnClose", "SF_OnClose");
	aref storyObject = GetEventData();

	if (!CheckAttribute(&storyObject, "onClose")) return; 

	string persistentFilePath = SF_FormPath(&storyObject) + "\OnClose.c"
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

// Костыль литературного отступа
string SF_Indent()
{
	return "~~~~~~~~~~~~~~~~~~~~~~~";
}

// Подтягиваем папку для истории, если она лежит внутри папки
string SF_FormPath(ref storyObject)
{
	string nameWithFolder = storyObject.nameWithFolder;
	object temp;
	SplitString(&temp, nameWithFolder, "\");
	if (GetAttributesNum(&temp) > 1)
	{
		storyObject.name = temp.p1;
		storyObject.folder =  temp.p0;
	}
	else storyObject.name = nameWithFolder;

	return "story_frames\" + nameWithFolder;
}

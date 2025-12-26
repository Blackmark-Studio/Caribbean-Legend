#include "story_frames\core.c"
#include "story_frames\helpers.c"
#include "story_frames\varianter.c"
#event_handler("Control Activation","ProcessInterfaceControls");


#define _STORY_INI "resource\ini\interfaces\story_frame.ini"
string storyPath = "story_frames\";
object storyObject;
aref context;

void InitInterface_RS(string iniName, ref _context, string _storyName)
{
	storyObject.random.mode = GetAttributeIntOrDefault(StealthSystem, "debug.random.mode", RAND_TAG);
	makearef(context, storyObject.context);
	CopyAttributes(&context, _context);
	bQuestCheckProcessFreeze = true;
	StartAboveForm(true);
	storyObject.name = _storyName;
	if (IsEntity(&worldMap)) wdmLockReload = true;
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	storyPath += storyObject.name + "\Node0.c";
	if (!LoadSegment(storyPath))
	{
		Trace("StoryFrame: Missing story file: " + storyPath);
		SetFormatedText("STORY_LOGS", "Missing story file: " + storyPath);
	}
	else _SF_NextFrame("Node0");

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0)
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	SetEventHandler("ShowInfoWindow", "ShowHelpHint", 0);
	SetEventHandler("MouseRClickUp","HideHelpHint",0);
	SetEventHandler("HideInfoWindow","HideHelpHint",0);
	_SF_InitButtons();

	SetNodeUsing("KEY_STRS", bBettaTestMode)
	SetNodeUsing("KEY_BTNS", bBettaTestMode)
	if (bBettaTestMode) XI_RegistryExitKey("IExit_Escape");
}

void _SF_InitButtons()
{
	for (int i = 1; i < 7; i++)
	{
		string buttonName = "button" + i;
		TextButton_SetRightTextWidth(buttonName, 100);
	}
}

bool _SF_NextFrame(string func)
{
	if (bBettaTestMode && strlen(func) > 5) Log_Clear(); // для дебага

	storyObject.currentFrame = func;
	if (func == "Node0") storyObject.currentNode = "Node0";
	string StoryFunctionName = storyObject.name + "_" + func;
	call StoryFunctionName();
	if (CheckAttribute(&storyObject, "exit"))
	{
		if (CheckAttribute(&storyObject, "onClose")) SetEventHandler("SF_OnClose", "SF_OnClose", 1);
		PostEvent("SF_OnClose", 100, "a", &storyObject);
		return IDoExit(RC_INTERFACE_ANY_EXIT);
	}

	_SF_ChangeFrameStyle();                            // общий стиль фрейма
	SetFormatedText("STORY_TITLE", storyObject.title); // заголовок фрейма
	FillStoryLogs();                                   // лог истории
	FillButtons();                                     // кнопки
	if (func != "Node0")
	{
		SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"SCROLLER_STORY_LOGS",10.0)
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"STORY_LOGS",2,1.0);
	}
	return true;
}

// Выводим кнопочки, скрываем пустые, включаем/отключаем тултипы
void FillButtons()
{
	aref links, link;
	makearef(links, storyObject.links);
	string text;
	for (int i = 1; i < 7; i++)
	{
		string linkName = "link" + i;
		string buttonName = "button" + i;
		if (!CheckAttribute(links, linkName))
		{
			SetNodeUsing(buttonName, false);
			SetSelectable(buttonName, false);
			continue;
		}

		makearef(link, links.(linkName));
		_SF_ChangeButtonType(buttonName, &link);
		bool disabled = AttributeIsTrue(&link, "disabled");
		SetSelectable(buttonName, !disabled);

		SetNodeUsing(buttonName, true);
		SetUseTrigger(buttonName, disabled || _SF_HasTooltip(&link));
		TextButton_SetGroupImageDefault(buttonName, link.iconGroup, link.iconName, 35, 35, 40);

		text = link.text;
		string percentPart = "";
		if (!disabled && CheckAttributeHasValue(&link, "check"))
		{
			int percent = iClamp(1, 99, GetAttributeInt(&link, "check"));
			percentPart = ToHumanPercent(percent);
			if (strlen(percentPart) < 4) percentPart = "~~~~~~~"+ percentPart;
		}

		TextButton_SetRightText(buttonName, percentPart);
		SetFormatedTextButton(buttonName, "#"+text);
	}
}

bool _SF_HasTooltip(ref link)
{
	if (bBettaTestMode) return true;
	if (CheckAttributeHasValue(link, "tooltipcallback")) return true;
	if (CheckAttributeHasValue(link, "tooltip_main")) return true;
	if (CheckAttributeHasValue(link, "fullText")) return true;
	if (CheckAttributeHasValue(link, "check")) return true;
	return false;
}

void FillStoryLogs()
{
	string value;
	string allText = "";
	SetFormatedText("STORY_LOGS", "");

	aref logs;
	makearef(logs, storyObject.logs);
	int logsNum = GetAttributesNum(logs);
	for (int i = 0; i < logsNum; i++)
	{
		aref log = GetAttributeN(logs, i);
		value = log.value;
		DLG_ReplaceAllMatches(&value, "<br>", NewStr(), 0);
		allText += value;
		AddLineToFormatedText("STORY_LOGS", value);

		if (i == logsNum-1) SetColorToFormatedText("STORY_LOGS", i, argb(255,15,15,15));
	}

	bool scroller = GetNumberOfStringsInFormatedText("STORY_LOGS", allText) > 10;
	SetNodeUsing("SCROLLER_STORY_LOGS", scroller);
	SendMessage( &GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE,"STORY_LOGS", 13, !scroller);
}

void ProcessBreakExit()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

bool IDoExit(int exitCode)
{
	UnloadSegment(storyPath);
	EndAboveForm(true);

	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("ShowInfoWindow", "ShowHelpHint");
	DelEventHandler("MouseRClickUp","HideHelpHint");
	DelEventHandler("HideInfoWindow","HideHelpHint");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
	PostEvent("StopQuestCheckProcessFreeze", 1000);//boal 230804 заморозка проверки квестов
	return true;
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodeName = GetEventData();

	_SF_PressedButton(nodeName, comName);
}

void _SF_PressedButton(string nodeName, string comName)
{
	if (!HasSubStr(nodeName, "BUTTON")) return;
	if (comName != "activate" && comName != "click") return;

	string linkName = "link" + strright(nodeName, 1);
	aref links, link;
	makearef(links, storyObject.links);
	makearef(link, links.(linkName));
	string func = GetAttributeOrDefault(&link, "func", "");
	if (func == "") return;

	_SF_NextFrame(func);
	if (!AttributeIsTrue(link, "reaction")) return;

	SetNodeUsing(nodeName, false);
	DeleteAttribute(&links, linkName);
}

void ShowHelpHint()
{
	string sCurrentNode = GetEventData();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int picW = 128;
	int picH = 128;
	if (HasSubStr(sCurrentNode, "BUTTON"))
	{
		string linkName = "link" + strright(sCurrentNode, 1);
		ActionHelpHint(linkName, &sHeader, &sText1, &sText2, &sText3);
	}

	if (sHeader != "") CreateTooltipNew(sCurrentNode, sHeader, sText1, sText2, sText3, "", sPicture, sGroup, sGroupPicture, picW, picH, true);
	else CloseTooltipNew();
}

void ActionHelpHint(string linkName, ref sHeader, ref text, ref badText, ref goodText)
{
	aref link;
	makearef(link, storyObject.links.(linkName));

	if (AttributeIsTrue(link, "reaction")) sHeader = SF_Convert("Reaction");
	else sHeader = SF_Convert("Action");

	string fullText = GetAttributeOrDefault(&link, "fullText", "");
	if (fullText != "") text += fullText;
	else text += link.text;

	string tempHeader = GetAttributeOrDefault(&link, "tooltip_header", "");
	if (tempHeader != "") sHeader = tempHeader; // кастомный заголовок
	text += GetAttributeOrDefault(&link, "tooltip_main", "");
	badText += GetAttributeOrDefault(&link, "tooltip_bad", "");
	goodText += GetAttributeOrDefault(&link, "tooltip_good", "");

	if (AttributeIsTrue(&link, "disabled"))
	{
		badText += newStr() + "~" + SF_Convert("DisabledAction");
	}
	else if (CheckAttributeHasValue(&link, "check"))
	{
		text += newStr() + "~";
		SF_HumanCurrentChance(&link, sHeader, text, badText, goodText);
	}

	if (CheckAttributeHasValue(&link, "tooltipCallback"))
	{
		string func = link.tooltipCallback;
		call func(&link, &sHeader, &text, &badText, &goodText);
	}

	// Дебаг
	if (bBettaTestMode)
	{
		string attrs[] = {"text", "fullText"};
		text += NewStr() + "~" + newStr();
		text += "====== ↓ [DEBUG] ↓ ======" + newStr() + AtributesToTextExclude(link, &attrs);
		text += "====== ↑ [DEBUG] ↑ ======";
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void HideHelpHint()
{
	CloseTooltipNew();
}

// Пишем во всплывашку разбивку шансов из успешности действия
void SF_HumanCurrentChance(ref link, ref sHeader, ref text, ref badText, ref goodText)
{
	aref check;
	makearef(check, link.check);

	int actionsNum = GetAttributesNum(check);
	for (int i=0; i < actionsNum; i++)
	{
		aref reason = GetAttributeN(check, i);
		string factorName = GetAttributeName(reason);
		string reasonValue = GetAttributeValue(reason);
		int value = sti(reasonValue);

		string humanReason = newStr() + _SF_GetHumanReadableFactor(factorName) + ": " + ToHumanModifier(reasonValue);
		if (factorName == "base") text += newStr() + _SF_GetHumanReadableFactor(factorName) + ": " + ToHumanNumber(value);
		else if (value > 0) goodText += humanReason;
		else if (value < 0) badText += humanReason;
	}
}

// Локализуем названия факторов в проверках
string _SF_GetHumanReadableFactor(string factorName)
{
	if (CheckAttribute(ChrPerksList, "list." + factorName)) return GetPerkName(factorName);

	string temp = "";
	temp = DLG_ConvertE("Factor" + factorName, "StoryFrames\Common.txt", &storyObject);
	if (temp != "") return temp; // нашли в общих ключах сторей

	return DLG_Convert(factorName, "StoryFrames\" + storyObject.name + ".txt", &storyObject); // смотрим в ключах конкретной стори
}

// Разруливаем внешний вид кнопок под реакции и решения
void _SF_ChangeButtonType(string nodeName, ref link)
{
	int iconIndex = 2;
	if (AttributeIsTrue(link, "reaction")) iconIndex = 1;
	TextButton_ChangePartPicture(nodeName, "buttonLeft", "STORY_FRAME", "buttonl" + iconIndex);
	TextButton_ChangePartPicture(nodeName, "buttonMiddle", "STORY_FRAME", "buttonm" + iconIndex);
	TextButton_ChangePartPicture(nodeName, "buttonRight", "STORY_FRAME", "buttonr" + iconIndex);
	TextButton_ChangePartPicture(nodeName, "selectButtonLeft", "STORY_FRAME", "buttonl" + (iconIndex + 2));
	TextButton_ChangePartPicture(nodeName, "selectButtonMiddle", "STORY_FRAME", "buttonm" + (iconIndex + 2));
	TextButton_ChangePartPicture(nodeName, "selectButtonRight", "STORY_FRAME", "buttonr" + (iconIndex + 2));
}

// Правим интерфейс под крах/триумф
void _SF_ChangeFrameStyle()
{
	string style = GetAttributeOrDefault(&StoryObject, "style", "")
	if (style == "") return;

	int cropY = 220;
	int x1,y1,x2,y2;
	GetNodePosition("MAIN_FRAME", &x1, &y1, &x2, &y2);
	SetNodePosition("MAIN_FRAME", x1, y1, x2, y2-cropY);
	GetNodePosition("FRAMEGOLD", &x1, &y1, &x2, &y2);
	SetNodePosition("FRAMEGOLD",x1, y1, x2, y2-cropY);
}

void _SF_ToggleRandomMode()
{
	int randomMode = GetAttributeIntOrDefault(StealthSystem, "debug.random.mode", RAND_TAG);
	if (randomMode == RAND_NORMAL) randomMode = RAND_TAG;
	else randomMode = RAND_NORMAL;
	StealthSystem.debug.random.mode = randomMode;
	if (randomMode) Log_Info("Рандом зафиксирован, перезапусти сторю через Esc");
	else Log_Info("Рандом снова случайный, перезапусти сторю через Esc");
}

// Дебагерское
void ProcessInterfaceControls()
{
	string controlName = GetEventData();
	if (!bBettaTestMode) return;
	if (controlName == "IExit_F1") _SF_ToggleRandomMode(); // F1 → переключение режима рандома
}

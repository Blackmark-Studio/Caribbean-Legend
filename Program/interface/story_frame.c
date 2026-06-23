#include "story_frames\core.c"
#include "story_frames\helpers.c"
#include "story_frames\conditions.c"
#include "story_frames\effects.c"
#include "story_frames\varianter.c"
#event_handler("Control Activation","ProcessInterfaceControls");


#define _STORY_INI "resource\ini\interfaces\story_frame.ini"
#define DEBUG_DETAILS_SHOW 0               // дебажный вывод в тултипах
#define DEBUG_SF_ALL_CONDITIONS_ARE_TRUE 0 // все условия выполняются
string storyPath = "";

// глобалки самой истории
object storyObject;
aref context;

// координаты для динамической расстановки кнопок и заголовков Реакци и Решений
int initButtonsY1 = 532;
int initButtonsY2 = 582;
int initButtonsX1 = 615;
int initButtonsX2 = 1305;

#define SF_NORMAL_MODE -1
#define SF_SUCCESS_MODE 1
#define SF_FAIL_MODE 0

void InitInterface_RS(string iniName, ref _context, string _storyName)
{
	pchar.systeminfo.NoNotifications = true;
	// Обучалка
	if (!CheckAttribute(&TEV, "Tutor.StoryFrames"))
	{
		DoQuestFunctionDelay("Tutorial_StoryFrames", 0.1);
		TEV.Tutor.storyFrames = true;
		TEV.Tutor.callback = "LaunchStoryFrame";
		TEV.Tutor.callback.arg2 = _storyName;
		aref callbackContext = GetAref(&TEV, "Tutor.callback.arg1", true);
		if (_context != nullptr) CopyAttributes(&callbackContext, _context);
		IDoExit(RC_INTERFACE_ANY_EXIT);
		return;
	}

	storyObject.nameWithFolder = _storyName;
	storyObject.random.mode = _SF_Debug_GetRandomMode();
	storyObject.checkResults = _SF_Debug_GetRollChecksModeOverride();
	makearef(context, storyObject.context);
	if (_context != nullptr) CopyAttributes(&context, _context);
	bQuestCheckProcessFreeze = true;
	StartAboveForm(true);
	if (IsEntity(&worldMap)) wdmLockReload = true;
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	storyPath = SF_FormPath(&storyObject) + "\Node0.c";
	_SF_FixYCoord();

	if (!LoadSegment(storyPath))
	{
		Trace("StoryFrame: Missing story file: " + storyPath);
		SetFormatedText("STORY_LOGS", "Missing story file: " + storyPath);
	}
	else _SF_NextFrame("Node0");

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	SetEventHandler("ShowInfoWindow", "ShowHelpHint", 0);
	SetEventHandler("MouseRClickUp","HideHelpHint",0);
	SetEventHandler("HideInfoWindow","HideHelpHint",0);
	_SF_InitButtons();

	SetNodeUsing("KEY_STRS", bBettaTestMode);
	SetNodeUsing("KEY_BTNS", bBettaTestMode);
	SetCurrentNode("STORY_LOGS");
	SetFormatedText("ACTIONS_TITLE", GetConvertStr("Actions", "StoryFrames\Common.txt"));
	SetFormatedText("REACTIONS_TITLE", GetConvertStr("Reactions", "StoryFrames\Common.txt"));

	// дальше для дебага полезности
	if (!bBettaTestMode) return;
	XI_RegistryExitKey("IExit_Escape");
	SetUseTrigger("STORY_LOGS", true);
}

// подтягиваем высоту кнопок по нарисованному окну текста
void _SF_FixYCoord()
{
	int x1,x2,y1,y2;
	GetNodePosition("FRAME_STORY_LOGS", &x1, &y1, &x2, &y2);
	initButtonsY1 = y2;
	initButtonsY2 = y2 + 50;
	initButtonsX1 = x1+12;
	initButtonsX2 = x2-12;
}

void _SF_InitButtons()
{
	 // в большинстве историй 5 кнопок макс, но технически может быть 6, если прямо укажут в истории
	int maxButtons = GetAttributeIntOrDefault(&storyObject, "maxButtons", 5);
	for (int i = 1; i <= maxButtons; i++)
	{
		string buttonName = "button" + i;
		TextButton_SetRightTextWidth(buttonName, 100);
	}

	if (maxButtons < 6) _SF_CropFrames(50);
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

	string lastText = "";
	string allText = "";
	SetFormatedText("STORY_TITLE", storyObject.title);           // заголовок фрейма
	FillStoryLogs(&lastText, &allText);                          // лог истории
	FillButtons();                                               // кнопки
	SetStoryIcon();                                              // иконка истории
	if (func != "Node0") _SF_AdjustScroll(lastText, allText);    // двигаем скролл-бар
	_SF_ChangeFrameStyle();                                      // общий стиль фрейма
	return true;
}

void SetStoryIcon()
{
	bool hasIcon = CheckAttribute(&storyObject, "icon");
	SetNodeUsing("STORY_ICON", hasIcon);
	SetNodeUsing("STORY_ICON_BG", hasIcon);
	if (!hasIcon) return;

	SetNewGroupPicture("STORY_ICON", storyObject.icon.group, storyObject.icon.picture);
}

// Пытаемся выставить скролл-бар по красоте
void _SF_AdjustScroll(string lastText, string allText)
{
	float scrollAdjast = 1.0; // до самого низа по умолчанию
	int lastTextLength = strlen(lastText);
	int allTextLength = strlen(allText);
	if (lastTextLength > 400) scrollAdjast -= float(float(lastTextLength)/allTextLength) / 1.8;

	SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"SCROLLER_STORY_LOGS",10.0);
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"STORY_LOGS",2,scrollAdjast);
}

// Выводим кнопочки, скрываем пустые, включаем/отключаем тултипы
void FillButtons()
{
	SetNodeUsing("REACTIONS_TITLE", false);
	SetNodeUsing("ACTIONS_TITLE", false);

	aref links, link;
	makearef(links, storyObject.links);
	string text;
	int yOffset = 0;
	int buttonHeight = initButtonsY2 - initButtonsY1;
	bool hasReactions = false;
	bool hasActions = false;
	int maxButtons = GetAttributeIntOrDefault(&storyObject, "maxButtons", 5);
	for (int i = 1; i < 7; i++)
	{
		string linkName = "link" + i;
		string buttonName = "button" + i;
		if (!CheckAttribute(links, linkName) || i > maxButtons)
		{
			SetNodeUsing(buttonName, false);
			SetSelectable(buttonName, false);
			continue;
		}
		makearef(link, links.(linkName));
		_SF_AlignButton(buttonName, link, &yOffset, buttonHeight, &hasReactions, &hasActions);
		_SF_ChangeButtonType(buttonName, &link);

		if (AttributeIsTrue(&link, "hidden"))
		{
			SetNodeUsing(buttonName, false);
			SetCurrentNode("STORY_LOGS");
			continue;
		}

		bool disabled = _SF_IsDisabled(&link);
		SetSelectable(buttonName, !disabled);

		SetNodeUsing(buttonName, true);
		SetUseTrigger(buttonName, disabled || _SF_HasTooltip(&link));
		TextButton_SetGroupImageDefault(buttonName, link.iconGroup, link.iconName, 36, 36, 40);

		text = link.text;
		string percentPart = "";
		if (!disabled && CheckAttributeHasValue(&link, "check"))
		{
			int percent = iClamp(1, 99, GetAttributeInt(&link, "check"));
			percentPart = ToHumanPercent(percent);
			if (strlen(percentPart) < 4) percentPart = "~~~~~~~"+ percentPart;
		}
		if (CheckAttributeHasValue(&link, "check.forceText")) percentPart = link.check.forceText;

		TextButton_SetRightText(buttonName, percentPart);
		SetFormatedTextButton(buttonName, "#~~~~~~~~~~~~~~~~~~~~"+text);
	}
}

bool _SF_IsDisabled(ref link)
{
	if (CheckAttributeHasValue(link, "disabled")) return true;

	aref disabledReasons = GetAref(link, "disabled");
	if (disabledReasons == nullptr) return false;

	if (GetAttributesNum(disabledReasons) > 0) return true;
	return false;
}

// Размещаем кнопки и заголовки
void _SF_AlignButton(string buttonName, ref link, ref yOffset, int buttonHeight, ref hasReactions, ref hasActions)
{
	// Есть первая реакция, выставляем заголовок реакций
	if (!hasReactions && AttributeIsTrue(link, "reaction"))
	{
		yOffset += 58;
		hasReactions = true;
		SetNodeUsing("REACTIONS_TITLE", true);
		SetNodePosition("REACTIONS_TITLE", initButtonsX1+220, initButtonsY1+yOffset-44, initButtonsX2-220, initButtonsY2+yOffset-58);
	}

	// Есть первое решение, выставляем заголовок решений
	if (!hasActions && AttributeIsTrue(link, "action"))
	{
		yOffset += 58;
		hasActions = true;
		SetNodeUsing("ACTIONS_TITLE", true);
		SetNodePosition("ACTIONS_TITLE", initButtonsX1+220, initButtonsY1+yOffset-44, initButtonsX2-220, initButtonsY2+yOffset-58);
	}

	// Двигаем кнопки
	SetNodePosition(buttonName, initButtonsX1, initButtonsY1+yOffset, initButtonsX2, initButtonsY2+yOffset);
	yOffset += buttonHeight + 5;
}

bool _SF_HasTooltip(ref link)
{
	if (bBettaTestMode) return true;
	if (CheckAttributeHasValue(link, "tooltipcallback")) return true;
	if (CheckAttributeHasValue(link, "tooltip_main")) return true;
	if (CheckAttributeHasValue(link, "fullText")) return true;
	if (CheckAttributeHasValue(link, "check")) return true;
	if (CheckAttributeHasValue(&StoryObject, "style")) return true; // конец истории
	return false;
}

void FillStoryLogs(ref lastText, ref allText)
{
	float scale = GetDialogScale();
	FormatedText_SetTextScale("STORY_LOGS", scale);
	SetFormatedText("STORY_LOGS", "");

	aref logs;
	makearef(logs, storyObject.logs);
	int logsNum = GetAttributesNum(logs);
	for (int i = 0; i < logsNum; i++)
	{
		aref log = GetAttributeN(logs, i);
		lastText = log.value;
		DLG_ReplaceAllMatches(&lastText, "<br>", NewStr(), 0);
		allText += lastText;
		AddLineToFormatedText("STORY_LOGS", lastText);

		if (i == logsNum-1) SetColorToFormatedText("STORY_LOGS", i, argb(255,15,15,15));
	}

	bool scroller = GetNumberOfStringsInFormatedText("STORY_LOGS", allText) > (scale == 1.0 ? 15 : 12);
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
	DeleteAttribute(pchar,"systeminfo.NoNotifications");

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

	if (comName=="downstep" && nodeName != "STORY_LOGS") _SF_SelectButtonByKeyboard(nodeName,1);
	else if (comName=="upstep" && nodeName != "STORY_LOGS") _SF_SelectButtonByKeyboard(nodeName,-1);
	if (comName=="activate" && nodeName == "STORY_LOGS") _SF_SelectButtonByKeyboard(nodeName,-1);
}

bool _SF_SelectButtonByKeyboard(string currentButtonName, int direction)
{
	int currentArrayIndex;
	if (currentButtonName == "STORY_LOGS") currentArrayIndex = -1;
	else if (!HasSubStr(currentButtonName, "BUTTON")) return false;
	string validButtons[];
	for (int i = 0; i < GetAttributeIntOrDefault(&storyObject, "maxButtons", 5); i++)
	{
		if (GetSelectable("BUTTON" + (i+1))) validButtons += "BUTTON" + (i+1);
		if ("BUTTON" + (i+1) == currentButtonName) currentArrayIndex = GetArraySize(&validButtons)-1;
	}

	int arraySize = GetArraySize(&validButtons);
	if (arraySize < 1)
	{
		trace("Error: missing active buttons in story");
		return false;
	}

	int nextArrayIndex = currentArrayIndex + direction;

	if (nextArrayIndex > arraySize-1) nextArrayIndex = arraySize-1;
	else if (nextArrayIndex < 0) nextArrayIndex = 0;
	SetCurrentNode(validButtons[nextArrayIndex]);
	HideHelpHint();
	_ShowHelpHint(validButtons[nextArrayIndex]);
	
	return true;
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

	if (HasSubStr(func,"Crash")) {
		IDoExit(RC_INTERFACE_ANY_EXIT);
		return;
	}

	if (AttributeIsTrue(&link, "reaction"))
	{
		SetNodeUsing(nodeName, false);
		SetAttribute(&links, linkName + ".hidden", 1);
	};

	Event("SF_ButtonWasPressed", "a", link);
	_SF_NextFrame(func);
}

void ShowHelpHint()
{
	_ShowHelpHint(GetEventData());
}

void _ShowHelpHint(string sCurrentNode)
{
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	if (sCurrentNode == "HELP")
	{
		sHeader = GetConvertStr("HelpTitleCommon", "StoryFrames\Common.txt");
		sText1 = GetConvertStr("HelpTextCommon", "StoryFrames\Common.txt");
	}
	else if (sCurrentNode == "ACTIONS_TITLE")
	{
		sHeader = GetConvertStr("Actions", "StoryFrames\Common.txt");
		sText1 = GetConvertStr("HelpTextActions", "StoryFrames\Common.txt");
	}
	else if (sCurrentNode == "REACTIONS_TITLE")
	{
		sHeader = GetConvertStr("Reactions", "StoryFrames\Common.txt");
		sText1 = GetConvertStr("HelpTextReactions", "StoryFrames\Common.txt");
	}
	if (HasSubStr(sCurrentNode, "BUTTON"))
	{
		string linkName = "link" + strright(sCurrentNode, 1);
		ActionHelpHint(linkName, &sHeader, &sText1, &sText2, &sText3);
		SF_ShowStoryEffects("link" + strright(sCurrentNode, 1), &sHeader, &sText1, &sText2, &sText3);
	}

	if (bBettaTestMode && sCurrentNode == "STORY_LOGS" && DEBUG_DETAILS_SHOW)
	{
		sHeader = "DEBUG";
		sText1 = AtributesToTextAref(&storyObject, "situation");
		sText1 += AtributesToTextAref(&storyObject, "context");
	}

	string config = GetAttributeOrDefault(&StoryObject, "tooltipConfig", "SF_DefaultTooltipConfig");
	if (sHeader != "") CreateTooltipWithConfig(sCurrentNode, sHeader, sText1, sText2, sText3, "", sPicture, sGroup, sGroupPicture, 128, 128, config);
	else CloseTooltipNew();
}

void SF_ShowStoryEffects(string linkName, ref sHeader, ref text, ref badText, ref goodText)
{
	string style = GetAttributeOrDefault(&StoryObject, "style", "");
	if (style == "") return;

	aref effects = GetAref(&storyObject, "effects", true);
	int effectsQty = GetAttributesNum(effects);

	if (strlen(text) > 0) text += "\n\n";
	if (effectsQty == 0 && strlen(badText) + strlen(goodText) == 0)
	{
		text += DLG_Convert("NoEffectsStory", "StoryFrames\Effects.txt");
		return;
	}
	else if (strlen(text) == 0) text += DLG_Convert("effects_title", "StoryFrames\Effects.txt");

	for (int i=0; i < effectsQty; i++)
	{
		aref effect = GetAttributeN(effects, i);
		string tempString = GetAttributeName(effect);
		string effectValue = GetAttributeValue(effect);
		float value = float(effectValue);
		string postfix = "";

		if (HasSubStr(tempString, "Custom"))
		{
			if (GetAttributeInt(&effect, "type") == 0) badText += "\n" + effectValue;
			else goodText += "\n" + effectValue;
			continue;
		}

		if (HasSubStr(tempString, "$pchar"))
		{
			DLG_ReplaceAllMatches(&tempstring, "$pchar", "", 0);
			postfix = "_pchar";
		}
		object ctx;
		CopyAttributes(&ctx, &effect);
		SplitString(&ctx, tempString, "$");
		postfix += "_" + (value >= 0.0);
		string effectType = ctx.p0 + postfix;
		ctx.value = effectValue;

		if (value == 0.0) continue; // эффекты сложились
		if (value < 0.0) badText += "\n" + DLG_Convert(effectType, "StoryFrames\Effects.txt", &ctx);
		else goodText += "\n" + DLG_Convert(effectType, "StoryFrames\Effects.txt", &ctx);
	}

	RemoveFirstNewline(&badtext);
	RemoveFirstNewline(&goodText);
}

void ActionHelpHint(string linkName, ref sHeader, ref text, ref badText, ref goodText)
{
	aref link;
	makearef(link, storyObject.links.(linkName));
	string style = GetAttributeOrDefault(&StoryObject, "style", "");

	if (AttributeIsTrue(link, "reaction")) sHeader = SF_Convert("Reaction");                    // для реакций
	else if (style == "ending") sHeader = link.text;                                            // для нейтральной концовки
	else if (style != "") sHeader = GetConvertStrB("Common" + style, "StoryFrames\Common.txt"); // для триумфа/краха
	else sHeader = SF_Convert("Action");                                                        // для решений

	string fullText = GetAttributeOrDefault(&link, "fullText", "");
	if (fullText != "") text += fullText;
	else if (style == "") text += link.text;

	string tempHeader = GetAttributeOrDefault(&link, "tooltip_header", "");
	if (tempHeader != "") sHeader = tempHeader; // кастомный заголовок
	text += GetAttributeOrDefault(&link, "tooltip_main", "");
	badText += GetAttributeOrDefault(&link, "tooltip_bad", "");
	goodText += GetAttributeOrDefault(&link, "tooltip_good", "");

	if (_SF_IsDisabled(&link)) _SF_DisabledTooltip(&link, &badText);
	else if (CheckAttributeHasValue(&link, "check"))
	{
		SF_HumanCurrentChance(&link, sHeader, text, badText, goodText);
	}

	if (CheckAttributeHasValue(&link, "tooltipCallback"))
	{
		string func = link.tooltipCallback;
		call func(&link, &sHeader, &text, &badText, &goodText);
	}

	// Дебаг
	if (bBettaTestMode && DEBUG_DETAILS_SHOW)
	{
		string attrs[] = {"text", "fullText"};
		text += NewStr() + "~" + newStr();
		text += "====== ↓ [DEBUG] ↓ ======" + newStr() + AtributesToTextExclude(link, &attrs);
		text += "====== ↑ [DEBUG] ↑ ======";
	}

	RemoveFirstNewline(&badtext);
	RemoveFirstNewline(&goodText);
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
	string addText = "";
	string addBadText = "";
	string addGoodText = "";

	int actionsNum = GetAttributesNum(check);
	if (actionsNum == 0) return;
	
	if (strlen(text) > 0) text += "\n\n";
	text += GetConvertStrB("check_title", "StoryFrames\Common.txt");
	for (int i=0; i < actionsNum; i++)
	{
		aref reason = GetAttributeN(check, i);
		string factorName = GetAttributeName(reason);
		string reasonValue = GetAttributeValue(reason);
		int value = int(reasonValue);

		string humanReason = "\n" + _SF_GetHumanReadableFactor(factorName) + ": " + ToHumanModifierPercent(value);
		if (factorName == "base") addText += "\n" + _SF_GetHumanReadableFactor(factorName) + ": " + ToHumanPercent(value);
		else if (value > 0) addGoodText += humanReason;
		else if (value < 0) addBadText += humanReason;
	}

	RemoveFirstNewline(&addGoodText);
	RemoveFirstNewline(&addBadText);
	text += addText;
	goodText += addGoodText;
	badText += addBadText;
}

// Локализуем названия факторов в проверках
// Сначала пробуем отсечь общие штуки, типа перков и предметов, затём идём общим путём локализации с приставкой Factor
string _SF_GetHumanReadableFactor(string factorName)
{
	if (strleft(factorName, 8) == "itmname_") return GetItemName(FindStringAfterChar(factorName, "_")); // это предмет
	if (CheckAttribute(ChrPerksList, "list." + factorName)) return GetPerkName(factorName);             // это перк

	// для имён
	if (HasSubStr(factorName, "$"))
	{
		object temp;
		SplitString(&temp, factorName, "$");
		factorName = temp.p0 + "_chr";
		context.name = temp.p1;
	}

	string locValue = DLG_ConvertE("Factor" + factorName, "StoryFrames\Common.txt", &context);
	if (locValue != "") return locValue; // нашли в общих ключах сторей

	if (CheckAttribute(&storyObject, "module"))
	{
		locValue = DLG_ConvertE("Factor" + factorName, "StoryFrames\" + storyObject.module + ".txt", &context);
		if (locValue != "") return locValue; // нашли в модуле
	}

	return DLG_Convert(factorName, "StoryFrames\" + storyObject.name + ".txt", &context); // смотрим в ключах конкретной стори
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
	string style = GetAttributeOrDefault(&StoryObject, "style", "");
	if (style == "") return;
	if (GetAttributeIntOrDefault(&storyObject, "maxButtons", 5) < 6) _SF_CropFrames(240);
	else _SF_CropFrames(290);

	SetUseTrigger("ACTIONS_TITLE", false);
	SetFormatedText("ACTIONS_TITLE", style == "ending" ? "" : GetConvertStrB("Common" + style, "StoryFrames\Common.txt"));
}

void _SF_CropFrames(int cropY)
{
	int x1,y1,x2,y2;
	GetNodePosition("MAIN_FRAME", &x1, &y1, &x2, &y2);
	SetNodePosition("MAIN_FRAME", x1, y1, x2, y2-cropY);
	GetNodePosition("FRAME_SHADOW", &x1, &y1, &x2, &y2);
	SetNodePosition("FRAME_SHADOW", x1, y1, x2, y2-cropY);
	GetNodePosition("FRAMEGOLD", &x1, &y1, &x2, &y2);
	SetNodePosition("FRAMEGOLD",x1, y1, x2, y2-cropY);
	SetCurrentNode("STORY_LOGS");
}

void _SF_ToggleRandomMode()
{
	int randomMode = _SF_Debug_GetRandomMode();
	if (randomMode == RAND_NORMAL) randomMode = RAND_TAG;
	else randomMode = RAND_NORMAL;
	StealthSystem.debug.random.mode = randomMode;
	if (randomMode) Log_Info("Рандом зафиксирован, перезапусти сторю через Esc");
	else Log_Info("Рандом снова случайный, перезапусти сторю через Esc");
}

void _SF_ToggleCheckMode()
{
	int checkMode = _SF_Debug_GetRollChecksModeOverride();
	checkMode++;
	if (checkMode > SF_SUCCESS_MODE) checkMode = SF_NORMAL_MODE;
	StealthSystem.debug.checkResults = checkMode;
	storyObject.checkResults = checkMode;

	switch (checkMode)
	{
		case SF_NORMAL_MODE:  Log_Info("Проверки работают случайно "); break;
		case SF_SUCCESS_MODE: Log_Info("Проверки всегда успешы "); break;
		case SF_FAIL_MODE:  Log_Info("Проверки всегда провал "); break;
	}
}

// Дебагерское
void ProcessInterfaceControls()
{
	string controlName = GetEventData();
	if (!bBettaTestMode) return;
	if (controlName == "IExit_F1") _SF_ToggleRandomMode(); // F1 → переключение режима рандома
	if (controlName == "IExit_F2") _SF_ToggleCheckMode(); // F2 → переключение всегда успех/всегда провал/случайно
}

void _SF_DisabledTooltip(ref link, ref tooltipText)
{
	if (CheckAttribute(link, "tooltip_bad")) return;
	// tooltipText += newStr() + "~" SF_Convert("DisabledAction");

	aref disabledReasons = GetAref(link, "disabled");
	if (disabledReasons == nullptr) return;

	string result = "";
	int reasonsQty = GetAttributesNum(disabledReasons);
	for (int i = 0; i < reasonsQty; i++)
	{
		aref reason = GetAttributeN(disabledReasons, i);
		string reasonName = GetAttributeName(reason);
		if (HasSubStr(reasonName, "$")) reasonName = FindStringBeforeChar(reasonName, "$");
		object context;
		context.value = GetAttributeValue(reason);
		if (reasonName == "custom") result += "\n" + context.value;
		else result += "\n" + DLG_Convert("DisabledAction_" + reasonName, "StoryFrames\Common.txt", &context);
	}

	RemoveFirstNewline(&result);
	tooltipText += result;
}

// Цветовой конфиг тултипа для историй
object SF_DefaultTooltipConfig()
{
	object res;
	res.theme = "dark";
	res.color1 = argb(255, 255, 255, 255);
	res.color2 = argb(255, 255, 128, 128);
	res.color3 = ARGB_Color("green");
	res.color4 = argb(255, 255, 255, 255);
	return res;
}
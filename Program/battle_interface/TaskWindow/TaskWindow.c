
#include "battle_interface\TaskWindow\TW_init.c"

object objTask;

////////////////////////////////////////////////////////////////////////
//  TASK WINDOW
////////////////////////////////////////////////////////////////////////

void TW_SetDefines()
{
	float fHtRatio = stf(Render.screen_y) / iHudScale;
	aref arDef;
	makearef(arDef, objTask.defines);
	
	// основная точка, от которой рассчитываются все остальные
	arDef.left = sti(showWindow.right) / 32;
	arDef.top = sti(showWindow.bottom) / 2.5;
	
	// вертикальные расстояния
	arDef.header = makeint(TW_DEF_HEADER * fHtRatio);
	arDef.first_string = makeint(TW_DEF_FIRSTSTRING * fHtRatio);
	arDef.interval = makeint(TW_DEF_INTERVAL * fHtRatio);
	arDef.counter_offset = makeint(TW_DEF_COUNTERVOFFSET * fHtRatio);
	arDef.mark_offset = makeint(TW_DEF_MARKOFFSET * fHtRatio);
	arDef.bottom_space = makeint(TW_DEF_BOTTOMSPACE * fHtRatio);
	
	// размеры картинок
	arDef.caption = makeint(TW_DEF_CAPTIONHEIGHT * fHtRatio);
	arDef.mark = makeint(TW_DEF_MARKSIZE * fHtRatio);
	arDef.line = makeint(TW_DEF_LINEHEIGHT * fHtRatio);
	
	// отступы слева и справа
	arDef.indent = makeint(TW_DEF_INDENT * fHtRatio);
}

// Вычислить корректные координаты (каждый раз при открытии)
// TO_DO: Можно и реже по другим условиям
void TW_RecalculateLayout()
{
    int  i, num;
    aref arNode, arTask, arTexts;
    string sTask = objTask.current;
	
	float fHtRatio = stf(Render.screen_y) / iHudScale;
	
	makearef(arTask, objTask.(sTask));
    makearef(arTexts, objTask.(sTask).texts);
    num = GetAttributesNum(arTexts);
    for(i=0; i<num; i++)
    {
        arNode = GetAttributeN(arTexts, i);
        arNode.pos.y = sti(objTask.defines.top) + makeint(sti(arNode.base.pos.y) * fHtRatio);
        if(CheckAttribute(arNode, "base.scale"))
            arNode.scale = stf(arNode.base.scale) * fHtRatio;
		else
			arNode.scale = fHtRatio;
    }

/*
    TO_DO: Когда будут ещё картинки, их тоже нужно подгонять по x

    makearef(arTask, objTask.(sTask).images);
    num = GetAttributesNum(arTask);
    for(i=0; i<num; i++)
    {
        arNode = GetAttributeN(arTask, i);

        if(arImage.picture == "background") continue;

        if(CheckAttribute(arNode, "pos"))
        {
            // Уже было выставлено, адаптируем текущие
            
        }
        else
        {
            arNode.pos = arNode.base.pos.x1 + "," +
                         arNode.base.pos.y1 + "," +
                         arNode.base.pos.x2 + "," +
                         arNode.base.pos.y2;
        }
    }
*/

    // Установить размер подложки и раздать всем x-координаты
    TW_SetBack();
    
    if(bSeaActive && !bAbordageStarted)
        SendMessage(&BattleInterface , "lla", BI_MSG_TUTORIAL_SHOW, true, arTask);
    else
        SendMessage(&objLandInterface, "lla", BI_MSG_TUTORIAL_SHOW, true, arTask);

    // Обновить инфу по контролкам
	ControlsDesc();
}

// TO_DO: RECALCULATE
void TW_SetBack()
{
    int iTemp;
    int width  = 0;
    int height = 0;
    float scale;
	float fHtRatio = stf(Render.screen_y) / iHudScale;

    aref arTextRoot, arText, arImage, arDef, arTask;
    string sTask = objTask.current;
	makearef(arTask, objTask.(sTask));
    makearef(arTextRoot, arTask.texts);
    makearef(arImage, arTask.images.background);
	makearef(arDef, objTask.defines);
	arImage.group   = "TUTORIAL_BACK1";
    arImage.picture = "background";
	
	int base_x1, base_y1, base_x2, base_y2;
	base_x1 = sti(arDef.left);
	base_y1 = sti(arDef.top);
	
	int x1, y1, x2, y2;

    // Pre-calculated values
    bool bFixW = CheckAttribute(arTask, "fixWidth");
    bool bFixH = CheckAttribute(arTask, "fixHeight");

	int maxY = 0;
	int num = GetAttributesNum(arTextRoot);
	int i;
    // Dynamic values
    if(!bFixW)
    {
        // Get max text width
        for(i=0; i<num; i++)
        {
            arText = GetAttributeN(arTextRoot, i);
            scale  = 1.0;
            if(CheckAttribute(arText, "scale")) 
				scale = stf(arText.scale);
            iTemp = GetStringWidth(arText.text, arText.font, scale);
            if(iTemp > width)
				width = iTemp;
        }
    }
	if(!bFixH)
	{
		// Get max text height
		for(i=0; i<num; i++)
        {
            arText = GetAttributeN(arTextRoot, i);
            iTemp = sti(arText.pos.y);
            if(iTemp > maxY)
				maxY = iTemp;
        }
	}
	
	if(bFixW)
		width = TW_GetFixWidth(arTask);
	
	height = maxY - base_y1;

	base_x2 = base_x1 + width + sti(arDef.indent) * 2;
	int center = base_x1 + (base_x2 - base_x1) / 2;

    if(bFixH)
        base_y2 = base_y1 + sti(objTask.(sTask).fixHeight);
    else
        base_y2 = base_y1 + height + sti(arDef.bottom_space);
	
	if(base_x2 - base_x1 > sti(arDef.first_string) + sti(arDef.interval) + sti(arDef.bottom_space))
		arImage.group = "TUTORIAL_BACK2";

    arImage.pos = GetPosString(base_x1, base_y1, base_x2, base_y2);
	
	// caption - полоска сверху
	makearef(arImage, objTask.(sTask).images.back_caption);
	arImage.group = "LE_ICONS";
    arImage.picture = "captionback";
	x1 = base_x1;
	x2 = base_x2;
	y1 = base_y1;
	y2 = base_y1 + sti(arDef.caption);
	arImage.pos = GetPosString(x1, y1, x2, y2);
	
	// line - черта
	makearef(arImage, objTask.(sTask).images.back_line);
	arImage.group = "LE_ICONS";
    arImage.picture = "gline_hs";
	x1 = base_x1;
	x2 = base_x2;
	y1 = base_y1 + sti(arDef.caption);
	y2 = base_y1 + sti(arDef.caption) + sti(arDef.line);
	arImage.pos = GetPosString(x1, y1, x2, y2);
	
	// exclamation - восклицательный знак
	makearef(arImage, objTask.(sTask).images.back_mark);
	arImage.group = "MARKERS";
    arImage.picture = "exclamation";
	x1 = center - sti(arDef.mark) / 2;
	x2 = center + sti(arDef.mark) / 2;
	y1 = base_y1 - sti(arDef.mark) + sti(arDef.mark_offset);
	y2 = base_y1 + sti(arDef.mark_offset);
	arImage.pos = GetPosString(x1, y1, x2, y2);
	
	string sAlign;
    for(i=0; i<num; i++)
    {
        arText = GetAttributeN(arTextRoot, i);
		sAlign = "left";
        if(CheckAttribute(arText, "align"))
			sAlign = arText.align;
		
		switch(sAlign)
		{
			case "left":	
				arText.pos.x = base_x1 + sti(arDef.indent);
				break;
			case "center":
				arText.pos.x = center;
				break;
			case "right":
				arText.pos.x = base_x2 - sti(arDef.indent);
				break;
		}
	}
}

// Открыть требуемый таск
void TW_Open(string attr)
{
    objTask.current = attr;
    TW_RecalculateLayout();
    DeleteAttribute(&objTask, "Stop");

    // Метод для анимаций
    // aref arTask;
    // makearef(arTask, objTask.(attr));
    // Event("TW_Update", "a", arTask);
}

// Временно закрыть окно, приостановить обработчики
// Когда таск ещё не окончен, но выключается BI/LI
void TW_Close()
{
    if(!bGlobalTutor || CheckAttribute(&objTask, "Stop")) return;

    objTask.Stop = "";
    if(bSeaActive && !bAbordageStarted)
        SendMessage(&BattleInterface , "ll", BI_MSG_TUTORIAL_SHOW, false);
    else
        SendMessage(&objLandInterface, "ll", BI_MSG_TUTORIAL_SHOW, false);

    // Обновить инфу по контролкам
	ControlsDesc();
}

// Заново открыть текущий таск
// Когда снова включается BI/LI, таск продолжается
void TW_Init()
{
	TW_SetDefines();
    if(!TW_IsActive()) return;
    TW_Open(objTask.current);
}

// Завершить текущий таск
#event_handler("TW_Release", "TW_Release");
void TW_Release()
{
    DeleteAttribute(&objTask, "current");
    TW_Close();
}

// Проверки в скриптах
bool TW_IsActive()
{
    return bGlobalTutor && CheckAttribute(&objTask, "current");
}

// Процессирование
#event_handler("TW_Update", "TW_Update");
void TW_Update()
{
    if(CheckAttribute(&objTask, "Stop")) return;

    aref  arTask = GetEventData();
    float dltTime = GetRealDeltaTime();

    if(CheckAttribute(arTask, "handlers"))
    {
        aref arHand;
        string func;
        makearef(arHand, arTask.handlers);
        int num = GetAttributesNum(arHand);
        for(int i=0; i<num; i++)
        {
            func = GetAttributeName(GetAttributeN(arHand, i));
            call func(arTask, dltTime);
        }
    }

    PostEvent("TW_Update", 0, "a", arTask);
}

// Сбросить временные атрибуты, мгновенно закончить анимации
void TW_Refresh()
{

}

// Удалить все ноды, кроме подложки
void TW_Reset(aref arTask)
{
    DeleteAttribute(arTask, "texts");
  //DeleteAttribute(arTask, "images");
    DeleteAttribute(arTask, "counters");
    DeleteAttribute(arTask, "percents");
  //DeleteAttribute(arTask, "lines");
    DeleteAttribute(arTask, "fixWidth");
    DeleteAttribute(arTask, "fixHeight");
    DeleteAttribute(arTask, "bottom");
}

////////////////////////////////////////////////////////////////////////
//  TEXT COLORS
////////////////////////////////////////////////////////////////////////

void TW_ColorDefault(aref arText) {arText.color = argb(255, 255, 255, 255);}
void TW_ColorHead(aref arText)    {arText.color = argb(255, 240, 175, 95);}
void TW_ColorDone(aref arText)    {arText.color = argb(255, 128, 220, 128);}
void TW_ColorWeak(aref arText)    {arText.color = argb(200, 200, 200, 200);}

////////////////////////////////////////////////////////////////////////
//  HANDLERS
////////////////////////////////////////////////////////////////////////

// Счётчики
bool TW_IncreaseCounter(string sTask, string sParent, int add)
{
    aref arCnt;
    sParent += "_cnt";
    makearef(arCnt, objTask.(sTask).texts.(sParent));
    if(arCnt.end == "1") return false;
	
	if(abs(add) > 0)
		TW_RestartTimer();

    arCnt.count = sti(arCnt.count) + add;
    if(sti(arCnt.count) >= sti(arCnt.max))
    {
        arCnt.text = arCnt.max + "/" + arCnt.max;
        arCnt.count = arCnt.max;
        arCnt.end = "1";
        TW_ColorDone(arCnt);

        sParent = arCnt.parent;
        makearef(arCnt, objTask.(sTask).texts.(sParent));
        TW_ColorWeak(arCnt);
        return true;
    }

    arCnt.text = arCnt.count + "/" + arCnt.max;
    return false;
}

bool TW_CheckCounter(string sTask, string sParent)
{
	aref arCnt;
    sParent += "_cnt";
    makearef(arCnt, objTask.(sTask).texts.(sParent));
    if(CheckAttribute(arCnt, "end") && arCnt.end == "1")
		return true;
	return false;
}

// Проценты
bool TW_IncreasePercents(string sTask, string sParent, float add)
{
    aref arCnt;
    sParent += "_percents";
    makearef(arCnt, objTask.(sTask).texts.(sParent));
    if(arCnt.end == "1") return false;
	
	if(abs(add) > 0.0)
		TW_RestartTimer();

    arCnt.count = stf(arCnt.count) + add;
    if(stf(arCnt.count) >= stf(arCnt.max))
    {
        arCnt.text = "100%";
        arCnt.count = arCnt.max;
        arCnt.end = "1";
        TW_ColorDone(arCnt);

        sParent = arCnt.parent;
        makearef(arCnt, objTask.(sTask).texts.(sParent));
        TW_ColorWeak(arCnt);
        return true;
    }

    arCnt.text = MakeInt(stf(arCnt.count) / stf(arCnt.max) * 100.0) + "%";
    return false;
}

// Индикатор выполнения (полоска)
void TW_IncreaseLine(string sTask, string sParent, float add)
{

}

void TW_SetTaskTimer(aref arTask, string sTask)
{
	if(!CheckAttribute(arTask, "timer"))
		PostEvent("TW_RefreshTimer", 1000);
	arTask.timer = TW_TASK_TIMER;
	arTask.timer.task = sTask;
}

#event_handler("TW_RefreshTimer", "TW_RefreshTimer");
void TW_RefreshTimer()
{
	string sTask = objTask.current;
	aref arTask;
	makearef(arTask, objTask.(sTask));
	if(!CheckAttribute(arTask, "timer"))
		return;
	int iCurTimer = sti(arTask.timer);
	Log_TestInfo("Таймер задачи " + GetAttributeValue(arTask) + " из раздела " + GetAttributeName(arTask) + ": " + iCurTimer);
	iCurTimer--;
	if(iCurTimer <= 0)
	{
		if(!CheckAttribute(arTask, "timer.task"))
			return;
		string sFinishTask = arTask.timer.task;
		DeleteAttribute(arTask, "timer");
		string sFunction = "TW_Finish" + GetAttributeName(arTask) + "_" + sFinishTask;
		call sFunction();
		return;
	}
	arTask.timer = iCurTimer;
	float timeScale = 1 + TimeScaleCounter * 0.25;
	PostEvent("TW_RefreshTimer", makeint(1000 * timeScale));
}

void TW_RestartTimer()
{
	string sTask = objTask.current;
	objTask.(sTask).timer = TW_TASK_TIMER;
}

void TW_DeleteTimer()
{
	string sTask = objTask.current;
	if(CheckAttribute(&objTask, sTask + ".timer"))
		DeleteAttribute(&objTask, sTask + ".timer");
}

////////////////////////////////////////////////////////////////////////
//  TEXT
////////////////////////////////////////////////////////////////////////

aref TW_GetTextARef(string sText)
{
    aref arText;
    string sTask = objTask.current;
    makearef(arText, objTask.(sTask).texts.(sText));
    return arText;
}

void TW_AddBottomText(string curText, string Text, string Color)
{
    aref arText, arTextUp;
    string sTask = objTask.current;
    makearef(arText, objTask.(sTask).texts.(curText));

    arTextUp = TW_GetBottom(sTask);
    arText.font = arTextUp.font;
    arText.base.pos.y = sti(arTextUp.base.pos.y) + TW_DEF_INTERVAL;
    arText.base.scale = arTextUp.base.scale;
    arText.text = Text;
    TW_MarkBottom(sTask, curText);

    Color = "TW_Color" + Color;
    call Color(arText);
	
	if(CheckAttribute(&objTask, sTask + ".timer"))
		TW_RestartTimer();
}

void TW_MarkBottom(string sTask, string sText)
{
    aref arTask, arText;
    makearef(arTask, objTask.(sTask));
    arTask.bottom = sText;
}

aref TW_GetBottom(string sTask)
{
    string sText;
    aref arTask, arText;
    makearef(arTask, objTask.(sTask));

    if(CheckAttribute(arTask, "bottom"))
    {
        sText = arTask.bottom;
        makearef(arText, arTask.texts.(sText));
        return arText;
    }
    else
    {
        aref arTextRoot, arBottom;
        makearef(arTextRoot, arTask.texts);
        int curH, height = 0;
        int num = GetAttributesNum(arTextRoot);
        for(int i = num-1; i>=0; i--)
        {
            arText = GetAttributeN(arTextRoot, i);
            curH = sti(arText.base.pos.y);
            if(curH > height)
            {
                makearef(arBottom, arText);
                height = curH;
            }
        }
        TW_MarkBottom(sTask, GetAttributeName(arBottom));
        return arBottom;
    }

    Log_TestInfo("objTask." + sTask + " has no texts");
    return ErrorAttr();
}

int TW_GetFixWidth(aref arTask)
{
    aref arText, arBase;
	makearef(arBase, arTask.base_text);
    int iTemp =0;
	int widthL = 0;
	int	widthR = 0;
    float scale;
	float fHtRatio = stf(Render.screen_y) / iHudScale;
    int num = GetAttributesNum(arBase);
    for(int i=0; i<num; i++)
    {
        arText = GetAttributeN(arBase, i);
        scale  = fHtRatio;
        if(CheckAttribute(arText, "scale"))
			scale = stf(arText.scale) * fHtRatio;
        iTemp = GetStringWidth(arText.text, arText.font, scale);
		if(!CheckAttribute(arText, "align") || arText.align == "left")
		{
			if(iTemp > widthL)
				widthL = iTemp;
		}
		else if(arText.align == "right")
		{
			if(iTemp > widthR)
				widthR = iTemp;
		}
    }
	if(widthR > 0)
		return widthL + sti(objTask.defines.indent) + widthR;
	
	return widthL;
}

// TW_GetKeyImageChar
string GKIC(string controlName, string groupName)
{
    if(!CheckAttribute(&objControlsState, "keygroups." + groupName + "." + controlName))
        return "NONE";

    string KeyName = objControlsState.keygroups.(groupName).(controlName);
    if(KeyName == "") return "NONE";
	if(CheckAttribute(&objControlsState, "keygroups.AltPressedGroup." + controlName))
		return objControlsState.key_codes.vk_menu.img + objControlsState.key_codes.(KeyName).img;
    return objControlsState.key_codes.(KeyName).img;
}

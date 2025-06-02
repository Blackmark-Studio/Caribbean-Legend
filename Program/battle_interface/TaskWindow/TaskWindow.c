
#include "battle_interface\TaskWindow\TW_init.c"

object objTask;

////////////////////////////////////////////////////////////////////////
//  TASK WINDOW
////////////////////////////////////////////////////////////////////////

// Вычислить корректные координаты (каждый раз при открытии)
// TO_DO: Можно и реже по другим условиям
void TW_RecalculateLayout()
{
    int  i, num;
    aref arNode, arTask;
    string sTask = objTask.current;

    makearef(arTask, objTask.(sTask).texts);
    num = GetAttributesNum(arTask);
    for(i=0; i<num; i++)
    {
        arNode = GetAttributeN(arTask, i);
        if(CheckAttribute(arNode, "pos"))
        {
            // Уже было выставлено, адаптируем текущие
            
        }
        else
        {
            // TO_DO: RECALCULATE
            arNode.pos.y = arNode.base.pos.y;
            if(CheckAttribute(arNode, "base.scale"))
                arNode.scale = arNode.base.scale;
        }
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

    makearef(arTask, objTask.(sTask));
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

    aref arTextRoot, arText, arImage;
    string sTask = objTask.current;
    makearef(arTextRoot, objTask.(sTask).texts);
    makearef(arImage, objTask.(sTask).images.background);

    // Default values (TO_DO: RECALCULATE)
    arImage.x2 = 1900; // Правый край
    arImage.y1 = 300;  // Верхний край

    // Pre-calculated values
    bool bFixW = CheckAttribute(&objTask, sTask + ".fixWidth");
    bool bFixH = CheckAttribute(&objTask, sTask + ".fixHeight");

    // Dynamic values
    if(!bFixW || !bFixH)
    {
        // Get max text width and max height
        int num = GetAttributesNum(arTextRoot);
        for(int i=0; i<num; i++)
        {
            arText = GetAttributeN(arTextRoot, i);
            scale  = 1.0;
            if(CheckAttribute(arText, "scale")) scale = stf(arText.scale);
            iTemp = GetStringWidth(arText.text, arText.font, scale);
            if(iTemp > width) width = iTemp;
            iTemp = sti(arText.pos.y);
            if(iTemp > height) height = iTemp;
        }
    }

    // TO_DO: RECALCULATE
    if(bFixW)
        arImage.x1 = objTask.(sTask).fixWidth;
    else
        arImage.x1 = 1900 - width - 200; // Левый край (отступ от правого и 200 в запас)

    if(bFixH)
        arImage.y2 = objTask.(sTask).fixHeight;
    else
        arImage.y2 = height + 50; // Нижний край (отступ от верха и 50 в запас)

    arImage.pos = arImage.x1 + "," +
                  arImage.y1 + "," +
                  arImage.x2 + "," +
                  arImage.y2;

    width = sti(arImage.x1);
    iTemp = width + (1900 - width) / 2;
    width += 70; // Добавим отступ
    for(i=0; i<num; i++)
    {
        // TO_DO: align == "right" (не нужно пока)
        arText = GetAttributeN(arTextRoot, i);
        if(CheckAttribute(arText, "align") && arText.align == "center")
            arText.pos.x = iTemp;
        else
            arText.pos.x = width;
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
void TW_ColorHead(aref arText)    {arText.color = argb(255, 255, 255, 192);}
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

// Проценты
bool TW_IncreasePercents(string sTask, string sParent, float add)
{
    aref arCnt;
    sParent += "_percents";
    makearef(arCnt, objTask.(sTask).texts.(sParent));
    if(arCnt.end == "1") return false;

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

void TW_AddBottomText(string curText, string Text, string Color, int OffSet)
{
    aref arText, arTextUp;
    string sTask = objTask.current;
    makearef(arText, objTask.(sTask).texts.(curText));

    arTextUp = TW_GetBottom(sTask);
    arText.font = arTextUp.font;
    arText.base.pos.y = sti(arTextUp.base.pos.y) + OffSet;
    arText.base.scale = arTextUp.base.scale;
    arText.text = Text;
    TW_MarkBottom(sTask, curText);

    Color = "TW_Color" + Color;
    call Color(arText);
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

    Log_Info("objTask." + sTask + " has no texts");
    return ErrorAttr();
}

void TW_SetFixWidth(aref arTask, ref Root)
{
    aref arText;
    int iTemp, width = 0;
    float scale;

    int num = GetAttributesNum(Root);
    for(int i=0; i<num; i++)
    {
        arText = GetAttributeN(Root, i);
        scale  = 1.0;
        if(CheckAttribute(arText, "scale")) scale = stf(arText.scale);
        iTemp = GetStringWidth(arText.text, arText.font, scale);
        if(iTemp > width) width = iTemp;
    }

    arTask.fixWidth = 1900 - width - 200;
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

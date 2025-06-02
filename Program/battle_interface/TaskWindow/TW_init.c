
#define TW_DEF_HEADER   315
#define TW_DEF_INTERVAL 40

/*  Параметры для картинок:
    - .technique
    - .priority (по умолчанию 10k)
    - .color    (argb)
    - .pos      (по умолчанию для FullHD)
    - Через battle_interface.ini
        - .group
        - .picture
    - Без ini
        - .texture
        - .uv

    Параметры для текста:
    - .font
    - .scale (по умолчанию 1.0)
    - .color (argb)
    - .align (по умолчанию left)
    - .pos.x (переопределяется по максимальной ширине)
    - .pos.y (по умолчанию для FullHD)
    - .text

    Остальное скриптовое */

////////////////////////////////////////////////////////////////////////
//  HANDLERS
////////////////////////////////////////////////////////////////////////

// Счётчики
aref TW_SetTextCounter(string sTask, string sTarget, int max, bool bCopy)
{
    aref   arCnt, arTask, arText;
    string sName = sTarget + "_cnt";
    makearef(arTask, objTask.(sTask));
    makearef(arCnt,  arTask.texts.(sName));
    makearef(arText, arTask.texts.(sTarget));

    arCnt.text  = "";
    if(bCopy)
    {
        arCnt.font  = arText.font;
        arCnt.color = arText.color;
        arCnt.base.pos.y = arText.base.pos.y;
        if(CheckAttribute(arText, "base.scale"))
            arCnt.base.scale = arText.base.scale;
    }

    // Скриптовое:
    arCnt.end    = 0;
    arCnt.count  = 0;
    arCnt.max    = max;
    arCnt.parent = sTarget;
    arTask.counters.(sName) = "";

    return arCnt;
}

// Проценты
aref TW_SetPercentCounter(string sTask, string sTarget, float max, bool bCopy)
{
    aref   arCnt, arTask, arText;
    string sName = sTarget + "_percents";
    makearef(arTask, objTask.(sTask));
    makearef(arCnt,  arTask.texts.(sName));
    makearef(arText, arTask.texts.(sTarget));

    arCnt.text  = "0%";
    if(bCopy)
    {
        arCnt.font  = arText.font;
        arCnt.color = arText.color;
        arCnt.base.pos.y = arText.base.pos.y;
        if(CheckAttribute(arText, "base.scale"))
            arCnt.base.scale = arText.base.scale;
    }

    // Скриптовое:
    arCnt.end    = 0;
    arCnt.count  = 0.0;
    arCnt.max    = max;
    arCnt.parent = sTarget;
    arTask.percents.(sName) = "";

    return arCnt;
}

////////////////////////////////////////////////////////////////////////
//  TUTORIALS
////////////////////////////////////////////////////////////////////////

// Обучение атаке
void TW_InitLand_1_Attack()
{
    aref arTask, arImage, arText;

    objTask.land = "1_Attack";
    makearef(arTask, objTask.land);

    // Параметры
    //

    // Подложка
    makearef(arImage, arTask.images.background);
    arImage.group   = "TUTORIAL_BACK";
    arImage.picture = "background";

    // Текст
    //

    // Обработчики
    //
}

// Основы управления кораблём - Поворот
void TW_InitSea_1_Turn()
{
    aref arTask, arImage, arText;

    objTask.sea = "1_Turn";
    makearef(arTask, objTask.sea);

    // Параметры
    //

    // Подложка
    makearef(arImage, arTask.images.background);
    arImage.group   = "TUTORIAL_BACK";
    arImage.picture = "background";

    // Текст
    makearef(arText, arTask.texts.turn_head);
    arText.font  = "interface_normal_bold";
    arText.base.pos.y = TW_DEF_HEADER;
    arText.text  = StringFromKey("Tutorial_1");
    arText.align = "center";
    TW_ColorHead(arText);

    makearef(arText, arTask.texts.turn_text);
    arText.font  = "interface_normalpcb";
    arText.base.pos.y = 355;
    arText.base.scale = 1.5;
    arText.text  = StringFromKey("Tutorial_2", GKIC("Ship_TurnLeft", "Sailing3Pers"), GKIC("Ship_TurnRight", "Sailing3Pers"));
    arText.align = "center";
    TW_ColorDefault(arText);

    arText = TW_SetPercentCounter("sea", "turn_text", PI*0.5, false);
    arText.font  = "interface_normal_bold";
    arText.base.pos.y = 395;
    arText.base.scale = 1.0;
    arText.align = "center";
    TW_ColorDefault(arText);

    // Обработчики
    //
}

// Основы управления кораблём - Ускорение времени
void TW_InitSea_2_TimeScale(string qName)
{
    aref arTask, arImage, arText;

    objTask.sea = "2_TimeScale";
    makearef(arTask, objTask.sea);
    TW_Reset(arTask);

    // Параметры
    object objTemp;
    objTemp.t0.text  = StringFromKey("Tutorial_3");
    objTemp.t0.font  = "interface_normal_bold";
    objTemp.t1.text  = StringFromKey("Tutorial_4", GKIC("TimeScale", "Sailing3Pers"));
    objTemp.t1.font  = "interface_normalpcb";
    objTemp.t1.scale = 1.5;
    objTemp.t2.text  = StringFromKey("Tutorial_5", GKIC("TimeScale", "Sailing3Pers"));
    objTemp.t2.font  = "interface_normalpcb";
    objTemp.t2.scale = 1.5;
    objTemp.t3.text  = StringFromKey("Tutorial_6", GKIC("TimeScaleFasterBA", "Sailing3Pers"));
    objTemp.t3.font  = "interface_normalpcb";
    objTemp.t3.scale = 1.5;
    objTemp.t4.text  = StringFromKey("Tutorial_7", GKIC("TimeScaleFasterBA", "Sailing3Pers"), GKIC("TimeScale", "Sailing3Pers"));
    objTemp.t4.font  = "interface_normalpcb";
    objTemp.t4.scale = 1.5;
    TW_SetFixWidth(arTask, &objTemp);

    // Подложка
    //

    // Текст
    makearef(arText, arTask.texts.TimeScale_head);
    arText.font  = "interface_normal_bold";
    arText.base.pos.y = TW_DEF_HEADER;
    arText.text  = StringFromKey("Tutorial_3");
    arText.align = "center";
    TW_ColorHead(arText);

    makearef(arText, arTask.texts.TimeScale_R_on);
    arText.font  = "interface_normalpcb";
    arText.base.pos.y = 355;
    arText.base.scale = 1.5;
    arText.text  = StringFromKey("Tutorial_4", GKIC("TimeScale", "Sailing3Pers"));
    TW_ColorDefault(arText);
    TW_MarkBottom("sea", "TimeScale_R_on");

    // Обработчики
    //

    TW_RecalculateLayout();
}

// Основы управления кораблём - Паруса
void TW_InitSea_3_Sails(string qName)
{
    aref arTask, arImage, arText;

    objTask.sea = "3_Sails";
    makearef(arTask, objTask.sea);
    TW_Reset(arTask);

    // Параметры
    object objTemp;
    objTemp.t0.text  = StringFromKey("Tutorial_8");
    objTemp.t0.font  = "interface_normal_bold";
    objTemp.t1.text  = StringFromKey("Tutorial_9");
    objTemp.t1.font  = "interface_normalpcb";
    objTemp.t1.scale = 1.5;
    objTemp.t2.text  = StringFromKey("Tutorial_10");
    objTemp.t2.font  = "interface_normalpcb";
    objTemp.t2.scale = 1.5;
    TW_SetFixWidth(arTask, &objTemp);

    // Подложка
    //

    // Текст
    makearef(arText, arTask.texts.Sails_head);
    arText.font  = "interface_normal_bold";
    arText.base.pos.y = TW_DEF_HEADER;
    arText.text  = StringFromKey("Tutorial_8");
    arText.align = "center";
    TW_ColorHead(arText);

    makearef(arText, arTask.texts.Battle_Sails);
    arText.font  = "interface_normalpcb";
    arText.base.pos.y = 355;
    arText.base.scale = 1.5;
    arText.text  = StringFromKey("Tutorial_9");
    TW_ColorDefault(arText);
    TW_MarkBottom("sea", "Battle_Sails");

    // Обработчики
    //

    TW_RecalculateLayout();
}

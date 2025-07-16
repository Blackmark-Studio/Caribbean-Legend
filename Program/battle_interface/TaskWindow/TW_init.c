#define TW_DEF_HEADER   		6		// расстояние от основной точки до текста заголовка
#define TW_DEF_FIRSTSTRING 		60		// расстояние от основной точки до первой строки
#define TW_DEF_INTERVAL 		35		// расстояние между строками
#define TW_DEF_COUNTERVOFFSET 	4		// сдвиг для выравнивания правого столбца с другим размером текста
#define TW_DEF_BOTTOMSPACE		50		// расстояние между последней строкой и низом задника

#define TW_DEF_CAPTIONHEIGHT 	40		// толщина полосы для заголовка
#define TW_DEF_MARKSIZE 		50		// размер восклицательного знака
#define TW_DEF_MARKOFFSET 		12		// сдвиг восклицательного знака
#define TW_DEF_LINEHEIGHT 		2		// толщина линии под заголовком

#define TW_DEF_INDENT 			30		// стандартный отступ

#define TW_DEF_HEADER_SCALE		0.85
#define TW_DEF_STRING_SCALE		1.4
#define TW_DEF_COUNTER_SCALE	1.5

#define TW_TASK_TIMER			40

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
	
	arCnt.text  = "0/" + max;
	
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

// Основы управления кораблём - Поворот
void TW_InitSea_1_Turn()
{
    aref arTask, arImage, arText, arDef;
	makearef(arDef, objTask.defines);

    objTask.sea = "1_Turn";
    makearef(arTask, objTask.sea);

    // Параметры
    //

    // Подложка

    // Текст
    makearef(arText, arTask.texts.turn_head);
    arText.font  = "interface_normal_bold";
    arText.base.pos.y = TW_DEF_HEADER;
	arText.base.scale = TW_DEF_HEADER_SCALE;
    arText.text  = StringFromKey("Tutorial_1");
    arText.align = "center";
    TW_ColorHead(arText);

    makearef(arText, arTask.texts.turn_text);
    arText.font  = "interface_normalpcb";
    arText.base.pos.y = TW_DEF_FIRSTSTRING;
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.text  = StringFromKey("Tutorial_2", GKIC("Ship_TurnLeft", "Sailing3Pers"), GKIC("Ship_TurnRight", "Sailing3Pers"));
    arText.align = "center";
    TW_ColorDefault(arText);

    arText = TW_SetPercentCounter("sea", "turn_text", PI*0.5, false);
    arText.font  = "interface_normal_bold";
    arText.base.pos.y = TW_DEF_FIRSTSTRING + TW_DEF_INTERVAL;
    arText.base.scale = TW_DEF_HEADER_SCALE;
    arText.align = "center";
    TW_ColorDefault(arText);

    // Обработчики
    //
	TW_SetTaskTimer(arTask, "1_Turn");
}

void TW_FinishSea_1_Turn()
{
	objTask.sea = "";
	if(CheckAttribute(&TEV, "Tutor.BackAY"))
		DeleteAttribute(&TEV, "Tutor.BackAY");
	DoQuestFunctionDelay("Tutorial_TimeScale", 1.5);
    DoQuestFunctionDelay("TW_InitSea_2_TimeScale", 2.5);
}

// Основы управления кораблём - Ускорение времени
void TW_InitSea_2_TimeScale(string qName)
{
    aref arTask, arImage, arText, arDef;
	makearef(arDef, objTask.defines);

    objTask.sea = "2_TimeScale";
    makearef(arTask, objTask.sea);
    TW_Reset(arTask);

    // Параметры
    aref arBase;
	if(CheckAttribute(arTask, "base_text"))
		DeleteAttribute(arTask, "base_text");
	makearef(arBase, arTask.base_text);
    arBase.t0.text  = StringFromKey("Tutorial_3");
    arBase.t0.font  = "interface_normal_bold";
	arBase.t0.scale = TW_DEF_HEADER_SCALE;
    arBase.t1.text  = StringFromKey("Tutorial_4", GKIC("TimeScale", "Sailing3Pers"));
    arBase.t1.font  = "interface_normalpcb";
    arBase.t1.scale = TW_DEF_STRING_SCALE;
    arBase.t2.text  = StringFromKey("Tutorial_5", GKIC("TimeScale", "Sailing3Pers"));
    arBase.t2.font  = "interface_normalpcb";
    arBase.t2.scale = TW_DEF_STRING_SCALE;
    arBase.t3.text  = StringFromKey("Tutorial_6", GKIC("TimeScaleFasterBA", "Sailing3Pers"));
    arBase.t3.font  = "interface_normalpcb";
    arBase.t3.scale = TW_DEF_STRING_SCALE;
    arBase.t4.text  = StringFromKey("Tutorial_7", GKIC("TimeScaleSlowerBA", "Sailing3Pers"), GKIC("TimeScale", "Sailing3Pers"));
    arBase.t4.font  = "interface_normalpcb";
    arBase.t4.scale = TW_DEF_STRING_SCALE;
    arTask.fixWidth = true;

    // Подложка
    //

    // Текст
    makearef(arText, arTask.texts.TimeScale_head);
    arText.font  = "interface_normal_bold";
    arText.base.pos.y = TW_DEF_HEADER;
	arText.base.scale = TW_DEF_HEADER_SCALE;
    arText.text  = StringFromKey("Tutorial_3");
    arText.align = "center";
    TW_ColorHead(arText);

    makearef(arText, arTask.texts.TimeScale_R_on);
    arText.font  = "interface_normalpcb";
    arText.base.pos.y = TW_DEF_FIRSTSTRING;
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.text  = StringFromKey("Tutorial_4", GKIC("TimeScale", "Sailing3Pers"));
    TW_ColorDefault(arText);
    TW_MarkBottom("sea", "TimeScale_R_on");

    // Обработчики
    //
	TW_SetTaskTimer(arTask, "2_TimeScale");

    TW_RecalculateLayout();
}

void TW_FinishSea_2_TimeScale()
{
	objTask.sea = "";
	DoQuestFunctionDelay("TW_InitSea_3_Sails", 2.0);
}

// Основы управления кораблём - Паруса
void TW_InitSea_3_Sails(string qName)
{
    aref arTask, arImage, arText, arDef;
	makearef(arDef, objTask.defines);

    objTask.sea = "3_Sails";
    makearef(arTask, objTask.sea);
    TW_Reset(arTask);

    // Параметры
    aref arBase;
	if(CheckAttribute(arTask, "base_text"))
		DeleteAttribute(arTask, "base_text");
	makearef(arBase, arTask.base_text);
    arBase.t0.text  = StringFromKey("Tutorial_8");
    arBase.t0.font  = "interface_normal_bold";
	arBase.t0.scale = TW_DEF_HEADER_SCALE;
    arBase.t1.text  = StringFromKey("Tutorial_9", GKIC("Ship_SailDown", "Sailing3Pers"));//, GKIC("Ship_SailUp", "Sailing3Pers"));
    arBase.t1.font  = "interface_normalpcb";
    arBase.t1.scale = TW_DEF_STRING_SCALE;
    arBase.t2.text  = StringFromKey("Tutorial_10", GKIC("Ship_SailDown", "Sailing3Pers"));
    arBase.t2.font  = "interface_normalpcb";
    arBase.t2.scale = TW_DEF_STRING_SCALE;
    arTask.fixWidth = true;

    // Подложка
    //

    // Текст
    makearef(arText, arTask.texts.Sails_head);
    arText.font  = "interface_normal_bold";
    arText.base.pos.y = TW_DEF_HEADER;
	arText.base.scale = TW_DEF_HEADER_SCALE;
    arText.text  = StringFromKey("Tutorial_8");
    arText.align = "center";
    TW_ColorHead(arText);

    makearef(arText, arTask.texts.Battle_Sails);
    arText.font  = "interface_normalpcb";
    arText.base.pos.y = TW_DEF_FIRSTSTRING;
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.text  = StringFromKey("Tutorial_9", GKIC("Ship_SailDown", "Sailing3Pers"));//, GKIC("Ship_SailUp", "Sailing3Pers"));
    TW_ColorDefault(arText);
    TW_MarkBottom("sea", "Battle_Sails");

    // Обработчики
    //
	TW_SetTaskTimer(arTask, "3_Sails");

    TW_RecalculateLayout();
}

void TW_FinishSea_3_Sails()
{
	objTask.sea = "";
	TW_DeleteTimer();
	PostEvent("TW_Release", 3000);
	DoQuestFunctionDelay("SharlieTutorial_ActivateButtonInTheSea_1", 4.0);
	DeleteAttribute(&TEV, "Tutor.SailStateTimer");
}

void TW_InitSea_Battle_1_AutoFire()
{
	aref arTask, arImage, arText, arDef;
	makearef(arDef, objTask.defines);
	
	objTask.sea_battle = "1_AutoFire";
	makearef(arTask, objTask.sea_battle);
    TW_Reset(arTask);
	
	aref arBase;
	if(CheckAttribute(arTask, "base_text"))
		DeleteAttribute(arTask, "base_text");
	makearef(arBase, arTask.base_text);
    arBase.t0.text  = StringFromKey("Tutorial_11");
    arBase.t0.font  = "interface_normal_bold";
	arBase.t0.scale = TW_DEF_HEADER_SCALE;
    arBase.t1.text  = StringFromKey("Tutorial_12", GKIC("Ship_Fire", "Sailing3Pers"));
    arBase.t1.font  = "interface_normalpcb";
    arBase.t1.scale = TW_DEF_STRING_SCALE;
	arBase.t2.text  = "0/3";
	arBase.t2.font  = "interface_normalpcb";
    arBase.t2.scale = 2.0;
	arBase.t2.align = "right";
	arTask.fixWidth = true;
	
	makearef(arText, arTask.texts.AutoFire_head);
	arText.font  = "interface_normal_bold";
    arText.base.pos.y = TW_DEF_HEADER;
	arText.base.scale = TW_DEF_HEADER_SCALE;
    arText.text  = StringFromKey("Tutorial_11");
    arText.align = "center";
    TW_ColorHead(arText);
	
	makearef(arText, arTask.texts.AutoFire_do);
    arText.font  = "interface_normalpcb";
    arText.base.pos.y = TW_DEF_FIRSTSTRING;
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.text  = StringFromKey("Tutorial_12", GKIC("Ship_Fire", "Sailing3Pers"));
    TW_ColorDefault(arText);
    TW_MarkBottom("sea_battle", "AutoFire_do");
	
	arText = TW_SetTextCounter("sea_battle", "AutoFire_do", 3, false);
	arText.font  = "interface_normalpcb";
	arText.base.scale = 2.0;
    arText.base.pos.y = TW_DEF_FIRSTSTRING - TW_DEF_COUNTERVOFFSET;
    arText.align = "right";
	TW_ColorDefault(arText);
	
	TW_SetTaskTimer(arTask, "1_AutoFire");
	
//	TW_RecalculateLayout();
}

void TW_FinishSea_Battle_1_AutoFire()
{
	objTask.sea_battle = "";
	LaunchTutorial("Prologue_AimingFire", 1);
	DoQuestFunctionDelay("TW_InitSea_Battle_2_AimingFire", 1.5);
}

void TW_InitSea_Battle_2_AimingFire(string qName)
{	
	bCanSwitchCameras = true;
	
	aref arTask, arImage, arText, arDef;
	makearef(arDef, objTask.defines);
	
	objTask.sea_battle = "2_AimingFire";
	makearef(arTask, objTask.sea_battle);
    TW_Reset(arTask);
	
	aref arBase;
	if(CheckAttribute(arTask, "base_text"))
		DeleteAttribute(arTask, "base_text");
	makearef(arBase, arTask.base_text);
    arBase.t0.text  = StringFromKey("Tutorial_13");
    arBase.t0.font  = "interface_normal_bold";
	arBase.t0.scale = TW_DEF_HEADER_SCALE;
    arBase.t1.text  = StringFromKey("Tutorial_14", GKIC("FireCamera_Set", "Sailing3Pers"));
    arBase.t1.font  = "interface_normalpcb";
    arBase.t1.scale = TW_DEF_STRING_SCALE;
	arBase.t2.text  = StringFromKey("Tutorial_15", GKIC("Ship_Fire", "SailingFire"));
    arBase.t2.font  = "interface_normalpcb";
    arBase.t2.scale = TW_DEF_STRING_SCALE;
	arBase.t3.text  = StringFromKey("Tutorial_16", GKIC("FireCamera_Set", "SailingFire"));
    arBase.t3.font  = "interface_normalpcb";
    arBase.t3.scale = TW_DEF_STRING_SCALE;
	arTask.fixWidth = true;
	
	makearef(arImage, arTask.images.background);
    arImage.group   = "TUTORIAL_BACK";
    arImage.picture = "background";
	
	makearef(arText, arTask.texts.AimingFire_head);
	arText.font  = "interface_normal_bold";
    arText.base.pos.y = TW_DEF_HEADER;
	arText.base.scale = TW_DEF_HEADER_SCALE;
    arText.text  = StringFromKey("Tutorial_13");
    arText.align = "center";
    TW_ColorHead(arText);
	
	makearef(arText, arTask.texts.AimingFire_enter);
    arText.font  = "interface_normalpcb";
    arText.base.pos.y = TW_DEF_FIRSTSTRING;
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.text  = StringFromKey("Tutorial_14", GKIC("FireCamera_Set", "SailingFire"));
    TW_ColorDefault(arText);
    TW_MarkBottom("sea_battle", "AimingFire_enter");
	
	TW_SetTaskTimer(arTask, "2_AimingFire");
	
	TW_RecalculateLayout();
}

void TW_FinishSea_Battle_2_AimingFire()
{
	objTask.sea_battle = "";
	TW_DeleteTimer();
	DoQuestFunctionDelay("TW_InitSea_Battle_3_WinBattle", 2.0);
}

void TW_InitSea_Battle_3_WinBattle(string qName)
{
	aref arTask, arImage, arText, arDef;
	makearef(arDef, objTask.defines);
	
	objTask.sea_battle = "3_WinBattle";
	makearef(arTask, objTask.sea_battle);
    TW_Reset(arTask);
	
	aref arBase;
	if(CheckAttribute(arTask, "base_text"))
		DeleteAttribute(arTask, "base_text");
	makearef(arBase, arTask.base_text);
    arBase.t0.text  = StringFromKey("Tutorial_17");
    arBase.t0.font  = "interface_normal_bold";
	arBase.t0.scale = TW_DEF_HEADER_SCALE;
    arBase.t1.text  = StringFromKey("Tutorial_18");
    arBase.t1.font  = "interface_normalpcb";
    arBase.t1.scale = TW_DEF_STRING_SCALE;
	arBase.t2.text  = "0/3";
	arBase.t2.font  = "interface_normalpcb";
    arBase.t2.scale = 2.0;
	arBase.t2.align = "right";
	arTask.fixWidth = true;
	
	makearef(arImage, arTask.images.background);
    arImage.group   = "TUTORIAL_BACK";
    arImage.picture = "background";
	
	makearef(arText, arTask.texts.WinBattle_head);
	arText.font  = "interface_normal_bold";
    arText.base.pos.y = TW_DEF_HEADER;
	arText.base.scale = TW_DEF_HEADER_SCALE;
    arText.text  = StringFromKey("Tutorial_17");
    arText.align = "center";
    TW_ColorHead(arText);
	
	makearef(arText, arTask.texts.WinBattle_do);
    arText.font  = "interface_normalpcb";
    arText.base.pos.y = TW_DEF_FIRSTSTRING;
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.text  = StringFromKey("Tutorial_18");
    TW_ColorDefault(arText);
    TW_MarkBottom("sea_battle", "WinBattle_do");
	
	int iMax = Group_GetLiveCharactersNum("SharlieTutorial_SeaAttack");
	arText = TW_SetTextCounter("sea_battle", "WinBattle_do", iMax, false);
	arText.font  = "interface_normalpcb";
	arText.base.scale = 2.0;
    arText.base.pos.y = TW_DEF_FIRSTSTRING - TW_DEF_COUNTERVOFFSET;
    arText.align = "right";
	TW_ColorDefault(arText);
	
	TW_RecalculateLayout();
}

void TW_InitLand_Fight_1_Attack()
{
	LaunchTutorial("Prologue_FightAttack", 1);
	
	aref arTask, arImage, arText, arDef;
	makearef(arDef, objTask.defines);
	
	objTask.land_fight = "1_Attack";
	makearef(arTask, objTask.land_fight);
    TW_Reset(arTask);
	
	aref arBase;
	if(CheckAttribute(arTask, "base_text"))
		DeleteAttribute(arTask, "base_text");
	makearef(arBase, arTask.base_text);
    arBase.t0.text  = StringFromKey("Tutorial_19");
    arBase.t0.font  = "interface_normal_bold";
	arBase.t0.scale = TW_DEF_HEADER_SCALE;
    arBase.t1.text  = StringFromKey("Tutorial_20", GKIC("ChrAltAttackBase", "FightModeControls"));
    arBase.t1.font  = "interface_normalpcb";
    arBase.t1.scale = TW_DEF_STRING_SCALE;
	arBase.t2.text  = StringFromKey("Tutorial_21", GKIC("ChrAttackBase", "FightModeControls"));
    arBase.t2.font  = "interface_normalpcb";
    arBase.t2.scale = TW_DEF_STRING_SCALE;
	arBase.t3.text  = StringFromKey("Tutorial_22", GKIC("ChrAttackBreakBase", "FightModeControls"));
    arBase.t3.font  = "interface_normalpcb";
    arBase.t3.scale = TW_DEF_STRING_SCALE;
	arBase.t4.text  = "0/3";
	arBase.t4.font  = "interface_normalpcb";
    arBase.t4.scale = 2.0;
	arBase.t4.align = "right";
	arTask.fixWidth = true;
	
	makearef(arText, arTask.texts.FightAttack_head);
	arText.font  = "interface_normal_bold";
    arText.base.pos.y = TW_DEF_HEADER;
	arText.base.scale = TW_DEF_HEADER_SCALE;
    arText.text  = StringFromKey("Tutorial_19");
    arText.align = "center";
    TW_ColorHead(arText);
	
	makearef(arText, arTask.texts.FightAttack_fast);
    arText.font  = "interface_normalpcb";
    arText.base.pos.y = TW_DEF_FIRSTSTRING;
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.text  = StringFromKey("Tutorial_20", GKIC("ChrAltAttackBase", "FightModeControls"));
    TW_ColorDefault(arText);
	
	makearef(arText, arTask.texts.FightAttack_force);
    arText.font  = "interface_normalpcb";
    arText.base.pos.y = TW_DEF_FIRSTSTRING + TW_DEF_INTERVAL;
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.text  = StringFromKey("Tutorial_21", GKIC("ChrAttackBase", "FightModeControls"));
    TW_ColorDefault(arText);
	
	makearef(arText, arTask.texts.FightAttack_break);
    arText.font  = "interface_normalpcb";
    arText.base.pos.y = TW_DEF_FIRSTSTRING + 2 * TW_DEF_INTERVAL;
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.text  = StringFromKey("Tutorial_22", GKIC("ChrAttackBreakBase", "FightModeControls"));
    TW_ColorDefault(arText);

    TW_MarkBottom("land_fight", "FightAttack_break");
	
	arText = TW_SetTextCounter("land_fight", "FightAttack_fast", 3, false);
	arText.font  = "interface_normalpcb";
	arText.base.scale = 2.0;
    arText.base.pos.y = TW_DEF_FIRSTSTRING - TW_DEF_COUNTERVOFFSET;
    arText.align = "right";
	TW_ColorDefault(arText);
	
	arText = TW_SetTextCounter("land_fight", "FightAttack_force", 3, false);
	arText.font  = "interface_normalpcb";
	arText.base.scale = 2.0;
    arText.base.pos.y = TW_DEF_FIRSTSTRING - TW_DEF_COUNTERVOFFSET + TW_DEF_INTERVAL;
    arText.align = "right";
	TW_ColorDefault(arText);
	
	arText = TW_SetTextCounter("land_fight", "FightAttack_break", 1, false);
	arText.font  = "interface_normalpcb";
	arText.base.scale = 2.0;
    arText.base.pos.y = TW_DEF_FIRSTSTRING - TW_DEF_COUNTERVOFFSET + 2 * TW_DEF_INTERVAL;
    arText.align = "right";
	TW_ColorDefault(arText);
	
	TW_SetTaskTimer(arTask, "1_Attack");
	
//	TW_RecalculateLayout();
}

void TW_FinishLand_Fight_1_Attack()
{
	objTask.land_fight = "";
	DoQuestFunctionDelay("TW_InitLand_Fight_2_Defence", 1.0);
}

void TW_InitLand_Fight_2_Defence(string qName)
{
	LaunchTutorial("Prologue_FightDefence", 1);
	
	aref arTask, arImage, arText, arDef;
	makearef(arDef, objTask.defines);
	
	objTask.land_fight = "2_Defence";
	makearef(arTask, objTask.land_fight);
    TW_Reset(arTask);
	
	aref arBase;
	if(CheckAttribute(arTask, "base_text"))
		DeleteAttribute(arTask, "base_text");
	makearef(arBase, arTask.base_text);
    arBase.t0.text  = StringFromKey("Tutorial_23");
    arBase.t0.font  = "interface_normal_bold";
	arBase.t0.scale = TW_DEF_HEADER_SCALE;
    arBase.t1.text  = StringFromKey("Tutorial_24", GKIC("ChrBlock", "FightModeControls"));
    arBase.t1.font  = "interface_normalpcb";
    arBase.t1.scale = TW_DEF_STRING_SCALE;
	arBase.t2.text  = StringFromKey("Tutorial_25", GKIC("ChrParry", "FightModeControls"));
    arBase.t2.font  = "interface_normalpcb";
    arBase.t2.scale = TW_DEF_STRING_SCALE;
	arBase.t3.text  = "0/3";
	arBase.t3.font  = "interface_normalpcb";
    arBase.t3.scale = 2.0;
	arBase.t3.align = "right";
	arTask.fixWidth = true;
	
	makearef(arText, arTask.texts.FightDefence_head);
	arText.font  = "interface_normal_bold";
    arText.base.pos.y = TW_DEF_HEADER;
	arText.base.scale = TW_DEF_HEADER_SCALE;
    arText.text  = StringFromKey("Tutorial_23");
    arText.align = "center";
    TW_ColorHead(arText);
	
	makearef(arText, arTask.texts.FightDefence_block);
    arText.font  = "interface_normalpcb";
    arText.base.pos.y = TW_DEF_FIRSTSTRING;
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.text  = StringFromKey("Tutorial_24", GKIC("ChrBlock", "FightModeControls"));
    TW_ColorDefault(arText);
	
	makearef(arText, arTask.texts.FightDefence_parry);
    arText.font  = "interface_normalpcb";
    arText.base.pos.y = TW_DEF_FIRSTSTRING + TW_DEF_INTERVAL;
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.text  = StringFromKey("Tutorial_25", GKIC("ChrParry", "FightModeControls"));
    TW_ColorDefault(arText);

    TW_MarkBottom("land_fight", "FightDefence_parry");
	
	arText = TW_SetTextCounter("land_fight", "FightDefence_block", 3, false);
	arText.font  = "interface_normalpcb";
	arText.base.scale = 2.0;
    arText.base.pos.y = TW_DEF_FIRSTSTRING - TW_DEF_COUNTERVOFFSET;
    arText.align = "right";
	TW_ColorDefault(arText);
	
	arText = TW_SetTextCounter("land_fight", "FightDefence_parry", 2, false);
	arText.font  = "interface_normalpcb";
	arText.base.scale = 2.0;
    arText.base.pos.y = TW_DEF_FIRSTSTRING - TW_DEF_COUNTERVOFFSET + TW_DEF_INTERVAL;
    arText.align = "right";
	TW_ColorDefault(arText);
	
	TW_SetTaskTimer(arTask, "2_Defence");
	
	TW_RecalculateLayout();
}

void TW_FinishLand_Fight_2_Defence()
{
	ref chr = CharacterFromID("SharlieTutorial_EnemyPirate_0");
	SetDummy(chr, false);
	objTask.land_fight = "";
	TW_DeleteTimer();
	DoQuestFunctionDelay("TW_InitLand_Fight_3_Win", 1.5);
}

void TW_InitLand_Fight_3_Win(string qName)
{
	if(CheckAttribute(&TEV, "Tutor.BackControlsTips"))
	{
		iControlsTips = sti(TEV.Tutor.BackControlsTips);
		DeleteAttribute(&TEV, "Tutor.BackControlsTips");
	}
				
	aref arTask, arImage, arText, arDef;
	makearef(arDef, objTask.defines);
	
	objTask.land_fight = "3_WinFight";
	makearef(arTask, objTask.land_fight);
    TW_Reset(arTask);
	
	aref arBase;
	if(CheckAttribute(arTask, "base_text"))
		DeleteAttribute(arTask, "base_text");
	makearef(arBase, arTask.base_text);
    arBase.t0.text  = StringFromKey("Tutorial_17");
    arBase.t0.font  = "interface_normal_bold";
	arBase.t0.scale = TW_DEF_HEADER_SCALE;
    arBase.t1.text  = StringFromKey("Tutorial_26");
    arBase.t1.font  = "interface_normalpcb";
    arBase.t1.scale = TW_DEF_STRING_SCALE;
	arTask.fixWidth = true;
	
	makearef(arImage, arTask.images.background);
    arImage.group   = "TUTORIAL_BACK";
    arImage.picture = "background";
	
	makearef(arText, arTask.texts.WinFight_head);
	arText.font  = "interface_normal_bold";
    arText.base.pos.y = TW_DEF_HEADER;
	arText.base.scale = TW_DEF_HEADER_SCALE;
    arText.text  = StringFromKey("Tutorial_17");
    arText.align = "center";
    TW_ColorHead(arText);
	
	makearef(arText, arTask.texts.WinFight_do);
    arText.font  = "interface_normalpcb";
    arText.base.pos.y = TW_DEF_FIRSTSTRING;
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.text  = StringFromKey("Tutorial_26");
	arText.align = "center";
    TW_ColorDefault(arText);
    TW_MarkBottom("land_fight", "WinFight_do");
	
	TW_RecalculateLayout();
}

void TW_InitLand_Craft_1_Inventory()
{
	Tutorial_Prologue_Inventory("");
	
	aref arTask, arImage, arText, arDef;
	makearef(arDef, objTask.defines);
	
	objTask.land_craft = "1_Inventory";
	makearef(arTask, objTask.land_craft);
    TW_Reset(arTask);
	
	aref arBase;
	if(CheckAttribute(arTask, "base_text"))
		DeleteAttribute(arTask, "base_text");
	makearef(arBase, arTask.base_text);
    arBase.t0.text  = StringFromKey("Tutorial_27");
    arBase.t0.font  = "interface_normal_bold";
	arBase.t0.scale = TW_DEF_HEADER_SCALE;
    arBase.t1.text  = StringFromKey("Tutorial_28", GKIC("QuestBook", "PrimaryLand"));
    arBase.t1.font  = "interface_normalpcb";
    arBase.t1.scale = TW_DEF_STRING_SCALE;
	arBase.t2.text  = StringFromKey("Tutorial_29", GKIC("Alchemy", "PrimaryLand"));
    arBase.t2.font  = "interface_normalpcb";
    arBase.t2.scale = TW_DEF_STRING_SCALE;
	arTask.fixWidth = true;
	
	makearef(arText, arTask.texts.Inventory_head);
	arText.font  = "interface_normal_bold";
    arText.base.pos.y = TW_DEF_HEADER;
	arText.base.scale = TW_DEF_HEADER_SCALE;
    arText.text  = StringFromKey("Tutorial_27");
    arText.align = "center";
    TW_ColorHead(arText);
	
	makearef(arText, arTask.texts.Inventory_document);
    arText.font  = "interface_normalpcb";
    arText.base.pos.y = TW_DEF_FIRSTSTRING;
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.text  = StringFromKey("Tutorial_28", GKIC("QuestBook", "PrimaryLand"));
    TW_ColorDefault(arText);
	
	makearef(arText, arTask.texts.Inventory_alchemy);
    arText.font  = "interface_normalpcb";
    arText.base.pos.y =  TW_DEF_FIRSTSTRING + TW_DEF_INTERVAL;
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.text  = StringFromKey("Tutorial_29", GKIC("Alchemy", "PrimaryLand"));
    TW_ColorDefault(arText);
	
	TW_MarkBottom("land_craft", "Inventory_alchemy");
	
	TEV.Tutor.Document = 0;
	TEV.Tutor.Alchemy = 0;
}

void TW_FinishLand_Craft_1_Inventory()
{
	objTask.land_craft = "";
	PostEvent("TW_Release", 2000);
}
		
void TW_InitLand_1_Loot()
{	
	aref arTask, arImage, arText, arDef;
	makearef(arDef, objTask.defines);
	
	objTask.land = "1_Loot";
	makearef(arTask, objTask.land);
    TW_Reset(arTask);
	
	aref arBase;
	if(CheckAttribute(arTask, "base_text"))
		DeleteAttribute(arTask, "base_text");
	makearef(arBase, arTask.base_text);
    arBase.t0.text  = StringFromKey("Tutorial_30");
    arBase.t0.font  = "interface_normal_bold";
	arBase.t0.scale = TW_DEF_HEADER_SCALE;
    arBase.t1.text  = StringFromKey("Tutorial_31");
    arBase.t1.font  = "interface_normalpcb";
    arBase.t1.scale = TW_DEF_STRING_SCALE;
	arBase.t2.text  = StringFromKey("Tutorial_32");
    arBase.t2.font  = "interface_normalpcb";
    arBase.t2.scale = TW_DEF_STRING_SCALE;
	arBase.t3.text  = "0/3";
	arBase.t3.font  = "interface_normalpcb";
    arBase.t3.scale = 2.0;
	arBase.t3.align = "right";
	arTask.fixWidth = true;
	
	makearef(arText, arTask.texts.Loot_head);
	arText.font  = "interface_normal_bold";
    arText.base.pos.y = TW_DEF_HEADER;
	arText.base.scale = TW_DEF_HEADER_SCALE;
    arText.text  = StringFromKey("Tutorial_30");
    arText.align = "center";
    TW_ColorHead(arText);
	
	makearef(arText, arTask.texts.Loot_search);
    arText.font  = "interface_normalpcb";
    arText.base.pos.y = TW_DEF_FIRSTSTRING;
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.text  = StringFromKey("Tutorial_31");
    TW_ColorDefault(arText);
	
	TW_MarkBottom("land", "Loot_search");
	
	TEV.Tutor.NeedPotion = 1;
	
	arText = TW_SetTextCounter("land", "Loot_search", 3, false);
	arText.font = "interface_normalpcb";
	arText.base.scale = 2.0;
    arText.base.pos.y = TW_DEF_FIRSTSTRING - TW_DEF_COUNTERVOFFSET;
    arText.align = "right";
	TW_ColorDefault(arText);
}
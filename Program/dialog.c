
// #include "dialog_func.c" // old
#include "dialogs\%language%\dialog_func.c"

#define EVENT_DIALOG_START		"evntDialogStart"
#define EVENT_DIALOG_EXIT		"evntDialogExit"

#event_handler("dlgReady", "StartDialogWithMainCharacter");
#event_handler("EmergencyDialogExit","DialogExit");

extern void ProcessDialogEvent();
extern void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag); // метод, содержащий ветку квест и др ветки конкрентого НПС

bool dialogDisable = false;
object	Dialog;
ref		CharacterRef;
bool	dialogRun = false;

bool	dialogSelf = false;

string  FullDialogPath;
string	PathDlgLngExtn = "";//fix

string dialogEditStrings[10];

void ProcessCommonDialog(ref NPChar, aref Link, aref NextDiag)
{
    ProcessCommonDialogEvent(NPChar, Link, NextDiag);
}

//Инициализация
void DialogsInit()
{
	//Quest_Init();				//Инициализация начального состояния слухов и информации об NPC ------- Ренат
	Set_inDialog_Attributes(); // boal
}

#event_handler("DialogControls_Lock","DialogControls_Lock");
void DialogControls_Lock()
{
    LockControl("DlgAction", true);
    LockControl("DlgAction1", true); 
    LockControl("DlgAction2", true); 
    PostEvent("DialogControls_Unlock", 250);
}

#event_handler("DialogControls_Unlock","DialogControls_Unlock");
void DialogControls_Unlock()
{
    if(!dialogRun) return;
    LockControl("DlgAction", false);
    LockControl("DlgAction1", false);
    LockControl("DlgAction2", false);
}

//Начать диалог
bool DialogMain(ref Character, bool bPlayerInit)
{
	//Если диалог запущен, выходим
	if(dialogRun != false) return false;
	//Ссылка на главного персонажа
	ref mainChr = GetMainCharacter();
	//Если когото не заведено, выходим
	if(!IsEntity(&mainChr)) return false;
	if(!IsEntity(&Character)) return false;
	if(LAi_IsDead(mainChr)) return false;
	if(LAi_IsDead(Character)) return false;
	//Проверим на существование текущего нода
	if(!CheckAttribute(Character, "Dialog.CurrentNode"))
	{
		Trace("Dialog: Character <" + Character.id + "> can't have field Dialog.CurrentNode, exit from dialog!")
		return false;
	}
	//Если персонаж не готов говорить выходим
	if(!LAi_Character_CanDialog(mainChr, Character)) return false;
	//Если персонаж не готов говорить выходим
	if(!LAi_Character_CanDialog(Character, mainChr)) return false;
	//Сохраняем ссыклу на того с кем говорим
	CharacterRef = Character;
	// Попытка загрузить текст дилога
	if( !LoadDialogFiles(Character.Dialog.Filename) ) {
		// имеем ошибочный диалог
		if( !LoadDialogFiles("error_dialog.c") ) {
			return false;
		}
	}
	//Можем начинать диалог
	dialogRun = true;
	dialogSelf = false;
    if (!bBettaTestMode && !bPlayerInit) PostEvent("DialogControls_Lock", 0);
	LAi_Character_StartDialog(mainChr, Character);
	LAi_Character_StartDialog(Character, mainChr);
	SendMessage(mainChr, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 1);
	SendMessage(Character, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 1);	
	//Запускаем диалог
	//Trace("Dialog: dialog path for character <" + Character.id + "> = " + FullDialogPath);
	Dialog.CurrentNode = CharacterRef.Dialog.CurrentNode;
	startDialogMainCounter = 0;
	SetEventHandler("frame", "StartDialogMain", 1);
	// SetTimeScale(0.0);
	ResetTimeScale();
	Log_SetActiveAction("Nothing");	
	bool groundSitPoorman = (mainChr.chr_ai.type == LAI_TYPE_GROUNDSIT);
	bool groundSitActor = (mainChr.chr_ai.type == LAI_TYPE_ACTOR) && (mainChr.chr_ai.type.mode == "groundSit");
    bool bLockCamAngle = CheckAttribute(loadedLocation, "lockCamAngle") && !Whr_CheckNewBoardingDeck();
	if (locCameraCurMode == LOCCAMERA_FOLLOW && !locCameraIsFPVMode() && !bLockCamAngle && mainChr.location.group != "sit" && !groundSitPoorman && !groundSitActor && !CheckAttribute(pchar, "GenQuest.BlockDialogCamera")) // для квестов
	{
		SetCameraDialogMode(Character);  // boal
	}
	return true;	
}

int startDialogMainCounter = 0;
int dialogWaitGreetingSound = 0;
string dialogGreetingSound = "";

void StartDialogMain()
{
	startDialogMainCounter++;
	if(startDialogMainCounter < 3) return;
	
	SendMessage(pchar, "l", MSG_CHARACTER_STOPSTRAFE);
	
	DelEventHandler("frame", "StartDialogMain");

	CreateEntity(&Dialog, "dialog");
	Dialog.headModel = CharacterRef.headModel;
	Dialog.gender = CharacterRef.sex;

	DeleteAttribute(&Dialog,"Links");
	DeleteAttribute(&Dialog,"Text");

	if(CheckAttribute(CharacterRef, "greeting"))
	{
		if(CharacterRef.greeting != "")
		{
			if (!CheckAttribute(CharacterRef, "greeting.minute"))
			{
				dialogGreetingSound = CharacterRef.greeting;
				dialogWaitGreetingSound = 0;
				SetEventHandler("frame", "DialogPlayGreeting", 1);
			}
			else
			{
				if (sti(CharacterRef.greeting.minute) != sti(Environment.date.min))
				{
					dialogGreetingSound = CharacterRef.greeting;
					dialogWaitGreetingSound = 0;
					SetEventHandler("frame", "DialogPlayGreeting", 1);
				}
			}
		}
	}

	object persRef = GetCharacterModel(Characters[GetMainCharacterIndex()]);
	SendMessage(&Dialog, "lii", 0, &Characters[GetMainCharacterIndex()], &persRef);

	ref chr = GetCharacter(makeint(CharacterRef.index));
	object charRef = GetCharacterModel(chr);
	SendMessage(&Dialog, "lii", 1, chr, &charRef);

	UpdateDynamicRole(&Dialog, chr);

	LayerSetRealize(REALIZE);
	LayerAddObject(REALIZE,Dialog,-256);
	Set_inDialog_Attributes();
	ProcessDialogEvent();
	AddDialogMeta();

	SetEventHandler("DialogEvent","ProcessDialogEvent",0);
	SetEventHandler("DialogEvent", "AddDialogMeta", 0);
	//SetEventHandler("DialogCancel","DialogExit",0);

	Event(EVENT_DIALOG_START,"");
}

void DialogPlayGreeting()
{
	dialogWaitGreetingSound++;
	if(dialogWaitGreetingSound < 10) return;
	dialogWaitGreetingSound = 0;
	DelEventHandler("frame", "DialogPlayGreeting");
	//Dialog.greeting = LanguageGetLanguage() + " " + CharacterRef.greeting;
	Dialog.greeting = CharacterRef.greeting;
	CharacterRef.greeting.minute = GetMinute();
	//Dialog.greeting = "Gr_Barmen";
}

//Начать диалог с самим собой
void SelfDialog(ref Character)
{
	//Если диалог запущен, выходим
	if(dialogRun != false) return false;
	//Если когото не заведено, выходим
	if(!IsEntity(&Character)) return false;
	//Проверим на существование текущего нода
	if(!CheckAttribute(Character, "Dialog.CurrentNode"))
	{
		Trace("SelfDialog: Character <" + Character.id + "> can't have field Dialog.CurrentNode, exit from dialog!")
		return false;
	}
	//Сохраняем ссыклу на того с кем говорим
	CharacterRef = Character;
	// Попытка загрузить текст дилога
	if( !LoadDialogFiles(Character.Dialog.Filename) ) {
		// имеем ошибочный диалог
		if( !LoadDialogFiles("error_dialog.c") ) {
			return false;
		}
	}
	//Если персонаж не готов говорить выходим
	LAi_Character_CanDialog(Character, Character);
	//Можем начинать диалог
	dialogRun = true;
	dialogSelf = true;
	SendMessage(Character, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 1);
	//Запускаем диалог
	Dialog.CurrentNode = CharacterRef.Dialog.CurrentNode;
	//Trace("SelfDialog: dialog path for self character <" + Character.id + "> = " + FullDialogPath);
	CreateEntity(&Dialog, "dialog");
	Dialog.headModel = Character.headModel;
	Dialog.gender = Character.sex;

	object persRef = GetCharacterModel(Characters[GetMainCharacterIndex()]);
	SendMessage(&Dialog, "lii", 0, Character, &persRef);
	SendMessage(&Dialog, "lii", 1, Character, &persRef);
	Dialog.role = "";
	
	LayerSetRealize(REALIZE);
	LayerAddObject(REALIZE,Dialog,-256);
	Set_inDialog_Attributes();
	ProcessDialogEvent();
	AddDialogMeta();

	SetEventHandler("DialogEvent","ProcessDialogEvent",0);
	SetEventHandler("DialogEvent", "AddDialogMeta", 0);
	//SetEventHandler("DialogCancel","DialogExit",0);	

	Event(EVENT_DIALOG_START,"");
}

//Закончить диалог
void DialogExit()
{
	//Если диалога уже не ведётся, выйдем
	if(dialogRun == false) return;
	DelEventHandler("frame", "DialogPlayGreeting");
	//Освобождаем ресурсы
	DeleteClass(&Dialog);
	if(FullDialogPath!="")
	{
		if (CheckAttribute(CharacterRef, "FileDialog2"))
		{
		    UnloadSegment(CharacterRef.FileDialog2);
		    // мешало выходу в сегменте DeleteAttribute(CharacterRef, "FileDialog2");
		    //DeleteAttribute(CharacterRef, "FileDialog2Ready");
		}
		UnloadSegment(FullDialogPath);
	}
	if(PathDlgLngExtn!="") UnloadSegment(PathDlgLngExtn);
	if(dialogSelf == false)
	{
		//Ссылка на главного персонажа
		ref mainChr = GetMainCharacter();
		//Отметим, что персонажи освободились от диалога
		LAi_Character_EndDialog(mainChr, CharacterRef);
		LAi_Character_EndDialog(CharacterRef, mainChr);
		SendMessage(mainChr, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 0);
		SendMessage(CharacterRef, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 0);
		// boal
		if (locCameraCurMode != LOCCAMERA_FOLLOW && !CheckAttribute(pchar, "GenQuest.BlockDialogCamera"))
		{
			locCameraTarget(mainChr);
			locCameraFollow();
			locCameraSetFollowCamAngleToCharacterAngle();
		}
	}else{
		LAi_Character_EndDialog(CharacterRef, CharacterRef);
		SendMessage(CharacterRef, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 0);
	}
	dialogRun = false;
	pchar.systeminfo.DialogExitDelay = true;
	DoQuestFunctionDelay("DialogExitDelayEnd", 0.5);
	//Сообщим об окончании диалога
	PostEvent(EVENT_DIALOG_EXIT, 1, "l", sti(CharacterRef.index));
	DelEventHandler("DialogEvent", "AddDialogMeta");
}

// belamour удалить флаг выхода из диалога
void DialogExitDelayEnd(string qName)
{
    DeleteAttribute(pchar,"systeminfo.DialogExitDelay");
}

//Это событие приходит от Player
void StartDialogWithMainCharacter()
{
	if(LAi_IsBoardingProcess()) return;
	if(dialogDisable) return;
	//С кем хотим говорить
	int person = GetEventData();
	//Сими с собой не беседуем
	if(person<0) return;
	if(person == GetMainCharacterIndex()) return;
	//С непрогруженными персонажами не беседуем
	if(!IsEntity(&Characters[person])) return;
	//Начинаем диалог
	DialogMain(&Characters[person], true);
	//Trace("Dialog: start dialog " + person + " whith main character");
}

bool LoadDialogFiles(string dialogPath)
{
	//FullDialogPath = "dialogs/" + dialogPath;
	FullDialogPath = "dialogs\" + LanguageGetLanguage() + "\" + dialogPath;

	// Выбор директории с языковыми файлами
	//string sLanguageDir = "dialogs\" + LanguageGetLanguage() + "\";
	//Путь до текста диалога
	/*int iTmp = strlen(dialogPath);
	if(iTmp<3)
	{
		Trace("Dialog: Missing dialog file: " + dialogPath);
		return false;
	}*/
	//PathDlgLngExtn = strcut(dialogPath,0,iTmp-2) + "h";

	//bool retVal = LoadSegment(PathDlgLngExtn);
	bool retVal;
	
	if( !LoadSegment(FullDialogPath) )
	{
		Trace("Dialog: Missing dialog file: " + FullDialogPath);
		retVal = false;
		// лишнее это UnloadSegment(FullDialogPath);
	} else {
		if(!retVal) {
			retVal = true;
			PathDlgLngExtn = "";
		}
	}

	return retVal;
}


string DText(string sString)
{
	return sString;
}

// boal -->
bool SetCameraDialogMode(ref chrRef)
{
	float x1,y1,z1, x2, y2, z2;
	if( false==GetCharacterPos(pchar,&x1,&y1,&z1) ) return false;
    if( false==GetCharacterPos(chrRef,&x2,&y2,&z2) ) return false;

    float a = 0.1;
	if(DlgCameraSpecAng(chrRef)) a = - 0.5;
	
    float len = GetDistance2D(x1,z1, x2,z2);
	float dx = x1*(1-a)+x2*a;
	float dz = z1*(1-a)+z2*a;
	len = 1;
	float s1 = (dx-x1)*len;
	float s2 = (dz-z1)*len;

    float xcam;
	float zcam;
	if (rand(1) == 0)
	{
		xcam = dx-s2;
		zcam = dz+s1;
	}
	else
	{
		xcam = dx+s2;
		zcam = dz-s1;
	}
	locCameraTarget(chrRef);
	float fH = 1.7;
	if (chrRef.location.group == "sit")
	{
	    fH = 1.15;
	}
	return locCameraToPosEx(xcam, y1+fH, zcam, false, 0.1);
}
// boal <--

// mitrokosta возможность начать диалог
bool CanStartDialog()
{
	if(LAi_IsBoardingProcess() || dialogDisable || dialogRun) {
		return false;
	}

	ref mc = GetMainCharacter();

	if(!IsEntity(mc)) {
		return false;
	}

	int chrIndex = SendMessage(mc, "ls", MSG_CHARACTER_EX_MSG, "FindDialogCharacter");

	if(chrIndex < 0 || chrIndex == GetMainCharacterIndex()) {
		return false;
	}

	ref chr = GetCharacter(chrIndex);

	if(!IsEntity(chr) || LAi_IsDead(mc) || LAi_IsDead(chr) || !CheckAttribute(chr, "Dialog.CurrentNode") || 
		!LAi_Character_CanDialog(mc, chr) || !LAi_Character_CanDialog(chr, mc)) {
		return false;
	}
	// evganat - помечаем готового к диалогу персонажа
	SendMessage(pchar, "lsli", MSG_CHARACTER_EX_MSG, "MarkDialogCharacter", true, chr);
	return true;
}
//belamour специальный угол для камеры
bool DlgCameraSpecAng(ref chrRef)
{
	ref loc = loadedLocation;
	if(CheckAttribute(loc,"type") && !CheckAttribute(pchar, "questTemp.CameraDialogMode"))
	{
		if(loc.type == "town") return true;
		if(loc.type == "jungle") return true;
		if(loc.type == "seashore") return true;
		if(loc.type == "reef") return true;
		if(loc.type == "questisland") return true;
		if(loc.type == "tavern") 
		{
			if(chrRef.location.group == "sit") return false;
			return true;
		}
		if(loc.type == "questisland") return true;
	}
	return false;
}

bool DialogHasEdit(aref link) {
	int linkCount = GetAttributesNum(link);
	for (int i = 0; i < linkCount; i++) {
		aref thisLink = GetAttributeN(link, i);
		if (CheckAttribute(thisLink, "edit")) {
			return true;
		}
	}
	
	return false;
}

void AddDialogMeta() {
	// if(dialog.text != "") dialog.text = GetFullName(CharacterRef) + ": " + dialog.text;
	aref link;
	makearef(link, dialog.links);
	bool hasEdit = DialogHasEdit(link);
	int linkCount = GetAttributesNum(link);
	for (int i = 0; i < linkCount; i++) {
		string linkName = GetAttributeName(GetAttributeN(link, i));
		if(link.(linkName) != "")
		{
			if(!hasEdit) link.(linkName) = "" + (i + 1) + ". " + link.(linkName);
		}
		else
		{
			if(!CheckAttribute(link, linkName + ".edit")) link.(linkName) = "...";
		}
	}
}

// Выставляем плашку с ролью в диалоге по атрибуту персонажа, за исключением офицеров
void UpdateDynamicRole(ref Dialog, ref chr)
{
	Dialog.role = "";

	// Уважаемый дата-майнер, здесь совершенно точно не спрятано секретных квестов, это просто пасхалка
	// медленно положи свой текстовый редактор на пол и отойди. Медленно! (⌐■_■)
	if (CheckAttribute(chr, "quest.last_theme") && chr.quest.last_theme == "0" && !CheckAttribute(chr, "role"))
	{
		if (chr.greeting == "habitue") chr.role = "drinker_" + rand(9);
	}
	if (CheckAttribute(chr, "PhantomType"))
	{
		if (chr.PhantomType == "pofficer") chr.role = "pofficer";
		else if (chr.PhantomType == "gipsy") chr.role = "gipsy";
		else if (chr.PhantomType == "captain") chr.role = "captain";
		else if (chr.PhantomType == "noble") chr.role = "noble";
	}
	if(CheckAttributeEqualTo(chr, "quest.type", "hovernor"))
	{
		if(sti(chr.nation) == PIRATE) chr.role = "Phovernor";
		else chr.role = "hovernor";
	}
	if(CheckAttribute(chr, "Merchant.type") && chr.Merchant.type != "GasparGold")
	{
		chr.role = chr.Merchant.type + "_merchant";
	}
	
	if(HasSubStr(chr.id, "_tavernkeeper")) chr.role = "tavernkeeper";
	else if(HasSubStr(chr.id, "_waitress")) chr.role = "waitress";
	else if(HasSubStr(chr.id, "_trader")) chr.role = "trader";
	else if(HasSubStr(chr.id, "_shipyarder")) chr.role = "shipyarder";
	else if(HasSubStr(chr.id, "_PortMan")) chr.role = "portman";
	else if(HasSubStr(chr.id, "_Priest")) chr.role = "priest";
	else if(HasSubStr(chr.id, "_usurer")) chr.role = "usurer";
	else if(HasSubStr(chr.id, "_Poorman")) chr.role = "poorman";
	else if(HasSubStr(chr.id, "_Hostess")) chr.role = "hostess";
	else if(HasSubStr(chr.id, "_smuggler")) chr.role = "smuggler";
	
	if(chr.model == "Alonso")
	{
		Dialog.role = GetConvertStr("HeadSailor", "roles.txt");
		if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.FourthStage", "completed"))
			Dialog.role = GetConvertStr("HeadSailorPlus", "roles.txt");
		return;
	}
	
	// belamour return только в особых ситуациях
	if(RoleFromID(chr))
	{
		Dialog.role = GetCharacterRole(chr);
		if(chr.role == "friend")
			Dialog.role = Dialog.role + " / " + GetJobsList(chr, " / ");
		return;
	}
	if (CheckAttribute(chr, "SpecialRole")) 
	{
		Dialog.role = GetCharacterSpecialRole(chr);
		return;
	}
	if (CheckAttribute(chr, "Payment")) Dialog.role = GetJobsList(chr, " / ");
	else if (CheckAttributeHasValue(chr, "role")) Dialog.role = GetCharacterRole(chr);
}

bool RoleFromID(ref chr)
{
	if(!CheckAttribute(chr, "id")) return;
	
	string role = "";
	switch (chr.id)
	{
		case "Puancie": role = "Ghovernor"; break;
		case "Vindzor": role = "Ghovernor"; break;
		case "Cordova": role = "Ghovernor"; break;
		
		case "LadyBeth_cap": role = "legend"; break;
		case "LadyBeth_clone_tavern": role = "legend"; break;
		case "Memento_cap": role = "legend"; break;
		case "SantaMisericordia_cap": role = "legend"; break;
		case "SantaMisericordia_clone_church": role = "legend"; break;
		case "SantaMisericordia_clone_city": role = "legend"; break;
		case "SantaMisericordia_clone_guber": role = "legend"; break;
		
		if (CheckAttribute(pchar, "questTemp.FinishTutorial"))
		{
			case "Guide": role = "friend"; break;
			case "Guide_y": role = "friend"; break;
			case "Guide_x": role = "friend"; break;
		}
		
		case "Tichingitu":
			if (CheckAttribute(chr, "Payment")) 
			{
				chr.role = "friend";
				return true;
			}
		break;
		case "Irons":
			if (CheckAttribute(chr, "Payment") && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted")) 
			{
				chr.role = "friend";
				return true;
			}
		break;
		case "Folke":
			if (CheckAttribute(chr, "FriendRole")) 
			{
				chr.role = "friend";
				return true;
			}
		break;
		case "Knippel":
			if (IsCharacterPerkOn(chr, "Bombardier")) 
			{
				chr.role = "friend";
				return true;
			}
		break;
		case "Longway":
			if (CheckAttribute(chr, "FriendRole")) 
			{
				chr.role = "friend";
				return true;
			}
		break;
		
	}
	if(role != "") chr.role = role;
	
	return false;
}

#include "ships\ships.h"
#include "ships\waterline_breaches.c"

#define NEED_SAILS_INIT 0
#define SHIP_SPEEDPOINT_QUANTITY 72
#define SHIP_RIGTYPE_SQUARE "rig_square"
#define SHIP_RIGTYPE_FOREAFT "rig_fore_aft"
#define SHIP_RIGTYPE_MIXED "rig_mixed"
#define SHIP_RIGUPGRADE_STRENGTH "upgrade_strength"
#define SHIP_RIGUPGRADE_WEAKNESS "upgrade_weakness"

extern void InitShips();
extern void InitSailsColors();
extern void InitRandomShipsNames();
extern void InitSailsParams();
extern void InitSpeedPoints();
extern void InitAdvancedSpeedPoints();

string	sRndShpSpName[22], sRndShpEnName[21], sRndShpFrName[14], sRndShpPiName[9], sRndShpHoName[10];


void ShipsInit()
{
	if (LoadSegment("ships\ships_init.c"))
	{
		InitShips();
		UnloadSegment("ships\ships_init.c");
	}

	// init sails color
	if (LoadSegment("ships\sails_init.c"))
	{
		InitSailsColors();
		InitSailsParams();
		InitSpeedPoints();
		InitAdvancedSpeedPoints();
		UnloadSegment("ships\sails_init.c");
	}
}

void SetRandomNameToShip(ref rCharacter)
{
	ref rMassiveOfNames;
	if(!CheckAttribute(rCharacter, "nation"))
	{
		rCharacter.nation = PIRATE;
	}
	if(sti(rCharacter.nation) == -1)
	{
		rCharacter.nation = PIRATE;
	}

	switch (sti(rCharacter.nation))
	{
		case ENGLAND:	makeref(rMassiveOfNames, sRndShpEnName); break;
		case FRANCE:	makeref(rMassiveOfNames, sRndShpFrName); break;
		case SPAIN:		makeref(rMassiveOfNames, sRndShpSpName); break;
		case PIRATE:	makeref(rMassiveOfNames, sRndShpPiName); break;
		case HOLLAND:	makeref(rMassiveOfNames, sRndShpHoName); break;
	}
	int iMassiveOfNamesSize = GetArraySize(rMassiveOfNames);
	rCharacter.Ship.Name = GetRandSubString(rMassiveOfNames[rand(iMassiveOfNamesSize-2)]);
}

string generateRandomNameToShip(int iNation)
{
	ref rMassiveOfNames;
	switch (iNation)
	{
		case ENGLAND:	makeref(rMassiveOfNames, sRndShpEnName); break;
		case FRANCE:	makeref(rMassiveOfNames, sRndShpFrName); break;
		case SPAIN:		makeref(rMassiveOfNames, sRndShpSpName); break;
		case PIRATE:	makeref(rMassiveOfNames, sRndShpPiName); break;
		case HOLLAND:	makeref(rMassiveOfNames, sRndShpHoName); break;
	}
	int iMassiveOfNamesSize = GetArraySize(rMassiveOfNames);
	string sName = GetRandSubString(rMassiveOfNames[rand(iMassiveOfNamesSize-2)]);
	
	return sName;
}

string GetShipLocationID(ref chref)
{
	if(!CheckAttribute(chref,"ship.type")) 
	{
		return "";
	}
	int st = sti(chref.ship.type);
	if(st==SHIP_NOTUSED) 
	{
		return "";
	}

	int iShipType = sti(RealShips[st].basetype);
	if(ShipsTypes[iShipType].name == "Fort")
	{
		aref ar_FindLoc = FindIslandReloadLocator(chref.location,chref.location.locator);
		if( CheckAttribute(ar_FindLoc,"go") ) 
		{
			MakeCloneFortBoarding(ar_FindLoc.go); // инитим локацию из разных городов
            return "BOARDING_FORT"; // всегда клоновая локация
		}
		return "";
	}
	// в данный метод на вход всегда идёт враг ГГ, метод только на абордаже
	// решаем, что за палуба
	bool bBig1 = (ShipsTypes[iShipType].DeckType == "Big");
	bool bBig2 = (RealShips[sti(pchar.ship.type)].DeckType == "Big");
	bool bMed1 = HasSubStr(ShipsTypes[iShipType].DeckType, "Medium");
	bool bMed2 = HasSubStr(RealShips[sti(pchar.ship.type)].DeckType, "Medium");
	if (bBig1)
	{
	    if (bMed2 || bBig2) return "BOARDING_BIG_DECK";
	    return "BOARDING_MEDIUM_DECK";
	}
	else
	{
	    if (bBig2)
		{
		    if (bMed1 || bBig1) return "BOARDING_BIG_DECK";
		    return "BOARDING_MEDIUM_DECK";
		}
	}
    return "BOARDING_SMALL_DECK";

	/*if(!CheckAttribute(&RealShips[st],"AbordageLocation"))
	{
		trace("WARNING!!! Ship ("+st+") " + ShipsTypes[st].name + " hav`t attribute AbordageLocation");
		return "";
	}
	return RealShips[st].AbordageLocation;*/
}

// boal
string GetShipCabinID(ref chref)
{

	if(!CheckAttribute(chref,"ship.type"))
	{
		return "";
	}
	int st = sti(chref.ship.type);
	if(st==SHIP_NOTUSED)
	{
		return "";
	}

	int iShipType = sti(RealShips[st].basetype);
	if(ShipsTypes[iShipType].name == "Fort")
	{
		return "";
	}
	if(!CheckAttribute(&RealShips[st],"CabinType"))
	{
		trace("WARNING!!! Ship ("+st+") " + ShipsTypes[st].name + " hav`t attribute CabinType");
		return "";
	}
	return RealShips[st].CabinType;
}

bool IsSmallShip(int iShipType)
{
	ref refShip;
	makeref(refShip, ShipsTypes[iShipType]);
	if (sti(refShip.Class) == 7)
	{
		return true;
	}
	return false;
}

void SailsInit()
{
	ref rShip;
	bool bNeedInit = NEED_SAILS_INIT;
	for(int iType = 0; iType < SHIP_TYPES_QUANTITY; iType++)
	{
		if(!Ship_HasSails(iType))
			continue;
		rShip = &ShipsTypes[iType];
		if("sails_data" !in rShip)
		{
			bNeedInit = true;
			break;
		}
	}
	if(!bNeedInit)
		return;
	trace("========= SAILS INIT =========");
	object objsail;
	CreateEntity(&objsail, "sail");
	object objship;
	CreateEntity(&objship, "ship");
	object objmodel;
	CreateEntity(&objmodel, "MODELR");
	for(int i = 0; i < SHIP_TYPES_QUANTITY; i++)
	{
		if(!Ship_HasSails(i))
			continue;
		rShip = &ShipsTypes[i];
		if("sails_data" in rShip)
			continue;
		trace("// === " + rShip.name + " ===");
		SetTexturePath(0, GetShipTexturePath(rShip));
		string sModel = GetShipModelPath(rShip);
		SendMessage(&objmodel, "ls", MSG_MODEL_LOAD_GEO, sModel);
		rShip.sails_data = false;
		aref arData = &rShip.sails_data;
        SendMessage(&objsail, "liila", MSG_SAIL_INIT, &objship, &objmodel, true, arData);
		trace("makeref(refShip, ShipsTypes[" + i + "]);")
		for(int iNode = 0; iNode < @arData; iNode++)
		{
			aref arNode = GetAttributeN(arData, iNode);
			for(int iSail = 0; iSail < @arNode; iSail++)
			{
				aref arSail = GetAttributeN(arNode, iSail);
				trace("refShip.sails_data." + GetAttributeName(arNode) + "." + GetAttributeName(arSail) + ".type = " + arSail.type + ";");
				trace("refShip.sails_data." + GetAttributeName(arNode) + "." + GetAttributeName(arSail) + ".square = " + arSail.square + ";");
				trace("refShip.sails_data." + GetAttributeName(arNode) + "." + GetAttributeName(arSail) + ".base_angle = " + fts(float(arSail.base_angle), 4) + ";");
			}
		}
	}
	DeleteClass(&objsail);
	DeleteClass(&objmodel);
	DeleteClass(&objship);
}

bool Ship_HasSails(int iType)
{
	if(iType == SHIP_BOAT || iType == SHIP_FORT)
		return false;
	if(iType >= SHIP_QUEST1 && iType <= SHIP_QUEST8)
		return false;
	return true;
}

string GetShipModelPath(ref rShip)
{
	int iType = int(rShip.index);
	string sName = rShip.name + "1";
	string sPath = "ships\" + sName + "\" + sName;
	return sPath;
}

string GetShipTexturePath(ref rShip)
{
	string sName = rShip.name + "1";
	string sPath = "ships\" + rShip.name + "1\hull1\";
	return sPath;
}

float Ship_GetSpeedPoint(ref rShip, int iAng, bool bAdvanced)
{
	if(iAng > 180)
		iAng = 360 - iAng;
	string sPoint = "a" + iAng;
	string sAttr = bAdvanced ? "adv_speed_points" : "speed_points";
	if((sAttr + "." + sPoint) !in rShip)
	{
		rShip.(sAttr).(sPoint) = 1.0;
		return 1.0;
	}
	return float(rShip.(sAttr).(sPoint));
}

void Ship_SetSpeedPoint(ref rShip, int iAng, float fSpeed)
{
	if(iAng > 180)
		iAng = 360 - iAng;
	string sPoint = "a" + iAng;
	rShip.speed_points.(sPoint) = fSpeed;
}

#event_handler("Event_SetSailWindParams", "SetSailWindParams");
void SetSailWindParams()
{
	float ts_min = GetEventData();
	float ts_xdep = GetEventData();
	float ts_zdep = GetEventData();
	float fs_min = GetEventData();
	float fs_xdep = GetEventData();
	float fs_zdep = GetEventData();
	float ss_min = GetEventData();
	float ss_xdep = GetEventData();
	float ss_zdep = GetEventData();
	float fMaxAngle = GetEventData();
	float fHoleDepend = GetEventData();
	TEV.SailData.ts_min = ts_min;
	TEV.SailData.ts_xdep = ts_xdep;
	TEV.SailData.ts_zdep = ts_zdep;
	TEV.SailData.fs_min = fs_min;
	TEV.SailData.fs_xdep = fs_xdep;
	TEV.SailData.fs_zdep = fs_zdep;
	TEV.SailData.ss_min = ss_min;
	TEV.SailData.ss_xdep = ss_xdep;
	TEV.SailData.ss_zdep = ss_zdep;
	TEV.SailData.fMaxAngle = fMaxAngle;
	TEV.SailData.fHoleDepend = fHoleDepend;
}

float GetCurSpeedFromPoint(ref chr, float fWindShipAngle)
{
	int iRealShip = int(chr.ship.type);
	int iShipType = int(RealShips[iRealShip].basetype);
	ref rShip = &ShipsTypes[iShipType];
	float fAng = Radian2Degree(fWindShipAngle);
	int angStep = 360 / SHIP_SPEEDPOINT_QUANTITY;
	int iAngL = int(fAng / angStep) * angStep;
	int iAngR = iAngL + angStep;
	bool bAdvanced = false;
	if("tuning.rig" in &RealShips[iRealShip])
		bAdvanced = true;
	float fSpeedL = Ship_GetSpeedPoint(rShip, iAngL, bAdvanced);
	float fSpeedR = Ship_GetSpeedPoint(rShip, iAngR, bAdvanced);
	float fSpeed = Bring2Range(fSpeedL, fSpeedR, iAngL * 1.0, iAngR * 1.0, fAng);
//	log_info("Speedpoints: fAng " + fAng + ", iAngL " + iAngL + ", iAngR " + iAngR + ", fSpeedL " + fSpeedL + ", fSpeedR " + fSpeedR + ", итого " + fSpeed);
	return fSpeed;
}

float Ship_SimulateSpeed_Init(int iShipType, float fWindShipAngle)
{
	if(fWindShipAngle > PI)
		fWindShipAngle = 2 * PI - fWindShipAngle;
	if(fWindShipAngle < 0.0)
		fWindShipAngle = -fWindShipAngle;
	ref rShip = &ShipsTypes[iShipType];
	
	if("sails_data" !in rShip)
		return 0.0;
	
	aref arInitData = &rShip.sails_data;
	float fSailsSpeed = Ship_SimulateSailsSpeed(arInitData, fWindShipAngle, pchar);
	return fSailsSpeed;
}

float Ship_SimulateSailsSpeed(aref arData, float fWindShipAngle, ref chr, bool bInit = true)
{	
	// собираем параметры
	aref arNode, arSail;
	float fCurPower = 0.0;
	float fMaxPower = 0.0;
	for(int i = 0; i < @arData; i++)
	{
		arNode = GetAttributeN(arData, i);
		string sNode = GetAttributeName(arNode);
		for(int j = 0; j < @arNode; j++)
		{
			arSail = GetAttributeN(arNode, j);
			string sGroupNum = strright(GetAttributeName(arSail), strlen(GetAttributeName(arSail) - strlen("sail_")));
			float fHoles = 1.0;
			if(!bInit && ("ship.sails." + sNode + "." + sGroupNum + ".hc") in chr)
				fHoles = Ship_SimulateSailsHoles(arSail, int(chr.ship.sails.(sNode).(sGroupNum).hc));
			float fSailPower = Sail_SimulatePower(arSail, sNode, fWindShipAngle) * fHoles;
			fCurPower += fSailPower;
			fMaxPower += float(arSail.square);
		}
	}
	if(fMaxPower == 0.0)
		return 0.0;
	
	float fSpeed = fCurPower / fMaxPower;
	return fSpeed;
}

float Ship_SimulateSailsHoles(aref arSail, int holesNum)
{
	aref arSailData = &TEV.SailData;
	// вычисляем дырки
	int holesMax = (arSail.sType == "triangle") ? 10 : 12;
	float kHoles = 1.0 - holesNum / float(holesMax) * float(arSailData.fHoleDepend);
	return kHoles;
}

float Sail_SimulatePower(aref arSail, string sNode, float fWindShipAngle)
{
	string sType = arSail.type;	// тип паруса: "triangle", "rectangle", "trapecidal", "special"
	float fBaseSailAngle = float(arSail.base_angle);	// базовый угол установки ноды с парусом относительно модели корабля
	float fSquare = float(arSail.square);	// площадь паруса, она же maxSpeed из движка
	
	aref arSailData = &TEV.SailData;
	if("fMaxAngle" !in arSailData)
		return 0.0;

	// вычисляем угол
	bool isTurnSail = IsStrLeft(sNode, "rey_");	
	float fMaxAngle = float(TEV.SailData.fMaxAngle);
	float fWindSailAngle = isTurnSail ? Sail_SimulateAngle(sType, fWindShipAngle, fMaxAngle) : fWindShipAngle;
	
	// разбиваем на составляющие
	float fSailWindX = sin(fWindSailAngle);
	float fSailWindZ = cos(fWindSailAngle);
	float z = fSailWindZ * 0.5 + 0.5;
	if(z > 1.0)
		z = 1.0;
	float x = fSailWindX * ((fSailWindX < 0.0) ? (z - 1.0) : (1.0 - z));
	
	// получаем парусные коэффициенты
	float rMin, rX, rZ;
	if(sType == "triangle")
	{
		rMin = float(arSailData.ts_min);
		rX = float(arSailData.ts_xdep);
		rZ = float(arSailData.ts_zdep);
	}
	else if(sType == "trapecidal")
	{
		rMin = float(arSailData.fs_min);
		rX = float(arSailData.fs_xdep);
		rZ = float(arSailData.fs_zdep);
	}
	else
	{
		rMin = float(arSailData.ss_min);
		rX = float(arSailData.ss_xdep);
		rZ = float(arSailData.ss_zdep);
	}

	float kSail = rMin + x * rX + z * rZ;
	
	// итоговая мощность паруса
	float fPower = fSquare * kSail;
	
	return fPower;
}

float Sail_SimulateAngle(string sType, float fWindShipAngle, float fMaxAngle)
{
	float fSailShipAngle = 0.0;
	float eps = 0.02;
	float fStep = 0.05;
	float windAng;
	float oldWindAngl = 0.0;
	int n = 0;
	float fWindSailAngle = fWindShipAngle;
	while(true)
	{
		if(n > 1000)
			return fWindShipAngle;
		windAng = -sin(fWindSailAngle);
		windAng *= fMaxAngle;
		windAng -= oldWindAngl;
		if(abs(windAng) < eps)
			break;
		if(windAng > fStep) windAng = fStep;
		if(windAng < -fStep) windAng = -fStep;
		oldWindAngl += windAng;
		
		fSailShipAngle += ((sType == "rectangle") ? -windAng : windAng);
		fWindSailAngle = fWindShipAngle - fSailShipAngle;
		n++;
	}
	return fWindSailAngle;
}

#event_handler("Event_GetShipSpeedByAngle", "GetShipSpeedByAngle");
float GetShipSpeedByAngle()
{
	float fAngle = GetEventData();
	int iShipType = int(RealShips[int(pchar.ship.type)].basetype);
	return Ship_SimulateSpeed_Init(iShipType, fAngle) * GetCurSpeedFromPoint(pchar, fAngle);
}

#event_handler("Event_GetSpeedColor", "GetSpeedColor");
int GetSpeedColor()
{
	float fSpeed = GetEventData();
	
	if("speed_colors" !in pchar)
		SetSpeedColors();
	
	aref arColors = &pchar.speed_colors;
	float cSpeed1, cSpeed2;
	int color1, color2;
	cSpeed1 = -1.0;
	cSpeed2 = -1.0;
	string sAttr;
	for(int i = 1; i < @arColors; i++)
	{
		sAttr = "a" + i;
		cSpeed1 = float(arColors.(sAttr).speed);
		color1 = int(arColors.(sAttr).color);
		sAttr = "a" + (i + 1);
		cSpeed2 = float(arColors.(sAttr).speed);
		color2 = int(arColors.(sAttr).color);
		if(cSpeed1 <= fSpeed && fSpeed <= cSpeed2)
			break;
	}
	if(cSpeed1 < 0.0 || cSpeed2 < 0.0)
		return argb(255, 255, 255, 255);
	int alpha = (color1 >> 24);
	int red = (color1 >> 16) & 255;
	int green = (color1 >> 8) & 255;
	int blue = color1 & 255;
	int alpha2 = color2 >> 24;
	int red2 = (color2 >> 16) & 255;
	int green2 = (color2 >> 8) & 255;
	int blue2 = color2 & 255;
	
	float k = (fSpeed - cSpeed1) / (cSpeed2 - cSpeed1)
	alpha += int(k * (alpha2 - alpha));
	red += int(k * (red2 - red));
	green += int(k * (green2 - green));
	blue += int(k * (blue2 - blue));
	
	return argb(alpha, red, green, blue);
}

void SetSpeedColors()
{
	DeleteAttribute(pchar, "speed_colors");
	switch(iVisualScheme)
	{
		case 0:	// градиент
			pchar.speed_colors.a1.speed = 0.0;
			pchar.speed_colors.a1.color = argb(225, 255, 180, 0);//красный резерв
			pchar.speed_colors.a2.speed = 0.3;
			pchar.speed_colors.a2.color = argb(225, 255, 0, 0);//красный
			pchar.speed_colors.a3.speed = 0.5;
			pchar.speed_colors.a3.color = argb(225, 255, 100, 0);//оранжевый
			pchar.speed_colors.a4.speed = 0.7;
			pchar.speed_colors.a4.color = argb(225, 255, 255, 0);//желтый
			pchar.speed_colors.a5.speed = 1.0;
			pchar.speed_colors.a5.color = argb(225, 0, 255, 0);//зелёный
		break;
		case 1:	// градиент низкой интенсивности
			pchar.speed_colors.a1.speed = 0.0;
			pchar.speed_colors.a1.color = argb(175, 255, 180, 0);//красный резерв
			pchar.speed_colors.a2.speed = 0.3;
			pchar.speed_colors.a2.color = argb(185, 255, 0, 0);//красный
			pchar.speed_colors.a3.speed = 0.5;
			pchar.speed_colors.a3.color = argb(195, 255, 100, 0);//оранжевый
			pchar.speed_colors.a4.speed = 0.7;
			pchar.speed_colors.a4.color = argb(195, 255, 255, 0);//желтый
			pchar.speed_colors.a5.speed = 1.0;
			pchar.speed_colors.a5.color = argb(195, 0, 255, 0);//зелёный
		break;
		case 2:	// температура/интенсивность
			pchar.speed_colors.a1.speed = 0.0;
			pchar.speed_colors.a1.color = argb(200, 150, 180, 235);//холодный резерв
			pchar.speed_colors.a2.speed = 0.3;
			pchar.speed_colors.a2.color = argb(210, 155, 185, 230);//холодный
			pchar.speed_colors.a3.speed = 0.5;
			pchar.speed_colors.a3.color = argb(220, 195, 175, 175);//нейтральный переход
			pchar.speed_colors.a4.speed = 0.7;
			pchar.speed_colors.a4.color = argb(235, 235, 190, 110);//тёплый
			pchar.speed_colors.a5.speed = 0.9;
			pchar.speed_colors.a5.color = argb(255, 255, 210, 80);//янтарь
			pchar.speed_colors.a6.speed = 1.0;
			pchar.speed_colors.a6.color = argb(255, 255, 150, 80);//янтарь тёмный
		break;
		case 3:	// протанопия
			pchar.speed_colors.a1.speed = 0.0;
			pchar.speed_colors.a1.color = argb(255, 0, 64, 255);    // глубокий синий резерв
			pchar.speed_colors.a2.speed = 0.3;
			pchar.speed_colors.a2.color = argb(255, 64, 128, 255);  // яркий синий
			pchar.speed_colors.a3.speed = 0.5;
			pchar.speed_colors.a3.color = argb(255, 255, 255, 255); // белый переход
			pchar.speed_colors.a4.speed = 0.7;
			pchar.speed_colors.a4.color = argb(255, 255, 255, 0);   // жёлтый
			pchar.speed_colors.a5.speed = 1.0;
			pchar.speed_colors.a5.color = argb(255, 255, 220, 0);   // насыщенный жёлтый максимум
		break;
		case 4:	// дейтеранопия
			pchar.speed_colors.a1.speed = 0.0;
			pchar.speed_colors.a1.color = argb(255, 0, 64, 255);    // глубокий синий резерв
			pchar.speed_colors.a2.speed = 0.3;
			pchar.speed_colors.a2.color = argb(255, 64, 128, 255);  // яркий синий
			pchar.speed_colors.a3.speed = 0.5;
			pchar.speed_colors.a3.color = argb(255, 255, 255, 255); // белый переход
			pchar.speed_colors.a4.speed = 0.7;
			pchar.speed_colors.a4.color = argb(255, 255, 255, 0);   // жёлтый
			pchar.speed_colors.a5.speed = 1.0;
			pchar.speed_colors.a5.color = argb(255, 255, 220, 0);   // насыщенный жёлтый максимум
		break;
		case 5:	// тританопия
			pchar.speed_colors.a1.speed = 0.0;
			pchar.speed_colors.a1.color = argb(255, 0, 255, 0);
			pchar.speed_colors.a2.speed = 0.3;
			pchar.speed_colors.a2.color = argb(255, 255, 255, 255);
			pchar.speed_colors.a3.speed = 0.5;
			pchar.speed_colors.a3.color = argb(255, 0, 0, 255);
			pchar.speed_colors.a4.speed = 0.7;
			pchar.speed_colors.a4.color = argb(255, 0, 255, 0);
			pchar.speed_colors.a5.speed = 1.0;
			pchar.speed_colors.a5.color = argb(255, 255, 0, 0);
		break;
	}
}

void ExportSpeedPoints(int iShipType)
{
	ref rShip = &ShipsTypes[iShipType];
	int iAng;
	int iStep = 360 / SHIP_SPEEDPOINT_QUANTITY;
	float fSpeedPoint;
	trace("// === " + rShip.name + " ===");
	trace("makeref(refShip, ShipsTypes[" + iShipType + "]);")
	for(int i = 0; i <= SHIP_SPEEDPOINT_QUANTITY / 2; i++)
	{
		iAng = i * iStep;
		fSpeedPoint = Ship_GetSpeedPoint(rShip, iAng, false);
		trace("Ship_SetSpeedPoint(refShip, " + iAng + ", " + fSpeedPoint + ");");
	}
}

void MassExportSpeedPoints()
{
	ref rShip;
	for(int i = 0; i < SHIP_TYPES_QUANTITY; i++)
	{
		if(!Ship_HasSails(i))
			continue;
		rShip = &ShipsTypes[i];
		ExportSpeedPoints(i);
	}
}

void ExportAdvancedSpeedPoints(int iShipType)
{
	ref rShip = &ShipsTypes[iShipType];
	int iAng;
	int iStep = 360 / SHIP_SPEEDPOINT_QUANTITY;
	float fSpeedPoint;
	trace("// === " + rShip.name + " ===");
	trace("makeref(refShip, ShipsTypes[" + iShipType + "]);")
	for(int i = 0; i <= SHIP_SPEEDPOINT_QUANTITY / 2; i++)
	{
		iAng = i * iStep;
		fSpeedPoint = Ship_GetSpeedPoint(rShip, iAng, true);
		trace("Ship_SetAdvancedSpeedPoint(refShip, " + iAng + ", " + fSpeedPoint + ");");
	}
}

void MassExportAdvancedSpeedPoints()
{
	ref rShip;
	for(int i = 0; i < SHIP_TYPES_QUANTITY; i++)
	{
		if(!Ship_HasSails(i))
			continue;
		rShip = &ShipsTypes[i];
		ExportAdvancedSpeedPoints(i);
	}
}

void Ship_SetAdvancedSpeedPoint(ref rShip, int iAng, float fSpeed)
{
	if(iAng > 180)
		iAng = 360 - iAng;
	string sPoint = "a" + iAng;
	rShip.adv_speed_points.(sPoint) = fSpeed;
}
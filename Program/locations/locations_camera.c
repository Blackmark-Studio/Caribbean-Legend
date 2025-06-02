
#define LOCCAMERA_FOLLOW	1
#define LOCCAMERA_TOPOS		2
#define LOCCAMERA_FREE		3

// Hokkins: радиус наземной камеры
#define DEFAULT_CAM_RAD 3.0
#define DEFAULT_CAM_RAD_DEN 0.22

// Warship 20.07.09 Новое
#define LOCCAMERA_MAX_STATES 15
#define LOCCAMERA_ROTATE "Rotate"
#define LOCCAMERA_FLYTOPOS "FlyToPosition"
#define LOCCAMERA_NEARHERO "LockNearHero"

// evganat - меняем целевую точку камеры
#define LOCCAMERA_LOOKTOHERO "LookToHero"
#define LOCCAMERA_LOOKTOPOINT "LookToPoint"
#define LOCCAMERA_LOOKTOANGLE "LookToAngle"

#event_handler("frame", "locCameraUpdate");

Object objLocCameraStates[LOCCAMERA_MAX_STATES];
int iLocCameraCurState = -1;

int locCameraCurMode;
bool locCameraEnableSpecialMode;
bool locCameraEnableFree;

void locCameraInit()
{
	locCameraEnableFree = false;
	locCameraEnableSpecialMode = false;
	//locCameraEnableFree = true;
	locCameraCurMode = LOCCAMERA_FOLLOW;
}

void locCameraSetRadius(float fRadius)
{
	SendMessage(&locCamera, "lf", MSG_CAMERA_SET_RADIUS, fRadius);
}

//Set camera follow mode
bool locCameraFollow()
{
	return locCameraFollowEx(false);
}

bool locCameraFollowEx(bool isTeleport)
{
	if(IsEntity(&locCamera) == 0) return false;
	bool res;
	if(isTeleport)
		res = SendMessage(&locCamera, "ll", MSG_CAMERA_FOLLOW, isTeleport);
	else
		res = SendMessage(&locCamera, "l", MSG_CAMERA_FOLLOW);
	locCameraCurMode = LOCCAMERA_FOLLOW;
	return res;
}

//Set camera toPos mode
bool locCameraToPos(float x, float y, float z, bool isTeleport)
{
	return locCameraToPosEx(x, y, z, isTeleport, 1.0);
}

bool locCameraToPosEx(float x, float y, float z, bool isTeleport, float fMorphSpeed)
{
	if(IsEntity(&locCamera) == 0) return false;
	if(locCameraEnableFree == true) return true;
	bool res = SendMessage(&locCamera, "lffflf", MSG_CAMERA_TOPOS, x, y, z, isTeleport, fMorphSpeed);
	locCameraCurMode = LOCCAMERA_TOPOS;
	return res;
}

//Set camera move mode (speed meter per second)
bool locCameraFree()
{
	if(IsEntity(&locCamera) == 0) return false;
	bool res = SendMessage(&locCamera, "l", MSG_CAMERA_FREE);
	locCameraCurMode = LOCCAMERA_FREE;
	return res;
}

//
bool locCameraLock(float ax)
{
	if(IsEntity(&locCamera) == 0) return false;
	bool res = SendMessage(&locCamera, "lf", MSG_CAMERA_MOVE, ax);
	return res;
}


void locCameraSleep(bool isSleep)
{
	SendMessage(&locCamera, "ll", MSG_CAMERA_SLEEP, isSleep);
}

void locCameraSwitch()
{
	if(locCameraEnableFree == false) return;
	string controlName = GetEventData();
	if(controlName != "ChrCamCameraSwitch") return;
	if(locCameraCurMode != LOCCAMERA_FREE)
	{
		locCameraFree();
	}else{
		locCameraFollow();
	}
}

void locCameraSetSpecialMode(bool isEnable)
{
	locCameraEnableSpecialMode = isEnable;
}

#event_handler("EventGetSpecialMode", "locCameraGetSpecialMode");
int locCameraGetSpecialMode()
{
	return false;
}   
void LoadTrackCamera(string sTrackName,float fTrackTime,aref arTrackPause)
{
	SendMessage(&locCamera, "lsfa", -2, sTrackName, fTrackTime, arTrackPause);
}

void TurnOffTrackCamera()
{
	SendMessage(&locCamera, "l", -3);
}
// boal -->
void locCameraTarget(ref _char)
{
    SendMessage(&locCamera, "li", MSG_CAMERA_SETTARGET, _char);
}
// boal <--	 
// to_do нет в ядре  
bool locCameraFromToPos(float from_x,float from_y,float from_z, bool isTeleport, float to_x,float to_y,float to_z)
{
	if(IsEntity(&locCamera) == 0)
		return false;
	if(locCameraEnableFree == true)
		return true;
	bool res = SendMessage(&locCamera, "lffflfffl", -4, from_x, from_y, from_z, isTeleport, to_x, to_y, to_z, true);
	locCameraCurMode = LOCCAMERA_TOPOS;
	return res;
}

bool locCameraFromToPosEx(float from_x, float from_y, float from_z, bool isTeleport, float to_x, float to_y, float to_z, bool targetChr)
{
	if(IsEntity(&locCamera) == 0)
		return false;
	if(locCameraEnableFree == true)
		return true;
	bool res = SendMessage(&locCamera, "lffflfffl", -4, from_x, from_y, from_z, isTeleport, to_x, to_y, to_z, targetChr);
	locCameraCurMode = LOCCAMERA_TOPOS;
	return res;
}

/////////////////////////////////////////////////////////////////////////////////////////
//							Warship 20.07.09 НОВОЕ - СНИМАЕМ КИНО
/////////////////////////////////////////////////////////////////////////////////////////

// Функция запуска вращения камеры вокруг персонажа.
// Параметры:
// float  _offsetX ... _offsetZ - смещение камеры относительно текущей позиции персонажа
// float _rotateX, _rotateY - скорость фращения по данной оси, от 0.01 и меньше до 0.3, может быть отрицательна
// float _radius - радиус, он же дистанция от начальных точек до камеры
// float _startAngle- начальный угол, откуда крутим
// int _time - время вращения В КАДРАХ. Она секунда - в среднем 30 кадров, но если учитывать тормоза, то может быть и 10
// bool _teleport - если true, переместится в заданную точку мгновенно, иначе - плавный полет
bool locCameraRotateAroundHero(float _offsetX, float _offsetY, float _offsetZ, float _rotateX, float _rotateY,  float _radius, float _startAngle, int _time)
{
	ref curCameraState;
	int cameraCurState = locCameraGetFirstEmptyState();
	float charX, charY, charZ;
	
	if(cameraCurState == -1 || !GetCharacterPos(PChar, &charX, &charY, &charZ)) return false;
	
	curCameraState = &objLocCameraStates[cameraCurState];
	curCameraState.curCameraX = charX + _offsetX;
	curCameraState.curCameraY = charY + _offsetY;
	curCameraState.curCameraZ = charZ + _offsetZ;
	curCameraState.offsetX = _offsetX;
	curCameraState.offsetY = _offsetY;
	curCameraState.offsetZ = _offsetZ;
	curCameraState.rotateX = _rotateX;
	curCameraState.rotateY = _rotateY;
	curCameraState.rotateRadius = _radius;
	curCameraState.time = _time;
	curCameraState.angle = _startAngle;
	curCameraState.type = LOCCAMERA_ROTATE; // Тип камеры
	
	if(iLocCameraCurState == -1) iLocCameraCurState = 0;
	
	return true;
}


bool locCameraSetSpeedpoint(int spNum, float accel, float timer)
{
	if(iLocCameraCurState == -1)
		return false;
	
	ref curCameraState = &objLocCameraStates[iLocCameraCurState];
	string sPoint = "point" + spNum;
	curCameraState.speedpoints.(sPoint).timer = timer;
	curCameraState.speedpoints.(sPoint).accel = accel * GetRealDeltaTime() / timer;
}

void locCameraSetCurSpeedpoint(int spNum)
{
	if(iLocCameraCurState == -1)
		return;
	ref curCameraState = &objLocCameraStates[iLocCameraCurState];
	if(!CheckAttribute(curCameraState, "speedpoints"))
		return;
	
	curCameraState.speedpoints.cur = spNum;
}

// Полет камеры от начальных точек _startX ... _startZ до конечных точек _endX ... _endZ
// float _speed - множитель скорости в режиме полета _time == -1. Если _speed == 1, то это стандартная скорость
// int _time - кол-во кадров, за которое должно долететь. Если -1, то высчитывается исходя из расстояния
// bool _fromCurCameraPos - если true, то при переходе на эту функци полета, начальная позиция будет считаться как текущая позиция камеры
void locCameraFlyToPosition(ref curCameraState, float _startX, float _startY, float _startZ, float _endX, float _endY, float _endZ, float _speed, int _time)
{
	float distance = GetDistance3D(_startX, _startY, _startZ, _endX, _endY, _endZ);

	curCameraState.curCameraX = _startX;
	curCameraState.curCameraY = _startY;
	curCameraState.curCameraZ = _startZ;
	curCameraState.endCameraX = _endX;
	curCameraState.endCameraY = _endY;
	curCameraState.endCameraZ = _endZ;
	
	if(_time == -1)
	{
		curCameraState.speedX = (_endX - _startX) / (distance * (1 / _speed));
		curCameraState.speedY = (_endY - _startY) / (distance * (1 / _speed));
		curCameraState.speedZ = (_endZ - _startZ) / (distance * (1 / _speed));
	}
	else
	{
		curCameraState.speedX = (_endX - _startX) / _time;
		curCameraState.speedY = (_endY - _startY) / _time;
		curCameraState.speedZ = (_endZ - _startZ) / _time;
	}
	
	curCameraState.speed = _speed;
	curCameraState.time = _time;
	curCameraState.type = LOCCAMERA_FLYTOPOS; // Тип камеры
	
	if(iLocCameraCurState == -1) iLocCameraCurState = 0;
}

bool locCameraFlyToPositionLookToHero(float _startX, float _startY, float _startZ, float _endX, float _endY, float _endZ, float _speed, int _time)
{
	int iCameraCurState = locCameraGetFirstEmptyState();
	if(iCameraCurState == -1)
		return false;
	ref curCameraState = &objLocCameraStates[iCameraCurState];
	locCameraFlyToPosition(curCameraState, _startX, _startY, _startZ, _endX, _endY, _endZ, _speed, _time);
	curCameraState.lookTo = LOCCAMERA_LOOKTOHERO;	// смотрим на ГГ
	return true;
}

bool locCameraFlyToPositionLookToPoint(float _startX, float _startY, float _startZ, float _endX, float _endY, float _endZ, float _lookToX, float _lookToY, float _lookToZ, float _speed, int _time)
{
	int iCameraCurState = locCameraGetFirstEmptyState();
	if(iCameraCurState == -1)
		return false;
	ref curCameraState = &objLocCameraStates[iCameraCurState];
	locCameraFlyToPosition(curCameraState, _startX, _startY, _startZ, _endX, _endY, _endZ, _speed, _time);
	curCameraState.lookTo = LOCCAMERA_LOOKTOPOINT;	// смотрим на точку
	curCameraState.lookTo.x = _lookToX;
	curCameraState.lookTo.y = _lookToY;
	curCameraState.lookTo.z = _lookToZ;
	return true;
}

bool locCameraFlyToPositionLookToOffset(float _startX, float _startY, float _startZ, float _endX, float _endY, float _endZ, float _offsetX, float _offsetY, float _offsetZ, float _speed, int _time)
{
	int iCameraCurState = locCameraGetFirstEmptyState();
	if(iCameraCurState == -1)
		return false;
	ref curCameraState = &objLocCameraStates[iCameraCurState];
	locCameraFlyToPosition(curCameraState, _startX, _startY, _startZ, _endX, _endY, _endZ, _speed, _time);
	curCameraState.lookTo = LOCCAMERA_LOOKTOANGLE;	// смотрим под углом
	curCameraState.lookTo.offsetX = _offsetX;
	curCameraState.lookTo.offsetY = _offsetY;
	curCameraState.lookTo.offsetZ = _offsetZ;
	return true;
}

bool locCameraFlyToPositionLookToAngle(float _startX, float _startY, float _startZ, float _endX, float _endY, float _endZ, float _ax, float _ay, float _speed, int _time)
{
	int iCameraCurState = locCameraGetFirstEmptyState();
	if(iCameraCurState == -1)
		return false;
	ref curCameraState = &objLocCameraStates[iCameraCurState];
	locCameraFlyToPosition(curCameraState, _startX, _startY, _startZ, _endX, _endY, _endZ, _speed, _time);
	curCameraState.lookTo = LOCCAMERA_LOOKTOANGLE;	// смотрим под углом
	float ax = _ax * PI / 180.0;
	float ay = _ay * PI / 180.0;
	curCameraState.lookTo.offsetX = cos(ax) * sin(ay);
	curCameraState.lookTo.offsetY = sin(ax);
	curCameraState.lookTo.offsetZ = cos(ax) * cos(ay);
	return true;
}

// Фиксирование камеры в определённой точке относительно ГГ
// float _offsetX ... _offsetZ - смещение относительно координат ГГ, для определения точки, где будет находиться камера
// int _time - кол-во кадров, сколько будет висеть. Если -1 - будет висеть вечно
// bool _canRotate - если true, то камера будет крутиться вместе с персонажем
bool locCameraLockNearHero(float _offsetX, float _offsetY, float _offsetZ, int _time, bool _canRotate)
{
	ref curCameraState;
	int cameraCurState = locCameraGetFirstEmptyState();
	float charX, charY, charZ, offsetAY;
	
	if(cameraCurState == -1 || !GetCharacterPos(PChar, &charX, &charY, &charZ)) return false;
	
	offsetAY = atan2(_offsetZ, _offsetX);
	
	if(_offsetX > 0 && _offsetZ > 0)
	{
		offsetAY = offsetAY + PI;
	}
	
	curCameraState = &objLocCameraStates[cameraCurState];
	curCameraState.curCameraX = charX;
	curCameraState.curCameraY = charY;
	curCameraState.curCameraZ = charZ;
	curCameraState.offsetX = _offsetX;
	curCameraState.offsetY = _offsetY;
	curCameraState.offsetZ = _offsetZ;
	curCameraState.time = _time;
	curCameraState.canRotate = _canRotate;
	curCameraState.offsetAY = offsetAY;
	curCameraState.type = LOCCAMERA_NEARHERO; // Тип камеры
	
	if(iLocCameraCurState == -1) iLocCameraCurState = 0;
	
	return true;
}

int locCameraGetFirstEmptyState()
{
	for(int i = 0; i < LOCCAMERA_MAX_STATES; i++)
	{
		if(!CheckAttribute(&objLocCameraStates[i], "time"))
		{
			return i;
		}
	}
	
	return -1;
}

// Переход к следующей функции установки камеры
// Последовательность методов задается, например, так:
// locCameraRotateAroundHero(0.0, 1.0, 0.0, 0.03, 0.0, 3.0, 0.0, 200);
// locCameraRotateAroundHero(0.0, 1.0, 0.0, 0.0, 0.01, 5.0, 0.0, 150);
// locCameraRotateAroundHero(0.0, 1.0, 0.0, -0.03, 0.03, 7.0, 0.0, 225);
// В результате получаем последовательные полеты камеры
void locCameraNextState()
{
	if (CheckAttribute(PChar, "FuncCameraFly"))
	{
		locCameraResetState();
		string func = Pchar.FuncCameraFly;
		call func();
		return;
	}
	ref prevCamera, curCamera, nextCamera;
	float distance;
	int time;
	
	prevCamera = &objLocCameraStates[iLocCameraCurState];
	DeleteAttribute(prevCamera, "time"); // Критерий ненужность
	iLocCameraCurState++;
	
	curCamera = &objLocCameraStates[iLocCameraCurState];
	
	if(iLocCameraCurState == LOCCAMERA_MAX_STATES || !CheckAttribute(&curCamera, "curCameraX"))
	{
		locCameraResetState();
		return;
	}
	
	time = sti(curCamera.time);
	
	Log_TestInfo("locCameraNextState() == " + curCamera.type); 
}

// Сброс специальных состояний камеры - привязывание к персонажу
void locCameraResetState()
{
	locCameraFollow();
	
	iLocCameraCurState = -1;
	
	// Потрем все
	for(int i = 0; i < LOCCAMERA_MAX_STATES; i++)
	{
		DeleteAttribute(&objLocCameraStates[i], "");
	}
	
	//Log_TestInfo("locCameraResetState()");
}

// Обновление позиции камеры при входе в кадр
void locCameraUpdate()
{
	ref curCameraState; 
	float charX, charY, charZ, charAY;
	float offsetX, offsetZ;
	float rotateRadius, rotateAngle;
	float time; // Здесь время дробное, т.к. учитывается ещё ускорение времени
	
	float accel = 0.0;
	float kSpeedTimer = -1.0;
	string sPoint = "";
	float dltTime = GetRealDeltaTime();
	
	float timeScale = 1 + TimeScaleCounter * 0.25; // Текущее ускорение времени
	
	if(iLocCameraCurState != -1 && !sti(InterfaceStates.Launched))
	{
		if(GetCharacterPos(PChar, &charX, &charY, &charZ))
		{
			curCameraState = &objLocCameraStates[iLocCameraCurState];
			
			time = stf(curCameraState.time);
			
			bool bSetPoint = false;
			
			if(CheckAttribute(curCameraState, "speedpoints.cur"))
			{
				sPoint = "point" + curCameraState.speedpoints.cur;
				accel = stf(curCameraState.speedpoints.(sPoint).accel);
				kSpeedTimer = stf(curCameraState.speedpoints.(sPoint).timer);
			}
			
			switch(curCameraState.type)
			{
				case LOCCAMERA_ROTATE:
					rotateRadius = stf(curCameraState.rotateRadius);
					rotateAngle = stf(curCameraState.angle);
					
					// X rotation
					if(stf(curCameraState.rotateX) != 0.0)
					{
						curCameraState.rotateX = stf(curCameraState.rotateX) + accel * dltTime;
						curCameraState.curCameraX = charX + sin(rotateAngle) * rotateRadius + stf(curCameraState.offsetX);
						curCameraState.curCameraZ = charZ + cos(rotateAngle) * rotateRadius + stf(curCameraState.offsetZ);
						curCameraState.angle = rotateAngle + stf(curCameraState.rotateX) * timeScale;
					}
					else // Иначе просто обновление
					{
						curCameraState.curCameraX = charX + stf(curCameraState.offsetX);
						curCameraState.curCameraZ = charZ + stf(curCameraState.offsetZ);
					}
					
					// Y rotation
					if(stf(curCameraState.rotateY) != 0.0)
					{
						curCameraState.rotateY = stf(curCameraState.rotateY) + accel * dltTime;
						curCameraState.curCameraY = charY + cos(rotateAngle) * rotateRadius + stf(curCameraState.offsetY);
						curCameraState.curCameraX = charX + sin(rotateAngle) * rotateRadius + stf(curCameraState.offsetX);
						curCameraState.angle = rotateAngle + stf(curCameraState.rotateY) * timeScale;
					}
					else
					{
						curCameraState.curCameraY = charY + stf(curCameraState.offsetY);
					}
				break;
				
				case LOCCAMERA_FLYTOPOS:
					curCameraState.speedX = stf(curCameraState.speedX) + accel * dltTime;
					curCameraState.speedY = stf(curCameraState.speedY) + accel * dltTime;
					curCameraState.speedZ = stf(curCameraState.speedZ) + accel * dltTime;
					curCameraState.curCameraX = stf(curCameraState.curCameraX) + stf(curCameraState.speedX) * timeScale;
					curCameraState.curCameraY = stf(curCameraState.curCameraY) + stf(curCameraState.speedY) * timeScale;
					curCameraState.curCameraZ = stf(curCameraState.curCameraZ) + stf(curCameraState.speedZ) * timeScale;
					if(CheckAttribute(curCameraState, "lookTo") && curCameraState.lookTo != LOCCAMERA_LOOKTOHERO)
					{
						if(curCameraState.lookTo == LOCCAMERA_LOOKTOANGLE)
						{
							curCameraState.lookTo.x = stf(curCameraState.curCameraX) + stf(curCameraState.lookTo.offsetX);
							curCameraState.lookTo.y = stf(curCameraState.curCameraY) + stf(curCameraState.lookTo.offsetY);
							curCameraState.lookTo.z = stf(curCameraState.curCameraZ) + stf(curCameraState.lookTo.offsetZ);
						}
						//Log_TestInfo("camPos = " + curCameraState.curCameraX + ", " + curCameraState.curCameraY + ", " + curCameraState.curCameraZ + ", lookTo = " + curCameraState.lookTo.x + ", " + curCameraState.lookTo.y + ", " + curCameraState.lookTo.z);
						locCameraFromToPosEx(stf(curCameraState.curCameraX), stf(curCameraState.curCameraY), stf(curCameraState.curCameraZ), true, stf(curCameraState.lookTo.x), stf(curCameraState.lookTo.y), stf(curCameraState.lookTo.z), false);
						bSetPoint = true;
					}
				break;
				
				case LOCCAMERA_NEARHERO:
					offsetX = stf(curCameraState.offsetX);
					offsetZ = stf(curCameraState.offsetZ);
					
					if(sti(curCameraState.canRotate) && GetCharacterAy(PChar, &charAY))
					{
						curCameraState.curCameraX = charX + offsetX * sin(charAY + stf(curCameraState.offsetAY));
						curCameraState.curCameraZ = charZ + offsetZ * cos(charAY + stf(curCameraState.offsetAY));
					}
					else
					{
						curCameraState.curCameraX = charX + offsetX;
						curCameraState.curCameraZ = charZ + offsetZ;
					}
					
					curCameraState.curCameraY = charY + stf(curCameraState.offsetY);
				break;
			}
			
			if(!bSetPoint)
				locCameraToPos(stf(curCameraState.curCameraX), stf(curCameraState.curCameraY), stf(curCameraState.curCameraZ), true);
			
			if(time != -1.0)
			{
				time -= 1 * timeScale; // Учет ускорения времени
				curCameraState.time = time;
			}
			
			if(kSpeedTimer > -1.0)
			{
				kSpeedTimer -= dltTime;
				if(kSpeedTimer <= 0.0)
				{
					sPoint = "point" + (sti(curCameraState.speedpoints.cur) + 1);
					if(CheckAttribute(curCameraState, "speedpoints."+sPoint))
						curCameraState.speedpoints.cur = sti(curCameraState.speedpoints.cur) + 1;
					else
						DeleteAttribute(curCameraState, "speedpoints");
				}
				else
					curCameraState.speedpoints.(sPoint).timer = kSpeedTimer;
			}
			
			if(time <= 0.0 && time != -1.0)
			{
				locCameraNextState();
			}
			
			// Тут высчитываем попадание в нужную точку
			if(time == -1.0 && curCameraState.type == LOCCAMERA_FLYTOPOS)
			{
				if(stf(curCameraState.curCameraX) + stf(curCameraState.speedX) * timeScale >= stf(curCameraState.endCameraX) &&
					stf(curCameraState.curCameraX) - stf(curCameraState.speedX) * timeScale <= stf(curCameraState.endCameraX) &&
					stf(curCameraState.curCameraY) + stf(curCameraState.speedY) * timeScale >= stf(curCameraState.endCameraY) &&
					stf(curCameraState.curCameraY) - stf(curCameraState.speedY) * timeScale <= stf(curCameraState.endCameraY) &&
					stf(curCameraState.curCameraZ) + stf(curCameraState.speedZ) * timeScale >= stf(curCameraState.endCameraZ) &&
					stf(curCameraState.curCameraZ) - stf(curCameraState.speedZ) * timeScale <= stf(curCameraState.endCameraZ))
				{
					locCameraNextState();
				}
			}
		}
	}
}

#event_handler("AimingActive", "AimingActive");
void AimingActive()
{
	int isActive = GetEventData();
	
	if(isActive)
	{
		locCameraSetRadius(stf(locCamera.maxRadius)*0.75);
		locCamera.zoom.lock = true;
		BI_CrosshairSet();
		SendMessage(&objLandInterface, "ll", MSG_BATTLE_LAND_CROSSHAIR_SHOW, 1);
	}
	else
	{
		if(!CheckAttribute(locCamera, "zoom"))
			locCamera.zoom = 0.75;
		if(CheckAttribute(locCamera, "zoom.lock"))
			DeleteAttribute(&locCamera, "zoom.lock");
		locCameraSetRadius(stf(locCamera.maxRadius)*stf(locCamera.zoom));
		SendMessage(&objLandInterface, "ll", MSG_BATTLE_LAND_CROSSHAIR_SHOW, 0);
	}
}
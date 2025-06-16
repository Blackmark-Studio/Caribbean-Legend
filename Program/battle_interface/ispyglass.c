// Sith Переделка для CLE
#define ISG_CHARGE_BALLS		0
#define ISG_CHARGE_GRAPES		1
#define ISG_CHARGE_KNIPPELS		2
#define ISG_CHARGE_BOMBS		3

object objISpyGlass;

void InterfaceSpyGlassInit(bool bNet)
{
	FillISpyGlassParameters();
	CreateEntity(&objISpyGlass,"ispyglass");
	DeleteAttribute(&objISpyGlass,"parameters");
	TelescopeInitParameters(&Telescope);

	LayerAddObject(SEA_EXECUTE,&objISpyGlass,-1);
	LayerAddObject(SEA_REALIZE,&objISpyGlass,-1);
	SetEventHandler("SetTelescopeInfo","SetSpyGlassData",0);
		
	SetEventHandler("ReleaseTelescopeInfo","ResetSpyGlassData",0);
	SetEventHandler("BI_VISIBLE","CheckInterfaceVisible",0);
}

void InterfaceSpyGlassRelease()
{
	DelEventHandler("BI_VISIBLE","CheckInterfaceVisible");
	DelEventHandler("ReleaseTelescopeInfo","ResetSpyGlassData");
	DelEventHandler("SetTelescopeInfo","SetSpyGlassData");
	DeleteClass(&objISpyGlass);
}

void CheckInterfaceVisible()
{
	int vtype = GetEventData();
	if(vtype!=0) ResetSpyGlassData();
}

void SetSpyGlassData()
{
	int chrIdx = GetEventData();
	if(chrIdx<0) return;

	string sTextureName = "interfaces\le\battle_interface\ship_icons2.tga";
	string sBackCapTextureName = "interfaces\le\battle_interface\shipbackicon1.tga";
	float uvLeft = 0;
	float uvTop = 0;
	float uvRight = 0.125;
	float uvBottom = 0.125;

	int	shipHull = -1;
	int shipSail = -1;
	int shipCrew = -1;
	int shipCannons = -1;
	int shipMaxCannons = -1;
	int shipCharge = -1;
	int shipNation = -1;
	int shipClass = 1;
	float shipSpeed = -1.0;
	string shipName = "";
	string shipType = "";
	bool isFort;

	object tmpobj;
	aref arScopeItm;
	int tmpCharge;
	
	ref chref = GetCharacter(chrIdx);

	if(Items_FindItem( GetCharacterEquipByGroup(pchar,SPYGLASS_ITEM_TYPE), &arScopeItm) < 0)
    {
        makearef(arScopeItm,tmpobj);
    }

	if(!CheckAttribute(arScopeItm, "scope.show.nation") || sti(arScopeItm.scope.show.nation)!= 0)
	{
		shipNation = sti(chref.nation);
	}

	int nSailState = 1;
	float fSailSt = Ship_GetSailState(chref);
	if( fSailSt<0.3 ) {nSailState = 0;}
	else {
		if( fSailSt<0.6 ) {nSailState = 1;}
		else {nSailState = 2;}
	}
	
	int nFace = sti(chref.faceID);
//	Log_SetStringToLog("FaceID : " + nFace);
	string sCaptainName = GetCharacterFullName(chref.id);
	string sCaptainPerk = "";
	string sChargeName = "";
	int nDefenceSkill = GetCharacterSkill(chref,SKILL_DEFENCE);   // защита
	int nCannonSkill = GetCharacterSkill(chref,SKILL_CANNONS); // орудия
	int nAccuracySkill = GetCharacterSkill(chref,SKILL_ACCURACY); // меткость
	int nNavigationSkill = GetCharacterSkill(chref,SKILL_SAILING);  // навигация
	int nBoardingSkill = GetCharacterSkill(chref,SKILL_GRAPPLING);    // абордаж
	bool bSurrender = false;    // Око Мертвеца
	if( !CheckAttribute(arScopeItm,"scope.show.captain_skills") || sti(arScopeItm.scope.show.captain_skills)==0 ) {
		nDefenceSkill = -1;
		nCannonSkill = -1;
		nAccuracySkill = -1;
		nNavigationSkill = -1;
		nBoardingSkill = -1;
	}

	// Warship 08.07.09 Запрет спуска парусов
	// Показываем всегда иконку полных парусов, без этого - прыгает
	if(CheckAttribute(chref, "CanDropSails") && !sti(chref.CanDropSails))
	{
		nSailState = 2;
	}
	
	// Кэп "Мэри Селест" - его как бы и нету, поэтому показываем нули
	if((chref.ID == "MaryCelesteCapitan") || (CheckAttribute(pchar,"GenQuest.ShipSituation.Explosion")))
	{
		// Показываем нули в скилах
		nDefenceSkill = 0;
		nCannonSkill = 0;
		nAccuracySkill = 0;
		nNavigationSkill = 0;
		nBoardingSkill = 0;
	}

	// смотрим на форт
	if(CheckAttribute(chref,"Ship.Type")) 
	{
		int iShip = sti(chref.Ship.Type);
		if (iShip != SHIP_NOTUSED)
		{
			iShip = sti(RealShips[iShip].basetype);
			if(ShipsTypes[iShip].name == "fort")
			{
				isFort = true;
				if (CheckAttribute(arScopeItm,"scope.show.ship_type") && sti(arScopeItm.scope.show.ship_type)!=0 )
				{
					shipType = XI_ConvertString("Fort_Name");//boal fix
				}
				// boal -->
				if (CheckAttribute(arScopeItm,"scope.show.ship_name") && sti(arScopeItm.scope.show.ship_name)!=0 )
				{
					shipName =  chref.Ship.Name;
				}
				// boal <--
				if (CheckAttribute(arScopeItm,"scope.show.cannons") && sti(arScopeItm.scope.show.cannons)!=0 ) {
					shipCannons = Fort_GetCannonsQuantity(chref);
					if( !CheckAttribute(chref, "fort.Cannons.Quantity") ) {shipMaxCannons=0;}
					else {shipMaxCannons = sti(chref.Fort.Cannons.Quantity);}
				}
				if(CheckAttribute(arScopeItm,"scope.show.crew") && sti(arScopeItm.scope.show.crew)!=0 )
					{	shipCrew = GetCrewQuantity(chref);	}
				if( !CheckAttribute(arScopeItm,"scope.show.hull") || sti(arScopeItm.scope.show.hull)!=0 ) {
					if( CheckAttribute(chref,"ship.hp") && CheckAttribute(chref,"fort.hp") && stf(chref.Fort.hp)>0.0 ) {
						shipHull = makeint( stf(chref.ship.hp)/stf(chref.Fort.hp) * 100.0 );
					} else {
						shipHull = 100;
					}
				}
				if (CheckAttribute(arScopeItm,"scope.show.charge") && sti(arScopeItm.scope.show.charge)!=0 )
				{
					tmpCharge = sti(chref.Ship.Cannons.Charge.Type);
					switch(tmpCharge)
					{
						case GOOD_BALLS:
							 shipCharge=0;
							 sChargeName = XI_ConvertString("Balls");
							 break;
						case GOOD_GRAPES:
							 shipCharge=3;
							 sChargeName = XI_ConvertString("Grapes");
							 break;
						case GOOD_KNIPPELS:
							 shipCharge=2;
							 sChargeName = XI_ConvertString("Knippels");
							 break;
						case GOOD_BOMBS:
							 shipCharge=1;
							 sChargeName = XI_ConvertString("Bombs");
							 break;
					}
				}
	
				sTextureName = "interfaces\le\battle_interface\list_icons.tga";
				uvLeft = 0.8164;
				uvTop = 0.3828;
				uvRight = 0.8710;
				uvBottom = 0.4921;
				nSailState = -1;
			}
			// смотрим на корабль
			else
			{
				isFort = false;
				GetTextureUVForShip(iShip, &uvLeft, &uvTop, &uvRight, &uvBottom);

				shipClass = GetCharacterShipClass(chref);
				
				ref refShip;
				makeref(refShip, ShipsTypes[sti(RealShips[sti(chref.Ship.Type)].basetype)]);
				if (CheckAttribute(refShip, "modname"))
				{
					string largeFilePath = "interfaces\le\battle_interface\mods\"+refShip.modname+"\ship_icons2.tga.tx";
					sTextureName = largeFilePath;
				}
	
				if (CheckAttribute(arScopeItm,"scope.show.cannons") && sti(arScopeItm.scope.show.cannons)!=0 )
				{
					shipCannons = GetIntactCannonQuantity(chref);
					shipMaxCannons = GetCannonQuantity(chref);
				}
				if (CheckAttribute(arScopeItm,"scope.show.ship_name") && sti(arScopeItm.scope.show.ship_name)!=0 )
				{
					shipName =  chref.Ship.Name;
				}
				if (CheckAttribute(arScopeItm,"scope.show.ship_type") && sti(arScopeItm.scope.show.ship_type)!=0 )
				{
					shipType = XI_ConvertString(GetShipTypeName(chref));
				}		
				if (CheckAttribute(arScopeItm,"scope.show.hull") && sti(arScopeItm.scope.show.hull) == true )
				{
					shipHull = makeint(GetHullPercent(chref));
				}
				if (CheckAttribute(arScopeItm,"scope.show.sail") && sti(arScopeItm.scope.show.sail) == true )
				{
					shipSail = makeint(GetSailPercent(chref));
				}
				if (CheckAttribute(arScopeItm,"scope.show.crew") && sti(arScopeItm.scope.show.crew) == true )
				{
					shipCrew = GetCrewQuantity(chref);
				}
				if (CheckAttribute(arScopeItm,"scope.show.speed") && sti(arScopeItm.scope.show.speed) == true)
				{
					shipSpeed = stf(chref.Ship.speed.z) * stf(BattleInterface.ShipSpeedScaler);
				}
				if (CheckAttribute(arScopeItm,"scope.show.charge") && sti(arScopeItm.scope.show.charge) == true )
				{
					tmpCharge = sti(chref.Ship.Cannons.Charge.Type);
					switch(tmpCharge)
					{
						case GOOD_BALLS:
							 shipCharge=0;
							 sChargeName = XI_ConvertString("Balls");
							 break;
						case GOOD_GRAPES:
							 shipCharge=3;
							 sChargeName = XI_ConvertString("Grapes");
							 break;
						case GOOD_KNIPPELS:
							 shipCharge=2;
							 sChargeName = XI_ConvertString("Knippels");
							 break;
						case GOOD_BOMBS:
							 shipCharge=1;
							 sChargeName = XI_ConvertString("Bombs");
							 break;
					}
				}
				if (CheckAttribute(arScopeItm,"scope.show.CheckSurrender") && sti(arScopeItm.scope.show.CheckSurrender) != 0)
				{
					bSurrender = !CheckAttribute(chref, "DontRansackCaptain") && CheckForSurrender(pchar, chref, 1);
				}
			}
		}
	}
	if (CheckAttribute(arScopeItm,"scope.show.cannontype") && sti(arScopeItm.scope.show.cannontype)== true)
	{
		string CannonTypeName = "";
		
		int cannonIdx = sti(chref.Ship.Cannons.Type);
		int cannonGoodIdx = GetCannonGoodsIdxByType(cannonIdx);
		
		
		if (cannonGoodIdx != -1)
		{
			string cannonString = Goods[cannonGoodIdx].Name;
			
			if (sti(Cannon[cannonIdx].type) != CANNON_NAME_CULVERINE)
			{
				cannonString = cannonString + "s";
			}
			
			CannonTypeName = XI_ConvertString(cannonString);
		}
	}	
	
	if (CheckAttribute(arScopeItm,"scope.show.mushketshot") && sti(arScopeItm.scope.show.mushketshot) != 0  && CheckCharacterPerk(chref, "MusketsShoot") && !isFort)	
	{
		sCaptainName = sCaptainName;
		sCaptainPerk = XI_ConvertString("MushketVolley");
		sBackCapTextureName = "interfaces\le\battle_interface\charbackicon2.tga";
	}
	else
	{
		sCaptainName = sCaptainName;
		sCaptainPerk = "";
        if (isFort)
        {
            sBackCapTextureName = "interfaces\le\battle_interface\charbackicon3.tga";
        }
        else
        {
			sBackCapTextureName = "interfaces\le\battle_interface\charbackicon1.tga";
		}
	}	
    //sCaptainName = XI_ConvertString("Distance") + ": " + FloatToString(Ship_GetDistance2D(GetMainCharacter(), chref), 1) + "       " + sCaptainName;
    float fDistance = stf(FloatToString(Ship_GetDistance2D(GetMainCharacter(), chref), 1)); //boal
	SendMessage(&objISpyGlass,"lsslllfflllllllllllssslssl",MSG_ISG_UPDATE, shipName,shipType,  //boal
		shipHull,shipSail,shipCrew,	shipSpeed, fDistance,
		shipCannons,shipMaxCannons,
		shipCharge,shipNation, nSailState,nFace,
		nDefenceSkill,nCannonSkill,nAccuracySkill,nNavigationSkill,nBoardingSkill,
		sCaptainName,sCaptainPerk,"",shipClass,CannonTypeName, sChargeName, bSurrender);
	SendMessage(&objISpyGlass,"lsffff",MSG_ISG_SET_SHIPICON, sTextureName, uvLeft,uvTop,uvRight,uvBottom);
	uvLeft = 0;
	uvTop = 0;
	uvRight = 1.0;
	uvBottom = 1.0;
	SendMessage(&objISpyGlass,"lsffff",MSG_ISG_SET_CHARICON, sBackCapTextureName, uvLeft,uvTop,uvRight,uvBottom);
	SendMessage(&objISpyGlass,"ll",MSG_ISG_VISIBLE,true);
	// debug info -->
	if (bBettaTestMode)
	{
		ClearAllLogStrings();
		if (CheckAttribute(chref, "SeaAI.Task"))
		{
		    Log_SetStringToLog("shipType=" + GetCharacterShipType(chref) +
		                               " SeaAI.Task=" + chref.SeaAI.Task);
			if (CheckAttribute(chref, "SeaAI.Task.Target"))		                               
			{
		        sCaptainName = "none";
				if (sti(chref.SeaAI.Task.Target) != -1)  sCaptainName = Characters[sti(chref.SeaAI.Task.Target)].id;
		        
				Log_Info("SeaAI.Task.Target = " + chref.SeaAI.Task.Target + " id npc = " + sCaptainName);
			}		        
		}
		if (TestRansackCaptain && !bQuestLogShow && rand(20) == 4) // иначе не отжать кнопку
		{
		    pchar.SystemInfo.OnlyShowCharacter = true;
		    LaunchCharacter(chref);
		} 
		if (TestRansackCaptain && bQuestLogShow && rand(20) == 4) // иначе не отжать кнопку
		{
		    LaunchShipStateNPC(chref);
		} 
		Log_SetStringToLog("Cap_id = " + chref.id +" hp= " + makeint(chref.chr_ai.hp) + " rank= "+ chref.rank +
		                           " Moral= " + chref.ship.crew.morale);
		Log_SetStringToLog("Sailors = " + chref.Ship.Crew.Exp.Sailors +" Cannoners = " + chref.Ship.Crew.Exp.Cannoners + " Soldiers = "+ chref.Ship.Crew.Exp.Soldiers);
		Log_SetStringToLog("Ship.MaxCaliber=  " + RealShips[sti(chref.Ship.Type)].MaxCaliber +
		                           " Ship.Capacity =" + RealShips[sti(chref.Ship.Type)].Capacity  +
		                           " Ship.MaxCrew= " + RealShips[sti(chref.Ship.Type)].MaxCrew);

		Log_SetStringToLog("Ship.SpeedRate= " + RealShips[sti(chref.Ship.Type)].SpeedRate +
		                           " Ship.TurnRate =" + RealShips[sti(chref.Ship.Type)].TurnRate  +
		                           " Ship.HP=" + RealShips[sti(chref.Ship.Type)].HP +
								   " Ship.SP=" + chref.ship.SP);
		Log_Info("CheckForSurrender = " + CheckForSurrender(pchar, chref, 1));
		Log_Info("CheckLockTask = " + CheckAttribute(chref, "ShipTaskLock"));
		Log_Info("CheckWatchFort = " + CheckAttribute(chref, "WatchFort"));
		if (CheckAttribute(chref, "EncType")) Log_Info("EncType = " + chref.EncType);
		if (CheckAttribute(chref, "Ship.Mode")) Log_Info("Ship.Mode = " + chref.Ship.Mode);
		if (CheckAttribute(chref, "Ship.LastBallCharacter")) Log_Info("LastBallCharacter = " + chref.Ship.LastBallCharacter);
		if (CheckAttribute(arScopeItm,"scope.show.mushketshot") && sti(arScopeItm.scope.show.mushketshot) != 0  && CheckOfficersPerk(chref, "MusketsShoot")) Log_Info("MushketShot enabled");		
		if (CheckAttribute(chref,"Situation")) Log_Info("Cap. Situation : " + chref.situation +" type :" + chref.situation.type);
		if (CheckAttribute(chref, "DontRansackCaptain")) Log_Info(XI_ConvertString("DontRansackCaptain"));
		if (CheckAttribute(chref, "surrendered")) Log_Info(XI_ConvertString("Surrendered"));
		if (CheckAttribute(chref, "ShipHideImmortal")) Log_Info(XI_ConvertString("ShipHideImmortal"));
		if (CheckAttribute(chref, "SeaBoss")) Log_Info(XI_ConvertString("SeaBoss")+stf(chref.SeaBoss)+"");
		
//		Log_Info("ShipEnemyDisable = " + CheckAttribute(chref, "ShipEnemyDisable"));
		Log_Info("AlwaysFriend = " + CheckAttribute(chref, "AlwaysFriend"));
//		Log_Info("Coastal_Captain = " + CheckAttribute(chref, "Coastal_Captain"));
		
	}
	// boal <--
}

void ResetSpyGlassData()
{
	SendMessage(&objISpyGlass,"ll",MSG_ISG_VISIBLE,false);
}

void FillISpyGlassParameters()
{
	//==========================================================
	float fHtRatio = stf(Render.screen_y) / iHudScale;
	int fTmp, fTmp2, fTmp3, fTmp4;
	int fAddX, fAddY;
	int	fOffX = 10;
	int	fOffY = 10;
	int fSizeX = 128;
	int fSizeY = 128;
	string sTexture = "spyglass1";
	if (CheckAttribute(pchar, "equip.spyglass"))
	{
	    sTexture = pchar.equip.spyglass;
	}
	//log_info(pchar.equip.spyglass);
	int nHCenter = sti(showWindow.right)/2;
	int nVCenter = sti(showWindow.bottom)/2;
	int nleft = sti(showWindow.left);
	int ntop = sti(showWindow.top);
	int nright = sti(showWindow.right);
	int nbottom = sti(showWindow.bottom);
	objISpyGlass.lens.texture = "interfaces\le\battle_interface\spyglass\" + sTexture + ".tga";
	float fratio = stf(showWindow.right)/stf(showWindow.bottom);
	if (stf(fratio)>2.0) objISpyGlass.lens.pos = (nleft-1)+","+(ntop-1)+","+nright+","+nbottom;// fix wide screen
	else objISpyGlass.lens.pos = (nHCenter-sti(showWindow.bottom))+","+(sti(showWindow.top)-1)+","+(nHCenter+sti(showWindow.bottom))+","+showWindow.bottom;

	//==========================================================
	float fRes = 0.85; // для ресайза
	objISpyGlass.shipsign.ship.texture = "interfaces\le\battle_interface\ship_icons2.tga";//
	fTmp = nleft + fOffX + makeint(fSizeX * fHtRatio) - makeint(fSizeX * fRes * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fRes * fHtRatio);
	fTmp3 = nleft + fOffX + makeint(fSizeX * fRes * fHtRatio);
	fTmp4 = ntop + fOffY + makeint(fSizeY * fRes * fHtRatio);
	objISpyGlass.shipsign.ship.pos = fTmp + "," + fTmp2 + "," + fTmp3 + "," + fTmp4;
	objISpyGlass.shipsign.ship.uv = "0,0,0.0625,0.0625";
	objISpyGlass.shipsign.back.texture = "interfaces\le\battle_interface\shipbackicon1.tga";
	fTmp = nleft + fOffX;
	fTmp2 = ntop + fOffY;
	fTmp3 = nleft + fOffX + makeint(fSizeX * fHtRatio);
	fTmp4 = ntop + fOffY + makeint(fSizeY * fHtRatio);
	objISpyGlass.shipsign.back.pos = fTmp + "," + fTmp2 + "," + fTmp3 + "," + fTmp4;

	// hp bar
	fRes = 0.8;
	objISpyGlass.shipsign.hp.texture = "interfaces\le\battle_interface\ShipState.tga";
	fTmp = nleft + fOffX + makeint(fSizeX * fHtRatio) - makeint(fSizeX * fRes * fHtRatio) - makeint(28 * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fRes * fHtRatio) - makeint(4 * fHtRatio);
	fTmp3 = nleft + fOffX + makeint(fSizeX * fRes * fHtRatio) - makeint(28 * fHtRatio);
	fTmp4 = ntop + fOffY + makeint(fSizeY * fRes * fHtRatio) + makeint(0 * fHtRatio);
	objISpyGlass.shipsign.hp.pos = fTmp + "," + fTmp2 + "," + fTmp3 + "," + fTmp4;
	objISpyGlass.shipsign.hp.uv = "0.0,0.1875,0.5,0.7968";
	// sp bar
	objISpyGlass.shipsign.sp.texture = "interfaces\le\battle_interface\ShipState.tga";
	fTmp = nleft + fOffX + makeint(fSizeX * fHtRatio) - makeint(fSizeX * fRes * fHtRatio) + makeint(28 * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fRes * fHtRatio) - makeint(4 * fHtRatio);
	fTmp3 = nleft + fOffX + makeint(fSizeX * fRes * fHtRatio) + makeint(28 * fHtRatio);
	fTmp4 = ntop + fOffY + makeint(fSizeY * fRes * fHtRatio) + makeint(0 * fHtRatio);
	objISpyGlass.shipsign.sp.pos = fTmp + "," + fTmp2 + "," + fTmp3 + "," + fTmp4;
	objISpyGlass.shipsign.sp.uv = "0.5,0.1875,1.0,0.7968";
	// shipclass
	objISpyGlass.shipsign.class.texture = "interfaces\le\battle_interface\ShipClass2.tga";
	fRes = 0.9;
	fTmp = nleft + fOffX + makeint(fSizeX * fHtRatio) - makeint(fSizeX * fRes * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(32 * fHtRatio) - makeint(32 * fRes * fHtRatio);
	fTmp3 = nleft + fOffX + makeint(fSizeX * fRes * fHtRatio);
	fTmp4 = ntop + fOffY + makeint(32 * fRes * fHtRatio);
	objISpyGlass.shipsign.class.pos = fTmp + "," + fTmp2 + "," + fTmp3 + "," + fTmp4;
	//
	fRes = 1.5;
	objISpyGlass.info.nation.texture = "interfaces\le\nations.tga";
	fTmp = nleft + fOffX + makeint(fSizeX * fHtRatio) - makeint(fSizeX * fHtRatio) + makeint(0 * fHtRatio);
	fTmp2 = nbottom + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fHtRatio) - makeint(210 * fHtRatio);
	fTmp3 = nleft + fOffX + makeint(fSizeX * fRes * fHtRatio) + makeint(0 * fHtRatio);
	fTmp4 = nbottom + fOffY + makeint(fSizeY * fRes * fHtRatio) - makeint(210 * fHtRatio);
	objISpyGlass.info.nation.pos = fTmp + "," + fTmp2 + "," + fTmp3 + "," + fTmp4;
	objISpyGlass.info.nation.uv = "0,0,0.0625,1.0";

	// shipname text
	fTmp = makeint(150.0 * fHtRatio);
    fTmp2 = makeint(40.0 * fHtRatio);
	objISpyGlass.text.shipname.font = "interface_normal";
	objISpyGlass.text.shipname.pos = fTmp + "," + fTmp2;
	objISpyGlass.text.shipname.color = argb(255,255,255,255);
	objISpyGlass.text.shipname.scale = 2.0 * fHtRatio;
	// shiptype text
	fTmp = makeint(150.0 * fHtRatio);
    fTmp2 = makeint(80.0 * fHtRatio);
	objISpyGlass.text.shiptype.font = "interface_normal";
	objISpyGlass.text.shiptype.pos = fTmp + "," + fTmp2;
	objISpyGlass.text.shiptype.color = argb(255,255,255,255);
	objISpyGlass.text.shiptype.scale = 2.0 * fHtRatio;
	// crew text
	fTmp = nleft + fOffX + makeint(fSizeX * fHtRatio) - makeint(fSizeX * fHtRatio) + makeint(64 * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fHtRatio) + makeint(104 * fHtRatio);
	objISpyGlass.text.crew.font = "interface_normal";
	objISpyGlass.text.crew.pos = fTmp + "," + fTmp2;
	objISpyGlass.text.crew.align = "center";
	objISpyGlass.text.crew.color = argb(255,255,255,255);
	objISpyGlass.text.crew.scale = 1.5 * fHtRatio;

	// left info icons and text
	fAddX = 120;
	fAddY = 100;
	fRes = 0.8;
	// speed icon
	objISpyGlass.info.speed.texture = "interfaces\le\battle_interface\list_icons.tga";
	fTmp = nleft + fOffX + makeint(fSizeX * fHtRatio) - makeint(fSizeX * fRes * fHtRatio) + makeint(0 * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fRes * fHtRatio) + makeint(128 * fHtRatio);
	fTmp3 = nleft + fOffX + makeint(fSizeX * fRes * fHtRatio) + makeint(0 * fHtRatio);
	fTmp4 = ntop + fOffY + makeint(fSizeY * fRes * fHtRatio) + makeint(128 * fHtRatio);
	objISpyGlass.info.speed.pos = fTmp + "," + fTmp2 + "," + fTmp3 + "," + fTmp4;
	objISpyGlass.info.speed.uv = "0.4375,0.0,0.625,0.125";
	// speed text
	fTmp = nleft + fOffX + makeint(fSizeX * fHtRatio) - makeint(fSizeX * fHtRatio) + makeint(fAddX * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fHtRatio) + makeint(175 * fHtRatio);
	objISpyGlass.text.speed.font = "interface_normal";
	objISpyGlass.text.speed.pos = fTmp + "," + fTmp2;
	objISpyGlass.text.speed.align = "left";
	objISpyGlass.text.speed.color = argb(255,255,255,255);
	objISpyGlass.text.speed.scale = 2.0 * fHtRatio;
	// sailto icon
	objISpyGlass.info.sailto.texture = "interfaces\le\battle_interface\list_icons.tga";
	fTmp = nleft + fOffX + makeint(fSizeX * fHtRatio) - makeint(fSizeX * fRes * fHtRatio) + makeint(0 * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fRes * fHtRatio) + makeint((128 + fAddY*1) * fHtRatio);
	fTmp3 = nleft + fOffX + makeint(fSizeX * fRes * fHtRatio) + makeint(0 * fHtRatio);
	fTmp4 = ntop + fOffY + makeint(fSizeY * fRes * fHtRatio) + makeint((128 + fAddY*1) * fHtRatio);	
	objISpyGlass.info.sailto.pos = fTmp + "," + fTmp2 + "," + fTmp3 + "," + fTmp4;
	objISpyGlass.info.sailto.uv = "0.75,0.25,0.8125,0.375";
	// sailto text
	fTmp = nleft + fOffX + makeint(fSizeX * fHtRatio) - makeint(fSizeX * fHtRatio) + makeint(fAddX * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fHtRatio) + makeint((175 + fAddY*1) * fHtRatio);
	objISpyGlass.text.sailto.font = "interface_normal";
	objISpyGlass.text.sailto.pos = fTmp + "," + fTmp2;
	objISpyGlass.text.sailto.align = "left";
	objISpyGlass.text.sailto.color = argb(255,255,255,255);
	objISpyGlass.text.sailto.scale = 2.0 * fHtRatio;
	// cannons icon
	objISpyGlass.info.cannon.texture = "interfaces\le\battle_interface\list_icons.tga";
	fTmp = nleft + fOffX + makeint(fSizeX * fHtRatio) - makeint(fSizeX * fRes * fHtRatio) + makeint(0 * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fRes * fHtRatio) + makeint((128 + fAddY*2) * fHtRatio);
	fTmp3 = nleft + fOffX + makeint(fSizeX * fRes * fHtRatio) + makeint(0 * fHtRatio);
	fTmp4 = ntop + fOffY + makeint(fSizeY * fRes * fHtRatio) + makeint((128 + fAddY*2) * fHtRatio);
	objISpyGlass.info.cannon.pos = fTmp + "," + fTmp2 + "," + fTmp3 + "," + fTmp4;
	objISpyGlass.info.cannon.uv = "0.625,0.375,0.6875,0.5";
	// cannonstype text
	fTmp = nleft + fOffX + makeint(fSizeX * fHtRatio) - makeint(fSizeX * fHtRatio) + makeint(fAddX * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fHtRatio) + makeint((175 + fAddY*1.85) * fHtRatio);
	objISpyGlass.text.cannonstype.font = "interface_normal";
	objISpyGlass.text.cannonstype.pos = fTmp + "," + fTmp2;
	objISpyGlass.text.cannonstype.align = "left";
	objISpyGlass.text.cannonstype.color = argb(255,255,255,255);
	objISpyGlass.text.cannonstype.scale = 2.0 * fHtRatio;
	// cannons qty text
	fTmp = nleft + fOffX + makeint(fSizeX * fHtRatio) - makeint(fSizeX * fHtRatio) + makeint(fAddX * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fHtRatio) + makeint((175 + fAddY*2.2) * fHtRatio);
	objISpyGlass.text.cannons.font = "interface_normal";
	objISpyGlass.text.cannons.pos = fTmp + "," + fTmp2;
	objISpyGlass.text.cannons.align = "left";
	objISpyGlass.text.cannons.color = argb(255,255,255,255);
	objISpyGlass.text.cannons.scale = 2.0 * fHtRatio;
	// charge icon
	objISpyGlass.info.charge.texture = "interfaces\le\battle_interface\list_icons.tga";//тип боеприпасов
	fTmp = nleft + fOffX + makeint(fSizeX * fHtRatio) - makeint(fSizeX * fRes * fHtRatio) + makeint(0 * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fRes * fHtRatio) + makeint((128 + fAddY*3) * fHtRatio);
	fTmp3 = nleft + fOffX + makeint(fSizeX * fRes * fHtRatio) + makeint(0 * fHtRatio);
	fTmp4 = ntop + fOffY + makeint(fSizeY * fRes * fHtRatio) + makeint((128 + fAddY*3) * fHtRatio);
	objISpyGlass.info.charge.pos = fTmp + "," + fTmp2 + "," + fTmp3 + "," + fTmp4;
	objISpyGlass.info.charge.uv = "0.125,0.0,0.375,0.125";
	// charge text
	fTmp = nleft + fOffX + makeint(fSizeX * fHtRatio) - makeint(fSizeX * fHtRatio) + makeint(fAddX * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fHtRatio) + makeint((175 + fAddY*3) * fHtRatio);
	objISpyGlass.text.charge.font = "interface_normal";
	objISpyGlass.text.charge.pos = fTmp + "," + fTmp2;
	objISpyGlass.text.charge.align = "left";
	objISpyGlass.text.charge.color = argb(255,255,255,255);
	objISpyGlass.text.charge.scale = 2.0 * fHtRatio;
	
	//==========================================================
	// right info icons and text
	objISpyGlass.captain.back.texture = "interfaces\le\battle_interface\shipbackicon1.tga";
	fTmp = nright - fOffX - makeint(fSizeX * fHtRatio);
	fTmp2 = ntop + fOffY;
	fTmp3 = nright - fOffX;
	fTmp4 = ntop + fOffY + makeint(fSizeY * fHtRatio);
	objISpyGlass.captain.back.pos = fTmp + "," + fTmp2 + "," + fTmp3 + "," + fTmp4;

	fRes = 1.0;
	objISpyGlass.captain.face.texture = "interfaces\le\battle_interface\portraits\face_0.tga";
	fTmp = nright - fOffX - makeint(fSizeX * fRes * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fRes * fHtRatio) + makeint(15 * fHtRatio);
	fTmp3 = nright - fOffX - makeint(fSizeX * fHtRatio) + makeint(fSizeX * fRes * fHtRatio);
	fTmp4 = ntop + fOffY + makeint(fSizeY * fRes * fHtRatio) + makeint(15 * fHtRatio);
	objISpyGlass.captain.face.pos = fTmp + "," + fTmp2 + "," + fTmp3 + "," + fTmp4;

	// icons
	fAddX = 120;
	fAddY = 100;
	fRes = 0.8;
	// навигация
	objISpyGlass.captain.navigation.texture = "interfaces\le\icons_spec.tga";
	fTmp = nright - fOffX - makeint(fSizeX * fRes * fHtRatio) + makeint(0 * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fRes * fHtRatio) + makeint(128 * fHtRatio);
	fTmp3 = nright - fOffX - makeint(fSizeX * fHtRatio) + makeint(fSizeX * fRes * fHtRatio) + makeint(0 * fHtRatio);
	fTmp4 = ntop + fOffY + makeint(fSizeY * fRes * fHtRatio) + makeint(128 * fHtRatio);
	objISpyGlass.captain.navigation.pos = fTmp + "," + fTmp2 + "," + fTmp3 + "," + fTmp4;
	objISpyGlass.captain.navigation.uv = "0.5,0.125,0.625,0.25";
	// меткость
	objISpyGlass.captain.accuracy.texture = "interfaces\le\icons_spec.tga";
	fTmp = nright - fOffX - makeint(fSizeX * fRes * fHtRatio) + makeint(0 * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fRes * fHtRatio) + makeint((128 + fAddY*1) * fHtRatio);
	fTmp3 = nright - fOffX - makeint(fSizeX * fHtRatio) + makeint(fSizeX * fRes * fHtRatio) + makeint(0 * fHtRatio);
	fTmp4 = ntop + fOffY + makeint(fSizeY * fRes * fHtRatio) + makeint((128 + fAddY*1) * fHtRatio);
	objISpyGlass.captain.accuracy.pos = fTmp + "," + fTmp2 + "," + fTmp3 + "," + fTmp4;
	objISpyGlass.captain.accuracy.uv = "0.25,0.125,0.375,0.25";
	// орудия
	objISpyGlass.captain.cannon.texture = "interfaces\le\icons_spec.tga";
	fTmp = nright - fOffX - makeint(fSizeX * fRes * fHtRatio) + makeint(0 * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fRes * fHtRatio) + makeint((128 + fAddY*2) * fHtRatio);
	fTmp3 = nright - fOffX - makeint(fSizeX * fHtRatio) + makeint(fSizeX * fRes * fHtRatio) + makeint(0 * fHtRatio);
	fTmp4 = ntop + fOffY + makeint(fSizeY * fRes * fHtRatio) + makeint((128 + fAddY*2) * fHtRatio);
	objISpyGlass.captain.cannon.pos = fTmp + "," + fTmp2 + "," + fTmp3 + "," + fTmp4;
	objISpyGlass.captain.cannon.uv = "0.375,0.125,0.5,0.25";
	// абордаж
	objISpyGlass.captain.boarding.texture = "interfaces\le\icons_spec.tga";
	fTmp = nright - fOffX - makeint(fSizeX * fRes * fHtRatio) + makeint(0 * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fRes * fHtRatio) + makeint((128 + fAddY*3) * fHtRatio);
	fTmp3 = nright - fOffX - makeint(fSizeX * fHtRatio) + makeint(fSizeX * fRes * fHtRatio) + makeint(0 * fHtRatio);
	fTmp4 = ntop + fOffY + makeint(fSizeY * fRes * fHtRatio) + makeint((128 + fAddY*3) * fHtRatio);
	objISpyGlass.captain.boarding.pos = fTmp + "," + fTmp2 + "," + fTmp3 + "," + fTmp4;
	objISpyGlass.captain.boarding.uv = "0.75,0.125,0.875,0.25";
	// защита
	objISpyGlass.captain.defence.texture = "interfaces\le\icons_spec.tga";
	fTmp = nright - fOffX - makeint(fSizeX * fRes * fHtRatio) + makeint(0 * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fRes * fHtRatio) + makeint((128 + fAddY*4) * fHtRatio);
	fTmp3 = nright - fOffX - makeint(fSizeX * fHtRatio) + makeint(fSizeX * fRes * fHtRatio) + makeint(0 * fHtRatio);
	fTmp4 = ntop + fOffY + makeint(fSizeY * fRes * fHtRatio) + makeint((128 + fAddY*4) * fHtRatio);
	objISpyGlass.captain.defence.pos = fTmp + "," + fTmp2 + "," + fTmp3 + "," + fTmp4;
	objISpyGlass.captain.defence.uv = "0.875,0.125,1.0,0.25";
	// Око мертвеца
	fOffX = 25;
	fSizeX = 75;
	fRes = 1.0;
	objISpyGlass.captain.surrender.texture = "interfaces\morality.tga";
	fTmp = nright - fOffX - makeint(fSizeX * fRes * fHtRatio) + makeint(0 * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fRes * fHtRatio) + makeint((128 + fAddY*1) * fHtRatio);
	fTmp3 = nright - fOffX - makeint(fSizeX * fHtRatio) + makeint(fSizeX * fRes * fHtRatio) + makeint(0 * fHtRatio);
	fTmp4 = ntop + fOffY + makeint(fSizeY * fRes * fHtRatio) + makeint((128 + fAddY*1) * fHtRatio);
	objISpyGlass.captain.surrender.pos = fTmp + "," + fTmp2 + "," + fTmp3 + "," + fTmp4;
	objISpyGlass.captain.surrender.uv = "0.5,0.0,0.65,1.0";

	// text
	fTmp = nright - makeint(150.0 * fHtRatio);
    fTmp2 = ntop + makeint(40.0 * fHtRatio);
	objISpyGlass.captext.capname.font = "interface_normal";
	objISpyGlass.captext.capname.pos = fTmp + "," + fTmp2;
	objISpyGlass.captext.capname.align = "right";
	objISpyGlass.captext.capname.color = argb(255,255,255,255);
	objISpyGlass.captext.capname.scale = 2.0 * fHtRatio;
	// перк
	fTmp = nright - makeint(150.0 * fHtRatio);
    fTmp2 = ntop + makeint(80.0 * fHtRatio);
	objISpyGlass.captext.capperk.font = "interface_normal";
	objISpyGlass.captext.capperk.pos = fTmp + "," + fTmp2;
	objISpyGlass.captext.capperk.align = "right";
	objISpyGlass.captext.capperk.color = argb(255,255,255,255);
	objISpyGlass.captext.capperk.scale = 2.0 * fHtRatio;
	// навигация
	fTmp = nright - fOffX + makeint(fSizeX * fHtRatio) - makeint(fSizeX * fHtRatio) - makeint(fAddX * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fHtRatio) + makeint(175 * fHtRatio);
	objISpyGlass.captext.navigation.font = "interface_normal";
	objISpyGlass.captext.navigation.pos = fTmp + "," + fTmp2;
	objISpyGlass.captext.navigation.align = "right";
	objISpyGlass.captext.navigation.color = argb(255,255,255,255);
	objISpyGlass.captext.navigation.scale = 2.0 * fHtRatio;
	// меткость
	fTmp = nright - fOffX + makeint(fSizeX * fHtRatio) - makeint(fSizeX * fHtRatio) - makeint(fAddX * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fHtRatio) + makeint((175 + fAddY*1) * fHtRatio);
	objISpyGlass.captext.accuracy.font = "interface_normal";
	objISpyGlass.captext.accuracy.pos = fTmp + "," + fTmp2;
	objISpyGlass.captext.accuracy.align = "right";
	objISpyGlass.captext.accuracy.color = argb(255,255,255,255);
	objISpyGlass.captext.accuracy.scale = 2.0 * fHtRatio;
	// орудия
	fTmp = nright - fOffX + makeint(fSizeX * fHtRatio) - makeint(fSizeX * fHtRatio) - makeint(fAddX * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fHtRatio) + makeint((175 + fAddY*2) * fHtRatio);
	objISpyGlass.captext.cannon.font = "interface_normal";
	objISpyGlass.captext.cannon.pos = fTmp + "," + fTmp2;
	objISpyGlass.captext.cannon.align = "right";
	objISpyGlass.captext.cannon.color = argb(255,255,255,255);
	objISpyGlass.captext.cannon.scale = 2.0 * fHtRatio;
	// абордаж
	fTmp = nright - fOffX + makeint(fSizeX * fHtRatio) - makeint(fSizeX * fHtRatio) - makeint(fAddX * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fHtRatio) + makeint((175 + fAddY*3) * fHtRatio);
	objISpyGlass.captext.boarding.font = "interface_normal";
	objISpyGlass.captext.boarding.pos = fTmp + "," + fTmp2;
	objISpyGlass.captext.boarding.align = "right";
	objISpyGlass.captext.boarding.color = argb(255,255,255,255);
	objISpyGlass.captext.boarding.scale = 2.0 * fHtRatio;
	// защита
	fTmp = nright - fOffX + makeint(fSizeX * fHtRatio) - makeint(fSizeX * fHtRatio) - makeint(fAddX * fHtRatio);
	fTmp2 = ntop + fOffY + makeint(fSizeY * fHtRatio) - makeint(fSizeY * fHtRatio) + makeint((175 + fAddY*4) * fHtRatio);
	objISpyGlass.captext.defence.font = "interface_normal";
	objISpyGlass.captext.defence.pos = fTmp + "," + fTmp2;
	objISpyGlass.captext.defence.align = "right";
	objISpyGlass.captext.defence.color = argb(255,255,255,255);
	objISpyGlass.captext.defence.scale = 2.0 * fHtRatio;
	//===============================================
	objISpyGlass.nationuvarray.uv0 = "0.0,0,0.125,1.0"; // england
	objISpyGlass.nationuvarray.uv1 = "0.125,0,0.25,1.0"; // france
	objISpyGlass.nationuvarray.uv2 = "0.25,0,0.375,1.0"; // spain
	objISpyGlass.nationuvarray.uv3 = "0.375,0,0.5,1.0"; // holland
	objISpyGlass.nationuvarray.uv4 = "0.5,0,0.625,1.0"; // pirate
	objISpyGlass.nationuvarray.uv5 = "0.5,0,0.625,1.0"; // smuggler
	//
	objISpyGlass.chargeuvarray.uv0 = "0.1875,0.0,0.25,0.125"; // balls
	objISpyGlass.chargeuvarray.uv1 = "0.25,0.0,0.3125,0.125"; // bombs
	objISpyGlass.chargeuvarray.uv2 = "0.3125,0.0,0.375,0.125"; // knippels
	objISpyGlass.chargeuvarray.uv3 = "0.125,0.0,0.1875,0.125"; // grapes
	//
	objISpyGlass.sailuvarray.uv0 = "0.5625,0.0,0.625,0.125"; // down
	objISpyGlass.sailuvarray.uv1 = "0.5,0.0,0.5625,0.125"; // middle
	objISpyGlass.sailuvarray.uv2 = "0.4375,0.0,0.5,0.125"; // up
}

void TelescopeInitParameters(ref fTelescope)
{
	aref arItmScope;
	if( Items_FindItem(GetCharacterEquipByGroup(pchar,SPYGLASS_ITEM_TYPE),&arItmScope)>=0 )
	{	setTelescopeInitParameters(arItmScope);
	}
	else
	{
		object tmpobj;
		setTelescopeInitParameters(&tmpobj);
	}
}

void setTelescopeInitParameters(aref arItmScope)
{
	string texName = "telescope.tga";
	float fZoom = 5.5;
	int activateTime = 500;
	int updateTime = 150;

	if( CheckAttribute(arItmScope,"scope.texture") )
	{	texName = arItmScope.scope.texture;
	}
	if( CheckAttribute(arItmScope,"scope.zoom") )
	{	fZoom = stf(arItmScope.scope.zoom);
	}
	if( CheckAttribute(arItmScope,"scope.time_activate") )
	{	activateTime = sti(arItmScope.scope.time_activate);
	}
	if( CheckAttribute(arItmScope,"scope.time_update") )
	{	updateTime = sti(arItmScope.scope.time_update);
	}

	SendMessage(&objISpyGlass, "lsfll", MSG_TELESCOPE_SET_TYPE, texName, fZoom, activateTime, updateTime);
}

object objActivePerkShower;

#event_handler(EVENT_LOCATION_LOAD,"procLoadIntoNew");

void InitActivePerkShower()
{
    InitShowPlaces();
}

void InitShowPlaces()
{
	float fHtRatio = stf(Render.screen_y) / iHudScale;
	/*objActivePerkShower.ShowParam.PosRect.left		= sti(showWindow.right) - RecalculateHIcon(300 * fHtRatio));
	objActivePerkShower.ShowParam.PosRect.top		= sti(showWindow.bottom) - RecalculateVIcon(makeint(300 * fHtRatio));
	objActivePerkShower.ShowParam.PosRect.right		= sti(showWindow.right) - RecalculateHIcon(makeint(35 * fHtRatio));
	objActivePerkShower.ShowParam.PosRect.bottom	= sti(showWindow.bottom) - RecalculateVIcon(makeint(400 * fHtRatio));
	objActivePerkShower.ShowParam.IconSize.horz		= RecalculateHIcon(makeint(60 * fHtRatio));
	objActivePerkShower.ShowParam.IconSize.vert		= RecalculateVIcon(makeint(60 * fHtRatio));*/
	objActivePerkShower.ShowParam.PosRect.left		= sti(showWindow.right) - RecalculateHIcon(100 * fHtRatio));
	objActivePerkShower.ShowParam.PosRect.top		= sti(showWindow.bottom)/2 + RecalculateVIcon(makeint(64 * fHtRatio));
	objActivePerkShower.ShowParam.PosRect.right		= sti(showWindow.right) - RecalculateHIcon(makeint(40 * fHtRatio));
	objActivePerkShower.ShowParam.PosRect.bottom	= sti(showWindow.bottom) - RecalculateVIcon(makeint(0 * fHtRatio));
	objActivePerkShower.ShowParam.IconSize.horz		= RecalculateHIcon(makeint(60 * fHtRatio));
	objActivePerkShower.ShowParam.IconSize.vert		= RecalculateVIcon(makeint(60 * fHtRatio));
	objActivePerkShower.ShowParam.IconSpace.horz	= RecalculateHIcon(2);
	objActivePerkShower.ShowParam.IconSpace.vert	= RecalculateVIcon(2);
}

void procLoadIntoNew()
{
	UnloadActivePerkShower();
	SetEventHandler("frame","LoadActivePerkShower",1);
}

void LoadActivePerkShower()
{
	DelEventHandler("frame","LoadActivePerkShower");

	DeleteAttribute(&objActivePerkShower,"PerkList.list");
	DeleteAttribute(&objActivePerkShower,"Textures");
	
	// информация о текстурах
	if(bSeaActive && !bAbordageStarted)
	{	// морская часть
		objActivePerkShower.Textures.t0.file = "interfaces\le\battle_interface\list_icons.tga";
		objActivePerkShower.Textures.t0.horz = 16;
		objActivePerkShower.Textures.t0.vert = 8;
	}
	else
	{	// земная часть
		objActivePerkShower.Textures.t0.file = "interfaces\le\battle_interface\LandCommands.tga";
		objActivePerkShower.Textures.t0.horz = 16;
		objActivePerkShower.Textures.t0.vert = 4;
	}

	aref arPerksRoot,arPerk;
	makearef(arPerksRoot,pchar.perks.list);
	int perksQ = GetAttributesNum(arPerksRoot);

	string stmp;
	int idx = 0;
	for(int j=0; j<perksQ; j++)
	{
		arPerk = GetAttributeN(arPerksRoot,j);
		if( CheckAttribute(arPerk,"delay") )
		{
			if( CheckAttribute(arPerk,"active") )
			{
				AddPerkToActiveList(GetAttributeName(arPerk));
			}
		}
	}

	CreateEntity(&objActivePerkShower,"ActivePerkShower");
	if(bSeaActive && !bAbordageStarted)
	{	// морская часть
		LayerAddObject(SEA_EXECUTE,&objActivePerkShower,-1);
		LayerAddObject(SEA_REALIZE,&objActivePerkShower,-1);
	}
	else
	{
		LayerAddObject(EXECUTE,&objActivePerkShower,-1);
		LayerAddObject(REALIZE,&objActivePerkShower,-1);
	}
	InitShowPlaces();
	SendMessage(&objActivePerkShower,"l",MSG_ACTIVE_PERK_ICON_REFRESH);
}

void UnloadActivePerkShower()
{
	DeleteClass(&objActivePerkShower);
	DeleteAttribute(&objActivePerkShower,"PerkList");
}

bool IsPerkIntoList(string perkID)
{
	return CheckAttribute(&objActivePerkShower,"PerkList.list."+perkID);
}

void AddPerkToActiveList(string perkID)
{
	if( !IsEntity(&objActivePerkShower) ) return;
	aref arRoot,arCur;
	makearef(arRoot,objActivePerkShower.PerkList.list);
	if( CheckAttribute(arRoot,perkID) ) return;

	makearef(arCur,arRoot.(perkID));

	int nTex = GetTextureIndex(GetPerkTextureName(perkID));
	if(nTex < 0)
        return;
	arCur.texture = nTex;
	arCur.pic_idx = GetPerkPictureIndex(perkID);
	SendMessage(&objActivePerkShower,"lsa",MSG_ACTIVE_PERK_LIST_REFRESH,"add",arCur);
}

int GetPerkPictureIndex(string perkName)
{
	switch(perkName)
	{
		case "TimeSpeed":
	        if(bSeaActive && !bAbordageStarted)
			{
				return 59;
			}
			else
			{
			    return 15;
			}
		break;
		case "Sink":			return 43; break;
		case "Repair":			return 39; break;
		// boal зачем же так игру кастрировать? грустно, однако :( -->
		//case "Rush":	        return 28;	break;
		case "Rush":	        return -1;	break;
		case "IronWill":	    return -1;	break; // belamour legendary edition todo
		case "LightRepair":		return 38; break;
		case "InstantRepair":	return 39; break;
		case "ImmediateReload":	return 37; break;
		case "Turn180":			return 40; break;
		// boal <--
	}
	trace("WARNING!!! Perk name - "+perkName+" hav`t picture");
	return 0;
}

string GetPerkTextureName(string perkName)
{
	switch(perkName)
	{
		case "TimeSpeed":
			if(bSeaActive && !bAbordageStarted)
			{
				return "interfaces\le\battle_interface\list_icons.tga";
			}
			else
			{
			    return "interfaces\le\battle_interface\LandCommands.tga";
			}
		break;
		case "Sink":			return "interfaces\le\battle_interface\list_icons.tga"; break;
		case "Repair":			return "interfaces\le\battle_interface\list_icons.tga"; break;
		case "Rush":			return "interfaces\le\battle_interface\LandCommands.tga";	break;
		//case "IronWill":		return "interfaces\le\battle_interface\LandCommands.tga";	break; // belamour legendary edition todo
		case "ImmediateReload":	return "interfaces\le\battle_interface\list_icons.tga"; break;
		case "InstantBoarding":	return "interfaces\le\battle_interface\list_icons.tga"; break;
		case "Turn180":			return "interfaces\le\battle_interface\list_icons.tga"; break;
		case "LightRepair":		return "interfaces\le\battle_interface\list_icons.tga"; break;
		case "InstantRepair":	return "interfaces\le\battle_interface\list_icons.tga"; break;
	}
	trace("WARNING!!! Perk name - "+perkName+" hav`t texture");
	return "";
}

int GetTextureIndex(string texName)
{
	aref arTexList,arCurTex;
	makearef(arTexList,objActivePerkShower.Textures);
	int i,q;

	q = GetAttributesNum(arTexList);
	for(i=0; i<q; i++)
	{
		arCurTex = GetAttributeN(arTexList,i);
		if(arCurTex.file == texName) return i;
	}
	trace("WARNING!!! Texture name - "+texName+" hav`t describe");
	return -1;
}

void DelPerkFromActiveList(string perkID)
{
	aref arRoot,arCur;
	makearef(arRoot,objActivePerkShower.PerkList.list);
	if( !CheckAttribute(arRoot,perkID) ) return;

	makearef(arCur,arRoot.(perkID));
	SendMessage(&objActivePerkShower,"lsa",MSG_ACTIVE_PERK_LIST_REFRESH,"del",arCur);
	DeleteAttribute(arRoot,perkID);
}
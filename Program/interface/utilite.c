
native string LanguageGetLanguage();
native int LanguageOpenFile(string sFileName);
native void LanguageCloseFile(int idLngFile);
native string LanguageConvertString(int userLngFileID, string inStr);
native int LanguageGetFileStringsQuantity(int userLngFileID);
native void LanguageSetLanguage(string sLanguageName);
native string XI_ConvertString(string inStr);
native int GlobalLngFileID();
native string LanguageGetFaderPic(string faderPicName);
native string DialogAssembleStr(string idStr, string paramStr);
native string DialogAddParamToStr(string oldParamStr, string paramID, string paramValue);
native string StringFromKey(string key_name, string arg1, string arg2, string arg3, string arg4, string arg5, string arg6, string arg7, string arg8, string arg9, string arg10, string arg11, string arg12, string arg13, string arg14, string arg15, string arg16, string arg17, string arg18, string arg19);

//native int NFFindFiles(ref rObject, string sDirectory, string sMask, bool bRecursive);

native void XI_SetColorCorrection(float fContrast, float fGamma, float fBrightness);
native void XI_SetMouseSensitivity( float fMouseXSens, float fMouseYSens );
native void XI_ControlMakeInvert(string sControlName, int bInvertState);
native void XI_MakeNode(string sIniFileName, string sNodeType, string sNodeName, int nPriority);
native void XI_DeleteNode(string sNodeName);
native bool XI_IsWindowEnable(string sWindowName);
native void XI_WindowShow(string sWindowName, int bShowStatus);
native void XI_WindowDisable(string sWindowName, int bDisableStatus);
native void XI_WindowAddNode(string sWindowName, string sNodeName);
native bool XI_CreateFolder(string sFolderName);
native bool XI_CheckFolder(string sFolderName);
native bool XI_DeleteFolder(string sFolderName);
native bool XI_FindFolders(string sFindTemplate,aref arFoldersList);
native int XI_StoreNodeLocksWithOff();
native void XI_RestoreNodeLocks(int nStoreCode);
native bool XI_IsKeyPressed(string key_name); // key_name = {"shift","control","alt"}
native bool XI_IsVirtualKeyPressed(int key_code);
native void XI_RegistryExitKey(string key_name);

#libriary "script_interface_functions"

void CreateImage(string AttrName,string imgListName,string imgName,int left,int top,int right,int bottom)
{
	GameInterface.pictures.(AttrName).tex = imgListName;
    GameInterface.pictures.(AttrName).pic = imgName;
    SendMessage(&GameInterface,"lslllll",MSG_INTERFACE_PLACE_IMAGE,AttrName,true,left,top,right,bottom);
}

void CreateAbsoluteImage(string AttrName,string imgListName,string imgName,int left,int top,int right,int bottom)
{
	GameInterface.pictures.(AttrName).tex = imgListName;
    GameInterface.pictures.(AttrName).pic = imgName;
    SendMessage(&GameInterface,"lslllll",MSG_INTERFACE_PLACE_IMAGE,AttrName,false,left,top,right,bottom);
}

void SetPictureBlind(string picName,bool blindFlag,int minCol,int maxCol)
{
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_SET_BLIND,picName,blindFlag,minCol,maxCol);
}

void CreateString(int enable,string strName, string strData, string fontName, int color, int x, int y, int alignment, float scale)
{
    GameInterface.strings.(strName) = strData;
    SendMessage(&GameInterface,"lssllllf",MSG_INTERFACE_CREATE_STRING, strName, fontName, color, x,y,alignment,scale);
    if(enable==FALSE)
    {
        SendMessage(&GameInterface,"ls", MSG_INTERFACE_DISABLE_STRING, strName);
    }
}

void DisableString(string strName)
{
    SendMessage(&GameInterface,"ls", MSG_INTERFACE_DISABLE_STRING, strName);
}

void EnableString(string strName)
{
    SendMessage(&GameInterface,"ls", MSG_INTERFACE_ENABLE_STRING, strName);
}

void ChangeStringColor(string strName, int newCol)
{
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_CHANGE_STR_COLOR,strName,newCol);
}

void SetNodeUsing(string nodeName,int bUsing)
{
    SendMessage(&GameInterface,"lsl", MSG_INTERFACE_SET_NODE_USING, nodeName, bUsing);
}

void SetCurrentNode(string nodeName)
{
    SendMessage(&GameInterface,"ls", MSG_INTERFACE_NEW_CURRENT_NODE,nodeName);
}
string GetCurrentNode()
{
	string retVal;
	SendMessage(&GameInterface,"le", MSG_INTERFACE_GET_CURRENT_NODE,&retVal);
	return retVal;
}

void ShowHelpString(string helpString)
{
    SendMessage(&GameInterface,"ls", MSG_INTERFACE_SETHELPSTRING, helpString);
}

string MakeMoneyShow(int moneyQuantity,string sign,string deliver)
{
	string moneyStr;
	int i,j;
	moneyStr="";
	while(moneyQuantity>999)
	{
		i = moneyQuantity/1000;
		j = moneyQuantity-i*1000;
		if(j>99)
		{
			moneyStr = deliver + j + moneyStr;
		}
		else
		{
			if(j>9)
			{
				moneyStr = deliver+"0" + j + moneyStr;
			}
			else
			{
				moneyStr = deliver+"00" + j + moneyStr;
			}
		}
		moneyQuantity = i;
	}
	moneyStr = sign+moneyQuantity+moneyStr;
	return moneyStr;
}

void SetNewPicture(string _NodeName,string _NewPictureFileName)
{
	SendMessage(&GameInterface,"lslls", MSG_INTERFACE_MSG_TO_NODE,_NodeName,2, false, _NewPictureFileName);
}

void SetNewGroupPicture(string sNodeName,string sGroup, string sName)
{
	SendMessage(&GameInterface,"lslss", MSG_INTERFACE_MSG_TO_NODE, sNodeName,6, sGroup, sName);	
}

void SetNewVideoPicture(string _NodeName,string _NewVideoPicFileName)
{
	SendMessage(&GameInterface,"lslls", MSG_INTERFACE_MSG_TO_NODE,_NodeName,2, true, _NewVideoPicFileName);
}

void SetNewVideo(string _NodeName,string _NewVideoFileName)
{
    SendMessage(&GameInterface,"lsls", MSG_INTERFACE_MSG_TO_NODE,_NodeName,2, _NewVideoFileName);
}

void SetSelectable(string _NodeName,int _Selectable)
{
	SendMessage(&GameInterface,"lsl", MSG_INTERFACE_SET_SELECTABLE, _NodeName, _Selectable);
}
int GetSelectable(string _NodeName)
{
	return SendMessage(&GameInterface,"ls", MSG_INTERFACE_GET_SELECTABLE, _NodeName);
}

void SetClickable(string _NodeName, bool ClickStatus)
{
	SendMessage(&GameInterface,"lslll", MSG_INTERFACE_MSG_TO_NODE,_NodeName,-1,1, ClickStatus);
}
bool GetClickable(string _NodeName)
{
	return SendMessage(&GameInterface,"lsll", MSG_INTERFACE_MSG_TO_NODE,_NodeName,-1,2);
}

void DelFromScroll(string nodeName,int pnum)
{
	int qn = sti(GameInterface.(nodeName).ListSize)-1;
	aref inar,outar;
	string attrName;
	for(int i=pnum; i<qn; i++)
	{
		attrName = "pic"+(i+1);
		makearef(inar,GameInterface.(nodeName).(attrName));
		attrName = "pic"+(i+2);
		makearef(outar,GameInterface.(nodeName).(attrName));
		CopyAttributes(inar,outar);
	}
	attrName = "pic"+(i+1);
	DeleteAttribute(&GameInterface,nodeName+"."+attrName);
	if(qn>=0) GameInterface.(nodeName).ListSize = qn;
	SendMessage(&GameInterface,"lsl", MSG_INTERFACE_DEL_SCROLLIMAGE, nodeName, pnum);
}

void AddToScroll(string nodeName,int pnum)
{
	SendMessage(&GameInterface,"lsl", MSG_INTERFACE_ADD_SCROLLIMAGE, nodeName, pnum);
}

void XI_SetQuestTitles(string nodName,aref questInfo,int topNum)
{
	SendMessage(&GameInterface,"lsal",MSG_INTERFACE_SET_TITLE_STRINGS,nodName,questInfo,topNum);
}

int GetShipTexture(string shipType)
{
	if(shipType=="Not Used") return -1;
	if(shipType=="Galeoth1") return 1;
	if(shipType=="Galeoth2") return 1;
	if(shipType=="Fearless") return 1;
	if(shipType=="GhostShip") return 1;
	return 0;
}

string GetShipTextureName(string shipType)
{
	if(shipType=="Not Used") return "";
	if(shipType=="Galeoth1") return "SHIPS1";
	if(shipType=="Galeoth2") return "SHIPS1";
	if(shipType=="Fearless") return "SHIPS1";
	if(shipType=="GhostShip") return "SHIPS1";
	return "SHIPS16";
}

string GetFaceGroupName(int charIdx)
{
	if(charIdx<0) {return "EMPTYFACE";}
	return "FACE128_"+Characters[charIdx].FaceID;
}

string GetFacePictureName(int charIdx)
{
	if(charIdx<0) return "emptyface";
	return "face";
}
//-------------------------------------------------------------------------------------------------------------
// FormatedText
//-------------------------------------------------------------------------------------------------------------
void SetFormatedText(string sNodeName, string sText)
{
	SendMessage(&GameInterface,"lss",MSG_INTERFACE_SET_FORMATEDTEXT,sNodeName,sText);
}
//-------------------------------------------------------------------------------------------------------------
void AddLineToFormatedText(string sNodeName, string sText)
{
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, &sText);
}
//-------------------------------------------------------------------------------------------------------------
void SelectLineInFormatedText(string sNodeName, int line)
{
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,sNodeName, 1, line);
}
//-------------------------------------------------------------------------------------------------------------
int SelectedLineInFormatedText(string sNodeName)
{
	return SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,sNodeName, 11);
}

// Sith считаем сколько умещается строк в тексте по форме
int GetNumberOfStringsInFormatedText (string sNodeName, string sText)
{
	return SendMessage( &GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE, sNodeName, 9, &sText );
}

int SetVAligmentFormatedText(string sNodeName)  // boal нарыл в ядре, что можно
{
	return SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,sNodeName, 5);
}
//-------------------------------------------------------------------------------------------------------------
// Warship -->
void SetFormattedTextLastLineColor(string _sNodeName, int _iColor)
{
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, _sNodeName, 8, -1, _iColor); // -1 = последняя лини, как я понял
}
// <--
//-------------------------------------------------------------------------------------------------------------

string FloatToString(float fl,int nDigAfterPoint)
{
	//float fmul = pow(10.0,nDigAfterPoint);
	//fl = fl + 0.5/fmul;
	//int p1 = makeint(fl);
	//int p2 = makeint((fl-p1)*fmul);
	//return p1+"."+p2;

	fl= fl + 0.5/pow(10.0,nDigAfterPoint); // округление
	int p1 = makeint(fl); // целая часть
	string str = p1 + "."; // строка
	for(int n=0; n<nDigAfterPoint; n++)
	{
		fl = (fl - p1)*10.0;
		p1 = makeint(fl);
		str = str + p1;
	}
	return str;
}
int GetStringWidth(string str, string fontID, float fScale)
{
	if(!IsEntity(&GameInterface))
		CreateEntity(&GameInterface,"xinterface");
	return SendMessage(&GameInterface, "lssf", MSG_INTERFACE_GET_STRWIDTH, str, fontID, fScale);
}

string GetItemPictureName(string itemName)
{
	aref arItm;
	if( Items_FindItem(itemName,&arItm)>=0 )
	{
		if( CheckAttribute(arItm,"picIndex") )
		{
			return	"itm"+sti(arItm.picIndex);
		}
	}
	return "cannon back";
}

string GetItemTextureName(string itemName)
{
	aref arItm;
	if( Items_FindItem(itemName,&arItm)>=0 )
	{
		if( CheckAttribute(arItm,"picTexture") )
		{
			return	arItm.picTexture;
		}
	}
	return "ICONS";
}

int GetItemPictureTexture(string accessString, string itemName)
{
	aref arItm,arGroup;
	makearef(arGroup,GameInterface.(accessString));
	string sTexName = "ICONS";

	if( Items_FindItem(itemName,&arItm)>=0 )
	{	if( CheckAttribute(arItm,"picTexture") )
		{	sTexName = arItm.picTexture;
		}
	}
	int q = GetAttributesNum(arGroup);
	for(int i=0; i<q; i++)
	{	if( GetAttributeValue(GetAttributeN(arGroup,i)) == sTexName )
		{	return i;
		}
	}
	return -1;
}

void FillImagesGroupForItems(aref arImgGrp)
{
	int i,n,q;
	string stmp;
	object objtmp;
	for(i=0; i<ITEMS_QUANTITY; i++)
	{
		if( CheckAttribute( &Items[i], "picTexture" ) && Items[i].picTexture!="" )
		{
			stmp = Items[i].picTexture;
			objtmp.(stmp) = true;
		}
	}
	q = GetAttributesNum(&objtmp);
	n = GetAttributesNum(arImgGrp);
	for(i=0; i<q; i++)
	{
		stmp = "t"+n;
		arImgGrp.(stmp) = GetAttributeName(GetAttributeN(&objtmp,i));
		n++;
	}
}

string GetFacePicName(ref chref)
{
	return "face";
}


void FillFaceList(string strAccess, ref chref, int fillCode)
{
	aref ar;
	makearef(ar, GameInterface.(strAccess));

	int n, cn, q;

	AddFaceGroup(strAccess,"FACE128_"+chref.faceID);

	if(fillCode==0) // officers
	{
		//officers
		if (chref.Fellows.Passengers.navigator == "-1")
		{
			AddFaceGroup(strAccess,"FACE128_NAVIGATOR");
		}
		else
		{
			AddFaceGroup(strAccess,"FACE128_"+Characters[sti(chref.Fellows.Passengers.navigator)].faceID);
		}
		
		if (chref.Fellows.Passengers.boatswain == "-1")
		{
			AddFaceGroup(strAccess,"FACE128_BOATSWAIN");
		}
		else
		{
			AddFaceGroup(strAccess,"FACE128_"+Characters[sti(chref.Fellows.Passengers.boatswain)].faceID);
		}
		
		if (chref.Fellows.Passengers.cannoner == "-1")
		{
			AddFaceGroup(strAccess,"FACE128_cannoner");
		}
		else
		{
			AddFaceGroup(strAccess,"FACE128_"+Characters[sti(chref.Fellows.Passengers.cannoner)].faceID);
		}
		
		if (chref.Fellows.Passengers.doctor == "-1")
		{
			AddFaceGroup(strAccess,"FACE128_doctor");
		}
		else
		{
			AddFaceGroup(strAccess,"FACE128_"+Characters[sti(chref.Fellows.Passengers.doctor)].faceID);
		}
		
		if (chref.Fellows.Passengers.treasurer == "-1")
		{
			AddFaceGroup(strAccess,"FACE128_treasurer");
		}
		else
		{
			AddFaceGroup(strAccess,"FACE128_"+Characters[sti(chref.Fellows.Passengers.treasurer)].faceID);
		}
		
		if (chref.Fellows.Passengers.carpenter == "-1")
		{
			AddFaceGroup(strAccess,"FACE128_carpenter");
		}
		else
		{
			AddFaceGroup(strAccess,"FACE128_"+Characters[sti(chref.Fellows.Passengers.carpenter)].faceID);
		}
		
		//fighters
		for(n=1; n<4; n++)
		{
			cn = GetOfficersIndex(chref,n);
			if( cn>=0 ) {
				AddFaceGroup(strAccess,"FACE128_"+Characters[cn].faceID);
			}
			else
			{
				AddFaceGroup(strAccess,"FACE128_fighter");
			}
		}
	}

	if(fillCode==1) // companions
	{
		for(n=1; n<COMPANION_MAX; n++)
		{
			cn = GetCompanionIndex(chref,n);
			if( cn>=0 ) {
				AddFaceGroup(strAccess,"FACE128_"+Characters[cn].faceID);
			}
		}
	}

	if(fillCode==2) // passengers
	{
		q = GetPassengersQuantity(chref);
		for(n=0; n<q; n++)
		{
			cn = GetPassenger(chref,n);
			if( cn>=0) 
			{
				AddFaceGroup(strAccess,"FACE128_"+Characters[cn].faceID);
			}
		}
	}
	
	if(fillCode==3) // officer for hire
	{
		
	}
	if(fillCode==4) // free passengers
	{
		q = GetPassengersQuantity(chref);
		for(n=0; n<q; n++)
		{
			cn = GetPassenger(chref,n);
			if( cn>=0) 
			{
				if (!CheckAttribute(&characters[cn], "prisoned") || sti(characters[cn].prisoned) != true)
				{
					if(!CheckAttribute(&characters[cn], "isbusy"))
					{
						if(!CheckAttribute(&characters[cn], "isquest")) // to_do
						{
							AddFaceGroup(strAccess,"FACE128_"+Characters[cn].faceID);
						}
					}
				}
			}
		}
	}
}

void AddShipPictureToList(string strAccess, ref chref) {
	int shipIndex = sti(chref.ship.type);
	if (shipIndex == SHIP_NOTUSED) return;
	
	ref realShip = GetRealShip(shipIndex);
	AddFaceGroup(strAccess,"SHIPS_"+realShip.BaseName+"_"+realShip.ship.upgrades.hull);
}

void FillShipList(string strAccess, ref chref)
{
	/*
	aref ar;
	makearef(ar, GameInterface.(strAccess));

	int n, cn, q;
	int iShipType;
	string sShip;

	for(n=0; n<COMPANION_MAX; n++)
	{
		cn = GetCompanionIndex(chref, n);
		if(cn != -1)
		{
			iShipType = GetCharacterShipType(/*&*//*characters[cn]);
			iShipType = sti(RealShips[iShipType].basetype);
			sShip = ShipsTypes[iShipType].name;
			AddFaceGroup(strAccess,"SHIPS_"+sShip);
		}
	}
	*/

	aref ar;
	makearef(ar, GameInterface.(strAccess));

	int n;
	string sShip;

	for(n = 0; n < GetArraySize(&ShipsTypes) - 1; n++)
	{
		if(CheckAttribute(ShipsTypes[n], "name"))
		sShip = ShipsTypes[n].name;
		else
			sShip = "";
		// AddFaceGroup(strAccess,"SHIPS_"+sShip);
		for (int i = 1; i <= 3; i++)
		{
			AddFaceGroup(strAccess,"SHIPS_"+sShip+"_"+i);
		}
	}
}

void FillItemsPicturesList(string strAccess, ref chref)  // to_do del
{
	AddFaceGroup(strAccess, "WEAPONS");
	/*
	AddFaceGroup(strAccess, "ITEMS_1");
	AddFaceGroup(strAccess, "ITEMS_2");
	AddFaceGroup(strAccess, "ITEMS_3");
	AddFaceGroup(strAccess, "ITEMS_4");
	*/
	return;
}
void FillUpgradesList(string strAccess, string smode, int iCannonMaterial)  // to_do del
{
	aref ar;
	makearef(ar, GameInterface.(strAccess));
	
	int iMax;
	if(smode == "cannons")
	{
		iMax = CANNON_TYPES_QUANTITY + 1;
	}
	else
	{
		iMax = 4;
	}
	if(smode == "cannons")
	{
		AddFaceGroup(strAccess,smode + "_UPGRADE_"+iCannonMaterial);
	}
	else
	{
		for(int i = 1; i < iMax; i++)
		{
			AddFaceGroup(strAccess,smode + "_UPGRADE_"+i);
		}
	}
}


void AddFaceGroup(string strAccess, string groupName)
{
	if( FindFaceGroupNum(strAccess,groupName)<0 )
	{
		aref ar;
		makearef(ar, GameInterface.(strAccess));
		string attrName = "t"+GetAttributesNum(ar);
		ar.(attrName) = groupName;
	}
}

int FindFaceGroupNum(string strAccess, string groupName)
{
	int n, q;
	aref aRoot, aCur;
	makearef(aRoot, GameInterface.(strAccess));

	q = GetAttributesNum(aRoot);
	for(n=0; n<q; n++)
	{
		aCur = GetAttributeN(aRoot,n);
		if( GetAttributeValue(aCur) == groupName ) return n;
	}

	return -1;
}

string GlobalStringConvert(string strID)
{
	return LanguageConvertString( GlobalLngFileID(), strID );
}

void LoadIcons(string sDirectory, string sFileMask, string sControlName, int iAddListSize) {
	object objFileFinder;
	aref arList, arFile;
	int iNumFiles;
	string sFile, attrName, sName;
	
	objFileFinder.dir = "resource\textures\" + sDirectory;
	objFileFinder.mask = sFileMask;
	
	CreateEntity(&objFileFinder, "FINDFILESINTODIRECTORY");
	makearef(arList, objFileFinder.filelist);
	iNumFiles = GetAttributesNum(arList);	
		
	for (int i = 0; i < iNumFiles; i++) {
		arFile = GetAttributeN(arList, i);
		sFile = GetAttributeValue(arFile);
		
		attrName = "pic" + (i + 1);
		sName = "f" + i;
		GameInterface.(sControlName).(attrName).name1 = sName;
		GameInterface.(sControlName).(attrName).FileName = sFile;
		GameInterface.(sControlName).(attrName).TexId = GetTexture(sDirectory + sFile);
	}
	
	GameInterface.(sControlName).ListSize = iNumFiles + iAddListSize;
	//SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,sControlName,-1);
	DeleteClass(&objFileFinder);
}

void UnloadIcons(string sControlName) {
	string sAttr;
	aref arPics;
	makearef(arPics, GameInterface.(sControlName));
	int iNumPics = sti(GameInterface.(sControlName).ListSize);
	
	for (int i = 0; i < iNumPics; i++) {
		sAttr = "pic" + (i + 1);
		ReleaseTexture(sti(arPics.(sAttr).TexId));
	}
	
	DeleteAttribute(&GameInterface, sControlName);
}

void CreateTooltip(string header, string text1, int color1, string text2, int color2, string text3, int color3, string text4, int color4, string picTexture, string picGroup, string picImage, int nPicWidth, int nPicHeight)
{
	// сохранить состояния окон и элементов
	int nSaveNodeState = -1;
	nSaveNodeState = XI_StoreNodeLocksWithOff();
	InterfaceStates.tooltip.savestate = nSaveNodeState;
	InterfaceStates.tooltip.oldcurrentnode = GetCurrentNode();
	// создать элементы тултипа:
	XI_MakeNode( "", "TOOLTIP_FADER", "tooltip_fader", 30000 ); // fader
	XI_MakeNode( "", "TOOLTIP_FRAME", "tooltip_frame", 30000 ); // окно
	XI_MakeNode( "", "TOOLTIP_TITLERECT", "tooltip_titlerect", 30001 ); // заголовок
	XI_MakeNode( "", "TOOLTIP_PICTURE", "tooltip_picture", 30001 ); // картинка
	XI_MakeNode( "", "TOOLTIP_TEXTRECT", "tooltip_textborder2", 30001 ); // окно для техт2
	XI_MakeNode( "", "TOOLTIP_TEXTRECT", "tooltip_textborder4", 30001 ); // окно для техт4
	XI_MakeNode( "", "TOOLTIP_TITLE", "tooltip_titile", 30002 ); // заголовок
	XI_MakeNode( "", "TOOLTIP_TEXT1", "tooltip_text1", 30002 ); //
	XI_MakeNode( "", "TOOLTIP_TEXT2", "tooltip_text2", 30002 ); //
	XI_MakeNode( "", "TOOLTIP_TEXT3", "tooltip_text3", 30002 ); //
	XI_MakeNode( "", "TOOLTIP_TEXT4", "tooltip_text4", 30002 ); //
	SendMessage(&GameInterface,"lsslslslslsssll",MSG_INTERFACE_SET_TOOLTIP, header, text1,color1, text2,color2, text3,color3, text4,color4, picTexture, picGroup, picImage, nPicWidth, nPicHeight );
}

void CloseTooltip()
{
	// удалить элементы тултипа:
	XI_DeleteNode( "tooltip_fader" ); // окно
	XI_DeleteNode( "tooltip_frame" ); // окно
	XI_DeleteNode( "tooltip_titlerect" ); // заголовок
	XI_DeleteNode( "tooltip_picture" ); // картинка
	XI_DeleteNode( "tooltip_textborder2" ); // окно
	XI_DeleteNode( "tooltip_textborder4" ); // окно
	XI_DeleteNode( "tooltip_titile" ); // заголовок
	XI_DeleteNode( "tooltip_text1" ); //
	XI_DeleteNode( "tooltip_text2" ); //
	XI_DeleteNode( "tooltip_text3" ); //
	XI_DeleteNode( "tooltip_text4" ); //
	// воccтановить состояния окон и элементов
	if( CheckAttribute(&InterfaceStates,"tooltip.oldcurrentnode") ) {
		SetCurrentNode(InterfaceStates.tooltip.oldcurrentnode);
	}
	int nSaveNodeState = -1;
	if( CheckAttribute(&InterfaceStates,"tooltip.savestate") ) {
		nSaveNodeState = sti(InterfaceStates.tooltip.savestate);
	}
	if( nSaveNodeState!=-1 ) {
		XI_RestoreNodeLocks(nSaveNodeState);
		InterfaceStates.tooltip.savestate = -1;
	}
}

string GetMoralePicture(float fMoraleValue)
{
	if( fMoraleValue >= 75.0 ) {return "interfaces\flags\flag_1_64.tga.tx";}
	if( fMoraleValue >= 50.0 ) {return "interfaces\flags\flag_2_64.tga.tx";}
	if( fMoraleValue >= 25.0 ) {return "interfaces\flags\flag_3_64.tga.tx";}
	return "interfaces\flags\flag_4_64.tga.tx";
}

string GetExperiencePicture(float fExpValue)
{
	if( fExpValue >= 75.0 ) {return "interfaces\stars\Yellow_star1.tga.tx";}
	if( fExpValue >= 50.0 ) {return "interfaces\stars\Yellow_star2.tga.tx";}
	if( fExpValue >= 25.0 ) {return "interfaces\stars\Yellow_star3.tga.tx";}
	return "interfaces\stars\Yellow_star4.tga.tx";
}

string GetMoraleGroupPicture(float fMoraleValue)
{
	if( fMoraleValue >= 75.0 ) {return "high morale";}
	if( fMoraleValue >= 40.0 ) {return "medium morale";}
	return "low morale";
}

bool XI_FindFoldersWithoutNetsave(string sFindTemplate,aref arFoldersList)
{
	bool bRetVal = XI_FindFolders(sFindTemplate,arFoldersList);

	int num = GetAttributesNum(arFoldersList);
	int i = 0;
	for(i=0; i<num; i++) {
		if( "NetSaves" == GetAttributeValue(GetAttributeN(arFoldersList,i)) )
		{
			DeleteAttribute( arFoldersList, GetAttributeName(GetAttributeN(arFoldersList,i)) );
			return bRetVal;
		}
	}

	return bRetVal;
}

void ReadSavedOptionsEx(aref gopt, string fileName) {
	SendMessage(&GameInterface, "lsa", MSG_INTERFACE_LOADOPTIONS, fileName, gopt);
}

void SaveSavedOptionsEx(aref gopt, string fileName) {
	SendMessage(&GameInterface, "lsa", MSG_INTERFACE_SAVEOPTIONS, fileName, gopt);
}

// boal -->
void ReadSavedOptionsGlobal(aref gopt) {
	ReadSavedOptionsEx(gopt, "options");
}

void SaveSavedOptionsGlobal(aref gopt) {
	SaveSavedOptionsEx(gopt, "options");
}

void SaveStartGameParam()
{
    object gopt;

	ReadSavedOptionsGlobal(&gopt);

	ref optref = &gopt;

    optref.StartGameParam.PlayerProfile    		 = GameInterface.PROFILE_NAME.str;//PlayerProfile.name;
    optref.StartGameParam.MOD_SKILL_ENEMY_RATE   = MOD_SKILL_ENEMY_RATE;
    optref.StartGameParam.bHardcoreGame          = bHardcoreGame;
    optref.StartGameParam.bRechargePistolOnLine  = bRechargePistolOnLine;
	optref.StartGameParam.bSeaBattleSave		 = bSeaBattleSave;
	optref.StartGameParam.bPartitionSet          = bPartitionSet;
	optref.StartGameParam.bRains                 = bRains;
	optref.StartGameParam.iArcadeSails           = iArcadeSails;

	SaveSavedOptionsGlobal(&gopt);
}
void LoadStartGameParam()
{
    object gopt;

	ReadSavedOptionsGlobal(&gopt);

	ref optref = &gopt;

	if (CheckAttribute(optref, "StartGameParam.PlayerProfile"))
	{
    	GameInterface.PROFILE_NAME.str = optref.StartGameParam.PlayerProfile;
    }

    if (CheckAttribute(optref, "StartGameParam.MOD_SKILL_ENEMY_RATE"))
	{
    	MOD_SKILL_ENEMY_RATE = sti(optref.StartGameParam.MOD_SKILL_ENEMY_RATE);
		if(MOD_SKILL_ENEMY_RATE < 1 || MOD_SKILL_ENEMY_RATE > 10) 
		{
			MOD_SKILL_ENEMY_RATE = 4; 
		}
		else
		{
			if(MOD_SKILL_ENEMY_RATE%2 == 1) MOD_SKILL_ENEMY_RATE = 4;
		}
    }
    if (CheckAttribute(optref, "StartGameParam.bHardcoreGame"))
	{
    	bHardcoreGame = sti(optref.StartGameParam.bHardcoreGame);
    }
    if (CheckAttribute(optref, "StartGameParam.bRechargePistolOnLine"))
	{
    	bRechargePistolOnLine = sti(optref.StartGameParam.bRechargePistolOnLine);
    }	
	if (CheckAttribute(optref, "StartGameParam.bSeaBattleSave"))
	{
    	bSeaBattleSave = sti(optref.StartGameParam.bSeaBattleSave);
    }
	if (CheckAttribute(optref, "StartGameParam.bPartitionSet"))
	{
    	bPartitionSet = sti(optref.StartGameParam.bPartitionSet);
    }

	if (CheckAttribute(optref, "StartGameParam.bRains"))
	{
    	bRains = sti(optref.StartGameParam.bRains);
    }		
	
    if (CheckAttribute(optref, "StartGameParam.iArcadeSails"))
	{
    	iArcadeSails = sti(optref.StartGameParam.iArcadeSails);
    }
}

void LoadPlayerProfileDefault()
{
    object gopt;

	ReadSavedOptionsGlobal(&gopt);

	ref optref = &gopt;

	if (CheckAttribute(optref, "StartGameParam.PlayerProfile"))
	{
    	PlayerProfile.name = optref.StartGameParam.PlayerProfile;
    }
}

// boal сложность -->
string GetLevelComplexity(int _Level_Complexity)
{
	string level = _Level_Complexity;
	switch (_Level_Complexity)
	{
	    case 1 :
            return XI_ConvertString("m_Complexity_1"); //Матрос "Халява";
            break;
        case 2 :
            return XI_ConvertString("m_Complexity_2"); // Боцман "Юнга";
            break;
        case 3 :
            return XI_ConvertString("m_Complexity_3");//Шкипер "Матрос";
            break;
        case 4 :
            return XI_ConvertString("m_Complexity_4");//Лейтенант "Боцман";
            break;
        case 5 :
            return XI_ConvertString("m_Complexity_5");
            break;
        case 6 :
            return XI_ConvertString("m_Complexity_6");
            break;
        case 7 :
            return XI_ConvertString("m_Complexity_7");//Командор "Пират";
            break;
        case 8 :
            return XI_ConvertString("m_Complexity_8");
            break;
        case 9 :
            return XI_ConvertString("m_Complexity_9");
            break;
        case 10 :
            return XI_ConvertString("m_Complexity_10");
            break;
    }
	return level;
}

string GetItemDescribe(int iGoodIndex)
{
	string GoodName = Items[iGoodIndex].name;
	ref    arItm = &Items[iGoodIndex];
	int    lngFileID = LanguageOpenFile("ItemsDescribe.txt");
    string describeStr = "";

	if (CheckAttribute(arItm, "groupID"))
	{
		aref arGrape;
		if(arItm.groupID == GUN_ITEM_TYPE)
		{
			if(IsBulletGrape(arItm.type.t1.bullet))
			{
				makearef(arGrape, arItm.type.t1);
				describeStr += GetAssembledString( LanguageConvertString(lngFileID,"weapon grape parameters"), arGrape) + newStr();
			}
			else
				describeStr += GetAssembledString( LanguageConvertString(lngFileID,"weapon gun parameters"), arItm) + newStr();
		}
		if(arItm.groupID == MUSKET_ITEM_TYPE)
		{
			if(IsBulletGrape(arItm.type.t1.bullet))
			{
				makearef(arGrape, arItm.type.t1);
				describeStr += GetAssembledString( LanguageConvertString(lngFileID,"weapon grape parameters"), arGrape) + newStr();
			}
			else
				describeStr += GetAssembledString( LanguageConvertString(lngFileID,"mushket parameters"), arItm) + newStr();
		}
		if(arItm.groupID==BLADE_ITEM_TYPE)
		{
			SetBladeWeightAttack(arItm);
			describeStr += GetAssembledString(
				LanguageConvertString(lngFileID,"weapon blade parameters"),
				arItm) + newStr();
			if (CheckAttribute(arItm, "FencingType"))
			{
    			arItm.FencingTypeName = XI_ConvertString(arItm.FencingType);
    			describeStr += GetAssembledString( LanguageConvertString(lngFileID,"weapon blade type"), arItm) + newStr();
			}
			else
			{
                describeStr += "ERROR" + newStr();
			}
		}
	}

	describeStr = describeStr + GetAssembledString(LanguageConvertString(lngFileID, Items[iGoodIndex].describe), &Items[iGoodIndex]);
	if (CheckAttribute(arItm, "potion"))
	{
		if (CheckAttribute(arItm, "potion.health"))
		{
			describeStr += NewStr() + LanguageConvertString(lngFileID, "Potion parameters")+":";
			describeStr += " "+LanguageConvertString(lngFileID, "health value");
			if (stf(arItm.potion.health) >= 0)
			{	
				describeStr += "+" + sti(arItm.potion.health);
			} 
			else
			{	
				describeStr += "" + sti(arItm.potion.health);
			}
		}
	}
	if(arItm.id == "lacrima_patris" && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_GALEON_SM)
	{
		if(CheckAttribute(arItm,"KillerBonus.RangeBonus"))
		{
			aref KillerB;
			makearef(KillerB, arItm.KillerBonus);
			describeStr += newStr() + GetAssembledString( LanguageConvertString(lngFileID,"lacrima_patris_parameters"), KillerB) + newStr();
		}
	}
	if(arItm.id == "talisman17")
	{
		if(CheckAttribute(arItm,"QBonus"))
		{
			describeStr += newStr() + GetAssembledString( LanguageConvertString(lngFileID,"talisman17_quests"), arItm) + newStr();
		}
		else
		{
			describeStr += newStr() + LanguageConvertString(lngFileID, "talisman17_questsNoBonus") + newStr();
		}
	}
	if(arItm.id == "talisman18")
	{
		if(CheckAttribute(arItm,"QBonus"))
		{
			describeStr += newStr() + GetAssembledString( LanguageConvertString(lngFileID,"talisman18_Bonus"), arItm) + newStr();
		}
		else
		{
			describeStr += newStr() + LanguageConvertString(lngFileID, "talisman18_NoBonus") + newStr();
		}
	}
	if(arItm.id == "talisman19")
	{
		if(IsEquipCharacterByArtefact(pchar, "talisman19"))
		{
			describeStr = LanguageConvertString(lngFileID, "talisman19_InSlot") + newStr();
			
		}
		else
		{
			describeStr = GetAssembledString( LanguageConvertString(lngFileID,"itmdescr_talisman19"), pchar) + newStr();
		}
	}
	if(CheckAttribute(arItm, "UpgradeStage"))
	{
		describeStr += newStr() + LanguageConvertString(lngFileID,"UpgradeStageInfo_" + arItm.id + "_" + sti(arItm.UpgradeStage));
	}
    describeStr += newStr() + XI_ConvertString("weight") + " " + FloatToString(stf(arItm.weight), 1);
    
	LanguageCloseFile(lngFileID);
	
	return describeStr;
}
// boal <--

string GetItemName(string sItemID)
{
	ref refItem = ItemsFromID(sItemID);
	if (CheckAttribute(refItem, "name"))
		return GetConvertStr(refItem.name, "ItemsDescribe.txt");
	else
		return sItemID;
}

#event_handler("Tips_GetTipsDirectory","Tips_GetTipsDirectory");
string Tips_GetTipsDirectory() {
  return "interfaces\tips\" + LanguageGetLanguage();
}

//#event_handler("Tips_GetText", "Tips_GetText");
aref Tips_GetText()
{
	DeleteAttribute(&InterfaceStates, "Tip");
	aref arTip;
	makearef(arTip, InterfaceStates.Tip);
	arTip.font = "interface_normal";
	arTip.color = argb(255, 255, 255, 255);
	arTip.scale = 3.0;
	arTip.pos_x = sti(showWindow.right) / 2;
	arTip.pos_y = sti(showWindow.bottom) / 5 * 4;
	arTip.linespace = 50;
	
	string sTipsFile = "GameTips.txt";
	int nTips = GetFileStringsQuantity(sTipsFile);
	int iRandomTip = rand(nTips-1) + 1;
	string sText = GetConvertStr("Tip" + iRandomTip, sTipsFile);
	FillStringsAttr(arTip, "text", "strings", sText, "interface_normal", 3.0, 1000);
	return arTip;
}

void FillStringsAttr(aref arMain, string textAttr, string nAttr, string sText, string sFont, float fScale, int maxWidth)
{
	int fullWidth;
	string sLeft, sRight;
	fullWidth = GetStringWidth(sText, sFont, fScale);
	int iSpace;
	string sAttr;
	int iString;
	iString = 1;
	sLeft = sText;
	sRight = "";
	while(fullWidth > maxWidth)
	{
		iSpace = GetLastSeparatorPos(sLeft, " ", sFont, fScale, maxWidth);
		if(iSpace != -1)	// искомый пробел существует
		{
			sAttr = textAttr + iString;
			sRight = strright(sLeft, strlen(sLeft) - iSpace - 1);	// правая часть
			sLeft = strleft(sLeft, iSpace);	// левая часть
			arMain.(sAttr) = sLeft;	// записываем текст в очередной атрибут
			sLeft = sRight;
			iString++;
		}
		else	// искомого пробела не существует
			break;
		fullWidth = GetStringWidth(sLeft, sFont, fScale);
	}
	arMain.(nAttr) = iString;
	if(iString > 1)
	{
		sAttr = textAttr + iString;
		arMain.(sAttr) = sRight;
	}
}

int GetLastSeparatorPos(string sText, string sSepar, string sFont, float fScale, int maxWidth)
{
	string sTemp;
	int iSpace, iPrevSpace, curWidth;
	iPrevSpace = -1;
	while(true)
	{
		iSpace = findSubStr(sText, sSepar, iPrevSpace + 1);
		if(iSpace != -1)	// если есть пробел
		{
			sTemp = strcut(sText, 0, iSpace);
			curWidth = GetStringWidth(sTemp, sFont, fScale);
			if(curWidth > maxWidth)	// если текущий пробел слишком далеко
			{
				if(iPrevSpace > 0)	// если есть предыдущий пробел
				{
					iSpace = iPrevSpace;	// предыдущий пробел и есть искомый
					break;
				}
			}
		}
		else	// если пробела нет
		{
			if(iPrevSpace != -1)
				iSpace = iPrevSpace;
			break;
		}
		iPrevSpace = iSpace;
	}
	return iSpace;
}

void GetNodePosition(string sNode, ref x1, ref y1, ref x2, ref y2)
{
	SendMessage(&GameInterface, "lslleeee", MSG_INTERFACE_MSG_TO_NODE, sNode, -1, 5, &x1, &y1, &x2, &y2);
}

void SetNodePosition(string sNode, int x1, int y1, int x2, int y2)
{
	SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, sNode, -1, 4, x1, y1, x2, y2);
}

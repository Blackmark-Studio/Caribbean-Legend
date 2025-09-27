void EI_CreateFrame(string sNodeName, int x1, int y1, int x2, int y2)
{
	SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 1, "LE_ICONS");

	// UPLEFT
	SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, "BORDER_UPLEFT", argb(255, 128, 128, 128), x1, y1, x1 + 10, y1 + 10);
	// URRIGHT
	SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, "BORDER_UPRIGHT", argb(255, 128, 128, 128), x2 - 10, y1, x2, y1 + 10);
	// DOWNLEFT
	SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, "BORDER_DOWNLEFT", argb(255, 128, 128, 128), x1, y2 - 10, x1 + 10, y2);
	// DOWNRIGHT
	SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, "BORDER_DOWNRIGHT", argb(255, 128, 128, 128), x2 - 10, y2 - 10, x2, y2);
	// LEFT
	SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, "BORDER_LEFT", argb(255, 128, 128, 128), x1, y1 + 10, x1 + 1, y2 - 10);
	// RIGHT
	SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, "BORDER_RIGHT", argb(255, 128, 128, 128), x2 - 1, y1 + 10, x2, y2 - 10);
	// UP
	SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, "BORDER_UP", argb(255, 128, 128, 128), x1 + 10, y1, x2 - 10, y1 + 1);
	// DOWN
	SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, "BORDER_DOWN", argb(255, 128, 128, 128), x1 + 10, y2 - 1, x2 - 10, y2);
}

void EI_CreateFrameWithBack(string sBackNodeName, string sFrameNodeName, string sBackImage, int x1, int y1, int x2, int y2)
{
	// Back
	if (sBackNodeName != "")
	{
		SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, sBackNodeName, 1, "PAPIRUS");
		SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sBackNodeName, 0, sBackImage, argb(255, 128, 128, 128), x1, y1, x2, y2);
	}

	// Frame
	if (sFrameNodeName != "") { EI_CreateFrame(sFrameNodeName, x1, y1, x2, y2); }
}

void EI_CreateTriggerFrame(int iFrameType, int x1, int y1, int x2, int y2)
{
	switch(iFrameType)
	{
		case 1:
			XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "IMAGECOLLECTION", "TRIGGER_NODE_FRAME", 900);
			EI_CreateFrame("TRIGGER_NODE_FRAME", x1, y1, x2, y2);
			SetPictureBlind("TRIGGER_NODE_FRAME", true, argb(255, 75, 75, 75), argb(255, 165, 165, 165), 1.0, 1.0);
		break;
		case 2:
			XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "PICTURE", "TRIGGER_NODE_FRAME", 900);
			SetNewGroupPicture("TRIGGER_NODE_FRAME", "LE_ICONS", "traitframe");
			SetNodePosition("TRIGGER_NODE_FRAME", x1, y1, x2, y2);
			SetPictureBlind("TRIGGER_NODE_FRAME", true, argb(255, 75, 75, 75), argb(255, 165, 165, 165), 1.0, 1.0);
		break;
		case 3:
			XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "PICTURE", "TRIGGER_NODE_FRAME", 900);
			SetNewGroupPicture("TRIGGER_NODE_FRAME", "LE_ICONS", "glow1");
			SetNodePosition("TRIGGER_NODE_FRAME", x1, y1, x2, y2);
			SetPictureBlind("TRIGGER_NODE_FRAME", true, argb(255, 75, 75, 75), argb(255, 165, 165, 165), 1.0, 1.0);
		break;
	}
}

void EI_DeleteTriggerFrame()
{
	XI_DeleteNode("TRIGGER_NODE_FRAME");
}

// create vertical line with width = 3
void EI_CreateVLine(string sNodeName, int x1, int y1, int y2, int iNumLines, int iWidth)
{
	SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 1, "MAIN_ICONS");
	for (int i=0; i<iNumLines; i++)
	{
		SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, "BORDER_LEFT", argb(255, 128, 128, 128), x1 + i * iWidth, y1, x1 + i * iWidth + 3, y2);
	}
}

// create horizontal line with width = 3
void EI_CreateHLine(string sNodeName, int x1, int y1, int x2, int iNumLines, int iHeight)
{
	SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 1, "MAIN_ICONS");
	for (int i=0; i<iNumLines; i++)
	{
		SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, "BORDER_CENTER", argb(255, 128, 128, 128), x1, y1 + i * iHeight, x2, y1 + i * iHeight + 3);
	}
}

void EI_CreateSubstrate(string sNodeName, string sSubsrateType, int x1, int y1, int x2, int y2)
{
	SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 1, "MAIN_ICONS");
	// SUBSTRATE
	SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, sSubsrateType, argb(255, 128, 128, 128), x1, y1, x2, y2);
	EI_CreateHLine(sNodeName, x1,y1-3,x2,1, 4);
}

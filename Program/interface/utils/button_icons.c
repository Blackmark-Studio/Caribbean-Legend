// управление картинками в кнопках
void TextButton_UseImage(string sNode, bool bUse)
{
	SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, sNode, 2, bUse);
}

void TextButton_SetImageTexture(string sNode, string sTexture, float x1, float y1, float x2, float y2)
{
	SendMessage(&GameInterface, "lslsffff", MSG_INTERFACE_MSG_TO_NODE, sNode, 3, sTexture, x1, y1, x2, y2);
}

void TextButton_SetImageGroup(string sNode, string sGroup, string sPicture)
{
	SendMessage(&GameInterface, "lslss", MSG_INTERFACE_MSG_TO_NODE, sNode, 4, sGroup, sPicture);
}

void TextButton_SetImageSize(string sNode, int width, int height)
{
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, sNode, 5, width, height);
}

void TextButton_SetImageOffset(string sNode, int offsetX)
{	
	SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, sNode, 6, offsetX);
}

void TextButton_SetImageColor(string sNode, int iColor)
{
	if(iColor < 0)
		iColor = 0;
	SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, sNode, 7, iColor);
}

void TextButton_ShowImage(string sNode, bool isShow)
{
	SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, sNode, 8, isShow);
}

void TextButton_SetTextureImageDefault(string sNode, string sTexture, int width, int height, int offsetX)
{
	TextButton_UseImage(sNode, true);
	TextButton_SetImageTexture(sNode, sTexture, 0.0, 0.0, 1.0, 1.0);
	TextButton_SetImageSize(sNode, width, height);
	TextButton_SetImageOffset(sNode, offsetX);
	TextButton_ShowImage(sNode, true);
}

void TextButton_SetGroupImageDefault(string sNode, string sGroup, string sPicture, int width, int height, int offsetX)
{
	TextButton_UseImage(sNode, true);
	TextButton_SetImageGroup(sNode, sGroup, sPicture);
	TextButton_SetImageSize(sNode, width, height);
	TextButton_SetImageOffset(sNode, offsetX);
	TextButton_ShowImage(sNode, true);
}

void TextButton_RemoveImage(string sNode)
{
	TextButton_ShowImage(sNode, false);
	TextButton_SetImageOffset(sNode, 0);
	TextButton_SetImageSize(sNode, 0, 0);
}
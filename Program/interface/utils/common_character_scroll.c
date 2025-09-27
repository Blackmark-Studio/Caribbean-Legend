// Общий метод заполнения карусели персонажами из команды игрока по фильтру IsFellowOkToFunc
// scrollToNull нужен просто из-за отличий в интерфейсах
// direction если нужно развернуть порядок персонажей, в частности на верфи при покупке корабля
void FillScrollWithCharacters(ref firstChr, string scrollNodeName, string IsFellowOkToFunc, bool withPchar, ref scrollToNull, int direction)
{
	scrollToNull = -1;
	string attributeName;
	int m = 0;
	DeleteAttribute(&GameInterface, scrollNodeName);
	object fellows;

	// Вывести персонажа первым в карусели
	if (CheckAttribute(firstChr, "index")) 
	{
		attributeName = "f" + firstChr.index;
		fellows.(attributeName) = firstChr.index;
	}

	// Собираем остальных персонажей
	AddAllFellows(&fellows, pchar, withPchar);
	int fellowsQty = GetAttributesNum(&fellows);
	int inversedI = fellowsQty-1;

	GameInterface.(scrollNodeName).current = 0;
	GameInterface.(scrollNodeName).NotUsed = 6;
	GameInterface.(scrollNodeName).ListSize = fellowsQty;
	GameInterface.(scrollNodeName).ImagesGroup.t0 = "EMPTYFACE";
	FillFaceList(scrollNodeName +".ImagesGroup", pchar, 0);
	FillFaceList(scrollNodeName +".ImagesGroup", pchar, 1);
	FillFaceList(scrollNodeName +".ImagesGroup", pchar, 2);
	GameInterface.(scrollNodeName).BadTex1 = 0;
	GameInterface.(scrollNodeName).BadPic1 = "emptyface";

	// Выводим по фильтру
	for (int i=0; i < fellowsQty; i++)
	{
		int pointer = i;
		if (direction < 0) pointer = inversedI;
		inversedI --;
		ref chr = GetCharacter(sti(GetAttributeValue(GetAttributeN(&fellows, pointer))));
		if (!call IsFellowOkToFunc(chr)) continue;

		attributeName = "pic" + (m + 1);
		GameInterface.(scrollNodeName).(attributeName).character = chr.index;
		GameInterface.(scrollNodeName).(attributeName).img1 = GetFacePicName(chr);
		GameInterface.(scrollNodeName).(attributeName).tex1 = FindFaceGroupNum(scrollNodeName+".ImagesGroup","FACE128_"+chr.FaceID);
		m++;
	}
	GameInterface.(scrollNodeName).ListSize = m + 2;
}

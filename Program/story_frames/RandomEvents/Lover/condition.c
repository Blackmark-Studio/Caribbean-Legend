bool SF_InitConditions(ref context, ref situation, bool fromStory = false)
{
	if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
	{
		situation.a.a = 100;
	}
	if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
	{
		situation.a.b = 100;
	}
	if (GetAttributesNum(situation) == 0) return false; // хотя бы 1 вариант
	return true;
}
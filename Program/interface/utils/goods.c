string GetGoodName(ref ref_Id_Idx)
{
	ref refGood = FindGood_VT(&ref_Id_Idx);

	if (CheckAttribute(refGood, "modname"))
	{
		return GetConvertStr(refGood.name, "mods\"+refGood.modname+"\GoodsDescribe.txt");
	}
	return GetConvertStr(refGood.name, "GoodsDescribe.txt");
}

string GetGoodDescr(ref ref_Id_Idx)
{
	ref refGood = FindGood_VT(&ref_Id_Idx);

	if (CheckAttribute(refGood, "modname"))
	{
		return GetConvertStr(refGood.name + "_descr", "mods\"+refGood.modname+"\GoodsDescribe.txt");
	}
	return GetConvertStr(refGood.name + "_descr", "GoodsDescribe.txt");
}

string GetGoodImageGroup(ref refGood)
{
	if (!CheckAttribute(refGood, "picTexture")) return "GOODS";

	return refGood.picTexture;
}
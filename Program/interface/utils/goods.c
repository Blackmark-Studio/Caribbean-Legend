string GetGoodName(ref ref_Id_Idx)
{
	ref refGood = FindGood_VT(&ref_Id_Idx);
	return GetConvertStr(refGood.name, "GoodsDescribe.txt");
}

// boal -->

string GetGoodsNameSeaSection(ref ref_Id_Idx)
{

	ref refGood = FindGood_VT(&ref_Id_Idx);

	string sKeyFile = "SeaSection.txt";
	return GetConvertStr("seg_" + refGood.name, sKeyFile);
}

string GetSimpleSeaSectionKey(string sKey)
{
	return GetConvertStr(sKey, "SeaSection.txt");
}

string GetGoodsNameAlt(int iIdx)
{
	return GetGoodsNameSeaSection(&Goods[iIdx]);
}

string GetGoodDescr(ref ref_Id_Idx)
{
	ref refGood = FindGood_VT(&ref_Id_Idx);
	return GetConvertStr(refGood.name + "_descr", "GoodsDescribe.txt");
}

string GetGoodImageGroup(ref refGood)
{
	if (!CheckAttribute(refGood, "picTexture")) return "GOODS";

	return refGood.picTexture;
}

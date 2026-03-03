#define ITEM_PACK_GENERIC "generic"
#define ITEM_PACK_ELITE "elite"

#define ITEM_BLADE_TYPE_FLAG_LIGHT			      1 // рапиры и шпаги - лёгкое оружие
#define ITEM_BLADE_TYPE_FLAG_MEDIUM			      2 // сабли - среднее оружие
#define ITEM_BLADE_TYPE_FLAG_HEAVY    			  4 // палаши и тесаки - тяжелое оружие
#define ITEM_BLADE_TYPE_FLAG_ALL    			  7 // все
int gItemBladeTypes[3] = {1, 2, 4};

#define ITEM_ARMOR_TYPE_FLAG_LIGHT			      1
#define ITEM_ARMOR_TYPE_FLAG_MEDIUM			      2
#define ITEM_ARMOR_TYPE_FLAG_HEAVY    			  4
#define ITEM_ARMOR_TYPE_FLAG_ALL    			  7
int gItemArmorTypes[3] = {1, 2, 4};

// качественные группы
#define ITEM_QUALITY_FLAG_POOR                	  1  // плохое
#define ITEM_QUALITY_FLAG_ORDINARY                2  // обычное
#define ITEM_QUALITY_FLAG_GOOD                    4  // хорошее
#define ITEM_QUALITY_FLAG_EXCELLENT               8  // отличное
#define ITEM_QUALITY_FLAG_UNIQUE				  16 // уникальное
#define ITEM_QUALITY_FLAG_ALL				      31 // все
int gItemQualityGroups[5] = {1, 2, 4, 8, 16};

// целевые группы
#define ITEM_GROUP_FLAG_QUEST                 1 // квестовое оружие
#define ITEM_GROUP_FLAG_YANKEE                2 // рабы, бунтовщики, каторжники
#define ITEM_GROUP_FLAG_NATIVE                4 // мезоамерика
#define ITEM_GROUP_FLAG_MARGINAL              8 // маргиналы - низкуровневые пираты, граждане, бандиты
#define ITEM_GROUP_FLAG_SOLDIER               16 // солдаты, пираты
#define ITEM_GROUP_FLAG_OFFICER               32 // офицерское оружие, капитаны
#define ITEM_GROUP_FLAG_PERSIAN               64 // индо-персидские клинки
int gItemTargetGroups[7] = {1, 2, 4, 8, 16, 32, 64};

void SetNPCEquip(ref rChar, ref rItems, bool bMushketer)
{
	string sBladeID = "";
	string sGunID = "";
	string sBulletID = "";
	string sArmorID = "";
	int nItemsCount = GetArraySize(rItems);
	int nItemIndex = rand(nItemsCount - 1);
	ref rItem = &rItems[nItemIndex];

	sBladeID = rItems[nItemIndex].blade;
	sGunID = rItems[nItemIndex].gun;
	sBulletID = rItems[nItemIndex].bullet;
	sArmorID = rItems[nItemIndex].armor;

	if (bMushketer)
	{
		rChar.MushketBulletType = sBulletID;
		rChar.MushketType = sGunID;
	}
	else
	{
		rChar.GunBulletType = sBulletID;
		rChar.GunType = sGunID;
		rChar.BladeType = sBladeID;
	}
	//Log_Info("SetNPCEquip: sArmorID = "+sArmorID+"; sBladeID="+sBladeID+"; sGunID="+sGunID+"; sBulletID="+sBulletID);

	if (sArmorID != "")
	{
		GiveItem2Character(rChar, sArmorID);
		EquipCharacterbyItem(rChar, sArmorID);
	}
}

void GenerateItemsForCharacter(ref rChar, string sType, ref rSoldier, ref rMushketer)
{
	//trace("GenerateItemsForCharacter: "+rChar.id);
	string sGenerateCallback = GetAttributeOrDefault(rChar, "GenerateItemsCallback", "");
	if (sGenerateCallback != "")
	{
		call sGenerateCallback(rChar, sType, rSoldier, rMushketer);
		return;
	}

	int i, j, k, n;
	int iBladeTypeFlags, iBladeQualityFlags, iBladeGroupFlags, iItemQualityFlags, iMushketQualityFlags, iBulletQuality;
	GetItemFiltersBlade(rChar, sType, &iBladeTypeFlags, &iBladeQualityFlags, &iBladeGroupFlags);
	GetItemFiltersItems(rChar, sType, &iItemQualityFlags);

	GetMushketFiltersItems(rChar, sType, &iMushketQualityFlags);
	GetBulletQuality(rChar, sType, &iBulletQuality);
	int aBlades[1];
	int aGuns[1];
	int aMushkets[1];
	int aArmours[1];

	FindArmors(&aArmours, iItemQualityFlags, ITEM_ARMOR_TYPE_FLAG_ALL);
	int iArmoursCount = GetArraySize(&aArmours);

	int iGunIdx;
	int iArmorIdx;
	int iBladeIdx;
	string sBullet;
	string sGun;
	string sArmor;
	string sBlade;
	if (rSoldier != nullptr)
	{
		n = 0;
		FindBlades(&aBlades, iBladeTypeFlags, iBladeQualityFlags, iBladeGroupFlags);
		FindGuns(&aGuns, iItemQualityFlags, GUN_ITEM_TYPE);
		int iBladesCount = GetArraySize(&aBlades);
		int iGunsCount = GetArraySize(&aGuns);
		for (i = 0; i < iBladesCount; i++)
		{
			for (j = 0; j < iArmoursCount; j++)
			{
				for (k = 0; k < iGunsCount; k++)
				{
					iGunIdx = aGuns[k];
					iArmorIdx = aArmours[j];
					iBladeIdx = aBlades[i];
					sBullet = GetBestBulletWithLimit(&Items[iGunIdx], iBulletQuality);
					sGun = Items[iGunIdx].id;
					sArmor = "";
					if (rand(1) == 0 || sType == ITEM_PACK_ELITE) //даем броню в 50% случаев. Потом подумаем как лучше
					{
						if (iArmorIdx != -1)
						{
							sArmor = Items[iArmorIdx].id;
						}
					}
					sBlade = Items[iBladeIdx].id;

					n++;
					SetArraySize(rSoldier, n);
					rSoldier[n-1].blade = sBlade;
					rSoldier[n-1].gun = sGun;
					rSoldier[n-1].bullet = sBullet;
					rSoldier[n-1].armor = sArmor;
				}
			}
		}
	}

	if (rMushketer != nullptr)
	{
		n = 0;
		FindGuns(&aMushkets, iMushketQualityFlags, MUSKET_ITEM_TYPE);
		int iMushketsCount = GetArraySize(&aMushkets);
		for (j = 0; j < iArmoursCount; j++)
		{
			for (k = 0; k < iMushketsCount; k++)
			{
				iGunIdx = aMushkets[k];
				iArmorIdx = aArmours[j];
				sBullet = GetBestBulletWithLimit(&Items[iGunIdx], iBulletQuality);
				sGun = Items[iGunIdx].id;
				sArmor = "";
				if (rand(1) == 0 || sType == ITEM_PACK_ELITE) //даем броню в 50% случаев. Потом подумаем как лучше
				{
					sArmor = Items[iArmorIdx].id;
				}

				n++;
				SetArraySize(rMushketer, n);
				rMushketer[n-1].blade = "";
				rMushketer[n-1].gun = sGun;
				rMushketer[n-1].bullet = sBullet;
				rMushketer[n-1].armor = sArmor;
			}
		}
	}

	//trace("rChar = "+rChar.id+"; iBladesCount = "+iBladesCount+"; iGunsCount = "+iGunsCount+"; iMushketsCount = "+iMushketsCount+"; iArmoursCount = "+iArmoursCount);
	//trace("end GenerateItemsForCharacter: "+rChar.id);
}


void GetItemFiltersBlade(ref rChar, string sType, ref rBladeTypeFlags, ref rQualityFlags, ref rGroupFlags)
{
	string sPhantomType;
	string blade;
	int iRank = sti(rChar.rank);
	rBladeTypeFlags = ITEM_BLADE_TYPE_FLAG_ALL;
	if(CheckAttribute(rChar, "PhantomType"))
	{
		sPhantomType = rChar.PhantomType;
		switch( sPhantomType )
		{
			case "slave" 		:
				rQualityFlags = ITEM_QUALITY_FLAG_ALL;
				rGroupFlags = ITEM_GROUP_FLAG_YANKEE;
			break;
			case "native" 		:
				rQualityFlags = ITEM_QUALITY_FLAG_ALL;
				rGroupFlags = ITEM_GROUP_FLAG_YANKEE;
			break;
			case "marginal" 	:
				if (iRank > 20)
				{
					rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD;
				}
				else
				{
					rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY;
				}
				rGroupFlags = ITEM_GROUP_FLAG_MARGINAL;
			break;
			case "skeleton" 	:
				if (iRank > 20)
				{
					rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD;
				}
				else
				{
					rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY;
				}
				rGroupFlags = ITEM_GROUP_FLAG_MARGINAL;
			break;
			case "hunter" 		:
				rQualityFlags = ITEM_QUALITY_FLAG_ALL;
				if (iRank > 20)
				{
					rGroupFlags = ITEM_GROUP_FLAG_SOLDIER;
				}
				else
				{
					rGroupFlags = or(ITEM_GROUP_FLAG_MARGINAL, ITEM_GROUP_FLAG_SOLDIER);
				}

			break;
			case "mercenary"	:
				if (iRank > 25)
				{
					rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD + ITEM_QUALITY_FLAG_EXCELLENT;
					rGroupFlags = ITEM_GROUP_FLAG_OFFICER;
				}
				else if (iRank > 15)
				{
					rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD;
					rGroupFlags = ITEM_GROUP_FLAG_SOLDIER + ITEM_GROUP_FLAG_OFFICER;
				}
				else
				{
					rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD;
					rGroupFlags = ITEM_GROUP_FLAG_SOLDIER;
				}
			break;
			case "governor" 	:
				rQualityFlags = ITEM_QUALITY_FLAG_GOOD + ITEM_QUALITY_FLAG_EXCELLENT;
				rGroupFlags = ITEM_GROUP_FLAG_OFFICER;
			break;
			case "itza" 		:
				rQualityFlags = ITEM_QUALITY_FLAG_ALL;
				rGroupFlags = ITEM_GROUP_FLAG_NATIVE;
			break;
			case "quest" 		:
				rQualityFlags = ITEM_QUALITY_FLAG_ALL;
				rGroupFlags = ITEM_GROUP_FLAG_SOLDIER;
			break;
			case "pofficer" 	:
				if (iRank > 25)
				{
					rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD;
					rGroupFlags = ITEM_GROUP_FLAG_SOLDIER;
				}
				else if (iRank > 15)
				{
					rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD;
					rGroupFlags = ITEM_GROUP_FLAG_SOLDIER + ITEM_GROUP_FLAG_MARGINAL;
				}
				else
				{
					rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD;
					rGroupFlags = ITEM_GROUP_FLAG_MARGINAL;
				}
			break;
			case "officer" 		:
				if (iRank > 25 || sType == ITEM_PACK_ELITE)
				{
					rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD + ITEM_QUALITY_FLAG_EXCELLENT;
					rGroupFlags = ITEM_GROUP_FLAG_OFFICER;
				}
				else if (iRank > 15)
				{
					rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD;
					rGroupFlags = ITEM_GROUP_FLAG_SOLDIER + ITEM_GROUP_FLAG_OFFICER;
				}
				else
				{
					rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD;
					rGroupFlags = ITEM_GROUP_FLAG_SOLDIER;
				}
			break;
			case "soldier"		:
				if (iRank > 25 || sType == ITEM_PACK_ELITE)
				{
					rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD + ITEM_QUALITY_FLAG_EXCELLENT;
					rGroupFlags = ITEM_GROUP_FLAG_SOLDIER + ITEM_GROUP_FLAG_OFFICER;
				}
				else if (iRank > 15)
				{
					rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD;
					rGroupFlags = ITEM_GROUP_FLAG_SOLDIER + ITEM_GROUP_FLAG_OFFICER;
				}
				else
				{
					rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY;
					rGroupFlags = ITEM_GROUP_FLAG_SOLDIER;
				}
			break;
			case "pirate"		:
				if (iRank > 25 || sType == ITEM_PACK_ELITE)
				{
					rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD;
					rGroupFlags = ITEM_GROUP_FLAG_SOLDIER;
				}
				else if (iRank > 15)
				{
					rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD;
					rGroupFlags = ITEM_GROUP_FLAG_SOLDIER + ITEM_GROUP_FLAG_MARGINAL;
				}
				else
				{
					rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY;
					rGroupFlags = ITEM_GROUP_FLAG_MARGINAL;
				}
			break;
			case "citizen"		:
				if (iRank > 25 || sType == ITEM_PACK_ELITE)
				{
					rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD;
					rGroupFlags = ITEM_GROUP_FLAG_SOLDIER;
				}
				else if (iRank > 15)
				{
					rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD;
					rGroupFlags = ITEM_GROUP_FLAG_SOLDIER + ITEM_GROUP_FLAG_MARGINAL;
				}
				else
				{
					rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY;
					rGroupFlags = ITEM_GROUP_FLAG_MARGINAL;
				}
			break;
		}
	}
	else
	{
		if (iRank > 25 || sType == ITEM_PACK_ELITE)
		{
			rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD + ITEM_QUALITY_FLAG_EXCELLENT;
			rGroupFlags = ITEM_GROUP_FLAG_SOLDIER + ITEM_GROUP_FLAG_OFFICER;
		}
		else if (iRank > 15)
		{
			rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD;
			rGroupFlags = ITEM_GROUP_FLAG_SOLDIER + ITEM_GROUP_FLAG_OFFICER;
		}
		else
		{
			rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY;
			rGroupFlags = ITEM_GROUP_FLAG_SOLDIER;
		}
	}
}



void GetItemFiltersItems(ref rChar, string sType, ref rQualityFlags)
{
	string sPhantomType;
	int iRank = sti(rChar.rank);

	if (sType == ITEM_PACK_ELITE)
	{
		rQualityFlags = ITEM_QUALITY_FLAG_GOOD + ITEM_QUALITY_FLAG_EXCELLENT;
	}
	else if (iRank > 25)
	{
		rQualityFlags = ITEM_QUALITY_FLAG_GOOD + ITEM_QUALITY_FLAG_EXCELLENT;
	}
	else if (iRank > 20)
	{
		rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD;
	}
	else if (iRank > 15)
	{
		rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD;
	}
	else if (iRank > 10)
	{
		rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY;
	}
	else if (iRank > 5)
	{
		rQualityFlags = ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_POOR;
	}
	else
	{
		rQualityFlags = ITEM_QUALITY_FLAG_POOR;
	}
}


void GetMushketFiltersItems(ref rChar, string sType, ref rQualityFlags)
{
	string sPhantomType;
	int iRank = sti(rChar.rank);

	if (sType == ITEM_PACK_ELITE)
	{
		rQualityFlags = ITEM_QUALITY_FLAG_GOOD + ITEM_QUALITY_FLAG_EXCELLENT;
	}
	else if (iRank > 25)
	{
		rQualityFlags = ITEM_QUALITY_FLAG_GOOD + ITEM_QUALITY_FLAG_EXCELLENT;
	}
	else if (iRank > 20)
	{
		rQualityFlags = ITEM_QUALITY_FLAG_GOOD + ITEM_QUALITY_FLAG_EXCELLENT;
	}
	else if (iRank > 15)
	{
		rQualityFlags = ITEM_QUALITY_FLAG_POOR + ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD;
	}
	else if (iRank > 10)
	{
		rQualityFlags = ITEM_QUALITY_FLAG_POOR + ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD;
	}
	else if (iRank > 5)
	{
		rQualityFlags = ITEM_QUALITY_FLAG_POOR + ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD;
	}
	else
	{
		rQualityFlags = ITEM_QUALITY_FLAG_POOR + ITEM_QUALITY_FLAG_ORDINARY + ITEM_QUALITY_FLAG_GOOD;
	}
}


void GetBulletQuality(ref rChar, string sType, ref rQuality)
{
	string sPhantomType;
	int iRank = sti(rChar.rank);

	if (sType == ITEM_PACK_ELITE)
	{
		rQuality = B_EXCELLENT;
	}
	else if (iRank > 20)
	{
		rQuality = B_EXCELLENT;
	}
	else if (iRank > 10)
	{
		rQuality = B_GOOD;
	}
	else
	{
		rQuality = B_POOR;
	}
}

void FindBlades(ref rArray, int iBladeTypeFlags, int iQualityFlags, int iGroupFlags)
{
	//trace("FindArmors: iBladeTypeFlags = "+iBladeTypeFlags+"; iQualityFlags = "+iQualityFlags+"; iGroupFlags = "+iGroupFlags);
	int iItemCount = GetArraySize(&Items);
	int n = 0;
	for (int i = 0; i<iItemCount; i++)
	{
		ref rItem = &Items[i];
		if (!CheckAttribute(rItem, "groupID") || rItem.groupID != BLADE_ITEM_TYPE || AttributeIsTrue(rItem, "Generated"))
		{
			continue;
		}

		int iTypeFlag = 0;


		int iWeaponType = GetWeaponType(rItem);
		if (iWeaponType < 0)
		{
			continue;
		}
		iTypeFlag = gItemBladeTypes[iWeaponType];

		if (!and(iTypeFlag, iBladeTypeFlags))
		{
			continue;
		}

		int iGroupFlag = gItemTargetGroups[GetAttributeInt(rItem, "target")];

		if (!and(iGroupFlag, iGroupFlags))
		{
			continue;
		}

		int iQualityFlag = gItemQualityGroups[GetAttributeInt(rItem, "quality")];
		if (!and(iQualityFlag, iQualityFlags))
		{
			continue;
		}
		//trace("blade rItem.id "+rItem.id+" accepted");
		n++;
		SetArraySize(rArray, n);
		rArray[n - 1] = i;
	}
	if (n == 0)
	{
		trace("blade not found: iBladeTypeFlags="+iBladeTypeFlags+"; iQualityFlags = "+iQualityFlags+"; iGroupFlags = "+iGroupFlags);
		SetArraySize(rArray, 1);
		rArray[0] = GetItemIndex("blade_05"); // Катлас если совсем ничего не нашлось
	}
}


void FindGuns(ref rArray, int iQualityFlags, int iItemType)
{
	int n = 0;
	//trace("FindGuns: iQualityFlags = "+iQualityFlags+"; iItemType = "+iItemType);
	int iItemCount = GetArraySize(&Items);
	for (int i = 0; i<iItemCount; i++)
	{
		ref rItem = &Items[i];
		if (!CheckAttribute(rItem, "groupID") || rItem.groupID != iItemType)
		{
			continue;
		}

		int iQualityFlag = gItemQualityGroups[GetAttributeInt(rItem, "quality")];
		if (!and(iQualityFlag, iQualityFlags))
		{
			continue;
		}
		//trace("gun rItem.id "+rItem.id+" accepted");

		n++;
		SetArraySize(rArray, n);
		rArray[n - 1] = i;
	}
	if (n == 0)
	{
		trace("gun not found: iQualityFlags = "+iQualityFlags+"; iItemType = "+iItemType);
		SetArraySize(rArray, 1);
		if (iItemType == MUSKET_ITEM_TYPE)
			rArray[0] = GetItemIndex("mushket1"); // Если совсем ничего не нашлось
		else
			rArray[0] = GetItemIndex("pistol1"); // Если совсем ничего не нашлось
	}
}

void FindArmors(ref rArray, int iQualityFlags, int iTypeFlags)
{
	//trace("FindArmors: iQualityFlags = "+iQualityFlags+"; iTypeFlags = "+iTypeFlags);
	int n = 0;
	int iItemCount = GetArraySize(&Items);
	for (int i = 0; i<iItemCount; i++)
	{
		ref rItem = &Items[i];
		if (!CheckAttribute(rItem, "groupID") || rItem.groupID != CIRASS_ITEM_TYPE)
		{
			continue;
		}

		int iTypeFlag = 0;

		int iArmorType = GetArmorType(rItem);
		if (iArmorType < 0)
		{
		    continue;
		}
		iTypeFlag = gItemArmorTypes[iArmorType];

		if (!and(iTypeFlag, iTypeFlags))
		{
			continue;
		}

		int iQualityFlag = gItemQualityGroups[GetAttributeInt(rItem, "quality")];
		if (!and(iQualityFlag, iQualityFlags))
		{
			continue;
		}
		//trace("armor rItem.id "+rItem.id+" accepted");
		n++;
		SetArraySize(rArray, n);
		rArray[n - 1] = i;
	}
	if (n == 0)
	{
		trace("armor not found: iQualityFlags = "+iQualityFlags+"; iTypeFlags = "+iTypeFlags);
		SetArraySize(rArray, 1);
		rArray[0] = -1; // Если совсем ничего не нашлось
	}
}

string GetBestBulletWithLimit(ref rGun, int iMaxQuality)
{
	aref rType;
	makearef(rType, rGun.type);
	int iNum = GetAttributesNum(rType);

	string sDefaultBullet;
	int iSelectedBulletIdx = -1;
	int iSelectedQuality = -1;
	for (int i = 0; i < iNum; i++)
	{
		aref arCur = GetAttributeN(rType, i);
		string sBulletType = arCur.bullet;
		if(AttributeIsTrue(arCur, "Default"))
		{
			sDefaultBullet = sBulletType;
		}
		int iBulletIdx = GetItemIndex(sBulletType);
		if(iBulletIdx == -1)
		{
			trace("Bad index for item : " + sBulletType);
			continue;
		}

		int iCurQuality = GetAttributeInt(&Items[iBulletIdx], "quality");
		if (iCurQuality > iMaxQuality)
		{
			continue;
		}

		if (iSelectedBulletIdx == -1 || iCurQuality > iSelectedQuality)
		{
			iSelectedQuality = iCurQuality;
			iSelectedBulletIdx = iBulletIdx;
		}
	}
	if (iSelectedBulletIdx == -1 && sDefaultBullet != "")
	{
		return sDefaultBullet;
	}
	else if (iSelectedBulletIdx == -1)
	{
		trace("unable to found default bullet for "+rGun.id);
		return "";
	}
	else
	{
		return Items[iSelectedBulletIdx].id;
	}
}

void GetAllBulletTypes(ref rGun, ref rBullets)
{
	aref rType;
	makearef(rType, rGun.type);
	int iNum = GetAttributesNum(rType);

	for (int i = 0; i < iNum; i++)
	{
		aref arCur = GetAttributeN(rType, i);
		string sBulletType = arCur.bullet;

		int iBulletIdx = GetItemIndex(sBulletType);
		if(iBulletIdx == -1)
		{
			trace("Bad index for item : " + sBulletType);
			continue;
		}

		SetArraySize(rBullets, i+1);
		rBullets[i] = iBulletIdx;
	}
}

string GetGunPowderTypeForBullet(ref rGun, ref rBullet)
{
	string sBulletID = rBullet.id;
	aref rType;
	makearef(rType, rGun.type);
	int iNum = GetAttributesNum(rType);

	for (int i = 0; i < iNum; i++)
	{
		aref arCur = GetAttributeN(rType, i);
		string sBulletType = arCur.bullet;
		if (sBulletType  == sBulletID)
		{
			return GetAttributeOrDefault(arCur, "gunpowder", "");
		}
	}

	trace("warning: bullet "+sBulletID+" not found for "+rGun.id);
	return "";
}

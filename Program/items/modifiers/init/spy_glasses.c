bool InitSpyGlassModifiers(ref item)
{
	if (item.groupID != SPYGLASS_ITEM_TYPE) return false;

	string realId = item.id;
	if (CheckAttribute(item, "DefItemID")) realId = item.DefItemID; // для ген-предметов принимаем id базовых

	AddDescriptor(item, "SpyGlass", -1);
	switch (realId)
	{
		case "spyglass1":
		{
			AddDescriptor(item, "SpyGlass_Crew", 0);
		}
		break;
		case "spyglass2":
		{
			AddDescriptor(item, "SpyGlass_Crew", 0);
		}
		break;
		case "spyglass3":
		{
			AddDescriptor(item, "SpyGlass_Caliber", 0);
			AddDescriptor(item, "SpyGlass_Crew", 1);
		}
		break;
		case "spyglassSP3":
		{
			AddDescriptor(item, "SpyGlass_Caliber", 0);
			AddDescriptor(item, "SpyGlass_Crew", 1);
			AddDescriptor(item, "Special", -1);
		}
		break;
		case "spyglass4":
		{
			AddDescriptor(item, "SpyGlass_Caliber", 1);
			AddDescriptor(item, "SpyGlass_Crew", 2);
		}
		break;
		case "spyglass5":
		{
			AddDescriptor(item, "SpyGlass_Caliber", 1);
			AddDescriptor(item, "SpyGlass_Crew", 2);
		}
		break;
	}

	return true;
}

bool InitAmmunitionModifiers(ref item)
{
	if (item.groupID != AMMO_ITEM_TYPE) return false;

	string realId = item.id;
	if (CheckAttribute(item, "DefItemID")) realId = item.DefItemID; // для ген-предметов принимаем id базовых

	switch (realId)
	{
		case "GunCap_colt":
		{
			AddDescriptor(item, "BulletAmmo", -1);
			AddSpecialDescriptor(item, "Unknown");
		}
		break;
		case "shotgun_cartridge":
		{
			AddDescriptor(item, "BulletAmmo", -1);
			AddSpecialDescriptor(item, "Unknown");
		}
		break;
		case "cartridge":
		{
			AddDescriptor(item, "BulletAmmo", -1);
			AddDescriptor(item, "EmpoweredAmmo", -1);
		}
		break;
		case "grapeshot_double":
		{
			AddDescriptor(item, "GrapeAmmo", -1);
			AddDescriptor(item, "EmpoweredAmmo", -1);
		}
		break;
		case "bullet_double":
		{
			AddDescriptor(item, "BulletAmmo", -1);
			AddDescriptor(item, "EmpoweredAmmo", -1);
		}
		break;
		case "GunEchin":
		{
			AddDescriptor(item, "GrapeAmmo", -1);
			AddDescriptor(item, "BulletNeedPowder", -1);
			AddDescriptor(item, "PiercingAmmo", -1);
		}
		break;
		case "harpoon":
		{
			AddDescriptor(item, "BulletAmmo", -1);
			AddDescriptor(item, "BulletNeedPowder", -1);
			AddDescriptor(item, "PiercingAmmo", -1);
		}
		break;
		case "powder_pellet":
		{
			AddDescriptor(item, "BombAmmo", -1);
			AddDescriptor(item, "BulletNeedPowder", -1);
			AddDescriptor(item, "StunAmmo", -1);
		}
		break;
		case "grenade":
		{
			AddDescriptor(item, "BombAmmo", -1);
			AddDescriptor(item, "BulletNeedPowder", -1);
		}
		break;
		case "bullet":
		{
			AddDescriptor(item, "BulletAmmo", -1);
			AddDescriptor(item, "BulletNeedPowder", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "grapeshot":
		{
			AddDescriptor(item, "GrapeAmmo", -1);
			AddDescriptor(item, "BulletNeedPowder", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
		case "shotgun_bullet":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
			AddDescriptor(item, "Valuable", -1);
		}
		break;
		case "gunpowder":
		{
			AddDescriptor(item, "Junk", -1);
			AddDescriptor(item, "Ingredient", -1);
		}
		break;
	}

	return true;
}

#include "items\modifiers\init\blades.c"
#include "items\modifiers\init\armor.c"
#include "items\modifiers\init\guns.c"
#include "items\modifiers\init\ammunition.c"
#include "items\modifiers\init\amulets.c"
#include "items\modifiers\init\spy_glasses.c"
#include "items\modifiers\init\hats.c"
#include "items\modifiers\init\potions.c"
#include "items\modifiers\init\all_rest.c"


void InitModifiers()
{
	ref item;
	for (int i = 0; i < TOTAL_ITEMS; i++)
	{
		item = &Items[i];
		if (!CheckAttribute(&item, "id")) continue;
		DeleteAttribute(item, "modifiers");
		DeleteAttribute(item, "descriptors");

		if (IsQuestUsedItem(item.id) && item.id != "gold") AddDescriptor(item, "Quest", -1);

		if (CheckAttribute(item, "groupID"))
		{
			if (InitAmuletModifiers(item)) continue;
			if (InitWeaponModifiers(item)) continue;
			if (InitGunsModifiers(item)) continue;
			if (InitArmorModifiers(item)) continue;
			if (InitAmmunitionModifiers(item)) continue;
			if (InitSpyGlassModifiers(item)) continue;
			if (InitHatModifiers(item)) continue;
		}

		InitRestModifiers(item);
		InitPotionModifiers(item);
	}
}

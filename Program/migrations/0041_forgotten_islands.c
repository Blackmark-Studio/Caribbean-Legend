
void ApplyMigration(ref migrationState)
{
	MigrateStealthFlags_0041();
	MigrateStealthLicense_0041();

	int n = GetArraySize(&Islands);
	SetArraySize(&Islands, n + 2);
	Islands[n].id = "MarieGalante";
	Islands[n].name = "MarieGalante";
	Islands[n].model = "IslaMona";
	Islands[n].filespath.models = "islands\IslaMona";
	Islands[n].refl_model = "IslaMona_refl";
	Islands[n].locators = "IslaMona_locators";
	Islands[n].visible = false;
	Islands[n].reload_enable = false;
	Islands[n].hidden = true;
	Islands[n].colonyquantity = 0;
	Islands[n].jungle.patch = "IslaMona_jungles";
	Islands[n].jungle.texture = "junglesprites";
	Islands[n].jungle.scale = 12.5;
	Islands[n].TexturePath = "IslaMona";

	Islands[n].InterfaceTextures.t1 = "battle_interface\moor_7.tga";
	Islands[n].InterfaceTextures.t1.h = 4;
	Islands[n].InterfaceTextures.t1.v = 1;

	//Виртуальный остров
	//SendMessage(&locator,"le",LM_LOCATE_I,&Islands[n]);

	/////////////////////////////////////////////////////////////////////////
	/// Tenotchitlan
	/////////////////////////////////////////////////////////////////////////

	n = n + 1;
	Islands[n].id = "Tobago";
	Islands[n].name = "Tobago";
	Islands[n].model = "IslaMona";
	Islands[n].filespath.models = "islands\IslaMona";
	Islands[n].refl_model = "IslaMona_refl";
	Islands[n].locators = "IslaMona_locators";
	Islands[n].visible = false;
	Islands[n].reload_enable = false;
	Islands[n].hidden = true;
	Islands[n].colonyquantity = 0;
	Islands[n].jungle.patch = "IslaMona_jungles";
	Islands[n].jungle.texture = "junglesprites";
	Islands[n].jungle.scale = 12.5;
	Islands[n].TexturePath = "IslaMona";

	Islands[n].InterfaceTextures.t1 = "battle_interface\moor_7.tga";
	Islands[n].InterfaceTextures.t1.h = 4;
	Islands[n].InterfaceTextures.t1.v = 1;
}

// Меняем перки флагов на флаги
void MigrateStealthFlags_0041()
{
	int maxClass = 6;

	// ищем старший используемый класс
	for (int j = 0; j < COMPANION_MAX; j++)
	{
		int companionIdx = GetCompanionIndex(pchar, j);
		if (companionIdx < 0) continue;
		ref companion = GetCharacter(companionIdx);
		int companionClass = GetCharacterShipClass(companion);
		if (companionClass < maxClass ) maxClass = companionClass;
	}

	for (int i = 0; i < MAX_NATIONS; i++)
	{
		if (i == GetBaseHeroNation()) continue;
		if (i == PIRATE) continue;
		string perkName = "flag" + NationShortName(i);
		if (!HasPerk(pchar, perkName)) continue;

		DelCharacterPerk(pchar, perkName);

		for (int x = maxClass; x <= 6; x++)
		{
			_STH_AddFlagToUse(i, x)
		}
	}
}

// Меняем предмет лицензии на новую схему
void MigrateStealthLicense_0041()
{
	int licenseQty = GetCharacterFreeItem(pchar, "HolTradeLicence");
	ref rItem = ItemsFromID("HolTradeLicence");

	int Validity = GetAttributeInt(rItem, "Validity.QtyDays");
	if (Validity > 0) LICENSE_AddDays(Validity);
	TakeItemFromCharacter(pchar, "HolTradeLicence");
	DeleteAttribute(rItem, "Action_date");
	DeleteAttribute(rItem, "Validity");
}
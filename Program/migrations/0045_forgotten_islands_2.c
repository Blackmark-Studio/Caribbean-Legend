
void ApplyMigration(ref migrationState)
{

	int n = GetArraySize(&Islands);
	SetArraySize(&Islands, n + 1);
	Islands[n].id = "Pearl";
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

}

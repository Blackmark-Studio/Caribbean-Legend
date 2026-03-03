
void ApplyMigration(ref migrationState)
{
	Colonies[FindColony("Bridgetown")].lighthouse = "Mayak2";
	Colonies[FindColony("Santiago")].lighthouse = "Mayak9";
	Colonies[FindColony("PortRoyal")].lighthouse = "Mayak3";
	Colonies[FindColony("BasTer")].lighthouse = "Mayak4";
	Colonies[FindColony("SantoDomingo")].lighthouse = "Mayak8";
	Colonies[FindColony("PortPax")].lighthouse = "Mayak7";
	Colonies[FindColony("Havana")].lighthouse = "Mayak10";
	Colonies[FindColony("Charles")].lighthouse = "Mayak5";
	Colonies[FindColony("PortSpein")].lighthouse = "Mayak1";
	Colonies[FindColony("Tortuga")].lighthouse = "Mayak6";
	Colonies[FindColony("Cartahena")].lighthouse = "Mayak11";

	int n = FindIsland("Barbados");
	Islands[n].name = "Barbados";
	Islands[n].main_colony = "Bridgetown";

	n = FindIsland("Jamaica");
	Islands[n].name = "Jamaica";
	Islands[n].main_colony = "PortRoyal";

	n = FindIsland("PuertoRico");
	Islands[n].name = "PuertoRico";
	Islands[n].main_colony = "SanJuan";

	n = FindIsland("Cuba1");
	Islands[n].name = "Cuba";
	Islands[n].main_colony = "Santiago";

	n = FindIsland("Cuba2");
	Islands[n].name = "Cuba";
	Islands[n].main_colony = "Havana";

	n = FindIsland("Curacao");
	Islands[n].name = "Curacao";
	Islands[n].main_colony = "Villemstad";

	n = FindIsland("Tortuga");
	Islands[n].name = "Tortuga";
	Islands[n].main_colony = "Tortuga";

	n = FindIsland("SentMartin");
	Islands[n].name = "SentMartin";
	Islands[n].main_colony = "Marigo";

	n = FindIsland("Trinidad");
	Islands[n].name = "Trinidad";
	Islands[n].main_colony = "PortSpein";

	n = FindIsland("Nevis");
	Islands[n].name = "Nevis";
	Islands[n].main_colony = "Charles";

	n = FindIsland("Antigua");
	Islands[n].name = "Antigua";
	Islands[n].main_colony = "SentJons";

	n = FindIsland("Guadeloupe");
	Islands[n].name = "Guadeloupe";
	Islands[n].main_colony = "BasTer";

	n = FindIsland("Martinique");
	Islands[n].name = "Martinique";
	Islands[n].main_colony = "FortFrance";

	n = FindIsland("Hispaniola1");
	Islands[n].name = "Hispaniola";
	Islands[n].main_colony = "SantoDomingo";

	n = FindIsland("Hispaniola2");
	Islands[n].name = "Hispaniola";
	Islands[n].main_colony = "PortPax";

	n = FindIsland("Bermudes");
	Islands[n].name = "Bermudes";
	Islands[n].main_colony = "Pirates";

	n = FindIsland("Dominica");
	Islands[n].name = "Dominica";

	n = FindIsland("Terks");
	Islands[n].name = "Terks";

	n = FindIsland("Caiman");
	Islands[n].name = "Caiman";

	n = FindIsland("PortoBello");
	Islands[n].name = "Mein";
	Islands[n].main_colony = "PortoBello";

	n = FindIsland("Cartahena");
	Islands[n].name = "Mein";
	Islands[n].main_colony = "Cartahena";

	n = FindIsland("Maracaibo");
	Islands[n].name = "Mein";
	Islands[n].main_colony = "Maracaibo";

	n = FindIsland("Caracas");
	Islands[n].name = "Mein";
	Islands[n].main_colony = "Caracas";

	n = FindIsland("Cumana");
	Islands[n].name = "Mein";
	Islands[n].main_colony = "Cumana";

	n = FindIsland("SantaCatalina");
	Islands[n].name = "Mein";
	Islands[n].main_colony = "SantaCatalina";

	n = FindIsland("Beliz");
	Islands[n].name = "Mein";
	Islands[n].main_colony = "Beliz";

	n = FindIsland("LostShipsCity");
	Islands[n].name = "LostShipsCity";
	Islands[n].main_colony = "LostShipsCity";

	n = FindIsland("KhaelRoa");
	Islands[n].name = "KhaelRoa";

	n = FindIsland("Ksochitam");
	Islands[n].name = "Ksochitam";

	n = FindIsland("RockIsland");
	Islands[n].name = "RockIsland";

	n = FindIsland("Providence");
	Islands[n].name = "Providence";
	Islands[n].main_colony = "SanAndres";

	n = FindIsland("SantaQuiteria");
	Islands[n].name = "SantaQuiteria";

	n = FindIsland("IslaDeVieques");
	Islands[n].name = "IslaDeVieques";

	n = FindIsland("IslaMona");
	Islands[n].name = "IslaMona";

	n = FindIsland("IslaDeCoche");
	Islands[n].name = "IslaDeCoche";


	n = GetArraySize(&Islands);
	SetArraySize(&Islands, n + 2);
	Islands[n].id = "Panama";
	Islands[n].name = "Main";
	Islands[n].main_colony = "Panama";
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
	Islands[n].id = "Tenotchitlan";
	Islands[n].name = "Main";
	Islands[n].main_colony = "Tenotchitlan";
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
	
	aref arLab;
    makearef(arLab, worldMap.labels);
	DeleteAttribute(arLab, "Shore64");
	DeleteAttribute(arLab, "Shore65");
	DeleteAttribute(arLab, "Shore67");
	DeleteAttribute(arLab, "Shore68");
	DeleteAttribute(arLab, "Shore72");
	DeleteAttribute(arLab, "Shore73");
	DeleteAttribute(arLab, "Shore75");
	DeleteAttribute(arLab, "Shore78");
}

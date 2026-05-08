// Переходим на палубу
void _Birthday_TeleportToDeck(ref storyObject)
{
	MakeCloneShipDeck(pchar, true); // подмена палубы
	int i = FindLocation("Ship_deck");
	Locations[i].image = "loading\Quarter_1.tga";
	aref wormhole = GetAref(&TEV, "wormhole", true);
	SetFunctionLocationCondition("_Birthday_SetUpDeck", "Ship_deck", false);
	DoReloadFromWorldMapToLocation("Ship_deck", "reload", "reload1");
}


void ApplyMigration(ref migrationState)
{
	for (int n=0;n<MAX_ISLANDS;n++)
	{
		ref island = GetIslandByIndex(n);
		if (island.id == "LostShipsCity") island.type = ISLAND_QUEST;
		else if (island.id == "KhaelRoa") island.type = ISLAND_QUEST;
		else if (island.id == "Ksochitam") island.type = ISLAND_QUEST;
		else if (island.id == "RockIsland") island.type = ISLAND_QUEST;
		else if (island.id == "Providence") island.type = ISLAND_QUEST;
		else if (island.id == "SantaQuiteria") island.type = ISLAND_QUEST;
		else if (island.id == "IslaDeVieques") island.type = ISLAND_QUEST;
		else if (island.id == "IslaMona") island.type = ISLAND_QUEST;
		else if (island.id == "IslaDeCoche") island.type = ISLAND_QUEST;
		else if (island.id == "Panama") island.type = ISLAND_VIRTUAL;
		else if (island.id == "Tenotchitlan") island.type = ISLAND_VIRTUAL;
		else if (island.id == "MarieGalante") island.type = ISLAND_VIRTUAL;
		else if (island.id == "Tobago") island.type = ISLAND_VIRTUAL;
		else if (island.id == "Pearl") island.type = ISLAND_VIRTUAL;
		else if (island.id == "LosTeques") island.type = ISLAND_VIRTUAL;
		else if (island.id != "") island.type = ISLAND_COMMON;
	}
}

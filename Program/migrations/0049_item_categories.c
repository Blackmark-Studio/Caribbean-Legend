
void ApplyMigration(ref migrationState)
{
	ref rItem;
	rItem = ItemsFromID("cirass1");
	rItem.Quality = B_POOR; // траншейный доспех
	rItem = ItemsFromID("cirass2");
	rItem.Quality = B_ORDINARY; // рейтарская кираса
	rItem = ItemsFromID("cirass3");
	rItem.Quality = B_GOOD; // парадная кираса
	rItem = ItemsFromID("cirass4");
	rItem.Quality = B_EXCELLENT; // миланский панцирь
	rItem = ItemsFromID("underwater");
	rItem.Quality = B_UNIQUE; // водолазное снаряжение
	rItem = ItemsFromID("cirass10");
	rItem.Quality = B_UNIQUE; // Броня железнобоких
	rItem = ItemsFromID("cirass11");
	rItem.Quality = B_UNIQUE; // Зерцальный нагрудник

	rItem = ItemsFromID("suit1");
	rItem.Quality = B_UNIQUE; // французский офицерский мундир
	rItem = ItemsFromID("suit5");
	rItem.Quality = B_UNIQUE; // французский адмиральский мундир
	rItem = ItemsFromID("suit2");
	rItem.Quality = B_UNIQUE; // английский офицерский мундир
	rItem = ItemsFromID("suit3");
	rItem.Quality = B_UNIQUE; // испанский офицерский мундир
	rItem = ItemsFromID("suit4");
	rItem.Quality = B_UNIQUE; // костюм Лампорта

	rItem = ItemsFromID("cirass5");
	rItem.Quality = B_POOR; // кожаный корсет
	rItem = ItemsFromID("cirass6");
	rItem.Quality = B_ORDINARY; // жилет бретера
	rItem = ItemsFromID("cirass7");
	rItem.Quality = B_GOOD; // бригант
	rItem = ItemsFromID("cirass8");
	rItem.Quality = B_UNIQUE; // плетёный доспех
	rItem = ItemsFromID("cirass9");
	rItem.Quality = B_UNIQUE; // бригант с горжетом

	rItem = ItemsFromID("bullet");
	rItem.Quality = B_POOR;
	rItem = ItemsFromID("shotgun_bullet");
	rItem.Quality = B_UNIQUE;
	rItem = ItemsFromID("grapeshot");
	rItem.Quality = B_POOR;
	rItem = ItemsFromID("cartridge");
	rItem.Quality = B_EXCELLENT;
	rItem = ItemsFromID("grapeshot_double");
	rItem.Quality = B_UNIQUE;
	rItem = ItemsFromID("bullet_double");
	rItem.Quality = B_UNIQUE;
	rItem = ItemsFromID("powder_pellet");
	rItem.Quality = B_GOOD;
	rItem = ItemsFromID("grenade");
	rItem.Quality = B_EXCELLENT;
	rItem = ItemsFromID("harpoon");
	rItem.Quality = B_GOOD;
	rItem = ItemsFromID("GunCap_colt");
	rItem.Quality = B_UNIQUE;
	rItem = ItemsFromID("shotgun_cartridge");
	rItem.Quality = B_UNIQUE;
	rItem = ItemsFromID("GunEchin");
	rItem.Quality = B_EXCELLENT;

}

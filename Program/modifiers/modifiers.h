#define M_ARMOR_TYPE "ArmorType"
#define M_ARMOR_MATERIAL "ArmorMaterial"

#define M_WEAPON_LENGTH "WeaponLength"
#define M_WEAPON_CURVATURE "WeaponCurvature"
#define M_WEAPON_TYPE "WeaponType"

#define M_CANT_BE_POISONED "CantBePoisoned"

#define M_CROSSHAIR_UPDATE_SPEED "CrosshairUpdateSpeed"
#define M_SQUADRON_POWER "SquadronPower"
#define M_REDUCE_DAMAGE "IncomingDamageReduction"
#define M_REDUCE_CRIT_DAMAGE "CritIncomingDamageReduction"

#define M_RELOAD_SPEED "ReloadSpeed"       // увеличение скорости перезарядки, используется с типом оружия
#define M_DAMAGE "Damage"                  // урон, используется с типами ударов и оружия
#define M_CRIT_CHANCE "CritChance"         // критшанс, используется с типом оружия
#define M_CRIT_DAMAGE "CritDamage"         // модификатор урона крита, float типа 0.2 это 20%, используется с типом оружия
#define M_HEADSHOT_DAMAGE "HeadshotDamage" // модификатор урона хедшота, float типа 0.2 это 20%
#define M_ACTION_SPEED "ActionSpeed"
#define M_MOVE_SPEED "MoveSpeed"
#define M_POISON_CHANCE "PoisonChance"     // шанс отравить с атакой
#define M_STAGGER_SPEED "StaggerSpeed"
#define M_STRIKE_ANGLE "StrikeAngle"

#define M_HP_MAX "hpMax"                    // флет макс хп
#define M_MTP_HP_MAX "mtpHpMax"             // процент макс хп
#define M_HP_PER_RANK "hpPerRank"           // +хп за уровень
#define M_ENERGY_MAX "energyMax"            // флет макс энергия
#define M_MTP_ENERGY_MAX "mtpEnergyMax"     // процент макс энергия
#define M_ENERGY_PER_RANK "energyPerRank"   // +энергия за уровень
#define M_ENERGY_REGEN_MTP "energyRegenMtp" // ускорение восстановления энергии
#define M_HP_REGEN_MTP "hpRegenMtp"         // ускорение восстановления хп

#define MELEE "Melee"
#define RANGE "Range"
#define BULLET "bullet"
#define GRAPESHOT "grapeshot"

#define WEAPON_LIGHT 0
#define WEAPON_MEDIUM 1
#define WEAPON_HEAVY 2

#define ARMOR_LIGHT 0
#define ARMOR_MEDIUM 1
#define ARMOR_HEAVY 2

#define ARMOR_FABRIC 0
#define ARMOR_LEATHER 1
#define ARMOR_PLATES 2
#define ARMOR_STAMPS 3
#define ARMOR_MOLDED 4

#define WEAPON_STRAIGHT 0
#define WEAPON_CURVE 1

#define WEAPON_SHORT 0
#define WEAPON_LONG 1

#define M_AMULET_TYPE "AmuletType"
#define AMULET_COMMON 0
#define AMULET_PAGAN  1
#define AMULET_CHURCH 2

#define SET "has."   // для консистентности нейминга
#define HAS "has."   // модификатор установки состояния, такие модификаторы складываются в атрибут has и тупо копируются

// Корабельные

#define M_SHIP_HP "shipHP"
#define M_SHIP_CAPACITY "shipCapacity"
#define M_SHIP_SPEED "shipSpeed"
#define M_SHIP_TURNRATE "shipTurnrate"
#define M_SHIP_MAXCREW "shipMaxcrew"
#define M_SHIP_MINCREW "shipMincrew"
#define M_SHIP_FIRE_DISTANCE "shipFireDistance"
#define M_SHIP_RELOAD_SPEED "shipReloadSpeed"

// Глобальная карта
#define M_GLOBAL_SPEED "GlobalSpeed"

// Не процессируемые на персонаже эффекты, используемые в сезонах
#define M_MEDICAMENT_CONSUMPTION "drugConsumption"              // Потребление медикаментов
#define M_FOOD_CONSUMPTION "foodConsumption"                    // Потребление провианта
#define M_RECRUITS_MTP "recruitsMtp"                            // Глобальный бонус к рекрутам в тавернах
#define M_CARIBBEAN_GOODS_COST "caribbeanGoodsCost"             // Стоимость местных товаров
#define M_CARIBBEAN_GOODS_STOCK "caribbeanGoodsStock"           // Запасы местных товаров
#define M_EUROPEAN_GOODS_COST "europeanGoodsCost"               // Стоимость европейских товаров
#define M_EUROPEAN_GOODS_STOCK "europeanGoodsStock"             // Запасы европейских товаров
#define M_CONVENIENCE_GOODS_COST "convenienceGoodsCost"         // Стоимость товаров повседневного спроса
#define M_CONVENIENCE_GOODS_STOCK "convenienceGoodsStock"       // Запасы товаров повседневного спроса
#define M_UNIQUE_GOODS_AVAILABLE "uniqueGoodsAvailable"         // Доступность стратегических товаров в магазинах
#define M_UNIQUE_GOODS_STOCK "uniqueGoodsStock"                 // Запасы стратегических товаров
#define M_GOLDSILVER_GOODS_AVAILABLE "goldsilverGoodsAvailable" // Доступность золота и серебра в магазинах
#define M_LEGAL_CONTRABAND "legalContraband"                    // Контрабанда работает как обычно или становится импортом
#define M_SLAVES_GOODS_AVAILABLE "slavesGoodsAvailable"         // Доступность рабов в магазинах
#define M_MEDICAMENT_COST "medicamentCost"                      // Стоимость медикаментов
#define M_DEBIT_RATE "debitRate"                                // Ставка кредитов
#define M_DEPOSIT_SILVER_RATE "depositSilverRate"               // Ставка вкладов в песо
#define M_DEPOSIT_GOLD_RATE "depositGoldRate"                   // Ставка вкладов в дублонах
#define M_REPAIR_COST "repairCost"                              // Цена ремонта на верфи
#define M_SHIPYARD_CANNONS_STOCK "shipyardCannonsStock"         // Запасы пушек на верфи
#define M_BIG_CANNONS_AVAILABLE "bigCannonsAvailable"           // Доступность крупных калибров на верфи
#define M_STOLEN_GOODS_MTP "stolenGoodsMtp"                     // Уменьшение штрафа краденых товаров
#define M_CONTRABAND_TRADE_STATUS "contrabandTradeStatus"       // Торговля с контрабандистами возможна или нет
#define M_IMPORT_PRICE_MTP "importPriceMtp"                     // Цена импортных товаров
#define M_EXPORT_PRICE_MTP "exportPriceMtp"                     // Цена экспортных товаров
#define M_SEA_REPAIR_EFFICENCY "seaRepairEfficency"             // Эффективность ремонта в море
#define M_ENEMY_HULL_DAMAGE_MTP "enemyHullDamageMtp"            // Множитель урона по корпусу вражеских кораблей
#define M_NATIONS_REPUTATION_MTP "nationsReputationMtp"         // Скорость изменения репутации у наций
#define M_CREW_MORALE_MTP "moraleMtp"                           // Скорость изменения морали
#define M_CREW_HIRING_EXP_MTP "crewHiringExpMtp"                // Множитель опыта новых матросов
#define M_CREW_EXP_MTP "crewExpMtp"                             // Множитель опыта новых матросов
#define M_CREW_HIRE_MORALE_MTP "crewHireMoraleMtp"              // Множитель морали новых матросов
#define M_CREW_HIRE_COST "crewHireCost"                         // Стоимость найма матросов
#define M_CREW_MAINTENANCE_COST "crewMaintenanceCost"           // Стоимость содержания матросов
#define M_MIN_FORT_CANNONS_MTP "minFortCannonsMtp"              // Множитель порога пушек для разгрома форта
#define M_STEALTH_INCEPTION_BONUS "stealthInceptionBonus"       // Бонус к сторям скрытности
#define M_TRADE_LICENSE_COST "tradeLicenseCost"                 // Стоимость торговой лицензии
#define M_WORLD_SHIPS_CREW_MTP "worldShipsCrewMtp"              // Множитель заполненности команд у фантомов
#define M_WORLD_SHIPS_HULL_MTP "worldShipsHullMtp"              // Множитель целостности корпуса у фантомов
#define M_STORM_DAMAGE_MTP "stormDamageMtp"                     // Множитель урона штормов
#define M_AMMO_GOODS_COST "ammoGoodsCost"                       // Запасы аммуниции в магазинах
#define M_AMMO_GOODS_STOCK "ammoGoodsStock"                     // Стоимость аммуниции в магазинах
#define M_SHIP_SPEED_DYNAMIC "shipSpeedDynamic"                 // Множитель динамики набора скорости
#define M_CREW_MORALE_DEBUFF_MTP "crewMoraleDebuffMtp"          // Множитель мощности дебаффа на мораль от перегруза, голода и болезней
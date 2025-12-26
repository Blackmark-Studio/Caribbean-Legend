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

#define M_HP_MAX "hpMax"                   // флет макс хп
#define M_MTP_HP_MAX "mtpHpMax"            // процент макс хп
#define M_HP_PER_RANK "hpPerRank"          // +хп за уровень
#define M_ENERGY_MAX "energyMax"           // флет макс энергия
#define M_MTP_ENERGY_MAX "mtpEnergyMax"    // процент макс энергия
#define M_ENERGY_PER_RANK "energyPerRank"  // +энергия за уровень

#define MELEE "Melee"
#define RANGE "Range"

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
#define M_SHIP_WINDAGAINST "shipWindagainst"
#define M_SHIP_MAXCREW "shipMaxcrew"
#define M_SHIP_MINCREW "shipMincrew"
#define M_SHIP_FIRE_DISTANCE "shipFireDistance"
#define M_SHIP_RELOAD_SPEED "shipReloadSpeed"
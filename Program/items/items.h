#define GOLD					"gold"
#define GOLD_ITEM               "jewelry5"

//TEMP
#define BLADE_SABER				"blade_11"
#define BLADE_SHORT				"blade_05"// boal 27.03.2004
#define BLADE_NORMAL			"blade_12"// boal 27.03.2004
#define BLADE_LONG				"blade_07"// boal 27.03.2004

#define GUN_COMMON				"pistol1"
#define CHEAP_SPYGLASS			"spyglass1"
#define COMMON_SPYGLASS			"spyglass2"
#define GOOD_SPYGLASS			"spyglass3"
#define SUPERIOR_SPYGLASS		"spyglass4"
#define POTION					"potion1"
#define INVALID_SUIT			"NoSuit" // Warship 25.10.08

// items group id
#define GUN_ITEM_TYPE			"gun"		
#define BLADE_ITEM_TYPE			"blade"		
#define SPYGLASS_ITEM_TYPE		"spyglass"	
#define PATENT_ITEM_TYPE        "patent"	
#define CIRASS_ITEM_TYPE		"cirass"	
#define MAPS_ITEM_TYPE		    "maps"		
#define TOOL_ITEM_TYPE			"tool"		
#define TALISMAN_ITEM_TYPE 		"talisman"	
#define ITEM_SLOT_TYPE			"slot"		
#define SPECIAL_ITEM_TYPE		"special" 	// Jason, спецпредметы, не отн. к прочим группам
#define AMMO_ITEM_TYPE			"ammo" 		// Боеприпас
#define LANTERN_ITEM_TYPE		"lantern" 	// фонарь
#define HAT_ITEM_TYPE			"hat" 		// шляпы
#define MUSKET_ITEM_TYPE		"musket"	// evganat - мушкеты

#define ITEM_SLOT1_TYPE			"slot1"		
#define ITEM_SLOT2_TYPE			"slot2"		
#define ITEM_SLOT3_TYPE			"slot3"	

#define ITEM_INDIAN				1
#define ITEM_AMULET				2
#define ITEM_OBEREG				3	
#define ITEM_TOTEM				4

#define SLOT_NOT_USED			""

#define ITEM_TRADE_NORMAL		0
#define ITEM_TRADE_JEWELRY		1
#define	ITEM_TRADE_POTION		2
#define ITEM_TRADE_AMMUNITION	3
#define ITEM_TRADE_ARTEFACT		4
#define ITEM_TRADE_MAP			5

// indexes for items` array
//#define TOTAL_ITEMS				  1008 // Warship 08.05.09 - Новая система предметов
int TOTAL_ITEMS = 1134;   //
int ITEMS_QUANTITY = 606; // не забываем менять номер
#define MAX_BUTTONS               64
#define RANDITEMS_QUANTITY    	  45
#define BUTTON_ACTIVATION_TIME	  1000
#define ITEMS_LAYER				  65549
#define MAX_LOADED_RANDITEMS      10
#define MAX_HANDLED_BOXES 		  25
#define ITEM_PROBABILITY		  0.5
#define OBJECTS_IN_BOX			  9
#define MAPS_IN_ATLAS			  23 // ugeen 21.06.09  -не забываем увеличивать при появлении новых карт
#define TREASURE_NOTES			  32

// blade defines - некоторые константы для клинков
// типы холодного оружия
#define FencingL			      0 // рапиры и шпаги - лёгкое оружие
#define FencingS			      1 // сабли - среднее оружие
#define FencingH    			  2 // палаши и тесаки - тяжелое оружие

// качественные группы
#define B_POOR                	  0 // плохое
#define B_ORDINARY                1 // обычное
#define B_GOOD                    2 // хорошее
#define B_EXCELLENT               3 // отличное
#define B_UNIQUE				  4 // уникальное

// целевые группы
#define TGT_QUEST                 0 // квестовое оружие
#define TGT_YANKEE                1 // рабы, бунтовщики, каторжники
#define TGT_NATIVE                2 // мезоамерика
#define TGT_MARGINAL              3 // маргиналы - низкуровневые пираты, граждане, бандиты
#define TGT_SOLDIER               4 // солдаты, пираты
#define TGT_OFFICER               5 // офицерское оружие, капитаны
#define TGT_PERSIAN               6 // индо-персидские клинки    

#define FencingL_MaxAttack        60.0    // максимальная атака для легих клинков
#define FencingS_MaxAttack        80.0    // максимальная атака для средних клинков
#define FencingH_MaxAttack        100.0   // максимальная атака для тяжёлых клинков

// Модификаторы урона типов оружия по типам ударов, 1 процент = 0,01
#define WEAPON_LIGHT_FAST_STRIKE_MTP  0.65
#define WEAPON_LIGHT_FORCE_STRIKE_MTP 1.1
#define WEAPON_LIGHT_ROUND_STRIKE_MTP 0.75
#define WEAPON_LIGHT_BREAK_STRIKE_MTP 0.8
#define WEAPON_MEDIUM_FAST_STRIKE_MTP  1.1
#define WEAPON_MEDIUM_FORCE_STRIKE_MTP 0.75
#define WEAPON_MEDIUM_ROUND_STRIKE_MTP 0.9
#define WEAPON_MEDIUM_BREAK_STRIKE_MTP 0.85
#define WEAPON_HEAVY_FAST_STRIKE_MTP  0.9
#define WEAPON_HEAVY_FORCE_STRIKE_MTP 0.65
#define WEAPON_HEAVY_ROUND_STRIKE_MTP 0.8
#define WEAPON_HEAVY_BREAK_STRIKE_MTP 1.1
#define MUSKET_FAST_STRIKE_MTP  0.65
#define MUSKET_FORCE_STRIKE_MTP 0.9
#define MUSKET_ROUND_STRIKE_MTP 0.6
#define MUSKET_BREAK_STRIKE_MTP 1.2

// Влияение веса по типам оружия
#define WEAPON_LIGHT_WEIGHT_MTP_1 0.5
#define WEAPON_LIGHT_WEIGHT_MTP_2 0.25
#define WEAPON_MEDIUM_WEIGHT_MTP_1 0.25
#define WEAPON_MEDIUM_WEIGHT_MTP_2 0.25
#define WEAPON_HEAVY_WEIGHT_MTP_1 0.25
#define WEAPON_HEAVY_WEIGHT_MTP_2 0.2

// Снижение урона от брони, 1 процент = 0.01
#define ARMOR_FABRIC_DAMAGE_REDUCTION  0.05
#define ARMOR_LEATHER_DAMAGE_REDUCTION 0.08
#define ARMOR_PLATES_DAMAGE_REDUCTION  0.16
#define ARMOR_STAMPS_DAMAGE_REDUCTION  0.24
#define ARMOR_MOLDED_DAMAGE_REDUCTION  0.40

// Влияние типов оружия на атак-спид
#define WEAPON_MEDIUM_ATTACK_SPEED_MTP -0.05
#define WEAPON_HEAVY_ATTACK_SPEED_MTP  -0.10

// Влияние типов брони на мув-спид
#define ARMOR_MEDIUM_MOVE_SPEED_MTP -0.06
#define ARMOR_HEAVY_MOVE_SPEED_MTP  -0.12


object Items[1134];
object RandItems[RANDITEMS_QUANTITY];
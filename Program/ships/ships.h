#define SAILS_COLOR_QUANTITY				9
#define SHIP_TYPES_QUANTITY					57
#define SHIP_TYPES_QUANTITY_WITH_FORT		58	// must be (SHIP_TYPES_QUANTITY + 1) 

// "Universal"
#define SHIP_TARTANE			0   // баркас			- 7-ой класс 	(SEFH)
#define SHIP_WAR_TARTANE		1	// тартана			- 7-ой класс	(SEFHP)
#define SHIP_LUGGER				2	// люггер			- 6-ой класс	(SEFHP)
#define SHIP_SCHOONER			3	// торговая шхуна	- 5-ый класс	(SEFH)
#define SHIP_BRIGANTINE			4	// бригантина		- 4-ый класс	(SP)
#define SHIP_POLACRE			5	// полакр			- 3-ий класс	(SF)
#define SHIP_EASTINDIAMAN		6	// ост-индец		- 2-ой класс	(SEFH)

// "Merchant"
#define SHIP_BARKENTINE			7	// баркентина		- 6-ой класс	(SEFH)
#define SHIP_BARQUE				8	// барк			    - 5-ый класс	(SEFH)
#define SHIP_FLEUT				9	// флейт			- 4-ый класс	(SEFH)
#define SHIP_PINNACE			10	// пинасс			- 3-ий класс	(SEFH)
#define SHIP_NAVIO				11	// навио			- 2-ой класс	(SEFH)

// "Raider"
#define SHIP_CAREERLUGGER       12	// курьерский люггер	- 6-ой класс	(SEFH)
#define SHIP_SCHOONER_W			13	// военная шхуна	    - 5-ый класс	(FHP)
#define SHIP_XebekVML			14	// шебека			    - 4-ый класс	(SH)
#define SHIP_BRIG				15	// бриг			        - 4-ый класс	(EP)
#define SHIP_CORVETTE			16	// корвет			    - 3-ий класс	(EFP)
#define SHIP_FRIGATE			17	// фрегат			    - 2-ой класс	(EFH)

// "War"
#define SHIP_SLOOP				18	// шлюп			    - 6-ой класс	(SEFHP)
#define SHIP_SHNYAVA			19	// шнява			- 5-ый класс	(SEFH)
#define SHIP_CARAVEL			20	// каравелла		- 4-ый класс	(SEFH)
#define SHIP_GALEON_L			21	// галеон			- 3-ий класс	(SEFHP)
#define SHIP_GALEON_H			22	// тяжёлый галеон	- 2-ой класс	(SP)
#define SHIP_FRIGATE_H			23	// тяжёлый фрегат	- 2-ой класс	(SEFH)
#define SHIP_LINESHIP			24	// военный корабль	- 1-ый класс	(SEFHP)
#define SHIP_LSHIP_FRA			25	// линейный корабль	- 1-ый класс (Франция)  (F)
#define SHIP_LSHIP_HOL			26	// линейный корабль	- 1-ый класс (Голландия)(H)
#define SHIP_LSHIP_SPA			27	// линейный корабль	- 1-ый класс (Испания)	(S)
#define SHIP_LSHIP_ENG			28	// линейный корабль	- 1-ый класс (Англия)	(E)

// квестовые
#define SHIP_MAYFANG			29 	// Мэйфэнг 			- легкая шебека			- 4-ый класс
#define SHIP_MIRAGE				30	// Мираж			- приватирский кеч	 	- 4-ый класс
#define SHIP_VALCIRIA			31	// Валькирия		- патрульный бриг	 	- 4-ый класс

#define SHIP_CORVETTE_QUEST		32	// Гриффондор		- малый фрегат			- 3-ий класс
#define SHIP_POLACRE_QUEST		33	// Тореро			- полакр		    	- 3-ий класс
#define SHIP_FRIGATE_L			34	// Фрегат "Акула"	- быстрый фрегат		- 2-ой класс
#define SHIP_HIMERA			    35  // Химера (Мираж 2) - военный кеч	 	    - 4-ый класс
#define SHIP_PINK				36  // Пинк - 5-ый класс
#define SHIP_GALEON_SM          37  // Галеон Святое Милосердие военный галеон  - 3-ий класс
#define SHIP_LADYBETH           38  // Военная шнява "Леди Бет"                 - 5-ый класс
#define SHIP_MEMENTO            39  // Военный бриг "Мементо"  					- 4-ый класс

// --> квестовые - заглушки !!!!
#define SHIP_QUEST0				40  // квестовый №0 - 6-ый класс
#define SHIP_QUEST1				41  // квестовый №1 - 5-ый класс
#define SHIP_QUEST2             42  // квестовый №2 - 4-ый класс
#define SHIP_QUEST3             43  // квестовый №3 - 4-ый класс
#define SHIP_QUEST4             44  // квестовый №4 - 3-ый класс
#define SHIP_QUEST5				45  // квестовый №5 - 3-ый класс
#define SHIP_QUEST6				46  // квестовый №6 - 2-ый класс
#define SHIP_QUEST7				47  // квестовый №7 - 2-ый класс
#define SHIP_QUEST8				48  // квестовый №8 - 1-ый класс
// <-- квестовые - заглушки !!!!

#define SHIP_CURSED_FDM			49	// Проклятый Калеуче	- военный корабль		- 1-ый класс
#define SHIP_FDM				50	// Копия Калеуче	- военный корабль	    	- 1-ый класс

#define SHIP_LSHIP_QUEST		51	// "Реус де Сан-Педро" - линейный корабль		- 1-ый класс
#define SHIP_ELCASADOR			52  // "Эль Касадор" - галеон               		- 3-ий класс
#define SHIP_ECLIATON			53  // "Эклятон" - французский линейный корабль     - 1-ый класс
#define SHIP_RENOVATED_FDM      54	// Отреставрированный Калеуче                   - 1-ый класс

#define SHIP_BOAT               55	// лодка у берега
#define SHIP_FORT               56	// форт

#define SHIP_NOTUSED			 1000
#define SHIP_NOTUSED_TYPE_NAME	"Not Used"
#define SHIP_NAME_NOTUSED		"Noname"

#define SHIP_SPEC_MERCHANT      0
#define SHIP_SPEC_WAR           1
#define SHIP_SPEC_RAIDER        2
#define SHIP_SPEC_UNIVERSAL     3

object  ShipsTypes[SHIP_TYPES_QUANTITY_WITH_FORT];  // RealShips
object	SailsColors[SAILS_COLOR_QUANTITY];

ref GetShipByType(int iType) { return &ShipsTypes[iType]; }  // пользовать GetRealShip

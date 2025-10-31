#include "characters\RPG\perks\init\self.c"
#include "characters\RPG\perks\init\ship.c"

void extrnInitPerks()
{
	DeleteAttribute(&ChrPerksList, "list");
	// NPCOnly - только НПС  PlayerOnly - только ГГ, Hidden - скрыт для всех, кодерские трюки Боссов-НПС
	// navigator  boatswain  cannoner doctor carpenter treasurer fighter  - офицеры  для  .OfficerType
	// belamour Перки индивидуализации по хиротайпам HT1,HT2,HT3,HT4 для legendary edition (бутафория)
	// Гимнаст(HT1), Счетовод(HT2), Атлет(HT3), Стрелок(HT4)

	// список из ВМЛ -->
	//	Personal Skills Group
	//==========================================================
	aref list;
	makearef(list, ChrPerksList.list);
	initSelfPerks(&list);
	initShipPerks(&list);

	/////////////////////////////////////////////////////////////
	/// Скрытые перки
	/////////////////////////////////////////////////////////////

	// скрытый перк даёт 1.5 к приросту энергии, даётся ГГ и боссам уровней
	ChrPerksList.list.Energaiser.descr = "perkEnergaiser";
	ChrPerksList.list.Energaiser.Hidden = true;
	ChrPerksList.list.Energaiser.cost = 0;
	ChrPerksList.list.Energaiser.BaseType = "Utility";

	// скрытый перк даёт бонус в 5% к базовой скорости корабля при наличии всех карт
	ChrPerksList.list.MapMaker.descr = "perkMapMaker";
	ChrPerksList.list.MapMaker.PlayerOnly = true;
	ChrPerksList.list.MapMaker.Hidden = true;
	ChrPerksList.list.MapMaker.cost = 0;
	ChrPerksList.list.MapMaker.BaseType = "Utility";

	ChrPerksList.list.Rush.descr = "perkRush";
	ChrPerksList.list.Rush.TimeDelay = 72; // 12+60
	ChrPerksList.list.Rush.TimeDuration = 12;
	ChrPerksList.list.Rush.Hidden = true;
	ChrPerksList.list.Rush.cost = 0;
	ChrPerksList.list.Rush.BaseType = "Utility";

	// Личные спецперки при выборе ГГ
	ChrPerksList.list.HT1.descr = "perkHT1";
	ChrPerksList.list.HT1.PlayerOnly = true;
	ChrPerksList.list.HT1.Hidden = true;
	ChrPerksList.list.HT1.cost = 0;
	ChrPerksList.list.HT1.BaseType = "Utility";

	ChrPerksList.list.HT2.descr = "perkHT2";
	ChrPerksList.list.HT2.PlayerOnly = true;
	ChrPerksList.list.HT2.Hidden = true;
	ChrPerksList.list.HT2.cost = 0;
	ChrPerksList.list.HT2.BaseType = "Utility";

	ChrPerksList.list.HT3.descr = "perkHT3";
	ChrPerksList.list.HT3.PlayerOnly = true;
	ChrPerksList.list.HT3.Hidden = true;
	ChrPerksList.list.HT3.cost = 0;
	ChrPerksList.list.HT3.BaseType = "Utility";

	ChrPerksList.list.HT4.descr = "perkHT4";
	ChrPerksList.list.HT4.PlayerOnly = true;
	ChrPerksList.list.HT4.Hidden = true;
	ChrPerksList.list.HT4.cost = 0;
	ChrPerksList.list.HT4.BaseType = "Utility";
}
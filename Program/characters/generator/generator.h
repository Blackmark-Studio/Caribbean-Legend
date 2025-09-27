// Разряды
#define GEN_COMMONER 0 // слабее ГГ
#define GEN_ELITE 1    // типа ГГ
#define GEN_MINIBOSS 2 // сильнее ГГ
#define GEN_BOSS 3     // мощна сильнее ГГ

// Бонусы разрядов к скиллам
#define GEN_COMMONER_SKILL_BONUS 0
#define GEN_ELITE_SKILL_BONUS 6
#define GEN_MINIBOSS_SKILL_BONUS 9
#define GEN_BOSS_SKILL_BONUS 14

// Бонусы разрядов к пиратес фикса
#define GEN_COMMONER_PIRATES_BONUS 3
#define GEN_ELITE_PIRATES_BONUS 4
#define GEN_MINIBOSS_PIRATES_BONUS 5
#define GEN_BOSS_PIRATES_BONUS 5

// Бонусы разрядов к пиратес рандом
#define GEN_COMMONER_PIRATES_BONUS_RANDOM 2
#define GEN_ELITE_PIRATES_BONUS_RANDOM 2
#define GEN_MINIBOSS_PIRATES_BONUS_RANDOM 2
#define GEN_BOSS_PIRATES_BONUS_RANDOM 3


// Типы персонажей
#define GEN_TYPE_ENEMY   0 // тип противника подразумевает, что набор архетипов будет боевой от оружия+корабельный
#define GEN_TYPE_OFFICER 1 // для офицеров набор архетипов может быть любым
#define GEN_TYPE_CAPTAIN 2 // у капитанов набор архетипов будет боевой-от-оружия- +корабельный + бонусы к скиллам от его собственных офицеров
#define GEN_TYPE_HERO    3 // у героев фиксированные шаблоны, их нужно задать до закидывания в генератор

// Архетипы генерации
#define GEN_ARCHETYPE_DUELIST "Duelist"
#define GEN_ARCHETYPE_PIRATE "Pirate"
#define GEN_ARCHETYPE_GUNMAN "Gunman"
#define GEN_ARCHETYPE_SOLDIER "Soldier"
#define GEN_ARCHETYPE_PEASANT "Peasant"
#define GEN_ARCHETYPE_TREASURER "Treasurer"
#define GEN_ARCHETYPE_CARPENTER "Carpenter"
#define GEN_ARCHETYPE_BOATSWAIN "Boatswain"
#define GEN_ARCHETYPE_CANNONER "Cannoner"
#define GEN_ARCHETYPE_NAVIGATOR "Navigator"
#define GEN_ARCHETYPE_DOCTOR "Doctor"

#define GEN_SELF_PERKS_PENALTY -2  // Штраф в очки перков. Эмулирует наличие базовых умений с начала игры, за которые ГГ не получает очков
#define GEN_SHIP_PERKS_PENALTY -2  // Штраф в очки перков. Эмулирует наличие базовых умений с начала игры, за которые ГГ не получает очков
#define ARCHETYPE_M_BONUS 18       // Преимущество в скилле основной профессии (торговля у казначея, ремонт у плотника...). Сглаживается об ранг ГГ
#define ARCHETYPE_M_RANDBONUS 10   // Дополнительное преимущество в скилле основной профессии, здесь рандом до N. Сглаживается об ранг ГГ
#define ARCHETYPE_S_BONUS 9        // Преимущество в скилле второй профессии (хобби)
#define GEN_PIRATES_IMPACT_LEVEL 5 // Уровень импакта пиратес на количество скиллов, имитация того, что персонаж развивался естественным путём. Больше число – меньше импакт
#define GEN_PIRATES_MAX_IMPACT 14  // Максимум очков от пиратес
#define GEN_CHAOS_VALUE 5          // Общий фактор случайности, влияет на разброс умений от уровня ГГ
#define GEN_MAX_ARCHETYPES 6       // Сколько всего архетипов, все боевые считаются здесь за 1 из-за неравного распределения

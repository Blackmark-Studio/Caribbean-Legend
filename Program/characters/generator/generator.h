// Разряды
#define GEN_BY_RANK -1  // значит, что разряд задаётся от целевого ранга, а не наоборот
#define GEN_COMMONER 0 // слабее ГГ
#define GEN_ELITE 1    // типа ГГ
#define GEN_MINIBOSS 2 // сильнее ГГ
#define GEN_BOSS 3     // мощна сильнее ГГ

// Бонусы разрядов к целевому рангу
#define GEN_COMMONER_RANK_OFFSET -1
#define GEN_ELITE_RANK_OFFSET    1
#define GEN_MINIBOSS_RANK_OFFSET 2
#define GEN_BOSS_RANK_OFFSET     5

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
#define GEN_TYPE_ENEMY   0 // тип противника подразумевает, что набор архетипов будет боевой от оружия+корабельный, если не фиксирован
#define GEN_TYPE_OFFICER 1 // для офицеров набор архетипов может быть любым, если не фиксирован

// Архетипы генерации
#define GEN_ARCHETYPE_RANDOM "Random" // будет заменен на случайный
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
#define GEN_ARCHETYPE_FREE "Free"

// Параметр изменения пиратес
#define GEN_FIXED_PIRATES 0
#define GEN_RANDOM_PIRATES 1

// Параметры генератора
#define GEN_SELF_PERKS_PENALTY -20 // Штраф в очки перков. Эмулирует наличие базовых умений с начала игры, за которые ГГ не получает очков
#define GEN_SHIP_PERKS_PENALTY -20 // Штраф в очки перков. Эмулирует наличие базовых умений с начала игры, за которые ГГ не получает очков
#define ARCHETYPE_M_BONUS 18       // Преимущество в скилле основной профессии (торговля у казначея, ремонт у плотника...). Сглаживается об ранг ГГ
#define ARCHETYPE_M_RANDBONUS 6    // Дополнительное преимущество в скилле основной профессии, здесь рандом до N. Сглаживается об ранг ГГ
#define ARCHETYPE_S_BONUS 10       // Преимущество в скилле второй профессии (хобби)
#define GEN_CHAOS_VALUE 3          // Общий фактор случайности, влияет на разброс умений от уровня ГГ
#define GEN_MAX_ARCHETYPES 6       // Сколько всего архетипов, все боевые считаются здесь за 1 из-за неравного распределения
#define GEN_MUSKETERS_OFFSET 12    // Шифт пистолетов/среднег оружия для мушкетеров

// Влияние сложности на хп-за-уровень для врагов, при изменении не забыть поменять GEN_CHECK_SUM
#define GEN_ENEMY_COMMONER_HP_BONUS "0|0|1|2|4"
#define GEN_ENEMY_ELITE_HP_BONUS    "1|2|3|4|6"
#define GEN_ENEMY_MINIBOSS_HP_BONUS "2|3|4|5|8"
#define GEN_ENEMY_BOSS_HP_BONUS     "4|5|6|8|12"

// Влияние сложности на хп-за-уровень для офицеров, при изменении не забыть поменять GEN_CHECK_SUM
#define GEN_OFFICER_COMMONER_HP_BONUS "2|1|0|0|0"
#define GEN_OFFICER_ELITE_HP_BONUS    "2|1|0|0|0"
#define GEN_OFFICER_MINIBOSS_HP_BONUS "2|2|0|0|0"
#define GEN_OFFICER_BOSS_HP_BONUS     "3|4|0|0|0"

#define GEN_PLAYER_HP_BONUS "5|3|0|0|0" // Влияние сложности на хп-за-уровень для ГГ
#define GEN_CHECK_SUM "22.12.2025"      // Тут просто строка для понимания, что конфиг формата val|val|val актуален, можно ставить дату редактирования

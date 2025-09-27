#define SKILL_MTP_POWER 0.55           // степень, в которую возводим скилл владения оружием для влияния на урон

#define BASE_CRIT_CHANCE 0.05          // базовый шанс крит-удара, 1 процент = 0,01
#define CRIT_PSEUDO_RANDOM_VALUE 0.002 // на сколько меняется шанс крита в псевдорандоме, 1 процент = 0.01
#define CRIT_MTP 0.4                   // бонус-множитель крита, 1 процент = 0,01
#define HEADSHOT_MTP 0.4               // бонус-множитель хедшота, 1 процент = 0,01

#define EXP_FOR_HIT 0.8                // коэффициент получения опыта за удар
#define EXP_FOR_KILL 0.8               // коэффициент получения опыта за убийство

#define BACKSTAB_ANGLE 25.0            // разница между 180 и фактическим углом удара, принимаемая за удар в спину, 25 это от 155 до 205

#define FORCE_STRIKE "force" // обычная
#define FAST_STRIKE  "fast"  // быстрая атака
#define ROUND_STRIKE "round" // круговая
#define BREAK_STRIKE "break" // пробивающий
#define FEINT_STRIKE "feint" // финт
#define SHOT_STRIKE  "shot"  // выстрел как тип удара, для упрощения подсчётов
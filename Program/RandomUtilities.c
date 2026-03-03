// Движковые: frnd, rand, hrand

float frand(float _x)
{
	return rand(32768) / 32768.0 * _x;
}

float frandSmall(float _x)
{
	return rand(32) / 32.0 * _x;
}

float uniform(float x, float y)
{
  return x + frand(y - x);
}

float uniform_angle(float left, float right) 
{
  return uniform(PI * left / 180.0, PI * right / 180.0);
}

aref GetRandomAttr(aref Lottery)
{
    int num = GetAttributesNum(Lottery);
    if (num == 0) return ErrorAttr();
    return GetAttributeN(Lottery, rand(num-1));
}

string GetRandomAttrName(aref Lottery)
{
    return GetAttributeName(GetRandomAttr(Lottery));
}

////////////////////////////////////////////////////////////////////////
//  WEIGHT RANDOM (АТРИБУТНЫЙ)
////////////////////////////////////////////////////////////////////////
//  1. Лотерея создаётся в виде:
//     LTR.LotteryName.participant_1.weight = n_1;
//     LTR.LotteryName.participant_2.weight = n_2;
//     ...
//  2. Через wrand(LotteryName) получим имя победителя,
//     через GetRandomAttrByWeight(LotteryName) получим aref.
//  3. Как правило, веса задаются в InitWeightParameters.
//     Как правило, после лотереи веса меняются в CorrectWeightParameters.
//  4. Чтобы определить победителя через hrand используется wrand_h.
////////////////////////////////////////////////////////////////////////

// TO_DO: Это и тасование вынести в C-API в нормальном виде
int WeightRandomMethod(ref iMassive)
{
    int i, n;
    int Size = GetArraySize(iMassive);
    int Summ = -1;
    for (i = 0; i < Size; i++) Summ += iMassive[i];
    if (wrand_h_tag != "") n = hrand(Summ, wrand_h_tag);
    else n = rand(Summ);
    for (i = 0; n >= 0; i++) n -= iMassive[i];
    return i-1;
}

// Подготовка участников лотереи
int WeightRandom(aref Lottery)
{
    aref participant;
    string sNumber;
    int num = GetAttributesNum(Lottery);
    if(num == 0) return -1;
    int iMassive[num];
    int k = 0;
    for(int i = 0; i < num; i++)
    {
        participant = GetAttributeN(Lottery,i);
        if(CheckAttribute(participant, "weight") && sti(participant.weight) > 0)
        {
            sNumber = k;
            LTR.LotteryProcess.(sNumber) = i;
            iMassive[k] = sti(participant.weight);
            k++;
        }
    }
    if(k == 0) return -1;
    SetArraySize(&iMassive, k);
    sNumber = WeightRandomMethod(&iMassive);
    sNumber = LTR.LotteryProcess.(sNumber);
    DeleteAttribute(&LTR, "LotteryProcess");
    return sti(sNumber);
}

// Получить ссылку на победителя лотереи
aref GetRandomAttrByWeight(aref Lottery)
{
    int iWinner = WeightRandom(Lottery);
    if (iWinner == -1) return ErrorAttr();
    return GetAttributeN(Lottery, iWinner);
}

// Получить имя победителя по названию лотереи
// GetRandomAttrNameByWeight
string wrand(string sLottery)
{
    aref Lottery;
    makearef(Lottery, LTR.(sLottery));
    aref aWinner = GetRandomAttrByWeight(Lottery);
    return GetAttributeName(aWinner);
}

string wrand_h_tag = "";
string wrand_h(string sLottery, string tag)
{
    if (tag == "") wrand_h_tag = sLottery;
    else wrand_h_tag = tag;
    sLottery = wrand(sLottery);
    wrand_h_tag = "";
    return sLottery;
}

// Взятие наибольшего по весу
string GetMaxWeightAttr(string sLottery)
{
    aref Lottery, participant;
    makearef(Lottery, LTR.(sLottery));

    int i, iMax = 0;
    int num = GetAttributesNum(Lottery);
    if(num == 0) return "Error"; //Нет участников
    for(i = 0; i < num; i++)
    {
        participant = GetAttributeN(Lottery,i);
        if(sti(participant.weight) > iMax) iMax = sti(participant.weight);
    }
    if(iMax <= 0) return "Error"; //Нет валидных участников

    int k = 0;
    string sTemp;
    for(i = 0; i < num; i++)
    {
        participant = GetAttributeN(Lottery,i);
        if(sti(participant.weight) == iMax)
        {
            sTemp = k;
            LTR.LotteryProcess.(sTemp) = i; //Общий номер участника
            k++;
        }
    }

    sTemp = rand(k); //Рандом среди равных весов
    sTemp = LTR.LotteryProcess.(sTemp);
    DeleteAttribute(&LTR, "LotteryProcess");

    sTemp = GetAttributeName(GetAttributeN(Lottery, sti(sTemp)));
    CorrectWeightParameters(sLottery, sTemp, "GetMax");
    return sTemp;
}

////////////////////////////////////////////////////////////////////////
//  ROSARAK HASH RANDOM
////////////////////////////////////////////////////////////////////////
//  ПОЛОЖНЯК:
//  1. hrand(n) возвращает случайное число от 0 до n:
//   - Одно и то же в течении суток
//   - В отличие от drand, числа определяются независимо в разных местах использования
//  2. В качестве второго аргумента опционально указывается тэг:
//   - Можно hrand(n), можно hrand(n, tag)
//  3. В диалогах с персонажем к тэгу автоматически добавляются его id и имя
//  4. Два hrand отождествляются, если у них одинаковый тэг с первым символом '&'
//  5. В среднем это работает всего на 15% медленнее обычного rand
////////////////////////////////////////////////////////////////////////

void UpdateSeeds()
{
    GSeed = rand(INT_MAX);
    SetGlobalSeed(GSeed);
}

// Для каждой конкретной даты и тэга число предопределено
int DateRandom(int n, string tag)
{
    tag += "_" + Environment.date.year + "." + Environment.date.month + "." + Environment.date.day;
    return TagRandom(n, tag);
}

// Для каждого конкретного тэга число предопределено
int TagRandom(int n, string tag)
{
    float fSeed = GetFractionByHash(Hash(tag + PChar.PersonalSeed));
    return MakeInt(fSeed * (n + 1));
}

// TO_DO: Сделать нормальную версию в C-API
float GetFractionByHash(int iHash)
{
    if (iHash == INT_MIN) return 0.83647;
    return (abs(iHash) % 100000) * 0.00001; 
}

////////////////////////////////////////////////////////////////////////
//  ПОКУПКА ЛОТЕРЕЙНЫХ БИЛЕТОВ (АТРИБУТНАЯ)
////////////////////////////////////////////////////////////////////////

// Первичное выставление весовых параметров в начале игры
void InitWeightParameters()
{
    int i, j;
    string sTemp, sVar;

    // Карты сокровищ
    for(i = 1; i <= 15; i++)
    {
        sTemp = "T" + i;
        LTR.TresuareMapTier.(sTemp) = i;
        LTR.TresuareMapTier.(sTemp).weight = 10;
    }
    // Описания карт сокровищ (shuffle bag)
    for(i = 1; i <= 3; i++)
    {
        sTemp = "T" + i;
        for(j = 1; j <= 3; j++)
        {
            sVar = "v" + j;
            LTR.TresuareMapDescribe.(sTemp).(sVar) = j;
        }
    }
}

// Корректировка весов
void CorrectWeightParameters(string sLottery, string Winner, string sCase)
{
    aref Lottery, participant;
    makearef(Lottery, LTR.(sLottery));
    string sTemp;
    int iTemp, i;
    int num = GetAttributesNum(Lottery);

    switch(sCase)
    {
        case "GetMax":
            for(i = 0; i < num; i++)
            {
                participant = GetAttributeN(Lottery,i);
                if(GetAttributeName(participant) == Winner)
                    iTemp = sti(participant.weight) - sti(participant.decrease);
                else
                    iTemp = sti(participant.weight) + sti(participant.increase);
                participant.weight = iClamp(0, sti(participant.weight_max), iTemp);
            }
            break;

        case "Treasure":
            // Выпавший тир
            i = sti(Lottery.(Winner).weight) - 3;
            Lottery.(Winner).weight = iClamp(0, 20, i);
            // Соседи
            iTemp = sti(Lottery.(Winner));
            if(iTemp != 1)
            {
                sTemp = "T" + (iTemp-1);
                i = sti(Lottery.(sTemp).weight) + 1;
                Lottery.(sTemp).weight = iClamp(0, 20, i);
            }
            if(iTemp != 15)
            {
                sTemp = "T" + (iTemp+1);
                i = sti(Lottery.(sTemp).weight) + 1;
                Lottery.(sTemp).weight = iClamp(0, 20, i);
            }
            break;

        case "Winner":
            break;

        case "Daily":
            break;
    }
}

// Бросок с шансом n
bool PercentChance(int chance)
{
  return chance > rand(99);
}

// Бросок с шансом n
bool fPercentChance(float chance)
{
  return chance > frandSmall(0.99);
}

// Берем два числа из диапазона по принципу если первое число больше половины, тогда 
// второе число берется из предыдущих, а если меньше – из следующих
void SetTwoRandomNums(int max, ref a, ref b, string dayLockTag)
{
	int tempA;
	int tempB;
	tempA = randWWoDate(max, dayLockTag);
	if (tempA > (max / 2)) tempB = randWWoDate(tempA - 1, dayLockTag);
	else tempB = randWWoDate(max - tempA - 1, dayLockTag) + tempA + 1;

	a = tempA;
	b = tempB;
}

// Рандом с пробросом флага закрепления за датой
int randWWoDate(int max, string tag)
{
	if (tag != "") return DateRandom(max, tag);
	return rand(max);
}

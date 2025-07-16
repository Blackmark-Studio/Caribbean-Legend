// Движковые: frnd, rand, hrand, wrand_h

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
//  ROSARAK WEIGHT RANDOM
////////////////////////////////////////////////////////////////////////
//  ПОЛОЖНЯК:
//  1. Лотерея создаётся в виде:
//     LTR.LotteryName.participant_1.weight = n_1;
//     LTR.LotteryName.participant_2.weight = n_2;
//     ...
//  2. Через wrand(LotteryName) получим имя победителя,
//     через GetRandomAttrByWeight(LotteryName) получим aref.
//  3. Как правило, веса задаются в InitWeightParameters.
//     Как правило, после лотереи веса меняются в CorrectWeightParameters.
//  4. Чтобы определить победителя через hrand используется wrand_h.
//     В нём опционально вторым аргументом указывается тэг:
//     Можно wrand_h(LotteryName), можно wrand_h(LotteryName, tag).
////////////////////////////////////////////////////////////////////////

// Лотерея для целочисленных массивов (она же развесовка)
// Здесь нет проверки валидности, так как массив предварительно подготавливается в WeightRandom
int WeightRandomMethod(ref iMassive)
{
    int i, n;
    int Size = GetArraySize(iMassive);
    int Summ = -1; //чтобы рандомило от 0 до Summ-1
    for (i = 0; i < Size; i++) Summ += iMassive[i];
    if(CheckAttribute(&LTR, "WRM"))
    {
        n = hrand(Summ, LTR.WRM.TAG);
        DeleteAttribute(&LTR, "WRM");
    }
    else n = rand(Summ);
    for (i = 0; n >= 0; i++) n -= iMassive[i]; //Определяем победителя
    return i-1; //После победителя был инкремент, поэтому -1
}

// Подготовка участников лотереи
int WeightRandom(aref Lottery)
{
    aref participant;
    string sNumber; //Для конвертации
    int num = GetAttributesNum(Lottery);
    if(num == 0) return -1; //Нет участников
    int iMassive[2]; //Меньше 2 нельзя!
    int k = 0;
    SetArraySize(&iMassive, num);
    for(int i = 0; i < num; i++)
    {
        participant = GetAttributeN(Lottery,i);
        if(CheckAttribute(participant, "weight") && sti(participant.weight) > 0)
        {
            sNumber = k;
            LTR.LotteryProcess.(sNumber) = i; //Общий номер участника
            iMassive[k] = sti(participant.weight); //Сколько билетов купил
            k++;
        }
    }
    if(k == 0) return -1; //Нет валидных участников
    SetArraySize(&iMassive, k); //Срезаем лишнее
    sNumber = WeightRandomMethod(&iMassive); //Проводим лотерею
    sNumber = LTR.LotteryProcess.(sNumber);
    DeleteAttribute(&LTR, "LotteryProcess");
    return sti(sNumber); //Победил атрибут под номером sNumber!
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

// Для wrand_h, если тэг не указан отдельно, используется название лотереи
// В этом случае также можно добавлять спецсимволы @ и &
#event_handler("evntWeightHashRandom","WeightHashRandom");
string WeightHashRandom()
{
    LTR.WRM.TAG = GetEventData();
    string sLottery = GetEventData();

    if(LTR.WRM.TAG == "")
    {
        LTR.WRM.TAG = sLottery;

        // Удаляем спецсимволы
        int i, iMax = strlen(sLottery);
        string s1, s2 = "";
        for (i = 0; i < iMax; i++)
        {
            s1 = GetSymbol(sLottery, i);
            if (s1 != "@" && s1 != "&")
                s2 += GetSymbol(sLottery, i);
        }
        sLottery = s2;
    }

    return wrand(sLottery);
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
//     Можно hrand(n), можно hrand(n, tag). 
//  3. В диалогах с персонажем к тэгу автоматически добавляется id + имя.
//  4. Чтобы использовать предопределённую на сутки очередь значений,
//     в тэге дожен присутствовать символ '@'.
//  5. Чтобы отождествить два hrand в разных местах, в их тэгах должен присутствовать
//     символ '&'.
//  6. Два одинаковых hrand, находящиеся в одной строке файла, вернут одно и то же,
//     если только не используют очередь.
////////////////////////////////////////////////////////////////////////

void UpdateSeeds()
{
    GlobalSeed = rand(100000);
    DeleteAttribute(&HTBL, "");
}

#event_handler("evntHashRandom","HashRandom");
int HashRandom()
{
    int n = GetEventData();
    string tag = GetEventData();
    string callID = GetEventData();
    bool inDiag = GetEventData(); // dialogRun не подходит, надо проверять стек вызовов
    bool bQueue = (FindSubStr(tag, "@", 0) != -1); //Генерировать новое зерно по номеру вызова

    string HRAND_ID;
    if(FindSubStr(tag, "&", 0) != -1) HRAND_ID = tag; //Универсальный тэг
    else
    {
        if(inDiag) tag += CharacterRef.id + CharacterRef.name; //Авто
        HRAND_ID = callID + "_" + tag;
    }

    aref CurCall;
    makearef(CurCall, HTBL.(HRAND_ID));

    float fSeed;
    if(CheckAttribute(CurCall, "Seed"))
    {
        // Таймер не истёк
        if(bQueue) GetCurSeed(CurCall, &fSeed);
        else fSeed = stf(CurCall.Seed);
    }
    else
    {
        GetCurSeed(CurCall, &fSeed);
        CurCall.Seed = fSeed;
        if(bQueue) CurCall.callCount = 0; 
    }

    return MakeInt(fSeed * (n + 1));
}

void GetCurSeed(aref CurCall, ref fSeed)
{
    int iHash;
    if(!CheckAttribute(CurCall, "Seed"))
    {
        //Выбор первого зерна
        iHash = hash(GetAttributeName(CurCall) + GlobalSeed);
    }
    else
    {
        //Выбор нового зерна для очереди (bQueue) 
        CurCall.callCount = sti(CurCall.callCount) + 1;
        iHash = hash(CurCall.callCount + CurCall.Seed);
    }
    fSeed = GetFractionByHash(iHash);
}

float GetFractionByHash(int iHash)
{
    iHash = abs(iHash) % 100000; //Последние 5 цифр
    if(iHash < 1) return 0.0;

    string fResult = iHash;
    while(iHash < 10000)
    {
        fResult = "0" + fResult;
        iHash *= 10;
    }
    fResult = "0." + fResult;
    return stf(fResult);
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

////////////////////////////////////////////////////////////////////////
//  ПОКУПКА ЛОТЕРЕЙНЫХ БИЛЕТОВ
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

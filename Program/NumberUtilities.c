
#define PI 3.14159265
#define PIm2 6.28318530
#define PId2 1.57079632

float Radian2Degree(float _rad) 
{
	return 180 / PI * _rad;
}

float NormalizeAngle(float Angle)
{
	while (Angle >= PIm2) Angle -= PIm2;
	while (Angle < 0.0)   Angle += PIm2;

	return Angle;
}

int func_max(int a, int b)
{
	if (a > b) return a;
	return b;
}

int func_min(int a, int b)
{
	if (a > b) return b;
	return a;
}

float func_fmax(float a, float b)
{
	if (a > b) return a;
	return b;
}

float func_fmin(float a, float b)
{
	if (a > b) return b;
	return a;
}

int iClamp(int min, int max, int val)
{
	if(val < min) val = min;
	else
	{
		if(val > max) val = max;
	}
	return val;
}

float fClamp(float min, float max, float val)
{
	if(val < min) val = min;
	else
	{
		if(val > max) val = max;
	}
	return val;
}

int iabs(int num)
{
	if (num < 0)
		return -num;
	else
		return num;
}

//Mett: универсальная функция для диапазона чисел
void wRange(ref _num, ref _min, ref _max)
{
    if(_num < _min) _num = _min; //мин порог
    if(_num > _max) _num = _max; //макс порог
}

//Mett: диапазон чисел для float
float wRangeFloat(float _num, float _min, float _max)
{
    if(_num < _min) _num = _min; //мин порог
    if(_num > _max) _num = _max; //макс порог
    return _num;
}

//Mett: диапазон чисел для int
int wRangeInt(int _num, int _min, int _max)
{
    if(_num < _min) _num = _min; //мин порог
    if(_num > _max) _num = _max; //макс порог
    return _num;
}

//Mett: расчёт процентов от числа для float
float wPercentFloat(float _num, float _percent)
{
    float _value = _num * _percent * 0.01;
    return _value;
}

//Mett: расчёт процентов от числа для int
int wPercentInt(int _num, int _percent)
{
    int _value = _num * _percent / 100;
    return _value;
}

// belamour возвращает значение в зависимости от условия
int GetIntByCondition(bool condition, int falseValue, int trueValue)
{
	if(condition) return trueValue;
	return falseValue;
}

float GetFloatByCondition(bool condition, float falseValue, float trueValue)
{
	if(condition) return trueValue;
	return falseValue;
}

// belamour Линейная интерполяция
// Bring2Range, Bring2RangeNoCheck
float linear_interpolate(float x, float x1, float y1, float x2, float y2)
{
	// если вдруг за пределами интерполяции
    if (x < x1) return y1;
    if (x > x2) return y2;
	
    return y1 + (x - x1) * (y2 - y1) / (x2 - x1);
}

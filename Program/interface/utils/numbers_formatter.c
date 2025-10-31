// Выводим числа в интерфейсы без лишних нулей и точек с максимум двумя знаками после запятой
// 20 → 20
// 20.00 → 20
// 20.50 → 20.5
// 20.76 → 20.76
string ToHumanNumber(ref number_string)
{
	string str = "error";
	switch (VarType(&number_string))
	{
		case "int":    return its(number_string);                  break;
		case "string": str = FloatToString(stf(number_string), 2); break;
		case "float":  str = FloatToString(number_string, 2);      break;
	}

	if (str == "error")
	{
		trace("Incorrect argument for ToHumanNumber");
		return "";
	}

	int dotPos = FindSubStr(str, ".", 0);
	string result = strcut(str, 0, dotPos-1);
	int floatPart = sti(strright(str, 2));
	if (floatPart == 0) return result;

	if (floatPart % 10 > 0) return result + "." + floatPart;
	else return result + strcut(str, dotPos, dotPos+1);
}

// Игромеханический флоат в виде читабельного процента
// 0.02 → "2 %", 0.1 → "10 %", 0,3764 → "37,64 %"
string ToHumanPercent(float percent)
{
	return ToHumanNumber(percent * 100) + " %";
}

// Вывод числа с фиксированным количеством цифр после точки
string FloatToString(float fl,int nDigAfterPoint)
{
  return fts(fl, nDigAfterPoint);
}
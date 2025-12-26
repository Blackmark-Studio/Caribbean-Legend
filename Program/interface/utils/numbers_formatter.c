// Выводим числа в интерфейсы без лишних нулей и точек с максимум двумя знаками после запятой
// 20 → 20
// 20.00 → 20
// 20.50 → 20.5
// 20.76 → 20.76
string ToHumanNumber(ref number_string)
{
	string str = "error";
	switch (VarType(number_string))
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
// Либо целое число + %
// 25 → "25 %"
string ToHumanPercent(ref percent)
{
	switch (Vartype(percent))
	{
		case "int": return ToHumanNumber(percent) + " %"; break;
		case "float": return ToHumanNumber(percent * 100) + " %"; break;
	}

	trace("Error: wrong percent type in ToHumanPercent()");
	return "error";
}


// Вывод числа с фиксированным количеством цифр после точки
string FloatToString(float fl,int nDigAfterPoint)
{
  return fts(fl, nDigAfterPoint);
}

// Выводим числа в интерфейсы без лишних нулей и точек с максимум двумя знаками после запятой, но с плюсом или минусом
string ToHumanModifier(ref number_string)
{
	string sNumber = ToHumanNumber(number_string);
	float number = stf(sNumber);
	if (number > 0) sNumber = "+ " + sNumber;
	// else if (number < 0) sNumber = "- " + sNumber;
	return sNumber;
}

// Игромеханический флоат в виде читабельного процента, но с плюсом или минусом
string ToHumanModifierPercent(ref number_string)
{
	string sNumber = ToHumanPercent(number_string);
	float number = stf(sNumber);
	if (number > 0) sNumber = "+ " + sNumber;
	// else if (number < 0) sNumber = "- " + sNumber;
	return sNumber;
}
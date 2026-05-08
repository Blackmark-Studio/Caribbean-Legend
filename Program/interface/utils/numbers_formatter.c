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
		case VAR_INTEGER: return its(number_string); break;
		case VAR_STRING: str = FloatToString(stf(number_string), 2); break;
		case VAR_FLOAT:  str = FloatToString(number_string, 2);      break;
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
	string result = "";
	switch (Vartype(percent))
	{
		case VAR_INTEGER: result = ToHumanNumber(percent); break;
		case VAR_FLOAT: result = ToHumanNumber(percent * 100); break;
	}

	if (result == "")
	{
		trace("Error: wrong percent type in ToHumanPercent()");
		return "error";
	}

	// исключения форматирования по языкам
	switch (LanguageGetLanguage())
	{
		case "russian": return result + " %"; break;
		case "turkish": return "%" + result; break;
	}

	return result + "%";
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
	if (number > 0) sNumber = "+" + sNumber;
	// else if (number < 0) sNumber = "- " + sNumber;
	return sNumber;
}

// Игромеханический флоат в виде читабельного процента, но с плюсом или минусом
string ToHumanModifierPercent(ref number_string)
{
	string sNumber = ToHumanPercent(number_string);
	float number = stf(sNumber);
	if (number > 0) sNumber = "+" + sNumber;
	// else if (number < 0) sNumber = "- " + sNumber;
	return sNumber;
}
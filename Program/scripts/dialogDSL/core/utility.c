// Iternal helpers

string DLG_RandArgument(ref args, int argsCount)
{
  return GetAttributeValue(GetAttributeN(&args, rand(argsCount-1)));
}

// Just safety calls
string DLG_GetObjectAttributeSafe(ref obj, string attribute)
{
  if (CheckAttribute(&obj, attribute)) return obj.(attribute);
  trace("Error: missing argument " + attribute);
  return ("Error: missing argument " + attribute);
}

// Just safety calls
string DLG_A(ref args, int index)
{
  string argName = "var" + index;
  return DLG_GetObjectAttributeSafe(&args, &argName);
}

//Syntax sugar for first argument
string DLG_A0(ref args)
{
  return DLG_A(&args, 0);
}

//Syntax sugar for second argument
string DLG_A1(ref args)
{
  return DLG_A(&args, 1);
}

//Syntax sugar for third argument
string DLG_A2(ref args)
{
  return DLG_A(&args, 2);
}

// func("aXbXcX", "X", "Y", 0) → "aYbYcY"
// func("aXbXcX", "X", "Y", 3) → "aXbYcY"
void DLG_ReplaceAllMatches(string input, string key, string replace, int curPos)
{
  int markPos = FindSubStr(&input, key, curPos);
  if (markPos < 0) return;
  int keyLength = strlen(&key);

  string start   = "";
  string end     = "";
  if (markPos > 0) start = strcut(input, 0, markPos-1);
  end = strcut(input, markPos+keyLength, strlen(&input)-1);

  input = start + replace + end;
  DLG_ReplaceAllMatches(input, &key, &replace, markPos); // looking for the next replacement
}

// func(obj, "a|b|c", "|", 0) →
//   obj.var0 = a
//   obj.var1 = b
//   obj.var2 = c
void DLG_SplitString(ref result, string input, string bySym, int iteration)
{
  string varName = "var" + iteration;
  int iPos = findsubstr(input, "|", 0);
  result.(varName) = input;
  if (iPos < 0) return;

  if (iPos == 0) result.(varName) = "";
  else result.(varName) = strcut(input, 0, iPos-1);

  DLG_SplitString(&result, strcut(&input, iPos+1, strlen(&input)-1), &bySym, iteration+1);
}

// Shortcuts
// $shortcut → result

// Looking for a specific key
void DLG_Replace(string input, ref context, string key)
{
  int iPos = FindSubStr(input, key, 0);
  if (iPos == -1) return;

  int lastIdx = iPos + strlen(&key);
  string start = "";
  string end = "";
  if (iPos > 0) start = strcut(input, 0, iPos-1);
  if (lastIdx < strlen(&input)) end = strcut(input, lastIdx, strlen(&input)-1);

  input = start + DLG_RunReplace(&key, &context) + end;
  DLG_Replace(input, &context, &key);
}

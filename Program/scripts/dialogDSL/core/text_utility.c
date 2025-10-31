// Text stuff

// Lower and Upper register by keys "^" and "_" 
void DLG_ModifyAllRegister(string input)
{
  DLG_ModifyRegister(&input, "^", 0);
  DLG_ModifyRegister(&input, "_", 0);
}

void DLG_ModifyRegister(string input, string key, int startPos)
{
  int markPos = FindSubStr(input, key, startPos);
  if (markPos < 0) return;

  int length = strlen(&input);
  string start   = "";
  string end     = "";
  if (markPos+3 > length) return;

  string replace = strcut(input, markPos+1, markPos+2);
  if (key == "^") replace = ToUpper(replace);
  else replace = GetStrSmallRegister(replace);

  if (markPos > 0) start = strcut(input, 0, markPos-1);
  if (markPos+3 < length) end = strcut(input, markPos+3, length-1);

  input = start + replace + end;
  DLG_ModifyRegister(&input, &key, markPos); // looking for the next replacement
}

void DLG_EscapeAllChars(string input)
{
  DLG_ReplaceAllMatches(&input, "\(", "{{", 0);
  DLG_ReplaceAllMatches(&input, "\)", "}}", 0);
}

void DLG_UnescapeAllChars(string input)
{
  DLG_ReplaceAllMatches(&input, "{{", "(", 0);
  DLG_ReplaceAllMatches(&input, "}}", ")", 0);
}

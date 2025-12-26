// DSL for localizations files

#include "scripts\dialogDSL\core\utility.c"           // iternal helpers
#include "scripts\dialogDSL\core\text_utility.c"      // lower/uper register
#include "scripts\dialogDSL\core\simple_replace.c"    // replace $shortcut$
#include "scripts\dialogDSL\core\functions_replace.c" // replace $func(args)
#include "scripts\dialogDSL\defines.c"                // DSL-functions and shorcuts defines here
#include "scripts\dialogDSL\helpers.c"                // helpers for localization stuff

// Main function to use
string DLGO(string input, ref context)
{
  DLG_EscapeAllChars(&input);             // escape all system chars like \( and \) to {{}}
  DLG_ReplaceSimpleKeys(&input, context); // replace all the simple shortcuts like $shortcut
  DLG_RunAllFunctions(&input, context);   // replace all the functions like $func(args)
  DLG_ModifyAllRegister(&input);          // lower and Upper register by keys "^" and "_"
  DLG_UnescapeAllChars(&input);           // return all system chars back from {{}} to ()
  return "" + input;
}

// Universal translate function
string DLG_Convert(string key, string filename, ref context)
{
  string result;
  object tempContext;
  CopyAttributes(&tempContext, context);
  tempContext.filename = filename;
  if (filename != "") result = GetConvertStr(key, filename);
  else result = xiStr(key); // empty filename so we looking in common.ini

  if (result == "" || result == " ") return "Key " + key + " in " + filename;
  if (HasSubStr(result, "#")) result = GetAssembledString(result, &tempContext);
  return DLGO(result, &tempContext);
}

// Universal translate function with empty result
string DLG_ConvertE(string key, string filename, ref context)
{
  string result;
  object tempContext;
  CopyAttributes(&tempContext, context);
  tempContext.filename = filename;
  if (filename != "") result = GetConvertStr(key, filename);
  else result = xiStr(key); // empty filename so we looking in common.ini

  if (HasSubStr(result, "#")) result = GetAssembledString(result, &tempContext);
  return DLGO(result, &tempContext);
}
// имя персонажа
string GetCharacterName(string _param)
{
    int    idLngFile = -1;
    string totalInfo;

    idLngFile = LanguageOpenFile("CharactersStaticNames.txt");
    totalInfo = LanguageConvertString(idLngFile, _param);
    LanguageCloseFile(idLngFile);

    return totalInfo;
}

// название корабля
string GetShipName(string _param)
{
    int    idLngFile = -1;
    string totalInfo;

    idLngFile = LanguageOpenFile("ShipNames.txt");
    totalInfo = LanguageConvertString(idLngFile, _param);
    LanguageCloseFile(idLngFile);

    return totalInfo;
}

// Архетип
string GetCharacterArchetype(ref chr, string type)
{
	if (type == "main") return GetAttributeOrDefault(chr, "Personality.mainArchetype", "");
	else return GetAttributeOrDefault(chr, "Personality.SecondaryArchetype", "");
}
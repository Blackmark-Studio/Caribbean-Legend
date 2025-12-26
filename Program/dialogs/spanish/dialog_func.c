#include "scripts\utils.c"

// boal -->
#define CARDS_RULE "Las reglas son simples.  Blackjack. 36 cartas, de seis a ases. El as vale 11 puntos, los reyes - 4, el señor (caballo caballero) - 3, Nobile (soldado de a pie) - 2, el resto tiene el mismo valor que el escrito. Tu objetivo es conseguir 21 puntos. Haz clic en el mazo para coger una carta más. Cada carta es una apuesta. Haz clic en un retrato en la parte superior derecha para terminar tu turno. Necesitas suficiente dinero para al menos tres apuestas si quieres jugar. Presiona esc o una cruz si has terminado."
#define DICE_RULE "Dados. Cinco para cada jugador. Puedes derribar a los cinco o a cualquiera de ellos pero sólo una vez. Cada dado es una apuesta. Tu objetivo es conseguir la máxima puntuación.\nAquí van las combinaciones: dúo (2), dos dúos (2+2), tríada (3), full (3+2), cuadrado (4), calle (dados en fila) y póker (5). \n Haz clic en un recipiente para lanzar, haz clic en un dado para derribar este dado en particular, haz clic en un retrato para terminar tu turno (en caso de que no necesites derribar o no tengas suficiente dinero para hacerlo)."
#define MAX_TITLENEXTRATE 13 // счетчик для званий
#define MAX_TITLE 5
// boal <--

object Address_Form;

void Set_inDialog_Attributes()
{
	ref The_Character_is;

	The_Character_is = GetMainCharacter();
	if (!CheckAttribute(The_Character_is, "sex") || The_Character_is.sex == "man")
	{
		Address_Form.Spa = "señor";
		Address_Form.Fra = "monsieur";
		Address_Form.Eng = "sir";
		Address_Form.Hol = "mynheer";
		Address_Form.Pir = "sir";
	}
	else
	{
		Address_Form.Spa = "señorita";
		Address_Form.Fra = "mademoiselle";
		Address_Form.Eng = "miss";
		Address_Form.Hol = "lady";
		Address_Form.Pir = "miss";
	}
	Address_Form.Spa.Title1 = "Corsario";
	Address_Form.Fra.Title1 = "Privateer";
	Address_Form.Eng.Title1 = "Caper";
	Address_Form.Hol.Title1 = "Filibuster";
	Address_Form.Pir.Title1 = "Pirate";

	Address_Form.Spa.Title2 = "Comandante";
	Address_Form.Fra.Title2 = "Commander";
	Address_Form.Eng.Title2 = "Commander";
	Address_Form.Hol.Title2 = "Commander";
	Address_Form.Pir.Title2 = "Commander";

	Address_Form.Spa.Title3 = "Capitán";
	Address_Form.Fra.Title3 = "Captain";
	Address_Form.Eng.Title3 = "Captain";
	Address_Form.Hol.Title3 = "Captain";
	Address_Form.Pir.Title3 = "Captain";

	Address_Form.Spa.Title4 = "Comodoro";
	Address_Form.Fra.Title4 = "Commodore";
	Address_Form.Eng.Title4 = "Commodore";
	Address_Form.Hol.Title4 = "Commodore";
	Address_Form.Pir.Title4 = "Commodore";

	Address_Form.Spa.Title5 = "Almirante";
	Address_Form.Fra.Title5 = "Admiral";
	Address_Form.Eng.Title5 = "Admiral";
	Address_Form.Hol.Title5 = "Admiral";
	Address_Form.Pir.Title5 = "Admiral";

	Address_Form.Spa.woman = "señora";
	Address_Form.Fra.woman = "madame";
	Address_Form.Eng.woman = "missis";
	Address_Form.Hol.woman = "lady";
	Address_Form.Pir.woman = "missis";

	Address_Form.Spa.man = "señor";
	Address_Form.Fra.man = "monsieur";
	Address_Form.Eng.man = "sir";
	Address_Form.Hol.man = "mynheer";
	Address_Form.Pir.man = "sir";
	/*switch (The_Character_is.id)
	{
		case "Blaze":

			Address_Form.Spa = GlobalStringConvert("Address_Form_Spa");
			Address_Form.Fra = GlobalStringConvert("Address_Form_Fra");
			Address_Form.Eng = GlobalStringConvert("Address_Form_Eng");
			Address_Form.Por = GlobalStringConvert("Address_Form_Por");
			Address_Form.Hol = GlobalStringConvert("Address_Form_Hol");
			return;
		break;

		case "Beatriss":

			Address_Form.Spa = "Señorita";
			Address_Form.Fra = "Mademoiselle";
			Address_Form.Eng = "Miss";
			Address_Form.Por = "Senhorita";
			Address_Form.Hol = "Juffrouw";
			return;
		break;
	}
	trace("ERROR: Player Character is not defined - can't select address form");
	*/
}

// boal -->

string RandSwear()
{
	switch (rand(14))
	{
	case 0:
		return "¡Caramba! ";
		break;

	case 1:
		return "¡Maldita sea! ";
		break;

	case 2:
		return "¡Maldición! ";
		break;

	case 3:
		return "¡Mierda! ";
		break;

	case 4:
		return "No me jodas... ";
		break;

	case 5:
		return "¡Por los malditos tiburones! ";
		break;

	case 6:
		return "¡¡¡Argh!!! ";
		break;

	case 7:
		return "¡¡Qué demonios!! ";
		break;

	case 8:
		return "¡Alle hagel! "; // ñòàíäàðòíîå ïèðàòñêîå "òâîþ ìàòü"
		break;

	case 9:
		return "¡Maldito sea! ";
		break;

	case 10:
		return "¡Mierda! ";
		break;

	case 11:
		return "Maldito seas... ";
		break;

	case 12:
		return "¡Vete a la mierda! ";
		break;

	case 13:
		return "¡Maldita sea! ";
		break;

	case 14:
		return "¡Qué me aspen! ";
		break;
	}
}

// navy --> вынес простые восклицания,
// т.к. "О, Боже!!! Я вырежу тебе сердце" звучит мягко говоря странно :)
string RandExclamation()
{
	switch (rand(2))
	{
	case 0:
		return "¡Oh, Señor! ";
		break;

	case 1:
		return "¡Oh, Cielos! ";
		break;

	case 2:
		return "¡Santa Virgen! ";
		break;
	}
}
// navy <--
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                Выбор фраз для диалога
////////////////////////////////////////////////////////////////////////////////////////////////////////
// boal 13.03.2004 -->
string RandPhraseSimple(string Var1, string Var2)
{
	int RandP;
	RandP = Rand(1);
	switch (RandP)
	{
	case 0:
		return /*"First phrase selected" + */ Var1;
		break;

	case 1:
		return /*"Second phrase selected" + */ Var2;
		break;
	}
	return "ERROR";
}
// выбор фразы из трех
string LinkRandPhrase(string Var1, string Var2, string Var3)
{
	int RandP;
	RandP = Rand(2);
	switch (RandP)
	{
	case 0:

		return /*"First phrase selected" + */ Var1;

		break;

	case 1:

		return /*"Second phrase selected" + */ Var2;

		break;

	case 2:

		return /*"Third phrase selected" + */ Var3;

		break;
	}
	return "ERROR";
}

string NationKingsCrown(ref Character)
{
	switch (sti(Character.nation))
	{
	case ENGLAND:
		return "trono inglés";
		break;
	case FRANCE:
		return "corona francesa";
		break;
	case SPAIN:
		return "corona española";
		break;
	case HOLLAND:
		return "Reino de Holanda";
		break;
	case PIRATE:
		return "Hermanos de la Costa";
		break;
	}
}
string NationKingsName(ref NPChar)
{
	switch (sti(NPChar.nation))
	{
	case ENGLAND:
		return "Su Majestad Charles II de Inglaterra";
		break;
	case FRANCE:
		return "Su Majestad Louis XIV de Francia";
		break;
	case SPAIN:
		return "Su Católica Majestad Carlos II de España";
		break;
	case HOLLAND:
		return "Su Majestad William III de Holanda";
		break;
	case PIRATE:
		return "Los Hermanos de la Costa";
		break;
	}
}

string NationNameMan(int pNation)
{
	switch (pNation)
	{
	case ENGLAND:
		return "Inglés";
		break;
	case FRANCE:
		return "Francés";
		break;
	case SPAIN:
		return "Español";
		break;
	case HOLLAND:
		return "Holandés";
		break;
	case PIRATE:
		return "un pirata";
		break;
	}
}

string NationNameWoman(int pNation)
{
	switch (pNation)
	{
	case ENGLAND:
		return "Inglés";
		break;
	case FRANCE:
		return "Francés";
		break;
	case SPAIN:
		return "Español";
		break;
	case HOLLAND:
		return "Holandés";
		break;
	case PIRATE:
		return "un pirata";
		break;
	}
}
// boal 13.03.2004 <--
string NationNamePeople(int pNation)
{
	switch (pNation)
	{
	case ENGLAND:
		return "Ingleses";
		break;
	case FRANCE:
		return "Franceses";
		break;
	case SPAIN:
		return "Españoles";
		break;
	case HOLLAND:
		return "Holandeses";
		break;
	case PIRATE:
		return "piratas";
		break;
	}
}

string NationNamePeopleAcc(int pNation)
{
	switch (pNation)
	{
	case ENGLAND:
		return "Ingleses";
		break;
	case FRANCE:
		return "Franceses";
		break;
	case SPAIN:
		return "Españoles";
		break;
	case HOLLAND:
		return "Holandeses";
		break;
	case PIRATE:
		return "piratas";
		break;
	}
}

string NationNameAblative(int iNation) // творительный падеж
{
	switch (iNation)
	{
	case ENGLAND:
		return "Inglaterra";
		break;
	case FRANCE:
		return "Francia";
		break;
	case SPAIN:
		return "España";
		break;
	case HOLLAND:
		return "Holanda";
		break;
	case PIRATE:
		return "los piratas";
		break;
	}
}

string NationNameNominative(int iNation) // именительный падеж
{
	switch (iNation)
	{
	case ENGLAND:
		return "Inglaterra";
		break;
	case FRANCE:
		return "Francia";
		break;
	case SPAIN:
		return "España";
		break;
	case HOLLAND:
		return "Holanda";
		break;
	case PIRATE:
		return "Hermanos de la Costa";
		break;
	}
}

string NationNameGenitive(int iNation) // родительный падеж
{
	switch (iNation)
	{
	case ENGLAND:
		return "Inglaterra";
		break;
	case FRANCE:
		return "Francia";
		break;
	case SPAIN:
		return "España";
		break;
	case HOLLAND:
		return "Holanda";
		break;
	case PIRATE:
		return "los piratas";
		break;
	}
}

///////Часто будет использоваться поэтому заношу сюда
string NationEuropaTown(int iNation)
{
	switch (iNation)
	{
	case ENGLAND:
		return "London";
		break;
	case FRANCE:
		return "Le Roshele";
		break;
	case SPAIN:
		return "Sevilla";
		break;
	case PIRATE:
		return "Tortuga";
		break;
	case HOLLAND:
		return "Amsterdam";
		break;
	}
}

string TimeGreeting()
{
	if (GetHour() >= 18 && GetHour() < 23)
	{
		return "Buenas tardes";
	}
	if (GetHour() >= 6 && GetHour() < 12)
	{
		return "Buenos dias";
	}
	if (GetHour() >= 12 && GetHour() < 18)
	{
		return "Buena mañana";
	}
	if (GetHour() >= 23 || GetHour() < 6)
	{
		return "Buenas noches";
	}
	return "¡Hola!";
}

string Greeting(bool formal)
{
	if (GetHour() >= 6 && GetHour() < 12)
	{
		return "Buenos dias";
	}
	if (formal == true) return "Hola"; // polite
	else return "Hola"; // friendly
}

string Goodbye(bool formal)
{
	if (GetHour() >= 23 || GetHour() < 6)
	{
	   return "Buenas noches";
	}
	if (formal == true) return RandPhraseSimple("Adiós", "Hasta la vista"); // polite
	else return RandPhraseSimple("Adiós", "Adiós"); // friendly
}

// выбор фразы от репутации
string PCharRepPhrase(string bad, string good)
{
	if (makeint(pchar.reputation.nobility) < 41)
	{
		return bad;
	}
	else
	{
		return good;
	}
}
// boal для НПС
string NPCharRepPhrase(ref _pchar, string bad, string good)
{
	if (makeint(_pchar.reputation) < 41)
	{
		return bad;
	}
	else
	{
		return good;
	}
}

////////// поиск нужного перса для диалога
string GetCharIDByParam(string attrPresent1, string attr2, string val2)
{
	ref rCharacter; // ищем
	int n = GetCharIDXByParam(attrPresent1, attr2, val2);

	if (n > 0)
	{
		makeref(rCharacter, Characters[n]);
		return rCharacter.id;
	}
	return "";
}
int GetCharIDXByParam(string attrPresent1, string attr2, string val2)
{
	ref rCharacter; // ищем
	int n;

	for (n = 0; n < MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, attrPresent1))
		{
			if (rCharacter.(attr2) == val2)
				return n;
		}
	}
	return -1;
}
int GetCharIDXForTownAttack(string attrPresent1)
{
	ref rColony; // ищем
	int n;
	bool ok;

	for (n = 0; n < MAX_COLONIES; n++)
	{
		makeref(rColony, colonies[n]);
		ok = false;
		if (CheckAttribute(rColony, "Default.BoardLocation2") && rColony.Default.BoardLocation2 == attrPresent1)
		{
			ok = true;
		}
		if (rColony.Default.BoardLocation == attrPresent1 || ok)
		{
			if (rColony.HeroOwn == true)
			{
				return -1;
			}

			return GetFortCommanderIdx(rColony.id);
		}
	}
	return -1;
}
// обращение НПС к ГГ, зависит от нации НПС
string GetAddress_Form(ref NPChar)
{
	string attr = NationShortName(sti(NPChar.nation));
	return address_form.(attr);
}
// обращение ГГ к НПС, зависит от нации НПС и его пола
string GetAddress_FormToNPC(ref NPChar)
{
	string attr = NationShortName(sti(NPChar.nation));
	string attr2 = NPChar.sex;
	// проверка на скелетов
	if (attr2 != "woman")
	{
		attr2 = "man";
	}
	return address_form.(attr).(attr2);
}
string GetAddress_FormTitle(int nation, int num)
{
	string attr = NationShortName(nation);
	string attr2 = "Title" + num;
	string ret = XI_ConvertString("NoTitle");
	if (CheckAttribute(address_form, attr + "." + attr2))
	{
		ret = address_form.(attr).(attr2);
	}
	return ret;
}

// eddy. кто по профессии (только для типовых статиков, не фантомов). sPrefix - приставка для падежей: Gen, Dat..
string GetWorkTypeOfMan(ref NPChar, string sPrefix)
{
	string sCity, sTemp;
	sTemp = "desconocido";
	if (CheckAttribute(NPChar, "City"))
	{
		sCity = NPChar.City;
		sTemp = NPChar.id;
		sTemp = strcut(sTemp, strlen(sCity) + 1, strlen(sTemp) - 1);
	}
	return XI_ConvertString("Qué" + sTemp + sPrefix);
}

// Warship 07.08.09 -->
// Количество имен в группе
int GetNamesCount(String _nameType)
{
	aref typeNames;
	makearef(typeNames, Names.Pirates.(_nameType));

	return GetAttributesNum(typeNames);
}

// Случайное имя из определённой группы в определённом падеже
String GetRandName(String _nameType, String _case)
{
	String nameId;

	nameId = "l" + rand(GetNamesCount(_nameType) - 1);

	return GetName(_nameType, nameId, _case);
}

// Вернет имя из группы с указаным Id и в указанном падеже
String GetName(String _nameType, String _nameId, String _nameCase)
{
	return Names.Pirates.(_nameType).(_nameId).(_nameCase);
}

// Вернет указанное имя в другом падеже, поиск по именам группы _nameType
String ChangeNameCaseEx(String _nameType, String _name, String _fromCase, String _toCase)
{
	aref typeNames;
	String nameId;

	makearef(typeNames, Names.Pirates.(_nameType));

	for (int i = 0; i < GetAttributesNum(typeNames); i++)
	{
		nameId = "l" + i;

		if (GetName(_nameType, nameId, _fromCase) == _name)
		{
			return GetName(_nameType, nameId, _toCase);
		}
	}

	return "";
}

// Тоже самое, что и выше, только меньше параметров - ищет само
String ChangeNameCase(String _nameType, String _name, String _toCase)
{
	aref typeNames;
	String nameId;

	makearef(typeNames, Names.Pirates.(_nameType));

	for (int i = 0; i < GetAttributesNum(typeNames); i++)
	{
		nameId = "l" + i;

		if (GetName(_nameType, nameId, NAME_NOM) == _name || GetName(_nameType, nameId, NAME_GEN) || GetName(_nameType, nameId, NAME_DAT) ||
			GetName(_nameType, nameId, NAME_ACC) == _name || GetName(_nameType, nameId, NAME_ABL) || GetName(_nameType, nameId, NAME_VOC))
		{
			return GetName(_nameType, nameId, _toCase);
		}
	}

	return "";
}
// <-- Warship 07.08.09
string GetIndianName(int Sex) // Jason имена индейцев
{
	string nameid;

	if (Sex == MAN)
		nameid = "l" + rand(99);
	else
		nameid = "l" + (100 + rand(68));

	return Names.Indian.(nameId);
}

string GetTitle(ref NPChar, bool address) //Титул ГГ
{
	string Title, Nation;
	
	if (PChar.sex == "man")
	{
		if (address == true)
		{
			Nation = GetAddress_Form(NPChar);
		}
		
		Title = "capitán";
	}
	if (PChar.sex == "woman")
	{
		Title = GetAddress_Form(NPChar);
	}
	
	if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) Title = "Generalgouverneur";
	if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4) Title = "Vizeadmiral";

	if (address == true && PChar.sex == "man") return Nation + " " + Title;
	else return Title;
}

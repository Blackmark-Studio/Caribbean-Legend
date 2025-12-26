#include "scripts\utils.c"

// boal -->
#define CARDS_RULE  "Zasady są proste. Blackjack. 36 kart - od szóstek do asów. As to 11 punktów, król - 4, lord (jeździec) - 3, nobil (piechur) - 2, reszta ma wartość zgodną z oznaczeniem. Celem jest uzyskanie 21 punktów.\nKliknij talię, by dobrać kartę. Każda karta to jedna stawka. Kliknij portret w prawym górnym rogu, by zakończyć turę. Aby grać, musisz mieć środki na co najmniej trzy stawki. Wciśnij Esc lub krzyżyk, by wyjść."
#define DICE_RULE   "Gra w kości. Po pięć rzutów dla każdego gracza. Możesz przerzucić wszystkie lub dowolne z nich, ale tylko raz. Każda kość to jedna stawka. Celem jest uzyskanie jak najlepszego układu.\nKombinacje: para (2), dwie pary (2+2), trójka (3), full (3+2), czwórka (4), strit (kolejne wartości) i poker (5).\nKliknij kubek, by rzucić. Kliknij daną kość, by ją przerzucić. Kliknij portret, by zakończyć turę (jeśli nie chcesz lub nie możesz już przerzucać)."
#define MAX_TITLENEXTRATE   13 // счетчик для званий
#define MAX_TITLE           5
// boal <--

object Address_Form;

void Set_inDialog_Attributes()
{ 
	ref The_Character_is;

	The_Character_is = GetMainCharacter();
    if (!CheckAttribute(The_Character_is, "sex") || The_Character_is.sex == "man")
	{
		Address_Form.Spa = "senor";
		Address_Form.Fra = "monsieur";
		Address_Form.Eng = "sir";
		Address_Form.Hol = "mynheer";
		Address_Form.Pir = "sir";
    }
    else
    {
		Address_Form.Spa = "senorita";
		Address_Form.Fra = "mademoiselle";
		Address_Form.Eng = "miss";
		Address_Form.Hol = "mevrouw";
		Address_Form.Pir = "miss";
	}
	Address_Form.Spa.Title1 = "Korsarz";
	Address_Form.Fra.Title1 = "Flibustier";
	Address_Form.Eng.Title1 = "Kaper";
	Address_Form.Hol.Title1 = "Wolny strzelec";
	Address_Form.Pir.Title1 = "Pirat";

    Address_Form.Spa.Title2 = "Comandante";
	Address_Form.Fra.Title2 = "Dowódca";
	Address_Form.Eng.Title2 = "Dowódca";
	Address_Form.Hol.Title2 = "Dowódca";
	Address_Form.Pir.Title2 = "Dowódca";
	
	Address_Form.Spa.Title3 = "Capitán";
	Address_Form.Fra.Title3 = "Kapitan";
	Address_Form.Eng.Title3 = "Kapitan";
	Address_Form.Hol.Title3 = "Kapitan";
	Address_Form.Pir.Title3 = "Kapitan";

	Address_Form.Spa.Title4 = "Komodor";
	Address_Form.Fra.Title4 = "Komodor";
	Address_Form.Eng.Title4 = "Komodor";
	Address_Form.Hol.Title4 = "Komodor";
	Address_Form.Pir.Title4 = "Watażka";

	Address_Form.Spa.Title5 = "Admirał";
	Address_Form.Fra.Title5 = "Admirał";
	Address_Form.Eng.Title5 = "Admirał";
	Address_Form.Hol.Title5 = "Admirał";
	Address_Form.Pir.Title5 = "Lord";

	Address_Form.Spa.woman = "senora";
	Address_Form.Fra.woman = "madame";
	Address_Form.Eng.woman = "missis";
	Address_Form.Hol.woman = "mevrouw";
	Address_Form.Pir.woman = "missis";

	Address_Form.Spa.man = "senor";
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

			Address_Form.Spa = "Senorita";
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
			return "O w mordę!";
		break;

		case 1:
			return "Do diabła! ";
		break;

		case 2:
			return "Cholera! ";
		break;

		case 3:
			return "Szlag by to! ";
		break;

		case 4:
			return "O kurwa... ";
		break;

		case 5:
			return "O ja pierdolę! ";
		break;

		case 6:
			return "Argh!!! ";
		break;

		case 7:
			return "Co u licha! ";
		break;	 
		
		case 8:
			return "Bóbr kurwa! ";	// стандартное пиратское "твою мать"
		break;
		
		case 9:
			return "Do stu piorunów! ";
		break;

		case 10:
			return "Niech mnie prądy porwią! ";
		break;
		
		case 11:
			return "Osz, kurwa mać...! ";
		break;
		
		case 12:
			return "Zaraza! ";
		break;
		
		case 13:
			return "A żeby to! ";
		break;
		
		case 14:
			return "Do kurwy nędzy! ";
		break;
	}
}

//navy --> вынес простые восклицания,
//т.к. "О, Боже!!! Я вырежу тебе сердце" звучит мягко говоря странно :)
string RandExclamation()
{
	switch(rand(2))
	{
		case 0:
			return "O, Panie! ";
		break;

		case 1:
			return "Na niebiosa! ";
		break;

		case 2:
			return "Matko Boska! ";
		break;
	}
}
//navy <--
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                Выбор фраз для диалога
////////////////////////////////////////////////////////////////////////////////////////////////////////
// boal 13.03.2004 -->
string RandPhraseSimple(string Var1, string Var2)
{
	int RandP;
	RandP = Rand(1);
	switch(RandP)
	{
		case 0:
			return /*"First phrase selected" + */ Var1;
		break;

		case 1:
			return /*"Second phrase selected" + */Var2;
		break;
	}
	return "ERROR";
}
// выбор фразы из трех
string LinkRandPhrase (string Var1, string Var2, string Var3)
{
	int RandP;
	RandP = Rand(2);
	switch(RandP)
	{
		case 0:

			return /*"First phrase selected" + */ Var1;

		break;

		case 1:

			return /*"Second phrase selected" + */Var2;

		break;

		case 2:

			return /*"Third phrase selected" + */Var3;

		break;
	}
	return "ERROR";
}

string NationKingsCrown(ref Character)
{
    switch(sti(Character.nation))
	{
		case ENGLAND:
            return "Protektorat Anglii, Szkocji i Irlandii";
		break;
		case FRANCE:
            return "Najjaśniejsza Korona Francji";
		break;
		case SPAIN:
            return "Hiszpańska Korona Katolicka";
		break;
		case HOLLAND:
			return "Zjednoczone Prowincje";
		break;
		case PIRATE:
			return "Bractwo Wybrzeża";
		break;
	}
}
string NationKingsName(ref NPChar)
{
    switch(sti(NPChar.nation))
	{
		case ENGLAND:
            return "Lorda Protektora Olivera Cromwella";
		break;
		case FRANCE:
            return "Jego Królewskiej Wysokości Ludwika XIV, Króla Francji i Nawarry";
		break;
		case SPAIN:
            return "Jego Katolickiej Mości Filipa IV Habsburga, Króla Hiszpanii i Indii";
		break;
		case HOLLAND:
			return "Stanu Generalnego Zjednoczonych Prowincji Niderlandzkich";
		break;
		case PIRATE:
			return "Bractwa Wybrzeża";
		break;
	}
}

string NationNameMan(int pNation)
{
    switch(pNation)
	{
		case ENGLAND:
            return "anglik";
		break;
		case FRANCE:
            return "francuz";
		break;
		case SPAIN:
            return "hiszpan";
		break;
		case HOLLAND:
			return "holender";
		break;
		case PIRATE:
			return "pirat";
		break;
	}
}

string NationNameWoman(int pNation)
{
    switch(pNation)
	{
		case ENGLAND:
			return "angielka";
		break;
		case FRANCE:
			return "francuzka";
		break;
		case SPAIN:
			return "hiszpanka";
		break;
		case HOLLAND:
			return "holenderka";
		break;
		case PIRATE:
			return "piratka";
		break;
	}
}
// boal 13.03.2004 <--
string NationNamePeople(int pNation)
{
    switch(pNation)
	{
		case ENGLAND:
            return "anglicy";
		break;
		case FRANCE:
            return "francuzi";
		break;
		case SPAIN:
            return "hiszpanie";
		break;
		case HOLLAND:
			return "holendrzy";
		break;
		case PIRATE:
			return "piraci";
		break;
	}
}

string NationNamePeopleAcc(int pNation)
{
    switch(pNation)
	{
        case ENGLAND:
            return "anglików";
        break;
        case FRANCE:
            return "francuzów";
        break;
        case SPAIN:
            return "hiszpanów";
        break;
        case HOLLAND:
            return "holendrów";
        break;
        case PIRATE:
            return "piratów";
        break;
	}
}

string NationNameAblative(int iNation) //творительный падеж
{
    switch(iNation)
	{
        case ENGLAND:
            return "Anglikami";
        break;
        case FRANCE:
            return "Francuzami";
        break;
        case SPAIN:
            return "Hiszpanami";
        break;
        case HOLLAND:
            return "Holendrami";
        break;
        case PIRATE:
            return "piratami";
        break;
	}
}

string NationNameNominative(int iNation) //именительный падеж
{
    switch(iNation)
	{
        case ENGLAND:
            return "Anglia";
        break;
        case FRANCE:
            return "Francja";
        break;
        case SPAIN:
            return "Hiszpania";
        break;
        case HOLLAND:
            return "Holandia";
        break;
        case PIRATE:
            return "Bractwo Wybrzeża";
        break;
	}
}

string NationNameGenitive(int iNation) // родительный падеж
{
    switch(iNation)
	{
        case ENGLAND:
            return "Anglii";
        break;
        case FRANCE:
            return "Francji";
        break;
        case SPAIN:
            return "Hiszpanii";
        break;
        case HOLLAND:
            return "Holandii";
        break;
        case PIRATE:
            return "piratów";
        break;
	}
}

///////Часто будет использоваться поэтому заношу сюда
string NationEuropaTown(int iNation)
{
    switch(iNation)
	{
        case ENGLAND:
            return "Londyn";
        break;
        case FRANCE:
            return "La Rochelle";
        break;
        case SPAIN:
            return "Sewilla";
        break;
        case HOLLAND:
            return "Amsterdam";
        break;
        case PIRATE:
            return "Tortuga";
        break;
	}
}

string TimeGreeting()
{
    if (GetHour() >= 18 && GetHour() < 23)
    {
       return "Dobry wieczór";
    }
	if (GetHour() >= 6 && GetHour() < 12)
	{
       return "Dzień dobry";
    }
    if (GetHour() >= 12 && GetHour() < 18)
    {
       return "Dzień dobry";
    }
    if (GetHour() >= 23 || GetHour() < 6)
    {
       return "Dobry wieczór";
    }
    return "Hallo!";
}

string Greeting(bool formal)
{
	if (GetHour() >= 6 && GetHour() < 12)
	{
       return "Dzień dobry";
    }
	if (formal == true) return "Witajcie"; // polite
	else return "Witam"; // friendly
}

string Goodbye(bool formal)
{
    if (GetHour() >= 23 || GetHour() < 6)
    {
       return "Dobranoc";
    }
	if (formal == true) return RandPhraseSimple("Żegnaj", "Do zobaczenia"); // polite
	else return RandPhraseSimple("Pa", "Pa"); // friendly
}

// выбор фразы от репутации
string PCharRepPhrase (string bad, string good)
{
	if(makeint(pchar.reputation.nobility) < 41)
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
	if(makeint(_pchar.reputation) < 41)
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
    ref rCharacter; //ищем
	int n = GetCharIDXByParam(attrPresent1, attr2, val2);

    if (n > 0)
    {
        makeref(rCharacter,Characters[n]);
        return  rCharacter.id;
    }
    return  "";
}
int GetCharIDXByParam(string attrPresent1, string attr2, string val2)
{
    ref rCharacter; //ищем
	int n;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter,Characters[n]);
		if (CheckAttribute(rCharacter, attrPresent1))
		{
            if (rCharacter.(attr2) == val2)
                return  n;
		}
    }
    return  -1;
}
int GetCharIDXForTownAttack(string attrPresent1)
{
    ref   rColony; //ищем
	int   n;
	bool  ok;

	for (n=0; n<MAX_COLONIES; n++)
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
			    return  -1;
			}
			
			return GetFortCommanderIdx(rColony.id);
		}
    }
    return  -1;
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
    string attr  = NationShortName(sti(NPChar.nation));
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
    string attr  =  NationShortName(nation);
    string attr2 =  "Title" + num;
    string ret   =  XI_ConvertString("NoTitle");
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
	sTemp = "unknown";
	if (CheckAttribute(NPChar, "City")) 
	{
		sCity = NPChar.City;
		sTemp = NPChar.id;
		sTemp = strcut(sTemp, strlen(sCity)+1, strlen(sTemp)-1);
	}
	return XI_ConvertString("Who" + sTemp + sPrefix);
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
	
	for(int i = 0; i < GetAttributesNum(typeNames); i++)
	{
		nameId = "l" + i;
		
		if(GetName(_nameType, nameId, _fromCase) == _name)
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
	
	for(int i = 0; i < GetAttributesNum(typeNames); i++)
	{
		nameId = "l" + i;
		
		if(GetName(_nameType, nameId, NAME_NOM) == _name || GetName(_nameType, nameId, NAME_GEN) || GetName(_nameType, nameId, NAME_DAT) ||
			GetName(_nameType, nameId, NAME_ACC) == _name || GetName(_nameType, nameId, NAME_ABL) || GetName(_nameType, nameId, NAME_VOC))
		{
			return GetName(_nameType, nameId, _toCase);
		}
	}
	
	return "";
}
// <-- Warship 07.08.09
string GetIndianName(int Sex) //Jason имена индейцев
{
	string nameid;
	
	if (Sex == MAN) nameid = "l" + rand(99);
	else nameid = "l" + (100+rand(68));

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
		
		Title = "kapitan";
	}
	if (PChar.sex == "woman")
	{
		Title = GetAddress_Form(NPChar);
	}
	
	if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) Title = "gubernator generalny";
	if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4) Title = "wiceadmirał";

	if (address == true && PChar.sex == "man") return Nation + " " + Title;
	else return Title;
}

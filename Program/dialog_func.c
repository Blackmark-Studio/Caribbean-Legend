#include "scripts\utils.c"

#define MAX_TITLENEXTRATE   13 // счетчик для званий
#define MAX_TITLE           5

object Address_Form;
object obPhrases;

void Set_inDialog_Attributes()
{
    if (!CheckAttribute(PChar, "sex") || PChar.sex == "man")
	{
		Address_Form.Spa = GlobalStringConvert("Address_Form_Spa");
		Address_Form.Fra = GlobalStringConvert("Address_Form_Fra");
		Address_Form.Eng = GlobalStringConvert("Address_Form_Eng");
		Address_Form.Hol = GlobalStringConvert("Address_Form_Hol");
		Address_Form.Pir = GlobalStringConvert("Address_Form_Pir");
    }
    else
    {
		Address_Form.Spa = GlobalStringConvert("Address_Form_SpaWoman");
		Address_Form.Fra = GlobalStringConvert("Address_Form_FraWoman");
		Address_Form.Eng = GlobalStringConvert("Address_Form_EngWoman");
		Address_Form.Hol = GlobalStringConvert("Address_Form_HolWoman");
		Address_Form.Pir = GlobalStringConvert("Address_Form_PirWoman");
	}

	Address_Form.Spa.man = GlobalStringConvert("Address_Form_Spa");
	Address_Form.Fra.man = GlobalStringConvert("Address_Form_Fra");
	Address_Form.Eng.man = GlobalStringConvert("Address_Form_Eng");
	Address_Form.Hol.man = GlobalStringConvert("Address_Form_Hol");
	Address_Form.Pir.man = GlobalStringConvert("Address_Form_Pir");

	Address_Form.Spa.woman = GlobalStringConvert("Address_Form_SpaWoman2");
	Address_Form.Fra.woman = GlobalStringConvert("Address_Form_FraWoman2");
	Address_Form.Eng.woman = GlobalStringConvert("Address_Form_EngWoman2");
	Address_Form.Hol.woman = GlobalStringConvert("Address_Form_HolWoman2");
	Address_Form.Pir.woman = GlobalStringConvert("Address_Form_PirWoman2");

	Address_Form.Spa.Title1 = GlobalStringConvert("Address_Form_Spa_Title1");
	Address_Form.Fra.Title1 = GlobalStringConvert("Address_Form_Fra_Title1");
	Address_Form.Eng.Title1 = GlobalStringConvert("Address_Form_Eng_Title1");
	Address_Form.Hol.Title1 = GlobalStringConvert("Address_Form_Hol_Title1");
	Address_Form.Pir.Title1 = GlobalStringConvert("Address_Form_Pir_Title1");

    Address_Form.Spa.Title2 = GlobalStringConvert("Address_Form_Spa_Title2");
	Address_Form.Fra.Title2 = GlobalStringConvert("Address_Form_Fra_Title2");
	Address_Form.Eng.Title2 = GlobalStringConvert("Address_Form_Eng_Title2");
	Address_Form.Hol.Title2 = GlobalStringConvert("Address_Form_Hol_Title2");
	Address_Form.Pir.Title2 = GlobalStringConvert("Address_Form_Pir_Title2");

	Address_Form.Spa.Title3 = GlobalStringConvert("Address_Form_Spa_Title3");
	Address_Form.Fra.Title3 = GlobalStringConvert("Address_Form_Fra_Title3");
	Address_Form.Eng.Title3 = GlobalStringConvert("Address_Form_Eng_Title3");
	Address_Form.Hol.Title3 = GlobalStringConvert("Address_Form_Hol_Title3");
	Address_Form.Pir.Title3 = GlobalStringConvert("Address_Form_Pir_Title3");

	Address_Form.Spa.Title4 = GlobalStringConvert("Address_Form_Spa_Title4");
	Address_Form.Fra.Title4 = GlobalStringConvert("Address_Form_Fra_Title4");
	Address_Form.Eng.Title4 = GlobalStringConvert("Address_Form_Eng_Title4");
	Address_Form.Hol.Title4 = GlobalStringConvert("Address_Form_Hol_Title4");
	Address_Form.Pir.Title4 = GlobalStringConvert("Address_Form_Pir_Title4");

	Address_Form.Spa.Title5 = GlobalStringConvert("Address_Form_Spa_Title5");
	Address_Form.Fra.Title5 = GlobalStringConvert("Address_Form_Fra_Title5");
	Address_Form.Eng.Title5 = GlobalStringConvert("Address_Form_Eng_Title5");
	Address_Form.Hol.Title5 = GlobalStringConvert("Address_Form_Hol_Title5");
	Address_Form.Pir.Title5 = GlobalStringConvert("Address_Form_Pir_Title5");

    int i;
    string attr;

    // RandSwear
    for(i = 1; i <= 15; i++)
    {
        attr = "Swear_" + i;
        obPhrases.Swears.(attr) = GlobalStringConvert("Swear_" + i) + " ";
    }

    // RandExclamation
    for(i = 1; i <= 3; i++)
    {
        attr = "Exclamation_" + i;
        obPhrases.Exclamations.(attr) = GlobalStringConvert("Exclamation_" + i) + " ";
    }
}

string RandSwear()
{
    return GetRandomAttrValue(&obPhrases.Swears);
}

string RandExclamation()
{
    return GetRandomAttrValue(&obPhrases.Exclamations);
}

string RandPhraseSimple(string Var1, string Var2)
{
	switch(rand(1))
	{
		case 0: return Var1; break;
		case 1: return Var2; break;
	}
}

string LinkRandPhrase(string Var1, string Var2, string Var3)
{
	switch(rand(2))
	{
		case 0: return Var1; break;
		case 1: return Var2; break;
		case 2: return Var3; break;
	}
}

string RandPhrase(...)
{
   return string(GetArg(rand(GetArgCount() - 1)));
}

string NationKingsCrown(ref Character)
{
    return GlobalStringConvert("NationKingsCrown_" + NationShortName(int(Character.nation)));
}

string NationKingsName(ref NPChar)
{
    return GlobalStringConvert("NationKingsName_" + NationShortName(int(NPChar.nation)));
}

string NationNameMan(int iNation)
{
    return GlobalStringConvert("NationNameMan_" + NationShortName(iNation));
}

string NationNameWoman(int iNation)
{
    return GlobalStringConvert("NationNameWoman_" + NationShortName(iNation));
}

string NationNamePeople(int iNation)
{
    return GlobalStringConvert("NationNamePeople_" + NationShortName(iNation));
}

string NationNamePeopleAcc(int iNation)
{
    return GlobalStringConvert("NationNamePeopleAcc_" + NationShortName(iNation));
}

string NationNameNominative(int iNation)
{
    return GlobalStringConvert("NationNameNominative_" + NationShortName(iNation));
}

string NationNameAblative(int iNation)
{
    return GlobalStringConvert("NationNameAblative_" + NationShortName(iNation));
}

string NationNameGenitive(int iNation)
{
    return GlobalStringConvert("NationNameGenitive_" + NationShortName(iNation));
}

string NationEuropaTown(int iNation)
{
    return GlobalStringConvert("NationEuropaTown_" + NationShortName(iNation));
}

string TimeGreeting()
{
    if (GetHour() >= 23 || GetHour() < 6)  return GlobalStringConvert("NightGreeting");
    if (GetHour() >= 6  && GetHour() < 12) return GlobalStringConvert("MorningGreeting");
    if (GetHour() >= 12 && GetHour() < 18) return GlobalStringConvert("DayGreeting");
    return GlobalStringConvert("EveningGreeting");
}

string Greeting(bool formal)
{
	if (GetHour() >= 6 && GetHour() < 12) return GlobalStringConvert("MorningGreeting");
	if (formal) return GlobalStringConvert("PoliteGreeting");
	return GlobalStringConvert("FriendlyGreeting");
}

string Goodbye(bool formal)
{
	if (GetHour() >= 23 || GetHour() < 6) return GlobalStringConvert("NightGreeting");
	if (formal) return GlobalStringConvert("PoliteGoodbye_" + rand(1));
	return GlobalStringConvert("FriendlyGoodbye_" + rand(1));
}

string PCharRepPhrase(string bad, string good)
{
    return int(PChar.reputation.nobility) < 41 ? bad : good;
}

string NPCharRepPhrase(ref chr, string bad, string good)
{
    return int(chr.reputation) < 41 ? bad : good;
}

// TO_DO: DEL
string GetCharIDByParam(string attrPresent1, string attr2, string val2)
{
	int n = GetCharIDXByParam(attrPresent1, attr2, val2);
    return n > 0 ? Characters[n].id : "";
}

// TO_DO: DEL
int GetCharIDXByParam(string attrPresent1, string attr2, string val2)
{
	for(int i = 0; i < MAX_CHARACTERS; i++)
	{
		if (CheckAttribute(&Characters[i], attrPresent1) && Characters[i].(attr2) == val2)
        {
            return i;
        }
    }
    return -1;
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
    string attr = NationShortName(int(NPChar.nation));
    return address_form.(attr);
}

// обращение ГГ к НПС, зависит от нации НПС и его пола
string GetAddress_FormToNPC(ref NPChar)
{
    string attr  = NationShortName(int(NPChar.nation));
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
// to_do: доинитить статиков
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

// Количество имен в группе
int GetNamesCount(string _nameType)
{
	aref typeNames;
	makearef(typeNames, Names.Pirates.(_nameType));
	return GetAttributesNum(typeNames);
}

// Случайное имя из определённой группы в определённом падеже
string GetRandName(string _nameType, string _case)
{
	string nameId = "l" + rand(GetNamesCount(_nameType) - 1);
	return GetName(_nameType, nameId, _case);
}

// Вернет имя из группы с указаным Id и в указанном падеже
string GetName(string _nameType, string _nameId, string _nameCase)
{
	return Names.Pirates.(_nameType).(_nameId).(_nameCase);
}

// Вернет указанное имя в другом падеже, поиск по именам группы _nameType
string ChangeNameCaseEx(string _nameType, string _name, string _fromCase, string _toCase)
{
	aref typeNames;
	string nameId;

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
string ChangeNameCase(string _nameType, string _name, string _toCase)
{
	aref typeNames;
	string nameId;

	makearef(typeNames, Names.Pirates.(_nameType));

	for(int i = 0; i < GetAttributesNum(typeNames); i++)
	{
		nameId = "l" + i;

		if (GetName(_nameType, nameId, NAME_NOM) == _name ||
            GetName(_nameType, nameId, NAME_GEN) == _name ||
            GetName(_nameType, nameId, NAME_DAT) == _name ||
            GetName(_nameType, nameId, NAME_ACC) == _name ||
            GetName(_nameType, nameId, NAME_ABL) == _name ||
            GetName(_nameType, nameId, NAME_VOC) == _name)
		{
			return GetName(_nameType, nameId, _toCase);
		}
	}

	return "";
}

// Jason имена индейцев
string GetIndianName(int iSex)
{
	string nameid = (iSex == MAN) ? "l" + rand(99) : "l" + (100+rand(68));
	return Names.Indian.(nameId);
}

// Титул ГГ ~!~
string GetTitle(ref NPChar, bool address)
{
	string Title;

    if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4)
        Title = GlobalStringConvert("Title_ViceAdmiral");
	else if (CheckAttribute(PChar, "questTemp.Patria.GenGovernor"))
        Title = GlobalStringConvert("Title_Ghovernor");
    else if (PChar.sex == "man")
        Title = GlobalStringConvert("Title_Captain");
    else
        Title = GetAddress_Form(NPChar);

	if (address && PChar.sex == "man")
        return GetAddress_Form(NPChar) + " " + Title;

	return Title;
}

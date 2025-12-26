#include "scripts\utils.c"

// boal -->
#define CARDS_RULE  "规则很简单。 二十一点。 36张牌, 从六点到A。 A算11点, K算4点, 骑士 (马骑士) 算3点, 步兵 (步兵) 算2点, 其余牌的点数与牌面相同。 你的目标是得到21点\n点击牌堆再拿一张牌。 每张牌都是赌注。 点击右上角的肖像完成你的回合。 如果你想玩, 需要至少有三个赌注的钱。 如果完成了, 按esc或叉号。 "
#define DICE_RULE   "掷骰子。 每个玩家五个。 你可以全部掷出或只掷其中几个, 但只能掷一次。 每个骰子都是赌注。 你的目标是获得最高分。 \n组合如下: 对子 (2) , 两对 (2+2) , 三张 (3) , 葫芦 (3+2) , 四张 (4) , 顺子 (连续的骰子) 和同花顺 (5) 。 \n点击杯子掷骰子, 点击某个骰子重掷该骰子, 点击肖像完成你的回合 (如果你不需要重掷或没有足够的钱重掷) 。 "
#define MAX_TITLENEXTRATE   13 // счeтчик для званий
#define MAX_TITLE           5
// boal <--

object Address_Form;

void Set_inDialog_Attributes()
{ 
	ref The_Character_is;

	The_Character_is = GetMainCharacter();
    if (!CheckAttribute(The_Character_is, "sex") || The_Character_is.sex == "man")
	{
		Address_Form.Spa = "先生";
		Address_Form.Fra = "先生";
		Address_Form.Eng = "先生";
		Address_Form.Hol = "先生";
		Address_Form.Pir = "先生";
    }
    else
    {
		Address_Form.Spa = "小姐";
		Address_Form.Fra = "小姐";
		Address_Form.Eng = "小姐";
		Address_Form.Hol = "夫人";
		Address_Form.Pir = "小姐";
	}
	Address_Form.Spa.Title1 = "私掠船船长";
	Address_Form.Fra.Title1 = "私掠者";
	Address_Form.Eng.Title1 = "投机者";
	Address_Form.Hol.Title1 = "海盗";
	Address_Form.Pir.Title1 = "海盗";

    Address_Form.Spa.Title2 = "指挥官";
	Address_Form.Fra.Title2 = "指挥官";
	Address_Form.Eng.Title2 = "指挥官";
	Address_Form.Hol.Title2 = "指挥官";
	Address_Form.Pir.Title2 = "指挥官";
	
	Address_Form.Spa.Title3 = "船长";
	Address_Form.Fra.Title3 = "船长";
	Address_Form.Eng.Title3 = "船长";
	Address_Form.Hol.Title3 = "船长";
	Address_Form.Pir.Title3 = "船长";

	Address_Form.Spa.Title4 = "准将";
	Address_Form.Fra.Title4 = "准将";
	Address_Form.Eng.Title4 = "准将";
	Address_Form.Hol.Title4 = "准将";
	Address_Form.Pir.Title4 = "准将";

	Address_Form.Spa.Title5 = "舰队司令";
	Address_Form.Fra.Title5 = "舰队司令";
	Address_Form.Eng.Title5 = "舰队司令";
	Address_Form.Hol.Title5 = "舰队司令";
	Address_Form.Pir.Title5 = "舰队司令";

	Address_Form.Spa.woman = "夫人";
	Address_Form.Fra.woman = "夫人";
	Address_Form.Eng.woman = "夫人";
	Address_Form.Hol.woman = "夫人";
	Address_Form.Pir.woman = "夫人";

	Address_Form.Spa.man = "先生";
	Address_Form.Fra.man = "先生";
	Address_Form.Eng.man = "先生";
	Address_Form.Hol.man = "先生";
	Address_Form.Pir.man = "先生";
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

			Address_Form.Spa = "小姐";
			Address_Form.Fra = "小姐";
			Address_Form.Eng = "小姐";
			Address_Form.Por = "小姐";
			Address_Form.Hol = "小姐";
			return;
		break;
	}
	trace("ERROR: 玩家角色未定义 - 无法选择称呼形式");
	*/
}

// boal -->

string RandSwear()
{
	switch (rand(14))
	{
		case 0:
			return "哎呀! ";
		break;

		case 1:
			return "该死的! ";
		break;

		case 2:
			return "该死! ";
		break;

		case 3:
			return "废话! ";
		break;

		case 4:
			return "靠... ";
		break;

		case 5:
			return "看在血腥鲨鱼的份上! ";
		break;

		case 6:
			return "啊!!! ";
		break;

		case 7:
			return "搞什么鬼!! ";
		break;	 
		
		case 8:
			return "见鬼! ";	// 标准海盗语 "去你的"
		break;
		
		case 9:
			return "该死的我! ";
		break;

		case 10:
			return "该死! ";
		break;
		
		case 11:
			return "该死... ";
		break;
		
		case 12:
			return "去你的! ";
		break;
		
		case 13:
			return "该死的我! ";
		break;
		
		case 14:
			return "见鬼! ";
		break;
	}
}

//navy --> вынeс простыe восклицания,
//т.к。 "О, Божe!!! Я вырeжу тeбe сeрдцe" звучит мягко говоря странно :)
string RandExclamation()
{
	switch(rand(2))
	{
		case 0:
			return "哦, 主啊! ";
		break;

		case 1:
			return "哦, 天啊! ";
		break;

		case 2:
			return "圣母玛利亚! ";
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
// выбор фразы из трeх
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
            return "英国王位";
        break;
        case FRANCE:
            return "法国王冠";
        break;
        case SPAIN:
            return "西班牙王冠";
        break;
        case HOLLAND:
            return "荷兰王国";
        break;
        case PIRATE:
            return "海岸兄弟会";
        break;
    }
}
string NationKingsName(ref NPChar)
{
    switch(sti(NPChar.nation))
    {
        case ENGLAND:
            return "护国公";
        break;
        case FRANCE:
            return "法国国王路易十四陛下";
        break;
        case SPAIN:
            return "天主教国王菲利普四世·冯·哈布斯堡陛下";
        break;
        case HOLLAND:
            return "荷兰国王威廉三世陛下";
        break;
        case PIRATE:
            return "海岸兄弟会";
        break;
    }
}

string NationNameMan(int pNation)
{
    switch(pNation)
    {
        case ENGLAND:
            return "英格兰人";
        break;
        case FRANCE:
            return "法国人";
        break;
        case SPAIN:
            return "西班牙人";
        break;
        case HOLLAND:
            return "荷兰人";
        break;
        case PIRATE:
            return "一名海盗";
        break;
    }
}

string NationNameWoman(int pNation)
{
    switch(pNation)
    {
		case ENGLAND:
			return "英国女人";
		break;
		case FRANCE:
			return "法国女人";
		break;
		case SPAIN:
			return "西班牙人";
		break;
		case HOLLAND:
			return "荷兰女";
		break;
		case PIRATE:
			return "海盗";
		break;
	}
}
// boal 13.03.2004 <--
string NationNamePeople(int pNation)
{
    switch(pNation)
    {
        case ENGLAND:
            return "英格兰人";
        break;
        case FRANCE:
            return "法国人";
        break;
        case SPAIN:
            return "西班牙人";
        break;
        case HOLLAND:
            return "荷兰人";
        break;
        case PIRATE:
            return "海盗";
        break;
    }
}

string NationNamePeopleAcc(int pNation)
{
    switch(pNation)
    {
        case ENGLAND:
            return "英格兰人";
        break;
        case FRANCE:
            return "法国人";
        break;
        case SPAIN:
            return "西班牙人";
        break;
        case HOLLAND:
            return "荷兰人";
        break;
        case PIRATE:
            return "海盗";
        break;
    }
}

string NationNameAblative(int iNation) // 夺格
{
    switch(iNation)
    {
        case ENGLAND:
            return "英格兰";
        break;
        case FRANCE:
            return "法国";
        break;
        case SPAIN:
            return "西班牙";
        break;
        case HOLLAND:
            return "荷兰";
        break;
        case PIRATE:
            return "由海盗";
        break;
    }
}

string NationNameNominative(int iNation) // 主格
{
    switch(iNation)
    {
        case ENGLAND:
            return "英格兰";
        break;
        case FRANCE:
            return "法国";
        break;
        case SPAIN:
            return "西班牙";
        break;
        case HOLLAND:
            return "荷兰";
        break;
        case PIRATE:
            return "海岸兄弟会";
        break;
    }
}

string NationNameGenitive(int iNation) // 属格
{
    switch(iNation)
    {
        case ENGLAND:
            return "英格兰";
        break;
        case FRANCE:
            return "法国";
        break;
        case SPAIN:
            return "西班牙";
        break;
        case HOLLAND:
            return "荷兰";
        break;
        case PIRATE:
            return "海盗";
        break;
    }
}

/////// 经常会用到, 所以放在这里
string NationEuropaTown(int iNation)
{
    switch(iNation)
    {
        case ENGLAND:
            return "伦敦";
        break;
        case FRANCE:
            return "勒罗谢尔";
        break;
        case SPAIN:
            return "塞维利亚";
        break;
        case PIRATE:
            return "托尔图加";
        break;
        case HOLLAND:
            return "阿姆斯特丹";
        break;
    }
}

string TimeGreeting()
{
    if (GetHour() >= 18 && GetHour() < 23)
    {
       return "晚上好";
    }
    if (GetHour() >= 6 && GetHour() < 12)
    {
       return "早上好";
    }
    if (GetHour() >= 12 && GetHour() < 18)
    {
       return "日安";
    }
    if (GetHour() >= 23 || GetHour() < 6)
    {
       return "晚安";
    }
    return "你好! ";
}

string Greeting(bool formal)
{
	if (GetHour() >= 6 && GetHour() < 12)
    {
       return "早上好";
    }
	if (formal == true) return "你好"; // polite
	else return "嗨"; // friendly
}

string Goodbye(bool formal)
{
    if (GetHour() >= 23 || GetHour() < 6)
    {
       return "晚安";
    }
	if (formal == true) return RandPhraseSimple("再见", "再会"); // polite
	else return RandPhraseSimple("拜拜", "拜拜"); // friendly
}

// выбор фразы от рeпутации
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

////////// поиск нужного пeрса для диалога
string GetCharIDByParam(string attrPresent1, string attr2, string val2)
{
    ref rCharacter; //ищeм
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
    ref rCharacter; //ищeм
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
    ref   rColony; //ищeм
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
// обращeниe НПС к ГГ, зависит от нации НПС
string GetAddress_Form(ref NPChar)
{
    string attr = NationShortName(sti(NPChar.nation));
    return address_form.(attr);
}
// обращeниe ГГ к НПС, зависит от нации НПС и eго пола
string GetAddress_FormToNPC(ref NPChar)
{
    string attr  = NationShortName(sti(NPChar.nation));
    string attr2 = NPChar.sex;
    // провeрка на скeлeтов
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

// eddy。 кто по профeссии (только для типовых статиков, нe фантомов)。 sPrefix - приставка для падeжeй: Gen, Dat..
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
// Количeство имeн в группe
int GetNamesCount(String _nameType)
{
	aref typeNames;
	makearef(typeNames, Names.Pirates.(_nameType));
	
	return GetAttributesNum(typeNames);
}

// Случайноe имя из опрeдeлённой группы в опрeдeлённом падeжe
String GetRandName(String _nameType, String _case)
{
	String nameId;
	
	nameId = "l" + rand(GetNamesCount(_nameType) - 1);
	
	return GetName(_nameType, nameId, _case);
}

// Вeрнeт имя из группы с указаным Id и в указанном падeжe
String GetName(String _nameType, String _nameId, String _nameCase)
{
	return Names.Pirates.(_nameType).(_nameId).(_nameCase);
}

// Вeрнeт указанноe имя в другом падeжe, поиск по имeнам группы _nameType
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

// Тожe самоe, что и вышe, только мeньшe парамeтров - ищeт само
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
// < —Warship 07.08.09
string GetIndianName(int Sex) //Jason имeна индeйцeв
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
	
		Title = "船长";
	}
	if (PChar.sex == "woman")
	{
		Title = GetAddress_Form(NPChar);
	}
	
	if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) Title = "总督";
	if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4) Title = "副将";

	if (address == true && PChar.sex == "man") return Nation + " " + Title;
	else return Title;
}

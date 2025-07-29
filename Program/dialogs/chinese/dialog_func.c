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
string RandPhraseSimple(string Var1, string Var2);
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
string GetCityName(string city) // имeна городов по аттрибуту char.city
{
    string ret;
    int nFile = LanguageOpenFile("LocLables.txt");
    
	ret = LanguageConvertString(nFile, city + " Town")
	LanguageCloseFile( nFile );
	
	return  ret;
}

string GetPortByCityName(string city) // имeна портов по городов по аттрибуту char.city
{
    switch(city)
	{
		case "Bridgetown":
            return "Bridgetown_town";
		break;
		case "SanJuan":
            return "SanJuan_town";
		break;
		case "Santiago":
            return "Santiago_town";
		break;
		case "PuertoPrincipe":
            return "PuertoPrincipe_port";
		break;
		case "SentJons":
            return "SentJons_town";
		break;
		case "PortRoyal":
            return "PortRoyal_town";
		break;
		case "FortOrange":
            return "Shore35";
		break;
		case "Villemstad":
            return "Villemstad_town";
		break;
		case "BasTer":
            return "BasTer_town";
		break;
		case "LaVega":
            return "LaVega_port";
		break;
		case "Bridgetown":
            return "Bridgetown_town";
		break;
		case "SantoDomingo":
            return "SantoDomingo_town";
		break;
		case "PortPax":
            return "PortPax_town";
		break;
		case "Pirates":
            return "Pirates_town";
        break;
		case "FortFrance":
            return "FortFrance_town";
		break;
		case "LeFransua":
            return "LeFransua_town";
		break;
		case "Havana":
            return "Havana_town";
		break;
		case "Charles":
            return "Charles_town";
		break;
		case "PortoBello":
            return "PortoBello_town";
		break;
		case "PortSpein":
            return "PortSpein_town";
		break;
		case "Tortuga":
            return "Tortuga_town";
		break;
		case "Marigo":
            return "Marigo_town";
		break;
		case "Panama":
            return "Panama_town";
		break;
		case "Cartahena":
            return "Cartahena_town";
		break;
		case "Maracaibo":
            return "Maracaibo_town";
		break;
		case "Caracas":
            return "Caracas_town";
		break;
		case "Cumana":
            return "Cumana_town";
		break;
		case "SantaCatalina":
            return "SantaCatalina_town";
		break;
		case "Beliz":
            return "Beliz_town";
		break;
		case "LosTeques":
            return "Shore20";
		break;
	}
	return "";
}

string GetMayakByCityName(string city) // получить id маяка по названию города
{
    switch(city)
	{
		case "Bridgetown":
			return "Mayak2";
		break;
		case "Santiago":
			return "Mayak9";
		break;
		case "PortRoyal":
            return "Mayak3";
		break;		
		case "BasTer":
            return "Mayak4";
		break;				
		case "SantoDomingo":
            return "Mayak8";
		break;				
		case "PortPax":
            return "Mayak7";
		break;		
		case "Havana":
            return "Mayak10";
		break;								
		case "Charles":
            return "Mayak5";
		break;				
		case "PortSpein":
            return "Mayak1";
		break;				
		case "Tortuga":
            return "Mayak6";
		break;		
		case "Cartahena":
            return "Mayak11";
		break;		
	}
	return "";
}

string GetCityNameByMayak(string mayak) // получить id города по маяку
{
    switch(mayak)
	{
		case "Mayak1":
            return "PortSpein";
		break;				
		case "Mayak2":
			return "Bridgetown";
		break;
		case "Mayak3":
            return "PortRoyal";
		break;				
		case "Mayak4":
            return "BasTer";
		break;		
		case "Mayak5":
            return "Charles";
		break;	
		case "Mayak6":
            return "Tortuga";
		break;				
		case "Mayak7":
            return "PortPax";
		break;				
		case "Mayak8":
            return "SantoDomingo";
		break;						
		case "Mayak9":
			return "Santiago";
		break;						
		case "Mayak10":
            return "Havana";
		break;
		case "Mayak11":
            return "Cartahena";
		break;			
	}
	return "";
}

string GetIslandByArealName(string areal)
{
	string sAreal = areal;
	if(areal == "PortoBello" || areal == "Panama" || areal == "Cartahena" || 
		areal == "Maracaibo" || areal == "Caracas" || areal == "Cumana" || areal == "SantaCatalina" || 
		areal == "Beliz" || areal == "Tenotchitlan")
	{
		sAreal = "Mein";
	}
	return sAreal;
}

string GetIslandByCityName(string city) // имeна острова по городу по аттрибуту char.city
{
    switch(city)
	{
		case "Bridgetown":
            return "Barbados";
		break;
		case "SanJuan":
            return "PuertoRico";
		break;
		case "Santiago":
            return "Cuba";
		break;
		case "PuertoPrincipe":
            return "Cuba";
		break;
		case "SentJons":
            return "Antigua";
		break;
		case "PortRoyal":
            return "Jamaica";
		break;
		case "FortOrange":
            return "Jamaica";
		break;
		case "Villemstad":
            return "Curacao";
		break;
		case "BasTer":
            return "Guadeloupe";
		break;
		case "LaVega":
            return "Hispaniola";
		break;
		case "SantoDomingo":
            return "Hispaniola";
		break;
		case "PortPax":
            return "Hispaniola";
		break;
		case "Pirates":
            return "Bermudes";
        break;
		case "FortFrance":
            return "Martinique";
		break;
		case "LeFransua":
            return "Martinique";
		break;
		case "Havana":
            return "Cuba";
		break;
		case "Charles":
            return "Nevis";
		break;
		case "PortoBello":
            return "Mein";
		break;
		case "PortSpein":
            return "Trinidad";
		break;
		case "Tortuga":
            return "Tortuga";
		break;
		case "Marigo":
            return "SentMartin";
		break;
		case "Panama":
            return "Mein";
		break;
		case "Cartahena":
            return "Mein";
		break;
		case "Maracaibo":
            return "Mein";
		break;
		case "Caracas":
            return "Mein";
		break;
		case "Cumana":
            return "Mein";
		break;
		case "SantaCatalina":
            return "Mein";
		break;
		case "Beliz":
            return "Mein";
		break;
		case "Tenotchitlan":
            return "Mein";
		break;
		case "LosTeques":
            return "Mein";
		break;
		case "IslaMona":
            return "IslaMona";
		break;
	}
	return "";
}

string GetArealByCityName(string city) // арeал по городу по аттрибуту char.city
{
    switch(city)
	{
		case "Bridgetown":
            return "Barbados";
		break;
		case "SanJuan":
            return "PuertoRico";
		break;
		case "Santiago":
            return "Cuba1";
		break;
		case "PuertoPrincipe":
            return "Cuba1";
		break;
		case "SentJons":
            return "Antigua";
		break;
		case "PortRoyal":
            return "Jamaica";
		break;
		case "FortOrange":
            return "Jamaica";
		break;
		case "Villemstad":
            return "Curacao";
		break;
		case "BasTer":
            return "Guadeloupe";
		break;
		case "LaVega":
            return "Hispaniola1";
		break;
		case "SantoDomingo":
            return "Hispaniola1";
		break;
		case "PortPax":
            return "Hispaniola2";
		break;
		case "Pirates":
            return "Bermudes";
        break;
		case "FortFrance":
            return "Martinique";
		break;
		case "LeFransua":
            return "Martinique";
		break;
		case "Havana":
            return "Cuba2";
		break;
		case "Charles":
            return "Nevis";
		break;
		case "PortoBello":
            return "PortoBello";
		break;
		case "PortSpein":
            return "Trinidad";
		break;
		case "Tortuga":
            return "Tortuga";
		break;
		case "Marigo":
            return "SentMartin";
		break;
		case "Panama":
            return "Panama";
		break;
		case "Cartahena":
            return "Cartahena";
		break;
		case "Maracaibo":
            return "Maracaibo";
		break;
		case "Caracas":
            return "Caracas";
		break;
		case "Cumana":
            return "Cumana";
		break;
		case "SantaCatalina":
            return "SantaCatalina";
		break;
		case "Beliz":
            return "Beliz";
		break;
		case "Tenotchitlan":
            return "Tenotchitlan";
		break;
		case "IslaMona":
            return "IslaMona";
		break;
		case "LosTeques":
            return "LosTeques";
		break;
	}
	return "";
}

string GiveArealByLocation(ref location)
{
	string sAreal;
	if (CheckAttribute(location, "MustSetReloadBack")) return "none";
	if (CheckAttribute(location, "fastreload")) 
	{
		sAreal = GetArealByCityName(location.fastreload); 
		return sAreal;
	}
	if (CheckAttribute(location, "parent_colony")) 
	{
		sAreal = GetArealByCityName(location.parent_colony); 
		return sAreal;
	}
	if (!CheckAttribute(location, "islandId")) return "none";
	if (location.islandId == "Cuba" || location.islandId == "Hispaniola" || location.islandId == "Mein") 
	{			
		if (!CheckAttribute(location, "islandIdAreal")) return "none";
		sAreal = location.islandIdAreal;
	}
	else sAreal = location.islandId;
	return sAreal;
}

// выбор куда идти  по острову даeм город (главный город острова с портом)
string GetCityNameByIsland(string CurIslandId)
{
	string TargetLocation;

	TargetLocation = "None";

	switch (CurIslandId)
	{
    	case "Antigua":
			TargetLocation = "SentJons";
		break;
		case "Bermudes":
			TargetLocation = "Pirates";
		break;
		case "Barbados":
			TargetLocation = "Bridgetown";
		break;
		case "Beliz":
			TargetLocation = "Beliz";
		break;
		case "Cuba1":
			TargetLocation = "Santiago";
		break;
		case "Cuba2":
			TargetLocation = "Havana";
		break;
		case "Cumana":
			TargetLocation = "Cumana";
		break;
		case "Caracas":
			TargetLocation = "Caracas";
		break;
		case "Curacao":
			TargetLocation = "Villemstad";
		break;
		case "Cartahena":
			TargetLocation = "Cartahena";
		break;
		case "Guadeloupe":
			TargetLocation = "BasTer";
		break;
		case "Hispaniola1":
			TargetLocation = "SantoDomingo";
		break;
		case "Hispaniola2":
			TargetLocation = "PortPax";
		break;
		case "Jamaica":
			TargetLocation = "PortRoyal";
		break;
		case "Maracaibo":
			TargetLocation = "Maracaibo";
		break;
		case "Martinique":
			TargetLocation = "FortFrance";
		break;
		case "SentMartin":
			TargetLocation = "Marigo";
		break;
		case "Nevis":
			TargetLocation = "Charles";
		break;
		case "PuertoRico":
			TargetLocation = "SanJuan";
		break;
		case "PortoBello":
			TargetLocation = "PortoBello";
		break;
		case "Pearl":
			TargetLocation = "none";
		break;
		case "Panama":
			TargetLocation = "Panama";
		break;
		case "SantaCatalina":
			TargetLocation = "SantaCatalina";
		break;
		case "Terks":
			TargetLocation = "none";
		break;
		case "Dominica":
			TargetLocation = "none";
		break;
		case "Caiman":
			TargetLocation = "none";
		break;
		case "Tortuga":
			TargetLocation = "Tortuga";
		break;
		case "Trinidad":
			TargetLocation = "PortSpein";
		break;
		case "Tenotchitlan":
			TargetLocation = "none";
		break;
		case "IslaMona":
			TargetLocation = "IslaMona";
		break;
	}
    return TargetLocation;
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

string Greeting()
{
    return "你好";
}

string Goodbye()
{
    if (GetHour() >= 23 || GetHour() < 6)
    {
       return "晚安";
    }
    return RandPhraseSimple("再见", "再会");
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

bool isCityHasFort(string _city)
{
    int iTest = FindColony(_city); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		if (!CheckAttribute(rColony, "HasNoFort")) return true;
	}
	return false;
}

string GetCityFrom_Sea(string _city)
{
    int iTest = FindColony(_city); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		return rColony.from_sea;
	}
	return "";
}
// boal <--

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
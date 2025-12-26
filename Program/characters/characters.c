
#include "characters\characters_ai.c"
#include "characters\characters_events.c"
#include "characters\characters_login.c"
#include "characters\characters_face.c"
#include "characters\characters.h"
#include "characters\characterUtilite.c"
#include "characters\fellowsUtilite.c"
#include "characters\RPG\rpg.c"
#include "characters\GeneratorUtilite.c" //boal
#include "characters\TravelMap.c" //navy
#include "characters\QuestsUtilite.c" //boal
#include "characters\LSC_Q2Utilite.c"
#include "characters\generator\generator.c"

object chrFindNearCharacters[MAX_CHARS_IN_LOC];
bool isBoardingLoading = false;


void CharactersInit()
{
    if(LoadSegment("characters\Characters_tables.c"))
	{
		InitCharactersTables();
		UnloadSegment("characters\Characters_tables.c");
	}
	ReloadProgressUpdate();

	string sPath = "characters\";
	// + LanguageGetLanguage() + "\";
	
	LoadSegment(sPath + "init\Antigua.c");          ReloadProgressUpdate();
	
	LoadSegment(sPath + "init\Barbados.c");         ReloadProgressUpdate();
	
	LoadSegment(sPath + "init\Jamaica.c");          ReloadProgressUpdate();

	LoadSegment(sPath + "init\Curacao.c");          ReloadProgressUpdate();
	
	LoadSegment(sPath + "init\Guadeloupe.c");       ReloadProgressUpdate();
	
	LoadSegment(sPath + "init\Santiago.c");         ReloadProgressUpdate();

	LoadSegment(sPath + "init\Panama.c");           ReloadProgressUpdate();
	
	LoadSegment(sPath + "init\PuertoPrincipe.c");   ReloadProgressUpdate();

	LoadSegment(sPath + "init\Martinique.c");       ReloadProgressUpdate();

	LoadSegment(sPath + "init\Havana.c");           ReloadProgressUpdate();

	LoadSegment(sPath + "init\Bermudes.c");         ReloadProgressUpdate();
		
	LoadSegment(sPath + "init\Nevis.c");            ReloadProgressUpdate();
	
	LoadSegment(sPath + "init\PuertoRico.c");       ReloadProgressUpdate();
	
	LoadSegment(sPath + "init\LaVega.c");           ReloadProgressUpdate();
	
	LoadSegment(sPath + "init\SantoDomingo.c");     ReloadProgressUpdate();
	
	LoadSegment(sPath + "init\PortPax.c");          ReloadProgressUpdate();
	
	LoadSegment(sPath + "init\PortoBello.c");       ReloadProgressUpdate();
	
	LoadSegment(sPath + "init\Trinidad.c");         ReloadProgressUpdate();
	
	LoadSegment(sPath + "init\SentMartin.c");       ReloadProgressUpdate();
	
	LoadSegment(sPath + "init\Tortuga.c");          ReloadProgressUpdate();

	LoadSegment(sPath + "init\Cartahena.c");        ReloadProgressUpdate();

	LoadSegment(sPath + "init\Maracaibo.c");        ReloadProgressUpdate();

	LoadSegment(sPath + "init\Caracas.c");          ReloadProgressUpdate();

	LoadSegment(sPath + "init\Cumana.c");           ReloadProgressUpdate();

	LoadSegment(sPath + "init\Beliz.c");            ReloadProgressUpdate();

	LoadSegment(sPath + "init\SantaCatalina.c");    ReloadProgressUpdate();
	
	LoadSegment(sPath + "init\Providence.c");       ReloadProgressUpdate();

	LoadSegment(sPath + "init\StoryCharacters.c");  ReloadProgressUpdate();
	
	LoadSegment(sPath + "init\Other.c");            ReloadProgressUpdate();
	
 	if(LoadSegment("characters\characters_init.c"))
	{
		CreateCharacters();
		UnloadSegment("characters\characters_init.c");
	}

	ReloadProgressUpdate();	   
	sPath = "characters\";
	UnloadSegment(sPath + "init\Antigua.c");
	UnloadSegment(sPath + "init\Barbados.c");
	UnloadSegment(sPath + "init\Jamaica.c");
	UnloadSegment(sPath + "init\Curacao.c");
	UnloadSegment(sPath + "init\Guadeloupe.c");
	UnloadSegment(sPath + "init\Santiago.c");
	UnloadSegment(sPath + "init\Panama.c");
	UnloadSegment(sPath + "init\PuertoPrincipe.c");
	UnloadSegment(sPath + "init\Martinique.c");
	UnloadSegment(sPath + "init\Havana.c");
	UnloadSegment(sPath + "init\Bermudes.c");
	UnloadSegment(sPath + "init\Nevis.c");
	UnloadSegment(sPath + "init\PuertoRico.c");
	UnloadSegment(sPath + "init\LaVega.c");
	UnloadSegment(sPath + "init\SantoDomingo.c");
	UnloadSegment(sPath + "init\PortPax.c");
	UnloadSegment(sPath + "init\PortoBello.c");
	UnloadSegment(sPath + "init\Trinidad.c");
	UnloadSegment(sPath + "init\SentMartin.c");
	UnloadSegment(sPath + "init\Tortuga.c");
	UnloadSegment(sPath + "init\Cartahena.c");
	UnloadSegment(sPath + "init\Maracaibo.c");
	UnloadSegment(sPath + "init\Caracas.c");
	UnloadSegment(sPath + "init\Cumana.c");
	UnloadSegment(sPath + "init\Beliz.c");
	UnloadSegment(sPath + "init\SantaCatalina.c");
	UnloadSegment(sPath + "init\Providence.c");
	UnloadSegment(sPath + "init\StoryCharacters.c");
	UnloadSegment(sPath + "init\Other.c");

	ReloadProgressUpdate();
	InitCharacterEvents();
	ReloadProgressUpdate();
	LAi_NewGame();
}

bool CreateCharacter(ref character)
{
	if(character.model.entity != "NPCharacter" && character.model.entity != "Player")
	{
		Trace("CreateCharacter -> character id = '" + character.id + "' idx = " + character.index +" can invalide model.entity ("+ character.model.entity +")");
		/* if(character == GetMainCharacter()) character.model.entity = "Player";
		else character.model.entity = "NPCharacter"; */
		return false;
	}
	
	CreateEntity(&character, character.model.entity);
	if(!SendMessage(character, "lss", MSG_CHARACTER_SETMODEL, character.model, character.model.animation))
	{
		Trace("CreateCharacter -> character id = '" + character.id + "' idx = " + character.index +" can invalide model("+ character.model +") or animation(" + character.model.animation + ")");
		DeleteClass(&character);
		return false;
	}

	float fCurChargePistol = 1000.0;
	float fCurChargeMusket = 1000.0;
	if(actLoadFlag)
	{	//После перезагрузки вернуть заряженность огнестрельного оружия персонажа
		if(CheckAttribute(character,"chr_ai.gun.charge"))
			fCurChargePistol = stf(character.chr_ai.gun.charge);
		if(CheckAttribute(character,"chr_ai.musket.charge"))
			fCurChargeMusket = stf(character.chr_ai.musket.charge);
	}
	ExecuteCharacterEquip(character);
	if(CheckAttribute(character,"chr_ai.gun.charge") && fCurChargePistol < stf(character.chr_ai.gun.charge))
		character.chr_ai.gun.charge = fCurChargePistol;
	if(CheckAttribute(character,"chr_ai.musket.charge") && fCurChargeMusket < stf(character.chr_ai.musket.charge))
		character.chr_ai.musket.charge = fCurChargeMusket;

	//Set fight level
	if(!CheckAttribute(&character, "sex"))
	{
		character.sex = "man";
	}
	//if(character.sex == "man")
	//{
	float fgtlevel = LAi_GetCharacterFightLevel(character); // boal fix

	// Коллизии
	if(CheckAttribute(character, "col_modif.BonusPush"))
		SendMessage(character, "lsl", MSG_CHARACTER_EX_MSG, "SetBonusPush", true);
    if(CheckAttribute(character, "col_modif.Unpushable"))
		SendMessage(character, "lsl", MSG_CHARACTER_EX_MSG, "MakeUnpushable", true);
    if(CheckAttribute(character, "col_modif.IgnoreCollision"))
		SendMessage(character, "lsl", MSG_CHARACTER_EX_MSG, "IgnoreCollision", true);

	SendMessage(character, "lf", MSG_CHARACTER_SETFTGLEVEL, fgtlevel);
	//Set character sex
	int iSex = 1;
	if(character.sex == "woman")
		iSex = 2;
	else if(character.sex == "skeleton")
		iSex = 3;
	SendMessage(character, "lsl", MSG_CHARACTER_EX_MSG, "SetSex", iSex);
	//
	AddCharacterLocatorGroup(character, "goto");
	BeginChangeCharacterActions(character);
	SetDefaultFight(character);
	EndChangeCharacterActions(character);
	// evganat - выставление кастомных баров и иконок архетипов при загрузке персонажа
	SendMessage(character, "lss", MSG_CHARACTER_EX_MSG, "SetBarTexture", "LocEfx\\bars_back.tga");
	GEN_OverrideAppearance(character, -1);
	int iMass = 100;
	if (HasPerk(character, "Dodgy")) iMass *= (1 + PERK_VALUE_DODGY);
	SendMessage(character, "lsl", MSG_CHARACTER_EX_MSG, "SetMass", makeint(iMass));
	return true;
}

bool DeleteCharacter(ref character)
{
	DeleteClass(character);
	return true;
}

bool TeleportCharacterToPos(ref character, float x, float y, float z)
{
	return SendMessage(character, "lfff", MSG_CHARACTER_TELEPORT, x, y, z);
}

bool TeleportCharacterToPosAy(ref character, float x, float y, float z, float ay)
{
	return SendMessage(character, "lffff", MSG_CHARACTER_TELEPORT_AY, x, y, z, ay);
}

bool TeleportCharacterToLocator(ref character, string group, string locator)
{
	return SendMessage(character, "lss", MSG_CHARACTER_TELEPORT_TO_LOCATOR, group, locator);
}

bool CheckLocationPosition(ref location, float x, float y, float z)
{
	if(IsEntity(&loadedLocation) == false) return false;
	return (SendMessage(loadedLocation, "lfff", MSG_LOCATION_CHECKENTRY, x, y, z) != 0);
}

object GetCharacterModel(ref character)
{
	object model;
	SendMessage(character, "le", MSG_CHARACTER_GETMODEL, &model);
	return model;
}

bool GetCharacterPos(ref character, ref float_x, ref float_y, ref float_z)
{
	float cx, cy, cz;
	if(SendMessage(character, "leee", MSG_CHARACTER_GETPOS, &cx, &cy, &cz) == 0) return false;
	float_x = cx; float_y = cy; float_z = cz;
	return true;
}

bool GetCharacterAy(ref character, ref float_ay)
{
	float ay = 0.0;
	if(SendMessage(character, "le", MSG_CHARACTER_GETAY, &ay) == 0) return false;
	float_ay = ay;
	return true;
}

bool PushCharacterAy(ref character)
{
	return SendMessage(character, "l", MSG_CHARACTER_TURNPUSH);
}

bool PopCharacterAy(ref character)
{
	return SendMessage(character, "l", MSG_CHARACTER_TURNPOP);
}

int FindNearCharacters(ref character, float rad, float ax, float testAng, float nearDist, bool isVisibleTest, bool isSort)
{
	int num = 0;
	SendMessage(character, "leeffffll", MSG_CHARACTER_FINDNEAR, &chrFindNearCharacters, &num, rad, ax, testAng, nearDist, isVisibleTest, isSort);
	return num;
}

/*int FindNearNotCompanionCharacters(ref character, float rad, float ax, float testAng, float nearDist, bool isVisibleTest, bool isSort)
{
	int num = 0;
	SendMessage(character, "leeffffll", MSG_CHARACTER_FINDNEAR, &chrFindNearCharacters, &num, rad, ax, testAng, nearDist, isVisibleTest, isSort);
	return num;
}*/

bool CharactersVisibleTest(ref character, ref lookTo)
{
	return SendMessage(character, "li", MSG_CHARACTER_VISIBLE, lookTo);
}

//belamour проверка бега для стелса
bool CharacterIsRun(ref character)
{
	bool r, m;
	if(SendMessage(character, "lee", MSG_CHARACTER_ISRUN, &r, &m) == 0) return false;
	if(r && m) return true;
	return false;
}

//
void BeginChangeCharacterActions(ref character)
{
	DeleteAttribute(character, "actions");
}

//
void EndChangeCharacterActions(ref character)
{
	character.actions = "";
}

void EndChangeCharacterActionsBlend(ref character)
{
	SendMessage(character, "ls", MSG_CHARACTER_EX_MSG, "forceBlend");
	character.actions = "";
}

//Character is stay where play idle animation
void SetDefaultStayIdle(ref character)
{
	character.actions.idle.i1 = "idle_1";
	character.actions.idle.i2 = "idle_2";
	character.actions.idle.i3 = "idle_3";
	character.actions.idle.i4 = "idle_4";
	character.actions.idle.i5 = "idle_5";
	character.actions.idle.i6 = "idle_6";
	character.actions.idle.i7 = "idle_7";
	character.actions.idle.i8 = "idle_8";
	character.actions.idle.i9 = "idle_9";
	character.actions.idle.i10 = "idle_10";
	character.actions.idle.i11 = "idle_11";
	character.actions.HitNoFight = "HitNoFight";

    // TO_DO: УДАЛИТЬ
	if(CheckAttribute(character, "watchglass"))
	{
		character.actions.idle.i1 = "tutorial_1";
		character.actions.idle.i4 = "tutorial_1";
		character.actions.idle.i6 = "tutorial_1";
		character.actions.idle.i8 = "tutorial_1";
		SendMessage(character, "lslssl", MSG_CHARACTER_EX_MSG, "TieItem", FindItem("Spyglass_1"), "Spyglass_1", "Saber_hand", 1);
	}
	if(CheckAttribute(character, "SpyglassWithSkull"))
	{
		character.actions.idle.i1 = "tutorial_1";
		character.actions.idle.i4 = "tutorial_1";
		character.actions.idle.i6 = "tutorial_1";
		character.actions.idle.i8 = "tutorial_1";
		SendMessage(character, "lslssl", MSG_CHARACTER_EX_MSG, "TieItem", FindItem("Spyglass_1"), "Spyglass_SP3", "Saber_hand", 1);
	}
}

//Character is sit where play idle animation
void SetDefaultSitIdle(ref character)
{
	character.actions.idle.i1 = "Sit_Look_Around";
	character.actions.idle.i2 = "Sit_Lower_head";
	character.actions.idle.i3 = "Sit_Idle01";
	character.actions.idle.i4 = "Sit_Idle02";
	character.actions.idle.i5 = "Sit_Idle03";
	character.actions.idle.i6 = "Sit_Idle04";
	character.actions.idle.i7 = "Sit_Idle05";
	character.actions.idle.i8 = "Sit_Idle06";
	character.actions.HitNoFight = "HitNoFightSit";
}

void SetDefaultSit2Idle(ref character)
{
	character.actions.idle.i1 = "Sit2_Idle01";
	character.actions.idle.i2 = "Sit2_Idle02";
	character.actions.idle.i3 = "Sit2_Idle03";
	character.actions.idle.i4 = "Sit2_Idle04";
	character.actions.idle.i5 = "Sit2_Idle05";
	character.actions.idle.i6 = "Sit2_Idle06";
	character.actions.idle.i7 = "Sit2_Idle07";
	character.actions.HitNoFight = "HitNoFightSit";
}

void SetDefaultSit2ChurchIdle(ref character)
{
	if(rand(12) == 3)
	{
		character.actions.idle.i1 = "Church_Stay_1";
		character.actions.idle.i2 = "Church_Stay_2";
		character.actions.idle.i3 = "Church_Stay_3";
		character.actions.idle.i4 = "Church_Stay_4";
		character.actions.idle.i5 = "Church_Stay_5";
		character.actions.idle.i6 = "Church_Stay_1";
		character.actions.idle.i7 = "Church_Stay_2";
	}
	else
	{
		character.actions.idle.i1 = "Church_Sit_1";
		character.actions.idle.i2 = "Church_Sit_2";
		character.actions.idle.i3 = "Church_Sit_3";
		character.actions.idle.i4 = "Church_Sit_4";
		character.actions.idle.i5 = "Church_Sit_5";
		character.actions.idle.i6 = "Church_Sit_1";
		character.actions.idle.i7 = "Church_Sit_2";
	}
	character.actions.HitNoFight = "HitNoFightSit";
}

void SetDialogStayIdle(ref character)
{
	character.actions.idle.i1 = "dialog_stay1";
	character.actions.idle.i2 = "dialog_stay2";
	character.actions.idle.i3 = "dialog_stay3";
	character.actions.idle.i4 = "dialog_stay4";
	character.actions.idle.i5 = "dialog_stay5";
	character.actions.idle.i6 = "dialog_stay6";
	character.actions.idle.i7 = "dialog_stay7";
	character.actions.idle.i8 = "dialog_stay8";
}
// boal -->

// boal <--
void SetDefaultNormWalk(ref character)
{
	string tagMus = "";
	if(LAi_CheckFightMode(character) == 2) tagMus = "_mus";

	int i, j, k, l;
	string tagFightMode;	// "fight" или ""
	string tagMoveMode;		// "walk", "run" или "sprint"
	string tagDirection;	// "forward", "back", "right", "left", "forward-left", "forward-right", "back-left" или "back-right"
	string tagStep;			// "rstep", "lstep" или ""
	string sAttr, sAnim;
	for(i=0; i<2; i++)	// боевой режим
	{
		switch(i)
		{
			case 0:		tagFightMode = "";			break;
			case 1:		tagFightMode = "fight";		break;
		}
		for(j=0; j<3; j++)	// тип движения
		{
			switch(j)
			{
				case 0:		tagMoveMode = "walk";		break;
				case 1:		tagMoveMode = "run";		break;
				case 2:		tagMoveMode = "sprint";		break;
			}
			for(k=0; k<8; k++)	// направление движения
			{
				if(j == 2 && k > 2)	// в спринте нет других направлений
					continue;
				
				switch(k)
				{
					case 0:		tagDirection = "forward";			break;
					case 1:		tagDirection = "forward-right";		break;
					case 2:		tagDirection = "forward-left";		break;
					case 3:		tagDirection = "back";				break;
					case 4:		tagDirection = "back-right";		break;
					case 5:		tagDirection = "back-left";			break;
					case 6:		tagDirection = "right";				break;
					case 7:		tagDirection = "left";				break;	
				}
				
				sAttr = StrConCheck(tagFightMode, "_") + tagDirection + "_" + tagMoveMode;
				sAnim = StrConCheck(tagFightMode, " ") + tagDirection + " " + tagMoveMode;
				character.actions.(sAttr) = sAnim;	// выставляем анимацию постоянного движения
				
				if(j == 0)	// при ходьбе нет инерции и подбора шагов
					continue;
				
				sAttr = "start_" + StrConCheck(tagFightMode, "_") + tagDirection + "_" + tagMoveMode;
				sAnim = "start " + StrConCheck(tagFightMode, " ") + tagDirection + " " + tagMoveMode;
				character.actions.(sAttr) = sAnim;	// выставляем анимацию разгона
				
				if(i == 1)	// в боевом режиме нет торможения и подбора шагов
					continue;
				
				for(l=0; l<3; l++)	// подбор шагов
				{
					switch(l)
					{
						case 0:		tagStep = "";		break;
						case 1:		tagStep = "rstep";	break;
						case 2:		tagStep = "lstep";	break;
					}
					
					sAttr = "stop_" + StrConCheck(tagFightMode, "_") + tagDirection + "_" + tagMoveMode + StrConCheck("_", tagStep);
					sAnim = "stop " + StrConCheck(tagFightMode, " ") + tagDirection + " " + tagMoveMode + StrConCheck(" ", tagStep);
					character.actions.(sAttr) = sAnim;	// выставляем анимацию торможения
				}
			}
		}
	}

    string tagVert = "";
    for(i=0; i<2; i++)
    {
        if(i == 0)	tagVert = "up";
        else		tagVert = "down";
        for(j=0; j<2; j++)
        {
            for(k=0; k<4; k++)
            {
                switch(k)
                {
                    case 0:	tagDirection = "forward";	break;
                    case 1:	tagDirection = "back";		break;
                    case 2:	tagDirection = "right";		break;
                    case 3:	tagDirection = "left";		break;
                }
                if(j == 1)
                    tagFightMode = "fight";
				else
					tagFightMode = "";
				sAttr = StrConCheck(tagFightMode, "_") + tagDirection + "_walk_stairs_" + tagVert;
				sAnim = StrConCheck(tagFightMode, " ") + tagDirection + " walk stairs " + tagVert; 
                character.actions.(sAttr) = sAnim;
            }
        }
    }

	CheckAndSetOverloadMode(character);

	character.actions.turnLeft = "turn left";
	character.actions.turnRight = "turn right";
	character.actions.swim = "swim" + tagMus;
	character.actions.swim_sprint = "swim sprint" + tagMus;
	character.actions.fall = "fall" + tagMus;
	character.actions.fall_land = "fall_land" + tagMus;
	character.actions.fall_water = "fall_water" + tagMus;
}

void SetDefaultFight(ref character)
{
	string tag = "";
	if(LAi_CheckFightMode(character) == 2) tag = "_mus";

	character.actions.fightwalk = "fight walk" + tag;
	character.actions.fightrun = "fight run" + tag;
	character.actions.fightbackwalk = "fight back walk" + tag;
	character.actions.fightbackrun = "fight back run" + tag;
	
	CheckAndSetOverloadMode(character);

	//Действия в режиме боя
	//Fast (max 3) --------------------------------------------------
	character.actions.attack_fast.a1 = "attack_fast_1" + tag;
	character.actions.attack_fast.a2 = "attack_fast_2" + tag;
	character.actions.attack_fast.a3 = "attack_fast_3" + tag;
	//Force (max 4) --------------------------------------------------
	character.actions.attack_force.a1 = "attack_force_1" + tag;
	character.actions.attack_force.a2 = "attack_force_2" + tag;
	character.actions.attack_force.a3 = "attack_force_3" + tag;
	character.actions.attack_force.a4 = "attack_force_4" + tag;
	//Round (max 2) --------------------------------------------------
	character.actions.attack_round.a1 = "attack_round_1" + tag;
	//Break (max 4) --------------------------------------------------
	character.actions.attack_break.a1 = "attack_break_1" + tag;
	//Feint (max 4) --------------------------------------------------
	character.actions.attack_feint.a1 = "attack_feint_1" + tag;
	character.actions.attack_feint.a2 = "attack_feint_2" + tag;
	character.actions.attack_feint.a3 = "attack_feint_3" + tag;
	character.actions.attack_feint.a4 = "attack_feint_4" + tag;

	character.actions.attack_feintc.a1 = "attack_feintc_1" + tag;
	character.actions.attack_feintc.a2 = "attack_feintc_2" + tag;
	character.actions.attack_feintc.a3 = "attack_feintc_3" + tag;
	character.actions.attack_feintc.a4 = "attack_feintc_4" + tag;
	//Shot--------------------------------------------------
	
//	character.actions.shot = "Shot" + tag;
	//Normal hit (max 3) --------------------------------------------------
	character.actions.hit_attack.h1 = "hit_attack_1" + tag;
	character.actions.hit_attack.h2 = "hit_attack_2" + tag;
	character.actions.hit_attack.h3 = "hit_attack_3" + tag;
	//Ohter hits --------------------------------------------------------------------
	character.actions.hit_feint = "hit_feint" + tag;
	character.actions.hit_parry = "hit_parry" + tag;
	character.actions.hit_round = "hit_round" + tag;
	character.actions.hit_shot  = "hit_fire" + tag;
	//Block--------------------------------------------------------------------
	character.actions.block = "block" + tag;
	character.actions.block_forward = "block forward walk" + tag;
	character.actions.block_back = "block back walk" + tag;
	character.actions.block_right = "block right walk" + tag;
	character.actions.block_left = "block left walk" + tag;
	character.actions.block_forward_right = "block forward-right walk" + tag;
	character.actions.block_forward_left = "block forward-left walk" + tag;
	character.actions.block_back_right = "block back-right walk" + tag;
	character.actions.block_back_left = "block back-left walk" + tag;
	character.actions.blockhit = "block_hit" + tag;
	
	// стаггеры в блоке
	string sAttr;
	for(int i = 1; i <= 3; i++)	// лочим на 3 вариации
	{
		sAttr = "a" + i;
		character.actions.blockbreak.(sAttr) = "block_break_" + i + tag;
		character.actions.blockbreak_back.(sAttr) = "block_break_back_" + i + tag;
		character.actions.blockbreak_bypass.(sAttr) = "block_break_bypass_" + i + tag;
		character.actions.blockbreak_fire.(sAttr) = "block_break_fire_" + i + tag;
	}
	character.actions.attack_block_bypass.a1 = "attack_block_bypass_1";
	character.actions.attack_power_break.a1 = "attack_power_break_1";
	character.actions.attack_power_round.a1 = "attack_power_round_1";

	character.actions.block_axe = "block_axe";
	character.actions.block_axe_forward = "block_axe forward walk" + tag;
	character.actions.block_axe_back = "block_axe back walk" + tag;
	character.actions.block_axe_right = "block_axe right walk" + tag;
	character.actions.block_axe_left = "block_axe left walk" + tag;
	character.actions.block_axe_forward_right = "block_axe forward-right walk" + tag;
	character.actions.block_axe_forward_left = "block_axe forward-left walk" + tag;
	character.actions.block_axe_back_right = "block_axe back-right walk" + tag;
	character.actions.block_axe_back_left = "block_axe back-left walk" + tag;
	character.actions.blockhit = "block_hit" + tag;
	character.actions.blockaxehit = "block_axe_hit";
	//Parry--------------------------------------------------------------------
	character.actions.parry.p1 = "parry_1" + tag;
	character.actions.parry.p2 = "parry_2" + tag;
	character.actions.parry.p3 = "parry_3" + tag;
	character.actions.parry.p4 = "parry_4" + tag;
	//Strafes--------------------------------------------------------------------
	character.actions.recoil = "recoil" + tag;			//Назад
	character.actions.strafeleft  = "strafeleft" + tag;	//Влево
	character.actions.straferight = "straferight" + tag;//Вправо
	//Death
	SetDefaultFightDead(character);
	//Idle анимация в режиме боя
	character.actions.fightidle.i1 = "fight stand_1" + tag;
	character.actions.fightidle.i2 = "fight stand_2" + tag;
	character.actions.fightidle.i3 = "fight stand_3" + tag;
	character.actions.fightidle.i4 = "fight stand_4" + tag;
	character.actions.fightidle.i5 = "fight stand_5" + tag;
	character.actions.fightidle.i6 = "fight stand_6" + tag;
	character.actions.fightidle.i7 = "fight stand_7" + tag;
	//Дразнилка после отскока в сабельном, просто айдл в мушкетном
	character.actions.fightidle.i8 = "fight stand_8" + tag;
	
/*	character.actions.aim_start = "aiming start" + tag;
	character.actions.aiming = "aiming" + tag;
	character.actions.aim_shot = "aiming shot" + tag;
	character.actions.aim_end = "aiming end" + tag;	*/
	character.actions.aim_hit1 = "hit_aiming_1" + tag;
	character.actions.aim_hit2 = "hit_aiming_2" + tag;
//	character.actions.fast_shot = "fast shot" + tag;
}

void SetDefaultDead(ref character)
{
	character.actions.dead.d1 = "death_citizen_1";
	character.actions.dead.d2 = "death_citizen_2";
}

void SetDefaultSitDead(ref character)
{
	character.actions.dead.d1 = "Sit_Death";
}

void SetAfraidDead(ref character)
{
	character.actions.dead.d1 = "death_afraid_1";
	character.actions.dead.d2 = "death_afraid_2";
}

void SetDefaultFightDead(ref character)
{
	string tag = "";
	if(LAi_CheckFightMode(character) == 2) tag = "_mus";

	character.actions.fightdead.d1 = "death_0" + tag;
	character.actions.fightdead.d2 = "death_1" + tag;
	character.actions.fightdead.d3 = "death_2" + tag;
	character.actions.fightdead.d4 = "death_3" + tag;
	if(character.model.animation == "man")
		character.actions.fightdead.d5 = "death_11";
}

void SetHuberAnimation(ref character)
{
	character.actions.idle.i1 = "Gov_ObserveHands";
	character.actions.idle.i2 = "Gov_LegOnLeg";
	character.actions.idle.i3 = "Gov_Look_Around";
	character.actions.idle.i4 = "Gov_think_1";
	character.actions.idle.i5 = "Gov_think_2";
	character.actions.idle.i6 = "Gov_think_3";
	character.actions.HitNoFight = "HitNoFightSit";
}

void TeleportCharacterToLocatorIgnoreCollision(ref chr, string group, string locator) {
	aref aloc;
	makearef(aloc, loadedLocation.locators.(group).(locator));
	
	float x = stf(aloc.x);
	float y = stf(aloc.y);
	float z = stf(aloc.z);
	
	float vz = stf(aloc.vz.z);
	float vx = stf(aloc.vz.x);
	float l = vx * vx + vz * vz;
	if (l > 0.0000001) {
		vz = acos(vz / sqrt(l));
	} else {
		vz = l;
	}

	if (vx < 0) {
		vz = -vz;
	}
	
	TeleportCharacterToPosAy(chr, x, y, z, vz);
}

void CharacterTurnByLocInstant(ref character, string group, string locator) {
	float x, y, z;
	GetCharacterPos(character, &x, &y, &z);
	
	aref aloc;
	makearef(aloc, loadedLocation.locators.(group).(locator));
	
	float lx = stf(aloc.x);
	float ly = stf(aloc.y);
	float lz = stf(aloc.z);
	
	float dx = lx - x;
	float dz = lz - z;
	
	float l = dx * dx + dz * dz;
	if (l <= 0) {
		return;
	}
	
	float ay = acos(dz / sqrt(l));
	if (dx < 0) {
		ay = -ay;
	}
	
	TeleportCharacterToPosAy(character, x, y, z, ay);
}

#event_handler("Event_SetAnimations", "Character_SetAnimations");
void Character_SetAnimations()
{
	aref character = GetEventData();
	string tag = GetEventData();

	if (bMainMenu) return;
	if (!IsEntity(&character)) return;
	CheckAndSetOverloadMode(character);
}

void SetPriorityMode(ref chr, int iPMode)
{
    //Для диалогов можно и через CharacterRef, но пусть будет общий метод
    chr.PriorityMode = iPMode;
    SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "SetMusketer", iPMode == 2);
}

// Проверка на наличие локатора шляпы в модели
bool HasHatLocator(ref chr)
{
  object mdl, locs;
  CreateEntity(&mdl, "MODELR");
  SendMessage(&mdl, "ls", MSG_MODEL_LOAD_GEO, "Characters\" + chr.model);
  SendMessage(&mdl, "la", MSG_MODEL_GET_LOCATORS, &locs);
  DeleteClass(&mdl);
  
  int nGroup = GetAttributesNum(&locs);
  for (int i = 0; i < nGroup; i++) {
    aref grp = GetAttributeN(&locs, i);
    int nLoc = GetAttributesNum(grp);
    for (int j = 0; j < nLoc; j++) {
      aref loc = GetAttributeN(grp, j);
      if (GetAttributeName(loc) == "hat") {
        return true;
      }
    }
  }
  
  return false;
}

// belamour исключения для моделей без локатора шляпы
bool CanEquipHatDirectly(ref chr)
{
	if(!CheckAttribute(chr, "model")) return false;
	if(chr.model == "Sharle_6") return true;
	if(chr.model == "Sharle_7") return true;
	if(chr.model == "Sharle_8") return true;
	if(chr.model == "Diego_6") return true;
	if(chr.model == "Diego_8") return true;
	if(chr.model == "protocusto") return true;
	//if(HasSubStr(chr.model, "Willy")) return true;
	
	return false;
}

// складывает строки, если не пустые
string StrConCheck(string str1, string str2)
{
	if(str1 != "" && str2 != "")
		return str1 + str2;
	return "";
}

// Модификаторы коллизий
void SetBonusPush(ref chr, bool bSet)
{
    if(bSet) chr.col_modif.BonusPush = "";
    else DeleteAttribute(chr, "col_modif.BonusPush");
    SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "SetBonusPush", bSet);
}

void MakeUnpushable(ref chr, bool bSet)
{
    if(bSet) chr.col_modif.Unpushable = "";
    else DeleteAttribute(chr, "col_modif.Unpushable");
    SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "MakeUnpushable", bSet);
}

void IgnoreCollision(ref chr, bool bSet)
{
    if(bSet) chr.col_modif.IgnoreCollision = "";
    else DeleteAttribute(chr, "col_modif.IgnoreCollision");
    SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "IgnoreCollision", bSet);
}

// Методы для синхронизации скорости воспроизведения
// Для анимаций с несколькими актёрами
void SetPlaybackDlt(ref chr, float dlt)
{
    wRange(&dlt, -0.05, 0.05);
    SendMessage(chr, "lsf", MSG_CHARACTER_EX_MSG, "SetPlaybackDlt", dlt);
}

// Скорость воспроизведения по умолчанию как указана в экшене из ani
void SyncPlaybackDlt(ref chr1, ref chr2)
{
    SendMessage(chr1, "lsf", MSG_CHARACTER_EX_MSG, "SetPlaybackDlt", 0.0);
    SendMessage(chr2, "lsf", MSG_CHARACTER_EX_MSG, "SetPlaybackDlt", 0.0);
}

// [-0.05, 0.05]
float GenPlaybackDlt()
{
    return frnd()*0.1 - 0.05;
}

void SetAttackSpeed(ref chr, float speed)
{
	SetCharacterActionSpeed(chr, FORCE_STRIKE, speed);
	SetCharacterActionSpeed(chr, FAST_STRIKE,  speed);
	SetCharacterActionSpeed(chr, ROUND_STRIKE, speed);
	SetCharacterActionSpeed(chr, BREAK_STRIKE, speed);
}

void SetCharacterActionAnimation(ref chr, string sAction, string sAnimation)
{
	BeginChangeCharacterActions(chr);
	chr.actions.(sAction) = sAnimation;
	chr.actions.(sAction).d1 = sAnimation;
	EndChangeCharacterActions(chr);
}

// Для ручного управления
void SetPCharRank(int val)
{
    int old = sti(PChar.rank);
    PChar.rank = val;
    if (old < val) Event("PlayerLevelUp");
}

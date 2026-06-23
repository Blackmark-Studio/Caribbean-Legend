// BOAL полностью переделано под нужны ВМЛ

// -> ugeen 27.01.09 - лочим лояльность квестовых офф-ов (всегда максимальная)
void OfficersReaction(string alignment)
{
	int iPassenger;
	int i, cn;
	ref sld;
	
	for (int io = 0; io<GetPassengersQuantity(pchar); io++)
	{   // любой пассажир у кого есть пристрастие может свалить если наши дела ему не по душе
		iPassenger = GetPassenger(pchar, io);
		if (iPassenger != -1)
		{
			sld = GetCharacter(iPassenger);
			if (CheckAttribute(sld, "loyality") && !CheckAttribute(sld, "OfficerWantToGo.DontGo") && !IsEquipCharacterByArtefact(sld, "totem_04"))
			{
				if(CheckAttribute(sld, "alignment"))
				{
					if (sld.alignment == alignment)
					{
						sld.loyality = int(sld.loyality) + 1;
					}
					else
					{
						sld.loyality = int(sld.loyality) - 1;
					}
				}
			}
		}
	}
	for (i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn!=-1)
		{
			sld = GetCharacter(cn);
			if (CheckAttribute(sld, "loyality") && !CheckAttribute(sld, "OfficerWantToGo.DontGo") && !IsEquipCharacterByArtefact(sld, "totem_04"))
			{
				if (sld.alignment == alignment)
				{
					sld.loyality = int(sld.loyality) + 1;
					if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, 1); //navy
				}
				else
				{
					sld.loyality = int(sld.loyality) - 1;
					// специально не далею приведение к 0 и мах. потому чтоб был запас минусов для проверок
					if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, -1); //navy
				}
			}									
		}
	}
}
//-> ugeen

void ChangeOfficerLoyality(ref officer, int addLoyality)
{
	if (!CheckAttribute(officer, "loyality")) return;

	officer.loyality = int(officer.loyality) + addLoyality;
}

void ChangeOfficersLoyality(string alignment, int iLoyality)
{ // aliggnment types : "bad" , "good" , "bad_all" , "good_all"

	int iPassenger;
	int i, cn;
	ref sld;

    // Нормируем
    if (iLoyality < 0)
    {
        iLoyality = -iLoyality;
        switch (alignment)
        {
            case "good":     alignment = "bad";      break;
            case "good_all": alignment = "bad_all";  break;
            case "bad":      alignment = "good";     break;
            case "bad_all":  alignment = "good_all"; break;
        }
    }

	for (int io = 0; io < GetPassengersQuantity(pchar); io++)
	{   // любой пассажир у кого есть пристрастие может свалить если наши дела ему не по душе	
		iPassenger = GetPassenger(pchar, io);
		if (iPassenger != -1)
		{
			sld = GetCharacter(iPassenger);
			if (CheckAttribute(sld, "loyality") && !CheckAttribute(sld, "OfficerWantToGo.DontGo"))
			{
				switch (alignment)
				{
					case "bad":
						if (sld.alignment == alignment) sld.loyality = int(sld.loyality) + iLoyality*2;
						else 							sld.loyality = int(sld.loyality) - iLoyality;
					break;
					case "good":
						if (sld.alignment == alignment) sld.loyality = int(sld.loyality) + iLoyality*2;
						else 							sld.loyality = int(sld.loyality) - iLoyality;
					break;
					case "bad_all":
						sld.loyality = int(sld.loyality) - iLoyality;
					break;
					case "good_all":
						sld.loyality = int(sld.loyality) + iLoyality*2;
					break;
				}
			}
		}
	}
	for (i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn!=-1)
		{
			sld = GetCharacter(cn);
			if (CheckAttribute(sld, "loyality") && !CheckAttribute(sld, "OfficerWantToGo.DontGo"))
			{
				switch (alignment)
				{
					case "bad":
						if (sld.alignment == alignment)
                        {
							sld.loyality = int(sld.loyality) + iLoyality*2;
							if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, 1);
						}
						else 
						{
							sld.loyality = int(sld.loyality) - iLoyality;
							if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, -1);
						}
					break;
					case "good":
						if (sld.alignment == alignment)
                        {
							sld.loyality = int(sld.loyality) + iLoyality*2;
							if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, 1);	
						}
						else 
						{
							sld.loyality = int(sld.loyality) - iLoyality;
							if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, -1);
						}
					break;
					case "bad_all":
						sld.loyality = int(sld.loyality) - iLoyality;
						if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, -1);
					break;
					case "good_all":
						sld.loyality = int(sld.loyality) + iLoyality*2;
						if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, 1);
					break;
				}
			}
		}
	}
}

// результат реакции - действия офа - диалог
void OfficersReactionResult()
{
	int iPassenger;
	int i;
	ref sld;
	
	if (LAi_IsCapturedLocation) return;
	if (chrDisableReloadToLocation) return; // идёт некий другой квест с запретом выхода
	if (CheckAttribute(Pchar,"questTemp.MutinyOfficerIDX")) return;
	
	for (i = 0; i<GetPassengersQuantity(pchar); i++)
	{   // любой пассажир у кого есть пристрастие может свалить если наши дела ему не по душе
		iPassenger = GetPassenger(pchar, i);
		if (iPassenger != -1)
		{
			sld = GetCharacter(iPassenger);
			//if(sld.id != "Duran") return;
			if (CheckAttribute(sld, "loyality") && !CheckAttribute(sld,"prisoned") && GetRemovable(sld) && !CheckAttribute(sld, "OfficerWantToGo.DontGo"))
			{
				if (int(sld.loyality) < 1)
				{
					if (PlaceCharacter(sld, "goto", "random_must_be_near") != "")
					{
						sld.dialog.filename = "Enc_Officer_dialog.c";
						sld.dialog.currentnode = "WantToRemove";
				      	if (sld.sex != "woman")
						{
					    	sld.greeting = "Gr_Officer_Fired";
							if(sld.id == "Duran") sld.greeting = "Duran_officer";
					    }
						if(!CheckCharacterPerk(pchar, "IronWill")) DeleteAttribute(sld, "quest.officertype");
	
						LAi_SetOneTimeActorTypeForOfficer(sld);
						LAi_ActorDialog(sld, pchar, "OpenTheDoors", 2.0, 0);
						//SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0.0, 0.0);
			    		//LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			    		chrDisableReloadToLocation = true;
			    		//DoQuestCheckDelay("OpenTheDoors", 5.0);
						break; 
					}
				}
			}
		}
	}
	if (chrDisableReloadToLocation) return; // уже увольняется
	
	if (CheckNPCQuestDate(pchar, "OfficerWantToGo") && rand(1) == 1) // только раз в день
	{
		SetNPCQuestDate(pchar, "OfficerWantToGo");
		for (i = 0; i<GetPassengersQuantity(pchar); i++)
		{   // любой пассажир у кого есть пристрастие может свалить если наши дела ему не по душе
			iPassenger = GetPassenger(pchar, i);
			if (iPassenger != -1)
			{
				sld = GetCharacter(iPassenger);
				if (sld.id == "Duran" && CheckAttribute(pchar,"QuestInfo.TheFormerKnight")) continue;
				if (!CheckAttribute(sld,"prisoned") && !CheckAttribute(sld, "OfficerWantToGo.DontGo") && GetRemovable(sld) && rand(10) == 5 && GetNpcQuestPastDayParam(sld, "HiredDate") > 60)
				{
					if (sld.dialog.filename == "Enc_Officer_dialog.c") // квестовые не достают
					{
						if (PlaceCharacter(sld, "goto", "random_must_be_near") != "")
						{
							sld.dialog.currentnode = "WantToGo";
		                    sld.greeting           = "Gr_Officer_Salary";
							if(sld.id == "Duran") sld.greeting = "Duran_officer";
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "OpenTheDoors", 2.0, 0);
							//SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0.0, 0.0);
				    		//LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
				    		chrDisableReloadToLocation = true;
				    		//DoQuestCheckDelay("OpenTheDoors", 5.0);
							break; 
						}
					}
				}
			}
		}
	}
}

bool isOfficerInShip(ref _chr, bool _withBoard)
{
    int idx = int(_chr.index);

	if(int(pchar.Fellows.Passengers.navigator) == idx)
	{
  		return true;
	}

	if(int(pchar.Fellows.Passengers.boatswain) == idx)
	{
		return true;
	}

	if(int(pchar.Fellows.Passengers.cannoner) == idx)
	{
  		return true;
	}

	if(int(pchar.Fellows.Passengers.doctor) == idx)
	{
  		return true;
	}

	if(int(pchar.Fellows.Passengers.carpenter) == idx)
	{
  		return true;
	}

    if(int(pchar.Fellows.Passengers.treasurer) == idx)
	{
  		return true;
	}

	if(_withBoard && IsOfficer(_chr))
	{
		return true;
	}

	return false;
}

// метод увольняет офицера - название левое, наследие к3
void CheckForReleaseOfficer(int iCharIndex)
{
	if(int(pchar.Fellows.Passengers.navigator) == iCharIndex)
	{
		pchar.Fellows.Passengers.navigator = -1;
		DeleteAttribute(&characters[iCharIndex], "navigator"); // совместитель дожности
	}

	if(int(pchar.Fellows.Passengers.boatswain) == iCharIndex)
	{
		pchar.Fellows.Passengers.boatswain = -1;
		DeleteAttribute(&characters[iCharIndex], "boatswain"); // совместитель дожности
	}

	if(int(pchar.Fellows.Passengers.cannoner) == iCharIndex)
	{
		pchar.Fellows.Passengers.cannoner = -1;
		DeleteAttribute(&characters[iCharIndex], "cannoner"); // совместитель дожности
	}

	if(int(pchar.Fellows.Passengers.doctor) == iCharIndex)
	{
		pchar.Fellows.Passengers.doctor = -1;
		DeleteAttribute(&characters[iCharIndex], "doctor"); // совместитель дожности
	}

	if(int(pchar.Fellows.Passengers.carpenter) == iCharIndex)
	{
		pchar.Fellows.Passengers.carpenter = -1;
		DeleteAttribute(&characters[iCharIndex], "carpenter"); // совместитель дожности
	}
	
    if(int(pchar.Fellows.Passengers.treasurer) == iCharIndex)
	{
		pchar.Fellows.Passengers.treasurer = -1;
		DeleteAttribute(&characters[iCharIndex], "treasurer"); // совместитель дожности
	}

	RemoveOfficersIndex(pchar, iCharIndex);
	DeleteAttribute(&characters[iCharIndex], "fighter"); // совместитель дожности
	DeleteAttribute(&characters[iCharIndex], "isbusy");
	Event(EVENT_CT_UPDATE_FELLOW, "a", &Characters[iCharIndex]);
}

bool CheckForAllOfficers() // ugeen 2016 -  возвращает true при наличии всех офицеров в команде ГГ
{
	bool bOk = true;

	if( !CheckAttribute(pchar,"Fellows.Passengers.navigator") || int(pchar.Fellows.Passengers.navigator) < 0 ) bOk = false;
	if( !CheckAttribute(pchar,"Fellows.Passengers.boatswain") || int(pchar.Fellows.Passengers.boatswain) < 0 ) bOk = false;
	if( !CheckAttribute(pchar,"Fellows.Passengers.cannoner")  || int(pchar.Fellows.Passengers.cannoner)  < 0 ) bOk = false;
	if( !CheckAttribute(pchar,"Fellows.Passengers.doctor")    || int(pchar.Fellows.Passengers.doctor)    < 0 ) bOk = false;
	if( !CheckAttribute(pchar,"Fellows.Passengers.treasurer") || int(pchar.Fellows.Passengers.treasurer) < 0 ) bOk = false;
	if( !CheckAttribute(pchar,"Fellows.Passengers.carpenter") || int(pchar.Fellows.Passengers.carpenter) < 0 ) bOk = false;
	
	for(int i=1; i<4; i++)
	{	
		if (int(GetOfficersIndex(pchar, i)) < 0) bOk = false;
	}
	return bOk;
}

//////////////// OFFICER ////////////////
void SetOfficerParam(ref Npchar, int _type)
{
	float upSkill = 0.7;
	
	ClearCharacterExpRate(Npchar); // трем все пороги экспы на всяк сулчай

    Npchar.quest.LeadershipModify  = 0;
	Npchar.quest.FencingModify     = 0;
	Npchar.quest.SailingModify     = 0;
	Npchar.quest.AccuracyModify    = 0;
	Npchar.quest.CannonsModify     = 0;
	Npchar.quest.GrapplingModify   = 0;
	Npchar.quest.RepairModify      = 0;
	Npchar.quest.DefenseModify     = 0;
	Npchar.quest.CommerceModify    = 0;
	Npchar.quest.SneakModify       = 0;
	Npchar.quest.PistolModify      = 0;

	SetRandSPECIAL(Npchar);
	Npchar.quest.officertype_2 = "";
    switch(_type)
	{
		case 0:
			Npchar.quest.officertype = "boatswain";
			Npchar.quest.officertype_2 = RandPhraseSimple(XI_ConvertString("BoatswainPhrase1"), XI_ConvertString("BoatswainPhrase2"));
			Npchar.quest.LeadershipModify  = frandSmall(2.0);
			Npchar.quest.FencingModify     = Rand(1);
			Npchar.quest.GrapplingModify   = frandSmall(2.0) + 2;
			Npchar.quest.DefenseModify     = frandSmall(2.0) + 2;
			Npchar.quest.SneakModify       = Rand(1);
			
			//Npchar.skill.Grappling_rate = int(MOD_EXP_RATE * upSkill);
            //Npchar.skill.Defence_rate   = int(MOD_EXP_RATE * upSkill);
		break;

		case 1:
			Npchar.quest.officertype = "cannoner";
			Npchar.quest.AccuracyModify      = frandSmall(2.0) + 2;
			Npchar.quest.CannonsModify       = frandSmall(2.0) + 2;
			Npchar.quest.SneakModify         = Rand(1);
			
			//Npchar.skill.Cannons_rate = int(MOD_EXP_RATE * upSkill);
            //Npchar.skill.Accuracy_rate   = int(MOD_EXP_RATE * upSkill);
		break;

		case 2:
			Npchar.quest.officertype_2 = RandPhraseSimple(XI_ConvertString("TreasurerPhrase1"), XI_ConvertString("TreasurerPhrase2"));
			Npchar.quest.officertype = "treasurer";
			Npchar.quest.RepairModify        = frandSmall(2.0) + 3;
			Npchar.quest.CommerceModify      = frandSmall(2.0) + 2;
			Npchar.quest.SneakModify         = frandSmall(2.0) + 2;
			
			//Npchar.skill.Repair_rate = int(MOD_EXP_RATE * upSkill);
            //Npchar.skill.Commerce_rate   = int(MOD_EXP_RATE * upSkill);
		break;

		case 3:
			Npchar.quest.officertype_2 = RandPhraseSimple(XI_ConvertString("NavigatorPhrase1"), XI_ConvertString("NavigatorPhrase2"));
			Npchar.quest.officertype = "navigator";
			Npchar.quest.SailingModify        = frandSmall(2.0) + 2;
			Npchar.quest.DefenseModify        = frandSmall(2.0) + 1.3;
			Npchar.quest.SneakModify          = frandSmall(2.0);
			
			//Npchar.skill.Sailing_rate = int(MOD_EXP_RATE * upSkill);
		break;

        case 4:
			Npchar.quest.officertype = "fighter";
			Npchar.quest.FencingModify         = frandSmall(2.0) + 2;
			Npchar.quest.PistolModify          = frandSmall(2.0) + 2;
			
			//Npchar.skill.Fencing_rate = int(MOD_EXP_RATE * upSkill);
            //Npchar.skill.Pistol_rate   = int(MOD_EXP_RATE * upSkill);
		break;
        // не при делах -->
        case 5:
			//Npchar.quest.officertype = OFFIC_TYPE_FIRSTMATE;
			Npchar.quest.LeadershipModify     = frandSmall(3.0) + 2;
			Npchar.quest.SailingModify        = frandSmall(1.0) + 1;
			Npchar.quest.SneakModify          = Rand(3) + 1;
			
			//Npchar.skill.Leadership_rate = int(MOD_EXP_RATE * upSkill);
            //Npchar.skill.Sneak_rate   = int(MOD_EXP_RATE * upSkill);
		break;
		
		case 6:
			//Npchar.quest.officertype = OFFIC_TYPE_DOCTOR;
			Npchar.quest.DefenseModify       = Rand(3) + 3;
			Npchar.quest.SneakModify         = Rand(3);
		break;
		// не при делах
		case 7:
			//Npchar.quest.officertype = OFFIC_TYPE_CARPENTER;
			Npchar.quest.RepairModify         = Rand(3) + 3;
			Npchar.quest.SneakModify          = Rand(3);
		break;
	}

	// boal Npchar.rank = int(Pchar.rank) - 2 + Rand(4);
	Npchar.experience = 0;// boal CalculateExperienceFromRank(int(Npchar.rank));
    // boal fix 16.12.2003 -->
	//CalculateAppropriateSkills(NPchar);
	float MiddleK = GetMiddleMainSkill();

    Npchar.skill.Leadership    = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.FencingS      = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Sailing       = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Accuracy      = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Cannons       = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Grappling     = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Repair        = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Defence       = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Commerce      = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Sneak         = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
    Npchar.skill.Pistol        = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
    Npchar.skill.FencingL      = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
    Npchar.skill.FencingH      = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
    Npchar.skill.Fortune       = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;

    CorrectSkillParam(Npchar); // привести к 0-1
    // boal fix 16.12.2003 <--

	Npchar.skill.Leadership   = int(float(Npchar.skill.Leadership)   + 10*float(Npchar.quest.LeadershipModify));
	Npchar.skill.FencingS     = int(float(Npchar.skill.FencingS)     + 10*float(Npchar.quest.FencingModify));
	Npchar.skill.Sailing      = int(float(Npchar.skill.Sailing)      + 10*float(Npchar.quest.SailingModify));
	Npchar.skill.Accuracy     = int(float(Npchar.skill.Accuracy)     + 10*float(Npchar.quest.AccuracyModify));
	Npchar.skill.Cannons      = int(float(Npchar.skill.Cannons)      + 10*float(Npchar.quest.CannonsModify));
	Npchar.skill.Grappling    = int(float(Npchar.skill.Grappling)    + 10*float(Npchar.quest.GrapplingModify));
	Npchar.skill.Repair       = int(float(Npchar.skill.Repair)       + 10*float(Npchar.quest.RepairModify));
	Npchar.skill.Defence      = int(float(Npchar.skill.Defence)      + 10*float(Npchar.quest.DefenseModify));
	Npchar.skill.Commerce     = int(float(Npchar.skill.Commerce)     + 10*float(Npchar.quest.CommerceModify));
	Npchar.skill.Sneak        = int(float(Npchar.skill.Sneak)        + 10*float(Npchar.quest.SneakModify));
    Npchar.skill.Pistol       = int(float(Npchar.skill.Pistol)       + 10*float(Npchar.quest.PistolModify));
    Npchar.skill.FencingL     = int(float(Npchar.skill.FencingL)     + 10*float(Npchar.quest.FencingModify));
    Npchar.skill.FencingH     = int(float(Npchar.skill.FencingH)     + 10*float(Npchar.quest.FencingModify));
    Npchar.skill.Fortune      = int(float(Npchar.skill.Fortune)      + 10*float(Npchar.quest.SneakModify));

    CorrectSkillParam(Npchar); // привести к 0-10
    
    // CL - ugeen,ограничение на навигацию
    if(int(Npchar.skill.Sailing) > 75) Npchar.skill.Sailing = 75;

    Npchar.reputation = rand(84) + 5;
    // пристрастие офицера -->
    Npchar.loyality = 10 + rand(10);
    if (int(Npchar.reputation) > 41)
    {
        Npchar.alignment = "good";
    }
    else
    {
        Npchar.alignment = "bad";
    }
    SetRankFromSkill(Npchar);

    LAi_NPC_Equip(Npchar, int(Npchar.rank), true, true); // fix 101104 выдадим все заново!!!!
    
    SetFantomHP(Npchar);
    
    Npchar.quest.OfficerPrice    = (11 + 2*int(Npchar.rank))*(150 + MOD_SKILL_ENEMY_RATE*16) + rand(5)*8;
    Npchar.quest.OfficerLowPrice = int(int(Npchar.quest.OfficerPrice)/1.5 + 0.5);
}
///////////////////////////////////////////////////////////////////////////

int FindFreeRandomOfficer()
{
	int Counter, OfficerIdx;
	string OfficerId;
	// special -->
	if (GetCharacterMaxOfficersQty(Pchar) <= (GetOfficerPassengerQuantity(Pchar) + GetRemovableCompanionsNumber(Pchar) - 1)) return -1;
	return 1;
}
void LandEnc_OfficerHired()
{
	ref sld = &Characters[int(Pchar.questTemp.HiringOfficerIDX)];
    sld.Money = 0; // деньги

	AddPassenger(pchar, sld, false);

	sld.location = "None";
	sld.Dialog.CurrentNode = "hired";
	/*if (sld.sex == "man") sld.greeting = "Gr_officer";
	else sld.greeting = "Gr_Danielle";*/
	// boal новый учёт зп -->
	sld.Payment = true;  // признак офицера для +1 предметов  
	sld.DontClearDead = true;  // не убирать труп
	// boal новый учёт зп <--
	DeleteAttribute(Pchar, "questTemp.HiringOfficerIDX");
	DeleteAttribute(sld, "LifeDay"); // постоянный
	SaveCurrentNpcQuestDateParam(sld, "HiredDate"); // дата найма
}

void LandEnc_OfficerStay()
{
    SetCharacterTask_Stay(Characters[int(Pchar.questTemp.HiringOfficerIDX)]);
    Characters[int(Pchar.questTemp.HiringOfficerIDX)].chr_ai.tmpl = LAI_TMPL_STAY;
    DeleteAttribute(Pchar, "questTemp.HiringOfficerIDX");
}   

void LandEnc_OfficerFired()
{
	ref sld = &Characters[int(Pchar.questTemp.FiringOfficerIDX)];
	CheckForReleaseOfficer(int(Pchar.questTemp.FiringOfficerIDX));
	RemovePassenger(Pchar, sld);
	RemoveCharacterCompanion(pchar, sld);
	LAi_SetCitizenType(sld);
	sld.location = "none";
	if (sld.sex != "woman")
	{
		sld.greeting = "Gr_Officer_Fired";
		if (sld.id == "Duran") 
		{
			if (CheckAttribute(pchar,"QuestInfo.TheFormerKnight"))
			{
				CloseQuestHeader("TheFormerKnight");
				AddQuestRecord("TheFormerKnight", "5");
				pchar.quest.SKD_DuranDied.over = "yes";
			}
			sld.greeting = "Duran_officer";
		}
	}
    sld.LifeDay = 0; // стереть при выходе
    DeleteAttribute(sld, "Payment"); // признак офицера для +1 предметов  
	DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX");
}			

// Jason: сделать офицера мушкетером. На данный момент возможно только для 3 офицеров-друзей главных героев: Тичингиту, Арчи, Алонсо. Для прочих нет моделей с нужной анимацией.
bool SetOfficerToMushketer(ref rCharacter, string sMushket, bool _ToMushketer) 
{
	int iItem;
	string sLastGun = "";
	string modelName;
	
	if(_ToMushketer && sMushket != "") // Делаем мушкетером
	{
		iItem = GetItemIndex(sMushket);
		if(iItem == -1) return false;
		//sLastGun = GetCharacterEquipByGroup(rCharacter, GUN_ITEM_TYPE);
		//rCharacter.DefaultAnimation = rCharacter.model.Animation;
		//rCharacter.IsMushketer = true; // Ставим флаг "мушкетер"
		//rCharacter.IsMushketer.MushketID = sMushket; // Запомним, какой мушкет надели
		//rCharacter.IsMushketer.LastGunID = sLastGun; // Запомним ID предыдущего пистоля
		//rCharacter.model = rCharacter.model;
		//rCharacter.model.animation = rCharacter.model; // Сменим анимацию
		//Characters_RefreshModel(rCharacter); // Обновим модель. Важно: обновлять модель нужно ДО экипировки мушкетом
		//rCharacter.equip.gun = rCharacter.IsMushketer.LastGunID;
		//RemoveCharacterEquip(rCharacter, GUN_ITEM_TYPE);
		EquipCharacterByItem(rCharacter, sMushket);
		/* EquipCharacterByItem(rCharacter, sMushket); // Экипируем мушкет
		rCharacter.Equip.TempGunID = sLastGun; // Пистоль оставляем экипированным, но в другой группе */
		if (!CheckAttribute(rCharacter, "MusketerDistance")) rCharacter.MusketerDistance = 10.0;
		//rCharacter.isMusketer = true;
		//rCharacter.isMusketer.weapon = true;
		LAi_SetOfficerType(rCharacter);
	}
	else // Делаем обычным фехтовальщиком
	{
		/* if(CheckAttribute(rCharacter, "equip.gun"))
		{
			aref arItm;
			Items_FindItem(rCharacter.equip.gun, &arItm);
			modelName = arItm.model;
		} */
		/* if(GetCharacterAnimation(rCharacter) == "mushketer")
		{
			rCharacter.model = FindStringBeforeChar(rCharacter.model, "_mush");
			rCharacter.model.animation = "man"; //Можно и через резерв
		} */
		//rCharacter.equip.gun = rCharacter.IsMushketer.LastGunID;
		//rCharacter.model.animation = rCharacter.model;
		RemoveCharacterEquip(rCharacter, MUSKET_ITEM_TYPE);
		//EquipCharacterByItem(rCharacter, rCharacter.IsMushketer.LastGunID);
		/* SendMessage(rCharacter, "lss", MSG_CHARACTER_SETMODEL, rCharacter.model, rCharacter.model.animation);
		SendMessage(rCharacter, "lsl", MSG_CHARACTER_EX_MSG, "SetMusketer", false); //Флаг в движок на мушкетёрский ИИ
		//SendMessage(rCharacter, "ls",  MSG_CHARACTER_SETGUN, modelName);
		Characters_RefreshModel(rCharacter); */
		/* rCharacter.model = FindStringBeforeChar(rCharacter.model, "_mush"); // Вернем модель и анимацию
		rCharacter.model.Animation = rCharacter.DefaultAnimation;
		Characters_RefreshModel(rCharacter);
		RemoveCharacterEquip(rCharacter, MUSKET_ITEM_TYPE); // cнимем мушкет
		
		if(rCharacter.IsMushketer.LastGunID != "" && GetCharacterItem(rCharacter, rCharacter.IsMushketer.LastGunID) > 0)
		{
			MusketEquipOldLogic(rCharacter, rCharacter.IsMushketer.LastGunID, false)
			//EquipCharacterByItem(rCharacter, rCharacter.IsMushketer.LastGunID); // Оденем прошлый пистоль
		}
		DeleteAttribute(rCharacter, "IsMushketer");
		DeleteAttribute(rCharacter, "Equip.TempGunID");
		DeleteAttribute(rCharacter, "MusketerDistance");
		DeleteAttribute(rCharacter, "isMusketer");
		if(CheckAttribute(rCharacter, "MusketerDistance")) DeleteAttribute(rCharacter, "MusketerDistance"); */
		LAi_SetOfficerType(rCharacter);
	}
	return true;
}

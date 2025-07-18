
//==========================================================================================
//Update events
//==========================================================================================

void LAi_Character_FrameUpdate()
{
	float dltTime = GetEventData();
	//Обновляем состояние персонажей
	LAi_AllCharactersUpdate(dltTime);
	//Задержка исполнения квестов
	LAi_QuestDelayProcess(dltTime);
}

void LAi_CharacterUpdate()
{
	//Параметры
	aref chr = GetEventData();
	float dltTime = GetEventData();
	if(LAi_CheckCharacter(chr, "LAi_CharacterUpdate") == false) return;
	//Процессируем соответствующий тип
	string func = chr.chr_ai.type;
	if(func != "")
	{
		func = "LAi_type_" + func + "_CharacterUpdate";
		call func(chr, dltTime);
	}
	//Процессируем соответствующий шаблон
	func = chr.chr_ai.tmpl;
	if(func == "") return;
	func = "LAi_tmpl_" + func + "_CharacterUpdate";
	call func(chr, dltTime);
}

//==========================================================================================
//EndTask events
//==========================================================================================

void LAi_CharacterEndTask()
{
	//Параметры
	string endTask = GetEventData();
	aref chr = GetEventData();
	if(LAi_CheckCharacter(chr, "LAi_CharacterEndTask") == false) return;
	string func = chr.chr_ai.tmpl;
	if(func == "") return;
	//Определяем отработавшую задачу
	bool isProcessed = false;
	switch(endTask)
	{
	case "Goto point":
		func = "LAi_tmpl_" + func + "_EndGoToPoint";
		isProcessed = true;
		break;
	case "Runto point":
		func = "LAi_tmpl_" + func + "_EndRunToPoint";
		isProcessed = true;
		break;
	case "Escape":
		func = "LAi_tmpl_" + func + "_EndEscape";
		isProcessed = true;
		break;
	}
	if(isProcessed != false)
	{
		call func(chr);
	}else{
		Trace("LAi_CharacterEndTask -> unknow end task <" + endTask + ">");
	}
}

//==========================================================================================
//TaskFailure events
//==========================================================================================

void LAi_CharacterTaskFailure()
{
	//Параметры
	string endTask = GetEventData();
	aref chr = GetEventData();
	if(LAi_CheckCharacter(chr, "LAi_CharacterTaskFailure") == false) return;
	string func = chr.chr_ai.tmpl;
	if(func == "") return;
	//Определяем невыполнившиюся задачу
	bool isProcessed = false;
	switch(endTask)
	{
	case "Goto point":
		func = "LAi_tmpl_" + func + "_FailureGoToPoint";
		isProcessed = true;
		break;
	case "Runto point":
		func = "LAi_tmpl_" + func + "_FailureRunToPoint";
		isProcessed = true;
		break;
	case "Follow character":
		func = "LAi_tmpl_" + func + "_FailureFollow";
		isProcessed = true;
		break;
	case "Fight":
		func = "LAi_tmpl_" + func + "_FailureFight";
		isProcessed = true;
		break;
	case "Escape":
		func = "LAi_tmpl_" + func + "_FailureEscape";
		isProcessed = true;
		break;
	}
	if(isProcessed != false)
	{
		call func(chr);
	}else{
		Trace("LAi_CharacterTaskFailure -> unknow failure task <" + endTask + ">");
	}
}

void LAi_CharacterBusyPos()
{
	//Параметры
	aref chr = GetEventData();
	float x = GetEventData();
	float y = GetEventData();
	float z = GetEventData();
	if(LAi_CheckCharacter(chr, "LAi_CharacterTaskFailure") == false) return;
	string func = chr.chr_ai.tmpl;
	if(func == "") return;
	func = "LAi_tmpl_" + func + "_BusyPos";
	call func(chr, x, y, z);
}


//==========================================================================================
//Follow character's events
//==========================================================================================

void LAi_CharacterFollowGo()
{
	//Параметры
	string endTask = GetEventData();
	aref chr = GetEventData();
	if(LAi_CheckCharacter(chr, "LAi_CharacterFollowGo") == false) return;
	string func = chr.chr_ai.tmpl;
	if(func == "") return;
	//Исполнение
	func = "LAi_tmpl_" + func + "_FollowGo";
	call func(chr);
}

void LAi_CharacterFollowStay()
{
	//Параметры
	string endTask = GetEventData();
	aref chr = GetEventData();
	if(LAi_CheckCharacter(chr, "LAi_CharacterFollowStay") == false) return;
	string func = chr.chr_ai.tmpl;
	if(func == "") return;
	//Исполнение
	func = "LAi_tmpl_" + func + "_FollowStay";
	call func(chr);
}

//==========================================================================================
//Fight character's events
//==========================================================================================

void LAi_CharacterFightGo()
{
	//Параметры
	string endTask = GetEventData();
	aref chr = GetEventData();
	if(LAi_CheckCharacter(chr, "LAi_CharacterFightGo") == false) return;
	string func = chr.chr_ai.tmpl;
	if(func == "") return;
	//Исполнение
	func = "LAi_tmpl_" + func + "_FightGo";
	call func(chr);
}

void LAi_CharacterFightStay()
{
	//Параметры
	string endTask = GetEventData();
	aref chr = GetEventData();
	if(LAi_CheckCharacter(chr, "LAi_CharacterFightStay") == false) return;
	string func = chr.chr_ai.tmpl;
	if(func == "") return;
	//Исполнение
	func = "LAi_tmpl_" + func + "_FightStay";
	call func(chr);
}

void LAi_CharacterAttack()
{
	aref attack = GetEventData();
	aref enemy = GetEventData();
	string attackType = GetEventData();
	bool isBlocked = GetEventData();
	/*if(attack.id == pchar.id)
	{
		pchar.combo.target = sti(enemy.index);
	}   */
	if(isBlocked == true)  // to_do
	{
		if(CheckCharacterPerk(attack, "sliding"))
		{
			int iRand = rand(100);
			// belamour legendary edition бонус за удачу
			if(iRand < 20 + GetCharacterSPECIALSimple(attack, SPECIAL_L))
			{
				isBlocked = false;
			}
		}
		if(GetCharacterEquipByGroup(enemy, BLADE_ITEM_TYPE) == "topor_07") isBlocked = false;
		if(CheckAttribute(attack, "cheats.sliding")) isBlocked = false;
		
	}
	if(CheckAttribute(enemy, "cheats.NOsliding")) isBlocked = true;
	//Реакция груп на атаку
	LAi_group_Attack(attack, enemy);
	
	// TUTOR-ВСТАВКА
	if(TW_IsActive())
	{
		if(objTask.land_fight == "1_Attack" && IsMainCharacter(attack))
		{
			if(attackType == "fast" || attackType == "force" || attackType == "break")
			{
				string sAttr = "FightAttack_" + attackType;
				TW_IncreaseCounter("land_fight", sAttr, 1);
				if(TW_CheckCounter("land_fight", "FightAttack_fast") && TW_CheckCounter("land_fight", "FightAttack_force") && TW_CheckCounter("land_fight", "FightAttack_break"))
					TW_FinishLand_Fight_1_Attack();
			}
		}
		if(objTask.land_fight == "2_Defence" && IsMainCharacter(enemy) && isBlocked)
		{
			TW_IncreaseCounter("land_fight", "FightDefence_block", 1);
			if(TW_CheckCounter("land_fight", "FightDefence_block") && TW_CheckCounter("land_fight", "FightDefence_parry"))
				TW_FinishLand_Fight_2_Defence();
		}
	}
	
	//Начисление повреждений
	LAi_ApplyCharacterAttackDamage(attack, enemy, attackType, isBlocked);
	//Обновим цель сразу
	LAi_group_UpdateTargets(enemy);
	string func = enemy.chr_ai.type;
	if(func == "") return;
	func = "LAi_type_" + func + "_Attacked";
	call func(enemy, attack);
	func = "LAi_type_" + enemy.chr_ai.type + "_CharacterUpdate";
	call func(enemy, 0.0001);
	
}

void LAi_CharacterFire()
{
	string sBullet, sGunPowder, sType, weaponID;
	aref attack = GetEventData();
	aref enemy = GetEventData();
	float kDist = GetEventData();	//0..1
	int isFindedEnemy = GetEventData();
	float fAimingTime = GetEventData();	// evganat - прицеливание
	
	//Rosarak. Чем стреляли?
	if(!CharUseMusket(attack))
	{
		sType = "gun";
		weaponID = GetCharacterEquipByGroup(attack, GUN_ITEM_TYPE);
	}
	else
	{
		sType = "musket";
		weaponID = GetCharacterEquipByGroup(attack, MUSKET_ITEM_TYPE);
	}
	sBullet = LAi_GetCharacterBulletType(attack, sType);
	if(rand(9) == 7 && GetCharacterEquipByGroup(attack, HAT_ITEM_TYPE) == "hat7")
	{
		notification(XI_ConvertString("hat7"), "Fortune");
		PlayStereoSound("interface\new_level.wav");
	}
	else
	{
		//Заряд персонажа
		if(!CheckAttribute(attack, "chr_ai." + sType + ".charge")) attack.chr_ai.(sType).charge = "0";
		float charge = stf(attack.chr_ai.(sType).charge) - 1.0;
		// boal gun bullet убираем пулю после выстрела -->
		TakeItemFromCharacter(attack, sBullet);
		// boal gun bullet убираем пулю после выстрела <--
		sGunPowder = LAi_GetCharacterGunpowderType(attack, sType);
		if(sGunPowder != "")
		{
			RemoveItems(attack, sGunPowder, 1); // Warship. Забираем порох
		}
		if(charge <= 0.0)
		{
			charge = 0.0;
			attack.chr_ai.(sType).chargeprc = "1";
		}
		// boal fix любой выстрел врубает дозарядку! -->
		attack.chr_ai.(sType).chargeprc = "1";
		// boal <--
		attack.chr_ai.(sType).charge = charge;
	}
	// ugeen -> мультиурон и прочее(27.07.10)
		
	//weaponID = GetCharacterEquipByGroup(attack, sType);
	aref weapon;
	Items_FindItem(weaponID, &weapon);
	// belamour расширенное издание разрыв ствола от х2 боеприпаса
	if(HasSubStr(sBullet, "double") && !IsEquipCharacterByArtefact(attack, "indian_2") && GetCharacterEquipByGroup(attack, CIRASS_ITEM_TYPE) != "cirass10")
	{
		LAi_Explosion(attack, rand(40));
  		if(GetCharacterItem(attack, weaponID) <= 1) RemoveCharacterEquip(attack, weapon.groupID);
        TakeItemFromCharacter(attack, weaponID);
		if(ShowCharString()) Log_Chr(attack, XI_ConvertString("GunBreakLog"));
		else Log_Info(XI_ConvertString("GunBreak1") + GetCharacterFullName(attack.id) + XI_ConvertString("GunBreak2"));
		return;
	}
	// belamour legendary edition пороховой тестер уменьшает разрыв ствола -->
	if(attack.id != "Blaze" && CheckAttribute(attack, "chr_ai."+sType+".misfire") && sti(attack.chr_ai.(sType).misfire) > 0 && rand(100)*isEquippedArtefactUse(attack, "indian_2", 1.0, 2.0) < sti(attack.chr_ai.(sType).misfire) && !HasSubStr(weapon.id, "mushket") && GetCharacterEquipByGroup(attack, CIRASS_ITEM_TYPE) != "cirass10")
	{
		LAi_Explosion(attack, rand(20));
  		if(GetCharacterItem(attack, weaponID) <= 1) RemoveCharacterEquip(attack, weapon.groupID);
        TakeItemFromCharacter(attack, weaponID);
		if(ShowCharString()) Log_Chr(attack, XI_ConvertString("GunBreakLog"));
		else Log_Info(XI_ConvertString("GunBreak1") + GetCharacterFullName(attack.id) + XI_ConvertString("GunBreak2"));
		return;
	}
	
	//Если промахнулись, то ничего не делаем
	if(isFindedEnemy == 0)
	{
		//здесь можно поднимать тревогу в случае близкого выстрела
		return;
	}
	
	// evganat - хедшот
	int isHeadShot = GetEventData();
	
	if(CheckAttribute(attack, "chr_ai.explosion" ) && sti(attack.chr_ai.explosion) > 0)
	{	
		float x, y, z;						
		GetCharacterPos(enemy, &x, &y, &z);
		CreateParticleSystemX("blood_shoot", x, y, z, x, y, z, 0);	
		PlayStereoSound("Sea Battles\cannon_fire_03.wav");
	}	
	
	if(CheckAttribute(attack, "chr_ai." + sType + ".multidmg") && sti(attack.chr_ai.(sType).multidmg) > 0)
	{
		int num = FindNearCharacters(enemy, 2.5, -1.0, -1.0, 0.001, false, true);
		for (int j = 0; j < num; j++)
		{
			int idx = -1;
			if(CheckAttribute(chrFindNearCharacters[j], "index")) idx = sti(chrFindNearCharacters[j].index);	
			if(idx == -1) continue;
			ref findCh;
			findCh = GetCharacter(idx);	
			if(findCh.chr_ai.group != LAI_GROUP_PLAYER)
			{
				LAi_ApplyCharacterFireDamage(attack, &Characters[idx], kDist, fAimingTime, isHeadShot, 1);
			}	
			
			if(CheckAttribute(attack, "chr_ai."+sType+".stun" ) && sti(attack.chr_ai.(sType).stun) > 0 && !LAi_IsFightMode(enemy) && !IsMainCharacter(enemy))
			{
				if(CheckAttribute(enemy, "cirassId"))
				{
					if(sti(attack.chr_ai.Stun_C) > 0) 
					{
						LAi_Stunned_StunCharacter(enemy, 10, true);
					}
				}
				else
				{
					if(sti(attack.chr_ai.(sType).Stun_NC) > 0) 
					{
						LAi_Stunned_StunCharacter(enemy, 10, true);
					}
				}		
			}			
									
			if( CheckAttribute(attack, "chr_ai."+sType+".selfdmg" ) && sti(attack.chr_ai.(sType).selfdmg) > 0 && findCh.id == attack.id && rand(4) == 1)	
			{
				LAi_ApplyCharacterDamage( &Characters[idx], 10 + rand(sti(weapon.dmg_min) - 10), "fire" );
				if(stf(attack.chr_ai.hp) < 1.0) attack.chr_ai.hp = 1 + makeint(rand(10));
			}
		}
	}

	if(CheckAttribute(attack, "chr_ai."+sType+".stun" ) && sti(attack.chr_ai.(sType).stun) > 0 && !LAi_IsFightMode(enemy) && !IsMainCharacter(enemy))
	{
		if(CheckAttribute(enemy, "cirassId"))
		{
			if(sti(attack.chr_ai.(sType).Stun_C) > 0) 
			{
				LAi_Stunned_StunCharacter(enemy, 10, true);
			}
		}
		else
		{		
			if(sti(attack.chr_ai.(sType).Stun_NC) > 0) 
			{
				LAi_Stunned_StunCharacter(enemy, 10, true);
			}
		}		
	}
	// <-- ugeen
	
	//Реакция груп на атаку
	LAi_group_Attack(attack, enemy);
	//Начисление повреждений
	LAi_ApplyCharacterFireDamage(attack, enemy, kDist, fAimingTime, isHeadShot, 1);
	if(CheckAttribute(attack, "chr_ai." + sType + ".multidmg") && sti(attack.chr_ai.(sType).multidmg) > 0)
	{
		if(stf(enemy.chr_ai.hp) < 1.0 && enemy.chr_ai.group == LAI_GROUP_PLAYER) enemy.chr_ai.hp = 5;
		LAi_CheckKillCharacter(enemy);
	}
	
	//Исполнение типа
	string func = attack.chr_ai.type;
	if(func == "") return;
	func = "LAi_type_" + func + "_Fire";
	call func(attack, enemy, kDist, isFindedEnemy != 0);
	//Обновим цель сразу
	LAi_group_UpdateTargets(enemy);
	func = enemy.chr_ai.type;
	if(func == "") return;
	func = "LAi_type_" + func + "_Attacked";
	call func(enemy, attack);
	func = "LAi_type_" + enemy.chr_ai.type + "_CharacterUpdate";
	call func(enemy, 0.0001);
}

bool LAi_tmp_return_bool;
bool LAi_CharacterIsFire()
{
	aref chr = GetEventData();
	string func = chr.chr_ai.tmpl;
	if(func == "") return;
	//Исполнение
	func = "LAi_tmpl_" + func + "_IsFire";
	LAi_tmp_return_bool = call func(chr);
	return LAi_tmp_return_bool;
}

bool LAi_CharacterIsFight()
{
	aref chr = GetEventData();
	
	if (CheckAttribute(chr, "DeadWithBlade")) {
		return true;
	}
	
	string func = chr.chr_ai.tmpl;
	if(func == "") return false;
	//Исполнение
	func = "LAi_tmpl_" + func + "_IsFight";
	LAi_tmp_return_bool = call func(chr);
	return LAi_tmp_return_bool;
}

//==========================================================================================
//Escape events
//==========================================================================================

void LAi_CharacterEscapeSlide()
{
	//Параметры
	string endTask = GetEventData();
	aref chr = GetEventData();
	if(LAi_CheckCharacter(chr, "LAi_CharacterEscapeSlide") == false) return;
	string func = chr.chr_ai.tmpl;
	if(func == "") return;
	//Исполнение
	func = "LAi_tmpl_" + func + "_EscapeSlide";
	call func(chr);
}

//==========================================================================================
//Collision events
//==========================================================================================

void LAi_CharacterColThreshold()
{
	//Параметры
	string endTask = GetEventData();
	aref chr = GetEventData();
	if(LAi_CheckCharacter(chr, "LAi_CharacterColThreshold") == false) return;
	string func = chr.chr_ai.tmpl;
	if(func == "") return;
	//Исполнение
	func = "LAi_tmpl_" + func + "_ColThreshold";
	call func(chr);
}

//==========================================================================================
//Animation events
//==========================================================================================

void LAi_Character_EndAction()
{
	//Параметры
	aref chr = GetEventData();
	if(LAi_CheckCharacter(chr, "LAi_Character_EndAction") == false) return;
	string func = chr.chr_ai.tmpl;
	if(func == "") return;
	//Исполнение
	func = "LAi_tmpl_" + func + "_EndAction";
	call func(chr);
}


//==========================================================================================
//Dead event
//==========================================================================================

void LAi_Character_Dead_Process(aref chr)
{
	if (sti(chr.index) == nMainCharacterIndex || sti(chr.index) == sti(CharacterRef.index)) {
		DialogExit();
	}
	LAi_CharacterLogoff(chr);
	if(sti(chr.index) != nMainCharacterIndex)
	{
//navy --> смерть ПГГ
		if (CheckAttribute(chr, "PGGAi"))
		{
			PGG_CheckDead(chr);
		}
//navy <--
		//Подождём, а затем удалим персонажа
		// boal трупы не убирать
        if (MOD_DEAD_CLEAR == "On" && !CheckAttribute(chr, "DontClearDead"))
        {
            PostEvent("LAi_event_Character_Dead", MOD_DEAD_CLEAR_TIME * 1000, "i", chr);
        }
        // убираем совместителя в CharacterDeadProcess
        
		//Реинкарнируем
		LAi_GenerateFantomFromMe(chr);
		//Посмотрим группу
		LAi_group_CheckGroupQuest(chr);
	}
	else
	{
		//Доигрались...
		if(!LAi_IsBoardingProcess())
		{
			if (loadedLocation.type == "town")
				PostEvent("LAi_event_GameOver", 5000, "s", "town");
			else
			{
				if (loadedLocation.type == "underwater")
					PostEvent("LAi_event_GameOver", 5000, "s", "sea");
				else
					PostEvent("LAi_event_GameOver", 5000, "s", "land");
			}
		}
		else
		{
			PostEvent("LAi_event_GameOver", 5000, "s", "boarding");
		}
	}
}

#event_handler("LAi_event_Character_Dead", "LAi_Character_Dead_Event");
void LAi_Character_Dead_Event()
{
	aref chr = GetEventData();
	if (IsEntity(&chr))  //fix
	{
		// boal dead can be searched 14.12.2003 -->
		Dead_DelLoginedCharacter(chr); // трем
		// boal dead can be searched 14.12.2003 <--
		CharacterExitFromLocation(chr);
	}
}

#event_handler("LAi_event_GameOver", "LAi_GameOver");
void LAi_GameOver()
{
	string str = GetEventData();
	GameOver(str);
}



//==========================================================================================
//Internal events
//==========================================================================================

//------------------------------------------------------------------------------------------
//Сообщение об окончании работы темплейта
//------------------------------------------------------------------------------------------

void LAi_Character_TemplateComplite(aref chr, string tmplName)
{

	int index = sti(chr.index);
	PostEvent("LAi_event_Character_TemplateComplite", 1, "ls", index, tmplName);

}

#event_handler("LAi_event_Character_TemplateComplite", "LAi_Character_TemplateComplite_Event");
void LAi_Character_TemplateComplite_Event()
{
	int index = GetEventData();
	string tmpl = GetEventData();
	ref chr = &Characters[index];
	// boal fix -->
	string func = "";
	if ( CheckAttribute(chr, "chr_ai.type"))
	{
	    func = chr.chr_ai.type;
	}
	// boal fix <--
	if(func != "")
	{
		func = "LAi_type_" + func + "_TemplateComplite";
		call func(chr, tmpl);
	}
}

//------------------------------------------------------------------------------------------
//Запрос локатора
//------------------------------------------------------------------------------------------

void LAi_Character_FreeLocator(aref chr, string group, string locator)
{
	int index = sti(chr.index);
	PostEvent("LAi_event_Character_FreePos", 1, "lss", index, group, locator);
}

#event_handler("LAi_event_Character_FreePos", "LAi_Character_FreePos_Event");
void LAi_Character_FreePos_Event()
{
	int index = GetEventData();
	string group = GetEventData();
	string locator = GetEventData();
	for(int i = 0; i < LAi_numloginedcharacters; i++)
	{
		int idx = LAi_loginedcharacters[i];
		if(idx >= 0)
		{
			if(idx != index)
			{
				float dist;
				if(GetCharacterDistByLoc(&Characters[idx], group, locator, &dist))
				{
					if(dist < 0.8)
					{
						string func = Characters[idx].chr_ai.tmpl;
						if(func == "") return;
						//Исполнение
						func = "LAi_tmpl_" + func + "_FreePos";
						call func(&Characters[idx], &Characters[index]);
					}
				}
			}
		}
	}
}


//------------------------------------------------------------------------------------------
//Запрос на диалог
//------------------------------------------------------------------------------------------

void LAi_Character_NeedDialog(aref chr, aref by)
{
	if(IsEntity(&by))
	{
		string func = chr.chr_ai.type;
		if(func != "")
		{
			func = "LAi_type_" + func + "_NeedDialog";
			call func(by, chr);
		}
	}
}

//Запрос на диалог, если возвратить true то в этот момент можно начать диалог
bool LAi_Character_CanDialog(aref chr, aref by)
{
	if(IsEntity(&by))
	{
		bool isDisable = false;
		if(CheckAttribute(chr, "chr_ai.disableDlg"))
		{
			if(sti(chr.chr_ai.disableDlg) != 0) isDisable = true;
		}
		if(isDisable == false)
		{
			string func = by.chr_ai.type;
			if(func != "")
			{
				func = "LAi_type_" + func + "_CanDialog";
				return call func(by, chr);
			}
		}
	}
	return false;
}

//Начать диалог
void LAi_Character_StartDialog(aref chr, aref by)
{
	if(IsEntity(&by))
	{
		string func = by.chr_ai.type;
		if(func != "")
		{
			func = "LAi_type_" + func + "_StartDialog";
			call func(by, chr);
		}
	}
}

//Закончить диалог
void LAi_Character_EndDialog(aref chr, aref by)
{
	if(IsEntity(&by))
	{
		string func = by.chr_ai.type;
		if(func != "")
		{
			func = "LAi_type_" + func + "_EndDialog";
			call func(by, chr);
		}
	}
}
// Привязать к/отвязать от модели персонажа какую нить модель (предмет)
void LAi_CharacterItemAction()
{
	aref chr = GetEventData();
	string sActionName = GetEventData();
	int nItemIndex = GetEventData();

	switch(sActionName)
	{
	case "reset": LAi_UntieItemFromCharacter(chr,nItemIndex); break;
	case "set": LAi_TieItemToCharacter(chr,nItemIndex); break;
	}
}
void LAi_UntieItemFromCharacter(aref chr, int nItemIndex)
{
	if( nItemIndex<0 ) return;
	SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "UntieItem", nItemIndex);
}
void LAi_TieItemToCharacter(aref chr, int nItemIndex)
{
	if( nItemIndex<0 ) return;

	string sModel = "HandsItems\cup";
	string sLocator = "Saber_hand";

	string sitm = "TiedItems.itm"+nItemIndex;
	if( CheckAttribute(chr,sitm) )
	{
		if( CheckAttribute(chr,sitm+".model") ) {
			sModel = chr.(sitm).model;
		}
		if( CheckAttribute(chr,sitm+".locator") ) {
			sLocator = chr.(sitm).locator;
		}
	}

	SendMessage(chr, "lslss", MSG_CHARACTER_EX_MSG, "TieItem", nItemIndex, sModel, sLocator);
}

#event_handler("Location_CharacterFireShards","Location_CharacterFireShards");
void Location_CharacterFireShards()
{
	aref attack = GetEventData();
	aref enemy = GetEventData();
	float fAimingTime = GetEventData();
	int nShots = GetEventData();
	int nHeadShots = GetEventData();
	
	string sType;
	if(!CharUseMusket(attack))
		sType = "gun";
	else
		sType = "musket";
	
	if(CheckAttribute(attack, "chr_ai."+sType+".stun" ) && sti(attack.chr_ai.(sType).stun) > 0 && !LAi_IsFightMode(enemy) && !IsMainCharacter(enemy))
	{
		if(CheckAttribute(enemy, "cirassId"))
		{
			if(sti(attack.chr_ai.(sType).Stun_C) > 0) 
				LAi_Stunned_StunCharacter(enemy, 10, true);
		}
		else
		{		
			if(sti(attack.chr_ai.(sType).Stun_NC) > 0) 
				LAi_Stunned_StunCharacter(enemy, 10, true);
		}		
	}
	
	LAi_group_Attack(attack, enemy);
	
	if(nHeadShots > 0)
		LAi_ApplyCharacterFireDamage(attack, enemy, 1.0, fAimingTime, true, nHeadShots);
	LAi_CheckKillCharacter(enemy);
	
	if(nShots > 0)
		LAi_ApplyCharacterFireDamage(attack, enemy, 1.0, fAimingTime, false, nShots);
	if(stf(enemy.chr_ai.hp) < 1.0 && enemy.chr_ai.group == LAI_GROUP_PLAYER) 
		enemy.chr_ai.hp = 5;
	LAi_CheckKillCharacter(enemy);
	
	string func = attack.chr_ai.type;
	if(func == "")
		return;
	func = "LAi_type_" + func + "_Fire";
	call func(attack, enemy, 1.0, true);
	LAi_group_UpdateTargets(enemy);
	func = enemy.chr_ai.type;
	if(func == "")
		return;
	func = "LAi_type_" + func + "_Attacked";
	call func(enemy, attack);
	func = "LAi_type_" + enemy.chr_ai.type + "_CharacterUpdate";
	call func(enemy, 0.0001);
}

#event_handler("Location_CharacterFireShardEnd","Location_CharacterFireShardEnd");
void Location_CharacterFireShardEnd()
{
	string sBullet, sGunPowder, sType, weaponID;
	aref attack = GetEventData();
	
	//Rosarak. Чем стреляли?
	if(!CharUseMusket(attack))
	{
		sType = "gun";
		weaponID = GetCharacterEquipByGroup(attack, GUN_ITEM_TYPE);
	}
	else
	{
		sType = "musket";
		weaponID = GetCharacterEquipByGroup(attack, MUSKET_ITEM_TYPE);
	}
	
	//Заряд персонажа
	if(!CheckAttribute(attack, "chr_ai." + sType + ".charge")) attack.chr_ai.(sType).charge = "0";
	float charge = stf(attack.chr_ai.(sType).charge) - 1.0;
	// boal gun bullet убираем пулю после выстрела -->
	sBullet = LAi_GetCharacterBulletType(attack, sType);
	TakeItemFromCharacter(attack, sBullet);
	// boal gun bullet убираем пулю после выстрела <--
	sGunPowder = LAi_GetCharacterGunpowderType(attack, sType);
	if(sGunPowder != "")
	{
		RemoveItems(attack, sGunPowder, 1); // Warship. Забираем порох
	}
	if(charge <= 0.0)
	{
		charge = 0.0;
		attack.chr_ai.(sType).chargeprc = "1";
	}
	// boal fix любой выстрел врубает дозарядку! -->
	attack.chr_ai.(sType).chargeprc = "1";
	// boal <--
	attack.chr_ai.(sType).charge = charge;
	// ugeen -> мультиурон и прочее(27.07.10)
		
	//weaponID = GetCharacterEquipByGroup(attack, sType);
	aref weapon;
	Items_FindItem(weaponID, &weapon);
	// belamour расширенное издание разрыв ствола от х2 боеприпаса
	if(HasSubStr(sBullet, "double") && !IsEquipCharacterByArtefact(attack, "indian_2") && GetCharacterEquipByGroup(attack, CIRASS_ITEM_TYPE) != "cirass10")
	{
		LAi_Explosion(attack, rand(40));
  		if(GetCharacterItem(attack, weaponID) <= 1) RemoveCharacterEquip(attack, weapon.groupID);
        TakeItemFromCharacter(attack, weaponID);
		if(ShowCharString()) Log_Chr(attack, XI_ConvertString("GunBreakLog"));
		else Log_Info(XI_ConvertString("GunBreak1") + GetCharacterFullName(attack.id) + XI_ConvertString("GunBreak2"));
		return;
	}
	// belamour legendary edition пороховой тестер уменьшает разрыв ствола -->
	if(attack.id != "Blaze" && CheckAttribute(attack, "chr_ai."+sType+".misfire") && sti(attack.chr_ai.(sType).misfire) > 0 && rand(100)*isEquippedArtefactUse(attack, "indian_2", 1.0, 2.0) < sti(attack.chr_ai.misfire) && !HasSubStr(weapon.id, "mushket") && GetCharacterEquipByGroup(attack, CIRASS_ITEM_TYPE) != "cirass10")
	{
		LAi_Explosion(attack, rand(20));
  		if(GetCharacterItem(attack, weaponID) <= 1) RemoveCharacterEquip(attack, weapon.groupID);
        TakeItemFromCharacter(attack, weaponID);
		if(ShowCharString()) Log_Chr(attack, XI_ConvertString("GunBreakLog"));
		else Log_Info(XI_ConvertString("GunBreak1") + GetCharacterFullName(attack.id) + XI_ConvertString("GunBreak2"));
		return;
	}
	
	if(CheckAttribute(attack, "chr_ai.explosion" ) && sti(attack.chr_ai.explosion) > 0)
		PlayStereoSound("Sea Battles\cannon_fire_03.wav");
}
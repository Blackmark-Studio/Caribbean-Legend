

#define LAI_TMPL_DIALOG		"dialog"

/*
	Возможные состояния:
		"wait"		ждёт начала диалога
		"dialog"	разговаривает
*/


bool LAi_tmpl_SetDialog(ref chr, ref by, float dlgTime)
{
	if(!LAi_tmpl_dialog_InitTemplate(chr)) return false;
	chr.chr_ai.tmpl.dialog = "";
	chr.chr_ai.tmpl.time = "0";
	chr.chr_ai.tmpl.dlgtime = "-1";	
	chr.chr_ai.tmpl.state = "wait";
	DeleteAttribute(chr, "chr_ai.tmpl.poklon");
	LAi_tmpl_dialog_StartDialog(chr, by, dlgTime);
	return true;
}

//Если мы пасивны, запускаем шаблон без времени завершения
bool LAi_tmpl_SetActivatedDialog(ref chr, ref by)
{
	if(!LAi_tmpl_dialog_InitTemplate(chr)) return false;
	chr.chr_ai.tmpl.dialog = by.index;
	chr.chr_ai.tmpl.time = "0";
	chr.chr_ai.tmpl.dlgtime = "-1";	
	chr.chr_ai.tmpl.state = "dialog";
	LAi_tmpl_dialog_CharacterUpdate(chr, 0.0);
	return true;
}

void LAi_tmpl_dialog_NoAni(ref chr)
{
	chr.chr_ai.tmpl.noani = "1";
}

//Остановить диалог между NPC
bool LAi_tmpl_dialog_StopNPC(ref chr)
{
	if(chr.chr_ai.tmpl.state == "dialog")
	{
		//Если один из беседующих игрок, то не прекращаем диалог
		int idx = int(chr.chr_ai.tmpl.dialog);
		if(nMainCharacterIndex == int(chr.index)) return false;
		if(nMainCharacterIndex == idx) return false;
		//Операнивно всё сворачиваем
		CharacterPlayAction(chr, "");
		CharacterPlayAction(&Characters[idx], "");
		LAi_Character_EndDialog(chr, &Characters[idx]);
		LAi_Character_EndDialog(&Characters[idx], chr);
		chr.chr_ai.tmpl.dialog = "";
		chr.chr_ai.tmpl.time = "0";
		chr.chr_ai.tmpl.dlgtime = "-1";	
		chr.chr_ai.tmpl.state = "wait";
	}
	return true;
}


bool LAi_tmpl_dialog_InitTemplate(ref chr)
{
	SendMessage(&chr, "ls", MSG_CHARACTER_EX_MSG, "ForcedStopMove");	// evganat - фикс движения в диалоге
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "LockFightMode", false);
	CharacterPlayAction(chr, "");
	bool isNew = false;
	if(CheckAttribute(chr, "chr_ai.tmpl"))
	{
		if(chr.chr_ai.tmpl != LAI_TMPL_DIALOG) isNew = true;
	}else{
		isNew = true;
	}
	if(isNew)
	{
		DeleteAttribute(chr, "chr_ai.tmpl");
		chr.chr_ai.tmpl = LAI_TMPL_DIALOG;
		chr.chr_ai.tmpl.state = "wait";
		chr.chr_ai.tmpl.dialog = "";
		chr.chr_ai.tmpl.time = "0";
		chr.chr_ai.tmpl.dlgtime = "-1";
		if(LAi_IsInitedAI) SetCharacterTask_Stay(chr);
	}else{
		chr.chr_ai.tmpl.wait = "0";
		if(!CheckAttribute(chr, "chr_ai.tmpl.state")) chr.chr_ai.tmpl.state = "wait";
		if(chr.chr_ai.tmpl.state == "falure") chr.chr_ai.tmpl.state = "wait";
		if(!CheckAttribute(chr, "chr_ai.tmpl.time")) chr.chr_ai.tmpl.time = "0";
		if(!CheckAttribute(chr, "chr_ai.tmpl.dlgtime")) chr.chr_ai.tmpl.dlgtime = "-1";		
		if(!CheckAttribute(chr, "chr_ai.tmpl.dialog"))
		{
			chr.chr_ai.tmpl.dialog = "";
			chr.chr_ai.tmpl.state = "wait";
		}else{
			if(chr.chr_ai.tmpl.dialog == "") chr.chr_ai.tmpl.state = "wait";
		}
		if(chr.chr_ai.tmpl.state == "wait")
		{
			chr.chr_ai.tmpl.dialog = "";
			chr.chr_ai.tmpl.time = "0";
			chr.chr_ai.tmpl.dlgtime = "-1";
		}
		if(LAi_IsInitedAI) LAi_tmpl_dialog_CharacterUpdate(chr, 0.0);
	}
	chr.chr_ai.tmpl.phrasetime = rand(3);
	return true;
}

//Возможно ли завенсти диалог
bool LAi_tmpl_dialog_IsActive(ref chr)
{	
	if(chr.chr_ai.tmpl.state == "wait") return false;
	return true;
}


//Процессирование шаблона персонажа
void LAi_tmpl_dialog_CharacterUpdate(ref chr, float dltTime)
{
	float time, fAng;
	aref tmpl;
	float xAng = 0;
	float zAng = 0;
	int animChoice = 0;
	makearef(tmpl, chr.chr_ai.tmpl);
	int idx = int(chr.chr_ai.tmpl.dialog);
	if(LAi_IsDead(&Characters[idx]))
	{
		LAi_tmpl_dialog_StopNPC(chr);
		return;
	}
	if(LAi_IsDead(chr))
	{
		LAi_tmpl_dialog_StopNPC(chr);
		return;
	}
	if (int(chr.index) == nMainCharacterIndex && !CheckAttribute(chr, "QuestDiag")) return;
	//Если в диалоге, направляемся на персонажа
	if(tmpl.state == "dialog")
	{
		//Проверяем время ведения диолога
		float dlgtime = float(tmpl.dlgtime);
		if(dlgtime >= 0)
		{
			//Мы ведём диалог
			time = float(tmpl.time) + dltTime;
			tmpl.time = time;
			if(time > dlgtime)
			{
				CharacterPlayAction(chr, "");
				CharacterPlayAction(&Characters[idx], "");
				LAi_Character_EndDialog(chr, &Characters[idx]);
				LAi_Character_EndDialog(&Characters[idx], chr);
				chr.chr_ai.tmpl.dialog = "";
				chr.chr_ai.tmpl.time = "0";
				chr.chr_ai.tmpl.dlgtime = "-1";	
				chr.chr_ai.tmpl.state = "wait";
				return;
			}
		}
	}	
	//если нищий и сидит - ничего не крутим
	if (chr.chr_ai.type == LAI_TYPE_POOR && int(chr.chr_ai.type.SitState)) return;
	if (chr.model.animation == "mushketer") return;
	
	if (chr.chr_ai.type == LAI_TYPE_OFFICER && bCabinStarted)
	{
		if(chr.location.locator == "sit1" && NeedCabinTmpl())
		{
			time = float(chr.chr_ai.tmpl.phrasetime) - dltTime;
			chr.chr_ai.tmpl.phrasetime = time;
			if(time < 0.0)
			{
				CharacterPlayAction(chr, "Sit_Cabin_Dialog_" + (rand(4)+1));
				chr.chr_ai.tmpl.phrasetime = 20;
			}
		}
		return;
	}

	if (chr.chr_ai.type == LAI_TYPE_HUBER) 
	{
		time = float(chr.chr_ai.tmpl.phrasetime) - dltTime;
		chr.chr_ai.tmpl.phrasetime = time;
		if(time < 0.0)
		{
			if(!CheckAttribute(chr, "chr_ai.tmpl.noani"))
			{
				if (CheckAttribute(chr, "chr_ai.tmpl.firstAnim"))
				{
					CharacterPlayAction(chr, "Gov_Dialog_" + chr.chr_ai.tmpl.firstAnim);
					DeleteAttribute(chr, "chr_ai.tmpl.firstAnim");
				}
				else CharacterPlayAction(chr, "Gov_Dialog_" + (rand(2)+1));
				chr.chr_ai.tmpl.phrasetime = 20;
			}
		}
		return;
	}
	//если диалоговый нпс сидит
	if (chr.chr_ai.type == LAI_TYPE_SIT)
	{
		if (CheckAttribute(chr, "nonTable")) return; //режеми диалоговые анимации сидунам не за столом
		time = float(chr.chr_ai.tmpl.phrasetime) - dltTime;
		if(time < 0.0)
		{			
			int num = FindNearCharacters(chr, 2.5, -1.0, 0.0, 0.0, false, false);
			for(int i = 0; i < num; i++)
			{
				if(chrFindNearCharacters[i].index == idx)
				{
					GetCharacterAy(chr, &fAng);
					xAng = float(chrFindNearCharacters[i].dx) * cos(fAng) - float(chrFindNearCharacters[i].dz) * sin(fAng);
					zAng = float(chrFindNearCharacters[i].dz) * cos(fAng) + float(chrFindNearCharacters[i].dx) * sin(fAng);
					//Log_SetEternalString("xAng: " + xAng + "    zAng: " + zAng + "   fAng: " + fAng);
					break;
				}
			}
			if(!CheckAttribute(chr, "chr_ai.tmpl.noani"))
			{
				if (zAng < 0)
				{	//если нпс сзади
					if (xAng > 0)
					{
						CharacterPlayAction(chr, "Sit_Dialog2"); //справа
						chr.chr_ai.tmpl.phrasetime = 60.0;
					}
					if (xAng < 0)
					{
						CharacterPlayAction(chr, "Sit_Dialog1"); //слева
						chr.chr_ai.tmpl.phrasetime = 60.0;
					}
				}
				else
				{	//если нпс спереди
					if (xAng > 0.9)
					{
						CharacterPlayAction(chr, "Sit_Dialog2"); //справа
						chr.chr_ai.tmpl.phrasetime = 60.0;
					}
					if (xAng < -0.9)
					{
						CharacterPlayAction(chr, "Sit_Dialog1"); //слева
						chr.chr_ai.tmpl.phrasetime = 60.0;
					}
				}
				if (xAng == 0)
				{
					CharacterPlayAction(chr, "Sit_Dialog0");
					chr.chr_ai.tmpl.phrasetime = 60.0;
				}
			}
		}
		else
		{
			chr.chr_ai.tmpl.phrasetime = time;
		}
	}
	//если диалоговый нпс стоит
	else
	{				
		//Всегда стоим
		SetCharacterTask_Stay(chr);
		//Выкидываем всякие жесты и фразочки
		time = float(chr.chr_ai.tmpl.phrasetime) - dltTime;
		if(time < 0.0)
		{
			string sTemp;
            if(CheckAttribute(chr, "QuestDiag"))
            {
                sTemp = chr.QuestDiag;
                sTemp = call sTemp(chr);
                if(sTemp != "") CharacterPlayAction(chr, sTemp);
            }
            else
            {
                if(!CheckAttribute(chr, "chr_ai.tmpl.noani"))
                {
                    if(CheckAttribute(chr,"sex"))
                    {
                        if(chr.sex == "woman") 
                        {
                            if (characters[int(chr.chr_ai.tmpl.dialog)].sex == "man" && !CheckAttribute(chr, "chr_ai.tmpl.poklon"))
                            {
                                sTemp = "knicksen";
                                chr.chr_ai.tmpl.poklon = true;
                            }						
                            else sTemp = "dialog_stay" + (rand(8)+1);
                        }
                        else 
                        {
                            if (characters[int(chr.chr_ai.tmpl.dialog)].sex == "woman" && !CheckAttribute(chr, "chr_ai.tmpl.poklon"))
                            {
                                sTemp = "Poklon";
                                chr.chr_ai.tmpl.poklon = true;
                            }
                            else sTemp = "dialog_stay" + (rand(14)+1);
                        }
                    }				
                    CharacterPlayAction(chr, sTemp);
                }
            }
			if(float(tmpl.dlgtime) >= 0.0)
			{	
//				string snd = "citizen_male";
//				if(CheckAttribute(chr,"sex"))
//				{
//					if(chr.sex == "woman") snd = "citizen_female";
//				}
//				LAi_CharacterPlaySound(chr, snd);
			}
			chr.chr_ai.tmpl.phrasetime = 5 + rand(1);
		}
        else
        {
			chr.chr_ai.tmpl.phrasetime = time;
		}
	}
}

//Персонаж выполнил команду  go to point
void LAi_tmpl_dialog_EndGoToPoint(ref chr)
{
}

//Персонаж провалил команду  go to point
void LAi_tmpl_dialog_FailureGoToPoint(ref chr)
{
}

//Персонаж выполнил команду  run to point
void LAi_tmpl_dialog_EndRunToPoint(ref chr)
{	
}

//Персонаж провалил команду  run to point
void LAi_tmpl_dialog_FailureRunToPoint(ref chr)
{	
}

//Персонаж не может добраться до точки назначения
void LAi_tmpl_dialog_BusyPos(ref chr, float x, float y, float z)
{
}

//Персонаж начал перемещение за другим
void LAi_tmpl_dialog_FollowGo(ref chr)
{
}

//Персонаж начал дошёл до другого персонажа
void LAi_tmpl_dialog_FollowStay(ref chr)
{	
}

//Персонаж провалил команду  dialog character
void LAi_tmpl_dialog_FailureFollow(ref chr)
{	
}


//Персонаж начал перемещение за другим
void LAi_tmpl_dialog_FightGo(ref chr)
{
}

//Персонаж начал дошёл до другого персонажа
void LAi_tmpl_dialog_FightStay(ref chr)
{
}

//Персонаж провалил команду  Fight
void LAi_tmpl_dialog_FailureFight(ref chr)
{
}

//Можно ли стрелять
bool LAi_tmpl_dialog_IsFire(ref chr)
{	
	return false;
}

//Можно ли использовать оружие
bool LAi_tmpl_dialog_IsFight(ref chr)
{
	return false;
}


//Персонаж выполнил команду  escape
void LAi_tmpl_dialog_EndEscape(ref chr)
{
}

//Персонаж скользит вдоль патча
void LAi_tmpl_dialog_EscapeSlide(ref chr)
{
}

//Персонаж провалил команду  escape
void LAi_tmpl_dialog_FailureEscape(ref chr)
{
}


//Персонаж толкается с другими персонажами
void LAi_tmpl_dialog_ColThreshold(ref chr)
{
}

//Персонаж закончил проигрывать анимацию
void LAi_tmpl_dialog_EndAction(ref chr)
{
	CharacterPlayAction(chr, "");
}


//Персонажа просят освободить место
void LAi_tmpl_dialog_FreePos(ref chr, aref who)
{
}

//------------------------------------------------------------------------------------------
//Внутреннии функции
//------------------------------------------------------------------------------------------

void LAi_tmpl_dialog_updatetemplate(ref chr)
{
	if(chr.chr_ai.tmpl.state == "dialog")
	{
		SetCharacterTask_Stay(chr);
	}else{
		chr.chr_ai.tmpl.state = "wait";
		SetCharacterTask_Stay(chr);
	}
}

void LAi_tmpl_dialog_StartDialog(ref chr, ref by, float dlgTime)
{
	//Заполняем поля
	chr.chr_ai.tmpl.dialog = by.index;
	chr.chr_ai.tmpl.state = "wait";
	chr.chr_ai.tmpl.dtime = "0";
	chr.chr_ai.tmpl.dlgtime = dlgTime;
	//Запускаем диалог
	int idx = int(chr.chr_ai.tmpl.dialog);
	int my = int(chr.index);
	if(idx == my)
	{
		//Не говорим сами с собой
		Trace("Template dialog: can't start dialog with myself!");
		chr.chr_ai.tmpl.dlgtime = "0";
	}
	if(!IsEntity(&Characters[idx]))
	{
		//Не говорим с несущиствующим персонажем
		Trace("Template dialog: can't start dialog with unloaded character!");
		chr.chr_ai.tmpl.dlgtime = "0";
	}	
	if(nMainCharacterIndex == idx)
	{
		//Диалог с главным персонажем
		chr.chr_ai.tmpl.dlgtime = "-1";
		if(!DialogMain(&Characters[my], false))
		{
			Trace("Template dialog: can't start dialog_1, DialogMain return false!");
			chr.chr_ai.tmpl.dlgtime = "0";
		}
	}else{
		if(nMainCharacterIndex == my)
		{
			//Диалог с главным персонажем
			chr.chr_ai.tmpl.dlgtime = "-1";
			if(!DialogMain(&Characters[idx], false))
			{
				Trace("Template dialog: can't start dialog_2, DialogMain return false!");
				chr.chr_ai.tmpl.dlgtime = "0";
			}			
		}else{
			//Диалог между NPC
			if(dlgTime < 0) dlgTime = 0;
			LAi_Character_StartDialog(&Characters[my], &Characters[idx]);
			LAi_Character_StartDialog(&Characters[idx], &Characters[my]);
			chr.chr_ai.tmpl.dlgtime = dlgTime;
		}
	}
	chr.chr_ai.tmpl.state = "dialog";
	LAi_tmpl_dialog_CharacterUpdate(chr, 0.0);
}

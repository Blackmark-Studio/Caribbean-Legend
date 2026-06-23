

#define LAI_TMPL_STAY	"stay"



bool LAi_tmpl_stay_InitTemplate(ref chr)
{
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "LockFightMode", false);
	CharacterPlayAction(chr, "");
	DeleteAttribute(chr, "chr_ai.tmpl");
	chr.chr_ai.tmpl = LAI_TMPL_STAY;
	if(LAi_IsInitedAI) SetCharacterTask_Stay(chr);
	if (chr.model.animation == "main_menu_mc" || 
		chr.model.animation == "main_menu_mc_mary" || 
		chr.model.animation == "main_menu_mary" ||
		chr.model.animation == "main_menu_mc_helena" ||
		chr.model.animation == "main_menu_mc_rumba" ||
		chr.model.animation == "main_menu_mc_man_b" ||
		chr.model.animation == "main_menu_helena") 
	{
		chr.chr_ai.tmpl.state = "idle";
		chr.chr_ai.tmpl.time = 10.0;
	}
	return true;
}

//Процессирование шаблона персонажа
void LAi_tmpl_stay_CharacterUpdate(ref chr, float dltTime) {
	float time;
	// float time = float(chr.chr_ai.tmpl.time) - dltTime;
	if (chr.model.animation == "main_menu_mc" || 
	chr.model.animation == "main_menu_mc_man_b" ||
	chr.model.animation == "main_menu_mc_rumba") {
	time = float(chr.chr_ai.tmpl.time) - dltTime;
		switch (chr.chr_ai.tmpl.state) {
			case "idle":
				if (time < 0) {
					CharacterPlayAction(chr, "look_right");
					chr.chr_ai.tmpl.state = "look_right";
					chr.chr_ai.tmpl.time = 5.0;
					break;
				}

				chr.chr_ai.tmpl.time = time;
			break;

			case "looking_right":
				if (time < 0) {
					CharacterPlayAction(chr, "look_left");
					chr.chr_ai.tmpl.state = "look_left";
					chr.chr_ai.tmpl.time = 20.0;
					break;
				}
				
				chr.chr_ai.tmpl.time = time;
			break;

			case "idle2":
				if (time < 0) {
					CharacterPlayAction(chr, "look_down");
					chr.chr_ai.tmpl.state = "look_down";
					chr.chr_ai.tmpl.time = 2.0;
					break;
				}

				chr.chr_ai.tmpl.time = time;
			break;
	
			case "looking_down":
				if (time < 0) {
					CharacterPlayAction(chr, "look_downup");
					chr.chr_ai.tmpl.state = "look_downup";
					chr.chr_ai.tmpl.time = 15.0;
					break;
				}
				
				chr.chr_ai.tmpl.time = time;
			break;
		}
	}
	if (chr.model.animation == "main_menu_mc_mary" || 
		chr.model.animation == "main_menu_mary" || 
		chr.model.animation == "main_menu_mc_helena" || 
		chr.model.animation == "main_menu_helena") {
	time = float(chr.chr_ai.tmpl.time) - dltTime;
		switch (chr.chr_ai.tmpl.state) {
			case "idle":
				if (time < 0) {
					CharacterPlayAction(chr, "look_right1");
					chr.chr_ai.tmpl.state = "look_right1";
					chr.chr_ai.tmpl.time = 8.0;
					break;
				}

				chr.chr_ai.tmpl.time = time;
			break;

			case "looking_right":
				if (time < 0) {
					CharacterPlayAction(chr, "look_left1");
					chr.chr_ai.tmpl.state = "look_left1";
					chr.chr_ai.tmpl.time = 20.0;
					break;
				}
				
				chr.chr_ai.tmpl.time = time;
			break;

			case "idle2":
				if (time < 0) {
					CharacterPlayAction(chr, "look_left2");
					chr.chr_ai.tmpl.state = "look_left2";
					chr.chr_ai.tmpl.time = 5.0;
					break;
				}

				chr.chr_ai.tmpl.time = time;
			break;
	
			case "looking_left":
				if (time < 0) {
					CharacterPlayAction(chr, "look_right2");
					chr.chr_ai.tmpl.state = "look_right2";
					chr.chr_ai.tmpl.time = 15.0;
					break;
				}
				
				chr.chr_ai.tmpl.time = time;
			break;
		}
	}
}

//Персонаж выполнил команду  go to point
void LAi_tmpl_stay_EndGoToPoint(ref chr)
{
	SetCharacterTask_Stay(chr);
}

//Персонаж провалил команду  go to point
void LAi_tmpl_stay_FailureGoToPoint(ref chr)
{
	SetCharacterTask_Stay(chr);
}


//Персонаж выполнил команду  run to point
void LAi_tmpl_stay_EndRunToPoint(ref chr)
{
	SetCharacterTask_Stay(chr);
}

//Персонаж провалил команду  run to point
void LAi_tmpl_stay_FailureRunToPoint(ref chr)
{
	SetCharacterTask_Stay(chr);
}

//Персонаж не может добраться до точки назначения
void LAi_tmpl_stay_BusyPos(ref chr, float x, float y, float z)
{
	SetCharacterTask_Stay(chr);
}

//Персонаж начал перемещение за другим
void LAi_tmpl_stay_FollowGo(ref chr)
{
	SetCharacterTask_Stay(chr);
}

//Персонаж начал дошёл до другого персонажа
void LAi_tmpl_stay_FollowStay(ref chr)
{
	SetCharacterTask_Stay(chr);
}

//Персонаж провалил команду  follow character
void LAi_tmpl_stay_FailureFollow(ref chr)
{
	SetCharacterTask_Stay(chr);
}


//Персонаж начал перемещение за другим
void LAi_tmpl_stay_FightGo(ref chr)
{
	SetCharacterTask_Stay(chr);
}

//Персонаж начал дошёл до другого персонажа
void LAi_tmpl_stay_FightStay(ref chr)
{
	SetCharacterTask_Stay(chr);
}

//Персонаж провалил команду  Fight
void LAi_tmpl_stay_FailureFight(ref chr)
{
	SetCharacterTask_Stay(chr);
}

//Можно ли стрелять
bool LAi_tmpl_stay_IsFire(ref chr)
{	
	return false;
}

//Можно ли использовать оружие
bool LAi_tmpl_stay_IsFight(ref chr)
{
	return false;
}


//Персонаж выполнил команду  escape
void LAi_tmpl_stay_EndEscape(ref chr)
{
	SetCharacterTask_Stay(chr);
}

//Персонаж скользит вдоль патча
void LAi_tmpl_stay_EscapeSlide(ref chr)
{
	SetCharacterTask_Stay(chr);
}

//Персонаж провалил команду  escape
void LAi_tmpl_stay_FailureEscape(ref chr)
{
	SetCharacterTask_Stay(chr);
}


//Персонаж толкается с другими персонажами
void LAi_tmpl_stay_ColThreshold(ref chr)
{
	SetCharacterTask_Stay(chr);
}


//Персонаж закончил проигрывать анимацию
void LAi_tmpl_stay_EndAction(ref chr)
{
	if (chr.model.animation == "main_menu_mc" || 
	chr.model.animation == "main_menu_mc_man_b" || 
	chr.model.animation == "main_menu_mc_rumba") {
		switch (chr.chr_ai.tmpl.state) {
			case "look_right":
				CharacterPlayAction(chr, "looking_right");
				chr.chr_ai.tmpl.state = "looking_right";
			break;
			
			case "look_left":
				CharacterPlayAction(chr, "");
				chr.chr_ai.tmpl.state = "idle2";
			break;

			case "look_down":
				CharacterPlayAction(chr, "looking_down");
				chr.chr_ai.tmpl.state = "looking_down";
			break;

			case "look_downup":
				CharacterPlayAction(chr, "");
				chr.chr_ai.tmpl.state = "idle";
			break;
		}
	}
	if (chr.model.animation == "main_menu_mc_mary" || 
		chr.model.animation == "main_menu_mary" ||
		chr.model.animation == "main_menu_mc_helena" ||
		chr.model.animation == "main_menu_helena") {
		switch (chr.chr_ai.tmpl.state) {
			case "look_right1":
				CharacterPlayAction(chr, "looking_right");
				chr.chr_ai.tmpl.state = "looking_right";
			break;
			
			case "look_left1":
				CharacterPlayAction(chr, "");
				chr.chr_ai.tmpl.state = "idle2";
			break;

			case "look_left2":
				CharacterPlayAction(chr, "looking_left");
				chr.chr_ai.tmpl.state = "looking_left";
			break;

			case "look_right2":
				CharacterPlayAction(chr, "");
				chr.chr_ai.tmpl.state = "idle";
			break;
		}
	}
	SetCharacterTask_Stay(chr);
}


//Персонажа просят освободить место
void LAi_tmpl_stay_FreePos(ref chr, aref who)
{
	SetCharacterTask_Stay(chr);
}


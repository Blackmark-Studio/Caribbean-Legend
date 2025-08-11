


void SetupItemModifiers()
{
	
	ref item = ItemsFromID("indian_1");
	SetFloatModifierToItem(item, MODIFIER_RANGE_HIT_ENEMY_PROBABILITY, 1.10);
	SetFloatModifierToItem(item, MODIFIER_RANGE_DAMAGE_MODIFIER, 1.15);
	SetFloatModifierToItem(item, MODIFIER_RANGE_CRIT_CHANCE, 3);
	
	item = ItemsFromID("indian_2");
	SetBoolModifierToItem(item, MODIFIER_PROTECT_RANGE_EXPLOSION_DOUBLE_BULLET, true);
	SetFloatModifierToItem(item, MODIFIER_PROTECT_RANGE_EXPLOSION_MODIFIER, 2.0);
	SetFloatModifierToItem(item, MODIFIER_RANGE_HIT_PROBABILITY, 1.15);
	SetFloatModifierToItem(item, MODIFIER_RANGE_ENEMY_DAMAGE, 1.10);
	SetFloatModifierToItem(item, MODIFIER_RANGE_CRIT_CHANCE, 3);

	item = ItemsFromID("indian_3");
	SetFloatModifierToItem(item, MODIFIER_MELEE_CRIT_CHANCE, 15);
	SetFloatModifierToItem(item, MODIFIER_MELEE_BREAK_ATTACK_BONUS_ENEMY, 1.1);
	
	item = ItemsFromID("indian_4");
	SetFloatModifierToItem(item, MODIFIER_MELEE_CRIT_DAMAGE, 0.5);
	SetFloatModifierToItem(item, MODIFIER_CRIT_INCOMING_CHANCE, 10);
	SetFloatModifierToItem(item, MODIFIER_MELEE_BREAK_ATTACK_BONUS, 1.25);

	item = ItemsFromID("indian_9");
	SetFloatModifierToItem(item, MODIFIER_SKILL_ACCURACY_SCALE, 1.1);
	
	item = ItemsFromID("amulet_1");
	SetFloatModifierToItem(item, MODIFIER_RANGE_HIT_PROBABILITY, 0.9);
	SetFloatModifierToItem(item, MODIFIER_RANGE_ENEMY_DAMAGE, 0.85);
	
	
	item = ItemsFromID("amulet_2");
	SetCallbackModifierToItem(item, MODIFIER_RANGE_DAMAGE_MODIFIER, "Amulet2DamageModifier");
	SetCallbackModifierToItem(item, MODIFIER_RANGE_HIT_ENEMY_PROBABILITY, "Amulet2HitEnemyProbability");
	
	item = ItemsFromID("amulet_3");
	SetCallbackModifierToItem(item, MODIFIER_MELEE_CRIT_DAMAGE, "Amulet3CritDamageModifier");
	SetCallbackModifierToItem(item, MODIFIER_MELEE_BREAK_ATTACK_BONUS, "Amulet3BreakAttackBonus");
	
	
	
	

	item = ItemsFromID("amulet_4");
	SetFloatModifierToItem(item, MODIFIER_CRIT_INCOMING_CHANCE, 10);
	SetFloatModifierToItem(item, MODIFIER_MELEE_BREAK_ATTACK_BONUS_ENEMY, 0.85);
	
	
	item = ItemsFromID("amulet_6");
	SetCallbackModifierToItem(item, MODIFIER_SKILL_SNEAK_SCALE, "Amulet6SneakScaleBonus");
	
	item = ItemsFromID("amulet_7");
	SetCallbackModifierToItem(item, MODIFIER_SKILL_FORTUNE_SCALE, "Amulet7FortuneScaleBonus");
	
	
	item = ItemsFromID("totem_05");
	SetFloatModifierToItem(item, MODIFIER_OWN_STUN_CHANCE, 0.0);

	item = ItemsFromID("totem_06");
	SetBoolModifierToItem(item, MODIFIER_DISABLE_OVERLOAD_CHECK, true);
	
	item = ItemsFromID("totem_11");
	SetFloatModifierToItem(item, MODIFIER_ENERGY_DRAIN, 0.1);
	
	item = ItemsFromID("totem_12");
	SetFloatModifierToItem(item, MODIFIER_RANGE_CRIT_CHANCE, 3);
	SetCallbackModifierToItem(item, MODIFIER_RANGE_HIT_PROBABILITY, "Totem12HitProbability");
	SetCallbackModifierToItem(item, MODIFIER_SKILL_ACCURACY_SCALE, "Totem12AccuracyScale");






	item = ItemsFromID("totem_13");
	SetSkillModifierToItem(item, SPECIAL_L, 1);

	item = ItemsFromID("KhaelRoa_item");
	SetFloatModifierToItem(item, MODIFIER_RANGE_DAMAGE_MODIFIER, 10);

	item = ItemsFromID("kaleuche_amulet3");
	SetFloatModifierToItem(item, MODIFIER_INCOMING_DAMAGE, 0.75);


	item = ItemsFromID("talisman8");
	SetBoolModifierToItem(item, MODIFIER_POISON_PROTECT, true);


	item = ItemsFromID("talisman9");
	SetSkillModifierToItem(item, SPECIAL_C, 1);


	item = ItemsFromID("talisman11");
	SetSkillModifierToItem(item, SKILL_F_LIGHT, 2);
	SetSkillModifierToItem(item, SKILL_FENCING, 2);
	SetSkillModifierToItem(item, SKILL_F_HEAVY, 2);
	SetSkillModifierToItem(item, SKILL_PISTOL, 2);
	SetSkillModifierToItem(item, SKILL_FORTUNE, 2);
	SetSkillModifierToItem(item, SKILL_LEADERSHIP, 2);
	SetSkillModifierToItem(item, SKILL_COMMERCE, 2);
	SetSkillModifierToItem(item, SKILL_ACCURACY, 2);
	SetSkillModifierToItem(item, SKILL_CANNONS, 2);
	SetSkillModifierToItem(item, SKILL_SAILING, 2);
	SetSkillModifierToItem(item, SKILL_REPAIR, 2);
	SetSkillModifierToItem(item, SKILL_GRAPPLING, 2);
	SetSkillModifierToItem(item, SKILL_DEFENCE, 2);
	SetSkillModifierToItem(item, SKILL_SNEAK, 2);

	item = ItemsFromID("talisman14");
	SetSkillModifierToItem(item, SKILL_SAILING, 15);
	
	item = ItemsFromID("talisman16");
	SetFloatModifierToItem(item, MODIFIER_MELEE_DAMAGE, 1.1);

	item = ItemsFromID("talisman17");
	SetSkillModifierToItem(item, SKILL_SAILING, 15);
	SetSkillCallbackModifierToItem(item, SKILL_DEFENCE, "Talisman17DefenceModifier");
	
	
	
	item = ItemsFromID("talisman18");
	SetCallbackModifierToItem(item, MODIFIER_RANGE_EXTRA_DAMAGE_GRAPE, "Talisman18DamageModifier");
	
	item = ItemsFromID("kaleuche_amulet2");
	SetSkillModifierToItem(item, SKILL_F_LIGHT, 25);
	SetSkillModifierToItem(item, SKILL_FENCING, 25);
	SetSkillModifierToItem(item, SKILL_F_HEAVY, 25);
	SetSkillModifierToItem(item, SKILL_PISTOL, 25);

	item = ItemsFromID("obereg_1");
	SetSkillModifierToItem(item, SKILL_REPAIR, 10);

	item = ItemsFromID("obereg_2");
	SetSkillModifierToItem(item, SKILL_REPAIR, 10);
	
	item = ItemsFromID("obereg_4");
	SetSkillModifierToItem(item, SKILL_SNEAK, 10);
	
	item = ItemsFromID("obereg_5");
	SetSkillModifierToItem(item, SKILL_FORTUNE, 15);
	
	item = ItemsFromID("obereg_6");
	SetSkillModifierToItem(item, SKILL_LEADERSHIP, 10);
	
	item = ItemsFromID("obereg_7");
	SetSkillCallbackModifierToItem(item, SKILL_SAILING, "Obereg7SailingBonus");
	
	
	
	item = ItemsFromID("obereg_8");
	SetSkillModifierToItem(item, SKILL_COMMERCE, 15);
	
	

	item = ItemsFromID("saber");
	SetSkillModifierToItem(item, SKILL_FENCING, 5);
	
	item = ItemsFromID("pirate_cutlass");
	SetSkillModifierToItem(item, SKILL_FENCING, 5);

	item = ItemsFromID("topor_06");
	SetSkillModifierToItem(item, SKILL_F_HEAVY, 5);

	item = ItemsFromID("machete2");
	SetSkillModifierToItem(item, SKILL_FENCING, 5);
	
	item = ItemsFromID("khopesh1");
	SetFloatModifierToItem(item, MODIFIER_MELEE_CRIT_CHANCE, 1);
	SetFloatModifierToItem(item, MODIFIER_MELEE_DAMAGE_MISHELLE, 1.2);
	SetSkillModifierToItem(item, SKILL_FENCING, 5);

	item = ItemsFromID("khopesh2");
	SetFloatModifierToItem(item, MODIFIER_MELEE_CRIT_CHANCE, 3);
	SetFloatModifierToItem(item, MODIFIER_MELEE_DAMAGE_MISHELLE, 2.0);
	SetSkillModifierToItem(item, SKILL_FENCING, 15);
	
	item = ItemsFromID("khopesh3");
	SetFloatModifierToItem(item, MODIFIER_MELEE_CRIT_CHANCE, 2);
	SetFloatModifierToItem(item, MODIFIER_MELEE_DAMAGE_MISHELLE, 1.4);
	SetSkillModifierToItem(item, SKILL_FENCING, 10);
	
	item = ItemsFromID("knife_01");
	//SetFloatModifierToItem(item, MODIFIER_MELEE_DAMAGE_UNDEAD, 16);
	SetBoolModifierToItem(item, MODIFIER_MELEE_EXTRA_DAMAGE_TO_UNDEAD, true);
	SetSkillModifierToItem(item, SKILL_F_LIGHT, 5);
	
	item = ItemsFromID("knife_02");
	SetSkillModifierToItem(item, SKILL_F_LIGHT, 15);

	item = ItemsFromID("knife_03");
	SetSkillModifierToItem(item, SPECIAL_L, 1);
	
	item = ItemsFromID("blade_38");
	SetSkillModifierToItem(item, SKILL_F_LIGHT, 5);
	
	item = ItemsFromID("blade_39");
	SetSkillModifierToItem(item, SKILL_F_LIGHT, 10);
	
	item = ItemsFromID("blade_40");
	SetSkillModifierToItem(item, SKILL_LEADERSHIP, 5);
	
	item = ItemsFromID("blade_42");
	SetSkillModifierToItem(item, SKILL_F_HEAVY, 5);
	

	item = ItemsFromID("q_blade_10");
	SetSkillModifierToItem(item, SKILL_FENCING, 10);
	item = ItemsFromID("q_blade_13");
	SetSkillModifierToItem(item, SKILL_F_HEAVY, 10);
	item = ItemsFromID("q_blade_16");
	SetSkillModifierToItem(item, SKILL_F_LIGHT, 10);
	item = ItemsFromID("q_blade_18");
	SetSkillModifierToItem(item, SKILL_F_LIGHT, 12);
	item = ItemsFromID("q_blade_19");
	SetSkillModifierToItem(item, SKILL_FENCING, 12);
	item = ItemsFromID("q_blade_21");
	SetSkillModifierToItem(item, SKILL_F_HEAVY, 12);
	
	
	item = ItemsFromID("blade_SP_3");
	SetCallbackModifierToItem(item, MODIFIER_MELEE_DAMAGE, "BladeSP3DamageModifier");
	

	item = ItemsFromID("mushket3");
	SetFloatModifierToItem(item, MODIFIER_RANGE_CRIT_CHANCE, 3);

	item = ItemsFromID("mushket5");
	SetFloatModifierToItem(item, MODIFIER_RANGE_INSTA_SHOT, 5);
	SetFloatModifierToItem(item, MODIFIER_RANGE_CRIT_CHANCE, 10);

	item = ItemsFromID("mushket7");
	SetFloatModifierToItem(item, MODIFIER_RANGE_CRIT_CHANCE, 6);
	
	item = ItemsFromID("pistol5");
	SetFloatModifierToItem(item, MODIFIER_RANGE_INSTA_SHOT, 2);
	SetFloatModifierToItem(item, MODIFIER_RANGE_CRIT_CHANCE, 15);
	SetSkillModifierToItem(item, SKILL_PISTOL, 5);

	item = ItemsFromID("pistol9");
	SetFloatModifierToItem(item, MODIFIER_RANGE_INSTA_SHOT, 1);
	SetFloatModifierToItem(item, MODIFIER_RANGE_CRIT_CHANCE, 3);

	item = ItemsFromID("pistol11");
	SetFloatModifierToItem(item, MODIFIER_RANGE_INSTA_SHOT, 2);
	SetFloatModifierToItem(item, MODIFIER_RANGE_CRIT_CHANCE, 6);
	SetSkillModifierToItem(item, SKILL_F_HEAVY, 20);
	
	item = ItemsFromID("pistol13");
	SetSkillModifierToItem(item, SPECIAL_C, 1);
	
	item = ItemsFromID("pistol14");
	SetFloatModifierToItem(item, MODIFIER_RANGE_CRIT_CHANCE, 9);	

	item = ItemsFromID("howdah");
	SetFloatModifierToItem(item, MODIFIER_RANGE_INSTA_SHOT, 1);
	

	item = ItemsFromID("bullet_double");
	SetBoolModifierToItem(item, MODIFIER_RANGE_EXPLODE_ON_SHOT, true);

	item = ItemsFromID("grapeshot_double");
	SetBoolModifierToItem(item, MODIFIER_RANGE_EXPLODE_ON_SHOT, true);

	
	item = ItemsFromID("hat2");
	SetFloatModifierToItem(item, MODIFIER_KILL_ENERGY_UP, 0.25);
	
	item = ItemsFromID("hat5");
	SetBoolModifierToItem(item, MODIFIER_ALLOW_ENEMY_FLAGSHIP, true);
	
	item = ItemsFromID("hat9");
	SetFloatModifierToItem(item, MODIFIER_SHOT_AVOID_CHANCE, 0.1);

	item = ItemsFromID("cirass1");
	SetSkillModifierToItem(item, SKILL_SNEAK, -5);
	SetSkillModifierToItem(item, SPECIAL_E, -1);
	SetSkillModifierToItem(item, SPECIAL_A, -2);
	SetBoolModifierToItem(item, MODIFIER_HEAVY_ARMOR, true);
	
	item = ItemsFromID("cirass2");
	SetSkillModifierToItem(item, SKILL_SNEAK, -5);
	SetSkillModifierToItem(item, SPECIAL_E, -1);
	SetSkillModifierToItem(item, SPECIAL_A, -1);
	SetBoolModifierToItem(item, MODIFIER_HEAVY_ARMOR, true);
	
	item = ItemsFromID("cirass3");
	SetSkillModifierToItem(item, SKILL_LEADERSHIP, 15);
	SetSkillModifierToItem(item, SKILL_SNEAK, -15);
	SetBoolModifierToItem(item, MODIFIER_HEAVY_ARMOR, true);
	
	item = ItemsFromID("cirass4");
	SetSkillModifierToItem(item, SKILL_LEADERSHIP, 10);
	SetSkillModifierToItem(item, SKILL_SNEAK, -20);
	SetSkillModifierToItem(item, SPECIAL_E, -1);
	SetBoolModifierToItem(item, MODIFIER_HEAVY_ARMOR, true);

	item = ItemsFromID("cirass5");
	SetBoolModifierToItem(item, MODIFIER_LIGHT_ARMOR, true);
	
	item = ItemsFromID("cirass6");
	SetSkillModifierToItem(item, SKILL_LEADERSHIP, -5);
	SetSkillModifierToItem(item, SKILL_SNEAK, -5);
	SetSkillModifierToItem(item, SPECIAL_P, -1);
	SetBoolModifierToItem(item, MODIFIER_LIGHT_ARMOR, true);
	
	item = ItemsFromID("cirass7");
	SetSkillModifierToItem(item, SKILL_LEADERSHIP, -10);
	SetSkillModifierToItem(item, SPECIAL_P, -1);
	SetBoolModifierToItem(item, MODIFIER_LIGHT_ARMOR, true);
	
	item = ItemsFromID("cirass8");
	SetSkillModifierToItem(item, SKILL_LEADERSHIP, -15);
	SetSkillModifierToItem(item, SKILL_SNEAK, 15);
	SetBoolModifierToItem(item, MODIFIER_LIGHT_ARMOR, true);
		
	item = ItemsFromID("cirass9");
	SetFloatModifierToItem(item, MODIFIER_MELEE_CRIT_CHANCE, 5);
	SetFloatModifierToItem(item, MODIFIER_OWN_STUN_CHANCE, 0.0);
	SetSkillModifierToItem(item, SKILL_F_LIGHT, 5);
	SetSkillModifierToItem(item, SKILL_FENCING, 5);
	SetSkillModifierToItem(item, SKILL_F_HEAVY, 5);
	SetSkillModifierToItem(item, SKILL_PISTOL, 5);
	SetBoolModifierToItem(item, MODIFIER_LIGHT_ARMOR, true);

	item = ItemsFromID("cirass10");
	SetFloatModifierToItem(item, MODIFIER_RANGE_CRIT_CHANCE, 5);
	SetFloatModifierToItem(item, MODIFIER_RANGE_RELOAD_SPEED_BONUS, 1.15);
	SetBoolModifierToItem(item, MODIFIER_PROTECT_RANGE_EXPLOSION, true);
	SetBoolModifierToItem(item, MODIFIER_PROTECT_RANGE_EXPLOSION_DOUBLE_BULLET, true);
	SetSkillModifierToItem(item, SPECIAL_A, -1);
	SetBoolModifierToItem(item, MODIFIER_HEAVY_ARMOR, true);

	
	item = ItemsFromID("suit1");
	SetSkillModifierToItem(item, SKILL_LEADERSHIP, 25);
	SetSkillModifierToItem(item, SKILL_SNEAK, -25);
	SetSkillModifierToItem(item, SPECIAL_C, 1);
	SetBoolModifierToItem(item, MODIFIER_LIGHT_ARMOR, true);
	
	item = ItemsFromID("suit2");
	SetSkillModifierToItem(item, SKILL_LEADERSHIP, 25);
	SetSkillModifierToItem(item, SKILL_SNEAK, -25);
	SetSkillModifierToItem(item, SPECIAL_C, 1);
	SetBoolModifierToItem(item, MODIFIER_LIGHT_ARMOR, true);
	
	item = ItemsFromID("suit3");
	SetSkillModifierToItem(item, SKILL_LEADERSHIP, 25);
	SetSkillModifierToItem(item, SKILL_SNEAK, -25);
	SetSkillModifierToItem(item, SPECIAL_C, 1);
	SetBoolModifierToItem(item, MODIFIER_LIGHT_ARMOR, true);
	
	item = ItemsFromID("suit4");
	SetSkillModifierToItem(item, SKILL_LEADERSHIP, -25);
	SetSkillModifierToItem(item, SKILL_SNEAK, 30);
	SetSkillModifierToItem(item, SPECIAL_P, -1);
	SetSkillModifierToItem(item, SPECIAL_A, 1);
	SetBoolModifierToItem(item, MODIFIER_LIGHT_ARMOR, true);

	item = ItemsFromID("suit5");
	SetSkillModifierToItem(item, SKILL_LEADERSHIP, 40);
	SetSkillModifierToItem(item, SKILL_SNEAK, -50);
	SetSkillModifierToItem(item, SKILL_SAILING, 5);
	SetSkillModifierToItem(item, SPECIAL_C, 1);
	SetBoolModifierToItem(item, MODIFIER_LIGHT_ARMOR, true);
	
	item = ItemsFromID("underwater");
	SetSkillModifierToItem(item, SKILL_LEADERSHIP, -20);
	SetSkillModifierToItem(item, SKILL_SNEAK, -100);
	SetSkillModifierToItem(item, SKILL_F_LIGHT, -15);
	SetSkillModifierToItem(item, SKILL_FENCING, -15);
	SetSkillModifierToItem(item, SKILL_F_HEAVY, -15);
	SetSkillModifierToItem(item, SKILL_PISTOL, -50);
	SetSkillModifierToItem(item, SPECIAL_P, -2);
	SetSkillModifierToItem(item, SPECIAL_E, -2);
	SetSkillModifierToItem(item, SPECIAL_A, -1);
	SetBoolModifierToItem(item, MODIFIER_HEAVY_ARMOR, true);
	

	item = ItemsFromID("indian_poison");
	SetBoolModifierToItem(item, MODIFIER_POISON_ATTACK, true);

	item = ItemsFromID("SkullAztec");
	SetPassiveSkillModifierToItem(item, SKILL_FORTUNE, -20);
	SetPassiveSkillModifierToItem(item, SKILL_LEADERSHIP, 10);

	
	item = ItemsFromID("mineral8");
	SetPassiveSkillModifierToItem(item, SKILL_FORTUNE, -10);

	item = ItemsFromID("mineral14");
	SetPassiveSkillModifierToItem(item, SKILL_FORTUNE, -10);

	
	item = ItemsFromID("mineral30");
	SetPassiveSkillModifierToItem(item, SKILL_LEADERSHIP, -10);
	
	item = ItemsFromID("mineral31");
	SetPassiveSkillModifierToItem(item, SKILL_LEADERSHIP, -10);
	SetPassiveSkillModifierToItem(item, SKILL_FORTUNE, -10);


	// такого предмета просто нет
	/*item = ItemsFromID("Coins");
	SetPassiveSkillModifierToItem(item, SKILL_FORTUNE, -50);*/

	// такого предмета просто нет
	/*item = ItemsFromID("KnifeAztec");
	SetPassiveSkillModifierToItem(item, SKILL_PISTOL, -30);
	SetPassiveSkillModifierToItem(item, SKILL_F_LIGHT, -20);
	SetPassiveSkillModifierToItem(item, SKILL_FENCING, -20);
	SetPassiveSkillModifierToItem(item, SKILL_F_HEAVY, -20);*/
}


int Obereg7SailingBonus(ref rChar)
{
	if (ShipBonus2Artefact(rChar, SHIP_GALEON_SM)) 
		return 15;
	return 10;
}

float Amulet2DamageModifier(ref rChar)
{
	if (ShipBonus2Artefact(rChar, SHIP_GALEON_SM)) 
		return 0.94;
	return 0.9;
}

float Amulet2HitEnemyProbability(ref rChar)
{
	if (ShipBonus2Artefact(rChar, SHIP_GALEON_SM)) 
		return 0.75;
	return 0.85;
}

float Amulet3CritDamageModifier(ref rChar)
{
	if (ShipBonus2Artefact(rChar, SHIP_GALEON_SM)) 
		return -0.4;
	return -0.3;
}

float Amulet3BreakAttackBonus(ref rChar)
{
	if (ShipBonus2Artefact(rChar, SHIP_GALEON_SM)) 
		return 0.95;
	return 0.9;
}

float Amulet6SneakScaleBonus(ref rChar)
{
	if (ShipBonus2Artefact(rChar, SHIP_GALEON_SM)) 
		return 0.75;
	return 0.5;
}

float Amulet7FortuneScaleBonus(ref rChar)
{
	if (ShipBonus2Artefact(rChar, SHIP_GALEON_SM)) 
		return 0.75;
	return 0.5;
}

int Talisman17DefenceModifier(ref rChar)
{
	bool bHero = (sti(rChar.index) == GetMainCharacterIndex());
	
	if (bHero && ShipBonus2Artefact(rChar, SHIP_GALEON_SM)) 
		return 10;
	return 0;
}

float Talisman18DamageModifier(ref rChar)
{
	return 1.0 + 2.0 * ArticlesBonus(rChar);
}

float Totem12AccuracyScale(ref rChar)
{
	if (!IsDay())
		return 2.0;
	return 1.0;
}

float Totem12HitProbability(ref rChar)
{
	if (!IsDay())
		return 2.0;
	return 1.0;
}


float BladeSP3DamageModifier(ref rChar)
{
	return 1.0 + Bring2Range(0.0, 0.75, 0.0, 0.5, (1.0 - LAi_GetCharacterRelHP(rChar)) / 2.0);
}
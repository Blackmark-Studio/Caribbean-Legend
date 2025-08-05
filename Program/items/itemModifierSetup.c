


void SetupItemModifiers()
{
	
	ref item = ItemsFromID("indian_1");
	AddFloatModifierToItem(item, MODIFIER_RANGE_HIT_ENEMY_PROBABILITY, 1.10);
	AddFloatModifierToItem(item, MODIFIER_RANGE_DAMAGE_MODIFIER, 1.15);
	AddFloatModifierToItem(item, MODIFIER_RANGE_CRIT_CHANCE, 3);
	
	item = ItemsFromID("indian_2");
	AddBoolModifierToItem(item, MODIFIER_PROTECT_RANGE_EXPLOSION_DOUBLE_BULLET, true);
	AddFloatModifierToItem(item, MODIFIER_PROTECT_RANGE_EXPLOSION_MODIFIER, 2.0);
	AddFloatModifierToItem(item, MODIFIER_RANGE_HIT_PROBABILITY, 1.15);
	AddFloatModifierToItem(item, MODIFIER_RANGE_ENEMY_DAMAGE_MODIFIER, 1.10);
	AddFloatModifierToItem(item, MODIFIER_RANGE_CRIT_CHANCE, 3);

	item = ItemsFromID("indian_3");
	AddFloatModifierToItem(item, MODIFIER_MELEE_CRIT_CHANCE, 15);
	
	item = ItemsFromID("indian_4");
	AddFloatModifierToItem(item, MODIFIER_MELEE_CRIT_DAMAGE, 0.5);
	AddFloatModifierToItem(item, MODIFIER_CRIT_INCOMING_CHANCE, 10);

	item = ItemsFromID("indian_9");
	AddFloatModifierToItem(item, MODIFIER_SKILL_ACCURACY_SCALE, 1.1);
	
	item = ItemsFromID("amulet_1");
	AddFloatModifierToItem(item, MODIFIER_RANGE_HIT_PROBABILITY, 0.9);
	AddFloatModifierToItem(item, MODIFIER_RANGE_ENEMY_DAMAGE_MODIFIER, 0.85);
	
	item = ItemsFromID("amulet_4");
	AddFloatModifierToItem(item, MODIFIER_CRIT_INCOMING_CHANCE, 10);
	
	
	item = ItemsFromID("totem_05");
	AddFloatModifierToItem(item, MODIFIER_OWN_STUN_CHANCE, 0.0);

	item = ItemsFromID("totem_06");
	AddBoolModifierToItem(item, MODIFIER_DISABLE_OVERLOAD_CHECK, true);
	
	item = ItemsFromID("totem_12");
	AddFloatModifierToItem(item, MODIFIER_RANGE_CRIT_CHANCE, 3);

	item = ItemsFromID("totem_13");
	AddSkillModifierToItem(item, SPECIAL_L, 1);

	item = ItemsFromID("KhaelRoa_item");
	AddFloatModifierToItem(item, MODIFIER_RANGE_DAMAGE_MODIFIER, 10);

	item = ItemsFromID("kaleuche_amulet3");
	AddFloatModifierToItem(item, MODIFIER_INCOMING_DAMAGE, 0.75);


	item = ItemsFromID("talisman8");
	AddBoolModifierToItem(item, MODIFIER_POISON_PROTECT, true);


	item = ItemsFromID("talisman9");
	AddSkillModifierToItem(item, SPECIAL_C, 1);


	item = ItemsFromID("talisman11");
	AddSkillModifierToItem(item, SKILL_F_LIGHT, 2);
	AddSkillModifierToItem(item, SKILL_FENCING, 2);
	AddSkillModifierToItem(item, SKILL_F_HEAVY, 2);
	AddSkillModifierToItem(item, SKILL_PISTOL, 2);
	AddSkillModifierToItem(item, SKILL_FORTUNE, 2);
	AddSkillModifierToItem(item, SKILL_LEADERSHIP, 2);
	AddSkillModifierToItem(item, SKILL_COMMERCE, 2);
	AddSkillModifierToItem(item, SKILL_ACCURACY, 2);
	AddSkillModifierToItem(item, SKILL_CANNONS, 2);
	AddSkillModifierToItem(item, SKILL_SAILING, 2);
	AddSkillModifierToItem(item, SKILL_REPAIR, 2);
	AddSkillModifierToItem(item, SKILL_GRAPPLING, 2);
	AddSkillModifierToItem(item, SKILL_DEFENCE, 2);
	AddSkillModifierToItem(item, SKILL_SNEAK, 2);

	item = ItemsFromID("talisman14");
	AddSkillModifierToItem(item, SKILL_SAILING, 15);
	
	item = ItemsFromID("talisman16");
	AddFloatModifierToItem(item, MODIFIER_MELEE_DAMAGE_MODIFIER, 1.1);

	item = ItemsFromID("talisman17");
	AddSkillModifierToItem(item, SKILL_SAILING, 15);
	
	item = ItemsFromID("kaleuche_amulet2");
	AddSkillModifierToItem(item, SKILL_F_LIGHT, 25);
	AddSkillModifierToItem(item, SKILL_FENCING, 25);
	AddSkillModifierToItem(item, SKILL_F_HEAVY, 25);
	AddSkillModifierToItem(item, SKILL_PISTOL, 25);

	item = ItemsFromID("obereg_1");
	AddSkillModifierToItem(item, SKILL_REPAIR, 10);

	item = ItemsFromID("obereg_2");
	AddSkillModifierToItem(item, SKILL_REPAIR, 10);
	
	item = ItemsFromID("obereg_4");
	AddSkillModifierToItem(item, SKILL_SNEAK, 10);
	
	item = ItemsFromID("obereg_5");
	AddSkillModifierToItem(item, SKILL_FORTUNE, 15);
	
	item = ItemsFromID("obereg_6");
	AddSkillModifierToItem(item, SKILL_LEADERSHIP, 10);
	
	item = ItemsFromID("obereg_8");
	AddSkillModifierToItem(item, SKILL_COMMERCE, 15);
	
	

	item = ItemsFromID("saber");
	AddSkillModifierToItem(item, SKILL_FENCING, 5);
	
	item = ItemsFromID("pirate_cutlass");
	AddSkillModifierToItem(item, SKILL_FENCING, 5);

	item = ItemsFromID("topor_06");
	AddSkillModifierToItem(item, SKILL_F_HEAVY, 5);

	item = ItemsFromID("machete2");
	AddSkillModifierToItem(item, SKILL_FENCING, 5);
	
	item = ItemsFromID("khopesh1");
	AddFloatModifierToItem(item, MODIFIER_MELEE_CRIT_CHANCE, 1);
	AddFloatModifierToItem(item, MODIFIER_MELEE_DAMAGE_MISHELLE, 1.2);
	AddSkillModifierToItem(item, SKILL_FENCING, 5);

	item = ItemsFromID("khopesh2");
	AddFloatModifierToItem(item, MODIFIER_MELEE_CRIT_CHANCE, 3);
	AddFloatModifierToItem(item, MODIFIER_MELEE_DAMAGE_MISHELLE, 2.0);
	AddSkillModifierToItem(item, SKILL_FENCING, 15);
	
	item = ItemsFromID("khopesh3");
	AddFloatModifierToItem(item, MODIFIER_MELEE_CRIT_CHANCE, 2);
	AddFloatModifierToItem(item, MODIFIER_MELEE_DAMAGE_MISHELLE, 1.4);
	AddSkillModifierToItem(item, SKILL_FENCING, 10);
	
	item = ItemsFromID("knife_01");
	//AddFloatModifierToItem(item, MODIFIER_MELEE_DAMAGE_UNDEAD, 16);
	AddBoolModifierToItem(item, MODIFIER_MELEE_EXTRA_DAMAGE_TO_UNDEAD, true);
	AddSkillModifierToItem(item, SKILL_F_LIGHT, 5);
	
	item = ItemsFromID("knife_02");
	AddSkillModifierToItem(item, SKILL_F_LIGHT, 15);

	item = ItemsFromID("knife_03");
	AddSkillModifierToItem(item, SPECIAL_L, 1);
	
	item = ItemsFromID("blade_38");
	AddSkillModifierToItem(item, SKILL_F_LIGHT, 5);
	
	item = ItemsFromID("blade_39");
	AddSkillModifierToItem(item, SKILL_F_LIGHT, 10);
	
	item = ItemsFromID("blade_40");
	AddSkillModifierToItem(item, SKILL_LEADERSHIP, 5);
	
	item = ItemsFromID("blade_42");
	AddSkillModifierToItem(item, SKILL_F_HEAVY, 5);
	

	item = ItemsFromID("q_blade_10");
	AddSkillModifierToItem(item, SKILL_FENCING, 10);
	item = ItemsFromID("q_blade_13");
	AddSkillModifierToItem(item, SKILL_F_HEAVY, 10);
	item = ItemsFromID("q_blade_16");
	AddSkillModifierToItem(item, SKILL_F_LIGHT, 10);
	item = ItemsFromID("q_blade_18");
	AddSkillModifierToItem(item, SKILL_F_LIGHT, 12);
	item = ItemsFromID("q_blade_19");
	AddSkillModifierToItem(item, SKILL_FENCING, 12);
	item = ItemsFromID("q_blade_21");
	AddSkillModifierToItem(item, SKILL_F_HEAVY, 12);
	
	
	item = ItemsFromID("blade_SP_3");
	AddBoolModifierToItem(item, MODIFIER_MELEE_SP3_DAMAGE_BONUS, true);
	

	item = ItemsFromID("mushket3");
	AddFloatModifierToItem(item, MODIFIER_RANGE_CRIT_CHANCE, 3);

	item = ItemsFromID("mushket5");
	AddFloatModifierToItem(item, MODIFIER_RANGE_INSTA_SHOT, 5);
	AddFloatModifierToItem(item, MODIFIER_RANGE_CRIT_CHANCE, 10);

	item = ItemsFromID("mushket7");
	AddFloatModifierToItem(item, MODIFIER_RANGE_CRIT_CHANCE, 6);
	
	item = ItemsFromID("pistol5");
	AddFloatModifierToItem(item, MODIFIER_RANGE_INSTA_SHOT, 2);
	AddFloatModifierToItem(item, MODIFIER_RANGE_CRIT_CHANCE, 15);
	AddSkillModifierToItem(item, SKILL_PISTOL, 5);

	item = ItemsFromID("pistol9");
	AddFloatModifierToItem(item, MODIFIER_RANGE_INSTA_SHOT, 1);
	AddFloatModifierToItem(item, MODIFIER_RANGE_CRIT_CHANCE, 3);

	item = ItemsFromID("pistol11");
	AddFloatModifierToItem(item, MODIFIER_RANGE_INSTA_SHOT, 2);
	AddFloatModifierToItem(item, MODIFIER_RANGE_CRIT_CHANCE, 6);
	AddSkillModifierToItem(item, SKILL_F_HEAVY, 20);
	
	item = ItemsFromID("pistol13");
	AddSkillModifierToItem(item, SPECIAL_C, 1);
	
	item = ItemsFromID("pistol14");
	AddFloatModifierToItem(item, MODIFIER_RANGE_CRIT_CHANCE, 9);	

	item = ItemsFromID("howdah");
	AddFloatModifierToItem(item, MODIFIER_RANGE_INSTA_SHOT, 1);
	

	item = ItemsFromID("bullet_double");
	AddBoolModifierToItem(item, MODIFIER_RANGE_EXPLODE_ON_SHOT, true);

	item = ItemsFromID("grapeshot_double");
	AddBoolModifierToItem(item, MODIFIER_RANGE_EXPLODE_ON_SHOT, true);

	
	item = ItemsFromID("hat2");
	AddFloatModifierToItem(item, MODIFIER_KILL_ENERGY_UP, 0.25);
	
	item = ItemsFromID("hat5");
	AddBoolModifierToItem(item, MODIFIER_ALLOW_ENEMY_FLAGSHIP, true);
	

	item = ItemsFromID("cirass1");
	AddSkillModifierToItem(item, SKILL_SNEAK, -5);
	AddSkillModifierToItem(item, SPECIAL_E, -1);
	AddSkillModifierToItem(item, SPECIAL_A, -2);
	AddBoolModifierToItem(item, MODIFIER_HEAVY_ARMOR, true);
	
	item = ItemsFromID("cirass2");
	AddSkillModifierToItem(item, SKILL_SNEAK, -5);
	AddSkillModifierToItem(item, SPECIAL_E, -1);
	AddSkillModifierToItem(item, SPECIAL_A, -1);
	AddBoolModifierToItem(item, MODIFIER_HEAVY_ARMOR, true);
	
	item = ItemsFromID("cirass3");
	AddSkillModifierToItem(item, SKILL_LEADERSHIP, 15);
	AddSkillModifierToItem(item, SKILL_SNEAK, -15);
	AddBoolModifierToItem(item, MODIFIER_HEAVY_ARMOR, true);
	
	item = ItemsFromID("cirass4");
	AddSkillModifierToItem(item, SKILL_LEADERSHIP, 10);
	AddSkillModifierToItem(item, SKILL_SNEAK, -20);
	AddSkillModifierToItem(item, SPECIAL_E, -1);
	AddBoolModifierToItem(item, MODIFIER_HEAVY_ARMOR, true);

	item = ItemsFromID("cirass5");
	AddBoolModifierToItem(item, MODIFIER_LIGHT_ARMOR, true);
	
	item = ItemsFromID("cirass6");
	AddSkillModifierToItem(item, SKILL_LEADERSHIP, -5);
	AddSkillModifierToItem(item, SKILL_SNEAK, -5);
	AddSkillModifierToItem(item, SPECIAL_P, -1);
	AddBoolModifierToItem(item, MODIFIER_LIGHT_ARMOR, true);
	
	item = ItemsFromID("cirass7");
	AddSkillModifierToItem(item, SKILL_LEADERSHIP, -10);
	AddSkillModifierToItem(item, SPECIAL_P, -1);
	AddBoolModifierToItem(item, MODIFIER_LIGHT_ARMOR, true);
	
	item = ItemsFromID("cirass8");
	AddSkillModifierToItem(item, SKILL_LEADERSHIP, -15);
	AddSkillModifierToItem(item, SKILL_SNEAK, 15);
	AddBoolModifierToItem(item, MODIFIER_LIGHT_ARMOR, true);
		
	item = ItemsFromID("cirass9");
	AddFloatModifierToItem(item, MODIFIER_MELEE_CRIT_CHANCE, 5);
	AddFloatModifierToItem(item, MODIFIER_OWN_STUN_CHANCE, 0.0);
	AddSkillModifierToItem(item, SKILL_F_LIGHT, 5);
	AddSkillModifierToItem(item, SKILL_FENCING, 5);
	AddSkillModifierToItem(item, SKILL_F_HEAVY, 5);
	AddSkillModifierToItem(item, SKILL_PISTOL, 5);
	AddBoolModifierToItem(item, MODIFIER_LIGHT_ARMOR, true);

	item = ItemsFromID("cirass10");
	AddFloatModifierToItem(item, MODIFIER_RANGE_CRIT_CHANCE, 5);
	AddFloatModifierToItem(item, MODIFIER_RANGE_RELOAD_SPEED_BONUS, 1.15);
	AddBoolModifierToItem(item, MODIFIER_PROTECT_RANGE_EXPLOSION, true);
	AddBoolModifierToItem(item, MODIFIER_PROTECT_RANGE_EXPLOSION_DOUBLE_BULLET, true);
	AddSkillModifierToItem(item, SPECIAL_A, -1);
	AddBoolModifierToItem(item, MODIFIER_HEAVY_ARMOR, true);

	
	item = ItemsFromID("suit1");
	AddSkillModifierToItem(item, SKILL_LEADERSHIP, 25);
	AddSkillModifierToItem(item, SKILL_SNEAK, -25);
	AddSkillModifierToItem(item, SPECIAL_C, 1);
	AddBoolModifierToItem(item, MODIFIER_LIGHT_ARMOR, true);
	
	item = ItemsFromID("suit2");
	AddSkillModifierToItem(item, SKILL_LEADERSHIP, 25);
	AddSkillModifierToItem(item, SKILL_SNEAK, -25);
	AddSkillModifierToItem(item, SPECIAL_C, 1);
	AddBoolModifierToItem(item, MODIFIER_LIGHT_ARMOR, true);
	
	item = ItemsFromID("suit3");
	AddSkillModifierToItem(item, SKILL_LEADERSHIP, 25);
	AddSkillModifierToItem(item, SKILL_SNEAK, -25);
	AddSkillModifierToItem(item, SPECIAL_C, 1);
	AddBoolModifierToItem(item, MODIFIER_LIGHT_ARMOR, true);
	
	item = ItemsFromID("suit4");
	AddSkillModifierToItem(item, SKILL_LEADERSHIP, -25);
	AddSkillModifierToItem(item, SKILL_SNEAK, 30);
	AddSkillModifierToItem(item, SPECIAL_P, -1);
	AddSkillModifierToItem(item, SPECIAL_A, 1);
	AddBoolModifierToItem(item, MODIFIER_LIGHT_ARMOR, true);

	item = ItemsFromID("suit5");
	AddSkillModifierToItem(item, SKILL_LEADERSHIP, 40);
	AddSkillModifierToItem(item, SKILL_SNEAK, -50);
	AddSkillModifierToItem(item, SKILL_SAILING, 5);
	AddSkillModifierToItem(item, SPECIAL_C, 1);
	AddBoolModifierToItem(item, MODIFIER_LIGHT_ARMOR, true);
	
	item = ItemsFromID("underwater");
	AddSkillModifierToItem(item, SKILL_LEADERSHIP, -20);
	AddSkillModifierToItem(item, SKILL_SNEAK, -100);
	AddSkillModifierToItem(item, SKILL_F_LIGHT, -15);
	AddSkillModifierToItem(item, SKILL_FENCING, -15);
	AddSkillModifierToItem(item, SKILL_F_HEAVY, -15);
	AddSkillModifierToItem(item, SKILL_PISTOL, -50);
	AddSkillModifierToItem(item, SPECIAL_P, -2);
	AddSkillModifierToItem(item, SPECIAL_E, -2);
	AddSkillModifierToItem(item, SPECIAL_A, -1);
	AddBoolModifierToItem(item, MODIFIER_HEAVY_ARMOR, true);
	
	
	
	item = ItemsFromID("indian_poison");
	AddBoolModifierToItem(item, MODIFIER_POISON_ATTACK, true);

	
}
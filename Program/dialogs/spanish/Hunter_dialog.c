void ProcessDialogEvent()
{
	ref NPChar, TempChar, sld;
	aref Link, Diag;

	int i, iTemp;
	string sTemp, sTemp1;
	string sGroup;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	// -----------------------------------Диалог первый - первая встреча
	case "exit":
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		break;

	case "First time":
		chrDisableReloadToLocation = false;
		// Lai_SetPlayerType(pchar);

		dialog.text = GetFullName(PChar) + "! " + " Hemos estado siguiéndote durante bastante tiempo, y finalmente eres nuestro.";
		Link.l1 = "¿Quién eres y qué quieres de mí?";
		Link.l1.go = "meeting";

		PChar.GenQuest.HunterStart = true;
		break;

	case "meeting":
		dialog.text = XI_ConvertString(Nations[sti(NPChar.nation)].Name) + " ha puesto una recompensa decente por tu cabeza, tenemos que entregarte a cualquiera de sus colonias y nos pagarán, no importa si estás muerto o vivo.";
		Link.l1 = "Escucha, te pagaré si me dejas en paz.";
		Link.l1.go = "Cost_Head";
		// boal 08.04.04 -->
		if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 2 || bBettaTestMode)
		{
			TempChar = characterFromID("Bug Fixer");
			SetRandomNameToCharacter(TempChar);
			Link.l2 = "" + GetSexPhrase("Disculpa, pero debes estar equivocado. Yo soy " + GetFullName(TempChar) + ", un comerciante bien conocido en estas tierras.", "Disculpa, pero debes estar equivocado. Solo soy una chica sencilla, y mi padre es " + GetFullName(TempChar) + ", un comerciante bien conocido en estas tierras.") + ".";
			Link.l2.go = "lier";
		}
		Link.l3 = "Está bien, puedes probar tu suerte, si así lo deseas.";
		Link.l3.go = "battle";
		break;

	case "lier":
		if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150) || bBettaTestMode)
		{
			dialog.text = "¡Oh! De hecho, podríamos estar equivocados. Por favor, perdónanos, " + GetAddress_Form(NPChar) + ".";
			Link.l1 = "Estas cosas suceden, no te preocupes...";
			Link.l1.go = "lier_2";
			AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
		}
		else
		{
			dialog.text = "¡Creo que estás mintiendo!";
			Link.l1 = "Escucha, te pagaré si me dejas en paz.";
			Link.l1.go = "Cost_Head";
			Link.l2 = "Está bien, puedes probar tu suerte, si así lo deseas.";
			Link.l2.go = "battle";
			AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
		}

		break;

	case "lier_2":
		AddDialogExitQuest("GoAway_Hunters_Land");
		DialogExit();
		break;
		// boal <--

	case "battle":
		AddDialogExitQuest("Battle_Hunters_Land"); // BOAL Весь код я перенес сюда по всем нациям, просто не переименовал
		DialogExit();
		break;

	case "Cost_Head2":
		AddMoneyToCharacter(pchar, -sti(PChar.HunterCost));

		AddDialogExitQuest("GoAway_Hunters_Land");
		DialogExit();
		break;

	case "Cost_Head":
		dialog.text = "Creo que " + PChar.HunterCost + " pesos nos vendrán bien.";
		if (makeint(Pchar.money) < sti(PChar.HunterCost))
		{
			Link.l1 = "Pero no tengo tal dinero.";
			Link.l1.go = "NoMoney";
		}
		else
		{
			Link.l1 = "Aquí está tu dinero, tómalo y piérdete.";
			Link.l1.go = "Cost_Head2";
			Link.l2 = "Dar tal suma a canallas como ustedes... Supongo que preferiría despellajarlos a todos aquí mismo!";
			Link.l2.go = "battle";
		}
		break;

	case "NoMoney":
		dialog.text = "¡En ese caso nuestra charla ha terminado!";
		Link.l1 = "Jamás me atraparás vivo.";
		Link.l1.go = "battle";
		break;

	case "TreasureHunter":
		dialog.text = "Espera, " + GetSexPhrase("compañero", "chica") + "... Creo que llevas algo interesante encima. Los amigos deberían compartir los tesoros encontrados entre ellos, ¿no crees?";
		Link.l1 = "Escucha, te pagaré si me dejas en paz.";
		Link.l1.go = "Cost_Head";
		// boal 08.04.04 -->
		if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 3)
		{
			TempChar = characterFromID("Bug Fixer");
			SetRandomNameToCharacter(TempChar);
			Link.l2 = "" + GetSexPhrase("¡Discúlpeme, pero debe estar equivocado. Yo soy " + GetFullName(TempChar) + ", un ciudadano bien conocido en estas tierras, y ciertamente no soy un buscador de tesoros.", "¡Disculpe, pero debe estar equivocado. Solo soy una chica simple, y no una buscadora de tesoros. Y mi padre es " + GetFullName(TempChar) + " un ciudadano bien conocido en estas tierras") + "!";
			Link.l2.go = "TreasureHunterLier";
		}
		Link.l3 = "Bueno, parece que es hora de que vuestras cabezas se separen de vuestros cuerpos.";
		Link.l3.go = "battle";
		break;

	case "TreasureHunterLier":
		if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150))
		{
			dialog.text = "¡Oh! Podríamos estar equivocados, entonces. Por favor, perdónanos, " + GetAddress_Form(NPChar) + ".";
			Link.l1 = "Estas cosas pasan, no te preocupes por eso...";
			Link.l1.go = "lier_2";
			AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
		}
		else
		{
			dialog.text = "¡Creo que estás mintiendo!";
			Link.l1 = "Entonces escucha la canción de mi espada.";
			Link.l1.go = "battle";
			AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
		}
		break;

	case "TreasureCaptain":
		dialog.text = LinkRandPhrase("¡Así que tú eres el que se llevó mi mapa del tesoro! Creo, compañero, que es hora de entregar todo lo que has tomado...", "¡Oh, un rival! No llegarás muy lejos, estás ralentizado por el peso de mis tesoros...", "¡Huh, finalmente te he alcanzado! Todos los tesoros en esta caverna me pertenecen, ¿lo entiendes? ¡Ahora vacía tus bolsillos, amigo!");
		Link.l1 = LinkRandPhrase("¡Es hora de que conozcas mi espada, compañero!", "¿Tus tesoros? Quisiste decir que eran tuyos, ¡porque ahora son míos!", "Preferiría vaciar tu estómago con mi espada, amigo.");
		Link.l1.go = "TreasureCaptain_fight";
		break;

	case "TreasureCaptain_fight":
		DialogExit();
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться // patch-6
		for (i = 1; i <= 4; i++)
		{
			sld = characterFromId("Treasure_sailor_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "TreasureOfficer":
		dialog.text = LinkRandPhrase("Entonces, el coronel tenía razón, el tesoro estaba escondido en esta cueva... ¡Vacía tus bolsillos, marinero!", "Entonces finalmente te hemos atrapado después de todo este rastreo a través de todas estas malditas junglas entre espinas y pantanos. Ahora, bastardo, nos darás todo...", "¡Eh, marinero! Los tesoros de ese pirata nos pertenecen, así que aleja tus sucias manos de ellos!");
		Link.l1 = LinkRandPhrase("Seguramente, no esperaba eso de un oficial del ejército. Pero está bien, te enseñaré una lección de todos modos...", "Míralo, un pirata con uniforme de oficial...", "De hecho, soldados y piratas no son tan diferentes estos días...");
		Link.l1.go = "TreasureOfficer_fight";
		break;

	case "TreasureOfficer_fight":
		DialogExit();
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться // patch-6
		for (i = 1; i <= 4; i++)
		{
			sld = characterFromId("Treasure_soldier_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	// генератор "A reason to hurry"
	case "ReasonToFast_THunter_1":
		if (CheckAttribute(pchar, "GenQuest.CannotWait"))
			DeleteAttribute(pchar, "GenQuest.CannotWait");
		dialog.text = "Y aquí llega nuestro oro. Al menos nuestra espera no fue en vano.";
		link.l1 = RandPhraseSimple("¿De qué están hablando, señores? ¡Soy un representante de la Compañía Holandesa de las Indias Occidentales y solo estoy de paso por aquí! Me he detenido para admirar la vista de la costa.", "Temo que me has confundido con otra persona. Yo soy " + GetSexPhrase("Francua Marie Paganel, ", "Maria-Theresa, ") + "un naturalista. Estoy recolectando muestras de la flora de la zona. ¿Quieres echar un vistazo a mi colección de hojas de yuca? ¡Tengo varias muy interesantes!");
		link.l1.go = "ReasonToFast_THunter_2";
		link.l2 = "¿Qué quieres?! ¡Mantente fuera de mi camino!";
		link.l2.go = "ReasonToFast_THunter_2";
		break;

	case "ReasonToFast_THunter_2":
		ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.Treasure.Location);
		dialog.text = "Oh no, " + GetSexPhrase("mi querido amigo", "mi bonita chica") + ". Eso no funcionará. Sabemos con certeza que eras dueño del mapa de " + GetName(pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN) + ". Y era tal avaro que sus cofres estaban a punto de romperse por dentro llenos de dinero. Así que no vamos a irnos con las manos vacías.";
		link.l1 = "Tienes razón. Los cofres estaban de hecho llenos. Pero no los conseguirás. Puedes intentar visitar esa cueva, un par de cubos agujereados deberían seguir allí.";
		link.l1.go = "ReasonToFast_THunter_3";
		if (ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) && ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
		{
			link.l2 = "Tienes razón. Puedes tener tu tesoro. Solo ten en cuenta que no te hará feliz, ya que está manchado con sangre.";
			link.l2.go = "ReasonToFast_THunter_4";
		}
		break;

	case "ReasonToFast_THunter_3":
		dialog.text = "" + GetSexPhrase("Je, capitán, eres demasiado joven para morir, ¿no es así...", "Je, muchacha, eres demasiado joven para morir, ¿no es así...") + "?";
		link.l1 = "¡De hecho, no voy a morir!";
		link.l1.go = "ReasonToFastTHunter_Fight";
		break;

	case "ReasonToFast_THunter_4":
		dialog.text = "¡Esas son palabras de una persona razonable!";
		link.l1 = "Maldición a ti y a todos esos tesoros...";
		link.l1.go = "ReasonToFast_THunter_GoAway";
		break;

	case "ReasonToFast_THunter_GoAway":
		iTemp = ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8));
		if (iTemp > 0)
		{
			ReasonToFast_GetTreasure("icollection", iTemp);
			Log_Info(XI_ConvertString("Dar artículo"));
			PlayStereoSound("interface\important_item.wav");
		}

		iTemp = ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7));
		if (iTemp > 0)
		{
			ReasonToFast_GetTreasure("Chest", iTemp);
			Log_Info(XI_ConvertString("Dar artículo"));
			PlayStereoSound("interface\important_item.wav");
		}
		if (pchar.questTemp.ReasonToFast == "GetTreasure")
		{
			AddQuestRecord("ReasonToFast", "24");
			AddQuestUserData("ReasonToFast", "sName", GetName(pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN));
			CloseQuestHeader("ReasonToFast");
		}
		DialogExit();
		AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;

	case "ReasonToFastTHunter_Fight":
		sGroup = "LAND_HUNTER";
		sTemp = "LandHunter0";
		iTemp = sti(pchar.HunterCost.Qty);
		chrDisableReloadToLocation = true;
		LAi_SetPlayerType(pchar);
		LAi_SetFightMode(pchar, true);
		for (i = 1; i <= iTemp; i++)
		{
			sld = CharacterFromID(sTemp + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, sGroup);
		}

		LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck(sGroup, "OpenTheDoors");
		LAi_group_SetCheck(sGroup, "ReasonToFast_TrHuntersDied");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "ReasonToFast_HunterShore1":
		dialog.text = "Oye," + GetSexPhrase("compañero", "muchacha") + "¡ " + GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " dijo que tenías algo para nosotros.";
		link.l1 = "¿Qué quieres decir?";
		link.l1.go = "ReasonToFast_HunterShore11";
		pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
		pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
		break;

	case "ReasonToFast_HunterShore11":
		if (pchar.questTemp.ReasonToFast == "GetMap")
		{
			dialog.text = "Un mapa de " + GetName(pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN);
			link.l1 = "Tómalo y saluda a " + GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ". Dile que nos encontraremos pronto...";
			link.l1.go = "ReasonToFast_HunterShore12_1";
			link.l2 = GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " está gravemente equivocado si piensa que voy a sacar las castañas del fuego para él.";
			link.l2.go = "ReasonToFast_HunterShore23";
		}
		if (pchar.questTemp.ReasonToFast == "LakeyExitSuccess")
		{
			dialog.text = "Joyas que has robado del gobernador.";
			if (ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) && ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
			{
				link.l1 = "Tómalo y saluda a " + GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ". Dile que nos encontraremos pronto...";
				link.l1.go = "ReasonToFast_HunterShore12_2";
			}
			link.l2 = GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " está gravemente equivocado si piensa que voy a sacarle las castañas del fuego.";
			link.l2.go = "ReasonToFast_HunterShore23";
		}
		pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
		pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
		chrDisableReloadToLocation = false;
		break;

	case "ReasonToFast_HunterShore12_1":
		TakeNItems(pchar, "mapQuest", -1);
		AddQuestRecord("ReasonToFast", "20");
		AddQuestUserData("ReasonToFast", "sText", "un mapa de");
		AddQuestUserData("ReasonToFast", "sName", GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
		CloseQuestHeader("ReasonToFast");
		DialogExit();
		AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;

	case "ReasonToFast_HunterShore12_2":
		iTemp = ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8));
		if (iTemp > 0)
		{
			ReasonToFast_GetTreasure("icollection", iTemp);
			Log_Info(XI_ConvertString("Dar artículo"));
			PlayStereoSound("interface\important_item.wav");
		}

		iTemp = ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7));
		if (iTemp > 0)
		{
			ReasonToFast_GetTreasure("Chest", iTemp);
			Log_Info(XI_ConvertString("Dar artículo"));
			PlayStereoSound("interface\important_item.wav");
		}
		AddQuestRecord("ReasonToFast", "20");
		AddQuestUserData("ReasonToFast", "sText", "treasures");
		AddQuestUserData("ReasonToFast", "sName", GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
		CloseQuestHeader("ReasonToFast");
		DialogExit();
		ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.city + "_townhall");
		ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.LakeyLocation);
		AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;

	case "ReasonToFast_HunterShore2":
		dialog.text = "Eh," + GetSexPhrase("compañero", "chica") + "¡ " + GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN) + " tiene varias preguntas para ti.";
		link.l1 = "¿Y por qué no les preguntaría él mismo?";
		link.l1.go = "ReasonToFast_HunterShore21";
		chrDisableReloadToLocation = false;
		break;

	case "ReasonToFast_HunterShore21":
		dialog.text = "No de acuerdo a su rango. Arruinaste nuestra operación y perdimos " + sti(pchar.questTemp.ReasonToFast.p10) + " pesos debido a ti. Así que ahora tienes una deuda que pagar.";
		link.l1 = "Tómalo y saluda a " + GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ". Dile que nos encontraremos pronto...";
		link.l1.go = "ReasonToFast_HunterShore22";
		link.l2 = GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " está gravemente equivocado si piensa que voy a sacar las castañas del fuego por él.";
		link.l2.go = "ReasonToFast_HunterShore23";
		break;

	case "ReasonToFast_HunterShore22":
		if (makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p10))
		{
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.questTemp.ReasonToFast.p10)));
			AddQuestRecord("ReasonToFast", "20");
			AddQuestUserData("ReasonToFast", "sText", "money");
			AddQuestUserData("ReasonToFast", "sName", GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
			DialogExit();
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		}
		else
		{
			dialog.text = "¡Oh, no tienes tal dinero! Bueno, has hecho tu elección...";
			link.l1 = "Hace mucho tiempo...";
			link.l1.go = "ReasonToFastTHunter_Fight";
			if (pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
			{
				pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
				pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
			}
		}
		break;

	case "ReasonToFast_HunterShore23":
		dialog.text = "Bueno, has hecho tu elección...";
		link.l1 = "Hace mucho tiempo...";
		link.l1.go = "ReasonToFastTHunter_Fight";
		if (pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
		{
			pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
			pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
		}
		break;
		// генератор "A reason to hurry"
	}
}

string GetLocHunterName()
{
	int nLoc = FindLocation(Pchar.location);
	int nFile = LanguageOpenFile("LocLables.txt");
	string ret = "";

	if (nFile >= 0)
	{
		if (CheckAttribute(&locations[nLoc], "islandId"))
		{
			if (locations[nLoc].islandId != "Mein")
			{
				ret = "isla de " + LanguageConvertString(nFile, locations[nLoc].islandId);
			}
			else
			{
				ret = "continente de ";
			}
		}
		//
		if (CheckAttribute(&locations[nLoc], "fastreload"))
		{
			ret += " (" + LanguageConvertString(nFile, locations[nLoc].fastreload + " Town") + ")";
		}
		// ret += LanguageConvertString(nFile, locations[nLoc].id.label);
		LanguageCloseFile(nFile);
	}
	return ret;
}

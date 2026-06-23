void ProcessDialogEvent()
{
	ref NPChar, sld;
	ref arItem;
	aref Link, Diag;
	int i, iShipType, iShipGoods;
	int jewelType;
	string sItemName = "";
	string sItem;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = int(npchar.EncQty);
	string sTemp = "Patrol" + locations[FindLocation(npchar.location)].index + "_";
	string sGroup = "PatrolGroup_" + locations[FindLocation(npchar.location)].index;
	string sTemp1, sTemp2;

	switch (Dialog.CurrentNode)
	{
	case "exit":
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		break;

	case "exit_fight":
		for (i = 0; i < iTemp; i++)
		{
			sld = CharacterFromID(sTemp + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, sGroup);
		}
		LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck(sGroup, "LandEnc_PatrolAfrer");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "exit_noFight":
		for (i = 0; i < iTemp; i++)
		{
			sld = CharacterFromID(sTemp + i);
			sld.Dialog.CurrentNode = "GoodBye";
			sld.greeting = "soldier_common";
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			LAi_group_MoveCharacter(sld, sGroup);
		}
		LAi_group_SetCheck(sGroup, "LandEnc_PatrolAfrer");
		DialogExit();
		break;

	case "First Time":
		for (i = 0; i < iTemp; i++)
		{
			sld = CharacterFromID(sTemp + i);
			LAi_type_actor_Reset(sld);
			LAi_RemoveCheckMinHP(sld);
		}
		if (GetNationRelation2MainCharacter(int(NPChar.nation)) == RELATION_ENEMY && int(NPChar.nation) != PIRATE)
		{
			if (pchar.nation == npchar.nation)
			{
				dialog.text = RandPhraseSimple("Vaya, parece que este granuja ha levantado la alarma en " + XI_ConvertString("Colony" + npchar.city + "Dat") + "¡Capturad" + GetSexPhrase("lo", "la") + "!", "¡Eh, mira esto! Varios " + NationNamePeople(int(pchar.nation)) + " lograr ser enemigos con " + NationNameAblative(int(npchar.nation)) + "¡Atrapad al malandrín!");
			}
			else
			{
				dialog.text = RandPhraseSimple("Agente enemigo cerca " + XI_ConvertString("Colony" + npchar.city + "Gen") + "¡Capturad" + GetSexPhrase("lo", "la") + "!", "Oye, mira, " + NationNamePeople(int(pchar.nation)) + " están caminando casi en " + XI_ConvertString("Colony" + npchar.city + "Dat") + "¡Agárralo inmediatamente!");
			}
			link.l1 = RandPhraseSimple("Bueno, puedes intentarlo. Estamos solos aquí...", "Je, nadie te echará una mano por aquí.");
			link.l1.go = "exit_fight";
		}
		else
		{
			// belamour legendary edition
			sTemp1 = "";
			if (isMainCharacterPatented() && int(Items[int(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == int(Items[int(pchar.EquipedPatentId)].Nation))
				sTemp1 = "¡Vicealmirante! ";
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
				sTemp1 = "¡Su Excelencia el Gobernador General! ";

			dialog.text = LinkRandPhrase("¡Permíteme presentarme! Soy un oficial de patrulla de " + XI_ConvertString("Colony" + npchar.city + "Gen") + ", estamos buscando a un convicto fugado.", "Hola, soy el jefe de esta patrulla. Estamos buscando a un esclavo fugado de " + XI_ConvertString("Colony" + npchar.city + "Gen") + ".", "Saludos a ti, " + GetAddress_Form(NPChar) + ". Mi destacamento está patrullando el territorio cerca de " + XI_ConvertString("Colony" + npchar.city + "Gen") + ".");
			Link.l1 = LinkRandPhrase("Muy bien. ¿Cómo puedo ayudarte?", "Muy bien. ¿Puedo ayudarte en algo, " + GetAddress_FormToNPC(NPChar) + "?", "Muy bien. ¿Hay algo que pueda hacer por ti?");
			Link.l1.go = "Node_2";
		}
		break;

	case "Node_2":
		dialog.text = RandPhraseSimple("¿Has visto algo sospechoso en el distrito?", "¿Has conocido a alguien que parezca sospechoso, " + GetAddress_Form(NPChar) + "?");
		Link.l1 = RandPhraseSimple("No, nada parecido.", "No, oficial, todo parecía tranquilo.");
		Link.l1.go = "Node_3";
		break;

	case "Node_3":
		Diag.TempNode = "GoodBye";
		dialog.text = RandPhraseSimple("Bueno, no te retrasaré más. Adiós, " + GetAddress_Form(NPChar) + ".", "Entiendo. Adiós, entonces.");
		Link.l1 = "Buena suerte.";
		Link.l1.go = "exit_noFight";
		break;

	case "GoodBye":
		Diag.TempNode = "GoodBye";
		dialog.text = LinkRandPhrase("No nos distraigas de nuestro deber.", "¡Me gustaría que nos dejaras en paz!", "Oh, eres tú de nuevo... Sigue tu propio camino y no nos molestes.");
		Link.l1 = "Bien.";
		Link.l1.go = "Exit";
		break;

	// генератор "A reason to hurry"
	case "Reason_To_Fast_1":
		if (Pchar.Location == Pchar.location.from_sea)
		{
			dialog.text = "Hmm... No te he visto antes. ¿Quién eres tú?";
			link.l1 = "Soy el que estás esperando...";
			link.l1.go = "Reason_To_Fast_11";
			link.l2 = "Soy el capitán " + GetFullName(pchar) + ". Me gustaría saber por qué tendrías tanta prisa que casi te olvidas los pantalones en el burdel...";
			link.l2.go = "Reason_To_Fast_21";
			link.l3 = "Soy capitán " + GetFullName(pchar) + ". Solo estoy dando un paseo por aquí, respirando la brisa marina salada...";
			link.l3.go = "Reason_To_Fast_31";
		}
		else
		{
			Diag.TempNode = "GoodBye";
			dialog.text = "Por fin has llegado. Pensé que nunca te volvería a ver. ¿Y quién es ese tipo contigo?";
			link.l1 = "¿Qué tipo?";
			link.l1.go = "Reason_To_Fast_Hunter";
		}
		break;

	case "Reason_To_Fast_Hunter":
		DialogExit();
		AddDialogExitQuest("ReasonToFast_MeetHunter");
		break;

	case "Reason_To_Fast_11":
		dialog.text = "No pareces alguien en quien yo confiaría " + GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + ".";
		if (!CheckCharacterItem(pchar, "mapQuest"))
		{
			link.l1 = "Está bien, le diré todo lo que has dicho.";
			link.l1.go = "Reason_To_Fast_12";
		}
		link.l2 = "¿Y quién es este " + GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + "?";
		link.l2.go = "Reason_To_Fast_13";
		break;

	case "Reason_To_Fast_21":
		dialog.text = "La curiosidad ha matado a mucha más gente que los gatos...";
		link.l1 = "¡Vaya, vaya!";
		link.l1.go = "Reason_To_Fast_ExitFight";
		pchar.questTemp.ReasonToFast = "PatrolAfter";
		break;

	case "Reason_To_Fast_31":
		Diag.TempNode = "Reason_To_Fast_GoodBye";
		dialog.text = "La marea está llegando. Sería mejor que dejaras la cala, el agua aquí sube hasta el nivel de la palmera.";
		link.l1 = "Sin problema, soy buen nadador.";
		link.l1.go = "Reason_To_Fast_GoodBye_0";
		pchar.questTemp.ReasonToFast = "MeetPatrolFail";
		break;

	case "Reason_To_Fast_12":
		jewelType = int(pchar.questTemp.ReasonToFast.p4);
		pchar.questTemp.ReasonToFast.item = "jewelry" + jewelType;
		sItem = "jewelry" + jewelType;
		switch (jewelType)
		{
		case 1:
			sItemName = "amethysts";
			break;
		case 2:
			sItemName = "diamonds";
			break;
		case 3:
			sItemName = "rubies";
			break;
		case 4:
			sItemName = "emeralds";
			break;
		}
		pchar.questTemp.ReasonToFast.jewType = sItemName;
		dialog.text = "Está bien, está bien. Se prometieron 30 " + sItemName + "¿contigo?";
		link.l1 = GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " dijo que no había suficiente tiempo para recolectar tantas gemas. Me ordenó ofrecer dinero en su lugar.";
		link.l1.go = "Reason_To_Fast_14";
		if (GetCharacterItem(pchar, pchar.questTemp.ReasonToFast.item) >= 30)
		{
			link.l2 = "Aquí tienes.";
			link.l2.go = "Reason_To_Fast_15";
		}
		break;

	case "Reason_To_Fast_13":
		dialog.text = "¡Heh! ¡Lo sabrás en el infierno!";
		link.l1 = "Qué autoconfianza ...";
		link.l1.go = "Reason_To_Fast_ExitFight";
		pchar.questTemp.ReasonToFast = "PatrolAfter";
		break;

	case "Reason_To_Fast_14":
		dialog.text = "Está bien, entonces me debes " + int(pchar.questTemp.ReasonToFast.p5) + " pesos, como habíamos acordado.";
		link.l1 = "¿No es eso un poco demasiado?";
		link.l1.go = "Reason_To_Fast_16";
		if (int(pchar.money) >= int(pchar.questTemp.ReasonToFast.p5))
		{
			link.l2 = "Aquí tienes.";
			link.l2.go = "Reason_To_Fast_17";
		}
		link.l3 = "¡Pero no tengo tanto dinero encima!";
		link.l3.go = "Reason_To_Fast_18";
		AddQuestRecord("ReasonToFast", "9");
		AddQuestUserData("ReasonToFast", "sText", pchar.questTemp.ReasonToFast.jewType);
		break;

	case "Reason_To_Fast_15":
		TakeNItems(pchar, pchar.questTemp.ReasonToFast.item, -30);
		dialog.text = "Todo está de acuerdo con el acuerdo. Aquí tienes. Este mapa fue tomado del pirata ahorcado, sobre quien " + GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " había preguntado.";
		link.l1 = "¡El trato está hecho!";
		link.l1.go = "Reason_To_Fast_15_1";
		break;

	case "Reason_To_Fast_15_1":
		Diag.TempNode = "Reason_To_Fast_GoodBye";
		DialogExit();
		AddQuestRecord("ReasonToFast", "10");
		AddQuestUserData("ReasonToFast", "sName", GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
		pchar.questTemp.ReasonToFast = "PatrolSuccess_2";
		GiveItem2Character(pchar, "mapQuest");
		arItem = ItemsFromID("mapQuest");
		ReasonToFast_GenerateTreasureMap(arItem);
		DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther"); // можем говорить с губером
		AddDialogExitQuest("pchar_back_to_player");
		LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);
		break;

	case "Reason_To_Fast_16":
		dialog.text = "Hemos saldado la suma con " + GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_ABL) + " por adelantado. No me gusta nada. ¡Matad" + GetSexPhrase("lo", "la") + ", muchachos!";
		link.l1 = "¡Está bien, puedes intentarlo!";
		link.l1.go = "Reason_To_Fast_ExitFight";
		pchar.questTemp.ReasonToFast = "PatrolAfter";
		break;

	case "Reason_To_Fast_17":
		pchar.questTemp.ReasonToFast = "PatrolSuccess_1";
		AddMoneyToCharacter(pchar, -int(int(pchar.questTemp.ReasonToFast.p5)));
		pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха
		if (CheckAttribute(pchar, "questTemp.ReasonToFast.chain"))
			DeleteAttribute(pchar, "questTemp.ReasonToFast.chain");
		if (CheckAttribute(pchar, "questTemp.ReasonToFast.ShipName"))
			DeleteAttribute(pchar, "questTemp.ReasonToFast.ShipName");
		if (CheckAttribute(pchar, "questTemp.ReasonToFast.ShipTypeName"))
			DeleteAttribute(pchar, "questTemp.ReasonToFast.TypeName");
		switch (int(pchar.questTemp.ReasonToFast.target))
		{
		case 0: // корабль с товаром
			sTemp1 = generateRandomNameToShip(int(pchar.questTemp.ReasonToFast.GuardNation));
			iShipType = ReasonToFast_GetVictimShipType();
			iShipGoods = ReasonToFast_GetVictimShipGoods();
			dialog.text = "¡Excelente! Ahora vamos al grano. Hemos interceptado eso " + GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipTypeName) + " '" + sTemp1 + "' con una carga de " + GetGoodsNameAlt(iShipGoods) + ", la tripulación ya está detenida y la 'carga' aún está a bordo. La tripulación fue contratada entre los desesperados en el puerto, y no llegarán al puerto hasta mañana. Puedes lidiar con ellos como quieras.";
			link.l1 = "Está bien. Transmitiré tus palabras " + GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ".";
			link.l1.go = "Reason_To_Fast_GoodBye_0";
			pchar.questTemp.ReasonToFast.chain = "A0";
			pchar.questTemp.ReasonToFast.ShipName = sTemp1;
			DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther"); // можем говорить с губером
			AddQuestRecord("ReasonToFast", "11");
			AddQuestUserData("ReasonToFast", "sShipType", pchar.questTemp.ReasonToFast.ShipTypeName);
			AddQuestUserData("ReasonToFast", "sShipName", sTemp1);
			AddQuestUserData("ReasonToFast", "sGoodsName", GetGoodsNameAlt(iShipGoods));
			ReasonToFast_GenerateVictimShip(iShipType, iShipGoods);
			break;

		case 1: // сокровища губернатора
			switch (rand(3))
			{
			case 0:
				sTemp1 = "La dote de la hija del gobernador esta";
				break;
			case 1:
				sTemp1 = "Los regalos del Gobernador para el Virrey está";
				break;
			case 2:
				sTemp1 = "Los regalos para el jubileo del gobernador está";
				break;
			case 3:
				sTemp1 = "El dinero de la 'pensión' del gobernador está";
				break;
			}
			switch (rand(3))
			{
			case 0:
				sTemp2 = "Engañar";
				break;
			case 1:
				sTemp2 = "Travesuras";
				break;
			case 2:
				sTemp2 = "Broma";
				break;
			case 3:
				sTemp2 = "Travieso";
				break;
			}
			pchar.questTemp.ReasonToFast.password = sTemp2;
			sTemp2 = generateRandomNameToShip(int(pchar.questTemp.ReasonToFast.GuardNation));
			dialog.text = "¡Excelente! " + sTemp1 + " guardado en su tocador. El barco mensajero llegará cualquier día, pero aún deberías poder manejarlo. El lacayo es 'nuestro' hombre. Contraseña: '" + pchar.questTemp.ReasonToFast.password + "', respuesta: '" + sTemp2 + "'.'";
			link.l1 = "Está bien. Pasaré tu palabra " + GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ".";
			link.l1.go = "Reason_To_Fast_GoodBye_0";
			pchar.questTemp.ReasonToFast.chain = "A1";
			AddQuestRecord("ReasonToFast", "12");
			pchar.questTemp.ReasonToFast.ShipName = sTemp2;
			DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther"); // можем говорить с губером

			pchar.quest.ReasonToFast_ClearLakey.win_condition.l1 = "Timer";
			pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
			pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
			pchar.quest.ReasonToFast_ClearLakey.function = "ReasonToFast_ClearLakey";
			break;
		}
		break;

	case "Reason_To_Fast_18":
		if (int(pchar.money) >= int(pchar.questTemp.ReasonToFast.p5))
		{
			dialog.text = "¿Estás intentando engañarme?! ¡Eres un perro!";
			link.l1 = "¡Cállate de una puta vez!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";
		}
		else
		{
			dialog.text = "¡Bebiste! ¡Mi! ¡Dinero!... Argh.";
			link.l1 = "¡Mierda!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";
		}
		break;

	case "Reason_To_Fast_GoodBye_0":
		LAi_SetPlayerType(pchar);
		for (i = 0; i < iTemp; i++)
		{
			sld = CharacterFromID(sTemp + i);
			sld.Dialog.CurrentNode = "Reason_To_Fast_GoodBye";
			sld.greeting = "soldier_common";
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			LAi_group_MoveCharacter(sld, sGroup);
		}
		pchar.quest.RemovePatrolFromShore.win_condition.l1 = "ExitFromLocation";
		pchar.quest.RemovePatrolFromShore.win_condition.l1.location = pchar.location;
		pchar.quest.RemovePatrolFromShore.function = "ReasonToFast_DeletePatrolFromShore";
		DialogExit();
		break;

	case "Reason_To_Fast_GoodBye":
		Diag.TempNode = "Reason_To_Fast_GoodBye";
		dialog.text = "Será mejor que abandones la cala, la marea ya está llegando...";
		link.l1 = "Sí, sí, me estoy yendo.";
		link.l1.go = "Exit";
		break;

	case "Reason_To_Fast_ExitFight":
		pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(int(pchar.questTemp.ReasonToFast.GuardNation));
		SetNationRelation2MainCharacter(int(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY);

		pchar.GenQuest.HunterScore2Pause = 1;	// НЗГ не начисляются
		pchar.GenQuest.ReputationNotChange = 1; // репутацию не менять

		chrDisableReloadToLocation = true;
		LAi_SetPlayerType(pchar);
		LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);
		for (i = 0; i < iTemp; i++)
		{
			sld = CharacterFromID(sTemp + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, sGroup);
		}
		if (pchar.questTemp.ReasonToFast == "PatrolAngry")
		{
			sld = CharacterFromID("ReasonToFast_Hunter");
			if (sld != -1)
			{
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
		}
		LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck(sGroup, "OpenTheDoors");
		LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "Reason_To_Fast_AfterHunter1":
		dialog.text = "¿No habíamos acordado que el mensajero debe estar solo?";
		link.l1 = "Falta de coordinación. El mensajero se perdió. Yo soy el sustituto.";
		link.l1.go = "Reason_To_Fast_11";
		link.l2 = "Y he venido solo, pero no por lo que estás esperando.";
		link.l2.go = "Reason_To_Fast_AfterHunter2";
		break;

	case "Reason_To_Fast_AfterHunter2":
		dialog.text = "Entonces, finalmente me has rastreado, lamento lo que va a suceder...";
		link.l1 = "¡Arrgh!";
		link.l1.go = "Reason_To_Fast_ExitFight";
		pchar.questTemp.ReasonToFast = "PatrolAfterHunter";
		break;

	case "Reason_To_Fast_AfterHunter3":
		dialog.text = "¡Maldito seas! ¡Casi creí en eso! ¡Guardias! ¡Atrápen" + GetSexPhrase("lo", "la") + "...!";
		link.l1 = "¡Inténtenlo, bastardos!";
		link.l1.go = "Reason_To_Fast_ExitFight";
		pchar.questTemp.ReasonToFast = "PatrolAngry";
		break;
		// генератор "A reason to hurry"
	}
}

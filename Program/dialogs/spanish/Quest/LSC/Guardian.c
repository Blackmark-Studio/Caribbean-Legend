// диалог протекторов, солдат и мушкетеров кланов LSC
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "¿Qué demonios quieres?";
		link.l1 = "No, no es nada.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

		//------------------------------------- фразы гардов нарвалов --------------------------------------------
		// пост нарвалов на проход на Сан-Габриэль
	case "Narval_warning":
		if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
		{
			dialog.text = LinkRandPhrase("¡Muchachos, cuidado, ahí está el psicópata! ¡A las armas!", "¡El enemigo está aquí! ¡A las armas!", "¡Ah, eres un bastardo! ¡Ahora te daremos una lección!");
			link.l1 = "¡Mierda!";
			link.l1.go = "check_parol_fight";
			break;
		}
		ref location = &Locations[FindLocation(pchar.location)];
		if (!CheckAttribute(location, "nrv_parolinfo"))
		{
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend"))
			{
				dialog.text = "Detente, amigo. Territorios del Narval adelante, la entrada está prohibida para los extraños. Solo puedes pasar con una invitación. ¿Conoces la contraseña?";
				link.l1 = "Sí.";
				link.l1.go = "Narval_warning_yes";
				link.l2 = "No.";
				link.l2.go = "Narval_warning_no";
			}
			else // если друг нарвалам
			{
				dialog.text = "A-ah, " + GetFullName(pchar) + "Hola, amigo, estamos advertidos de que puedes caminar libremente aquí. ¡Bienvenido!";
				link.l1 = "¡Gracias, amigo!";
				link.l1.go = "exit";
			}
			location.nrv_parolinfo = "true";
		}
		else
		{
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend"))
			{
				dialog.text = "Espero que no hayas olvidado una contraseña...";
				link.l1 = "No te preocupes...";
				link.l1.go = "exit";
			}
			else // если друг нарвалам
			{
				dialog.text = TimeGreeting() + ", " + pchar.name + ". ¿Cómo estás?";
				link.l1 = "¡Bien, gracias!";
				link.l1.go = "exit";
			}
		}
		NextDiag.TempNode = "Narval_warning_repeat";
		DeleteAttribute(npchar, "protector.CheckAlways");
		break;

	case "Narval_warning_yes":
		dialog.text = "Entonces ve y dile eso al tipo duro de allí. No trates de engañarlo, nuestros muchachos con mosquetes saben qué hacer. Así que si planeas alguna trampa, será mejor que te des la vuelta y te vayas. Ahora. Te lo advertí.";
		link.l1 = "Está bien, amigo. Lo tengo.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Narval_warning_repeat";
		break;

	case "Narval_warning_no":
		dialog.text = "Entonces, no tienes nada que hacer aquí si no vas a terminar con tu vida, claro. ¿O estás bromeando, eh? ¿Te estás burlando de mí? En realidad, no me importa. Baja, mi trabajo es advertir, no detener. No regresarás si no sabes la contraseña.";
		link.l1 = "Está bien, amigo. Lo entiendo.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Narval_warning_repeat";
		break;

	case "Narval_warning_repeat":
		if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend"))
		{
			dialog.text = "¿Qué más necesitas? ¡Baja al 'San Gabriel' o piérdete!";
			link.l1 = "...";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "Lo siento, " + pchar.name + ", pero estoy de servicio. No me molestes, amigo. ¡Sigue adelante!";
			link.l1 = "...";
			link.l1.go = "exit";
		}
		NextDiag.TempNode = "Narval_warning_repeat";
		break;

	case "Narval_parol":
		if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
		{
			dialog.text = LinkRandPhrase("¡Muchachos, cuidado, ahí viene el psicópata! ¡A las armas!", "¡El enemigo está aquí! ¡A las armas!", "¡Ah, eres un bastardo! ¡Ahora te daremos una lección!");
			link.l1 = "¡Maldición!";
			link.l1.go = "check_parol_fight";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend"))
		{
			dialog.text = "Lo siento, " + pchar.name + ", pero estoy de servicio. No me molestes, amigo. ¡Sigue tu camino!";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol";
			break;
		}
		dialog.text = "¡Quédate justo donde estás! ¡No eres uno de los nuestros!";
		link.l1 = "Estoy de pie, de pie.";
		link.l1.go = "check_parol";
		break;

	case "check_parol":
		dialog.text = "Di una contraseña y hazlo claro y fuerte.";
		link.l1.edit = 3;
		link.l1 = "";
		link.l1.go = "check_parol_1";
		break;

	case "check_parol_1":
		sTemp = GetStrSmallRegister(dialogEditStrings[3]);
		if (sTemp == sNrvParol && CheckAttribute(pchar, "questTemp.LSC.NParol_bye"))
		{
			dialog.text = "Está bien, puedes proceder.";
			link.l1 = "Gracias, amigo...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_NARVAL");
			pchar.questTemp.LSC.parol_nrv = "true";
		}
		else
		{
			dialog.text = "Mm... ¡Muchachos! ¡Tenemos compañía!";
			link.l1 = "¡Mierda!";
			link.l1.go = "check_parol_fight";
		}
		break;

	case "check_parol_fight":
		DialogExit();
		LAi_SetGuardianType(NPChar);
		LAi_group_MoveCharacter(NPChar, "LSC_NARVAL");
		LAi_group_Attack(NPChar, Pchar);
		break;

	case "Narval_parol_repeat":
		if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
		{
			dialog.text = LinkRandPhrase("¡Muchachos, cuidado, ahí está el psicópata! ¡A las armas!", "¡El enemigo está aquí! ¡A las armas!", "¡Ah, eres un bastardo! ¡Ahora te daremos una lección!");
			link.l1 = "¡Maldición!";
			link.l1.go = "check_parol_fight";
			break;
		}
		dialog.text = "¡Sigue adelante! ¡No te quedes aquí!";
		link.l1 = "...";
		link.l1.go = "exit";
		NextDiag.TempNode = "Narval_parol_repeat";
		break;

	// у резиденции
	case "Narval_residence":
		if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
		{
			dialog.text = LinkRandPhrase("¡Muchachos, cuidado, ahí viene el loco! ¡A las armas!", "¡El enemigo está aquí! ¡A las armas!", "¡Ah, eres un bastardo! ¡Ahora te daremos una lección!");
			link.l1 = "¡Maldición!";
			link.l1.go = "check_parol_fight";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend"))
		{
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // диалог от времени суток. лесник
			{
				dialog.text = TimeGreeting() + ", " + pchar.name + "¡La puerta está abierta, por si quieres ver al jefe!";
				link.l1 = "Está bien...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Narval_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else
			{
				dialog.text = TimeGreeting() + ", " + pchar.name + "¡ En caso de que quieras ver al jefe, ya está dormido. Vuelve por la mañana.";
				link.l1 = "Bien...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Narval_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
			}
			break;
		}
		if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && CheckAttribute(pchar, "questTemp.LSC.rvd_friend"))
		{
			dialog.text = "¡Los amigos de los negros no tienen nada que hacer aquí! ¡Una orden directa del jefe!";
			if (CheckAttribute(pchar, "questTemp.LSC.Donald_enter"))
			{
				link.l1 = "Tendrá que verme. Tenéis problemas de verdad, muchachos. Estoy aquí por órdenes oficiales del almirante. ¡Así que abran la maldita puerta!";
				link.l1.go = "negotiations";
			}
			else
			{
				link.l1 = "No puedo decir que quiera verlo tampoco...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			break;
		}
		if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
		{
			dialog.text = "¿Quieres ver al jefe? Hm, bueno, sigue adelante entonces.";
			link.l1 = "Gracias por permitir...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
		}
		else
		{
			dialog.text = "¿Quieres ver al jefe? No más visitas hoy. Vuelve por la mañana.";
			link.l1 = "Está bien...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
		}
		break;

	case "Narval_soldier":
		if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
		{
			dialog.text = LinkRandPhrase("¡Muchachos, cuidado, ahí viene el loco! ¡A las armas!", "¡El enemigo está aquí! ¡A las armas!", "¡Ah, eres un bastardo! ¡Ahora te daremos una lección!");
			link.l1 = "¡Maldición!";
			link.l1.go = "check_parol_fight";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend"))
		{
			dialog.text = TimeGreeting() + ", " + pchar.name + ". ¿Cómo estás?";
			link.l1 = "Estoy bien, gracias...";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "Escucha, amigo, no estoy de humor para hablar. Sigue tu camino...";
			link.l1 = "Bien.";
			link.l1.go = "exit";
		}
		NextDiag.TempNode = "Narval_soldier";
		break;

	case "negotiations":
		dialog.text = "Bueno, bueno... Cálmate. Deberías haber dicho que venías del almirante desde el principio. Verás, hay diferentes personas deambulando...";
		link.l1 = "¿Finalmente vas a dejarme pasar? ¡Gracias!";
		link.l1.go = "negotiations_1";
		break;

	case "negotiations_1":
		DialogExit();
		NextDiag.CurrentNode = "negotiations_2";
		LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false); // открыть вход к Дональду Гринспи
		break;

	case "negotiations_2":
		dialog.text = "Muévete, se te permite...";
		link.l1 = "¿Oh, de verdad? No puedo creerlo.";
		link.l1.go = "exit";
		NextDiag.TempNode = "negotiations_2";
		break;

		//------------------------------------- фразы гардов ривадос --------------------------------------------
		// пост ривадос на проход на Фурию и Веласко
	case "Rivados_warning":
		if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
		{
			dialog.text = LinkRandPhrase("¡Muchachos, cuidado, ahí viene el psicópata agresivo! ¡A las armas!", "¡El enemigo está aquí! ¡A las armas!", "¡Ah, eres un bastardo enfermo! ¡Ahora te daremos una lección!");
			link.l1 = "¡Maldita sea!";
			link.l1.go = "Rcheck_parol_fight";
			break;
		}
		location = &Locations[FindLocation(pchar.location)];
		if (!CheckAttribute(location, "rvd_parolinfo"))
		{
			if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend"))
			{
				dialog.text = "¡Alto! Los territorios detrás de mí pertenecen al clan Rivados, no se permite pasar a extraños como tú sin una invitación. ¿Sabes la contraseña?";
				link.l1 = "Sí.";
				link.l1.go = "Rivados_warning_yes";
				link.l2 = "No.";
				link.l2.go = "Rivados_warning_no";
			}
			else // если друг ривадос
			{
				dialog.text = "Ah, " + GetFullName(pchar) + "¡Me alegra verte! Nos informaron que puedes caminar libremente aquí. ¡Bienvenido!";
				link.l1 = "¡Gracias, amigo!";
				link.l1.go = "exit";
			}
			location.rvd_parolinfo = "true";
		}
		else
		{
			if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend"))
			{
				dialog.text = "Espero que no hayas olvidado la contraseña...";
				link.l1 = "No te preocupes...";
				link.l1.go = "exit";
			}
			else // если друг ривадос
			{
				dialog.text = TimeGreeting() + ", " + pchar.name + ". ¿Cómo te va?";
				link.l1 = "Estoy bien, gracias...";
				link.l1.go = "exit";
			}
		}
		NextDiag.TempNode = "Rivados_warning_repeat";
		DeleteAttribute(npchar, "protector.CheckAlways");
		break;

	case "Rivados_warning_yes":
		dialog.text = "Entonces puedes irte. Este muchacho te pedirá una contraseña. Mejor que te vayas ahora si tienes alguna idea de engañarnos. Te he advertido.";
		link.l1 = "Bien, amigo. Lo tengo.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Rivados_warning_repeat";
		break;

	case "Rivados_warning_no":
		dialog.text = "¡Jo-jo! O eres muy valiente o muy tonto si vas a visitarnos sin una contraseña. ¿O acaso estás bromeando? Adelante entonces. Estoy aquí para advertir, no para detener. ¡Cuidado si realmente no sabes la contraseña!";
		link.l1 = "Está bien, amigo. Lo entiendo.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Rivados_warning_repeat";
		break;

	case "Rivados_warning_repeat":
		if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend"))
		{
			dialog.text = "Bueno, ¿qué quieres? ¡Sigue adelante o piérdete!";
			link.l1 = "...";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "Lo siento, " + pchar.name + ", pero estoy de servicio. Eddie no quiere que hable demasiado.";
			link.l1 = "...";
			link.l1.go = "exit";
		}
		NextDiag.TempNode = "Rivados_warning_repeat";
		DeleteAttribute(npchar, "protector.CheckAlways");
		break;

	case "Rivados_parol":
		if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
		{
			dialog.text = LinkRandPhrase("¡Muchachos, cuidado, ahí viene el psicópata agresivo! ¡A las armas!", "¡El enemigo está aquí! ¡A las armas!", "¡Ah, eres un bastardo enfermo! ¡Ahora te enseñaremos una lección!");
			link.l1 = "¡Maldición!";
			link.l1.go = "Rcheck_parol_fight";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend"))
		{
			dialog.text = "Lo siento, " + pchar.name + ", pero estoy de servicio. Eddie no quiere que hable demasiado.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol";
			DeleteAttribute(npchar, "protector.CheckAlways");
			break;
		}
		dialog.text = "¡Detente justo donde estás! ¡No eres de los Rivados!";
		link.l1 = "Quiero pasar.";
		link.l1.go = "Rcheck_parol";
		break;

	case "Rcheck_parol":
		dialog.text = "Entonces di una contraseña y hazlo alto y claro.";
		link.l1.edit = 3;
		link.l1 = "";
		link.l1.go = "Rcheck_parol_1";
		break;

	case "Rcheck_parol_1":
		sTemp = GetStrSmallRegister(dialogEditStrings[3]);
		if (sTemp == sRvdParol && CheckAttribute(pchar, "questTemp.LSC.RParol_bye"))
		{
			dialog.text = "Correcto. Sigue adelante.";
			link.l1 = "Gracias, amigo...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_RIVADOS");
			pchar.questTemp.LSC.parol_rvd = "true";
		}
		else
		{
			dialog.text = "¡Ja, ja! ¡Tenemos un invitado aquí! ¡Mostrémosle quiénes somos!";
			link.l1 = "¡Mierda!";
			link.l1.go = "Rcheck_parol_fight";
		}
		break;

	case "Rcheck_parol_fight":
		DialogExit();
		LAi_SetGuardianType(NPChar);
		LAi_group_MoveCharacter(NPChar, "LSC_RIVADOS");
		LAi_group_Attack(NPChar, Pchar);
		break;

	case "Rivados_parol_repeat":
		if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
		{
			dialog.text = LinkRandPhrase("¡Muchachos, cuidado, ahí viene el psicópata agresivo! ¡A las armas!", "¡El enemigo está aquí! ¡A las armas!", "¡Ah, eres un bastardo enfermo! ¡Ahora te daremos una lección, una lección!");
			link.l1 = "¡Mierda!";
			link.l1.go = "Rcheck_parol_fight";
			break;
		}
		dialog.text = "¡No te quedes aquí, sigue adelante!";
		link.l1 = "...";
		link.l1.go = "exit";
		NextDiag.TempNode = "Rivados_parol_repeat";
		break;

	// у резиденции
	case "Rivados_residence":
		if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
		{
			dialog.text = LinkRandPhrase("¡Muchachos, cuidado, ahí está el psicópata agresivo! ¡A las armas!", "¡El enemigo está aquí! ¡A las armas!", "¡Ah, eres un bastardo enfermo! ¡Ahora te enseñaremos!");
			link.l1 = "¡Mierda!";
			link.l1.go = "Rcheck_parol_fight";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend"))
		{
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
			{
				dialog.text = TimeGreeting() + ", " + pchar.name + "¡La puerta está abierta, por si quieres ver a Eddie y Chimiset. Se alegrarán de verte.";
				link.l1 = "Bien...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else // лесник - режим пропуска
			{
				dialog.text = TimeGreeting() + ", " + pchar.name + "¡Por si quieres ver a Eddie y Chimiset, ya están descansando. Vuelve por la mañana, estarán encantados de verte.";
				link.l1 = "Bien...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
			}
			break;
		}
		if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && !CheckAttribute(pchar, "questTemp.LSC.rvd_friend"))
		{
			dialog.text = "No hay nada que los amigos de los Narvales puedan hacer dentro de la cabina de Eddie. ¡Esta es su orden directa! ¡Piérdete!";
			link.l1 = "No quería verlo tampoco...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			break;
		}
		if (GetCharacterIndex("Chimiset") == -1) // Чимисет убит
		{
			dialog.text = "No tienes nada que hacer dentro de la cabina de Eddie. ¡Esta es su orden directa! ¡Piérdete!";
			link.l1 = "No quería verlo tampoco...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			break;
		}
		if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
		{
			dialog.text = "¿Quieres ver a Eddie? Bien, sigue adelante, supongo que te dedicará un minuto.";
			link.l1 = "Gracias por permitir...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
		}
		else // лесник режим пропуска.
		{
			dialog.text = "¿Quieres ver a Eddie? No más visitas hoy, vuelve por la mañana y él te dedicará un minuto.";
			link.l1 = "Está bien...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
		}
		break;

	case "Rivados_soldier":
		if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
		{
			dialog.text = LinkRandPhrase("¡Muchachos, cuidado, ahí viene el psicópata agresivo! ¡A las armas!", "¡El enemigo está aquí! ¡A las armas!", "¡Ah, eres un bastardo enfermo! ¡Ahora te daremos una lección!");
			link.l1 = "¡Mierda!";
			link.l1.go = "Rcheck_parol_fight";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend"))
		{
			dialog.text = TimeGreeting() + ", " + pchar.name + ". ¿Cómo te va?";
			link.l1 = "Estoy bien, gracias...";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "Escucha, amigo, no estoy de humor para hablar. Sigue tu camino...";
			link.l1 = "Bien.";
			link.l1.go = "exit";
		}
		NextDiag.TempNode = "Rivados_soldier";
		break;
		//------------------------------------- фразы гардов пиратов --------------------------------------------
		// у склада
	case "Shark_storage":
		if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
		{
			dialog.text = LinkRandPhrase("¡Muchachos, cuidado, ahí viene el psicópata armado! ¡A las armas!", "¡El enemigo está aquí! ¡A las armas!", "¡Ah, eres un bastardo! ¡Ahora te patearemos el trasero!");
			link.l1 = "¡Maldita sea!";
			link.l1.go = "shark_guard_fight";
			break;
		}
		dialog.text = "¡Alto! ¡Esta es un área restringida!";
		link.l1 = "Está bien, como dices...";
		link.l1.go = "exit";
		NextDiag.TempNode = "Shark_storage";
		break;

	// у резиденции
	case "Shark_residence":
		if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
		{
			dialog.text = LinkRandPhrase("¡Muchachos, cuidado, ahí viene el psicópata armado! ¡A las armas!", "¡El enemigo está aquí! ¡A las armas!", "¡Ah, eres un bastardo! ¡Ahora te patearemos el trasero!");
			link.l1 = "¡Maldita sea!";
			link.l1.go = "shark_guard_fight";
			break;
		}
		if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00)
		{
			if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
			{
				dialog.text = "¡Alto! No eres uno de los nuestros... ¿Te está esperando Shark o solo estás deambulando sin propósito?";
				link.l1 = "¿Shark? ¿Steve Dodson?";
				link.l1.go = "first_talk_day";
			}
			else
			{
				dialog.text = "El almirante te aceptará. Sigue adelante.";
				link.l1 = "¡Gracias!";
				link.l1.go = "exit";
			}
		}
		else
		{
			if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
			{
				dialog.text = "¿Adónde te apresuras? ¡Es de noche, ¿no lo ves?! ¿O realmente piensas que el almirante se despertará para saludarte personalmente? Ven por la mañana.";
				link.l1 = "Como usted diga. ¿Y dónde puedo descansar?";
				link.l1.go = "first_talk_night";
			}
			else
			{
				dialog.text = "Es tarde, el almirante no está recibiendo ahora. Vuelve mañana.";
				link.l1 = "Bien...";
				link.l1.go = "exit";
			}
		}
		NextDiag.TempNode = "Shark_residence";
		break;

	case "Shark_soldier":
		if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
		{
			dialog.text = LinkRandPhrase("¡Muchachos, cuidado, hay un psicópata armado! ¡A las armas!", "¡El enemigo está aquí! ¡A las armas!", "¡Ah, eres un bastardo! ¡Ahora te patearemos el trasero!");
			link.l1 = "¡Maldita sea!";
			link.l1.go = "shark_guard_fight";
			break;
		}
		dialog.text = "El almirante no estará contento si me ve hablando. Sigue adelante.";
		link.l1 = "Bien...";
		link.l1.go = "exit";
		NextDiag.TempNode = "Shark_soldier";
		break;

	case "first_talk_night":
		dialog.text = NPCStringReactionRepeat("¿Estás borracho? Da la vuelta y cruza el puente, pasa dos barcos y luego encontrarás otro puente que te llevará a la taberna. Duerme allí.", "¿Estás tratando de enfurecerme? ¡Ya te he dicho qué hacer. ¡Lárgate!", "Ve y duerme, cara de borracho...", "¡Vete!!", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Gracias, señor. Podrías ser más cortés, en realidad...", "Lo siento, olvidé...", "¡No estoy borracho!", "¿Qué?!", npchar, Dialog.CurrentNode);
		link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;

	case "first_talk_day":
		dialog.text = "No pongas ojos redondos, muchacho. Todo el mundo sabe que Steve Shark es nuestro almirante. ¿Tienes algún asunto con él?";
		link.l1 = "¡Sí, maldita sea! Tengo asuntos con él y es urgente.";
		link.l1.go = "first_talk_day_1";
		break;

	case "first_talk_day_1":
		dialog.text = "¿Y qué tipo de negocio?";
		link.l1 = "Lo contaré solo a Shark en privado. Estoy trabajando para Jan Svenson, ¿lo conoces?";
		link.l1.go = "first_talk_day_2";
		break;

	case "first_talk_day_2":
		dialog.text = "¿Demonio del Bosque? ¡Ja! La mitad del continente conoce a ese hombre. Escucha, muchacho, no seas terco. O te explicas o te pierdes antes de que me enoje. Shark dijo que lo librara de gente inútil y solo estoy haciendo lo que ordenó.";
		link.l1 = "Bien. Aquí, echa un vistazo a esta carta, está escrita por Forest Devil para Shark.";
		link.l1.go = "first_talk_day_3";
		break;

	case "first_talk_day_3":
		PlaySound("interface\important_item.wav");
		dialog.text = "...Está bien. Supongo que a Steve le parecerá interesante. Sigue adelante.";
		link.l1 = "¿De verdad? Devuelve la carta si no te resulta muy difícil, por favor.";
		if (pchar.questTemp.LSC == "mary")
			link.l1.go = "first_talk_day_5";
		else
			link.l1.go = "first_talk_day_4";
		break;

	case "first_talk_day_4":
		PlaySound("interface\important_item.wav");
		npchar.dialog.currentnode = "First time";
		DialogExit();
		LSC_OpenSanAvgustinDoors();										  // открываем Сан-Августин
		LocatorReloadEnterDisable("LostShipsCity_town", "reload2", true); // закрываем кладовку со стороны моря
		pchar.quest.LSC_entry_pantry.over = "yes";						  // снять прерывание на арест
		pchar.quest.LSC_findMary.over = "yes";							  // снять прерывание на Мэри
		pchar.questTemp.LSC = "entrance";								  // меняем флаг
		sld = characterFromId("Dodson");
		sld.dialog.currentnode = "entrance";
		// закрываем вход к Мэри
		LocatorReloadEnterDisable("LostShipsCity_town", "reload60", true);
		LocatorReloadEnterDisable("LostShipsCity_town", "reload61", true);
		break;

	case "first_talk_day_5":
		PlaySound("interface\important_item.wav");
		npchar.dialog.currentnode = "First time";
		DialogExit();
		LSC_OpenSanAvgustinDoors(); // открываем Сан-Августин
		sld = characterFromId("Dodson");
		sld.dialog.currentnode = "entrance";
		break;

	case "shark_guard_fight":
		DialogExit();
		LAi_SetGuardianType(NPChar);
		LAi_group_MoveCharacter(NPChar, "LSC_SHARK");
		LAi_group_Attack(NPChar, Pchar);
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}

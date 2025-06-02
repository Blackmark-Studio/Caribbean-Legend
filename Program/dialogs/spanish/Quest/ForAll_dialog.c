void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, forName;
	string sTemp, sGem, sTitle;
	int iTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "No tenemos nada de qué hablar.";
		link.l1 = "Está bien...";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "CitizenNotBlade":
		if (LoadedLocation.type == "town")
		{
			dialog.text = NPCharSexPhrase(NPChar, "Escucha, soy ciudadano de este pueblo y te pediría que bajes tu espada.", "Escucha, soy ciudadano de este pueblo y te pediría que bajes tu espada.");
			link.l1 = LinkRandPhrase("Bien.", "Claro.", "Bien...");
		}
		else
		{
			dialog.text = NPCharSexPhrase(NPChar, "Ten cuidado, " + GetSexPhrase("compadre", "chica") + ", corriendo con un arma. Puedo ponerme nervioso...", "No me gusta cuando hay " + GetSexPhrase("hombres", "gente") + " caminando delante de mí con su arma lista. Me asusta...");
			link.l1 = RandPhraseSimple("Lo tengo.", "Lo tengo.");
		}

		link.l1.go = "exit";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	//--------------------------- квест официантки --------------------------------
	// грабитель
	case "WaitressBerglar":
		dialog.text = "Vamos, amigo, muéstrame tus bolsillos.";
		link.l1 = "¿¡Qué?!";
		link.l1.go = "WaitressBerglar_1";
		break;
	case "WaitressBerglar_1":
		dialog.text = "Me has oído. Rápido, menos palabras. No me gusta hablar...";
		link.l1 = "¡Maldita sea! Y  ¿hace " + pchar.questTemp.different.FackWaitress.Name + " trabajar contigo?";
		link.l1.go = "WaitressBerglar_2";
		break;
	case "WaitressBerglar_2":
		dialog.text = "Lo hace, lo hace... ¡Dame tu dinero o te destriparé!";
		link.l1 = "¡No! ¡Te destriparé!";
		link.l1.go = "WaitressBerglar_fight";
		link.l2 = "Toma mis monedas, ¡bastardo! Pero no te librarás de esto...";
		link.l2.go = "WaitressBerglar_take";
		break;
	case "WaitressBerglar_take":
		dialog.text = "Claro, no se puede discutir con eso. ¡Adiós, camarada! Y recuerda, no eres tan apuesto como para hacer que las camareras se mojen. ¡Sé más listo la próxima vez!";
		link.l1 = "... Vete ya.";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("WaitressFack_outRoom");
		break;
	case "WaitressBerglar_fight":
		dialog.text = "Como usted diga...";
		link.l1 = "Eso hago...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("WaitressFack_fight");
		break;
	// официантка
	case "Waitress":
		dialog.text = "¡Aquí estoy! ¿Me deseas, guapo?";
		link.l1 = "Maldición, eso se intensificó rápidamente...";
		link.l1.go = "Waitress_1";
		break;
	case "Waitress_1":
		dialog.text = "¡No perdamos nuestro tiempo!";
		link.l1 = "¡Je, no podría estar más de acuerdo!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("WaitressFack_fack");
		break;

	//--------------------------- догнать кэпа, потерявшего судовой журнал --------------------------------
	// встретил в городе
	case "PortmansCap":
		dialog.text = "Buen día. Mi nombre es " + GetFullName(npchar) + ". Soy un capitán de " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Acc")) + " '" + npchar.Ship.name + " '.";
		link.l1 = "¡Espléndido! Al fin te he encontrado.";
		link.l1.go = "PortmansCap_1";
		break;
	case "PortmansCap_1":
		dialog.text = "¡¿Me encontraste?!";
		link.l1 = "Sí. Bueno, he traído tu diario de a bordo, que olvidaste en la oficina del puerto de " + XI_ConvertString("Colony" + npchar.quest.firstCity + "Gen") + ".";
		link.l1.go = "PortmansCap_2";
		break;
	case "PortmansCap_2":
		dialog.text = "¡Maldita sea! Ahora veo dónde lo había perdido. Esta pérdida casi ha provocado un motín en mi barco...";
		link.l1 = "Así que bien está lo que bien acaba. Toma tu libro de bitácora y hablemos de mi dinero.";
		link.l1.go = "PortmansCap_3";
		break;
	case "PortmansCap_3":
		if (sti(npchar.quest.stepsQty) == 1)
		{
			dialog.text = "Gran momento, aún no he comenzado uno nuevo, así que te pagaré tanto como pueda. " + FindRussianMoneyString(sti(npchar.quest.money)) + " y acepta algunas piezas de mis joyas privadas.";
			link.l1 = "Lindo. Tómalo.";
			link.l1.go = "PortmansCap_4";
		}
		else
		{
			if (sti(npchar.quest.stepsQty) < 5)
			{
				npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); // уменьшаем вознаграждение
				dialog.text = "Hum, sabes, ya he comenzado el nuevo cuaderno de bitácora. No obstante, el viejo todavía tiene valor para mí. Así que te pagaré " + FindRussianMoneyString(sti(npchar.quest.money)) + " y acepta algunas piezas de mis joyas privadas.";
				link.l1 = "Trato hecho. Toma tu diario de a bordo.";
				link.l1.go = "PortmansCap_4";
			}
			else
			{
				dialog.text = "Ya he comenzado el nuevo cuaderno de bitácora. Y he transferido todas las notas del anterior. Ya no lo necesito, así que no hay dinero para ti.";
				link.l1 = "Genial. Así que toda esta persecución fue para nada.";
				link.l1.go = "PortmansCap_5";
			}
		}
		break;
	case "PortmansCap_4":
		dialog.text = "Gracias. Adiós, " + GetSexPhrase("amigo", "chica") + ".";
		link.l1 = "Lo mismo para ti...";
		link.l1.go = "exit";
		sTemp = "Timer_" + npchar.id;
		pchar.quest.(sTemp).over = "yes"; // снимаем таймер на выход в море
		npchar.LifeDay = 2;				  // через пару дней снимаем кэпа
		SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		group_DeleteGroup("PorpmansShip_" + npchar.index); // чистим группу, на всякий случай
		sld = characterFromId(npchar.quest.firstCity + "_PortMan");
		sTitle = sld.id + "PortmansBook_Delivery";
		AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Voc")); // belamour gen
		AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
		CloseQuestHeader(sTitle);
		sGem = pchar.questTemp.PortmansJornal.gem;
		TakeNItems(pchar, sGem, 12 + hrand(10));
		DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
		DeleteAttribute(sld, "quest.PortmansJornal");
		sld.quest = ""; // освобождаем личный флаг квеста для портмана
		AddCharacterExpToSkill(pchar, "Repair", makeint(400 / sti(npchar.quest.stepsQty)));
		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
		ChangeCharacterComplexReputation(pchar, "nobility", 2);
		TakeItemFromCharacter(pchar, "PortmansBook");
		NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
	case "PortmansCap_5":
		dialog.text = "Ja, trabaja en tu sincronización la próxima vez.";
		link.l1 = "Cierto es.";
		link.l1.go = "exit";
		sTemp = "Timer_" + npchar.id;
		pchar.quest.(sTemp).over = "yes"; // снимаем таймер на выход в море
		npchar.LifeDay = 2;				  // через пару дней снимаем кэпа
		SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		group_DeleteGroup("PorpmansShip_" + npchar.index); // чистим группу, на всякий случай
		sld = characterFromId(npchar.quest.firstCity + "_PortMan");
		sTitle = sld.id + "PortmansBook_Delivery";
		AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Voc")); // belamour gen
		AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
		CloseQuestHeader(sTitle);
		DeleteAttribute(sld, "quest.PortmansJornal");
		sld.quest = ""; // освобождаем личный флаг квеста для портмана
		AddCharacterExpToSkill(pchar, "Repair", makeint(200 / sti(npchar.quest.stepsQty)));
		TakeItemFromCharacter(pchar, "PortmansBook");
		NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
	// догнал в море
	case "PortmansCap_inDeck":
		if (isBadReputation(pchar, 20))
		{
			dialog.text = "Te saludo en la cubierta de mi barco. Para ser honesto, me asustaste de muerte, pensé que el Cazador del Corcel Tuerto me estaba cazando...";
			link.l1 = "No, capitán, estoy de buen humor hoy. Estoy aquí para ayudarte.";
		}
		else
		{
			dialog.text = "¡Te saludo en la cubierta de mi barco!";
			link.l1 = "¡Ahoy, cap! Te estaba buscando.";
		}
		link.l1.go = "PortmansCap_inDeck_1";
		break;
	case "PortmansCap_inDeck_1":
		dialog.text = "¿Por qué?";
		link.l1 = "Has olvidado tu cuaderno de bitácora en la casa del capitán del puerto de " + XI_ConvertString("Colony" + npchar.quest.firstCity + "Gen") + ".";
		link.l1.go = "PortmansCap_inDeck_2";
		break;
	case "PortmansCap_inDeck_2":
		if (sti(npchar.quest.stepsQty) == 1)
		{
			dialog.text = "¡Maldita sea, entonces ese era el lugar! Esta pérdida ya me ha causado un montón de problemas.";
			link.l1 = "¿Qué tal una recompensa?";
			link.l1.go = "PortmansCap_inDeck_3";
		}
		else
		{
			if (sti(npchar.quest.stepsQty) < 5)
			{
				npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); // уменьшаем вознаграждение
				dialog.text = "¡Maldita sea, ahora veo dónde lo había perdido! Gracias, pero me buscaste demasiado tiempo. Ya he empezado el nuevo cuaderno de bitácora. No obstante, las notas antiguas todavía deben ser transferidas al nuevo...";
				link.l1 = "¿Y cuánto?";
				link.l1.go = "PortmansCap_inDeck_3";
			}
			else
			{
				dialog.text = "Ya he comenzado el nuevo cuaderno de bitácora. Y he transferido todas las notas del antiguo. Ya no lo necesito.";
				link.l1 = "¿Así que no necesitas un viejo diario? ¿De verdad?";
				link.l1.go = "PortmansCap_inDeck_5";
			}
		}
		break;
	case "PortmansCap_inDeck_3":
		dialog.text = "Puedo pagarte " + FindRussianMoneyString(sti(npchar.quest.money)) + " y algunas de mis joyas. Eso es todo lo que puedo permitirme.";
		link.l1 = "Está bien entonces. Toma tu diario.";
		link.l1.go = "PortmansCap_inDeck_4";
		break;
	case "PortmansCap_inDeck_4":
		dialog.text = "Gracias de nuevo. Adiós, camarada.";
		link.l1 = "Manténlo así.";
		link.l1.go = "exit";
		npchar.LifeDay = 30; // через десять дней снимаем кэпа
		SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		npchar.quest = "over"; // флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
		sld = characterFromId(npchar.quest.firstCity + "_PortMan");
		sTitle = sld.id + "PortmansBook_Delivery";
		AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
		AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
		CloseQuestHeader(sTitle);
		sGem = pchar.questTemp.PortmansJornal.gem;
		TakeNItems(pchar, sGem, 12 + hrand(10));
		DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
		DeleteAttribute(sld, "quest.PortmansJornal");
		sld.quest = ""; // освобождаем личный флаг квеста для портмана
		AddCharacterExpToSkill(pchar, "Sailing", makeint(200 / sti(npchar.quest.stepsQty)));
		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
		ChangeCharacterComplexReputation(pchar, "nobility", 5);
		TakeItemFromCharacter(pchar, "PortmansBook");
		npchar.DeckDialogNode = "PortmansCap_inDeck_over";
		NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
	case "PortmansCap_inDeck_5":
		dialog.text = "Eso es seguro. Si estás persiguiendo a alguien, entonces tienes que ser más rápido.";
		link.l1 = "No pierdas tus cuadernos de bitácora para empezar. Bien.";
		link.l1.go = "exit";
		npchar.LifeDay = 30; // через десять дней снимаем кэпа
		SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		npchar.quest = "over"; // флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
		sld = characterFromId(npchar.quest.firstCity + "_PortMan");
		sTitle = sld.id + "PortmansBook_Delivery";
		AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
		AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
		CloseQuestHeader(sTitle);
		DeleteAttribute(sld, "quest.PortmansJornal");
		sld.quest = ""; // освобождаем личный флаг квеста для портмана
		AddCharacterExpToSkill(pchar, "Sailing", makeint(100 / sti(npchar.quest.stepsQty)));
		TakeItemFromCharacter(pchar, "PortmansBook");
		npchar.DeckDialogNode = "PortmansCap_inDeck_over";
		NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
	case "PortmansCap_inDeck_over":
		dialog.text = "Pensé que lo habíamos arreglado todo.";
		link.l1 = "Sí, eso es cierto.";
		link.l1.go = "exit";
		NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
	//--------------------------- розыск украденного корабля --------------------------------
	case "SeekCap_inDeck":
		dialog.text = "Saludos. ¿Qué quieres?";
		link.l1 = "No es nada, solo quería escuchar algunas noticias. ¿Tienes algo a la venta?";
		link.l1.go = "SeekCap_inDeck_1";
		break;
	case "SeekCap_inDeck_1":
		dialog.text = "No tengo nada que venderte y no tengo noticias. Por cierto, tu presencia aquí no es deseada. ¿Está claro?";
		link.l1 = "Eres... Adiós entonces, camarada.";
		link.l1.go = "exit";
		NextDiag.TempNode = "SeekCap_inDeck_over";
		sld = characterFromId(npchar.quest.cribCity + "_PortMan");
		sTitle = sld.id + "Portmans_SeekShip";
		AddQuestRecordEx(sTitle, "Portmans_SeekShip", "4");
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen"));
		AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName)));
		break;
	case "SeekCap_inDeck_over":
		dialog.text = "¡Te he dicho que no tienes nada que hacer aquí!";
		link.l1 = "Ya veo...";
		link.l1.go = "exit";
		NextDiag.TempNode = "SeekCap_inDeck_over";
		break;
	// абордаж
	case "SeekCap":
		dialog.text = "¿Por qué me has atacado?!";
		link.l1 = "Tengo que devolver el barco a su dueño..";
		link.l1.go = "SeekCap_1";
		break;
	case "SeekCap_1":
		dialog.text = "¿A qué tipo de propietario? ¡Yo soy el propietario!";
		link.l1 = "No, no lo eres. No sé quién es el dueño de este barco. Pero fue robado y tengo que devolverlo.";
		link.l1.go = "SeekCap_2";
		break;
	case "SeekCap_2":
		dialog.text = "¡Maldición! Pero aún no ha terminado para mí. Al menos intentaré matarte...";
		link.l1 = "Intentar es todo lo que puedes hacer.";
		link.l1.go = "SeekCap_3";
		break;
	case "SeekCap_3":
		LAi_SetCurHPMax(npchar);
		QuestAboardCabinDialogExitWithBattle("");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//-------------------------------------------поисковый генератор горожан--------------------------------------
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////

	case "SCQ_exit":
		DialogExit();
		npchar.lifeDay = 0;
		LAi_CharacterDisableDialog(npchar);
		break;

	case "SCQ_exit_clear":
		sld = characterFromId(npchar.quest.SeekCap.capId); // капитан
		sld.lifeDay = 0;
		Map_ReleaseQuestEncounter(sld.id);
		string sGroup = "SeekCapShip_" + sld.index;
		group_DeleteGroup(sGroup);
		sTemp = "SCQ_" + sld.index;
		pchar.quest.(sTemp).over = "yes"; // снимаем прерывание смерть кэпа
		sTemp = "SCQ_" + npchar.index;
		pchar.quest.(sTemp).over = "yes"; // снимаем прерывание смерть квестодателя
		npchar.lifeDay = 0;
		LAi_CharacterDisableDialog(npchar);
		DialogExit();
		break;

		//--------------------------------------------поисковые квесты дворян---------------------------------------------

	case "SCQ_Nobleman":
		dialog.text = "Saludos, " + GetAddress_Form(NPChar) + ". Veo que eres el capitán de tu propio barco. Mi nombre es " + GetFullName(npchar) + " y quiero ofrecerte un trato.";
		link.l1 = RandPhraseSimple("Lo siento mucho, pero tengo que irme.", "Lo siento mucho, pero no tengo tiempo para hablar contigo.");
		link.l1.go = "SCQ_exit";
		link.l2 = "Soy todo oídos.";
		link.l2.go = "SCQ_Nobleman_1";
		break;

	case "SCQ_Nobleman_1":
		switch (sti(npchar.quest.SeekCap.numQuest))
		{
		case 0: // вариант А
			if (sti(pchar.reputation.nobility) < 35)
			{
				dialog.text = "Escucha entonces. " + SelectNB_battleText() + "\nNo poseo ni tiempo ni oportunidad para encontrarlo. Porque... nunca aparece aquí. Supongo que ahora lo ves, ¿ves lo que voy a proponerte?";
				link.l1 = LinkRandPhrase("Supongo que tengo que localizar a alguien y traértelo.", "¿Quizás, encontrar al bastardo y traerlo ante usted?", "¿Quieres que encuentre a este hombre y lo traiga aquí?");
				link.l1.go = "SCQ_NM_battle";
			}
			else // вариант В
			{
				SelectNB_prisonerText(npchar);
				dialog.text = "Entonces escucha." + SelectNB_battleText() + "\nNo poseo ni tiempo ni oportunidad de encontrarlo. Porque... él nunca aparece aquí. Supongo que ahora lo ves, ¿ves lo que te voy a proponer?";
				link.l1 = LinkRandPhrase("Supongo que quieres que rastree a alguien y te lo traiga.", "¿Quizás, encontrar al bastardo y traértelo?", "¿Quieres que encuentre a este hombre y lo traiga aquí?");
				link.l1.go = "SCQ_NM_prisoner"
			}
			break;

		case 1: // вариант С
			SelectNB_peaceText(npchar);
			dialog.text = "Escucha entonces. En realidad, " + npchar.quest.text + " está sirviendo en la marina como capitán. ¡Ni siquiera sabe que también estoy aquí!\nMe gustaría reunirme con él, pero no tengo ni tiempo ni oportunidad para encontrarlo...";
			link.l1 = "¿Supongo que quieres que encuentre a este capitán y le hable de ti?";
			link.l1.go = "SCQ_NM_peace";
			break;
		}
		break;

	case "SCQ_NM_battle": // вариант А
		dialog.text = "No es del todo así. Encuéntralo, pero no es necesario traerlo aquí. Mátalo y eso será suficiente. Húndelo con su asqueroso barco, dispárale, apuñálalo con tu espada; realmente no me importa eso, solo haz que este bastardo deje de envenenar este mundo con su presencia. La recompensa será generosa.";
		link.l1 = "¡Ja! Bastante fácil. Dime su nombre y el nombre de su barco.";
		link.l1.go = "SCQ_NM_battle_1";
		break;

	case "SCQ_NM_battle_1":
		npchar.quest.SeekCap = "NM_battle";			   // личный флаг на квест
		SetSeekCapCitizenParam(npchar, rand(NON_PIRATES)); // любая нация кроме пиратов
		dialog.text = "" + npchar.quest.SeekCap.capName + " de la " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")) + " llamado " + npchar.quest.SeekCap.shipName + ". Él es un visitante frecuente en el puerto de " + XI_ConvertString("Colony" + npchar.quest.Qcity) + ". Te pagaré " + FindRussianMoneyString(sti(npchar.quest.money)) + " en doblones de oro.";
		link.l1 = "Eso es todo lo que necesito saber. Estaré atento en el mar. Y cuando encuentre a tu amigo, lo haré... 'bajando la voz' ...no muy vivo.";
		link.l1.go = "SCQ_NM_battle_2";
		link.l2 = "No es suficiente para ese tipo de trabajo.";
		link.l2.go = "SCQ_exit_clear";
		break;

	case "SCQ_NM_battle_2":
		dialog.text = "Me alegra que hayamos llegado a un acuerdo. Estaré esperando tu regreso.";
		link.l1 = "¿Dónde podré encontrarte? Aclarémoslo ahora, no quiero perder tiempo buscándote.";
		link.l1.go = "SCQ_NM_battle_3";
		break;

	case "SCQ_NM_battle_3":
		dialog.text = "Cada mañana asisto a un servicio en la iglesia. Puedes encontrarme allí todos los días de 8 a 9 a.m.";
		link.l1 = "¡Trato hecho! Espera el resultado pronto.";
		link.l1.go = "exit";
		DeleteAttribute(npchar, "LifeDay");
		DeleteAttribute(npchar, "talker");
		DeleteAttribute(npchar, "CityType"); // удалить признак фантома, иначе - пустые города
		LAi_SetLoginTime(npchar, 8.0, 10.0);
		pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
		npchar.location = npchar.city + "_church";
		npchar.location.locator = "goto2";
		pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
		pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
		pchar.quest.SeekShip_Stay.Idx = npchar.index;
		NextDiag.TempNode = "SCQ_NM_result";
		sTitle = npchar.city + "SCQ_NM_battle";
		ReOpenQuestHeader(sTitle);
		AddQuestRecordEx(sTitle, "SCQ_NM_battle", "1");
		AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
		AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony" + npchar.quest.Qcity));
		AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
		AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
		AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;

	case "SCQ_NM_prisoner": // вариант В
		dialog.text = "Exactamente. Encuéntralo y tráemelo. Vivo. Quiero encargarme de él yo mismo. Te recompensaré generosamente.";
		link.l1 = "Bueno, puedo intentar encontrarlo, pero necesito detalles.";
		link.l1.go = "SCQ_NM_prisoner_1";
		break;

	case "SCQ_NM_prisoner_1":
		npchar.quest.SeekCap = "NM_prisoner";		   // личный флаг на квест
		SetSeekCapCitizenParam(npchar, rand(NON_PIRATES)); // любая нация кроме пиратов
		makearef(forName, npchar.quest.SeekCap);
		forName.nation = sti(npchar.nation);
		forName.sex = "man";
		forName.name = GenerateRandomName(sti(npchar.nation), "man");
		dialog.text = "El nombre del bastardo es " + npchar.quest.SeekCap.name + ". Sirve en " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")) + " llamado " + npchar.quest.SeekCap.shipName + ", que está bajo el mando de " + npchar.quest.SeekCap.capName + ". El barco a menudo se puede ver en el puerto de " + XI_ConvertString("Colony" + npchar.quest.Qcity) + ". Te pagaré por este trabajo " + FindRussianMoneyString(sti(npchar.quest.money)) + " en doblones de oro.";
		link.l1 = "Eso es suficiente para mí. Estaré atento en mar abierto.";
		link.l1.go = "SCQ_NM_prisoner_2";
		link.l2 = "No es suficiente para ese tipo de trabajo.";
		link.l2.go = "SCQ_exit_clear";
		break;

	case "SCQ_NM_prisoner_2":
		dialog.text = "Me alegra que hayamos llegado a un acuerdo. Estaré esperando tu regreso.";
		link.l1 = "¿Dónde podré encontrarte? Aclarémoslo ahora, no quiero perder tiempo buscándote.";
		link.l1.go = "SCQ_NM_prisoner_3";
		break;

	case "SCQ_NM_prisoner_3":
		dialog.text = "Cada mañana asisto a un servicio en la iglesia. Puedes encontrarme allí todos los días de 8 a 9 a.m.";
		link.l1 = "¡Trato hecho! Espera el resultado pronto.";
		link.l1.go = "exit";
		DeleteAttribute(npchar, "LifeDay");
		DeleteAttribute(npchar, "talker");
		DeleteAttribute(npchar, "CityType"); // удалить признак фантома, иначе - пустые города
		LAi_SetLoginTime(npchar, 8.0, 10.0);
		pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
		npchar.location = npchar.city + "_church";
		npchar.location.locator = "goto2";
		pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
		pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
		pchar.quest.SeekShip_Stay.Idx = npchar.index;
		NextDiag.TempNode = "SCQ_NM_result";
		sTitle = npchar.city + "SCQ_NM_prisoner";
		ReOpenQuestHeader(sTitle);
		AddQuestRecordEx(sTitle, "SCQ_NM_prisoner", "1");
		AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
		AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony" + npchar.quest.Qcity));
		AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
		AddQuestUserData(sTitle, "sName1", npchar.quest.SeekCap.name);
		AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
		AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;

	case "SCQ_NM_peace": // вариант С
		dialog.text = "¡Exactamente! Encuéntralo y dile que vivo en esta ciudad. Pagaré por tus servicios.";
		link.l1 = "Bueno... Puedo intentarlo. Dime los detalles.";
		link.l1.go = "SCQ_NM_peace_1";
		break;

	case "SCQ_NM_peace_1":
		npchar.quest.SeekCap = "NM_peace";					// личный флаг на квест
		SetSeekCapCitizenParam(npchar, sti(npchar.nation)); // нация = нации квестодателя
		dialog.text = "Su nombre es " + npchar.quest.SeekCap.capName + ". Y sirve en " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")) + " " + npchar.quest.SeekCap.shipName + "'. A menudo visita " + XI_ConvertString("Colony" + npchar.quest.Qcity) + " Te pagaré por este trabajo " + FindRussianMoneyString(sti(npchar.quest.money)) + " en doblones de oro.";
		link.l1 = "¡Trato hecho! Supongo que encontraré a tu amigo bastante pronto.";
		link.l1.go = "SCQ_NM_peace_2";
		link.l2 = "No es suficiente para mí.";
		link.l2.go = "SCQ_exit_clear";
		break;

	case "SCQ_NM_peace_2":
		dialog.text = "Me alegra que hayamos llegado a un acuerdo. Estaré esperando tu regreso.";
		link.l1 = "¿Dónde podré encontrarte? Aclarémoslo ahora, no quiero perder tiempo buscándote.";
		link.l1.go = "SCQ_NM_peace_3";
		break;

	case "SCQ_NM_peace_3":
		dialog.text = "Siempre asisto a un servicio vespertino en la iglesia. Puedes encontrarme allí todos los días de 6 a 8 p.m.";
		link.l1 = "¡Trato hecho! Espera el resultado pronto.";
		link.l1.go = "exit";
		DeleteAttribute(npchar, "LifeDay");
		DeleteAttribute(npchar, "talker");
		DeleteAttribute(npchar, "CityType"); // удалить признак фантома, иначе - пустые города
		LAi_SetLoginTime(npchar, 18.0, 20.0);
		pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
		npchar.location = npchar.city + "_church";
		npchar.location.locator = "goto2";
		pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
		pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
		pchar.quest.SeekShip_Stay.Idx = npchar.index;
		NextDiag.TempNode = "SCQ_NM_result";
		sTitle = npchar.city + "SCQ_NM_peace";
		ReOpenQuestHeader(sTitle);
		AddQuestRecordEx(sTitle, "SCQ_NM_peace", "1");
		AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
		AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony" + npchar.quest.Qcity));
		AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
		AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
		AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;

	//--> разговор на суше, вариант А
	case "NM_battleCap":
		dialog.text = "¿Y? ¿Qué quieres, señor?";
		link.l1 = "¿Eres el capitán " + GetFullName(npchar) + "?";
		link.l1.go = "NM_battleCap_1";
		break;

	case "NM_battleCap_1":
		dialog.text = "Sí lo soy. ¿Cuál es el trato?";
		link.l1 = "Un hombre tiene un gran interés en vos, su nombre es " + GetFullName(&characters[GetCharacterIndex("CiudadanoDeMisión_" + npchar.quest.cribCity)]) + "¿Recuerdas?";
		link.l1.go = "NM_battleCap_2";
		link.l2 = "He oído que tienes mucho caoba en tus bodegas. Quiero comprarlo. ¿Me lo venderás?";
		link.l2.go = "NM_battleCap_4";
		break;

	case "NM_battleCap_2":
		dialog.text = "Es la primera vez que oigo este nombre. Te has equivocado de alguna manera, capitán. ¿Hemos terminado?";
		link.l1 = "Mm. Bien, perdóname...";
		link.l1.go = "NM_battleCap_exit";
		link.l2 = "Oh, ¿de veras? Pero él te recuerda bastante bien. Mencionó tu deuda con él...";
		link.l2.go = "NM_battleCap_3";
		break;

	case "NM_battleCap_3":
		dialog.text = "¿Qué deuda? ¿De qué estás hablando?";
		link.l1 = "¡La deuda de honor!";
		link.l1.go = "NM_battleCap_fight";
		break;

	case "NM_battleCap_4":
		dialog.text = "Eres un error. No comercio con madera. ¿Hemos terminado?";
		link.l1 = "Hm. Bien, discúlpame...";
		link.l1.go = "NM_battleCap_exit";
		break;

	case "NM_battleCap_exit":
		DialogExit();
		NextDiag.TempNode = "NM_battleDeck_exit";
		npchar.DeckDialogNode = "NM_battleDeck_exit";
		break;

	case "NM_battleCap_fight":
		NextDiag.TempNode = "NM_battleDeck_exit";
		npchar.DeckDialogNode = "NM_battleDeck_exit";
		LAi_group_Attack(NPChar, Pchar);
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	//--> разговор на суше и палубе одинаковый, вариант В
	case "NM_prisonerCap":
		dialog.text = "¿Y? ¿Qué desea, señor?";
		link.l1 = "¿Eres el capitán " + GetFullName(npchar) + "?";
		link.l1.go = "NM_prisonerCap_1";
		break;

	case "NM_prisonerCap_1":
		sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]; // квестодатель
		dialog.text = "Sí, soy yo. ¿Cuál es el trato?";
		link.l1 = "¿Un hombre llamado " + sld.quest.SeekCap.name + " servir bajo tu mando?";
		link.l1.go = "NM_prisonerCap_2";
		break;

	case "NM_prisonerCap_2":
		sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]; // квестодатель
		dialog.text = "Sí. Es uno de mis oficiales. Ahora dime, ¿por qué preguntas?";
		link.l1 = "Claro, te lo diré. Estoy buscando a este hombre por orden de las autoridades de " + XI_ConvertString("Colony" + sld.city + "Gen") + ", y tengo el poder de arrestarle y entregarle a " + XI_ConvertString("Colony" + sld.city) + "  Te pido que me ayudes con este asunto para que podamos resolverlo pacíficamente.";
		link.l1.go = "NM_prisonerCap_3";
		break;

	case "NM_prisonerCap_3":
		if (sti(npchar.reputation.nobility) > 41)
		{
			dialog.text = "¿De verdad? ¿Y tal hombre sirve en mi tripulación? ¿Hablas en serio?";
			link.l1 = "No te molestes con eso, " + GetAddress_FormToNPC(NPChar) + ". Enviaré un bote a tu barco y lo llevaremos nosotros mismos.";
			link.l1.go = "NM_prisonerCap_good";
		}
		else
		{
			dialog.text = "¡No me diga! ¿Sabe qué, señor? No me importa un comino su pasado. No me concierne. ¿Y quién es usted, por cierto? ¿Autoridades? ¿De verdad? ¡Ja! No le entrego a mis hombres ni a usted ni a nadie más. Esta conversación ha terminado. ¡Váyase!";
			link.l1 = "¡Mala elección... Terrible!";
			link.l1.go = "NM_prisonerCap_bad";
		}
		break;

	case "NM_prisonerCap_good":
		dialog.text = "Haz lo que tengas que hacer.";
		link.l1 = "En ello.";
		link.l1.go = "NM_prisonerCap_good_1";
		break;

	case "NM_prisonerCap_good_1":
		DialogExit();
		NextDiag.CurrentNode = "NM_prisonerDeck_exit";
		npchar.DeckDialogNode = "NM_prisonerDeck_exit";
		npchar.quest.release = "true";
		sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
		ref chr = GetCharacter(NPC_GenerateCharacter(npchar.quest.SeekCap + "_" + npchar.quest.cribCity, "citiz_" + (rand(9) + 21), "man", "man", 5, sti(npchar.nation), -1, false, "citizen"));
		chr.name = sld.quest.SeekCap.name;
		chr.lastname = "";
		// pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(chr);
		// SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
		AddPassenger(pchar, chr, false); // добавить пассажира
		SetCharacterRemovable(chr, false);
		log_info(sld.quest.SeekCap.name + " está bajo arresto");
		PlaySound("interface\notebook.wav");
		sTemp = "SCQ_" + npchar.index;
		pchar.quest.(sTemp).win_condition.l1 = "MapEnter";
		pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
		// DoQuestFunctionDelay("SCQ_seekCapIsDeath", 0.5); // 170712
		AddCharacterExpToSkill(pchar, "Fortune", 200); // везение
		break;

	case "NM_prisonerCap_bad":
		DialogExit();
		NextDiag.CurrentNode = "NM_prisonerDeck_exit";
		npchar.DeckDialogNode = "NM_prisonerDeck_exit";
		npchar.quest.mustboarding = "true";
		sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]; // квестодатель
		sTitle = sld.City + "SCQ_" + sld.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + sld.quest.SeekCap, "6");
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;

	case "NM_prisonerDeck_exit":
		dialog.text = "¿Hemos terminado, capitán?";
		link.l1 = "...";
		link.l1.go = "exit";
		NextDiag.TempNode = "NM_prisonerDeck_exit";
		break;

	//--> разговор на суше и палубе одинаковый, вариант C
	case "NM_peaceCap":
		dialog.text = "Buen día. ¿Qué desea, capitán?";
		link.l1 = "Eres capitán " + GetFullName(npchar) + ", ¿verdad?";
		link.l1.go = "NM_peaceCap_1";
		break;

	case "NM_peaceCap_1":
		sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity); // квестодатель
		dialog.text = "Tienes razón. ¿Tienes algo para mí?";
		link.l1 = "Tengo. Un hombre llamado " + GetFullName(sld) + " te está buscando. Quiere que lo visites lo antes posible. Vive en " + XI_ConvertString("Colony" + npchar.quest.cribCity + "Voc") + ".";
		link.l1.go = "NM_peaceCap_2";
		break;

	case "NM_peaceCap_2":
		dialog.text = "¡Ja! ¿Así que él también se trasladó al Nuevo Mundo? Entonces realmente debería hacerle una visita... ¡Gracias por la información, señor!";
		link.l1 = "De nada. Mi trabajo será pagado por tu amigo. ¡Buena suerte, " + GetAddress_FormToNPC(NPChar) + "!";
		link.l1.go = "NM_peaceCap_3";
		break;

	case "NM_peaceCap_3":
		DialogExit();
		NextDiag.CurrentNode = "NM_peaceCap_exit";
		npchar.DeckDialogNode = "NM_peaceCap_exit";
		sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Acc"));
		sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity); // квестодатель
		sld.quest.SeekCap = sld.quest.SeekCap + "over";				  // дополняем флаг квест до 'выполнен'
		// удаляем запись в базе кэпов
		makearef(forName, NullCharacter.capitainBase);
		DeleteAttribute(forName, npchar.id);
		break;

	case "NM_peaceCap_exit":
		dialog.text = "Fue un placer, " + GetAddress_Form(NPChar) + ".";
		link.l1 = "El placer fue mío, capitán.";
		link.l1.go = "exit";
		NextDiag.TempNode = "NM_peaceCap_exit";
		break;

	//--> встреча на палубе, вариант А
	case "NM_battleDeck":
		dialog.text = "Ahoy, " + GetAddress_Form(NPChar) + ". ¿Qué quieres?";
		link.l1 = "Escuché que tienes mucho palo de rosa en tu carga y quiero comprarlo. ¿Lo venderás?";
		link.l1.go = "NM_battleDeck_1";
		break;

	case "NM_battleDeck_1":
		dialog.text = "Eres un equivocado. No comercia ninguna madera y tu visita aquí me huele bastante sospechosa. ¡Creo que será mejor que dejes mi barco!";
		link.l1 = "Está bien, solo estaba preguntando. Adiós.";
		link.l1.go = "exit";
		NextDiag.TempNode = "NM_battleDeck_exit";
		npchar.DeckDialogNode = "NM_battleDeck_exit";
		sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;

	case "NM_battleDeck_exit":
		dialog.text = "¿Quieres problemas, señor? ¿Debería repetirlo?";
		link.l1 = "...";
		link.l1.go = "exit";
		NextDiag.TempNode = "NM_battleDeck_exit";
		break;

		//--> абордаж, вариант А
	case "NM_battleBoard":
		sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
		dialog.text = "¿Por qué has atacado mi barco, granuja?";
		link.l1 = "Estoy aquí para darte los mejores saludos de " + XI_ConvertString("Colony" + npchar.quest.cribCity) + " , del hombre llamado " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]) + "Espero que entiendas la situación ahora.";
		link.l1.go = "NM_battleBoard_1";
		break;

	case "NM_battleBoard_1":
		dialog.text = "¡Imposible! Entonces, nada que perder para mí...";
		link.l1 = "¿Qué tal tu vida?";
		link.l1.go = "NM_battleBoard_2";
		break;

	case "NM_battleBoard_2":
		DialogExit();
		LAi_SetCurHPMax(npchar);
		QuestAboardCabinDialogFree();
		LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//--> абордаж, вариант В
	case "NM_prisonerBoard":
		sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]; // квестодатель
		dialog.text = "¿Por qué has atacado mi barco, granuja?";
		if (CheckAttribute(npchar, "quest.mustboarding"))
		{
			link.l1 = "¿Tienes alguna idea? Te he pedido que me entregues a tu oficial pacíficamente. ¡Ahora me lo llevo, a ti y a tu cascarón!";
			link.l1.go = "NM_prisonerBoard_1";
		}
		else
		{
			link.l1 = "Hay un canalla que sirve bajo tu mando. Su nombre es " + sld.quest.SeekCap.name + ". Autoridades de " + XI_ConvertString("Colony" + npchar.quest.cribCity) + " están realmente ansiosos por verle. Será arrestado y puesto en mi bodega.";
			link.l1.go = "NM_prisonerBoard_1";
		}
		break;

	case "NM_prisonerBoard_1":
		dialog.text = "¿Y por eso has cometido una matanza en mi barco? ¡Bastardo! Aún me queda algo de fuerza... ¡Te mataré!";
		link.l1 = "Hombres más fuertes lo han intentado...";
		link.l1.go = "NM_prisonerBoard_2";
		break;

	case "NM_prisonerBoard_2":
		DialogExit();
		LAi_SetCurHPMax(npchar);
		pchar.GenQuest.mustboarding = "true"; // ставим этот флаг для завершения квеста
		QuestAboardCabinDialogFree();
		LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_GivePrisoner");
		AddDialogExitQuest("MainHeroFightModeOn");
		pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; // флаг квеста для нпс
		pchar.GenQuest.CitizSeekCap.nation = npchar.nation;		  // нацию для нпс
		pchar.GenQuest.CitizSeekCap.sex = "man";
		pchar.GenQuest.CitizSeekCap.ani = "man";
		pchar.GenQuest.CitizSeekCap.model = "citiz_" + (rand(9) + 21);	  // модель для нпс
		pchar.GenQuest.CitizSeekCap.PrisonerCity = npchar.quest.cribCity; // исходный город для нпс
		sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
		pchar.GenQuest.CitizSeekCap.PrisonerName = sld.quest.SeekCap.name; // имя и фамилию для нпс
		pchar.GenQuest.CitizSeekCap.PrisonerLastname = "";
		AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
		break;

	//--> результаты квестов дворян
	case "SCQ_NM_result":
		dialog.text = "¿Qué dices, capitán? ¿Tienes algún progreso con mi asunto?";
		link.l1 = "Aún no. Pero estoy en ello.";
		link.l1.go = "exit";
		switch (npchar.quest.SeekCap)
		{
		case "NM_battleover": // сдача квеста, вариант А
			dialog.text = "¿Qué decís, capitán? ¿Tenéis algún progreso con mi asunto?";
			link.l1 = "Claro que sí. Y te va a gustar." + npchar.quest.SeekCap.capName + " está muerto y su " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName)) + " está en el fondo del mar.";
			link.l1.go = "SCQ_NM_result_A1";
			break;

		case "NM_prisonerover": // сдача квеста, вариант B
			dialog.text = "¿Qué decís, capitán? ¿Habéis avanzado con mi asunto?";
			link.l1 = "Hago. Y te va a gustar." + npchar.quest.SeekCap.Name + " está sentado en la cabina de mi barco bajo arresto.";
			link.l1.go = "SCQ_NM_result_B1";
			break;

		case "NM_peaceover": // сдача квеста, вариант C
			dialog.text = "Ajá, aquí estás. Me alegra verte. ¡Me informaron que has tenido éxito en tu misión!";
			link.l1 = "¿Te visitó tu amigo?";
			link.l1.go = "SCQ_NM_result_C1";
			break;
		}
		break;

	case "SCQ_NM_result_A1":
		dialog.text = "¡Espléndido! Sabía que podía contar contigo. Aquí, toma tu oro. Te lo has ganado.";
		link.l1 = "Gracias. Háblame de nuevo en caso de que consigas otro enemigo.";
		link.l1.go = "SCQ_exit";
		sTemp = "SCQ_" + npchar.index;
		pchar.quest.(sTemp).over = "yes"; // снимаем прерывание смерть горожанина-квестодателя
		TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
		Log_Info("Has recibido " + FindRussianDublonString(sti(npchar.quest.dublon)) + "");
		PlaySound("interface\important_item.wav");
		sTitle = npchar.city + "SCQ_NM_battle";
		CloseQuestHeader(sTitle);
		ChangeCharacterComplexReputation(pchar, "nobility", -1);
		ChangeCharacterComplexReputation(pchar, "authority", 1);
		OfficersReaction("bad");
		ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
		AddComplexSeaExpToScill(100, 50, 50, 50, 50, 50, 0);
		AddCharacterExpToSkill(pchar, "Leadership", 100); // авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 50);	  // везение
		break;

	case "SCQ_NM_result_B1":
		dialog.text = "¡Espléndido! Ordenaré a mis hombres que lo saquen de tu barco inmediatamente. ¡No escapará ahora! Aquí, toma tu oro. Te lo has ganado.";
		link.l1 = "Gracias. Dirígete a mí en cualquier momento para un trabajo como este.";
		link.l1.go = "SCQ_exit";
		sTemp = "SCQ_" + npchar.index;
		pchar.quest.(sTemp).over = "yes"; // снимаем прерывание смерть горожанина-квестодателя
		TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
		Log_Info("Has recibido " + FindRussianDublonString(sti(npchar.quest.dublon)) + "");
		PlaySound("interface\important_item.wav");
		sTitle = npchar.city + "SCQ_NM_prisoner";
		CloseQuestHeader(sTitle);
		sld = characterFromId("NM_prisoner_" + npchar.City);
		RemovePassenger(pchar, sld); // 170712
		// ReleasePrisoner(sld);
		sld.lifeday = 0;
		ChangeCharacterComplexReputation(pchar, "authority", 1);
		ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
		AddCharacterExpToSkill(pchar, "Sailing", 100);	  // навигация
		AddCharacterExpToSkill(pchar, "Leadership", 150); // авторитет
		break;

	case "SCQ_NM_result_C1":
		dialog.text = "Sí, estuvo aquí y me habló de ti. Aquí, toma tu oro. Te lo has ganado.";
		link.l1 = "Mis gracias. ¡Adiós, señor!";
		link.l1.go = "SCQ_exit";
		sTemp = "SCQ_" + npchar.index;
		pchar.quest.(sTemp).over = "yes"; // снимаем прерывание смерть горожанина-квестодателя
		sld = characterFromId(npchar.quest.SeekCap.capId);
		sld.lifeday = 0;
		Map_ReleaseQuestEncounter(sld.id);
		sGroup = "SeekCapShip_" + sld.index;
		group_DeleteGroup(sGroup);
		sTemp = "SecondTimer_" + sld.id;
		pchar.quest.(sTemp).over = "yes"; // снимаем возможный таймер на выход в море
		sTemp = "SCQ_" + sld.index;
		pchar.quest.(sTemp).over = "yes"; // снимаем прерывание смерть кэпа
		TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
		Log_Info("Has recibido " + FindRussianDublonString(sti(npchar.quest.dublon)) + "");
		PlaySound("interface\important_item.wav");
		sTitle = npchar.city + "SCQ_NM_peace";
		CloseQuestHeader(sTitle);
		ChangeCharacterComplexReputation(pchar, "nobility", 1);
		OfficersReaction("good");
		ChangeCharacterComplexReputation(pchar, "authority", 1);
		ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
		AddCharacterExpToSkill(pchar, "Sailing", 100);	  // навигация
		AddCharacterExpToSkill(pchar, "Leadership", 200); // авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 50);	  // везение
		break;
		//<-- поисковые квесты дворян

	//========= квесты мужиков ===========
	case "SCQ_man":
		dialog.text = LinkRandPhrase("Saludos, capitán. Quiero pedir tu ayuda.", "¡Capitán! ¿Puedes ayudarme? Por favor.", "¡Capitán, le estoy pidiendo su ayuda!");
		link.l1 = RandPhraseSimple("Estoy ocupado.", "Estoy apurado.");
		link.l1.go = "SCQ_exit";
		link.l2 = RandPhraseSimple("¿Qué pasa?", "Di qué te molesta. Quizás pueda ayudarte.");
		link.l2.go = "SCQ_man_1";
		break;
	case "SCQ_exit":
		// минус один шанс, что следующий квестодатель сам заговорит
		sld = &locations[FindLocation(npchar.location)];
		if (sti(sld.questSeekCap) > 0)
			sld.questSeekCap = sti(sld.questSeekCap) - 1;
		npchar.lifeDay = 0;
		LAi_CharacterDisableDialog(npchar);
		DialogExit();
		break;
	case "SCQ_exit_clear":
		// минус один шанс, что следующий квестодатель сам заговорит
		sld = &locations[FindLocation(npchar.location)];
		if (sti(sld.questSeekCap) > 0)
			sld.questSeekCap = sti(sld.questSeekCap) - 1;
		sld = characterFromId(npchar.quest.SeekCap.capId); // капитан
		sld.lifeDay = 0;
		Map_ReleaseQuestEncounter(sld.id);
		sGroup = "SeekCapShip_" + sld.index;
		group_DeleteGroup(sGroup);
		sTemp = "SCQ_" + sld.index;
		pchar.quest.(sTemp).over = "yes"; // снимаем прерывание смерть кэпа
		sTemp = "SCQ_" + npchar.index;
		pchar.quest.(sTemp).over = "yes"; // снимаем прерывание смерть квестодателя
		npchar.lifeDay = 0;
		LAi_CharacterDisableDialog(npchar);
		DialogExit();
		break;
	// выбираем квест
	case "SCQ_man_1":
		switch (npchar.quest.SeekCap.numQuest)
		{
		case "0":
			dialog.text = "Hace un año un capitán prometió llevarme a " + XI_ConvertString("Colony" + SelectNotEnemyColony(NPChar) + "Acc") + ". Pero mientras estaba en su barco, me echaron a la bodega y luego me vendieron como esclavo. Apenas lo superé. Estuve cerca de la muerte varias veces... De todos modos, quiero recordarle a mi 'amigo' que todavía estoy vivo."; // belamour gen
			link.l1 = "¿Qué quieres decir? Dime exactamente lo que quieres.";
			link.l1.go = "SCQ_Slave";
			break;
		case "1":
			dialog.text = "Mi esposa fue secuestrada. Un capitán, un pirata como dicen, la estaba cortejando. Mi esposa tuvo que quedarse en casa durante días, por culpa de su acecho. He intentado que las autoridades de la ciudad nos ayuden, pero fracasé. Y ahora...";
			link.l1 = "¿Y ahora qué?";
			link.l1.go = "SCQ_RapeWife";
			break;
		case "2":
			dialog.text = "Sabes, estoy buscando a mi compatriota. Hace tres años llegamos juntos aquí desde Europa para encontrar una vida mejor. Nos perdimos el rastro. ¡Pero no hace mucho escuché que ahora es capitán de un barco mercante! Traté de encontrarlo yo mismo, pero fracasé.";
			link.l1 = "¿Entonces?";
			link.l1.go = "SCQ_Friend";
			break;
		}
		break;
	// квест бывшего раба, которого негодяй-кэп взял в плен
	case "SCQ_Slave":
		dialog.text = "Quiero que lo encuentres y lo mates. Quiero que esté tan muerto que ni siquiera puedo comer...";
		link.l1 = "Ya veo... Supongo que puedo ayudarte con eso. Dime su nombre y el nombre de su barco.";
		link.l1.go = "SCQ_Slave_1";
		link.l2 = "Lo siento pero no estoy interesado.";
		link.l2.go = "SCQ_exit";
		break;
	case "SCQ_Slave_1":
		npchar.quest.SeekCap = "manSlave"; // личный флаг ситизена на квест
		SetSeekCapCitizenParam(npchar, PIRATE);
		dialog.text = "" + npchar.quest.SeekCap.capName + " del " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")) + " llamado " + npchar.quest.SeekCap.shipName + ". Te pagaré  " + FindRussianMoneyString(sti(npchar.quest.money)) + ", además de todas mis joyas."; // belamour gen
		link.l1 = "Ya veo. Estaré atento en el mar. Si encuentro el objetivo... Considéralo muerto entonces.";
		link.l1.go = "SCQ_Slave_2";
		link.l2 = "No haré nada por esa cantidad de dinero. Encuentra a otro tonto para llevar a cabo tu venganza.";
		link.l2.go = "SCQ_exit_clear";
		break;
	case "SCQ_Slave_2":
		dialog.text = "¡Eso es lo que esperaba escuchar! ¡Oh, ahora puedo comer! ¡Finalmente! Tengo que conseguir algo de comida...";
		link.l1 = "Buen provecho. Te encontraré una vez que el trabajo esté hecho.";
		link.l1.go = "SCQ_Slave_3";
		break;
	case "SCQ_Slave_3":
		dialog.text = "Te estaré esperando en la iglesia.";
		link.l1 = "Bien.";
		link.l1.go = "exit";
		//==> ставим квестодателя в церковь
		pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
		npchar.location = npchar.city + "_church";
		npchar.location.locator = "goto2";
		pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
		pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
		pchar.quest.SeekShip_Stay.Idx = npchar.index;
		NextDiag.TempNode = "SCQ_manResult";
		sTitle = npchar.city + "SCQ_manSlave";
		ReOpenQuestHeader(sTitle);
		AddQuestRecordEx(sTitle, "SCQ_manSlave", "1");
		AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
		AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
		AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
		AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
		break;
	// пират похитил жену у ситизена
	case "SCQ_RapeWife":
		dialog.text = "Me distraje y el bastardo se llevó a mi esposa a bordo de su barco. ¡Te pido que encuentres a este sinvergüenza!";
		link.l1 = "Mm, ¿y por qué debería pelear con un compañero granuja?";
		link.l1.go = "SCQ_RapeWife_1";
		break;
	case "SCQ_RapeWife_1":
		npchar.quest.SeekCap = "manRapeWife"; // личный флаг ситизена на квест
		SetSeekCapCitizenParam(npchar, PIRATE);
		makearef(forName, npchar.quest.SeekCap);
		forName.nation = npchar.nation;
		forName.sex = "woman";
		SetRandomNameToCharacter(forName);	// npchar.quest.SeekCap.name - имя жены ситизена
		forName.lastname = npchar.lastname; // фамилия как и у мужа есно
		dialog.text = "No soy rico, pero será un placer darte todos los objetos de valor que poseo. ¡Si liberas a mi esposa y la traes a mí, te pagaré " + FindRussianMoneyString(sti(npchar.quest.money)) + ", además de todas mis joyas.";
		link.l1 = "Está bien, estoy dentro. Dime los detalles. Su nombre, su barco y cómo se llama tu esposa.";
		link.l1.go = "SCQ_RapeWife_2";
		link.l2 = "No, amigo, no quiero hacerlo por una suma tan pequeña. Lo siento...";
		link.l2.go = "SCQ_exit_clear";
		break;
	case "SCQ_RapeWife_2":
		dialog.text = "Su nombre es " + npchar.quest.SeekCap.name + ". Y el nombre del bastardo es " + npchar.quest.SeekCap.capName + ", él nada en " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")) + " llamado " + npchar.quest.SeekCap.shipName + "."; // belamour gen
		link.l1 = "Las mierdas flotan, amigo. Los capitanes navegan...";
		link.l1.go = "SCQ_RapeWife_3";
		break;
	case "SCQ_RapeWife_3":
		dialog.text = "¡Sí, sí, lo siento mucho! No soy marinero, espero que lo entiendas...";
		link.l1 = "Está bien, no te preocupes. Como sea, volveré tan pronto como esté hecho.";
		link.l1.go = "SCQ_RapeWife_4";
		break;
	case "SCQ_RapeWife_4":
		dialog.text = "¡Muchas gracias! Te estaré esperando en la iglesia. Pero te ruego que te apresures. Estoy realmente preocupado por mi esposa...";
		link.l1 = "Sí, tampoco la envidio.";
		link.l1.go = "exit";
		//==> ставим квестодателя в церковь
		pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
		npchar.location = npchar.city + "_church";
		npchar.location.locator = "goto2";
		pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
		pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
		pchar.quest.SeekShip_Stay.Idx = npchar.index;
		NextDiag.TempNode = "SCQ_manResult";
		sTitle = npchar.city + "SCQ_manRapeWife";
		ReOpenQuestHeader(sTitle);
		AddQuestRecordEx(sTitle, "SCQ_manRapeWife", "1");
		AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData(sTitle, "sSex", GetSexPhrase("", ""));
		AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
		AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
		AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		AddQuestUserData(sTitle, "sName2", npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname);
		AddQuestUserData(sTitle, "sSex", GetSexPhrase("", ""));
		break;
	// поиски земляка
	case "SCQ_Friend":
		dialog.text = "El problema es que mi amigo no tiene propiedades. Su barco es su hogar. Así que no puedo encontrarlo, porque siempre está navegando. Y no puedo permitirme viajes inútiles, tengo que ganar dinero para vivir.";
		link.l1 = "No puedo ayudarte, si no tienes dinero...";
		link.l1.go = "SCQ_Friend_1";
		break;
	case "SCQ_Friend_1":
		npchar.quest.SeekCap = "manFriend"; // личный флаг ситизена на квест
		SetSeekCapCitizenParam(npchar, sti(npchar.nation));
		dialog.text = "Puedo pagarte " + FindRussianMoneyString(sti(npchar.quest.money)) + " y te daré todas mis joyas. Esto es todo lo que puedo permitir ahora.";
		link.l1 = "Esta suma me conviene. Estoy dentro. De hecho, puedes unirte a mí como pasajero, así verás a tu amigo tan pronto como lo encontremos.";
		link.l1.go = "SCQ_Friend_2";
		link.l2 = "No es suficiente para mí. Busca a alguien más para hacerlo.";
		link.l2.go = "SCQ_exit_clear";
		break;
	case "SCQ_Friend_2":
		dialog.text = "No, supongo que me quedaría aquí. No sabemos cuánto tiempo durarán estas búsquedas y podría perder todo mi dinero. Tengo un trabajo aquí.";
		link.l1 = "Ya veo. Ahora dime, ¿quién es tu amigo y en qué barco está?";
		link.l1.go = "SCQ_Friend_3";
		break;
	case "SCQ_Friend_3":
		dialog.text = "Su nombre es " + npchar.quest.SeekCap.capName + "  Según sé, él comanda un " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Acc")) + " llamado " + npchar.quest.SeekCap.shipName + "."; // belamour gen
		link.l1 = "Ya veo. Bueno, le contaré a tu amigo sobre ti si lo veo.";
		link.l1.go = "SCQ_Friend_4";
		break;
	case "SCQ_Friend_4":
		dialog.text = "Gracias. Estaré esperando tu llegada en la iglesia. Recibirás tus monedas una vez que el trabajo esté hecho.";
		link.l1 = "Claro. Entonces, adiós, espera los resultados pronto.";
		link.l1.go = "exit";
		//==> ставим квестодателя в церковь
		pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
		npchar.location = npchar.city + "_church";
		npchar.location.locator = "goto2";
		pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
		pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
		pchar.quest.SeekShip_Stay.Idx = npchar.index;
		NextDiag.TempNode = "SCQ_manResult";
		sTitle = npchar.city + "SCQ_manFriend";
		ReOpenQuestHeader(sTitle);
		AddQuestRecordEx(sTitle, "SCQ_manFriend", "1");
		AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData(sTitle, "sSex", GetSexPhrase("", ""));
		AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
		AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
		AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		AddQuestUserData(sTitle, "sSex", GetSexPhrase("", ""));
		AddQuestUserData(sTitle, "sSex1", GetSexPhrase("", ""));
		break;

	// --- результаты мужских квестов ---
	case "SCQ_manResult":
		dialog.text = "Buen día a usted, capitán. ¿Ya tiene algún resultado?";
		link.l1 = "Recuérdame tu problema...";
		link.l1.go = "SCQ_manResult_exit";
		switch (npchar.quest.SeekCap)
		{
		case "manSlaveover":
			dialog.text = "Tengo entendido que fui vengado. ¿Es así?";
			link.l1 = "Exactamente. " + npchar.quest.SeekCap.capName + " está muerto y su " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName)) + " está en el fondo del mar.";
			link.l1.go = "SCQR_manSlave";
			break;
		case "manRapeWifeover":
			dialog.text = "¡Has encontrado a mi esposa! ¡No puedo creerlo! ¿Puedo?";
			link.l1 = "Tú puedes. Ella es mi pasajera. La puedes llevar de vuelta, si " + npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname + " realmente es tu esposa...";
			link.l1.go = "SCQR_manRapeWife";
			break;
		case "manFriendover":
			dialog.text = "Buen día para ti, capitán. ¿Has encontrado a mi compañero?";
			link.l1 = "Le he contado sobre ti.";
			link.l1.go = "SCQR_manFriend";
			break;
		}
		break;
	case "SCQ_manResult_exit":
		switch (npchar.quest.SeekCap)
		{
		case "manSlave":
			dialog.text = "¿Qué? ¿De verdad has olvidado que te pedí vengar al capitán " + npchar.quest.SeekCap.capName + " ¿por un año de mi esclavitud?";
			link.l1 = "No, no lo he hecho.";
			link.l1.go = "exit";
			break;
		case "manRapeWife":
			dialog.text = "¡No puedo creer lo que oigo! ¿Has olvidado que te pedí que encontraras y liberaras a mi esposa? ¡Fue capturada por el pirata llamado " + npchar.quest.SeekCap.capName + "!";
			link.l1 = "No lo he hecho.";
			link.l1.go = "exit";
			break;
		case "manFriend":
			dialog.text = "Espera un momento... ¿Has olvidado tu promesa de encontrar a mi camarada llamado " + npchar.quest.SeekCap.capName + "?";
			link.l1 = "No lo he hecho.";
			link.l1.go = "exit";
			break;
		}
		break;

	case "SCQR_manSlave":
		dialog.text = "¡Excelente, tenía razón sobre ti! Así que, como te prometí, aquí están tus " + FindRussianMoneyString(sti(npchar.quest.money)) + " y joyas. Gracias por tu ayuda.";
		link.l1 = "De nada...";
		link.l1.go = "SCQ_exit";
		sTemp = "SCQ_" + npchar.index;
		pchar.quest.(sTemp).over = "yes"; // снимаем прерывание смерть горожанина-квестодателя
		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
		TakeNItems(pchar, npchar.quest.gem, 10 + hrand(8));
		sTitle = npchar.city + "SCQ_manSlave";
		CloseQuestHeader(sTitle);
		break;
	case "SCQR_manRapeWife":
		dialog.text = "¡Oh Dios mío! ¡Nos has salvado! Por favor, toma tu " + FindRussianMoneyString(sti(npchar.quest.money)) + " y joyas. ¡Y sabed que rezaremos por vosotros para siempre!";
		link.l1 = "Reza si quieres. No tengo problemas con eso.";
		link.l1.go = "SCQ_exit";
		sld = characterFromId("manRapeWife_" + npchar.City);
		RemovePassenger(pchar, sld);
		sld.lifeDay = 0;
		sTemp = "SCQ_" + npchar.index;
		pchar.quest.(sTemp).over = "yes"; // снимаем прерывание смерть горожанина-квестодателя
		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
		TakeNItems(pchar, npchar.quest.gem, 12 + hrand(8));
		sTitle = npchar.city + "SCQ_manRapeWife";
		CloseQuestHeader(sTitle);
		break;
	case "SCQR_manFriend":
		dialog.text = "¡Espléndido!... Aquí, toma " + FindRussianMoneyString(sti(npchar.quest.money)) + " y joyas. Y gracias, capitán.";
		link.l1 = "De nada, amigo. Adiós...";
		link.l1.go = "SCQ_exit";
		sTemp = "SCQ_" + npchar.index;
		pchar.quest.(sTemp).over = "yes"; // снимаем прерывание смерть горожанина-квестодателя
		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
		TakeNItems(pchar, npchar.quest.gem, 8 + hrand(8));
		sTitle = npchar.city + "SCQ_manFriend";
		CloseQuestHeader(sTitle);
		break;
	//========= квесты баб ===========
	case "SCQ_woman":
		dialog.text = LinkRandPhrase("Saludos, capitán. ¿Puedes ayudarme?", "¡Capitán! ¿Puede ayudar a una mujer? Sería tan amable...", "Capitán, ayuda" + GetSexPhrase("", "") + ".");
		link.l1 = RandPhraseSimple("Estoy ocupado.", "Lo siento, " + GetAddress_FormToNPC(NPChar) + ", pero no tengo tiempo de sobra...");
		link.l1.go = "SCQ_exit";
		link.l2 = RandPhraseSimple("¿Cuál es tu problema, " + GetAddress_FormToNPC(NPChar) + "?", "Habla de tus problemas, " + GetAddress_FormToNPC(NPChar) + ". Intentaré ayudarte.");
		link.l2.go = "SCQ_woman_1";
		break;
	// выбираем квест
	case "SCQ_woman_1":
		switch (npchar.quest.SeekCap.numQuest)
		{
		case "0":
			dialog.text = "Mi esposo es comerciante, entrega mercancías a todas las colonias de alrededor. Hace tres meses se fue al mar. ¡Aún no ha regresado!";
			link.l1 = "¿Crees que le pasó algo?";
			link.l1.go = "SCQ_Hasband";
			break;
		case "1":
			dialog.text = "" + GetSexPhrase("Capitán, veo que eres un capitán valiente, un perfecto bribón", "Capitana, veo que eres una mujer fuerte, que puedes lidiar con cualquier hombre") + "...";
			link.l1 = "¿Y por qué dices eso, " + GetAddress_FormToNPC(NPChar) + "?";
			link.l1.go = "SCQ_Revenge";
			break;
		case "2":
			dialog.text = "¡Capitán, por favor ayúdame, te lo suplico! ¡Mi esposo fue capturado! ¿Puedes salvarlo?";
			link.l1 = "Espera un segundo, no lo entiendo. ¿Quién fue capturado por quién?";
			link.l1.go = "SCQ_Pirates";
			break;
		}
		break;

	// жещина разыскивает мужа-торговца
	case "SCQ_Hasband":
		dialog.text = "No sé, pero todavía espero que esté demasiado ocupado para escribirme. ¡Podría haberme enviado una carta, sabe que me preocupo por él!";
		link.l1 = "No es seguro en el mar, cualquier cosa podría suceder...";
		link.l1.go = "SCQ_Hasband_1";
		break;
	case "SCQ_Hasband_1":
		npchar.quest.SeekCap = "womanHasband"; // личный флаг ситизена на квест
		SetSeekCapCitizenParam(npchar, sti(npchar.nation));
		dialog.text = "¡Exactamente! Entiendes de lo que estoy hablando. Pareces un " + GetSexPhrase("valiente capitán", "valiente chica") + ", así que quiero pedirte que encuentres a mi esposo. Estoy dispuesta a pagarte " + FindRussianMoneyString(sti(npchar.quest.money)) + ", además te daré todas mis joyas.";
		link.l1 = "Está bien. Le contaré a tu marido sobre tus preocupaciones, si lo encuentro en el mar o en cualquier otro lugar. Dime su nombre y el nombre de su barco.";
		link.l1.go = "SCQ_Hasband_2";
		link.l2 = "No estoy interesado en una suma tan pequeña.";
		link.l2.go = "SCQ_exit_clear";
		break;
	case "SCQ_Hasband_2":
		dialog.text = "Su nombre es " + npchar.quest.SeekCap.capName + ". Navega en un " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")) + " llamado " + npchar.quest.SeekCap.shipName + "."; // belamour gen
		link.l1 = "Ya veo. Ahora debes esperar. Intenta pasar la mayor parte de tu tiempo en la iglesia, para que pueda encontrarte.";
		link.l1.go = "exit";
		//==> ставим квестодателя в церковь
		pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
		npchar.location = npchar.city + "_church";
		npchar.location.locator = "goto2";
		pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
		pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
		pchar.quest.SeekShip_Stay.Idx = npchar.index;
		NextDiag.TempNode = "SCQ_womanResult";
		sTitle = npchar.city + "SCQ_womanHasband";
		ReOpenQuestHeader(sTitle);
		AddQuestRecordEx(sTitle, "SCQ_womanHasband", "1");
		AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
		AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
		AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
	// месть отвергнутой женщины
	case "SCQ_Revenge":
		dialog.text = "" + GetSexPhrase("Lo digo, buen señor, porque quiero contratarle para hacer el trabajo al que está acostumbrado... por así decirlo.", "Quiero que me ayudes. Espero que me entiendas como mujer.") + "Un capitán me ha molestado y quiero que esté muerto.";
		link.l1 = "¿Y qué te ha hecho esa pobre alma?";
		link.l1.go = "SCQ_Revenge_1";
		break;
	case "SCQ_Revenge_1":
		dialog.text = "Este bastardo me ha engañado. Fingió estar enamorado de mí, incluso me estaba cortejando. ¡Y la razón por la que hacía todo eso era para obtener algo valioso de mi marido! Y cuando el perro consiguió su hueso, me dijo que no significaba nada... ¡que solo éramos amigos!";
		link.l1 = "Mm, ¿quizás tenía razón?";
		link.l1.go = "SCQ_Revenge_2";
		break;
	case "SCQ_Revenge_2":
		dialog.text = "¿Acaso parezco un idiota?! ¿Crees que no veo la diferencia entre un cortejo y una simple charla vacía?";
		link.l1 = "Claro que sí...";
		link.l1.go = "SCQ_Revenge_3";
		break;
	case "SCQ_Revenge_3":
		dialog.text = "¡Él me utilizó, ese bribón! ¡Nunca le perdonaré por eso!";
		link.l1 = "Sí, los hombres son así. Pero, ¿quizás puedas calmarte? No hay nada terrible en eso...";
		link.l1.go = "SCQ_Revenge_4";
		break;
	case "SCQ_Revenge_4":
		dialog.text = "¿Nada horrible? ¡Maldita sea!" + GetSexPhrase("¡Eres un moralista de alguna clase, no eres un verdadero pirata!", "Parece que nunca has estado en una situación así. ¡Oh, sí, quién se arriesgaría... y yo solo soy una mujer débil...");
		link.l1 = "Está bien. Suficiente. Simplemente deseo saber, cuán serias son tus intenciones.";
		link.l1.go = "SCQ_Revenge_5";
		break;
	case "SCQ_Revenge_5":
		dialog.text = "¡Maldita sea, " + GetSexPhrase("no sabes cómo es la venganza de una mujer rechazada", "eres una mujer y tienes que entender lo que es ser rechazada! ¡Quiero venganza ") + "!";
		link.l1 = "" + GetSexPhrase("Es cierto, nunca tuve tal experiencia", "Bueno, ella solo lloraría un poco, rompería algo de vidrio y eso sería todo.") + "...";
		link.l1.go = "SCQ_Revenge_6";
		break;
	case "SCQ_Revenge_6":
		dialog.text = "" + GetSexPhrase("Considérate afortunado. ¡La mujer rechazada y engañada en sus expectativas es una furia, un diablo en falda! Nada en el mundo podría suavizar su ira", "Y yo no soy como ella. Nada podría suavizar mi ira") + "¡\nAsí que quiero que lo mates personalmente. Y antes de que muera, debe saber quién está pagando por su muerte...";
		link.l1 = "Mm, ni siquiera sé qué decir... ¿Y cuánto estás pagando?";
		link.l1.go = "SCQ_Revenge_7";
		break;
	case "SCQ_Revenge_7":
		npchar.quest.SeekCap = "womanRevenge"; // личный флаг ситизена на квест
		SetSeekCapCitizenParam(npchar, PIRATE);
		dialog.text = "Todo lo que tengo. Te daré mis joyas y " + FindRussianMoneyString(sti(npchar.quest.money)) + ". ¿Trato?";
		link.l1 = "Estoy interesado. Dime su nombre y el nombre de su barco.";
		link.l1.go = "SCQ_Revenge_8";
		link.l2 = "No me interesa. Adiós.";
		link.l2.go = "SCQ_exit_clear";
		break;
	case "SCQ_Revenge_8":
		dialog.text = "El nombre del bribón es " + npchar.quest.SeekCap.capName + " y navega en un " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")) + " llamado " + npchar.quest.SeekCap.shipName + "."; // belamour gen
		link.l1 = "Considéralo hecho, " + GetAddress_FormToNPC(NPChar) + " Esprérame en la iglesia. Espero que te calmes un poco...";
		link.l1.go = "exit";
		//==> ставим квестодателя в церковь
		pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
		npchar.location = npchar.city + "_church";
		npchar.location.locator = "goto2";
		pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
		pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
		pchar.quest.SeekShip_Stay.Idx = npchar.index;
		NextDiag.TempNode = "SCQ_womanResult";
		sTitle = npchar.city + "SCQ_womanRevenge";
		ReOpenQuestHeader(sTitle);
		AddQuestRecordEx(sTitle, "SCQ_womanRevenge", "1");
		AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
		AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")));
		AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
		AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
		AddQuestUserData(sTitle, "sSex", GetSexPhrase("", ""));
		AddQuestUserData(sTitle, "sSex1", GetSexPhrase("", ""));
		AddQuestUserData(sTitle, "sSex2", GetSexPhrase("", ""));
		break;
	// муж женщины попал в плен к пиратам
	case "SCQ_Pirates":
		dialog.text = "Te lo explicaré. El problema es que mi esposo, que es solo un hombre común, fue capturado por piratas. ¡Estaban matando a todos y no perdonaron a nadie!";
		link.l1 = "Parece que el capitán se atrevió a resistir. De lo contrario, habrían perdonado a la tripulación.";
		link.l1.go = "SCQ_Pirates_1";
		break;
	case "SCQ_Pirates_1":
		dialog.text = "Tal vez sí, pero mi esposo es un alma inocente. Solo era un pasajero allí. Tuvo que decirles que es rico para salvar su vida. Los piratas le perdonaron, ni siquiera lo metieron en la bodega.";
		link.l1 = "¿Y cómo sabes eso?";
		link.l1.go = "SCQ_Pirates_2";
		break;
	case "SCQ_Pirates_2":
		dialog.text = "Logró enviarme una carta. Escribió que está bien y que lo tienen en una cabina, no como al resto de los prisioneros.";
		link.l1 = "¿Y qué piensas hacer? No puede seguir así. Tarde o temprano, los piratas lo calarán.";
		link.l1.go = "SCQ_Pirates_3";
		break;
	case "SCQ_Pirates_3":
		dialog.text = "¿Eres tú también un pirata? Sí, sí, lo sé... Te lo suplico, ayúdanos, ¡salva a mi esposo! Ha descrito ese barco pirata y ha escrito el nombre del capitán. ¡No te será difícil encontrarlos!";
		link.l1 = "No es tan fácil como piensas. Todos los prisioneros son el justo premio del capitán que capturó a tu marido, además tomará tiempo.";
		link.l1.go = "SCQ_Pirates_4";
		break;
	case "SCQ_Pirates_4":
		dialog.text = "¡Pero al menos puedes intentarlo! Además, tienes suficiente tiempo para buscar. Mi esposo no es un tonto y está fingiendo ser un comerciante del Viejo Mundo, así que esos piratas no le exigen monedas por ahora. Si lo liberas, te daré todo lo que tengo.";
		link.l1 = "¿Y qué tienes?";
		link.l1.go = "SCQ_Pirates_5";
		break;
	case "SCQ_Pirates_5":
		npchar.quest.SeekCap = "womanPirates"; // личный флаг ситизена на квест
		SetSeekCapCitizenParam(npchar, PIRATE);
		dialog.text = "No mucho, " + FindRussianMoneyString(sti(npchar.quest.money)) + " y todas mis joyas... ¡Pero rezaré por tu alma para siempre!";
		link.l1 = "Sí, eso realmente no es mucho... Está bien, estoy listo para ayudarte.";
		link.l1.go = "SCQ_Pirates_6";
		link.l2 = "Lo siento, pero no es suficiente para mí.";
		link.l2.go = "SCQ_exit_clear";
		break;
	case "SCQ_Pirates_6":
		dialog.text = "¡Gracias, muchísimas gracias!";
		link.l1 = "Tú me lo agradecerás, si tengo éxito, así que detente. Sería mejor que me dijeras el nombre de tu esposo y todo lo que sepas sobre esos piratas.";
		link.l1.go = "SCQ_Pirates_7";
		break;
	case "SCQ_Pirates_7":
		makearef(forName, npchar.quest.SeekCap);
		forName.nation = npchar.nation;
		forName.sex = "man";
		SetRandomNameToCharacter(forName);																																																							   // npchar.quest.SeekCap.name - имя жены ситизена
		forName.lastname = npchar.lastname;																																																							   // фамилия как и у жены есно
		dialog.text = "Mi marido se llama " + GetFullName(forName) + ". El capitán pirata es " + npchar.quest.SeekCap.capName + ", navega en el " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")) + " llamado " + npchar.quest.SeekCap.shipName + "."; // belamour gen
		link.l1 = "Ya veo. Bueno, ahora deberías esperar y confiar en que tendré éxito en mi búsqueda. Quédate en la iglesia, espera y reza ...";
		link.l1.go = "exit";
		//==> ставим квестодателя в церковь
		pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
		npchar.location = npchar.city + "_church";
		npchar.location.locator = "goto2";
		pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
		pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
		pchar.quest.SeekShip_Stay.Idx = npchar.index;
		NextDiag.TempNode = "SCQ_womanResult";
		sTitle = npchar.city + "SCQ_womanPirates";
		ReOpenQuestHeader(sTitle);
		AddQuestRecordEx(sTitle, "SCQ_womanPirates", "1");
		AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
		AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName)));		 // belamour gen
		AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
		AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		AddQuestUserData(sTitle, "sName2", GetFullName(forName));
		AddQuestUserData(sTitle, "sSex", GetSexPhrase("", ""));
		AddQuestUserData(sTitle, "sSex1", GetSexPhrase("", ""));
		break;
	// --- результаты женских квестов ---
	case "SCQ_womanResult":
		dialog.text = "¡Oh, capitán, me alegra tanto verte! Dime ahora, ¿qué tienes que contarme sobre mi tarea?";
		link.l1 = "Mm, recuérdame, " + GetAddress_FormToNPC(NPChar) + ", ¿de qué tarea estás hablando?";
		link.l1.go = "SCQ_womanResult_exit";
		switch (npchar.quest.SeekCap)
		{
		case "womanHasbandover":
			dialog.text = "¡Ah, capitán, he recibido una carta de mi esposo! Ha escrito que lo has encontrado.";
			link.l1 = "Sí, es correcto, " + GetAddress_FormToNPC(NPChar) + ". Tu marido, " + npchar.quest.SeekCap.capName + ", está bien y saludable. Está simplemente demasiado ocupado...";
			link.l1.go = "SCQR_womanHasband";
			break;
		case "womanRevengeover":
			dialog.text = "¿Qué dirías, capitán? ¿Has hecho lo que te he pedido? ¿Es el capitán " + npchar.quest.SeekCap.capName + " ¿Muerto?";
			link.l1 = "Sí, está muerto, " + GetAddress_FormToNPC(NPChar) + ". Le dije quién fue la razón de su muerte. Lo último que escuchó en su vida fue tu nombre.";
			link.l1.go = "SCQR_womanRevenge";
			break;
		case "womanPiratesover":
			dialog.text = "¡Has salvado a mi esposo! ¡Te ruego que me digas que es verdad!";
			link.l1 = "Sí, lo es. Está en mi barco ahora mismo. Puedes verlo si " + npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname + "es realmente tu esposo...";
			link.l1.go = "SCQR_womanPirates";
			break;
		}
		break;
	case "SCQ_womanResult_exit":
		switch (npchar.quest.SeekCap)
		{
		case "womanHasband":
			dialog.text = "¿Realmente has olvidado que me prometiste encontrar a mi esposo? ¡Su nombre es " + npchar.quest.SeekCap.capName + "!";
			link.l1 = "Oh, sí, claro... No lo he olvidado.";
			link.l1.go = "exit";
			break;
		case "womanRevenge":
			dialog.text = "No lo entiendo. ¿Has olvidado que debes matar a mi ofensor, un capitán llamado " + npchar.quest.SeekCap.capName + "?";
			link.l1 = "Oh, por favor, claro que no lo he hecho. Tu pedido está en proceso, por favor espera...";
			link.l1.go = "exit";
			break;
		case "womanPirates":
			dialog.text = "Jesús, capitán, ¿ha olvidado su promesa de liberar a mi esposo?";
			link.l1 = "No lo he hecho. Solo espera, " + GetAddress_FormToNPC(NPChar) + " " + npchar.lastname + ".";
			link.l1.go = "exit";
			break;
		}
		break;

	case "SCQR_womanHasband":
		dialog.text = "Oh, ¡Dios, estoy tan agradecido! Y sí, toma tu " + FindRussianMoneyString(sti(npchar.quest.money)) + ". ¡Y gracias de nuevo!";
		link.l1 = "Hum, de nada...";
		link.l1.go = "SCQ_exit";
		sTemp = "SCQ_" + npchar.index;
		pchar.quest.(sTemp).over = "yes"; // снимаем прерывание смерть горожанина-квестодателя
		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
		TakeNItems(pchar, npchar.quest.gem, 8 + hrand(8));
		sTitle = npchar.city + "SCQ_womanHasband";
		CloseQuestHeader(sTitle);
		break;
	case "SCQR_womanRevenge":
		dialog.text = "¡Excelente! Bueno, lleva tu " + FindRussianMoneyString(sti(npchar.quest.money)) + " y joyas. Adiós...";
		link.l1 = "Adiós. ";
		link.l1.go = "SCQ_exit";
		sTemp = "SCQ_" + npchar.index;
		pchar.quest.(sTemp).over = "yes"; // снимаем прерывание смерть горожанина-квестодателя
		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
		TakeNItems(pchar, npchar.quest.gem, 10 + hrand(8));
		TakeNItems(pchar, "jewelry47", rand(3));
		TakeNItems(pchar, "jewelry43", rand(3));
		TakeNItems(pchar, "jewelry41", rand(3));
		TakeNItems(pchar, "jewelry48", rand(3));
		TakeNItems(pchar, "jewelry51", rand(3));
		TakeNItems(pchar, "jewelry46", rand(3));
		TakeNItems(pchar, "jewelry49", rand(3));
		TakeNItems(pchar, "jewelry40", rand(3));
		sTitle = npchar.city + "SCQ_womanRevenge";
		CloseQuestHeader(sTitle);
		break;
	case "SCQR_womanPirates":
		dialog.text = "¡Seguro que es él! Oh Dios, capitán, estoy tan agradecido. Tome su " + FindRussianMoneyString(sti(npchar.quest.money)) + "¡Rezaré por ti todos los días de mi vida!";
		link.l1 = "Suena bien...";
		link.l1.go = "SCQ_exit";
		sld = characterFromId("womanPirates_" + npchar.City);
		RemovePassenger(pchar, sld);
		sld.lifeDay = 0;
		sTemp = "SCQ_" + npchar.index;
		pchar.quest.(sTemp).over = "yes"; // снимаем прерывание смерть горожанина-квестодателя
		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
		TakeNItems(pchar, npchar.quest.gem, 12 + hrand(8));
		sTitle = npchar.city + "SCQ_womanPirates";
		CloseQuestHeader(sTitle);
		break;
	//========= разыскиваемый капитан-работорговец ===========
	case "CitizCap": // встреча на суше
		switch (npchar.quest.SeekCap)
		{
		case "manSlave":
			dialog.text = "Saludos a mi camarada. ¿Quieres algo?" + GetSexPhrase(", amigo ", ",  chica") + "?";
			link.l1 = "Tu nombre es " + GetFullName(npchar) + ", ¿verdad?";
			link.l1.go = "CCmanSlave";
			break;
		}
		break;
	case "CCmanSlave":
		dialog.text = "¡Sí, lo eres!";
		link.l1 = "Qué lástima por ti. Te diré un nombre y será mejor que lo conozcas." + GetFullName(&characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]) + ". ¿Lo recuerdas?";
		link.l1.go = "CCmanSlave_1";
		break;
	case "CCmanSlave_1":
		dialog.text = "Mm, lo hago...";
		link.l1 = "Ahora escucha, está muy enfadado contigo, amigo. Es hora de pagar por vender a un hombre libre a la esclavitud.";
		link.l1.go = "CCmanSlave_2";
		break;
	case "CCmanSlave_2":
		dialog.text = "¿Pagar?! ¿De qué diablos estás hablando?";
		link.l1 = "Quiero decir que voy a matarte justo donde estás.";
		link.l1.go = "CCmanSlave_3";
		break;
	case "CCmanSlave_3":
		dialog.text = "¡Piénsalo, ¿para quién trabajas?! ¡Este hombre es miserable y su lugar está en la plantación de azúcar!";
		link.l1 = "Bueno, esto no es de tu incumbencia. ¡Ahora tienes que responder por lo que has hecho!";
		link.l1.go = "CCmanSlave_4";
		break;
	case "CCmanSlave_4":
		dialog.text = "¡Ho! ¡Responderé de la única manera que suelo hacerlo!";
		link.l1 = "Continúa...";
		link.l1.go = "CCmanSlave_fight";
		break;
	case "CCmanSlave_fight":
		NextDiag.TempNode = "CitizCap_inDeck_exit";
		npchar.DeckDialogNode = "CitizCap_inDeck_exit";
		LAi_group_Attack(NPChar, Pchar);
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "CitizCap_inDeck": // встреча на палубе
		dialog.text = "¿Qué quieres?";
		link.l1 = "Quiero preguntarte, ¿llevas pasajeros? ";
		link.l1.go = "CitizCap_inDeck_1";
		break;
	case "CitizCap_inDeck_1":
		dialog.text = "¿Y cómo te concierne eso?";
		link.l1 = "Solo preguntaba.";
		link.l1.go = "CitizCap_inDeck_2";
		break;
	case "CitizCap_inDeck_2":
		dialog.text = "Solo pregunto... Mira, será mejor que te largues de aquí mientras aún te doy esta oportunidad. ¡No me caes bien!";
		link.l1 = "Está bien, está bien, cálmate. Me voy...";
		link.l1.go = "exit";
		NextDiag.TempNode = "CitizCap_inDeck_exit";
		npchar.DeckDialogNode = "CitizCap_inDeck_exit";
		sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
	case "CitizCap_inDeck_exit":
		dialog.text = "Ya hemos hablado, ¡así que no me pongas a prueba!";
		link.l1 = "No lo haré.";
		link.l1.go = "exit";
		NextDiag.TempNode = "CitizCap_inDeck_exit";
		break;
	//========= разыскиваемый кэп, похитивший чужую жену ===========
	case "RapeWifeCap": // встреча на суше
		sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
		dialog.text = "¡Saludos, colega! ¿Quieres algo?";
		link.l1 = "Me gustaría saber, ¿no te llevaste a la mujer de " + XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen") + " llamada " + GetFullName(sld) + "?";
		link.l1.go = "RapeWifeCap_1";
		break;
	case "RapeWifeCap_1":
		dialog.text = "Heh, tienes razón, ¡ella está en mi camarote! Buena moza, con unas piernas estupendas por cierto... ¿Por qué preguntas?";
		link.l1 = "Amigo, esta mujer está casada. Esto está mal.";
		link.l1.go = "RapeWifeCap_2";
		break;
	case "RapeWifeCap_2":
		dialog.text = "¿Y qué? Me gusta ella y punto. ¡No permitiré que algún idiota andrajoso interfiera en nuestra relación solo porque es su esposo!";
		link.l1 = "Déjame decirte que la Hermandad no aprueba cosas como esta, y si ciertas personas se enteran de lo que hiciste, la marca negra vendrá hacia ti.";
		link.l1.go = "RapeWifeCap_3";
		break;
	case "RapeWifeCap_3":
		dialog.text = "¿Vas a empezar a sermonearme?";
		link.l1 = "Tranquilo, solo me interesaba... Adiós.";
		link.l1.go = "exit";
		NextDiag.TempNode = "RapeWifeCap_exit";
		npchar.DeckDialogNode = "RapeWifeCap_exit";
		sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
	case "RapeWifeCap_exit":
		dialog.text = "Ya hemos hablado sobre la mujer. ¡No quiero discutir el asunto de nuevo!";
		link.l1 = "Lo que sea...";
		link.l1.go = "exit";
		NextDiag.TempNode = "RapeWifeCap_exit";
		break;
	case "RapeWifeCap_inDeck": // встреча на палубе
		sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
		dialog.text = "¡Me alegra saludar a un colega en mi cubierta! ¿Qué deseas?";
		link.l1 = "Me gustaría saber si has secuestrado a una mujer de " + XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen") + " de nombre " + GetFullName(sld) + ".";
		link.l1.go = "RapeWifeCap_1";
		break;
	case "RapeWifeCap_inDeck_1":
		dialog.text = "Heh, tienes razón, ¡ella está en mi camarote! Buena moza, por cierto, ¡bonitas piernas!... ¿Por qué preguntas?";
		link.l1 = "Amigo, esta mujer está casada. Esto está mal.";
		link.l1.go = "RapeWifeCap_inDeck_2";
		break;
	case "RapeWifeCap_inDeck_2":
		dialog.text = "¿Y qué? Me gusta ella y ya está. ¡No permitiré que algún tipo harapiento se entrometa en nuestra relación solo porque es su marido!";
		link.l1 = "Permíteme decirte que los Hermanos no aprueban cosas como esta, y si ciertas personas se enteran de lo que hiciste, la marca negra será enviada hacia ti.";
		link.l1.go = "RapeWifeCap_inDeck_3";
		break;
	case "RapeWifeCap_inDeck_3":
		dialog.text = "¿Vas a empezar a sermonearme?";
		link.l1 = "Tranquilo, solo estaba mostrando interés... Adiós.";
		link.l1.go = "exit";
		NextDiag.TempNode = "RapeWifeCap_exit";
		npchar.DeckDialogNode = "RapeWifeCap_exit";
		sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
	case "RapeWifeCap_Board": // абордаж
		sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
		dialog.text = "¿Qué quieres de mí, escoria?!";
		link.l1 = "Estoy aquí por la mujer que le robaste a su marido. ¿Recuerdas " + XI_ConvertString("Colony" + npchar.quest.cribCity) + "? Su nombre es " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
		link.l1.go = "RapeWifeCap_Board_1";
		break;
	case "RapeWifeCap_Board_1":
		dialog.text = "¡Maldita sea! ¡Nunca la verás, al igual que nunca verás tus orejas!";
		link.l1 = "¡Idiota. Puedo verlos en un espejo. ¡Y voy a cortarte los tuyos!";
		link.l1.go = "RapeWifeCap_Board_2";
		break;
	case "RapeWifeCap_Board_2":
		LAi_SetCurHPMax(npchar);
		QuestAboardCabinDialogFree(); // важный метод
		LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
		pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; // флаг квеста для нпс
		pchar.GenQuest.CitizSeekCap.nation = npchar.nation;		  // нацию для нпс
		pchar.GenQuest.CitizSeekCap.sex = "woman";
		pchar.GenQuest.CitizSeekCap.ani = "towngirl";
		pchar.GenQuest.CitizSeekCap.model = "women_" + (hrand(3) + 7); // модель для нпс
		pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity;  // исходный город для нпс
		sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
		pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; // имя и фамилию для нпс
		pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
	//========= похищенная жена ===========
	case "manRapeWife_Board":
		dialog.text = "¿Quién eres tú?";
		link.l1 = "Hola. He venido por ti porque tu marido me lo pidió. Ahora eres libre y puedo llevarte a él.";
		link.l1.go = "manRapeWife_Board_1";
		break;
	case "manRapeWife_Board_1":
		dialog.text = "¿Es un sueño?! ¿Es cierto?!";
		link.l1 = "Es, " + GetAddress_FormToNPC(NPChar) + ".";
		link.l1.go = "manRapeWife_Board_2";
		break;
	case "manRapeWife_Board_2":
		dialog.text = "¡Alabado sea el Señor! Estoy listo, ¡vámonos de aquí!";
		link.l1 = "Claro, " + GetAddress_FormToNPC(NPChar) + ", prepárate para un seguro regreso con tu marido.";
		link.l1.go = "exit";
		// уберем жену из каюты
		npchar.location = "none";
		npchar.location.locator = "";
		LAi_SetPlayerType(pchar);
		AddPassenger(pchar, npchar, false);
		SetCharacterRemovable(npchar, false);
		sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
		sld.quest.SeekCap = sld.quest.SeekCap + "over"; // дополняем флаг квест до 'выполнен'
		sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Acc"));
		break;
	//========= разыскиваемый земляк-торговый кэп ===========
	case "FriendCap": // встреча на суше
		dialog.text = "¡Hola! Encantado de saludar a un colega en tierra...";
		link.l1 = TimeGreeting() + ", tengo un asunto que tratar contigo.";
		link.l1.go = "FriendCap_1";
		break;
	case "FriendCap_1":
		dialog.text = "Estoy escuchando.";
		link.l1 = "Un compañero tuyo te está buscando. Navegaban juntos y llegaron aquí desde el Viejo Mundo." + GetFullName(&characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]) + ", ¿recuerdas?";
		link.l1.go = "FriendCap_2";
		break;
	case "FriendCap_2":
		dialog.text = "¡Ja, claro que sí! ¿Y dónde vive ahora?";
		link.l1 = "En " + XI_ConvertString("Colony" + npchar.quest.cribCity + "Dat");
		link.l1.go = "FriendCap_3";
		break;
	case "FriendCap_3":
		dialog.text = "¡Gracias! Sabes... ¡pensé que eras un pirata!";
		link.l1 = "Lo soy. Más o menos. O no lo soy. Pero de todos modos, estoy de buen humor hoy, así que no tienes de qué preocuparte. Adiós.";
		link.l1.go = "exit";
		NextDiag.TempNode = "FriendCap_exit";
		npchar.DeckDialogNode = "FriendCap_exit";
		sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Acc"));
		sTemp = "SecondTimer_" + npchar.id;
		pchar.quest.(sTemp).over = "yes"; // снимаем установленный таймер на выход в море
		npchar.lifeDay = 0;
		sTemp = "SCQ_" + npchar.index;
		pchar.quest.(sTemp).over = "yes"; // снимаем прерывание смерть кэпа
		sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
		sld.quest.SeekCap = sld.quest.SeekCap + "over"; // дополняем флаг квест до 'выполнен'
		// удаляем запись в базе кэпов
		makearef(forName, NullCharacter.capitainBase);
		DeleteAttribute(forName, npchar.id);
		break;
	case "FriendCap_exit":
		dialog.text = "¿Hay algún problema? Lo siento, estoy un poco nervioso...";
		link.l1 = "Está bien, camarada.";
		link.l1.go = "exit";
		NextDiag.TempNode = "FriendCap_exit";
		break;
	case "FriendCap_inDeck": // встреча на палубе
		dialog.text = TimeGreeting() + ". ¿Qué quieres de mí? Solo soy un simple comerciante y...";
		link.l1 = "Lo sé, camarada. No te preocupes tanto, dicen que no es bueno para la salud. Tengo algunos asuntos contigo.";
		link.l1.go = "FriendCap_inDeck_1";
		break;
	case "FriendCap_inDeck_1":
		dialog.text = "¿Qué clase de negocio?";
		link.l1 = "Un amigo tuyo te está buscando. Su nombre es " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]) + "¿Lo conoces?";
		link.l1.go = "FriendCap_inDeck_2";
		break;
	case "FriendCap_inDeck_2":
		dialog.text = "Oh, ¡por fin! Eso es estupendo... Lamento mucho un saludo tan grosero, pero pensé que eras un pirata.";
		link.l1 = "Lo soy. En cierto modo. O no lo soy. Pero de todos modos, estoy de buen humor hoy, así que no tienes de qué preocuparte. Me pidieron que te entregara un mensaje y he hecho el trabajo. Tu compañero vive en " + XI_ConvertString("Colony" + npchar.quest.cribCity + "Voc") + "."; // belamour gen
		link.l1.go = "FriendCap_inDeck_3";
		break;
	case "FriendCap_inDeck_3":
		dialog.text = "¡Eso sí que es algo! Eres un hombre honorable. ¡Gracias!";
		link.l1 = "De nada. Adiós y cuídate, camarada.";
		link.l1.go = "exit";
		NextDiag.TempNode = "FriendCap_exit";
		npchar.DeckDialogNode = "FriendCap_exit";
		sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Acc"));
		npchar.quest = "outMap"; // доходит до нужной точки - и исчезает
		sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
		sld.quest.SeekCap = sld.quest.SeekCap + "over"; // дополняем флаг квест до 'выполнен'
		// удаляем запись в базе кэпов
		makearef(forName, NullCharacter.capitainBase);
		DeleteAttribute(forName, npchar.id);
		break;
	//========= разыскиваемый муж-торговец ===========
	case "HasbandCap": // встреча на суше
		dialog.text = "Hola. ¿Quieres algo?";
		link.l1 = "Tu nombre es " + GetFullName(npchar) + ", ¿verdad?";
		link.l1.go = "HasbandCap_1";
		break;
	case "HasbandCap_1":
		dialog.text = "Sí, soy yo.";
		link.l1 = "Probablemente suene estúpido, pero tu esposa me ha pedido que te diga que se preocupa por ti.";
		link.l1.go = "HasbandCap_2";
		break;
	case "HasbandCap_2":
		dialog.text = "¡Ja! Ya veo... En realidad, estaba demasiado ocupado, hay muchas ofertas lucrativas y no puedo perder posibles ingresos solo porque mi esposa se preocupa demasiado.";
		link.l1 = "Pero podrías al menos escribirle una carta y decirle que estás bien.";
		link.l1.go = "HasbandCap_3";
		break;
	case "HasbandCap_3":
		dialog.text = "Sí, tienes razón. ¡Le escribiré de inmediato! ¡Gracias por participar en nuestros asuntos familiares!";
		link.l1 = "De nada, compadre.";
		link.l1.go = "exit";
		NextDiag.TempNode = "HasbandCap_inDeck_exit";
		npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
		sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
		sTemp = "SecondTimer_" + npchar.id;
		pchar.quest.(sTemp).over = "yes"; // снимаем установленный таймер на выход в море
		npchar.lifeDay = 0;
		sTemp = "SCQ_" + npchar.index;
		pchar.quest.(sTemp).over = "yes"; // снимаем прерывание смерть кэпа
		sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
		sld.quest.SeekCap = sld.quest.SeekCap + "over"; // дополняем флаг квест до 'выполнен'
		// удаляем запись в базе кэпов
		makearef(forName, NullCharacter.capitainBase);
		DeleteAttribute(forName, npchar.id);
		break;
	case "HasbandCap_inDeck": // встреча на палубе
		dialog.text = "Buen día a ti. ¿Cómo puedo ayudarte?";
		link.l1 = "Tu nombre es " + GetFullName(npchar) + ", ¿verdad?";
		link.l1.go = "HasbandCap_inDeck_1";
		break;
	case "HasbandCap_inDeck_1":
		dialog.text = "Sí, soy yo.";
		link.l1 = "Probablemente suene estúpido, pero tu esposa me ha pedido que te diga que se preocupa por ti.";
		link.l1.go = "HasbandCap_inDeck_2";
		break;
	case "HasbandCap_inDeck_2":
		dialog.text = "¡Maldita sea! Temía que fuera el famoso cazador de recompensas que venía por mí, Steve el Tuerto es su nombre. Bueno, es bueno que me haya equivocado\nVerás, estoy tan ocupado con mi trabajo que no puedo dedicarle tiempo a ella. Tengo ofertas lucrativas todo el tiempo y no puedo rechazarlas por las preocupaciones de mi esposa.";
		link.l1 = "Tienes razón, seguro. Pero podrías al menos escribirle una carta y decirle que estás bien.";
		link.l1.go = "HasbandCap_inDeck_3";
		break;
	case "HasbandCap_inDeck_3":
		dialog.text = "Sí, tienes razón. Lo haré en el primer puerto... ¡Gracias por participar en nuestros asuntos familiares!";
		link.l1 = "De nada, camarada.";
		link.l1.go = "exit";
		NextDiag.TempNode = "HasbandCap_inDeck_exit";
		npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
		sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
		npchar.quest = "outMap"; // доходит до нужной точки - и исчезает
		sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
		sld.quest.SeekCap = sld.quest.SeekCap + "over"; // дополняем флаг квест до 'выполнен'
		// удаляем запись в базе кэпов
		makearef(forName, NullCharacter.capitainBase);
		DeleteAttribute(forName, npchar.id);
		break;
	case "HasbandCap_inDeck_exit":
		dialog.text = "Tienes mi agradecimiento, capitán...";
		link.l1 = "De nada.";
		link.l1.go = "exit";
		NextDiag.TempNode = "HasbandCap_inDeck_exit";
		break;
	//========= разыскиваемый капитан-обманщик ===========
	case "RevengeCap": // встреча на суше
		dialog.text = "Me alegra verte en esta ciudad, capitán. ¿Necesitas algo de mí?";
		link.l1 = "" + GetSexPhrase("Tú sabes, capitán... ¡Fuh, ni siquiera sé cómo decirlo!", "Sí, lo tengo.") + "";
		link.l1.go = "RevengeCap_1";
		break;
	case "RevengeCap_1":
		dialog.text = "" + GetSexPhrase("Dilo como es.", "Interesante, ¿y qué es?") + "";
		link.l1 = "Tengo una pregunta para ti. ¿Conoces a una mujer llamada " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]) + "?";
		link.l1.go = "RevengeCap_2";
		break;
	case "RevengeCap_2":
		dialog.text = "Je, sí. Tuve mala suerte al conocerla. Una muchacha tonta, te lo puedo asegurar...";
		link.l1 = "Mm... Sí, y esta tonta muchacha me ha pedido que te mate. Eso es todo....";
		link.l1.go = "RevengeCap_3";
		break;
	case "RevengeCap_3":
		dialog.text = "Disparates.";
		link.l1 = "" + GetSexPhrase("Estoy de acuerdo. Perdóneme, pero hay una recompensa por su cabeza", "No lo es. Hay una recompensa") + ". Y voy a tomarlo.";
		link.l1.go = "RevengeCap_4";
		break;
	case "RevengeCap_4":
		dialog.text = "¡Jo-jo!... ¿Me estás tomando el pelo, capitán?";
		link.l1 = "" + GetSexPhrase("No, amigo.", "¡Ni siquiera iba a hacerlo!") + "";
		link.l1.go = "RevengeCap_5";
		break;
	case "RevengeCap_5":
		dialog.text = "" + GetSexPhrase("¡No eres mi amigo, idiota! Ni siquiera puedes llamarte capitán. ¡Eres un juguete de esta necia furia!", "¡Maldita sea! ¡Un furioso ha contratado a otro! ¿Qué demonios está pasando con este mundo?") + "";
		link.l1 = "" + GetSexPhrase("Cuida tu lengua, canalla.", "La has utilizado, así que no te sorprendas de que haya decidido vengarse.") + "";
		link.l1.go = "RevengeCap_6";
		break;
	case "RevengeCap_6":
		dialog.text = "" + GetSexPhrase("¿He tocado la fibra?", "¿Solidaridad femenina?!") + "";
		link.l1 = "¡Terminemos con esto!";
		link.l1.go = "RevengeCap_7";
		break;
	case "RevengeCap_7":
		NextDiag.TempNode = "RevengeCapCap_exit";
		npchar.DeckDialogNode = "RevengeCapCap_exit";
		npchar.quest.SeekCap = "womanRevengeFight"; // флаг квеста для зачета в прерывании на убийство
		LAi_group_Attack(NPChar, Pchar);
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
	case "RevengeCapCap_exit":
		dialog.text = "Ya he hablado contigo. ¡Piérdete, imbécil!";
		link.l1 = "¿Idiota?! Muy bien entonces...";
		link.l1.go = "exit";
		NextDiag.TempNode = "RevengeCapCap_exit";
		break;
	case "RevengeCap_inDeck": // встреча на палубе
		dialog.text = "Me alegra verte a bordo, capitán. ¿Qué deseas?";
		link.l1 = "Tengo una pregunta para ti. ¿Conoces a una mujer llamada " + GetFullName(&characters[GetCharacterIndex("CiudadanoDeLaMisión_" + npchar.quest.cribCity)]) + "?";
		link.l1.go = "RevengeCap_inDeck_1";
		break;
	case "RevengeCap_inDeck_1":
		dialog.text = "Je, lo sé. Tuve mala suerte al conocerla. Una chica tonta, te lo puedo asegurar...";
		link.l1 = "Sí, y esta tonta muchacha me ha pedido que te mate.";
		link.l1.go = "RevengeCap_inDeck_2";
		break;
	case "RevengeCap_inDeck_2":
		dialog.text = "Capitán, no me hagas reír. Si no tienes ningún asunto serio conmigo, entonces te digo adiós.";
		link.l1 = "Adiós, entonces. Pero considera lo que te he dicho.";
		link.l1.go = "RevengeCap_inDeck_3";
		break;
	case "RevengeCap_inDeck_3":
		dialog.text = "¡Claro, capitán, cómo no hacerlo!";
		link.l1 = "Adiós.";
		link.l1.go = "exit";
		NextDiag.TempNode = "RevengeCapCap_inDeck_exit";
		npchar.DeckDialogNode = "RevengeCapCap_inDeck_exit";
		npchar.quest.SeekCap = "womanRevengeFight"; // флаг квеста для зачета в прерывании на убийство
		break;
	case "RevengeCapCap_inDeck_exit":
		dialog.text = "No quiero hablar más sobre este asunto, capitán. Esto es demasiado ridículo.";
		link.l1 = "Cualquier cosa que digas...";
		link.l1.go = "exit";
		NextDiag.TempNode = "RevengeCapCap_exit";
		break;
	case "RevengeCap_board": // абордаж
		dialog.text = "¿Qué diablos está pasando aquí?! ¿Por qué habéis atacado mi barco?";
		link.l1 = "Por la petición de la dama llamada " + GetFullName(&characters[GetCharacterIndex("CiudadanoDeMisión_" + npchar.quest.cribCity)]) + "¿La conoces?";
		link.l1.go = "RevengeCap_board_1";
		break;
	case "RevengeCap_board_1":
		dialog.text = "¡Qué demonios!!! No puedo creerlo...";
		link.l1 = "Tienes que hacerlo. ¿No conoces a las mujeres, compañero? Pueden morder.";
		link.l1.go = "RevengeCap_board_2";
		break;
	case "RevengeCap_board_2":
		dialog.text = "Bueno, no voy a morir así como así. Gracias por la charla, ahora he recuperado algo de fuerza.";
		link.l1 = "No te servirá de nada.";
		link.l1.go = "RevengeCap_board_3";
		break;
	case "RevengeCap_board_3":
		LAi_SetCurHPMax(npchar);
		//==> флаг квеста сменим у оригинального кэпа
		characters[sti(npchar.baseCapIdx)].quest.SeekCap = "womanRevengeFight";
		QuestAboardCabinDialogFree(); // важный метод
		LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
	//========= вызволение мужа из пиратских затрюмков =========
	case "PiratesCap_inDeck": // встреча на палубе
		sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
		dialog.text = "Me alegra verte a bordo. ¿Puedo ayudarte?";
		link.l1 = "Puedes. Estoy buscando a un hombre llamado " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
		link.l1.go = "PiratesCap_1";
		break;
	case "PiratesCap_inDeck_1":
		dialog.text = "Este hombre es mi prisionero y planeo pedir un rescate por él.";
		link.l1 = "Quiero llevármelo.";
		link.l1.go = "PiratesCap_inDeck_2";
		break;
	case "PiratesCap_inDeck_2":
		dialog.text = "Desafortunadamente, eso es imposible. Si eso es todo, te pediría que dejaras mi barco.";
		link.l1 = "Está bien, capitán, como usted diga.";
		link.l1.go = "exit";
		NextDiag.TempNode = "PiratesCapCap_exit";
		npchar.DeckDialogNode = "PiratesCapCap_exit";
		sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
	case "PiratesCapCap_exit":
		dialog.text = "Ya hemos hablado sobre mi prisionero. Nada ha cambiado.";
		link.l1 = "Ya veo...";
		link.l1.go = "exit";
		break;
	case "PiratesCap": // встреча на суше
		sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
		dialog.text = "Un placer conocerte. ¿Puedo ayudarte?";
		link.l1 = "Puede que sí. Estoy buscando a un hombre llamado " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
		link.l1.go = "PiratesCap_1";
		break;
	case "PiratesCap_1":
		dialog.text = "Este hombre es mi prisionero y planeo pedir un rescate por él.";
		link.l1 = "Quiero llevarlo.";
		link.l1.go = "PiratesCap_2";
		break;
	case "PiratesCap_2":
		dialog.text = "Lo siento, pero no es posible.";
		link.l1 = "Qué lástima...";
		link.l1.go = "exit";
		NextDiag.TempNode = "PiratesCapCap_exit";
		npchar.DeckDialogNode = "PiratesCapCap_exit";
		sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
	case "PiratesCap_Board": // абордаж
		sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
		dialog.text = "¡Maldita sea! ¿Qué diablos?!";
		link.l1 = "Necesito a tu prisionero llamado " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
		link.l1.go = "PiratesCap_Board_1";
		break;
	case "PiratesCap_Board_1":
		dialog.text = "¡Ja! ¡De ninguna manera, solo por encima de mi cadáver!";
		link.l1 = "Ya que has preguntado...";
		link.l1.go = "PiratesCap_Board_2";
		break;
	case "PiratesCap_Board_2":
		LAi_SetCurHPMax(npchar);
		QuestAboardCabinDialogFree(); // важный метод
		LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
		pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap;	   // флаг квеста для нпс
		pchar.GenQuest.CitizSeekCap.nation = npchar.nation;			   // нацию для нпс
		pchar.GenQuest.CitizSeekCap.model = "citiz_" + (rand(9) + 11); // модель для нпс
		pchar.GenQuest.CitizSeekCap.sex = "man";
		pchar.GenQuest.CitizSeekCap.ani = "man";
		pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; // исходный город для нпс
		sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
		pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; // имя и фамилию для нпс
		pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
	//========= пленный муж ===========
	case "womanPirates_Board":
		dialog.text = "¿Quién eres tú?";
		link.l1 = "Soy capitán " + GetFullName(pchar) + ". No te preocupes, estoy aquí para llevarte con tu esposa.";
		link.l1.go = "womanPirates_Board_1";
		break;
	case "womanPirates_Board_1":
		dialog.text = "¡Maldita sea, debo estar soñando!";
		link.l1 = "Te aseguro que no es el caso... Bueno, ya todo ha terminado, vámonos de aquí.";
		link.l1.go = "exit";
		// уберем мужа из каюты
		npchar.location = "none";
		npchar.location.locator = "";
		LAi_SetPlayerType(pchar);
		AddPassenger(pchar, npchar, false);
		SetCharacterRemovable(npchar, false);
		sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
		sld.quest.SeekCap = sld.quest.SeekCap + "over"; // дополняем флаг квест до 'выполнен'
		sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Acc"));
		break;

	case "plantation_slave":
		if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen" && findsubstr(npchar.id, "Slave_", 0) != -1)
		{
			dialog.text = RandPhraseSimple(RandPhraseSimple("Estoy exhausto, ayúdame.", "¡No tengo más fuerzas para vivir así!"), RandPhraseSimple("Este trabajo nos está devorando vivos.", "¡Malditos guardias no dejaron ni un pedazo de piel en mi espalda!"));
			link.l1 = RandPhraseSimple("Qué pena.", "Sí, la vida es una perra.");
			link.l1.go = "exit";
		}
		break;

	//=====================================================================================================================================
	// Warship, 25.05.11. && Jason 10.02.12 Серия миниквестов "Дело чести" -->
	//=====================================================================================================================================
	case "AffairOfHonor_1":
		LAi_CharacterDisableDialog(NPChar);

		if (LoadedLocation.type == "tavern")
		{
			// "Честь мундира".
			if (!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor"))
			{
				dialog.text = "Oh, capitán, siéntate conmigo. ¡Invito yo!";
				link.l1 = "Mi placer.";
				link.l1.go = "AffairOfHonor_CoatHonor_1";
				PChar.QuestTemp.AffairOfHonor.CoatHonor = true;
				break;
			}
		}
		else
		{
			if (NPChar.sex == "man")
			{
				// "Невольник чести".
				if (!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.HonorSlave"))
				{
					dialog.text = "Hola, capitán. Usted es un capitán, ¿no es así? ¿Incluso un capitán de la marina, tal vez?\nSí, debe ser bueno con la espada a diferencia de mi hijo inútil que va a morir mañana... ¡Por culpa de este bastardo lujurioso que puso el ojo en la dama de interés de mi hijo!";
					link.l1 = "Sí, soy capitán, y mi espada ya me ha salvado muchas veces, ¿pero qué hay del resto de tu discurso deprimente? ¿Te importaría explicarlo?";
					link.l1.go = "AffairOfHonor_HonorSlave_1";
					PChar.QuestTemp.AffairOfHonor.HonorSlave = true;
					break;
				}

				// "Красотка и пират".
				if (!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.BeautifulPirate"))
				{
					dialog.text = "Saludos, capitán. Permítame preguntar, ¿no será usted un pirata por casualidad? ¡Oh, por supuesto que no! Usted no lo es. Los piratas tienen mal aspecto, se comportan como animales y ese hedor...";
					link.l1 = "¿Tienes rencores contra los piratas?";
					link.l1.go = "AffairOfHonor_BeautifulPirate_1";
					PChar.QuestTemp.AffairOfHonor.BeautifulPirate = true;
					break;
				}

				// "Заносчивый нахал".
				if (!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Jackanapes"))
				{
					// if(NPChar.city == "PortRoyal" || NPChar.city == "Havana" || NPChar.city == "Villemstad" || NPChar.city == "FortFrance")
					//{
					//  Jason: что за чудное условие? Типа - столица? Кроме Гаваны, квест более нигде не выпадет - остальные города непригодны априори. Убираю. Неразумно ограничивать одним городом.
					dialog.text = "¡Oye, tú! Sí, tú, dime, ¿dónde están tus modales? ¿Por qué demonios estás aquí parado y molestándome? No, solo míralo, ¡qué imbécil! ¡Estoy hablando contigo! ¡Hazte a un lado! ¡Demasiados forasteros aquí!";
					link.l1 = "Calma, no quería molestarte. Te pido disculpas.";
					link.l1.go = "AffairOfHonor_Exit";
					link.l2 = "Cuida tu lengua, o te la cortaré, buen señor.";
					link.l2.go = "AffairOfHonor_Jackanapes_1";
					PChar.QuestTemp.AffairOfHonor.Jackanapes = true;
					break;
					//}
				}

				// "Волки и овцы".
				if (!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.WolvesAndSheeps"))
				{
					dialog.text = "Saludos, capitán. Tengo algo que pedirle. No se quedará al margen si es un hombre de honor.\nAsí que, vayamos al grano: un noble se alojó en nuestra taberna hace un mes. ¡Resultó ser un libertino y un bastardo! ¡Y aún más, es un asesino!";
					link.l1 = "Que yo recuerde, la pena por asesinar a un inocente es la horca. Ser un libertino y un bastardo tampoco te servirá de mucho en el tribunal. ¿Tengo razón?";
					link.l1.go = "AffairOfHonor_WolvesAndSheeps_1";
					PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps = true;
					break;
				}

				// "Трусливый фехтовалщик".
				if (!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer"))
				{
					dialog.text = "Capitán, espere, se lo ruego. Parece un espadachín hábil, mucho mejor que yo. Así que quiero pedirle que me reemplace.";
					link.l1 = "Intrigante. Continúa.";
					link.l1.go = "AffairOfHonor_CowardFencer_1";
					PChar.QuestTemp.AffairOfHonor.CowardFencer = true;
					break;
				}

				// "Божий суд".
				if (!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.GodJudgement"))
				{
					dialog.text = "Por favor, te lo ruego, ¡no te vayas! Espera... ¿No ayudarías a un pobre alma en un asunto que requiere la intervención de un valiente oficial militar como tú?\nEl caso es que tuve una disputa sobre las plantaciones de uva locales con mi vecino, por cierto, se sospecha que tiene tratos con contrabandistas. Sí, sí, y podría incluso tener algunos tratos con piratas, ¿cómo si no podría hacer tal fortuna en tan poco tiempo?\nNo tenía más que una barca hace un año y ahora quiere tomar mis viñedos, ¿me escuchas?! ¡Mis viñedos!";
					link.l1 = "Me siento mal por tus viñedos. Honestamente. Adiós.";
					link.l1.go = "exit";
					link.l2 = "Perdone, ¿pero no puede dirigirse a las autoridades locales?";
					link.l2.go = "AffairOfHonor_GodJudgement_1";
					PChar.QuestTemp.AffairOfHonor.GodJudgement = true;
					break;
				}
			}
			else
			{
				// "Навязчивый кавалер".
				if (!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Cavalier"))
				{
					dialog.text = "¡Capitán, capitán, te lo ruego! ¡Protege el honor de una inocente doncella!";
					link.l1 = "No tengo tiempo para esto, linda. Busca a alguien más...";
					link.l1.go = "AffairOfHonor_Exit";
					link.l2 = "Saludos, mi señora. ¡No tiembles así! ¿Qué ocurrió?";
					link.l2.go = "AffairOfHonor_Cavalier_1";
					PChar.QuestTemp.AffairOfHonor.Cavalier = true;
					break;
				}
			}
		}

		dialog.text = "Error. Que lo sepan los desarrolladores.";
		link.l1 = RandSwear();
		link.l1.go = "exit";
		break;

	case "AffairOfHonor_Exit":
		ChangeCharacterComplexReputation(PChar, "nobility", -2);
		NextDiag.CurrentNode = "First time";
		DialogExit();
		break;

	case "AffairOfHonor_Cavalier_1":
		dialog.text = "¡Capitán, un oficial de nuestra guarnición me ha estado acechando de la manera más inequívoca! ¡Podrías haber oído estos rumores inmundos que difunde sobre mí, tratando de avergonzarme!\n¡Ay, no tengo amigos capaces de proteger mi honesto nombre! ¡Estoy desesperada! ¡Oh, Dios, es él! ¡Ayúdame!";
		link.l1 = "No te preocupes, lo llevaré a cabo.";
		link.l1.go = "exit";
		int Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 12;
		int Scl = 30 + 2 * sti(pchar.rank);
		sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_Cavalier_Man", GetRandQuestSoldierModel(sti(NPChar.nation)), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
		// Jason: дохляки нам не нужны - делаем кулфайтера
		FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_12", "blade_14"), RandPhraseSimple("pistol6", "pistol5"), "bullet", Scl * 3);
		float Mft = MOD_SKILL_ENEMY_RATE / 20;
		sld.MultiFighter = 1.0 + Mft; // мультифайтер
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", FindNearestFreeLocator("goto"));
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, PChar, "", -1, 5);
		LAi_SetImmortal(sld, true); // Еще успеем.
		sld.dialog.filename = "Quest\ForAll_dialog.c";
		sld.dialog.currentnode = "AffairOfHonor_Cavalier_2";
		PChar.QuestTemp.AffairOfHonor.Cavalier.Started = true;
		DisableAllExits(true);
		break;

	case "AffairOfHonor_Cavalier_2":
		dialog.text = "¡Ah, ahí estás, mi señora! ¿Otro caballero, supongo? ¿Cuándo te vas a asentar? Quizás nunca... Ve a trabajar en el burdel, ese es el lugar más adecuado para ti...";
		link.l1 = "¡Oficial, cierra la boca y deja de soltar insultos o te haré callar a mi manera especial!";
		link.l1.go = "AffairOfHonor_Cavalier_2a";
		break;

	case "AffairOfHonor_Cavalier_2a":
		dialog.text = "Mm... ¿Quién eres tú? A-ah, salado por el mismo mar, el valiente capitán de una pequeña embarcación, ¿no es así? ¿Y qué piensas hacer, cachorro del mar?";
		link.l1 = "¡Esta dama es mi amiga! ¡Y te arrojaré un guantelete!";
		link.l1.go = "AffairOfHonor_Cavalier_3";
		break;

	case "AffairOfHonor_Cavalier_3":
		dialog.text = "¿Qué?! No vas a retarme por esto...";
		link.l1 = "¡Basta! Te estaré esperando cerca del faro en dos horas. ¡Y no olvides traer tu espada!";
		link.l1.go = "AffairOfHonor_Cavalier_4";
		break;

	case "AffairOfHonor_Cavalier_4":
		DialogExit();
		DeleteAttribute(npchar, "LifeDay");
		DisableAllExits(false);
		LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
		Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
		LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
		SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
		// Jason: отсрочка на 2 часа как договаривались
		SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour() + 2, false);
		ReOpenQuestHeader("AffairOfHonor");
		AddQuestRecord("AffairOfHonor", "1");
		break;

	case "AffairOfHonor_Cavalier_5":
		dialog.text = "¡Ah, lo sé todo, señor! ¡Ni siquiera entiende cuán agradecido estoy con usted! ¡Que el Señor le proteja!";
		link.l1 = "Me alegra haber podido ayudarte. ¡Buena suerte!";
		link.l1.go = "exit";
		ChangeCharacterComplexReputation(PChar, "nobility", 7);
		ChangeCharacterComplexReputation(pchar, "authority", 1);
		ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
		ChangeOfficersLoyality("good_all", 1);
		AddComplexSelfExpToScill(50, 50, 50, 50);
		AddCharacterExpToSkill(pchar, "Leadership", 300);
		AddCharacterExpToSkill(pchar, "Fortune", 100);
		npchar.lifeday = 0;
		LAi_CharacterDisableDialog(NPChar);
		break;

	case "AffairOfHonor_Cavalier_6":
		dialog.text = "Ah, eres como todos ellos, ¡déjame!";
		link.l1 = "...";
		link.l1.go = "exit";
		LAi_CharacterDisableDialog(NPChar);
		break;

	case "AffairOfHonor_HonorSlave_1":
		sTemp = "";
		if (FindLocation(NPChar.city + "_brothel") != -1)
			sTemp = "o en el burdel ";
		dialog.text = "Oh, " + GetAddress_Form(NPChar) + "... No me atrevo a tener esperanzas, pero quizás tu espada podría proteger a mi familia esta vez?\nComo dije, mi hijo no es un espadachín, pero va a un duelo a la mañana siguiente. Ah, si no fuera por su dama y el maldito honor\nPero no pudo dar un paso atrás y ahora está condenado, ¿no lo ves? Estoy desesperado, es mi único hijo y heredero, por lo tanto te pido que mates al bastardo que desafió a mi pequeño antes de que llegue el amanecer. Haré que valga la pena tu tiempo, ¡puedes contar con eso!\nEncontrarás al hombre en la taberna " + sTemp + ", donde bastardos como él pasan su tiempo libre... Te lo suplico...";
		link.l1 = "No me importa ni tú ni tu hijo. ¡Déjame ir!";
		link.l1.go = "exit";
		link.l2 = "Mm ... ¿Así nada más? Bien, veremos cómo termina esto.";
		link.l2.go = "AffairOfHonor_HonorSlave_1a";
		break;

	case "AffairOfHonor_HonorSlave_1a":
		dialog.text = "¿De verdad ayudarás a mi hijo? Oh, " + GetAddress_Form(NPChar) + "¡Rezaré por ti y tu suerte!";
		link.l1 = "No veo daño en eso... ¡Espérame!";
		link.l1.go = "AffairOfHonor_HonorSlave_2";
		break;

	case "AffairOfHonor_HonorSlave_2":
		DialogExit();
		Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 8;
		Scl = 30 + 2 * sti(pchar.rank);
		sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_HonorSlave_Man", "citiz_" + (rand(9) + 41), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
		// Jason: дохляки нам не нужны - делаем кулфайтера
		FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_04", "blade_06"), RandPhraseSimple("pistol1", "pistol5"), "bullet", Scl * 3);
		Mft = MOD_SKILL_ENEMY_RATE / 20;
		sld.MultiFighter = 1.0 + Mft; // мультифайтер
		if (rand(1) == 0 || FindLocation(NPChar.city + "_brothel") == -1 || CheckAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor"))
		{
			FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
			LAi_SetSitType(sld);
		}
		else
		{
			ChangeCharacterAddressGroup(sld, NPChar.city + "_brothel", "goto", "goto3");
			LAi_SetCitizenType(sld);
		}
		LAi_SetImmortal(sld, true); // Еще успеем.
		sld.dialog.filename = "Quest\ForAll_dialog.c";
		sld.dialog.currentnode = "AffairOfHonor_HonorSlave_3";
		SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
		PChar.QuestTemp.AffairOfHonor.HonorSlave.Started = true;
		ReOpenQuestHeader("AffairOfHonor");
		AddQuestRecord("AffairOfHonor", "3");
		break;

	case "AffairOfHonor_HonorSlave_3":
		dialog.text = "¿Qué demonios quieres de mí? Estoy descansando aquí y no quiero que me molesten. Hay muchos asientos libres y oídos disponibles, así que déjame en paz, ¡señor!";
		link.l1 = "Desafortunadamente, tendrás que hacer una pausa en tu descanso hasta tiempos mejores.";
		link.l1.go = "AffairOfHonor_HonorSlave_3a";
		break;

	case "AffairOfHonor_HonorSlave_3a":
		dialog.text = "¡¿Qué?! ¿Y quién eres tú para decirme qué hacer?!";
		link.l1 = "¿Te has olvidado de mí, eh? ¡Pero yo te recuerdo! Y mi punto es que canallas como tú están envenenando nuestro mundo solo con su presencia.";
		link.l1.go = "AffairOfHonor_HonorSlave_3b";
		break;

	case "AffairOfHonor_HonorSlave_3b":
		dialog.text = "¿Ah?! ¡Marinero, parece que estás demasiado borracho! ¡Es la primera vez que te veo! ¡Pero no voy a ignorar tu comportamiento! ¡Esta es tu última oportunidad para salvar tu miserable vida! ¡Haz tus disculpas ahora, arenque hinchado, y olvidaré tu insolente discurso!";
		link.l1 = "¡Doy excusas solo a hombres honorables, no a cerdos inmundos!";
		link.l1.go = "AffairOfHonor_HonorSlave_4";
		break;

	case "AffairOfHonor_HonorSlave_4":
		dialog.text = "¡¿Qué demonios?! ¿Buscas problemas, piojo de letrina?";
		link.l1 = "¡Te cerraré la maldita garganta con tus palabras, rata! Te esperaré cerca del faro en dos horas y no olvides llevar esa chatarra oxidada que llevas en el cinturón.";
		link.l1.go = "AffairOfHonor_HonorSlave_5";
		break;

	case "AffairOfHonor_HonorSlave_5":
		dialog.text = "¡Ja! ¡Estaré allí!";
		link.l1 = "¡Hasta pronto!";
		link.l1.go = "AffairOfHonor_HonorSlave_6";
		break;

	case "AffairOfHonor_HonorSlave_6":
		DialogExit();
		LAi_CharacterDisableDialog(NPChar);
		Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
		LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
		// Jason: отсрочка на 2 часа как договаривались
		SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour() + 2, false);
		AddQuestRecord("AffairOfHonor", "3_1");
		break;

	case "AffairOfHonor_HonorSlave_7":
		dialog.text = "Oh, ¡eres tú! Estás vivo, lo que significa que...";
		link.l1 = "Sí, lo estoy, y tu hijo no necesita batirse en duelo mañana por la mañana...";
		link.l1.go = "AffairOfHonor_HonorSlave_8";
		break;

	case "AffairOfHonor_HonorSlave_8":
		dialog.text = "¡Qué día tan hermoso! ¡Debería ir y contarle a mi esposa las buenas nuevas!\nCapitán, el destino mismo te ha enviado a ayudarme. Aquí, toma estas monedas y acepta la gratitud de nuestra familia.";
		link.l1 = "¡Gracias!";
		link.l1.go = "exit";
		iTemp = 50 + hrand(5) * 10;
		TakeNItems(pchar, "gold_dublon", iTemp);
		Log_Info("Has recibido " + FindRussianDublonString(iTemp) + "");
		PlaySound("interface\important_item.wav");
		ChangeCharacterComplexReputation(pchar, "authority", 1);
		ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
		AddComplexSelfExpToScill(50, 50, 50, 50);
		AddCharacterExpToSkill(pchar, "Leadership", 200);
		AddCharacterExpToSkill(pchar, "Fortune", 50);
		npchar.lifeday = 0;
		LAi_CharacterDisableDialog(NPChar);
		break;

	case "AffairOfHonor_HonorSlave_9":
		dialog.text = "¡Lárgate, asesino de niños!";
		link.l1 = "...";
		link.l1.go = "exit";
		LAi_CharacterDisableDialog(NPChar);
		break;

	case "AffairOfHonor_BeautifulPirate_1":
		dialog.text = "¿Yo? Gracias a Dios, estoy bien, pero mi hermana no tiene tanta suerte. Ella sirve en una taberna. \nHay un corsario que visita el lugar a menudo, un tipo muy peligroso. ¡Pirata! Su nave ha estado en el viaje por una semana no menos. El hombre está bebiendo, amenazando a la gente y promete matar a todos los que traten de razonar con él. Lo peor es que mi hermana me dijo que él se jacta de robarla y llevarla quién sabe dónde si ella no cumple sus sucios deseos. \n¡No sé qué hacer! A las autoridades no les importa una simple sirvienta y ciudadanos pacíficos como yo temen a este corsario. ¡Ayúdanos a tratar con él, por favor!";
		link.l1 = "No tengo tiempo para calmar a los borrachos en las tabernas. Habla con el comandante, le pagan para resolver tales asuntos.";
		link.l1.go = "exit";
		link.l2 = "Hum, ¿un corsario amenazante? Está bien, me encargaré de él.";
		link.l2.go = "AffairOfHonor_BeautifulPirate_1a";
		break;

	case "AffairOfHonor_BeautifulPirate_1a":
		dialog.text = "¡Ah, gracias, capitán! Estoy seguro de que te escuchará como un marinero escucha a otro marinero. ¡Haz que deje en paz a mi hermana para siempre! No somos ricos, pero te pagaremos lo suficiente por tus molestias.";
		link.l1 = "Está bien, está bien... Estoy en camino para resolver tus problemas. ¡Espérame!";
		link.l1.go = "AffairOfHonor_BeautifulPirate_1_1";
		break;

	case "AffairOfHonor_BeautifulPirate_1_1":
		DialogExit();
		NextDiag.CurrentNode = "AffairOfHonor_BeautifulPirate_r";
		npchar.lifeday = 3;
		Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 12;
		Scl = 25 + 3 * sti(pchar.rank);
		Mft = MOD_SKILL_ENEMY_RATE / 15;
		sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_BeautifulPirate_Man", "mercen_" + (rand(9) + 1), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
		// Jason: дохляки нам не нужны - делаем кулфайтера
		FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_10", "blade_13"), RandPhraseSimple("pistol6", "pistol4"), "bullet", Scl * 3);
		sld.MultiFighter = 1.0 + Mft; // мультифайтер
		FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
		ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
		LAi_SetSitType(sld);
		LAi_SetImmortal(sld, true); // Еще успеем.
		sld.dialog.filename = "Quest\ForAll_dialog.c";
		sld.dialog.currentnode = "AffairOfHonor_BeautifulPirate_2";
		SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
		PChar.QuestTemp.AffairOfHonor.BeautifulPirate.Started = true;
		ReOpenQuestHeader("AffairOfHonor");
		AddQuestRecord("AffairOfHonor", "5");
		break;

	case "AffairOfHonor_BeautifulPirate_r":
		dialog.text = "¿Y qué? ¿Has hablado con ese pirata? ¿Nos dejará en paz?";
		link.l1 = "Espera un poco. Estoy en ello.";
		link.l1.go = "exit";
		NextDiag.TempNode = "AffairOfHonor_BeautifulPirate_r";
		break;

	case "AffairOfHonor_BeautifulPirate_2":
		dialog.text = "¿Qué quieres? ¿No ves que estoy descansando aquí?";
		link.l1 = "Bueno, bueno... He aquí, el gran señor de las jarras de cerveza, ladrón de doncellas y la tormenta de este pequeño pueblo en carne y hueso, ¿verdad? ¿Y serías tan valiente fuera del pueblo? Cerca del faro, un duelo, en dos horas?";
		link.l1.go = "AffairOfHonor_BeautifulPirate_2a";
		DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
		SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;

	case "AffairOfHonor_BeautifulPirate_2a":
		dialog.text = "¡Oh-ho-ho! ¿Estás pretendiendo ser un héroe? Como sea, camarada, estoy de buen humor hoy, así que te perdono. ¡Ve y cómprame unas pintas de cerveza!";
		link.l1 = "No soy tu amigo. ¿Debo repetirme para un idiota como tú? ¿Serías tan valiente para presentarte a un duelo como eres valiente para aparecer en la taberna?";
		link.l1.go = "AffairOfHonor_BeautifulPirate_3";
		break;

	case "AffairOfHonor_BeautifulPirate_3":
		dialog.text = "¿Me estás desafiando?! ¿Qué te pasa? ¿Te aburriste de la vida, quieres morir, perro sarnoso? ¡Bien, si realmente quieres eso, caminaré hasta el faro, te arrancaré las tripas y luego destruiré también esta maldita taberna!";
		link.l1 = "Hablar es barato, las espadas no lo son, ¡así que recuerda traer una!";
		link.l1.go = "AffairOfHonor_BeautifulPirate_4";
		break;

	case "AffairOfHonor_BeautifulPirate_4":
		DialogExit();
		LAi_CharacterDisableDialog(NPChar);
		Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
		LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
		SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
		break;

	case "AffairOfHonor_BeautifulPirate_5":
		dialog.text = "¿Y qué? ¿Has hablado con ese pirata? ¿Nos dejará en paz? Mi hermana me dijo que salió de la taberna y no volvió...";
		link.l1 = "He tenido. El tipo fue un poco grosero, pero mis argumentos fueron bastante razonables y persuasivos. Tu hermana no tiene nada de qué temer ahora.";
		link.l1.go = "AffairOfHonor_BeautifulPirate_6";
		break;

	case "AffairOfHonor_BeautifulPirate_6":
		dialog.text = "¿Esto... se acabó? ¿Podemos respirar libremente ahora? ¡Gracias, capitán! Y dónde... ¿dónde está ese sinvergüenza??";
		link.l1 = "Él... está en su barco. Ha decidido dejar este pueblo lo antes posible.";
		link.l1.go = "AffairOfHonor_BeautifulPirate_7";
		break;

	case "AffairOfHonor_BeautifulPirate_7":
		dialog.text = "¡Le has hecho un gran servicio a los ciudadanos de esta colonia! ¡Toma, recibe esta recompensa por tu ayuda! Es bastante modesta, pero obtendrás respeto de todos mis amigos y, créeme, tengo muchos de ellos.";
		link.l1 = "¡Mis agradecimientos! Buena suerte para ti y tu hermana. Le deseo que se case con un hombre honorable. ¡Adiós!";
		link.l1.go = "exit";
		iTemp = 50 + hrand(5) * 10;
		AddMoneyToCharacter(pchar, iTemp * 100);
		ChangeCharacterComplexReputation(pchar, "authority", 1);
		ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
		AddComplexSelfExpToScill(50, 50, 50, 50);
		AddCharacterExpToSkill(pchar, "Leadership", 200);
		AddCharacterExpToSkill(pchar, "Fortune", 50);
		npchar.lifeday = 0;
		LAi_CharacterDisableDialog(NPChar);
		break;

	case "AffairOfHonor_Jackanapes_1":
		dialog.text = "¿Oh, de verdad? ¿Y cómo planeas detenerme?";
		link.l1 = "Con mi espada, por supuesto, esa es la única manera adecuada para un cerdo insolente como tú.";
		link.l1.go = "AffairOfHonor_Jackanapes_1_1";
		break;

	case "AffairOfHonor_Jackanapes_1_1":
		dialog.text = "¡Espléndido! Te estaré esperando cerca del faro en dos horas.";
		link.l1 = "¡Genial!  Estaré allí seguro.";
		link.l1.go = "AffairOfHonor_Jackanapes_1_2";
		break;

	case "AffairOfHonor_Jackanapes_1_2":
		DialogExit();
		PChar.QuestTemp.AffairOfHonor.Jackanapes.Started = true;
		Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
		LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
		NPChar.id = "AffairOfHonor_Jackanapes_Man";
		LAi_SetImmortal(NPChar, true); // Еще успеем.
		SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
		// Jason: отсрочка на 2 часа как договаривались
		SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour() + 2, false);
		ReOpenQuestHeader("AffairOfHonor");
		AddQuestRecord("AffairOfHonor", "7");
		break;

	case "AffairOfHonor_Jackanapes_2":
		dialog.text = "¡Fuera de mi camino, cobarde!";
		link.l1 = "...";
		link.l1.go = "exit";
		LAi_CharacterDisableDialog(NPChar);
		break;

	case "AffairOfHonor_WolvesAndSheeps_1":
		dialog.text = "Capitán, el bastardo no es tan simple, Tom, mi viejo amigo, murió en un duelo contra él, acusado de hacer trampas en el juego! Era inocente, lo juro. Pero el gobernador dijo que no había crimen en ese maldito duelo.";
		link.l1 = "Hm...  Todo es culpa de tu amigo. Jugar con cartas puede acabar mal para tu salud.";
		link.l1.go = "AffairOfHonor_WolvesAndSheeps_2";
		break;

	case "AffairOfHonor_WolvesAndSheeps_2":
		dialog.text = "¿Sí? Ya ha habido cuatro fulleros en las últimas dos semanas en nuestro pueblo. ¿Y todos ellos intentaban engañar a nuestro noble? ¿Qué dirías sobre eso? Mi punto es que este noble es el fullero mismo. Si no me crees, entonces ve y compruébalo por ti mismo.";
		link.l1 = "¿Quieres jugar con él? No, no me gusta apostar. Ni hablar.";
		link.l1.go = "exit";
		link.l2 = "Supongo que haré eso... Algo está muy mal aquí.";
		link.l2.go = "AffairOfHonor_WolvesAndSheeps_3";
		break;

	case "AffairOfHonor_WolvesAndSheeps_3":
		dialog.text = "Capitán, mis amigos y yo hemos reunido una suma para pagar al hombre que revelará a ese noble y vengarnos de él por todas sus fechorías. Estaré esperando en la ciudad para darte tu recompensa una vez que el trabajo esté hecho.";
		link.l1 = "Haré eso si lo que dices es cierto.";
		link.l1.go = "AffairOfHonor_WolvesAndSheeps_4";
		break;

	case "AffairOfHonor_WolvesAndSheeps_4":
		DialogExit();
		PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps.Started = true;
		npchar.lifeday = 3;
		// Jason: дохляки нам не нужны - делаем кулфайтера
		Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 10;
		Scl = 30 + 2 * sti(pchar.rank);
		Mft = MOD_SKILL_ENEMY_RATE / 20;
		sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_WolvesAndSheeps_Man", "citiz_" + (rand(9) + 1), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
		FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_08", "blade_09"), RandPhraseSimple("pistol1", "pistol5"), "bullet", Scl * 3);
		sld.MultiFighter = 1.0 + Mft; // мультифайтер
		sld.skill.Fortune = 1;
		sld.Default = NPChar.city + "_tavern";
		sld.Default.group = "sit";
		sld.Default.ToLocator = "sit_front1";
		LAi_SetSitType(sld);
		ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_base1");
		LAi_SetImmortal(sld, true); // Еще успеем.
		sld.dialog.filename = "Quest\ForAll_dialog.c";
		sld.dialog.currentnode = "AffairOfHonor_WolvesAndSheeps_5";
		SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
		ReOpenQuestHeader("AffairOfHonor");
		AddQuestRecord("AffairOfHonor", "9");
		break;

	case "AffairOfHonor_WolvesAndSheeps_5":
		dialog.text = "¡Mis respetos, señor! Veo a un hombre noble y quizás... ¿un jugador? ¿Te apetece una partida?";
		link.l1 = "¡Claro! Hablemos de la apuesta. ¿Qué tal 50 monedas?";
		link.l1.go = "AffairOfHonor_WolvesAndSheeps_6";
		break;

	case "AffairOfHonor_WolvesAndSheeps_6":
		if (sti(PChar.money) < 200)
		{
			dialog.text = "¿Probablemente me estás tomando el pelo? ¡No los tienes!";
			link.l1 = "Tienes razón...";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_5";
		}
		else
		{
			dialog.text = "La apuesta es irrelevante, vamos a jugar, esa es la mejor parte. Casi he olvidado cómo lucen las cartas, por culpa de los idiotas locales.";
			link.l1 = "Bueno, comencemos.";
			link.l1.go = "exit";
			PChar.QuestTemp.friend_in_tavern = NPChar.id;
			AddDialogExitQuest("alc");
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
			NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_7";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		}
		break;

	case "AffairOfHonor_WolvesAndSheeps_7":
		dialog.text = "Entonces, la apuesta es de 50 monedas.";
		link.l1 = "... ";
		link.l1.go = "AffairOfHonor_WolvesAndSheeps_8";
		PChar.GenQuest.Cards.npcharIdx = NPChar.index;
		PChar.GenQuest.Cards.iRate = 50;
		PChar.GenQuest.Cards.SitType = true;
		break;

	case "AffairOfHonor_WolvesAndSheeps_8":
		NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_9";
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LaunchCardsGame();
		break;

	case "AffairOfHonor_WolvesAndSheeps_9":
		dialog.text = "Espera un poco, ¿qué es esto?.. ¡Imposible! ¡Señor, usted es un tramposo! ¡Devuélvame mis monedas!";
		link.l1 = "Tienes que tener razones sólidas para culparme,  " + GetAddress_FormToNPC(NPChar) + "Más te vale dispararles ahora mismo, ¡o será un duelo!";
		link.l1.go = "AffairOfHonor_WolvesAndSheeps_10";
		break;

	case "AffairOfHonor_WolvesAndSheeps_10":
		dialog.text = "¿Ah, así nomás? ¡Bien, un duelo entonces! ¡Hoy, en dos horas, cerca del faro!";
		link.l1 = "¡Trato hecho!";
		link.l1.go = "AffairOfHonor_WolvesAndSheeps_11";
		break;

	case "AffairOfHonor_WolvesAndSheeps_11":
		AddDialogExitQuest("exit_sit");
		DialogExit();
		LAi_CharacterDisableDialog(NPChar);
		Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
		LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
		// Jason: отсрочка на 2 часа как договаривались
		SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour() + 2, false);
		break;

	case "AffairOfHonor_WolvesAndSheeps_12":
		dialog.text = "¿Alguna noticia, capitán?";
		link.l1 = "Eras correcto, también me acusaron de hacer trampa, así que tuve que cortar al bastardo en un duelo.";
		link.l1.go = "AffairOfHonor_WolvesAndSheeps_13";
		break;

	case "AffairOfHonor_WolvesAndSheeps_13":
		dialog.text = "¿Ves ahora? ¡Yo sabía eso! ¡Muchas gracias de mi parte y de mis amigos! Aquí, toma tu recompensa, capitán.";
		link.l1 = "Gracias.";
		link.l1.go = "exit";
		iTemp = 50 + hrand(5) * 10;
		AddMoneyToCharacter(pchar, iTemp * 100);
		ChangeCharacterComplexReputation(pchar, "authority", 1);
		ChangeCharacterComplexReputation(PChar, "nobility", 2);
		ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
		AddComplexSelfExpToScill(50, 50, 50, 50);
		AddCharacterExpToSkill(pchar, "Leadership", 200);
		AddCharacterExpToSkill(pchar, "Fortune", 200);
		npchar.lifeday = 0;
		LAi_CharacterDisableDialog(NPChar);
		break;

	case "AffairOfHonor_CowardFencer_1":
		dialog.text = "¿Te conté que vine aquí para solicitar una posición de tutor de esgrima? ¿No? Entonces, el gobernador está buscando un tutor para su sobrino y me viene como anillo al dedo. Conozco los fundamentos de este arte, aunque nunca lo he intentado en la práctica. Casi tenía el trabajo en el bolsillo, pero resultó que el comerciante se ha enfrentado a un problema, un rufián de aspecto peligroso lo está amenazando. El gobernador me dio la orden de resolver este asunto para poner a prueba mis habilidades profesionales.";
		link.l1 = "Hazlo entonces. Adiós.";
		link.l1.go = "exit";
		link.l2 = "¿Y qué quiere este granuja del mercader y para qué me necesitas a mí?";
		link.l2.go = "AffairOfHonor_CowardFencer_1_1";
		break;

	case "AffairOfHonor_CowardFencer_1_1":
		dialog.text = "Pensé que el hombre era un mercenario y que siempre se puede llegar a un acuerdo con los mercenarios. Viejas deudas o lo que sea... Pero el hombre estaba serio en sus intenciones de seguir presionando al comerciante. Quería pedirte que ayudes al comerciante y a mí salvándolo del mercenario y cumpliendo las órdenes del gobernador. Realmente necesito este puesto y no puedo deshacerme del mercenario por mi cuenta. Por favor, ayúdame y te daré cada moneda que he ahorrado o me veré obligado a abandonar la ciudad con vergüenza.";
		link.l1 = "Está bien, está bien, te ayudaré... 'maestro de esgrima'.";
		link.l1.go = "AffairOfHonor_CowardFencer_1_2";
		break;

	case "AffairOfHonor_CowardFencer_1_2":
		DialogExit();
		npchar.lifeday = 3;
		// Jason: дохляки нам не нужны - делаем кулфайтера
		Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 15;
		Scl = 30 + 3 * sti(pchar.rank);
		Mft = MOD_SKILL_ENEMY_RATE / 15;
		sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_CowardFencer_Man", "mercen_" + (rand(7) + 23), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
		FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_06", "blade_10"), RandPhraseSimple("pistol4", "pistol6"), "bullet", Scl * 3 + 70);
		sld.MultiFighter = 1.0 + Mft; // мультифайтер
		LAi_SetCitizenType(sld);
		ChangeCharacterAddressGroup(sld, NPChar.city + "_store", "goto", "goto3");
		LAi_SetImmortal(sld, true); // Еще успеем.
		sld.dialog.filename = "Quest\ForAll_dialog.c";
		sld.dialog.currentnode = "AffairOfHonor_CowardFencer_2";
		SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
		PChar.QuestTemp.AffairOfHonor.CowardFencer.Started = true;
		ReOpenQuestHeader("AffairOfHonor");
		AddQuestRecord("AffairOfHonor", "11");
		break;

	case "AffairOfHonor_CowardFencer_2":
		dialog.text = "¿Qué quieres? ¡¿No ves que estoy ocupado?!";
		link.l1 = "¿Molestando a algún respetable comerciante y haciendo un escándalo?";
		link.l1.go = "AffairOfHonor_CowardFencer_3";
		DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
		SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;

	case "AffairOfHonor_CowardFencer_3":
		dialog.text = "¡Bah! ¿Otro protector? Será más barato pagarme a mí, en lugar de contratar guardias todos los días. No me gusta mucho el trabajo de matar en comparación con cobrar las deudas, así que si eres tan héroe, ven al faro y nos pondremos a prueba en un duelo. Y si no lo eres, entonces no te metas conmigo de nuevo.";
		link.l1 = "¡Trato hecho! Te estaré esperando allí.";
		link.l1.go = "AffairOfHonor_CowardFencer_4";
		break;

	case "AffairOfHonor_CowardFencer_4":
		DialogExit();
		Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
		LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
		SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
		LAi_CharacterDisableDialog(NPChar);
		break;

	case "AffairOfHonor_CowardFencer_4_1":
		dialog.text = "Parece que eres incluso más cobarde que yo...";
		link.l1 = "Sí, lo soy.";
		link.l1.go = "exit";
		LAi_CharacterDisableDialog(NPChar);
		break;

	case "AffairOfHonor_CowardFencer_5":
		dialog.text = "¿Alguna novedad, capitán?";
		link.l1 = "El mercenario está muerto. ¿Espero que el puesto sea tuyo ahora?";
		link.l1.go = "AffairOfHonor_CowardFencer_6";
		break;

	case "AffairOfHonor_CowardFencer_6":
		dialog.text = "Oh, ¡capitán, mis agradecimientos! ¡Toma tu recompensa y yo informaré a nuestro gobernador!";
		link.l1 = "Adiós... maestro.";
		link.l1.go = "exit";
		ChangeCharacterComplexReputation(pchar, "authority", 1);
		ChangeCharacterComplexReputation(PChar, "nobility", 2);
		ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
		AddComplexSelfExpToScill(60, 60, 60, 60);
		AddCharacterExpToSkill(pchar, "Leadership", 200);
		AddCharacterExpToSkill(pchar, "Fortune", 200);
		npchar.lifeday = 0;
		LAi_CharacterDisableDialog(NPChar);
		GiveItem2Character(pchar, "chest");
		Log_Info("Has recibido un cofre lleno de doblones");
		PlaySound("interface\important_item.wav");
		break;

	case "AffairOfHonor_CoatHonor_1":
		LAi_CharacterEnableDialog(NPChar);
		NextDiag.TempNode = "AffairOfHonor_CoatHonor_2";
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		PChar.QuestTemp.friend_in_tavern = npchar.id;
		AddDialogExitQuest("alc");
		break;

	case "AffairOfHonor_CoatHonor_2":
		dialog.text = "¿Uno más?";
		link.l1 = "Abajo los fondos.";
		link.l1.go = "AffairOfHonor_CoatHonor_2_1";
		break;

	case "AffairOfHonor_CoatHonor_2_1":
		dialog.text = "¡Y más!";
		link.l1 = "¡Espera un poco! ¿A dónde te apresuras?";
		link.l1.go = "AffairOfHonor_CoatHonor_2_2";
		break;

	case "AffairOfHonor_CoatHonor_2_2":
		dialog.text = "¡Al diablo con las preguntas! ¡Bebe!";
		link.l1 = "Está bien, pero tal vez me cuentes más tarde qué te ha pasado.";
		link.l1.go = "AffairOfHonor_CoatHonor_2_3";
		break;

	case "AffairOfHonor_CoatHonor_2_3":
		dialog.text = "¿De verdad estás interesado? ¡Entonces escucha mientras todavía puedo hablar! No podré hablar en unos días porque estaré muerto... ¡Sí, muerto! Y la culpa es del ron. Mucho ron y este oficial, aparentemente traído por el diablo sobre mi cabeza.\nSeguro que no pelearía con el mejor espadachín de nuestra guarnición y de toda la ciudad si estuviera sobrio o al menos no tan borracho. ¿Pero qué hago ahora? ¡Estoy condenado, perdido y estoy muerto! Soy un tonto estúpido...";
		link.l1 = "Sí, eso fue demasiado tonto. Pero probablemente te comportarás con más inteligencia en el futuro... en caso de que sobrevivas al duelo, por supuesto. Adiós.";
		link.l1.go = "AffairOfHonor_CoatHonor_Exit";
		link.l2 = "Embriagarse tampoco es la mejor opción, oficial. Estoy seguro de que existe una solución para este problema.";
		link.l2.go = "AffairOfHonor_CoatHonor_2_4";
		break;

	case "AffairOfHonor_CoatHonor_2_4":
		dialog.text = "¿Qué clase de solución? ¿Desertar y perder mi reputación y mi uniforme de oficial? ¿O suicidarme para evitar que me corten como a un cerdo? ¿Cuál será tu consejo?";
		link.l1 = "Ni uno de ellos. Te ayudaré e intentaré evitar que tu oponente te cause algún daño antes de la hora de tu duelo. ¿Dónde puedo encontrarlo?";
		link.l1.go = "AffairOfHonor_CoatHonor_2_5";
		break;

	case "AffairOfHonor_CoatHonor_2_5":
		dialog.text = "¿Hablas en serio? ¡¿Lo harás?! ¡Oh, te juro que te recompensaré generosamente!\nSe le puede encontrar en la ciudad. Su amante vive aquí, todos los oficiales han oído hablar de ella, pero por desgracia su dirección es desconocida... Así que mi apuesta es que puedes encontrarlo allí también.";
		link.l1 = "Eso es suficiente. Espérame aquí. Iré a charlar con este... 'mejor espadachín'.";
		link.l1.go = "AffairOfHonor_CoatHonor_3";
		break;

	case "AffairOfHonor_CoatHonor_Exit":
		DialogExit();
		AddDialogExitQuest("exit_sit");
		NextDiag.CurrentNode = NextDiag.TempNode;
		break;

	case "AffairOfHonor_CoatHonor_3":
		AddDialogExitQuest("exit_sit");
		NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_Next";
		DialogExit();
		SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 2, false);
		PChar.QuestTemp.AffairOfHonor.CoatHonor.Started = true;
		PChar.QuestTemp.AffairOfHonor.CoatHonor.CityId = NPChar.city;
		PChar.QuestTemp.AffairOfHonor.CoatHonor.NeedGenerateDuelMan = true;
		ReOpenQuestHeader("AffairOfHonor");
		AddQuestRecord("AffairOfHonor", "13");
		npchar.lifeday = 2;
		break;

	case "AffairOfHonor_CoatHonor_Next":
		dialog.text = "¿Tiene alguna noticia para mí, señor? ¿Buenas o... no tan buenas?";
		link.l1 = "Aún no tengo noticias. Espera aquí. Todo estará bien.";
		link.l1.go = "exit";
		NextDiag.TempNode = "AffairOfHonor_CoatHonor_Next";
		break;

	case "AffairOfHonor_CoatHonor_Final":
		dialog.text = "¿Tiene alguna noticia para mí, señor? ¿Buenas o... no son tan buenas?";
		link.l1 = "Se acabó. Tu potencial adversario ya no podrá hacer daño a nadie más... Ahora estás a salvo. Pero espero que aprendas de esta lección y no seas agresivo con personas que no conoces.";
		link.l1.go = "AffairOfHonor_CoatHonor_Final_1";
		break;

	case "AffairOfHonor_CoatHonor_Final_1":
		dialog.text = "¿No me estás tomando el pelo, verdad? Yo... Estoy realmente agradecido, " + GetAddress_Form(NPChar) + "¡Aquí, toma todo lo que tengo. Este es mi salario, llévatelo todo!\n¿Una lección, dices? ¡Sí, maldita sea, tienes razón! ¡No volverá a suceder nunca más! Eso te lo prometo, y gracias una vez más por darme otra oportunidad.";
		link.l1 = "Está bien entonces. Adiós, oficial...";
		link.l1.go = "AffairOfHonor_CoatHonor_Final_2";
		break;

	case "AffairOfHonor_CoatHonor_Final_2":
		DialogExit();
		npchar.lifeday = 0;
		NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_End";
		TakeNItems(pchar, "purse3", 1);
		Log_Info("Has recibido un monedero con doblones");
		PlaySound("interface\important_item.wav");
		ChangeCharacterComplexReputation(pchar, "authority", 1);
		ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
		AddComplexSelfExpToScill(50, 50, 50, 50);
		AddCharacterExpToSkill(pchar, "Leadership", 200);
		AddCharacterExpToSkill(pchar, "Fortune", 50);
		break;

	case "AffairOfHonor_CoatHonor_End":
		dialog.text = "¡Gracias de nuevo, " + GetAddress_Form(NPChar) + ", por tu ayuda!";
		link.l1 = "De nada...";
		link.l1.go = "exit";
		NextDiag.TempNode = "AffairOfHonor_CoatHonor_End";
		break;

	case "AffairOfHonor_CoatHonor_4":
		dialog.text = "¡Oye, qué demonios! ¿Qué haces en las cámaras de mi dama? ¡Aléjate de aquí o te sacaré a la fuerza!";
		link.l1 = "¡Camino donde quiera y no voy a darte cuentas por tal comportamiento! ¿Por la fuerza? ¡Inténtalo entonces!";
		link.l1.go = "AffairOfHonor_CoatHonor_5";
		break;

	case "AffairOfHonor_CoatHonor_5":
		dialog.text = "¡Qué insolencia! ¡Insólita desfachatez! ¡Señor, realmente está equivocado! ¡Abandone esta casa inmediatamente o juro que lamentará haber nacido!";
		link.l1 = "¡Hablar es barato! Te arrepentirás de esto, no yo, " + GetAddress_FormToNPC(NPChar) + "¡ ";
		link.l1.go = "AffairOfHonor_CoatHonor_6";
		break;

	case "AffairOfHonor_CoatHonor_6":
		dialog.text = "¿De veras? ¡Entonces ten cuidado! Si te mato en esta casa, será un asesinato. Así que tu muerte no manchará mi nombre, los hombres de honor resuelven tales asuntos cerca de un faro.\n¡Te desafío, " + GetAddress_Form(NPChar) + ", ¡hombre insolente! ¡Responderás por tus palabras! Entonces, ¿un duelo en dos horas?";
		link.l1 = "Claro, " + GetAddress_FormToNPC(NPChar) + " tipo audaz.";
		link.l1.go = "AffairOfHonor_CoatHonor_7";
		break;

	case "AffairOfHonor_CoatHonor_7":
		dialog.text = "Entonces asegúrate de estar allí a la hora adecuada. Todavía tienes tiempo para encargar un réquiem a nuestro sacerdote.";
		link.l1 = "¿Un réquiem para ti? No vales ni un solo peso. ¡Nos vemos cerca del faro!";
		link.l1.go = "AffairOfHonor_CoatHonor_8";
		break;

	case "AffairOfHonor_CoatHonor_8":
		DialogExit();
		Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
		LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
		// Jason: отсрочка на 2 часа как договаривались
		SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour() + 2, false);
		DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
		SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_9";
		LAi_SetWarriorType(npchar); // 140313
		break;

	case "AffairOfHonor_CoatHonor_9":
		dialog.text = "¡Piérdete!";
		link.l1 = "...";
		link.l1.go = "exit";
		NextDiag.TempNode = "AffairOfHonor_CoatHonor_9";
		break;

	case "AffairOfHonor_GodJudgement_1":
		dialog.text = "¿Te refieres al gobernador? ¡Ja! 'El juicio de Dios' es lo que el gobernador me dijo en respuesta a mis quejas. ¡Duelo! ¿Qué te parece? Soy solo un tranquilo y pacífico plantador, no un bandido o un luchador.\n¡Esto será un asesinato, no un duelo! Y tú, sin duda, eres mejor en estas cosas que yo. Por lo tanto, te pido que actúes como mi representante para el próximo duelo. Créeme, no me quedaré en deuda.";
		link.l1 = "¿Cuándo es el duelo?";
		link.l1.go = "AffairOfHonor_GodJudgement_1_1";
		break;

	case "AffairOfHonor_GodJudgement_1_1":
		dialog.text = "Hoy antes de la medianoche cerca del faro. ¿Me ayudarás?";
		link.l1 = "Está bien, te ayudaré. ¡Espérame en el pueblo!";
		link.l1.go = "AffairOfHonor_GodJudgement_1_2";
		break;

	case "AffairOfHonor_GodJudgement_1_2":
		DialogExit();
		PChar.QuestTemp.AffairOfHonor.GodJudgement.Started = true;
		PChar.QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest = true;
		PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId = NPChar.city;
		Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
		LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
		SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
		SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
		npchar.lifeday = 3;
		// Jason: дохляки нам не нужны - делаем кулфайтера
		Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 12;
		Scl = 30 + 2 * sti(pchar.rank);
		Mft = MOD_SKILL_ENEMY_RATE / 20;
		sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man", "citiz_" + (rand(9) + 41), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
		FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_05", "blade_07"), RandPhraseSimple("pistol1", "pistol5"), "bullet", Scl * 3);
		sld.MultiFighter = 1.0 + Mft; // мультифайтер
		LAi_SetImmortal(sld, true);	  // Еще успеем.
		sld.dialog.filename = "Quest\ForAll_dialog.c";
		ReOpenQuestHeader("AffairOfHonor");
		AddQuestRecord("AffairOfHonor", "15");
		break;

	case "AffairOfHonor_GodJudgement_2":
		dialog.text = "¿Dime qué ha sucedido allí? ¿Ganamos... lo siento, ganaste?";
		link.l1 = "Estoy seguro de que te interesará saber que hubo una emboscada. Quizás, tu vecino decidió asegurarse invitando a unos cuantos representantes más en lugar de uno, y todos ellos eran bandidos experimentados. Afortunadamente, soy un espadachín experimentado.";
		link.l1.go = "AffairOfHonor_GodJudgement_3";
		break;

	case "AffairOfHonor_GodJudgement_3":
		dialog.text = "¡Qué bastardo! Ahora, supongo, nuestro gobernador no tendrá razones para rechazar mi petición de arrestar al sinvergüenza. ¡Gracias! Toma tu recompensa y tengo que ir a la residencia.";
		link.l1 = "Adiós.";
		link.l1.go = "exit";
		npchar.lifeday = 0;
		TakeNItems(pchar, "purse3", 1);
		TakeNItems(pchar, "purse" + (hrand(2) + 1), 1);
		Log_Info("Has recibido monederos con doblones");
		PlaySound("interface\important_item.wav");
		ChangeCharacterComplexReputation(pchar, "authority", 1);
		ChangeCharacterComplexReputation(PChar, "nobility", 3);
		ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
		AddComplexSelfExpToScill(50, 50, 50, 50);
		AddCharacterExpToSkill(pchar, "Leadership", 200);
		AddCharacterExpToSkill(pchar, "Fortune", 50);
		LAi_CharacterDisableDialog(NPChar);
		break;

	// Диалоги до боя -->
	case "AffairOfHonor_BeforeFight_1":
		dialog.text = "Es divertido jugar sin bichos, ya que esas perras son difíciles de encontrar.";
		link.l1 = "Relájate, informaré a los desarrolladores.";
		link.l1.go = "AffairOfHonor_BeforeFight_2";

		switch (AffairOfHonor_GetCurQuest())
		{
		case "Cavalier":
			dialog.text = "Ah, ahí estás. Estos son mis amigos y segundos. ¿Empezamos?";
			link.l1 = "¡Estoy a su servicio!";
			link.l1.go = "AffairOfHonor_BeforeFight_2";
			break;

		case "HonorSlave":
			dialog.text = "Todos están reunidos. ¿Estás listo?";
			link.l1 = "¡Sí, podemos empezar!";
			link.l1.go = "AffairOfHonor_BeforeFight_2";
			break;

		case "BeautifulPirate":
			dialog.text = "¡Por fin! Ya estaba pensando que tendría que caminar un camino tan largo para nada... Terminemos esto rápido, he dejado una copa de ron y una moza caliente en la taberna.";
			link.l1 = "¡Estoy seguro de que ya no necesitarás ninguno de los dos!";
			link.l1.go = "AffairOfHonor_BeforeFight_2" break;

		case "Jackanapes":
			dialog.text = "¿Así que has decidido venir? ¡Finalmente! ¡Entonces comencemos!";
			link.l1 = "No te apresures así, podrías caer sobre una espada.";
			link.l1.go = "AffairOfHonor_BeforeFight_2" break;

		case "WolvesAndSheeps":
			dialog.text = "Y estos son mis segundos, señor. ¡Ahora prepárate para morir!";
			link.l1 = "Después de ti.";
			link.l1.go = "AffairOfHonor_BeforeFight_2" break;

		case "CowardFencer":
			dialog.text = "Aquí estamos. ¡Prepárate la espada, señor!";
			link.l1 = "¡Con gusto, que gane el mejor hombre!";
			link.l1.go = "AffairOfHonor_BeforeFight_2" break;

		case "CoatHonor":
			dialog.text = "Excelente, todos han llegado... ¡Comencemos, señor!";
			link.l1 = "¡Bailemos!";
			link.l1.go = "AffairOfHonor_BeforeFight_2" break;

		case "GodJudgement":
			dialog.text = "¿Y quién eres tú? No pareces un ciudadano común, compadre...";
			link.l1 = "¿Entonces? ¡¿Tengo un duelo concertado contigo?!";
			link.l1.go = "AffairOfHonor_BeforeFight_2_1" break;
		}
		break;

	case "AffairOfHonor_BeforeFight_2_1":
		dialog.text = "¡Ja! ¡Un duelo! Parece que eres nuestro cliente. Chicos, vamos a apuñalarlo y simplemente ir por nuestra recompensa. ¡Destrúyelo!";
		link.l1 = "¿Una emboscada? Qué patético, necesitarás mucho más que esto para derrotarme...";
		link.l1.go = "AffairOfHonor_BeforeFight_2";
		break;

	case "AffairOfHonor_BeforeFight_2":
		LAi_LocationFightDisable(LoadedLocation, false);
		AddDialogExitQuest("MainHeroFightModeOn");
		PChar.Quest.AffairOfHonor_KillChar.win_condition.l1 = "NPC_Death";
		PChar.Quest.AffairOfHonor_KillChar.win_condition.l1.character = "AffairOfHonor_" + AffairOfHonor_GetCurQuest() + "_Man";
		PChar.Quest.AffairOfHonor_KillChar.function = "AffairOfHonor_KillChar";
		if (hrand(1) == 0 && AffairOfHonor_GetCurQuest() != "CowardFencer" && AffairOfHonor_GetCurQuest() != "CoatHonor")
		{
			PChar.QuestTemp.AffairOfHonor.FightWithHelpers = true;
			Log_TestInfo("Seconds will fight");
		}
		// В квесте "Божий суд" всегда нападают.
		if (AffairOfHonor_GetCurQuest() == "GodJudgement")
		{
			Log_TestInfo("Global massacre");
			sld = CharacterFromID("AffairOfHonor_Helper_1");
			LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
			LAi_SetImmortal(sld, false);
			sld = CharacterFromID("AffairOfHonor_Helper_2");
			LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
			LAi_SetImmortal(sld, false);
			iTemp = hrand(3);
			if (AffairOfHonor_GetCurQuest() == "GodJudgement")
			{
				for (i = 0; i < iTemp; i++)
				{
					sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(9) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true, "soldier"));
					SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
					ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
					LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				}
			}
		}
		LAi_Group_MoveCharacter(NPChar, "AffairOfHonor_Enemies");
		LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);

		DialogExit();
		break;
	// <-- Диалоги до боя.

	// Диалоги после боя -->
	case "AffairOfHonor_AfterFight_1":
		if (CheckAttribute(PChar, "QuestTemp.AffairOfHonor.FightWithHelpers"))
		{
			dialog.text = "¿Acaso piensas que te dejaremos matar a nuestro amigo y escapar así como así? ¡A las armas!";
			link.l1 = "¡Debería haber esperado esto de un miserable bastardo como tú!";
			link.l1.go = "AffairOfHonor_AfterFight_FightWithHelpers";
			break;
		}
		if (AffairOfHonor_GetCurQuest() == "CoatHonor")
		{
			dialog.text = "Capitán, el honor está restaurado, has ganado. Pero permíteme darte un buen consejo: deja la ciudad y no te aparezcas por aquí durante un tiempo...";
			link.l1 = "¿Y cuál es el problema??";
			link.l1.go = "AffairOfHonor_AfterFight_2_1";
		}
		else
		{
			dialog.text = "Todo fue por honor y ahora vayamos a buscar a nuestro amigo.";
			link.l1 = "Claro, no te detendré...";
			link.l1.go = "AffairOfHonor_AfterFight_2";
		}
		break;

	case "AffairOfHonor_AfterFight_2_1":
		dialog.text = "El problema es que has matado a un ordenanza de nuestro comandante. Era un mal hombre y nadie lamentará su muerte... pero al comandante realmente le gustaba y nunca te perdonará por la muerte de su amigo.";
		link.l1 = "Gracias por el consejo, seguramente lo seguiré. Adiós.";
		link.l1.go = "AffairOfHonor_AfterFight_2";
		break;

	case "AffairOfHonor_AfterFight_2":
		DialogExit();
		LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
		LAi_ActorGoToLocation(CharacterFromID("AffairOfHonor_Helper_2"), "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
		if (AffairOfHonor_GetCurQuest() == "CoatHonor")
		{
			ChangeCharacterComplexReputation(PChar, "nobility", 5);
		}
		break;

	case "AffairOfHonor_AfterFight_FightWithHelpers":
		iTemp = hrand(3);
		AddDialogExitQuest("MainHeroFightModeOn");
		sld = CharacterFromID("AffairOfHonor_Helper_1");
		LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
		LAi_SetImmortal(sld, false);
		sld = CharacterFromID("AffairOfHonor_Helper_2");
		LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
		LAi_SetImmortal(sld, false);
		if (AffairOfHonor_GetCurQuest() == "GodJudgement")
		{
			for (i = 0; i < iTemp; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(9) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true, "soldier"));
				SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
				ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
				LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
			}
		}
		LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);

		DialogExit();
		break;
		// <-- Диалоги после боя.
		//=====================================================================================================================================
		// <-- Серия миниквестов "Дело чести".
		//=====================================================================================================================================
	}
}

void SetSeekCapCitizenParam(ref npchar, int iNation)
{
	//создаем кэпов
	int Rank = sti(pchar.rank)+5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCitizCap_"+npchar.index, "", "man", "man", Rank, iNation, -1, true, "soldier"));
	switch (npchar.quest.SeekCap)
	{
		case "NM_battle": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "NM_battleCap";
			sld.DeckDialogNode = "NM_battleDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*8000+sti(pchar.rank)*500;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
		
		case "NM_prisoner": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "NM_prisonerCap";
			sld.DeckDialogNode = "NM_prisonerCap";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+sti(pchar.rank)*600;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
		
		case "NM_peace": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "war";
			SetCaptanModelByEncType(sld, "war");
			sld.dialog.currentnode = "NM_peaceCap";
			sld.DeckDialogNode = "NM_peaceCap";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*6000+sti(pchar.rank)*400;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
	
		case "manSlave": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "CitizCap";
			sld.DeckDialogNode = "CitizCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "manRapeWife": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "RapeWifeCap";
			sld.DeckDialogNode = "RapeWifeCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "manFriend": 
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "FriendCap";
			sld.DeckDialogNode = "FriendCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanHasband": 
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "HasbandCap";
			sld.DeckDialogNode = "HasbandCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanRevenge": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "RevengeCap";
			sld.DeckDialogNode = "RevengeCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanPirates": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "PiratesCap";
			sld.DeckDialogNode = "PiratesCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
	}
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	// в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest.SeekCap.capId = sld.id //Id искомого кэпа
	npchar.quest.SeekCap.capName = GetFullName(sld); //имя искомого кэпа
	npchar.quest.SeekCap.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.SeekCap.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	//npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1)*1000)+(sti(pchar.rank)*500); //вознаграждение
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.quest.SeekCap = npchar.quest.SeekCap; //запишем кэпу флаг квеста
	sld.quest.nation = iNation; //запомним базовую нацию кэпа
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придёт
	//Log_TestInfo("Разыскиваемый кэп " + sld.id + " вышел из: " + sld.city + " и направился в: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, где ошивается квестодатель
	npchar.quest.Qcity = sld.city;
	//==> на карту
	sld.mapEnc.type = "trade";
	// выбор типа кораблика на карте
	switch (npchar.quest.SeekCap)
	{
		case "NM_battle":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "NM_prisoner":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "NM_peace":	 sld.mapEnc.worldMapShip = "ranger";	  break;
		case "manSlave":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manRapeWife":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manFriend":	 sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanHasband": sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanRevenge": sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "womanPirates": sld.mapEnc.worldMapShip = "Galleon_red"; break;
	}
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.SeekCap.shipTapeName) + " '" + npchar.quest.SeekCap.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city)) + 5; // дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	// прерывание на смерть кэпа
	string sTemp = "SCQ_" + sld.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	// прерывание на смерть квестодателя
	sTemp = "SCQ_" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).function = "SCQ_CitizenIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	pchar.quest.(sTemp).CitizenId = npchar.id;
	// заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "citizen"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = npchar.id; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = sld.quest.cribCity + "SCQ_" + npchar.quest.SeekCap; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "SCQ_" + npchar.quest.SeekCap; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
	NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
	NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
	NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string SelectNB_battleText()
{
	string sText;
	switch (hrand(5))
	{
	case 0:
		sText = "Un bastardo ha seducido a mi hermana debido a su ingenuidad, y la dejó después de divertirse con ella. No podía dejarlo irse sin castigo y tuve que desafiarlo. Se asustó y huyó en su barco" break;
	case 1:
		sText = "Un bastardo deshonroso ha perdido una enorme suma en los juegos de azar y ha huido en su barco" break;
	case 2:
		sText = "Un canalla me ha pedido prestado dinero y cuando no estaba en casa pagó su deuda con monedas falsas a mi criado. Se esconde en algún lugar de su barco" break;
	case 3:
		sText = "Un canalla ha intentado deshonrarme a ojos del gobernador, pero su mentira fue revelada y ese bastardo ha huido en su nave" break;
	case 4:
		sText = "Por error mío, contraté a un pícaro como contable. Cometió una gran atrocidad, ha comprado una nave y ha huido" break;
	case 5:
		sText = "Mi antiguo vigilante robó una caja llena de joyas de los aposentos de mi esposa y huyó. Ahora creo que tiene bastantes monedas para comprar una nave" break;
	}
	return sText;
}

void SelectNB_prisonerText(ref npchar)
{
	switch (hrand(5))
	{
	case 0:
		npchar.quest.text = "Un bastardo ha seducido a mi hermana debido a su ingenuidad y la dejó después de divertirse con ella. No podía dejarlo salir sin castigo y tuve que desafiarlo. Sin embargo, el desgraciado contrato al constructor de barcos y huyó lejos a mar abierto";
		npchar.quest.text1 = " deshonró a una mujer y huyó cobardemente";
		break;
	case 1:
		npchar.quest.text = "Un bastardo deshonroso perdió una gran suma en juegos de azar y huyó, se ofreció para trabajar como artillero y se ha escapado";
		npchar.quest.text1 = " perdió todo su dinero en juegos de azar y no quiere pagar la deuda ";
		break;
	case 2:
		npchar.quest.text = "Un canalla me pidió prestado dinero y cuando no estaba en casa pagó la deuda con monedas falsas a mi criado. Ahora está trabajando en una nave como intendente y se esconde de mí";
		npchar.quest.text1 = " falsificador que ha cometido un delito";
		break;
	case 3:
		npchar.quest.text = "Un canalla ha tratado de deshonrarme a ojos del gobernador y su mentira fue revelada. Pero ese bastardo fue contratado como médico en un barco y se ha escapado";
		npchar.quest.text1 = " calumniador e intrigante que ha tratado de deshonrar a un buen ciudadano";
		break;
	case 4:
		npchar.quest.text = "Por error contraté a un pícaro como contable. Cometió una gran atrocidad, ahora sirve en una nave como intendente y se esconde de mí";
		npchar.quest.text1 = " se le culpa de fraude y malversación";
		break;
	case 5:
		npchar.quest.text = "Mi antiguo vigilante robó una caja llena de joyas del gabinete de mi esposa y huyó. Consiguió el puesto de oficial de abordaje en un barco";
		npchar.quest.text1 = " un ladrón común, su lugar está en la cárcel. Ha robado las joyas de su jefe en su trabajo";
		break;
	}
}

void SelectNB_peaceText(ref npchar)
{
	switch (hrand(5))
	{
	case 0:
		npchar.quest.text = "mi viejo amigo, que era un amigo cercano en el Viejo Mundo";
		npchar.quest.text1 = "él es tu viejo amigo";
		break;
	case 1:
		npchar.quest.text = "un hombre, que básicamente era mi padre";
		npchar.quest.text1 = "tu eras un padre para el";
		break;
	case 2:
		npchar.quest.text = "mi hermanastro, que dejó el viejo mundo en su juventud";
		npchar.quest.text1 = "usted es su hermanastro";
		break;
	case 3:
		npchar.quest.text = "un hombre que me ayudó en el Viejo Mundo";
		npchar.quest.text1 = "le has ayudado mucho";
		break;
	case 4:
		npchar.quest.text = "el marido de mi hermana que era mi amigo en el Viejo Mundo";
		npchar.quest.text1 = "eres el esposo de su hermana";
		break;
	case 5:
		npchar.quest.text = "mi amigo, que era mi hermano de armas en el Viejo Mundo";
		npchar.quest.text1 = "eran hermanos de armas";
		break;
	}
}

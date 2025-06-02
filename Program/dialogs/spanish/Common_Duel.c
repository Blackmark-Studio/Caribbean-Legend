// navy 26.07.06
// генератор дуэлей...
// в диалоге НПС делаем линк с проверкой флага оскорбления... по нему переход на "outraged"
// если НПС сделал что-то ГГ (продажа фальшивки) или ГГ наехал на НПС, вешаем на него флаг.
// для некоторых, например ПГГ, можно делать переход сразу на вызов: "let_s_duel"
void ProcessDuelDialog(ref NPChar, aref Link, aref NextDiag)
{
	int iHour;
	string sLocation;

	// флаг убираем
	DeleteAttribute(NPChar, "Outrage");
	switch (Dialog.CurrentNode)
	{
	case "outraged":
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + RandPhraseSimple("¿Cómo te atreves a insultarme, canalla?!", "¡Estas palabras te costarán mucho!"), RandPhraseSimple("Insultaste mi honor, " + GetAddress_Form(NPChar) + "¡Y pagarás por eso!", "¿Cómo te atreves? ¡Retira tus palabras inmediatamente!"));

		// это такая засада.. чтобы читали текст :)
		MakeRandomLinkOrderTwo(link,
							   NPCharRepPhrase(pchar,
											   RandPhraseSimple("¡¿Ha?! ¡Ni siquiera quiero manchar mi espada con tu sangre!", "¡¿Ha?! ¡Ni siquiera quiero manchar mi espada con tu sangre!"),
											   RandPhraseSimple("Estoy siempre a su servicio.", "No voy a elegir las palabras al hablar con la chusma.")),
							   "outraged_1",
							   NPCharRepPhrase(pchar, RandSwear() + RandPhraseSimple("¡No lo decía en serio!", "Encendí..."),
											   RandPhraseSimple("Eso fue un error. Lo lamento.", "Te tomé por otra persona, " + GetAddress_FormToNPC(NPChar) + ". Por favor, perdóname.")),
							   "change_mind");
		break;

	case "outraged_1":
		Dialog.Text = NPCharRepPhrase(NPChar, RandPhraseSimple("¡Te cortaré las orejas!", "¡Arrancaré tu corazón!"), RandPhraseSimple("¡Espero que escucharé tus excusas o no puedo garantizar que me controlaré!", "¿Te das cuenta de lo que significa... lo haces?"));

		MakeRandomLinkOrderTwo(link,
							   NPCharRepPhrase(pchar, RandSwear() + RandPhraseSimple("Espero que tu sable sea tan rápido como tu lengua.", "Mi espada hablará por mí."),
											   RandPhraseSimple("¡Te reto a un duelo!", "¡Es una cuestión de honor!")),
							   "let_s_duel",
							   NPCharRepPhrase(pchar,
											   RandPhraseSimple("Creo que aún no estoy preparado.", "¡Piensa, no deberíamos emocionarnos! ¡Sólo son palabras!"),
											   RandPhraseSimple("Me acordé de que me están esperando. Mis bendiciones...", "¡Ah! Parece que mi barco saldrá a navegar. Adios.")),
							   "change_mind");
		break;

	case "let_s_duel":
		// проверка на начатые дуэли.
		if (CheckAttribute(PChar, "questTemp.duel.Start") && sti(PChar.questTemp.duel.Start))
		{
			Dialog.Text = "Primero, arregla tus asuntos con los demás, y luego hablaremos.";
			if (PChar.questTemp.duel.enemy == NPChar.id)
			{
				Dialog.Text = "Ya hemos llegado a un acuerdo.";
			}
			link.l1 = RandSwear() + "Oh, ¿cómo podría olvidar...?";
			link.l1.go = "exit";
			break
		}
		// может отказаться.
		if (rand(100) < 30)
		{
			Dialog.Text = RandPhraseSimple("¿Duelo?! Piérdete, no vales la pena perder tiempo contigo.", "¿Duelo? ¡No mereces ese honor! ¡Pierde de vista!");
			link.l1 = RandPhraseSimple("Está bien...", "Supongo que puedo esperar...");
			link.l1.go = "exit";
			/**/
			// можно дать возможность драться полюбому :)
			if (rand(100) < 30)
			{
				link.l1 = RandPhraseSimple("¿Crees eso? ¡No estés tan seguro, bastardo!!!", "¿¡Ah, de verdad?! ¡Vamos a ver de qué color es tu sangre!");
				link.l1.go = "fight_right_now";
			}
			/**/
			break;
		}

		// согласен.
		Dialog.Text = RandPhraseSimple("¿El duelo, dices? Me parece bien. Las espadas y las pistolas serán nuestras armas.", "¿Puedes siquiera sostener una espada?");
		link.l1 = RandPhraseSimple("Rogarás por misericordia, de rodillas.", "¡Te estrangularé con mis propias manos, canalla!");
		link.l1.go = "land_duel";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			Dialog.Text = RandPhraseSimple(Dialog.Text + "¡O podemos zarpar y ver quién es quién!", "¿El duelo?!! ¡Ja, te aplastaré como a un insecto! ¡Elige cómo te gustaría morir!");
			link.l2 = RandPhraseSimple("En el mar, soy el mejor que hay.", "¡Mi barco hundirá fácilmente tu vieja tina!");
			link.l2.go = "sea_duel";
		}
		link.l3 = "Cambié de opinión...";
		link.l3.go = "change_mind";
		break;

	// дуэль на подводных лодках :))))
	case "sea_duel":
		Dialog.Text = RandPhraseSimple("No veo tu barco en el puerto...", "¡Pierde hasta que encuentres una vieja tina de mierda al menos!");
		link.l1 = RandPhraseSimple("Mi error...", "Entonces te dejo.");
		link.l1.go = "exit";
		if (pchar.location.from_sea == GetCurrentTown() + "_town")
		{
			Dialog.Text = "Está bien, te estaré esperando en la salida de la cala...";
			link.l1 = "No te haré esperar demasiado tiempo.";

			pchar.questTemp.Duel.enemy = NPChar.id;
			pchar.questTemp.Duel.Sea_Location = Islands[GetCharacterCurrentIsland(PChar)].id;
			AddDialogExitQuestFunction("Duel_Sea_Prepare");
		}

		break;

	// на суше
	case "land_duel":
		iHour = 1 + rand(2);
		if (GetTime() > 4.0 && GetTime() < 17.0)
		{
			//			iHour = MakeInt(18.0 - GetTime()) + rand(2); //раскоментировать для дуэлей только по ночам
		}
		pchar.questTemp.Duel.WaitTime = iHour;
		Dialog.Text = RandSwear() + RandPhraseSimple("¡Desenvaina tu espada, y veremos de qué color es tu sangre!", "Bueno, si tienes un deseo de muerte...");
		link.l1 = RandPhraseSimple("Será mejor que vayamos a algún lugar sin demasiados testigos. Conozco justo el lugar adecuado más allá de las puertas de la ciudad. Encontrémonos allí en " + iHour + " horas.", "Sostén tus caballos. Tales cosas se resuelven mejor sin testigos. Entra " + iHour + "  horas hasta la entrada a la ciudad.");
		link.l1.go = "fight_off_town";
		link.l2 = RandPhraseSimple("Bueno, si quieres morir tanto...", "¡Maldición! ¡Te ayudaré a ver el Infierno con tus propios ojos!");
		link.l2.go = "fight_right_now";
		link.l3 = "Cambié de opinión...";
		link.l3.go = "change_mind";

		if (rand(1))
		{
			Dialog.Text = RandSwear() + RandPhraseSimple("Creo que será mejor que pasemos por las puertas de la ciudad. Te estaré esperando allí en " + pchar.questTemp.Duel.WaitTime + " horas. ¡No te demores!", "Este no es el mejor lugar para resolver disputas. Sería mejor que saliéramos de la ciudad. En " + pchar.questTemp.Duel.WaitTime + " horas estaré allí.");
			link.l1 = RandPhraseSimple("¡No mereces ese honor! ¡Defiéndete!", "¡No tengo tiempo! ¡Desenvaina el acero!");
			link.l1.go = "fight_right_now";
			link.l2 = RandPhraseSimple("Está bien, vamos a dar un paseo.", "Probablemente tengas razón. Nos encontramos más allá de las puertas.");
			link.l2.go = "fight_off_town_prep";
		}
		break;

	// предложение "пойдём выйдем" рассматривается
	case "fight_off_town":
		Dialog.Text = RandPhraseSimple("¡No mereces ese honor! ¡Defiéndete!", "¡No tengo tiempo! ¡Justo aquí y ahora!");
		link.l1 = RandPhraseSimple("Bueno, si tanto quieres morir...", "¡Maldita sea! ¡Te ayudaré a ver el Infierno con tus propios ojos!");
		link.l1.go = "fight_right_now";
		if (rand(1))
		{
			Dialog.Text = RandPhraseSimple("Está bien, vamos a dar un paseo.", "Probablemente tengas razón. Nos encontramos más allá de las puertas.");
			link.l1 = RandPhraseSimple("Te estaré esperando allí.", "No demores.");
			link.l1.go = "fight_off_town_prep";
		}
		break;

	// что ж, пойдём выйдем
	case "fight_off_town_prep":
		SaveCurrentQuestDateParam("questTemp.Duel.StartTime");
		PChar.questTemp.duel.Start = true;
		PChar.questTemp.duel.enemy = NPChar.id;
		sLocation = GetCurrentTown();
		if (sLocation != "")
		{
			// где?
			sLocation += "_ExitTown";
			pchar.questTemp.duel.place = sLocation;

			Locations[FindLocation(sLocation)].DisableEncounters = true;
			// приходит ко времени.
			pchar.quest.duel_move_opponent2place.win_condition.l1 = "Location";
			pchar.quest.duel_move_opponent2place.win_condition.l1.location = pchar.questTemp.duel.place;
			pchar.quest.duel_move_opponent2place.function = "Duel_Move_Opponent2Place";
			// на случай, если не дождется, часа вполне достаточно
			SetTimerConditionParam("duel_move_opponentBack", "Duel_Move_OpponentBack", 0, 0, 0, sti(GetTime() + 0.5) + sti(pchar.questTemp.Duel.WaitTime) + 1, false);
			pchar.quest.duel_move_opponentBack.function = "Duel_Move_OpponentBack";
			if (CheckAttribute(NPChar, "CityType"))
			{
				DeleteAttribute(NPChar, "City"); // чтоб не было ругани с нацией
				DeleteAttribute(NPChar, "CityType");
				if (!CheckAttribute(NPChar, "PGGAi"))
				{
					if (!CheckAttribute(NPChar, "LifeDay"))
						npchar.LifeDay = 0;
					npchar.LifeDay = sti(npchar.LifeDay) + 3; // чтоб до дуэли не помер
				}
			}
		}
		NextDiag.CurrentNode = "let_s_duel";
		DialogExit();
		break;

	// последнее слово перед боем
	case "talk_off_town":
		Dialog.Text = "Entonces, ¿estás listo?";
		link.l1 = "Sí. ¡Veamos quién es el mejor hombre!";
		link.l1.go = "fight_right_now";
		link.l2 = "No, decidí traerte las disculpas. Estaba equivocado, me encendí.";
		link.l2.go = "change_mind";
		if (rand(100) < 20)
		{
			Dialog.Text = RandPhraseSimple("Oye, escucha, he estado pensando en ello y ahora veo que estaba equivocado. Mis disculpas.", "¡Maldita sea! ¡Es todo ese maldito ron! Mis disculpas, " + GetSexPhrase("hermano", "hermana") + ".");
			link.l1 = NPCharRepPhrase(pchar, RandPhraseSimple("¡No, solo tu sangre puede darme satisfacción ahora!", "¡Desenfunda el acero y deja de ser una niña llorona!"), RandPhraseSimple("¡No! ¡Exijo satisfacción!", "¡Eres una deshonra para tu familia! ¡Desenvaina tu espada!"));
			link.l1.go = "fight_right_now";
			link.l2 = NPCharRepPhrase(pchar, RandPhraseSimple("De acuerdo, lo admito. Nos hemos exaltado un poco.", "¡Quién lleva la cuenta entre amigos!"), RandPhraseSimple("Probablemente tengas razón. No deberíamos derramar sangre por cosas tan insignificantes.", "¡Mi generosidad no conoce límites! ¡Estás perdonado!"));
			link.l2.go = "peace";
		}
		NextDiag.TempNode = npchar.BackUp.DialogNode;
		pchar.questTemp.Duel.End = true;
		break;

	// дуэли быть!
	case "fight_right_now":
		PChar.questTemp.duel.enemy = NPChar.id;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "fight_right_now_1":
		PChar.questTemp.duel.enemy = NPChar.id;
		PChar.questTemp.duel.enemyQty = rand(2) + 1;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	// передумал, э... не хорошо ;)
	case "change_mind":
		if (CheckAttribute(pchar, "questTemp.Duel.End"))
			LAi_SetWarriorType(NPChar);
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + RandPhraseSimple("¡Entonces piérdete!", "Lárgate entonces, antes de que cambie de opinión."), RandPhraseSimple("¡En ese caso no te retraso más!", "Entonces será mejor que te vayas antes de que cambie de opinión."));
		link.l1 = "Ya me estoy yendo...";
		link.l1.go = "peace";
		break;

	case "after_peace":
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + RandPhraseSimple("¡Pierde el rastro!", "Desaparece de mi vista, antes de que cambie de opinión."), RandPhraseSimple("¿Puedo ayudarte?", "¿Quieres algo?"));
		link.l1 = "Me voy.";
		link.l1.go = "peace";
		break;

	// мир и все такое.
	case "peace":
		LAi_SetWarriorType(NPChar);
		NextDiag.CurrentNode = "after_peace";
		DialogExit();
		break;
	}
}

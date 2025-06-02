// Эдвард Мэнсфилд, глава буканьеров и авторитетный пират, английская линейка
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// ============================================================================
	// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
	if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
	{
		npchar.angry.ok = 1;
		if (!CheckAttribute(npchar, "angry.first")) // ловушка первого срабатывания
		{
			NextDiag.TempNode = NextDiag.CurrentNode;
			Dialog.CurrentNode = "AngryExitAgain";
			npchar.angry.first = 1;
		}
		else
		{
			switch (npchar.angry.kind) // сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
			{
			case "repeat":
				if (npchar.angry.name == "Firsttime")
					Dialog.CurrentNode = "AngryRepeat_1";
				break;
			}
		}
	}
	// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
	// ============================================================================
	switch (Dialog.CurrentNode)
	{
	case "First time":
		NextDiag.TempNode = "First time";
		if (CheckAttribute(npchar, "Sp5LaVegaAttackDone"))
		{
			if (NPChar.quest.meeting == "0")
			{
				dialog.Text = TimeGreeting() + "¡ Yo soy " + GetFullName(NPChar) + ", el nuevo gobernador de este antro. No será fácil poner en orden a los matones locales, pero ya no representan una amenaza para las colonias españolas.";
				Link.l1 = "Me alegra conocerte. Soy el capitán " + GetFullName(Pchar) + " Lo siento, pero debo irme.";
				Link.l1.go = "exit";
				NPChar.quest.meeting = "1";
			}
			else
			{
				dialog.Text = TimeGreeting() + " Estoy ocupado, muy ocupado, necesito controlar a los matones locales para prevenir cualquier amenaza a las colonias españolas.";
				Link.l1 = "No te molestaré entonces.";
				Link.l1.go = "exit";
			}
		}
		else
		{
			dialog.text = NPCStringReactionRepeat("¿Tienes algo que decirme? ¿No? Entonces " + GetSexPhrase("¡Aléjate de aquí!", "Le pido que no me moleste.") + "", "Creo que me he explicado con claridad...", "¡Aunque he sido claro, sigues molestándome!", "Bueno, eres inconmensurable " + GetSexPhrase("demasiado grosero, mon cheri", "qué descortesía, muchacha", "tal descortesía, muchacha") + "...", "repeat", 30, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Me voy.", "Sí, " + npchar.name + ", veo eso.", "Lo siento, " + npchar.name + "...", "¡Ay...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		}

		if (npchar.city == sti(pchar.HeroParam.Location))
		{
			if (!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
			{
				link.l2 = "¿Tienes algún trabajo para mí?";
				link.l2.go = "pirateStartQuest";
			}
			else
			{
				if (pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many"))
				{
					link.l2 = "Encontré el rastro, pero necesito algunas monedas - 30.000 pesos para sacar a la rata de su agujero.";
					link.l2.go = "pirateStartQuest_many";
				}
				if (pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
				{
					link.l2 = "Aquí, mira esta carta que encontré en el cadáver del contrabandista";
					link.l2.go = "pirateStartQuest_info_1";
				}
				if (pchar.questTemp.pirateStartQuest == "5")
				{
					link.l2 = "Está hecho. Norman Vigo y su barco pertenecen al demonio del mar.";
					link.l2.go = "pirateStartQuest_final";
				}
			}
		}
		break;

	case "Exit":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		break;

	// zagolski. начальный квест за пирата ===================================
	case "pirateStartQuest":
		dialog.text = "Mm.. ¿Trabajo, dijiste? En realidad, es bueno que me lo hayas preguntado. Necesito a un hombre de afuera. Quiero averiguar algo en el pueblo más cercano, pero mis hombres son conocidos allí. No puedo prometerte mucho, pero obtendrás algo.";
		link.l1 = "¿Cuál es la misión?";
		link.l1.go = "pirateStartQuest_1";
		link.l2 = "Lo siento, pero no correré el riesgo por unas pocas sobras. Adiós.";
		link.l2.go = "exit";
		pchar.questTemp.pirateStartQuest = "0";
		break;
	case "pirateStartQuest_1":
		dialog.text = "Entonces escucha, tenía un trato para entregar 200 esclavos hace un mes con el capitán de la goleta 'Saintblue'. Quería venderlos al dueño de la plantación. El tiempo ha pasado y el cliente ha comenzado a preocuparse, pero ayer me dijeron que la goleta fue vista no lejos de la isla. ¡Pero! El capitán no se presentó. Hoy, mi cliente me ha exigido que le devuelva su adelanto y dijo que le ofrecieron comprar esclavos de otro vendedor. Más caro, pero todo el lote de esclavos de una vez.";
		link.l1 = "¿Y? ¿Tengo que encontrar 200 esclavos en unos pocos días para salvarte de perder un adelanto? ¿Por unas pocas monedas?";
		link.l1.go = "pirateStartQuest_2";
		break;
	case "pirateStartQuest_2":
		dialog.text = "Por supuesto que no. ¿Acaso parezco un idiota? De todos modos, no le devolveré el adelanto. Pero necesito pruebas de que esos esclavos que le fueron ofrecidos son míos. Encuentra a aquellos que le ofrecieron un nuevo trato y obtendrás tus 10.000 pesos. ¿Trato?";
		link.l1 = "Estoy dentro. ¿Tienes alguna sospecha de quién podría ser?";
		link.l1.go = "pirateStartQuest_3";
		link.l2 = "Ni hablar. Busca a alguien más, ¿solo por 10.000? Lo siento, pero no funcionará.";
		link.l2.go = "exit";
		break;
	case "pirateStartQuest_3":
		dialog.text = "Si tuviera alguna idea, nunca usaría tus servicios. Esos hombres ya estarían muertos. Pero estoy ansioso por saber cómo se enteraron de la carga del 'Saintblue' y de mi cliente. Parece que les fue bastante fácil. ¿Ves ahora?";
		link.l1 = "Sí, alguien te ha traicionado.";
		link.l1.go = "pirateStartQuest_4";

		pchar.questTemp.pirateStartQuest = "1";
		pchar.questTemp.pirateStartQuest.City = npchar.city;
		pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
		pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

		AddQuestRecord("pSQ", "1");
		AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
		AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
	case "pirateStartQuest_4":
		dialog.text = "¡Exactamente! Estoy buscándolo. Matar a mis competidores y devolverme mis esclavos no es tu prioridad. Necesito a esa rata, en realidad su cabeza en una pica si soy honesto. ¿Ves ahora por qué mis hombres no deben saber nada sobre tu misión? Sospecharé de todos hasta que descubra quién vende la información. Y realmente no quiero eso...";
		link.l1 = "Ya veo. Entonces mantendré un perfil bajo. Estoy en camino.";
		link.l1.go = "exit";
		break;

	case "pirateStartQuest_many":
		dialog.text = "Treinta mil dices? Esa es una gran suma... Solo puedo darte 5.000 pesos, es todo lo que tengo ahora. ¡Y ni se te ocurra escapar con el dinero o te encontraré y te colgaré en la cerca más cercana! ¿Entendido?";
		link.l1 = "Está bien, dame cinco mil entonces...";
		link.l1.go = "pirateStartQuest_many_1";
		break;
	case "pirateStartQuest_many_1":
		dialog.text = "Tómalo. Estoy esperando el resultado de tu búsqueda.";
		link.l1 = "Estará bien.";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, 5000);
		pchar.questTemp.pirateStartQuest.many = "";
		break;

	//------------------------------------
	case "pirateStartQuest_info_1":
		dialog.text = "¡Ja! ¡Excelentes noticias! Estaba seguro de que lo lograrías. Tengo información intrigante.";
		link.l1 = "He hecho mi trabajo y quiero mis diez mil.";
		link.l1.go = "pirateStartQuest_info_2";
		TakeItemFromCharacter(pchar, "letter_open");
		break;
	case "pirateStartQuest_info_2":
		dialog.text = "Claro, aquí tienes tu recompensa. Pero no te vayas, tengo otra tarea para ti.\nPfaifer es un tripulante de Norman Vigo del lugre 'Septima'. Estoy seguro de que Norman Vigo es la rata, incluso si es uno de los nuestros. Recientemente ha sido visto en las aguas de la isla. Tu trabajo es enviar a esta rata al diablo del mar. No me fallaste la primera vez, por eso quiero pedirte que te encargues de este asunto también. Te pagaré 15.000 pesos. ¿Trato hecho?";
		link.l1 = "¡Estoy en ello! Considera al traidor muerto.";
		link.l1.go = "pirateStartQuest_info_3";
		link.l2 = "Sabes, no quiero participar en eso... De todos modos, no tengo tiempo. Lo siento, pero me voy.";
		link.l2.go = "pirateStartQuest_info_noex";
		AddMoneyToCharacter(pchar, 10000);
		break;
	case "pirateStartQuest_info_noex":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		pchar.questTemp.pirateStartQuest = "0";
		CloseQuestHeader("pSQ");
		break;
	case "pirateStartQuest_info_3":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		pchar.questTemp.pirateStartQuest = "4";

		AddQuestRecord("pSQ", "7");
		AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

		pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
		pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
		pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

	case "pirateStartQuest_final":
		dialog.text = "Lo sé, lo sé. Mis hombres estaban observando la batalla y ya me han informado sobre tu victoria impecable. Muy bien, has hecho bien tu trabajo. Aquí tienes 15.000 pesos, como te prometí. Y gracias, me has ayudado enormemente.";
		link.l1 = "¡Está bien, me alegró poder ayudar! Pero ahora debo irme, he estado aquí demasiado tiempo y tengo muchas cosas que hacer. ¡Adiós!";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, 15000);
		pchar.questTemp.pirateStartQuest = "0";
		CloseQuestHeader("pSQ");
		group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;

	case "No_Mansfield_first_time":
		dialog.text = "Saludos, mi nombre es Alistair Good. Fui elegido como jefe de los bucaneros después de la muerte de Mansfield.";
		link.l1 = "Encantado de conocerte, Alistair.";
		link.l1.go = "exit";
		NextDiag.TempNode = "No_Mansfield";
		break;
	case "No_Mansfield":
		dialog.text = "No tengo tiempo para hablar contigo. Visítame más tarde.";
		link.l1 = "Ya me voy.";
		link.l1.go = "exit";
		break;

		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
	case "AngryRepeat_1":
		dialog.text = RandPhraseSimple("" + GetSexPhrase("Obtener", "Obtener") + " ¡fuera!", "¡Vete de mi casa!");
		link.l1 = "Ups...";
		link.l1.go = "AngryExitAgainWithOut";
		if (CheckAttribute(npchar, "angry.terms")) // примиряемся с Мэнсфилдом через 30 дней.
		{
			if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
			{
				dialog.text = "No me molestes, recuerda eso.";
				link.l1 = "Lo tengo.";
				link.l1.go = NextDiag.TempNode;
				CharacterDelAngry(npchar);
			}
		}
		break;
	case "AngryExitAgain":
		DialogExit();
		DeleteAttribute(npchar, "angry.ok");
		break;
	case "AngryExitAgainWithOut":
		DialogExit();
		DeleteAttribute(npchar, "angry.ok");
		DoReloadCharacterToLocation("LaVega_town", "reload", "reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
	}
}

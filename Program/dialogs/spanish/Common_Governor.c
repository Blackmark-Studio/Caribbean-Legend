// boal 25/04/04 общий диалог Governor
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Governor\" + NationShortName(sti(NPChar.nation)) + "_Governor.c ";
						 if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--

	ref offref, sld;
	int i, cn;
	int qty;
	int iSumm;
	string attrLoc;

	/// выкуп колонии
	ref CaptGovenor, FortColony;
	int f, colony_money;

	int k = 1000;
	if (CheckAttribute(Nations[sti(NPChar.nation)], "Fort"))
	{
		k = (300 - sti(Nations[sti(NPChar.nation)].Fort) * 10);
	}
	bool ok;

	attrLoc = Dialog.CurrentNode;
	if (findsubstr(attrLoc, "CityGive_", 0) != -1)
	{
		i = findsubstr(attrLoc, "_", 0);
		NPChar.quest.CityIdx = strcut(attrLoc, i + 1, strlen(attrLoc) - 1); // индех в конце
		Dialog.CurrentNode = "ColonyGive";
	}

	switch (Dialog.CurrentNode)
	{
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOff");
		break;

	case "fight":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		LAi_group_Attack(NPChar, Pchar);
		break;

	case "First time":
		NextDiag.TempNode = "First time";
		if (LAi_grp_playeralarm > 0)
		{
			dialog.text = NPCharRepPhrase(pchar, LinkRandPhrase("¿Te atreves a mostrar tu cara en la oficina del gobernador general? Estás loco, de verdad...", "¿Cómo dejaron estos holgazanes que un enemigo irrumpiera en mi residencia? Esto está más allá de mi comprensión...", "Ciertamente, mis guardias no valen un centavo si algún vagabundo anda por mi residencia..."), LinkRandPhrase("¿Qué necesitas, " + GetSexPhrase("reptil", "apestosa") + "? Mis soldados ya han sido enviados tras tu rastro, " + GetSexPhrase("pirata asqueroso", "apestosa") + ".", "" + GetSexPhrase("¡Sucio asesino", "¡Sucia asesina") + ", abandona mi residencia de inmediato! ¡Guardias!", "No te tengo miedo, " + GetSexPhrase("canalla", "granuja") + ". ¡Pronto serás colgado en nuestro fuerte, no llegarás lejos!"));
			link.l1 = NPCharRepPhrase(pchar, RandPhraseSimple("Los soldados no valen una mierda...", "Jamás me capturarás."), RandPhraseSimple("¡Cállate, compañero, o te arrancaré esa lengua podrida tuya!", "Te lo digo, compañero: siéntate tranquilamente o te cortaré la cabeza y la lanzaré por esa puerta a tus perros guardianes..."));
			link.l1.go = "fight";
			break;
		}
		if (npchar.quest.meeting == "0")
		{
			dialog.text = "He oído que has sido muy persistente al solicitar una audiencia. Mi nombre es " + GetFullName(npchar) + ". Soy el gobernador general de las colonias de " + NationNameGenitive(sti(NPChar.nation)) + ", delegado de la Corona de " + NationKingsName(npchar) + " en estas aguas. Ahora, por favor, sea tan amable de decirme, ¿cuál es el propósito de su visita, " + GetAddress_Form(NPChar) + "?";
			link.l1 = "Mi nombre es " + GetFullName(pchar) + ".";
			link.l1.go = "node_1";
			npchar.quest.meeting = "1";
		}
		else
		{
			dialog.text = RandPhraseSimple("¿Oh, eres tú de nuevo? Bueno, ¿qué quieres del gobernador general de " + NationNameGenitive(sti(NPChar.nation)) + "¿esta vez?", "¿Y una vez más, me estás distrayendo de asuntos de estado importantes? ¿Qué quieres, " + GetAddress_Form(NPChar) + "?");
			link.l1 = "Quiero hablar contigo sobre trabajar en nombre de la Corona de " + NationNameGenitive(sti(NPChar.nation));
			link.l1.go = "work";
			link.l2 = "Necesito hablar contigo sobre un asunto importante.";
			link.l2.go = "quests"; // файл нации
			// Jason --> Регата
			if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
			{
				link.l3 = "Llegué por una invitación para participar en la regata. Aquí está mi invitación.";
				link.l3.go = "Regata";
			}
			//<-- Регата
			link.l10 = "Lo siento, pero tengo algunos asuntos que atender.";
			link.l10.go = "exit";
		}
		break;

	case "node_1":
		dialog.text = "¿Entonces cuál fue la razón para que vinieras aquí y me distraigas de los asuntos importantes del estado?";
		link.l1 = "Quería hablar contigo sobre trabajar en nombre de la Corona de " + NationNameGenitive(sti(NPChar.nation));
		link.l1.go = "work";
		link.l2 = "Iba a hablar contigo sobre un asunto importante.";
		link.l2.go = "quests";
		// Jason --> Регата
		if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
		{
			link.l3 = "Vine aquí para participar en la regata. Aquí está mi invitación.";
			link.l3.go = "Regata";
		}
		//<-- Регата
		link.l10 = "Es solo una visita de cortesía, nada más, " + GetAddress_FormToNPC(NPChar);
		link.l10.go = "node_2";
		break;

	case "node_2":
		dialog.text = "En ese caso, te pediría que salgas de mi oficina y dejes de distraerme de mi trabajo.";
		link.l1 = "Sí, sí, por supuesto. Perdón por molestarte.";
		link.l1.go = "exit";
		break;

	case "work":
		dialog.text = "Si buscas trabajo, habla con los gobernadores de las colonias. A menudo necesitan capitanes inteligentes y valientes.";
		link.l1 = "Lo tendré en cuenta. Gracias.";
		link.l1.go = "exit";
		break;

	//--> Jason регата
	case "Regata":
		dialog.text = "¡Oh, estupendo, me alegra verte, capitán! Has llegado justo a tiempo, la regata está a punto de comenzar en unos días. ¿Leíste las reglas de la regata en la carta que el mensajero debió haberte entregado?";
		link.l1 = "Sí, señor, lo hice.";
		link.l1.go = "Regata_1";
		RemoveItems(PChar, "letter_open", 1);					// уберем письмо
		TakeNationLicence(HOLLAND);								// уберем лицензию
		DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
		break;

	case "Regata_1":
		dialog.text = "¿Y preparaste 50000 pesos, tu cuota de entrada, que contribuirá al premio?";
		if (makeint(Pchar.money) >= 50000)
		{
			link.l1 = "Sí, por supuesto. Por favor, acepta mi tarifa.";
			link.l1.go = "Regata_2";
		}
		link.l2 = "Estoy un poco corto de dinero en este momento. Pero definitivamente lo traeré tan rápido como pueda.";
		link.l2.go = "Regata_nomoney";
		break;

	case "Regata_2":
		dialog.text = "Muy bien. Si ganas, tu dinero se te devolverá quintuplicado. Ahora, deberías saber cómo no romper las reglas de la regata.\nDiscute los detalles con Henry Stevenson, debe estar en la sala de residencia. Encuéntrate con él, él te lo explicará todo.";
		link.l1 = "Está bien. Haré como dices.";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, -50000);
		pchar.quest.Regata_Guber.win_condition.l1 = "location";
		pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
		pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
		pchar.questTemp.Regata.Begin = "true";
		NextDiag.TempNode = "First time";
		break;

	case "Regata_nomoney":
		dialog.text = "Bien, pero por favor no tardes demasiado, capitán. La regata está a punto de comenzar pronto.";
		link.l1 = "Ya veo. Intentaré traerte dinero antes de que comience la regata.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Regata_1";
		pchar.questTemp.Regata.nomoney = "true";
		break;

	// регата-финал
	case "Regata_Final":
		dialog.text = "¡Y aquí tenemos al ganador de la regata! Hola, capitán " + GetFullName(pchar) + "¡Permíteme felicitarte por este éxito bien merecido! Los ganadores de la regata siempre son populares en las colonias inglesas, merecidamente populares.";
		link.l1 = "¡Gracias, señor!";
		link.l1.go = "Regata_complete";
		break;

	case "Regata_complete":
		dialog.text = "Ahora pasemos a la parte más agradable para ti, la ceremonia de recompensa. El primer premio en dinero es de 250000 pesos. ¡Aquí tienes!";
		link.l1 = "¡Gracias!";
		link.l1.go = "Regata_complete_1";
		break;

	case "Regata_complete_1":
		AddMoneyToCharacter(pchar, 250000);
		int iGift;
		string sItem1, sItem2, sItem3, sAdd;

		iGift = 3;
		switch (iGift)
		{
		case 0:
			sItem1 = "blade_10"; // корд
			sItem2 = "cirass6";
			sItem3 = "bussol";
			sAdd = "cordón, chaleco de duelista y boussole";
			break;

		case 1:
			sItem1 = "blade_15"; // маринера
			sItem2 = "cirass2";	 // рейтарский панцирь
			sItem3 = "bussol";
			sAdd = "marinera, armadura de reiter y boussole";
			break;

		case 2:
			sItem1 = "blade_17"; // бретта
			sItem2 = "cirass7";	 // карацена
			sItem3 = "bussol";
			sAdd = "bretta, karacena y boussole";
			break;

		case 3:					 //
			sItem1 = "blade_20"; // мадонна
			sItem2 = "cirass2";	 // офицерская кираса
			sItem3 = "bussol";
			sAdd = "'Madonna', coraza de oficial y boussole";
			break;
		}
		GiveItem2Character(pchar, sItem1);
		GiveItem2Character(pchar, sItem2);
		GiveItem2Character(pchar, sItem3);
		dialog.text = "Además, eres elegible para un conjunto de valiosos premios: " + sAdd + ". Ahora todo es tuyo.";
		link.l1 = "¡Estoy muy contento, señor! Realmente, no podría haberlo esperado.";
		link.l1.go = "Regata_complete_2";
		break;

	case "Regata_complete_2":
		dialog.text = "¡En nombre de todas las colonias inglesas, me complace agradecerte por participar en la regata y una vez más te felicito por tu victoria! Si hiciste una apuesta, ahora es el momento perfecto para ver a Sir Henry Stevenson y recoger tus ganancias, si aún no lo has hecho. ¡Buena suerte para ti, capitán!";
		link.l1 = "¡Gracias por sus amables palabras, señor! A su vez, permítame agradecerle por brindarme la oportunidad de participar en un evento tan grandioso. Y ahora, por favor permítame despedirme y marcharme.";
		link.l1.go = "Regata_complete_3";
		break;

	case "Regata_complete_3":
		DialogExit();
		NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
	}
}

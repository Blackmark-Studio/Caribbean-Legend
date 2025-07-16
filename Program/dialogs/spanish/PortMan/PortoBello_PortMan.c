// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	int i, n;
	string month;

	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas son esas?", "¿Qué quieres, " + GetAddress_Form(NPChar) + "?"), "Ya has intentado hacerme una pregunta " + GetAddress_Form(NPChar) + "...", "Has estado hablando de alguna cuestión por tercera vez hoy...", "Mira, si no tienes nada que contarme sobre los asuntos del puerto, entonces no me molestes con tus preguntas.", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión.", "No tengo nada de qué hablar."), "No importa.", "De hecho, ya es la tercera vez...", "Lo siento, pero no estoy interesado en los asuntos del puerto por ahora.", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		if (pchar.questTemp.Slavetrader == "FindRatPortobello_1")
		{
			link.l1 = "Buen día. Me gustaría saber dónde está el Capitán Francois Gontier. Tengo un asunto importante.";
			link.l1.go = "Portobello_ratP_1";
		}
		// belamour legengary edition на пару с Акулой -->
		if (CheckAttribute(pchar, "questTemp.SharkGoldFleet"))
		{
			if (pchar.questTemp.SharkGoldFleet == "toPBPortOffice" || pchar.questTemp.SharkGoldFleet == "KillCurier")
			{
				link.l1 = "Soy un mercader, vine de Caracas, y tu colega de la autoridad portuaria me pidió que te entregara alguna correspondencia ...";
				link.l1.go = "SharkGoldFleet";
			}
			if (pchar.questTemp.SharkGoldFleet == "MoneySpeak")
			{
				link.l1 = "Sí, estoy aquí por el pago.";
				link.l1.go = "SharkGoldFleet_11";
			}
		}
		//<-- на пару с Акулой
		break;

	case "Portobello_ratP_1":
		dialog.text = "¿Un asunto importante dices? Vamos a ver. Bueno...  Francois Gontier, en la corbeta '" + pchar.questTemp.Slavetrader.ShipName + "... Según mis notas, el señor Gontier se dirigía a Jamaica.";
		link.l1 = "¡Gracias! ¡Has ayudado mucho!";
		link.l1.go = "exit";
		pchar.questTemp.Slavetrader = "FindRatJamaica";
		AddQuestRecord("Slavetrader", "21_3");
		AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
		break;
	// на пару с Акулой -->
	case "SharkGoldFleet":
		if (!bImCasual)
			pchar.quest.SharkGoldFleetToPB10.over = "yes";
		RemoveItems(PChar, "letter_1", 1);
		ChangeItemDescribe("letter_1", "itmdescr_letter_1");
		dialog.text = "¡Ah, bueno, por fin! ¿Dices que eres un comerciante? Otra vez están tratando de ahorrar dinero en mensajeros y posponiendo el envío hasta el último maldito... ¡Sí, bueno, claro que sí! Esto es verdad. ¿Y así es como debería equipar la escuadra con ellos en un plazo tan corto?...";
		link.l1 = "Parece irresponsable...";
		link.l1.go = "SharkGoldFleet_01";
		break;

	case "SharkGoldFleet_01":
		dialog.text = "¡Esa es una manera de decirlo! Bueno, está bien, qué hacer. Nos encontraremos a tiempo... Estoy hablando de mí, no prestes atención. Escucha, ¿vas a volver por casualidad?";
		link.l1 = "Bueno, en realidad, iba a vender mercancías aquí y luego regresar a Caracas...";
		link.l1.go = "SharkGoldFleet_02";
		break;

	case "SharkGoldFleet_02":
		dialog.text = "¡Estupendo! Ahora les escribiré una respuesta y te pediré que la envíes de vuelta. Así que... entrégala, por favor, dentro de diez días, de lo contrario no tendrán tiempo de hacer nada a tiempo... Y di tu nombre.";
		if (pchar.questTemp.SharkGoldFleet == "KillCurier")
		{
			link.l1 = "Mi nombre es " + GetFullName(pchar) + ".";
			link.l1.go = "SharkGoldFleet_03";
		}
		else
		{
			link.l1 = "Mi nombre es Andreas Garcia.";
			link.l1.go = "SharkGoldFleet_09";
		}
		break;

	case "SharkGoldFleet_03":
		TakeNItems(pchar, "letter_2", 1);
		ChangeItemDescribe("letter_2", "itmdescr_letter_SharkGoldFleet_2");
		dialog.text = "Espera un momento... Registrado. Aquí tienes. Recuerda: ¡diez días! Mientras tanto, leeré con más detalle lo que me trajiste.";
		link.l1 = "Sí, lo recuerdo. ¡Adiós!";
		link.l1.go = "SharkGoldFleet_04";
		break;

	case "SharkGoldFleet_04":
		dialog.text = "Espera un minuto... No entiendo... Una vez más, ¿cómo dijiste que te llamabas?";
		link.l1 = "¿Yo?.. Bueno... ¿Por qué es tan importante?";
		link.l1.go = "SharkGoldFleet_05";
		break;

	case "SharkGoldFleet_05":
		n = GetAddingDataDay(0, 0, 21);
		if (n < 21)
			i = GetAddingDataMonth(0, 1, 0);
		else
			i = GetDataMonth();
		month = XI_ConvertString("target_month_" + i);
		pchar.questTemp.SharkGoldFleet.Date = "" + n + " " + month + "";
		SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
		SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
		if (!bImCasual)
			SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
		else
			NewGameTip("Modo exploración: el temporizador está desactivado.");
		dialog.text = "¡Es muy importante! Dice... Entonces... " + n + " " + month + "... No, eso no es... 12, 50, 69, 55... Pero dónde está... ¡Ah, aquí está! La carta debe ser entregada por el Capitán " + pchar.questTemp.SharkGoldFleet.CurierName + " " + pchar.questTemp.SharkGoldFleet.Curierlastname + " ¿Y dijiste que tu nombre es... " + GetFullName(pchar) + "?";
		link.l1 = "Debe haber habido algún error...";
		link.l1.go = "SharkGoldFleet_06";
		break;

	case "SharkGoldFleet_06":
		DeleteAttribute(pchar, "questTemp.SharkGoldFleet.CurierName");
		DeleteAttribute(pchar, "questTemp.SharkGoldFleet.Curierlastname");
		dialog.text = "No, no puede haber error. Devuélveme la carta que te di. ¡Necesito resolver esto!";
		link.l1 = "Vamos... Lo entregaré, todo estará bien.";
		link.l1.go = "SharkGoldFleet_07";
		break;

	case "SharkGoldFleet_07":
		dialog.text = "¡No! ¡Devuélveme la carta! ¡Guardias!!!";
		link.l1 = "Ah, ¿quieres hacerlo por las malas, eh?";
		link.l1.go = "SharkGoldFleet_08";
		break;

	case "SharkGoldFleet_08":
		DialogExit();
		pchar.questTemp.SharkGoldFleet = "DifficultVar";
		if (CheckCharacterItem(pchar, "HolTradeLicence"))
		{
			TakeNationLicence(HOLLAND);
			log_info("¡Licencia de comercio cancelada!");
		}
		for (i = 1; i <= 2; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("Sold" + i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", sti(pchar.rank), SPAIN, 0, true, "soldier"));
			SetFantomParamFromRank(sld, sti(pchar.rank), true);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto3");
			LAi_SetWarriorType(sld);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Attack(sld, Pchar);
		}
		LAi_group_Attack(NPChar, Pchar);
		SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
		AddDialogExitQuest("MainHeroFightModeOn");
		SetFunctionExitFromLocationCondition("SharkGoldFleetExitPO", pchar.location, false);
		break;

	case "SharkGoldFleet_09":
		dialog.text = "Espera un minuto... Ahí vamos. Entonces escribiré tu nombre en una carta de respuesta. Aquí tienes. Recuerda: ¡tienes diez días! Mientras tanto, leeré con más detalle lo que me trajiste.";
		link.l1 = "Sí, recuerdo. ¡Adiós!";
		link.l1.go = "SharkGoldFleet_10";
		break;

	case "SharkGoldFleet_10":
		DialogExit();
		pchar.questTemp.SharkGoldFleet = "MoneySpeak";
		TakeNItems(pchar, "letter_2", 1);
		ChangeItemDescribe("letter_2", "itmdescr_letter_SharkGoldFleet_2");
		AddQuestRecord("SharkGoldFleet", "17");
		chrDisableReloadToLocation = true;
		bDisableFastReload = true;
		break;

	case "SharkGoldFleet_11":
		dialog.text = "¿Pago?..";
		link.l1 = "En Caracas, tu colega me dijo que pagarías por la entrega de la carta.";
		link.l1.go = "SharkGoldFleet_12";
		break;

	case "SharkGoldFleet_12":
		dialog.text = "¡No, bueno, están completamente locos allí! ¡Ahora tengo que pagar por ellos!";
		link.l1 = "...";
		link.l1.go = "SharkGoldFleet_13";
		break;

	case "SharkGoldFleet_13":
		dialog.text = "¿Y cuánto te prometieron?";
		link.l1 = "Cinco mil pesos.";
		link.l1.go = "SharkGoldFleet_14";
		link.l2 = "Diez mil pesos.";
		link.l2.go = "SharkGoldFleet_15";
		break;

	case "SharkGoldFleet_14":
		pchar.questTemp.SharkGoldFleet = 5000;
		dialog.text = "Aparentemente, decidieron vivir allí a mi costa... ¡No solo no quieren gastar dinero en mensajeros, confiando tales casos a los barcos mercantes que pasan, sino que también me cargan los gastos a mí! ¡Escribiré una queja contra ellos a La Habana!";
		link.l1 = "Entiendo su indignación, señor, pero ¿qué debo hacer?";
		link.l1.go = "SharkGoldFleet_16";
		break;

	case "SharkGoldFleet_15":
		pchar.questTemp.SharkGoldFleet = 10000;
		ChangeCharacterComplexReputation(pchar, "nobility", -1);
		ChangeOfficersLoyality("bad", 1);
		dialog.text = "Al parecer, decidieron vivir allí a mi costa... ¡No solo no quieren gastar dinero en mensajeros, confiando tales casos a los barcos mercantes de paso, sino que también me cuelgan los gastos a mí! ¡Les enviaré una queja a La Habana!";
		link.l1 = "Entiendo su indignación, señor, pero ¿qué debo hacer?";
		link.l1.go = "SharkGoldFleet_16";
		break;

	case "SharkGoldFleet_16":
		dialog.text = "Argh, no tienes la culpa de la avaricia de los funcionarios de la Nueva España en Caracas. Pero simplemente no tengo esa cantidad de dinero conmigo ahora mismo. Y el presupuesto debería llegar solo mañana... Espera aquí, por favor, iré al prestamista ahora y volveré enseguida.";
		link.l1 = "...";
		link.l1.go = "SharkGoldFleet_17";
		break;

	case "SharkGoldFleet_17":
		DialogExit();
		LAi_SetActorType(pchar);
		LAi_ActorTurnToLocator(pchar, "reload", "reload1");
		LAi_SetStayType(npchar);
		ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto2");
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocator(npchar, "reload", "reload1", "SGF_toUsurer", -1);
		break;

	case "SharkGoldFleet_18":
		AddMoneyToCharacter(pchar, makeint(pchar.questTemp.SharkGoldFleet));
		n = GetAddingDataDay(0, 0, 21);
		if (n < 21)
			i = GetAddingDataMonth(0, 1, 0);
		else
			i = GetDataMonth();
		month = XI_ConvertString("target_month_" + i);
		pchar.questTemp.SharkGoldFleet.Date = "" + n + " " + month + "";
		SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
		SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
		if (!bImCasual)
			SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
		else
			NewGameTip("Modo exploración: el temporizador está desactivado.");
		AddQuestRecord("SharkGoldFleet", "18");
		AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
		LAi_SetHuberType(npchar);
		Lai_SetPlayerType(pchar);
		chrDisableReloadToLocation = false;
		bDisableFastReload = false;
		dialog.text = "Lo siento por la espera. Aquí están sus " + makeint(pchar.questTemp.SharkGoldFleet) + "piezas de a ocho. Y en este caso, ellos mismos pagarán por la respuesta en Caracas. Dime que lo hice.";
		link.l1 = "Bien, lo transmitiré. ¡Gracias y buena suerte!";
		link.l1.go = "exit";
		pchar.questTemp.SharkGoldFleet = "LightVar";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

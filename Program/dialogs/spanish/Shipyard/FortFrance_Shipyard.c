// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?", "¿Cómo puedo ayudarte?"), "Intentaste hacerme una pregunta hace un rato...", "Jamás he conocido a personas con tanta curiosidad en mi astillero ni en ninguna otra parte de este pueblo.", "¿Por qué tantas preguntas? Mi trabajo es construir barcos. Ocupémonos de eso.", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No tengo nada de qué hablar en este momento."), "Umph, ¿a dónde se ha ido mi memoria...?", "Mm, bueno...", "Adelante...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		// Addon-2016 Jason ”ЊЉ-Њартиника
		if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "begin")
		{
			link.l1 = "Tu hombre me dijo que quieres verme. Soy todo oídos.";
			link.l1.go = "FMQM";
		}
		if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "oil" && GetSquadronGoods(pchar, GOOD_OIL) >= 50)
		{
			link.l1 = "He hecho el trabajo. " + FindRussianQtyString(GetSquadronGoods(pchar, GOOD_OIL)) + " barriles de resina están dentro de mis bodegas de carga.";
			link.l1.go = "FMQM_9";
		}
		break;

	// Addon-2016 Jason ”ЊЉ-Њартиника
	case "FMQM":
		pchar.quest.FMQM_Denial.over = "yes";
		dialog.text = "Sí, sí, capitán " + GetFullName(pchar) + ". Vi tu nave entrando en nuestro puerto e inmediatamente envié a mi trabajador hacia ti. Vamos directo al grano: eres un recién llegado, pero dicen que ya te has convertido en un marinero experimentado y la fortuna está de tu lado. Por eso tengo una propuesta de negocio para ti.";
		link.l1 = "¡Interesante! Continúa, cuéntame.";
		link.l1.go = "FMQM_1";
		DelLandQuestMark(npchar);
		break;

	case "FMQM_1":
		dialog.text = "¿Alguna vez has oído hablar de una resina especial que los españoles producen en la isla de Trinidad? Es un recurso raro de valor estratégico usado para reforzar el casco de los barcos. Cada barril cuesta una suma considerable porque los españoles destinan toda la resina para las necesidades de su Armada. Todas las autoridades coloniales mantienen el comercio de este bien bajo control, para ponerlo simple, es un puro contrabando. Necesito esta resina para un pedido especial. Por supuesto, nuestra tienda no la tiene, lo mismo se puede decir sobre nuestros almacenes militares locales o simplemente no querían venderla. Realmente es irrelevante. Lo que es relevante es que necesito la resina y sé dónde conseguirla. Todo lo que necesito es un capitán que se sienta cómodo con los abordajes.";
		link.l1 = "Creo que empiezo a ver tu punto...";
		link.l1.go = "FMQM_2";
		break;

	case "FMQM_2":
		dialog.text = "Espléndido. Ahora escucha, un pequeño convoy comercial fue localizado cerca de Trinidad o, para ser más preciso, en el puerto de San José. Un barco lleva un buen lote de resina, la misma resina que necesito desesperadamente. Te contaré más si te gusta la idea de saquear a los enemigos de nuestra nación. ¿Qué dices?";
		link.l1 = "Me gusta tu propuesta. Estoy listo para intentarlo.";
		link.l1.go = "FMQM_3";
		link.l2 = "Pasaré, monsieur. Mi barco y mi tripulación no están en su mejor estado en este momento.";
		link.l2.go = "FMQM_exit";
		break;

	case "FMQM_exit":
		dialog.text = "Está bien, es tu derecho hacer lo que quieras. Lamento haber tomado tu tiempo, capitán.";
		link.l1 = "Adiós.";
		link.l1.go = "FMQM_exit_1";
		break;

	case "FMQM_exit_1":
		DialogExit();
		pchar.questTemp.FMQM = "fail";
		AddQuestRecord("FMQ_Martinique", "3");
		CloseQuestHeader("FMQ_Martinique");
		break;

	case "FMQM_3":
		string sTemp = "barquentine";
		if (MOD_SKILL_ENEMY_RATE < 7)
			sTemp = "barque"; // Addon 2016-1 Jason пиратскаЯ линейка
		dialog.text = "Entonces escucha: el convoy consta de tres barcos, la resina estará entre otras mercancías en un " + sTemp + " llamado 'Bensecho'. Este es tu objetivo principal. Como he dicho antes, los españoles navegan desde San José, Trinidad, hasta San Juan, Puerto Rico. Zarparán mañana, así que eres libre de elegir dónde atacarlos.";
		link.l1 = "Entendido. ¿Qué hay de la recompensa?";
		link.l1.go = "FMQM_4";
		break;

	case "FMQM_4":
		dialog.text = "Todo lo que me interesa es la resina. Pagaré quince doblones de oro por cada barril de esa mercancía. Según mi información, el 'Bensecho' lleva alrededor de cien barriles.";
		link.l1 = "¡Santo cielo! ¡Esta es una cantidad enorme!";
		link.l1.go = "FMQM_5";
		break;

	case "FMQM_5":
		dialog.text = "Sí. Ya te dije que esta mercancía en particular es muy cara y rara.";
		link.l1 = "También me dijiste que esto es un contrabando.";
		link.l1.go = "FMQM_6";
		break;

	case "FMQM_6":
		dialog.text = "No te preocupes, no habrá necesidad de que lo lleves a la tienda o a los contrabandistas. Ven a verme cuando el trabajo esté hecho, atracaremos tu embarcación en mi astillero para repararla y luego descargaremos todo el cargamento en secreto por la noche. Nadie sospechará nada.";
		link.l1 = "Piensas por delante de mí, maestro. Muy bien. No perdamos tiempo entonces. Estoy en camino a zarpar.";
		link.l1.go = "FMQM_7";
		break;

	case "FMQM_7":
		dialog.text = "Viento en popa, capitán.";
		link.l1 = "... ";
		link.l1.go = "FMQM_8";
		break;

	case "FMQM_8":
		DialogExit();
		pchar.questTemp.FMQM = "convoy";
		AddQuestRecord("FMQ_Martinique", "4");
		SetFunctionTimerCondition("FMQM_ConvoyStart", 0, 0, 1, false);
		break;

	case "FMQM_9":
		dialog.text = "¡Excelente! Pongamos tu barco en los muelles como acordamos antes. La descargaremos allí esta noche. Regresa a tu barco y déjame preparar el dinero para ti.";
		link.l1 = "Hagámoslo.";
		link.l1.go = "FMQM_10";
		DelLandQuestMark(npchar);
		break;

	case "FMQM_10":
		pchar.quest.FMQM_Late.over = "yes";
		DialogExit();
		InterfaceStates.Buttons.Save.enable = false;
		chrDisableReloadToLocation = true;
		pchar.GenQuest.FrameLockEsc = true;
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
		pchar.questTemp.FMQM = "remove_oil";
		pchar.questTemp.FMQM.Oil = "true";
		pchar.questTemp.FMQM.Qty = GetSquadronGoods(pchar, GOOD_OIL);
		DoQuestFunctionDelay("FMQM_WaitTime", 1.0);
		RemoveCharacterGoods(pchar, GOOD_OIL, GetSquadronGoods(pchar, GOOD_OIL));
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

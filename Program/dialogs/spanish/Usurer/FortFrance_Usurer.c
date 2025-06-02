// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?", "¿Cómo puedo ayudarle?"), "Intentaste hacerme esa pregunta no hace mucho...", "Sí, déjame adivinar... ¿Otra vez dando vueltas en círculos?", "Escucha, yo manejo las finanzas aquí, no respondo preguntas...", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No tengo nada de qué hablar en este momento."), "Umph, ¿dónde se ha ido mi memoria...?", "Lamentablemente, has acertado...", "Entiendo...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		/* //--> Бремя гасконца
		if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
		{
			link.l1 = "Tome un vistazo a estos pendientes, monsieur. Los encontré en el bolsillo de un bandido en la jungla. Este es claramente el trabajo de un fino joyero que, estoy seguro, no es de esta selva. ¿Qué dice?";
			link.l1.go = "Sharlie_junglejew";
		}
		if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
		{
			link.l1 = "Sé que tienes un deudor llamado Folke Deluc. Dime, ¿qué tan grave es su... morosidad?";
			link.l1.go = "Sharlie";
		}
		if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
		{
			link.l1 = "Estoy aquí por la deuda de Folke Deluc.";
			link.l1.go = "Sharlie_repeat";
		}
		if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
		{
			link.l1 = "He completado tu encargo, monsieur. Aquí está tu... amigo español.";
			link.l1.go = "Sharlie_14";
		}
		//<-- Бремя гасконца */

		//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
		if (CheckAttribute(pchar, "questTemp.Del_Rostovshik"))
		{
			link.l1 = "Estoy aquí, acerca de...";
			link.l1.go = "Del_Deluck";
		}
		if (CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat"))
		{
			dialog.text = "¿Trajiste 100 doblones?";
			if (PCharDublonsTotal() >= 100)
			{
				link.l1 = "Aquí está el dinero por mi oficial...";
				link.l1.go = "Del_Deluck_5";
			}
			link.l2 = "No, todavía estoy pensando.";
			link.l2.go = "exit";
		}
		//<-- Миниквест "Делюк"
		break;

	case "Sharlie":
		DelLandQuestMark(npchar);
		dialog.text = "¿Y por qué te importa eso, puedo preguntar?";
		link.l1 = "Necesito que este hombre esté libre, no entre rejas. Y según me han informado, hasta que esta deuda no se te devuelva, no será liberado. Estoy interesado en saldar esta deuda.";
		link.l1.go = "Sharlie_1";
		break;

	case "Sharlie_1":
		dialog.text = "Ajá, eso lo cambia todo. También me interesa que mi dinero regrese a mí... Este Folke Deluc es un tipo extraño. Pidió prestada una cantidad relativamente pequeña de dinero de cinco mil pesos. Simplemente no quería devolverlo y comenzó a esconderse. Al final, los intereses subieron hasta el precio de la deuda original, y se encontró tras las rejas.";
		link.l1 = "¿Se deduce que su deuda ha alcanzado actualmente los diez mil?";
		link.l1.go = "Sharlie_2";
		break;

	case "Sharlie_2":
		dialog.text = "Diez mil cuatrocientos cincuenta pesos exactamente, monsieur. Así que su libertad tiene este precio. ¿Está dispuesto a pagármelo? Estoy un poco sorprendido...";
		if (sti(pchar.money) >= 10450)
		{
			link.l1 = "No te sorprendas. Aquí está el dinero.";
			link.l1.go = "Sharlie_3";
		}
		link.l2 = "Mm... Una suma considerable, sin duda. Escuche, monsieur, ¿quizás usted y yo deberíamos intentar hacer un trato? Por ejemplo, usted tiene algo de lo que podría encargarme y usted podría evaluar mi favor en estos diez mil quinientos...";
		if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart"))
			link.l2.go = "Sharlie_5x";
		else
			link.l2.go = "Sharlie_5"; // Addon 2016-1 Jason пиратскаЯ линейка 1
		break;

	case "Sharlie_3":
		AddMoneyToCharacter(pchar, -10450);
		dialog.text = "Sí, parece que realmente necesitas a este marinero si estás dispuesto a desembolsar tal cantidad de dinero por él. De todas formas, no es asunto mío, ¿verdad, monsieur? Aquí está su pagaré, ahora tienes derecho a su deuda y puedes exigirle el dinero. Bueno, y por supuesto, solicitar su liberación de la prisión.";
		link.l1 = "Eso es exactamente lo que quería. ¡Adiós, " + npchar.name + "!";
		link.l1.go = "Sharlie_4";
		break;

	case "Sharlie_4":
		DialogExit();
		Log_Info("¡Has recibido una letra de deuda!");
		PlaySound("interface\important_item.wav");
		GiveItem2Character(pchar, "letter_open");
		ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
		pchar.questTemp.Sharlie = "freeskiper";
		AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
		break;

	case "Sharlie_5x": // Addon 2016-1 Jason пиратскаЯ линейка 1
		dialog.text = "¿Un favor? Ay, no necesito favores de ti. Al menos por ahora.";
		link.l1 = "Lástima. Debería traer el dinero para Folke entonces. ¡Adiós!";
		link.l1.go = "exit";
		pchar.questTemp.Sharlie = "bankskipermoney";
		break;

	case "Sharlie_5":
		dialog.text = "¿Favor? Hm... Sabes, monsieur, habría dado una respuesta negativa si hubieras venido ayer, pero ahora... sí, tengo algo que necesita ser atendido, pero te advierto que es bastante peligroso.";
		link.l1 = "¿Peligroso por qué?";
		link.l1.go = "Sharlie_6";
		break;

	case "Sharlie_6":
		dialog.text = "Por tu preciosa vida, por supuesto. Así que piénsalo bien antes de aceptar, y decide si estás dispuesto a hacer algo así o no.";
		link.l1 = "Monsieur, el peligro no me es desconocido. Ya he estado en situaciones peligrosas tantas veces. Así que, vayamos a los detalles. Mientras no implique eliminar a toda la guarnición del fuerte yo solo, tal vez pueda lograr lo que tan misteriosamente está insinuando.";
		link.l1.go = "Sharlie_7";
		break;

	case "Sharlie_7":
		dialog.text = "Bien. Escucha entonces. Esta noche, varios piratas y un prisionero saldrán del refugio pirata de Le Francois y caminarán hacia la cala de Le Marin. El prisionero es un oficial español, y un gran experto en ingeniería de fortificaciones. Los británicos planean usarlo para sus propios fines, así que enviarán un buque de guerra para recoger al hombre de la cala.\nEl oficial es un viejo amigo, y no quiero que termine como cautivo inglés. No puedo pedir ayuda a las autoridades locales porque estamos en guerra con España. Si tuviera más tiempo, contrataría a hombres capaces de rescatar al español... perdón, de rescatar a mi amigo, ¡pero ay!\nTú eres el único hombre en el que puedo confiar para este trabajo. Debes ir a la cala de Le Marin y... persuadir a los piratas para que te entreguen al prisionero. Dudo que muestren mucha cooperación, así que depende de ti.";
		link.l1 = "¿Cuántos piratas estarán en el convoy?";
		link.l1.go = "Sharlie_8";
		break;

	case "Sharlie_8":
		dialog.text = "No lo sé. Tal vez dos personas, tal vez tres o cuatro. Entonces, ¿qué dirías?";
		link.l1 = "Ya te he dicho 'el peligro no me es ajeno' y sé de qué lado sostener una espada.";
		link.l1.go = "Sharlie_10";
		link.l2 = "Hum. Tienes razón, es peligroso. No atacaré a una tripulación de piratas yo solo.";
		link.l2.go = "Sharlie_9";
		break;

	case "Sharlie_9":
		dialog.text = "Es tu decisión. Si crees que no estás a la altura de este trabajo, entonces es mejor que te niegues de inmediato. Entonces esperaré el dinero de la deuda de Deluc.";
		link.l1 = "Está bien. Traeré el dinero para él. ¡Nos vemos luego!";
		link.l1.go = "exit";
		pchar.questTemp.Sharlie = "bankskipermoney";
		break;

	case "Sharlie_10":
		dialog.text = "Muy bien. Me alegra oír eso. Entonces deberías ir a la cala de Le Marin, los piratas estarán allí desde las siete de la tarde hasta las cuatro de la mañana. ¡No los pierdas! ¡Y ni siquiera pienses en usar un barco! ¡Tales acciones los espantarán, camina allí a través de la jungla!\nTráeme al prisionero cuando lo encuentres, mantendré la puerta abierta. Recomiendo esperar hasta la una de la mañana antes de regresar a la ciudad porque necesitas evitar la atención de los guardias. ¡Ten cuidado y buena suerte!";
		link.l1 = "¡Gracias! Definitivamente necesitaré algo de suerte...";
		if (CheckCharacterItem(pchar, "pistol1"))
			link.l1.go = "Sharlie_13";
		else
			link.l1.go = "Sharlie_11";
		break;

	case "Sharlie_11":
		dialog.text = "¡Espera un minuto! Veo que ni siquiera tienes un arma. Toma una de las mías. También tengo varias balas para ella. Creo que te será útil.";
		link.l1 = "Sí, esto definitivamente será útil. Gracias, monsieur.";
		link.l1.go = "Sharlie_12";
		break;

	case "Sharlie_12":
		Log_Info("¡Has recibido una pistola de combate!");
		PlaySound("interface\important_item.wav");
		GiveItem2Character(pchar, "pistol1");
		TakeNItems(pchar, "bullet", 20);
		TakeNItems(pchar, "gunpowder", 20);
		dialog.text = "¡Y ahora vete, que Dios te ayude!";
		link.l1 = "...";
		link.l1.go = "Sharlie_13";
		break;

	case "Sharlie_13":
		DialogExit();
		pchar.quest.Sharlie_captive_Tut.win_condition.l1 = "location";
		pchar.quest.Sharlie_captive_Tut.win_condition.l1.location = "Shore39";
		pchar.quest.Sharlie_captive_Tut.function = "Tutorial_Rest_Delay";
		pchar.quest.Sharlie_captive.win_condition.l1 = "HardHour";
		pchar.quest.Sharlie_captive.win_condition.l1.hour = 19.00;
		pchar.quest.Sharlie_captive.function = "Captive_Timer";
		SetFunctionTimerCondition("Captive_CreatePiratesOver", 0, 0, 1, false);
		AddQuestRecord("SharlieD", "1");
		pchar.questTemp.Sharlie = "bankskiperfight";
		pchar.questTemp.Sharlie.Captive = "true";
		pchar.questTemp.Sharlie.Captive.Name = GetFullName(npchar);
		DeleteAttribute(pchar, "GenQuest.CannotWait"); // можно мотать время
		// Rebbebion, новые марки до места назначения
		QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
		QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
		QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
		QuestPointerToLoc("martinique_jungle_02", "reload", "reload2_back");
		QuestPointerToLoc("martinique_jungle_03", "reload", "reload2_back");
		break;

	case "Sharlie_14":
		pchar.quest.Sharlie_captive1.over = "yes";
		pchar.quest.Sharlie_captive2.over = "yes";
		pchar.quest.Sharlie_captive3.over = "yes";
		// Rebbebion, новые марки до места назначения
		QuestPointerDelLoc("shore39", "reload", "reload1_back");
		QuestPointerDelLoc("martinique_jungle_03", "reload", "reload2_back");
		QuestPointerDelLoc("martinique_jungle_02", "reload", "reload2_back");
		QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
		QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
		QuestPointerDelLoc("fortfrance_town", "reload", "reload8_back");
		DelLandQuestMark(npchar);
		ref sld = characterFromId("CaptiveSpain");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 5.0);
		sld.lifeday = 0;
		SetNationRelation2MainCharacter(FRANCE, RELATION_FRIEND);
		DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
		dialog.text = "¡Maravilloso! Me complace mucho que hayas podido manejarlo con éxito. Supongo que no necesito saber los detalles de la operación, ¿verdad? Así que, mi querido huésped español puede ahora sentirse seguro en mi hogar...";
		link.l1 = "¿Qué pasa con la deuda de Folke Deluc?";
		link.l1.go = "Sharlie_15";
		break;

	case "Sharlie_15":
		dialog.text = "Por supuesto, sí. Toma su pagaré, ahora tienes derecho a su deuda y puedes pedirle dinero. Bueno, y por supuesto, solicita su liberación de la prisión. ¿He hecho todo como prometí?";
		link.l1 = "Sí, monsieur. Todo está estrictamente de acuerdo con el trato. Ahora permítame retirarme.";
		link.l1.go = "Sharlie_4";
		AddQuestRecord("SharlieD", "7");
		CloseQuestHeader("SharlieD");
		DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
		break;

	case "Sharlie_repeat":
		dialog.text = "Entonces, ¿estás listo para pagar su deuda?";
		if (sti(pchar.money) >= 10450)
		{
			link.l1 = "Sí. Aquí está el dinero.";
			link.l1.go = "Sharlie_3";
		}
		link.l2 = "Lamentablemente, todavía no he reunido la suma requerida...";
		link.l2.go = "exit";
		break;

	case "Sharlie_junglejew":
		dialog.text = "Hm. Parece que tienes razón, estos son pendientes caros y fueron hechos en el Viejo Mundo con seguridad... ¿Qué puedo decir? Te daré por ellos treinta... no, incluso treinta y cinco doblones de oro. Toma el dinero, no los venderás por más.";
		link.l1 = "¿Treinta y cinco doblones? Ese no es un mal precio. Estoy de acuerdo. Aquí tienes.";
		link.l1.go = "Sharlie_junglejew_1";
		link.l2 = "No. Creo que me quedaré estos pendientes para mí.";
		link.l2.go = "exit";
		npchar.quest.junglejew = "true";
		break;

	case "Sharlie_junglejew_1":
		DialogExit();
		PlaySound("interface\important_item.wav");
		Log_Info("¡Le has entregado los pendientes!");
		RemoveItems(pchar, "jewelry25", 1);
		TakeNItems(pchar, "gold_dublon", 35);
		AddQuestRecord("SharlieE", "3");
		CloseQuestHeader("SharlieE");
		DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
		if (!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
		{
			DelLandQuestMark(characterFromId("FortFrance_Mayor"));
		}
		break;

	//--> Миниквест "Делюк"
	case "Del_Deluck":
		DeleteAttribute(pchar, "questTemp.Del_Rostovshik");
		dialog.text = "Lo sé, lo sé, capitán. Parece que su navegante ha acumulado deudas en casi todas las colonias francesas. A decir verdad, lo sabía desde hace mucho tiempo. Consulté con mis colegas, un procedimiento estándar, ya ve...";
		link.l1 = "¿Y no pensaste que era lo suficientemente importante como para informarme durante nuestro acuerdo anterior?";
		link.l1.go = "Del_Deluck_2";
		break;

	case "Del_Deluck_2":
		dialog.text = "¿Por qué? En ese momento, me preocupaba principalmente la deuda de Deluc conmigo, que, por cierto, era la mayor. Una vez que la saldaste, notifiqué prontamente a mis colegas... Tenemos una vasta flota de mensajeros profesionales, así que no pasó mucho tiempo antes de que acumulara un montón de facturas de Deluc en mi escritorio.";
		link.l1 = "Ya veo... Los compraste sabiendo que tengo un interés vital en él y los medios para pagar... Esto es extorsión, monsieur.";
		link.l1.go = "Del_Deluck_3";
		break;

	case "Del_Deluck_3":
		dialog.text = "¡Son solo negocios, capitán! La deuda total de Deluc es de cien doblones, y los intereses están acumulándose... ¿Está dispuesto a pagar?";
		link.l1 = "Aún no estoy preparado para responder, pero lo consideraré. ¡Adiós!";
		link.l1.go = "Del_Deluck_4";
		break;

	case "Del_Deluck_4":
		DialogExit();

		pchar.questTemp.Del_Rostovshik_repeat = true;
		sld = CharacterFromID("Tichingitu");
		if (sld.location == pchar.location && !LAi_IsDead(sld))
		{
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.dialog.currentnode = "Del_Deluck";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		}
		break;

	case "Del_Deluck_5":
		dialog.text = "¡Excelente! Sabes qué hacer a continuación, igual que la última vez. Aquí están los documentos, preséntalos al comandante de la prisión. Ha sido un placer hacer negocios contigo, capitán.";
		link.l1 = "No hay mucho que disfrutar de esta situación. Adiós.";
		link.l1.go = "exit";
		RemoveItems(pchar, "gold_dublon", 100);
		DeleteAttribute(pchar, "questTemp.Del_Rostovshik_repeat");
		Log_Info("¡Has recibido una letra de deuda!");
		PlaySound("interface\important_item.wav");
		GiveItem2Character(pchar, "letter_open");
		ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
		pchar.questTemp.Del_DeluckSvoboda = true;
		AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
		DelLandQuestMark(npchar);
		break;
		//<-- Миниквест "Делюк"
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

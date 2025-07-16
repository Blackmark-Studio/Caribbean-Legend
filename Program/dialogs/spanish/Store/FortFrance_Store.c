// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat("Adelante, ¿qué deseas?", "Justo estábamos hablando de eso. Debes haberlo olvidado...", "Esta es la tercera vez hoy que hablas de alguna pregunta...", "Escucha, esta es una tienda. La gente compra cosas aquí. ¡No me molestes!", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Sabes, " + NPChar.name + ", tal vez la próxima vez.", "Claro, lo he olvidado por alguna razón...", "Sí, realmente es la tercera vez...", "Hm, yo no...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		/* //--> Бремя гасконца
		if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
		{
			Link.l1 = "Escuche, monsieur, estoy buscando un trabajo. No como un trabajo a tiempo completo o cargar sacos de carga, sino más bien hacer recados, por así decirlo. ¿Por casualidad necesita asistencia?";
			Link.l1.go = "Sharlie_storehelper";
		}
		if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
		{
			Link.l1 = "He completado tu encargo. Encontré a Gralam Lavoie.";
			Link.l1.go = "Sharlie_storehelper_2";
		}
		if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
		{
			Link.l1 = "Conozca a su nuevo asistente, monsieur.";
			Link.l1.go = "Sharlie_storehelper_11";
		}
		if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
		{
			Link.l1 = "Soy yo otra vez, monsieur. He venido por mi recompensa.";
			Link.l1.go = "Sharlie_storehelper_13";
		}
		if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
		{
			link.l1 = "Échele un vistazo a estos pendientes, monsieur. Los encontré en el cuerpo de un bandido que fue asesinado en la jungla. Es evidentemente obra de un fino joyero que, estoy seguro, no es de por aquí. ¿Hay algo que pueda decir sobre estos pendientes?";
			link.l1.go = "Sharlie_junglejew";
		}
		//<-- Бремя гасконца */
		break;

	//--> Бремя гасконца
	case "Sharlie_storehelper":
		if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "")
		{
			dialog.text = "Disculpe, señor, pero ¿dónde está su espada? No es seguro salir de la ciudad sin un arma. ¡Nunca se sabe lo que podría suceder en la jungla!";
			link.l1 = "¡Maldita sea, lo olvidé por completo! ¡Todo ha sido llevado!";
			link.l1.go = "Store_noweapon";
			break;
		}
		DelLandQuestMark(npchar);
		QuestPointerDelLoc("Fortfrance_town", "reload", "reload6_back");
		dialog.text = "¿Un trabajo? Hm. Supongo que tengo un trabajo que podría interesarte. Mi asistente ha desaparecido, solía trabajar en mi almacén. Lleva una semana desaparecido y esto es muy molesto, porque me veo obligado a hacer sus tareas y no tengo tiempo.\nPor favor, encuentra a este idiota y averigua por qué demonios abandonó su trabajo. O mejor aún, tráemelo de vuelta. Te pagaré mil piezas de a ocho.";
		link.l1 = "De acuerdo, estoy dentro. Dime su nombre y descríbeme su apariencia. ¿Tienes alguna idea de dónde buscarlo?";
		link.l1.go = "Sharlie_storehelper_1";
		link.l2 = "¿Buscar a un hombre Dios sabe dónde por un miserable millar? ¡Debes estar bromeando!";
		link.l2.go = "Sharlie_storehelper_exit";
		npchar.quest.storehelper = "true";
		break;

	case "Sharlie_storehelper_exit":
		AddTimeToCurrent(2, 0);
		LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false); // пу откр
		dialog.text = "Hola, monsieur. ¿Quién está buscando trabajo, tú o yo? Si no quieres, no te estoy obligando. Que tengas un buen día.";
		link.l1 = "Hm... Creo que iré a ver a la autoridad portuaria. Quizás allí ofrezcan algo más sustancial.";
		link.l1.go = "exit";
		break;

	case "Sharlie_storehelper_1":
		dialog.text = "Se llama Gralam Lavois. ¿Su aspecto? Treinta y cinco años, barba y bigote, largo abrigo marrón, camisa blanca. Ah, y siempre lleva ese ridículo sombrero de tres picos, pretende ser un almirante con un ancla en el trasero.\nNo está en Saint-Pierre, he revisado toda la ciudad. Debe estar en las selvas, o en Les Francois escondiéndose con los piratas que merodean por allí.\nPor otro lado, es probable que esté en el asentamiento pirata de Le Francois, que se encuentra en la parte oriental de nuestra isla. Tal vez esté charlando con los piratas allí, o pasando el rato en la taberna, o discutiendo con el comerciante en la tienda.\n¿Cómo llegar a Le Francois? Salga por las puertas de la ciudad hacia la selva, en el cruce de caminos, tome el camino de la izquierda, luego siga la carretera hasta que gire a la derecha, y luego tome el pasaje de la izquierda entre las rocas, y encontrará Le Francois. No creo que se pierda.";
		link.l1 = "Bien. Me pondré a buscar. Tan pronto como surja algo, te informaré de inmediato.";
		link.l1.go = "exit";
		AddQuestRecord("SharlieA", "1");
		pchar.questTemp.Sharlie.Storehelper = "true";
		pchar.questTemp.Sharlie.Storehelper.Chance = rand(2);
		AddDialogExitQuestFunction("Sharlie_CreateStorehelper");
		// Rebbebion, новые марки до места назначения
		QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
		QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
		QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
		QuestPointerToLoc("martinique_jungle_02", "reload", "reload3_back");
		QuestPointerToLoc("lefransua_exittown", "reload", "reload1_back");
		break;

	case "Sharlie_storehelper_2":
		DelLandQuestMark(npchar);
		// Rebbebion, новые марки до места назначения
		QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
		QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
		QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
		QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
		QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
		QuestPointerDelLoc("fortfrance_town", "reload", "reload6_back");
		dialog.text = "¿Ah, sí? ¿Y dónde está él?";
		link.l1 = "Lo he encontrado en Le Francois. Ya no va a trabajar para usted. También añadió muchas cosas bastante picantes sobre usted... ¿Le interesaría escucharlas?";
		link.l1.go = "Sharlie_storehelper_3";
		break;

	case "Sharlie_storehelper_3":
		dialog.text = "No. Ahórrame los detalles... ¡Qué pena! ¿Qué voy a hacer ahora sin un asistente?";
		link.l1 = "Contrata a alguien más. ¿O realmente es tan grande el problema como dijo Gralam?";
		link.l1.go = "Sharlie_storehelper_4";
		break;

	case "Sharlie_storehelper_4":
		dialog.text = "Pura mala suerte, en verdad. ¿Y qué dijo ese holgazán?";
		link.l1 = "Bueno, para empezar, obviamente no está perdiendo el tiempo, je-je. Dijo que nadie en todo Saint-Pierre se alistaría para servirte porque... no pagas lo suficiente a tus trabajadores. Sí, por cierto, " + npchar.name + ", debes mil pesos como prometido.";
		link.l1.go = "Sharlie_storehelper_5";
		break;

	case "Sharlie_storehelper_5":
		AddMoneyToCharacter(pchar, 1000);
		dialog.text = "Por favor, toma tu dinero. ¡Ja! ¡No pagan lo suficiente! Por supuesto, nadie quiere trabajar para mí. El bastardo hizo todo lo posible para difundir habladurías sucias. ¿Qué puedo hacer? ¡No puedo hacerlo todo solo!\nNo puedo irme a dormir hasta que cuente cada pieza de carga porque esos malditos trabajadores siempre roban algo. Después de la última carga me faltan cinco barriles de ron. Estoy seguro de que los trabajadores los 'tomaron por error'...";
		link.l1 = "Bueno, no sé qué aconsejar. Está bien, todo lo mejor. Es hora de que me vaya.";
		link.l1.go = "Sharlie_storehelper_6";
		break;

	case "Sharlie_storehelper_6":
		dialog.text = "¡Espera! Creo que puedes ayudarme. Si fuiste capaz de encontrar a ese bastardo, entonces bien podrías ser capaz de...";
		link.l1 = "¿Y qué podría hacer, me pregunto, si nadie en esta ciudad te cree? Soy nuevo aquí y...";
		link.l1.go = "Sharlie_storehelper_7";
		break;

	case "Sharlie_storehelper_7":
		dialog.text = "Déjeme terminar, monsieur. Ha estado en Le Francois. Me gustaría que fuera allí de nuevo y tratara de encontrar un empleado para mí. Quizás, Gralam no arruinó completamente mi reputación en este nido de piratas.\nEl trabajo es sencillo: contar carga y vigilar a los trabajadores del puerto para evitar robos. A veces hacer mi trabajo aquí en lugar mío mientras estoy fuera, por una tarifa extra, por supuesto.\nDígales que ofrezco una habitación en la tienda para vivir y quinientas piezas de a ocho por semana. ¡Monsieur, iba a expandir mi negocio y las cosas finalmente van bien, necesito un asistente!\nPor cierto, es mejor buscar ayuda para encontrar un trabajador del tabernero, Cesare Craig. Ese bribón seguramente le ayudará, aunque no gratis, a encontrar individuos que estarían interesados en trabajar para mí.";
		link.l1 = "Mm. Puedo intentarlo, aunque no estoy seguro... ¿Cuánto me pagarás por el trabajo?";
		link.l1.go = "Sharlie_storehelper_8";
		break;

	case "Sharlie_storehelper_8":
		dialog.text = "Eso dependerá de qué trabajador puedas contratar. Cuanto mejor resulte ser, más te pagaré por tus esfuerzos. Eso es justo, ¿no es así?";
		link.l1 = "¿No crees que me estás obligando a ir a ciegas? ¿Cómo voy a saber cómo vas a evaluar a un trabajador? Podrías categorizar a cualquiera como malo o...";
		link.l1.go = "Sharlie_storehelper_9";
		break;

	case "Sharlie_storehelper_9":
		dialog.text = "¡Monsieur! Muy bien puede ser correcto llamarme un poco tacaño, ¡pero nadie podría llamarme deshonesto! Si te digo que pagaré por tus esfuerzos dependiendo de cómo resulte, lo digo en serio. Míralo también desde mi punto de vista. Podrías traerme aquí a algún gitano perezoso que no solo se escaquearía y no haría nada, ¡sino que incluso podría robarme por la noche!";
		link.l1 = "Está bien. Estoy de acuerdo. Te tomaré la palabra, " + npchar.name + ". Me aseguraré de no traer de vuelta a ningún gitano.";
		link.l1.go = "Sharlie_storehelper_10";
		break;

	case "Sharlie_storehelper_10":
		DialogExit();
		SetLaunchFrameFormParam("Vuelve a Le Francois...", "Reload_To_Location", 0, 3.0);
		SetLaunchFrameReloadLocationParam("LeFransua_tavern", "reload", "reload1", "SharlieA_TeleportLF");
		LaunchFrameForm();
		break;

	case "Sharlie_storehelper_11":
		dialog.text = "¿Has encontrado un trabajador para mí? Maravilloso. Permíteme hablar con él, vuelve en una hora para recibir tu recompensa.";
		link.l1 = "Está bien. Volveré en una hora.";
		link.l1.go = "Sharlie_storehelper_12";
		DelLandQuestMark(npchar);
		break;

	case "Sharlie_storehelper_12":
		chrDisableReloadToLocation = false; // открыть локацию
		pchar.questTemp.Sharlie.Storehelper = "final";
		DialogExit();
		SetLaunchFrameFormParam("Una hora más tarde...", "", 0, 5);
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 1, 0); // крутим время
		RecalculateJumpTable();
		AddQuestRecord("SharlieA", "5");
		AddLandQuestMark(npchar, "questmarkmain");
		break;

	case "Sharlie_storehelper_13":
		switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
		{
		case 0:
			AddMoneyToCharacter(pchar, 3000);
			dialog.text = "Estoy bastante contento con el trabajador que has encontrado para mí, aunque habla más de lo que hace, pero no te preocupes, le quitaré lo parlanchín a golpes en algún momento. Tu recompensa son tres mil piezas de a ocho. Aquí tienes.";
			link.l1 = "¡Gracias! Dígame, Monsieur, ¿sabe si alguien más en el pueblo podría necesitar ayuda con algún asunto importante?";
			link.l1.go = "Sharlie_storehelper_14a";
			break;

		case 1:
			AddMoneyToCharacter(pchar, 5000);
			dialog.text = "¡Has logrado encontrar un trabajador verdaderamente valioso! Es incluso mejor que ese bribón de Gralam. Estoy muy, muy complacido, señor. Aquí, tome su recompensa: cinco mil piezas de a ocho.";
			link.l1 = "¡Gracias! Dígame, Monsieur, ¿sabe si hay alguien más en el pueblo que necesite ayuda con algún asunto importante?";
			link.l1.go = "Sharlie_storehelper_14a";
			break;

		case 2:
			AddMoneyToCharacter(pchar, 4000);
			dialog.text = "Has encontrado un buen trabajador. Y aunque no conoce todos los trucos del oficio, estoy seguro de que se las arreglará sin mucho problema. Estoy complacido contigo, señor. Aquí, toma tu recompensa: cuatro mil piezas de a ocho.";
			link.l1 = "¡Gracias! Dígame, Monsieur, ¿sabe si alguien más en la ciudad podría necesitar ayuda con algún asunto importante?";
			link.l1.go = "Sharlie_storehelper_14a";
			break;
		}
		break;

	case "Sharlie_storehelper_14a":
		LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false); // пу откр
		dialog.text = "Hmm... Hace poco vi al maestro del puerto, claramente molesto, dirigiéndose a la autoridad portuaria. Habla con él, quién sabe qué pudo haber pasado.";
		link.l1 = "Haré justo eso. Gracias, monsieur.";
		link.l1.go = "Sharlie_storehelper_14";
		DelLandQuestMark(npchar);
		break;

	case "Sharlie_storehelper_14":
		DialogExit();
		DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
		CloseQuestHeader("SharlieA");

		QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
		QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
		QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
		QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
		QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
		QuestPointerDelLoc("fortfrance_town", "reload", "reload6_back");

		QuestPointerToLoc("fortfrance_town", "reload", "reload10_back");
		break;

	case "Sharlie_junglejew":
		dialog.text = "Bueno, ¿qué se supone que debo decir, magníficos pendientes? Puedo darte... veamos... cuatro mil piezas de a ocho por ellos. Dudo que alguien te ofrezca más. ¿Tenemos un trato?";
		link.l1 = "¡Trato hecho! Son tuyos.";
		link.l1.go = "Sharlie_junglejew_1";
		link.l2 = "No. Creo que me quedaré con estas joyas.";
		link.l2.go = "exit";
		npchar.quest.junglejew = "true";
		break;

	case "Sharlie_junglejew_1":
		DialogExit();
		PlaySound("interface\important_item.wav");
		Log_Info("¡Le has entregado los pendientes!");
		RemoveItems(pchar, "jewelry25", 1);
		AddMoneyToCharacter(pchar, 4000);
		AddQuestRecord("SharlieE", "4");
		CloseQuestHeader("SharlieE");
		DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
		if (!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
		{
			DelLandQuestMark(characterFromId("FortFrance_Mayor"));
		}
		break;

	case "Store_noweapon":
		dialog.text = "Eso no servirá. Te sugiero que te acerques a nuestro gobernador y le pidas su ayuda.";
		link.l1 = "Gracias por el consejo. Eso es lo que planeo hacer.";
		link.l1.go = "exit";
		break;
		//<-- Бремя гасконца
	}
	UnloadSegment(NPChar.FileDialog2);
}

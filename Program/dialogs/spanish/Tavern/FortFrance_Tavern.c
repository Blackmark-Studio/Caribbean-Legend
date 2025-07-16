// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?", "¿Cómo puedo ayudarte, " + GetAddress_Form(NPChar) + "?"), "Intentaste hacerme una pregunta hace no mucho, " + GetAddress_Form(NPChar) + "...", "Durante todo este día, esta es la tercera vez que hablas de alguna pregunta...", "¿Más preguntas, supongo?", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No tengo nada de qué hablar en este momento."), "Umph, ¿dónde se ha ido mi memoria...?", "Sí, realmente es la tercera vez...", "No, ¿qué preguntas?...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		/* //--> Jason, Бремя гасконца
		if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
		{
			link.l1 = "Monsieur, estoy buscando trabajo. ¿Tienes algún empleo?";
			link.l1.go = "Sharlie_rum";
		}
		if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
		{
			link.l1 = "He cumplido con tu misión. El bote con el ron ha sido entregado en la Bahía de Le Francois, y entregado a tu gente.";
			link.l1.go = "Sharlie_rum_5";
		}
		//<-- Бремя гасконца */

		// Jason, Португалец
		if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToMartinique" && !CheckAttribute(npchar, "quest.Portugal"))
		{
			link.l1 = "Necesito alquilar una de tus habitaciones por dos o tres días. Tengo un hombre a bordo que está herido. Necesita descansar y recuperarse.";
			link.l1.go = "Portugal";
		}
		if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernorEnd")
		{
			link.l1 = "Dime, la persona a la que le alquilé una habitación... ¿se ha ido? Prometió esperarme, pero la habitación está vacía.";
			link.l1.go = "Portugal_2";
		}
		// Португалец
		//  Jason Долго и счастливо
		if (!CheckAttribute(npchar, "quest.LongHappy") && CheckAttribute(PChar, "questTemp.LongHappy.MarryRum") && LongHappy_CheckTavernGoods())
		{
			link.l1 = "Voy a organizar una fiesta para mis hombres. Supongo que ya lo sabes, ¿verdad?";
			link.l1.go = "LH_tavern_SP";
		}
		if (CheckAttribute(npchar, "quest.LongHappy.Nomoney") && LongHappy_CheckTavernGoods() && sti(Pchar.money) >= 100000 + sti(pchar.questTemp.LongHappy.MarryMoney))
		{
			link.l1 = "Traje todo lo necesario para nuestra celebración.";
			link.l1.go = "LH_tavern_SP_3";
		}
		break;

	//--> Jason, Бремя гасконца
	case "Sharlie_rum":
		DelLandQuestMark(npchar);
		dialog.text = "¿Trabajo? Hm... Pareces tener algo de cerebro, muchacho. Puede que tenga algo para ti.\nEste trabajo puede parecer fácil, pero requiere responsabilidad e inteligencia. No puedo confiar en estos idiotas para hacer negocios, seguro que lo arruinarán...";
		link.l1 = "Escucha, ¿puedes por favor decirme qué demonios quieres asignarme? Lo juro, no te defraudaré, o al menos haré lo mejor que pueda.";
		link.l1.go = "Sharlie_rum_1";
		break;

	case "Sharlie_rum_1":
		switch (rand(4))
		{
		case 0:
			pchar.questTemp.Sharlie.Rum.Pass = "El viejo Thomas se ha cansado de esperar la cerveza";
			break;
		case 1:
			pchar.questTemp.Sharlie.Rum.Pass = "Las tablas y el roble estarán aquí por la mañana.";
			break;
		case 2:
			pchar.questTemp.Sharlie.Rum.Pass = "No esperes al viento del sur";
			break;
		case 3:
			pchar.questTemp.Sharlie.Rum.Pass = "La bahía está lista para el desembarco";
			break;
		case 4:
			pchar.questTemp.Sharlie.Rum.Pass = "Los camellos van hacia el norte";
			break;
		}
		dialog.text = "Bien. Necesito a alguien para entregar varias cajas de fino ron de Jamaica a mi taberna. Aquí está el asunto, los aranceles de importación reducen mis márgenes y mis mejores clientes están sedientos, así que debemos actuar con astucia para evitar a los oficiales de aduanas. El lugre 'Fantasma' llegará frente a Martinica esta noche.\nDejarán caer el ancla no lejos de la Bahía de Lamentin. Debes encontrar esta embarcación y subir a bordo. Te proporcionaré un bote y cinco marineros, ellos seguirán tus órdenes.\nUna vez a bordo, un hombre se acercará a ti. Tendrás que decirle una contraseña: '" + pchar.questTemp.Sharlie.Rum.Pass + "'\nLa respuesta será '¿Por qué no tomar un ron, marinero?'. Tendrás solo un intento, así que anótalo y no cometas un error o el trato se cancelará. Por eso no puedo confiarlo a esos idiotas sin cerebro que navegarán contigo. Repite la contraseña.";
		link.l1 = "'" + pchar.questTemp.Sharlie.Rum.Pass + "'.";
		link.l1.go = "Sharlie_rum_2";
		break;

	case "Sharlie_rum_2":
		dialog.text = "Estupendo. Repítelo para ti mismo unas cuantas veces más, o mejor aún, escríbelo en algún lugar. Después de que menciones la contraseña al capitán del lugre, las cajas con botellas de ron serán cargadas en la embarcación, la cual necesitarás navegar hasta la bahía del asentamiento pirata Le Francois, allí te recibirán.\nEsa es toda la tarea. Puedes llegar de la Bahía de Le Francois a Saint-Pierre a pie, la tartana se quedará en la bahía. Te pagaré cinco mil piezas de a ocho una vez que esté hecho el trabajo.";
		link.l1 = "El contrabando suena tanto emocionante como lucrativo. Haré lo que me dijiste que hiciera. ¿Dónde está el bote?";
		link.l1.go = "Sharlie_rum_3";
		link.l2 = "Entonces, ¿me propones que me dedique al contrabando? Hm... Sabes, no puedo arriesgar mi nombre. Tendrás que disculparme, fingiremos que no he oído nada.";
		link.l2.go = "Sharlie_rum_exit";
		break;

	case "Sharlie_rum_exit":
		dialog.text = "Como desees, monsieur. No tengo otros trabajos.";
		link.l1 = "Ya veo. Entonces, todo lo mejor, " + npchar.name + ".";
		link.l1.go = "exit";
		DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
		SetCurrentTime(23, 0);
		Sharlie_removeLocks("");
		break;

	case "Sharlie_rum_3":
		dialog.text = "La tartana estará en el muelle a las siete de la tarde. La tripulación en el bote es hábil, así que deberías llegar al lugre rápidamente. Toda la tarea no debería tomar más de cuatro horas, estoy seguro de que estarás de vuelta en Saint-Pierre para las once de la noche. Toma este catalejo, es un pedazo de basura pero es mejor que nada. La Bahía Lamentin está ubicada en la parte norte de la isla, así que al salir del puerto, mantén el rumbo al norte. ¡Buena suerte!";
		link.l1 = "De acuerdo, lo tengo. Nos vemos pronto, " + npchar.name + ".";
		link.l1.go = "Sharlie_rum_4";
		break;

	case "Sharlie_rum_4":
		DialogExit();
		AddQuestRecord("SharlieB", "1");
		AddQuestUserData("SharlieB", "sPassword", pchar.questTemp.Sharlie.Rum.Pass);
		GiveItem2Character(pchar, "spyglass1");
		Log_Info("¡Has recibido un catalejo!");
		PlaySound("interface\important_item.wav");
		if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart"))
		{
			GiveItem2Character(pchar, "map_martiniqua");
			Log_Info("Has recibido un mapa de Martinica");
			RefreshEquippedMaps(GetMainCharacter());
		}
		/* pchar.quest.Sharlie_rum.win_condition.l1 = "location";
		pchar.quest.Sharlie_rum.win_condition.l1.location = "Fortfrance_town"; */
		// pchar.quest.Sharlie_rum.win_condition.l1.locator_group = "rld";
		// pchar.quest.Sharlie_rum.win_condition.l1.locator = "loc0";
		pchar.quest.Sharlie_rum.win_condition.l1 = "HardHour";
		pchar.quest.Sharlie_rum.win_condition.l1.hour = 19.00;
		pchar.quest.Sharlie_rum.function = "Rum_CreateBarkas";
		SetFunctionTimerCondition("Rum_CreateBarkasOver", 0, 0, 1, false);
		pchar.questTemp.Sharlie.Rum = "true";
		npchar.quest.Rum = "true";
		NewGameTip("¡Abre tu inventario (F1) y equipa el catalejo!");
		pchar.quest.NgtBarkas.win_condition.l1 = "location";
		pchar.quest.NgtBarkas.win_condition.l1.location = "Fortfrance_town";
		pchar.quest.NgtBarkas.win_condition.l2 = "HardHour";
		pchar.quest.NgtBarkas.win_condition.l2.hour = 19.00;
		pchar.quest.NgtBarkas.function = "NgtBarkas";
		AddTimeToCurrent(1, 30);
		QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
		QuestPointerToLoc("fortfrance_town", "reload", "reload1_back");
		break;

	case "Sharlie_rum_5":
		dialog.text = "¡Maravilloso! Sabía que podía contar contigo. ¿Fue difícil?";
		link.l1 = "Bueno, eso depende de cómo definas duro...";
		link.l1.go = "Sharlie_rum_6";
		break;

	case "Sharlie_rum_6":
		dialog.text = "Bueno, aquí está tu recompensa: cinco mil pesos. Puedes quedarte con el catalejo. Y también, otro pequeño presente, por favor, toma estas tres botellas de ron. Después de probarlo, entenderás por qué hay tanta demanda por él.";
		link.l1 = "¡Gracias! ¡Fue un placer trabajar contigo! ¡Hasta luego!";
		link.l1.go = "Sharlie_rum_7";
		break;

	case "Sharlie_rum_7":
		DialogExit();
		AddMoneyToCharacter(pchar, 5000);
		TakeNItems(pchar, "potionrum", 3);
		AddQuestRecord("SharlieB", "5");
		CloseQuestHeader("SharlieB");
		DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
		// Rebbebion, новые марки до места назначения
		QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
		QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
		QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
		QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
		QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
		QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
		DelLandQuestMark(npchar);
		if (!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))
		{
			pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
			pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
			pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
			pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
		}
		break;
	//<-- Бремя гасконца

	// Португалец
	case "Portugal":
		dialog.text = "Sin problema, tengo una habitación. Por 50 pesos, es tuya por tres días.";
		if (sti(pchar.money) >= 50)
		{
			link.l1 = "Aquí tienes.";
			link.l1.go = "Portugal_1";
		}
		else
		{
			link.l1 = "Iré a tomar el dinero del tesorero y regresaré.";
			link.l1.go = "exit";
		}
		break;

	case "Portugal_1":
		ref sld;
		DialogExit();
		AddMoneyToCharacter(pchar, -50);
		npchar.quest.Portugal = "true";
		LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", false);
		pchar.quest.Portugal_Ill3.over = "yes";
		LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", true);
		LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", true);
		LocatorReloadEnterDisable("Fortfrance_town", "gate_back", true); // закрыть выходы из города
		sld = characterFromId("Portugal");
		ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto3");
		sld = characterFromId("PortugalDoctor");
		ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto1");
		pchar.quest.Portugal_tavernroom.win_condition.l1 = "location";
		pchar.quest.Portugal_tavernroom.win_condition.l1.location = "FortFrance_tavern_upstairs";
		pchar.quest.Portugal_tavernroom.function = "PortugalInTavernRoom";
		break;

	case "Portugal_2":
		dialog.text = "No diría que se levantó y salió de la habitación por sí mismo, monsieur. Algunas personas vinieron por aquí ayer. Uno de ellos era un hombre alto, flaco y tuerto, obviamente un bandido por su aspecto, y también un hombre con ceceo, parecía un castellano. Me sorprendió, pero ese ceceoso me miró... como si fuera un piojo antes de machacarlo. Y preguntaron por tu amigo... y les conté. ¿Qué más se supone que debía hacer?";
		link.l1 = "Lo sé, " + npchar.name + ", no eres un héroe, eso es cierto. ¿Qué más viste? ¿Adónde fueron?";
		link.l1.go = "Portugal_3";
		break;

	case "Portugal_3":
		dialog.text = "Eso es todo... espera, ¡no!... El tuerto dijo algo sobre un carro. Supongo que tomaron un carro y arrastraron a tu amigo hasta el otro lado de la isla. Eso es todo, monsieur, lo juro... Llamaría a la guardia, pero ese ceceante me dijo que tenía una esposa hermosa antes de irse... ¿Ves? Si se enteran de que te conté todo esto, ellos...";
		if (pchar.money >= 1000)
		{
			link.l1 = "No temas, no oirán nada de mí aparte de balas. Realmente me has ayudado, gracias. Aquí, toma 1000 pesos como recompensa.";
			link.l1.go = "Portugal_4";
		}
		link.l2 = "No es mucho, pero gracias de todos modos. La próxima vez llama a la guardia y no seas tan pardillo.";
		link.l2.go = "Portugal_5";
		break;

	case "Portugal_4":
		AddMoneyToCharacter(pchar, -1000);
		dialog.text = "Gracias, monsieur. Puedo darte mi palabra de que tu amigo casi se ha recuperado. Al menos estaba caminando por sí mismo. Y el otro hombre, ese silencioso holandés, entró desde afuera en ese momento, vio todo ese lío y saltó hacia afuera, simplemente desapareció después.";
		link.l1 = "Diría que ya ha partido en el primer barco que pudo tomar. Gracias por la información, es hora de que me vaya.";
		link.l1.go = "Portugal_6";
		break;

	case "Portugal_5":
		dialog.text = "No todos los hombres pueden ser héroes con su espada desenvainada, capitán.";
		link.l1 = "Bueno... esa es la elección del hombre.";
		link.l1.go = "Portugal_6";
		break;

	case "Portugal_6":
		DialogExit();
		sld = characterFromId("Avendel");
		sld.dialog.currentnode = "Avendel_seapatrol_9";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
	// Португалец

	// Jason Долго и счастливо
	case "LH_tavern_SP":
		npchar.quest.LongHappy = "true";
		dialog.text = "Sí, tu asistente pasó por aquí, pero le dije y te repetiré a ti, me acostumbré a las multitudes de marineros borrachos, pero sé cómo van tus fiestas. Lo que quede se parecerá a Amberes después de la visita de los tercios españoles. Estaré feliz si las paredes siguen en pie. Así que, si quieres que la multitud se pelee, necesitaré un depósito no reembolsable además de lo que ya has traído. En caso de consecuencias, por así decirlo.";
		link.l1 = "¡Zorro astuto! Yo mismo he estado bebiendo con lobos de mar durante muchos años, he estado en diferentes... establecimientos, ¡y sé que con el dinero que traje podríamos reconstruir tu taberna desde cero! Aprovechando la oportunidad, ¿eh? Está bien, tengo una boda, y no estoy de humor para molestarme con cosas tan pequeñas, ¿cuánto quieres?";
		link.l1.go = "LH_tavern_SP_1";
		break;

	case "LH_tavern_SP_1":
		dialog.text = "Otras 100 000 piezas de a ocho deberían ser suficientes y no te preocupes, haré todo de la mejor manera posible. ¡Tus muchachos recordarán esta fiesta por mucho tiempo, recuerda mi palabra!";
		if (sti(Pchar.money) >= 100000 + sti(pchar.questTemp.LongHappy.MarryMoney))
		{
			link.l1 = "Tienes que esforzarte de verdad, es una ocasión especial, ¿entiendes? Y sí, después de la celebración, no vengas a mí con quejas, incluso si tu taberna se incendia.";
			link.l1.go = "LH_tavern_SP_4";
		}
		else
		{
			link.l1 = "¡Ya parece que estoy organizando la boda de un rey! Espera, volveré pronto.";
			link.l1.go = "LH_tavern_SP_2";
		}
		break;

	case "LH_tavern_SP_2":
		DialogExit();
		npchar.quest.LongHappy.Nomoney = "true";
		break;

	case "LH_tavern_SP_3":
		dialog.text = "¡Tus muchachos recordarán esta fiesta durante mucho tiempo, recuerda mis palabras!";
		link.l1 = "Tienes que esforzarte de verdad, es una ocasión especial, ¿entiendes? No vengas llorando a mí si mis muchachos accidentalmente incendian tu taberna.";
		link.l1.go = "LH_tavern_SP_4";
		break;

	case "LH_tavern_SP_4":
		DialogExit();
		RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.questTemp.LongHappy.MarryRum));
		AddMoneyToCharacter(pchar, -sti(pchar.questTemp.LongHappy.MarryMoney));
		AddMoneyToCharacter(pchar, -100000);
		DeleteAttribute(npchar, "quest.LongHappy.Nomoney");
		pchar.questTemp.LongHappy.DrinkReady = "true";
		pchar.questTemp.LongHappy.MarrySP = "true";
		DeleteAttribute(pchar, "questTemp.LongHappy.MarryMoney");
		DeleteAttribute(pchar, "questTemp.LongHappy.MarryRum");
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

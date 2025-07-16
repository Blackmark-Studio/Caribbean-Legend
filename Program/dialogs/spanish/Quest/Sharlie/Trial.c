// диалоги НПС по квесту 'Карибские нравы'
void ProcessDialogEvent()
{
	ref NPChar, sld, rColony;
	aref Link, NextDiag;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "¿Qué quieres?";
		link.l1 = "No, nada.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	// Жерар Лекруа
	case "lecrua":
		pchar.quest.Trial_LineOver.over = "yes"; // снять таймер
		dialog.text = "Buenas tardes. Usted debe ser " + GetFullName(pchar) + ".";
		link.l1 = "Tienes razón, Monsieur LeCroix. Capitán " + GetFullName(pchar) + " a su servicio. Fadey el Moscovita me lo recomendó...";
		link.l1.go = "lecrua_1";
		DelLandQuestMark(npchar);
		break;

	case "lecrua_1":
		iTemp = FindColony("Baster");
		rColony = GetColonyByIndex(iTemp);
		bOk = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		dialog.text = "Sí, sí. Mi querido amigo Fadey te describió a ti y tu situación con todo detalle. Supe que eras tú tan pronto como te vi en la puerta. Dime, capitán, ¿qué tipo de barco tienes?";
		if (sti(pchar.ship.type) == SHIP_NOTUSED || !bOk)
		{
			link.l1 = "Ah...No tengo un barco en este momento, monsieur...";
			link.l1.go = "lecrua_noship";
		}
		else
		{
			link.l1 = "Tengo un " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype), "Name"))) + ", su nombre es " + pchar.ship.name + ".";
			if (5 - sti(RealShips[sti(pchar.ship.type)].Class) < 0)
				link.l1.go = "lecrua_badship";
			else
				link.l1.go = "lecrua_2";
		}
		break;

	case "lecrua_noship":
		dialog.text = "¡Ja! Entonces, ¿qué clase de capitán eres si no tienes barco? Lo siento, monsieur, pero en ese caso no tengo trabajo que ofrecerte. ¡Que te vaya bien, dale mis saludos a Fadey!";
		link.l1 = "Mm...";
		link.l1.go = "lecrua_exit";
		sTotalTemp = "No tengo un barco en este momento";
		break;

	case "lecrua_badship":
		dialog.text = "Bueno, eso simplemente no servirá. ¡Eso no es un barco, señor, es un bote! Ay, monsieur, usted no encaja en el papel. ¡Salude a Fadey de mi parte, buen día!";
		link.l1 = "Mm...";
		link.l1.go = "lecrua_exit";
		sTotalTemp = "Mi barco no era lo suficientemente grande para él";
		break;

	case "lecrua_exit":
		DialogExit();
		npchar.lifeday = 0;
		NextDiag.CurrentNode = "lecrua_repeat";
		AddQuestRecord("Trial", "3");
		AddQuestUserData("Trial", "sText", sTotalTemp);
		CloseQuestHeader("Trial");
		DeleteAttribute(pchar, "questTemp.Trial");
		break;

	case "lecrua_repeat":
		dialog.text = "Ya hemos discutido todo, monsieur. ¿No es así?";
		link.l1 = "Oui, Monsieur LeCroix... Estoy en camino.";
		link.l1.go = "exit";
		NextDiag.TempNode = "lecrua_repeat";
		break;

	case "lecrua_2":
		dialog.text = "Excelente. En ese caso, eres adecuado para mí. ¿Estás listo para zarpar de inmediato?";
		link.l1 = "Sí, monsieur, estoy listo. ¿Qué tengo que hacer?";
		link.l1.go = "lecrua_3";
		break;

	case "lecrua_3":
		sld = characterFromId("BasTer_trader");
		dialog.text = "Debes entregar un pequeño lote de pólvora y bombas a Puerto Príncipe, en la Española francesa. El comandante lleva tiempo esperándolo, así que no pierdas tiempo, te quedan unos diez días\nRespetado " + GetFullName(sld) + "se encargará de entregarlo y cargarlo en su buque. El comandante le pagará cinco mil piezas de a ocho por el trabajo.";
		link.l1 = "¿Y eso es todo el trabajo?";
		link.l1.go = "lecrua_4";
		break;

	case "lecrua_4":
		dialog.text = "Oh de ninguna manera, monsieur. El comandante le explicará el verdadero trabajo cuando traiga las municiones. Esta carga es solo un pequeño aperitivo del trabajo que tiene por delante. Pero no tenga miedo, si hace bien el trabajo, ganará un buen dinero.";
		link.l1 = "Tiene toda mi atención, monsieur. Mi barco está listo para cargar la mercancía a bordo.";
		link.l1.go = "lecrua_5";
		break;

	case "lecrua_5":
		dialog.text = "¡No perdamos tiempo entonces, capitán! Dirígete a tu barco y prepárate para zarpar.";
		link.l1 = "¡Voy!";
		link.l1.go = "lecrua_6";
		break;

	case "lecrua_6":
		DialogExit();
		NextDiag.CurrentNode = "lecrua_repeat";
		AddQuestRecord("Trial", "4");
		pchar.questTemp.Trial = "fraht";
		AddMapQuestMarkCity("PortPax", false);
		// belamour legendary edition халява по чекбоксу
		if (!bImCasual)
			SetFunctionTimerCondition("Trial_FrahtFail", 0, 0, 17, false); // таймер
		else
			NewGameTip("Modo exploración: el temporizador está desactivado.");
		SetFunctionTimerCondition("Trial_LecruaHide", 0, 0, 1, false); // таймер
		// груз
		SetCharacterGoods(pchar, GOOD_BOMBS, GetCargoGoods(pchar, GOOD_BOMBS) + 2500);
		SetCharacterGoods(pchar, GOOD_POWDER, GetCargoGoods(pchar, GOOD_POWDER) + 2500);
		// Sinistra Пасхалка с Диего
		pchar.quest.VsD_DiegoNachalo.win_condition.l1 = "Ship_location";
		pchar.quest.VsD_DiegoNachalo.win_condition.l1.location = "PortPax_town";
		PChar.quest.VsD_DiegoNachalo.win_condition = "VsD_DiegoNachalo";

		// отключить все враждебные энкаунтеры на глобальной карте
		pchar.worldmapencountersoff = "1";
		SetFunctionTimerCondition("DelNavigatorNoShow", 0, 0, 180, false);
		pchar.systeminfo.tutorial.navigatorTrial = true;
		break;

	// Флориан Шоке
	case "florian_deck":
		if (!bImCasual)
			pchar.quest.Trial_CannonFail.over = "yes"; // belamour legendary edition снять таймер
		DelMapQuestMarkShore("shore47");
		DelLandQuestMark(npchar);
		sld = CharacterFromID("PortRoyal_shipyarder");
		if (CheckAttribute(sld, "TrialDelQuestMark"))
		{
			DeleteAttribute(sld, "TrialDelQuestMark");
			DelLandQuestMark(sld);
			DelMapQuestMarkCity("PortRoyal");
		}
		dialog.text = "¿En qué puedo ayudarle, señor?";
		link.l1 = "Buenas tardes, capitán. Usted es Florian Shoke, supongo.";
		link.l1.go = "florian_deck_1";
		break;

	case "florian_deck_1":
		dialog.text = "Lo soy. Y tú eres el paquebote de Port-au-Prince, si no me equivoco.";
		link.l1 = "¡Aye, tengo quince cañones para ti! El plazo estuvo a punto de no cumplirse, apenas lo logré...";
		link.l1.go = "florian_deck_2";
		break;

	case "florian_deck_2":
		if (GetSquadronGoods(pchar, GOOD_CANNON_24) < 15)
		{
			dialog.text = "Mm. ¡Extraño sentido del humor tiene, señor! Por alguna razón no veo quince cañones siendo descargados de su barco...";
			link.l1 = "Bueno, verás, tuvimos una fuga y tuvimos que lanzar parte de la carga por la borda...";
			link.l1.go = "florian_deck_fail";
		}
		else
		{
			dialog.text = "¿Contento de verte, capitán?..";
			link.l1 = "" + GetFullName(pchar) + ". Capitán " + GetFullName(pchar) + ".";
			link.l1.go = "florian_deck_3";
		}
		break;

	case "florian_deck_3":
		dialog.text = "Encantado de conocerte. No perdamos tiempo y subamos estos cañones a bordo. Esto no va a ser fácil, así que necesitaré que tus hombres ayuden.";
		link.l1 = "Lo manejaremos. ¡Tú, allí, coloca el aparejo en el penol!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Trial_TakeCannons");
		break;

	case "florian_deck_fail":
		dialog.text = "¡Maldito idiota! Si no puedes ni manejar esta simple tarea, seguro que te hundirás en la próxima tormenta. Regresa a tu barco, capitán, y haz algo para lo que seas mejor, como entregar flores a las damas nobles. Mejor aún, navega de regreso a Europa y deja el Nuevo Mundo a los hombres de verdad. ¡Buen día, señor!";
		link.l1 = "Pero...";
		link.l1.go = "florian_deck_fail_1";
		break;

	case "florian_deck_fail_1":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		npchar.DontDeskTalk = true;
		RemoveCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24));
		SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
		sld = characterFromId("Lecrua");
		sld.lifeday = 0;
		AddQuestRecord("Trial", "10");
		CloseQuestHeader("Trial");
		DeleteAttribute(pchar, "questTemp.Trial");
		ChangeCharacterNationReputation(pchar, FRANCE, -3);
		break;

	case "florian_deck_4":
		dialog.text = "¡Uf, eso fue un trabajo que da sed! ¡Le agradezco por el servicio, capitán! Tome su recompensa, doscientos doblones.";
		link.l1 = "¡Gracias!";
		link.l1.go = "florian_deck_5";
		break;

	case "florian_deck_5":
		TakeNItems(pchar, "gold_dublon", 200);
		Log_Info("Has recibido 200 doblones.");
		PlaySound("interface\important_item.wav");
		dialog.text = "Pero eso no es todo, capitán. ¿Le gustaría ganar otros doscientos cincuenta escudos de oro?";
		link.l1 = "Eso suena prometedor, pero depende de lo que me vaya a pedir que haga por ello, señor.";
		link.l1.go = "florian_deck_6";
		break;

	case "florian_deck_6":
		dialog.text = "No voy a mentir, es peligroso. Como ya sabrás, estoy al acecho de un galeón español pesado con un valioso cargamento. El barco fue llevado a los muelles para una reparación. Según mis fuentes, se suponía que zarparía ayer, pero no sucedió. Además, mi agente en Portobello no llegó al punto de encuentro para entregar las actualizaciones que he estado esperando. Sospecho que los españoles lo arrestaron. Te pagaré para que te infiltras en Portobello y averigües dos cosas: por qué el galeón sigue allí y qué le pasó a mi agente. ¿Aceptas?";
		link.l1 = "Me temo que carezco del entrenamiento adecuado para tal operación. Soy un caballero, no un espía. Podría meterme en problemas yo mismo y no podré ayudarte.";
		link.l1.go = "florian_deck_bye";
		link.l2 = "Suena peligroso, pero rentable. Me arriesgaré. ¿Cómo se llama tu hombre y cómo se llama el galeón?";
		link.l2.go = "florian_deck_7";
		break;

	case "florian_deck_bye":
		dialog.text = "Bueno, ¿no estás lleno de derechos? Te entiendo. Entonces adiós, capitán, ¡gracias de nuevo por tu ayuda!";
		link.l1 = "Todo lo mejor, Monsieur Shoke.";
		link.l1.go = "florian_deck_bye_1";
		break;

	case "florian_deck_bye_1":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		npchar.DontDeskTalk = true;
		SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
		sld = characterFromId("Lecrua");
		sld.lifeday = 0;
		AddQuestRecord("Trial", "11");
		CloseQuestHeader("Trial");
		DeleteAttribute(pchar, "questTemp.Trial");
		break;

	case "florian_deck_7":
		dialog.text = "¡Aye, escucha bien entonces! El nombre de mi hombre es Sylvan Laforet, pero en Portobello se hace llamar Jaime Silicio, un comerciante. El galeón se llama 'Alacantara'. Te aconsejo que pases por las puertas de la ciudad de noche, a través de la selva. Los guardias de Portobello son muy suspicaces en estos días, sin mencionar que la desaparición de Sylvan no augura nada bueno para que esté vivo y sano. Tienes dos días antes de que tenga que irme de aquí antes de que las patrullas españolas nos encuentren. ¡Buena suerte, monsieur!";
		link.l1 = "Nos vemos pronto, Monsieur Shoke...";
		link.l1.go = "florian_deck_8";
		break;

	case "florian_deck_8":
		bQuestDisableMapEnter = true;			 // закрыть карту
		pchar.GenQuest.MapClosedNoBattle = true; // доступно ожидание и sailto
		DialogExit();
		npchar.DeckDialogNode = "florian_deck_repeat";
		NextDiag.CurrentNode = "florian_deck_repeat";
		pchar.questTemp.Trial = "spy";
		AddQuestRecord("Trial", "12");
		// belamour legendary edition -->
		if (!bImCasual)
		{
			pchar.quest.trial_spy_over.win_condition.l1 = "Timer";
			pchar.quest.trial_spy_over.win_condition.l1.date.hour = sti(GetTime() + 2);
			pchar.quest.trial_spy_over.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
			pchar.quest.trial_spy_over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.trial_spy_over.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
			pchar.quest.trial_spy_over.function = "Trial_SpyTimeOver";
		}
		else
			NewGameTip("Modo exploración: el temporizador está desactivado.");
		// <-- legendary edition
		// Log_Info("Has recibido el amuleto 'Fan de Gypsy'");
		PlaySound("interface\important_item.wav");
		GiveItem2Character(pchar, "obereg_4");
		pchar.quest.NewGameTip5.win_condition.l1 = "location";
		pchar.quest.NewGameTip5.win_condition.l1.location = "PortoBello_town";
		pchar.quest.NewGameTip5.function = "ShowNewGameTip";
		pchar.quest.NewGameTip5.text = "Los guardias sospechan menos cuando caminas a paso lento.";

		pchar.quest.Trial_CreatHabitue.win_condition.l1 = "location";
		pchar.quest.Trial_CreatHabitue.win_condition.l1.location = "PortoBello_tavern";
		pchar.quest.Trial_CreatHabitue.function = "Trial_CreatHabitue";

		pchar.quest.Tutorial_stealth.win_condition.l1 = "location";
		pchar.quest.Tutorial_stealth.win_condition.l1.location = "PortoBello_ExitTown";
		pchar.quest.Tutorial_stealth.function = "Tutorial_stealth";

		QuestPointerToLoc("shore47", "reload", "reload1_back");
		QuestPointerToLoc("PortoBello_Jungle_02", "reload", "reload1_back");
		QuestPointerToLoc("PortoBello_Jungle_01", "reload", "reload3_back");
		QuestPointerToLoc("PortoBello_ExitTown", "reload", "reload4");
		QuestPointerToLoc("PortoBello_Town", "reload", "reload41_back");
		QuestPointerToLoc("PortoBello_Town", "reload", "reload4_back");
		break;

	case "florian_deck_repeat":
		dialog.text = "Hemos discutido todo, capitán, ¿no es así?";
		link.l1 = "Sí. Estoy en camino.";
		link.l1.go = "exit";
		NextDiag.TempNode = "florian_deck_repeat";
		break;

	case "florian_failspy":
		pchar.quest.trial_spy_over.over = "yes"; // снять прерывание
		dialog.text = "¿Cómo van las cosas, capitán? ¿Qué has logrado averiguar?";
		link.l1 = "Las cosas van mal, Monsieur Shoke. No soy muy buen espía, me descubrieron muy rápido. Tuve que escapar de la ciudad después de pelear con algunos guardias. Lo único que logré descubrir es que su hombre Sylvan Laforet ha sido arrestado y está detenido en la cárcel.";
		link.l1.go = "florian_failspy_1";
		break;

	case "florian_failspy_1":
		dialog.text = "¡Maldita sea! Eso no es bueno... ¿Descubriste algo sobre el galeón?";
		link.l1 = "No, no lo hice.";
		link.l1.go = "florian_failspy_2";
		break;

	case "florian_failspy_2":
		dialog.text = "Maldición. Realmente necesito información al respecto. ¡Pero este premio es demasiado jugoso para dejarlo pasar! De todos modos, intentaré enviar otro explorador allí... Capitán, le pido que no me deje por ahora. Podría necesitar su ayuda. ¿Esperará hasta otro día mientras investigo información sobre el Alacantara?";
		link.l1 = "Por supuesto, ¡esperaré! Me gustaría compensar ese fracaso.";
		link.l1.go = "florian_9";
		link.l2 = "No lo creo. Aparentemente soy demasiado malo en estos juegos. Me dirijo a casa.";
		link.l2.go = "florian_failspy_3";
		break;

	case "florian_failspy_3":
		dialog.text = "Bueno, es tu elección. Todo lo mejor, capitán.";
		link.l1 = "Adiós, Monsieur Shoke.";
		link.l1.go = "florian_failspy_4";
		break;

	case "florian_failspy_4":
		DialogExit();
		bQuestDisableMapEnter = false;
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		LAi_CharacterDisableDialog(npchar);
		npchar.DontDeskTalk = true;
		SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
		sld = characterFromId("Lecrua");
		sld.lifeday = 0;
		CloseQuestHeader("Trial");
		DeleteAttribute(pchar, "questTemp.Trial");
		pchar.questTemp.TrialEnd = true;
		break;

	case "florian_failspy_5":
		pchar.quest.trial_spy_over.over = "yes"; // снять прерывание
		dialog.text = "¿Cómo van las cosas, capitán? ¿Qué has logrado averiguar?";
		link.l1 = "Las cosas van mal, Monsieur Shoke. No soy muy buen espía, me descubrieron muy rápido. Lo único que logré averiguar es que su hombre, Sylvan Laforet, ha sido arrestado y está detenido en algún lugar.";
		link.l1.go = "florian_failspy_1";
		break;

	case "florian_9":
		dialog.text = "Entonces dirígete a tu barco, capitán. Mañana a la misma hora, o un poco más tarde, tendrás que visitarme. Tal vez para entonces haya descubierto algo. ¡No pises tierra, espérame en tu barco!";
		link.l1 = "Está bien. Lo haré.";
		link.l1.go = "florian_10";
		break;

	case "florian_10":
		dialog.text = "Y capitán, tome esta bolsa. Sus esfuerzos no fueron completamente en vano después de todo. Al menos sabemos qué le pasó al pobre viejo Sylvan...";
		link.l1 = "...";
		link.l1.go = "florian_11";
		break;

	case "florian_11":
		DialogExit();
		Island_SetReloadEnableGlobal("Portobello", false); // закрыть остров
		npchar.DeckDialogNode = "florian_deck_wait";
		NextDiag.CurrentNode = "florian_deck_wait";
		pchar.questTemp.Trial = "spy_wait";
		pchar.quest.Trial_spyfail_wait.win_condition.l1 = "Timer";
		pchar.quest.Trial_spyfail_wait.win_condition.l1.date.hour = sti(GetTime() + rand(12));
		pchar.quest.Trial_spyfail_wait.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.Trial_spyfail_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.Trial_spyfail_wait.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.Trial_spyfail_wait.function = "Trial_Spyfail_NextStage";
		TakeNItems(pchar, "purse2", 1);
		Log_Info("Has recibido un monedero con doblones");
		break;

	case "florian_deck_wait":
		dialog.text = "Capitán, no tengo ninguna noticia por el momento. Todavía estamos esperando...";
		link.l1 = "Está bien...";
		link.l1.go = "exit";
		NextDiag.TempNode = "florian_deck_wait";
		break;

	case "florian_12":
		pchar.quest.trial_spy_over.over = "yes"; // снять прерывание
		dialog.text = "¿Cómo van las cosas, capitán? ¿Qué ha logrado averiguar?";
		link.l1 = "Está hecho. Tu hombre, Sylvan Laforet, fue arrestado y está detenido en la cárcel. Se acabó para él.";
		link.l1.go = "florian_13";
		DelLandQuestMark(npchar);
		QuestPointerDelLoc("PortoBello_Town", "reload", "gate_back");
		QuestPointerDelLoc("PortoBello_ExitTown", "reload", "reload1_back");
		QuestPointerDelLoc("PortoBello_Jungle_01", "reload", "reload2_back");
		QuestPointerDelLoc("PortoBello_Jungle_02", "reload", "reload3_back");
		QuestPointerDelLoc("shore47", "reload", "boat");
		break;

	case "florian_13":
		dialog.text = "¡Maldita sea! Eso es espantoso... ¿Descubriste algo sobre el galeón?";
		link.l1 = "Sí. Ha estado preparándose para embarcarse por un tiempo, pero el gobernador de Portobello tiene la intención de retenerla en el muelle. Ahora mismo está esperando que llegue una barca llamada 'Puebla' desde Cartagena con un cargamento de pólvora para el 'Alcántara'. Según un marinero del galeón, no tienen suficiente de ella y el gobernador teme a los piratas.";
		link.l1.go = "florian_14";
		break;

	case "florian_14":
		dialog.text = "¡Qué interesante!";
		link.l1 = "Pero si Puebla no llega dentro de tres días, entonces el Alacantara dejará de esperar y zarpará.";
		link.l1.go = "florian_15";
		break;

	case "florian_15":
		dialog.text = "Excelente trabajo, Capitán " + GetFullName(pchar) + "¡Estoy muy complacido! Aquí tienes tu recompensa. ¡Te la has ganado totalmente!";
		link.l1 = "¡Gracias! ¿Tienes alguna otra tarea para mí?";
		link.l1.go = "florian_16";
		break;

	case "florian_16":
		TakeNItems(pchar, "gold_dublon", 250);
		Log_Info("Has recibido 250 doblones");
		PlaySound("interface\important_item.wav");
		dialog.text = "Estás leyendo mi mente, " + GetFullName(pchar) + "¡Sí, maldita sea! Como Alacantara tiene poca pólvora, puedo dejarla navegar en mar abierto y luego obligarla a entablar una prolongada pelea naval, en la que su pólvora se agotará antes que la nuestra, ¡ja ja!\nDebes asegurarte de que el barca goleta de suministros Puebla nunca llegue a . No puedo navegar cerca de la costa, las patrullas notarán mi fragata fácilmente y me echarán antes de que pueda interceptar a Alacantara.\nPuedes encargarte de Puebla por tu cuenta. Encuéntrala y deshazte de ella. Hundela o tómala como premio, no me importa. ¡Solo impide que llegue aquí!\nSi tienes éxito, entonces ve a Guadalupe y busca a Gerard LeCroix. Creo que ya lo conoces, ¿no? Él te pagará la moneda que mereces.";
		link.l1 = "¡Trato hecho! ¡Me pondré en camino para cortar el Puebla!";
		link.l1.go = "florian_19";
		link.l2 = "Espere un poco, Monsieur Choquet. La verdad es que todavía estoy... Digamos, no particularmente acostumbrado a las batallas navales. Y usted es el capitán de una fragata, obviamente tiene más de una batalla naval a sus espaldas. Si no le es difícil, podría usted... ¿Cómo debería decirlo...?";
		link.l2.go = "florian_guide_01";
		break;

	case "florian_17":
		dialog.text = "Me alegra que estés aquí, capitán. Acabo de recibir información de mi espía y tengo una misión importante para ti.";
		link.l1 = "Soy todo oídos.";
		link.l1.go = "florian_18";
		break;

	case "florian_18":
		dialog.text = "El Alacantara está listo para zarpar, pero el capitán del galeón está esperando que el bergantín 'Puebla' llegue de Cartagena cargado con municiones. Aparentemente, el Alacantara no tiene suficiente pólvora, así que los españoles aún no están listos para zarpar. Pero la paciencia del capitán tiene sus límites y si Puebla no llega en tres días, entonces el galeón saldrá de Portobello sin ella\nEl Alacantara tiene poca pólvora, puedo dejar que navegue hacia mar abierto y luego forzarla a participar en una prolongada batalla naval, en la cual su pólvora se acabará antes que la nuestra. Tu objetivo es interceptar la Puebla y destruirla. Hundirla o capturarla como premio, no me importa. ¡Solo evita que ese bergantín de reabastecimiento llegue aquí!\nSi tienes éxito, entonces ve a Guadalupe y busca a Gerard LeCroix, creo que ya lo conoces, ¿verdad? Él te pagará la moneda que mereces.";
		link.l1 = "¡Trato hecho! ¡Me pondré en camino para interceptar al Puebla!";
		link.l1.go = "florian_19";
		link.l2 = "Espere un poco, Monsieur Choquet. El hecho es que todavía estoy... Digamos, no particularmente acostumbrado a las batallas navales. Y usted es el capitán de un fragata, obviamente tiene más de una batalla naval a sus espaldas. Si no le resulta difícil, podría... ¿Cómo debería decirlo...?";
		link.l2.go = "florian_guide_01";
		break;

	case "florian_19":
		DialogExit();
		Island_SetReloadEnableGlobal("Portobello", true); // открыть остров
		bQuestDisableMapEnter = false;					  // открыть карту
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		LAi_CharacterDisableDialog(npchar);
		npchar.DontDeskTalk = true;
		SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
		Trial_CreatePueblaBarqueInWorld();
		pchar.questTemp.Trial = "puebla";
		AddQuestRecord("Trial", "19");
		break;
	// belamour legendary edition дополнительное обучение -->
	case "florian_guide_01":
		dialog.text = "¿Te gustaría que te diera una lección sobre las tácticas del combate naval? ¡Con mucho gusto, capitán! Especialmente porque es de mi propio interés: quiero asegurarme de que interceptes con éxito el 'Puebla'.";
		link.l1 = "No, no lo dije en serio. Está bien, olvídalo: estoy seguro de que no tendré problemas para interceptar una barca goleta.";
		link.l1.go = "florian_19";
		link.l2 = "Sí, eso es exactamente lo que quise decir. Estoy seguro de que el nuevo conocimiento no me hará daño.";
		link.l2.go = "florian_guide_02";
		break;

	case "florian_guide_02":
		dialog.text = "Así que lo primero que debes recordar es que la mitad de la batalla se gana o se pierde antes de que siquiera comience. Mucho depende de cuán preparados estén tú y tu barca goleta para ello.";
		link.l1 = "...";
		link.l1.go = "florian_guide_03";
		break;

	case "florian_guide_03":
		dialog.text = "Primero, asegúrate de que tu barco esté reparado. Si tienes agujeros en el casco, no será difícil para el enemigo enviarte al fondo. Y si tienes harapos colgando en lugar de velas, esto limita muy significativamente tu movilidad. El enemigo puede fácilmente alejarse de ti si el equilibrio de fuerzas no está a su favor o, peor aún, alcanzarte e imponerte una batalla desfavorable, o incluso abordarte de inmediato. Además, con las velas rasgadas, te costará ganar el barlovento, es decir, ponerte a barlovento de tu oponente donde deseas estar.";
		link.l1 = "Ventaja del viento, entendido. ¿Algo más?";
		link.l1.go = "florian_guide_04";
		break;

	case "florian_guide_04":
		dialog.text = "Asegúrate de tener suficientes hombres. Incluso el barco más poderoso con cañones de 42 libras se vuelve inútil si tienes a un artillero corriendo para recargar tres cañones y simplemente no hay nadie para controlar las velas. En general, yo simplemente abordaría inmediatamente un barco así y lo capturaría.";
		link.l1 = "Basta de hombres, entendido.";
		link.l1.go = "florian_guide_05";
		break;

	case "florian_guide_05":
		dialog.text = "Además, vigila tus cañones: se desgastarán y explotarán con el tiempo. Con el tiempo, la condición de los cañones se deteriora, y si tus cañones comienzan a explotar en medio de una batalla, puede terminar muy mal para ti. No tuve suerte en absoluto: el lote de cañones con el que navegué resultó tener varios defectos de fundición. Si no hubieras traído un reemplazo a tiempo, simplemente habría abandonado la operación, ya que el Militant sería mucho inferior al Alcantara en potencia de fuego. Las herramientas necesitan ser cambiadas a tiempo.";
		link.l1 = "¡Ahora entiendo por qué era tan importante!";
		link.l1.go = "florian_guide_06";
		break;

	case "florian_guide_06":
		dialog.text = "Además de los cañones, también vigila la cantidad de municiones. Alcantara caerá ante mí por esto. Si tiene pocas reservas de pólvora, no podrá luchar una batalla larga, necesita entrar inmediatamente en combate cuerpo a cuerpo. Y jugaré con esto: mi fragata es más rápida, un galeón pesado no podrá escapar de ella. Pero tampoco necesito acercarme: imponeré un duelo de artillería a larga distancia y luego, cuando se acabe la pólvora en la Alcantara, cerraré, la barreré con metralla y la abordaré.";
		link.l1 = "Situación desesperada...";
		link.l1.go = "florian_guide_07";
		break;

	case "florian_guide_07":
		dialog.text = "Exactamente. Mantén un ojo en tu pólvora y municiones. Si te quedas sin balas sólidas, lo más probable es que no puedas hundir un barco enemigo. Si te quedas sin metralla, no puedes esperar abordar si estás en desventaja numérica. Si no tienes balas de cadena o knipples, no podrás alcanzar al enemigo ni alejarte de él si es más rápido. Todos los tipos de munición son importantes.";
		link.l1 = "Instructivo, gracias.";
		link.l1.go = "florian_guide_08";
		break;

	case "florian_guide_08":
		dialog.text = "Y finalmente, dependiendo del tipo y tamaño de tu barco y del barco enemigo, usa las tácticas apropiadas. Hay un equilibrio en el mar entre potencia de fuego y velocidad. En un barco grande y lento, no tiene sentido perseguir un bergantín o una corbeta para abordarlos: todavía no los alcanzarás sin ablandarlos primero con metralla. En tales casos, es más sabio destruirlos desde la distancia y recoger los restos. Si aún necesitas abordar tal barco, es preferible usar un barco rápido y maniobrable.";
		link.l1 = "... ";
		link.l1.go = "florian_guide_09";
		break;

	case "florian_guide_09":
		dialog.text = "Al mismo tiempo, no te enfrentes cara a cara con un navío de línea con una fragata. Una andanada de un monstruo así destrozará los cascos de barcos más pequeños en astillas. Usa tu ventaja en velocidad y maniobrabilidad, derriba sus mástiles y aparejos, luego acércate y barre sus cubiertas con metralla si aún necesitas abordarla. Si necesitas hundirla... no será una tarea fácil, pero es posible. Puedes abordarla y luego incendiar su santabárbara, pero nunca es vergonzoso huir. Un buen capitán salvará a su barco y tripulación de una muerte segura en lugar de un heroísmo excesivo. Recuerda, la discreción y la prudencia son a menudo la mejor parte del valor.";
		link.l1 = "¡Muchas gracias, Monsieur Choquet!";
		link.l1.go = "florian_guide_10";
		break;

	case "florian_guide_10":
		AddCharacterSkillDontClearExp(pchar, SKILL_CANNONS, 1);
		AddCharacterSkillDontClearExp(pchar, SKILL_ACCURACY, 1);
		// Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_CANNONS));
		notification(XI_ConvertString("Experience Bonus") + ": +1 ", SKILL_CANNONS);
		// Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_ACCURACY));
		notification(XI_ConvertString("Experience Bonus") + ": +1 ", SKILL_ACCURACY);
		dialog.text = "Alegre de ayudar, capitán. Espero que este conocimiento te ayude en el futuro.";
		link.l1 = "Estoy seguro de que ayudará. ¡Vamos a interceptar el 'Puebla!'";
		link.l1.go = "florian_19";
		break;
	// <-- legendary edition дополнительное обучение

	// испанский офицер в таверне
	case "tavern_officer":
		dialog.text = "Es un acento inusual el que tienes, señor. ¿O debería decir 'monsieur'? ¿Te gustaría ver a Jaime Silicio? Quizás puedas compartir la misma celda. ¡Llévenselo, muchachos!";
		link.l1 = "Bueno, si no te gusta mi acento, ¡quizás pueda presentarte al arte de la espada francesa!";
		link.l1.go = "tavern_officer_1";
		break;

	case "tavern_officer_1":
		DialogExit();
		chrDisableReloadToLocation = true; // закрыть локацию
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		LAi_SetWarriorTypeNoGroup(npchar);
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheck("EnemyFight", "Trial_AfterTavernFight");
		AddDialogExitQuest("MainHeroFightModeOn");
		SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}

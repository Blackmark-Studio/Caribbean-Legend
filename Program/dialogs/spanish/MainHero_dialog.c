void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref chr, sld, rShip, rItm, rItem;
	float fTemp;
	bool bOk;
	int i, iTemp;
	string sAttr, sGun, sBullet, attrL;
	aref rType;

	// генератор ИДХ по кейсу -->
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "CabinCompanionTalk_", 0) != -1)
	{
		i = findsubstr(sAttr, "_", 0);
		PChar.GenQuest.CabinCompanionNum = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
		Dialog.CurrentNode = "Cabin_Companion_Talk";
	}

	if (findsubstr(sAttr, "SetGunBullets1_", 0) != -1)
	{
		i = findsubstr(sAttr, "_", 0);
		PChar.GenQuest.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
		Dialog.CurrentNode = "SetGunBullets2";
	}

	if (findsubstr(sAttr, "SetMusketBullets1_", 0) != -1)
	{
		i = findsubstr(sAttr, "_", 0);
		PChar.GenQuest.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
		Dialog.CurrentNode = "SetMusketBullets2";
	}

	if (findsubstr(sAttr, "tonzag_jail_", 0) != -1)
	{
		pchar.questTemp.Tonzag.JailDialog.ID = strcut(sAttr, strlen("tonzag_jail_"), strlen(sAttr) - 1);
		DeleteAttribute(pchar, "questTemp.TonzagQuest.JailDialog." + pchar.questTemp.Tonzag.JailDialog.ID);
		AddDialogExitQuestFunction("Tonzag_InJailDialog");
		Dialog.CurrentNode = "exit";
	}
	// генератор ИДХ по кейсу <--

	switch (Dialog.CurrentNode)
	{
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit_Self();
		break;

	case "First time":
		NextDiag.TempNode = "First time";

		Dialog.Text = "Si estás leyendo esta línea, es un error en el código";
		Link.l1 = "Salir";
		Link.l1.go = "exit";
		//--> Вступительный туториал на палубе корабля за Шарля
		if (CheckAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_1"))
		{
			dialog.text = "¡Emocionante, maldita sea! ¡Una verdadera batalla naval!\nLástima, claro, que no pueda ver la lucha real desde aquí abajo... Bueno, no importa. Creo que ya he aprendido lo suficiente sobre navegación para imaginar vívidamente cómo se desarrollan los acontecimientos\nCinco barcos piratas, me atrevería a decir... uno grande, un par de medianos y algunos más pequeños. Perfecto para nuestro pinaza. ¡Será un relato espléndido — Lulu estará encantada!";
			link.l1 = "...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_1");
			pchar.wind.speed = 18.0;
			fWeatherSpeed = stf(18.0);
			//AddDialogExitQuestFunction("SharlieTutorial_StartShip");
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_3");
		}
		//<-- Вступительный туториал на палубе корабля за Шарля

		//--> Голландский гамбит
		if (CheckAttribute(pchar, "questTemp.HWIC_FindIsland"))
		{
			dialog.text = "Entonces, hemos encontrado este lugar en el mapa. Debería marcarlo, y estamos listos para ir a buscar.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SearchingForIslandOnMap");
		}
		if (CheckAttribute(pchar, "questTemp.HWICMC") && pchar.questTemp.HWICMC == "Fleetwood")
		{
			dialog.text = "Está bien, ya estamos aquí. Debería esconder mi barco en la bahía del Sur, luego volver a pie a través de la jungla y preparar una desagradable sorpresa para Fleetwood.";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.quest.Fleetwood_repeatShore.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Fleetwood_repeatShore.win_condition.l1.location = pchar.location;
			pchar.quest.Fleetwood_repeatShore.function = "Fleetwood_repeatShore";
		}
		//<-- Голландский гамбит

		//--> Ложный след
		if (CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabinWoman" && PChar.location == Get_My_Cabin())
		{
			dialog.text = "Hm... Confiar en este granuja es peligroso, aunque su historia parece auténtica. Quizás, no está mintiendo esta vez. Pero, de todas formas, debería hablar con su esposa... ¡Contramaestre! ¡Tráeme a esa mujer cautiva!";
			link.l1 = "¡Aye Aye, capitán!";
			Link.l1.go = "exit";
			chr = characterFromId("FalseTraceWife");
			chr.dialog.currentnode = "FalseTrace_wife_6";
			pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
			AddDialogExitQuest("SetFalseTraceCharToCabin");
		}
		//<-- Ложный след

		//--> Португалец
		if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "DigGems")
		{
			dialog.text = "Este parece ser el lugar. Es el único árbol sin savia en las cercanías. Debería cavar aquí.";
			link.l1 = "(desenterrar el tesoro)";
			link.l1.go = "exit";
			AddDialogExitQuest("FindPortugalGems");
		}
		//<-- Португалец
		// Сага
		if (CheckAttribute(pchar, "questTemp.Saga.JessSoul"))
		{
			dialog.text = "¿Qué está pasando? ¿Dónde estoy?! ¿Qué tipo de lugar es este?";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Saga_JessikaSoul_2");
		}
		//--> приколы со стуком в дверь Диффиндура, LSC
		if (CheckAttribute(pchar, "questTemp.LSC.DiffIndoor"))
		{
			dialog.text = "Esta es la puerta que conduce a las dependencias internas del barco. Está cerrada... Hawk debe estar aquí. ¿Qué mencionó Ole otra vez? Debería usar un golpe secreto.";
			link.l1 = "Golpea dos veces.";
			link.l1.go = "knock_2";
			link.l2 = "Golpea tres veces.";
			link.l2.go = "knock_3";
			link.l3 = "Toca una vez, pausa, toca tres veces.";
			link.l3.go = "knock_1_3";
			link.l4 = "Golpea dos veces, pausa, golpea dos veces.";
			link.l4.go = "knock_2_2";
			link.l5 = "Golpea tres veces, pausa, golpea una vez.";
			link.l5.go = "knock_3_1";
		}
		//<-- приколы со стуком в дверь Диффиндура, LSC

		//--> напялили водолазный скафандр, для перехода в режим шага
		if (pchar.model == "protocusto")
		{
			dialog.text = "¡Vaya! ¡Eso es realmente pesado!";
			link.l1 = "";
			link.l1.go = "exit";
		}
		//<-- водолазный скафандр
		// отказ от телепортации
		if (IsCharacterInLocator(pchar, "item", "dolly1") || IsCharacterInLocator(pchar, "item", "dolly2") || IsCharacterInLocator(pchar, "item", "dolly3"))
		{
			dialog.text = "¡No-no-no! ¡De ninguna manera! ¡Tres veces fueron más que suficientes!";
			link.l1 = "...";
			link.l1.go = "exit";
		}
		if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "roof")
		{
			dialog.text = "Está hecho. Levasseur está muerto. Resultó ser mucho más fácil de lo que esperaba... Pero algo no está bien. ¡Thibaut ni siquiera habló con Martene! Significa que o Robert me traicionó o ha habido un accidente\n¿Pero dónde podría haber huido ese bastardo de Thibaut? Debe estar cazando a Catherine. Debo actuar rápido si quiero tomar a la chica viva de debajo de su nariz...";
			link.l1 = "";
			link.l1.go = "terrapin";
		}
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
		{
			dialog.text = "Tesoros, tesoros... una ciudad india... No creo en tales coincidencias... Apostaría que mi hermano tuvo algo que ver con la desaparición de la fragata de Dichoso. Probablemente se aseguró de que Dichoso nunca más abriera la boca\nO, tal vez, estaba trabajando con él, los españoles deben haber tenido razones para pensar que Dichoso está por aquí. Esto no tiene sentido. Pero estoy seguro de que el oro indio que Michel entregaba a de Poincy, así como el oro de Miguel Dichoso, es el mismo oro. La historia del prisionero coincide con lo que el oficial me contó sobre las aventuras de mi hermano\nCurioso, ¡Michel no logró entregar el oro y tampoco lo hizo Miguel! ¿Y dónde están los tesoros ahora entonces? Quizás, fueron la razón por la que mi hermano tiene tanta prisa\nPor lo tanto, encontrar el oro significará matar dos pájaros de un tiro: Miraré de nuevo en los insolentes ojos de mi hermano y... sí, el oro siempre es bueno. ¿Pero cómo diablos lo encuentro? Parece, que es hora de acercarme mucho a los españoles\nDon Ramona Mendoza está fuera de la mesa, dudo que pueda tratar con él, pero el santo padre Vincento, el peor enemigo de un barón... él servirá. Su tipo no es escrupuloso pero ama el dinero y los medios sucios\nDichoso, Dichoso... He oído este apellido antes... ¿o no? No importa, al diablo con eso. Debería ir al oficial y reclamar al prisionero español. Luego puedo dirigirme a Santiago en cualquier momento.";
			link.l1 = "";
			link.l1.go = "exit";
		}
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore")
		{
			dialog.text = "La vainilla ha sido cargada en la carraca y sus velas hace mucho que desaparecieron más allá del horizonte, y este maldito galeón ha vuelto al puerto en lugar de tomar alta mar. No debo aparecer con mi barco en el puerto, es mejor si piensan que me fui de Guadalupe... Supongo que caminaré a la ciudad a través de la jungla y me informaré sobre mi querido Marchais...";
			link.l1 = "";
			link.l1.go = "exit";
		}
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "galeon")
		{
			dialog.text = "Solo hay unos pocos guardias en la cubierta superior, todos ellos bastante adormilados. Supongo que puedo eliminarlos uno por uno, si me acerco silenciosamente por detrás y los golpeo con una manopla en la parte posterior de la cabeza...";
			link.l1 = "";
			link.l1.go = "exit";
		}
		if (CheckAttribute(pchar, "questTemp.Guardoftruth_room"))
		{
			dialog.text = "Una casa desbloqueada vacía con una habitación acogedora en el segundo piso, y en las cercanías de los apartamentos de Calhoun... Esto es simplemente la respuesta a la oración de una doncella... Si salgo por la ventana y camino sobre el abat-jour del techo, entraré con facilidad a la habitación de Archie. Pero esto debe hacerse de noche para que no me atrapen...";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("GuardOT_FindWayToRoom");
		}
		// Поиски Ксочитэма
		if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_pearl")
		{
			dialog.text = "¡Finalmente! He localizado el lugar, indicado por la 'manifestación': es un ídolo indio. Cuando estoy cerca, la 'Flecha del Camino' deja de oscilar y señala en una dirección. Bueno, parece lógico: magia india y un ídolo indio. Ahora debería marcar la ubicación indicada por la 'Flecha del Camino' en el mapa, y luego iré a Dominica.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Ksochitam_FindFirstWay");
		}
		if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_dominica")
		{
			dialog.text = "¡Finalmente! He localizado el lugar indicado por la 'manifestación': es un ídolo indio. Cuando estoy cerca, la 'Flecha del Camino' deja de oscilar y apunta en una dirección. Bueno, parece lógico, magia india y un ídolo indio. Ahora debería marcar la ubicación indicada por la 'Flecha del Camino' en el mapa, y luego iré a Tierra Firme.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Ksochitam_FindSecondWay");
		}
		if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "full")
		{
			dialog.text = "¡Se han encontrado ambas manifestaciones! Ahora debo marcar la segunda dirección en el mapa. La intersección de estas dos direcciones me mostrará la ubicación de la isla de Ksocheatem.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Ksochitam_FindFullWay");
		}
		// рассуждения по Тайясалю
		if (CheckAttribute(pchar, "questTemp.Tieyasal_CabinTalk"))
		{
			if (pchar.questTemp.Tieyasal_CabinTalk == "calendar")
			{
				dialog.text = "Alonso de Maldonado dijo que hay un camino a Tayasal que comienza al norte de Yucatán. Eso significa que debería adentrarme en la selva de la zona. Pero Gino dijo que las estatuas de teletransporte originalmente se suponía que trasladaban a las personas a Tayasal\nY el chamán Miskito Ojo de Serpiente me dijo que los ídolos estaban diseñados para enviar a los 'devorados' al lugar. Pero entonces, ¿por qué esas puertas están rotas? Hm. Además, el mapa de Dos Manifestaciones muestra un círculo extraño cerca de la estatua de Miskito\n¿Qué diablos significa eso? ¿Otro lugar mágico? ¿O muestra que la estatua allí tiene algunas funciones adicionales? Supongo que debería visitar al chamán. O podría ir al Noroeste de la Principal y buscar el camino allí, en una de las bahías locales.";
				link.l1 = "";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Alonso de Maldonado dijo que había otra manera de llegar a Tayasal desde la parte norte de la península de Yucatán. Eso significa que debo buscar un camino hacia las profundidades de la selva. Es probable que el camino que necesito comience en una de las calas en el noroeste principal.";
				link.l1 = "";
				link.l1.go = "exit";
			}
			AddDialogExitQuest("Tieyasal_AfterCabinTalk");
		}
		// решаем - титры или фриплей 010912
		if (CheckAttribute(pchar, "questTemp.Tieyasal_final"))
		{
			dialog.text = "Está hecho. El fin de mi largo viaje. No podía imaginar que salvar a mi hermano de la prisión significaba prepararme para la lucha final contra él. ¡Que casi había condenado nuestro mundo! Gracias a Dios, esto ha terminado\nNada me retiene en el Caribe por más tiempo. Es hora de regresar a casa, a Francia. Pero... ¿Realmente quiero eso?";
			link.l1 = "Sí, estoy volviendo a Europa.";
			link.l1.go = "final_1";
			link.l2 = "No, me quedo aquí en el Caribe.";
			link.l2.go = "final_2";
		}
		// фэйловый финал 040912
		if (CheckAttribute(pchar, "questTemp.Europe"))
		{
			PlaySound("Voice\Spanish\YouFace_3.wav");
			dialog.text = "¿Has escuchado al coronel? ¡Los rebeldes se esconden allí! Hay que buscar en todos los rincones. Pon la casa patas arriba de ser necesario, y retiene a todos los que encuentres allí! ¡Vamos! ¡Manos a la obra!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Europe_SharlieFinal_2");
		}
		// Addon-2016 Jason, французские миниквесты (ФМК) Гваделупа
		/*if (CheckAttribute(pchar, "questTemp.FMQG.Info") && pchar.location == "Bridgetown_Plantation")
		{
			dialog.text = "Este es el mejor lugar para una emboscada. Debería esperar aquí la llegada de Pinette.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQG_KidnappingInfo");
		}*/
		// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
		if (CheckAttribute(pchar, "questTemp.FMQN.Choose") && pchar.location == "shore40")
		{
			dialog.text = "Mmm. Esta historia no parece correcta. Creo que esa balandra de St. John's nunca debió existir. El teniente me está arrastrando a su operación militar. ¿Por qué necesitaría eso? No estoy en guerra con los holandeses... ¿Qué debería hacer? ¿Debería irme y dejar que los británicos se diviertan por su cuenta? ¿O debería quedarme?";
			link.l1 = "Vete.";
			link.l1.go = "FMQN_1";
			link.l2 = "Quédate.";
			link.l2.go = "FMQN_2";
		}
		// Addon 2016-1 Jason пиратская линейка
		if (CheckAttribute(pchar, "questTemp.Mtraxx.Chest") && pchar.location == "shore37")
		{
			dialog.text = "Entonces, el cofre está preparado. Podría intentar encontrar todo el material requerido por mí mismo, pero prefiero ir a ver a Fadey. Me parece un hombre que puede conseguir cualquier cosa.";
			link.l1 = "*USA UNA OPCIÓN DE PENSAR EN VOZ ALTA PARA TERMINAR DE RECOGER MUNICIONES*";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_PlantChestReadyExit");
		}
		if (CheckAttribute(pchar, "questTemp.Mtraxx.Boats") && pchar.location == "Maracaibo_river")
		{
			dialog.text = "Entonces, tenemos que construir seis botes largos. Para esto necesito un carpintero, 20 tablas y 10 paquetes de cuero";
			link.l1 = "*USA UNA OPCIÓN DE PENSAR EN VOZ ALTA PARA EMPEZAR A CONSTRUIR BOTES LARGOS*";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Boats");
			AddQuestRecord("Roger_5", "11");
		}
		if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder") && pchar.location == "shore10")
		{
			dialog.text = "Entonces, tengo la intención de simplemente volar este montón de viejos árboles hasta el cielo. Todo lo que necesito para esto son 300 unidades de pólvora solo para estar seguro.";
			link.l1 = "*usa una opción de Pensar en Voz Alta para ordenar la colocación de pólvora*";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder");
			pchar.questTemp.Mtraxx.Retribution = "powder";
			chrDisableReloadToLocation = false;
		}
		if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed") && pchar.location == "Judgement_dungeon_01")
		{
			dialog.text = RandSwear() + " ¡La salida está sellada! ¡Parece que bloquearon la puerta con algo pesado! " + RandSwear() + "\nSilencio... ¿Qué demonios?";
			link.l1 = "";
			link.l1.go = "mtraxx_dungeon";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed");
		}
		if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead") && pchar.location == "Judgement_church")
		{
			dialog.text = "Esto es todo... Fin de la línea\n Parece que don Enrico estaba en serio: no hay salida de estas mazmorras. Tuve un momento de esperanza cuando encontré una segunda puerta a nivel del agua pero ahora... He perdido la cuenta del tiempo, ¿cuánto tiempo llevo merodeando estos oscuros túneles? ¿Medio día, todo el día? Este lugar es tan silencioso y aterrador como un ataúd\nAquí había una iglesia una vez, justo aquí. Qué lugar tan perfecto para decir mis oraciones. He pecado mucho, demasiado... Rezaré y dormiré aquí, mis heridas y mi agotamiento me están matando. Si tengo suerte nunca me levantaré...";
			link.l1 = "";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead");
			AddDialogExitQuestFunction("Mtraxx_RetributionBead");
		}
		// belamour legendary edition -->
		if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice") && pchar.questTemp.Mtraxx.Retribution.Choice == "to_choice")
		{
			dialog.text = "";
			link.l1 = "¡Yo, Charles de Maure, capitán francés y noble, juro por mí mismo y mi conciencia que he terminado con mi pasado pirata para siempre!";
			link.l1.go = "Good_Choice";
			link.l2 = "¡Sí! ¡Sí! ¡Ah ja ja!! Lo hice, sobreviví! ¡Cómetelo, Zorro! ¡Vete al infierno, Marcus! ¡Ahora estoy solo! Charlie Prince puede haber muerto, ¡pero a Charles de Maure nadie lo matará jamás!";
			link.l2.go = "Bad_Choice";
		}
		// <-- legendary edition

		if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog"))
		{
			dialog.text = "¿Qué deberíamos hacer?";
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.FirstTime"))
			{
				DeleteAttribute(pchar, "questTemp.TonzagQuest.JailDialog.FirstTime");
				dialog.text = "... por supuesto, Levasseur no es ningún tonto. ¿De lo contrario, por qué tendrían que arrestarnos justo en este momento?\n¡Y no dijeron una palabra!\n" + dialog.text;
			}

			DeleteAttribute(link, "l1");
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Helena"))
			{
				link.l1 = "Helen, ¿por qué estás tan callada?";
				link.l1.go = "tonzag_jail_helena";
			}

			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Mary"))
			{
				link.l2 = "¡María!, ¿por qué pareces tan feliz?";
				link.l2.go = "tonzag_jail_mary";
			}

			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Tichingitu"))
			{
				link.l3 = "¿Tichingitu? Di algo apropiado para la situación.";
				link.l3.go = "tonzag_jail_tichingitu";
			}

			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Tonzag"))
			{
				link.l4 = "¿Hercule, puedes oírme? ¿Qué vamos a hacer?";
				link.l4.go = "tonzag_jail_tonzag";
			}

			link.l5 = "Nada que hacer. Supongo que usaré los zapatos de Michel por un tiempo.";
			link.l5.go = "tonzag_exit";
		}

		if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailPanic"))
		{
			dialog.text = "";
			link.l1 = "¡Dios mío, han matado a Hercule!";
			link.l1.go = "exit";
			link.l2 = "¡Vosotros bastardos!";
			link.l2.go = "exit";

			DeleteAttribute(pchar, "questTemp.TonzagQuest.JailPanic");
			AddDialogExitQuestFunction("Tonzag_GFAfterShot");
		}

		if (CheckAttribute(pchar, "questTemp.HelenDrinking.RefusedGame"))
		{
			dialog.text = "¡Vaya una noche! ¿Por qué la escuché? Mi hermano tenía razón: las chicas de aquí son completamente diferentes. ¿Quizás le añaden algo al ron?";
			link.l1 = "¡Hora de dormir, y luego a Cartagena!";
			link.l1.go = "exit";

			DeleteAttribute(pchar, "questTemp.HelenDrinking.RefusedGame");

			AddDialogExitQuestFunction("HelenDrinking_LightsOut1");
		}

		if (CheckAttribute(pchar, "questTemp.PZ_OsmatrivaemSunduk"))
		{
			dialog.text = "No se robó ni una sola cosa, aunque todo está esparcido por todas partes. Incluso los objetos de valor no han sido tocados.";
			link.l1 = "No intentaban robarme, buscaban algo específico. ¿Pero qué? Y más importante aún, ¿quién...?";
			link.l1.go = "exit";

			DeleteAttribute(pchar, "questTemp.PZ_OsmatrivaemSunduk");

			AddDialogExitQuest("PZ_OsmatrivaemSunduk_3");
		}

		if (CheckAttribute(pchar, "questTemp.PZ_GotovimShlupki"))
		{
			dialog.text = "Esperemos hasta el anochecer y ¡ataquemos!";
			link.l1 = "Comenzaremos a preparar los botes largos mientras tanto.";
			link.l1.go = "exit";

			DeleteAttribute(pchar, "questTemp.PZ_GotovimShlupki");

			AddDialogExitQuest("PZ_ShturmZvezdy");
		}

		if (CheckAttribute(pchar, "questTemp.PZ_TiboUkralDevu"))
		{
			dialog.text = "Dios mío... No, no, no...";
			link.l1 = "";
			link.l1.go = "exit";

			DeleteAttribute(pchar, "questTemp.PZ_TiboUkralDevu");

			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "kneeling", "1", 7.5);
		}

		if (CheckAttribute(pchar, "questTemp.PZ_DevaMertva"))
		{
			dialog.text = "Oh Dios, oh Dios, oh Dios... ¿Por qué? Oh Dios, por qué... pero hice todo lo que pude...";
			link.l1 = "Es toda mi culpa, solo mía. No llegué aquí a tiempo. Lo siento mucho... Por favor, por favor perdóname.";
			link.l1.go = "exit";

			DeleteAttribute(pchar, "questTemp.PZ_DevaMertva");

			AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva8");
		}
		break;

	// boal -->
	case "TalkSelf_Main":
		NextDiag.TempNode = "First time";
		// navy --> after duel in tavern
		if (CheckAttribute(pchar, "questTemp.LocationClone"))
		{
			Dialog.Text = RandPhraseSimple("Esa fue una pelea infernal... Ahora podemos llamar a esos cobardes que huyeron...", "¡Ja! Eso fue fácil. ¡Y esos perros de tierra simplemente se dispersaron!");
			link.l1 = "...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LocationClone");
			break;
		}
		// navy <--
		Dialog.Text = RandPhraseSimple("¿Hmm... Entonces qué debería hacer ahora?", "¿Qué hacer ahora?");
		if (!bDisableMapEnter && pchar.location == Get_My_Cabin())
		{
			// navy --> 13.02.08
			if (!bDisableMapEnter && GetCompanionQuantity(PChar) > 1)
			{
				link.l3 = "Llama a un compañero.";
				link.l3.go = "Cabin_CompanionSelect";
			}
			// navy <--
		}
		else
		{ // исп.линейка, квест №6, возможность переночевать в оплаченной комнате
			if (CheckAttribute(pchar, "questTemp.State.Open") && pchar.location == "Tortuga_tavern_upstairs")
			{
				if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
				{
					link.l1 = "Descansa hasta la mañana.";
					link.l1.go = "TalkSelf_room_day";
				}
				else
				{
					link.l1 = "Descansa hasta la noche.";
					link.l1.go = "TalkSelf_room_night";
					link.l2 = "Descansa hasta la próxima mañana.";
					link.l2.go = "TalkSelf_room_day";
				}
			}
		}
		if (!bDisableMapEnter) // боя в море нет
		{
			if (GetCargoGoods(pchar, GOOD_SLAVES) > 0)
			{
				Link.l5 = "Enlista a los esclavos en la tripulación.";
				Link.l5.go = "TalkSelf_SlavesToCrew";
			}
		}
		// захват города
		if (GetCharIDXForTownAttack(pchar.location) != -1 && !CheckAttribute(Pchar, "GenQuestFort.StartAttack") && !CheckAttribute(Pchar, "questTemp.Sharlie.DefendSP"))
		{
			Link.l6 = "Empieza a capturar el pueblo más cercano.";
			Link.l6.go = "TalkSelf_TownAttack";
		}

		bool bSeaBattle = (bDisableMapEnter) && (bSeaActive) && (!CheckAttribute(pchar, "GenQuest.MapClosedNoBattle"));
		if (!bSeaBattle && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard", 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar, "GenQuest.CannotWait") && !CheckAttribute(loadedLocation, "CannotWait"))
		{
			Link.l7 = "Debería descansar...";
			Link.l7.go = "TalkSelf_StartWait";
		}

		if (CheckAttribute(pchar, "equip.gun"))
		{
			if (CheckAttribute(pchar, "chr_ai.gun.bulletNum") && sti(pchar.chr_ai.gun.bulletNum) > 1)
			{
				Link.l8 = "Quiero cambiar la munición para las armas de fuego.";
				Link.l8.go = "SetGunBullets";
			}
		}

		if (CheckAttribute(pchar, "equip.musket"))
		{
			if (CheckAttribute(pchar, "chr_ai.musket.bulletNum") && sti(pchar.chr_ai.musket.bulletNum) > 1)
			{
				Link.l9 = "Quiero cambiar la munición para el mosquete.";
				Link.l9.go = "SetMusketBullets";
			}
			Link.l10 = "Quiero elegir un arma prioritaria para el combate.";
			Link.l10.go = "SetPriorityMode";
		}

		Link.l19 = "Quiero seleccionar una poción para uso constante.";
		Link.l19.go = "ChoosePotion";

		//--> Голландский гамбит
		if (CheckAttribute(pchar, "questTemp.HWIC_Coordinates") && PChar.location == Get_My_Cabin())
		{
			Link.l11 = "Intenta encontrar la isla por las coordenadas en el mapa.";
			Link.l11.go = "Seek_AbyIsland";
		}
		//<-- Голландский гамбит

		//--> Ложный след
		if (CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabin" && PChar.location == Get_My_Cabin())
		{
			Link.l13 = "Llama a Adam Rayner.";
			Link.l13.go = "FalseTrace_Cabin";
		}
		if (CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "CatchAdam" && PChar.location == Get_My_Cabin())
		{
			Link.l13 = "Arresta a Adam Rayner.";
			Link.l13.go = "FalseTrace_Cabin";
		}
		//<-- Ложный след
		// Addon 2016-1 Jason Пиратская линейка
		if (CheckAttribute(pchar, "questTemp.Mtraxx.Ammo") && PChar.location == "Shore37") // прогон 3
		{
			Link.l17 = "Suma el contenido del cofre y decide terminar de reunir municiones para Picard.";
			Link.l17.go = "mtraxx_ammo";
		}
		if (CheckAttribute(pchar, "questTemp.Mtraxx.Mutiny") && pchar.location == "Maracaibo_Plantation" && stf(environment.time) >= 3.00 && stf(environment.time) < 4.00)
		{
			Link.l17 = "Da una orden para atacar la plantación de Maracaibo.";
			Link.l17.go = "mtraxx_mutiny";
		}
		if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_boats" && pchar.location == "Maracaibo_river")
		{
			Link.l17 = "Da la orden de construir botes largos.";
			Link.l17.go = "mtraxx_boats";
		}
		if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "powder" && pchar.location == "shore10")
		{
			Link.l17 = "Ordena entregar la pólvora al abatis muerto.";
			Link.l17.go = "mtraxx_powder";
		}
		// Jason Долго и счастливо
		if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "letter")
		{
			Link.l18 = "Piensa en una boda.";
			Link.l18.go = "LH_marry";
		}
		if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "marry_offer" && LongHappy_CheckShore()) // 28-03-20
		{
			Link.l18 = "Haz una propuesta de matrimonio.";
			Link.l18.go = "LH_marry_3";
		}
		if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "toIslaTesoro" && pchar.location == "Pirates_town")
		{
			Link.l18 = "Prepara la celebración.";
			Link.l18.go = "LH_marry_4";
		}
		// -->Авторемонт
		if (Pchar.Location == Pchar.location.from_sea && CheckOfficersPerk(pchar, "SelfRepair") && CheckSelfRepairConditions())
		{
			Link.l14 = "Comienza a reparar los barcos";
			Link.l14.go = "StartSelfRepair";
		}
		// <--Авторемонт
		//--> завершение игры
		if (CheckAttribute(pchar, "questTemp.Tieyasal_WinEnd")) // patch-9
		{
			Link.l15 = "Termina los asuntos en el Caribe y navega hacia Europa.";
			Link.l15.go = "final_1";
		}
		//<-- завершение игры
		Link.l20 = RandPhraseSimple("No ahora. No hay tiempo.", "Sin tiempo para eso, demasiado que hacer.");
		Link.l20.go = "exit";
		break;

	case "tonzag_exit":
		DialogExit_Self();
		AddDialogExitQuestFunction("Tonzag_CreateKiller");
		break;

	case "StartSelfRepair":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit_Self();
		LaunchRepair(pchar);
		break;

	case "SetGunBullets":
		Dialog.Text = "Selecciona el tipo de munición:";
		sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
		rItm = ItemsFromID(sGun);
		makearef(rType, rItm.type);
		for (i = 0; i < sti(pchar.chr_ai.gun.bulletNum); i++)
		{
			sAttr = GetAttributeName(GetAttributeN(rType, i));
			sBullet = rItm.type.(sAttr).bullet;
			rItem = ItemsFromID(sBullet);
			attrL = "l" + i;
			Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
			;
			Link.(attrL).go = "SetGunBullets1_" + i;
		}
		break;

	case "SetGunBullets2":
		i = sti(PChar.GenQuest.SetGunBullets) + 1;
		sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
		rItm = ItemsFromID(sGun);
		sAttr = "t" + i;
		sBullet = rItm.type.(sAttr).bullet;
		LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, sBullet);
		LAi_GunSetUnload(pchar, GUN_ITEM_TYPE);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DeleteAttribute(pchar, "GenQuest.SetGunBullets");
		DialogExit_Self();
		break;

	case "SetMusketBullets":
		Dialog.Text = "Selecciona el tipo de munición:";
		sGun = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
		rItm = ItemsFromID(sGun);
		makearef(rType, rItm.type);
		for (i = 0; i < sti(pchar.chr_ai.musket.bulletNum); i++)
		{
			sAttr = GetAttributeName(GetAttributeN(rType, i));
			sBullet = rItm.type.(sAttr).bullet;
			rItem = ItemsFromID(sBullet);
			attrL = "l" + i;
			Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
			;
			Link.(attrL).go = "SetMusketBullets1_" + i;
		}
		break;

	case "SetMusketBullets2":
		i = sti(PChar.GenQuest.SetMusketBullets) + 1;
		sGun = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
		rItm = ItemsFromID(sGun);
		sAttr = "t" + i;
		sBullet = rItm.type.(sAttr).bullet;
		LAi_SetCharacterUseBullet(pchar, "musket", sBullet);
		LAi_GunSetUnload(pchar, "musket");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DeleteAttribute(pchar, "GenQuest.SetMusketBullets");
		DialogExit_Self();
		break;

	case "SetPriorityMode":
		Dialog.Text = "Al comienzo de la pelea usaré:";
		Link.l1 = "Espada";
		Link.l1.go = "BladePriorityMode";
		Link.l2 = "Escopeta";
		Link.l2.go = "MusketPriorityMode";
		break;

	case "BladePriorityMode":
		pchar.PriorityMode = 1;
		DialogExit_Self();
		break;

	case "MusketPriorityMode":
		pchar.PriorityMode = 2;
		DialogExit_Self();
		break;

	case "ChoosePotion":
		Dialog.Text = "Selecciona poción:";
		Link.l1 = "Poción de curación.";
		Link.l1.go = "ChoosePotion1";
		Link.l2 = "Elixir.";
		Link.l2.go = "ChoosePotion2";
		Link.l3 = "Mezcla.";
		Link.l3.go = "ChoosePotion3";
		Link.l4 = "Raíz de jengibre.";
		Link.l4.go = "ChoosePotion4";
		Link.l5 = "Ron.";
		Link.l5.go = "ChoosePotion5";
		Link.l6 = "Vino.";
		Link.l6.go = "ChoosePotion6";
		if (CheckAttribute(pchar, "GenQuest.Potion_choice"))
		{
			Link.l7 = "Quiero seleccionar pociones automáticamente.";
			Link.l7.go = "ChoosePotion7";
		}
		Link.l8 = "Espera, he cambiado de opinión..";
		Link.l8.go = "ChoosePotion8";
		break;

	case "ChoosePotion1":
		log_info("Por defecto se utilizará una esencia curativa.");
		pchar.GenQuest.Potion_choice = "potion1";
		DialogExit_Self();
		break;

	case "ChoosePotion2":
		log_info("Se utilizará un elixir por defecto.");
		pchar.GenQuest.Potion_choice = "potion2";
		DialogExit_Self();
		break;

	case "ChoosePotion3":
		log_info("Por defecto se utilizará una mezcla.");
		pchar.GenQuest.Potion_choice = "potion4";
		DialogExit_Self();
		break;

	case "ChoosePotion4":
		log_info("Por defecto se utilizará una raíz de jengibre.");
		pchar.GenQuest.Potion_choice = "potion5";
		DialogExit_Self();
		break;

	case "ChoosePotion5":
		log_info("El ron se utilizará por defecto.");
		pchar.GenQuest.Potion_choice = "potionrum";
		DialogExit_Self();
		break;

	case "ChoosePotion6":
		log_info("Se utilizará vino por defecto.");
		pchar.GenQuest.Potion_choice = "potionwine";
		DialogExit_Self();
		break;

	case "ChoosePotion7":
		log_info("Las pociones se seleccionarán automáticamente.");
		DeleteAttribute(pchar, "GenQuest.Potion_choice");
		DialogExit_Self();
		break;

	case "ChoosePotion8":
		DialogExit_Self();
		break;

	case "TalkSelf_StartWait":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit_Self();
		PChar.GenQuest.CallFunctionParam = "LaunchTavernWaitScreen";
		DoQuestCheckDelay("CallFunctionParam", 0.1); // Нужно с задержкой, иначе - ГГ начинает крутиться
		break;

	case "TalkSelf_room_night":
		NextDiag.CurrentNode = NextDiag.TempNode;
		// AddDialogExitQuestFunction("TavernWaitDate_Night");
		TavernWaitDate("wait_night");
		DialogExit_Self();
		break;

	case "TalkSelf_room_day":
		NextDiag.CurrentNode = NextDiag.TempNode;
		// AddDialogExitQuestFunction("TavernWaitDate_Day");
		TavernWaitDate("wait_day");
		DialogExit_Self();
		break;
	//  захват города
	case "TalkSelf_TownAttack":
		int needCrew = 500;
		if (CheckOfficersPerk(pchar, "Troopers"))
			needCrew = 300;
		bOk = (GetPartyCrewQuantity(Pchar, true) >= needCrew) || bBettaTestMode;
		if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk)
		{
			chr = GetCharacter(GetCharIDXForTownAttack(pchar.location));
			if (chr.from_sea == Pchar.location.from_sea)
			{
				Dialog.Text = "Podríamos empezar a capturar el pueblo, pero el barco no resistiría los salvos de los cañones del fuerte por mucho tiempo, y no podríamos enviar un grupo de desembarco.";
				Link.l1 = "...";
				Link.l1.go = "exit";
			}
			else
			{
				if (pchar.location == "Panama_ExitTown" || pchar.location == "Tortuga_ExitTown" || pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_ExitTown") // patch-5
				{
					Dialog.Text = "No, aún no estoy tan loco..";
					Link.l1 = "...";
					Link.l1.go = "exit";
				}
				else
				{
					if (pchar.location == "LosTeques_ExitTown")
					{
						Dialog.Text = "No tiene sentido atacar esta mina sin primero recabar información sobre el oro y la plata que se extrae allí. De lo contrario, estaré enviando a mis hombres a morir en vano.";
						Link.l1 = "...";
						Link.l1.go = "exit";
					}
					else
					{
						Dialog.Text = "Ataque " + GetCityName(chr.City) + ".";
						if (CheckAttribute(pchar, "questTemp.Patria.SanJoseAttack") && pchar.location == "PortSpein_ExitTown") // Jason НСО
						{
							Link.l1 = "¡Deja de hacer el tonto! ¡Alto!";
							Link.l1.go = "exit";
							break;
						}
						if (CheckAttribute(pchar, "questTemp.Patria")) // Jason НСО
						{
							if (pchar.questTemp.Patria != "fail" || pchar.questTemp.Patria != "complete")
							{
								if (pchar.location == "Marigo_ExitTown" || pchar.location == "Villemstad_ExitTown")
								{
									Link.l1 = "¡Deja de hacer el tonto! ¡Alto!";
									Link.l1.go = "exit";
									break;
								}
							}
						}
						Link.l1 = "¡A las armas!";
						Link.l1.go = "TalkSelf_TownAttack_Start";
						Link.l2 = "¡Alto!";
						Link.l2.go = "exit";
					}
				}
			}
		}
		else
		{
			if (!CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
			{
				Dialog.Text = "¡Eh! No hay suficiente gente en la tripulación; necesitamos al menos " + needCrew + " hombres.";
				Link.l1 = "...";
				Link.l1.go = "exit";
			}
			else
			{
				Dialog.Text = "¡No os disperséis! ¡Continuad con el ataque!";
				Link.l2 = "...";
				Link.l2.go = "exit";
			}
		}
		break;

	case "TalkSelf_TownAttack_Start":
		NextDiag.CurrentNode = NextDiag.TempNode;

		Pchar.GenQuestFort.StartAttack = true;
		Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
		DeleteQuestAttribute("Union_with_Escadra");
		chr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
		if (isCityHasFort(chr.City))
		{
			SetLocationCapturedState(chr.from_sea, true);
		}
		else
		{
			SetLocationCapturedState(chr.Default, true); // для сухопутных
		}
		AddDialogExitQuest("Capture_Forts");
		Ship_NationAgressive(chr, chr);
		DialogExit_Self();
		break;
	// Зачислить рабов в команду  -->
	case "TalkSelf_SlavesToCrew":
		if (GetCurCrewEscadr() >= GetMaxCrewAble())
		{
			Dialog.Text = "Ninguno de los esclavos está dispuesto a unirse a la tripulación.";
			Link.l1 = "¡Al diablo con ellos!";
			Link.l1.go = "exit";
		}
		else
		{
			if (GetCrewQuantity(pchar) >= GetMaxCrewQuantity(pchar))
			{
				Dialog.Text = "No hay espacio libre en el barco para nuevos marineros.";
				Link.l1 = "¡Je! Necesitaré transferir parte de la tripulación a otro barco.";
				Link.l1.go = "exit";
			}
			else
			{
				if (GetFreeCrewQuantity(pchar) <= GetCargoGoods(pchar, GOOD_SLAVES))
				{
					pchar.GenQuest.SlavesToCrew = GetFreeCrewQuantity(pchar);
				}
				else
				{
					pchar.GenQuest.SlavesToCrew = GetCargoGoods(pchar, GOOD_SLAVES);
				}
				Dialog.Text = "Tu tripulación puede ser reabastecida con " + pchar.GenQuest.SlavesToCrew + " esclavos que quieren servir bajo tu mando. ¿Te gustaría aceptar?";
				Link.l1 = "Sí";
				Link.l1.go = "TalkSelf_SlavesToCrew_1";
				Link.l2 = "No";
				Link.l2.go = "exit";
			}
		}
		break;

	case "TalkSelf_SlavesToCrew_1":
		bOk = ShipBonus2Artefact(pchar, SHIP_MEMENTO) && CheckAttribute(&RealShips[sti(pchar.Ship.Type)], "DeadSailors.RecruitSlaveBonus");
		if(!bOk)
		{
			// belamour legendary edition перк получил время работы, старый метод не подходит
			if (GetOfficersPerkUsing(pchar, "IronWill"))
			{
				AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 5.0))
			}
			else
			{
				AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 3.0))
			}
		}
		ChangeCharacterComplexReputation(pchar, "authority", -0.5);
		// падение опыта -->
		fTemp = stf(GetCrewQuantity(pchar) + sti(pchar.GenQuest.SlavesToCrew));
		pchar.Ship.Crew.Exp.Sailors = (stf(pchar.Ship.Crew.Exp.Sailors) * GetCrewQuantity(pchar) +
									   stf(pchar.Ship.Crew.Exp.Sailors) * 0.3 * sti(pchar.GenQuest.SlavesToCrew)) /
									  fTemp;
		pchar.Ship.Crew.Exp.Cannoners = (stf(pchar.Ship.Crew.Exp.Cannoners) * GetCrewQuantity(pchar) +
										 stf(pchar.Ship.Crew.Exp.Cannoners) * 0.3 * sti(pchar.GenQuest.SlavesToCrew)) /
										fTemp;
		pchar.Ship.Crew.Exp.Soldiers = (stf(pchar.Ship.Crew.Exp.Soldiers) * GetCrewQuantity(pchar) +
										stf(pchar.Ship.Crew.Exp.Soldiers) * 0.3 * sti(pchar.GenQuest.SlavesToCrew)) /
									   fTemp;
		// падение опыта <--
		pchar.Ship.Crew.Quantity = sti(pchar.Ship.Crew.Quantity) + sti(pchar.GenQuest.SlavesToCrew);
		RemoveCharacterGoodsSelf(pchar, GOOD_SLAVES, sti(pchar.GenQuest.SlavesToCrew));

		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit_Self();
		break;
		// Зачислить рабов в команду  <--
		// boal <--

		// navy CONTRABAND METRO -->
	case "GenTravel_Main":
		NextDiag.TempNode = "First time";
		dialog.Text = "¡Este dulce barco es mío ahora, y yo soy el capitán aquí! Es una lástima que tuve que matar a toda la tripulación, aunque.";
		Link.l1 = "Es hora de desembarcar...";
		Link.l1.go = "exit";

		chr = CharacterFromID("Abracham_Gray");
		chr.location = "none";
		SeaExchangeCharactersShips(PChar, chr, false, false);
		SetCrewQuantity(PChar, 0);

		// грузим ГГ куда нужно...
		SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc, pchar.GenQuest.contraTravel.destination.group, pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
		AddDialogExitQuest("AnyReloadToLocation");
		chrDisableReloadToLocation = false;

		CloseQuestHeader("Gen_ContrabandTravel");
		setCharacterShipLocation(PChar, pchar.GenQuest.contraTravel.destination.loc);
		setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);

		// трем аттрибуты
		DeleteAttribute(PChar, "GenQuest.contraTravel");
		break;
		// navy CONTRABAND METRO <--

		// navy --> 13.02.08
	case "Cabin_CompanionSelect":
		Dialog.Text = "¿Qué compañero invocar?";
		for (i = 1; i < GetCompanionQuantity(PChar); i++)
		{
			chr = GetCharacter(GetCompanionIndex(PChar, i));
			if (!CheckAttribute(chr, "Tasks.Clone") && sti(chr.Payment) == true)
			{
				sAttr = "l" + i;
				rShip = GetRealShip(sti(chr.Ship.Type));
				link.(sAttr) = GetFullName(chr) + ", " + xiStr(rShip.BaseName) + " '" + chr.Ship.Name + "'.";
				link.(sAttr).go = "CabinCompanionTalk_" + i;
			}
		}
		link.l9 = "En otro momento.";
		link.l9.go = "exit";
		break;

	case "Cabin_Companion_Talk":
		i = sti(PChar.GenQuest.CabinCompanionNum);
		PlaceCompanionCloneNearMChr(i, false);

		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit_Self();
		break;
		// navy <--

	//--> Голландский гамбит
	case "Seek_AbyIsland":
		bOk = CheckCharacterItem(pchar, "bussol") && CheckCharacterItem(pchar, "clock2");
		bool bOk1 = CheckCharacterItem(pchar, "sextant2");
		if (bOk || bOk1)
		{
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC_Coordinates");
			pchar.questTemp.HWIC_FindIsland = "true";
			AddDialogExitQuestFunction("PrepareSearchingFor");
		}
		else
		{
			dialog.text = "Lástima que no tenga los instrumentos de navegación necesarios para determinar la latitud y longitud. Tendré que buscar la isla en otro momento. ";
			link.l1 = "";
			link.l1.go = "exit";
		}
		break;
	//<-- Голландский гамбит

	//--> Ложный след
	case "FalseTrace_Cabin":
		dialog.text = "¡Contramaestre! ¡Trae a Adam Rayner ante mí de inmediato!";
		link.l1 = "¡A la orden, capitán!";
		link.l1.go = "exit";
		chr = characterFromId("Mugger");
		if (pchar.questTemp.FalseTrace == "CatchAdam")
			chr.dialog.currentnode = "FalseTrace_17";
		else
			chr.dialog.currentnode = "FalseTrace_7";
		pchar.questTemp.FalseTrace.CharID = "Mugger";
		AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;

	case "FalseTrace_Woman":
		DialogExit();
		chr = characterFromId("FalseTraceWife");
		chr.dialog.currentnode = "FalseTrace_wife_6";
		pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
		AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;
	//<-- Ложный след

	//--> LSC, приколы со стуком в дверь
	case "knock_2":
		PlaySound("interface\knock_2.wav");
		dialog.text = "Entonces, toqué, ahora esperemos la respuesta...";
		link.l1 = "(espera)";
		link.l1.go = "knock_wrong";
		break;

	case "knock_3":
		PlaySound("interface\knock.wav");
		dialog.text = "Entonces, toqué, ahora esperemos la respuesta...";
		link.l1 = "(espera)";
		link.l1.go = "knock_wrong";
		break;

	case "knock_3_1":
		PlaySound("interface\knock_3_1.wav");
		dialog.text = "Entonces, llamé, ahora esperemos la respuesta...";
		link.l1 = "(espera)";
		link.l1.go = "knock_wrong";
		break;

	case "knock_1_3":
		PlaySound("interface\knock_1_3.wav");
		dialog.text = "Entonces, llamé, ahora esperemos la respuesta...";
		link.l1 = "(espera)";
		link.l1.go = "knock_wrong";
		break;

	case "knock_2_2":
		PlaySound("interface\knock_2_2.wav");
		dialog.text = "Entonces, llamé, ahora esperemos la respuesta...";
		link.l1 = "(espera)";
		link.l1.go = "knock_right";
		break;

	case "knock_wrong":
		dialog.text = "No está abriendo la puerta... Supongo que utilicé el toque secreto equivocado. Bien, vendré mañana y lo intentaré de nuevo. Hoy, seguro que no abrirá la puerta.";
		link.l1 = "(vete)";
		link.l1.go = "exit";
		break;

	case "knock_right":
		PlaySound("interface\key.wav");
		PlaySound("Voice\Spanish\YouFace.wav");
		dialog.text = "¡Vaya! ¡Respondió y abrió la puerta! Ahora puedo entrar...";
		link.l1 = "(entrar)";
		link.l1.go = "exit";
		DeleteAttribute(pchar, "questTemp.LSC.DiffIndoor");
		LocatorReloadEnterDisable("LostShipsCity_town", "reload74", false);
		break;
	//<-- LSC, приколы со стуком в дверь

	// суп из черепахи
	case "terrapin":
		PlaySound("Interface\Door_Kick.wav");
		PlaySound("Voice\Spanish\YouFace_2.wav");
		dialog.text = "¡Caramba! Así que esa es la ayuda retrasada para Levasseur... De ninguna manera puedo salir por la puerta... Está bien, seguiré los pasos de Thibaut, ¡por la ventana! Después de todo, este bribón logró escaparse de alguna manera.";
		link.l1 = "";
		link.l1.go = "exit";
		AddDialogExitQuest("Terrapin_GoWindow");
		break;

	// защита Сен-Пьера
	case "SP_defend":
		PlaySound("Voice\Spanish\YouFace_4.wav");
		dialog.text = "Entonces, nuestra misión es repeler el ataque de los malditos españoles, y salvar a Saint-Pierre. El fuerte ha sido capturado, y se está librando una batalla en las calles. Hay una poderosa escuadra en la bahía de Saint-Pierre y tienen un buque de línea como nave insignia. Atacarlo ahora es inútil. El fuerte y la ciudad están bajo control enemigo, por lo que no nos dejarán desembarcar en el puerto.\nPor lo tanto, he decidido avanzar a través de la jungla y golpearlos por detrás a través de las puertas de la ciudad. Una vez que el fuerte y la ciudad sean liberados de los españoles, nos ocuparemos de la escuadra. Se volverá mucho más vulnerable sin el apoyo de fuego del fuerte\nEsto no será fácil, por lo que he dado órdenes de pagar cien mil pesos extra para distribuir entre la tripulación además del salario normal. ¡Vamos!";
		link.l1 = "";
		link.l1.go = "exit";
		AddDialogExitQuest("DefendSP_GoJungle");
		break;

	// финал игры
	case "final_1":												   // Jason НСО
		if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) // генерал-губернатор никуда не уедет
		{
			dialog.text = "¡Espera!, ¿adónde voy? ¡No puedo dejar el cargo de Gobernador General sin permiso de París! De lo contrario, sin duda alguna seré arrestado cuando regrese a Francia por el abandono no autorizado de las colonias que me confiaron. París, te echaré de menos ...";
			link.l1 = "";
			link.l1.go = "exit";
			EndQuestMovie();
		}
		else
		{
			dialog.text = "¡Entonces no perdamos más tiempo! ¡Extraño tanto los campos de mi querida Gascuña! ¡Levanta el ancla!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Final_ReturnToEurope");
		}
		break;

	case "final_2":
		dialog.text = "¡Creo que esta es la decisión correcta! ¿Qué me queda en la buena y vieja Europa, cuando me encontré aquí? Además, puedo volver a Francia cuando quiera, de todos modos!";
		link.l1 = "";
		link.l1.go = "exit";
		AddDialogExitQuest("Final_StayInCarribean"); // 010912
		DeleteAttribute(pchar, "questTemp.Tieyasal_final");
		break;

	// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
	case "FMQN_1":
		dialog.text = "Esa es la mejor manera. Debería subir a bordo y zarpar de aquí.";
		link.l1 = "";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("FMQN_ChooseExit");
		break;

	case "FMQN_2":
		dialog.text = "Nah, de ninguna manera, me quedo. Pero diablos, no me quedaré aquí esperando a Dios sabe qué. Debería navegar al puerto de Philipsburg e investigar la situación. No me agrada la idea de ser una herramienta en manos de algún maldito inglés mentiroso.";
		link.l1 = "";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("FMQN_ChooseContinue");
		break;

	// Addon 2016-1 Jason Пиратская линейка
	case "mtraxx_ammo":
		Mtraxx_PlantCheckShoreBox();																							 // анализируем содержимое сундука
		if (CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.Blade") && !CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.NoBlade")) // собрали 30 сабель
		{
			dialog.text = "¡Treinta piezas de acero frío están en el cofre! ¿Debería parar ahora, o debería reunir más armas de fuego, cargas y pociones?";
			link.l1 = "¡Esto es suficiente!";
			link.l1.go = "mtraxx_ammo_1";
			link.l2 = "No, debería seguir llenando este cofre.";
			link.l2.go = "exit";
			// belamour legendary edition
			if (CheckAttribute(pchar, "questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Full")
			{
				link.l3 = "Llena con el contenido del cofre de Fadey y lleva el exceso.";
				link.l3.go = "mtraxx_ammo_1";
			}
		}
		else
		{
			dialog.text = "Todavía no se han recogido treinta piezas de acero frío! Debería traer más.";
			link.l1 = "";
			link.l1.go = "exit";
		}
		break;

	case "mtraxx_ammo_1":
		DelMapQuestMarkCity("baster");
		DelLandQuestMark(characterFromId("Fadey"));
		dialog.text = "Cerrando el cofre y haciendo un plan para llevarlo a la plantación a hurtadillas.";
		link.l1 = "";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_PlantShoreBoxComplete");
		break;

	case "mtraxx_mutiny":
		dialog.text = "¡Vamos, al ataaaque! ¡Huurra!";
		link.l1 = "";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_PlantMutiny");
		break;

	case "mtraxx_boats":
		if (GetSquadronGoods(pchar, GOOD_PLANKS) >= 20 && GetSquadronGoods(pchar, GOOD_LEATHER) >= 10) // наличие материалов
		{
			if (Mtraxx_MeridaCheckCarpenter()) // наличие плотника
			{
				dialog.text = "Todos los materiales requeridos están preparados, deberíamos empezar a construir los botes largos de inmediato.";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("Mtraxx_MeridaBuildBoats");
			}
			else
			{
				dialog.text = "No tengo un carpintero experimentado capaz de realizar el trabajo. Debería asignar a un oficial a esta posición.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		}
		else
		{
			dialog.text = "No hay suficientes materiales, necesitamos al menos 20 paquetes de tablas más 10 fardos de cuero.";
			link.l1 = "";
			link.l1.go = "exit";
		}
		break;

	case "mtraxx_powder":
		if (GetSquadronGoods(pchar, GOOD_POWDER) >= 300) // наличие пороха
		{
			if (GetCrewQuantity(pchar) >= 20) // наличие команды
			{
				dialog.text = "¡Todo está listo para una explosión!";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("Mtraxx_RetributionBarrels");
			}
			else
			{
				dialog.text = "Necesito al menos 20 hombres para entregar la pólvora.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		}
		else
		{
			dialog.text = "No hay suficiente pólvora, se necesita al menos 300.";
			link.l1 = "";
			link.l1.go = "exit";
		}
		break;

	case "mtraxx_dungeon":
		PlaySound("ambient\jail\jail_door2.wav");
		dialog.text = "¿Fue una puerta?";
		link.l1 = "";
		link.l1.go = "mtraxx_dungeon_1";
		break;

	case "mtraxx_dungeon_1":
		PlaySound("ambient\jail\jail_door1.wav");
		dialog.text = "¡Correcto! Tenemos visitantes... ¿Jan?..";
		link.l1 = "";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_RetributionRunToEnrico");
		break;
	// belamour legendary edition -->
	case "Good_Choice":
		pchar.questTemp.Mtraxx.Retribution.Choice = "good";
		DoQuestCheckDelay("Mtraxx_RetributionFreedom", 0.5);
		DialogExit_Self();
		break;

	case "Bad_Choice":
		pchar.questTemp.Mtraxx.Retribution.Choice = "bad";
		Achievment_Set("ach_CL_97");
		bNoEatNoRats = false;
		LAi_SetPlayerType(pchar);
		AddQuestRecord("Roger_10", "18");
		bQuestDisableMapEnter = false; // открыть карту
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		DeleteAttribute(pchar, "GenQuest.CannotWait");
		pchar.quest.mtraxx_line_complete.win_condition.l1 = "MapEnter";
		pchar.quest.mtraxx_line_complete.function = "Mtraxx_RetributionComplete";
		DialogExit_Self();
		break;
	// <-- legendary edition

	// Jason Долго и счастливо
	case "LH_marry":
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		string sTemp = sld.name;
		dialog.text = "Yo y " + sTemp + " hemos estado juntos durante mucho tiempo, y nuestros lazos son más fuertes que cualquier voto de iglesia, pero quiero que ambos recordemos este momento. Por lo tanto, necesito decidir dónde voy a proponerle matrimonio a ella:";
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
		{
			link.l1 = "La Isla Tesoro, esta isla significa mucho en nuestra historia. Supongo que no hay mejor lugar, la bahía de Sabu Matila es encantadora al atardecer!";
			link.l1.go = "LH_marry_1_1";
		}
		link.l2 = "¡Tortuga, un símbolo de la libertad de nuestro tiempo, y la vista desde el faro al estrecho de Tortu merece la brocha de cualquier pintor!";
		link.l2.go = "LH_marry_1_2";
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
		{
			link.l3 = "Jamaica, ¡hay tanto en ella! Y admirar el amanecer en la Ensenada de Portland es como imagino el Paraíso en la tierra.";
			link.l3.go = "LH_marry_1_3";
		}
		break;

	case "LH_marry_1_1":
		pchar.questTemp.LongHappy.Shore = "Shore_ship1";
		AddQuestRecord("LongHappy", "2_1");
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		sTemp = sld.name;
		AddQuestUserData("LongHappy", "sName", sTemp);
		dialog.text = "Pero no podemos hacer esto sin la solemnidad de la iglesia, todo debería ser según todos los cánones para que mi padre se viera obligado a aceptar mi elección. Entonces, necesitaré un sacerdote, y no veo a nadie digno de esta posición además del Abad Benoit. Es un viejo amigo de mi padre y con él comenzaron mis aventuras en el Nuevo Mundo. Creo que aceptará hacerme el honor.";
		link.l1 = "";
		link.l1.go = "LH_marry_2";
		break;

	case "LH_marry_1_2":
		pchar.questTemp.LongHappy.Shore = "Mayak6";
		AddQuestRecord("LongHappy", "2_2");
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		sTemp = sld.name;
		AddQuestUserData("LongHappy", "sName", sTemp);
		dialog.text = "Pero no podemos hacer esto sin la solemnidad de la iglesia, todo debería ser de acuerdo con todos los cánones para que mi padre se viera obligado a aceptar mi elección. Entonces, necesitaré un sacerdote, y no veo a nadie digno de este puesto además del Abad Benoit. Es un viejo amigo de mi padre y con él comenzaron mis aventuras en el Nuevo Mundo. Creo que accederá a hacerme el honor.";
		link.l1 = "";
		link.l1.go = "LH_marry_2";
		break;

	case "LH_marry_1_3":
		pchar.questTemp.LongHappy.Shore = "Shore36";
		AddQuestRecord("LongHappy", "2_3");
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		sTemp = sld.name;
		AddQuestUserData("LongHappy", "sName", sTemp);
		dialog.text = "Pero no podemos hacer esto sin la solemnidad de la iglesia, todo debería estar de acuerdo con todos los cánones para que mi padre se vea obligado a aceptar mi elección. Entonces, necesitaré un sacerdote, y no veo a nadie digno de este puesto además del Abad Benoit. Él es un viejo amigo de mi padre y con él comenzaron mis aventuras en el Nuevo Mundo. Creo que él aceptará hacerme el honor.";
		link.l1 = "";
		link.l1.go = "LH_marry_2";
		break;

	case "LH_marry_2":
		AddQuestRecord("LongHappy", "3");
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		sTemp = sld.name;
		AddQuestUserData("LongHappy", "sName", sTemp);
		dialog.text = "Bueno, esto puede suceder sin la solemnidad de la humanidad. Aunque preferiría discutir esto con " + sTemp + "un poco después.";
		link.l1 = "";
		link.l1.go = "exit";
		pchar.questTemp.LongHappy = "choose";
		break;

	case "LH_marry_3":
		dialog.text = "¡Bueno, estoy listo!";
		link.l1 = "";
		link.l1.go = "exit";
		LongHappy_MarryOffer();
		break;

	case "LH_marry_4":
		if (LongHappy_CheckGoods())
		{
			dialog.text = "¡Todo está preparado!";
			link.l1 = "";
			link.l1.go = "exit";
			LongHappy_OnIslaTesoro();
		}
		else
		{
			dialog.text = "¡Los bienes necesarios y la moneda aún no se han recolectado!";
			link.l1 = "";
			link.l1.go = "exit";
		}
		break;
	}
}

void DialogExit_Self()
{
    SendMessage(PChar, "ls", MSG_CHARACTER_EX_MSG, "forceBlend");
	DialogExit();
	locCameraSleep(false); // boal
}

// Ричард Флитвуд - английский капитан
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
		{
			if (pchar.questTemp.HWIC.Eng == "Start_main")
			{
				dialog.text = "¡Saludos, capitán! No se distraiga con mi apariencia, estoy bien, casi ciego, pero estoy bien. Permítame presentarme, soy Richard Fleetwood.";
				link.l1 = "Buenos días, es un placer conocerte, soy el capitán " + GetFullName(pchar) + ".";
				link.l1.go = "First_Task";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "GotoPortoffice")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
				{
					dialog.text = "Te he pedido que atraques tu barco. ¿Acaso me escuchas?";
					link.l1 = "Claro, lo hago. Me encargo de ello.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Entonces, estás aquí de nuevo. Toma el mando del 'Valkyrie' - mi tripulación está advertida sobre los detalles y navega hacia Bridgetown. Visita a cada persona de interés en la ciudad y difunde los chismes de los que hablamos. Luego prepárate para el ataque del bastardo. No cambies la nave y no formes una escuadra, de lo contrario sospechará una trampa y no se presentará\nDebes abordar su barco y llevarlo a St. John's. Es imperativo que localices el cuaderno de bitácora del pirata, ya que es la única evidencia que tendremos jamás de la implicación de Lucas Rodenburg. Estoy seguro de que te encargarás de esto. Buena suerte, capitán.";
					link.l1 = "¡Gratitud! Haré el trabajo según nuestro plan.";
					link.l1.go = "First_Task_3";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
				}
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "MirageTake") // а вот теперь начинается перебор кораблей
			{
				pchar.quest.ToAntiguaMirageOver.over = "yes"; // снять таймер
				int iMir = 0;
				int iVal = 0;
				for (i = 0; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE)
						{
							iMir = 1;
							RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1; // чистый корпус
							SetShipSailsFromFile(sld, "ships/parus_silk.tga");
							SetSailsColor(sld, 0);				// белый хлопковый парус
							DeleteAttribute(sld, "ship.sails"); // починить паруса
							DeleteAttribute(sld, "ship.masts"); // вернуть мачты
						}
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA)
							iVal = 1;
					}
				} // установили признак наличия кораблей в эскадре.
				if (iMir == 1 && iVal == 0) // потеряли Валькирию
				{
					dialog.text = "Eres tú de vuelta, capitán... Ya sé todo sobre tu viaje.";
					link.l1 = "¿Lo sabes? Entonces debes saber que...";
					link.l1.go = "Fleetwood_lostVal";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				if (iMir == 0 && iVal == 1) // потеряли Мираж
				{
					dialog.text = "Eres tú de vuelta, capitán... Ya sé todo sobre tu viaje.";
					link.l1 = "¿Lo sabes? Entonces debes saber que...";
					link.l1.go = "Fleetwood_lostMir";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				if (iMir == 0 && iVal == 0) // а это вообще плохо
				{
					dialog.text = "Has vuelto, capitán... Ya sé todo sobre tu viaje.";
					link.l1 = "¿Ah, sí? Entonces debes saber que...";
					link.l1.go = "Fleetwood_lostFull";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				dialog.text = "Has vuelto, capitán... Ya sé todo sobre tu viaje.";
				link.l1 = "¿De veras? Entonces debes saber que...";
				link.l1.go = "Fleetwood_complete";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SentJons");
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "toAntigua")
			{
				dialog.text = "¡Saludos, mi amigo! ¡Me alegra verte! ¿Tienes a Abigail en tu barco?";
				link.l1 = "Lamentablemente, no, Richard. Ella se negó a venir conmigo, porque su partida sería un duro golpe para su padre, quien ya ha perdido hasta la última moneda. He decidido ocuparme del problema y encontrar el dinero de Solomon y esa isla...";
				link.l1.go = "Fleetwood_LastTask";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SentJons");
				break;
			}
			dialog.text = "¿Algo más, capitán?";
			link.l1 = "No, ya me voy.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		}
		dialog.text = "¿Algo más, capitán?";
		link.l1 = "No, ya me voy.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "Fleetwood_abordage":
		PlaySound("Voice\Spanish\hambit\Richard Flitwood-04.wav");
		dialog.text = "¡Maldito pirata! Has ganado la pelea de abordaje, pero de todos modos cumpliré con mi deber. He preparado todo para encender la bodega de pólvora, y mi navío pronto explotará junto con tu 'Barco Fantasma'. No hundirás ni un solo barco inglés más. ¡Moriré con honor!";
		link.l1 = "Lamento decepcionarte, pero estás equivocado, Fleetwood. No hay piratas en mi barco, ya me he encargado de ellos antes. Te necesitaba y este barco sirvió como una buena trampa. \n¡Basta de palabras amables, todavía tengo que matarte y escapar de tu bañera en llamas!";
		link.l1.go = "Fleetwood_abordage_1";
		break;

	case "Fleetwood_abordage_1":
		LAi_SetCurHPMax(NPChar);
		LAi_GetCharacterMaxEnergy(NPChar);
		QuestAboardCabinDialogExitWithBattle("PrepareToBoom");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		pchar.questTemp.HWIC.Holl = "FleetwoodCapture";
		pchar.GenQuest.Detonation = true; // patch-4
		break;

	case "First_Task":
		dialog.text = "Charlie ya me informó sobre tu exitosa interceptación de la caravana comercial enemiga. Me alegra conocerte, Inglaterra necesita capitanes tan valientes. Ahora, déjame contarte algo de gran importancia.";
		link.l1 = "Estoy escuchando, Sr. Fleetwood.";
		link.l1.go = "First_Task_1";
		break;

	case "First_Task_1":
		dialog.text = "Un pirata ha estado cometiendo actos de violencia en todo el archipiélago, haciéndose pasar por el 'Holandés Errante', un barco fantasma legendario. Pretende ser el 'Holandés Errante', un barco fantasma legendario. Estoy seguro de que es un holandés, pero no puede volar. Tiendo a creer que es un mercenario de Lucas Rodenburg, vicedirector de la Compañía Holandesa de las Indias Occidentales.\nRodenburg ha declarado una guerra comercial en las sombras contra Inglaterra - este 'barco fantasma' solo ataca embarcaciones comerciales bajo la bandera inglesa. Es vital para la compañía debilitar nuestra influencia en esta área sin librar una guerra real.\nHe estado cazando este barco fantasma por un tiempo, pero su capitán es un marinero muy experimentado y su barco es rápido y escurridizo.\nDado que es imposible atrapar al chacal en una pelea abierta, debemos actuar con astucia y el reciente intento de asesinato contra mí nos hará un gran favor. ¿Qué piensas al respecto, capitán? ¿Estás asustado?";
		link.l1 = "Ni lo sueñes. Me complacería ayudarte a rastrear y hundir a ese bastardo. Ibas a pedírmelo, ¿verdad?";
		link.l1.go = "First_Task_2";
		break;

	case "First_Task_2":
		dialog.text = "Tienes razón. Ahora, discutamos los detalles. Mis hombres esparcirán el rumor de que estoy casi muerto y que vendí mi barco, el 'Valkyrie', a ti. Luego, continuaremos con nuestro pequeño engaño. Fingirás ser un comerciante que compró el bergantín de mí y se deshizo de la mayoría de los cañones. \nPor lo tanto, tu tarea es navegar hacia Barbados y decirle a todos allí que tus bodegas están llenas de carga valiosa y tus bolsillos llenos de monedas. Déjales saber que pronto zarparás. Interpreta el papel de un comerciante avaricioso, simple pero rico. \nNuestro maldito holandés obtiene su información sobre el barco mercante por Bridgetown. No se sabe exactamente quién le suministra la información. Todos están bajo sospecha, desde el comerciante hasta elun gobernador, aunque esta última posibilidad es bastante aterradora. \nToma el mando de mi 'Valkyrie' y su tripulación. Pero primero, debes dejar todos tus barcos aquí, ya he hablado con el maestro del puerto, costará 10 000 pesos al mes por tu buque insignia. \nUna vez hecho esto, regresa a mí y haré los arreglos. Ah, capitán, no olvides tomar tu parte por capturar la caravana de plata y diez mil para el maestro del puerto, el dinero está en la cómoda.";
		link.l1 = "Lo entiendo, señor Fleetwood. Voy a ver al maestro del puerto.";
		link.l1.go = "exit";
		pchar.questTemp.HWIC.Eng = "GotoPortoffice";
		bDisableFastReload = false;						  // откроем быстрый переход
		DeleteAttribute(pchar, "questTemp.HWIC.CanTake"); // иные варианты более невозможны
		AddLandQuestMark(characterFromId("SentJons_PortMan"), "questmarkmain");
		break;

	case "First_Task_3":
		DialogExit();
		pchar.questTemp.HWIC.TakeQuestShip = "true"; // все ПУ недоступны для стоянки до поры, также корабль нельзя продать
		pchar.questTemp.HWIC.EngEquip = "true";		 // форма солдат
		pchar.questTemp.HWIC.Eng = "GotoBridgetown";
		GetValckiriaToCharacter(pchar);
		pchar.quest.Knippel_Officer.win_condition.l1 = "location";
		pchar.quest.Knippel_Officer.win_condition.l1.location = "SentJons_houseSP3";
		pchar.quest.Knippel_Officer.function = "KnippelToOfficer";
		pchar.questTemp.HWIC.Eng.BridgeCounter = 0; // счетчик посещений неписей Бриджтауна по квесту
		AddQuestRecord("Holl_Gambit", "2-5");
		AddMapQuestMarkCity("Bridgetown", false);
		AddLandQuestMark(characterFromId("Bridgetown_trader"), "questmarkmain");
		AddLandQuestMark(characterFromId("Bridgetown_shipyarder"), "questmarkmain");
		AddLandQuestMark(characterFromId("Bridgetown_Mayor"), "questmarkmain");
		AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
		AddLandQuestMark(characterFromId("Bridgetown_usurer"), "questmarkmain");
		AddLandQuestMark(characterFromId("Bridgetown_PortMan"), "questmarkmain");
		AddLandQuestMark(characterFromId("Bridgetown_Hostess"), "questmarkmain");
		break;

	// изымаем корабль
	case "Fleetwood_lostMir":
		dialog.text = "Sí, estoy al tanto de que has fallado en tu misión de capturar el barco pirata. Todos mis planes están arruinados. Te quito el 'Valkyrie'. Puedes irte ahora, no necesito tus servicios.";
		link.l1 = "Lo siento mucho por eso. Adiós, Sr. Fleetwood.";
		link.l1.go = "Fleetwood_RemoveShip";
		pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
		break;

	case "Fleetwood_lostVal":
		dialog.text = "Sí, estoy al tanto de que has perdido 'Valkyrie'. Fue lo más inaceptable... Voy a confiscar el navío pirata capturado. Puedes irte ahora, no necesito tus servicios.";
		link.l1 = "Lamento mucho eso. Adiós, Sr. Fleetwood.";
		link.l1.go = "Fleetwood_RemoveShip";
		pchar.questTemp.HWIC.Eng.ShipType = SHIP_MIRAGE;
		break;

	case "Fleetwood_lostFull":
		dialog.text = "Sí, estoy al tanto de que eres un raro inepto y torpe. No capturaste el navío pirata y perdiste mi 'Valquiria'. Estoy realmente decepcionado de ti. ¡Fuera!";
		link.l1 = "Lo siento mucho por eso. Adiós, Sr. Fleetwood.";
		link.l1.go = "exit";
		Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Knippel");
		AddDialogExitQuestFunction("LandEnc_OfficerFired"); // Книппеля из офицеров
		sld = characterFromId("Knippel");
		ChangeCharacterAddressGroup(sld, "SentJons_houseH1", "goto", "goto1"); // Книппеля домой
		pchar.questTemp.HWIC.Eng = "end";
		CloseQuestHeader("Holl_Gambit");
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip"); // ПУ откроем
		DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
		pchar.questTemp.HWIC.Detector = "eng_fail";
		AddSimpleRumourCity("Dicen que has fallado en algún encargo secreto de Richard Fleetwood. Bueno, ahora no tienes nada que hacer en Antigua...", "SentJons", 20, 3, "");
		break;

	case "Fleetwood_RemoveShip":
		DialogExit();
		AddDialogExitQuestFunction("Fleetwood_RemoveShip");
		pchar.questTemp.HWIC.Eng = "end";
		CloseQuestHeader("Holl_Gambit");
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip"); // ПУ откроем
		DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
		pchar.questTemp.HWIC.Detector = "eng_fail";
		AddSimpleRumourCity("Dicen que has fallado en algún encargo secreto de Richard Fleetwood. Bueno, ahora no tienes nada que hacer en Antigua...", "SentJons", 20, 3, "");
		break;

	case "Fleetwood_complete":
		pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
		AddDialogExitQuestFunction("Fleetwood_RemoveShip");
		if (CheckCharacterItem(pchar, "JacobJournal")) // проверяем журнал
		{
			dialog.text = "Sí, soy consciente de que has tenido éxito en nuestro plan. Has eliminado al malvado pirata y capturado su barco. ¿Cuál es el verdadero nombre de ella?";
			link.l1 = "Espejismo";
			link.l1.go = "Abigile";
		}
		else // нет журнала - нет продолжения квеста
		{
			dialog.text = "Sí, soy consciente de que has tenido éxito en nuestro plan. Has eliminado al malvado pirata y capturado su barco. Recuperaré mi 'Valkyrie'. Puedes quedarte con el navío pirata como un premio. También servirá como una especie de... compensación. Tu barco anclado en el puerto se quemó cuando el fuego en los muelles comenzó a extenderse. Me disculpo por las molestias, " + pchar.name + "... Espero que el barco fantasma te sirva mejor.\nHe ordenado que limpien tu nueva embarcación de la suciedad y las algas persistentes. También vestirán a tu belleza con nuevas velas del mejor algodón.\nFinalmente, por favor acepta tu recompensa de 100 000 pesos y esta herramienta de navegación. Siempre quise entregársela a un marinero digno y ¡hiciste un trabajo admirable allá afuera! Bueno, ha llegado el momento de despedirse, he terminado mis asuntos aquí y debo regresar a Europa. ¡Buena fortuna para ti, capitán!";
			link.l1 = "¡Igualmente, Richard!";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true); // закроем Флитвуда в комнате и пусть там сидит
			pchar.questTemp.HWIC.Eng = "end";
			pchar.questTemp.HWIC.Detector = "eng_win_half";
			CloseQuestHeader("Holl_Gambit");
		}
		AddMoneyToCharacter(pchar, 100000);
		GiveItem2Character(pchar, "bussol");
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip"); // ПУ откроем
		DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
		AddSimpleRumourCity("Dicen que usted y Richard Fleetwood han planeado alguna operación militar y que usted ha destruido personalmente a ese escurridizo pirata que ha estado robando nuestros barcos comerciales. ¡Es usted un verdadero héroe, capitán!", "SentJons", 20, 3, "");
		break;

	case "Abigile":
		dialog.text = "¿Espejismo? Un nombre muy adecuado, diría yo... Voy a recuperar mi 'Valkyrie' de ti y, por lo tanto, puedes quedarte con el barco pirata como premio. También servirá como una especie de compensación. Tu barco anclado en el puerto se quemó cuando el fuego en los muelles comenzó a extenderse. Lo siento, " + pchar.name + "... Espero que el barco fantasma te sirva mejor.\nHe ordenado que limpien tu nueva embarcación de esa obstinada suciedad y algas marinas. También vestirán a tu belleza con nuevas velas del mejor algodón.\nFinalmente, acepta tu recompensa de 100 000 pesos y esta herramienta de navegación, siempre quise entregársela a un marinero digno... ¡Hiciste un buen trabajo allá afuera y estoy orgulloso de ti! ¿Tienes el cuaderno de bitácora del bastardo?";
		link.l1 = "Sí, claro. Aquí lo tienes, tómalo. Quiero preguntarte algo, ¿hay algún... asiático entre los secuaces de Lucas Rodenburg?";
		link.l1.go = "Abigile_1";
		break;

	case "Abigile_1":
		RemoveItems(PChar, "JacobJournal", 1);
		dialog.text = "Sí, lo hay. El chino Longway, capitán de su barco privado 'Meifeng'. ¿Leíste eso del diario del pirata? Vamos a echar un vistazo...(leyendo) Bueno, bueno. ¡Como esperaba, Lucas Rodenburg estaba detrás de todo eso! Bueno, lo que sea, no es nuestro problema ahora... Nuestro gobernador general se encargará de este bastardo. ¡Lucas Rodenburg tendrá que asumir la responsabilidad de todo lo que ha hecho!";
		link.l1 = "Mm, interesante, ¿y cómo podrá el gobernador general inglés 'arreglarse' con un súbdito de Holanda?";
		link.l1.go = "Abigile_2";
		break;

	case "Abigile_2":
		dialog.text = "Siempre hay hilos políticos que tirar, mi querido amigo... Holanda tendrá que admitir que empezaron la guerra comercial contra Inglaterra, pero es poco probable que lo hagan. En su lugar, culparán a Rodenburg de todo. Lucas podría perder su puesto, o tal vez no. De cualquier forma, su carrera sufrirá un duro golpe.\nSin embargo, esto no es asunto nuestro ahora, capitán. Has hecho bien tu parte del trabajo. Es por eso que tengo otro asunto muy delicado para ti.";
		link.l1 = "Estoy escuchando, Richard. ¿Quién será el próximo enemigo de la corona inglesa que será destruido esta vez?";
		link.l1.go = "Abigile_3";
		break;

	case "Abigile_3":
		dialog.text = "No, quiero pedirte que te ocupes de un asunto más personal y pacífico esta vez. Déjame contarte una breve historia que, por cierto, concierne a tu 'Espejismo'.";
		link.l1 = "Continúa.";
		link.l1.go = "Abigile_4";
		break;

	case "Abigile_4":
		dialog.text = "Estaba en una incursión, cazando el barco fantasma un mes antes de que tú y yo nos conociéramos. Fue al sur de Martinica, no lejos de la longitud 64 dg. 41'. Oímos una pelea a lo lejos, pero el viento era demasiado débil, así que no llegamos a tiempo. Un flautista inglés fue hundido por un barco fantasma cerca de una pequeña isla que ni siquiera está en el mapa\nNo logré atrapar al pirata y decidí visitar esa isla, con la esperanza de encontrar sobrevivientes. Y los encontré. Un par de refugiados judíos, padre e hija. La chica se llamaba Abigail y ¡era hermosa! Un milagro viviente... Los llevé a bordo y los llevé a Curazao, aunque su padre, Salomón, no me mostró mucha simpatía\nPor lo que entendí, pensaba que yo era el pirata que hundió su barco, el viejo no sabe mucho sobre barcos y las diferencias entre ellos. Durante ese pequeño viaje, Abigail y yo nos hicimos amigos, o, para ser completamente honesto, nos enamoramos el uno del otro. ¿No es una historia?\nY recientemente descubrí que el bastardo de Rodenburg ha estado cortejando a mi Abigail por un tiempo, ¡solo piénsalo! Iba a traerla aquí, una vez que resolviera el asunto del dinero perdido de su padre, guardó cada moneda que tenía en esa isla que mencioné. No logré encontrar su ubicación. No podemos esperar más\nDado que mi salud todavía no me permite zarpar yo mismo, te pido que vayas a Willemstad, encuentres a Abigail y la traigas aquí. Menciona mi nombre y ella confiará en ti.";
		link.l1 = "No veo ningún problema en este asunto. Estoy listo para zarpar ahora.";
		link.l1.go = "Abigile_5";
		break;

	case "Abigile_5":
		PlaySound("Voice\Spanish\hambit\Richard Flitwood-05.wav");
		dialog.text = "¡Excelente! Me alegra que pueda contar contigo, " + pchar.name + "  Tu trabajo será bien remunerado, no te preocupes por eso.";
		link.l1 = "No te haré esperar demasiado. ¡Nos vemos pronto, Richard!";
		link.l1.go = "Abigile_6";
		break;

	case "Abigile_6":
		DialogExit();
		npchar.greeting = "fleetwood_2";
		LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);   // откроем дом Аби
		LocatorReloadEnterDisable("Villemstad_houseSp2", "reload2", true); // закроем спальню Аби
		AddQuestRecord("Holl_Gambit", "2-16");
		pchar.questTemp.HWIC.Eng = "toAbigile";
		sld = characterFromId("Bridgetown_tavernkeeper");
		sld.model = "barmen_3";
		sld.name = "Harry";
		sld.lastname = "Fletcher"; // перерисуем бармена Бриджтауна
		sld.greeting = "barmen_1";
		sld = characterFromId("Solomon");
		sld.greeting = "solomon_2";
		AddLandQuestMark(sld, "questmarkmain");
		AddMapQuestMarkCity("Villemstad", false);
		break;

	case "Fleetwood_LastTask":
		dialog.text = "" + pchar.name + ", ¿realmente decidiste encontrar la isla? Estoy impresionado con tu generosidad. ¿La encontraste?";
		link.l1 = "Sí, lo hice. Desafortunadamente, aquí es donde comienzan las malas noticias. Apenas escapé de ese maldito lugar con vida... Todavía tiemblo cuando lo pienso...";
		link.l1.go = "Fleetwood_LastTask_1";
		break;

	case "Fleetwood_LastTask_1":
		dialog.text = "¿Qué ha sucedido allí? ¡Dime, amigo mío, no me tengas en suspense!";
		link.l1 = "Vine a la isla y me dirigí a la gruta donde Salomón probablemente había escondido su cofre. Realmente estaba allí. Pero cuando lo toqué, algún poder desconocido me lanzó hacia arriba. Escuché una explosión y fui arrojado al suelo a tres metros del cofre...";
		link.l1.go = "Fleetwood_LastTask_2";
		break;

	case "Fleetwood_LastTask_2":
		dialog.text = "¡Increíble!";
		link.l1 = "Apenas sobreviví - tengo algunos rasguños dolorosos. Cuando volvía a la conciencia, unos ruidos aterradores zumbaban en mi cabeza y la espantosa criatura apareció directamente del suelo... ¡oh, Dios, ese monstruo!";
		link.l1.go = "Fleetwood_LastTask_3";
		break;

	case "Fleetwood_LastTask_3":
		dialog.text = "" + pchar.name + "...";
		link.l1 = "Richard, no estoy loco. Realmente ocurrió aunque yo mismo apenas lo creo. Era un cadáver completamente seco y pintado de un indio con un montón de plumas en la cabeza. ¡Este monstruo murmuró algo, luego sacó un enorme garrote indio y me atacó!";
		link.l1.go = "Fleetwood_LastTask_4";
		break;

	case "Fleetwood_LastTask_4":
		dialog.text = "";
		link.l1 = "¡Por el amor de Dios... Aún no entiendo cómo pude lidiar con esa cosa... La golpeé tantas veces que sería suficiente para matar a una docena de hombres y aún seguía de pie... Después de recuperar el aliento, abrí ese desgraciado cofre... No había dinero dentro, pero había algo en su lugar. ¡Mira, un objeto muy intrigante!";
		link.l1.go = "Fleetwood_LastTask_5";
		break;

	case "Fleetwood_LastTask_5":
		RemoveItems(PChar, "GastonHead", 1);
		dialog.text = "B-r-r... terrible..." + pchar.name + ", espera... ¡seguro que es él! ¡Es la cabeza del bastardo que intentó matarme cegándome con pimienta!";
		link.l1 = "¿Lo conoces? Se llama Gaston, el tabernero de Bridgetown y partidario de van Berg, el capitán del barco fantasma. ¡Lo he reconocido de inmediato, pero no sé quién lo ha matado ni cómo su cabeza cortada terminó en el cofre de Solomon en la isla desconocida!";
		link.l1.go = "Fleetwood_LastTask_6";
		break;

	case "Fleetwood_LastTask_6":
		dialog.text = "Tienes razón, es una historia realmente escalofriante y oscura. Mística...";
		link.l1 = "Exactamente. No tenía sentido regresar con Abigail debido a la ausencia del dinero. Así que estoy aquí para contártelo. Quizás tú, Richard, entiendas algo en este lío...";
		link.l1.go = "Fleetwood_LastTask_7";
		break;

	case "Fleetwood_LastTask_7":
		dialog.text = "¿Yo? No entiendo nada aquí, igual que tú... Pero te puedo decir algo con seguridad - tengo un mal presentimiento sobre esto..." + pchar.name + ", escúchame ahora. Ve y revisa Bridgetown para asegurarte de que... Gaston se haya ido para siempre. Luego, te pido que vengas a la Laguna Blanca de Curazao en 20 días. Charlie Knippel te estará esperando allí. Reuniré dinero para el padre de Abigail. Se lo daré a Charlie, y tú lo llevarás a Solomon y entregarás a Abigail en Antigua. Esta vez no habrá obstáculos, debes entender eso. ¡Ve, mi amigo!";
		link.l1 = "Está bien, Richard. Zarparé de inmediato.";
		link.l1.go = "Fleetwood_LastTask_8";
		break;

	case "Fleetwood_LastTask_8":
		DialogExit();
		pchar.questTemp.HWIC.Eng = "toBarbados";
		AddQuestRecord("Holl_Gambit", "2-21");
		SetFunctionTimerCondition("HWICEng_toBarbadosOver", 0, 0, 20, false); // чтобы не тянули
		AddSimpleRumourCity("Oh, capitán, he oído que Richard Fleetwood realmente te admira. Créeme, sus elogios cuestan mucho. Usted debe ser una persona muy importante...", "SentJons", 20, 3, "");
		AddMapQuestMarkCity("Bridgetown", false);
		AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
		break;

		//---------------------------------------------против всех-----------------------------------------------

	case "InTerksShore":
		DelLandQuestMark(npchar);
		pchar.quest.Fleetwood_ShoreOver.over = "yes"; // снять таймер
		dialog.text = "Supongo que eres el bastardo que ha secuestrado a mi Abigail. Charlie no regresó a mí, así que también debes ser tú quien tiene la culpa.";
		link.l1 = "Tiene razón, señor Fleetwood. Soy yo. Charlie me ha ayudado a ganarme la confianza de Abigail gracias a la carta que usted le escribió. Pero vayamos directo al grano... ¿Ha traído el dinero?";
		link.l1.go = "InTerksShore_1";
		break;

	case "InTerksShore_1":
		dialog.text = "He tenido. Pero quiero ver a Abigail primero. Debo estar seguro de que está viva e intacta, ya que no voy a confiar en la palabra de un bastardo.";
		link.l1 = "¿No crees, señor, que no estás en posición de dictar tus términos?";
		link.l1.go = "InTerksShore_2";
		// belamour legendary edition -->
		link.l2 = "Ya no quiero jugar este juego. ¡Abi se quedará conmigo, y tú estás en esta playa! ¡Fuego!";
		link.l2.go = "InTerksShore_2a";
		break;

	case "InTerksShore_2a": // массовая драка на необитаемом острове
		AddCharacterExpToSkill(pchar, "FencingL", 60);
		AddCharacterExpToSkill(pchar, "FencingS", 60);
		AddCharacterExpToSkill(pchar, "FencingH", 60);
		AddCharacterExpToSkill(pchar, "Pistol", 60);
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешим драться
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		for (i = 1; i <= 3; i++) // офицеры Флитвуда
		{
			sld = characterFromId("FlOfficer_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		for (i = 1; i <= 7; i++) // засада Флитвуда
		{
			sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_" + i, "sold_eng_" + i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			if (i >= 1 && i < 3)
				ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
			else
				ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
		}
		for (i = 1; i <= 7; i++) // наши - к бою!
		{
			sld = characterFromId("OwrSailor_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "InTerksShore_2":
		ChangeCharacterComplexReputation(pchar, "nobility", 1);
		AddCharacterExpToSkill(pchar, "Leadership", 120);
		// <-- legendary edition
		dialog.text = "Lo entiendo, pero tampoco soy un tonto. No hablaremos de dinero hasta que vea a Abigail. ¿Y bien? Estoy esperando.";
		link.l1 = "Bien. Ahora es el momento de poner mis cartas sobre la mesa, Capitán Fleetwood. He organizado nuestra reunión aquí no por dinero. Bueno, claro, me gustaría tomarlo, pero te necesito primero.";
		link.l1.go = "InTerksShore_3";
		break;

	case "InTerksShore_3":
		dialog.text = "¿Yo? Esto se está poniendo de lo más interesante... Creo que estoy empezando a entender lo que realmente está sucediendo aquí. Dime, ¿Abigail está viva? ¿Vive ella o la has asesinado, bastardo?";
		link.l1 = "Supongo que te dejaré en la ignorancia sobre su destino. Solo hay una cosa que debes saber: ella no está aquí. Ha jugado su papel muy bien, tú estás aquí en mis manos. El amor es una cosa tan maravillosa... ¿Cómo más podría atraer a un zorro fuera de su guarida hacia campo abierto? ¡Ja-ja-ja!";
		link.l1.go = "InTerksShore_4";
		break;

	case "InTerksShore_4":
		dialog.text = "No te alegres tan pronto, bribón. He organizado una buena bienvenida para ti en esta isla y se desconoce quién está en manos de quién. Así que prepárate, tienes muchas cosas que contarme: sobre Abigail, sobre Charlie, ¡pagarás por haberles hecho daño!";
		link.l1 = "¡Ya estoy temblando de miedo! Es hora de terminar nuestra conversación, señor. Prepárate para ir al infierno, porque no hay lugar para ti en el cielo.";
		link.l1.go = "InTerksShore_5";
		break;

	case "InTerksShore_5":														   // массовая драка на необитаемом острове
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешим драться
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		for (i = 1; i <= 3; i++) // офицеры Флитвуда
		{
			sld = characterFromId("FlOfficer_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		for (i = 1; i <= 7; i++) // засада Флитвуда
		{
			sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_" + i, "sold_eng_" + i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			if (i >= 1 && i < 3)
				ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
			else
				ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
		}
		for (i = 1; i <= 7; i++) // наши - к бою!
		{
			sld = characterFromId("OwrSailor_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
	}
}

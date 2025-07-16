// Чарли Книппель - старый артиллерист
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, iTemp, amount;
	string sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_", 0) != -1)
	{
		i = findsubstr(sAttr, "_", 0);
		NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
		Dialog.CurrentNode = "SetGunBullets2";
	}

	switch (Dialog.CurrentNode)
	{
	case "First time":
		// ветка на взятие 2 варианта прохождения - за Англию
		if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Eng") && !CheckAttribute(npchar, "quest.HWICTake") && !CheckAttribute(pchar, "questTemp.HWIC.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
		{
			dialog.text = "¡Ahoy, camarada, cadena de disparo en mi trasero! ¿Qué te trae por aquí?";
			link.l1 = "¡Disparo de cadena tu...! ¿qué? Oh no importa, solo quería decir hola.";
			link.l1.go = "exit";
			link.l2 = "Saludos, Sr. Knippel. Ja, veo por qué te llaman Knippel. De todos modos, hay rumores de que solías servir en la Armada Inglesa. Tengo un buen barco y una tripulación hábil. Me gustaría ofrecerme a mí y a mi barco al servicio de la Corona Inglesa...eh...del Commonwealth. ¿Podrías darme algún consejo o recomendarme a alguien o, tal vez, ayudarme en ese asunto?";
			link.l2.go = "Knippel_check";
			break;
		}
		// за Голландию
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "toKnippel")
			{
				dialog.text = "¡Ahoy, compañero, que me parta un rayo! ¿Qué te trae por aquí?";
				link.l1 = "Saludos, señor Knippel. Ja, veo por qué te llaman Knippel. Hay rumores de que solías servir en la Marina Inglesa, por eso quiero pedirte ayuda...";
				link.l1.go = "Dominica";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "¡Cadena de disparo, mi trasero! ¿Qué quieres, camarada?";
			link.l1 = "No, no es nada. Me voy.";
			link.l1.go = "exit";
			break;
		}
		// за Англию
		if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
		{
			if (pchar.questTemp.HWIC.Eng == "TakeHollConvoy")
			{
				dialog.text = "¡Ahoy, capitán, he oído rumores sobre un convoy de plata siendo interceptado...";
				link.l1 = "Está bien informado, Sr. Knippel.";
				link.l1.go = "HollConvoy_Check";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SentJons");
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Wait")
			{
				dialog.text = "¿Preguntas, capitán?";
				link.l1 = "No, no es nada. Me voy.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Start_main")
			{
				dialog.text = "¡Me alegra verte, capitán! Mi comandante Richard Fleetwood iba a venir aquí para conocerte él mismo, pero ocurrió un accidente anoche... Alguien intentó matarlo en medio de la calle, ¡cadena de disparo en mi trasero!";
				link.l1 = "¡Imposible! ¿Qué estaban haciendo los guardias?";
				link.l1.go = "Fleetwood_house";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "¿Preguntas, capitán?";
			link.l1 = "No, no es nada. Me voy.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "¡Ahoy, compañero, me cago en el tiro de cadena! ¿Qué te trae por aquí?";
		link.l1 = "Hola, solo de paso.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

		//-------------------------------------------за Голландию--------------------------------------------------
	case "Dominica":
		dialog.text = "¡Ahoy, ¿en serio? ¿Y cómo puede un viejo marinero que hace tiempo quedó varado ayudarte, camarada?";
		link.l1 = "Vea... Soy solo un capitán común y hago viajes regulares entre Martinica y Curazao. Así que he sido atacado dos veces por el barco fantasma no muy lejos de Martinica... Aunque, aquí está el asunto, ella no es una Fata Morgana ni un Holandés Errante. ¡Pude desgarrar sus velas con simples balas de cañón!";
		link.l1.go = "Dominica_1";
		break;

	case "Dominica_1":
		dialog.text = "¿Es eso así? Eso ciertamente no es propio de un barco fantasma perder velas por un disparo sólido, ¡que me parta un rayo...";
		link.l1 = "Solo sobrevivimos porque mi barco pudo superarlo navegando ceñido al viento. La última vez tuve que lanzar toda mi carga por la borda para aligerar el casco lo suficiente como para escapar... ¿puedes imaginarte la pérdida? ¡Es desgarrador!";
		link.l1.go = "Dominica_2";
		break;

	case "Dominica_2":
		dialog.text = "¡Que me lleve el diablo, capitán...";
		link.l1 = "Mathias Beck, el gobernador de Curazao, simplemente desestimó mis quejas. Dijo que los cuentos del barco fantasma son tonterías y que mis vigilantes estaban borrachos de grog. El gobernador de Martinica prometió enviar una patrulla allí, pero sus ojos me dijeron que no tiene intención de hacer nada. No puedo regresar a Martinica mientras ese maldito pirata 'fantasma' esté merodeando. Mi barco es pequeño al igual que mi tripulación, es probable que no sobrevivamos al tercer encuentro que tengamos con él...";
		link.l1.go = "Dominica_3";
		break;

	case "Dominica_3":
		dialog.text = "Es una verdadera lástima, compañero. Pero, ¿cómo puedo ayudarte?";
		link.l1 = "Escuché de los marineros por aquí que había un capitán aquí en St. John's llamado Richard Fleetwood que ha cazado este mismo barco fantasma. No lo conozco personalmente, por eso te cuento esta historia a ti, ¿podrías tal vez pasarle la historia de mis desgracias? Estoy seguro de que el sucio pirata se esconde en algún lugar cerca de las salvajes costas de Dominica y está atacando entre Barbados y Martinica.";
		link.l1.go = "Dominica_4";
		break;

	case "Dominica_4":
		dialog.text = "¿Entre Barbados y Martinica? ¡Ja, ja! Un carril comercial gordo y rico. Suena mucho a algo que haría ese rata de sentina.";
		link.l1 = "No soy rico ni gordo, y no tengo dinero para sobornar a un capitán naval por una escolta militar. Pero, si Sir Fleetwood ya está cazando a este rufián, ¿podrías decirle dónde podría encontrar a este 'Holandés Errante'?";
		link.l1.go = "Dominica_5";
		break;

	case "Dominica_5":
		dialog.text = "Has hecho bien en venir aquí, camarada. Contaré tu historia a los hombres adecuados, ¡que me arranquen el hígado con una bala encadenada! Pronto podrás comerciar con Martinica de nuevo.";
		link.l1 = "¡Espero que Dios escuche tus palabras! Gracias por escucharme, Charlie. Espero lo mejor. ¡Adiós y esquiva la bala de cadena!";
		link.l1.go = "Dominica_6";
		break;

	case "Dominica_6":
		DialogExit();
		pchar.questTemp.HWIC.Holl = "toDominica";
		AddQuestRecord("Holl_Gambit", "1-17");
		pchar.quest.toDominica.win_condition.l1 = "location";
		pchar.quest.toDominica.win_condition.l1.location = "Dominica";
		pchar.quest.toDominica.function = "PrepareToFleetwoodAttack";
		DelMapQuestMarkShore("Shore1");
		DelMapQuestMarkShore("Shore2");
		AddMapQuestMarkIsland("Dominica", true);
		break;

		//----------------------------------------------за Англию--------------------------------------------------
	case "Knippel_check":							 // начинаем проверять нашего ГГ по всем статьям
		if (makeint(PChar.reputation.nobility) < 48) // низкая репа
		{
			// belamour legendary edition покажем критерии
			notification("¡Reputación demasiado baja! (Aventurero)", "None");
			PlaySound("Voice\Spanish\hambit\Charlie Knippel-04.wav");
			dialog.text = "¡Me parece, capitán, que en la vida seguiremos rumbos diferentes! Y el tuyo, no me gusta demasiado.";
			link.l1 = "¡Eh, eh, compañero, cuida tu tono o te la coseré!";
			link.l1.go = "exit";
			break;
		}
		else
		{
			notification("Reputation Check Passed", "None");
		}
		if (GetSummonSkillFromName(pchar, SKILL_SAILING) < 30) // низкая навигация
		{
			dialog.text = "Capitán, seré franco. No podrías navegar ni para salir de un saco mojado. Vuelve cuando tengas más habilidades en navegación, ¿entendido?";
			// belamour legendary edition покажем критерии  -->
			notification("Skill Check Failed (30)", SKILL_SAILING);
			//<--
			dialog.text = "Capitán, nuestra flota necesita capitanes experimentados, no novatos. Vuelve cuando hayas dominado el arte de la navegación.";
			link.l1 = "Ya veo... Entonces te veré más tarde.";
			link.l1.go = "exit";
			break;
		}
		else
		{
			notification("Skill Check Passed", SKILL_SAILING);
		}
		dialog.text = "¡Ahoy, llegas justo a tiempo, capitán, que me disparen bolas encadenadas! Richard no sabía en quién podía confiar para este negocio arriesgado, incluso estaba considerando rechazarlo... Así que hoy los pajarillos de la oportunidad cantan dulcemente en tus oídos. Si cumples con nuestros estándares, te recomendaré a un hombre muy importante. ¿Tienes suficiente plomo en tus calzones para manejarlo?";
		link.l1 = "Estoy cargado con metralla, Sr. Knippel.";
		link.l1.go = "Knippel_task";
		break;

	case "Knippel_task": // первое задание
		DelLandQuestMark(npchar);
		DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
		DelLandQuestMark(characterFromId("Lucas"));
		DelMapQuestMarkCity("Bridgetown");
		DelMapQuestMarkCity("Villemstad");
		DelMapQuestMarkCity("SentJons");
		dialog.text = "¡Ar har! ¡Veo que tu gallardete está izado, capitán! ¡Pronto seguirá el fuego centelleante! Ahora escucha con atención. La flota de plata de la Compañía Holandesa de las Indias Occidentales partió de Willemstad en Curazao hace uno o dos días. Está navegando hacia Philipsburg. Esta vez solo hay unos pocos barcos en la flota. Un único barco de la Compañía de las Indias Orientales con la plata en su bodega junto con dos escoltas. Intercepta la flota de plata, captura el barco de las Indias Orientales con la carga de plata y llévala a Antigua. Puedes hundir las escoltas, son prescindibles. ¡Despedaza sus hígados con disparos de cadena, yar!";
		link.l1 = "Sus días están contados.";
		link.l1.go = "Knippel_task_1";
		DelLandQuestMark(npchar);
		break;

	case "Knippel_task_1":
		dialog.text = "Un consejo, capitán. La ruta comercial de Curazao a Sint Maarten no está lejos de las costas de San Cristóbal. Te aconsejaría preparar una emboscada allí. Prepárate bien tú y tu nave para este enfrentamiento. Enredarse con la Compañía de las Indias Occidentales no es un paseo en el parque con una chica bonita.";
		link.l1 = "Sé en lo que me estoy metiendo, pero agradezco tu franqueza, señor Knippel. Volveré con la plata holandesa.";
		link.l1.go = "Knippel_task_2";
		break;

	case "Knippel_task_2":
		DialogExit();
		npchar.quest.HWICTake = "true";
		pchar.questTemp.HWIC.CanTake.Eng = "true"; // признак, что английка уже бралась
		HWICSilverConvoyInWorld();
		AddQuestRecord("Holl_Gambit", "2-1");
		ReOpenQuestHeader("Holl_Gambit"); // данила ,чтобы вышел из архива.
		pchar.questTemp.HWIC.Eng = "begin";
		SetFunctionTimerCondition("HollConvoy_Over", 0, 0, 15, false);
		break;

	case "HollConvoy_Check": // начинаем проверять
		int iHal = 0;
		for (i = 0; i < COMPANION_MAX; i++)
		{
			iTemp = GetCompanionIndex(PChar, i);
			if (iTemp > 0)
			{
				sld = GetCharacter(iTemp);
				pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
				if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_GALEON_L)
					iHal++;
			}
		} // признак наличия ТГ в компаньонах
		if (iHal > 0)
		{
			amount = sti(pchar.questTemp.HWIC.Eng.SlvQty) - GetSquadronGoods(pchar, GOOD_SILVER);
			if (amount <= 0)
			{
				dialog.text = "No hace falta que me cuente lo que pasó, capitán. Me informaron de todo mientras el agente de aduanas inspeccionaba su barco... Lo ha hecho bastante bien, capitán. ¡Excelente! No sonaba fácil, ¡cadena de tiro mi trasero!";
				link.l1 = "Es agradable ser apreciado.";
				link.l1.go = "HollConvoy_complete";
			}
			else
			{
				dialog.text = "No necesitas contarme lo que pasó, camarada. Me informaron de todo mientras el agente de aduanas inspeccionaba tu barco... ¡No trajiste toda la plata, que me cuelguen de un mástil! Sé exactamente cuánto plata había en ese Indiaman del Este hasta el último peso. El propósito de esta misión no era solo probar tus habilidades de combate sino también tu honestidad. Has fallado en lo último. ¡Fuera de mi casa, grumete!";
				link.l1 = "¡Al diablo contigo entonces, simplón!";
				link.l1.go = "HollConvoy_fail";
			}
		}
		else
		{
			dialog.text = "¡Alto, camarada! No veo al Indiaman holandés en tu escuadrón. Te dije que la trajeras aquí como un premio. La vendiste y trataste de quedarte con el dinero, ¿eh?";
			link.l1 = "Espera, ¿se suponía que debía traer el barco? Pensé que solo querías la plata.";
			link.l1.go = "HollConvoy_noShip";
		}
		break;

	case "HollConvoy_noShip":
		dialog.text = "¡Nadie toma por tonto a Charlie Knippel, camarada! Recuerdo claramente lo que te dije y lo que no. Has roto los términos de nuestro trato y ningún inglés honesto trabajará contigo, aquí no hay lugar para sinvergüenzas. ¡Fuera de mi casa, grumete!";
		link.l1 = "¡Al diablo contigo entonces, simplón!";
		link.l1.go = "HollConvoy_fail";
		break;

	case "HollConvoy_fail":
		DialogExit();
		AddQuestRecord("Holl_Gambit", "2-3");
		CloseQuestHeader("Holl_Gambit");
		DeleteAttribute(pchar, "questTemp.HWIC.Eng"); // зачищаем для возможности отката к голландскому варианту
		pchar.questTemp.HWIC.Fail2 = "true";
		break;

	case "HollConvoy_complete":
		dialog.text = "Visítame mañana y te presentaré a mi patrón. Te ofrecerá más trabajo digno de tus habilidades. Además, se encargará de tu...incentivo financiero. ¡Levamos anclas!";
		link.l1 = "Muy bien, Sr. Knippel. Estaré aquí mañana.";
		link.l1.go = "exit";
		npchar.greeting = "knippel_2";
		AddDialogExitQuestFunction("HollConvoy_Remove");
		AddQuestRecord("Holl_Gambit", "2-4");
		SetTimerFunction("EnglandGambit_2_ZadanieStart", 0, 0, 1);
		pchar.questTemp.HWIC.Eng = "Wait";
		AddSimpleRumourCity("Dicen que capturó un barco holandés lleno de plata. ¡Bien hecho! ¡Eres un marinero valiente, capitán! ¡Que Dios te acompañe!", "SentJons", 10, 3, "");
		break;

	case "Fleetwood_house":
		dialog.text = "He estado preguntándome lo mismo... Algún bastardo arrojó pimienta molida en los ojos del capitán Fleetwood y lo apuñaló en el pecho antes de que Richard siquiera lograra tomar su espada. El asesino esperaba acabar con el capitán de un solo golpe, ya que no tenía tiempo para otro, pero falló. El capitán Fleetwood siempre lleva una coraza bajo su abrigo\nEl sucio canalla, le disparó en el hígado y logró huir y esconderse. Parece que tiene amigos en la ciudad. El único detalle que el capitán recuerda es que el asesino solo tiene un ojo. Sin embargo, no nos ayudará mucho, hay muchos Cíclopes como él merodeando por los muelles estos días\nRichard ha perdido mucha sangre y la pimienta le irritó los ojos horriblemente, por lo que ahora está casi ciego...";
		link.l1 = "¿Pimienta molida? Esa es una forma costosa de dejar a alguien ciego. Fleetwood debe haber enfadado seriamente a alguien. Lamento lo de tu capitán. ¿Ha revelado algo la búsqueda del atacante?";
		link.l1.go = "Fleetwood_house_1";
		break;

	case "Fleetwood_house_1":
		dialog.text = "Los marineros del capitán Fleetwood han buscado por todo el pueblo y las bahías locales, ¡pero no encontraron nada, que les corten el cuello! Si no lo encontramos justo después del ataque, no hay esperanza de encontrar al bastardo ahora. El capitán Fleetwood tiene muchos enemigos... Pero, capitán, mi comandante quiere verlo de todos modos a pesar del incidente. Ahora descansa en su casa, así que vayamos a verlo. ¡Sígame!";
		link.l1 = "Guía el camino, señor Knippel.";
		link.l1.go = "Fleetwood_house_2";
		break;

	case "Fleetwood_house_2":
		chrDisableReloadToLocation = true; // закрыть локацию
		bDisableFastReload = true;		   // закроем быстрый переход
		LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
		LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
		LocatorReloadEnterDisable("SentJons_town", "gate_back", true); // чтобы не сбежал
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_town", "reload", "houseH1", "OpenTheDoors", -1);
		pchar.quest.Knippel_Outside.win_condition.l1 = "location";
		pchar.quest.Knippel_Outside.win_condition.l1.location = "SentJons_town";
		pchar.quest.Knippel_Outside.function = "Knippel_GoTown";
		LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);
		sld = characterFromId("Fleetwood");
		LAi_SetStayType(sld);
		ChangeCharacterAddressGroup(sld, "SentJons_houseSP3_room", "goto", "goto1");
		AddLandQuestMark(sld, "questmarkmain");
		pchar.GenQuestBox.SentJons_houseSP3_room = true;
		pchar.GenQuestBox.SentJons_houseSP3_room.box1.money = 110000;
		break;

	case "InFleetwoodHouse":
		dialog.text = "El capitán Fleetwood está arriba en su cuarto. Ve a él, te está esperando. Me quedaré aquí.";
		link.l1 = "Entendido, Sr. Knippel. Estoy en camino.";
		link.l1.go = "exit";
		break;

	case "Knippel_ToOfficer":
		dialog.text = "Escucha cap... El capitán Fleetwood está a salvo y en buenas manos ahora. Quiero ayudarte a vengarte del bastardo que lo atacó. Te ofrezco mis servicios como oficial de artillería. No soy tan bueno en esgrima, demasiado viejo para eso, pero puedo derribar los palos mayores de un mercante a mil pasos.";
		link.l1 = "Ahora eso me gustaría verlo. ¡Bienvenido a bordo, Sr. Knippel!";
		link.l1.go = "Knippel_ToOfficer_1";
		break;

	case "Knippel_ToOfficer_1":
		LocatorReloadEnterDisable("SentJons_town", "reload1_back", false);
		LocatorReloadEnterDisable("SentJons_town", "reload2_back", false);
		LocatorReloadEnterDisable("SentJons_town", "gate_back", false); // откроем локаторы
		// Книппеля - в офицеры
		npchar.quest.OfficerPrice = sti(pchar.rank) * 500;
		Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
		npchar.OfficerWantToGo.DontGo = true; // не пытаться уйти
		npchar.HalfImmortal = true;			  // полубессмертен
		npchar.loyality = 20;
		AddDialogExitQuestFunction("LandEnc_OfficerHired");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		SetFunctionTimerCondition("GotoBridgetownOver", 0, 0, 30, false); // на все дела - 1 месяц
		AddSimpleRumourCity("Dicen que el mismísimo Sir Richard Fleetwood está en deuda contigo. Usted es un hombre muy importante en nuestra ciudad, señor...", "SentJons", 10, 3, "");
		break;

	case "hired":
		dialog.text = "¡Ahoy, capitán! ¿Necesita algo?";
		link.l1 = "No, nada.";
		link.l1.go = "exit";
		NextDiag.TempNode = "hired";
		break;

	case "MC_GoAway":
		PlaySound("Voice\Spanish\hambit\Charlie Knippel-04.wav");
		if (pchar.questTemp.HWIC.Eng == "MirageFail")
		{
			dialog.text = "Eres un completo bufón, compadre, ¡rayos y truenos! Fallaste en realizar una tarea elemental: capturar el 'Espejismo' sin perder el 'Valkiria'\nNuestra tripulación no servirá más bajo tu mando. Estamos seguros de que Sir Fleetwood aprobará nuestra decisión, le gustan los idiotas tan poco como a nosotros.";
			link.l1 = "¡Que te jodan a ti y a tu amo!";
			link.l1.go = "exit";
		}
		if (pchar.questTemp.HWIC.Eng == "GotoBridgetown" || pchar.questTemp.HWIC.Eng == "SeekVanBerg")
		{
			dialog.text = "Eres un completo idiota, compañero, ¡disparo de cadena mi trasero! Hemos desperdiciado demasiado tiempo resolviendo tus problemas personales\nNuestra tripulación ya no te servirá. Estamos seguros de que Sir Fleetwood aprobará nuestra decisión, le gustan los idiotas tan poco como a nosotros.";
			link.l1 = "¡Que te jodan a ti y a tu amo!";
			link.l1.go = "exit";
		}
		if (pchar.questTemp.HWIC.Eng == "VanBergFailInWorld")
		{
			dialog.text = "Eres un completo idiota, camarada, ¡disparo en cadena mi trasero! Se te dijo que jugaras a ser un mercader solitario en el 'Valkyrie', ¿y qué hiciste? ¡Ahuyentaste al pirata con tu flotilla!\nEstamos seguros de que Sir Fleetwood aprobará nuestra decisión, le gustan los idiotas tan poco como a nosotros.";
			link.l1 = "¡Que te jodan a ti y a tu amo!";
			link.l1.go = "exit";
		}
		if (pchar.questTemp.HWIC.Eng == "MirageTake")
		{
			dialog.text = "Eres un completo idiota, camarada, ¡cadena de tiro mi trasero! ¿Decidiste perder nuestro tiempo haciendo cualquier cosa menos capturar el 'Mirage' y navegar hacia Antigua?\nNuestra tripulación ya no te servirá. Estamos seguros de que Sir Fleetwood aprobará nuestra decisión, a él le gustan los idiotas tan poco como a nosotros.";
			link.l1 = "¡Que te jodan a ti y a tu amo!";
			link.l1.go = "exit";
		}
		PChar.quest.Munity = "Deads";
		LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
		if (sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_VALCIRIA) // если сам на Валькирии
		{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "Boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);
		}
		else
		{
			for (i = 1; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if (iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA)
					{
						pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
						sld = GetCharacter(sti(pchar.questTemp.HWIC.Eng.CompanionIndex));
						RemoveCharacterCompanion(PChar, sld);
						AddPassenger(PChar, sld, false);
					}
				}
			}
		}
		LAi_CharacterDisableDialog(npchar);
		LAi_SetImmortal(npchar, true);
		ChangeCharacterAddressGroup(npchar, "SentJons_houseH1", "goto", "goto1"); // Книппеля домой
		pchar.questTemp.HWIC.Eng = "end";
		pchar.questTemp.HWIC.Detector = "eng_fail";
		CloseQuestHeader("Holl_Gambit");
		break;

	case "OnCuracao":
		pchar.quest.HWICEng_toBarbadosOver.over = "yes"; // снять прерывание
		dialog.text = "Saludos, capitán. ¡Me alegra verte!";
		link.l1 = "Saludos, Sr. Knippel. ¿Tienes el dinero? Dámelo y vayamos a Willemstad a buscar a Abigail. ¿Te unirás a mí?";
		link.l1.go = "OnCuracao_1";
		break;

	case "OnCuracao_1":
		dialog.text = "Capitán, escuche... No hay necesidad de ir a ningún lado ahora.";
		link.l1 = "¿De qué estás hablando? ¡Esto es una tontería!";
		link.l1.go = "OnCuracao_2";
		break;

	case "OnCuracao_2":
		dialog.text = "Tengo una carta del capitán Fleetwood para ti. Y el dinero. Pero este dinero no es para el padre de Abigail, sino para ti. Doscientos mil pesos. Lee la carta e intenta no juzgarlo demasiado severamente...";
		link.l1 = "¡¿Qué demonios está pasando estos días?! ¿Otra sorpresa desagradable? ¡Dame la carta!";
		link.l1.go = "OnCuracao_3";
		break;

	case "OnCuracao_3":
		DialogExit();
		NextDiag.CurrentNode = "OnCuracao_4";
		AddMoneyToCharacter(pchar, 200000);
		LAi_SetCitizenType(npchar);
		npchar.lifeday = 1; // еще денек пусть погуляет по пляжу
		pchar.quest.Holland_ShoreAttack.win_condition.l1 = "location";
		pchar.quest.Holland_ShoreAttack.win_condition.l1.location = "Curacao";
		pchar.quest.Holland_ShoreAttack.function = "CreateHollandShorePatrol"; // патруль в прибрежных водах
		LocatorReloadEnterDisable("SentJons_town", "basement1_back", false);   // открыть подземелье
		pchar.questTemp.HWIC.Eng = "MerdokMeeteng";
		AddQuestRecordInfo("LetterFromFleetwood", "1");
		AddQuestRecord("Holl_Gambit", "2-23");
		AddLandQuestMark(npchar, "questmarkmain");
		break;

	case "OnCuracao_4":
		dialog.text = "¿Lo leíste, capitán? Seré franco. Estoy avergonzado del capitán Fleetwood y de lo que hizo, disparar con bala encadenada su... ah, al diablo con esto. Rodenburg se enfureció cuando se enteró del romance de Abigail con Richard. Las patrullas a pie están peinando Curazao y hay barcos militares de la Compañía patrullando las aguas locales. Necesitamos largarnos de aquí.\n Capitán, ¿necesita un artillero? No necesito lujo, solo una ración normal de mar de manera regular. No soy muy bueno con la esgrima, demasiado viejo para eso, pero puedo derribar los juanetes de un mercante a mil pasos.";
		link.l1 = "¡Maldita sea, me gustaría ver cómo haces eso, Sr. Knippel. ¡Bienvenido a la tripulación!";
		link.l1.go = "Knippel_hire";
		link.l2 = "Lamento haber ayudado a ustedes, sinvergüenzas ingleses, desde el principio. Ahora no sé cómo salir de este lío. Sigue tu propio camino, ya he tenido suficientes sorpresas.";
		link.l2.go = "Knippel_exit";
		DelLandQuestMark(npchar);
		break;

	case "Knippel_hire":
		DialogExit();
		DeleteAttribute(npchar, "LifeDay");
		npchar.quest.OfficerPrice = sti(pchar.rank) * 200;
		npchar.OfficerWantToGo.DontGo = true;
		DeleteAttribute(npchar, "CompanionDisable"); // теперь можем и в компаньоны
		DeleteAttribute(npchar, "HalfImmortal");
		npchar.loyality = MAX_LOYALITY;
		npchar.OfficerImmortal = true;
		npchar.Health.HP = 60.0;
		npchar.Health.maxHP = 60.0;
		SetCharacterPerk(npchar, "ShipEscape");
		AddPassenger(pchar, npchar, false);
		SetCharacterRemovable(npchar, true);
		npchar.Payment = true;
		LAi_SetImmortal(npchar, false);
		LAi_SetHP(npchar, 120, 120);
		LAi_SetOfficerType(npchar);
		npchar.greeting = "knippel_hire";
		NextDiag.CurrentNode = "Knippel_officer";
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		SaveCurrentNpcQuestDateParam(npchar, "HiredDate");

		// Sinistra - через 2 месяца стартует личный квест Чарли Книппеля "Длинные тени старых грехов"
		SetTimerCondition("DTSG_Start", 0, 0, 60, false);
		break;

	case "Knippel_exit":
		DialogExit();
		npchar.lifeday = 0;
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
		break;

		//------------------------------------------------против всех-----------------------------------------------
	case "Knippel_abordage":
		dialog.text = "¡Avast, ratero de sentina! ¿Por qué has atacado este pacífico barco holandés? No tengo mercancías valiosas ni oro, ¡cadena mi trasero!";
		link.l1 = "¿Barco holandés? ¡Ja ja! No me hagas reír, 'holandés'. He atacado tu bergantín para capturarte, querido Charlie. Bienvenido a mi bodega. Hablaremos sobre hacia dónde navegabas y por qué...";
		link.l1.go = "Knippel_abordage_1";
		break;

	case "Knippel_abordage_1":
		AddQuestRecord("Holl_Gambit", "3-20");
		pchar.quest.Knippel_DieHard.over = "yes";
		DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
		DialogExit();
		LAi_SetPlayerType(pchar);
		pchar.questTemp.HWIC.Self = "KnippelPrisoner";
		npchar.lifeday = 0;
		SetFunctionTimerCondition("RemoveKnippelOver", 0, 0, 1, false); // таймер до конца суток, ибо нефиг
		break;

	case "Knippel_prisoner":
		DelLandQuestMark(npchar);
		PlaySound("Voice\Spanish\hambit\Charlie Knippel-04.wav");
		dialog.text = "Eres un diablo, pirata... ¡Arderás en el infierno por todos tus pecados! ¡Grit...";
		link.l1 = "Relájate, predicador. Predicas como un puritano. Más te vale ocuparte primero del estado de tu alma.";
		link.l1.go = "Knippel_prisoner_1";
		break;

	case "Knippel_prisoner_1":
		dialog.text = "¿Qué planeas, canalla? ¿Qué quieres de mi comandante y de la pobre chica holandesa?";
		link.l1 = "No es asunto tuyo, Charlie. Ya no te necesito. Levántate.";
		link.l1.go = "Knippel_prisoner_2";
		break;

	case "Knippel_prisoner_2":
		dialog.text = "¿Quieres matarme? Digno de un bastardo como tú. *escupe* ¡Vete al diablo!";
		link.l1 = "Levántate, Charlie. Di tus últimas oraciones.";
		link.l1.go = "Knippel_prisoner_3";
		break;

	case "Knippel_prisoner_3":
		DialogExit();
		LAi_SetActorType(pchar);
		sld = characterFromId("KnippelClone");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "Ground_StandUp", "Kill_Knippel", 3.5);
		pchar.quest.RemoveKnippelOver.over = "yes"; // снять таймер
		break;

	//--> ----------------------------------- офицерский блок ------------------------------------------
	case "Knippel_officer":
		dialog.text = "¡Ahoy, capitán, bola encadenada en mi trasero!";
		if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
		{
			Link.l4 = "Señor Knippel, voy a la antigua y perdida ciudad india de Tayasal. Seré claro, este va a ser un viaje realmente peligroso y también inusual - necesitamos llegar allí a través de este... ídolo mágico. ¿Te unirás a mí?";
			Link.l4.go = "tieyasal";
		}

		////////////////////////казначей///////////////////////////////////////////////////////////
		// boal отчёт о корабле
		if (CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
		{
			Link.l11 = "Señor Knippel, deme un informe completo del barco.";
			Link.l11.go = "QMASTER_1";

			// Warship. Автозакупка товара
			Link.l12 = "Quiero que compres ciertos bienes cada vez que estemos atracados.";
			Link.l12.go = "QMASTER_2";
		}

		if (CheckAttribute(NPChar, "IsCompanionClone")) //////////////////компаньон//////////////////////////////////////////////
		{
			// dialog.text = "    He llegado según su disposición, capitán.";
			Link.l2 = "Necesito darte varias órdenes.";
			Link.l2.go = "Companion_Tasks";
			NextDiag.TempNode = "Knippel_officer"; // не забыть менять в зависисомости от оффа
			break;
		}
		Link.l1 = "¡Escucha mis órdenes!";
		Link.l1.go = "stay_follow";
		link.l2 = "Es nada. ¡Despedido!";
		link.l2.go = "exit";
		NextDiag.TempNode = "Knippel_officer";
		break;

	/////////////////////////// ответы для казначея ///////////////////////////////////
	case "QMASTER_1":
		dialog.Text = "Hundidme... Los cañones están bien, reemplazamos los que explotan y mantenemos nuestra pólvora seca y segura. ¿Qué tipo de informe esperabas, capitán? Soy un viejo artillero, no un intendente. ¡Disparar cadenas a mi trasero, soy el mejor artillero del Caribe, eso sí!";
		Link.l1 = "Sin discutir aquí, Sr. Knippel, usted conoce su oficio. Buscaré un sobrecargo yo mismo, no se preocupe.";
		Link.l1.go = "exit";
		break;

	case "QMASTER_2":
		dialog.text = "¿Quieres que el viejo Charlie cambie su cubierta de armas por el alcázar? Capitán, yo hundo barcos, no peleo por cada peso. Y estoy seguro de que me estafarán en la primera colonia donde lo intentemos.";
		link.l1 = "Pero por supuesto, señor Knippel. Debería empezar a buscar un intendente adecuado.";
		link.l1.go = "exit";
		break;

	// Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
	case "Companion_Tasks":
		dialog.Text = "Te escucho.";
		Link.l1 = "Esto se trata de abordaje.";
		Link.l1.go = "Companion_TaskBoarding";
		Link.l2 = "Se trata de tu barco.";
		Link.l2.go = "Companion_TaskChange";
		if (bBettaTestMode) // Только при бета-тесте
		{
			Link.l3 = "Quiero que dejes mi escuadrón por un tiempo y busques fortuna por tu cuenta.";
			Link.l3.go = "CompanionTravel";
		}
		Link.l8 = "Nada hasta ahora.";
		Link.l8.go = "exit";
		break;

	case "Companion_TaskBoarding":
		dialog.Text = "Entonces, ¿cuál es tu deseo?";
		Link.l1 = "No abordes los barcos enemigos. Cuida de ti mismo y de la tripulación.";
		Link.l1.go = "Companion_TaskBoardingNo";
		Link.l2 = "Quiero que abordes los barcos enemigos.";
		Link.l2.go = "Companion_TaskBoardingYes";
		break;

	case "Companion_TaskChange":
		dialog.Text = "Entonces, ¿cuál es tu deseo?";
		Link.l1 = "Me gustaría que no cambiaras tu barco por otro después de abordarlo. Tu barco es demasiado valioso.";
		Link.l1.go = "Companion_TaskChangeNo";
		Link.l2 = "Cuando abordes barcos enemigos, puedes quedártelos si resultan ser decentes.";
		Link.l2.go = "Companion_TaskChangeYes";
		break;

	case "Companion_TaskBoardingNo":
		dialog.Text = "¡Aye aye!";
		Link.l1 = "A sus órdenes.";
		Link.l1.go = "exit";
		NPChar.Tasks.CanBoarding = false;
		break;

	case "Companion_TaskBoardingYes":
		dialog.Text = "Será hecho.";
		Link.l1 = "Descansa.";
		Link.l1.go = "exit";
		NPChar.Tasks.CanBoarding = true;
		break;

	case "Companion_TaskChangeNo":
		dialog.Text = "¡Sí, sí!";
		Link.l1 = "Se hará.";
		Link.l1.go = "exit";
		NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

	case "Companion_TaskChangeYes":
		dialog.Text = "Se hará.";
		Link.l1 = "Relájate.";
		Link.l1.go = "exit";
		NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//	<========////////////////////////////////////////

	case "stay_follow":
		dialog.Text = "¿Órdenes?";
		Link.l1 = "¡Quédate aquí!";
		Link.l1.go = "Boal_Stay";
		Link.l2 = "¡Sígueme y mantén el ritmo!";
		Link.l2.go = "Boal_Follow";
		sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
		if (sGun != "")
		{
			rItm = ItemsFromID(sGun);
			if (CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
			{
				Link.l3 = "Cambia el tipo de munición para tus armas de fuego.";
				Link.l3.go = "SetGunBullets";
			}
		}
		break;

	case "SetGunBullets":
		Dialog.Text = "Eligiendo el tipo de munición:";
		sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
		rItm = ItemsFromID(sGun);
		makearef(rType, rItm.type);
		for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
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
		i = sti(NPChar.SetGunBullets) + 1;
		sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
		rItm = ItemsFromID(sGun);
		sAttr = "t" + i;
		sBullet = rItm.type.(sAttr).bullet;
		LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
		LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
		NextDiag.CurrentNode = NextDiag.TempNode;
		rItem = ItemsFromID(sBullet);
		notification(GetFullName(NPChar) + " " + XI_ConvertString("AmmoSelectNotif") + GetConvertStr(rItem.name, "ItemsDescribe.txt") + "", "AmmoSelect");
		DeleteAttribute(NPChar, "SetGunBullets");
		DialogExit();
		break;

	case "Boal_Stay":
		Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
		AddDialogExitQuestFunction("LandEnc_OfficerStay");
		dialog.Text = "¡Hay un cambio de disposición!";
		Link.l1 = "Despedido.";
		Link.l1.go = "Exit";
		Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
		break;

	case "Boal_Follow":
		SetCharacterTask_FollowCharacter(Npchar, PChar);
		dialog.Text = "¡Hay un cambio de disposición!";
		Link.l1 = "Retírate.";
		Link.l1.go = "Exit";
		break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------

		// на Тайясаль
	case "tieyasal":
		dialog.text = "Me he encariñado mucho contigo durante mi servicio, " + pchar.name + ", y no dejo a mi capitán en la estacada. Te seguiría hasta el infierno si fuera necesario. ¡Estoy contigo!";
		link.l1 = "¡Gracias, señor Knippel! Me alegra haber acertado contigo.";
		link.l1.go = "tieyasal_1";
		break;

	case "tieyasal_1":
		dialog.text = "¿Cuándo empezaremos, maldita sea?";
		link.l1 = "Un poco más tarde. Tenemos que prepararnos para ello.";
		link.l1.go = "tieyasal_2";
		break;

	case "tieyasal_2":
		DialogExit();
		AddQuestRecord("Tieyasal", "22");
		npchar.quest.Tieyasal = "teleport";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	//--> блок реагирования на попытку залезть в сундук
	case "Man_FackYou":
		dialog.text = LinkRandPhrase("Eres un " + GetSexPhrase("Ladrón, señor! ¡Guardias, atrapadlo!", "¡ladrona, chica! Guardias, llévensela") + "!!!", "¡Sólo mira eso! ¡El momento en que me di la vuelta, decidiste revisar mi cofre! ¡Atrapen al ladrón!!!", "¡Guardias! ¡Robo! ¡Atrapen al ladrón!!!");
		link.l1 = "¡Maldita sea!";
		link.l1.go = "exit";
		LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}

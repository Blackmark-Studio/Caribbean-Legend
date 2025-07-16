// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?", "¿En qué puedo ayudarle, " + GetAddress_Form(NPChar) + "?"), "Intentaste hacerme alguna pregunta no hace mucho, " + GetAddress_Form(NPChar) + "... ", "Esta es la tercera vez que me molestas ahora...", "¿Más preguntas, supongo?", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No tengo nada de qué hablar en este momento."), "Umph, ¿dónde se ha ido mi memoria...?", "Sí, realmente es la tercera vez...", "No, ¿qué preguntas?...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		// Голландский гамбит /за Англию/
		if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
		{
			link.l1 = "Me gustaría un trago. Sírveme el mejor ron que tengas.";
			link.l1.go = "TavernDone";
		}
		if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "toBarbados")
		{
			link.l1 = "Escucha, ¿dónde está Callow Gastón?";
			link.l1.go = "Tonzag_Letter";
		}
		// Голландский гамбит /против всех/
		if (!CheckAttribute(npchar, "quest.HWICTake") && CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Self") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			link.l1 = "¿Tienes algún tipo de trabajo? ¿O tal vez podrías sugerir algo?";
			link.l1.go = "Tonzag_check";
		}
		if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FernandoDie")
		{
			link.l1 = "He terminado el trabajo. Fernando Rodríguez está muerto.";
			link.l1.go = "Task_check";
		}
		// Страж Истины
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
		{
			link.l1 = "Escucha, ¿ha llegado aquí a esta ciudad un alquimista, o un médico? Es italiano, tiene unos treinta años, su nombre es Gino Gvineili. ¿Has oído algo al respecto?";
			link.l1.go = "guardoftruth";
		}
		break;

	// Голландский гамбит /за Англию/
	case "TavernDone":
		dialog.text = "Aquí tienes tu bebida. ¡El mejor ron para nuestro nuevo invitado! ¿Es una ocasión especial o solo has pasado por aquí para mojar el gaznate?";
		link.l1 = "¡Ja, puedes decir que es una ocasión especial! Estoy llevando algunos negros a Blueweld. He modificado recientemente la bodega de mi nuevo bergantín específicamente para este propósito. Acabo de pasar por una plantación y hablé con el capataz, quien me encargó un buen lote de 'marfil negro'. Así que espérame de vuelta en tu taberna pronto. Entregaré la mercancía a Blueweld y luego haré más negocios aquí en Barbados, ¡yo-ho!";
		link.l1.go = "TavernDone_1";
		break;

	case "TavernDone_1":
		dialog.text = "¿De verdad? ¡Pues no hay vergüenza en beber por un buen trato! Entonces, dices que vas a hacer negocios en Barbados. ¡Eso es genial! ¡Salud por ti, capitán!";
		link.l1 = "Gracias, amablemente camarada. Muy bien... Iré a buscar un lugar donde pueda sentarme.";
		link.l1.go = "exit";
		npchar.quest.HWICTalked = "true";
		pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter) + 1;
		AddQuestRecord("Holl_Gambit", "2-12");
		DelLandQuestMark(npchar);
		if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7)
		{
			AddQuestRecord("Holl_Gambit", "2-6");
			pchar.questTemp.HWIC.Eng = "SeekVanBerg";
			pchar.quest.GotoBridgetownOver.over = "yes"; // снять таймер
			DelMapQuestMarkCity("Bridgetown");
			pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
			pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
		}
		break;

	case "Tonzag_Letter":
		dialog.text = "Gastón se fue del pueblo dos días después de tu acto de 'comerciante'. ¡Montaste un espectáculo aquí, ja! Tu engaño fue descubierto rápidamente, este pueblo es pequeño y los chismes viajan rápido. Esto hizo que Gastón se marchara. Nadie lo ha visto aquí desde entonces. Sin embargo, ha dejado una carta para ti.\nPidió entregártela personalmente en caso de que aparezcas aquí antes que él. De hecho, no eres el primer hombre que busca a Gastón. Hubo un hombre grande de ojos estrechos y un viejo, parecían españoles o portugueses, no puedo decirlo con certeza. Pero no puedo olvidar su rostro, había algo muy extraño en él...";
		link.l1 = "Dame esa carta... ¡Gracias!";
		link.l1.go = "Tonzag_Letter_1";
		DelLandQuestMark(npchar);
		DelMapQuestMarkCity("Bridgetown");
		break;

	case "Tonzag_Letter_1":
		DialogExit();
		AddQuestRecord("Holl_Gambit", "2-22");
		AddQuestRecordInfo("LetterFromGaston", "1");
		pchar.questTemp.HWIC.Eng = "toCuracao";
		LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);		// закрыть дом Флитвуда
		LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);		// закрыть аптеку
		LocatorReloadEnterDisable("SentJons_town", "basement1_back", true); // закрыть подземелье
		pchar.quest.Knippel_Shore.win_condition.l1 = "location";
		pchar.quest.Knippel_Shore.win_condition.l1.location = "Shore24";
		pchar.quest.Knippel_Shore.function = "KnippelOnCuracao";
		AddMapQuestMarkShore("Shore24", true);
		break;

	// Голландский гамбит /против всех/
	case "Tonzag_check":						 // начинаем проверять нашего ГГ по всем статьям
		if (sti(pchar.reputation.nobility) > 48) // высокая репа
		{
			// belamour legendary edition покажем критерии
			notification("¡Reputación demasiado baja! (Pícaro)", "None");
			PlaySound("Voice\Spanish\hambit\Ercule Tongzag-03.wav");
			dialog.text = "Ya veo. Así que eres un tipo heroico. Lo siento, capitán. Pero hoy en día pagan mal por las heroicidades.";
			link.l1 = "¡Eh, eh! ¡Cuidado con ese sarcásmo, compañero!";
			link.l1.go = "exit";
			break;
		}
		bool bOk = GetSummonSkillFromName(pchar, SKILL_F_LIGHT) > 34 || GetSummonSkillFromName(pchar, SKILL_FENCING) > 34 || GetSummonSkillFromName(pchar, SKILL_F_HEAVY) > 34 || GetSummonSkillFromName(pchar, SKILL_PISTOL) > 34;
		if (!bOk) // слабое фехтование
		{
			// belamour legendary edition покажем критерии -->
			notification("Skill Check Failed (35)", SKILL_F_LIGHT);
			notification("Skill Check Failed (35)", SKILL_FENCING);
			notification("Skill Check Failed (35)", SKILL_F_HEAVY);
			notification("Skill Check Failed (35)", SKILL_PISTOL);
			// <--
			dialog.text = "Capitán, eres demasiado blando. Necesito a un luchador un poco más reputado que tú. Vuelve cuando aprendas a manejar ese acero que cuelga de tu cinturón. Y un poco de precisión al disparar tampoco vendría mal.";
			link.l1 = "Ya veo. Entonces te haré una visita más tarde.";
			link.l1.go = "exit";
			break;
		}
		PlaySound("Voice\Spanish\hambit\Ercule Tongzag-02.wav");
		dialog.text = "¿Qué? ¿Me tomas el pelo? Sé como conseguir un buen premio mayor, si no tienes miedo de ensuciarte las manos. En realidad llegas a tiempo. Tengo un encargo que debe cumplirse de inmediato. Te presentaré a algunas personas influyentes. Ahora escucha, esto es lo que tienes que hacer.";
		link.l1 = "Soy todo oídos.";
		link.l1.go = "Tonzag_task";
		break;

	case "Tonzag_task":
		DelLandQuestMark(npchar);
		DelMapQuestMarkCity("Bridgetown");
		pchar.questTemp.HWIC.Self.SpainCity = FindSpainCity();
		log_Testinfo(pchar.questTemp.HWIC.Self.SpainCity);
		dialog.text = "Un hidalgo ha llegado recientemente de Sevilla con la intención de evitar algunas consecuencias indeseadas de un duelo en Europa. Pero la venganza no tiene límites y una familia noble española desea a este hidalgo muerto. Cumple su deseo por cualquier medio necesario.\nTrae el dedo del hombre con su anillo como prueba. Además, trae todos los otros objetos que encuentres en su cadáver. ¿Estás listo para aceptar el trabajo?";
		link.l1 = "Si el pago es bueno, entonces estoy dentro.";
		link.l1.go = "Tonzag_task_1";
		link.l2 = "¿Trabajar como asesino? ¡De ninguna manera!";
		link.l2.go = "Tonzag_exit";
		npchar.quest.HWICTake = "true";
		pchar.questTemp.HWIC.CanTake.Self = "true"; // признак, что против всех уже бралась
		break;

	case "Tonzag_exit":
		dialog.text = "Entonces, vete al diablo y olvida de lo que hemos hablado.";
		link.l1 = "Me voy.";
		link.l1.go = "exit";
		DeleteAttribute(pchar, "questTemp.HWIC.Self"); // откат к двум другим вариантам
		pchar.questTemp.HWIC.Fail3 = "true";
		if (!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
		{
			AddMapQuestMarkCity("Villemstad", false);
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
		}
		if (!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
		{
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
		}
		break;

	case "Tonzag_task_1":
		dialog.text = "Tu recompensa será de 30 000 piezas de a ocho, buen dinero. Además, puedes tomar cada moneda que encuentres en su cuerpo. Ahora discutamos los detalles. Se llama Don Fernando Rodríguez, 35 años, alto, moreno, vestido como un oficial militar. Es un buen marinero y un espadachín experimentado.\nNo puedo decirte dónde encontrarlo, todo lo que sé es que está en algún lugar del Caribe.\nBusca en cada ciudad española hasta que lo atrapes. Tienes dos meses. Una última cosa: sé lo que lleva consigo, así que ni pienses en esconderme ningún objeto. ¿Preguntas?";
		link.l1 = "No tengo preguntas. ¡Estoy en camino!";
		link.l1.go = "Tonzag_task_2";
		break;

	case "Tonzag_task_2":
		DialogExit();
		pchar.questTemp.HWIC.Self = "start";
		SetFunctionTimerCondition("TargetFernandoOver", 0, 0, 60, false); // таймер
		// SetFunctionExitFromLocationCondition("CreateMapMarksTonzag", pchar.location, false);
		AddQuestRecord("Holl_Gambit", "3-1");
		ReOpenQuestHeader("Holl_Gambit"); // данила . чтобы вышел из архива
		Log_TestInfo("" + XI_ConvertString("Colony" + pchar.questTemp.HWIC.Self.SpainCity) + "");
		DelLandQuestMark(npchar);
		DelLandQuestMark(characterFromId("Lucas"));
		DelLandQuestMark(characterFromId("Knippel"));
		DelMapQuestMarkCity("Bridgetown");
		DelMapQuestMarkCity("Villemstad");
		DelMapQuestMarkCity("SentJons");
		AddMapQuestMarkCity(pchar.questTemp.HWIC.Self.SpainCity, true);
		AddLandQuestMark(characterFromId(pchar.questTemp.HWIC.Self.SpainCity + "_tavernkeeper"), "questmarkmain");
		break;

	case "Task_check":
		DelLandQuestMark(npchar);
		DelMapQuestMarkCity("bridgetown");
		dialog.text = "¿Tienes un dedo con el anillo contigo? Déjame verlo.";
		if (CheckCharacterItem(pchar, "Finger"))
		{
			link.l1 = "Sí, por supuesto. Aquí está.";
			link.l1.go = "Task_check_1";
		}
		else
		{
			link.l1 = "No. Fernando se hundió en el agua junto con su barco y el dedo se hundió con Fernando.";
			link.l1.go = "Task_fail";
		}
		break;

	case "Task_fail":
		dialog.text = "El dedo con el anillo era una condición obligatoria en el contrato. Se suponía que debía servir como confirmación de la muerte del cliente. ¿Quién sabe si Rodríguez nadó hasta la orilla desde el barco hundido? ¿Lo comprobaste? No. Básicamente has fallado en la tarea, así que nuestro acuerdo se ha terminado. Todo lo mejor.";
		link.l1 = "Pero me deshice de él. ¡Se ha ido! Oh, vete al demonio... Hay muchas otras cosas que hacer en el Caribe. Adiós.";
		link.l1.go = "exit";
		if (!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
		{
			AddMapQuestMarkCity("Villemstad", false);
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
		}
		if (!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
		{
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
		}
		pchar.questTemp.HWIC.Fail3 = "true";
		AddQuestRecord("Holl_Gambit", "3-8");
		CloseQuestHeader("Holl_Gambit");
		DeleteAttribute(pchar, "questTemp.HWIC.Self"); // зачищаем для возможности отката к голландскому варианту
		break;

	case "Task_check_1":
		RemoveItems(PChar, "Finger", 1);
		dialog.text = "¡Maravilloso! Me quedaré el dedo yo mismo. Ahora, veamos el contenido de sus bolsillos. Vamos a ver qué has traído.";
		link.l1 = "Adelante, echa un vistazo...";
		link.l1.go = "Task_check_2";
		break;

	case "Task_check_2":
		if (CheckCharacterItem(pchar, "jewelry7") && CheckCharacterItem(pchar, "totem_05") && CheckCharacterItem(pchar, "amulet_1"))
		{
			dialog.text = "¡Ajá, eso es todo lo que necesito! ¡Bien hecho! Has hecho un buen trabajo. Estoy muy complacido contigo.";
			link.l1 = "¡Gracias! Siempre es agradable recibir elogios por un trabajo bien hecho.";
			link.l1.go = "Task_complete";
		}
		else
		{
			dialog.text = "Hm... Te advertí que sé lo que Rodriguez llevaba encima. Y no veo lo que necesito aquí. ¿Te has guardado esas cosas? ¿Las has perdido? No importa de todos modos. No tengo deseo de involucrarme contigo más. Lárgate de aquí.";
			link.l1 = "Oh, ...";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Fail3 = "true";
			if (!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
			{
				AddMapQuestMarkCity("Villemstad", false);
				AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			}
			if (!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
			{
				AddMapQuestMarkCity("SentJons", false);
				AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			}
			AddQuestRecord("Holl_Gambit", "3-9");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Self"); // зачищаем для возможности отката к голландскому варианту
		}
		break;

	case "Task_complete":
		RemoveItems(PChar, "jewelry7", 1);
		RemoveItems(PChar, "totem_05", 1);
		RemoveItems(PChar, "amulet_1", 1);
		AddMoneyToCharacter(pchar, 30000);
		dialog.text = "Aquí está tu recompensa como prometí, treinta mil. Y también tengo una misión adicional, de alta responsabilidad y alto riesgo, pero la paga aumentará en consecuencia, 40 000 pesos.";
		link.l1 = "Soy todo oídos. ¿Quién es el próximo cliente?";
		link.l1.go = "Fleetwood_house";
		break;

	// 2 задание
	case "Fleetwood_house":
		PlaySound("Voice\Spanish\hambit\Ercule Tongzag-10.wav");
		dialog.text = "¡Te ves bastante amenazante! ¡Veamos cómo te va! Esta vez vas a cazar no a un hombre, sino un objeto. Debes colarte en la casa de Richard Fleetwood en Antigua y robar su bitácora. Él es un capitán inglés. El lugar está fuertemente custodiado, y Richard rara vez visita su casa. \nEl plan es sencillo. El gobernador de St. John's organizará una fiesta privada en diez días, a la que asistirá Fleetwood. Debes entrar en su casa por la noche entre la una y las tres en punto. Solo habrá un soldado adentro.\nDeshazte de él. Busca un diario dentro del apartamento de Richard. Toma esta llave.";
		link.l1 = "Hum... Interesante. Entendí lo que necesito hacer. ¡Estoy listo para ponerme en marcha!";
		link.l1.go = "Fleetwood_house_1";
		break;

	case "Fleetwood_house_1":
		GiveItem2Character(pchar, "key3");
		dialog.text = "Ten cuidado. No te metas en la casa antes de la fecha que te he indicado. De lo contrario, en el mejor de los casos, solo te echarán de allí o, en el peor de los casos, acabarás entre rejas. Repite la fecha y la hora.";
		link.l1 = "En exactamente diez días, entre la una y las tres de la madrugada.";
		link.l1.go = "Fleetwood_house_2";
		break;

	case "Fleetwood_house_2":
		dialog.text = "Bien. Puedes irte. ¡Buena suerte!";
		link.l1 = "Gracias, Gastón.";
		link.l1.go = "Fleetwood_house_3";
		break;

	case "Fleetwood_house_3":
		DialogExit();
		AddQuestRecord("Holl_Gambit", "3-10");
		pchar.questTemp.HWIC.Self = "theft";
		DeleteAttribute(pchar, "questTemp.HWIC.CanTake");				 // иные варианты более невозможны
		LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true); // комнату закроем
		pchar.GenQuestBox.SentJons_houseSP3_room = true;
		pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.FleetwoodJournal = 1; // положим в комод СЖ
		pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.sand_clock = 1;		  // и песочные часы
		AddDialogExitQuestFunction("CreateFleetwoodSoldiers");					  // 4 солдат в доме
		if (bImCasual)
			NewGameTip("Modo exploración: el temporizador no está desactivado. ¡Cumple el plazo!");
		SetFunctionTimerCondition("FleetwoodJournalOver", 0, 0, 11, false); // таймер
		pchar.quest.Fleetwood_Journal.win_condition.l1 = "Timer";
		pchar.quest.Fleetwood_Journal.win_condition.l1.date.hour = sti(GetTime());
		pchar.quest.Fleetwood_Journal.win_condition.l1.date.day = GetAddingDataDay(0, 0, 9);
		pchar.quest.Fleetwood_Journal.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 9);
		pchar.quest.Fleetwood_Journal.win_condition.l1.date.year = GetAddingDataYear(0, 0, 9);
		pchar.quest.Fleetwood_Journal.win_condition.l2 = "Hour";
		pchar.quest.Fleetwood_Journal.win_condition.l2.start.hour = 0;
		pchar.quest.Fleetwood_Journal.win_condition.l2.finish.hour = 3;
		pchar.quest.Fleetwood_Journal.win_condition.l3 = "locator";
		pchar.quest.Fleetwood_Journal.win_condition.l3.location = "SentJons_town";
		pchar.quest.Fleetwood_Journal.win_condition.l3.locator_group = "reload";
		pchar.quest.Fleetwood_Journal.win_condition.l3.locator = "houseSP3"; // доступно открывание двери
		pchar.quest.Fleetwood_Journal.function = "FleetwoodHouseEnter";
		pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
		pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
		pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier"; // если надумает раньше заявиться
		AddMapQuestMarkCity("sentjons", true);
		break;

	case "guardoftruth":
		dialog.text = LinkRandPhrase("No, no lo he hecho. Tenemos herbolarios y médicos, pero ninguno con ese nombre.", "Esta es la primera vez que oigo un nombre tan extraño. No, nunca hemos recibido una visita del hombre del que hablas.", "No tenemos ningún tipo de alquimista en absoluto. Tenemos médicos, pero ninguno con un nombre tan extraño.");
		link.l1 = "Ya veo. Es una lástima. ¡Seguiré buscando!";
		link.l1.go = "exit";
		npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

string FindSpainCity() // Jason выбрать радномный испанский город - пусть побегает
{
	int n, nation;
	int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
	int howStore = 0;

	for (n = 0; n < MAX_COLONIES; n++)
	{
		if (colonies[n].nation == SPAIN && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0)
		return "none";
	nation = storeArray[hrand(howStore - 1)];
	return colonies[nation].id;
}

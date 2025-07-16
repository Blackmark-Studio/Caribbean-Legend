// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?", "¿Cómo puedo ayudarle?"), "Intentaste hacerme esa pregunta no hace mucho...", "Sí, déjame adivinar... ¿Otra vez dando vueltas en círculos?", "Escucha, yo manejo las finanzas aquí, no respondo preguntas...", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No tengo nada de qué hablar en este momento."), "Umph, ¿dónde se ha ido mi memoria...?", "Lo has adivinado, lo siento...", "Entiendo...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		// Addon-2016 Jason ФМК-Гваделупа
		if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "continue")
		{
			link.l1 = "Soy el capitán " + GetFullName(pchar) + ". Tu hombre me dijo que querías verme. Soy todo oídos.";
			link.l1.go = "FMQG";
		}
		if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "sucsess")
		{
			link.l1 = "Soy yo de nuevo, monseniour " + GetFullName(pchar) + ". Te traje a Bertrand Pinette. Está en mi bodega.";
			link.l1.go = "FMQG_14";
		}
		if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "letter")
		{
			link.l1 = "Soy yo de nuevo, monsieur " + GetFullName(pchar) + ". Hablemos.";
			link.l1.go = "FMQG_17";
		}
		if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers")
		{
			link.l1 = "Soy yo otra vez, monsieur " + GetFullName(pchar) + ". Tengamos una charla.";
			link.l1.go = "FMQG_17";
		}
		if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
		{
			link.l1 = "Soy yo otra vez, monsieur " + GetFullName(pchar) + ". Supongo que no esperabas volver a verme.";
			link.l1.go = "FMQG_23";
		}
		break;

	// Addon-2016 Jason ФМК-Гваделупа
	case "FMQG":
		dialog.text = "A-ah, capitán " + GetFullName(pchar) + ". Estoy tan contento de verte. He estado esperándote durante bastante tiempo... Bien. Tengo una pregunta que hacerte. Hace algún tiempo, un hombre llamado Bertrand Pinette se acercó a ti en el puerto para subir a bordo de tu barco. Un tipo con aspecto adinerado y una peluca lujosa. ¿Te suena de algo?";
		link.l1 = "Sí, así es. Realmente se acercó a mí con ese propósito exacto.";
		link.l1.go = "FMQG_1";
		break;

	case "FMQG_1":
		DelLandQuestMark(npchar);
		Log_Info("¡Has recibido un bolso pesado!");
		PlaySound("interface\important_item.wav");
		GiveItem2Character(pchar, "purse3");
		dialog.text = "¿Quería contratarte a ti y a tu barco? Capitán, me harías un gran favor contándome todos los detalles de este caso. Haré que valga la pena. Aquí, toma esta bolsa llena de monedas. Es tuya, ahora por favor, cuéntame sobre Bertrand Pinette.";
		link.l1 = "Muy bien. Monsieur Pinette contrató mi barco para llevarlo a él y a dos de sus amigos desde Guadalupe hasta la Costa Española. Más específicamente, la Bahía de los Mosquitos en Portobello. Hice el trabajo, dejaron mi barco y se adentraron directamente en la jungla.";
		link.l1.go = "FMQG_2";
		break;

	case "FMQG_2":
		dialog.text = "Ya veo. ¿Y mencionó monsieur Pinette su destino final? ¿Y qué hay de sus acompañantes?";
		link.l1 = "Según sus propias palabras, se dirigían a Panamá. Sus amigos eran bastante intrigantes: dos oficiales, un español y un francés. Aún no puedo entender qué los unía, pero no me pagaron para hacer preguntas.";
		link.l1.go = "FMQG_3";
		break;

	case "FMQG_3":
		dialog.text = "¿Un oficial español? ¿Y un oficial francés? ¡Oh! ¡Eso sí que es algo! ¡Bien hecho, monsieur Pinette! ¡Qué perro astuto! ¡Incluso aquí encontró la manera de ganar dinero! ¿Panamá, dijiste?";
		link.l1 = "Sí, y te conté todo lo que sabía. ¿Puedo retirarme?";
		link.l1.go = "FMQG_4";
		break;

	case "FMQG_4":
		dialog.text = "Espera, capitán. Tengo una propuesta de negocio para usted. ¿No le interesa ganar algunas monedas? Pero primero, permítame contarle algo sobre sus pasajeros.";
		link.l1 = "Bueno, escuchemoslo.";
		link.l1.go = "FMQG_5";
		break;

	case "FMQG_5":
		dialog.text = "Monsieur Bertrand Pinette apareció en nuestra colonia hace dos años e inmediatamente comenzó a hacer negocios con los capitanes. El negocio es, bueno, también oscuro... Le estaban entregando mercancías de gran escasez en este lugar, objetos de valor, contrabando, incluso esclavos a veces... Él estaba tomando préstamos sistemáticamente para sus operaciones ilegales en mi oficina, pero siempre pagaba con todos los intereses.\nAntes de dejar la isla con tu buena ayuda, había tomado un gran préstamo, mucho más grande de lo habitual. Él es... era un cliente de confianza con un historial crediticio impecable, por eso le proporcioné un préstamo. Gran error. Monsieur Pinette ha huido y, obviamente, no va a devolver mis monedas.";
		link.l1 = "¿Cuál es la suma, si puedo preguntar?";
		link.l1.go = "FMQG_6";
		break;

	case "FMQG_6":
		dialog.text = "Es grande. Alrededor de ciento cincuenta mil pesos en doblones. Diez cofres, cada uno con ciento cincuenta doblones. Y no hablemos de todos los intereses.";
		link.l1 = "Hm... Te estuvo pagando durante dos años, te hizo acostumbrarte, tomó un préstamo sustancial y luego se volvió un pícaro. Inteligente.";
		link.l1.go = "FMQG_7";
		break;

	case "FMQG_7":
		dialog.text = "Precisamente, capitán. Por eso me gustaría contratarlo para un trabajo: encuentre a ese granuja y tráigalo aquí. Yo, el gobernador y el comandante encontraremos la manera de hacer que salde su deuda. Usted ha visto a ese hombre, fue su pasajero, eso significa que tiene más posibilidades de encontrar al señor Pinette que cualquier otro. Claro, también contrataré cazarrecompensas profesionales por su trasero miserable, pero tengo la sensación de que su ayuda resultará ser más efectiva.";
		link.l1 = "¿Qué tal una recompensa?";
		link.l1.go = "FMQG_8";
		break;

	case "FMQG_8":
		dialog.text = "Por hacer el trabajo, te daré un cofre lleno de doblones, ciento cincuenta monedas.";
		link.l1 = "Diría que esto sería una recompensa bastante patética por rastrear y secuestrar un alma viviente en la ciudad española.";
		link.l1.go = "FMQG_9";
		break;

	case "FMQG_9":
		dialog.text = "Capitán, supongo que monsieur Pinette le ha pagado bien con mi dinero, ya que evalúa mi propuesta tan barata. Le aseguro que vale la pena el esfuerzo. Por supuesto, tiene todo el derecho a negarse... pero tengo algo que decirle y seguramente le hará cambiar de opinión.";
		link.l1 = "¿Y qué es?";
		link.l1.go = "FMQG_10";
		break;

	case "FMQG_10":
		dialog.text = "Unos días antes de la fuga de Pinette de Guadalupe, un prisionero se había escapado de la prisión de Basse-Terre. Su nombre es don Carlos de Milyar, un hombre grande de España y un oficial. Lo logró gracias a la traición de un oficial francés, un teniente de la Marina... ¿Entiendes lo que quiero decir?";
		link.l1 = "Mm... ¿Y cómo me concierne eso? Estaba transportando pasajeros, nada más.";
		link.l1.go = "FMQG_11";
		break;

	case "FMQG_11":
		dialog.text = "¡Claro que sí, lo hiciste! Personalmente, no tengo dudas de que no tienes nada que ver con la organización de la fuga de don de Milyar. Pero no es así como nuestro gobernador junto con nuestro comandante podrían pensarlo. Un cargo de complicidad si tienes suerte y si no... Realmente no quiero continuar. Míralo por ti mismo, llevaste a bordo a un oficial español fugitivo, muy probablemente en alguna cala oculta... ¿estoy en lo cierto, capitán?";
		link.l1 = "Entiendo. Me estás chantajeando. Cometí un error al venir aquí...";
		link.l1.go = "FMQG_12";
		break;

	case "FMQG_12":
		dialog.text = "¿Qué dice, capitán?! ¡No le estoy chantajeando! Todo lo que pido es que me ayude por una buena recompensa. ¿Sería tan amable de encontrar al monsieur Pinette y llevarlo a Basse-Terre? Estaré esperando su regreso. Creo que dos meses son suficientes para navegar hasta Panamá y regresar.";
		link.l1 = "Me dejas sin elección. Aunque dudo que tal enfoque comercial nos haga amigos. Adiós, monsieur.";
		link.l1.go = "FMQG_13";
		break;

	case "FMQG_13":
		DialogExit();
		LocatorReloadEnterDisable("Baster_town", "reload1_back", false);
		LocatorReloadEnterDisable("Baster_town", "reload2_back", false);
		LocatorReloadEnterDisable("Baster_town", "gate_back", false); // открыть выходы из города
		pchar.questTemp.FMQG = "headhunter_panama";
		ReOpenQuestHeader("FMQ_Guadeloupe");
		AddQuestRecord("FMQ_Guadeloupe", "7");
		if (bImCasual)
		{
			NewGameTip("Modo exploración: se duplica la duración de las misiones");
			SetFunctionTimerCondition("FMQG_UsurerTimeOut", 0, 0, 122, false);
		}
		else
			SetFunctionTimerCondition("FMQG_UsurerTimeOut", 0, 0, 61, false);
		AddMapQuestMarkCity("panama", false);
		AddLandQuestMark(characterFromId("Panama_tavernkeeper"), "questmarkmain");

		// Sinistra - Старт квеста "Мерзкий Божок"
		PChar.quest.ChickenGod_StartLoc.win_condition.l1 = "ExitFromLocation";
		PChar.quest.ChickenGod_StartLoc.win_condition.l1.location = PChar.location;
		PChar.quest.ChickenGod_StartLoc.function = "ChickenGod_BrothelCheck";
		break;

	case "FMQG_14":
		DelMapQuestMarkCity("baster");
		DelLandQuestMark(npchar);
		dialog.text = "¡Excelentes noticias, capitán! Enviaré a mis hombres para recoger a este bastardo de su barco de inmediato. Este pajarillo no se escapará de mí esta vez... Usted ha merecido su recompensa, tome este cofre. Por favor, no se enoje conmigo, aquí tiene un amuleto. Es un regalo.";
		link.l1 = "Gracias. ¿Asumo que su silencio también es parte de mi recompensa?";
		link.l1.go = "FMQG_15";
		break;

	case "FMQG_15":
		Log_Info("¡Has recibido un cofre lleno de doblones!");
		Log_Info("¡Has recibido el amuleto 'Pescador'!");
		PlaySound("interface\important_item.wav");
		GiveItem2Character(pchar, "chest");
		GiveItem2Character(pchar, "obereg_7");
		dialog.text = "¿Silencio? ¿Sobre qué? Me encantaría verte entre mis clientes. ¿Sabes lo que dicen sobre el silencio y el oro?";
		link.l1 = "A veces vale mucho más que el oro, monsieur. Lección aprendida. ¡Adiós!";
		link.l1.go = "FMQG_16";
		break;

	case "FMQG_16":
		DialogExit();
		pchar.quest.FMQG_UsurerTimeOut.over = "yes";
		ref sld = characterFromId("FMQG_pass_1");
		RemovePassenger(pchar, sld);
		sld.lifeday = 0;
		pchar.questTemp.FMQG = "end";
		FMQ_Count();
		AddQuestRecord("FMQ_Guadeloupe", "23");
		CloseQuestHeader("FMQ_Guadeloupe");
		ChangeCharacterNationReputation(pchar, FRANCE, 5);
		ChangeCharacterComplexReputation(pchar, "nobility", 5);
		ChangeCharacterComplexReputation(pchar, "authority", 3);
		AddCharacterExpToSkill(pchar, "Leadership", 400);
		AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;

	case "FMQG_17":
		DelLandQuestMark(npchar);
		DelMapQuestMarkCity("baster");
		dialog.text = "Estoy escuchando. Bertrand Pinette está en tu barco, ¿supongo?";
		link.l1 = "No. Aunque tengo algo mucho mejor para ti. Lee esto.";
		link.l1.go = "FMQG_18";
		break;

	case "FMQG_18":
		RemoveItems(pchar, "letter_baker", 1);
		dialog.text = "¿Qué es esto?";
		link.l1 = "Siga leyendo, monsieur. Continuaremos después.";
		link.l1.go = "FMQG_19";
		break;

	case "FMQG_19":
		LAi_Fade("", "");
		dialog.text = "(leyendo) Ejem ... ¿Qué es esta tontería de un paciente febril?";
		link.l1 = "¿Hablas en serio? Bien, llevaré esta 'tontería' al gobernador. Creo que él mostrará un gran interés en conocer la verdad sobre la desaparición del 'Courage' y su cargamento de diamantes... ¿Por qué te has puesto tan pálido?";
		if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
			link.l1.go = "FMQG_24";
		else
			link.l1.go = "FMQG_20";
		break;

	case "FMQG_20":
		dialog.text = "Entonces, encontraste a Pinette después de todo...";
		link.l1 = "Sí. Así que le propongo un trato. Olvídese de Carlos de Milyar, Jean Deno y otros buenos caballeros. Haga eso y yo olvidaré esta carta.";
		link.l1.go = "FMQG_21";
		break;

	case "FMQG_21":
		dialog.text = "Muy bien, capitán... Estoy de acuerdo con sus términos.";
		link.l1 = "Encantador. Espero que no estés enojado conmigo, hemos terminado ahora, creo. Adiós.";
		link.l1.go = "FMQG_22";
		break;

	case "FMQG_22":
		DialogExit();
		pchar.quest.FMQG_UsurerTimeOut.over = "yes";
		pchar.questTemp.FMQG = "cave";
		bQuestDisableMapEnter = true; // закрыть карту
		pchar.GenQuest.MapClosedNoBattle = true;
		pchar.quest.FMQG_cave.win_condition.l1 = "location";
		pchar.quest.FMQG_cave.win_condition.l1.location = "Guadeloupe_Cave";
		pchar.quest.FMQG_cave.function = "FMQG_InCave";
		// заполним сундук
		pchar.GenQuestBox.Guadeloupe_Cave = true;
		pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse1 = 5;
		pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse2 = 2;
		pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse3 = 1;
		SetFunctionTimerCondition("FMQG_ClearBox", 0, 0, 3, false);
		if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
		{
			SetFunctionTimerCondition("FMQG_RemoveHunterScore", 0, 0, 1, false);
			AddQuestRecord("FMQ_Guadeloupe", "29");
			DeleteAttribute(pchar, "questTemp.FMQG.Letter");
		}
		else
			AddQuestRecord("FMQ_Guadeloupe", "25");
		break;

	case "FMQG_23":
		dialog.text = "Ja... Tienes razón, capitán.";
		link.l1 = "Tengo algo para usted. Tome esto y léalo.";
		link.l1.go = "FMQG_18";
		break;

	case "FMQG_24":
		dialog.text = "Así que encontraste a Pinette después de todo...";
		link.l1 = "Sí. Así que te propongo un trato. Restaura mi buen nombre dentro de las colonias francesas, y olvidaré esta carta.";
		link.l1.go = "FMQG_25";
		break;

	case "FMQG_25":
		dialog.text = "Pero...";
		link.l1 = "No me importa un carajo cómo lo harás. Si la caza por mi cabeza no termina mañana, el gobernador se enterará de todo.";
		link.l1.go = "FMQG_21";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

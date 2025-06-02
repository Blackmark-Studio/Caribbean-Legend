// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?", "¿En qué puedo ayudarle?"), "Intentaste hacerme una pregunta hace un rato...", "Jamás he conocido gente con tanta curiosidad en mi astillero ni en ningún otro lugar de esta ciudad.", "¿Qué pasa con todas las preguntas? Mi trabajo es construir barcos. Ocupémonos de eso.", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No tengo nada de qué hablar en este momento."), "Umph, ¿a dónde se ha ido mi memoria...?", "Mm, bueno...", "Adelante...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		// Addon 2016-1 Jason пиратскаЯ линейка
		if (CheckAttribute(pchar, "questTemp.Mtraxx"))
		{
			if (pchar.questTemp.Mtraxx == "silk_2" || pchar.questTemp.Mtraxx == "silk_3")
			{
				link.l1 = "He oído que este astillero se ocupa de mejorar la velocidad de navegación del barco. Se requiere tela de vela de seda, que es muy rara. ¿Te gustaría... hablar sobre esto?";
				link.l1.go = "mtraxx";
			}
		}
		if (CheckAttribute(npchar, "quest.upgradeship"))
		{
			link.l2 = "Soy de parte de la señorita MacArthur, respecto a...";
			link.l2.go = "helen_upgradeship";
		}

		if (CheckAttribute(npchar, "quest.upgradeship.money") && HelenCanUpgrade())
		{
			link.l2 = "¡Comience la revisión del barco!";
			link.l2.go = "helen_upgradeship_money";
		}
		break;

	// Addon 2016-1 Jason пиратскаЯ линейка
	case "mtraxx":
		dialog.text = "¿Podrías ser más claro, joven? ¿Qué exactamente te trajo aquí? Si quieres mejorar tu barco, vayamos al grano de inmediato.";
		link.l1 = "No del todo. El tipo de servicios que realizas requiere bienes que no están libremente disponibles en la tienda. Me gustaría ofrecerte el mismo tipo de esos materiales que podrías necesitar.";
		link.l1.go = "mtraxx_1";
		break;

	case "mtraxx_1":
		dialog.text = "Bueno-bueno... Hmm... ¿Sabes que solo las autoridades de esta colonia tienen permitido tratar con tales bienes estratégicos? Eres libre de proporcionarme tu propia seda para que yo pueda trabajar en la mejora de tu barco, sin embargo, venderla está estrictamente prohibido. Al igual que comprarla de mí: tales actividades serán multadas con severidad.";
		link.l1 = "Bueno, esto no es una tienda, ni tampoco una oficina de aduanas...";
		link.l1.go = "mtraxx_2";
		break;

	case "mtraxx_2":
		dialog.text = "Adquiero toda la tela de vela de seda directamente de mis clientes, o compro cantidades limitadas con un permiso especial del gobernador. Si no tienes más preguntas, por favor, déjame volver a mi trabajo.";
		link.l1 = "Hmm... Muy bien. Que tengas un buen día, maestro. ";
		link.l1.go = "mtraxx_3";
		break;

	case "mtraxx_3":
		DialogExit();
		AddQuestRecord("Roger_2", "5");
		pchar.questTemp.Mtraxx = "silk_4";
		break;

	case "helen_upgradeship":
		dialog.text = "¡Oh, lo sé! Qué suerte tiene, Capitán. ¿Se trata de una revisión completa de la nave? Nos encargaremos de todo; ¡nuestro astillero está a la altura de los de Plymouth!";
		link.l1 = "Supongo que este no será un servicio gratuito...";
		link.l1.go = "helen_upgradeship_1";
		break;

	case "helen_upgradeship_1":
		dialog.text = "Por supuesto, Capitán, tales servicios no pueden ser gratis, ¡ni siquiera para Cromwell! Sin embargo, mantengo mi palabra y solo aceptaré dinero, no tendrás que contrabandear mercancías.";
		link.l1 = "Comprensible. ¿Cuánto?";
		link.l1.go = "helen_upgradeship_2";
		break;

	case "helen_upgradeship_2":
		dialog.text = "Depende del tamaño de tu buque insignia, Capitán. Un barco de primera clase te costará cinco mil doblones, y uno de quinta clase, solo mil.";
		link.l1 = "Está bien, vendré a ti una vez que tome una decisión.";
		link.l1.go = "exit";

		npchar.quest.upgradeship.money = true;
		break;

	case "helen_upgradeship_money":
		dialog.text = "Excelente, ahora tengo todo lo que necesito. Empezaré a trabajar, entonces.";
		link.l1 = "Estoy esperando.";
		link.l1.go = "helen_upgradeship_money_1";

		iTemp = GetCharacterShipType(pchar);
		sld = GetRealShip(iTemp);
		iTemp = (6 - sti(sld.class)) * 1000;
		RemoveDublonsFromPCharTotal(iTemp);
		break;

	case "helen_upgradeship_money_1":
		AddTimeToCurrent(6, 30);
		dialog.text = "... Supongo que eso es todo... La calidad está garantizada.";
		link.l1 = "¡Gracias! Lo revisaré.";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("HelenUpgradeShip2");
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

bool HelenCanUpgrade()
{
	int shipIndex = GetCharacterShipType(pchar);
	if (shipIndex == SHIP_NOTUSED)
	{
		return false;
	}

	sld = GetRealShip(shipIndex);
	if (sti(sld.class) == 6)
	{
		return false;
	}

	int cost = (6 - sti(sld.class)) * 1000;
	return (PCharDublonsTotal() >= cost);
}

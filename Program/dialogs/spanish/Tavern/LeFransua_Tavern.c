// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?", "¿Cómo puedo ayudarle, " + GetAddress_Form(NPChar) + "?"), "Intentaste hacerme una pregunta no hace mucho, " + GetAddress_Form(NPChar) + "...", "Durante todo este día, esta es la tercera vez que hablas de alguna pregunta...", "Más preguntas, supongo?", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No tengo nada de qué hablar en este momento."), "Umph, ¿dónde se ha ido mi memoria...?", "Sí, realmente es la tercera vez...", "No, ¿qué preguntas?...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		// Jason, Бремя гасконца
		if (CheckAttribute(PChar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "hire" && !CheckAttribute(npchar, "quest.storehelper"))
		{
			link.l1 = "Escucha, " + npchar.name + ", he venido a ti por un asunto inusual. Necesito encontrar a un hombre que desee una vida tranquila y pacífica en la bahía como asistente de comerciante, en una tienda de Saint-Pierre. El salario es bueno y tendrá un techo sobre su cabeza asegurado. ¿Podrías sugerirme a quién podría acudir?";
			link.l1.go = "storehelper";
		}
		if (CheckAttribute(PChar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "seabattle" && !CheckAttribute(npchar, "quest.seabattle") && pchar.location.from_sea == "LeFransua_town")
		{
			link.l1 = "Estoy aquí por los barriles de vino que estás a punto de cargar en mi barco para su entrega a Guadalupe...";
			link.l1.go = "seabattle";
		}
		// Бремя гасконца
		// Jason, Португалец
		if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalLeFransua" && !CheckAttribute(npchar, "quest.portugal") && Pchar.location.from_sea == "LeFransua_town")
		{
			link.l1 = "Sabes, " + npchar.name + ", estoy buscando a un amigo mío. Se suponía que llegaría aquí, y se sentía mal. Tal vez sus amigos lo ayudaron...";
			link.l1.go = "Portugal";
		}
		// Португалец
		break;

	case "storehelper":
		dialog.text = "Mm.. Tenemos a varias personas aquí que quisieran dejar de ser marineros y llevar la vida de un terrícola. Podría ayudarte, pero te digo de una vez: no será gratis.";
		link.l1 = "¡Je! ¿Y cuánto quieres?";
		link.l1.go = "storehelper_1";
		break;

	case "storehelper_1":
		dialog.text = "Mil piezas de a ocho. Y no tendrás que hacer nada, en una hora tus candidatos para el trabajo estarán en mi taberna, múltiples candidatos. Podrás hablar con ellos y seleccionar al que te atraiga más que los demás.";
		if (sti(Pchar.money) >= 1000)
		{
			link.l1 = "Ahh... Está bien, aquí, ¡toma mil!";
			link.l1.go = "storehelper_2";
		}
		link.l2 = "¡Lo siento, pero no tengo tanto dinero!";
		link.l2.go = "storehelper_exit";
		break;

	case "storehelper_2":
		AddMoneyToCharacter(pchar, -1000);
		dialog.text = "No te preocupes, camarada. Recuperarás la mitad de esta cantidad del candidato. Le diré que ese es el costo de tus servicios, je je... No darán más de quinientos. Pasa por mi taberna en una hora, para entonces habré encontrado a las personas que necesitas y estarán aquí esperándote.";
		link.l1 = "Bien. Volveré en una hora, " + npchar.name + ".";
		link.l1.go = "storehelper_3";
		npchar.quest.storehelper = "true";
		DelLandQuestMark(npchar);
		break;

	case "storehelper_3":
		DialogExit();
		SetLaunchFrameFormParam("Una hora más tarde...", "", 0, 5);
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 1, 0); // крутим время
		RecalculateJumpTable();
		Storehelper_hire("");
		break;

	case "storehelper_exit":
		dialog.text = "Siento que tú tampoco tengas ese tipo de dinero. Pero tú mismo sabes, asuntos como esos no se resuelven solo con un 'gracias'. Así que...";
		link.l1 = "Entiendo. Pero realmente no tengo el dinero. Está bien, adiós...";
		link.l1.go = "exit";
		// pchar.quest.storehelper.over = "yes";
		// AddTimeToCurrent(2,0);
		// DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
		// CloseQuestHeader("SharlieA");
		break;

	case "seabattle":
		DelLandQuestMark(npchar);
		dialog.text = "¿De qué estás hablando, camarada? ¿De qué vino hablas?";
		link.l1 = "Me ha enviado un hombre llamado Walter Catcher. Dijo que necesitabas un barco para trasladar un cargamento de vino a Guadalupe por diez mil pesos. Y que necesitas exactamente mi barco para este trabajo...";
		link.l1.go = "seabattle_1";
		npchar.quest.seabattle = "true";
		break;

	case "seabattle_1":
		dialog.text = "Escucha, camarada, no trato con vino, no necesito tus servicios, y no conozco a ningún Walter Catcher.";
		link.l1 = "¡Vaya sorpresa! Entonces, ese Cazador no fue enviado por ti en absoluto... Entonces, ¿de qué se trata toda esta comedia?";
		link.l1.go = "seabattle_2";
		break;

	case "seabattle_2":
		dialog.text = "¡Je! Bueno, esto es o un error, o una broma de mal gusto o...";
		link.l1 = "¿O qué?";
		link.l1.go = "seabattle_3";
		break;

	case "seabattle_3":
		dialog.text = "¿No lo entiendes por ti mismo? Alguien necesitaba atraerte a Le Francois, para qué, no lo sé. En tu lugar, me apresuraría a salir de aquí mientras sea lo más cuidadoso posible. Esto huele a asunto turbio, camarada...";
		link.l1 = "Supongo que tienes razón. No me gustaba la cara de ese Catcher. Está bien, seguiré tu consejo. ¡Adiós, Cesar!";
		link.l1.go = "seabattle_4";
		break;

	case "seabattle_4":
		DialogExit();
		AddQuestRecord("Sharlie", "16");
		pchar.quest.seabattle.win_condition.l1 = "location";
		pchar.quest.seabattle.win_condition.l1.location = "Martinique";
		pchar.quest.seabattle.function = "SharlieSeabattle_ship";

		pchar.quest.NewGameTip4.win_condition.l1 = "location";
		pchar.quest.NewGameTip4.win_condition.l1.location = "LeFransua_town";
		pchar.quest.NewGameTip4.function = "ShowNewGameTip";
		pchar.quest.NewGameTip4.text = "¡Llega tu primera batalla naval! ¡Guarda tu partida!";
		break;

	case "Portugal":
		dialog.text = "Sí, tu amigo llegó aquí, capitán. Llegó ayer y alquiló una habitación arriba. Sus compañeros de tripulación también están aquí, je-je... Están sentados allí. ¡Pregúntales!";
		link.l1 = "...";
		link.l1.go = "Portugal_1";
		break;

	case "Portugal_1":
		DialogExit();
		AddDialogExitQuestFunction("Portugal_enterPirates");
		npchar.quest.portugal = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

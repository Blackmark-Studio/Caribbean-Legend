// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?", "¿Cómo puedo ayudarle?"), "Intentaste hacerme esa pregunta no hace mucho...", "Sí, déjame adivinar... ¿Otra vez dando vueltas en círculos?", "Escucha, yo manejo las finanzas aquí, no respondo preguntas...", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No tengo nada de qué hablar en este momento."), "Umph, ¿dónde se ha ido mi memoria...?", "Lo has adivinado, lo siento...", "Entiendo...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";

		// --> Sinistra Длинные тени старых грехов
		if (CheckAttribute(pchar, "questTemp.DTSG_depozit"))
		{
			link.l1 = "Dime, ¿el coronel te visitó? Dijo que tienes una recompensa preparada para mí.";
			link.l1.go = "DTSG_depozit_1";
		}
		// <-- Длинные тени старых грехов
		break;

	// --> Sinistra Длинные тени старых грехов
	case "DTSG_depozit_1":
		dialog.text = "¿Qué coronel?";
		link.l1 = "Thomas Lynch.";
		link.l1.go = "DTSG_depozit_2";
		break;

	case "DTSG_depozit_2":
		dialog.text = "¡Habla en voz baja! Conozco al hombre. Sí, pasó por aquí. Tu recompensa te está esperando, capitán.";
		link.l1 = "¿Y cuánto hay?";
		link.l1.go = "DTSG_depozit_3";
		break;

	case "DTSG_depozit_3":
		dialog.text = "Exactamente diez mil en oro. Ni un solo peso, todo oro.";
		link.l1 = "Al menos no son treinta piezas de plata...";
		link.l1.go = "DTSG_depozit_4";
		AddItems(pchar, "chest", 70);
		Log_Info("¡Has recibido 70 cofres!");
		PlaySound("interface\important_item.wav");
		break;

	case "DTSG_depozit_4":
		dialog.text = "¿Qué fue eso?";
		link.l1 = "Oh, nada... Gracias. Adiós.";
		link.l1.go = "exit";
		DeleteAttribute(pchar, "questTemp.DTSG_depozit");
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

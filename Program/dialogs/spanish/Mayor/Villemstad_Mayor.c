// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué quieres? Pregunta lo que desees.", "Te escucho, ¿cuál es la pregunta?"), "Esta es la segunda vez que intentas preguntar...", "Esta es la tercera vez que intentas preguntar...", "¿Cuándo va a terminar esto? ¡Soy un hombre ocupado, trabajando en asuntos de la colonia y todavía me estás molestando!", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple(" He cambiado de opinión, lo siento.", "Ahora no. Lugar y momento equivocados."), "Es cierto, no tengo nada que decir ahora, lo siento.", "Preguntaré, más tarde.", "Lo siento, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		// Португалец
		if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad"))
		{
			link.l1 = "Yo sé que la Compañía Holandesa de las Indias Occidentales ha asignado un precio por la cabeza de un cierto pirata, Bartolomeo el Portugués. Pude capturarlo. Actualmente está en mi bodega de carga y estoy listo para entregarlo a las autoridades.";
			link.l1.go = "Portugeze";
		}
		break;

	case "Cupture_after":
		dialog.text = RandPhraseSimple("Ya te has llevado todo. ¿Qué más quieres?", "¿Queda algo que no hayas agarrado?");
		link.l1 = RandPhraseSimple("Solo echando un vistazo...", "Solo comprobando, podría haber olvidado tomar algo...");
		link.l1.go = "exit";
		NextDiag.TempNode = "Cupture_after";
		break;

	// Португалец
	case "Portugeze":
		dialog.text = "¿Bart el Portugués?! ¿Lo tienes, vivo?!";
		link.l1 = "Sé que no te sirve de nada muerto. Está vivo y, ¡malditos sean los dioses!, tuve que contenerme para mantenerlo así.";
		link.l1.go = "Portugeze_1";
		break;

	case "Portugeze_1":
		dialog.text = "¡Muy excelente! Ahora nos dirá todo... Mynheer, prepare al prisionero para el traslado. Enviaremos una barca militar a su barco de inmediato. ";
		link.l1 = "Primero me gustaría hablar sobre mi recompensa, señor, si no le importa.";
		link.l1.go = "Portugeze_2";
		break;

	case "Portugeze_2":
		dialog.text = "No se preocupe por su recompensa, señor. La recibirá. Hemos asignado un precio por la cabeza de Bartolomeo el Portugués: mil quinientos doblones. ¡Teniente! ¡Traiga al capitán su recompensa!";
		link.l1 = "Mm... Hugo me dijo que eran dos mil doblones... Está bien entonces.";
		link.l1.go = "Portugeze_3";
		break;

	case "Portugeze_3":
		TakeNItems(pchar, "gold_dublon", 1500);
		Log_Info("Has recibido 1500 doblones");
		PlaySound("interface\important_item.wav");
		dialog.text = "Y ahora, señor, ¿sería tan amable de transferir al portugués a la Compañía? Estamos ansiosos por hablar con él.";
		link.l1 = "Claro, señor, envíe la barca a mi barco.";
		link.l1.go = "Portugeze_4";
		break;

	case "Portugeze_4":
		DialogExit();
		DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
		DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

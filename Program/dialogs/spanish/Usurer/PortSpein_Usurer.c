// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?", "¿Cómo puedo ayudarle?"), "Intentaste hacerme esa pregunta no hace mucho...", "Sí, déjame adivinar... ¿Otra vez dando vueltas en círculos?", "Escucha, yo manejo las finanzas aquí, no respondo preguntas...", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No tengo nada de qué hablar en este momento."), "Umph, ¿dónde se ha ido mi memoria...?", "Lo has adivinado, lo siento...", "Entiendo...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		// Цена чахотки
		if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
		{
			link.l1 = "Escucha, ¿te dice algo el nombre 'Juan'?";
			link.l1.go = "Consumption";
		}
		break;

	// Цена чахотки
	case "Consumption":
		dialog.text = "No lo sé. Y no quiero saberlo. Tampoco te recomiendo que lo sepas. Y ahora, tendrás que disculparme, pero tengo asuntos a los que debo regresar. Supongo que tú también tienes asuntos que atender, ¿no es así? Así que vete y ocúpate de ellos.";
		link.l1 = "Está bien, de acuerdo. Perdón por molestarte...";
		link.l1.go = "exit";
		pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan) + 1;
		if (sti(pchar.questTemp.Consumption.AskJuan) == 3)
		{
			pchar.quest.Consumption2.win_condition.l1 = "location";
			pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
			pchar.quest.Consumption2.function = "Consumption_CreateSergio";
		}
		npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?", "¿Cómo puedo ayudarte?"), "Intentaste hacerme una pregunta hace un rato...", "Jamás he conocido a personas con tanta curiosidad en mi astillero o en cualquier otro lugar de esta ciudad.", "¿Qué pasa con todas las preguntas? Mi trabajo es construir barcos. Ocupémonos de eso.", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No tengo nada de qué hablar en este momento."), "Umph, ¿a dónde se ha ido mi memoria...?", "Hum, bueno...", "Adelante...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		break;

	case "helendrinking_buy_rainbow":
		dialog.text = "... una elección digna, señor. Entonces, ¿tenemos un trato?";
		link.l1 = "¡S-sí! ¡Salud! Envuélvelo y envíalo al muelle. Y hazlo rápido, una dama me espera en la calle.";
		link.l1.go = "helendrinking_buy_rainbow_1";
		locCameraFromToPos(0.36, 1.86, 1.15, true, 2.06, -0.20, -4.38);
		break;

	case "helendrinking_buy_rainbow_1":
		dialog.text = "Cincuenta mil monedas de plata por todo, señor.";
		if (sti(pchar.money) >= 55000)
		{
			link.l1 = "¿C-cuánto dijiste? ¿C-cincuenta mil? ¡Bueno, cuéntalo tú mismo! Y toma otros cinco mil como propina. ¡Vamos!";
			link.l1.go = "helendrinking_buy_rainbow_yes";
		}

		link.l2 = "No-no, ¡puede que sea un tipo rico, hic! ...pero no lo aceptaré por tanto. ¡No, señor! Adiós, barquero.";
		link.l2.go = "helendrinking_buy_rainbow_no";
		break;

	case "helendrinking_buy_rainbow_yes":
		dialog.text = "Gracias, señor. ¡Que te sirva bien!";
		link.l1 = "";
		link.l1.go = "exit";

		NextDiag.TempNode = "First time";

		AddMoneyToCharacter(pchar, -55000);
		pchar.questTemp.HelenDrinking.BoughtRainbow = true;

		AddDialogExitQuestFunction("HelenDrinking_GoToPerlas");
		break;

	case "helendrinking_buy_rainbow_no":
		dialog.text = "Sí, lárgate, ricachón. Cerramos hace tres horas.";
		link.l1 = "";
		link.l1.go = "exit";

		NextDiag.TempNode = "First time";

		AddDialogExitQuestFunction("HelenDrinking_GoToPerlas");
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

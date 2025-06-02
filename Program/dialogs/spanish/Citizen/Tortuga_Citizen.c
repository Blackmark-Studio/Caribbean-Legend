// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = RandPhraseSimple("¿Qué tipo de preguntas?", "¿Qué quieres?");
		link.l1 = RandPhraseSimple("He cambiado de opinión.", "No tengo nada que decirte.");
		link.l1.go = "exit";

		// Rebbebion, "Путеводная звезда"
		if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && npchar.sex == "man")
		{
			link.l1 = "¿No conocerías a cierto Joep van der Vink, verdad?";
			link.l1.go = "PZ1";
		}
		break;

	case "info":
		// заменить на описание неких НПС, по квестам
		dialog.text = "¿Crees que trabajo para el servicio secreto de " + NationNameGenitive(sti(NPChar.nation)) + "?";
		link.l1 = "Bueno... no. Adiós entonces.";
		link.l1.go = "exit";
		link.l2 = "¿Alguna otra pregunta, entonces?";
		link.l2.go = "new question";
		break;

	case "town":
		// заменить на описание как пройти, по квестам
		dialog.text = "¿Parezco una oficina de investigaciones? No sé, no sé nada.";

		link.l1 = "¡Eres un cabeza de chorlito! Vete.";
		link.l1.go = "exit";
		link.l2 = "¿Alguna otra pregunta, entonces?";
		link.l2.go = "new question";
		break;

	case "PZ1":
		dialog.text = "Bueno, no lo conozco personalmente, pero lo veo aquí de vez en cuando. ¿Por qué preguntas?";
		link.l1 = "Me han asignado entregar un paquete personalmente. Pero nadie quiere hablar de él, y no sé por qué. ¿Tú lo sabes? ¿Es un hombre malo? Apreciaría tu opinión honesta.";
		link.l1.go = "PZ2";
		break;

	case "PZ2":
		dialog.text = "De nuevo, no nos conocemos personalmente, así que no sé casi nada. Pero tiene un amigo cercano en la ciudad, y a menudo se les ve juntos. Ve con él... él decidirá si contarte más o no. Su compañero se llama Rober Martene.";
		link.l1 = "Rober Martene, dices... ¿Y quién es él? ¿Dónde puedo encontrarlo?";
		link.l1.go = "PZ3";
		break;

	case "PZ3":
		dialog.text = "Varios lugares, pero ahora mismo está en nuestro faro, reparando su galeón después de una terrible tormenta. Se llama el 'Voltigeur'.";
		link.l1 = "¡Muchas gracias! No tienes idea de cuánto me has ayudado.";
		link.l1.go = "Exit";
		AddDialogExitQuest("PZ_CreateRobertMartin");
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

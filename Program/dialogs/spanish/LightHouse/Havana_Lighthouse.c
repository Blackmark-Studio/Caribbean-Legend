// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué quieres?", "¿Qué te gustaría saber?"), "¿Qué necesitas, " + GetAddress_Form(NPChar) + "?", "Esa es la tercera vez que intentas preguntarme...", "¡He tenido suficiente de ti, piérdete!", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Lo siento, he cambiado de opinión.", "Es nada, disculpas."), "Olvidé, mis disculpas...", "La tercera es la vencida, ¿eh? Disculpa...", "¡Lo siento, lo siento! Me iré entonces...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		// калеуче
		if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
		{
			link.l1 = "Escucha, ¿ha estado aquí un hombre llamado Joachim Merriman? Es un señor portugués de mediana edad, con bigote, barba imperial y ojos penetrantes. ¿Quizás desembarcó en alguna playa o cerca del faro? ¿Has visto a alguien así?";
			link.l1.go = "merriman";
		}
		break;

	// калеуче
	case "merriman":
		dialog.text = "No, camarada, no he visto a nadie como él. Me habría dado cuenta, sí.";
		link.l1 = "Ya veo, qué lástima. Gracias por tu tiempo, continuaré mi búsqueda entonces.";
		link.l1.go = "exit";
		npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes para un soldado?", "El soldado tiene toda su vida planeada, guardia, ajetreo... ¿Cómo puedo ayudarte, " + GetAddress_Form(NPChar) + "?"), "No deberías molestar a un soldado con preguntas estúpidas, " + GetAddress_Form(NPChar) + "...", "Esta es la tercera vez hoy que intentas hacerme una pregunta...", "La suerte de un soldado no es fácil, y ahora tú, escoria, me estás volviendo loco...", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No tengo nada de qué hablar en este momento."), "Entendido...", "Sí, tienes razón, ya es la tercera vez...", "Lo siento...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

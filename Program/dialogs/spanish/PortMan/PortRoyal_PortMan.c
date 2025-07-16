// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué tipo de preguntas?", "¿Qué quieres, " + GetAddress_Form(NPChar) + "?"), "Ya has intentado hacerme una pregunta " + GetAddress_Form(NPChar) + "...", "Es la tercera vez que me interrumpes hoy...", "Mira, si no tienes nada que decirme sobre los asuntos del puerto, entonces no me molestes con tus preguntas.", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión.", "No tengo nada de qué hablar."), "Olvídalo.", "En efecto, ya es la tercera vez...", "Lo siento, pero no estoy interesado en los asuntos del puerto por ahora.", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";

		if (pchar.questTemp.Slavetrader == "FindRatJamaica")
		{
			link.l1 = "Buen día. ¿Se ha registrado aquí el Capitán François Gontier? Zarpaba de Portobello en una corbeta llamada '" + pchar.questTemp.Slavetrader.ShipName + "'. ";
			link.l1.go = "Jamaica_ratPP_1";
		}

		break;

	case "Jamaica_ratPP_1":
		dialog.text = NPCStringReactionRepeat("No, no lo ha hecho. Y la corbeta '" + pchar.questTemp.Slavetrader.ShipName + "no ha sido visto en Port-Royal.", "Ya has preguntado sobre esto y te he respondido.", "Te digo que ya has preguntado por ese tal Gontier.", "¡Por favor, no me distraigas de mi trabajo!", "block", 0, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Gracias. Seguiré buscando.", "Mm, bueno...", "Sí, realmente he preguntado ...", "Perdón, " + npchar.name + "...", npchar, Dialog.CurrentNode);
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

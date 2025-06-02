// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?", "¿Cómo puedo ayudarle?"), "Intentaste hacerme esa pregunta no hace mucho...", "Sí, déjame adivinar... ¿Otra vez dando vueltas en círculos?", "Escucha, yo manejo las finanzas aquí, no respondo preguntas...", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No tengo nada de qué hablar en este momento."), "Umph, ¿dónde se ha ido mi memoria...?", "Lo has adivinado, lo siento...", "Entiendo...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		break;

	// Реакция ростовщика Панамы на репутацию ГГ или на разграбление Картахены по сюжету
	case "Panama_Deposit_NoReputation":
		dialog.text = "Así es... Un hombre de honor que es amado por los súbditos del Rey nunca será rechazado por mi banco, sin importar su nacionalidad.";
		link.l1 = "Entiendo. Adiós.";
		link.l1.go = "exit";
		break;

	case "Panama_Deposit_Cartahena":
		dialog.text = "Pero mi hija y mi suegro lo tuvieron, desafortunadamente. Vivían en Cartagena. Márchate, " + GetAddress_Form(NPChar) + ". No eres bienvenido aquí.";
		if (pchar.questTemp.Mtraxx.Retribution.Choice == "good")
		{
			link.l1 = "Perdóname. Adiós.";
			link.l1.go = "exit";
		}
		else
		{
			link.l1 = "Como quieras. Adiós.";
			link.l1.go = "exit";
		}
		NextDiag.TempNode = "NeHochuRazgovarivat";
		break;

	case "Panama_Deposit_SgorelVklad":
		dialog.text = "Los fondos fueron incautados por la Corona para ayudar a las víctimas del saqueo de la ciudad de Cartagena. No puedo ayudarte. ¡Voy a pedirte que abandones mi banco inmediatamente antes de llamar a los guardias!";
		link.l1 = "Vas a lamentar esto...";
		link.l1.go = "exit";
		NextDiag.TempNode = "NeHochuRazgovarivat";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

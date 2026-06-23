// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = RandPhraseSimple("¿Qué tipo de preguntas?", "¿Qué quieres?");
		link.l1 = RandPhraseSimple("He cambiado de opinión.", "No tengo nada que decirte.");
		link.l1.go = "exit";
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince" && !CheckAttribute(npchar, "quest.Guardoftruth"))
		{
			link.l1 = "Dime, " + GetAddress_FormToNPC(NPChar) + "¿No estuvo aquí hace poco el galeón 'Santa Margarita'? ¿Quizás como barco premio de un corsario?";
			link.l1.go = "guardoftruth";
		}
		break;

	case "info":
		// заменить на описание неких НПС, по квестам
		dialog.text = "¿Crees que trabajo para el servicio secreto de " + NationNameGenitive(int(NPChar.nation)) + "?";
		link.l1 = "Bueno... no. Adiós entonces.";
		link.l1.go = "exit";
		link.l2 = "¿Alguna otra pregunta, entonces?";
		link.l2.go = "new question";
		break;

	case "town":
		// заменить на описание как пройти, по квестам
		dialog.text = "¿Tengo pinta de ser de la oficina de investigaciones? No sé, no sé nada.";

		link.l1 = "¡Eres un cabeza hueca! Lárgate.";
		link.l1.go = "exit";
		link.l2 = "¿Alguna otra pregunta, entonces?";
		link.l2.go = "new question";
		break;

	case "guardoftruth":
		dialog.text = LinkRandPhrase("No, no recuerdo ningún galeón con ese nombre. Rara vez vemos barcos tan grandes por aquí.", "¿Qué? ¿Un galeón? ¿Aquí? No tengo ni idea.", "No señor, ese barco no ha atracado aquí últimamente, al menos no recuerdo que haya pasado.");
		link.l1 = LinkRandPhrase("Está bien...", "Muy bien...", "Ya veo, lástima...");
		link.l1.go = "exit";
		npchar.quest.Guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = RandPhraseSimple("¿Qué preguntas son esas?", "¿Qué quieres?");
		link.l1 = RandPhraseSimple("He cambiado de opinión.", "No tengo nada que decirte.");
		link.l1.go = "exit";
		break;

	case "info":
		dialog.text = LinkRandPhrase("¿En quién estás interesado?", "¿A quién te refieres?", "Bueno, ¿quién es?");
		link.l1 = "Quiero saber más sobre Fadey el Moscovita.";
		link.l1.go = "fadey";
		link.l2 = "Nadie, no importa.";
		link.l2.go = "new question";
		break;

	case "town":
		dialog.text = LinkRandPhrase("¿A dónde quieres ir?", "¿Qué estás buscando?", "¿Qué necesitas exactamente?");
		link.l1 = "¿Dónde está la casa de Fadey?";
		link.l1.go = "fadey_house";
		link.l2 = "Hablemos de otra cosa...";
		link.l2.go = "new question";
		break;

	case "fadey":
		dialog.text = RandPhraseSimple("Ah, un hombre importante. Es dueño de la fábrica, y está cercano a la alta sociedad de Basse-Terre. Tiene un acento fuerte y le gusta mucho beber... pero nunca se emborracha.", "Es un pez gordo y amigo del gobernador. Fadey posee una fábrica. Vino de un país del norte muy, muy lejos de aquí... Ni siquiera sé el nombre de ese lugar. Tiene manos fuertes, y es capaz de beber un barril entero de ron sin emborracharse.");
		link.l1 = "Muchas gracias.";
		link.l1.go = "exit";
		break;

	case "fadey_house":
		dialog.text = RandPhraseSimple("Ve derecho desde el muelle hasta que veas la plaza, la casa a la izquierda es la cada de Fadey.", "Ve al muelle a través de la plaza desde la residencia del gobernador, la casa a la derecha es el hogar de Fadey.");
		link.l1 = "Te lo agradezco.";
		link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

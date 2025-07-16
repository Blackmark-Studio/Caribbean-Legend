// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = RandPhraseSimple("¿Qué tipo de preguntas?", "¿Qué quieres?");
		link.l1 = RandPhraseSimple("He cambiado de opinión.", "No tengo nada que decirte.");
		link.l1.go = "exit";
		break;

	case "info":
		dialog.text = LinkRandPhrase("¿En quién estás interesado?", "¿A quién te refieres?", "Bueno, ¿quién es?");
		if (CheckAttribute(pchar, "questTemp.Saga"))
		{
			link.l1 = "Quiero saber más sobre Jan Svenson.";
			link.l1.go = "svenson";
		}
		link.l2 = "Cambiemos de tema...";
		link.l2.go = "new question";
		break;

	case "town":
		dialog.text = LinkRandPhrase("¿A dónde quieres ir?", "¿Qué estás buscando?", "¿Qué necesitas exactamente?");
		if (CheckAttribute(pchar, "questTemp.Saga"))
		{
			link.l1 = "¿Dónde está la casa de Jan Svenson?";
			link.l1.go = "svenson_house";
		}
		link.l2 = "Cambiemos de tema...";
		link.l2.go = "new question";
		break;

	case "svenson":
		dialog.text = RandPhraseSimple("Oh, nuestro Jan Svenson es una persona muy importante. En el pasado fue el pirata más audaz de Tierra Firme Occidental, y aún ahora no ha comenzado a oxidarse, ¡ja! Pero esos días han pasado, ya no está activo como solía estar. Posee una mansión y vive allí con su joven esposa, y siempre es un invitado bienvenido en la residencia del gobernador. Muchos invitados vienen a ver a Jan, piratas, la mayoría.", "¡Jan Svenson es una leyenda de Tierra Firme Occidental! 'Forest Devil', así lo llamaban los españoles cuando los expulsaba de aquí. Solía ser un corsario famoso, pero ahora es un ciudadano respetado de nuestra colonia. Aunque todavía hace algunos 'negocios', pero ya no con sus propias manos. Rara vez deja su casa desde que se casó con una joven belleza.");
		link.l1 = "Te lo agradezco.";
		link.l1.go = "exit";
		break;

	case "svenson_house":
		dialog.text = RandPhraseSimple("Ve derecho desde el muelle hasta que veas la plaza, la casa a la derecha cerca de la fuente es la casa de Svenson.", "Ve al muelle a través de la plaza desde la residencia del gobernador, la casa a la izquierda cerca de la fuente es la casa de Svenson.");
		link.l1 = "Te lo agradezco.";
		link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

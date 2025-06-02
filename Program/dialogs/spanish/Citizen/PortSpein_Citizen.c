// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = RandPhraseSimple("¿Qué tipo de preguntas?", "¿Qué quieres?");
		link.l1 = RandPhraseSimple("He cambiado de opinión.", "No tengo nada que decirte.");
		link.l1.go = "exit";
		// Цена чахотки
		if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
		{
			link.l1 = "Dime, ¿te suena el nombre 'Juan'?";
			link.l1.go = "Consumption";
		}
		if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
		{
			link.l1 = "Escucha, compañero, una fragata bajo el mando de Miguel Dichoso atracó en el puerto aquí, en abril de 1654. Desapareció ese día. ¿Recuerdas algo al respecto?";
			link.l1.go = "guardoftruth";
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
		dialog.text = "¿Acaso parezco la oficina de investigaciones? No sé, no sé nada.";

		link.l1 = "¡Eres un cabeza de chorlito! Vete.";
		link.l1.go = "exit";
		link.l2 = "¿Alguna otra pregunta, entonces?";
		link.l2.go = "new question";
		break;

	// Цена чахотки
	case "Consumption":
		dialog.text = "¿Me estás tomando el pelo? ¡Hay dos docenas de Juanes en cada colonia!";
		link.l1 = "Ya veo. Disculpa por molestarte...";
		link.l1.go = "exit";
		npchar.quest.Consumption = "true";
		break;

	// Страж Истины
	case "guardoftruth":
		dialog.text = LinkRandPhrase("¡Vamos, capitán! ¿Crees que recuerdo esas cosas?", "Perdóname, señor, no puedo ayudarte con eso.", "Señor, ¿de verdad cree que recuerdo tales tonterías? Ya tengo suficientes problemas.");
		link.l1 = LinkRandPhrase("Ya veo. Disculpa por molestarte...", "Qué lástima, adiós.", "Está bien, adiós...");
		link.l1.go = "exit";
		npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

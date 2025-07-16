// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = RandPhraseSimple("¿Qué tipo de preguntas?", "¿Qué quieres?");
		link.l1 = RandPhraseSimple("He cambiado de opinión.", "No tengo nada que decirte.");
		link.l1.go = "exit";
		// Jason, суп из черепахи
		if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin") && CheckAttribute(PChar, "questTemp.Terrapin.SJ_count"))
		{
			link.l1 = "Estoy buscando al señor Jones. ¿Lo conoces?";
			link.l1.go = "terrapin";
		}
		break;

	case "terrapin":
		if (sti(pchar.questTemp.Terrapin.SJ_count) == 5 || rand(9) == 1) // 10% или числом
		{
			dialog.text = "Hay muchos Jones aquí. El más renombrado que conozco es un ayudante de campo bajo el mando del coronel Fox, Benjamin Jones. Usualmente recibe a los visitantes en el cuartel del regimiento.";
			link.l1 = "¿Tiene una hermana llamada Molly?";
			link.l1.go = "terrapin_yes";
		}
		else
		{
			dialog.text = LinkRandPhrase("¿Cuál Jones necesitas? Conozco al menos dos docenas de ellos...", "Tenemos demasiados Jones aquí. Necesitas ser más específico.", "Hay muchos Jones aquí, así como Johnsons o Jacksons. Necesitas ser más específico, ¿eh?");
			link.l1 = "Tiene una hermana adulta llamada Molly. Me han dicho que es una rara belleza.";
			link.l1.go = "terrapin_no";
		}
		npchar.quest.terrapin = "true";
		break;

	case "terrapin_no":
		dialog.text = RandPhraseSimple(LinkRandPhrase("Hum, me temo que no puedo ayudarte con eso.", "No, no lo conozco.", "¡Bah! Si la Molly Jones que conozco es una rara belleza, entonces el Coronel Fox es un cura de parroquia."), LinkRandPhrase("Conozco a algunas Molly Jones. Una de ellas tiene hermano, pero... ella no es la que estás buscando. Solo un hombre que ha vivido entre simios la llamaría 'una rara belleza'.", "Lo siento, pero todos los Jones que conozco no tienen hermanas.", "Lo siento, no puedo ayudarte. Pregunta a alguien más."));
		link.l1 = "Ya veo. Perdón por la molestia.";
		link.l1.go = "exit";
		pchar.questTemp.Terrapin.SJ_count = sti(pchar.questTemp.Terrapin.SJ_count) + 1;
		break;

	case "terrapin_yes":
		dialog.text = "Sí, pero estaría mejor como su hermano. Esta moza probablemente no encontrará un pretendiente debido a su feo rostro.";
		link.l1 = "Entiendo, gracias.";
		link.l1.go = "terrapin_yes_1";
		break;

	case "terrapin_yes_1":
		DialogExit();
		AddQuestRecord("Terrapin", "2");
		pchar.questTemp.Terrapin.Benjamin = true;
		DeleteAttribute(pchar, "questTemp.Terrapin.SJ_count");
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
		dialog.text = "¿Tengo pinta de ser la oficina de investigación? No lo sé, no sé nada.";

		link.l1 = "¡Eres un cabeza de chorlito! Márchate.";
		link.l1.go = "exit";
		link.l2 = "¿Alguna otra pregunta, entonces?";
		link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas son esas?", "¿Qué quieres, " + GetAddress_Form(NPChar) + "?"), "Ya has intentado hacerme una pregunta " + GetAddress_Form(NPChar) + "...", "Has estado hablando de alguna pregunta por tercera vez hoy...", "Mira, si no tienes nada que decirme sobre los asuntos del puerto, entonces no me molestes con tus preguntas.", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión.", "No tengo nada de qué hablar."), "No importa.", "De hecho, ya es la tercera vez...", "Lo siento, pero no estoy interesado en los asuntos del puerto por ahora.", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		// Цена чахотки
		if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
		{
			link.l1 = "Dime, ¿el nombre 'Juan' significa algo para ti?";
			link.l1.go = "Consumption";
		}
		if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
		{
			link.l1 = "Señor, hubo una fragata aquí bajo el mando de Miguel Dichoso en abril de 1654. Luego desapareció. ¿No recuerda nada al respecto? Quizás, Dichoso estuvo aquí y registró su barco...";
			link.l1.go = "guardoftruth";
		}
		break;

	// Цена чахотки
	case "Consumption":
		dialog.text = "¿Juan? ¿Eso es todo? Señor, ¿está usted borracho o me está gastando una broma estúpida? ¿Puede recordar un apellido o al menos, el nombre de su barco? Esta es una colonia española, por el amor de Dios. ¿Sabe cuántos Juans tenemos por aquí? No podré ayudarle sin más detalles.";
		link.l1 = "Ya veo. Lamento molestarte...";
		link.l1.go = "exit";
		pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan) + 1;
		if (sti(pchar.questTemp.Consumption.AskJuan) == 3)
		{
			pchar.quest.Consumption2.win_condition.l1 = "location";
			pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
			pchar.quest.Consumption2.function = "Consumption_CreateSergio";
		}
		npchar.quest.Consumption = "true";
		break;

	case "guardoftruth":
		dialog.text = "Veamos mis notas... ¡ah, sí! Sí, el Capitán Miguel Dichoso estuvo aquí en abril de 1654, en la fragata 'Santa-Quiteria'. Se registró como proveniente de la colonia San-Andrés, Providencia. Se dirigía a Cádiz, España. Zarpó el 14 de abril de 1654. Eso es todo lo que tengo.";
		link.l1 = "¿Navegando hacia Europa? Ya veo. ¡Gracias por eso!";
		link.l1.go = "exit";
		npchar.quest.guardoftruth = "true";
		AddQuestRecord("Guardoftruth", "39");
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

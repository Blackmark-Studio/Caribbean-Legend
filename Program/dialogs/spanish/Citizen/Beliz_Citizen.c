// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = RandPhraseSimple("¿Qué tipo de preguntas?", "¿Qué quieres?");
		link.l1 = RandPhraseSimple("He cambiado de opinión.", "No tengo nada que decirte.");
		link.l1.go = "exit";
		// Rebbebion, квест "Путеводная звезда" ==>
		if (CheckAttribute(pchar, "questTemp.Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.Sotta") && !CheckAttribute(npchar, "questTemp.Lutter"))
		{
			if (rand(1) == 0)
			{
				link.l1 = "¿Te has cruzado, por casualidad, con el Capitán Edgardo Sotta? ¿Puedes contarnos algo sobre él? Parece un hombre digno de conocer.";
				link.l1.go = "Sotta1";
				link.l2 = "¿No vas a ver la ejecución del Charlatán?";
				link.l2.go = "Lutter1";
			}
			else
			{
				link.l1 = "Dime, ¿has visto al héroe del día, el Capitán Edgardo Sotta? Me lo perdí, lamentablemente. ¿Cómo es él? ¡No puedo creer que un comerciante atrapó al infame Matt el Bocazas!";
				link.l1.go = "Sotta1_1";
				link.l2 = "Veo que toda la ciudad está celebrando la captura de Lutter, incluso aquellos que nunca van al mar." link.l2.go = "Lutter1_1";
			}
		}
		// <== квест "Путеводная звезда"
		break;

	case "info":
		// заменить на описание неких НПС, по квестам
		dialog.text = "¿Crees que trabajo para el servicio secreto de " + NationNameGenitive(sti(NPChar.nation)) + "?";
		link.l1 = "Bueno... no. Entonces, adiós.";
		link.l1.go = "exit";
		link.l2 = "¿Alguna otra pregunta, entonces?";
		link.l2.go = "new question";
		break;

	case "town":
		// заменить на описание как пройти, по квестам
		dialog.text = "¿Acaso parezco la oficina de investigaciones? No sé, no sé nada.";

		link.l1 = "¡Eres tan cabeza hueca! Vete.";
		link.l1.go = "exit";
		link.l2 = "¿Alguna otra pregunta, entonces?";
		link.l2.go = "new question";
		break;

	// Квест "Путеводная звезда" ==>
	case "Sotta1":
		dialog.text = "No llegué a hablar con él, pero vi su barco, un galeón pesado. Es peligroso navegar solo en estas aguas, pero Sotta lo hace sin escolta.";
		link.l1 = "Probablemente persiguiendo cada moneda de oro y recortando gastos donde pueda. Bueno, no te retendré más. Buen día.";
		link.l1.go = "Exit";

		npchar.questTemp.Sotta = true;
		pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
		AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;

	case "Sotta1_1":
		dialog.text = "¡Ay, es difícil de creer! Pero no confíes en todo lo que oyes, señor. Lo he visto, tan claro como te veo ahora. Es bueno que Lutter haya sido atrapado, pero ¿por qué todo este teatro de mercader? Se comporta como un soldado. Siempre puedo decirlo: un pariente mío sirvió durante años.";
		link.l1 = "Interesante. Bueno, todos tienen sus secretos. Será mejor que me vaya. Gracias por la información.";
		link.l1.go = "Exit";

		npchar.questTemp.Sotta = true;
		pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
		AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;

	case "Lutter1":
		dialog.text = "Ya he visto al hombre. Es difícil creer que este sea el mismo pirata que aterrorizó a nuestros comerciantes durante años. ¿Cómo consiguió llegar a estar al mando? Vi a los soldados escoltándolo... gritando, llorando, riendo. Un loco.";
		link.l1 = "Quizás la derrota y la realidad de su muerte inminente fueron demasiado para él. Pero no importa. ¡Adiós!";
		link.l1.go = "Exit";

		npchar.questTemp.Lutter = true;
		pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
		AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;

	case "Lutter1_1":
		dialog.text = "Sí, y yo también estoy celebrando, un buen número de mis compatriotas murieron a manos suyas. Los desafortunados perdieron a un padre, un hermano, un hijo... ya te haces la idea. ¡Esa barbarie duró demasiado! Matt debe haber sido uno de los piratas más afortunados de los últimos años, si me preguntas.";
		link.l1 = "La suerte siempre se acaba tarde o temprano. Nos vemos.";
		link.l1.go = "Exit";

		npchar.questTemp.Lutter = true;
		pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
		AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		// <== Квест "Путеводная звезда"
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

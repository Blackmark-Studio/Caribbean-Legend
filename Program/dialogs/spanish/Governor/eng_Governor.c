// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = RandPhraseSimple("¿Qué preguntas son esas?", "¿Qué necesitas?");
		link.l1 = RandPhraseSimple("Nada de importancia, señor.", "No tengo nada que decir, disculpas.");
		link.l1.go = "exit";
		break;

	case "work_1": // работа на благо короны - линейка нации
		if (CheckAttribute(npchar, "notQuestLine"))
		{
			dialog.text = "Lamentablemente, no puedo considerarte para un trabajo. No eres alguien con quien quisiera trabajar en este momento. Adiós.";
			link.l1 = "No puede estar hablando en serio... Pero en fin, como quiera.";
			link.l1.go = "exit";
			break;
		}
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

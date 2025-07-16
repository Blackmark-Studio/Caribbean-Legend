// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?", "¿Cómo puedo ayudarle?"), "Intentaste hacerme una pregunta no hace mucho...", "Nadie ha hecho preguntas así en una tienda de Tortuga desde hace mucho tiempo...", "Preguntas, preguntas, y más preguntas...", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No tengo nada de qué hablar en este momento."), "Umph, ¿dónde se ha ido mi memoria...?", "De acuerdo, ha pasado mucho tiempo.", "Mááás preguntas, sí...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga2")
		{
			link.l1 = "Escucha, necesito encontrar a un tal Gaius Marchais. Me han dicho que está involucrado con el corso y se ha convertido en un buen negociador, arrebatando un excelente galeón a los españoles. ¿Ha comprado algún tipo de mercancía de ti para comerciar?";
			link.l1.go = "guardoftruth";
		}
		break;

	case "guardoftruth":
		dialog.text = "¿Gaius Marchais? ¡Oh sí, por supuesto que lo recuerdo! Pero no compró nada. Ofreció su barco para carga. Justo necesitaba un barco con una bodega espaciosa, un gran lote de pieles crudas.";
		link.l1 = "¿Y cuál fue el punto de descarga?";
		link.l1.go = "guardoftruth_1";
		break;

	case "guardoftruth_1":
		dialog.text = "Philipsburg, Saint Martin.";
		link.l1 = "Bien. ¡Gracias, me has ayudado mucho!";
		link.l1.go = "guardoftruth_2";
		break;

	case "guardoftruth_2":
		dialog.text = "¡Cuando quieras, capitán. Pase por mi tienda cuando le apetezca!";
		link.l1 = "... ";
		link.l1.go = "exit";
		AddQuestRecord("Guardoftruth", "10");
		pchar.questTemp.Guardoftruth = "maarten";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

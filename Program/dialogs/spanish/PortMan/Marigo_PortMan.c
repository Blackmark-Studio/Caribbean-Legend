// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué tipo de preguntas?","¿Qué deseas, "+GetAddress_Form(NPChar)+"?"),"Ya has intentado hacerme una pregunta "+GetAddress_Form(NPChar)+"...","Has estado hablando de alguna cuestión por tercera vez hoy...","Mira, si no tienes nada que contarme sobre los asuntos del puerto, entonces no me molestes con tus preguntas.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión.","No tengo nada de qué hablar."),"No importa.","De hecho, ya es la tercera vez...","Lo siento, pero no estoy interesado en los asuntos del puerto por ahora.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "maarten1")
			{
				link.l1 = "Estoy buscando un galeón llamado 'Admirable' bajo la bandera francesa. Su capitán se llamaba Gaius Marchais. ¿Puedes decirme a dónde ha navegado? Tal vez, se ha registrado aquí?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Hmmm, ¿'Admirable'? ¿Galeón? Lo recuerdo. Veamos aquí... lo fletamos para entregar pimentón a Bridgetown en Barbados. ¿Sucedió algo?";
			link.l1 = "No, pero Gaius es mi amigo y estoy deseando conocerlo.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Entonces navega hacia Barbados. Pero dudo que lo encuentres allí, fue hace mucho tiempo. Al menos puedes pedirle ayuda al maestro del puerto.";
			link.l1 = "Allá voy de nuevo, supongo.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "12");
			pchar.questTemp.Guardoftruth = "barbados";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?","¿Cómo puedo ayudarte, "+GetAddress_Form(NPChar)+"?"),"Intentaste hacerme una pregunta hace no mucho, "+GetAddress_Form(NPChar)+"... ","Durante todo este día, esta es la tercera vez que hablas de alguna cuestión...","Más preguntas, supongo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...","No tengo nada de qué hablar en este momento."),"Umph, ¿dónde se ha ido mi memoria...?","Sí, realmente es la tercera vez...","No, ¿qué preguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Долго и счастливо
			if (CheckAttribute(pchar, "questTemp.LongHappy.Santiago"))
			{
				link.l1 = "¿He oído que los santos padres llegaron aquí desde una colonia francesa con alguna delegación, para acordar algo? ¿Probablemente, para intercambiar prisioneros después de esa sangrienta matanza en Martinica?";
				link.l1.go = "LH_tavern";
			}
		break;
		
		// Jason Долго и счастливо
		case "LH_tavern":
			dialog.text = "No señor, esa historia se resolvió hace mucho tiempo sin ningún clérigo. Verá, vive completamente bajo una palmera, ya que no ha oído que el Papa Inocencio X con el Cardenal Mazarino finalmente acordaron. Europa con sus guerras es una cosa, pero todos los cristianos deberían luchar juntos contra la oscuridad pagana al final del mundo.\nY sí, los comedores de ranas vinieron a nosotros. Pero simplemente no acordaron nada: nuestros honorables invitados se sientan en la mansión del gobernador, bajo guardia, beben café y calientan el asiento. ¡Casi un mes ya! La gente chismeó, habló mucho y se acostumbró a ello: mire, el abad francés ofrece un servicio de oración por las tardes en la iglesia. ¡Casi como un espectáculo, ha-ha!";
			link.l1 = "¡Interesante! Debería echar un vistazo a ese francés, al menos es más divertido que mirar una jarra.";
			link.l1.go = "LH_tavern_1";
		break;
		
		case "LH_tavern_1":
			DialogExit();
			LongHappy_SantiagoBenua();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

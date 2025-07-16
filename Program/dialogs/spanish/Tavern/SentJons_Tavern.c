// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?","¿Cómo puedo ayudarte, "+GetAddress_Form(NPChar)+"?"),"Intentaste hacerme una pregunta hace no mucho tiempo, "+GetAddress_Form(NPChar)+"...","Durante todo este día, esta es la tercera vez que hablas de alguna pregunta...","¿Más preguntas, supongo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...","No tengo nada de qué hablar en este momento."),"Umph, ¿dónde se ha ido mi memoria...?","Sí, realmente es la tercera vez...","No, ¿qué preguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason, Сага, Тени прошлого
			if (CheckAttribute(PChar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "sentjons")
			{
				link.l1 = "Estoy buscando a Raymond Baker, un antiguo verdugo. ¿Sabes si está vivo y dónde podría encontrarlo?";
				link.l1.go = "baker";
			}
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
			{
				link.l1 = "Estoy buscando al Sr. Jones. ¿Puedes ayudarme en mi búsqueda, compañero?";
				link.l1.go = "terrapin";
			}
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok")
			{
				link.l1 = "Escucha, ¿ha llegado a esta ciudad un alquimista, o un médico? Es italiano, tiene unos treinta años, se llama Gino Gvineili. ¿Has oído algo al respecto?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Сага, Тени прошлого
		case "baker":
			dialog.text = "¡Nuestro querido gordiflón se ha vuelto más popular que el Coronel Fox! Está vivo, el pobre. Pero no está en la ciudad en este momento. Después de que Raymond se enteró de que personas serias como tú estaban interesadas en él, se apresuró a vender su choza por una miseria y se fue como el viento.";
			link.l1 = "¿Adónde se lo llevó el viento?";
			link.l1.go = "baker_1";
		break;
		
		case "baker_1":
			dialog.text = "Oh, quién sabe. Se fue a servir como médico de barco en el primer navío que pasó. Solo que ese navío acaba de regresar hoy y nadie ha visto a Baker desembarcar todavía.";
			link.l1 = "¿Cómo puedo encontrar al capitán?";
			link.l1.go = "baker_2";
		break;
		
		case "baker_2":
			dialog.text = "¿Por qué crees que necesitas buscarlo? Estoy seguro de que ya está borracho como de costumbre en su camarote. Su cubo con fugas se llama 'Callow Meggy'. Tal es el capitán, tal es el nombre...";
			link.l1 = "¡Gracias por la ayuda, compañero!";
			link.l1.go = "baker_3";
		break;
		
		case "baker_3":
			DialogExit();
			AddQuestRecord("Shadows", "2");
			pchar.questTemp.Saga.Shadows = "baldmaggy";
			pchar.quest.Saga_ShadowsMaggy.win_condition.l1 = "location";
			pchar.quest.Saga_ShadowsMaggy.win_condition.l1.location = "Antigua";
			pchar.quest.Saga_ShadowsMaggy.function = "Saga_SetBaldMaggy";
		break;
		
		//суп из черепахи
		case "terrapin":
			dialog.text = "¿Señor Jones? ¿Me estás tomando el pelo, camarada? ¿Sabes cuántos malditos Jones hay en esta isla? Vas a necesitar ser más específico que eso.";
			link.l1 = "Tiene una hermana adulta, Molly. Dicen que es asombrosamente hermosa.";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "No. Nada de eso me viene a la mente. Lo siento, camarada...";
			link.l1 = "Está bien, si no sabes, no sabes...";
			link.l1.go = "exit";
			npchar.quest.terrapin = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "No, no lo he oído. Y solo tenemos un alquimista en el pueblo, el farmacéutico John Murdock. Tiene pociones extraordinarias, curan cualquier dolencia.";
			link.l1 = "¿Crees que él mismo elabora estas pociones?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Buena pregunta. Me lo pregunto de vez en cuando, John no se parece en nada a un conocedor de vasos de medicina, hierbas y polvos. Más bien se asemeja a un ex-soldado, un mercenario... eso está más cerca de la verdad.";
			link.l1 = "Bueno, supongo que el hombre está sobrecalificado...";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Tal vez lo sea. Pero hay una cosa que sé con certeza, alguien vive en su segundo piso. La ventana está constantemente cubierta. Incluso cuando John está abajo, se escucha un sonido de tintineo como de frascos de vidrio y botellas, así como el olor de hierbas hirviendo, y por la noche la luz no se apaga. Por eso sospecho que el habitante de esa habitación es quien está preparando las medicinas de John para la venta.";
			link.l1 = "Hum. Observación interesante. ¡Gracias, camarada!";
			link.l1.go = "exit";
			pchar.questTemp.Guardoftruth = "merdok1";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

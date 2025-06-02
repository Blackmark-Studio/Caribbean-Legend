// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?","¿Cómo puedo ayudarte, "+GetAddress_Form(NPChar)+"?"),"Intentaste hacerme una pregunta hace poco, "+GetAddress_Form(NPChar)+"...","Durante todo el día, esta es la tercera vez que hablas de alguna pregunta...","Más preguntas, supongo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...","No tengo nada de qué hablar en este momento."),"Umph, ¿dónde se ha ido mi memoria...?","Sí, realmente es la tercera vez...","No, ¿qué preguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Сага
			if(CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "valet")
			{
				link.l1 = "Busco a un hombre apodado Valet. ¿Lo conoces?";
				link.l1.go = "valet_1";
				link.l2 = "Busco al capitán de una polacra, llamada 'Marlin'. ¿Podrías decirme dónde encontrarlo?";
				link.l2.go = "valet_2";
			}
		break;
		
		case "valet_1":
			dialog.text = NPCStringReactionRepeat("No, no lo sé, colega. Así que no hay nada con lo que pueda ayudarte.","¡Ya te he dicho que no lo sé!","¿Estás borracho o solo estás jugando?","¡Déjame en paz!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ya veo. Eso es una lástima...","Eso es una lástima. Pensé que recordarías...","¡Estoy sobrio! Solo soy persistente...","Mm...",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		case "valet_2":
			dialog.text = NPCStringReactionRepeat("¡Ah, el señor David Fackman! Alquila una casa no lejos del astillero. Búscalo allí.","Acabo de responderte. ¿Me has escuchado?","¿Estás borracho o solo estás haciendo el tonto?","¡Déjame en paz!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("¡Gracias!","Sí. Lo siento.","¡Estoy sobrio! Sólo soy persistente...","Mm...",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

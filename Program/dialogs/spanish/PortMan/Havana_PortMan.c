// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué tipo de preguntas?","¿Qué quieres, "+GetAddress_Form(NPChar)+"?"),"Ya has intentado hacerme una pregunta "+GetAddress_Form(NPChar)+"...","Has estado hablando de alguna cuestión por tercera vez hoy...","Mira, si no tienes nada que decirme sobre los asuntos del puerto, entonces no me molestes con tus preguntas.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión.","No tengo nada de qué hablar."),"No importa.","De hecho, ya es la tercera vez...","Lo siento, pero no estoy interesado en los asuntos del puerto por ahora.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "Buen día para usted. Me gustaría saber sobre una corbeta llamada '"+pchar.questTemp.Slavetrader.ShipName+" bajo el mando de Francois Gontier.";
                link.l1.go = "Havana_ratP_1";
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Disculpe, ¿ha llegado a su puerto un hombre llamado Joachim Merriman? Un señor de mediana edad, portugués, con bigote, barba imperial y ojos penetrantes?";
				link.l1.go = "caleuche";
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && !CheckAttribute(npchar, "quest.Mtraxx"))
			{
				link.l1 = "Me interesa un barco llamado 'Cantavro'. Busco a su capitán, Esberdo Cabanas, por un asunto privado. ¿Podrías ayudarme?";
				link.l1.go = "mtraxx";
			}
		break;
		
		case "Havana_ratP_1":
			dialog.text = NPCStringReactionRepeat("Sí, estuvo aquí. Pero ya se ha ido. Pregunta a nuestro tabernero por él, ha alquilado una habitación arriba.","Ya has preguntado sobre esto y te he respondido.","Te digo que ya has preguntado por este Gontier..","¡Te pido que no me molestes!","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Gracias. Haré eso.","Mm, bueno ...","Sí, realmente he preguntado ...","Perdón, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "No puedo decirte nada sobre él. Incluso si llegó, nunca se registró en ningún lado.";
			link.l1 = "Ya veo. Qué lástima... Está bien, continuaré mi búsqueda ...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
			dialog.text = "Veamos... el bergantín 'Cantavro' zarpó hace dos días en una patrulla... sin embargo, la ubicación no está listada. Es un buque militar, así que el destino solo lo conocen su capitán y el comandante del fuerte. Te sugeriría hablar directamente con el comandante, puedes encontrarlo en el fuerte, si deseas saber más. Desafortunadamente, eso es todo lo que puedo hacer por ti.";
			link.l1 = "Ya veo. Bueno, gracias por tu tiempo...";
			link.l1.go = "exit";
			npchar.quest.Mtraxx = "true";
			AddQuestRecord("Roger_1", "5");
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Havana_tavernkeeper"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas son esas?", "¿Qué deseas, " + GetAddress_Form(NPChar) + "?"), "Ya has intentado hacerme una pregunta " + GetAddress_Form(NPChar) + "...", "Has estado hablando de alguna pregunta por tercera vez hoy...", "Mira, si no tienes nada que contarme sobre los asuntos del puerto, entonces no me molestes con tus preguntas.", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión.", "No tengo nada de qué hablar."), "No importa.", "De hecho, ya es la tercera vez...", "Lo siento, pero no estoy interesado en los asuntos del puerto por ahora.", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		//--> Бремя гасконца
		if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "ship" && !CheckAttribute(npchar, "quest.RescueDaughter"))
		{
			DelLandQuestMark(npchar);
			link.l1 = "Señor, estoy buscando un trabajo. Pero no un trabajo de mozo, algo más adecuado para mi rango. Misión, servicio, con asuntos delicados... Aceptaré cualquier encargo que tenga.";
			link.l1.go = "Sharlie";
		}
		//<-- Бремя гасконца

		// Jason „олго и счастливо
		if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "portman")
		{
			link.l1 = "Me dijeron que tenías una carta para mí. El nombre es Capitán Charles de Maure.";
			link.l1.go = "LH_letter";
		}
		break;

	case "Sharlie":
		dialog.text = "¿Ayuda? Hm. Estoy bien, gracias a Dios. Pero uno de mis amigos realmente necesita ayuda y es urgente. ¡Va a entrar a la selva solo para luchar contra los indios, esto es una locura absoluta!\nIntenté razonar con él, le supliqué, ¡pero no escuchó! Se preocupa demasiado por su hija y está dispuesto a dar su vida por ella.";
		link.l1 = "Espera, empecemos de nuevo: ¿quién es tu amigo, dónde puedo encontrarlo y qué tipo de ayuda necesita?";
		link.l1.go = "Sharlie_1";
		break;

	case "Sharlie_1":
		dialog.text = "Ah, discúlpame, estoy demasiado ansioso. Su nombre es Prosper... Prosper Troubale. ¡Va a morir seguro! Y no puedo ayudarlo, no soy un soldado. Su hija ha desaparecido y él cree que los indios locales son responsables\n¡Imagínate eso, planea ir tras los salvajes por su cuenta! Lo harán pedazos... En este momento está comprando un mosquete y preparándose para salir a la selva.";
		link.l1 = "Eres un narrador miserable, señor. ¿Dónde puedo encontrar a tu amigo... cómo era su nombre... Prosper?";
		link.l1.go = "Sharlie_2";
		break;

	case "Sharlie_2":
		dialog.text = "Acabo de hablar con él e intentaba hacerle cambiar de opinión. No está lejos de las puertas de la ciudad, junto al pozo, revisando su mosquete y municiones. ¡Ve a él y haz algo! Si se adentra solo en la jungla, no volverá, estoy seguro de ello. Los diablos de piel roja lo destrozarán...";
		link.l1 = "¡Deja de divagar, suenas como una vieja! Me dirijo a tu amigo de inmediato. Espero poder ayudarle.";
		link.l1.go = "Sharlie_3";
		break;

	case "Sharlie_3":
		DialogExit();
		AddQuestRecord("SharlieF", "1");
		RescueDaughter_CreateProsper();
		npchar.quest.RescueDaughter = "true";
		QuestPointerDelLoc("fortfrance_town", "reload", "reload10_back");
		break;

	// Jason „олго и счастливо
	case "LH_letter":
		dialog.text = "Sí, tienes razón, hay un sobre. Aquí está, pero primero, necesitas pagar por la entrega, doce mil pesos de plata.";
		if (sti(pchar.money) >= 12000)
		{
			link.l1 = "Siempre sospeché que tu oficio era originalmente un negocio de ladrones, pero de alguna manera me perdí la noticia, hm. Por favor, aquí está tu dinero.";
			link.l1.go = "LH_letter_1";
		}
		else
		{
			link.l1 = "Volveré un poco más tarde, creo que dejé mi bolsa de monedas en la taberna.";
			link.l1.go = "exit";
		}
		break;

	case "LH_letter_1":
		DialogExit();
		AddMoneyToCharacter(pchar, -12000);
		LongHappy_RecibeLetter();
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?", "¿Cómo puedo ayudarte?"), "Intentaste hacerme esa pregunta no hace mucho...", "Sí, déjame adivinar... ¿Otra vez dando vueltas en círculos?", "Escucha, yo manejo las finanzas aquí, no respondo preguntas...", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No tengo nada de qué hablar en este momento."), "Umph, ¿dónde se ha ido mi memoria...?", "Lo has adivinado, lo siento...", "Entiendo...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
		{
			link.l1 = "Mynheer, tengo un asunto algo inusual. Sé que un corsario francés llamado Gaius Marchais te vendió recientemente dos objetos únicos: una custodia de oro y un incensario de oro. Me gustaría comprártelos.";
			link.l1.go = "guardoftruth";
		}
		if (CheckAttribute(npchar, "quest.GOT_chest") && CheckCharacterItem(pchar, "chest"))
		{
			link.l1 = "Te he traído un pequeño cofre de doblones.";
			link.l1.go = "guardoftruth_3";
		}
		break;

	case "guardoftruth":
		dialog.text = "¡Oh, sí! ¡Por supuesto que los recuerdo! Sí, realmente eran artículos originales y, más importante, caros. Pero llegas tarde, capitán, ya no los tengo. Ya los he vendido.";
		link.l1 = "¡Increíble! ¿Y quién estaba interesado en objetos de iglesia de ese tipo? Mynheer, ¿a quién se los vendiste? Me gustaría intentar recomprarlos...";
		link.l1.go = "guardoftruth_1";
		npchar.quest.utensil = "true";
		break;

	case "guardoftruth_1":
		dialog.text = "Hum, ¿y por qué debería darte los nombres de mis clientes?";
		if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "self_win")
		{
			link.l1 = "¿Tal vez porque soy un buen amigo del gobernador Matthias Beck y puedo pedirle una sanción correspondiente para ti?";
			link.l1.go = "guardoftruth_2_1";
		}
		else
		{
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "holl_win")
			{
				link.l1 = "¿Tal vez, porque tengo excelentes relaciones con la Compañía Holandesa de las Indias Occidentales y he prestado gran ayuda a muchos colonos holandeses en el archipiélago?";
				link.l1.go = "guardoftruth_2_2";
			}
			else
			{
				link.l1 = "¿Quizás porque pagaré por ello?";
				link.l1.go = "guardoftruth_2_3";
				npchar.quest.GOT_chest = "true";
			}
		}
		break;

	case "guardoftruth_2_1":
		dialog.text = "Ah, seguro que eres " + GetFullName(pchar) + ", un amigo del propio gobernador que reveló la conspiración criminal de Lucas Rodenburg... ¿Cómo podría olvidarlo? Por supuesto, te lo diré.";
		link.l1 = "Entonces, soy todo oídos.";
		link.l1.go = "guardoftruth_4";
		break;

	case "guardoftruth_2_2":
		dialog.text = "Ah, correcto, eres " + GetFullName(pchar) + ", el gran conquistador del 'barco fantasma' pirata. ¿Cómo podría olvidar eso? Por supuesto, te lo diré.";
		link.l1 = "Entonces, soy todo oídos.";
		link.l1.go = "guardoftruth_4";
		break;

	case "guardoftruth_2_3":
		dialog.text = "Está bien, entonces. Por un cofre lleno hasta el tope de doblones de oro, supongo que te contaré sobre aquellos que te superaron para hacer la compra.";
		if (CheckCharacterItem(pchar, "chest"))
		{
			link.l1 = "Aquí tienes. Son artículos muy queridos para mí...";
			link.l1.go = "guardoftruth_3";
		}
		else
		{
			link.l1 = "Está bien, te traeré lo que pides. Son objetos muy preciados para mí...";
			link.l1.go = "exit";
		}
		break;

	case "guardoftruth_3":
		RemoveItems(pchar, "chest", 1);
		Log_Info("¡Has entregado un cofre de doblones!");
		PlaySound("interface\important_item.wav");
		dialog.text = "Maravilloso. En ese caso, estoy dispuesto a compartir alguna información contigo.";
		link.l1 = "Soy todo oídos.";
		link.l1.go = "guardoftruth_4";
		DeleteAttribute(npchar, "quest.GOT_chest");
		break;

	case "guardoftruth_4":
		dialog.text = "El incensario de oro fue comprado por un hombre llamado Rolande Moses, mejor conocido como Rollie el Cap. Por qué este carnicero necesitaba un objeto precioso de iglesia, no puedo entenderlo, pero por alguna razón estaba indescriptiblemente feliz con él... Por cierto, dudo que te encuentres con el propio Rollie.";
		link.l1 = "¿Y a qué se debe?";
		link.l1.go = "guardoftruth_5";
		break;

	case "guardoftruth_5":
		dialog.text = "Porque este ávido ladrón de solitarios comerciantes ingleses recientemente cayó con su goleta justo en las garras del Coronel Fox. ¿Sabes quién es?";
		link.l1 = "¡Por supuesto que sí! El comandante de los 'Sea Foxes' de St. John's, en Antigua...";
		link.l1.go = "guardoftruth_6";
		break;

	case "guardoftruth_6":
		dialog.text = "Bueno, entonces entiendes por qué nunca volveremos a ver a nuestro pobre Rolande. El coronel se apoderó de su goleta con todos los sobrevivientes de su tripulación, y los entregó a St. John's, donde probablemente ya les hayan atado una soga al cuello.";
		link.l1 = "Ya veo. ¿Y el ostensorio?";
		link.l1.go = "guardoftruth_7";
		break;

	case "guardoftruth_7":
		dialog.text = "La custodia ha sido adquirida muy recientemente por la Señora Belinda de Ribero de Cumaná. Una señora muy notable, pariente del mismo Fernando de Villegas, gobernador de Cumaná. Supongo que ella quería llevarla como regalo a la iglesia.";
		link.l1 = "¿Señora Belinda de Ribero? ¿Puedo encontrarla en Cumaná, verdad?";
		link.l1.go = "guardoftruth_8";
		break;

	case "guardoftruth_8":
		dialog.text = "Definitivamente. Ella misma dijo que iría directamente a casa desde Willemstad.";
		link.l1 = "Está bien. Gracias, " + npchar.name + ". Has sido de gran ayuda.";
		link.l1.go = "guardoftruth_9";
		break;

	case "guardoftruth_9":
		dialog.text = "¡En cualquier momento, mynheer! ¡Visítame de vez en cuando!";
		link.l1 = "Te deseo clientes ricos con carteras gordas y cerebros escasos... ¡Ja-ja!";
		link.l1.go = "guardoftruth_10";
		break;

	case "guardoftruth_10":
		DialogExit();
		AddQuestRecord("Guardoftruth", "23");
		pchar.questTemp.Guardoftruth.Usurer = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

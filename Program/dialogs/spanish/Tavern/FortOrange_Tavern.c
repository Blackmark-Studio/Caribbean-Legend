// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?", "¿Cómo puedo ayudarte, " + GetAddress_Form(NPChar) + "?"), "Intentaste hacerme una pregunta no hace mucho, " + GetAddress_Form(NPChar) + "...", "Durante todo este día, esta es la tercera vez que hablas de alguna pregunta...", "Más preguntas, supongo?", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No tengo nada de qué hablar en este momento."), "Umph, dónde se ha ido mi memoria...", "Sí, es realmente la tercera vez...", "No, ¿qué preguntas?...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		if (pchar.questTemp.Slavetrader == "FindRatJamaica")
		{
			link.l1 = "¿Un hombre llamado Francois Gontier ha pasado por tu pueblo? Realmente lo necesito.";
			link.l1.go = "Jamaica_ratF_1";
		}
		// Addon 2016-1 Jason пиратская линейка
		if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_4")
		{
			link.l1 = "Escucha, amigo, hay un barco de Port Royal que está comprando algo de seda para su astillero... una seda muy especial, seguramente has oído hablar de eso. Dicen que un vendedor de esa seda está residiendo en algún lugar de este asentamiento. ¿Tienes alguna pista sobre cómo encontrarlo? Tengo una propuesta de negocio para él.";
			link.l1.go = "mtraxx";
		}
		if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_5" && (PCharDublonsTotal() >= 50))
		{
			link.l1 = "Tengo cincuenta doblones conmigo. Tómalos y empieza a hablar.";
			link.l1.go = "mtraxx_4_1";
		}
		break;

	case "Jamaica_ratF_1":
		dialog.text = "Lo ha hecho. Estuvo alquilando una habitación por unos días. No es el sujeto más agradable, te lo diré. Además de eso, estaba obsesivamente paranoico de ser buscado. Siempre tenía miedo y miraba a su alrededor. ¿Eres tú el hombre del que tenía tanto miedo?";
		link.l1 = "No, no soy yo. Sabes, los corsarios tienen muchos enemigos. Entonces, ¿dónde puedo encontrarlo? Él y yo decidimos llegar a un acuerdo, pero parece que la tierra se lo ha tragado.";
		link.l1.go = "Jamaica_ratF_2";
		break;

	case "Jamaica_ratF_2":
		dialog.text = "Se ha marchado a alta mar en su propio barco. No sé a dónde. No me informó sobre eso.";
		link.l1 = "¡Ah, qué lástima! ¿Dónde voy a buscarlo ahora?";
		link.l1.go = "Jamaica_ratF_3";
		break;

	case "Jamaica_ratF_3":
		dialog.text = "No lo sé, camarada. Te lo diría si lo supiera.";
		link.l1 = "Está bien, ya veo. Iré a preguntarle a otras personas...";
		link.l1.go = "exit";
		AddQuestRecord("Slavetrader", "21_4");
		pchar.questTemp.Slavetrader = "FindRatJamaica_H";
		break;

	// Addon 2016-1 Jason пиратская линейка
	case "mtraxx":
		dialog.text = "Vaya, si sospechas de nuestro comerciante, el que lleva la tienda, puedo decirte que no es él, no comercia con tela de vela de seda. Los contrabandistas tampoco vienen aquí, no tienen necesidad cuando no hay aduana. Y además, nadie más, excepto nuestro comerciante, comercia aquí de todas formas. Echa un vistazo, no somos de ese tipo de gente, ¡ja-ja!";
		link.l1 = "Pero alguien está suministrando la seda a Port Royal, eso es irrefutable. ¿Tienes alguna pista de quién podría ser el proveedor?";
		link.l1.go = "mtraxx_1";
		break;

	case "mtraxx_1":
		dialog.text = "¿Contrabandistas de Port Royal, tal vez? ¿O piratas rebeldes? Deben estar descargando su botín en alguna cala escondida... ¡Ja! Tengo una idea, camarada. Hay un lugareño, él sabe todo lo que sucede en estas aguas. Si él no tiene ninguna suposición, entonces no hay mercaderes de seda.";
		link.l1 = "¡Espléndido! ¿Cómo se llama el tipo?";
		link.l1.go = "mtraxx_2";
		break;

	case "mtraxx_2":
		dialog.text = "Hm... Estoy tratando de recordar su nombre, pero por alguna razón no me viene a la mente...";
		link.l1 = "¿Qué tal unas monedas para refrescar tu memoria?";
		link.l1.go = "mtraxx_3";
		break;

	case "mtraxx_3":
		dialog.text = "Supongo que eso podría ayudar... Cincuenta doblones de oro seguramente iluminarán esta vieja cabeza.";
		if (PCharDublonsTotal() >= 50) // Rebbebion, учёт количества дублонов из рундука
		{
			link.l1 = "Ya veo. Aquí, toma las monedas.";
			link.l1.go = "mtraxx_4_1";
		}
		else
		{
			link.l1 = "Ya veo. Volveré...";
			link.l1.go = "mtraxx_4_2";
		}
		break;

	case "mtraxx_4_1":
		RemoveDublonsFromPCharTotal(50);
		PlaySound("interface\important_item.wav");
		dialog.text = "Husky Billy es el hombre que necesitas. Ha estado viviendo en Jamaica desde hace una eternidad, conoce a cada perro en las calles. Solía ser un pirata y un dolor en el trasero de los británicos hasta que resultó herido hace unos tres años. Ahora principalmente pesca, caza tiburones y recolecta ámbar en las bahías de Jamaica. Deja su vieja chalupa solo para comprar más ron y galletas.\nDeberías buscarlo en las aguas alrededor de Jamaica. Dicen que está navegando en el lado norte, hasta el punto más al este. Pero perseguir un bote es un esfuerzo inútil, es mejor que vigiles alrededor del rincón suroeste, dicen que lo han visto cerca del Cabo Negril aproximadamente una vez a la semana. Su barquichuelo se llama 'El Pez Volador'.";
		link.l1 = "Gracias, compañero. Has ganado tu oro.";
		link.l1.go = "mtraxx_5";
		break;

	case "mtraxx_5":
		dialog.text = "¡Buena suerte, camarada! ¡Espero que encuentres lo que buscas!";
		link.l1 = "...";
		link.l1.go = "mtraxx_6";
		break;

	case "mtraxx_4_2":
		DialogExit();
		AddQuestRecord("Roger_2", "6");
		pchar.questTemp.Mtraxx = "silk_5";
		break;

	case "mtraxx_6":
		DialogExit();
		AddQuestRecord("Roger_2", "7");
		pchar.questTemp.Mtraxx = "silk_6";
		/*pchar.quest.mtr_negril.win_condition.l1 = "Timer";
		pchar.quest.mtr_negril.win_condition.l1.date.hour  = 12+rand(12);
		pchar.quest.mtr_negril.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2+rand(3));
		pchar.quest.mtr_negril.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2+rand(3));
		pchar.quest.mtr_negril.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2+rand(3));*/
		PChar.quest.mtr_negril.win_condition.l1 = "ExitFromLocation";
		PChar.quest.mtr_negril.win_condition.l1.location = PChar.location;
		pchar.quest.mtr_negril.function = "Mtraxx_CreateBilly";
		SetFunctionTimerCondition("Mtraxx_BillySeaTimeOver", 0, 0, 7, false);
		if (bImCasual)
			NewGameTip("Modo exploración: el temporizador no está desactivado. ¡Cumple el plazo!");
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

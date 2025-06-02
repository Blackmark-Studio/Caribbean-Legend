// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
	int i, tempQty, chComp, iShip, iBaseType;
	string tempStr;
	switch (Dialog.CurrentNode)
	{
	case "quests":
		// Португалец
		if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad") && pchar.location == "villemstad_townhall")
		{
			dialog.text = RandPhraseSimple("¿Qué tipo de preguntas?", "¿Qué te gustaría?");
			link.l1 = "Yo sé que la Compañía Holandesa de las Indias Occidentales ha asignado un buen precio por la cabeza del famoso pirata Bartolomeo el Portugués. Pude capturarlo. Actualmente está en la bodega de mi barco, y estoy listo para entregarlo a las autoridades.";
			link.l1.go = "Portugal";
			break;
		}
		dialog.text = RandPhraseSimple("¿Qué tipo de preguntas?", "¿Qué es lo que necesitas?");
		link.l1 = RandPhraseSimple("Nada de importancia, señor.", "No tengo nada que decir, disculpas.");
		link.l1.go = "exit";
		break;

	case "work_1": // работа на благо короны - линейка нации
		if (CheckAttribute(npchar, "notQuestLine"))
		{
			dialog.text = "Lamentablemente, no puedo considerarte para un trabajo. No eres alguien con quien quisiera trabajar en este momento. Adiós.";
			link.l1 = "No puedes estar hablando en serio... Pero en fin, como quiera.";
			link.l1.go = "exit";
			break;
		}
		break;

	// Португалец
	case "Portugal":
		dialog.text = "¿Bart el Portugués? ¿Lo tienes? ¿Vivo?";
		link.l1 = "¡Sé que no necesitas que esté muerto! Está vivo. ¡Tuve que hacer grandes esfuerzos para mantenerlo así!";
		link.l1.go = "Portugal_1";
		break;

	case "Portugal_1":
		dialog.text = "¡Excelente! Ahora él nos contará todo... Mynheer, prepare al prisionero para su traslado. Enviaremos una barca militar a su barco de inmediato.";
		link.l1 = "Quisiera hablar primero sobre mi recompensa, señor... Si no le importa.";
		link.l1.go = "Portugal_2";
		break;

	case "Portugal_2":
		dialog.text = "No te preocupes por tu recompensa, capitán. La obtendrás. Hemos asignado un precio por la cabeza de Bartolomeo el Portugués: mil quinientos doblones. ¡Teniente! ¡Traiga al capitán su recompensa!";
		link.l1 = "Mm... Parece que Hugo me ha mentido sobre dos mil doblones... Está bien, entonces.";
		link.l1.go = "Portugal_3";
		break;

	case "Portugal_3":
		TakeNItems(pchar, "gold_dublon", 1500);
		Log_Info("¡Has recibido 1.500 doblones!");
		PlaySound("interface\important_item.wav");
		dialog.text = "Y ahora, capitán, ¿sería tan amable de transferir al portugués a la Compañía? No podemos esperar para tener una charla con él.";
		link.l1 = "Claro, señor, envíe la barca a mi barco.";
		link.l1.go = "Portugal_4";
		break;

	case "Portugal_4":
		DialogExit();
		DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
		DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

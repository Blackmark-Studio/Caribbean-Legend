// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat("Todos los rumores de " + GetCityName(npchar.city) + " a su servicio. ¿Qué le gustaría saber?", "Justo estábamos hablando de eso. Debes haberlo olvidado...", "Esta es la tercera vez hoy que hablas de alguna pregunta...", "Repites lo mismo como un loro...", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Sabes, " + NPChar.name + ", tal vez la próxima vez.", "Es cierto, lo he olvidado por alguna razón...", "Sí, realmente es la tercera vez...", "Sí...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince")
		{
			link.l1 = "Cuéntame, ¿ha pasado por tu colonia últimamente un galeón llamado 'Santa Margarita'? ¿Quizás como el premio de un corsario?";
			link.l1.go = "guardoftruth";
		}
		//--> Украденное воспоминание
		if (CheckAttribute(pchar, "questTemp.UV_DialogCitizen"))
		{
			link.l1 = "¿No ha pasado por aquí Tristan Renier?";
			link.l1.go = "UV_DialogTavern";
		}
		//<-- Украденное воспоминание
		break;

	case "guardoftruth":
		dialog.text = "Amigo, es bastante raro que alguien se detenga en nuestra colonia con premios y no hemos visto un galeón con un nombre como ese. La Española es una isla salvaje y somos una colonia pequeña. Aquí es tranquilo. Comerciamos con los bucaneros en las tierras altas por pieles de vaca y carne seca. Los corsarios no suelen quedarse por aquí, no tenemos burdeles y tenemos a los españoles muy cerca. Busca tu galeón en otro lugar.";
		link.l1 = "Ya veo. ¡Gracias por el consejo!";
		link.l1.go = "exit";
		AddQuestRecord("Guardoftruth", "7");
		pchar.questTemp.Guardoftruth = "tortuga";
	break;
		
	//--> Украденное воспоминание
	case "UV_DialogTavern":
		dialog.text = "¿Tristán? Claro que estuvo aquí. De hecho, en una de las habitaciones.";
		link.l1 = "Perfecto, entonces lleg"+GetSexPhrase("ué","ué")+ " a tiempo. Tengo un asunto urgente con él, así que tendré que interrumpir su descanso.";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("UV_GoldSeagull_RoomInTavern");
		DelLandQuestMark(npchar);
	break;
//<-- Украденное воспоминание

	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

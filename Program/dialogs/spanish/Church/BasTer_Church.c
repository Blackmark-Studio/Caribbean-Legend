// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué tipo de preguntas, " + GetSexPhrase("hijo mío", "hija mía") + "?", "Pregunta, estoy escuchando..."), "Estoy escuchando, habla ahora, " + GetSexPhrase("hijo mío", "hija mía") + "...", "Por tercera vez, " + GetSexPhrase("hijo mío", "hija mía") + ", pide lo que necesites.", "Un clérigo tiene mucho trabajo y me estás distrayendo, " + GetSexPhrase("hijo mío", "hija mía") + "...", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No en este momento, padre..."), "No tengo nada que decir, mis disculpas.", "Lo preguntaré, pero más tarde. Perdóname, padre.", "Perdóneme, santo padre...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
		{
			link.l1 = "Vengo a usted por un asunto inusual, santo padre. Un corsario llamado Guy Marchais ha presentado un objeto muy valioso a su parroquia hace poco. Era una cruz pectoral dorada con lapislázuli incrustado en ella. ¿Es eso cierto?";
			link.l1.go = "guardoftruth";
		}
		break;

	case "guardoftruth":
		dialog.text = "¡Oh sí, hijo mío! Es el mejor objeto de nuestra parroquia. ¡No he visto tal magnificencia en toda mi vida! Pero, ¿por qué preguntas, hijo mío? ¿Por qué te interesa esta cruz?";
		link.l1 = "Santo padre, sé que esto no será de su agrado, pero esta cruz fue robada de otra parroquia, y el clérigo fue asesinado durante el acto. Ese hombre que le ha presentado este objeto es un asesino.";
		link.l1.go = "guardoftruth_1";
		break;

	case "guardoftruth_1":
		dialog.text = "Todos pecamos, hijo mío, y asesinar a un clérigo es una acusación seria. ¿Tienes alguna prueba? ¿De qué parroquia fue robada esta cruz?";
		link.l1 = "¿Mi palabra no es prueba suficiente? Esta cruz fue robada de la parroquia en Santiago, y debe ser devuelta.";
		link.l1.go = "guardoftruth_2";
		break;

	case "guardoftruth_2":
		dialog.text = "¿Santiago? ¿No es esa una ciudad española? Hijo mío, me estás sorprendiendo...";
		link.l1 = "Santo padre, todos somos iguales ante Dios. Los españoles son cristianos como nosotros, y las desavenencias entre las naciones no deben afectar los sentimientos de los creyentes. Te suplico que devuelvas esta cruz a la parroquia de Santiago.";
		link.l1.go = "guardoftruth_3";
		break;

	case "guardoftruth_3":
		dialog.text = "Hijo mío, ¿no entiendes que esta cruz es un regalo de los cristianos devotos para nuestra parroquia? No, hijo mío, no puedo hacer lo que pides.";
		link.l1 = "¿No te importa que se haya derramado sangre por esta cruz? La sangre de un clérigo, español o no, no importa.";
		link.l1.go = "guardoftruth_4";
		break;

	case "guardoftruth_4":
		dialog.text = "Hijo mío, no has mostrado ninguna prueba y no puedo aceptar tu palabra ciegamente. La cruz se quedará en nuestra parroquia. Esta es mi decisión final. Además, tu esfuerzo por ayudar a los españoles en este asunto me preocupa mucho.";
		link.l1 = "Así sea. Adiós pues, santo padre...";
		link.l1.go = "guardoftruth_5";
		break;

	case "guardoftruth_5":
		DialogExit();
		npchar.quest.utensil = "true";
		pchar.questTemp.Guardoftruth.Baster_church = "seek";
		AddQuestRecord("Guardoftruth", "27");
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

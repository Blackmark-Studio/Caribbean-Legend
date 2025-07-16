// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Todos los rumores de "+GetCityName(npchar.city)+" a su servicio. ¿Qué le gustaría averiguar?","Justo estábamos hablando de eso. Debes haberlo olvidado...","Esta es la tercera vez hoy que me lo preguntas...","Repites todo igual que un loro...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabes, "+NPChar.name+", tal vez la próxima vez.","Correcto, lo he olvidado por alguna razón...","Sí, realmente es la tercera vez...","Aye...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Escucha, ¿ha llegado aquí a este pueblo un alquimista, o un médico? Es italiano, tiene unos treinta años, y se llama Gino Gvineili?";
				link.l1.go = "guardoftruth";
			}
			// Калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.Caleuche"))
			{
				link.l1 = "Escucha, necesito a un cazador llamado Fergus Hooper. Me han dicho que vive aquí. ¿Dónde puedo encontrarlo?";
				link.l1.go = "caleuche";
			}
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("No, creo que no. Tenemos herbolarios y médicos, pero ninguno con ese nombre.","Es la primera vez que oigo un nombre tan extraño. No, nunca hemos recibido la visita del hombre del que hablas.","No tenemos ningún tipo de alquimista en absoluto. Tenemos médicos, pero ninguno con un nombre así.");
			link.l1 = "Ya veo. Eso es una lástima. ¡Seguiré buscando!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
		
		// Калеуче
		case "caleuche":
			dialog.text = "¿Fergus? A menudo visita este lugar. Pero ha estado en la selva desde ayer. No te preocupes, volverá en una semana, bebiendo ron y jactándose de sus aventuras marinas. Aunque, lo admito, es un maldito buen cazador. No conozco a nadie que atrape serpientes tan bien como él.";
			link.l1 = "¿Serpientes? Hm. ¿Cuándo debería volver aquí para encontrarlo?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Al menos tres días. Tenga en cuenta que él siempre viene aquí no antes de las seis de la tarde, y se va no más tarde de las diez.";
			link.l1 = "¿Cómo luce? Nunca lo he visto antes.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Barbudo, de mediana edad, lleva un abrigo marrón, sombrero y botas largas.";
			link.l1 = "¡Gracias! Me has ayudado mucho, camarada. ¡Nos vemos!";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "8");
			int iTerms = sti(pchar.questTemp.Caleuche.Belizterms);
			SetFunctionTimerCondition("Caleuche_FergusCome", 0, 0, iTerms, false);
			npchar.quest.Caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

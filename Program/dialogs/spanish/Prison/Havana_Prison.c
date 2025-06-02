// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Habla, estoy escuchando";
			link.l1 = "Me equivoqué. Adiós.";
			link.l1.go = "Exit";
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_4")
			{
				link.l1 = "Oficial, me ha llamado la atención que un oficial del navío 'Cantavro' está detenido aquí. ¿Es correcto?";
                link.l1.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_8")
			{
				link.l1 = "Regresé para preguntar nuevamente por don Lope, oficial. ¿Ya ha recibido sus órdenes de liberación?";
                link.l1.go = "Mtraxx_5";
			}
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "Mtraxx":
            dialog.text = "¿El oficial de 'Cantavro'? ¿Don Lope Montoro? Sí, está detenido aquí. ¿Qué te importa a ti?";
			link.l1 = "Me gustaría obtener un permiso para visitarlo.";
			link.l1.go = "Mtraxx_1";
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Lope"), "questmarkmain");
		break;
		
		case "Mtraxx_1":
            dialog.text = "Le ruego me disculpe, pero ¿con qué motivo?";
			link.l1 = "Es solo un asunto personal. Lo conocí en Europa y me sorprendieron las noticias sobre su encarcelamiento y los chismes que se esparcieron por todo el pueblo. Me gustaría hablar con él.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
            dialog.text = "Mm...";
			link.l1 = "Oficial, tal vez podría... 'agradecerle' por permitirme visitarlo.";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            dialog.text = "No hay necesidad de eso. Te permito reunirte con don Montoro. Los guardias te dejarán pasar.";
			link.l1 = "¡Gracias!";
			link.l1.go = "Mtraxx_4";
		break;
		
		case "Mtraxx_4":
			DialogExit();
            pchar.questTemp.jailCanMove = true;
			pchar.questTemp.Mtraxx = "jewelry_5";
		break;
		
		case "Mtraxx_5":
            dialog.text = "En efecto, mi orden es entregar a don Lope Montoro directamente al comandante. Pero supongo que no saldrá de la celda durante un par de semanas. Sin embargo, puedes ir a verlo mientras aún esté aquí.";
			link.l1 = "Gracias, oficial, por eso estoy aquí.";
			link.l1.go = "Mtraxx_6";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtraxx_6":
            DialogExit();
            pchar.questTemp.jailCanMove = true;
			pchar.questTemp.Mtraxx = "jewelry_9";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

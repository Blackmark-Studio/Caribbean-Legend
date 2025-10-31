// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = "Habla, estoy escuchando";
		link.l1 = "Me equivoqué. Adiós.";
		link.l1.go = "Exit";
		/* //--> Бремя гасконца
		if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
		{
			link.l1 = "Oficial, he oído que hay un hombre llamado Folke Deluc en su prisión. ¿Hay algo que pueda hacer para liberarlo?";
			link.l1.go = "Sharlie";
		}
		if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
		{
			link.l1 = "Oficial, soy yo de nuevo sobre el prisionero Folke Deluc. He comprado los derechos de su deuda y quiero que este hombre sea liberado y entregado a mí. Aquí están sus documentos de deuda, échales un vistazo.";
			link.l1.go = "Sharlie_3";
		}
		//<-- Бремя гасконца */

		//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
		if (CheckAttribute(pchar, "questTemp.Del_Deluck"))
		{
			link.l1 = "Buenas tardes, oficial. Quiero preguntar por mi tripulante...";
			link.l1.go = "Del_Deluck";
		}
		if (CheckAttribute(pchar, "questTemp.Del_DeluckSvoboda"))
		{
			link.l1 = "Aquí están los papeles, ahora libera a mi hombre.";
			link.l1.go = "Del_DeluckSvoboda";
		}
		//<-- Миниквест "Делюк"
		break;

	//--> Бремя гасконца
	case "Sharlie":
		DelLandQuestMark(npchar);
		dialog.text = "Ah, ¿ese marinero? Había tomado prestada una suma significativa de nuestro banquero, no la devolvió e incluso intentó escapar. Pero lo encontraron rápidamente. Desde entonces ha estado bajo arresto y se quedará aquí hasta que pague su deuda.";
		link.l1 = "¿Hm. Y cómo lo hará mientras esté en prisión?";
		link.l1.go = "Sharlie_1";
		break;

	case "Sharlie_1":
		dialog.text = "No me importa, monsieur.";
		link.l1 = "Gracioso... ¿Y cuánto debe esta pobre alma?";
		link.l1.go = "Sharlie_2";
		break;

	case "Sharlie_2":
		dialog.text = "No lo sé. Pregúntale al banquero y él te dará detalles.";
		link.l1 = "Ya veo, gracias por su información, oficial.";
		link.l1.go = "exit";
		pchar.questTemp.Sharlie = "bankskiper";
		LocatorReloadEnterDisable("Fortfrance_town", "reload8_back", false);
		AddLandQuestMark(characterFromId("FortFrance_usurer"), "questmarkmain");
		break;

	case "Sharlie_3":
		Log_Info("Has entregado documentos de débito");
		PlaySound("interface\important_item.wav");
		RemoveItems(pchar, "letter_open", 1);
		DelLandQuestMark(npchar);
		dialog.text = "Mm. Todos son correctos. ¿De verdad quieres que libere a ese prisionero?";
		link.l1 = "Sí. Necesito que salde la deuda y sé cómo puede hacerlo.";
		link.l1.go = "Sharlie_4";
		break;

	case "Sharlie_4":
		dialog.text = "Está bien, no tengo razones para negarte. Deluc será traído aquí pronto. Pero debo advertirte que este zorro escapará a la primera oportunidad, así que no te hagas ilusiones sobre él.";
		link.l1 = "Lo entiendo, oficial. Y ahora quiero llevarme a mi deudor.";
		link.l1.go = "Sharlie_5";
		break;

	case "Sharlie_5":
		dialog.text = "Sí, claro. ¡Sargento! ¡Traiga al prisionero! ¡Folke Deluc, parece que ahora tiene un nuevo amo!";
		link.l1 = "...";
		link.l1.go = "Sharlie_6";
		break;

	case "Sharlie_6":
		DialogExit();
		// создаем штурмана
		sld = InitFolke("Folke", "Deluc");
		pchar.questTemp.Sharlie = "takeskiper";	
		ForceHeroAutolevel(sld);
		AddDialogExitQuestFunction("Del_Turma");
	break;
	//<-- Бремя гасконца

	//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
	case "Del_Deluck":
		DelLandQuestMark(npchar);
		dialog.text = "¡Ja! Te digo, los chismes sobre tu situación entretendrán a Saint-Pierre por mucho tiempo. Pero no te lo tomes personalmente, Capitán. Claramente eres víctima de la mala fortuna. Entra y no te preocupes: tu navegante no se escapará de esta conversación, ¡ja ja!";
		link.l1 = "Divertidísimo. Gracias, oficial.";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Del_prison");
	break;

	case "Del_DeluckSvoboda":
		dialog.text = "Entendido, Capitán. Procederemos en consecuencia.";
		link.l1 = "...";
		link.l1.go = "Del_DeluckSvoboda_2";
		Log_Info("Has entregado documentos de deuda");
		PlaySound("interface\important_item.wav");
		RemoveItems(pchar, "letter_open", 1);
		DelLandQuestMark(npchar);
		break;

	case "Del_DeluckSvoboda_2":
		DialogExit();
		DeleteAttribute(pchar, "questTemp.Del_DeluckSvoboda");
		
		sld = CharacterFromID("Folke");
		sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
		sld.dialog.currentnode = "Del_Folke_10";
		
		AddDialogExitQuestFunction("Del_Turma");
	break;
		//<-- Миниквест "Делюк"
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool bOk;
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat("Adelante, ¿qué quieres?", "Justo estábamos hablando de eso. Debes haberlo olvidado...", "Esta es la tercera vez hoy que hablas de alguna pregunta...", "Escucha, esto es una tienda. La gente compra cosas aquí. ¡No me molestes!", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Sabes, " + NPChar.name + ", tal vez la próxima vez.", "Ah, lo he olvidado por alguna razón...", "Sí, en verdad es la tercera vez...", "Mm, no lo haré...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		if (CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
		{
			link.l1 = "Escucha, " + npchar.name + ", ¿has visto a Miguel Dichoso en Isla Tesoro últimamente?";
			link.l1.go = "tieyasal";
		}
		// Addon 2016-1 Jason пиратскаЯ линейка
		if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_start")
		{
			link.l1 = "" + npchar.name + ", estoy aquí en nombre de Marcus Tyrex. Dijo que necesitabas un hombre para un trabajo.";
			link.l1.go = "mtraxx";
		}
		if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_win")
		{
			link.l1 = "" + npchar.name + ", el 'Rosbohom' fue encontrado y capturado. ¿Deberíamos comenzar a descargar y contar?";
			link.l1.go = "mtraxx_5";
		}
		break;

	// город майя
	case "tieyasal":
		dialog.text = "Sí, así es. Compró suministros para su barco aquí. Por cierto, ha sido muy recientemente. Literalmente se perdieron el uno al otro por unos días. Por cierto, podría todavía estar en este asentamiento. No espío para la gente, ya sabes. Pregunta un poco más y quién sabe, tal vez encuentres a tu don.";
		link.l1 = "Está bien. ¡Gracias por la información!";
		link.l1.go = "tieyasal_1";
		break;

	case "tieyasal_1":
		DialogExit();
		npchar.quest.tieyasal = "true";
		break;

	// Addon 2016-1 Jason пиратскаЯ линейка
	case "mtraxx":
		pchar.quest.Mtraxx_PasqualeLate.over = "yes";
		dialog.text = "¡Precisamente! Es bueno que hayas llegado a tiempo. Ahora déjame contarte el meollo del asunto...";
		link.l1 = "Soy todo oídos.";
		link.l1.go = "mtraxx_1";
		break;

	case "mtraxx_1":
		string sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")));
		dialog.text = "En este momento un " + sTemp + ", el navío holandés llamado 'Rosbohom', está llegando a nuestras aguas junto con un barco de escolta. Está cargado de ébano y navega desde Willemstad para encontrarse con otro barco de escolta y asegurar un viaje seguro a Europa. No sé qué ruta toma, si a través de Saint-Martin o a través de aguas españolas, pero sé las coordenadas de su punto de encuentro.\nTu misión es encontrar a los holandeses allí, abordar al comerciante y traerme su cargamento. Pagaré tan pronto como se entregue el cargamento.";
		link.l1 = "Entendido. ¿Hora y lugar?";
		link.l1.go = "mtraxx_2";
		break;

	case "mtraxx_2":
		int i = sti(pchar.questTemp.Mtraxx.Crdn.minN2) - 10;
		int n = sti(pchar.questTemp.Mtraxx.Crdn.minW2) - 10;
		dialog.text = "" + sti(pchar.questTemp.Mtraxx.Crdn.degN) + " " + i + " Norte y " + sti(pchar.questTemp.Mtraxx.Crdn.degW) + " " + n + " Oeste. Debe estar en algún lugar al sur o suroeste de Isla Tesoro, no soy bueno en esto, no soy marinero, pero tú sí. Tienes alrededor de cinco días para hacer el trabajo.";
		link.l1 = "Anotado... Lo entiendo. ¡No perdamos tiempo entonces!";
		link.l1.go = "mtraxx_3";
		break;

	case "mtraxx_3":
		dialog.text = "Que tengas buen viento, capitán. Te estaré esperando a ti y a la carga.";
		link.l1 = "...";
		link.l1.go = "mtraxx_4";
		break;

	case "mtraxx_4":
		DialogExit();
		pchar.questTemp.Mtraxx = "pasq_convoy";
		i = sti(pchar.questTemp.Mtraxx.Crdn.minN2) - 10;
		n = sti(pchar.questTemp.Mtraxx.Crdn.minW2) - 10;
		AddQuestRecord("Roger_4", "3");
		AddQuestUserData("Roger_4", "sShip", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name") + "Gen")));
		AddQuestUserData("Roger_4", "sdegN", sti(pchar.questTemp.Mtraxx.Crdn.degN));
		AddQuestUserData("Roger_4", "sminN", i);
		AddQuestUserData("Roger_4", "sdegW", sti(pchar.questTemp.Mtraxx.Crdn.degW));
		AddQuestUserData("Roger_4", "sminW", n);
		SetFunctionTimerCondition("Mtraxx_PasqualeTimeConvoy", 0, 0, 6, false);
		SetFunctionTimerCondition("Mtraxx_PasqualeConvoyOver", 0, 0, 7, false);
		break;

	case "mtraxx_5":
		iTotalTemp = GetSquadronGoods(pchar, GOOD_EBONY);
		if (iTotalTemp < 1)
		{
			dialog.text = "¿Me estás tomando el pelo, joven? ¡Tus bodegas no tienen ni una sola tabla de ébano! ¡Esto es un engaño insolente! ¡Fuera de aquí! ¡Informaré a Marcus de esto! ¡Fuera!!!";
			link.l1 = "Ajá...";
			link.l1.go = "mtraxx_6";
			break;
		}
		if (iTotalTemp < makeint(sti(pchar.questTemp.Mtraxx.Crdn.Ebony) / 4))
		{
			dialog.text = "¿Me estás tomando el pelo, chico? ¡Tu bodega tiene solo unas pocas astillas de ébano! ¡Esto es un engaño insolente! ¡Fuera de aquí! ¡Voy a informar a Marcus de esto! ¡¡¡Fuera!!!";
			link.l1 = "Mm...";
			link.l1.go = "mtraxx_6";
			break;
		}
		if (iTotalTemp < sti(pchar.questTemp.Mtraxx.Crdn.Ebony) - 20)
		{
			dialog.text = "El Rosbohom tenía al menos " + FindRussianQtyString(sti(pchar.questTemp.Mtraxx.Crdn.Ebony)) + " de ébano. ¿Por qué me trajiste menos?";
			link.l1 = "Bueno... tuve que deshacerme de una parte durante la pelea. Además de las ratas, malditas sean...";
			link.l1.go = "mtraxx_7";
			break;
		}
		dialog.text = "Muy bien. ¿Cuánto tienes? ¿" + FindRussianQtyString(iTotalTemp) + "? ¡Espléndido! Te pagaré 150 pesos por cada pieza.";
		link.l1 = "¿150 piezas de a ocho? Supongo que ese ébano cuesta mucho más.";
		link.l1.go = "mtraxx_10";
		break;

	case "mtraxx_6":
		DialogExit();
		pchar.questTemp.Mtraxx = "pasq_angry";
		DoQuestReloadToLocation("Pirates_town", "reload", "reload6", "");
		AddQuestRecord("Roger_4", "8");
		CloseQuestHeader("Roger_4");
		QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;

	case "mtraxx_7":
		dialog.text = "¿Ratas? Bueno, bueno... Pero está bien. 100 pesos por pieza y puedes irte.";
		link.l1 = "¿Sólo 100 pesos? ¡Esto es un robo!";
		link.l1.go = "mtraxx_8";
		break;

	case "mtraxx_8":
		AddMoneyToCharacter(pchar, iTotalTemp * 100);
		RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
		dialog.text = "El robo es tu oficio, capitán, yo soy un simple comerciante. Toma tu dinero y no sigamos discutiendo, ya has hecho una buena suma vendiendo parte de mi carga en otro lugar.";
		link.l1 = "¡Que te parte un rayo, entonces!";
		link.l1.go = "mtraxx_9";
		break;

	case "mtraxx_9":
		DialogExit();
		pchar.questTemp.Mtraxx = "pasq_fail";
		AddQuestRecord("Roger_4", "8");
		CloseQuestHeader("Roger_4");
		QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;

	case "mtraxx_10":
		dialog.text = "Y tienes razón, capitán, pero primero, intenta vender bienes robados y veré cuánto te pagarán otros mercaderes por ellos. El precio que te ofrezco es muy alto. Segundo, fue mi pista, nunca encontrarías esa caravana por tu cuenta. Además había otros objetos de valor y bienes en ella y no los estoy reclamando. Tercero, te daré los mejores créditos a los ojos de Marcus Tyrex y esto cuesta mucho, créeme. Y finalmente, cuarto, un pobre comerciante debe ganarse la vida de alguna manera.";
		link.l1 = "¡Vaya! Debo retirarme ante tales argumentos " + npchar.name + ". Vamos a contar.";
		link.l1.go = "mtraxx_11";
		break;

	case "mtraxx_11":
		AddMoneyToCharacter(pchar, iTotalTemp * 150);
		RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
		dialog.text = "Espléndido. Toma tus monedas. Fue un placer. Asegúrate de visitar mi tienda de vez en cuando. ¡Que tengas fortuna en el mar!";
		link.l1 = "Y tú en tu comercio...";
		link.l1.go = "mtraxx_12";
		break;

	case "mtraxx_12":
		DialogExit();
		pchar.questTemp.Mtraxx = "pasq_complete";
		AddQuestRecord("Roger_4", "9");
		pchar.quest.mtr_pasq_fin.win_condition.l1 = "location";
		pchar.quest.mtr_pasq_fin.win_condition.l1.location = "Pirates_town";
		pchar.quest.mtr_pasq_fin.function = "Mtraxx_PasqualeJeffry";
		bDisableFastReload = true;
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

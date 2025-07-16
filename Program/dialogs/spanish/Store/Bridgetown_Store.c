// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Adelante, ¿qué quieres?","Justo estábamos hablando de eso. Debes haberlo olvidado...","Esta es la tercera vez hoy que hablas de alguna pregunta...","Escucha, esto es una tienda. La gente compra cosas aquí. ¡No me molestes!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabes, "+NPChar.name+" , tal vez la próxima vez.","Correcto, lo he olvidado por alguna razón...","Sí, realmente es la tercera vez...","Hm, no lo haré...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Escucha, un pajarito me dijo que los precios de la madera roja y el cacao en Belice van a dispararse muy pronto. He hecho un buen trato recientemente y he llenado mi bolsa de doblones, je-je... Me gustaría adquirir algo de esta mercancía. ¿Puedo contar con un descuento?";
                link.l1.go = "StoreDone";
            }
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados1")
			{
				link.l1 = "Un galeón llamado 'Admirable' ha atracado recientemente en tu colonia bajo el mando del capitán Gaius Marchais. Dime, ¿podría haber abastecido aquí con municiones o mercancías para revender?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "StoreDone":
			dialog.text = "Bueno, sir, si el lote es realmente grande, entonces, por supuesto, podemos discutir un descuento razonable.";
			link.l1 = "¡Maravilloso! Escuché que un nuevo filibote debería salir a la venta en el astillero cualquier día de estos. Esperaré y compraré ese barco. ¡Aunque he despojado todos los cañones de mi bergantín, todavía no hay suficiente espacio en mi bodega para todas estas mercancías! ¡Pasaré más tarde!";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-11");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "¡Ja! Recuerdo a ese tipo extraño. Confiaba en un chisme tonto de que Guadalupe necesitaría desesperadamente vainilla porque una gran caravana de comerciantes europeos haría una parada allí para comprar tantas especias como pudieran llevar. \nEscucho tales tonterías cada mes, pero Marchais se lo tomó muy en serio. Pasó una semana aquí, me dijo que reuniera suficiente vainilla para llenar sus bodegas de carga.\nParece que gastó cada moneda en esto. Me siento mal por ese hombre, pero no puedo detener a los hombres que quieren volverse locos si así lo desean.";
			link.l1 = "¿Entonces, podría estar en Guadalupe ahora mismo?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Lo más probable. Porque seguirá esperando a sus fantasiosos 'mercaderes' hasta la segunda venida de Cristo y solo perderá dinero vendiendo vainilla. Si es sabio, se quedará en Basse-Terre hasta que la demanda de vainilla se dispare o hasta que descubra con certeza otro lugar donde se necesite más.";
			link.l1 = "¡Sí. Gracias, me has ayudado mucho!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "14");
			pchar.questTemp.Guardoftruth = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1 = "location";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1.location = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.function = "GuardOT_CreateTwoShips";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

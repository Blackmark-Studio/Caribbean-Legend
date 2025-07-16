// старпом Акулы - Лейтон Декстер
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (npchar.quest.meeting == "0")
		{
			dialog.text = "¿Qué quieres, muchacho? Habla con Shark, él está a cargo aquí.";
			link.l1 = "¿Puedo al menos saludarte o eso va contra las reglas?";
			link.l1.go = "meeting";
			npchar.quest.meeting = "1";
		}
		else
		{
			if (CheckAttribute(npchar, "quest.map"))
			{
				link.l2 = "Layton, Shark me dijo que tienes un mapa de la Isla. ¿Lo estás vendiendo?";
				link.l2.go = "map";
			}
			dialog.text = "A-ah, " + GetFullName(pchar) + ". ¿Tienes asuntos conmigo o solo quieres hablar de nuevo? Si es así, trae una botella de ron la próxima vez, ¡ja-ja!";
			link.l1 = "No, no tengo ningún asunto particular para ti. Traeré ron la próxima vez, solo para ti.";
			link.l1.go = "exit";
		}
		NextDiag.TempNode = "First time";
		break;

	case "meeting":
		dialog.text = "¡Ja! Eres un bromista, ¿verdad, chico? Está bien... Mi nombre es Layton Dexter, soy el segundo al mando de Shark y hoy en día soy su suplente en esta maldita Ciudad de Barcos Abandonados. Mientras tanto, vendo provisiones e intento sacarle dinero a ese vago Fazio.";
		link.l1 = "Y mi nombre es " + GetFullName(pchar) + "¡Encantado de conocerte!";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	// Акула погиб по варианту N
	case "admiral":
		dialog.text = "Supongo que ya has oído que Steven está muerto. Los Narvales lo hicieron.";
		link.l1 = "Tienes razón, lo sé... ¿Y qué, ahora eres el almirante?";
		link.l1.go = "admiral_1";
		AddQuestRecord("SharkHunt", "28");
		CloseQuestHeader("SharkHunt");
		bDisableFastReload = false; // belamour legendary edition
		break;

	case "admiral_1":
		dialog.text = "Exactamente. Chad desertó a los Narvales, Steven está muerto y por lo tanto, siendo yo el segundo al mando, naturalmente, ahora soy el almirante. ¿Objeciones?";
		link.l1 = "No. No hay objeciones.";
		link.l1.go = "admiral_2";
		break;

	case "admiral_2":
		dialog.text = "Bien. Escuchemos tus preguntas.";
		link.l1 = "¿Vas a vengar la muerte de Steven contra los Narvales?";
		link.l1.go = "admiral_3";
		break;

	case "admiral_3":
		dialog.text = "¿Quieres decir, que les declararé la guerra? No. Hay mejores maneras de hacerles pagar. Primero triplicaré el precio que pagan por las provisiones\nSi atacan el 'San Augustine' les daremos el infierno. Luego, voy a negociar con los Rivados. Por supuesto, no podemos confiar en esos sucios negros y tienen un rencor contra nosotros por la muerte de su hechicero, pero cualquier problema se puede suavizar con ron y comida.";
		link.l1 = "Ya veo. Está bien, Layton, tengo que irme...";
		link.l1.go = "admiral_4";
		break;

	// нода пересечения
	case "admiral_4":
		dialog.text = "Espera. ¿Steven me dijo que estás intentando dejar la Ciudad de los Barcos Abandonados de alguna manera y volver aquí en un barco?";
		link.l1 = "Eso es el plan.";
		link.l1.go = "admiral_5";
		break;

	case "admiral_5":
		dialog.text = "Toma estas direcciones de navegación. Usándolas, podrás regresar aquí por mar en una sola pieza. Es decir: no encallarás en los arrecifes, no te arrastrará la corriente, y tu barco no se estrellará contra los otros naufragios en el borde exterior\nSin ellas, o no encontrarás un paso o tu barco se unirá a sus hermanas aquí. Recuerda que debes usar una embarcación pequeña con poco calado para pasar los bajíos. Lugre, goleta, bergantín, bric... nada más grande que una de cuarta clase. ¿Entendido?";
		link.l1 = "¡Sí, lo hago. Gracias! Eso es exactamente lo que necesito.";
		link.l1.go = "admiral_6";
		break;

	case "admiral_6":
		GiveItem2Character(pchar, "LSC_navigation_map");
		dialog.text = "No olvides llenar tu bodega con provisiones. Te las venderé a buen precio. No le muestres este documento a nadie, nuestra base debe permanecer en secreto. Te estoy dando este documento solo porque el mismo Steven iba a dártelo, y eres amigo de Jan Svenson.";
		link.l1 = "No te preocupes por eso. ¡Gracias de nuevo y nos vemos por ahí!";
		link.l1.go = "exit";
		NextDiag.TempNode = "Dexter_wait";
		AddQuestRecord("LSC", "5");
		CloseQuestHeader("SharkHunt");
		bDisableFastReload = false; // belamour legendary edition
		// убираем квестовые предметы
		sld = ItemsFromID("key_capper");
		sld.price = 10;
		if (CheckCharacterItem(pchar, "letter_chad"))
			RemoveItems(pchar, "letter_chad", 1);
		break;

	case "Dexter_wait":
		dialog.text = "¿Tienes algún progreso en escapar de la Ciudad de los Barcos Abandonados, " + pchar.name + "?";
		link.l1 = "Aún no hay progreso, Layton. Estoy trabajando en ello.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Dexter_wait";
		break;

	// Акула погиб по варианту M
	case "admiral_7":
		dialog.text = "Aquí estás, " + pchar.name + "Tengo algunas cosas que discutir contigo.";
		link.l1 = "Según entendí, has tomado el puesto de Steven después de su muerte. ¿Entonces ahora eres el almirante?";
		link.l1.go = "admiral_8";
		break;

	case "admiral_8":
		dialog.text = "Exactamente. Siendo el segundo al mando, ahora soy el almirante. ¿Objeciones?";
		link.l1 = "Sin objeciones. Tienes todo el derecho a mantener esta posición.";
		link.l1.go = "admiral_9";
		break;

	case "admiral_9":
		dialog.text = "Me alegra que nos entendamos. Avísame si necesitas algo.";
		link.l1 = "¿Vas a vengarte de los Narvales por la muerte de Steven?";
		link.l1.go = "admiral_10";
		break;

	case "admiral_10":
		dialog.text = "¿Quieres decir, que declararé la guerra entonces? No. Hay mejores maneras de hacerles pagar. Triplicaré el precio que pagan por las provisiones.\nSi atacan 'San Augustine', les daremos el infierno. Además, ahora tenemos buenas relaciones con los Rivados, así que los Narvales no se arriesgarán a actuar tontamente.";
		link.l1 = "Ya veo. ¿Quieres contarme algo más? ¿O puedo irme ahora?";
		link.l1.go = "admiral_4";
		break;

	case "plan":
		PlaySound("Voice\Spanish\LSC\Layton Dexter-07");
		dialog.text = "Lo hago. Solo veo una manera de atraparlos a los Narvales. No es perfecto, pero no veo otra alternativa. Los atacaremos desde dos direcciones. Un grupo de valientes canallas en botes largos abordará el 'Ceres Smithy', mientras que un segundo grupo junto con los Rivados asaltará el 'Esmeralda'. Esto los eliminará por completo o los hará huir al 'San Gabriel'. El segundo escenario es el más probable, San Gabriel es una posición altamente fortificada y sitiarla lleva mucho tiempo. Pero de cualquier manera, ganaremos.";
		link.l1 = "";
		link.l1.go = "plan_1";
		break;

	case "plan_1": // ноду Акуле
		DialogExit();
		npchar.greeting = "dexter_1";
		sld = characterFromId("Dodson");
		sld.dialog.currentnode = "whyskey_final_3";
		LAi_SetActorType(sld);
		LAi_ActorSetHuberMode(sld);
		LAi_CharacterEnableDialog(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
		NextDiag.CurrentNode = "plan_2";
		break;

	case "plan_2":
		dialog.text = "Estamos esperando los resultados de tu conversación con Donald Greenspen. Es un asunto muy importante, así que no pierdas tiempo.";
		link.l1 = "¡Estoy en camino!";
		link.l1.go = "exit";
		NextDiag.TempNode = "plan_2";
		break;

	case "map":
		dialog.text = "Sí, tengo el mapa. ¿Te gustaría comprarlo? Eres bienvenido a hacerlo, si lo deseas. Será tuyo por solo doscientos doblones.";
		link.l1 = "¿Qué tal pesos?";
		link.l1.go = "map_1";
		break;

	case "map_1":
		dialog.text = "No. Quiero oro. No habrá regateo.";
		if (GetCharacterItem(pchar, "gold_dublon") >= 200)
		{
			link.l1 = "Bien. Toma tu oro, estoy de acuerdo.";
			link.l1.go = "map_2";
		}
		link.l2 = "No tengo tanto oro. Quizás más tarde...";
		link.l2.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "map_2":
		RemoveItems(pchar, "gold_dublon", 200);
		PlaySound("interface\important_item.wav");
		Log_Info("Has recibido un mapa de la Ciudad de los Barcos Abandonados");
		GiveItem2Character(pchar, "map_LSC");
		dialog.text = "¡Buen trato, muchacho! Toma tu mapa. Vale el precio: me arrastré por toda la Ciudad durante una semana entera para dibujarlo, así que, de hecho, te lo he vendido bastante barato.";
		link.l1 = "¿Barato?! Claro. Bueno, gracias de todos modos.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		DeleteAttribute(npchar, "quest.map");
		break;

	// геймовер диким геймерам за издевательство над игрой
	case "LSC_GameOverPrison":
		dialog.text = "¡Alto ahí, camarada! Sí, Shark tenía razón, este tipo se ha vuelto loco. Tantos hombres han muerto por su culpa... ¡Encadenadlo, muchachos, y echadlo en la bodega!";
		link.l1 = "...";
		link.l1.go = "LSC_GameOverPrison_1";
		break;

	case "LSC_GameOverPrison_1":
		DialogExit();
		DoQuestReloadToLocation("TartarusPrison", "quest", "prison4", "LSC_GameOverInPrison");
		break;

	case "return":
		dialog.text = "Steven me nombró almirante de la Ciudad en lugar de él - supongo que tú y él van a regresar juntos al Caribe. Yo me quedaré aquí y continuaré con el negocio, Steven y yo detestamos perder una base tan estupenda. Y quiero decirte que siempre serás un huésped bienvenido aquí.";
		link.l1 = "Gracias, Layton. Creo que regresaré a tu Isla con bastante frecuencia.";
		link.l1.go = "return_1";
		break;

	case "return_A":
		dialog.text = "Ah, mi viejo amigo " + GetFullName(pchar) + "¡Has logrado encontrar la Ciudad de los Barcos Abandonados usando las direcciones de navegación de Steven, ¿verdad? Estoy muy, muy contento de verte. Siempre eres un invitado bienvenido aquí.";
		link.l1 = "Gracias, Layton. Creo que regresaré a tu Ciudad con bastante frecuencia.";
		link.l1.go = "return_1";
		break;

		int iTrade = GetSquadronGoods(pchar, GOOD_FOOD) - GetCrewQuantity(pchar);
		int iMoney = 0;
	case "return_1":
		dialog.text = "Muy bien. ¿Tienes alguna comida para vender? Estoy listo para comprártela por el doble del precio habitual.";
		if (iTrade > 0)
		{
			link.l1 = "Sí, puedo venderte algunas provisiones.";
			link.l1.go = "trade";
		}
		link.l2 = "Desafortunadamente, no tengo nada que venderte en este momento.";
		link.l2.go = "return_2";
		npchar.quest.foodqty = 0; // предел затарки складов = 15 000
		break;

	case "return_2":
		dialog.text = "Lástima. No olvides traerlo la próxima vez - pagaré bien.";
		link.l1 = "Está bien. Trataré de no olvidarlo...";
		link.l1.go = "exit";
		NextDiag.TempNode = "head";
		break;

	case "trade":
		dialog.text = "¿Cuánto?";
		link.l1.edit = 4;
		link.l1 = "";
		link.l1.go = "trade_1";
		break;

	case "trade_1":
		iTemp = dialogEditStrings[4];
		int iMax = GetSquadronGoods(pchar, GOOD_FOOD) - GetCrewQuantity(pchar);
		if (iTemp <= 0 || iTemp > GetSquadronGoods(pchar, GOOD_FOOD))
		{
			dialog.text = "¡Maldita sea, estás completamente borracho, amigo! ¡Estoy impresionado! Ve a dormir un poco, negociaremos más tarde.";
			link.l1 = "Mm...";
			link.l1.go = "exit";
			break;
		}
		if (iTemp <= 50)
		{
			dialog.text = "No levantaré ni mi trasero de la silla por una cantidad tan miserable. ¡Tráeme más!";
			link.l1 = "Mm...";
			link.l1.go = "exit";
			break;
		}
		if (iTemp > iMax)
		{
			dialog.text = "¿Y cómo piensas navegar sin provisiones en tu barco, camarada? ¿Quieres que tus muchachos se mueran de hambre? Al menos mantén " + FindRussianQtyString(GetCrewQuantity(pchar)) + " por ti mismo.";
			link.l1 = "Mm, tienes razón.";
			link.l1.go = "exit";
			break;
		}
		if (iTemp >= 15000) // лесник
		{
			iTemp = (15000 - sti(npchar.quest.foodqty))
						dialog.text = "¡Vaya, amigo, eso es demasiado para nosotros! No podremos comerlo antes de que se pudra. Ahora mismo no puedo llevar más de " + iTemp + ".";
			link.l1 = "Lo que digas.";
			link.l1.go = "trade_3";
			break;
		}
		iMoney = (50 + hrand(5, "&Slayer")) * iTemp;
		dialog.text = "" + FindRussianQtyString(iTemp) + "¿Está bien? Te pagaré " + FindRussianMoneyString(iMoney) + "¿Trato?";
		link.l1 = "¡Claro! ¡Un placer hacer negocios contigo!";
		link.l1.go = "trade_2";
		link.l2 = "Hm. No, he cambiado de opinión.";
		link.l2.go = "exit";
		NextDiag.TempNode = "head";
		break;
	case "trade_3": // лесник
		iTemp = (15000 - sti(npchar.quest.foodqty))
			iMoney = (50 + hrand(5, "&Slayer")) * iTemp;
		dialog.text = "Trato. Te pagaré " + FindRussianMoneyString(iMoney) + " para las mercancías. ¿Es suficiente?";
		link.l1 = "¡Claro! ¡Buen comercio!";
		link.l1.go = "trade_4";
		link.l2 = "Hum. No, he cambiado de opinión.";
		link.l2.go = "exit";
		NextDiag.TempNode = "head";
		break;
	case "trade_4": // лесник
		iTemp = (15000 - sti(npchar.quest.foodqty))
			iMoney = (50 + hrand(5, "&Slayer")) * iTemp;
		AddMoneyToCharacter(pchar, iMoney);
		RemoveCharacterGoods(pchar, GOOD_FOOD, iTemp);
		npchar.quest.foodqty = sti(npchar.quest.foodqty) + iTemp;
		if (!CheckAttribute(pchar, "Achievment.LSCfood"))
			pchar.Achievment.LSCfood = iTemp;
		else
			pchar.Achievment.LSCfood = sti(pchar.Achievment.LSCfood) + iTemp;
		if (sti(pchar.Achievment.LSCfood) >= 20000)
			Achievment_Set("ach_CL_112");
		if (sti(npchar.quest.foodqty) >= 15000) // склады затарены на полгода
		{
			SetFunctionTimerCondition("LSC_ClearFoodStorage", 0, 0, 180, false);
			dialog.text = "¡Maldita sea, mis ojos! ¡Mi almacén está lleno! No necesitaré comprar provisiones por los próximos seis meses.";
			link.l1 = "Bien. Entonces, traeré el próximo cargamento de provisiones en seis meses.";
			link.l1.go = "exit";
			AddQuestRecord("LSC", "25");
		}
		else
		{
			dialog.text = "¡Estupendo! Tráeme más la próxima vez.";
			link.l1 = "¡Claro!";
			link.l1.go = "exit";
		}
		NextDiag.TempNode = "head";
		break;
	case "trade_2":
		iTemp = dialogEditStrings[4];
		iMoney = (50 + hrand(5, "&Slayer")) * iTemp;
		AddMoneyToCharacter(pchar, iMoney);
		RemoveCharacterGoods(pchar, GOOD_FOOD, iTemp);
		npchar.quest.foodqty = sti(npchar.quest.foodqty) + iTemp;
		if (!CheckAttribute(pchar, "Achievment.LSCfood"))
			pchar.Achievment.LSCfood = iTemp;
		else
			pchar.Achievment.LSCfood = sti(pchar.Achievment.LSCfood) + iTemp;
		if (sti(pchar.Achievment.LSCfood) >= 20000)
			Achievment_Set("ach_CL_112");
		if (sti(npchar.quest.foodqty) >= 15000) // склады затарены на полгода
		{
			SetFunctionTimerCondition("LSC_ClearFoodStorage", 0, 0, 180, false);
			dialog.text = "¡Estupendo! Mi almacén está lleno ahora. No necesitaré comprar víveres durante el próximo medio año.";
			link.l1 = "Bien. Entonces, te traeré la próxima carga de provisiones en seis meses.";
			link.l1.go = "exit";
			AddQuestRecord("LSC", "25");
		}
		else
		{
			dialog.text = "¡Estupendo! Tráeme más la próxima vez.";
			link.l1 = "¡Por supuesto!";
			link.l1.go = "exit";
		}
		NextDiag.TempNode = "head";
		break;

	case "head": // стандартный диалог Декстера-адмирала
		dialog.text = "A-ah, " + GetFullName(pchar) + "¡Encantado de verte! ¿Qué quieres?";
		if (iTrade > 0 && sti(npchar.quest.foodqty) < 15000)
		{
			link.l1 = "¿Quieres comprar algunas provisiones de mí?";
			link.l1.go = "trade";
		}
		link.l2 = "No es nada, solo quería saber cómo te iba.";
		link.l2.go = "exit";
		NextDiag.TempNode = "head";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}

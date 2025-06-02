// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool ok;
	int iTest;
	ref rColony;
	string sFrom_sea = "";
	switch (Dialog.CurrentNode)
	{
	case "quests":
		// регата
		if (CheckAttribute(pchar, "questTemp.Regata.Go") && !CheckAttribute(npchar, "quest.regatatalk"))
		{
			dialog.text = "¿Qué quieres? ¡Ajá, eres el participante de la regata! ¿Tengo razón?";
			link.l1 = "Exactamente, señor. Necesito registrarme aquí de acuerdo con las reglas.";
			link.l1.go = "Regata_check";
			break;
		}
		// регата
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué tipo de preguntas?","¿Qué quieres, "+GetAddress_Form(NPChar)+"?"),"Ya has intentado hacerme una pregunta "+GetAddress_Form(NPChar)+"... ","Has estado hablando de alguna cuestión por tercera vez hoy...","Mira, si no tienes nada que contarme sobre los asuntos del puerto, entonces no me molestes con tus preguntas.","block",1,npchar,Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión.","No tengo nada de qué hablar."),"No importa.","De hecho, ya es la tercera vez...","Lo siento, pero no estoy interesado en los asuntos del puerto por ahora.",npchar,Dialog.CurrentNode);
		link.l1.go = "exit";
		// Голландский гамбит
		if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
		{
			link.l1 = "Estoy navegando hacia Blueweld para vender un poco de pimentón. Dígame, señor, ¿tiene algún pasajero que se dirija a Blueweld? O al menos a Port-Royal. Sería estupendo ganar algo de dinero con un pasajero, podría ayudar a pagar el salario de la tripulación. Ya lo he reducido al mínimo, pero esos vagos bastardos todavía piden dinero...";
			link.l1.go = "PortofficeDone";
		}
		// Страж Истины
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados")
		{
			link.l1 = "Había un galeón llamado 'Admirable' cargado en Philipsburg bajo el mando de Gaius Marchais. Tenía que entregar aquí un cargamento de pimentón. ¿Puedes ayudarme a encontrar a este capitán?";
			link.l1.go = "guardoftruth";
		}
		// калеуче
		if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.garpiya"))
		{
			if (CheckAttribute(npchar, "questTemp.caleuche"))
			{
				link.l1 = "Quería preguntar sobre un jabeque con un nombre extraño.";
				link.l1.go = "caleuche_2";
			}
			else
			{
				link.l1 = "He oído que un jabeque perteneciente a un Capitán Jack... o Jackson visita a menudo su puerto. ¿Podría decirme dónde buscarlo?";
				link.l1.go = "caleuche";
			}
		}
		break;

	// Голландский гамбит
	case "PortofficeDone":
		dialog.text = "Desafortunadamente, no hay pasajeros para Blueweld ni para Port-Royal. Vuelve mañana o pasado mañana.";
		link.l1 = "Qué lástima. Adiós entonces.";
		link.l1.go = "exit";
		npchar.quest.HWICTalked = "true";
		pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter) + 1;
		AddQuestRecord("Holl_Gambit", "2-9");
		DelLandQuestMark(npchar);
		if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7)
		{
			AddQuestRecord("Holl_Gambit", "2-6");
			pchar.quest.GotoBridgetownOver.over = "yes"; // снять таймер
			DelMapQuestMarkCity("Bridgetown");
			pchar.questTemp.HWIC.Eng = "SeekVanBerg";
			pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
			pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
		}
		break;

	// регата
	case "Regata_check":
		iTest = FindColony(npchar.city);
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok) // проверка на наличие корабля в порту
		{
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Sentjons") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
				dialog.text = "Hm... Has roto las reglas de la regata y tengo que descalificarte. Lo siento. No participarás en el próximo viaje. Ya he preparado un despacho para Port-Royal.";
				link.l1 = "Eh... ¡qué lástima! Pero no puedo hacer nada aquí, fuiste demasiado vigilante. ¡Adiós!";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata");
				AddQuestRecord("Regata", "45");
				CloseQuestHeader("Regata");
			}
			else
			{
				pchar.questTemp.Regata.FourthTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime()); // истратил ГГ в часах на 1+2+3+4 переход
				dialog.text = "Puede que hayas notado, capitán, que la ciudad está bajo asedio. Esperamos que los españoles nos ataquen en cualquier momento y estamos movilizando nuestras fuerzas. Pero la regata sigue adelante\nVamos a registrarnos: capitán " + GetFullName(pchar) + ", el barco está, " + pchar.Ship.Name + "... El tiempo de la regata en horas es " + sti(pchar.questTemp.Regata.FourthTransitionTime) + ". Hecho, tu resultado está registrado, puedes continuar tu camino.";
				link.l1 = "Dime mi rango.";
				link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "Estás aquí pero no veo tu barco. ¿Dónde está?";
			link.l1 = "Lo siento, señor. Transferiré mi barco al puerto de inmediato.";
			link.l1.go = "exit";
		}
		break;

	case "Regata_info":
		int n = 1;
		string sTemp, sName, sShip;
		for (int i = 1; i <= 5; i++)
		{
			if (i == 1)
				sTemp = "a";
			if (i == 2)
				sTemp = "b";
			if (i == 3)
				sTemp = "c";
			if (i == 4)
				sTemp = "d";
			if (i == 5)
				sTemp = "e";
			if (pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FourthTransitionTime))
			{
				n++;
				sName = pchar.questTemp.Regata.AdversaryName.(sTemp);	  // имя ближайшего противника
				sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp); // его корабль
			}
		}
		if (n == 1)
		{
			dialog.text = "Ah, sí... Lo siento, estaba demasiado ocupado para eso. Tú eres el primero.";
			link.l1 = "Ya veo. Gracias por su información.";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "22");
		}
		else
		{
			if (n == 6)
			{
				dialog.text = "Ah, sí... Lo siento, estoy demasiado ocupado para eso. Eres el último.";
				link.l1 = "Ya veo. Gracias por tu información.";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "27");
			}
			else
			{
				if (n == 2)
				{
					dialog.text = "Ah, sí... Lo siento, estoy demasiado ocupado para eso. Eres el segundo. Solo hay un capitán que te supera. Su nombre es " + sName + " en el barco " + sShip + ".";
					link.l1 = "Ya veo. Gracias por tu información.";
					link.l1.go = "exit";
					AddQuestRecord("Regata", "23");
				}
				else
				{
					dialog.text = "Ah, sí... Lo siento, estoy demasiado ocupado para eso. Tu rango es " + n + " . Tu oponente más cercano es " + sName + " en el barco " + sShip + ".";
					link.l1 = "Ya veo. Gracias por tu información.";
					link.l1.go = "exit";
					if (n == 3)
						AddQuestRecord("Regata", "24");
					if (n == 4)
						AddQuestRecord("Regata", "25");
					if (n == 5)
						AddQuestRecord("Regata", "26");
				}
			}
		}
		AddCharacterExpToSkill(pchar, "Sailing", 50); // навигация
		AddCharacterExpToSkill(pchar, "Defence", 30); // защита
		AddCharacterExpToSkill(pchar, "Repair", 30);  // починка
		AddCharacterExpToSkill(pchar, "Fortune", 30); // везение
		AddCharacterExpToSkill(pchar, "Sneak", 30);	  // скрытность
		npchar.quest.regatatalk = "true";
		pchar.questTemp.Regata.Bridgetown = "true"; // отметка Бриджтауна
		pchar.quest.Regata_Check1.win_condition.l1 = "location";
		pchar.quest.Regata_Check1.win_condition.l1.location = "Curacao";
		pchar.quest.Regata_Check1.function = "RegataCheck"; // проверка 1
		pchar.quest.Regata_Check2.win_condition.l1 = "location";
		pchar.quest.Regata_Check2.win_condition.l1.location = "Caracas";
		pchar.quest.Regata_Check2.function = "RegataCheck"; // проверка 2
		pchar.quest.Regata_Check3.win_condition.l1 = "location";
		pchar.quest.Regata_Check3.win_condition.l1.location = "PortoBello";
		pchar.quest.Regata_Check3.function = "RegataCheck"; // проверка 3
		pchar.quest.Regata_Check.win_condition.l1 = "location";
		pchar.quest.Regata_Check.win_condition.l1.location = "Jamaica";
		pchar.quest.Regata_Check.function = "RegataCheck"; // проверка 4
		pchar.questTemp.Regata.AttackIsland = "Curacao";
		pchar.questTemp.Regata.AttackNation = HOLLAND;
		pchar.quest.Regata_Attack.win_condition.l1 = "location";
		pchar.quest.Regata_Attack.win_condition.l1.location = "Curacao";
		pchar.quest.Regata_Attack.function = "RegataAttack_Brigantine";
		pchar.quest.Regata_Attack1.win_condition.l1 = "location";
		pchar.quest.Regata_Attack1.win_condition.l1.location = "Curacao";
		pchar.quest.Regata_Attack1.function = "RegataAttack_Corvette"; // третья засада
		pchar.quest.Regata_Hunter.win_condition.l1 = "location";
		pchar.quest.Regata_Hunter.win_condition.l1.location = "Barbados";
		pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter"; // ДУ у Барбадоса
		pchar.quest.Regata_Finish.win_condition.l1 = "location";
		pchar.quest.Regata_Finish.win_condition.l1.location = "Jamaica";
		pchar.quest.Regata_Finish.function = "RegataFinishSea";
		pchar.quest.Regata_Finish1.win_condition.l1 = "location";
		pchar.quest.Regata_Finish1.win_condition.l1.location = "Portroyal_town";
		pchar.quest.Regata_Finish1.function = "RegataFinishTown"; // финиш регаты
		// ситуации
		pchar.quest.Regata_Siege.win_condition.l1 = "location";
		pchar.quest.Regata_Siege.win_condition.l1.location = "Bridgetown_town";
		pchar.quest.Regata_Siege.function = "RegataSiegeOfficer"; // на квест по вывозу жителей
		break;
	// регата

	// Страж Истины
	case "guardoftruth":
		dialog.text = "Sí, este galeón estuvo aquí, fue despojado de sus bienes y luego dejó nuestro puerto. Información sobre su destino... hm... nada, no hay nada. Lo siento, pero no hay nada que pueda hacer.";
		link.l1 = "Ya veo. Qué lástima... Seguiré buscándolo.";
		link.l1.go = "guardoftruth_1";
		break;

	case "guardoftruth_1":
		DialogExit();
		AddQuestRecord("Guardoftruth", "13");
		pchar.questTemp.Guardoftruth = "barbados1";
		break;

	// калеуче
	case "caleuche":
		dialog.text = "Señor, necesito el nombre exacto del barco. Tenemos montones de Jacks y Jacksons pasando por nuestro puerto. Entonces, ¿cuál es el nombre?";
		link.l1 = "";
		Link.l1.edit = 2;
		link.l1.go = "caleuche_name";
		link.l2 = "El problema es que no sé el nombre de su vieja bañera. Es extraño, alguna mujer pájaro, nacida...";
		link.l2.go = "caleuche_1";
		break;

	case "caleuche_1":
		dialog.text = "Señor, vaya a contar sus historias y acertijos a la taberna, aquí tenemos un establecimiento serio. O me dice el nombre de ese jabeque, o deje de molestarme en mi trabajo.";
		link.l1 = "Está bien, intentaré averiguarlo.";
		link.l1.go = "exit";
		npchar.questTemp.caleuche = "true";
		break;

	case "caleuche_2":
		dialog.text = "¿Entonces? ¿Tiene el nombre del barco? Estoy escuchando.";
		link.l1 = "";
		Link.l1.edit = 2;
		link.l1.go = "caleuche_name";
		break;

	case "caleuche_name":
		if (GetStrSmallRegister(dialogEditStrings[2]) == "harpy")
		{
			dialog.text = "¿'Harpy'? Por supuesto, conozco ese xebec. Su capitán es Reginald Jackson. Pero no había estado en Bridgetown por mucho tiempo. Escuché que ahora trabaja para la Compañía Holandesa de las Indias Occidentales. Así que deberías buscarlo en Willemstad.";
			link.l1 = "¡Muchas gracias! Me has ayudado mucho.";
			link.l1.go = "caleuche_3";
		}
		else
		{
			dialog.text = "Lo siento, pero eso no me suena. ¿Está seguro de que su capitán ha estado alguna vez aquí, en Bridgetown?";
			link.l1 = "Estoy seguro. Muy bien, tal vez se me ocurra algo ...";
			link.l1.go = "exit";
		}
		break;

	case "caleuche_3":
		DialogExit();
		AddQuestRecord("Caleuche", "18");
		pchar.questTemp.Caleuche.Garpiya = "gwik";
		npchar.quest.garpiya = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

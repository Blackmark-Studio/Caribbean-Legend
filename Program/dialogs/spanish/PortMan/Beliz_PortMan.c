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
			dialog.text = "¿Qué quieres? ¡Ajá, eres el participante de la regata! ¿Estoy en lo cierto?";
			link.l1 = "Exactamente, señor. Necesito registrarme aquí según las reglas.";
			link.l1.go = "Regata_check";
			break;
		}
		// регата
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas son esas?", "¿Qué deseas, " + GetAddress_Form(NPChar) + "?"), "Ya has intentado hacerme una pregunta " + GetAddress_Form(NPChar) + "...", "Es la tercera vez que me interrumpes hoy...", "Mira, si no tienes nada que decirme sobre los asuntos del puerto, entonces no me molestes con tus preguntas.", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión.", "No tengo nada de qué hablar."), "Olvídalo.", "De hecho, ya es la tercera vez...", "Lo siento, pero no me interesan los asuntos del puerto por ahora.", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		//--> Грани справедливости
		if (CheckAttribute(pchar, "questTemp.GS_Portman"))
		{
			link.l1 = "He oído rumores de que intentaron asesinarle y que está buscando al atacante.";
			link.l1.go = "GS_Portman_1";
		}
		if (CheckAttribute(pchar, "questTemp.GS_NaemnikMertv"))
		{
			link.l1 = "El hombre que atentó contra su vida ha caído, señor "+npchar.lastname+". Ya no corre peligro.";
			link.l1.go = "GS_Portman_6";
		}
		//<-- Грани справедливости 
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
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
				dialog.text = "Hm... Has roto las reglas de la regata y tengo que descalificarte. Lo siento. No participarás en el próximo viaje. Ya he preparado un despacho para Port-Royal.";
				link.l1 = "¡Vaya... qué lástima! Pero no puedo hacer nada aquí, fuiste demasiado vigilante. ¡Adiós!";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata");
				pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
				AddQuestRecord("Regata", "45");
				CloseQuestHeader("Regata");
			}
			else
			{
				pchar.questTemp.Regata.FirstTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime()); // истратил ГГ в часах на 1 переход
				dialog.text = "Vamos a registrarnos: capitán " + GetFullName(pchar) + ", el barco es " + pchar.Ship.Name + "... el tiempo de la regata en horas es " + sti(pchar.questTemp.Regata.FirstTransitionTime) + ". Listo, tu resultado está registrado, puedes continuar tu camino.";
				link.l1 = "Dime mi rango.";
				link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "Estás aquí, pero no veo tu barco. ¿Dónde está?";
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
			if (pchar.questTemp.Regata.AdversaryFirstTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FirstTransitionTime))
			{
				n++;
				sName = pchar.questTemp.Regata.AdversaryName.(sTemp);	  // имя ближайшего противника
				sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp); // его корабль
			}
		}
		if (n == 1)
		{
			dialog.text = "¡Vas a la cabeza! ¡Felicitaciones! ¡Sigue así!";
			link.l1 = "¡Gracias!";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "4");
		}
		else
		{
			if (n == 6)
			{
				dialog.text = "Eres el último. Deberías darte prisa.";
				link.l1 = "¡Estoy en camino!";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "9");
			}
			else
			{
				if (n == 2)
				{
					dialog.text = "Eres el segundo. El líder es " + sName + " en el barco " + sShip + "Supongo que aún puedes dejarlo atrás.";
					link.l1 = "¡Gracias! ¡Lo intentaré!";
					link.l1.go = "exit";
					AddQuestRecord("Regata", "5");
				}
				else
				{
					dialog.text = "Tu rango es " + n + ". Tu oponente más cercano es " + sName + " en el barco " + sShip + ".";
					link.l1 = "¡Gracias!";
					link.l1.go = "exit";
					if (n == 3)
						AddQuestRecord("Regata", "6");
					if (n == 4)
						AddQuestRecord("Regata", "7");
					if (n == 5)
						AddQuestRecord("Regata", "8");
				}
			}
		}
		AddCharacterExpToSkill(pchar, "Sailing", 50); // навигация
		npchar.quest.regatatalk = "true";
		pchar.questTemp.Regata.Beliz = "true"; // отметка Белиза
		pchar.quest.Regata_Check1.win_condition.l1 = "location";
		pchar.quest.Regata_Check1.win_condition.l1.location = "Cuba1";
		pchar.quest.Regata_Check1.function = "RegataCheck"; // проверка 1
		pchar.quest.Regata_Check2.win_condition.l1 = "location";
		pchar.quest.Regata_Check2.win_condition.l1.location = "Cuba2";
		pchar.quest.Regata_Check2.function = "RegataCheck"; // проверка 2
		pchar.quest.Regata_Check.win_condition.l1 = "location";
		pchar.quest.Regata_Check.win_condition.l1.location = "Hispaniola2";
		pchar.quest.Regata_Check.function = "RegataCheck"; // проверка 3
		pchar.questTemp.Regata.AttackIsland = "Cuba1";
		pchar.questTemp.Regata.AttackNation = SPAIN;
		pchar.quest.Regata_Attack.win_condition.l1 = "location";
		pchar.quest.Regata_Attack.win_condition.l1.location = "Cuba1";
		pchar.quest.Regata_Attack.function = "RegataAttack_Lugger"; // первая засада у Сантьяго
		pchar.quest.Regata_Hunter.win_condition.l1 = "location";
		pchar.quest.Regata_Hunter.win_condition.l1.location = "Cuba2";
		pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter"; // ДУ у Гаваны
		pchar.questTemp.Regata.Town = "Portpax";
		pchar.quest.Regata_PU.win_condition.l1 = "locator";
		pchar.quest.Regata_PU.win_condition.l1.location = "Portpax_town";
		pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
		pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
		pchar.quest.Regata_PU.win_condition.l2 = "Night";
		pchar.quest.Regata_PU.function = "RegataPU_Open"; // вход в ПУ ночью
		break;
		// регата
		
		//--> Грани справедливости
		case "GS_Portman_1":
			dialog.text = "El intento de asesinato fue real, es cierto. Pero en cuanto a la búsqueda... es un poco diferente. No necesito un criminal fugitivo, necesito su cabeza. Solo entonces podré recuperar la tranquilidad.";
			Link.l1 = "¿Tiene alguna idea de quién lo atacó y por qué?";
			Link.l1.go = "GS_Portman_2";
			DelLandQuestMark(npchar);
		break;

		case "GS_Portman_2":
			dialog.text = "¡Yo... no sé quién es! No sé de dónde vino ni por qué me atacó. Pero una cosa está clara: quería matarme. Y ahora... ¡ahora deseo su muerte con la misma furia! ¿Me entiende?\nAsí que deje sus preguntas inútiles. Su curiosidad no me sirve; solo las acciones pueden ayudarme. Doscientos doblones por su cabeza, ese es mi precio. Comience la búsqueda o no pierda mi tiempo con charlas vacías.";
			Link.l1 = "Entiendo que el miedo y la ira nublan su juicio, y le perdono ese tono. Pero contrólese. No veo una fila de personas dispuestas a resolver sus problemas, así que modere su fervor. Doscientos doblones me parecen bien, pero antes de comenzar, necesito saber todo.";
			Link.l1.go = "GS_Portman_3";
			Link.l2 = "Sus palabras son solo charla vacía y no hay pistas. Buscar a alguien desconocido en la selva es como buscar una aguja en un pajar. No perderé mi tiempo en una búsqueda inútil. Le deseo suerte. La necesitará.";
			Link.l2.go = "GS_Portman_End";
		break;

		case "GS_Portman_End":
			DialogExit();
			CloseQuestHeader("GS");
			DeleteAttribute(pchar, "questTemp.GS_Portman");
		break;

		case "GS_Portman_3":
			dialog.text = "Argh... Perdóneme, "+GetAddress_Form(NPChar)+", estoy muy nervioso... ¿Qué exactamente quiere saber?";
			Link.l1 = "¿Recuerda alguna característica que me ayude a identificarlo? ¿Estaba solo o hay un enemigo más influyente detrás de él? Cuanto más me diga, más rápido podrá dormir tranquilo.";
			Link.l1.go = "GS_Portman_4";
		break;

		case "GS_Portman_4":
			dialog.text = "¿Qué enemigo? ¡No tengo enemigos! ¡Nunca los he tenido! No hago nada para merecer la muerte así, en medio de la calle, a plena luz del día.\nEse canalla... es simplemente un loco enfurecido, como tantos en estos asentamientos coloniales.\nEn cuanto a dónde buscarlo... creo que se esconde en la selva. Es fácil perderse en esa maldita jungla, pero estoy seguro de que se dirigirá a grutas o calas, allí es más fácil esconderse.\nEn cuanto a su apariencia, su rostro estaba cubierto con un pañuelo, llevaba un sombrero y tenía más armas que un guardia de Su Majestad. No hubo tiempo para ver más.";
			Link.l1 = "Bien, no es mucha información, pero suficiente para comenzar la búsqueda. Parto de inmediato. No esconda el oro muy lejos; regresaré pronto.";
			Link.l1.go = "GS_Portman_5";
		break;
		
		case "GS_Portman_5":
			DialogExit();
			AddQuestRecord("GS", "2");
			DeleteAttribute(pchar, "questTemp.GS_Portman");
			
			PChar.quest.GS_Peshera.win_condition.l1 = "location";
			PChar.quest.GS_Peshera.win_condition.l1.location = "Beliz_Cave";
			PChar.quest.GS_Peshera.function = "GS_Peshera";
			locations[FindLocation("Beliz_Cave")].DisableEncounters = true;
			
			PChar.quest.GS_Peshera_pusto.win_condition.l1 = "location";
			PChar.quest.GS_Peshera_pusto.win_condition.l1.location = "Beliz_Cave_2";
			PChar.quest.GS_Peshera_pusto.function = "GS_Peshera_pusto";
		break;
		
		case "GS_Portman_6":
			dialog.text = "¡Excelente, "+GetFullName(pchar)+"! ¡Simplemente excelente! Ha demostrado que su habilidad no tiene igual. Aquí está su recompensa: doscientos doblones. ¡Adelante, tómelos!";
			Link.l1 = "¡Gracias! Pero dígame, ¿tiene razones para creer que el asesino fue contratado por alguno de sus antiguos clientes?";
			Link.l1.go = "GS_Portman_7";
			AddItems(pchar, "gold_dublon", 200);
			DelLandQuestMark(npchar);
		break;

		case "GS_Portman_7":
			dialog.text = "¿Antiguos clientes? ¡Qué tontería! Soy un hombre honesto y mis asuntos siempre han sido limpios. Pero ya que me ha ayudado, le contaré. No hace mucho, vinieron a verme unos piratas.\nMe ofrecieron vender información sobre barcos mercantes por dinero. Rechacé y me lanzaron amenazas y maldiciones antes de irse. Creo que ese asesino es obra suya. No toleran rechazos.";
			Link.l1 = "En ese caso, cuídese. ¿Quién sabe cuántos asesinos más enviarán esos 'piratas', como usted los llama? Por ahora debo despedirme, los asuntos me esperan.";
			Link.l1.go = "GS_Portman_8";
		break;

		case "GS_Portman_8":
			dialog.text = "Espere, capitán. Quiero agradecerle una vez más. Además del dinero, se ha ganado mi aprecio. Mientras yo sea el jefe del puerto aquí, puede dejar cualquier barco suyo aquí por cualquier tiempo con un descuento del cincuenta por ciento. ¿Qué le parece esta oferta?";
			Link.l1 = "¡Muy generoso de su parte! ¡Gracias de nuevo!";
			Link.l1.go = "GS_Portman_9";
		break;

		case "GS_Portman_9":
			dialog.text = "Y yo le agradezco una vez más por el trabajo realizado. Estoy seguro de que, si pensamientos innecesarios no lo distraen de lo principal, sus asuntos seguirán siendo tan exitosos como hoy. Adiós, capitán.";
			Link.l1 = "Adiós.";
			Link.l1.go = "GS_Portman_10";
		break;

		case "GS_Portman_10":
			DialogExit();
			AddQuestRecord("GS", "4");
			CloseQuestHeader("GS");
			DeleteAttribute(pchar, "questTemp.GS_NaemnikMertv");
			pchar.questTemp.GS_BelizSkidka = true;
		break;
		//<-- Грани справедливости
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

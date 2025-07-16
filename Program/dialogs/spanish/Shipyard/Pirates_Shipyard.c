// диалог по городам
// Это мастер тюнинга
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	string sTemp;
	int amount, iSan, iOil, iSil, iRop;
	int iTemp, iSum; // 280912
	ref shTo;
	string s1;

	int Matherial1;
	int Matherial2;
	int Matherial3;
	int Matherial4;
	int HPPrice;

	if (sti(pchar.Ship.Type) != SHIP_NOTUSED)
	{
		int shipCurHP = sti(RealShips[sti(pchar.Ship.Type)].HP);
		int shipBaseHP = sti(RealShips[sti(pchar.Ship.Type)].BaseHP);
		int shipClass = sti(RealShips[sti(pchar.Ship.Type)].Class);
	}

	switch (Dialog.CurrentNode)
	{
	// -----------------------------------Диалог первый - первая встреча
	case "First time": // перехват основного диалога, только один раз
		if (NPChar.quest.meeting == "0")
		{
			Dialog.Text = "Phew... Qué clima tan terrible... Mi nombre es " + GetFullName(npchar) + ", y que Dios me maldiga, si no soy el mejor constructor naval en estas islas olvidadas por Dios. Pero esta humedad me está tumbando...";
			Link.l1 = pcharrepphrase("Mil tiburones, solo me faltaba el murmullo de un viejo. Mi nombre es " + GetFullName(pchar) + ", creo que has oído hablar de mí.", " No es la humedad, es la vejez, señor. Mi nombre es " + GetFullName(pchar) + ", creo que has oído hablar de mí.");
			Link.l1.go = "node_1";
			npchar.quest.meeting = "1";
		}
		else // нужно, если по квестам будет сброс на  "First time"
		{
			dialog.text = "Oh, tú de nuevo, siempre hablando de tus problemas... (tosiendo).";
			link.l1 = pcharrepphrase("Tienes razón, soy yo otra vez. Pero hablemos de negocios mientras aún no le hayas entregado tu alma a Dios.", "Tu memoria te sirve bien, y ahora, si me permites, pasemos a algunas preguntas más específicas.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("Me he cansado de tus murmuraciones. Adiós.", "Es hora de irme. Lamento molestarte");
			link.l2.go = "exit";
		}
		NextDiag.TempNode = "Master_Ship";
		Dialog.CurrentNode = "Master_Ship";
		break;

	case "Master_Ship":
		// Jason ----------------------------------- Хронометр Алекса ------------------------------------------
		if (CheckAttribute(npchar, "quest.sextant") && CheckAttribute(pchar, "questTemp.AlexClock") && pchar.location == "Pirates_shipyard" && !CheckAttribute(npchar, "quest.clock"))
		{
			dialog.text = "Aha, capitán " + GetFullName(pchar) + "¡Qué bueno que has pasado por aquí!";
			Link.l1 = "Parece que me necesitas para algo, ¿verdad? Normalmente no eres tan cortés.";
			Link.l1.go = "clock_begin";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "clock" && pchar.location == "Pirates_shipyard")
		{
			dialog.text = "¡Veo que has vuelto a mí con las manos vacías, capitán! ¿Qué pasó con los... invitados?";
			Link.l1 = "Se han ido. Les pregunté y se han ido.";
			Link.l1.go = "clock_complete";
			break;
		}
		//<-- хронометр Алекса
		dialog.text = "Oh, tú de nuevo, siempre hablando de tus problemas... (tosiendo)";
		link.l1 = pcharrepphrase("Tienes razón, soy yo de nuevo. Pero hablemos de negocios mientras todavía no le hayas entregado tu alma a Dios.", "Tu memoria te sirve bien, y ahora, si me permites, pasemos a algunas preguntas más específicas.");
		link.l1.go = "node_3";
		link.l2 = pcharrepphrase("Me he cansado de tus murmuraciones. Adiós.", "Es hora de que me vaya. Perdón por molestarte.");
		link.l2.go = "exit";
		NextDiag.TempNode = "Master_Ship";
		break;

	case "node_1":
		dialog.text = "Los jóvenes de hoy en día... Nunca tienen respeto. Cabezas calientes, manos duras, ¿qué necesitas?";
		link.l1 = pcharrepphrase("Así es. Pero tarde o temprano todo llega a su fin y parece que tu hora está cerca...", "Algo me dice que durante tus años jóvenes, tampoco tenías mucho respeto por los mayores. ¿Estoy en lo correcto?");
		link.l1.go = "node_2";
		break;

	case "node_2":
		dialog.text = "No discutas con tus mayores, cachorro.";
		link.l1 = pcharrepphrase("Tranquilo, ahora. Cálmate. No te esfuerces demasiado, de lo contrario podrías sufrir un ataque al corazón. No quiero ser acusado de la muerte del mejor constructor naval del Caribe. Vamos al grano.", "Te perdono por tu grosería, solo por respeto a tu edad. Y ahora, si has terminado, pasemos al negocio.");
		link.l1.go = "node_3";
		link.l2 = pcharrepphrase("¡Está bien, eso es suficiente de sermones para mí! ¡Adiós!", "Veo que no vamos a estar de acuerdo. Adiós.");
		link.l2.go = "exit";
		break;

	case "node_3":
		dialog.text = "(tosiendo)... La gente no deja en paz a un anciano. ¿Qué necesitas de mí esta vez, " + GetAddress_Form(NPChar) + "?";
		link.l1 = pcharrepphrase("Necesito utilizar los servicios del astillero.", "Quiero usar los servicios del astillero.");
		link.l1.go = "shipyard_dlg";
		Link.l2 = "Tengo una pregunta.";
		Link.l2.go = "quests"; //(пересылка в файл города)
		// -->
		if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
		{
			link.l3 = "Me gustaría hablar sobre finanzas.";
			link.l3.go = "LoanForAll"; //(перессылка в файл города)
		}
		link.l9 = pcharrepphrase("Mierda, tengo un par de asuntos urgentes que atender, adiós.", "Es hora de que me vaya. Lo siento.");
		link.l9.go = "exit";
		NextDiag.TempNode = "Master_Ship";
		break;

	case "shipyard_dlg":
		if ((shipBaseHP - shipCurHP > 0) && (shipClass < 7))
		{
			dialog.Text = "Puedo ofrecerte una reparación capital del marco de tu casco. La gente aquí no tiene ni idea de cómo construir barcos decentes, todos se deshacen con un solo disparo...";
			Link.l1 = "¡Genial! Resulta que tengo un barco que necesita reparación. ¿Quizás puedas echar un vistazo a ver qué puedes hacer?";
			Link.l1.go = "ship_repair_start";
		}
		else
		{
			dialog.Text = "Vamos, ¿qué quieres? No acoses a un viejo...";
		}
		link.l2 = "Solo quiero utilizar los servicios del astillero.";
		link.l2.go = "shipyard";
		link.l3 = "Necesito armas para el barco.";
		link.l3.go = "Cannons";
		if (RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
		{
			link.l4 = "Quiero cambiar el aspecto de mis velas.";
			link.l4.go = "SailsGerald";
		}
		if (RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_hull"))
		{
			link.l50 = "Mi barco es bastante... especial. Me gustaría hacer algunos cambios.";
			link.l50.go = "FDM";
		}
		if (RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_full") && npchar.quest.FDM_full == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
		{
			link.l50 = "Tengo más cofres para la reconstrucción de la cabina.";
			link.l50.go = "FDM_cabin_pay";
		}
		// Xenon -->
		if (RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmoney")
		{
			link.l50 = "Estoy aquí por la reconstrucción del barco.";
			link.l50.go = "FDM_hull_givemoney";
		}

		if (RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmaterials")
		{
			link.l50 = "Estoy aquí por la reconstrucción del barco.";
			link.l50.go = "FDM_hull_checkmaterials";
		}
		// <-- Xenon
		link.l9 = pcharrepphrase("Mierda, tengo un par de asuntos urgentes que atender, adiós.", "Es hora de que me vaya. Lo siento.");
		Link.l9.go = "ship_tunning_not_now";
		break;

	case "ship_repair_again":
		if ((shipBaseHP - shipCurHP > 0) && (shipClass < 7))
		{
			dialog.Text = RandPhraseSimple("Ah... tú otra vez. ¿Quieres reparar tu navío de nuevo?", RandPhraseSimple("Saludos, a un capitán famoso. ¿Qué, necesitas otra reparación capital?", "Caray... Ni un minuto de paz y tranquilidad. No dejas que un viejo se concentre... ¿Otra reparación?"));
			Link.l1 = "Sí. Tienes razón. ¿Echaremos un vistazo a lo que podemos hacer?";
			Link.l1.go = "ship_repair_start";
		}
		else
		{
			dialog.Text = "¿Qué ha pasado esta vez? Simplemente no quieres dejarme en paz...";
		}
		link.l2 = "Solo quiero utilizar los servicios del astillero.";
		link.l2.go = "shipyard";
		link.l3 = "Necesito armas para el barco.";
		link.l3.go = "Cannons";
		if (RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
		{
			link.l31 = "Quiero cambiar el aspecto de mis velas.";
			link.l31.go = "SailsGerald";
		}
		if (RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_hull"))
		{
			link.l50 = "Mi barco es bastante... especial. Me gustaría hacer algunos cambios.";
			link.l50.go = "FDM";
		}
		if (RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_full") && npchar.quest.FDM_full == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
		{
			link.l50 = "Tengo más cofres para la reconstrucción de la cabina.";
			link.l50.go = "FDM_cabin_pay";
		}
		Link.l4 = "Tengo una pregunta.";
		Link.l4.go = "quests"; //(пересылка в файл города)
		// -->
		if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
		{
			link.l5 = "Me gustaría hablar sobre finanzas.";
			link.l5.go = "LoanForAll"; //(пересылка в файл города)
		}
		Link.l9 = "No. Estoy contento con lo que tengo.";
		Link.l9.go = "ship_tunning_not_now_2";
		break;

	case "ship_tunning_not_now_2":
		dialog.Text = "¡Oh, veo que sigues pensando! ¡Llegarás lejos! Vuelve cuando decidas lo que quieres y no me molestes con tonterías triviales.";
		Link.l1 = RandPhraseSimple("¡Gracias! Todo lo mejor.", "Adiós, maestro. Y menos sarcasmo.");
		Link.l1.go = "ship_tunning_not_now";
		break;

	case "ship_repair_start":
		if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || Pchar.location.from_sea != "Pirates_town")
		{
			dialog.Text = "¿Dónde está el barco? ¿Qué es todo este abracadabra?!";
			Link.l1 = "Sí, tienes razón... yo... Lo siento.";
			Link.l1.go = "ship_tunning_not_now";
		}
		else
		{
			if (GetHour() == 13)
			{
				dialog.Text = "Puede que sea un adicto al trabajo, pero también tengo mi hora de almuerzo. ¡Vuelve más tarde!";
				Link.l1 = "Bien...";
				Link.l1.go = "ship_tunning_not_now";
			}
			else
			{
				if (makefloat(shipCurHP) / makefloat(shipBaseHP) < 0.10)
				{
					dialog.Text = "¡Caramba... Tu barco está completamente destrozado. No haré una reparación capital, ni me lo pidas... Si hubieras venido un poco antes...";
					Link.l1 = "Está bien... Eso es una lástima...";
					Link.l1.go = "ship_tunning_not_now";
					break;
				}
				if (makefloat(shipCurHP) / makefloat(shipBaseHP) > 0.95)
				{
					dialog.Text = "¿Qué es todo este hocus pocus...? Tu barco parece como nuevo... El armazón prácticamente brilla intensamente. No hay nada que reparar aquí.";
					Link.l1 = "Bien... Bueno, vendré más tarde...";
					Link.l1.go = "ship_tunning_not_now";
					break;
				}
				s1 = "Bien, de acuerdo... ¿Qué tenemos aquí...? Ajá, " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ".";
				if (sti(RealShips[sti(Pchar.Ship.Type)].Stolen) == true && !CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning"))
				{
					s1 = s1 + " ¡Bah! Este barco ha estado en demasiadas manos. Sí y hay un montón de rasguños. ¿Tiene patente de corsario? Sólo bromeaba... de todos modos, volviendo al asunto.";
				}
				dialog.Text = s1;
				Link.l1 = "Echemos un vistazo a lo que podemos hacer.";
				Link.l1.go = "ship_repair_HP";
				Link.l2 = "¡Detente! He cambiado de opinión.";
				Link.l2.go = "ship_tunning_not_now_2";
			}
		}
		break;

	case "ship_repair_HP":
		HPPrice = GetMaterialQtyRepair(pchar, 0);
		Matherial1 = GetMaterialQtyRepair(pchar, 1);
		Matherial2 = GetMaterialQtyRepair(pchar, 2);
		Matherial3 = GetMaterialQtyRepair(pchar, 3);
		Matherial4 = GetMaterialQtyRepair(pchar, 4);

		s1 = "Veamos lo que podemos hacer. En este momento, la estructura de la nave es " + shipCurHP + ". . El valor más alto posible es " + shipBaseHP;
		s1 = s1 + ". Para hacer una reparación completa, necesito de sándalo:, " + Matherial1 + ", resina, " + Matherial2 + ", seda de barco, " + Matherial3 + " cuerdas, " + Matherial4 + ".";
		s1 = s1 + " Por este trabajo cobraré: " + HPPrice + " doblones por el trabajo... Hace tiempo que mis nietos me llaman para que vuelva a Europa. No quiero volver con las manos vacías... Así que, eso será todo. Y sí, el dinero por adelantado.";
		dialog.Text = s1;
		Link.l1 = "Suena bien. Aceptaré las condiciones. Todo será entregado según lo acordado.";
		if (CheckItemMyCabin("gold_dublon") >= HPPrice)
		{
			Link.l1.go = "ship_repair_HP_start_0";
		}
		else
		{
			Link.l1.go = "ship_repair_HP_start";
		}
		Link.l2 = "No. No estoy satisfecho con eso.";
		Link.l2.go = "ship_tunning_not_now";
		break;

	case "ship_repair_HP_start_0":
		dialog.Text = "Sí... El pago... Puedes pagar ahora mismo o puedes enviar a un chico de los recados a la nave por la cantidad necesaria... ¿Qué te gustaría hacer?";
		link.l1 = "Pagaré ahora mismo.";
		link.l1.go = "ship_repair_HP_start";
		link.l2 = "Enviaré a un chico de los recados. Creo que tenía un poco de oro en mis cofres...";
		link.l2.go = "ship_repair_HP_start_1";
		break;

	case "ship_repair_HP_start":
		HPPrice = GetMaterialQtyRepair(pchar, 0);
		Matherial1 = GetMaterialQtyRepair(pchar, 1);
		Matherial2 = GetMaterialQtyRepair(pchar, 2);
		Matherial3 = GetMaterialQtyRepair(pchar, 3);
		Matherial4 = GetMaterialQtyRepair(pchar, 4);
		amount = HPPrice;
		if (GetCharacterItem(pchar, "gold_dublon") >= amount)
		{
			TakeNItems(pchar, "gold_dublon", -amount);
			NPChar.Repair.Money = amount;
			NPChar.Repair.Matherial1 = Matherial1;
			NPChar.Repair.Matherial2 = Matherial2;
			NPChar.Repair.Matherial3 = Matherial3;
			NPChar.Repair.Matherial4 = Matherial4;
			NPChar.Repair.ShipType = Pchar.Ship.Type;
			NPChar.Repair.ShipName = RealShips[sti(Pchar.Ship.Type)].BaseName;
			NPChar.Repair.Delta = shipBaseHP - shipCurHP;

			NextDiag.TempNode = "ship_repair_HP_again";
			dialog.text = "Espléndido. Estaré esperando los materiales.";
			link.l1 = "Voy a reunirlos...";
			link.l1.go = "Exit";

			ReOpenQuestHeader("ShipRepair");
			AddQuestRecord("ShipRepair", "t1");
			AddQuestUserData("ShipRepair", "sText", "Para las medidas de reparación de capital de  " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + " el capitán del barco necesita de sándalo, " + NPChar.Repair.Matherial1 + ", resina, " + NPChar.Repair.Matherial2 + ", seda de barco, " + NPChar.Repair.Matherial3 + " cuerdas, " + NPChar.Repair.Matherial4 + ". Como depósito entregamos " + NPChar.Repair.Money + " doblones... Dice que está a punto de despegar hacia Europa. Creo que ese viejo diablo miente.");
		}
		else
		{
			NextDiag.TempNode = "ship_tunning_not_now";
			dialog.text = RandPhraseSimple("No veo el depósito...", "¿Qué es este hocus pocus...?");
			link.l1 = "Regresaré más tarde.";
			link.l1.go = "Exit";
		}
		break;

	case "ship_repair_HP_start_1":
		HPPrice = GetMaterialQtyRepair(pchar, 0);
		Matherial1 = GetMaterialQtyRepair(pchar, 1);
		Matherial2 = GetMaterialQtyRepair(pchar, 2);
		Matherial3 = GetMaterialQtyRepair(pchar, 3);
		Matherial4 = GetMaterialQtyRepair(pchar, 4);
		AddTimeToCurrent(0, 30);
		amount = HPPrice;
		GetItemMyCabin("gold_dublon", amount);

		NPChar.Repair.Money = amount;
		NPChar.Repair.Matherial1 = Matherial1;
		NPChar.Repair.Matherial2 = Matherial2;
		NPChar.Repair.Matherial3 = Matherial3;
		NPChar.Repair.Matherial4 = Matherial4;
		NPChar.Repair.ShipType = Pchar.Ship.Type;
		NPChar.Repair.ShipName = RealShips[sti(Pchar.Ship.Type)].BaseName;
		NPChar.Repair.Delta = shipBaseHP - shipCurHP;

		NextDiag.TempNode = "ship_repair_HP_again";
		dialog.text = "Espléndido. Estaré esperando los materiales.";
		link.l1 = "Me voy...";
		link.l1.go = "Exit";

		ReOpenQuestHeader("ShipRepair");
		AddQuestRecord("ShipRepair", "t1");
		AddQuestUserData("ShipRepair", "sText", "Para las medidas de reparación del " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + " el capitán del barco necesita: sándalo, " + NPChar.Repair.Matherial1 + ", resina, " + NPChar.Repair.Matherial2 + ", seda de barco, " + NPChar.Repair.Matherial3 + " cuerdas, " + NPChar.Repair.Matherial4 + ". Como depósito entregamos " + NPChar.Repair.Money + " doblones... Dice que está a punto de despegar hacia Europa. Creo que ese viejo diablo miente.");

		break;

	case "ship_repair_HP_again":
		if (sti(NPChar.Repair.ShipType) == sti(Pchar.Ship.Type) && NPChar.Repair.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName)
		{
			NextDiag.TempNode = "ship_repair_HP_again";
			dialog.Text = "El tiempo corre. ¿Tienes lo que pedí?";
			Link.l1 = "Sí. Logré conseguir algo.";
			Link.l1.go = "ship_repair_HP_again_2";
			Link.l2 = "No. Todavía estoy en mis búsquedas.";
			Link.l2.go = "Exit";
		}
		else
		{
			DeleteAttribute(NPChar, "Repair");
			NextDiag.TempNode = "ship_repair_again";
			dialog.Text = "Me parece, señor, que ha cambiado su barco desde la última vez que acordamos. Tendremos que volver a contar todo desde el principio...";
			Link.l1 = "Sí, es cierto. Qué lástima que el depósito se haya ido...";
			Link.l1.go = "Exit";
			AddQuestRecord("ShipRepait", "Lose");
			CloseQuestHeader("ShipRepair");
		}
		break;

	case "ship_repair_HP_again_2":
		checkMatherial_repair(Pchar, NPChar, GOOD_SANDAL, 1);
		checkMatherial_repair(Pchar, NPChar, GOOD_OIL, 2);
		checkMatherial_repair(Pchar, NPChar, GOOD_SHIPSILK, 3);
		checkMatherial_repair(Pchar, NPChar, GOOD_ROPES, 4);
		if (sti(NPChar.Repair.Matherial1) < 1 &&
			sti(NPChar.Repair.Matherial2) < 1 &&
			sti(NPChar.Repair.Matherial3) < 1 &&
			sti(NPChar.Repair.Matherial4) < 1)
		{
			NextDiag.TempNode = "ship_repair_again";
			dialog.text = "Todo lo que necesitaba. ¡Bien! Hora de trabajar...";
			link.l1 = "De acuerdo, esperaré.";
			link.l1.go = "ship_repair_HP_complite";
		}
		else
		{
			NextDiag.TempNode = "ship_repair_HP_again";
			dialog.Text = "Ahora lo que aún te queda por traerme es: " + sti(NPChar.Repair.Matherial1) + " de sándalo, " + sti(NPChar.Repair.Matherial2) + " resina, " + NPChar.Repair.Matherial3 + " de seda de barco, " + NPChar.Repair.Matherial4 + "cuerdas.";
			link.l1 = "Está bien.";
			link.l1.go = "Exit";

			AddQuestRecord("ShipRepair", "t1");
			AddQuestUserData("ShipRepair", "sText", "Materials left: ironwood, " + NPChar.Repair.Matherial1 + ", resin, " + NPChar.Repair.Matherial2 + ", ship silk, " + NPChar.Repair.Matherial3 + " ropes, " + NPChar.Repair.Matherial4 + ".");
		}
		break;

	case "ship_repair_HP_complite":
		AddTimeToCurrent(6, 30);
		shTo = &RealShips[sti(Pchar.Ship.Type)];
		shTo.HP = sti(shTo.HP) + sti(NPChar.Repair.Delta);
		DeleteAttribute(NPChar, "Repair");

		pchar.ship.hp = GetCharacterShipBaseHP(pchar);
		DeleteAttribute(pchar, "ship.hulls");
		DeleteAttribute(pchar, "ship.blots");

		NextDiag.TempNode = "node_3";
		dialog.Text = "... Bueno, eso es todo... ¡Te garantizo que ahora será bastante difícil destrozar este barco!";
		Link.l1 = "¡Gracias! Preferiría no experimentar, pero confiaré en ti.";
		Link.l1.go = "Exit";
		AddQuestRecord("ShipRepair", "End");
		CloseQuestHeader("ShipRepair");
		break;

	///////////////////////////////  квестовые ветки
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?", "¿Cómo puedo ayudarle?"), "Intentaste hacerme una pregunta hace un rato...", "Jamás he conocido a personas con tanta curiosidad en mi astillero ni en ningún otro lugar de esta ciudad.", "¿Por qué tantas preguntas? Mi trabajo es construir barcos. Ocuparémonos de eso.", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No tengo nada de qué hablar por el momento."), "Umph, ¿dónde se ha ido mi memoria...?", "Mm, bueno...", "Bien, dejemos que...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		if (!CheckAttribute(npchar, "Step_Door"))
		{
			link.l2 = "Escucha, me gustaría pasar y esa puerta está cerrada con llave...";
			link.l2.go = "Step_Door_1";
		}

		if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAlexus"))
		{
			link.l1 = "Me gustaría proponer un trato.";
			link.l1.go = "Al_ShipLetters_1"; // генератор  "Найденные документы"
			pchar.questTemp.different.GiveShipLetters.speakAlexus = true;
		}
		if (CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "go") // 280912
		{
			link.l1 = "Estoy aquí por los materiales para la fragata.";
			link.l1.go = "clock";
		}
		if (CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
		{
			link.l1 = "Escucha, " + npchar.name + ", ¿has visto a Miguel Dichoso en Isla Tesoro recientemente?";
			link.l1.go = "tieyasal";
		}
		break;
		//*************************** Генератор - "Найденные судовые документы" **************

	case "Al_ShipLetters_1":
		dialog.text = "Expón tus términos.";
		s1 = "Tuve la suerte de encontrar un paquete de documentos del barco absolutamente legal que aún no ha sido llamado a registro.";
		s1 = s1 + "El barco está a flote y no ha sido excluido del registro, no se preocupe. Sólo un tonto ciego propietario tuvo la desgracia de perder estos papeles...";
		link.l1 = s1;
		link.l1.go = "Al_ShipLetters_2";
		break;
	case "Al_ShipLetters_2":
		s1 = "¡Déjame echar un vistazo! Realmente parece estar recién rellenado. ¡Bueno, la suerte está a su favor, señor! ";
		s1 = s1 + "En realidad necesitaba un paquete como este. Yo, por mi parte, le ofreceré " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " pesos. ¿Qué me dices?";
		dialog.text = s1;
		link.l1 = "¡Verdadera generosidad real! ¡Por supuesto que estoy de acuerdo!";
		link.l1.go = "Al_ShipLetters_3";
		link.l2 = "No, no lo creo.";
		link.l2.go = "exit";
		break;
	case "Al_ShipLetters_3":
		TakeItemFromCharacter(pchar, "CaptainBook");
		addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5));
		ChangeCharacterComplexReputation(pchar, "nobility", -1);
		OfficersReaction("bad");
		pchar.questTemp.different = "free";
		pchar.quest.GiveShipLetters_null.over = "yes"; // снимаем таймер
		AddQuestRecord("GiveShipLetters", "9");
		CloseQuestHeader("GiveShipLetters");
		DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

		//*************************** Открывание двери ***************************
	case "Step_Door_1":
		dialog.text = "Eso es correcto. Si quieres pasar por esta puerta, tienes que pagarme 20000 pesos. Si no pagas, no abriré. Esto no es una cocina de beneficencia. Y no te aconsejo que vayas allí de todos modos. Será mejor para ti si no lo haces...";
		if (sti(pchar.money) >= 20000)
		{
			link.l1 = "Aquí tienes tu dinero. Ábrete.";
			link.l1.go = "Step_Door_2";
		}
		else
		{
			link.l1 = "No tengo tanto dinero.";
			link.l1.go = "Step_Door_3";
		}
		link.l2 = "¡De ninguna manera! Nunca pagaría por una puerta.";
		link.l2.go = "exit";
		break;

	case "Step_Door_2":
		npchar.Step_Door = true; // fix
		dialog.text = "Entra. La puerta está abierta. ¡No te preocupes por darme las gracias!";
		link.l1 = "No, por qué no. Gracias, " + npchar.name + "... ";
		link.l1.go = "exit";
		LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
		AddMoneyToCharacter(pchar, -20000);
		pchar.quest.CloseBermudesDungeonDoor.win_condition.l1 = "MapEnter";
		pchar.quest.CloseBermudesDungeonDoor.win_condition = "CloseBermudesDungeonDoor";
		break;

	case "Step_Door_3":
		dialog.text = "Bueno, cuando lo tengas, vuelve. De lo contrario, no trates de convencerme. Es inútil...";
		link.l1 = "¡Argh, estoy completamente sin palabras!";
		link.l1.go = "exit";
		break;

		// ------------------------------------------- хронометр Ђлекса ----------------------------------------------// Addon-2016 Jason замена дублонов на песо везде
	case "clock_begin":
		dialog.text = "Vamos, no seas tan estricto con un viejo... Realmente necesito tu ayuda, capitán.";
		link.l1 = "Dime, maestro. ¿Qué te sucedió?";
		link.l1.go = "clock_begin_1";
		break;

	case "clock_begin_1":
		sTotalTemp = "Steven Dodson";
		if (pchar.questTemp.Alex.Clock == "terrax")
			sTotalTemp = "Marcus Tyrex";
		dialog.text = "Nuestro nuevo líder de la Cofradía de la Costa, " + sTotalTemp + ", ha encargado un nuevo barco, una fragata. También puso tareas bastante difíciles: casco protegido, alta velocidad y buena maniobrabilidad, además de cañones del mayor calibre posible\nEntiendo que el barco de un almirante, perdón, líder de los hermanos, debe ser algo especial, pero eso significa que necesito materiales especiales para construirlo. Debes haber oído hablar de ellos. sándalo, resina, seda de barco y cuerdas...";
		link.l1 = "Entonces cuéntale esto al líder de los Hermanos. ¿O temes que " + sTotalTemp + " ¿te cortará la cabeza por eso?";
		link.l1.go = "clock_begin_2";
		break;

	case "clock_begin_2":
		dialog.text = "Le dije... La cuestión es que nuestro nuevo líder no tiene tiempo ni oportunidad de encontrar y traer estos materiales. Debes saber qué tipo de rareza es. Y no hay manera de que pueda construir una fragata con dichas características sin ellos.";
		link.l1 = "¿Y probablemente propones que yo deba encontrar materiales para el barco?";
		link.l1.go = "clock_begin_3";
		break;

	case "clock_begin_3":
		dialog.text = "Bueno, sí. Eres un buen amigo de nuestro líder." + sTotalTemp + " dice que te debe mucho y que exige todo tipo de respeto por ti... Así que pensé: ya que eres su amigo, ¿tal vez no estarías en contra de ayudarlo? Y al mismo tiempo: ¿te das cuenta de la incómoda posición en la que estoy? Todos los materiales serán pagados, " + sTotalTemp + "no es avaro con su oro.";
		link.l1 = "Lo siento mucho, maestro, pero no estoy menos ocupado que " + sTotalTemp + ". Me temo que recolectar materiales puede llevar una eternidad. Así que, mejor pregunta a alguien más.";
		link.l1.go = "clock_exit";
		link.l2 = "Bueno, si " + sTotalTemp + " ordené un barco de ti, entonces, por supuesto, intentaré ayudar. Realmente somos amigos, y los amigos deben ayudarse mutuamente. ¿Cuántos materiales necesitas?";
		link.l2.go = "clock_begin_4";
		break;

	case "clock_exit":
		dialog.text = "Eso es una pena. Realmente es una pena. Dependía de ti. Bueno, como dicen, no es no...";
		link.l1 = "...";
		link.l1.go = "exit";
		DeleteAttribute(pchar, "questTemp.AlexClock");
		break;

	case "clock_begin_4":
		dialog.text = "Me faltan 100 unidades de sándalo, 150 contenedores de resina, 110 rollos de seda para barcos y 90 bobinas de cuerdas de cáñamo. ¿Qué piensas? ¿Podrías encontrarme todo eso en el transcurso de cuatro meses? No creo que tenga más tiempo.";
		link.l1 = "Puedo al menos intentarlo. ¿Y en cuanto al pago?";
		link.l1.go = "clock_begin_5";
		break;

	case "clock_begin_5":
		dialog.text = "Aquí están mis tarifas: sándalo a 4000 pesos por pieza, resinas a 1400 pesos por contenedor, seda a 2500 pesos por rollo y cuerdas a 1500 pesos por bobina. Y si me traes todo eso, recibirás un regalo muy bonito de mi parte.";
		link.l1 = "¿Qué es, me pregunto?";
		link.l1.go = "clock_begin_6";
		break;

	case "clock_begin_6":
		dialog.text = "Primero tráeme los materiales. Pero te aseguro: te será muy útil, y la cosa es única. No hay otra en el Caribe, ni en todo el mundo hasta ahora. Espero que esa pequeña chispa de curiosidad haya encendido tu interés en reunir los materiales para mí.";
		link.l1 = "Bueno, ¡eres más astuto que un duende, maestro! Muy bien, tienes un trato.";
		link.l1.go = "clock_begin_7";
		break;

	case "clock_begin_7":
		dialog.text = "Estoy muy feliz. Estaré esperando con ansias tu regreso.";
		link.l1 = "Espero que no tome demasiado tiempo...";
		link.l1.go = "clock_begin_8";
		break;

	case "clock_begin_8":
		DialogExit();
		pchar.questTemp.AlexClock = "go";
		npchar.quest.clock = "true";
		SetFunctionTimerCondition("AlexClock_Over", 0, 0, 122, false); // таймер
		AddQuestRecord("alex_clock", "1");
		// запоминаем переменные
		pchar.questTemp.AlexClock.Sandal = 100;
		pchar.questTemp.AlexClock.Oil = 150;
		pchar.questTemp.AlexClock.Shipsilk = 110;
		pchar.questTemp.AlexClock.Ropes = 90;
		break;

	case "clock":
		dialog.text = "¡Excelente! ¿Qué me has traído hoy?";
		if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && !CheckAttribute(npchar, "quest.sandal"))
		{
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			link.l1 = "Sándalo, en la cantidad de " + FindRussianQtyString(iSan) + ".";
			link.l1.go = "sandal";
		}
		if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && !CheckAttribute(npchar, "quest.oil"))
		{
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			link.l2 = "Resinas, en la cantidad de " + FindRussianQtyString(iOil) + ".";
			link.l2.go = "oil";
		}
		if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && !CheckAttribute(npchar, "quest.shipsilk"))
		{
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			link.l3 = "Seda del barco, en la cantidad de " + FindRussianQtyString(iSil) + ".";
			link.l3.go = "shipsilk";
		}
		if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && !CheckAttribute(npchar, "quest.ropes"))
		{
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			link.l4 = "Cuerdas de cáñamo, en la cantidad de " + FindRussianQtyString(iRop) + ".";
			link.l4.go = "ropes";
		}
		link.l5 = "Nada en este momento. Solo quería asegurarme de que todavía tenemos un acuerdo.";
		link.l5.go = "exit";
		break;

	case "clock_1":
		if (CheckAttribute(npchar, "quest.sandal") && CheckAttribute(npchar, "quest.oil") && CheckAttribute(npchar, "quest.shipsilk") && CheckAttribute(npchar, "quest.ropes")) // все привез
		{
			dialog.text = "¡Maravilloso! Tengo todos los materiales en la cantidad que necesito. Mil gracias por tu ayuda, capitán. Me has ayudado muchísimo.";
			link.l1 = "Sí, en cualquier momento, maestro. Estoy bastante complacido también: ayudé a un amigo y gané buen dinero. Y ahora volvamos a nuestra conversación sobre tu misterioso objeto que me prometiste.";
			link.l1.go = "clock_2";
		}
		else
		{
			dialog.text = "¿Alguna otra sorpresa para mí, capitán?";
			link.l1 = "Por desgracia, eso es todo por ahora. Solo sigue esperando.";
			link.l1.go = "exit";
			link.l2 = "Sí, tengo una cosa más...";
			link.l2.go = "clock";
		}
		break;

	case "sandal": // бакаут
		amount = sti(pchar.questTemp.AlexClock.Sandal);
		iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
		iTemp = amount - iSan;
		if (iTemp > 0) // ещё не все привез
		{
			iSum = 4000 * iSan;
			dialog.text = "Está bien, de acuerdo. También voy a necesitar " + FindRussianQtyString(amount) + " de sándalo. Me has traído " + FindRussianQtyString(iSan) + ". Entonces, lo que te queda por traerme es " + FindRussianQtyString(iTemp) + ". De acuerdo, a razón de 4000 pesos por pieza, tu recompensa asciende a " + FindRussianMoneyString(iSum) + ". Por favor, tómalo.";
			link.l1 = "¡Gracias! Tendrás el resto pronto.";
			link.l1.go = "clock_1";
			RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
			pchar.questTemp.AlexClock.Sandal = iTemp; // столько осталось довезти
			AddQuestRecord("alex_clock", "2");
			AddQuestUserData("alex_clock", "sGood", "ironwood");
			AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
		}
		else
		{
			iSum = 4000 * amount;
			dialog.text = "Está bien, de acuerdo. También voy a necesitar " + FindRussianQtyString(amount) + " de sándalo. Me has traído " + FindRussianQtyString(iSan) + ". Entonces, ¡nos hemos encargado del sándalo ahora! Muy bien, a razón de 4000 pesos por pieza, tu recompensa totaliza " + FindRussianMoneyString(iSum) + ". Por favor, tómalo.";
			link.l1 = "¡Gracias!";
			link.l1.go = "clock_1";
			RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
			npchar.quest.sandal = "true";
			AddQuestRecord("alex_clock", "3");
			AddQuestUserData("alex_clock", "sGood", "ironwood");
		}
		AddMoneyToCharacter(pchar, iSum);
		break;

	case "oil": // смолы
		amount = sti(pchar.questTemp.AlexClock.Oil);
		iOil = GetSquadronGoods(pchar, GOOD_OIL);
		iTemp = amount - iOil;
		if (iTemp > 0) // ещё не все привез
		{
			iSum = 1400 * iOil;
			dialog.text = "Está bien, de acuerdo. También voy a necesitar " + FindRussianQtyString(amount) + " resinas. Me has traído " + FindRussianQtyString(iOil) + "Entonces, lo que te queda por traerme es " + FindRussianQtyString(iTemp) + " Está bien, a razón de 1400 pesos por contenedor, tu recompensa total es de " + FindRussianMoneyString(iSum) + " Por favor, tómalo.";
			link.l1 = "¡Gracias! Tendrás el resto pronto.";
			link.l1.go = "clock_1";
			RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
			pchar.questTemp.AlexClock.Oil = iTemp; // столько осталось довезти
			AddQuestRecord("alex_clock", "2");
			AddQuestUserData("alex_clock", "sGood", "resins");
			AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
		}
		else
		{
			iSum = 1400 * amount;
			dialog.text = "Está bien, de acuerdo. También voy a necesitar " + FindRussianQtyString(amount) + " resinas. Me has traído " + FindRussianQtyString(iOil) + ". ¡Así que ya nos hemos ocupado de las resinas! Muy bien, a razón de 1400 pesos por contenedor, tu recompensa asciende a " + FindRussianMoneyString(iSum) + ". Por favor, tómalo.";
			link.l1 = "¡Gracias!";
			link.l1.go = "clock_1";
			RemoveCharacterGoods(pchar, GOOD_OIL, amount);
			npchar.quest.oil = "true";
			AddQuestRecord("alex_clock", "3");
			AddQuestUserData("alex_clock", "sGood", "resins");
		}
		AddMoneyToCharacter(pchar, iSum);
		break;

	case "shipsilk": // шёлк
		amount = sti(pchar.questTemp.AlexClock.Shipsilk);
		iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
		iTemp = amount - iSil;
		if (iTemp > 0) // ещё не все привез
		{
			iSum = 2600 * iSil;
			dialog.text = "Está bien, de acuerdo. También voy a necesitar " + FindRussianQtyString(amount) + " seda. Me has traído " + FindRussianQtyString(iSil) + ". Entonces, lo que te queda por traerme es " + FindRussianQtyString(iTemp) + ". Muy bien, a razón de 2600 pesos por pieza, tu recompensa suma un total de " + FindRussianMoneyString(iSum) + "Por favor, tómalo.";
			link.l1 = "¡Gracias! Pronto tendrás el resto.";
			link.l1.go = "clock_1";
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
			pchar.questTemp.AlexClock.Shipsilk = iTemp; // столько осталось довезти
			AddQuestRecord("alex_clock", "2");
			AddQuestUserData("alex_clock", "sGood", "silk");
			AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
		}
		else
		{
			iSum = 2600 * amount;
			dialog.text = "Bien, de acuerdo. También voy a necesitar " + FindRussianQtyString(amount) + " seda. Me has traído " + FindRussianQtyString(iSil) + ". ¡Entonces, ya nos hemos encargado de la seda! Así que, a razón de 2600 pesos por pieza, tu recompensa asciende a " + FindRussianMoneyString(iSum) + "Por favor, tómalo.";
			link.l1 = "¡Gracias!";
			link.l1.go = "clock_1";
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
			npchar.quest.shipsilk = "true";
			AddQuestRecord("alex_clock", "3");
			AddQuestUserData("alex_clock", "sGood", "silk");
		}
		AddMoneyToCharacter(pchar, iSum);
		break;

	case "ropes": // канаты
		amount = sti(pchar.questTemp.AlexClock.Ropes);
		iRop = GetSquadronGoods(pchar, GOOD_ROPES);
		iTemp = amount - iRop;
		if (iTemp > 0) // ещё не все привез
		{
			iSum = 1500 * iRop;
			dialog.text = "Está bien, de acuerdo. También voy a necesitar " + FindRussianQtyString(amount) + " cuerdas. Me has traído " + FindRussianQtyString(iRop) + ". Entonces, lo que te queda por traerme es " + FindRussianQtyString(iTemp) + ". Así que, a la tasa de 1500 pesos por pieza, tu recompensa asciende a " + FindRussianMoneyString(iSum) + " Por favor, tómalo.";
			link.l1 = "¡Gracias! Tendrás el resto pronto.";
			link.l1.go = "clock_1";
			RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
			pchar.questTemp.AlexClock.Ropes = iTemp; // столько осталось довезти
			AddQuestRecord("alex_clock", "2");
			AddQuestUserData("alex_clock", "sGood", "ropes");
			AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
		}
		else
		{
			iSum = 1500 * amount;
			dialog.text = "Está bien, de acuerdo. También voy a necesitar " + FindRussianQtyString(amount) + "cuerdas. Me has traído " + FindRussianQtyString(iRop) + ". Así que, ya nos hemos encargado de las cuerdas. Muy bien, a razón de 1500 pesos por pieza, tu recompensa asciende a " + FindRussianMoneyString(iSum) + " Por favor, tómalo.";
			link.l1 = "¡Gracias!";
			link.l1.go = "clock_1";
			RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
			npchar.quest.ropes = "true";
			AddQuestRecord("alex_clock", "3");
			AddQuestUserData("alex_clock", "sGood", "ropes");
		}
		AddMoneyToCharacter(pchar, iSum);
		break;

	case "clock_2":
		dialog.text = "Sí, sí... sobre mi asunto, por supuesto. M-m-mmm... Hmmm... ¿dónde estaba yo...? Ahhh...";
		link.l1 = "¿Qué sucede, maestro? Pareces bastante preocupado. ¿Hay algo malo? ¿Algún tipo de problema?";
		link.l1.go = "clock_3";
		break;

	case "clock_3":
		dialog.text = "Precisamente. Problemas. Recientes. Malditos cazadores de tesoros...";
		link.l1 = "Tranquilízate, tranquilízate. No es bueno a tu edad preocuparse así. Dios no lo quiera, podrías estar a un latido de distancia. ¿Quién construiría la fragata para el jefe de los Hermanos entonces? Tranquilízate y explícame quiénes son esos cazadores de tesoros.";
		link.l1.go = "clock_4";
		break;

	case "clock_4":
		dialog.text = "Allí, junto a mi mesa, hay una puerta. Conduce directamente a una antigua bóveda. En esta bóveda, en uno de los cofres del tesoro, guardo mi caja de metal con objetos que estaban conmigo cuando fui arrastrado por ese maldito embudo hace veinte años, y terminé aquí...";
		link.l1 = "¿Qué embudo? ¿De qué estás hablando?";
		link.l1.go = "clock_5";
		break;

	case "clock_5":
		dialog.text = "Ah, disculpa por mis fantasías. Ser viejo no es fácil, joven. Perdóname. Pero es irrelevante. Lo relevante es que una caja con un regalo para ti está en el cofre que se encuentra en la mazmorra actualmente ocupada por unos canallas. No son nuestros hombres, ni de Isla Tesoro. Cazadores de tesoros, alguien debió decirles que este lugar está lleno de tesoros. No se atreverán a mostrarse aquí, sin embargo, yo tengo demasiado miedo para visitarlos, ¿ves? Sus caras son...";
		link.l1 = "Ya veo. Abre tu puerta. Expulsaré a tus invitados no deseados.";
		link.l1.go = "clock_6";
		break;

	case "clock_6":
		dialog.text = "¿Así nomás? ¿Los vencerás tú solo? ¿No tienes miedo? Tenemos todo un asentamiento que luchará por ti si solo lo pides...";
		link.l1 = "Menos charla, más acción, maestro. Abre esta puerta y deja el resto a mí. ¿En qué cofre guardas tus cosas?";
		link.l1.go = "clock_7";
		break;

	case "clock_7":
		dialog.text = "Justo al final del pasillo hay toda una colección de barriles de madera vacíos. Detrás de ellos, en el suelo, en un lugar apartado, hay un pequeño cofre. He colocado un candado en él, así que dudo que esos intrusos logren meter sus sucias manos dentro, incluso si lo encuentran. Aquí, toma la llave.";
		link.l1 = "Me alegra que pienses con anticipación. Espera aquí y no vayas a ninguna parte.";
		link.l1.go = "clock_8";
		break;

	case "clock_8":
		DialogExit();
		GiveItem2Character(pchar, "key3");
		bDisableFastReload = true; // закрыть переход
		LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", true);
		LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
		LAi_LocationDisableOfficersGen("Bermudes_Dungeon", true); // офицеров не пускать
		pchar.quest.Alex_Chest.win_condition.l1 = "location";
		pchar.quest.Alex_Chest.win_condition.l1.location = "Bermudes_Dungeon";
		pchar.quest.Alex_Chest.function = "AlexClock_Chest";
		pchar.quest.AlexClock_Over.over = "yes"; // снять прерывание
		pchar.questTemp.AlexClock = "chest";
		AddQuestRecord("alex_clock", "3");
		break;

	case "clock_complete":
		dialog.text = "¿Simplemente te escucharon y se fueron?";
		link.l1 = "Así es. Terminaron siendo unos tipos amables y educados. Les expliqué que su presencia estaba asustando al viejo y famoso constructor de barcos y, por respeto a tu avanzada edad, se retiraron del lugar. Puedes bajar allí sin preocupación.";
		link.l1.go = "clock_complete_1";
		break;

	case "clock_complete_1":
		dialog.text = "¡Ah-ha, te estás burlando de un viejo! Está bien. Dame mi caja y la abriré para darte el dispositivo que te has ganado con todo derecho.";
		link.l1 = "Por favor, tómalo...";
		link.l1.go = "clock_complete_2";
		break;

	case "clock_complete_2":
		RemoveItems(pchar, "alexs_chest", 1);
		dialog.text = "¡Gratitud! Vamos a abrirlo. Aquí, toma esto. Temporizador mecánico automático, nadie fabrica tales dispositivos aquí y nadie lo hará en los próximos trescientos años... eh, disculpa, por favor perdona al viejo. Todo lo que digo es que esta cosa es única\nHace todo el trabajo por sí misma, no necesitarás esos estúpidos relojes de arena y demás. ¡Sin errores! Solo mantenlo a salvo de golpes directos y agua, de lo contrario lo perderás. Hasta un mono puede usar este temporizador.";
		link.l1 = "¡Mira esto! ¡Nunca he visto algo tan milagroso en mi vida! Gracias, maestro.";
		link.l1.go = "clock_complete_3";
		break;

	case "clock_complete_3":
		GiveItem2Character(pchar, "clock3");
		Log_Info("Has recibido un temporizador mecánico automático");
		SetAlchemyRecipeKnown("sextant2");
		PlaySound("interface\important_item.wav");
		dialog.text = "De nada. Ahora siempre sabrás con certeza qué hora es. No me preguntes de dónde lo saqué. No te lo diré.";
		link.l1 = "Todos tienen sus secretos, ¿no es cierto, maestro? Bien... guarda tus secretos y yo no me meteré en tus asuntos. ¡Gracias por el regalo!";
		link.l1.go = "clock_complete_4";
		break;

	case "clock_complete_4":
		dialog.text = "Y gracias por tu ayuda, capitán. Visítame de vez en cuando. No olvides a un viejo constructor naval.";
		link.l1 = "Como si pudiera olvidarte... De todos modos, definitivamente haré eso, Alexus el Maestro. ¡Adiós!";
		link.l1.go = "clock_complete_5";
		break;

	case "clock_complete_5":
		DialogExit();
		bDisableFastReload = false;
		LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
		LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", false);
		LocatorReloadEnterDisable("Bermudes_Dungeon", "reload2_back", false);
		LAi_LocationDisableOfficersGen("Bermudes_Dungeon", false);
		AddQuestRecord("alex_clock", "5");
		CloseQuestHeader("alex_clock");
		DeleteAttribute(pchar, "questTemp.AlexClock");
		// belamour legendary edition на пару с Акулой
		pchar.questTemp.SharkGoldFleet.KGBB = true;
		if (CheckAttribute(pchar, "questTemp.SharkFrigate"))
			SetTimerCondition("SharkGoldFleet", 0, 0, 30, false);
		break;
		// <-- хронометр Алекса

	// город майя
	case "tieyasal":
		dialog.text = "¡Ajá, Miguel! Mi viejo conocido. Lo recuerdo. Me preguntaba sobre cada pequeño detalle una y otra vez. Pero, ¿cómo iba a explicarle cómo se construía un radio por dentro cuando ni siquiera había visto un simple telégrafo?";
		link.l1 = "¿Qué?.. ¿De qué hablas, maestro?";
		link.l1.go = "tieyasal_1";
		break;

	case "tieyasal_1":
		dialog.text = "Oh, lo siento, joven. No prestes mucha atención a lo que digo... Nuestro curioso Michel satisfizo su curiosidad y desapareció. Hace solo tres días que tuvimos una charla.";
		link.l1 = "¿Dónde está Miguel ahora mismo, si no te importa que pregunte?";
		link.l1.go = "tieyasal_2";
		break;

	case "tieyasal_2":
		dialog.text = "Quién sabe.  Tal vez esté haciendo sus negocios en Sharptown o tal vez ya haya partido de Isla Tesoro.";
		link.l1 = "Ya veo. ¡Gracias, maestro!";
		link.l1.go = "tieyasal_3";
		break;

	case "tieyasal_3":
		DialogExit();
		npchar.quest.tieyasal = "true";
		break;

	// Калеуче
	case "FDM":
		if (CheckAttribute(npchar, "quest.FDM_secondtime"))
			dialog.text = "De nuevo con tu 'barco fantasma'... Sepa esto: solo estoy trabajando en él con la esperanza de que se convierta en algo decente. De lo contrario, ni lo tocaría. Creo que todos en el mar comparten una opinión similar. ¿Qué quieres hacer con él esta vez?";
		else
			dialog.text = "¡Ah, el 'barco fantasma'! Las madres usan tu galeón para asustar a los niños traviesos. ¡Y tú decidiste quedarte con esa maldita nave en lugar de hundirla! Los marineros tiemblan cuando ven tu barco en el horizonte... Entonces, ¿qué quieres hacer con él?";
		if (!CheckAttribute(npchar, "quest.FDM_cabin"))
		{
			link.l1 = "Me gusta la idea de pequeños cobardes que están cagados de miedo. Pero el interior me pone triste. ¿Has visto la cabina? Se siente como un ataúd. Todo ese moho y polvo. Quiero arreglarlo. ¿Puedes hacer eso, maestro?";
			link.l1.go = "FDM_cabin";
		}
		if (!CheckAttribute(npchar, "quest.FDM_sails"))
		{
			link.l2 = "Estoy harto de estos harapos negros desgarrados. Lo admito, atrapan el viento tan bien como las velas normales, pero la vista... Repugnante. Quiero velas blancas como la nieve. ¿Estás de acuerdo, maestro?";
			link.l2.go = "FDM_sails";
		}

		if (!CheckAttribute(npchar, "quest.FDM_hull"))
		{
			link.l3 = "Bueno, creo que es hora de convertirla en algo decente. El barco es bueno, la tripulación está acostumbrada, pero simplemente no es digno de un respetable capitán navegar en una embarcación que puede hacer que los adultos se caguen de miedo, ni hablar de los niños. Quiero reconstruirla completamente para que otros capitanes la envidien cuando vean mi barco, en lugar de santiguarse. ¿Y a quién más debería acudir para esto sino al mejor constructor naval del archipiélago?";
			link.l3.go = "FDM_hull";
		}
		break;

	case "FDM_cabin":
		dialog.text = "¿Por qué no? Mis manos todavía son firmes. Tu galeón es enorme, así que incluso puedo hacer una cabina real como las que construyen en los navíos de línea y en los barcos de guerra. O podemos mantener una cabina estándar. ¿La elección es tuya?";
		link.l1 = "¡Construyan el camarote del navío de línea! Todos morirán de envidia...";
		link.l1.go = "FDM_cabin_m";
		link.l2 = "De nada sirven los lujos excesivos. Mantén el estándar.";
		link.l2.go = "FDM_cabin_s";
		break;

	case "FDM_cabin_m":
		dialog.text = "Bien. Diez cofres de doblones y estará listo en cinco días.";
		link.l1 = "¡Trato hecho!";
		link.l1.go = "FDM_cabin_m1";
		link.l2 = "¿Diez cofres? ¿Mil quinientos doblones? Hm, necesito tiempo para considerar tales gastos...";
		link.l2.go = "exit";
		break;

	case "FDM_cabin_s":
		dialog.text = "Bien. Siete arcones de doblones y estará hecho en cinco días.";
		link.l1 = "¡Trato hecho!";
		link.l1.go = "FDM_cabin_s1";
		link.l2 = "Siete cofres? ¿Más de mil doblones? Hm, necesito tiempo para considerar tales gastos...";
		link.l2.go = "exit";
		break;

	case "FDM_cabin_m1":
		iTemp = GetCharacterItem(pchar, "Chest");
		npchar.quest.FDM_cabin = 10;
		npchar.quest.FDM_cabin.type = "Cabin_Huge";
		dialog.text = "Bien, estaré esperando un pago.";
		if (iTemp > 0)
		{
			link.l1 = "Tengo cofres conmigo. Veamos. Aquí, " + FindRussianQtyString(iTemp) + ".";
			link.l1.go = "FDM_cabin_pay";
		}
		else
		{
			link.l1 = "Tengo que ir a poner monedas en los cofres.";
			link.l1.go = "FDM_cabin_wait";
		}
		break;

	case "FDM_cabin_s1":
		iTemp = GetCharacterItem(pchar, "Chest");
		npchar.quest.FDM_cabin = 7;
		npchar.quest.FDM_cabin.type = "Cabin";
		dialog.text = "Bien, estaré esperando un pago.";
		if (iTemp > 0)
		{
			link.l1 = "Tengo cofres conmigo. Vamos a ver. Aquí, " + FindRussianQtyString(iTemp) + ".";
			link.l1.go = "FDM_cabin_pay";
		}
		else
		{
			link.l1 = "Tengo que ir a poner monedas en los cofres.";
			link.l1.go = "FDM_cabin_wait";
		}
		break;

	case "FDM_cabin_wait":
		DialogExit();
		npchar.quest.FDM_full = "cabin";
		break;

	case "FDM_cabin_pay":
		iTemp = GetCharacterItem(pchar, "Chest");
		amount = sti(npchar.quest.FDM_cabin) - iTemp;
		Log_Info("Has entregado los cofres al Maestro Alexus");
		PlaySound("interface\important_item.wav");
		if (amount <= 0) // всё принес
		{
			RemoveItems(pchar, "chest", sti(npchar.quest.FDM_cabin));
			dialog.text = "Entonces, tenías que traerme " + FindRussianQtyString(sti(npchar.quest.FDM_cabin)) + " cofres, has traído " + FindRussianQtyString(iTemp) + ". Tengo el pago. Ahora es mi turno. Ve y da un paseo. No te preocupes, haré lo mejor que pueda.";
			link.l1 = "Bueno...";
			link.l1.go = "FDM_cabin_do";
		}
		else
		{
			RemoveItems(pchar, "chest", iTemp);
			dialog.text = "Entonces, tenías que traerme " + FindRussianQtyString(sti(npchar.quest.FDM_cabin)) + " cofres, has traído " + FindRussianQtyString(iTemp) + ". " + FindRussianQtyString(amount) + " cofres restantes.";
			link.l1 = "Muy bien, maestro.";
			link.l1.go = "FDM_cabin_wait";
			npchar.quest.FDM_cabin = amount;
		}
		break;

	case "FDM_cabin_do":
		DialogExit();
		SetLaunchFrameFormParam("Cinco días después..." + NewStr() + "El Maestro Alexus ha hecho su trabajo", "", 0, 5);
		WaitDate("", 0, 0, 5, 0, 10); // крутим время
		LaunchFrameForm();
		RefreshLandTime();
		RecalculateJumpTable();
		Whr_UpdateWeather();
		shTo = &RealShips[sti(Pchar.Ship.Type)];
		shTo.CabinType = npchar.quest.FDM_cabin.type;
		if (CheckAttribute(npchar, "quest.FDM_sails"))
			npchar.quest.FDM_full = "done";
		else
			DeleteAttribute(npchar, "quest.FDM_full");
		break;

	case "FDM_sails":
		dialog.text = "¡Claro, puedo hacerlo! Bueno-bueno... Esto significa que tenemos que desechar todos los viejos trapos sucios y colocar nuevas y limpias velas de algodón. Hay mucho trabajo por hacer aquí. Cien mil pesos por el trabajo y los materiales. ¿Trato?";
		if (sti(Pchar.money) >= 100000)
		{
			link.l1 = "Claro, estoy de acuerdo con eso. ¡Trato hecho!";
			link.l1.go = "FDM_sails_do";
		}
		link.l2 = "Hum. Supongo que necesito pensarlo...";
		link.l2.go = "exit";
		break;

	case "FDM_sails_do":
		AddMoneyToCharacter(pchar, -100000);
		dialog.text = "Bien. Tengo las monedas, es hora de hacer mi trabajo. Pasea un poco hasta que esté hecho y no te preocupes.";
		link.l1 = "Bueno...";
		link.l1.go = "FDM_sails_done";
		break;

	case "FDM_sails_done":
		DialogExit();
		SetLaunchFrameFormParam("Dos días después..." + NewStr() + "El Maestro Alexus ha hecho su trabajo", "", 0, 5);
		WaitDate("", 0, 0, 2, 0, 10); // крутим время
		LaunchFrameForm();
		RefreshLandTime();
		RecalculateJumpTable();
		Whr_UpdateWeather();
		SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
		SetSailsColor(pchar, 0); // белый хлопковый парус
		npchar.quest.FDM_sails = "true";
		if (CheckAttribute(npchar, "quest.FDM_cabin"))
			npchar.quest.FDM_full = "done";
		break;
	//--> Xenon
	case "FDM_hull":
		dialog.text = "Bueno, me alegra finalmente escuchar eso. Y es cierto, pareces un buen tipo, pero estás navegando en quién sabe qué. Pero déjame advertirte de antemano, este trabajo no es solo por unas pocas horas, y te costará un buen dinero.";
		link.l1 = "¿Puedes ser un poco más específico?";
		link.l1.go = "FDM_hull_01";
		break;

	case "FDM_hull_01":
		dialog.text = "Está bien, vamos a calcular... Para una renovación completa del casco del barco, necesitaré 150 unidades de sándalo, 130 bobinas de cuerdas, 170 rollos de seda naval y 200 barriles de resina. Cobraré 250 mil pesos por todo esto. ¡Y no me mires así, la mayor parte de ese dinero se irá en trabajo de todos modos! Después de todo, no estamos reconstruyendo una tartana.";
		link.l1 = "Creo que no. No estoy dispuesto a transportar una cantidad tan enorme de materiales junto con pagar un cuarto de millón por el trabajo. Supongo que seguiré navegando en él tal como está.";
		link.l1.go = "FDM_hull_thinking";
		link.l2 = "Eh, qué no haremos por nuestro barco...Está bien, es un trato.";
		link.l2.go = "FDM_hull_02";
		break;

	case "FDM_hull_02":
		dialog.text = "Bien, menos conversación, más acción. Estaré esperando el dinero de tu parte para que pueda comenzar a comprar todo lo que necesito. Una vez que tenga el dinero, puedes comenzar a traerme los materiales. Y me pondré a trabajar en tu barco.";
		if (sti(pchar.money) >= 250000)
		{
			link.l1 = "Bueno, el dinero no es un problema. Lo tengo conmigo. Aquí tienes, maestro.";
			link.l1.go = "FDM_hull_waitmaterials";
		}
		else
		{
			link.l1 = "En este momento, no tengo ese tipo de dinero. Espera un poco, te lo traeré.";
			link.l1.go = "FDM_hull_waitmoney";
		}
		break;

	case "FDM_hull_waitmaterials":
		addMoneyToCharacter(pchar, -250000);
		npchar.quest.FDMsandal = 0;
		npchar.quest.FDMoil = 0;
		npchar.quest.FDMshipsilk = 0;
		npchar.quest.FDMropes = 0;
		AddQuestRecord("renovate_fdm", "1");

		npchar.quest.FDM_hull = "hull_waitmaterials";
		dialog.text = "¿No tienes miedo de pasearte por un asentamiento pirata con una suma tan ordenada, jeje? Está bien, estoy bromeando, todos son personas honestas, a su manera. Ahora estoy esperando los materiales. Como recordatorio, necesitarás traer un total de 150 maderas de hierro, 130 rollos de cuerdas, 170 rollos de seda para barcos y 200 barriles de resina.";
		link.l1 = "Aguanta ahí, te traeré tus materiales.";
		link.l1.go = "exit";
		break;

	case "FDM_hull_checkmaterials":
		dialog.text = "¡Muy bien! ¿Qué me has traído hoy?";
		if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && sti(npchar.quest.FDMsandal) < 150)
		{
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			link.l1 = "Sándalo en la cantidad de " + FindRussianQtyString(iSan) + ".";
			link.l1.go = "FDM_sandal";
		}
		if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && sti(npchar.quest.FDMoil) < 200)
		{
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			link.l2 = "Resina en la cantidad de " + FindRussianQtyString(iOil) + ".";
			link.l2.go = "FDM_oil";
		}
		if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && sti(npchar.quest.FDMshipsilk) < 170)
		{
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			link.l3 = "Envío de seda en la cantidad de " + FindRussianQtyString(iSil) + ".";
			link.l3.go = "FDM_shipsilk";
		}
		if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && sti(npchar.quest.FDMropes) < 130)
		{
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			link.l4 = "Cuerdas en la cantidad de " + FindRussianQtyString(iRop) + ".";
			link.l4.go = "FDM_ropes";
		}
		link.l5 = "Aún nada. Solo quería asegurarme de que el trato sigue en pie.";
		link.l5.go = "exit";
		break;

	case "FDM_hull_checkmaterials_1":
		if (sti(npchar.quest.FDMsandal) > 149 && sti(npchar.quest.FDMoil) > 199 && sti(npchar.quest.FDMshipsilk) > 169 && sti(npchar.quest.FDMropes) > 129)
		{
			dialog.text = "¡Maravilloso! Todos los materiales están contabilizados. Ahora, déjame quitarte ese monstruo de las manos. Por fin, tendrá un aspecto adecuado.";
			link.l1 = "Está bien, basta de refunfuñar, maestro. Estoy ansioso por el resultado.";
			link.l1.go = "FDM_hull_building";
		}
		else
		{
			dialog.text = "¿Tienes algo más para alegrar mi día, Capitán?";
			link.l1 = "Por desgracia, eso es todo por ahora.";
			link.l1.go = "exit";
			link.l2 = "Sí, tengo algo más para ti...";
			link.l2.go = "FDM_hull_checkmaterials";
		}
		break;

	case "FDM_sandal": // бакаут
		amount = 150 - sti(npchar.quest.FDMsandal);
		iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
		iTemp = amount - iSan;
		if (iTemp > 0)
		{
			dialog.text = "Veamos... Requiero " + FindRussianQtyString(amount) + " de sándalo. Trajiste " + FindRussianQtyString(iSan) + ". Por lo tanto, todavía necesitas traerme " + FindRussianQtyString(iTemp) + ".";
			link.l1 = "¡Gracias! Te traeré el resto pronto.";
			link.l1.go = "FDM_hull_checkmaterials_1";
			RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
			npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + iSan;
			AddQuestRecord("renovate_fdm", "2");
			AddQuestUserData("renovate_fdm", "sGood", "ironwood");
			AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
		}
		else
		{
			dialog.text = "Veamos... Todavía necesito " + FindRussianQtyString(amount) + " de sándalo. Me trajiste " + FindRussianQtyString(iSan) + ". Por lo tanto, ¡hemos terminado con el sándalo!";
			link.l1 = "¡Gracias!";
			link.l1.go = "FDM_hull_checkmaterials_1";
			RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
			npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + amount;
			AddQuestRecord("renovate_fdm", "3");
			AddQuestUserData("renovate_fdm", "sGood", "ironwood");
		}
		break;

	case "FDM_oil": // смолы
		amount = 200 - sti(npchar.quest.FDMoil);
		iOil = GetSquadronGoods(pchar, GOOD_OIL);
		iTemp = amount - iOil;
		if (iTemp > 0)
		{
			dialog.text = "Veamos... Requiero " + FindRussianQtyString(amount) + " de resina. Trajiste " + FindRussianQtyString(iOil) + "Por lo tanto, todavía necesitas traerme " + FindRussianQtyString(iTemp) + ".";
			link.l1 = "¡Gracias! Te traeré el resto pronto.";
			link.l1.go = "FDM_hull_checkmaterials_1";
			RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
			npchar.quest.FDMoil = sti(npchar.quest.FDMoil) + iOil;
			AddQuestRecord("renovate_fdm", "2");
			AddQuestUserData("renovate_fdm", "sGood", "resin");
			AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
		}
		else
		{
			dialog.text = "Veamos... Aún necesito " + FindRussianQtyString(amount) + " de resina. Me trajiste " + FindRussianQtyString(iOil) + ". Por lo tanto, ¡hemos terminado con la resina!";
			link.l1 = "¡Gracias!";
			link.l1.go = "FDM_hull_checkmaterials_1";
			RemoveCharacterGoods(pchar, GOOD_OIL, amount);
			npchar.quest.FDMoil = makeint(npchar.quest.FDMoil) + amount;
			AddQuestRecord("renovate_fdm", "3");
			AddQuestUserData("renovate_fdm", "sGood", "resin");
		}
		break;

	case "FDM_shipsilk": // шёлк
		amount = 170 - sti(npchar.quest.FDMshipsilk);
		iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
		iTemp = amount - iSil;
		if (iTemp > 0)
		{
			dialog.text = "Veamos... Requiero " + FindRussianQtyString(amount) + " de seda del barco. Trajiste " + FindRussianQtyString(iSil) + "  Por lo tanto, todavía necesitas traerme " + FindRussianQtyString(iTemp) + ".";
			link.l1 = "¡Gracias! Te traeré el resto pronto";
			link.l1.go = "FDM_hull_checkmaterials_1";
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
			npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + iSil;
			AddQuestRecord("renovate_fdm", "2");
			AddQuestUserData("renovate_fdm", "sGood", "ship silk");
			AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
		}
		else
		{
			dialog.text = "Veamos... Todavía necesito " + FindRussianQtyString(amount) + " de seda de barco. Por lo tanto, aún necesitas traerme " + FindRussianQtyString(iSil) + ". Por lo tanto, hemos terminado con la seda del barco";
			link.l1 = "¡Gracias!";
			link.l1.go = "FDM_hull_checkmaterials_1";
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
			npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + amount;
			AddQuestRecord("renovate_fdm", "3");
			AddQuestUserData("renovate_fdm", "sGood", "ship silk");
		}
		break;

	case "FDM_ropes": // канаты
		amount = 170 - sti(npchar.quest.FDMropes);
		iRop = GetSquadronGoods(pchar, GOOD_ROPES);
		iTemp = amount - iRop;
		if (iTemp > 0)
		{
			dialog.text = "Veamos... Necesito " + FindRussianQtyString(amount) + " de cuerdas. Trajiste " + FindRussianQtyString(iRop) + "Por lo tanto, todavía necesitas traerme " + FindRussianQtyString(iTemp) + ".";
			link.l1 = "¡Gracias! Pronto te daré el resto";
			link.l1.go = "FDM_hull_checkmaterials_1";
			RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
			npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + iRop;
			AddQuestRecord("renovate_fdm", "2");
			AddQuestUserData("renovate_fdm", "sGood", "ropes");
			AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
		}
		else
		{
			dialog.text = "Veamos... Requiero  " + FindRussianQtyString(amount) + " de cuerdas. Has traído " + FindRussianQtyString(iRop) + "¡Por lo tanto, hemos terminado con las cuerdas!";
			link.l1 = "¡Gracias!";
			link.l1.go = "FDM_hull_checkmaterials_1";
			RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
			npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + amount;
			AddQuestRecord("renovate_fdm", "3");
			AddQuestUserData("renovate_fdm", "sGood", "ropes");
		}
		break;

	case "FDM_hull_thinking":
		DialogExit();
		npchar.quest.FDM_secondtime = true;
		break;

	case "FDM_hull_waitmoney":
		DialogExit();
		npchar.quest.FDM_hull = "hull_waitmoney";
		break;

	case "FDM_hull_givemoney":
		dialog.text = "Bueno, ¿trajiste el dinero?";
		if (sti(pchar.money) >= 250000)
		{
			link.l2 = "Sí, lo hice. 250 000 pesos, como acordamos.";
			link.l2.go = "FDM_hull_waitmaterials";
		}
		else
		{
			link.l1 = "Aún no, espera, maestro.";
			link.l1.go = "exit";
		}
		break;

	case "FDM_hull_building":
		DialogExit();
		SetLaunchFrameFormParam("Pasaron cinco días..." + NewStr() + "El maestro Alexus completó el trabajo", "", 0, 5);
		WaitDate("", 0, 0, 5, 0, 10); // Pass time
		LaunchFrameForm();
		RefreshLandTime();
		RecalculateJumpTable();
		Whr_UpdateWeather();
		RealShips[sti(Pchar.Ship.Type)].BaseType = SHIP_RENOVATED_FDM;
		RealShips[sti(Pchar.Ship.Type)].Name = "NewFlyingdutchman1";
		RealShips[sti(Pchar.Ship.Type)].BaseName = "NewFlyingdutchman";
		/* RealShips[sti(Pchar.Ship.Type)].CannonsQuantity = 58;
		RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMax = 58;
		RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMin = 58;
		RealShips[sti(Pchar.Ship.Type)].rcannon = 24;
		RealShips[sti(Pchar.Ship.Type)].lcannon = 24;
		RealShips[sti(Pchar.Ship.Type)].fcannon = 6;
		RealShips[sti(Pchar.Ship.Type)].bcannon = 4; */
		if (Get_My_Cabin() == "My_Cabin")
			RealShips[sti(Pchar.Ship.Type)].CabinType = "Cabin";
		else
			RealShips[sti(Pchar.Ship.Type)].CabinType = "Cabin_Huge";
		SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
		SetSailsColor(pchar, 0); // White cotton sail
		RealShips[sti(Pchar.Ship.Type)].HP = GetCharacterShipBaseHP(pchar);
		pchar.ship.hp = GetCharacterShipBaseHP(pchar);
		DeleteAttribute(pchar, "ship.hulls");
		DeleteAttribute(pchar, "ship.blots");
		CloseQuestHeader("renovate_fdm");
		break;
		//<-- Xenon
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

void checkMatherial_repair(ref Pchar, ref NPChar, int good, int goodType)
{
	int amount;
	string Matherial = "Matherial" + goodType;
	amount = GetSquadronGoods(Pchar, good) - sti(NPChar.Repair.(Matherial));

	if (amount < 0)
	{
		amount = amount + sti(NPChar.Repair.(Matherial));
	}
	else
	{
		amount = sti(NPChar.Repair.(Matherial));
	}
	RemoveCharacterGoods(Pchar, good, amount);
	NPChar.Repair.(Matherial) = sti(NPChar.Repair.(Matherial)) - amount;
}

int GetMaterialQtyRepair(ref _chr, int MaterialNum)
{
	if (sti(_chr.Ship.Type) == SHIP_NOTUSED)
		return 0;

	int shipCurHP = sti(RealShips[sti(_chr.Ship.Type)].HP);
	int shipBaseHP = sti(RealShips[sti(_chr.Ship.Type)].BaseHP);
	int shipClass = sti(RealShips[sti(_chr.Ship.Type)].Class);
	int shipWeight = CWT2Tonnes(sti(RealShips[sti(_chr.Ship.Type)].Weight));
	int HPPrice = shipWeight * (1.2 - makefloat(shipCurHP) / makefloat(shipBaseHP));
	int modifier = (2 * MOD_SKILL_ENEMY_RATE) + sti(RealShips[sti(_chr.Ship.Type)].MinCrew) / 2 + 1;

	float fQuest = 1.0;
	if (CheckAttribute(&RealShips[sti(_chr.Ship.Type)], "QuestShip"))
	{
		fQuest = 1.3;
		HPPrice = HPPrice * 2;
	}

	int Matherial1 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);
	int Matherial2 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);
	int Matherial3 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);
	int Matherial4 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);

	if (MaterialNum == 0)
		return HPPrice;
	if (MaterialNum == 1)
		return Matherial1;
	if (MaterialNum == 2)
		return Matherial2;
	if (MaterialNum == 3)
		return Matherial3;
	if (MaterialNum == 4)
		return Matherial4;

	return 0;
}

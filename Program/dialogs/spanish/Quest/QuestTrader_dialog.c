void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		bool ok = CheckFreeSitFront(npchar);
		if (hrand(11) > 8 && ok && !CheckAttribute(pchar, "GenQuest.Racing.Go") && !CheckAttribute(npchar, "quest.race") && sti(Pchar.Ship.Type) != SHIP_NOTUSED && 6 - sti(RealShips[sti(pchar.ship.type)].Class) > 0) // гонки на гидропланах
		{
			dialog.text = TimeGreeting() + ", " + GetAddress_Form(NPChar) + "¡ Mi nombre es " + GetFullName(NPChar) + ", soy un capitán. Veo que tú también eres un capitán. ¿Te gustaría unirte a mí y tomar una copa juntos? Invito yo.";
			link.l1 = "¿Por qué no? No me importaría tomar unas copas en buena compañía.";
			link.l1.go = "Race_prepare";
			link.l2 = "Lo siento, pero tengo prisa. La próxima vez.";
			link.l2.go = "exit";
			npchar.quest.race = "true";
		}
		else
		{
			// конвой торгового судна
			if (!CheckAttribute(pchar, "GenQuest.Escort.Trader") && !CheckAttribute(npchar, "quest.race") && sti(Pchar.Ship.Type) != SHIP_NOTUSED && !CheckAttribute(npchar, "repeat_work") && 6 - sti(RealShips[sti(pchar.ship.type)].Class) > 0 && GetCompanionQuantity(pchar) < 3)
			{
				dialog.text = TimeGreeting() + ", " + GetAddress_Form(NPChar) + "¡ Yo soy " + GetFullName(NPChar) + ", un mercader. Supongo que eres un capitán. ¿Qué tal hacer unos cuantos miles de pesos?";
				link.l1 = "Siempre estoy ansioso por ganar algunas monedas. ¿De qué tipo de trabajo estamos hablando?";
				link.l1.go = "Escort_choice";
				link.l2 = "¿Y qué clase de trabajo puede proponer el comerciante, eh? ¿Proteger su nave podrida? No ayudo a los acaparadores.";
				link.l2.go = "exit_distress";
				SaveCurrentNpcQuestDateParam(npchar, "repeat_work");
			}
			else
			{
				dialog.text = TimeGreeting() + ", " + GetAddress_Form(NPChar) + "¡Cómo te va? ¿Necesitas algo?";
				link.l1 = TimeGreeting() + ", " + GetAddress_FormToNPC(NPChar) + "No, no lo hago. Solo quería saludar. ¡Disfruta tu estancia!";
				link.l1.go = "exit";
			}
		}
		break;

	case "exit_distress":
		DialogExit();
		NextDiag.CurrentNode = "Trader_distress";
		break;

	case "Trader_distress":
		dialog.text = "Capitán, ya hemos hablado, ¿verdad? Tú 'no ayudas a los especuladores', entonces, ¿qué quieres de mí ahora?";
		link.l1 = "Sí, y tienes razón. Bien, solo siéntate en tu gordo trasero aquí y bebe tu ron. Tengo que irme.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Trader_distress";
		break;

	case "Escort_choice":										   // первые развилки - выбираем между городом, бухтой и необитайкой
		pchar.GenQuest.Escort.Trader.StartCity = GetCurrentTown(); // стартовый город
		pchar.GenQuest.Escort.Trader.ShipType = TraderShipType(&iTemp);  // тип корабля торговца
		pchar.GenQuest.Escort.Trader.Nation = npchar.nation;	   // нация торговца
		switch (hrand(2))
		{
		case 0:																																														   // город дружественный
			pchar.GenQuest.Escort.Trader.City = FindFriendCityToMC(false);																															   // целевой город
			pchar.GenQuest.Escort.Trader.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Escort.Trader.StartCity), GetArealByCityName(pchar.GenQuest.Escort.Trader.City)) + 5; // дни
			pchar.GenQuest.Escort.Trader.Money =  makeint(sti(pchar.GenQuest.Escort.Trader.DaysQty) * 400 * ShipFactorMC() + iTemp * 700);						   // оплата от расстояния и классов кораблей ГГ и неписи
			pchar.GenQuest.Escort.Trader.Type1 = "true";																																			   // тип задания
			pchar.GenQuest.Escort.Trader.Chance = rand(1);
			pchar.GenQuest.Escort.Trader.Add = "a " + XI_ConvertString("Colony" + pchar.GenQuest.Escort.Trader.City + "Gen") + "";
			dialog.text = "Me gustaría pedirte que me escoltes a " + XI_ConvertString("Colony" + pchar.GenQuest.Escort.Trader.City + "Gen") + " dentro de " + FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty)) + ". Te pagaré " + FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)) + ".";
			link.l1 = "¿Y por qué no? Siempre es más seguro navegar juntos, lo entiendo. Estoy de acuerdo.";
			link.l1.go = "EscortType";
			link.l2 = "Me alegraría ayudar, pero estoy yendo en otra dirección.";
			link.l2.go = "Escort_exit";
			break;
		case 1:						// бухта
			GetEscortTraderShore(); // целевая бухта
			while (pchar.GenQuest.Escort.Trader.City == "Terks" || pchar.GenQuest.Escort.Trader.City == "caiman" || pchar.GenQuest.Escort.Trader.City == "dominica" || pchar.GenQuest.Escort.Trader.City == "Pearl" || pchar.GenQuest.Escort.Trader.City == "Tenotchitlan")
			{
				GetEscortTraderShore();
			} // patch-6
			pchar.GenQuest.Escort.Trader.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Escort.Trader.StartCity), pchar.GenQuest.Escort.Trader.Island) + 5; // дни
			pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.DaysQty) * 400 * ShipFactorMC() + iTemp * 700);		 // оплата
			pchar.GenQuest.Escort.Trader.Type2 = "true";																															 // тип задания
			pchar.GenQuest.Escort.Trader.Chance = rand(2);
			pchar.GenQuest.Escort.Trader.Add = "a " + XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore + "Gen") + ", no lejos de " + XI_ConvertString("Colony" + pchar.GenQuest.Escort.Trader.City + "Gen") + "";
			dialog.text = "Me gustaría pedirte que me escoltes a " + XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore + "Gen") + ", no lejos de " + XI_ConvertString("Colony" + pchar.GenQuest.Escort.Trader.City + "Gen") + " dentro de " + FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty)) + ". Te pagaré " + FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)) + ".";
			link.l1 = "¿Y por qué no? Siempre es más seguro navegar juntos, lo puedo entender. Estoy de acuerdo.";
			link.l1.go = "EscortType";
			link.l2 = "Me alegraría ayudar, pero voy en la dirección opuesta.";
			link.l2.go = "Escort_exit";
			break;
		case 2:																																										 // необитайка
			pchar.GenQuest.Escort.Trader.Island = DesIsland();																														 // целевой остров
			pchar.GenQuest.Escort.Trader.Shore = SelectQuestShoreLocationFromSea(pchar.GenQuest.Escort.Trader.Island);																 // и бухта на нём
			pchar.GenQuest.Escort.Trader.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Escort.Trader.StartCity), pchar.GenQuest.Escort.Trader.Island) + 5; // дни
			pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.DaysQty) * 400 * ShipFactorMC() + iTemp * 700);		 // оплата
			pchar.GenQuest.Escort.Trader.Type3 = "true";																															 // тип задания
			pchar.GenQuest.Escort.Trader.Chance = rand(2);
			pchar.GenQuest.Escort.Trader.Add = "a " + XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore + "Gen") + " de la isla deshabitada  " + XI_ConvertString(pchar.GenQuest.Escort.Trader.Island) + "";
			dialog.text = "Me gustaría pedirte que me escoltes a " + XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore + "Gen") + " que está en " + XI_ConvertString(pchar.GenQuest.Escort.Trader.Island) + ", en " + FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty)) + ". Te pagaré " + FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)) + ".";
			link.l1 = "¿Y por qué no? Siempre es más seguro navegar juntos, lo puedo entender. Estoy de acuerdo. Pero nunca he oído hablar de tiendas y puestos de comercio allí.";
			link.l1.go = "EscortType";
			link.l2 = "Me encantaría ayudar, pero voy en otra dirección.";
			link.l2.go = "Escort_exit";
			break;
		}
		break;

	case "Escort_exit":
		DialogExit();
		DeleteAttribute(pchar, "GenQuest.Escort.Trader");
		break;

	case "Trader_wait":
		dialog.text = "¿Está listo para zarpar, capitán? Estoy esperando sus órdenes.";
		link.l1 = "Sí, vamos a zarpar ahora. Nos vemos en el puerto.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Trader_wait";
		break;

	case "EscortType":
		dialog.text = "¡Espléndido! Me alegra que hayamos llegado a un acuerdo. Espero que nuestro viaje sea seguro.";
		link.l1 = "Yo también. ¡Es hora de zarpar!";
		link.l1.go = "EscortType_go";
		NextDiag.CurrentNode = "Trader_wait";
		break;

	case "EscortType_go":
		// общие параметры
		DialogExit();
		pchar.GenQuest.Escort.Trader.id = npchar.id;
		CreateTraderShipAndAdd(npchar); // присоединяем торговца
		pchar.GenQuest.Escort.Trader.ShipMaxHP = sti(npchar.ship.HP);
		ReOpenQuestHeader("TraderEscort");
		AddQuestRecord("TraderEscort", "1");
		AddQuestUserData("TraderEscort", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty)));
		AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
		AddQuestUserData("TraderEscort", "sStartCity", XI_ConvertString("Colony" + pchar.GenQuest.Escort.Trader.StartCity + "Gen"));
		AddQuestUserData("TraderEscort", "sAdd", pchar.GenQuest.Escort.Trader.Add);
		pchar.GenQuest.Escort.Trader = "begin";
		// различные параметры
		if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type1")) // в дружественный город
		{
			pchar.GenQuest.Escort.Trader.Location = pchar.GenQuest.Escort.Trader.City + "_tavern";
			if (sti(pchar.GenQuest.Escort.Trader.Chance) == 1)
				TraderHunterOnMap(true);
			else
				TraderHunterOnMap(false); // запуск ДУ на глобалке
		}
		if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type2")) // в бухту
		{
			pchar.GenQuest.Escort.Trader.Location = pchar.GenQuest.Escort.Trader.Shore;
			if (sti(pchar.GenQuest.Escort.Trader.Chance) != 2)
				TraderHunterOnMap(false);
			else
			{
				pchar.quest.EscortTrader_Attack.win_condition.l1 = "location";
				pchar.quest.EscortTrader_Attack.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Island;
				pchar.quest.EscortTrader_Attack.function = "EscortTraderAttackInShore";
			}
		}
		if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type3")) // на необитайку
		{
			pchar.GenQuest.Escort.Trader.Location = pchar.GenQuest.Escort.Trader.Shore;
			if (sti(pchar.GenQuest.Escort.Trader.Chance) == 0)
				TraderHunterOnMap(false);
			if (sti(pchar.GenQuest.Escort.Trader.Chance) == 1)
			{
				if(sti(RealShips[sti(pchar.Ship.Type)].Class) >= sti(RealShips[sti(pchar.GenQuest.Escort.Trader.ShipType)].Class) && sti(RealShips[sti(pchar.Ship.Type)].BaseType) != SHIP_GALEON_H && GetCompanionQuantity(pchar) < 3)//меряемся кораблями
				{																																																	  // нападет сам
					pchar.quest.EscortTrader_Attack.win_condition.l1 = "location";
					pchar.quest.EscortTrader_Attack.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Island;
					pchar.quest.EscortTrader_Attack.function = "DesIslandAttack";
				}
				else
					TraderHunterOnMap(true);
			}
			else
			{ // будет засада + сам нападет
				pchar.quest.EscortTrader_Attack.win_condition.l1 = "location";
				pchar.quest.EscortTrader_Attack.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Island;
				pchar.quest.EscortTrader_Attack.function = "DesIslandAttack";
			}
		}
		pchar.quest.EscortTrader_Complete.win_condition.l1 = "location";
		pchar.quest.EscortTrader_Complete.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Location;
		pchar.quest.EscortTrader_Complete.function = "EscortTraderComplete";
		SetFunctionTimerCondition("EscortTrader_Over", 0, 0, sti(pchar.GenQuest.Escort.Trader.DaysQty), false);
		pchar.quest.EscortTrader_fail.win_condition.l1 = "NPC_Death"; // прерывание на потопление сопровождаемого
		pchar.quest.EscortTrader_fail.win_condition.l1.character = pchar.GenQuest.Escort.Trader.id;
		pchar.quest.EscortTrader_fail.function = "EscortTrader_failed";
		break;

	case "EscortTrader_complete": // сдаём квест
		sld = characterFromId(pchar.GenQuest.Escort.Trader.id);
		if (sti(sld.ship.HP) < makeint(sti(pchar.GenQuest.Escort.Trader.ShipMaxHP) / 4)) // если корпуса осталось меньше 1/4 - первая проверка
		{
			dialog.text = "Capitán, dime por qué te he contratado. ¡Mira mi barco! ¿Qué parece? ¡Está arruinado! Apenas se mantiene a flote. ¿No lo ves? No lo entiendo, ¿quién escoltaba a quién? De todos modos, no recibirás ninguna recompensa, olvídalo.";
			link.l1 = "Si no fuera por mí, estarías alimentando cangrejos, maldito mercader. Está bien, es tu día de suerte, pero el mundo es pequeño y algún día te encontraré en mar abierto.";
			link.l1.go = "EscortTrader_complete_1";
			break;
		}
		if (sti(sld.ship.HP) < makeint(sti(pchar.GenQuest.Escort.Trader.ShipMaxHP) / 2)) // если корпуса осталось меньше 1/2 - вторая проверка
		{
			pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.Money)) / 2;
			dialog.text = "Capitán, dime ¿por qué te contraté? ¡Mira mi barco! ¿Cómo se ve? ¡Está arruinado! Apenas se mantiene a flote... ¿No lo ves? De todos modos, te pagaré solo la mitad de tu recompensa. ¡No cuentes con recibir más!";
			link.l1 = "Mm... Bien, estoy de acuerdo. Tu barco está realmente... un poco dañado...";
			link.l1.go = "EscortTrader_complete_2";
			break;
		}
		if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type2") && sti(pchar.GenQuest.Escort.Trader.Chance) == 1) // вместо денег - наводка
		{
			dialog.text = "Capitán, verá... No tengo dinero para pagarle por su trabajo. ¡Pero no se preocupe, por favor, quiero ofrecerle otro tipo de pago que es mucho mayor de lo que le he prometido antes!";
			link.l1 = "Hmm... En realidad esperaba recibir monedas ahora mismo. Pero soy todo oídos si ese es el caso.";
			link.l1.go = "EscortTrader_complete_4";
			break;
		}
		dialog.text = "Muchas gracias, capitán. Fue una navegación segura contigo a pesar de todos los peligros. Aquí, toma tu recompensa.";
		link.l1 = "De nada... Solo hice mi trabajo.";
		link.l1.go = "EscortTrader_complete_3";
		break;

	case "EscortTrader_complete_1":
		dialog.text = "¡No trates de asustarme! Tus habilidades de combate hacen que tus amenazas sean patéticas. ¡Adiós!";
		link.l1 = "Piérdete mientras puedas, bucanero...";
		link.l1.go = "complete_exit";
		AddQuestRecord("TraderEscort", "4");
		AddComplexSeaExpToScill(20, 20, 20, 0, 20, 0, 0);
		AddCharacterExpToSkill(pchar, "Fortune", 20); // везение
		break;

	case "EscortTrader_complete_2":
		dialog.text = "Sí, una observación muy sabia... Aquí, toma tu " + FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)) + " y adiós.";
		link.l1 = "Nos vemos, " + npchar.name + ".";
		link.l1.go = "complete_exit";
		AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Escort.Trader.Money));
		AddQuestRecord("TraderEscort", "5");
		AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
		AddComplexSeaExpToScill(50, 50, 50, 0, 50, 0, 50);
		AddCharacterExpToSkill(pchar, "Fortune", 40); // везение
		break;

	case "EscortTrader_complete_3":
		dialog.text = "¡Lo hiciste genial! Bueno, ahora debo irme. ¡Adiós, capitán!";
		link.l1 = "Buena suerte, " + npchar.name + ".";
		link.l1.go = "complete_exit";
		AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Escort.Trader.Money));
		AddQuestRecord("TraderEscort", "6");
		AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
		AddComplexSeaExpToScill(100, 100, 100, 50, 100, 100, 150);
		AddCharacterExpToSkill(pchar, "Leadership", 80); // авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 80);	 // везение
		AddCharacterExpToSkill(pchar, "Sneak", 50);		 // скрытность
		break;

	case "EscortTrader_complete_4":
		pchar.GenQuest.Escort.Trader.Enemyname = GenerateRandomName_Generator(sti(npchar.nation), "man");
		GetEnemyTraderGoods();
		pchar.GenQuest.Escort.Trader.EnIsland = DesIsland();
		dialog.text = "Hay un mercader, " + pchar.GenQuest.Escort.Trader.Enemyname + ". Él posee y comanda un filibote. Me informaron que en dos semanas llegará a la isla habitada " + XI_ConvertString(pchar.GenQuest.Escort.Trader.EnIsland) + ", para reponer sus suministros de agua y comerciar con los indios locales. Tendrá un montón de " + pchar.GenQuest.Escort.Trader.add + " abordo. Un luchador patético, no enfrentarás problemas al tomar su barco.\nAsí que te beneficiarás de ello de todas formas, capitán.";
		link.l1 = "¿Homo homini lupus est?";
		link.l1.go = "EscortTrader_complete_5";
		break;

	case "EscortTrader_complete_5":
		dialog.text = "¿Perdón?";
		link.l1 = "Eres tan fácil y honestamente 'delatando' a tu colega... Pero me importa poco tu conciencia y te agradezco por esta información. ¡Buena suerte, señor!";
		link.l1.go = "EscortTrader_complete_6";
		break;

	case "EscortTrader_complete_6":
		DialogExit();
		chrDisableReloadToLocation = false;
		bDisableFastReload = false;
		pchar.quest.EscortTrader_fail.over = "yes";
		pchar.quest.EscortTrader_Over.over = "yes"; // снять оба прерывания
		npchar.lifeday = 0;
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
		RemoveCharacterCompanion(Pchar, npchar);
		AddQuestRecord("TraderEscort", "7");
		AddQuestUserData("TraderEscort", "sIsland", XI_ConvertString(pchar.GenQuest.Escort.Trader.EnIsland));
		AddQuestUserData("TraderEscort", "sAdd", pchar.GenQuest.Escort.Trader.add);
		pchar.quest.EscortTrader_EnTrader.win_condition.l1 = "Timer";
		pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.hour = sti(GetTime());
		pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.day = GetAddingDataDay(0, 0, 12);
		pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 12);
		pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.year = GetAddingDataYear(0, 0, 12);
		pchar.quest.EscortTrader_EnTrader.win_condition.l2 = "location";
		pchar.quest.EscortTrader_EnTrader.win_condition.l2.location = pchar.GenQuest.Escort.Trader.EnIsland;
		pchar.quest.EscortTrader_EnTrader.function = "Create_EnemyTraderFleut";
		SetFunctionTimerCondition("EscortTraderEnemy_Over", 0, 0, 16, false); // таймер
		AddComplexSeaExpToScill(100, 100, 100, 50, 100, 100, 150);
		AddCharacterExpToSkill(pchar, "Leadership", 80); // авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 80);	 // везение
		AddCharacterExpToSkill(pchar, "Sneak", 50);		 // скрытность
		break;

	case "complete_exit":
		DialogExit();
		CloseQuestHeader("TraderEscort");
		chrDisableReloadToLocation = false;
		bDisableFastReload = false;
		pchar.quest.EscortTrader_fail.over = "yes";
		pchar.quest.EscortTrader_Over.over = "yes";	  // снять оба прерывания
		pchar.quest.EscortTrader_Attack.over = "yes"; // patch-8
		npchar.lifeday = 0;
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
		RemoveCharacterCompanion(Pchar, npchar);
		DeleteAttribute(pchar, "GenQuest.Escort.Trader");
		break;

	case "Race_prepare":
		NextDiag.TempNode = "Race_begin";
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		pchar.questTemp.friend_in_tavern = npchar.id;
		AddDialogExitQuest("alc");
		break;

	case "exit_sit":
		NextDiag.CurrentNode = "First time";
		DialogExit();
		AddDialogExitQuest("exit_sit");
		break;

	case "Race_begin": // гонки на гидропланах
		dialog.text = "Eh, ¡bebamos un buen ron añejo, capitán! ¿Cómo estás, cómo va tu comercio?";
		link.l1 = "No soy realmente un mercader. Pero me las arreglo bien.";
		link.l1.go = "Race_begin_1";
		break;

	case "Race_begin_1":
		dialog.text = "¡Y eso es lo más importante! Considerando los peligros en el mar abierto.";
		link.l1 = "Sí, tienes razón. Especialmente para ustedes, los comerciantes, hay muchos cazadores tras su carga. Y rara vez pueden ni huir ni defenderse. Sus naves son lentas y sus cañones son pequeños, ya que anteponen sus ganancias. Navegar en convoyes con cuatro o cinco barcos juntos, eso es lo que los salva.";
		link.l1.go = "Race_begin_2";
		break;

	case "Race_begin_2":
		dialog.text = "Bueno, no todos somos así, amigo. Yo siempre navego solo, no necesito lastre alguno. Conozco perfectamente el mar Caribe y, si se me permite decirlo, soy realmente bueno en la navegación, la vela y el mando de mis hombres. Soy capaz de dejar atrás a cualquier pirata.";
		link.l1 = "¿De verdad? Apenas puedo creerlo. ¿Con la bodega llena? ¿En el barco mercante? ¿Entonces quieres decir que puedes escapar de un bergantín pirata, un lugre o una corbeta rápida?";
		link.l1.go = "Race_begin_3";
		break;

	case "Race_begin_3":
		dialog.text = "Parece que tú, amigo, estás dudando de que mi barco sea capaz de navegar rápido. Bien. Te ofrezco una apuesta.";
		link.l1 = "¿Qué tipo de apuesta?";
		link.l1.go = "Race_begin_4";
		break;

	case "Race_begin_4": // тут устанавливаем все параметры
		if (!CheckAttribute(pchar, "GenQuest.Racing"))
			pchar.GenQuest.Racing.Count = 0;
		pchar.GenQuest.Racing.Go.Nation = npchar.nation;
		pchar.GenQuest.Racing.Go.StartCity = GetCurrentTown();
		pchar.GenQuest.Racing.Go.City = FindFriendCityToMC(false); // целевой дружественный город
		pchar.GenQuest.Racing.Go.Island = GetIslandByCityName(pchar.GenQuest.Racing.Go.City);
		pchar.GenQuest.Racing.Go.DaysQty = makeint((GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Racing.Go.StartCity), GetArealByCityName(pchar.GenQuest.Racing.Go.City))) / 1.3); // дни
		pchar.GenQuest.Racing.Go.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
		if (sti(pchar.GenQuest.Racing.Go.DaysQty) < 1)
			pchar.GenQuest.Racing.Go.DaysQty = 1; // patch-8
		dialog.text = "Escucha. Hoy voy a zarpar hacia " + XI_ConvertString("Colony" + pchar.GenQuest.Racing.Go.City) + ". Y digo que estaré allí en " + FindRussianDaysString(pchar.GenQuest.Racing.Go.DaysQty) + ". Intenta superarme y llegar a " + XI_ConvertString("Colony" + pchar.GenQuest.Racing.Go.City) + " más pronto. El tiempo empieza a correr ahora. ¿Quieres arriesgarte? ¿O es demasiado difícil para ti?";
		link.l1 = "¿Para quién? ¿Para mí? No seas tan gracioso. ¿Vas a lograrlo en ese tiempo? Ridículo. Bien, acepto tu apuesta. ¿Cuánto estás dispuesto a perder?";
		link.l1.go = "Race_begin_5";
		link.l2 = "Estoy demasiado ocupado para empezar una carrera por unas tontas jactancias.";
		link.l2.go = "Race_exit";
		break;

	case "Race_exit":
		dialog.text = "Hm... ¿Tienes miedo de perder? Como sea. Pero no juzgues tan rápido a los demás, hay muchos marineros experimentados entre los mercaderes... mucho más experimentados que tú.";
		link.l1 = "Bien, bien, no me sermonees, filósofo. Adiós...";
		link.l1.go = "exit_sit";
		DeleteAttribute(pchar, "GenQuest.Racing.Go");
		NextDiag.TempNode = "First time";
		break;

	case "Race_begin_5":
		dialog.text = "Es tu elección, capitán.";
		iTemp = 1;
		for (i = 5; i >= 1; i--)
		{
			sTemp = "l" + iTemp;
			link.(sTemp) = "" + FindRussianMoneyString(sti(10000 * i)) + "";
			link.(sTemp).go = "Racing_rate" + i;
			iTemp++;
		}
		break;

	case "Racing_rate5": // 50 000
		if (hrand(9, "&RacRa") > 6)
		{
			dialog.text = "Está bien. Estoy de acuerdo. Tus monedas, por favor. Aquí está mi apuesta.";
			link.l1 = "Déjame coger mi bolso...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 50000;
		}
		else
		{
			dialog.text = "¿Qué oferta tan insensata, capitán? Puedes comprar un bergantín con esa cantidad de dinero y beber ron durante todo un mes. Ofrece una suma razonable.";
			link.l1 = "Esta suma me parece bastante razonable, y no voy a perder mi tiempo contigo por menos. No somos mendigos para apostar por unos pocos pesos. Bien... ya hemos hablado, es suficiente. Si temes apostar, es tu elección... Presumir no es barato.";
			link.l1.go = "Race_exit";
			link.l2 = "¿De veras? Está bien. Déjame pensar...";
			link.l2.go = "Race_begin_5";
		}
		break;

	case "Racing_rate4": // 40 000
		if (hrand(9, "&RacRa") > 4)
		{
			dialog.text = "Está bien. Estoy de acuerdo. Tus monedas, por favor. Aquí está mi apuesta.";
			link.l1 = "Déjame coger mi bolsa...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 40000;
		}
		else
		{
			dialog.text = "¿Qué oferta tan insensata, capitán? Puedes comprar un bergantín por esa cantidad de dinero y beber ron durante todo un mes. Ofrece una suma razonable.";
			link.l1 = "Esta suma me parece lo suficientemente razonable, y no voy a perder mi tiempo contigo por menos. No somos mendigos para apostar unos pocos pesos. Bien... hemos tenido nuestra charla, ya es suficiente. Si temes apostar, es tu elección... Fanfarronear no es barato.";
			link.l1.go = "Race_exit";
			link.l2 = "¿De veras? Está bien. Déjame pensar...";
			link.l2.go = "Race_begin_5";
		}
		break;

	case "Racing_rate3": // 30 000
		if (hrand(9, "&RacRa") > 2)
		{
			dialog.text = "De acuerdo. Acepto. Tus monedas, por favor. Aquí está mi apuesta.";
			link.l1 = "Déjame coger mi bolsa...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 30000;
		}
		else
		{
			dialog.text = "¿Qué oferta tan insensata, capitán? Puedes comprar un balandro por esa cantidad de dinero y beber ron durante todo un mes. Ofrece una suma razonable.";
			link.l1 = "Esta suma me parece lo suficientemente razonable, y no voy a perder mi tiempo contigo por menos. No somos mendigos para apostar por unos pocos pesos. Bien... hemos hablado, ya es suficiente. Si temes apostar, es tu elección... Fanfarronear no es barato.";
			link.l1.go = "Race_exit";
			link.l2 = "¿De verdad? Está bien. Déjame pensar...";
			link.l2.go = "Race_begin_5";
		}
		break;

	case "Racing_rate2": // 20 000
		if (hrand(9, "&RacRa") > 0)
		{
			dialog.text = "Acepto. Tus monedas, por favor. Aquí está mi apuesta.";
			link.l1 = "Déjame coger mi bolsa...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 20000;
		}
		else
		{
			dialog.text = "¿Qué oferta tan insensata, capitán? Puedes comprar un lugre por esa cantidad de dinero y beber ron durante todo un mes. Ofrece una suma razonable.";
			link.l1 = "Esta suma me parece lo suficientemente razonable, y no voy a perder mi tiempo contigo por menos. No somos mendigos para apostar por unos pocos pesos. Bien... hemos hablado, basta ya. Si temes apostar, es tu elección... Fanfarrear no es barato.";
			link.l1.go = "Race_exit";
			link.l2 = "¿En serio? Está bien. Déjame pensar...";
			link.l2.go = "Race_begin_5";
		}
		break;

	case "Racing_rate1": // 10 000
		dialog.text = "Bien. Estoy de acuerdo. Tus monedas, por favor. Aquí está mi apuesta.";
		link.l1 = "Déjame coger mi bolso...";
		link.l1.go = "Racing_rate";
		pchar.GenQuest.Racing.Go.Money = 10000;
		break;

	case "Racing_rate":
		dialog.text = "¿Entonces?";
		if (sti(pchar.money) >= sti(pchar.GenQuest.Racing.Go.Money))
		{
			link.l1 = "¡Aquí!";
			link.l1.go = "Racing_Go";
		}
		else
		{
			link.l1 = "Mm... parece que no tengo tanto.";
			link.l1.go = "Racing_rate_nomoney";
		}
		break;

	case "Racing_rate_nomoney":
		if (sti(pchar.GenQuest.Racing.Go.Money) == 10000 || sti(pchar.Money) < 10000)
		{
			dialog.text = "Bueno, ya sabes que no somos unos mendigos para apostar unos pocos pesos, ¿o simplemente tienes miedo? Está bien, al diablo contigo. Pero no seas tan rápido en juzgar a otras personas, hay muchos marineros experimentados entre los comerciantes... mucho más experimentados que tú.";
			link.l1 = "Está bien, está bien, no me sermonees, filósofo. Adiós...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
		}
		else
		{
			dialog.text = "Entonces, ¿por qué no revisas tu bolsa o haces una apuesta menor?";
			link.l1 = "Bien, intentaré recordar cuánto dinero tengo...";
			link.l1.go = "Race_begin_5";
			link.l2 = "He cambiado de opinión.";
			link.l2.go = "Racing_exit";
		}
		break;

	case "Racing_exit":
		dialog.text = "¿Cambiaste de opinión, eh? ¿Acaso no estás asustado? Está bien, al diablo contigo. Pero no seas tan rápido en juzgar a los demás, hay muchos marineros experimentados entre los mercaderes... mucho más experimentados que tú.";
		link.l1 = "Está bien, está bien, no me sermonees filósofo. Adiós...";
		link.l1.go = "exit_sit";
		DeleteAttribute(pchar, "GenQuest.Racing.Go");
		NextDiag.TempNode = "First time";
		break;

	case "Racing_Go":
		AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Racing.Go.Money));
		dialog.text = "¡Entonces tenemos una apuesta! Llamemos a un tabernero para que lo presencie, si no te importa... y entreguemos nuestras apuestas a él. El ganador regresará y tomará toda la suma. Engañar es imposible ya que los chismes se difunden por el archipiélago muy rápido, así que él sabrá quién es el ganador.";
		link.l1 = "Estoy de acuerdo. Eso parece correcto.";
		link.l1.go = "Racing_Go_1";
		break;

	case "Racing_Go_1":
		dialog.text = "Bueno, supongo que es hora de que subamos a nuestros barcos y zarpemos, el tiempo apremia. No sé tú, pero yo voy a zarpar de inmediato. Ah, y mi barco es un filibote y su nombre es " + pchar.GenQuest.Racing.Go.ShipName + ". Supongo que la reconocerás fácilmente en el puerto una vez que llegues.";
		link.l1 = "No saltes de alegría tan pronto. ¡Nos vemos en la taberna de " + XI_ConvertString("Colony" + pchar.GenQuest.Racing.Go.City + "Gen") + "!";
		link.l1.go = "Racing_Go_2";
		break;

	case "Racing_Go_2":
		DialogExit();
		npchar.lifeday = 0;
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(npchar, pchar.GenQuest.Racing.Go.StartCity + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "exit_sit", -1);
		// работает корректно только через клон :(
		sTemp = npchar.model;
		int iNation = sti(npchar.Nation);
		sld = GetCharacter(NPC_GenerateCharacter("RaceTrader", sTemp, "man", "man", sti(PChar.rank) + 5, iNation, -1, true, "quest"));
		sld.name = npchar.name;
		sld.lastname = npchar.lastname;
		sld.Dialog.Filename = "Quest\QuestTrader_dialog.c";
		pchar.quest.Racing_Timer.win_condition.l1 = "Timer";
		pchar.quest.Racing_Timer.win_condition.l1.date.hour = sti(GetTime() + rand(6));
		pchar.quest.Racing_Timer.win_condition.l1.date.day = GetAddingDataDay(0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty));
		pchar.quest.Racing_Timer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty));
		pchar.quest.Racing_Timer.win_condition.l1.date.year = GetAddingDataYear(0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty));
		pchar.quest.Racing_Timer.function = "TraderRaceInTargetCity";
		pchar.quest.Racing_Finish.win_condition.l1 = "location";
		pchar.quest.Racing_Finish.win_condition.l1.location = pchar.GenQuest.Racing.Go.City + "_town";
		pchar.quest.Racing_Finish.function = "MCRaceInTargetCity";
		SetFunctionTimerCondition("RacingTimeOver", 0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty) + 10, false);
		ReOpenQuestHeader("Racing");
		AddQuestRecord("Racing", "1");
		AddQuestUserData("Racing", "sStartCity", XI_ConvertString("Colony" + pchar.GenQuest.Racing.Go.StartCity + "Gen"));
		AddQuestUserData("Racing", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Racing.Go.City + "Gen"));
		AddQuestUserData("Racing", "sDay", FindRussianDaysString(pchar.GenQuest.Racing.Go.DaysQty));
		AddQuestUserData("Racing", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Racing.Go.Money)));
		break;

	case "Racing_Finished":
		if (CheckAttribute(pchar, "GenQuest.Racing.Go.MCWin"))
		{
			dialog.text = "¡Je! Estoy sorprendido, de hecho... ¡Felicidades, capitán! Realmente eres más rápido que yo. Dicen que siempre hay una fuerza mayor para cualquier fuerza, ¿verdad?";
			link.l1 = "Exactamente, señor. Pero quiero decirle que es sorprendentemente experimentado y hábil para ser un capitán de un barco mercante. No todos los comerciantes son capaces de navegar de esa manera en un filibote en tan poco tiempo.";
			link.l1.go = "Racing_Finished_1";
		}
		else
		{
			dialog.text = "Bueno, ¿no estás sorprendido, capitán? Como dije, conozco perfectamente el mar y navego mi barco lo suficientemente bien. ¿Ves ahora?";
			link.l1 = "¡Argh! ¡Increíble! En un filibote... tan lejos y en tan poco tiempo... ¡Felicidades, capitán!";
			link.l1.go = "Racing_Finished_2";
		}
		// bDisableFastReload = false;
		// LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload1_back", false);
		// LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload2_back", false);
		// LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "gate_back", false);
		break;

	case "Racing_Finished_1":
		dialog.text = "Bueno, eres el ganador. Ahora, tienes que regresar a " + XI_ConvertString("Colony" + pchar.GenQuest.Racing.Go.StartCity) + " y toma tu dinero del tabernero. ¡Seguramente te lo has ganado!";
		link.l1 = "Ya estoy en camino. Fue un placer. ¡Adiós!";
		link.l1.go = "Racing_end";
		pchar.GenQuest.Racing.Count = sti(pchar.GenQuest.Racing.Count) + 1;
		// запустить регату
		if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.GenQuest.Racing.Count) == 3)
		{
			pchar.questTemp.RegataGo = "true";
			pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true); // город, в котором вестовой подойдет
			if (pchar.questTemp.Regata.CureerCity == "PortRoyal")
				pchar.questTemp.Regata.CureerCity = "SentJons";
			pchar.quest.Regata_Cureer.win_condition.l1 = "location";
			pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity + "_town";
			pchar.quest.Regata_Cureer.function = "PrepareToRegata";
			log_testinfo(pchar.questTemp.Regata.CureerCity);
		}
		pchar.GenQuest.Racing.Go.Advantage = "true";
		npchar.lifeday = 0;
		AddCharacterExpToSkill(pchar, "Sailing", 200);	  // навигация
		AddCharacterExpToSkill(pchar, "Fortune", 200);	  // везение
		AddCharacterExpToSkill(pchar, "Leadership", 100); // харизма
		ChangeCharacterComplexReputation(pchar, "authority", 3);
		ChangeOfficersLoyality("good_all", 3);
		break;

	case "Racing_Finished_2":
		dialog.text = "No hay secreto en eso, solo habilidad y experiencia.  Y tengo que ir a " + XI_ConvertString("Colony" + pchar.GenQuest.Racing.Go.StartCity + "Acc") + " para recoger mi premio.";
		link.l1 = "Te lo has ganado. ¡Adiós!";
		link.l1.go = "Racing_end";
		npchar.lifeday = 0;
		DeleteAttribute(pchar, "GenQuest.Racing.Go");
		AddCharacterExpToSkill(pchar, "Sailing", 50);	 // навигация
		AddCharacterExpToSkill(pchar, "Fortune", 50);	 // везение
		AddCharacterExpToSkill(pchar, "Leadership", 20); // харизма
		ChangeCharacterComplexReputation(pchar, "authority", 1);
		AddQuestRecord("Racing", "5");
		CloseQuestHeader("Racing");
		break;

	case "Racing_end":
		DialogExit();
		NextDiag.currentNode = "Racing_end_repeat";
		pchar.quest.Racing_fail.over = "yes";
		Group_DeleteGroup("RacingTrader");
		sld = characterFromId("RaceTraderSkiper");
		sld.lifeday = 0;
		break;

	case "Racing_end_repeat":
		dialog.text = "¿Hay algo más de lo que quieras hablar?";
		link.l1 = "No, es nada.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Racing_end_repeat";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}

float ShipFactorMC()//коэффициент от класса корабля ГГ
{
	float f;
	switch (sti(RealShips[sti(pchar.Ship.Type)].Class))
	{
		case 1: f = 1.0 break;
		case 2: f = 1.2 break;
		case 3: f = 1.5 break;
		case 4: f = 2.2 break;
		case 5: f = 3.0 break;
		case 6: f = 4.5 break;
		case 7: f = 5.5 break;
	}
	return f;
}

int TraderShipType(ref iShipCoef)//корабль торговца
{
	int iRank = sti(pchar.rank);
	int iShip;
	
	if(iRank < 5)
	{
		switch (rand(2))
		{
			case 0:
				iShip = SHIP_BARKENTINE;
				iShipCoef = 2;
			break;
			case 1:
				iShip = SHIP_LUGGER;
				iShipCoef = 3;
			break;
			case 2:
				iShip = SHIP_BARQUE;
				iShipCoef = 4;
			break;
		}
	}
	if(iRank >= 5 && iRank < 11)
	{
		switch (rand(2))
		{
			case 0:
				iShip = SHIP_BARKENTINE;
				iShipCoef = 2;
			break;
			case 1:
				iShip = SHIP_BARQUE;
				iShipCoef = 4;
			break;
			case 2:
				iShip = SHIP_SCHOONER;
				iShipCoef = 5;
			break;
		}
	}
	if(iRank >= 11 && iRank < 18)
	{
		switch (rand(3))
		{
			case 0:
				iShip = SHIP_SCHOONER;
				iShipCoef = 5;
			break;
			case 1:
				iShip = SHIP_FLEUT;
				iShipCoef = 6;
			break;
			case 2:
				iShip = SHIP_CARAVEL;
				iShipCoef = 7;
			break;
			case 3:
				iShip = SHIP_BRIGANTINE;
				iShipCoef = 8;
			break;
		}
	}
	if(iRank >= 18 && iRank < 25)
	{
		switch (rand(4))
		{
			case 0:
				iShip = SHIP_CARAVEL;
				iShipCoef = 7;
			break;
			case 1:
				iShip = SHIP_BRIGANTINE;
				iShipCoef = 8;
			break;
			case 2:
				iShip = SHIP_PINNACE;
				iShipCoef = 9;
			break;
			case 3:
				iShip = SHIP_GALEON_L;
				iShipCoef = 10;
			break;
			case 4:
				iShip = SHIP_EASTINDIAMAN;
				iShipCoef = 11;
			break;
		}
	}
	if(iRank > 25)
	{
		switch (rand(3))
		{
			case 0:
				iShip = SHIP_PINNACE;
				iShipCoef = 9;
			break;
			case 1:
				iShip = SHIP_GALEON_L;
				iShipCoef = 10;
			break;
			case 2:
				iShip = SHIP_EASTINDIAMAN;
				iShipCoef = 11;
			break;
			case 3:
				iShip = SHIP_NAVIO;
				iShipCoef = 12;
			break;
		}
	}
	return iShip;
}

void GetEnemyTraderGoods() // выберем товар
{
	switch (rand(7))
	{
	case 0:
		pchar.GenQuest.Escort.Trader.Goods = GOOD_EBONY;
		pchar.GenQuest.Escort.Trader.add = "ebony";
		break;
	case 1:
		pchar.GenQuest.Escort.Trader.Goods = GOOD_MAHOGANY;
		pchar.GenQuest.Escort.Trader.add = "redwood";
		break;
	case 2:
		pchar.GenQuest.Escort.Trader.Goods = GOOD_TOBACCO;
		pchar.GenQuest.Escort.Trader.add = "tobacco";
		break;
	case 3:
		pchar.GenQuest.Escort.Trader.Goods = GOOD_COFFEE;
		pchar.GenQuest.Escort.Trader.add = "coffee";
		break;
	case 4:
		pchar.GenQuest.Escort.Trader.Goods = GOOD_CINNAMON;
		pchar.GenQuest.Escort.Trader.add = "cinnamon";
		break;
	case 5:
		pchar.GenQuest.Escort.Trader.Goods = GOOD_FOOD;
		pchar.GenQuest.Escort.Trader.add = "provision";
		break;
	case 6:
		pchar.GenQuest.Escort.Trader.Goods = GOOD_WEAPON;
		pchar.GenQuest.Escort.Trader.add = "weapon";
		break;
	case 7:
		pchar.GenQuest.Escort.Trader.Goods = GOOD_CHOCOLATE;
		pchar.GenQuest.Escort.Trader.add = "cacao";
		break;
	}
}

bool CheckFreeSitFront(ref _npchar)
{
	ref rCharacter;
	int n;

	if (!CheckAttribute(_npchar, "Default.ToLocator"))
		return false;

	for (n = 0; n < MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, "location") && rCharacter.location == _npchar.location)
		{
			if (rCharacter.location.locator == _npchar.Default.ToLocator)
				return false;
		}
	}
	return true;
}

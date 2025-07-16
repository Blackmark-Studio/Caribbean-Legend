void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;
	int Shit, i;
	ref refStore;
	ref sld;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "exit":
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = NPC_Meeting;
		DialogExit();
		break;

	case "First time":
		Diag.TempNode = "first time";
		if (CheckAttribute(PChar, "quest.Contraband.active"))
		{
			int iTmp = false;
			int iChIdx;

			// поиск мин.  те старшего класса
			for (i = 0; i < COMPANION_MAX; i++)
			{
				iChIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iChIdx >= 0)
				{
					sld = GetCharacter(iChIdx);
					if (GetCharacterShipClass(sld) < ((MOD_SKILL_ENEMY_RATE / 5.0) + 1.5))
						iTmp = true;
				}
			}

			if (iTmp)
			{
				dialog.text = NPCStringReactionRepeat("¿No te dijeron que no vinieras aquí en un barco tan notable! ¿Por qué no traes un par de hombres de guerra? Piérdete y ven en un barco más pequeño.", "¡Lárgate! O te entregaremos nosotros mismos a la patrulla.", "Ve a tu barco y aléjate.", "Tan cansado de ti...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Está bien, está bien voy a cambiar mi embarcación.", "Cálmate, estoy en camino.", "Maldición, pensé que funcionaría...", "¡Sí, realmente soy terco!", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
				break;
			}

			Dialog.snd = "voice\SMSH\SMSH001";
			dialog.Text = RandPhraseSimple("Oye, ¿qué haces aquí, " + GetSexPhrase("colega", "chica") + "?", RandSwear() + "¿Cuál es tu negocio aquí?!");
			Link.l1 = "Relájate, compañero, ¡vamos a comerciar!";
			Pchar.quest.Contraband.Counter = 0; // не торговали
			if (Pchar.Location == Pchar.location.from_sea)
			{
				Link.l1.go = "Exchange";
			}
			else
			{
				Link.l1.go = "No_Ship";
			}
			// по заданию губернатора, истребление контры, только эта ветка.
			if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))
			{
				Link.l2 = "Estoy aquí por las órdenes del gobernador de " + XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city + "Gen") + "¡Deja caer tus armas y sígueme, estás arrestado!";
				Link.l2.go = "GenQuestKillContraband_1";
			}
		}
		else
		{
			//================ METRO ====================
			// если заплатил, то разговаривают, иначе посылают
			if (CheckAttribute(PChar, "GenQuest.contraTravel.payed") && sti(PChar.GenQuest.contraTravel.payed) == true)
			{
				dialog.Text = RandPhraseSimple("¡Ah, por fin! Te hemos estado esperando. Vamos, es hora de zarpar.", "¡Hagámoslo rápido. Hay patrullas por todas partes. ¡Necesitamos alejarnos de aquí!");
				// по заданию губернатора, истребление контры, только эта ветка.
				if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))
				{
					Link.l1 = "Estoy aquí por las órdenes del gobernador de " + XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city + "Gen") + "¡Baja tus armas y sígueme, estás arrestado!";
					Link.l1.go = "GenQuestKillContraband_1";
					break;
				}
				// если набрал пассажиров, в сад..
				if (GetPassengersQuantity(PChar) > 0)
				{
					dialog.Text = "¿Y quién eres tú? ¡Estábamos hablando de solo un pasajero!";
					Link.l1 = "Vaya..";
					Link.l1.go = "Exit";
					break;
				}
				// если набрал компаньонов или купил корабль себе уже :), в сад..
				if (GetCompanionQuantity(PChar) > 1 || sti(PChar.ship.type) != SHIP_NOTUSED)
				{
					dialog.Text = RandPhraseSimple("¿Quién eres? Hemos estado esperando a un pasajero, no a un capitán.", "¡Piérdete! No vuelvas hasta que te deshagas de tu barco.");
					Link.l1 = "¡Mierda!";
					Link.l1.go = "Exit";
					break;
				}
				// типа помог отбиться, свой парень...
				if (CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight") && sti(PChar.GenQuest.contraTravel.PatrolFight) == true)
				{
					if (chrDisableReloadToLocation) // ещё бой идёт
					{
						dialog.Text = "Mierda, ¡patrulla! No te conocemos y tú no nos conoces.";
						Link.l1 = "Bien...";
						Link.l1.go = "Exit";
						break;
					}
					dialog.Text = RandPhraseSimple("Gracias por tu ayuda. No lo olvidaremos. Naveguemos ahora.", "¡Bien hecho! Buena lucha. Vamos.");
					ChangeContrabandRelation(PChar, 5);
					PChar.GenQuest.contraTravel.PatrolFight = false;
					AddCharacterExpToSkill(Pchar, "Sneak", 50);
				}
				// тут все ок, отправляемся.
				Link.l2 = "Estoy en camino.";
				Link.l2.go = "Exit";
				// а это патруль...
				if (GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < frandSmall(13.0 * (1.0 - pow(0.9, sti(PChar.rank)))) && !CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight"))
				{
					AddDialogExitQuest("Rand_ContrabandInterruption");
					PChar.GenQuest.contraTravel.PatrolFight = true;
				}
				else
				{
					// поместим Грея в локацию.
					refStore = CharacterFromID("Abracham_Gray");
					ChangeCharacterAddressGroup(refStore, "Ship_deck", "goto", "goto2");
					refStore.dialog.Filename = "Smuggler_Ship_dialog.c";
					refStore.dialog.CurrentNode = "Travel_talkStart";
					// поплыл, иначе RemoveTravelSmugglers грохнет всю ветку
					PChar.GenQuest.contraTravel.ship = true;
					PChar.quest.Munity = ""; // признак выхода с палубы

					SetLaunchFrameFormParam("Han pasado " + sti(Pchar.GenQuest.contraTravel.destination.days) + " días." + NewStr() + "Cubierta del barco de los contrabandistas.",
											"Reload_To_Location", 0.1, 5.0);
					bQuestCheckProcessFreeze = true;
					WaitDate("", 0, 0, sti(Pchar.GenQuest.contraTravel.destination.days), rand(20), 0);
					bQuestCheckProcessFreeze = false;
					MakeCloneShipDeck(refStore, true); // подмена палубы
					SetLaunchFrameReloadLocationParam("Ship_deck", "reload", "reload1", "Travel_talkOnDeck");
					AddDialogExitQuest("LaunchFrameForm");
					AddCharacterExpToSkill(Pchar, "Sneak", 50);
				}
				//================ METRO ====================
			}
			else
			{
				// если таможня уже бежит
				if (CheckAttribute(NPChar, "ContrabandInterruption"))
				{
					dialog.Text = RandSwear() + "¡Patrulla! No nos conoces y tú no nos conoces.";
					Link.l1 = "¡Bien!";
					Link.l1.go = "Exit";
				}
				else
				{
					dialog.Text = "¡Piérdete! Te desgarraremos las tripas si estropeas nuestro trato.";
					Link.l1 = RandPhraseSimple("¿Te atreves a amenazarme, chucho!?", "¡Te ahogarás con tus palabras!");
					Link.l1.go = "Exit_fight";
					Link.l2 = "No te preocupes, sé lo que es el negocio. Adiós.";
					Link.l2.go = "Exit";
				}
			}
		}
		break;

	case "No_Ship":
		Dialog.snd = "voice\SMSH\SMSH003";
		dialog.Text = "¿Lo llevas en tu espalda? ¿Dónde está tu barco?";
		Link.l1 = RandPhraseSimple("Primero, me gustaría ver si hay alguna trampa en ello.", "No quería arriesgar el barco. Prefiero verlo todo con mis propios ojos.");
		Link.l1.go = "No_ship_1";
		Link.l2 = "¡El trato se ha acabado!";
		Link.l2.go = "Cancellation";
		break;

	case "No_ship_1":
		Dialog.snd = "voice\SMSH\SMSH004";
		dialog.Text = "Somos hombres honestos y no te engañaremos. Trae tu barco aquí, solo no hagas que las patrullas te sigan.";
		Link.l1 = "Bien. Espérame aquí.";
		Link.l1.go = "Exit";
		break;

	case "Cancellation":
		if (sti(Pchar.quest.Contraband.Counter) == 0)
		{
			dialog.Text = "¿Terminado? ¡Probablemente te estás burlando de mí!";
			Link.l1 = "Estoy hablando en serio.";
			Link.l1.go = "Cancellation_1";
		}
		else
		{
			dialog.Text = "Bien entonces. De todos modos, hemos tenido buenos intercambios hoy.";
			Link.l1 = "¡Correcto!";
			Link.l1.go = "Finish_exit";
		}
		break;

	case "Cancellation_1":
		if (makeint(Pchar.rank) <= 3 || GetSummonSkillFromNameToOld(Pchar, SKILL_FENCING) <= 5 || GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) <= 5)
		{
			if (Rand(1) == 1)
			{
				ChangeContrabandRelation(pchar, -30);
				Dialog.snd = "voice\SMSH\SMSH006";
				dialog.Text = "¡Bastardo! ¡No puedes engañarnos así como así! ¡Lo pagarás con tu propia cabeza!";
				Link.l1 = "¡Lo dudo!";
				Link.l1.go = "Exit_fight";
			}
			else
			{
				ChangeContrabandRelation(pchar, -10);
				Dialog.snd = "voice\SMSH\SMSH007";
				dialog.Text = "¡No te saldrás con la tuya!";
				Link.l1 = "¡Vayan a ladrar a otra parte, perros!";
				Link.l1.go = "Exit_cancel";
			}
		}
		else
		{
			ChangeContrabandRelation(pchar, -10);
			Dialog.snd = "voice\SMSH\SMSH008";
			dialog.Text = "¡Te arrepentirás de eso!";
			Link.l1 = "Hablas demasiado.";
			Link.l1.go = "Exit_cancel";
		}
		break;

	case "GenQuestKillContraband_1":
		// счетчик подстав по "метро"...
		if (CheckAttribute(PChar, "GenQuest.contraTravel.active") && sti(PChar.GenQuest.contraTravel.active) == true)
		{
			Statistic_AddValue(PChar, "contr_TravelKill", 1);
			ChangeContrabandRelation(pchar, -20); // репу контры вниз
		}
		dialog.Text = "¡Responderás por eso!";
		Link.l1 = "Entonces todos vosotros estáis muertos. Tengo una orden clara: eliminaros a todos si resistís.";
		Link.l1.go = "Exit_fight";
		break;

	case "Exit_Cancel":
		DeleteAttribute(Pchar, "quest.Contraband");
		CloseQuestHeader("Gen_Contraband");
		Pchar.quest.Rand_Smuggling.over = "yes";
		RemoveSmugglersFromShore();
		RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = NPC_Meeting;
		DialogExit();
		break;

	case "Exit_fight":
		DeleteAttribute(Pchar, "quest.Contraband.active");
		DeleteAttribute(Pchar, "quest.Contraband.counter");

		AddSimpleRumourCity("¿Has oído las últimas noticias? Los contrabandistas locales fueron acorralados por una patrulla no hace mucho. ¿Y sabes qué? ¡El capitán que tenía un trato con ellos escapó!" +
								"Tenía muchachos apuestos en su tripulación y toda la patrulla fue asesinada. Y nuestros contrabandistas locales desaparecieron. No se encontró nada en la orilla. Ni mercancía, ni alijo, ni contrabandistas. ¡Vean cómo hacen sus negocios aquí!",
							Pchar.quest.contraband.City, 3, 5, "");

		CloseQuestHeader("Gen_Contraband");
		Pchar.quest.Rand_Smuggling.over = "yes";
		LAi_group_FightGroups(LAI_GROUP_PLAYER, pchar.GenQuest.Smugglers_Group, true);
		RemoveSmugglersFromShore();
		RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
		LAi_SetFightMode(Pchar, true);

		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = NPC_Meeting;
		DialogExit();
		break;

	case "Finish_exit":
		// таможня на суше
		if (GetSummonSkillFromName(pchar, "Sneak") < Rand(120))
		{
			AddDialogExitQuest("Rand_ContrabandInterruption");
			for (i = 1; i <= 3; i++)
			{
				characters[GetCharacterIndex("Rand_Smug0" + i)].ContrabandInterruption = true;
			}
		}
		AddCharacterExpToSkill(Pchar, "Sneak", 100);
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = NPC_Meeting;
		DialogExit();
		ChangeContrabandRelation(pchar, 15);
		OfficersReaction("bad");
		ChangeCharacterComplexReputation(pchar, "nobility", -1);

		CloseQuestHeader("Gen_Contraband");

		DeleteAttribute(Pchar, "quest.Contraband.active");
		DeleteAttribute(Pchar, "quest.Contraband.counter");

		Pchar.quest.Rand_Smuggling.over = "yes";
		RemoveSmugglersFromShore();
		RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
		break;

	case "Exchange":
		// сама торговля -->
		if (FindContrabandGoods(Pchar) == -1 && sti(Pchar.quest.Contraband.Counter) == 0)
		{
			dialog.Text = "¿Y qué haces aquí? ¡No tienes nada para vender! Cada bien en tu carga se puede vender en la ciudad!";
			Link.l1 = "Esta vez no hay suerte.";
			Link.l1.go = "NoGoods";
		}
		else
		{
			// установим окружение -->
			if (sti(Pchar.quest.Contraband.Counter) == 0) // не торговали ещё
			{
				if (hrand(11) == 3)
				{
					dialog.Text = "Ya veo.. Sabes, tomaremos tus bienes gratis. Dudo que puedas quejarte de todos modos.";
					Link.l1 = "¡Inténtalo, escoria!";
					Link.l1.go = "Exit_fight";
					break;
				}
				// море и солдаты на суше НЕЗАВИСИМЫ!!!
				if (GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < Rand(12))
				{
					SetCoastalGuardPursuit();
				}
				// при убегании от патруля на карту - корабли трем
				SetTimerCondition("Rand_ContrabandInterruptionAtSeaEnded", 0, 0, 2, false); // если в порту сидим, спим, то 2 день

				Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition.l1 = "MapEnter";
				Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition = "Rand_ContrabandAtSeaEnded";
			}
			// установим окружение <--
			dialog.text = "Vale, veamos lo que tienes.";
			Link.l1 = "Muéstranos lo que tienes.";
			Link.l1.go = "Exchange1";
			if (sti(Pchar.quest.Contraband.Counter) == 0)
			{
				Link.l99 = "He cambiado de opinión.";
				Link.l99.go = "Cancellation";
			}
		}
		break;

	case "Exchange1":
		NPChar.quest.meeting = NPC_Meeting;
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		// belamour legendary edition опасный груз
		pchar.GenQuest.Smugglerzpq = npchar.id;

		LaunchContrabandTrade(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId), sti(pchar.FindContrabandGoods.StoreIdx));
		break;
	// belamour legendary edition опасный груз -->
	case "SmugglerZPQ":
		dialog.text = "¡Buen trato, capitán! Si hay otros productos interesantes, ¡contáctanos!";
		Link.l1 = "Estoy de acuerdo, también estoy satisfecho con nuestro comercio. ¡Ay, si tan solo pudiera comprar todas las mercancías a un precio tan bueno...";
		Link.l1.go = "SmugglerZPQ_1";
		break;

	case "SmugglerZPQ_1":
		dialog.text = "¿Por qué necesitamos comprar bienes ordinarios a tales precios, si pueden ser comprados legalmente en una tienda? Pero no te desanimes: en realidad, cualquier producto puede ser vendido, ¡incluso la pólvora ordinaria! Podrías vender a un precio astronómico, solo necesitas conocer el lugar.";
		Link.l1 = "Vamos. ¿Quién comprará pólvora a un precio exorbitante?";
		Link.l1.go = "SmugglerZPQ_2";
		break;

	case "SmugglerZPQ_2":
		dialog.text = "Bueno, eso es lo que te dije, jeje... Aunque... Sabes, realmente existe tal oportunidad de vender pólvora por una fortuna, pero este trato aún no brilla para nosotros, para ello necesitas tener una reputación bastante buena, y nosotros, como comprendes, no somos nobles.";
		Link.l1 = "Bueno, quizás pueda echarle un vistazo. Puedo ser bueno y amable cuando es necesario. ¿Puedes contarme sobre el trato?";
		Link.l1.go = "SmugglerZPQ_3";
		break;

	case "SmugglerZPQ_3":
		dialog.text = "Todo cuesta dinero en este mundo, capitán, incluso la información. Diría incluso, especialmente la información. Te propongo esto: te daré este consejo por una cantidad simbólica de... digamos cinco mil pesos. ¿Te parece bien?";
		Link.l1 = "¿Pagar cinco mil pesos por información dudosa sobre dónde puedes vender pólvora a un alto precio? No, creo que puedo vivir de alguna manera sin este consejo.";
		Link.l1.go = "SmugglerZPQ_NM";
		if (sti(pchar.money) > 4999)
		{
			Link.l2 = "Creo que puedo hacer más que solo cinco mil en este trato. De acuerdo entonces, acepto.";
			Link.l2.go = "SmugglerZPQ_4";
		}
		break;

	case "SmugglerZPQ_NM":
		npchar.Dialog.CurrentNode = "first time";
		chrDisableReloadToLocation = false;
		DeleteAttribute(pchar, "GenQuest.Smugglerzpq");
		dialog.text = "Depende de ti, capitán. De todas formas, tuvimos un buen trato. Buena suerte... ¡y no te encuentres con una patrulla!";
		Link.l1 = "Tú también. Adiós.";
		Link.l1.go = "exit";
		break;

	case "SmugglerZPQ_4":
		AddMoneyToCharacter(pchar, -5000);
		dialog.text = "¡Excelente, capitán! Eres un cliente asombroso, ya sabes. Así que escucha. Me susurraron al oído que en algunas de las ciudades españolas en Tierra Firme había un problema con la pólvora. Ya sea por las lluvias tropicales, o algo más, en general, en el fuerte que guarda la colonia, hay muy pocas reservas. Y el comandante de este fuerte está buscando a alguien que pueda ayudarlo en esta difícil situación.\nSolo hay dos problemas: primero, este es un asunto delicado, y el comandante no hablará de ello con cualquier pillo, y segundo, estamos hablando de un lote muy grande, no cada barco cabrá tanta pólvora, por lo que podrías necesitar una flota. Además, no todos los capitanes aceptarán convertir su buque en una bomba flotante que puede destruir fácilmente una isla entera si es alcanzada por una bala de cañón perdida.";
		if (CheckAttribute(pchar, "questTemp.zpq"))
		{
			Link.l1 = "Lo siento, pero ya sé sobre este trato. De todos modos, el trato vale más que dinero, por lo que te mereces cinco mil.";
			Link.l1.go = "SmugglerZPQ_5";
		}
		else
		{
			Link.l1 = "Información valiosa, gracias. Si estoy en Tierra Firme, preguntaré a los comandantes locales de los fuertes sobre sus desgracias. Y de alguna manera espero lidiar con estos problemas o aprovecharme de ellos, je-je.";
			Link.l1.go = "SmugglerZPQ_6";
		}
		break;

	case "SmugglerZPQ_5":
		npchar.Dialog.CurrentNode = "first time";
		chrDisableReloadToLocation = false;
		DeleteAttribute(pchar, "GenQuest.Smugglerzpq");
		dialog.text = "Así es como sucede. En cualquier caso, hicimos un buen trato. Buena suerte... ¡y no te encuentres con una patrulla!";
		Link.l1 = "Tú también. Adiós.";
		Link.l1.go = "exit";
		break;

	case "SmugglerZPQ_6":
		npchar.Dialog.CurrentNode = "first time";
		chrDisableReloadToLocation = false;
		DeleteAttribute(pchar, "GenQuest.Smugglerzpq");
		AddQuestRecord("zpq", "0");
		dialog.text = "Así es como sucede. De todos modos, tuvimos un buen trato. Buena suerte... ¡y no te topes con una patrulla!";
		Link.l1 = "Tú también. Adiós.";
		Link.l1.go = "exit";
		break;
		// <-- legendary edition опасный груз
	}
}

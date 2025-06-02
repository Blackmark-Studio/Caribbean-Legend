void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;
	ref rColony;

	int iTest;

	bool ok; // лесник . спецпеременная.

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	iTest = FindColony(NPChar.City);
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}

	switch (Dialog.CurrentNode)
	{
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "exit_setOwner":
		LAi_SetOwnerTypeNoGroup(npchar);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "fight":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetOwnerTypeNoGroup(npchar);
		LAi_group_Attack(NPChar, Pchar);
		if (rand(3) != 1)
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "exit_GoOut":
		makearef(arRld, Locations[reload_cur_location_index].reload);
		Qty = GetAttributesNum(arRld);
		for (i = 0; i < Qty; i++)
		{
			arDis = GetAttributeN(arRld, i);
			if (arDis.go == npchar.location)
			{
				arDis.disable = true; // закрываем вход в дом
				break;
			}
		}
		DoQuestFunctionDelay("HouseEnc_TimerGoUot", 10.0);
		pchar.questTemp.HouseEncTimer = pchar.location;
		pchar.questTemp.HouseEncTimer.Id = npchar.id;
		LAi_SetOwnerTypeNoGroup(npchar);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "exit_close":
		makearef(arRld, Locations[reload_cur_location_index].reload);
		Qty = GetAttributesNum(arRld);
		for (i = 0; i < Qty; i++)
		{
			arDis = GetAttributeN(arRld, i);
			if (arDis.go == npchar.location)
			{
				arDis.disable = true; // закрываем вход в дом
				break;
			}
		}
		LAi_SetOwnerTypeNoGroup(npchar);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	//--------------------------------- мужик ---------------------------------
	case "HouseMan":
		NextDiag.TempNode = "HouseMan";
		if (LAi_grp_playeralarm > 0)
		{
			dialog.text = PCharRepPhrase(LinkRandPhrase("Se ha dado la alarma en el pueblo. Aparentemente, es hora de que yo también tome las armas...", "¿No estarán los guardias de la ciudad corriendo tras de ti, por casualidad?", "¡No encontrarás refugio aquí, pero bien podrías encontrar varias pulgadas de acero frío entre tus costillas!"), LinkRandPhrase("¿Qué necesitas, " + GetSexPhrase("granuja", "granuja") + "? ¡Los guardias de la ciudad ya han encontrado tu rastro, no llegarás lejos, " + GetSexPhrase("pirata asqueroso", "sucia pirata") + "!", "¡Sucio asesino! ¡Guardias!", "No te temo, " + GetSexPhrase("alimaña", "zorra") + ". ¡Pronto serás colgado en nuestro fuerte, no llegarás lejos!"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("Veo que estás cansado de vivir...", "Así parece, ¡no hay vida pacífica para los ciudadanos de " + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"), RandPhraseSimple("¡Vete al infierno!", "Je, esos serán los últimos segundos de tu vida..."));
			link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
			break;
		}
		if (isBadReputation(pchar, 40))
		{
			if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
			{
				dialog.text = "Te he advertido. Y luego puedes decidir por ti mismo, si quieres meterte en problemas.";
				link.l1 = "¡Je!";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "¿Qué necesitas en mi casa, malandrín?! ¡Tienes diez segundos para salir de aquí!";
				link.l1 = LinkRandPhrase("Je, parece que también me conocen aquí!", "Mi fama me ha precedido...", "Mmm, ya veo.");
				link.l1.go = "exit_GoOut";
			}
		}
		else
		{
			if (IsDay())
			{
				dialog.text = NPCStringReactionRepeat("Me alegra darle la bienvenida a mi hogar. ¿Tiene algún asunto conmigo?", "¿Qué puedo hacer por ti?", "¿Hmm... Qué puedo hacer por ti?", "Lo siento, pero si no tienes asuntos conmigo, por favor no me molestes...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("No, solo estoy mirando alrededor, conociendo a gente nueva...", "No, nada en particular...", "Nada...", "Bien, como tú dices.", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("HouseMan_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("Lo siento, pero la noche no es el mejor momento para las visitas, y por lo tanto te pediré que abandones mi casa de inmediato.", "Ya te lo he dicho, es tarde. Por favor, vete.", "No quiero parecer grosero, ¡pero insisto en que abandones mi casa de inmediato!", "¡Maldita sea!, ¿qué está pasando aquí? ¡Guardias! ¡Ladrones!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Está bien, veo ...", "Sí, solo un momento...", "Está bien, solo no te emociones tanto.", "¿Qué ladrones?! ¡Cállate!", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "fight", npchar, Dialog.CurrentNode);
			}
		}
		break;

	case "HouseMan_1":
		dialog.text = "Oh, permíteme presentarme, " + GetFullName(npchar) + ". Estamos muy contentos de tenerle como nuestro huésped. En esta ciudad, se honran las leyes de la hospitalidad.";
		link.l1 = GetFullName(pchar) + ", si le place...";
		link.l1.go = "exit_setOwner";
		break;
	case "Man_FackYou":
		dialog.text = LinkRandPhrase("Tú eres " + GetSexPhrase("¡un ladrón, veo! Guardias, atrapadlo", "¡un ladrón, veo! Guardias, atrapadla") + "¡¡¡", "¡No puedo creerlo! Me volteé por un segundo, ¡y estás hurgando en mis pertenencias! ¡Detén a un ladrón!!!", "¡Guardias! ¡Robo! ¡Detened a ese ladrón!!!");
		link.l1 = "¡Aaaah, diablo!";
		link.l1.go = "fight";
		break;
	// --------------------------------- баба ---------------------------------
	case "HouseWoman":
		NextDiag.TempNode = "HouseWoman";
		if (LAi_grp_playeralarm > 0)
		{
			dialog.text = PCharRepPhrase(LinkRandPhrase("¡Te advierto que mi marido volverá pronto! ¡Sería mejor que salgas de mi casa ahora mismo!", "¡No creo que logres escapar! ¡Y ten en cuenta que mi marido volverá a casa pronto!", "¡Mi marido volverá a casa pronto! ¡Debes irte de inmediato!"), LinkRandPhrase("Una lástima que mi marido no esté en casa... ¡Fuera! ¡Ahora!!!", "¡Asesino sucio, sal de mi casa de inmediato! ¡Guardias!", "" + GetSexPhrase("Qué canalla", "Qué suciedad") + "... Pronto regresará mi marido, ¡y verá de qué color es tu sangre!"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("Oh, tu marido... oooooh...Estoy temblando...", "Heh... Sabes, chica, tu marido es solo un hombre... ¿no querrías verlo muerto a tus pies, verdad?"), RandPhraseSimple("Cierra el pico, bruja, antes de que te desangre...", "Me quedaré aquí todo el tiempo que quiera. Y más te vale mantener la boca cerrada si sabes lo que te conviene..."));
			link.l1.go = "exit_setOwner";
			break;
		}
		if (isBadReputation(pchar, 40))
		{
			if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
			{
				dialog.text = "¡Te he advertido. ¡Sal o lo lamentarás!";
				link.l1 = "Qué estúpida moza...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "¿Qué estás haciendo en mi casa, " + GetSexPhrase("granuja", "granuja") + "? ¡Si no te vas en diez segundos, llamaré a los guardias!";
				link.l1 = "Qué estúpida moza...";
				link.l1.go = "exit_GoOut";
			}
		}
		else
		{
			if (IsDay())
			{
				dialog.text = NPCStringReactionRepeat("Me alegra verte en nuestra casa. Mi nombre es " + GetFullName(npchar) + ". ¿Qué puedo hacer por ti?", "¿Todavía estás aquí?", "Eh, discúlpame, ¿pero no crees que ya es hora de que te vayas?", "Le pediría amablemente que no abuse de nuestra hospitalidad.", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(GetFullName(pchar) + " a su servicio. Vine aquí sin ninguna razón en particular, solo para hacer un conocido.", "Todavía aquí.", "Bueno, yo no sé...", "Bien.", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("HouseWoman_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("¡Oh Dios mío, por qué irrumpes en mi casa a estas horas! Realmente me asustaste... Por favor, ven a visitarnos mañana!", "¡Por favor, deja nuestra casa!" + GetSexPhrase("", "¡Soy una mujer casada!") + "", "¡Te pido que abandones nuestra casa por última vez!", "¡¿Pero qué demonios está pasando aquí?!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("No temas, no te haré daño.", "Está bien, simplemente no te pongas tan agitado.", "Me voy.", "¿Qué pasa?", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "HouseWoman_2", npchar, Dialog.CurrentNode);
			}
		}
		break;

	case "HouseWoman_1":
		dialog.text = "Siempre nos alegra tener invitados. Simplemente no te quedes aquí por mucho tiempo," + GetSexPhrase(", ya que soy una mujer casada...", " ya que tengo mucho que hacer...") + "";
		link.l1 = "Ah, sí, claro...";
		link.l1.go = "exit_setOwner";
		break;
	case "Woman_FackYou":
		dialog.text = "¿Así que así es? Te recibí como mi invitado, ¿y tú estás hurgando en nuestros cofres?! ¡Guardias!";
		link.l1 = "¡Cállate, perra!";
		link.l1.go = "exit_setOwner";
		LAi_group_Attack(NPChar, Pchar);
		if (rand(3) != 1)
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
	case "HouseWoman_2":
		dialog.text = "¡Te pedí que abandonaras nuestra casa de manera amistosa, pero simplemente no escuchaste! ¡Basta! ¡Ayuda! ¡Guardias!";
		link.l1 = "¡Cállate, mujer tonta! ¿Estás loca?!";
		link.l1.go = "exit_setOwner";
		LAi_group_Attack(NPChar, Pchar);
		if (rand(3) != 1)
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
	//--------------------------------- завсклад ---------------------------------
	case "SkladMan":
		NextDiag.TempNode = "SkladMan1";
		if (LAi_grp_playeralarm > 0)
		{
			dialog.text = NPCharRepPhrase(pchar, LinkRandPhrase("Se ha dado la alarma en la ciudad. Aparentemente, es hora de que yo también tome las armas...", "¿No estarán los guardias de la ciudad corriendo tras de ti, por casualidad?", "No encontrarás refugio aquí, ¡pero bien podrías encontrar varias pulgadas de acero frío entre tus costillas!"), LinkRandPhrase("¿Qué necesitas, " + GetSexPhrase("granuja", "granuja") + "? ¡Los guardias de la ciudad ya han encontrado tu rastro, no llegarás lejos, " + GetSexPhrase("pirata asqueroso", "zorra") + "!", "¡Sucio asesino! ¡Guardias!", "No te temo, " + GetSexPhrase("reptil", "zorra") + ". ¡Pronto serás colgado en nuestro fuerte, no llegarás lejos!"));
			link.l1 = NPCharRepPhrase(pchar, RandPhraseSimple("Veo que estás cansado de vivir...", "Así parece, no hay vida pacífica para los ciudadanos de " + XI_ConvertString("Colony" + npchar.city + "Gen") + "¡!"), RandPhraseSimple("¡Vete al infierno!", "Je, esos serán los últimos segundos de tu vida..."));
			link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
			break;
		}
		dialog.text = NPCStringReactionRepeat("¡Bienvenido! Mi nombre es " + GetFullName(npchar) + ". Aquí mando yo, así que ni siquiera pienses en llevarte algo...", "Compórtate decentemente y ten en cuenta que te tengo bajo mi observación.", "Mientras no mires dentro de los cofres, puedes quedarte aquí. De todos modos, me aburro estando solo...", RandPhraseSimple("¡Ay caramba, estoy tan aburrido!", "¡Maldita sea!, ¿qué puedo hacer? ¡Estar aquí es tan aburrido!"), "block", 3, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Está bien, no te preocupes.", "¡Claro!", "Ya veo...", "Sí, eso suena como un problema.", npchar, Dialog.CurrentNode);
		link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
		break;

	case "SkladMan1":
		NextDiag.TempNode = "SkladMan1";
		if (LAi_grp_playeralarm > 0)
		{
			dialog.text = NPCharRepPhrase(pchar, LinkRandPhrase("Se ha dado la alarma en la ciudad. Aparentemente, es hora de que yo también tome las armas...", "¿No estarán por casualidad los guardias de la ciudad persiguiéndote?", "No encontrarás refugio aquí, ¡pero bien podrías encontrar varias pulgadas de acero frío entre tus costillas!"), LinkRandPhrase("¿Qué necesitas," + GetSexPhrase("granuja", "granuja") + "? ¡Los guardias de la ciudad ya han encontrado tu rastro, no llegarás lejos, " + GetSexPhrase("sucio pirata", "ramera") + "!", "" + GetSexPhrase("¡Asqueroso asesino!", "¡Asquerosa asesina!") + " ¡Guardias!", "No te temo, " + GetSexPhrase("reptil", "zorra") + ". ¡Pronto serás colgado en nuestro fuerte, no llegarás muy lejos!"));
			link.l1 = NPCharRepPhrase(pchar, RandPhraseSimple("Veo que estás cansado de vivir...", "Así parece, no hay vida pacífica para los ciudadanos de " + XI_ConvertString("Colony" + npchar.city + "Gen") + "¡!"), RandPhraseSimple("¡Vete al infierno!", "Je, esos serán los últimos segundos de tu vida..."));
			link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
			break;
		}
		dialog.text = NPCStringReactionRepeat("Aquí yo estoy al mando, así que ni siquiera pienses en llevarte algo...", "Compórtate decentemente y ten en cuenta que te tengo bajo mi mirada.", "Mientras no mires en los cofres, puedes quedarte aquí. De todos modos, me aburro estando solo...", RandPhraseSimple("¡Ay de mí, estoy tan aburrido!", "¡Maldita sea!, ¿qué puedo hacer? ¡Estar aquí es tan aburrido!"), "block", 3, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Está bien, no te preocupes.", "¡Claro!", "Ya veo...", "Sí, eso suena como un problema.", npchar, Dialog.CurrentNode);
		link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
		// открывание двери верфи по квесту промышленного шпионажа
		if (CheckAttribute(pchar, "questTemp.different.ShipyardsMap") && pchar.questTemp.different.ShipyardsMap == "toTarget" && npchar.city == pchar.questTemp.different.ShipyardsMap.city && locations[reload_cur_location_index].type == "shipyard")
		{
			link.l2 = "Escucha, compañero, quiero hablar contigo abiertamente.";
			link.l2.go = "ShipyardsMap_1";
			pchar.questTemp.different.ShipyardsMap = "toResult";
		}
		// ugeen --> склад товаров для ГГ
		if (CheckAttribute(NPChar, "Storage"))
		{
			if (!CheckAttribute(NPChar, "Storage.Speak"))
			{
				dialog.text = "Tengo una oferta tentadora para ti. Quizás, podría interesarte.";
				link.l7 = "¿De verdad? Bueno, estoy escuchando.";
				link.l7.go = "storage_rent";
			}
			else
			{
				if (CheckAttribute(NPChar, "Storage.Activate"))
				{
					link.l7 = "Llévame al almacén. Quiero ver en qué condición está.";
					link.l7.go = "storage_0";
					link.l8 = "He decidido desocupar el almacén. Ya no lo necesito.";
					link.l8.go = "storage_04";
				}
				else
				{
					if (!CheckAttribute(NPChar, "Storage.NoActivate"))
					{
						link.l7 = "Has mencionado un almacén. ¿Sigue estando vacío?";
						link.l7.go = "storage_01";
					}
				}
			}
			// <-- ugeen
		}
		break;

	//--------------------------------- Аренда склада ---------------------------------
	case "storage_rent":
		NPChar.Storage.Speak = true;
		dialog.text = "Tenemos un área adecuada como almacén. ¿Le gustaría alquilarla por un precio razonable? Solo piense, tendría su propio almacén para almacenar cargamento valioso...";
		link.l1 = "¿Un almacén, dices? Sí, tentador, en efecto... ¿Es lo suficientemente grande? ¿Y cuánto me cobrarás por el alquiler?";
		link.l1.go = "storage_rent1";
		break;

	case "storage_rent1":
		NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
		dialog.text = "Es bastante espacioso incluso para un almacén portuario, puede contener veamos ... 50000 quintales de carga. Para " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + "  por mes puedo garantizar la custodia segura de tus bienes. " + "Esto incluye protegerlo con mis hombres, protección contra el agua, y luchar contra las ratas. ¿Qué dices tú? Ah, y la confidencialidad también, eso va sin decir.";
		link.l1 = "Lo haré. ¿Puedo echarle un vistazo?";
		link.l1.go = "storage_rent2";
		link.l2 = "Eso es demasiado. Y apuesto a que está inundado e infestado de ratas.";
		link.l2.go = "storage_rent3";
		break;

	case "storage_rent2":
		dialog.text = "Claro, claro. Pero... necesitaré un mes de pago por adelantado.";
		if (sti(pchar.money) >= sti(NPChar.MoneyForStorage))
		{
			link.l1 = "Eres... bastante mercantil, debo decir. Aquí está tu dinero ... Alquilaré este cobertizo.";
			link.l1.go = "storage_11";
		}
		else
		{
			link.l1 = "Eres... bastante mercantil, debo decir. Está bien, conseguiré el dinero.";
			link.l1.go = "exit";
		}
		break;

	case "storage_rent3":
		dialog.text = "Como desees. Si cambias de opinión, házmelo saber. Y ten en cuenta que es poco probable que un almacén tan bonito permanezca vacío por mucho tiempo...";
		link.l1 = "Sin problema. Te haré saber si lo necesito.";
		link.l1.go = "exit";
		break;

	case "storage_0":
		NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage);
		if (sti(NPChar.MoneyForStorage) > 0)
		{
			dialog.text = "Y por el alquiler, aún me debes  " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
			if (sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Está bien, pagaré el alquiler ahora.";
				link.l1.go = "storage_3";
			}
			else
			{
				link.l1 = "Volveré más tarde.";
				link.l1.go = "exit";
			}
		}
		else
		{ // лесник . если забыл с собой корабль то никак.
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.text = "Sigue adelante.";
				link.l1 = "Gracias.";
				link.l1.go = "storage_2";
			}
			else
			{
				dialog.text = RandPhraseSimple("Capitán, ¿dónde está tu barco? ¿Cómo planeas mover la carga?", "No veo tu barco atracado en el puerto. ¿Cómo exactamente vas a cargarla?");
				link.l1 = RandPhraseSimple("¡Oh.. totalmente olvidé eso!", "¡Maldita sea, eso es correcto!");
				link.l1.go = "exit";
				break;
			}
		}
		link.l2 = "No, he cambiado de opinión.";
		link.l2.go = "exit";
		break;

	case "storage_01":
		dialog.text = "No, " + GetSexPhrase("señor", "señora") + ", aún vacante y esperándote. Sabía que al final no rechazarías mi oferta.";
		link.l1 = "Muy bien. Lo alquilaré.";
		link.l1.go = "storage_1";
		link.l2 = "No, simplemente me vino a la mente...";
		link.l2.go = "exit";
		break;

	case "storage_1":
		NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
		dialog.text = "Como deberías recordar, necesito el pago de un mes por adelantado.";
		if (sti(pchar.money) >= sti(NPChar.MoneyForStorage))
		{
			link.l1 = "Por supuesto, recuerdo. Aquí tienes.";
			link.l1.go = "storage_11";
		}
		else
		{
			link.l1 = "Maldita sea. Está bien, iré a buscar el dinero.";
			link.l1.go = "exit";
		}
		break;

	case "storage_11":
		AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage));
		NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
		NPChar.Storage.Activate = true;
		Achievment_Set("ach_67"); // ugeen 2016
		SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LaunchStorage(sti(rColony.StoreNum));
		break;

	case "storage_2":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LaunchStorage(sti(rColony.StoreNum));
		break;

	case "storage_3":
		AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage));
		NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
		NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
		SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LaunchStorage(sti(rColony.StoreNum));
		break;

	case "storage_04":
		dialog.text = "¿Ya te vas? Qué lástima, realmente es un excelente lugar en grandes términos. Te aseguro que no conseguirás un trato como este en ningún lugar del Caribe.";
		link.l1 = "Dije, lo estoy desocupando. ¿O me propones pagar por guardar aire? Puedes buscar a otro titular.";
		link.l1.go = "storage_4";
		link.l2 = "¿En ninguna parte del Caribe, dices? Bueno, lo guardaré por un tiempo, entonces. Pero el costo del alquiler, debo decir, es un poco demasiado alto.";
		link.l2.go = "exit";
		break;

	case "storage_4":
		NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage);
		if (sti(NPChar.MoneyForStorage) > 0)
		{
			dialog.text = "Y por el alquiler, todavía me debes " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
			if (sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Bien.";
				link.l1.go = "storage_5";
			}
		}
		else
		{ // лесник . если нет корабля то и товар не забрать
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.text = "Recoge tus bienes, y cerraré el almacén.";
				link.l1 = "Bien.";
				link.l1.go = "storage_6";
			}
			else
			{
				dialog.text = RandPhraseSimple("Capitán, ¿dónde está tu barco? ¿Cómo planeas mover la carga?", "No veo tu barco atracado en el puerto. ¿Cómo exactamente vas a cargarla?");
				link.l1 = RandPhraseSimple("¡Ah.. totalmente olvidé eso!", "¡Maldita sea, eso es correcto!");
				link.l1.go = "exit";
				break;
			}
		}
		break;

	case "storage_5":
		SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
		AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage));
		NPChar.Storage.NoActivate = true;
		DeleteAttribute(NPChar, "Storage.Activate");
		DialogExit();
		break;

	case "storage_6":
		SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
		DeleteAttribute(NPChar, "Storage.Activate");
		NPChar.Storage.NoActivate = true;
		DialogExit();
		break;

		//--------------------------------- Аренда склада ---------------------------------

	case "ShipyardsMap_1":
		dialog.text = "¡Heh! Bueno, hablemos.";
		link.l1 = "Necesito llegar al astillero por la noche, cuando no hay nadie alrededor.";
		link.l1.go = "ShipyardsMap_2";
		break;
	case "ShipyardsMap_2":
		if (sti(pchar.questTemp.different.ShipyardsMap.skladFight))
		{
			dialog.text = "¡Mírate! ¡Eh, guardias, tenemos un ladrón aquí!!!";
			link.l1 = "¿Qué ladrón? ¡Solo quería hablar!";
			link.l1.go = "fight";
			AddCharacterExpToSkill(pchar, "FencingL", 5);
			AddCharacterExpToSkill(pchar, "FencingS", 5);
			AddCharacterExpToSkill(pchar, "FencingH", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		}
		else
		{
			dialog.text = "¡Vaya! Mírate, " + GetSexPhrase("compañero", "chica") + "¡Venir al almacén del astillero con tal solicitud!";
			link.l1 = "Necesito llegar al propio astillero. No me importa en lo más mínimo tu almacén.";
			link.l1.go = "ShipyardsMap_3";
			AddCharacterExpToSkill(pchar, "Fortune", 10);
		}
		break;
	case "ShipyardsMap_3":
		dialog.text = "¿Pero por qué lo necesitas?";
		link.l1 = "Hay una necesidad. Y estoy dispuesto a pagar por ello...";
		link.l1.go = "ShipyardsMap_4";
		break;
	case "ShipyardsMap_4":
		dialog.text = "Hmm, eso es mejor... ¡Bien! Pásame " + FindRussianMoneyString(sti(pchar.questTemp.different.ShipyardsMap.sklad) * 1000) + ", y dejaré la puerta del astillero abierta durante el día siguiente.";
		link.l1 = "Eso es demasiado caro. Tendré que prescindir de ello, entonces...";
		link.l1.go = "exit";
		if (sti(pchar.money) >= (sti(pchar.questTemp.different.ShipyardsMap.sklad) * 1000))
		{
			link.l2 = "Está bien, estoy de acuerdo. Toma tu dinero y haz como acordamos.";
			link.l2.go = "ShipyardsMap_5";
		}
		break;
	case "ShipyardsMap_5":
		dialog.text = "No te preocupes, se hará.";
		link.l1 = "Espero que sí...";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.ShipyardsMap.sklad) * 1000);
		AddQuestRecord("ShipyardsMap", "5");
		AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		// снимаем close_for_night
		string sName;
		int location_index = FindLocation(npchar.city + "_town");
		makearef(arRld, Locations[location_index].reload);
		Qty = GetAttributesNum(arRld);
		for (int a = 0; a < Qty; a++)
		{
			arDis = GetAttributeN(arRld, a);
			sName = arDis.go;
			if (findsubstr(sName, "_shipyard", 0) != -1)
			{
				DeleteAttribute(arDis, "close_for_night");
				break;
			}
		}
		LocatorReloadEnterDisable(npchar.city + "_shipyard", "reload2", true);
		// ставим таймер на возврат close_for_night
		SetTimerFunction("ShipyardsMap_returnCFN", 0, 0, 2);
		break;
	}
}

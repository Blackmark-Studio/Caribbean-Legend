// китаец Лонгвэй, подручный Роденбурга
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_", 0) != -1)
	{
		i = findsubstr(sAttr, "_", 0);
		NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
		Dialog.CurrentNode = "SetGunBullets2";
	}
	if (findsubstr(sAttr, "SetMusketBullets1_", 0) != -1)
	{
		i = findsubstr(sAttr, "_", 0);
		NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
		Dialog.CurrentNode = "SetMusketBullets2";
	}

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "Chuanzhang. Mi nombre es Longway. Longway pone su barco bajo tu mando. Longway también está bajo tu mando. Orden de mynheer Rodenburg.";
		link.l1 = "Saludos, Longway. Charles de Maure, a su servicio. ¿Tiene alguna pista sobre la operación para eliminar a Jacob van Berg?";
		link.l1.go = "Longway_friend";
		link.l2 = "Es bueno verte, Longway. Mi nombre es Charles de Maure. No hay tiempo que perder - el señor Rodenburg aprecia el trabajo rápido y de alta calidad. ¿Dónde se esconde Jacob van Berg ahora?";
		link.l2.go = "Longway_neutral";
		link.l3 = "¡Bueno, y el mío es Charles de Maure! ¡Esperemos que el nuestro funcione bien juntos! Entonces, señor Longway, dígame, por favor, ¿dónde debería el nuestro buscar a Jacob van Berg?";
		link.l3.go = "Longway_enemy";
		NextDiag.TempNode = "First time";
		pchar.questTemp.HWIC.Holl.JacobCity = SelectJacobCity();
		break;

		//-----------------------------------------------за Голландию-----------------------------------------------
	case "Longway_neutral":
		dialog.text = "Longway está seguro de que trabajaremos bien juntos, chuanzhang. Jacob van Berg actualmente en " + XI_ConvertString("Colony" + pchar.questTemp.HWIC.Holl.JacobCity + "Gen") + ". He concertado una reunión con él en la taberna. Estará allí.";
		link.l1 = "¡Zarpemos!";
		link.l1.go = "Longway_JacobGo";
		pchar.questTemp.HWIC.Holl.LongwayNeutral = "true"; // признак враждебности китайца
		break;

	case "Longway_enemy":
		dialog.text = "Orden del señor Rodenburg para Longway... Jacob van Berg actualmente en " + XI_ConvertString("Colony" + pchar.questTemp.HWIC.Holl.JacobCity + "Gen") + ". He concertado una reunión con él en la taberna. Estará allí.";
		link.l1 = "¡Zarpemos!";
		link.l1.go = "Longway_JacobGo";
		pchar.questTemp.HWIC.Holl.LongwayEnemy = "true"; // признак враждебности китайца
		notification("Longway disapproves", "Longway");
		break;

	case "Longway_friend":
		dialog.text = "Longway hará todo lo que pueda, chuanzhang. Y Jacob van Berg actualmente en " + XI_ConvertString("Colony" + pchar.questTemp.HWIC.Holl.JacobCity + "Dat") + ". He arreglado una reunión con él en la taberna. Estará allí.";
		link.l1 = "¡Zarpemos!";
		link.l1.go = "Longway_JacobGo";
		pchar.questTemp.HWIC.Holl.LongwayFriend = "true"; // признак враждебности китайца
		notification("Longway approves", "Longway");
		break;

	case "Longway_JacobGo":
		// Лонгвэя - в офицеры
		npchar.quest.OfficerPrice = sti(pchar.rank) * 500;
		Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
		npchar.OfficerWantToGo.DontGo = true; // не пытаться уйти
		npchar.HalfImmortal = true;			  // полубессмертен
		npchar.loyality = 18;
		AddDialogExitQuestFunction("LandEnc_OfficerHired");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", -1);
		AddQuestRecord("Holl_Gambit", "1-8");
		AddQuestUserData("Holl_Gambit", "sCity", XI_ConvertString("Colony" + pchar.questTemp.HWIC.Holl.JacobCity + "Dat"));
		AddMapQuestMarkCity(pchar.questTemp.HWIC.Holl.JacobCity, true);
		AddLandQuestMark(characterFromId("" + pchar.questTemp.HWIC.Holl.JacobCity + "_tavernkeeper"), "questmarkmain");
		pchar.questTemp.HWIC.Holl = "JacobOnMain";
		if (bImCasual)
		{
			NewGameTip("Modo exploración: se duplica la duración de las misiones");
			SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 30, false);
		}
		else
			SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 15, false);
		break;

	case "hired":
		dialog.text = "¿Qué puede hacer Longway, chuanzhang?";
		link.l1 = "Nada por ahora.";
		link.l1.go = "exit";
		NextDiag.TempNode = "hired";
		break;

	case "MC_GoAway":
		PlaySound("Voice\Spanish\hambit\Longway-02.wav");
		if (pchar.questTemp.HWIC.Holl == "MirageFail")
		{
			dialog.text = "Eres un idiota, tonto mongol, ¡chuanzhang! Teníamos una tarea fácil: capturar el 'Espejismo' sin perder el 'Meifeng'. Era un blanco fácil sin su chuanzhang, pero fallaste en hacer el trabajo.\nLongway no te servirá, ni te verá más. Longway está seguro de que Mynheer Rodenburg aprobará su decisión.";
			link.l1 = "¡Al diablo contigo y tu amo!";
			link.l1.go = "exit";
			AddQuestRecord("Holl_Gambit", "1-10");
		}
		if (pchar.questTemp.HWIC.Holl == "JacobOnMain" || pchar.questTemp.HWIC.Holl == "JacobInRoom")
		{
			dialog.text = "Eres un idiota, mongol, ¡chuanzhang! Perdimos demasiado tiempo resolviendo tus propios asuntos en lugar de reunirnos con Jacob van Berg. Ya se ha ido de " + XI_ConvertString("Colony" + pchar.questTemp.HWIC.Holl.JacobCity + "Dat") + "\nNo lograste cumplir la tarea. Longway no desea ni servirte ni verte más. Longway está seguro de que el señor Rodenburg aprobará su decisión.";
			link.l1 = "¡Al diablo contigo y tu amo!";
			link.l1.go = "exit";
			AddQuestRecord("Holl_Gambit", "1-9");
		}
		if (pchar.questTemp.HWIC.Holl == "lateVillemstad")
		{
			dialog.text = "Chuanzhang, has desperdiciado demasiado tiempo sin resultados. Este no es tu barco y Longway no es tu cargador. Longway regresa a Willemstad. Longway ni te servirá ni te verá más. Longway está seguro de que el Señor Rodenburg aprobará su decisión.";
			link.l1 = "¡Al infierno contigo y tu amo!";
			link.l1.go = "exit";
		}
		PChar.quest.Munity = "Deads";
		LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
		if (sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG) // если сам на Мейфенг
		{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "Boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);
		}
		else
		{
			for (i = 1; i < COMPANION_MAX; i++)
			{
				int iTemp = GetCompanionIndex(PChar, i);
				if (iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
					{
						pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
						sld = GetCharacter(sti(pchar.questTemp.HWIC.Holl.CompanionIndex));
						RemoveCharacterCompanion(PChar, sld);
						AddPassenger(PChar, sld, false);
					}
				}
			}
		}
		LAi_CharacterDisableDialog(npchar);
		LAi_SetImmortal(npchar, true);
		npchar.lifeday = 0;
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip"); // ПУ откроем
		DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
		pchar.questTemp.HWIC.Holl = "end";
		CloseQuestHeader("Holl_Gambit");
		pchar.questTemp.HWIC.Detector = "holl_fail";
		break;

	case "Longway_hire":
		PlaySound("Voice\Spanish\hambit\Longway-03.wav");
		dialog.text = "Chuanzhang, Longway dejó a Mynheer Rodenburg. Longway nunca volverá a él. Fuiste amable con Longway y eres un chuanzhang valiente. Longway quiere unirse a tu tripulación como tu servidor, Lord Capitán.";
		link.l1 = "¡No como un sirviente, sino como un oficial! ¡Bienvenido a bordo, amigo!";
		link.l1.go = "Longway_hire_1";
		link.l2 = "No gracias, Longway. Eres un hombre libre. No necesito tus servicios.";
		link.l2.go = "Longway_exit";
		break;

	case "Longway_exit":
		DialogExit();
		npchar.lifeday = 0;
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 30.0);
		AddQuestRecord("Holl_Gambit", "1-37");
		break;

	case "Longway_hire_1": // нанимаем китайца
		DialogExit();
		DeleteAttribute(npchar, "LifeDay");
		DeleteAttribute(npchar, "HalfImmortal");
		npchar.quest.OfficerPrice = sti(pchar.rank) * 500;
		npchar.OfficerWantToGo.DontGo = true;
		npchar.loyality = MAX_LOYALITY;
		AddPassenger(pchar, npchar, false);
		SetCharacterRemovable(npchar, true);
		npchar.OfficerImmortal = true;
		npchar.Health.HP = 60.0;
		npchar.Health.maxHP = 60.0;
		SetCharacterPerk(npchar, "ShipEscape");
		npchar.CanTakeMushket = true;
		npchar.Payment = true;
		LAi_SetOfficerType(npchar);
		NextDiag.CurrentNode = "Longway_officer";
		npchar.quest.meeting = true;
		npchar.HoldEquip = true;
		LAi_SetImmortal(npchar, false);
		LAi_SetHP(npchar, 200, 200);
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
		AddQuestRecord("Holl_Gambit", "1-38");

		// Sinistra - квест Лонгвэя "Путеводная звезда"
		PChar.quest.PZ_Start.win_condition.l1 = "location";
		PChar.quest.PZ_Start.win_condition.l1.location = "Curacao";
		PChar.quest.PZ_Start.win_condition = "PZ_Start";
		break;

		//---------------------------------------------против всех-------------------------------------------------
	case "Longway_abordage":
		PlaySound("Voice\Spanish\hambit\Longway-02.wav");
		dialog.text = "¿Por qué te detienes? Mata. Longway está cansado, Longway quiere muerte. Xing... perdóname.";
		link.l1 = "No tan rápido, chino. Te mataré si quiero, pero primero necesito hablar contigo. Tu destino depende de tus acciones futuras. Por ahora, ¡bienvenido a mi bodega de carga!";
		link.l1.go = "Longway_abordage_1";
		break;

	case "Longway_abordage_1":
		AddQuestRecord("Holl_Gambit", "3-45");
		DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
		DialogExit();
		LAi_SetPlayerType(pchar);
		pchar.questTemp.HWIC.Self = "LongwayPrisoner";
		npchar.lifeday = 0;
		SetFunctionTimerCondition("RemoveLongwayOver", 0, 0, 1, false); // таймер до конца суток, ибо нефиг
		break;

	case "Longway_prisoner":
		DelLandQuestMark(npchar);
		dialog.text = "";
		link.l1 = "Ahora podemos hablar sin que el choque del acero resuene en mis oídos. Escucha Longway, necesito información y no tengo duda de que sabes lo que necesito saber. La pregunta es: ¿me lo dirás por las buenas o por las malas?";
		link.l1.go = "Longway_prisoner_1";
		break;

	case "Longway_prisoner_1":
		dialog.text = "";
		link.l1 = "¿Te quedas callado? Está bien. Te ofrezco un trato. Te perdonaré la vida y te dejaré en la próxima costa. A cambio, me dirás dónde y por qué te ha enviado Lucas Rodenburg. ¿Trato?";
		link.l1.go = "Longway_prisoner_2";
		break;

	case "Longway_prisoner_2":
		dialog.text = "";
		link.l1 = "Sé que entiendes inglés, holandés y francés. También eres buen oyente. Ahora es el momento de empezar a hablar. Eventualmente me dirás todo lo que sabes. Sé que ustedes, los chinos, están orgullosos de su arte de la tortura, pero nosotros, hombres de Occidente, hemos hecho nuestros propios avances en esa antigua ciencia. Alonso aquí es un maestro en soltar lenguas. Fue inquisidor para la Santa Inquisición en Santiago antes de que lo contratara en mi barco. Conoce todo tipo de trucos que aprendió de los santos padres que perfeccionaron el arte de hacer confesar a la gente... ¡ni siquiera tienes que ser protestante!";
		link.l1.go = "Longway_prisoner_3";
		break;

	case "Longway_prisoner_3":
		dialog.text = "";
		link.l1 = "Mi ingenio se desperdicia contigo. Me dirás todo, mi amigo de ojos rasgados... Todo... Pero no vivirás mucho después de eso, no, no lo harás. Tu cuerpo sufrirá mucho después de encontrarse con Alonso/. Así que la elección es tuya. O me dices toda la verdad y vives, o me dices toda la verdad y mueres en agonía en el potro. Atormentado por el dolor en el potro. ¿Entiendes? No te preocupes, me aseguraré de tener a un sacerdote presente para bautizarte como cristiano y salvar tu alma pagana de los fuegos eternos del infierno.";
		link.l1.go = "Longway_prisoner_4";
		break;

	case "Longway_prisoner_4":
		dialog.text = "";
		link.l1 = "Veo la duda creciendo en tus ojos negros. ¿Por qué deberías morir por los pecados de tu amo? ¿Vale la pena eso? ¿Realmente vale Rodenburg que tu alma sea arrancada de tu cuerpo sufriente?";
		link.l1.go = "Longway_prisoner_5";
		break;

	case "Longway_prisoner_5":
		dialog.text = "Longway habla. Pero primero, Longway quiere estar seguro de que cumples tu palabra, chuanzhang.";
		link.l1 = "¡Ja! ¡Sabias palabras! Te doy mi palabra, muchacho.";
		link.l1.go = "Longway_prisoner_6";
		break;

	case "Longway_prisoner_6":
		dialog.text = "Lo siento, chuanzhang, tu palabra no es suficiente. ¡Obtén la información y mata a Longway después! Longway quiere garantías.";
		link.l1 = "Haces tratos como un judío. ¿Qué garantías deseas?";
		link.l1.go = "Longway_prisoner_7";
		break;

	case "Longway_prisoner_7":
		dialog.text = "Hay una pequeña isla al sur de Guadalupe. Cabo Inaccesible. Desembarca a Longway allí y dale un arma. Solo entonces Longway te contará todo lo que sabe sobre Lucas Rodenburg.";
		link.l1 = "No estás en posición de negociar conmigo, chino.";
		link.l1.go = "Longway_prisoner_8";
		break;

	case "Longway_prisoner_8":
		dialog.text = "Harías lo mismo si fueras Longway, chuanzhang. No será fácil para tu hombre sacarme palabras incluso con torturas. Longway no es un hombre blanco débil.";
		link.l1 = "Está bien. Trato hecho. Pero te advierto: no intentes engañarme o personalmente te haré pedazos. En mil trozos, y lentamente... justo como hacen tus emperadores. ¡Alonso!";
		link.l1.go = "Longway_prisoner_9";
		// belamour legendary edition -->
		link.l2 = "Hablas con verdad. Pero ten en cuenta que he llegado demasiado lejos para que lo arruines. Si intentas detenerme, acabaré con tu vida como si aplastara un insecto.";
		link.l2.go = "Longway_prisoner_9a";
		break;

	case "Longway_prisoner_9a":
		ChangeCharacterComplexReputation(pchar, "nobility", 1);
		AddCharacterExpToSkill(pchar, "Leadership", 120);
		DialogExit();
		NextDiag.Currentnode = "Longway_prisoner_0";
		npchar.greeting = "longway";
		sld = characterFromId("Sailor_3");
		sld.dialog.currentnode = "Sailor_deck_7";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		pchar.quest.RemoveLongwayOver.over = "yes"; // снять таймер
		pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
		pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour = sti(GetTime());
		pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
		pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
		pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
		pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
		pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;

	case "Longway_prisoner_9":
		ChangeCharacterComplexReputation(pchar, "nobility", -5);
		AddCharacterExpToSkill(pchar, "FencingL", 30);
		AddCharacterExpToSkill(pchar, "FencingS", 30);
		AddCharacterExpToSkill(pchar, "FencingH", 30);
		AddCharacterExpToSkill(pchar, "Pistol", 30);
		// <-- legendary edition
		DialogExit();
		NextDiag.Currentnode = "Longway_prisoner_0";
		npchar.greeting = "longway";
		sld = characterFromId("Sailor_3");
		sld.dialog.currentnode = "Sailor_deck_7";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		pchar.quest.RemoveLongwayOver.over = "yes"; // снять таймер
		pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
		pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour = sti(GetTime());
		pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
		pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
		pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
		pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
		pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;

	case "Longway_prisoner_0":
		dialog.text = "¿Hemos llegado a Guadalupe, chuanzhang?";
		link.l1 = "Enfría tus talones, estaremos allí pronto.";
		link.l1.go = "exit";
		NextDiag.Tempnode = "Longway_prisoner_0";
		break;

	case "Longway_prisoner_10":
		dialog.text = "Has cumplido tu palabra, chuanzhang. Longway también lo hará. ¿Querías saber sobre la misión de Longway?";
		link.l1 = "Sí. Pero permíteme recordarte tu propia promesa hacia mí: me contarás *todo* lo que sabes.";
		link.l1.go = "Longway_prisoner_11";
		break;

	case "Longway_prisoner_11":
		dialog.text = "Longway recuerda. Él responderá todo lo que preguntes sobre Rodenburg, chuanzhang.";
		link.l1 = "Empieza a hablar.";
		link.l1.go = "Longway_prisoner_12";
		break;

	case "Longway_prisoner_12":
		dialog.text = "El 'Meifeng' zarpó del puerto de Willemstad hacia el norte, hacia las costas de San Cristóbal. En cinco días habría un galeón bajo el mando de Peter Stuyvesant. La orden de Longwei era hundir este barco con su capitán a bordo.";
		link.l1 = "¡Dios en el cielo! ¿Rodenburg te ordenó matar a Stuyvesant? ¡Eso es una locura!";
		link.l1.go = "Longway_prisoner_13";
		break;

	case "Longway_prisoner_13":
		dialog.text = "Longway habla la verdad, capitán. Eso fue orden de Mynheer Rodenburg. A Longway no le gustó, pero Longway no cuestiona órdenes.";
		link.l1 = "Qué típico de un chino. ¿Qué juego trama tu maestro?";
		link.l1.go = "Longway_prisoner_14";
		break;

	case "Longway_prisoner_14":
		dialog.text = "Ya no es mi amo, chuanzhang. Longway no va a volver con Mynheer Rodenburg. Rodenburg ha tomado el poder en Curazao. Mathias Beck fue presa fácil, la autoridad de Rodenburg y sus conexiones con el comandante son suficientes para encarcelar al gobernador. \nEl único obstáculo que queda es el director de la Compañía de las Indias Occidentales, Mynheer Stuyvesant. Una vez eliminado Stuyvesant, Rodenburg tendrá todos los cargos de poder en las colonias holandesas.";
		link.l1 = "Dime, Longway, ¿qué ha hecho que un hombre respetado y poderoso como Rodenburg realice acciones tan radicales contra su compañía y república? Y no me digas que es por un golpe de sol o un arrebato de locura.";
		link.l1.go = "Longway_prisoner_15";
		break;

	case "Longway_prisoner_15":
		dialog.text = "Longway quería saberlo de ti mismo, chuanzhang. Fuiste tú quien capturó el barco correo de la Compañía y llevó la carta a Rodenburg, ¿verdad? La razón está en esa carta.";
		link.l1 = "Ya veo... Parece que hay muchas cosas maravillosas en el archivo de John Murdock para asustar a Rodenburg lo suficiente como para lanzar una rebelión contra su propio país.";
		link.l1.go = "Longway_prisoner_16";
		break;

	case "Longway_prisoner_16":
		dialog.text = "¿Quieres saber algo más, chuanzhang?";
		link.l1 = "Sí. ¿Qué más ha hecho Rodenburg?";
		link.l1.go = "Longway_prisoner_17";
		break;

	case "Longway_prisoner_17":
		dialog.text = "El señor Rodenburg ha ordenado matarte. Longway estuvo en Caracas antes de cazar a Stuyvesant y tuvo una reunión con Chuanzhang Jacob y le dio órdenes.";
		link.l1 = "¿Capitán Jacob van Berg?";
		link.l1.go = "Longway_prisoner_18";
		break;

	case "Longway_prisoner_18":
		dialog.text = "Estás bien informado. Sí. Chuanzhang Jacob van Berg te está cazando, capitán. Eventualmente te encontrará. Nadie puede esconderse de van Berg por mucho tiempo.";
		link.l1 = "Si sangra, puedo matarlo. Me encargaré de van Berg y su alabado barco fantasma.";
		link.l1.go = "Longway_prisoner_19";
		break;

	case "Longway_prisoner_19":
		dialog.text = "Sabes mucho, chuanzhang. Longway no tiene nada que añadir. Pregunta si todavía tienes algo que preguntar.";
		link.l1 = "¿Estará Stuyvesant cerca de las costas de San Cristóbal?";
		link.l1.go = "Longway_prisoner_20";
		break;

	case "Longway_prisoner_20":
		dialog.text = "Sí, chuanzhang. Podrás encontrar su galeón cerca de las costas de esta isla en aproximadamente una semana.";
		link.l1 = "¡Estupendo! Vamos a atrapar a este zorro en su propia trampa... No tengo más preguntas. Sé todo lo que quería saber.";
		link.l1.go = "Longway_prisoner_21";
		break;

	case "Longway_prisoner_21":
		dialog.text = "Un último consejo, chuanzhang. Debes llevar 'Meifeng' si quieres acercarte al galeón sin ser atacado.";
		link.l1 = "Entendido. Gracias por tu información.";
		link.l1.go = "Longway_prisoner_22";
		break;

	case "Longway_prisoner_22":
		dialog.text = "Longway se va ahora. Adiós, chuanzhang.";
		link.l1 = "¡Buen viento, mi oriental camarada!";
		link.l1.go = "Longway_prisoner_23";
		break;

	case "Longway_prisoner_23":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "ReturnShoreToNormal", -1);
		npchar.lifeday = 0;
		AddQuestRecord("Holl_Gambit", "3-49");
		pchar.questTemp.HWIC.Self = "MeetingStivesant";
		pchar.quest.Seek_Piter.win_condition.l1 = "location";
		pchar.quest.Seek_Piter.win_condition.l1.location = "Nevis";
		pchar.quest.Seek_Piter.function = "CreatePiterHalleon";
		pchar.quest.RemoveLongwayTimer.over = "yes";					   // снять прерывание
		SetFunctionTimerCondition("QuestShipsTerms_Over", 0, 0, 8, false); // таймер
		AddMapQuestMarkIsland("Nevis", true);
		break;

	//--> ----------------------------------- офицерский блок ------------------------------------------
	case "Longway_officer":
		dialog.text = "Longway escuchando, chuanzhang.";
		if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
		{
			Link.l4 = "Longway, voy a una antigua ciudad india, Tayasal. Seré claro, este será un viaje realmente peligroso y también místico: llegaremos allí a través del ídolo de teletransporte. ¿Te unirás a mí?";
			Link.l4.go = "tieyasal";
		}

		////////////////////////казначей///////////////////////////////////////////////////////////
		// boal отчёт о корабле
		if (CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
		{
			Link.l11 = "Longway, dame un informe completo del barco.";
			Link.l11.go = "QMASTER_1";

			// Warship. Автозакупка товара
			Link.l12 = "Quiero que compres ciertos bienes cada vez que estemos atracados.";
			Link.l12.go = "QMASTER_2";
		}

		if (CheckAttribute(NPChar, "IsCompanionClone")) //////////////////компаньон//////////////////////////////////////////////
		{
			// dialog.text = "He llegado por su disposición, capitán.";
			Link.l2 = "Necesito darte varias órdenes.";
			Link.l2.go = "Companion_Tasks";
			NextDiag.TempNode = "Longway_officer"; // не забыть менять в зависисомости от оффа
			break;
		}
		Link.l1 = "¡Escucha mi orden!";
		Link.l1.go = "stay_follow";
		link.l2 = "Nada. ¡Retírate!";
		link.l2.go = "exit";
		NextDiag.TempNode = "Longway_officer";
		break;

	/////////////////////////// ответы для казначея ///////////////////////////////////
	case "QMASTER_1":
		dialog.Text = "Longway nunca ha sido contramaestre, chuanzhang. Longway puede decirte cómo navegar de Trinidad a La Habana y cuánto tiempo tomará. Pero Longway nunca cuenta carga, ventas y comercio.";
		Link.l1 = "Supongo que tienes razón. Sería una pena desperdiciar a un navegante tan excelente.";
		Link.l1.go = "exit";
		break;

	case "QMASTER_2":
		dialog.text = "Longway no comercia con gwailo, chuanzhang. Longway siempre estuvo al timón, no en la tienda donde el viejo nariz ganchuda regatea hasta el último real de a ocho.";
		link.l1 = "Mm, tienes razón. Probablemente asustarías a los mercaderes.";
		link.l1.go = "exit";
		break;

	// Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
	case "Companion_Tasks":
		dialog.Text = "Estoy escuchando.";
		Link.l1 = "Hablemos sobre el abordaje.";
		Link.l1.go = "Companion_TaskBoarding";
		Link.l2 = "Hablemos de tu barco.";
		Link.l2.go = "Companion_TaskChange";
		if (bBettaTestMode) // Только при бета-тесте
		{
			Link.l3 = "Quiero que dejes mi escuadrón por un tiempo y busques fortuna por tu cuenta.";
			Link.l3.go = "CompanionTravel";
		}
		Link.l8 = "Nada hasta ahora.";
		Link.l8.go = "exit";
		break;

	case "Companion_TaskBoarding":
		dialog.Text = "¿Cuál es tu deseo?";
		Link.l1 = "No abordes barcos enemigos. Cuida de ti mismo y de la tripulación.";
		Link.l1.go = "Companion_TaskBoardingNo";
		Link.l2 = "Quiero que abordes los barcos enemigos agresivamente.";
		Link.l2.go = "Companion_TaskBoardingYes";
		break;

	case "Companion_TaskChange":
		dialog.Text = "¿Cuál es tu deseo?";
		Link.l1 = "No cambies tu barco por otro después de abordarlo. Es demasiado valioso.";
		Link.l1.go = "Companion_TaskChangeNo";
		Link.l2 = "Cuando abordes barcos enemigos, puedes quedártelos si resultan ser decentes.";
		Link.l2.go = "Companion_TaskChangeYes";
		break;

	case "Companion_TaskBoardingNo":
		dialog.Text = "¡Aye aye!";
		Link.l1 = "Descansa.";
		Link.l1.go = "exit";
		NPChar.Tasks.CanBoarding = false;
		break;

	case "Companion_TaskBoardingYes":
		dialog.Text = "Será hecho.";
		Link.l1 = "Descansa.";
		Link.l1.go = "exit";
		NPChar.Tasks.CanBoarding = true;
		break;

	case "Companion_TaskChangeNo":
		dialog.Text = "Sí, señor.";
		Link.l1 = "Será hecho.";
		Link.l1.go = "exit";
		NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

	case "Companion_TaskChangeYes":
		dialog.Text = "Será hecho.";
		Link.l1 = "Descansa.";
		Link.l1.go = "exit";
		NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//	<========////////////////////////////////////////
	case "stay_follow":
		dialog.Text = "¿Órdenes, chuanzhang?";
		Link.l1 = "¡Manteneos firmes!";
		Link.l1.go = "Boal_Stay";
		Link.l2 = "¡Sígueme y mantén el ritmo!";
		Link.l2.go = "Boal_Follow";
		if (CheckAttribute(NPChar, "equip.gun"))
		{
			if (CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
			{
				Link.l3 = "Cambia el tipo de munición para tus armas de fuego.";
				Link.l3.go = "SetGunBullets";
			}
		}
		if (CheckAttribute(NPChar, "equip.musket"))
		{
			if (CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
			{
				Link.l4 = "Cambia el tipo de munición para tu mosquete.";
				Link.l4.go = "SetMusketBullets";
			}
			Link.l5 = "Cambia tu arma prioritaria para el combate.";
			Link.l5.go = "SetPriorityMode";
			Link.l6 = "Quiero que dispares a los enemigos desde una distancia específica, Lonway.";
			Link.l6.go = "TargetDistance";
		}
		break;

	case "SetGunBullets":
		Dialog.Text = "Eligiendo el tipo de munición:";
		sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
		rItm = ItemsFromID(sGun);
		makearef(rType, rItm.type);
		for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
		{
			sAttr = GetAttributeName(GetAttributeN(rType, i));
			sBullet = rItm.type.(sAttr).bullet;
			rItem = ItemsFromID(sBullet);
			attrL = "l" + i;
			Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
			;
			Link.(attrL).go = "SetGunBullets1_" + i;
		}
		break;

	case "SetGunBullets2":
		i = sti(NPChar.SetGunBullets) + 1;
		sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
		rItm = ItemsFromID(sGun);
		sAttr = "t" + i;
		sBullet = rItm.type.(sAttr).bullet;
		LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
		LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
		NextDiag.CurrentNode = NextDiag.TempNode;
		rItem = ItemsFromID(sBullet);
		notification(GetFullName(NPChar) + " " + XI_ConvertString("AmmoSelectNotif") + GetConvertStr(rItem.name, "ItemsDescribe.txt") + "", "AmmoSelect");
		DeleteAttribute(NPChar, "SetGunBullets");
		DialogExit();
		break;

	case "SetMusketBullets":
		Dialog.Text = "Selecciona el tipo de munición:";
		sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
		rItm = ItemsFromID(sGun);
		makearef(rType, rItm.type);
		for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
		{
			sAttr = GetAttributeName(GetAttributeN(rType, i));
			sBullet = rItm.type.(sAttr).bullet;
			rItem = ItemsFromID(sBullet);
			attrL = "l" + i;
			Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
			Link.(attrL).go = "SetGunBullets1_" + i;
		}
		break;

	case "SetMusketBullets2":
		i = sti(NPChar.SetMusketBullets) + 1;
		sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
		rItm = ItemsFromID(sGun);
		sAttr = "t" + i;
		sBullet = rItm.type.(sAttr).bullet;
		LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
		LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
		NextDiag.CurrentNode = NextDiag.TempNode;
		rItem = ItemsFromID(sBullet);
		notification(GetFullName(NPChar) + " " + XI_ConvertString("AmmoSelectNotif") + GetConvertStr(rItem.name, "ItemsDescribe.txt") + "", "AmmoSelect");
		DeleteAttribute(NPChar, "SetMusketBullets");
		DialogExit();
		break;

	case "SetPriorityMode":
		Dialog.Text = "Al comienzo de la pelea usarás:";
		Link.l1 = "Hoja";
		Link.l1.go = "BladePriorityMode";
		Link.l2 = "Mosquete";
		Link.l2.go = "MusketPriorityMode";
		break;

	case "BladePriorityMode":
		SetPriorityMode(NPChar, 1);
		DialogExit();
		break;

	case "MusketPriorityMode":
		SetPriorityMode(NPChar, 2);
		DialogExit();
		break;

	case "Boal_Stay":
		Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
		AddDialogExitQuestFunction("LandEnc_OfficerStay");
		dialog.Text = "¡Hay un cambio de disposición!";
		Link.l1 = "Despedido.";
		Link.l1.go = "Exit";
		Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
		break;

	case "Boal_Follow":
		SetCharacterTask_FollowCharacter(Npchar, PChar);
		dialog.Text = "¡Hay un cambio de disposición!";
		Link.l1 = "Despedido.";
		Link.l1.go = "Exit";
		break;

	//--> задать дистанцию стрельбы
	case "TargetDistance":
		dialog.text = "¿Y qué distancia sería esa? Tenga en cuenta, mi Lord Capitán, que no puede acertar a nada con un mosquete más allá de veinte metros.";
		link.l1 = "";
		Link.l1.edit = 3;
		link.l1.go = "TargetDistance_1";
		break;

	case "TargetDistance_1":
		iTemp = sti(dialogEditStrings[3]);
		if (iTemp < 0)
		{
			dialog.text = "¿Qué queréis decir, Lord Capitán?";
			link.l1 = "Lo siento, a veces olvido que no eres bueno con las bromas.";
			link.l1.go = "exit";
			break;
		}
		if (iTemp == 0)
		{
			dialog.text = "Mantendré mi posición pero dispararé a cualquier enemigo que se acerque demasiado. ¿Es eso lo que quieres?";
			link.l1 = "Sí, exactamente, Lonway.";
			link.l1.go = "exit";
			npchar.MusketerDistance = 0;
			break;
		}
		if (iTemp > 20)
		{
			dialog.text = "Eso está demasiado lejos, mi Capitán. Podrías dar en la multitud, pero apuntar a un solo objetivo - no hay posibilidad.";
			link.l1 = "Valdría la pena intentarlo, pero está bien.";
			link.l1.go = "exit";
			npchar.MusketerDistance = 20.0;
			break;
		}
		dialog.text = "Entiendo, Señor Capitán.";
		link.l1 = "Excelente.";
		link.l1.go = "exit";
		npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
		//<-- ----------------------------------- офицерский блок ----------------------------------------

		// на Тайясаль
	case "tieyasal":
		dialog.text = "Longway te ha estado siguiendo durante mucho tiempo. Longway te seguirá como siempre. Longway no dejará a su chuanzhang.";
		link.l1 = "¡Gracias, Longway! Me alegra haber acertado contigo.";
		link.l1.go = "tieyasal_1";
		break;

	case "tieyasal_1":
		dialog.text = "¿Cuándo empezaremos?";
		link.l1 = "Un poco más tarde. Tenemos que prepararnos para ello.";
		link.l1.go = "tieyasal_2";
		break;

	case "tieyasal_2":
		DialogExit();
		AddQuestRecord("Tieyasal", "24");
		npchar.quest.Tieyasal = "teleport";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}

string SelectJacobCity()
{
	string sTemp;
	switch (hrand(4))
	{
	case 0:
		sTemp = "Cumana" break;
	case 1:
		sTemp = "Caracas" break;
	case 2:
		sTemp = "Maracaibo" break;
	case 3:
		sTemp = "Cartahena" break;
	case 4:
		sTemp = "Portobello" break;
	}
	return sTemp;
}

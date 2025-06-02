void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp, iQty;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "Un error. Asegúrate de decírselo a los desarrolladores.";
		link.l1 = "Está bien.";
		link.l1.go = "exit";
		break;

	// разговор на палубе
	case "MarchCap":
		pchar.quest.MarchCapOver.over = "yes"; // снять прерывание
		dialog.text = "Aquí estás, capitán. Vamos a discutir los detalles de mi oferta. Entenderás por qué no quería hablar de esto en público.";
		link.l1 = "Continúe, señor. Estoy escuchando.";
		link.l1.go = "MarchCap_1";
		break;

	case "MarchCap_1":
		pchar.GenQuest.MarchCap.Goods = SelectMarchCapGoods1(); // целевой товар
		switch (rand(2))
		{
		case 0: // конвой у острова, установка параметров
			pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
			while (pchar.GenQuest.MarchCap.Island == pchar.GenQuest.MarchCap.Startisland)
			{
				pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
			}
			pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
			while (pchar.GenQuest.MarchCap.Island.Shore == "")
			{
				pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
				pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
				if (!isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island) || !isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island.Shore))
					pchar.GenQuest.MarchCap.Island.Shore = "";
			}
			pchar.GenQuest.MarchCap.DaysQty = GetMaxDaysFromIsland2Island(pchar.GenQuest.MarchCap.Startisland, pchar.GenQuest.MarchCap.Island) + 3;
			dialog.text = "Logré averiguar que en " + FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)) + " un pequeño convoy mercante bajo la bandera de " + NationNameGenitive(sti(pchar.GenQuest.MarchCap.Nation)) + ", dos barcos mercantes y un barco de guardia, navegarán cerca de " + XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore + "Gen") + ", esto no está lejos de " + XI_ConvertString(pchar.GenQuest.MarchCap.Island + "Gen") + "  Los comerciantes tienen mucho de  " + GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)) + " en sus bodegas. Sería una tontería no usar esta información, capitán\nTú y yo podemos encargarnos de los guardias fácilmente y llevarnos la carga para nosotros. Entonces, ¿estás dentro?";
			link.l1 = "Suena tentador. ¡Diría que sí!";
			link.l1.go = "MarchCap_1_1";
			link.l2 = "Algunos" + GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)) + " no es suficiente para que yo arruine mis relaciones con " + NationNameAblative(sti(pchar.GenQuest.MarchCap.Nation)) + " No, ¡no voy a hacer esto! ¡Adiós, señor, y ni siquiera intente detenerme!";
			link.l2.go = "MarchCap_exit";
			break;

		case 1: // энкаунтер на глобалке, установка параметров
			pchar.GenQuest.MarchCap.Startcity = SelectAnyColony(pchar.GenQuest.MarchCap.basecity);
			pchar.GenQuest.MarchCap.Finishcity = SelectAnyColony2(pchar.GenQuest.MarchCap.basecity, pchar.GenQuest.MarchCap.Startcity);
			pchar.GenQuest.MarchCap.DaysQty = 5 + hrand(5);
			dialog.text = "Logré averiguar que en " + FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)) + " un pequeño convoy mercante bajo la bandera de " + NationNameGenitive(sti(pchar.GenQuest.MarchCap.Nation)) + ", dos barcos mercantes y un barco de escolta, zarparán desde " + XI_ConvertString("Colony" + pchar.GenQuest.MarchCap.Startcity + "Gen") + " a " + XI_ConvertString("Colony" + pchar.GenQuest.MarchCap.Finishcity + "Acc") + ". Los comerciantes tienen mucho de " + GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)) + " en sus bodegas. Sería tonto no usar esta información, capitán.\nTú y yo podemos ocuparnos fácilmente de los guardias y tomar la carga para nosotros. La parte más difícil es encontrarlos en el mar abierto entre estas dos colonias. Entonces, ¿estás dentro?";
			link.l1 = "Suena tentador. ¡Diría que sí!";
			link.l1.go = "MarchCap_2_1";
			link.l2 = "Algunos " + GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)) + " no es suficiente para que arruine mis relaciones con " + NationNameAblative(sti(pchar.GenQuest.MarchCap.Nation)) + ". ¡No, no voy a hacer esto! ¡Adiós, señor, y ni siquiera intente detenerme!";
			link.l2.go = "MarchCap_exit";
			break;

		case 2: // одиночный пиратский кулсейлор у бухты, установка параметров
			pchar.GenQuest.MarchCap.Goods = GOOD_GOLD + hrand(makeint(GOOD_SILVER - GOOD_GOLD));
			pchar.GenQuest.MarchCap.GoodsQty = sti(pchar.rank) * 50 + 170 + rand(30);
			if (sti(pchar.GenQuest.MarchCap.GoodsQty) > 1600)
				pchar.GenQuest.MarchCap.GoodsQty = 1500 + rand(100);
			pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
			while (pchar.GenQuest.MarchCap.Island == pchar.GenQuest.MarchCap.Startisland)
			{
				pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
			}
			pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
			while (pchar.GenQuest.MarchCap.Island.Shore == "")
			{
				pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
				pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
				if (!isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island) || !isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island.Shore))
					pchar.GenQuest.MarchCap.Island.Shore = "";
			}
			pchar.GenQuest.MarchCap.DaysQty = GetMaxDaysFromIsland2Island(pchar.GenQuest.MarchCap.Startisland, pchar.GenQuest.MarchCap.Island) + 1;
			pchar.GenQuest.MarchCap.PirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1); // пират
			pchar.GenQuest.MarchCap.ShipType = SelectPirateShipType();
			pchar.GenQuest.MarchCap.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.MarchCap.ShipType));
			dialog.text = "Me informaron sobre un pirata llamado " + GetName(NAMETYPE_ORIG, pchar.GenQuest.MarchCap.PirateName, NAME_NOM) + "Este bandido ha pellizcado recientemente " + RandPhraseSimple(RandPhraseSimple("Español", "Francés"), RandPhraseSimple("Español", "Holandés")) + " y cargó su bodega con " + GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)) + ". Pero, qué lástima, su barco " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.ShipType), "Name") + "Acc")) + " estaba gravemente dañada, así que tuvo que tomarse tiempo para repararla.\nActualmente está en " + XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore + "Gen") + " de " + XI_ConvertString(pchar.GenQuest.MarchCap.Island + "Gen") + ". Creo que tomará alrededor de " + FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)) + " para que él repare los mástiles y los agujeros en el casco. Podemos llegar a tiempo si nos damos prisa y todos " + GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)) + " será nuestro\nNo podré lidiar con este pirata por mi cuenta, es un muy buen marinero y luchador, pero dos de nosotros podemos enfrentarlo con éxito a pesar de su experiencia. Entonces, ¿estás dentro o no?";
			link.l1 = "Suena tentador. ¡Diría que sí!";
			link.l1.go = "MarchCap_3_1";
			link.l2 = "Mm. Parece que este premio es inalcanzable no solo para ti, sino para ambos. No, no voy a hacer esto, adiós, señor, ¡y ni siquiera intentes detenerme!";
			link.l2.go = "MarchCap_exit";
			break;
		}
		break;

	case "MarchCap_1_1":
		dialog.text = "¡Sabía que podía contar contigo! No perdamos un solo minuto. Ve a tu barco y toma el mando, yo te seguiré. ¡Es hora de zarpar!";
		link.l1 = "¡Ordene levantar anclas, capitán!";
		link.l1.go = "MarchCap_1_2";
		break;

	case "MarchCap_1_2":
		DialogExit();
		NextDiag.CurrentNode = "MarchCap_repeat";
		Group_DelCharacter("MarchGroup", "MarchCap");
		SetCompanionIndex(pchar, -1, sti(npchar.index));
		npchar.loyality = MAX_LOYALITY;
		SetCharacterRemovable(npchar, false);
		Character_SetAbordageEnable(npchar, false);
		npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
		pchar.quest.MarchCap1_1.win_condition.l1 = "Timer";
		pchar.quest.MarchCap1_1.win_condition.l1.date.hour = sti(GetTime() + rand(10));
		pchar.quest.MarchCap1_1.win_condition.l1.date.day = GetAddingDataDay(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
		pchar.quest.MarchCap1_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
		pchar.quest.MarchCap1_1.win_condition.l1.date.year = GetAddingDataYear(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
		pchar.quest.MarchCap1_1.win_condition.l2 = "location";
		pchar.quest.MarchCap1_1.win_condition.l2.location = pchar.GenQuest.MarchCap.Island;
		pchar.quest.MarchCap1_1.function = "MarchCap1_CreateConvoy";
		SetFunctionTimerCondition("MarchCap_Attack_Over", 0, 0, sti(pchar.GenQuest.MarchCap.DaysQty) + 2, false); // таймер на нахождение
		pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
		pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
		pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
		ReOpenQuestHeader("MarchCap");
		AddQuestRecord("MarchCap", "1");
		AddQuestUserData("MarchCap", "sShore", XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore + "Gen"));
		AddQuestUserData("MarchCap", "sIsland", XI_ConvertString(pchar.GenQuest.MarchCap.Island + "Gen"));
		AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
		AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
		AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
		break;

	case "MarchCap_TimeOver":
		dialog.text = "¿Y por qué me he involucrado contigo, capitán? ¡Hemos perdido un premio tan valioso por tu culpa! Mejor navegaré solo la próxima vez...";
		link.l1 = "Tu culpa, no la mía. Adiós.";
		link.l1.go = "MarchCap_Talk_exit";
		pchar.GenQuest.MarchCap = "late";
		break;

	case "MarchCap_Talk_exit":
		pchar.quest.MarchCap1_fail2.over = "yes"; // снять прерывание
		pchar.quest.MarchCap1_fail1.over = "yes"; // снять прерывание
		pchar.quest.MarchCap1_fail.over = "yes";  // снять прерывание
		DialogExit();
		npchar.lifeday = 0;
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
		DeleteAttribute(npchar, "AlwaysFriend");
		npchar.DontDeskTalk = true;
		if (CheckAttribute(pchar, "GenQuest.MarchCap.Deck"))
		{
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
		}
		else
		{
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			chrDisableReloadToLocation = false;
		}
		RemoveCharacterCompanion(pchar, npchar);
		npchar.location = pchar.location;
		if (pchar.GenQuest.MarchCap == "late")
			AddQuestRecord("MarchCap", "2");
		if (pchar.GenQuest.MarchCap == "bad")
			AddQuestRecord("MarchCap", "5");
		if (pchar.GenQuest.MarchCap == "poor" || pchar.GenQuest.MarchCap == "good" || pchar.GenQuest.MarchCap == "exellent")
		{
			iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods)) - sti(pchar.GenQuest.MarchCap.StartGoodsQty));
			iTemp = iQty - sti(pchar.GenQuest.MarchCap.CapPart);
			RemoveCharacterGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods), iQty);
			AddCharacterGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods), iTemp);
			if (pchar.GenQuest.MarchCap == "poor")
				AddQuestRecord("MarchCap", "6");
			if (pchar.GenQuest.MarchCap == "good")
				AddQuestRecord("MarchCap", "7");
			if (pchar.GenQuest.MarchCap == "exellent")
				AddQuestRecord("MarchCap", "8");
		}
		AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
		CloseQuestHeader("MarchCap");
		DeleteAttribute(pchar, "GenQuest.MarchCap");
		break;

	case "MarchCap_AfterBattle":
		iTemp = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods)) - sti(pchar.GenQuest.MarchCap.StartGoodsQty)) * sti(Goods[sti(pchar.GenQuest.MarchCap.Goods)].Weight);
		iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods)) - sti(pchar.GenQuest.MarchCap.StartGoodsQty));
		pchar.GenQuest.MarchCap.CapPart = iQty / sti(pchar.GenQuest.MarchCap.Parts);
		if (iTemp < 50)
		{
			dialog.text = "Eres un perdedor, ¡capitán! ¡No conseguimos ni un trozo! ¡Y todo esto es por tu culpa! ¡Tú eres la razón de nuestro fracaso, maldito seas!";
			link.l1 = "¿Ah, sí? ¡Mírate a ti mismo! ¡No me has ayudado en la batalla! Solo he perdido mi tiempo contigo... ¡Fuera de mi barco!";
			link.l1.go = "MarchCap_Talk_exit";
			pchar.GenQuest.MarchCap = "bad";
			break;
		}
		if (iTemp > 50 && iTemp < 500)
		{
			dialog.text = "Bueno, esta incursión no fue tan exitosa como esperaba, nuestro botín es realmente modesto... Como sea, capitán, compartamos estos restos y despidámonos.";
			link.l1 = "Si hubieras estado ayudándome en vez de contar pájaros en el cielo, la incursión habría tenido éxito... Toma tu parte, " + FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart)) + " ¡y piérdete!";
			link.l1.go = "MarchCap_Talk_exit";
			pchar.GenQuest.MarchCap = "poor";
			break;
		}
		if (iTemp > 500 && iTemp < 1500)
		{
			dialog.text = "Bien hecho, capitán. Como dije, fue bastante fácil vaciar las bodegas de esos mercaderes, ja-ja... El premio es " + FindRussianQtyString(iQty) + " piezas. Mi parte es " + FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart)) + ".";
			link.l1 = "Es correcto, " + npchar.name + "  No tengo objeciones. Las chalupas están siendo cargadas en este momento. Quizás, hagamos otro ataque juntos en el futuro. Pareces un compañero adecuado para mí.";
			link.l1.go = "MarchCap_Talk_exit";
			pchar.GenQuest.MarchCap = "good";
			break;
		}
		dialog.text = "¡Excelente, capitán! Como dije, fue relativamente fácil vaciar las bodegas de esos mercaderes, ja-ja... El botín es enorme, mucho más de lo que esperaba. Es " + FindRussianQtyString(iQty) + " piezas. Mi parte es " + FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart)) + ".";
		link.l1 = "Es correcto, " + npchar.name + ". No tengo objeciones. Las chalupas se están cargando ahora mismo. ¿Quizás, hagamos otra incursión juntos en el futuro? Pareces un compañero adecuado para mí.";
		link.l1.go = "MarchCap_Deck_continue";
		pchar.GenQuest.MarchCap = "exellent";
		break;

	// если будет время - здесь создаем еще одного клона с уникальным ИД для продолжения квеста
	case "MarchCap_Deck_continue":
		dialog.text = "Hay una posibilidad, capitán. Te encontraré si obtengo otra pista rentable que no pueda manejar por mi cuenta. También me pareces un compañero de batalla confiable.";
		link.l1 = "¡Genial! Adiós, capitán. ¡Buena suerte!";
		link.l1.go = "MarchCap_Talk_exit";
		break;

	case "MarchCap_2_1":
		dialog.text = "¡Sabía que podía contar contigo! No perdamos ni un minuto. Ve a tu nave y toma el mando, yo te seguiré. ¡Es hora de zarpar!";
		link.l1 = "Orden de levar anclas, capitán.";
		link.l1.go = "MarchCap_2_2";
		break;

	case "MarchCap_2_2":
		DialogExit();
		NextDiag.CurrentNode = "MarchCap_repeat";
		Group_DelCharacter("MarchGroup", "MarchCap");
		SetCompanionIndex(pchar, -1, sti(npchar.index));
		npchar.loyality = MAX_LOYALITY;
		SetCharacterRemovable(npchar, false);
		Character_SetAbordageEnable(npchar, false);
		npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
		pchar.quest.MarchCap1_1.win_condition.l1 = "Timer";
		pchar.quest.MarchCap1_1.win_condition.l1.date.hour = sti(GetTime() + rand(10));
		pchar.quest.MarchCap1_1.win_condition.l1.date.day = GetAddingDataDay(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
		pchar.quest.MarchCap1_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
		pchar.quest.MarchCap1_1.win_condition.l1.date.year = GetAddingDataYear(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
		pchar.quest.MarchCap1_1.function = "MarchCap2_CreateConvoy";
		pchar.GenQuest.MarchCap.WdmEnc = "true";
		pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
		pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
		pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
		ReOpenQuestHeader("MarchCap");
		AddQuestRecord("MarchCap", "10");
		AddQuestUserData("MarchCap", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.MarchCap.Startcity + "Gen"));
		AddQuestUserData("MarchCap", "sCity2", XI_ConvertString("Colony" + pchar.GenQuest.MarchCap.Finishcity + "Acc"));
		AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
		AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
		AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
		break;

	case "MarchCap_3_1":
		dialog.text = "¡Sabía que podía contar contigo! No perdamos ni un minuto. Ve a tu barco y guíame. ¡Es hora de zarpar!";
		link.l1 = "Orden de levar anclas, capitán.";
		link.l1.go = "MarchCap_3_2";
		break;

	case "MarchCap_3_2":
		DialogExit();
		NextDiag.CurrentNode = "MarchCap_repeat";
		Group_DelCharacter("MarchGroup", "MarchCap");
		SetCompanionIndex(pchar, -1, sti(npchar.index));
		npchar.loyality = MAX_LOYALITY;
		SetCharacterRemovable(npchar, false);
		Character_SetAbordageEnable(npchar, false);
		npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
		pchar.quest.MarchCap1_1.win_condition.l1 = "location";
		pchar.quest.MarchCap1_1.win_condition.l1.location = pchar.GenQuest.MarchCap.Island;
		pchar.quest.MarchCap1_1.function = "MarchCap3_CreatePirate";
		SetFunctionTimerCondition("MarchCap_Attack_Over", 0, 0, sti(pchar.GenQuest.MarchCap.DaysQty), false); // таймер
		pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
		pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
		pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
		pchar.GenQuest.MarchCap.Pirate = "true";
		ReOpenQuestHeader("MarchCap");
		AddQuestRecord("MarchCap", "11");
		AddQuestUserData("MarchCap", "sShore", XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore + "Gen"));
		AddQuestUserData("MarchCap", "sIsland", XI_ConvertString(pchar.GenQuest.MarchCap.Island + "Gen"));
		AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
		AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
		AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
		AddQuestUserData("MarchCap", "sName1", GetName(NAMETYPE_ORIG, pchar.GenQuest.MarchCap.PirateName, NAME_NOM));
		break;

	case "MarchCap_DieHard":
		dialog.text = "¡Eres un cobarde, maldito seas! ¡Acabas de huir del campo de batalla!";
		link.l1 = "¿Y qué crees que se suponía que debía hacer? ¿Dejar que ese pirata hundiera mi barco? ¡De ninguna manera, es mejor ser un cobarde vivo que un idiota muerto!";
		link.l1.go = "MarchCap_DieHard_1";
		break;

	case "MarchCap_DieHard_1":
		dialog.text = "¿Y por qué me he involucrado contigo, capitán? ¡Debería haber encontrado a un hombre que no temiera a los sables de abordaje!";
		link.l1 = "Ahora, te pido que abandones mi barco, necesito repararlo.";
		link.l1.go = "MarchCap_Talk_exit";
		break;

	case "MarchCap_AfterBattleGold":
		iTemp = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods)) - sti(pchar.GenQuest.MarchCap.StartGoodsQty)) * sti(Goods[sti(pchar.GenQuest.MarchCap.Goods)].Weight);
		iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods)) - sti(pchar.GenQuest.MarchCap.StartGoodsQty));
		pchar.GenQuest.MarchCap.CapPart = iQty / sti(pchar.GenQuest.MarchCap.Parts);
		if (iTemp < 10)
		{
			dialog.text = "¡Eres un perdedor, capitán! ¡No conseguimos ni una sola pieza de nuestro premio! ¡Y todo esto es por tu culpa! ¡Tú eres la razón de nuestro fracaso, maldición!";
			link.l1 = "¿Yo? ¡Mírate tú mismo! ¡No me has ayudado en la batalla! Solo he perdido mi tiempo contigo... ¡Fuera de mi barco!";
			link.l1.go = "MarchCap_Talk_exit";
			pchar.GenQuest.MarchCap = "bad";
			break;
		}
		if (iTemp > 10 && iTemp < 100)
		{
			dialog.text = "Bueno, esta incursión no fue tan exitosa como esperaba, nuestro botín es realmente modesto... Como sea, capitán, repartamos estos restos y despidámonos.";
			link.l1 = "Si me estuvieras ayudando en lugar de contar pájaros en el cielo, la incursión habría sido exitosa... Toma tu parte, " + FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart)) + "¡y piérdete!";
			link.l1.go = "MarchCap_Talk_exit";
			pchar.GenQuest.MarchCap = "poor";
			break;
		}
		if (iTemp > 100 && iTemp < 500)
		{
			dialog.text = "¡Bien hecho, capitán! El premio es " + FindRussianQtyString(iQty) + " piezas. Mi parte es " + FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart)) + ".";
			link.l1 = "Es correcto, " + npchar.name + ". No tengo objeciones. Los botes largos se están cargando ahora mismo. Quizás nos volvamos a encontrar...";
			link.l1.go = "MarchCap_Talk_exit";
			pchar.GenQuest.MarchCap = "good";
			break;
		}
		dialog.text = "¡Espléndido, capitán! Como dije, fue bastante fácil, ja-ja... El botín es enorme, mucho más de lo que esperaba. Es " + FindRussianQtyString(iQty) + " piezas. Mi parte es " + FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart)) + ".";
		link.l1 = "Es correcto, " + npchar.name + "  No tengo objeciones. Los botes largos se están cargando ahora mismo. Quizás, haremos otro ataque juntos en el futuro. Pareces un compañero adecuado para mí.";
		link.l1.go = "MarchCap_Deck_continue";
		pchar.GenQuest.MarchCap = "exellent";
		break;

	case "":
		dialog.text = "";
		link.l1 = "";
		link.l1.go = "";
		break;

	case "MarchCap_repeat":
		dialog.text = "" + GetAddress_Form(NPChar) + ", ve a tu barco. No tenemos tiempo para charlar. ¡Zarpemos!";
		link.l1 = "Sí, sí, por supuesto, tienes razón.";
		link.l1.go = "exit";
		NextDiag.TempNode = "MarchCap_repeat";
		break;

	case "MarchCap_exit":
		dialog.text = "Mm... No voy a hacerlo. ¡Piérdete! ¡Lo haré yo mismo!";
		link.l1 = "Bueno, bueno, que tengas un feliz viaje entonces...";
		link.l1.go = "MarchCap_DeckExit";
		break;

	case "MarchCap_DeckExit":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		npchar.lifeday = 0;
		DeleteAttribute(npchar, "AlwaysFriend");
		npchar.DontDeskTalk = true;
		DeleteAttribute(pchar, "GenQuest.MarchCap");
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}

int SelectMarchCapGoods1()
{
	int iGoods;
	switch (hrand(5))
	{
	case 0:
		iGoods = GOOD_EBONY;
		break;
	case 1:
		iGoods = GOOD_MAHOGANY;
		break;
	case 2:
		iGoods = GOOD_CINNAMON;
		break;
	case 3:
		iGoods = GOOD_COFFEE;
		break;
	case 4:
		iGoods = GOOD_CHOCOLATE;
		break;
	case 5:
		iGoods = GOOD_TOBACCO;
		break;
	}
	return iGoods;
}

int SelectPirateShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 5;
	if(iRank >= 12 && iRank < 21) iClass = 4;
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
}

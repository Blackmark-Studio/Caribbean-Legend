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
		dialog.text = "Un error. Asegúrate de informar a los desarrolladores.";
		link.l1 = "Está bien";
		link.l1.go = "exit";
		break;

	// разговор на палубе
	case "MarginCap":
		dialog.text = "Saludos, capitán. ¿Quieres algo de mí?";
		link.l1 = "Sí. Exactamente, " + GetAddress_FormToNPC(NPChar) + ". Hay un pasajero en tu barco que me interesa bastante. Se llama " + pchar.GenQuest.Marginpassenger.q1Name + ". Quiero que tu pasajero se convierta en mi pasajero. Si estás de acuerdo con eso, nos separaremos y nunca más nos volveremos a ver.";
		link.l1.go = "MarginCap_1";
		break;

	case "MarginCap_1":
		dialog.text = "¿Es eso así? ¿Y qué si digo que no?";
		link.l1 = "Entonces tendré que hacerte reconsiderar tu decisión con unas cuantas andanadas de mis cañones, que están apuntados en tu dirección en este mismo momento. No desafíes tu suerte, " + GetAddress_FormToNPC(NPChar) + ".";
		link.l1.go = "MarginCap_2";
		break;

	case "MarginCap_2":
		int MCparam = (7 - sti(RealShips[sti(pchar.ship.type)].Class)) * 100 + sti(pchar.ship.Crew.Morale) + sti(pchar.Ship.Crew.Exp.Sailors) + sti(pchar.Ship.Crew.Exp.Cannoners) + sti(pchar.Ship.Crew.Exp.Soldiers);
		int NPCparam = (7 - sti(RealShips[sti(npchar.ship.type)].Class)) * 100 + sti(npchar.ship.Crew.Morale) + sti(npchar.Ship.Crew.Exp.Sailors) + sti(npchar.Ship.Crew.Exp.Cannoners) + sti(npchar.Ship.Crew.Exp.Soldiers);
		if (MCparam > NPCparam) // отдаст сам
		{
			dialog.text = "No tengo otra opción entonces. El destino de mi tripulación es más valioso para mí que el destino de un solo hombre. ¡Pero no te saldrás con la tuya tan fácilmente! ¡No lo olvidaré!";
			link.l1 = "¡Cálmate, y sálvate de un ataque al corazón... ¡Tráeme a mi nuevo pasajero!";
			link.l1.go = "MarginCap_3";
		}
		else
		{
			dialog.text = "Será mejor que abandone mi barco, señor, mientras todavía se lo permito. No trate de asustarme. Y no se atreva a atacar mi nave, de lo contrario será repelido de inmediato. ¡Salga, mientras todavía estoy de buen humor!";
			link.l1 = "Te he advertido. Estoy en camino. Nos vemos pronto, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "MarginCap_4";
		}
		break;

	case "MarginCap_3":
		DialogExit();
		npchar.Dialog.CurrentNode = "MarginCap_repeat";
		// отдаем пассажира
		sld = GetCharacter(NPC_GenerateCharacter("MarginPass", pchar.GenQuest.Marginpassenger.model, pchar.GenQuest.Marginpassenger.sex, pchar.GenQuest.Marginpassenger.ani, 2, sti(pchar.GenQuest.Marginpassenger.Nation), -1, true, "quest"));
		sld.Dialog.Filename = "Quest\Marginpassenger.c";
		sld.Dialog.currentnode = "MarginPass";
		sld.name = pchar.GenQuest.Marginpassenger.q1Name;
		sld.lastname = "";
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		Map_ReleaseQuestEncounter(npchar.id);
		npchar.Abordage.Enable = false; // запрет абордажа
		npchar.ShipEnemyDisable = true;
		npchar.AlwaysFriend = true;
		ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;

	case "MarginCap_4":
		DialogExit();
		NextDiag.CurrentNode = "MarginCap_repeat";
		pchar.GenQuest.Marginpassenger.Mustboarding = "true";
		AddQuestRecord("Marginpassenger", "5");
		AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name") + "Acc")));
		AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
		ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;

	case "MarginCap_repeat":
		dialog.text = "Ya hemos tenido una charla, ¿recuerdas? ¡Aléjate de mi barco!";
		link.l1 = "...";
		link.l1.go = "exit";
		NextDiag.TempNode = "MarginCap_repeat";
		break;

	case "MarginCap_abordage":
		if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Mustboarding"))
		{
			dialog.text = "¡Argh, bastardo! ¡Quema en el infierno por tus actos!";
			link.l1 = "Te he ofrecido entregarme al pasajero pacíficamente... y has rechazado mi oferta. ¡Ahora sólo tú tienes la culpa!";
			link.l1.go = "MarginCap_abordage_1";
		}
		else
		{
			dialog.text = "¡Argh, bastardo! ¿Por qué has atacado el pacífico barco? ¡No tenemos oro ni bienes valiosos!";
			link.l1 = "Pero tienes a una persona valiosa a bordo..." + pchar.GenQuest.Marginpassenger.q1Name + " Quiero a tu pasajero.";
			link.l1.go = "MarginCap_abordage_2";
		}
		break;

	case "MarginCap_abordage_1":
		dialog.text = "¡Tú... eres el sucio pirata!";
		link.l1 = "Menos charla, mi amigo...";
		link.l1.go = "MarginCap_abordage_3";
		break;

	case "MarginCap_abordage_2":
		dialog.text = "¿Y por eso has cometido una matanza en mi barco? ¡Muchos hombres están muertos! ¡Pirata!";
		link.l1 = "Menos charla, mi amigo...";
		link.l1.go = "MarginCap_abordage_3";
		break;

	case "MarginCap_abordage_3":
		DialogExit();
		LAi_SetCurHPMax(npchar);
		QuestAboardCabinDialogFree();
		LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Marginpassenger_GivePrisoner");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "MarginNeed":
		dialog.text = "¿Qué quieres, " + GetAddress_Form(NPChar) + "?";
		link.l1 = "¿Eres tú " + pchar.GenQuest.Marginpassenger.q2Name + "?";
		link.l1.go = "MarginNeed_1";
		break;

	case "MarginNeed_1":
		dialog.text = "Sí, soy yo. ¿Quieres presentar una solicitud? Entonces debes saber que...";
		link.l1 = "Espere un momento, señor. Tengo un tipo de solicitud un poco diferente... ¿Conoce a alguien llamado " + pchar.GenQuest.Marginpassenger.q1Name + "?";
		link.l1.go = "MarginNeed_2";
		break;

	case "MarginNeed_2":
		switch (pchar.GenQuest.Marginpassenger.sex)
		{
		case "woman":
			dialog.text = "Sí, la conozco... ¡Claro que sí! ¿Qué pasa?";
			link.l1 = "Se había metido en una historia muy desagradable: su barco fue capturado por piratas. Afortunadamente, tuve la oportunidad de abordar su barco y salvar a la pobre alma. Ella me ha dicho tu nombre y aquí estoy.";
			link.l1.go = "MarginNeed_woman";
			break;
		case "man":
			dialog.text = "Sí, conozco muy bien a este hombre. ¿Qué sucede?";
			link.l1 = "Se había metido en una historia muy desagradable: su barco fue capturado por piratas. Afortunadamente, tuve la oportunidad de abordar su barco y salvar a este prisionero. Me ha dicho tu nombre y aquí estoy.";
			link.l1.go = "MarginNeed_man";
			break;
		}
		break;

	case "MarginNeed_woman":
		dialog.text = "¡Oh Dios! ¿Dónde está ella ahora? ¿Por qué no la has traído aquí?";
		link.l1 = "Está a salvo. Y en cuanto a tu pregunta... no es tan sencillo. Podría haberla llevado de vuelta a casa yo mismo, pero puedo darte esta oportunidad a ti. Por una modesta tarifa, por supuesto.";
		link.l1.go = "MarginNeed_woman_1";
		break;

	case "MarginNeed_woman_1":
		dialog.text = "Mm... No lo entiendo...";
		link.l1 = "¿Por qué no lo haces? Me pagas en oro, yo te daré a la chica y podrás usar esta situación en tus intereses... Quieres casarte con ella, ¿verdad? Y yo repararé mi barco con esas monedas, fue dañado durante esa pelea con los piratas.";
		link.l1.go = "MarginNeed_money";
		break;

	case "MarginNeed_man":
		dialog.text = "¡Dios mío! ¿Dónde está ahora? ¿Por qué no lo has traído aquí?";
		link.l1 = "Él está a salvo. Y sobre tu pregunta... no es tan sencillo. Podría haberlo llevado a casa yo mismo, pero puedo darte esta oportunidad a ti, considerando que tienes tus propios intereses en su familia. Por una modesta tarifa, por supuesto.";
		link.l1.go = "MarginNeed_man_1";
		break;

	case "MarginNeed_man_1":
		dialog.text = "Hm... No lo entiendo...";
		link.l1 = "¿Por qué no lo haces? Me pagas en oro, te devolveré a tu amigo y podrás usar esta situación en tu beneficio. Tengo algo de información, ¿sabes...? Repararé mi barco con esas monedas, ella resultó dañada durante esa pelea con los piratas.";
		link.l1.go = "MarginNeed_money";
		break;

	case "MarginNeed_money":
		dialog.text = "Bueno, bueno... ¿y cuánto quieres?";
		link.l1 = "Considera que quiero doblones, no pesos.";
		link.l1.go = "MarginNeed_money_1";
		break;

	case "MarginNeed_money_1":
		dialog.text = "Está bien, está bien... ¿Cuántos doblones quieres?";
		Link.l1.edit = 1;
		link.l1 = "";
		link.l1.go = "MarginNeed_money_2";
		break;

	case "MarginNeed_money_2":
		iTemp = sti(dialogEditStrings[1]);
		int iSum = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon) * 5 * stf(pchar.GenQuest.Marginpassenger.Chance));
		if (iTemp <= 0)
		{
			dialog.text = "Muy gracioso. Está bien, finjamos que tu broma fue divertida. ¡Adiós!";
			link.l1 = "Mm...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 0 && iTemp <= iSum)
		{
			if (hrand(2) > 1) // Addon-2016 Jason уменьшаем раздачу дублонов
			{
				dialog.text = "Está bien, estoy de acuerdo. Poseo la suma requerida. ¿Dónde está " + pchar.GenQuest.Marginpassenger.q1Name + "?";
				link.l1 = "Debe estar en el muelle ya. Así que puedes ir a buscar al pasajero.";
				link.l1.go = "MarginNeed_dublon";
			}
			else
			{
				dialog.text = "Lo siento, pero no tengo tantos doblones. ¿Servirán los pesos?";
				link.l1 = "Quiero doblones, pero supongo que el maestro del barco aceptará pesos... Dámelos.";
				link.l1.go = "MarginNeed_peso";
				link.l2 = "No, solo necesito doblones.";
				link.l2.go = "MarginNeed_dublon_exit";
			}
			break;
		}
		if (iTemp > iSum && iTemp < 1000)
		{
			dialog.text = "Desafortunadamente, no tengo tal suma. Así que no puedo aceptar tu propuesta, aunque lo desee con todas mis fuerzas.";
			link.l1 = "Hum...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 1000 && iTemp < 3000)
		{
			dialog.text = "Señor, ¿entiende siquiera de qué está hablando? ¿Es consciente de que esta suma es demasiado grande? ¡Lárguese al infierno de aquí!";
			link.l1 = "Mm...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		dialog.text = "Bueno... Señor, tiene que ir al médico inmediatamente. Parece que tiene una fiebre muy fuerte o... de todos modos, necesita un médico. Y yo estoy demasiado ocupado. ¡Adiós!";
		link.l1 = "Mm...";
		link.l1.go = "MarginNeed_exit";
		break;

	case "MarginNeed_dublon":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
		npchar.lifeday = 0;
		sld = characterFromId("MarginPass");
		RemovePassenger(Pchar, sld);
		sld.lifeday = 0;
		iTemp = sti(dialogEditStrings[1]);
		TakeNItems(pchar, "gold_dublon", iTemp);
		AddQuestRecord("Marginpassenger", "9");
		AddQuestUserData("Marginpassenger", "sSum", iTemp);
		CloseQuestHeader("Marginpassenger");
		DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		AddCharacterExpToSkill(pchar, "Fortune", 100); // везение
		break;

	case "MarginNeed_peso":
		dialog.text = "Aquí está, toda la suma en pesos, justo lo que querías... ¿Dónde está " + pchar.GenQuest.Marginpassenger.q1Name + "?";
		link.l1 = "Debe estar en el muelle ahora. Así que puedes ir a buscar al pasajero..";
		link.l1.go = "MarginNeed_peso_1";
		break;

	case "MarginNeed_peso_1":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
		npchar.lifeday = 0;
		sld = characterFromId("MarginPass");
		RemovePassenger(Pchar, sld);
		sld.lifeday = 0;
		iTemp = sti(dialogEditStrings[1]) * 100;
		AddMoneyToCharacter(pchar, iTemp);
		AddQuestRecord("Marginpassenger", "10");
		AddQuestUserData("Marginpassenger", "sSum", FindRussianMoneyString(iTemp));
		CloseQuestHeader("Marginpassenger");
		DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		AddCharacterExpToSkill(pchar, "Fortune", 80); // везение
		break;

	case "MarginNeed_dublon_exit":
		dialog.text = "Entonces no puedo aceptar tu propuesta, aunque lo desee con todas mis fuerzas. ¡Adiós!";
		link.l1 = "Mm...";
		link.l1.go = "MarginNeed_exit";
		break;

	case "MarginNeed_exit":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		npchar.lifeday = 0;
		AddQuestRecord("Marginpassenger", "11");
		AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
		AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.City));
		// belamour gen: Добряку недолго осталось -->
		if (CheckAttribute(pchar, "questTemp.LongHappy"))
		{
			AddQuestUserData("Marginpassenger", "sBaron", "a Puerto Príncipe con Black Pastor");
		}
		else
		{
			AddQuestUserData("Marginpassenger", "sBaron", "a Le Francois con Kindly Jacques");
		}
		// <-- belamour gen
		pchar.GenQuest.Marginpassenger = "cabin";
		break;

	case "MarginPass":
		dialog.text = "¿Qué es... ¿Qué está pasando aquí?!";
		link.l1 = "Es muy sencillo, " + NPCharSexPhrase(NPChar, "compañero", "chica") + " . Ahora eres mi querido pasajero. Un pasajero vigilado. No intentes resistirte o acabarás en la bodega.";
		link.l1.go = "MarginPass_1";
		break;

	case "MarginPass_1":
		dialog.text = "¿Quieres decir que soy tu prisionero?";
		link.l1 = "Oh, no. Por supuesto que no. No un prisionero, sino un querido invitado. Un invitado muy valioso...";
		link.l1.go = "MarginPass_2";
		break;

	case "MarginPass_2":
		dialog.text = "¡Tú... tú pagarás por tus acciones!";
		link.l1 = "Te equivocas de nuevo," + NPCharSexPhrase(NPChar, ", compadre", ", querido") + " No pagaré, pero me pagarán a mí. ¡Basta de hablar, ve a tu camarote!";
		link.l1.go = "MarginPass_3";
		break;

	case "MarginPass_3":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "", "", "none", "", "", "", 1.0);
		AddPassenger(pchar, npchar, false);
		SetCharacterRemovable(npchar, false);
		pchar.quest.Marginpassenger_InWorldOver.over = "yes"; // снять прерывание
		pchar.quest.Marginpassenger_Sink.over = "yes";		  // снять прерывание
		pchar.GenQuest.Marginpassenger = "take";
		if (rand(2) == 1)
			pchar.GenQuest.Marginpassenger.lose = "true";
		else
			Marginpassenger_CreateNeedman();
		if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Boarding"))
			AddQuestRecord("Marginpassenger", "6");
		else
			AddQuestRecord("Marginpassenger", "4");
		AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
		AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
		AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name") + "Acc")));
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}

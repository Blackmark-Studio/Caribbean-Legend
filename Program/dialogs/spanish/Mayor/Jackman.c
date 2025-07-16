// Якоб Джекман
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
	if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
	{
		npchar.angry.ok = 1;
		if (!CheckAttribute(npchar, "angry.first")) // ловушка первого срабатывания
		{
			NextDiag.TempNode = NextDiag.CurrentNode;
			Dialog.CurrentNode = "AngryExitAgain";
			npchar.angry.first = 1;
		}
		else
		{
			switch (npchar.angry.kind) // сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
			{
			case "repeat":
				if (npchar.angry.name == "Firsttime")
					Dialog.CurrentNode = "AngryRepeat_1";
				if (npchar.angry.name == "I_know_you_good")
					Dialog.CurrentNode = "AngryRepeat_2";
				break;
			}
		}
	}
	// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
	// ============================================================================

	switch (Dialog.CurrentNode)
	{
	// ----------------------------------- Диалог первый - первая встреча
	case "First time":
		dialog.text = NPCStringReactionRepeat("" + GetSexPhrase("¿Tienes algo que decirme? ¿No? ¡Entonces lárgate de aquí!", "Ja, " + pchar.name + "¡Tienes negocios conmigo? ¿No? Entonces no me molestes.") + "", "Creo que me he explicado lo suficientemente claro, deja de molestarme.", "¡Aunque he sido claro, sigues molestándome!", "Bien, me estoy cansando de esta grosería, lárgate, bicho raro.", "repeat", 3, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Ya me voy.", "Claro, Jackman...", "Lo siento, Jackman...", "Ay...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";

		if (sti(pchar.GenQuest.Piratekill) > 20)
		{
			dialog.text = RandPhraseSimple("¿Estás loco? ¿Querías jugar a ser carnicero? Todos los piratas están enfadados contigo, muchacho, será mejor que abandones este lugar...", "  Parece que te volviste loco, muchacho. ¿Querías estirar un poco las manos? Sin ofender, pero no tienes nada que hacer aquí. ¡Piérdete!");
			link.l1 = RandPhraseSimple("Escucha, quiero arreglar la situación...", " Ayúdame a resolver este problema... ");
			link.l1.go = "pirate_town";
			break;
		}

		//--> Сага
		if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "maruntown")
		{
			link.l1 = "¿Dónde puedo encontrar a Jimmy Higgins?";
			link.l1.go = "Saga_Jimmy";
		}
		if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "jackman")
		{
			link.l1 = "Yo de nuevo, Jackman. Dicen que estás buscando a algunas personas desaparecidas...";
			link.l1.go = "Saga_search";
		}
		//<-- Сага

		// поручение капитана - выкуп
		if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
		{
			if (CheckAttribute(pchar, "GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "Es sobre tu prisionero.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar, "GenQuest.CaptainComission.toMayor");
			}
			if (CheckAttribute(pchar, "GenQuest.CaptainComission.PirateShips"))
			{
				link.l1 = "Hola, Jackman. Sobre tu misión...";
				link.l1.go = "CapComission3";
			}
			if (CheckAttribute(pchar, "GenQuest.CaptainComission.RepeatSpeak"))
			{
				link.l1 = "Es sobre tu prisionero.";
				link.l1.go = "CapComission6";
			}
		}
		break;

	case "Exit":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		break;

	case "I_know_you_good":
		dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + ", ¡Me alegra verte! ¿Qué quieres?", "¿Qué quieres?", "¿Tú otra vez? ¡No molestes a la gente si no tienes nada que hacer!", "Eres " + GetSexPhrase("un buen corsario", " una buena chica") + ", así que puedes vivir por ahora. Pero no quiero hablar contigo más.", "repeat", 10, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Sólo haciendo una visita.", "Nada...", "Está bien, Jackman, lo siento...", "¡Maldita sea! Bueno, como dices...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		NextDiag.TempNode = "I_know_you_good";

		if (sti(pchar.GenQuest.Piratekill) > 20)
		{
			dialog.text = RandPhraseSimple("¿Estás loco? ¿Querías jugar a ser carnicero? Todos los piratas están enfadados contigo, chico, será mejor que te largues de aquí...");
			link.l1 = RandPhraseSimple("Escucha, quiero arreglar la situación...", "Ayúdame a resolver este problema...");
			link.l1.go = "pirate_town";
			break;
		}

		// поручение капитана - выкуп
		if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.toMayor"))
		{
			link.l1 = "Es sobre tu prisionero.";
			link.l1.go = "CapComission1";
			DeleteAttribute(pchar, "GenQuest.CaptainComission.toMayor");
		}
		break;

		//-----------------------------------------пиратская сага----------------------------------------------------
	case "Saga_Jimmy":
		dialog.text = "¡De verdad! ¡Alguien necesita a este holgazán! Ha estado bebiendo ron solo en su choza durante varios días. No te aconsejo que lo visites. No es el mejor hombre, ni siquiera cuando está sobrio...";
		link.l1 = "Está bien, tampoco soy un santo. ¿Dónde está su choza?";
		link.l1.go = "Saga_Jimmy_1";
		break;

	case "Saga_Jimmy_1":
		dialog.text = "Está justo frente a la taberna. Eligió un buen lugar para correr rápido a tomar un trago.";
		link.l1 = "¡Gracias!";
		link.l1.go = "Saga_Jimmy_2";
		break;

	case "Saga_Jimmy_2":
		DialogExit();
		pchar.quest.Saga_createJimmy.win_condition.l1 = "location";
		pchar.quest.Saga_createJimmy.win_condition.l1.location = "FortOrange_House1";
		pchar.quest.Saga_createJimmy.function = "Saga_CreateJimmy";
		pchar.questTemp.Saga = "jimmy";
		break;

	case "Saga_search":
		dialog.text = "¿Y quién te ha dicho eso? ¿Ese cabeza de borracho Higgins? ¿Has averiguado algo sobre Gladys Chandler o Henry el Verdugo?";
		link.l1 = "Nada especial, en realidad, pero quiero saber algo específico sobre ese Ahorcado.";
		link.l1.go = "Saga_search_1";
		break;

	case "Saga_search_1":
		dialog.text = "No hay nada que saber al respecto. Pocos lo recuerdan ahora, pero hace veinte años Henry era muy popular entre las putas desde Bridgetown hasta Tortuga. ¡Vaya que sí! ¡Un contramaestre del 'Neptune', bajo el mando del propio capitán Butcher! Debe ser muy viejo ahora, si es que aún está vivo, por supuesto.\nLas posibilidades son bajas, pero nada es imposible. Pagaré veinte mil pesos por cualquier información sobre él, el doble si lo traes aquí vivo.";
		link.l1 = "¿Cuánto pagarás por Gladys y su hija?";
		link.l1.go = "Saga_search_2";
		break;

	case "Saga_search_2":
		dialog.text = "Oh, ella no es su hija. Si traes a esa chica con vida, te pagaré un montón de doblones. No estoy interesado en Gladys. ¿Preguntas?";
		link.l1 = "Desearía saber la razón de este alboroto, pero no voy a preguntar. Parece que podría acortar mi biografía.";
		link.l1.go = "Saga_search_3";
		break;

	case "Saga_search_3":
		dialog.text = "Quizás... Esos secretos no son de tu incumbencia. Sabe menos, vive más. No intentes hacerme esas preguntas de nuevo, porque he empezado a sospechar que hay algo raro contigo. Pierdete antes de que cambie de opinión.";
		link.l1 = "¡Hasta la vista, barón!";
		link.l1.go = "Saga_search_4";
		break;

	case "Saga_search_4":
		DialogExit();
		AddQuestRecord("Saga", "6");
		if (CheckAttribute(pchar, "questTemp.Saga.Jimmysecret"))
		{
			AddQuestUserData("Saga", "sText", "A Antigua ahora. La corbeta debe ser abordada.");
			DeleteAttribute(pchar, "questTemp.Saga.Jimmysecret");
		}
		pchar.quest.Saga_createDonovan.win_condition.l1 = "location";
		pchar.quest.Saga_createDonovan.win_condition.l1.location = "Antigua";
		pchar.quest.Saga_createDonovan.function = "Saga_createDonovan";
		pchar.questTemp.Saga = "donovan";
		break;

	// абордаж, в каюте
	case "Jackman_abordage":
		dialog.text = "¡Ja! Nos encontramos de nuevo, capitán " + GetFullName(pchar) + ". Admito que eres un oponente digno, a pesar de tus intentos de hacerte pasar por un simplón en Maroon-Town. He descubierto algo sobre ti, tus intrigas con la Compañía Holandesa de las Indias Occidentales fueron descubiertas... Ahora entiendo qué tipo de persona eres.";
		link.l1 = "Conozco tu tipo también, Jacob. Así que no nos hagamos ilusiones.";
		link.l1.go = "Jackman_abordage_1";
		break;

	case "Jackman_abordage_1":
		dialog.text = "¡Y cómo me has engañado con 'Marlin'! Supongo que mi pobre hermano está muerto...";
		link.l1 = "Tengo entendido que quieres vengarte por él. Pero también tengo una larga cuenta pendiente contigo. Por el acorralado Nathaniel, su esposa, su fragata, el calumniado Shark, Blaze Sharp...";
		link.l1.go = "Jackman_abordage_2";
		break;

	case "Jackman_abordage_2":
		dialog.text = "¿Blaze? No lo maté.";
		link.l1 = "Incluso si es cierto, el resto de mi lista es suficiente. Estoy harto de tu nombre. ¡Suficientes palabras, Jackman! ¡Nuestras espadas hablarán!";
		link.l1.go = "Jackman_abordage_3";
		break;

	case "Jackman_abordage_3":
		dialog.text = "Qué necio tan vehemente... ¡Maldito seas! ¡Ahora más te vale aguantar! ¡Jacob Jackman nunca ha sido derrotado! ¡Carpacho, llegas justo a tiempo! ¡Ven aquí!";
		link.l1 = "...";
		link.l1.go = "Jackman_abordage_4";
		break;

	case "Jackman_abordage_4":
		DialogExit();
		LAi_SetCurHPMax(npchar);
		QuestAboardCabinDialogFree();
		LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterJackmanBoarding");
		AddDialogExitQuest("MainHeroFightModeOn");
		// подкрепление
		int iRank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 12;
		int iScl = 30 + 2 * sti(pchar.rank);
		sld = GetCharacter(NPC_GenerateCharacter("Saga_JackmanCabinHelper", "citiz_58", "man", "man", iRank, sti(npchar.nation), 0, true, "quest"));
		FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol4", "bullet", iScl * 2 + 100);
		LAi_SetCheckMinHP(sld, 150, true, "Saga_DannyHurryHelp");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		sld = characterFromId("Danielle");
		RemovePassenger(Pchar, sld);
		break;

	//*************************** Генератор "Captain's offer - Ransom" **********************
	case "CapComission1":
		dialog.text = "Ja-ja. ¿Crees que sólo tengo un prisionero aquí? Nómbralo.";
		link.l1 = pchar.GenQuest.CaptainComission.SlaveName + "¿Está aquí?";
		link.l1.go = "CapComission2";
		DeleteAttribute(pchar, "GenQuest.CaptainComission.toMayor");
		break;

	case "CapComission2":
		if (CheckAttribute(pchar, "GenQuest.CaptainComission.DaysLeft"))
		{
			dialog.text = "Lo era. Lo he vendido a ese dueño de plantación de Barbados, el coronel Bishop, cuando estuvo aquí hace una semana.";
			link.l1 = "Maldita sea...";
			link.l1.go = "CapComission2_1";
		}
		else
		{
			dialog.text = "Ah, al fin. Estaba pensando en venderlo a ese dueño de plantación de Barbados, él estará aquí en una o dos semanas... ¿Tienes un rescate?";
			link.l1 = "Mira, hay un pequeño problema... En realidad, no tengo tanto dinero. Pero estoy listo para trabajar.";
			link.l1.go = "CapComission2_2";
			if (makeint(pchar.money) > 150000)
			{
				link.l2 = "Es bueno que no lo hayas vendido. Aquí están tus monedas - 150.000 pesos. ¿Dónde puedo encontrarlo?" link.l2.go = "CapComission2_3";
			}
		}
		break;

	case "CapComission2_1":
		dialog.text = "Fuiste demasiado lento... ¿Y por qué te importa él? Solo he estado negociando con sus parientes.";
		link.l1 = "Me han pedido que venga aquí.";
		link.l1.go = "CapComission2_11";
		break;

	case "CapComission2_11":
		dialog.text = "Bueno, llegas tarde. No puedo hacer nada.";
		link.l1 = "Escucha, ¿por cuánto lo has vendido si no es un secreto?";
		link.l1.go = "CapComission2_12";
		break;

	case "CapComission2_12":
		dialog.text = "Eh, no lo es. Pero no te lo diré... Te reirás si lo hago. ¡Ja-ja-ja-ja! Adiós.";
		link.l1 = "Nos vemos...";
		link.l1.go = "exit";
		AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
			// AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
			break;

	case "CapComission2_2":
		if (rand(1) == 0)
		{
			dialog.text = "Bueno, bueno... Tengo un asunto... Ni siquiera sé por dónde empezar. Necesito hundir a un pirata que se pasó de la raya.";
			link.l1 = "¿No se le puede simplemente matar en la jungla?";
			link.l1.go = "CapComission2_2_1";
		}
		else
		{
			dialog.text = "Bueno, " + pchar.name + ", sabes, no funciona así. Vuelve con el dinero y obtendrás a tu debilucho, ja-ja.";
			link.l1 = "Está bien. Nos vemos.";
			link.l1.go = "CapComission2_4";
		}
		break;

	case "CapComission2_2_1":
		dialog.text = "No es así como funcionan los negocios, ¿sabes?... No necesito su muerte, necesito enseñar a algunos a mantenerse alejados de tomar mi parte del botín. Pero si va a alimentar a los tiburones, no me voy a molestar.";
		link.l1 = "¿Por qué no envías a tus propios hombres tras él?";
		link.l1.go = "CapComission2_2_2";
		break;

	case "CapComission2_2_2":
		CaptainComission_GetRandomShore();
		pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
		pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
		pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
		sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl");
		dialog.text = "Mm... Bueno, " + GetName(NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM) + " ha convencido a algunos piratas de que su parte del botín está guardada en nuestro escondite no lejos de " + XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen") + ". Sus dos barcos '" + pchar.GenQuest.CaptainComission.ShipName1 + "' y '" + pchar.GenQuest.CaptainComission.ShipName2 + "' levantaron anclas hace poco y navegaron hacia " + sLoc + ". ¿Ahora ves por qué no puedo confiar en mis hombres para hacer ese trabajo?";
		link.l1 = "Lo veo. ¿Cuánto tiempo tengo?";
		link.l1.go = "CapComission2_2_3";
		break;

	case "CapComission2_2_3":
		dialog.text = "12 a 15 días, no más, supongo. No quiero que lleguen al escondite, o será una tontería hundirlos con un cargamento valioso. En ese caso, sería mejor que lo trajeran aquí...";
		link.l1 = "Está bien, estoy dentro. Intentaré atraparlos.";
		link.l1.go = "CapComission2_2_4";
		break;

	case "CapComission2_2_4":
		AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
			// AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat"));				 // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
			pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
			pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips";
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";
			DialogExit();
			break;

	case "CapComission2_3":
		dialog.text = "No te preocupes. Mis hombres lo llevarán a tu barco. ¿Y por qué te importa él?";
		link.l1 = "No lo hago. Sus parientes me pidieron que lo entregue.";
		link.l1.go = "CapComission2_31";
		break;

	case "CapComission2_31":
		dialog.text = "Ah, está bien. Casi me sentí mal por ofrecer un precio tan bajo por tu hombre. Ja-ja-ja-ja. Adiós.";
		link.l1 = "Nos vemos.";
		link.l1.go = "CapComission2_32";
		break;

	case "CapComission2_32":
		AddQuestRecord("CaptainComission1", "9");
		AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
		AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
		addMoneyToCharacter(pchar, -150000);
		DialogExit();
		AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

	case "CapComission2_4":
		if (!CheckAttribute(pchar, "GenQuest.CaptainComission.RepeatSpeak"))
		{
			AddQuestRecord("CaptainComission1", "31");
			AddQuestUserData("CaptainComission1", "sName", "Jackman"); // belamour gen
																	   // AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
		}
		pchar.GenQuest.CaptainComission.RepeatSpeak = true;
		DialogExit();
		break;

	case "CapComission3":
		dialog.text = "Entonces, " + GetFullName(pchar) + ", ¿hundiste a mi compinche? Je-je-je...";
		if (pchar.GenQuest.CaptainComission.PirateShips == "goaway")
		{
			link.l1 = "No. No pude atraparlos. Y no los encontré al regresar.";
			link.l1.go = "CapComission4";
		}
		if (pchar.GenQuest.CaptainComission.PirateShips == "died")
		{
			link.l1 = "Lo hice. Los envié a alimentar a los tiburones.";
			link.l1.go = "CapComission5";
		}
		DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		break;

	case "CapComission4":
		dialog.text = "¡Maldita sea! ¡Los hayas conocido o no, ya no importa! ¿Y cuál será tu próxima sugerencia?";
		link.l1 = "¿Tal vez tienes un trabajo más fácil para mí?";
		link.l1.go = "CapComission4_1";
		link.l2 = "Escucha, Jackman, baja el precio por el prisionero...";
		link.l2.go = "CapComission4_2";
		break;

	case "CapComission4_1":
		dialog.text = "No.";
		link.l1 = "Adiós entonces...";
		link.l1.go = "CapComission4_3";
		break;

	case "CapComission4_2":
		dialog.text = "¿Bajar el precio? ¡Acabo de perder mi alijo por tu incompetencia! ¡Y ahora puedo subir el precio! Puedes llevártelo por 200,000 pesos si quieres, o puedes largarte al infierno de aquí.";
		link.l1 = "Es demasiado caro... Adiós...";
		link.l1.go = "CapComission4_4";
		if (sti(pchar.money) >= 200000)
		{
			link.l2 = "Maldita sea, toma tus monedas.";
			link.l2.go = "CapComission4_5";
		}
		break;

	case "CapComission4_3":
		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		AddQuestRecord("CaptainComission1", "27");
		AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
		AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
		AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
		DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		DialogExit();
		break;

	case "CapComission4_4":
		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		AddQuestRecord("CaptainComission1", "28");
		AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
		AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
		AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
		DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		DialogExit();
		break;

	case "CapComission4_5":
		dialog.text = "Está bien, puedes llevarte a este debilucho...";
		link.l1 = "Adiós.";
		link.l1.go = "CapComission4_6";
		break;

	case "CapComission4_6":
		addMoneyToCharacter(pchar, -200000);
		AddQuestRecord("CaptainComission1", "29");
		AddQuestUserData("CaptainComission1", "sName", "Jackman");																   // belamour gen
		AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
		AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
		DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
		DialogExit();
		AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

	case "CapComission5":
		dialog.text = "¡Ja-ja! ¡Bien hecho! Toma a tu debilucho y buena suerte.";
		link.l1 = "Gracias. Adiós.";
		link.l1.go = "CapComission5_1";
		break;

	case "CapComission5_1":
		AddQuestRecord("CaptainComission1", "34");
		AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
		AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
		AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
		DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		DialogExit();
		AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

	case "CapComission6":
		dialog.text = "¿Has traído el dinero, Charles? No estaba bromeando sobre vender al hombre a la plantación.";
		link.l1 = "Escucha, " + NPChar.name + ", hay un problema... No tengo tanto dinero. Pero estoy listo para trabajar.";
		link.l1.go = "CapComission2_2";
		if (makeint(pchar.money) > 150000)
		{
			link.l2 = "Es bueno que no lo hayas vendido. Aquí están tus monedas - 150.000 pesos. ¿Dónde puedo encontrarlo?" link.l2.go = "CapComission2_3";
		}
		break;

	// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
	case "Man_FackYou":
		dialog.text = LinkRandPhrase("¡Robo!!! Eso es inaceptable! Prepárate, " + GetSexPhrase("chico", "chica") + "...", "¡Oye, qué demonios estás haciendo ahí?! ¿Pensaste que podrías robarme? Estás acabado...", "Espera, ¿qué demonios? ¡Quita tus manos! ¡Resulta que eres un ladrón! Se acabó el camino, bastardo...");
		link.l1 = LinkRandPhrase("¡Mierda!", "¡Caramba!!", "¡Maldita sea!!");
		link.l1.go = "PL_Q3_fight";
		break;

	// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
	case "AngryRepeat_1":
		dialog.text = RandPhraseSimple("¡Aléjate de aquí!", "¡Fuera de mi casa!");
		link.l1 = "Oups...";
		link.l1.go = "AngryExitAgainWithOut";
		if (CheckAttribute(npchar, "angry.terms")) // примиряемся с Джекменом через 10 дней.
		{
			if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
			{
				dialog.text = "No me molestes con tus charlas baratas. La próxima vez no te gustará el resultado...";
				link.l1 = "Lo tengo.";
				link.l1.go = NextDiag.TempNode;
				CharacterDelAngry(npchar);
			}
		}
		break;
	case "AngryRepeat_2":
		dialog.text = "Se acabó, no hay más que hablar."
					  "No quiero hablar contigo más, así que será mejor que no me molestes.";
		link.l1 = RandPhraseSimple("Como desees...", "Está bien entonces...");
		link.l1.go = "AngryExitAgain";
		if (CheckAttribute(npchar, "angry.terms")) // примиряемся с Джекменом через 10 дней.
		{
			if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
			{
				dialog.text = "¿Espero que muestres más respeto y dejes de ser grosero? De lo contrario, tendré que matarte. Eso sería muy desagradable.";
				link.l1 = "Puedes estar seguro, Jackman, lo haré.";
				link.l1.go = NextDiag.TempNode;
				CharacterDelAngry(npchar);
			}
		}
		break;
	case "AngryExitAgain":
		DialogExit();
		DeleteAttribute(npchar, "angry.ok");
		break;
	case "AngryExitAgainWithOut":
		DialogExit();
		DeleteAttribute(npchar, "angry.ok");
		DoReloadCharacterToLocation("Fortorange_town", "reload", "reload6");
		break;
	// <<<<<<<<<<<<============= блок нод angry =============================
	case "pirate_town":
		dialog.text = "¿Resolver el problema? ¿Entiendes lo que has hecho? De todas formas, tráeme un millón de pesos y persuadiré a los muchachos para que olviden tus 'hazañas'. Si no te gusta la idea, entonces puedes irte al infierno.";
		if (sti(Pchar.money) >= 1000000)
		{
			link.l1 = "Está bien, estoy listo para pagar.";
			link.l1.go = "pirate_town_pay";
		}
		link.l2 = "Entendido. Me voy.";
		link.l2.go = "pirate_town_exit";
		break;

	case "pirate_town_exit":
		DialogExit();
		bDisableFastReload = true; // закрыть переход
		pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
		pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
		pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;

	case "pirate_town_pay":
		dialog.text = "¡Bien! Considérate limpio de nuevo. Pero espero que no vuelvas a hacer cosas tan asquerosas.";
		link.l1 = "No lo haré. Demasiado caro para mí. Adiós...";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, -1000000);
		pchar.GenQuest.Piratekill = 0;
		break;
	}
}

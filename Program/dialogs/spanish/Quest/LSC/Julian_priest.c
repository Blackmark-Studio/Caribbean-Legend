// брат Юлиан - священник
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
		{
			dialog.text = "No deseo hablar contigo. Atacas a los pacíficos lugareños sin razón y los provocas a pelear. ¡Piérdete, ateo!";
			link.l1 = "Como desees...";
			link.l1.go = "exit";
			break;
		}
		if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
		{
			dialog.text = "No me sorprende que hayas sobrevivido. Misteriosos son los caminos del Señor. La vida y la muerte están en Sus manos.";
			link.l1 = "Estoy completamente de acuerdo contigo, hermano Julian.";
			link.l1.go = "exit";
			npchar.quest.return_isl = "true";
			break;
		}
		if (npchar.quest.meeting == "0")
		{
			dialog.text = "Bienvenido a la santa iglesia de nuestra Isla, hijo mío. Las puertas siempre están abiertas para ti. Soy el hermano Julián y me alegra ver a cualquier siervo de nuestro gran Señor.";
			link.l1 = TimeGreeting() + ". Me llamo " + GetFullName(pchar) + "Encantado de conocerte, hermano Julián.";
			link.l1.go = "meeting";
			npchar.quest.meeting = "1";
		}
		else
		{
			dialog.text = "¡Ah, " + GetFullName(pchar) + "! " + TimeGreeting() + ". ¿Quieres algo?";
			link.l1 = "Quiero hacerte algunas preguntas sobre la isla.";
			link.l1.go = "int_quests"; // информационный блок
			link.l2 = "¿Puedo comprar algunas pociones de ti?";
			link.l2.go = "potion";
			link.l3 = "¿Tienes algún objeto sagrado para vender?";
			link.l3.go = "amulet";
			link.l5 = "Solo quería rezar aquí y ver cómo estás. ¡Nos vemos!";
			link.l5.go = "exit";
		}
		NextDiag.TempNode = "First time";
		break;

	case "meeting": // первая встреча
		dialog.text = "Espero que visites nuestra iglesia más a menudo. Cuida de tu alma, hijo mío. También puedo curar tu cuerpo; aquí trabajo no solo como pastor, sino también como médico.";
		link.l1 = "Quiero hacerte unas preguntas sobre la isla.";
		link.l1.go = "int_quests"; // информационный блок
		link.l2 = "¿Puedo comprar algunas pociones de ti?";
		link.l2.go = "potion";
		link.l3 = "¿Tienes algún objeto sagrado para vender?";
		link.l3.go = "amulet";
		link.l4 = "Tengo que irme, hermano Julian. ¡Nos vemos!";
		link.l4.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "potion":
		dialog.text = "Claro, hijo mío. ¿Qué poción necesitas?";
		if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
		{
			link.l1 = "Una simple poción de curación.";
			link.l1.go = "potion1";
		}
		if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
		{
			link.l2 = "Un elixir curativo.";
			link.l2.go = "potion2";
		}
		if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
		{
			link.l3 = "Un antídoto.";
			link.l3.go = "potion3";
		}
		if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
		{
			link.l4 = "Una mezcla de hierbas.";
			link.l4.go = "potion4";
		}
		link.l5 = "Lamento, hermano Julián, he cambiado de opinión.";
		link.l5.go = "exit";
		break;

	case "potion1":
		npchar.quest.price = 90;
		npchar.quest.type = 1;
		dialog.text = "¿Una poción? 90 pesos, hijo mío.";
		if (sti(Pchar.money) >= 90)
		{
			link.l1 = "Llévalos, hermano Julián.";
			link.l1.go = "potion_pay";
		}
		else
		{
			link.l1 = "No tengo suficientes monedas ahora... Volveré más tarde.";
			link.l1.go = "exit";
		}
		break;

	case "potion2":
		npchar.quest.price = 500;
		npchar.quest.type = 2;
		dialog.text = "¿Un elixir? 500 pesos, hijo mío.";
		if (sti(Pchar.money) >= 500)
		{
			link.l1 = "Tómalos, hermano Julián.";
			link.l1.go = "potion_pay";
		}
		else
		{
			link.l1 = "No tengo suficientes monedas ahora... Volveré más tarde.";
			link.l1.go = "exit";
		}
		break;

	case "potion3":
		npchar.quest.price = 200;
		npchar.quest.type = 3;
		dialog.text = "¿Un antídoto? 200 pesos, hijo mío.";
		if (sti(Pchar.money) >= 200)
		{
			link.l1 = "Llévalos, hermano Julián.";
			link.l1.go = "potion_pay";
		}
		else
		{
			link.l1 = "No tengo suficientes monedas ahora... Volveré más tarde.";
			link.l1.go = "exit";
		}
		break;

	case "potion4":
		npchar.quest.price = 900;
		npchar.quest.type = 4;
		dialog.text = "¿Una mezcla? 900 pesos, hijo mío.";
		if (sti(Pchar.money) >= 900)
		{
			link.l1 = "Tómalos, hermano Julián.";
			link.l1.go = "potion_pay";
		}
		else
		{
			link.l1 = "No tengo suficientes monedas ahora... Volveré más tarde.";
			link.l1.go = "exit";
		}
		break;

	case "potion_pay":
		AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
		iTemp = sti(npchar.quest.type);
		GiveItem2Character(pchar, "potion" + iTemp);
		PlaySound("interface\important_item.wav");
		dialog.text = "Aquí. Toma tu medicina. ¡Que Dios te guíe!";
		link.l1 = "Gracias, hermano Julián.";
		link.l1.go = "exit";
		SaveCurrentNpcQuestDateParam(npchar, "potion" + iTemp + "_date");
		break;

	case "amulet":
		bool bOK = (!CheckAttribute(npchar, "amulet_date")) || (GetNpcQuestPastDayParam(npchar, "amulet_date") >= 3) if (bOk && GetSummonSkillFromName(pchar, SKILL_FORTUNE) > (10 + hrand(110)))
		{
			npchar.quest.amulet = SelectLSCChurchAmulet();
			dialog.text = "Sí, puedo darte algunos amuletos sagrados que protegen a la gente de heridas y enfermedades. El precio es el mismo para cualquier amuleto: diez doblones de oro. Puedo ofrecerte " + XI_ConvertString(npchar.quest.amulet) + " hoy.";
			if (PCharDublonsTotal() >= 10)
			{
				link.l1 = "Sí, quiero comprar este amuleto. Aquí está tu oro.";
				link.l1.go = "amulet_pay";
				link.l2 = "No necesito este amuleto, hermano Julian. Esperaré hasta que tengas lo que necesito.";
				link.l2.go = "exit";
				SaveCurrentNpcQuestDateParam(npchar, "amulet_date");
			}
			else
			{
				link.l1 = "Ahora no tengo suficientes monedas... Volveré más tarde.";
				link.l1.go = "exit";
			}
		}
		else
		{
			dialog.text = "No, hijo mío, desafortunadamente no tengo nada más. Ven a verme otro día, quizás encuentre algo para ti.";
			link.l1 = "Trato, hermano Julián.";
			link.l1.go = "exit";
		}
		break;

	case "amulet_pay":
		RemoveDublonsFromPCharTotal(10);
		GiveItem2Character(pchar, npchar.quest.amulet);
		Log_Info("Has recibido un amuleto");
		PlaySound("interface\important_item.wav");
		dialog.text = "Gracias, hijo mío. Tu dinero será bien utilizado. Toma tu amuleto y ¡que Dios te bendiga!";
		link.l1 = "Gratitud, hermano Julián.";
		link.l1.go = "exit";
		break;

		//--------------------------------------- блок вопросов и ответов ---------------------------------------------
	case "int_quests":
		dialog.text = "Estoy escuchando.";
		if (!CheckAttribute(npchar, "quest.answer_1"))
		{
			link.l1 = "¿Cómo llegaste aquí, hermano Julián?";
			link.l1.go = "ansewer_1";
		}
		if (!CheckAttribute(npchar, "quest.answer_2"))
		{
			link.l2 = "¿Cuántas personas hay en tu parroquia?";
			link.l2.go = "ansewer_2";
		}
		if (!CheckAttribute(npchar, "quest.answer_3"))
		{
			link.l3 = "¿Quién vende cosas aquí?";
			link.l3.go = "ansewer_3";
		}
		if (!CheckAttribute(npchar, "quest.answer_4"))
		{
			link.l4 = "¿Existe algún riesgo de destrucción para la Isla? ¿Tormentas, quizás?";
			link.l4.go = "ansewer_4";
		}
		link.l10 = "Sin preguntas. Lo siento...";
		link.l10.go = "exit";
		break;

	case "ansewer_1":
		dialog.text = "De la misma manera que muchos de los lugareños, hijo mío. Mi barco fue hundido por una tormenta durante mi viaje de La Habana a la Nueva España. Gracias a Dios, sobreviví y ahora le sirvo aquí, ayudando a las almas perdidas a encontrar su verdadero camino.";
		link.l1 = "Veo...";
		link.l1.go = "int_quests";
		npchar.quest.answer_1 = "true";
		break;

	case "ansewer_2":
		dialog.text = "Menos de lo que quiero. La mayoría de los Narvalos prefieren la violencia a la misericordia y los Rivados son ovejas pobres y perdidas. Realizan ciegamente sus rituales paganos, poniendo en riesgo sus almas inmortales. Hay un hechicero peligroso entre ellos que debe ser purificado por la Santa Inquisición.";
		link.l1 = "Veo...";
		link.l1.go = "int_quests";
		npchar.quest.answer_2 = "true";
		break;

	case "ansewer_3":
		dialog.text = "Sancho Carpentero posee una taberna en el Fleron, allí puedes encontrar comida, bebidas y una cama caliente. Axel Yost vende una gran variedad de mercancías en la 'Esmeralda'. Pregunta a la gente en las calles, hijo mío, muchos de ellos encuentran cosas interesantes en el anillo exterior.";
		link.l1 = "¡Gracias!";
		link.l1.go = "int_quests";
		npchar.quest.answer_3 = "true";
		break;

	case "ansewer_4":
		dialog.text = "Todo está en manos de nuestro Señor, hijo mío. Creemos en Él y confiamos en Él. Los problemas serios siempre se han mantenido alejados de nuestra Isla: las tormentas a menudo ocurren fuera de ella, pero aquí siempre hay tranquilidad.";
		link.l1 = "Gracias. Me has tranquilizado.";
		link.l1.go = "int_quests";
		npchar.quest.answer_4 = "true";
		break;
		// <-- блок вопросов и ответов

		//----------------------------------------- специальные реакции -----------------------------------------------
		// обнаружение ГГ в сундуках
	case "Man_FackYou":
		dialog.text = LinkRandPhrase("¿Qué haces ahí, eh? ¡Ladrón!", "¡Mira eso! ¡Apenas me perdí en la contemplación, decidiste revisar mis cofres!", "¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!");
		link.l1 = "¡Mierda!";
		link.l1.go = "fight";
		break;

	case "Woman_FackYou":
		dialog.text = "¿Qué?! ¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!";
		link.l1 = "¡Chiquilla insensata!";
		link.l1.go = "exit_setOwner";
		LAi_group_Attack(NPChar, Pchar);
		break;

	case "fight":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetOwnerTypeNoGroup(npchar);
		LAi_group_Attack(NPChar, Pchar);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "exit_setOwner":
		LAi_SetOwnerTypeNoGroup(npchar);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	// замечание по обнажённому оружию
	case "LSCNotBlade":
		dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.", "Sabes, no se tolera correr con la espada aquí. Guárdala.", "Escucha, no juegues al caballero medieval corriendo con una espada por ahí. Quítatela, no te queda bien...");
		link.l1 = LinkRandPhrase("Bien.", "Está bien.", "Como dices...");
		link.l1.go = "exit";
		NextDiag.TempNode = "First Time";
		break;

	case "CitizenNotBlade":
		if (loadedLocation.type == "town")
		{
			dialog.text = NPCharSexPhrase(NPChar, "Escucha, soy ciudadano de esta ciudad y te pediría que envaines tu espada.", "Escucha, soy ciudadano de esta ciudad y te pediría que envaines tu espada.");
			link.l1 = LinkRandPhrase("Bien.", "Está bien.", "Como usted diga...");
		}
		else
		{
			dialog.text = NPCharSexPhrase(NPChar, "Ten cuidado, camarada, al correr con un arma. Puedo ponerme nervioso...", "No me gusta cuando la gente camina frente a mí con su arma lista. Me asusta...");
			link.l1 = RandPhraseSimple("Entendido.", "Me lo llevo.");
		}
		link.l1.go = "exit";
		NextDiag.TempNode = "First Time";
		break;
		// <-- специальные реакции

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}

string SelectLSCChurchAmulet();
{
	string sAmulet;
	switch (hrand(3))
	{
	case 0:
		sAmulet = "amulet_2";
		break;
	case 1:
		sAmulet = "amulet_3";
		break;
	case 2:
		sAmulet = "amulet_6";
		break;
	case 3:
		sAmulet = "amulet_7";
		break;
	}
	return sAmulet;
}

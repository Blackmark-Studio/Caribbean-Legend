// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?", "¿Cómo puedo ayudarle?"), "Intentaste hacerme esa pregunta no hace mucho...", "Sí, déjame adivinar... ¿Otra vez dando vueltas en círculos?", "Escucha, yo manejo las finanzas aquí, no respondo preguntas...", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No tengo nada de qué hablar en este momento."), "Umph, ¿dónde se ha ido mi memoria...?", "Lo has adivinado, lo siento...", "Entiendo...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		// --> Sinistra Длинные тени старых грехов
		if (CheckAttribute(pchar, "questTemp.DTSG_KnippelDolg"))
		{
			link.l1 = "Me gustaría hablar contigo sobre uno de tus deudores.";
			link.l1.go = "DTSG_KnippelDolg";
		}
		// <-- Длинные тени старых грехов
		break;

	// --> Sinistra Длинные тени старых грехов
	case "DTSG_KnippelDolg":
		DeleteAttribute(pchar, "questTemp.DTSG_KnippelDolg");
		dialog.text = "¿Cuál?";
		if (sti(pchar.reputation.nobility) > 50)
		{
			link.l1 = "(Honor) Pues, Charlie Knippel.";
			link.l1.go = "DTSG_KnippelDolg_VD_2";
		}
		else
		{
			link.l2 = "(Honor) Tienes el descaro de hablarme con tanta calma. Enviaste cazarrecompensas tras mi hombre.";
			link.l2.go = "DTSG_KnippelDolg_2";
		}
		break;

	case "DTSG_KnippelDolg_VD_2":
		dialog.text = "¿Charlie? Pero ya no es mi deudor. Su deuda fue saldada hace mucho tiempo, sir.";
		link.l1 = "¿De veras? ¿Por quién, si no es un secreto?";
		link.l1.go = "DTSG_KnippelDolg_VD_3";
		break;

	case "DTSG_KnippelDolg_VD_3":
		dialog.text = "No lo es. Por su capitán, Richard Fleetwood. Un verdadero caballero, todos deberían tener amigos como él.";
		link.l1 = "Verás, ahora soy el capitán de Charlie. El señor Fleetwood... lo transfirió a mi servicio. Es bueno saber que cumplió su promesa y te pagó.";
		link.l1.go = "DTSG_KnippelDolg_VD_4";
		break;

	case "DTSG_KnippelDolg_VD_4":
		dialog.text = "Así que por eso preguntas.";
		link.l1 = "No sólo eso. Conoces bien a Charlie, ¿verdad? Fue arrestado, y antes enviaron mercenarios tras él. ¿Alguna idea de por qué? Al fin y al cabo, tienes tratos con un círculo de personas muy... diverso.";
		link.l1.go = "DTSG_KnippelDolg_VD_5";
		break;

	case "DTSG_KnippelDolg_VD_5":
		dialog.text = "¿Charlie arrestado? Me sorprendes, sir, no sabía nada al respecto. Ni sobre sus... enemigos. Un buen hombre temeroso de Dios como él...";
		link.l1 = "No se puede discutir con eso. Bueno, gracias de todos modos. Espero que el comandante acepte la fianza de mi parte.";
		link.l1.go = "DTSG_KnippelDolg_VD_6";
		break;

	case "DTSG_KnippelDolg_VD_6":
		dialog.text = "No dude en acercarse a mí de nuevo si necesita fondos para asegurar la fianza, le ofreceré buenas condiciones.";
		link.l1 = "Ja-ja, ¿hablas en serio? Un prestamista siempre será un prestamista. Puedo permitirme la fianza yo mismo. Adiós.";
		link.l1.go = "DTSG_KnippelDolg_VD_7";
		break;

	case "DTSG_KnippelDolg_VD_7":
		DialogExit();

		LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
		// LAi_LocationDisableOfficersGen("SentJons_town", false);
		LAi_LocationDisableOfficersGen("SentJons_bank", false);
		AddQuestRecord("DTSG", "11");
		pchar.questTemp.DTSG_AntiguaZalog = true;
		AddLandQuestMarkToPhantom("SentJons_prison", "SentJonsJailOff");
		break;

	case "DTSG_KnippelDolg_2":
		dialog.text = "¿Cazarrecompensas? ¿Tras tu hombre? ¿De qué estás hablando?..";
		link.l1 = "No lo niegues. Mejor confiesa, y lo resolveremos como caballeros. Pero si te haces el tonto, tendré que tratar contigo de la manera difícil.";
		link.l1.go = "DTSG_KnippelDolg_3";
		break;

	case "DTSG_KnippelDolg_3":
		dialog.text = "¡D-debes estar equivocado!.. ¡Guardia! ¡Está amenazando con matarme!";
		link.l1 = "¡Por el amor de Dios!";
		link.l1.go = "DTSG_KnippelDolg_4";
		break;

	case "DTSG_KnippelDolg_4":
		DialogExit();

		sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaStrazhBank_1", "sold_eng_" + (rand(15) + 1), "man", "man", 10, ENGLAND, 0, false, "soldier"));
		GiveItem2Character(sld, "blade_10");
		EquipCharacterByItem(sld, "blade_10");
		GiveItem2Character(sld, "pistol1");
		EquipCharacterByItem(sld, "pistol1");
		ChangeCharacterAddressGroup(sld, "SentJons_bank", "reload", "reload1");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_AntiguaStrazhBank";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		LAi_SetHP(sld, 140 + MOD_SKILL_ENEMY_RATE * 10, 140 + MOD_SKILL_ENEMY_RATE * 10);
		AddLandQuestMarkToPhantom("SentJons_prison", "SentJonsJailOff");
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

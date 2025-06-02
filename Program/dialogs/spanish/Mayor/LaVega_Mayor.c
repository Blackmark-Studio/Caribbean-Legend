// заместитель Маркуса Тиракса в Ла Веге
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// ------------------------------------------блок angry-----------------------------------------------
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
	// ------------------------------------------блок angry-----------------------------------------------

	switch (Dialog.CurrentNode)
	{
	// ----------------------------------- Диалог первый - первая встреча
	case "First time":
		dialog.text = NPCStringReactionRepeat("¿Tienes algo que decirme? ¿No? ¡Entonces aléjate de aquí!", "Creo que me he expresado claramente, deja de molestarme.", "¡Aunque he sido claro, sigues molestándome!", "Bien, me estoy cansando de esta grosería.", "repeat", 3, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Ya me voy.", "Por supuesto" + npchar.name + "...", "Lo siento, " + npchar.name + "...", "Ups...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "Exit":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		break;

	case "I_know_you_good":
		dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + ", ¡Me alegra verte! ¿Qué deseas?", "¿Qué más?", " ¿Tú de nuevo? ¡No molestes a la gente si no tienes nada que hacer!", "Yo sé que eres un hombre decente. Pero he terminado de hablar contigo.", "repeat", 10, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Nada. Solo quería verte.", "Nada...", "De acuerdo, " + npchar.name + "Lo siento...", "Maldita sea, es solo mi culpa...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		NextDiag.TempNode = "I_know_you_good";
		break;

	// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
	case "Man_FackYou":
		dialog.text = LinkRandPhrase("¡Ratería! ¿Estás hablando en serio? Estás acabado, amigo...", "Espera, ¿qué demonios? ¡Resulta que eres un ladrón! Estás acabado...");
		link.l1 = LinkRandPhrase("¡Mierda!", "¡Carramba!!", "¡Maldita sea!!");
		link.l1.go = "PL_Q3_fight";
		break;

	// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
	case "AngryRepeat_1":
		dialog.text = RandPhraseSimple("" + GetSexPhrase("Vete", "Aléjate ") + " ¡de aquí!", "¡Sal de mi casa!");
		link.l1 = "Ups...";
		link.l1.go = "AngryExitAgainWithOut";
		if (CheckAttribute(npchar, "angry.terms")) // примиряемся через 10 дней.
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
		dialog.text = "Se acabó, no hay más que hablar.";
		link.l1 = RandPhraseSimple("Como desees...", "Bien entonces...");
		link.l1.go = "AngryExitAgain";
		if (CheckAttribute(npchar, "angry.terms")) // примиряемся через 10 дней.
		{
			if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
			{
				dialog.text = "¿Espero que me muestres más respeto y dejes de ser grosero? Tendría que matarte de lo contrario. Eso sería muy desagradable.";
				link.l1 = "" + npchar.name + ", puedes estar seguro, lo haré.";
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
		DoReloadCharacterToLocation("Lavega_town", "reload", "reload6");
		break;
	// <<<<<<<<<<<<============= блок нод angry =============================

	// Rebbebion, квест "Путеводная звезда"
	case "PZ1":
		dialog.text = "Ah, eres tú, de Maure. Bueno, qué sorpresa. Por el diablo del mar, tu llegada es lo más interesante que ha pasado en mucho tiempo, maldita sea.";
		link.l1 = "Me alegra verte también, Vensan. ¿Disfrutando de gobernar el pueblo?";
		link.l1.go = "PZ2";
		DelLandQuestMark(npchar);
		break;

	case "PZ2":
		dialog.text = "¿Cómo podría? Soy un capitán, ¡un maldito buen capitán, para eso, no algún condenadamente contable! Y he estado esperando a que los mensajeros de Marcus me convoquen para un nuevo viaje más tiempo del que he esperado la Navidad, ¡malditas maldiciones!";
		link.l1 = "Navidad y maldiciones en una sola frase, eso sí que es algo. ¡Ay, no te envidio! Aunque, muchos desearían estar en tu posición actual. Pero he venido a verte por negocios, Vensan.";
		link.l1.go = "PZ3";
		break;

	case "PZ3":
		dialog.text = "¿Negocios?! Bueno, escúpelo entonces, ¿has pensado en algo? ¿Tienes una buena pista? Estoy a punto de vaciar la bodega por puro aburrimiento y todos estos malditos cálculos.";
		link.l1 = "Bueno, es más que tengo una pregunta para usted, nada más.";
		link.l1.go = "PZ4";
		break;

	case "PZ4":
		dialog.text = "¡Maldita sea! Pero bueno, te escucho, Charles.";
		link.l1 = "¿Ha venido a verte una mujer? ¿O tal vez la has visto en La Vega? Se hace llamar Belle Étoile, aunque ese es solo un alias, así que podría haberse presentado con otro nombre. Lo importante es que ella... tiene la piel amarilla. Pero no es una esclava ni una trabajadora, es una mujer adinerada.";
		link.l1.go = "PZ5";
		break;

	case "PZ5":
		dialog.text = "¿Piel amarilla, pero rico? ¡Nunca hemos tenido a alguien así aquí, jamás! Parece que sigues llevando esa vida interesante tuya, ¡de Maure! Casi te envidio.";
		link.l1 = "¿Es eso así...? Bueno, gracias por tu tiempo, Vensan. No te distraeré más de tu contabilidad, je-je.";
		link.l1.go = "Exit";

		AddQuestRecord("PZ", "40");

		pchar.quest.PZ_SetHeavyFrigate.win_condition.l1 = "location";
		pchar.quest.PZ_SetHeavyFrigate.win_condition.l1.location = "Hispaniola1";
		pchar.quest.PZ_SetHeavyFrigate.win_condition = "PZ_SetHeavyFrigate";
		DelMapQuestMarkCity("LaVega");
		AddMapQuestMarkCity("PortPax", false);
		LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", true);
		LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
		break;
	}
}

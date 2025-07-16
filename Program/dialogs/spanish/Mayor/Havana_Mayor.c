// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref FortChref;
	FortChref = GetFortCommander(NPChar.City);
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué quieres? Pregunta lo que desees.", "Te escucho, ¿cuál es la pregunta?"), "Esta es la segunda vez que intentas preguntar...", "Es la tercera vez que intentas preguntar...", "¿Cuándo va a terminar esto?! ¡Soy un hombre ocupado, trabajando en asuntos de la colonia y todavía me estás molestando!", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No ahora. Lugar y momento equivocados."), "Verdad... Pero más tarde, no ahora...", "Preguntaré... Pero un poco más tarde...", "Lo siento, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		// Addon 2016-1 Jason пиратскаЯ линейка
		if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_6")
		{
			link.l1 = "Su Excelencia, estoy aquí por el oficial encarcelado, Lope Montoro...";
			link.l1.go = "Mtraxx";
		}
		break;

	case "Cupture_after":
		dialog.text = RandPhraseSimple("Ya te has llevado todo. ¿Qué más quieres?", "¿Queda algo que no hayas agarrado?");
		link.l1 = RandPhraseSimple("Sólo echando un vistazo...", "Solo estoy comprobando, podría haber olvidado tomar algo...");
		link.l1.go = "exit";
		NextDiag.TempNode = "Cupture_after";
		break;

	case "Slavetrader_HavanaAttack":
		dialog.text = "¡Malditos ladrones! ¿Os atrevéis a atacar La Habana?! ¿Qué queréis?!";
		link.l1 = "Piensa un poco, lo entenderás.";
		link.l1.go = "Slavetrader_HavanaAttack_1";
		pchar.quest.Slavetrader_HavanaOver.over = "yes";
		AfterTownBattle();
		break;

	case "Slavetrader_HavanaAttack_1":
		dialog.text = "¡Oro, por supuesto! ¿En qué más podrían estar interesados, malditos, sino en oro?! Y no lo tenemos... Solo unas pocas medidas en la tienda.";
		link.l1 = "Ja, ja... No, no estamos interesados en el oro. Vinimos aquí por el marfil... el negro. ¿Me entiendes?";
		link.l1.go = "Slavetrader_HavanaAttack_2";
		break;

	case "Slavetrader_HavanaAttack_2":
		if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD) // для особо хитрых - нефиг лезть с суши
		{
			dialog.text = "¡Ja! He sospechado que has venido aquí por esclavos. Pero están ubicados en el fuerte. Nuestros refuerzos están llegando ahora y tu banda será destruida en un segundo.";
			link.l1 = "¡Maldita sea! Bueno, siéntate aquí y no te muevas... ¡Vámonos de aquí! Mierda...";
			link.l1.go = "Slavetrader_HavanaAttack_lose";
		}
		else
		{
			dialog.text = "¿Pero cómo... Cómo lo supiste?";
			link.l1 = "¡Ja! Solo un idiota podría reunir 5000 esclavos en un solo lugar y esperar que nadie lo supiera. Apestan desde aquí hasta la maldita Tortuga... Espero que entiendas que los vamos a quitar de tu posesión.";
			link.l1.go = "Slavetrader_HavanaAttack_3";
		}
		break;

	case "Slavetrader_HavanaAttack_3":
		dialog.text = "Está bien, has ganado de todos modos y tenemos que obedecer a tu violencia. Pero no esperes escapar de la justicia después de ese robo y de hundir dos buques de guerra españoles.";
		link.l1 = "No te hinches así o te dará un ataque al corazón. Siéntate aquí y no te muevas...";
		link.l1.go = "Slavetrader_HavanaAttack_4";
		ChangeCharacterHunterScore(pchar, NationShortName(sti(npchar.Nation)) + "hunter", 50);
		ChangeCharacterComplexReputation(pchar, "nobility", -8);
		break;

	case "Slavetrader_HavanaAttack_4":
		string sTemp;
		NextDiag.CurrentNode = "Cupture_after";
		DialogExit();
		SetReturn_Gover_Dialog_Exit(NPChar);
		Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
		pchar.quest.Slavetrader_DieHardHavana.over = "yes";		 // теперь можно на карту
		SetCharacterGoods(pchar, GOOD_SLAVES, 5000 + rand(500)); // c перегрузом пойдёт
		Log_SetStringToLog("Los esclavos han sido puestos en su barco");
		Log_SetStringToLog("Tienes 30 días para entregar los esclavos a tu empleador");
		chrDisableReloadToLocation = false;
		sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
		AddQuestRecord("Slavetrader", "27");
		AddQuestUserData("Slavetrader", "sQty", sTemp);
		SetFunctionTimerCondition("Slavetrader_FiveTSlavesOver", 0, 0, 30, false); // таймер
		pchar.questTemp.Slavetrader = "Win_HavanaFort";
		break;

	case "Slavetrader_HavanaAttack_lose":
		NextDiag.CurrentNode = "Cupture_after";
		DialogExit();
		SetReturn_Gover_Dialog_Exit(NPChar);
		ChangeCharacterComplexReputation(pchar, "nobility", -8);
		Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
		chrDisableReloadToLocation = false;
		pchar.quest.Slavetrader_DieHardHavana.over = "yes"; // можно на карту
		pchar.quest.Slavetrader_HavanaAttack.over = "yes";	// если из Сантьяго по суше пришёл - уберем корабли
		AddQuestRecord("Slavetrader", "27_1");
		AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("", ""));
		CloseQuestHeader("Slavetrader");
		pchar.questTemp.Slavetrader = "End_quest";
		break;

	// Addon 2016-1 Jason пиратскаЯ линейка
	case "Mtraxx":
		dialog.text = "Qué curioso... ¿más quejas?";
		link.l1 = "No, no, al contrario, su Excelencia. Lope es un viejo amigo del ejército, luchamos juntos en Europa... Me encantaría ayudarlo y vine a pedir su asistencia.";
		link.l1.go = "Mtraxx_1";
		DelLandQuestMark(npchar);
		break;

	case "Mtraxx_1":
		dialog.text = "Mm... Bueno, supongo que, ya que has venido a mí, ya conoces esta... absurda historia, ¿no?";
		link.l1 = "Lo hago, su Excelencia.";
		link.l1.go = "Mtraxx_2";
		break;

	case "Mtraxx_2":
		dialog.text = "Le sugiero que contacte a don Rosario Gusman. Él, al igual que usted, quiere ayudar a don Lope Montero. Había intentado contactar a la víctima, sin embargo, las negociaciones no dieron frutos. Reúnase con él, le explicará los detalles. Puede encontrar a don Rosario en las calles desde las cuatro hasta las ocho de la tarde. Hace una inspección completa de los puestos de guardia de la ciudad todos los días.";
		link.l1 = "¡Gratitud, su Excelencia!";
		link.l1.go = "Mtraxx_3";
		break;

	case "Mtraxx_3":
		DialogExit();
		pchar.questTemp.Mtraxx = "jewelry_7";
		AddQuestRecord("Roger_1", "17");
		Mtraxx_CreateRosario();
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

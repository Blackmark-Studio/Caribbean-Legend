// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?", "¿Cómo puedo ayudarle?"), "Intentaste hacerme esa pregunta no hace mucho...", "Sí, déjame adivinar... ¿Otra vez dando vueltas en círculos?", "Escucha, yo manejo las finanzas aquí, no respondo preguntas...", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No tengo nada de qué hablar en este momento."), "Umph, ¿a dónde se ha ido mi memoria...?", "Lo has adivinado, lo siento...", "Entiendo...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		break;

	case "tonzag_bail":
		dialog.text = "Hola, capitán. ¿Cómo puedo yo y mi firma ser de servicio para usted?";
		link.l1 = "Me gustaría hacer una donación al fondo de pensiones de la ilustre guarnición de Tortuga.";
		link.l1.go = "tonzag_bail_1";
		break;

	case "tonzag_bail_1":
		dialog.text = "Entiendo. ¡Haciéndose bastante popular estos días! ¿Cuánto debe... quiero decir, desea donar?";
		link.l1 = pchar.questTemp.TonzagQuest.Bail + " doblones. Dime, ¿aceptas en pesos?";
		link.l1.go = "tonzag_bail_2";
		break;

	case "tonzag_bail_2":
		dialog.text = "Por supuesto, sin embargo, será un poco más caro para usted. Permítame decirle exactamente... " + pchar.questTemp.TonzagQuest.Bail + " los doblones serán " + sti(pchar.questTemp.TonzagQuest.Bail) * 150 + " pesos.";
		if (PCharDublonsTotal() >= sti(pchar.questTemp.TonzagQuest.Bail) || sti(pchar.money) >= sti(pchar.questTemp.TonzagQuest.Bail) * 150)
		{
			link.l1 = "¿Un poco más caro, dices? Aquí tienes, la cantidad total requerida.";
			link.l1.go = "tonzag_bail_give";
		}
		else
		{
			link.l1 = "¿Un poco más caro, dices? Desafortunadamente, no tengo esa cantidad en este momento. ¿Es posible tomar un préstamo para este asunto?";
			link.l1.go = "tonzag_bail_loan";
		}
		break;

	case "tonzag_bail_give":
		dialog.text = "Maravilloso. ¡Informaremos a su contraparte de inmediato! Adiós, capitán. Y... buena suerte, hemos estado esperando su actuación durante mucho tiempo.";
		link.l1 = "Adiós.";
		link.l1.go = "exit";

		NextDiag.TempNode = "First time";

		if (PCharDublonsTotal() >= sti(pchar.questTemp.TonzagQuest.Bail))
		{
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.TonzagQuest.Bail));
		}
		else
		{
			AddMoneyToCharacter(pchar, -(sti(pchar.questTemp.TonzagQuest.Bail) * 150));
		}
		sld = CharacterFromID("TortugaJailOff");
		LAi_CharacterEnableDialog(sld);
		sld.dialog.currentnode = "tonzag_bailed";
		break;

	case "tonzag_bail_loan":
		dialog.text = "¡Tal oportunidad siempre está disponible para usted, capitán! Digamos, ¿con la devolución de doscientos mil pesos en seis meses?";
		link.l1 = "No tengo elección. ¿Dónde firmo?";
		link.l1.go = "tonzag_bail_give";

		pchar.quest.loans.tortuga.sum = 200000;
		pchar.quest.loans.tortuga.interest = 0;
		pchar.quest.loans.tortuga.period = 6;
		pchar.quest.loans.tortuga.StartDay = GetDataDay();
		pchar.quest.loans.tortuga.StartMonth = GetDataMonth();
		pchar.quest.loans.tortuga.StartYear = GetDataYear();
		pchar.quest.loans.tortuga.StartTime = GetTime();
		SetTimerCondition("Loans_Tortuga", 0, makeint(pchar.quest.loans.tortuga.period), 0, false);
		pchar.quest.Loans_Tortuga.CityId = "Tortuga";
		pchar.quest.Loans_Tortuga.win_condition = "LoansForAll";

		AddMoneyToCharacter(pchar, sti(pchar.questTemp.TonzagQuest.Bail) * 150);
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

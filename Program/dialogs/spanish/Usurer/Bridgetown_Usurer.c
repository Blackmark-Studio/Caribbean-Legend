// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?", "¿Cómo puedo ayudarte?"), "Intentaste hacerme esa pregunta no hace mucho...", "Sí, déjame adivinar... ¿Otra vez dando vueltas en círculos?", "Escucha, yo manejo las finanzas aquí, no respondo preguntas...", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No tengo nada de qué hablar en este momento."), "Umph, ¿dónde se ha ido mi memoria...?", "Lo has adivinado, lo siento...", "Entiendo...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		// Голландский гамбит
		if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
		{
			link.l1 = "Me dirijo a Blueweld con un cargamento de vino. Pero me enteré por un capitán que en Blueweld ha aumentado la demanda de café, y no sé qué lo está causando. Estoy pensando en vender el vino y comprar café en su lugar, pero no tengo suficiente dinero para llenar mi bodega hasta arriba. ¿Podría pedirte dinero prestado con interés?";
			link.l1.go = "UsurerDone";
		}
		break;

	case "UsurerDone":
		dialog.text = "Crédito para un comerciante reputado, no hay problema. ¿Qué cantidad necesitas? Hablemos de ello.";
		link.l1 = "Está bien. Cargaré la bodega y contaré cuánto espacio queda. Luego calcularé la cantidad que me falta y volveré a ti, si es necesario.";
		link.l1.go = "exit";
		npchar.quest.HWICTalked = "true";
		pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter) + 1;
		AddQuestRecord("Holl_Gambit", "2-13");
		DelLandQuestMark(npchar);
		if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7)
		{
			AddQuestRecord("Holl_Gambit", "2-6");
			pchar.questTemp.HWIC.Eng = "SeekVanBerg";
			pchar.quest.GotoBridgetownOver.over = "yes"; // снять таймер
			DelMapQuestMarkCity("Bridgetown");
			pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
			pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			// if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_VALCIRIA || GetCompanionQuantity(pchar) > 1) AddDialogExitQuestFunction("FailVanBergInWorld");
			// else AddDialogExitQuestFunction("CreateVanBergInWorld");
		}
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

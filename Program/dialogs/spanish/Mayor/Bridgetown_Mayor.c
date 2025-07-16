// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué quieres? Pregunta lo que desees.", "Te escucho, ¿cuál es la pregunta?"), "Es la segunda vez que intentas preguntar...", "Es la tercera vez que intentas preguntar de nuevo...", "¿Cuándo va a terminar?! ¡Soy un hombre ocupado, trabajando en los asuntos de la colonia y tú sigues intentando preguntar algo!", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "Ahora no. Lugar y tiempo equivocados."), "Verdad... Pero más tarde, no ahora...", "Preguntaré... Pero un poco más tarde...", "Lo siento, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		// Голландский гамбит
		if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
		{
			link.l1 = "Tuve un negocio rentable en Martinica y ahora planeo navegar hacia Blueweld. Quiero comprar palo de rosa y café en tu colonia. Además, mi bergantín no puede transportar tanto cargamento como quiero comprar, así que necesito comprar un filibote aquí en tu astillero. ¿Podría contar con tu asistencia en estos asuntos?";
			link.l1.go = "MayorDone";
		}
		break;

	case "MayorDone":
		dialog.text = "¿Mi asistencia? Nuestro comerciante es un hombre muy honesto, así que dudo que intente engañarte. Habla con el maestro de barcos sobre el filibote, él te ayudará con este asunto. Y si de todos modos tienes problemas, entonces deberías venir a verme. Estoy interesado en avanzar las conexiones comerciales con nuestra colonia y te mostraré todo mi apoyo.\nAdemás, estoy organizando un banquete esta noche, asistirán las mentes más brillantes de Bridgetown. Deberías venir también, capitán.";
		link.l1 = "Gracias por vuestra invitación, pero desafortunadamente estoy demasiado ocupado. ¡Adiós y gracias por vuestra gestión!";
		link.l1.go = "exit";
		npchar.quest.HWICTalked = "true";
		pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter) + 1;
		AddQuestRecord("Holl_Gambit", "2-8");
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

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué quieres? Pregunta lo que desees.", "Te escucho, ¿cuál es la pregunta?"), "Es la segunda vez que intentas preguntar...", "Es la tercera vez que intentas preguntar de nuevo...", "¿Cuándo va a terminar?! Soy un hombre ocupado, trabajando en los asuntos de la colonia y tú todavía intentas preguntar algo!", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "Ahora no. Lugar y momento equivocados."), "Verdad... Pero más tarde, no ahora...", "Preguntaré... Pero un poco más tarde...", "Lo siento, " + GetAddress_FormToNPC(NPChar) + "... ", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		//--> Бремя гасконца
		if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "saga" && !CheckAttribute(npchar, "quest.saga"))
		{
			link.l1 = "Quiero ver al Caballero de Poincy. Se trata de la deuda de mis hermanos.";
			link.l1.go = "puancie";
		}
		//<-- Бремя гасконца
		break;

	case "puancie":
		dialog.text = "Ajá, bueno, estoy informado sobre esa deuda... ¿Tienes la suma requerida contigo?";
		if (sti(pchar.money) >= 1000000)
		{
			link.l1 = "Claro que sí. ¿Cómo podría ser si no?";
			link.l1.go = "puancie_1";
		}
		else
		{
			link.l1 = "No, no tengo tanto dinero todavía.";
			link.l1.go = "puancie_exit";
		}
		break;

	case "puancie_exit":
		dialog.text = "Entonces vuelve cuando lo tengas y no molestes al Chevalier.";
		link.l1 = "...";
		link.l1.go = "exit";
		break;

	case "puancie_1":
		dialog.text = "Entonces pasa por la puerta de la derecha. El Chevalier te recibirá.";
		link.l1 = "¡Gracias!";
		link.l1.go = "puancie_2";
		break;

	case "puancie_2":
		DialogExit();
		npchar.quest.saga = "true";
		bDisableFastReload = true;											 // закрыть переход
		LocatorReloadEnterDisable("Charles_townhall", "reload1_back", true); // чтобы не вышел
		LocatorReloadEnterDisable("Charles_townhall", "reload3", false);	 // откроем вход к Пуанси
		ref sld = characterFromId("Puancie");
		ChangeCharacterAddressGroup(sld, "Charles_Roomtownhall", "sit", "sit1");
		LAi_SetHuberType(sld);
		sld.dialog.currentnode = "saga";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

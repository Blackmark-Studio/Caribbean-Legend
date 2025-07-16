// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat("Todos los rumores de " + GetCityName(npchar.city) + " a su servicio. ¿Qué le gustaría saber?", "Justo estábamos hablando de eso. Debes haberlo olvidado...", "Esta es la tercera vez que me molestas ahora...", "Repites todo igual que un loro...", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Sabes, " + NPChar.name + ", tal vez la próxima vez.", "Bien, lo he olvidado por alguna razón...", "Sí, es realmente la tercera vez...", "Sí...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
		{
			link.l1 = "Dime, ¿dónde puedo encontrar a la señora Belinda de Ribero?";
			link.l1.go = "guardoftruth";
		}
		break;

	case "guardoftruth":
		dialog.text = "En el palacio del gobernador, por supuesto. Es prima de Don Fernando de Villegas. Puedes buscarla allí después del mediodía durante su siesta, suele tener asuntos que atender por las mañanas. Está en algunos problemas ahora, así que tenlo en cuenta. Pero no le importará hablar contigo. Doña Belinda es una buena mujer.";
		link.l1 = "¡Gracias!";
		link.l1.go = "guardoftruth_1";
		break;

	case "guardoftruth_1":
		DialogExit();
		npchar.quest.utensil = "true";
		pchar.questTemp.Guardoftruth.Belinda = "seek";
		// ставим Белинду
		sld = GetCharacter(NPC_GenerateCharacter("GOT_Belinda", "Belinda", "woman", "towngirl", 3, SPAIN, -1, true, "quest"));
		SetFantomParamFromRank(sld, 3, true);
		sld.name = "Belinda";
		sld.lastname = "de Ribero";
		sld.dialog.FileName = "Quest\Sharlie\guardoftruth.c";
		sld.dialog.currentnode = "belinda";
		sld.greeting = "noble_female";
		LAi_SetLoginTime(sld, 13.0, 20.0);
		LAi_SetOwnerType(sld);
		LAi_SetImmortal(sld, true);
		ChangeCharacterAddressGroup(sld, "Cumana_TownhallRoom", "barmen", "stay");
		LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

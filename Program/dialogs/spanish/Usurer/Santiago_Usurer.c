// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?", "¿Cómo puedo ayudarle?"), "Intentaste hacerme esa pregunta no hace mucho...", "Sí, déjame adivinar... ¿Otra vez dando vueltas en círculos?", "Escucha, yo me encargo de las finanzas aquí, no respondo preguntas...", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No tengo nada de qué hablar en este momento."), "Umph, ¿dónde se ha ido mi memoria...?", "Lo has adivinado, lo siento...", "Entiendo...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		// Голландский гамбит, Голландия
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
		{
			link.l1 = "Señor, soy el capitán " + GetFullName(pchar) + ", y estoy aquí en una diligencia para Lucas Rodenburg. Tengo un paquete de él para usted.";
			link.l1.go = "SantiagoTripBank";
		}
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "SantiagoTripReturn")
		{
			link.l1 = "He venido por la respuesta del señor Lucas Rodenburg.";
			link.l1.go = "SantiagoTripBank_3";
		}
		// Голландский гамбит, Голландия
		break;

	case "SantiagoTripBank":
		if (GetCharacterItem(pchar, "Chest") >= 5)
		{
			dialog.text = "Solo imagina... ¡un paquete! Bueno, dámelo, señor.";
			link.l1 = "Además, el señor Rodenburg pidió que le transfiera esto...";
			link.l1.go = "SantiagoTripBank_1";
			RemoveItems(PChar, "NPC_Letter", 1);
			RemoveItems(PChar, "Chest", 5);
			DelLandQuestMark(npchar);
		}
		else
		{
			dialog.text = "Que yo sepa, había algo más que debía recibir además del paquete, capitán. Entonces... ¿dónde está? ¿Entiende de qué estoy hablando?";
			link.l1 = "¡Pero por supuesto! Los cofres están bajo vigilancia segura en mi barco. Te los entregaré de inmediato.";
			link.l1.go = "exit";
		}
		break;

	case "SantiagoTripBank_1":
		dialog.text = "Mm... interesante. Así que él 'envía sus disculpas'. Bueno-bueno. Aunque las disculpas del señor Rodenburg son bastante persuasivas, es difícil negarlo. Señor, tomará algún tiempo escribir una respuesta adecuada, ¿podría venir de nuevo y verme mañana alrededor del mediodía para que pueda llevarse una respuesta? Descanse en la taberna, camine por la ciudad. Santiago tiene mucho que ofrecer.";
		link.l1 = "Bien, regresaré mañana al mediodía. Nos vemos entonces, señor.";
		link.l1.go = "SantiagoTripBank_2";
		break;

	case "SantiagoTripBank_2":
		DialogExit();
		pchar.quest.SantiagoTripOver.over = "yes"; // снять таймер
		bDisableFastReload = true;
		pchar.quest.Santiago_Trip.win_condition.l1 = "location";
		pchar.quest.Santiago_Trip.win_condition.l1.location = "Santiago_town";
		pchar.quest.Santiago_Trip.function = "SantiagoTrip_Attack";
		pchar.questTemp.HWIC.Holl = "SantiagoTripAttack";
		LAi_LocationDisableOfficersGen("Santiago_town", true); // офицеров не пускать // 291112
		break;

	case "SantiagoTripBank_3":
		dialog.text = "Sí, por supuesto... pero creo que podemos arreglarnos sin convencionalismos escritos. Solo dile estas palabras 'este hombre debe morir'. Eso sería justo y no tendremos problemas al considerar un 'valor' de las disculpas recibidas. Y el incidente se considerará completamente resuelto.";
		link.l1 = "Bien, lo recordaré, señor. ¿Algo más?";
		link.l1.go = "SantiagoTripBank_4";
		DelLandQuestMark(npchar);
		break;

	case "SantiagoTripBank_4":
		dialog.text = "Sí, por supuesto. Lo que he dicho es la voluntad de la familia Giraldi. Y, por supuesto, puedes dar mis mejores deseos al Señor Lucas. Te deseo buen viento, capitán " + GetFullName(pchar) + ".";
		link.l1 = "Entiendo. Adiós, señor " + npchar.name + ".";
		link.l1.go = "SantiagoTripBank_5";
		break;

	case "SantiagoTripBank_5":
		DialogExit();
		pchar.questTemp.HWIC.Holl = "SantiagoTripFinal";
		LAi_LocationDisableOfficersGen("Santiago_town", false); // офицеров пускать // 291112
		AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
		AddMapQuestMarkCity("Villemstad", true);
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

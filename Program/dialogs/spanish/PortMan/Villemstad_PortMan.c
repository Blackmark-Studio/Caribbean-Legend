// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué tipo de preguntas?", "¿Qué quieres, " + GetAddress_Form(NPChar) + "?"), "Ya has intentado hacerme una pregunta " + GetAddress_Form(NPChar) + "...", "Has estado hablando de alguna cuestión por tercera vez hoy...", "Mira, si no tienes nada que decirme sobre los asuntos del puerto, entonces no me molestes con tus preguntas.", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión.", "No tengo nada de qué hablar."), "No importa.", "En efecto, ya es la tercera vez...", "Lo siento, pero no estoy interesado en los asuntos del puerto por ahora.", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";

		// работорговец
		if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_P")
		{
			link.l1 = "Me gustaría saber sobre el bergantín que desapareció tras la revuelta de esclavos.";
			link.l1.go = "EscapeSlave_Villemstad_P1";
		}
		// Голландский гамбит, против всех
		if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "SeekFleut")
		{
			link.l1 = "Quiero encontrar a un capitán llamado Toff Keller. Es dueño de un fluyt llamado 'Leiden'. Me dijeron que a menudo visita Willemstad, así que no será difícil para ti ayudarme.";
			link.l1.go = "SeekTradeFleut";
		}
		break;

	// работорговец
	case "EscapeSlave_Villemstad_P1":
		dialog.text = "Mm... ¿Y por qué te interesa? ¿Los negros son tu especialidad?";
		link.l1 = "Estoy aquí por orden de Mathias Beck, el gobernador. Tengo todas las razones para sospechar que los negros fugados robaron ese barco y se lo llevaron. Así que le pido que me ayude de todas las maneras posibles en mi búsqueda.";
		link.l1.go = "EscapeSlave_Villemstad_P2";
		break;

	case "EscapeSlave_Villemstad_P2":
		dialog.text = "Ya veo. Bueno, no puedo ayudarte. El bergantín '" + pchar.questTemp.Slavetrader.ShipName + "' se había ido por la mañana, nadie vio nada. Yo estaba en casa durmiendo. El vigilante del muelle también desapareció y no dejó rastro.\nEl gobernador envió un balandro para intentar rastrearlo mientras la pista estaba caliente, pero regresaron con las manos vacías. Ni rastro de los negros ni del '" + pchar.questTemp.Slavetrader.ShipName + "'. Para ser honesto, el balandro no los buscó muy de cerca, todos todavía estaban en pánico y pensaban que los infieles saldrían hirviendo de la jungla con horcas y machetes, hambrientos de sangre blanca.";
		link.l1 = "Eso no fue muy útil, pero gracias de todos modos. Adiós.";
		link.l1.go = "exit";
		AddQuestRecord("Slavetrader", "22_3");
		AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
		pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_H";
		break;
	// Голландский гамбит
	case "SeekTradeFleut":
		DelLandQuestMark(npchar);
		dialog.text = "¿Toff Keller? ¡Claro que lo conozco! Regularmente navega en viajes a San José, que está en Trinidad, y Cumana. Ha navegado a Trinidad recientemente. Supongo que puedes encontrarlo allí.";
		link.l1 = "¡Gracias!";
		link.l1.go = "SeekTradeFleut_1";
		break;

	case "SeekTradeFleut_1":
		DialogExit();
		AddMapQuestMarkIsland("Trinidad", true);
		pchar.questTemp.HWIC.Self = "FleutOnTrinidad";
		AddQuestRecord("Holl_Gambit", "3-59");
		pchar.quest.Seek_Fleut.win_condition.l1 = "location";
		pchar.quest.Seek_Fleut.win_condition.l1.location = "Trinidad";
		pchar.quest.Seek_Fleut.function = "CreateTradeFleut";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

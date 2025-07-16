// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat("Todos los rumores de " + GetCityName(npchar.city) + " a su servicio. ¿Qué le gustaría saber?", "Justamente estábamos hablando de eso. Debes haberlo olvidado...", "Esta es la tercera vez hoy que hablas de alguna pregunta...", "Repites lo mismo como un loro...", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Sabes, " + NPChar.name + ", tal vez la próxima vez.", "Correcto, lo he olvidado por alguna razón...", "Sí, realmente es la tercera vez...", "Sí...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		if (pchar.questTemp.Slavetrader == "FindRatPanama")
		{
			link.l1 = "Escuché que tienes a un corsario llamado Francois Gontier en tu ciudad. ¿Sabrías dónde encontrarlo?";
			link.l1.go = "Panama_rat_1";
		}
		// Addon-2016 Jason ”ЊЉ-ѓваделупа
		if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_panama")
		{
			link.l1 = "Mira, estoy buscando a un hombre llamado Bertrand Pinette, ¿has oído hablar de él? Llegó a Panamá no hace mucho. Un caballero imponente con peluca. Tal vez haya estado aquí...";
			link.l1.go = "FMQG";
		}
		break;

	//-->работорговец
	case "Panama_rat_1":
		dialog.text = NPCStringReactionRepeat("Sí, hemos tenido a un tipo así en el pueblo. Estaba merodeando por lugares oscuros... Luego algunos de sus compañeros vinieron a visitarlo, parecían una banda de rufianes. Se fue del pueblo con ellos.", "Ya has preguntado sobre eso y te he respondido.", "Te dije, ya habías preguntado por ese Gontier.", "¡Escucha, aléjate y deja de molestarme! ¿Has perdido completamente la chaveta?", "block", 0, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("¿Y sabes a dónde se fue?", "Mm, supongo que sí...", "Sí, correcto, he preguntado eso...", "Lo siento, " + npchar.name + "... ", npchar, Dialog.CurrentNode);
		link.l1.go = "Panama_rat_2";
		break;

	case "Panama_rat_2":
		dialog.text = "Bueno, solo hay una forma de salir de aquí a pie hacia Portobello. Y se fue a pie. Así que búscalo allí.";
		link.l1 = "¡Gracias, has sido de gran ayuda!";
		link.l1.go = "exit";
		pchar.questTemp.Slavetrader = "FindRatPortobello";
		AddQuestRecord("Slavetrader", "21_1");
		break;
	//<--работорговец

	// Addon-2016 Jason ”ЊЉ-ѓваделупа
	case "FMQG":
		DelLandQuestMark(npchar);
		DelMapQuestMarkCity("panama");
		dialog.text = "¿Bertrand Pinette? ¿Francés? Nunca he oído hablar de él. No, compañero, no hemos visto a franceses por aquí en un buen tiempo.";
		link.l1 = "Qué lástima... ¿Estás seguro? Es amigo de un importante hidalgo llamado Don Carlos de Milyar. Se suponía que llegarían aquí juntos.";
		link.l1.go = "FMQG_1";
		break;

	case "FMQG_1":
		dialog.text = "¿Señor de Milyar? Ese caballero visitó Panamá hace un año. En realidad, Don Carlos de Milyar es un gran amigo del gobernador.";
		link.l1 = "Ya veo. No había necesidad de perder tiempo y aliento en la jungla. Gracias, compañero.";
		link.l1.go = "FMQG_2";
		break;

	case "FMQG_2":
		DialogExit();
		pchar.questTemp.FMQG = "headhunter_portobello";
		AddQuestRecord("FMQ_Guadeloupe", "8");
		AddMapQuestMarkCity("PortoBello", true);
		AddLandQuestMark(characterFromId("PortoBello_tavernkeeper"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = RandPhraseSimple("¿Qué tipo de preguntas?", "¿Qué quieres?");
		link.l1 = RandPhraseSimple("He cambiado de opinión.", "No tengo nada que decirte.");
		link.l1.go = "exit";
		// Бремя гасконца
		if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && !CheckAttribute(npchar, "quest.Sharlie"))
		{
			link.l1 = "Disculpe, " + GetAddress_FormToNPC(NPChar) + " ¿Podrías decirme dónde puedo encontrar a Michel de Monper? He oído que está en esta ciudad.";
			link.l1.go = "Sharlie";
		}
		if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "findskiper" && !CheckAttribute(npchar, "quest.Sharlie1"))
		{
			link.l1 = "Escucha, " + GetAddress_FormToNPC(NPChar) + ", quiero preguntarte algo... Estoy buscando un navegante para servir en mi barco. ¿Conoces alguno?";
			link.l1.go = "Sharlie_1";
		}
		// Бремя гасконца
		break;

	case "info":
		// заменить на описание неких НПС, по квестам
		dialog.text = "¿Crees que trabajo para el servicio secreto de " + NationNameGenitive(sti(NPChar.nation)) + "?";
		link.l1 = "Bueno... no. Adiós entonces.";
		link.l1.go = "exit";
		link.l2 = "¿Alguna otra pregunta, entonces?";
		link.l2.go = "new question";
		break;

	case "town":
		// заменить на описание как пройти, по квестам
		dialog.text = "¿Parezco la oficina de investigación? No lo sé, no sé nada.";

		link.l1 = "¡Eres un cabeza de chorlito! Márchate.";
		link.l1.go = "exit";
		link.l2 = "¿Alguna otra pregunta, entonces?";
		link.l2.go = "new question";
		break;

	//--> Бремя гасконца
	case "Sharlie":
		if (sti(pchar.questTemp.Sharlie.Citcount) == 3)
		{
			dialog.text = "Hmm... Sospecho que has llegado aquí recientemente, ya que preguntas con tanta audacia... Te aconsejo que pares si no quieres problemas. Habla con el Abad, tal vez él te ayude a 'entrar en razón'. Puedes encontrarlo en la iglesia.";
			link.l1 = "Ya veo...";
			link.l1.go = "exit";
			AddDialogExitQuest("Sharlie_SetBenua");
			DelLandQuestMark(characterFromId("FortFrance_Mayor"));
		}
		else
		{
			dialog.text = LinkRandPhrase("No, no he oído hablar de él.", "No puedo ayudarte, tengo trabajo que hacer.", "¿Quién? No me suena, no. Debo irme a otra parte.");
			link.l1 = "Ya veo... Entonces seguiré mi camino.";
			link.l1.go = "exit";
			npchar.quest.Sharlie = "true";
		}
		break;

	case "Sharlie_1":
		dialog.text = LinkRandPhrase("No, no conozco ningún navegante.", "Tengo tareas pendientes, pregúntale a otro...", "Lamentablemente no puedo ayudarte, no conozco a nadie.");
		link.l1 = "Ya veo. Preguntaré en otro lugar entonces.";
		link.l1.go = "exit";
		npchar.quest.Sharlie1 = "true";
		npchar.dialog.currentnode = "first time";
		break;
		//<-- Бремя Гасконца
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}

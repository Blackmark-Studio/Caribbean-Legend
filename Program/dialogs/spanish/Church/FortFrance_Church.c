// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué tipo de preguntas, " + GetSexPhrase("hijo mío", "hija mía") + "?", "Pregunta lo que quieras, te escucho..."), "Estoy escuchando, habla ahora, " + GetSexPhrase("hijo mío", "hija mía") + "...", "Por tercera vez, " + GetSexPhrase("hijo mío", "hija mía") + " , pide lo que necesites.", "Un clérigo tiene mucho trabajo y me estás distrayendo, " + GetSexPhrase("hijo mío", "hija mía") + "... ", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No en este momento, padre..."), " No tengo nada que decir, mis disculpas.", "Preguntaré, pero más tarde. Perdóname, padre.", "Perdóneme, santo padre...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		// Jason Долго и счастливо
		if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "choose" && !CheckAttribute(npchar, "quest.LongHappy"))
		{
			link.l1 = "Santo Padre, busco al Abad Benoit, tengo un asunto urgente para él. ¿Puede decirme dónde puedo encontrarlo?";
			link.l1.go = "LH_church";
		}
		break;

	// Jason Долго и счастливо
	case "LH_church":
		dialog.text = "El abad Benoit ha dejado la ciudad en asuntos de la iglesia con representantes de la misión católica española en el Nuevo Mundo. No sé ningún detalle, pero el abad Benoit lleva ausente suficiente tiempo como para suponer que las negociaciones se han prolongado, o que algo sucedió en el camino. Todos estamos inquietos, pero solo podemos rezar y esperar las noticias.";
		link.l1 = "No puedo suponer que todo sea fácil. Santo padre, ¿puede decirme exactamente a dónde fue el abad Benoit? Necesito encontrarlo lo más rápido posible.";
		link.l1.go = "LH_church_1";
		break;

	case "LH_church_1":
		dialog.text = "Me temo que no puedo, hijo mío. Hasta donde sé, el abad Benoit fue a negociar con el obispo de Nueva España, y el prelado de la Inquisición, el padre Vincento Palotti, pero no especificó dónde se llevará a cabo la reunión.";
		link.l1 = "Eso debería ser suficiente, Santo Padre, gracias. Conozco al padre Palotti de alguna manera... Buscaré en Santiago.";
		link.l1.go = "LH_church_2";
		break;

	case "LH_church_2":
		DialogExit();
		npchar.quest.LongHappy = "true";
		LongHappy_GoToSantiago();
		break;
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
